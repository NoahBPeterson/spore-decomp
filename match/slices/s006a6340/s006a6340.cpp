// Slice s006a6340 - EA::ArgScript -> EA::Variant value parser (SporeApp.exe, MSVC 2008 SP1).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE  (old-style EH prolog, no cookie, frame 0x6a0;
// Vector3 copies go through movss).
//
// `anonymous namespace'::ParseVariantValue (dev-PDB anchor 0157a300) converts the textual
// arguments of an ArgScript line into an EA::Variant (the App::Property payload) according
// to a property type tag.  Scalar tags (App::PropertyType: Bool 1, Int32 9, UInt32 0xa,
// Float 0xd, String8 0x12, String16 0x13, Key 0x20, Flags 0x21, Text 0x22, Vector2 0x30,
// Vector3 0x31, ColorRGB 0x32, Vector4 0x33, ColorRGBA 0x34, Transform 0x38, BBox 0x39)
// assign one value; the same tags with bit 0x80000000 set build an eastl::vector of
// values, hand it to Variant::Set (which copies it) and mark the output as an array (0x80).
//
// Complete reconstruction of every path; not byte-exact (EH state numbering, register
// allocation and the inline/out-of-line split of a few EASTL helpers differ).
#include "types.h"

#pragma warning(disable : 4290 4100)

// ---------------------------------------------------------------------------------------
// Math / resource value types (ModAPI layouts; all have user ctors so the parser returns
// them through a hidden result pointer, as the original does).
// Per-field copies (the original moves them through movss, not integer registers).
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const Vector2& o) : x(o.x), y(o.y) {}
    Vector2& operator=(const Vector2& o) { x = o.x; y = o.y; return *this; }
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(const Vector4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    Vector4& operator=(const Vector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};
struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(const ColorRGB& o) : r(o.r), g(o.g), b(o.b) {}
    ColorRGB& operator=(const ColorRGB& o) { r = o.r; g = o.g; b = o.b; return *this; }
};
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA() {}
    ColorRGBA(const ColorRGBA& o) : r(o.r), g(o.g), b(o.b), a(o.a) {}
    ColorRGBA& operator=(const ColorRGBA& o) { r = o.r; g = o.g; b = o.b; a = o.a; return *this; }
};
struct Matrix3 { float m[9]; };

struct BoundingBox {
    Vector3 lower;  // +0x00
    Vector3 upper;  // +0x0c
    BoundingBox() {}
    __forceinline BoundingBox(const Vector3& lo, const Vector3& hi) : lower(lo), upper(hi) {}
};

// Spore Transform (0x38 bytes).
struct Transform {
    uint16_t mnFlags;           // +0x00
    uint16_t mnTransformCount;  // +0x02
    Vector3  mOffset;           // +0x04
    float    mfScale;           // +0x10
    Matrix3  mRotation;         // +0x14
    Transform();                // 0x00409930 (pos 0, scale 1, rotation identity)
    void SetOffset(const Vector3& v)   { mnFlags |= 4; mnTransformCount++; mOffset = v; }
    void SetScale(float s)             { mfScale = s; mnTransformCount++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnFlags |= 2; mnTransformCount++; }
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

// 96-bit flag set (property type 0x21).
struct Flags96 {
    uint32_t mWord[3];
    Flags96() { mWord[0] = 0; mWord[1] = 0; mWord[2] = 0; }
    void set(uint32_t bit) { mWord[bit >> 5] |= 1u << (bit & 31); }
};

// App::Property LocalizedString payload (0x208 bytes).
struct LocalizedString {
    uint32_t mTableID;      // +0x000
    uint32_t mInstanceID;   // +0x004
    wchar_t  mBuffer[256];  // +0x008
    LocalizedString() : mTableID(0xffffffff), mInstanceID(0xffffffff) { mBuffer[0] = 0; }
};

// ---------------------------------------------------------------------------------------
// EASTL pieces.
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

namespace EA { string16 ConvertToString16(const char* p, int len = -1); }  // 0x0093c5a0

void operator delete[](void* p); // 0x00f47380

// eastl::vector<T, sp_vector_allocator>: (n, allocator) ctor out of line; for POD element
// types the dtor is inline and the sp allocator frees only blocks with a non-zero header.
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

// Same, for element types with a destructor (dtor out of line).
template <class T>
struct SpVectorNP {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator;
    SpVectorNP(int n, const allocator_tag& a);  // 0x006a5e10 / 0x0068a460
    ~SpVectorNP();                              // 0x00553b90 / 0x00553e00
    T& operator[](int i) { return mpBegin[i]; }
    T* data() { return mpBegin; }
};

// ---------------------------------------------------------------------------------------
// EA::Variant (dev PDB: size 0x14; mFlags +0x10, mTypeId +0x12).
struct Variant {
    enum { kFlagCleanup = 4, kFlagArray = 0x80, kSetFlagsCopy = 0x18 };
    char     mValue[0x10];
    uint16_t mFlags;   // +0x10
    uint16_t mTypeId;  // +0x12
    Variant() { mFlags = 0; mTypeId = 0; }
    ~Variant() { if (mFlags & kFlagCleanup) Destruct(0); }
    void Destruct(int);                                                          // 0x0093db80
    bool Set(uint32_t type, int flags, const void* p, uint32_t size, uint32_t n);  // 0x0093dd80
    Variant& operator=(const Variant& x);                                         // 0x00542b80
    // operator=<bool/int/uint/float/Key/string/string16/Vector*/Color*/Transform/BBox/Flags>
    template <class T> Variant& operator=(const T& v);
};

// ---------------------------------------------------------------------------------------
// ArgScript.
namespace EA { namespace ArgScript {

class cError {
    char mMessage[0x10];  // eastl::string
public:
    cError(const char* fmt, ...);  // 0x0052df30 (vsnprintf into the message)
    cError(const cError&);
    ~cError();
};

class cArguments {  // size 0x38
    char mStorage[0x38];
public:
    cArguments(const char* text);                                // 0x008386d0
    ~cArguments();                                               // 0x00837fa0
    const char** MainArguments(int* count, int nMin, int nMax);  // 0x00838020
    const char** MainArguments(int count);                       // 0x00838320
};

// The format parser: only the value-parsing virtuals at +0x94..+0xb4 are used here.
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
    virtual Vector2      ParseVector2(const char* s);    // +0xa4
    virtual Vector3      ParseVector3(const char* s);    // +0xa8
    virtual Vector4      ParseVector4(const char* s);    // +0xac
    virtual ColorRGB     ParseColorRGB(const char* s);   // +0xb0
    virtual ColorRGBA    ParseColorRGBA(const char* s);  // +0xb4
};

}}  // namespace EA::ArgScript

using EA::ArgScript::cError;
using EA::ArgScript::cArguments;
using EA::ArgScript::cFormatParser;

void SPKeyFromName(ResourceKey* key, const char* name, uint32_t defType, uint32_t defGroup);  // 0x0068d5a0
namespace SP { Matrix3 Matrix3FromEulerXYZ(const Vector3& euler); }                        // 0x005f4e80
// Fills a LocalizedString from (table, instance, placeholder text).
void SetLocalizedString(uint32_t tableID, uint32_t instanceID, const wchar_t* text,
                        LocalizedString* out);                                              // 0x006b5040

static const uint32_t kArray = 0x80000000;

// Argument-count check (expanded in every case: each has its own cError temporary).
#define CheckArgCount(count, nMin, nMax) \
    if ((count) < (nMin) || (count) > (nMax)) \
        throw cError("wrong number of arguments: %d, expecting [%d, %d]\n", (count), (nMin), (nMax))

// Assigns an array payload built in `values` to `out` and marks it as an array.
template <class Vec>
static __forceinline void SetArray(Variant* out, uint32_t type, Vec& values, uint32_t elemSize, int count)
{
    Variant tmp;
    tmp.Set(type, Variant::kSetFlagsCopy, values.data(), elemSize, count);
    *out = tmp;
}

namespace {

// @ 0x006a6340
// `anonymous namespace'::ParseVariantValue
bool ParseVariantValue(uint32_t type, cFormatParser* parser, int count, const char** args,
                       Variant* out)
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
        Flags96 flags;
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
        LocalizedString text;
        SetLocalizedString(key.groupID, key.instanceID, EA::ConvertToString16(args[0]).c_str(), &text);
        Variant tmp;
        tmp.Set(0x22, Variant::kSetFlagsCopy, &text, sizeof(LocalizedString), 1);
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
        Transform t;
        Vector3 offset = parser->ParseVector3(args[0]);
        t.SetOffset(offset);
        if (count > 1)
            t.SetScale(parser->ParseFloat(args[1]));
        if (count > 2) {
            Vector3 euler = parser->ParseVector3(args[2]);
            t.SetRotation(SP::Matrix3FromEulerXYZ(euler));
        }
        *out = t;
        return true;
    }
    case 0x39: {  // BBox: lower upper
        CheckArgCount(count, 2, 2);
        *out = BoundingBox(parser->ParseVector3(args[0]), parser->ParseVector3(args[1]));
        return true;
    }

    // ------------------------------------------------------------------ array values
    case kArray | 0x01: {
        SpVector<bool> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseBool(args[i]);
        SetArray(out, 0x01, values, sizeof(bool), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x09: {
        SpVector<int> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseInt(args[i]);
        SetArray(out, 0x09, values, sizeof(int), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x0a: {
        SpVector<unsigned int> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseUInt(args[i]);
        SetArray(out, 0x0a, values, sizeof(unsigned int), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x0d: {
        SpVector<float> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseFloat(args[i]);
        SetArray(out, 0x0d, values, sizeof(float), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x12: {
        SpVectorNP<string8> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = args[i];
        SetArray(out, 0x12, values, sizeof(string8), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x13: {
        SpVectorNP<string16> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = EA::ConvertToString16(args[i]);
        SetArray(out, 0x13, values, sizeof(string16), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x22: {
        SpVector<LocalizedString> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments entry(args[i]);
            int n;
            const char** a = entry.MainArguments(&n, 1, 2);
            ResourceKey key(0xffffffff, 0xffffffff, 0xffffffff);
            if (n > 1)
                SPKeyFromName(&key, a[1], 0, 0);
            SetLocalizedString(key.groupID, key.instanceID, EA::ConvertToString16(a[0]).c_str(),
                               &values[i]);
        }
        SetArray(out, 0x22, values, sizeof(LocalizedString), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x20: {
        SpVector<ResourceKey> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            SPKeyFromName(&values[i], args[i], 0, 0);
        SetArray(out, 0x20, values, sizeof(ResourceKey), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x30: {
        SpVector<Vector2> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector2(args[i]);
        SetArray(out, 0x30, values, sizeof(Vector2), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x31: {
        SpVector<Vector3> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector3(args[i]);
        SetArray(out, 0x31, values, sizeof(Vector3), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x33: {
        SpVector<Vector4> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseVector4(args[i]);
        SetArray(out, 0x33, values, sizeof(Vector4), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x32: {
        SpVector<ColorRGB> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseColorRGB(args[i]);
        SetArray(out, 0x32, values, sizeof(ColorRGB), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x34: {
        SpVector<ColorRGBA> values(count, allocator_tag());
        for (int i = 0; i < count; i++)
            values[i] = parser->ParseColorRGBA(args[i]);
        SetArray(out, 0x34, values, sizeof(ColorRGBA), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x38: {
        SpVector<Transform> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments entry(args[i]);
            int n;
            const char** a = entry.MainArguments(&n, 1, 3);
            Transform& t = values[i];
            Vector3 offset = parser->ParseVector3(a[0]);
            t.SetOffset(offset);
            if (n > 1)
                t.SetScale(parser->ParseFloat(a[1]));
            if (n > 2) {
                Vector3 euler = parser->ParseVector3(a[2]);
                t.SetRotation(SP::Matrix3FromEulerXYZ(euler));
            }
        }
        SetArray(out, 0x38, values, sizeof(Transform), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    case kArray | 0x39: {
        SpVector<BoundingBox> values(count, allocator_tag());
        for (int i = 0; i < count; i++) {
            cArguments entry(args[i]);
            const char** a = entry.MainArguments(2);
            values[i] = BoundingBox(parser->ParseVector3(a[0]), parser->ParseVector3(a[1]));
        }
        SetArray(out, 0x39, values, sizeof(BoundingBox), count);
        out->mFlags |= Variant::kFlagArray;
        return true;
    }
    default:
        return false;
    }
}

}  // namespace

// Keeps the anonymous-namespace function emitted in this TU.
bool (*g_pParseVariantValue)(uint32_t, cFormatParser*, int, const char**, Variant*) = &ParseVariantValue;
// --- equivalence checker address annotations
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void ConvertToString16(char*, int); // 0x0093c5a0
};
}
