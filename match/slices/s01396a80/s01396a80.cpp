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

void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset

struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml)
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
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ int setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};

struct AttrSlot { uint32_t d[15]; };

// Per-row callback symbols (distinct declarations; the linker folds equal template instances).
bool R0(ISerializerReadStream*, void*);  bool W0(ISerializerWriteStream*, void*);
void RT0(const string8&, void*);         void WT0(char*, void*);   bool V0();  bool X0(void*, const char*, int);
bool R1(ISerializerReadStream*, void*);  bool W1(ISerializerWriteStream*, void*);
void RT1(const string8&, void*);         void WT1(char*, void*);   bool V1();  bool X1(void*, const char*, int);
bool R2(ISerializerReadStream*, void*);  bool W2(ISerializerWriteStream*, void*);
void RT2(const string8&, void*);         void WT2(char*, void*);   bool V2();  bool X2(void*, const char*, int);
bool R3(ISerializerReadStream*, void*);  bool W3(ISerializerWriteStream*, void*);
void RT3(const string8&, void*);         void WT3(char*, void*);   bool V3();  bool X3(void*, const char*, int);
bool R4(ISerializerReadStream*, void*);  bool W4(ISerializerWriteStream*, void*);
void RT4(const string8&, void*);         void WT4(char*, void*);   bool V4();  bool X4(void*, const char*, int);
bool R5(ISerializerReadStream*, void*);  bool W5(ISerializerWriteStream*, void*);
void RT5(const string8&, void*);         void WT5(char*, void*);   bool V5();  bool X5(void*, const char*, int);

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_sAttributes[IDX] = a; }

// 0x015b52b0: cGameData / creature serializer attribute table (6 records, step 0x3c).
extern AttrSlot g_sAttributes[];

// @ 0x01397520
void InitE235()
{
    ADD(0, "mPosition",     0x4acb9a9, 0x00, R0, W0, RT0, WT0, V0, X0)
    ADD(1, "mOrientation",  0x4acb9b7, 0x0c, R1, W1, RT1, WT1, V1, X1)
    ADD(2, "mModelKey",     0x4acb9ba, 0x24, R2, W2, RT2, WT2, V2, X2)
    ADD(3, "mClassId",      0x4acb9bc, 0x30, R3, W3, RT3, WT3, V3, X3)
    ADD(4, "mHealthPoints", 0x4acb9bf, 0x1c, R4, W4, RT4, WT4, V4, X4)
    ADD(5, "mDamageState",  0x4acb9c1, 0x20, R5, W5, RT5, WT5, V5, X5)
}

// ---- 0x01397130 ($E231): 10-record serializer attribute table at 0x015b5018 ----
// Per-type template instances give distinct symbols (the linker folds equal instances);
// the plain-value (int) rows share one validate and one toXml symbol, which cl hoists into ebp/ebx.
template<typename T> bool IRead(ISerializerReadStream*, void*);
template<typename T> bool IWrite(ISerializerWriteStream*, void*);
template<typename T> void IReadText(const string8&, void*);
template<typename T> void IWriteText(char*, void*);
template<typename T> bool IValid();
template<typename T> bool IToXml(void*, const char*, int);

bool ValidInt();                                // 0x00b1fbf0, shared by the int rows
bool ToXmlIntShared(void*, const char*, int);   // 0x0057cde0, shared by the int rows

struct C0; struct C1; struct C2; struct C3; struct C4;
struct C5; struct C6; struct C7; struct C8; struct C9;
#define INT_ROW(T) IRead<T>, IWrite<T>, IReadText<T>, IWriteText<T>, ValidInt, ToXmlIntShared

extern AttrSlot g_creatureAttrs[];   // 0x015b5018

#define ADD2(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_creatureAttrs[IDX] = a; }

// @ 0x01397130
void InitE231()
{
    ADD2(0, "mPosition",     0x34da7b6, 0x00, IRead<C0>, IWrite<C0>, IReadText<C0>, IWriteText<C0>, IValid<C0>, IToXml<C0>)
    ADD2(1, "mOrientation",  0x34da7b7, 0x0c, IRead<C1>, IWrite<C1>, IReadText<C1>, IWriteText<C1>, IValid<C1>, IToXml<C1>)
    ADD2(2, "mClassId",      0x34da7b8, 0x34, INT_ROW(C2))
    ADD2(3, "mHealthPoints", 0x3def5f4, 0x1c, IRead<C3>, IWrite<C3>, IReadText<C3>, IWriteText<C3>, IValid<C3>, IToXml<C3>)
    ADD2(4, "mDamageState",  0x3df010e, 0x20, INT_ROW(C4))
    ADD2(5, "mConnected",    0x4bee126, 0x24, IRead<C5>, IWrite<C5>, IReadText<C5>, IWriteText<C5>, IValid<C5>, IToXml<C5>)
    ADD2(6, "mIrradiated",   0x5e4ee09, 0x25, IRead<C6>, IWrite<C6>, IReadText<C6>, IWriteText<C6>, IValid<C6>, IToXml<C6>)
    ADD2(7, "mEffectiveness",0x4bee127, 0x28, INT_ROW(C7))
    ADD2(8, "mFreezeCount",  0x4bee12a, 0x2c, INT_ROW(C8))
    ADD2(9, "mSlot",         0x5761ca2, 0x30, INT_ROW(C9))
}

// ---- 0x01396a80 ($E229): 9-record serializer attribute table at 0x015b4b90 ----
// Rows 0-2 are bool members sharing one validate (0x00b1fbf0 -> ebp) and one toXml (0x0057ce00 -> ebx);
// rows 3-8 share one readText (0x00c2e4e0) and one writeText (0x00692fb0), reloaded into ebp/ebx at row 3.
bool AV_bool();                              // 0x00b1fbf0
bool TX_bool(void*, const char*, int);       // 0x0057ce00
void NoopRT(const string8&, void*);          // 0x00c2e4e0
void NoopWT(char*, void*);                   // 0x00692fb0

struct M0; struct M1; struct M2; struct M3; struct M4;
struct M5; struct M6; struct M7; struct M8;

extern AttrSlot g_missionAttrs[];   // 0x015b4b90

#define ADD3(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_missionAttrs[IDX] = a; }

// @ 0x01396a80
void InitE229()
{
    ADD3(0, "mbFirstCommunication",       0x361c377, 0x16, IRead<M0>, IWrite<M0>, IReadText<M0>, IWriteText<M0>, AV_bool, TX_bool)
    ADD3(1, "mbFlightSchoolFinished",     0x56cfe7c, 0x17, IRead<M1>, IWrite<M1>, IReadText<M1>, IWriteText<M1>, AV_bool, TX_bool)
    ADD3(2, "mbMission201Finished",       0x6410400, 0x18, IRead<M2>, IWrite<M2>, IReadText<M2>, IWriteText<M2>, AV_bool, TX_bool)
    ADD3(3, "mTutorialTargetPlanetKeys",  0x361c389, 0x80, IRead<M3>, IWrite<M3>, NoopRT, NoopWT, IValid<M3>, IToXml<M3>)
    ADD3(4, "mTutorialSpeciesIDs",        0x361d38d, 0x94, IRead<M4>, IWrite<M4>, NoopRT, NoopWT, IValid<M4>, IToXml<M4>)
    ADD3(5, "mRecentNPCMissions",         0x1361c38a, 0xc8, IRead<M5>, IWrite<M5>, NoopRT, NoopWT, IValid<M5>, IToXml<M5>)
    ADD3(6, "mRecentColonyMissions",      0x1361c38b, 0xd4, IRead<M6>, IWrite<M6>, NoopRT, NoopWT, IValid<M6>, IToXml<M6>)
    ADD3(7, "mTrackedMissions",           0x361c38c, 0xa8, IRead<M7>, IWrite<M7>, NoopRT, NoopWT, IValid<M7>, IToXml<M7>)
    ADD3(8, "mTutorialMissionStates",     0x361c38d, 0x5c, IRead<M8>, IWrite<M8>, NoopRT, NoopWT, IValid<M8>, IToXml<M8>)
}

}  // namespace Simulator