// Slice s0056c570: SP::Traits author/feed/texture classifiers, cMetadataSummarizer, cAssetMetadata.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

struct Feature { uint32_t field0; uint32_t field1; };
struct WStrSrc;
struct cFeatureVector { float add(const Feature& f, float weight); float addDescribed(const Feature& f, WStrSrc d); };   // @ 0x00571790 / 0x0056aec0

struct PList {                       // refcounted resource
    virtual void AddRef();           // 0x00
    virtual void Release();          // 0x04
};
struct PListRefInline {
    PList* mpObject;
    PListRefInline() : mpObject(0) {}
    ~PListRefInline() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer()
    {
        if (mpObject) {
            PList* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct ResKey { uint32_t instance; uint32_t type; uint32_t group; };
struct IObjectService {              // returned by 0x008de1a0
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(ResKey* key, PList** out, int a, int b, int c, int d);   // 0x0c
};
IObjectService* ObjectError();       // 0x008de1a0 (cdecl)
struct Meta {
    int64_t GetAssetKey();           // @ 0x005508a0 (thiscall, edx:eax)
    const wchar_t* GetName();        // @ 0x00550880 (thiscall)
    unsigned GetTagCount();          // @ 0x005509b0 (thiscall)
    unsigned GetCount2();            // @ 0x005508e0 (thiscall)
    const char* GetItem(unsigned i); // @ 0x00550910 (thiscall, ret 4)
    const wchar_t* GetTag(unsigned i);   // @ 0x005509e0 (thiscall, ret 4)
};
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned int);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseSens);                // 0x00932f30
uint32_t FNV1_String8(const char* s, uint32_t seed, int caseSens);                    // 0x00932e80
struct WStr {                         // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WStr() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WStr() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};
struct WStrSrc {                      // weight + description string (by-value arg of cFeatureVector::AddDescribed)
    float value;
    WStr str;
    WStrSrc() { InitEmpty(); }
    WStrSrc(WStrSrc& src);            // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
};
int WStr_Format(WStr* s, const wchar_t* fmt, ...);                                    // 0x0041e050

Meta* GetModelInfo(PListRefInline* r);   // 0x00421f60 (cdecl)
uint32_t FNV1Hash(const void* data, uint32_t length, uint32_t hash);  // 0x00932E50

struct cAuthorClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056c570
    bool DescribeTraits(void* creature, void* weights, cFeatureVector* features);   // @ 0x0056c670
};
bool cAuthorClassifier::ExtractTraits(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x518af1d;
            int64_t k = p->GetAssetKey();
            f.field1 = FNV1Hash(&k, 8, 0x811c9dc5);
            features->add(f, 100.0f);
        }
    }
    return true;
}
bool cAuthorClassifier::DescribeTraits(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x518af1d;
            int64_t k = p->GetAssetKey();
            f.field1 = FNV1Hash(&k, 8, 0x811c9dc5);
            WStrSrc d;
            ScratchSlots<28>();
            WStr_Format(&d.str, L"(%ls) %ls", GetName(), p->GetName());
            d.value = 100.0f;
            features->addDescribed(f, d);
        }
    }
    return true;
}

struct cMetadataSummarizer {
    bool ExtractParameters(void* a, void* b, cFeatureVector* features);  // @ 0x0056c7d0
};
bool cMetadataSummarizer::ExtractParameters(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x68375d7;
            unsigned count = p->GetTagCount();
            for (unsigned i = 0; i < count; i++) {
                const wchar_t* str = p->GetTag(i);
                if (wcsncmp(str, L"set:", 4) == 0) {
                    f.field1 = FNV1_String16(str, 0x811c9dc5, 0);
                    features->add(f, 100.0f);
                    break;
                }
            }
        }
    }
    return true;
}

struct cAssetMetadata {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool SetMetadata(void* creature, void* weights, cFeatureVector* features);   // @ 0x0056c910
};
bool cAssetMetadata::SetMetadata(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x68375d7;
            unsigned count = p->GetTagCount();
            for (unsigned i = 0; i < count; i++) {
                const wchar_t* str = p->GetTag(i);
                if (wcscmp(str, L"set:") == 0) {
                    f.field1 = FNV1_String16(str, 0x811c9dc5, 0);
                    WStrSrc d;
                    ScratchSlots<28>();
                    WStr_Format(&d.str, L"(%ls) %ls", GetName(), str);
                    d.value = 100.0f;
                    features->addDescribed(f, d);
                    break;
                }
            }
        }
    }
    return true;
}

struct cFeedClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(void* creature, void* weights, cFeatureVector* features);  // @ 0x0056cb30
    bool DescribeTraits(void* creature, void* weights, cFeatureVector* features); // @ 0x0056cc50
};
bool cFeedClassifier::ExtractTraits(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x518b883;
            unsigned count = p->GetCount2();
            for (unsigned i = 0; i < count; i++) {
                f.field1 = FNV1_String8(p->GetItem(i), 0x811c9dc5, 0);
                features->add(f, 100.0f);
            }
        }
    }
    return true;
}
bool cFeedClassifier::DescribeTraits(void* creature, void*, cFeatureVector* features)
{
    ResKey key = *(ResKey*)((char*)creature + 8);
    key.type = 0x30bdee3;
    PListRefInline ref;
    if (ObjectError()->GetResource(&key, ref.AsPointer(), 0, 0, 0, 0)) {
        Meta* p = GetModelInfo(&ref);
        if (p) {
            Feature f;
            f.field0 = 0x518b883;
            unsigned count = p->GetCount2();
            for (unsigned i = 0; i < count; i++) {
                f.field1 = FNV1_String8(p->GetItem(i), 0x811c9dc5, 0);
                WStrSrc d;
                ScratchSlots<28>();
                WStr_Format(&d.str, L"(%ls) %hs", GetName(), p->GetItem(i));
                d.value = 100.0f;
                features->addDescribed(f, d);
            }
        }
    }
    return true;
}

struct cPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, struct PropListA** ppList);   // 0x2c
};
cPropertyManager* PropertyManager();   // 0x0067de30
struct Vec3c { float x, y, z; };
struct Prop {                          // cProperty header
    void* mpData;                      // +0x00
    uint32_t pad4;
    uint32_t mCount;                   // +0x08
    uint32_t pad0c;
    uint16_t mFlags;                   // +0x10
    uint16_t mInline;                  // +0x12
    unsigned Count()
    {
        if (mFlags & 0x30) {
            return mCount;
        } else if (mInline) {
            return 1;
        }
        return 0;
    }
    struct Vec3c* Data();
};
struct PropListA {
    virtual void AddRef();             // 0x00
    virtual void Release();            // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);        // 0x1c
    virtual void v20(); virtual void v24();
    virtual Prop* GetProperty(uint32_t id);       // 0x28
};
struct PropListRefA {
    PropListA* mpObject;
    PropListRefA() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PropListRefA() { if (mpObject) mpObject->Release(); }
    PropListA* get() const { return mpObject; }
    PropListA** AsPointer()
    {
        if (mpObject) {
            PropListA* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};
struct TagE { TagE() {} };
inline Vec3c* Prop::Data()
{
    if (mFlags & 0x30) {
        return (Vec3c*)mpData;
    } else if (mInline) {
        return (Vec3c*)this;
    }
    return 0;
}
struct SpVecV3 {
    Vec3c* mpBegin; Vec3c* mpEnd; Vec3c* mpCapacity; unsigned int mAlloc[2];
    Vec3c* erase(Vec3c* first, Vec3c* last);                  // 0x0050f740
    void assign(Vec3c* first, Vec3c* last, TagE tag);         // 0x0056fee0
    void clear() { erase(mpBegin, mpEnd); }
    void assign(Vec3c* first, Vec3c* last) { TagE e; TagE t; TagE m; TagE j; uint32_t s[6]; assign(first, last, j); }
};
struct cSwatchColorLookup {
    SpVecV3 mTabColors;
    cSwatchColorLookup() { mTabColors.mpBegin = 0; mTabColors.mpEnd = 0; mTabColors.mpCapacity = 0; }
    bool Init();   // @ 0x0056cde0
};
bool cSwatchColorLookup::Init()
{
    PropListRefA tmp;
    bool t14 = PropertyManager()->GetPropertyList(0x2ab48add, 0x97097e36, tmp.AsPointer());
    if (t14 && tmp.get()->HasProperty(0xd29675ec)) {
        Prop* v33 = tmp.get()->GetProperty(0xd29675ec);
        Vec3c* n40;
        unsigned len;
        len = v33->Count();
        n40 = v33->Data();
        if (len > 0) {
            mTabColors.clear();
            mTabColors.assign(n40, n40 + len);
            return true;
        }
    }
    return false;
}

// eastl::vector<float> helper (nearest-element scan)
struct VecFloat {
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    unsigned GetAllocated(const void* a);   // @ 0x0056cf70 (index of nearest colour)
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
const Vec3& Vec3Sub(Vec3* out, const Vec3* a, const Vec3* b);   // @ 0x0041db10 cdecl
float VectorLength(const Vec3* v);            // @ 0x0040ae50 cdecl, x87 return
unsigned VecFloat::GetAllocated(const void* a)
{
    // @ 0x0056cf70: index of the element (stride 12) whose distance to the query is smallest
    int value = 0;
    float v18;
    Vec3* left;
    Vec3* v8;
    Vec3* mem;
    float j;
    left = (Vec3*)mpBegin;
    mem = (Vec3*)mpEnd;
    v8 = left;
    {
        Vec3 t14;
        Vec3 tmp = Vec3Sub(&t14, (const Vec3*)a, left);
        v18 = VectorLength(&tmp);
    }
    for (++left; left != mem; ++left) {
        ScratchSlots<1>();
        Vec3 t14;
        Vec3 tmp = Vec3Sub(&t14, (const Vec3*)a, left);
        j = VectorLength(&tmp);
        if (v18 > j)
            value = (int)(left - v8);
    }
    ScratchSlots<1>();
    return value;
}

struct Block {                       // creature part, 0x1d8 bytes
    char pad0[0xd4];
    uint32_t mnKeys;                 // +0xd4
    uint32_t mKeys[16];              // +0xd8
    Vec3 mColors[1];                 // +0x118
    char pad2[0x1d8 - 0x124];
};
struct Creature {
    char pad0[0x0c];
    uint32_t mType;                  // +0x0c
    char pad1[0x38 - 0x10];
    Vec3 mColor0;                    // +0x38
    Vec3 mColor1;                    // +0x44
    Vec3 mColor2;                    // +0x50
    char pad3[0x98 - 0x5c];
    Block* mpBegin;                  // +0x98
    Block* mpEnd;                    // +0x9c
};
extern cSwatchColorLookup* gSwatchColors;   // 0x015e4468
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0

struct cTextureClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                             // 0x18
    bool ExtractTraits(Creature* creature, float** weights, cFeatureVector* features);  // @ 0x0056d080
};
bool cTextureClassifier::ExtractTraits(Creature* creature, float** weights, cFeatureVector* features)
{
    bool result = false;
    if (creature) {
        if (!gSwatchColors) {
            ScratchSlots<1>();
            cSwatchColorLookup* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookup();
            if (lookup->Init())
                gSwatchColors = lookup;
            else
                return true;
        }
        result = true;
        if (creature->mType == 0x2b978c46) {
            Feature f;
            f.field0 = 0x52b27b5;
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor0);
            features->add(f, 33.333f);
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor1) | 0x10000;
            features->add(f, 33.333f);
            f.field1 = ((VecFloat*)gSwatchColors)->GetAllocated(&creature->mColor2) | 0x20000;
            features->add(f, 33.333f);
        } else {
            Block* p15 = creature->mpBegin;
            Block* n35 = p15;
            Block* p12 = creature->mpEnd;
            Feature v18;
            v18.field0 = 0x52b27b5;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3* col = &t14->mColors[i];
                    v18.field1 = (t14->mKeys[i] << 16) | ((VecFloat*)gSwatchColors)->GetAllocated(col);
                    features->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}
