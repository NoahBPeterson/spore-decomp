// w1g1 slice s004ea310 -- editor validity key writer + flag helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

struct FlagWord {
    unsigned int a : 8;
    unsigned int b : 8;
    unsigned int c : 8;
    unsigned int d : 6;
    unsigned int e : 2;
};
struct DeclareParam { int key; int a; int b; };
void operator delete[](void* p);
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Alloc { Alloc() {} };
struct ResourceKey {
    uint32_t instance, type, group;
    ResourceKey() : instance(0), type(0), group(0) {}
};
// eastl::VectorBase<ResourceKey, sp_vector_allocator>: the destructor is out of line (0x005156b0).
struct VectorBase {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator;
    ~VectorBase()
    {
        if (mpBegin) {
            unsigned n = (mpCapacity - mpBegin) * sizeof(ResourceKey);
            ResourceKey* p = mpBegin;
            if (((int*)p)[-1] != 0) {
                ResourceKey* q = p;
                operator delete[](q);
            }
        }
    }
};
// "VSet": the 12-byte-key vector the validity collectors fill (ctor 0x00540470 is out of line).
struct VSet : VectorBase {
    uint32_t mPadding;
    VSet(const Alloc& a = Alloc());   // 0x00540470
    ~VSet() { for (ResourceKey* p = mpBegin; p < mpEnd; ++p) {} }
    void push_back(const DeclareParam& v);
    ResourceKey* begin() { ResourceKey* it = mpBegin; return it; }
    int size() { return mpEnd - mpBegin; }
    ResourceKey* data() { return mpBegin; }
    ResourceKey* end() { ResourceKey* it = mpEnd; return it; }
    ResourceKey* erase(ResourceKey* first, ResourceKey* last);   // 0x0050f740
};
struct Iface { virtual void v0(); virtual void Release(); }; // Release at +4
struct PaletteMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetConfig(int cfg, int key, int* out); // +0x2c
    virtual void v12();                                 // +0x30
    virtual void StoreProperties(void* list, int instance, uint32_t group); // +0x34
};

int GetConfigFromModelType(int id);      // 0x00432f10
void* PropertyManager();                 // 0x0067de30
bool GetPropertyAsKey(void* holder, int key, void* out);   // 0x006a1250
extern int g_15daa00;

// ===========================================================================
// @ 0x004ea720  (MATCH)
// Packs a model type + paint flag byte into the validity flag word.
// ===========================================================================
FlagWord FUN_004ea720(int p1, int p2)
{
    FlagWord f = {0};
    f.e = 1;
    f.c = p1;
    f.b = p2;
    return f;
}

// ===========================================================================
// @ 0x004ea780  (complete; not byte-exact)
// Recursively remaps a model-type id through the paint-key chain, then appends
// the tag property of the resulting config to `out`.  (PDB candidate:
// SP::EditorValidity::WriteKeysToFile.)
// ===========================================================================
void FUN_004ea780(int id, int tag, VSet* out, int param4)
{
    int v22;
    int v14;
    int v3, v1, p20;
    int idx;
    int t33;
    int t28, n36;
    void* n32;
    switch (id) {
    case 0x4178b8e8: FUN_004ea780(0x65672ade, tag, out, param4); break;
    case 0x65672ade: FUN_004ea780(0xccc35c46, tag, out, param4); break;
    case 0xccc35c46: FUN_004ea780(0x372e2c04, tag, out, param4); break;
    case 0x372e2c04: FUN_004ea780(0x9ea3031a, tag, out, param4); break;
    }
    if (tag == 0x7a926123 && id == 0x9ea3031a && param4 != 0x5bf8f774)
        FUN_004ea780(0xdfad9f51, tag, out, param4);
    v14 = 0;
    v22 = GetConfigFromModelType(id);
    if (param4 != 0)
        v22 = param4;
    n32 = PropertyManager();
    if (v14)
        ((Iface*)v14)->Release();
    ((PaletteMgr*)n32)->GetConfig(v22, g_15daa00, &v14);
    if (v14) {
        p20 = 0;
        v1 = 0;
        v3 = 0;
        t33 = v14;
        if (GetPropertyAsKey((void*)t33, tag, &p20))
            out->push_back(*(DeclareParam*)&p20);
    }
    if (v14)
        ((Iface*)v14)->Release();
}

// ===========================================================================
// @ 0x004ea310  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004ea310(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

struct Variant {
    uint32_t mData[4];
    unsigned short mnFlags;
    unsigned short mnType;
    // Key-array property (type 0x20), by reference/copy depending on `byCopy`.
    __forceinline Variant(const ResourceKey* data, unsigned count, unsigned short base = 0x80, bool byCopy = true)
        : mnFlags(0), mnType(0)
    {
        if (byCopy)
            Set(0x20, base | 0x10 | 8, data, sizeof(ResourceKey), count);
        else
            Set(0x20, base | 0x20, data, sizeof(ResourceKey), count);
    }
    ~Variant() { if (mnFlags & 4) Destruct(false); }
    void Set(unsigned short type, int flags, const void* data, unsigned size, unsigned count);   // 0x0093dd80
    void Destruct(bool b);   // 0x0093db80
};

struct cPropertyList {
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void AddProperty(uint32_t id, const Variant* v);   // +0x14
    char pad[0x38 - 4];
    cPropertyList();           // Editor::cPropertyList::cPropertyList, 0x006a1c40
};

struct PropList { virtual void AddRef(); virtual void Release(); };   // the config property list (slot 4 = Release)

struct PropListRef {
    PropList* mpObject;
    PropListRef() : mpObject(0) {}
    ~PropListRef() { if (mpObject) mpObject->Release(); }
    PropList** AsPPVoidParam();   // 0x0041d870
    PropList** operator&() { return AsPPVoidParam(); }
};

struct ListRef {
    cPropertyList* mpObject;
    ListRef(cPropertyList* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ListRef() { if (mpObject) mpObject->Release(); }
    cPropertyList* get() { return mpObject; }
    cPropertyList* operator->() { return mpObject; }
};

struct ResMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Write(cPropertyList* list, int a, int area, int b, int c);   // +0x20
};
ResMgr* GetResourceMgr();                       // 0x0067dcd0
int GetSaveArea(int id);                        // 0x006b1f90 (cdecl)
void* operator new(uint32_t size, const char* tag, int, int, int, int);   // 0x00f473a0

void FUN_004e9fc0(const ResourceKey* key, VSet* out, int kind);   // 0x004e9fc0
void FUN_004ea190(int id, VSet* out, int flag);                    // 0x004ea190
void AddSpecialPaints(int id, VSet* out, int flag);                // 0x004ea310
namespace eastl {
void sort(ResourceKey* first, ResourceKey* last);                  // 0x004f6b70
ResourceKey* unique(ResourceKey* first, ResourceKey* last);        // 0x004f6830
}

static inline uint32_t MakeFlags(unsigned a, unsigned b, unsigned c)
{
    FlagWord f = {0};
    f.e = 1;
    f.c = c;
    f.b = b;
    f.a = a;
    return *(uint32_t*)&f;
}

// ===========================================================================
// @ 0x004ea920  (MATCH)
// Builds the two validity key lists for a model type (the "paint" list from the 0xf5cbe065 key and the
// "special paint" list from the 0x7a926123 key), sorts and dedups both, then writes them as two
// Editor::cPropertyList key-array properties (property 0x53878d0), each stored under its own flag word.
// (PDB candidate: SP::EditorValidity::DumpPaletteInfo.)
//
// Local names are chosen only to reproduce the /Od stack-slot order (cl orders a scope's locals by a hash of
// their names).  Roles: d = paint keys, next = their completed/sorted copy, size = special-paint keys,
// n4 = their sorted copy, src = config property list holder, other = config id, t15/buf = the two 12-byte keys
// read from the config, v39/p29 = the two new property lists, v11/pos = their key-array properties,
// result/n8 = the two flag words, p19 = instance id, alloc = property id 0x53878d0.
// ScratchSlots<4>() after each erase() is the reserved frame of the out-of-line vector::erase.
// ===========================================================================
void FUN_004ea920(int modelType, int instance, int param3)
{
    VSet d;
    FUN_004ea780(modelType, 0xf5cbe065, &d, param3);
    VSet next;
    for (unsigned i = 0; i < (unsigned)(d.mpEnd - d.mpBegin); ++i)
        FUN_004e9fc0(&d.mpBegin[i], &next, 0);
    FUN_004ea190(modelType, &next, param3);
    eastl::sort(next.begin(), next.end());
    next.erase(eastl::unique(next.begin(), next.end()), next.end());
    ScratchSlots<4>();

    VSet size;
    FUN_004ea780(modelType, 0x7a926123, &size, param3);
    if (modelType == 0x7d433fad || modelType == (int)0x8f963dcb || modelType == 0x441cd3e6 ||
        modelType == (int)0xf670aa43 || modelType == 0x2a5147a9 || modelType == 0x1a4e0708 ||
        modelType == (int)0x9ad7d4aa || modelType == 0x1f2a25b6 || modelType == 0x449c040f ||
        modelType == (int)0xbc1041e6 || modelType == (int)0xc15695da || modelType == 0x2090a11b ||
        modelType == (int)0x98e03c0d || modelType == (int)0xc0b74287)
        FUN_004ea780(0x99e92f05, 0x7a926123, &size, param3);
    if (modelType == (int)0x99e92f05 || modelType == 0x4e3f7777 || modelType == (int)0xbdd15f3d ||
        modelType == 0x47c10953 || modelType == 0x72c49181)
        FUN_004ea780(0x7d433fad, 0x7a926123, &size, param3);
    if (param3 == (int)0xe46c381e)
        FUN_004ea780(0x9ea3031a, 0x7a926123, &size, 0);

    VSet n4;
    for (unsigned it = 0, len = size.mpEnd - size.mpBegin; it < len; ++it)
        FUN_004e9fc0(&size.mpBegin[it], &n4, 1);
    AddSpecialPaints(modelType, &n4, param3);
    eastl::sort(n4.begin(), n4.end());
    n4.erase(eastl::unique(n4.begin(), n4.end()), n4.end());
    ScratchSlots<4>();

    PropListRef src;
    int other = GetConfigFromModelType(modelType);
    if (param3 != 0)
        other = param3;
    ((PaletteMgr*)PropertyManager())->GetConfig(other, g_15daa00, (int*)&src);
    ResourceKey t15;
    if (src.mpObject)
        GetPropertyAsKey(src.mpObject, 0xf5cbe065, &t15);
    ResourceKey buf;
    if (src.mpObject)
        GetPropertyAsKey(src.mpObject, 0x7a926123, &buf);
    const uint32_t alloc = 0x53878d0;

    ListRef v39(new ("Editor", 0, 0, 0, 0) cPropertyList());
    Variant v11(next.data(), next.size());
    v39->AddProperty(alloc, &v11);
    ListRef p29(new ("Editor", 0, 0, 0, 0) cPropertyList());
    Variant pos(n4.data(), n4.size());
    p29->AddProperty(alloc, &pos);

    uint32_t result = MakeFlags(t15.instance, 0x7b, 0x6b);
    uint32_t n8 = MakeFlags(buf.instance, 0x7b, 0x6b);
    int p19 = instance;
    ((PaletteMgr*)PropertyManager())->StoreProperties(v39.mpObject, p19, result);
    ((PaletteMgr*)PropertyManager())->StoreProperties(p29.mpObject, p19, n8);
    GetResourceMgr()->Write(v39.get(), 0, GetSaveArea(0x11ac19e), 0, 0);
    GetResourceMgr()->Write(p29.get(), 0, GetSaveArea(0x11ac19e), 0, 0);
}
