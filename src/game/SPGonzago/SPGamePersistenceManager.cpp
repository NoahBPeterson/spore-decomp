// src/game/SPGonzago/SPGamePersistenceManager.cpp -- migrated from slice(s) s01318c70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGamePersistenceManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01318c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_8c70; 
}
typedef eastl::string8_s0131_8c70 string8_s0131_8c70;
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
typedef void  (*ReadTextFunction_t)(const string8_s0131_8c70&, void*);
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
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0131_8c70& text, void* pData);          // 0x00693090
}
namespace Simulator {
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0
}
namespace Simulator {
template<int N> bool Read4i(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
template<int N> bool Write4i(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<int N> void ReadTexti(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
template<int N> void WriteTexti(char* pBuffer, void* pData);
}
namespace Simulator {
template<int N> bool AlwaysValidi();
}
namespace Simulator {
template<int N> bool ToXmli(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00b00430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05de0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05ec0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05fa0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b0c730(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20510(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20570(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b21e60(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b26970(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b1fbf0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aca060(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00acdf10(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bab620(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b02570(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b02630(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b035b0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b26990(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b1fbf0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba7590(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba94e0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_8c70& text, void* pData);
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
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00b004e0();
}
namespace Simulator {
bool Validate_00b00520();
}
namespace Simulator {
bool Validate_00b20230();
}
namespace Simulator {
bool Validate_00ba7450();
}
namespace Simulator {
bool Validate_00d011e0();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00d022e0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00b04120(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00fe4be0(void* pData, const char* pName, int depth);
}
namespace Simulator {
void SetDefault_00b269b0(Attribute* pAttr);
}
namespace Simulator {
void SetDefault_00b269d0(Attribute* pAttr);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot GameSnapshot_sAttributes[7];           // 0x01568b08
}
namespace Simulator {
#define INT_ATTR      Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
}
namespace Simulator {
#define SHORT_ATTR    Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0
}
namespace Simulator {
#define BOOL_ATTR     Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
#define STATIC_INT_ATTR  Read4<int>, Write4<int>, ReadTextInt<int>, WriteText_00694f00, AlwaysValid<int>
}
namespace Simulator {
#define FLAGS_ATTR    Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
}
namespace Simulator {
#define TREE_OBJ_ATTR Read_00b05de0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define TREE_OBJ2_ATTR Read_00b05ec0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define MULTIMAP_ATTR Read_00b05fa0, Write_00b035b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b004e0, ToXml_00d022e0
}
namespace Simulator {
#define CLUMP_ATTR    Read_00b0c730, Write_00b02630, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b00520, ToXml_00b04120
}
namespace Simulator {
#define OWNER_ATTR    Read_00aca060, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define AVATAR_ATTR   Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define AVATARHERD_ATTR Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define PTRIBE_ATTR   Read_00aca090, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define PPLAYER_ATTR  Read_00b20570, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define POSSE_ATTR    Read_00acdf10, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define POLMAP_ATTR   Read_00b21e60, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0
}
namespace Simulator {
#define NOUNS_ATTR    Read_00b1fbf0, Write_00b1fbf0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b20230, ToXml_00ac8050
}
namespace Simulator {
#define OBJCOUNT_ATTR Read_00bab620, Write_00ba7590, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00d011e0, ToXml_00fe4be0
}
namespace Simulator {
#define TIMESTAMP_ATTR Read_00b26970, Write_00b26990, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
}
namespace Simulator {
#define PLANETKEY_ATTR Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<int>, ToXml_00ae5720
}
namespace Simulator {
#define ADD_SNAP(IDX, ...)     { Attribute a(__VA_ARGS__); *(Attribute*)&GameSnapshot_sAttributes[IDX] = a; }
}
namespace Simulator {
extern const char* g_0167e064;    // 0x0167e064
}
namespace Simulator {
extern uint8_t     g_0167e068;    // 0x0167e068
}
namespace Simulator {
extern uint8_t     g_01654c01;    // 0x01654c01
}
// ---- items of slice s01318c70 end

// @ 0x0131b210
namespace Simulator {
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
