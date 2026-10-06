// @ 0x01330060  $E410: dynamic initializer of Simulator::cCivilization's serializer attribute
// table (57 Simulator::Attribute records, 0x3c bytes each, at 0x0156faa8..0x01570803).
//
// Layout and meaning of the record come from ModAPI Simulator/Serialization.h (struct
// Attribute, ASSERT_SIZE 0x3C): name, id, member offset, three fields the ctor leaves
// uninitialized (+0x0C..+0x14), pCurrentObject (+0x18), a set-default callback (+0x1C),
// the offset function (always DefaultOffset @ 0x00692ca0) and the read/write/text/validate/
// xml callbacks. Two attributes carry a default value held in a static (0x0168cb48 = 1,
// 0x0168cb4c = -1) that this initializer stores and the callbacks at 0x00befb20/0x00befb40
// copy into the member.
//
// The row data (names, ids, member offsets, callback addresses) was read off the retail
// initializer; the callbacks live outside this slice and are declared by address.
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

struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        offset = nOffset;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
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

// Stores the attribute's default value into its static and hands back the callback that
// copies that static into the member.
inline SetDefaultFunction_t InitDefault(int& var, int value, SetDefaultFunction_t pSetDefault)
{
    var = value;
    return pSetDefault;
}

extern int sVehicleTechLevelDefault;   // 0x0168cb48
extern int sCommRelPanelSlotDefault;   // 0x0168cb4c

// SetDefault functions
void SetDefault_00befb20(Attribute* pAttr);  // 0x00befb20
void SetDefault_00befb40(Attribute* pAttr);  // 0x00befb40
// Read functions
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);  // 0x00ac87c0
bool Read_00aca060(ISerializerReadStream* pStream, void* pData);  // 0x00aca060
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
bool Read_00ae9e00(ISerializerReadStream* pStream, void* pData);  // 0x00ae9e00
bool Read_00ae9e30(ISerializerReadStream* pStream, void* pData);  // 0x00ae9e30
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);  // 0x00b6e3a0
bool Read_00be0810(ISerializerReadStream* pStream, void* pData);  // 0x00be0810
bool Read_00bf1c70(ISerializerReadStream* pStream, void* pData);  // 0x00bf1c70
bool Read_00bf26b0(ISerializerReadStream* pStream, void* pData);  // 0x00bf26b0
bool Read_00bf26e0(ISerializerReadStream* pStream, void* pData);  // 0x00bf26e0
bool Read_00bf3ea0(ISerializerReadStream* pStream, void* pData);  // 0x00bf3ea0
bool Read_00bf3f80(ISerializerReadStream* pStream, void* pData);  // 0x00bf3f80
bool Read_00bf50f0(ISerializerReadStream* pStream, void* pData);  // 0x00bf50f0
bool Read_00bf77d0(ISerializerReadStream* pStream, void* pData);  // 0x00bf77d0
// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac87f0
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88c0
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);  // 0x00aca730
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
bool Write_00bf1cb0(ISerializerWriteStream* pStream, void* pData);  // 0x00bf1cb0
bool Write_00bf1cf0(ISerializerWriteStream* pStream, void* pData);  // 0x00bf1cf0
bool Write_00bf2ce0(ISerializerWriteStream* pStream, void* pData);  // 0x00bf2ce0
bool Write_00c43790(ISerializerWriteStream* pStream, void* pData);  // 0x00c43790
// ReadText functions
void ReadText_00692ff0(const string8& text, void* pData);  // 0x00692ff0
void ReadText_00693090(const string8& text, void* pData);  // 0x00693090
void ReadText_006930b0(const string8& text, void* pData);  // 0x006930b0
void ReadText_00693150(const string8& text, void* pData);  // 0x00693150
void ReadText_00694c80(const string8& text, void* pData);  // 0x00694c80
void ReadText_00c2e4e0(const string8& text, void* pData);  // 0x00c2e4e0
// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
void WriteText_00694c10(char* pBuffer, void* pData);  // 0x00694c10
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080
// Validate functions
bool Validate_00ae3310();  // 0x00ae3310
bool Validate_00b1fbf0();  // 0x00b1fbf0
bool Validate_00b6f550();  // 0x00b6f550
bool Validate_00b6f860();  // 0x00b6f860
bool Validate_00befb00();  // 0x00befb00
bool Validate_00bf1d50();  // 0x00bf1d50
bool Validate_00bf2670();  // 0x00bf2670
// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);  // 0x00acbbc0
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
bool ToXml_00c6c390(void* pData, const char* pName, int depth);  // 0x00c6c390
bool ToXml_00d02570(void* pData, const char* pName, int depth);  // 0x00d02570
bool ToXml_00f29650(void* pData, const char* pName, int depth);  // 0x00f29650

// 0x0156faa8
Attribute cCivilization_sAttributes[] = {
    Attribute("mCultureSet", 0x03acc625, 0x06c,
              Read_00bf1c70, Write_00bf1cb0, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00befb00, ToXml_00ac8050),
    Attribute("mInitialized", 0x023922cc, 0x088,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mIsPlayerOwned", 0x0417adaa, 0x089,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mIsNeutral", 0x045abb43, 0x08a,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mCommNotifiedFirstCityCapture", 0x046a8e8c, 0x08b,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mCommNotifiedWarning", 0x047645bf, 0x08c,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mHasDeveloped", 0x047fbc25, 0x08d,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mAttackedByMilitary", 0x047fbc26, 0x08e,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mAttackedByReligion", 0x047fbc27, 0x08f,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mSurrendered", 0x047fbc28, 0x090,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mTargetMinerals", 0x047fbc29, 0x092,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mFirstMinerals", 0x05500838, 0x093,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mFirstBudget", 0x05dfc2b8, 0x094,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mWealth", 0x023922cd, 0x098,
              Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
              Validate_00b1fbf0, ToXml_00acbb80),
    Attribute("mCities", 0x023922d0, 0x09c,
              Read_00bf3ea0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f860, ToXml_00c6c390),
    Attribute("mVehicles", 0x023922d2, 0x0b0,
              Read_00be0810, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f860, ToXml_00c6c390),
    Attribute("mPrimaryColor", 0x0417adeb, 0x0c4,
              Read_00b6e3a0, Write_00ac88c0, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b1fbf0, ToXml_00ac8050),
    Attribute("mCultureId", 0x0417adf0, 0x0d0,
              Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
              Validate_00b1fbf0, ToXml_00675ca0),
    Attribute("mSelectableObjectVector", 0x023922d3, 0x0d4,
              Read_00bf50f0, Write_00c43790, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f860, ToXml_00c6c390),
    Attribute("mSpeciesKey", 0x04d029e1, 0x268,
              Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
              Validate_00b1fbf0, ToXml_00ae5720),
    Attribute("mDistanceToCityMap", 0x023922d5, 0x410,
              Read_00bf3f80, Write_00bf2ce0, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00bf2670, ToXml_00d02570),
    Attribute("mCityMusic", 0x0424ea0e, 0x274,
              Read_00bf26b0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mName", 0x042e2195, 0x278,
              Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
              Validate_00b1fbf0, ToXml_00acbbc0),
    Attribute("mDescription", 0x042e219a, 0x288,
              Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
              Validate_00b1fbf0, ToXml_00acbbc0),
    Attribute("mVehicleTechLevel", 0x050a121d, 0x298,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0,
                InitDefault(sVehicleTechLevelDefault, 1, SetDefault_00befb20)),
    Attribute("mCommRelPanelSlot", 0x04d2fd10, 0x29c,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0,
                InitDefault(sCommRelPanelSlotDefault, -1, SetDefault_00befb40)),
    Attribute("mCurrentCommEventId", 0x0472a939, 0x2a0,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mpCurrentCommSource", 0x0472a93a, 0x2a4,
              Read_00aca060, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mpCurrentCommTargetCity", 0x0472a93b, 0x2a8,
              Read_00ae9e00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mHumanAttackTimer", 0x0589ec5f, 0x0e8,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mHumanProposeTimer", 0x042ca8cb, 0x108,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mProposeRouteTimer", 0x042ca8cc, 0x128,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mBuildMilitaryUnitsTimer", 0x050e1dc9, 0x148,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mBuildReligionUnitsTimer", 0x050e1dca, 0x168,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mBuildEconUnitsTimer", 0x042ca8cd, 0x188,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mExpansionMineralTimer", 0x051df47b, 0x1a8,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mClaimMineralTimer", 0x0552a010, 0x1c8,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mDemandTimer", 0x042ca8cf, 0x1e8,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mEmbargoTimer", 0x05ad8b2f, 0x208,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mAllianceTimer", 0x0508a5c4, 0x228,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mNemesisTimer", 0x0577663a, 0x248,
              Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00ae3310, ToXml_00ac8050),
    Attribute("mMilitaryExpansionCity", 0x050f3c3a, 0x458,
              Read_00ae9e00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mReligiousExpansionCity", 0x050f3c3b, 0x45c,
              Read_00ae9e00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mDiploAttackCity", 0x05ac6450, 0x460,
              Read_00ae9e00, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mExpansionMineral", 0x050f3c3c, 0x464,
              Read_00bf26e0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mClaimMineral", 0x050f3c3d, 0x468,
              Read_00bf26e0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mNemesisCiv", 0x057764e2, 0x46c,
              Read_00ae9e30, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00b6f550, ToXml_00ac8050),
    Attribute("mDomesticBudget", 0x05de699b, 0x4ac,
              Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
              Validate_00b1fbf0, ToXml_00acbb80),
    Attribute("mExpansionBudget", 0x05de69a0, 0x4b0,
              Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
              Validate_00b1fbf0, ToXml_00acbb80),
    Attribute("mUpdateMoneyCount", 0x05f8b65f, 0x4b4,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mForceMinDiploCount", 0x05fa08c5, 0x4b8,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mMilitaryCaptureCount", 0x065f7b0b, 0x4c0,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mReligiousCaptureCount", 0x065f7b0c, 0x4c4,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mEconomicCaptureCount", 0x065f7b0d, 0x4c8,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mbLauncedIWinWeapon", 0x0670bf56, 0x4cc,
              Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
              Validate_00b1fbf0, ToXml_0057ce00),
    Attribute("mHighestCityCount", 0x069489be, 0x4d0,
              Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
              Validate_00b1fbf0, ToXml_0057cde0),
    Attribute("mSuperweaponCooldown", 0x0643efbd, 0x490,
              Read_00bf77d0, Write_00bf1cf0, ReadText_00c2e4e0, WriteText_00692fb0,
              Validate_00bf1d50, ToXml_00f29650),
};

}  // namespace Simulator
