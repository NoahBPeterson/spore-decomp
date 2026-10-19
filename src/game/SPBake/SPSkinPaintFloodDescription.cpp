// src/game/SPBake/SPSkinPaintFloodDescription.cpp -- migrated from slice(s) s00535d00, s00534cf0 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinPaintFloodDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Swarm/cDescription.h"
#include "EA/ArgScript/cICommand.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/ArgScript/cState.h"
#pragma intrinsic(strlen)

// ---- items of slice s00534cf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                // @ 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3_s0053_4cf0 : Vector3T {
    cSPVector3_s0053_4cf0() {}
    cSPVector3_s0053_4cf0(const cSPVector3_s0053_4cf0& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0053_4cf0(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
namespace nSPSkinner {
struct sp_vector_allocator {
    uint32_t mData[2];
    void deallocate(void* p, size_t) {
        if (((uint32_t*)p)[-1])
            delete[] (char*)p;
    }
};
}
namespace nSPSkinner {
template<typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
};
}
namespace nSPSkinner {
template<typename T> struct sp_vector : public VectorBase<T> {
    sp_vector() {}
    sp_vector(const sp_vector& x);
    ~sp_vector() { DoDestroyValues(this->mpBegin, this->mpEnd); }
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
};
}
namespace nSPSkinner {
struct cPaintVarEvalList_s0053_4cf0 {
    struct Modifier { cSPVector3_s0053_4cf0 mVec; uint8_t mModType; uint8_t pad[3]; };
    struct Entry { float mRangeMin, mRangeMax, mValueMin, mValueMax; uint8_t mVariable, mVarModIdx, mApplyMode, mEdgeMode; };
    sp_vector<Modifier> mModifiers;     // +0x00
    sp_vector<Entry> mEntries;          // +0x14
    sp_vector<float> mCurveData;        // +0x28
    cPaintVarEvalList_s0053_4cf0() { uint32_t unused; }
    cPaintVarEvalList_s0053_4cf0(const cPaintVarEvalList_s0053_4cf0& x);
};
}
// ---- items of slice s00534cf0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" size_t __cdecl strlen(const char*);

// ---- items of slice s00535d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);   // 0x0042dee0
struct Elem16 {
    uint32_t d[4];
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    uint32_t mAlloc[2];
    Vec16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec16(const Vec16& x);
};
void* uninitialized_copy16(Elem16* first, Elem16* last, Elem16* dest);   // 0x005371a0
// ---- items of slice s00535d00 end

// @ 0x00535c60
namespace nSPSkinner {
cPaintVarEvalList_s0053_4cf0::cPaintVarEvalList_s0053_4cf0(const cPaintVarEvalList_s0053_4cf0& x)
: mModifiers(x.mModifiers), mEntries(x.mEntries), mCurveData(x.mCurveData)
{
    ScratchSlots<39>();
}
}  // namespace nSPSkinner

// @ 0x00535d00
Vec16::Vec16(const Vec16& x)
{
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    Elem16* p = (n == 0) ? 0 : (Elem16*)EASTL_Allocate(mAlloc, n * 16, 4, 0);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    mpEnd = (Elem16*)uninitialized_copy16(x.mpBegin, x.mpEnd, mpBegin);
}
