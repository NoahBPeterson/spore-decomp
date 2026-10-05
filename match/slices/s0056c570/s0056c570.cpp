// Slice s0056c570: SP::Traits author/feed/texture classifiers, cMetadataSummarizer, cAssetMetadata.
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

struct cAuthorClassifier {
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056c570
    bool DescribeTraits(void* stream);                                           // @ 0x0056c670
};
bool cAuthorClassifier::ExtractTraits(void*, void*, cFeatureVector*)
{
    // partial: queries an asset metadata service, hashes asset key, adds key 0x518af1d weight 100.0f
    return true;
}
bool cAuthorClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

struct cMetadataSummarizer {
    bool ExtractParameters(void* a, void* b, cFeatureVector* features);  // @ 0x0056c7d0
};
bool cMetadataSummarizer::ExtractParameters(void*, void*, cFeatureVector*)
{
    // partial: iterates asset metadata params, matches L"set:" via wcsncmp, hashes with FNV1_String16
    return false;
}

struct cAssetMetadata {
    void SetMetadata(void* a, void* b);   // @ 0x0056c910
};
void cAssetMetadata::SetMetadata(void*, void*)
{
    // partial
}

struct UnkClass_0056cb30 {
    void Method(void* a);   // @ 0x0056cb30
};
void UnkClass_0056cb30::Method(void*)
{
    // partial
}

struct cFeedClassifier {
    bool DescribeTraits(void* stream);   // @ 0x0056cc50
};
bool cFeedClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

struct cSwatchColorLookup {
    void Init(void* a);   // @ 0x0056cde0
};
void cSwatchColorLookup::Init(void*)
{
    // partial
}

// eastl::vector<float> helper (nearest-element scan)
struct VecFloat {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void* GetAllocated(void* a);   // @ 0x0056cf70
};
void* VecFloat::GetAllocated(void*)
{
    // partial
    return 0;
}

struct cTextureClassifier {
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056d080
};
bool cTextureClassifier::ExtractTraits(void*, void*, cFeatureVector*)
{
    // partial
    return false;
}
