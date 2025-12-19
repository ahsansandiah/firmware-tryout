#include <stdint.h>

extern int main(void);

// Symbols from linker script
extern uint32_t _sidata; // start of init values for .data in flash
extern uint32_t _sdata;  // start of .data in RAM
extern uint32_t _edata;  // end of .data in RAM
extern uint32_t _sbss;   // start of .bss in RAM
extern uint32_t _ebss;   // end of .bss in RAM
extern uint32_t _estack; // top of stack

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    &_estack,
    Reset_Handler,
    Default_Handler, // NMI
    Default_Handler, // HardFault
    Default_Handler, // MemManage
    Default_Handler, // BusFault
    Default_Handler, // UsageFault
    0, 0, 0, 0,      // Reserved
    Default_Handler, // SVC
    Default_Handler, // DebugMon
    0,               // Reserved
    Default_Handler, // PendSV
    Default_Handler  // SysTick
    // Add peripheral IRQs as needed
};

void Reset_Handler(void) {
    // Copy .data from flash to RAM
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    // Zero .bss
    for (dst = &_sbss; dst < &_ebss; ++dst) {
        *dst = 0;
    }
    // Call main
    main();
    // If main returns, loop forever
    while (1) {
    }
}

void Default_Handler(void) {
    while (1) {
    }
}
