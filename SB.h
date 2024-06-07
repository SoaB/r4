#ifndef HEADER_A60AE57AA09DF288
#define HEADER_A60AE57AA09DF288

#include <SDL3\SDL.h>
#include <SDL3\SDL_main.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Global variable definition

typedef struct tag_RGBA {
  union {
    struct {
      unsigned char r;
      unsigned char g;
      unsigned char b;
      unsigned char a;
    };
    uint32_t color;
  };
} RGBA;
//
const RGBA RGB_Black = {.color = 0xFF000000};
const RGBA RGB_Red = {.color = 0xFF0000FF};
const RGBA RGB_Green = {.color = 0xFF00FF00};
const RGBA RGB_Blue = {.color = 0xFFFF0000};
const RGBA RGB_Cyan = {.color = 0xFFFFFF00};
const RGBA RGB_Magenta = {.color = 0xFFFF00FF};
const RGBA RGB_Yellow = {.color = 0xFF00FFFF};
const RGBA RGB_White = {.color = 0xFFFFFFFF};
const RGBA RGB_Gray = {.color = 0xFF808080};
const RGBA RGB_Grey = {.color = 0xFFC0C0C0};
const RGBA RGB_Maroon = {.color = 0xFF000080};
const RGBA RGB_Darkgreen = {.color = 0xFF008000};
const RGBA RGB_Navy = {.color = 0xFF800000};
const RGBA RGB_Teal = {.color = 0xFF808000};
const RGBA RGB_Purple = {.color = 0xFF800080};
const RGBA RGB_Olive = {.color = 0xFF008080};
//
typedef struct tag_SB {
  SDL_Window *Window;
  SDL_Renderer *Renderer;
  SDL_Event event;
  RGBA SelColor;
  uint32_t w;
  uint32_t h;
  const uint8_t *inkeys;
  float mouseX;
  float mouseY;
  bool LMB;
  bool RMB;
} SB_t;
// instance of SB
SB_t SB;
/*
    function definition
*/
bool SB_Key_Down(int key);
bool SB_Init(int w, int h, char *title);
int SB_Mode_None();
int SB_Mode_Blend();
int SB_Mode_Add();
int SB_Mode_Mod();
void SB_Update();
void SB_ReadKeys();
void SB_GetMouseState(int *x, int *y);
unsigned long SB_GetTicks();
void SB_Delay(int ms);
bool SB_Done(void);
void SB_Fini();
void SB_Clear(RGBA col);
void SB_Point(int x, int y, RGBA col);
bool SB_Line(int x1, int y1, int x2, int y2, RGBA col);
bool SB_Circle(int xc, int yc, int radius, RGBA col);
bool SB_Disk(int xc, int yc, int radius, RGBA col);
bool SB_Rect(int x, int y, int w, int h, RGBA col);
bool SB_FillRect(int x, int y, int w, int h, RGBA col);
////////////////////////////////////////////////////
bool SB_Key_Down(int key) {
  if (!SB.inkeys)
    return false;
  return (SB.inkeys[key] != 0);
}
/*
    Initialized BGI...
*/
bool SB_Init(int w, int h, char *title) {
  // Initialization flag

  bool bRet = true;
  SB.w = w;
  SB.h = h;
  SDL_SetMainReady();

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  SB.Window = SDL_CreateWindow(title, w, h, 0);
  if (SB.Window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  SB.Renderer = SDL_CreateRenderer(SB.Window, NULL, 0);
  if (SB.Renderer == NULL) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    bRet = false;
    return bRet;
  };
  return bRet;
}
////////////////////////////////////////////////////////////////////////////////////
int SB_Mode_None() {
  return SDL_SetRenderDrawBlendMode(SB.Renderer, SDL_BLENDMODE_NONE);
}
////////////////////////////////////////////////////////////////////////////////////
int SB_Mode_Blend() {
  return SDL_SetRenderDrawBlendMode(SB.Renderer, SDL_BLENDMODE_BLEND);
}
////////////////////////////////////////////////////////////////////////////////////
int SB_Mode_Add() {
  return SDL_SetRenderDrawBlendMode(SB.Renderer, SDL_BLENDMODE_ADD);
}
////////////////////////////////////////////////////////////////////////////////////
int SB_Mode_Mod() {
  return SDL_SetRenderDrawBlendMode(SB.Renderer, SDL_BLENDMODE_MOD);
}
////////////////////////////////////////////////////////////////////////////////////
void SB_Update() { SDL_RenderPresent(SB.Renderer); }
///////////////////////////////////////////////////////////////////
// sdl input function ...
///////////////////////////////////////////////////////////////////
void SB_ReadKeys() {
  SDL_PumpEvents();
  SB.inkeys = SDL_GetKeyboardState(NULL);
}
////////////////////////////////////////////////////////////////////////////////////
void SB_GetMouseState(int *x, int *y) {
  uint8_t mouseState = SDL_GetMouseState(&SB.mouseX, &SB.mouseY);
  *x = SB.mouseX;
  *y = SB.mouseY;
  if (mouseState & 1)
    SB.LMB = true;
  else
    SB.LMB = false;
  if (mouseState & 4)
    SB.RMB = true;
  else
    SB.RMB = false;
}
// Returns the time in milliseconds since the program started
unsigned long SB_GetTicks() { return SDL_GetTicks(); }
//////////////////////////////////////////////////////////////////////
void SB_Delay(int ms) { SDL_Delay(ms); }
////////////////////////////////////////////////////////////////////////////////////
bool SB_Done(void) {
  while (SDL_PollEvent(&SB.event)) {
    if (SB.event.type == SDL_EVENT_QUIT)
      return true;
  }
  SB_ReadKeys();
  if (SB.inkeys[SDL_SCANCODE_ESCAPE])
    return true;
  return false;
}
////////////////////////////////////////////////////////////////////////////////////
void SB_Fini() {
  SDL_DestroyRenderer(SB.Renderer);
  SB.Renderer = NULL;
  SDL_DestroyWindow(SB.Window);
  SB.Window = NULL;
  SDL_Quit();
}
////////////////////////////////////////////////////////////////////////////////////
void SB_Clear(RGBA col) {
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderClear(SB.Renderer);
}
////////////////////////////////////////////////////////////////////////////////////
void SB_Point(int x, int y, RGBA col) {
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderPoint(SB.Renderer, x, y);
}
////////////////////////////////////////////////////////////////////////////////////
bool SB_Line(int x1, int y1, int x2, int y2, RGBA col) {
  if (x1 < 0 || x1 > SB.w - 1 || x2 < 0 || x2 > SB.w - 1 || y1 < 0 ||
      y1 > SB.h - 1 || y2 < 0 || y2 > SB.h - 1)
    return false;
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_RenderLine(SB.Renderer, x1, y1, x2, y2);
  return true;
}
////////////////////////////////////////////////////////////////////////////
// Bresenham circle with center at(xc, yc) with radius and red green blue color
bool SB_Circle(int xc, int yc, int radius, RGBA col) {
  if (xc - radius < 0 || xc + radius >= SB.w || yc - radius < 0 ||
      yc + radius >= SB.h)
    return false;
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  int x = 0;
  int y = radius;
  int p = 3 - (radius << 1);
  int a, b, c, d, e, f, g, h;
  while (x <= y) {
    a = xc + x; // 8 pixels can be calculated at once thanks to the symmetry
    b = yc + y;
    c = xc - x;
    d = yc - y;
    e = xc + y;
    f = yc + x;
    g = xc - y;
    h = yc - x;
    SDL_RenderPoint(SB.Renderer, a, b);
    SDL_RenderPoint(SB.Renderer, c, d);
    SDL_RenderPoint(SB.Renderer, e, f);
    SDL_RenderPoint(SB.Renderer, g, f);
    if (x > 0) { // avoid drawing pixels at same position as the other ones
      SDL_RenderPoint(SB.Renderer, a, d);
      SDL_RenderPoint(SB.Renderer, c, b);
      SDL_RenderPoint(SB.Renderer, e, h);
      SDL_RenderPoint(SB.Renderer, g, h);
    }
    if (p < 0)
      p += (x++ << 2) + 6;
    else
      p += ((x++ - y--) << 2) + 10;
  }
  return true;
}
///////////////////////////////////////////////////////////////////////////////
// Filled bresenham circle with center at (xc,yc) with radius and red green blue
// color
bool SB_Disk(int xc, int yc, int radius, RGBA col) {
  if (xc + radius < 0 || xc - radius >= SB.w || yc + radius < 0 ||
      yc - radius >= SB.h)
    return false; // every single pixel outside screen, so don't waste time on
  // it
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  int x = 0;
  int y = radius;
  int p = 3 - (radius << 1);
  int a, b, c, d, e, f, g, h;
  int pb = yc + radius + 1,
      pd = yc + radius + 1; // previous values: to avoid drawing horizontal
  // lines multiple times
  // (ensure initial value is outside the range)
  while (x <= y) {
    // write data
    a = xc + x;
    b = yc + y;
    c = xc - x;
    d = yc - y;
    e = xc + y;
    f = yc + x;
    g = xc - y;
    h = yc - x;
    if (b != pb)
      SDL_RenderLine(SB.Renderer, a, b, c, b);
    if (d != pd)
      SDL_RenderLine(SB.Renderer, a, d, c, d);
    if (f != b)
      SDL_RenderLine(SB.Renderer, e, f, g, f);
    if (h != d && h != f)
      SDL_RenderLine(SB.Renderer, e, h, g, h);
    pb = b;
    pd = d;
    if (p < 0)
      p += (x++ << 2) + 6;
    else
      p += ((x++ - y--) << 2) + 10;
  }
  return true;
}
bool SB_Rect(int x, int y, int w, int h, RGBA col) {
  if (x < 0 || x > SB.w - 1 || x + w > SB.w - 1 || y < 0 || y > SB.h - 1 ||
      y + h > SB.h - 1)
    return false;
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_FRect rect;
  rect.h = h;
  rect.w = w;
  rect.x = x;
  rect.y = y;
  SDL_RenderRect(SB.Renderer, &rect);
  return true;
}
bool SB_FillRect(int x, int y, int w, int h, RGBA col) {
  if (x < 0 || x > SB.w - 1 || x + w > SB.w - 1 || y < 0 || y > SB.h - 1 ||
      y + h > SB.h - 1)
    return false;
  if (col.color != SB.SelColor.color) {
    SB.SelColor.color = col.color;
    SDL_SetRenderDrawColor(SB.Renderer, col.r, col.g, col.b, col.a);
  }
  SDL_FRect rect;
  rect.h = h;
  rect.w = w;
  rect.x = x;
  rect.y = y;
  SDL_RenderFillRect(SB.Renderer, &rect);
  return true;
}
/////////////////////////////////////////////////////////////////////////////////////
/*
SB Image
*/
typedef struct SB_Image {
  SDL_Texture *Tex;
  int w, h;
  void (*Boundary)(struct SB_Image *self, int *w, int *h);
  void (*Draw)(struct SB_Image *simg, int x, int y, float angle);
  void (*Destroy)(struct SB_Image *self);
} SB_Image;

static void _SB_image_destroy(SB_Image *simg) {
  if (simg != NULL) {
    SDL_DestroyTexture(simg->Tex);
    free(simg);
    simg = NULL;
  }
}
static void _boundary(SB_Image *simg, int *w, int *h) {
  *w = simg->w;
  *h = simg->h;
}
static void _draw(SB_Image *simg, int x, int y, float angle) {
  SDL_FRect src = {0, 0, simg->w, simg->h};
  SDL_FRect dest = {x - simg->w / 2, y - simg->h / 2, simg->w, simg->h};
  SDL_RenderTextureRotated(SB.Renderer, simg->Tex, &src, &dest, angle, NULL,
                   SDL_FLIP_NONE);
}
SB_Image *NewSBImage(char *filename) {
  SB_Image *simg = (SB_Image *)malloc(sizeof(SB_Image));
  SDL_Surface *surface = SDL_LoadBMP(filename);
  if (!surface) {
    if (simg != NULL) {
      free(simg);
      simg = NULL;
    }
    return NULL;
  }
  SDL_SetSurfaceColorKey(surface, SDL_TRUE, 0);
  simg->w = surface->w;
  simg->h = surface->h;
  simg->Tex = SDL_CreateTextureFromSurface(SB.Renderer, surface);
  SDL_DestroySurface(surface);
  SDL_SetTextureBlendMode(simg->Tex, SDL_BLENDMODE_BLEND);
  simg->Boundary = &_boundary;
  simg->Draw = &_draw;
  simg->Destroy = &_SB_image_destroy;
  return simg;
}
#endif // header guard
