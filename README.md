# Humbllesoft_GFX
arduino library, inherit Adafruit_GFX, expand functions, Kanji Font drawing ...

Arduino用ライブラリ, Adafruit_GFXを継承し漢字描画機能等を拡張。

## 関連文書

* <a href="https://github.com/h-nari/Humblesoft_GFX/blob/master/doc/adafruit_gfx_programing.md">Adafruit_GFXのプログラミング</a>
* <a href="https://github.com/h-nari/Humblesoft_GFX/blob/master/doc/methods.md">Adafruit_GFX,Humblesoft_GFXのメソッド一覧</a>

## 概要

<img src="https://github.com/h-nari/Humblesoft_GFX/blob/master/img/fig171030a1.png?raw=true&2">

Humblesoft_GFXクラスは、Adafruit社提供のAdafruit_GFXクラスに
日本語描画機能と、いくつかの便利な機能を追加したクラスです。

Adafruit_GFXクラスは、様々なグラフィック表示デバイス（小型液晶やOLED等）のライブラリのクラスの親クラスで、図形や文字の描画機能を提供します。
ただし、漢字ひらがな等の日本語描画機能はありませんので、それを追加した
クラスHumblesoft_GFXクラスを作成しました。
Humblesoft_GFXを親クラスとすることで、日本語描画機能つきのライブラリを
各種グラフィック表示デバイス向けに用意に作成することができます。

Humblesoft_GFXを使用しているグラフィックデバイスライブラリの例

* [h-nari/Humblesoft_LedMat:](https://github.com/h-nari/Humblesoft_LedMat "h-nari/Humblesoft_LedMat: arduino library for Humblesoft Led Matrix controller with esp8266")
* [h-nari/Humblesoft_ILI9341](https://github.com/h-nari/Humblesoft_ILI9341 "h-nari/Humblesoft_ILI9341: add some functions to Adaruit_ILI9341")
* [h-nari/Humblesoft_SSD1306](https://github.com/h-nari/Humblesoft_SSD1306 "h-nari/Humblesoft_SSD1306: arduino library for SSD1306, inherit Adafruit_SSD1306 add Kanji drawing feature")

以下では、Adafruit_GFXの使い方(描画方法)、Humblesoft_GFXクラスで拡張された機能
について説明します。

## Adafruit_GFXでの描画方法

- doc/adafruit_gfx_programming.md を御覧ください。

## Humblesoft_GFXで拡張された機能

### 日本語の描画

FONTX形式のフォントを使用して、
日本語（漢字、平仮名、カタカナ等）の描画ができます。

新たに```Fontx```というクラスを作成し、setFont()メソッドで
指定することにより、print(),println(),printf()メソッドで
日本語を描画することができます。文字列のエンコーディングは
utf-8で行います。

Fontxクラスはインターフェースを定義するための抽象クラスで、
実際にはRomFontx , FsFontxクラスでフォントを使用します。

RomFontxは、フォントのデータをプログラム中に配置し、
ROMに書き込みます。プログラムのサイズが大きくなり、
書込に時間がかかるようになるという欠点はありますが、
簡単に使用できます。

FsFontxは、フォントのデータを<a href="https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst">ROM上に作成されたFileSystem</a>から読み出して
使用します。プログラムのサイズが大きくならないので、
書込時間が長くならないというメリットがありますが、
フォントデータをFileSystemに書き込む必要があります。

Fontxクラスの詳細については、
<a href="https://github.com/h-nari/Fontx">
Fontxのgithubのページ</a>に書いていく予定です。

### 色指定の方法

Adafruit_GFXクラスでは、色の指定に 数値(uint16_t)の値で
指定する方法しかなく、少し面倒です。
そこで、色名の文字列で色指定できる方法を準備しました。
文字列を Red:5bit, Green:6bit, Blue:5bitの16bitの値に
変換します。

使用できる色指定は、色名か #rrggbb という形式の '#'で始まり、
6桁の16進数が続く形式です。

色名としては、以下のものが使用できます。
大文字でも小文字でも構いません。

black, white, red, green, blue, yellow, purple, cyan, magenta, navy,darkgreen, darkcyan, maroon, olive, lightgrey, darkgray, orange, greenyellow, pink

文字列による色指定は、下記のメソッドで使用できます。
図形描画に関しては、使用頻度が高い fillScreen()と
fillRect()でのみ使用できます。

``` c
  static uint16_t rgb(const char *color);
  void setTextColor(const char *color);
  void setTextColor(const char *fg, const char *bg);
  void fillScreen(const char *color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,const char *color);
```

### 位置決め付き文字列描画

posPrintf()は、位置指定機能付きprintf()で、setCursor() + printf()と同じことをします。

``` c
  void posPrintf(int16_t x,int16_t y,const char *fmt,...);
```

printf()でデフォルトフォントやFontxのフォントを描画すると
文字列の左位置が指定位置となりますが、
alignPrintf()では、位置指定する文字列の基準位置も指定することができます。

水平方向と垂直方向それぞれに指定することができ、
水平方向は ```TA_LEFT, TA_CENTER, TA_RIGHT``` から、
垂直方向は ```TA_TOP, TA_CENTER, TA_BOTTOM``` から
指定することが出来ます。

``` c
  enum TextAlign { TA_NONE, TA_LEFT, TA_CENTER, TA_RIGHT, TA_TOP, TA_BOTTOM};
  void alignPrintf(int16_t x,int16_t y,TextAlign hAlign, TextAlign vAlign,const char *fmt,...);
```

### 文字列描画位置の相対移動

カーソル位置（文字列描画位置）は
setCursor()メソッドで設定できますが、
現在の位置からの相対位置に動かそうとすると
getCursorX(),getCursorY()なども使わなければ
ならず、若干面倒です。

そこでmoveCursor()メソッドを用意しました。

``` c
void moveCursor(int16_t rx, int16_t ry);
```

# 今後

なにか便利な機能があれば、
今後もHumblesoft_GFXに追加していく
つもりです。
