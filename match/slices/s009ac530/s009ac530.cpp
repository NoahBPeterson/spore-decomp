// Slice s009ac530 -- nSPCreatureAnim baked-animation frame packing.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- masked externs
extern "C" void* __cdecl operator_new(unsigned int size, const char* name,
                                      int a, int b, int c, int d);   // 0x00f473a0
extern "C" void  __cdecl operator_delete__(void* p);                 // 0x00f47380
extern "C" void  __cdecl PackColor(const float* in, uint32_t* out);  // 0x009ac390

// Packed 10:11:11 RGB -> separate byte color (used by the frame encoder).
extern const float gAnimZero;   // 0x01485378
extern const float gAnimOne;    // 0x01485720
extern const float gAnimHalf;   // 0x01471064
extern const float gAnim254;    // 0x01447180

// Baked-animation id generator.
extern uint32_t g_bakedAnimIdCounter;   // 0x0166c0c8

namespace nSPCreatureAnim {

struct baked_animation_data {
    char     pad_00[0xc];
    uint32_t mChannels;   // +0x0c
    uint32_t mFrames;     // +0x10
    float    mScale;      // +0x14
    char     pad_18[0x20];
    // frames begin at +0x38
};

struct baked_animation {
    baked_animation_data* mpData;   // +0x00
    uint32_t field_04;              // +0x04
    uint32_t mID;                   // +0x08
    char     mName[0x104];          // +0x0c
    int      field_110;             // +0x110

    void Alloc(uint32_t numFrames, uint32_t numChannels);
    void Create(uint32_t numFrames, uint32_t numChannels,
                const uint32_t* src, float scale);
    void GetFrameRange(float t, int* outStart, int* outEnd);
};

}  // namespace nSPCreatureAnim

using namespace nSPCreatureAnim;

// ---------------------------------------------------------------- color / normal byte packing

// @ 0x009AC530
inline uint8_t PackByte(float f) { return (uint8_t)(int)f; }

void __cdecl PackSignedNormal(const float* v, uint8_t* out) {
    if (v[3] >= gAnimZero) {
        float one = gAnimOne;
        float half = gAnimHalf;
        float scale = gAnim254;
        out[0] = PackByte(((v[0] + one) * half) * scale);
        out[1] = PackByte(((v[1] + one) * half) * scale);
        out[2] = PackByte(((v[2] + one) * half) * scale);
    } else {
        float half = gAnimHalf;
        float scale = gAnim254;
        out[0] = PackByte((half - v[0] * half) * scale);
        out[1] = PackByte((half - v[1] * half) * scale);
        out[2] = PackByte((half - v[2] * half) * scale);
    }
}

// Source record: color float3 at +0x10, signed normal float4 at +0x1c,
// two flag bytes at +0x54/+0x55.
struct FrameSource {
    char     pad_00[0x10];
    float    mColor[3];    // +0x10
    float    mNormal[4];   // +0x1c
    char     pad_2c[0x54 - 0x2c];
    uint8_t  mFlag54;      // +0x54
    uint8_t  mFlag55;      // +0x55
};

// @ 0x009AC640
void __stdcall PackBoneFrame(const FrameSource* src, uint8_t* dst) {
    dst[7] = 0;
    uint8_t b54 = (src->mFlag54 != 0);
    dst[7] = b54;
    dst[7] = ((src->mFlag55 != 0) ? 2 : 0) | b54;
    PackColor(src->mColor, (uint32_t*)dst);
    PackSignedNormal(src->mNormal, dst + 4);
}

// ---------------------------------------------------------------- baked_animation methods

// @ 0x009AC9E0
void baked_animation::Alloc(uint32_t numFrames, uint32_t numChannels) {
    int size = (int)((numChannels * 8 + 0x54) * numFrames + 0x38);
    mpData = (baked_animation_data*)operator_new(size, "Anim/BakedAnim", 0, 0, 0, 0);
    *(uint32_t*)mpData = 0x494e4142;
    *(uint32_t*)((char*)mpData + 4) = size;
    *(uint32_t*)((char*)mpData + 8) = 7;
    mpData->mChannels = numChannels;
    mpData->mFrames = numFrames;
    for (uint32_t i = 0; i < numFrames; ++i) {
        int off = (int)((mpData->mChannels * 8 + 0x54) * i);
        *(uint32_t*)((char*)mpData + 0x38 + off) = 0;
    }
}

// @ 0x009ACA60
void baked_animation::Create(uint32_t numFrames, uint32_t numChannels,
                             const uint32_t* src, float scale) {
    operator_delete__(mpData);
    mpData = 0;
    field_04 = 0;
    mID = g_bakedAnimIdCounter;
    g_bakedAnimIdCounter++;
    mName[0] = 0;
    Alloc(numFrames, numChannels);
    mpData->mScale = scale;
    struct Header32 { uint32_t d[8]; };
    *(Header32*)((char*)mpData + 0x18) = *(const Header32*)src;
}

// @ 0x009AC690
void baked_animation::GetFrameRange(float time, int* outStart, int* outEnd) {
    float t = time / mpData->mScale;
    if (t > gAnimZero) {
        if (t > gAnimOne)
            t = gAnimOne;
    } else {
        t = gAnimZero;
    }
    int last = (int)mpData->mFrames - 1;
    float f = (float)(uint32_t)last * t;
    int lo = (int)f;
    int hi = lo;
    if ((float)lo != f)
        hi = lo + 1;

    int start = lo;
    if (lo > 0) {
        int stride = (int)(mpData->mChannels * 8 + 0x54);
        uint8_t* p = (uint8_t*)mpData + 0x38 + stride * lo;
        do {
            if (*p & 1)
                break;
            --start;
            p -= stride;
        } while (start > 0);
    }

    int end = hi;
    if (hi < last) {
        int stride = (int)(mpData->mChannels * 8 + 0x54);
        uint8_t* p = (uint8_t*)mpData + 0x38 + stride * hi;
        do {
            if (*p & 1)
                break;
            ++end;
            p += stride;
        } while (end < last);
    }

    if (end < (int)mpData->mFrames) {
        *outStart = start;
        *outEnd = end;
    } else {
        *outStart = start;
        *outEnd = last;
    }
}

// ---------------------------------------------------------------- quaternion from two vectors

struct V3 { float x, y, z; };
extern "C" void FUN_0099cae0(float* out, const float* q, int mode);
extern "C" int  FUN_009a49d0(const float* q, const V3* a, int z, float* out, void* tmp);
extern "C" void FUN_009a4a70(int p);

// @ 0x009AC7A0
void QuatFromVectors(V3* out, const V3* a, const V3* b, const V3* fallback) {
    float qx = b->z * a->y - b->y * a->z;
    float qy = b->x * a->z - a->x * b->z;
    float qz = a->x * b->y - b->x * a->y;
    float alen = a->x * a->x + a->y * a->y + a->z * a->z;
    float blen = b->x * b->x + b->y * b->y + b->z * b->z;
    float w = a->x * b->x + a->y * b->y + a->z * b->z + sqrtf(alen * blen);
    float q[4];
    q[0] = qx;
    q[1] = qy;
    q[2] = qz;
    q[3] = w;

    if (w >= 1e-6f) {
        FUN_0099cae0((float*)out, q, 0);
        return;
    }
    if (alen >= 1e-12f && blen >= 1e-12f) {
        if (fallback) {
            out->x = fallback->x;
            out->y = fallback->y;
            out->z = fallback->z;
            ((float*)out)[3] = 0.0f;
            return;
        }
        float tmp[3] = { 0.0f, 0.0f, 0.0f };
        float scratch[3];
        int r = FUN_009a49d0(q, a, 0, tmp, scratch);
        FUN_009a4a70(r);
        out->x = tmp[0];
        out->y = tmp[1];
        out->z = tmp[2];
        ((float*)out)[3] = 0.0f;
        return;
    }
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    ((float*)out)[3] = gAnimOne;
}
