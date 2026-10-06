// slice s0058e6d0 -- SP::cAppModeEditorBase::Activate (12212 B).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the cString and message locals get no EH frame).
//
// Retail layout of cAppModeEditorBase follows the Spore ModAPI `Editors::cEditor` header (2017 build) far
// more closely than the 2008 dev PDB, so field names below come from ModAPI where it has one.  Every
// offset was confirmed against the disassembly of Activate.
#include "types.h"

typedef unsigned int size_t;

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)
extern "C" void* __cdecl memmove(void* dst, const void* src, size_t n);

// EA allocator new: new("Editor", 0, 0, 0, 0) T(...)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);

// Placeholder virtual slots, used to put the real methods at the right vtable index.
#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)
#define VS16(n) VS4(n##0) VS4(n##1) VS4(n##2) VS4(n##3)
#define VS64(n) VS16(n##a) VS16(n##b) VS16(n##c) VS16(n##d)

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------------------------------------
// EA::AutoRefCount.  The assignment is inlined for most pointee types; a few instantiations were
// emitted out of line (identical-code-folded to one function), declared as specializations below.
template <class T>
class AutoRefCount {
public:
    T* mpObject;

    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }

    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    void reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    AutoRefCount& operator=(const AutoRefCount& x);   // out of line (0x00ac9480 for the paint theme)
    T** AsPPTypeParam();                                // out of line (0x00a16f40): release, return &mpObject

    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// ---------------------------------------------------------------------------------------------
// EASTL pieces (layout-compatible; sp_vector_allocator is 8 bytes in this build).
template <class T>
class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    T& operator[](size_t i) { return mpBegin[i]; }

    T* erase(T* first, T* last)
    {
        memmove(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }

    void resize(size_t n);                       // out of line (0x00585cb0)
    T* DoInsertValue(T* position, const T& value);   // out of line (0x00630b30)

    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    bool empty() const { return mpBegin == mpEnd; }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

// ---------------------------------------------------------------------------------------------
// App properties.
enum PropertyType {
    kPropBool = 1,
    kPropInt32 = 9,
    kPropUInt32 = 10,
    kPropFloat = 13,
    kPropBools = 0x10
};

extern bool g_PropertyDefaultBool;   // 0x015d115d: returned for a property of the wrong type

class Property {
public:
    void* mpData;        // +00 (or the value itself when not an array/pointer property)
    uint32_t field_4;
    uint32_t mnItemCount;   // +08
    uint32_t field_C;
    uint16_t mnFlags;    // +10
    uint16_t mnType;     // +12

    bool* GetBool();            // 0x0041e920
    int* GetInt();              // 0x0041e990
    uint32_t* GetUInt();        // 0x0041ea00
    float* GetFloat();          // 0x0041ea70
    ResourceKey* GetKeyTPTR();  // 0x00454b10 (VariantTypeTraits<ResourceMan::Key>::GetTPTR)

    void* GetDataPtr() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
    size_t GetItemCount() { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    bool* GetValueBool()
    {
        if (mnType == kPropBool || mnType == kPropBools)
            return (bool*)GetDataPtr();
        return &g_PropertyDefaultBool;
    }
};

// ---------------------------------------------------------------------------------------------
// Ref-counted interface with AddRef in slot 0 and Release in slot 1.
class IRefCounted {
public:
    virtual int AddRef();
    virtual int Release();
};

class cMWModel;
class cILayer;
class cMainWinBase;

namespace SP { class cAppModeEditorBase; }

class PropertyList {
public:
    virtual int AddRef();   // 00h
    virtual int Release();   // 04h
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual bool HasProperty(uint32_t propertyID);   // 1Ch
    virtual void _v20();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // 24h
    virtual Property* GetPropertyObject(uint32_t propertyID);   // 28h
};

class ILightingWorld {
public:
    virtual int AddRef();   // 00h
    virtual int Release();   // 04h
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void SetLightingState(uint32_t configID);   // 30h
    virtual void _v34();
    virtual PropertyList* GetLightingStateConfig();   // 38h
};

class IModelWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual cMWModel* CreateModel(uint32_t instanceID, uint32_t groupID, int arg);   // 0Ch
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24();
    virtual void _v28(); virtual void _v2C(); virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4C(); virtual void _v50(); virtual void _v54();
    virtual void StallUntilLoaded(cMWModel* model);   // 58h
    virtual void _v5C(); virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6C(); virtual void _v70();
    virtual void _v74(); virtual void _v78(); virtual void _v7C(); virtual void _v80(); virtual void _v84(); virtual void _v88();
    virtual void _v8C(); virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9C(); virtual void _vA0();
    virtual void _vA4(); virtual void _vA8(); virtual void _vAC(); virtual void _vB0(); virtual void _vB4(); virtual void _vB8();
    virtual void _vBC(); virtual void _vC0(); virtual void _vC4(); virtual void _vC8(); virtual void _vCC(); virtual void _vD0();
    virtual void _vD4(); virtual void _vD8(); virtual void _vDC(); virtual void _vE0(); virtual void _vE4(); virtual void _vE8();
    virtual void _vEC(); virtual void _vF0(); virtual void _vF4(); virtual void _vF8(); virtual void _vFC(); virtual void _v100();
    virtual void _v104(); virtual void _v108(); virtual void _v10C(); virtual void _v110(); virtual void _v114(); virtual void _v118();
    virtual void _v11C(); virtual void _v120(); virtual void _v124(); virtual void _v128(); virtual void _v12C(); virtual void _v130();
    virtual void SetActive(bool active);   // 134h
    virtual void _v138(); virtual void _v13C();
    virtual int SetLightingWorld(ILightingWorld* pWorld, int indexDrawSet, bool drawShadows);   // 140h
    virtual ILightingWorld* GetLightingWorld(int indexDrawSet);   // 144h
};

class IEffectsWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void SetState(int state);   // 0Ch
};

class cEffectsManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4C(); virtual void _v50(); virtual void _v54();
    virtual void SetActiveWorld(IEffectsWorld* world);   // 58h
    virtual void _v5C(); virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6C(); virtual void _v70();
    virtual void _v74(); virtual void _v78(); virtual void _v7C(); virtual void _v80(); virtual void _v84(); virtual void _v88();
    virtual void _v8C(); virtual void _v90(); virtual void _v94();
    virtual void SetFlags(int flags, int value);   // 98h
};

class IShadowWorld {
public:
    virtual int AddRef();   // 00h
    virtual int Release();   // 04h
    virtual void _v08(); virtual void _v0C();
    virtual void SetLightingWorld(ILightingWorld* world);   // 10h
    virtual void _v14();
    virtual void AddModelWorld(IModelWorld* world, int flags);   // 18h
    virtual void _v1C(); virtual void _v20(); virtual void _v24();
    virtual void SetActive(bool active);   // 28h
    virtual void _v2C(); virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40();
    virtual void _v44();
    virtual void SetActiveID(uint32_t id);   // 48h
};

class IHandler {
public:
    virtual bool HandleMessage(uint32_t messageID, void* msg);   // 00h
};

class IMessageServer {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10();
    virtual void PostMSG(uint32_t messageID, void* msg, int arg);   // 14h
    virtual void _v18(); virtual void _v1C(); virtual void _v20();
    virtual void AddListener(IHandler* pHandler, uint32_t messageID);   // 24h
};

class cEditorCamera {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4C();
    virtual void Activate();   // 50h
    void InitTerrain();   // 0x005a22d0
};

class ICamera {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual cEditorCamera* Cast(uint32_t typeID);   // 0Ch
};

class cCameraManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30();
    virtual void SetActiveCameraByID(uint32_t id);   // 34h
    virtual ICamera* GetActiveCamera();   // 38h
};

class cGameModeManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4C();
    virtual cCameraManager* GetCameraManager();   // 50h
};

class cModelManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20();
    virtual void SetSaveModelWorld(IModelWorld* world);   // 24h
    virtual uint32_t GetModelTypeIndex(uint32_t modelType, int arg);   // 28h
};

class cRenderTarget {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18();
    virtual void SetValue(uint32_t value);   // 1Ch
};

class cRenderTargets {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C();
    virtual cRenderTarget* GetTarget();   // 20h
};

class cAppWindow {
public:
    float GetAspect();   // 0x007c40a0
};

class cApp {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4C(); virtual void _v50(); virtual void _v54();
    virtual cAppWindow* GetWindow();   // 58h
};

class IPropManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst);   // 2Ch
};

class IWindow {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4C(); virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5C();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6C(); virtual void _v70(); virtual void _v74();
    virtual void _v78();
    virtual void SetFlag(int flag, bool value);   // 7Ch
};

class cEditorLimits {
public:
    virtual int AddRef();   // 00h
    virtual int Release();   // 04h
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void SetLimit(int which, int value);   // 18h
};

class cSPPlayModeBase {
public:
    virtual void _v00();
    virtual int AddRef();   // 04h
    virtual int Release();   // 08h
};

class cSPEditorBudgetBase {
public:
    virtual void _v00(); virtual void _v04();
    virtual int AddRef();   // 08h
    virtual int Release();   // 0Ch
};

class cSPPaletteBase {
public:
    virtual void _v00();
    virtual int AddRef();   // 04h
    virtual int Release();   // 08h
};

class cSPVerbTrayCollection : public IRefCounted {
public:
    virtual void _v08(); virtual void _v0C();
    virtual void Init(IWindow* pWindow, ResourceKey key, int a, int b, int c);   // 10h
    void SetVisible(bool visible);   // 0x00605870
};

class cSellBackRollover : public IRefCounted {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C();
    virtual void _v20(); virtual void _v24();
    virtual void SetCurrencyChar(wchar_t c);   // 28h
    void HideWin();   // 0x005cc690
};

class cEditorMessageRollover : public IRefCounted {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void Load();   // 1Ch
    void HideWin();   // 0x005bee80
};

class cDetachedRollover : public IRefCounted {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C();
    virtual void _v20(); virtual void _v24();
    virtual void SetCurrencyChar(wchar_t c);   // 28h
    void HideWin();   // 0x005cc0e0
};

class IUnknown32 {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void* Cast(uint32_t typeID);   // 0Ch
};

class cAnimCallbackTarget {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C();
    virtual void SetCallback(int arg, void (*pFunc)(void*), void* pData);   // 10h
};

class IVisualEffect {
public:
    virtual int AddRef();   // 00h
    virtual int Release();   // 04h
    virtual void _v08();
    virtual void Stop(int hard);   // 0Ch
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24();
    virtual void _v28();
    virtual void Start(int arg);   // 2Ch
};

class cInputManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void _v48();
    virtual void AddKeyBinding(cILayer* pLayer, int key, int modifiers);   // 4Ch
};

class IWindowManager {
public:
    virtual void _v00();
    virtual cMainWinBase* GetMainWindow();   // 04h
};

class IAudioSystem {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34();
    virtual void LoadBank(uint32_t id);   // 38h
    virtual void _v3C();
    virtual void SetState(uint32_t group, uint32_t state);   // 40h
    virtual void _v44(); virtual void _v48(); virtual void _v4C(); virtual void _v50(); virtual void _v54();
    virtual void Update();   // 58h
};

class cAudioSystem {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40(); virtual void _v44();
    virtual void PlayMusic(uint32_t id);   // 48h
};

class cConfigManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void* GetConfig(uint32_t id);   // 30h
};

class cIAppMode {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40();
    virtual uint32_t GetModeID();   // 44h
};

// The App::Property static helpers, inlined at every use.
inline bool GetPropBool(PropertyList* pList, uint32_t id, bool& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == kPropBool) {
        dst = *p->GetBool();
        return true;
    }
    return false;
}
inline bool GetPropInt(PropertyList* pList, uint32_t id, int& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == kPropInt32) {
        dst = *p->GetInt();
        return true;
    }
    return false;
}
inline bool GetPropUInt(PropertyList* pList, uint32_t id, uint32_t& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == kPropUInt32) {
        dst = *p->GetUInt();
        return true;
    }
    return false;
}
inline bool GetPropFloat(PropertyList* pList, uint32_t id, float& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == kPropFloat) {
        dst = *p->GetFloat();
        return true;
    }
    return false;
}
// Variants that read the value in place instead of through the out-of-line accessors.
inline bool GetPropBoolDirect(PropertyList* pList, uint32_t id, bool& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == kPropBool) {
        dst = *(bool*)p->GetDataPtr();
        return true;
    }
    return false;
}

namespace SP {
bool GetPropertyAsKey(PropertyList* pList, uint32_t id, ResourceKey* pDst);            // 0x006a1250
bool GetPropertyAsKeyInstance(PropertyList* pList, uint32_t id, uint32_t* pDst);       // 0x006a12a0
bool GetPropertyAsKeyGroup(PropertyList* pList, uint32_t id, uint32_t* pDst);          // 0x006a12e0
bool GetPropertyAsKeyType(PropertyList* pList, uint32_t id, uint32_t* pDst);           // 0x006a1320
class cString;
bool GetPropertyAsText(PropertyList* pList, uint32_t id, cString* pDst);              // 0x006a1360
bool GetPropertyArrayKey(PropertyList* pList, uint32_t id, int& count, ResourceKey*& pKeys);  // 0x006a0ae0
}
bool GetBoolProperty(PropertyList* pList, uint32_t id, bool& dst);    // 0x00407190
bool GetFloatProperty(PropertyList* pList, uint32_t id, float& dst);  // 0x0040cf10
inline bool GetPropUIntDirect(PropertyList* pList, uint32_t id, uint16_t type, uint32_t& dst)
{
    Property* p;
    if (pList && pList->GetProperty(id, p) && p->mnType == type) {
        dst = *(uint32_t*)p->GetDataPtr();
        return true;
    }
    return false;
}

namespace SP {
class cString {
public:
    uint32_t mData[4];
    cString();    // 0x006b5060
    ~cString();   // 0x006b5240
    const wchar_t* GetText();   // 0x006b55c0
};
}
// ---------------------------------------------------------------------------------------------
// Concrete classes used by Activate (constructors and non-virtual methods are external).

// EA::RefCountVTemplate<int>: virtual dtor in slot 0 and an inline count.
class RefCountVTemplate {
public:
    virtual ~RefCountVTemplate();
    int mnRefCount;

    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
};
void operator delete(void* p);

class cMWModel : public IRefCounted {
public:
    uint32_t mFlags;              // +04: bit 0 cleared for play-mode-only backgrounds
    uint32_t field_8[15];
    uint32_t mModelTypeBits[2];   // +44: eastl::bitset<64>

    // eastl::bitset<64>::set(index); out-of-range indices are ignored
    void SetModelTypeBit(uint32_t index)
    {
        if (index < 64)
            mModelTypeBits[index >> 5] |= (uint32_t)1 << (index & 0x1f);
    }
};

class cSPEditorPhysicsWorld;

class cSPEditorModelBase {
public:
    virtual void _v00();
};
class cSPEditorModel : public cSPEditorModelBase, public RefCountVTemplate {
public:
    uint32_t field_C[19];
    uint32_t mModelType;   // +58
    uint32_t field_5C[33];

    cSPEditorModel();   // 0x004ab690
    void SetPhysicsWorld(cSPEditorPhysicsWorld* pWorld);   // 0x004ad370
    void SetBoundsMax(float f);          // 0x004ada80
    void SetFeetBounds(float f);         // 0x004adac0
    void SetMinHeight(float f);          // 0x004adae0
    void SetMaxHeight(float f);          // 0x004adb20
    void SetUseBoundsForDelete(bool b);  // 0x004adb60
    void SetFlag470(bool b);             // 0x004adba0
    void SetShowBoneLengthHandles(bool b);   // 0x004adbe0
    void SetMinLeglessHeight(float f);   // 0x004adc00
    void SetFlag2F4(bool b);             // 0x004adc20
    bool GetFlag2F4();                   // 0x004adc40
    void SetTranslationOptions(uint32_t options);   // 0x004abad0
    void CreateEmpty(IModelWorld* pWorld, cSPEditorPhysicsWorld* pPhysics, bool a, bool b);   // 0x004ae260
};

class cSPEditorUIBase {
public:
    virtual void _v00();
};
class cSPEditorUI : public cSPEditorUIBase, public IRefCounted {
public:
    uint32_t mData[73];   // sizeof 0x12C
    cSPEditorUI();   // 0x005dea60
    void Init(SP::cAppModeEditorBase* pEditor, uint32_t layoutID, uint32_t groupID, bool bShowSave);   // 0x005ddd60
    void SetShowLoad(bool b);      // 0x005dcc90
    void SetShowPublish(bool b);   // 0x005ddd40
    void SetShowNew(bool b);       // 0x005dcba0
    void SetShowNewFromType(bool b);   // 0x005dcbf0
    void SetShowExit(bool b);      // 0x005dcd80
    void SetShowSporepedia(bool b);   // 0x005dce20
    void SetShowSave(bool b);      // 0x005dcc40
    void SetupAcceptCancel(bool a, uint32_t id, bool b);   // 0x005dc280
    void SetTitleText(uint32_t textID);   // 0x005dc5a0
    IWindow* FindWindowByID(uint32_t id);   // 0x005dc310
    void Show();   // 0x005dd070
    void EnablePlayModeButton(bool b);   // 0x005dcf90
    void UpdateUIBasedOnModelSaveability();   // 0x005dd7a0
};



class cSPPlayMode : public cSPPlayModeBase {
public:
    uint32_t mData[5603];   // sizeof 0x5790
    cSPPlayMode();   // 0x0062b1c0
    void Init(SP::cAppModeEditorBase* pEditor, int arg);   // 0x0062a3d0
};

class cSPEditorBudget : public cSPEditorBudgetBase {
public:
    uint32_t mData[28];   // sizeof 0x74
    cSPEditorBudget();   // 0x004575d0
    void Init(ResourceKey* pLayoutKey, cEditorLimits* pLimits, wchar_t currencyChar, IWindow* pWindow,
              const wchar_t* pPrompt);   // 0x00457af0
};

class cSPEditorComplexityMeter : public IRefCounted {
public:
    uint32_t mData[21];   // sizeof 0x58
    cSPEditorComplexityMeter();   // 0x005a6e60
    void Init(IWindow* pWindow, cEditorLimits* pLimits);   // 0x005a6fc0
};

class cSPEditorStatsPanel : public IRefCounted {
public:
    uint32_t mData[31];   // sizeof 0x80
    cSPEditorStatsPanel();   // 0x0059a270
    void Init(IWindow* pWindow);   // 0x0059a7f0
};

class cISPEditorNameProvider {
public:
    virtual void _v00();
};

class cSPEditorNaming : public IRefCounted {
public:
    uint32_t mData[13];   // sizeof 0x38
    cSPEditorNaming();   // 0x005bfff0
    void Init(cISPEditorNameProvider* pProvider, IWindow* pWindow, uint32_t id, bool bShowNew,
              uint32_t defaultNameID);   // 0x005bfd40
    void SetPrompt(const wchar_t* pText);   // 0x005c0320
};

class cSPPalette : public cSPPaletteBase {
public:
    uint32_t mData[15];   // sizeof 0x40
    cSPPalette();   // 0x005c5e30
    bool Init(ResourceKey* pKey, uint32_t modelType, uint32_t groupID, int a, int b, int c, int d);   // 0x005c6340
};

class cCollectableItems : public IRefCounted {};

class cSPEditorPaintTheme : public IRefCounted {
public:
    uint32_t field_4[80];
    uint32_t mPropertyID;   // +144
    uint32_t field_148[22];   // sizeof 0x1A0

    cSPEditorPaintTheme();   // 0x004b24c0
    void SetSource(uint32_t typeID);   // 0x004b26e0
    void ReadFromProp(uint32_t instanceID);   // 0x004b2bb0
};

// The palette data source handed to cSPPaletteUI::Init.
class cPaletteItemsSource : public cSPPaletteBase {
public:
    uint32_t field_4;
    AutoRefCount<cEditorLimits> mpEditorLimits;          // +08
    AutoRefCount<cSPEditorPaintTheme> mpPaintTheme;      // +0C
    AutoRefCount<cCollectableItems> mpCollectableItems;  // +10
    uint32_t field_14;
    wchar_t mCurrencyChar;       // +18
    uint32_t mCameraPalette;     // +1C
    uint32_t mSaveExtension;     // +20
    uint32_t field_24[2];
    uint32_t mModelType;         // +2C
    uint32_t field_30;

    cPaletteItemsSource();   // 0x005c64e0
};

class cSPPaletteUI : public IRefCounted {
public:
    uint32_t mData[26];   // sizeof 0x6C
    cSPPaletteUI();   // 0x005cb3b0
    void Init(cSPPalette* pPalette, IWindow* pWindow, int arg, cPaletteItemsSource* pSource);   // 0x005cb5a0
};

class cSPEditorAnimatedCreatureManager : public IRefCounted {
public:
    uint32_t field_4[13];
    cAnimCallbackTarget* mpAnimWorld;   // +38
    uint32_t field_3C[3];   // sizeof 0x48

    cSPEditorAnimatedCreatureManager();   // 0x0059c7c0
    void Init(IModelWorld* pWorld, bool bEnableAnim);   // 0x0059c060
};

class cSPEditorSkinManager : public IRefCounted {
public:
    uint32_t mData[33];   // sizeof 0x88
    cSPEditorSkinManager();   // 0x004c2bc0
    void Init(SP::cAppModeEditorBase* pEditor, cSPEditorModel* pModel, IModelWorld* pWorld);   // 0x004c3070
    void SetSkinEffect(uint32_t effectID);   // 0x004c4f60
    void SetSkinRange(float a, float b);   // 0x004c5100
    void* GetSkin(int index);   // 0x004c49e0
};

class cSPEditorSpine : public IRefCounted {
public:
    uint32_t mData[73];   // sizeof 0x128
    cSPEditorSpine();   // 0x005d0ea0
    void SetVertebraModel(ResourceKey* pKey);   // 0x005cd940
    void SetVertebraScale(float f);   // 0x005cd970
    void InitSpine(cSPEditorModel* pModel, IModelWorld* pWorld, int count);   // 0x005d36e0
};

class cSPVerbTray : public cSPVerbTrayCollection {
public:
    uint32_t mData[46];   // sizeof 0xBC
    cSPVerbTray();   // 0x005e0cf0
};
class cSPVerbTrayCollectionSimple : public cSPVerbTrayCollection {
public:
    uint32_t mData[20];   // sizeof 0x54
    cSPVerbTrayCollectionSimple();   // 0x005e8920
};

class cSPEditorSellBackDetachedRollover : public cSellBackRollover {
public:
    uint32_t mData[41];   // sizeof 0xA8
    cSPEditorSellBackDetachedRollover();   // 0x005cc520
};
class cSPEditorMessageRollover : public cEditorMessageRollover {
public:
    uint32_t mData[37];   // sizeof 0x98
    cSPEditorMessageRollover();   // 0x005bed80
};
class cSPEditorDetachedRollover : public cDetachedRollover {
public:
    uint32_t mData[39];   // sizeof 0xA0
    cSPEditorDetachedRollover();   // 0x005cbf60
};

struct cEditorLaunchData {
    uint32_t field_0[3];
    uint32_t mEditorConfig;    // +0C
    ResourceKey mModelKey;     // +10
    uint32_t mModelKeyExtra;   // +1C
    bool mbLoadAsTemplate;     // +20
    uint8_t pad21[0x14];
    bool mbAllowNameEdit;      // +35
    bool mbShowLoad;           // +36
    bool mbShowPublish;        // +37
    bool mbShowNew;            // +38
    bool mbShowExit;           // +39
    bool mbShowSporepedia;     // +3A
    bool mbShowSave;           // +3B
    bool mbShowSaveAs;         // +3C
    bool mbIsOwnCreation;      // +3D
    uint8_t pad3E[0x22];
    uint32_t mShaderArg;       // +60
    uint8_t pad64;
    bool mbAccept;             // +65
    bool mbCancel;             // +66
    uint8_t pad67;
    uint32_t mAcceptTextID;    // +68
    bool mbReadOnly;           // +6C
    uint8_t pad6D;
    bool mbCountActivation;    // +6E
    uint8_t pad6F[0x15];
    uint32_t mPaletteInstance;   // +84
    uint32_t field_88;
    uint32_t mPaletteGroup;    // +8C
    uint32_t mLaunchSource;    // +90
    AutoRefCount<IUnknown32> mpCollectableItems;   // +94
    uint32_t mTitleOverride;   // +98
};

struct cAppPropertiesData {
    uint32_t field_0[70];
    int mbCheatsEnabled;   // +118
};
class cDirectPropertyList {
public:
    uint32_t field_0[15];
    cAppPropertiesData* mpData;   // +3C

    int GetIntProperty(uint32_t id);              // 0x006a2660
    void SetIntProperty(uint32_t id, int value);  // 0x006a1880
};

struct cIntrusiveListOwner {
    uint32_t field_0[28];
    void* mpListHead;   // +70: points at itself when empty
};

struct cLoadModelParams {
    uint32_t mData[4];
};

class cSPEditorTuning {
public:
    void LoadTuningValues(PropertyList* pList);   // 0x005dbd20
};
struct cEditorDisplayOptions {
    uint8_t pad[0xb9];
    bool mbShowAbilityIcons;   // +B9
};
class cDisplayManager {
public:
    cEditorDisplayOptions* GetEditorOptions();   // 0x0113ae10
    cEditorDisplayOptions* GetGameOptions();     // 0x00801920
};
class cEditorCameraController {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10();
    virtual void _v14();
    virtual void Reset();   // 18h
    void SetPartModeCameraOffset();   // 0x005a2400
    void SetZoomInverted(bool b);     // 0x005a2000
    void SetBoundSize(float f);       // 0x010171e0
};
class cSwarmManager {
public:
    IVisualEffect* CreateEffect(uint32_t id, bool bStart);   // 0x0045ae10
    IVisualEffect* FindEffect(uint32_t id);                  // 0x0045b210
    void KillEffect(uint32_t id);                            // 0x0045b150
};
class cRenderManager {
public:
    IModelWorld* GetUILayerModelWorld();   // 0x006c10e0
};
class cSPUILayoutManager {
public:
    char IsWorldVisible(uint32_t id);           // 0x00810760
    void SetWorldVisible(uint32_t id, bool b);  // 0x00810660
};
class cMainWinBase {
public:
    virtual void _v00();
};
class cMainWinPrimary {
public:
    virtual void _v00();
};
class cSPUIMainWin : public cMainWinPrimary, public cMainWinBase {
public:
    uint64_t GetTimeStamp();   // 0x008130a0
};
class cHintManager {
public:
    uint32_t field_0[18];
    int mHintMode;   // +48
    void AddHintProcessor(class cIHintProcessor* p);   // 0x0067ca50
};

class ArgScript_cCommandBase {
public:
    virtual void _v00();
    uint32_t field_4[3];
    ArgScript_cCommandBase();   // 0x0083c800
};
// Editor cheat command ("Editor" cheat), holds a back pointer to the editor.
class cEditorCheat : public ArgScript_cCommandBase {
public:
    SP::cAppModeEditorBase* mpEditor;   // +10
    cEditorCheat(SP::cAppModeEditorBase* pEditor) : mpEditor(pEditor) {}
    virtual void _v00();
};

// Message posted to the message server when an editor activates (vtable 0x013eb844, base 0x013eb90c).
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;   // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
class cEditorActivatedMessage : public cBehaviorMessage {
public:
    uint32_t mModeID;        // +08
    uint32_t field_C[9];
    uint32_t mMessageID;     // +30
    uint32_t field_34;
    void* mpData;            // +38

    cEditorActivatedMessage() : mMessageID(0x60c8707), mpData(0) {}
    virtual void _v00();
    ~cEditorActivatedMessage();   // 0x00421cf0
};

// Registers one handler for a fixed list of message IDs (stored on the editor so it can unregister).
struct cMessageListenerRegistration {
    IMessageServer* mpServer;
    IHandler* mpHandler;
    const uint32_t* mpMessageIDs;
    int mnCount;
    int mnFlags;

    void Register(IMessageServer* pServer, IHandler* pHandler, const uint32_t* pIDs, int count)
    {
        mpServer = pServer;
        mpHandler = pHandler;
        mpMessageIDs = pIDs;
        mnCount = count;
        mnFlags = 0;
        if (pServer && pHandler)
            for (int i = 0; i < count; i++)
                pServer->AddListener(pHandler, pIDs[i]);
    }
};
extern const uint32_t kEditorMessageIDs[30];   // 0x013f5fc8

// ---------------------------------------------------------------------------------------------
// Globals and free functions.
namespace SP {
IMessageServer* MessageServer();   // 0x0067dcc0
void CheatManager();               // 0x0067de20
cModelManager* ModelManager();     // 0x0067dd80
void ModelManagerInit();           // 0x0067de00
cEffectsManager* EffectsManager();   // 0x0067ddd0
cRenderTargets* RenderTargets();   // 0x0067de40
cApp* App();                       // 0x0067dd10
IPropManager* PropertyManager();   // 0x0067de30
cSPEditorTuning* EditorTuning();   // 0x00401070
cDisplayManager* DisplayManager();   // 0x00401020
cSwarmManager* SwarmManager();     // 0x00401050
cRenderManager* RenderManager();   // 0x0067cad0
IShadowWorld* ShadowWorld();       // 0x0067ddc0
cInputManager* InputManager();     // 0x0067dd50
IWindowManager* WindowManager();   // 0x0067caa0
cHintManager* HintManager();       // 0x0067cac0
cAudioSystem* AudioSystem();       // 0x0067cb00
cConfigManager* ConfigManager();   // 0x0067dd30
namespace EditorUtils {
bool GetCreatorType(ResourceKey* pKey);   // 0x00641900
void PlayEditorSound(uint32_t group, uint32_t id, float value, int arg);   // 0x00435f40
void ApplySkinPaintThemeToModel(cSPEditorModel* pModel, cSPPalette* pPalette);   // 0x004b76c0
}
namespace cSPUISpace {
void KillSetiEffects(uint32_t patchID, uint32_t groupID);   // 0x00435ed0
}
}
namespace SPUIHelpers {
cSPUILayoutManager* GetLayoutManager();   // 0x00805070
}
namespace EA { namespace Audio { IAudioSystem* GetSystemAT(); } }   // 0x00a206f0

void PlayBackgroundMusic(uint32_t groupID, int arg);   // 0x00572020
bool GetLaunchPropertyList(const ResourceKey& key, AutoRefCount<PropertyList>& dst);   // 0x005bf0e0
void GetLaunchName(PropertyList* pList, string16* pDst);   // 0x005bf7c0
bool IsModelTypeNewable(uint32_t modelType);   // 0x004bbf10
cCollectableItems* interface_cast_cCollectableItems(AutoRefCount<IUnknown32>* p);   // 0x005767d0
void ReadCollectableItems(PropertyList* pList, cCollectableItems** ppDst);   // 0x005bf1e0
int GetModelCreatorKind(ResourceKey* pKey);   // 0x00552300
void SetShaderParam(int id, void* pValue, int arg);   // 0x00777ae0
void EditorAnimCallback(void* pData);   // 0x00572cf0

extern cDirectPropertyList* g_pAppProperties;     // 0x015fd918
extern PropertyList* g_pConfigPropertyList;       // 0x015fd91c
extern cIntrusiveListOwner* g_pPendingDownloads;  // 0x015fd928
extern uint32_t* g_pRenderFlags;                  // 0x016f6ee0
extern uint32_t g_RenderTargetValue;              // 0x015eebec
extern uint32_t g_EditorPropGroup;                // 0x0150cdd4
extern uint32_t g_ModelGroupID;                   // 0x0150cdf0
extern const cLoadModelParams g_DefaultLoadParams;   // 0x015dac10

// ---------------------------------------------------------------------------------------------
class cILayer {
public:
    virtual void _v00();
};
class cIHintProcessor {
public:
    virtual void _v00();
};
class IHandlerRC : public IHandler {};
class RefCountVBase {
public:
    virtual void _v00();
    int mnRefCount;
};

namespace SP {

class cAppModeEditorBase : public cIAppMode, public cILayer, public cIHintProcessor, public cISPEditorNameProvider,
                           public IHandlerRC, public RefCountVBase {
public:
    /* 01Ch */ uint32_t field_1C;
    /* 020h */ cGameModeManager* mpGameModeMgr;
    /* 024h */ AutoRefCount<PropertyList> mpPropList;
    uint32_t pad028[6];
    /* 040h */ int field_40;
    /* 044h */ int field_44;
    uint32_t pad048[9];
    /* 06Ch */ float mCreatureIdleActivationTime;
    uint32_t pad070[1];
    /* 074h */ bool field_74;
    uint8_t pad075[3];
    /* 078h */ AutoRefCount<cSPEditorUI> mpEditorUI;
    /* 07Ch */ AutoRefCount<cSPPlayMode> mpPlayMode;
    /* 080h */ ILightingWorld* mpLightingWorld;
    /* 084h */ IModelWorld* mpMainModelWorld;
    /* 088h */ IModelWorld* mSaveModelWorld;
    /* 08Ch */ IModelWorld* mpBackgroundModelWorld;
    /* 090h */ cSPEditorPhysicsWorld* mpPhysicsWorld;
    /* 094h */ IEffectsWorld* mpEffectWorld;
    /* 098h */ AutoRefCount<cSPEditorModel> mpEditorModel;
    uint32_t pad09C[1];
    /* 0A0h */ AutoRefCount<cMWModel> mpPedestalModel;
    /* 0A4h */ AutoRefCount<cMWModel> mpTestEnvironmentModel;
    /* 0A8h */ AutoRefCount<cMWModel> mpBackgroundModel;
    /* 0ACh */ AutoRefCount<cMWModel> mpPlayModeBackgroundModel;
    uint32_t pad0B0[37];
    /* 144h */ bool field_144;
    uint8_t pad145[7];
    /* 14Ch */ AutoRefCount<cSPEditorSpine> mpSpine;
    /* 150h */ AutoRefCount<cSPEditorSkinManager> mpSkinManager;
    uint32_t pad154[14];
    /* 18Ch */ uint32_t mEditorName;
    /* 190h */ bool mbTransitionHideUI;
    /* 191h */ bool mbTransitionCenterCamera;
    uint8_t pad192[2];
    /* 194h */ uint32_t mTransitionAnimationID;
    uint32_t pad198[1];
    /* 19Ch */ uint32_t mTransitionEffectID;
    uint32_t pad1A0[3];
    /* 1ACh */ AutoRefCount<ILightingWorld> mpUILayerOldLightingWorld;
    uint32_t pad1B0[7];
    /* 1CCh */ cEditorLaunchData* mpLaunchData;
    /* 1D0h */ ResourceKey mParentModelKey;
    /* 1DCh */ string16 mOriginalTag;
    uint32_t pad1EC[3];
    /* 1F8h */ uint32_t mCameraThumbnail;
    /* 1FCh */ uint32_t mCameraPalette;
    /* 200h */ ResourceKey mCurrencyIconKey;
    /* 20Ch */ wchar_t mCurrencyChar;
    /* 20Eh */ bool mbBackgroundMusic;
    uint8_t pad20F[1];
    /* 210h */ uint32_t mBackgroundMusicPatchID;
    /* 214h */ uint32_t mTutorialPartModeID;
    /* 218h */ uint32_t mTutorialPlayModeID;
    /* 21Ch */ uint32_t mTutorialPaintModeID;
    uint32_t pad220[22];
    /* 278h */ uint32_t mPlayModeEntryEffectID;
    /* 27Ch */ uint32_t mPlayModeExitEffectID;
    /* 280h */ uint32_t mSkyBoxEffectID;
    uint32_t pad284[4];
    /* 294h */ AutoRefCount<IShadowWorld> mpShadowWorld;
    uint32_t pad298[1];
    /* 29Ch */ AutoRefCount<cSPEditorPaintTheme> mDefaultPaintTheme;
    /* 2A0h */ AutoRefCount<cSPEditorPaintTheme> mCurrentPaintTheme;
    /* 2A4h */ AutoRefCount<cSPVerbTrayCollection> mVerbIconTray;
    /* 2A8h */ uint32_t mSaveExtension;
    /* 2ACh */ uint32_t mSaveDirectory;
    /* 2B0h */ bool mIsActive;
    uint8_t pad2B1[1];
    /* 2B2h */ bool mbShowVertebrae;
    uint8_t pad2B3[2];
    /* 2B5h */ bool mbDisableCreatureAnimIK;
    uint8_t pad2B6[2];
    /* 2B8h */ float mBoundSize;
    /* 2BCh */ float mFeetBoundSize;
    /* 2C0h */ float mMinHeight;
    /* 2C4h */ float mMaxHeight;
    /* 2C8h */ float mMinPlayableWidth;
    /* 2CCh */ float mMinPlayableDepth;
    /* 2D0h */ float mMinPlayableHeight;
    /* 2D4h */ float mMinimumLeglessCreatureHeight;
    /* 2D8h */ uint32_t mViewableComplexityFlags;
    /* 2DCh */ int mComplexityLimit;
    /* 2E0h */ int mBoneComplexityLimit;
    /* 2E4h */ int mMaxBakedBlocks;
    uint32_t pad2E8[1];
    /* 2ECh */ float mMaxGeomScore;
    /* 2F0h */ bool mbCellPinningToRigBlocks;
    /* 2F1h */ bool mbUseSkin;
    /* 2F2h */ bool mbUseSpine;
    /* 2F3h */ bool mbInitSpine;
    /* 2F4h */ bool field_2F4;
    /* 2F5h */ bool mbAllowAsymmetry;
    /* 2F6h */ bool mbOnlyEditFromPalette;
    /* 2F7h */ bool mbMoveModelToGround;
    /* 2F8h */ bool mbMoveModelToCenterOfMass;
    /* 2F9h */ bool mbUseBoundsForDelete;
    /* 2FAh */ bool mbTranslateModelOnSave;
    uint8_t pad2FB[1];
    /* 2FCh */ uint32_t mSporepediaConfigID;
    /* 300h */ uint32_t mSporepediaCanSwitchConfigID;
    /* 304h */ uint32_t mModelTranslationOptions;
    uint32_t pad308[2];
    /* 310h */ bool mbPreserveLineage;
    uint8_t pad311[7];
    /* 318h */ uint32_t field_318;
    uint32_t pad31C[1];
    /* 320h */ vector<uint32_t> mEnabledManipulators;
    /* 334h */ vector<uint32_t> mModelTypes;
    uint32_t pad348[1];
    /* 34Ch */ uint32_t mnDefaultBrainLevel;
    /* 350h */ AutoRefCount<cSPEditorBudget> mpBudget;
    /* 354h */ AutoRefCount<cSPEditorComplexityMeter> mpComplexityMeter;
    /* 358h */ AutoRefCount<cSPEditorNaming> mpNaming;
    /* 35Ch */ AutoRefCount<cSPEditorStatsPanel> mpStatsPanel;
    /* 360h */ AutoRefCount<cSPEditorAnimatedCreatureManager> mpAnimCreatureManager;
    uint32_t pad364[9];
    /* 388h */ int field_388;
    uint8_t pad38C[11];
    /* 397h */ bool field_397;
    uint32_t pad398[8];
    /* 3B8h */ AutoRefCount<cSPPalette> mpPaintPalette;
    /* 3BCh */ AutoRefCount<cSPPaletteUI> mpPaintPaletteUI;
    /* 3C0h */ AutoRefCount<cSPPalette> mpPartsPalette;
    /* 3C4h */ AutoRefCount<cSPPaletteUI> mpPartsPaletteUI;
    /* 3C8h */ bool mbHasPalettes;
    uint8_t pad3C9[107];
    /* 434h */ cEditorLimits* mpEditorLimits;
    /* 438h */ uint64_t mnActivateTime;
    /* 440h */ uint64_t mnModelStartTime;
    uint32_t pad448[2];
    /* 450h */ int field_450;
    uint32_t pad454[7];
    /* 470h */ bool field_470;
    /* 471h */ bool mbShowBoneLengthHandles;
    uint8_t pad472[6];
    /* 478h */ float mfMouseWheelTimeout;
    /* 47Ch */ float mfMouseWheelDistanceThreshold;
    uint32_t pad480[2];
    /* 488h */ float mAnimationInterruptDistance;
    uint32_t pad48C[2];
    /* 494h */ AutoRefCount<cSellBackRollover> mpSellBackRollover;
    /* 498h */ AutoRefCount<cSellBackRollover> mpSellBackRollover2;
    /* 49Ch */ AutoRefCount<cEditorMessageRollover> mpMessageRollover;
    /* 4A0h */ AutoRefCount<cDetachedRollover> mpDetachedRollover;
    /* 4A4h */ AutoRefCount<cDetachedRollover> mpDetachedRollover2;
    uint32_t pad4A8[1];
    /* 4ACh */ int mRenderingQuality;
    /* 4B0h */ bool field_4B0;
    /* 4B1h */ bool field_4B1;
    uint8_t pad4B2[1];
    /* 4B3h */ bool field_4B3;
    uint8_t pad4B4[1];
    /* 4B5h */ bool field_4B5;
    /* 4B6h */ bool field_4B6;
    /* 4B7h */ bool mbModelForceSaveOver;
    /* 4B8h */ bool mbModelCopyConsequence;
    /* 4B9h */ bool mbModelSaveLastChild;
    uint8_t pad4BA[14];
    /* 4C8h */ bool field_4C8;
    uint8_t pad4C9[7];
    /* 4D0h */ float field_4D0;
    uint32_t pad4D4[6];
    /* 4ECh */ int mnActivateCount;
    /* 4F0h */ int mnActivateCountByType[6];
    uint32_t pad508[37];
    /* 59Ch */ uint32_t mDaisType;
    /* 5A0h */ float mfDaisRadius;
    uint32_t pad5A4[12];
    /* 5D4h */ cMessageListenerRegistration mMessageRegistration;
    uint32_t pad5E8[6];  // to 0x600

    cEditorCameraController* GetCameraController();   // 0x00574590
    void ResetEconomy();                                // 0x005754c0
    bool SetMode(int mode, bool bForce);                // 0x00587270
    bool LoadModel(const ResourceKey& key, cLoadModelParams params, bool bIsTemplate);   // 0x0058cee0
    void RefreshModel();                                // 0x00582d00
    void InitializeUndoList();                          // 0x00586690
    void SetSubMode(int subMode);                       // 0x005744b0
    ResourceKey GetDefaultModelKey();                   // 0x00574900
    void UpdateEffectsMask(int arg);                    // 0x0057e340
    void CreateEditorWidgets(uint32_t modeID);          // 0x005dbc10
    int GetEditorTypeIndex();                           // 0x00576140
    void ShowFirstTimeHints();                          // 0x00576440
    void ShowCreatureTutorial();                        // 0x005751b0

    bool Activate();   // 0x0058e6d0
};

}  // namespace SP

// Instantiations of AutoRefCount::operator= that the original calls out of line.
template <> AutoRefCount<cSellBackRollover>& AutoRefCount<cSellBackRollover>::operator=(cSellBackRollover*);
template <> AutoRefCount<cEditorMessageRollover>& AutoRefCount<cEditorMessageRollover>::operator=(cEditorMessageRollover*);
template <> AutoRefCount<cDetachedRollover>& AutoRefCount<cDetachedRollover>::operator=(cDetachedRollover*);
template <> AutoRefCount<cSPEditorPaintTheme>& AutoRefCount<cSPEditorPaintTheme>::operator=(cSPEditorPaintTheme*);
template <> AutoRefCount<cMWModel>& AutoRefCount<cMWModel>::operator=(cMWModel*);
template <> AutoRefCount<IVisualEffect>& AutoRefCount<IVisualEffect>::operator=(IVisualEffect*);
template <> AutoRefCount<ILightingWorld>& AutoRefCount<ILightingWorld>::operator=(ILightingWorld*);
template <> AutoRefCount<cSPVerbTrayCollection>& AutoRefCount<cSPVerbTrayCollection>::operator=(cSPVerbTrayCollection*);
template <> AutoRefCount<cCollectableItems>& AutoRefCount<cCollectableItems>::operator=(cCollectableItems*);
template <> AutoRefCount<cEditorLimits>& AutoRefCount<cEditorLimits>::operator=(cEditorLimits*);
template <> AutoRefCount<cSPEditorAnimatedCreatureManager>& AutoRefCount<cSPEditorAnimatedCreatureManager>::operator=(cSPEditorAnimatedCreatureManager*);
template <> AutoRefCount<cSPEditorSpine>& AutoRefCount<cSPEditorSpine>::operator=(cSPEditorSpine*);

using namespace SP;

// Loads a model into one of the editor's model worlds from a property-list key and tags it with its
// model-type bit.  Inlined three times in Activate.
#define LOAD_WORLD_MODEL(world, slot, instanceID, typeProp)                                      \
    do {                                                                                          \
        slot = (world)->CreateModel(instanceID, g_ModelGroupID, 0);                               \
        if (slot) {                                                                               \
            (world)->StallUntilLoaded(slot);                                                      \
            slot->SetModelTypeBit(pModelManager->GetModelTypeIndex(typeProp, 0));                 \
        }                                                                                         \
    } while (0)

// @ 0x0058e6d0
// Brings an editor up: creates the editor model, UI, play mode, palettes, budget/naming/complexity
// widgets, skin and spine managers, reads every editor tuning property, loads the launch model and
// starts the editor audio.  Returns false only when there is no model manager.
bool cAppModeEditorBase::Activate()
{
    mpEditorModel = new ("Editor", 0, 0, 0, 0) cSPEditorModel();
    mpEditorModel->SetPhysicsWorld(mpPhysicsWorld);

    mMessageRegistration.Register(MessageServer(), this, kEditorMessageIDs, 30);
    field_74 = true;

    new ("Editor", 0, 0, 0, 0) cEditorCheat(this);
    CheatManager();
    mnActivateCount++;

    cModelManager* pModelManager = ModelManager();
    ModelManagerInit();
    cCameraManager* pCameraManager = mpGameModeMgr->GetCameraManager();
    if (!pModelManager)
        return false;

    EffectsManager()->SetFlags(0x10, 1);
    pModelManager->SetSaveModelWorld(mSaveModelWorld);

    if (mpLaunchData && mpLaunchData->mEditorConfig)
        mEditorName = mpLaunchData->mEditorConfig;

    cEditorActivatedMessage msg;
    msg.mModeID = GetModeID();
    MessageServer()->PostMSG(msg.mMessageID, &msg, 0);

    RenderTargets()->GetTarget()->SetValue(g_RenderTargetValue);
    field_4D0 = App()->GetWindow()->GetAspect();

    mpPropList = 0;
    IPropManager* pPropManager = PropertyManager();
    mpPropList = 0;
    pPropManager->GetPropertyList(GetModeID(), g_EditorPropGroup, &mpPropList.mpObject);

    if (mpPropList) {
        uint32_t instanceID;
        if (GetPropertyAsKeyInstance(mpPropList, 0x300db745, &instanceID))
            pCameraManager->SetActiveCameraByID(instanceID);
        GetPropertyAsKeyInstance(mpPropList, 0x9036d280, &field_318);
        GetPropertyAsKeyInstance(mpPropList, 0xb02d871c, &mCameraThumbnail);
        GetPropertyAsKeyInstance(mpPropList, 0x121d3184, &mCameraPalette);
        GetPropertyAsKey(mpPropList, 0x03749179, &mCurrencyIconKey);

        uint32_t currencyChar = 0;
        GetPropUInt(mpPropList, 0x05daa925, currencyChar);
        mCurrencyChar = (wchar_t)currencyChar;
        GetPropUInt(mpPropList, 0x05fa1567, mViewableComplexityFlags);
        GetPropInt(mpPropList, 0x9187aee3, mComplexityLimit);
        GetPropInt(mpPropList, 0x047c1d1b, mBoneComplexityLimit);
        GetPropInt(mpPropList, 0x04dbc51f, mMaxBakedBlocks);
        mMaxGeomScore = 0.0f;
        GetPropFloat(mpPropList, 0x066f72ae, mMaxGeomScore);
        GetPropBool(mpPropList, 0xc8067851, mbPreserveLineage);

        EditorTuning()->LoadTuningValues(mpPropList);

        cEditorDisplayOptions* pOptions = DisplayManager()->GetEditorOptions();
        if (pOptions) {
            bool bShowAbilityIcons = true;
            GetBoolProperty(mpPropList, 0x12ef44d9, bShowAbilityIcons);
            field_4B6 = pOptions->mbShowAbilityIcons;
            pOptions->mbShowAbilityIcons = bShowAbilityIcons;
            cEditorDisplayOptions* pGameOptions = DisplayManager()->GetGameOptions();
            if (pGameOptions)
                pGameOptions->mbShowAbilityIcons = bShowAbilityIcons;
        }

        if (mComplexityLimit == 0)
            mComplexityLimit = -1;
        if (mBoneComplexityLimit == 0)
            mBoneComplexityLimit = -1;
        if (mMaxBakedBlocks == 0)
            mMaxBakedBlocks = -1;

        GetPropertyAsKeyType(mpPropList, 0x100f322f, &mSaveExtension);
        GetPropertyAsKeyGroup(mpPropList, 0x70104290, &mSaveDirectory);

        ICamera* pCamera = mpGameModeMgr->GetCameraManager()->GetActiveCamera();
        if (pCamera && pCamera->Cast(0x029da727)) {
            GetCameraController()->Reset();
            GetCameraController()->SetPartModeCameraOffset();
            bool bInvertZoom = false;
            GetBoolProperty(mpPropList, 0x937e6619, bInvertZoom);
            GetCameraController()->SetZoomInverted(bInvertZoom);
        }

        // Rollovers, created once and kept across activations.
        if (!mpSellBackRollover)
            mpSellBackRollover = new ("Editor", 0, 0, 0, 0) cSPEditorSellBackDetachedRollover();
        if (mpSellBackRollover) {
            mpSellBackRollover->SetCurrencyChar(mCurrencyChar);
            mpSellBackRollover->HideWin();
        }
        if (!mpSellBackRollover2)
            mpSellBackRollover2 = new ("Editor", 0, 0, 0, 0) cSPEditorSellBackDetachedRollover();
        if (mpSellBackRollover2) {
            mpSellBackRollover2->SetCurrencyChar(mCurrencyChar);
            mpSellBackRollover2->HideWin();
        }
        if (!mpMessageRollover)
            mpMessageRollover = new ("Editor", 0, 0, 0, 0) cSPEditorMessageRollover();
        if (mpMessageRollover) {
            mpMessageRollover->Load();
            mpMessageRollover->HideWin();
        }
        if (!mpDetachedRollover)
            mpDetachedRollover = new ("Editor", 0, 0, 0, 0) cSPEditorDetachedRollover();
        if (mpDetachedRollover) {
            mpDetachedRollover->SetCurrencyChar(mCurrencyChar);
            mpDetachedRollover->HideWin();
        }
        if (!mpDetachedRollover2)
            mpDetachedRollover2 = new ("Editor", 0, 0, 0, 0) cSPEditorDetachedRollover();
        if (mpDetachedRollover2) {
            mpDetachedRollover2->SetCurrencyChar(mCurrencyChar);
            mpDetachedRollover2->HideWin();
        }

        field_40 = 1;
        field_44 = 0;
        uint32_t paintThemeID;
        if (GetPropertyAsKeyInstance(mpPropList, 0xb1abf848, &paintThemeID)) {
            mDefaultPaintTheme = new ("Editor", 0, 0, 0, 0) cSPEditorPaintTheme();
            mDefaultPaintTheme->SetSource(mSaveExtension);
            mDefaultPaintTheme->ReadFromProp(paintThemeID);
        }

        if (!mbBackgroundMusic &&
            GetPropertyAsKeyInstance(mpPropList, 0xda51ec17, &mBackgroundMusicPatchID)) {
            PlayBackgroundMusic(0x1d6253c0, 1);
            cSPUISpace::KillSetiEffects(mBackgroundMusicPatchID, 0x1d6253c0);
            mbBackgroundMusic = true;
        }

        // Pedestal and test environment in the main model world.
        if (mpMainModelWorld) {
            uint32_t pedestalID;
            if (GetPropertyAsKeyInstance(mpPropList, 0xb00db7bd, &pedestalID))
                LOAD_WORLD_MODEL(mpMainModelWorld, mpPedestalModel, pedestalID, 0x0fe39de0);
            uint32_t environmentID;
            if (GetPropertyAsKeyInstance(mpPropList, 0x026f3355, &environmentID))
                LOAD_WORLD_MODEL(mpMainModelWorld, mpTestEnvironmentModel, environmentID, 0x026f3933);
        }

        GetPropUInt(mpPropList, 0x067331da, mDaisType);
        GetPropFloat(mpPropList, 0x06733247, mfDaisRadius);

        // Background, plus a play-mode copy for the creature-like editors.
        uint32_t backgroundID;
        if (mpBackgroundModelWorld && GetPropertyAsKeyInstance(mpPropList, 0x021b35a0, &backgroundID)) {
            LOAD_WORLD_MODEL(mpBackgroundModelWorld, mpBackgroundModel, backgroundID, 0x0223e8e0);
            if (mEditorName == 0x37e82da1 || mEditorName == 0x156276d1 || mEditorName == 0x9adf00a9 ||
                mEditorName == 0xa56567f7) {
                mpPlayModeBackgroundModel = mpMainModelWorld->CreateModel(backgroundID, g_ModelGroupID, 0);
                if (mpPlayModeBackgroundModel) {
                    mpMainModelWorld->StallUntilLoaded(mpPlayModeBackgroundModel);
                    mpPlayModeBackgroundModel->SetModelTypeBit(pModelManager->GetModelTypeIndex(0x0223e8e0, 0));
                    mpPlayModeBackgroundModel->mFlags &= ~1u;
                }
            }
        }

        uint32_t skyBoxID = 0x183250af;
        GetPropertyAsKeyInstance(mpPropList, 0x026f337b, &skyBoxID);
        SwarmManager()->CreateEffect(skyBoxID, true);
        mSkyBoxEffectID = 0x183250af;
        GetPropertyAsKeyInstance(mpPropList, 0x026f337b, &mSkyBoxEffectID);
        mPlayModeExitEffectID = 0;
        GetPropertyAsKeyInstance(mpPropList, 0x92ddfc3f, &mPlayModeExitEffectID);
        mPlayModeEntryEffectID = 0;
        GetPropertyAsKeyInstance(mpPropList, 0x92ddfc3e, &mPlayModeEntryEffectID);
        if (mPlayModeExitEffectID) {
            AutoRefCount<IVisualEffect> pEffect = SwarmManager()->FindEffect(mPlayModeExitEffectID);
            if (pEffect)
                pEffect->Stop(0);
            pEffect = SwarmManager()->CreateEffect(mPlayModeExitEffectID, true);
            if (pEffect)
                pEffect->Start(1);
        }
        field_4C8 = true;

        GetPropFloat(mpPropList, 0xf8ddbf2c, mFeetBoundSize);
        mpEditorModel->SetFeetBounds(mFeetBoundSize);

        float value;
        if (GetPropFloat(mpPropList, 0x700db77d, value)) {
            mBoundSize = value;
            mpEditorModel->SetBoundsMax(value);
            mpEditorModel->SetMaxHeight(mBoundSize * 2.0f);
            mpEditorModel->SetMinHeight(mBoundSize * -0.5f);
            cEditorCameraController* pController = GetCameraController();
            if (pController)
                pController->SetBoundSize(mBoundSize);
        }

        GetPropertyAsKeyInstance(mpPropList, 0x044f217a, &mTutorialPartModeID);
        GetPropertyAsKeyInstance(mpPropList, 0x044f21a7, &mTutorialPlayModeID);
        GetPropertyAsKeyInstance(mpPropList, 0x044f21ab, &mTutorialPaintModeID);

        field_470 = false;
        GetPropBool(mpPropList, 0x046082ca, field_470);
        mpEditorModel->SetFlag470(field_470);
        mbShowBoneLengthHandles = false;
        GetPropBool(mpPropList, 0x043f419b, mbShowBoneLengthHandles);
        mpEditorModel->SetShowBoneLengthHandles(mbShowBoneLengthHandles);

        if (GetPropFloat(mpPropList, 0x44c7f29f, value)) {
            mMinHeight = value;
            mpEditorModel->SetMinHeight(value);
        }
        if (GetPropFloat(mpPropList, 0x2704959d, value)) {
            mMaxHeight = value;
            mpEditorModel->SetMaxHeight(value);
        }

        if (mpPropList->HasProperty(0x0538b032))
            GetFloatProperty(mpPropList, 0x0538b032, mMinPlayableWidth);
        if (mpPropList->HasProperty(0x0538b033))
            GetFloatProperty(mpPropList, 0x0538b033, mMinPlayableDepth);
        if (mpPropList->HasProperty(0x0538b031))
            GetFloatProperty(mpPropList, 0x0538b031, mMinPlayableHeight);

        mModelTranslationOptions = 0;
        GetPropUInt(mpPropList, 0x051ce36a, mModelTranslationOptions);
        mpEditorModel->SetTranslationOptions(mModelTranslationOptions);
        mbUseBoundsForDelete = true;
        GetPropBool(mpPropList, 0x05134bdf, mbUseBoundsForDelete);
        mpEditorModel->SetUseBoundsForDelete(mbUseBoundsForDelete);

        mSporepediaConfigID = 0;
        GetPropertyAsKeyInstance(mpPropList, 0x05b70ec7, &mSporepediaConfigID);
        mSporepediaCanSwitchConfigID = 0;
        GetPropertyAsKeyInstance(mpPropList, 0x05baca1f, &mSporepediaCanSwitchConfigID);

        mMinimumLeglessCreatureHeight = 0.0f;
        if (GetPropFloat(mpPropList, 0x5e941753, value)) {
            mMinimumLeglessCreatureHeight = value;
            mpEditorModel->SetMinLeglessHeight(value);
        }

        mfMouseWheelTimeout = 0.3f;
        GetPropFloat(mpPropList, 0x4a6ea1a3, mfMouseWheelTimeout);
        mfMouseWheelDistanceThreshold = 10.0f;
        GetPropFloat(mpPropList, 0x33382a22, mfMouseWheelDistanceThreshold);
        mAnimationInterruptDistance = 30.0f;
        GetPropFloat(mpPropList, 0x05107f8a, mAnimationInterruptDistance);
        mCreatureIdleActivationTime = 500.0f;
        GetPropFloat(mpPropList, 0x0525ea2e, mCreatureIdleActivationTime);

        uint32_t lightingStateID;
        if (GetPropertyAsKeyInstance(mpPropList, 0xb00db8c8, &lightingStateID))
            mpLightingWorld->SetLightingState(lightingStateID);

        // Borrow the UI layer's lighting world (restored on deactivate).
        mpUILayerOldLightingWorld.reset();
        if (RenderManager()->GetUILayerModelWorld()) {
            mpUILayerOldLightingWorld = RenderManager()->GetUILayerModelWorld()->GetLightingWorld(0);
            RenderManager()->GetUILayerModelWorld()->SetLightingWorld(mpLightingWorld, 0, false);
        }

        mModelTypes.clear();
        int nModelTypes = 0;
        ResourceKey* pModelTypes = 0;
        if (GetPropertyArrayKey(mpPropList, 0xb0351b13, nModelTypes, pModelTypes)) {
            for (int i = 0; i < nModelTypes; i++) {
                mModelTypes.push_back(pModelTypes[i].instanceID);
                if (i == 0)
                    mpEditorModel->mModelType = pModelTypes[0].instanceID;
            }
        }

        // Editor UI.
        mpEditorUI = new ("Editor", 0, 0, 0, 0) cSPEditorUI();

        bool bShowSave = true;
        AutoRefCount<PropertyList> pLaunchProps;
        field_4B5 = false;
        mbModelForceSaveOver = false;
        mbModelCopyConsequence = false;
        mbModelSaveLastChild = false;
        if (mpLaunchData) {
            field_4B5 = mpLaunchData->mbIsOwnCreation;
            bShowSave = mpLaunchData->mbShowSaveAs;
            if (GetLaunchPropertyList(mpLaunchData->mModelKey, pLaunchProps)) {
                GetBoolProperty(pLaunchProps, 0x99524faf, mbModelForceSaveOver);
                GetBoolProperty(pLaunchProps, 0xae773a29, mbModelCopyConsequence);
                GetBoolProperty(pLaunchProps, 0x2e0fcc74, mbModelSaveLastChild);
            }
        }
        if (mbModelForceSaveOver) {
            bShowSave = true;
            field_4B5 = field_4B5 || EditorUtils::GetCreatorType(&mpLaunchData->mModelKey);
        }

        uint32_t layoutID = 0;
        GetPropertyAsKeyInstance(mpPropList, 0x700ed5e1, &layoutID);
        mpEditorUI->Init(this, layoutID, 0x40464100, bShowSave);

        bool bShowNew = true;
        if (mpLaunchData) {
            mpEditorUI->SetShowLoad(mpLaunchData->mbShowLoad);
            mpEditorUI->SetShowPublish(mpLaunchData->mbShowPublish);
            mOriginalTag.clear();
            if (pLaunchProps)
                GetLaunchName(pLaunchProps, &mOriginalTag);

            bool bAllowNew = true;
            GetPropBool(mpPropList, 0x055ace95, bAllowNew);
            bShowNew = bAllowNew && !mpLaunchData->mbAllowNameEdit && mOriginalTag.empty();

            if (mpLaunchData->mbShowNew && bShowNew) {
                if (mModelTypes.size() > 0 && IsModelTypeNewable(mModelTypes[0])) {
                    mpEditorUI->SetShowNew(false);
                    mpEditorUI->SetShowNewFromType(true);
                } else {
                    mpEditorUI->SetShowNew(true);
                    mpEditorUI->SetShowNewFromType(false);
                }
            } else {
                mpEditorUI->SetShowNew(false);
                mpEditorUI->SetShowNewFromType(false);
            }
            mpEditorUI->SetShowExit(mpLaunchData->mbShowExit);

            bool bAllowSporepedia = true;
            GetPropBool(mpPropList, 0x0660a318, bAllowSporepedia);
            mpEditorUI->SetShowSporepedia(mpLaunchData->mbShowSporepedia & bAllowSporepedia);
            mpEditorUI->SetShowSave(mpLaunchData->mbShowSave);
            mpEditorUI->SetupAcceptCancel(mpLaunchData->mbAccept, mpLaunchData->mAcceptTextID, mpLaunchData->mbCancel);
            if (mpLaunchData->mTitleOverride)
                mpEditorUI->SetTitleText(0x0615ff74);
            else if (mpLaunchData->mbAccept)
                mpEditorUI->SetTitleText(0x0615ff75);
        }

        cSPUILayoutManager* pLayoutManager = SPUIHelpers::GetLayoutManager();
        if (pLayoutManager->IsWorldVisible(0x0614de4c) == 1)
            pLayoutManager->SetWorldVisible(0x0614de4c, false);
        pLayoutManager->SetWorldVisible(0xcbdf6e1d, true);

        // Play mode.
        mpPlayMode = new ("Editor", 0, 0, 0, 0) cSPPlayMode();
        if (mpPlayMode) {
            int playModeArg = 0;
            GetPropInt(mpPropList, 0x0673a6e1, playModeArg);
            mpPlayMode->Init(this, playModeArg);
        }

        if (mpEditorUI) {
            bool bHasPlayMode;
            switch (GetModeID()) {
            case 0x9adf00a9:
            case 0xa56567f7:
            case 0xcf2dc8d0:
            case 0x156276d1:
            case 0x281f5960:
            case 0x290adace:
            case 0x312e9d6a:
            case 0x37e82da1:
            case 0x465c50ba:
            case 0x5bf8f774:
                bHasPlayMode = true;
                break;
            default:
                bHasPlayMode = false;
                break;
            }
            mpEditorUI->EnablePlayModeButton(bHasPlayMode);
        }

        // Verb (ability) tray.
        if (!g_pAppProperties->mpData->mbCheatsEnabled || !mpLaunchData ||
            mpLaunchData->mLaunchSource == 0x0517560a || mpLaunchData->mModelKeyExtra == 0x042b4372) {
            ResourceKey trayKey = {0, 0, 0};
            if (GetPropertyAsKey(mpPropList, 0x04aa3989, &trayKey) && mpEditorUI &&
                mpEditorUI->FindWindowByID(0x722f9a6b) && trayKey.instanceID) {
                AutoRefCount<PropertyList> pTrayProps;
                IPropManager* pManager = PropertyManager();
                pManager->GetPropertyList(trayKey.instanceID, trayKey.groupID, pTrayProps.AsPPTypeParam());
                bool bFullTray = false;
                GetBoolProperty(pTrayProps, 0x0630a7a2, bFullTray);
                if (bFullTray) {
                    mVerbIconTray = new ("Editor", 0, 0, 0, 0) cSPVerbTray();
                    if (mpEditorUI->FindWindowByID(0x0630c829))
                        mpEditorUI->FindWindowByID(0x0630c829)->SetFlag(1, false);
                } else
                    mVerbIconTray = new ("Editor", 0, 0, 0, 0) cSPVerbTrayCollectionSimple();
                cSPVerbTrayCollection* pTray = mVerbIconTray;
                if (pTray) {
                    pTray->Init(mpEditorUI->FindWindowByID(0x722f9a6b), trayKey, 0, 0, 0);
                    mVerbIconTray->SetVisible(true);
                }
            }
        }

        int budgetLimit = 0;
        GetPropInt(mpPropList, 0x065e9be8, budgetLimit);
        mpEditorLimits->SetLimit(0, budgetLimit);
        ResetEconomy();

        // Budget, complexity meter, stats panel, naming.
        mpBudget = new ("Editor", 0, 0, 0, 0) cSPEditorBudget();
        if (mpBudget) {
            cString budgetText;
            const wchar_t* pBudgetText = 0;
            if (GetPropertyAsText(mpPropList, 0x065238b1, &budgetText))
                pBudgetText = budgetText.GetText();
            ResourceKey budgetLayout = {0x734d3ba1, 0x0510a95b, 0x40464100};
            mpBudget->Init(&budgetLayout, mpEditorLimits, mCurrencyChar, mpEditorUI->FindWindowByID(0x908891a7),
                           pBudgetText);
        }

        mpComplexityMeter = new ("Editor", 0, 0, 0, 0) cSPEditorComplexityMeter();
        if (mpComplexityMeter)
            mpComplexityMeter->Init(mpEditorUI->FindWindowByID(0xf383c97d), mpEditorLimits);

        bool bStatsPanel;
        if (GetPropBool(mpPropList, 0x6468562d, bStatsPanel) && bStatsPanel)
            mpStatsPanel = new ("Editor", 0, 0, 0, 0) cSPEditorStatsPanel();
        if (mpStatsPanel)
            mpStatsPanel->Init(mpEditorUI->FindWindowByID(0x0760a5d8));

        mpNaming = new ("Editor", 0, 0, 0, 0) cSPEditorNaming();
        if (mpNaming) {
            uint32_t defaultNameID = 0;
            GetPropertyAsKeyInstance(mpPropList, 0x0552ab54, &defaultNameID);
            mpNaming->Init(this, mpEditorUI->FindWindowByID(0x272eb68e), 0x80c5e3c3, bShowNew, defaultNameID);
            cString promptText;
            if (GetPropertyAsText(mpPropList, 0x05371343, &promptText))
                mpNaming->SetPrompt(promptText.GetText());
        }

        // Parts palette.
        ResourceKey partsPaletteKey = {0, 0, 0};
        GetPropertyAsKey(mpPropList, 0x7a926123, &partsPaletteKey);
        if (partsPaletteKey.instanceID) {
            mpPartsPalette = new ("Editor", 0, 0, 0, 0) cSPPalette();
            uint32_t modelType = 0x9ea3031a;
            if (mModelTypes.size() > 0)
                modelType = mModelTypes[0];
            uint32_t paletteGroup = 0;
            GetPropertyAsKeyGroup(mpPropList, 0x02233661, &paletteGroup);
            if (mpPartsPalette->Init(&partsPaletteKey, modelType, paletteGroup, 0, 0, 0, 0)) {
                mpPartsPaletteUI = new ("Editor", 0, 0, 0, 0) cSPPaletteUI();
                if (g_pAppProperties->mpData->mbCheatsEnabled) {
                    AutoRefCount<cPaletteItemsSource> pSource = new ("Editor", 0, 0, 0, 0) cPaletteItemsSource();
                    pSource->mpCollectableItems =
                        mpLaunchData ? interface_cast_cCollectableItems(&mpLaunchData->mpCollectableItems) : 0;
                    mpPartsPaletteUI->Init(mpPartsPalette, mpEditorUI->FindWindowByID(0xf006f309), 0, pSource);
                } else
                    mpPartsPaletteUI->Init(mpPartsPalette, mpEditorUI->FindWindowByID(0xf006f309), 0, 0);
                mbHasPalettes = true;
            }
        }

        // Paint palette.
        ResourceKey paintPaletteKey = {0, 0, 0};
        GetPropertyAsKey(mpPropList, 0xf5cbe065, &paintPaletteKey);
        if (paintPaletteKey.instanceID) {
            mpPaintPalette = new ("Editor", 0, 0, 0, 0) cSPPalette();
            uint32_t modelType = 0x9ea3031a;
            if (mModelTypes.size() > 0)
                modelType = mModelTypes[0];
            if (mpPaintPalette->Init(&paintPaletteKey, modelType, 0, 0, 0, 0, 0)) {
                AutoRefCount<cPaletteItemsSource> pSource = new ("Editor", 0, 0, 0, 0) cPaletteItemsSource();
                if (mpLaunchData) {
                    IUnknown32* pItems = mpLaunchData->mpCollectableItems;
                    pSource->mpCollectableItems = pItems ? (cCollectableItems*)pItems->Cast(0x03a3aa3a) : 0;
                    if (!pSource->mpCollectableItems) {
                        ResourceKey itemsKey = {0, 0, 0};
                        if (pLaunchProps)
                            ReadCollectableItems(pLaunchProps, pSource->mpCollectableItems.AsPPTypeParam());
                        else if ((mpLaunchData->mPaletteInstance &&
                                  PropertyManager()->GetPropertyList(mpLaunchData->mPaletteInstance,
                                                                     mpLaunchData->mPaletteGroup,
                                                                     pLaunchProps.AsPPTypeParam())) ||
                                 (GetPropertyAsKey(mpPropList, 0x1b814928, &itemsKey) &&
                                  PropertyManager()->GetPropertyList(itemsKey.instanceID, itemsKey.groupID,
                                                                     pLaunchProps.AsPPTypeParam())))
                            ReadCollectableItems(pLaunchProps, pSource->mpCollectableItems.AsPPTypeParam());
                    }
                }
                pSource->mCurrencyChar = mCurrencyChar;
                pSource->mCameraPalette = mCameraPalette;
                pSource->mpEditorLimits = mpEditorLimits;
                pSource->mpPaintTheme = mDefaultPaintTheme;
                pSource->mSaveExtension = mSaveExtension;
                pSource->mModelType = modelType;
                mpPaintPaletteUI = new ("Editor", 0, 0, 0, 0) cSPPaletteUI();
                mpPaintPaletteUI->Init(mpPaintPalette, mpEditorUI->FindWindowByID(0xf006f308), 0, pSource);
                mbHasPalettes = true;
            }
        }

        mpEditorUI->Show();

        if (mpPropList->HasProperty(0x300dd020)) {
            mpEditorModel->SetFlag2F4(*mpPropList->GetPropertyObject(0x300dd020)->GetValueBool());
            field_2F4 = mpEditorModel->GetFlag2F4();
        }
        GetPropBool(mpPropList, 0x08506dea, mbAllowAsymmetry);

        // Animated creature (play) manager.
        bool bAnimCreatures;
        if (mpPropList->HasProperty(0xf0997c95) && GetPropBool(mpPropList, 0xf0997c95, bAnimCreatures) &&
            bAnimCreatures && mpMainModelWorld) {
            mpAnimCreatureManager = new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedCreatureManager();
            if (mpAnimCreatureManager) {
                bool bDisableAnim = false;
                GetBoolProperty(mpPropList, 0x03c5407b, bDisableAnim);
                mpAnimCreatureManager->Init(mpMainModelWorld, !bDisableAnim);
                if (mpTestEnvironmentModel && mpAnimCreatureManager->mpAnimWorld)
                    mpAnimCreatureManager->mpAnimWorld->SetCallback(0, EditorAnimCallback, this);
                mbDisableCreatureAnimIK = false;
                GetBoolProperty(mpPropList, 0x324b1ebe, mbDisableCreatureAnimIK);
            }
        }

        mbMoveModelToCenterOfMass = false;
        GetPropBool(mpPropList, 0x122a4a7b, mbMoveModelToCenterOfMass);
        mbMoveModelToGround = false;
        GetPropBool(mpPropList, 0x73a9f96a, mbMoveModelToGround);
        mbTranslateModelOnSave = false;
        GetPropBool(mpPropList, 0x051cf3d3, mbTranslateModelOnSave);

        // Editor transition.
        ResourceKey transitionKey = {0, 0, 0};
        GetPropertyAsKey(mpPropList, 0x0534192a, &transitionKey);
        AutoRefCount<PropertyList> pTransitionProps;
        IPropManager* pTransitionManager = PropertyManager();
        pTransitionProps = 0;
        pTransitionManager->GetPropertyList(transitionKey.instanceID, transitionKey.groupID,
                                            &pTransitionProps.mpObject);
        if (pTransitionProps) {
            GetPropertyAsKeyInstance(pTransitionProps, 0x053419da, &mTransitionAnimationID);
            GetPropertyAsKeyInstance(pTransitionProps, 0x053419f1, &mTransitionEffectID);
            GetPropBool(pTransitionProps, 0x05341b56, mbTransitionHideUI);
            GetPropBool(pTransitionProps, 0x05341b5a, mbTransitionCenterCamera);
        } else {
            mbTransitionHideUI = true;
            mbTransitionCenterCamera = true;
            mTransitionEffectID = 0x6ca35b3b;
        }

        // Skin.
        mbCellPinningToRigBlocks = false;
        GetPropBool(mpPropList, 0x0e67bc3a, mbCellPinningToRigBlocks);
        mbUseSkin = false;
        GetPropBool(mpPropList, 0x300de90b, mbUseSkin);
        if (mbUseSkin) {
            mpSkinManager = new ("Editor", 0, 0, 0, 0) cSPEditorSkinManager();
            mpSkinManager->Init(this, mpEditorModel, mpMainModelWorld);
            mpSkinManager->SetSkinEffect(0xca9bb36f);
            float skinMin = 0.05f;
            float skinMax = 0.028f;
            GetPropFloat(mpPropList, 0x711306cd, skinMin);
            GetPropFloat(mpPropList, 0x711306ce, skinMax);
            mpSkinManager->SetSkinRange(skinMin, skinMax);
        }

        // Spine.
        mbUseSpine = false;
        mbInitSpine = false;
        if (mpPropList->HasProperty(0xd02bedc8) && *mpPropList->GetPropertyObject(0xd02bedc8)->GetValueBool())
            mbInitSpine = true;
        if (mpPropList->HasProperty(0x100de9e3) && *mpPropList->GetPropertyObject(0x100de9e3)->GetValueBool()) {
            mpSpine = new ("Editor", 0, 0, 0, 0) cSPEditorSpine();
            if (mpSpine) {
                if (mpPropList->HasProperty(0xd112e352))
                    mpSpine->SetVertebraModel(mpPropList->GetPropertyObject(0xd112e352)->GetKeyTPTR());
                float vertebraScale;
                if (mpPropList->HasProperty(0xd1241c36) && GetFloatProperty(mpPropList, 0xd1241c36, vertebraScale))
                    mpSpine->SetVertebraScale(vertebraScale * 0.5f);
                if (mbInitSpine)
                    mpSpine->InitSpine(mpEditorModel, mpMainModelWorld, 8);
            }
            mbUseSpine = true;
        }

        // Enabled manipulators (array of keys; the instance IDs are the manipulator interface IDs).
        if (mpPropList->HasProperty(0x10119203)) {
            Property* pProp = mpPropList->GetPropertyObject(0x10119203);
            int nManipulators = (int)pProp->GetItemCount();
            ResourceKey* pManipulators = (ResourceKey*)pProp->GetDataPtr();
            mEnabledManipulators.resize(nManipulators);
            for (int i = 0; i < nManipulators; i++)
                mEnabledManipulators[i] = pManipulators[i].instanceID;
        }

        mbOnlyEditFromPalette = false;
        GetPropBoolDirect(mpPropList, 0x3022c4b9, mbOnlyEditFromPalette);
        GetPropBoolDirect(mpPropList, 0x1022adb0, mbShowVertebrae);

        mRenderingQuality = g_pAppProperties->GetIntProperty(0x0400178a);

        // Editor shadows.
        bool bShadows;
        if (GetPropBoolDirect(mpPropList, 0xd0ad4b00, bShadows) && bShadows) {
            mpShadowWorld = ShadowWorld();
            if (mpShadowWorld) {
                mpShadowWorld->SetLightingWorld(mpLightingWorld);
                mpShadowWorld->AddModelWorld(mpMainModelWorld, 1);
                mpShadowWorld->SetActiveID(0x05e51c99);
                bool bActive = mpLightingWorld->GetLightingStateConfig()->HasProperty(0x027f36bb);
                mpShadowWorld->SetActive(bActive);
            }
        }
    }

    SetSubMode(0);

    InputManager()->AddKeyBinding(this, 0x0d, 0);
    InputManager()->AddKeyBinding(this, 0x1a, 2);
    InputManager()->AddKeyBinding(this, 0x11, 3);
    InputManager()->AddKeyBinding(this, 0x0c, 0);
    InputManager()->AddKeyBinding(this, 0x0f, 7);
    InputManager()->AddKeyBinding(this, 0x14, 5);

    mpMainModelWorld->SetActive(true);
    mpBackgroundModelWorld->SetActive(true);
    mSaveModelWorld->SetActive(false);
    if (mpEffectWorld) {
        mpEffectWorld->SetState(0);
        EffectsManager()->SetActiveWorld(mpEffectWorld);
    }

    uint32_t brainLevel = 3;
    GetPropUIntDirect(mpPropList, 0x05deb6a5, kPropInt32, brainLevel);
    mnDefaultBrainLevel = brainLevel;
    if (mbBackgroundMusic)
        EditorUtils::PlayEditorSound(0x1d6253c0, 0xac23893f, (float)brainLevel, 0);

    SetMode(0, true);

    mCurrentPaintTheme = new ("Editor", 0, 0, 0, 0) cSPEditorPaintTheme();
    mCurrentPaintTheme->SetSource(mSaveExtension);

    // Load the launch model, a template model, or start empty.
    bool bLoaded = false;
    if (mpLaunchData && mpLaunchData->mModelKey.instanceID) {
        field_4B1 = false;
        if (GetModelCreatorKind(&mpLaunchData->mModelKey) == 1)
            field_4B0 = true;
        else
            field_4B0 = false;
        bLoaded = LoadModel(mpLaunchData->mModelKey, g_DefaultLoadParams, true);
        if (mpLaunchData->mbLoadAsTemplate) {
            RefreshModel();
            field_4B0 = false;
        }
    }
    if (!bLoaded) {
        if (mpPropList && mpPropList->HasProperty(0x503d2f60)) {
            cLoadModelParams params = {0, 0, 0, 0};
            LoadModel(GetDefaultModelKey(), params, false);
            field_4B0 = false;
            field_4B1 = true;
            if (mpSkinManager && mpSkinManager->GetSkin(1) &&
                (!g_pPendingDownloads || g_pPendingDownloads->mpListHead == &g_pPendingDownloads->mpListHead))
                EditorUtils::ApplySkinPaintThemeToModel(mpEditorModel, mpPartsPalette);
        } else {
            field_4B0 = false;
            field_4B1 = true;
            mpEditorModel->CreateEmpty(mpMainModelWorld, mpPhysicsWorld, true, true);
            if (mDefaultPaintTheme && mDefaultPaintTheme->mPropertyID)
                mCurrentPaintTheme->ReadFromProp(mDefaultPaintTheme->mPropertyID);
        }
        RefreshModel();
        mParentModelKey.instanceID = 0;
        mParentModelKey.typeID = 0;
        mParentModelKey.groupID = 0;
    }
    InitializeUndoList();

    if (mpLaunchData && mpLaunchData->mbReadOnly) {
        field_4B3 = true;
        mpEditorUI->UpdateUIBasedOnModelSaveability();
    }

    ICamera* pCamera = mpGameModeMgr->GetCameraManager()->GetActiveCamera();
    if (pCamera) {
        cEditorCamera* pEditorCamera = pCamera->Cast(0x029da727);
        if (pEditorCamera) {
            pEditorCamera->Activate();
            pEditorCamera->InitTerrain();
        }
    }

    mnModelStartTime = static_cast<cSPUIMainWin*>(WindowManager()->GetMainWindow())->GetTimeStamp();
    mnActivateTime = static_cast<cSPUIMainWin*>(WindowManager()->GetMainWindow())->GetTimeStamp();

    if (mbBackgroundMusic)
        EditorUtils::PlayEditorSound(0x1d6253c0, 0xac23893f, (float)mnDefaultBrainLevel, 0);

    IAudioSystem* pAudio = EA::Audio::GetSystemAT();
    if (pAudio) {
        pAudio->LoadBank(0x03475365);
        pAudio->SetState(0x03475381, 0x8a590b9e);
        pAudio->SetState(0x03475385, 0xb07c3bbf);
        pAudio->Update();
    }

    UpdateEffectsMask(0);

    AutoRefCount<IVisualEffect> pAmbientEffect = SwarmManager()->FindEffect(0xb8deeb8b);
    if (!pAmbientEffect) {
        SwarmManager()->KillEffect(0x4cf52822);
        pAmbientEffect = SwarmManager()->CreateEffect(0xb8deeb8b, true);
    }
    if (pAmbientEffect)
        pAmbientEffect->Start(1);

    field_397 = false;
    field_388 = 0;
    CreateEditorWidgets(GetModeID());

    int hintMode = HintManager()->mHintMode;
    field_144 = (hintMode == 0 || hintMode == 1);
    HintManager()->AddHintProcessor(this);

    cAudioSystem* pAudioSystem = AudioSystem();
    if (pAudioSystem) {
        uint32_t musicID;
        switch (mEditorName) {
        case 0x465c50ba:
        case 0x156276d1:
        case 0x247e2615:
        case 0x5bf8f774:
            musicID = 0xbd1a8c04;
            break;
        default:
            musicID = 0xad7f8693;
            break;
        }
        pAudioSystem->PlayMusic(musicID);
    }

    mIsActive = true;
    *g_pRenderFlags |= 1;

    if (mpLaunchData && mpEditorModel->mModelType == 0xdfad9f51)
        SetShaderParam(0x236, &mpLaunchData->mShaderArg, 1);

    int typeIndex = GetEditorTypeIndex();
    if (typeIndex < 6 && mpLaunchData && mpLaunchData->mbCountActivation)
        mnActivateCountByType[typeIndex]++;

    if (!g_pAppProperties->mpData->mbCheatsEnabled)
        ShowFirstTimeHints();

    PropertyList* pConfig = g_pConfigPropertyList;
    bool bHasTutorialConfig = ConfigManager()->GetConfig(0x04ea96cb) != 0;
    bool bTutorialSeen = false;
    if (mEditorName == 0xa56567f7) {
        GetPropBoolDirect(pConfig, 0x07be27a2, bTutorialSeen);
        if (bHasTutorialConfig && !bTutorialSeen)
            ShowCreatureTutorial();
    }

    field_450 = g_pAppProperties->GetIntProperty(0x0b);
    g_pAppProperties->SetIntProperty(0x0b, 0);

    return true;
}
