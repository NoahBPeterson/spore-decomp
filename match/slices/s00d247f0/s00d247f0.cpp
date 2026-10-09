// Slice s00d247f0 (batch cl1_new, slice 5): SP::cCreatureCamera::ReloadTuning.
// Flat if (p && p->GetProperty(id,&prop) && prop->type==K) dst = *prop->GetX(); chain; the original
// binary threads the repeated null tests into jumps to the common tail.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Status: complete; not byte-exact (callee-saved register assignment of pm/keyA/keyB differs, rest of body matches modulo shifts).
#include "types.h"

extern const float kDeg2Rad;   // 0x0147a304
extern const float kHalfDeg;   // 0x0147a330

extern bool g_158275c;
extern bool g_158275e;
extern bool g_158275f;
extern float g_1582760;
extern float g_1582764;
extern float g_1582768;
extern float g_158276c;
extern float g_1582770;
extern float g_1582774;
extern float g_1582778;
extern float g_158277c;
extern float g_1582780;
extern bool g_1582784;
extern bool g_1582785;
extern bool g_1582786;
extern float g_1582788;
extern float g_158278c;
extern float g_1582790;
extern float g_1582794;
extern float g_1582798;
extern float g_158279c;
extern float g_15827a0;
extern float g_15827a4;
extern float g_15827a8;
extern float g_15827b0;
extern float g_15827b4;
extern float g_15827b8;
extern float g_15827bc;
extern float g_15827c0;
extern float g_15827c4;
extern float g_15827c8;
extern float g_15827cc;
extern float g_15827d0;
extern float g_15827d4;
extern float g_15827d8;
extern float g_15827f0;
extern float g_15827f4;
extern float g_15827f8;
extern float g_15827fc;
extern float g_1582850;
extern float g_1582854;
extern float g_1582858;
extern float g_158285c;
extern float g_1582860;
extern float g_1582864;
extern float g_1582870;
extern float g_1582874;
extern bool g_169de80;
extern bool g_169de81;
extern bool g_169de82;
extern bool g_169de83;
extern bool g_169de84;
extern float g_169de90;
extern float g_169de94;
extern float g_169de98;

struct Property {
    uint32_t pad0[4];
    uint16_t pad10; uint16_t mnType;
    float* GetFloat();     // 0x0041ea70
    int*   GetInt();       // 0x0041e990
    bool*  GetBool();      // 0x0041e920
};

struct cPropertyList {
    virtual void AddRef();
    virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};

struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t a, uint32_t b, cPropertyList** out);   // +0x2c
};

struct Vec2 { float x, y; inline void Scale(float s) { x = x * s; y = y * s; } };

cPropertyManager* PropertyManager();                     // 0x0067de30
void* GetCurrentGameMode();                              // 0x00b5b800
struct TerrainMgr { cPropertyList* Fn1(); };             // 0x00b1daf0
TerrainMgr* __stdcall FUN_00b3d320(int a, void* mode);   // 0x00b3d320
extern bool g_158275d;
void GetPropertyAsVector2(cPropertyList* p, uint32_t id, Vec2* out);   // 0x006a10c0

extern char g_Mode_1654c10;
extern char g_Mode_1654c01;
// 0x00b1b104 is a plain constant here (it points into the middle of an instruction in .text)
static const unsigned kDead_b1b104 = 0x00b1b104;

struct Local { Property* prop; uint32_t a; const void* dead; uint32_t b; };

#define PF(id, dst, mul) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 0xd) dst = *loc.prop->GetFloat() mul
#define PB(id, dst) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 1) dst = *loc.prop->GetBool()
#define PI(id, dst) if (p && p->GetProperty(id, &loc.prop) && loc.prop->mnType == 9) { uint32_t v = *(uint32_t*)loc.prop->GetInt(); if (v <= 2) dst = v; }

namespace SP {
class cCreatureCamera {
public:
    uint32_t pad0[0x1ec / 4];

    int m_1ec;
    uint32_t pad_1f0[2];
    float m_1f8;
    float m_1fc;
    float m_200;
    uint32_t pad_204[1];
    float m_208;
    float m_20c;
    float m_210;
    float m_214;
    float m_218;
    float m_21c;
    float m_220;
    float m_224;
    float m_228;
    float m_22c;
    float m_230;
    float m_234;
    float m_238;
    uint32_t pad_23c[1];
    float mDistA_x;
    float mDistA_y;
    float mFar_x;
    float mFar_y;
    float m_250;
    float m_254;
    uint32_t pad_258[44];
    cPropertyList* mConfig;
    void ReloadTuning();
};

// @ 0x00d247f0
void cCreatureCamera::ReloadTuning()
{
    Local loc;
    cPropertyList* p;
    #define Q(id, dst, mul) if (mConfig && mConfig->GetProperty(id, &loc.prop) && loc.prop->mnType == 0xd) dst = *loc.prop->GetFloat() mul

    Q(0x1102b20, this->m_220);
    Q(0x1102b2f, this->m_224);
    #undef Q
    cPropertyManager* pm = PropertyManager();
    p = 0;
    uint32_t keyA = 0xd03a25cf, keyB = 0xad56080c;
    if (GetCurrentGameMode() == &g_Mode_1654c10) {
        keyA = 0x70ec1123; keyB = 0x408a0100;
        loc.dead = (const void*)kDead_b1b104;
    }
    if (p) { cPropertyList* t = p; p = 0; t->Release(); }
    if (pm->GetPropertyList(keyA, keyB, &p)) {
    PI(0xb060e649, this->m_1ec);
    PF(0xb03ee61d, this->m_218, );
    PF(0x503ee62b, this->m_21c, * kDeg2Rad);
    PF(0x303eb34d, this->m_210, );
    PF(0x703eb357, this->m_214, );
    PB(0xd0723c18, g_169de80);
    PB(0x30723c1d, g_169de81);
    PF(0x50723c22, g_1582850, * kDeg2Rad);
    PF(0xf0723c26, g_1582854, * kDeg2Rad);
    PF(0x70723c2c, g_1582858, * kDeg2Rad);
    PF(0x70723c32, g_158285c, * kDeg2Rad);
    PF(0x90723c38, g_1582860, * kDeg2Rad);
    PF(0xb0723c3c, g_1582864, * kDeg2Rad);
    PF(0x7b68967, this->m_208, * kDeg2Rad);
    PF(0x7b68979, this->m_20c, * kDeg2Rad);
    PB(0x19bdd9c, g_169de82);
    PB(0x19d778a, g_158275c);
    PF(0xf06d1e9b, this->m_1f8, * kHalfDeg);
    PF(0x306d1e9e, this->m_1fc, * kHalfDeg);
    PF(0x506d1ea0, this->m_200, );
        {
            GetPropertyAsVector2(p, 0xedb1e6ec, (Vec2*)&this->mDistA_x);
            float* pf = &this->mDistA_x;
            const float k1 = kDeg2Rad;
            *pf = *pf * k1;
            this->mDistA_y = this->mDistA_y * k1;
            GetPropertyAsVector2(p, 0x50c6e997, (Vec2*)&this->mFar_x);
            float* pf2 = &this->mFar_x;
            const float k2 = kDeg2Rad;
            *pf2 = *pf2 * k2;
            this->mFar_y = this->mFar_y * k2;
        }
    PF(0x22fb568c, this->m_250, );
    PF(0x14f8c017, g_15827b4, );
    PF(0xeec1bc52, g_15827a4, );
    PF(0x47a9c597, g_1582870, );
        g_1582870 = g_1582870 * kDeg2Rad;
    PF(0x8c78383d, g_1582874, );
        g_1582874 = g_1582874 * kDeg2Rad;
    PF(0xc8624936, g_15827a8, );
    PF(0x3dbe5f51, g_15827b0, );
    PF(0x126ecc27, g_15827b8, );
    PF(0xe815bc27, g_15827bc, );
    PF(0xb5f3ddd9, g_15827c0, );
    PF(0x61197290, g_15827c4, );
    PF(0xbc7c9cee, g_15827c8, );
    PF(0x60ea71bd, g_15827cc, );
    PF(0x8a1a6bc7, g_15827d0, );
    PF(0x29ce91, g_15827d4, );
    PF(0x8d98b7f8, g_15827d8, );
    PF(0xff6e121b, g_169de90, );
    PF(0xca517888, g_169de94, );
    PF(0x7be527ed, g_169de98, );
    PF(0x1a57b85, g_1582760, );
    PF(0x1a57b91, g_1582764, );
    PF(0x1a57b9b, g_1582768, );
    PF(0x2797fff, this->m_254, );
    PF(0xd03ee49b, this->m_228, );
    PF(0x703ee4a1, this->m_22c, );
    PF(0x503ee4a2, this->m_230, );
    PF(0x303ee4a4, this->m_234, );
    PF(0xf03ee4a8, this->m_238, );
    PB(0x50652350, g_158275e);
    PB(0x50692031, g_158275f);
    PF(0x90652352, g_158276c, );
    PF(0x70652353, g_1582770, );
    PF(0x10652354, g_1582774, );
    PF(0xf0652355, g_1582778, );
    PF(0xf0652356, g_158277c, );
    PF(0x3065235a, g_1582780, );
    PB(0x706913e6, g_1582784);
    PB(0x50692288, g_1582785);
    PF(0xf06913e7, g_1582788, );
    PF(0x706913e8, g_158278c, );
    PF(0xd06913ea, g_1582790, );
    PF(0xd06913ea, g_1582794, );
    PF(0x106913eb, g_1582798, );
    PF(0x506913ed, g_158279c, );
    PF(0xf0692887, g_15827a0, );
    PF(0x582c3384, g_15827f0, );
    PB(0x1c71aad, g_1582786);
    PB(0xb057d114, g_169de83);
    PB(0x306536a3, g_169de84);
    }
    {
        cPropertyList* np = FUN_00b3d320(1, GetCurrentGameMode())->Fn1();
        if (np != p) {
            cPropertyList* old = p;
            if (np) np->AddRef();
            p = np;
            if (old) old->Release();
        }
    }
    PF(0x2648458, g_15827f4, );
    PF(0x3d03d69, g_15827f8, );
    PF(0x556a736a, g_15827fc, );
    g_158275d = GetCurrentGameMode() == &g_Mode_1654c01;
    if (p) p->Release();
}
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
