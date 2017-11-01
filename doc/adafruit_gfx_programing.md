## Adafruit_GFXでの描画方法

Adafruit_GFXクラスのオブジェクト gfx があるとして説明する。

### 座標系

座標系はスクリーン左上が原点。
X座標は右方向が正、y座標は下方向が正である。

gfx.setRotation(n) nは0～3で、スクリーンの方向を回転することができる。
値が1増えるごとに90度時計回りに回転する。原点の位置は、回転した後のスクリーンの左上となる。　
gfx.width()とgfx.height()で、それぞれ回転後のスクリーンの幅と高さを得ることができる。

### 図形描画

点は以下のメソッドで描画できる。
colorは描画色を示す16bitの値で、後述する。

``` c
gfx.drawPixel(int16_t x, int16_t y, uint16_t color);
```

端点の座標(x0,y0),(x1,y1)を指定し直線を描画することもできる。

``` c
gfx.drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
```

長方形、円、三角形、角丸長方形についても、
描画(draw...) ,塗り潰し(fill...)のメソッドが準備されている。

``` c
gfx.drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
gfx.fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
gfx.drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
gfx.fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
gfx.drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
gfx.fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
gfx.drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
gfx.fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
```

### bitmapの描画

ビットマップの描画機能もある。
まだ、調べていないので、そのうち書きます。

``` c
gfx.drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
gfx.drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color, uint16_t bg);
gfx.drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color);
gfx.drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
gfx.drawXBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
gfx.drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],   int16_t w, int16_t h);
gfx.drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h);
gfx.drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], const uint8_t mask[],int16_t w, int16_t h);
gfx.drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
gfx.drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
gfx.drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
gfx.drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
gfx.drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
```

### 色の指定

Adafruit_GFXでは16bitの値(uint16_t)で色を指定します。
これはAdafruit_GFXが主に小型カラーグラフィックLCDを
念頭に開発されたためだと思います。

具体的な色指定方法は、Adafruit_GFXクラスを継承する実際の
デバイス用のクラスに任されています。

### 文字描画

Adafruit_GFXクラスはPrintクラスを継承しているので、
print(),println(), esp8266-arduinoであればprintf()も使用できます。

#### フォントの指定

Adafruit_GFXのデフォルトのフォントは
5x7dotのサイズ固定のフォントです。

setTextSize()メソッドで、何倍かに
拡大して描画することもできます。

``` c
gfx.setTextSize(uint8_t s),
```

Adafruit_GFXではsetFont()メソッドで、
文字描画に使用するフォントを切り替えることができます。

``` c
gfx.setFont(const GFXfont *f = NULL);
```

フォントのデータはヘッダーファイルの形式で
Adafruit_GFXライブラリの
<a href="https://github.com/adafruit/Adafruit-GFX-Library/tree/master/Fonts">Fontsフォルダ</a>に
24dot程度までの様々なサイズ、字形のフォントが
収められています。

以下のような形でプログラムに取り込み、
使用することが出来ます。

``` c
#include <Adafruit_GFX.h>
#include <Fonts/フォント名.h>
...

  gfx.setFont(フォント名);
  gfx.print("Hello");
```

デフォルトのフォントに戻したい場合、
setFont()を引数なしか、NULLを指定して呼び出します。

#### 文字位置

setCursor()メソッドで、文字の描画位置を
指定できます。

``` c
gfx.setCursor(int16_t x, int16_t y);
```

getCursorX(), getCursorY()メソッドで
現在のカーソル位置（文字描画位置）を取得することが
できます。

``` c
int16_t getCursorX(void) const;
int16_t getCursorY(void) const;
```
