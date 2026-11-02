// src/game/SPGonzago/SPSpeciesRelationshipManager.cpp -- migrated from slice(s) s013249a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpeciesRelationshipManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s013249a0_g7 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_49a0__g7; 
}
typedef eastl::string8_s0132_49a0__g7 string8_s0132_49a0__g7;
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
typedef void  (*ReadTextFunction_t)(const string8_s0132_49a0__g7&, void*);
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
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);          // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);        // 0x00572840
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0132_49a0__g7& text, void* pData);               // 0x00693090
}
namespace Simulator {
template<typename T> bool AlwaysValid();                                               // 0x00b1fbf0
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0132_49a0__g7& text, void* pData);   // ParseLong (signed)
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
extern uint32_t cRelationship_sAttributes[5 * 15];              // 0x0156c208 (5 * 0x3c)
}
namespace Simulator {
#define ADD(PBASE, IDX, ...) \
    { Attribute a(__VA_ARGS__); *(Attribute*)&PBASE[(IDX) * 15] = a; }
}
// ---- items of slice s013249a0_g7 end

// @ 0x013249a0
namespace Simulator {
void InitRelationshipManagerAttributes()
{
    ADD(cRelationship_sAttributes, 0,
        "relationship", 0xd358c5eb, 0,
        Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(cRelationship_sAttributes, 1,
        "friendlyCount", 0xd358c5ec, 4,
        Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(cRelationship_sAttributes, 2,
        "numBefriended", 0xb3855529, 8,
        Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(cRelationship_sAttributes, 3,
        "numKilled", 0x739aab32, 0xc,
        Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(cRelationship_sAttributes, 4,
        "lastAbilityMode", 0x33b214ec, 0x10,
        Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0,
        AlwaysValid<int>, ToXml_0057cde0)
}
}  // namespace Simulator
