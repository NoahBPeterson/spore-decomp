// Slice s006a4990: EA::Variant default value for an App::Property type tag (SporeApp.exe,
// MSVC 2008 SP1).  Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE (old-style EH prolog,
// no cookie, frame 0x1d8), the same module as `anonymous namespace'::ParseVariantValue (0x6a6340).
//
// SetDefaultVariantValue(type, out) stores the default value of a property type into `out`:
// zero/false/empty for the scalar tags (Bool 1, Int32 9, UInt32 0xa, Float 0xd, String8 0x12,
// String16 0x13, Key 0x20 (all 0xffffffff), Flags 0x21, Text 0x22, Vector2 0x30, Vector3 0x31,
// Vector4 0x33, ColorRGB 0x32, ColorRGBA 0x34 (module constants), Transform 0x38 (identity),
// BBox 0x39 (inverted: lower = FLT_MAX, upper = -FLT_MAX)), and an empty array for the same tags
// with bit 0x80000000 set.  Returns false for an unknown tag.
#include "types.h"
#include <string.h>

#pragma warning(disable : 4290 4100)

static const float kFloatMax = 3.402823466e+38F;

// ---------------------------------------------------------------------------------------
// Value types (ModAPI layouts).
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

// Spore Transform (0x38 bytes); default ctor out of line (pos 0, scale 1, identity).
struct Transform {
    uint32_t mData[0x38 / 4];
    Transform();                // 0x00409930
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

// 96-bit flag set (property type 0x21).
struct Flags96 {
    uint32_t mWord[3];
    Flags96() { reset(); }
    void reset() { memset(mWord, 0, sizeof(mWord)); }
};

// App::Property Text payload (LocalizedString, 0x14 bytes); ctor/dtor out of line.
struct LocalizedString {
    uint32_t mData[5];
    LocalizedString();          // 0x006b5060
    ~LocalizedString();         // 0x006b5240
};

// ---------------------------------------------------------------------------------------
// EASTL strings (16 bytes); the default ctor points at the shared empty string.
namespace eastl {
union EmptyString {
    uint32_t mUint32;
    char     mEmpty8[1];
    wchar_t  mEmpty16[1];
};
extern EmptyString gEmptyString;   // 0x01667bac

struct string8 {    // basic_string<char>
    char* mpBegin; char* mpEnd; char* mpCapacity; uint32_t mAllocator;
    string8() { mpBegin = gEmptyString.mEmpty8; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~string8() throw();                         // 0x00530670
};
struct string16 {   // basic_string<wchar_t>
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    string16() { mpBegin = gEmptyString.mEmpty16; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf() throw();              // 0x00933960
};
}  // namespace eastl

// ---------------------------------------------------------------------------------------
// EA::Variant (dev PDB: size 0x14; mFlags +0x10, mTypeId +0x12).
struct Variant {
    enum { kFlagCleanup = 4, kFlagArray = 0x80, kSetFlagsCopy = 0x18 };
    char     mValue[0x10];
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    __forceinline Variant(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n)
    {
        mFlags = 0;
        mTypeId = 0;
        Set(type, flags, p, size, n);
    }
    ~Variant() { if (mFlags & kFlagCleanup) Destruct(0); }
    void Destruct(int);                                                            // 0x0093db80
    bool Set(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n);  // 0x0093dd80
    Variant& operator=(const Variant& x);                                          // 0x00542b80

    Variant& operator=(const bool& v);                     // 0x00422e20
    Variant& operator=(const int& v);                      // 0x00422eb0
    Variant& operator=(const unsigned int& v);             // 0x00427fd0
    Variant& operator=(const float& v);                    // 0x00428060
    Variant& operator=(const eastl::string8& v);           // 0x004b5dd0
    Variant& operator=(const eastl::string16& v);          // 0x004279d0
    Variant& operator=(const ResourceKey& v);              // 0x00422f40
    Variant& operator=(const Flags96& v);                  // 0x006a34a0
    Variant& operator=(const LocalizedString& v);          // 0x006a36b0
    Variant& operator=(const Vector2& v);                  // 0x006a3510
    Variant& operator=(const Vector3& v);                  // 0x006a3570
    Variant& operator=(const Vector4& v);                  // 0x006a35e0
    Variant& operator=(const ColorRGB& v);                 // 0x006a3610
    Variant& operator=(const ColorRGBA& v);                // 0x006a3680
    Variant& operator=(const Transform& v);                // 0x006a3fa0
    Variant& operator=(const BoundingBox& v)
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

// An empty array of `type` (elements of `size` bytes) assigned to `out`.
#define SET_EMPTY_ARRAY(out, type, size)                                  \
    *(out) = Variant((type), Variant::kSetFlagsCopy, 0, (size), 0);       \
    (out)->mFlags |= Variant::kFlagArray;                                 \
    return true

// @ 0x006a4990
bool SetDefaultVariantValue(uint32_t type, Variant* out)
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
        *out = eastl::string8();
        return true;
    case 0x13:
        *out = eastl::string16();
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
    case kArray | 0x12: SET_EMPTY_ARRAY(out, 0x12, sizeof(eastl::string8));
    case kArray | 0x13: SET_EMPTY_ARRAY(out, 0x13, sizeof(eastl::string16));
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
