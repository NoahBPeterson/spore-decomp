// Slice s01397890 -- SP::Simulator::Attribute serializer-table dynamic
// initializers at 0x01397890, 0x01397ff0, 0x01398270 and 0x01398420.
//
// Every record is a 0x3c-byte Simulator::Attribute (name, id, member offset, three
// uninitialised words, pCurrentObject, set-default, the offset function 0x00692ca0 and
// the read/write/readText/writeText/validate/toXml callbacks).  Each record is built in
// one reused 0x3c-byte stack temp and copied into its table with `rep movsd`.
//
// Which callback constants cl keeps in a register across records depends on symbol
// identity, so every repeated callback gets its own declaration; only the offset
// function is shared by every record and only the validate/toXml slots of the
// 0x01397890 long and short groups are shared within their group (the original caches
// exactly those two in ebp/ebx).  Addresses are masked by the matcher, so the symbols
// are placeholders.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

class ISerializerReadStream;
class ISerializerWriteStream;
struct Attribute;

typedef bool  (*ReadFn)(ISerializerReadStream*, void*);
typedef bool  (*WriteFn)(ISerializerWriteStream*, void*);
typedef void  (*ReadTextFn)(const char*, void*);
typedef void  (*WriteTextFn)(char*, void*);
typedef bool  (*ValidateFn)();
typedef bool  (*ToXmlFn)(void*, const char*, int);
typedef void* (*OffsetFn)(Attribute*);

void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0

struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFn pRead, WriteFn pWrite, ReadTextFn pReadText,
              WriteTextFn pWriteText, ValidateFn pValidate, ToXmlFn pToXml)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
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
    /* 04h */ uint32_t    id;
    /* 08h */ uint32_t    offset;
    /* 0Ch */ int         field_0C;
    /* 10h */ int         field_10;
    /* 14h */ int         field_14;
    /* 18h */ void*       pCurrentObject;
    /* 1Ch */ void*       setDefaultFunction;
    /* 20h */ OffsetFn    offsetFunction;
    /* 24h */ ReadFn      readFunction;
    /* 28h */ WriteFn     writeFunction;
    /* 2Ch */ ReadTextFn  readTextFunction;
    /* 30h */ WriteTextFn writeTextFunction;
    /* 34h */ ValidateFn  validateFunction;
    /* 38h */ ToXmlFn     toXmlFunction;
};

struct AttrSlot { uint32_t d[15]; };

// --- table storage -------------------------------------------------------
extern AttrSlot gAttr01397890[19];
extern AttrSlot gAttr01397ff0[6];
extern AttrSlot gAttr01398270[4];
extern AttrSlot gAttr01398420[5];

// --- callback declarations ----------------------------------------------
bool F_01397890_0_0(ISerializerReadStream*, void*);
bool F_01397890_0_1(ISerializerWriteStream*, void*);
void F_01397890_0_2(const char*, void*);
void F_01397890_0_3(char*, void*);
bool F_01397890_0_4();
bool F_01397890_0_5(void*, const char*, int);
bool F_01397890_1_0(ISerializerReadStream*, void*);
bool F_01397890_1_1(ISerializerWriteStream*, void*);
void F_01397890_1_2(const char*, void*);
void F_01397890_1_3(char*, void*);
bool F_01397890_1_4();
bool F_01397890_1_5(void*, const char*, int);
bool F_01397890_2_0(ISerializerReadStream*, void*);
bool F_01397890_2_1(ISerializerWriteStream*, void*);
void F_01397890_2_2(const char*, void*);
void F_01397890_2_3(char*, void*);
bool F_01397890_2_4();
bool F_01397890_2_5(void*, const char*, int);
bool F_01397890_3_0(ISerializerReadStream*, void*);
bool F_01397890_3_1(ISerializerWriteStream*, void*);
void F_01397890_3_2(const char*, void*);
void F_01397890_3_3(char*, void*);
bool V_INT();
bool X_INT(void*, const char*, int);
void R_STL(const char*, void*);   // 0x00c2e4e0 shared readText, records 7..9
void W_STL(char*, void*);         // 0x00692fb0 shared writeText, records 7..9
bool F_01397890_4_0(ISerializerReadStream*, void*);
bool F_01397890_4_1(ISerializerWriteStream*, void*);
void F_01397890_4_2(const char*, void*);
void F_01397890_4_3(char*, void*);
bool F_01397890_5_0(ISerializerReadStream*, void*);
bool F_01397890_5_1(ISerializerWriteStream*, void*);
void F_01397890_5_2(const char*, void*);
void F_01397890_5_3(char*, void*);
bool F_01397890_6_0(ISerializerReadStream*, void*);
bool F_01397890_6_1(ISerializerWriteStream*, void*);
void F_01397890_6_2(const char*, void*);
void F_01397890_6_3(char*, void*);
bool F_01397890_6_4();
bool F_01397890_6_5(void*, const char*, int);
bool F_01397890_7_0(ISerializerReadStream*, void*);
bool F_01397890_7_1(ISerializerWriteStream*, void*);
void F_01397890_7_2(const char*, void*);
void F_01397890_7_3(char*, void*);
bool F_01397890_7_4();
bool F_01397890_7_5(void*, const char*, int);
bool F_01397890_8_0(ISerializerReadStream*, void*);
bool F_01397890_8_1(ISerializerWriteStream*, void*);
void F_01397890_8_2(const char*, void*);
void F_01397890_8_3(char*, void*);
bool F_01397890_8_4();
bool F_01397890_8_5(void*, const char*, int);
bool F_01397890_9_0(ISerializerReadStream*, void*);
bool F_01397890_9_1(ISerializerWriteStream*, void*);
void F_01397890_9_2(const char*, void*);
void F_01397890_9_3(char*, void*);
bool F_01397890_9_4();
bool F_01397890_9_5(void*, const char*, int);
bool F_01397890_10_0(ISerializerReadStream*, void*);
bool F_01397890_10_1(ISerializerWriteStream*, void*);
void F_01397890_10_2(const char*, void*);
void F_01397890_10_3(char*, void*);
bool V_SHRT();
bool X_SHRT(void*, const char*, int);
bool F_01397890_11_0(ISerializerReadStream*, void*);
bool F_01397890_11_1(ISerializerWriteStream*, void*);
void F_01397890_11_2(const char*, void*);
void F_01397890_11_3(char*, void*);
bool F_01397890_11_4();
bool F_01397890_11_5(void*, const char*, int);
bool F_01397890_12_0(ISerializerReadStream*, void*);
bool F_01397890_12_1(ISerializerWriteStream*, void*);
void F_01397890_12_2(const char*, void*);
void F_01397890_12_3(char*, void*);
bool F_01397890_12_4();
bool F_01397890_12_5(void*, const char*, int);
bool F_01397890_13_0(ISerializerReadStream*, void*);
bool F_01397890_13_1(ISerializerWriteStream*, void*);
void F_01397890_13_2(const char*, void*);
void F_01397890_13_3(char*, void*);
bool F_01397890_13_4();
bool F_01397890_13_5(void*, const char*, int);
bool F_01397890_14_0(ISerializerReadStream*, void*);
bool F_01397890_14_1(ISerializerWriteStream*, void*);
void F_01397890_14_2(const char*, void*);
void F_01397890_14_3(char*, void*);
bool F_01397890_15_0(ISerializerReadStream*, void*);
bool F_01397890_15_1(ISerializerWriteStream*, void*);
void F_01397890_15_2(const char*, void*);
void F_01397890_15_3(char*, void*);
bool F_01397890_15_4();
bool F_01397890_15_5(void*, const char*, int);
bool F_01397890_16_0(ISerializerReadStream*, void*);
bool F_01397890_16_1(ISerializerWriteStream*, void*);
void F_01397890_16_2(const char*, void*);
void F_01397890_16_3(char*, void*);
bool F_01397890_16_4();
bool F_01397890_16_5(void*, const char*, int);
bool F_01397890_17_0(ISerializerReadStream*, void*);
bool F_01397890_17_1(ISerializerWriteStream*, void*);
void F_01397890_17_2(const char*, void*);
void F_01397890_17_3(char*, void*);
bool F_01397890_18_0(ISerializerReadStream*, void*);
bool F_01397890_18_1(ISerializerWriteStream*, void*);
void F_01397890_18_2(const char*, void*);
void F_01397890_18_3(char*, void*);
bool F_01397ff0_0_0(ISerializerReadStream*, void*);
bool F_01397ff0_0_1(ISerializerWriteStream*, void*);
void F_01397ff0_0_2(const char*, void*);
void F_01397ff0_0_3(char*, void*);
bool F_01397ff0_0_4();
bool F_01397ff0_0_5(void*, const char*, int);
bool F_01397ff0_1_0(ISerializerReadStream*, void*);
bool F_01397ff0_1_1(ISerializerWriteStream*, void*);
void F_01397ff0_1_2(const char*, void*);
void F_01397ff0_1_3(char*, void*);
bool F_01397ff0_1_4();
bool F_01397ff0_1_5(void*, const char*, int);
bool F_01397ff0_2_0(ISerializerReadStream*, void*);
bool F_01397ff0_2_1(ISerializerWriteStream*, void*);
void F_01397ff0_2_2(const char*, void*);
void F_01397ff0_2_3(char*, void*);
bool F_01397ff0_2_4();
bool F_01397ff0_2_5(void*, const char*, int);
bool F_01397ff0_3_0(ISerializerReadStream*, void*);
bool F_01397ff0_3_1(ISerializerWriteStream*, void*);
void F_01397ff0_3_2(const char*, void*);
void F_01397ff0_3_3(char*, void*);
bool F_01397ff0_3_4();
bool F_01397ff0_3_5(void*, const char*, int);
bool F_01397ff0_4_0(ISerializerReadStream*, void*);
bool F_01397ff0_4_1(ISerializerWriteStream*, void*);
void F_01397ff0_4_2(const char*, void*);
void F_01397ff0_4_3(char*, void*);
bool F_01397ff0_4_4();
bool F_01397ff0_4_5(void*, const char*, int);
bool F_01397ff0_5_0(ISerializerReadStream*, void*);
bool F_01397ff0_5_1(ISerializerWriteStream*, void*);
void F_01397ff0_5_2(const char*, void*);
void F_01397ff0_5_3(char*, void*);
bool F_01397ff0_5_4();
bool F_01397ff0_5_5(void*, const char*, int);
bool F_01398270_0_0(ISerializerReadStream*, void*);
bool F_01398270_0_1(ISerializerWriteStream*, void*);
void F_01398270_0_2(const char*, void*);
void F_01398270_0_3(char*, void*);
bool F_01398270_0_4();
bool F_01398270_0_5(void*, const char*, int);
bool F_01398270_1_0(ISerializerReadStream*, void*);
bool F_01398270_1_1(ISerializerWriteStream*, void*);
void F_01398270_1_2(const char*, void*);
void F_01398270_1_3(char*, void*);
bool F_01398270_1_4();
bool F_01398270_1_5(void*, const char*, int);
bool F_01398270_2_0(ISerializerReadStream*, void*);
bool F_01398270_2_1(ISerializerWriteStream*, void*);
void F_01398270_2_2(const char*, void*);
void F_01398270_2_3(char*, void*);
bool F_01398270_2_4();
bool F_01398270_2_5(void*, const char*, int);
bool F_01398270_3_0(ISerializerReadStream*, void*);
bool F_01398270_3_1(ISerializerWriteStream*, void*);
void F_01398270_3_2(const char*, void*);
void F_01398270_3_3(char*, void*);
bool F_01398270_3_4();
bool F_01398270_3_5(void*, const char*, int);
bool F_01398420_0_0(ISerializerReadStream*, void*);
bool F_01398420_0_1(ISerializerWriteStream*, void*);
void F_01398420_0_2(const char*, void*);
void F_01398420_0_3(char*, void*);
bool F_01398420_0_4();
bool F_01398420_0_5(void*, const char*, int);
bool F_01398420_1_0(ISerializerReadStream*, void*);
bool F_01398420_1_1(ISerializerWriteStream*, void*);
void F_01398420_1_2(const char*, void*);
void F_01398420_1_3(char*, void*);
bool F_01398420_1_4();
bool F_01398420_1_5(void*, const char*, int);
bool F_01398420_2_0(ISerializerReadStream*, void*);
bool F_01398420_2_1(ISerializerWriteStream*, void*);
void F_01398420_2_2(const char*, void*);
void F_01398420_2_3(char*, void*);
bool F_01398420_2_4();
bool F_01398420_2_5(void*, const char*, int);
bool F_01398420_3_0(ISerializerReadStream*, void*);
bool F_01398420_3_1(ISerializerWriteStream*, void*);
void F_01398420_3_2(const char*, void*);
void F_01398420_3_3(char*, void*);
bool F_01398420_3_4();
bool F_01398420_3_5(void*, const char*, int);
bool F_01398420_4_0(ISerializerReadStream*, void*);
bool F_01398420_4_1(ISerializerWriteStream*, void*);
void F_01398420_4_2(const char*, void*);
void F_01398420_4_3(char*, void*);
bool F_01398420_4_4();
bool F_01398420_4_5(void*, const char*, int);

// @ 0x01397890
void __cdecl FUN_01397890()
{
    { Attribute a("mPosition", 0x3221494, 0, F_01397890_0_0, F_01397890_0_1, F_01397890_0_2, F_01397890_0_3, F_01397890_0_4, F_01397890_0_5); *(Attribute*)&gAttr01397890[0] = a; }
    { Attribute a("mOrientation", 0x3e44212, 0xc, F_01397890_1_0, F_01397890_1_1, F_01397890_1_2, F_01397890_1_3, F_01397890_1_4, F_01397890_1_5); *(Attribute*)&gAttr01397890[1] = a; }
    { Attribute a("mSpiceProduction", 0x32214b1, 0x1c, F_01397890_2_0, F_01397890_2_1, F_01397890_2_2, F_01397890_2_3, F_01397890_2_4, F_01397890_2_5); *(Attribute*)&gAttr01397890[2] = a; }
    { Attribute a("mMaxSize", 0x32214b6, 0x20, F_01397890_3_0, F_01397890_3_1, F_01397890_3_2, F_01397890_3_3, V_INT, X_INT); *(Attribute*)&gAttr01397890[3] = a; }
    { Attribute a("mSize", 0x32214bc, 0x24, F_01397890_4_0, F_01397890_4_1, F_01397890_4_2, F_01397890_4_3, V_INT, X_INT); *(Attribute*)&gAttr01397890[4] = a; }
    { Attribute a("mFinalIncome", 0x32214c2, 0x2c, F_01397890_5_0, F_01397890_5_1, F_01397890_5_2, F_01397890_5_3, V_INT, X_INT); *(Attribute*)&gAttr01397890[5] = a; }
    { Attribute a("mHappiness", 0x32214c5, 0x30, F_01397890_6_0, F_01397890_6_1, F_01397890_6_2, F_01397890_6_3, F_01397890_6_4, F_01397890_6_5); *(Attribute*)&gAttr01397890[6] = a; }
    { Attribute a("mBuilding", 0x34da69b, 0x7c, F_01397890_7_0, F_01397890_7_1, R_STL, W_STL, F_01397890_7_4, F_01397890_7_5); *(Attribute*)&gAttr01397890[7] = a; }
    { Attribute a("mOrnament", 0x34da69f, 0x90, F_01397890_8_0, F_01397890_8_1, R_STL, W_STL, F_01397890_8_4, F_01397890_8_5); *(Attribute*)&gAttr01397890[8] = a; }
    { Attribute a("mWall", 0x34da69c, 0xa4, F_01397890_9_0, F_01397890_9_1, R_STL, W_STL, F_01397890_9_4, F_01397890_9_5); *(Attribute*)&gAttr01397890[9] = a; }
    { Attribute a("mWallStyle", 0x34da69e, 0xb8, F_01397890_10_0, F_01397890_10_1, F_01397890_10_2, F_01397890_10_3, V_SHRT, X_SHRT); *(Attribute*)&gAttr01397890[10] = a; }
    { Attribute a("mVehicleSpecialty", 0x510c373, 0x34, F_01397890_11_0, F_01397890_11_1, F_01397890_11_2, F_01397890_11_3, F_01397890_11_4, F_01397890_11_5); *(Attribute*)&gAttr01397890[11] = a; }
    { Attribute a("mName", 0x54ff019, 0x40, F_01397890_12_0, F_01397890_12_1, F_01397890_12_2, F_01397890_12_3, F_01397890_12_4, F_01397890_12_5); *(Attribute*)&gAttr01397890[12] = a; }
    { Attribute a("mDescription", 0x6cb88ca, 0x50, F_01397890_13_0, F_01397890_13_1, F_01397890_13_2, F_01397890_13_3, F_01397890_13_4, F_01397890_13_5); *(Attribute*)&gAttr01397890[13] = a; }
    { Attribute a("mCaptureID", 0x55ba598, 0x38, F_01397890_14_0, F_01397890_14_1, F_01397890_14_2, F_01397890_14_3, V_SHRT, X_SHRT); *(Attribute*)&gAttr01397890[14] = a; }
    { Attribute a("mCapturePercent", 0x55ba59e, 0x3c, F_01397890_15_0, F_01397890_15_1, F_01397890_15_2, F_01397890_15_3, F_01397890_15_4, F_01397890_15_5); *(Attribute*)&gAttr01397890[15] = a; }
    { Attribute a("mTurretLocations", 0x55a554d, 0x28, F_01397890_16_0, F_01397890_16_1, F_01397890_16_2, F_01397890_16_3, F_01397890_16_4, F_01397890_16_5); *(Attribute*)&gAttr01397890[16] = a; }
    { Attribute a("mLevelHandle", 0x689db9f, 0xbc, F_01397890_17_0, F_01397890_17_1, F_01397890_17_2, F_01397890_17_3, V_SHRT, X_SHRT); *(Attribute*)&gAttr01397890[17] = a; }
    { Attribute a("mTextureHandle", 0x689dba2, 0xc0, F_01397890_18_0, F_01397890_18_1, F_01397890_18_2, F_01397890_18_3, V_SHRT, X_SHRT); *(Attribute*)&gAttr01397890[18] = a; }
}

// @ 0x01397ff0
void __cdecl FUN_01397ff0()
{
    { Attribute a("mPoliticalID", 0x32218ad, 0x14, F_01397ff0_0_0, F_01397ff0_0_1, F_01397ff0_0_2, F_01397ff0_0_3, F_01397ff0_0_4, F_01397ff0_0_5); *(Attribute*)&gAttr01397ff0[0] = a; }
    { Attribute a("mWealth", 0x32218d3, 0x1c, F_01397ff0_1_0, F_01397ff0_1_1, F_01397ff0_1_2, F_01397ff0_1_3, F_01397ff0_1_4, F_01397ff0_1_5); *(Attribute*)&gAttr01397ff0[1] = a; }
    { Attribute a("mColorID", 0x5d6ab6b, 0x18, F_01397ff0_2_0, F_01397ff0_2_1, F_01397ff0_2_2, F_01397ff0_2_3, F_01397ff0_2_4, F_01397ff0_2_5); *(Attribute*)&gAttr01397ff0[2] = a; }
    { Attribute a("mNumBuildings", 0x3718b19, 0x24, F_01397ff0_3_0, F_01397ff0_3_1, F_01397ff0_3_2, F_01397ff0_3_3, F_01397ff0_3_4, F_01397ff0_3_5); *(Attribute*)&gAttr01397ff0[3] = a; }
    { Attribute a("mNumTurrets", 0x3718b1a, 0x20, F_01397ff0_4_0, F_01397ff0_4_1, F_01397ff0_4_2, F_01397ff0_4_3, F_01397ff0_4_4, F_01397ff0_4_5); *(Attribute*)&gAttr01397ff0[4] = a; }
    { Attribute a("mModelKeys", 0x4acca33, 0, F_01397ff0_5_0, F_01397ff0_5_1, F_01397ff0_5_2, F_01397ff0_5_3, F_01397ff0_5_4, F_01397ff0_5_5); *(Attribute*)&gAttr01397ff0[5] = a; }
}

// @ 0x01398270
void __cdecl FUN_01398270()
{
    { Attribute a("mPoliticalID", 0x3225179, 0, F_01398270_0_0, F_01398270_0_1, F_01398270_0_2, F_01398270_0_3, F_01398270_0_4, F_01398270_0_5); *(Attribute*)&gAttr01398270[0] = a; }
    { Attribute a("mPosition", 0x3225193, 4, F_01398270_1_0, F_01398270_1_1, F_01398270_1_2, F_01398270_1_3, F_01398270_1_4, F_01398270_1_5); *(Attribute*)&gAttr01398270[1] = a; }
    { Attribute a("mPopulation", 0x32251a8, 0x10, F_01398270_2_0, F_01398270_2_1, F_01398270_2_2, F_01398270_2_3, F_01398270_2_4, F_01398270_2_5); *(Attribute*)&gAttr01398270[2] = a; }
    { Attribute a("mFood", 0x32251b8, 0x14, F_01398270_3_0, F_01398270_3_1, F_01398270_3_2, F_01398270_3_3, F_01398270_3_4, F_01398270_3_5); *(Attribute*)&gAttr01398270[3] = a; }
}

// @ 0x01398420
void __cdecl FUN_01398420()
{
    { Attribute a("mItemID", 0x355ee20, 4, F_01398420_0_0, F_01398420_0_1, F_01398420_0_2, F_01398420_0_3, F_01398420_0_4, F_01398420_0_5); *(Attribute*)&gAttr01398420[0] = a; }
    { Attribute a("mNumCharges", 0x355ee48, 0x10, F_01398420_1_0, F_01398420_1_1, F_01398420_1_2, F_01398420_1_3, F_01398420_1_4, F_01398420_1_5); *(Attribute*)&gAttr01398420[1] = a; }
    { Attribute a("mPosition", 0x355ee49, 0x18, F_01398420_2_0, F_01398420_2_1, F_01398420_2_2, F_01398420_2_3, F_01398420_2_4, F_01398420_2_5); *(Attribute*)&gAttr01398420[2] = a; }
    { Attribute a("mItemType", 0x355ee4a, 0, F_01398420_3_0, F_01398420_3_1, F_01398420_3_2, F_01398420_3_3, F_01398420_3_4, F_01398420_3_5); *(Attribute*)&gAttr01398420[3] = a; }
    { Attribute a("mHasMoved", 0x4fcdb10, 0x14, F_01398420_4_0, F_01398420_4_1, F_01398420_4_2, F_01398420_4_3, F_01398420_4_4, F_01398420_4_5); *(Attribute*)&gAttr01398420[4] = a; }
}

