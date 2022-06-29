// Author: Siebren Bouwhuis
// Copyright Siebren Bouwhuis 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



/// @file
/// \brief
/// Contains the declaration for the pin_in_invert class
///

#include "hwlib.hpp"

#ifndef PIN_IN_INVERT_HPP
#define PIN_IN_INVERT_HPP

/// A simple decorator for the pin_in class, which will invert the read values
class pin_in_invert : public hwlib::pin_in {
private:
    /// A regular pin_in, to be inverted
    hwlib::pin_in& slave;
public:
    /// The constructor only requires a regular pin_in
    pin_in_invert(hwlib::pin_in
    &slave) :
    slave(slave) {}

    /// Will return the inverted read value of the pin (either high or low)
    bool read() override {
        return !slave.read();
    }

    /// Will refresh the pin
    void refresh() override {
        slave.refresh();
    }

};

#endif /* PIN_IN_INVERT_HPP */