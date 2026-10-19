// src/game/Spui/SPUIPieMenu.cpp -- migrated from slice(s) s0081a790, s008198f0, s008189a0, s00817cb0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPieMenu.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void SPUIHelpers_UpdateMouseFocus(int);

// ---- items of slice s00817cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct IWindow;
static inline void Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline int Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline char Vb1(void* p, int off, int a) {
    return ((char(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp1(void* p, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp2(void* p, int off, int a, int b) {
    return ((void*(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline void Vv5(void* p, int off, int a, int b, int c, int d, int e) {
    ((void(__thiscall*)(void*, int, int, int, int, int))(*(void***)p)[off / 4])(p, a, b, c, d, e);
}
extern "C" void SPUIHelpers_UpdateMouseFocus(int);
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);
struct cSPUIPieMenuItem {
    void**    vftable;          // +0x00
    u32       mID;              // +0x04
    IWindow*  mpCurrentWindow;  // +0x08
    char      pad_0c[0x14 - 0x0c];
    u32       mFlags;           // +0x14
    char      pad_18[0x1c - 0x18];
    void*     mpLHSWindowSet;   // +0x1c
    void*     mpRHSWindowSet;   // +0x20
    void*     mpIconWindow;     // +0x24
    void*     mpParentWin;      // +0x28
    void*     mpWinProc;        // +0x2c

    void SetIcon(int);          // 00818000
    void SetTextColor(int);     // 00817ee0
    void SetId(u32);            // 008188d0
    void MarkUnused();          // 00818950
    bool SetPos(int, int);      // 00817eb0
    void sub817fa0(int);        // 00817fa0
};
struct cItemInfo {
    cSPUIPieMenuItem item;
    char             pad_30[0x4c - 0x30];
};
struct Sub30 {
    char pad_00[0x18];
    int  f18;   // +0x18
    int  f1c;   // +0x1c
};
struct WinProcHolder {
    char      pad_00[0x24];
    IWindow*  mW24;   // +0x24
    bool has(IWindow* w);
};
struct Holder2 {
    char     pad_00[0x24];
    IWindow* mW24;   // +0x24
    char     pad_28[0xb0 - 0x28];
    void*    mWb0;   // +0xb0
    void teardown();
};
struct PieMenu02 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    bool assign(int a, int b);
};
struct PieMenu03 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    void setColor(u32 id, int color);
};
struct PieMenu04 {
    char       pad_00[0xc];
    cItemInfo* mpBegin;  // +0xc
    cItemInfo* mpEnd;    // +0x10
    char       pad_14[0x5c - 0x14];
    u8         b5c;      // +0x5c
    bool setTextColor(u32 id, int color);
};
struct PieMenuInit {
    char pad_00[0x100];
    void Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7);
};
// ---- items of slice s00817cb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void SPKeyFromName(void* out, void* name, u32, void*);

// ---- items of slice s008189a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPUIPieMenuItem_s0081_89a0 {
    void**   vftable;          // +0x00
    u32      mID;              // +0x04
    IWindow* mpCurrentWindow;  // +0x08
    char     pad_0c[0x14 - 0x0c];
    u32      mFlags;           // +0x14
    char     pad_18[0x1c - 0x18];
    void*    mpLHSWindowSet;   // +0x1c
    void*    mpRHSWindowSet;   // +0x20
    void*    mpIconWindow;     // +0x24
    void*    mpParentWin;      // +0x28
    void*    mpWinProc;        // +0x2c

    void SetIcon(int);          // 00818000 0x00818000
    void Update();              // 008189a0 0x008189a0
    void MarkUnused();          // 00818950 (slice 6) 0x00818950
    bool sub8191b0();           // 008191b0
    void dtor819880();          // 00819880
    void SetOrientation(bool, bool); // 008192e0 0x008192e0
};
struct cSPUIPieMenu {
    char     pad_00[0xc];
    char*    mpBegin;   // +0xc
    char*    mpEnd;     // +0x10
    char     pad_14[0x20 - 0x14];
    int      mItemCount;// +0x20 (used as a count in this build)
    char     pad_24[0x5c - 0x24];
    u8       b5c;       // +0x5c

    void RemoveItem();  // 00818c80
};
// ---- items of slice s008189a0 end

// ---- items of slice s008198f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00818650(void*);
struct DestroyHelper { void Fn(); };
static inline void DestroyItem(char* p) {
    *(void**)p = (void*)0x1418ef8;
    ((DestroyHelper*)p)->Fn();
    void* q;
    q = *(void**)(p + 0x30); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x2c); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x28); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x24); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x20); if (q) Vv0(q, 0x04);
    q = *(void**)(p + 0x1c); if (q) Vv0(q, 0x04);
}
struct Tail5 { float f0, f1, f2, f3; int i; };
// ---- items of slice s008198f0 end

// ---- items of slice s0081a790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_00817fa0(void*, int);
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct cSPUIPieMenuItem_s0081_a790 {
  char pad00[0x38];
  float mf0;    // +0x38
  float mf1;    // +0x3c
  float mf2;    // +0x40
  float mf3;    // +0x44
  char pad01[0x4];
  void SetId(int);  // 0x008188d0 (cSPUIPieMenuItem::SetId)
  void SetText(int, int);  // 0x00819220 (cSPUIPieMenuItem::SetText)
  void SetTextColor(int);  // 0x00817ee0 (cSPUIPieMenuItem::SetTextColor)
  void SetIcon(void*);  // 0x00818000 (cSPUIPieMenuItem::SetIcon)
};
struct cSPUIPieMenu_s0081_a790 {
  char pad00[0xc];
  cSPUIPieMenuItem_s0081_a790* mpBegin;   // +0x0c
  cSPUIPieMenuItem_s0081_a790* mpEnd;     // +0x10
  cSPUIPieMenuItem_s0081_a790* mpCap;     // +0x14
  char pad01[0x8];             // +0x18..0x1f
  int mCount;                  // +0x20
  int mItem;                   // +0x24
  void** mpListBegin;          // +0x28
  void** mpListEnd;            // +0x2c
  char pad02[0x2c];            // +0x30..0x5b
  char mChanged;               // +0x5c

  cSPUIPieMenuItem_s0081_a790* get_unused_item();
  int AddItem(int a, int b, int c, int d);
};
// ---- items of slice s0081a790 end

// @ 0x00817e20
void PieMenuInit::Init(void* n1, void* n2, void* p4, void* p5, void* p6, void* p7)
{
    u32 key1[3] = {0, 0, 0};
    u32 key2[3] = {0, 0, 0};
    if (n1) SPKeyFromName(key1, n1, 0x510a95b, p4);
    if (n2) SPKeyFromName(key2, n2, 0x510a95b, p4);
    Vv5(this, 0x20, (int)key1, (int)key2, (int)p4, (int)p5, (int)p6);
}




// @ 0x00817ee0
void cSPUIPieMenuItem::SetTextColor(int color)
{
    if (!color) return;
    IWindow* w = (IWindow*)Vcp1(mpRHSWindowSet, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    void* q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
    w = (IWindow*)Vcp1(mpIconWindow, 0xf0, 0x122d76c);
    if (!w) return;
    w = (IWindow*)Vcp1(w, 0x0c, 0xf15f4bd);
    if (!w) return;
    Vv1(w, 0x28, color);
    q = Vcp0(w, 0x10);
    Vv0(q, 0x90);
}




// @ 0x00817fa0
void cSPUIPieMenuItem::sub817fa0(int color)
{
    IWindow* w = (IWindow*)Vcp2(mpRHSWindowSet, 0xf0, 0x122a5c7, 1);
    if (w) {
        Vv2(w, 0x7c, 2, color);
        w = (IWindow*)Vcp2(mpIconWindow, 0xf0, 0x122a5c7, 1);
        if (w) Vv2(w, 0x7c, 2, color);
    }
}




// @ 0x008181e0
void PieMenu03::setColor(u32 id, int color)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == 0xffffffff || it->mID != id) continue;
        it->sub817fa0(color);
    }
}




// @ 0x00818250
bool PieMenu04::setTextColor(u32 id, int color)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem* it = (cSPUIPieMenuItem*)((char*)mpBegin + i * 0x4c);
        if (it->mID == id) {
            b5c = 1;
            it->SetTextColor(color);
            return true;
        }
    }
    return false;
}




// @ 0x008182c0
bool PieMenu02::assign(int a, int b)
{
    for (u32 i = 0; i < (u32)(((char*)mpEnd - (char*)mpBegin) / 0x4c); ++i) {
        Sub30* s = *(Sub30**)((char*)mpBegin + i * 0x4c + 0x30);
        s->f18 = a;
        s->f1c = b;
    }
    return true;
}




// @ 0x00818330
void Holder2::teardown()
{
    if (mW24) Vv2(mW24, 0x7c, 1, 0);
    if (mWb0) { void* q = mWb0; mWb0 = 0; Vv0(q, 0x04); }
    SPUIHelpers_UpdateMouseFocus(1);
}




// @ 0x00818370
bool WinProcHolder::has(IWindow* w)
{
    bool result = false;
    if (w) {
        if (w != mW24) {
            if (!Vb1(mW24, 0xf8, (int)w)) return false;
        }
        result = true;
    }
    return result;
}




// @ 0x008188d0
void cSPUIPieMenuItem::SetId(u32 id)
{
    IWindow* p = mpCurrentWindow;
    *(u32*)((char*)mpWinProc + 0x10) = id;
    if (id == mID) return;
    SetIcon(0);
    mID = id;
    if (id == 0xffffffff) {
        if (p) {
            if (Vi0(p, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
    } else {
        if (p) {
            if (Vi0(p, 0x10) == 0) {
                Vv1(mpWinProc, 0xd8, (int)mpCurrentWindow);
                mFlags = 3;
                return;
            }
        }
    }
    mFlags = 3;
}




// @ 0x00818950
void cSPUIPieMenuItem::MarkUnused()
{
    *(u32*)(*(int*)((char*)this + 0x30) + 0x10) = 0xffffffff;
    if (mID != 0xffffffff) {
        SetIcon(0);
        mID = 0xffffffff;
        if (mpCurrentWindow) {
            int r = Vi0(mpCurrentWindow, 0x10);
            if (r) Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mFlags = 3;
    }
}



// @ 0x00818c80
void cSPUIPieMenu::RemoveItem()
{
    for (u32 i = 0; i < (u32)((mpEnd - mpBegin) / 0x4c); ++i) {
        cSPUIPieMenuItem_s0081_89a0* it = (cSPUIPieMenuItem_s0081_89a0*)(mpBegin + i * 0x4c);
        if (it->mID != 0xffffffff) {
            // MarkUnused() inlined by the original
            *(u32*)(*(int*)((char*)it + 0x30) + 0x10) = 0xffffffff;
            if (it->mID != 0xffffffff) {
                it->SetIcon(0);
                it->mID = 0xffffffff;
                if (it->mpCurrentWindow && Vi0(it->mpCurrentWindow, 0x10))
                    Vv1(it->mpWinProc, 0xdc, (int)it->mpCurrentWindow);
                it->mFlags = 3;
            }
            mItemCount += -1;
        }
    }
}



// @ 0x008191b0
bool cSPUIPieMenuItem_s0081_89a0::sub8191b0()
{
    MarkUnused();
    mpCurrentWindow = 0;
    { void* q = mpRHSWindowSet;  if (q) { mpRHSWindowSet = 0;  Vv0(q, 0x04); } }
    { void* q = mpIconWindow;    if (q) { mpIconWindow = 0;    Vv0(q, 0x04); } }
    { void* q = mpParentWin;     if (q) { mpParentWin = 0;     Vv0(q, 0x04); } }
    { void* q = mpWinProc;       if (q) { mpWinProc = 0;       Vv0(q, 0x04); } }
    { void* q = *(void**)((char*)this + 0x30);
      if (q) { *(void**)((char*)this + 0x30) = 0; Vv0(q, 0x04); } }
    return true;
}



// @ 0x008192e0
void cSPUIPieMenuItem_s0081_89a0::SetOrientation(bool vert, bool update)
{
    void** slot = vert ? &mpRHSWindowSet : &mpIconWindow;
    IWindow* w = (IWindow*)*slot;
    if (mpCurrentWindow != w) {
        if (mpCurrentWindow) {
            if (Vi0(mpCurrentWindow, 0x10))
                Vv1(mpWinProc, 0xdc, (int)mpCurrentWindow);
        }
        mpCurrentWindow = w;
        if (mID != 0xffffffff)
            Vv1(mpWinProc, 0xd8, (int)w);
        mFlags |= 2;
        if (update) Update();
        IWindow* parent = (IWindow*)mpParentWin;
        SetIcon(0);
        SetIcon((int)parent);
    }
}



// @ 0x00819880
void cSPUIPieMenuItem_s0081_89a0::dtor819880()
{
    vftable = (void**)0x1418ef8;
    sub8191b0();
    void* q;
    q = *(void**)((char*)this + 0x30); if (q) Vv0(q, 0x04);
    q = mpWinProc;    if (q) Vv0(q, 0x04);
    q = mpParentWin;  if (q) Vv0(q, 0x04);
    q = mpIconWindow; if (q) Vv0(q, 0x04);
    q = mpRHSWindowSet; if (q) Vv0(q, 0x04);
    q = mpLHSWindowSet; if (q) Vv0(q, 0x04);
}


// @ 0x00819e00
int __cdecl FUN_00819e00(char* a, char* b, char* c)
{
    if (a == b) return (int)c;
    char* dst = c + 0x40;
    char* src = a + 0x40;
    do {
        if (c) {
            FUN_00818650(a);
            Tail5* d = (Tail5*)(dst - 8);
            Tail5* s = (Tail5*)(src - 8);
            d->f0 = s->f0;
            d->f1 = s->f1;
            d->f2 = s->f2;
            d->f3 = s->f3;
            d->i  = s->i;
        }
        a += 0x4c;
        src += 0x4c;
        c += 0x4c;
        dst += 0x4c;
    } while (a != b);
    return (int)c;
}


// @ 0x00819e60
int __cdecl FUN_00819e60(char* a, char* b, int c)
{
    if (a == b) return c;
    do {
        DestroyItem(a);
        a += 0x4c;
        c += 0x4c;
    } while (a != b);
    return c;
}


// @ 0x00819f10
void __stdcall FUN_00819f10(char* a, char* b)
{
    for (; a < b; a += 0x4c) DestroyItem(a);
}

// @ 0x0081a790
cSPUIPieMenuItem_s0081_a790* cSPUIPieMenu_s0081_a790::get_unused_item()
{
  return 0;
}

// @ 0x0081a940
int cSPUIPieMenu_s0081_a790::AddItem(int a, int b, int c, int d)
{
  cSPUIPieMenuItem_s0081_a790* item = get_unused_item();
  if (item == 0) return 0;
  item->mf0 = 0.f; item->mf1 = 0.f; item->mf2 = 0.f; item->mf3 = 0.f;
  item->SetId(a);
  item->SetText(b, 1);
  item->SetTextColor(c);
  FUN_00817fa0(item, d);
  uint32_t n = (uint32_t)(mpListEnd - mpListBegin);
  if (n != 0) {
    uint32_t i = 0;
    for (;;) {
      void* p = mpListBegin[i];
      int id = ((int (__thiscall*)(void*))VTSLOT(p, 0x1c))(p);
      if (id == a) { item->SetIcon(p); break; }
      i++;
      if (i >= (uint32_t)(mpListEnd - mpListBegin)) break;
    }
  }
  mCount++;
  mChanged = 1;
  return 1;
}
