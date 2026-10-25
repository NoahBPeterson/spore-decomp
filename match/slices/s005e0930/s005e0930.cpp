#include "types.h"

// Slice s005e0930: SP verb-tray / editor widgets.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.

// ---------------------------------------------------------------------------------------------
// @ 0x005e0e50  (matched)
struct RefObj {
    virtual void v0();
    virtual void v1();
    virtual void Release();     // +0x08
    void Shutdown(int);
};
struct BaseB { virtual void vb(); void ShutdownBase(); };
struct CShut : BaseB {
    char pad[0x50];
    RefObj* m54;                // +0x54
    void Shutdown();
};
void CShut::Shutdown()
{
    ShutdownBase();
    if (m54) {
        m54->Shutdown(1);
        RefObj* p = m54;
        if (p) {
            m54 = 0;
            p->Release();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x005e0cf0  ctor (complete; see nonmatching.txt)
struct BaseA { BaseA(); virtual void v0(); };
struct IBaseB { virtual void vb(); };
struct VerbTray : BaseA, IBaseB {
    char pad08[0x4c];      // +0x08..+0x53
    uint32_t z54[12];      // +0x54..+0x83
    char pad84[0xc];       // +0x84..+0x8f
    float f90[6];          // +0x90..+0xa4
    VerbTray();
};
VerbTray::VerbTray()
{
    z54[0] = 0; z54[1] = 0; z54[2] = 0; z54[3] = 0; z54[4] = 0; z54[5] = 0;
    z54[6] = 0; z54[7] = 0; z54[8] = 0; z54[9] = 0; z54[10] = 0; z54[11] = 0;
    f90[0] = 0.0f; f90[1] = 0.0f; f90[2] = 0.0f;
    f90[3] = 0.0f; f90[4] = 0.0f; f90[5] = 0.0f;
}

// ---------------------------------------------------------------------------------------------
// Shared widget/tray types used by the cSPVerbTray editor functions below.
#include <math.h>

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    Rectangle(const Rectangle& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) {}
    Rectangle& operator=(const Rectangle& r) {
        x1 = r.x1; y1 = r.y1; x2 = r.x2; y2 = r.y2;
        return *this;
    }
    float Width() const { return x2 - x1; }
    float Height() const { return y2 - y1; }
};
}  // namespace Math

namespace eastl {
class sp_vector_allocator {
 public:
    uint32_t mData[2];
    sp_vector_allocator() {}
};

template <typename T>
class vector {
 public:
    T* mpBegin;                       // +0x0
    T* mpEnd;                         // +0x4
    T* mpCapacity;                    // +0x8
    sp_vector_allocator mAllocator;   // +0xc
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int i) { return mpBegin[i]; }
    T* erase(T* first, T* last) { (void)first; (void)last; return first; }
};
}  // namespace eastl

template <typename T>
class AutoRefCount {
 public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T** AsOutParam() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct ColorRGBA {
    ColorRGBA(const ColorRGBA& c) : mR(c.mR), mG(c.mG), mB(c.mB), mA(c.mA) {}
    float mR, mG, mB, mA;
};

// Opaque property-list interfaces shared with the property helpers.
namespace App {
struct Property {
    char pad[0x12];
    uint16_t mnType;  // +0x12
};
}  // namespace App

class cPropertyList {
 public:
    virtual int AddRef();
    virtual int Release();
    virtual void q08(); virtual void q0c(); virtual void q10(); virtual void q14(); virtual void q18();
    virtual bool HasProperty(uint32_t id);                                 // +0x1c
    virtual void q20();
    virtual bool GetProperty(uint32_t id, App::Property*& result);          // +0x24
};
class IPropertyManager {
 public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c(); virtual void m10();
    virtual void m14(); virtual void m18(); virtual void m1c(); virtual void m20(); virtual void m24();
    virtual void m28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** out);  // +0x2c
};
IPropertyManager* PropertyManager();                                       // 0x0067de30
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* value);  // 0x006a12a0
bool GetPropertyArrayKey(cPropertyList* list, uint32_t id, int* count, void** keys);  // 0x006a0ae0

class cString {
 public:
    cString();                        // 0x006b5060
    ~cString();                       // 0x006b5240
    const wchar_t* c_str() const;     // 0x006b55c0
    uint32_t mData[5];
};
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString& out);   // 0x006a1360

// Widget interface: the retail slots used by the tray code.
class IEditorWidget {
 public:
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
    virtual void w08();                                    // +0x08
    virtual void w0c();                                    // +0x0c
    virtual void w10();                                    // +0x10
    virtual void w14();                                    // +0x14
    virtual void w18();                                    // +0x18
    virtual void w1c();                                    // +0x1c
    virtual void w20();                                    // +0x20
    virtual void Update(uint32_t dt);                      // +0x24
    virtual void w28();                                    // +0x28
    virtual void w2c();                                    // +0x2c
    virtual IEditorWidget* GetWindow();                    // +0x30
    virtual void w34();                                    // +0x34
    virtual const Math::Rectangle& GetArea();              // +0x38
    virtual void w3c();                                    // +0x3c
    virtual void w40();                                    // +0x40
    virtual void w44();                                    // +0x44
    virtual void w48();                                    // +0x48
    virtual void w4c();                                    // +0x4c
    virtual void w50();                                    // +0x50
    virtual void w54();                                    // +0x54
    virtual void w58();                                    // +0x58
    virtual void SetColor(uint32_t color);                 // +0x5c
    virtual void w60();                                    // +0x60
    virtual void w64();                                    // +0x64
    virtual void w68();                                    // +0x68
    virtual void SetArea(const Math::Rectangle& area);     // +0x6c
    virtual void w70();                                    // +0x70
    virtual void w74();                                    // +0x74
    virtual void w78();                                    // +0x78
    virtual void SetEnabled(int flag, bool enabled);       // +0x7c
    void SetVerbIconList(void* list);                      // 0x005e8470
};

struct TrayData {
    char pad00[0x20];
    float mScale;        // +0x20
    char pad24[8];
    ColorRGBA mColor;    // +0x2c
};

class IVerbTray {
 public:
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual IEditorWidget* GetWindow();                    // +0x30
    TrayData* GetData();                                   // 0x00a42730 (inlined getter)
    void SetVerbIconList(void* list);                      // 0x005e8470
    void SetMaxArea(const Math::Rectangle& area);          // 0x005e63b0
};

uint32_t ColorRGBAToU32(const ColorRGBA* color);           // 0x004580c0
extern const float kRealZero;                              // 0x01485378

struct ILegacyRef {
    virtual void l00();
    virtual void l04();
    virtual int Release();                                 // +0x08
};

class TrayPrimary {
 public:
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
    virtual void p08();                                    // +0x08
    virtual void* Cast(uint32_t type);                     // +0x0c
    virtual void p10();                                    // +0x10
    virtual void SetList(void* list);                      // +0x14
    virtual void Shutdown();                               // +0x18
    virtual void Update(uint32_t dt);                      // +0x1c
    virtual void p20();                                    // +0x20
    virtual void p24();                                    // +0x24
    virtual void Layout();                                 // +0x28
    virtual void p2c();                                    // +0x2c
};

class TrayRefCount {
 public:
    virtual void r00();                                    // +0x00
    virtual int AddRef();                                  // +0x04
    virtual int Release();                                 // +0x08
    virtual void r0c();                                    // +0x0c
    int mRefCount;
};

class TrayBase : public TrayPrimary, public TrayRefCount {
 public:
    ~TrayBase();                                           // 0x00605cb0
    eastl::vector<IEditorWidget*> mVerbIcons;              // +0x0c
    AutoRefCount<IEditorWidget> mWinParent;                // +0x20
    AutoRefCount<IEditorWidget> mWinVerbTray;              // +0x24
    char mPad28[0x54 - 0x28];                              // +0x28..+0x53
};

class VehicleTray : public TrayBase {
 public:
    ~VehicleTray();                                        // 0x005e0d80
    void Update(uint32_t dt);                              // 0x005e0e80
    void SetList(void* list);                              // 0x005e1020
    virtual void Layout();                                 // 0x005e12c0
    void LayoutAbilities(IEditorWidget* window, int flag); // 0x005e0930

    AutoRefCount<ILegacyRef> m54;                          // +0x54
    AutoRefCount<IEditorWidget> m58;                       // +0x58
    AutoRefCount<IEditorWidget> m5c;                       // +0x5c
    AutoRefCount<IEditorWidget> m60;                       // +0x60
    AutoRefCount<IEditorWidget> m64;                       // +0x64
    AutoRefCount<IEditorWidget> m68;                       // +0x68
    AutoRefCount<IEditorWidget> m6c;                       // +0x6c
    AutoRefCount<IEditorWidget> m70;                       // +0x70
    AutoRefCount<IEditorWidget> m74;                       // +0x74
    AutoRefCount<IEditorWidget> m78;                       // +0x78
    AutoRefCount<IEditorWidget> m7c;                       // +0x7c
    AutoRefCount<IEditorWidget> m80;                       // +0x80
    IVerbTray* m84;                                        // +0x84
    IVerbTray* m88;                                        // +0x88
    IVerbTray* m8c;                                        // +0x8c
    float m90;                                             // +0x90
    float m94;                                             // +0x94
    float m98;                                             // +0x98
    float m9c;                                             // +0x9c
    float ma0;                                             // +0xa0
    float ma4;                                             // +0xa4
    Math::Rectangle mMaxArea;                              // +0xa8
    Math::Rectangle mGutters;                              // +0xb8
};

// @ 0x005e0d80
VehicleTray::~VehicleTray()
{
}

// @ 0x005e0e80
void VehicleTray::Update(uint32_t dt)
{
    float seconds = (float)dt * 0.001f;
    int count = (int)mVerbIcons.size();
    for (int i = 0; i < count; i++)
        mVerbIcons[i]->Update(dt);

    if (m9c != m90) {
        float value = (m9c - m90) * seconds * 6.5f + m90;
        m90 = value;
        if (fabsf(value - m9c) < 0.001f)
            m90 = m9c;
    }
    if (ma0 != m94) {
        float value = (ma0 - m94) * seconds * 6.5f + m94;
        m94 = value;
        if (fabsf(value - ma0) < 0.001f)
            m94 = ma0;
    }
    if (ma4 != m98) {
        float value = (ma4 - m98) * seconds * 6.5f + m98;
        m98 = value;
        if (fabsf(value - ma4) < 0.001f)
            m98 = ma4;
    }
    Layout();
}

// @ 0x005e1020
void VehicleTray::SetList(void* list)
{
    if (list) {
        int count = (int)mVerbIcons.size();
        for (int i = 0; i < count; i++)
            mVerbIcons[i]->SetVerbIconList(list);

        if (m84->GetData() && m88->GetData() && m8c->GetData()) {
            m9c = m84->GetData()->mScale * 0.01f;
            ma0 = m88->GetData()->mScale * 0.01f;
            ma4 = m8c->GetData()->mScale * 0.01f;

            bool enabled0 = m84->GetData()->mScale == kRealZero;
            bool enabled1 = m88->GetData()->mScale == kRealZero;
            bool enabled2 = m8c->GetData()->mScale == kRealZero;

            ColorRGBA color0 = m84->GetData()->mColor;
            ColorRGBA color1 = m88->GetData()->mColor;
            ColorRGBA color2 = m8c->GetData()->mColor;

            m6c->SetColor(ColorRGBAToU32(&color0));
            m70->SetColor(ColorRGBAToU32(&color1));
            m74->SetColor(ColorRGBAToU32(&color2));
            m78->SetEnabled(1, enabled0);
            m7c->SetEnabled(1, enabled1);
            m80->SetEnabled(1, enabled2);
        }
        Layout();
    }
}

// @ 0x005e12c0
void VehicleTray::Layout()
{
    float origin = mMaxArea.x1;
    float range = (mGutters.x1 - mMaxArea.x2) - origin * 3.0f;
    float level0 = m98 * range + origin;
    float level1 = m90 * range + origin;
    float level2 = m94 * range + origin;
    float centerX = mMaxArea.y2;

    Math::Rectangle r0 = m68->GetArea();
    r0.y1 = r0.y2 - level0;
    m68->SetArea(r0);

    Math::Rectangle r1 = m64->GetArea();
    r1.y1 = r1.y2 - level0 - level1;
    m64->SetArea(r1);

    Math::Rectangle r2 = m60->GetArea();
    r2.y1 = r2.y2 - level0 - level1 - level2;
    m60->SetArea(r2);

    float bottom = r2.y1;
    float top = r1.y1;
    IVerbTray* tray = m84;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }

    bottom = r1.y1;
    top = r0.y1;
    tray = m88;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }

    bottom = r0.y1;
    top = r0.y2;
    tray = m8c;
    {
        IEditorWidget* window = tray->GetWindow();
        Math::Rectangle area = window->GetArea();
        float width = area.x2 - area.x1;
        float height = area.y2 - area.y1;
        area.y1 = (top - bottom) * 0.5f + bottom - height * 0.5f;
        area.y2 = area.y1 + height;
        area.x1 = centerX - width * 0.5f;
        area.x2 = area.x1 + width;
        tray->SetMaxArea(area);
    }
}

// @ 0x005e0930
// SP::cSPEditorVehicleAbilities::LayoutAbilities(IWindow*, bool) -- 900 bytes.
struct ResourceKey {
    uint32_t instanceID;   // +0x00
    uint32_t typeID;       // +0x04
    uint32_t groupID;      // +0x08
};

class IResource {
 public:
    virtual int AddRef();                  // +0x00
    virtual int Release();                 // +0x04
    virtual void r08();                    // +0x08
    virtual void* Cast(uint32_t type);     // +0x0c
};

namespace EA {
namespace ResourceMan {
class IResourceManager {
 public:
    virtual void m00(); virtual void m04(); virtual void m08();
    virtual bool GetResource(const ResourceKey* key, IResource** out, uint32_t unk0,
                             uint32_t unk1, uint32_t unk2, uint32_t unk3);  // +0x0c
};
IResourceManager* GetManager();            // 0x0067dcd0
}  // namespace ResourceMan
}  // namespace EA

// Ability record returned by the vehicle resource's ability list.
struct AbilityRecord {
    char pad00[0x18];
    float m18;             // +0x18
    char pad1c[8];         // +0x1c..+0x23
    uint32_t m24;          // +0x24
    char pad28[0x2c];      // +0x28..+0x53
    cString m54;           // +0x54
    char pad68[0x28];      // +0x68..+0x8f
    uint32_t m90;          // +0x90
    char pad94[0x20];      // +0x94..+0xb3
    ResourceKey mb4;       // +0xb4
};

void ApplyOwnerEntries(void** entries, void* owner);                               // 0x00433210
void CollectAbilityRecords(void* list, eastl::vector<void*>* out, void** entries);  // 0x004e7610

class AbilityLayoutData {
 public:
    float LayoutLine(IEditorWidget* window, const ResourceKey* key, float startY,
                     uint32_t value, const ResourceKey* subKey, cString* text,
                     float number);                        // 0x005e04d0
    void LayoutAbilities(IEditorWidget* window, bool alt);  // 0x005e0930

    ResourceKey mVehicleKey;              // +0x0c
    ResourceKey mTypeKey;                 // +0x18
    ResourceKey mLineKey;                 // +0x24
    ResourceKey mRowKey;                  // +0x30
    eastl::vector<void*> mPages;          // +0x3c
    char mPad4c[8];                       // +0x4c..+0x53
    uint32_t mAbilityPropId;              // +0x54
};

void AbilityLayoutData::LayoutAbilities(IEditorWidget* window, bool alt)
{
    (void)alt;
    float total = 0.0f;

    mPages.erase(mPages.mpBegin, mPages.mpEnd);

    AutoRefCount<cPropertyList> typeList;
    PropertyManager()->GetPropertyList(mTypeKey.instanceID, mTypeKey.groupID,
                                       typeList.AsOutParam());

    mPages.erase(mPages.mpBegin, mPages.mpEnd);

    int count = 0;
    void* keys = 0;
    if (GetPropertyArrayKey(typeList, mAbilityPropId, &count, &keys) && count > 0) {
        for (int i = 0; i < count; i++) {
            const uint32_t* entry = (const uint32_t*)keys + i * 3;
            AutoRefCount<cPropertyList> abilityList;
            if (PropertyManager()->GetPropertyList(entry[0], 0x1b68db4,
                                                   abilityList.AsOutParam())) {
                uint32_t subKey = 0;
                if (abilityList->HasProperty(0x626efe0))
                    GetPropertyAsKeyInstance(abilityList, 0x626efe0, &subKey);
                cString text;
                GetPropertyAsText(abilityList, 0x1b7c544, text);
                ResourceKey nullKey = { 0, 0, 0 };
                total += LayoutLine(window, &mLineKey, total, subKey, &nullKey, &text, -1.0f);
            }
        }
    }

    EA::ResourceMan::IResourceManager* manager = EA::ResourceMan::GetManager();
    if (mVehicleKey.instanceID) {
        AutoRefCount<IResource> resource;
        if (manager->GetResource(&mVehicleKey, resource.AsOutParam(), 0, 0, 0, 0)) {
            AutoRefCount<IResource> owner;
            owner = (IResource*)resource->Cast(0x3c609f8);
            void* entries[3] = { 0, 0, 0 };
            ApplyOwnerEntries(entries, (void*)owner.mpObject);
            eastl::vector<void*> records;
            CollectAbilityRecords(*(void**)((char*)owner.mpObject + 0x18), &records, entries);
            for (unsigned int i = 0; i < records.size(); i++) {
                AbilityRecord* record = (AbilityRecord*)records[i];
                if (record && record->m24 != 0x66904205)
                    total += LayoutLine(window, &mRowKey, total, record->m90, &record->mb4,
                                        &record->m54, record->m18);
            }
        }
    }

    Math::Rectangle area = window->GetArea();
    area.y1 += total;
    window->SetArea(area);
}
