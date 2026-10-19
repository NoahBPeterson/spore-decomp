// Slice s0056a7b0: SP::Traits classifier ExtractTraits/DescribeTraits and eastl::basic_string<wchar_t>
// helpers. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include <math.h>
#include <xmmintrin.h>   // switches /arch:SSE scalar float codegen to SSE at /Od

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);


// NOTE: at /Od the local-variable names below were chosen (tools/matching/od_names.py ranking) so the
// hashed stack-slot order reproduces the original; they are not the original source names.
// ---------------------------------------------------------------- shared helpers (as in s0056b680)
struct PList {                       // cPropertyList (refcounted)
    virtual void AddRef();           // 0x00
    virtual void Release();          // 0x04
};

// inline AsPointer variant (releases the held object, returns &mpObject)
struct PListRefInline {
    PList* mpObject;
    PListRefInline() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
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

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PList** ppList);   // 0x2c
};

// SP::cString (localized text handle, 0x18 bytes)
namespace SP {
class cString {
public:
    cString();                         // 0x006b5060
    ~cString();                        // 0x006b5240
    const wchar_t* GetText();          // 0x006b55c0
private:
    uint32_t mData[5];
};
}

// eastl::basic_string<wchar_t>, 16 bytes, with the inline default ctor / dtor
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mpBegin = kEmpty; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~WString() { FreeBuffer(); }
    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { const wchar_t* p0 = mpBegin; return p0; }
    void FreeBuffer();                // @ 0x004237d0
    static wchar_t kEmpty[];          // 0x01667bac
};

// the same string with its ctor body out of line (0x0045dac0): used where the original inlines the
// cAnnotation ctor but keeps the string init as a call
struct WStrB {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    WStrB() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; Init(); }
    ~WStrB() { FreeBuffer(); }
    void Init();                      // @ 0x0045dac0
    void FreeBuffer();                // @ 0x004237d0
};
struct AnnotN {                       // cAnnotation with the inline default ctor
    float value;
    WStrB str;
    AnnotN() {}
};
// SP::Traits::cAnnotation: weight + description string (by-value arg of cAnnotatedFeatureVector::Add);
// the default ctor is the out-of-line 0x0056afc0, the copy ctor the out-of-line 0x0056b020
struct Annot {
    float value;
    WString str;
    Annot() { InitEmpty(); }
    Annot(AnnotN& src);               // @ 0x0056b020 (copy)
    void InitEmpty();                 // @ 0x0056afc0
    Annot(Annot& src);                // @ 0x0056b020 (copy)
};

int WStr_Format(void* s, const wchar_t* fmt, ...);                                 // 0x0041e050

namespace SP {
    cPropertyManager* PropertyManager();                                              // 0x0067de30
    bool GetPropertyAsKey(PList* p, uint32_t id, uint32_t* out3);                     // 0x006a1250
    bool GetPropertyAsText(PList* p, uint32_t id, cString* out);                      // 0x006a1360
}

struct Block { char pad[0x1d8]; };
struct Creature {
    char pad[0x98];
    Block* mpBegin;       // +0x98
    Block* mpEnd;         // +0x9c
};

// ---------------------------------------------------------------- eastl feature vector
struct cID { uint32_t cls; uint32_t type; };

// SP::Traits::cFeatureVector: ctor/dtor out of line, vector of {cID, weight} at +0
struct FVEntry { cID id; float weight; };
struct cFeatureVector {
    FVEntry* mpBegin;
    FVEntry* mpEnd;
    FVEntry* mpCapacity;
    uint32_t mAllocator;
    uint32_t mPad[2];
    float mLen;                                  // +0x18
    cFeatureVector();                            // @ 0x00571640
    ~cFeatureVector();                           // @ 0x00564470
    float add(const cID& id, float weight);      // @ 0x00571790
};

// SP::Traits::cAnnotatedFeatureVector (vector_map<cID, cAnnotation> + total length)
struct AnnotPair {
    cID first;
    Annot second;
    AnnotPair(const cID& id, Annot& a) : first(id), second(a) {}
};
struct AnnotInsRes { AnnotPair* first; bool second; AnnotInsRes() {} };
struct cAnnotatedFeatureVector {
    char mMap[0x18];
    float mLen;                                                  // +0x18
    AnnotInsRes insert(const AnnotPair& p);                      // @ 0x0056e580
    float Add(const cID& id, Annot a);                           // @ 0x0056aec0
};

// ---------------------------------------------------------------- cBlockTypePercentClassifier
struct cBlockTypePercentClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);            // @ 0x0056b080
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);  // @ 0x0056b120
};

// @ 0x0056b120
bool cBlockTypePercentClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* self = c->mpBegin;
        Block* pl = self;
        Block* num = c->mpEnd;
        for (; pl != num && p30; pl++) {
            uint32_t* j = (uint32_t*)pl;
            cID w;
            w.cls = 0x1f71e85;
            w.type = j[1];
            PListRefInline weight;
            bool t = SP::PropertyManager()->GetPropertyList(j[1], j[0], weight.AsPointer());
            if (t) {
                SP::cString left;
                if (SP::GetPropertyAsText(weight.get(), 0x8f6fc401, &left)) {
                    Annot buf;
                    ScratchSlots<25>();
                    WStr_Format(&buf.str, L"(%ls) %ls", GetName(), left.GetText());
                    buf.value = (*weights)[pl - self];
                    out->Add(w, buf);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b080
bool cBlockTypePercentClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* block = (uint32_t*)t32;
            cID buf;
            buf.cls = 0x1f71e85;
            buf.type = block[1];
            fv->add(buf, (*weights)[t32 - begin]);
        }
    }
    return p30;
}

// ---------------------------------------------------------------- cTallnessClassifier
struct V3 {
    float x, y, z;
    V3() {}
    V3(const V3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct V3C : V3 {                    // Vector3 with an out-of-line copy ctor
    V3C(const V3& v);                // @ 0x004098a0
};
V3 operator-(const V3& a, const V3& b);   // @ 0x0041db10

struct M3 { float f[9]; };           // rw::math::fpu::Matrix33Template<float>: plain copy (rep movsd)
M3 operator*(const M3& a, const M3& b);   // @ 0x0041de20

struct Xf {                          // cSPTransform
    uint16_t mFlags;
    uint16_t mModificationCount;
    V3 mTranslation;
    float mScale;
    M3 mRotation;
    Xf();                                                            // @ 0x00409930
    void SetTranslation(const V3& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(M3 m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
};

struct Box3 {
    V3 mn;   // +0
    V3 mx;   // +0xc
    Box3();                               // @ 0x00409c00 (BoundingBox reset)
    Box3* AddPoint(const V3& p);          // @ 0x0056aba0
    void Transform(const Xf& t);          // @ 0x00409dd0
};

struct Sizer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e();
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void Vfn54(unsigned inst, unsigned group, float* data, int count, V3* mn, V3* mx);   // +0x54
};
Sizer* GetSizer();                                  // 0x00401010

struct SizedPart {                   // 0x1d8-byte creature part
    uint32_t group;                  // +0
    uint32_t instance;               // +4
    char pad8[8];
    float scale;                     // +0x10
    V3 pos;                          // +0x14
    char pad20[0x38 - 0x20];
    M3 rotA;                         // +0x38
    M3 rotB;                         // +0x5c
    char pad80[0x90 - 0x80];
    int count;                       // +0x90
    float data[1];                   // +0x94
    char padEnd[0x1d8 - 0x98];
};

template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

struct cTallnessClassifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    virtual bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);      // @ 0x0056a7b0 (0x1c)
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);        // @ 0x0056ad20
};

// @ 0x0056a7b0
bool cTallnessClassifier::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool i = false;
    if (c) {
        Box3 offset;
        SizedPart* x = (SizedPart*)c->mpBegin;
        SizedPart* count = (SizedPart*)c->mpEnd;
        for (; x != count; x++) {
            SizedPart* g = x;
            Box3 left;
            GetSizer()->Vfn54(g->instance, g->group, g->data, g->count, &left.mn, &left.mx);
            Xf list;
            list.SetTranslation(g->pos);
            list.SetRotation(g->rotB * g->rotA);
            list.SetScale(g->scale);
            left.Transform(list);
            offset.AddPoint(left.mn);
            offset.AddPoint(left.mx);
            i = true;
        }
        ScratchSlots<36>();
        V3C item = offset.mx - offset.mn;
        float right = max_(item.x, 0.5f);
        float data = max_(item.y, 0.5f);
        float d = max_(item.z, 0.5f);
        float part, s;
        if (right > data) { part = right; s = data; }
        else { part = data; s = right; }
        cID begin;
        begin.cls = 0x227f195;
        begin.type = 0;
        fv->add(begin, d * 100.0f / part);
        begin.type = 1;
        fv->add(begin, d * 100.0f / s);
        begin.type = 2;
        fv->add(begin, s * 100.0f / part);
    }
    return i;
}

// @ 0x0056ad20
bool cTallnessClassifier::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    cFeatureVector fv;
    ScratchSlots<32>();
    if (ExtractTraits(c, weights, &fv)) {
        FVEntry* it = fv.mpBegin;
        FVEntry* end = fv.mpEnd;
        for (; it != end; it++) {
            FVEntry* e = it;
            Annot desc;
            switch (e->id.type) {
            case 0:
                WStr_Format(&desc.str, L"(%ls) tall/wide", GetName());
                break;
            case 1:
                WStr_Format(&desc.str, L"(%ls) tall/thin", GetName());
                break;
            case 2:
                WStr_Format(&desc.str, L"(%ls) thin/wide", GetName());
                break;
            default:
                WStr_Format(&desc.str, L"(%ls) Error", GetName());
                break;
            }
            desc.value = it->weight;
            out->Add(e->id, desc);
        }
        return true;
    }
    return false;
}

// ---------------------------------------------------------------- unnamed helpers in this TU
Box3* Box3::AddPoint(const V3& p)
{
    if (mn[0] > p[0]) mn[0] = p[0];
    else if (mx[0] < p[0]) mx[0] = p[0];
    if (mn[1] > p[1]) mn[1] = p[1];
    else if (mx[1] < p[1]) mx[1] = p[1];
    if (mn[2] > p[2]) mn[2] = p[2];
    else if (mx[2] < p[2]) mx[2] = p[2];
    return this;
}

// @ 0x0056aec0
extern const float kAddEpsilon;   // 0x0013f4b68 (1.5258789e-05f)

float cAnnotatedFeatureVector::Add(const cID& id, Annot a)
{
    if (fabsf(a.value) > kAddEpsilon) {
        ScratchSlots<21>();
        AnnotInsRes r = insert(AnnotPair(id, a));
        float* pv = &r.first->second.value;
        if (!r.second)
            *pv = *pv + a.value;
        mLen = mLen + a.value;
        return *pv;
    } else {
        return 0.0f;
    }
}

struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
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
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                                       // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);                   // @ 0x0056b2e0
    bool DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out);        // @ 0x0056b440
};

// @ 0x0056b2e0
bool cEditorRigBlockType::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                uint32_t n37[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, n37)) {
                    cID buf;
                    buf.cls = 0x4ea801f;
                    buf.type = n37[0];
                    fv->add(buf, (*weights)[t32 - begin]);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b440
bool cEditorRigBlockType::DescribeTraits(Creature* c, float** weights, cAnnotatedFeatureVector* out)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            uint32_t* n30 = (uint32_t*)t32;
            ScratchSlots<1>();
            PListRefInline t25;
            bool p32 = SP::PropertyManager()->GetPropertyList(n30[1], n30[0], t25.AsPointer());
            if (p32) {
                WString n37;
                uint32_t buf[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, buf)) {
                    cID owner;
                    owner.cls = 0x4ea801f;
                    owner.type = buf[0];
                    if (n37.empty())
                        WStr_Format(&n37, L"0x%08x", buf[0]);
                    ScratchSlots<1>();
                    AnnotN n6;
                    WStr_Format(&n6.str, L"(%ls) %ls", GetName(), n37.c_str());
                    n6.value = (*weights)[t32 - begin];
                    ScratchSlots<25>();
                    out->Add(owner, n6);
                }
            }
        }
    }
    return p30;
}
