// Module 0x0040FE00: an editor input handler that classifies a message target against three
// registered object ids, reports it to the UI and plays a response. Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

struct ResourceKeyPair { uint32_t a, b; };

struct AtomicRefCounted {
    void* vftable;
    uint32_t mField4;
    volatile long mnRefCount;
    int Release();      // 0x00402420
};

struct SimplePtr {      // smart pointer to an AtomicRefCounted
    AtomicRefCounted* mpObject;
    SimplePtr() : mpObject(0) {}
    ~SimplePtr() {
        if (mpObject)
            mpObject->Release();
    }
    AtomicRefCounted** GetAddressForWrite() {
        if (mpObject) {
            AtomicRefCounted* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

struct ObjectHolder {
    AtomicRefCounted* mpObject;
    uint32_t mField4;
    uint32_t mField8;
};

// Editor-wide registry (singleton at 0x0067dd40)
struct IEditorRegistry {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29(); virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34(); virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39(); virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43(); virtual void r44();
    virtual void GetPartKey(ResourceKeyPair* out);      // slot 45 (+0xb4)
    virtual void GetPaintKey(ResourceKeyPair* out);     // slot 46 (+0xb8)
    virtual void GetModelKey(ResourceKeyPair* out);     // slot 47 (+0xbc)
    virtual void r48(); virtual void r49(); virtual void r50(); virtual void r51(); virtual void r52(); virtual void r53(); virtual void r54(); virtual void r55(); virtual void r56(); virtual void r57(); virtual void r58();
    virtual void GetObject(int which, ObjectHolder* out);   // slot 59 (+0xec)
};

// Key resolver (singleton at 0x0067dda0)
struct IKeyResolver {
    virtual void k0(); virtual void k1(); virtual void k2(); virtual void k3(); virtual void k4(); virtual void k5(); virtual void k6();
    virtual uint32_t Resolve(uint32_t a, uint32_t b);   // slot 7 (+0x1c)
};

// Action sink (singleton at 0x0067dd60)
struct IActionSink {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void SetTarget(AtomicRefCounted* obj, int flag);    // slot 21 (+0x54)
    virtual void s22();
    virtual void Perform(uint32_t id, int a, int b, int c);     // slot 23 (+0x5c)
};

// Notifier (singleton at 0x0067dcc0)
struct INotifier {
    virtual void n0(); virtual void n1(); virtual void n2(); virtual void n3(); virtual void n4();
    virtual void Notify(uint32_t id, int a, int b);     // slot 5 (+0x14)
};

struct IPropertyEntry;
struct IPropertyMap {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool Find(uint32_t key, IPropertyEntry** ppEntry);   // slot 9 (+0x24)
};

struct IPropertyEntry {
    uint8_t pad[0x12];
    uint16_t mType;
    uint32_t* GetValue();    // 0x0041e990
};

// @ 0x00410370
bool TryGetUIntProperty(IPropertyMap* map, uint32_t key, uint32_t* out)
{
    if (map) {
        uint32_t dead[1];
        IPropertyEntry* entry;
        if (map->Find(key, &entry) && entry->mType == 9) {
            *out = *entry->GetValue();
            return true;
        }
    }
    return false;
}

// Reference-counted editor object with a secondary interface at +0xc.
struct RefCountedBase {
    virtual int AddRef();
    virtual int Release();      // slot 1 (+4)
    uint32_t mField4;
    uint32_t mField8;
};
struct EditorSink {
    virtual void v0();
};
struct EditorOwner : RefCountedBase, EditorSink {};

// eastl::intrusive_ptr (virtual AddRef/Release)
template <class T> struct intrusive_ptr {
    T* mpObject;

    intrusive_ptr() : mpObject(0) {}
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr& operator=(T* pNew)
    {
        if (mpObject != pNew) {
            T* const pTemp = mpObject;
            if (pNew)
                pNew->AddRef();
            mpObject = pNew;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct IdFlags {
    uint32_t state : 8;
    uint32_t kind : 8;
    uint32_t rest : 16;
    void SetKind(int v) { kind = v; }
    void SetState(int v) { state = v; }
};

struct EditorMessage {
    uint32_t pad[2];
    struct { uint32_t a, b; } args[2];
    uint32_t GetArg(int idx) { return args[idx].a; }
};


struct ILogger {
    bool IsEnabled(uint32_t id);        // 0x006a25a0
};
extern ILogger* g_pLogger;              // 0x015fd918
inline ILogger* GetLogger() { ILogger* l = g_pLogger; return l; }

struct ResourceRef {
    uint32_t instance;
    uint32_t type;
    IdFlags flags;
};

inline void InitRef(ResourceRef* r, uint64_t inst, uint32_t type, const IdFlags& group)
{
    r->instance = (uint32_t)inst;
    r->type = type;
    r->flags = group;
}

IEditorRegistry* GetEditorRegistry();   // 0x0067dd40
IKeyResolver* GetKeyResolver();         // 0x0067dda0
IActionSink* GetActionSink();           // 0x0067dd60
INotifier* GetNotifier();               // 0x0067dcc0
void FindObject(EditorSink* base, uint32_t id, IdFlags flags, AtomicRefCounted** out);    // 0x007aff00
uint32_t LookupString(uint32_t hash);     // 0x006b1f90
void LogResource(EditorSink* base, ResourceRef* ref, uint32_t str, int flag);   // 0x007b10d0

struct EditorHandler {
    uint8_t pad0[0x228];
    uint32_t mTargetId;                 // +0x228
    uint32_t mPad22c;
    IdFlags mFlags;                     // +0x230
    uint8_t pad1[0x24c - 0x234];
    IPropertyMap* mpProperties;         // +0x24c
    uint8_t pad2[0x117c - 0x250];
    intrusive_ptr<EditorOwner> mpOwner; // +0x117c

    IPropertyMap* GetProperties()
    {
        return mpProperties;
    }

    IdFlags MakeFlags(int kind, int state)
    {
        uint32_t reserved[3];
        IdFlags result = mFlags;
        result.SetKind(kind);
        result.SetState(state);
        return result;
    }

    bool HandleMessage(EditorMessage* msg);
};

// @ 0x0040fe00
// Local names are not meaningful: at /Od the stack slots of function-scope locals are laid out
// in an order that depends on the identifier names, so these were found by search to reproduce
// the original frame. Roughly: `event` is the message, `hovered` the target object id, `code`
// the mode read from the property map, the *Key/*Holder/*Obj groups are the three registered
// editor object ids, and `mode` (0/1/2) says which one the target matched.
bool EditorHandler::HandleMessage(EditorMessage* msg)
{
    EditorMessage* event = msg;
    uint32_t hovered = event->GetArg(1);
    uint32_t code = 0;
    TryGetUIntProperty(GetProperties(), 0x4c6ba3c, &code);

    ResourceKeyPair keyOne = { 0xffffffff, 0xffffffff };
    ResourceKeyPair toolKey = { 0xffffffff, 0xffffffff };
    ResourceKeyPair categoryKey = { 0xffffffff, 0xffffffff };
    GetEditorRegistry()->GetModelKey(&keyOne);
    uint32_t paintResult = GetKeyResolver()->Resolve(keyOne.a, keyOne.b);
    GetEditorRegistry()->GetPaintKey(&toolKey);
    uint32_t uiAction = GetKeyResolver()->Resolve(toolKey.a, toolKey.b);
    GetEditorRegistry()->GetPartKey(&categoryKey);
    uint32_t value = GetKeyResolver()->Resolve(categoryKey.a, categoryKey.b);

    ObjectHolder editHolder = { 0, 0, 0 };
    ObjectHolder paintHolder = { 0, 0, 0 };
    ObjectHolder modelHolder = { 0, 0, 0 };
    GetEditorRegistry()->GetObject(2, &editHolder);
    GetEditorRegistry()->GetObject(4, &paintHolder);
    GetEditorRegistry()->GetObject(3, &modelHolder);
    AtomicRefCounted* modelObj = editHolder.mpObject;
    AtomicRefCounted* object = paintHolder.mpObject;
    AtomicRefCounted* tool = modelHolder.mpObject;

    uint32_t mode = 0;
    if ((AtomicRefCounted*)hovered == object)
        mode = 1;
    else if ((AtomicRefCounted*)hovered == tool)
        mode = 2;

    IdFlags uiFlags = MakeFlags(0x29, mode);

    SimplePtr obj;
    FindObject(mpOwner.get(), mTargetId, uiFlags, obj.GetAddressForWrite());
    if (obj.mpObject && GetLogger()->IsEnabled(0x26cd3c9)) {
        ResourceRef ref;
        InitRef(&ref, mTargetId, 0x2f4e681c, uiFlags);
        LogResource(mpOwner.get(), &ref, LookupString(0x11ac1ac), 1);
        GetActionSink()->SetTarget(obj.mpObject, 0);
    }
    mpOwner = 0;

    if ((code == 1 || code == 2) && (AtomicRefCounted*)hovered == modelObj) {
        GetActionSink()->Perform(uiAction, 0, 1, 0);
    } else if (code == 2 && (AtomicRefCounted*)hovered == object) {
        GetActionSink()->Perform(value, 0, 1, 0);
    } else if ((code == 0 && (AtomicRefCounted*)hovered == modelObj) ||
               (code == 1 && (AtomicRefCounted*)hovered == object) ||
               (code == 2 && (AtomicRefCounted*)hovered == tool)) {
        GetNotifier()->Notify(0x52deb9e, 0, 0);
    }
    return true;
}
