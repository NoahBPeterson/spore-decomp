// @ 0x01357f40  $E615: dynamic initializer of the Simulator::cVehicle serializer attribute table
// (32 Simulator::Attribute records, 0x3c bytes each, at 0x0157cac8..0x0157d247).
//
// Same record layout as the cTribe / cPlayer / cHerd tables (s013551e0, s01350ca0, s0134d380):
// name, id, member offset, three uninitialized fields, pCurrentObject (+0x18), set-default
// callback (+0x1c), the offset function (DefaultOffset for every record) and the
// read/write/text/validate/xml callbacks. Member names and offsets agree with ModAPI cVehicle.h
// (mLocomotionHint at 0xaf8, mCargoType at 0xb28, mpHitSphere at 0xcfc).
// One record carries a default: mStance, whose set-default callback (0x00c9f080) reads back the
// static at 0x01699abc; this initializer zeroes it inside the record's construction (the store
// sits between the ToXml and offset stores).
// Every record is built in one reused 0x3c-byte stack temp and copied (rep movsd) into the table.
// Row data read off the retail initializer; callbacks live outside this slice and are declared
// by address.
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

    // Record with a default value: the static the set-default callback reads back is
    // initialized here too.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, int* pDefault, int defaultValue)
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
        *pDefault = defaultValue;
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

// Default value read back by SetDefault_00c9f080 for mStance.
extern int cVehicle_sStanceDefault;   // 0x01699abc
void SetDefault_00c9f080(Attribute* pAttr);

// Read functions
// Per-type template instances. The linker folds them (identical code) to one address each,
// but cl sees distinct symbols, which decides which callback constants it keeps in registers.
// The 4-byte raw read 0x00572810: Read4<uint32_t>, Read4<float>, Read4<int> and the three enums.
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
// 0x00572840: Write4<T> for 4-byte integers
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
// 0x00693090: ReadTextInt<T> for unsigned integers, bool and the enums
template<typename T> void ReadTextInt(const string8& text, void* pData);
// 0x00b1fbf0: AlwaysValid<T> (return true) for every plain-value type
template<typename T> bool AlwaysValid();
struct Vector3;
enum VehicleLocomotion {};   // mLocomotion
enum VehiclePurpose {};      // mPurpose
enum CargoType {};           // mCargoType
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00ae9e00(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Read_00bceb00(ISerializerReadStream* pStream, void* pData);
bool Read_00bd0cb0(ISerializerReadStream* pStream, void* pData);
bool Read_00bdc650(ISerializerReadStream* pStream, void* pData);
bool Read_00ca75e0(ISerializerReadStream* pStream, void* pData);
bool Read_00ca9fe0(ISerializerReadStream* pStream, void* pData);
bool Read_00cab0e0(ISerializerReadStream* pStream, void* pData);
bool Read_00cab210(ISerializerReadStream* pStream, void* pData);

// Write functions
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00bd1780(ISerializerWriteStream* pStream, void* pData);
bool Write_00bdd350(ISerializerWriteStream* pStream, void* pData);
bool Write_00ca0710(ISerializerWriteStream* pStream, void* pData);
bool Write_00ca0830(ISerializerWriteStream* pStream, void* pData);
bool Write_00ca4420(ISerializerWriteStream* pStream, void* pData);
bool Write_00ca7690(ISerializerWriteStream* pStream, void* pData);

// ReadText functions
void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);

// Validate functions
bool Validate_00ae3310();
bool Validate_00b6f550();
bool Validate_00bd0c80();
bool Validate_00c87090();
bool Validate_00ca07b0();
bool Validate_00ca07f0();
bool Validate_00ca08c0();

// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00ca8470(void* pData, const char* pName, int depth);
bool ToXml_00ca85c0(void* pData, const char* pName, int depth);
bool ToXml_00ca8710(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cVehicle_sAttributes[32];   // 0x0157cac8

#define UINT_ATTR  Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0
#define INT_ATTR   Read4<int>, Write4<uint32_t>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<uint32_t>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define VEC3_ATTR  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0
#define TIMER_ATTR Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050
#define ENUM_ATTR(E) Read4<E>, Write4<E>, ReadTextInt<E>, WriteText_00694f00, AlwaysValid<uint32_t>, ToXml_00675ca0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cVehicle_sAttributes[IDX] = a; }

// @ 0x01357f40
void InitVehicleAttributes()
{
    ADD(0,  "mLocomotion", 0x02620f95, 0xb1c, ENUM_ATTR(VehicleLocomotion))
    ADD(1,  "mPurpose", 0x02620f96, 0xb20, ENUM_ATTR(VehiclePurpose))
    ADD(2,  "mCargoType", 0x02620f97, 0xb28, ENUM_ATTR(CargoType))
    ADD(3,  "mEvents", 0x02620f9a, 0xb2c, Read_00ca75e0, Write_00ca4420, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00bd0c80, ToXml_00ca8470)
    ADD(4,  "mCargoUnits", 0x02620f98, 0xb58, FLOAT_ATTR)
    ADD(5,  "mpNearestCity", 0x02620f99, 0xb5c, Read_00ae9e00, Write_00bca960, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(6,  "mpWeapon", 0x02620f9b, 0xb60, Read_00bceb00, Write_00bd1780, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00c87090, ToXml_00ac8050)
    ADD(7,  "mOrders", 0x03b0af2a, 0xb68, Read_00cab0e0, Write_00ca0710, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00ca07b0, ToXml_00ca85c0)
    ADD(8,  "mpChaseTarget", 0x03b0af74, 0xb7c, Read_00bdc650, Write_00bdd350, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(9,  "mIdlePosition", 0x03b0af75, 0xb80, VEC3_ATTR)
    ADD(10, "mHostileUnits", 0x03b0afe4, 0xb8c, Read_00ca9fe0, Write_00ca7690, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00ca07f0, ToXml_00c6c390)
    ADD(11, "mUIState", 0x03fea288, 0xc38, UINT_ATTR)
    ADD(12, "mAcceptableCenter", 0x03b0b02b, 0xc3c, VEC3_ATTR)
    ADD(13, "mAcceptableMinDist", 0x03b0b02c, 0xc48, FLOAT_ATTR)
    ADD(14, "mAcceptableMaxDist", 0x03b0b02d, 0xc4c, FLOAT_ATTR)
    ADD(15, "mPowerStat", 0x03b0b02e, 0xc50, FLOAT_ATTR)
    ADD(16, "mDefenseStat", 0x03b0b02f, 0xc54, FLOAT_ATTR)
    ADD(17, "mSpeedStat", 0x03b0b030, 0xc58, FLOAT_ATTR)
    ADD(18, "mDamageMultiplier", 0x04179651, 0xc5c, FLOAT_ATTR)
    ADD(19, "mWeapons", 0x0417967b, 0xc64, Read_00cab210, Write_00ca0830, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00ca08c0, ToXml_00ca8710)
    ADD(20, "mActiveWeaponIndex", 0x03b0b207, 0xc78, INT_ATTR)
    ADD(21, "mDefaultWeaponCycleTimeMS", 0x03b0b20b, 0xc7c, UINT_ATTR)
    ADD(22, "mTimeToCycleWeaponMS", 0x03b0b20e, 0xc80, INT_ATTR)
    ADD(23, "mTimeSinceLastWeaponFireMS", 0x03b0b211, 0xc84, UINT_ATTR)
    ADD(24, "mCombatStatusTimer", 0x03b0b271, 0xc88, TIMER_ATTR)
    ADD(25, "mCombatVoxTimer", 0x04a1cd8a, 0xca8, TIMER_ATTR)
    ADD(26, "mParkingTimer", 0x041f7573, 0xba0, TIMER_ATTR)
    ADD(27, "mbDead", 0x041f7574, 0xbcd, BOOL_ATTR)
    ADD(28, "mbDrone", 0x04cc2134, 0xbce, BOOL_ATTR)
    ADD(29, "mStance", 0x052d8b08, 0xb24, UINT_ATTR, SetDefault_00c9f080, &cVehicle_sStanceDefault, 0)
    ADD(30, "mLocomotionHint", 0x05b56c0d, 0xaf8, UINT_ATTR)
    ADD(31, "mpHitSphere", 0x065bcd6f, 0xcfc, Read_00bd0cb0, Write_00bca960, ReadText_00c2e4e0,
            WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
}

}  // namespace Simulator
