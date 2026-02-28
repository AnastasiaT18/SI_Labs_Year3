#include "Task_Report.h"
#include "SharedData.h"
#include <Arduino.h>

void Task_Report_init(void) {
    // nothing to initialize, uses only global variables
}

void Task_Report(void) {
    printf("========================================\n");
    printf("         10s STATISTICS REPORT         \n");
    printf("========================================\n");
    printf("  Total presses   : %lu\n", g_totalPresses);
    printf("  Short (<500ms)  : %lu\n", g_shortPresses);
    printf("  Long  (>=500ms) : %lu\n", g_longPresses);

    if (g_totalPresses > 0) {
    unsigned long avg = (g_sumShortDuration + g_sumLongDuration) / g_totalPresses;
    printf("  Avg duration    : %lums\n", avg);
    } else {
        printf("  Avg duration    : N/A\n");
    }
    printf("========================================\n");

    // reset all stats after report
    g_totalPresses     = 0;
    g_shortPresses     = 0;
    g_longPresses      = 0;
    g_sumShortDuration = 0;
    g_sumLongDuration  = 0;
}