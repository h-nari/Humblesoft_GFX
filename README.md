# Humbllesoft_GFX
arduino library, inherit Adafruit_GFX, expand functions, Kanji Font drawing ...

Arduino用ライブラリ, Adafruit_GFXを継承し漢字描画機能等を拡張。

## Humblesoft_GFXクラスのメソッド一覧


``` c
// 画面全体をクリア
void clear();

// RGB各成分からcolor値の計算  
uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

// RGB各成分からcolor値の計算、color565()と同じ
static uint16_t rgb(uint32_t d);

// カラー名(eg. "red"や"#ff0000")からcolor値の計算
static uint16_t rgb(const char *color);

// 文字色を色名の文字列で指定
void setTextColor(const char *color);
void setTextColor(const char *fg, const char *bg);

// 色名文字列版の描画メソッド
void fillScreen(const char *color);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, const char *color);

// 文字位置指定付き printf
void posPrintf(int16_t x,int16_t y,const char *fmt,...);

// 文字位置＋align機能付き printf
void alignPrintf(int16_t x,int16_t y,TextAlign hAlign,TextAlign vAlign,const char *fmt,...);

// 文字描画位置の相対移動
void moveCursor(int16_t rx, int16_t ry);
```    

## Adafruit_GFXクラスのメソッド一覧

``` c
// ドットの描画
void drawPixel(int16_t x, int16_t y, uint16_t color);

// 直線の描画
virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

// 垂直線の描画
virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

// 水平線の描画
virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);

// 長方形の描画（枠だけ）
virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

// 長方形の塗り潰し
virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

// 画面全体の塗り潰し
virtual void fillScreen(uint16_t color);

// 描画色()前景色と背景色)の反転
virtual void invertDisplay(boolean i);

// 円の描画
void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

// 円の塗り潰し
void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

// 三角形の描画
void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
int16_t x2, int16_t y2, uint16_t color);

// 三角形の塗り潰し
void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);

// 角丸長方形の描画
void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);

// 角丸長方形の塗り潰し
void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);

// ビットマップの描画
void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);

void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color, uint16_t bg);

void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);

void drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,
int16_t w, int16_t h, uint16_t color, uint16_t bg);

//
void drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);

// 文字の描画
void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,uint16_t bg, uint8_t size);

// write()での文字描画位置指定
void setCursor(int16_t x, int16_t y),

// 文字色の指定（背景は透明)
void setTextColor(uint16_t c);

// 文字色の指定（背景色も指定)
void setTextColor(uint16_t c, uint16_t bg);

// 文字サイズの指定
void setTextSize(uint8_t s);

// 行折り曲げの指定
void setTextWrap(boolean w);

// 描画方向の指定
void setRotation(uint8_t r);

// 文字セットの指定
void cp437(boolean x=true);

// フォントの設定
void setFont(const GFXfont *f = NULL);

// 文字列のサイズの取得
void getTextBounds(char *string, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
void getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y,int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);

// 文字の描画
size_t write(uint8_t);

// 画面高さの取得(rotationの影響を受ける)
int16_t height(void) const;

// 画面幅の取得（rotationの影響を受ける)
int16_t width(void) const;

// 描画方向の取得
uint8_t getRotation(void) const;

// 文字描画x座標の取得
int16_t getCursorX(void) const;

// 文字描画y座標の取得
int16_t getCursorY(void) const;
```
