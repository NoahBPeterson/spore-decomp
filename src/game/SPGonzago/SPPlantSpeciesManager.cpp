// src/game/SPGonzago/SPPlantSpeciesManager.cpp -- migrated from slice(s) s01320f20 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlantSpeciesManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01320f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_0f20; 
}
typedef eastl::string8_s0132_0f20 string8_s0132_0f20;
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
typedef void  (*ReadTextFunction_t)(const string8_s0132_0f20&, void*);
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
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);    // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
void ReadText_00693090(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00bb9cd0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bb9d00(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00693050(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00694f60(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0132_0f20& text, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
struct TShort{}; struct TU64{}; struct TFloat{}; struct TDouble{}; struct TU8{}; struct TKey{}; struct TSpecies{}; struct TName{}; struct TRotAxis{}; struct TStamps{};
}
namespace Simulator {
template<typename T> bool Valid();      // 0x00b1fbf0
}
namespace Simulator {
template<typename T> bool ToXmlT(void* pData, const char* pName, int depth);
}
namespace Simulator {
#define U32_ATTR   Read4<uint64_t>, Write4<uint64_t>, ReadText_00692ff0, WriteText_00694ee0, Valid<TU64>, ToXmlT<TU64>
}
namespace Simulator {
#define S16_ATTR   Read4<int16_t>, Write4<int16_t>, ReadText_00693090, WriteText_00694f00, Valid<TShort>, ToXmlT<TShort>
}
namespace Simulator {
#define FLOAT_ATTR Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0, Valid<TFloat>, ToXmlT<TFloat>
}
namespace Simulator {
#define DOUBLE_ATTR Read4<double>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXmlT<TDouble>
}
namespace Simulator {
#define U8_ATTR    Read_00bb9cd0, Write_00bb9d00, ReadText_00693050, WriteText_00694f60, Valid<TU8>, ToXmlT<TU8>
}
namespace Simulator {
#define KEY_ATTR   Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, Valid<TKey>, ToXmlT<TKey>
}
namespace Simulator {
#define SPECIES_ATTR Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TSpecies>, ToXmlT<TSpecies>
}
namespace Simulator {
void FUN_00b8f8b0(Attribute* pAttr);                                   // 0x00b8f8b0  setDefault of mAlphaModel
}
namespace Simulator {
void FUN_00b8f8d0(Attribute* pAttr);                                   // 0x00b8f8d0  setDefault of mBaseRadius
}
namespace Simulator {
void FUN_00b8f8f0(Attribute* pAttr);                                   // 0x00b8f8f0  setDefault of mCanopyRadius
}
namespace Simulator {
void FUN_00b8f910(Attribute* pAttr);                                   // 0x00b8f910  setDefault of mHeight
}
namespace Simulator {
extern Attribute sModelAttributes[8];      // 0x0156bd78  model + appearance records
}
namespace Simulator {
extern int   g_16882ec;                    // 0x016882ec  model info key
}
namespace Simulator {
extern float g_16882f0;                    // 0x016882f0  model base radius
}
namespace Simulator {
extern float g_16882f4;                    // 0x016882f4  model canopy radius
}
namespace Simulator {
extern float g_16882f8;                    // 0x016882f8  model height
}
// ---- items of slice s01320f20 end

// @ 0x01324260
namespace Simulator {
void InitModelAttributes()
{
    {
        Attribute a("mModelIDLOD0", 0x384448b, 0x7c, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[0] = a;
    }
    {
        Attribute a("mModelIDLOD1", 0x384448c, 0x80, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[1] = a;
    }
    {
        Attribute a("mModelIDLOD2", 0x384448f, 0x84, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[2] = a;
    }
    {
        Attribute a("mModelIDLOD3", 0x3844491, 0x88, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0);
        sModelAttributes[3] = a;
    }
    {
        Attribute a("mAlphaModel", 0x5ada0bb, 0x8c, Read4<uint64_t>, Write4<uint64_t>,
                    ReadText_00693090, WriteText_00694f00, Valid<TU64>, ToXml_00675ca0,
                    FUN_00b8f8b0);
        sModelAttributes[4] = a;
    }
    {
        Attribute a("mBaseRadius", 0x5ad9efa, 0x94, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f8d0);
        sModelAttributes[5] = a;
    }
    {
        Attribute a("mCanopyRadius", 0x5ad9f00, 0x98, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f8f0);
        sModelAttributes[6] = a;
    }
    {
        Attribute a("mHeight", 0x5ad9f03, 0x9c, Read4<double>, Write_00ac88f0,
                    ReadText_006930b0, WriteText_00694fc0, Valid<TDouble>, ToXml_00acbb80,
                    FUN_00b8f910);
        sModelAttributes[7] = a;
    }
    g_16882ec = 0;
    g_16882f0 = 0.0f;
    g_16882f4 = 0.0f;
    g_16882f8 = 0.0f;
}
}  // namespace Simulator
