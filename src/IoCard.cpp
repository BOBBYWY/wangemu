// Although the IoCard class is abstract for the most part,
// these factory functions live here

#include "Ui.h"
#include "CardCfgState.h"
#include "DiskCtrlCfgState.h"
#include "Host.h"
#include "Cpu2200.h"
#include "IoCardDisk.h"
#include "IoCardDisplay.h"
#include "IoCardKeyboard.h"
#include "IoCardPrinter.h"
#include "IoCardTermMux.h"
#include "Scheduler.h"
#include "System2200.h"
#include "SysCfgState.h"

// ========================================================================
// card management functions (used by UI)
// ========================================================================

// create an instance of the specified card
IoCard *
IoCard::makeCard(Scheduler& scheduler, Cpu2200& cpu, card_t type,
                 int baseaddr, int cardslot, const CardCfgState *cfg)
{
    return makeCardImpl(scheduler, cpu, type, baseaddr, cardslot, cfg);
}


// make a temporary card; this is so code can query the properties of the card;
// as such, the IoCard* functions know to do only partial construction
IoCard *
IoCard::makeTmpCard(card_t type)
{
// FIXME: this is sinful to pass 0 to a ref!
    return makeCardImpl( *(Scheduler*)0, *(Cpu2200*)0, type, 0x000, -1,
                         (CardCfgState *)0 );
}


// this is the shared implementation that the other make*Card functions use
IoCard *
IoCard::makeCardImpl(Scheduler& scheduler, Cpu2200& cpu, card_t type,
                     int baseaddr, int cardslot,
                     const CardCfgState *cfg)
{
    IoCard* crd = nullptr;

    switch (type) {
        case card_t::keyboard:
            crd = new IoCardKeyboard( scheduler, cpu, baseaddr, cardslot );
            break;
        case card_t::disp_64x16:
            crd = new IoCardDisplay( scheduler, cpu, baseaddr, cardslot,
                                     UI_SCREEN_64x16 );
            break;
        case card_t::disp_80x24:
            crd = new IoCardDisplay( scheduler, cpu, baseaddr, cardslot,
                                     UI_SCREEN_80x24 );
            break;
        case card_t::term_mux:
            crd = new IoCardTermMux( cpu, baseaddr, cardslot);
            break;
        case card_t::printer:
            crd = new IoCardPrinter( cpu, baseaddr, cardslot );
            break;
        case card_t::disk:
            crd = new IoCardDisk( scheduler, cpu, baseaddr, cardslot, cfg );
            break;
        default:
            assert(false);
            break;
    }

    return crd;
}

// vim: ts=8:et:sw=4:smarttab
