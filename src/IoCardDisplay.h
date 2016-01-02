// this is a base class for the 80x24 and the 64x16 display controllers
// and implements all the real functionality of both.

#ifndef _INCLUDE_IOCARD_DISPLAY_H_
#define _INCLUDE_IOCARD_DISPLAY_H_

#include "IoCard.h"

class Cpu2200;
class Scheduler;
class Timer;

class IoCardDisplay : public IoCard
{
public:
    // see the base class for the definition of the public functions
    CANT_ASSIGN_OR_COPY_CLASS(IoCardDisplay);

    // ----- common IoCard functions -----
    IoCardDisplay(Scheduler &scheduler, Cpu2200 &cpu,
                  int baseaddr, int cardslot, int size=UI_SCREEN_64x16);
    ~IoCardDisplay();

    vector<int> getAddresses() const override;

    void  reset(bool hard_reset=true) override;
    void  select() override;
    void  deselect() override;
    void  OBS(int val) override;
    void  CBS(int val) override;
    int   getIB5() const override;
    void  CPB(bool busy) override;

private:
    // ---- card properties ----
    const string getDescription() const override;
    const string getName() const override;
    vector<int> getBaseAddresses() const override;

    Scheduler &m_scheduler;     // shared system event scheduler
    Cpu2200   &m_cpu;           // associated CPU
    const int  m_baseaddr;      // the address the card is mapped to
    const int  m_slot;          // which slot the card is plugged into
    bool       m_selected;      // the card is currently selected
    bool       m_cpb;           // the cpu is busy
    bool       m_card_busy;     // the card is busy doing something

    const int  m_size;          // display type
    UI_gui_handle_t m_wndhnd;   // opaque handle to UI window

    // model controller "busy" timing
    Timer     *m_thnd_hsync;    // horizontal sync timer
    bool       m_realtime;      // true: match real timing, false: go fast
    int        m_hsync_count;   // which horizontal line we are on
    enum {
        BUSY_NOT,     // not busy
        BUSY_CHAR,    // wait for next hsync then clear busy
        BUSY_CLEAR1,  // wait for vsync, then advance to BUSY_CLEAR2
        BUSY_CLEAR2,  // wait for vsync, then clear busy
        BUSY_ROLL1,   // wait for hsync, then advance to BUSY_ROLL2
        BUSY_ROLL2,   // wait for hsync, then clear busy
    } m_busy_state;

    void tcbHsync(int arg);     // timer callback
};

#endif // _INCLUDE_IOCARD_DISPLAY_H_

// vim: ts=8:et:sw=4:smarttab
