// src/game/Swarm/ShakeDescription.cpp -- migrated from slice(s) s00abe110, s00abd170 by tools/migrate/rewrite.py
// Object file: Swarm/ShakeDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern void* const vtbl_14599ec;                  // 0x014599ec
extern void* const vtbl_14599e8;                  // 0x014599e8
extern void* const vtbl_13ef094;                  // 0x013ef094
extern const float kOne_1485720;                  // 0x01485720
extern const float k63_14321f8;                   // 0x014321f8
extern const float k9e84;                         // 0x01679e84
extern const float k9e88;                         // 0x01679e88
extern float* g_tabA_begin;                       // 0x01679e5c
extern float* g_tabA_end;                         // 0x01679e60
extern float* g_tabB_begin;                       // 0x01679e8c
extern const char kSwarm[];                       // 0x013f1fdc
extern "C" double __cdecl sqrt(double);

// ---- items of slice s00abd170 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VCV(p, off, a)  ((void(__thiscall*)(void*, int))VFN(p, off))((void*)(p), (int)(a))
#define VCM2(p, off, a, b) ((void(__thiscall*)(void*, float, float))VFN(p, off))((void*)(p), (a), (b))
#define D(p, off) (*(int*)((char*)(p) + (off)))
#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(unsigned char*)((char*)(p) + (off)))
#define W(p, off) (*(unsigned short*)((char*)(p) + (off)))
#define SV(p, off) (*(volatile int*)((char*)(p) + (off)))
#define SB(p, off) (*(volatile unsigned char*)((char*)(p) + (off)))
#define SF(p, off) (*(volatile float*)((char*)(p) + (off)))
struct Mat3 {
    float f0, f1, f2, f3, f4, f5, f6, f7, f8;
    Mat3() {}
    Mat3(const Mat3& o) { Assign(&o); }
    void Assign(const void* src);                // 0x0041cb40
};
struct CTrans {
    short a;                                     // +0x00
    short b;                                     // +0x02
    float x, y, z;                               // +0x04
    float w;                                     // +0x10
    Mat3  mat;                                   // +0x14
    void PreTransformBy(const CTrans& o);        // 0x00537f40
};
extern void* const vtbl_14599ec;                  // 0x014599ec
extern void* const vtbl_14599e8;                  // 0x014599e8
extern void* const vtbl_13ef094;                  // 0x013ef094
extern const float kOne_1485720;                  // 0x01485720
extern const float k63_14321f8;                   // 0x014321f8
extern const float k9e84;                         // 0x01679e84
extern const float k9e88;                         // 0x01679e88
extern float* g_tabA_begin;                       // 0x01679e5c
extern float* g_tabA_end;                         // 0x01679e60
extern float* g_tabB_begin;                       // 0x01679e8c
extern const char kSwarm[];                       // 0x013f1fdc
struct RandObj { double RandomDoubleUniform(); }; // 0x009360d0
extern RandObj g_random_16778dc;                  // 0x016778dc
void* __cdecl EAAllocate(uint32_t sz, const char* name, int, int, int, int); // 0x00f473a0
void  __cdecl EADealloc(void* p);                                            // 0x00f47380
void  __cdecl ReadInt32(void* s, void* out, int n, int a);                   // 0x0093a780
void  __cdecl ReadU8(void* s, void* out, int n);                             // 0x0093a6c0
void  __cdecl Ser7d27d0(void* s, void* out);                                 // 0x007d27d0
extern "C" double __cdecl sqrt(double);
struct Eff {
    char pad0[0xc];

    void FUN_00abd1f0(int a, int b, int c);
    void FUN_00abd230(int p);
    int  FUN_00abd270();
    void FUN_00abd290(char on);
    void FUN_00abd390(void* a, void* b);
    void* FUN_00abd3e0(int a, int b);
    void* FUN_00abd540(char del);
    void FUN_00abd590(void* p);
    void FUN_00abd640();
    void FUN_00abd6f0(float dt, int a, int b);
    void* FUN_00abd970(char del);
    void FUN_00abdb20(int unused);
    char FUN_00abdb70(int evt, void* data, int unused);
    void FUN_00abdbb0(float a, float b, int unused);
    void FUN_00abe090(CTrans* by, CTrans* src);
};
// ---- items of slice s00abd170 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern RandObj g_random_16778dc;                  // 0x016778dc

// ---- items of slice s00abe110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_vtbl_14599a8;
extern float g_hkRealOne;    // 0x1485720
extern float g_noiseSeed;    // 0x1679f4c
extern "C" void FUN_00abb820(void* dst, int count, void* src);
extern "C" void FUN_00d018d0(void* first, void* last);
extern "C" void FUN_008399d0(void* pos, const void* value);
typedef unsigned int u32;
void* __cdecl operator_new(u32 size, const char* tag, int a, int b, int c, int d);
namespace EA {
namespace Swarm {
struct cShakeDescription {
  void* mpVtbl;       // +0x00
  void* mpField04;    // +0x04
  u32 mHash;          // +0x08
  void* mpField0c;    // +0x0c
  float mField10;     // +0x10
  float mField14;     // +0x14
  void* mpField18;    // +0x18
  void* mpField1c;    // +0x1c
  void* mpField20;    // +0x20
  void* mpField24;    // +0x24
  void* mpField28;    // +0x28
  void* mpField2c;    // +0x2c
  void* mpField30;    // +0x30
  void* mpField34;    // +0x34
  void* mpField38;    // +0x38
  void* mpField3c;    // +0x3c
  float mField40;     // +0x40
  void* mpField44;    // +0x44
  float mField48;     // +0x48
  static cShakeDescription* create(void* a, void* b);
};
}
}
void __cdecl FUN_00abd9c0(void* a, void* b, void* obj);
struct INoiseConfig {
  virtual void* v00();
  virtual void* v04();
  virtual void* v08();
  virtual void* v0c();
  virtual void* v10();
  virtual void* v14();
  virtual void* v18();
  virtual void* v1c();
  virtual void* v20();
  virtual void* v24();
  virtual void* v28();
  virtual void* v2c();
};
struct RandPair {
  float mX;
  float mY;
};
struct RNG {
  int mState;
  void setSeed(u32 seed);
};
RandPair* g_pairs1Begin;
RandPair* g_pairs1End;
RandPair* g_pairs1Cap;
RandPair* g_pairs2Begin;
RandPair* g_pairs2End;
RandPair* g_pairs2Cap;
RandPair* __cdecl FUN_00abda70(RandPair* out, RNG* rng, const RandPair* minv, const RandPair* maxv);
struct cNoiseSource {
  char mPad00[0x10];
  void* mField10;  // +0x10
  void* mField14;  // +0x14
  void Init(INoiseConfig* cfg, void* a, void* b);
};
// ---- items of slice s00abe110 end

// @ 0x00abd970
void* Eff::FUN_00abd970(char del)
{
    int x = D(this, 0x2c);
    if (x != 0 && D((char*)x - 4, 0) != 0)
        EADealloc((void*)x);
    x = D(this, 0x18);
    if (x != 0 && D((char*)x - 4, 0) != 0)
        EADealloc((void*)x);
    D(this, 0) = (int)&vtbl_13ef094;
    if ((del & 1) != 0)
        EADealloc(this);
    return this;
}

// @ 0x00abd9c0
void __cdecl FUN_00abd9c0(int* stream, int unused, char* out)
{
    int v;
    unsigned char b;
    ReadInt32(stream, &v, 1, 0);
    D(out, 0xc) = v & 1;
    ReadInt32(stream, out + 0x10, 1, 0);
    ReadInt32(stream, out + 0x14, 1, 0);
    Ser7d27d0(stream, out + 0x18);
    Ser7d27d0(stream, out + 0x2c);
    ReadInt32(stream, out + 0x40, 1, 0);
    ReadU8(stream, &b, 1);
    D(out, 0x44) = b;
    ReadInt32(stream, out + 0x48, 1, 0);
}

// @ 0x00abda70
float* __cdecl FUN_00abda70(float* out, int unused, float* lo, float* hi)
{
    double l = *lo;
    double h = *hi;
    double r = g_random_16778dc.RandomDoubleUniform();
    double v = l + (h - l) * r;
    if (v >= h)
        v = h;
    else if (v < l)
        v = l;
    out[0] = (float)v;

    double h2;
    double l2;
    l2 = lo[1];
    h2 = hi[1];
    r = g_random_16778dc.RandomDoubleUniform();
    v = l2 + (h2 - l2) * r;
    if (v >= h2)
        v = h2;
    else if (v < l2)
        v = l2;
    out[1] = (float)v;
    return out;
}

// @ 0x00abdb20
void Eff::FUN_00abdb20(int unused)
{
    if (B(this, 0x18) == 0 && D(this, 0x10) != 0) {
        int e = D(this, 0xc);
        if (D(e, 0x18) != D(e, 0x1c) && D(e, 0x2c) != D(e, 0x30) &&
            F(e, 0x10) > 0.0f) {
            F(this, 0x28) = kOne_1485720 / F(e, 0x10);
            F(this, 0x2c) = 0.0f;
            F(this, 0x30) = 0.0f;
            B(this, 0x18) = 1;
        }
    }
}

// @ 0x00abdb70
char Eff::FUN_00abdb70(int evt, void* data, int unused)
{
    switch (evt) {
    case 0x101:
        F(this, 0x38) = F(data, 8);
        F(this, 0x3c) = F(data, 0x14);
        return 1;
    case 4:
        F(this, 0x34) = F(data, 0);
        return 1;
    }
    return 0;
}

// @ 0x00abdbb0
void Eff::FUN_00abdbb0(float a, float b, int unused)
{
    float one = kOne_1485720;
    F(this, 0x2c) = F(this, 0x28) * a + F(this, 0x2c);
    if (F(this, 0x2c) > one)
        F(this, 0x2c) = one;

    int cfg = D(this, 0xc);
    unsigned n = (unsigned)((D(cfg, 0x1c) - D(cfg, 0x18)) >> 2) - 1;
    float t = F(this, 0x2c);
    float v;
    if (n == 0) {
        v = *(float*)D(cfg, 0x18);
    } else {
        float f = (float)((double)n * t);
        int i = (int)f;
        float fr = f - (float)i;
        float* base = (float*)D(cfg, 0x18);
        if (fr <= 0.0f)
            v = base[i];
        else
            v = (base[i + 1] - base[i]) * fr + base[i];
    }

    float lo = F(this, 0x38);
    float amp = F(this, 0x3c);
    cfg = D(this, 0xc);
    float att = F(cfg, 0x48);
    amp = (amp - lo) * b + lo;
    amp *= F(this, 0x34);
    amp *= v;
    if (att > 0.0f) {
        float d;
        if ((B(cfg, 0xc) & 1) == 0) {
            float* m = (float*)D(this, 0x14);
            float px = F(this, 0x1c);
            float py = F(this, 0x20);
            float pz = F(this, 0x24);
            float X = m[7] * px + m[11] * py + m[15] * pz + m[19];
            float Y = m[8] * px + m[12] * py + m[16] * pz + m[20];
            float W = m[10] * px + m[14] * py + m[18] * pz + m[22];
            float nx = X / W;
            float ny = Y / W;
            d = nx * nx + ny * ny;
        } else {
            float* m = (float*)D(this, 0x14);
            float dx = m[0x80 / 4] - F(this, 0x1c);
            float dy = m[0x84 / 4] - F(this, 0x20);
            float dz = m[0x88 / 4] - F(this, 0x24);
            d = (float)sqrt((double)(dz * dz + dy * dy + dx * dx));
        }
        amp = (one / (att * d + one)) * amp;
    }

    cfg = D(this, 0xc);
    unsigned n2 = (unsigned)((D(cfg, 0x30) - D(cfg, 0x2c)) >> 2) - 1;
    float scale = amp / F(cfg, 0x40);
    float amp2 = F(cfg, 0x40) * amp;
    float t2 = F(this, 0x2c);
    float v2;
    if (n2 == 0) {
        v2 = *(float*)D(cfg, 0x2c);
    } else {
        float f = (float)((double)n2 * t2);
        int i = (int)f;
        float fr = f - (float)i;
        float* base = (float*)D(cfg, 0x2c);
        if (fr <= 0.0f)
            v2 = base[i];
        else
            v2 = (base[i + 1] - base[i]) * fr + base[i];
    }
    F(this, 0x30) = v2 * a + F(this, 0x30);

    unsigned tc = (unsigned)(((char*)g_tabA_end - (char*)g_tabA_begin) >> 3);
    float phase = F(this, 0x30) / (double)tc;
    int idx = (int)phase;
    if (phase < (float)idx)
        --idx;
    float frac = (float)((double)phase - (double)idx);

    float s1, s2;
    if (D(cfg, 0x44) == 0) {
        float* tab = g_tabA_begin;
        float x = frac * k63_14321f8;
        int i = (int)x;
        float fr = x - (float)i;
        if (fr <= 0.0f) {
            s1 = tab[i * 2];
            s2 = tab[i * 2 + 1];
        } else {
            s1 = (tab[i * 2 + 2] - tab[i * 2]) * fr + tab[i * 2];
            s2 = (tab[i * 2 + 3] - tab[i * 2 + 1]) * fr + tab[i * 2 + 1];
        }
    } else if (D(cfg, 0x44) == 1) {
        float* tab = g_tabB_begin;
        float x = frac * k63_14321f8;
        int i = (int)x;
        float fr = x - (float)i;
        if (fr <= 0.0f) {
            s1 = tab[i * 2];
            s2 = tab[i * 2 + 1];
        } else {
            s1 = (tab[i * 2 + 2] - tab[i * 2]) * fr + tab[i * 2];
            s2 = (tab[i * 2 + 3] - tab[i * 2 + 1]) * fr + tab[i * 2 + 1];
        }
    } else {
        s1 = 0.0f;
        s2 = 0.0f;
    }
    float o1 = s1 * scale;
    float o2 = s2 * amp2;
    VCM2(D(this, 0x10), 0x5c, o1, o2);
    if (F(this, 0x2c) == one)
        VCV(this, 0xc, 0);
}

// @ 0x00abe010
void* __cdecl FUN_00abe010(int arg)
{
    int* p = (int*)EAAllocate(0x40, kSwarm, 0, 0, 0, 0);
    if (p != 0) {
        SV(p, 8) = 0;
        SV(p, 4) = (int)&vtbl_13ef094;
        SF(p, 0x28) = 0.0f;
        SF(p, 0x2c) = 0.0f;
        SF(p, 0x30) = 0.0f;
        float one = kOne_1485720;
        SV(p, 0x10) = 0;
        SV(p, 0x14) = 0;
        SB(p, 0x18) = 0;
        SV(p, 0) = (int)&vtbl_14599ec;
        SV(p, 4) = (int)&vtbl_14599e8;
        SV(p, 0xc) = arg;
        SF(p, 0x34) = one;
        SF(p, 0x38) = k9e84;
        SF(p, 0x3c) = k9e88;
        return p;
    }
    return 0;
}

// @ 0x00abe090
void Eff::FUN_00abe090(CTrans* by, CTrans* src)
{
    CTrans t = *src;
    t.PreTransformBy(*by);
    D(this, 0x1c) = *(int*)&t.x;
    D(this, 0x20) = *(int*)&t.y;
    D(this, 0x24) = *(int*)&t.z;
}

// @ 0x00abe110
void cNoiseSource::Init(INoiseConfig* cfg, void* a, void* b)
{
  mField10 = cfg->v20();
  mField14 = cfg->v2c();
  if (g_pairs1Begin == g_pairs1End) {
    u32 count = (u32)(g_pairs1End - g_pairs1Begin);
    RandPair fillValue;
    if (count < 0x40) {
      FUN_00abb820(g_pairs1End, 0x40 - (int)count, &fillValue);
    } else {
      FUN_00d018d0(g_pairs1Begin + 0x40, g_pairs1End);
    }
    count = (u32)(g_pairs2End - g_pairs2Begin);
    if (count < 0x40) {
      FUN_00abb820(g_pairs2End, 0x40 - (int)count, &fillValue);
    } else {
      FUN_00d018d0(g_pairs2Begin + 0x40, g_pairs2End);
    }
    RNG rng;
    rng.setSeed(0x58);
    RandPair minv;
    RandPair maxv;
    maxv.mX = 10.0f;
    maxv.mY = 10.0f;
    minv.mX = -10.0f;
    minv.mY = -10.0f;
    for (int i = 0; i < 0x40; ++i) {
      RandPair* p = FUN_00abda70(&fillValue, &rng, &minv, &maxv);
      if (g_pairs1End < g_pairs1Cap) {
        *g_pairs1End = *p;
        ++g_pairs1End;
      } else {
        FUN_008399d0(g_pairs1End, p);
      }
    }
    float scale = g_noiseSeed * 0.015625f;
    for (int i = 0; i < 0x40; ++i) {
      RandPair p;
      p.mX = 0.0f;
      p.mY = (float)sinf((float)i * scale) * 10.0f;
      if (g_pairs2End < g_pairs2Cap) {
        *g_pairs2End = p;
        ++g_pairs2End;
      } else {
        FUN_008399d0(g_pairs2End, &p);
      }
    }
  }
}

// @ 0x00abe2f0
namespace EA { namespace Swarm {
cShakeDescription* cShakeDescription::create(void* a, void* b)
{
  cShakeDescription* p = (cShakeDescription*)operator_new(0x4c, "Swarm", 0, 0, 0, 0);
  cShakeDescription* result = 0;
  if (p) {
    float zero = 0.0f;
    float one = g_hkRealOne;
    p->mpField04 = 0;
    p->mHash = 0xcbb908f4;
    p->mpVtbl = (void*)&g_vtbl_14599a8;
    p->mpField0c = 0;
    p->mField10 = zero;
    p->mField14 = one;
    p->mpField18 = 0;
    p->mpField1c = 0;
    p->mpField20 = 0;
    p->mpField2c = 0;
    p->mpField30 = 0;
    p->mpField34 = 0;
    p->mpField44 = 0;
    p->mField40 = one;
    p->mField48 = zero;
    result = p;
  }
  FUN_00abd9c0(a, b, result);
  return result;
}
}}  // namespace EA::Swarm
