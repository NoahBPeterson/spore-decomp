// Slice s00778060: rw::graphics shader-constant setters and the shader-data state stack.
// Region 0x778060-0x778fd0. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---- D3D9 device (IDirect3DDevice9) ------------------------------------------------------
extern void* g_pDevice;  // 0x16f89d0  rw::graphics::ActiveState::m_d3d9Device

struct D3D9Vtbl { void* slots[112]; };
typedef void (__stdcall *PFN_SetConstF)(void* self, unsigned reg, const float* data, unsigned count);
#define SETVS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[94]))((dev), (reg), (data), (n)))
#define SETPS(dev, reg, data, n) (((PFN_SetConstF)(((D3D9Vtbl*)(*(void**)(dev)))->slots[109]))((dev), (reg), (data), (n)))

// ---- shader-constant source globals ------------------------------------------------------
extern float* g_shConstA;   // 0x16f6db0  used fields +4..+0x10
struct ShConstB { float v; int i; };
extern ShConstB* g_shConstB;// 0x16f6db4
extern float* g_shConstC;   // 0x16f6db8  four raw dwords
extern float* g_shConstD;   // 0x16f6dd8  pointer to 4 floats (used directly)
extern int*   g_shConstE;   // 0x16f6de4  { int v; unsigned char flag; }
struct ShConst12 { int d[8]; float f[4]; };
extern ShConst12* g_shConstF;// 0x16f6df4
extern float  g_defConst[4];// 0x1539ff8
extern float  g_one;        // 0x1485720  = 1.0f

// ---- shader-data state stack -------------------------------------------------------------
struct ShStackEnt { unsigned short idx; unsigned short pad; int val; };
extern ShStackEnt g_shStack[];          // 0x16312f0
extern int        g_shTop;              // 0x1632bf0
extern void*      g_shActive[];         // 0x16f65a8
extern unsigned int g_shDirty[];        // 0x16f89f8
extern unsigned int g_softStateUpdated; // 0x16f9110

#pragma warning(disable:4035)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x00778060  Matrix4 invert; flags bit2 = copy through, (flags&3)==3 = affine special case
void FUN_00778060(float* out, const float* m, unsigned flags) {
    if (flags & 4) {
        for (int i = 0; i < 16; ++i)
            out[i] = m[i];
        return;
    }
    if ((flags & 3) == 3) {
        float a0 = m[0], a1 = m[1], a2 = m[2], a3 = m[3];
        float b0 = m[4], b1 = m[5], b2 = m[6];
        float c0 = m[8], c1 = m[9], c2 = m[10];
        float t0 = m[12], t1 = m[13], t2 = m[14];
        out[0] = a0;  out[1] = b0;  out[2]  = c0;  out[3]  = 0.0f;
        out[4] = a1;  out[5] = b1;  out[6]  = c1;  out[7]  = 0.0f;
        out[8] = a2;  out[9] = b2;  out[10] = c2;  out[11] = 0.0f;
        out[12] = -(a0 * t0 + a1 * t1 + a2 * t2);
        out[13] = -(b0 * t0 + b1 * t1 + b2 * t2);
        out[14] = -(c0 * t0 + c1 * t1 + c2 * t2);
        out[15] = 1.0f;
        return;
    }
    float i0  =  m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15] + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    float i4  = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15] - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    float i8  =  m[4]*m[9]*m[15]  - m[4]*m[11]*m[13] - m[8]*m[5]*m[15] + m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    float i12 = -m[4]*m[9]*m[14]  + m[4]*m[10]*m[13] + m[8]*m[5]*m[14] - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    float det = m[0]*i0 + m[1]*i4 + m[2]*i8 + m[3]*i12;
    float id = 1.0f / det;
    out[0]  = i0 * id;
    out[1]  = (-m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15] - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10]) * id;
    out[2]  = ( m[1]*m[6]*m[15]  - m[1]*m[7]*m[14]  - m[5]*m[2]*m[15] + m[5]*m[3]*m[14] + m[13]*m[2]*m[7]  - m[13]*m[3]*m[6])  * id;
    out[3]  = (-m[1]*m[6]*m[11]  + m[1]*m[7]*m[10]  + m[5]*m[2]*m[11] - m[5]*m[3]*m[10] - m[9]*m[2]*m[7]   + m[9]*m[3]*m[6])   * id;
    out[4]  = i4 * id;
    out[5]  = ( m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15] + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10]) * id;
    out[6]  = (-m[0]*m[6]*m[15]  + m[0]*m[7]*m[14]  + m[4]*m[2]*m[15] - m[4]*m[3]*m[14] - m[12]*m[2]*m[7]  + m[12]*m[3]*m[6])  * id;
    out[7]  = ( m[0]*m[6]*m[11]  - m[0]*m[7]*m[10]  - m[4]*m[2]*m[11] + m[4]*m[3]*m[10] + m[8]*m[2]*m[7]   - m[8]*m[3]*m[6])   * id;
    out[8]  = i8 * id;
    out[9]  = (-m[0]*m[9]*m[15]  + m[0]*m[11]*m[13] + m[8]*m[1]*m[15] - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9])  * id;
    out[10] = ( m[0]*m[5]*m[15]  - m[0]*m[7]*m[13]  - m[4]*m[1]*m[15] + m[4]*m[3]*m[13] + m[12]*m[1]*m[7]  - m[12]*m[3]*m[5])  * id;
    out[11] = (-m[0]*m[5]*m[11]  + m[0]*m[7]*m[10]  + m[4]*m[1]*m[11] - m[4]*m[3]*m[10] - m[8]*m[1]*m[7]   + m[8]*m[3]*m[5])   * id;
    out[12] = i12 * id;
    out[13] = ( m[0]*m[9]*m[14]  - m[0]*m[10]*m[13] - m[8]*m[1]*m[14] + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9])  * id;
    out[14] = (-m[0]*m[5]*m[14]  + m[0]*m[6]*m[13]  + m[4]*m[1]*m[14] - m[4]*m[2]*m[13] - m[12]*m[1]*m[6]  + m[12]*m[2]*m[5])  * id;
    out[15] = ( m[0]*m[5]*m[10]  - m[0]*m[6]*m[9]   - m[4]*m[1]*m[10] + m[4]*m[2]*m[9]  + m[8]*m[1]*m[6]   - m[8]*m[2]*m[5])   * id;
}

// @ 0x007789d0  rw::graphics::ShaderDataState list -> active-state commit (pushes old values)
struct ShaderDataVec {
    char pad00[8];
    int* begin;   // +0x08
    int* end;     // +0x0c
    void Push();
};

void ShaderDataVec::Push() {
    if (begin == end)
        return;
    int i = 0;
    if (g_shTop > 0) {
        int n = (int)((end - begin) >> 2);
        if (n > 0) {
            do {
                int elem = begin[i];
                unsigned short idx = *(unsigned short*)(elem + 4);
                int val = *(int*)(elem + 8);
                g_shStack[g_shTop].idx = idx;
                g_shStack[g_shTop].val = (int)g_shActive[idx];
                g_shActive[idx] = (void*)val;
                ++g_shTop;
                g_shDirty[idx >> 5] |= 1u << (idx & 0x1f);
                ++i;
            } while (i < n);
        }
    } else {
        int n = (int)((end - begin) >> 2);
        if (n > 0) {
            do {
                int elem = begin[i];
                unsigned short idx = *(unsigned short*)(elem + 4);
                g_shActive[idx] = *(void**)(elem + 8);
                g_shDirty[idx >> 5] |= 1u << (idx & 0x1f);
                ++i;
            } while (i < n);
        }
    }
    g_softStateUpdated |= 8;
}

// @ 0x00778c50  set one float4 constant from g_shConstA
void FUN_00778c50(unsigned reg, unsigned p2, int isVS) {
    float* p = g_shConstA;
    if (p) {
        float v[4];
        v[0] = p[1];
        v[1] = p[2];
        v[2] = p[3];
        v[3] = p[4];
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00778cc0  set one float4 constant from g_shConstB (fractional part)
void FUN_00778cc0(unsigned reg, unsigned p2, int isVS) {
    ShConstB* p = g_shConstB;
    if (p) {
        float f = p->v;
        int i = FloorToInt(f);
        float a = (float)(unsigned)p->i;
        float b = p->v;
        float v[4];
        v[0] = b;
        v[1] = a;
        v[2] = 0.0f;
        v[3] = b - (float)i;
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00778d70  set one float4 constant from g_shConstC
void FUN_00778d70(unsigned reg, unsigned p2, int isVS) {
    float* p = g_shConstC;
    if (p) {
        float v[4];
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        v[3] = p[3];
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00778de0  set one float4 constant from g_shConstD or the default constant
void FUN_00778de0(unsigned reg, unsigned p2, int isVS) {
    if (g_shConstD) {
        if (isVS)
            SETVS(g_pDevice, reg, g_shConstD, 1);
        else
            SETPS(g_pDevice, reg, g_shConstD, 1);
    } else {
        float v[4];
        v[0] = g_defConst[0];
        v[1] = g_defConst[1];
        v[2] = g_defConst[2];
        v[3] = g_defConst[3];
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}

// @ 0x00778ea0  set three float4 constants from g_shConstF
void FUN_00778ea0(unsigned reg, unsigned p2, int isVS) {
    ShConst12* p = g_shConstF;
    if (p) {
        ShConst12 v;
        v.d[0] = p->d[0];
        v.d[1] = p->d[1];
        v.d[2] = p->d[2];
        v.d[3] = p->d[3];
        v.d[4] = p->d[4];
        v.d[5] = p->d[5];
        v.d[6] = p->d[6];
        v.d[7] = p->d[7];
        v.f[0] = p->f[0];
        v.f[1] = p->f[1];
        v.f[2] = p->f[2];
        v.f[3] = p->f[3];
        if (isVS)
            SETVS(g_pDevice, reg, (const float*)&v, 3);
        else
            SETPS(g_pDevice, reg, (const float*)&v, 3);
    }
}

// @ 0x00778ab0  upload skinning-bone matrix rows as vertex/pixel shader constants
struct ConstG { int n; float* p; };
extern ConstG* g_shConstG;  // 0x16f6da8

void FUN_00778ab0(unsigned startReg, int count, int isVS) {
    float buf[64] = {0};
    ConstG* g = g_shConstG;
    int n = g->n;
    float* src = g->p;
    while (count != 0) {
        int chunk = count < 0x11 ? count : 0x10;
        int copyN = n < chunk ? n : chunk;
        for (int i = 0; i < copyN; ++i)
            buf[i] = src[i];
        for (int i = copyN; i < chunk; ++i)
            buf[i] = 0.0f;
        if (isVS)
            SETVS(g_pDevice, startReg, buf, chunk);
        else
            SETPS(g_pDevice, startReg, buf, chunk);
        startReg += chunk;
        count -= chunk;
        n -= chunk;
        src += chunk;
    }
}

// @ 0x00778f50  set one float4 constant from g_shConstE
void FUN_00778f50(unsigned reg, unsigned p2, int isVS) {
    int* p = g_shConstE;
    if (p) {
        float v[4];
        v[1] = *(unsigned char*)((char*)p + 4) ? g_one : 0.0f;
        v[0] = (float)p[0];
        v[2] = 0.0f;
        v[3] = 0.0f;
        if (isVS)
            SETVS(g_pDevice, reg, v, 1);
        else
            SETPS(g_pDevice, reg, v, 1);
    }
}
