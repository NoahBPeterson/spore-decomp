// Slice s0088ed20 -- the value constructor the FontServer face map's hashtable
// instantiates: eastl::pair<const eastl::string16, FontServer::Face> copied from
// another value (the sibling 0x0088ed90 builds the same value from (key, face)).
#include "game/types.h"
#include "eastl/string.h"
#include "EA/Text/FontServer.h"
#include <string.h>

// The retail value type is eastl::pair<const eastl::string16, FontServer::Face> as
// built by eastl::hashtable<...>::DoCreateNode(): the string is copy-initialized from
// the key with basic_string's own copy constructor, which goes through RangeInitialize
// (the retail EASTL emits memcpy here, not the vendored memmove).
struct FaceMapString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    eastl::allocator mAllocator;

    typedef unsigned int size_type;

    void AllocateSelf(size_type count); // 0x00429760

    static wchar_t* CharStringUninitializedCopy(const wchar_t* pSource, const wchar_t* pSourceEnd,
                                               wchar_t* pDestination) {
        memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(wchar_t));
        return pDestination + (pSourceEnd - pSource);
    }

    void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd) {
        const size_type n = (size_type)(pEnd - pBegin);
        AllocateSelf((size_type)(n + 1));
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }

    FaceMapString(const eastl::string16& source)
        : mpBegin(0), mpEnd(0), mpCapacity(0) {
        RangeInitialize(source.mpBegin, source.mpEnd);
    }
};

// The list copy constructor manages its embedded node pool and overflow nodes.
struct FaceSourceListCopy {
    unsigned char mStorage[0x47c];
    FaceSourceListCopy(const FaceSourceListCopy&); // 0x0088e980
};

// Stand-in for EA::Text::FontServer::Face (0x4bc bytes).  The retail copy is the
// compiler-generated memberwise one: the family array with `rep movsd`, then the
// fixed_list member through its out-of-line copy constructor.
struct FaceMapFace {
    wchar_t mFamily[32];
    FaceSourceListCopy mFaceSourceList;
};

struct FaceMapValue {
    const FaceMapString first;
    FaceMapFace second;
    FaceMapValue(const FaceMapValue& source);
};

// @ 0x0088ed20
FaceMapValue::FaceMapValue(const FaceMapValue& source)
    : first(*reinterpret_cast<const eastl::string16*>(&source.first)),
      second(source.second) {
}
