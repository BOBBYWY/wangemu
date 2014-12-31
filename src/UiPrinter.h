// This represents the paper surface that gets drawn upon.
// It is managed by PrinterFrame.

#ifndef _INCLUDE_UI_PRINTER_H_
#define _INCLUDE_UI_PRINTER_H_

#include "wx/print.h"   // printing support

class PrinterFrame;

class Printer: public wxScrolledWindow
{
public:
    Printer( PrinterFrame *parent );
    ~Printer();

    // ---- setters/getters ----
    void setFontSize(const int size);

    void setGreenbar(bool greenbar=true);
    bool getGreenbar() const;

    void setMargins(int left, int right, int top, int bottom);
    void getMargins(int& left, int& right, int& top, int& bottom);
    
    void               setOrientation(wxPrintOrientation orientation);
    wxPrintOrientation getOrientation();

    void        setPaperId(wxPaperSize paperid);
    wxPaperSize getPaperId();

    void   setPaperName(const string &papername);
    string getPaperName();

    void       setBin(wxPrintBin paperbin);
    wxPrintBin getBin();

    void   setRealPrinterName(const string &name);
    string getRealPrinterName();
    
    void setPageAttributes( int linelength, int pagelength);
    void getPageAttributes(int& linelength, int& pagelength);

    void getCellAttributes(int *cell_w, int *cell_h);

    void setAutoshow(bool b);
    bool getAutoshow();

    void setPrintasgo(bool b);
    bool getPrintasgo();

    void setPortdirect(bool b);
    bool getPortdirect();

    void   setPortstring(const string &name);
    string getPortstring();

    // ---- other functions ----
    // redraw entire screen
    void invalidateAll()  { Refresh(false); }

    // return a pointer to the screen image
    wxBitmap *grabScreen();

    // emit a character to the display
    void printChar(uint8 byte);

    // save the printer contents to a file
    void saveToFile();

    // clear the printer contents
    void printClear();

    // return true if the print stream is empty
    bool isEmpty();

    // return the number of pages in the current copy of the printstream
    int numberOfPages();

    // create a print page image
    void generatePrintPage(wxDC *dc, int pagenum, float vertAdjust);

    // redraw the scrollbars
    void scrollbarSet(int xpos, int ypos, bool redraw);

    // the print dialog is modeless, so a copy of the stream needs to be made
    // and used for the print dialog. These two functions are used to manage the copy
    void createStreamCopy();
    void destroyStreamCopy();

private:
    // ---- event handlers ----
    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnEraseBackground(wxEraseEvent &event);
    void OnTimer(wxTimerEvent &event);

    // ---- utility functions ----

    // send a byte directly to the parallel port (windows only)
    void lptChar(uint8 byte);

    // close the parallel port (windows only)
    void closePort();

    // refresh the screen display
    void drawScreen(wxDC &dc, int startCol, int startRow );

    // update the bitmap of the screen image
    void generateScreen(int startCol, int startRow);

    // add a line to the print stream
    void emitLine();

    // add lines to print stream to account for form feed
    void formFeed();

    // check redraw of screen and set scrollbars
    void updateView();

    // update the statusbar text
    void updateStatusbar();

    // ---- member variables ----
    PrinterFrame *m_parent;             // who owns us

    // for support of direct printing to parallel port
    bool        m_printing_flag;
    FILE       *m_fp_port;

    // this holds the dimensions of the visible area we have to draw on,
    // which is entirely independent of the logical Printer dimensions.
    int         m_scrpix_w;             // display dimension, in pixels
    int         m_scrpix_h;             // display dimension, in pixels

    wxBitmap    m_scrbits;              // image of the display

    int         m_chars_w;              // screen dimension, in characters
    int         m_chars_h;              // screen dimension, in characters

    wxFont      m_font;                 // font in use
    int         m_fontsize;             // size of font (in points)
    int         m_charcell_w;           // width of one character cell
    int         m_charcell_h;           // height of one character cell

    bool        m_greenbar;             // paper display format

    // margins
    int         m_marginleft;
    int         m_margintop;
    int         m_marginright;
    int         m_marginbottom;

    string      m_realprintername;      // name of the real printer
    wxPrintOrientation m_orientation;   // page orientation (wxPORTRAIT or wxLANDSCAPE)
    wxPaperSize m_paperid;              // paper id (wxPAPER_LETTER, etc.)
    string      m_papername;            // the name of the paperid
    wxPrintBin  m_paperbin;             // paper bin (wxPRINTBIN_DEFAULT, etc.)

    int         m_linelength;           // the line length of the logical printer
    int         m_pagelength;           // the page length of the logical printer
    bool        m_autoshow;             // indicates if view should automatically when new print stream is received
    bool        m_printasgo;            // indicates if each page of the stream should be printed automatically, then cleared, as it fills up
    bool        m_portdirect;           // indicates printing directly to parallel port (windows only). All other printing settings are ignored
                                        //   and output is dumped directly to the port
    string      m_portstring;           // contains the name of the parallel port (windows only)
    wxTimer     m_portTimer;            // control closing of LPT port

    // place to accumulate characters until we have a full line.
    // a char array is used instead of a wxString to avoid tons
    // of wxString reallocations.
#define m_linebuf_maxlen (256)
    int         m_linebuf_len;          // number of characters in buffer
    char        m_linebuf[m_linebuf_maxlen+1];  // accumulates line to print

    wxArrayString m_printstream;        // represents the entire print stream
    wxArrayString m_printstream_copy;   // this is a copy that is used for printing purposes

    CANT_ASSIGN_OR_COPY_CLASS(Printer);
    DECLARE_EVENT_TABLE()
};


class Printout : public wxPrintout
{
public:
    Printout(wxChar *title, Printer *printer);

    // ---- event handlers ----
    bool OnPrintPage(int page);
    bool OnBeginDocument(int startPage, int endPage);

    bool HasPage(int page);
    void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);

private:
    Printer *m_printer;

    CANT_ASSIGN_OR_COPY_CLASS(Printout);
};

#endif _INCLUDE_UI_PRINTER_H_
