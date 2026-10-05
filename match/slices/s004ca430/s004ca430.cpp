// Slice s004ca430: editor object lazy-initialising two refcounted sub-objects and
// applying a property-driven override to a float, then forwarding to a manager
// virtual.  Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
//
// The class identity of the receiver is not recovered from the 2008 PDB (its
// members are an opaque pointer at +0x8 and two AutoRefCount at +0x34/+0x38),
// so a faithful stub layout is used.  Callee targets are masked relocations.
#include "types.h"

#pragma pack(push, 4)

// Reproduces dead /Od stack slots left by inlined helpers.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct RefCounted {
    virtual void Unused(); // vptr at +0x0
    int   mnRefCount;      // +0x4
    int AddRef() {
        // double load, as emitted at /Od for this refcount template
        int n = mnRefCount + 1;
        mnRefCount = mnRefCount + 1;
        return n;
    }
    void Release();        // out of line (masked: 0x00453540)
};

// 0x1d0-byte object (constructor at 0x00507380), no ctor args.
class BigAbility : public RefCounted {
public:
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);
    static void operator delete(void*, size_t);
    BigAbility();
    uint32_t mPad[0x1c8 / 4];      // total size 0x1d0
};

// 0xf8-byte object (constructor at 0x004f85b0), one float ctor argument.
class AbilityData : public RefCounted {
public:
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d);
    static void operator delete(void*, size_t);
    AbilityData(float value);
    uint32_t mPad[0xf0 / 4];       // total size 0xf8
};

template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            ScratchSlots<2>();
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* mpObject;
};

// Interface handed back by the application singleton (0x00401010): the trailing
// virtual is invoked at vtable +0x68.
class IEditorManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();
    virtual void Apply(void* pOwner, float value);   // +0x68
};

// Manager returned by SP::PropertyManager() (0x0067de30); slot +0x2c lookup.
class IPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool Find(uint32_t key, void* pArchive, void** ppOut);   // +0x2c
};

// Object stored into the lookup output; slot +0x24 fetches a property; +0x4 releases.
class IPropertyList {
public:
    virtual void v00();
    virtual void Release();                                          // +0x4
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(uint32_t key, void** ppOut);            // +0x24
};

struct Property;   // opaque; the word at +0x12 is the property type

// 0x0041ea70: returns a pointer to the float payload of a numeric property.
float* GetPropertyAsFloat(Property* p);

// 0x004bb860: maps a resource-key hash to another hash.
uint32_t InitVerbCollection(uint32_t key);

// The receiver: only the offsets used by this method are modelled.
class EditorObject {
public:
    char pad00[8];
    void* mpOwner;                  // +0x8; +0x18 holds a resource key
    char pad0c[0x34 - 0xc];
    AutoRefCount<BigAbility>  mPrimary;   // +0x34
    AutoRefCount<AbilityData> mSecondary; // +0x38

    void Update(float value);
};

// Application singleton (0x00401010).
extern IEditorManager* g_pEditorManager;
extern IPropertyManager* g_pPropertyManager;   // 0x15fd8a8, via SP::PropertyManager()
extern void* g_pArchive;                       // DAT_015d9354

// ---------------------------------------------------------------------------
// @ 0x004CA430
void EditorObject::Update(float value)
{
    if (mPrimary.mpObject == 0) {
        mPrimary = new ("Editor", 0, 0, 0, 0) BigAbility();
    }

    if (mSecondary.mpObject == 0) {
        mSecondary = new ("Editor", 0, 0, 0, 0) AbilityData(0.01f);
    }

    if (value == -1.0f) {
        uint32_t key = 0;
        void* pOwner = mpOwner;
        uint32_t id = InitVerbCollection(*(uint32_t*)((char*)pOwner + 0x18));
        if (id == 0x438f6347)
            key = 0x1c7eca95;
        else if (id == 0x3d97a8e4)
            key = 0x3615a30b;
        else if (id == 0x2b978c46)
            key = 0x465c50ba;

        value = 0.028f;
        if (key != 0) {
            uint32_t propertyId = 0x711306ce;
            IPropertyList* pList = 0;

            IPropertyManager* pMgr = g_pPropertyManager;
            if (pList != 0)
                pList->Release();

            if (pMgr->Find(key, g_pArchive, (void**)&pList)) {
                if (pList != 0) {
                    Property* pProp = 0;
                    if (pList->GetProperty(propertyId, (void**)&pProp)) {
                        if (*(uint16_t*)((char*)pProp + 0x12) == 0xd) {
                            value = *GetPropertyAsFloat(pProp);
                        }
                    }
                    pList->Release();
                }
            }
        }
    }

    IEditorManager* pManager = g_pEditorManager;
    pManager->Apply(this, value);
}
