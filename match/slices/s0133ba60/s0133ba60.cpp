// 0x0133ba60 ($E577): dynamic initializer of the Simulator::cMission serializer attribute table
// (26 Simulator::Attribute records, 0x3c bytes each, at 0x015745f0..0x01574c07).
//
// Same record layout and construction as the cGameDataUFO table (s013388f0) and the cVehicle /
// cTribe / cPlayer tables: name, id, member offset, three uninitialized fields, pCurrentObject
// (+0x18) = 0, set-default callback (+0x1c) = 0, the offset function (0x00692ca0) and the
// read/write/readText/writeText/validate/toXml callbacks. Every record is built in one reused
// 0x3c-byte stack temp and copied (rep movsd) into the table. Row data read off the retail
// initializer; the callbacks live outside this slice and are declared by address (per-type template
// instances folded by the linker are declared as templates, as in s013388f0).
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
class cPlanet;
class cMission;
class cStarClue;
class cPlanetClue;
class cGalaxyCommEvent;
struct UInt32Vector;   // eastl::vector<uint32_t> members (tool/animal/plant ID lists)
struct MissionFlags;
// Tags for the unsigned-int rows: their per-type callbacks are distinct template instances.
struct UInt_mMissionID;
struct UInt_mDuration;
struct UInt_mElapsedTimeMS;
struct UInt_mOwnerEmpireID;
struct UInt_mStarMapIconEffectID;
struct UInt_mTargetEmpireID;
struct UInt_mProgressEventID;

// Per-type template instances (folded by the linker to one address each).
// 0x00572810: 4-byte raw read
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
// 0x00572840: 4-byte integer write
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
// 0x00693090: ReadTextInt<T> for unsigned integers and bool
template<typename T> void ReadTextInt(const string8& text, void* pData);
// 0x00b1fbf0: AlwaysValid<T> (return true) for every plain-value type
template<typename T> bool AlwaysValid();

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00ae97b0(ISerializerReadStream* pStream, void* pData);
bool Read_00ae9dd0(ISerializerReadStream* pStream, void* pData);
bool Read_00b00430(ISerializerReadStream* pStream, void* pData);
bool Read_00c3b930(ISerializerReadStream* pStream, void* pData);
bool Read_00c463f0(ISerializerReadStream* pStream, void* pData);
bool Read_00c4a960(ISerializerReadStream* pStream, void* pData);
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00b02570(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00bdd350(ISerializerWriteStream* pStream, void* pData);
bool Write_00c46430(ISerializerWriteStream* pStream, void* pData);
bool Write_00c47660(ISerializerWriteStream* pStream, void* pData);
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

bool Validate_00b6f550();
bool Validate_00c45100();
bool Validate_00c45120();

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cMission_sAttributes[26];   // 0x015745f0

// ToXml 0x00675ca0 is a per-type template instance as well (unsigned int fields).
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);
#define UINT_ATTR(T) Read4<T>, Write4<uint32_t>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<T>, ToXmlUInt<T>
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720
#define IDLIST_ATTR Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<UInt32Vector>, ToXml_00c6c4e0
#define PTR_ATTR(T, R, W, V)  /* T: pointee, for reading only */ R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cMission_sAttributes[IDX] = a; }

// @ 0x0133ba60
void InitMissionAttributes()
{
    ADD(0,  "mMissionID", 0x03851967, 0x78, UINT_ATTR(UInt_mMissionID))
    ADD(1,  "mDuration", 0x13851968, 0x80, UINT_ATTR(UInt_mDuration))
    ADD(2,  "mElapsedTimeMS", 0x03851968, 0x7c, UINT_ATTR(UInt_mElapsedTimeMS))
    ADD(3,  "mState", 0x03851969, 0x84, INT_ATTR)
    ADD(4,  "mOwnerEmpireID", 0x0385196a, 0x8c, UINT_ATTR(UInt_mOwnerEmpireID))
    ADD(5,  "mpSourcePlanet", 0x0385196b, 0x9c, PTR_ATTR(cPlanet, Read_00c3b930, Write_00bdd350, Validate_00b6f550))
    ADD(6,  "mpTargetPlanet", 0x0385196c, 0x1e8, PTR_ATTR(cPlanet, Read_00c3b930, Write_00bdd350, Validate_00b6f550))
    ADD(7,  "mRewardMoney", 0x0385196d, 0xa0, FLOAT_ATTR)
    ADD(8,  "mRewardToolID", 0x0385196e, 0xa4, KEY_ATTR)
    ADD(9,  "mTargetAnimalSpeciesKey", 0x03f6ad2c, 0x170, KEY_ATTR)
    ADD(10, "mStarClue", 0x03851972, 0xc4, PTR_ATTR(cStarClue, Read_00c4a960, Write_00c47660, Validate_00c45100))
    ADD(11, "mPlanetClue", 0x03851973, 0xf4, PTR_ATTR(cPlanetClue, Read_00c463f0, Write_00c46430, Validate_00c45120))
    ADD(12, "mStarMapIconEffectID", 0x03851974, 0x100, UINT_ATTR(UInt_mStarMapIconEffectID))
    ADD(13, "mUnlockToolIDList", 0x03851977, 0x11c, IDLIST_ATTR)
    ADD(14, "mTargetEmpireID", 0x03851978, 0x94, UINT_ATTR(UInt_mTargetEmpireID))
    ADD(15, "mProgressEventID", 0x03978791, 0x148, UINT_ATTR(UInt_mProgressEventID))
    ADD(16, "mGiveOnAcceptAnimalIDs", 0x03f6b0d8, 0x1a8, IDLIST_ATTR)
    ADD(17, "mGiveOnAcceptPlantIDs", 0x03f6b0de, 0x1bc, IDLIST_ATTR)
    ADD(18, "mGiveOnAcceptToolIDs", 0x03f6b0df, 0x194, IDLIST_ATTR)
    ADD(19, "mGiveOnAcceptMoney", 0x03f6b0e0, 0x190, INT_ATTR)
    ADD(20, "mFlags", 0x03f6b0e1, 0x130, PTR_ATTR(MissionFlags, Read_00b00430, Write_00b02570, AlwaysValid<MissionFlags>))
    ADD(21, "mpParentMission", 0x03f6b0e2, 0x17c, PTR_ATTR(cMission, Read_00ae97b0, Write_00bca960, Validate_00b6f550))
    ADD(22, "mSystemsShutdown", 0x03f6b0e3, 0x88, BOOL_ATTR)
    ADD(23, "mAcceptCost", 0x03f6b0e4, 0x184, INT_ATTR)
    ADD(24, "mToolCost", 0x03f6b0e5, 0x188, INT_ATTR)
    ADD(25, "mpGalaxyCommEvent", 0x0679f2f3, 0x1e4, PTR_ATTR(cGalaxyCommEvent, Read_00ae9dd0, Write_00bca960, Validate_00b6f550))
}

}  // namespace Simulator
