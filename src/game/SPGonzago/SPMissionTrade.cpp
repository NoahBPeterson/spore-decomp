// src/game/SPGonzago/SPMissionTrade.cpp -- migrated from slice(s) s01347830 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionTrade.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01347830 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0134_7830; 
}
typedef eastl::string8_s0134_7830 string8_s0134_7830;
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
typedef void  (*ReadTextFunction_t)(const string8_s0134_7830&, void*);
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
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
}
namespace Simulator {
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
extern AttrSlot cTradeOffer_sAttributes[5];   // 0x015773b8
}
namespace Simulator {
#define ADD_TRADE(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cTradeOffer_sAttributes[IDX] = a; }
}
// ---- items of slice s01347830 end

// @ 0x0134b6b0
namespace Simulator {
void InitTradeOfferAttributes()
{
    ADD_TRADE(0, "mTradeState",    0xf38538ad, 0x1f0, Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0)
    ADD_TRADE(1, "mTradeItemType", 0xf38538ae, 0x1f4, Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0)
    ADD_TRADE(2, "mTradeKind",     0xf38538af, 0x1f8, Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0)
    ADD_TRADE(3, "mBoughtItem",    0xf38538b0, 0x1fc, Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00)
    ADD_TRADE(4, "mSoldItem",      0xf38538b1, 0x1fd, Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00)
}
}  // namespace Simulator
