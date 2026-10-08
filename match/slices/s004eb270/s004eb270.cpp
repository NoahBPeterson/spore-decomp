// w1g1 slice s004eb270 -- editor validity key seeding + record comparison.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct DeclareParam { int key; int a; int b; };
void FUN_004ea920(int, int, int);
extern int g_150ca00[];

// ===========================================================================
// @ 0x004eb930  (MATCH)
// Three-field equality of two declare-param records.
// ===========================================================================
bool FUN_004eb930(const DeclareParam& a, const DeclareParam& b)
{
    int r;
    if (a.key == b.key && a.a == b.a && a.b == b.b)
        r = 1;
    else
        r = 0;
    return *(bool*)&r;
}

// ===========================================================================
// @ 0x004eb980  (MATCH)
// Seeds the validity key table: one entry per registered model type, then two
// special entries.
// ===========================================================================
void FUN_004eb980(void)
{
    int v33 = 1;
    int n40 = 0;
    int len = 0x1b;
    for (; n40 < len; n40++)
        FUN_004ea920(g_150ca00[n40], 1, 0);
    FUN_004ea920(0x9ea3031a, 1, 0x5bf8f774);
    FUN_004ea920(0x9ea3031a, 1, 0xe46c381e);
}

// ===========================================================================
// @ 0x004eb270  SP::EditorValidity::ReadKeysFromFile
// Collects the (key, extra) validity records for one model category: lists every property file in the
// category's group (0x406b7bXX, type 0xb1b104), and for each one appends the entries of its 0x053878d0
// key array (tagged with its 0x1b8716d6 int, default from a global table), then recurses through the
// 0x0769eeee key array, merging results that are not already present.
// ===========================================================================
struct Alloc { Alloc() {} };                                    // empty allocator tag (EASTL allocator)
typedef DeclareParam ResKey;                         // {instanceID, typeID, groupID}

struct Elem16 { DeclareParam k; int extra; };

struct KeyVec {                                      // eastl::vector<ResKey> (12-byte elements)
    ResKey* mpBegin; ResKey* mpEnd; ResKey* mpCap; uint32_t alloc;
    KeyVec(const Alloc&);                            // 0x00540470
    ~KeyVec();                                       // 0x00540520
};

struct VecBase16 { Elem16* mpBegin; Elem16* mpEnd; Elem16* mpCap; uint32_t alloc; ~VecBase16(); };  // 0x00554b10
struct Elem16Vec : VecBase16 {                       // eastl::vector<Elem16, sp_vector_allocator>
    Elem16Vec(const Alloc&);                         // 0x00540470 (same code as KeyVec's)
    ~Elem16Vec() { for (Elem16* p = mpBegin; p < mpEnd; ++p) { } }
    void reserve(uint32_t n);                        // 0x004f6630
    void push_back(const Elem16& v);                 // 0x004fd5e0
};

struct IKeyFilter { virtual ~IKeyFilter() {} virtual bool IsValid(const ResKey& k) = 0; };
struct StandardFileFilter : IKeyFilter {
    uint32_t instanceID, groupID, typeID, groupMask;
    StandardFileFilter(uint32_t i, uint32_t g, uint32_t t, uint32_t m)
        : instanceID(i), groupID(g), typeID(t), groupMask(m) {}
    virtual bool IsValid(const ResKey& k);
};

struct IResMgr {                                     // slot 0x38 = GetRecordKeyList
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d();
    virtual uint32_t GetRecordKeyList(KeyVec& dst, IKeyFilter* filter, void* pDbs);
};
IResMgr* FUN_0067dcd0();                             // GetManager, cdecl

struct Property {
    void* mpData; uint32_t pad4; int mnItemCount; uint32_t padc; unsigned short mnFlags; unsigned short mnType;
    int GetItemCount() { if (mnFlags & 0x30) return mnItemCount; if (mnType) return 1; return 0; }
    void* GetValue() { if (mnFlags & 0x30) return mpData; if (mnType) return this; return 0; }
    int* GetValueInt32();                            // 0x004e41c0
};

struct PropList {                                    // IRefCount + PropertyList vtable
    virtual int AddRef(); virtual int Release();
    virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual bool HasProperty(uint32_t id);                             // 0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result);       // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result);          // 0x24
};
struct PropListPtr {
    PropList* mp;
    PropList* operator->() const { return mp; }
    PropListPtr* AsPPVoid();                         // 0x0041d870 (releases, returns this)
    void** AsPPVoidParam() { return (void**)AsPPVoid(); }
};
struct IPropMgr {                                    // slot 0x2c = GetPropertyList
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, void** pDst);
};
IPropMgr* FUN_0067de30();                            // PropertyManager, cdecl
struct PtrVec { int* At(int i); };                   // 0x007db620
PtrVec* FUN_0067dea0();                              // global table, cdecl

union GroupBits {                                    // 0x40 6b 7b <id>
    struct { uint32_t b0 : 8; uint32_t b1 : 8; uint32_t b2 : 8; uint32_t b3 : 6; uint32_t b4 : 2; } f;
    uint32_t v;
};

static inline uint32_t MakeGroup(uint32_t c2, uint32_t c1, uint32_t c0)
{
    GroupBits g;
    g.v = 0;
    g.f.b4 = 1;
    g.f.b2 = c2;
    g.f.b1 = c1;
    g.f.b0 = c0;
    return g.v;
}

static inline int GetIntProp(PropList* pl, int dflt)
{
    Property* prop;
    int r;
    if (pl && pl->GetProperty(0x1b8716d6, prop))
        r = *prop->GetValueInt32();
    else
        r = dflt;
    return r;
}

static inline bool operator==(const Elem16& a, const Elem16& b)
{
    return FUN_004eb930(a.k, b.k) && a.extra == b.extra;
}

void FUN_004eb270(uint32_t id, Elem16Vec* out)
{
    uint32_t len = MakeGroup(0x6b, 0x7b, id);

    KeyVec v33((Alloc()));
    StandardFileFilter n40(0xffffffff, len, 0xb1b104, 0xffffffff);
    FUN_0067dcd0()->GetRecordKeyList(v33, &n40, 0);

    for (uint32_t i = 0; i < (uint32_t)(v33.mpEnd - v33.mpBegin); ++i) {
        PropListPtr pl;
        pl.mp = 0;
        ResKey* k = &v33.mpBegin[i];
        FUN_0067de30()->GetPropertyList(k->key, k->b, pl.AsPPVoidParam());
        if (pl.mp) {
            const uint32_t kKeysA = 0x53878d0;
            const uint32_t kKeysB = 0x769eeee;
            const uint32_t kExtraId = 0x1b8716d6;
            (void)kExtraId;
            int* pDef = FUN_0067dea0()->At(0);
            int extra = pDef ? *pDef : 1;
            extra = GetIntProp(pl.mp, extra);

            if (pl->HasProperty(kKeysA)) {
                Property* prop = 0;
                pl->GetPropertyAlt(kKeysA, prop);
                out->reserve(prop->GetItemCount());
                int n = prop->GetItemCount();
                for (int j = 0; j < n; ++j) {
                    ResKey* e = (ResKey*)prop->GetValue() + j;
                    Elem16 tmp;
                    tmp.k.key = e->key; tmp.k.a = e->a; tmp.k.b = e->b;
                    tmp.extra = extra;
                    out->push_back(tmp);
                }
            }
            if (pl->HasProperty(kKeysB)) {
                Property* prop = 0;
                pl->GetPropertyAlt(kKeysB, prop);
                out->reserve(prop->GetItemCount());
                int n = prop->GetItemCount();
                for (int j = 0; j < n; ++j) {
                    ResKey* e = (ResKey*)prop->GetValue() + j;
                    uint32_t sub = e->b & 0xff;
                    Elem16Vec more((Alloc()));
                    FUN_004eb270(sub, &more);
                    for (uint32_t m = 0; m < (uint32_t)(more.mpEnd - more.mpBegin); ++m) {
                        const Elem16& cand = more.mpBegin[m];
                        Elem16* it = out->mpBegin;
                        Elem16* last = out->mpEnd;
                        for (; it != last; ++it)
                            if (*it == cand)
                                break;
                        Elem16* found = it;
                        if (found == out->mpEnd)
                            out->push_back(more.mpBegin[m]);
                    }
                }
            }
        }
        if (pl.mp)
            pl.mp->Release();
    }
}

// ===========================================================================
// @ 0x004eba00  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004eba00(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
