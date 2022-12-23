#ifndef TEXT_SCROLLER_HPP
#define TEXT_SCROLLER_HPP

#include <cstddef>
#include <string>

class Adafruit_SSD1306;

/*
 * The screen will only display the text between pixels 0 to 132.
 * The cursor is the beginning pixel for a string to be printed.
 * The cursor can be moved to any non-printable position. By moving
 * the cursor into the negative space, you achieve the effect of left
 * scrolling, because the screen will act as a sliding window.
 *
 *              OLED Display:
 *              -------------
 * "Hello WOrrrr|rllllllllll|llllllllllllllllllldddd"
 *              -------------
 *   -1                    1          2         3
 *  210987654321|01234567890|1234567890123456789012345678
 *  <<< Negative | Positive >>>
 *
 * _**NOTE:** Numbers shown above represent characters, not pixels._
 */
class Marquee {
  public:
    Marquee (Adafruit_SSD1306 & display);

    void scroll (void);
    void scrollPeriodMs (size_t ms);
    size_t scrollPeriodMs (void) const;
    void text (const std::string & text_);

  private:
    Adafruit_SSD1306 & _display;
    size_t _first_char_pixel;
    size_t _left_most_pixel;
    size_t _next_scroll_ms;
    size_t _scroll_period_ms;
    std::string _text;
};

#endif
