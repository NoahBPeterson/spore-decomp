// Slice s00e9a7c0: SP::cSPUFOGfx::SetUFOModel (0x00e9a940, 1765 bytes, __thiscall, ret 8).
//
// SetUFOModel(ResourceKey* key, bool announce): swaps the UFO view's model.
//   1. looks up the UFO game data (this->GetGameObject()->Cast(0xb033b403)); mode 0 = a normal/player
//      UFO ("isMode0");
//   2. when `announce` it posts message 0x2ea8fb98 {1,0} (mode 0) or {0,3} to the global message bus;
//   3. in mode 0 or when the universe context is 2 it builds a cSimulator property list for the model
//      (parent = the key's property list, property 0x2e33a81 = 4 x 10000.0f, property 0x2a907b8 = 0 in
//      mode 0), forces key.group = (group & 0xffff72ff) | 0x7200 and registers the list under the key;
//   4. loads the model from the Gonzago model world (instance, group), adds a reference, hands it to
//      this->SetModel(model, world), sets its flags (0x20 unless in game mode 0x1654c10, then 0x10),
//      clears a bit in its mask, swaps its effect pointer (+0x64) for the object's 0x17f243b-cast
//      interface, tints the model with the owning empire's colour (not mode 0/5), resets a model
//      parameter (id 0x13) in mode 0, refreshes the UFO and updates the object's flag 0x10 / effect pos;
//   5. creates or re-enables the five effect slots (+0x80, +0xb8, +0x84, +0x88, +0x8c);
//   6. applies the UFO's visible flag, then (model exists) takes the display name (resource of type
//      0x30bdee3 -> IWinText text, else property 0x43afa7e of model+0x90) into the UFO, and drops
//      the model reference (disposing it through its owner when it was the last one).
// The method name and class are the dev-PDB's; the stubs are read off the asm. Flags: /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (no /EHsc: the original has no EH frame).
#include "types.h"

typedef unsigned int size_t;
void operator delete[](void* p);                                         // 0x00f47380
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0

#pragma warning(disable: 4100 4355)

struct Vector3 { float x, y, z; };

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------------------------------------
// engine stubs
struct IRefObject {
    virtual void AddRef();                    // 0x00
    virtual void Release();                   // 0x04
};

template <class T> struct AutoRef {          // reference holder as used by the original (AsPointer idiom)
    T* mpObject;
    __forceinline AutoRef() : mpObject(0) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRef() { if (mpObject) mpObject->Release(); }
    __forceinline T** AsPointer()
    {
        if (mpObject) {
            T* t = mpObject;
            mpObject = 0;
            t->Release();
        }
        return &mpObject;
    }
};

// EA::Variant (0x14 bytes, flags word at +0x10; bit 4 = owns heap data)
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;
    uint16_t mFlags2;
    __forceinline Variant() { mFlags = 0; mFlags2 = 0; }
    __forceinline ~Variant() { if (mFlags & 4) Destruct(0); }
    void Set(int type, int a, const void* data, int size, int count);    // 0x0093dd80 (ret 0x14)
    void Destruct(int arg);                                             // 0x0093db80 (ret 4)
    void SetU32(const uint32_t* value);                                  // 0x00422eb0 (ret 4)
};

// Editor::cPropertyList (0x38 bytes, refcounted)
class cPropertyList {
public:
    cPropertyList();                                                     // 0x006a1c40
    virtual void AddRef();                                               // 0x00
    virtual void Release();                                              // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void SetProperty(uint32_t id, const Variant* value);         // 0x14 (ret 8)
    void SetParent(cPropertyList* parent);                               // 0x006a1710 (ret 4)
    uint32_t mData[(0x38 - 4) / 4];
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** ppList);   // 0x2c
    virtual void v30();
    virtual void AddPropertyList(cPropertyList* list, uint32_t instance, uint32_t group);      // 0x34
};
cPropertyManager* PropertyManager();                                     // 0x0067de30

// eastl::basic_string<wchar_t, eastl::allocator>, 16 bytes
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    static wchar_t kEmpty[];                                             // 0x01667bac
    __forceinline WStr() : mpBegin(kEmpty), mpEnd(kEmpty), mpCapacity(kEmpty + 1) {}
    __forceinline WStr(int, int) : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~WStr()
    {
        if ((mpCapacity - mpBegin) * 2 > 2 && mpBegin)
            operator delete[](mpBegin);
    }
    void RangeInitialize(const wchar_t* psz);                            // 0x00579a90 (ret 4)
};
bool GetPropertyAsString16(cPropertyList* list, uint32_t id, WStr* out); // 0x006a1400 (cdecl)

struct IWinText : IRefObject {
    const wchar_t* GetText();                                            // 0x00414e10
};
struct AutoRefText {                                                      // EA::AutoRefCount<IWinText>
    IWinText* mpObject;
    __forceinline AutoRefText() : mpObject(0) {}
    AutoRefText& operator=(IWinText* p);                                 // 0x00b5f950 (ret 4)
};

struct IResource {
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                                 // 0x0c
};
class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey* key, IResource** out, int a, int b, int c, int d);   // 0x0c
};
IResourceManager* GetManager();                                          // 0x0067dcd0

class IMessageBus {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Post(const ResourceKey* key, const void* message);      // 0x4c
};
IMessageBus* GetMessageBus();                                            // 0x00401010 (returns global 0x015d0c04)

// effects
class IEffect {
public:
    virtual void v00();
    virtual void Release();                                              // 0x04
    virtual void v08();
    virtual void Stop(int arg);                                          // 0x0c
};
class IEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void CreateEffect(uint32_t id, int a, IEffect** out);        // 0x2c
};
IEffectsManager* EffectsManager();                                       // 0x0067ddd0

// model-world model object
class cGameModelOwner {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void DisposeModel(class cGameModel* model, bool flag);       // 0x170 (ret 8)
};

class cEffectRef : public IRefObject {};

class cGameModel {
public:
    cGameModelOwner* mpOwner;                // +0x00
    uint32_t mFlags;                         // +0x04 (bit 31, 14: see below)
    uint32_t pad08[(0x40 - 0x08) / 4];
    int mRefCount;                           // +0x40
    uint32_t mMask[2];                       // +0x44, +0x48
    Vector3 mColor;                          // +0x4c
    uint32_t pad58[(0x64 - 0x58) / 4];
    IRefObject* mpEffect;                    // +0x64
    uint32_t pad68[(0x70 - 0x68) / 4];
    Vector3 mEffectPos;                      // +0x70
    uint32_t pad7c[(0x90 - 0x7c) / 4];
    cPropertyList* mpPropertyList;           // +0x90
};

class cModelWorld {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cGameModel* LoadModel(uint32_t instance, uint32_t group, int flag);         // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4();
    virtual void SetModelParam(cGameModel* model, int id, const float* value, int a, int b);   // 0xc8 (ret 0x14)
};
cModelWorld* GonzagoModelWorld();                                        // 0x00b3d520

class cModelManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual uint32_t GetBitIndex(uint32_t hash, int arg);                // 0x28
};
cModelManager* ModelManager();                                           // 0x0067dd80

class cEmpire { public: void GetColor(Vector3* out); };                  // 0x00c32cd0
class cStarManager { public: cEmpire* GetEmpireByID(int id); };          // 0x00ba9370 (ret 4)
cStarManager* StarManager();                                             // 0x00b3d2a0
uint32_t GetCurrentGameMode();                                           // 0x00b5b800
int GetUniverseContext();                                                // 0x01021080

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    virtual void SetEffectPos(const Vector3* pos, float scale);          // 0x64
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual IRefObject* Cast(uint32_t typeID);                           // 0xb8
    uint32_t pad04[(0x50 - 4) / 4];
    uint32_t mFlags;                                                     // +0x50
};

class cSPGameDataUFO {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetEmpireID();                                           // 0x4c
    uint32_t pad04[(0x714 - 4) / 4];
    int mMode;                                                           // +0x714
    uint32_t pad718[(0x77c - 0x718) / 4];
    bool mbVisible;                                                      // +0x77c
    bool GetVisible();                                                   // 0x00c37170
    void Refresh();                                                      // 0x00c3b4d0
    void SetName(const WStr* name);                                      // 0x00c3dac0 (ret 4)
};

class IGameObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);                                 // 0x0c
};

struct UFOModelMessage {
    uint32_t mID;
    uint16_t mA;
    uint16_t mB;
};

class cSPUFOGfx {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual IGameObject* GetGameObject();                                // 0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetModel(cGameModel* model, cModelWorld* world);        // 0x30

    void SetVisible(bool v);                                             // 0x00e98db0 (ret 4)
    void SetUFOModel(ResourceKey* key, bool announce);                   // 0x00e9a940 (ret 8)

    uint32_t pad04[2];
    cSpatialObject* mpObject;                                            // +0x0c
    uint32_t pad10[2];
    Vector3 mColor;                                                      // +0x18
    uint32_t pad24[(0x30 - 0x24) / 4];
    bool mbModelVisible;                                                 // +0x30
    uint8_t pad31[0x80 - 0x31];
    IEffect* mFilterRangeEffect;                                         // +0x80
    IEffect* mSelectionEffect;                                           // +0x84
    IEffect* mRolloverEffect;                                            // +0x88
    IEffect* mRadarEffect;                                               // +0x8c
    uint32_t pad90[(0xb8 - 0x90) / 4];
    IEffect* mContextEffect;                                             // +0xb8
};

__forceinline void EnsureEffect(IEffect*& slot, uint32_t id)
{
    if (slot == 0) {
        IEffectsManager* mgr = EffectsManager();
        IEffect* old = slot;
        if (old) {
            slot = 0;
            old->Release();
        }
        mgr->CreateEffect(id, 0, &slot);
    } else {
        slot->Stop(1);
    }
}

// @ 0x00E9A940
void cSPUFOGfx::SetUFOModel(ResourceKey* key, bool announce)
{
    const ResourceKey origKey = *key;
    cModelWorld* world = GonzagoModelWorld();
    IGameObject* gameObject = GetGameObject();
    cSPGameDataUFO* ufo = gameObject ? (cSPGameDataUFO*)gameObject->Cast(0xb033b403) : 0;
    const bool isMode0 = ufo->mMode == 0;

    if (announce) {
        UFOModelMessage msg;
        msg.mID = 0x2ea8fb98;
        msg.mA = 0;
        if (isMode0) {
            msg.mB = 0;
            msg.mA = 1;
        } else {
            msg.mB = 3;
        }
        GetMessageBus()->Post(key, &msg);
    }

    if (isMode0 || GetUniverseContext() == 2) {
        cPropertyList* list = new ("Simulator", 0, 0, 0, 0) cPropertyList();
        if (list)
            list->AddRef();
        AutoRef<cPropertyList> parent;
        if (PropertyManager()->GetPropertyList(key->instanceID, key->groupID, parent.AsPointer()))
            list->SetParent(parent.mpObject);
        {
            Variant value;
            float colour[4];
            colour[0] = 10000.0f;
            colour[1] = 10000.0f;
            colour[2] = 10000.0f;
            colour[3] = 10000.0f;
            value.Set(0x33, 0, colour, 0x10, 1);
            list->SetProperty(0x2e33a81, &value);
        }
        if (isMode0) {
            Variant value;
            uint32_t zero = 0;
            value.SetU32(&zero);
            list->SetProperty(0x2a907b8, &value);
        }
        key->groupID = (key->groupID & 0xffff72ff) | 0x7200;
        PropertyManager()->AddPropertyList(list, key->instanceID, key->groupID);
        list->Release();
    }

    cGameModel* model = world->LoadModel(key->instanceID, key->groupID, 0);
    if (model) {
        model->mRefCount++;
        SetModel(model, world);
        if (GetCurrentGameMode() != 0x1654c10)
            model->mFlags |= 0x20;
        model->mFlags |= 0x10;
        model->mMask[0] = 0;
        model->mMask[1] = 0;
        uint32_t bit = ModelManager()->GetBitIndex(0x64ac354, 0);
        if (bit < 0x40)
            model->mMask[bit >> 5] &= ~(1 << (bit & 0x1f));

        IRefObject* effect = 0;
        if (mpObject)
            effect = mpObject->Cast(0x17f243b);
        IRefObject* oldEffect = model->mpEffect;
        if (effect != oldEffect) {
            if (effect)
                effect->AddRef();
            model->mpEffect = effect;
            if (oldEffect)
                oldEffect->Release();
        }

        if (StarManager()->GetEmpireByID(ufo->GetEmpireID()) && ufo->mMode != 0 && ufo->mMode != 5) {
            Vector3 colour;
            StarManager()->GetEmpireByID(ufo->GetEmpireID())->GetColor(&colour);
            mColor = colour;
            model->mFlags |= 4;
            model->mColor = mColor;
        }

        if (isMode0) {
            float zero = 0.0f;
            world->SetModelParam(model, 0x13, &zero, 1, 0);
        }

        ufo->Refresh();
        const bool visible = !((model->mFlags >> 14) & 1);
        mbModelVisible = visible;
        if (visible)
            mpObject->mFlags |= 0x10;
        else
            mpObject->mFlags &= ~0x10u;
        if (!mbModelVisible)
            mpObject->SetEffectPos(&model->mEffectPos, 1.0f);
    }

    EnsureEffect(mFilterRangeEffect, 0x3d6f0bf);
    EnsureEffect(mContextEffect, 0x628a6b8e);
    EnsureEffect(mSelectionEffect, 0x3d6f0d2);
    EnsureEffect(mRolloverEffect, 0x829c3007);
    EnsureEffect(mRadarEffect, 0xdec8dff8);
    SetVisible(ufo->GetVisible());

    if (model) {
        if (model->mpPropertyList) {
            AutoRef<IResource> resource;
            AutoRefText text;
            ResourceKey textKey;
            textKey.instanceID = origKey.instanceID;
            textKey.typeID = 0x30bdee3;
            textKey.groupID = origKey.groupID;
            IResourceManager* manager = GetManager();
            if (manager->GetResource(&textKey, (IResource**)resource.AsPointer(), 0, 0, 0, 0)) {
                text = resource.mpObject ? (IWinText*)resource.mpObject->Cast(0x30bdee3) : 0;
            }
            if (text.mpObject) {
                WStr name(0, 0);
                name.RangeInitialize(text.mpObject->GetText());
                ufo->SetName(&name);
                text.mpObject->Release();
            } else {
                WStr name;
                GetPropertyAsString16(model->mpPropertyList, 0x43afa7e, &name);
                ufo->SetName(&name);
            }
        }
        if (model->mRefCount > 1)
            model->mRefCount--;
        else
            model->mpOwner->DisposeModel(model, (model->mFlags >> 31) & 1);
    }
}
