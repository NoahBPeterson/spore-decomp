// @ 0x013388f0  $E432: dynamic initializer of the Simulator::cGameDataUFO serializer attribute
// table (32 Simulator::Attribute records, 0x3c bytes each, at 0x01573290..0x01573a0f).
//
// Same record layout as the cVehicle / cTribe / cPlayer tables (s01357f40, s013551e0, s01350ca0):
// name, id, member offset, three uninitialized fields, pCurrentObject (+0x18), set-default
// callback (+0x1c, null here), the offset function and the read/write/text/validate/xml
// callbacks. Member names and offsets agree with ModAPI cGameDataUFO.h (mNPCFollowUFO at 0x68c,
// mDestinationPlanet at 0x75c, mOwnerMission at 0x800).
// Two records describe class statics (sDestinationStarKey at 0x0168df6c, sNPCHomeStarKey at
// 0x0168df70): their offset field holds the static's address, their offset function is
// 0x011874d0 (returns pAttr->offset) and they have no ToXml callback.
// Every record is built in one reused 0x3c-byte stack temp and copied (rep movsd) into the table.
// Row data read off the retail initializer; callbacks live outside this slice and are declared
// by address. Callbacks that are per-type template instances in the original (the linker folds
// identical code to one address) are declared as templates: cl sees distinct symbols, which
// decides which callback constants it keeps in ebx/ebp. The pointer-member callbacks
// (text 0x00c2e4e0/0x00692fb0, validate 0x00b6f550, xml 0x00ac8050, write 0x00bca960) must be
// single shared symbols: as per-type templates cl picks different registers.
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
struct Quaternion;
struct ResourceKey;
class cPlanet;
class cGameDataUFO;
class cWeapon;   // ModAPI cSpaceToolData
class cMission;

// Per-type template instances (folded by the linker to one address each).
// 0x00572810: 4-byte raw read
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
// 0x00572840: 4-byte integer write
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
// 0x00693090: ReadTextInt<T> for unsigned integers and bool
template<typename T> void ReadTextInt(const string8& text, void* pData);
// 0x00b1fbf0: AlwaysValid<T> (return true) for every plain-value type
template<typename T> bool AlwaysValid();
// 0x00c2e4e0 / 0x00692fb0 / 0x00ac8050: text and xml callbacks shared by every pointer type
template<typename T> void ReadTextPtr(const string8& text, void* pData);
template<typename T> void WriteTextPtr(char* pBuffer, void* pData);
template<typename T> bool ToXmlPtr(void* pData, const char* pName, int depth);
// 0x00b6f550: Validate_00b6f550
template<typename T> bool ValidatePtr();

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae33d0(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00ae97b0(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Read_00bceb00(ISerializerReadStream* pStream, void* pData);
bool Read_00c3b930(ISerializerReadStream* pStream, void* pData);
bool Read_00c3b970(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3400(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00bd1780(ISerializerWriteStream* pStream, void* pData);
bool Write_00bdd350(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00693120(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);

void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);
void WriteText_00695040(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

bool Validate_00c87090();
bool Validate_00b6f550();
void ReadText_00c2e4e0(const string8& text, void* pData);
void WriteText_00692fb0(char* pBuffer, void* pData);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00ae5700(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);

extern uint32_t cGameDataUFO_sDestinationStarKey;   // 0x0168df6c
extern uint32_t cGameDataUFO_sNPCHomeStarKey;       // 0x0168df70

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cGameDataUFO_sAttributes[32];   // 0x01573290

#define VEC3_ATTR  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0
#define QUAT_ATTR  Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AlwaysValid<Quaternion>, ToXml_00ae5700
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define PTR_ATTR(T, R, W, V)  /* T: pointee, for reading only */ R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050
#define STATIC_UINT_ATTR Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cGameDataUFO_sAttributes[IDX] = a; }

// @ 0x013388f0
void InitGameDataUFOAttributes()
{
    ADD(0,  "mNextPosition", 0x021fc170, 0x718, VEC3_ATTR)
    ADD(1,  "mNextVelocity", 0x058241ad, 0x724, VEC3_ATTR)
    ADD(2,  "mNextOrientation", 0x021fc172, 0x730, QUAT_ATTR)
    ADD(3,  "mOffsetFromPosition", 0x058241c6, 0x740, VEC3_ATTR)
    ADD(4,  "mLastTangentialVelocity", 0x021fc174, 0x5f4, VEC3_ATTR)
    ADD(5,  "mDestination", 0x021fc178, 0x750, VEC3_ATTR)
    ADD(6,  "mAtDestination", 0x021fc17c, 0x74c, BOOL_ATTR)
    ADD(7,  "mRotateTowardsDestination", 0x05823f78, 0x624, BOOL_ATTR)
    ADD(8,  "mOffsetDueToDamage", 0x021fc17e, 0x60c, VEC3_ATTR)
    ADD(9,  "mUFOType", 0x021fc17f, 0x714, INT_ATTR)
    ADD(10, "mDesiredModelKey", 0x03868c14, 0x780, KEY_ATTR)
    ADD(11, "mDesiredVisible", 0x038784a4, 0x77c, BOOL_ATTR)
    ADD(12, "mZoomAltitude", 0x0519c29e, 0x768, FLOAT_ATTR)
    ADD(13, "mStartEndPoint", 0x053eb2fe, 0x6bc, VEC3_ATTR)
    ADD(14, "mDestinationPlanet", 0x053eb303, 0x75c, PTR_ATTR(cPlanet, Read_00c3b930, Write_00bdd350, Validate_00b6f550))
    ADD(15, "mPreviousPlanet", 0x05823bff, 0x760, PTR_ATTR(cPlanet, Read_00c3b930, Write_00bdd350, Validate_00b6f550))
    ADD(16, "sDestinationStarKey", 0x05823cbd, &cGameDataUFO_sDestinationStarKey, STATIC_UINT_ATTR)
    ADD(17, "mNPCFollowUFO", 0x053ecd20, 0x68c, PTR_ATTR(cGameDataUFO, Read_00c3b970, Write_00bca960, Validate_00b6f550))
    ADD(18, "mNPCFollowOffset", 0x053efa00, 0x694, VEC3_ATTR)
    ADD(19, "mNPCOrbitOffset", 0x053ff93c, 0x6a0, VEC3_ATTR)
    ADD(20, "mNPCZoomOffset", 0x05824001, 0x6ac, FLOAT_ATTR)
    ADD(21, "mNPCFlockIndex", 0x053ed0f8, 0x6b0, INT_ATTR)
    ADD(22, "mNPCWeapon", 0x05823a4c, 0x790, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(23, "mNPCGroundWeapon", 0x05823a79, 0x794, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(24, "mNPCNearAirWeapon", 0x05823a7b, 0x798, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(25, "mNPCMediumAirWeapon", 0x0615d246, 0x79c, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(26, "mNPCFarAirWeapon", 0x0615d248, 0x7a0, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(27, "mNPCAbductWeapon", 0x05823a7d, 0x7a4, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(28, "sNPCHomeStarKey", 0x05823afe, &cGameDataUFO_sNPCHomeStarKey, STATIC_UINT_ATTR)
    ADD(29, "mEnergy", 0x0581e106, 0x7f4, FLOAT_ATTR)
    ADD(30, "mMaxEnergy", 0x0581e107, 0x7f8, FLOAT_ATTR)
    ADD(31, "mOwnerMission", 0x0644fb47, 0x800, PTR_ATTR(cMission, Read_00ae97b0, Write_00bca960, Validate_00b6f550))
}

}  // namespace Simulator
