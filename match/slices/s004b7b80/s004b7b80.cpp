// Slice s004b7b80: mix of editor/rng helpers near the cSPEditorPhysicsWorld region.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE (frame-pointer) for most; a few x87 float helpers.
#include "types.h"

extern void* g_vtbl;

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------------------
// comparator helpers (member functions of a MI class; base at -8)
// ---------------------------------------------------------------------------
struct BaseCmp {
    unsigned char* SetEq(unsigned char* out, int a, int b);   // 0x4b8950
};
struct DerivedCmp {
    char pad[8];
    unsigned char* SetEqFromNodes(unsigned char* out, int a, int b);  // 0x4b8980
    unsigned char* SetEqFromRoots(unsigned char* out, int u, int a, int b);  // 0x4b89c0
};

// @ 0x4b8950
unsigned char* BaseCmp::SetEq(unsigned char* out, int a, int b)
{
    if (a == b) { *out = 1; return out; }
    *out = 0;
    return out;
}

// @ 0x4b8980
unsigned char* DerivedCmp::SetEqFromNodes(unsigned char* out, int a, int b)
{
    int b18 = *(int*)(b + 0x1c);
    int a10 = *(int*)(a + 0x1c);
    ((BaseCmp*)((char*)this - 8))->SetEq(out, a10, b18);
    return out;
}

// @ 0x4b89c0
unsigned char* DerivedCmp::SetEqFromRoots(unsigned char* out, int unused, int a, int b)
{
    int r = b;
    while (*(int*)(r + 0xc) != 0)
        r = *(int*)(r + 0xc);
    int l = a;
    while (*(int*)(l + 0xc) != 0)
        l = *(int*)(l + 0xc);
    ((BaseCmp*)((char*)this - 8))->SetEq(out, *(int*)(l + 0x1c), *(int*)(r + 0x1c));
    return out;
}

// ---------------------------------------------------------------------------
// misc helpers
// ---------------------------------------------------------------------------
struct PropObj {
    virtual void v0(); virtual void Release();
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_00425990(void* vec);
    void  FUN_0042dee0();
    void  FUN_004b64b0();
    void  FUN_004b66b0();
    void  FUN_004b62a0();
    void  FUN_004b6340();
    void  FUN_004b69d0();
    void  FUN_004b6450();
    void  FUN_004b6bf0();
    char  SP_GetResourceTypeFromModelType();
    void  FUN_004b8950(void* a, void* b, void* c);
    void  FUN_004b5fb0(void* a, void* b);
    void  FUN_004b54b0(void* a);
    void  FUN_004b5610(void* a);
    void  FUN_004b5a60(void* a);
    void  FUN_004b97e0(void* a, void* b);
    int   EA_RandomDoubleUniform(void* rng);
    void  FUN_00540470(void* a);
    void  FUN_00540520(void);
    void  FUN_005c7bc0(void* a);
    void* FUN_005c7e80(int a, int b, int c, int d);
    void* FUN_005c7e20(int a, int b, int c, int d);
    void* FUN_005c7b80(void);
    void  FUN_004e8a30(void* a);
    void* operator_new_ea(uint32_t n, const char* tag, int a, int b, int c, int d);
}

// @ 0x4b7b80
int FUN_004b7b80(void* self, int a, int b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x4b8180
int FUN_004b8180(void* self, void* a, void* b, void* c, void* d, void* e)
{
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x4b8750
void FUN_004b8750(int a, int* b, int c, int d)
{
    if (c != 0) {
        if (d == -1) {
            if (b != 0 && a != 0) {
                (*(void(__thiscall**)(int*, int, int))(*b + 0x54))(b, a, c);
                if (SP_GetResourceTypeFromModelType()) {
                    uint32_t v = 0xffffffff;
                    extern void vec_push_u32(uint32_t*);
                    vec_push_u32(&v);
                }
            }
        } else {
            extern void vec_push_u32(uint32_t*);
            vec_push_u32((uint32_t*)&d);
        }
    }
}

// @ 0x4b87c0
void* __fastcall FUN_004b87c0(void** o)
{
    o[0] = &g_vtbl;
    *(uint16_t*)(o + 1) = 0x212;
    *(uint16_t*)((char*)o + 6) = 0x20;
    o[2] = 0;
    for (int i = 2; i >= 0; i--) {
    }
    o[0] = &g_vtbl;
    void* p = (o == 0) ? 0 : (void*)(o + 3);
    o[2] = p;
    return o;
}

// @ 0x4b8860
void* __fastcall FUN_004b8860(void** o)
{
    o[0] = &g_vtbl;
    *(uint16_t*)(o + 1) = 0x213;
    *(uint16_t*)((char*)o + 6) = 0x30;
    o[2] = 0;
    for (int i = 2; i >= 0; i--) {
    }
    o[0] = &g_vtbl;
    void* p = (o == 0) ? 0 : (void*)(o + 3);
    o[2] = p;
    return o;
}

extern void* g_vtbl;

// @ 0x4b8900
float FUN_004b8900(void* rng, double lo, double hi)
{
    float v = (float)((float)EA_RandomDoubleUniform(rng) * (hi - lo) + lo);
    if (v < hi) {
        if (v >= lo)
            return v;
        return (float)lo;
    }
    return (float)hi;
}

// @ 0x4b8a70
int FUN_004b8a70(int self, int out, int a, int* b, int e)
{
    (void)self;
    int u = (*(int(__thiscall**)(int*, int, int))(*b + 0x2c))(b, e, self);
    FUN_004b8950((void*)out, (void*)*(int*)(a + 0x20), (void*)u);
    return out;
}
