// Slice s01318c70 -- dynamic initializers of five Simulator::Attribute serializer
// tables plus one small global-object initializer.
//
//   0x0131aa90  SP::cGameNounManager-adjacent global at 0x0167c988 (ctor + vtable store
//               + atexit of the static destructor at 0x013c1ff0).
//   0x01318c70  SP::cFruitManager      table, 10 records at 0x01567a80
//               (mFlags, mFruitPickMethod, mPickableTreeFruit, mFruitPool, mFruitGroupPool,
//                mActiveOnGroundFruit, mFruitGroupMultiMap, mRemovedFruitGroupMultiMap,
//                mTreePickTypes, mTreeClumpDataMap).  The class owns the
//               "Simulator/SubSystem/FruitManager" subsystem (s00b60d80) and its
//               SerializeMgr (0x00b0a040) serializes this table.
//   0x013194a0  Simulator::cGameData   table,  5 records at 0x01567e48
//               (registered as L"cGameData" by 0x00beb6d0).
//   0x0131aac0  SP::cGameNounManager   table,  7 records at 0x015685a8
//               (mAvatar 0x54, mAvatarHerd 0x58, mPosseMembers 0x5c, mpPlayerTribe 0x70,
//                mpPlayer 0x74, mPoliticalMap 0xd0, cGameData::sInstanceIDGenerator static).
//   0x0131ad80  SP::cGameNounManager variant with mNouns (0x78) + the seven records
//               above, 8 records at 0x01568788.
//   0x0131b210  game-data save/version table, 7 records at 0x01568b08
//               (mFileVersionMajor/Minor, mObjectCountMap, mTimeStamp, mGameMode,
//                mbSnapshot, mCurrentPlanetKey) plus two global stores.
//
// Every serializer record is 0x3c bytes (15 dwords) laid out exactly like
// s0132cde0 / s0137ef90: name, id, offset, three untouched dwords, pCurrentObject,
// setDefaultFunction, offsetFunction, read/write/readText/writeText/validate/toXml.
// Each record is built in one reused 0x3c-byte stack temp and copied into the table with
// `rep movsd`.  The three untouched dwords are deliberately left uninitialised in the
// constructor so cl emits the original write pattern.  Callbacks that are per-type
// template instances in the original (folded by the linker to one address) are declared as
// templates so cl sees distinct symbols.  Ids and callbacks were read off the initializer.
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
    Attribute() {}

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

// Per-type template instances (folded by the linker to one address each).
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
template<typename T> void ReadTextInt(const string8& text, void* pData);          // 0x00693090
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0

// Per-record callback instances used only by the game-data snapshot table (0x0131b210).
// The original compiler materialises every one of these callbacks as an immediate on each
// record instead of caching it in a callee-saved register, so each occurrence is given its
// own symbol (the addresses are identical in the original and are masked on both sides).
template<int N> bool Read4i(ISerializerReadStream* pStream, void* pData);
template<int N> bool Write4i(ISerializerWriteStream* pStream, void* pData);
template<int N> void ReadTexti(const string8& text, void* pData);
template<int N> void WriteTexti(char* pBuffer, void* pData);
template<int N> bool AlwaysValidi();
template<int N> bool ToXmli(void* pData, const char* pName, int depth);

// Read callbacks.
bool Read_00b00430(ISerializerReadStream* pStream, void* pData);
bool Read_00b05de0(ISerializerReadStream* pStream, void* pData);
bool Read_00b05ec0(ISerializerReadStream* pStream, void* pData);
bool Read_00b05fa0(ISerializerReadStream* pStream, void* pData);
bool Read_00b0c730(ISerializerReadStream* pStream, void* pData);
bool Read_00b20510(ISerializerReadStream* pStream, void* pData);
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
bool Read_00b20570(ISerializerReadStream* pStream, void* pData);
bool Read_00b21e60(ISerializerReadStream* pStream, void* pData);
bool Read_00b26970(ISerializerReadStream* pStream, void* pData);
bool Read_00b1fbf0(ISerializerReadStream* pStream, void* pData);
bool Read_00aca060(ISerializerReadStream* pStream, void* pData);
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);
bool Read_00acdf10(ISerializerReadStream* pStream, void* pData);
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
bool Read_00bab620(ISerializerReadStream* pStream, void* pData);

// Write callbacks.
bool Write_00b02570(ISerializerWriteStream* pStream, void* pData);
bool Write_00b02630(ISerializerWriteStream* pStream, void* pData);
bool Write_00b035b0(ISerializerWriteStream* pStream, void* pData);
bool Write_00b26990(ISerializerWriteStream* pStream, void* pData);
bool Write_00b1fbf0(ISerializerWriteStream* pStream, void* pData);
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
bool Write_00ba7590(ISerializerWriteStream* pStream, void* pData);
bool Write_00ba94e0(ISerializerWriteStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);

// ReadText callbacks.
void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

// WriteText callbacks.
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

// Validate callbacks.
bool Validate_00b6f550();
bool Validate_00b6f860();
bool Validate_00b004e0();
bool Validate_00b00520();
bool Validate_00b20230();
bool Validate_00ba7450();
bool Validate_00d011e0();

// ToXml callbacks.
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
bool ToXml_00d022e0(void* pData, const char* pName, int depth);
bool ToXml_00b04120(void* pData, const char* pName, int depth);
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
bool ToXml_00fe4be0(void* pData, const char* pName, int depth);

// SetDefault callbacks.
void SetDefault_00b269b0(Attribute* pAttr);
void SetDefault_00b269d0(Attribute* pAttr);

struct AttrSlot { uint32_t d[15]; };

extern AttrSlot FruitMgr_sAttributes[10];              // 0x01567a80
extern AttrSlot GameData_sAttributes[5];               // 0x01567e48
extern AttrSlot GameNounManager_sAttributes[7];        // 0x015685a8
extern AttrSlot GameNounManagerEx_sAttributes[8];      // 0x01568788
extern AttrSlot GameSnapshot_sAttributes[7];           // 0x01568b08

// Class static registered by the cGameNounManager table.
extern int GameData_sInstanceIDGenerator;              // 0x0167be28

#define INT_ATTR      Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define SHORT_ATTR    Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0
#define BOOL_ATTR     Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define STATIC_INT_ATTR  Read4<int>, Write4<int>, ReadTextInt<int>, WriteText_00694f00, AlwaysValid<int>

#define FLAGS_ATTR    Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
#define TREE_OBJ_ATTR Read_00b05de0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
#define TREE_OBJ2_ATTR Read_00b05ec0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
#define MULTIMAP_ATTR Read_00b05fa0, Write_00b035b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b004e0, ToXml_00d022e0
#define CLUMP_ATTR    Read_00b0c730, Write_00b02630, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b00520, ToXml_00b04120
#define OWNER_ATTR    Read_00aca060, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
#define AVATAR_ATTR   Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
#define AVATARHERD_ATTR Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
#define PTRIBE_ATTR   Read_00aca090, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
#define PPLAYER_ATTR  Read_00b20570, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
#define POSSE_ATTR    Read_00acdf10, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
#define POLMAP_ATTR   Read_00b21e60, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0
#define NOUNS_ATTR    Read_00b1fbf0, Write_00b1fbf0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b20230, ToXml_00ac8050
#define OBJCOUNT_ATTR Read_00bab620, Write_00ba7590, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00d011e0, ToXml_00fe4be0
#define TIMESTAMP_ATTR Read_00b26970, Write_00b26990, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
#define PLANETKEY_ATTR Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<int>, ToXml_00ae5720

#define ADD_FRUIT(IDX, ...)    { Attribute a(__VA_ARGS__); *(Attribute*)&FruitMgr_sAttributes[IDX] = a; }
#define ADD_GAMEDATA(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&GameData_sAttributes[IDX] = a; }
#define ADD_GNM(IDX, ...)      { Attribute a(__VA_ARGS__); *(Attribute*)&GameNounManager_sAttributes[IDX] = a; }
#define ADD_GNMX(IDX, ...)     { Attribute a(__VA_ARGS__); *(Attribute*)&GameNounManagerEx_sAttributes[IDX] = a; }
#define ADD_SNAP(IDX, ...)     { Attribute a(__VA_ARGS__); *(Attribute*)&GameSnapshot_sAttributes[IDX] = a; }

// @ 0x01318c70
void InitFruitManagerAttributes()
{
    ADD_FRUIT(0, "mFlags", 0x3fe80a6, 0x1ba18c, FLAGS_ATTR)
    ADD_FRUIT(1, "mFruitPickMethod", 0x3fe820a, 0x1b8e10, INT_ATTR)
    ADD_FRUIT(2, "mPickableTreeFruit", 0x3fe823c, 0x1b8e14, TREE_OBJ_ATTR)
    ADD_FRUIT(3, "mFruitPool", 0x3fe8263, 0x1b8f44, TREE_OBJ_ATTR)
    ADD_FRUIT(4, "mFruitGroupPool", 0x5879e4a, 0x1b9174, TREE_OBJ2_ATTR)
    ADD_FRUIT(5, "mActiveOnGroundFruit", 0x42b920f, 0x1b905c, TREE_OBJ_ATTR)
    ADD_FRUIT(6, "mFruitGroupMultiMap", 0x4bda148, 0x34, MULTIMAP_ATTR)
    ADD_FRUIT(7, "mRemovedFruitGroupMultiMap", 0x4bda14a, 0x165a0, MULTIMAP_ATTR)
    ADD_FRUIT(8, "mTreePickTypes", 0x5ac78a8, 0x1659c, SHORT_ATTR)
    ADD_FRUIT(9, "mTreeClumpDataMap", 0x626e1fc, 0x1e5f0, CLUMP_ATTR)
}

// @ 0x013194a0
void InitGameDataAttributes()
{
    ADD_GAMEDATA(0, "mpGameDataOwner", 0x240e421, 0x2c, OWNER_ATTR)
    ADD_GAMEDATA(1, "mIsDestroyed", 0x240e422, 0x21, BOOL_ATTR)
    ADD_GAMEDATA(2, "mPoliticalID", 0x240e423, 0x30, SHORT_ATTR)
    ADD_GAMEDATA(3, "mDefinitionID", 0x2e9efd3, 0x28, SHORT_ATTR)
    ADD_GAMEDATA(4, "mID", 0x3cdd54b, 0x24, SHORT_ATTR)
}

// @ 0x0131aac0
void InitGameNounManagerAttributes()
{
    ADD_GNM(0, "mAvatar", 0x222ceb7, 0x54, AVATAR_ATTR)
    ADD_GNM(1, "mAvatarHerd", 0x52aea77b, 0x58, AVATARHERD_ATTR)
    ADD_GNM(2, "mPosseMembers", 0xd26a1d6f, 0x5c, POSSE_ATTR)
    ADD_GNM(3, "mpPlayerTribe", 0x222ceb9, 0x70, PTRIBE_ATTR)
    ADD_GNM(4, "mpPlayer", 0x2c215c5, 0x74, PPLAYER_ATTR)
    ADD_GNM(5, "mPoliticalMap", 0x2cb7255, 0xd0, POLMAP_ATTR)
    ADD_GNM(6, "cGameData::sInstanceIDGenerator", 0x3cdd5c7, &GameData_sInstanceIDGenerator, STATIC_INT_ATTR)
}

// @ 0x0131ad80
void InitGameNounManagerExAttributes()
{
    ADD_GNMX(0, "mNouns", 0x222cbfa, 0x78, NOUNS_ATTR)
    ADD_GNMX(1, "mAvatar", 0x222ceb7, 0x54, AVATAR_ATTR)
    ADD_GNMX(2, "mAvatarHerd", 0x52aea77b, 0x58, AVATARHERD_ATTR)
    ADD_GNMX(3, "mPosseMembers", 0xd26a1d6f, 0x5c, POSSE_ATTR)
    ADD_GNMX(4, "mpPlayerTribe", 0x222ceb9, 0x70, PTRIBE_ATTR)
    ADD_GNMX(5, "mpPlayer", 0x2c215c5, 0x74, PPLAYER_ATTR)
    ADD_GNMX(6, "mPoliticalMap", 0x2cb7255, 0xd0, POLMAP_ATTR)
    ADD_GNMX(7, "cGameData::sInstanceIDGenerator", 0x3cdd5c7, &GameData_sInstanceIDGenerator, STATIC_INT_ATTR)
}

// Game-data version / snapshot globals written alongside the table above.
extern const char* g_0167e064;    // 0x0167e064
extern uint8_t     g_0167e068;    // 0x0167e068
extern uint8_t     g_01654c01;    // 0x01654c01

// @ 0x0131b210
void InitGameSnapshotAttributes()
{
    ADD_SNAP(0, "mFileVersionMajor", 0x4162d88, 0xc, Read4i<0>, Write4i<0>, ReadTexti<0>, WriteTexti<0>, AlwaysValidi<0>, ToXmli<0>)
    ADD_SNAP(1, "mFileVersionMinor", 0x4162d89, 0x10, Read4i<1>, Write4i<1>, ReadTexti<1>, WriteTexti<1>, AlwaysValidi<1>, ToXmli<1>)
    ADD_SNAP(2, "mObjectCountMap", 0x4162d8a, 0x14, Read_00bab620, Write_00ba7590, ReadTexti<2>, WriteTexti<2>, Validate_00d011e0, ToXml_00fe4be0)
    ADD_SNAP(3, "mTimeStamp", 0x4162d8b, 0x30, Read_00b26970, Write_00b26990, ReadTexti<3>, WriteTexti<3>, AlwaysValidi<3>, ToXml_00ac8050)
    {
        Attribute a;
        a.name = "mGameMode";
        a.id = 0x4162d8c;
        a.pCurrentObject = 0;
        a.setDefaultFunction = SetDefault_00b269b0;
        a.offsetFunction = DefaultOffset;
        a.readFunction = Read4i<4>;
        a.writeFunction = Write4i<4>;
        a.readTextFunction = ReadText_00692ff0;
        a.writeTextFunction = WriteText_00694ee0;
        a.validateFunction = AlwaysValidi<4>;
        a.toXmlFunction = ToXml_0057cde0;
        g_0167e064 = (const char*)&g_01654c01;
        a.offset = 0x54;
        *(Attribute*)&GameSnapshot_sAttributes[4] = a;
    }
    ADD_SNAP(5, "mbSnapshot", 0x64bc1cf, 0x58, Read_00ac8750, Write_00ac8780, ReadTexti<5>, WriteText_00694fa0, AlwaysValidi<5>, ToXml_0057ce00, SetDefault_00b269d0)
    ADD_SNAP(6, "mCurrentPlanetKey", 0x64be534, 0x5c, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValidi<6>, ToXml_00ae5720)
    g_0167e068 = 0;
}

}  // namespace Simulator

// ---------------------------------------------------------------------------
// 0x0131aa90: dynamic initializer of the global object at 0x0167c988.
// The object is constructed (base ctor 0x00b63bd0), its vtable pointer is set to
// 0x0145e9a8, a second global at 0x0167dae0 is cleared, and the object's static
// destructor 0x013c1ff0 is registered with atexit.
// ---------------------------------------------------------------------------

struct Obj_167c988
{
    void* vptr;                 // 0x00
    void Ctor();                // 0x00b63bd0
};

extern Obj_167c988 g_167c988;   // 0x0167c988
extern uint32_t    g_167dae0;   // 0x0167dae0
extern void*       g_vtable_145e9a8;  // 0x0145e9a8
void FUN_013c1ff0();            // 0x013c1ff0
extern "C" int atexit(void (*pfn)(void));   // 0x011e07ef

// @ 0x0131aa90
void InitGlobal_167c988()
{
    g_167c988.Ctor();
    g_167c988.vptr = &g_vtable_145e9a8;
    g_167dae0 = 0;
    atexit(FUN_013c1ff0);
}