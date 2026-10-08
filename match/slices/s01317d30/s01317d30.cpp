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

}  // namespace Simulator
