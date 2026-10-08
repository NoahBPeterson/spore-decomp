// @ 0x0132cde0  dynamic initializer of the Simulator::tCultureTargetInfo serializer attribute
// table (17 Simulator::Attribute records, 0x3c bytes each, at 0x0156e448..0x0156e846).
//
// Same record layout and construction as the cCellSerialiazibleData / cGameDataUFO tables
// (s0137ef90, s013388f0): every record is built in one reused 0x3c-byte stack temp and copied
// (rep movsd) into the table. Member names and offsets agree with ModAPI tCultureTargetInfo
// (cCity.h): mBucketMaxPopulation[2] at 0x00, mBucketPopulation[2] 0x08, mBucketEmigration[2]
// 0x10, mBucketImmigration[2] 0x18, mClearEverything 0x20, the three crowd fractions 0x24..0x2c,
// two cGonzagoTimers at 0x30 / 0x50, mAttackTarget 0x70, mAttackTargetChanged 0x74 and
// mCultureObject 0x78. Ids and callbacks were read off the initializer. Callbacks that are
// per-type template instances in the original (folded by the linker to one address) are
// declared as templates so cl sees distinct symbols.
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
struct Timer;
struct SpatialObjectPtr;

// Per-type template instances (folded by the linker to one address each).
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
template<typename T> void ReadTextInt(const string8& text, void* pData);          // 0x00693090
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
bool Read_00bdc650(ISerializerReadStream* pStream, void* pData);

bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
bool Write_00bdd350(ISerializerWriteStream* pStream, void* pData);

void ReadText_00692ff0(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);

bool Validate_00ae3310();
bool Validate_00b6f550();

bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);

struct AttrSlot { uint32_t d[15]; };
extern AttrSlot tCultureTargetInfo_sAttributes[17];   // 0x0156e448

#define INT_ATTR    Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
#define BOOL_ATTR   Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
#define FLOAT_ATTR  Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
#define TIMER_ATTR  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050
#define OBJECT_ATTR Read_00bdc650, Write_00bdd350, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050

#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&tCultureTargetInfo_sAttributes[IDX] = a; }

// @ 0x0132cde0
void InitCultureTargetInfoAttributes()
{
    ADD(0,  "mBucketMaxPopulation[kListening]", 0x068c49f8, 0x00, INT_ATTR)
    ADD(1,  "mBucketMaxPopulation[kConverted]", 0x068c49fd, 0x04, INT_ATTR)
    ADD(2,  "mBucketPopulation[kListening]", 0x068c4a01, 0x08, INT_ATTR)
    ADD(3,  "mBucketPopulation[kConverted]", 0x068c4a06, 0x0c, INT_ATTR)
    ADD(4,  "mBucketEmigration[kListening]", 0x068c4a09, 0x10, INT_ATTR)
    ADD(5,  "mBucketEmigration[kConverted]", 0x068c4a0d, 0x14, INT_ATTR)
    ADD(6,  "mBucketImmigration[kListening]", 0x068c4a12, 0x18, INT_ATTR)
    ADD(7,  "mBucketImmigration[kConverted]", 0x068c4a15, 0x1c, INT_ATTR)
    ADD(8,  "mClearEverything", 0x068c3c35, 0x20, BOOL_ATTR)
    ADD(9,  "mAngryCrowdFraction", 0x068c3c38, 0x24, FLOAT_ATTR)
    ADD(10, "mDancingCrowdFraction", 0x068c3c3b, 0x28, FLOAT_ATTR)
    ADD(11, "mIndifferentCrowdFraction", 0x068c3c3e, 0x2c, FLOAT_ATTR)
    ADD(12, "mConvertCheckTimer", 0x068c3c41, 0x30, TIMER_ATTR)
    ADD(13, "mConvertedTimer", 0x068c3c45, 0x50, TIMER_ATTR)
    ADD(14, "mAttackTargetChanged", 0x068c3c48, 0x74, BOOL_ATTR)
    ADD(15, "mAttackTarget", 0x068c3c4c, 0x70, OBJECT_ATTR)
    ADD(16, "mCultureObject", 0x068c3c4f, 0x78, OBJECT_ATTR)
}

}  // namespace Simulator
