// 0x01313ff0 ($E231): dynamic initializer of the Simulator::cCity serializer attribute table (16 records,
// 0x3c bytes each, at 0x015665f0..0x015669af). Same record layout/construction as s01315a50 (cCommEvent).
// Which callbacks cl hoists into ebx/ebp depends on symbol identity (per-type template instances: bool rows
// share AV_bool/ToXml_0057ce00, int rows share ToXml_0057cde0, rows 11/14 share ReadText_00692ff0).
// Each record is built in one reused 0x3c-byte stack temp and rep-movsd copied into the table.

#include "types.h"
#include <new>

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

    // Record with a default value: the store of the default (static or GetDefaultValue<T>()) is part
    // of the record's construction and sits just before the offset store.
    template<typename Store>
    __forceinline Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, const Store& storeDefault)
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
        storeDefault();
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

struct ResourceKey;
class cCity;
class cCivilization;
class cMission;
class cGameDataCommList;
struct DynamicResponseList;   // eastl::vector<int> mDynamicResponses
// Tags for the unsigned-int rows: their per-type callbacks are distinct template instances.

// Per-type template instances (folded by the linker to one address each).
// 0x00572810: 4-byte raw read
// 0x00572840: 4-byte integer write
// 0x00693090: ReadTextInt<T> for unsigned integers and bool
// 0x00b1fbf0: AlwaysValid (return true) for every plain-value type
// 0x00694ee0 / 0x0057cde0: text writer and xml writer of the int rows (per-type instances)
template<typename T> void WriteTextInt(char* pBuffer, void* pData);
template<typename T> void WriteTextUInt(char* pBuffer, void* pData);
template<typename T> bool ToXmlInt(void* pData, const char* pName, int depth);
// 0x00675ca0: ToXml for the unsigned-int rows
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);

struct AttrSlot { uint32_t d[15]; };

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool Validate_00b6f550();
void ReadText_00692ff0(const string8& text, void* pData);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
bool ToXml_00675ca0(void* pData, const char* pName, int depth);

// Vector / orientation / wall-key rows have their own per-type instances.
bool Read_00b6e3a0(ISerializerReadStream*, void*);  bool Write_00ac88c0(ISerializerWriteStream*, void*);
void ReadText_006930f0(const string8&, void*);      void WriteText_00695010(char*, void*);   bool ToXml_00acbba0(void*, const char*, int);
bool Read_00ae33d0(ISerializerReadStream*, void*);  bool Write_00ae3400(ISerializerWriteStream*, void*);
void ReadText_00693120(const string8&, void*);      void WriteText_00695040(char*, void*);   bool ToXml_00ae5700(void*, const char*, int);
bool Read_00ae3430(ISerializerReadStream*, void*);  bool Write_00ae3450(ISerializerWriteStream*, void*);
void ReadText_00693150(const string8&, void*);      void WriteText_00695080(char*, void*);   bool ToXml_00ae5720(void*, const char*, int);

extern AttrSlot cCity_sAttributes[16];   // 0x015665f0

struct Short_mMarkerID; struct Short_mPoliticalID;
struct Vec_mPosition; struct Quat_mOrientation; struct Key_mWallPropKey;
struct Int_mContinent; struct Int_mPersonality; struct Int_mAppearanceOrder; struct Int_mWallOffset; struct Int_mCivColorID;
struct Bool_a;

bool Read4(ISerializerReadStream* pStream, void* pData); bool Read4s(ISerializerReadStream* pStream, void* pData); bool Write4s(ISerializerWriteStream* pStream, void* pData); void ReadTextShort(const string8& text, void* pData);                    // 0x00572810 (shared instance)
bool Write4(ISerializerWriteStream* pStream, void* pData);                  // 0x00572840
void ReadTextInt(const string8& text, void* pData);                         // 0x00693090
bool AlwaysValid(); bool AV_bool(); bool AV_short(); bool AV_v1(); bool AV_v2(); bool AV_v3();                                                         // 0x00b1fbf0
template<int N> bool IRead(ISerializerReadStream*, void*); template<int N> bool IWrite(ISerializerWriteStream*, void*);
template<int N> void IReadText(const string8&, void*); template<int N> void IWriteText(char*, void*);
template<int N> bool IValid(); template<int N> bool IToXml(void*, const char*, int);
#define INT_ATTR_A(N) IRead<N>, IWrite<N>, IReadText<N>, IWriteText<N>, IValid<N>, ToXml_0057cde0
#define INT_ATTR_B(N) IRead<N>, IWrite<N>, rtB, IWriteText<N>, IValid<N>, txB
#define INT_ATTR Read4, Write4, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid, ToXml_0057cde0
#define SHORT_ATTR Read4s, Write4s, ReadTextShort, WriteText_00694f00, AV_short, ToXml_00675ca0
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCity_sAttributes[IDX] = a; }

// @ 0x01313ff0
void InitCityAttributes()
{
    ToXmlFunction_t txB = ToXml_0057cde0;
    ReadTextFunction_t rtB = ReadText_00692ff0;
    ADD(0,  "miMarkerID", 0x04a3c9eb, 0x0, SHORT_ATTR)
    ADD(1,  "mPosition", 0x0632c957, 0x4, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AV_v1, ToXml_00acbba0)
    ADD(2,  "mOrientation", 0x0632c95d, 0x10, Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AV_v2, ToXml_00ae5700)
    ADD(3,  "miContinent", 0x04a3bae4, 0x20, INT_ATTR_A(3))
    ADD(4,  "mbIsPlayerCity", 0x04a3baeb, 0x24, BOOL_ATTR)
    ADD(5,  "mbIsNeutral", 0x04a3c9bc, 0x25, BOOL_ATTR)
    ADD(6,  "mbIsPlayerContinent", 0x066ce9b5, 0x26, BOOL_ATTR)
    ADD(7,  "miPersonality", 0x04a3c9c0, 0x28, INT_ATTR_A(7))
    ADD(8,  "miAppearanceOrder", 0x04a3c9c3, 0x2c, INT_ATTR_A(8))
    ADD(9,  "mbHasAppeared", 0x04a3c9c7, 0x30, BOOL_ATTR)
    ADD(10, "mbIsCoastalCity", 0x050a4cd0, 0x31, BOOL_ATTR)
    ADD(11, "miWallOffset", 0x050a4ceb, 0x34, INT_ATTR_B(11))
    ADD(12, "mpTribe", 0x050f758c, 0x38, Read_00aca090, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(13, "mPoliticalID", 0x052f20e5, 0x3c, SHORT_ATTR)
    ADD(14, "miCivColorID", 0x0549651f, 0x44, INT_ATTR_B(14))
    ADD(15, "mWallPropKey", 0x0667bfd9, 0x48, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AV_v3, ToXml_00ae5720)
}

}  // namespace Simulator
