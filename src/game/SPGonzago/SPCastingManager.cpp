// src/game/SPGonzago/SPCastingManager.cpp -- migrated from slice(s) s005f6df0, s0056df80, s004e12c0, s004c2100, s00448fa0, s00432830, s0040ccb0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCastingManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <intrin.h>
#include "SP/cResourceBase.h"
#include "SP/cIReleaseCallback.h"
#include "EA/ResourceMan/Key.h"
#include <math.h>
#include <xmmintrin.h>
#include "EA/Stopwatch.h"
#include "SP/cISPCreatureAnimWorld.h"
#include "SP/cSPEditorPaintTheme.h"
#include "cSPMatrix3.h"
#include "SP/cSPSwatch.h"
#include "cSPUILayeredObject.h"
#include "cSPUIModelsAndEffectsRenderer.h"
#include "SP/cSwatch3DView.h"

// ---- items of slice s0040ccb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Property {
public:
    float* GetValueFloat();          // 0x0041ea70
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12  (0xd = float)
};
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};
// ---- items of slice s0040ccb0 end

// ---- items of slice s00432830 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
struct EditorResource {
    virtual void v0();
    virtual void v1();
    virtual ~EditorResource() {}
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct BakeSprites : EditorResource {
    virtual void v0();
    virtual void v1();
};
struct Triple { int a, b, c; Triple() { a = 0; b = 0; c = 0; } };
struct AtomicInt {
    volatile long v;
    AtomicInt() { _InterlockedExchange(&v, 0); }
};
struct PropertyList_s0043_2830 : BakeSprites {
    AtomicInt     mRefCount;
    Triple        mList;
    PropertyList_s0043_2830();            // 0x004329E0
    int GetRefCount();         // 0x00432940
    int AddRef();              // 0x00432BE0
    virtual void v0();
    virtual void v1();
    virtual ~PropertyList_s0043_2830() {}   // 0x00432B10 (scalar deleting form)
};
struct Listener { virtual void Notify(void* src); };
struct RefIface {              // secondary base at +0x18
    virtual void r0();
    virtual void r1();
};
struct ResourceList : PropertyList_s0043_2830 {
    Listener* mListener;
    ResourceList() { mListener = 0; }
    int Release();             // 0x00432B50
    virtual void v0();
    virtual void v1();
};
struct SpriteGrid : ResourceList, RefIface {
    int  mWidth;
    int  mHeight;
    int  mState;
    int* mData;
    SpriteGrid(int w, int h);  // 0x00432960
    int ReleaseThunk();        // 0x00432C00
};
// ---- items of slice s00432830 end

// ---- items of slice s00448fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
float* sub_453880(float* tmp, const float* v, float* s);
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3 {
    Vector3 r[3];
    Matrix3() {}
    Matrix3(const Matrix3& other);              // 0x0041cb40 (out of line)
    Vector3& operator[](int i) { return r[i]; }
};
Vector3 operator-(const Vector3& v);                               // 0x00422020
Vector3& operator*=(Vector3& a, const float& s);                   // 0x0041dba0
Vector3 normalized_safe(const Vector3& v);                         // 0x00449c20 (value-returning view)
Vector3 operator*(const Vector3& a, const float& s);               // 0x0041dca0
Vector3 operator*(const Vector3& v, const Matrix3& m);             // 0x0041daf0
Vector3 operator+(const Vector3& a, const Vector3& b);             // 0x0041dc10
// ---- items of slice s00448fa0 end

// ---- items of slice s004c2100 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
namespace eastl {
struct WideFixedAlloc {
    uint32_t mOverflow;
    void* mpPoolBegin;
};
}
namespace eastl {
struct WideFixedStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    WideFixedAlloc mAllocator;

    void EnsureCapacity(uint32_t n);      // 0x004c26d0
    void SetCapacity(uint32_t n);         // 0x004c29c0
    void SwapHeap(WideFixedStr* other);   // 0x004c2ad0
};
}
// ---- items of slice s004c2100 end

// ---- items of slice s004e12c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropertyHolder {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual bool GetProperty(int key, void* out); // +0x24
};
void* __fastcall ResolveFloatValue(int v);  // 0x004e4230
// ---- items of slice s004e12c0 end

// ---- items of slice s0056df80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* EASTL_Allocate(void* pAllocator, size_t n, size_t alignment, int flags); // 0x42dee0
namespace eastl {
  class allocator_s0056_df80 {
  public:
    const char* mpName;
    int         mFlags;
    void* allocate(size_t n, size_t alignment, size_t offset) { return EASTL_Allocate(this, n, alignment, offset); }
    void  deallocate(void* p, size_t) { delete[] (char*)p; }
  };
}
namespace eastl {
  template<class T, class A> class basic_string_s0056_df80 {
  public:
    T* mpBegin; T* mpEnd; T* mpCapacity;
    struct { const char* mpName; } mAllocator;
    basic_string_s0056_df80(const basic_string_s0056_df80& x);
    void RangeInitialize(const T* pBegin, const T* pEnd);              // 0x423820
  };
}
namespace eastl {
  template<class T, class A> basic_string_s0056_df80<T,A>::basic_string_s0056_df80(const basic_string_s0056_df80& x)
    : mpBegin(0), mpEnd(0), mpCapacity(0)
  {
    RangeInitialize(x.mpBegin, x.mpEnd);
  }
}
namespace SP {
namespace Traits {
  using namespace eastl;
}
}
// ---- items of slice s0056df80 end


// @ 0x0040cf10
bool GetFloatProperty(PropertyList* list, uint32_t propertyID, float& result)
{
    Property* pProp;
    float* pValue;   // unused; keeps the original frame layout
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 0xd) {
        result = *pProp->GetValueFloat();
        return true;
    }
    return false;
}

// @ 0x00432b50
int ResourceList::Release()
{
    int n = _InterlockedExchangeAdd(&mRefCount.v, -2) - 2;
    if (n == 0) {
        _InterlockedExchange(&mRefCount.v, 2);
        delete this;
    } else if (n == 3 && mListener) {
        mListener->Notify(this);
    }
    return n;
}

// @ 0x00432be0
int PropertyList_s0043_2830::AddRef()
{
    return (_InterlockedExchangeAdd(&mRefCount.v, 2) + 2) >> 1;
}

// @ 0x00432c00
int SpriteGrid::ReleaseThunk()
{
    int pad1, pad2, pad3;
    return ResourceList::Release();
}

// @ 0x00449c20
float* normalized_safe(float* out, const float* v)
{
    float v1 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f;
    float p15 = sqrtf(v1);
    float n20[3];
    float* owner = sub_453880(n20, v, &p15);
    out[0] = owner[0];
    out[1] = owner[1];
    out[2] = owner[2];
    return out;
}

// @ 0x004c26d0
namespace eastl {
void WideFixedStr::EnsureCapacity(uint32_t n)
{
    uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
    uint32_t* p = (n < nSize) ? &nSize : &n;
    n = *p + 1;
    if ((uint32_t)(mpCapacity - mpBegin) < n)
        SetCapacity(n);
}
}  // namespace eastl

// @ 0x004e1c70
float GetPropertyFloat(PropertyHolder* pHolder, int key, float defaultValue)
{
    float value;
    int dummy;
    if (pHolder != 0 && pHolder->GetProperty(key, &value))
        return *(float*)ResolveFloatValue(*(int*)&value);
    return defaultValue;
}

// @ 0x0056e2d0
template eastl::basic_string_s0056_df80<wchar_t, eastl::allocator_s0056_df80>::basic_string_s0056_df80(const eastl::basic_string_s0056_df80<wchar_t, eastl::allocator_s0056_df80>&)
;

