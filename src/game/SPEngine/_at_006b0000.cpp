// src/game/SPEngine/_at_006b0000.cpp -- migrated from slice(s) s006bb1c0, s006ba2f0, s006b9510, s006b8680, s006b5770, s006b47a0, s006b37d0, s006b18c0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_006b0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cJob.h"

// unnamed retail callees and globals (address in the comment)
extern uint8_t g_16046d8;
#include <intrin.h>
#include <wchar.h>
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include "EA/Thread/Mutex.h"
#include "SP/cEditorsTokenTranslator.h"
#include "EA/Swarm/cTransform.h"
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s006b18c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t g_16046d8;
// ---- items of slice s006b18c0 end

// ---- items of slice s006b37d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Counter40 {
  uint32_t pad[0x10];
  uint32_t m40;
  bool Inc();
};
// ---- items of slice s006b37d0 end

// ---- items of slice s006b47a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(dllimport) void* __cdecl SteamApps();
struct IRefCountedStub {
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
};
struct ISteamApps {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual bool v6(const char* p);
};
struct CSink {
    uint32_t mField0;        // +0x0
    uint32_t mField4;        // +0x4
    uint32_t mField8;        // +0x8
    uint32_t mFieldC;        // +0xc
    bool     mField10;       // +0x10
    char     mPad11;         // +0x11

    CSink(uint32_t a, uint32_t b);
    void FUN_006b4f90(bool b);
    void FUN_006b4fa0(const void* arg);
    void FUN_006b4fd0(const void* arg);
    void FUN_006b5000();
};
// ---- items of slice s006b47a0 end

// ---- items of slice s006b5770 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
#pragma intrinsic(wcscmp, wcslen)
typedef unsigned short wchar16;
__declspec(dllimport) wchar16* __cdecl wcschr(const wchar16* s, wchar16 c);
namespace eastl {
struct string16_s006b_5770 {
    wchar16* mpBegin;      // +0
    wchar16* mpEnd;        // +4
    wchar16* mpCapacity;   // +8
    int      mAllocator;   // +0xc

    void assign(const wchar16* first, const wchar16* last);     // 0x00423650
    void append(const wchar16* first, const wchar16* last);     // 0x00429580
    void append(const wchar16* s);                              // 0x005c3d90
    void push_back(wchar16 c);                                  // 0x004f6510
    void set_capacity(unsigned n);                              // 0x0042f360
    void reserve(unsigned n);                                   // 0x0042e610
    string16_s006b_5770& operator=(const string16_s006b_5770& o);                     // 0x0057cb60
    string16_s006b_5770& operator+=(const wchar16* s);                     // 0x00599bb0
    wchar16* FillInsert(unsigned n, unsigned ch);               // 0x00674230

    void clear() {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace App {
struct ITokenTranslator;
}
namespace App {
struct intrusive_ptr {
    ITokenTranslator* ptr;   // +0

    intrusive_ptr(ITokenTranslator* p);
    intrusive_ptr(ITokenTranslator* p, int) : ptr(p) {}   // adopts an existing reference
    intrusive_ptr(const intrusive_ptr& o);
    ~intrusive_ptr();
    intrusive_ptr& operator=(const intrusive_ptr& o);
};
}
namespace App {
struct TranslatorVector {
    intrusive_ptr* mpBegin;      // +0
    intrusive_ptr* mpEnd;        // +4
    intrusive_ptr* mpCapacity;   // +8

    __declspec(noinline) intrusive_ptr* erase(intrusive_ptr* pos);   // 0x006b5990
    intrusive_ptr* erase(intrusive_ptr* first, intrusive_ptr* last);   // 0x005c2170
    void push_back(const intrusive_ptr& v);                            // 0x006b5f80
    void DoInsertValue(intrusive_ptr* pos, const intrusive_ptr* pValue);
};
}
namespace App {
struct ITokenTranslator {
    virtual void Slot00();                                                     // +0x00
    virtual int  AddRef();                                                     // +0x04
    virtual int  Release();                                                    // +0x08
    virtual void* Cast(uint32_t typeID);                                       // +0x0c
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16_s006b_5770& dst);  // +0x10
    virtual void func14h(int);                                                 // +0x14

    int mnRefCount;   // +0x04
};
}
namespace App {
inline intrusive_ptr::intrusive_ptr(ITokenTranslator* p) : ptr(p)
{
    if (ptr) ptr->AddRef();
}
}
namespace App {
inline intrusive_ptr::intrusive_ptr(const intrusive_ptr& o) : ptr(o.ptr)
{
    if (ptr) ptr->AddRef();
}
}
namespace App {
inline intrusive_ptr::~intrusive_ptr()
{
    if (ptr) ptr->Release();
}
}
namespace App {
inline intrusive_ptr& intrusive_ptr::operator=(const intrusive_ptr& o)
{
    ITokenTranslator* n = o.ptr;
    ITokenTranslator* old = ptr;
    if (n != old) {
        if (n) n->AddRef();
        ptr = n;
        if (old) old->Release();
    }
    return *this;
}
}
namespace App {
struct TokenEntry {
    uint32_t hash;          // +0
    eastl::string16_s006b_5770 str;    // +4
};
}
namespace App {
struct SPCString {
    void* vtbl;                  // +0x00
    eastl::string16_s006b_5770* mpOut;      // +0x04
    const wchar16* mpSrc;        // +0x08
    int pad0c;                   // +0x0c
    bool mbEnabled;              // +0x10
    bool mbDirty;                // +0x11
};
}
namespace App {
struct cStringDetokenizer : ITokenTranslator {
    virtual void func18h();                                                    // +0x18
    virtual void AddTranslator(ITokenTranslator*);                             // +0x1c
    virtual void RemoveTranslator(ITokenTranslator*);                          // +0x20
    virtual bool HasTokens(const wchar16* pStr);                               // +0x24
    virtual bool func28h(void* a, eastl::string16_s006b_5770& dst);                       // +0x28
    virtual bool ProcessString(const wchar16* pStr, eastl::string16_s006b_5770& dst);     // +0x2c
    virtual bool func30h(SPCString* s, TokenEntry* table, uint32_t count);      // +0x30
    virtual void func34h(const wchar16* pStr, uint32_t index);                 // +0x34
    virtual bool ProcessStringEx(const wchar16* pStr, eastl::string16_s006b_5770& dst, TokenEntry* table, uint32_t count); // +0x38
    virtual bool FindTokenTranslation(const wchar16* pToken, eastl::string16_s006b_5770& dst); // +0x3c
    // Override of ITokenTranslator::TranslateToken (slot +0x10).
    virtual bool TranslateToken(const wchar16* pToken, eastl::string16_s006b_5770& dst);

    void ctor();                         // 0x006b6490 (thiscall constructor)

    TranslatorVector mTranslators;       // +0x08 (begin/end/cap)
    uint32_t mPad14;                     // +0x14
    uint32_t mPad18;                     // +0x18
    eastl::string16_s006b_5770 mGenericTokens[4];   // +0x1c
};
}
namespace App {
void ITokenTranslator::Slot00() {}
}
namespace App {
int  ITokenTranslator::AddRef() { return 1; }
}
namespace App {
int  ITokenTranslator::Release() { return 0; }
}
namespace App {
void* ITokenTranslator::Cast(uint32_t) { return 0; }
}
namespace App {
bool ITokenTranslator::TranslateToken(const wchar16*, eastl::string16_s006b_5770&) { return false; }
}
// ---- items of slice s006b5770 end

// ---- items of slice s006b8680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl sinf(float);
extern "C" float __cdecl cosf(float);
extern "C" float __cdecl sqrtf(float);
extern "C" unsigned int __cdecl strlen(const char*);
extern float DAT_016063f8[9];
extern float DAT_016062b8, DAT_016062bc, DAT_016062c0;
extern const char DAT_015311fc;
typedef unsigned int DWORD;
typedef unsigned int LCID;
extern "C" __declspec(dllimport) int __stdcall CompareStringW(LCID, DWORD, const wchar_t*, int, const wchar_t*, int);
extern "C" __declspec(dllimport) int __stdcall LCMapStringW(LCID, DWORD, const wchar_t*, int, wchar_t*, int);
int __cdecl ConvertEncoding6(const char*, int, int, void*, int*, int);   // 0x93c950
int __cdecl ConvertEncoding4(const char*, int, int, void*);              // 0x93cfb0
bool __cdecl FUN_0087da90(void*, const void*);
int __cdecl FUN_WriteUint16(void*, void*, int, int);   // 0x93a9d0
int __cdecl FUN_WriteUint32(void*, void*, int, int);   // 0x93aa70
int __cdecl FUN_IO_Field1(void*, void*);               // 0x6980c0
int __cdecl FUN_IO_Field2(void*, void*);               // 0x6980e0
int __cdecl FUN_ReadUint16_93a700(void*, void*, int, int);  // 0x93a700
int __cdecl FUN_ReadInt32(void*, void*, int, int);          // 0x93a780
int __cdecl FUN_IO_ReadField1(void*, void*);                // 0x698120
int __cdecl FUN_IO_ReadField2(void*, void*);                // 0x698140
struct WString {                                                  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WString& assign(const wchar_t* first, const wchar_t* last);    // 0x00423650
};
struct WVector {                                                  // eastl::vector<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void insert(wchar_t* pos, uint32_t n, const wchar_t& value);   // 0x006b6f80 (see s006b6920)
};
void __cdecl EASTL_allocator_deallocate(void* p);                 // 0x00f47380
struct MatX {
    uint16_t flags;
    uint16_t count;
    uint8_t  pad[0xc];
    float    m10;
    float    r14, r18, r1c, r20, r24, r28, r2c, r30, r34;
    void Rotate(float a);
};
struct BasisM {
    uint16_t flags;      // +0x00
    uint16_t count;      // +0x02
    float    f4;         // +0x04
    float    f8;         // +0x08
    float    mc;         // +0x0c
    float    m10;        // +0x10
    float    row0[3];    // +0x14
    float    row1[3];    // +0x20
    float    row2[3];    // +0x2c
    uint32_t Save(void* io);
    uint32_t Load(void* io);
    void     Build(float* out);
};
struct Basis3 {
    uint16_t f0;
    uint16_t f2;
    float    f4;
    float    f8;
    float    m10;
    float    row0[3];   // 0x14
    float    row1[3];   // 0x20
    float    row2[3];   // 0x2c
    void Normalize(const float* src);
};
// ---- items of slice s006b8680 end

// ---- items of slice s006b9510 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct XformKernel
{
    uint16_t flags;     // bit1: has matrix, bit2: has translation
    uint16_t pad;
    float    t[3];      // +4 translation
    float    s;         // +0x10 uniform scale
    float    m[9];      // +0x14 3x3 matrix (columns gathered as m[i], m[3+i], m[6+i])
};
static inline void RotElem(const XformKernel* xf, float* p)
{
    float x = p[0];
    float y = p[1];
    float z = p[2];
    float rx = (xf->m[3] * y + xf->m[6] * z) + x * xf->m[0];
    float ry = (xf->m[1] * x + xf->m[4] * y) + xf->m[7] * z;
    float rz = (xf->m[2] * x + xf->m[5] * y) + xf->m[8] * z;
    p[0] = rx;
    p[1] = ry;
    p[2] = rz;
}
static inline void FullElem(const XformKernel* xf, float* p)
{
    if (xf->flags & 2)
        RotElem(xf, p);
    float s = xf->s;
    float z = p[2];
    p[0] = s * p[0];
    p[1] = s * p[1];
    p[2] = s * z;
    float t2 = xf->t[2];
    float t1 = xf->t[1];
    p[0] = xf->t[0] + p[0];
    p[1] = p[1] + t1;
    p[2] = t2 + s * z;
}
static inline uint8_t Bit(uint16_t f, int n) { uint8_t b = (uint8_t)(f >> n); return b; }
static inline float* Adv(float* p, int stride) { return (float*)((char*)p + stride); }
static inline void RotScaleElem(const XformKernel* xf, float* p)
{
    if (xf->flags & 2)
        RotElem(xf, p);
    float s = xf->s;
    float z = p[2];
    p[0] = s * p[0];
    p[1] = s * p[1];
    p[2] = s * z;
}
// ---- items of slice s006b9510 end

// ---- items of slice s006ba2f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t g_emptyStrW[];                                 // 0x1667bae
extern const float        DAT_01485720;                             // 0x1485720
typedef unsigned int UINT;
typedef void* HWND;
extern "C" __declspec(dllimport) int __stdcall MessageBoxW(HWND, const wchar_t*, const wchar_t*, UINT);
void __cdecl EASTL_dealloc(void*);                                  // 0x00f47380
struct EStrW {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void* mpAllocator;
    EStrW() : mpBegin((wchar_t*)g_emptyStrW), mpEnd((wchar_t*)g_emptyStrW), mpCapacity((wchar_t*)g_emptyStrW + 1) {}
    ~EStrW() { if (((char*)mpCapacity - (char*)mpBegin) > 1 && mpBegin) EASTL_dealloc(mpBegin); }
};
int __cdecl EStrW_format(EStrW* s, const wchar_t* fmt, ...);
struct Matrix3 {
    float m[9];
    void Assign(const void* src);                                   // 0x0041cb40
};
struct cTransform {
    float    tx, ty, tz;
    uint16_t flags;
    uint16_t modCount;
    float    scale;
    Matrix3  rot;
    void PreRotateX(float angle);                                   // 0x005a2d90
    void PreRotateY(float angle);                                   // 0x004099b0
};
extern const float        DAT_016062b8_s006b_a2f0;                             // 0x16062b8
extern const float        DAT_016062bc_s006b_a2f0;                             // 0x16062bc
extern const unsigned int DAT_016062c0_s006b_a2f0;                             // 0x16062c0
extern const Matrix3      DAT_016063f8_s006b_a2f0;                             // 0x16063f8
void* __cdecl FUN_00453b20(Matrix3*, int, float);                   // builds a Matrix3
void* __cdecl FUN_0069b1c0(void*, int, int);                        // 0x0069b1c0
Matrix3* __cdecl FUN_006ba620(Matrix3* dst, const float* other);
Matrix3* __cdecl FUN_006ba620_ext(Matrix3* dst, const float* other);   // 0x006ba620
struct PropList {
    void Set(int, int);
    void SetInt(int, int);
    void SetFloat(int, float);
};
extern PropList* g_appProperties;   // 0x15fd918
struct MatOwner {
    void SetA(int, float);
    void SetB(int, int);
    void SetMatrix(Matrix3*);
};
struct XForm2 {
    uint16_t flags;
    uint16_t count;
    float    m4, m8, mc;
    float    m10;
    Matrix3  rot;   // 0x14
    void Apply(const float* other);
    void SetA(int a, float b);
    void SetB(int a, int b);
    void PreRotateX(float angle);
    void PreRotateY(float angle);
};
__declspec(noinline)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// pre-rotate wrappers
// ---------------------------------------------------------------------------
void __cdecl PreRotateY(cTransform*, float);
struct LogVector {
    void* mpBegin;   // 0x00
    void* mpEnd;     // 0x04
    void* mpCap;     // 0x08
    void erase(void* begin, void* end);                             // 0x00e25bd0
};
struct ILogReporter;
struct ILogReporterVtbl {
    void (__thiscall* mSlot0)(ILogReporter*);
    void (__thiscall* mSlot1)(ILogReporter*);
};
struct ILogReporter {
    ILogReporterVtbl* mpVtbl;
};
struct LogManager {
    LogVector     mVector;      // 0x00
    unsigned int  m0c;          // 0x0c
    unsigned int  m10;          // 0x10
    unsigned int  m14;          // 0x14
    unsigned int  m18;          // 0x18
    void*         m1c;          // 0x1c
    uint8_t       m20;          // 0x20
    uint8_t       mPad21[3];    // 0x21
    ILogReporter* m24;          // 0x24
    LogManager(void* p);
};
struct XFormMat {
    uint8_t  mFlags;        // 0x00
    uint8_t  mPad01[0x13];  // 0x01
    Matrix3  mRot;          // 0x14
};
#define XFORM_APPLY(P, V)                                                             \
    do {                                                                              \
        if (((P)->mFlags & 2) != 0) {                                                 \
            float fx = (V)[0], fy = (V)[1], fz = (V)[2];                              \
            (V)[0] = (((P)->mRot.m[3] * fy + (P)->mRot.m[6] * fz) + (P)->mRot.m[0] * fx); \
            (V)[1] = (((P)->mRot.m[1] * fx + (P)->mRot.m[4] * fy) + (P)->mRot.m[7] * fz); \
            (V)[2] = (((P)->mRot.m[2] * fx + (P)->mRot.m[5] * fy) + (P)->mRot.m[8] * fz); \
        }                                                                             \
    } while (0)
// ---- items of slice s006ba2f0 end

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl memcmp(const void*, const void*, size_t);
#pragma intrinsic(memcmp)
typedef wchar_t wchar16_s006b_b1c0;
int   __cdecl Sprintf8(char* buf, const char* fmt, ...);                            // 0x00938470
bool  __cdecl SPKeyFromName(void* key, const char* name, unsigned t, unsigned g);   // 0x0068d5a0
void* __cdecl EA_ConvertToString16Impl(void* dst, const char* src, unsigned len);   // 0x0093c5a0
void  __cdecl FUN_006bb0b0(const wchar16_s006b_b1c0* text, unsigned a, unsigned b);            // 0x006bb0b0
bool  __cdecl WideSearchEnvironmentPath(const wchar16_s006b_b1c0* p, wchar16_s006b_b1c0* buf, int);       // 0x00935e00
int   __cdecl WideSpawn(wchar16_s006b_b1c0* buf, const void* argv, int);                       // 0x00935d60
void  __cdecl VecWStrInsert(void* end, const void* val);                            // 0x00690c90
wchar16_s006b_b1c0* __cdecl eastl_search_w(wchar16_s006b_b1c0* f, wchar16_s006b_b1c0* l, const wchar16_s006b_b1c0* sf, const wchar16_s006b_b1c0* sl); // 0x005e8ff0
void  __cdecl EA_Free2(void* p);                                                    // 0x00f47380
__declspec(dllimport) char* __cdecl strstr(const char*, const char*);
struct CWStr {
    wchar16_s006b_b1c0* mpBegin;
    wchar16_s006b_b1c0* mpEnd;
    wchar16_s006b_b1c0* mpCapacity;
    void RangeInitialize(const wchar16_s006b_b1c0* psz);                                   // 0x00579a90
    void replace(wchar16_s006b_b1c0* f1, wchar16_s006b_b1c0* l1, const wchar16_s006b_b1c0* f2, const wchar16_s006b_b1c0* l2); // 0x005f8400
    ~CWStr()
    {
        if ((((int)((char*)mpCapacity - (char*)mpBegin)) & -2) > 2 && mpBegin) EA_Free2(mpBegin);
    }
};
namespace SP {
struct string16 { wchar16_s006b_b1c0* mpBegin; wchar16_s006b_b1c0* mpEnd; wchar16_s006b_b1c0* mpCapacity; int mAllocator; };
}
namespace SP {
struct IRefCounted {
virtual void AddRef();
virtual void Release();
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
};
}
namespace SP {
struct AutoRefCount {
    IRefCounted* mpObject;
    explicit AutoRefCount(IRefCounted* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
}
namespace SP {
class cString_s006b_b1c0 { public:
    AutoRefCount   mpTableResource;   // +0x00
    string16*      mpLocalString;     // +0x04
    const wchar16_s006b_b1c0* mpSourceCStr;      // +0x08
    unsigned       mPlaceholderId;    // +0x0c
    bool           mbHasTokens;       // +0x10
    bool           mField11;          // +0x11
    unsigned       mTableId;          // +0x14
    unsigned       mInstanceId;       // +0x18
    cString_s006b_b1c0();                                                    // 0x006b5060
    ~cString_s006b_b1c0();                                                   // 0x006b5240
    bool Load(unsigned tableID, unsigned instanceID, int group); // 0x006b54b0
    const wchar16_s006b_b1c0* GetText();                                     // 0x006b55c0
};
}
// ---- items of slice s006bb1c0 end

// @ 0x006b1d40
void SetSaveAreaFlag(uint8_t b)
{
  g_16046d8 = b;
}

// @ 0x006b42f0
bool Counter40::Inc()
{
  if (m40 != 0) {
    ++m40;
    return true;
  }
  return false;
}

// @ 0x006b4f40
bool __cdecl FUN_006b4f40(const char* p)
{
    ISteamApps* pApps = (ISteamApps*)SteamApps();
    if (pApps != 0)
        return pApps->v6(p);
    return 0;
}

// @ 0x006b4f60
CSink::CSink(uint32_t a, uint32_t b)
{
    mField0 = 0;
    mField4 = 0;
    mField8 = a;
    mFieldC = b;
    mField10 = true;
}

// @ 0x006b4f90
void CSink::FUN_006b4f90(bool b)
{
    mField10 = mField10 & b;
}

// @ 0x006b4fa0
void CSink::FUN_006b4fa0(const void* arg)
{
    if (mField10) {
        bool __cdecl FUN_00693390(uint32_t src, const void* arg, uint32_t placeholder);
        mField10 = mField10 & FUN_00693390(mField8, arg, mFieldC);
    }
}

// @ 0x006b4fd0
void CSink::FUN_006b4fd0(const void* arg)
{
    if (mField10) {
        bool __cdecl FUN_00694440(uint32_t src, const void* arg, uint32_t placeholder);
        mField10 = mField10 & FUN_00694440(mField8, arg, mFieldC);
    }
}

// @ 0x006b5000
void CSink::FUN_006b5000()
{
    if (mField4 != 0) {
        ((IRefCountedStub*)mField4)->v9();
        ((IRefCountedStub*)mField4)->v2();
        mField4 = 0;
        mField8 = 0;
    }
}

// @ 0x006b57f0
bool App::cStringDetokenizer::func28h(void* a, eastl::string16_s006b_5770& dst)
{
    return ProcessString(*(const wchar16**)((char*)a + 8), dst);
}

// @ 0x006b5810
bool App::cStringDetokenizer::HasTokens(const wchar16* pStr)
{
    if (pStr != 0) {
        return wcschr(pStr, L'~') != 0;
    }
    return false;
}

// @ 0x006b5840
void App::ITokenTranslator::func14h(int arg)
{
    // The detokenizer overrides this; mTranslators lives at +0x08 of the
    // derived object, so this base view is shared with cStringDetokenizer.
    App::cStringDetokenizer* self = (App::cStringDetokenizer*)this;
    App::intrusive_ptr* it = self->mTranslators.mpBegin + 1;
    App::intrusive_ptr* end = self->mTranslators.mpEnd;
    while (it < end) {
        it->ptr->func14h(arg);
        ++it;
    }
}

// @ 0x006b8d60
int __cdecl FUN_006b8d60(const char* src, wchar_t* dst, int dstLen)
{
    int n = dstLen;
    if (n == 0) return 0;
    int len = (int)strlen(src);
    n = n - 1;
    ConvertEncoding6(src, len, 8, dst, &n, 0x10);
    *(uint16_t*)(dst + n) = 0;
    return n;
}

// @ 0x006b8e10
int __cdecl FUN_006b8e10(const wchar_t* a, int na, const wchar_t* b, int nb, uint32_t flags)
{
    DWORD cmpFlags = 0;
    LCID locale = 0x400;
    LCID local[2];
    if (FUN_0087da90(local, &DAT_015311fc)) locale = local[0];
    if (flags & 0x20) locale = 0x7f;
    if (flags & 1) cmpFlags = 1;
    if (flags & 2) cmpFlags |= 0x10000;
    if (flags & 4) cmpFlags |= 2;
    if (flags & 8) cmpFlags |= 4;
    if (flags & 0x10) cmpFlags |= 0x20000;
    if (flags & 0x40) cmpFlags |= 0x1000;
    return CompareStringW(locale, cmpFlags, a, na, b, nb) - 2;
}

// @ 0x006b8f00
int __cdecl FUN_006b8f00(const char* src, int* dst)
{
    int len = (int)strlen(src);
    ConvertEncoding4(src, len, 8, dst);
    return (dst[1] - dst[0]) >> 1;
}

// @ 0x006b8f40
void __cdecl FUN_006b8f40(void* str)
{
    WString& dst = *(WString*)str;
    __try {
        LCID locale = 0x400;
        LCID local[2];
        if (FUN_0087da90(local, &DAT_015311fc)) locale = local[0];

        const wchar_t* src = dst.mpBegin;
        int cchSrc = (int)(dst.mpEnd - dst.mpBegin);
        int cchDest = LCMapStringW(locale, 0x100, src, cchSrc, 0, 0);

        // A zero-length result still allocates one element: LCMapStringW reports
        // failure as 0 and never as -1, so the original's cchDest + 1 == 0 guard
        // branch (a degenerate copy) is unreachable.
        WVector tmp = {0, 0, 0};
        wchar_t zero = 0;
        tmp.insert(tmp.mpBegin, (uint32_t)(cchDest + 1), zero);

        LCMapStringW(locale, 0x100, src, cchSrc, tmp.mpBegin, cchDest);

        wchar_t* end = tmp.mpBegin;
        while (*end) ++end;
        dst.assign(tmp.mpBegin, end);

        if (tmp.mpBegin != 0 && *(int*)((char*)tmp.mpBegin - 4) != 0)
            EASTL_allocator_deallocate(tmp.mpBegin);
    } __except (1) {
    }
}

// @ 0x006b9050
void MatX::Rotate(float a)
{
    float s = sinf(a);
    float c = cosf(a);
    float v14 = r14, v18 = r18, v1c = r1c;
    float v20 = r20, v24 = r24, v28 = r28;
    float v2c = r2c, v30 = r30, v34 = r34;
    r2c = v2c * c + v14 * s;
    r30 = v30 * c + v18 * s;
    r34 = v34 * c + v1c * s;
    flags |= 2;
    count = (uint16_t)(count + 1);
    r14 = v14 * -s + v20 * c;
    r18 = v18 * -s + v24 * c;
    r1c = v1c * -s + v28 * c;
}

// @ 0x006b9190
uint32_t BasisM::Save(void* io)
{
    uint16_t f = flags;
    if (m10 == 1.0f) f &= 0xfffe;
    else             f |= 1;
    uint32_t local = (uint32_t)(f | 8);
    FUN_WriteUint16(io, &local, 1, 0);
    if (f & 1) {
        float v = m10;
        FUN_WriteUint32(io, &v, 1, 0);
    }
    if (f & 2) FUN_IO_Field1(io, &row0[0]);
    if (f & 4) FUN_IO_Field2(io, &f4);
    return (uint32_t)io;
}

// @ 0x006b9230
uint32_t BasisM::Load(void* io)
{
    row0[0] = DAT_016063f8[0]; row0[1] = DAT_016063f8[1]; row0[2] = DAT_016063f8[2];
    row1[0] = DAT_016063f8[3]; row1[1] = DAT_016063f8[4]; row1[2] = DAT_016063f8[5];
    row2[0] = DAT_016063f8[6]; row2[1] = DAT_016063f8[7]; row2[2] = DAT_016063f8[8];
    m10 = 1.0f;
    f4 = DAT_016062b8;
    f8 = DAT_016062bc;
    mc = DAT_016062c0;
    flags = 0;
    count = 0;
    FUN_ReadUint16_93a700(io, this, 1, 0);
    if (flags & 1) FUN_ReadInt32(io, &m10, 1, 0);
    if (flags & 2) FUN_IO_ReadField1(io, &row0[0]);
    if (flags & 4) FUN_IO_ReadField2(io, &f4);
    return (uint32_t)io;
}

// @ 0x006b92d0
void Basis3::Normalize(const float* src)
{
    row0[0] = src[0]; row0[1] = src[1]; row0[2] = src[2];
    row1[0] = src[4]; row1[1] = src[5]; row1[2] = src[6];
    row2[0] = src[8]; row2[1] = src[9]; row2[2] = src[10];
    f4 = src[12];
    *(float*)((char*)this + 8) = src[13];
    *(float*)((char*)this + 0xc) = src[14];
    float l0 = sqrtf(row0[0]*row0[0] + row0[1]*row0[1] + row0[2]*row0[2]);
    float l1 = sqrtf(row1[0]*row1[0] + row1[1]*row1[1] + row1[2]*row1[2]);
    float l2 = sqrtf(row2[0]*row2[0] + row2[1]*row2[1] + row2[2]*row2[2]);
    float i0 = 1.0f / l0, i1 = 1.0f / l1, i2 = 1.0f / l2;
    row0[0]*=i0; row0[1]*=i0; row0[2]*=i0;
    row1[0]*=i1; row1[1]*=i1; row1[2]*=i1;
    row2[0]*=i2; row2[1]*=i2; row2[2]*=i2;
    m10 = (l2 + l1 + l0) * 0.33333334f;
}

// @ 0x006b9440
void BasisM::Build(float* out)
{
    float s = m10;
    out[0] = row0[0] * s; out[1] = row0[1] * s; out[2] = row0[2] * s;
    out[4] = row1[0] * s; out[5] = row1[1] * s; out[6] = row1[2] * s;
    out[8] = row2[0] * s; out[9] = row2[1] * s; out[10] = row2[2] * s;
    out[12] = f4; out[13] = f8; out[14] = mc;
    out[3] = 0.0f; out[7] = 0.0f; out[11] = 0.0f; out[15] = 1.0f;
}

// @ 0x006b9510
void __cdecl FUN_006b9510(const XformKernel* xf, int count, float* p, int stride)
{
    uint16_t f = xf->flags;
    if (Bit(f, 1) & 1)
    {
        for (int i = 0; i < count; i++)
        {
            FullElem(xf, p);
            p = Adv(p, stride);
        }
        return;
    }
    float s = xf->s;
    if (s != 1.0f && Bit(f, 2) & 1)
    {
        float t0 = xf->t[0], t1 = xf->t[1], t2 = xf->t[2];
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] * s + t0;
            p[1] = p[1] * s + t1;
            p[2] = s * p[2] + t2;
            p = Adv(p, stride);
        }
    }
    else if (s != 1.0f)
    {
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] * s;
            p[1] = p[1] * s;
            p[2] = s * p[2];
            p = Adv(p, stride);
        }
    }
    else if (Bit(f, 2) & 1)
    {
        float t0 = xf->t[0], t1 = xf->t[1], t2 = xf->t[2];
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] + t0;
            p[1] = p[1] + t1;
            p[2] = t2 + p[2];
            p = Adv(p, stride);
        }
    }
}

// @ 0x006b9dc0
void __cdecl FUN_006b9dc0(const XformKernel* xf, int count, float* p, int stride)
{
    if (Bit(xf->flags, 1) & 1)
    {
        for (int i = 0; i < count; i++)
        {
            RotScaleElem(xf, p);
            p = Adv(p, stride);
        }
        return;
    }
    float s = xf->s;
    if (s != 1.0f)
    {
        for (int i = 0; i < count; i++)
        {
            p[0] = p[0] * s;
            p[1] = p[1] * s;
            p[2] = s * p[2];
            p = Adv(p, stride);
        }
    }
}

// @ 0x006ba2f0
void __cdecl FUN_006ba2f0(void* ctx, int count, char* data, int stride)
{
    XFormMat* p = (XFormMat*)ctx;
    if (((p->mFlags >> 1) & 1) == 0) return;

    int done = 0;
    if (count > 3)
    {
        unsigned int blocks = ((unsigned int)(count - 4) >> 2) + 1;
        done = (int)(blocks * 4);
        do
        {
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            XFORM_APPLY(p, (float*)data); data += stride;
            --blocks;
        } while (blocks != 0);
    }
    if (done < count)
    {
        int remaining = count - done;
        do
        {
            XFORM_APPLY(p, (float*)data); data += stride;
        } while (--remaining != 0);
    }
}

// @ 0x006ba620
Matrix3* __cdecl FUN_006ba620(Matrix3* dst, const float* other)
{
    float r[9];
    r[0] = (dst->m[0] * other[0] + dst->m[1] * other[3]) + dst->m[2] * other[6];
    r[1] = (dst->m[0] * other[1] + dst->m[1] * other[4]) + dst->m[2] * other[7];
    r[2] = (dst->m[0] * other[2] + dst->m[1] * other[5]) + dst->m[2] * other[8];
    r[3] = (dst->m[3] * other[0] + dst->m[4] * other[3]) + dst->m[5] * other[6];
    r[4] = (dst->m[3] * other[1] + dst->m[4] * other[4]) + dst->m[5] * other[7];
    r[5] = (dst->m[3] * other[2] + dst->m[4] * other[5]) + dst->m[5] * other[8];
    r[6] = (dst->m[6] * other[0] + dst->m[7] * other[3]) + dst->m[8] * other[6];
    r[7] = (dst->m[6] * other[1] + dst->m[7] * other[4]) + dst->m[8] * other[7];
    r[8] = (dst->m[6] * other[2] + dst->m[7] * other[5]) + dst->m[8] * other[8];
    float* d = dst->m;
    const float* s = r;
    for (int i = 0; i < 9; ++i) *d++ = *s++;
    return dst;
}

// @ 0x006ba800
void MatOwner::SetA(int a, float b)
{
    Matrix3 tmp;
    void* r = FUN_00453b20(&tmp, a, b);
    Matrix3 m;
    m.Assign(r);
    SetMatrix(&m);
}

// @ 0x006ba840
void MatOwner::SetB(int a, int b)
{
    Matrix3 m;
    void* r = FUN_0069b1c0(&m, a, b);
    SetMatrix((Matrix3*)r);
}

// @ 0x006ba870
void XForm2::Apply(const float* other)
{
    uint16_t f = flags;
    if (f & 2) {
        FUN_006ba620_ext(&rot, other);
    } else {
        rot = *(const Matrix3*)other;
        flags = (uint16_t)(f | 2);
    }
    float a = m4, b = m8, c = mc;
    m4 = ((other[3] * b + other[6] * c) + other[0] * a);
    m8 = ((other[1] * a + other[4] * b) + other[7] * c);
    mc = ((other[2] * a + other[5] * b) + other[8] * c);
    count = (uint16_t)(count + 1);
}

// @ 0x006ba940
void XForm2::PreRotateX(float angle)
{
    cTransform t;
    t.tx = 0.0f;
    t.ty = DAT_016062b8_s006b_a2f0;
    t.tz = DAT_016062bc_s006b_a2f0;
    t.flags = (uint16_t)DAT_016062c0_s006b_a2f0;
    t.modCount = (uint16_t)(DAT_016062c0_s006b_a2f0 >> 16);
    t.scale = DAT_01485720;
    t.rot.Assign(&DAT_016063f8_s006b_a2f0);
    t.PreRotateX(angle);

    if ((flags & 2) == 0) {
        rot = t.rot;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&t.rot);
    }

    float a = m4, b = m8, c = mc;
    m4 = ((a * t.rot.m[0] + b * t.rot.m[3]) + c * t.rot.m[6]);
    m8 = ((a * t.rot.m[1] + c * t.rot.m[7]) + b * t.rot.m[4]);
    mc = ((a * t.rot.m[2] + c * t.rot.m[8]) + b * t.rot.m[5]);
    count = (uint16_t)(count + 1);
}

// @ 0x006baa70
void XForm2::PreRotateY(float angle)
{
    cTransform t;
    t.tx = 0.0f;
    t.ty = DAT_016062b8_s006b_a2f0;
    t.tz = DAT_016062bc_s006b_a2f0;
    t.flags = (uint16_t)DAT_016062c0_s006b_a2f0;
    t.modCount = (uint16_t)(DAT_016062c0_s006b_a2f0 >> 16);
    t.scale = DAT_01485720;
    t.rot.Assign(&DAT_016063f8_s006b_a2f0);
    t.PreRotateY(angle);

    if ((flags & 2) == 0) {
        rot = t.rot;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&t.rot);
    }

    float a = m4, b = m8, c = mc;
    m4 = ((a * t.rot.m[0] + b * t.rot.m[3]) + c * t.rot.m[6]);
    m8 = ((a * t.rot.m[1] + c * t.rot.m[7]) + b * t.rot.m[4]);
    mc = ((a * t.rot.m[2] + c * t.rot.m[8]) + b * t.rot.m[5]);
    count = (uint16_t)(count + 1);
}

// @ 0x006baba0
void XForm2::SetA(int a, float b)
{
    Matrix3 tmp;
    void* r = FUN_00453b20(&tmp, a, b);
    Matrix3 m;
    m.Assign(r);

    if ((flags & 2) == 0) {
        rot = m;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)&m);
    }

    float u = m4, v = m8, w = mc;
    m4 = ((u * m.m[0] + v * m.m[3]) + w * m.m[6]);
    m8 = ((u * m.m[1] + v * m.m[4]) + w * m.m[7]);
    mc = ((u * m.m[2] + v * m.m[5]) + w * m.m[8]);
    count = (uint16_t)(count + 1);
}

// @ 0x006bac90
void XForm2::SetB(int a, int b)
{
    Matrix3 m;
    Matrix3* r = (Matrix3*)FUN_0069b1c0(&m, a, b);

    if ((flags & 2) == 0) {
        rot = *r;
        flags = (uint16_t)(flags | 2);
    } else {
        FUN_006ba620(&rot, (float*)r);
    }

    float u = m4, v = m8, w = mc;
    m4 = ((r->m[3] * v + r->m[6] * w) + r->m[0] * u);
    m8 = ((r->m[1] * u + r->m[4] * v) + r->m[7] * w);
    mc = ((r->m[2] * u + r->m[5] * v) + r->m[8] * w);
    count = (uint16_t)(count + 1);
}

// @ 0x006badd0
LogManager::LogManager(void* p)
{
    mVector.mpBegin = 0;
    mVector.mpEnd = 0;
    mVector.mpCap = 0;
    m24 = 0;
    m1c = p;
    m14 = 0;
    mVector.erase(mVector.mpBegin, mVector.mpEnd);
    m18 = m18 + 1;
    m20 = 1;
    if (m24 != 0) {
        ILogReporter* r = m24;
        m24 = 0;
        r->mpVtbl->mSlot1(r);
    }
    m18 = 0;
}

// @ 0x006bae50
void __cdecl FUN_006bae50(void)
{
    PropList* p = g_appProperties;
    p->Set(2, 1);
    p->Set(3, 1);
    p->Set(4, 1);
    p->Set(5, 1);
    p->Set(6, 1);
    p->Set(0xb, 1);
    p->SetInt(0x1c, 0x800);
    p->SetFloat(0x1d, 3.0f);
}

// @ 0x006bb0b0
void __cdecl FUN_006bb0b0(const wchar_t* msg, int line, int type)
{
    UINT uType = 0x52000;
    if (type == 0) uType = 0x52040;
    else if (type == 1) uType = 0x52030;
    else if (type == 2) uType = 0x52010;
    EStrW str;
    EStrW_format(&str, L"%ls [%d]", msg, line);
    MessageBoxW(0, str.mpBegin, L"Alert", uType);
}

// @ 0x006bb1c0
void __cdecl FUN_006bb1c0(const char* src, unsigned id, unsigned arg2, const char* name)
{
    char buf[128];
    const char* pName = name;
    if (name == 0) {
        Sprintf8(buf, "AppConfig!0x%08x", id);
        pName = buf;
    } else if (strstr(name, "!") == 0) {
        Sprintf8(buf, "AppConfig!%hs", name);
        pName = buf;
    }

    unsigned key[3] = { 0, 0, 0 };
    SPKeyFromName(key, pName, 0, 0);

    char conv[12];
    void* r = EA_ConvertToString16Impl(conv, src, 0xffffffff);
    CWStr wstr;
    wstr.RangeInitialize(*(const wchar16_s006b_b1c0**)r);

    // replace every L"\n" with L"~br~".
    while (true) {
        unsigned hayLen = (unsigned)(wstr.mpEnd - wstr.mpBegin);
        unsigned nLen = 1;
        if (hayLen < nLen) break;
        wchar16_s006b_b1c0* m = eastl_search_w(wstr.mpBegin, wstr.mpEnd, L"\n", L"\n" + nLen);
        if (m == wstr.mpEnd && nLen != 0) break;
        long pos = (long)(m - wstr.mpBegin);
        if (pos == -1) break;
        unsigned remaining = hayLen - (unsigned)pos;
        unsigned take = remaining < nLen ? remaining : nLen;
        wstr.replace(wstr.mpBegin + pos, wstr.mpBegin + pos + take, L"~br~", L"~br~" + 4);
    }

    SP::cString_s006b_b1c0 str;
    bool ok = str.Load(key[2], key[0], 0);
    if (!ok) {
        // fallback: replace every L"~br~" with L"\n".
        while (true) {
            unsigned hayLen = (unsigned)(wstr.mpEnd - wstr.mpBegin);
            unsigned nLen = 4;
            if (hayLen < nLen) break;
            wchar16_s006b_b1c0* m = eastl_search_w(wstr.mpBegin, wstr.mpEnd, L"~br~", L"~br~" + nLen);
            if (m == wstr.mpEnd && nLen != 0) break;
            long pos = (long)(m - wstr.mpBegin);
            if (pos == -1) break;
            unsigned remaining = hayLen - (unsigned)pos;
            unsigned take = remaining < nLen ? remaining : nLen;
            wstr.replace(wstr.mpBegin + pos, wstr.mpBegin + pos + take, L"\n", L"\n" + 1);
        }
        FUN_006bb0b0(wstr.mpBegin, id, arg2);
    } else {
        FUN_006bb0b0(str.GetText(), id, arg2);
    }
}

// @ 0x006bb4b0
bool __cdecl FUN_006bb4b0(unsigned a, unsigned b, const wchar16_s006b_b1c0* path, ...)
{
    (void)a; (void)b;
    wchar16_s006b_b1c0 buf[130];
    if (!WideSearchEnvironmentPath(path, buf, 0))
        return false;

    const wchar16_s006b_b1c0* args[65];
    int n = 0;
    args[n++] = path;
    const wchar16_s006b_b1c0** ap = (const wchar16_s006b_b1c0**)&path + 1;
    const wchar16_s006b_b1c0* v;
    while ((v = *ap++) != 0) {
        if (n < 64) args[n++] = v;
        else        VecWStrInsert(&args[n], &v);
    }
    args[n] = 0;

    int r = WideSpawn(buf, args, 0);
    return r == 0;
}
