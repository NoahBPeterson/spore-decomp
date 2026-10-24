// @ 0x01322a30  $E489: dynamic initializer of a Simulator serializer attribute table
// (23 Simulator::Attribute records, 0x3c bytes each, at 0x0156b758..0x0156bcbb): the planet record
// (mKey, name, type, techLevel, flags, orbit, rotation*, ringType, gasGiantType, scores, UFO fields,
// homeWorld, plantSpecies, animalSpecies, mTerrainStampsToRemove).
//
// Same record layout and construction as the cStarManager / cGameDataUFO tables (s013249a0,
// s013388f0): every record is built in one reused 0x3c-byte stack temp and copied (rep movsd) into the
// table. Callbacks live outside this slice and are declared by address.
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

// Callbacks, by original address.
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);    // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
void ReadText_00693090(const string8& text, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
bool Valid_00b1fbf0();
bool ToXml_00675ca0(void* pData, const char* pName, int depth);

bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);
void ReadText_00694c80(const string8& text, void* pData);
void WriteText_00694c10(char* pBuffer, void* pData);
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);

void ReadText_00692ff0(const string8& text, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
bool ToXml_0057cde0(void* pData, const char* pName, int depth);

bool Read_00b8db30(ISerializerReadStream* pStream, void* pData);
bool Write_00b8db50(ISerializerWriteStream* pStream, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);
void WriteText_00692fb0(char* pBuffer, void* pData);
bool Valid_00b8db10();
bool ToXml_00ac8050(void* pData, const char* pName, int depth);

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);

bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);

bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);

bool Read_00bb9cd0(ISerializerReadStream* pStream, void* pData);
bool Write_00bb9d00(ISerializerWriteStream* pStream, void* pData);
void ReadText_00693050(const string8& text, void* pData);
void WriteText_00694f60(char* pBuffer, void* pData);
bool ToXml_00b8e840(void* pData, const char* pName, int depth);

bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);

bool Read_00c95780(ISerializerReadStream* pStream, void* pData);
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);

bool Read_00b04e00(ISerializerReadStream* pStream, void* pData);
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
bool ToXml_00eafe40(void* pData, const char* pName, int depth);

struct TShort{}; struct TU64{}; struct TFloat{}; struct TDouble{}; struct TU8{}; struct TKey{}; struct TSpecies{}; struct TName{}; struct TRotAxis{}; struct TStamps{};
template<typename T> bool Valid();      // 0x00b1fbf0
template<typename T> bool ToXmlT(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot sAttributes[23];   // 0x0156b758

#define U32_ATTR   Read4<uint64_t>, Write4<uint64_t>, ReadText_00692ff0, WriteText_00694ee0, Valid<TU64>, ToXmlT<TU64>
#define S16_ATTR   Read4<int16_t>, Write4<int16_t>, ReadText_00693090, WriteText_00694f00, Valid<TShort>, ToXmlT<TShort>
#define FLOAT_ATTR Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0, Valid<TFloat>, ToXmlT<TFloat>
#define DOUBLE_ATTR Read4<double>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXmlT<TDouble>
#define U8_ATTR    Read_00bb9cd0, Write_00bb9d00, ReadText_00693050, WriteText_00694f60, Valid<TU8>, ToXmlT<TU8>
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, Valid<TKey>, ToXmlT<TKey>
#define SPECIES_ATTR Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TSpecies>, ToXmlT<TSpecies>

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&sAttributes[IDX] = a; }

// @ 0x01322a30
void InitPlanetAttributes()
{
    ADD(0,  "mKey", 0x04164f8e, 0x184, S16_ATTR)
    ADD(1,  "name", 0x03d58b9a, 0x18, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, Valid<TName>, ToXmlT<TName>)
    ADD(2,  "type", 0x03d58b9e, 0x28, U32_ATTR)
    ADD(3,  "techLevel", 0x03d58b9f, 0x194, U32_ATTR)
    ADD(4,  "flags", 0x03d58b99, 0x2c, S16_ATTR)
    ADD(5,  "orbit", 0x03f6d6ba, 0x30, Read_00b8db30, Write_00b8db50, ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b8db10, ToXml_00ac8050)
    ADD(6,  "rotationIsNull", 0x0417a8ca, 0x98, FLOAT_ATTR)
    ADD(7,  "rotationAxis", 0x0417a8e9, 0x9c, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, Valid<TRotAxis>, ToXmlT<TRotAxis>)
    ADD(8,  "rotationPeriod", 0x0417a902, 0xa8, DOUBLE_ATTR)
    ADD(9,  "ringType", 0x03f6d514, 0xac, U8_ATTR)
    ADD(10, "gasGiantType", 0x03f6d526, 0xad, U8_ATTR)
    ADD(11, "mGeneratedTerrainKey", 0x03d58b9b, 0x1a4, KEY_ATTR)
    ADD(12, "mSpiceGen", 0x03d58b9c, 0x198, KEY_ATTR)
    ADD(13, "atmosphereScore", 0x0415fbbe, 0xb0, DOUBLE_ATTR)
    ADD(14, "temperatureScore", 0x0415fbcd, 0xb4, DOUBLE_ATTR)
    ADD(15, "waterScore", 0x0415fbdf, 0xb8, DOUBLE_ATTR)
    ADD(16, "numDefenderUFOs", 0x05c19861, 0x124, U32_ATTR)
    ADD(17, "timeLastBuiltUFOs", 0x05c1a01b, 0x128, DOUBLE_ATTR)
    ADD(18, "timeCalledReinforcements", 0x05c1a027, 0x12c, DOUBLE_ATTR)
    ADD(19, "homeWorld", 0x05c1a028, 0x130, FLOAT_ATTR)
    ADD(20, "plantSpecies", 0x04164f63, 0xbc, SPECIES_ATTR)
    ADD(21, "animalSpecies", 0x04164f8d, 0xd0, SPECIES_ATTR)
    ADD(22, "mTerrainStampsToRemove", 0x04164f9e, 0x148, Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TStamps>, ToXmlT<TStamps>)
}

// =====================================================================================
// Slice s01320f20 -- three more static attribute-table initialisers of the same family:
// the cIDColor table (0x0156b0d8, 2 records), the creature/species mission table
// (0x0156b198, 5 records) and the model/appearance table (0x0156bd78, 8 records).
// Every record is built in one reused 0x3c-byte Attribute temporary and copied into the
// static table with a 15-dword rep movsd, exactly like InitPlanetAttributes above.
// =====================================================================================

// --- callbacks that are not declared above, by original address -----------------------
void FUN_00b6e230(Attribute* pAttr);                 // 0x00b6e230  setDefault of mIDColorID
bool Read_00572810(ISerializerReadStream* pStream, void* pData);      // 0x00572810
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);     // 0x00572840

bool Read_00b701b0(ISerializerReadStream* pStream, void* pData);       // 0x00b701b0
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);     // 0x00aca730
bool Valid_00b6f860();                                                 // 0x00b6f860
bool ToXml_00c6c390(void* pData, const char* pName, int depth);        // 0x00c6c390

bool Read_00b6fb20(ISerializerReadStream* pStream, void* pData);       // 0x00b6fb20
bool Write_00b6fc90(ISerializerWriteStream* pStream, void* pData);     // 0x00b6fc90
bool Valid_00cd36f0();                                                 // 0x00cd36f0
bool ToXml_00cd3920(void* pData, const char* pName, int depth);        // 0x00cd3920

bool Read_00b70290(ISerializerReadStream* pStream, void* pData);       // 0x00b70290
bool Write_00b6ffa0(ISerializerWriteStream* pStream, void* pData);     // 0x00b6ffa0
bool Valid_00b6fd80();                                                 // 0x00b6fd80
bool ToXml_00b70410(void* pData, const char* pName, int depth);        // 0x00b70410

bool Read_00b6fa00(ISerializerReadStream* pStream, void* pData);       // 0x00b6fa00
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);     // 0x00bca960
bool Valid_00b6f550();                                                 // 0x00b6f550

bool Read_00b6fa30(ISerializerReadStream* pStream, void* pData);       // 0x00b6fa30

void FUN_00b8f8b0(Attribute* pAttr);                                   // 0x00b8f8b0  setDefault of mAlphaModel
void FUN_00b8f8d0(Attribute* pAttr);                                   // 0x00b8f8d0  setDefault of mBaseRadius
void FUN_00b8f8f0(Attribute* pAttr);                                   // 0x00b8f8f0  setDefault of mCanopyRadius
void FUN_00b8f910(Attribute* pAttr);                                   // 0x00b8f910  setDefault of mHeight

// --- the attribute tables these initialisers fill ------------------------------------
extern Attribute sColorAttributes[2];      // 0x0156b0d8  cIDColor records
extern Attribute sMissionAttributes[5];    // 0x0156b198  creature / species mission records
extern Attribute sModelAttributes[8];      // 0x0156bd78  model + appearance records

// --- globals written by the initialisers ---------------------------------------------
extern int   g_1687980;                    // 0x01687980  cached colour attribute id
extern int   g_16882ec;                    // 0x016882ec  model info key
extern float g_16882f0;                    // 0x016882f0  model base radius
extern float g_16882f4;                    // 0x016882f4  model canopy radius
extern float g_16882f8;                    // 0x016882f8  model height

// @ 0x01320f20
void InitIDColorAttributes()
{
    {
        Attribute a("mIDColorID", 0x5594700, 4, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0,
                    FUN_00b6e230);
        sColorAttributes[0] = a;
    }
    {
        Attribute a("mCachedColor", 0x6cf7f50, 0x24, Read_00b6e3a0, Write_00ac88c0,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid<TRotAxis>, ToXml_00ac8050);
        sColorAttributes[1] = a;
    }
    g_1687980 = 0x53dbcf2;
}

// @ 0x01321080
void InitMissionAttributes()
{
    {
        Attribute a("mCreatureMissionList", 0x940fd9b5, 0x14, Read_00b701b0, Write_00aca730,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b6f860, ToXml_00c6c390);
        sMissionAttributes[0] = a;
    }
    {
        Attribute a("mCreatureMissionMap", 0x53540b3, 0x28, Read_00b6fb20, Write_00b6fc90,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid_00cd36f0, ToXml_00cd3920);
        sMissionAttributes[1] = a;
    }
    {
        Attribute a("mSpeciesMissionMap", 0xf40fd9b4, 0x48, Read_00b70290, Write_00b6ffa0,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b6fd80, ToXml_00b70410);
        sMissionAttributes[2] = a;
    }
    {
        Attribute a("mpDisplayedSpeciesMission", 0xb40fd9ab, 0x68, Read_00b6fa00, Write_00bca960,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b6f550, ToXml_00ac8050);
        sMissionAttributes[3] = a;
    }
    {
        Attribute a("mpDisplayedTutorialMission", 0xb40fd9ac, 0x6c, Read_00b6fa30, Write_00bca960,
                    ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b6f550, ToXml_00ac8050);
        sMissionAttributes[4] = a;
    }
}

// @ 0x01324260
void InitModelAttributes()
{
    {
        Attribute a("mModelIDLOD0", 0x384448b, 0x7c, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[0] = a;
    }
    {
        Attribute a("mModelIDLOD1", 0x384448c, 0x80, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[1] = a;
    }
    {
        Attribute a("mModelIDLOD2", 0x384448f, 0x84, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[2] = a;
    }
    {
        Attribute a("mModelIDLOD3", 0x3844491, 0x88, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[3] = a;
    }
    {
        Attribute a("mAlphaModel", 0x5ada0bb, 0x8c, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0,
                    FUN_00b8f8b0);
        sModelAttributes[4] = a;
    }
    {
        Attribute a("mBaseRadius", 0x5ad9efa, 0x94, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f8d0);
        sModelAttributes[5] = a;
    }
    {
        Attribute a("mCanopyRadius", 0x5ad9f00, 0x98, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f8f0);
        sModelAttributes[6] = a;
    }
    {
        Attribute a("mHeight", 0x5ad9f03, 0x9c, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f910);
        sModelAttributes[7] = a;
    }
    g_16882ec = 0;
    g_16882f0 = 0.0f;
    g_16882f4 = 0.0f;
    g_16882f8 = 0.0f;
}

}  // namespace Simulator
