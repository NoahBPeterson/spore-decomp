// slice s00599040 -- SP::cCollectableItems::LoadConfiguration and the SpaceInventory UI template
// helpers (layout class with cSPUIPropertyLayout base, cSPUILayout at +0xc, vptr field at +0xa8).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// Debug allocator used by the original for every heap object below.
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void  operator delete(void* p);                                             // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

namespace SP {

struct Rect {
    float left, top, right, bottom;
};

struct ResourceKey {
    unsigned instanceID;
    unsigned typeID;
    unsigned groupID;
};

// ---------------------------------------------------------------------------------------------
// UI windows
class IWindow;
class IWindowComponent {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual IWindow* GetWindow();                                           // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void GetTextBounds(Rect* bounds, int line, int flags);          // +0x20
};
class IWindow {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* GetComponent(unsigned id);                                // +0x0c
    virtual IWindow* GetParent();                                           // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Rect* GetArea();                                          // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetArea(const Rect* area);                                 // +0x6c
    virtual void v70();
    virtual void SetSize(float width, float height);                        // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                             // +0x7c
    virtual void SetCaption(const wchar_t* text);                           // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4();
    virtual void BringToFront(IWindow* child);                              // +0xe8
};

class cSPUILayout {
public:
    void* FindWindowByID(int id, int b);   // 0x008105b0
};

class cSPUILayoutManager {
public:
    void* GetWorldMainWindow(unsigned id);  // 0x00810620
};
cSPUILayoutManager* GetLayoutManager();     // 0x00805070

// ---------------------------------------------------------------------------------------------
class IRefCounted {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
};

namespace eastl {
class allocator { public: };
}

class cString {
public:
    uint32_t data[5];
    cString();                                                              // 0x006b5060
    ~cString();                                                             // 0x006b5240
    const wchar_t* c_str() const;                                          // 0x006b55c0
};

namespace EA {
template <typename T>
class AutoRefCount { public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}  // namespace EA

class Property {
public:
    char pad0[0x12];
    short mType;                                                            // +0x12
    float* GetFloat();                                                      // 0x0041ea70
    unsigned* GetUInt();                                                    // 0x0041ea00
};

class cPropertyList {
public:
    virtual void AddRef();                                                  // +0x00
    virtual void Release();                                                 // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual bool GetProperty(unsigned id, Property** out);                  // +0x24
};

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(unsigned instanceID, unsigned groupID,
                                 EA::AutoRefCount<cPropertyList>& out);    // +0x2c
};

cPropertyManager* PropertyManager();                                        // 0x0067de30
bool GetPropertyAsText(cPropertyList* list, unsigned id, cString& out);     // 0x006a1360
bool GetPropertyAsKey(cPropertyList* list, unsigned id, ResourceKey* out);  // 0x006a1250
bool GetPropertyAsIntArray(cPropertyList* list, unsigned id, unsigned* count,
                           unsigned** values);                              // 0x006a07d0

// Palette / palette cursor used by LoadConfiguration.
class cSPPalette {
public:
    virtual void Destroy();                                                 // +0x00
    virtual void AddRef();                                                  // +0x04
    virtual void Release();                                                 // +0x08
    char pad4[0x40 - 4];
    cSPPalette();                                                           // 0x005c5e30
    bool Init(const ResourceKey& key, unsigned type, unsigned a, unsigned b,
              unsigned c, int d, int modelType);                            // 0x005c6340
    void Shutdown();                                                        // 0x005c5c20
};

class cSPPaletteCursor {
public:
    virtual void Destroy();                                                 // +0x00
    virtual void AddRef();                                                  // +0x04
    virtual void Release();                                                 // +0x08
    char pad4[0x20 - 4];
    cSPPaletteCursor();                                                     // 0x005c7b80
    void SetPalette(cSPPalette* palette);                                   // 0x005c7bc0
    int First(unsigned* categoryId, int* indexInPage, int* pageIndex,
              int* categoryIndex);                                          // 0x005c7e80
    int Next(unsigned* categoryId, int* indexInPage, int* pageIndex,
             int* categoryIndex);                                           // 0x005c7e20
    void ReadText();                                                        // 0x00c2e4e0
};

class cSPPaletteItem {
public:
    char pad0[0xc];
    int mInstanceID;                                                        // +0x0c
    int mTypeID;                                                            // +0x10
    int mGroupID;                                                           // +0x14
};

struct UIntVector {
    unsigned* mpBegin;
    unsigned* mpEnd;
    void Resize(unsigned count);                                            // 0x004cd3c0
};

// out = p; if (out) out->AddRef();   (intrusive ref-count assignment helper)
struct RefCountSlot {
    void Assign(void* p);                                                   // 0x0061df40
};

// SPUI helpers
void* FUN_008061c0(void* layout, int id);                                   // 0x008061c0
char  FUN_00806230(void* key, void** out, int a, int width, int height);    // 0x00806230
char  FUN_008068d0(void* window, void* image, int a);                       // 0x008068d0

class cSpaceInventory {
public:
    char pad0[0xc];
    cSPUILayout mLayout;                    // +0x0c
    char pad10[0x78 - (0xc + sizeof(cSPUILayout))];
    Rect mArea;                             // +0x78
    Rect mTitleArea;                        // +0x88
    Rect mDescriptionArea;                  // +0x98
    void* mpA8;                             // +0xa8
    char padAc[0x6d5c - 0xac];
    UIntVector mStatusVector;               // +0x6d5c
    char pad6d64[0x6d74 - 0x6d64];
    int mField6d74;                         // +0x6d74
    float mField6d78;                       // +0x6d78
    float mField6d7c;                       // +0x6d7c

    bool FUN_00599440(int a, int b, int c);           // 0x00599440
    __declspec(noinline) bool LoadConfiguration(int a, int b);   // 0x00599040
    void FUN_00599460();                              // 0x00599460
    void* FUN_005994d0();                             // 0x005994d0
    void FUN_00599530();                              // 0x00599530
    void FUN_00599560();                              // 0x00599560
    bool FUN_005995d0();                              // 0x005995d0
    void FUN_00599730(void* a, void* b);              // 0x00599730
    __declspec(noinline) void FUN_005997f0(int a, int b, int c, int d, int e); // 0x005997f0
    void FUN_00599be0(int a);                         // 0x00599be0
    void FUN_00599c10(int a);                         // 0x00599c10

    bool AddCollectableItemInfo(int a, int b, int c, int d, int e, int f, int g); // 0x00598e90

    // external (not in this slice)
    void FUN_008286d0();                              // 0x008286d0
    void FUN_00828020(int a);                         // 0x00828020
    void FUN_00828010(float f);                       // 0x00828010
    void FUN_00828be0();                              // 0x00828be0
    void FUN_00827fc0(const wchar_t* s, int a);       // 0x00827fc0
    void FUN_008c87bc0(unsigned a);                   // 0x008c87bc0
    bool FUN_00828250();                              // 0x00828250
    void SetMaxCargoAmount(int a);
};

}  // namespace SP

using namespace SP;

volatile int g_dummySideEffect;
#define SIDE_EFFECT() (g_dummySideEffect = 1)

// @ 0x00599440
bool cSpaceInventory::FUN_00599440(int a, int b, int c)
{
    mField6d74 = c;
    LoadConfiguration(a, b);
    return true;
}

// @ 0x00599530
void cSpaceInventory::FUN_00599530()
{
    FUN_00828020(1);
    void* p = mpA8;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(p, 1, 1);
    }
}

// @ 0x00599560
void cSpaceInventory::FUN_00599560()
{
    FUN_00828020(0);
    void* p = mpA8;
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(p, 1, 0);
    }
}

// @ 0x00599be0
void cSpaceInventory::FUN_00599be0(int a)
{
    FUN_005997f0(a, 0xf865c777, 0x54d95160, 0x54d95161, 0x54d95162);
}

// @ 0x00599c10
void cSpaceInventory::FUN_00599c10(int a)
{
    FUN_005997f0(a, 0x449505af, 0xd4d959e0, 0xd4d959e1, 0xd4d959e2);
}

// @ 0x00599460
void cSpaceInventory::FUN_00599460()
{
    void* win = mLayout.FindWindowByID(0, 1);
    if (win) {
        void* x = ((void*(__thiscall*)(void*))(*(void***)win)[0x10 / 4])(win);
        if (x) {
            void* y = ((void*(__thiscall*)(void*))(*(void***)win)[0x10 / 4])(win);
            ((void(__thiscall*)(void*, void*))(*(void***)y)[0xdc / 4])(y, win);
        }
    }
    FUN_00828be0();
}

// @ 0x00599040
bool cSpaceInventory::LoadConfiguration(int a, int b)
{
    if (a != 0 && b != 0) {
        EA::AutoRefCount<cPropertyList> props;
        if (PropertyManager()->GetPropertyList(b, a, props = 0)) {
            unsigned count = 0;
            unsigned* values = 0;
            if (GetPropertyAsIntArray(props, 0x33265801, &count, &values)) {
                mStatusVector.Resize(count);
                for (unsigned i = 0; i < count; ++i)
                    mStatusVector.mpBegin[i] = values[i];
            }

            Property* prop = 0;
            if (props && props->GetProperty(0x86236d5f, &prop) && prop->mType == 0xd)
                mField6d78 = *prop->GetFloat();
            if (props && props->GetProperty(0xfa56f65c, &prop) && prop->mType == 0xd)
                mField6d7c = *prop->GetFloat();

            unsigned paletteType = 0;
            unsigned paletteId = 0;
            unsigned paletteFilter = 0;
            if (props && props->GetProperty(0x52d669e8, &prop) && prop->mType == 0xa)
                paletteType = *prop->GetUInt();
            if (props && props->GetProperty(0x23a13b31, &prop) && prop->mType == 0xa)
                paletteId = *prop->GetUInt();
            if (props && props->GetProperty(0xad7cdb56, &prop) && prop->mType == 0xa)
                paletteFilter = *prop->GetUInt();

            if (paletteType != 0 && paletteId != 0) {
                EA::AutoRefCount<cPropertyList> paletteProps;
                if (PropertyManager()->GetPropertyList(paletteType, *(unsigned*)0x0150d514, paletteProps = 0)) {
                    ResourceKey key;
                    key.instanceID = 0;
                    key.typeID = 0;
                    key.groupID = 0;
                    if (GetPropertyAsKey(paletteProps, 0xf5cbe065, &key)) {
                        cSPPalette* palette = new ("Editor", 0, 0, 0, 0) cSPPalette();
                        ((RefCountSlot*)&palette)->Assign(palette);
                        if (palette) {
                            if (!palette->Init(key, paletteId, 0, 0, 0, 0, 0)) {
                                palette->Release();
                            } else {
                                cSPPaletteCursor* cursor = new ("Editor", 0, 0, 0, 0) cSPPaletteCursor();
                                ((RefCountSlot*)&cursor)->Assign(cursor);
                                if (cursor) {
                                    cursor->SetPalette(palette);
                                    unsigned categoryId;
                                    int indexInPage;
                                    int pageIndex;
                                    int categoryIndex;
                                    cSPPaletteItem* item =
                                        (cSPPaletteItem*)cursor->First(&categoryId, &indexInPage,
                                                                       &pageIndex, &categoryIndex);
                                    while (item) {
                                        if (paletteFilter == 0 || paletteFilter == categoryId)
                                            AddCollectableItemInfo(item->mInstanceID, item->mTypeID,
                                                                   item->mGroupID, (int)categoryId,
                                                                   pageIndex, indexInPage, categoryIndex);
                                        item = (cSPPaletteItem*)cursor->Next(&categoryId, &indexInPage,
                                                                             &pageIndex, &categoryIndex);
                                    }
                                }
                                cursor->ReadText();
                                if (cursor)
                                    cursor->Release();
                                palette->Shutdown();
                                palette->Release();
                            }
                        }
                    }
                }
            }
            return true;
        }
    }

    mStatusVector.Resize(4);
    unsigned* values = mStatusVector.mpBegin;
    values[0] = 5;
    values[1] = 5;
    values[2] = 5;
    values[3] = 5;
    mField6d78 = *(float*)0x01485720;
    mField6d7c = *(float*)0x01485720;
    return true;
}

// @ 0x005994d0
void* cSpaceInventory::FUN_005994d0()
{
    FUN_008286d0();
    *(void**)this = (void*)0x013f6374;
    *(void**)((char*)this + 4) = (void*)0x013f6364;
    mpA8 = 0;
    FUN_00827fc0(L"TraitSuperPowerRollover", 0x40464100);
    FUN_008c87bc0(0);
    FUN_00828010(*(float*)0x01488874);
    return this;
}

// @ 0x005995d0
bool cSpaceInventory::FUN_005995d0()
{
    bool ok = FUN_00828250();
    if (!ok)
        return false;

    void* root = mLayout.FindWindowByID(0, 1);
    if (root) {
        FUN_00828020(0);
        if (mpA8) {
            void** vt = *(void***)mpA8;
            ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(mpA8, 1, 0);
        }
        cSPUILayoutManager* manager = GetLayoutManager();
        void* world = manager->GetWorldMainWindow(0x5b598f6);
        ((void(__thiscall*)(void*, void*))(*(void***)world)[0xd8 / 4])(world, root);

        mArea = *((const Rect*)((void*(__thiscall*)(void*))(*(void***)root)[0x38 / 4])(root));

        void* titleWindow = mLayout.FindWindowByID(0x331cc0e, 1);
        if (titleWindow)
            mTitleArea = *((const Rect*)((void*(__thiscall*)(void*))(*(void***)titleWindow)[0x38 / 4])(titleWindow));

        void* descWindow = mLayout.FindWindowByID(0x331cc0f, 1);
        if (descWindow)
            mDescriptionArea = *((const Rect*)((void*(__thiscall*)(void*))(*(void***)descWindow)[0x38 / 4])(descWindow));
    }

    void* window = mLayout.FindWindowByID(0x680d540, 1);
    void* old = mpA8;
    if (window != old) {
        if (window)
            ((void(__thiscall*)(void*))(*(void***)window)[0])(window);
        mpA8 = window;
        if (old)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
    return ok;
}

// @ 0x00599730
void cSpaceInventory::FUN_00599730(void* window, void* keyPtr)
{
    ResourceKey* key = (ResourceKey*)keyPtr;
    void* image = FUN_008061c0(&mLayout, key->instanceID);
    if (image) {
        ((void(__thiscall*)(void*))(*(void***)image)[0])(image);
    } else {
        const Rect* area = (const Rect*)((void*(__thiscall*)(void*))(*(void***)window)[0x34 / 4])(window);
        int width = (int)(area->right - area->left);
        int height = (int)(area->bottom - area->top);
        FUN_00806230(key, &image, 0, width, height);
    }
    FUN_008068d0(window, image, 0);
    if (image)
        ((void(__thiscall*)(void*))(*(void***)image)[1])(image);
}

// @ 0x005997f0
void cSpaceInventory::FUN_005997f0(int a, int b, int c, int d, int e)
{
    void* root = mLayout.FindWindowByID(0, 1);
    Rect area = mArea;
    float height = mDescriptionArea.bottom - mDescriptionArea.top;
    EA::AutoRefCount<cPropertyList> props;
    if (root)
        ((void(__thiscall*)(void*, const Rect*))(*(void***)root)[0x6c / 4])(root, &mArea);

    void* descWindow = mLayout.FindWindowByID(0x331cc0f, 1);
    void* iconBackground = mLayout.FindWindowByID(0x4d982f8, 1);
    if (descWindow && iconBackground) {
        Rect descArea = *((const Rect*)((void*(__thiscall*)(void*))(*(void***)descWindow)[0x38 / 4])(descWindow));
        descArea.top = ((const Rect*)((void*(__thiscall*)(void*))(*(void***)iconBackground)[0x38 / 4])(iconBackground))->bottom;
        ((void(__thiscall*)(void*, const Rect*))(*(void***)descWindow)[0x6c / 4])(descWindow, &descArea);
        height = descArea.bottom - descArea.top;
    }

    if (PropertyManager()->GetPropertyList(a, b, props = 0)) {
        void* window;
        if ((window = mLayout.FindWindowByID(0x6133600, 1)) != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)window)[0x7c / 4])(window, 1, 0);
        if ((window = mLayout.FindWindowByID(0x6133601, 1)) != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)window)[0x7c / 4])(window, 1, 0);
        if ((window = mLayout.FindWindowByID(0x6133602, 1)) != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)window)[0x7c / 4])(window, 1, 0);
        if ((window = mLayout.FindWindowByID(0x6133603, 1)) != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)window)[0x7c / 4])(window, 1, 0);
        if ((window = mLayout.FindWindowByID(0x4d97710, 1)) != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)window)[0x7c / 4])(window, 1, 0);

        void* titleWindow = mLayout.FindWindowByID(0x331cc0e, 1);
        if (titleWindow) {
            cString title;
            GetPropertyAsText(props, c, title);
            ((void(__thiscall*)(void*, const wchar_t*))(*(void***)titleWindow)[0x80 / 4])(titleWindow, title.c_str());
            Rect bounds;
            IWindowComponent* component =
                (IWindowComponent*)((void*(__thiscall*)(void*, unsigned))(*(void***)titleWindow)[0x0c / 4])(titleWindow, 0xf15f4bd);
            component->GetTextBounds(&bounds, 0, 0);
            float textWidth = bounds.right - bounds.left;
            float titleWidth = mTitleArea.right - mTitleArea.left;
            if (textWidth > titleWidth)
                area.right += textWidth - titleWidth;
        }

        if (root)
            ((void(__thiscall*)(void*, const Rect*))(*(void***)root)[0x6c / 4])(root, &area);

        void* iconWindow = mLayout.FindWindowByID(0x677f65f, 1);
        if (iconWindow) {
            ResourceKey key;
            key.instanceID = 0;
            key.typeID = 0;
            key.groupID = 0;
            GetPropertyAsKey(props, e, &key);
            if (key.instanceID)
                FUN_00599730(iconWindow, &key);
        }

        if (descWindow) {
            cString description;
            GetPropertyAsText(props, d, description);
            ((void(__thiscall*)(void*, const wchar_t*))(*(void***)descWindow)[0x80 / 4])(descWindow, description.c_str());
            Rect bounds;
            IWindowComponent* component =
                (IWindowComponent*)((void*(__thiscall*)(void*, unsigned))(*(void***)descWindow)[0x0c / 4])(descWindow, 0xf15f4bd);
            component->GetTextBounds(&bounds, 1, 0);
            area.bottom += (bounds.bottom - bounds.top) - height;
        }
    }

    if (root)
        ((void(__thiscall*)(void*, const Rect*))(*(void***)root)[0x6c / 4])(root, &area);
}
