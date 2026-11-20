// @ 0x00e24f10
// cSPUIPosseItemTribeBaby::DoMessage -- 305 bytes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The tribe baby's picture window is drawn by hand: when the message targets
// that window (window id 0x3dea7f0) and carries tag 13, the render context
// stored in the message opens a 2-D batch, the window's image is drawn over
// the window rectangle, tilted by the item's control value, and the batch is
// closed.  A message for anything else is left to the base item handler.
//
// Local stand-ins: the canonical classes live in SPGonzago/SPUIPosse.cpp; this
// slice only needs the parts the function touches (vtable + mControlValue01 at
// +0x14c, message tag at +0x08, render context at +0x18).
#include "types.h"

// ---------------------------------------------------------------------------
// shapes used by this function
// ---------------------------------------------------------------------------
struct cSPUIVtbl_s00e2_4f10 { void (*slot[128])(); };
#define VT(p) (*(cSPUIVtbl_s00e2_4f10**)(p))

typedef void     (__thiscall* FnVoid0_s00e2_4f10)(void*);
typedef uint32_t (__thiscall* FnU32_0_s00e2_4f10)(void*);

// The rectangle a window reports through vtable slot 0x38.
struct RectF_s00e2_4f10 {
  float mLeft;    // +0x00
  float mTop;     // +0x04
  float mRight;   // +0x08
  float mBottom;  // +0x0c
};

// A corner of that rectangle.  The original reads the rect as its top-left and
// bottom-right points and takes the size as the difference of the two.
struct Point2_s00e2_4f10 {
  float mX;       // +0x00
  float mY;       // +0x04
  Point2_s00e2_4f10(float x, float y) : mX(x), mY(y) {}
};

// Message handed to an item: tag at +0x08, render context at +0x18.
struct MsgIn_s00e2_4f10 {
  uint8_t mPad00[8];   // +0x00
  int32_t mField08;    // +0x08
  uint8_t mPad0c[0x0c];// +0x0c
  void*   mField18;    // +0x18
};

class cSPUIPosseItem_s00e2_4f10 {
public:
  void*   mpVtable;         // +0x00
  uint8_t mPad04[0x148];    // +0x04 .. +0x14b
  float   mControlValue01;  // +0x14c

  char DoMessage(void* win, MsgIn_s00e2_4f10* msg);   // 0x00e247f0, base handler
};

class cSPUIPosseItemTribeBaby_s00e2_4f10 : public cSPUIPosseItem_s00e2_4f10 {
public:
  char DoMessage(void* win, MsgIn_s00e2_4f10* msg);   // 0x00e24f10
};

// 0x00e232b0: the image a window draws itself with.
void* __cdecl sGetWindowImage(void* win);

// 0x0095bc10 / 0x0095bb20: UTFWin RenderContext 2-D batch open/close.
struct RenderContext_s00e2_4f10 {
  void* Begin2D(int flags);   // 0x0095bc10
  void  End2D();              // 0x0095bb20
};

// 0x00e23340: draws an image quad over the window rectangle, rotated between
// two angles (half extents first, then the full extents, then the sweep).
void __cdecl FUN_00e23340(void* batch, float halfWidth, float halfHeight, float width,
                          float height, int32_t a, int32_t b, float angleFrom,
                          float angleTo, void* image, float alpha);

// Writable game globals the tilt is built from (0x015a547c is pi/2, the base
// tilt; 0x016ac2cc is the tilt range accumulated over the control value).
extern float g_015a547c;
extern float g_016ac2cc;

// ---------------------------------------------------------------------------
// @ 0x00e24f10
char cSPUIPosseItemTribeBaby_s00e2_4f10::DoMessage(void* win, MsgIn_s00e2_4f10* msg)
{
  if (((FnU32_0_s00e2_4f10)VT(win)->slot[0x1c / 4])(win) == 0x3dea7f0u &&
      msg->mField08 == 13) {
    void* ctx = msg->mField18;
    void* image = sGetWindowImage(win);
    if (image) {
      ((FnVoid0_s00e2_4f10)VT(image)->slot[0])(image);

      void* batch = ((RenderContext_s00e2_4f10*)ctx)->Begin2D(0);

      RectF_s00e2_4f10* rc =
          ((RectF_s00e2_4f10* (__thiscall*)(void*))VT(win)->slot[0x38 / 4])(win);
      Point2_s00e2_4f10 topLeft(rc->mLeft, rc->mTop);
      Point2_s00e2_4f10 bottomRight(rc->mRight, rc->mBottom);
      float w = bottomRight.mX - topLeft.mX;
      float h = bottomRight.mY - topLeft.mY;

      FUN_00e23340(batch, w * 0.5f, h * 0.5f, w, h, -1, -1, g_015a547c,
                   (1.0f - mControlValue01) * g_016ac2cc + g_015a547c, image, 0.05f);

      ((RenderContext_s00e2_4f10*)ctx)->End2D();
      ((FnVoid0_s00e2_4f10)VT(image)->slot[1])(image);
      return 1;
    }
  }
  return cSPUIPosseItem_s00e2_4f10::DoMessage(win, msg);
}
