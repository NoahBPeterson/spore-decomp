// src/game/SPGonzago/SPCreatureAnimal.cpp -- migrated from slice(s) s013329c0, s00c053b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureAnimal.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameBundleContainer.h"
#include <float.h>
#include <stdlib.h>

// ---- items of slice s013329c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_29c0; 
}
typedef eastl::string8_s0133_29c0 string8_s0133_29c0;
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
typedef void  (*ReadTextFunction_t)(const string8_s0133_29c0&, void*);
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
#define DECL_FAMILY(S) \
    void WriteText_00694fc0_##S(char* pBuffer, void* pData);                 /* 0x00694fc0 */ \
    bool Write_00572840_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00572840 */ \
    void ReadText_006930b0_##S(const string8_s0133_29c0& text, void* pData);            /* 0x006930b0 */ \
    void ReadText_00693090_##S(const string8_s0133_29c0& text, void* pData);            /* 0x00693090 */ \
    bool Write_00ac88f0_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00ac88f0 */ \
    void ReadText_00692ff0_##S(const string8_s0133_29c0& text, void* pData);            /* 0x00692ff0 */ \
    bool Read_00572810_##S(ISerializerReadStream* pStream, void* pData);     /* 0x00572810 */ \
    void WriteText_00694f00_##S(char* pBuffer, void* pData);                 /* 0x00694f00 */ \
    bool Validate_00b1fbf0_##S();                                            /* 0x00b1fbf0 */ \
    bool ToXml_00675ca0_##S(void* pData, const char* pName, int depth);      /* 0x00675ca0 */ \
    bool ToXml_00acbb80_##S(void* pData, const char* pName, int depth);      /* 0x00acbb80 */
}
namespace Simulator {
DECL_FAMILY(s)
}
namespace Simulator {
DECL_FAMILY(r0) DECL_FAMILY(r1) DECL_FAMILY(r2) DECL_FAMILY(r3) DECL_FAMILY(r4)
}
namespace Simulator {
DECL_FAMILY(r5) DECL_FAMILY(r6) DECL_FAMILY(r7) DECL_FAMILY(r8) DECL_FAMILY(r9)
}
namespace Simulator {
DECL_FAMILY(r10) DECL_FAMILY(r11) DECL_FAMILY(r12) DECL_FAMILY(r13) DECL_FAMILY(r14)
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_29c0& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00ae3310();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);      // 0x00ae3430
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);    // 0x00ae3450
}
namespace Simulator {
void ReadText_00693150(const string8_s0133_29c0& text, void* pData);             // 0x00693150
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);                  // 0x00695080
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);       // 0x00ae5720
}
namespace Simulator {
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);      // 0x00b20540
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);      // 0x00b6e3a0
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);    // 0x00ac88c0
}
namespace Simulator {
bool Read_00bd0d50(ISerializerReadStream* pStream, void* pData);      // 0x00bd0d50
}
namespace Simulator {
bool Write_00bd17b0(ISerializerWriteStream* pStream, void* pData);    // 0x00bd17b0
}
namespace Simulator {
bool Validate_00bcd450();                                             // 0x00bcd450
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cSPCreatureAnimal_sAttributes[13]; // 0x01571370
}
namespace Simulator {
#define ADD_TO(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
}
// ---- items of slice s013329c0 end

// @ 0x00c06320
float SP::cGameBundleContainer::GetRank(SP::cSPCreatureBase * param_2)
{
    int param_2_v = (int)param_2; (void)param_2_v; return 0.0f; }

// @ 0x01334790
namespace Simulator {
void InitSPCreatureAnimalAttributes()
{
#undef DECL_FAMILY  // the declarations above are all the table below needs
    ADD_TO(cSPCreatureAnimal_sAttributes, 0, "mPlayerAlertState", 0xd2708c85, 0x101c,
           Read_00572810_r0, Write_00572840_r0, ReadText_00692ff0_r0, WriteText_00694ee0,
           Validate_00b1fbf0_r0, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 1, "mNextSpecies", 0x03f6565d, 0x1004,
           Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
           Validate_00b1fbf0_r1, ToXml_00ae5720)
    ADD_TO(cSPCreatureAnimal_sAttributes, 2, "mHerd", 0x72ae9fe0, 0x1674,
           Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b6f550, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 3, "mNoDamageTimer", 0x05c02449, 0xfc0,
           Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00ae3310, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 4, "mLastAvatarDamageTimer", 0x05ee740c, 0xfe0,
           Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00ae3310, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 5, "mPregnantEggs", 0x52709079, 0x1678,
           Read_00572810_r5, Write_00572840_r5, ReadText_00692ff0_r5, WriteText_00694ee0,
           Validate_00b1fbf0_r5, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 6, "mUntargetDistanceTime", 0x021d2388, 0x167c,
           Read_00572810_r6, Write_00ac88f0_r6, ReadText_006930b0_r6, WriteText_00694fc0_r6,
           Validate_00b1fbf0_r6, ToXml_00acbb80_r6)
    ADD_TO(cSPCreatureAnimal_sAttributes, 7, "mOwnerMissionID", 0x92709161, 0x1680,
           Read_00572810_r7, Write_00572840_r7, ReadText_00693090_r7, WriteText_00694f00_r7,
           Validate_00b1fbf0_r7, ToXml_00675ca0_r7)
    ADD_TO(cSPCreatureAnimal_sAttributes, 8, "mPersonality", 0x72709236, 0x1684,
           Read_00572810_r8, Write_00572840_r8, ReadText_00692ff0_r8, WriteText_00694ee0,
           Validate_00b1fbf0_r8, ToXml_0057cde0)
    ADD_TO(cSPCreatureAnimal_sAttributes, 9, "mColor", 0x042a2b01, 0x1010,
           Read_00b6e3a0, Write_00ac88c0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b1fbf0_r9, ToXml_00ac8050)
    ADD_TO(cSPCreatureAnimal_sAttributes, 10, "mCharmDamage", 0x0666441b, 0x1694,
           Read_00572810_r10, Write_00ac88f0_r10, ReadText_006930b0_r10, WriteText_00694fc0_r10,
           Validate_00b1fbf0_r10, ToXml_00acbb80_r10)
    ADD_TO(cSPCreatureAnimal_sAttributes, 11, "mCharmTime", 0x06664451, 0x169c,
           Read_00572810_r11, Write_00ac88f0_r11, ReadText_006930b0_r11, WriteText_00694fc0_r11,
           Validate_00b1fbf0_r11, ToXml_00acbb80_r11)
    ADD_TO(cSPCreatureAnimal_sAttributes, 12, "mpCharmer", 0x06664454, 0x1698,
           Read_00bd0d50, Write_00bd17b0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00bcd450, ToXml_00ac8050)
}
}  // namespace Simulator
