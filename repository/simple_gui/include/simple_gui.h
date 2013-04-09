#ifndef _SIMPLE_GUI_H_
#define _SIMPLE_GUI_H_

#include "SDL/SDL.h"
#include <stdint.h>

class simple_gui
{
public:
  simple_gui(void);

  void createWindow(uint32_t p_width,uint32_t p_height);

  inline uint32_t getColorCode(uint8_t r,uint8_t g,uint8_t b);
  inline void get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b);
  inline void refresh(void);
  inline void * save_buffer(void)const;
  inline void load_buffer(void *);

  virtual ~simple_gui(void);
  void setPixel(uint32_t p_x,uint32_t p_y,uint32_t p_color);
  inline void set_pixel_without_lock(uint32_t p_x,uint32_t p_y,uint32_t p_color);
  uint32_t get_pixel(uint32_t p_x,uint32_t p_y)const;

  void draw_line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t p_color);

  inline void lock(void);
  inline void unlock(void);

private:
  SDL_Surface *m_screen;
  uint32_t m_coef;
  void * m_start;
  uint32_t m_size;
  unsigned int m_width;
  unsigned int m_height;
};

void * simple_gui::save_buffer(void)const
{
  void * l_buffer = new uint8_t[m_size];
  memset(l_buffer,0,m_size);
  memcpy(l_buffer,m_start,m_size);
  return l_buffer;
}

void simple_gui::load_buffer(void * p_buffer)
{
  memcpy(m_start,p_buffer,m_size);
}


//------------------------------------------------------------------------------
uint32_t simple_gui::getColorCode(uint8_t r,uint8_t g,uint8_t b)
{
  return SDL_MapRGB(m_screen->format,r,g,b);
}

//------------------------------------------------------------------------------
void simple_gui::get_RGB_code(uint32_t p_color,uint8_t & r,uint8_t & g,uint8_t & b)
{
  SDL_GetRGB(p_color,m_screen->format,&r,&g,&b); 
}

//------------------------------------------------------------------------------
void simple_gui::refresh(void)
{
  SDL_UpdateRect(m_screen,0,0,0,0);
}

//------------------------------------------------------------------------------
void simple_gui::set_pixel_without_lock(uint32_t p_x,uint32_t p_y,uint32_t p_color)
{
  for(uint32_t l_x = p_x * m_coef;l_x < m_coef *(p_x + 1);++l_x)
    {
      for(uint32_t l_y = p_y * m_coef;l_y < m_coef *(p_y + 1);++l_y)
	{
	  if(l_x >= 0 && l_x < m_width && l_y >= 0 && l_y < m_height)
	    {
	      uint32_t *l_bufp = (uint32_t *)m_screen->pixels + l_y * m_screen->pitch/4 + l_x;
	      *l_bufp = p_color;
	    }
	}
    }	  
}

//------------------------------------------------------------------------------
void simple_gui::lock(void)
{
  if ( SDL_MUSTLOCK(m_screen) )
    {
      if ( SDL_LockSurface(m_screen) < 0 )
	{
	  exit(-1);
	}
    }
}

//------------------------------------------------------------------------------
void simple_gui::unlock(void)
{
  if ( SDL_MUSTLOCK(m_screen) )
    {
      SDL_UnlockSurface(m_screen);
    }
}



#endif /* _SIMPLE_GUI_H_ */
