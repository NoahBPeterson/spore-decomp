// Slice s0110fa20: hkGsk manifold vertex-welding helpers plus the feature-query routine.
// Flags: /O2 /MD /Gy /GS- /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------
// externals (callee addresses as 0x...).
struct GskTransform {
    float m[16];  // +0: row-major 3x? matrix, +0x30..+0x38 translation
};

struct GskManifold {
    unsigned char mCount0;   // +0  number of groups of the first kind
    unsigned char mCount1;   // +1
    unsigned char mCount2;   // +2  number of records
    unsigned char pad3;
    // records of 8 bytes start at +4
};

struct GskFeatureQuery {
    signed char idx0;   // +0
    signed char idx1;   // +1
    signed char idx2;   // +2
    signed char idx3;   // +3
    int pad4;
    int pad8;
    int padC;
    int valid;          // +0x10 -> [esp+0x30]? used as the 0x110cd00 guard
};

extern "C" void FUN_0110e510();  // 0x110e510  hkGsk::getClosestFeature
extern "C" void FUN_0110cd00();  // 0x110cd00  hkTriangleUtil::sortFeatureIndices

static inline void* VSlot(void* obj, int byte_offset)
{
    return (*(void***)obj)[byte_offset / 4];
}

// @ 0x0110fc50
void __fastcall hkGskManifold_removeUnusedVertices(unsigned char* p)
{
    unsigned char used[16];
    for (int i = 0; i < 16; i++)
        used[i] = 0;

    unsigned char* base_p = p;
    if ((int)base_p[2] > 0) {
        unsigned int n = base_p[2];
        unsigned char* rec = base_p + 8;
        do {
            unsigned int b = rec[-3];
            unsigned int a = rec[-4];
            unsigned int sum = a + b;
            used[rec[0] >> 4] = 1;
            used[rec[1] >> 4] = 1;
            if (sum > 2)
                used[rec[2] >> 4] = 1;
            if (sum == 4)
                used[rec[3] >> 4] = 1;
            rec += 8;
        } while (--n != 0);
    }

    unsigned int rec_count = base_p[2];
    unsigned int total = (unsigned int)base_p[0] + (unsigned int)base_p[1];
    unsigned short* verts = (unsigned short*)(base_p + rec_count * 8 + 4);
    unsigned int remap[16];
    int i = 0;
    unsigned int w = 0;
    unsigned int off = 0;
    if ((int)total > 0) {
        do {
            remap[i] = off;
            if (used[i] != 0) {
                verts[w] = verts[i];
                w++;
                off += 0x10;
            }
            i++;
        } while (i < (int)total);
    }

    unsigned char base = (unsigned char)(remap[base_p[0]] >> 4);
    base_p[0] = base;
    base_p[1] = (unsigned char)(w - base);

    if (base_p[2] != 0) {
        unsigned int count2 = base_p[2];
        unsigned char* idx = base_p + 9;
        unsigned int n = count2;
        do {
            idx[-1] = (unsigned char)remap[idx[-1] >> 4];
            idx[0] = (unsigned char)remap[idx[0] >> 4];
            idx[1] = (unsigned char)remap[idx[1] >> 4];
            idx[2] = (unsigned char)remap[idx[2] >> 4];
            idx += 8;
        } while (--n != 0);
    }
}

// @ 0x0110fd70
void FUN_0110fd70(unsigned char* p, int index)
{
    unsigned int n = (unsigned char)(p[2] - 1);
    p[2] = (unsigned char)n;
    unsigned char* src = p + n * 8;
    unsigned char* dst = p + (unsigned int)index * 8;
    *(uint32_t*)(dst + 4) = *(uint32_t*)(src + 4);
    *(uint32_t*)(dst + 8) = *(uint32_t*)(src + 8);

    src = p + (unsigned int)p[2] * 8 + 0xc;
    dst = p + (unsigned int)p[2] * 8 + 4;
    int nslots = ((int)p[1] - 1 + (int)p[0]) >> 1;
    if (nslots >= 0) {
        int n2 = nslots + 1;
        do {
            *(uint32_t*)dst = *(uint32_t*)src;
            dst += 4;
            src += 4;
        } while (--n2 != 0);
    }

    hkGskManifold_removeUnusedVertices(p);
}

// @ 0x0110fdd0
void FUN_0110fdd0(unsigned char* p, void* obj)
{
    for (int i = 0; i < p[2]; i++) {
        unsigned short v = *(unsigned short*)(p + 6 + i * 8);
        if (v != 0xffff) {
            (*(void (__thiscall**)(void*, int))(*(void***)obj + 4))(obj, (int)v);
        }
    }
    p[2] = 0;
    p[0] = 0;
    p[1] = 0;
}

// @ 0x0110fa20
int FUN_0110fa20(int* q, unsigned char* shape, float* outA, float* outB)
{
    float* matrix = (float*)q[1];
    void* objA = (void*)q[2];
    void* objB = (void*)q[3];
    float threshold = ((float*)q)[4];

    signed char c8 = (signed char)shape[8];
    signed char c9 = (signed char)shape[9];
    signed char c10 = (signed char)shape[10];
    signed char c11 = (signed char)shape[11];

    float matA[16];
    float matB[16];
    ((void (__thiscall*)(void*, void*, int, void*))VSlot(objA, 0x28))(objA, shape, (int)c8, matA);
    ((void (__thiscall*)(void*, void*, int, void*))VSlot(objB, 0x28))(objB, shape + (unsigned int)c8 * 2, (int)c9, matB);

    GskFeatureQuery query;
    query.idx0 = c8;
    query.idx1 = c9;
    query.idx2 = c10;
    query.idx3 = c11;
    query.pad4 = 0;
    query.pad8 = 0;
    query.padC = 0;
    query.valid = 0;

    float closest[4];
    closest[0] = 0.0f;
    closest[1] = 0.0f;
    closest[2] = 0.0f;
    closest[3] = 0.0f;
    ((void (__thiscall*)(void*, void*, void*, void*, void*))&FUN_0110e510)
        (&query, objA, objB, (void*)q[0], closest);

    if (query.pad8 != 0)
        ((void (__thiscall*)(void*, void*))&FUN_0110cd00)(&query, shape);

    float dist = closest[3] - *(float*)((char*)objA + 0xc) - *(float*)((char*)objB + 0xc);

    outA[0] = closest[0] * matrix[0] + closest[1] * matrix[4] + closest[2] * matrix[8];
    outA[1] = closest[0] * matrix[1] + closest[1] * matrix[5] + closest[2] * matrix[9];
    outA[2] = closest[0] * matrix[2] + closest[1] * matrix[6] + closest[2] * matrix[10];
    outA[3] = 0.0f;
    outA[3] = dist;

    if (dist < threshold) {
        float v0, v1, v2;
        if (c8 == 1) {
            float delta = *(float*)((char*)objB + 0xc) - closest[3];
            v0 = closest[0] * delta + matA[0];
            v1 = closest[1] * delta + matA[4];
            v2 = closest[2] * delta + matA[8];
        } else if (c9 == 1) {
            float delta = *(float*)((char*)objB + 0xc);
            v0 = closest[0] * delta + matB[0];
            v1 = closest[1] * delta + matB[4];
            v2 = closest[2] * delta + matB[8];
        } else {
            float delta = *(float*)((char*)objB + 0xc) - closest[3];
            v0 = closest[0] * delta + 0.0f;
            v1 = closest[1] * delta + 0.0f;
            v2 = closest[2] * delta + 0.0f;
        }
        outB[0] = v0 * matrix[0] + v1 * matrix[4] + v2 * matrix[8] + matrix[0xc];
        outB[1] = v0 * matrix[1] + v1 * matrix[5] + v2 * matrix[9] + matrix[0xd];
        outB[2] = v0 * matrix[2] + v1 * matrix[6] + v2 * matrix[10] + matrix[0xe];
        outB[3] = 0.0f;
        return 0;
    }

    return 1;
}
