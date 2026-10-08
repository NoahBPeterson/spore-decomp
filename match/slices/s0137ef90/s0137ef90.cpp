// @ 0x0137ef90  $E299: dynamic initializer of the Simulator::cCellSerialiazibleData serializer
// attribute table (22 Simulator::Attribute records, 0x3c bytes each, at 0x015a7e38..0x015a835f).
//
// Same record layout and construction as the cGameDataUFO table (s013388f0): every record is built
// in one reused 0x3c-byte stack temp and copied (rep movsd) into the table. Member names and offsets
// agree with ModAPI cCellSerialiazibleData.h (mPlayerCreatureKey at 0x10, mFirstEditorEntry at 0xe2,
// mNanovirusActive at 0xe8, mAddedStartTelemetry at 0xe9). Ids/offsets and callbacks were read off
// the initializer. Callbacks that are per-type template instances in the original (folded by the
// linker to one address) are declared as templates so cl sees distinct symbols.
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


struct ResourceKey;
struct UnlockedParts;
struct MissionList;

// Per-type template instances (folded by the linker to one address each).
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
template<typename T> void ReadTextInt(const string8& text, void* pData);          // 0x00693090
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00e5c5d0(ISerializerReadStream* pStream, void* pData);
bool Read_00e5c6e0(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00e5c660(ISerializerWriteStream* pStream, void* pData);
bool Write_00e51250(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00b1fbf0(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cCellSerialiazibleData_sAttributes[22];   // 0x015a7e38

#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define SHORT_ATTR Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCellSerialiazibleData_sAttributes[IDX] = a; }

// @ 0x0137ef90
void InitCellDataAttributes()
{
    ADD(0,  "mPlayerCreatureKey", 0xabcd0000, 0x10, KEY_ATTR)
    ADD(1,  "mFoodProgression", 0xabcd0001, 0x1c, INT_ATTR)
    ADD(2,  "mPlantFoodProgression", 0xabcd0011, 0x20, INT_ATTR)
    ADD(3,  "mUnlockedParts", 0xabcd0002, 0x34, Read_00e5c5d0, Write_00e5c660, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<UnlockedParts>, ToXml_00b1fbf0)
    ADD(4,  "mPartCinematicPlayed", 0xabcd0004, 0x68, BOOL_ATTR)
    ADD(5,  "mShowMateButton", 0xabcd0005, 0x69, BOOL_ATTR)
    ADD(6,  "mKillCount", 0x06947316, 0x6c, INT_ATTR)
    ADD(7,  "mDeathCount", 0x06947317, 0x70, INT_ATTR)
    ADD(8,  "gameTimeMS", 0x35875139, 0x74, INT_ATTR)
    ADD(9,  "gameID", 0xabcd0009, 0x78, SHORT_ATTR)
    ADD(10, "difficulty", 0xabcd0010, 0x7c, INT_ATTR)
    ADD(11, "missions", 0xabcd0012, 0x80, Read_00e5c6e0, Write_00e51250, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<MissionList>, ToXml_00ac8050)
    ADD(12, "playerHasMoved", 0xabcd0013, 0xe0, BOOL_ATTR)
    ADD(13, "playerHasEaten", 0xabcd0014, 0xe1, BOOL_ATTR)
    ADD(14, "mEvolutionPointsSpent", 0xabcd0015, 0x2c, INT_ATTR)
    ADD(15, "mOverPlantFoodProgression", 0xabcd0016, 0x24, INT_ATTR)
    ADD(16, "mOverAnimalFoodProgression", 0xabcd0017, 0x28, INT_ATTR)
    ADD(17, "mFirstEditorEntry", 0xabcd0018, 0xe2, BOOL_ATTR)
    ADD(18, "mNanites", 0xabcd0019, 0xe4, INT_ATTR)
    ADD(19, "mNanovirusActive", 0xabcd0020, 0xe8, BOOL_ATTR)
    ADD(20, "mGameMode", 0xabcd0021, 0xc, INT_ATTR)
    ADD(21, "mAddedStartTelemetry", 0xabcd0022, 0xe9, BOOL_ATTR)
}

}  // namespace Simulator
