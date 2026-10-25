// src/game/SPGonzago/SPGameInputManager.cpp -- migrated from slice(s) s00542980, s00427fd0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameInputManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#pragma intrinsic(memcpy)

// ---- items of slice s00427fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Variant {
    uint32_t data[4];
    uint16_t flags;      // 2 = owns/typed, 4 = needs clear
    uint16_t type;

    void __thiscall Clear(int full);                                                    // 0x93DB80
    void __thiscall Set(int type, int flags, const void* src, int elemSize, int count); // 0x93DD80

    Variant() : flags(0), type(0) {}
    inline Variant(const bool* v);
    ~Variant() { if (flags & 4) Clear(0); }
    void __thiscall SetBool(const bool* v);         // 0x422E20
    Variant* __thiscall SetInt(const int* v);       // 0x427FD0
    Variant* __thiscall SetFloat(const float* v);   // 0x428060
};
static const bool kTrue = true;   // compile-time constant condition kept by /Od
inline Variant::Variant(const bool* v)
{
    flags = 0;
    type = 0;
    type = 1;
    flags = 2;
    SetBool(v);
}
// ---- items of slice s00427fd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, uint);

// ---- items of slice s00542980 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
namespace EA {
struct Variant_s0054_2980 {
    struct Generic { unsigned int mData[4]; };
    struct Pointer { const void* mpData; unsigned int mnSize; unsigned int mnCount; };
    enum { kFlagUnsized = 2, kFlagAllocated = 4, kFlagNoCopy = 8, kFlagPointer = 0x30 };
    union {
        Generic mGeneric;
        Pointer mPointer;
        int mInt32;
        float mFloat;
    };
    unsigned short mFlags;          // +0x10
    unsigned short mTypeId;         // +0x12

    Variant_s0054_2980() : mFlags(0), mTypeId(0) {}
    ~Variant_s0054_2980() {
        if (mFlags & kFlagAllocated)
            Destruct(false);  // 0x0093db80 (EA::Variant::Destruct)
    }
    Variant_s0054_2980& operator=(const Variant_s0054_2980& x);                          // 0x00542b80
    template <typename T> Variant_s0054_2980& operator=(const T& x);        // 0x00422eb0 <int>, 0x00428060 <float>
    void Destruct(bool bReconstruct);                              // 0x0093db80
    void Construct(const Variant_s0054_2980& x, unsigned short flags);
    void Construct(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
                   unsigned int nCount);                           // 0x0093dd80
};
}
// ---- items of slice s00542980 end

// @ 0x00427fd0
Variant* __thiscall Variant::SetInt(const int* v)
{
    if (flags & 4)
        Clear(1);
    if (kTrue && (!(flags & 2) || type == 10)) {
        *(int*)this = *v;
        type = 10;
        flags = flags & 2;
    } else {
        Set(10, 0, v, 4, 1);
    }
    return this;
}

// @ 0x00542b80
EA::Variant & EA::Variant::operator=(EA::Variant const & x)
{
    if (mFlags & kfDestruct)
        Destruct(true);
    if (!(x.mFlags & kfConstruct) && (!(mFlags & kfInvariant) || mTypeId == x.mTypeId)) {
        mGeneric = x.mGeneric;
        mTypeId = x.mTypeId;
        mFlags = (x.mFlags & ~kfInvariant) | (mFlags & kfInvariant);
    } else
        Construct(x, 0);
    return *this;
}

// @ 0x00542c30
namespace EA {
void Variant_s0054_2980::Construct(const Variant_s0054_2980& x, unsigned short flags)
{
    if (x.mFlags & kFlagPointer)
        Construct(x.mTypeId, x.mFlags | flags, x.mPointer.mpData, x.mPointer.mnSize, x.mPointer.mnCount);
    else
        Construct(x.mTypeId, x.mFlags | flags, &x, 0x10, 1);
}
}  // namespace EA
