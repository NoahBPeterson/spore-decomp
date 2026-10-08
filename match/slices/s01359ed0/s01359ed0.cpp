// @ 0x0135a630  $E414: dynamic initializer of the Simulator::cDefaultToolProjectile serializer attribute
// table (20 Simulator::Attribute records, 0x3c bytes each, at 0x0157d890..0x0157dd4b).
//
// Same record layout and construction as the cGameDataUFO / cCommEvent tables (s013388f0, s01315a50):
// name, id, member offset, three uninitialized fields, pCurrentObject (+0x18) = 0, set-default
// callback (+0x1c) = 0, the offset function (0x00692ca0) and the read/write/readText/writeText/
// validate/toXml callbacks. Member names and offsets agree with ModAPI cDefaultToolProjectile.h
// (mTool 0x518, mPrevPosition 0x520, mMinDamage 0x52c, mMaxDamage 0x530, mExplosionRadius 0x534,
// mDamageType 0x538, mProjectileScale 0x53c, mBombPhase 0x544, mPhaseTimer 0x548, mDamagedObjects 0x570,
// mTargetPoint 0x59c, mStrikeType 0x5d0, mpTarget 0x5d8, mWaveFrontTargetCities 0x5dc). Every record is
// built in one reused 0x3c-byte stack temp and copied (rep movsd) into the table.
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
class cWeapon;          // ModAPI cSpaceToolData
class cGameData;
class cSpatialObject;

// Per-type template instances (folded by the linker to one address each).
// 0x00572810: 4-byte raw read
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
// 0x00572840: 4-byte integer write
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
// 0x00b1fbf0: AlwaysValid<T> (return true) for every plain-value type
template<typename T> bool AlwaysValid();
// 0x00692ff0 / 0x00694ee0: text reader / writer of the int rows (per-type instances)
template<typename T> void ReadTextInt(const string8& text, void* pData);
template<typename T> void WriteTextInt(char* pBuffer, void* pData);

// Tags for the int rows: their per-type callbacks are distinct template instances.
struct Int_mMaxDamage;
struct Int_mMinDamage;
struct Int_mBombPhase;
struct Int_mDamageType;
struct Int_mTargetDamagePointId;
struct Int_mStrikeType;

bool Read_00aca060(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
bool Read_00bceb00(ISerializerReadStream* pStream, void* pData);
bool Read_00bdc650(ISerializerReadStream* pStream, void* pData);
bool Read_00bf3ea0(ISerializerReadStream* pStream, void* pData);
bool Read_00cbb4c0(ISerializerReadStream* pStream, void* pData);

bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00bd1780(ISerializerWriteStream* pStream, void* pData);
bool Write_00bdd350(ISerializerWriteStream* pStream, void* pData);
bool Write_00cbad90(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692fd0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ec0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);

bool Validate_00ae3310();
bool Validate_00b6f550();
bool Validate_00b6f860();
bool Validate_00bf2670();
bool Validate_00c87090();

bool ToXml_00595a70(void* pData, const char* pName, int depth);
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
// 0x0057cde0 as per-type instances (the later int rows; only the first two rows share one copy)
template<typename T> bool ToXmlIntT(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00cbb590(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cDefaultToolProjectile_sAttributes[20];   // 0x0157d890

#define INTX_ATTR(T) Read4<T>, Write4<int>, ReadTextInt<T>, WriteTextInt<T>, AlwaysValid<T>, ToXmlIntT<T>
#define INT_ATTR(T) Read4<T>, Write4<int>, ReadTextInt<T>, WriteTextInt<T>, AlwaysValid<T>, ToXml_0057cde0
#define FLOAT_ATTR  Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define VEC3_ATTR   Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0
#define UINT64_ATTR Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0, AlwaysValid<uint64_t>, ToXml_00595a70
#define PTR_ATTR(T, R, W, V)  /* T: pointee, for reading only */ R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050
#define PTRX_ATTR(R, W, V, X) R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, X

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cDefaultToolProjectile_sAttributes[IDX] = a; }

// @ 0x0135a630
void InitDefaultToolProjectileAttributes()
{
    ADD(0,  "mMaxDamage", 0x03212e08, 0x530, INT_ATTR(Int_mMaxDamage))
    ADD(1,  "mMinDamage", 0x03212e09, 0x52c, INT_ATTR(Int_mMinDamage))
    ADD(2,  "mTool", 0x03212e0a, 0x518, PTR_ATTR(cWeapon, Read_00bceb00, Write_00bd1780, Validate_00c87090))
    ADD(3,  "mPrevPosition", 0x03212e0b, 0x520, VEC3_ATTR)
    ADD(4,  "mExplosionPoint", 0x03212e0c, 0x58c, VEC3_ATTR)
    ADD(5,  "mTargetOffset", 0x03212e0d, 0x508, VEC3_ATTR)
    ADD(6,  "mExplosionRadius", 0x03212e0e, 0x534, FLOAT_ATTR)
    ADD(7,  "mCurrentExplosionRadius", 0x03212e0f, 0x540, FLOAT_ATTR)
    ADD(8,  "mTimeOfLastDamageCheck", 0x03212e10, 0x568, UINT64_ATTR)
    ADD(9,  "mBombPhase", 0x03212e11, 0x544, INTX_ATTR(Int_mBombPhase))
    ADD(10, "mDamageType", 0x0679bfa0, 0x538, INTX_ATTR(Int_mDamageType))
    ADD(11, "mProjectileScale", 0x0679c043, 0x53c, FLOAT_ATTR)
    ADD(12, "mPhaseTimer", 0x0679c063, 0x548, PTRX_ATTR(Read_00ae3470, Write_00ae3490, Validate_00ae3310, ToXml_00ac8050))
    ADD(13, "mTargetDamagePointId", 0x0679c095, 0x598, INTX_ATTR(Int_mTargetDamagePointId))
    ADD(14, "mTargetPoint", 0x0679c0b5, 0x59c, VEC3_ATTR)
    ADD(15, "mStrikeType", 0x0679c1b3, 0x5d0, INTX_ATTR(Int_mStrikeType))
    ADD(16, "mTargetStruck", 0x0679c1e6, 0x5d4, PTR_ATTR(cGameData, Read_00aca060, Write_00bca960, Validate_00b6f550))
    ADD(17, "mpTarget", 0x0679c218, 0x5d8, PTR_ATTR(cSpatialObject, Read_00bdc650, Write_00bdd350, Validate_00b6f550))
    ADD(18, "mWaveFrontTargetCities", 0x0679c258, 0x5dc, PTRX_ATTR(Read_00bf3ea0, Write_00aca730, Validate_00b6f860, ToXml_00c6c390))
    ADD(19, "mDamagedObjects", 0x0679c2c1, 0x570, PTRX_ATTR(Read_00cbb4c0, Write_00cbad90, Validate_00bf2670, ToXml_00cbb590))
}

}  // namespace Simulator
