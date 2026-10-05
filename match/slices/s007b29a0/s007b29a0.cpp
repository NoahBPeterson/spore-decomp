// Slice s007b29a0 — texture/thumbnail RTT and property-driven helpers. Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067dd40();                       // 0x0067DD40
void* __cdecl FUN_0067dd60();                       // 0x0067DD60
void* __cdecl FUN_0067dda0();                       // 0x0067DDA0
void* __cdecl FUN_011ef750(int, int, void*);        // 0x011EF750

struct PropHandle {
    char pad[0x10];
    unsigned char flags;                            // +0x10
    unsigned short type;                            // +0x12
    int* GetInt();                                  // 0x0041E990 __thiscall
};
struct PropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool v9(int hash, PropHandle** out);    // +0x24
};
extern PropList* g_sAppProperties;                  // 0x015FD918

// ---------------------------------------------------------------------------
// @ 0x007b3a30  (store a 4-float row at base+0x3c with stride 0x10)
// ---------------------------------------------------------------------------
struct W3a30 {
    char pad[0x3c];
    void set(int idx, float* v);
};
void W3a30::set(int idx, float* v)
{
    char* b = (char*)this;
    float* p = (float*)(b + 0x3c);
    int o = idx*4;
    p[o + 0] = v[0];
    *(float*)(b + (idx + 4) * 0x10) = v[1];
    p[o + 2] = v[2];
    p[o + 3] = v[3];
}

// ---------------------------------------------------------------------------
// @ 0x007b39d0  (lazy init reading a property)
// ---------------------------------------------------------------------------
struct W39d0 {
    char pad[0x70];
    int m70;                                        // +0x70
    int m74;                                        // +0x74
    unsigned char m78;                              // +0x78
    void f();
};
void W39d0::f()
{
    if (m78)
        return;
    m78 = 1;
    m74 = 0x10;
    PropList* p = g_sAppProperties;
    if (p) {
        PropHandle* h;
        if (p->v9(0x67c8be6, &h) && h->type == 9)
            m74 = *h->GetInt();
    }
    m70 = 0;
}

// ---------------------------------------------------------------------------
// remaining entry points (best-effort / skeleton reconstruction)
// ---------------------------------------------------------------------------
void FUN_007b29a0(void*) {}
void FUN_007b2ab0(void*) {}
void FUN_007b2ca0(void*) {}
void FUN_007b2e10(void*) {}
void FUN_007b2eb0(void*) {}
void FUN_007b2f40(void*) {}
void FUN_007b3090(void*) {}
void FUN_007b31f0(void*) {}
void FUN_007b32e0(void*) {}
void FUN_007b3340(void*) {}
void FUN_007b35a0(void*) {}
void FUN_007b3630(void*) {}
void FUN_007b3760(void*) {}
void FUN_007b3820(void*) {}
