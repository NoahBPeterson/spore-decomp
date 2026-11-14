#include "game/types.h"
#include "EA/Variant.h"

// Local Variant stand-in for the non-canonical header EA/Variant.h (module SPEngine/SPPropertyList.obj).
struct Variant {
    enum { kfInvariant = 2, kfDestruct = 4 };
    enum { kTypeInt32 = 10 };
    uint32_t data[4];
    uint16_t flags;    // 2 = invariant/typed, 4 = needs destruct
    uint16_t type;

    void __thiscall Clear(int full);                                                    // 0x93DB80
    void __thiscall Set(int type, int flags, const void* src, int elemSize, int count); // 0x93DD80

    Variant() : flags(0), type(0) {}
    void __thiscall SetBool(const bool* v);         // 0x422E20
    Variant* __thiscall SetInt(const int* v);       // 0x427FD0
    Variant* __thiscall SetFloat(const float* v);   // 0x428060
};

// @ 0x00427fd0
Variant* __thiscall Variant::SetInt(const int* v)
{
    if (flags & kfDestruct)
        Clear(1);
    if (true && (!(flags & kfInvariant) || type == kTypeInt32)) {
        *(int*)this = *v;
        type = kTypeInt32;
        flags = flags & kfInvariant;
    } else {
        Set(kTypeInt32, 0, v, 4, 1);
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
// Local stand-in for EA::Variant_s0054_2980 (the retail object at this address is 0x14 bytes with the
// canonical member names); the header declares this method as bool, which does not match the retail bytes.
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
    void Construct(const Variant_s0054_2980& x, unsigned short flags);
    void Destruct(bool bReconstruct);                                                    // 0x0093db80
    void Construct(unsigned short typeId, unsigned short flags, const void* pData, unsigned int nSize,
                   unsigned int nCount);                                                 // 0x0093dd80
};

void Variant_s0054_2980::Construct(const Variant_s0054_2980& x, unsigned short flags)
{
    if (x.mFlags & kFlagPointer)
        Construct(x.mTypeId, x.mFlags | flags, x.mPointer.mpData, x.mPointer.mnSize, x.mPointer.mnCount);
    else
        Construct(x.mTypeId, x.mFlags | flags, &x, 0x10, 1);
}
}  // namespace EA
