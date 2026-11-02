// src/game/SPGonzago/SPGameBundle.cpp -- migrated from slice(s) s01336df0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameBundle.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s01336df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_6df0; 
}
typedef eastl::string8_s0133_6df0 string8_s0133_6df0;
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
typedef void  (*ReadTextFunction_t)(const string8_s0133_6df0&, void*);
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
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0133_6df0& text, void* pData);  // 0x00692ff0
}
namespace Simulator {
void ReadText_00693090(const string8_s0133_6df0& text, void* pData);  // 0x00693090
}
namespace Simulator {
void ReadText_006930b0(const string8_s0133_6df0& text, void* pData);  // 0x006930b0
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_6df0& text, void* pData);  // 0x00c2e4e0
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
}
namespace Simulator {
bool Validate_00b1fbf0();  // 0x00b1fbf0
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
}
namespace Simulator {
bool Read_00c362d0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c364e0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Validate_00c35d90();
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cItem_sAttributes[5];   // 0x01573038
}
// ---- items of slice s01336df0 end

// @ 0x01337610
namespace Simulator {
void InitItemAttributes()
{
    {
        Attribute a("mAmountInBundle", 0x22553f2, 0x134,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cItem_sAttributes[0] = a;
    }
    {
        Attribute a("mpContainer", 0x22553f3, 0x128,
                  Read_00c362d0, Write_00c364e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c35d90, ToXml_00ac8050);
        *(Attribute*)&cItem_sAttributes[1] = a;
    }
    {
        Attribute a("mType", 0x22553f4, 0x12c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cItem_sAttributes[2] = a;
    }
    {
        Attribute a("mDisplayType", 0x22553f5, 0x130,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cItem_sAttributes[3] = a;
    }
    {
        Attribute a("mLoose", 0x6c3d90d, 0x124,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cItem_sAttributes[4] = a;
    }
}
}  // namespace Simulator
