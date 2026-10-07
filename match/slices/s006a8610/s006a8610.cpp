// Slice s006a8610: `anonymous namespace'::GetVariantValueDescription (3666 bytes).
// Module flags: /O2 /MD /Gy /EHsc /TP (64-byte aligned frame, x87 float args).
//
// Writes a human-readable description of an App::Property value into an eastl::string:
// a switch over the property type (0x80000000 set for array properties).  Scalars are
// printed with sprintf/assign; arrays append one "\n   ..." line per item via
// EA::ArgScript::SprintfAppend / append_sprintf and end with "\nend".
#include "types.h"

// ---------------------------------------------------------------- EASTL strings (retail)
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

extern wchar_t gEmptyString16[1];  // 0x01667bac

class string16 {
 public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;

    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
}  // namespace eastl

// bit-wise image of an eastl::string (the original passes the object itself to "%s")
struct StringImage {
    uint32_t w[4];
};

namespace EA {
eastl::string ConvertToString8(const eastl::string16& s);  // 0x0093c570
namespace ArgScript {
void SprintfAppend(eastl::string* out, const char* fmt, ...);  // 0x00840c70
}
}  // namespace EA

// ---------------------------------------------------------------- math / resource types
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };
struct Matrix3 { float m[9]; };
struct BBox { Vector3 lower, upper; };
struct ResourceKey { uint32_t instance, type, group; };
struct LocalizedString { uint32_t tableId, instanceId, pad[3]; };  // 0x14 bytes per array item

struct Transform {               // 0x38 bytes
    uint16_t mnFlags;            // +0
    uint16_t mnTransformCount;   // +2
    Vector3 mOffset;             // +4
    float mfScale;               // +10
    Matrix3 mRotation;           // +14
    Transform(const Transform& x);  // 0x0040ce80
};

Vector3 GetEulerAngles(const Matrix3& m);   // 0x006a3920

struct Flags96 {
    uint32_t mWord[3];
    __forceinline bool test(uint32_t i) const
    {
        if (i < 96)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};

const Vector3* GetDefaultVector3();   // 0x006bb5e0

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
    virtual bool GetFileName(const ResourceKey& key, eastl::string16* name);  // +0x7c
};
IResourceManager* GetResourceManager();   // 0x0067dcd0
bool GetKeyDisplayName(const ResourceKey& key, eastl::string16* name, int flags);  // 0x00b1e4d0

namespace SP {
class cString {   // 0x1c bytes
 public:
    uint32_t mData[7];
    cString();                    // 0x006b5060
    ~cString();                   // 0x006b5240
    const wchar_t* GetText();     // 0x006b55c0
};
void LoadFromKey(const LocalizedString* key, cString* dst);  // 0x006b56d0
}  // namespace SP

// ---------------------------------------------------------------- App::Property
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
    eastl::string16* GetValueString16();  // 0x0068a4f0
    ResourceKey* GetValueKey();           // 0x006a1030
    Flags96* GetValueFlags();             // 0x006a3890
    LocalizedString* GetValueText();      // 0x006a1090
    Vector2* GetValueVector2();           // 0x006a0f70
    Vector3* GetValueColorRGB();          // 0x006a0fd0
    Vector4* GetValueVector4();           // 0x006a0fa0
    Vector4* GetValueColorRGBA();         // 0x006a1000
    Transform* GetValueTransform();       // 0x006a1060
    BBox* GetValueBBox();                 // 0x005f2320
    int GetItemCount();                   // 0x00571ef0
    void* GetValue();                     // 0x00446ff0

    // inlined copies of the two accessors above
    __forceinline int GetItemCountInl() const { return (mnFlags & 0x30) ? mnItemCount : (mnType != 0); }
    __forceinline void* GetValueInl() { return (mnFlags & 0x30) ? mpData : (mnType ? (void*)this : 0); }
    __forceinline const Vector3* GetValueVector3()
    {
        if (mnType == 0x31 || mnType == 0x10)
            return (const Vector3*)GetValueInl();
        return GetDefaultVector3();
    }
};


namespace {

// @ 0x006a8610  `anonymous namespace'::GetVariantValueDescription
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
        const ResourceKey* key = prop->GetValueKey();
        eastl::string16 name;
        GetResourceManager()->GetFileName(*key, &name);
        GetKeyDisplayName(*key, &name, 0);
        *out = EA::ConvertToString8(name);
        return;
    }
    case 0x21: {
        Flags96 flags = *prop->GetValueFlags();
        for (int i = 0; i < 96; i++) {
            if (flags.test(i))
                EA::ArgScript::SprintfAppend(out, "%d ", i);
        }
        return;
    }
    case 0x22: {
        SP::cString text;
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
        const Vector3* v = prop->GetValueVector3();
        out->sprintf("(%g, %g, %g)", (double)v->x, (double)v->y, (double)v->z);
        return;
    }
    case 0x32: {
        const Vector3* v = prop->GetValueColorRGB();
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
        Transform t(*prop->GetValueTransform());
        Vector3 euler = GetEulerAngles(t.mRotation);
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
        const eastl::string16* values = (const eastl::string16*)prop->GetValueInl();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   %ls", values[i].c_str());
        break;
    }
    case 0x80000020: {
        IResourceManager* rm = GetResourceManager();
        int count = prop->GetItemCount();
        const ResourceKey* keys = (const ResourceKey*)prop->GetValue();
        eastl::string16 name;
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
        LocalizedString* texts = (LocalizedString*)prop->GetValue();
        SP::cString text;
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
        const Vector3* values = (const Vector3*)prop->GetValue();
        for (int i = 0; i < count; i++)
            EA::ArgScript::SprintfAppend(out, "\n   (%g, %g, %g) ",
                                         (double)values[i].x, (double)values[i].y, (double)values[i].z);
        break;
    }
    case 0x80000032: {
        int count = prop->GetItemCount();
        const Vector3* values = (const Vector3*)prop->GetValue();
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
        const Transform* values = (const Transform*)prop->GetValue();
        for (int i = 0; i < count; i++) {
            Vector3 offset = values[i].mOffset;
            Vector3 euler = GetEulerAngles(values[i].mRotation);
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

}  // namespace

// Out-of-namespace caller so the anonymous-namespace function is emitted.
void GetVariantValueDescription_Emit(Property* prop, eastl::string* out)
{
    GetVariantValueDescription(prop, out);
}
