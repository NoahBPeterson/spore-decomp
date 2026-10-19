// Slice s0056d2b0: SP::Traits color/texture classifiers and small vector/hashtable helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

struct cID { uint32_t cls; uint32_t type; };
struct cFeatureVector { float add(const cID& id, float weight); };   // @ 0x00571790

struct Alloc { char pad[1]; Alloc() {} };
struct Alloc17 { char pad[1]; Alloc17() {} };
struct Vec3 { float x, y, z; };
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
    char pad1[0x20 - 0x10];
    uint32_t mKey0, mKey1, mKey2;    // +0x20
    char pad2[0x38 - 0x2c];
    Vec3 mColor0;                    // +0x38
    Vec3 mColor1;                    // +0x44
    Vec3 mColor2;                    // +0x50
    char pad3[0x98 - 0x5c];
    Block* mpBegin;                  // +0x98
    Block* mpEnd;                    // +0x9c
};

// swatch colour table: three-pointer vector built by the out-of-line allocator ctor 0x00540470
struct SwatchVecBase {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; uint32_t mAlloc[2];
    SwatchVecBase() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    SwatchVecBase(const Alloc& a);   // 0x00540470
    SwatchVecBase(const Alloc17& a);   // 0x00540470
};
struct cSwatchColorLookupB {
    SwatchVecBase mTabColors;
    cSwatchColorLookupB() {}
    cSwatchColorLookupB(const Alloc& a) : mTabColors(a) {}
    cSwatchColorLookupB(const Alloc17& a) : mTabColors(a) {}
    bool Init();                     // @ 0x0056cde0
    unsigned GetAllocated(const void* a);   // @ 0x0056cf70
};
extern cSwatchColorLookupB* gSwatchColors;   // 0x015e4468
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0

struct WStrB {                       // eastl::basic_string<wchar_t>; ctor body out of line (0x0045dac0)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WStrB() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; Init(); }
    WStrB(WStrB& o);                 // 0x0056e2d0 (copy)
    ~WStrB() { FreeBuffer(); }
    void Init();                     // @ 0x0045dac0
    void FreeBuffer();               // @ 0x004237d0
};
struct DescSrc {                     // weight + description (by-value arg of cAnnotatedFeatureVector::Add)
    float value;
    WStrB str;
    DescSrc() {}
    DescSrc(DescSrc& src);           // @ 0x0056b020 (copy)
};
struct DescSrcI {                    // same layout, implicit copy inlined
    float value;
    WStrB str;
    DescSrcI(DescSrcI& src) : value(src.value), str(src.str) {}
};
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WString() { FreeBuffer(); }
    void FreeBuffer();               // @ 0x004237d0
    static wchar_t kEmpty[];         // 0x01667bac
};
struct Annot {
    float value;
    WString str;
    Annot() { InitEmpty(); }
    Annot(Annot& src);               // @ 0x0056b020 (copy)
    void InitEmpty();                // @ 0x0056afc0
};
int WStr_Format(void* s, const wchar_t* fmt, ...);   // 0x0041e050
struct cAnnotatedFeatureVector {
    float Add(const cID& id, DescSrc a);   // @ 0x0056aec0
    float Add(const cID& id, DescSrcI a);   // @ 0x0056aec0
    float Add(const cID& id, Annot a);     // @ 0x0056aec0
};

struct cRegionColorClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);   // 0x0056d2b0
};
// @ 0x0056d2b0
bool cRegionColorClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors) {
            ScratchSlots<1>();
            cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB(Alloc17());
            if (lookup->Init())
                gSwatchColors = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            cID id;
            id.cls = 0x52b27b5;
            DescSrc d;
            ScratchSlots<75>();
            d.value = 33.333f;
            id.type = gSwatchColors->GetAllocated(&c->mColor0);
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 0, c->mColor0);
            out->Add(id, d);
            id.type = gSwatchColors->GetAllocated(&c->mColor1) | 0x10000;
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 1, gSwatchColors->GetAllocated(&c->mColor1));
            out->Add(id, d);
            id.type = gSwatchColors->GetAllocated(&c->mColor2) | 0x20000;
            WStr_Format(&d.str, L"(%ls) %d: swatch %d", GetName(), 2, gSwatchColors->GetAllocated(&c->mColor2));
            out->Add(id, d);
        } else {
            Block* p15 = c->mpBegin;
            Block* n35 = p15;
            Block* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52b27b5;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3* j = &t14->mColors[i];
                    v18.type = (t14->mKeys[i] << 16) | gSwatchColors->GetAllocated(j);
                    Annot desc;
                    WStr_Format(&desc.str, L"(%ls) %d: swatch %d", GetName(), t14->mKeys[i], gSwatchColors->GetAllocated(j));
                    desc.value = (*weights)[n35 - p15];
                    out->Add(v18, desc);
                }
            }
        }
    }
    return true;
}

struct cBaseColorClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);   // 0x0056d650
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);   // 0x0056d810
};
// @ 0x0056d650
bool cBaseColorClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors) {
            ScratchSlots<1>();
            cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB();
            if (lookup->Init())
                gSwatchColors = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            Vec3* col = &c->mColor0;
            cID id;
            id.cls = 0x52c812a;
            id.type = gSwatchColors->GetAllocated(col);
            fv->add(id, 100.0f);
        } else {
            Block* p15 = c->mpBegin;
            Block* n35 = p15;
            Block* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c812a;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3* col = &t14->mColors[i];
                    v18.type = gSwatchColors->GetAllocated(col);
                    fv->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}
// @ 0x0056d810
bool cBaseColorClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool result = false;
    if (c) {
        if (!gSwatchColors) {
                        cSwatchColorLookupB* lookup = new ("OTDB", 0, 0, 0, 0) cSwatchColorLookupB(Alloc());
            if (lookup->Init())
                gSwatchColors = lookup;
            else
                return true;
        }
        result = true;
        if (c->mType == 0x2b978c46) {
            cID v18;
            v18.cls = 0x52c812a;
            Vec3* j = &c->mColor0;
            v18.type = gSwatchColors->GetAllocated(j);
            DescSrc item;
            ScratchSlots<42>();
            WStr_Format(&item.str, L"(%ls) swatch %d", GetName(), v18.type);
            item.value = 100.0f;
            out->Add(v18, item);
        } else {
            Block* p15 = c->mpBegin;
            Block* n35 = p15;
            Block* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c812a;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    Vec3* j = &t14->mColors[i];
                    v18.type = gSwatchColors->GetAllocated(j);
                    Annot desc;
                    WStr_Format(&desc.str, L"(%ls) swatch %d", GetName(), v18.type);
                    desc.value = (*weights)[n35 - p15];
                    out->Add(v18, desc);
                }
            }
        }
    }
    return true;
}

struct cRegionKeyClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);   // 0x0056da90
};
// @ 0x0056da90
bool cRegionKeyClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        if (c->mType == 0x2b978c46) {
            cID id;
            id.cls = 0x52c8ca5;
            id.type = c->mKey0;
            fv->add(id, 100.0f);
            id.type = c->mKey1;
            fv->add(id, 100.0f);
            id.type = c->mKey2;
            fv->add(id, 100.0f);
        } else {
            Block* p15 = c->mpBegin;
            Block* n35 = p15;
            Block* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c8ca5;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    v18.type = t14->mKeys[8 + i];
                    fv->add(v18, (*weights)[n35 - p15]);
                }
            }
        }
    }
    return result;
}

struct cTextureClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);   // 0x0056dbe0
};
// @ 0x0056dbe0
bool cTextureClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool result = false;
    if (c) {
        result = true;
        if (c->mType == 0x2b978c46) {
            DescSrc d;
            ScratchSlots<32>();
            cID id;
            id.cls = 0x52c8ca5;
            id.type = c->mKey0;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, d);
            id.type = c->mKey1;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, d);
            id.type = c->mKey2;
            WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), id.type);
            d.value = 33.333f;
            out->Add(id, *(DescSrcI*)&d);
            ScratchSlots<18>();
        } else {
            Block* p15 = c->mpBegin;
            Block* n35 = p15;
            Block* p12 = c->mpEnd;
            cID v18;
            v18.cls = 0x52c8ca5;
            for (; n35 != p12 && result; n35++) {
                Block* t14 = n35;
                unsigned tmp = t14->mnKeys;
                for (unsigned i = 0; i < tmp; i++) {
                    v18.type = t14->mKeys[8 + i];
                    DescSrc d;
                    ScratchSlots<19>();
                    WStr_Format(&d.str, L"(%ls) 0x%08x", GetName(), v18.type);
                    d.value = (*weights)[n35 - p15];
                    out->Add(v18, d);
                }
            }
        }
    }
    return true;
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
