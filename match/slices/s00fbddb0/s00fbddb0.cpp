// Slice s00fbddb0 -- SP::cTerrainStateMgr terraform state (retail layout).
//   00fbddb0  cTerrainStateMgr::SetTerraformValues
//   00fbdee0  cTerrainStateMgr::RefreshTerraformValues
//   00fbe050  cTerrainStateMgr::StateParms::Reset       (sub-object at this+8)
//   00fbe130  cTerrainStateMgr::cTerrainStateMgr
//   00fbe390  PlanarDef copy ctor
//   00fbe410  StateOutputParms copy ctor
//   00fbe4f0  cTerrainStateMgr::~cTerrainStateMgr
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// ---- SSE clamp helper (the original's inline EA math, maxss/minss) ----------
inline float Clamp01(float v)
{
    float hi = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

// ---- callees ---------------------------------------------------------------
float __cdecl FUN_00fc2040(float, float);              // 0xfc2040
float __cdecl FUN_00fc2300(float, float, float);       // 0xfc2300

struct cTerrainSphere {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual uint32_t v0c();                            // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void vt48(int arg);                        // +0x48
};

// ---------- 20-byte eastl-style vector (begin/end/cap + 8-byte allocator slot)
struct E12 { uint32_t a, b, c; };
struct E8  { uint32_t a, b; };

struct Vec12 {
    E12* mpBegin; E12* mpEnd; E12* mpCap; uint32_t mAlloc0, mAlloc1;
    __forceinline void erase(E12* first, E12* last)
    {
        E12* d = first;
        for (E12* s = last; s != mpEnd; ++s)
            *d++ = *s;
        mpEnd -= last - first;
    }
};

struct Vec8 {
    E8* mpBegin; E8* mpEnd; E8* mpCap; uint32_t mAlloc0, mAlloc1;
    __forceinline void erase(E8* first, E8* last)
    {
        E8* d = first;
        for (E8* s = last; s != mpEnd; ++s)
            *d++ = *s;
        mpEnd -= last - first;
    }
};

// Objects reachable from the +0x300..+0x32c slots: virtual slot +4 releases.
struct IRefObject {
    virtual void v00();
    virtual void Release();                            // +0x04
    virtual void v08();
    virtual void v0c();
};

// Slots whose lifetime is governed by an atomic count at object+8 (no virtual call).
struct AtomicRef {
    char pad00[8];
    volatile long mnRefCount;
    int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

struct IEffect {
    virtual void v00();                                // +0x00
    virtual void Release();                            // +0x04
    virtual bool Activate(unsigned int key, int arg, IEffect** out); // +0x08
    virtual void SetActive(int on);                    // +0x0c
};
struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(int arg);                         // +0x50
};
namespace SP { IEffectsManager* __cdecl EffectsManager(); }   // 0x67ddd0
struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(float arg);                       // +0xbc
};
IApp* FUN_0067de00();                                  // 0x67de00

// small object at this+4 that receives the terrain scale
struct TerrainScaleTarget {
    void SetScale(float v);                            // 0xff03c0
};

// ---------- cTerrainStateMgr -------------------------------------------------
struct CoreState {
    char pad000[0x120];
    uint32_t m120, m124, m128;
    char pad12c[0x150 - 0x12c];
    uint32_t m150, m154, m158;
    char pad15c[0x164 - 0x15c];
    uint32_t m164, m168, m16c;
    char pad170[0x178 - 0x170];
    uint32_t m178, m17c, m180;
    char pad184[0x18c - 0x184];
    uint32_t m18c, m190, m194;
    char pad198[0x1a0 - 0x198];
    uint32_t m1a0, m1a4, m1a8;
    char pad1ac[0x1b4 - 0x1ac];
    uint32_t m1b4, m1b8, m1bc;
    char pad1c0[0x1c8 - 0x1c0];
    uint32_t m1c8, m1cc, m1d0;
    char pad1d4[0x1ec - 0x1d4];
    uint32_t m1ec;
    char pad1f0[0x204 - 0x1f0];
    uint32_t m204, m208, m20c, m210;
    char pad214[0x290 - 0x214];
    uint32_t m290, m294, m298;
    char pad29c[0x2a4 - 0x29c];
    uint32_t m2a4, m2a8, m2ac;
    CoreState* Reset();
};

extern float gTerraformColor[4];                       // 0x016d671c

struct cTerrainStateMgr {
    cTerrainSphere* mpTerrainSphere;   // +0x000
    uint32_t m004;                     // +0x004
    char pad008[0x18 - 8];
    float m18;                         // +0x018
    char pad01c[0x28 - 0x1c];
    float m28;                         // +0x028
    float m02c;                        // +0x02c
    float m030;                        // +0x030
    char pad034[0x158 - 0x34];
    Vec12 m158[4];                     // +0x158
    Vec8  m1a8;                        // +0x1a8
    Vec12 m1bc;                        // +0x1bc
    Vec8  m1d0;                        // +0x1d0
    char pad1e4[0x2f4 - 0x1e4];
    uint32_t m2f4, m2f8, m2fc, m300, m304, m308, m30c, m310, m314, m318, m31c;
    uint32_t m320, m324, m328, m32c, m330, m334, m338, m33c, m340, m344, m348;
    char pad34c[0x5ac - 0x34c];
    uint8_t m5ac;                      // +0x5ac
    uint8_t m5ad;                      // +0x5ad
    char pad5ae[2];
    uint32_t m5b0, m5b4, m5b8;
    char pad5bc[4];
    uint32_t m5c0, m5c4;
    float m5c8[4], m5d8[4], m5e8[4];   // +0x5c8 three Vector4
    IEffect* m5f8;                     // +0x5f8
    IEffect* m5fc;                     // +0x5fc
    float m600, m604, m608, m60c, m610, m614, m618, m61c, m620, m624;
    uint8_t m628[0x194];               // +0x628
    uint8_t m7bc;                      // +0x7bc
    char pad7bd[3];
    uint8_t m7c0[0x180];               // +0x7c0
    uint8_t m940[0x180];               // +0x940
    uint8_t mac0[0x180];               // +0xac0

    void SetTemperature(float t);                      // 0xfbcc20
    void SetTerraformAmount(float v);                  // 0xfbdaa0
    float ComputeTerraformScale(float v);              // 0xfbd9d0
    void SetTerraformValues(float a, float b, bool c); // 0xfbddb0
    void RefreshTerraformValues();                     // 0xfbdee0
    cTerrainStateMgr(cTerrainSphere* sphere);          // 0xfbe130
    ~cTerrainStateMgr();                               // 0xfbe4f0
};

// @ 0x00fbddb0
void cTerrainStateMgr::SetTerraformValues(float a, float b, bool c)
{
    float ca = Clamp01(a);
    float cb = Clamp01(b);
    float v = (1.0f - ca) - m624;
    if (fabsf(m02c - v) > 0.001f) {
        m02c = v;
        ((void(__thiscall*)(void*, int))(*(void***)mpTerrainSphere)[0x48 / 4])(mpTerrainSphere, 2);
    }
    SetTemperature(cb);
    float r = FUN_00fc2040(ca, cb);
    if (fabsf(m28 - r) > 0.001f)
        m28 = r;
    if (c)
        SetTerraformAmount(FUN_00fc2300(ca, cb, m600));
    m5ad = 1;
}

// @ 0x00fbdee0
void cTerrainStateMgr::RefreshTerraformValues()
{
    float a01 = 1.0f - m02c;
    float t = m030;
    float r = FUN_00fc2040(a01, t);
    if (fabsf(m28 - r) > 0.001f)
        m28 = r;
    float q = ComputeTerraformScale(FUN_00fc2300(a01, t, m600));
    m18 = q;
    ((TerrainScaleTarget*)*(void**)((char*)this + 4))->SetScale(q * 2.0f - 1.0f);
    m5ad = 1;
}

// @ 0x00fbe050
CoreState* CoreState::Reset()
{
    m120 = 0; m124 = 0; m128 = 0;
    m150 = 0; m154 = 0; m158 = 0;
    m164 = 0; m168 = 0; m16c = 0;
    m178 = 0; m17c = 0; m180 = 0;
    m18c = 0; m190 = 0; m194 = 0;
    m1a0 = 0; m1a4 = 0; m1a8 = 0;
    m1b4 = 0; m1b8 = 0; m1bc = 0;
    m1c8 = 0; m1cc = 0; m1d0 = 0;
    m1ec = 0;
    m204 = 0; m208 = 0; m20c = 0; m210 = 0;
    m290 = 0; m294 = 0; m298 = 0;
    m2a4 = 0; m2a8 = 0; m2ac = 0;
    return this;
}

// @ 0x00fbe130
cTerrainStateMgr::cTerrainStateMgr(cTerrainSphere* sphere)
{
    mpTerrainSphere = sphere;
    m004 = sphere->v0c();
    ((CoreState*)((char*)this + 8))->Reset();

    m2f4 = 0; m2f8 = 0; m2fc = 0; m300 = 0; m304 = 0;
    m308 = 0; m30c = 0; m310 = 0; m314 = 0; m318 = 0;
    m31c = 0; m320 = 0; m324 = 0; m328 = 0; m32c = 0;
    m330 = 0; m334 = 0; m338 = 0; m33c = 0; m340 = 0;
    m344 = 0; m348 = 0;

    m5ac = 1;
    m5ad = 0;
    m5b0 = 0; m5b4 = 0; m5b8 = 0;
    m5c0 = 0; m5c4 = 0;

    m5c8[0] = gTerraformColor[0]; m5c8[1] = gTerraformColor[1];
    m5c8[2] = gTerraformColor[2]; m5c8[3] = gTerraformColor[3];
    m5d8[0] = gTerraformColor[0]; m5d8[1] = gTerraformColor[1];
    m5d8[2] = gTerraformColor[2]; m5d8[3] = gTerraformColor[3];
    m5e8[0] = gTerraformColor[0]; m5e8[1] = gTerraformColor[1];
    m5e8[2] = gTerraformColor[2]; m5e8[3] = gTerraformColor[3];

    m600 = -1.0f;
    m5f8 = 0;
    m5fc = 0;
    m604 = 0.5f;
    m608 = 0.0f;
    m60c = 1.0f;
    m610 = 1.0f;
    m614 = 0.0f; m618 = 0.0f; m61c = 0.0f; m620 = 0.0f; m624 = 0.0f;

    m7bc = 0;
    memset(m628, 0, 0x194);
    memset(m7c0, 0, 0x180);
    memset(m940, 0, 0x180);
    memset(mac0, 0, 0x180);
}

// ---------- PlanarDef (00fbe390) and StateOutputParms (00fbe410) -------------
struct Elem20a { uint32_t w0, w1, w2, w3, w4; Elem20a& operator=(const Elem20a&); };
struct Elem20b { uint32_t w0, w1, w2, w3, w4; Elem20b& operator=(const Elem20b&); };

struct PlanarDef {
    float f00, f04, f08, f0c, f10;
    Elem20a arr[4];                    // +0x14 four 20-byte sub-vectors
    Elem20b v64;                       // +0x64
    Elem20a v78;                       // +0x78
    Elem20b v8c;                       // +0x8c
    PlanarDef(const PlanarDef& o);
};

// @ 0x00fbe390
PlanarDef::PlanarDef(const PlanarDef& o)
{
    f00 = o.f00; f04 = o.f04; f08 = o.f08; f0c = o.f0c; f10 = o.f10;
    for (int i = 0; i < 4; i++) arr[i] = o.arr[i];
    v64 = o.v64;
    v78 = o.v78;
    v8c = o.v8c;
}

struct Elem4B {
    uint32_t w0, w1, w2, w3, w4;
    Elem4B& operator=(const Elem4B&);      // 0x0050d4e0
};
struct Elem12B {
    uint32_t w0, w1, w2, w3, w4;
    Elem12B& operator=(const Elem12B&);    // 0x00473500
};

struct StateOutputParms {
    uint8_t b00;
    uint32_t d04, d08, d0c, d10, d14, d18, d1c, d20, d24, d28, d2c, d30;
    Elem4B  v34;                       // +0x34
    Elem12B v48;                       // +0x48
    float f5c, f60, f64, f68, f6c, f70, f74, f78, f7c, f80, f84, f88, f8c;
    StateOutputParms(const StateOutputParms& o);
};

// @ 0x00fbe410
StateOutputParms::StateOutputParms(const StateOutputParms& o)
{
    b00 = o.b00;
    d04 = o.d04; d08 = o.d08; d0c = o.d0c; d10 = o.d10;
    d14 = o.d14; d18 = o.d18; d1c = o.d1c; d20 = o.d20;
    d24 = o.d24; d28 = o.d28; d2c = o.d2c; d30 = o.d30;
    v34 = o.v34;
    v48 = o.v48;
    f5c = o.f5c; f60 = o.f60; f64 = o.f64; f68 = o.f68;
    f6c = o.f6c; f70 = o.f70; f74 = o.f74; f78 = o.f78;
    f7c = o.f7c; f80 = o.f80; f84 = o.f84; f88 = o.f88; f8c = o.f8c;
}

// @ 0x00fbe4f0
cTerrainStateMgr::~cTerrainStateMgr()
{
    for (int i = 0; i < 4; i++)
        m158[i].erase(m158[i].mpBegin, m158[i].mpEnd);
    m1a8.erase(m1a8.mpBegin, m1a8.mpEnd);
    m1bc.erase(m1bc.mpBegin, m1bc.mpEnd);
    m1d0.erase(m1d0.mpBegin, m1d0.mpEnd);

    if (m328) { AtomicRef* p = (AtomicRef*)m328; m328 = 0; p->Release(); }
    if (m304) { AtomicRef* p = (AtomicRef*)m304; m304 = 0; p->Release(); }
    if (m31c) { AtomicRef* p = (AtomicRef*)m31c; m31c = 0; p->Release(); }
    if (m320) { AtomicRef* p = (AtomicRef*)m320; m320 = 0; p->Release(); }
    if (m32c) { IRefObject* p = (IRefObject*)m32c; m32c = 0; p->Release(); }
    if (m300) { AtomicRef* p = (AtomicRef*)m300; m300 = 0; p->Release(); }
    if (m5fc) {
        m5fc->SetActive(0);
        if (m5fc) { IEffect* p = m5fc; m5fc = 0; p->Release(); }
    }
    FUN_0067de00()->vbc(1.0f);
    if (m5f8) {
        if (m5f8) {
            IEffect* p = (IEffect*)m5f8;
            m5f8 = 0;
            p->Release();
        }
        SP::EffectsManager()->v50(0x23541242);
    }
}
