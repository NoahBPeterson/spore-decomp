// src/game/SPGonzago/_at_01380000.cpp -- migrated from slice(s) s0138d560, s0138c850, s0138c040, s0138b190, s013894f0, s0137ef90 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01380000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/LimitStopwatch.h"
#include "EA/Stopwatch.h"

// ---- items of slice s0137ef90 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned int, void* p) { return p; }
namespace EA {
namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t basis, int lower); // 0x00932e80
}
}
extern "C" int __cdecl atexit(void (__cdecl*)(void));   // 0x011e07ef
namespace Simulator {
void FUN_013c8c90();                                    // 0x013c8c90
}
namespace Simulator {
void FUN_013c8f90();                                    // 0x013c8f90
}
namespace Simulator {
struct MyCaptainLevels {
    void*             mpVtable;                    // +0x00
    uint32_t          mNameHash;                   // +0x04
    MyCaptainLevels*  mpNext;                      // +0x08
    uint32_t          mField0c;                    // +0x0c
    uint32_t          mField10;                    // +0x10
};
}
namespace Simulator {
extern MyCaptainLevels  g_myCaptainLevels;         // 0x016c7a18
}
namespace Simulator {
extern MyCaptainLevels* g_myCaptainLevelsHead;     // 0x015aca38
}
namespace Simulator {
extern ::EA::LimitStopwatch g_limitStopwatch;      // 0x016c7b60
}
// ---- items of slice s0137ef90 end

// ---- items of slice s013894f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_spScenarioModeUI;    // 0x015ad334 (the constructed UI object)
extern char  g_spScenarioModeAux[]; // 0x015ad328 (0x0c bytes before the UI pointer)
typedef bool (*ReadFn)(void*, void*);
typedef bool (*WriteFn)(void*, void*);
typedef void (*ReadTextFn)(const void*, void*);
typedef void (*WriteTextFn)(char*, void*);
typedef bool (*UnkFn)();
typedef bool (*Unk2Fn)(void*, const char*, int);
struct Attribute;
typedef void* (*OffsetFn)(Attribute*);
void* DefaultOffset(Attribute*);                       // 0x692ca0
bool  rd_00572810(void*, void*);
bool  wr_00572840(void*, void*);
void  rt_00692ff0(const void*, void*);
void  wt_00694ee0(char*, void*);
bool  uk_00b1fbf0();                                   // shared "return true" stub
bool  u2_0057cde0(void*, const char*, int);
bool  rd_00f2c950(void*, void*);
bool  wr_00f268f0(void*, void*);
void  rt_00c2e4e0(const void*, void*);
void  wt_00692fb0(char*, void*);
bool  uk_00f26990();
bool  u2_00f29410(void*, const char*, int);
bool  rd_00f293f0(void*, void*);
bool  wr_00f268b0(void*, void*);
bool  uk_00f25b60();
bool  u2_00f28880(void*, const char*, int);
bool  rd_00f29560(void*, void*);
bool  wr_00f269d0(void*, void*);
bool  uk_00f26a60();
bool  u2_00f29650(void*, const char*, int);
struct Attribute {
  const char* name;
  uint32_t id;
  unsigned offset;
  int field_0C, field_10, field_14;
  void* pCurrentObject;
  int field_1C;
  OffsetFn offsetFunction;
  ReadFn readFunction;
  WriteFn writeFunction;
  ReadTextFn readTextFunction;
  WriteTextFn writeTextFunction;
  UnkFn field_34;
  Unk2Fn field_38;

  Attribute() {}
  Attribute(const char* n, uint32_t i, unsigned o, ReadFn r, WriteFn w, ReadTextFn rt,
            WriteTextFn wt, UnkFn u, Unk2Fn u2) {
    name = n;
    id = i;
    pCurrentObject = 0;
    field_1C = 0;
    offsetFunction = DefaultOffset;
    readFunction = r;
    writeFunction = w;
    readTextFunction = rt;
    writeTextFunction = wt;
    field_34 = u;
    field_38 = u2;
    offset = o;
  }
};
bool rd_00572810_g1(void*, void*);
bool rd_00572810_g2(void*, void*);
bool rd_00ac8750_g3(void*, void*);
void rt_00692ff0_g1(const void*, void*);
void rt_00693090_g3(const void*, void*);
void rt_006930b0_g2(const void*, void*);
bool u2_0057cde0_g1(void*, const char*, int);
bool u2_0057ce00_g3(void*, const char*, int);
bool u2_00acbb80_g2(void*, const char*, int);
bool uk_00b1fbf0_g1();
bool uk_00b1fbf0_g2();
bool uk_00b1fbf0_g3();
bool wr_00572840_g1(void*, void*);
bool wr_00ac8780_g3(void*, void*);
bool wr_00ac88f0_g2(void*, void*);
void wt_00694ee0_g1(char*, void*);
void wt_00694fa0_g3(char*, void*);
void wt_00694fc0_g2(char*, void*);
void* operator_new(unsigned size, const char* name, int, int, int, int);   // 0x00f473a0
void AtExit013c9070();                                                    // 0x013c9070
struct SceneModeUI { void* Construct(); };        // 0x00f2aac0
struct SceneModeAux { void  Init(); };            // 0x00f03290
struct ListHead { void* mpBegin; void* mpEnd; char pad[0x18]; };
extern ListHead g_spHeadArray[10];   // 0x016c7df0
void AtExit013c9140();               // 0x013c9140
Attribute gScenarioClassActAttributes[25];
Attribute gServerIdAttributes[4];   // 0x015adbd0
bool rd_00ae3430_r0(void*, void*);
bool wr_00ae3450_r0(void*, void*);
void rt_00693150_r0(const void*, void*);
void wt_00695080_r0(char*, void*);
bool uk_00b1fbf0_r0();
bool u2_00ae5720_r0(void*, const char*, int);
bool rd_00572810_r1(void*, void*);
bool wr_00572840_r1(void*, void*);
void rt_00693090_r1(const void*, void*);
void wt_00694f00_r1(char*, void*);
bool uk_00b1fbf0_r1();
bool u2_00675ca0_r1(void*, const char*, int);
bool rd_00aff840_r2(void*, void*);
bool wr_00aff870_r2(void*, void*);
void rt_00692fd0_r2(const void*, void*);
void wt_00694ec0_r2(char*, void*);
bool uk_00b1fbf0_r2();
bool u2_00595a70_r2(void*, const char*, int);
bool rd_00572810_r3(void*, void*);
bool wr_00572840_r3(void*, void*);
void rt_00693090_r3(const void*, void*);
void wt_00694f00_r3(char*, void*);
bool uk_00b1fbf0_r3();
bool u2_00675ca0_r3(void*, const char*, int);
Attribute gSensorTagAttributes[8];   // 0x015add00
// ---- items of slice s013894f0 end

// ---- items of slice s0138b190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char s_defaultOffsetThunk;   // 0x00692ca0
extern char s_f26be0;               // 0x00f26be0
extern char s_f26c20;               // 0x00f26c20
extern char s_c2e4e0;               // 0x00c2e4e0
extern char s_692fb0;               // 0x00692fb0
extern char s_f25b80;               // 0x00f25b80
extern char s_f2a510;               // 0x00f2a510
extern char s_ac8750;               // 0x00ac8750
extern char s_ac8780;               // 0x00ac8780
extern char s_693090;               // 0x00693090
extern char s_694fa0;               // 0x00694fa0
extern char s_b1fbf0;               // 0x00b1fbf0
extern char s_57ce00;               // 0x0057ce00
extern char s_ae3430;               // 0x00ae3430
extern char s_ae3450;               // 0x00ae3450
extern char s_693150;               // 0x00693150
extern char s_695080;               // 0x00695080
extern char s_ae5720;               // 0x00ae5720
extern char s_aff840;               // 0x00aff840
extern char s_aff870;               // 0x00aff870
extern char s_692fd0;               // 0x00692fd0
extern char s_694ec0;               // 0x00694ec0
extern char s_595a70;               // 0x00595a70
extern char s_572810;               // 0x00572810
extern char s_572840;               // 0x00572840
extern char s_692ff0;               // 0x00692ff0
extern char s_694ee0;               // 0x00694ee0
extern char s_57cde0;               // 0x0057cde0
extern char s_f2c950;               // 0x00f2c950
extern char s_f268f0;               // 0x00f268f0
extern char s_f26990;               // 0x00f26990
extern char s_f29410;               // 0x00f29410
extern char s_f26ac0;               // 0x00f26ac0
extern char s_f26aa0;               // 0x00f26aa0
extern char s_f27ec0;               // 0x00f27ec0
extern char s_ac8050;               // 0x00ac8050
extern char s_f2e370;               // 0x00f2e370
extern char s_f26b00;               // 0x00f26b00
extern char s_f26ba0;               // 0x00f26ba0
extern char s_f297a0;               // 0x00f297a0
extern char s_f293f0;               // 0x00f293f0
extern char s_f268b0;               // 0x00f268b0
extern char s_f25b60;               // 0x00f25b60
extern char s_f28880;               // 0x00f28880
extern char s_ac88f0;               // 0x00ac88f0
extern char s_6930b0;               // 0x006930b0
extern char s_694fc0;               // 0x00694fc0
extern char s_acbb80;               // 0x00acbb80
extern char s_b6e3a0;               // 0x00b6e3a0
extern char s_ac88c0;               // 0x00ac88c0
extern char s_6930f0;               // 0x006930f0
extern char s_695010;               // 0x00695010
extern char s_acbba0;               // 0x00acbba0
extern char s_c41210;               // 0x00c41210
extern char s_c40e80;               // 0x00c40e80
extern char s_c41b00;               // 0x00c41b00
extern char s_694f00;               // 0x00694f00
extern char s_675ca0;               // 0x00675ca0
struct cAttribute
{
    const char* m_name;             // 0x00
    int         m_hash;             // 0x04
    int         m_offset;           // 0x08
    int         m_reserved0;        // 0x0c
    int         m_reserved1;        // 0x10
    int         m_reserved2;        // 0x14
    void*       m_zero0;            // 0x18
    void*       m_zero1;            // 0x1c
    void*       m_defaultOffset;    // 0x20
    void*       m_get;              // 0x24
    void*       m_set;              // 0x28
    void*       m_parse;            // 0x2c
    void*       m_toString;         // 0x30
    void*       m_fromString;       // 0x34
    void*       m_serialise;        // 0x38
};
cAttribute g_attributes[32];
// ---- items of slice s0138b190 end

// ---- items of slice s0138c040 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned u32;
struct Desc {
    const char* name;   // 0x00
    u32         id;     // 0x04
    u32         size;   // 0x08
    u32         r0;     // 0x0c
    u32         r1;     // 0x10
    u32         r2;     // 0x14
    u32         a;      // 0x18
    u32         b;      // 0x1c
    u32         c;      // 0x20
    const void* d;      // 0x24
    const void* e;      // 0x28
    const void* f;      // 0x2c
    const void* g;      // 0x30
    const void* h;      // 0x34
    const void* i;      // 0x38
};
Desc g_desc1[64];       // 0x15aefd0 .. (14 records used)
Desc g_desc2[64];       // 0x15af358 .. (6 records used)
static char S_c[1];
static char S_0_n[1], S_0_d[1], S_0_e[1], S_0_f[1], S_0_g[1], S_0_h[1], S_0_i[1];
static char S_1_n[1], S_1_d[1], S_1_e[1], S_1_f[1], S_1_g[1], S_1_h[1], S_1_i[1];
static char S_2_n[1], S_2_d[1], S_2_e[1], S_2_f[1], S_2_g[1], S_2_h[1], S_2_i[1];
static char S_3_n[1], S_3_d[1], S_3_e[1], S_3_f[1], S_3_g[1], S_3_h[1], S_3_i[1];
static char S_4_n[1], S_4_d[1], S_4_e[1], S_4_f[1], S_4_g[1], S_4_h[1], S_4_i[1];
static char S_5_n[1], S_5_d[1], S_5_e[1], S_5_f[1], S_5_g[1], S_5_h[1], S_5_i[1];
// ---- items of slice s0138c040 end

// ---- items of slice s0138c850 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0138_c850; 
}
typedef eastl::string8_s0138_c850 string8_s0138_c850;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute_s0138_c850;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0138_c850&, void*);
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
typedef void* (*OffsetFunction_t)(Attribute_s0138_c850*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute_s0138_c850*);
}
namespace Simulator {
void* DefaultOffset(Attribute_s0138_c850* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute_s0138_c850
{
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
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);   // bool
}
namespace Simulator {
bool Read_00ae33d0(ISerializerReadStream* pStream, void* pData);   // Quaternion
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);   // ResourceKey
}
namespace Simulator {
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);   // uint64_t
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);   // Vector3
}
namespace Simulator {
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);   // vector<ResourceKey>
}
namespace Simulator {
bool Read_00f26be0(ISerializerReadStream* pStream, void* pData);   // cScenarioAsset
}
namespace Simulator {
bool Read_00f27170(ISerializerReadStream* pStream, void* pData);   // uint32_t[4]
}
namespace Simulator {
bool Read_00f293f0(ISerializerReadStream* pStream, void* pData);   // cScenarioString
}
namespace Simulator {
bool Read_00f2ae60(ISerializerReadStream* pStream, void* pData);   // posse members
}
namespace Simulator {
bool Read_00f2b8d0(ISerializerReadStream* pStream, void* pData);   // vector<uint32_t>
}
namespace Simulator {
bool Read_00f2f1b0(ISerializerReadStream* pStream, void* pData);   // markers
}
namespace Simulator {
bool Read_00f2f4f0(ISerializerReadStream* pStream, void* pData);   // acts
}
namespace Simulator {
bool Read_00f2f5e0(ISerializerReadStream* pStream, void* pData);   // vector<cScenarioClass>
}
namespace Simulator {
bool Read_00f2f6c0(ISerializerReadStream* pStream, void* pData);   // classes
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3400(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f25d80(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f268b0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f26c20(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f26ef0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f27010(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f27200(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f27290(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f27ee0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00f28ce0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692fd0(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_006930f0(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_00693120(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0138_c850& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ec0(char* pBuffer, void* pData);
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
void WriteText_00695010(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695040(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
bool Validate_00f25b60();
}
namespace Simulator {
bool Validate_00f25b80();
}
namespace Simulator {
bool Validate_00f26f90();
}
namespace Simulator {
bool Validate_00f26fd0();
}
namespace Simulator {
bool Validate_00f270b0();
}
namespace Simulator {
bool Validate_00f270f0();
}
namespace Simulator {
bool Validate_00f27330();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00595a70(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5700(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00b1fbf0(void* pData, const char* pName, int depth);   // same body as AlwaysValid (return true)
}
namespace Simulator {
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f28880(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f29b90(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f29ce0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f29e30(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f29f80(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f2a100(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f2a250(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00f2a510(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct Vector3;
}
namespace Simulator {
struct Quaternion;
}
namespace Simulator {
struct ResourceKey;
}
namespace Simulator {
struct ResourceKeyVector;
}
namespace Simulator {
extern Attribute_s0138_c850 cScenarioResource_sAttributes[34];   // 0x015af500
}
namespace Simulator {
#define ATTR(NAME, ID, OFFSET, RD, WR, RT, WT, VAL, XML, IDX) \
    a.name = NAME; a.id = ID; a.pCurrentObject = 0; a.setDefaultFunction = 0; \
    a.offsetFunction = DefaultOffset; a.readFunction = RD; a.writeFunction = WR; \
    a.readTextFunction = RT; a.writeTextFunction = WT; a.validateFunction = VAL; \
    a.toXmlFunction = XML; a.offset = (uint32_t)(OFFSET); \
    cScenarioResource_sAttributes[IDX] = a;
}
// ---- items of slice s0138c850 end

// ---- items of slice s0138d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char InitSharedAllocator();
extern void FUN_013c9950(void);
struct PropertyDesc {
    unsigned int name;   // +0x00  const char* (VA)
    unsigned int hash;   // +0x04
    unsigned int size;   // +0x08  byte size of the value
    unsigned int unk0c;  // +0x0c  uninitialised in the original
    unsigned int unk10;  // +0x10  uninitialised in the original
    unsigned int unk14;  // +0x14  uninitialised in the original
    unsigned int fn0;    // +0x18
    unsigned int fn1;    // +0x1c
    unsigned int fn2;    // +0x20
    unsigned int fn3;    // +0x24
    unsigned int fn4;    // +0x28
    unsigned int fn5;    // +0x2c
    unsigned int fn6;    // +0x30
    unsigned int fn7;    // +0x34
    unsigned int fn8;    // +0x38
};
// ---- items of slice s0138d560 end

// @ 0x01388f50
namespace Simulator {
void InitMyCaptainLevels()
{
    g_myCaptainLevels.mNameHash = EA::Hash::FNV1_String8("MyCaptainLevels", 0x811c9dc5, 1);
    g_myCaptainLevels.mpNext = g_myCaptainLevelsHead;
    g_myCaptainLevelsHead = &g_myCaptainLevels;
    g_myCaptainLevels.mpVtable = (void*)0x148ad9c;
    g_myCaptainLevels.mField0c = 0;
    g_myCaptainLevels.mField10 = 0;
    atexit(FUN_013c8c90);
}
}  // namespace Simulator

// @ 0x01389390
namespace Simulator {
void InitLimitStopwatch()
{
    new (&g_limitStopwatch) ::EA::Stopwatch(5, false);
    g_limitStopwatch.SetTimeLimit(0, false);
    atexit(FUN_013c8f90);
}
}  // namespace Simulator

// @ 0x013894f0
void InitScenarioModeUI()
{
  SceneModeUI* p = (SceneModeUI*)operator_new(0x234, "Simulator/ScearioMode/UI", 0, 0, 0, 0);
  g_spScenarioModeUI = p ? p->Construct() : 0;
  ((SceneModeAux*)g_spScenarioModeAux)->Init();
  atexit(&AtExit013c9070);
}

// @ 0x01389680
void InitHeadArray()
{
  for (int i = 0; i < 10; ++i) {
    g_spHeadArray[i].mpBegin = 0;
    g_spHeadArray[i].mpEnd = 0;
  }
  atexit(&AtExit013c9140);
}

// @ 0x0138a250
void InitServerIdAttributes()
{
  gServerIdAttributes[0] = Attribute("mKey",       0x62b74270, 0x00, rd_00ae3430_r0, wr_00ae3450_r0, rt_00693150_r0, wt_00695080_r0, uk_00b1fbf0_r0, u2_00ae5720_r0);
  gServerIdAttributes[1] = Attribute("mMachineId", 0x62b74271, 0x0c, rd_00572810_r1, wr_00572840_r1, rt_00693090_r1, wt_00694f00_r1, uk_00b1fbf0_r1, u2_00675ca0_r1);
  gServerIdAttributes[2] = Attribute("mServerId",  0x62b74272, 0x10, rd_00aff840_r2, wr_00aff870_r2, rt_00692fd0_r2, wt_00694ec0_r2, uk_00b1fbf0_r2, u2_00595a70_r2);
  gServerIdAttributes[3] = Attribute("mModelType", 0x62b74273, 0x18, rd_00572810_r3, wr_00572840_r3, rt_00693090_r3, wt_00694f00_r3, uk_00b1fbf0_r3, u2_00675ca0_r3);
}

// @ 0x0138a400
void InitSensorTagAttributes()
{
  gSensorTagAttributes[0] = Attribute("condition.conditionType",       0x7b78783, 0x00, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[1] = Attribute("condition.target.type",         0x7b7a2f2, 0x04, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[2] = Attribute("condition.target.value",        0x7b7a2f3, 0x08, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[3] = Attribute("action.actionType",             0x7b78786, 0x0c, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[4] = Attribute("action.target.type",            0x7bd3fae, 0x10, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[5] = Attribute("action.target.value",           0x7bd3fb4, 0x14, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[6] = Attribute("action.secondaryTarget.type",   0x7bd3fb8, 0x18, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
  gSensorTagAttributes[7] = Attribute("action.secondaryTarget.value",  0x7bd3fbd, 0x1c, rd_00572810, wr_00572840, rt_00692ff0, wt_00694ee0, uk_00b1fbf0, u2_0057cde0);
}

// @ 0x0138a710
void InitScenarioClassActAttributes()
{
  gScenarioClassActAttributes[0] = Attribute("teamBehavior", 0x7114ed5, 0x4a8, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[1] = Attribute("stanceBehavior", 0x7114ed6, 0x4ac, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[2] = Attribute("pickupBehavior", 0x7114ed7, 0x4b0, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[3] = Attribute("giveBehavior", 0x73923ef, 0x4b4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[4] = Attribute("movementBehavior", 0x7114ed8, 0x4b8, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[5] = Attribute("pickupTargetClassIndex", 0x7114ed9, 0x4bc, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[6] = Attribute("giveTargetClassIndex", 0x73b8345, 0x4c0, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[7] = Attribute("trackTargetClassIndex", 0x7114eda, 0x4c4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[8] = Attribute("awareness", 0x7114edb, 0x484, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[9] = Attribute("damageMultiplier", 0x7cc8d8a, 0x494, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[10] = Attribute("speedMultiplier", 0x7cc8d8f, 0x490, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[11] = Attribute("health_DEPRECATED", 0x7114edc, 0x488, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[12] = Attribute("healthMultiplier", 0x7cf7330, 0x48c, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[13] = Attribute("damageTuning", 0x7cf7430, 0x49c, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[14] = Attribute("radiusTuning", 0x7cf7530, 0x498, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[15] = Attribute("jumpTuning", 0x7cf7630, 0x4a0, rd_00572810_g2, wr_00ac88f0_g2, rt_006930b0_g2, wt_00694fc0_g2, uk_00b1fbf0_g2, u2_00acbb80_g2);
  gScenarioClassActAttributes[16] = Attribute("spawnDelay_", 0x7114fdd, 0x4a4, rd_00572810_g1, wr_00572840_g1, rt_00692ff0_g1, wt_00694ee0_g1, uk_00b1fbf0_g1, u2_0057cde0_g1);
  gScenarioClassActAttributes[17] = Attribute("invulnerable", 0x75f7aa0, 0x1, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[18] = Attribute("isDead", 0x75f7aa1, 0x2, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[19] = Attribute("visible", 0x7114ede, 0x0, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[20] = Attribute("dialogs_chatter", 0x7114ee1, 0x4, rd_00f2c950, wr_00f268f0, rt_00c2e4e0, wt_00692fb0, uk_00f26990, u2_00f29410);
  gScenarioClassActAttributes[21] = Attribute("dialogs_inspect", 0x7114ee3, 0x170, rd_00f2c950, wr_00f268f0, rt_00c2e4e0, wt_00692fb0, uk_00f26990, u2_00f29410);
  gScenarioClassActAttributes[22] = Attribute("descriptionDEPRECATED", 0x7114edf, 0x448, rd_00f293f0, wr_00f268b0, rt_00c2e4e0, wt_00692fb0, uk_00f25b60, u2_00f28880);
  gScenarioClassActAttributes[23] = Attribute("customBehavior", 0x7b787ea, 0x4c8, rd_00ac8750_g3, wr_00ac8780_g3, rt_00693090_g3, wt_00694fa0_g3, uk_00b1fbf0_g3, u2_0057ce00_g3);
  gScenarioClassActAttributes[24] = Attribute("customBehaviorEntries", 0x7b787fd, 0x4cc, rd_00f29560, wr_00f269d0, rt_00c2e4e0, wt_00692fb0, uk_00f26a60, u2_00f29650);
}

// @ 0x0138b190
void InitClassAttributes()
{
    cAttribute attr;

    attr.m_name = "type";
    attr.m_hash = 0x7114b5f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "targetClassIndex";
    attr.m_hash = 0x7114b60;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 4;
    g_attributes[1] = attr;

    attr.m_name = "targetClass2Index";
    attr.m_hash = 0x733df78;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 8;
    g_attributes[2] = attr;

    attr.m_name = "requiredCount";
    attr.m_hash = 0x71d3b1d;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0x0c;
    g_attributes[3] = attr;

    attr.m_name = "visibility";
    attr.m_hash = 0x71d3b1e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x10;
    g_attributes[4] = attr;

    attr.m_name = "dialog";
    attr.m_hash = 0x728ffd81;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2c950;
    attr.m_set = &s_f268f0;
    attr.m_parse = &s_b1fbf0;
    attr.m_toString = &s_57cde0;
    attr.m_serialise = &s_f29410;
    attr.m_fromString = &s_f26990;
    attr.m_offset = 0x18;
    g_attributes[5] = attr;

    attr.m_name = "flags";
    attr.m_hash = 0x7bbdea5;
    attr.m_zero0 = 0;
    attr.m_zero1 = &s_f26ac0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26aa0;
    attr.m_set = &s_f27ec0;
    attr.m_parse = &s_b1fbf0;
    attr.m_toString = &s_57cde0;
    attr.m_serialise = &s_ac8050;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0x14;
    g_attributes[6] = attr;
}

// @ 0x0138b560
void InitSimulatorAttributes()
{
    cAttribute attr;

    attr.m_name = "acts";
    attr.m_hash = 0x7114973;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2e370;
    attr.m_set = &s_f26b00;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f26ba0;
    attr.m_serialise = &s_f297a0;
    attr.m_offset = 0x70;
    g_attributes[0] = attr;

    attr.m_name = "castName";
    attr.m_hash = 0x7114975;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f293f0;
    attr.m_set = &s_f268b0;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b60;
    attr.m_serialise = &s_f28880;
    attr.m_offset = 0x2788;
    g_attributes[1] = attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x7114976;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[2] = attr;

    attr.m_name = "isDeepEditEnabled";
    attr.m_hash = 0x96a9466b;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x20;
    g_attributes[3] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset";
    attr.m_hash = 0x96a94671;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x28;
    g_attributes[4] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset_Secondary";
    attr.m_hash = 0x96a94670;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x50;
    g_attributes[5] = attr;

    attr.m_name = "gfxOverideType";
    attr.m_hash = 0x96a9466e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x24;
    g_attributes[6] = attr;

    attr.m_name = "gfxOverideTypeSecondary";
    attr.m_hash = 0x96a9466f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x48;
    g_attributes[7] = attr;

    attr.m_name = "assetKeyDEPRECATED";
    attr.m_hash = 0x7114972;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ae3430;
    attr.m_set = &s_ae3450;
    attr.m_parse = &s_693150;
    attr.m_toString = &s_695080;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_ae5720;
    attr.m_offset = 0x27c4;
    g_attributes[8] = attr;

    attr.m_name = "modelTypeDEPRECATED";
    attr.m_hash = 0x74fc4f6;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694f00;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_675ca0;
    attr.m_offset = 0x27d0;
    g_attributes[9] = attr;

    attr.m_name = "serverIDDEPRECATED";
    attr.m_hash = 0x7114974;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_aff840;
    attr.m_set = &s_aff870;
    attr.m_parse = &s_692fd0;
    attr.m_toString = &s_694ec0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_595a70;
    attr.m_offset = 0x27d8;
    g_attributes[10] = attr;
}

// @ 0x0138b9b0
void InitVsliderAttributes()
{
    cAttribute attr;

    attr.m_name = "acts";
    attr.m_hash = 0x7114973;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2e370;
    attr.m_set = &s_f26b00;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f26ba0;
    attr.m_serialise = &s_f297a0;
    attr.m_offset = 0x70;
    g_attributes[0] = attr;

    attr.m_name = "castName";
    attr.m_hash = 0x7114975;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f293f0;
    attr.m_set = &s_f268b0;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b60;
    attr.m_serialise = &s_f28880;
    attr.m_offset = 0x2788;
    g_attributes[1] = attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x7114976;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[2] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset";
    attr.m_hash = 0x96a94671;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x28;
    g_attributes[3] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset_Secondary";
    attr.m_hash = 0x96a94670;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x50;
    g_attributes[4] = attr;

    attr.m_name = "gfxOverideType";
    attr.m_hash = 0x96a9466e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x24;
    g_attributes[5] = attr;

    attr.m_name = "gfxOverideTypeSecondary";
    attr.m_hash = 0x96a9466f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x48;
    g_attributes[6] = attr;
}

// @ 0x0138bc70
void InitAssetPartAttributes()
{
    cAttribute attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x1c3f08b3;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "isLocked";
    attr.m_hash = 0x7c4c078;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x20;
    g_attributes[1] = attr;

    attr.m_name = "assetKeyDEPRECATED";
    attr.m_hash = 0x1c3f08b1;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ae3430;
    attr.m_set = &s_ae3450;
    attr.m_parse = &s_693150;
    attr.m_toString = &s_695080;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_ae5720;
    attr.m_offset = 0x24;
    g_attributes[2] = attr;

    attr.m_name = "serverIDDEPRECATED";
    attr.m_hash = 0x1c3f08b2;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_aff840;
    attr.m_set = &s_aff870;
    attr.m_parse = &s_692fd0;
    attr.m_toString = &s_694ec0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_595a70;
    attr.m_offset = 0x30;
    g_attributes[3] = attr;
}

// @ 0x0138be20
void InitPatrolAttributes()
{
    cAttribute attr;

    attr.m_name = "wanderRadius";
    attr.m_hash = 0x76dc170;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_ac88f0;
    attr.m_parse = &s_6930b0;
    attr.m_toString = &s_694fc0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbb80;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "patrolPositionDEPRECATED";
    attr.m_hash = 0x76dc171;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_b6e3a0;
    attr.m_set = &s_ac88c0;
    attr.m_parse = &s_6930f0;
    attr.m_toString = &s_695010;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbba0;
    attr.m_offset = 4;
    g_attributes[1] = attr;

    attr.m_name = "teleportPositionDEPRECATED";
    attr.m_hash = 0x76dc172;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_b6e3a0;
    attr.m_set = &s_ac88c0;
    attr.m_parse = &s_6930f0;
    attr.m_toString = &s_695010;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbba0;
    attr.m_offset = 0x10;
    g_attributes[2] = attr;

    attr.m_name = "patrolPath";
    attr.m_hash = 0x7114773;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_c41210;
    attr.m_set = &s_c40e80;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_c41b00;
    attr.m_offset = 0x1c;
    g_attributes[3] = attr;

    attr.m_name = "patrolStyle";
    attr.m_hash = 0x7114774;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x30;
    g_attributes[4] = attr;
}

// @ 0x0138c040
void f0138c040()
{
    Desc d;

    d.name = (const char*)0x148cb7c; d.id = 0x71147e5; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0x572840; d.f = (const void*)0x692ff0;
    d.g = (const void*)0x694ee0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0x57cde0;
    d.size = 0;
    g_desc1[0] = d;

    d.name = (const char*)0x13ed4e4; d.id = 0x71147e6; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xb6e3a0; d.e = (const void*)0xac88c0; d.f = (const void*)0x6930f0;
    d.g = (const void*)0x695010; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbba0;
    d.size = 4;
    g_desc1[1] = d;

    d.name = (const char*)0x1447370; d.id = 0x71147e7; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xae33d0; d.e = (const void*)0xae3400; d.f = (const void*)0x693120;
    d.g = (const void*)0x695040; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xae5700;
    d.size = 0x10;
    g_desc1[2] = d;

    d.name = (const char*)0x148cb70; d.id = 0x71147ea; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x220;
    g_desc1[3] = d;

    // The original also sets a one-time-init flag (bit 0 of 0x16c847c) while filling
    // record 4 -- an artefact of a static local in the original source.  Reproduced
    // here so the function is observably equivalent.
    if ((*(volatile u32*)0x16c847c & 1u) == 0u) *(volatile u32*)0x16c847c |= 1u;

    d.name = (const char*)0x145ca9c; d.id = 0x71147eb; d.a = 0; d.b = 0xf26c60; d.c = 0x692ca0;
    d.d = (const void*)0xf26aa0; d.e = (const void*)0xf27ec0; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xac8050;
    d.size = 0x224;
    g_desc1[4] = d;

    d.name = (const char*)0x13f2d1c; d.id = 0x71147e8; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x20;
    g_desc1[5] = d;

    d.name = (const char*)0x148cb58; d.id = 0x71147e9; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x24;
    g_desc1[6] = d;

    d.name = (const char*)0x1452788; d.id = 0x78d5a93; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x1e0;
    g_desc1[7] = d;

    d.name = (const char*)0x1452794; d.id = 0x78d5a94; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x1e4;
    g_desc1[8] = d;

    d.name = (const char*)0x148cb44; d.id = 0x78d5895; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xb6e3a0; d.e = (const void*)0xac88c0; d.f = (const void*)0x6930f0;
    d.g = (const void*)0x695010; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbba0;
    d.size = 0x1e8;
    g_desc1[9] = d;

    d.name = (const char*)0x148cb30; d.id = 0x71148e7; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xae33d0; d.e = (const void*)0xae3400; d.f = (const void*)0x693120;
    d.g = (const void*)0x695040; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xae5700;
    d.size = 0x1f4;
    g_desc1[10] = d;

    d.name = (const char*)0x148cb20; d.id = 0x71148ea; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0x572810; d.e = (const void*)0xac88f0; d.f = (const void*)0x6930b0;
    d.g = (const void*)0x694fc0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0xacbb80;
    d.size = 0x204;
    g_desc1[11] = d;

    d.name = (const char*)0x148cb10; d.id = 0x71148e9; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xce27a0; d.e = (const void*)0xf26ca0; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xb1fbf0; d.i = (const void*)0x103c3a0;
    d.size = 0x20c;
    g_desc1[12] = d;

    d.name = (const char*)0x148ca9c; d.id = 0x76ca8d3; d.a = 0; d.b = 0; d.c = 0x692ca0;
    d.d = (const void*)0xf2d430; d.e = (const void*)0xf26d30; d.f = (const void*)0xc2e4e0;
    d.g = (const void*)0x692fb0; d.h = (const void*)0xf26dd0; d.i = (const void*)0xf298f0;
    d.size = 0x28;
    g_desc1[13] = d;
}

// @ 0x0138c5d0
void f0138c5d0()
{
    Desc d;

    d.name = S_0_n; d.id = 0x711477d; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_0_d; d.e = S_0_e; d.f = S_0_f; d.g = S_0_g; d.h = S_0_h; d.i = S_0_i;
    d.size = 0;
    g_desc2[0] = d;

    d.name = S_1_n; d.id = 0x711477e; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_1_d; d.e = S_1_e; d.f = S_1_f; d.g = S_1_g; d.h = S_1_h; d.i = S_1_i;
    d.size = 0x3c;
    g_desc2[1] = d;

    d.name = S_2_n; d.id = 0x711477c; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_2_d; d.e = S_2_e; d.f = S_2_f; d.g = S_2_g; d.h = S_2_h; d.i = S_2_i;
    d.size = 0x78;
    g_desc2[2] = d;

    d.name = S_3_n; d.id = 0x711477f; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_3_d; d.e = S_3_e; d.f = S_3_f; d.g = S_3_g; d.h = S_3_h; d.i = S_3_i;
    d.size = 0x7c;
    g_desc2[3] = d;

    d.name = S_4_n; d.id = 0x78fe86a; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_4_d; d.e = S_4_e; d.f = S_4_f; d.g = S_4_g; d.h = S_4_h; d.i = S_4_i;
    d.size = 0x80;
    g_desc2[4] = d;

    d.name = S_5_n; d.id = 0x711477b; d.a = 0; d.b = 0; d.c = (u32)S_c;
    d.d = S_5_d; d.e = S_5_e; d.f = S_5_f; d.g = S_5_g; d.h = S_5_h; d.i = S_5_i;
    d.size = 0x84;
    g_desc2[5] = d;
}

// @ 0x0138c850
namespace Simulator {
void InitScenarioResourceAttributes()
{
    Attribute_s0138_c850 a;
    ATTR("avatarPosition", 0x07102e68, 0x150,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 0)
    ATTR("avatarHealthMultiplier", 0x07c8cbfe, 0x170,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 1)
    ATTR("avatarIsInvulnerable", 0x07c8d9a6, 0x174,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 2)
    ATTR("avatarOrientation", 0x07102e69, 0x15c,
         Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AlwaysValid<Quaternion>, ToXml_00ae5700, 3)
    ATTR("avatarScale", 0x07579cb4, 0x16c,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 4)
    ATTR("bAvatarLocked", 0x07734a68, 0x175,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 5)
    ATTR("initialPosseMembers", 0x07749ad3, 0x178,
         Read_00f2ae60, Write_00f26ef0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f26f90, ToXml_00f29b90, 6)
    ATTR("numAllowedPosseMembers", 0x07749afe, 0x238,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 7)
    ATTR("classes", 0x072a9b58, 0x2bf4,
         Read_00f2f6c0, Write_00f27ee0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f26fd0, ToXml_00f29ce0, 8)
    ATTR("acts", 0x07102e6a, 0x23c,
         Read_00f2f4f0, Write_00f27010, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f270b0, ToXml_00f29e30, 9)
    ATTR("markers", 0x07102e6c, 0x2c10,
         Read_00f2f1b0, Write_00f28ce0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f270f0, ToXml_00f29f80, 10)
    ATTR("winText", 0x07102e70, 0xb8,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 11)
    ATTR("loseText", 0x07102e71, 0xf4,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 12)
    ATTR("introText", 0x07102e72, 0x7c,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 13)
    ATTR("type", 0x07102e76, 0x78,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 14)
    ATTR("bIsMission", 0x07102e77, 0x2c2c,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 15)
    ATTR("classIDCounter", 0x07906d3c, 0x2c0c,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 16)
    ATTR("mScreenshotTypes", 0x07cf8e1b, 0x68,
         Read_00f27170, Write_00f25d80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<uint32_t[4]>, ToXml_00b1fbf0, 17)
    ATTR("mAvatarAsset", 0x07102e78, 0x130,
         Read_00f26be0, Write_00f26c20, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b80, ToXml_00f2a510, 18)
    ATTR("markerPositioningVersion", 0x07f33740, 0x2c50,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 19)
    ATTR("usedAppPackIds", 0x07f33741, 0x2c54,
         Read_00f2b8d0, Write_00f27200, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<uint32_t*>, ToXml_00f2a100, 20)
    ATTR("cameraTarget", 0x07ea0c00, 0x2c30,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 21)
    ATTR("cameraOrientation", 0x07ea0c10, 0x2c3c,
         Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AlwaysValid<Quaternion>, ToXml_00ae5700, 22)
    ATTR("cameraDistance", 0x07ea0c20, 0x2c4c,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 23)
    ATTR("avatarAssetKeyDEPRECATED", 0x07102e67, 0x2c94,
         Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720, 24)
    ATTR("avatarServerIDDEPRECATED", 0x07102e6f, 0x2ca0,
         Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0, AlwaysValid<uint64_t>, ToXml_00595a70, 25)
    ATTR("atmosphereScoreDEPRECATED", 0x07102e6d, 0x54,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 26)
    ATTR("temperatureScoreDEPRECATED", 0x07102e6e, 0x58,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 27)
    ATTR("classesOld", 0x07102e6b, 0x2c6c,
         Read_00f2f5e0, Write_00f27290, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f27330, ToXml_00f2a250, 28)
    ATTR("initialPosseMemberKeysDEPRECATED", 0x07749ad2, 0x2c80,
         Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ResourceKeyVector>, ToXml_00c6c4e0, 29)
    ATTR("waterScoreDEPRECATED", 0x07102e73, 0x50,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 30)
    ATTR("mbIsTimeLockedDEPRECATED", 0x07102e74, 0x5c,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 31)
    ATTR("mTimeElapsedDEPRECATED", 0x07102e75, 0x60,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 32)
    ATTR("mbCustomScreenshotThumbnailDEPRECATED", 0x074b9f5a, 0x64,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 33)
}
}  // namespace Simulator

// @ 0x0138d560
void init_15afd38()
{
    static const PropertyDesc desc[9] = {
        { 0x148cd30, 0x7905d42, 0x130,  0,0,0, 0,0,
          0x692ca0, 0xf26be0, 0xf26c20, 0xc2e4e0, 0x692fb0, 0xf25b80, 0xf2a510 },
        { 0x148cdcc, 0x7734a68, 0x175,  0,0,0, 0,0,
          0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00 },
        { 0x148cda0, 0x7905d3c, 0x238,  0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x148cd88, 0x7905d3e, 0xb8,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x148cd7c, 0x7905d3f, 0xf4,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x148cd70, 0x7905d40, 0x7c,   0,0,0, 0,0,
          0x692ca0, 0xf293f0, 0xf268b0, 0xc2e4e0, 0x692fb0, 0xf25b60, 0xf28880 },
        { 0x1412cf4, 0x7905d41, 0x78,   0,0,0, 0,0,
          0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0 },
        { 0x148ca9c, 0x7be36ef, 0x23c,  0,0,0, 0,0,
          0x692ca0, 0xf2f4f0, 0xf27010, 0xc2e4e0, 0x692fb0, 0xf270b0, 0xf29e30 },
        { 0x148cd98, 0x7be710b, 0x2bf4, 0,0,0, 0,0,
          0x692ca0, 0xf2f6c0, 0xf27ee0, 0xc2e4e0, 0x692fb0, 0xf26fd0, 0xf29ce0 },
    };
    PropertyDesc* dst = (PropertyDesc*)0x15afd38;
    for (int i = 0; i < 9; ++i)
        dst[i] = desc[i];
}

// @ 0x0138e640
void init_16c8b40()
{
    if (*(int*)0x16c8b40 == 0) {
        char ok = InitSharedAllocator();
        *(char*)0x16c8b48 = 1;
        if (!ok)
            *(char*)0x16c8b48 = 0;
    } else {
        *(char*)0x16c8b48 = 0;
    }
    atexit(&FUN_013c9950);
}
