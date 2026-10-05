// Slice s0056d2b0: SP::Traits color/texture classifiers and small vector/hashtable helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

struct Feature { uint32_t field0; uint32_t field1; void* ptr; };
struct cFeatureVector { float add(const Feature& f, float weight); };   // @ 0x00571790

struct cRegionColorClassifier {
    bool DescribeTraits(void* stream);   // @ 0x0056d2b0
};
bool cRegionColorClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

struct UnkClass_0056d650 {
    void Method(void* a);   // @ 0x0056d650
};
void UnkClass_0056d650::Method(void*)
{
    // partial
}

struct cBaseColorClassifier {
    bool DescribeTraits(void* stream);   // @ 0x0056d810
};
bool cBaseColorClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

struct UnkClass_0056da90 {
    void Method(void* a);   // @ 0x0056da90
};
void UnkClass_0056da90::Method(void*)
{
    // partial
}

struct cTextureClassifier {
    bool DescribeTraits(void* stream);   // @ 0x0056dbe0
};
bool cTextureClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

// 3-float zero initializer
struct Vector3 {
    float x;
    float y;
    float z;
    Vector3* SetZero();   // @ 0x0056dec0
};

Vector3* Vector3::SetZero()
{
    ScratchSlots<1>();
    ((int*)this)[0] = 0;
    ((int*)this)[1] = 0;
    ((int*)this)[2] = 0;
    return this;
}

struct UnkClass_0056def0 {
    char pad0[4];
    void* mpEnd;   // +4
    bool Find(void* a, void* out);   // @ 0x0056def0
};
bool UnkClass_0056def0::Find(void*, void*)
{
    // partial: hashtable lookup returning bool
    return false;
}
