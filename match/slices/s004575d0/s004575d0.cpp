// slice s004575d0 -- SP::cSPEditorBudget and small editor helpers.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"
#include <xmmintrin.h>

struct Float4 { float x, y, z, w; };

// @ 0x004580c0
unsigned int ColorRGBAToU32(const float* c) {
    __m128 v;
    v = _mm_load_ss(&c[0]);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    unsigned char r = (unsigned char)_mm_cvtss_si32(v);
    v = _mm_load_ss(&c[1]);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    unsigned char g = (unsigned char)_mm_cvtss_si32(v);
    v = _mm_load_ss(&c[2]);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    unsigned char b = (unsigned char)_mm_cvtss_si32(v);
    v = _mm_load_ss(&c[3]);
    v = _mm_max_ss(_mm_setzero_ps(), v);
    v = _mm_mul_ss(v, _mm_set_ss(255.0f));
    v = _mm_min_ss(v, _mm_set_ss(255.0f));
    unsigned char a = (unsigned char)_mm_cvtss_si32(v);
    return ((unsigned int)r << 0x10) | ((unsigned int)g << 8) | (unsigned int)b | ((unsigned int)a << 0x18);
}

struct cSPEditorBudget {
    char pad0[0x34];
    void* mLayout;        // +0x34

    void* AsInterface(unsigned int id);   // 0x00457950
    void  Shutdown();                     // 0x004581d0
    void  Init();                         // 0x00457af0
};

// @ 0x00457950
void* cSPEditorBudget::AsInterface(unsigned int id) {
    unsigned int iid = id;
    void* result;
    if (iid == 0xee3f516e) {
        if ((char*)this - 4 == 0)
            result = 0;
        else
            result = this;
    } else if (iid == 0x726ecf35) {
        result = (char*)this - 4;
    } else {
        result = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// Remaining functions (approximations; not byte-exact)
// ---------------------------------------------------------------------------
extern void  FUN_00811ad0(void* layout, int one);   // cSPUILayout::Shutdown
extern void* SP_MessageServer();                    // 0x0067dcc0

struct MessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(void* self, unsigned int msg, int flags);   // slot 11 (+0x2c)
};

// @ 0x004581d0
void cSPEditorBudget::Shutdown() {
    if (mLayout != 0) {
        FUN_00811ad0(mLayout, 1);
        if (mLayout != 0) {
            void* old = mLayout;
            mLayout = 0;
            ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
        }
    }
    MessageServer* ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9ce, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x522f9cd, 0xffffd8f1);
    ms = (MessageServer*)SP_MessageServer();
    ms->Send(this, 0x3150c27, 0xffffd8f1);
}

// @ 0x004575d0, 0x00457840, 0x004579a0, 0x00457af0: large bodies
// (construct/blow-away/Init) only approximated.
void* FUN_004575d0(int* self) {
    (void)self;
    return 0;
}
void FUN_00457840(int* self) {
    self[0] = 0x13ec584;
    self[1] = 0x13ec574;
    self[2] = 0x13ec564;
    for (unsigned int it = (unsigned int)self[0x16]; it < (unsigned int)self[0x17]; it += 4) {
    }
    self[2] = 0x13ec458;
    self[1] = 0x13eb938;
    self[0] = 0x13eb394;
}
void FUN_004579a0(int* self) {
    (void)self;
}
void cSPEditorBudget::Init() {
}
