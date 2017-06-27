#include "Bitmap.h"

Bitmap::Bitmap(uint16_t w, uint16_t h) : Humblesoft_GFX(w,h)
{
  m_bpl = (w + 7)/8;
  m_bufSize = m_bpl * h;
  m_buffer = (uint8_t *)malloc(m_bufSize);
  m_bAllocated = true;
  if(m_buffer) memset(m_buffer, 0, m_bufSize);
}

Bitmap::Bitmap(uint16_t w, uint16_t h, uint8_t *buf, size_t bufSize)
  : Humblesoft_GFX(w,h)
{
  m_bpl = (w + 7)/8;
  m_bufSize = bufSize;
  m_buffer =  buf;
  m_bAllocated = false;
  if(m_buffer) memset(m_buffer, 0, m_bufSize);
}

Bitmap::~Bitmap()
{
  if(m_buffer && m_bAllocated) free(m_buffer);
}

void Bitmap::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if(m_buffer && x >= 0 && x < _width && y >= 0 && y < _height){
    uint32_t offset = m_bpl * y + x / 8;
    if(offset < m_bufSize){
      uint8_t mask = 1 << (x & 7);
      if(color)
	m_buffer[offset] |= mask;
      else
	m_buffer[offset] &= ~mask;
    }
  }
}

int Bitmap::getPixel(int16_t x, int16_t y)
{
  if(m_buffer && x >= 0 && x < _width && y >= 0 && y < _height){
    uint16_t offset = m_bpl * y + x / 8;
    uint8_t mask = 1 << (x & 7);
    return m_buffer[offset] & mask ? 1 : 0;
  }
  return 0;
}

void Bitmap::fillScreen(uint16_t color)
{
  if(m_buffer)
    memset(m_buffer, 0, m_bufSize);
}

