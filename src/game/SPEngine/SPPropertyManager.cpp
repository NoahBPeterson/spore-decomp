// src/game/SPEngine/SPPropertyManager.cpp -- migrated from slice(s) s006aa3f0, s006a9470, s006a8610, s006a7e40, s006a6340, s006a5690, s006a4990, s006a4770, s006a32a0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPPropertyManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyManager.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArguments.h"
#include "SP/cPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned int FNVHash(const char* s, unsigned int seed, int dummy); // 0x00932e80
extern void* g_sAppProperties;      // 0x015fd918
extern "C" void  EA_Dealloc(void* p);
extern "C" void* EA_Alloc(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" float atan2f_(float, float);
extern "C" void Fill16a(void* begin, int n, void* tmp, const void* value);   // 0x0047cae0
extern "C" void Fill16b(void* begin, int n, void* tmp, const void* value);   // 0x00b11580
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "EA/ArgScript/cArguments.h"
#include <float.h>
#include "SP/cString.h"
#include "EA/ResourceMan/Factory.h"
#include <intrin.h>
#include "EA/ArgScript/cExprFunction.h"

// ---- items of slice s006a32a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Variant {
    uint32_t d0;        // +0x00
    uint32_t d1;        // +0x04
    uint32_t d2;        // +0x08
    uint32_t d3;        // +0x0c
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12

    void Destruct(int b);                       // 0x0093db80
    void SetType(int type, int a, const void* p, int size, int b);  // 0x0093dd80

    Variant& SetVec21(const void* p);   // 0x006a34a0
    Variant& SetVec30(const void* p);   // 0x006a3510
    Variant& SetVec31(const void* p);   // 0x006a3570
    Variant& SetVec32(const void* p);   // 0x006a3610
};
namespace EA {
namespace ArgScript {
class cArguments_s006a_32a0 {
public:
    void* MainArguments(int b);     // 0x00838320
};
}
}
struct cPropertyManager {
    uint8_t  pad0[0x114];
    char*    mVecBegin;         // +0x114
    char*    mVecEnd;           // +0x118
    uint16_t mPad2[2];
    uint8_t  mInAppProperties;  // +0x1d0  (retail appears shifted; used as +0x1e8 below)

    int  GetSupportedTypes(uint32_t* p, unsigned n);  // 0x006a3400
    int  Count();                                      // 0x006a39a0
    bool GetAt(int idx, uint32_t* out);                // 0x006a39d0
};
struct cCommandStub {
    void Forward(int a, int b);     // 0x006a3310
};
struct cAppPropsCommand {
    uint8_t pad0[4];
    void*   mOwner;                 // +0x4
    uint8_t pad1[0x28];
    void*   mManager;               // +0x30
    void Execute(void* args);       // 0x006a3ce0
    void OnEndParse(int b);         // 0x006a3d10
};
struct cDealloc {
    uint8_t pad0[4];
    void Release();     // 0x006a4360
};
struct String {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void* mAlloc;       // +0xc
    String& assign(const char* p);
    String& assign(const char* pBegin, const char* pEnd);
};
namespace EA {
namespace ArgScript {
class cIMetaCommand {
public:
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mState;       // +0xc
    void OnRegister(void* parser, int b);   // 0x0083c7f0 (ret 8, only parser used)
};
}
}
void StringEvalString(void* out, void* arg);              // 0x0083dc00
struct cCommandStateA {
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mCmd;         // +0xc
    void OnRegister(void* parser, int b);
};
struct cCommandStateB {
    void* vftable;      // +0
    void* mParser;      // +4
    int   mRefCount;    // +8
    int   mState;       // +0xc
    uint8_t pad[0x20];  // +0x10
    void* mCmd;         // +0x30
    void OnRegister(void* parser, int b);
    void OnRegister2(void* parser, int b);  // 0x0083c780 (external)
};
struct Float3 { float x, y, z; };
struct cPropertyList {
    void* vftable;           // +0
    void* mRef;              // +4
    uint32_t mKey0, mKey1, mKey2;  // +8,0xc,0x10
    uint8_t pad[0x20];       // +0x14
    void* vfn0_idx;          // placeholder
    cPropertyList* Ctor(const char* name);
    void Release(int);
    void AddRef();
};
struct cPropertyManager2 {
    void* vftable;              // +0
    void* mBase;                // +4
    uint8_t pad[0x20];          // +8
    void* mFactoryVt;           // +0x24 area
    bool CreateResource(int* info, int a, int b, int* out);
};
struct FeedbackCmd {
    uint8_t pad0[0x1c];
    uint8_t mActive;        // +0x1c
    uint8_t pad1[3];
    uint8_t mMap[0x20];     // +0x20  (rbtree)
    void*   mEnd;           // +0x40 ... approx
};
static const char kAllocPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct Vec38 {
    void* begin; void* end; void* cap;
    Vec38* Init(int n, const void* alloc);
};
struct Vec208 {
    void* begin; void* end; void* cap;
    Vec208* Init(unsigned n, const void* alloc);
};
struct VecC {
    void* begin; void* end; void* cap;
    VecC* Init(unsigned n, const void* alloc);
    VecC* InitValue(unsigned n, const float* value);
};
struct Vec8 {
    void* begin; void* end; void* cap;
    Vec8* Init(unsigned n, const float* value);
    void* Alloc(unsigned n, const void* x);   // 0x006a40a0 (external)
};
struct E208 { int32_t a; int32_t b; int16_t c; char rest[0x1fe]; };
struct E12 { uint32_t x, y, z; };
struct Vec10 {
    void* begin; void* end; void* cap;
    Vec10* Init(int n, const void* value);
    void Alloc(int n, const void* value);   // 0x007c7a40 (external)
};
struct Vec10b {
    void* begin; void* end; void* cap;
    Vec10b* Init(int n, const void* value);
    void Alloc(int n, const void* value);   // 0x007c7a40 (external)
};
// ---- items of slice s006a32a0 end

// ---- items of slice s006a4770 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  Fill18(void* dst, int n, const void* value, int m);                                  // 0x00511990
struct Box18 { float x, y, z; float nx, ny, nz; };
struct Vec18 {
    void* begin; void* end; void* cap;
    Vec18* Init(unsigned n, const void* alloc);
};
// ---- items of slice s006a4770 end

// ---- items of slice s006a4990 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4290 4100)
static const float kFloatMax = 3.402823466e+38F;
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Vector2 { float x, y; };
struct Vector4 { float x, y, z, w; };
struct ColorRGB { float r, g, b; };
struct ColorRGBA { float r, g, b, a; };
struct BoundingBox {
    Vector3 lower;  // +0x00
    Vector3 upper;  // +0x0c
    // default: inverted (empty) box
    BoundingBox()
    {
        lower = Vector3(kFloatMax, kFloatMax, kFloatMax);
        upper = Vector3(-kFloatMax, -kFloatMax, -kFloatMax);
    }
};
struct Transform {
    uint32_t mData[0x38 / 4];
    Transform();                // 0x00409930
};
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
struct Flags96 {
    uint32_t mWord[3];
    Flags96() { reset(); }
    void reset() { memset(mWord, 0, sizeof(mWord)); }
};
struct LocalizedString {
    uint32_t mData[5];
    LocalizedString();          // 0x006b5060
    ~LocalizedString();         // 0x006b5240
};
namespace eastl {
union EmptyString {
    uint32_t mUint32;
    char     mEmpty8[1];
    wchar_t  mEmpty16[1];
};
}
namespace eastl {
extern EmptyString gEmptyString;   // 0x01667bac
}
namespace eastl {
struct string8_s006a_4990 {    // basic_string<char>
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator;
    string8_s006a_4990() { mpBegin = gEmptyString.mEmpty8; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~string8_s006a_4990() throw();                         // 0x00530670
};
}
namespace eastl {
struct string16_s006a_4990 {   // basic_string<wchar_t>
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    string16_s006a_4990() { mpBegin = gEmptyString.mEmpty16; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~string16_s006a_4990() { DeallocateSelf(); }
    void DeallocateSelf() throw();              // 0x00933960
};
}
struct Variant_s006a_4990 {
    enum { kFlagCleanup = 4, kFlagArray = 0x80, kSetFlagsCopy = 0x18 };
    char     mValue[0x10];
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    __forceinline Variant_s006a_4990(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n)
    {
        mFlags = 0;
        mTypeId = 0;
        Set(type, flags, p, size, n);
    }
    ~Variant_s006a_4990() { if (mFlags & kFlagCleanup) Destruct(0); }
    void Destruct(int);                                                            // 0x0093db80
    bool Set(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n);  // 0x0093dd80
    Variant_s006a_4990& operator=(const Variant_s006a_4990& x);                                          // 0x00542b80

    Variant_s006a_4990& operator=(const bool& v);                     // 0x00422e20
    Variant_s006a_4990& operator=(const int& v);                      // 0x00422eb0
    Variant_s006a_4990& operator=(const unsigned int& v);             // 0x00427fd0
    Variant_s006a_4990& operator=(const float& v);                    // 0x00428060
    Variant_s006a_4990& operator=(const eastl::string8_s006a_4990& v);           // 0x004b5dd0
    Variant_s006a_4990& operator=(const eastl::string16_s006a_4990& v);          // 0x004279d0
    Variant_s006a_4990& operator=(const ResourceKey& v);              // 0x00422f40
    Variant_s006a_4990& operator=(const Flags96& v);                  // 0x006a34a0
    Variant_s006a_4990& operator=(const LocalizedString& v);          // 0x006a36b0
    Variant_s006a_4990& operator=(const Vector2& v);                  // 0x006a3510
    Variant_s006a_4990& operator=(const Vector3& v);                  // 0x006a3570
    Variant_s006a_4990& operator=(const Vector4& v);                  // 0x006a35e0
    Variant_s006a_4990& operator=(const ColorRGB& v);                 // 0x006a3610
    Variant_s006a_4990& operator=(const ColorRGBA& v);                // 0x006a3680
    Variant_s006a_4990& operator=(const Transform& v);                // 0x006a3fa0
    Variant_s006a_4990& operator=(const BoundingBox& v)
    {
        if (mFlags & kFlagCleanup)
            Destruct(1);
        Set(0x39, 0, &v, sizeof(BoundingBox), 1);
        return *this;
    }
};
extern const Vector2   kDefaultVector2;     // 0x016029c8
extern const Vector3   kDefaultVector3;     // 0x016029d0
extern const Vector4   kDefaultVector4;     // 0x016029dc
extern const ColorRGB  kDefaultColorRGB;    // 0x0152f070
extern const ColorRGBA kDefaultColorRGBA;   // 0x0152f0d0
static const uint32_t kArray = 0x80000000;
#define SET_EMPTY_ARRAY(out, type, size)                                  \
    *(out) = Variant_s006a_4990((type), Variant_s006a_4990::kSetFlagsCopy, 0, (size), 0);       \
    (out)->mFlags |= Variant_s006a_4990::kFlagArray;                                 \
    return true
// ---- items of slice s006a4990 end

// ---- items of slice s006a5690 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  DoInsertValue(void* dst, const void* src, int n);           // 0x011e0744
extern "C" void UninitFillN56(void* dst, int n, const void* value, const void* m);  // 0x0042e680
extern "C" void UninitFillN16(void* dst, int n, const void* value, const void* m);  // 0x00555b40
extern "C" void Matrix3Assign(void* dst, const void* src);                  // 0x0041cb40
extern "C" void VariantRelease(int* p);                                     // 0x006ad050
extern "C" void VariantHold(int* p);                                        // 0x006ad010
struct Variant_s006a_5690 {
    uint32_t d0, d1, d2, d3;
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
};
struct String_s006a_5690 {
    void*   mpBegin;    // +0
    void*   mpEnd;      // +4
    void*   mpCapacity; // +8
    void*   mAlloc;     // +0xc
    String_s006a_5690& assign(const char* p);
    void    append(const char* pBegin, const char* pEnd);
};
namespace EA {
namespace ArgScript {
void MakeCaseInsensitive(const char* src, char* dst);   // 0x00840cc0
}
}
struct HashTable {
    void Find(void* out, const void* key);              // 0x007e2ea0
    void Find2(void* out, const void* key);             // 0x0041fb20
};
struct HashMapKey8 {
    void* operator[](const void* key);                 // 0x0041cd60
};
struct ArgMgr {
    bool FUN_006a58a0(int msg, int* v);            // ret 8
    void FUN_006a59f0(int* v);                     // ret 4
    void FUN_006a5a90(int a, int count, int* p);   // ret 0xc
    void FUN_006a5b80(int count, int* p);          // ret 8
    void FUN_006a5c50(int* out, void* key);        // ret 0xc
    bool FUN_006a5f70(const char* name, uint32_t* out);
    bool FUN_006a5fd0(const char* name, uint32_t* out);
    bool FUN_006a60b0(int a, int b, int* out);
    void FUN_006a61c0(int a, int b);
    bool FUN_006a6240(const char* name, uint32_t* out);
};
struct Vec10s {
    void* begin; void* end; void* cap;
    Vec10s* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x007c7a40
};
struct Vec38b {
    void* begin; void* end; void* cap;
    Vec38b* Init(unsigned n, const void* value);
    void Alloc(unsigned n, const void* value);   // 0x006a4130
};
struct VecU32 {
    void* begin; void* end; void* cap;
    VecU32* Init(unsigned n, const void* alloc);
    void Alloc(unsigned n, const void* alloc);   // 0x004aa350
};
// ---- items of slice s006a5690 end

// ---- items of slice s006a6340 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector2_s006a_6340 {
    float x, y;
    Vector2_s006a_6340() {}
    Vector2_s006a_6340(const Vector2_s006a_6340& o) : x(o.x), y(o.y) {}
    Vector2_s006a_6340& operator=(const Vector2_s006a_6340& o) { x = o.x; y = o.y; return *this; }
};
struct Vector3_s006a_6340 {
    float x, y, z;
    Vector3_s006a_6340() {}
    Vector3_s006a_6340(const Vector3_s006a_6340& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s006a_6340& operator=(const Vector3_s006a_6340& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vector4_s006a_6340 {
    float x, y, z, w;
    Vector4_s006a_6340() {}
    Vector4_s006a_6340(const Vector4_s006a_6340& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    Vector4_s006a_6340& operator=(const Vector4_s006a_6340& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
struct ColorRGB_s006a_6340 {
    float r, g, b;
    ColorRGB_s006a_6340() {}
    ColorRGB_s006a_6340(const ColorRGB_s006a_6340& o) : r(o.r), g(o.g), b(o.b) {}
    ColorRGB_s006a_6340& operator=(const ColorRGB_s006a_6340& o) { r = o.r; g = o.g; b = o.b; return *this; }
};
struct ColorRGBA_s006a_6340 {
    float r, g, b, a;
    ColorRGBA_s006a_6340() {}
    ColorRGBA_s006a_6340(const ColorRGBA_s006a_6340& o) : r(o.r), g(o.g), b(o.b), a(o.a) {}
    ColorRGBA_s006a_6340& operator=(const ColorRGBA_s006a_6340& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
struct Matrix3 { float m[9]; };
struct BoundingBox_s006a_6340 {
    Vector3_s006a_6340 lower;  // +0x00
    Vector3_s006a_6340 upper;  // +0x0c
    BoundingBox_s006a_6340() {}
    __forceinline BoundingBox_s006a_6340(const Vector3_s006a_6340& lo, const Vector3_s006a_6340& hi) : lower(lo), upper(hi) {}
};
struct Transform_s006a_6340 {
    uint16_t mnFlags;           // +0x00
    uint16_t mnTransformCount;  // +0x02
    Vector3_s006a_6340  mOffset;           // +0x04
    float    mfScale;           // +0x10
    Matrix3  mRotation;         // +0x14
    Transform_s006a_6340();                // 0x00409930 (pos 0, scale 1, rotation identity)
    void SetOffset(const Vector3_s006a_6340& v)   { mnFlags |= 4; mnTransformCount++; mOffset = v; }
    void SetScale(float s)             { mfScale = s; mnTransformCount++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnFlags |= 2; mnTransformCount++; }
};
struct Flags96_s006a_6340 {
    uint32_t mWord[3];
    Flags96_s006a_6340() { mWord[0] = 0; mWord[1] = 0; mWord[2] = 0; }
    void set(uint32_t bit) { mWord[bit >> 5] |= 1u << (bit & 31); }
};
struct LocalizedString_s006a_6340 {
    uint32_t mTableID;      // +0x000
    uint32_t mInstanceID;   // +0x004
    wchar_t  mBuffer[256];  // +0x008
    LocalizedString_s006a_6340() : mTableID(0xffffffff), mInstanceID(0xffffffff) { mBuffer[0] = 0; }
};
struct allocator_tag {};  // empty allocator argument (a 1-byte temporary in the original)
struct string8 {  // eastl::basic_string<char>, 16 bytes
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator;
    string8(const char* p, const allocator_tag& a = allocator_tag());  // 0x0057ed80
    ~string8();                                                        // 0x00530670
    string8& assign(const char* p);                                    // 0x006a4380
    string8& operator=(const char* p) { return assign(p); }
};
struct string16 {  // eastl::basic_string<wchar_t>, 16 bytes
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                              // 0x00933960
    string16& assign(const wchar_t* first, const wchar_t* last);       // 0x00423650
    string16& operator=(const string16& x) {
        if (&x != this) assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    const wchar_t* c_str() const { return mpBegin; }
};
namespace EA {
 string16 ConvertToString16(const char* p, int len = -1);   // 0x0093c5a0
}
template <class T>
struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator;
    SpVector(int n, const allocator_tag& a);  // 0x00686430 / 0x006a6310 / 0x006a4580 ...
    ~SpVector() {
        if (mpBegin && reinterpret_cast<int*>(mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    T& operator[](int i) { return mpBegin[i]; }
    T* data() { return mpBegin; }
};
template <class T>
struct SpVectorNP {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator;
    SpVectorNP(int n, const allocator_tag& a);  // 0x006a5e10 / 0x0068a460
    ~SpVectorNP();                              // 0x00553b90 / 0x00553e00
    T& operator[](int i) { return mpBegin[i]; }
    T* data() { return mpBegin; }
};
struct Variant_s006a_6340 {
    enum { kFlagCleanup = 4, kFlagArray = 0x80, kSetFlagsCopy = 0x18 };
    char     mValue[0x10];
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    Variant_s006a_6340() { mFlags = 0; mTypeId = 0; }
    ~Variant_s006a_6340() { if (mFlags & kFlagCleanup) Destruct(0); }
    void Destruct(int);                                                          // 0x0093db80
    bool Set(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n);  // 0x0093dd80
    Variant_s006a_6340& operator=(const Variant_s006a_6340& x);                                         // 0x00542b80
    // operator=<bool/int/uint/float/Key/string/string16/Vector*/Color*/Transform/BBox/Flags>
    template <class T> Variant_s006a_6340& operator=(const T& v);
};
namespace EA {
namespace ArgScript {
class cError {
    char mMessage[0x10];  // eastl::string
public:
    cError(const char* fmt, ...);  // 0x0052df30 (vsnprintf into the message)
    cError(const cError&);
    ~cError();
};
}
}
namespace EA {
namespace ArgScript {
class cArguments_s006a_6340 {  // size 0x38
    char mStorage[0x38];
public:
    cArguments_s006a_6340(const char* text);                                // 0x008386d0
    ~cArguments_s006a_6340();                                               // 0x00837fa0
    const char** MainArguments(int* count, int nMin, int nMax);  // 0x00838020
    const char** MainArguments(int count);                       // 0x00838320
};
}
}
namespace EA {
namespace ArgScript {
class cFormatParser {
public:
#define PV(n) virtual void pad##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
#undef PV
    virtual bool         ParseBool(const char* s);       // +0x94
    virtual float        ParseFloat(const char* s);      // +0x98
    virtual int          ParseInt(const char* s);        // +0x9c
    virtual unsigned int ParseUInt(const char* s);       // +0xa0
    virtual Vector2_s006a_6340      ParseVector2(const char* s);    // +0xa4
    virtual Vector3_s006a_6340      ParseVector3(const char* s);    // +0xa8
    virtual Vector4_s006a_6340      ParseVector4(const char* s);    // +0xac
    virtual ColorRGB_s006a_6340     ParseColorRGB(const char* s);   // +0xb0
    virtual ColorRGBA_s006a_6340    ParseColorRGBA(const char* s);  // +0xb4
};
}
}
using EA::ArgScript::cError;
using EA::ArgScript::cArguments_s006a_6340;
using EA::ArgScript::cFormatParser;
void SPKeyFromName(ResourceKey* key, const char* name, uint32_t defType, uint32_t defGroup);  // 0x0068d5a0
namespace SP {
 Matrix3 Matrix3FromEulerXYZ(const Vector3_s006a_6340& euler);   // 0x005f4e80
}
void SetLocalizedString(uint32_t tableID, uint32_t instanceID, const wchar_t* text,
                        LocalizedString_s006a_6340* out);                                              // 0x006b5040
#define CheckArgCount(count, nMin, nMax) \
    if ((count) < (nMin) || (count) > (nMax)) \
        throw cError("wrong number of arguments: %d, expecting [%d, %d]\n", (count), (nMin), (nMax))
template <class Vec>
static __forceinline void SetArray(Variant_s006a_6340* out, uint32_t type, Vec& values, uint32_t elemSize, int count)
{
    Variant_s006a_6340 tmp;
    tmp.Set(type, Variant_s006a_6340::kSetFlagsCopy, values.data(), elemSize, count);
    *out = tmp;
}
// ---- items of slice s006a6340 end

// ---- items of slice s006a8610 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
class string {
 public:
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    char* mpCapacity;   // +8
    const char* mpName; // +c  allocator

    ~string();                                         // 0x00530670
    string& operator=(const string& x);                // 0x00579c60
    string& assign(const char* p);                     // 0x006a4380
    string& append(const char* p);                     // 0x0060c4e0
    string& append(const char* first, const char* last);  // 0x00455d60
    void push_back(char c);                            // 0x005306c0
    string& sprintf(const char* fmt, ...);             // 0x00472fe0
    string& append_sprintf(const char* fmt, ...);      // 0x005f9450

    string& append(const string& x) { return append(x.mpBegin, x.mpEnd); }
    const char* c_str() const { return mpBegin; }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
}
namespace eastl {
extern wchar_t gEmptyString16[1];  // 0x01667bac
}
namespace eastl {
class string16_s006a_8610 {
 public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;

    string16_s006a_8610() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16_s006a_8610() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
}
struct StringImage {
    uint32_t w[4];
};
namespace EA {
eastl::string ConvertToString8(const eastl::string16_s006a_8610& s);  // 0x0093c570
}
namespace EA {
namespace ArgScript {
void SprintfAppend(eastl::string* out, const char* fmt, ...);  // 0x00840c70
}
}
struct Vector3_s006a_8610 { float x, y, z; };
struct BBox { Vector3_s006a_8610 lower, upper; };
struct ResourceKey_s006a_8610 { uint32_t instance, type, group; };
struct LocalizedString_s006a_8610 { uint32_t tableId, instanceId, pad[3]; };  // 0x14 bytes per array item
struct Transform_s006a_8610 {               // 0x38 bytes
    uint16_t mnFlags;            // +0
    uint16_t mnTransformCount;   // +2
    Vector3_s006a_8610 mOffset;             // +4
    float mfScale;               // +10
    Matrix3 mRotation;           // +14
    Transform_s006a_8610(const Transform_s006a_8610& x);  // 0x0040ce80
};
Vector3_s006a_8610 GetEulerAngles(const Matrix3& m);   // 0x006a3920
struct Flags96_s006a_8610 {
    uint32_t mWord[3];
    __forceinline bool test(uint32_t i) const
    {
        if (i < 96)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};
const Vector3_s006a_8610* GetDefaultVector3();   // 0x006bb5e0
class IResourceManager {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e();
    virtual bool GetFileName(const ResourceKey_s006a_8610& key, eastl::string16_s006a_8610* name);  // +0x7c
};
IResourceManager* GetResourceManager();   // 0x0067dcd0
bool GetKeyDisplayName(const ResourceKey_s006a_8610& key, eastl::string16_s006a_8610* name, int flags);  // 0x00b1e4d0
namespace SP {
class cString_s006a_8610 {   // 0x1c bytes
 public:
    uint32_t mData[7];
    cString_s006a_8610();                    // 0x006b5060
    ~cString_s006a_8610();                   // 0x006b5240
    const wchar_t* GetText();     // 0x006b55c0
};
}
namespace SP {
void LoadFromKey(const LocalizedString_s006a_8610* key, cString_s006a_8610* dst);  // 0x006b56d0
}
class Property {
 public:
    void* mpData;          // +0
    uint32_t mUnk4;        // +4
    int mnItemCount;       // +8
    uint32_t mUnkC;        // +c
    uint16_t mnFlags;      // +10
    uint16_t mnType;       // +12

    bool* GetValueBool();                 // 0x004e42a0
    char* GetValueChar();                 // 0x006a36e0
    wchar_t* GetValueWChar();             // 0x006a3710
    int8_t* GetValueInt8();               // 0x006a3740
    uint8_t* GetValueUInt8();             // 0x006a3770
    int16_t* GetValueInt16();             // 0x006a37a0
    uint16_t* GetValueUInt16();           // 0x006a37d0
    int32_t* GetValueInt32();             // 0x0041e990
    uint32_t* GetValueUInt32();           // 0x0041ea00
    int64_t* GetValueInt64();             // 0x006a3800
    uint64_t* GetValueUInt64();           // 0x006a3830
    float* GetValueFloat();               // 0x0041ea70
    double* GetValueDouble();             // 0x006a3860
    eastl::string* GetValueString8();     // 0x0060ebf0
    eastl::string16_s006a_8610* GetValueString16();  // 0x0068a4f0
    ResourceKey_s006a_8610* GetValueKey();           // 0x006a1030
    Flags96_s006a_8610* GetValueFlags();             // 0x006a3890
    LocalizedString_s006a_8610* GetValueText();      // 0x006a1090
    Vector2* GetValueVector2();           // 0x006a0f70
    Vector3_s006a_8610* GetValueColorRGB();          // 0x006a0fd0
    Vector4* GetValueVector4();           // 0x006a0fa0
    Vector4* GetValueColorRGBA();         // 0x006a1000
    Transform_s006a_8610* GetValueTransform();       // 0x006a1060
    BBox* GetValueBBox();                 // 0x005f2320
    int GetItemCount();                   // 0x00571ef0
    void* GetValue();                     // 0x00446ff0

    // inlined copies of the two accessors above
    __forceinline int GetItemCountInl() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    __forceinline void* GetValueInl() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
    __forceinline const Vector3_s006a_8610* GetValueVector3()
    {
        if (mnType == 0x31 || mnType == 0x10)
            return (const Vector3_s006a_8610*)GetValueInl();
        return GetDefaultVector3();
    }
};
// ---- items of slice s006a8610 end

// ---- items of slice s006a9470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyStr[];   // 0x01667bac
extern const char* gCmdName_Property;        // 0x0152ee54
extern const char* gCmdName_PropertyGroup;   // 0x0152ef9c
extern const char* gCmdName_PropertyList;    // 0x0152ef98
extern const char* gCmdName_AppProps;        // 0x0152efa0
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
namespace eastl {
struct string_s006a_9470 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    string_s006a_9470() : mpBegin(gEmptyStr), mpEnd(gEmptyStr), mpCapacity(gEmptyStr + 1) {}
    ~string_s006a_9470()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            delete[] mpBegin;
    }
    const char* c_str() const { return mpBegin; }
    void sprintf(const char* fmt, ...);        // 0x00472fe0
};
}
struct UIntVec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
    UIntVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVec()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            delete[] mpBegin;
    }
};
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRef {
    T* p;
    AutoRef() : p(0) {}
    AutoRef(T* o) : p(o) { if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
    AutoRef& operator=(T* o)
    {
        T* old = p;
        if (o != old) {
            if (o) o->AddRef();
            p = o;
            if (old) old->Release();
        }
        return *this;
    }
};
struct ResourceKey_s006a_9470 { unsigned a, b, c; };
struct Variant_s006a_9470 {                       // EA::Variant (0x14 bytes)
    char data[0x10];
    unsigned short flags;              // |2 = initialised, 0x80 = array, 4 = owns data
    unsigned short type;
    Variant_s006a_9470() : flags(0), type(0) {}
    ~Variant_s006a_9470() { if (flags & 4) Destruct(0); }
    Variant_s006a_9470& operator=(const Variant_s006a_9470& o);        // 0x00542b80
    void Destruct(int);                          // 0x0093db80
};
struct PropObj {                       // property entry (flags at +0x10)
    char pad[0x10];
    unsigned flags;                    // 0x80 = array
};
struct cError_s006a_9470 { eastl::string_s006a_9470 mMessage; cError_s006a_9470(const char* fmt, ...); cError_s006a_9470(const cError_s006a_9470&); };
namespace EA {
namespace ArgScript {
struct cArguments_s006a_9470 {
    const char** MainArguments(int* pCount, int min, int max);   // 0x00838020
    const char** OptionArguments(const char* name, int n);       // 0x00838330
    bool HasFlag(const char* name);                              // 0x008380b0
};
}
}
using EA::ArgScript::cArguments_s006a_9470;
void __cdecl Output(void* out, const char* fmt, ...);                         // 0x00841000
void __cdecl SPKeyFromName(ResourceKey_s006a_9470* out, const char* name, int a, int b); // 0x0068d5a0
bool __cdecl WildcardMatch(const char* str, const char* pattern, int flags);  // 0x0093d5d0
void __cdecl GetVariantTypeDescription(PropObj* p, eastl::string_s006a_9470* out);       // 0x006a5690
void __cdecl GetVariantValueDescription(PropObj* p, eastl::string_s006a_9470* out);      // 0x006a8610
bool __cdecl ParseVariantValue(unsigned type, void* out, int argc, const char** argv, Variant_s006a_9470* v); // 0x006a6340
struct PropList : IRefObj {
    virtual void p2(); virtual void p3(); virtual void p4();
    virtual void SetProperty(unsigned id, const Variant_s006a_9470* v);            // slot 5
    virtual void RemoveProperty(unsigned id);                           // slot 6
    virtual bool HasProperty(unsigned id);                              // slot 7
    virtual void GetVariant(unsigned id, const Variant_s006a_9470** out);          // slot 8
    virtual void p9();
    virtual PropObj* GetProperty(unsigned id);                          // slot 10
    virtual void LoadFrom(void* res);                                   // slot 11
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual bool Write(void* stream);                                   // slot 16
    virtual void GetPropertyIDs(UIntVec* out);                          // slot 17
};
extern PropList* sAppProperties;   // 0x015fd918
struct IdNameNode { unsigned key; char* name; };
struct IdNameIter { IdNameNode* node; IdNameNode** bucket; };
struct IdNameTable {
    int pad0;
    IdNameNode** mpBuckets;            // +4
    unsigned mnBucketCount;            // +8
    IdNameIter find(const unsigned& key);                           // 0x00a3b2c0
    IdNameNode* end() { return mpBuckets[mnBucketCount]; }
};
struct cPropertyManager_s006a_9470;
struct IPropertyManager {                                           // SP::PropertyManager()
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual bool LookupPropertyID(const char* name, unsigned* outId);   // slot 6
    virtual const char* GetPropertyName(unsigned id);                   // slot 7
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(unsigned a, unsigned c, AutoRef<PropList>* out);   // slot 11
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual const Variant_s006a_9470* GetDefaultVariant(unsigned id);              // slot 20
};
IPropertyManager* __cdecl PropertyManager();                        // 0x0067de30
struct MsgData { unsigned v, t; };
struct MsgBase {
    virtual void m0();
    long mRefCount;
    MsgData d[5];
    MsgBase() { _InterlockedExchange(&mRefCount, 0); }
    void Destruct();                                                // 0x00421cf0
};
struct PropMsg : MsgBase {
    virtual void m0();
    ~PropMsg() { Destruct(); }
};
struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(unsigned id, MsgBase* msg, int arg);          // slot 5
    virtual void s6(); virtual void s7();
    virtual void AddHandler(unsigned id, void* handler);            // slot 8
};
IMessageServer* __cdecl MessageServer();                            // 0x0067dcc0
struct ListMgr;
struct cCommandBase {                  // base of ArgScript commands / cheats (ctor at 0x0083c800)
    cCommandBase();                    // 0x0083c800
    virtual void Execute(cArguments_s006a_9470* args);
    void* mOut;                        // +4
    int f8, fc;
};
struct cListPropsCheat : cCommandBase {
    ListMgr* mMgr;                     // +0x10
    virtual void Execute(cArguments_s006a_9470* args);
};
struct ListMgr {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual void m6();
    virtual const char* GetPropertyName(unsigned id);                   // slot 7
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(unsigned a, unsigned c, AutoRef<PropList>* out);   // slot 11
    char pad[0x148 - 4 - 0];           // (vptr + padding)
    IdNameTable mIdToName;             // +0x148
};
struct cPropCheat : cCommandBase {
    ListMgr* mMgr;                     // +0x10
    virtual void Execute(cArguments_s006a_9470* args);
};
struct IResource : IRefObj {
    virtual void p2();
    virtual unsigned GetType();                                    // slot 3
};
struct IParser : IRefObj {
    virtual void p2();                                             // +8
    virtual void p3();
    virtual void SetOwner(void* a);                                // +0x10 (slot 4)
    virtual void RegisterCommand(const char* name, void* cmd);     // +0x14 (slot 5)
    virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10();
    virtual void q11(); virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15();
    virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19(); virtual void q20();
    virtual void q21(); virtual void q22(); virtual void q23(); virtual void q24(); virtual void q25();
    virtual void q26(); virtual void q27(); virtual void q28(); virtual void q29(); virtual void q30();
    virtual void q31(); virtual void q32(); virtual void q33(); virtual void q34(); virtual void q35();
    virtual void q36(); virtual void q37(); virtual void q38(); virtual void q39(); virtual void q40();
    virtual void q41(); virtual void q42(); virtual void q43(); virtual void q44(); virtual void q45();
    virtual struct HashHolder* RegisterHashFunction(const char* name, void* obj);   // +0xb8 (slot 46)
};
struct IFileParser : IRefObj {
    virtual void f2();                                             // +8
    virtual void f3();
    virtual void SetParser(IParser* p);                            // +0x10 (slot 4)
    virtual void f5(); virtual void f6();
    virtual void ParseFile(const char* path, int flags);           // +0x1c (slot 7)
    virtual void f8();                                             // +0x20
    virtual void f9(); virtual void f10();
    virtual void f11(int a);                                       // +0x2c
};
struct IResMgr {
    virtual void r0(); virtual void r1(); virtual void r2();
    virtual bool GetResource(ResourceKey_s006a_9470* key, AutoRef<IResource>* out, int a, int b, int c, int d);   // +0xc
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8();
    virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13();
    virtual void r14(); virtual void r15(); virtual void r16();
    virtual void RegisterFactory(int a, void* factory, int b);     // +0x44
    virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
    virtual IResource* FindResource(ResourceKey_s006a_9470* key);             // +0x58
};
struct ICheatMgr {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5();
    virtual void AddCheat(const char* name, void* cheat, int a);   // +0x18
};
IResMgr* __cdecl GetResourceManager_s006a_9470();                   // 0x0067dcd0
ICheatMgr* __cdecl CheatManager();                       // 0x0067de20
IParser* __cdecl CreateParser();                         // 0x008408d0
IFileParser* __cdecl CreateFileParser();                 // 0x00840940
const wchar_t* __cdecl GetDirFromID(unsigned id);        // 0x006886b0
void __cdecl ParseHashDefault(IParser* parser, ResourceKey_s006a_9470* key);   // 0x008476b0
unsigned* __cdecl RBTreeIncrement(void* node);           // 0x00921580
namespace eastl {
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    wstring(const wchar_t* pBegin);                                // RangeInitialize, 0x00579a90
    ~wstring()
    {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            delete[] mpBegin;
    }
    void append(const wchar_t* pBegin, const wchar_t* pEnd);      // 0x00429580
};
}
eastl::string_s006a_9470* __cdecl ConvertToString8(eastl::string_s006a_9470* out, const eastl::wstring* in);   // 0x0093c570
struct HashHolder {
    void Finish();                                       // 0x0083df90
};
struct cCommandBase2 {                                   // ctor at 0x0083c840
    cCommandBase2();                                     // 0x0083c840
    virtual void Execute(cArguments_s006a_9470* args);
    void* mOut; int f8, fc;
};
struct cPropertyDefCmd : cCommandBase { virtual void Execute(cArguments_s006a_9470* args); };          // size 0x10
struct cPropertyGroupDefCmd : cCommandBase { virtual void Execute(cArguments_s006a_9470* args); };     // size 0x10
struct cPropertyListDefCmd : cCommandBase2 {                                                 // size 0x14
    int mField10;
    cPropertyListDefCmd() : mField10(0) {}
    virtual void Execute(cArguments_s006a_9470* args);
};
struct cAppPropsCmd {                                                                        // size 0x34
    cAppPropsCmd();                                                                          // 0x0083cdd0
    virtual void Execute(cArguments_s006a_9470* args);
    char pad[0x30];
};
struct cHashFunction { virtual void Eval(); int f4; cHashFunction() : f4(0) {} };            // size 8
void* operator new(size_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct cPropertyManager_s006a_9470 {
    void* vtbl;                    // +0
    void* factoryVtbl;             // +4  (Factory subobject)
    int f8;
    char mHandler[4];              // +0xc (IHandlerRC subobject)
    char mBlock10[4];              // +0x10 (ArgScript state)
    bool mInitialized;             // +0x14
    bool mUseFileParser;           // +0x15
    char pad16[2];
    IResMgr* mResMgr;              // +0x18
    bool mParsing;                 // +0x1c
    char pad1d[3];
    int mTreeAlloc;                // +0x20
    char* mTreeEndNode() { return (char*)this + 0x24; }
    void* mTreeRight;              // +0x24
    void* mTreeLeft;               // +0x28
    void* mTreeRoot;               // +0x2c
    char mTreeColor;               // +0x30
    char pad31[3];
    unsigned mTreeSize;            // +0x34
    char pad38[4];
    PropList* BaseList() { return (PropList*)((char*)this + 0x3c); }   // embedded list
    char pad3c[0x178 - 0x3c];
    AutoRef<IFileParser> mFileParser;   // +0x178
    AutoRef<IParser> mParser;           // +0x17c

    bool Init();                                       // 0x006a9b60
    void DoNuke(void* root);                           // 0x0068a0f0 (rbtree)
};
struct PropVec { void reserve(unsigned n); };          // 0x006a84f0, at list+0x18
struct RBIter { void* node; };
struct PropTree { RBIter find(const unsigned& key); }; // 0x00e5c780          // 0x006a84f0, at list+0x18
struct IStream32 {
    virtual void s0();
    virtual int AddRef();
    virtual int Release();
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13();
    virtual void Write(const void* data, int len);                  // slot 14 (+0x38)
};
struct StreamRef {
    IStream32* p;
    StreamRef(IStream32* s) : p(s) { if (p) p->AddRef(); }
    ~StreamRef() { if (p) p->Release(); }
};
struct IQueryable {
    virtual void a(); virtual void b(); virtual void c();
    virtual void* Query(unsigned id);                               // slot 3 (+0xc)
};
struct IResEntry {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5();
    virtual IStream32* GetStream();                                  // slot 6 (+0x18)
    virtual char* GetOwner();                                        // slot 7 (+0x1c)
};
struct cPropertyFactory {                                             // the Factory subobject (this = manager + 4)
    bool WriteResource(PropList* list, IResEntry* entry, int a3, int a4);   // @ 0x006aa130
};
struct BoolVec {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
};
struct BoolVecOwner {
    void* vtbl;      // +0

    bool Append(int arg1, BoolVec* v);
};
void FUN_0050f0d0(void*, void*);
void* FUN_0050e4b0(void*, void*);
void BoolVec_DoInsertValue(void* dst, void* src, int count);
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s006a9470 end

// ---- items of slice s006aa3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct StrKey {
    void* mpBegin;      // +0
    void* mpEnd;        // +4
    void* mpCapacity;   // +8
    void* mAllocator;   // +0xc

    void assign(const char* first, const char* last);                 // 0x00454cb0
    void assign(const char* s) { assign(s, s + strlen(s)); }
};
struct MapNameToID {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    int& operator[](const StrKey& key);       // 0x006a8340
};
struct MapIDToName {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    StrKey* operator[](const uint32_t& key);  // 0x006a8410
};
struct Vec32 {
    uint32_t* mpBegin;     // +0
    uint32_t* mpEnd;       // +4
    uint32_t* mpCapacity;  // +8

    void DoInsertValue(uint32_t* pos, const uint32_t* value);  // 0x004558a0
};
void EA_MakeCaseInsensitive(const char* src, StrKey* dst);   // 0x00840cc0
struct cPropertyManager_s006a_a3f0 {
    char pad00[0x94];
    MapNameToID mPropertyNameToIDMap;      // +0x94
    char pad01[0x14];
    MapIDToName mPropertyIDToNameMap;      // +0xb4
    char pad02[0x14];
    MapNameToID mGroupNameToIDMap;         // +0xd4
    char pad03[0x14];
    MapIDToName mGroupIDToNameMap;         // +0xf4
    char pad04[0x14];
    Vec32 mGroupIDs;                       // +0x114
    char pad05[8];
    MapNameToID mLocalPropertyNameToIDMap; // +0x128
    char pad06[0x14];
    MapIDToName mLocalPropertyIDToNameMap; // +0x148
    char pad07[0x14];
    StrKey mLCName;                        // +0x168

    void RegisterPropertyName(const char* name, uint32_t id);
    void RegisterPropertyNameLocal(const char* name, uint32_t id);
    void Fun_006aa450(const char* name, uint32_t id);
    uint32_t Shutdown();
    void ParseAndAddProperty(uint32_t id, uint32_t arg2, uint32_t arg3);
};
struct cPropertyCommand {
    char pad0[4];
    uint32_t mArg3;                 // +4
    char pad8[4];
    cPropertyManager_s006a_a3f0* mManager;     // +0xc
    uint32_t mArg4;                 // +0x10

    bool Parse(void** param_2);
};
struct cPropertyCommandExec {
    void Execute(void* args);
};
// ---- items of slice s006aa3f0 end

// @ 0x006a3310
void cCommandStub::Forward(int a, int b)
{
    ((void (__thiscall*)(cCommandStub*, int, int, int))(*(void***)this)[0xb])(this, a, 0, b);
}









// @ 0x006a3330
bool cPropertyManager2::CreateResource(int* info, int a, int b, int* out)
{
    cPropertyList* pl = (cPropertyList*)EA_Alloc(0x38, "App/PropertyList/Create", 0, 0, 0, 0);
    if (pl)
        pl = pl->Ctor("CreateResource");

    uint32_t* k = (uint32_t*)((int* (*)(int*))((void**)info)[0x10 / 4])(info);
    pl->mKey0 = k[0];
    pl->mKey1 = k[1];
    pl->mKey2 = k[2];

    bool ok = ((bool (__thiscall*)(void*, int*, void*, int, int))(((void**)this)[0x24 / 4]))(this, info, pl, a, b);
    if (ok) {
        *out = (int)pl;
        pl->AddRef();
        return true;
    }
    pl->Release(1);
    return false;
}









// @ 0x006a3400
unsigned int SP::cPropertyManager::GetSupportedTypes(unsigned int * p, unsigned int n)
{
    if (p) {
        if (n < 1)
            return 0;
        *p = 0xb1b104;
    }
    return 1;
}









// @ 0x006a3430
float* EulerFromMatrix(float* out, const float* m)
{
    float len = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (len > 0.001f) {
        out[0] = atan2f_(m[5], m[8]);
        out[1] = atan2f_(-m[2], len);
        out[2] = atan2f_(m[1], m[0]);
        return out;
    }
    out[2] = 0.0f;
    out[0] = atan2f_(-m[7], m[4]);
    out[1] = atan2f_(-m[2], len);
    return out;
}









// @ 0x006a34a0
Variant& Variant::SetVec21(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x21) {
        SetType(0x21, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x21;
    mFlags = mFlags & 2;
    return *this;
}









// @ 0x006a3510
Variant& Variant::SetVec30(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x30) {
        SetType(0x30, 0, p, 8, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    mTypeId = 0x30;
    mFlags = mFlags & 2;
    return *this;
}









// @ 0x006a3570
Variant& Variant::SetVec31(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x31) {
        SetType(0x31, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x31;
    mFlags = mFlags & 2;
    return *this;
}









// @ 0x006a3610
Variant& Variant::SetVec32(const void* p)
{
    if (mFlags & 4) Destruct(1);
    if ((mFlags & 2) != 0 && mTypeId != 0x32) {
        SetType(0x32, 0, p, 0xc, 1);
        return *this;
    }
    d0 = ((const uint32_t*)p)[0];
    d1 = ((const uint32_t*)p)[1];
    d2 = ((const uint32_t*)p)[2];
    mTypeId = 0x32;
    mFlags = mFlags & 2;
    return *this;
}









// @ 0x006a38c0
void cCommandStateA::OnRegister(void* parser, int b)
{
    if (b) {
        mCmd = b - 0x10;
        ((EA::ArgScript::cIMetaCommand*)this)->OnRegister(parser, b);
    } else {
        mCmd = 0;
        ((EA::ArgScript::cIMetaCommand*)this)->OnRegister(parser, b);
    }
}









// @ 0x006a38f0
void cCommandStateB::OnRegister(void* parser, int b)
{
    if (b) {
        mCmd = (void*)(b - 0x10);
        OnRegister2(parser, b);
    } else {
        mCmd = 0;
        OnRegister2(parser, b);
    }
}









// @ 0x006a3920
Float3* FUN_006a3920(Float3* out, const float* m)
{
    Float3 tmp;
    Float3* p = (Float3*)EulerFromMatrix((float*)&tmp, m);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}









// @ 0x006a3980
const char* __stdcall FUN_006a3980(int index)
{
    if (index == 0)
        return "Displays or modifies properties";
    return index == 1 ? "[<propName:string>]                Displays value of given app property" : 0;
}









// @ 0x006a39a0
int SP::cPropertyManager::GetPropertyGroupCount()
{
    // The retail code reloads mpEnd for the subtraction (it is not kept in a
    // register across the branch), so the end pointer is read through a
    // volatile-qualified lvalue to reproduce that load.
    if (((char *)mPropertyGroupIDs.mpBegin) != ((char *)mPropertyGroupIDs.mpEnd))
        return (int)((*(char *volatile *)&mPropertyGroupIDs.mpEnd - (char *)mPropertyGroupIDs.mpBegin) >> 2);
    return 0;
}









// @ 0x006a39d0
bool SP::cPropertyManager::GetPropertyGroupID(int idx, unsigned int * out)
{
    if (((char *)mPropertyGroupIDs.mpBegin) != ((char *)mPropertyGroupIDs.mpEnd) && idx < (int)((((char *)mPropertyGroupIDs.mpEnd) - ((char *)mPropertyGroupIDs.mpBegin)) >> 2)) {
        *out = ((uint32_t*)((char *)mPropertyGroupIDs.mpBegin))[idx];
        return true;
    }
    return false;
}









// @ 0x006a3ac0
void FUN_006a3ac0(void* args)
{
    (void)args;
}









// @ 0x006a3c30
void FUN_006a3c30(int b)
{
    (void)b;
}









// @ 0x006a3ce0
void cAppPropsCommand::Execute(void* args)
{
    ((EA::ArgScript::cArguments_s006a_32a0*)args)->MainArguments(0);
    *(uint8_t*)(*(int*)((char*)this + 0x30) + 0x1e8) = 1;
    ((void (__thiscall*)(void*, void*))(*(void***)mOwner)[0x8c / 4])(mOwner, this);
}









// @ 0x006a3d10
void cAppPropsCommand::OnEndParse(int b)
{
    (void)b;
    *(uint8_t*)(*(int*)((char*)this + 0x30) + 0x1e8) = 0;
    ++*(uint32_t*)((char*)g_sAppProperties + 0x34);
}









// @ 0x006a3d50
void* FUN_006a3d50(FeedbackCmd* self)
{
    if (!self->mActive)
        return ((void* (__thiscall*)(void*))((void**)*(void**)((char*)self + 0x3c))[0x28 / 4])((char*)self + 0x3c);
    // rbtree find + atexit fallback
    extern void* g_feedbackFallback;
    return g_feedbackFallback;
}









// @ 0x006a3dd0
void FUN_006a3dd0(int* p)
{
    (void)p;
}









// @ 0x006a3f00
bool FUN_006a3f00(FeedbackCmd* self)
{
    if (self->mActive)
        return true;    // replaced by real rbtree test in matching version
    return ((bool (__thiscall*)(void*))((void**)*(void**)((char*)self + 0x3c))[0x1c / 4])((char*)self + 0x3c);
}









// @ 0x006a3f40
void FUN_006a3f40(String* self, const char** range, const void* tag)
{
    self->mpBegin = 0;
    self->mpEnd = 0;
    self->mpCapacity = 0;
    const char* b = range[0];
    const char* e = range[1];
    unsigned n = (unsigned)(e - b);
    ((void (__thiscall*)(String*, unsigned))0x00475ab0)(self, n + 1);  // RangeInitialize
    char* dst = (char*)self->mpBegin;
    memcpy(dst, b, n);
    self->mpEnd = dst + n;
    dst[n] = 0;
    *(const void**)((char*)self + 0x10) = tag;
}









// @ 0x006a4100
void* CopyVec12(void* dst, unsigned n, const void* src)
{
    if (n > 0) {
        do {
            if (dst) {
                *(float*)dst = *(const float*)src;
                *((float*)dst + 1) = *((const float*)src + 1);
                *((float*)dst + 2) = *((const float*)src + 2);
            }
            --n;
            dst = (char*)dst + 0xc;
        } while (n > 0);
    }
    return dst;
}









// @ 0x006a4130
Vec38* Vec38::Init(int n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x38, "App", 0, 0, kAllocPath, 0xd1) : 0;
    begin = p;
    end = p;
    cap = p + n * 0x38;
    return this;
}









// @ 0x006a4190
uint32_t FUN_006a4190(void* parser)
{
    static char buf[0x10];
    char* s = buf;
    // EvalString(parser, string) then hash
    StringEvalString(parser, s);
    return FNVHash(s, 0x811c9dc5u, 1);
}









// @ 0x006a4240
bool FUN_006a4240(cPropertyManager* self, int a, int b)
{
    (void)self; (void)a; (void)b;
    return false;
}









// @ 0x006a42d0
bool FUN_006a42d0(cPropertyManager* self, int n, const void* values)
{
    (void)self; (void)n; (void)values;
    return false;
}









// @ 0x006a4360
void cDealloc::Release()
{
    char* b = *(char**)((char*)this + 4);
    if (1 < (*(char**)((char*)this + 0xc) - b) && b != 0) {
        EA_Dealloc(b);
    }
}









// @ 0x006a4380
String& String::assign(const char* p)
{
    return assign(p, p + strlen(p));
}









// @ 0x006a43b0
int FUN_006a43b0(char* self, const uint32_t* key)
{
    uint32_t before = *(uint32_t*)(self + 0xc);
    uint32_t b = key[0] % *(uint32_t*)(self + 8);
    uint32_t** slot = (uint32_t**)(*(int*)(self + 4) + b * 4);
    if (*slot) {
        // find node then unlink
        while (*slot) {
            uint32_t* node = *slot;
            if (node[0] == key[0] && node[1] == key[1]) {
                *slot = *(uint32_t**)((char*)node + 0x10);
                if (*(int*)((char*)node + 8))
                    (**(void (__thiscall***)(void*))(*(int*)((char*)node + 8)))((void*)(*(int*)((char*)node + 8)));
                EA_Dealloc(node);
                --*(uint32_t*)(self + 0xc);
                break;
            }
            slot = (uint32_t**)((char*)node + 0x10);
        }
    }
    return (int)(before - *(uint32_t*)(self + 0xc));
}









// @ 0x006a4450
void* FUN_006a4450(char* tree, void** it, int node, void** root)
{
    (void)tree; (void)it; (void)node; (void)root;
    return it;
}









// @ 0x006a44d0
Vec208* Vec208::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x208, "App", 0, 0, kAllocPath, 0xd1) : 0;
    unsigned cnt = n;
    cap = p + n * 0x208;
    E208 v;
    v.a = -1;
    v.b = -1;
    begin = p;
    end = p;
    v.c = 0;
    if (cnt > 0) {
        do {
            if (p)
                *(E208*)p = v;
            --cnt;
            p += 0x208;
        } while (cnt > 0);
    }
    end = (char*)begin + n * 0x208;
    return this;
}









// @ 0x006a4580
VecC* VecC::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0xc, "App", 0, 0, kAllocPath, 0xd1) : 0;
    unsigned bytes = n * 0xc;
    E12 zero;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    begin = p;
    end = p;
    cap = p + bytes;
    unsigned cnt = n;
    for (; cnt; --cnt) {
        if (p)
            *(E12*)p = zero;
        p = (char*)p + 0xc;
    }
    end = (char*)begin + bytes;
    return this;
}









// @ 0x006a4600
Vec8* Vec8::Init(unsigned n, const float* value)
{
    Alloc(n, value);
    char* p = (char*)begin;
    float a = value[0];
    float b = value[1];
    unsigned cnt = n;
    while (cnt--) {
        if (p) {
            *(float*)p = a;
            *(float*)(p + 4) = b;
        }
        p = (char*)p + 8;
    }
    end = p;
    return this;
}









// @ 0x006a4660
Vec10* Vec10::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16a(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}









// @ 0x006a46a0
VecC* VecC::InitValue(unsigned n, const float* value)
{
    char* p = n ? (char*)EA_Alloc(n * 0xc, "App", 0, 0, kAllocPath, 0xd1) : 0;
    begin = p;
    end = p;
    cap = p + n * 0xc;
    float v0 = value[0];
    float v1 = value[1];
    float v2 = value[2];
    unsigned cnt = n;
    while (cnt--) {
        if (p) {
            *(float*)(p + 0) = v0;
            *(float*)(p + 4) = v1;
            *(float*)(p + 8) = v2;
        }
        p += 0xc;
    }
    end = p;
    return this;
}









// @ 0x006a4730
Vec10b* Vec10b::Init(int n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    Fill16b(begin, n, tmp, value);
    end = (char*)begin + n * 0x10;
    return this;
}









// @ 0x006a4770
Vec18* Vec18::Init(unsigned n, const void* alloc)
{
    (void)alloc;
    char* p = n ? (char*)EA_Alloc(n * 0x18, "App", 0, 0, kAllocPath, 0xd1) : 0;
    cap = p + n * 0x18;
    Box18 v;
    v.x = FLT_MAX;
    v.y = FLT_MAX;
    v.z = FLT_MAX;
    v.nx = -FLT_MAX;
    v.ny = -FLT_MAX;
    v.nz = -FLT_MAX;
    begin = p;
    end = p;
    Fill18(p, n, &v, n);
    end = (char*)begin + n * 0x18;
    return this;
}








// @ 0x006a4990
bool SetDefaultVariantValue(uint32_t type, Variant_s006a_4990* out)
{
    switch (type) {
    // ----------------------------------------------------------------- scalar values
    case 0x01:
        *out = false;
        return true;
    case 0x09:
        *out = 0;
        return true;
    case 0x0a:
        *out = 0u;
        return true;
    case 0x0d:
        *out = 0.0f;
        return true;
    case 0x12:
        *out = eastl::string8_s006a_4990();
        return true;
    case 0x13:
        *out = eastl::string16_s006a_4990();
        return true;
    case 0x20:
        *out = ResourceKey(0xffffffff, 0xffffffff, 0xffffffff);
        return true;
    case 0x21:
        *out = Flags96();
        return true;
    case 0x22: {
        *out = LocalizedString();
        out->mTypeId = 0x22;
        return true;
    }
    case 0x30:
        *out = kDefaultVector2;
        return true;
    case 0x31:
        *out = kDefaultVector3;
        return true;
    case 0x33:
        *out = kDefaultVector4;
        return true;
    case 0x32:
        *out = kDefaultColorRGB;
        return true;
    case 0x34:
        *out = kDefaultColorRGBA;
        return true;
    case 0x38:
        *out = Transform();
        return true;
    case 0x39:
        *out = BoundingBox();
        return true;

    // ------------------------------------------------------------------ empty arrays
    case kArray | 0x01: SET_EMPTY_ARRAY(out, 0x01, 1);
    case kArray | 0x09: SET_EMPTY_ARRAY(out, 0x09, 4);
    case kArray | 0x0a: SET_EMPTY_ARRAY(out, 0x0a, 4);
    case kArray | 0x0d: SET_EMPTY_ARRAY(out, 0x0d, 4);
    case kArray | 0x12: SET_EMPTY_ARRAY(out, 0x12, sizeof(eastl::string8_s006a_4990));
    case kArray | 0x13: SET_EMPTY_ARRAY(out, 0x13, sizeof(eastl::string16_s006a_4990));
    case kArray | 0x22: SET_EMPTY_ARRAY(out, 0x22, sizeof(LocalizedString));
    case kArray | 0x20: SET_EMPTY_ARRAY(out, 0x20, sizeof(ResourceKey));
    case kArray | 0x30: SET_EMPTY_ARRAY(out, 0x30, sizeof(Vector2));
    case kArray | 0x31: SET_EMPTY_ARRAY(out, 0x31, sizeof(Vector3));
    case kArray | 0x33: SET_EMPTY_ARRAY(out, 0x33, sizeof(Vector4));
    case kArray | 0x32: SET_EMPTY_ARRAY(out, 0x32, sizeof(ColorRGB));
    case kArray | 0x34: SET_EMPTY_ARRAY(out, 0x34, sizeof(ColorRGBA));
    case kArray | 0x39: SET_EMPTY_ARRAY(out, 0x39, sizeof(BoundingBox));
    case kArray | 0x38: SET_EMPTY_ARRAY(out, 0x38, sizeof(Transform));
    default:
        return false;
    }
}







// @ 0x006a5690
void GetVariantTypeDescription(const Variant_s006a_5690& v, String_s006a_5690& out)
{
    switch (v.mTypeId) {
    case 0x00: out.assign("unknown"); break;
    case 0x01: out.assign("bool"); break;
    case 0x02: out.assign("char8"); break;
    case 0x03: out.assign("char16"); break;
    case 0x05: out.assign("int8"); break;
    case 0x06: out.assign("uint8"); break;
    case 0x07: out.assign("int16"); break;
    case 0x08: out.assign("uint16"); break;
    case 0x09: out.assign("int32"); break;
    case 0x0a: out.assign("uint32"); break;
    case 0x0b: out.assign("int64"); break;
    case 0x0c: out.assign("uint64"); break;
    case 0x0d: out.assign("float"); break;
    case 0x0e: out.assign("double"); break;
    case 0x0f: out.assign("void*"); break;
    case 0x10: out.assign("void"); break;
    case 0x11: out.assign("IUnknownRC"); break;
    case 0x12: out.assign("string8"); break;
    case 0x13: out.assign("string16"); break;
    case 0x20: out.assign("key"); break;
    case 0x21: out.assign("flags"); break;
    case 0x22: out.assign("text"); break;
    case 0x30: out.assign("vector2"); break;
    case 0x31: out.assign("vector3"); break;
    case 0x32: out.assign("colorRGB"); break;
    case 0x33: out.assign("vector4"); break;
    case 0x34: out.assign("colorRGBA"); break;
    case 0x35: out.assign("matrix2"); break;
    case 0x36: out.assign("matrix3"); break;
    case 0x37: out.assign("matrix4"); break;
    case 0x38: out.assign("transform"); break;
    case 0x39: out.assign("bbox"); break;
    default: goto append_array;
    }
append_array:
    if (v.mFlags & 0x80)
        out.append(" array", "");
}






// @ 0x006a58a0
bool ArgMgr::FUN_006a58a0(int msg, int* v)
{
    void* server = (void*)0;    // SP::MessageServer(); (masked call)
    if (msg != 0xf62ade)
        return false;
    if (v[2] == 0xb1b104) {
        char key[0x10];
        *(uint32_t*)key = v[6];
        *(uint32_t*)(key + 4) = v[4];
        void* iter = 0;
        ((HashTable*)((char*)this + 0x74))->Find2(&iter, key);
        if (*(void**)&iter != *(void**)(*(int*)((char*)this + 0x78) + *(int*)((char*)this + 0x7c) * 4)) {
            if (*(int*)(*(int*)&iter + 8))
                FUN_006a60b0(0, 0, 0);
        }
        (*(void (__thiscall**)(void*, int, int*, int))(*(int*)server + 0x14))(server, 0xf62def, v, 0);
        (*(void (__thiscall**)(void*, void*, int*, int, int))(*(int*)server + 0x18))(server, server, v, 0, 0);
    }
    return true;
}






// @ 0x006a59f0
void ArgMgr::FUN_006a59f0(int* v)
{
    int tmp = 0;
    char ok = (*(char (__thiscall**)(void*, int, int*))(**(int**)((char*)this + 0x18) + 0x14))(
        *(void**)((char*)this + 0x18), (int)v + 8, &tmp);
    if (ok)
        VariantRelease(&tmp);
    char key[0x10];
    *(uint32_t*)key = *(uint32_t*)((char*)v + 0x10);
    *(uint32_t*)(key + 4) = *(uint32_t*)((char*)v + 0x18);
    ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
    VariantRelease(&tmp);
}






// @ 0x006a5a90
void ArgMgr::FUN_006a5a90(int a, int count, int* p)
{
    (void)a;
    int* held = 0;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            int val = p[i];
            if (held) {
                int* h = held;
                held = 0;
                (*(void (__thiscall**)(int*))(*h + 4))(h);
            }
            char ok = (*(char (__thiscall**)(void*, int*, int**))(**(int**)((char*)this + 0x18) + 0x14))(
                *(void**)((char*)this + 0x18), &val, &held);
            if (ok)
                VariantRelease(held);
            char key[0x10];
            *(uint32_t*)key = val;
            *(uint32_t*)(key + 4) = 0xb1b104;
            ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
        }
    }
    if (held) {
        int* h = held;
        (*(void (__thiscall**)(int*))(*h + 4))(h);
    }
}






// @ 0x006a5b80
void ArgMgr::FUN_006a5b80(int count, int* p)
{
    int* held = 0;
    if (count > 0) {
        do {
            if (held) {
                int* h = held;
                held = 0;
                (*(void (__thiscall**)(int*))(*h + 4))(h);
            }
            char ok = (*(char (__thiscall**)(void*, int*, int**))(**(int**)((char*)this + 0x18) + 0x14))(
                *(void**)((char*)this + 0x18), p, &held);
            if (ok)
                VariantRelease(held);
            char key[0x10];
            *(uint32_t*)key = p[0];
            *(uint32_t*)(key + 4) = p[2];
            ((HashTable*)((char*)this + 0x74))->Find2(&key[0], key);
            p += 3;
        } while (--count);
    }
    if (held) {
        int* h = held;
        (*(void (__thiscall**)(int*))(*h + 4))(h);
    }
}






// @ 0x006a5c50
void ArgMgr::FUN_006a5c50(int* out, void* key)
{
    (void)key;
    out[0] = 0;
    out[1] = 0;
    *((uint8_t*)(out + 2)) = 0;
}






// @ 0x006a5e10
Vec10s* Vec10s::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    uint32_t tmp[4];
    tmp[0] = 0x01667bac;
    tmp[1] = 0x01667bac;
    tmp[2] = 0x01667bad;
    tmp[3] = 0;
    UninitFillN16(begin, n, tmp, value);
    *(void**)((char*)this + 4) = (char*)begin + n * 0x10;
    return this;
}






// @ 0x006a5ea0
Vec38b* Vec38b::Init(unsigned n, const void* value)
{
    Alloc(n, value);
    uint8_t tmp[0x38];
    uint32_t m[4];
    Matrix3Assign(m, 0);
    UninitFillN56(begin, n, tmp, value);
    *(void**)((char*)this + 4) = (char*)begin + n * 0x38;
    return this;
}






// @ 0x006a5f70
bool ArgMgr::FUN_006a5f70(const char* name, uint32_t* out)
{
    char buf[0x10];
    EA::ArgScript::MakeCaseInsensitive(name, (char*)this + 0x168);
    ((HashTable*)((char*)this + 0x94))->Find(buf, (char*)this + 0x168);
    if (*(void**)buf != *(void**)(*(int*)((char*)this + 0x98) + *(int*)((char*)this + 0x9c) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}






// @ 0x006a5fd0
bool ArgMgr::FUN_006a5fd0(const char* name, uint32_t* out)
{
    unsigned n = (unsigned)(strlen(name) + 1);
    char* p;
    unsigned cap;
    if (n < 2) {
        p = (char*)0x01667bac;
        cap = 0x01667bad;
    } else {
        p = (char*)EA_Alloc(n, "App", 0, 0, kAllocPath, 0xd1);
        cap = (unsigned)(p + n);
    }
    char* first = p;
    DoInsertValue(p, name, (int)strlen(name));
    p[strlen(name)] = 0;
    char buf[0x10];
    buf[0] = 0;
    ((HashTable*)((char*)this + 0xd4))->Find(buf, p);
    if (1 < (int)(cap - (unsigned)first) && first)
        EA_Dealloc(first);
    if (*(void**)buf != *(void**)(*(int*)((char*)this + 0xd8) + *(int*)((char*)this + 0xdc) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}






// @ 0x006a60b0
bool ArgMgr::FUN_006a60b0(int a, int b, int* out)
{
    char key[0x10];
    *(uint32_t*)key = a;
    *(uint32_t*)(key + 4) = b;
    *(uint32_t*)(key + 8) = 0xb1b104;
    void* iter = 0;
    ((HashTable*)((char*)this + 0x74))->Find2(&iter, key);
    if (*(void**)&iter == *(void**)(*(int*)((char*)this + 0x78) + *(int*)((char*)this + 0x7c) * 4)) {
        char ok = (*(char (__thiscall**)(void*, void*, int*, int, int))(**(int**)((char*)this + 0x18) + 0xc))(
            *(void**)((char*)this + 0x18), key, out, 0, 0);
        return ok != 0;
    }
    *out = *(int*)(*(int*)&iter + 8);
    return true;
}






// @ 0x006a61c0
void ArgMgr::FUN_006a61c0(int a, int b)
{
    char* self = (char*)this;
    *(uint32_t*)(self + 8) = a;
    *(uint32_t*)(self + 0xc) = 0xb1b104;
    *(uint32_t*)(self + 0x10) = b;
    VariantHold((int*)self);
    char key[0x10];
    *(uint32_t*)key = a;
    *(uint32_t*)(key + 4) = b;
    void** slot = (void**)((HashMapKey8*)(self + 0x74))->operator[](key);
    void* old = *slot;
    if (self != old) {
        (*(void (__thiscall**)(char*))(*(int*)self))(self);
        *slot = self;
        if (old)
            (*(void (__thiscall**)(void*))(*(int*)old + 4))(old);
    }
}






// @ 0x006a6240
bool ArgMgr::FUN_006a6240(const char* name, uint32_t* out)
{
    char* self = (char*)this;
    EA::ArgScript::MakeCaseInsensitive(name, self + 0x168);
    if (isdigit((unsigned char)*name)) {
        *out = (uint32_t)strtoul(name, 0, 0);
        return true;
    }
    char buf[0x10];
    ((HashTable*)(self + 0x128))->Find(buf, self + 0x168);
    if (*(void**)buf != *(void**)(*(int*)(self + 0x12c) + *(int*)(self + 0x130) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    ((HashTable*)(self + 0x94))->Find(buf, self + 0x168);
    if (*(void**)buf != *(void**)(*(int*)(self + 0x98) + *(int*)(self + 0x9c) * 4)) {
        *out = *(uint32_t*)(*(int*)buf + 0x10);
        return true;
    }
    return false;
}






// @ 0x006a6310
VecU32* VecU32::Init(unsigned n, const void* alloc)
{
    Alloc(n, alloc);
    uint32_t* p = (uint32_t*)begin;
    for (unsigned i = 0; i < n; i++)
        p[i] = 0;
    *(uint32_t*)((char*)this + 4) = (uint32_t)begin + n * 4;
    return this;
}






// @ 0x006a6340
bool ParseVariantValue(uint32_t type, cFormatParser* parser, int count, const char** args, Variant_s006a_6340* out)
{
    switch (type) {
    // ----------------------------------------------------------------- scalar values
    case 0x01: {  // Bool
        CheckArgCount(count, 1, 1);
        bool v = parser->ParseBool(args[0]);
        *out = v;
        return true;
    }
    case 0x09: {  // Int32
        CheckArgCount(count, 1, 1);
        int v = parser->ParseInt(args[0]);
        *out = v;
        return true;
    }
    case 0x0a: {  // UInt32
        CheckArgCount(count, 1, 1);
        unsigned int v = parser->ParseUInt(args[0]);
        *out = v;
        return true;
    }
    case 0x0d: {  // Float
        CheckArgCount(count, 1, 1);
        float v = parser->ParseFloat(args[0]);
        *out = v;
        return true;
    }
    case 0x12:  // String8
        CheckArgCount(count, 1, 1);
        *out = string8(args[0]);
        return true;
    case 0x13:  // String16
        CheckArgCount(count, 1, 1);
        *out = EA::ConvertToString16(args[0]);
        return true;
    case 0x20: {  // Key
        CheckArgCount(count, 1, 1);
        ResourceKey key(0, 0, 0);
        SPKeyFromName(&key, args[0], 0, 0);
        *out = key;
        return true;
    }
    case 0x21: {  // Flags: every argument is a bit index (< 96)
        Flags96_s006a_6340 flags;
        for (int i = 0; i < count; i++) {
            unsigned int bit = parser->ParseInt(args[i]);
            if (bit < 96)
                flags.set(bit);
        }
        *out = flags;
        return true;
    }
    case 0x22: {  // Text: "placeholder" [table!instance]
        CheckArgCount(count, 1, 2);
        ResourceKey key(0xffffffff, 0xffffffff, 0xffffffff);
        if (count > 1)
            SPKeyFromName(&key, args[1], 0, 0);
        LocalizedString_s006a_6340 text;
        SetLocalizedString(key.groupID, key.instanceID, EA::ConvertToString16(args[0]).c_str(), &text);
        Variant_s006a_6340 tmp;
        tmp.Set(0x22, Variant_s006a_6340::kSetFlagsCopy, &text, sizeof(LocalizedString_s006a_6340), 1);
        *out = tmp;
        return true;
    }
    case 0x30:  // Vector2
        CheckArgCount(count, 1, 1);
        *out = parser->ParseVector2(args[0]);
        return true;
    case 0x31:  // Vector3
        CheckArgCount(count, 1, 1);
        *out = parser->ParseVector3(args[0]);
        return true;
    case 0x33:  // Vector4
        CheckArgCount(count, 1, 1);
        *out = parser->ParseVector4(args[0]);
        return true;
    case 0x32:  // ColorRGB
        CheckArgCount(count, 1, 1);
        *out = parser->ParseColorRGB(args[0]);
        return true;
    case 0x34:  // ColorRGBA
        CheckArgCount(count, 1, 1);
        *out = parser->ParseColorRGBA(args[0]);
        return true;
    case 0x38: {  // Transform: offset [scale [eulerXYZ]]
        CheckArgCount(count, 1, 3);
        Transform_s006a_6340 t;
        Vector3_s006a_6340 offset = parser->ParseVector3(args[0]);
        t.SetOffset(offset);
        if (count > 1)
            t.SetScale(parser->ParseFloat(args[1]));
        if (count > 2) {
            Vector3_s006a_6340 euler = parser->ParseVector3(args[2]);
            t.SetRotation(SP::Matrix3FromEulerXYZ(euler));
        }
        *out = t;
        return true;
    }
    case 0x39: {  // BBox: lower upper
        CheckArgCount(count, 2, 2);
        *out = BoundingBox_s006a_6340(parser->ParseVector3(args[0]), parser->ParseVector3(args[1]));
        return true;
    }

    // ------------------------------------------------------------------ array values
    case kArray | 0x01: {
        SpVector<bool> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseBool(args[i]);
        SetArray(out, 0x01, values, sizeof(bool), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x09: {
        SpVector<int> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseInt(args[i]);
        SetArray(out, 0x09, values, sizeof(int), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x0a: {
        SpVector<unsigned int> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseUInt(args[i]);
        SetArray(out, 0x0a, values, sizeof(unsigned int), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x0d: {
        SpVector<float> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseFloat(args[i]);
        SetArray(out, 0x0d, values, sizeof(float), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x12: {
        SpVectorNP<string8> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = args[i];
        SetArray(out, 0x12, values, sizeof(string8), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x13: {
        SpVectorNP<string16> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = EA::ConvertToString16(args[i]);
        SetArray(out, 0x13, values, sizeof(string16), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x22: {
        SpVector<LocalizedString_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments_s006a_6340 entry(args[i]);
            int n;
            const char** a = entry.MainArguments(&n, 1, 2);
            ResourceKey key(0xffffffff, 0xffffffff, 0xffffffff);
            if (n > 1)
                SPKeyFromName(&key, a[1], 0, 0);
            SetLocalizedString(key.groupID, key.instanceID, EA::ConvertToString16(a[0]).c_str(),
                               &values[i]);
        }
        SetArray(out, 0x22, values, sizeof(LocalizedString_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x20: {
        SpVector<ResourceKey> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            SPKeyFromName(&values[i], args[i], 0, 0);
        SetArray(out, 0x20, values, sizeof(ResourceKey), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x30: {
        SpVector<Vector2_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector2(args[i]);
        SetArray(out, 0x30, values, sizeof(Vector2_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x31: {
        SpVector<Vector3_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector3(args[i]);
        SetArray(out, 0x31, values, sizeof(Vector3_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x33: {
        SpVector<Vector4_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector4(args[i]);
        SetArray(out, 0x33, values, sizeof(Vector4_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x32: {
        SpVector<ColorRGB_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseColorRGB(args[i]);
        SetArray(out, 0x32, values, sizeof(ColorRGB_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x34: {
        SpVector<ColorRGBA_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseColorRGBA(args[i]);
        SetArray(out, 0x34, values, sizeof(ColorRGBA_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x38: {
        SpVector<Transform_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments_s006a_6340 entry(args[i]);
            int n;
            const char** a = entry.MainArguments(&n, 1, 3);
            Transform_s006a_6340& t = values[i];
            Vector3_s006a_6340 offset = parser->ParseVector3(a[0]);
            t.SetOffset(offset);
            if (n > 1)
                t.SetScale(parser->ParseFloat(a[1]));
            if (n > 2) {
                Vector3_s006a_6340 euler = parser->ParseVector3(a[2]);
                t.SetRotation(SP::Matrix3FromEulerXYZ(euler));
            }
        }
        SetArray(out, 0x38, values, sizeof(Transform_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    case kArray | 0x39: {
        SpVector<BoundingBox_s006a_6340> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments_s006a_6340 entry(args[i]);
            const char** a = entry.MainArguments(2);
            values[i] = BoundingBox_s006a_6340(parser->ParseVector3(a[0]), parser->ParseVector3(a[1]));
        }
        SetArray(out, 0x39, values, sizeof(BoundingBox_s006a_6340), count);
        out->mFlags |= Variant_s006a_6340::kFlagArray;
        return true;
    }
    default:
        return false;
    }
}





// @ 0x006a7e40
void SP::cPropertyManager::PreloadPropertyLists()
{
    // TODO(partial): walks the resource manager's property-list resources, instantiates a
    // cPropertyList per instance, feeds it through cPropertyList::cPropertyList("Preloaded")
    // and cPropertyList::Load, then registers every resulting list via
    // FUN_006a1710/GetPropertyList.  The 4096-entry scratch vector and the EH/FUN_* cleanup
    // layout are not reproduced yet.
}




// @ 0x006a8610
void GetVariantValueDescription(Property* prop, eastl::string* out)
{
    uint32_t type = prop->mnType;
    if (prop->mnFlags & 0x80)
        type |= 0x80000000u;
    out->clear();

    switch (type) {
    case 0x00:
        out->assign("unknown");
        return;
    case 0x01:
        if (*prop->GetValueBool())
            out->assign("true");
        else
            out->assign("false");
        return;
    case 0x02:
        out->sprintf("%c", (int)*prop->GetValueChar());
        return;
    case 0x03:
        out->sprintf("%lc", (unsigned int)(uint16_t)*prop->GetValueWChar());
        return;
    case 0x05:
        out->sprintf("%d", (int)*prop->GetValueInt8());
        return;
    case 0x06:
        out->sprintf("%d", (unsigned int)*prop->GetValueUInt8());
        return;
    case 0x07:
        out->sprintf("%d", (int)*prop->GetValueInt16());
        return;
    case 0x08:
        out->sprintf("%d", (unsigned int)*prop->GetValueUInt16());
        return;
    case 0x09:
        out->sprintf("%d", *prop->GetValueInt32());
        return;
    case 0x0a:
        out->sprintf("%d", *prop->GetValueUInt32());
        return;
    case 0x0b:
        out->sprintf("%d", *prop->GetValueInt64());
        return;
    case 0x0c:
        out->sprintf("%d", *prop->GetValueUInt64());
        return;
    case 0x0d:
        out->sprintf("%f", (double)*prop->GetValueFloat());
        return;
    case 0x0e:
        out->sprintf("%f", *prop->GetValueDouble());
        return;
    case 0x0f:
    case 0x10:
    case 0x11:
        out->assign("void");
        return;
    case 0x12:
        out->sprintf("\"%s\"", *(StringImage*)prop->GetValueString8());
        return;
    case 0x13:
        out->sprintf("\"%s\"", EA::ConvertToString8(*prop->GetValueString16()).c_str());
        return;
    case 0x20: {
        const ResourceKey_s006a_8610* key = prop->GetValueKey();
        eastl::string16_s006a_8610 name;
        GetResourceManager()->GetFileName(*key, &name);
        GetKeyDisplayName(*key, &name, 0);
        *out = EA::ConvertToString8(name);
        return;
    }
    case 0x21: {
        Flags96_s006a_8610 flags = *prop->GetValueFlags();
        for (int i = 0; i < 96; i++) {
            if (flags.test(i))
                EA::ArgScript::SprintfAppend(out, "%d ", i);
        }
        return;
    }
    case 0x22: {
        SP::cString_s006a_8610 text;
        SP::LoadFromKey(prop->GetValueText(), &text);
        out->sprintf("%ls", text.GetText());
        return;
    }
    case 0x30: {
        const Vector2* v = prop->GetValueVector2();
        out->sprintf("(%g, %g)", (double)v->x, (double)v->y);
        return;
    }
    case 0x31: {
        const Vector3_s006a_8610* v = prop->GetValueVector3();
        out->sprintf("(%g, %g, %g)", (double)v->x, (double)v->y, (double)v->z);
        return;
    }
    case 0x32: {
        const Vector3_s006a_8610* v = prop->GetValueColorRGB();
        out->sprintf("(%g, %g, %g)", (double)v->x, (double)v->y, (double)v->z);
        return;
    }
    case 0x33: {
        const Vector4* v = prop->GetValueVector4();
        out->sprintf("(%g, %g, %g, %g)", (double)v->x, (double)v->y, (double)v->z, (double)v->w);
        return;
    }
    case 0x34: {
        const Vector4* v = prop->GetValueColorRGBA();
        out->sprintf("(%g, %g, %g, %g)", (double)v->x, (double)v->y, (double)v->z, (double)v->w);
        return;
    }
    case 0x38: {
        Transform_s006a_8610 t(*prop->GetValueTransform());
        Vector3_s006a_8610 euler = GetEulerAngles(t.mRotation);
        out->sprintf("((%g, %g, %g) %g (%g, %g, %g))",
                     (double)t.mOffset.x, (double)t.mOffset.y, (double)t.mOffset.z, (double)t.mfScale,
                     (double)euler.x, (double)euler.y, (double)euler.z);
        return;
    }
    case 0x39: {
        const BBox* b = prop->GetValueBBox();
        out->sprintf("(%g, %g, %g) (%g, %g, %g)",
                     (double)b->lower.x, (double)b->lower.y, (double)b->lower.z,
                     (double)b->upper.x, (double)b->upper.y, (double)b->upper.z);
        return;
    }

    // ---------------------------------------------------------------- arrays
    case 0x80000001: {
        int count = prop->GetItemCount();
        const bool* values = (const bool*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %s ", values[i] ? "true" : "false");
        break;
    }
    case 0x80000009: {
        int count = prop->GetItemCount();
        const int32_t* values = (const int32_t*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %d ", values[i]);
        break;
    }
    case 0x8000000a: {
        int count = prop->GetItemCount();
        const uint32_t* values = (const uint32_t*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %d ", values[i]);
        break;
    }
    case 0x8000000d: {
        int count = prop->GetItemCount();
        const float* values = (const float*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %g ", (double)values[i]);
        break;
    }
    case 0x80000012: {
        int count = prop->GetItemCount();
        const eastl::string* values = (const eastl::string*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %s ", values[i].c_str());
        break;
    }
    case 0x80000013: {
        int count = prop->GetItemCountInl();
        const eastl::string16_s006a_8610* values = (const eastl::string16_s006a_8610*)prop->GetValueInl();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %ls", values[i].c_str());
        break;
    }
    case 0x80000020: {
        IResourceManager* rm = GetResourceManager();
        int count = prop->GetItemCount();
        const ResourceKey_s006a_8610* keys = (const ResourceKey_s006a_8610*)prop->GetValue();
        eastl::string16_s006a_8610 name;
        for (int i = 0; i < count; i++) {
            rm->GetFileName(keys[i], &name);
            GetKeyDisplayName(keys[i], &name, 0);
            out->append("\n   ");
            out->append(EA::ConvertToString8(name));
            out->push_back(' ');
        }
        out->append("\nend");
        return;
    }
    case 0x80000022: {
        int count = prop->GetItemCount();
        LocalizedString_s006a_8610* texts = (LocalizedString_s006a_8610*)prop->GetValue();
        SP::cString_s006a_8610 text;
        for (int i = 0; i < count; i++) {
            // the original calls the Property text accessor on the array item itself
            SP::LoadFromKey(((Property*)&texts[i])->GetValueText(), &text);
            EA::ArgScript::SprintfAppend(out, "\n   %ls", text.GetText());
        }
        out->append("\nend");
        return;
    }
    case 0x80000030: {
        int count = prop->GetItemCount();
        const Vector2* values = (const Vector2*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g) ", (double)values[i].x, (double)values[i].y);
        break;
    }
    case 0x80000031: {
        int count = prop->GetItemCount();
        const Vector3_s006a_8610* values = (const Vector3_s006a_8610*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g, %g) ",
                                         (double)values[i].x, (double)values[i].y, (double)values[i].z);
        break;
    }
    case 0x80000032: {
        int count = prop->GetItemCount();
        const Vector3_s006a_8610* values = (const Vector3_s006a_8610*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g, %g) ",
                                         (double)values[i].x, (double)values[i].y, (double)values[i].z);
        break;
    }
    case 0x80000033: {
        int count = prop->GetItemCount();
        const Vector4* values = (const Vector4*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g, %g, %g) ",
                                         (double)values[i].x, (double)values[i].y,
                                         (double)values[i].z, (double)values[i].w);
        break;
    }
    case 0x80000034: {
        int count = prop->GetItemCount();
        const Vector4* values = (const Vector4*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g, %g, %g) ",
                                         (double)values[i].x, (double)values[i].y,
                                         (double)values[i].z, (double)values[i].w);
        break;
    }
    case 0x80000038: {
        int count = prop->GetItemCount();
        const Transform_s006a_8610* values = (const Transform_s006a_8610*)prop->GetValue();
        for (int i = 0; i < count; i++) {
            Vector3_s006a_8610 offset = values[i].mOffset;
            Vector3_s006a_8610 euler = GetEulerAngles(values[i].mRotation);
            out->append_sprintf("\n   ((%g, %g, %g) %g (%g, %g, %g)) ",
                                (double)offset.x, (double)offset.y, (double)offset.z,
                                (double)values[i].mfScale,
                                (double)euler.x, (double)euler.y, (double)euler.z);
        }
        break;
    }
    case 0x80000039: {
        int count = prop->GetItemCount();
        const BBox* values = (const BBox*)prop->GetValue();
        for (int i = 0; i < count; i++)
            out->append_sprintf("\n   ((%g, %g, %g) (%g, %g, %g)) ",
                                (double)values[i].lower.x, (double)values[i].lower.y,
                                (double)values[i].lower.z, (double)values[i].upper.x,
                                (double)values[i].upper.y, (double)values[i].upper.z);
        break;
    }
    default:
        return;
    }
    out->append("\nend");
}



// @ 0x006a9470
void cListPropsCheat::Execute(cArguments_s006a_9470* args)
{
    AutoRef<PropList> list(sAppProperties);

    const char** opt = args->OptionArguments("list", 1);
    if (opt) {
        ResourceKey_s006a_9470 key = {0, 0, 0};
        SPKeyFromName(&key, opt[0], 0, 0);
        list = 0;
        if (!mMgr->GetPropertyList(key.a, key.c, &list))
            throw cError_s006a_9470("no such property list!");
    }

    bool ids = args->HasFlag("ids");
    args->HasFlag("desc");

    int cnt;
    const char* wild = 0;
    const char** main = args->MainArguments(&cnt, 0, 1);
    if (cnt > 0)
        wild = main[0];

    UIntVec v;
    list.p->GetPropertyIDs(&v);
    if (v.mpBegin != v.mpEnd) {
        int n = (int)(v.mpEnd - v.mpBegin);
        for (int i = 0; i < n; i++) {
            PropObj* prop = list.p->GetProperty(v.mpBegin[i]);

            eastl::string_s006a_9470 typeDesc;
            GetVariantTypeDescription(prop, &typeDesc);
            eastl::string_s006a_9470 valueDesc;
            eastl::string_s006a_9470 suffix;
            GetVariantValueDescription(prop, &valueDesc);

            unsigned id = v.mpBegin[i];
            const char* name = mMgr->GetPropertyName(id);
            bool named = name != 0;
            if (!name) {
                unsigned key = v.mpBegin[i];
                IdNameIter it = mMgr->mIdToName.find(key);
                if (it.node != mMgr->mIdToName.end()) {
                    name = it.node->name;
                    named = name != 0;
                }
            }

            if (named && (!wild || WildcardMatch(name, wild, 0))) {
                if (!ids)
                    Output(mOut, "%s = %s (%s) %s\n", name, valueDesc.c_str(), typeDesc.c_str(), suffix.c_str());
                else
                    Output(mOut, "%s [0x%08x] = %s (%s) %s\n", name, v.mpBegin[i], valueDesc.c_str(),
                           typeDesc.c_str(), suffix.c_str());
            } else if (!wild) {
                Output(mOut, "0x%08x = %s %s %s\n", v.mpBegin[i], valueDesc.c_str(), typeDesc.c_str(),
                       suffix.c_str());
            }
        }
    }
}


// @ 0x006a9790
void cPropCheat::Execute(cArguments_s006a_9470* args)
{
    AutoRef<PropList> list(sAppProperties);

    int argc = 0;
    const char** argv = args->MainArguments(&argc, 1, 0x7fffffff);

    unsigned propId = 0;
    PropertyManager()->LookupPropertyID(argv[0], &propId);
    if (propId == 0)
        throw cError_s006a_9470("no such property: %s", argv[0]);

    if (argc > 1) {
        Variant_s006a_9470 v;
        v = *PropertyManager()->GetDefaultVariant(propId);
        if (v.type == 0) {
            const Variant_s006a_9470* p;
            list.p->GetVariant(propId, &p);
            v = *p;
        }
        v.flags |= 2;
        unsigned vt = v.type;
        if (v.flags & 0x80)
            vt |= 0x80000000;
        int n = argc - 1;
        if (!ParseVariantValue(vt, mOut, n, argv + 1, &v))
            throw cError_s006a_9470("unknown property type");
        list.p->SetProperty(propId, &v);

        PropMsg msg;
        msg.d[0].v = ((unsigned*)list.p)[3];
        msg.d[1].v = ((unsigned*)list.p)[4];
        msg.d[2].v = ((unsigned*)list.p)[2];
        MessageServer()->Post(0xf62def, &msg, 0);
    } else if (args->HasFlag("remove") || args->HasFlag("clear")) {
        list.p->RemoveProperty(propId);
        PropMsg msg;
        msg.d[0].v = ((unsigned*)list.p)[3];
        msg.d[1].v = ((unsigned*)list.p)[4];
        msg.d[2].v = ((unsigned*)list.p)[2];
        MessageServer()->Post(0xf62def, &msg, 0);
    } else {
        PropObj* prop = list.p->GetProperty(propId);
        eastl::string_s006a_9470 typeDesc;
        GetVariantTypeDescription(prop, &typeDesc);
        eastl::string_s006a_9470 valueDesc;
        GetVariantValueDescription(prop, &valueDesc);
        eastl::string_s006a_9470 suffix;
        Output(mOut, "%s = %s (%s) %s \n", argv[0], valueDesc.c_str(), typeDesc.c_str(), suffix.c_str());
    }
}


// @ 0x006a9b60
bool cPropertyManager_s006a_9470::Init()
{
    if (mInitialized)
        return true;
    mInitialized = true;

    mResMgr = GetResourceManager_s006a_9470();
    mResMgr->RegisterFactory(1, &factoryVtbl, 0);

    ResourceKey_s006a_9470* appKey = (ResourceKey_s006a_9470*)((char*)sAppProperties + 8);
    appKey->a = 0;
    appKey->b = 0xb1b104;
    appKey->c = 0;

    ResourceKey_s006a_9470 key = {0x8ea246b, 0xb1b104, 0};
    IResource* found = mResMgr->FindResource(&key);
    if (found && found->GetType() != 0x34728492) {
        AutoRef<IResource> res;
        if (mResMgr->GetResource(&key, &res, 0, 0, 0, 0)) {
            BaseList()->LoadFrom(res.p);
            sAppProperties->LoadFrom(res.p);
        }
    }

    mParser = CreateParser();
    if (mUseFileParser) {
        mFileParser = CreateFileParser();
        mFileParser.p->f2();
        mFileParser.p->SetParser(mParser.p);
    } else {
        mParser.p->p2();
    }
    mParser.p->SetOwner(&mBlock10);

    mParser.p->RegisterCommand(gCmdName_Property, new("ArgScript/Property", 0, 0, 0, 0) cPropertyDefCmd);
    mParser.p->RegisterCommand(gCmdName_PropertyGroup, new("ArgScript/PropertyGroup", 0, 0, 0, 0) cPropertyGroupDefCmd);
    mParser.p->RegisterCommand(gCmdName_PropertyList, new("ArgScript/PropertyList", 0, 0, 0, 0) cPropertyListDefCmd);
    mParser.p->RegisterCommand(gCmdName_AppProps, new("ArgScript/AppProps", 0, 0, 0, 0) cAppPropsCmd);
    mParser.p->RegisterHashFunction("hash", new("App", 0, 0, 0, 0) cHashFunction)->Finish();

    mParsing = true;
    if (mFileParser.p) {
        eastl::wstring path(GetDirFromID(0xa0214f));
        const wchar_t* name = L"Properties.txt";
        const wchar_t* nameEnd = name;
        while (*nameEnd)
            ++nameEnd;
        path.append(name, nameEnd);
        {
            eastl::string_s006a_9470 conv;
            mFileParser.p->ParseFile(ConvertToString8(&conv, &path)->mpBegin, 5);
        }
        mFileParser.p->f8();
        mFileParser.p->f11(1);
    } else {
        ResourceKey_s006a_9470 hashKey = {0x658b0ab2, 0x24a0e52, 0};
        ParseHashDefault(mParser.p, &hashKey);
    }
    mParsing = false;

    ((PropVec*)((char*)this + 0x54))->reserve(mTreeSize);

    void* end = &mTreeRight;
    for (char* it = (char*)mTreeLeft; it != (char*)end; it = (char*)RBTreeIncrement(it))
        BaseList()->SetProperty(*(unsigned*)(it + 0x10), (const Variant_s006a_9470*)(it + 0x14));
    DoNuke(mTreeRoot);
    mTreeRight = end;
    mTreeLeft = end;
    mTreeRoot = 0;
    mTreeColor = 0;
    mTreeSize = 0;

    ICheatMgr* cheats = CheatManager();
    if (cheats) {
        cListPropsCheat* listCheat = new("App", 0, 0, 0, 0) cListPropsCheat;
        listCheat->mMgr = (ListMgr*)this;
        cPropCheat* propCheat = new("App", 0, 0, 0, 0) cPropCheat;
        propCheat->mMgr = (ListMgr*)this;
        cheats->AddCheat("prop", propCheat, 0);
    }

    IMessageServer* ms = MessageServer();
    if (ms)
        ms->AddHandler(0xf62ade, mHandler);
    return true;
}


// @ 0x006aa0d0
bool BoolVecOwner::Append(int arg1, BoolVec* v)
{
    // this->vfunc_0x48(arg1, v)
    typedef void (__thiscall* Fn48)(void*, int, BoolVec*);
    ((Fn48)((void**)vtbl)[0x48 / 4])(this, arg1, v);

    FUN_0050f0d0(v->mpBegin, v->mpEnd);
    void* dst = FUN_0050e4b0(v->mpBegin, v->mpEnd);
    void* src = v->mpEnd;
    BoolVec_DoInsertValue(dst, src, 0);
    v->mpEnd = (char*)v->mpEnd - (((char*)src - (char*)dst) >> 2) * 4;
    return v->mpBegin != v->mpEnd;
}


// @ 0x006aa130
bool cPropertyFactory::WriteResource(PropList* list, IResEntry* entry, int a3, int a4)
{
    cPropertyManager_s006a_9470* mgr = (cPropertyManager_s006a_9470*)((char*)this - 4);
    bool ok;
    StreamRef stream(entry->GetStream());
    char* owner = entry->GetOwner();
    if (!owner || !((IQueryable*)(owner + 4))->Query(0x226a1de)) {
        ok = list->Write(stream.p);
    } else {
        eastl::string_s006a_9470 line;
        UIntVec ids;
        list->GetPropertyIDs(&ids);
        eastl::string_s006a_9470 desc;
        int n = (int)(ids.mpEnd - ids.mpBegin);
        for (int i = 0; i < n; i++) {
            unsigned id = ids.mpBegin[i];
            bool present;
            if (mgr->mParsing) {
                unsigned key = id;
                present = ((PropTree*)((char*)mgr + 0x20))->find(key).node != mgr->mTreeEndNode();
            } else {
                present = mgr->BaseList()->HasProperty(id);
            }
            if (present) {
                PropObj* prop = list->GetProperty(id);
                GetVariantValueDescription(prop, &desc);
                if (prop->flags & 0x80)
                    stream.p->Write("array ", 6);
                const char* name = ((IPropertyManager*)mgr)->GetPropertyName(ids.mpBegin[i]);
                if (name) {
                    const char* e = name;
                    while (*e++) {}
                    stream.p->Write(name, (int)(e - (name + 1)));
                    stream.p->Write(" ", 1);
                } else {
                    line.sprintf("0x%08x ", ids.mpBegin[i]);
                    stream.p->Write(line.mpBegin, (int)(line.mpEnd - line.mpBegin));
                }
                for (const char* c = desc.mpBegin; *c; ++c) {
                    if (*c == '\r' && c[1] == '\n')
                        continue;
                    if (*c == '\n')
                        stream.p->Write("\r\n", 2);
                    else
                        stream.p->Write(c, 1);
                }
                stream.p->Write("\r\n", 2);
            }
        }
        ok = true;
    }
    return ok;
}


// @ 0x006aa3f0
void cPropertyManager_s006a_a3f0::RegisterPropertyName(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa450
void cPropertyManager_s006a_a3f0::Fun_006aa450(const char* name, uint32_t id)
{
    StrKey* s = mGroupIDToNameMap[id];
    s->assign(name);

    uint32_t* end = mGroupIDs.mpEnd;
    if (end < mGroupIDs.mpCapacity) {
        mGroupIDs.mpEnd = end + 1;
        if (end)
            *end = id;
    } else {
        mGroupIDs.DoInsertValue(end, &id);
    }
}

// @ 0x006aa4c0
void FUN_006aa4c0(void* self, uint32_t key, int value)
{
    // TODO(partial): rbtree insert (find/yrotate/alloc node, copy EA::Variant).
    (void)self; (void)key; (void)value;
}

// @ 0x006aa5e0
void cPropertyManager_s006a_a3f0::RegisterPropertyNameLocal(const char* name, uint32_t id)
{
    EA_MakeCaseInsensitive(name, &mLCName);
    mLocalPropertyNameToIDMap[mLCName] = id;
    StrKey* s = mLocalPropertyIDToNameMap[id];
    s->assign(name);
}

// @ 0x006aa640
void cPropertyCommandExec::Execute(void* args)
{
    // TODO(partial): parse the command line, look the property up and print/set it.
    (void)args;
}

// @ 0x006aa780
void FUN_006aa780(void* self, void* args)
{
    // TODO(partial): group-name command handler (MainArguments + manager id/name maps).
    (void)self; (void)args;
}

// @ 0x006aa7c0
bool SP::cPropertyManager::Shutdown()
{
    // TODO(partial): unregister from the message server/resource manager, unregister the
    // listProps/prop cheats, release mLine and tear down all property maps/vectors.
    return 1;
}

// @ 0x006aa910
uint8_t FUN_006aa910(void* self, uint32_t arg2, int* arg3)
{
    // TODO(partial): append 0xc-stride entries into the bool vector and return non-empty.
    (void)self; (void)arg2; (void)arg3;
    return 0;
}

// @ 0x006aaa10
void FUN_006aaa10(void* self, uint32_t id, uint32_t arg2, uint32_t arg3)
{
    // TODO(partial): parse a property line and add it to the base property list.
    (void)self; (void)id; (void)arg2; (void)arg3;
}

// @ 0x006aadb0
bool cPropertyCommand::Parse(void** param_2)
{
    mManager->ParseAndAddProperty(*(uint32_t*)param_2, mArg3, mArg4);
    return true;
}

// @ 0x006ab120
char FUN_006ab120(void* self, int* arg2, int* arg3)
{
    // TODO(partial): SP::cPropertyManager::ReadResource.
    (void)self; (void)arg2; (void)arg3;
    return 0;
}
