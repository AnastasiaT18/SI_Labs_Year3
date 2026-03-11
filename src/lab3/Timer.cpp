#include "Timer.h"
#include "Scheduler.h"

void timer1_init(void) {
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS11);
    OCR1A  = 1999;                // 16MHz/8/1000 - 1 = every 1ms
    TIMSK1 = (1 << OCIE1A); //enables the Output Compare Match A interrupt for Timer1. Without this, the hardware event happens silently and nothing fires.
    sei(); //sets the global interrupt enable flag (I-bit in SREG). Even if TIMSK1 is set, interrupts won't fire until this is called.
}

ISR(TIMER1_COMPA_vect) { //the vector name the compiler uses to map this function to the correct interrupt vector table address. The hardware knows to jump here when Timer1 compare match fires.
    os_seq_scheduler_loop();      // called every 1ms by hardware
}