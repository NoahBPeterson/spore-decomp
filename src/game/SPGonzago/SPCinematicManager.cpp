// src/game/SPGonzago/SPCinematicManager.cpp
// Object file: SPGonzago/SPCinematicManager.obj.  Types, members and virtual calls use the canonical headers under
// src/game/include where they exist; the local stand-ins below are kept until their canonical classes are migrated.
// Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdarg.h>
#include <intrin.h>
#include <string.h>
#include "EA/Messaging/Server.h"
#include "EA/Messaging/IHandler.h"
#include <new>
#include <math.h>
#include "EA/Variant.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorUI.h"
#include "EA/UTFWinControls/IButtonDrawable.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

struct WStr {
    const wchar_t* mBegin;
    const wchar_t* mEnd;
    uint32_t mCap;
    WStr(const wchar_t* s, int unused);
    void Assign(const wchar_t* b, const wchar_t* e);        // 0x00423820
    int rfind(wchar_t c, uint32_t pos);
    void AppendVPrintf(const wchar_t* fmt, va_list args);   // 0x004234b0
};

extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844
struct Holder {
    uint32_t pad[3];
    uint32_t mValue;
    void Apply(uint32_t a, uint32_t b);      // 0x0083c7f0
    void Set(uint32_t a, uint32_t b);
};
struct MessageHeader { uint32_t data[10]; uint32_t arg; };
struct SlotMessage {
    const void* vptr;          // +0x00
    volatile long refCount;    // +0x04
    uint32_t body[0x2c];       // +0x08 .. : 32 slots of 8 bytes; arg lives at +0x30, listener mask at +0x38

    SlotMessage* Construct(uint32_t arg);
    void Destruct();
};

struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;

    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    wchar_t* at(int i) { return mpBegin + i; }
    unsigned size() { return (unsigned)(mpEnd - mpBegin); }
    unsigned capacity() { return (unsigned)(mpCapacity - mpBegin); }
    unsigned remaining() { return (unsigned)(mpCapacity - mpEnd); }

    WString& AppendSprintfVa(const wchar_t* fmt, va_list args);   // 0x004234b0
    WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    unsigned Find(const wchar_t* s, unsigned pos, unsigned n);    // 0x00423700
    void FreeBuffer();                                            // 0x004237d0
    void AllocateSelf(const wchar_t* first, const wchar_t* last); // 0x00423820

    void reserve(unsigned n);                                      // 0x00429520
    void AllocateBuf(unsigned n);                                  // 0x00429760
    void Append(const wchar_t* first, const wchar_t* last);        // 0x00429580
    void Erase(wchar_t* first, wchar_t* last);                     // 0x0042e2f0
};

extern const char g_EditorName[];     // "Editor"
extern const char g_AllocatorHdr[];   // ".../EASTL/include/EASTL/allocator.h"
typedef uint16_t wchar16;
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags,
                                       int align, const char* file, int line);
extern wchar16    g_EmptyWStr[];      // shared 1-char empty string storage
template <class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
static inline wchar16* WCopy(const wchar16* first, const wchar16* last, wchar16* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}
static inline wchar16* WAlloc(uint32_t n)
{
    void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
    return (wchar16*)p;
}
static inline void Nop3() { volatile int u1, u2, u3; }
struct WStr_s0042_92a0 {
    wchar16* mBegin; wchar16* mEnd; wchar16* mCap;
    void Erase(wchar16* first, wchar16* last);
    void AppendFill(uint32_t n, wchar16 c);
    void FreeBuffer();
    void Resize(uint32_t n);
    WStr_s0042_92a0* Append(const wchar16* first, const wchar16* last);
    void AllocateSelf(uint32_t n);
};

#pragma intrinsic(_InterlockedIncrement)
struct Alloc {
    uint32_t pad;
    const char* mpName;
    Alloc& operator=(const Alloc& x)
    {
        mpName = x.mpName;
        return *this;
    }
};
struct WString_s0042_f160 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    Alloc mAllocator;

    WString_s0042_f160(const WString_s0042_f160& x);
    void AllocateSelf(const uint16_t* b, const uint16_t* e);  // 0x00423820
    void FreeBuffer();                                         // 0x004237d0
    void Resize(uint32_t n);                                   // 0x00429520
    void Swap(WString_s0042_f160& x);                                     // 0x0042f620
    void SetCapacity(uint32_t n);                              // 0x0042f360
    WString_s0042_f160& AssignRange(const uint16_t* b, const uint16_t* e);    // 0x0042f920
    void Assign(const uint16_t* b, const uint16_t* e);         // 0x00423650
    void EraseRange(uint16_t* b, uint16_t* e);                 // 0x0042e2f0
    void AppendRange(const uint16_t* b, const uint16_t* e);    // 0x0042f9d0
};
void* EastlAllocate(uint32_t size, const char* name, uint32_t flags, uint32_t align,
                    const char* file, int line);  // 0x00f473a0
inline void DeadHelper()
{
    uint32_t dead[3];
}
inline uint16_t* DoAllocate(uint32_t n)
{
    uint16_t* p = (uint16_t*)EastlAllocate(
        n * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    return p;
}
inline uint16_t* UninitializedCopy16(const uint16_t* first, const uint16_t* last, uint16_t* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct Key12 {
    uint32_t mA;
    uint32_t mB;
    uint32_t mC;
    bool operator<(const Key12& rhs) const;      // 0x5715d0
};
struct Block36 { uint32_t mData[9]; };
struct DirtyState {
    uint16_t mDirtyFlags;
    uint16_t mRevision;
    Key12 mKey;            // +0x04
    uint32_t mPad10;       // +0x10
    Block36 mBlock;        // +0x14

    void SetBlock(const Block36& b);
    void SetKey(const Key12& k);
};
struct Vec3 { float x, y, z; };
struct VecPair {
    Vec3 mA;
    Vec3 mB;
    VecPair& operator=(const VecPair& o);
};
struct OwnerHandle;
struct OwnerTarget {
    PV16 PV16 PV16 PV16 PV16 PV8 PV2 PV
    virtual void Notify(OwnerHandle* h, int arg);   // +0x16c
};
struct OwnerHandle {
    OwnerTarget* mpTarget;
    void Notify();
};

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
class allocator_s0057_bfb0 { public:
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_bfb0>
class basic_string_s0057_bfb0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string_s0057_bfb0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string_s0057_bfb0(const basic_string_s0057_bfb0& x);
    struct CtorDoNotInitialize {};
    basic_string_s0057_bfb0(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string_s0057_bfb0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s0057_bfb0() { DeallocateSelf(); }

    basic_string_s0057_bfb0& operator=(const basic_string_s0057_bfb0& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string_s0057_bfb0& assign(const T* pBegin, const T* pEnd);
    basic_string_s0057_bfb0& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};
}

#define PV_s005c_a070(n) virtual void pv##n();
class cAudioSystem {
 public:
  PV_s005c_a070(0) PV_s005c_a070(1) PV_s005c_a070(2) PV_s005c_a070(3) PV_s005c_a070(4) PV_s005c_a070(5) PV_s005c_a070(6) PV_s005c_a070(7) PV_s005c_a070(8) PV_s005c_a070(9) PV_s005c_a070(10) PV_s005c_a070(11) PV_s005c_a070(12) PV_s005c_a070(13)
  virtual void SetId(int id);              // +0x38
  virtual void SetFloat(int id, float v);  // +0x3c
  virtual void SetInt(int id, int v);      // +0x40
  PV_s005c_a070(17) PV_s005c_a070(18) PV_s005c_a070(19) PV_s005c_a070(20) PV_s005c_a070(21)
  virtual void Flush();                    // +0x58
};
cAudioSystem* GetSystemAT();  // 0x00a206f0

// ---- items of slice s00423110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];   // 0x01667BAC
int __cdecl VsnprintfW(wchar_t* dst, unsigned n, const wchar_t* fmt, va_list args);       // 0x00939950
wchar_t* __cdecl SearchW(wchar_t* b1, wchar_t* e1, const wchar_t* b2, const wchar_t* e2); // 0x004297f0
void __cdecl DeallocateRaw(void* p);                                                      // EASTL allocator
template <class T> inline const T& Max_s0042_3110(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (a < b) ? a : b; }
// ---- items of slice s00423110 end

// ---- items of slice s004292a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl EASTL_allocator_deallocate(void* p) throw();
struct ByteFixedBuf {
    char* mBegin; char* mEnd; char* mCap; int pad; char* mFixed;
    void ReleaseHeap();
    ByteFixedBuf* DeletingDtor(uint32_t flags);
    ByteFixedBuf* Identity(int unused);
    void DoFree(char* p, int n) { if (p && p != mFixed) { char* q = p; EASTL_allocator_deallocate(q); } }
    void DoFreeNoFixed(char* p, int n) { if (p) { char* q = p; EASTL_allocator_deallocate(q); } }
};
wchar16* __cdecl WFindChar(wchar16* first, wchar16* last, wchar16 c);
// ---- items of slice s004292a0 end

// ---- items of slice s0042dee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);
template<int N> inline void padfn() { uint32_t pad[N]; }
template<class T> struct It {
    T* p;
    It(T* q) : p(q) {}
    T& operator*() const { return *p; }
    It& operator++() { ++p; return *this; }
};
template<class T> inline bool operator!=(It<T> a, It<T> b) { return a.p != b.p; }
struct WString_s0042_dee0 {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCapEnd;
    wchar_t* erase(wchar_t* first, wchar_t* last);
    void reserve_internal(size_t n);  // 0x0042F360
    void reserve(size_t n);
};
template<class T> inline const T& eastl_max(const T& a, const T& b)
{
    padfn<15>();
    return (a < b) ? b : a;
}
// ---- items of slice s0042dee0 end

// ---- items of slice s0045aa70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VAlloc { char b; };              // empty allocator tag (distinct temp per member)
struct AllocObj {                       // allocator sub-object at +0xc of a vector
    uint32_t mA, mB;                    // +0x00, +0x04
    void ctor(const VAlloc& alloc);     // 0x429360
};
struct VecHdr {                         // vector header + sp_vector_allocator (0x14 bytes)
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    AllocObj mAllocator;                // +0x0c
    VecHdr() { ctor(VAlloc()); }
    VecHdr(const VAlloc& alloc) { ctor(alloc); }
    void ctor(const VAlloc& alloc);     // 0x540470  (empty the three pointers)
    void dtor4();                       // 0x425990  (4-byte elements: int/uint32/pointer)
    void dtor8();                       // 0x45daf0  (8-byte elements)
    void dtor12();                      // 0x5156b0  (12-byte elements: Vector3)
    void dtor16();                      // 0x554b10  (16-byte elements: Vector4f)
    void dtor64();                      // 0x45d750  (64-byte elements: Matrix4)
    void dtorVec3();                    // 0x540520  (out-of-line vector<Vector3> dtor)
};
struct PadVec {                         // 0x14: vector whose allocator is constructed separately
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    AllocObj mAllocator;                // +0x0c
    PadVec() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mAllocator.ctor(VAlloc()); }
    void dtor64();                      // 0x45d750
};
struct WString_s0045_aa70 {
    void*    mpBegin;                   // +0x00
    void*    mpEnd;                     // +0x04
    void*    mpCapacity;                // +0x08
    uint32_t mAllocator;                // +0x0c
    WString_s0045_aa70() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; SetEmpty(); }
    void SetEmpty();                    // 0x45dac0
    void Free();                        // 0x4237d0
};
struct ColladaExport {
    WString_s0045_aa70  mName;                     // +0x000
    VecHdr   mPositions;                // +0x010
    VecHdr   mNormals;                  // +0x024
    VecHdr   mUVs;                      // +0x038
    VecHdr   mTangents;                 // +0x04c
    VecHdr   mBinormals;                // +0x060
    VecHdr   mBoneIndices;              // +0x074
    VecHdr   mBoneWeights;              // +0x088
    VecHdr   mPosIndices;               // +0x09c
    VecHdr   mNormalIndices;            // +0x0b0
    VecHdr   mUVIndices;                // +0x0c4
    VecHdr   mBoneNames;                // +0x0d8
    VecHdr   mBoneParents;              // +0x0ec
    VecHdr   mBindMatrices;             // +0x100
    PadVec   mPad114;                   // +0x114
    VecHdr   mBoneMatrices;             // +0x128
    PadVec   mPad13c;                   // +0x13c

    ColladaExport();
    ~ColladaExport();
};
// ---- items of slice s0045aa70 end

// ---- items of slice s0045d2c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  Vsnprintf8(char* buf, unsigned int count, const char* fmt, void* args); // 0x938400
extern char g_sentinel;                                      // 0x01667bac
struct Matrix44 {
    float m[16];
    Matrix44();
    Matrix44(const Matrix44& o);
};
Matrix44::Matrix44(const Matrix44& o)
{
    for (int i = 0; i < 4; i = i + 1) {
        float a = o.m[i * 4 + 0];
        float b = o.m[i * 4 + 1];
        float c = o.m[i * 4 + 2];
        float d = o.m[i * 4 + 3];
        m[i * 4 + 0] = a;
        m[i * 4 + 1] = b;
        m[i * 4 + 2] = c;
        m[i * 4 + 3] = d;
    }
}
struct DStr {
    char* begin;
    char* end;
    char* cap;
    void resize(unsigned int n);                        // 0x45ebd0
};
struct Str : public DStr {
    Str* SprintfCore(const char* fmt, void* args);
    void ResetAndFormat(const char* fmt, void* args);   // 0x45da50
};
template <typename T>
static inline const T& max_alt(const T& a, const T& b)
{
    return a < b ? b : a;
}
static inline int Vsnprintf(char* dst, unsigned int count, const char* fmt, void* args)
{
    return Vsnprintf8(dst, count, fmt, args);
}
// ---- items of slice s0045d2c0 end

// ---- items of slice s0045df90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DStr_s0045_df90 {
    char* begin;
    char* end;
    char* cap;
    void  trim(char* first, char* last);            // 0x45f080
    void  append(unsigned int n, int value);        // 0x45efa0
    void  resize(unsigned int n);                   // 0x45ebd0 (defined below)
};
namespace rw {
namespace math {
namespace fpu {
template <class T, int A>
class Vector4Template_s0045_df90 { public:
    T mX, mY, mZ, mW;
    Vector4Template_s0045_df90() {}
    Vector4Template_s0045_df90(T x, T y, T z, T w) : mX(x), mY(y), mZ(z), mW(w) {}
    Vector4Template_s0045_df90(const Vector4Template_s0045_df90& v) : mX(v.mX), mY(v.mY), mZ(v.mZ), mW(v.mW) {}
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template <class T, int A>
class Matrix44Template_s0045_df90 { public:
    Vector4Template_s0045_df90<T, A> xAxis, yAxis, zAxis, wAxis;
    Matrix44Template_s0045_df90() {}
    Matrix44Template_s0045_df90(T m00, T m01, T m02, T m03,
                     T m10, T m11, T m12, T m13,
                     T m20, T m21, T m22, T m23,
                     T m30, T m31, T m32, T m33)
        : xAxis(m00, m01, m02, m03), yAxis(m10, m11, m12, m13),
          zAxis(m20, m21, m22, m23), wAxis(m30, m31, m32, m33) {}
    // @ 0x45dca0: inline, but cl /Ob1 declines it (called out of line; its
    // reserved frame stays behind as a hole in each caller scope).
    Matrix44Template_s0045_df90(const Matrix44Template_s0045_df90& m)
    {
        xAxis = Vector4Template_s0045_df90<T, A>(m.xAxis);
        yAxis = Vector4Template_s0045_df90<T, A>(m.YAxis());
        zAxis = Vector4Template_s0045_df90<T, A>(m.ZAxis());
        wAxis = Vector4Template_s0045_df90<T, A>(m.WAxis());
    }
    const Vector4Template_s0045_df90<T, A>& YAxis() const { return yAxis; }
    const Vector4Template_s0045_df90<T, A>& ZAxis() const { return zAxis; }
    const Vector4Template_s0045_df90<T, A>& WAxis() const { return wAxis; }
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
typedef Matrix44Template_s0045_df90<float, 0> Matrix44f;
}
}
}
namespace rw {
namespace math {
namespace fpu {
float Determinant(const Matrix44f& m);           // @ 0x45ec30
}
}
}
namespace rw {
namespace math {
namespace fpu {
#define M(i) ((const float*)&m)[i]
}
}
}
// ---- items of slice s0045df90 end

// @ 0x0041df50
WStr::WStr(const wchar_t* s, int unused)
{
    mBegin = 0;
    mEnd = 0;
    mCap = 0;
    const wchar_t* p = s;
    while (*p) ++p;
    Assign(s, s + (p - s));
}

// @ 0x0041e050
WStr* __cdecl WStr_Format(WStr* s, const wchar_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    s->mEnd = s->mBegin;
    s->AppendVPrintf(fmt, args);
    va_end(args);
    return s;
}

// @ 0x00421c80
SlotMessage* SlotMessage::Construct(uint32_t arg)
{
    MessageHeader* pHdr = (MessageHeader*)((char*)this + 8);
    pHdr->arg = arg;
    vptr = vtbl_App_cLocaleChangeMessage;
    vptr = vtbl_UI_BehaviorMessage;
    volatile long* pRefCount = &refCount;
    _InterlockedExchange(pRefCount, 0);
    vptr = vtbl_UI_BehaviorMessage;
    vptr = vtbl_SlotMessage;
    body[12] = 0;
    return this;
}

// @ 0x00421e80
void Holder::Set(uint32_t a, uint32_t b)
{
    mValue = b;
    Apply(a, b);
}

// @ 0x004234b0
WString& WString::AppendSprintfVa(const wchar_t* fmt, va_list args)
{
    const int nInitialSize = (int)size();
    int nReturnValue;

    if (mpBegin == gEmptyWString) {
        nReturnValue = VsnprintfW(end(), 0, fmt, args);
    } else {
        nReturnValue = VsnprintfW(end(), (int)remaining(), fmt, args);
    }

    if (nReturnValue >= (int)remaining()) {
        reserve(nInitialSize + nReturnValue);
        nReturnValue = VsnprintfW(at(nInitialSize), nReturnValue + 1, fmt, args);
    } else if (nReturnValue < 0) {
        unsigned nLocalBufferSize = Max_s0042_3110<unsigned>(7, size() << 1);
        for (; nReturnValue < 0 && nLocalBufferSize < 1000000; nLocalBufferSize <<= 1) {
            reserve(nLocalBufferSize);
            nReturnValue = VsnprintfW(at(nInitialSize), nLocalBufferSize + 1 - nInitialSize, fmt, args);
        }
    }

    if (nReturnValue >= 0)
        mpEnd = mpBegin + nInitialSize + nReturnValue;
    return *this;
}

// @ 0x00423650
WString& WString::Assign(const wchar_t* first, const wchar_t* last)
{
    const unsigned n = (unsigned)(last - first);
    if (n <= (unsigned)(mpEnd - mpBegin)) {
        memcpy(mpBegin, first, n * 2);
        Erase(mpBegin + n, mpEnd);
    } else {
        memcpy(mpBegin, first, (mpEnd - mpBegin) * 2);
        Append(first + (mpEnd - mpBegin), last);
    }
    return *this;
}

// @ 0x00423700
unsigned WString::Find(const wchar_t* s, unsigned pos, unsigned n)
{
    const unsigned nLength = (unsigned)(mpEnd - mpBegin);
    if (n <= nLength) {
        if (n != 0) {
            wchar_t* const pEnd = mpBegin + Min(pos, nLength - n) + n;
            wchar_t* const pResult = SearchW(mpBegin, pEnd, s, s + n);
            if (pResult != pEnd)
                return (unsigned)(pResult - mpBegin);
        } else {
            return Min(pos, nLength);
        }
    }
    return (unsigned)-1;
}

// @ 0x004237d0
void WString::FreeBuffer()
{
    int n;
    wchar_t* pData;
    wchar_t* pMem;
    if ((mpCapacity - mpBegin) > 1) {
        n = (int)(mpCapacity - mpBegin);
        pData = mpBegin;
        if (pData) {
            pMem = pData;
            DeallocateRaw(pMem);
        }
    }
}

// @ 0x00423820
void WString::AllocateSelf(const wchar_t* first, const wchar_t* last)
{
    const unsigned n = (unsigned)(last - first);
    AllocateBuf(n + 1);
    wchar_t* pNew = mpBegin;
    memcpy(pNew, first, (last - first) * 2);
    mpEnd = pNew + (last - first);
    *mpEnd = 0;
}

// @ 0x00429300
void ByteFixedBuf::ReleaseHeap()
{
    if ((mCap - mBegin) > 1) DoFree(mBegin, mCap - mBegin);
}

// @ 0x00429520
void WStr_s0042_92a0::Resize(uint32_t n)
{
    uint32_t sz = mEnd - mBegin;
    if (n < sz) Erase(mBegin + n, mEnd);
    else if (n > sz) AppendFill(n - sz, 0);
}

// @ 0x00429580
WStr_s0042_92a0* WStr_s0042_92a0::Append(const wchar16* first, const wchar16* last)
{
    uint32_t nOldSize; int n; uint32_t capacity; wchar16* yfv; int k; wchar16* pNewBegin; const wchar16* tvi;
    // Local names are load-bearing: /Od frame slot order follows the symbol table.
    if (first != last) {
        nOldSize = mEnd - mBegin;
        n = last - first;
        capacity = (mCap - mBegin) - 1;
        if (nOldSize + n > capacity) {
            uint32_t nRequired = nOldSize + n;
            uint32_t nGrow = (capacity > 8) ? capacity * 2 : 8;
            k = Max(nGrow, nRequired) + 1;
            pNewBegin = WAlloc(k);
            yfv = pNewBegin;
            yfv = WCopy(mBegin, mEnd, pNewBegin);
            yfv = WCopy(first, last, yfv);
            *yfv = 0;
            Nop3();
            FreeBuffer();
            mBegin = pNewBegin; mEnd = yfv; mCap = pNewBegin + k;
        } else {
            tvi = first; ++tvi;
            WCopy(tvi, last, mEnd + 1);
            mEnd[n] = 0; *mEnd = *first; mEnd = mEnd + n;
        }
    }
    return this;
}

// @ 0x00429760
void WStr_s0042_92a0::AllocateSelf(uint32_t n)
{
    if (n > 1) {
        void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
        mBegin = (wchar16*)p;
        mEnd = mBegin;
        mCap = mBegin + n;
    } else {
        mBegin = g_EmptyWStr;
        mEnd = mBegin;
        mCap = mBegin + 1;
    }
}

// @ 0x004297f0
wchar16* WSearch(wchar16* first1, wchar16* last1, wchar16* first2, wchar16* last2)
{
    if (first1 == last1 || first2 == last2) return first1;
    if (first2 + 1 == last2) return WFindChar(first1, last1, *first2);
    if ((last2 - first2) > (last1 - first1)) return last1;
    wchar16* cur = last1 - (last2 - first2) + 1;
    while (cur != first1) {
        wchar16* found = WFindChar(first1, cur, *first2);
        if (found == cur) return last1;
        wchar16* p = first2;
        while (*found++ == *p++) {
            if (p == last2) return found - (last2 - first2);
        }
        --cur;
    }
    return last1;
}

// @ 0x0042e2f0
wchar_t* WString_s0042_dee0::erase(wchar_t* first, wchar_t* last)
{
    if (first != last) {
        memmove(first, last, (mEnd - last + 1) * sizeof(wchar_t));
        wchar_t* newEnd = mEnd - (last - first);
        mEnd = newEnd;
    }
    return first;
}

// @ 0x0042e610
void WString_s0042_dee0::reserve(size_t n)
{
    size_t size = mEnd - mBegin;
    n = eastl_max(n, size) + 1;
    if (n > (size_t)(mCapEnd - mBegin))
        reserve_internal(n);
}

// @ 0x0042f360
void WString_s0042_f160::SetCapacity(uint32_t n)
{
    uint32_t dead0;
    if (n == (uint32_t)-1 || n <= (uint32_t)(mpEnd - mpBegin)) {
        if (n < (uint32_t)(mpEnd - mpBegin))
            Resize(n);
        struct { uint16_t* b; uint16_t* e; uint16_t* c; } tmp = {0, 0, 0};
        ((WString_s0042_f160*)&tmp)->AllocateSelf(mpBegin, mpEnd);
        Swap(*(WString_s0042_f160*)&tmp);
        ((WString_s0042_f160*)&tmp)->FreeBuffer();
    } else {
        uint16_t* pNew;
        uint16_t* pEnd;
        {
            uint32_t dead1[3];
            pNew = DoAllocate(n);
            pEnd = pNew;
            pEnd = UninitializedCopy16(mpBegin, mpEnd, pNew);
            *pEnd = 0;
            FreeBuffer();
            mpBegin = pNew;
            mpEnd = pEnd;
            mpCapacity = pNew + n;
            DeadHelper();
        }
    }
}

// @ 0x0045b9a0
ColladaExport::~ColladaExport()
{
    mPad13c.dtor64();
    mBoneMatrices.dtor64();
    mPad114.dtor64();
    mBindMatrices.dtor64();
    mBoneParents.dtor4();
    mBoneNames.dtor4();
    mUVIndices.dtor4();
    mNormalIndices.dtor4();
    mPosIndices.dtor4();
    mBoneWeights.dtor16();
    mBoneIndices.dtor8();
    mBinormals.dtor12();
    mTangents.dtor12();
    mUVs.dtor8();
    mNormals.dtor12();
    mPositions.dtorVec3();
    mName.Free();
}

// @ 0x0045dca0
Matrix44::Matrix44()
{
}

// @ 0x0045de10
Str* Str::SprintfCore(const char* fmt, void* args)
{
    unsigned int nInitialSize = (unsigned int)(end - begin);
    int nReturnValue;
    if (begin == &g_sentinel) {
        nReturnValue = Vsnprintf(end, 0, fmt, args);
    } else {
        nReturnValue = Vsnprintf(end, (unsigned int)(cap - end), fmt, args);
    }
    if (nReturnValue >= (int)(cap - end)) {
        resize(nInitialSize + nReturnValue);
        nReturnValue = Vsnprintf(begin + nInitialSize, nReturnValue + 1, fmt, args);
    } else if (nReturnValue < 0) {
        unsigned int n = max_alt((unsigned int)7, (unsigned int)((end - begin) * 2));
        for (; nReturnValue < 0 && n < 1000000; n = n * 2) {
            resize(n);
            nReturnValue = Vsnprintf(begin + nInitialSize, (n + 1) - nInitialSize, fmt, args);
        }
    }
    if (nReturnValue >= 0) {
        end = begin + nInitialSize + nReturnValue;
    }
    return this;
}

// @ 0x0045df90
namespace rw { namespace math { namespace fpu {
Matrix44f Inverse(const Matrix44f& m, float& det)
{
    det = Determinant(m);
    if (det == 0.0f) {
        Matrix44f zero;
        return zero;
    } else {
        Matrix44f result(
            (((M(10) * M(15) - M(11) * M(14)) * M(5) + (M(13) * M(11) - M(9) * M(15)) * M(6)) + (M(9) * M(14) - M(13) * M(10)) * M(7)) / det,
            (((M(2) * M(15) - M(3) * M(14)) * M(9) + (M(3) * M(13) - M(1) * M(15)) * M(10)) + (M(1) * M(14) - M(2) * M(13)) * M(11)) / det,
            (((M(2) * M(7) - M(3) * M(6)) * M(13) + (M(3) * M(5) - M(1) * M(7)) * M(14)) + (M(1) * M(6) - M(2) * M(5)) * M(15)) / det,
            (((M(7) * M(10) - M(6) * M(11)) * M(1) + (M(5) * M(11) - M(7) * M(9)) * M(2)) + (M(6) * M(9) - M(5) * M(10)) * M(3)) / det,
            (((M(8) * M(15) - M(12) * M(11)) * M(6) + (M(12) * M(10) - M(8) * M(14)) * M(7)) + (M(11) * M(14) - M(10) * M(15)) * M(4)) / det,
            (((M(0) * M(15) - M(12) * M(3)) * M(10) + (M(12) * M(2) - M(0) * M(14)) * M(11)) + (M(3) * M(14) - M(2) * M(15)) * M(8)) / det,
            (((M(0) * M(7) - M(4) * M(3)) * M(14) + (M(4) * M(2) - M(0) * M(6)) * M(15)) + (M(3) * M(6) - M(2) * M(7)) * M(12)) / det,
            (((M(8) * M(7) - M(4) * M(11)) * M(2) + (M(4) * M(10) - M(8) * M(6)) * M(3)) + (M(6) * M(11) - M(7) * M(10)) * M(0)) / det,
            (((M(8) * M(13) - M(12) * M(9)) * M(7) + (M(9) * M(15) - M(13) * M(11)) * M(4)) + (M(12) * M(11) - M(8) * M(15)) * M(5)) / det,
            (((M(0) * M(13) - M(12) * M(1)) * M(11) + (M(1) * M(15) - M(3) * M(13)) * M(8)) + (M(12) * M(3) - M(0) * M(15)) * M(9)) / det,
            (((M(0) * M(5) - M(4) * M(1)) * M(15) + (M(1) * M(7) - M(3) * M(5)) * M(12)) + (M(4) * M(3) - M(0) * M(7)) * M(13)) / det,
            (((M(8) * M(5) - M(4) * M(9)) * M(3) + (M(7) * M(9) - M(5) * M(11)) * M(0)) + (M(4) * M(11) - M(8) * M(7)) * M(1)) / det,
            (((M(13) * M(10) - M(9) * M(14)) * M(4) + (M(8) * M(14) - M(12) * M(10)) * M(5)) + (M(12) * M(9) - M(8) * M(13)) * M(6)) / det,
            (((M(2) * M(13) - M(1) * M(14)) * M(8) + (M(0) * M(14) - M(12) * M(2)) * M(9)) + (M(12) * M(1) - M(0) * M(13)) * M(10)) / det,
            (((M(2) * M(5) - M(1) * M(6)) * M(12) + (M(0) * M(6) - M(4) * M(2)) * M(13)) + (M(4) * M(1) - M(0) * M(5)) * M(14)) / det,
            (((M(5) * M(10) - M(6) * M(9)) * M(0) + (M(8) * M(6) - M(4) * M(10)) * M(1)) + (M(4) * M(9) - M(8) * M(5)) * M(2)) / det);
        return result;
    }
}
}}}  // namespace rw::math::fpu

// @ 0x0045ebd0
void DStr_s0045_df90::resize(unsigned int n)
{
    unsigned int cur = (unsigned int)(end - begin);
    if (n < cur) {
        trim(begin + n, end);
    } else if (n > cur) {
        append(n - cur, 0);
    }
    return;
}

// @ 0x0045ec30
float __cdecl FUN_0045ec30(const float* m)
{
    return
        m[0] * ((m[10] * m[15] - m[11] * m[14]) * m[5]
              + (m[13] * m[11] - m[9] * m[15]) * m[6]
              + (m[9] * m[14] - m[13] * m[10]) * m[7])
      + m[1] * ((m[11] * m[14] - m[10] * m[15]) * m[4]
              + (m[8] * m[15] - m[12] * m[11]) * m[6]
              + (m[12] * m[10] - m[8] * m[14]) * m[7])
      + m[2] * ((m[9] * m[15] - m[13] * m[11]) * m[4]
              + (m[12] * m[11] - m[8] * m[15]) * m[5]
              + (m[8] * m[13] - m[12] * m[9]) * m[7])
      + m[3] * ((m[13] * m[10] - m[9] * m[14]) * m[4]
              + (m[8] * m[14] - m[12] * m[10]) * m[5]
              + (m[12] * m[9] - m[8] * m[13]) * m[6]);
}

// @ 0x00571d40
void DirtyState::SetKey(const Key12& k)
{
    mKey = k;
    mDirtyFlags |= 4;
    mRevision++;
}

// @ 0x00571d60
VecPair& VecPair::operator=(const VecPair& o)
{
    mB = o.mB;
    mA = o.mA;
    return *this;
}

// @ 0x00571d90
void OwnerHandle::Notify()
{
    mpTarget->Notify(this, 0);
}

// @ 0x00571db0
namespace EA {
namespace Messaging {
bool RemoveHandler(Server * server, IHandler * handler, unsigned int const * ids, unsigned int count, int priority)
{
    bool result = true;
    for (uint32_t i = 0; i < count; ++i)
        if (!server->RemoveHandler(handler, ids[i], priority))
            result = false;
    return result;
}
}
}  // namespace EA::Messaging

// @ 0x00571e60
uint64_t __cdecl GetStopwatchCycle()
{
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
}

// @ 0x0057cb60
template <> eastl::basic_string_s0057_bfb0<wchar_t>& eastl::basic_string_s0057_bfb0<wchar_t>::operator=(const basic_string_s0057_bfb0<wchar_t>& x)
{
    if (&x != this)
        assign(x.mpBegin, x.mpEnd);
    return *this;
}

// @ 0x005ca880
void SetGlobalProperty(int value, float scale)
{
    cAudioSystem* sys = GetSystemAT();
    if (sys) {
        sys->SetId(0x3cdd1a9);
        sys->SetInt(0x34753a7, value);
        sys->SetFloat(0x34753aa, scale);
        sys->Flush();
    }
}
