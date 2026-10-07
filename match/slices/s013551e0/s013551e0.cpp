// @ 0x013551e0  $E247: dynamic initializer of the Simulator::cTribe serializer attribute table
// (36 Simulator::Attribute records, 0x3c bytes each, at 0x0157ba68..0x0157c2d7).
//
// Same record layout as the cHerd / cPlayer / cCivilization tables (see s0134d380, s01350ca0,
// s01330060): name, id, member offset, three uninitialized fields, pCurrentObject (+0x18),
// set-default callback (+0x1c), the offset function and the read/write/text/validate/xml
// callbacks. The first 33 records describe cTribe members (offset function DefaultOffset,
// 0x00692ca0 = pCurrentObject + offset). The last three describe cTribe statics: their
// "offset" is the static's address, the offset function is 0x011874d0 (returns pAttr->offset)
// and they have no ToXml callback. Every record is built in one reused 0x3c-byte stack temp
// and copied (rep movsd) into the table, the way s0131ea90 spells it.
// Row data read off the retail initializer; callbacks live outside this slice and are
// declared by address.
// Flags: /O2 /MD /Gy /EHsc /TP.

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
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset

struct Attribute
{
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

// cTribe statics described by the last three records
extern char cTribe_sFishHotSpots[];   // 0x0157abb0
extern char cTribe_sFishTimer[];      // 0x016953f8
extern char cTribe_sFishEndTime[];    // 0x01695368

// Read functions
// 4-byte raw read: Read4<uint32_t> and Read4<float> fold to 0x00572810
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Read_00bed160(ISerializerReadStream* pStream, void* pData);
bool Read_00bf50f0(ISerializerReadStream* pStream, void* pData);
bool Read_00c41210(ISerializerReadStream* pStream, void* pData);
bool Read_00c92a00(ISerializerReadStream* pStream, void* pData);
bool Read_00c92a30(ISerializerReadStream* pStream, void* pData);
bool Read_00c92a60(ISerializerReadStream* pStream, void* pData);
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);
bool Read_00c95850(ISerializerReadStream* pStream, void* pData);
bool Read_00c9ab30(ISerializerReadStream* pStream, void* pData);
bool Read_00ce26c0(ISerializerReadStream* pStream, void* pData);

// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00c40e80(ISerializerWriteStream* pStream, void* pData);
bool Write_00c43790(ISerializerWriteStream* pStream, void* pData);
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
bool Write_00c92a90(ISerializerWriteStream* pStream, void* pData);

// ReadText functions
void ReadText_00692fd0(const string8& text, void* pData);
// ReadTextInt<bool> and ReadTextInt<uint32_t> fold to 0x00693090
template<typename T> void ReadTextInt(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694bd0(char* pBuffer, void* pData);
void WriteText_00694ec0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);

// Validate functions
bool Validate_00ae3310();
// AlwaysValid<T>: every instantiation folds to 0x00b1fbf0 (return true)
template<typename T> bool AlwaysValid();
bool Validate_00b6f550();
bool Validate_00b6f860();
bool Validate_00c9ad90();

// ToXml functions
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00c41b00(void* pData, const char* pName, int depth);
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);

struct Vector3;
struct ResourceKeyVector;
struct ForestList;

extern Attribute cTribe_sAttributes[36];   // 0x0157ba68

// Fills the reused record temp; the store order is the original's.
#define ATTR(NAME, ID, OFFSET, OFS, RD, WR, RT, WT, VAL, XML, IDX) \
    a.name = NAME; a.id = ID; a.pCurrentObject = 0; a.setDefaultFunction = 0; \
    a.offsetFunction = OFS; a.readFunction = RD; a.writeFunction = WR; \
    a.readTextFunction = RT; a.writeTextFunction = WT; a.validateFunction = VAL; \
    a.toXmlFunction = XML; a.offset = (uint32_t)(OFFSET); \
    cTribe_sAttributes[IDX] = a;

// @ 0x013551e0
void InitTribeAttributes()
{
    Attribute a;
    ATTR("mbMotiveCheatOn", 0x02fab837, 0x264, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 0)
    ATTR("mbRoboTribe", 0x02fab839, 0x334, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 1)
    ATTR("mbVisualized", 0x0510d72a, 0x33c, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 2)
    ATTR("mUpgradeLevel", 0x02fab83e, 0x32c, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 3)
    ATTR("mRoboPopulationCount", 0x02fab83f, 0x338, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 4)
    ATTR("mSpeciesKeys", 0x041171cc, 0x1904, DefaultOffset,
         Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ResourceKeyVector>, ToXml_00c6c4e0, 5)
    ATTR("mpHut", 0x02fab843, 0x368, DefaultOffset,
         Read_00c92a00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 6)
    ATTR("mTribeMembers", 0x02fab844, 0x340, DefaultOffset,
         Read_00ce26c0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 7)
    ATTR("mSelectableMembers", 0x02fab845, 0x354, DefaultOffset,
         Read_00bf50f0, Write_00c43790, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 8)
    ATTR("mTools", 0x02fab847, 0x36c, DefaultOffset,
         Read_00c95850, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 9)
    ATTR("mSocialTools", 0x34474cfa, 0x380, DefaultOffset,
         Read_00c95850, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390, 10)
    ATTR("mZoningRadius", 0x02fab849, 0x330, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 11)
    ATTR("mRSquareSize", 0x02fab854, 0x268, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 12)
    ATTR("mbCheckedForWater", 0x05107b10, 0x300, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 13)
    ATTR("mbCheckedForForests", 0x05108592, 0x301, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 14)
    ATTR("mClosestWater", 0x05107b15, 0x304, DefaultOffset,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 15)
    ATTR("mhFootprint", 0xc807312a, 0x19d4, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 16)
    ATTR("mpDomesticatedAnimalsHerd", 0x051cc74e, 0x19cc, DefaultOffset,
         Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 17)
    ATTR("mpDomesticatedAnimalsPen", 0x053d8e28, 0x19c4, DefaultOffset,
         Read_00bed160, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 18)
    ATTR("mpEggPen", 0x05b9a1a7, 0x19c8, DefaultOffset,
         Read_00bed160, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 19)
    ATTR("mEggPenFoodValue", 0x05b9a1ae, 0x2c0, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 20)
    ATTR("mpTotemPole", 0x055cef22, 0x19d0, DefaultOffset,
         Read_00c92a30, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 21)
    ATTR("mClosestForests", 0x051089f5, 0x314, DefaultOffset,
         Read_00c41210, Write_00c40e80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ForestList>, ToXml_00c41b00, 22)
    ATTR("mpFoodMat", 0x062daeed, 0x260, DefaultOffset,
         Read_00c92a60, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050, 23)
    ATTR("mTribeArchetype", 0x02fab853, 0x550, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 24)
    ATTR("mPopulationTimer", 0x056591e5, 0x510, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 25)
    ATTR("mTimer", 0x056591e6, 0x530, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 26)
    ATTR("mVignetteTimer", 0x056591e7, 0x270, DefaultOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050, 27)
    ATTR("mInitialRelationship", 0x05ecc770, 0x2c4, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 28)
    ATTR("mPurchasedTools", 0x06612ff8, 0x19d8, DefaultOffset,
         Read4<uint32_t>, Write_00572840, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0, 29)
    ATTR("mGoodyPopped", 0x0674d16a, 0x557, DefaultOffset,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 30)
    ATTR("mChieftainRespawnTimer", 0x0682e28e, 0x2c8, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 31)
    ATTR("mGiftRelationshipDecayTimer", 0x95701374, 0x2cc, DefaultOffset,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 32)
    ATTR("cTribe::sFishHotSpots", 0x06a7f44e, cTribe_sFishHotSpots, StaticOffset,
         Read_00c9ab30, Write_00c92a90, ReadText_00c2e4e0, WriteText_00694bd0, Validate_00c9ad90, 0, 33)
    ATTR("cTribe::sFishTimer", 0x06c250f5, cTribe_sFishTimer, StaticOffset,
         Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, 0, 34)
    ATTR("cTribe::sFishEndTime", 0x06c25111, cTribe_sFishEndTime, StaticOffset,
         Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0, AlwaysValid<int64_t>, 0, 35)
}

}  // namespace Simulator
