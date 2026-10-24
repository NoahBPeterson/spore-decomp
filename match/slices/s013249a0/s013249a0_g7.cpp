// flags: /O2 /MD /Gy /EHsc /TP
// gold7 batch, worker 5 / slice s013249a0: two dynamic initializers that build
// Simulator::Attribute records (0x3c bytes each, 15 dwords) in one reused stack temp and copy
// them out with rep movsd.
//
//   0x013249a0  $E207  the cRelationshipManager attribute table (5 records at 0x0156c208 ..
//                       0x0156c333: relationship / friendlyCount / numBefriended / numKilled /
//                       lastAbilityMode).  One of them (lastAbilityMode) is a signed-integer
//                       attribute (ParseLong / write 0x694ee0 / toXml 0x0057cde0).
//   0x01325db0  $E499  the cSaveGame / serialized-version attribute table (6 records:
//                       savedGameVersionOnSave / savedGameVersionOnGenerate / buildVersionOnSave /
//                       buildVersionOnGenerate / timestampOnSave / timestampOnGenerate) plus the
//                       guard-initialized eastl::basic_string<wchar_t> statics at 0x01689dfc /
//                       0x01689e10 and the wstring globals around 0x01689db8.
//
// Record layout (matches the committed cStarManager table in s013249a0.cpp and cGameDataUFO in
// s013388f0): name, id, offset, three uninitialized fields, pCurrentObject (+0x18), set-default
// callback (+0x1c), offset function (+0x20, DefaultOffset 0x00692ca0), read (+0x24), write
// (+0x28), readText (+0x2c), writeText (+0x30), validate (+0x34), toXml (+0x38).
//
// The callbacks live outside this slice and are declared by address.  Some callback families
// (the 4-byte read/write, the text-int reader, the plain-value validator) are per-type template
// instances in the original that the linker folded to one address; they are declared as templates
// so cl keeps only the shared constants in registers.

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

struct Vector3;

// Callbacks, by original address.
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);          // 0x00572810
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);        // 0x00572840
template<typename T> void ReadTextInt(const string8& text, void* pData);               // 0x00693090
template<typename T> bool AlwaysValid();                                               // 0x00b1fbf0

void ReadText_00692ff0(const string8& text, void* pData);   // ParseLong (signed)
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694f00(char* pBuffer, void* pData);
void WriteText_00692fb0(char* pBuffer, void* pData);

bool ToXml_00675ca0(void* pData, const char* pName, int depth);
bool ToXml_0057cde0(void* pData, const char* pName, int depth);

// 0x01325db0 callbacks.
bool Read_00ba66b0(ISerializerReadStream* pStream, void* pData);   // savedGameVersionOnGenerate
bool Read_00ba9400(ISerializerReadStream* pStream, void* pData);   // buildVersionOnSave
bool Write_00ac87c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);
void ReadText_00694c80(const string8& text, void* pData);
void WriteText_00694c10(char* pBuffer, void* pData);
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);
bool Read_00ba9470(ISerializerReadStream* pStream, void* pData);   // buildVersionOnGenerate
bool Read_00b26970(ISerializerReadStream* pStream, void* pData);   // timestampOn*
bool Write_00b26990(ISerializerWriteStream* pStream, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);
bool ToXml_00ac8050(void* pData, const char* pName, int depth);

// eastl::basic_string<wchar_t> statics and the atexit guards for 0x01325db0.
// The two string statics are function-local `static` objects with non-trivial destructors, so cl
// emits a once-guard (test byte [guard],1 / or dword [guard],1) plus an atexit registration.
extern wchar_t gEmptyString16[2];               // 0x01667bac (eastl::gEmptyString16)

struct eastl_wstring
{
    wchar_t* mpBegin;   // +0x0
    wchar_t* mpEnd;     // +0x4
    wchar_t* mpCap;     // +0x8
    eastl_wstring() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCap(gEmptyString16 + 1) {}
    ~eastl_wstring();
    void assign(const wchar_t* pBegin, const wchar_t* pEnd);
};

// The field-name descriptor written at the end of 0x01325db0. The zeroed dwords at
// 0x01689dd0..0x01689df0 skip 0x01689dd8, which holds the offset function (StaticOffset);
// 0x01689df4 was already zeroed before the buildVersionOnSave record was built.
struct FieldNameString { const char* pName; int count; int flag; };
extern FieldNameString g_fieldNameString;       // 0x01689db8
extern int       g_fieldNameZerosLo[2];         // 0x01689dd0
extern void*     g_fieldNameOffsetFn;           // 0x01689dd8
extern int       g_fieldNameZerosHi[6];         // 0x01689ddc
extern int       g_fieldNameZeroF4;             // 0x01689df4

extern uint32_t cRelationship_sAttributes[5 * 15];              // 0x0156c208 (5 * 0x3c)
extern uint32_t cSaveGame_sAttributes[6 * 15];                  // 0x01689c50 (first record)
extern uint32_t cSaveGame_sBuildVersionOnSave[15];              // 0x01689cc8
extern uint32_t cSaveGame_sBuildVersionOnGenerate[15];          // 0x01689d04
extern uint32_t cSaveGame_sTimestampOnSave[15];                 // 0x01689d40
extern uint32_t cSaveGame_sTimestampOnGenerate[15];             // 0x01689d7c

#define ADD(PBASE, IDX, ...) \
    { Attribute a(__VA_ARGS__); *(Attribute*)&PBASE[(IDX) * 15] = a; }

// @ 0x013249a0
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

// @ 0x01325db0
void InitSaveGameAttributes()
{
    ADD(cSaveGame_sAttributes, 0,
        "savedGameVersionOnSave", 0x3f140b6, 4,
        Read4<uint32_t>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)
    ADD(cSaveGame_sAttributes, 1,
        "savedGameVersionOnGenerate", 0x3f140b7, 0,
        Read_00ba66b0, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteText_00694f00,
        AlwaysValid<uint32_t>, ToXml_00675ca0)

    // buildVersionOnSave: once-initialized eastl::basic_string<wchar_t> static.
    g_fieldNameZeroF4 = 0;                          // 0x01689df4
    {
        Attribute a("buildVersionOnSave", 0x3f140b8, 0x18,
                    Read_00ba9400, Write_00ac87c0, ReadText_00694c80, WriteText_00694c10,
                    AlwaysValid<uint32_t>, ToXml_00acbbc0);
        static eastl_wstring s_buildVersionOnSave;  // 0x01689dfc (guard 0x01689e0c)
        s_buildVersionOnSave.assign(gEmptyString16, gEmptyString16);
        *(Attribute*)&cSaveGame_sBuildVersionOnSave[0] = a;
    }

    // buildVersionOnGenerate: second once-initialized wstring static.
    {
        Attribute a("buildVersionOnGenerate", 0x3f140b9, 8,
                    Read_00ba9470, Write_00ac87c0, ReadText_00694c80, WriteText_00694c10,
                    AlwaysValid<uint32_t>, ToXml_00acbbc0);
        static eastl_wstring s_buildVersionOnGenerate;  // 0x01689e10 (guard 0x01689e20)
        s_buildVersionOnGenerate.assign(gEmptyString16, gEmptyString16);
        *(Attribute*)&cSaveGame_sBuildVersionOnGenerate[0] = a;
    }

    ADD(cSaveGame_sTimestampOnSave, 0,
        "timestampOnSave", 0x3f140ba, 0x4c,
        Read_00b26970, Write_00b26990, ReadText_00c2e4e0, WriteText_00692fb0,
        AlwaysValid<uint32_t>, ToXml_00ac8050)
    ADD(cSaveGame_sTimestampOnGenerate, 0,
        "timestampOnGenerate", 0x3f140bb, 0x28,
        Read_00b26970, Write_00b26990, ReadText_00c2e4e0, WriteText_00692fb0,
        AlwaysValid<uint32_t>, ToXml_00ac8050)

    g_fieldNameZerosLo[0] = 0;                      // 0x01689dd0
    g_fieldNameZerosLo[1] = 0;                      // 0x01689dd4
    g_fieldNameZerosHi[0] = 0;                      // 0x01689ddc
    g_fieldNameZerosHi[1] = 0;                      // 0x01689de0
    g_fieldNameZerosHi[2] = 0;                      // 0x01689de4
    g_fieldNameZerosHi[3] = 0;                      // 0x01689de8
    g_fieldNameZerosHi[4] = 0;                      // 0x01689dec
    g_fieldNameZerosHi[5] = 0;                      // 0x01689df0
    g_fieldNameString.flag = 0;                     // 0x01689dc0
    g_fieldNameString.pName = "field_name";         // 0x01689db8
    g_fieldNameString.count = -1;                   // 0x01689dbc
    g_fieldNameOffsetFn = (void*)StaticOffset;      // 0x01689dd8
}

}  // namespace Simulator
