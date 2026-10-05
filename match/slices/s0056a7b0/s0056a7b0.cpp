// Slice s0056a7b0: SP::Traits classifier ExtractTraits/DescribeTraits and eastl::basic_string<wchar_t>
// helpers. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

// ---------------------------------------------------------------- eastl feature vector
struct Feature {
    uint32_t field0;    // +0
    uint32_t field1;    // +4
    void* ptr;          // +8
};

struct cFeatureVector {
    float add(const Feature& f, float weight);   // @ 0x00571790
};

// ---------------------------------------------------------------- cBlockTypePercentClassifier
struct cBlockTypePercentClassifier {
    char ExtractTraits(void* creature, float** weights, cFeatureVector* features);   // @ 0x0056b080
    bool DescribeTraits(void* stream);                                              // @ 0x0056b120
};

bool cBlockTypePercentClassifier::DescribeTraits(void*)
{
    // partial: serialization body not reconstructed
    return false;
}

char cBlockTypePercentClassifier::ExtractTraits(void* creature, float** weights, cFeatureVector* features)
{
    bool result = false;
    if (creature) {
        result = true;
        char* begin = *(char**)((char*)creature + 0x98);
        char* end = begin;
        char* it = *(char**)((char*)creature + 0x9c);
        while (end != it && result) {
            Feature f;
            f.field0 = 0x1f71e85;
            f.field1 = *(uint32_t*)(end + 4);
            f.ptr = end;
            features->add(f, (*weights)[(end - begin) / 0x1d8]);
            end += 0x1d8;
        }
    }
    return result;
}

// ---------------------------------------------------------------- cTallnessClassifier
struct cTallnessClassifier {
    bool ExtractTraits(void* creature, float** weights, cFeatureVector* features);   // @ 0x0056a7b0
    bool DescribeTraits(void* stream);                                              // @ 0x0056ad20
};

bool cTallnessClassifier::ExtractTraits(void*, float**, cFeatureVector*)
{
    // partial: full classifier body (hashtable/string construction) not reconstructed
    return false;
}

bool cTallnessClassifier::DescribeTraits(void*)
{
    // partial
    return false;
}

// ---------------------------------------------------------------- unnamed helpers in this TU
struct Box3 {
    float min[3];   // +0
    float max[3];   // +0xc
    void AddPoint(const float* p);   // @ 0x0056aba0
};

void Box3::AddPoint(const float* p)
{
    for (int i = 0; i < 3; ++i) {
        if (min[i] > p[i])
            min[i] = p[i];
        else if (p[i] > max[i])
            max[i] = p[i];
    }
}

struct cTallnessMetric {
    char pad0[0x18];
    float mTotal;   // +0x18
    float Add(const void* key, float amount);   // @ 0x0056aec0
};

float cTallnessMetric::Add(const void* key, float amount)
{
    // partial: eastl::basic_string based metric accumulation
    if (amount < 0.0f)
        amount = -amount;
    if (amount <= 1.5258789e-05f)
        return 0.0f;
    mTotal += amount;
    return amount;
}

struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void AllocateSelf(wchar_t* p, wchar_t* q);   // @ 0x00423820
};

extern wchar_t g_emptyWStr[];   // 0x01667bac

void WString_FreeBuffer(void* s);                                   // 0x004237d0

struct WStrHolder {
    uint32_t pad0;
    WStr str;
    WStrHolder* InitEmpty();   // @ 0x0056afc0
};

WStrHolder* WStrHolder::InitEmpty()
{
    WStr* pStr = &str;
    int tmp;
    pStr->mpBegin = 0;
    pStr->mpEnd = 0;
    pStr->mpCapacity = 0;
    pStr->mpBegin = g_emptyWStr;
    pStr->mpEnd = pStr->mpBegin;
    pStr->mpCapacity = pStr->mpBegin + 1;
    return this;
}

struct WStrSrc {
    float value;
    WStr str;
    WStrSrc* CopyInit(WStrSrc* src);   // @ 0x0056b020
};

WStrSrc* WStrSrc::CopyInit(WStrSrc* src)
{
    value = src->value;
    WStr* d = &src->str;
    WStr* s = &str;
    s->mpBegin = 0;
    s->mpEnd = 0;
    s->mpCapacity = 0;
    s->AllocateSelf(d->mpBegin, d->mpEnd);
    return this;
}

// ---------------------------------------------------------------- cEditorRigBlockType
struct cEditorRigBlockType {
    char pad[4];
    bool ExtractTraits(void* creature, float** weights, cFeatureVector* features);   // @ 0x0056b2e0
    bool DescribeTraits(void* stream);                                              // @ 0x0056b440
};

bool cEditorRigBlockType::ExtractTraits(void*, float**, cFeatureVector*)
{
    // partial: uses SP::PropertyManager / SP::GetPropertyAsKey and hashtable lookups
    return false;
}

bool cEditorRigBlockType::DescribeTraits(void*)
{
    // partial
    return false;
}
