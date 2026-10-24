// gold7 batch, worker 5: four Simulator attribute-table dynamic initializers, same record layout
// and construction as s01315a50 (cCommEvent) / s01313370.cpp (cCity, $E231):
//   $E245 0x01313370  table at 0x01565d68  (7 records)
//   $E257 0x01313880  table at 0x015660f0  (2 records)
//   $E235 0x01314630  table at 0x015669f0  (5 records)
//   $E236 0x01315960  table at 0x01566cf8  (2 records)
// Each record is a 0x3c-byte Simulator::Attribute: name, id, member offset, three uninitialized
// fields, pCurrentObject (+0x18) = 0, set-default (+0x1c) = 0, offset function (0x00692ca0), then the
// read/write/readText/writeText/validate/toXml callbacks. Every record is built in one reused
// 0x3c-byte stack temp and rep-movsd copied into the table. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.

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

struct AttrSlot { uint32_t d[15]; };

bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);   // 0x00ac8750
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData); // 0x00ac8780
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);   // 0x00ac87c0
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData); // 0x00ac87f0
bool Read_00ad0710(ISerializerReadStream* pStream, void* pData);   // 0x00ad0710
bool Write_00ac8820(ISerializerWriteStream* pStream, void* pData); // 0x00ac8820
bool Read_00acda30(ISerializerReadStream* pStream, void* pData);   // 0x00acda30
bool Write_00ac9df0(ISerializerWriteStream* pStream, void* pData); // 0x00ac9df0
bool Read_00ad0d90(ISerializerReadStream* pStream, void* pData);   // 0x00ad0d90
bool Write_00ac9040(ISerializerWriteStream* pStream, void* pData); // 0x00ac9040
bool Read_00aca620(ISerializerReadStream* pStream, void* pData);   // 0x00aca620
bool Write_00ac9f70(ISerializerWriteStream* pStream, void* pData); // 0x00ac9f70
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);   // 0x00aca090
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData); // 0x00bca960
bool Read_00ce26c0(ISerializerReadStream* pStream, void* pData);   // 0x00ce26c0
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData); // 0x00aca730
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);   // 0x00ae3470
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData); // 0x00ae3490
bool Read_00572810(ISerializerReadStream* pStream, void* pData);   // 0x00572810
bool Write_00572840(ISerializerWriteStream* pStream, void* pData); // 0x00572840
bool Read_00ae6060(ISerializerReadStream* pStream, void* pData);   // 0x00ae6060
bool Write_00ae3930(ISerializerWriteStream* pStream, void* pData); // 0x00ae3930
bool Read_00ae9dd0(ISerializerReadStream* pStream, void* pData);   // 0x00ae9dd0
bool Read_00aeabe0(ISerializerReadStream* pStream, void* pData);   // 0x00aeabe0

void ReadText_00693090(const string8& text, void* pData);   // 0x00693090
void ReadText_00694c80(const string8& text, void* pData);   // 0x00694c80
void ReadText_00692ff0(const string8& text, void* pData);   // 0x00692ff0
void ReadText_00c2e4e0(const string8& text, void* pData);   // 0x00c2e4e0

void WriteText_00694fa0(char* pBuffer, void* pData);        // 0x00694fa0
void WriteText_00694c10(char* pBuffer, void* pData);        // 0x00694c10
void WriteText_00692fb0(char* pBuffer, void* pData);        // 0x00692fb0
void WriteText_00694ee0(char* pBuffer, void* pData);        // 0x00694ee0

bool Validate_00b1fbf0();   // 0x00b1fbf0
bool Validate2_00b1fbf0();  // 0x00b1fbf0 (a second template instance folded by the linker)
bool Validate_00ac9000();   // 0x00ac9000
bool Validate_00ac9ef0();   // 0x00ac9ef0
bool Validate_00ac9110();   // 0x00ac9110
bool Validate_00cd6630();   // 0x00cd6630
bool Validate_00b6f550();   // 0x00b6f550
bool Validate_00b6f860();   // 0x00b6f860
bool Validate_00ae3310();   // 0x00ae3310
bool Validate_00ae39d0();   // 0x00ae39d0

bool ToXml_0057ce00(void* pData, const char* pName, int depth);   // 0x0057ce00
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);   // 0x00acbbc0
bool ToXml_00ca85c0(void* pData, const char* pName, int depth);   // 0x00ca85c0
bool ToXml_00acb1b0(void* pData, const char* pName, int depth);   // 0x00acb1b0
bool ToXml_00acb340(void* pData, const char* pName, int depth);   // 0x00acb340
bool ToXml_00acbc10(void* pData, const char* pName, int depth);   // 0x00acbc10
bool ToXml_00ac8050(void* pData, const char* pName, int depth);   // 0x00ac8050
bool ToXml_00c6c390(void* pData, const char* pName, int depth);   // 0x00c6c390
bool ToXml_0057cde0(void* pData, const char* pName, int depth);   // 0x0057cde0
bool ToXml_00ae5a20(void* pData, const char* pName, int depth);   // 0x00ae5a20

#define BOOL_ATTR   Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0, Validate_00b1fbf0, ToXml_0057ce00
#define BOOL2_ATTR  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10, Validate2_00b1fbf0, ToXml_00acbbc0
#define PTR_ATTR(R, W, V, X) R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, X
#define INT_ATTR    Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, Validate_00b1fbf0, ToXml_0057cde0

#define ADD_MAIN(IDX, ...)  { Attribute a(__VA_ARGS__); *(Attribute*)&s_MainAttributes[IDX] = a; }
#define ADD_TRIBE(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&s_TribeAttributes[IDX] = a; }
#define ADD_GBL(IDX, ...)   { Attribute a(__VA_ARGS__); *(Attribute*)&s_GlobalAttributes[IDX] = a; }
#define ADD_COMM(IDX, ...)  { Attribute a(__VA_ARGS__); *(Attribute*)&s_CommAttributes[IDX] = a; }

extern AttrSlot s_MainAttributes[7];     // 0x01565d68  ($E245)
extern AttrSlot s_TribeAttributes[2];    // 0x015660f0  ($E257)
extern AttrSlot s_GlobalAttributes[5];   // 0x015669f0  ($E235)
extern AttrSlot s_CommAttributes[2];     // 0x01566cf8  ($E236)

// @ 0x01313370  ($E245)
void InitMainAttributes()
{
    ADD_MAIN(0, "mbInitialized",           0x03acc831, 0x100, BOOL_ATTR)
    ADD_MAIN(1, "mbUseCastedHerds",        0x03acc832, 0x101, BOOL_ATTR)
    ADD_MAIN(2, "mAnimalStagingDiagnostic",0x03acc833, 0x104, BOOL2_ATTR)
    ADD_MAIN(3, "mVisualizedTribes",       0x03acc836, 0x0a8,
             Read_00ad0710, Write_00ac8820, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ac9000, ToXml_00ca85c0)
    ADD_MAIN(4, "mAnimalStageMap",         0x05008fd9, 0x0c0,
             Read_00acda30, Write_00ac9df0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ac9ef0, ToXml_00acb1b0)
    ADD_MAIN(5, "mCastMap",                0x04206671, 0x088,
             Read_00ad0d90, Write_00ac9040, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ac9110, ToXml_00acb340)
    ADD_MAIN(6, "mInUseAnimals",           0x0656812e, 0x0e0,
             Read_00aca620, Write_00ac9f70, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00cd6630, ToXml_00acbc10)
}

// @ 0x01313880  ($E257)
void InitTribeAttributes()
{
    ADD_TRIBE(0, "mpTribe",      0x03acc4c7, 0x00, PTR_ATTR(Read_00aca090, Write_00bca960, Validate_00b6f550, ToXml_00ac8050))
    ADD_TRIBE(1, "mInUseMembers", 0x0510dd18, 0x04, PTR_ATTR(Read_00ce26c0, Write_00aca730, Validate_00b6f860, ToXml_00c6c390))
}

// @ 0x01314630  ($E235)
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

// @ 0x01315960  ($E236)
void InitCommAttributes()
{
    ADD_COMM(0, "mCurrentCommEvent", 0x0361c378, 0x20, PTR_ATTR(Read_00ae9dd0, Write_00bca960, Validate_00b6f550, ToXml_00ac8050))
    ADD_COMM(1, "mListCommEvents",   0x0361c379, 0x24, PTR_ATTR(Read_00aeabe0, Write_00aca730, Validate_00b6f860, ToXml_00c6c390))
}

}  // namespace Simulator
