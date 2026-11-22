// src/game/SPGonzago/SPCitySimulator.cpp -- migrated from slice(s) s01313370 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCitySimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>

// ---- items of slice s01313370 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_3370; 
}
typedef eastl::string8_s0131_3370 string8_s0131_3370;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0131_3370&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
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
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_3370& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0131_3370& text, void* pData);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream*, void*);
}
namespace Simulator {
void ReadText_006930f0(const string8_s0131_3370&, void*);
}
namespace Simulator {
void WriteText_00695010(char*, void*);
}
namespace Simulator {
bool ToXml_00acbba0(void*, const char*, int);
}
namespace Simulator {
bool Read_00ae33d0(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Write_00ae3400(ISerializerWriteStream*, void*);
}
namespace Simulator {
void ReadText_00693120(const string8_s0131_3370&, void*);
}
namespace Simulator {
void WriteText_00695040(char*, void*);
}
namespace Simulator {
bool ToXml_00ae5700(void*, const char*, int);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream*, void*);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream*, void*);
}
namespace Simulator {
void ReadText_00693150(const string8_s0131_3370&, void*);
}
namespace Simulator {
void WriteText_00695080(char*, void*);
}
namespace Simulator {
bool ToXml_00ae5720(void*, const char*, int);
}
namespace Simulator {
extern AttrSlot cCity_sAttributes[16];   // 0x015665f0
}
namespace Simulator {
bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read4s(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write4s(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadTextShort(const string8_s0131_3370& text, void* pData);
}
namespace Simulator {
bool Write4(ISerializerWriteStream* pStream, void* pData);                  // 0x00572840
}
namespace Simulator {
void ReadTextInt(const string8_s0131_3370& text, void* pData);                         // 0x00693090
}
namespace Simulator {
bool AlwaysValid();
}
namespace Simulator {
bool AV_bool();
}
namespace Simulator {
bool AV_short();
}
namespace Simulator {
bool AV_v1();
}
namespace Simulator {
bool AV_v2();
}
namespace Simulator {
bool AV_v3();
}
namespace Simulator {
template<int N> bool IRead(ISerializerReadStream*, void*);
}
namespace Simulator {
template<int N> bool IWrite(ISerializerWriteStream*, void*);
}
namespace Simulator {
template<int N> void IReadText(const string8_s0131_3370&, void*);
}
namespace Simulator {
template<int N> void IWriteText(char*, void*);
}
namespace Simulator {
template<int N> bool IValid();
}
namespace Simulator {
#define INT_ATTR_A(N) IRead<N>, IWrite<N>, IReadText<N>, IWriteText<N>, IValid<N>, ToXml_0057cde0
}
namespace Simulator {
#define INT_ATTR_B(N) IRead<N>, IWrite<N>, rtB, IWriteText<N>, IValid<N>, txB
}
namespace Simulator {
#define INT_ATTR Read4, Write4, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid, ToXml_0057cde0
}
namespace Simulator {
#define SHORT_ATTR Read4s, Write4s, ReadTextShort, WriteText_00694f00, AV_short, ToXml_00675ca0
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00
}
namespace Simulator {
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCity_sAttributes[IDX] = a; }
}
// ---- items of slice s01313370 end

// @ 0x01313ff0
namespace Simulator {
void InitCityAttributes()
{
    ToXmlFunction_t txB = ToXml_0057cde0;
    ReadTextFunction_t rtB = ReadText_00692ff0;
    ADD(0,  "miMarkerID", 0x04a3c9eb, 0x0, Read4s, Write4s, ReadTextShort, WriteText_00694f00, AV_short, ToXml_00675ca0)
    ADD(1,  "mPosition", 0x0632c957, 0x4, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AV_v1, ToXml_00acbba0)
    ADD(2,  "mOrientation", 0x0632c95d, 0x10, Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AV_v2, ToXml_00ae5700)
    ADD(3,  "miContinent", 0x04a3bae4, 0x20, INT_ATTR_A(3))
    ADD(4,  "mbIsPlayerCity", 0x04a3baeb, 0x24, Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00)
    ADD(5,  "mbIsNeutral", 0x04a3c9bc, 0x25, Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00)
    ADD(6,  "mbIsPlayerContinent", 0x066ce9b5, 0x26, Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00)
    ADD(7,  "miPersonality", 0x04a3c9c0, 0x28, INT_ATTR_A(7))
    ADD(8,  "miAppearanceOrder", 0x04a3c9c3, 0x2c, INT_ATTR_A(8))
    ADD(9,  "mbHasAppeared", 0x04a3c9c7, 0x30, Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00)
    ADD(10, "mbIsCoastalCity", 0x050a4cd0, 0x31, Read_00ac8750, Write_00ac8780, ReadTextInt, WriteText_00694fa0, AV_bool, ToXml_0057ce00)
    ADD(11, "miWallOffset", 0x050a4ceb, 0x34, INT_ATTR_B(11))
    ADD(12, "mpTribe", 0x050f758c, 0x38, Read_00aca090, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD(13, "mPoliticalID", 0x052f20e5, 0x3c, Read4s, Write4s, ReadTextShort, WriteText_00694f00, AV_short, ToXml_00675ca0)
    ADD(14, "miCivColorID", 0x0549651f, 0x44, INT_ATTR_B(14))
    ADD(15, "mWallPropKey", 0x0667bfd9, 0x48, Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AV_v3, ToXml_00ae5720)
}
}  // namespace Simulator

// ---- items of slice s01313370 (variant _g7) begin
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);   // 0x00ae3470
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData); // 0x00ae3490
}
namespace Simulator {
bool Validate_00ae3310();   // 0x00ae3310
}
namespace Simulator {
bool Read_00ae6060(ISerializerReadStream* pStream, void* pData);   // 0x00ae6060
}
namespace Simulator {
bool Write_00ae3930(ISerializerWriteStream* pStream, void* pData); // 0x00ae3930
}
namespace Simulator {
bool Validate_00ae39d0();   // 0x00ae39d0
}
namespace Simulator {
bool ToXml_00ae5a20(void* pData, const char* pName, int depth);   // 0x00ae5a20
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream* pStream, void* pData);   // 0x00572810
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData); // 0x00572840
}
namespace Simulator {
bool Validate_00b1fbf0();   // 0x00b1fbf0
}
namespace Simulator {
extern AttrSlot s_GlobalAttributes[5];   // 0x015669f0
}
namespace Simulator {
#define ADD_GBL(IDX, ...)   { Attribute a(__VA_ARGS__); *(Attribute*)&s_GlobalAttributes[IDX] = a; }
}
// ---- items of slice s01313370 (variant _g7) end

// @ 0x01314630
namespace Simulator {
void InitGlobalAttributes()
{
    ADD_GBL(0, "mTimer",               0x042ca8cb, 0x38,
            Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050)
    ADD_GBL(1, "mCityAppearanceTimer", 0x04a07c9f, 0x58,
            Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050)
    ADD_GBL(2, "mNumCitiesTotal",      0x04a37f39, 0xac, INT_ATTR)
    ADD_GBL(3, "mNumCitiesNotAppearedYet", 0x04a37f66, 0xb0, INT_ATTR)
    ADD_GBL(4, "mCityAppearanceInfo",  0x04a38663, 0x14,
            Read_00ae6060, Write_00ae3930, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae39d0, ToXml_00ae5a20)
}
}  // namespace Simulator
