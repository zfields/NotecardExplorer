#include "Marquee.hpp"

#include <string>

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#include "OLED_FeatherWing.hpp"

Marquee::Marquee (
    Adafruit_SSD1306 & display_
):
    _display(display_),
    _first_char_pixel(0),
    _left_most_pixel(0),
    _next_scroll_ms(0),
    _scroll_period_ms(0),
    _text(nullptr)
{ }

void
Marquee::scroll (
    void
) {
    size_t now_ms = ::millis();
    if (now_ms < _next_scroll_ms) {
        // Take no action
    } else {
        // Update the next scroll time
        _next_scroll_ms = (now_ms + _scroll_period_ms);

        // Collect Y cursor position
        size_t y_cursor = _display.getCursorY();

        // Tell the OLED display where to begin printing the message
        _display.setCursor(_first_char_pixel, y_cursor);

        // Print the message at the cursor position
        _display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        _display.print(_text.c_str());

        // Render the display contents
        _display.display();

        // Advance the cursor into the negative space,
        // until message is no longer visible.
        if (--_first_char_pixel < _left_most_pixel) {
            _first_char_pixel = _display.width();
        }
    }
}

void
Marquee::scrollPeriodMs (
    size_t ms_
) {
    _scroll_period_ms = ms_;
}

size_t
Marquee::scrollPeriodMs (
    void
) const {
    return _scroll_period_ms;
}

void
Marquee::text (
    const std::string & text_
) {
    _text = text_;
    _next_scroll_ms = (::millis() + _scroll_period_ms);
    _first_char_pixel = _display.width();

    // Get Character Properties
    uint16_t char_height, char_width;
    getCharacterHeightAndWidth (&char_height, &char_width);

    // Set left-most pixel position for scrolling text
    _left_most_pixel = (char_width * _text.length());
}
