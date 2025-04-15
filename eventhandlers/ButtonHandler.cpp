#include "ButtonHandler.h"

void buttonHandlerInit() {
    // Configure Button IO
    IOMUX->SECCFG.PINCM[PA15INDEX] = 0x40081;
    IOMUX->SECCFG.PINCM[PA16INDEX] = 0x40081;
    IOMUX->SECCFG.PINCM[PA17INDEX] = 0x40081;
    IOMUX->SECCFG.PINCM[PA18INDEX] = 0x40081;

    
}
