// Slice s0056b680: SP::Traits cEditorPartCount / cRigBlockTag / cTextureTag ExtractTraits + DescribeTraits.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------- shared helpers
struct Alloc { Alloc() {} };

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

// out-of-line AsPointer variant (0x0041d870)
struct PListRefCall {
    PList* mpObject;
    PListRefCall() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    ~PListRefCall() { if (mpObject) mpObject->Release(); }
    PList* get() const { return mpObject; }
    PList** AsPointer();   // @ 0x0041d870
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PList** ppList);   // 0x2c
};

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

struct Feature { uint32_t id; uint32_t value; };
struct cFeatureVector {
    float add(const Feature& f, float weight);          // @ 0x00571790
    float addDescribed(const Feature& f, WStrSrc d);    // @ 0x0056aec0
};

namespace SP {
    cPropertyManager* PropertyManager();                                              // 0x0067de30
    bool GetPropertyAsKey(PList* p, uint32_t id, uint32_t* out3);                     // 0x006a1250
    bool GetPropertyAsString16(PList* p, uint32_t id, WStr* out);                     // 0x006a1400
}
int WStr_Format(WStr* s, const wchar_t* fmt, ...);                                    // 0x0041e050
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseSens);                // 0x00932f30

// eastl::find over wchar_t with a const char& value (inline, params get /Od slots)
inline wchar_t* wfind(wchar_t* first, wchar_t* last, const char& value)
{
    while (first != last && *first != value)
        ++first;
    return first;
}

struct Block { char pad[0x1d8]; };
struct Creature {
    char pad[0x98];
    Block* mpBegin;       // +0x98
    Block* mpEnd;         // +0x9c
};
struct TextureBlock {     // element with +0xd4 key count, +0xf8 key array
    char pad[0xd4];
    uint32_t mnKeys;
    char pad2[0xf8 - 0xd8];
    uint32_t mKeys[1];
};

extern const float kPartCountWeight;     // 0x01473c70 (10.0f)
extern uint32_t gTextureGroup;           // 0x015e45a4

struct VSet {                            // eastl::vector_set<unsigned> (0x18 bytes)
    uint32_t mb, me, mc, ma, mx, my;
    VSet(const Alloc& = Alloc());        // @ 0x00540470
    VSet(const VSet& o);                 // @ 0x00564690
    ~VSet() { DoDestroyValues(); }
    void DoDestroyValues();              // @ 0x00553fb0
    struct InsRes { uint32_t* it; bool ok; InsRes() {} };
    InsRes insert(const uint32_t& v);    // @ 0x00554020
};

// ---------------------------------------------------------------- cEditorPartCount
struct cEditorPartCount {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b680
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056b7d0
};

// @ 0x0056b680
bool cEditorPartCount::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
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
                    Feature buf;
                    buf.id = 0x4eab460;
                    buf.value = n37[0];
                    fv->add(buf, kPartCountWeight);
                }
            }
        }
    }
    return p30;
}

// @ 0x0056b7d0
bool cEditorPartCount::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
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
                WStr n37;
                uint32_t buf[3] = { 0, 0, 0 };
                if (SP::GetPropertyAsKey(t25.get(), 0x186609d, buf)) {
                    Feature owner;
                    owner.id = 0x4eab460;
                    owner.value = buf[0];
                    if (n37.empty())
                        WStr_Format(&n37, L"0x%08x", buf[0]);
                    WStrSrc n6;
                    ScratchSlots<1>();
                    WStr_Format(&n6.str, L"(%ls) %ls", GetName(), n37.c_str());
                    n6.value = kPartCountWeight;
                    ScratchSlots<25>();
                    fv->addDescribed(owner, n6);
                }
            }
        }
    }
    return p30;
}

// ---------------------------------------------------------------- cRigBlockTag
struct BlockKey { uint32_t k0, k1; BlockKey(uint32_t a, uint32_t b) { k0 = a; k1 = b; } };
struct BlockEntry {                      // hashtable value_type: pair<BlockKey, vector_set<uint>>
    BlockKey first;
    VSet second;
    BlockEntry(const BlockKey& k, const VSet& v) : first(k), second(v) {}
};
struct false_type {};
struct BlockInsRes { uint32_t* node; uint32_t bucket; bool ok; BlockInsRes() {} };
struct BlockHash {                       // eastl::hashtable<BlockKey, ...> at tag+8
    BlockInsRes DoInsertValue(const BlockEntry& v, false_type);   // @ 0x0056e320
};
struct BlockSet {                        // vector_set<uint>
    uint32_t* mb; uint32_t* me;
};

struct cRigBlockTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    BlockHash mTable;                                                               // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056b9e0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056bd30
};

// @ 0x0056b9e0
bool cRigBlockTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            uint32_t* e = (uint32_t*)it;
            BlockInsRes res;
            res.node = 0;
            res.bucket = 0;
            res.ok = false;
            {
                VSet tmp;
                BlockEntry ent(BlockKey(e[0], e[1]), tmp);
                res = mTable.DoInsertValue(ent, false_type());
            }
            BlockSet* set = (BlockSet*)((char*)res.node + 8);
            if (res.ok) {
                PListRefCall pl;
                bool ok = SP::PropertyManager()->GetPropertyList(e[1], e[0], pl.AsPointer());
                if (ok) {
                    WStr s;
                    if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                        VSet* vs = (VSet*)set;
                        wchar_t* cur = s.mpBegin;
                        wchar_t* tokEnd = cur;
                        wchar_t* end = s.mpEnd;
                        do {
                            tokEnd = wfind(cur, end, '|');
                            *tokEnd = 0;
                            if (tokEnd != cur) {
                                uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                vs->insert(h);
                                cur = tokEnd + 1;
                            }
                        } while (tokEnd != end && cur != end);
                    }
                }
            }
            uint32_t* p = set->mb;
            uint32_t* pe = set->me;
            for (; p != pe; p++) {
                Feature f;
                f.id = 0x4ebfebd;
                f.value = *p;
                fv->add(f, (*weights)[it - first]);
            }
        }
    }
    return result;
}

// @ 0x0056bd30
bool cRigBlockTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
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
                WStr n37;
                if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                    wchar_t* owner = n37.mpBegin;
                    wchar_t* buf = owner;
                    wchar_t* n6 = n37.mpEnd;
                    do {
                        buf = wfind(owner, n6, '|');
                        *buf = 0;
                        if (buf != owner) {
                            uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                            Feature nSize;
                            nSize.id = 0x4ebfebd;
                            nSize.value = n28;
                            WStrSrc val;
                            ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                            val.value = (*weights)[t32 - begin];
                            ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                            owner = buf + 1;
                        }
                    } while (buf != n6 && owner != n6);
                }
            }
        }
    }
    return p30;
}

// ---------------------------------------------------------------- cTextureTag
struct TexHash {                         // eastl::vector_map<uint, vector_set<uint>> at tag+8
    struct Entry { uint32_t first; VSet second; Entry(uint32_t k, const VSet& v) : first(k), second(v) {} };
    struct R { uint32_t* it; bool ok; R() { it = 0; ok = false; } };
    R insert(const Entry& e);            // @ 0x0056e4d0
};

struct cTextureTag {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual const wchar_t* GetName();                                               // 0x18
    char pad[4];
    TexHash mTable;                                                                 // +8
    bool ExtractTraits(Creature* c, float** weights, cFeatureVector* fv);           // @ 0x0056bfa0
    bool DescribeTraits(Creature* c, float** weights, cFeatureVector* fv);          // @ 0x0056c2d0
};

// @ 0x0056bfa0
bool cTextureTag::ExtractTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool result = false;
    if (c) {
        result = true;
        Block* first = c->mpBegin;
        Block* it = first;
        Block* last = c->mpEnd;
        for (; it != last && result; it++) {
            TextureBlock* blk = (TextureBlock*)it;
            uint32_t n = blk->mnKeys;
            for (uint32_t i = 0; i < n; i++) {
                TexHash::R r;
                {
                    VSet tmp;
                    uint32_t key = blk->mKeys[i];
                    TexHash::Entry ent(key, tmp);
                    r = mTable.insert(ent);
                }
                VSet* set = (VSet*)((char*)r.it + 4);
                if (r.ok) {
                    PListRefCall pl;
                    bool ok = SP::PropertyManager()->GetPropertyList(blk->mKeys[i], gTextureGroup, pl.AsPointer());
                    if (ok) {
                        WStr s;
                        if (SP::GetPropertyAsString16(pl.get(), 0x4ebb27e, &s)) {
                            wchar_t* cur = s.mpBegin;
                            wchar_t* tokEnd = cur;
                            wchar_t* end = s.mpEnd;
                            do {
                                tokEnd = wfind(cur, end, '|');
                                *tokEnd = 0;
                                if (tokEnd != cur) {
                                    uint32_t h = FNV1_String16(cur, 0x811c9dc5, 1);
                                    set->insert(h);
                                    cur = tokEnd + 1;
                                }
                            } while (tokEnd != end && cur != end);
                        }
                    }
                }
                BlockSet* bs = (BlockSet*)set;
                uint32_t* p = bs->mb;
                uint32_t* pe = bs->me;
                for (; p != pe; p++) {
                    Feature f;
                    f.id = 0x5833344;
                    f.value = *p;
                    fv->add(f, (*weights)[it - first]);
                }
            }
        }
    }
    return result;
}

// @ 0x0056c2d0
bool cTextureTag::DescribeTraits(Creature* c, float** weights, cFeatureVector* fv)
{
    bool p30 = false;
    if (c) {
        p30 = true;
        Block* begin = c->mpBegin;
        Block* t32 = begin;
        Block* n10 = c->mpEnd;
        for (; t32 != n10 && p30; t32++) {
            TextureBlock* n31 = (TextureBlock*)t32;
            uint32_t p4 = n31->mnKeys;
            for (uint32_t v1 = 0; v1 < p4; v1++) {
                PListRefInline t25;
                bool p32 = SP::PropertyManager()->GetPropertyList(n31->mKeys[v1], gTextureGroup, t25.AsPointer());
                if (p32) {
                    WStr n37;
                    if (SP::GetPropertyAsString16(t25.get(), 0x4ebb27e, &n37)) {
                        wchar_t* owner = n37.mpBegin;
                        wchar_t* buf = owner;
                        wchar_t* n6 = n37.mpEnd;
                        do {
                            buf = wfind(owner, n6, '|');
                            *buf = 0;
                            if (buf != owner) {
                                uint32_t n28 = FNV1_String16(owner, 0x811c9dc5, 1);
                                Feature nSize;
                                nSize.id = 0x5833344;
                                nSize.value = n28;
                                WStrSrc val;
                                ScratchSlots<1>();
                            WStr_Format(&val.str, L"(%ls) %ls", GetName(), owner);
                                val.value = (*weights)[t32 - begin];
                                ScratchSlots<25>();
                            fv->addDescribed(nSize, val);
                                owner = buf + 1;
                            }
                        } while (buf != n6 && owner != n6);
                    }
                }
            }
        }
    }
    return p30;
}
