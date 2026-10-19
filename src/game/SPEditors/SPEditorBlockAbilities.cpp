// src/game/SPEditors/SPEditorBlockAbilities.cpp -- migrated from slice(s) s005a0510, s0059f510, s0059e360 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorBlockAbilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cISPEditorAbilityProvider.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPEditorAppEconomy.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorEconomy.h"
#include "SP/cString.h"
#include <xmmintrin.h>
#include "SP/cSPEditorVerbIconData.h"
#include <string.h>
#include "EA/Variant.h"
#include "SP/cSPEditorBlockAbilities.h"
#include "cSPUILayout.h"

// ---- items of slice s0059e360 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
    uint32_t instanceID;   // +0x0
    uint32_t typeID;       // +0x4
    uint32_t groupID;      // +0x8
};
namespace eastl {
struct sp_vector_allocator_s0059_e360 {
    uint32_t mData[2];
    sp_vector_allocator_s0059_e360() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
template <typename T>
class vector_s0059_e360 {
public:
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator_s0059_e360 mAllocator;   // +0xc
    vector_s0059_e360() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector_s0059_e360()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    T& operator[](size_t n) { return mpBegin[n]; }
    void resize(size_t n, const T& value);              // 0x004746C0 (int instance)
    T* DoInsertValue(T* position, const T& value);      // 0x00454EE0 (AutoRefCount<cSPEditorBlock> instance)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace eastl {
struct rbtree_node_base_s0059_e360 {
    rbtree_node_base_s0059_e360* mpNodeRight;
    rbtree_node_base_s0059_e360* mpNodeLeft;
    rbtree_node_base_s0059_e360* mpNodeParent;
    char              mColor;
};
}
namespace eastl {
struct uint_map {
    uint32_t         mCompare;    // +0x0 (empty less<>)
    rbtree_node_base_s0059_e360 mAnchor;     // +0x4
    uint32_t         mnSize;      // +0x14
    uint32_t         mAllocator;  // +0x18 (empty allocator)
    uint_map() : mAnchor(), mnSize(0) { reset(); }
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
};
}
namespace SP {
bool ReadAbilityList(eastl::uint_map* abilities, uint32_t propID);   // 0x004E5180
}
namespace SP {
class cISPEditorAbilityProvider_s0059_e360 {
public:
    virtual ~cISPEditorAbilityProvider_s0059_e360() {}
};
}
namespace SP {
class cRefCounted {
public:
    cRefCounted() : mnRefCount(0) {}
    virtual ~cRefCounted() {}
    int mnRefCount;
};
}
namespace SP {
class cSPEditorVehicleAbilities : public cISPEditorAbilityProvider_s0059_e360, public cRefCounted {
public:
    cSPEditorVehicleAbilities(ResourceKey vehicleKey, uint32_t abilityListPropID, uint32_t typeInstance,
                              uint32_t modelType, bool showStats);
    virtual ~cSPEditorVehicleAbilities();
    void SetVehicle(ResourceKey vehicleKey, uint32_t modelType);

    ResourceKey       mVehicleKey;          // +0xc
    ResourceKey       mTypeKey;             // +0x18
    eastl::vector_s0059_e360<int> mAbilityLines;       // +0x24
    eastl::uint_map   mAbilities;           // +0x38
    uint32_t          mAbilityListPropId;   // +0x54
    bool              mbHasAbilities;       // +0x58
    uint32_t          mModelType;           // +0x5c
    bool              mbShowStats;          // +0x60
    bool              mb61;                 // +0x61
    bool              mb62;                 // +0x62
    bool              mb63;                 // +0x63
};
}
// ---- items of slice s0059e360 end

// ---- items of slice s0059e360_b begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace COM {
class IUnknown32_s0059_e360__b {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IUnknown32_s0059_e360__b() {}
};
}
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0059_e360__b {
public:
    RefCountVTemplate_s0059_e360__b() : mRefCount(0) {}
    RefCountVTemplate_s0059_e360__b(const RefCountVTemplate_s0059_e360__b&) : mRefCount(0) {}
    RefCountVTemplate_s0059_e360__b& operator=(const RefCountVTemplate_s0059_e360__b&) { return *this; }
    virtual ~RefCountVTemplate_s0059_e360__b() {}
    T mRefCount;   // +0x4 (relative)
};
}
namespace EA {
template <typename T>
class AutoRefCount_s0059_e360__b {
public:
    T* mpObject;
    AutoRefCount_s0059_e360__b() : mpObject(0) {}
    AutoRefCount_s0059_e360__b(const AutoRefCount_s0059_e360__b& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0059_e360__b() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0059_e360__b& operator=(const AutoRefCount_s0059_e360__b& x) { return operator=(x.mpObject); }
    AutoRefCount_s0059_e360__b& operator=(T* pObject)
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
};
}
namespace eastl {
struct allocator_s0059_e360__b {};
}
namespace eastl {
template <typename T>
class basic_string_s0059_e360__b {
public:
    T*        mpBegin;      // +0x0
    T*        mpEnd;        // +0x4
    T*        mpCapacity;   // +0x8
    allocator_s0059_e360__b mAllocator;   // +0xc
    basic_string_s0059_e360__b(const basic_string_s0059_e360__b& x) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        RangeInitialize(x.mpBegin, x.mpEnd);
    }
    ~basic_string_s0059_e360__b() { DeallocateSelf(); }
    basic_string_s0059_e360__b& operator=(const basic_string_s0059_e360__b& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string_s0059_e360__b& assign(const T* pBegin, const T* pEnd);   // 0x00423650
    void AllocateSelf(size_t n);                              // 0x00429760
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    static T* CharStringUninitializedCopy(const T* pSource, const T* pSourceEnd, T* pDestination)
    {
        memcpy(pDestination, pSource, (size_t)(pSourceEnd - pSource) * sizeof(T));
        return pDestination + (pSourceEnd - pSource);
    }
};
}
namespace eastl {
struct sp_vector_allocator_s0059_e360__b {
    uint32_t mData[2];
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
template <typename T>
class vector_s0059_e360__b {
public:
    T*                  mpBegin;
    T*                  mpEnd;
    T*                  mpCapacity;
    sp_vector_allocator_s0059_e360__b mAllocator;
    ~vector_s0059_e360__b();
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    T* erase(T* first, T* last);
};
}
namespace eastl {
template <typename T>
vector_s0059_e360__b<T>::~vector_s0059_e360__b()
{
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}
}
namespace eastl {
struct copy_impl {
    template <typename T>
    static T* do_copy(T* first, T* last, T* result);   // 0x0059EDE0 (cSPUILayout instance)
};
}
namespace eastl {
template <typename T>
inline T* copy(T* first, T* last, T* result)
{
    return copy_impl::do_copy(first, last, result);
}
}
namespace eastl {
template <typename T>
T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    for (; first != last; ++first, ++dest)
        first->~T();
    return dest;
}
}
struct ResourceKey_s0059_e360__b { uint32_t instanceID, typeID, groupID; };
namespace SP {
class cString_s0059_e360__b {
public:
    ~cString_s0059_e360__b();                              // 0x006B5240 (folded)
    cString_s0059_e360__b(const cString_s0059_e360__b& x);               // 0x006B56F0
    cString_s0059_e360__b& operator=(const cString_s0059_e360__b& x);    // 0x006B5430
    uint32_t pad[5];
};
}
namespace SP {
class cPropertyList_s0059_e360__b {
public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA(const ColorRGBA& x) : r(x.r), g(x.g), b(x.b), a(x.a) {}
};
}
namespace SP {
class cSPEditorVerbIconData_s0059_e360__b : public EA::COM::IUnknown32_s0059_e360__b, public EA::RefCountVTemplate_s0059_e360__b<int> {
public:
    virtual int AddRef();
    virtual int Release();
    virtual ~cSPEditorVerbIconData_s0059_e360__b();

    bool        mUseDescription;      // +0xc
    bool        mShowLevel;           // +0xd
    bool        mShowHotKey;          // +0xe
    bool        mShowZeroLevel;       // +0xf
    bool        mb10;                 // +0x10
    bool        mb11;                 // +0x11
    int         mHotKeyProp;          // +0x14
    float       mLevel;               // +0x18
    float       mMaxLevel;            // +0x1c
    float       mf20;                 // +0x20
    int         mType;                // +0x24
    uint32_t    mAnimation;           // +0x28
    ColorRGBA   mColor;               // +0x2c
    uint32_t    m3c;                  // +0x3c
    uint32_t    m40;                  // +0x40
    uint32_t    m44;                  // +0x44
    uint32_t    m48;                  // +0x48
    bool        mb4c;                 // +0x4c
    bool        mb4d;                 // +0x4d
    uint32_t    mHotKeyID;            // +0x50
    cString_s0059_e360__b     mName;                // +0x54
    eastl::basic_string_s0059_e360__b<wchar_t> mHotKeyString;   // +0x68
    int         mArrayIndex;              // +0x78
    int         mPreSpecifiedArrayIndex;  // +0x7c
    ResourceKey_s0059_e360__b mIconKey;                 // +0x80
    ResourceKey_s0059_e360__b mGroupKey;                // +0x8c
    ResourceKey_s0059_e360__b mRolloverImage;           // +0x98
    ResourceKey_s0059_e360__b mKeyA4;                   // +0xa4
    uint32_t    mB0;                      // +0xb0
    uint32_t    mB4;                      // +0xb4
    uint32_t    mB8;                      // +0xb8
    uint32_t    mBC;                      // +0xbc
    EA::AutoRefCount_s0059_e360__b<cPropertyList_s0059_e360__b> mPropList;    // +0xc0
};
}
namespace SP {
class cSPUILayout {
public:
    virtual ~cSPUILayout();
    uint32_t pad[5];
};
}
template SP::cSPUILayout* eastl::vector_s0059_e360__b<SP::cSPUILayout>::erase(SP::cSPUILayout*, SP::cSPUILayout*);
// ---- items of slice s0059e360_b end

// ---- items of slice s0059f510 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPUILayout_s0059_f510 {
    char pad[0x18];
    cSPUILayout_s0059_f510();                 // 0x00810000
    ~cSPUILayout_s0059_f510();                // 0x00811fe0
    void Shutdown(int flag);       // 0x00811ad0
};
struct UILayoutVector {
    cSPUILayout_s0059_f510* mpBegin;
    cSPUILayout_s0059_f510* mpEnd;
    cSPUILayout_s0059_f510* mpCapacity;
    uint32_t     mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cSPUILayout_s0059_f510* erase(cSPUILayout_s0059_f510* first, cSPUILayout_s0059_f510* last);   // 0x0059f4a0
    void resize(uint32_t newSize);                               // 0x0059f950
};
struct cSPEditorBlockAbilities {
    char          pad[0x24];
    UILayoutVector mLayouts;    // +0x24
    void ShutdownLayouts();     // 0x0059f900
};
struct AbilityRec {
    void* mpObject;     // +0x0
    char  pad[0xc4 - 4];
};
struct AbilityVector {
    AbilityRec* mpBegin;
    AbilityRec* mpEnd;
    AbilityRec* mpCapacity;
    uint32_t    mAlloc[2];
    int EraseRange(AbilityRec* first, AbilityRec* last);   // 0x0059faa0
};
cSPUILayout_s0059_f510* ConstructLayout(cSPUILayout_s0059_f510* p, int arg);   // 0x00810020
void VectorInsertFill(UILayoutVector* v, cSPUILayout_s0059_f510* pos, uint32_t count, cSPUILayout_s0059_f510* value);  // 0x0059f510
AbilityRec* FindAbilitySlot(AbilityRec* a, AbilityRec* b, AbilityRec* c);  // 0x0059f740
struct VehicleAbilities {
    void* vptr0;      // +0x0
    void* vptr1;      // +0x4
    char  pad[0x61 - 0x8];
    unsigned char b61, b62, b63;
    int   m64;        // +0x64
    int   m68;        // +0x68
    int   m6c;        // +0x6c
    VehicleAbilities();
};
// ---- items of slice s0059f510 end

// ---- items of slice s005a0510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];   // 0x01667bac, EASTL's shared empty string
extern float kAbilityMargin;     // 0x0150f16c (2.0)
extern float kAbilityLevelPad;   // 0x0150f170 (16.0)
extern float kAbilityIconPad;    // 0x0150f174 (8.0)
extern float kAbilityRowPad;     // 0x0150f178 (6.0)
extern float kAbilityIconScale;  // 0x0150f17c (1.0)
namespace EA {
namespace ResourceMan {
struct Key_s005a_0510 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}
}
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
};
}
struct Image {
    uint32_t pad[7];
    int mWidth;   // +0x1c
    int mHeight;  // +0x20
};
struct ITextCaption {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetAutoSize(bool b);                                    // +0x14
    virtual void v18();
    virtual void v1c();
    virtual bool GetTextExtent(Math::Rectangle* out, int a, int b);      // +0x20
};
struct IStdDrawableBase0 {
    virtual void v00();
    uint32_t pad[2];
};
struct IStdDrawable {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* GetImage(int index);                                   // +0x10
};
struct cSPUIStdDrawable : IStdDrawableBase0, IStdDrawable {   // IStdDrawable at +0xc
    void SetImageColor(int index, uint32_t color);                     // 0x00831170
};
struct IDrawable {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual cSPUIStdDrawable* Cast(uint32_t type);                       // +0x0c
};
struct IWindow {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08();
    virtual ITextCaption* Cast(uint32_t type);                           // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual const Math::Rectangle& GetArea();                            // +0x34
    virtual const Math::Rectangle& GetRealArea();                        // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(const Math::Rectangle& area);             // +0x6c
    virtual void SetLayoutLocation(float x, float y);                    // +0x70
    virtual void SetLayoutSize(float w, float h);                        // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                          // +0x7c
    virtual void SetCaption(const wchar_t* caption);                     // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4();
    virtual IDrawable* GetDrawable();                                    // +0xa8
    virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(); virtual void vc0(); virtual void vc4(); virtual void vc8();
    virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void AddWindow(IWindow* w);                                  // +0xd8
    virtual void vdc(); virtual void ve0(); virtual void ve4(); virtual void ve8();
    virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);        // +0xf0
};
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(T* p) : mpObject(p) { if (p) p->AddRef(); }
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(T* p) {
        if (p) p->AddRef();
        T* old = mpObject;
        mpObject = p;
        if (old) old->Release();
        return *this;
    }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};
namespace SP {
struct cPropertyList_s005a_0510 {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                               // +0x1c 0x006a2470
};
}
namespace SP {
struct cString_s005a_0510 {
    uint32_t pad[5];
    cString_s005a_0510();                                                           // 0x006b5060
    ~cString_s005a_0510();                                                          // 0x006b5240
    const wchar_t* GetText();                                            // 0x006b55c0
};
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s005a_0510* p, uint32_t id, EA::ResourceMan::Key_s005a_0510* out);   // 0x006a1250
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s005a_0510* p, uint32_t id, uint32_t* out);       // 0x006a12a0
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005a_0510* p, uint32_t id, cString_s005a_0510* out);               // 0x006a1360
}
namespace SP {
uint32_t ColorRGBAToU32(const void* color);                                          // 0x004580c0
}
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() { mpBegin = gEmptyString16; mpEnd = gEmptyString16; mpCapacity = gEmptyString16 + 1; }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
    string16& sprintf(const wchar_t* fmt, ...);                          // 0x0041e050
};
namespace SP {
struct cSPEditorVerbIconData_s005a_0510 {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual ~cSPEditorVerbIconData_s005a_0510();                                    // +0x08
    virtual void* Cast(uint32_t type);                                   // +0x0c
    virtual void Init(cPropertyList_s005a_0510* p);                                 // +0x10 0x005e5470
    virtual void Shutdown();                                             // +0x14
    virtual void SetArrayIndex(int i);                                   // +0x18
    virtual void SetHotKey(int key);                                     // +0x1c 0x005e5c00
    virtual string16 GetName(bool includeLevel);                         // +0x20
    virtual string16 GetDescription();                                   // +0x24

    cSPEditorVerbIconData_s005a_0510& operator=(const cSPEditorVerbIconData_s005a_0510& o);    // 0x0059f0e0

    uint32_t pad04[2];
    bool mVerbIconUseDescription;          // +0x0c
    bool mVerbIconShowLevel;               // +0x0d
    bool mPaletteItemRolloverShowLevel;    // +0x0e
    bool mVerbIconRolloverShowLevel;       // +0x0f
    uint32_t pad10[2];
    float mVerbIconLevel;                  // +0x18
    float mVerbIconMaxLevel;               // +0x1c
    int field_20;                          // +0x20
    int mVerbIconCategory;                 // +0x24 (eVerbIconCategory)
    uint32_t mVerbIconRepresentativeAnimation;  // +0x28
    float mVerbIconColor[4];               // +0x2c
    uint32_t mVerbIconRolloverLevelImageID;     // +0x3c
    EA::ResourceMan::Key_s005a_0510 mVerbIconRolloverLevelLayoutID;  // +0x40
    bool mVerbIconRolloverShowIcon;        // +0x4c
    bool mVerbIconEnforceMaxLevel;         // +0x4d
    uint32_t pad50[16];
    uint32_t mVerbIconImageID;             // +0x90
    uint32_t mVerbIconTrayOverrideImageID; // +0x94
    uint32_t mVerbIconTraySmallCardOverrideImageID;  // +0x98
    EA::ResourceMan::Key_s005a_0510 mVerbIconLayout;        // +0x9c
    EA::ResourceMan::Key_s005a_0510 mVerbIconGameLayout;    // +0xa8
    EA::ResourceMan::Key_s005a_0510 mVerbIconStaticLayout;  // +0xb4
    cPropertyList_s005a_0510* mpPropList;             // +0xc0
};
}
namespace SP {
struct cSPEditorVerbIconArray {
    cSPEditorVerbIconData_s005a_0510* mpBegin;
    cSPEditorVerbIconData_s005a_0510* mpEnd;
    cSPEditorVerbIconData_s005a_0510* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t mBufferHeader;
    uint32_t mBuffer[32 * 0xc4 / 4];

    cSPEditorVerbIconArray() {
        mpBegin = (cSPEditorVerbIconData_s005a_0510*)mBuffer;
        mpEnd = (cSPEditorVerbIconData_s005a_0510*)mBuffer;
        mpCapacity = (cSPEditorVerbIconData_s005a_0510*)mBuffer + 32;
        mBufferHeader = 0;
    }
    ~cSPEditorVerbIconArray() {
        for (cSPEditorVerbIconData_s005a_0510* p = mpBegin; p < mpEnd; ++p)
            p->~cSPEditorVerbIconData_s005a_0510();
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    cSPEditorVerbIconData_s005a_0510& operator[](int i) { return mpBegin[i]; }
    cSPEditorVerbIconData_s005a_0510& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; mpEnd->~cSPEditorVerbIconData_s005a_0510(); }
};
}
namespace SP {
void BlockGetAbilities(cSPEditorVerbIconArray* out, const EA::ResourceMan::Key_s005a_0510* blockKey,
                       uint32_t imageGroup);                             // 0x0059fc60
}
struct cSPUILayout_s005a_0510 {
    uint32_t pad[6];
    cSPUILayout_s005a_0510();                                                       // 0x00810000 (folded)
    ~cSPUILayout_s005a_0510();                                                      // 0x00811fe0
    bool Init(const EA::ResourceMan::Key_s005a_0510* key, bool b, uint32_t group);  // 0x008120d0
    IWindow* FindWindowByID(uint32_t id, bool recursive);                // 0x008105b0
    void SetParentWin(IWindow* parent, bool b, uint32_t group);          // 0x008121b0
    void Shutdown(bool b);                                               // 0x00811ad0
};
struct cSPUILayoutVector {   // eastl::vector<cSPUILayout, sp_vector_allocator>
    cSPUILayout_s005a_0510* mpBegin;
    cSPUILayout_s005a_0510* mpEnd;
    cSPUILayout_s005a_0510* mpCapacity;
    cSPUILayout_s005a_0510* erase(cSPUILayout_s005a_0510* first, cSPUILayout_s005a_0510* last);           // 0x0059f4a0
    void resize(unsigned n);                                             // 0x0059f950
    cSPUILayout_s005a_0510& operator[](int i) { return mpBegin[i]; }
};
struct RBNodeBase {
    RBNodeBase* mpNodeRight;
    RBNodeBase* mpNodeLeft;
    RBNodeBase* mpNodeParent;
    char mColor;
};
struct RBIterator {
    RBNodeBase* mpNode;
    RBIterator() : mpNode(0) {}
    RBIterator(RBNodeBase* n) : mpNode(n) {}
    RBIterator(const RBIterator& x) : mpNode(x.mpNode) {}
    bool operator==(const RBIterator& x) const { return mpNode == x.mpNode; }
};
struct VerbCategoryMap {   // eastl::map<eVerbIconCategory, ...>
    uint32_t mCompare;
    RBNodeBase mAnchor;
    RBIterator find(const int& key);                                // 0x00e39fb0 (folded)
    RBIterator end() { return RBIterator(&mAnchor); }
};
namespace SPUIHelpers {
Image* GetImageFromTexture(uint32_t instance, uint32_t group, int a, int b);    // 0x008060d0
}
namespace SPUIHelpers {
Image* GetImageByID(uint32_t imageID);                                    // 0x00458de0
}
namespace SPUIHelpers {
char SetDrawableImage(IWindow* w, Image* img, int index);                       // 0x008068d0
}
namespace SPUIHelpers {
char SetImageIcon(IWindow* w, Image* img, int index);                           // 0x00806aa0
}
namespace SPUIHelpers {
void CenterWindowInArea(IWindow* w, const Math::Rectangle* r);                  // 0x00806d10
}
namespace SPUIHelpers {
IWindow* CreateChildImageWindow(IWindow* parent);                                    // 0x00806370
}
struct LocalizationParams {
    uint32_t pad[22];
    uint32_t mNumber;   // +0x58
};
extern LocalizationParams* g_pLocalizationParams;   // 0x015ee298
namespace SP {
struct cSPEditorBlockAbilities_s005a_0510 {
    void* vptr;
    uint32_t pad04[2];
    EA::ResourceMan::Key_s005a_0510 mBlockKey;              // +0x0c
    EA::ResourceMan::Key_s005a_0510 mAbilityLayoutKey;      // +0x18
    cSPUILayoutVector mAbilityLines;             // +0x24
    uint32_t pad30[2];
    VerbCategoryMap mVerbCategoryMap;            // +0x38
    uint32_t pad4c[3];
    bool mbFilterByCategory;                     // +0x58
    uint32_t mIconImageGroup;                    // +0x5c
    bool mbCheckCategories;                      // +0x60
    bool mbLevelAsNumber;                        // +0x61
    bool mbUseLevelTextProperty;                 // +0x62
    bool mbHideLockIfSingle;                     // +0x63

    void SortAbilities(cSPEditorVerbIconArray* abilities, VerbCategoryMap* categories);  // 0x0059f7c0
    void LayoutAbilities(IWindow* pParent, bool bUseAltProperties);                      // 0x005a0510
};  // namespace SP
}
// ---- items of slice s005a0510 end

// @ 0x0059ed20
template SP::cSPEditorVerbIconData_s0059_e360__b* eastl::uninitialized_relocate_commit<SP::cSPEditorVerbIconData_s0059_e360__b>( SP::cSPEditorVerbIconData_s0059_e360__b*, SP::cSPEditorVerbIconData_s0059_e360__b*, SP::cSPEditorVerbIconData_s0059_e360__b*)
;

// @ 0x0059efa0
SP::cSPEditorVerbIconData_s0059_e360__b::~cSPEditorVerbIconData_s0059_e360__b()
{
}

// @ 0x0059f030
SP::cSPEditorVehicleAbilities::cSPEditorVehicleAbilities(ResourceKey vehicleKey, uint32_t abilityListPropID, uint32_t typeInstance, uint32_t modelType, bool showStats)
{
    mVehicleKey         = vehicleKey;
    mModelType          = 0;
    mb61                = false;
    mb62                = true;
    mb63                = false;
    mAbilityListPropId  = abilityListPropID;
    mTypeKey.instanceID = typeInstance;
    mTypeKey.typeID     = 0x510a95b;
    mTypeKey.groupID    = 0x40464100;
    mbHasAbilities      = false;
    if (abilityListPropID != (uint32_t)-1 && mAbilities.mnSize == 0)
        mbHasAbilities = SP::ReadAbilityList(&mAbilities, abilityListPropID);
    mbShowStats = showStats;
    mModelType  = modelType;
}

// @ 0x0059f4a0
namespace eastl {
template <typename T> T* vector_s0059_e360__b<T>::erase(T* first, T* last)
{
    T* const position = eastl::copy(last, mpEnd, first);
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}
}  // namespace eastl

// @ 0x0059f510
void VectorInsertFill(UILayoutVector* v, cSPUILayout_s0059_f510* pos, uint32_t count, cSPUILayout_s0059_f510* value)
{
    (void)v; (void)pos; (void)count; (void)value;
}

// @ 0x0059f7c0
int SortAbilities(void* a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x0059f900
void cSPEditorBlockAbilities::ShutdownLayouts()
{
    UILayoutVector* v = &mLayouts;
    int n = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x18);
    if (n > 0) {
        int offset = 0;
        do {
            ((cSPUILayout_s0059_f510*)((char*)v->mpBegin + offset))->Shutdown(1);
            offset += 0x18;
        } while (--n != 0);
    }
    v->erase(v->mpBegin, v->mpEnd);
}

// @ 0x0059f950
void UILayoutVector::resize(uint32_t newSize)
{
    uint32_t cur = (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x18);
    if (cur < newSize) {
        char tmp[0x18];
        ConstructLayout((cSPUILayout_s0059_f510*)tmp, 0);
        VectorInsertFill(this, mpEnd, newSize - cur, (cSPUILayout_s0059_f510*)tmp);
        ((cSPUILayout_s0059_f510*)tmp)->~cSPUILayout_s0059_f510();
    } else {
        erase(mpBegin + newSize, mpEnd);
    }
}

// @ 0x0059f9e0
VehicleAbilities::VehicleAbilities()
{
    m64 = 2;
    b61 = 1;
    b62 = 0;
    b63 = 1;
    m68 = 0xf56d252d;
    m6c = 0x3c02fae0;
}

// @ 0x0059fa50
void* ScalarDeletingDtor(void* p, unsigned char flags)
{
    (void)flags;
    return p;
}

// @ 0x0059faa0
int AbilityVector::EraseRange(AbilityRec* first, AbilityRec* last)
{
    AbilityRec* p = FindAbilitySlot(first, mpEnd, last);
    AbilityRec* end = mpEnd;
    for (; p < end; p = (AbilityRec*)((char*)p + 0xc4)) {
        void** vtbl = *(void***)p->mpObject;
        void* fn = *(void**)((char*)vtbl + 8);
        (*(void(__thiscall**)(void*, int))fn)(p->mpObject, 0);
    }
    mpEnd = (AbilityRec*)((char*)mpEnd + (((char*)last - (char*)first) / 0xc4) * 0xc4);
    return (int)first;
}

// @ 0x005a0510
namespace SP {
void cSPEditorBlockAbilities_s005a_0510::LayoutAbilities(IWindow* pParent, bool bUseAltProperties)
{
    float y = 0.0f;
    const Math::Rectangle& parentArea = pParent->GetRealArea();
    float parentWidth = parentArea.x2 - parentArea.x1;

    cSPEditorVerbIconArray abilities;
    BlockGetAbilities(&abilities, &mBlockKey, mIconImageGroup);

    if (mbCheckCategories && mbFilterByCategory) {
        for (int i = (int)abilities.size() - 1; i >= 0; --i) {
            cSPEditorVerbIconData_s005a_0510& a = abilities[i];
            if (mVerbCategoryMap.find(a.mVerbIconCategory) == mVerbCategoryMap.end()) {
                switch (a.mVerbIconCategory) {
                case (int)0xe2654048:
                case (int)0x93a8cfc8:
                case (int)0xa09e2868:
                case (int)0x28ebaf02:
                    break;
                default:
                    a = abilities.back();
                    abilities.pop_back();
                    break;
                }
            }
        }
        SortAbilities(&abilities, &mVerbCategoryMap);
    }

    int count = (int)abilities.size();
    float totalHeight = 0.0f;
    mAbilityLines.erase(mAbilityLines.mpBegin, mAbilityLines.mpEnd);
    mAbilityLines.resize(count);

    float maxRowWidth = 0.0f;
    float maxIconWidth = 0.0f;
    float maxTextWidth = 0.0f;
    float maxLevelWidth = 0.0f;

    for (int i = 0; i < count; ++i) {
        mAbilityLines[i].Init(&mAbilityLayoutKey, false, 0x5b598fa);
        IWindow* rowWin = mAbilityLines[i].FindWindowByID(0x4c01bd5, true);
        Math::Rectangle rowArea = rowWin->GetRealArea();
        mAbilityLines[i].SetParentWin(pParent, true, 0x5b598fa);
        float rowWidth = rowArea.x2 - rowArea.x1;
        float rowHeight = rowArea.y2 - rowArea.y1;
        float baseRowHeight = rowHeight;

        cSPEditorVerbIconData_s005a_0510& a = abilities[i];

        // Icon image: a texture key, a key-instance property or the image ID.
        Image* img = 0;
        bool bTexture = false;
        if (a.mVerbIconRolloverShowIcon) {
            if (bUseAltProperties && a.mpPropList->HasProperty(0x6669c51)) {
                EA::ResourceMan::Key_s005a_0510 key;
                key.instanceID = 0;
                key.typeID = 0;
                key.groupID = 0;
                GetPropertyAsKey(a.mpPropList, 0x6669c51, &key);
                img = SPUIHelpers::GetImageFromTexture(key.instanceID, key.groupID, -1, -1);
                bTexture = true;
            } else if (a.mpPropList->HasProperty(0x668b0a0)) {
                uint32_t imageID = 0;
                GetPropertyAsKeyInstance(a.mpPropList, 0x668b0a0, &imageID);
                if (imageID == 0)
                    imageID = a.mVerbIconImageID;
                img = SPUIHelpers::GetImageByID(imageID);
            } else if (a.mVerbIconImageID != 0) {
                img = SPUIHelpers::GetImageByID(a.mVerbIconImageID);
            }
        }

        intrusive_ptr<IWindow> iconWin = mAbilityLines[i].FindWindowByID(0x4c01bbe, true);
        if (img == 0 || iconWin.get() == 0) {
            if (img == 0 && iconWin.get())
                iconWin->SetFlag(1, false);
            IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
            if (textWin)
                textWin->SetLayoutLocation(0.0f, textWin->GetRealArea().y1);
        } else {
            iconWin->SetFlag(1, true);
            intrusive_ptr<IWindow> iconLayoutWin;
            if (a.mVerbIconStaticLayout.instanceID != 0) {
                cSPUILayout_s005a_0510 layout;
                layout.Init(&a.mVerbIconStaticLayout, true, 0x5b598fa);
                iconLayoutWin = layout.FindWindowByID(0x902d3163, true);
            }
            if (iconLayoutWin.get()) {
                iconWin->AddWindow(iconLayoutWin.get());
                Math::Rectangle r = iconWin->GetRealArea();
                float w = r.x2 - r.x1;
                float h = r.y2 - r.y1;
                r.x1 = 0.0f;
                r.y1 = 0.0f;
                r.x2 = w;
                r.y2 = h;
                SPUIHelpers::CenterWindowInArea(iconLayoutWin.get(), &r);
                IWindow* iconImageWin = iconLayoutWin->FindWindowByID(0x6283c92, false);
                if (iconImageWin || (iconImageWin = iconLayoutWin->FindWindowByID(0x4976e19, false)) != 0) {
                    iconImageWin->SetFlag(0x10, true);
                    SPUIHelpers::SetImageIcon(iconImageWin, img, 0);
                }
            } else {
                SPUIHelpers::SetDrawableImage(iconWin.get(), img, 0);
            }
            const Math::Rectangle& ia = iconWin->GetRealArea();
            float iconWidth = ia.x2 - ia.x1;
            if (iconWidth > maxIconWidth)
                maxIconWidth = iconWidth;
        }

        // Texture icons are scaled to the image size and centered vertically.
        float iconOffset = 0.0f;
        if (iconWin.get() && bTexture && img) {
            const Math::Rectangle& ia = iconWin->GetRealArea();
            Math::Rectangle ir;
            ir.x1 = ia.x1;
            ir.y1 = ia.y1;
            ir.x2 = ia.x2;
            float iconHeight = ia.y2 - ia.y1;
            float imgHeight = (float)img->mHeight * kAbilityIconScale;
            ir.y1 = (ia.y2 + ia.y1) * 0.5f - imgHeight * 0.5f;
            ir.y2 = ir.y1 + imgHeight;
            ir.x2 = (float)img->mWidth * kAbilityIconScale + ir.x1;
            iconWin->SetLayoutArea(ir);
            const Math::Rectangle& na = iconWin->GetRealArea();
            float iconWidth = na.x2 - na.x1;
            if (iconWidth > maxIconWidth)
                maxIconWidth = iconWidth;

            IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
            if (textWin) {
                Math::Rectangle ta = textWin->GetRealArea();
                if (ir.y2 > ta.y2) {
                    ta.y2 = ir.y2;
                    textWin->SetLayoutArea(ta);
                }
                iconOffset = ir.x2 - textWin->GetRealArea().x1;
                rowWidth = iconOffset + rowWidth;
                textWin->SetLayoutLocation(ir.x2, textWin->GetRealArea().y1);
            }
            float h = kAbilityRowPad + (((ir.y2 - ir.y1) - iconHeight) * 0.5f + baseRowHeight);
            if (h > baseRowHeight)
                rowHeight = h;
        }

        // Caption text.
        IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
        if (textWin) {
            textWin->GetRealArea();
            const Math::Rectangle& ta0 = textWin->GetRealArea();
            float baseTextWidth = ta0.x2 - ta0.x1;
            if (bUseAltProperties && a.mpPropList->HasProperty(0x6669c7c)) {
                cString_s005a_0510 text;
                GetPropertyAsText(a.mpPropList, 0x6669c7c, &text);
                textWin->SetCaption(text.GetText());
            } else if (mbUseLevelTextProperty && a.mpPropList->HasProperty(0x6492b61)) {
                cString_s005a_0510 text;
                GetPropertyAsText(a.mpPropList, 0x6492b61, &text);
                textWin->SetCaption(text.GetText());
            } else if (a.mVerbIconUseDescription) {
                textWin->SetCaption(a.GetDescription().c_str());
            } else {
                textWin->SetCaption(a.GetName(false).c_str());
            }
            textWin->Cast(0xf15f4bd)->SetAutoSize(false);
            const Math::Rectangle& ta = textWin->GetRealArea();
            float textWidth = ta.x2 - ta.x1;
            if (textWidth + iconOffset >= parentWidth) {
                textWidth = parentWidth - iconOffset;
                const Math::Rectangle& tb = textWin->GetRealArea();
                textWin->SetLayoutSize(textWidth, tb.y2 - tb.y1);
            }
            textWin->Cast(0xf15f4bd)->SetAutoSize(true);
            if (textWidth > baseTextWidth)
                rowWidth = (textWidth - baseTextWidth) + rowWidth;
            float textBottom = textWin->GetRealArea().y2;
            textWin->GetRealArea();
            if (textWidth > maxTextWidth)
                maxTextWidth = textWidth;
            if (textBottom + kAbilityRowPad > rowHeight)
                rowHeight = textBottom + kAbilityRowPad;
        }

        IWindow* lockWin = mAbilityLines[i].FindWindowByID(0x64d2eee, true);
        if (lockWin)
            lockWin->SetFlag(1, !mbHideLockIfSingle || count > 1);

        // Level display.
        IWindow* levelWin = mAbilityLines[i].FindWindowByID(0x4c01bca, true);
        if (levelWin) {
            if (a.mVerbIconLevel > 0.0f && a.mPaletteItemRolloverShowLevel) {
                const Math::Rectangle& la = levelWin->GetRealArea();
                float baseLevelWidth = la.x2 - la.x1;
                float levelWidth = baseLevelWidth;
                if (a.mVerbIconRolloverLevelImageID != 0) {
                    // One pip per level, laid out left to right.
                    Image* pipImg = SPUIHelpers::GetImageByID(a.mVerbIconRolloverLevelImageID);
                    const Math::Rectangle& lb = levelWin->GetRealArea();
                    float centerY = (lb.y2 - lb.y1) * 0.5f;
                    float pipHeight = (float)pipImg->mHeight;
                    float pipWidth = (float)pipImg->mWidth;
                    float x = 0.0f;
                    for (int j = 0; (float)j < a.mVerbIconLevel; ++j) {
                        IWindow* pip = 0;
                        if (a.mVerbIconRolloverLevelLayoutID.instanceID != 0) {
                            cSPUILayout_s005a_0510 layout;
                            layout.Init(&a.mVerbIconRolloverLevelLayoutID, false, 0x5b598fa);
                            IWindow* w = layout.FindWindowByID(0x902d3163, true);
                            if (w) {
                                w->AddRef();
                                pip = w;
                            }
                            layout.Shutdown(true);
                            levelWin->AddWindow(pip);
                            IWindow* pipImageWin = pip->FindWindowByID(0x6283c92, false);
                            if (pipImageWin || (pipImageWin = pip->FindWindowByID(0x4976e19, false)) != 0) {
                                pipImageWin->SetFlag(0x10, true);
                                IDrawable* d = pipImageWin->GetDrawable();
                                if (d) {
                                    cSPUIStdDrawable* sd = d->Cast(0x53eb526);
                                    if (sd && sd->GetImage(0) && a.mpPropList->HasProperty(0x631704a))
                                        sd->SetImageColor(0, ColorRGBAToU32(a.mVerbIconColor));
                                }
                                SPUIHelpers::SetImageIcon(pipImageWin, pipImg, 0);
                            }
                            const Math::Rectangle& pa = pip->GetRealArea();
                            pipWidth = pa.x2 - pa.x1;
                            pipHeight = pa.y2 - pa.y1;
                        } else {
                            IWindow* w = SPUIHelpers::CreateChildImageWindow(levelWin);
                            if (w) {
                                w->AddRef();
                                pip = w;
                            }
                            SPUIHelpers::SetDrawableImage(pip, pipImg, -1);
                        }
                        Math::Rectangle pr;
                        pr.x1 = x;
                        pr.x2 = x + pipWidth;
                        pr.y1 = centerY - pipHeight * 0.5f;
                        pr.y2 = pr.y1 + pipHeight;
                        pip->SetLayoutArea(pr);
                        x = pr.x2;
                        pip->Release();
                    }
                    levelWidth = x;
                    levelWin->SetCaption(L"");
                } else {
                    if (mbLevelAsNumber) {
                        string16 s;
                        s.sprintf(L"%d", (int)a.mVerbIconLevel);
                        levelWin->SetCaption(s.c_str());
                    } else {
                        cString_s005a_0510 text;
                        g_pLocalizationParams->mNumber = (uint32_t)a.mVerbIconLevel;
                        intrusive_ptr<cPropertyList_s005a_0510> propList(a.mpPropList);
                        GetPropertyAsText(a.mpPropList, 0x62d00e7, &text);
                        levelWin->SetCaption(text.GetText());
                    }
                    Math::Rectangle extent;
                    if (levelWin->Cast(0xf15f4bd)->GetTextExtent(&extent, 0, 1))
                        levelWidth = extent.x2 - extent.x1;
                }
                if (levelWidth > maxLevelWidth)
                    maxLevelWidth = levelWidth;
                if (levelWidth > baseLevelWidth)
                    rowWidth = (levelWidth - baseLevelWidth) + rowWidth;
            } else {
                levelWin->SetCaption(gEmptyString16);
                const Math::Rectangle& la = levelWin->GetRealArea();
                rowWidth = rowWidth - (la.x2 - la.x1);
            }
        }

        if (rowWidth > maxRowWidth)
            maxRowWidth = rowWidth;
        totalHeight = rowHeight + totalHeight;
        rowArea.x1 = 0.0f;
        rowArea.y1 = y;
        rowArea.x2 = maxRowWidth;
        rowArea.y2 = rowHeight + y;
        rowWin->SetLayoutArea(rowArea);
        y = rowHeight + y;
    }

    float iconPad = maxIconWidth > 0.0f ? kAbilityIconPad : 0.0f;
    float levelPad = maxLevelWidth > 0.0f ? kAbilityLevelPad : 0.0f;
    float width = kAbilityMargin * 2.0f + levelPad + iconPad + maxLevelWidth + maxTextWidth + maxIconWidth;
    const Math::Rectangle& pa = pParent->GetRealArea();
    if (pa.x2 - pa.x1 > width)
        width = pa.x2 - pa.x1;

    // Stretch every row to the common width and right-align the level column.
    for (int i = 0; i < count; ++i) {
        IWindow* rowWin = mAbilityLines[i].FindWindowByID(0x4c01bd5, true);
        mAbilityLines[i].FindWindowByID(0x4c01bbe, true);
        IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
        IWindow* levelWin = mAbilityLines[i].FindWindowByID(0x4c01bca, true);
        Math::Rectangle r = rowWin->GetRealArea();
        r.x2 = r.x1 + width;
        rowWin->SetLayoutArea(r);
        if (textWin) {
            Math::Rectangle t = textWin->GetRealArea();
            float w = t.x2 - t.x1;
            t.x1 = iconPad + maxIconWidth;
            t.x2 = t.x1 + w;
            textWin->SetLayoutArea(t);
        }
        if (levelWin) {
            Math::Rectangle l = levelWin->GetRealArea();
            l.x2 = r.x2 - kAbilityMargin;
            l.x1 = l.x2 - maxLevelWidth;
            levelWin->SetLayoutArea(l);
        }
    }

    Math::Rectangle area = pParent->GetRealArea();
    area.x2 = area.x1 + width;
    area.y2 = area.y1 + totalHeight;
    pParent->SetLayoutArea(area);
}
}  // namespace SP
