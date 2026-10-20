// Spore SporeApp.exe 0x0096bdd0..0x0096c6e2
//   EA::UTFWinControls::WinDialog mouse / message / rebuild handlers.
//
// 0x0096bdd0  EA::UTFWinControls::WinDialog::OnMouseMove
// 0x0096c430  EA::UTFWinControls::WinDialog::DoMessage
// 0x0096c4c0  FUN_0096c4c0  (resize-border hit test)
// 0x0096c5d0  EA::UTFWinControls::WinDialog::OnRebuild
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct RectF {
  float mLeft, mTop, mRight, mBottom;
};

// ---------------------------------------------------------------------------
// Vtable stub classes: only the slot offsets matter (no definitions).
// ---------------------------------------------------------------------------

// Primary vtable of WinDialog (vptr at +0x00).  Slot 0x90 = index 36.
struct WinDialogVtbl {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
  virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
  virtual int  v36(float a, float b);  // +0x90
};

// First base sub-object of WinDialog (vptr at +0x04).
//   +0x60 index 24 : SetRect(RectF const*)
//   +0x78 index 30 : SetCursor(int)
//   +0x90 index 36 : Refresh()
//   +0x114 index 69: UpdateWindow(void*)
struct WinDialogBase {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void SetRect(RectF const* pRect);  // +0x60
  virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
  virtual void v29();
  virtual void SetCursor(int id);            // +0x78
  virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
  virtual void v35();
  virtual void Refresh();                    // +0x90
  virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
  virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
  virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
  virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
  virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();
  virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
  virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
  virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68();
  virtual void UpdateWindow(void* local);    // +0x114
};

// Object at WinDialog+0x34: slot 0x3c = index 15, slot 0x54 = index 21.
struct MouseManager {
  virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
  virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
  virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
  virtual void m12(); virtual void m13(); virtual void m14();
  virtual void GetPoint(void* pPoint);  // +0x3c
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
  virtual void m20();
  virtual void* GetTarget(int flag);    // +0x54
};

// Object at WinDialog+0x38 (two vptrs): primary slot 0x3c = index 15,
// second base at +0x04 slot 0xc4 = index 49.
struct CompContainer {
  virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
  virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
  virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
  virtual void c12(); virtual void c13(); virtual void c14();
  virtual void GetPoint(void* pPoint);  // +0x3c
};

struct CompContainerSub {
  virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
  virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
  virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
  virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
  virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
  virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
  virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
  virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
  virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
  virtual void s48();
  virtual void DrawPoint(RectF const* pRect);  // +0xc4
};

// Object at WinDialog+0x1e0: component container.
//   +0x0c index 3 : void* FindWindow(unsigned int id)
//   +0x10 index 4 : AddComponent(void* arg, RectF const* r, void* local)
struct ICompContainer {
  virtual void i00(); virtual void i01(); virtual void i02();
  virtual void* FindWindow(unsigned int id);                            // +0x0c
  virtual void  AddComponent(void* arg, RectF const* r, void* local);   // +0x10
};

// Object at WinDialog+0x228 and the layout object it hands back.
struct IWinRef {
  virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
  virtual void* QueryLayout();  // +0x10
};
struct ILayout {
  virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03();
  virtual void l04(); virtual void l05(); virtual void l06();
  virtual void* GetWindow();  // +0x1c
};

// ---------------------------------------------------------------------------
// WinDialog layout (only the fields the four functions touch).
// ---------------------------------------------------------------------------
#pragma pack(push, 4)
struct WinDialog {
  void* mVT0;                                // 0x000
  void* mVT1;                                // 0x004  base sub-object vptr
  void* mUnk08;                              // 0x008
  void* mVT2;                                // 0x00c
  void* mUnk10;                              // 0x010
  char  mPad14[0x34 - 0x14];
  MouseManager*  mObj34;                     // 0x034
  CompContainer* mObj38;                     // 0x038
  char  mPad3c[0x80 - 0x3c];
  void* mObj80;                              // 0x080
  void* mObj84;                              // 0x084
  RectF mWindowRect;                         // 0x088
  char  mPad98[0x1d8 - 0x98];
  int   mRef1d8;                             // 0x1d8
  int   mRef1dc;                             // 0x1dc
  ICompContainer* mComponents;               // 0x1e0
  char  mPad1e4[0x214 - 0x1e4];
  unsigned int mFlags;                       // 0x214
  int   mKind;                               // 0x218
  float mOff21c;                             // 0x21c
  float mOff220;                             // 0x220
  char  mPad224[0x228 - 0x224];
  IWinRef* mWinRef;                          // 0x228
  char  mPad22c[0x230 - 0x22c];
  RectF mRect230;                            // 0x230
  RectF mRect240;                            // 0x240
  RectF mChildren[8];                        // 0x250 .. 0x2cf
  char  mPad2d0[0x2e0 - 0x2d0];
  RectF mBorder;                             // 0x2e0
  char  mPad2f0[0x310 - 0x2f0];
  RectF mMinMax;                             // 0x310

  bool OnMouseMove(float a, float b, float c);  // 0x0096bdd0
  bool DoMessage(void* msg);                    // 0x0096c430
  int  FUN_0096c4c0(float x, float y);          // 0x0096c4c0
  bool OnRebuild(void* arg);                    // 0x0096c5d0
  bool DoMessageBase(void* msg);                // 0x00950bb0
  void OnPaint(void* arg);                      // 0x00960310
};

// Stack message block built for the UpdateWindow call in DoMessage.
struct MsgArg {
  int          mPad0;
  int          mPad4;
  unsigned int mType;
  void*        mPtr;
  int          mResult;
  int          mPad14;
  int          mPad18;
};
#pragma pack(pop)

// ---------------------------------------------------------------------------
// Function bodies.
// ---------------------------------------------------------------------------

// @ 0x0096c4c0
int WinDialog::FUN_0096c4c0(float x, float y) {
  unsigned int flags = mFlags;
  if ((flags & 0x20) != 0) {
    float w = mWindowRect.mRight - mWindowRect.mLeft - mBorder.mRight;
    float h = mWindowRect.mBottom - mWindowRect.mTop - mBorder.mBottom;
    if (x < mBorder.mLeft) {
      if (y < mBorder.mTop) return 6;
      if (h <= y) return 8;
      return 2;
    }
    if (w <= x) {
      if (y < mBorder.mTop) return 7;
      if (h <= y) return 9;
      return 3;
    }
    if (y < mBorder.mTop) return 4;
    if (h <= y) return 5;
  }
  if ((flags & 8) != 0) {
    if (mRect240.mLeft <= x && mRect240.mTop <= y && x < mRect240.mRight &&
        y < mRect240.mBottom)
      return 1;
    return -1;
  }
  return 0;
}

// @ 0x0096c430
bool WinDialog::DoMessage(void* msg) {
  int* pMsg = (int*)msg;
  if (pMsg[2] != 0x287259f6) return DoMessageBase(msg);
  if (pMsg[3] != 0x4f0dd487) return DoMessageBase(msg);
  if (mObj38 != 0) {
    MsgArg local;
    local.mType = 0x8f4d1282;
    local.mPtr = (mObj84 != 0) ? mObj84 : mObj80;
    IWinRef* pRef = mWinRef;
    ILayout* pLayout = (ILayout*)pRef->QueryLayout();
    local.mResult = (int)pLayout->GetWindow();
    ((WinDialogBase*)&mVT1)->UpdateWindow(&local);
  }
  return true;
}

// @ 0x0096c5d0
bool WinDialog::OnRebuild(void* arg) {
  if (mComponents != 0 && mComponents->FindWindow(0x6f0c6ff6) != 0) {
    int local[4];
    local[0] = 0;
    local[1] = 0;
    local[2] = mRef1dc;
    local[3] = mRef1d8;
    mComponents->AddComponent(arg, &mRect230, local);

    if ((mFlags & 8) != 0) {
      local[1] = 1;
      mComponents->AddComponent(arg, &mRect240, local);
    }

    if ((mFlags & 0x20) != 0) {
      for (int i = 2; i < 10; ++i) {
        RectF* r = &mChildren[i - 2];
        if (r->mRight > r->mLeft && r->mBottom > r->mTop) {
          local[1] = i;
          mComponents->AddComponent(arg, r, local);
        }
      }
    }
  } else {
    OnPaint(arg);
  }
  return true;
}

// @ 0x0096bdd0
bool WinDialog::OnMouseMove(float a, float b, float c) {
  WinDialogBase* pSelf = (this != 0) ? (WinDialogBase*)((char*)this + 4) : 0;
  if (mObj34->GetTarget(1) == (void*)pSelf) {
    RectF rect = mWindowRect;
    float pt[2];
    mObj34->GetPoint(pt);
    ((CompContainerSub*)((char*)mObj38 + 4))->DrawPoint(&rect);

    float w = mWindowRect.mRight - mWindowRect.mLeft;
    float h = mWindowRect.mBottom - mWindowRect.mTop;
    switch (mKind) {
      case 0:
        rect.mLeft = pt[0] - mOff21c;
        rect.mTop = pt[1] - mOff220;
        rect.mRight = w + rect.mLeft;
        rect.mBottom = h + rect.mTop;
        break;
      case 1: {
        float right = rect.mRight;
        float l = pt[0] - mOff21c;
        rect.mLeft = l;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        if (right - rect.mLeft <= mMinMax.mLeft) break;
        rect.mLeft = right - mMinMax.mLeft;
        break;
      }
      case 2: {
        float right = mOff21c + pt[0];
        rect.mRight = right;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (rect.mRight - rect.mLeft <= mMinMax.mLeft) break;
        rect.mRight = rect.mLeft + mMinMax.mLeft;
        break;
      }
      case 3: {
        float bottom = rect.mBottom;
        float t = pt[1] - mOff220;
        rect.mTop = t;
        if (mMinMax.mBottom > bottom - t) rect.mTop = bottom - mMinMax.mBottom;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = bottom - mMinMax.mTop;
        break;
      }
      case 4: {
        float bottom = mOff220 + pt[1];
        rect.mBottom = bottom;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 5: {
        float right = rect.mRight;
        float bottom = rect.mBottom;
        float l = pt[0] - mOff21c;
        float t = pt[1] - mOff220;
        rect.mLeft = l;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        rect.mTop = t;
        if (mMinMax.mBottom > bottom - t) rect.mTop = bottom - mMinMax.mBottom;
        if (right - rect.mLeft <= mMinMax.mLeft) break;
        rect.mLeft = right - mMinMax.mLeft;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = bottom - mMinMax.mTop;
        break;
      }
      case 6: {
        float right = mOff21c + pt[0];
        float t = pt[1] - mOff220;
        rect.mRight = right;
        rect.mTop = t;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (mMinMax.mBottom > rect.mBottom - t)
          rect.mTop = rect.mBottom - mMinMax.mBottom;
        if (rect.mRight - rect.mLeft <= mMinMax.mLeft) break;
        rect.mRight = rect.mLeft + mMinMax.mLeft;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mTop = rect.mBottom - mMinMax.mTop;
        break;
      }
      case 7: {
        float right = rect.mRight;
        float bottom = mOff220 + pt[1];
        float l = pt[0] - mOff21c;
        rect.mLeft = l;
        rect.mBottom = bottom;
        if (mMinMax.mRight > right - l) rect.mLeft = right - mMinMax.mRight;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (right - rect.mLeft <= mMinMax.mLeft) {
          if (bottom - rect.mTop <= mMinMax.mTop) break;
          rect.mBottom = rect.mTop + mMinMax.mTop;
          break;
        }
        rect.mLeft = right - mMinMax.mLeft;
        if (bottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 8: {
        float right = mOff21c + pt[0];
        float bottom = mOff220 + pt[1];
        rect.mRight = right;
        rect.mBottom = bottom;
        if (mMinMax.mRight > right - rect.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mRight;
        if (mMinMax.mBottom > bottom - rect.mTop)
          rect.mBottom = rect.mTop + mMinMax.mBottom;
        if (rect.mRight - rect.mLeft > mMinMax.mLeft)
          rect.mRight = rect.mLeft + mMinMax.mLeft;
        if (rect.mBottom - rect.mTop <= mMinMax.mTop) break;
        rect.mBottom = rect.mTop + mMinMax.mTop;
        break;
      }
      case 9:
      default:
        break;
    }
    ((WinDialogBase*)&mVT1)->SetRect(&rect);
  } else {
    int r = ((WinDialogVtbl*)this)->v36(c, b);
    int cmd;
    switch (r) {
      case 2:
      case 3: cmd = 0x1009; break;
      case 4:
      case 5: cmd = 0x1008; break;
      case 6:
      case 9: cmd = 0x100a; break;
      case 7:
      case 8: cmd = 0x100b; break;
      default: cmd = 0x1002; break;
    }
    ((WinDialogBase*)&mVT1)->SetCursor(cmd);
  }
  ((WinDialogBase*)&mVT1)->Refresh();
  return true;
}
