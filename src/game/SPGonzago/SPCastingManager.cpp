// src/game/SPGonzago/SPCastingManager.cpp -- migrated from slice(s) s00622f20, s004c10e0, s004c0410, s00472b80, s005f6df0, s0056df80, s004e12c0, s004c2100, s00448fa0, s00432830, s0040ccb0 by tools/migrate/rewrite.py
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
#include <stdarg.h>
#include "SP/cPropertyList.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/XHTML/DOM/Document.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/UTFWin/MultiHeapObject.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "SP/cPollinator.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cStringTokenTranslator.h"

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
extern const float kZero;                                          // 0x01485378
float* sub_453880(float* tmp, const float* v, float* s);
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct V3x : Vector3 {                          // Vector3 whose copy ctor is out of line (0x004098a0)
    V3x(const V3x& v);
};
struct Matrix3 {
    Vector3 r[3];
    Matrix3() {}
    Matrix3(const Matrix3& other);              // 0x0041cb40 (out of line)
    Vector3& operator[](int i) { return r[i]; }
};
struct cSPMatrix3_s0044_8fa0 : Matrix3 {                   // ctors are out of line
    cSPMatrix3_s0044_8fa0();                               // 0x00402ab0
    cSPMatrix3_s0044_8fa0(const cSPMatrix3_s0044_8fa0& o);            // 0x00449cc0
};
Vector3 operator-(const Vector3& v);                               // 0x00422020
Vector3& operator*=(Vector3& a, const float& s);                   // 0x0041dba0
Vector3 Normalize(const Vector3& v);                               // 0x00436ce0
Vector3 normalized_safe(const Vector3& v);                         // 0x00449c20 (value-returning view)
Vector3 Cross(const Vector3& a, const Vector3& b);                 // 0x00454c00
cSPMatrix3_s0044_8fa0 MakeOrientation(const Vector3& fwd, const Vector3& up);    // 0x004a89e0
extern const Vector3 kAxis15d23f0, kAxis15d2478, kAxis15d23a8;
bool operator!=(const Vector3& a, const Vector3& b);               // 0x0041dd30
Vector3 operator*(const Vector3& a, const float& s);               // 0x0041dca0
Vector3 operator*(const Vector3& v, const Matrix3& m);             // 0x0041daf0
Vector3 operator+(const Vector3& a, const Vector3& b);             // 0x0041dc10
template <class T>
struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
template <class T>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator;
    bool empty();                                                  // 0x00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(size_t i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
struct __declspec(align(16)) hkVector4_s0044_8fa0 {
    float x, y, z, w;
    hkVector4_s0044_8fa0(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
class hkRigidBody_s0044_8fa0 { public: void setPosition(const hkVector4_s0044_8fa0& p); };      // 0x01087820
struct XformRec {
    uint16_t flags; uint16_t version; Vector3 pos;
};
struct cMWModel {
    char pad0[8];
    XformRec mXform;
};
struct cIModelWorld {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
virtual void v42();
virtual void v43();
virtual void v44();
virtual void v45();
virtual void v46();
virtual void v47();
virtual void v48();
virtual void v49();
virtual void v50();
virtual void v51();
virtual void v52();
virtual void v53();
virtual void v54();
virtual void v55();
virtual void v56();
virtual void v57();
virtual void v58();
virtual void v59();
virtual void v60();
virtual void v61();
virtual void v62();
virtual void v63();
virtual void v64();
virtual void v65();
virtual void v66();
    virtual bool v67(cMWModel* m, void* bbox);   // +0x10c
    virtual bool v68(cMWModel* m, void* bbox);   // +0x110
};
struct cPropertyList {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool HasProperty(uint32_t id);
};
struct cSPEditorModel {
    bool IsSymmetryEnabled();                                      // 0x004adc40
};
struct cSPEditorHandle {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Update();                                         // +0x14
};
struct cSPBoundingBox_s0044_8fa0 {  // 0x00409c00
    cSPBoundingBox_s0044_8fa0();
    Vector3 mMin, mMax;
    void Reset();
};
struct cSPEditorBlock {
    char pad00[0x0c];
    AutoRefCount<cPropertyList> mPropList;                         // +0x0c
    AutoRefCount<cMWModel> mModel;                                 // +0x10
    char pad14[0x04];
    AutoRefCount<cIModelWorld> mModelWorld;                        // +0x18
    char pad1c[0x28 - 0x1c];
    cSPEditorModel* mEditorModel;                                  // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                                             // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 mMat60;                                                // +0x60
    char pad84[0xa8 - 0x84];
    Matrix3 mOrientation;                                          // +0xa8
    char padcc[0x154 - 0xcc];
    AutoRefCount<cSPEditorHandle> mRotationRingHandles[3];         // +0x154
    AutoRefCount<cSPEditorHandle> mRotationBallHandle;             // +0x160
    char pad164[0x18c - 0x164];
    hkRigidBody_s0044_8fa0* mPhysicsBody;                                     // +0x18c
    char pad190[0x1d8 - 0x190];
    float mScale;                                                  // +0x1d8
    char pad1dc[0x3e0 - 0x1dc];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;                  // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    AutoRefCount<cSPEditorHandle> mField3ec;                       // +0x3ec
    AutoRefCount<cMWModel> mField3f0;                              // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    Vector3 mOffset40c;                                            // +0x40c
    char pad418[0x6cc - 0x418];
    vector<AutoRefCount<cSPEditorHandle> > mMorphHandles;          // +0x6cc
    char pad6dc[0xdc8 - 0x6dc];
    bitset<60> mFlags;                                             // +0xdc8

    void SetBooleanAttribute(int index, bool value);               // 0x00435a10
    Vector3 GetPosition();                                         // 0x00436210
    void ApplyOrientation(Matrix3 m, bool flag);                   // 0x0044a0e0
    void UpdateAfterClone();                                       // 0x0044a070

    void A48fa0(Vector3 pos, bool updatePhysics);
    void A49420(const Matrix3& m, bool flag);
    cSPMatrix3_s0044_8fa0 A494b0(Vector3 dir);
    void A49ce0();
    void A49d40(cSPBoundingBox_s0044_8fa0* bbox);
};
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

// ---- items of slice s00472b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char* p);                          // inlined (intrinsic)
#pragma intrinsic(strlen)
void* EASTL_Allocate(void* alloc, uint32_t n, uint32_t align, uint32_t flags); // @ 0x0042dee0
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct sp_vector_allocator {
    uint32_t mDummy;
    void deallocate(void* p, uint32_t) { void* q = p; EASTL_allocator_deallocate(q); }
};
struct Counted { void Release(); };                                  // 0x40f360
struct AutoRefCount_s0047_2b80 {
    Counted* mpObject;
    AutoRefCount_s0047_2b80() : mpObject(0) {}
    ~AutoRefCount_s0047_2b80() { if (mpObject) mpObject->Release(); }
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
template<class T> struct ResizeHoles { enum { N = 6 }; };
template<> struct ResizeHoles<AutoRefCount_s0047_2b80> { enum { N = 15 }; };
template<class T> T* uninitialized_copy_ptr(T* first, T* last, T* dest);   // out of line
template<class T> inline void destruct(T* first, T* last)
{ for (; first < last; ++first) first->~T(); }
template<class T> inline T* CopyRef(T* first, T* last, T* dest)
{
    const bool from = false, left = false, pos = false;
    { uint32_t unused[2]; }
    T* pSource = first;
    T* pDest = dest;
    for (; pSource != last; ++pSource, ++pDest) *pDest = *pSource;
    return pDest;
}
template<class T, int A>
struct vector_s0047_2b80 {
    T* mpBegin; T* mpEnd; T* mpCapacity; sp_vector_allocator mAllocator;

    T* DoAllocate(uint32_t n) { return n ? (T*)EASTL_Allocate(&mAllocator, n * sizeof(T), A, 0) : 0; }
    void DoFree(T* p, uint32_t n) { if (p && ((int*)p)[-1]) mAllocator.deallocate(p, n); }

    void DoInsertValues(T* pos, uint32_t n, const T& v);   // out of line
    void erase(T* first, T* last);                         // out of line 0x00621f50
    void insert(T* pos, uint32_t n, const T& v) { DoInsertValues(pos, n, v); }

    vector_s0047_2b80& operator=(const vector_s0047_2b80& x);
    T* DoRealloc(uint32_t n, T* first, T* last);           // out of line
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void reserve(uint32_t n);
    void resize(uint32_t n);
};
template<class T, int A>
vector_s0047_2b80<T,A>& vector_s0047_2b80<T,A>::operator=(const vector_s0047_2b80& x)
{
    if (&x != this) {
        const uint32_t n = x.size();
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            T* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            ScratchSlots<9>();
            destruct(mpBegin, mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpBegin = pNewData;
            mpCapacity = mpBegin + n;
        } else if (n > size()) {
            CopyRef(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            uninitialized_copy_ptr(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            ScratchSlots<8>();
        } else {
            T* const position = CopyRef(x.mpBegin, x.mpEnd, mpBegin);
            destruct(position, mpEnd);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}
template<class T, int A>
void vector_s0047_2b80<T,A>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        T* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        destruct(mpBegin, mpEnd);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        const int nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}
template<class T, int A>
void vector_s0047_2b80<T,A>::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), T());
        ScratchSlots<ResizeHoles<T>::N>();
    } else
        erase(mpBegin + n, mpEnd);
}
struct Matrix33 { float m[12]; };
struct Quaternion { float x, y, z, w; };
// ---- items of slice s00472b80 end

// ---- items of slice s004c0410 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16;                                      // 0x01667bac
struct StrWriter {
    int* mBegin;     // +0
    int* mEnd;       // +4
    int* mCapacity;  // +8
    int pad0c;       // +0xc
    int* mInline;    // +0x10
    int* Init(uint32_t a, uint32_t b);   // 004c0570
    void Free();                         // 004c0b80
};
int Vsnprintf16(int16_t* pDest, uint32_t n, const wchar_t* fmt, char* args);  // @ 0x939950
struct BasicString16 {
    uint16_t* mpBegin;     // +0
    uint16_t* mpEnd;       // +4
    uint16_t* mpCapacity;  // +8
    void resize(uint32_t n);                                          // @ 0x4c1c80
    BasicString16* sprintf_va_list(const wchar_t* fmt, char* args);  // @ 0x4c09e0
};
// ---- items of slice s004c0410 end

// ---- items of slice s004c10e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct WideFixedStr_s004c_10e0 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    WideFixedAlloc mAllocator;

    void SetCapacity(uint32_t n);        // 0x004c26d0
    WideFixedStr_s004c_10e0* AppendN(uint32_t n, uint16_t c);
};
}
// ---- items of slice s004c10e0 end

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

// @ 0x004494b0
cSPMatrix3_s0044_8fa0 cSPEditorBlock::A494b0(Vector3 dir)
{
    if (mFlags.test(0xb))
        return *(cSPMatrix3_s0044_8fa0*)&mMat60;
    cSPMatrix3_s0044_8fa0 q;
    bool ok = (mEditorModel ? mEditorModel->IsSymmetryEnabled() : true) && mFlags.test(0xf);
    bool last = mFlags.test(0x22) || ok;
    Vector3 v18 = Vector3(-dir);
    if (last) {
        V3x a((const V3x&)kAxis15d23f0);
        V3x bb((const V3x&)kAxis15d2478);
        if (mPosition[0] < kZero) {
            a *= -1.0f;
            bb *= -1.0f;
        }
        V3x cc((const V3x&)kAxis15d23a8);
        q[0] = a;
        q[1] = bb;
        q[2] = cc;
    } else {
        Vector3 up = Vector3(-dir);
        up[2] = kZero;
        up = Normalize(up);
        q = MakeOrientation(up, kAxis15d23a8);
        if (mFlags.test(0x13)) {
            Vector3 r1 = Vector3(-kAxis15d23f0);
            Vector3 r0 = kAxis15d2478;
            if (mPosition[0] < kZero) {
                r0 *= -1.0f;
                r1 *= -1.0f;
            }
            r1[1] = kZero;
            r1 = normalized_safe(r1);
            Vector3 r2 = normalized_safe(Vector3(Cross(r0, r1)));
            if (r2[0] * r2[0] + r2[1] * r2[1] + r2[2] * r2[2] < 0.9f) {
                Matrix3 base(mMat60);
                r1 = base[1];
                r1[1] = kZero;
                r1 = Normalize(r1);
                r2 = Normalize(Vector3(Cross(r0, r1)));
            }
            q[0] = r0;
            q[1] = r1;
            q[2] = r2;
        }
    }
    return q;
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

// @ 0x00472b80
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix33* mat, float epsilon)
{
    const float trace = mat->m[0] + mat->m[4] + mat->m[8];
    if (trace > epsilon) {
        const float s = sqrt(trace + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[5] - mat->m[7]) * inv;
        out->y = (mat->m[6] - mat->m[2]) * inv;
        out->z = (mat->m[1] - mat->m[3]) * inv;
        out->w = 0.5f * s;
    } else if (mat->m[0] > mat->m[4] && mat->m[0] > mat->m[8]) {
        const float s = sqrt((mat->m[0] - (mat->m[4] + mat->m[8])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = 0.5f * s;
        out->y = (mat->m[1] + mat->m[3]) * inv;
        out->z = (mat->m[2] + mat->m[6]) * inv;
        out->w = (mat->m[5] - mat->m[7]) * inv;
    } else if (mat->m[4] > mat->m[8]) {
        const float s = sqrt((mat->m[4] - (mat->m[8] + mat->m[0])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[1] + mat->m[3]) * inv;
        out->y = 0.5f * s;
        out->z = (mat->m[5] + mat->m[7]) * inv;
        out->w = (mat->m[6] - mat->m[2]) * inv;
    } else {
        const float s = sqrt((mat->m[8] - (mat->m[0] + mat->m[4])) + 1.0f);
        const float inv = 0.5f / s;
        out->x = (mat->m[2] + mat->m[6]) * inv;
        out->y = (mat->m[5] + mat->m[7]) * inv;
        out->z = 0.5f * s;
        out->w = (mat->m[1] - mat->m[3]) * inv;
    }
    return out;
}

// @ 0x004c09e0
BasicString16* BasicString16::sprintf_va_list(const wchar_t* fmt, char* args)
{
    const int nOldSize = (int)(((char*)mpEnd - (char*)mpBegin) >> 1);
    int n = (mpBegin == (uint16_t*)&gEmptyString16)
        ? Vsnprintf16((int16_t*)mpEnd, 0, fmt, args)
        : Vsnprintf16((int16_t*)mpEnd, (uint32_t)(((char*)mpCapacity - (char*)mpEnd) >> 1), fmt, args);
    if (n < (int)(((char*)mpCapacity - (char*)mpEnd) >> 1)) {
        if (n < 0) {
            // not even the current size fits: double the capacity until it does (or give up)
            const int nMin = 7;
            int nTry0 = nOldSize * 2;
            int nTry = (nMin < nTry0) ? nTry0 : nMin;
            while (n < 0 && (uint32_t)nTry < 1000000u) {
                resize((uint32_t)nTry);
                n = Vsnprintf16((int16_t*)mpBegin + nOldSize, (uint32_t)((nTry + 1) - nOldSize), fmt, args);
                nTry = nTry * 2;
            }
        }
    } else {
        resize((uint32_t)(nOldSize + n));
        n = Vsnprintf16((int16_t*)mpBegin + nOldSize, (uint32_t)(n + 1), fmt, args);
    }
    if (n >= 0)
        mpEnd = mpBegin + nOldSize + n;
    return this;
}

// @ 0x004c0b80
void StrWriter::Free()
{
    if (mBegin != 0) {
        int n40 = (int)((char*)mCapacity - (char*)mBegin) >> 2 << 2;
        int* len = mBegin;
        if (len != mInline) {
            int* v33 = len;
            EASTL_allocator_deallocate(v33);
        }
        (void)n40;
    }
}

// @ 0x004c1ff0
namespace eastl {
WideFixedStr_s004c_10e0* WideFixedStr_s004c_10e0::AppendN(uint32_t n, uint16_t c)
{
    const uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
    const uint32_t nCapacity = (uint32_t)(mpCapacity - mpBegin) - 1;
    if (nCapacity < nSize + n) {
        const uint32_t nRequired = nSize + n;
        const uint32_t nGrowSize = (nCapacity < 9) ? 8 : nCapacity * 2;
        SetCapacity(nGrowSize < nRequired ? nRequired : nGrowSize);
    }
    if (n != 0) {
        uint16_t* p = mpEnd + 1;
        uint16_t* const pEnd = p + n - 1;
        for (; p < pEnd; ++p)
            *p = c;
        *mpEnd = c;
        mpEnd += n;
        *mpEnd = 0;
    }
    return this;
}
}  // namespace eastl

// @ 0x004c2100
void VectorSwap4(uint32_t* a, uint32_t* b)
{
    if (&a[3] == &b[3]) {
        uint32_t t0 = a[0]; a[0] = b[0]; b[0] = t0;
        uint32_t t1 = a[1]; a[1] = b[1]; b[1] = t1;
        uint32_t t2 = a[2]; a[2] = b[2]; b[2] = t2;
    } else {
        // PARTIAL: element-wise copy through a temporary buffer.
    }
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

// @ 0x004c2740
void VectorAssign4(uint32_t* self, uint32_t* other)
{
    (void)self; (void)other;
}

// @ 0x004c29c0
void eastl_set_capacity(eastl::WideFixedStr* self, uint32_t n)
{
    (void)self; (void)n;
}

// @ 0x004c2ad0
void WideFixedStr_SwapHeap(eastl::WideFixedStr* self, eastl::WideFixedStr* other)
{
    (void)self; (void)other;
}

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

// @ 0x006237a0
unsigned int SP::cPropertyList::GetModificationCount() const
{
  uint32_t parentCount = mParent.mpObject ? mParent.mpObject->GetModificationCount() : 0;
  return mModificationCount + parentCount;
}
