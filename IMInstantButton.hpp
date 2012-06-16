#ifndef IMGUI_INSTANTBUTTON_HPP__
#define IMGUI_INSTANTBUTTON_HPP__

/* This class is identical to IMButton in almost every way.
 * The only difference is in behavior: whereas an IMButton is activated
 * (returns 1 from doWidget()) when it is active and hot and the mouse is released,
 * an IMInstantButton is activated immediately upon being pressed.
 */

#include "IMButton.hpp"

class IMInstantButton : public IMButton
{
public:
    IMInstantButton();
    IMInstantButton( int x_pos, int y_pos, int x_size, int y_size );

    IMInstantButton( const IMButton& other );
    IMInstantButton& operator=( const IMButton& rhs );

    virtual ~IMInstantButton();

    virtual int doButton( int x_pos, int y_pos, int x_size, int y_size );
};
#endif
