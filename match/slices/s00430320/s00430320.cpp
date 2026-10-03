// Slice s00430320: creature-editor ability/graphics helpers: a destructor for an editor
// resource object (two bases at +0 and +4), a property-driven helper that builds
// "Graphics" material objects, and a tiny ability ctor / scalar deleting dtor.
//
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no EH frames).
#include "types.h"

extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

void EASTL_allocator_deallocate(void* p);                                       // 0x00F47380
void* operator new(unsigned int, const char*, int, int, int, int);              // 0x00F473A0

// ---------------------------------------------------------------------------
// Basic ref-counted interface
// ---------------------------------------------------------------------------
struct Object {
    virtual int AddRef();
    virtual int Release();
};

struct PropertyListValue {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t type;   // +0x12 (0xd = float)
    float* GetFloat();   // 0x0041EA70
};

struct PropertyList : Object {
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual bool GetProperty(uint32_t id, PropertyListValue** dst);   // +0x24
};

struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** OutImpl();    // 0x0041D870
    PropertyList** Out() { return OutImpl(); }
    PropertyList** AsPointer() {
        if (mpObject) {
            PropertyList* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

// Resource group id: byte 1 = kind, byte 0 = slot.
struct GroupKey {
    uint32_t slot : 8;
    uint32_t kind : 8;
    uint32_t rest : 16;
};
inline GroupKey MakeGroupKey(GroupKey base, uint8_t kind, uint8_t slot)
{
    base.kind = kind;
    base.slot = slot;
    return base;
}

struct PropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** dst);   // +0x2C
    static PropManager* GetImpl();   // 0x0067DE30
};

bool TryGetUIntProperty(PropertyList* list, uint32_t propId, int* out);   // 0x00410370

struct TextureHandle;
struct TextureManager {   // 0x0067DD60
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual TextureHandle* GetTexture(uint32_t instanceID, uint32_t groupID, int flags);   // +0x20
    static TextureManager* GetImpl();
};
void* GetUnusedManagerA();   // 0x0067DDA0
void* GetUnusedManagerB();   // 0x0067DD40

// ---------------------------------------------------------------------------
// Material objects
// ---------------------------------------------------------------------------
struct Material {
    uint32_t pad[28];
    Material();   // 0x0040D010 (size 0x70)
    void SetTexture(int stage, TextureHandle* tex);   // 0x0077CB10
    void SetFilterA(int stage, int mode);             // 0x00777A60
    void SetFilterB(int stage, int mode);             // 0x00777A80
    void SetFilterC(int stage, int mode);             // 0x00777AA0
};

struct MaterialParams {
    uint32_t pad[3];
    uint8_t flag;      // +0x0C
    float a;           // +0x10
    float b;           // +0x14
    float c;           // +0x18
    MaterialParams();  // 0x00432CF0 (size 0x20)
};

struct MaterialList {
    uint32_t pad[2];
    void** mpBegin;    // +8
    void resize(unsigned n);                // 0x004CD3C0
    void push_back(Material* const& m);     // 0x00454860
};

// @ 0x00430450
void BuildMaterials(MaterialList* pList, uint32_t instanceID, GroupKey baseKey)
{
    extern uint32_t g_Unused015FD918;
    uint32_t savedGlobal = g_Unused015FD918;
    int variant = 0;
    PropertyListPtr pProps;
    bool ok;
    if (PropManager::GetImpl()->GetPropertyList(instanceID, *(uint32_t*)&baseKey, pProps.AsPointer())) {
        ok = TryGetUIntProperty(pProps.mpObject, 0x4c6ba3c, &variant);
    }
    GroupKey key0 = MakeGroupKey(baseKey, 0x29, 0);
    GroupKey key1 = MakeGroupKey(baseKey, 0x29, 1);
    GroupKey key2 = MakeGroupKey(baseKey, 0x29, 2);
    TextureManager* pTexMgr = TextureManager::GetImpl();
    void* unusedA = GetUnusedManagerA();
    void* unusedB = GetUnusedManagerB();
    Material* pMaterial = new ("Graphics", 0, 0, 0, 0) Material;
    TextureHandle* tex0 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key0, 0);
    pMaterial->SetTexture(0, tex0);
    pMaterial->SetFilterA(0, 1);
    pMaterial->SetFilterA(0, 1);
    pMaterial->SetFilterB(0, 2);
    pMaterial->SetFilterC(0, 2);
    if (variant == 1) {
        TextureHandle* tex1 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key1, 0);
        pMaterial->SetTexture(1, tex1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterB(1, 2);
        pMaterial->SetFilterC(1, 2);
        MaterialParams* pParams = new ("Graphics", 0, 0, 0, 0) MaterialParams;
        pParams->flag = 0;
        pParams->a = 60.0f;
        pParams->b = 1.0f;
        pParams->c = 1.0f;
        pList->resize(2);
        pList->mpBegin[0] = pMaterial;
        pList->mpBegin[1] = pParams;
    } else if (variant == 2) {
        TextureHandle* tex1 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key1, 0);
        TextureHandle* tex2 = pTexMgr->GetTexture(instanceID, *(uint32_t*)&key2, 0);
        pMaterial->SetTexture(1, tex1);
        pMaterial->SetTexture(2, tex2);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterA(1, 1);
        pMaterial->SetFilterB(1, 2);
        pMaterial->SetFilterC(1, 2);
        pMaterial->SetFilterA(2, 1);
        pMaterial->SetFilterA(2, 1);
        pMaterial->SetFilterB(2, 2);
        pMaterial->SetFilterC(2, 2);
        MaterialParams* pParams = new ("Graphics", 0, 0, 0, 0) MaterialParams;
        pParams->flag = 1;
        pParams->a = 60.0f;
        pParams->b = 1.0f;
        pParams->c = 1.0f;
        pList->resize(2);
        pList->mpBegin[0] = pMaterial;
        pList->mpBegin[1] = pParams;
    } else {
        Material* tmp = pMaterial;
        pList->push_back(tmp);
    }
}

// ---------------------------------------------------------------------------
// Editor resource destructor
// ---------------------------------------------------------------------------
struct EditorResourceBase {
    virtual ~EditorResourceBase() {}
};
struct AbilityBase {
    virtual ~AbilityBase() {}
};

struct Alloc { const char* name; uint32_t flags; };
struct RefVector {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap; Alloc a;
    RefVector();
    ~RefVector() { int u0, u1, u2; Destroy(); }
    void Destroy();   // 0x0041EB80
};
struct SubObject { uint32_t d[6]; SubObject(); ~SubObject() { int u0, u1, u2, u3; Destroy(); } void Destroy(); };       // dtor 0x00564580 (size 0x18)
struct Elem24Vec { uint32_t d[5]; Elem24Vec(); ~Elem24Vec() { int u0, u1, u2; Destroy(); } void Destroy(); };       // dtor 0x00421230 (size 0x14)

struct Elem56 { uint32_t d[14]; };
struct Elem56VecBase {
    Elem56* mpBegin; Elem56* mpEnd; Elem56* mpCap; Alloc a;
    ~Elem56VecBase();   // 0x00427440
};
struct Elem56Vec : Elem56VecBase {
    ~Elem56Vec() {
        Elem56* p;
        int d0, d1, d2;
        for (p = mpBegin; p < mpEnd; ++p)
            p->~Elem56();
    }
};

struct DebugLog {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14();
    virtual void Notify(uint32_t id, int a, int b, int c);   // +0x18
    static DebugLog* Get();   // 0x0067DCC0
};

struct CreatureEditorResource : EditorResourceBase, AbilityBase {
    uint32_t pad08;
    RefVector mA;            // +0x0C
    uint32_t pad20[3];
    RefVector mB;            // +0x2C
    SubObject mSub;          // +0x40
    Elem24Vec mVec24;        // +0x58
    Elem56Vec mVec56;        // +0x6C
    uint8_t mQuiet;          // +0x80
    ~CreatureEditorResource();
};

// @ 0x00430320
CreatureEditorResource::~CreatureEditorResource()
{
    if (!mQuiet)
        DebugLog::Get()->Notify(0x355dad8, 0, 0, 0);
}

// ---------------------------------------------------------------------------
// Event helper
// ---------------------------------------------------------------------------
struct ResKey2 { uint32_t a, b; ResKey2() : a(0xffffffff), b(0xffffffff) {} };

struct KeyProvider {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5C();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6C();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7C();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8C();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9C();
    virtual void vA0(); virtual void vA4(); virtual void vA8(); virtual void vAC();
    virtual void vB0(); virtual void vB4(); virtual void vB8();
    virtual void FillKey(ResKey2* key);   // +0xBC
    static KeyProvider* Get();   // 0x0067DD40
};

struct Notifier {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual void Post(ResKey2* key, uint32_t a, uint32_t b, uint32_t evt, uint32_t c, uint8_t d);   // +0x3C
    static Notifier* Get();   // 0x0067DDB0
};

// @ 0x004303E0
void PostEditorEvent(uint32_t a, uint32_t b, uint32_t c, uint8_t d)
{
    Notifier* pNotifier = Notifier::Get();
    ResKey2 key;
    KeyProvider::Get()->FillKey(&key);
    pNotifier->Post(&key, b, a, 0x245801e, c, d);
}

// ---------------------------------------------------------------------------
// Small ability (vtable 0x013EBC60 over the 0x013EF094 base) and its subclass
// ---------------------------------------------------------------------------
struct RefCountedAbility {
    RefCountedAbility() : mRefCount(0) {}
    virtual ~RefCountedAbility() {}
    int mRefCount;   // +4
};

struct SimpleAbility : RefCountedAbility {
    SimpleAbility();
    int mKind;       // +8
};

// @ 0x00430C20
SimpleAbility::SimpleAbility() : mKind(4) {}

struct EmptyTag { EmptyTag() {} };

struct RcObject {
    uint32_t vtbl;
    int mRefCount;     // +4
    int AddRef() { return mRefCount++ + 1; }
    void Release();    // 0x00453540
};

struct RcPtr {
    RcObject* mp;
    RcPtr(RcObject* p) : mp(p) { if (mp) mp->AddRef(); }
    ~RcPtr() { if (mp) mp->Release(); }
};

struct OwnedVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap; Alloc a;
    OwnedVec(const EmptyTag& = EmptyTag());   // 0x00540470
    ~OwnedVec();                     // 0x00432D60
    void push_back(const RcPtr& p); // 0x004E0E80
};

// @ 0x00430C60 is VecAbility's compiler-generated scalar deleting destructor.
struct VecAbility : SimpleAbility {
    OwnedVec mVec;    // +0x0C
    static void operator delete(void* p) { int u0, u1, u2, u3, u4, u5, u6, u7; EASTL_allocator_deallocate(p); }
};

// ---------------------------------------------------------------------------
// 0x00430900: builds a VecAbility for a creature part from properties
// ---------------------------------------------------------------------------
struct Item8 { uint32_t a, b; };
struct ItemVec {            // 20 bytes
    Item8* mpBegin; Item8* mpEnd; Item8* mpCap; Alloc a;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct ItemVecVec {
    ItemVec* mpBegin; ItemVec* mpEnd; ItemVec* mpCap; Alloc a;
    ItemVecVec(const EmptyTag&);   // 0x00540470
    ~ItemVecVec();                 // 0x00432DE0
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct HandleRef { uint32_t v; };
struct HandleVec {
    HandleRef* mpBegin; HandleRef* mpEnd; HandleRef* mpCap; Alloc a;
    HandleVec(const EmptyTag& = EmptyTag());    // 0x00540470
    ~HandleVec();                  // 0x0041EB80
    void push_back(const Item8& v);   // 0x0041EF20
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    HandleRef& back() { return mpBegin[size() - 1]; }
};
void RegisterHandle(HandleRef h, uint32_t id);   // 0x00756280 (cdecl)

struct AbilityBuilder {
    void Collect(uint32_t instanceID, ItemVecVec& out);   // 0x007A0EE0
};
RcObject* CreateRcObject(int a, int b, float* data, int size);   // 0x0079AB90 (cdecl)
void FinishBuild(void* out, HandleVec* refs, uint32_t a, uint32_t b, uint32_t c, int, int, int, int,
                 uint32_t d, int, uint32_t e);   // 0x007573A0 (cdecl)

// @ 0x00430900
void BuildAbility(void* pOut, uint32_t instanceID, uint32_t propInstance, uint32_t propGroup,
                  uint32_t p5, uint32_t p6, uint32_t p7, uint32_t p8)
{
    float radius = 25.0f;
    PropertyListPtr pProps;
    if (PropManager::GetImpl()->GetPropertyList(propInstance, propGroup, pProps.Out())) {
        PropertyList* pList = pProps.mpObject;
        PropertyListValue* pValue;
        if (pList && pList->GetProperty(0xf9efb9, &pValue) && pValue->type == 0xd)
            radius = *pValue->GetFloat();
    }
    float r = radius - radius / 5.0f;
    HandleVec refs((EmptyTag()));
    float data[4];
    data[0] = 0.0f;
    data[1] = 2.0f;
    data[2] = 1.2f * r;
    data[3] = r * r;
    VecAbility* pAbility = new ("App", 0, 0, 0, 0) VecAbility;
    {
        RcPtr rc(CreateRcObject(0, 1, data, 4));
        pAbility->mVec.push_back(rc);
    }
    ItemVecVec items((EmptyTag()));
    ((AbilityBuilder*)pAbility)->Collect(instanceID, items);
    for (unsigned i = 0, n = (unsigned)items.size(); i < n; ++i) {
        for (unsigned j = 0, m = (unsigned)items.mpBegin[i].size(); j < m; ++j) {
            refs.push_back(items.mpBegin[i].mpBegin[j]);
            RegisterHandle(refs.back(), 0x407dfddb);
        }
    }
    FinishBuild(pOut, &refs, propInstance, p5, p6, 0, 0, 0, 0, p8, 0, p7);
}
