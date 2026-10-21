// SP::cSPEditorBlock — list update + model creation (unoptimized /Od /Ob1).
#include "types.h"

namespace SP {

struct Property {
    void* mpData;
    uint32_t pad04;
    int mnItemCount;
    uint32_t pad0c;
    uint16_t mnFlags;     // +0x10
    uint16_t mnType;      // +0x12
    const bool* GetBool();                       // 0x0041E920
    const float* GetFloat();                     // 0x0041EA70
};
struct ResourceKey { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };
class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};
template <class T>
struct AutoRefCount {
    T* mpObject;
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
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
class IModelManager;
class cSPEditorBlock;
class cSPEditorHandleRotationRing {
public:
    virtual int AddRef();
    virtual int Release();
    char pad[0x92 - 4];
    bool mField92;                               // +0x92
    void SetField92(bool v) { mField92 = v; }
    cSPEditorHandleRotationRing* Construct();    // 0x00483D40
    void Resume(IModelManager* modelMgr, cSPEditorBlock* block, uint32_t modelKey, uint32_t axisID,
                uint32_t placement, float angleDeg, float offset, float scale, bool hidden, bool loadProps); // 0x004849E0
};

__declspec(noinline) bool GetBoolProperty(cPropertyList* list, uint32_t id, bool& value)       // 0x00407190
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 1) {
        value = *prop->GetBool();
        return true;
    }
    return false;
}
__declspec(noinline) bool GetFloatProperty(cPropertyList* list, uint32_t id, float& value)     // 0x0040CF10
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd) {
        value = *prop->GetFloat();
        return true;
    }
    return false;
}
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey& value);      // 0x006A1250
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t& value); // 0x006A12A0
IModelManager* ModelManager();                                                    // 0x0067DD80
void* OperatorNewEditor(int size, const char* tag, int, int, int, int);           // 0x00F473A0

// Inline copy of the helper for the one call site where the original did inline it.
inline bool GetBoolPropertyIL(cPropertyList* list, uint32_t id, bool& value)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 1) {
        value = *prop->GetBool();
        return true;
    }
    return false;
}
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Elem { void* p; char pad[0x1C]; };   // 0x20-byte element

class cSPEditorBlock { public:
    char  pad0[0xC];
    AutoRefCount<cPropertyList> mpPropList;        // +0xC
    char  pad10[0x154 - 0x10];
    AutoRefCount<cSPEditorHandleRotationRing> mRotationRingHandles[3];   // +0x154
    char  pad160[0x4C8 - 0x160];
    Elem* begin48;     // +0x4C8
    Elem* end4cc;      // +0x4CC

    void F41080();                                     // 0441080
    void F40e60(void* p);                              // 0440E60
    void CreateRotationRingHandle(int index, uint32_t axisID, uint32_t useDefaultPropID, uint32_t keyPropID,
                                  uint32_t anglePropID, uint32_t offsetPropID, uint32_t scalePropID,
                                  uint32_t hiddenPropID, uint32_t tagPropID, uint32_t instancePropID);  // 04410D0
};

// @ 0x00441080
void cSPEditorBlock::F41080()
{
    Elem* it = begin48;
    Elem* end = end4cc;
    for (; it != end; it++) {
        F40e60(it->p);
    }
}

// @ 0x004410D0
void cSPEditorBlock::CreateRotationRingHandle(int index, uint32_t axisID, uint32_t useDefaultPropID, uint32_t keyPropID,
                                              uint32_t anglePropID, uint32_t offsetPropID, uint32_t scalePropID,
                                              uint32_t hiddenPropID, uint32_t tagPropID, uint32_t instancePropID)
{
    float v22;
    float v14;
    uint32_t v3;
    bool v1;
    float p20;
    bool idx;
    bool t33;
    bool t28;
    cSPEditorHandleRotationRing* n36;
    ResourceKey m;
    uint32_t n32;

    idx = mpPropList->HasProperty(keyPropID);
    t28 = true;
    GetBoolProperty(mpPropList, useDefaultPropID, t28);
    ScratchSlots<3>();
    if (idx == 0 && t28 == 0)
        return;
    p20 = 0.0f;
    v14 = 0.0f;
    v22 = 1.0f;
    t33 = false;
    v1 = true;
    v3 = 0xA659762B;
    n32 = 0x0C1EF506;
    GetPropertyAsKeyInstance(mpPropList, instancePropID, n32);
    if (idx) {
        m.instanceID = 0;
        m.typeID = 0;
        m.groupID = 0;
        GetPropertyAsKey(mpPropList, keyPropID, m);
        if (m.instanceID != 0x2CA33BDB && m.instanceID != 0) {
            n32 = m.instanceID;
            if (m.typeID != 0)
                v3 = m.typeID;
            GetFloatProperty(mpPropList, anglePropID, p20);
            ScratchSlots<3>();
            GetFloatProperty(mpPropList, offsetPropID, v14);
            ScratchSlots<3>();
            GetFloatProperty(mpPropList, scalePropID, v22);
            ScratchSlots<3>();
            GetBoolProperty(mpPropList, hiddenPropID, t33);
            ScratchSlots<3>();
            v1 = false;
            GetBoolPropertyIL(mpPropList, tagPropID, v1);
            ScratchSlots<1>();
        }
    }
    n36 = (cSPEditorHandleRotationRing*)OperatorNewEditor(0x9C, "Editor", 0, 0, 0, 0);
    mRotationRingHandles[index] = n36 ? n36->Construct() : 0;
    mRotationRingHandles[index]->Resume(ModelManager(), this, n32, axisID, v3, p20, v14, v22, t33, true);
    mRotationRingHandles[index]->SetField92(v1);
}

} // namespace SP
