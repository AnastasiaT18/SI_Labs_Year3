#include "Task_Report.h"
#include "SharedData.h"
#include <Arduino.h>

void Task_Report_init(void) {
    // nothing to initialize, uses only global variables
}

void Task_Report(void) {
    Serial.println("========================================");
    Serial.println("         10s STATISTICS REPORT         ");
    Serial.println("========================================");
    Serial.print("  Total presses   : "); Serial.println(g_totalPresses);
    Serial.print("  Short (<500ms)  : "); Serial.println(g_shortPresses);
    Serial.print("  Long  (>=500ms) : "); Serial.println(g_longPresses);

    if (g_totalPresses > 0) {
        unsigned long avg = (g_sumShortDuration + g_sumLongDuration)
                            / g_totalPresses;
        Serial.print("  Avg duration    : ");
        Serial.print(avg);
        Serial.println("ms");
    } else {
        Serial.println("  Avg duration    : N/A");
    }

    Serial.println("========================================");

    // reset all stats after report
    g_totalPresses     = 0;
    g_shortPresses     = 0;
    g_longPresses      = 0;
    g_sumShortDuration = 0;
    g_sumLongDuration  = 0;
}