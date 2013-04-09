#include "simple_gui.h"
#include <iostream>
#include <assert.h>

//------------------------------------------------------------------------------
simple_gui::simple_gui(void):
  m_screen(NULL),
  m_coef(20)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
      std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl ;
    }
}

//------------------------------------------------------------------------------
void simple_gui::createWindow(uint32_t p_width,uint32_t p_height)
{
  const SDL_VideoInfo *l_video_info = SDL_GetVideoInfo();
  
  assert(l_video_info);
#if SDL_COMPILEDVERSION >= SDL_VERSIONNUM(1, 2, 14)
  std::cout << "Current resolution : " << l_video_info->current_w << "x" << l_video_info->current_h << " with Pixel Format " << ((uint32_t)l_video_info->vfmt->BitsPerPixel) << " bits per pixel" << std::endl ;
  m_coef = (l_video_info->current_w / p_width < l_video_info->current_h / p_height ? l_video_info->current_w / p_width : l_video_info->current_h / p_height );
#else
  m_coef = (1900 / p_width < 1130 / p_height ? 1900 / p_width : 1130 / p_height );
#endif
  if(!m_coef) m_coef =1 ;
  std::cout << "coef = " << m_coef << std::endl ;
  
  
  m_width = p_width * m_coef;
  m_height = p_height * m_coef;
  m_screen = SDL_SetVideoMode(m_width,m_height,32,SDL_SWSURFACE);
  if(m_screen == NULL)
    {
      std::cout << "Unable to set video mode to " << m_width << "*"<< m_height << "*32" << std::endl ;
      SDL_Quit();
    }

  uint32_t l_x = 0;
  uint32_t l_y = 0;
  m_start = m_screen->pixels;
  l_x = (m_width - 1) * m_coef;
  l_y = (m_height - 1) * m_coef;
  m_size= (uint64_t)m_screen->pixels + l_y * m_screen->pitch/4 + l_x - (uint64_t)m_start + 1;
  m_size *= sizeof(uint32_t);
}

//------------------------------------------------------------------------------
simple_gui::~simple_gui(void)
{
  SDL_Quit();
}

//------------------------------------------------------------------------------
void simple_gui::setPixel(uint32_t p_x,uint32_t p_y,uint32_t p_color)
  {
    if ( SDL_MUSTLOCK(m_screen) )
      {
	if ( SDL_LockSurface(m_screen) < 0 )
	  {
	    exit(-1);
	  }
      }
    set_pixel_without_lock(p_x,p_y,p_color);
	  
    if ( SDL_MUSTLOCK(m_screen) )
      {
	SDL_UnlockSurface(m_screen);
      }

  }

//------------------------------------------------------------------------------
uint32_t simple_gui::get_pixel(uint32_t p_x,uint32_t p_y)const
{
    if ( SDL_MUSTLOCK(m_screen) )
      {
	if ( SDL_LockSurface(m_screen) < 0 )
	  {
	    exit(-1);
	  }
      }

    uint32_t l_x = p_x * m_coef;
    uint32_t l_y = p_y * m_coef;
    uint32_t *l_bufp = (uint32_t *)m_screen->pixels + l_y * m_screen->pitch/4 + l_x;
    uint32_t l_result = *l_bufp;
    if ( SDL_MUSTLOCK(m_screen) )
      {
	SDL_UnlockSurface(m_screen);
      }
    return l_result;
}

void simple_gui::draw_line(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t p_color)
{
  uint32_t l_delta_x = (x1 < x2 ? 1 : -1 );
  uint32_t l_delta_y = (y1 < y2 ? 1 : -1 );
  if(y1 == y2)
    {
      for(uint32_t l_x = x1 ; l_x != x2; l_x += l_delta_x)
        {
          this->setPixel(l_x,y1,p_color);
        }
    }
  else if(x1 == x2)
    {
      for(uint32_t l_y = y1 ; l_y != y2; l_y += l_delta_y)
        {
          this->setPixel(x1,l_y,p_color);
        }
    }
  else
    {
      uint32_t l_x = x1;
      uint32_t l_y = y1;
      if(abs(x2-x1) == abs(y2-y1))
        {
          while(l_x != x2)
            {
              this->setPixel(l_x,l_y,p_color);
              l_x += l_delta_x;
              l_y += l_delta_y;
            }
        }
      else
        {
          int32_t l_diff_x = x2 -x1;
          int32_t l_diff_y = y2 -y1;
          if(l_diff_x != 0)
            {
              if(l_diff_x > 0)
                {
                  if(l_diff_y != 0 )
                    {
                      if(l_diff_y > 0)
                        {
                          // vecteur oblique dans le 1er quadran
                          if(l_diff_x >= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 1er octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2;
                              l_diff_y = l_diff_y * 2; //positive cumulated_error
                              while((x1 = x1 + 1) != x2)  // d�placements horizontaux
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_y) < 0)
                                    {
                                      y1 = y1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 2nd octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ;
                              l_diff_x = l_diff_x * 2 ;  // positive cumulated_error
                              while((y1 = y1 + 1) != y2)  // vertical moves
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_x) < 0)
                                    {
                                      x1 = x1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                      else
                        { 
                          // l_diff_y < 0 (et l_diff_x > 0)
                          // vecteur oblique dans le 4e cadran
                          if(l_diff_x >= -l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 8e octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2 ;
                              l_diff_y = l_diff_y * 2 ;  // cumulated_error est positif
                              while((x1 = x1 + 1) != x2)// d�placements horizontaux
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_y) < 0)
                                    {
                                      y1 = y1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 7e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // negative cumulated_error
                              while((y1 = y1 - 1) != y2)  // vertical moves
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_x) > 0)
                                    {
                                      x1 = x1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                    }
                  else
                    {  // l_diff_y = 0 (et l_diff_x > 0)
                      
                      // vecteur horizontal vers la droite
                      while((x1 = x1 + 1) != x2)
                        {
                          this->setPixel(x1,y1,p_color);
                        }
                      
                    }
                }
              else
                {
                  // l_diff_x < 0
                  if(l_diff_y != 0)
                    {
                      if(l_diff_y > 0)
                        {
                          // vecteur oblique dans le 2nd quadran
                          if(-l_diff_x >= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 4e octant
                              int32_t cumulated_error = l_diff_x ;
                              l_diff_x = cumulated_error * 2 ;
                              l_diff_y = l_diff_y * 2 ;  // negative cumulated_error
                              while((x1 = x1 - 1) != x2)  // d�placements horizontaux
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_y) >= 0)
                                    {
                                      y1 = y1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 3e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // positive cumulated_error
                              while((y1 = y1 + 1) != y2)  // vertical moves
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_x) <= 0)
                                    {
                                      x1 = x1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                      else
                        {
                          // l_diff_y < 0 (et l_diff_x < 0)
                          // vecteur oblique dans le 3e cadran
                          if(l_diff_x <= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 5e octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2 ; 
                              l_diff_y = l_diff_y * 2 ;  // negative cumulated_error
                              while((x1 = x1 - 1) != x2)  // d�placements horizontaux
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_y) >= 0)
                                    {
                                      y1 = y1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 6e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // negative cumulated_error
                              while((y1 = y1 - 1) != y2 )  // vertical moves
                                {
                                  this->setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_x) >= 0)
                                    {
                                      x1 = x1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
          
                        }
                    }
                  else
                    {
                      // l_diff_y = 0 (et l_diff_x < 0)
                      // vecteur horizontal vers la gauche
                      while((x1 = x1 - 1) != x2)
                        {
                          this->setPixel(x1,y1,p_color);
                        }
                    }
                }
            }
          else
            {
              // l_diff_x = 0
              if(l_diff_y != 0)
                {
                  if(l_diff_y > 0)
                    {
                      // vecteur vertical croissant
                      while((y1 = y1 + 1) != y2)
                        {
                          this->setPixel(x1,y1,p_color);
                        }
                    }
                  else
                    {
                      // l_diff_y < 0 (et l_diff_x = 0)
                      // vecteur vertical d�croissant
                      while((y1 = y1 - 1) != y2)
                        { 
                          this->setPixel(x1,y1,p_color);
                        }

                    }
                }
            }

        }
    }
}
//EOF
