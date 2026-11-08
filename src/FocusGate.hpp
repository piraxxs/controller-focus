#pragma once
struct FocusGate {
    bool armed = false;
    void unfocus() { armed = false; }
    bool allow(bool foreground, bool connected, bool neutral) {
        if (!foreground || !connected) {
            armed = false;
            return false;
        }
        if (!armed && neutral) armed = true;
        return armed;
    }
};
