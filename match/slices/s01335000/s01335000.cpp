// @ 0x01335000  $E259: dynamic initializer of the Simulator::cCreatureBase serializer attribute
// table (35 Simulator::Attribute records, 0x3c bytes each, at 0x01571798..0x01571fcb).
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

struct AttrStorage { char data[sizeof(Attribute)]; };
AttrStorage cCreatureBase_sAttributes[35];   // 0x01571798

// @ 0x01335000
void InitCreatureBaseAttributes()
{
    {
        Attribute a("mbTeleport", 0x02415ec6, 0xb5d,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[0] = a;
    }
    {
        Attribute a("mbDead", 0x02415ebc, 0xb5e,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[1] = a;
    }
    {
        Attribute a("mbUpdateInteractionEffect", 0x02415ebd, 0xb60,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[2] = a;
    }
    {
        Attribute a("mbUpdateMotiveEffect", 0x02415ebe, 0xb61,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[3] = a;
    }
    {
        Attribute a("mbIsDiseased", 0x0303fb98, 0xb62,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[4] = a;
    }
    {
        Attribute a("mLastInteractionEffect", 0x021d1baa, 0xcc4,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[5] = a;
    }
    {
        Attribute a("mLastMotiveState", 0x021d1bab, 0xcc0,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[6] = a;
    }
    {
        Attribute a("mSpeciesKey", 0x03f64a78, 0xb28,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cCreatureBase_sAttributes[7] = a;
    }
    {
        Attribute a("mProfileSeq", 0x02415ec8, 0xb24,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[8] = a;
    }
    {
        Attribute a("mAge", 0x52773f6f, 0xb34,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[9] = a;
    }
    {
        Attribute a("mbCasted", 0x024cd902, 0xb67,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[10] = a;
    }
    {
        Attribute a("mpWhoIsInteractingWithMe", 0xb2774021, 0xb50,
                  Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[11] = a;
    }
    {
        Attribute a("mbStealthed", 0x06948b64, 0xbb1,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[12] = a;
    }
    {
        Attribute a("mCurrentLoudness", 0xd277405a, 0xb80,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[13] = a;
    }
    {
        Attribute a("mFoodValue", 0x021d1ba5, 0xb84,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[14] = a;
    }
    {
        Attribute a("mbHasBeenEaten", 0x72774074, 0xb5f,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[15] = a;
    }
    {
        Attribute a("mStrengthRating", 0x021d1bac, 0xb88,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[16] = a;
    }
    {
        Attribute a("mSpeedState", 0x02415eca, 0xf98,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[17] = a;
    }
    {
        Attribute a("mCreatureName", 0x03d97b19, 0xb38,
                  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
                  Validate_00b1fbf0, ToXml_00acbbc0);
        *(Attribute*)&cCreatureBase_sAttributes[18] = a;
    }
    {
        Attribute a("mCurrentAttackIdx", 0x021d239f, 0xe8c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[19] = a;
    }
    {
        Attribute a("mCurrentAttackAnimId", 0x0547c1bf, 0xe90,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[20] = a;
    }
    {
        Attribute a("mbColorIsIdentity", 0x042a2b0e, 0xb65,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[21] = a;
    }
    {
        Attribute a("mHunger", 0x05501f64, 0xbbc,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[22] = a;
    }
    {
        Attribute a("mHungerDelta", 0x05501f65, 0xbb8,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[23] = a;
    }
    {
        Attribute a("mHungerDelayTimer", 0x04653b60, 0xb90,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[24] = a;
    }
    {
        Attribute a("mArchetype", 0x33ace6b5, 0xe80,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[25] = a;
    }
    {
        Attribute a("mGeneralFlags", 0x051b38ff, 0xb58,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[26] = a;
    }
    {
        Attribute a("mNoAttackTimer", 0x5242896a, 0xb78,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[27] = a;
    }
    {
        Attribute a("DEPRECATED_mRechargingAbilityBits", 0x0528933e, 0xc18,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[28] = a;
    }
    {
        Attribute a("DEPRECATED_mInUseAbilityBits", 0x0535a140, 0xc10,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[29] = a;
    }
    {
        Attribute a("mRechargingAbilityBits", 0x076c8f4d, 0xbf8,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[30] = a;
    }
    {
        Attribute a("mInUseAbilityBits", 0x076c8f46, 0xbec,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[31] = a;
    }
    {
        Attribute a("mIntentionTowardsTarget", 0x05675535, 0xb74,
                  Read_00c7e9f0, Write_00cd44e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, (ToXmlFunction_t)Validate_00b1fbf0);  // same stub in both slots
        *(Attribute*)&cCreatureBase_sAttributes[32] = a;
    }
    {
        Attribute a("mAbilityStates", 0x0521e608, 0xc28,
                  Read_00c1b8c0, Write_00c0fba0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ca8710);
        *(Attribute*)&cCreatureBase_sAttributes[33] = a;
    }
    {
        Attribute a("mItemInventory", 0x05ef360e, 0xe40,
                  Read_00c21260, Write_00c15f60, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c0fc10, ToXml_00c19b60);
        *(Attribute*)&cCreatureBase_sAttributes[34] = a;
    }
}

}  // namespace Simulator
