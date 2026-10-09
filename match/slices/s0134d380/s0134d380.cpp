// @ 0x0134d380  $E223: dynamic initializer of the herd/nest serializer attribute table
// (43 Simulator::Attribute records, 0x3c bytes each, at 0x01577bc8..0x015785db).
//
// Same record layout as the cCivilization table (see s01330060): name, id, member offset,
// three uninitialized fields, pCurrentObject (+0x18), set-default callback (+0x1c), the
// DefaultOffset function and the read/write/text/validate/xml callbacks. Two records carry
// a default: mInitialPosition (a function-local static vec3 {0,0,0} behind a guard bit at
// 0x01693e4c, storage 0x01693e40) and mDNAEvolutionThreshold (a static float at 0x01693e3c
// set to FLT_MAX). Row data read off the retail initializer; callbacks live outside this
// slice and are declared by address.
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

struct Vec3Default { float x, y, z; };
struct Vec3Static { float x, y, z; Vec3Static() {} };   // empty ctor: guard set, value assigned on every call

// Stores a default vec3 {0,0,0} into a guarded function-local static, returns the callback.
inline SetDefaultFunction_t InitDefaultVec3(SetDefaultFunction_t pSetDefault)
{
    static Vec3Default sDefault = { 0.0f, 0.0f, 0.0f };
    return pSetDefault;
}

extern float sDNAEvolutionThresholdDefault;   // 0x01693e3c
inline SetDefaultFunction_t InitDefaultFloat(float& var, float value, SetDefaultFunction_t pSetDefault)
{
    var = value;
    return pSetDefault;
}

// SetDefault functions
void SetDefault_00c6a0e0(Attribute* pAttr);  // 0x00c6a0e0
void SetDefault_00c6ae30(Attribute* pAttr);  // 0x00c6ae30

// Read functions
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
bool Read_00acdf10(ISerializerReadStream* pStream, void* pData);  // 0x00acdf10
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
bool Read_00b20510(ISerializerReadStream* pStream, void* pData);  // 0x00b20510
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);  // 0x00b6e3a0
bool Read_00c41210(ISerializerReadStream* pStream, void* pData);  // 0x00c41210
bool Read_00c6a080(ISerializerReadStream* pStream, void* pData);  // 0x00c6a080
bool Read_00c6bce0(ISerializerReadStream* pStream, void* pData);  // 0x00c6bce0
bool Read_00c6cd50(ISerializerReadStream* pStream, void* pData);  // 0x00c6cd50
bool Read_00c6ce30(ISerializerReadStream* pStream, void* pData);  // 0x00c6ce30
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);  // 0x00c95780

// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88c0
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);  // 0x00aca730
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
bool Write_00c40e80(ISerializerWriteStream* pStream, void* pData);  // 0x00c40e80
bool Write_00c46470(ISerializerWriteStream* pStream, void* pData);  // 0x00c46470
bool Write_00c6a0b0(ISerializerWriteStream* pStream, void* pData);  // 0x00c6a0b0
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);  // 0x00c6adc0

// ReadText functions
void ReadText_00692ff0(const string8& text, void* pData);  // 0x00692ff0
void ReadText_00693090(const string8& text, void* pData);  // 0x00693090
void ReadText_006930b0(const string8& text, void* pData);  // 0x006930b0
void ReadText_006930d0(const string8& text, void* pData);  // 0x006930d0
void ReadText_006930f0(const string8& text, void* pData);  // 0x006930f0
void ReadText_00693150(const string8& text, void* pData);  // 0x00693150
void ReadText_00c2e4e0(const string8& text, void* pData);  // 0x00c2e4e0

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
void WriteText_00694fe0(char* pBuffer, void* pData);  // 0x00694fe0
void WriteText_00695010(char* pBuffer, void* pData);  // 0x00695010
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080

// Validate functions
bool Validate_00ae3310();  // 0x00ae3310
bool Validate_00b1fbf0();  // 0x00b1fbf0
bool Validate_00b6f550();  // 0x00b6f550
bool Validate_00b6f860();  // 0x00b6f860

// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
bool ToXml_00acbba0(void* pData, const char* pName, int depth);  // 0x00acbba0
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
bool ToXml_00c41b00(void* pData, const char* pName, int depth);  // 0x00c41b00
bool ToXml_00c6c0f0(void* pData, const char* pName, int depth);  // 0x00c6c0f0
bool ToXml_00c6c390(void* pData, const char* pName, int depth);  // 0x00c6c390
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);  // 0x00c6c4e0
bool ToXml_00c6c630(void* pData, const char* pName, int depth);  // 0x00c6c630

// 0x01577bc8
struct AttrStorage { char data[sizeof(Attribute)]; };
AttrStorage cHerd_sAttributes[43];   // 0x01577bc8

// @ 0x0134d380
void InitHerdAttributes()
{
    {
        Attribute a("mHerd", 0x021e6db2, 0x040,
                  Read_00acdf10, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cHerd_sAttributes[0] = a;
    }
    {
        Attribute a("mEggs", 0x52689e83, 0x054,
                  Read_00c6cd50, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cHerd_sAttributes[1] = a;
    }
    {
        Attribute a("mOwnedByAvatar", 0x021e6dae, 0x084,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[2] = a;
    }
    {
        Attribute a("mArchetype", 0x030bbb5d, 0x088,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[3] = a;
    }
    {
        Attribute a("mArchetypeGroup", 0x04894af5, 0x08c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[4] = a;
    }
    {
        Attribute a("mScheduleIndex", 0x04ea45ca, 0x090,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[5] = a;
    }
    {
        Attribute a("mOwnerSpeciesKey", 0x03f64453, 0x098,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cHerd_sAttributes[6] = a;
    }
    {
        Attribute a("mGeneration", 0x039a2b58, 0x0f0,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[7] = a;
    }
    {
        Attribute a("mEvolvedSpeciesProfileKeys", 0x9493bd27, 0x0a8,
                  Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c6c4e0);
        *(Attribute*)&cHerd_sAttributes[8] = a;
    }
    {
        Attribute a("mInitialShortfall", 0x03fe8d35, 0x0f8,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[9] = a;
    }
    {
        Attribute a("mScaleMultiplier", 0x03fe8d8b, 0x150,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[10] = a;
    }
    {
        Attribute a("mHitpointOverride", 0x03fe8e9c, 0x154,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[11] = a;
    }
    {
        Attribute a("mDamageMultiplier", 0x03fe8eb3, 0x158,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[12] = a;
    }
    {
        Attribute a("mTargetHerdSize", 0x021e6db0, 0x0f4,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[13] = a;
    }
    {
        Attribute a("mbEggStatusChanged", 0x021e6dad, 0x0fc,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[14] = a;
    }
    {
        Attribute a("mNumGuards", 0x12689e6f, 0x100,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[15] = a;
    }
    {
        Attribute a("mRespawnRate", 0x0320d9e2, 0x11c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[16] = a;
    }
    {
        Attribute a("mCreaturePersonality", 0x52ae4e7b, 0x15c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[17] = a;
    }
    {
        Attribute a("mpNest", 0xd2aa6604, 0x160,
                  Read_00c6bce0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[18] = a;
    }
    {
        Attribute a("mpEggLayer", 0x12ae4eca, 0x194,
                  Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[19] = a;
    }
    {
        Attribute a("mpHerdMom", 0x73d72126, 0x164,
                  Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[20] = a;
    }
    {
        Attribute a("mbEggsInNest", 0x021e6db1, 0x198,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[21] = a;
    }
    {
        Attribute a("mValidLocations", 0x32689ec8, 0x1e0,
                  Read_00c6ce30, Write_00c46470, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c6c630);
        *(Attribute*)&cHerd_sAttributes[22] = a;
    }
    {
        Attribute a("mbEnabled", 0xd2ae8fdc, 0x218,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[23] = a;
    }
    {
        Attribute a("mTerritoryRadius", 0x0403e2b1, 0x108,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[24] = a;
    }
    {
        Attribute a("mActivateBrainLevel", 0x0403e2b2, 0x120,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[25] = a;
    }
    {
        Attribute a("mDeactivateBrainLevel", 0x0403e2b3, 0x124,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[26] = a;
    }
    {
        Attribute a("mbCheckedForWateringHole", 0x04cfbbf9, 0x208,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[27] = a;
    }
    {
        Attribute a("mWateringHolePosition", 0x041fa3ba, 0x20c,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0);
        *(Attribute*)&cHerd_sAttributes[28] = a;
    }
    {
        Attribute a("mbCheckedForForests", 0x04cfcaee, 0x07c,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[29] = a;
    }
    {
        Attribute a("mCurrentFeedingGrounds", 0x04cfe14e, 0x080,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[30] = a;
    }
    {
        Attribute a("mChangeFeedingGroundsTimer", 0x04cfe1f5, 0x1c0,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[31] = a;
    }
    {
        Attribute a("mFeedingGrounds", 0x04cfcaf6, 0x068,
                  Read_00c41210, Write_00c40e80, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c41b00);
        *(Attribute*)&cHerd_sAttributes[32] = a;
    }
    {
        Attribute a("mNumGuardLocations", 0x04447955, 0x10c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[33] = a;
    }
    {
        Attribute a("mNumGuardsPerLocation", 0x04447959, 0x110,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[34] = a;
    }
    {
        Attribute a("mGuardMinMaxRadius", 0x04447971, 0x114,
                  Read_00c6a080, Write_00c6a0b0, ReadText_006930d0, WriteText_00694fe0,
                  Validate_00b1fbf0, ToXml_00c6c0f0);
        *(Attribute*)&cHerd_sAttributes[35] = a;
    }
    {
        Attribute a("mEggIndex", 0x1368374c, 0x12c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[36] = a;
    }
    {
        Vec3Default tmp = { 0.0f, 0.0f, 0.0f };
        static Vec3Static sDefault;   // 0x01693e40, guard bit 0x01693e4c
        sDefault.x = tmp.x;
        sDefault.y = tmp.y;
        sDefault.z = tmp.z;
        Attribute a("mInitialPosition", 0x1368374d, 0x034,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0,
                  SetDefault_00c6ae30);
        *(Attribute*)&cHerd_sAttributes[37] = a;
    }
    {
        sDNAEvolutionThresholdDefault = 3.402823466e+38f;
        Attribute a("mDNAEvolutionThreshold", 0x0517a7b0, 0x094,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80,
                  SetDefault_00c6a0e0);
        *(Attribute*)&cHerd_sAttributes[38] = a;
    }
    {
        Attribute a("mbShouldEvolve", 0x0517ad97, 0x085,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[39] = a;
    }
    {
        Attribute a("mbBestFriends", 0x342dfbf3, 0x191,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[40] = a;
    }
    {
        Attribute a("mbExtinction", 0xf42dfbf4, 0x190,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[41] = a;
    }
    {
        Attribute a("mbTransientHerd", 0x05c82085, 0x192,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[42] = a;
    }
}

}  // namespace Simulator
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
