// src/game/Spui/SPUIProgressBarGradientWin.cpp -- migrated from slice(s) s0081c9c0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIProgressBarGradientWin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char g_13ec458[];
extern "C" char g_140af70[];
extern "C" char g_141990c[];
extern "C" char g_1419920[];
extern "C" char g_1419a40[];
extern "C" char g_1419b34[];
#include <wchar.h>

// ---- items of slice s0081c9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13ec458[];
extern "C" char g_140af70[];
extern "C" char g_141990c[];
extern "C" char g_1419920[];
extern "C" char g_1419a40[];
extern "C" char g_1419b34[];
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct CopySrc  { char pad00[4]; void** mpItems; };              // +0x04
struct CopyDst  { char pad00[4]; char*  mpBase; };               // +0x04
struct CopySpec { char pad00[0x10]; int mOffset; int mCount; };  // +0x10 / +0x14
struct S962a10 { S962a10* f(); };
struct RenderCtx {
  void* f95bc10(int mode);   // 0x0095bc10 Begin2D
  void  f95bb20();           // 0x0095bb20 End2D
};
unsigned __cdecl ColorLerp(unsigned from, unsigned to, float t);   // 0x007f5eb0 Color::Lerp
namespace UTFWin {
struct cSPUIProgressBarGradientWin {
  void*  mVtbl0;                 // +0x000
  void*  mVtbl4;                 // +0x004
  char   pad00[0x88 - 8];
  float  mX1;                    // +0x088
  float  mY1;                    // +0x08c
  float  mX2;                    // +0x090
  float  mY2;                    // +0x094
  char   pad01[0x20c - 0x98];
  void* volatile mIfaceVtbl20c;  // +0x20c
  int   volatile mUnknown210;    // +0x210
  void* volatile mIfaceVtbl214;  // +0x214
  float  mValue218;              // +0x218
  unsigned mColorMin21c;         // +0x21c
  unsigned mColorMax220;         // +0x220
  unsigned mColorLine224;        // +0x224
  void* volatile mpGradientImage228;     // +0x228
  int    mMode22c;               // +0x22c
  cSPUIProgressBarGradientWin();
  bool Draw(RenderCtx* ctx);     // 0x0081d0f0
};
}
struct ProgressValueIface {
  void* mVtbl;        // +0x00
  float mValue;       // +0x04
  bool SetValue(float v);
};
struct ImgRect { float x, y, w, h; };
// ---- items of slice s0081c9c0 end

// @ 0x0081cf50
bool __cdecl CopyObjectList(CopyDst* dst, CopySrc* src, CopySpec* spec)
{
  void** out;
  void** in = src->mpItems;
  out = (void**)(dst->mpBase + spec->mOffset);
  for (unsigned i = 0; i < (unsigned)spec->mCount; i++) {
    void* old = *out;
    void* r = 0;
    if (old != 0) ((void (__thiscall*)(void*))VTSLOT(old, 4))(old);
    void* s = *in;
    if (s != 0) {
      r = ((void* (__thiscall*)(void*, int))VTSLOT(s, 0xc))(s, 0x1be6ab3);
      if (r != 0) ((void (__thiscall*)(void*))VTSLOT(r, 0))(r);
    }
    *out = r;
    out++;
    in++;
  }
  return true;
}

// @ 0x0081d020
UTFWin::cSPUIProgressBarGradientWin::cSPUIProgressBarGradientWin()
{
  ((S962a10*)this)->f();
  mIfaceVtbl20c = (void*)g_13ec458;
  mUnknown210 = 0;
  mIfaceVtbl214 = (void*)g_140af70;
  mpGradientImage228 = 0;
  mVtbl0 = (void*)g_1419a40;
  mVtbl4 = (void*)g_1419920;
  mIfaceVtbl20c = (void*)g_141990c;
  mIfaceVtbl214 = (void*)g_1419b34;
  mValue218 = 100.0f;
  mColorMin21c = 0xffff0000;
  mColorMax220 = 0xff00ff00;
  mColorLine224 = 0xffffffff;
  mMode22c = 1;
}

// @ 0x0081d0f0
bool UTFWin::cSPUIProgressBarGradientWin::Draw(RenderCtx* ctx)
{
  float w = mX2 - mX1;
  float h = mY2 - mY1;
  float t = mValue218 * 0.01f;
  RenderCtx* volatile rc = ctx;
  void* batch = rc->f95bc10(0);
  if (mpGradientImage228 != 0) {
    float ct = t;
    if (ct < 0.01f) ct = 0.01f;
    else if (ct > 0.99f) ct = 0.99f;
    ImgRect uv;
    uv.x = 0.0f; uv.y = ct; uv.w = 1.0f; uv.h = ct;
    ImgRect dst;
    dst.x = 0.0f; dst.y = 0.0f; dst.w = w; dst.h = h;
    ((void (__thiscall*)(void*, ImgRect*, void*, ImgRect*))VTSLOT(batch, 0x58))(
        batch, &dst, mpGradientImage228, &uv);
    ((void (__thiscall*)(void*, unsigned))VTSLOT(batch, 4))(batch, mColorLine224);
    float half = w * 0.5f;
    ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
        batch, half - 0.5f, 0.0f, half + 0.5f, h);
  } else {
    void* obj = ((void* (__thiscall*)(void*))VTSLOT((char*)this + 4, 0xa4))((char*)this + 4);
    if (obj != 0) {
      obj = ((void* (__thiscall*)(void*))VTSLOT((char*)this + 4, 0xa4))((char*)this + 4);
      ((void (__thiscall*)(void*, void*))VTSLOT(batch, 4))(batch, obj);
      ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
          batch, 0.0f, 0.0f, w, h);
    }
    unsigned col = ColorLerp(mColorMin21c, mColorMax220, t);
    ((void (__thiscall*)(void*, unsigned))VTSLOT(batch, 4))(batch, col);
    if (mMode22c == 1) {
      ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
          batch, 0.0f, 0.0f, t * w, h);
    } else if (mMode22c == 2) {
      ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
          batch, (1.0f - t) * w, 0.0f, w, h);
    } else if (mMode22c == 3) {
      float half = w * 0.5f;
      if (t > 0.5f) {
        ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
            batch, half, 0.0f, t * w, h);
      } else if (t >= 0.5f) {
        ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
            batch, half - 0.1f, 0.0f, half + 0.1f, h);
      } else {
        ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
            batch, t * w, 0.0f, half, h);
      }
      ((void (__thiscall*)(void*, unsigned))VTSLOT(batch, 4))(batch, mColorLine224);
      ((void (__thiscall*)(void*, float, float, float, float))VTSLOT(batch, 0x38))(
          batch, half - 0.5f, 0.0f, half + 0.5f, h);
    }
  }
  rc->f95bb20();
  return true;
}

// @ 0x0081d480
bool ProgressValueIface::SetValue(float v)
{
  if (mValue == v) return false;
  if (!(v >= 0.0f)) return false;
  if (!(v <= 100.0f)) return false;
  void* notify = (char*)this - 0x210;
  ((void (__thiscall*)(void*))VTSLOT(notify, 0x90))(notify);
  mValue = v;
  return false;
}
