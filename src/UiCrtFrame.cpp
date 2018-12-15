// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "Host.h"
#include "IoCardDisk.h"
#include "IoCardKeyboard.h"     // to pick up core_* keyboard interface
#include "IoCardPrinter.h"
#include "System2200.h"
#include "TerminalState.h"
#include "Ui.h"                 // emulator interface
#include "UiSystem.h"
#include "UiCrtFrame.h"
#include "UiCrt.h"
#include "UiCrtConfigDlg.h"
#include "UiCrtStatusBar.h"
#include "UiDiskFactory.h"
#include "UiPrinterFrame.h"

#include <algorithm>
#include <sstream>
#include <iomanip>

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon
#include "wang.xpm"

#define SFKEY_STYLE1 0
#if SFKEY_TINY_STYLE
    // special function key image for toolbar
    #include "sfkey.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
    // menu items
    File_Script = 1,
    File_Snapshot,
#if HAVE_FILE_DUMP
    File_Dump,
#endif
    File_Quit = wxID_EXIT,

    CPU_HardReset = File_Snapshot+3,
    CPU_WarmReset,
    CPU_ActualSpeed,
    CPU_UnregulatedSpeed,

    Disk_New,     // unique
    Disk_Inspect, // unique
    Disk_Format,  // unique
    Disk_Insert,  // \__ there are two per controller, up to one per IO slot
    Disk_Remove,  // /
    // ...
    Disk_LastRemove = Disk_Insert + 4*NUM_IOSLOTS-1,

    Configure_Dialog,
    Configure_Screen_Dialog,
    Configure_KeywordMode,
    Configure_SF_toolBar,
    Configure_Fullscreen,
    Configure_Stats,
    Configure_KB_Tie0,
    // ...
    Configure_KB_TieN = Configure_KB_Tie0 + NUM_IOSLOTS-1,

    // slots for printer windows
    Printer_0,
    // ...
    Printer_N = Printer_0 + NUM_IOSLOTS-1,

    Print_PrintAndClear,

    // other IDs
    TB_TOOLBAR,
    TB_SF0,  TB_SF1,  TB_SF2,  TB_SF3,
    TB_SF4,  TB_SF5,  TB_SF6,  TB_SF7,
    TB_SF8,  TB_SF9,  TB_SF10, TB_SF11,
    TB_SF12, TB_SF13, TB_SF14, TB_SF15,
    TB_EDIT,

    Timer_Frame,
    Timer_QSec,
};


// ========== Crt font styles ==========

static const struct font_table_t {
    int         size;   // encoding for font as it appears in .ini file
    std::string name;   // descriptive string
} font_table[] = {
    {  1, "Dot-matrix Font 1:1" },
    {  2, "Dot-matrix Font 1:2" },
    {  3, "Dot-matrix Font 2:4" },
    {  8, "Font Size  8" },
    { 10, "Font Size 10" },
    { 12, "Font Size 12" },
    { 14, "Font Size 14" },
    { 18, "Font Size 18" },
    { 24, "Font Size 24" },
};
const int num_fonts = (sizeof(font_table) / sizeof(font_table_t));


// ========== Crt color schemes ==========

static const struct colorscheme_t {
    unsigned char fg_r, fg_g, fg_b;     // foreground color
    unsigned char bg_r, bg_g, bg_b;     // background color
    std::string menuHelp;               // string as it appears on statusbar
} colorscheme[] = {
    {
#ifdef __WXMAC__
      0x80, 0xFF, 0x80, // Mac has different gamma than a PC, I guess
#else
      0x80, 0xFF, 0x80,
#endif
      0x00, 0x00, 0x00,
      "Green phosphor" },

    { 0xFF, 0xFF, 0xFF,
      0x00, 0x00, 0x00,
      "White phosphor" },

    { 0xFF, 0xFF, 0xFF,
#ifdef __WXMAC__
      0x10, 0x10, 0x80, // Mac different gamma than PC, I guess
#else
      0x40, 0x40, 0xA0,
#endif
      "White on Blue" }
};

static const int num_colorschemes = sizeof(colorscheme) / sizeof(colorscheme_t);

// ----------------------------------------------------------------------------
// CrtFrame
// ----------------------------------------------------------------------------

// what features are visible when in full screen mode
#define FULLSCREEN_FLAGS ( wxFULLSCREEN_NOBORDER |              \
                           wxFULLSCREEN_NOCAPTION |             \
                           wxFULLSCREEN_NOSTATUSBAR )

// CrtFrame static members
CrtFrame* CrtFrame::m_primaryFrame = nullptr;

// connect the wxWidgets events with the functions which process them
BEGIN_EVENT_TABLE(CrtFrame, wxFrame)

    EVT_MENU      (File_Script,           CrtFrame::OnScript)
    EVT_MENU      (File_Snapshot,         CrtFrame::OnSnapshot)
#if HAVE_FILE_DUMP
    EVT_MENU      (File_Dump,             CrtFrame::OnDump)
#endif
    EVT_MENU      (File_Quit,             CrtFrame::OnQuit)

    EVT_MENU      (CPU_HardReset,         CrtFrame::OnReset)
    EVT_MENU      (CPU_WarmReset,         CrtFrame::OnReset)
    EVT_MENU      (CPU_ActualSpeed,       CrtFrame::OnCpuSpeed)
    EVT_MENU      (CPU_UnregulatedSpeed,  CrtFrame::OnCpuSpeed)

    EVT_MENU      (Disk_New,              CrtFrame::OnDiskFactory)
    EVT_MENU      (Disk_Inspect,          CrtFrame::OnDiskFactory)
    EVT_MENU      (Disk_Format,           CrtFrame::OnDiskFormat)
    EVT_COMMAND_RANGE(Disk_Insert, Disk_Insert+NUM_IOSLOTS*4-1,
                wxEVT_COMMAND_MENU_SELECTED, CrtFrame::OnDisk)

    EVT_MENU      (Configure_Dialog,         CrtFrame::OnConfigureDialog)
    EVT_MENU      (Configure_Screen_Dialog,  CrtFrame::OnConfigureScreenDialog)
    EVT_MENU      (Configure_KeywordMode,    CrtFrame::OnConfigureKeywordMode)
    EVT_MENU      (Configure_SF_toolBar,     CrtFrame::OnConfigureSfToolbar)
    EVT_MENU      (Configure_Fullscreen,     CrtFrame::OnDisplayFullscreen)
    EVT_MENU      (Configure_Stats,          CrtFrame::OnConfigureStats)
    EVT_COMMAND_RANGE(Configure_KB_Tie0, Configure_KB_TieN,
                wxEVT_COMMAND_MENU_SELECTED, CrtFrame::OnConfigureKbTie)

    // printer window support
    EVT_COMMAND_RANGE(Printer_0, Printer_N,
                wxEVT_COMMAND_MENU_SELECTED, CrtFrame::OnPrinter)

    EVT_MENU      (Print_PrintAndClear,      CrtFrame::OnPrintAndClear)

    // toolbar event handler
    EVT_TOOL_RANGE(TB_SF0, TB_EDIT,          CrtFrame::OnToolBarButton)

    // non-menu event handlers
    EVT_MENU_OPEN (CrtFrame::OnMenuOpen)
    EVT_CLOSE     (CrtFrame::OnClose)
    EVT_TIMER     (Timer_Frame, CrtFrame::OnTimer)
    EVT_TIMER     (Timer_QSec,  CrtFrame::OnTimer)

    // help menu items do whatever they need to do
    HELP_MENU_EVENT_MAPPINGS()

END_EVENT_TABLE()


// constructor
CrtFrame::CrtFrame( const wxString& title,
                    const int io_addr,
                    const int term_num,
                    crt_state_t *crt_state
                  ) :
       wxFrame((wxFrame *)nullptr, -1, title, wxDefaultPosition, wxDefaultSize,
               wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE),
    m_menuBar(nullptr),
    m_statBar(nullptr),
    m_toolBar(nullptr),
    m_crt(nullptr),
    m_fullscreen(false),
    m_showstats(false),
    m_colorsel(0),
    m_fontsize{0},
    m_crt_addr(io_addr),
    m_term_num(term_num),
    m_primary_crt(false),
    m_assoc_kb_addr(-1),
    m_RefreshTimer(nullptr),
    m_QSecTimer(nullptr),
    m_blink_phase(0),
    m_fps(0)
{
    const bool smart_term = (crt_state->screen_type == UI_SCREEN_2236DE);
    m_primary_crt = (smart_term) ? ((m_crt_addr == 0x00) && (term_num == 0))
                                 : (m_crt_addr == 0x05);

    if (m_primary_crt) {
        assert(!m_primaryFrame);
        m_primaryFrame = this;
    }

    // set the frame icon
    SetIcon(&wang_xpm[0]);

    makeMenubar(isPrimaryCrt(), smart_term);

    // create a status bar with two panes
    m_statBar = new CrtStatusBar(this, smart_term, isPrimaryCrt());
    SetStatusBar(m_statBar);
    SetStatusBarPane(1);        // use second pane for menu help strings

    // create toolbar
#if 0
    const long tb_style = wxNO_BORDER | wxHORIZONTAL | wxTB_FLAT | wxTB_TEXT
                        | wxTB_NOICONS
#else
    const long tb_style = wxNO_BORDER | wxHORIZONTAL | wxTB_FLAT;
#endif
            ;
    m_toolBar = CreateToolBar(tb_style, TB_TOOLBAR);
    initToolBar(m_toolBar);
    m_toolBar->Show(false); // can get changed in GetDefaults()

    m_crt = new Crt(this, crt_state);

    getDefaults();      // get configuration options, or supply defaults
#if 1
// FIXME: hack -- m_assoc_kb_addr defaults to 01, so if we attempt to
//        route a key to a Terminal (which registers at registersKB at 0x00)
//        it fails to find it.  so hack around it for now.
if (smart_term) {
    m_assoc_kb_addr = 0x00;
}
#endif

    // if I don't do this before ShowFullScreen, bad things happen when
    // switching later from fullscreen to !fullscreen in some circumstances
    // wxMSW, wx2.5.2
    Show(true);

#ifndef __WXMAC__
    ShowFullScreen(m_fullscreen, FULLSCREEN_FLAGS);
#endif

    // track screen refresh rate, for kicks
    m_fps = 0;

    // only the primary has a status bar
    m_RefreshTimer = new wxTimer(this, Timer_Frame);
    m_QSecTimer    = new wxTimer(this, Timer_QSec);

    // it is hard to predict what the optimal refresh period
    // for a given system
    m_RefreshTimer->Start(30, wxTIMER_CONTINUOUS);   // ~30 fps
    m_QSecTimer->Start(250, wxTIMER_CONTINUOUS);     // 4 Hz
}


// destructor
CrtFrame::~CrtFrame()
{
    m_RefreshTimer->Stop();
    m_QSecTimer->Stop();
    wxDELETE(m_RefreshTimer);
    wxDELETE(m_QSecTimer);
}


// indicate if this is device 005 or not
bool
CrtFrame::isPrimaryCrt() const
{
    return m_primary_crt;
}


// create menubar
#ifdef __WXMAC__
    #define ALT  "Ctrl"         /* this gets remapped to Cmd */
    #define ALT2 "Shift-Ctrl"   /* this gets remapped to Shift-Cmd */
#else
    #define ALT  "Alt"
    #define ALT2 "Shift-Alt"
#endif

void
CrtFrame::makeMenubar(bool primary_crt, bool smart_term)
{
    wxMenu *menuFile = new wxMenu;
    if (primary_crt) {
        menuFile->Append(File_Script,   "&Script...", "Redirect keyboard from a file");
    }
    menuFile->Append(File_Snapshot, "Screen &Grab...\t" ALT "+G", "Save an image of the screen to a file");
#if HAVE_FILE_DUMP
    if (primary_crt) {
        menuFile->Append(File_Dump,     "Dump Memory...", "Save an image of the system memory to a file");
    }
#endif
    menuFile->Append(File_Quit,     "E&xit\t" ALT "+X", "Quit the program");

    wxMenu *menuCPU = nullptr;
    if (primary_crt) {
        menuCPU = new wxMenu;
        menuCPU->Append(CPU_HardReset, "Hard Reset CPU\t" ALT2 "+R", "Perform a power-up reset");
        menuCPU->Append(CPU_WarmReset, "Warm Reset CPU\t" ALT2 "+W", "Perform a state-preserving reset");
        menuCPU->AppendSeparator();
        menuCPU->Append(CPU_ActualSpeed,      "&Actual Speed",      "Run emulation at speed of the actual machine", wxITEM_CHECK);
        menuCPU->Append(CPU_UnregulatedSpeed, "&Unregulated Speed", "Run emulation at maximum speed", wxITEM_CHECK);
    }

    wxMenu *menuDisk = nullptr;
    if (primary_crt) {
        // nothing to do except add top -- it is added dynamically later
        menuDisk = new wxMenu;
    }

    // printer view
    wxMenu *menuPrinter = nullptr;
    if (primary_crt && (System2200::getPrinterIoAddr(0) >= 0)) {
        // there is at least one printer
        menuPrinter = new wxMenu;
        for(int i=0; ;i++) {
            const int io_addr = System2200::getPrinterIoAddr(i);
            if (io_addr < 0) {
                break;
            }
            wxString label;
            wxString help;
            label.Printf("Show Printer /%03X", io_addr);
            help.Printf("Show view for printer /%03X", io_addr);
            menuPrinter->Append(Printer_0+i, label, help);
        }
        menuPrinter->Append(Print_PrintAndClear, "Print and Clear All",   "Print and clear all printer logs");
    }

    wxMenu *menuConfig = new wxMenu;
    if (primary_crt) {
        menuConfig->Append(Configure_Dialog,     "&Configure System...",      "Change I/O settings");
    }
    menuConfig->Append(Configure_Screen_Dialog,  "&Configure Screen...",      "Change display settings");
    if (smart_term) {
        menuConfig->Append(Configure_KeywordMode,    "&Kaps lock\t" ALT "+K",  "Toggle keyboard keyword mode",        wxITEM_CHECK);
    } else {
        menuConfig->Append(Configure_KeywordMode,    "&Keyword mode\t" ALT "+K",  "Toggle keyboard keyword mode",        wxITEM_CHECK);
    }
    menuConfig->Append(Configure_SF_toolBar,     "SF key toolbar",            "Toggle special function key toolbar", wxITEM_CHECK);
    menuConfig->Append(Configure_Fullscreen,     "Fullscreen\t" ALT "+Enter", "Toggle full screen display",          wxITEM_CHECK);
    if (primary_crt) {
        menuConfig->Append(Configure_Stats,      "Statistics",                "Toggle statistics on statusbar",      wxITEM_CHECK);
    }
    if (System2200::getKbIoAddr(1) >= 0) {
        // there is more than one keyboard
        menuConfig->AppendSeparator();
        for(int i=0; ;i++) {
            const int addr = System2200::getKbIoAddr(i);
            if (addr < 0) {
                break;
            }
            wxString label;
            wxString help;
            label.Printf("Tie keyboard to /%03X", addr);
            help.Printf("Tie keyboard to IO device /%03X", addr);
            menuConfig->Append(Configure_KB_Tie0+i, label, help, wxITEM_CHECK);
        }
    }

    // make the help menu (as if it isn't obvious below!)
    wxMenu *menuHelp = TheApp::makeHelpMenu();

    // now append the freshly created menu to the menu bar...
    m_menuBar = new wxMenuBar;

    m_menuBar->Append(menuFile, "&File");
    if (menuCPU != nullptr) {
        m_menuBar->Append(menuCPU, "C&PU");
    }
    if (menuDisk != nullptr) {
        m_menuBar->Append(menuDisk, "&Disk");
    }
    if (menuPrinter != nullptr) {
        m_menuBar->Append(menuPrinter, "&Printer");
    }
    m_menuBar->Append(menuConfig, "&Configure");
    m_menuBar->Append(menuHelp, "&Help");

    // ... and attach this menu bar to the frame
    SetMenuBar(m_menuBar);
}


// this is called just before a menu is displayed.
// set the check status for each of the menu items.
// also dynamically disables/enables menu items,
void
CrtFrame::setMenuChecks(const wxMenu *menu)
{
    // ----- file --------------------------------------
    if (isPrimaryCrt()) {
        const bool script_running = System2200::kb_scriptModeActive(m_assoc_kb_addr, m_term_num);
        m_menuBar->Enable(File_Script, !script_running);
    }

    // ----- cpu ---------------------------------------
    if (isPrimaryCrt()) {
        const bool regulated = System2200::isCpuSpeedRegulated();
        m_menuBar->Check( CPU_ActualSpeed,       regulated );
        m_menuBar->Check( CPU_UnregulatedSpeed, !regulated );
    }

    // ----- disk --------------------------------------
    // dynamically generate the menu each time.
    // we qualify this one and regenerate it only if we must.
    int DiskMenuPos = m_menuBar->FindMenu("Disk");
    if (isPrimaryCrt() && (DiskMenuPos >= 0)
        && (menu == m_menuBar->GetMenu(DiskMenuPos)) ) {
        wxMenu *diskmenu = m_menuBar->GetMenu(DiskMenuPos);
        const int items = diskmenu->GetMenuItemCount();

        // the entire Disk menu used to be recreated and replaced each time,
        // but that caused problems on wxMAC, so now instead all the menu
        // items get removed and replaced each time.
        for(int i=items-1; i>=0; i--) {
            wxMenuItem *item = diskmenu->FindItemByPosition(i);
            diskmenu->Delete(item);
        }

        // see if there are any disk controllers
        for(int controller=0; ; controller++) {
            int slot, io_addr;
            if (!System2200::findDiskController(controller, &slot)) {
                break;
            }
            bool ok = System2200::getSlotInfo(slot, nullptr, &io_addr);
            assert(ok); ok=ok;
            for(int d=0; d<2; d++) {
                const int stat = IoCardDisk::wvdDriveStatus(slot, d);
                if (stat & IoCardDisk::WVD_STAT_DRIVE_OCCUPIED) {
                    wxString str1, str2;
                    str1.Printf("Drive %c/%03X: Remove", d?'R':'F', io_addr);
                    str2.Printf("Remove the disk from drive %d, unit /%03X", d, io_addr);
                    diskmenu->Append(Disk_Remove+4*slot+2*d, str1, str2, wxITEM_CHECK);
                } else {
                    wxString str1, str2;
                    str1.Printf("Drive %c/%03X: Insert", d?'R':'F', io_addr);
                    str2.Printf("Insert a disk into drive %d, unit /%03X", d, io_addr);
                    diskmenu->Append(Disk_Insert+4*slot+2*d, str1, str2, wxITEM_CHECK);
                }
            }
            diskmenu->AppendSeparator();
        }
        diskmenu->Append(Disk_New,     "&New Disk...",     "Create virtual disk");
        diskmenu->Append(Disk_Inspect, "&Inspect Disk...", "Inspect/modify virtual disk");
        diskmenu->Append(Disk_Format,  "&Format Disk...",  "Format existing virtual disk");
    }

    // ----- configure ---------------------------------
    int ConfigMenuPos = m_menuBar->FindMenu("Configure");
    if (menu == m_menuBar->GetMenu(ConfigMenuPos)) {
        m_menuBar->Check( Configure_KeywordMode, getKeywordMode() );
        m_menuBar->Check( Configure_SF_toolBar,  m_toolBar->IsShown() );
        if (isPrimaryCrt()) {
            m_menuBar->Check( Configure_Stats,   getShowStatistics() );
        }
        if (System2200::getKbIoAddr(1) >= 0) {
            // there is more than one keyboard
            for(int i=0; ;i++) {
                const int addr = System2200::getKbIoAddr(i);
                if (addr < 0) {
                    break;
                }
                m_menuBar->Check( Configure_KB_Tie0+i, (m_assoc_kb_addr == addr) );
            }
        }
    }
}


// create the 16 SF keys and the EDIT key on the toolbar
void
CrtFrame::initToolBar(wxToolBar *tb)
{
#if SFKEY_TINY_STYLE
    wxBitmap img(sfkey_xpm);
    int w = img.GetWidth();
    int h = img.GetHeight();
    tb->SetToolBitmapSize(wxSize(w,h));

    for(int i=0; i<17; i++) {
        wxString label, tooltip;
        if (i < 16) {
            label.Printf("SF%d", i);
            tooltip.Printf("Special Function key %d", i);
        } else {
            tb->AddSeparator();
            label = "EDIT";
            tooltip = "EDIT key";
        }
        tb->AddTool(TB_SF0+i, label, img, tooltip);
#ifdef __WXMAC__
        if (i==3 || i==7 || i==11) {
            tb->AddSeparator();
        }
#endif
    }

#else  // !SFKEY_TINY_STYLE

#ifdef __WXMAC__
    // as of wxWidgets 2.5.5 at least, toolbar icons must be <=32 pixels wide
    // or they must be exactly 48 pixels (and maybe 128) pixels wide otherwise
    // something forces the icon to shrink and the results aren't pretty.
    // this is combatted two ways.  first, shorter strings are used; second,
    // we keep trying smaller fonts until one meets the requirements.
    for(int font_size=14; font_size>=8; font_size--) {
#else
    const int font_size = 8;
#endif

    wxFont key_font(font_size, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    assert(key_font != wxNullFont);
    //key_font.SetNoAntiAliasing();

    wxMemoryDC memDC;
    memDC.SetFont(key_font);
    wxBitmap tmpbm(1,1);
    memDC.SelectObject(tmpbm); // wxmac requires it even before GetTextExtent()
    wxCoord textH, textW;
    memDC.GetTextExtent("SF15", &textW, &textH); // widest string in use
#if BIG_BUTTONS
    static const std::string sf_labels[17] = {
        "", "", "", "", // SF0-3
        "", "", "", "", // SF4-7
#ifdef __WXMAC__
        "Erase",        // SF8
        "Del",          // SF9
        "Ins",          // SF10
        "---->",        // SF11
        "->",           // SF12
        "<-",           // SF13
        "<----",        // SF14
        "Rcl",          // SF15
#else
                        // SF0-3 pc   mac  mac  mac
                        // SF4-7 8pt  12pt 11pt 10pt
        "Erase",        // SF8   27   32   29   27
        "Delete",       // SF9   31   38   35   32
        "Insert",       // SF10  26   33   31   28
        "---->",        // SF11  18   27   25   22
        "->",           // SF12   9   13   12   11
        "<-",           // SF13   9   13   12   11
        "<----",        // SF14  18   27   25   22
        "Recall",       // SF15  30   33   31   28
#endif
        "",             // EDIT
    };

    // see if any of the labels is wider than the SFxx string
    for(int ii=0; ii<17; ii++) {
        int width, height;
        memDC.GetTextExtent(sf_labels[ii], &width, &height);
        if (width > textW) {
            textW = width;
        }
        if (height > textH) {
            textH = height;
        }
    }
    const int buttonH(2*textH);
#else // !BIG_BUTTONS
    const int buttonH(textH);
#endif
    const int buttonW(textW);
#ifdef __WXMAC__
    if (buttonW > 32) {
        continue;       // try next smaller font size
    }
#endif

    tb->SetToolBitmapSize(wxSize(buttonW,buttonH));

    wxColor fg, bg;
    fg = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT);
    bg = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);

    wxBitmap img(buttonW, buttonH, -1);
    wxPen fgPen(fg, 1, wxPENSTYLE_SOLID);
    wxPen bgPen(bg, 1, wxPENSTYLE_SOLID);

    memDC.SelectObject(img);
    memDC.SetBrush(wxBrush(bg, wxBRUSHSTYLE_SOLID));
    memDC.SetBackgroundMode(wxSOLID);
    memDC.SetTextForeground(fg);
    memDC.SetTextBackground(bg);
    memDC.SelectObject(wxNullBitmap);

    for(int i=0; i<17; i++) {
        wxString label, tooltip;
        if (i < 16) {
            label.Printf("SF%d", i);
            tooltip.Printf("Special Function key %d", i);
        } else {
            tb->AddSeparator();
            label = "EDIT";
            tooltip = "EDIT key";
        }

        // print a horizontally centered label on the button bitmap
        m_sfkeyIcons[i] = wxBitmap(buttonW, buttonH, -1);
        memDC.SelectObject(m_sfkeyIcons[i]);
        memDC.SetPen(bgPen);
        memDC.DrawRectangle(0,0, buttonW, buttonH); // clear it

        memDC.GetTextExtent(label, &textW, &textH);
        int btnOrigX((buttonW - textW)>>1);
#if BIG_BUTTONS
        memDC.DrawText(label, btnOrigX, textH);
        memDC.GetTextExtent(sf_labels[i], &textW, &textH);
        btnOrigX = (buttonW - textW) >> 1;

    #if GRAPHIC_ARROWS
        int shaft_ticks;        // number of separators
        int arrow_dir;          // arrow direction
        switch (i) {
            case 11: // ---->
                shaft_ticks = 4;
                arrow_dir = +1;
                break;
            case 12: // ->
                shaft_ticks = 1;
                arrow_dir = +1;
                break;
            case 13: // <-
                shaft_ticks = 1;
                arrow_dir = -1;
                break;
            case 14: // <----
                shaft_ticks = 4;
                arrow_dir = -1;
                break;
            default:
                shaft_ticks = 0;
                arrow_dir   = 0;
                break;
        }
        if (shaft_ticks > 0) {
            wxPen dashPen(fg, 1, wxPENSTYLE_SOLID);
            const wxDash dashes[] = { 4, 2 };
            int shaft_len = buttonW/5;
            if (shaft_ticks > 1) {
#if __WXMSW__
                // the USER_DASH style doesn't seem to work as I'd expect
                // (as of wxWidgets 2.6.0)
                dashPen.SetStyle(wxPENSTYLE_USER_DASH);
                dashPen.SetDashes(2, &dashes[0]);
#endif
                // four dashes, three spaces
                shaft_len = (shaft_ticks  )*dashes[0]
                          + (shaft_ticks-1)*dashes[1];
            }

            const int shaft_y       = textH/2;
            const int shaft_beg_x   = buttonW/2   - (arrow_dir * shaft_len)/2;
            const int shaft_end_x   = shaft_beg_x + (arrow_dir * shaft_len);
            const int arrow_delta_x = -arrow_dir * dashes[0];
            const int arrow_delta_y =              dashes[0]; // make it 45 degrees

            // draw shaft
            memDC.SetPen(dashPen);
            memDC.DrawLine(shaft_beg_x, shaft_y, shaft_end_x, shaft_y);

            // draw arrowhead
            memDC.SetPen(fgPen);
            memDC.DrawLine(shaft_end_x, shaft_y,
                           shaft_end_x + arrow_delta_x,
                           shaft_y + arrow_delta_y);
            memDC.DrawLine(shaft_end_x, shaft_y,
                           shaft_end_x + arrow_delta_x,
                           shaft_y - arrow_delta_y);
        } else
    #endif
        {
            memDC.DrawText(sf_labels[i], btnOrigX, 0);
        }
#else
        memDC.DrawText(label, btnOrigX, 0);
#endif

        tb->AddTool(TB_SF0+i, label, m_sfkeyIcons[i], tooltip);
        memDC.SelectObject(wxNullBitmap);
    }
    #ifdef __WXMAC__
        break;  // we found a font size that works
    } // for(font_size)
    #endif
#endif // !SFKEY_TINY_STYLE

    tb->Realize();
}


// save Crt options to the config file
void
CrtFrame::saveDefaults()
{
    std::ostringstream sg;
    sg << "ui/CRT-" << std::setw(2) << std::setfill('0') << std::hex << m_crt_addr;
    std::string subgroup(sg.str());

    // save screen color
    Host::ConfigWriteInt(subgroup, "colorscheme", getDisplayColorScheme());

    // save font choice
    Host::ConfigWriteInt(subgroup, "fontsize",  m_fontsize[0]);
    Host::ConfigWriteInt(subgroup, "fontsize2", m_fontsize[1]);

    // save contrast/brightness
    Host::ConfigWriteInt(subgroup, "contrast",   m_crt->getDisplayContrast() );
    Host::ConfigWriteInt(subgroup, "brightness", m_crt->getDisplayBrightness() );

    // save keyword mode
    Host::ConfigWriteBool(subgroup, "keywordmode", getKeywordMode() );

    // save tied keyboard io address
    std::ostringstream tfoo;
    tfoo << "0x" << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << m_assoc_kb_addr;
    std::string foo(tfoo.str());
    Host::ConfigWriteStr(subgroup, "tied_keyboard", foo);

    // save position and size
    if (!m_fullscreen) {
        Host::ConfigWriteWinGeom(this, subgroup);
    }

    // save statistics display mode
    Host::ConfigWriteBool(subgroup, "timingstats", getShowStatistics() );

    // save toolbar status
    Host::ConfigWriteBool(subgroup, "toolbar", m_toolBar->IsShown());

    // save fullscreen status
    Host::ConfigWriteBool(subgroup, "fullscreen", m_fullscreen);
}


// get Crt options from the config file, supplying reasonable defaults
void
CrtFrame::getDefaults()
{
    wxString valstr;
    int v = 0;
    bool b;

    // pick up screen color scheme
    std::ostringstream sg;
    sg << "ui/CRT-" << std::setw(2) << std::setfill('0') << std::hex << m_crt_addr;
    std::string subgroup(sg.str());

    // pick up keyword mode (A/a vs Keyword/A)
    Host::ConfigReadBool(subgroup, "keywordmode", &b, false);
    setKeywordMode(b);

    // pick up tied keyboard io address
    b = Host::ConfigReadInt(subgroup, "tied_keyboard", &v);
    if (b && (v >= 0x00) && (v <= 0xFF)) {
        m_assoc_kb_addr = v;
    } else {
        m_assoc_kb_addr = 0x01; // default
    }
    // make sure that old mapping still makes sense
    int found = 0;
// FIXME: why 10?  why not NUM_IOSLOTS?
    for(int i=0; i<10; i++) {
        if (System2200::getKbIoAddr(i) == m_assoc_kb_addr) {
            found = 1;
            break;
        }
    }
    if (!found) {
        m_assoc_kb_addr = 0x01; // old mapping doesn't exist; use default
    }

    // pick up statistics display mode
    bool showstats;
    Host::ConfigReadBool(subgroup, "timingstats", &showstats, false );
    setShowStatistics(showstats);

    // save toolbar status
    bool show_toolbar;
    Host::ConfigReadBool(subgroup, "toolbar", &show_toolbar, false );
    m_toolBar->Show(show_toolbar);

    // pick up screen location and size
    wxRect default_geom(50,50,690,380);
    Host::ConfigReadWinGeom(this, subgroup, &default_geom);

    // pick up fullscreen status
    Host::ConfigReadBool(subgroup, "fullscreen", &m_fullscreen, false);

    // this must be done before changing the color scheme
    Host::ConfigReadInt(subgroup, "contrast", &v, 100 );
    m_crt->setDisplayContrast(v);
    Host::ConfigReadInt(subgroup, "brightness", &v, 0 );
    m_crt->setDisplayBrightness(v);

    (void)Host::ConfigReadInt(subgroup, "colorscheme", &v, 0);
    if ((v >= 0) && (v < num_colorschemes)) {
        setDisplayColorScheme(v);
    } else {
        setDisplayColorScheme(0);
    }

    // pick up screen font size
    m_fontsize[0] = m_fontsize[1] = 2; // default
    b = Host::ConfigReadInt(subgroup, "fontsize", &v);
    if (b && ((v >=1 && v <= 3) || (v >= 8 && v <= 28))) {
        m_fontsize[0] = v;
    }
    (void)Host::ConfigReadInt(subgroup, "fontsize2", &v);
    if (b && ((v >=1 && v <= 3) || (v >= 8 && v <= 28))) {
        m_fontsize[1] = v;
    }

    m_crt->setFontSize(m_fontsize[m_fullscreen]);
}


// make Crt the focus of further keyboard events
void
CrtFrame::refocus()
{
    m_crt->SetFocus();
}


// set simulation time for informative display
void
CrtFrame::setSimSeconds(int secs, float relative_speed)
{
    CrtFrame *pf = getPrimaryFrame();
    if (pf == nullptr) {
        return;
    }

    wxString str;
#if 0
    // too nerdy?
    wxString format = (relative_speed >= 10.0f) ?
                      "Sim time: %d seconds, %3.0fx, %d fps"
                    : "Sim time: %d seconds, %3.1fx, %d fps";
    str.Printf( format, secs, relative_speed, pf->m_fps );
#else
    wxString format = (relative_speed >= 10.0f) ?
                      "Sim time: %d seconds, %3.0fx"
                    : "Sim time: %d seconds, %3.1fx";
    str.Printf( format, secs, relative_speed );
#endif
    if (pf->getShowStatistics()) {
        pf->m_statBar->SetStatusMessage(std::string(str));
    } else {
        pf->m_statBar->SetStatusMessage("");
    }
}


// 2336: there is 2b counter
//        text   cursor
//   00:  norm     on
//   01:  bright   on
//   10:  norm     on
//   11:  bright   off
bool
CrtFrame::getTextBlinkPhase() const
{
    return (m_blink_phase & 1) == 1;
}

bool
CrtFrame::getCursorBlinkPhase() const
{
    // I believe the 2236 had a 50% duty cycle,
    // but the 2336 definitely has a 75% duty cycle
    return (m_blink_phase < 3);
}

// create a bell (0x07) sound
void
CrtFrame::ding()
{
    m_crt->ding();
}

// ----------------------------------------------------------------------------
// event handlers
// ----------------------------------------------------------------------------

// tell the emulator to accept keystrokes from a file
void
CrtFrame::OnScript(wxCommandEvent& WXUNUSED(event))
{
    std::string fullpath;
    const int r = Host::fileReq(Host::FILEREQ_SCRIPT, "Script to execute", 1, &fullpath);
    if (r == Host::FILEREQ_OK) {
        // tell the core emulator to redirect input for a while
        System2200::kb_invokeScript(m_assoc_kb_addr, m_term_num, fullpath);
    }
}


// do a screen capture to a named filed
void
CrtFrame::OnSnapshot(wxCommandEvent& WXUNUSED(event))
{
    // get the name of a file to execute
    std::string fullpath;

    const int r = Host::fileReq(Host::FILEREQ_GRAB, "Filename of image", 0, &fullpath);
    if (r == Host::FILEREQ_OK) {
        wxBitmap* bitmap = m_crt->grabScreen();
        assert(bitmap != nullptr);
        bitmap->SaveFile(wxString(fullpath), wxBITMAP_TYPE_BMP);
    }
}


#if HAVE_FILE_DUMP
// do a screen capture to a named filed
void
CrtFrame::OnDump(wxCommandEvent& WXUNUSED(event))
{
    // get the name of a file to execute
    std::string fullpath;
    int r = Host::fileReq(Host::FILEREQ_GRAB, "Name of file to save to", 0, &fullpath);

    if (r == Host::FILEREQ_OK) {
        dump_ram(fullpath);
    }
}
#endif


// called when File/Exit is selected
void
CrtFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    System2200::terminate(); // shut down all windows and exit
}


void
CrtFrame::OnReset(wxCommandEvent &event)
{
    switch (event.GetId()) {
        default:
            assert(false);
        case CPU_HardReset:
            System2200::reset(true);  // hard reset
            break;
        case CPU_WarmReset:
            // route it through the keyboard handler because the MXD
            // filters out resets which aren't from terminal #1
            System2200::kb_keystroke(getTiedAddr(), m_term_num, IoCardKeyboard::KEYCODE_RESET);
            break;
    }
}


void
CrtFrame::OnCpuSpeed(wxCommandEvent &event)
{
    System2200::regulateCpuSpeed( (event.GetId() == CPU_ActualSpeed) );
}


void
CrtFrame::OnDiskFactory(wxCommandEvent &event)
{
    std::string filename("");
    if (event.GetId() == Disk_Inspect) {
        if (Host::fileReq(Host::FILEREQ_DISK, "Virtual Disk Name", 1, &filename) !=
                          Host::FILEREQ_OK) {
            return;     // canceled
        }
    }

    doInspect(filename);
}


// inspect the named disk.  if it is mounted in a drive, disconnect the
// filehandle before performing the operation so that when the emulator
// resumes, it will be forced to reopen the file, picking up any changes
// made to the disk metadata.
void
CrtFrame::doInspect(const std::string &filename)
{
    System2200::freezeEmu(true);    // halt emulation

    int slot, drive;
    const bool in_use = System2200::findDisk(filename, &slot, &drive, nullptr);
    if (in_use) {
        // close filehandles to the specified drive
        IoCardDisk::wvdFlush(slot, drive);
    }

    DiskFactory *factory = new DiskFactory(this, filename);
    factory->ShowModal();

    System2200::freezeEmu(false);   // run emulation
}


void
CrtFrame::OnDiskFormat(wxCommandEvent& WXUNUSED(event))
{
    std::string filename;
    if (Host::fileReq(Host::FILEREQ_DISK, "Virtual Disk Name", 1, &filename) !=
                      Host::FILEREQ_OK) {
        return; // cancelled
    }

    doFormat(filename);
}


void
CrtFrame::doFormat(const std::string &filename)
{
    System2200::freezeEmu(true);    // halt emulation

    bool wp;
    bool ok = IoCardDisk::wvdGetWriteProtect(filename, &wp);
    if (ok) {
        int slot, drive, io_addr;
        const bool in_use = System2200::findDisk(filename, &slot, &drive, &io_addr);

        wxString prompt = "";
        if (in_use) {
            prompt = wxString::Format("Warning: this disk is in use at /%03X, drive %d.\n\n",
                                        io_addr, drive);
        }
        if (wp) {
            prompt += "Warning: write protected disk!\n\n";
        }

        prompt += "Formatting will lose all disk contents.\n"
                  "Do you really want me to format the disk?";

        if (UI_Confirm(prompt.c_str())) {
            if (in_use) {
                // close filehandles to the specified drive
                IoCardDisk::wvdFlush(slot, drive);
            }
            ok = IoCardDisk::wvdFormatFile(filename);
        }
    }

    if (!ok) {
        UI_Error("Error: operation failed");
    }

    System2200::freezeEmu(false);   // run emulation
}


void
CrtFrame::OnDisk(wxCommandEvent &event)
{
    // each controller manages two drives, each has three possible actions
    const int menu_id = event.GetId();
    const int slot  =  (menu_id - Disk_Insert) / 4;
    const int drive = ((menu_id - Disk_Insert) % 4) / 2;
    const int type  =  (menu_id - Disk_Insert) % 2;
    // UI_Info("Got disk menu: slot=%d, drive=%d, action=%d", slot, drive, type);

    int ok = true;
    switch (type) {

        case 0: // insert disk
        {   std::string fullpath;
            if (Host::fileReq(Host::FILEREQ_DISK, "Disk to load", 1, &fullpath) ==
                              Host::FILEREQ_OK) {
                int drive2, io_addr2;
                const bool b = System2200::findDisk(fullpath, nullptr, &drive2, &io_addr2);
                if (b) {
                    UI_Warn("Disk already in drive %c /%03x", "FC"[drive2], io_addr2);
                    return;
                } else {
                    ok = IoCardDisk::wvdInsertDisk(slot, drive, fullpath);
                }
            }
        }   break;

        case 1: // remove disk
            ok = IoCardDisk::wvdRemoveDisk(slot, drive);
            break;

#if 0
        case 2: // format disk
            if (UI_Confirm("Do you really want me to format the disk in drive %d?", drive)) {
                ok = IoCardDisk::wvd_format(slot, drive);
            }
            break;
#endif

        default:
            ok = false;
            assert(false);
            break;
    }

    if (!ok) {
        UI_Error("Error: operation failed");
    }
}


void
CrtFrame::OnDisplayFullscreen(wxCommandEvent& WXUNUSED(event))
{
    m_fullscreen = !m_fullscreen;
    ShowFullScreen(m_fullscreen, FULLSCREEN_FLAGS);
    m_crt->setFontSize(m_fontsize[m_fullscreen]);
}


// called when the window is manually closed ("X" button, or sys menu)
void
CrtFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
    System2200::freezeEmu(true);
    System2200::terminate(); // shut down all windows and exit
}


// update all displays
void
CrtFrame::OnTimer(wxTimerEvent &event)
{
    if (event.GetId() == Timer_Frame) {
        m_crt->refreshWindow(); // ask screen to update
    } else if (event.GetId() == Timer_QSec) {
        // count frames each second to display FPS figure
        m_blink_phase = (m_blink_phase == 3) ? 0 : (m_blink_phase+1);
        if (m_blink_phase == 0) {
            m_fps = m_crt->getFrameCount();
            m_crt->setFrameCount(0);
        }
        // there might be blinking text or blinking cursor
        m_crt->setDirty();
    }
}

void
CrtFrame::OnConfigureDialog(wxCommandEvent& WXUNUSED(event))
{
    System2200::reconfigure();
}

void
CrtFrame::OnConfigureScreenDialog(wxCommandEvent& WXUNUSED(event))
{
    wxString title;
    title.Printf( "Display /%03X Configuration", m_crt_addr);

    System2200::freezeEmu(true);    // halt emulation

    CrtConfigDlg dlg(this, title);
    (void)dlg.ShowModal();

    System2200::freezeEmu(false);   // run emulation
}


void
CrtFrame::OnConfigureKeywordMode(wxCommandEvent& WXUNUSED(event))
{
    const bool state = m_statBar->getKeywordMode();
    m_statBar->setKeywordMode(!state);
}


void
CrtFrame::OnConfigureSfToolbar(wxCommandEvent& WXUNUSED(event))
{
    const bool state = m_toolBar->IsShown();
    m_toolBar->Show(!state);
    SendSizeEvent();
}


void
CrtFrame::OnConfigureStats(wxCommandEvent& WXUNUSED(event))
{
    if (isPrimaryCrt()) {
        const bool showing = getShowStatistics();
        setShowStatistics(!showing);
    }
}


void
CrtFrame::OnConfigureKbTie(wxCommandEvent &event)
{
    const int id = event.GetId();
    assert( (id >= Configure_KB_Tie0) && (id <= Configure_KB_TieN) );

    const int idx = id - Configure_KB_Tie0;
    const int new_addr = System2200::getKbIoAddr(idx);
    assert(new_addr >= 0);

    m_assoc_kb_addr = new_addr;
}


void
CrtFrame::OnPrinter(wxCommandEvent &event)
{
    const int id = event.GetId();
    assert( (id >= Printer_0) && (id <= Printer_N) );

    // map chosen device to an I/O address
    const int idx = id - Printer_0;
    const int io_addr = System2200::getPrinterIoAddr(idx);
    IoCard *inst = System2200::getInstFromIoAddr(io_addr);
    assert(inst != nullptr);

    // get the printer controller card handle
    IoCardPrinter *card = dynamic_cast<IoCardPrinter*>(inst);
    assert(card != nullptr);
    PrinterFrame *prtwnd = card->getGuiPtr();
    assert(prtwnd != nullptr);

    prtwnd->Show(true);
    prtwnd->Raise();
}

// print all printer contents, and then clear all printers
void
CrtFrame::OnPrintAndClear(wxCommandEvent& WXUNUSED(event))
{
    // loop through each printer and ask it to print and clear its contents.
    // the clear should only be invoked if the print was successful,
    // otherwise a warning message should be displayed.
    if (System2200::getPrinterIoAddr(0) >= 0) {

        // there is at least one printer
        for(int i=0; ;i++) {
            const int io_addr = System2200::getPrinterIoAddr(i);
            if (io_addr < 0) {
                break; // no more printers
            }

            // map device I/O address to card handle
            IoCard *inst = System2200::getInstFromIoAddr(io_addr);
            assert(inst != nullptr);
            IoCardPrinter *card = dynamic_cast<IoCardPrinter*>(inst);
            assert(card != nullptr);

            // fetch associated gui window pointer and use it
            PrinterFrame *prtwnd = card->getGuiPtr();
            assert(prtwnd != nullptr);
            prtwnd->printAndClear();
        }
    }
}


// print all printer contents, and then clear all printers
void
CrtFrame::OnToolBarButton(wxCommandEvent &event)
{
    const int id = event.GetId();
    const bool shift = ::wxGetKeyState(WXK_SHIFT);

    const int sf = IoCardKeyboard::KEYCODE_SF;
    const int keycode = (id == TB_EDIT) ? (sf | IoCardKeyboard::KEYCODE_EDIT)
                      : (shift)         ? (sf | (id - TB_SF0 + 16))
                                        : (sf | (id - TB_SF0));

    System2200::kb_keystroke(getTiedAddr(), m_term_num, keycode);
}


void
CrtFrame::OnMenuOpen(wxMenuEvent &event)
{
    setMenuChecks(event.GetMenu());
}


// -------- allow discovery of possible font styles --------

int
CrtFrame::getNumFonts()
{
    return num_fonts;
}

// allow discovery of allowed values
// as idx ranges from 0 to n, return the font size constant.
int
CrtFrame::getFontNumber(int idx)
{
    assert(idx >= 0 && idx < num_fonts);
    return font_table[idx].size;
}

// as idx ranges from 0 to n, return the font name string.
std::string
CrtFrame::getFontName(int idx)
{
    assert(idx >= 0 && idx < num_fonts);
    return std::string(font_table[idx].name);
}

// -------- allow discovery of possible color schemes --------

int
CrtFrame::getNumColorSchemes()
{
    return num_colorschemes;
}

// as idx ranges from 0 to n, return the font name string.
std::string
CrtFrame::getColorSchemeName(int idx)
{
    assert(idx >= 0 && idx < num_colorschemes);
    return colorscheme[idx].menuHelp;
}

// -------- Crt display set/get --------

void
CrtFrame::setFontSize(int size)
{
    m_fontsize[m_fullscreen] = size;
    // pass it through
    m_crt->setFontSize(size);
}

int
CrtFrame::getFontSize() const
{
    return m_fontsize[m_fullscreen];
}


void
CrtFrame::setDisplayColorScheme(int n)
{
    assert( n >= 0 );
    assert( n <  num_colorschemes );

    wxColor FG = wxColor(colorscheme[n].fg_r, colorscheme[n].fg_g, colorscheme[n].fg_b);
    wxColor BG = wxColor(colorscheme[n].bg_r, colorscheme[n].bg_g, colorscheme[n].bg_b);
    m_crt->setColor(FG, BG);
    // this is required if we are using deep font bitmaps to store the fontmap
    m_crt->setFontSize(m_fontsize[m_fullscreen]);
    m_colorsel = n;
}

int
CrtFrame::getDisplayColorScheme() const
{
    return m_colorsel;
}


void
CrtFrame::setDisplayContrast(int n)
{
    m_crt->setDisplayContrast(n);
}

int
CrtFrame::getDisplayContrast() const
{
    return m_crt->getDisplayContrast();
}

void
CrtFrame::setDisplayBrightness(int n)
{
    m_crt->setDisplayBrightness(n);
}

int
CrtFrame::getDisplayBrightness() const
{
    return m_crt->getDisplayBrightness();
}


void
CrtFrame::setShowStatistics(bool show)
{
    m_showstats = show;
    CrtFrame *pf = getPrimaryFrame();
    if ((pf != nullptr) && isPrimaryCrt()) {
        if (getShowStatistics()) {
            pf->m_statBar->SetStatusMessage("(Performance statistics will appear here)");
        } else {
            pf->m_statBar->SetStatusMessage("");
        }
    }
}

bool
CrtFrame::getShowStatistics() const
{
    return m_showstats;
}

// set the keyword state from the statbar
void
CrtFrame::setKeywordMode(bool b)
{
    m_statBar->setKeywordMode(b);
}

bool
CrtFrame::getKeywordMode() const
{
    return m_statBar->getKeywordMode();
}


// the io address of the emulated keyboard associated with this window
int
CrtFrame::getTiedAddr() const
{
    return m_assoc_kb_addr;
}

int
CrtFrame::getTermNum() const
{
    return m_term_num;
}

// ----------------------------------------------------------------------------
//   Crt frame management functions
// ----------------------------------------------------------------------------

// remove self from the list of CRTs
void
CrtFrame::destroyWindow()
{
    saveDefaults();     // save config options

    // if this is the primary frame, forget about it now
    if (m_primaryFrame == this) {
        m_primaryFrame = nullptr;
    }

    // close this window (system may defer it for a while)
    Destroy();
}


// One distinguished CRT which has all the controls, eg, kind of the superuser.
// This primary Crt has the ability to change the system configuration, and to
// change which disk images are in use. Non-primary CRTs can change only local
// properties, like CRT phosphor color and font.
CrtFrame *
CrtFrame::getPrimaryFrame()
{
    return m_primaryFrame;
}


// if the display has changed, updated it
void
CrtFrame::refreshWindow()
{
    // pass it through
    m_crt->refreshWindow();
}


// ----------------------------------------------------------------------------
//   when various disk state changes occur, pass them on to the
//   status bar of each Crt window.
// ----------------------------------------------------------------------------

// called when something changes about the specified disk
void
CrtFrame::diskEvent(int controller, int drive)
{
    CrtFrame *pf = getPrimaryFrame();
    if (pf != nullptr) {
        pf->m_statBar->diskEvent(controller, drive);
    }
}

// vim: ts=8:et:sw=4:smarttab
