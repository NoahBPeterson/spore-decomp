// @ 0x01326120  $E506: dynamic initializer of the Simulator::cStarManager serializer attribute
// table (19 Simulator::Attribute records, 0x3c bytes each, at 0x0156c668..0x0156cadb).
//
// Same record layout and construction as the cGameDataUFO table (s013388f0): every record is built in
// one reused 0x3c-byte stack temp and copied (rep movsd) into the table. Member names and offsets
// agree with ModAPI cStarManager.h (mAvailableStarterWorlds at 0xa0, mStarRecordGrid at 0xc8,
// mGrobID at 0x1d8). Three records (sGameTimeManagerContainer, sRelationshipManagerContainer,
// sNameCountMap) describe class statics (0x01689644, 0x01689640, 0x0156c64c): their offset field
// holds the static's address, their offset function is 0x011874d0 and they have no ToXml callback.
// Callbacks live outside this slice and are declared by address.
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

struct Vector3;

// Callbacks, by original address.
bool Read_00bb67d0(ISerializerReadStream* pStream, void* pData);
bool Write_00ba73b0(ISerializerWriteStream* pStream, void* pData);
bool Read_00badf20(ISerializerReadStream* pStream, void* pData);
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
bool Read_00bab080(ISerializerReadStream* pStream, void* pData);
bool Write_00ba94e0(ISerializerWriteStream* pStream, void* pData);
bool Read_00ba7420(ISerializerReadStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Read_00ba8250(ISerializerReadStream* pStream, void* pData);
bool Read_00bab200(ISerializerReadStream* pStream, void* pData);
bool Read_00ba66d0(ISerializerReadStream* pStream, void* pData);
bool Write_00ba66f0(ISerializerWriteStream* pStream, void* pData);
bool Read_00b5cb60(ISerializerReadStream* pStream, void* pData);
bool Write_00b5cb80(ISerializerWriteStream* pStream, void* pData);
bool Read_00ba6710(ISerializerReadStream* pStream, void* pData);
bool Write_00ba6730(ISerializerWriteStream* pStream, void* pData);
bool Read_00bb1660(ISerializerReadStream* pStream, void* pData);
bool Write_00ba8280(ISerializerWriteStream* pStream, void* pData);
bool Read_00bb1830(ISerializerReadStream* pStream, void* pData);
bool Write_00ba7490(ISerializerWriteStream* pStream, void* pData);
bool Read_00b04e00(ISerializerReadStream* pStream, void* pData);
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
bool Read_00bb19d0(ISerializerReadStream* pStream, void* pData);
bool Write_00ba7510(ISerializerWriteStream* pStream, void* pData);
bool Read_00bab620(ISerializerReadStream* pStream, void* pData);
bool Write_00ba7590(ISerializerWriteStream* pStream, void* pData);

template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);          // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);        // 0x00572840
template<typename T> void ReadTextInt(const string8& text, void* pData);               // 0x00693090
template<typename T> bool AlwaysValid();                                               // 0x00b1fbf0

void ReadText_00c2e4e0(const string8& text, void* pData);
void WriteText_00692fb0(char* pBuffer, void* pData);
template<typename T> void ReadTextMap(const string8& text, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694bd0(char* pBuffer, void* pData);

bool Validate_00b6f860();
bool Validate_00ba7450();
bool Validate_00b6f550();
bool Validate_00ba6690();
bool Validate_00d011e0();

bool ToXml_00c51440(void* pData, const char* pName, int depth);
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00bab380(void* pData, const char* pName, int depth);
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
bool ToXml_00bab4d0(void* pData, const char* pName, int depth);
bool ToXml_00bab740(void* pData, const char* pName, int depth);

extern uint32_t cStarManager_sGameTimeManagerContainer;       // 0x01689644
extern uint32_t cStarManager_sRelationshipManagerContainer;   // 0x01689640
extern uint32_t cStarManager_sNameCountMap;                   // 0x0156c64c

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cStarManager_sAttributes[19];   // 0x0156c668

// record families (read, write, readText, writeText, validate, toXml)
#define GRID_ATTR     Read_00bb67d0, Write_00ba73b0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00c51440
#define STARVEC_ATTR  Read_00badf20, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
#define HOMEVEC_ATTR  Read_00bab080, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0
#define ID_ATTR       Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cStarManager_sAttributes[IDX] = a; }

// @ 0x01326120
void InitStarManagerAttributes()
{
    ADD(0,  "mStarRecordGrid", 0x03fabad0, 0xc8, GRID_ATTR)
    ADD(1,  "mStarterStarRecords", 0x03ea8676, 0xdc, STARVEC_ATTR)
    ADD(2,  "mSavedGameStarRecords", 0x03ea8679, 0xf0, STARVEC_ATTR)
    ADD(3,  "mBlackHoles", 0x055ceb62, 0x104, STARVEC_ATTR)
    ADD(4,  "mEmpireHomeStarRecords", 0x04274872, 0x12c, HOMEVEC_ATTR)
    ADD(5,  "mPossibleStartLocations", 0x0563c450, 0x118, STARVEC_ATTR)
    ADD(6,  "mSol", 0x03f5bbc2, 0x148, Read_00ba7420, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(7,  "mpGlobalCLGItems", 0x044ee63e, 0x220, Read_00ba8250, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(8,  "mNextPoliticalID", 0x044ee640, 0x1d4, Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(9,  "mGrobID", 0x044ee641, 0x1d8, Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(10, "mEmpires", 0x052c47aa, 0x150, Read_00bab200, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0)
    ADD(11, "mTradeRouteManager", 0x05528d40, 0x1e0, Read_00ba66d0, Write_00ba66f0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba6690, ToXml_00ac8050)
    ADD(12, "sGameTimeManagerContainer", 0x0579f61c, &cStarManager_sGameTimeManagerContainer, Read_00b5cb60, Write_00b5cb80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>)
    ADD(13, "sRelationshipManagerContainer", 0x056e616c, &cStarManager_sRelationshipManagerContainer, Read_00ba6710, Write_00ba6730, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>)
    ADD(14, "sNameCountMap", 0x05d55277, &cStarManager_sNameCountMap, Read_00bb1660, Write_00ba8280, ReadTextMap<int>, WriteText_00694bd0, AlwaysValid<void*>)
    ADD(15, "mTransactionLog", 0x05d55278, 0x208, Read_00bb1830, Write_00ba7490, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00bab380)
    ADD(16, "mAvailableStarterWorlds", 0x0563c451, 0xa0, Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00eafe40)
    ADD(17, "mEmpireNamesInUse", 0x06b94eb9, 0x16c, Read_00bb19d0, Write_00ba7510, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<void*>, ToXml_00bab4d0)
    ADD(18, "mAdventureIDs", 0x0799479d, 0x184, Read_00bab620, Write_00ba7590, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00d011e0, ToXml_00bab740)
}

}  // namespace Simulator
