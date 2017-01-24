#include <Humblesoft_GFX.h>

Humblesoft_GFX::Humblesoft_GFX(int16_t w, int16_t h): Adafruit_GFX(w,h) {
  m_spaceX = 0;
  m_spaceY = 0;
  m_fontx = NULL;
}

void Humblesoft_GFX::setFont(Fontx *fontx)
{
  m_fontx = fontx;
  if(gfxFont){
    cursor_y -= 6;
    gfxFont = NULL;
  }
}

void Humblesoft_GFX::setFont(const GFXfont *f)
{
  m_fontx = NULL;
  Adafruit_GFX::setFont(f);
}

size_t Humblesoft_GFX::write(uint8_t c)
{
  if(!m_fontx) {
    if(!gfxFont) { // 'Classic' built-in font
      if(c == '\n') {
	cursor_y += textsize*(m_spaceY + 8);
	cursor_x  = 0;
	lineFeedHook(&cursor_x, &cursor_y, textsize*(m_spaceY+8));
      } else if(c == '\r') {
	// skip em
      } else {
	if(wrap && ((cursor_x + textsize * 6) >= _width)) { // Heading off edge?
	  cursor_x  = 0;            // Reset x to zero
	  cursor_y += textsize * 8; // Advance y one line
	  lineFeedHook(&cursor_x, &cursor_y, textsize*8);
	}
	drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
	cursor_x += textsize * 6;
      }
    } else { // Custom font
      if(c == '\n') {
	cursor_x  = 0;
	int16_t lh = (int16_t)textsize *
	  ((uint8_t)pgm_read_byte(&gfxFont->yAdvance) + m_spaceY); 
	cursor_y += lh;
	lineFeedHook(&cursor_x, &cursor_y, lh);
      } else if(c != '\r') {
	uint8_t first = pgm_read_byte(&gfxFont->first);
	if((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last))) {
	  uint8_t   c2    = c - pgm_read_byte(&gfxFont->first);
	  GFXglyph *glyph =
	    &(((GFXglyph *)pgm_read_dword(&gfxFont->glyph))[c2]);
	  uint8_t w = pgm_read_byte(&glyph->width);
	  uint8_t h = pgm_read_byte(&glyph->height);
	  if((w > 0) && (h > 0)) { // Is there an associated bitmap?
	    int16_t xo = (int8_t)pgm_read_byte(&glyph->xOffset); // sic
	    if(wrap && ((cursor_x + textsize * (xo + w)) >= _width)) {
	      // Drawing character would go off right edge; wrap to new line
	      cursor_x  = 0;
	      cursor_y += (int16_t)textsize *
		(uint8_t)pgm_read_byte(&gfxFont->yAdvance);
	    }
	    drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
	  }
	  cursor_x += pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
	}
      }
    }
    
  } else {
    process_utf8_byte(c, &cursor_x, &cursor_y, textsize, wrap, textcolor,
		      textbgcolor);
  }
  return 1;
}


void Humblesoft_GFX::process_utf8_byte(uint8_t c, int16_t *pX, int16_t *pY,
				 uint8_t textsize, bool wrap,
				 uint16_t fg, uint16_t bg,
				 bool bDraw, int16_t *pX2)
{
  uint32_t ucode;
  const uint8_t *glyph;
  uint8_t w,h;
  uint8_t s = textsize < 1 ? 0 : textsize;
  
  if(pX2) *pX2 = *pX;
  
  if(c == '\n'){
    uint8_t h;
    if(m_fontx->getGlyph(' ', NULL, NULL, &h))
      *pY += (h + m_spaceY) * s;
    *pX = 0;
    lineFeedHook(pX, pY, (h + m_spaceY) * s);
  }
  else {
    if(m_u8d.decode(c, &ucode) && m_fontx->getGlyph(ucode, &glyph, &w, &h)){
      if(wrap && (*pX + (w + m_spaceX) * s > _width)){
	*pX = 0;
	if(pX2) *pX2 = 0;
	*pY += (h + m_spaceY) * s;
	lineFeedHook(pX, pY, (h + m_spaceY * s));
      }
      if(bDraw)
	drawFontxGlyph(glyph, w, h, *pX, *pY, textsize, wrap, fg, bg);
      *pX += (w + m_spaceX) * textsize;
    }
  }
}


void
Humblesoft_GFX::drawFontxGlyph(const uint8_t *glyph,uint8_t w,uint8_t h,
			       uint16_t cx, uint16_t cy,
			       uint8_t textsize, boolean /* wrap */,
			       uint16_t textcolor, uint16_t textbgcolor)
{
  const uint8_t *gp;
  uint8_t x,y;
  uint16_t xp, yp;
  uint8_t s = textsize < 1 ? 0 : textsize;

  if(glyph == NULL) return;
  
  gp = glyph;
  yp = cy;
  for (y = 0; y < h; y++) {
    xp = cx;
    for (x = 0; x < w; x += 8) {
      uint8_t d = pgm_read_byte(&gp[x / 8]);
      for (int i = 0, m = 0x80; i < 8 && i + x < w; i++, m >>= 1) {
	if (d & m)
	  fillRect(xp, yp, s, s , textcolor);
	else if(textcolor != textbgcolor)
	  fillRect(xp, yp, s, s , textbgcolor);
	xp += s;
      }
    }
    gp += (w + 7) / 8;
    yp += s;
  }
}


void Humblesoft_GFX::getTextBounds(char *string, int16_t x0, int16_t y0,
				   int16_t *x1, int16_t *y1,
				   uint16_t *w, uint16_t *h)
{
  if(!m_fontx)
    Adafruit_GFX::getTextBounds(string, x0, y0, x1, y1, w, h);
  else {
    char *p = string;
    int16_t x,y,max_x,max_y,min_x,min_y,x2;

    x = min_x = max_x = x2 = x0;
    y = min_y = max_y = y0;
    while(*p){
      process_utf8_byte(*p++, &x, &y, textsize, wrap, 0, 0, false, &x2);

      if(x < min_x) min_x = x;
      if(x > max_x) max_x = x;
      if(x2 < min_x) min_x = x2;
      if(x2 > max_x) max_x = x2;
      if(y < min_y) min_y = y;
      if(y > max_y) max_y = y;
    }

    uint8_t th;
    if(m_fontx->getGlyph(' ', NULL, NULL, &th))
      max_y += th * textsize;

    *x1 = min_x;
    *y1 = min_y;
    *w = max_x > min_x ? max_x - min_x - 1 : 0;
    *h = max_y > min_y ? max_y - min_y - 1 : 0;
  }
}

void Humblesoft_GFX::posPrintf(int16_t x,int16_t y,const char *fmt,...)
{
  va_list ap;
  char buf[80];
  
  va_start(ap, fmt);
  vsnprintf(buf,sizeof buf,fmt,ap);
  va_end(ap);

  setCursor(x,y);
  print(buf);
}

void Humblesoft_GFX::alignPrintf(int16_t x,int16_t y,TextAlign hAlign,
				 TextAlign vAlign,const char *fmt,...)
{
  va_list ap;
  char buf[80];
  int16_t tx,ty;
  uint16_t tw,th;
  
  va_start(ap, fmt);
  vsnprintf(buf,sizeof buf,fmt,ap);
  va_end(ap);

  getTextBounds(buf, 0, 0, &tx, &ty, &tw, &th);
  
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  
  switch(hAlign){
  case TA_LEFT:    			break;
  case TA_CENTER:	x -= tw/2;    	break;
  case TA_RIGHT:  	x -= tw;	break;
  }
  switch(vAlign){
  case TA_TOP:				break;
  case TA_CENTER:	y -= th/2;	break;
  case TA_BOTTOM:	y -= th/2;	break;
  }

#pragma GCC diagnostic pop  
  setCursor(x,y);
  print(buf);
}


