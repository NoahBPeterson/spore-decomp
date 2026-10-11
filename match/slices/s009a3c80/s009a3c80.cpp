// Slice s009a3c80 - nSPCreatureAnim animation-cache helpers + vector math.
// (0x9a3c80..0x9a4a70, 17 functions).
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
//
// The region mixes integer code, EASTL red-black-tree wrappers and SSE/x87 vector math,
// so individual functions were compiled under different code-generation settings.  The
// integer helpers follow the UTFWin defaults (/O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast);
// the x87 vector helpers (LengthSqVec3/NormalizeVec3/PerpPair) were built for the plain
// IA32 float model (the same set without /arch:SSE).  See partial.txt for what is not
// reconstructed.

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Shared external helpers / tiny stub object types (calls are thiscall unless noted).
// ---------------------------------------------------------------------------
struct Obj99f0b0 { void FUN_0099f0b0(); };   // 0x99f0b0
struct Obj9c26a0 { void Release(); };        // 0x9c26a0 nSPCreatureAnim::creature_static_data::Release
struct Obj99d060 { void FUN_0099d060(); };   // 0x99d060
struct Obj99c980 { void FUN_0099c980(); };   // 0x99c980
struct Obj9b3450 { void FUN_009b3450(); };   // 0x9b3450

void operator_delete(void* p);               // 0xf47380

namespace nSPCreatureAnim {

// Intrusive red-black-tree container used by the anim cache.
struct AnimTree {
    // 0x9a3c80 - recursively frees a node chain (node[0]=key-link, node[4]=next).
    void FUN_009a3c80(void* node);
    // 0x9a3c40 - sibling free used for the other global list.
    void FUN_009a3c40(void* node);
    // (partial RB-tree entry points)
    void* FUN_009a3da0(void* out, void* hint, void* key);      // 0x9a3da0
    unsigned FUN_009a3f50(int key, unsigned limit);            // 0x9a3f50
    unsigned FUN_009a4020(int key, unsigned limit);            // 0x9a4020
    void FUN_009a4190(int param);                              // 0x9a4190
    void* FUN_009a4310(void* key);                             // 0x9a4310
    void* FUN_009a4390(void* key);                             // 0x9a4390

    // Inlined cache-node-list clear helpers (used by FUN_009a3ef0).
    void ClearA()
    {
        FUN_009a3c40(*(void**)((char*)this + 0x0c));
        int base = (int)this + 4;
        *(int*)base = base;
        *(int*)((char*)this + 8) = base;
        *(int*)((char*)this + 0x0c) = 0;
        *(char*)((char*)this + 0x10) = 0;
        *(int*)((char*)this + 0x14) = 0;
    }
    void ClearB()
    {
        FUN_009a3c80(*(void**)((char*)this + 0x0c));
        int base = (int)this + 4;
        *(int*)base = base;
        *(int*)((char*)this + 8) = base;
        *(int*)((char*)this + 0x0c) = 0;
        *(char*)((char*)this + 0x10) = 0;
        *(int*)((char*)this + 0x14) = 0;
    }
};

int FUN_009a4430(int nameOrHash, int hash, char* name);        // 0x9a4430
int FUN_009a4550(int a, int b);                                // 0x9a4550
void FUN_009a3ef0();                                           // 0x9a3ef0

} // namespace nSPCreatureAnim

// ---------------------------------------------------------------------------
// 0x009a3c80  AnimTree::FUN_009a3c80 (recursive node-chain delete)
// ---------------------------------------------------------------------------
// @ 0x009a3c80
void nSPCreatureAnim::AnimTree::FUN_009a3c80(void* node)
{
    while (node != 0) {
        this->FUN_009a3c80(*(void**)node);
        void* next = *(void**)((char*)node + 4);
        if (*(void**)((char*)node + 0x18) != 0)
            (*(Obj99f0b0**)((char*)node + 0x18))->FUN_0099f0b0();
        if (*(void**)((char*)node + 0x10) != 0)
            (*(Obj9c26a0**)((char*)node + 0x10))->Release();
        operator_delete(node);
        node = next;
    }
}

// ---------------------------------------------------------------------------
// 0x009a3ef0  cache shutdown (clears both global anim-cache trees)
// ---------------------------------------------------------------------------
// @ 0x009a3ef0
void nSPCreatureAnim::FUN_009a3ef0()
{
    if (*(nSPCreatureAnim::AnimTree**)0x166c058 != 0)
        (*(nSPCreatureAnim::AnimTree**)0x166c058)->ClearA();
    if (*(nSPCreatureAnim::AnimTree**)0x166c05c != 0)
        (*(nSPCreatureAnim::AnimTree**)0x166c05c)->ClearB();
}

// ---------------------------------------------------------------------------
// 0x009a4660  Morton-style bit interleave helper
// ---------------------------------------------------------------------------
// @ 0x009a4660
unsigned FUN_009a4660(unsigned param_1, unsigned param_2)
{
    unsigned result = 0;
    for (unsigned bit = 1; param_2 != 0 && param_1 != 0; bit <<= 1) {
        unsigned t = (param_1 - 1) & param_1;
        unsigned x = t ^ param_1;
        result |= (unsigned)((x & param_2) ? 0xffffffffu : 0u) & bit;
        param_2 &= ~x;
        param_1 = t;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x009a47e0  nSPCreatureAnim::CheckEventLocationType
// ---------------------------------------------------------------------------
namespace nSPCreatureAnim {

// @ 0x009a47e0
bool CheckEventLocationType(unsigned param_1, int param_2)
{
    if ((param_1 & 0xc00000) == 0x400000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d6) == 0))
            return false;
    } else if (((param_1 & 0xc00000) == 0x800000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d6) != 0)) {
        return false;
    }
    if ((param_1 & 0xc000000) == 0x4000000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d4) == 0))
            return false;
    } else if (((param_1 & 0xc000000) == 0x8000000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d4) != 0)) {
        return false;
    }
    if ((param_1 & 0x3000000) == 0x1000000) {
        if ((param_2 == 0) || (*(char*)(param_2 + 0x2d5) == 0))
            return false;
    } else if (((param_1 & 0x3000000) == 0x2000000) && (param_2 != 0) && (*(char*)(param_2 + 0x2d5) != 0)) {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x009a4890  nSPCreatureAnim::ContextFilterEventLocationData
// ---------------------------------------------------------------------------
// @ 0x009a4890
bool ContextFilterEventLocationData(unsigned param_1, int param_2, int* param_3, int param_4, int param_5)
{
    switch (param_1 & 0x70) {
    case 0x00:
        return true;
    case 0x10:
        return param_2 == 0;
    case 0x20:
        return param_2 != 0;
    case 0x30:
        return param_4 == -1 || param_3[param_2] == param_4;
    case 0x40:
        return param_4 == -1 || param_3[param_2] != param_4;
    case 0x50:
        return param_3[param_2] == param_5;
    case 0x60:
        return param_3[param_2] != param_5;
    default:
        return false;
    }
}

} // namespace nSPCreatureAnim

// ---------------------------------------------------------------------------
// 0x009a46a0  quaternion -> 3x3 matrix (row major, SSE)
// ---------------------------------------------------------------------------
// @ 0x009a46a0
void FUN_009a46a0(float* out, float* q)
{
    float f1 = q[1];
    float f2 = q[2];
    float f3 = q[0];
    float f4 = q[3];
    out[0] = 1.0f - (f2 * f2 + f1 * f1) * 2.0f;
    out[1] = (f1 * f3 - f4 * f2) * 2.0f;
    out[2] = (f4 * f1 + f2 * f3) * 2.0f;
    out[3] = (f4 * f2 + f1 * f3) * 2.0f;
    out[4] = 1.0f - (f2 * f2 + f3 * f3) * 2.0f;
    out[5] = (f2 * f1 - f4 * f3) * 2.0f;
    out[6] = (f2 * f3 - f4 * f1) * 2.0f;
    out[7] = (f4 * f3 + f2 * f1) * 2.0f;
    out[8] = 1.0f - (f1 * f1 + f3 * f3) * 2.0f;
}

// ---------------------------------------------------------------------------
// 0x009a49b0  LengthSqVec3
// ---------------------------------------------------------------------------
// @ 0x009a49b0
float LengthSqVec3(float* v)
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

// ---------------------------------------------------------------------------
// 0x009a49d0  NormalizeVec3
// ---------------------------------------------------------------------------
// @ 0x009a49d0
void NormalizeVec3(float* out, float* in, float* lengthOut)
{
    float x = in[0];
    float z = in[2];
    float y = in[1];
    float len = sqrtf(y * y + z * z + x * x);
    if (lengthOut != 0) {
        *lengthOut = len;
    }
    if (len != 0.0f) {
        float inv = 1.0f / len;
        x = inv * x;
        y = inv * y;
        z = inv * z;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

// ---------------------------------------------------------------------------
// 0x009a4a70  PerpPair
// ---------------------------------------------------------------------------
// @ 0x009a4a70
void PerpPair(float* n, float* out1, float* out2)
{
    float v[3] = { 1.0f, 1.0f, 1.0f };
    float best = 0.0f;
    float x = n[0];
    if (0.0f < fabsf(x))
        best = fabsf(x);
    float a1 = fabsf(n[1]);
    bool b = best < a1;
    if (b)
        best = a1;
    unsigned idx = (unsigned)b;
    if (best < fabsf(n[2]))
        idx = 2;
    float n2 = n[2];
    float n1 = n[1];
    v[idx] = 0.0f;

    float f4 = n2 * v[1] - n1 * v[2];
    float f5 = n1 * v[0] - x * v[1];
    float f3 = x * v[2] - n2 * v[0];
    float len = sqrtf(f4 * f4 + (f3 * f3 + f5 * f5));
    if (len != 0.0f) {
        len = 1.0f / len;
        f4 = len * f4;
        f3 = len * f3;
        f5 = len * f5;
    }
    out1[0] = f4;
    out1[1] = f3;
    out1[2] = f5;

    float g7 = n[1] * f5 - n[2] * f3;
    float g5 = n[2] * f4 - n[0] * f5;
    float g3 = n[0] * f3 - n[1] * f4;
    float len2 = sqrtf(g7 * g7 + (g3 * g3 + g5 * g5));
    if (len2 != 0.0f) {
        len2 = 1.0f / len2;
        g7 = len2 * g7;
        g5 = len2 * g5;
        g3 = len2 * g3;
    }
    out2[0] = g7;
    out2[1] = g5;
    out2[2] = g3;
}

// ---------------------------------------------------------------------------
// Partial EASTL red-black-tree / anim-cache entry points.
// Bodies not reconstructed (see partial.txt).
// ---------------------------------------------------------------------------
// @ 0x009a3da0
void* nSPCreatureAnim::AnimTree::FUN_009a3da0(void*, void*, void*)
{
    return 0;
}

// @ 0x009a3f50
unsigned nSPCreatureAnim::AnimTree::FUN_009a3f50(int, unsigned)
{
    return 0;
}

// @ 0x009a4020
unsigned nSPCreatureAnim::AnimTree::FUN_009a4020(int, unsigned)
{
    return 0;
}

// @ 0x009a4190
void nSPCreatureAnim::AnimTree::FUN_009a4190(int)
{
}

// @ 0x009a4310
void* nSPCreatureAnim::AnimTree::FUN_009a4310(void*)
{
    return 0;
}

// @ 0x009a4390
void* nSPCreatureAnim::AnimTree::FUN_009a4390(void*)
{
    return 0;
}

// @ 0x009a4430
int nSPCreatureAnim::FUN_009a4430(int, int, char*)
{
    return 0;
}

// @ 0x009a4550
int nSPCreatureAnim::FUN_009a4550(int, int)
{
    return 0;
}
