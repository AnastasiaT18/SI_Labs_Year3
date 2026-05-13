#include "LedBank.h"

TrafficLedBank::TrafficLedBank(int ew_red, int ew_yellow, int ew_green,
                               int ns_red, int ns_yellow, int ns_green)
    : _ew_red(ew_red),
      _ew_yellow(ew_yellow),
      _ew_green(ew_green),
      _ns_red(ns_red),
      _ns_yellow(ns_yellow),
      _ns_green(ns_green)
{
    allOff();
}

void TrafficLedBank::apply(const TrafficOutput& out) {
    out.ew_red    ? _ew_red.turnOn()    : _ew_red.turnOff();
    out.ew_yellow ? _ew_yellow.turnOn() : _ew_yellow.turnOff();
    out.ew_green  ? _ew_green.turnOn()  : _ew_green.turnOff();
    out.ns_red    ? _ns_red.turnOn()    : _ns_red.turnOff();
    out.ns_yellow ? _ns_yellow.turnOn() : _ns_yellow.turnOff();
    out.ns_green  ? _ns_green.turnOn()  : _ns_green.turnOff();
}

void TrafficLedBank::allOff() {
    _ew_red.turnOff();
    _ew_yellow.turnOff();
    _ew_green.turnOff();
    _ns_red.turnOff();
    _ns_yellow.turnOff();
    _ns_green.turnOff();
}