// src/game/SPGonzago/SPCelestialBody.cpp -- migrated from slice(s) s0132abc0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCelestialBody.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s0132abc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0132_abc0; 
}
typedef eastl::string8_s0132_abc0 string8_s0132_abc0;
typedef bool (*ReadFunction_t)(void*, void*);
typedef bool (*WriteFunction_t)(void*, void*);
typedef void (*ReadTextFunction_t)(const string8_s0132_abc0&, void*);
typedef void (*WriteTextFunction_t)(char*, void*);
typedef bool (*ValidateFunction_t)();
typedef bool (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(void*);
typedef void (*SetDefaultFunction_t)(void*);
void* DefaultOffset(void* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
struct Attribute
{
    // Offset is written last, after every callback slot -- matches the binary.
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
    /* 0Ch */ int field_0C;   // not initialized by the constructor
    /* 10h */ int field_10;   // not initialized by the constructor
    /* 14h */ int field_14;   // not initialized by the constructor
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
bool Read_00572810(void*, void*);                                     // 0x00572810
bool Write_00572840(void*, void*);                                    // 0x00572840
void ReadText_00692ff0(const string8_s0132_abc0&, void*);                        // 0x00692ff0
void WriteText_00694ee0(char*, void*);                                // 0x00694ee0
struct TType{}; struct TPosition{}; struct TRotationRate{}; struct TName{}; struct THitSphereSize{};
template<typename T> bool Valid();                                    // 0x00b1fbf0
bool ToXml_0057cde0(void*, const char*, int);                         // 0x0057cde0
bool Read_00b8db30(void*, void*);                                     // 0x00b8db30
bool Write_00b8db50(void*, void*);                                    // 0x00b8db50
void ReadText_00c2e4e0(const string8_s0132_abc0&, void*);                        // 0x00c2e4e0
void WriteText_00692fb0(char*, void*);                                // 0x00692fb0
bool Valid_00b8db10();                                                // 0x00b8db10
bool ToXml_00ac8050(void*, const char*, int);                         // 0x00ac8050
bool Read_00b6e3a0(void*, void*);                                     // 0x00b6e3a0
bool Write_00ac88c0(void*, void*);                                    // 0x00ac88c0
void ReadText_006930f0(const string8_s0132_abc0&, void*);                        // 0x006930f0
void WriteText_00695010(char*, void*);                                // 0x00695010
bool ToXml_00acbba0(void*, const char*, int);                         // 0x00acbba0
bool Write_00ac88f0(void*, void*);                                    // 0x00ac88f0
void ReadText_006930b0(const string8_s0132_abc0&, void*);                        // 0x006930b0
void WriteText_00694fc0(char*, void*);                                // 0x00694fc0
bool ToXml_00acbb80(void*, const char*, int);                         // 0x00acbb80
bool Read_00ac87c0(void*, void*);                                     // 0x00ac87c0
bool Write_00ac87f0(void*, void*);                                    // 0x00ac87f0
void ReadText_00694c80(const string8_s0132_abc0&, void*);                        // 0x00694c80
void WriteText_00694c10(char*, void*);                                // 0x00694c10
bool ToXml_00acbbc0(void*, const char*, int);                         // 0x00acbbc0
struct AttrSlot { uint32_t d[15]; };
extern AttrSlot sCelestialBodyAttributes[6];
#define ADD_ATTR(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
// ---- items of slice s0132abc0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern AttrSlot sCelestialBodyAttributes[6];

// @ 0x0132b6b0
void FUN_0132b6b0()
{
    ADD_ATTR(sCelestialBodyAttributes, 0, "mType", 0x038cfe0e, 0x34, Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, Valid<TType>, ToXml_0057cde0)
    ADD_ATTR(sCelestialBodyAttributes, 1, "mOrbit", 0x038cfe26, 0x38, Read_00b8db30, Write_00b8db50, ReadText_00c2e4e0, WriteText_00692fb0, Valid_00b8db10, ToXml_00ac8050)
    ADD_ATTR(sCelestialBodyAttributes, 2, "mPosition", 0x038cfe48, 0xa0, Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, Valid<TPosition>, ToXml_00acbba0)
    ADD_ATTR(sCelestialBodyAttributes, 3, "mRotationRate", 0x038cfe5c, 0xac, Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<TRotationRate>, ToXml_00acbb80)
    ADD_ATTR(sCelestialBodyAttributes, 4, "mName", 0x038cfe6d, 0xb0, Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, Valid<TName>, ToXml_00acbbc0)
    ADD_ATTR(sCelestialBodyAttributes, 5, "mHitSphereSize", 0x038e5030, 0xc8, Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, Valid<THitSphereSize>, ToXml_00acbb80)
}
