// src/game/SPGonzago/SPGameData.cpp -- migrated from slice(s) s01318c70, s00b181d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl sqrt(double);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(sqrt)
#pragma intrinsic(__rdtsc)

// ---- items of slice s00b181d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
struct IRef {
  virtual int AddRef();
  virtual int Release();
};
struct IStreamW {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* Get18();
};
struct IStreamB {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual IStreamW* GetWriter();
};
namespace SP {
class cGameData_s00b1_81d0;
}
namespace SP {
struct cDefTable {
  unsigned Lookup(unsigned id);  // 0x00f3e8a0 (ret 4)
};
}
namespace SP {
class cApp { public:
  char pad[0x74];
  cDefTable* mpDefs;
};
}
namespace SP {
class cVarListSerializer_s00b1_81d0 { public:
  char mBuf[0xa14];
  cVarListSerializer_s00b1_81d0(cGameData_s00b1_81d0* gd, const void* table, unsigned id);  // 0x00692f90 (ret 0xc)
  void Serialize(IStreamB* s);                                       // 0x00692900 (ret 4)
};
}
namespace SP {
void* __cdecl WriteUint32(void* stream, const void* p, int n, int z);  // 0x0093aa70
}
namespace SP {
extern void* vtbl_cGameData0;  // 0x0145d060
}
namespace SP {
extern void* vtbl_cGameData1;  // 0x0145d050
}
namespace SP {
extern void* vtbl_Base0;       // 0x013eb938
}
namespace SP {
extern void* vtbl_Base1;       // 0x013ec458
}
namespace SP {
extern int gGameDataCount;     // 0x0167be2c
}
namespace SP {
extern cApp* gApp;             // 0x016c7aa4
}
namespace SP {
extern char gVarTable[];       // 0x01567e48
}
namespace SP {
struct RefCountBase {  // EA::RefCountVTemplate<int> part at +4 (inline ctor stores)
  void* vtbl1;
  int mRefCount;
  RefCountBase() {
    vtbl1 = &vtbl_Base1;
    mRefCount = 0;
  }
};
}
namespace SP {
class cGameData_s00b1_81d0 { public:
  void* vtbl0;     // +0x00
  RefCountBase mRC;  // +0x04
  void* mpNext;    // +0x0c
  void* mpPrev;    // +0x10
  int mIsDestroyed;  // +0x14
  u32 mID;           // +0x18
  u32 mDefinitionID;  // +0x1c
  u8 mb20;            // +0x20
  u8 mb21;            // +0x21
  u32 m24;            // +0x24
  u32 mView;          // +0x28
  IRef* mpOwner;      // +0x2c
  u32 mPoliticalID;   // +0x30

  bool WriteSerializableObjectCheck();   // 0x00b183e0
  void NotifyDirty(bool b);              // 0x00b189a0
  void VtableSlot40(int a);              // 0x00b183f0
  bool Init(void* a, int b, int c);      // 0x00b18400
  void DtorBody();                       // 0x00b184c0
  unsigned GetDefinition();              // 0x00b18530
  void SetOwner(IRef* o);                // 0x00b18550
  void Write(IStreamB* s);               // 0x00b18590
  cGameData_s00b1_81d0();                           // 0x00b18660
  cGameData_s00b1_81d0* ScalarDeletingDtor(u8 f);   // 0x00b186b0
};
}
using SP::cGameData_s00b1_81d0;
struct RefHolder {
  u32 m0, m4, m8;
  IRef* mC;
  RefHolder* Ctor(u32 a, u32 b, IRef* o);
};
// ---- items of slice s00b181d0 end

// ---- items of slice s01318c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_8c70; 
}
typedef eastl::string8_s0131_8c70 string8_s0131_8c70;
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
typedef void  (*ReadTextFunction_t)(const string8_s0131_8c70&, void*);
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
    Attribute() {}

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
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);     // 0x00572810
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);   // 0x00572840
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0131_8c70& text, void* pData);          // 0x00693090
}
namespace Simulator {
template<typename T> bool AlwaysValid();                                          // 0x00b1fbf0
}
namespace Simulator {
bool Read_00b00430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05de0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05ec0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b05fa0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b0c730(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20510(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b20570(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b21e60(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b26970(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b1fbf0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aca060(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aca090(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00acdf10(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00bab620(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b02570(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b02630(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b035b0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b26990(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00b1fbf0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba7590(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ba94e0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_8c70& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool Validate_00b6f860();
}
namespace Simulator {
bool Validate_00b004e0();
}
namespace Simulator {
bool Validate_00b00520();
}
namespace Simulator {
bool Validate_00b20230();
}
namespace Simulator {
bool Validate_00ba7450();
}
namespace Simulator {
bool Validate_00d011e0();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00d022e0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00b04120(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00fe4be0(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot GameData_sAttributes[5];               // 0x01567e48
}
namespace Simulator {
#define INT_ATTR      Read4<int>, Write4<int>, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0
}
namespace Simulator {
#define SHORT_ATTR    Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0
}
namespace Simulator {
#define BOOL_ATTR     Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
#define STATIC_INT_ATTR  Read4<int>, Write4<int>, ReadTextInt<int>, WriteText_00694f00, AlwaysValid<int>
}
namespace Simulator {
#define FLAGS_ATTR    Read_00b00430, Write_00b02570, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
}
namespace Simulator {
#define TREE_OBJ_ATTR Read_00b05de0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define TREE_OBJ2_ATTR Read_00b05ec0, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define MULTIMAP_ATTR Read_00b05fa0, Write_00b035b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b004e0, ToXml_00d022e0
}
namespace Simulator {
#define CLUMP_ATTR    Read_00b0c730, Write_00b02630, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b00520, ToXml_00b04120
}
namespace Simulator {
#define OWNER_ATTR    Read_00aca060, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define AVATAR_ATTR   Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define AVATARHERD_ATTR Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define PTRIBE_ATTR   Read_00aca090, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define PPLAYER_ATTR  Read_00b20570, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050
}
namespace Simulator {
#define POSSE_ATTR    Read_00acdf10, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f860, ToXml_00c6c390
}
namespace Simulator {
#define POLMAP_ATTR   Read_00b21e60, Write_00ba94e0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ba7450, ToXml_00baa2b0
}
namespace Simulator {
#define NOUNS_ATTR    Read_00b1fbf0, Write_00b1fbf0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b20230, ToXml_00ac8050
}
namespace Simulator {
#define OBJCOUNT_ATTR Read_00bab620, Write_00ba7590, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00d011e0, ToXml_00fe4be0
}
namespace Simulator {
#define TIMESTAMP_ATTR Read_00b26970, Write_00b26990, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<int>, ToXml_00ac8050
}
namespace Simulator {
#define PLANETKEY_ATTR Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<int>, ToXml_00ae5720
}
// ---- items of slice s01318c70 end

// @ 0x00b183e0
bool cGameData_s00b1_81d0::WriteSerializableObjectCheck()
{
  return mb21 == 0;
}

// @ 0x00b183f0
void cGameData_s00b1_81d0::VtableSlot40(int)
{
  ((int(__thiscall*)(void*))(*(void***)this)[16])(this);
}

// @ 0x00b18400
bool cGameData_s00b1_81d0::Init(void* a, int, int)
{
  if (a) {
    mView = ((u32*)a)[1];
    return mView != 0;
  }
  return false;
}

// @ 0x00b18490
RefHolder* RefHolder::Ctor(u32 a, u32 b, IRef* o)
{
  m0 = a;
  m4 = b;
  m8 = 0;
  mC = o;
  if (o)
    o->AddRef();
  return this;
}

// @ 0x00b184c0
void cGameData_s00b1_81d0::DtorBody()
{
  vtbl0 = &vtbl_cGameData0;
  mRC.vtbl1 = &vtbl_cGameData1;
  gGameDataCount--;
  if (mpOwner)
    mpOwner->Release();
  mRC.vtbl1 = &vtbl_Base1;
  vtbl0 = &vtbl_Base0;
}

// @ 0x00b18530
unsigned cGameData_s00b1_81d0::GetDefinition()
{
  if (mDefinitionID == 0xffffffff)
    return 0;
  cDefTable* t = SP::gApp->mpDefs;
  return t->Lookup(mDefinitionID);
}

// @ 0x00b18550
void cGameData_s00b1_81d0::SetOwner(IRef* o)
{
  IRef* old = mpOwner;
  if (o != old) {
    if (o)
      o->AddRef();
    mpOwner = o;
    if (old)
      old->Release();
  }
  if (o)
    mPoliticalID = ((cGameData_s00b1_81d0*)o)->mPoliticalID;
}

// @ 0x00b18590
void cGameData_s00b1_81d0::Write(IStreamB* s)
{
  unsigned magic;
  IStreamW* ww = s->GetWriter();
  magic = 0x17f243b;
  void* w = ww->Get18();
  SP::WriteUint32(w, &magic, 1, 0);
  SP::cVarListSerializer_s00b1_81d0 ser(this, SP::gVarTable, 0x1a80d26);
  ser.Serialize(s);
}

// @ 0x00b18660
cGameData_s00b1_81d0::cGameData_s00b1_81d0()
{
  vtbl0 = &vtbl_cGameData0;
  mRC.vtbl1 = &vtbl_cGameData1;
  mIsDestroyed = 0;
  mID = 0;
  mDefinitionID = 0xffffffff;
  mb20 = 0;
  mb21 = 0;
  m24 = 0xffffffff;
  mView = 0;
  mpOwner = 0;
  mPoliticalID = 0xffffffff;
  mpNext = 0;
  mpPrev = 0;
  gGameDataCount++;
}

// @ 0x013194a0
namespace Simulator {
void InitGameDataAttributes()
{
    { Attribute a("mpGameDataOwner", 0x240e421, 0x2c, Read_00aca060, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050); *(Attribute*)&GameData_sAttributes[0] = a; }
    { Attribute a("mIsDestroyed", 0x240e422, 0x21, Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00); *(Attribute*)&GameData_sAttributes[1] = a; }
    { Attribute a("mPoliticalID", 0x240e423, 0x30, Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0); *(Attribute*)&GameData_sAttributes[2] = a; }
    { Attribute a("mDefinitionID", 0x2e9efd3, 0x28, Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0); *(Attribute*)&GameData_sAttributes[3] = a; }
    { Attribute a("mID", 0x3cdd54b, 0x24, Read4<short>, Write4<short>, ReadTextInt<short>, WriteText_00694f00, AlwaysValid<short>, ToXml_00675ca0); *(Attribute*)&GameData_sAttributes[4] = a; }
}
}  // namespace Simulator
