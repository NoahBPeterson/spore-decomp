// src/game/UTFSpore_Win32/_at_00960000.cpp -- migrated from slice(s) s0096e3a0, s00968da0, s00966b20, s00962ff0, s00961db0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00960000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/BuildState.h"
#include "EA/Stopwatch.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern int  FUN_011f2e70(void*, void*);
extern void FUN_011f21a0();
extern int   g_16f8afc;
extern void* g_16f89d0;         // d3d device object pointer
extern void* g_16f65a0;         // active vertex descriptor
extern int   g_16f9110;         // soft-state dirty flags
extern int   g_16f9138;
extern int   g_16f913c;
extern int   g_16f9140;
extern void* g_16f6568;         // shader state object pointer

// ---- items of slice s00961db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void (*g_free_16f4aec)(void*);   // operator delete(void*) thunk in the IAT
extern int  FUN_011f2e70(void*, void*);
extern void FUN_011f21a0();
extern int   g_16f8afc;
struct S962da0c {
  void f();                            // 0x00962da0
};
struct S11f36a0 {
  void f();                            // 0x011f36a0
  unsigned FUN_011f3620(unsigned char flags, unsigned a, unsigned b);  // 0x011f3620
};
struct Vtbl190 { char pad[0x190]; int (__stdcall *fn)(void*, int, int, int, int); };
struct Vtbl1a0 { char pad[0x1a0]; int (__stdcall *fn)(void*, int); };
struct Vtbl144 { char pad[0x144]; void (__stdcall *fn)(void*, int, int, int); };
struct Vtbl148 { char pad[0x148]; void (__stdcall *fn)(void*, int, int, int, int, int, int); };
struct S962d10 { void f(); };
struct S962da0 { bool f(); };
struct S962e80 { unsigned f(unsigned, unsigned); };
struct S962f00 { void f(); };
struct Cln_e { void f(); };
struct Cln_4e { void f(); };
struct Cln_35 { void f(); };
struct Cln_31 { void f(); };
extern void* g_16f89d0;         // d3d device object pointer
extern void* g_16f65a0;         // active vertex descriptor
extern int   g_16f9110;         // soft-state dirty flags
extern int   g_16f9138;
extern int   g_16f913c;
extern int   g_16f9140;
extern void* g_16f6568;         // shader state object pointer
// ---- items of slice s00961db0 end

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
// (the local Stopwatch stand-in is gone: FadeEffect uses EA::Stopwatch from EA/Stopwatch.h)
// ---- items of slice s00962ff0 end

// ---- items of slice s00966b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);                            // 0xf47380
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* name,
                                       int, int, int, int);                // 0xf473a0
static inline const uint32_t& max_u32(const uint32_t& a, const uint32_t& b)
{
    return a < b ? b : a;
}
struct S_967690 { void     __thiscall m(); };
struct S_9676a0 { uint32_t __thiscall m(uint32_t, uint32_t); };
struct S_9676f0 { void     __thiscall m(uint32_t, const char*); };
struct S_967770 { uint32_t __thiscall m(uint32_t); };
struct S_9677d0 { uint32_t* __thiscall m(uint32_t); };
// ---- items of slice s00966b20 end

// ---- items of slice s00968da0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_166b1bc;            // 0x166b1bc
// ---- items of slice s00968da0 end

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0096eca0(void);
extern "C" void FUN_00963e50(void);
extern "C" void FUN_00988670(void);
extern "C" void FUN_00983ac0(void);
extern "C" void FUN_00980f30(void);
extern "C" void FUN_00985c30(void);
extern "C" void FUN_0096b310(void);
extern "C" void FUN_00970170(void);
extern "C" void FUN_0097ec60(void);
extern "C" void FUN_009891e0(void);
extern "C" void FUN_00967820(void);
extern "C" void FUN_00992590(void);
extern "C" void FUN_00991f20(void);
extern "C" void FUN_00969aa0(void);
extern "C" void FUN_0098f330(void);
extern "C" void FUN_009878e0(void);
extern "C" void FUN_00963ea0(void);
extern "C" void FUN_00963ef0(void);
extern "C" void FUN_00983b10(void);
extern "C" void FUN_00980f80(void);
extern "C" void FUN_00985c80(void);
extern "C" void FUN_0096b360(void);
extern "C" void FUN_0097d090(void);
extern "C" void FUN_00967870(void);
extern "C" void FUN_0096f220(void);
extern "C" void FUN_0097e780(void);
extern "C" void FUN_0097e7d0(void);
extern "C" void FUN_0096ff00(void);
extern "C" void FUN_0096f040(void);
extern "C" void FUN_0097e480(void);
extern "C" void FUN_009800c0(void);
extern "C" void FUN_009672b0(void);
extern "C" void FUN_00980be0(void);
extern "C" void FUN_009804c0(void);
extern "C" void FUN_009806f0(void);
extern "C" void FUN_0097d9e0(void);
#pragma intrinsic(sqrt)
struct ExtBase {
    void ctor963db0();      // 0x963db0
    void dtor980420();      // 0x980420 Navigator::~Navigator
    void ctor980430();      // 0x980430 ExplicitNavigator ctor
};
struct GlyphLayoutInfo { unsigned char b[0x20]; };
struct GlyphVec {
    unsigned v[3];
    void insert(GlyphLayoutInfo* pos, unsigned n, GlyphLayoutInfo* val);   // 0x96e540
    void resize(unsigned n);                                                // 0x96e6d0
    void* FUN_00899420(void* first, void* last);                            // 0x899420 vector::erase (thiscall)
    unsigned size() const { return (unsigned)(((int)v[1] - (int)v[0]) >> 5); }
};
struct Obj96 {
    char pad[0x1c];
    int  f1c;
    bool m(void* sink, void* arg2);   // 0x96ecf0
};
struct FadeEffect {
    void* v0; void* v1; void* v2[2];
    FadeEffect();   // 0x96f060
};
// ---- items of slice s0096e3a0 end

// @ 0x00962d10
void S962d10::f()
{
  int* self = (int*)this;
  if (self[1]) { ((Cln_e*)self[1])->f(); g_free_16f4aec((void*)self[1]); self[1] = 0; }
  if (self[8]) { g_free_16f4aec((void*)self[8]); self[8] = 0; }
  if (self[7]) { ((Cln_4e*)self[7])->f(); g_free_16f4aec((void*)self[7]); self[7] = 0; }
  if (self[6]) { ((Cln_35*)self[6])->f(); g_free_16f4aec((void*)self[6]); self[6] = 0; }
  if (self[2]) { ((Cln_31*)self[2])->f(); g_free_16f4aec((void*)self[2]); self[2] = 0; }
}

// @ 0x00962da0
bool S962da0::f()
{
  char* self = (char*)this;
  void* dev = g_16f89d0;
  void* vd = *(void**)(self + 8);
  if (g_16f65a0 == 0 || !FUN_011f2e70(g_16f65a0, vd))
    g_16f9110 |= 0x100000;
  g_16f65a0 = vd;
  ((S962da0c*)vd)->f();
  int a = *(int*)(*(int*)(self + 0x18) + 4);
  unsigned s = *(unsigned char*)(*(int*)(self + 8) + 0xf);
  if (g_16f9138 != a || g_16f913c != 0 || g_16f9140 != s) {
    int r = ((Vtbl190*)*(void**)dev)->fn(dev, 0, a, 0, (int)s);
    if (r < 0) return false;
    g_16f9138 = a; g_16f913c = 0; g_16f9140 = s;
  }
  int i = 1;
  unsigned off = 0xc;
  do {
    if (*(int*)((char*)&g_16f9138 + off) != 0) {
      int r = ((Vtbl190*)*(void**)dev)->fn(dev, i, 0, 0, 0);
      if (r < 0) return false;
      *(int*)((char*)&g_16f9138 + off) = 0;
      *(int*)((char*)&g_16f913c + off) = 0;
      *(int*)((char*)&g_16f9140 + off) = 0;
    }
    off += 0xc;
    i++;
  } while (off < 0x30);
  return true;
}

// @ 0x00962e80
unsigned S962e80::f(unsigned a, unsigned b)
{
  char* self = (char*)this;
  *(unsigned*)(self + 0xc) = a;
  unsigned old0 = *(unsigned*)(self + 0x10);
  *(unsigned*)(self + 0x14) = b;
  if (old0 + b > 0x1000) {
    *(unsigned*)(self + 0x10) = 0;
    if (b > 0x1000) return 0;
  }
  unsigned old = *(unsigned*)(self + 0x10);
  int* p = *(int**)(self + 0x18);
  unsigned flags = ((old != 0) * 4u + 4u) | 2u;
  unsigned n = b ? b : (unsigned)p[3];
  unsigned char stride = *(unsigned char*)((size_t)p[0] + 0xf);
  return ((S11f36a0*)p)->FUN_011f3620((unsigned char)flags, (unsigned)(p[2] + old) * stride,
                                     (unsigned)stride * n);
}

// @ 0x00962f00
void S962f00::f()
{
  char* self = (char*)this;
  ((S11f36a0*)*(void**)(self + 0x18))->f();
  void* dev = g_16f89d0;
  FUN_011f21a0();
  void* shader = g_16f6568;
  int (*sfn)(int) = *(int(**)(int))((char*)shader + 0x14);
  if (!sfn(*(int*)(self + 0x20))) return;
  g_16f9110 = 0;
  int idx = 0;
  if (*(int*)(self + 0xc) == 2) idx = *(int*)*(int**)(self + 0x1c);
  if (g_16f8afc != idx) {
    if (((Vtbl1a0*)*(void**)dev)->fn(dev, idx) < 0) return;
    g_16f8afc = idx;
  }
  switch (*(int*)(self + 0xc)) {
    case 0:
      ((Vtbl144*)*(void**)dev)->fn(dev, 2, *(int*)(self + 0x10), (int)(*(unsigned*)(self + 0x14) >> 1));
      break;
    case 1:
      ((Vtbl144*)*(void**)dev)->fn(dev, 4, *(int*)(self + 0x10), (int)(*(unsigned*)(self + 0x14) / 3));
      break;
    case 2:
      ((Vtbl148*)*(void**)dev)->fn(dev, 4, *(int*)(self + 0x10), 0, *(int*)(self + 0x14),
                                    *(int*)(*(int*)(self + 0x1c) + 4),
                                    (int)(*(unsigned*)(self + 0x14) >> 1));
      break;
  }
  *(int*)(self + 0x10) += *(int*)(self + 0x14);
}

// @ 0x00963db0
void* __fastcall FadeEffect_Ctor(void* self)
{
    *(void**)((char*)self + 4) = (void*)0x13fa72c;
    *(int*)  ((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = (void*)0x14085f0;
    *(void**)self = (void*)0x1440d88;
    *(void**)((char*)self + 4) = (void*)0x1440d6c;
    *(void**)((char*)self + 0xc) = (void*)0x1440d30;
    *(float*) ((char*)self + 0x10) = 0.0f;
    EA::Stopwatch* sw = (EA::Stopwatch*)((char*)self + 0x18);
    sw->EA::Stopwatch::Stopwatch(EA::Stopwatch::kUnitsCycles, false);
    *(int*)  ((char*)self + 0x30) = 1;
    *(int*)  ((char*)self + 0x34) = 0;
    *(float*)((char*)self + 0x38) = 0.0f;
    *(float*)((char*)self + 0x3c) = 0.0f;
    *(float*)((char*)self + 0x40) = 0.1f;
    *(float*)((char*)self + 0x44) = 0.0f;
    *(float*)((char*)self + 0x48) = 0.0f;
    *(float*)((char*)self + 0x4c) = 0.0f;
    *(char*) ((char*)self + 0x50) = 0;
    *(int*)  ((char*)self + 0x54) = 2;
    *(int*)  ((char*)self + 0x58) = 0;
    sw->SetUnits(EA::Stopwatch::kUnitsSeconds);
    return self;
}

// @ 0x00967690
void S_967690::m()
{
    uint32_t* this_ = (uint32_t*)this;
    this_[3] = this_[0];
    this_[2] = this_[0];
}

// @ 0x009676a0
uint32_t S_9676a0::m(uint32_t param_2, uint32_t param_3)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t m = ~(((param_3 - 1) | 7) + 1 - 1);
    uint32_t cur = this_[2];
    uint32_t last = this_[3];
    uint32_t a;
    if (cur > last) {
        a = (cur - param_2) & m;
        if (a <= last) {
            return 0;
        }
        this_[2] = a;
        return a;
    }
    a = (cur - param_2) & m;
    if (a >= this_[0]) {
        this_[2] = a;
        return a;
    }
    a = (this_[1] - param_2) & m;
    if (a <= last) {
        return 0;
    }
    this_[2] = a;
    return a;
}

// @ 0x009676f0
void S_9676f0::m(uint32_t param_2, const char* param_3)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t base = this_[0];
    if (this_[1] - base == param_2)
        return;
    if (base != 0) {
        FUN_00f47380((void*)base);
        this_[3] = 0;
        this_[2] = 0;
        this_[1] = 0;
        this_[0] = 0;
    }
    if (param_2 > 0) {
        if (param_3 == 0)
            param_3 = "UTFWin/CircularAllocator";
        void* p = FUN_00f473a0(param_2, param_3, 0, 0, 0, 0);
        this_[0] = (uint32_t)p;
        this_[1] = (uint32_t)p + param_2;
        this_[3] = (uint32_t)p;
        this_[2] = (uint32_t)p;
    }
}

// @ 0x00967770
uint32_t S_967770::m(uint32_t param_2)
{
    uint32_t* this_ = (uint32_t*)this;
    uint32_t align = ((param_2 - 1) | 7) + 1;
    uint32_t cur = this_[2];
    uint32_t last = this_[3];
    if (cur <= last) {
        uint32_t m = ~(align - 1);
        uint32_t b = this_[1] - ((last + align) & m);
        uint32_t a = cur - ((this_[0] + align - 1) & m);
        return max_u32(a, b);
    }
    uint32_t m = ~(align - 1);
    return cur - ((last + align) & m);
}

// @ 0x009677d0
uint32_t* S_9677d0::m(uint32_t param_2)
{
    uint32_t* this_ = (uint32_t*)this;
    this_[0] = 0;
    this_[1] = 0;
    this_[2] = 0;
    this_[3] = 0;
    if (param_2 == 0)
        return this_;
    if (!(param_2 > 0))
        return this_;
    void* p = FUN_00f473a0(param_2, "UTFWin/CircularAllocator", 0, 0, 0, 0);
    this_[0] = (uint32_t)p;
    this_[1] = (uint32_t)p + param_2;
    this_[3] = (uint32_t)p;
    this_[2] = (uint32_t)p;
    return this_;
}

// @ 0x00969ae0
void SetComboAlpha(float v)
{
    if (v >= 0.0f && v <= 1.0f)
        g_166b1bc = v;
}

// @ 0x0096e6d0
void GlyphVec::resize(unsigned n)
{
    if (n > size()) {
        GlyphLayoutInfo tmp;
        for (int i = 0; i < 8; i++) ((unsigned*)&tmp)[i] = 0;
        insert((GlyphLayoutInfo*)v[1], n - size(), &tmp);
        return;
    }
    FUN_00899420((void*)((unsigned)v[0] + n * 0x20), (void*)v[1]);
}

// @ 0x0096ecf0
bool Obj96::m(void* sink, void* arg2)
{
    if (f1c != 0) {
        (*(void(__thiscall**)(void*, void*, int))((char*)*(void**)sink + 0x4c))(sink, arg2, f1c);
        return true;
    }
    return false;
}

// @ 0x0096ef80
void FUN_0096ef80(void)
{
    FUN_00963e50();
    FUN_00988670();
    FUN_00983ac0();
    FUN_00980f30();
    FUN_00985c30();
    FUN_0096b310();
    FUN_00970170();
    FUN_0097ec60();
    FUN_009891e0();
    FUN_00967820();
    FUN_00992590();
    FUN_00991f20();
    FUN_00969aa0();
    FUN_0098f330();
    FUN_009878e0();
    FUN_00963ea0();
    FUN_00963ef0();
    FUN_00983b10();
    FUN_00980f80();
    FUN_00985c80();
    FUN_0096b360();
    FUN_0097d090();
    FUN_00967870();
    FUN_0096f220();
    FUN_0097e780();
    FUN_0097e7d0();
    FUN_0096ff00();
    FUN_0096f040();
    FUN_0097e480();
    FUN_009800c0();
    FUN_009672b0();
    FUN_00980be0();
    FUN_009804c0();
    FUN_009806f0();
    FUN_0096eca0();
    FUN_0097d9e0();
}

// @ 0x0096f060
FadeEffect::FadeEffect()
{
    ((ExtBase*)this)->ctor963db0();
    *(void**)((char*)this + 0x00) = (void*)0x14422f8;
    *(void**)((char*)this + 0x04) = (void*)0x14422e0;
    *(void**)((char*)this + 0x0c) = (void*)0x14422a4;
}
