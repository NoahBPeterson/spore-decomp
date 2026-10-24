// 0x01317d30 ($E423): dynamic initializer of a Simulator serializer attribute table
// (17 Simulator::Attribute records, 0x3c bytes each, at 0x01567428..0x015677e8+0x3c): mPosition,
// mRadius, mSeqId, the three mMax*TreeFruit counts, mDropRate, mRegrowRate, three species keys,
// three tree lists and the three Deprecated_*Trees lists (a vegetation / fruit-tree spawner class).
//
// Same record layout and construction as the cCommodityNode / cMission tables (s013329c0, s0133ba60):
// every record is built in one reused 0x3c-byte stack temp and copied (rep movsd) into the table.
// Between the records the retail code also initializes class statics: function-local default
// values (the guarded ones, each with its own one-byte flag at +0xc after the 12-byte value) and
// unguarded plain statics. The callbacks live outside this slice and are declared by address.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.

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

    // Record with a default value: the store of the default (GetDefaultValue<T>()) is part of the
    // record's construction and sits just before the offset store.
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


struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cTreeSpawner_sAttributes[17];   // 0x01567428

// Callbacks (all outside this slice), by address.
bool Read_00b6e3a0(ISerializerReadStream*, void*);   // Vector3
bool Read_00572810(ISerializerReadStream*, void*);   // raw 4 bytes
bool Read_00ae3430(ISerializerReadStream*, void*);   // ResourceKey
bool Read_00b04d20(ISerializerReadStream*, void*);
bool Read_00b0a310(ISerializerReadStream*, void*);
bool Write_00ac88c0(ISerializerWriteStream*, void*);
bool Write_00572840(ISerializerWriteStream*, void*);
bool Write_00ac88f0(ISerializerWriteStream*, void*);
bool Write_00ae3450(ISerializerWriteStream*, void*);
bool Write_00aca730(ISerializerWriteStream*, void*);
bool Write_00b00390(ISerializerWriteStream*, void*);
void ReadText_006930f0(const string8&, void*);
void ReadText_006930b0(const string8&, void*);
void ReadText_00693090(const string8&, void*);
void ReadText_00692ff0(const string8&, void*);
void ReadText_00693150(const string8&, void*);
void ReadText_00c2e4e0(const string8&, void*);
void WriteText_00695010(char*, void*);
void WriteText_00694fc0(char*, void*);
void WriteText_00694f00(char*, void*);
void WriteText_00694ee0(char*, void*);
void WriteText_00695080(char*, void*);
void WriteText_00692fb0(char*, void*);
bool Validate_00b1fbf0();
bool Validate_00b6f860();
bool Validate_00b00400();
bool ToXml_00acbba0(void*, const char*, int);
bool ToXml_00acbb80(void*, const char*, int);
bool ToXml_00675ca0(void*, const char*, int);
bool ToXml_0057cde0(void*, const char*, int);
bool ToXml_00ae5720(void*, const char*, int);
bool ToXml_00c6c390(void*, const char*, int);
bool ToXml_00b03fd0(void*, const char*, int);

// Per-field set-default callbacks.
void SetDefault_00b00350(Attribute*);   // mPosition
void SetDefault_00affa00(Attribute*);
void SetDefault_00affa20(Attribute*);
void SetDefault_00affa40(Attribute*);
void SetDefault_00affa60(Attribute*);
void SetDefault_00affa80(Attribute*);
void SetDefault_00affaa0(Attribute*);
void SetDefault_00affac0(Attribute*);
void SetDefault_00affae0(Attribute*);
void SetDefault_00affb30(Attribute*);
void SetDefault_00affb80(Attribute*);

// Class statics written between the records (unguarded).
extern float    sDefault_0167baec;
extern uint32_t sDefault_0167baf0;
extern uint32_t sDefault_0167baf4;
extern uint32_t sDefault_0167baf8;
extern uint32_t sDefault_0167bafc;
extern float    sDefault_0167bb00;
extern float    sDefault_0167bb04;
extern uint32_t sDefault_0167bb30;   // 4 bytes written after the third species key
extern uint32_t sDefault_0167bb10;
extern uint32_t sDefault_0167bb20;

// Guarded 12-byte function-local defaults: three zeroed ResourceKeys and one Vector3 copy.
struct Triple { uint32_t a, b, c; };
extern Triple gVec3Zero;   // 0x0167af5c
extern uint8_t  sFlag_0167bb4c; extern Triple sVec3_0167bb40;
extern uint8_t  sFlag_0167bb14; extern Triple sKey_0167bb08;
extern uint8_t  sFlag_0167bb24; extern Triple sKey_0167bb18;
extern uint8_t  sFlag_0167bb34; extern Triple sKey_0167bb28;

#define VEC3_ATTR  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, Validate_00b1fbf0, ToXml_00acbba0
#define FLOAT_ATTR Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Validate_00b1fbf0, ToXml_00acbb80
#define UINT_ATTR  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00, Validate_00b1fbf0, ToXml_00675ca0
#define INT_ATTR   Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, Validate_00b1fbf0, ToXml_0057cde0
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, Validate_00b1fbf0, ToXml_00ae5720
#define TREES_ATTR Read_00b04d20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
#define DEPR_ATTR  Read_00b0a310, Write_00b00390, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b00400, ToXml_00b03fd0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cTreeSpawner_sAttributes[IDX] = a; }

// @ 0x01317d30
void InitTreeSpawnerAttributes()
{
    if (!(sFlag_0167bb4c & 1)) sFlag_0167bb4c |= 1;
    sVec3_0167bb40.a = gVec3Zero.a;
    sVec3_0167bb40.b = gVec3Zero.b;
    sVec3_0167bb40.c = gVec3Zero.c;
    ADD(0,  "mPosition", 0x056690e8, 0x0, VEC3_ATTR, SetDefault_00b00350)
    ADD(1,  "mRadius", 0x056690e9, 0xc, FLOAT_ATTR, SetDefault_00affa00)
    ADD(2,  "mSeqId", 0x056690ea, 0x10, UINT_ATTR, SetDefault_00affa20)
    ADD(3,  "mMaxLargeTreeFruit", 0x05669d6b, 0x14, INT_ATTR, SetDefault_00affa40)
    sDefault_0167baec = 0.0f;
    sDefault_0167baf0 = 0;
    sDefault_0167baf4 = 0;
    ADD(4,  "mMaxMediumTreeFruit", 0x05669d6c, 0x18, INT_ATTR, SetDefault_00affa60)
    sDefault_0167baf8 = 0;
    ADD(5,  "mMaxSmallTreeFruit", 0x05669d6d, 0x1c, INT_ATTR, SetDefault_00affa80)
    ADD(6,  "mDropRate", 0x06288473, 0x14c, FLOAT_ATTR, SetDefault_00affaa0)
    ADD(7,  "mRegrowRate", 0x06288a5e, 0x150, FLOAT_ATTR, SetDefault_00affac0)
    if (!(sFlag_0167bb14 & 1)) sFlag_0167bb14 |= 1;
    sDefault_0167bafc = 0;
    sDefault_0167bb00 = -1.0f;
    sDefault_0167bb04 = -1.0f;
    sKey_0167bb08.a = 0; sKey_0167bb08.b = 0;
    ADD(8,  "mLargeSpecies", 0x062d70cf, 0x20, KEY_ATTR, SetDefault_00affae0)
    sKey_0167bb08.c = 0;
    if (!(sFlag_0167bb24 & 1)) sFlag_0167bb24 |= 1;
    sKey_0167bb18.a = 0; sKey_0167bb18.b = 0;
    ADD(9,  "mMediumSpecies", 0x062d832b, 0x2c, KEY_ATTR, SetDefault_00affb30)
    sKey_0167bb18.c = 0;
    if (!(sFlag_0167bb34 & 1)) sFlag_0167bb34 |= 1;
    sKey_0167bb28.a = 0; sKey_0167bb28.b = 0;
    ADD(10, "mSmallSpecies", 0x062d70d8, 0x38, KEY_ATTR, SetDefault_00affb80)
    sKey_0167bb28.c = 0;
    ADD(11, "mLargeTrees", 0x06abf140, 0x44, TREES_ATTR)
    ADD(12, "mMediumTrees", 0x06abf141, 0x9c, TREES_ATTR)
    ADD(13, "mSmallTrees", 0x06abf142, 0xf4, TREES_ATTR)
    ADD(14, "mDeprecated_LargeTrees", 0x056690eb, 0x158, DEPR_ATTR)
    ADD(15, "mDeprecated_MediumTrees", 0x056690ec, 0x970, DEPR_ATTR)
    ADD(16, "mDeprecated_SmallTrees", 0x056690ed, 0x1188, DEPR_ATTR)
}

// ---------------------------------------------------------------------------------------------
// 0x013184d0 ($E245): dynamic initializer of a fruit / tree-spawner attribute table (8 records at
// 0x01567860: mFlags, mFruitIdx, mElapsedOnGroundTime, tree species / sequence ids, mState and the
// static sFruitCount). Same record layout and construction as InitTreeSpawnerAttributes above.
// ---------------------------------------------------------------------------------------------

bool Read_00b00430(ISerializerReadStream*, void*);
bool Read_00aff7e0(ISerializerReadStream*, void*);
bool Read_00b02540(ISerializerReadStream*, void*);
bool Read_00b06e10(ISerializerReadStream*, void*);
bool Read_00b04e00(ISerializerReadStream*, void*);
bool Write_00b02570(ISerializerWriteStream*, void*);
bool Write_00aff810(ISerializerWriteStream*, void*);
bool Write_00bca960(ISerializerWriteStream*, void*);
bool Write_00b00450(ISerializerWriteStream*, void*);
bool Write_00c761c0(ISerializerWriteStream*, void*);
bool Validate_00b6f550();
bool ToXml_00ac8050(void*, const char*, int);
bool ToXml_00f29b90(void*, const char*, int);
bool ToXml_00eafe40(void*, const char*, int);
void SetDefault_00b02610(Attribute*);

// The original table was built with one typed Attribute specialization per field, so callbacks that
// end up at the same address in retail are distinct template instances here unless they share a tag.
// Tags used by 013184d0:
struct Tag_mFlags;
struct Tag_mFruitIdx;
struct Tag_mElapsedOnGroundTime;
struct Tag_mTreeSpeciesBracket;
struct Tag_mTreeSeqID;
struct Tag_mTreeDistSequenceIdx;
struct Tag_mState;
struct Tag_sFruitCount;
struct Tag_ValidCommon;      // rows 1..7 and the static row share their validate symbol
// Tags used by 01318800:
struct Tag_mSeqID;
struct Tag_mSpeciesBracket2;
struct Tag_mDistSequenceIdx;
struct Tag_mSpeciesKey;
struct Tag_mTransform;
struct Tag_mFlags2;
struct Tag_mFruitTransforms;
struct Tag_mFruitDistEffectIdxs;
struct Tag_ValidSeq;         // mSeqID + mDistSequenceIdx share their validate symbol

template<typename T> bool Read4(ISerializerReadStream*, void*);
template<typename T> bool Write4(ISerializerWriteStream*, void*);
template<typename T> void ReadTextInt(const string8&, void*);
template<typename T> bool ToXmlUInt(void*, const char*, int);
template<typename T> bool ToXmlInt(void*, const char*, int);
template<typename T> bool AlwaysValid();

extern AttrSlot cTreeFruit_sAttributes[8];   // 0x01567860
extern AttrSlot cFruit_sAttributes[10];      // 0x0167b858

#define ADD_TF(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cTreeFruit_sAttributes[IDX] = a; }
#define ADD_FR(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cFruit_sAttributes[IDX] = a; }

#define UINT_ROW(T)   Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<Tag_ValidCommon>, ToXmlUInt<T>
#define INT_ROW(T)    Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694ee0, AlwaysValid<T>, ToXmlInt<T>
#define STATIC_ROW(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<Tag_ValidCommon>

// @ 0x013184d0
void InitTreeFruitAttributes()
{
    ADD_TF(0, "mFlags", 0x3fe7ec0, 0x148, Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFlags>, ToXml_00ac8050)
    ADD_TF(1, "mFruitIdx", 0x410d8c8, 0x164, UINT_ROW(Tag_mFruitIdx))
    ADD_TF(2, "mElapsedOnGroundTime", 0x410d8fe, 0x168, UINT_ROW(Tag_mElapsedOnGroundTime))
    ADD_TF(3, "mTreeSpeciesBracket", 0x67ddca4, 0x158, INT_ROW(Tag_mTreeSpeciesBracket))
    ADD_TF(4, "mTreeSeqID", 0x67ddca8, 0x15c, UINT_ROW(Tag_mTreeSeqID))
    ADD_TF(5, "mTreeDistSequenceIdx", 0x67ddcab, 0x160, UINT_ROW(Tag_mTreeDistSequenceIdx))
    ADD_TF(6, "mState", 0x420798f, 0x16c, INT_ROW(Tag_mState))
    ADD_TF(7, "sFruitCount", 0x410d9be, (void*)0x167af58, STATIC_ROW(Tag_sFruitCount))
}

// ---------------------------------------------------------------------------------------------
// 0x01318800 ($E250): dynamic initializer of the cFruit-style table (10 records at 0x0167b858:
// mSeqID, mSpeciesBracket, mDistSequenceIdx, mTransform (with a cSPTransform default), mFlags,
// mSpeciesKey, mpInteractingWith, mFruitTransforms, mFruitDistEffectIdxs and the "field_name"
// sentinel). Same construction as InitPlantAttributes in s01315a50.
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
cSPTransform& GetDefaultTransform();              // 0x00b02590 (SP::GetDefaultValue<cSPTransform;79537323>)

struct StoreTransform { const cSPTransform& v; StoreTransform(const cSPTransform& x) : v(x) {} void operator()() const { GetDefaultTransform() = v; } };

// @ 0x01318800
void InitFruitAttributes()
{
    ADD_FR(0, "mSeqID", 0x4bda4a8, 0x4c, Read4<Tag_mSeqID>, Write4<Tag_mSeqID>, ReadTextInt<Tag_mSeqID>, WriteText_00694f00, AlwaysValid<Tag_ValidSeq>, ToXml_00675ca0)
    ADD_FR(1, "mSpeciesBracket", 0x4bda4af, 0x50, Read4<Tag_mSpeciesBracket2>, Write4<Tag_mSpeciesBracket2>, ReadTextInt<Tag_mSpeciesBracket2>, WriteText_00694ee0, AlwaysValid<Tag_mSpeciesBracket2>, ToXml_0057cde0)
    ADD_FR(2, "mDistSequenceIdx", 0x4bda4aa, 0x54, Read4<Tag_mDistSequenceIdx>, Write4<Tag_mDistSequenceIdx>, ReadTextInt<Tag_mDistSequenceIdx>, WriteText_00694f00, AlwaysValid<Tag_ValidSeq>, ToXml_00675ca0)
    cSPTransform defaultTransform;
    ADD_FR(3, "mTransform", 0x4bda4ab, 0x58, Read_00aff7e0, Write_00aff810, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mTransform>, ToXml_00ac8050, SetDefault_00b02610, StoreTransform(defaultTransform))
    ADD_FR(4, "mFlags", 0x4bda4ac, 0x90, Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFlags2>, ToXml_00ac8050)
    ADD_FR(5, "mSpeciesKey", 0x4bda4ad, 0x94, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<Tag_mSpeciesKey>, ToXml_00ae5720)
    ADD_FR(6, "mpInteractingWith", 0x410d913, 0xa0, Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD_FR(7, "mFruitTransforms", 0x62073d2, 0xa4, Read_00b06e10, Write_00b00450, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFruitTransforms>, ToXml_00f29b90)
    ADD_FR(8, "mFruitDistEffectIdxs", 0x62073d8, 0x19c, Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<Tag_mFruitDistEffectIdxs>, ToXml_00eafe40)
    // "field_name" sentinel: a static record (id -1, no callbacks) built in place at table slot 9.
    new (&cFruit_sAttributes[9]) Attribute("field_name", 0xffffffff, (void*)0, 0, 0, 0, 0, 0);
}

}  // namespace Simulator
