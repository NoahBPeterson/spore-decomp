// @ 0x01350ca0  $E587: dynamic initializer of the Simulator::cPlayer serializer attribute table
// (37 Simulator::Attribute records, 0x3c bytes each, at 0x01578d18..0x015795c3).
//
// Same record layout as the cHerd / cCivilization tables (see s0134d380, s01330060): name, id,
// member offset, three uninitialized fields, pCurrentObject (+0x18), set-default callback (+0x1c),
// the DefaultOffset function and the read/write/text/validate/xml callbacks. Each record is built
// in a 0x3c-byte stack temp and rep-movsd copied into the table. One record carries a default:
// mTotalTimeInCVG, whose set-default callback (0x00c75a80) copies the static int at 0x01694560,
// which this initializer sets to INT_MAX (0x7fffffff). Row data read off the retail initializer;
// callbacks live outside this slice and are declared by address.
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

// Default value read back by SetDefault_00c75a80 (*DefaultOffset(pAttr) = sTotalTimeInCVGDefault).
extern int sTotalTimeInCVGDefault;   // 0x01694560

// SetDefault functions
void SetDefault_00c75a80(Attribute* pAttr);  // 0x00c75a80

// Read functions
bool Read_00572810(ISerializerReadStream* pStream, void* pData);
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00b04e00(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Read_00ba8250(ISerializerReadStream* pStream, void* pData);
bool Read_00c777e0(ISerializerReadStream* pStream, void* pData);
bool Read_00c78020(ISerializerReadStream* pStream, void* pData);
bool Read_00c78130(ISerializerReadStream* pStream, void* pData);
bool Read_00c78d50(ISerializerReadStream* pStream, void* pData);
bool Read_00c7a970(ISerializerReadStream* pStream, void* pData);
bool Read_00c7aef0(ISerializerReadStream* pStream, void* pData);
bool Read_00c7b120(ISerializerReadStream* pStream, void* pData);
bool Read_00c7b240(ISerializerReadStream* pStream, void* pData);
bool Read_00c7c530(ISerializerReadStream* pStream, void* pData);
bool Read_00c7c9b0(ISerializerReadStream* pStream, void* pData);

// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
bool Write_00675790(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac9f70(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00c75e70(ISerializerWriteStream* pStream, void* pData);
bool Write_00c75f10(ISerializerWriteStream* pStream, void* pData);
bool Write_00c76010(ISerializerWriteStream* pStream, void* pData);
bool Write_00c76100(ISerializerWriteStream* pStream, void* pData);
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00c76c70(ISerializerWriteStream* pStream, void* pData);
bool Write_00c76d60(ISerializerWriteStream* pStream, void* pData);
bool Write_00c77890(ISerializerWriteStream* pStream, void* pData);

// ReadText functions
void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_00693090(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

// Validate functions
bool Validate_00675850();
bool Validate_00ae3310();
bool Validate_00b1fbf0();
bool Validate_00b6f550();
bool Validate_00c760c0();
bool Validate_00c76170();
bool Validate_00c76d10();
bool Validate_00c76e10();
bool Validate_00cd6630();
bool Validate_00d011e0();

// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
bool ToXml_00c51440(void* pData, const char* pName, int depth);
bool ToXml_00c788d0(void* pData, const char* pName, int depth);
bool ToXml_00c78a50(void* pData, const char* pName, int depth);
bool ToXml_00c78bd0(void* pData, const char* pName, int depth);
bool ToXml_00c78ea0(void* pData, const char* pName, int depth);
bool ToXml_00c78ff0(void* pData, const char* pName, int depth);
bool ToXml_00c79140(void* pData, const char* pName, int depth);
bool ToXml_00d022e0(void* pData, const char* pName, int depth);
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
bool ToXml_01011db0(void* pData, const char* pName, int depth);

struct AttrStorage { char data[sizeof(Attribute)]; };
AttrStorage cPlayer_sAttributes[37];   // 0x01578d18

// @ 0x01350ca0
void InitPlayerAttributes()
{
    {
        Attribute a("mGameEventRecord", 0x03b1e966, 0x111c,
                  Read_00c777e0, Write_00675790, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00675850, ToXml_00c788d0);
        *(Attribute*)&cPlayer_sAttributes[0] = a;
    }
    {
        Attribute a("mpCRGItems", 0x03a3a4b4, 0x10e8,
                  Read_00ba8250, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cPlayer_sAttributes[1] = a;
    }
    {
        Attribute a("mFlags", 0x03a8d5ca, 0x698,
                  Read_00c78020, Write_00ac9f70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00cd6630, ToXml_00c78a50);
        *(Attribute*)&cPlayer_sAttributes[2] = a;
    }
    {
        Attribute a("mOneTimeEventFlags", 0x044f3d49, 0x38,
                  Read_00c78130, Write_00c76c70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76d10, ToXml_00c78bd0);
        *(Attribute*)&cPlayer_sAttributes[3] = a;
    }
    {
        Attribute a("mSelectedCityHallKey", 0x047696c3, 0x1150,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[4] = a;
    }
    {
        Attribute a("mSelectedVehicleKey", 0x064e5ca6, 0x115c,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[5] = a;
    }
    {
        Attribute a("mSelectedUFOKey", 0x047696e9, 0x1168,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[6] = a;
    }
    {
        Attribute a("mCapitalCityPos", 0x047696ec, 0x1178,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0);
        *(Attribute*)&cPlayer_sAttributes[7] = a;
    }
    {
        Attribute a("mHasCheated", 0x04bc7c77, 0x11f0,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cPlayer_sAttributes[8] = a;
    }
    {
        Attribute a("mCurrentGoalProgress", 0x055a9786, 0x10f0,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[9] = a;
    }
    {
        Attribute a("mGoalProgressTotal", 0x055a97a7, 0x10f4,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[10] = a;
    }
    {
        Attribute a("mThemeID", 0x058b5e0e, 0x1244,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cPlayer_sAttributes[11] = a;
    }
    {
        Attribute a("mMaxPosseSize", 0x05d2ac6b, 0x124c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[12] = a;
    }
    {
        Attribute a("mTempPosseCount", 0x066e3237, 0x1250,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[13] = a;
    }
    {
        Attribute a("mUniqueGameID", 0x05ee017b, 0x10f8,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cPlayer_sAttributes[14] = a;
    }
    {
        Attribute a("mDifficultyLevel", 0x058b5e0f, 0x1248,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[15] = a;
    }
    {
        Attribute a("mStarsVisited", 0x047696ea, 0x1184,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[16] = a;
    }
    {
        Attribute a("mStarsKnown", 0x047696eb, 0x1198,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[17] = a;
    }
    {
        Attribute a("mWormholesUsed", 0x0674b0b0, 0x11ac,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[18] = a;
    }
    {
        Attribute a("mSpacePlayerWarData", 0x05626f25, 0x11f8,
                  Read_00c7aef0, Write_00c76d60, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76e10, ToXml_00d022e0);
        *(Attribute*)&cPlayer_sAttributes[19] = a;
    }
    {
        Attribute a("mPlayerCaptureProgressStars", 0x057a1100, 0x1214,
                  Read_00c7b120, Write_00c75e70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_01011db0);
        *(Attribute*)&cPlayer_sAttributes[20] = a;
    }
    {
        Attribute a("mEmbassies", 0x0580dbb7, 0x1228,
                  Read_00c78d50, Write_00c75f10, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00d011e0, ToXml_00baa2b0);
        *(Attribute*)&cPlayer_sAttributes[21] = a;
    }
    {
        Attribute a("mPlanetData", 0x0580dbbf, 0x11c0,
                  Read_00c7c9b0, Write_00c76010, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c760c0, ToXml_00c78ea0);
        *(Attribute*)&cPlayer_sAttributes[22] = a;
    }
    {
        Attribute a("mSoothingSongTimer", 0x0600bacf, 0x1258,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cPlayer_sAttributes[23] = a;
    }
    {
        Attribute a("mSocialTraitProgress", 0x06132c98, 0x1278,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[24] = a;
    }
    {
        Attribute a("mCombatTraitProgress", 0x06132ca7, 0x127c,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[25] = a;
    }
    {
        Attribute a("mPirateUFOModelKey", 0x062fdfef, 0x1280,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[26] = a;
    }
    {
        Attribute a("mSelectionGroups", 0x064909c8, 0x113c,
                  Read_00c7c530, Write_00c76100, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76170, ToXml_00c51440);
        *(Attribute*)&cPlayer_sAttributes[27] = a;
    }
    {
        Attribute a("mCellConsequenceTrait", 0x0679fb51, 0x10fc,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[28] = a;
    }
    {
        Attribute a("mCreatureConsequenceTrait", 0x0679fb52, 0x1100,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[29] = a;
    }
    {
        Attribute a("mTribeConsequenceTrait", 0x0679fb53, 0x1104,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[30] = a;
    }
    {
        Attribute a("mCivConsequenceTrait", 0x0679fb54, 0x1108,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[31] = a;
    }
    {
        Attribute a("mSpaceConsequenceTrait", 0x0679fb55, 0x110c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[32] = a;
    }
    {
        Attribute a("mInitCaptainKey", 0x07be547b, 0x1290,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[33] = a;
    }
    {
        Attribute a("mPlayerSpecificEmpireData", 0x0679fb56, 0x11d8,
                  Read_00c7b240, Write_00c77890, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c78ff0);
        *(Attribute*)&cPlayer_sAttributes[34] = a;
    }
    {
        sTotalTimeInCVGDefault = 0x7fffffff;
        Attribute a("mTotalTimeInCVG", 0x06cfb746, 0x128c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0,
                  SetDefault_00c75a80);
        *(Attribute*)&cPlayer_sAttributes[35] = a;
    }
    {
        Attribute a("mAdventuresCompleted", 0x07673918, 0x129c,
                  Read_00c7a970, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c79140);
        *(Attribute*)&cPlayer_sAttributes[36] = a;
    }
}

}  // namespace Simulator
