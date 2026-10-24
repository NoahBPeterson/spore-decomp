// 0x013329c0 ($E225): dynamic initializer of the Simulator::cCommodityNode serializer attribute table
// (15 Simulator::Attribute records, 0x3c bytes each, at 0x01570a60..0x01570dE3), plus the writes
// of the class's static default values (0x0168d181..0x0168d1a4) interleaved between the records.
//
// Same record layout and construction as the cMission table (s0133ba60): every record is built in one
// reused 0x3c-byte stack temp and copied (rep movsd) into the table. Some records carry a set-default
// callback (+0x1c) in the 0x00bfe310.. family (one per field, each a tiny function outside this slice).
// Members per the ModAPI cCommodityNode layout (1D0h mResourcePoints .. 22Ch mBuyPercent).
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

class cVehicle;
struct HitSphere;
struct GonzagoTimer;

// Per-type instances of the shared serializer callbacks. The linker folds the retail template
// instances to one address each, but the compiler saw them as distinct symbols; a suffix per
// instance keeps them distinct here too. "s" = the instance several neighbouring rows share (those are
// the constants the retail code keeps in registers); "rN" = an instance used by row N only.
#define DECL_FAMILY(S) \
    void WriteText_00694fc0_##S(char* pBuffer, void* pData);                 /* 0x00694fc0 */ \
    bool Write_00572840_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00572840 */ \
    void ReadText_006930b0_##S(const string8& text, void* pData);            /* 0x006930b0 */ \
    void ReadText_00693090_##S(const string8& text, void* pData);            /* 0x00693090 */ \
    bool Write_00ac88f0_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00ac88f0 */ \
    void ReadText_00692ff0_##S(const string8& text, void* pData);            /* 0x00692ff0 */ \
    bool Read_00572810_##S(ISerializerReadStream* pStream, void* pData);     /* 0x00572810 */ \
    void WriteText_00694f00_##S(char* pBuffer, void* pData);                 /* 0x00694f00 */ \
    bool Validate_00b1fbf0_##S();                                            /* 0x00b1fbf0 */ \
    bool ToXml_00675ca0_##S(void* pData, const char* pName, int depth);      /* 0x00675ca0 */ \
    bool ToXml_00acbb80_##S(void* pData, const char* pName, int depth);      /* 0x00acbb80 */
DECL_FAMILY(s)
DECL_FAMILY(r0) DECL_FAMILY(r1) DECL_FAMILY(r2) DECL_FAMILY(r3) DECL_FAMILY(r4)
DECL_FAMILY(r5) DECL_FAMILY(r6) DECL_FAMILY(r7) DECL_FAMILY(r8) DECL_FAMILY(r9)
DECL_FAMILY(r10) DECL_FAMILY(r11) DECL_FAMILY(r12) DECL_FAMILY(r13) DECL_FAMILY(r14)

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00bd0cb0(ISerializerReadStream* pStream, void* pData);
bool Read_00bfeca0(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);

bool Validate_00ae3310();
bool Validate_00b6f550();

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);

// Per-field set-default callbacks (0x00bfe310 .. 0x00bfe430, 0x20 bytes apart).
void SetDefault_00bfe310(Attribute*);
void SetDefault_00bfe330(Attribute*);
void SetDefault_00bfe350(Attribute*);
void SetDefault_00bfe370(Attribute*);
void SetDefault_00bfe390(Attribute*);
void SetDefault_00bfe3b0(Attribute*);
void SetDefault_00bfe3d0(Attribute*);
void SetDefault_00bfe3f0(Attribute*);
void SetDefault_00bfe410(Attribute*);
void SetDefault_00bfe430(Attribute*);

// Free-function callbacks of the cCommunity / cSPCreatureAnimal attribute tables.
bool Read_00c01ce0(ISerializerReadStream* pStream, void* pData);      // 0x00c01ce0
bool Write_00c006a0(ISerializerWriteStream* pStream, void* pData);    // 0x00c006a0
bool Validate_00c00740();                                             // 0x00c00740
bool ToXml_00c51440(void* pData, const char* pName, int depth);       // 0x00c51440
bool Read_00c024f0(ISerializerReadStream* pStream, void* pData);      // 0x00c024f0
bool Write_00c00780(ISerializerWriteStream* pStream, void* pData);    // 0x00c00780
bool Validate_00c00810();                                             // 0x00c00810
bool ToXml_00f29650(void* pData, const char* pName, int depth);       // 0x00f29650
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);      // 0x00ac87c0
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);    // 0x00ac87f0
void ReadText_00694c80(const string8& text, void* pData);             // 0x00694c80
void WriteText_00694c10(char* pBuffer, void* pData);                  // 0x00694c10
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);       // 0x00acbbc0
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);      // 0x00b02540
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);      // 0x00ae3430
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);    // 0x00ae3450
void ReadText_00693150(const string8& text, void* pData);             // 0x00693150
void WriteText_00695080(char* pBuffer, void* pData);                  // 0x00695080
bool ToXml_00ae5720(void* pData, const char* pName, int depth);       // 0x00ae5720
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);      // 0x00b20540
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);      // 0x00b6e3a0
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);    // 0x00ac88c0
bool Read_00bd0d50(ISerializerReadStream* pStream, void* pData);      // 0x00bd0d50
bool Write_00bd17b0(ISerializerWriteStream* pStream, void* pData);    // 0x00bd17b0
bool Validate_00bcd450();                                             // 0x00bcd450

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cCommodityNode_sAttributes[15];   // 0x01570a60
extern AttrSlot cCommunity_sAttributes[6];        // 0x015710b8
extern AttrSlot cSPCreatureAnimal_sAttributes[13]; // 0x01571370

// Static default values of the class (written between the records).
extern uint8_t  cCommodityNode_sDefault_0168d181;   // 0x0168d181
extern uint32_t cCommodityNode_sDefault_0168d184;   // 0x0168d184
extern uint32_t cCommodityNode_sDefault_0168d188;   // 0x0168d188
extern int      cCommodityNode_sDefault_0168d18c;   // 0x0168d18c
extern int      cCommodityNode_sDefault_0168d190;   // 0x0168d190
extern int      cCommodityNode_sDefault_0168d194;   // 0x0168d194
extern int      cCommodityNode_sDefault_0168d198;   // 0x0168d198
extern float    cCommodityNode_sDefault_0168d19c;   // 0x0168d19c
extern float    cCommodityNode_sDefault_0168d1a0;   // 0x0168d1a0
extern float    cCommodityNode_sDefault_0168d1a4;   // 0x0168d1a4

// FLOAT_ATTR(R, W, RT, WT, V, TX): suffix per callback.
#define FLOAT_ATTR(R, W, RT, WT, V, TX) Read_00572810_##R, Write_00ac88f0_##W, ReadText_006930b0_##RT, \
    WriteText_00694fc0_##WT, Validate_00b1fbf0_##V, ToXml_00acbb80_##TX
#define UINT_ATTR(R, W, RT, V, TX) Read_00572810_##R, Write_00572840_##W, ReadText_00693090_##RT, \
    WriteText_00694f00_##R, Validate_00b1fbf0_##V, ToXml_00675ca0_##TX
#define INT_ATTR(S) Read_00572810_##S, Write_00572840_##S, ReadText_00692ff0_##S, WriteText_00694ee0, \
    Validate_00b1fbf0_##S, ToXml_0057cde0
#define BOOL_ATTR(S) Read_00ac8750, Write_00ac8780, ReadText_00693090_##S, WriteText_00694fa0, Validate_00b1fbf0_##S, ToXml_0057ce00
#define PTR_ATTR(R, W, V)  R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCommodityNode_sAttributes[IDX] = a; }
#define ADD_TO(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }

// @ 0x013329c0
void InitCommodityNodeAttributes()
{
    ADD(0,  "mResourcePoints", 0x0403e5f1, 0x1d0, FLOAT_ATTR(r0, s, s, r0, r0, r0))
    ADD(1,  "mMaxResourcePoints", 0x0403e5f2, 0x1d4, FLOAT_ATTR(r1, s, s, r1, r1, r1))
    ADD(2,  "mpHitSphere", 0x0403e5f3, 0x1d8, PTR_ATTR(Read_00bd0cb0, Write_00bca960, Validate_00b6f550))
    ADD(3,  "mbMineInitialized", 0x0521d43e, 0x1e4, BOOL_ATTR(r3), SetDefault_00bfe310)
    cCommodityNode_sDefault_0168d181 = 0;
    ADD(4,  "mMineState", 0x0521d43f, 0x1ec, INT_ATTR(r4), SetDefault_00bfe330)
    ADD(5,  "mMineStateTimer", 0x0521d440, 0x1f0, PTR_ATTR(Read_00ae3470, Write_00ae3490, Validate_00ae3310))
    ADD(6,  "mMineStateTimeout", 0x0521d441, 0x210, UINT_ATTR(r6, r6, r6, s, s), SetDefault_00bfe350)
    ADD(7,  "mConstructingPoliticalID", 0x0521d442, 0x214, UINT_ATTR(r7, r7, r7, s, s), SetDefault_00bfe370)
    ADD(8,  "mCapturePoliticalID", 0x0521d443, 0x218, UINT_ATTR(r8, r8, r8, s, s), SetDefault_00bfe390)
    cCommodityNode_sDefault_0168d184 = 0;
    cCommodityNode_sDefault_0168d188 = 0;
    cCommodityNode_sDefault_0168d18c = -1;
    cCommodityNode_sDefault_0168d190 = -1;
    ADD(9,  "mConvertPoliticalID", 0x0521d444, 0x21c, UINT_ATTR(r9, r9, r9, s, s), SetDefault_00bfe3b0)
    ADD(10, "mBuyPoliticalID", 0x0521d445, 0x220, UINT_ATTR(r10, r10, r10, s, s), SetDefault_00bfe3d0)
    ADD(11, "mCapturePercent", 0x0521d446, 0x224, FLOAT_ATTR(s, r11, r11, s, r11, r11), SetDefault_00bfe3f0)
    ADD(12, "mConvertPercent", 0x0521d447, 0x228, FLOAT_ATTR(s, r12, r12, s, r12, r12), SetDefault_00bfe410)
    cCommodityNode_sDefault_0168d194 = -1;
    cCommodityNode_sDefault_0168d198 = -1;
    cCommodityNode_sDefault_0168d19c = 0.0f;
    cCommodityNode_sDefault_0168d1a0 = 0.0f;
    ADD(13, "mBuyPercent", 0x0521d448, 0x22c, FLOAT_ATTR(s, r13, r13, s, r13, r13), SetDefault_00bfe430)
    ADD(14, "mConstructingVehicle", 0x05776f58, 0x1e0, PTR_ATTR(Read_00bfeca0, Write_00bca960, Validate_00b6f550))
    cCommodityNode_sDefault_0168d1a4 = 0.0f;
}

// @ 0x013342f0
void InitCommunityAttributes()
{
    ADD_TO(cCommunity_sAttributes, 0, "mCommunitySize", 0x03223734, 0x38,
           Read_00572810_s, Write_00572840_s, ReadText_00692ff0_s, WriteText_00694ee0,
           Validate_00b1fbf0_s, ToXml_0057cde0)
    ADD_TO(cCommunity_sAttributes, 1, "mAssemblyBubbles", 0x03223735, 0x70,
           Read_00c01ce0, Write_00c006a0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00c00740, ToXml_00c51440)
    ADD_TO(cCommunity_sAttributes, 2, "mLanes", 0x03223736, 0x84,
           Read_00c024f0, Write_00c00780, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00c00810, ToXml_00f29650)
    ADD_TO(cCommunity_sAttributes, 3, "mName", 0x042c8cee, 0xf8,
           Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
           Validate_00b1fbf0_s, ToXml_00acbbc0)
    ADD_TO(cCommunity_sAttributes, 4, "mDescription", 0x042e213c, 0x108,
           Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
           Validate_00b1fbf0_s, ToXml_00acbbc0)
    ADD_TO(cCommunity_sAttributes, 5, "mpLeader", 0x04bd34fb, 0x11c,
           Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b6f550, ToXml_00ac8050)
}

// @ 0x01334790
void InitSPCreatureAnimalAttributes()
{
    ADD_TO(cSPCreatureAnimal_sAttributes, 0, "mPlayerAlertState", 0xd2708c85, 0x101c,
           Read_00572810_r0, Write_00572840_r0, ReadText_00692ff0_r0, WriteText_00694ee0,
           Validate_00b1fbf0_r0, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 1, "mNextSpecies", 0x03f6565d, 0x1004,
           Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
           Validate_00b1fbf0_r1, ToXml_00ae5720)
    ADD_TO(cSPCreatureAnimal_sAttributes, 2, "mHerd", 0x72ae9fe0, 0x1674,
           Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b6f550, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 3, "mNoDamageTimer", 0x05c02449, 0xfc0,
           Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00ae3310, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 4, "mLastAvatarDamageTimer", 0x05ee740c, 0xfe0,
           Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00ae3310, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 5, "mPregnantEggs", 0x52709079, 0x1678,
           Read_00572810_r5, Write_00572840_r5, ReadText_00692ff0_r5, WriteText_00694ee0,
           Validate_00b1fbf0_r5, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 6, "mUntargetDistanceTime", 0x021d2388, 0x167c,
           Read_00572810_r6, Write_00ac88f0_r6, ReadText_006930b0_r6, WriteText_00694fc0_r6,
           Validate_00b1fbf0_r6, ToXml_00acbb80_r6)
    ADD_TO(cSPCreatureAnimal_sAttributes, 7, "mOwnerMissionID", 0x92709161, 0x1680,
           Read_00572810_r7, Write_00572840_r7, ReadText_00693090_r7, WriteText_00694f00_r7,
           Validate_00b1fbf0_r7, ToXml_00675ca0_r7)
    ADD_TO(cSPCreatureAnimal_sAttributes, 8, "mPersonality", 0x72709236, 0x1684,
           Read_00572810_r8, Write_00572840_r8, ReadText_00692ff0_r8, WriteText_00694ee0,
           Validate_00b1fbf0_r8, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 9, "mColor", 0x042a2b01, 0x1010,
           Read_00b6e3a0, Write_00ac88c0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b1fbf0_r9, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 10, "mCharmDamage", 0x0666441b, 0x1694,
           Read_00572810_r10, Write_00ac88f0_r10, ReadText_006930b0_r10, WriteText_00694fc0_r10,
           Validate_00b1fbf0_r10, ToXml_00acbb80_r10)
    ADD_TO(cSPCreatureAnimal_sAttributes, 11, "mCharmTime", 0x06664451, 0x169c,
           Read_00572810_r11, Write_00ac88f0_r11, ReadText_006930b0_r11, WriteText_00694fc0_r11,
           Validate_00b1fbf0_r11, ToXml_00acbb80_r11)
    ADD_TO(cSPCreatureAnimal_sAttributes, 12, "mpCharmer", 0x06664454, 0x1698,
           Read_00bd0d50, Write_00bd17b0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00bcd450, ToXml_00ac8050)
}

}  // namespace Simulator
