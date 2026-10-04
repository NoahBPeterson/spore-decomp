// slice s0059e360 (part b) — SP::cSPEditorVerbIconData (retail layout, 0xC4 bytes): destructor,
// implicit copy constructor / assignment and the vector<cSPEditorVerbIconData> helpers; plus
// vector<cSPUILayout>::erase. Module flags: /O2 /MD /Gy /TP /GS- (x87, no /arch).
#include "types.h"
#include <string.h>

typedef unsigned int size_t;

void operator delete[](void* p);   // 0x00F47380
inline void* operator new(size_t, void* p) { return p; }

namespace EA {

namespace COM {
class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IUnknown32() {}
};
}

template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mRefCount(0) {}
    RefCountVTemplate(const RefCountVTemplate&) : mRefCount(0) {}
    RefCountVTemplate& operator=(const RefCountVTemplate&) { return *this; }
    virtual ~RefCountVTemplate() {}
    T mRefCount;   // +0x4 (relative)
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
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
};

}  // namespace EA

namespace eastl {

struct allocator {};

template <typename T>
class basic_string {
public:
    T*        mpBegin;      // +0x0
    T*        mpEnd;        // +0x4
    T*        mpCapacity;   // +0x8
    allocator mAllocator;   // +0xc
    basic_string(const basic_string& x) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        RangeInitialize(x.mpBegin, x.mpEnd);
    }
    ~basic_string() { DeallocateSelf(); }
    basic_string& operator=(const basic_string& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    basic_string& assign(const T* pBegin, const T* pEnd);   // 0x00423650
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

struct sp_vector_allocator {
    uint32_t mData[2];
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};

template <typename T>
class vector {
public:
    T*                  mpBegin;
    T*                  mpEnd;
    T*                  mpCapacity;
    sp_vector_allocator mAllocator;
    ~vector();
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    T* erase(T* first, T* last);
};

template <typename T>
vector<T>::~vector()
{
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin)
        mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
}

struct copy_impl {
    template <typename T>
    static T* do_copy(T* first, T* last, T* result);   // 0x0059EDE0 (cSPUILayout instance)
};

template <typename T>
inline T* copy(T* first, T* last, T* result)
{
    return copy_impl::do_copy(first, last, result);
}

template <typename T>
T* vector<T>::erase(T* first, T* last)
{
    T* const position = eastl::copy(last, mpEnd, first);
    DoDestroyValues(position, mpEnd);
    mpEnd -= (last - first);
    return first;
}

template <typename T>
T* uninitialized_relocate_commit(T* first, T* last, T* dest)
{
    for (; first != last; ++first, ++dest)
        first->~T();
    return dest;
}

}  // namespace eastl

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

namespace SP {

class cString {
public:
    ~cString();                              // 0x006B5240 (folded)
    cString(const cString& x);               // 0x006B56F0
    cString& operator=(const cString& x);    // 0x006B5430
    uint32_t pad[5];
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};

struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA(const ColorRGBA& x) : r(x.r), g(x.g), b(x.b), a(x.a) {}
};

class cSPEditorVerbIconData : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
public:
    virtual int AddRef();
    virtual int Release();
    virtual ~cSPEditorVerbIconData();

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
    cString     mName;                // +0x54
    eastl::basic_string<wchar_t> mHotKeyString;   // +0x68
    int         mArrayIndex;              // +0x78
    int         mPreSpecifiedArrayIndex;  // +0x7c
    ResourceKey mIconKey;                 // +0x80
    ResourceKey mGroupKey;                // +0x8c
    ResourceKey mRolloverImage;           // +0x98
    ResourceKey mKeyA4;                   // +0xa4
    uint32_t    mB0;                      // +0xb0
    uint32_t    mB4;                      // +0xb4
    uint32_t    mB8;                      // +0xb8
    uint32_t    mBC;                      // +0xbc
    EA::AutoRefCount<cPropertyList> mPropList;    // +0xc0
};

class cSPUILayout {
public:
    virtual ~cSPUILayout();
    uint32_t pad[5];
};

}  // namespace SP

using namespace SP;

// @ 0x0059ed20
template cSPEditorVerbIconData* eastl::uninitialized_relocate_commit<cSPEditorVerbIconData>(
    cSPEditorVerbIconData*, cSPEditorVerbIconData*, cSPEditorVerbIconData*);

// @ 0x0059eec0
template eastl::vector<cSPEditorVerbIconData>::~vector();

// @ 0x0059efa0
cSPEditorVerbIconData::~cSPEditorVerbIconData()
{
}

// @ 0x0059f0e0
// (implicit) cSPEditorVerbIconData& cSPEditorVerbIconData::operator=(const cSPEditorVerbIconData&)
cSPEditorVerbIconData& AssignVerbIconData(cSPEditorVerbIconData& dst, const cSPEditorVerbIconData& src)
{
    return dst = src;
}

// @ 0x0059f2a0
// (implicit) cSPEditorVerbIconData::cSPEditorVerbIconData(const cSPEditorVerbIconData&)
void CopyConstructVerbIconData(void* p, const cSPEditorVerbIconData& src)
{
    new (p) cSPEditorVerbIconData(src);
}

// @ 0x0059f4a0
template cSPUILayout* eastl::vector<cSPUILayout>::erase(cSPUILayout*, cSPUILayout*);
