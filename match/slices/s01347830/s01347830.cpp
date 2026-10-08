// @ 0x01347b70  $E420: dynamic initializer of the UFO game-data serializer attribute table
// (17 Simulator::Attribute records, 0x3c bytes each, at 0x01576bc8..0x01576fc3).
// Same record layout/construction as s0133ba60 (cMission): each record is built in one reused
// stack temp and copied into the table. Row data read off the retail initializer.
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
extern AttrSlot cUFO_sAttributes[17];   // 0x01576bc8

// ToXml 0x00675ca0 is a per-type template instance as well (unsigned int fields).
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);
#define UINT_ATTR(T) Read4<T>, Write4<uint32_t>, ReadTextInt<T>, WriteText_00694f00, AlwaysValid<T>, ToXmlUInt<T>
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720
#define PTR_ATTR(T, R, W, V)  R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cUFO_sAttributes[IDX] = a; }

struct Vec3Tag;
struct UInt_mOriginStarRecordID;
struct UInt_mAttackerEmpire;
struct UInt_mTimeOfArrivalMS;
class cSPGameDataUFO;
bool Read_00c3b970(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool Read_00c5cff0(ISerializerReadStream* pStream, void* pData);
bool Write_00c5b3d0(ISerializerWriteStream* pStream, void* pData);
bool Validate_00c5bb80();
bool ToXml_00f29650(void* pData, const char* pName, int depth);

// @ 0x01347b70
void InitUFOAttributes()
{
    ADD(0,  "mDamageRemainder", 0x038521e8, 0x20c, FLOAT_ATTR)
    ADD(1,  "mDamageRemainderUFO", 0x056bc0f6, 0x210, FLOAT_ATTR)
    ADD(2,  "mInitialized", 0x0552a11e, 0x21d, BOOL_ATTR)
    ADD(3,  "mShowDefaultEventLog", 0x0552a11f, 0x21e, BOOL_ATTR)
    ADD(4,  "mNumBombers", 0x056b7886, 0x1f8, INT_ATTR)
    ADD(5,  "mNumFighters", 0x06450510, 0x1fc, INT_ATTR)
    ADD(6,  "mShouldDestroyColonyObject", 0x05c4156b, 0x214, BOOL_ATTR)
    ADD(7,  "mOriginStarRecordID", 0x05e8ff22, 0x1f4, UINT_ATTR(UInt_mOriginStarRecordID))
    ADD(8,  "mGalaxyBomber", 0x05ed03d6, 0x1f0, PTR_ATTR(cSPGameDataUFO, Read_00c3b970, Write_00bca960, Validate_00b6f550))
    ADD(9,  "mPendingUFOKey", 0x05ed0f0f, 0x200, KEY_ATTR)
    ADD(10, "mUFOsLeaveOnArrival", 0x05ed0f10, 0x21c, BOOL_ATTR)
    ADD(11, "mUFOSpawnLocation", 0x060de151, 0x224, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vec3Tag>, ToXml_00acbba0)
    ADD(12, "mIsPlayerSummoned", 0x06367659, 0x234, BOOL_ATTR)
    ADD(13, "mAttackerEmpire", 0x0636765a, 0x230, UINT_ATTR(UInt_mAttackerEmpire))
    ADD(14, "mBackgroundShipsList", 0x0648d0a9, 0x238, Read_00c5cff0, Write_00c5b3d0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00c5bb80, ToXml_00f29650)
    ADD(15, "mWaitingForRaid", 0x064925c9, 0x215, BOOL_ATTR)
    ADD(16, "mTimeOfArrivalMS", 0x0684a115, 0x220, UINT_ATTR(UInt_mTimeOfArrivalMS))
}

}  // namespace Simulator
