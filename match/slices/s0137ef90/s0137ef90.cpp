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

inline void* operator new(unsigned int, void* p) { return p; }

namespace EA {
namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t basis, int lower); // 0x00932e80
}

class Stopwatch {
public:
    Stopwatch(int period, bool start);              // 0x0093a560
};

class LimitStopwatch : public Stopwatch {
public:
    void SetTimeLimit(uint32_t limit, bool start);  // 0x0093a480
};
}

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
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);
bool Read_00eae8a0(ISerializerReadStream* pStream, void* pData);
bool Read_00eae9b0(ISerializerReadStream* pStream, void* pData);
bool Read_00eaea80(ISerializerReadStream* pStream, void* pData);
bool Read_00c33820(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00e5c660(ISerializerWriteStream* pStream, void* pData);
bool Write_00e51250(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00f26ca0(ISerializerWriteStream* pStream, void* pData);
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00c332a0(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);
void ReadText_00694c80(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);
void WriteText_00694c10(char* pBuffer, void* pData);

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00b1fbf0(void* pData, const char* pName, int depth);
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);
bool ToXml_0103c3a0(void* pData, const char* pName, int depth);
bool ToXml_00eafcf0(void* pData, const char* pName, int depth);
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
bool Validate_00c31ca0();

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot cCellSerialiazibleData_sAttributes[22];   // 0x015a7e38
extern AttrSlot cMusicData_sAttributes[8];                // 0x015a9198

#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define SHORT_ATTR Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCellSerialiazibleData_sAttributes[IDX] = a; }
#define ADD_MUSIC(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cMusicData_sAttributes[IDX] = a; }

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

// @ 0x01387660
void InitMusicDataAttributes()
{
    ADD_MUSIC(0, "mName", 0x511dfb9, 0x178, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, AlwaysValid<int>, ToXml_00acbbc0)
    ADD_MUSIC(1, "mDescription", 0x511dfc3, 0x188, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, AlwaysValid<int>, ToXml_00acbbc0)
    ADD_MUSIC(2, "mVolumes", 0x4d81cfe, 0x198, Read_00eae8a0, Write_00f26ca0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_0103c3a0)
    ADD_MUSIC(3, "mAmbienceHistory", 0x4226180, 0x1b8, Read_00c33820, Write_00c332a0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00c31ca0, ToXml_00eafcf0)
    ADD_MUSIC(4, "mRhythm", 0x4226186, 0x1c4, INT_ATTR)
    ADD_MUSIC(5, "mInstrument", 0x4226189, 0x1c8, INT_ATTR)
    ADD_MUSIC(6, "mNotePitches", 0x4e551ee, 0x1cc, Read_00eae9b0, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00eafe40)
    ADD_MUSIC(7, "mNoteDurations", 0x4f7c02d, 0x1e0, Read_00eaea80, Write_00f26ca0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_0103c3a0)
}

// ---------------------------------------------------------------------------
// Static-initializer helpers in the same module.
// ---------------------------------------------------------------------------

extern "C" int __cdecl atexit(void (__cdecl*)(void));   // 0x011e07ef

void FUN_013c7db0();                                    // 0x013c7db0
void FUN_013c7e80();                                    // 0x013c7e80
void FUN_013c8c90();                                    // 0x013c8c90
void FUN_013c8f90();                                    // 0x013c8f90

// Array of six Simulator::cSPCreatureNestMission objects at 0x016b3de8.
// cSPCreatureNestMission is the multiple-inheritance subclass; its inlined constructor
// calls the cCreatureTutorialMission base constructor and then replaces the three vtables.
class cCreatureTutorialMission {
public:
    cCreatureTutorialMission();                    // 0x00c2f340
    void* mpVtable0;                               // +0x00
    void* mpVtable4;                               // +0x04
    char  mData08[0x2c];                           // +0x08
    void* mpVtable34;                              // +0x34
    char  mData38[0x60];                           // +0x38
};

class cSPCreatureNestMission : public cCreatureTutorialMission {
};

extern cSPCreatureNestMission g_nestMissions[6];   // 0x016b3de8

// @ 0x0137f820
void InitNestMissions()
{
    cSPCreatureNestMission* p = g_nestMissions;
    int i = 5;
    do {
        __assume(p != 0);
        new (p) cSPCreatureNestMission();
        p->mpVtable0  = (void*)0x1485240;
        p->mpVtable4  = (void*)0x148522c;
        p->mpVtable34 = (void*)0x148521c;
        ++p;
    } while (--i >= 0);
    atexit(FUN_013c7db0);
}

extern uint32_t g_zeroedArray[0x40];               // 0x016b4178

// @ 0x0137f8d0
void InitZeroedArray()
{
    for (int i = 0; i < 0x40; ++i)
        g_zeroedArray[i] = 0;
    atexit(FUN_013c7e80);
}

// Cell collision sound-pair table (10 records, 0x18 bytes each) at 0x015a8448.
// The last two words are material/impact indices; the first four are the FNV keys and
// display names of the impact and drag sound resources.
struct CollisionSoundPair {
    uint32_t    mImpactHash;
    const char* mpImpactSound;
    uint32_t    mDragHash;
    const char* mpDragSound;
    uint32_t    mImpactIndex;
    uint32_t    mDragIndex;
};

extern CollisionSoundPair g_cellCollisionSounds[10];  // 0x015a8448

// @ 0x0137f950
void InitCellCollisionSounds()
{
    g_cellCollisionSounds[0].mImpactHash = EA::Hash::FNV1_String8("cell_collision_creature_creature_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[0].mpImpactSound = "cell_collision_creature_creature_impact";
    g_cellCollisionSounds[0].mDragHash = EA::Hash::FNV1_String8("cell_collision_creature_creature_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[0].mpDragSound = "cell_collision_creature_creature_drag";
    g_cellCollisionSounds[0].mImpactIndex = 2;
    g_cellCollisionSounds[0].mDragIndex = 1;

    g_cellCollisionSounds[1].mImpactHash = EA::Hash::FNV1_String8("cell_collision_creature_plant_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[1].mpImpactSound = "cell_collision_creature_plant_impact";
    g_cellCollisionSounds[1].mDragHash = EA::Hash::FNV1_String8("cell_collision_creature_plant_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[1].mpDragSound = "cell_collision_creature_plant_drag";
    g_cellCollisionSounds[1].mImpactIndex = 2;
    g_cellCollisionSounds[1].mDragIndex = 2;

    g_cellCollisionSounds[2].mImpactHash = EA::Hash::FNV1_String8("cell_collision_plant_plant_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[2].mpImpactSound = "cell_collision_plant_plant_impact";
    g_cellCollisionSounds[2].mDragHash = EA::Hash::FNV1_String8("cell_collision_plant_plant_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[2].mpDragSound = "cell_collision_plant_plant_drag";
    g_cellCollisionSounds[2].mImpactIndex = 3;
    g_cellCollisionSounds[2].mDragIndex = 1;

    g_cellCollisionSounds[3].mImpactHash = EA::Hash::FNV1_String8("cell_collision_creature_rock_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[3].mpImpactSound = "cell_collision_creature_rock_impact";
    g_cellCollisionSounds[3].mDragHash = EA::Hash::FNV1_String8("cell_collision_creature_rock_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[3].mpDragSound = "cell_collision_creature_rock_drag";
    g_cellCollisionSounds[3].mImpactIndex = 3;
    g_cellCollisionSounds[3].mDragIndex = 2;

    g_cellCollisionSounds[4].mImpactHash = EA::Hash::FNV1_String8("cell_collision_plant_rock_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[4].mpImpactSound = "cell_collision_plant_rock_impact";
    g_cellCollisionSounds[4].mDragHash = EA::Hash::FNV1_String8("cell_collision_plant_rock_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[4].mpDragSound = "cell_collision_plant_rock_drag";
    g_cellCollisionSounds[4].mImpactIndex = 3;
    g_cellCollisionSounds[4].mDragIndex = 3;

    g_cellCollisionSounds[5].mImpactHash = EA::Hash::FNV1_String8("cell_collision_rock_rock_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[5].mpImpactSound = "cell_collision_rock_rock_impact";
    g_cellCollisionSounds[5].mDragHash = EA::Hash::FNV1_String8("cell_collision_rock_rock_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[5].mpDragSound = "cell_collision_rock_rock_drag";
    g_cellCollisionSounds[5].mImpactIndex = 4;
    g_cellCollisionSounds[5].mDragIndex = 1;

    g_cellCollisionSounds[6].mImpactHash = EA::Hash::FNV1_String8("cell_collision_creature_bubble_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[6].mpImpactSound = "cell_collision_creature_bubble_impact";
    g_cellCollisionSounds[6].mDragHash = EA::Hash::FNV1_String8("cell_collision_creature_bubble_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[6].mpDragSound = "cell_collision_creature_bubble_drag";
    g_cellCollisionSounds[6].mImpactIndex = 4;
    g_cellCollisionSounds[6].mDragIndex = 2;

    g_cellCollisionSounds[7].mImpactHash = EA::Hash::FNV1_String8("cell_collision_plant_bubble_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[7].mpImpactSound = "cell_collision_plant_bubble_impact";
    g_cellCollisionSounds[7].mDragHash = EA::Hash::FNV1_String8("cell_collision_plant_bubble_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[7].mpDragSound = "cell_collision_plant_bubble_drag";
    g_cellCollisionSounds[7].mImpactIndex = 4;
    g_cellCollisionSounds[7].mDragIndex = 3;

    g_cellCollisionSounds[8].mImpactHash = EA::Hash::FNV1_String8("cell_collision_rock_bubble_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[8].mpImpactSound = "cell_collision_rock_bubble_impact";
    g_cellCollisionSounds[8].mDragHash = EA::Hash::FNV1_String8("cell_collision_rock_bubble_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[8].mpDragSound = "cell_collision_rock_bubble_drag";
    g_cellCollisionSounds[8].mImpactIndex = 4;
    g_cellCollisionSounds[8].mDragIndex = 4;

    g_cellCollisionSounds[9].mImpactHash = EA::Hash::FNV1_String8("cell_collision_bubble_bubble_impact", 0x811c9dc5, 1);
    g_cellCollisionSounds[9].mpImpactSound = "cell_collision_bubble_bubble_impact";
    g_cellCollisionSounds[9].mDragHash = EA::Hash::FNV1_String8("cell_collision_bubble_bubble_drag", 0x811c9dc5, 1);
    g_cellCollisionSounds[9].mpDragSound = "cell_collision_bubble_bubble_drag";
}

// MyCaptainLevels registry node at 0x016c7a18; +0x08 is the previous list head.
struct MyCaptainLevels {
    void*             mpVtable;                    // +0x00
    uint32_t          mNameHash;                   // +0x04
    MyCaptainLevels*  mpNext;                      // +0x08
    uint32_t          mField0c;                    // +0x0c
    uint32_t          mField10;                    // +0x10
};

extern MyCaptainLevels  g_myCaptainLevels;         // 0x016c7a18
extern MyCaptainLevels* g_myCaptainLevelsHead;     // 0x015aca38

// @ 0x01388f50
void InitMyCaptainLevels()
{
    g_myCaptainLevels.mNameHash = EA::Hash::FNV1_String8("MyCaptainLevels", 0x811c9dc5, 1);
    g_myCaptainLevels.mpNext = g_myCaptainLevelsHead;
    g_myCaptainLevelsHead = &g_myCaptainLevels;
    g_myCaptainLevels.mpVtable = (void*)0x148ad9c;
    g_myCaptainLevels.mField0c = 0;
    g_myCaptainLevels.mField10 = 0;
    atexit(FUN_013c8c90);
}

extern ::EA::LimitStopwatch g_limitStopwatch;      // 0x016c7b60

// @ 0x01389390
void InitLimitStopwatch()
{
    new (&g_limitStopwatch) ::EA::Stopwatch(5, false);
    g_limitStopwatch.SetTimeLimit(0, false);
    atexit(FUN_013c8f90);
}

}  // namespace Simulator
