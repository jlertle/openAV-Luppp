/*
 * Author: Harry van Haaren 2013
 *         harryhaaren@gmail.com
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef AVTK_BUTTON_H
#define AVTK_BUTTON_H

#include <FL/Fl_Button.H>

namespace Avtk
{

class Button : public Fl_Button
{
  public:
    Button(int _x, int _y, int _w, int _h, const char *_label):
        Fl_Button(_x, _y, _w, _h, _label)
    {
      x = _x;
      y = _y;
      w = _w;
      h = _h;
      
      labelMe = _label;
      setLabel( labelMe );
      
      _r = 1.0;
      _g = 0.48;
      _b = 0.0;
      
      _bgr = 0.11;
      _bgg = 0.11;
      _bgb = 0.11;
      
      highlight = false;
      mouseOver = false;
      
      greyedOut = false;
    }
    
    void setGreyOut( bool g )
    {
      greyedOut = g;
    }
    
    bool greyedOut;
    
    bool mouseOver;
    bool highlight;
    int x, y, w, h;
    const char* labelMe;
    
    void setLabel( const char* l)
    {
      labelMe = l;
      label( labelMe );
      redraw();
    }
    
    float _r, _g, _b;       // foreground colour
    float _bgr, _bgg, _bgb; // background colour
    float _outr, _outg, _outb; // outline colour
    
    void setColor(float r, float g, float b)
    {
      _r = r;
      _g = g;
      _b = b;
    }
    
    void setBgColor(float r, float g, float b)
    {
      _bgr = r;
      _bgg = g;
      _bgb = b;
    }
    
    void setHighlight(bool b)
    {
      highlight = b; redraw();
    }
    
    void draw()
    {
      if (damage() & FL_DAMAGE_ALL)
      {
        cairo_t *cr = Fl::cairo_cc();
        
        cairo_save( cr );
        
        cairo_rectangle( cr, x+1, y+1, w-2, h-2 );
        if ( !greyedOut )
          cairo_set_source_rgb( cr, _bgr, _bgg, _bgb );
        else
        {
          float grey = (_bgr + _bgg + _bgb) / 3;
          cairo_set_source_rgb( cr, grey, grey, grey );
        }
        cairo_fill_preserve(cr);
        
        cairo_set_line_width(cr, 1.3);
        cairo_rectangle( cr, x+1, y+1, w-2, h-2 );
        
        if ( highlight && !greyedOut )
        {
          cairo_set_source_rgba(cr, _r, _g, _b, 0.4);
          cairo_fill_preserve(cr);
        }
        
        float alpha = 0.6;
        if (mouseOver)
          alpha = 1;
        
        if ( !greyedOut )
          cairo_set_source_rgba(cr,  _r, _g, _b, alpha);
        else
        {
          float grey = (_r + _g + _b) / 3;
          cairo_set_source_rgb( cr, grey, grey, grey );
        }
        
        if ( highlight && !greyedOut )
          cairo_set_line_width(cr, 2.2);
        cairo_stroke(cr);
        
        cairo_restore( cr );
        
        draw_label();
      }
    }
    
    void resize(int X, int Y, int W, int H)
    {
      Fl_Widget::resize(X,Y,W,H);
      x = X;
      y = Y;
      w = W;
      h = H;
      redraw();
    }
    
    int handle(int event)
    {
      switch(event) {
        case FL_PUSH:
          highlight = 1;
          redraw();
          return 1;
        case FL_DRAG: {
            int t = Fl::event_inside(this);
            if (t != highlight) {
              highlight = t;
              redraw();
            }
          }
          return 1;
        case FL_ENTER:
          mouseOver = true;
          redraw();
          return 1;
        case FL_LEAVE:
          mouseOver = false;
          redraw();
          return 1;
        case FL_RELEASE:
          if (highlight) {
            highlight = 0;
            redraw();
            do_callback();
          }
          return 1;
        case FL_SHORTCUT:
          if ( test_shortcut() )
          {
            do_callback();
            return 1;
          }
          return 0;
        default:
          return Fl_Widget::handle(event);
      }
    }
};

} // Avtk

#endif // AVTK_BUTTON_H

