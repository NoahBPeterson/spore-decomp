// 0x01315a50 ($E240): dynamic initializer of the Simulator::cCommEvent serializer attribute table
// (16 Simulator::Attribute records, 0x3c bytes each, at 0x01566db0..0x0156716f). Member names and
// offsets agree with ModAPI cCommEvent.h (mEventType at 0xc, mSource 0x18, mpMission 0x40, ...).
//
// Same record layout and construction as the cMission table (s0133ba60) and the cGameDataUFO /
// cVehicle / cTribe / cPlayer tables: name, id, member offset, three uninitialized fields,
// pCurrentObject (+0x18) = 0, set-default callback (+0x1c) = 0, the offset function (0x00692ca0)
// and the read/write/readText/writeText/validate/toXml callbacks. Every record is built in one
// reused 0x3c-byte stack temp and copied (rep movsd) into the table. Row data read off the retail
// initializer; the callbacks live outside this slice and are declared by address (per-type template
// instances folded by the linker are declared as templates, as in s013388f0).
//
// Which callback constants cl keeps in ebx/ebp across the records depends on symbol identity: the
// int rows share Write4<int> and ReadText_00692ff0, the first unsigned rows are fully per-type, and
// the last two unsigned rows (mDuration, mElapsedTime) share Write4<uint32_t> / ReadTextInt<uint32_t>
// (UINT2_ATTR). Every other callback is a per-type template instance (the linker later folds them).
// Both initializers (this one and $E419 below) build each record in one reused 0x3c-byte stack temp
// and rep-movsd it into the table. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.

#include "types.h"
#include <new>

namespace eastl { struct string8; }
typedef eastl::string8 string8;

namespace Simulator {

class ISerializerReadStream;
class ISerializerWriteStream;
struct Attribute;

typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
typedef void  (*ReadTextFunction_t)(const string8&, void*);
typedef void  (*WriteTextFunction_t)(char*, void*);
typedef bool  (*ValidateFunction_t)();
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(Attribute*);
typedef void  (*SetDefaultFunction_t)(Attribute*);

void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)

struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    // Record with a default value: the store of the default (static or GetDefaultValue<T>()) is part
    // of the record's construction and sits just before the offset store.
    template<typename Store>
    __forceinline Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, const Store& storeDefault)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        storeDefault();
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};

struct ResourceKey;
class cCity;
class cCivilization;
class cMission;
class cGameDataCommList;
struct DynamicResponseList;   // eastl::vector<int> mDynamicResponses
// Tags for the unsigned-int rows: their per-type callbacks are distinct template instances.
struct Int_mEventType;
struct Int_mFileID;
struct Int_mDialogID;
struct Int_mPriority;
struct UInt_mSource;
struct UInt_mTarget;
struct UInt_mPlanetKey;
struct UInt_mDuration;
struct UInt_mElapsedTime;

// Per-type template instances (folded by the linker to one address each).
// 0x00572810: 4-byte raw read
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
// 0x00572840: 4-byte integer write
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
// 0x00693090: ReadTextInt<T> for unsigned integers and bool
template<typename T> void ReadTextInt(const string8& text, void* pData);
// 0x00b1fbf0: AlwaysValid<T> (return true) for every plain-value type
template<typename T> bool AlwaysValid();
// 0x00694ee0 / 0x0057cde0: text writer and xml writer of the int rows (per-type instances)
template<typename T> void WriteTextInt(char* pBuffer, void* pData);
template<typename T> void WriteTextUInt(char* pBuffer, void* pData);
template<typename T> bool ToXmlInt(void* pData, const char* pName, int depth);
// 0x00675ca0: ToXml for the unsigned-int rows
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae97b0(ISerializerReadStream* pStream, void* pData);
bool Read_00ae9e00(ISerializerReadStream* pStream, void* pData);
bool Read_00ae9e30(ISerializerReadStream* pStream, void* pData);
bool Read_00aeba50(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae9e60(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);

bool Validate_00ae9ed0();
bool Validate_00b6f550();

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00aeacc0(void* pData, const char* pName, int depth);   // SerializeList

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cCommEvent_sAttributes[16];   // 0x01566db0

#define UINT_ATTR(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteTextUInt<T>, AlwaysValid<T>, ToXmlUInt<T>
#define UINT2_ATTR(T) Read4<T>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteTextUInt<T>, AlwaysValid<T>, ToXmlUInt<T>
#define INT_ATTR(T) Read4<T>, Write4<int>, ReadText_00692ff0, WriteTextInt<T>, AlwaysValid<T>, ToXmlInt<T>
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define PTR_ATTR(T, R, W, V)  /* T: pointee, for reading only */ R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050
#define LIST_ATTR  Read_00aeba50, Write_00ae9e60, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae9ed0, ToXml_00aeacc0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCommEvent_sAttributes[IDX] = a; }

// @ 0x01315a50
void InitCommEventAttributes()
{
    ADD(0,  "mEventType", 0x0444b325, 0xc, INT_ATTR(Int_mEventType))
    ADD(1,  "mSource", 0x04407904, 0x18, UINT_ATTR(UInt_mSource))
    ADD(2,  "mTarget", 0x04407905, 0x1c, UINT_ATTR(UInt_mTarget))
    ADD(3,  "mPlanetKey", 0x037add3d, 0x34, UINT_ATTR(UInt_mPlanetKey))
    ADD(4,  "mFileID", 0x037add3e, 0x38, INT_ATTR(Int_mFileID))
    ADD(5,  "mDialogID", 0x037add3f, 0x3c, INT_ATTR(Int_mDialogID))
    ADD(6,  "mpMission", 0x037add40, 0x40, PTR_ATTR(cMission, Read_00ae97b0, Write_00bca960, Validate_00b6f550))
    ADD(7,  "mPriority", 0x037add41, 0x44, INT_ATTR(Int_mPriority))
    ADD(8,  "mpTargetCity", 0x037add43, 0x24, PTR_ATTR(cCity, Read_00ae9e00, Write_00bca960, Validate_00b6f550))
    ADD(9,  "mpSourceCity", 0x037add44, 0x20, PTR_ATTR(cCity, Read_00ae9e00, Write_00bca960, Validate_00b6f550))
    ADD(10, "mpTargetCivilization", 0x037add45, 0x2c, PTR_ATTR(cCivilization, Read_00ae9e30, Write_00bca960, Validate_00b6f550))
    ADD(11, "mpSourceCivilization", 0x037add46, 0x28, PTR_ATTR(cCivilization, Read_00ae9e30, Write_00bca960, Validate_00b6f550))
    ADD(12, "mbVisibleInGalaxy", 0x037add47, 0x30, BOOL_ATTR)
    ADD(13, "mDynamicResponses", 0x037add42, 0x50, LIST_ATTR)
    ADD(14, "mDuration", 0x037add48, 0x48, UINT2_ATTR(UInt_mDuration))
    ADD(15, "mElapsedTime", 0x037add49, 0x4c, UINT2_ATTR(UInt_mElapsedTime))
}


// ---------------------------------------------------------------------------------------------
// 0x01317720 ($E419): dynamic initializer of another serializer attribute table (11 records at
// 0x0167b578, the cGameDataPlant-style object table: transform, fruit, sequence ids, size bracket,
// interacting object, species key, radii, height, removed flag), plus its "field_name" sentinel record.
// Every record has a set-default callback; the statics those callbacks read back (0x0167bab8..
// 0x0167bae8, a function-local static smart pointer at 0x0167bb38 and the static transform behind
// GetDefaultValue<cSPTransform>) are written inside the record constructions.
// ---------------------------------------------------------------------------------------------
struct Vector3 { float x, y, z; Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {} };
struct Matrix3 {
    float m[3][3];
    Matrix3& Assign(const Matrix3& other);        // 0x0041cb40
};
extern const Vector3 kDefaultOffset;              // 0x0167af5c (this module's zero vector)
extern const Matrix3 kDefaultRotation;            // 0x0167b554 (this module's identity)

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;
    cSPTransform() : mFlags(0), mModificationCount(0), mOffset(kDefaultOffset), mScale(1.0f)
    {
        mRotation.Assign(kDefaultRotation);
    }
    cSPTransform& operator=(const cSPTransform& other);   // 0x00537dc0
};
cSPTransform& GetDefaultTransform();              // 0x00b024a0 (SP::GetDefaultValue<cSPTransform;90607414>)

struct ResourceKeyValue {
    uint32_t instance, type, group;
    ResourceKeyValue() : instance(0), type(0), group(0) {}
};
struct IRefObject {
    virtual void AddRef();
    virtual void Release();
};
template<typename T> struct SmartPtr {
    T* mp;
    SmartPtr() : mp(0) {}
    ~SmartPtr() { if (mp) mp->Release(); }
    SmartPtr& operator=(T* p)
    {
        if (p != mp) {
            T* pOld = mp;
            mp = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};
// Function-local statics behind GetDefaultValue<T>() for the non-POD defaults.
__forceinline ResourceKeyValue& GetDefaultKey() { static ResourceKeyValue key; return key; }
__forceinline SmartPtr<IRefObject>& GetDefaultObject() { static SmartPtr<IRefObject> object; return object; }

// Default stores (one small functor per default kind)
struct StoreTransform { const cSPTransform& v; StoreTransform(const cSPTransform& x) : v(x) {} void operator()() const { GetDefaultTransform() = v; } };
struct StoreU64 { uint64_t* p; uint64_t v; StoreU64(uint64_t* a, uint64_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
struct StoreU32 { uint32_t* p; uint32_t v; StoreU32(uint32_t* a, uint32_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
struct StoreFloat { float* p; float v; StoreFloat(float* a, float b) : p(a), v(b) {} void operator()() const { *p = v; } };
struct StoreByte { uint8_t* p; uint8_t v; StoreByte(uint8_t* a, uint8_t b) : p(a), v(b) {} void operator()() const { *p = v; } };
struct StoreNullObject { StoreNullObject(int) {} void operator()() const { GetDefaultObject() = 0; } };
struct StoreNullKey { StoreNullKey(int) {} void operator()() const { GetDefaultKey() = ResourceKeyValue(); } };

extern uint64_t sFruitDefault;        // 0x0167bab8
extern uint32_t sSeqIdDefault;        // 0x0167bac0
extern uint32_t sSeqIndexDefault;     // 0x0167bac4
extern uint32_t sSizeBracketDefault;  // 0x0167bac8
extern float sBaseRadiusDefault;      // 0x0167badc
extern float sCanopyRadiusDefault;    // 0x0167bae0
extern float sHeightDefault;          // 0x0167bae4
extern uint8_t sRemovedDefault;       // 0x0167bae8

void SetDefault_00b02520(Attribute* pAttr);
void SetDefault_00aff8b0(Attribute* pAttr);
void SetDefault_00aff8d0(Attribute* pAttr);
void SetDefault_00aff8f0(Attribute* pAttr);
void SetDefault_00aff910(Attribute* pAttr);
void SetDefault_00b002e0(Attribute* pAttr);
void SetDefault_00aff930(Attribute* pAttr);
void SetDefault_00aff980(Attribute* pAttr);
void SetDefault_00aff9a0(Attribute* pAttr);
void SetDefault_00aff9c0(Attribute* pAttr);
void SetDefault_00aff9e0(Attribute* pAttr);

bool Read_00aff7e0(ISerializerReadStream* pStream, void* pData);
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);
bool Write_00aff810(ISerializerWriteStream* pStream, void* pData);
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
void ReadText_00692fd0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void WriteText_00694ec0(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
bool ToXml_00595a70(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);

struct Tag_mTransform;
struct Tag_mFruit;
struct Tag_mSeq;
struct Tag_mKey;

extern AttrSlot cPlant_sAttributes[12];   // 0x0167b578

#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define SHORT_ATTR(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteTextUInt<T>, AlwaysValid<Tag_mSeq>, ToXmlUInt<Tag_mSeq>

#define ADD2(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cPlant_sAttributes[IDX] = a; }

// @ 0x01317720
void InitPlantAttributes()
{
    cSPTransform defaultTransform;
    ADD2(0,  "mTransform", 0x05668f36, 0xc, Read_00aff7e0, Write_00aff810, ReadText_00c2e4e0, WriteText_00692fb0,
              AlwaysValid<Tag_mTransform>, ToXml_00ac8050, SetDefault_00b02520, StoreTransform(defaultTransform))
    ADD2(1,  "mFruit", 0x05668f38, 0x48, Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
              AlwaysValid<Tag_mFruit>, ToXml_00595a70, SetDefault_00aff8b0, StoreU64(&sFruitDefault, 0))
    ADD2(2,  "mSeqId", 0x05810db9, 0x50, SHORT_ATTR(UInt_mSource), SetDefault_00aff8d0, StoreU32(&sSeqIdDefault, 0))
    ADD2(3,  "mSeqIndex", 0x05810dba, 0x54, SHORT_ATTR(UInt_mTarget), SetDefault_00aff8f0, StoreU32(&sSeqIndexDefault, 0))
    ADD2(4,  "mSizeBracket", 0x05810dbb, 0x58, SHORT_ATTR(UInt_mPlanetKey), SetDefault_00aff910,
              StoreU32(&sSizeBracketDefault, 0x6d60a1cc))
    ADD2(5,  "mpWhoIsInteractingWithMe", 0x05810dbc, 0x68, Read_00b02540, Write_00bca960, ReadText_00c2e4e0,
              WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, SetDefault_00b002e0, StoreNullObject(0))
    ADD2(6,  "mSpeciesKey", 0x05810dbe, 0x5c, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
              AlwaysValid<Tag_mKey>, ToXml_00ae5720, SetDefault_00aff930, StoreNullKey(0))
    ADD2(7,  "mBaseRadius", 0x05810dbf, 0x6c, FLOAT_ATTR, SetDefault_00aff980, StoreFloat(&sBaseRadiusDefault, 0.0f))
    ADD2(8,  "mCanopyRadius", 0x0595fd21, 0x70, FLOAT_ATTR, SetDefault_00aff9a0, StoreFloat(&sCanopyRadiusDefault, 0.0f))
    ADD2(9,  "mHeight", 0x0595fdff, 0x74, FLOAT_ATTR, SetDefault_00aff9c0, StoreFloat(&sHeightDefault, 0.0f))
    ADD2(10, "mbRemoved", 0x06abf15d, 0x7c, BOOL_ATTR, SetDefault_00aff9e0, StoreByte(&sRemovedDefault, 0))
    // "field_name" sentinel: a static record (id -1, no callbacks) built in place at table slot 11.
    new (&cPlant_sAttributes[11]) Attribute("field_name", 0xffffffff, (void*)0, 0, 0, 0, 0, 0);
}

}  // namespace Simulator
