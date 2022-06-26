#include "hwlib.hpp"

#ifndef PIN_IN_INVERT_HPP
#define PIN_IN_INVERT_HPP

class pin_in_invert : public hwlib::pin_in {
private:
    hwlib::pin_in& slave;
public:
    pin_in_invert(hwlib::pin_in
    &slave) :
    slave(slave) {}

    bool read() override {
        return !slave.read();
    }

    void refresh() override {
        slave.refresh();
    }

};

#endif /* PIN_IN_INVERT_HPP */