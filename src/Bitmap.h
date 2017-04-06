#ifndef _bitmap_h_
#define _bitmap_h_

#include <Humblesoft_GFX.h>

class Bitmap : public Humblesoft_GFX {
 protected:
  uint16_t m_bpl;	/* byte per line */
  uint16_t m_bufsize;
  uint8_t *m_buffer; 
  
 public:
  Bitmap(uint16_t w, uint16_t h);
  ~Bitmap();
  void drawPixel(int16_t x, int16_t y, uint16_t color) override;
  void fillScreen(uint16_t color) override;
  int  getPixel(int16_t x, int16_t y);
};

#endif /* _bitmap_h_ */
