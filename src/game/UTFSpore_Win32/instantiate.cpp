// src/game/UTFSpore_Win32/instantiate.cpp -- migrated from slice(s) s0083c900, s0050c6c0, s00475d00, s004553b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/instantiate.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00475d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct E8  { uint a, b; };
// ---- items of slice s00475d00 end

// ---- items of slice s0050c6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void ea_delete(void* p);
uint32_t GrowCopy(uint32_t n, uint32_t* first, uint32_t* last);   // 0x0042e5b0
void MoveInto(void* dst, void* src, int bytes);                   // vector<bool>::DoInsertValue
// ---- items of slice s0050c6c0 end

// ---- items of slice s0083c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gAppPropsMin;
extern float gAppPropsMax;
extern void* gAppPropsBuckets[];
extern void* vtbl_AppProps;   // 0x0141b5e4 (equiv t3)
struct AppPropsFields {
    void* vtbl;          // +0x00
    int   mParser;       // +0x04
    int   mRefCount;     // +0x08
    int   pad0c;         // +0x0c
    int   pad10;         // +0x10
    void* mpBucketArray; // +0x14
    int   mnBucketCount; // +0x18
    int   mnElementCount;// +0x1c
    float mMin;          // +0x20
    float mMax;          // +0x24
    int   pad28;         // +0x28
    AppPropsFields();                        // 0x0083cdd0
    AppPropsFields* VectorDtor(unsigned char flags); // 0x0083ce20
};
// ---- items of slice s0083c900 end

// @ 0x004558a0
void* VectorInsertU32(int* self, void* position, unsigned int value)
{
    (void)self; (void)position; (void)value;
    return 0;
}

// @ 0x004763a0
E8* UninitCopy8Destruct(E8* first, E8* last, E8* dest)
{
    E8* result = dest;
    for (E8* p = first; p != last; ++p, ++result) {
        if (result) *result = *p;
    }
    for (E8* q = first; q != last; ++q) {}
    return result;
}

// @ 0x0050d4e0
uint32_t* __fastcall FloatVec_Assign(uint32_t* self, uint32_t* x)
{
    if (x != self) {
        uint32_t n = (uint32_t)((int)x[1] - (int)*x) >> 2;
        if ((uint32_t)(((int)self[2] - (int)*self) >> 2) < n) {
            uint32_t pNew = GrowCopy(n, (uint32_t*)*x, (uint32_t*)x[1]);
            for (uint32_t p = *self; p < self[1]; p += 4) {}
            if (*self != 0 && *(int*)(*self - 4) != 0)
                ea_delete((void*)*self);
            *self = pNew;
            self[2] = *self + n * 4;
        } else if ((uint32_t)(((int)self[1] - (int)*self) >> 2) < n) {
            MoveInto((void*)*self, (void*)*x, (int)(x[1] - *x));
        } else {
            for (uint32_t d = *self, s = *x; d < self[1]; d += 4, s += 4)
                *(uint32_t*)d = *(uint32_t*)s;
        }
        self[1] = *self + n * 4;
    }
    return self;
}

// @ 0x0083cdd0
AppPropsFields::AppPropsFields()
{
    vtbl = vtbl_AppProps;
    mParser = 0;
    mRefCount = 0;
    pad0c = 0;
    mpBucketArray = gAppPropsBuckets;
    mnBucketCount = 1;
    mnElementCount = 0;
    mMin = gAppPropsMin;
    mMax = gAppPropsMax;
    pad28 = 0;
}
