// Slice s00a89de0 -- EA::Swarm copy_range / copy_backward_range / cTransform::PostTransformBy.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// cdtors (cdecl)
extern "C" void* FUN_0041cb40(void* dst, const void* src);   // Matrix3::Assign
extern "C" void* FUN_00537dc0(void* dst, const void* src);   // cSPTransformOps::Assign

// ---------------------------------------------------------------------------
// cDistributeSample (retail, 0x4c bytes) : cTransform mTransform (+0), Vector4 mColorAlpha (+0x38),
// int mNumber (+0x48). cTransform is 0x38: flags/modcount word pair, translation, scale, Matrix3.
struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };

struct cTransform {                    // 0x38 bytes
    uint16_t mFlags;                   // +0x00
    uint16_t mModificationCount;       // +0x02
    Vector3  mTranslation;             // +0x04
    float    mScale;                   // +0x10
    Matrix3  mRotation;                // +0x14
};

struct cDistributeSample {             // 0x4c bytes
    cTransform mTransform;             // +0x00
    float      mColorAlpha[4];         // +0x38
    int        mNumber;                // +0x48

    cDistributeSample(const cDistributeSample& src);            // 0x00a89de0
    void Assign(const cDistributeSample* src);                  // 0x00a8a0a0-family element assign
};

// @ 0x00a89de0
cDistributeSample::cDistributeSample(const cDistributeSample& src)
{
    mTransform.mFlags = src.mTransform.mFlags;
    mTransform.mModificationCount = src.mTransform.mModificationCount;
    mTransform.mTranslation.x = src.mTransform.mTranslation.x;
    mTransform.mTranslation.y = src.mTransform.mTranslation.y;
    mTransform.mTranslation.z = src.mTransform.mTranslation.z;
    mTransform.mScale = src.mTransform.mScale;
    ((void*(__thiscall*)(void*, const void*))&FUN_0041cb40)(&mTransform.mRotation, &src.mTransform.mRotation);
    mColorAlpha[0] = src.mColorAlpha[0];
    mColorAlpha[1] = src.mColorAlpha[1];
    mColorAlpha[2] = src.mColorAlpha[2];
    mColorAlpha[3] = src.mColorAlpha[3];
    mNumber = src.mNumber;
}

// ===========================================================================
// @ 0x00a89e40
cDistributeSample** FUN_00a89e40(cDistributeSample** out, const cDistributeSample* first,
                  const cDistributeSample* last, cDistributeSample* dst)
{
    cDistributeSample** result = out;
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->mTransform.mFlags = first->mTransform.mFlags;
                dst->mTransform.mModificationCount = first->mTransform.mModificationCount;
                dst->mTransform.mTranslation.x = first->mTransform.mTranslation.x;
                dst->mTransform.mTranslation.y = first->mTransform.mTranslation.y;
                dst->mTransform.mTranslation.z = first->mTransform.mTranslation.z;
                dst->mTransform.mScale = first->mTransform.mScale;
                dst->mTransform.mRotation = first->mTransform.mRotation;
                dst->mColorAlpha[0] = first->mColorAlpha[0];
                dst->mColorAlpha[1] = first->mColorAlpha[1];
                dst->mColorAlpha[2] = first->mColorAlpha[2];
                dst->mColorAlpha[3] = first->mColorAlpha[3];
                dst->mNumber = first->mNumber;
            }
            first = (const cDistributeSample*)((const char*)first + 0x4c);
            dst = (cDistributeSample*)((char*)dst + 0x4c);
        } while (first != last);
        *out = dst;
    }
    return result;
}

// ===========================================================================
// @ 0x00a89f70
cDistributeSample* FUN_00a89f70(cDistributeSample* first, cDistributeSample* last, cDistributeSample* dst)
{
    cDistributeSample* result = dst;
    if (first != last) {
        uint32_t* d = (uint32_t*)((char*)dst + 0xc);
        uint32_t* s = (uint32_t*)((char*)first + 0x28);
        do {
            if (dst != 0) {
                *(uint16_t*)dst = *(uint16_t*)first;
                *(uint16_t*)((char*)d - 0xa) = *(uint16_t*)((char*)s - 0x26);
                *(uint32_t*)((char*)d - 8) = *(uint32_t*)((char*)s - 0x24);
                *(uint32_t*)((char*)d - 4) = *(uint32_t*)((char*)s - 0x20);
                *(uint32_t*)((char*)d) = *(uint32_t*)((char*)s - 0x1c);
                *(uint32_t*)((char*)d + 4) = *(uint32_t*)((char*)s - 0x18);
                *(uint32_t*)((char*)d + 8) = *(uint32_t*)((char*)s - 0x14);
                *(uint32_t*)((char*)d + 0xc) = *(uint32_t*)((char*)s - 0x10);
                *(uint32_t*)((char*)d + 0x10) = *(uint32_t*)((char*)s - 0xc);
                *(uint32_t*)((char*)d + 0x14) = *(uint32_t*)((char*)s - 8);
                *(uint32_t*)((char*)d + 0x18) = *(uint32_t*)((char*)s - 4);
                *(uint32_t*)((char*)d + 0x1c) = *(uint32_t*)((char*)s);
                *(uint32_t*)((char*)d + 0x20) = *(uint32_t*)((char*)s + 4);
                *(uint32_t*)((char*)d + 0x24) = *(uint32_t*)((char*)s + 8);
                *(uint32_t*)((char*)d + 0x28) = *(uint32_t*)((char*)s + 0xc);
                *(uint32_t*)((char*)d + 0x2c) = *(uint32_t*)((char*)s + 0x10);
                *(uint32_t*)((char*)d + 0x30) = *(uint32_t*)((char*)s + 0x14);
                *(uint32_t*)((char*)d + 0x34) = *(uint32_t*)((char*)s + 0x18);
                *(uint32_t*)((char*)d + 0x38) = *(uint32_t*)((char*)s + 0x1c);
                *(uint32_t*)((char*)d + 0x3c) = *(uint32_t*)((char*)s + 0x20);
            }
            first = (cDistributeSample*)((char*)first + 0x4c);
            s = (uint32_t*)((char*)s + 0x4c);
            dst = (cDistributeSample*)((char*)dst + 0x4c);
            d = (uint32_t*)((char*)d + 0x4c);
        } while (first != last);
        result = dst;
    }
    return result;
}

// ===========================================================================
// @ 0x00a8a0a0
cDistributeSample* FUN_00a8a0a0(cDistributeSample* first, cDistributeSample* last, cDistributeSample* dst)
{
    cDistributeSample* out = dst;
    if (first != last) {
        do {
            ((void*(__thiscall*)(void*, const void*))&FUN_00537dc0)(&dst->mTransform, &first->mTransform);
            *(uint32_t*)&dst->mColorAlpha[0] = *(uint32_t*)&first->mColorAlpha[0];
            *(uint32_t*)&dst->mColorAlpha[1] = *(uint32_t*)&first->mColorAlpha[1];
            *(uint32_t*)&dst->mColorAlpha[2] = *(uint32_t*)&first->mColorAlpha[2];
            *(uint32_t*)&dst->mColorAlpha[3] = *(uint32_t*)&first->mColorAlpha[3];
            dst->mNumber = first->mNumber;
            ++first;
            ++dst;
        } while (first != last);
        out = dst;
    }
    return out;
}

// ===========================================================================
// @ 0x00a8a0f0
cDistributeSample* FUN_00a8a0f0(cDistributeSample* first, cDistributeSample* last, cDistributeSample* dst)
{
    cDistributeSample* out = dst;
    if (last != first) {
        do {
            last = (cDistributeSample*)((char*)last - 0x4c);
            dst = (cDistributeSample*)((char*)dst - 0x4c);
            ((void*(__thiscall*)(void*, const void*))&FUN_00537dc0)(&dst->mTransform, &last->mTransform);
            *(uint32_t*)&dst->mColorAlpha[0] = *(uint32_t*)&last->mColorAlpha[0];
            *(uint32_t*)&dst->mColorAlpha[1] = *(uint32_t*)&last->mColorAlpha[1];
            *(uint32_t*)&dst->mColorAlpha[2] = *(uint32_t*)&last->mColorAlpha[2];
            *(uint32_t*)&dst->mColorAlpha[3] = *(uint32_t*)&last->mColorAlpha[3];
            dst->mNumber = last->mNumber;
        } while (last != first);
        out = dst;
    }
    return out;
}
