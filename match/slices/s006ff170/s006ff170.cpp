// Slice s006ff170: vertex-shader fragment-record serialization and plane/clip test helpers.
// Region 0x6ff170-0x6ffdf8. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"

// ---- external callees -------------------------------------------------------------------
void __cdecl FUN_0047d240(void* p, int a);
void __cdecl FUN_006fc540(void* p, int a);
void __cdecl FUN_00777720(void* p, unsigned a, int b);
unsigned __cdecl FUN_00777740(void* p);
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

// ---- globals ----------------------------------------------------------------------------
extern unsigned char g_1628c38;    // 0x1628c38 clip-disable flag
extern int  g_planeIndices[6];     // 0x1534e4c

// @ 0x006ff170  -- vertex-fragment record serializer (EH; stub, see partial.txt)
void __cdecl FUN_006ff170(void* stream) { (void)stream; }

// @ 0x006ff3f0  -- vertex-fragment record deserializer (EH; stub, see partial.txt)
void __cdecl FUN_006ff3f0(void* stream) { (void)stream; }

// @ 0x006ff680  -- SP::ClearVSFragment (EH; see nonmatching.txt)
void __cdecl FUN_006ff680(int idx) {
    (void)idx;
}

// @ 0x006ff750  -- vertex-fragment setup (stub, see partial.txt)
void __cdecl FUN_006ff750(void* a, void* b) { (void)a; (void)b; }

// @ 0x006ffa80
struct VertexCtx {
    void SubClip(float d);
    int  TestClip1(const float* a, const float* b);
    int  TestClip2(const float* p, float t);
};

void VertexCtx::SubClip(float d) {
    *(float*)((char*)this + 0x0c) -= d;
    *(float*)((char*)this + 0x34) -= d;
    *(float*)((char*)this + 0x5c) -= d;
    *(float*)((char*)this + 0x84) -= d;
    *(float*)((char*)this + 0xac) -= d;
    *(float*)((char*)this + 0xd4) -= d;
}

// @ 0x006ffaf0
int VertexCtx::TestClip1(const float* a, const float* b) {
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float local[6];
    local[0] = a[0];
    local[1] = a[1];
    local[2] = a[2];
    local[3] = b[0];
    local[4] = b[1];
    local[5] = b[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        int i0 = *(int*)((char*)pf + 0x10);
        int i1 = *(int*)((char*)pf + 0x18);
        int i2 = *(int*)((char*)pf + 0x20);
        float dot = ((pf[2] * local[i2] + pf[1] * local[i1]) + pf[0] * local[i0]) + pf[3];
        if ((*(unsigned int*)&dot & 0x80000000) == 0) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffbd0
int VertexCtx::TestClip2(const float* p, float t) {
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float x = p[0];
    float y = p[1];
    float z = p[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        float dot = ((pf[2] * z + pf[1] * y) + pf[0] * x) + pf[3];
        if (dot >= t) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffc60
void __cdecl FUN_006ffc60(float* p) {
    unsigned int mask = 0;
    if (0.0f <= p[0]) mask |= 1;
    if (0.0f <= p[1]) mask |= 2;
    if (0.0f <= p[2]) mask |= 4;
    switch (mask) {
    case 0: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 1: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 2: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 3: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 4: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 5: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 6: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    case 7: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    }
}

// @ 0x006ffdc0
void __cdecl FUN_006ffdc0(float* dst, const float* src) {
    float* d = dst;
    const float* s = src;
    int n = 4;
    do {
        d[0] = s[0];
        d[1] = s[4];
        d[2] = s[8];
        d[3] = s[12];
        ++s;
        d += 4;
    } while (--n);
}
