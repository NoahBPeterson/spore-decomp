// Slice s0056b680: SP::Traits cEditorPartCount / cRigBlockTag / cTextureTag classifier methods.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

struct Feature { uint32_t field0; uint32_t field1; void* ptr; };
struct cFeatureVector { float add(const Feature& f, float weight); };   // @ 0x00571790

// ---------------------------------------------------------------- cEditorPartCount
struct cEditorPartCount {
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056b680
    bool DescribeTraits(void* stream);                                           // @ 0x0056b7d0
};

bool cEditorPartCount::ExtractTraits(void*, void*, cFeatureVector*)
{
    // partial: iterates creature+0x98..0x9c, SP::PropertyManager / SP::GetPropertyAsKey, add key 0x4eab460
    return false;
}

bool cEditorPartCount::DescribeTraits(void*)
{
    // partial
    return false;
}

// ---------------------------------------------------------------- cRigBlockTag
struct cRigBlockTag {
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056b9e0
    bool DescribeTraits(void* stream);                                           // @ 0x0056bd30
};

bool cRigBlockTag::ExtractTraits(void*, void*, cFeatureVector*)
{
    // partial: BlockKey hashtable construction
    return false;
}

bool cRigBlockTag::DescribeTraits(void*)
{
    // partial
    return false;
}

// ---------------------------------------------------------------- cTextureTag
struct cTextureTag {
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056bfa0
    bool DescribeTraits(void* stream);                                           // @ 0x0056c2d0
};

bool cTextureTag::ExtractTraits(void*, void*, cFeatureVector*)
{
    // partial
    return false;
}

bool cTextureTag::DescribeTraits(void*)
{
    // partial
    return false;
}
