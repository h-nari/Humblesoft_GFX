#ifndef _humblesoft_gfx_h_
#define _humblesoft_gfx_h_

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fontx.h>
#include <Utf8Decoder.h>

enum TextAlign { TA_NONE, TA_LEFT, TA_CENTER, TA_RIGHT, TA_TOP, TA_BOTTOM};

class Humblesoft_GFX : public Adafruit_GFX {
 protected:
  Fontx       	*m_fontx;
  Utf8Decoder 	m_u8d;
  int8_t	m_spaceX;
  int8_t	m_spaceY;
 public:
  Humblesoft_GFX(int16_t w, int16_t h);
  void setFont(Fontx *fontx);
  void setFont(const GFXfont *f = NULL);
  void getTextBounds(char *string, int16_t x, int16_t y,
		     int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
  size_t write(uint8_t);
  virtual uint16_t colorRGB(uint8_t r, uint8_t g, uint8_t b) = 0;
  void posPrintf(int16_t x,int16_t y,const char *fmt,...)
    __attribute__ ((format (print,3,4)));
  void alignPrintf(int16_t x,int16_t y,TextAlign hAlign,
		   TextAlign vAlign,const char *fmt,...)
    __attribute__ ((format (print,5,6)));
  
 protected:
  void process_utf8_byte(uint8_t c, int16_t *pX, int16_t *pY,
			 uint8_t textsize, bool wrap, uint16_t fg, uint16_t bg,
			 bool bDraw = true, int16_t *pX2 = NULL);
  void drawFontxGlyph(const uint8_t *glyph,uint8_t w,uint8_t h,
		      uint16_t cx, uint16_t cy,
		      uint8_t textsize, boolean wrap,
		      uint16_t textcolor, uint16_t textbgcolor);
  void virtual lineFeedHook(int16_t *px, int16_t *py, int16_t h) {}

};


#endif /* _humblesoft_gfx_h_ */
