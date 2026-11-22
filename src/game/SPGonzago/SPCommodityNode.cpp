// src/game/SPGonzago/SPCommodityNode.cpp -- migrated from slice(s) s013329c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommodityNode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
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
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bd0cb0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bfeca0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
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
void WriteText_00694fa0(char* pBuffer, void* pData);
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
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
void SetDefault_00bfe310(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe330(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe350(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe370(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe390(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe3b0(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe3d0(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe3f0(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe410(Attribute*);
}
namespace Simulator {
void SetDefault_00bfe430(Attribute*);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cCommodityNode_sAttributes[15];   // 0x01570a60
}
namespace Simulator {
extern uint8_t  cCommodityNode_sDefault_0168d181;   // 0x0168d181
}
namespace Simulator {
extern uint32_t cCommodityNode_sDefault_0168d184;   // 0x0168d184
}
namespace Simulator {
extern uint32_t cCommodityNode_sDefault_0168d188;   // 0x0168d188
}
namespace Simulator {
extern int      cCommodityNode_sDefault_0168d18c;   // 0x0168d18c
}
namespace Simulator {
extern int      cCommodityNode_sDefault_0168d190;   // 0x0168d190
}
namespace Simulator {
extern int      cCommodityNode_sDefault_0168d194;   // 0x0168d194
}
namespace Simulator {
extern int      cCommodityNode_sDefault_0168d198;   // 0x0168d198
}
namespace Simulator {
extern float    cCommodityNode_sDefault_0168d19c;   // 0x0168d19c
}
namespace Simulator {
extern float    cCommodityNode_sDefault_0168d1a0;   // 0x0168d1a0
}
namespace Simulator {
extern float    cCommodityNode_sDefault_0168d1a4;   // 0x0168d1a4
}
namespace Simulator {
#define FLOAT_ATTR(R, W, RT, WT, V, TX) Read_00572810_##R, Write_00ac88f0_##W, ReadText_006930b0_##RT, \
    WriteText_00694fc0_##WT, Validate_00b1fbf0_##V, ToXml_00acbb80_##TX
}
namespace Simulator {
#define UINT_ATTR(R, W, RT, V, TX) Read_00572810_##R, Write_00572840_##W, ReadText_00693090_##RT, \
    WriteText_00694f00_##R, Validate_00b1fbf0_##V, ToXml_00675ca0_##TX
}
namespace Simulator {
#define INT_ATTR(S) Read_00572810_##S, Write_00572840_##S, ReadText_00692ff0_##S, WriteText_00694ee0, \
    Validate_00b1fbf0_##S, ToXml_0057cde0
}
namespace Simulator {
#define BOOL_ATTR(S) Read_00ac8750, Write_00ac8780, ReadText_00693090_##S, WriteText_00694fa0, Validate_00b1fbf0_##S, ToXml_0057ce00
}
namespace Simulator {
#define PTR_ATTR(R, W, V)  R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050
}
namespace Simulator {
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCommodityNode_sAttributes[IDX] = a; }
}
// ---- items of slice s013329c0 end

// @ 0x013329c0
namespace Simulator {
void InitCommodityNodeAttributes()
{
#undef DECL_FAMILY  // the declarations above are all the table below needs
    ADD(0,  "mResourcePoints", 0x0403e5f1, 0x1d0, FLOAT_ATTR(r0, s, s, r0, r0, r0))
    ADD(1,  "mMaxResourcePoints", 0x0403e5f2, 0x1d4, FLOAT_ATTR(r1, s, s, r1, r1, r1))
    ADD(2,  "mpHitSphere", 0x0403e5f3, 0x1d8, PTR_ATTR(Read_00bd0cb0, Write_00bca960, Validate_00b6f550))
    ADD(3,  "mbMineInitialized", 0x0521d43e, 0x1e4, BOOL_ATTR(r3), SetDefault_00bfe310)
    cCommodityNode_sDefault_0168d181 = 0;
    ADD(4,  "mMineState", 0x0521d43f, 0x1ec, INT_ATTR(r4), SetDefault_00bfe330)
    ADD(5,  "mMineStateTimer", 0x0521d440, 0x1f0, PTR_ATTR(Read_00ae3470, Write_00ae3490, Validate_00ae3310))
    ADD(6,  "mMineStateTimeout", 0x0521d441, 0x210, UINT_ATTR(r6, r6, r6, s, s), SetDefault_00bfe350)
    ADD(7,  "mConstructingPoliticalID", 0x0521d442, 0x214, UINT_ATTR(r7, r7, r7, s, s), SetDefault_00bfe370)
    ADD(8,  "mCapturePoliticalID", 0x0521d443, 0x218, UINT_ATTR(r8, r8, r8, s, s), SetDefault_00bfe390)
    cCommodityNode_sDefault_0168d184 = 0;
    cCommodityNode_sDefault_0168d188 = 0;
    cCommodityNode_sDefault_0168d18c = -1;
    cCommodityNode_sDefault_0168d190 = -1;
    ADD(9,  "mConvertPoliticalID", 0x0521d444, 0x21c, UINT_ATTR(r9, r9, r9, s, s), SetDefault_00bfe3b0)
    ADD(10, "mBuyPoliticalID", 0x0521d445, 0x220, UINT_ATTR(r10, r10, r10, s, s), SetDefault_00bfe3d0)
    ADD(11, "mCapturePercent", 0x0521d446, 0x224, FLOAT_ATTR(s, r11, r11, s, r11, r11), SetDefault_00bfe3f0)
    ADD(12, "mConvertPercent", 0x0521d447, 0x228, FLOAT_ATTR(s, r12, r12, s, r12, r12), SetDefault_00bfe410)
    cCommodityNode_sDefault_0168d194 = -1;
    cCommodityNode_sDefault_0168d198 = -1;
    cCommodityNode_sDefault_0168d19c = 0.0f;
    cCommodityNode_sDefault_0168d1a0 = 0.0f;
    ADD(13, "mBuyPercent", 0x0521d448, 0x22c, FLOAT_ATTR(s, r13, r13, s, r13, r13), SetDefault_00bfe430)
    ADD(14, "mConstructingVehicle", 0x05776f58, 0x1e0, PTR_ATTR(Read_00bfeca0, Write_00bca960, Validate_00b6f550))
    cCommodityNode_sDefault_0168d1a4 = 0.0f;
}
}  // namespace Simulator
