#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <assert.h>

class my_color
{
 public:
  
  my_color(void):
    m_R(0),
    m_G(0),
    m_B(0)
      {
      }

    my_color(uint8_t p_R,uint8_t p_G,uint8_t p_B):
      m_R(p_R),
      m_G(p_G),
      m_B(p_B)
	{
	}

      bool operator ==(const my_color & p_color)const
      {
	return m_R==p_color.m_R && m_G==p_color.m_G && m_B==p_color.m_B;
      }

      bool operator !=(const my_color & p_color)const
      {
	return m_R != p_color.m_R || m_G != p_color.m_G || m_B != p_color.m_B;
      }

      inline void set_red(uint8_t p_r)
	{
	  m_R = p_r;
	}

      inline void set_green(uint8_t p_g)
	{
	  m_G = p_g;
	}

      inline void set_blue(uint8_t p_b)
	{
	  m_B = p_b;
	}

      inline uint8_t get_red(void)const
	{
	  return m_R;
	}

      inline uint8_t get_green(void)const
	{
	  return m_G;
	}

      inline uint8_t get_blue(void)const
	{
	  return m_B;
	}

      virtual void display(void)const
      {
	std::cout << "R=" << std::setw(3) << (uint32_t)m_R << ", G=" << std::setw(3) << (uint32_t)m_G << ", B=" << std::setw(3) << (uint32_t)m_B ;
      }

      virtual ~my_color(void)
	{
	}
 private:
      uint8_t m_R;
      uint8_t m_G;
      uint8_t m_B;
};

class my_color_alpha: public my_color
{
 public:
  my_color_alpha(uint8_t p_R,uint8_t p_G,uint8_t p_B,uint8_t p_alpha=0):
    my_color(p_R,p_G,p_B),
    m_alpha(p_alpha)
      {
      }
  my_color_alpha(void):
    my_color(),
    m_alpha(0)
      {
      }
    void display(void)const
    {
      my_color::display();
      std::cout << ", A=" << std::setw(3) << (uint32_t)m_alpha ;
    }
    inline uint8_t get_alpha(void)const
      {
	return m_alpha;
      }

 private:
    uint8_t m_alpha;
};

class my_bmp_header
{
 public:
  my_bmp_header(FILE * p_file):
    m_reserved(0),
    m_offset(54),
    m_remaining_header_size(40),
    m_picture_width(0),
    m_picture_height(0),
    m_nb_plan(1),
    m_nb_bits_per_pixel(0),
    m_compression(0),
    m_picture_size(0),
    m_nb_horizontal_pixel_per_meter(3780),
    m_nb_vertical_pixel_per_meter(3780),
    m_nb_colour_used(0),
    m_nb_important_colors(0)
      {
	assert(p_file);

	fread(&m_file_type,sizeof(uint8_t),2,p_file);
	fread(&m_file_size,sizeof(uint32_t),1,p_file);
	fread(&m_reserved,sizeof(uint32_t),1,p_file);
	fread(&m_offset,sizeof(uint32_t),1,p_file);
	fread(&m_remaining_header_size,sizeof(uint32_t),1,p_file);
	fread(&m_picture_width,sizeof(uint32_t),1,p_file);
	fread(&m_picture_height,sizeof(uint32_t),1,p_file);
	fread(&m_nb_plan,sizeof(uint16_t),1,p_file);
	fread(&m_nb_bits_per_pixel,sizeof(uint16_t),1,p_file);
	fread(&m_compression,sizeof(uint32_t),1,p_file);
	fread(&m_picture_size,sizeof(uint32_t),1,p_file);
	fread(&m_nb_horizontal_pixel_per_meter,sizeof(uint32_t),1,p_file);
	fread(&m_nb_vertical_pixel_per_meter,sizeof(uint32_t),1,p_file);
	fread(&m_nb_colour_used,sizeof(uint32_t),1,p_file);
	fread(&m_nb_important_colors,sizeof(uint32_t),1,p_file);
	if(!m_picture_size)
	  {
	    m_picture_size = compute_picture_size(m_picture_width,m_picture_height,m_nb_bits_per_pixel);
	    std::cout << "Picture size read from file is 0 so replacing this by computed value " << m_picture_size << std::endl ;
	  }
      }

    void save(FILE *p_file)const
    {
      assert(p_file);

      fwrite(&m_file_type,sizeof(uint8_t),2,p_file);
      fwrite(&m_file_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_reserved,sizeof(uint32_t),1,p_file);
      fwrite(&m_offset,sizeof(uint32_t),1,p_file);
      fwrite(&m_remaining_header_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_width,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_height,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_plan,sizeof(uint16_t),1,p_file);
      fwrite(&m_nb_bits_per_pixel,sizeof(uint16_t),1,p_file);
      fwrite(&m_compression,sizeof(uint32_t),1,p_file);
      fwrite(&m_picture_size,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_horizontal_pixel_per_meter,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_vertical_pixel_per_meter,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_colour_used,sizeof(uint32_t),1,p_file);
      fwrite(&m_nb_important_colors,sizeof(uint32_t),1,p_file);
    }

    my_bmp_header(uint32_t p_width,uint32_t p_height,uint16_t p_nb_bits_per_pixel,uint32_t p_palette_size):
      m_file_size(0),
      m_reserved(0),
      m_offset(54+p_palette_size*4),
      m_remaining_header_size(40),
      m_picture_width(p_width),
      m_picture_height(p_height),
      m_nb_plan(1),
      m_nb_bits_per_pixel(p_nb_bits_per_pixel),
      m_compression(0),
      m_picture_size(compute_picture_size(p_width,p_height,p_nb_bits_per_pixel)),
      m_nb_horizontal_pixel_per_meter(3780),
      m_nb_vertical_pixel_per_meter(3780),
      m_nb_colour_used(0),
      m_nb_important_colors(0)
	{
	  m_file_type[0] = 'B';
	  m_file_type[1] = 'M';
	  m_file_size = m_offset+m_picture_size;
	}

      inline uint32_t get_palette_size(void)const
	{
	  return (m_offset - 54) / 4;
	}

      void display(void)const
      {
	std::cout << "File type : \"" << (char)m_file_type[0] << (char)m_file_type[1] << "\"" << std::endl;
	std::cout << "File size : " << m_file_size << std::endl ;
	std::cout << "4 Reserved bytes : " << m_reserved << std::endl ;
	std::cout << "Offset : " << m_offset << std::endl ;
	std::cout << "Remaining header size : " <<  m_remaining_header_size << std::endl ;
	std::cout << "Picture width : " << m_picture_width << std::endl ;
	std::cout << "Picture height : "<< m_picture_height << std::endl ;
	std::cout << "Nb plan : " << m_nb_plan << std::endl ;
	std::cout << "Nb bits per pixel : " << m_nb_bits_per_pixel << std::endl ;
	std::cout << "Compression : " << m_compression << std::endl;
	std::cout << "Picture size : " << m_picture_size << std::endl ;
	std::cout << "Nb horizontal pixel per meter : " << m_nb_horizontal_pixel_per_meter << std::endl ;
	std::cout << "Nb vertical pixel per meter : " << m_nb_vertical_pixel_per_meter << std::endl ;
	std::cout << "Nb colour used : " << m_nb_colour_used << std::endl ;
	std::cout << "Nb important colours : " <<  m_nb_important_colors << std::endl ;
      }

      inline uint16_t get_nb_bits_per_pixel(void)const
	{
	  return m_nb_bits_per_pixel;
	}

      inline uint32_t get_width(void)const
	{
	  return m_picture_width;
	}

      inline uint32_t get_height(void)const
	{
	  return m_picture_height;
	}

      inline uint32_t get_picture_size(void)const
	{
	  return m_picture_size;
	}

 private:
      static inline uint32_t compute_picture_size(uint32_t p_width,uint32_t p_height,uint16_t p_nb_bits_per_pixel)
	{
	  return 4 * p_height * (uint32_t)ceil((p_width * p_nb_bits_per_pixel) / 32.0 );
	}

      uint8_t m_file_type[2];
      uint32_t m_file_size;
      uint32_t m_reserved;
      uint32_t m_offset;
      uint32_t m_remaining_header_size;
      uint32_t m_picture_width;
      uint32_t m_picture_height;
      uint16_t m_nb_plan;
      uint16_t m_nb_bits_per_pixel;
      uint32_t m_compression;
      uint32_t m_picture_size;
      uint32_t m_nb_horizontal_pixel_per_meter;
      uint32_t m_nb_vertical_pixel_per_meter;
      uint32_t m_nb_colour_used;
      uint32_t m_nb_important_colors;
};

class my_palette
{
 public:
  my_palette(uint32_t p_size,FILE *p_file=NULL):
    m_size(p_size),
    m_colors(new my_color_alpha*[p_size])
      {
	assert(p_size);
	if(p_file)
	  {
	    uint8_t l_byte_array[4];
	    for(uint32_t l_index = 0 ; l_index < p_size; ++l_index)
	      {
		fread(l_byte_array,sizeof(uint8_t),4,p_file);
		m_colors[l_index] = new my_color_alpha(l_byte_array[2],l_byte_array[1],l_byte_array[0],l_byte_array[3]);
	      }
	  }
	else
	  {

	    switch(p_size)
	      {
	      case 2:
		m_colors[0] = new my_color_alpha(0,0,0,0);
		m_colors[1] = new my_color_alpha(255,255,255,0);
		break;
	      case 16:
		m_colors[0] = new my_color_alpha(  0,   0,   0,   0);
		m_colors[1] = new my_color_alpha(128,  0,  0,   0);
		m_colors[2] = new my_color_alpha(  0,128,  0,   0);
		m_colors[3] = new my_color_alpha(128,128,  0,   0);
		m_colors[4] = new my_color_alpha(  0,  0,128,   0);
		m_colors[5] = new my_color_alpha(128,  0,128,   0);
		m_colors[6] = new my_color_alpha(  0,128,128,   0);
		m_colors[7] = new my_color_alpha(128,128,128,   0);
		m_colors[8] = new my_color_alpha(192,192,192,   0);
		m_colors[9] = new my_color_alpha(255,  0,  0,   0);
		m_colors[10] = new my_color_alpha(  0,255,  0,   0);
		m_colors[11] = new my_color_alpha(255,255,  0,   0);
		m_colors[12] = new my_color_alpha(  0,  0,255,   0);
		m_colors[13] = new my_color_alpha(255,  0,255,   0);
		m_colors[14] = new my_color_alpha(  0,255,255,   0);
		m_colors[15] = new my_color_alpha(255,255,255,   0);
		break;
	      case 256:
		m_colors[0] = new my_color_alpha(  0,  0,  0,   0);
		m_colors[1] = new my_color_alpha(128,  0,  0,   0);
		m_colors[2] = new my_color_alpha(  0,128,  0,   0);
		m_colors[3] = new my_color_alpha(128,128,  0,   0);
		m_colors[4] = new my_color_alpha(  0,  0,128,   0);
		m_colors[5] = new my_color_alpha(128,  0,128,   0);
		m_colors[6] = new my_color_alpha(  0,128,128,   0);
		m_colors[7] = new my_color_alpha(192,192,192,   0);
		m_colors[8] = new my_color_alpha(192,220,192,   0);
		m_colors[9] = new my_color_alpha(166,202,240,   0);
		m_colors[10] = new my_color_alpha( 64, 32,  0,   0);
		m_colors[11] = new my_color_alpha( 96, 32,  0,   0);
		m_colors[12] = new my_color_alpha(128, 32,  0,   0);
		m_colors[13] = new my_color_alpha(160, 32,  0,   0);
		m_colors[14] = new my_color_alpha(192, 32,  0,   0);
		m_colors[15] = new my_color_alpha(224, 32,  0,   0);
		m_colors[16] = new my_color_alpha(  0, 64,  0,   0);
		m_colors[17] = new my_color_alpha( 32, 64,  0,   0);
		m_colors[18] = new my_color_alpha( 64, 64,  0,   0);
		m_colors[19] = new my_color_alpha( 96, 64,  0,   0);
		m_colors[20] = new my_color_alpha(128, 64,  0,   0);
		m_colors[21] = new my_color_alpha(160, 64,  0,   0);
		m_colors[22] = new my_color_alpha(192, 64,  0,   0);
		m_colors[23] = new my_color_alpha(224, 64,  0,   0);
		m_colors[24] = new my_color_alpha(  0, 96,  0,   0);
		m_colors[25] = new my_color_alpha( 32, 96,  0,   0);
		m_colors[26] = new my_color_alpha( 64, 96,  0,   0);
		m_colors[27] = new my_color_alpha( 96, 96,  0,   0);
		m_colors[28] = new my_color_alpha(128, 96,  0,   0);
		m_colors[29] = new my_color_alpha(160, 96,  0,   0);
		m_colors[30] = new my_color_alpha(192, 96,  0,   0);
		m_colors[31] = new my_color_alpha(224, 96,  0,   0);
		m_colors[32] = new my_color_alpha(  0,128,  0,   0);
		m_colors[33] = new my_color_alpha( 32,128,  0,   0);
		m_colors[34] = new my_color_alpha( 64,128,  0,   0);
		m_colors[35] = new my_color_alpha( 96,128,  0,   0);
		m_colors[36] = new my_color_alpha(128,128,  0,   0);
		m_colors[37] = new my_color_alpha(160,128,  0,   0);
		m_colors[38] = new my_color_alpha(192,128,  0,   0);
		m_colors[39] = new my_color_alpha(224,128,  0,   0);
		m_colors[40] = new my_color_alpha(  0,160,  0,   0);
		m_colors[41] = new my_color_alpha( 32,160,  0,   0);
		m_colors[42] = new my_color_alpha( 64,160,  0,   0);
		m_colors[43] = new my_color_alpha( 96,160,  0,   0);
		m_colors[44] = new my_color_alpha(128,160,  0,   0);
		m_colors[45] = new my_color_alpha(160,160,  0,   0);
		m_colors[46] = new my_color_alpha(192,160,  0,   0);
		m_colors[47] = new my_color_alpha(224,160,  0,   0);
		m_colors[48] = new my_color_alpha(  0,192,  0,   0);
		m_colors[49] = new my_color_alpha( 32,192,  0,   0);
		m_colors[50] = new my_color_alpha( 64,192,  0,   0);
		m_colors[51] = new my_color_alpha( 96,192,  0,   0);
		m_colors[52] = new my_color_alpha(128,192,  0,   0);
		m_colors[53] = new my_color_alpha(160,192,  0,   0);
		m_colors[54] = new my_color_alpha(192,192,  0,   0);
		m_colors[55] = new my_color_alpha(224,192,  0,   0);
		m_colors[56] = new my_color_alpha(  0,224,  0,   0);
		m_colors[57] = new my_color_alpha( 32,224,  0,   0);
		m_colors[58] = new my_color_alpha( 64,224,  0,   0);
		m_colors[59] = new my_color_alpha( 96,224,  0,   0);
		m_colors[60] = new my_color_alpha(128,224,  0,   0);
		m_colors[61] = new my_color_alpha(160,224,  0,   0);
		m_colors[62] = new my_color_alpha(192,224,  0,   0);
		m_colors[63] = new my_color_alpha(224,224,  0,   0);
		m_colors[64] = new my_color_alpha(  0,  0, 64,   0);
		m_colors[65] = new my_color_alpha( 32,  0, 64,   0);
		m_colors[66] = new my_color_alpha( 64,  0, 64,   0);
		m_colors[67] = new my_color_alpha( 96,  0, 64,   0);
		m_colors[68] = new my_color_alpha(128,  0, 64,   0);
		m_colors[69] = new my_color_alpha(160,  0, 64,   0);
		m_colors[70] = new my_color_alpha(192,  0, 64,   0);
		m_colors[71] = new my_color_alpha(224,  0, 64,   0);
		m_colors[72] = new my_color_alpha(  0, 32, 64,   0);
		m_colors[73] = new my_color_alpha( 32, 32, 64,   0);
		m_colors[74] = new my_color_alpha( 64, 32, 64,   0);
		m_colors[75] = new my_color_alpha( 96, 32, 64,   0);
		m_colors[76] = new my_color_alpha(128, 32, 64,   0);
		m_colors[77] = new my_color_alpha(160, 32, 64,   0);
		m_colors[78] = new my_color_alpha(192, 32, 64,   0);
		m_colors[79] = new my_color_alpha(224, 32, 64,   0);
		m_colors[80] = new my_color_alpha(  0, 64, 64,   0);
		m_colors[81] = new my_color_alpha( 32, 64, 64,   0);
		m_colors[82] = new my_color_alpha( 64, 64, 64,   0);
		m_colors[83] = new my_color_alpha( 96, 64, 64,   0);
		m_colors[84] = new my_color_alpha(128, 64, 64,   0);
		m_colors[85] = new my_color_alpha(160, 64, 64,   0);
		m_colors[86] = new my_color_alpha(192, 64, 64,   0);
		m_colors[87] = new my_color_alpha(224, 64, 64,   0);
		m_colors[88] = new my_color_alpha(  0, 96, 64,   0);
		m_colors[89] = new my_color_alpha( 32, 96, 64,   0);
		m_colors[90] = new my_color_alpha( 64, 96, 64,   0);
		m_colors[91] = new my_color_alpha( 96, 96, 64,   0);
		m_colors[92] = new my_color_alpha(128, 96, 64,   0);
		m_colors[93] = new my_color_alpha(160, 96, 64,   0);
		m_colors[94] = new my_color_alpha(192, 96, 64,   0);
		m_colors[95] = new my_color_alpha(224, 96, 64,   0);
		m_colors[96] = new my_color_alpha(  0,128, 64,   0);
		m_colors[97] = new my_color_alpha( 32,128, 64,   0);
		m_colors[98] = new my_color_alpha( 64,128, 64,   0);
		m_colors[99] = new my_color_alpha( 96,128, 64,   0);
		m_colors[100] = new my_color_alpha(128,128, 64,   0);
		m_colors[101] = new my_color_alpha(160,128, 64,   0);
		m_colors[102] = new my_color_alpha(192,128, 64,   0);
		m_colors[103] = new my_color_alpha(224,128, 64,   0);
		m_colors[104] = new my_color_alpha(  0,160, 64,   0);
		m_colors[105] = new my_color_alpha( 32,160, 64,   0);
		m_colors[106] = new my_color_alpha( 64,160, 64,   0);
		m_colors[107] = new my_color_alpha( 96,160, 64,   0);
		m_colors[108] = new my_color_alpha(128,160, 64,   0);
		m_colors[109] = new my_color_alpha(160,160, 64,   0);
		m_colors[110] = new my_color_alpha(192,160, 64,   0);
		m_colors[111] = new my_color_alpha(224,160, 64,   0);
		m_colors[112] = new my_color_alpha(  0,192, 64,   0);
		m_colors[113] = new my_color_alpha( 32,192, 64,   0);
		m_colors[114] = new my_color_alpha( 64,192, 64,   0);
		m_colors[115] = new my_color_alpha( 96,192, 64,   0);
		m_colors[116] = new my_color_alpha(128,192, 64,   0);
		m_colors[117] = new my_color_alpha(160,192, 64,   0);
		m_colors[118] = new my_color_alpha(192,192, 64,   0);
		m_colors[119] = new my_color_alpha(224,192, 64,   0);
		m_colors[120] = new my_color_alpha(  0,224, 64,   0);
		m_colors[121] = new my_color_alpha( 32,224, 64,   0);
		m_colors[122] = new my_color_alpha( 64,224, 64,   0);
		m_colors[123] = new my_color_alpha( 96,224, 64,   0);
		m_colors[124] = new my_color_alpha(128,224, 64,   0);
		m_colors[125] = new my_color_alpha(160,224, 64,   0);
		m_colors[126] = new my_color_alpha(192,224, 64,   0);
		m_colors[127] = new my_color_alpha(224,224, 64,   0);
		m_colors[128] = new my_color_alpha(  0,  0,128,   0);
		m_colors[129] = new my_color_alpha( 32,  0,128,   0);
		m_colors[130] = new my_color_alpha( 64,  0,128,   0);
		m_colors[131] = new my_color_alpha( 96,  0,128,   0);
		m_colors[132] = new my_color_alpha(128,  0,128,   0);
		m_colors[133] = new my_color_alpha(160,  0,128,   0);
		m_colors[134] = new my_color_alpha(192,  0,128,   0);
		m_colors[135] = new my_color_alpha(224,  0,128,   0);
		m_colors[136] = new my_color_alpha(  0, 32,128,   0);
		m_colors[137] = new my_color_alpha( 32, 32,128,   0);
		m_colors[138] = new my_color_alpha( 64, 32,128,   0);
		m_colors[139] = new my_color_alpha( 96, 32,128,   0);
		m_colors[140] = new my_color_alpha(128, 32,128,   0);
		m_colors[141] = new my_color_alpha(160, 32,128,   0);
		m_colors[142] = new my_color_alpha(192, 32,128,   0);
		m_colors[143] = new my_color_alpha(224, 32,128,   0);
		m_colors[144] = new my_color_alpha(  0, 64,128,   0);
		m_colors[145] = new my_color_alpha( 32, 64,128,   0);
		m_colors[146] = new my_color_alpha( 64, 64,128,   0);
		m_colors[147] = new my_color_alpha( 96, 64,128,   0);
		m_colors[148] = new my_color_alpha(128, 64,128,   0);
		m_colors[149] = new my_color_alpha(160, 64,128,   0);
		m_colors[150] = new my_color_alpha(192, 64,128,   0);
		m_colors[151] = new my_color_alpha(224, 64,128,   0);
		m_colors[152] = new my_color_alpha(  0, 96,128,   0);
		m_colors[153] = new my_color_alpha( 32, 96,128,   0);
		m_colors[154] = new my_color_alpha( 64, 96,128,   0);
		m_colors[155] = new my_color_alpha( 96, 96,128,   0);
		m_colors[156] = new my_color_alpha(128, 96,128,   0);
		m_colors[157] = new my_color_alpha(160, 96,128,   0);
		m_colors[158] = new my_color_alpha(192, 96,128,   0);
		m_colors[159] = new my_color_alpha(224, 96,128,   0);
		m_colors[160] = new my_color_alpha(  0,128,128,   0);
		m_colors[161] = new my_color_alpha( 32,128,128,   0);
		m_colors[162] = new my_color_alpha( 64,128,128,   0);
		m_colors[163] = new my_color_alpha( 96,128,128,   0);
		m_colors[164] = new my_color_alpha(128,128,128,   0);
		m_colors[165] = new my_color_alpha(160,128,128,   0);
		m_colors[166] = new my_color_alpha(192,128,128,   0);
		m_colors[167] = new my_color_alpha(224,128,128,   0);
		m_colors[168] = new my_color_alpha(  0,160,128,   0);
		m_colors[169] = new my_color_alpha( 32,160,128,   0);
		m_colors[170] = new my_color_alpha( 64,160,128,   0);
		m_colors[171] = new my_color_alpha( 96,160,128,   0);
		m_colors[172] = new my_color_alpha(128,160,128,   0);
		m_colors[173] = new my_color_alpha(160,160,128,   0);
		m_colors[174] = new my_color_alpha(192,160,128,   0);
		m_colors[175] = new my_color_alpha(224,160,128,   0);
		m_colors[176] = new my_color_alpha(  0,192,128,   0);
		m_colors[177] = new my_color_alpha( 32,192,128,   0);
		m_colors[178] = new my_color_alpha( 64,192,128,   0);
		m_colors[179] = new my_color_alpha( 96,192,128,   0);
		m_colors[180] = new my_color_alpha(128,192,128,   0);
		m_colors[181] = new my_color_alpha(160,192,128,   0);
		m_colors[182] = new my_color_alpha(192,192,128,   0);
		m_colors[183] = new my_color_alpha(224,192,128,   0);
		m_colors[184] = new my_color_alpha(  0,224,128,   0);
		m_colors[185] = new my_color_alpha( 32,224,128,   0);
		m_colors[186] = new my_color_alpha( 64,224,128,   0);
		m_colors[187] = new my_color_alpha( 96,224,128,   0);
		m_colors[188] = new my_color_alpha(128,224,128,   0);
		m_colors[189] = new my_color_alpha(160,224,128,   0);
		m_colors[190] = new my_color_alpha(192,224,128,   0);
		m_colors[191] = new my_color_alpha(224,224,128,   0);
		m_colors[192] = new my_color_alpha(  0,  0,192,   0);
		m_colors[193] = new my_color_alpha( 32,  0,192,   0);
		m_colors[194] = new my_color_alpha( 64,  0,192,   0);
		m_colors[195] = new my_color_alpha( 96,  0,192,   0);
		m_colors[196] = new my_color_alpha(128,  0,192,   0);
		m_colors[197] = new my_color_alpha(160,  0,192,   0);
		m_colors[198] = new my_color_alpha(192,  0,192,   0);
		m_colors[199] = new my_color_alpha(224,  0,192,   0);
		m_colors[200] = new my_color_alpha(  0, 32,192,   0);
		m_colors[201] = new my_color_alpha( 32, 32,192,   0);
		m_colors[202] = new my_color_alpha( 64, 32,192,   0);
		m_colors[203] = new my_color_alpha( 96, 32,192,   0);
		m_colors[204] = new my_color_alpha(128, 32,192,   0);
		m_colors[205] = new my_color_alpha(160, 32,192,   0);
		m_colors[206] = new my_color_alpha(192, 32,192,   0);
		m_colors[207] = new my_color_alpha(224, 32,192,   0);
		m_colors[208] = new my_color_alpha(  0, 64,192,   0);
		m_colors[209] = new my_color_alpha( 32, 64,192,   0);
		m_colors[210] = new my_color_alpha( 64, 64,192,   0);
		m_colors[211] = new my_color_alpha( 96, 64,192,   0);
		m_colors[212] = new my_color_alpha(128, 64,192,   0);
		m_colors[213] = new my_color_alpha(160, 64,192,   0);
		m_colors[214] = new my_color_alpha(192, 64,192,   0);
		m_colors[215] = new my_color_alpha(224, 64,192,   0);
		m_colors[216] = new my_color_alpha(  0, 96,192,   0);
		m_colors[217] = new my_color_alpha( 32, 96,192,   0);
		m_colors[218] = new my_color_alpha( 64, 96,192,   0);
		m_colors[219] = new my_color_alpha( 96, 96,192,   0);
		m_colors[220] = new my_color_alpha(128, 96,192,   0);
		m_colors[221] = new my_color_alpha(160, 96,192,   0);
		m_colors[222] = new my_color_alpha(192, 96,192,   0);
		m_colors[223] = new my_color_alpha(224, 96,192,   0);
		m_colors[224] = new my_color_alpha(  0,128,192,   0);
		m_colors[225] = new my_color_alpha( 32,128,192,   0);
		m_colors[226] = new my_color_alpha( 64,128,192,   0);
		m_colors[227] = new my_color_alpha( 96,128,192,   0);
		m_colors[228] = new my_color_alpha(128,128,192,   0);
		m_colors[229] = new my_color_alpha(160,128,192,   0);
		m_colors[230] = new my_color_alpha(192,128,192,   0);
		m_colors[231] = new my_color_alpha(224,128,192,   0);
		m_colors[232] = new my_color_alpha(  0,160,192,   0);
		m_colors[233] = new my_color_alpha( 32,160,192,   0);
		m_colors[234] = new my_color_alpha( 64,160,192,   0);
		m_colors[235] = new my_color_alpha( 96,160,192,   0);
		m_colors[236] = new my_color_alpha(128,160,192,   0);
		m_colors[237] = new my_color_alpha(160,160,192,   0);
		m_colors[238] = new my_color_alpha(192,160,192,   0);
		m_colors[239] = new my_color_alpha(224,160,192,   0);
		m_colors[240] = new my_color_alpha(  0,192,192,   0);
		m_colors[241] = new my_color_alpha( 32,192,192,   0);
		m_colors[242] = new my_color_alpha( 64,192,192,   0);
		m_colors[243] = new my_color_alpha( 96,192,192,   0);
		m_colors[244] = new my_color_alpha(128,192,192,   0);
		m_colors[245] = new my_color_alpha(160,192,192,   0);
		m_colors[246] = new my_color_alpha(255,251,240,   0);
		m_colors[247] = new my_color_alpha(160,160,164,   0);
		m_colors[248] = new my_color_alpha(128,128,128,   0);
		m_colors[249] = new my_color_alpha(255,  0,  0,   0);
		m_colors[250] = new my_color_alpha(  0,255,  0,   0);
		m_colors[251] = new my_color_alpha(255,255,  0,   0);
		m_colors[252] = new my_color_alpha(  0,  0,255,   0);
		m_colors[253] = new my_color_alpha(255,  0,255,   0);
		m_colors[254] = new my_color_alpha(  0,255,255,   0);
		m_colors[255] = new my_color_alpha(255,255,255,   0);
		break;
	      default:
		std::cout << "ERROR : palette of size "<< m_size << " is not supported"<< std::endl ;
		exit(-1);
	      }
	    
	  }
      }
    
    void save(FILE *p_file)
    {
      uint8_t l_byte_array[4];
      for(uint32_t l_index = 0 ; l_index < m_size; ++l_index)
	{
	  my_color_alpha & l_color = *(m_colors[l_index]);
	  l_byte_array[2] = l_color.get_red();
	  l_byte_array[1] = l_color.get_green();
          l_byte_array[0] = l_color.get_blue();
          l_byte_array[3] = l_color.get_alpha();
	  fwrite(l_byte_array,sizeof(uint8_t),4,p_file);

	}
    }

    const uint32_t get_index(const my_color_alpha & p_color)const
    {
      uint32_t l_result = 0;
      uint32_t l_index =0;
      double l_min_dist = 9999999;
      while(l_min_dist && l_index < m_size)
    	{
    	  double l_dist = pow(((int32_t)m_colors[l_index]->get_red())-((int32_t)p_color.get_red()),2)+
	    pow(((int32_t)m_colors[l_index]->get_green())-((int32_t)p_color.get_green()),2)+
	    pow(((int32_t)m_colors[l_index]->get_blue())-((int32_t)p_color.get_blue()),2);
    	  if(l_dist < l_min_dist)
    	    {
	      l_min_dist = l_dist;
    	      l_result = l_index;
    	    }
    	  ++l_index;
    	}
      return l_result;
    }

    const my_color_alpha & get_color(uint32_t p_index)
      {
	assert(p_index < m_size);
	return *(m_colors[p_index]);

      }

    void set_color(const my_color_alpha & p_color,uint32_t p_index)
    {
	assert(p_index < m_size);
	*(m_colors[p_index]) = p_color;
      
    }

    void display(void)const
    {
      std::cout << "Palette :" << std::endl ;
      for(uint32_t l_index = 0 ; l_index < m_size; ++l_index)
	{
	  std::cout << "Color[" << l_index << "] = " ;
	  m_colors[l_index]->display();
	  std::cout << std::endl ;
	}
      
    }

    ~my_palette(void)
      {
	for(uint32_t l_index = 0 ; l_index < m_size; ++l_index)
	  {
	    delete m_colors[l_index];
	  }
	delete[] m_colors;
      }
 private:
    uint32_t m_size;
    my_color_alpha ** m_colors;
  
};

class my_bmp
{
 public:
  my_bmp(uint32_t p_width,uint32_t p_height,uint32_t p_nb_bits_per_pixel):
    m_header(new my_bmp_header(p_width,p_height,p_nb_bits_per_pixel,get_default_palette_size(p_nb_bits_per_pixel))),
    m_palette(NULL),
    m_content(NULL)
      {
	create_palette();
	create_content();
      }

    my_bmp(const std::string & p_name):
      m_header(NULL),
      m_palette(NULL),
      m_content(NULL)
	{
	  FILE * l_file= fopen(p_name.c_str(),"r");
	  if(l_file == NULL)
	    {
	      std::cout << "ERROR : Unable to open file \"" << p_name << std::endl ;
	      exit(-1);
	    }

	  m_header = new my_bmp_header(l_file);

	  create_palette(l_file);

	  create_content();

	  // Create temporary buffer containing code picture content 
	  uint8_t * l_tmp_content = new uint8_t[m_header->get_picture_size()];
	  fread(l_tmp_content,m_header->get_picture_size(),1,l_file);

	  // Use coded picture to fill the RGB array representing pixels
	  uint16_t l_nb_bits = m_header->get_nb_bits_per_pixel();
	  uint32_t l_width = m_header->get_width();
	  uint32_t l_height = m_header->get_height();
	  for(uint32_t l_y = 0 ; l_y < l_height ; ++l_y)
	    {
	      for(uint32_t l_x = 0 ; l_x < l_width ; ++l_x)
		{
		  my_color_alpha & l_color = access_pixel(l_x,l_y);
		  uint32_t l_index= get_pixel_index(l_x,l_y,l_width,l_height,l_nb_bits);
		  uint32_t l_bit_index= get_pixel_bit_index(l_x,l_y,l_nb_bits);

		  switch(l_nb_bits)
		    {
		    case 1:
		      l_color = m_palette->get_color(((l_tmp_content[l_index])>>(7-l_bit_index))&1);
		      break;
		    case 4:
		      l_color = m_palette->get_color(((l_tmp_content[l_index])>>(4-l_bit_index))&15);
		      break;
		    case 8 :
		      l_color = m_palette->get_color(l_tmp_content[l_index]);
		      break;
		    case 16:
		      std::cout << "ERROR : 16 bits per pixel is not supported" << std::endl ;
		      exit(-1);
		      break;
		    case 24:
		      l_color.set_red(l_tmp_content[l_index+2]);
		      l_color.set_green(l_tmp_content[l_index+1]);
		      l_color.set_blue(l_tmp_content[l_index]);
		      break;
		    default:
		      std::cout << "ERROR : wrong value for field nb bits per pixel " << l_nb_bits << std::endl ;
		      exit(-1);
		    }
  
		}
	    }
	  
	  delete[] l_tmp_content;
	  fclose(l_file);


	  
	}

      inline uint32_t get_width(void)const
	{
	  return m_header->get_width();
	}

      inline uint32_t get_height(void)const
	{
	  return m_header->get_height();
	}

      static inline uint32_t get_default_palette_size(uint32_t p_nb_bits)
      {
	return (p_nb_bits >= 16 ? 0 : 1 << p_nb_bits);
      }

      void save(const std::string & p_name)const
      {
	FILE * l_file= fopen(p_name.c_str(),"w");
	if(l_file == NULL)
	  {
	    std::cout << "ERROR : Unable to open file \"" << p_name << std::endl ;
	    exit(-1);
	  }

	m_header->save(l_file);
	if(m_palette) m_palette->save(l_file);

	// Create temporary buffer containing code picture content 
	uint8_t * l_tmp_content = new uint8_t[m_header->get_picture_size()];

	// Use RGB array representing pixelsto fill the coded picture 
	uint16_t l_nb_bits = m_header->get_nb_bits_per_pixel();
	uint32_t l_width = m_header->get_width();
	uint32_t l_height = m_header->get_height();
	for(uint32_t l_y = 0 ; l_y < l_height ; ++l_y)
	  {
	    for(uint32_t l_x = 0 ; l_x < l_width ; ++l_x)
	      {
		my_color_alpha & l_color = access_pixel(l_x,l_y);
		uint32_t l_index= get_pixel_index(l_x,l_y,l_width,l_height,l_nb_bits);
		uint32_t l_bit_index= get_pixel_bit_index(l_x,l_y,l_nb_bits);

		switch(l_nb_bits)
		  {

		  case 1:
		    if(m_palette->get_index(l_color))
		      {
			l_tmp_content[l_index]=(l_tmp_content[l_index])|(1<<(7-l_bit_index));
		      }
		    else
		      {
			l_tmp_content[l_index]=(l_tmp_content[l_index])&(~(1<<(7-l_bit_index)));
		      }
		    break;
		  case 4:
		    l_tmp_content[l_index]=(l_tmp_content[l_index])&(~(15<<(4-l_bit_index)));
		      
		    l_tmp_content[l_index]=(l_tmp_content[l_index])|((m_palette->get_index(l_color))<<(4-l_bit_index));
		    break;
		  case 8:
		    l_tmp_content[l_index]=m_palette->get_index(l_color);
		    break;
		  case 16:
		    std::cout << "ERROR : 16 bits per pixel is not supported" << std::endl ;
		    exit(-1);
		    break;
		  case 24:
		    l_tmp_content[l_index+2] = l_color.get_red();
		    l_tmp_content[l_index+1] = l_color.get_green();
		    l_tmp_content[l_index] = l_color.get_blue();
		    break;
		  default:
		    std::cout << "ERROR : wrong value for field nb bits per pixel " << l_nb_bits << std::endl ;
		    exit(-1);
		  }
	      }
	  }
	fwrite(l_tmp_content,m_header->get_picture_size(),1,l_file);

	fclose(l_file);
      }

      const my_color_alpha & get_pixel_color(uint32_t p_x,uint32_t p_y)const
	{
	  return access_pixel(p_x,p_y);
	}

      void set_pixel_color(uint32_t p_x,uint32_t p_y,const my_color_alpha &p_color)const
	{
	  access_pixel(p_x,p_y) = p_color;
	}

      void display_info(void)const
      {
	m_header->display();
	if(m_palette) m_palette->display();
      }

      ~my_bmp(void)
	{
	  delete m_header;
	  delete m_palette;
	  delete[] m_content;
	}
 private:
      inline uint32_t get_pixel_index(uint32_t p_x,uint32_t p_y,uint32_t p_width,uint32_t p_height,uint32_t p_nb_bits)const
	{
	  return((p_x * p_nb_bits) / 8 + 4 * (p_height - p_y - 1)*(uint32_t)ceil((p_width * p_nb_bits)/32.0));
	}

      inline uint32_t get_pixel_bit_index(uint32_t p_x,uint32_t p_y,uint32_t p_nb_bits)const
	{
	  return ((p_x * p_nb_bits) % 8);
	}

      inline my_color_alpha & access_pixel(uint32_t p_x,uint32_t p_y)const
	{
	  return m_content[m_header->get_width() * p_y + p_x];
	}

      inline void create_content(void)
	{
	  m_content = new my_color_alpha[m_header->get_width() * m_header->get_height()];
	}

      void create_palette(FILE *p_file=NULL)
      {
	uint32_t l_palette_size = m_header->get_palette_size();
	if(l_palette_size)
	  {
	    m_palette = new my_palette(l_palette_size,p_file);
	  }
      }
      my_bmp_header *m_header;
      my_palette *m_palette;
      my_color_alpha * m_content;
};
//EOF
