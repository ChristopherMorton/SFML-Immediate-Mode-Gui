#ifndef IMGUI_WIDGET_HPP__
#define IMGUI_WIDGET_HPP__

/*
 * An IMGuiWidget is an object with one main function, doWidget(),
 * which will check the ui state in IMGuiManager,
 * update it if appropriate, render the widget based on that state,
 * and then return 0 if inactive or 1+ if activated.
 */

class IMGuiWidget
{
protected:
    int _x_position, _y_position, _x_dimension, _y_dimension;

    //IMGuiWidget( int x_pos, int y_pos, int x_dim, int y_dim )
        //: _x_position(x_pos), _y_position(y_pos),
          //_x_dimension(x_dim), _y_dimension(y_dim) {}
    //IMGuiWidget( const IMGuiWidget& other )
        //: _x_position(other._x_position), _y_position(other._y_position),
          //_x_dimension(other._x_dimension), _y_dimension(other._y_dimension) {}

public:
    virtual ~IMGuiWidget() {}

    virtual int doWidget() = 0;

    // Moves the widget before Do-ing, the values are absolute
    virtual int doMove( int x_pos, int y_pos, bool keep_new_position ) = 0;
    // Moves the widget before Do-ing, the values are relative
    virtual int doShift( int x_shift, int y_shift, bool keep_new_position ) = 0;
    // Resizes before Doing
    virtual int doResize( int x_size, int y_size, bool keep_new_size ) = 0;

    //virtual int SetPosition( int x_pos, int y_pos ) { _x_position = x_pos; _y_position = y_pos; return 0; }
    //virtual int SetSize( int x_dim, int y_dim ) { _x_dimension = x_dim; _y_dimension = y_dim; return 0; }
    virtual int setPosition( int x_pos, int y_pos ) = 0;
    virtual int setSize( int x_dim, int y_dim ) = 0;

};
#endif
