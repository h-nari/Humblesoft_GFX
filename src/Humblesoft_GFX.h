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
  static uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xf8) << 8)|((g & 0xfc) << 3)|((b & 0xfc) >> 3);// R:5,G:6,B:5
  }

  void clear() {
    fillScreen((uint16_t)0x0000);
    setCursor(0,0);
    setTextColor(0xffff);
    setTextSize(1);
    setFont();
  }

  uint16_t color565(uint8_t r, uint8_t g, uint8_t b) { return(rgb(r,g,b));}
  
  static uint16_t rgb(uint32_t d){
    return rgb(d >> 16, d >> 8, d);
  }
  
  static uint16_t rgb(const char *color);
  
  void setTextColor(int color) {
    Adafruit_GFX::setTextColor(color);
  }
  
  void setTextColor(int fg,int bg) {
    Adafruit_GFX::setTextColor(fg, bg);
  }
  
  void setTextColor(const char *color) {
    setTextColor(rgb(color));
  }
  
  void setTextColor(const char *fg, const char *bg) {
    setTextColor(rgb(fg), rgb(bg));
  }

  void fillScreen(int color) {
    Adafruit_GFX::fillScreen(color);
  }
  
  void fillScreen(const char *color) {
    Adafruit_GFX::fillScreen(rgb(color));
  }

  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, int color){
    Adafruit_GFX::fillRect(x, y, w, h, color);
  }
  
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, const char *color){
    Adafruit_GFX::fillRect(x, y, w, h, rgb(color));
  }
  
  void posPrintf(int16_t x,int16_t y,const char *fmt,...)
    __attribute__ ((format (printf, 4, 5)));
  void alignPrintf(int16_t x,int16_t y,TextAlign hAlign,
		   TextAlign vAlign,const char *fmt,...)
    __attribute__ ((format (printf, 6, 7)));

  void moveCursor(int16_t rx, int16_t ry){
    setCursor(cursor_x + rx, cursor_y + ry );
  }
 protected:
  void process_utf8_byte(uint8_t c, int16_t *pX, int16_t *pY,
			 uint8_t textsize, bool wrap, uint16_t fg, uint16_t bg,
			 bool bDraw = true, int16_t *pX2 = NULL);
  virtual void drawFontxGlyph(const uint8_t *glyph,uint8_t w,uint8_t h,
			      int16_t cx, int16_t cy,
			      uint8_t textsize, boolean wrap,
			      uint16_t textcolor, uint16_t textbgcolor);
  virtual void lineFeedHook(int16_t *, int16_t *, int16_t) {}


};


#endif /* _humblesoft_gfx_h_ */
