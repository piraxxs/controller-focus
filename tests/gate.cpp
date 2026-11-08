#include "../src/FocusGate.hpp"
#include <cstdlib>
#include <iostream>
void check(bool value, const char* message) {
    if (!value) { std::cerr << message << '\n'; std::exit(1); }
}
int main() {
    FocusGate gate;
    check(gate.allow(true, true, true), "neutral foreground must work");
    check(gate.allow(true, true, false), "foreground buttons must work");
    check(!gate.allow(false, true, false), "background button must be blocked");
    check(!gate.allow(false, true, true), "background neutral must be blocked");
    check(!gate.allow(true, true, false), "held button on return must be blocked");
    check(gate.allow(true, true, true), "neutral rearms controller");
    check(gate.allow(true, true, false), "fresh foreground press must work");
    gate.unfocus(); // No background polling when minimized.
    check(!gate.allow(true, true, false), "focus event must disarm without polling");
    check(!gate.allow(true, false, true), "disconnection must be blocked");
    check(!gate.allow(true, true, false), "reconnection with held button must wait");
    check(gate.allow(true, true, true), "neutral reconnect must rearm");
    FocusGate other;
    check(!other.allow(true, true, false), "second controller starts disarmed");
    check(gate.allow(true, true, false), "controllers must rearm independently");
    std::cout << "All focus transition tests passed\n";
}
