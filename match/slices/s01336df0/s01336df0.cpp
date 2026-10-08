// @ 0x01336df0  $E259: dynamic initializer of the SP::cEmpire serializer attribute
// table (19 Simulator::Attribute records, 0x3c bytes each, at 0x01572b60..0x01572fd3).
//
// Same record layout as the cHerd / cCivilization / cPlayer tables (see s0134d380, s01330060,
// s01350ca0): name, id, member offset, three uninitialized fields, pCurrentObject (+0x18),
// set-default callback (+0x1c, null for every record here), the DefaultOffset function and
// the read/write/text/validate/xml callbacks. Each record is built in a 0x3c-byte stack temp
// and rep-movsd copied into the table. Row data read off the retail initializer; callbacks
// live outside this slice and are declared by address.
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

// Read functions
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);  // 0x00ac87c0
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);  // 0x00aff840
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);  // 0x00b02540
bool Read_00c143c0(ISerializerReadStream* pStream, void* pData);  // 0x00c143c0
bool Read_00c1b8c0(ISerializerReadStream* pStream, void* pData);  // 0x00c1b8c0
bool Read_00c21260(ISerializerReadStream* pStream, void* pData);  // 0x00c21260
bool Read_00c7e9f0(ISerializerReadStream* pStream, void* pData);  // 0x00c7e9f0

// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac87f0
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);  // 0x00aff870
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
bool Write_00c0fba0(ISerializerWriteStream* pStream, void* pData);  // 0x00c0fba0
bool Write_00c143e0(ISerializerWriteStream* pStream, void* pData);  // 0x00c143e0
bool Write_00c15f60(ISerializerWriteStream* pStream, void* pData);  // 0x00c15f60
bool Write_00cd44e0(ISerializerWriteStream* pStream, void* pData);  // 0x00cd44e0

// ReadText functions
void ReadText_00692fd0(const string8& text, void* pData);  // 0x00692fd0
void ReadText_00692ff0(const string8& text, void* pData);  // 0x00692ff0
void ReadText_00693090(const string8& text, void* pData);  // 0x00693090
void ReadText_006930b0(const string8& text, void* pData);  // 0x006930b0
void ReadText_00693150(const string8& text, void* pData);  // 0x00693150
void ReadText_00694c80(const string8& text, void* pData);  // 0x00694c80
void ReadText_00c2e4e0(const string8& text, void* pData);  // 0x00c2e4e0

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
void WriteText_00694c10(char* pBuffer, void* pData);  // 0x00694c10
void WriteText_00694ec0(char* pBuffer, void* pData);  // 0x00694ec0
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080

// Validate functions
bool Validate_00ae3310();  // 0x00ae3310
bool Validate_00b1fbf0();  // 0x00b1fbf0
bool Validate_00b6f550();  // 0x00b6f550
bool Validate_00c0fc10();  // 0x00c0fc10

// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
bool ToXml_00595a70(void* pData, const char* pName, int depth);  // 0x00595a70
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);  // 0x00acbbc0
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
bool ToXml_00c19b60(void* pData, const char* pName, int depth);  // 0x00c19b60
bool ToXml_00ca8710(void* pData, const char* pName, int depth);  // 0x00ca8710

bool Read_00bb9cd0(ISerializerReadStream* pStream, void* pData);
bool Read_00bf26b0(ISerializerReadStream* pStream, void* pData);
bool Read_00c31c80(ISerializerReadStream* pStream, void* pData);
bool Read_00bf1c70(ISerializerReadStream* pStream, void* pData);
bool Read_00c34750(ISerializerReadStream* pStream, void* pData);
bool Read_00badf20(ISerializerReadStream* pStream, void* pData);
bool Read_00c33820(ISerializerReadStream* pStream, void* pData);
bool Write_00bb9d00(ISerializerWriteStream* pStream, void* pData);
bool Write_00c32a40(ISerializerWriteStream* pStream, void* pData);
bool Write_00bf1cb0(ISerializerWriteStream* pStream, void* pData);
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
bool Write_00c332a0(ISerializerWriteStream* pStream, void* pData);
void ReadText_00693070(const string8& text, void* pData);
void WriteText_00694f80(char* pBuffer, void* pData);
bool Validate_00b6f860();
bool Validate_00befb00();
bool Validate_00c31ca0();
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00eafcf0(void* pData, const char* pName, int depth);
bool ToXml_00595a50(void* pData, const char* pName, int depth);

struct AttrStorage { char data[sizeof(Attribute)]; };
AttrStorage cEmpire_sAttributes[19];   // 0x01572b60

// @ 0x01336df0
void InitEmpireAttributes()
{
    {
        Attribute a("mEmpireName", 0x03477139, 0x3c,
                  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
                  Validate_00b1fbf0, ToXml_00acbbc0);
        *(Attribute*)&cEmpire_sAttributes[0] = a;
    }
    {
        Attribute a("mEmpireMoney", 0x021e6db7, 0xd0,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[1] = a;
    }
    {
        Attribute a("mTravelDistance", 0x051e6db7, 0xd4,
                  Read_00bb9cd0, Write_00bb9d00, ReadText_00693070, WriteText_00694f80,
                  Validate_00b1fbf0, ToXml_00595a50);
        *(Attribute*)&cEmpire_sAttributes[2] = a;
    }
    {
        Attribute a("mTrait", 0x03477338, 0x54,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[3] = a;
    }
    {
        Attribute a("mArchetype", 0x0554279e, 0x58,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cEmpire_sAttributes[4] = a;
    }
    {
        Attribute a("mCurrentGameMode", 0x0362ab2e, 0x4c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[5] = a;
    }
    {
        Attribute a("mUFOKey", 0x03ab8a62, 0xb8,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cEmpire_sAttributes[6] = a;
    }
    {
        Attribute a("mCaptainKey", 0x07f55dbf, 0xc4,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cEmpire_sAttributes[7] = a;
    }
    {
        Attribute a("mHomePlanet", 0x021e6dbb, 0xb4,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[8] = a;
    }
    {
        Attribute a("mHomeStar", 0x021e6dba, 0xb0,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[9] = a;
    }
    {
        Attribute a("mPoliticalID", 0x021e6dbc, 0x84,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cEmpire_sAttributes[10] = a;
    }
    {
        Attribute a("mCityMusic", 0x042a0f35, 0x104,
                  Read_00bf26b0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[11] = a;
    }
    {
        Attribute a("mFlags", 0x035d5a51, 0x50,
                  Read_00c31c80, Write_00c32a40, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[12] = a;
    }
    {
        Attribute a("mCultureSet", 0x05624e2e, 0x108,
                  Read_00bf1c70, Write_00bf1cb0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00befb00, ToXml_00ac8050);
        *(Attribute*)&cEmpire_sAttributes[13] = a;
    }
    {
        Attribute a("mEnemies", 0x03477390, 0x5c,
                  Read_00c34750, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[14] = a;
    }
    {
        Attribute a("mAllies", 0x03868491, 0x70,
                  Read_00c34750, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[15] = a;
    }
    {
        Attribute a("mStars", 0x03868492, 0x88,
                  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[16] = a;
    }
    {
        Attribute a("mNextStarTowardsHome", 0x03868493, 0x9c,
                  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cEmpire_sAttributes[17] = a;
    }
    {
        Attribute a("mAdventureList", 0x07995682, 0x148,
                  Read_00c33820, Write_00c332a0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c31ca0, ToXml_00eafcf0);
        *(Attribute*)&cEmpire_sAttributes[18] = a;
    }
}

}  // namespace Simulator
