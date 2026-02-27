#include "Timer.h"
#include "Scheduler.h"

void timer1_init(void) {
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS11);
    OCR1A  = 1999;                // 16MHz/8/1000 - 1 = every 1ms
    TIMSK1 = (1 << OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect) {
    os_seq_scheduler_loop();      // called every 1ms by hardware
}