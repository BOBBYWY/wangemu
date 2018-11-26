#ifndef _INCLUDE_IOCARD_KEYBOARD_H_
#define _INCLUDE_IOCARD_KEYBOARD_H_

#include "IoCard.h"

class Cpu2200;
class Scheduler;
class Timer;

class IoCardKeyboard : public IoCard
{
public:
    // see the base class for the definition of the public functions
    CANT_ASSIGN_OR_COPY_CLASS(IoCardKeyboard);

    // ----- common IoCard functions -----
    IoCardKeyboard(std::shared_ptr<Scheduler> scheduler,
                   std::shared_ptr<Cpu2200>   cpu,
                   int baseaddr, int cardslot);
    ~IoCardKeyboard();

    std::vector<int> getAddresses() const override;

    void  reset(bool hard_reset=true) override;
    void  select() override;
    void  deselect() override;
    void  OBS(int val) override;
    void  CBS(int val) override;
    void  CPB(bool busy) override;

    // ----- IoCardKeyboard specific functions -----

    // this is called by UI when a key is entered by the user
    void receiveKeystroke(int keycode);

    // various keyboard related flags
    enum { KEYCODE_SF   = 0x0100,  // special function key flag
           KEYCODE_HALT = 0x0200,  // user pressed the reset button on the keyboard
           KEYCODE_EDIT =    240   // the EDIT key
    };

private:
    // ---- card properties ----
    const std::string getDescription() const override;
    const std::string getName() const override;
    std::vector<int> getBaseAddresses() const override;

    // timer callback function to put some required delay in script processing
    void tcbScript();

    // test if any key is ready to accept
    void check_keyready();

    std::shared_ptr<Scheduler> m_scheduler;  // shared event scheduler
    std::shared_ptr<Cpu2200>   m_cpu;        // associated CPU
    std::shared_ptr<Timer>     m_tmr_script; // keystrokes are sent a few 10s of uS after !CPB
    const int   m_baseaddr;       // the address the card is mapped to
    const int   m_slot;           // which slot the card is plugged into
    bool        m_selected;       // this card is being addressed
    bool        m_cpb;            // 1=CPU busy (not accepting IBS input)
    bool        m_key_ready;      // key_code is valid
    int         m_key_code;       // keycode of most recently received keystroke
};

#endif // _INCLUDE_IOCARD_KEYBOARD_H_

// vim: ts=8:et:sw=4:smarttab
