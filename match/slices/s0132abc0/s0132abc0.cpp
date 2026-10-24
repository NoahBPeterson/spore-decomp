// Dynamic initializers of two Simulator serializer attribute tables:
// SP::cCelestialBody (6 records, 0x3c bytes each, at 0x0156df10..0x0156e172) and
// SP::cCity (6 records at 0x0156e2a0..0x0156e502).
//
// Every record is constructed in one reused 0x3c-byte stack temporary by
// Simulator::Attribute's constructor and copied into its table slot with
// rep movsd.  Same construction as the sibling tables in s01320f20 (planet),
// s013249a0 (star manager) and s013388f0 (UFO): callbacks are declared by
// original address and the record is assigned through the AttrSlot cast.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

namespace eastl { struct string8; }
typedef eastl::string8 string8;

// ---------------------------------------------------------------------------
// Serializer callback signatures (only the pointer types matter to the table).
// ---------------------------------------------------------------------------
typedef bool (*ReadFunction_t)(void*, void*);
typedef bool (*WriteFunction_t)(void*, void*);
typedef void (*ReadTextFunction_t)(const string8&, void*);
typedef void (*WriteTextFunction_t)(char*, void*);
typedef bool (*ValidateFunction_t)();
typedef bool (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(void*);
typedef void (*SetDefaultFunction_t)(void*);

void* DefaultOffset(void* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset

struct Attribute
{
    // Offset is written last, after every callback slot -- matches the binary.
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
    /* 0Ch */ int field_0C;   // not initialized by the constructor
    /* 10h */ int field_10;   // not initialized by the constructor
    /* 14h */ int field_14;   // not initialized by the constructor
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

// Callbacks, declared by original address (bodies live outside this slice).
bool Read_00572810(void*, void*);                                     // 0x00572810
bool Write_00572840(void*, void*);                                    // 0x00572840
void ReadText_00692ff0(const string8&, void*);                        // 0x00692ff0
void WriteText_00694ee0(char*, void*);                                // 0x00694ee0
// The default validator is a template instantiated once per attribute type; all
// the bodies are identical and the linker folds them onto 0x00b1fbf0.
struct TType{}; struct TPosition{}; struct TRotationRate{}; struct TName{}; struct THitSphereSize{};
struct TGateIndex{}; struct TAttackStateIdx{}; struct TAttackStateTime{}; struct TAttackerPoliticalID{}; struct TAttackers{}; struct THitSphere{};
template<typename T> bool Valid();                                    // 0x00b1fbf0
template<typename T> bool Read4(void*, void*);                        // 0x00572810
template<typename T> bool Write4(void*, void*);                       // 0x00572840
template<typename T> void ReadTextT(const string8&, void*);           // 0x00692ff0
template<typename T> void WriteTextT(char*, void*);                   // 0x00694ee0
template<typename T> bool ToXmlT(void*, const char*, int);            // 0x0057cde0

// The common reader/writer and the default validator / to-XML helpers of a whole
// run of attributes: one symbol each, so the compiler hoists them once per run.
bool Valid_00b1fbf0();                                                // 0x00b1fbf0
bool ToXml_0057cde0(void*, const char*, int);                         // 0x0057cde0

// One tag type per attribute table entry of the SP::cBuilding table.
struct TBld0{}; struct TBld1{}; struct TBld2{}; struct TBld3{}; struct TBld4{}; struct TBld5{};
struct TBld6{}; struct TBld7{}; struct TBld8{}; struct TBld9{}; struct TBld10{}; struct TBld11{}; struct TBld12{};

bool Read_00b8db30(void*, void*);                                     // 0x00b8db30
bool Write_00b8db50(void*, void*);                                    // 0x00b8db50
void ReadText_00c2e4e0(const string8&, void*);                        // 0x00c2e4e0
void WriteText_00692fb0(char*, void*);                                // 0x00692fb0
bool Valid_00b8db10();                                                // 0x00b8db10
bool ToXml_00ac8050(void*, const char*, int);                         // 0x00ac8050

bool Read_00b6e3a0(void*, void*);                                     // 0x00b6e3a0
bool Write_00ac88c0(void*, void*);                                    // 0x00ac88c0
void ReadText_006930f0(const string8&, void*);                        // 0x006930f0
void WriteText_00695010(char*, void*);                                // 0x00695010
bool ToXml_00acbba0(void*, const char*, int);                         // 0x00acbba0

bool Write_00ac88f0(void*, void*);                                    // 0x00ac88f0
void ReadText_006930b0(const string8&, void*);                        // 0x006930b0
void WriteText_00694fc0(char*, void*);                                // 0x00694fc0
bool ToXml_00acbb80(void*, const char*, int);                         // 0x00acbb80

bool Read_00ac87c0(void*, void*);                                     // 0x00ac87c0
bool Write_00ac87f0(void*, void*);                                    // 0x00ac87f0
void ReadText_00694c80(const string8&, void*);                        // 0x00694c80
void WriteText_00694c10(char*, void*);                                // 0x00694c10
bool ToXml_00acbbc0(void*, const char*, int);                         // 0x00acbbc0

bool Read_00bb9cd0(void*, void*);                                     // 0x00bb9cd0
bool Write_00bb9d00(void*, void*);                                    // 0x00bb9d00
void ReadText_00693070(const string8&, void*);                        // 0x00693070
void WriteText_00694f80(char*, void*);                                // 0x00694f80
bool ToXml_00595a50(void*, const char*, int);                         // 0x00595a50

void ReadText_00693090(const string8&, void*);                        // 0x00693090
void WriteText_00694f00(char*, void*);                                // 0x00694f00
bool ToXml_00675ca0(void*, const char*, int);                         // 0x00675ca0

bool Read_00be0810(void*, void*);                                     // 0x00be0810
bool Write_00aca730(void*, void*);                                    // 0x00aca730
bool Valid_00b6f860();                                                // 0x00b6f860
bool ToXml_00c6c390(void*, const char*, int);                         // 0x00c6c390

bool Read_00bd0cb0(void*, void*);                                     // 0x00bd0cb0
bool Write_00bca960(void*, void*);                                    // 0x00bca960
bool Valid_00b6f550();                                                // 0x00b6f550

// ---------------------------------------------------------------------------
// 0x0156df10: SP::cCelestialBody attribute table.
// ---------------------------------------------------------------------------
struct AttrSlot { uint32_t d[15]; };
extern AttrSlot sCelestialBodyAttributes[6];

#define ADD_ATTR(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }

// @ 0x0132b6b0
void FUN_0132b6b0()
{
    ADD_ATTR(sCelestialBodyAttributes, 0, "mType", 0x038cfe0e, 0x34, Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, Valid<TType>, ToXml_0057cde0)
    ADD_ATTR(sCelestialBodyAttributes, 1, "mOrbit", 0x038cfe26, 0x38, Read_00b8db30, Write_00b8db50, ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b8db10, ToXml_00ac8050)
    ADD_ATTR(sCelestialBodyAttributes, 2, "mPosition", 0x038cfe48, 0xa0, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, Valid<TPosition>, ToXml_00acbba0)
    ADD_ATTR(sCelestialBodyAttributes, 3, "mRotationRate", 0x038cfe5c, 0xac, Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<TRotationRate>, ToXml_00acbb80)
    ADD_ATTR(sCelestialBodyAttributes, 4, "mName", 0x038cfe6d, 0xb0, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, Valid<TName>, ToXml_00acbbc0)
    ADD_ATTR(sCelestialBodyAttributes, 5, "mHitSphereSize", 0x038e5030, 0xc8, Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<THitSphereSize>, ToXml_00acbb80)
}

// ---------------------------------------------------------------------------
// 0x0156e2a0: SP::cCity attribute table.
// ---------------------------------------------------------------------------
extern AttrSlot sCityAttributes[6];

// @ 0x0132cb50
void FUN_0132cb50()
{
    ADD_ATTR(sCityAttributes, 0, "mGateIndex", 0x03dea810, 0x1d4, Read_00bb9cd0, Write_00bb9d00, ReadText_00693070, WriteText_00694f80, Valid<TGateIndex>, ToXml_00595a50)
    ADD_ATTR(sCityAttributes, 1, "mAttackState", 0x03df32d5, 0x1d8, Read4<TAttackStateIdx>, Write4<TAttackStateIdx>, ReadTextT<TAttackStateIdx>, WriteTextT<TAttackStateIdx>, Valid<TAttackStateIdx>, ToXmlT<TAttackStateIdx>)
    ADD_ATTR(sCityAttributes, 2, "mAttackState", 0x03df32d6, 0x1d8, Read4<TAttackStateTime>, Write4<TAttackStateTime>, ReadTextT<TAttackStateTime>, WriteTextT<TAttackStateTime>, Valid<TAttackStateTime>, ToXmlT<TAttackStateTime>)
    ADD_ATTR(sCityAttributes, 3, "mAttackerPoliticalID", 0x03dad664, 0x1dc, Read4<TAttackerPoliticalID>, Write4<TAttackerPoliticalID>, ReadText_00693090, WriteText_00694f00, Valid<TAttackerPoliticalID>, ToXml_00675ca0)
    ADD_ATTR(sCityAttributes, 4, "mAttackers", 0x03e0c0b0, 0x1f4, Read_00be0810, Write_00aca730, ReadTextT<TAttackers>, WriteTextT<TAttackers>, Valid_00b6f860, ToXml_00c6c390)
    ADD_ATTR(sCityAttributes, 5, "mpHitSphere", 0x03df010d, 0x208, Read_00bd0cb0, Write_00bca960, ReadTextT<THitSphere>, WriteTextT<THitSphere>, Valid_00b6f550, ToXml_00ac8050)
}

// ---------------------------------------------------------------------------
// 0x0156d770: SP::cBuilding attribute table (13 records).
// Entries 1..4 share the common reader/writer pair 0x00c2e4e0 / 0x00692fb0 and
// entries 6..10 share the default validator 0x00b1fbf0 / to-XML 0x0057cde0, so
// those two runs keep one symbol per run and the compiler hoists it once.
// ---------------------------------------------------------------------------
extern AttrSlot sBuildingsAttributes[13];

// @ 0x0132abc0
void FUN_0132abc0()
{
    ADD_ATTR(sBuildingsAttributes, 0, "mIsOn", 0x02416eb8, 0x1f4, Read4<TBld0>, Write4<TBld0>, ReadTextT<TBld0>, WriteTextT<TBld0>, Valid<TBld0>, ToXmlT<TBld0>)              // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 1, "mpOwnerCity", 0x02416ebb, 0x1f0, Read4<TBld1>, Write4<TBld1>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld1>, ToXmlT<TBld1>)       // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingsAttributes, 2, "mEvents", 0x041614aa, 0x1f8, Read4<TBld2>, Write4<TBld2>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld2>, ToXmlT<TBld2>)           // 0xbd16d0 0xbd0bb0 0xc2e4e0 0x692fb0 0xbd0c80 0xbd2840
    ADD_ATTR(sBuildingsAttributes, 3, "mAttackTimer", 0x04ac7af1, 0x238, Read4<TBld3>, Write4<TBld3>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld3>, ToXmlT<TBld3>)       // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 4, "mDestroyTimer", 0x05b9555b, 0x258, Read4<TBld4>, Write4<TBld4>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld4>, ToXmlT<TBld4>)      // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 5, "mConnected", 0x04b74e33, 0x289, Read4<TBld5>, Write4<TBld5>, ReadTextT<TBld5>, WriteTextT<TBld5>, Valid<TBld5>, ToXmlT<TBld5>)           // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 6, "mEffectiveness", 0x04b74e34, 0x28c, Read4<TBld6>, Write4<TBld6>, ReadTextT<TBld6>, WriteTextT<TBld6>, Valid_00b1fbf0, ToXml_0057cde0)     // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 7, "mFreezeCount", 0x04b74e37, 0x290, Read4<TBld7>, Write4<TBld7>, ReadTextT<TBld7>, WriteTextT<TBld7>, Valid_00b1fbf0, ToXml_0057cde0)       // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 8, "mMoneyCount", 0x04efa697, 0x294, Read4<TBld8>, Write4<TBld8>, ReadTextT<TBld8>, WriteTextT<TBld8>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 9, "mHappyCount", 0x04efa698, 0x298, Read4<TBld9>, Write4<TBld9>, ReadTextT<TBld9>, WriteTextT<TBld9>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 10, "mUnhappyCount", 0x04efa699, 0x29c, Read4<TBld10>, Write4<TBld10>, ReadTextT<TBld10>, WriteTextT<TBld10>, Valid_00b1fbf0, ToXml_0057cde0)  // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 11, "mNormalModelKey", 0x05e4d3d3, 0x224, Read4<TBld11>, Write4<TBld11>, ReadTextT<TBld11>, WriteTextT<TBld11>, Valid<TBld11>, ToXmlT<TBld11>)  // 0xae3430 0xae3450 0x693150 0x695080 0xb1fbf0 0xae5720
    ADD_ATTR(sBuildingsAttributes, 12, "mbIrradiated", 0x05e4d3d4, 0x230, Read4<TBld12>, Write4<TBld12>, ReadTextT<TBld12>, WriteTextT<TBld12>, Valid<TBld12>, ToXmlT<TBld12>)     // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
}

// ---------------------------------------------------------------------------
// 0x0156dc20: SP::cBuilding weapon/attachment attribute table (10 records).
// Every record shares the common writer 0x00692fb0 (writeText) and the common
// 0x00ac8050 to-XML helper, so those two symbols stay shared and get hoisted;
// the per-entry reader / validator / to-XML are distinct instantiations.
// ---------------------------------------------------------------------------
struct TW0{}; struct TW1{}; struct TW2{}; struct TW3{}; struct TW4{};
struct TW5{}; struct TW6{}; struct TW7{}; struct TW8{}; struct TW9{};
extern AttrSlot sBuildingWeaponsAttributes[10];

// @ 0x0132b1f0
void FUN_0132b1f0()
{
    ADD_ATTR(sBuildingWeaponsAttributes, 0, "mpCity", 0x044585b1, 0x688, Read4<TW0>, Write4<TW0>, ReadTextT<TW0>, WriteText_00692fb0, Valid<TW0>, ToXml_00ac8050)                    // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 1, "mpWeapon", 0x044585b2, 0x68c, Read4<TW1>, Write4<TW1>, ReadTextT<TW1>, WriteText_00692fb0, Valid<TW1>, ToXml_00ac8050)                  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 2, "mpCivTurretWeapon", 0x04c5a1ef, 0x690, Read4<TW2>, Write4<TW2>, ReadTextT<TW2>, WriteText_00692fb0, Valid<TW2>, ToXml_00ac8050)         // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 3, "mpSpaceBeamWeapon", 0x04c5a1f5, 0x694, Read4<TW3>, Write4<TW3>, ReadTextT<TW3>, WriteText_00692fb0, Valid<TW3>, ToXml_00ac8050)          // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 4, "mpSpaceDefenseMissileWeapon", 0x05790752, 0x698, Read4<TW4>, Write4<TW4>, ReadTextT<TW4>, WriteText_00692fb0, Valid<TW4>, ToXml_00ac8050)  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 5, "mpSpaceTurretFlak", 0x0579fa14, 0x69c, Read4<TW5>, Write4<TW5>, ReadTextT<TW5>, WriteText_00692fb0, Valid<TW5>, ToXml_00ac8050)           // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 6, "mDestroyTimer", 0x04161444, 0x660, Read4<TW6>, Write4<TW6>, ReadTextT<TW6>, WriteText_00692fb0, Valid<TW6>, ToXml_00ac8050)             // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 7, "mFreezeCount", 0x04161445, 0x684, Read4<TW7>, Write4<TW7>, ReadTextT<TW7>, WriteTextT<TW7>, Valid<TW7>, ToXmlT<TW7>)                    // 0x572810 0x572840 0x692ff0 0x694ee0 0xb1fbf0 0x57cde0
    ADD_ATTR(sBuildingWeaponsAttributes, 8, "mpHitSphere", 0x04161446, 0x6a0, Read4<TW8>, Write4<TW8>, ReadTextT<TW8>, WriteText_00692fb0, Valid<TW8>, ToXml_00ac8050)                // 0xbd0cb0 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 9, "mpFacingTarget", 0x04161447, 0x6a4, Read4<TW9>, Write4<TW9>, ReadTextT<TW9>, WriteText_00692fb0, Valid<TW9>, ToXml_00ac8050)             // 0xbd0d50 0xbd17b0 0xc2e4e0 0x692fb0 0xbcd450 0xac8050
}