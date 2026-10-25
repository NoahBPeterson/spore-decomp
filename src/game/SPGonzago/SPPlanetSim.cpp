// src/game/SPGonzago/SPPlanetSim.cpp -- migrated from slice(s) s01396a80, s00ff21d0, s00ff11c0, s00feff80, s00f28680, s00f27670, s00f25a40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlanetSim.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cVarListSerializer.h"
#include "SP/cCityData.h"
#include "SP/cBuildingData.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribe.h"
#include "SP/cTribeData.h"
#include "SP/cVehicleData.h"

// unnamed retail callees and globals (address in the comment)
extern char DAT_015aeb58;

// ---- items of slice s00f25a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mgr695b40 { void Add(void* p, const void* a, const wchar_t* s); };
extern char DAT_015aeb58;
// ---- items of slice s00f25a40 end

// ---- items of slice s00f27670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  sub_eece20(void*);
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b, int c, int d);
extern "C" void  __cdecl FUN_00f47380(void* p);
extern "C" void  __cdecl FUN_00720200(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00f25ea0(void* a, void* b, void* c);
typedef unsigned int uint;
struct CBase { void dtor(); };  // 0x006b5240 base destructor
extern "C" size_t __cdecl wcslen(const wchar_t*);
struct CS {
  char _pad[0x14];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int GetText();
};
struct StrObj {
  uint f00;
  char _pad4[0x14 - 4];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int fn277f0();
  bool fn278b0();
};
struct Elem { char _pad4[4]; CS s; char _tail[0x40 - sizeof(CS)]; };
struct Zeroed {
  float f00, f04, f08, f0c, f10, f14, f18;
  int i1c, i20, i24;
  int _pad28, _pad2c;
  int i30;
  Zeroed* fn280b0();
};
struct CStr {
  char  _pad00[0x14];  // 0x00..0x13
  char* mBegin1;       // +0x14
  char* mCap1;         // +0x18
  char* mEnd1;         // +0x1c
  char  _pad20[0x0c];  // 0x20..0x2b
  char* mBegin2;       // +0x2c
  char* mCap2;         // +0x30
  char* mEnd2;         // +0x34
  ~CStr();
};
struct Vec18 {
  char* begin;   // +0x00
  char* end;     // +0x04
  char* cap;     // +0x08
  void reserve(unsigned n);
};
struct AllocHdr { int mOwner; };  // 4-byte allocation header before the element buffer
struct Vec38 {
  char* begin;   // +0x00
  char* end;     // +0x04
  char* cap;     // +0x08
  void reserve(unsigned n);
};
// ---- items of slice s00f27670 end

// ---- items of slice s00f28680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char A_01667bac;   // eastl::gEmptyString16  (empty wide buffer)
extern "C" char B_01667bae;   // gEmptyString16 + 2 bytes
extern "C" char g_015aff90;
extern "C" char g_015aefd0;
int   FUN_00ef1990(void* a, void* b);
void  FUN_0093aa70(void* io, const void* src, uint n, int byteOrder); // EA::IO::WriteUint32
int   FUN_00f26770(void* ser, const wchar_t* name, int flag, const wchar_t* type);
int   FUN_00f26810(void* ser, const wchar_t* name, int flag, const wchar_t* type);
int   FUN_00eeea50(void* self, void* out);
struct String16 { unsigned short* b; unsigned short* e; unsigned short* c; };
struct WStr {
  wchar_t* b; wchar_t* e; wchar_t* c;
  void ctor(const String16* src);                          // 0x0056e2d0
  void assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  void append(const wchar_t* s);                           // 0x005c3d90
  void range_initialize(const wchar_t* first);             // 0x00579a90
};
void FUN_0093c5a0(String16* out, const char* src, int n);            // 0x0093c5a0 ConvertToString16
struct ListSer {
  char pad[0xa14];
  void ctor(const void* src, void* generic, uint sig);               // 0x00692f90
  char Read(void* stream);                                           // 0x00693e10
  void Serialize(void* ser);                                         // 0x00692900
};
struct IOut {
  virtual void o0();
  virtual void o1();
  virtual void o2();
  virtual void o3();
  virtual void o4();
  virtual void o5();
  virtual void* o6();
};
struct ISer {
  virtual void s0(const wchar_t*);
  virtual void s1(const wchar_t*);
  virtual void s2();
  virtual void s3(const wchar_t*);
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual IOut* s8();
};
struct CS_s00f2_8680 {
  int r0;                       // +0x00
  void* pLocal;                 // +0x04
  const wchar_t* pSrc;          // +0x08
  int pid;                      // +0x0c
  char hasTokens;               // +0x10
  char f11;                     // +0x11
  short pad;                    // +0x12
  const wchar_t* GetText();                     // 0x006b55c0
  void ctor(uint id, uint table, const wchar_t* s);  // 0x006b5770
  CS_s00f2_8680& operator=(const CS_s00f2_8680& other);               // 0x006b5430
  void dtor();                                  // 0x006b5240
  ~CS_s00f2_8680() { dtor(); }
};
struct TextObj {
  CS_s00f2_8680 cs;                        // +0x00
  WStr ws;                      // +0x14
  int a20;                      // +0x20
  uint id24;                    // +0x24
  uint id28;                    // +0x28
  int fn28c50(void* stream);
};
struct ObjD {
  int f00;                      // +0x00
  TextObj t;                    // +0x04
};
struct Str {
  char _pad[0x10];
  int Assign(const wchar_t* p, const wchar_t* e);
};
struct CStrCtor {
  char _pad[0x14];
  void ctor();
};
struct Obj8c {
  int f00;
  CStrCtor cs;          // +0x04
  int a18, a1c, a20;    // +0x18
  int _g24;             // +0x24
  int a28, a2c;         // +0x28
  int a30, a34, a38;    // +0x30
  int _g3c;
  int a40;              // +0x40
  Obj8c* init();
};
struct ObjC {
  char _pad[0x14];
  Str s;                // +0x14
  int f24;              // +0x24
  ObjC* fn28c10(short* p);
};
static void buildName(const char* name, String16* src, WStr* out) {
  if (name != 0) {
    FUN_0093c5a0(src, name, -1);
  } else {
    src->b = (unsigned short*)&A_01667bac;
    src->e = src->b;
    src->c = (unsigned short*)&B_01667bae;
  }
  out->ctor(src);
}
static void freeString16(String16& s) {
  if (s.b != 0 && (((uint)((char*)s.e - (char*)s.b) & 0xfffffffeu) > 2))
    FUN_00f47380(s.b);
}
static void freeWStr(WStr& s) {
  if (s.b != 0 && (((uint)((char*)s.e - (char*)s.b) & 0xfffffffeu) > 2))
    FUN_00f47380(s.b);
}
struct BigObj {
  char _pad[0x2788];
  TextObj txt;          // +0x2788
  int fn28b80(WStr* out);
};
struct E38 { int w[14]; };
struct Vec38_s00f2_8680 {
  E38* b; E38* e; E38* c;
  E38* erase(E38* first, E38* last);
  void insert(char* pos, uint count, char* value);
  void insertOne(char* pos, char* value);
};
// ---- items of slice s00f28680 end

// ---- items of slice s00feff80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
class IStream_s00fe_ff80;
}
}
namespace EA {
namespace IO {
bool WriteUint16(IStream_s00fe_ff80* pStream, const uint32_t* pValue, uint32_t nCount, int nFlags);     // 0x0093a9d0
}
}
namespace EA {
namespace IO {
bool WriteUint16Raw(IStream_s00fe_ff80* pStream, const uint16_t* pValue, uint32_t nCount, int nFlags);  // 0x0093a700
}
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s00fe_ff80* pStream, const uint32_t* pValue, uint32_t nCount, int nFlags);     // 0x0093aa70
}
}
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct cInt3 {
    int32_t x;    // +0x00
    int32_t y;    // +0x04
    int32_t z;    // +0x08
};
}
namespace SP {
struct cVector3 {
    union {
        struct { float x; float y; float z; };                    // +0x00
        struct { int32_t mWord0; int32_t mWord1; int32_t mWord2; };
    };
};
}
namespace SP {
static inline void CopyPositionFloats(cVector3* pDest, const cVector3* pSource)
{
    pDest->x = pSource->x;
    pDest->y = pSource->y;
    pDest->z = pSource->z;
}
}
namespace SP {
static inline void CopyPositionWords(cVector3* pDest, const cVector3* pSource)
{
    pDest->mWord0 = pSource->mWord0;
    pDest->mWord1 = pSource->mWord1;
    pDest->mWord2 = pSource->mWord2;
}
}
namespace SP {
struct cResourceKey {
    uint32_t mModelType;    // +0x00
    uint32_t mField04;      // +0x04
    uint32_t mField08;      // +0x08
};
}
namespace SP {
extern int32_t sStoredModelKeys[16];                                          // 0x015b4df8
}
namespace SP {
bool sGetIndexFromModelType(uint32_t modelType, uint32_t* pIndex);           // 0x00ff03d0
}
namespace SP {
static inline uint32_t FindModelKeyIndex(uint32_t modelType)
{
    for (int i = 0; i < 16; ++i) {
        if (sStoredModelKeys[i] == (int32_t)modelType)
            return (uint32_t)i;
    }
    return 0;
}
}
namespace SP {
static inline int CountBits(uint32_t bits)
{
    uint32_t v = bits;
    v = v - ((v >> 1) & 0x55555555u);
    v = (v & 0x33333333u) + ((v >> 2) & 0x33333333u);
    v = (v + (v >> 4)) & 0x0f0f0f0fu;
    return (int)((v * 0x01010101u) >> 24);
}
}
namespace SP {
class cStreamWriter {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void v5();
    virtual EA::IO::IStream_s00fe_ff80* GetStream();                     // +0x18
};
}
namespace SP {
class cOutStream {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool End();                                       // +0x1c
    virtual cStreamWriter* GetWriter();                       // +0x20
};
}
namespace SP {
static inline void WriteStreamCount(cOutStream* pStream, uint32_t nCount)
{
    cStreamWriter* pWriter = pStream->GetWriter();
    EA::IO::IStream_s00fe_ff80* pPos = pWriter->GetStream();
    EA::IO::WriteUint32(pPos, &nCount, 1, 0);
}
}
namespace SP {
extern void* gCityVarList[2];        // 0x015b5510
}
namespace SP {
extern void* gCivVarList[2];         // 0x015b59c0
}
namespace SP {
extern void* gVehicleVarList[2];     // 0x015b4f28
}
namespace SP {
extern void* gBuildingVarList[2];    // 0x015b5018
}
namespace SP {
class cVarListSerializer_s00fe_ff80 {
public:
    cVarListSerializer_s00fe_ff80(void* pObject, void* pVarList, uint32_t nSignature);  // 0x00692f90
    bool Serialize(cOutStream* pStream);                                     // 0x00692900
    bool SerializeAlt(cOutStream* pStream);                                  // 0x00693e10

    int32_t mStorage[0xa14 / 4];      // property table + object/var-list pointers
};
}
namespace SP {
class cSpatialObject_s00fe_ff80 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void va();
    virtual const cVector3* GetPosition();                    // +0x2c
virtual void vb2();
virtual void vb3();
virtual void vb4();
virtual void vb5();
};
}
namespace SP {
class cTribe_s00fe_ff80 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void va();
virtual void vb();
virtual void vc();
virtual void vd();
virtual void ve();
virtual void vf();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual uint32_t GetPoliticalID();                        // +0x4c
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
    virtual void v28();
    virtual uint32_t GetFood();                               // +0xa4

    char mPad04[0x120 - 0x04];                                // +0x004 .. +0x120
    cSpatialObject_s00fe_ff80 mSpatial;                                  // +0x120
    int32_t GetAdultPopulation();                             // 0x00c8f370
};
}
namespace SP {
class cStarManager_s00fe_ff80 {
public:
    uint32_t GetCurrentPoliticalID();                         // 0x00ba6630
};
}
namespace SP {
class cGameNounManager_s00fe_ff80;
}
namespace SP {
extern cVector3 gDefaultTribePosition;                        // 0x016dad08
}
namespace SP {
cGameNounManager_s00fe_ff80* NounManager();                              // 0x00b3d300
}
namespace SP {
cStarManager_s00fe_ff80* __stdcall StarManager(int nUniverse);           // 0x00b3d2a0
}
namespace SP {
struct cTribeData_s00fe_ff80 {
    uint32_t mPoliticalID;    // +0x00
    cVector3 mPosition;       // +0x04
    int32_t  mPopulation;     // +0x10
    int32_t  mFood;           // +0x14

    cTribeData_s00fe_ff80();
    cTribeData_s00fe_ff80(int32_t nPopulation, int32_t nFood);
    cTribeData_s00fe_ff80(cTribe_s00fe_ff80* pTribe);
};
}
namespace SP {
class cBuildingThing {
public:
    char mPad00[0x30];
    float mField30;           // +0x30
};
}
namespace SP {
class cCityBlock {
public:
    char mPad00[0x3c];
    cBuildingThing** mpThingsBegin;   // +0x3c
    cBuildingThing** mpThingsEnd;     // +0x40
};
}
namespace SP {
class cBuildingData_s00fe_ff80 {
public:
    Vec3 mPosition;           // +0x00
    char mPad0c[0x38 - 0x0c];
};
}
namespace SP {
class cCityData_s00fe_ff80 {
public:
    cInt3    mKey;                     // +0x00
    char     mPad0c[0x10];             // +0x0c
    float    mValue;                   // +0x1c
    int32_t  mField20;                 // +0x20
    int32_t  mNumBuildings;            // +0x24
    uint8_t  mTurretMask;              // +0x28
    char     mPad29[0x07];             // +0x29
    float    mThreatLevel;             // +0x30
    char     mPad34[0x2c];             // +0x34
    uint16_t mName[14];                // +0x60
    cBuildingData_s00fe_ff80* mpBuildingsBegin;   // +0x7c
    cBuildingData_s00fe_ff80* mpBuildingsEnd;     // +0x80
    char     mPad84[0x15c - 0x84];     // +0x84
    cCityBlock** mpBlocksBegin;        // +0x15c
    cCityBlock** mpBlocksEnd;          // +0x160

    bool TestNameBit(int nIndex, uint32_t nBit) const;     // 0x00ff0330
    void AddValue(float fDelta);                           // 0x00ff0350
    int  GetPercent() const;                               // 0x00ff0400
    void SetKey(const cInt3* pKey);                        // 0x00ff0430
    void Write(cOutStream* pStream);                       // 0x00ff0450
    void WriteRaw(cOutStream* pStream);                    // 0x00ff04d0
    int  GetNumTurrets() const;                            // 0x00ff0760
    cBuildingData_s00fe_ff80* GetBuilding(int nIndex);                // 0x00ff07a0
    void RemoveTurret();                                   // 0x00ff07e0
    int  GetNumBuildings() const;                          // 0x00ff0870
    void SetThreatLevel(float fLevel, cCityData_s00fe_ff80* pCity);   // 0x00ff08b0
    void SetAlert(bool bAlert);                            // 0x00b8d980
    bool IsAlerted();                                      // 0x00b8d9a0
};
}
namespace SP {
class cTerrainSphere_s00fe_ff80 {
public:
    char mPad00[0x1108];
    int32_t mSphereType;      // +0x1108
};
}
namespace SP {
class cGameNounManager_s00fe_ff80 {
public:
    cTerrainSphere_s00fe_ff80* GetCurrentTerrainSphere();    // 0x00f67d90
};
}
namespace SP {
class cNoun {
public:
    char mPad00[0x34];
    cSpatialObject_s00fe_ff80 mSpatial;     // +0x34 (its GetPosition is at +0x2c)
    char mPad38[0xb1c - 0x38];   // +0x38
    int32_t mFieldB1c;           // +0x0b1c
    int32_t mFieldB20;           // +0x0b20
};
}
namespace SP {
class cResourceNoun {
public:
    char mPad00[0x34];
    int32_t mResourceType;       // +0x34
};
}
namespace SP {
class cSpatialSnapshot {
public:
    cVector3 mPosition;          // +0x00
    int32_t  mField0c;           // +0x0c
    int32_t  mField10;           // +0x10

    cSpatialSnapshot* Init(cNoun* pNoun);                     // 0x00ff0db0
    cSpatialSnapshot& Set(const cVector3* pPosition, int32_t nField0c,
                          int32_t nField10);                  // 0x00ff0df0
};
}
namespace SP {
class cVehicleData_s00fe_ff80 {
public:
    char mPad00[4];
};
}
namespace SP {
class cCivData_s00fe_ff80 {
public:
    cResourceKey* mpModelKeys;      // +0x00
    char mPad04[0x28 - 0x04];       // +0x04
    cVehicleData_s00fe_ff80** mpVehiclesBegin; // +0x28
    cVehicleData_s00fe_ff80** mpVehiclesEnd;   // +0x2c
    char mPad30[0x3c - 0x30];       // +0x30
    cCityData_s00fe_ff80** mpCitiesBegin;      // +0x3c
    cCityData_s00fe_ff80** mpCitiesEnd;        // +0x40

    void CopyTerrainKeys();                     // 0x00ff0940
    cResourceKey* GetResourceKey(cResourceNoun* pNoun);  // 0x00ff0cd0
    void Write(cOutStream* pStream);            // 0x00ff0e20

    // copy the three terrain keys named by a terrain-sphere rule into the shared slots
    void CopyThreeKeys(uint32_t nKeyA, uint32_t nKeyB, uint32_t nKeyC)
    {
        uint32_t nSlotA = FindModelKeyIndex(nKeyA);
        uint32_t nSlotB = FindModelKeyIndex(nKeyB);
        uint32_t nSlotC = FindModelKeyIndex(nKeyC);
        uint32_t nSlotD = FindModelKeyIndex(0xbc1041e6);
        mpModelKeys[nSlotD] = mpModelKeys[nSlotA];
        uint32_t nSlotE = FindModelKeyIndex(0xc15695da);
        mpModelKeys[nSlotE] = mpModelKeys[nSlotB];
        uint32_t nSlotF = FindModelKeyIndex(0x2090a11b);
        mpModelKeys[nSlotF] = mpModelKeys[nSlotC];
    }
};
}
namespace SP {
class cBuildingList {
public:
    const cBuildingData_s00fe_ff80* mpBegin;    // +0x00
    const cBuildingData_s00fe_ff80* mpEnd;      // +0x04
};
}
namespace SP {
bool WriteSTLSequenceT(cOutStream* pStream, const cBuildingList* pBuildings);  // 0x00ff0f30
}
// ---- items of slice s00feff80 end

// ---- items of slice s00ff11c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
void __cdecl operator_delete_array(void* p);      // 0x00f47380
void* __cdecl memcpy_fn(void* dst, const void* src, unsigned int n);   // 0x011e0744
struct cWString {
    void* mpBegin;                 // 0x00
    void* mpEnd;                   // 0x04
    void* mpCap;                   // 0x08

    void assign(const void* first, const void* last);   // 0x00423650
};
struct cOrnamentDataA {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    bool  mFlag24;                 // 0x24
    bool  mFlag25;                 // 0x25
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    int   mField34;                // 0x34

    cOrnamentDataA& operator=(const cOrnamentDataA& o);   // 0x00ff11c0
};
struct cOrnamentDataB {
    float mF00;                    // 0x00
    float mF04;                    // 0x04
    float mF08;                    // 0x08
    float mF0c;                    // 0x0c
    float mF10;                    // 0x10
    float mF14;                    // 0x14
    float mF18;                    // 0x18
    float mF1c;                    // 0x1c
    int   mField20;                // 0x20
    int   mField24;                // 0x24
    int   mField28;                // 0x28
    int   mField2c;                // 0x2c
    int   mField30;                // 0x30
    u8    mPad0034[0x38 - 0x34];

    cOrnamentDataB& operator=(const cOrnamentDataB& o);   // 0x00ff1230
};
struct cTextHolder {
    u8        mPad0000[0x40];
    cWString  mText40;             // 0x40
    u8        mPad004c[0x50 - 0x4c];
    cWString  mText50;             // 0x50

    void SetText40(const cWString* src);   // 0x00ff14f0
    void SetText50(const cWString* src);   // 0x00ff1510
};
struct cCityData {
    u8 mPad0000[0x38];

    ~cCityData();                  // 0x00ff13c0
};
struct cCivData {
    u8           mPad0000[0x28];
    int*         mpValues28;       // 0x28
    int*         mpValuesEnd2c;    // 0x2c
    u8           mPad0030[0x3c - 0x30];
    cCityData**  mpCities3c;       // 0x3c
    cCityData**  mpCitiesEnd40;    // 0x40

    void EraseCity(int index);     // 0x00ff1fb0
    void EraseValue(int value);    // 0x00ff1ff0
};
// ---- items of slice s00ff11c0 end

// ---- items of slice s00ff21d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_0093a780(void* stream, void* dst, int count, int a);  // EA::IO::ReadInt32
extern "C" void* __cdecl memcpy(void* d, const void* s, unsigned n);
#pragma warning(disable : 4100)
typedef unsigned int  u32;
typedef unsigned short u16;
struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };
void  __cdecl FUN_00ff08b0(void* self, float f, int arg);  // 0x00ff08b0
struct VecHolder;
struct CityVehicle;
struct TileEntity;
extern u32  g_16dad08;   // 0x016dad08  (float bits)
extern u32  g_16dad0c;   // 0x016dad0c
extern u32  g_16dad10;   // 0x016dad10
extern u32  g_15b4e38;   // 0x015b4e38
extern u32  g_15b4e3c;   // 0x015b4e3c
extern u32  g_15b4e40;   // 0x015b4e40
extern u32  g_15b4e44;   // 0x015b4e44
extern u16  g_emptyString16_begin[1];   // 0x01667bac
extern u16  g_emptyString16_end[1];     // 0x01667bae
struct cVarListSerializer
{
    u32  mData[0x280];                                   // +0x000
    int  mSerializableVarCount;                          // +0xa00
    int  mSerializedVarCount;                            // +0xa04
    u32  mSignature;                                     // +0xa08
    void* mpObject;                                      // +0xa0c
    void* mpSerializerList;                              // +0xa10
    void Ctor(void* inst, void* dat, int tag);           // 0x692f90
    char Serialize(void* stream);                        // 0x693e10
};
struct VectorEC
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Erase();                       // 0x00e25bd0 vector::erase(begin,end) (general)
    void EraseBld();                    // 0x00f28dd0 eastl::vector<cBuildingData>::erase
    void EraseOrn();                    // 0x00ff1840 eastl::vector<cOrnamentData>::erase
    void InsertSlow(void* pos, const void* val);            // 0x00b96600 (ret 8)
    void InsertBld(void* pos, const void* val);             // 0x00ff1650 (ret 8)
    void InsertOrn(void* pos, const void* val);             // 0x00ff18a0 (ret 8)
};
struct cOrnamentData
{
    float f00, f04, f08, f0c, f10, f14, f18, f1c;
    u32   u20, u24, u28, u2c, u30;
};
struct VecOrn
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Erase(void* first, void* last);            // 0x00ff1840 (ret 8)
    void Resize(u32 n);                             // 0x00ff1790 (ret 4)
    void InsertSlow(void* pos, const void* val);    // 0x00ff18a0 (ret 8)
};
struct cBuildingData
{
    Float3 mPos;                               // 0x00..0x0c
    Float4 mOri;                               // 0x0c..0x1c
    float f1c;                                 // 0x1c
    u32   u20;                                 // 0x20
    u8    b24;                                 // 0x24
    u8    b25;                                 // 0x25
    u16   pad26;                               // 0x26
    u32   u28;                                 // 0x28
    u32   u2c;                                 // 0x2c
    u32   u30;                                 // 0x30
    u32   u34;                                 // 0x34
    void Assign(const cBuildingData* src);     // 0x00ff11c0 (thiscall, ret 4)
};
struct cOrnamentData2
{
    Float3 mPos;                               // 0x00..0x0c
    Float4 mOri;                               // 0x0c..0x1c
    float f1c;                                 // 0x1c
    u32   u20;                                 // 0x20
    u32   u24;                                 // 0x24
    u32   u28;                                 // 0x28
    u32   u2c;                                 // 0x2c
    u32   u30;                                 // 0x30
};
struct cCityData_s00ff_21d0
{
    void Destroy();                 // 0x00ff13c0 (thiscall dtor)
    void Init();                    // 0x00ff1cb0 (thiscall ctor helper)
    void ReadFrom(void* stream);    // 0x00ff04d0 (thiscall, ret 4)

    Float3 mPos;                    // 0x00
    Float4 mOri;                    // 0x0c
    float f1c;                      // 0x1c
    u32   u20;                      // 0x20
    u32   u24;                      // 0x24
    u8    mFlags;                   // 0x28
    u8    pad29[0x2c - 0x29];
    u32   u2c;                      // 0x2c
    float f30;                      // 0x30
    u32   u34;                      // 0x34
    u32   u38;                      // 0x38
    float f3c;                      // 0x3c
    u16*  mBeg;                     // 0x40
    u16*  mEnd;                     // 0x44
    u16*  mCap;                     // 0x48
    u32   pad4c;                    // 0x4c
    u16*  m2Beg;                    // 0x50
    u16*  m2End;                    // 0x54
    u16*  m2Cap;                    // 0x58
    u8    pad5c[0x60 - 0x5c];       // 0x5c..0x60
    u16   mSummary[0x0e];           // 0x60 (14 u16 groups for the 196-bitmap)
    VectorEC mBuildings;            // 0x7c (vector of cBuildingData, 0x38 elems)
    u8    pad88[0x90 - 0x88];       // 0x88..0x90
    VectorEC mOrnaments;            // 0x90 (vector of cOrnamentData, 0x34 elems)
    u8    pad9c[0xa4 - 0x9c];       // 0x9c..0xa4
    VectorEC m4;                    // 0xa4 (vector, 0xc-size elems)
    u8    padB0[0xb8 - 0xb0];       // 0xb0..0xb8
    u32   uB8;                      // 0xb8
    u32   uBC;                      // 0xbc
    u32   uC0;                      // 0xc0
};
struct cCitySummary
{
    VectorEC mPacked;               // 0x00  (vector of cCityData*)
    VectorEC mVehicles;             // 0x0c  (vector of cVehicleData*)
    u8       pad18[0x20 - 0x18];
    int      mPackCnt20;            // 0x20  running popcount tally
    int      mPackSum24;            // 0x24  running (u24 - popcount) tally
    VectorEC mCityData;             // 0x28  (vector of cCityData*, owned by l28)
    u8       pad34[0x3c - 0x34];
    VectorEC mBuildingList;         // 0x3c  (vector of cCityData*)
    u32      pad48[0x60 - 0x48];

    // 0x00ff2c70 -- account for one record's bit count into the summary tallies.
    void AddRecord(cCityData_s00ff_21d0* rec);                     // ret 4
    // 0x00ff2d50 -- remove the record at index (frees and pops).
    void RemoveAt(int index);                           // ret 8
    // 0x00ff2d80 -- release all records and both vectors.
    void ResetForward();
    // 0x00ff2e30 -- release everything plus the three owning vectors.
    void Destroy();
};
struct Spatial
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    Float3* GetPosition();                                  // +0x2c
    Float4* GetOrientation();                               // +0x30
};
struct cCity
{
    // vtable pointer at +0 (a single vptr; the individual virtual slots are not touched here).
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual void v90();

    u8    pad04[0x120 - 0x04];
    // (0x120) mSpatial -- the city's spatial sub-object (vtable +0x2c GetPosition, +0x30 GetOrientation)
    Spatial mSpatial120;            // 0x120
    u8    pad124[0x2e8 - 0x124];
    u32   u2e8;                     // 0x2e8
    u32   u2ec;                     // 0x2ec
    u8    pad2f0[0x340 - 0x2f0];
    int   mVecBeg340;               // 0x340
    int   mVecEnd344;               // 0x344
    u8    pad348[0x354 - 0x348];
    int   mVecBeg354;               // 0x354
    int   mVecEnd358;               // 0x358
    u8    pad35c[0x3ec - 0x35c];
    // 0x3ec -- the action circle storage (cast to cActionCircle* by the callers)
    u8    pad3ec[0x748 - 0x3ec];
    float f748;                     // 0x748
    u32   u74c;                     // 0x74c

    // 0x00bd8110 / 0x00bd8b80 / 0x00bd7d00 / 0x00bd81d0 -- scalar queries (thiscall).
    u32   Query8110();
    u32   Query8b80();
    float Query7d00();
    u32   GetVehicleSpecialty();
    // 0x00bd8130 -- the ornament entity vector (thiscall).
    VecHolder* OrnamentVec();
    // 0x00bd9e20 -- the packed-tile entity (thiscall).
    TileEntity* TileEntity();
    // 0x00bd7f60 -- the city action circle (thiscall).
    void* ActionCircle();
};
struct cActionCircle
{
    u8   pad00[0x50];
    int  mBeg50;                                            // +0x50
    int  mCap54;                                            // +0x54
    void* SlotAt(u32 slot);                                 // 0x00af9ff0
};
struct SlotObject
{
    CityVehicle* ToVehicle();                               // 0x00fcc210
};
struct SerObj
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    void* Channel();                                        // +0x18
};
struct SerHost
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    void Close();                                           // +0x1c
    SerObj* Stream();                                       // +0x20
};
struct EntitySpatial
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    Float3* GetPosition();          // +0x2c
    Float4* GetOrientation();       // +0x30
};
struct FileSlot
{
    u32 Count();                                            // 0x008e7f80 GetFileCount
};
struct TileEntity
{
virtual void v00();
virtual void v04();
virtual void v08();
    void* AsInterface(u32 id);                              // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    u32  GetId();                                           // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void v60();
    u32  GetPackedId();                                     // +0x64
    u8   pad68[0x274 - 0x68];
    u8   mFlags274[0xc4];                                   // 0x274 (packed tile flags)
};
struct CityVehicle
{
virtual void v00();
virtual void v04();
virtual void v08();
    void* AsInterface(u32 id);                              // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    u32  GetId();                                           // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
    virtual void v60();
    u32  GetPackedId();                                     // +0x64
    u8   SpecialByte();                                     // 0x00c3f540 (thiscall)

    EntitySpatial mSpatial34;       // 0x34 (building path)
    u8   pad64[0x70 - 0x64];
    EntitySpatial mSpatial70;       // 0x70 (ornament path, via a +0x70 cast)

    u8   padA4[0x120 - 0xa4];
    FileSlot mFiles;                // 0x120
    u8   pad124[0x158 - 0x124];
    float f158;                     // 0x158
    u8   pad15c[0x22c - 0x15c];
    u32  u22c;                      // 0x22c
    u8   pad230[0x289 - 0x230];
    u8   u289;                      // 0x289
    u8   pad28a[0x28c - 0x28a];
    int  i28c;                      // 0x28c
    int  i290;                      // 0x290
};
struct VecHolder
{
    void** mBegin;                  // +0x00
    void** mEnd;                    // +0x04
    void** mCap;                    // +0x08
};
static __inline u32 PopCount8(u32 b)
{
    u32 x = b - ((b >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = ((x >> 4) + x) & 0x0f0f0f0fu;
    return (x * 0x01010101u) >> 24;
}
// ---- items of slice s00ff21d0 end

// ---- items of slice s01396a80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0139_6a80; 
}
typedef eastl::string8_s0139_6a80 string8_s0139_6a80;
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
typedef void  (*ReadTextFunction_t)(const string8_s0139_6a80&, void*);
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
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
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
    /* 1Ch */ int setDefaultFunction;
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
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
bool R0(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W0(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT0(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT0(char*, void*);
}
namespace Simulator {
bool V0();
}
namespace Simulator {
bool X0(void*, const char*, int);
}
namespace Simulator {
bool R1(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W1(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT1(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT1(char*, void*);
}
namespace Simulator {
bool V1();
}
namespace Simulator {
bool X1(void*, const char*, int);
}
namespace Simulator {
bool R2(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W2(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT2(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT2(char*, void*);
}
namespace Simulator {
bool V2();
}
namespace Simulator {
bool X2(void*, const char*, int);
}
namespace Simulator {
bool R3(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W3(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT3(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT3(char*, void*);
}
namespace Simulator {
bool V3();
}
namespace Simulator {
bool X3(void*, const char*, int);
}
namespace Simulator {
bool R4(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W4(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT4(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT4(char*, void*);
}
namespace Simulator {
bool V4();
}
namespace Simulator {
bool X4(void*, const char*, int);
}
namespace Simulator {
bool R5(ISerializerReadStream*, void*);
}
namespace Simulator {
bool W5(ISerializerWriteStream*, void*);
}
namespace Simulator {
void RT5(const string8_s0139_6a80&, void*);
}
namespace Simulator {
void WT5(char*, void*);
}
namespace Simulator {
bool V5();
}
namespace Simulator {
bool X5(void*, const char*, int);
}
namespace Simulator {
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_sAttributes[IDX] = a; }
}
namespace Simulator {
extern AttrSlot g_sAttributes[];
}
namespace Simulator {
template<typename T> bool IRead(ISerializerReadStream*, void*);
}
namespace Simulator {
template<typename T> bool IWrite(ISerializerWriteStream*, void*);
}
namespace Simulator {
template<typename T> void IReadText(const string8_s0139_6a80&, void*);
}
namespace Simulator {
template<typename T> void IWriteText(char*, void*);
}
namespace Simulator {
template<typename T> bool IValid();
}
namespace Simulator {
template<typename T> bool IToXml(void*, const char*, int);
}
namespace Simulator {
bool ValidInt();                                // 0x00b1fbf0, shared by the int rows
}
namespace Simulator {
bool ToXmlIntShared(void*, const char*, int);   // 0x0057cde0, shared by the int rows
}
namespace Simulator {
struct C0; struct C1; struct C2; struct C3; struct C4;
}
namespace Simulator {
struct C5; struct C6; struct C7; struct C8; struct C9;
}
namespace Simulator {
#define INT_ROW(T) IRead<T>, IWrite<T>, IReadText<T>, IWriteText<T>, ValidInt, ToXmlIntShared
}
namespace Simulator {
extern AttrSlot g_creatureAttrs[];   // 0x015b5018
}
namespace Simulator {
#define ADD2(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&g_creatureAttrs[IDX] = a; }
}
// ---- items of slice s01396a80 end

// @ 0x00f26fd0
bool fn26fd0(Mgr695b40* self, int* range)
{
  int* p = (int*)range[0];
  int* e = (int*)range[1];
  while (p != e) {
    if (p != (int*)-8) self->Add((char*)p + 8, &DAT_015aeb58, L"cScenarioClass");
    p = (int*)((char*)p + 0x27e8);
  }
  return true;
}

// @ 0x00f278b0
bool StrObj::fn278b0()
{
  bool r = false;
  if (sub_eece20(this) == (int)0xcf56099a) {
    uint t = f00;
    if (t == 0x90c48d09 || t == 0x3144b430) r = true;
    else if (fn277f0()) r = true;
  }
  return r;
}

// @ 0x00f278f0
bool fn278f0(int* range)
{
  if ((range[1] - range[0]) / 0x44 == 0) return false;
  for (int i = 0; i < (range[1] - range[0]) / 0x44; ++i) {
    Elem* e = (Elem*)(range[0] + i * 0x44);
    int len;
    if (e->s.f28 != 0 && e->s.f24 != 0)
      len = (int)wcslen((const wchar_t*)e->s.GetText());
    else
      len = (e->s.f18 - e->s.f14) >> 1;
    if (len != 0) return true;
  }
  return false;
}

// @ 0x00f27fc0
int fn27fc0(int begin, int end, uint* key)
{
  int n = (end - begin) / 0x18;
  while (n > 0) {
    int half = n >> 1;
    uint* mid = (uint*)(begin + half * 0x18);
    bool less;
    if (*mid != key[0])
      less = *mid < key[0];
    else if (mid[2] != key[2])
      less = mid[2] < key[2];
    else
      less = mid[1] < key[1];
    if (less) {
      begin = (int)(mid + 6);
      n = n + (-1 - half);
    } else {
      n = half;
    }
  }
  return begin;
}

// @ 0x00f280b0
Zeroed* Zeroed::fn280b0()
{
  f00 = 0.0f; f04 = 0.0f; f08 = 0.0f; f0c = 0.0f;
  f10 = 0.0f; f14 = 0.0f; f18 = 0.0f;
  i1c = 0; i20 = 0; i24 = 0; i30 = 0;
  return this;
}

// @ 0x00f280f0
CStr::~CStr()
{
  if (((((int)(mEnd2 - mBegin2)) & ~1) > 2) && mBegin2) FUN_00f47380(mBegin2);
  if (((((int)(mEnd1 - mBegin1)) & ~1) > 2) && mBegin1) FUN_00f47380(mBegin1);
  ((CBase*)this)->dtor();
}

// @ 0x00f28140
void Vec18::reserve(unsigned n)
{
  unsigned capCount = (unsigned)((cap - begin) / 0x18);
  if (n > capCount) {
    char* p;
    if (n)
      p = (char*)FUN_00f473a0(n * 0x18, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    else
      p = 0;
    FUN_00720200(begin, end, p);
    if (begin)
      FUN_00f47380(begin);
    unsigned count = (unsigned)((end - begin) / 0x18);
    begin = p;
    end = p + count * 0x18;
    cap = p + n * 0x18;
  }
}

// @ 0x00f28280
void Vec38::reserve(unsigned n)
{
  unsigned capCount = (unsigned)((cap - begin) / 0x38);
  if (n > capCount) {
    char* p;
    if (n)
      p = (char*)FUN_00f473a0(n * 0x38, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    else
      p = 0;
    FUN_00f25ea0(begin, end, p);
    if (begin && ((AllocHdr*)begin)[-1].mOwner != 0)
      FUN_00f47380(begin);
    unsigned count = (unsigned)((end - begin) / 0x38);
    begin = p;
    end = p + count * 0x38;
    cap = p + n * 0x38;
  }
}

// @ 0x00f28680
int fn28680(void* ser, const char* name, int flag)
{
  if (flag == 0) return 1;
  String16 src;
  WStr w;
  buildName(name, &src, &w);
  freeString16(src);
  int r = FUN_00f26770(ser, (w.b != w.e) ? w.b : 0, flag, L"cScenarioGoal");
  freeWStr(w);
  return r;
}

// @ 0x00f28780
int fn28780(void* ser, const char* name, int flag)
{
  if (flag == 0) return 1;
  String16 src;
  WStr w;
  buildName(name, &src, &w);
  freeString16(src);
  int r = FUN_00f26810(ser, (w.b != w.e) ? w.b : 0, flag, L"cScenarioClassAct");
  freeWStr(w);
  return r;
}

// @ 0x00f28880
int fn28880(ISer* ser, const char* name, TextObj* obj)
{
  if (obj != 0) {
    bool empty;
    if (obj->id28 == 0 || obj->id24 == 0) {
      empty = (obj->ws.b == obj->ws.e);
    } else {
      const wchar_t* p = obj->cs.GetText();
      empty = (p[0] == 0);
    }
    if (!empty) {
      String16 src;
      WStr w;
      buildName(name, &src, &w);
      freeString16(src);
      if (w.b != w.e) ser->s0(w.b);
      const wchar_t* val =
          (obj->id28 != 0 && obj->id24 != 0) ? obj->cs.GetText() : obj->ws.b;
      ser->s3(val);
      if (w.b != w.e) ser->s1(w.b);
      freeWStr(w);
    }
  }
  return 1;
}

// @ 0x00f289d0
int fn289d0(ISer* ser, const char* name, ObjD* q)
{
  if (q != 0) {
    TextObj* obj = &q->t;
    bool empty;
    if (obj->id28 == 0 || obj->id24 == 0) {
      empty = (obj->ws.b == obj->ws.e);
    } else {
      const wchar_t* p = obj->cs.GetText();
      empty = (p[0] == 0);
    }
    if (!empty) {
      String16 src;
      WStr w;
      buildName(name, &src, &w);
      freeString16(src);
      if (w.b != w.e) ser->s0(w.b);
      ser->s0(L"cScenarioDialog");
      fn28880(ser, "text", obj);
      ser->s1(L"cScenarioDialog");
      if (w.b != w.e) ser->s1(w.b);
      freeWStr(w);
    }
  }
  return 1;
}

// @ 0x00f28b30
Obj8c* Obj8c::init()
{
  f00 = 0;
  cs.ctor();
  a18 = (int)&A_01667bac;
  a1c = (int)&A_01667bac;
  a20 = (int)&B_01667bae;
  a28 = 0;
  a2c = 0;
  a30 = (int)&A_01667bac;
  a34 = (int)&A_01667bac;
  a38 = (int)&B_01667bae;
  a40 = 0;
  return this;
}

// @ 0x00f28b80
int BigObj::fn28b80(WStr* out)
{
  TextObj* obj = &txt;
  bool empty;
  if (obj->id28 == 0 || obj->id24 == 0) {
    empty = (obj->ws.b == obj->ws.e);
  } else {
    const wchar_t* p = obj->cs.GetText();
    empty = (p[0] == 0);
  }
  if (!empty) {
    const wchar_t* s =
        (obj->id28 != 0 && obj->id24 != 0) ? obj->cs.GetText() : obj->ws.b;
    const wchar_t* e = s;
    while (*e != 0) ++e;
    out->assign(s, e);
    return 1;
  }
  return FUN_00eeea50(this, out);
}

// @ 0x00f28c10
ObjC* ObjC::fn28c10(short* p)
{
  f24 = 0;
  const wchar_t* q = (const wchar_t*)p;
  while (*q) ++q;
  int len = (int)(q - (const wchar_t*)p);
  s.Assign((const wchar_t*)p, (const wchar_t*)p + len);
  return this;
}

// @ 0x00f28c50
int TextObj::fn28c50(void* stream)
{
  ListSer ser;
  ser.ctor(this, &g_015aff90, 0x1a80d26);
  if (!ser.Read(stream)) return 0;
  if (id24 != 0 && id28 != 0) {
    CS_s00f2_8680 tmp;
    tmp.ctor(id24, id28, 0);
    cs = tmp;
    tmp.dtor();
    ws.append((const wchar_t*)0x13ec468);
  }
  return 1;
}

// @ 0x00f28ce0
void fn28ce0(ISer* ser, int* vec)
{
  char* end = (char*)vec[1];
  char* pos;
  if ((uint)vec[5] < 0x3fffffff) pos = (char*)vec[0] + vec[5] * 0x238;
  else pos = end;

  uint count = (uint)FUN_00ef1990(pos, end);
  IOut* out = ser->s8();
  void* io = out->o6();
  FUN_0093aa70(io, &count, 1, 0);

  char* p;
  if ((uint)vec[5] < 0x3fffffff) p = (char*)vec[0] + vec[5] * 0x238;
  else p = end;

  while (p != end) {
    ListSer buf;
    buf.ctor(p + 4, &g_015aefd0, 0x1a80d26);
    buf.Serialize(ser);
    for (;;) {
      uint u = *(uint*)p;
      p += 0x238;
      if ((u >> 0x1e) & 1) break;
      if (*(int*)p >= 0) break;
    }
  }
  ser->s7();
}

// @ 0x00f28dd0
E38* Vec38_s00f2_8680::erase(E38* first, E38* last)
{
  E38* stop = e;
  E38* d = first;
  for (E38* s = last; s != stop; ++s) { *d = *s; ++d; }
  e = stop - (last - first);
  return first;
}

// @ 0x00ff03d0
namespace SP {
bool sGetIndexFromModelType(uint32_t modelType, uint32_t* pIndex)
{
    for (int i = 0; i < 16; ++i) {
        if (modelType == (uint32_t)sStoredModelKeys[i]) {
            *pIndex = (uint32_t)i;
            return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00ff0400
namespace SP {
int cCityData_s00fe_ff80::GetPercent() const
{
    int nTotal = mField20 + mNumBuildings;
    if (nTotal != 0)
        return (mField20 * 1000) / nTotal;
    return 1000;
}
}  // namespace SP

// @ 0x00ff0430
namespace SP {
void cCityData_s00fe_ff80::SetKey(const cInt3* pKey)
{
    mKey.x = pKey->x;
    mKey.y = pKey->y;
    mKey.z = pKey->z;
}
}  // namespace SP

// @ 0x00ff0450
namespace SP {
void cCityData_s00fe_ff80::Write(cOutStream* pStream)
{
    for (int i = 0; i < 14; ++i) {
        cStreamWriter* pWriter = pStream->GetWriter();
        uint32_t nWord = mName[i];
        EA::IO::IStream_s00fe_ff80* pPos = pWriter->GetStream();
        EA::IO::WriteUint16(pPos, &nWord, 1, 0);
    }
    cVarListSerializer_s00fe_ff80 serializer(this, gCityVarList, 0x1a80d26);
    serializer.Serialize(pStream);
}
}  // namespace SP

// @ 0x00ff04d0
namespace SP {
void cCityData_s00fe_ff80::WriteRaw(cOutStream* pStream)
{
    for (int i = 0; i < 14; ++i) {
        cStreamWriter* pWriter = pStream->GetWriter();
        EA::IO::IStream_s00fe_ff80* pPos = pWriter->GetStream();
        EA::IO::WriteUint16Raw(pPos, &mName[i], 1, 0);
    }
    cVarListSerializer_s00fe_ff80 serializer(this, gCityVarList, 0x1a80d26);
    serializer.SerializeAlt(pStream);
}
}  // namespace SP

// @ 0x00ff05d0
namespace SP {
bool sWriteUint16(cOutStream* pStream, const uint16_t* pValue)
{
    cStreamWriter* pWriter = pStream->GetWriter();
    uint32_t nWord = *pValue;
    EA::IO::IStream_s00fe_ff80* pPos = pWriter->GetStream();
    EA::IO::WriteUint16(pPos, &nWord, 1, 0);
    return true;
}
}  // namespace SP

// @ 0x00ff0610
namespace SP {
cTribeData_s00fe_ff80::cTribeData_s00fe_ff80(cTribe_s00fe_ff80* pTribe)
{
    mPoliticalID = 0xffffffff;
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = 0;
    mFood = 0;
    if (pTribe != 0) {
        mPoliticalID = pTribe->GetPoliticalID();
        CopyPositionWords(&mPosition, pTribe->mSpatial.GetPosition());
        mPopulation = pTribe->GetAdultPopulation();
        mFood = pTribe->GetFood();
    }
}
}  // namespace SP

// @ 0x00ff06a0
namespace SP {
cTribeData_s00fe_ff80::cTribeData_s00fe_ff80(int32_t nPopulation, int32_t nFood)
{
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = nPopulation;
    mFood = nFood;
    if (NounManager() != 0)
        mPoliticalID = StarManager(0)->GetCurrentPoliticalID();
}
}  // namespace SP

// @ 0x00ff0700
namespace SP {
cTribeData_s00fe_ff80::cTribeData_s00fe_ff80()
{
    CopyPositionFloats(&mPosition, &gDefaultTribePosition);
    mPopulation = 0;
    mFood = 0;
    if (NounManager() != 0)
        mPoliticalID = StarManager(0)->GetCurrentPoliticalID();
}
}  // namespace SP

// @ 0x00ff0760
namespace SP {
int cCityData_s00fe_ff80::GetNumTurrets() const
{
    return CountBits(mTurretMask);
}
}  // namespace SP

// @ 0x00ff07a0
namespace SP {
cBuildingData_s00fe_ff80* cCityData_s00fe_ff80::GetBuilding(int nIndex)
{
    if (nIndex < (int32_t)(mpBuildingsEnd - mpBuildingsBegin))
        return &mpBuildingsBegin[nIndex];
    return 0;
}
}  // namespace SP

// @ 0x00ff07e0
namespace SP {
void cCityData_s00fe_ff80::RemoveTurret()
{
    int nBefore = CountBits(mTurretMask);
    mTurretMask &= mTurretMask - 1;
    int nAfter = CountBits(mTurretMask);
    if (nBefore - nAfter > 0)
        --mNumBuildings;
}
}  // namespace SP

// @ 0x00ff0870
namespace SP {
int cCityData_s00fe_ff80::GetNumBuildings() const
{
    return mNumBuildings - CountBits(mTurretMask);
}
}  // namespace SP

// @ 0x00ff0cd0
namespace SP {
cResourceKey* cCivData_s00fe_ff80::GetResourceKey(cResourceNoun* pNoun)
{
    uint32_t nIndex = 0;
    switch (pNoun->mResourceType) {
    case 0x018ea1eb:
        sGetIndexFromModelType(0x99e92f05, &nIndex);
        break;
    case 0x018ea2cc:
        sGetIndexFromModelType(0x47c10953, &nIndex);
        break;
    case 0x018eb106:
        nIndex = FindModelKeyIndex(0x4e3f7777);
        break;
    case 0x01a56aba:
        nIndex = FindModelKeyIndex(0x72c49181);
        break;
    }
    return mpModelKeys + nIndex;
}
}  // namespace SP

// @ 0x00ff0db0
namespace SP {
cSpatialSnapshot* cSpatialSnapshot::Init(cNoun* pNoun)
{
    if (pNoun != 0) {
        CopyPositionWords(&mPosition, pNoun->mSpatial.GetPosition());
        mField0c = pNoun->mFieldB1c;
        mField10 = pNoun->mFieldB20;
    }
    return this;
}
}  // namespace SP

// @ 0x00ff0df0
namespace SP {
cSpatialSnapshot& cSpatialSnapshot::Set(const cVector3* pPosition, int32_t nField0c, int32_t nField10)
{
    CopyPositionFloats(&mPosition, pPosition);
    mField0c = nField0c;
    mField10 = nField10;
    return *this;
}
}  // namespace SP

// @ 0x00ff0e20
namespace SP {
void cCivData_s00fe_ff80::Write(cOutStream* pStream)
{
    cVarListSerializer_s00fe_ff80 serializer(this, gCivVarList, 0x1a80d26);

    int32_t nCities = (int32_t)(mpCitiesEnd - mpCitiesBegin);
    WriteStreamCount(pStream, (uint32_t)nCities);
    for (int32_t i = 0; i < nCities; ++i)
        mpCitiesBegin[i]->Write(pStream);

    int32_t nVehicles = (int32_t)(mpVehiclesEnd - mpVehiclesBegin);
    WriteStreamCount(pStream, (uint32_t)nVehicles);
    for (int32_t i = 0; i < nVehicles; ++i) {
        cVarListSerializer_s00fe_ff80 vehicleSerializer(mpVehiclesBegin[i], gVehicleVarList, 0x1a80d26);
        vehicleSerializer.Serialize(pStream);
    }
    serializer.Serialize(pStream);
}
}  // namespace SP

// @ 0x00ff0f30
namespace SP {
bool WriteSTLSequenceT(cOutStream* pStream, const cBuildingList* pBuildings)
{
    WriteStreamCount(pStream, (uint32_t)(pBuildings->mpEnd - pBuildings->mpBegin));
    const cBuildingData_s00fe_ff80* pEnd = pBuildings->mpEnd;
    for (const cBuildingData_s00fe_ff80* pData = pBuildings->mpBegin; pData != pEnd; ++pData) {
        cVarListSerializer_s00fe_ff80 serializer((void*)pData, gBuildingVarList, 0x1a80d26);
        serializer.Serialize(pStream);
    }
    return pStream->End();
}
}  // namespace SP

// @ 0x00ff11c0
cOrnamentDataA& cOrnamentDataA::operator=(const cOrnamentDataA& o)
{
    mF00 = o.mF00;
    mF04 = o.mF04;
    mF08 = o.mF08;
    mF0c = o.mF0c;
    mF10 = o.mF10;
    mF14 = o.mF14;
    mF18 = o.mF18;
    mF1c = o.mF1c;
    mField20 = o.mField20;
    mFlag24 = o.mFlag24;
    mFlag25 = o.mFlag25;
    mField28 = o.mField28;
    mField2c = o.mField2c;
    mField30 = o.mField30;
    mField34 = o.mField34;
    return *this;
}

// @ 0x00ff1230
cOrnamentDataB& cOrnamentDataB::operator=(const cOrnamentDataB& o)
{
    mF00 = o.mF00;
    mF04 = o.mF04;
    mF08 = o.mF08;
    mF0c = o.mF0c;
    mF10 = o.mF10;
    mF14 = o.mF14;
    mF18 = o.mF18;
    mF1c = o.mF1c;
    mField20 = o.mField20;
    mField24 = o.mField24;
    mField28 = o.mField28;
    mField2c = o.mField2c;
    mField30 = o.mField30;
    return *this;
}

// @ 0x00ff14f0
void cTextHolder::SetText40(const cWString* src)
{
    if (src != &mText40)
        mText40.assign(src->mpBegin, src->mpEnd);
}

// @ 0x00ff1510
void cTextHolder::SetText50(const cWString* src)
{
    if (src != &mText50)
        mText50.assign(src->mpBegin, src->mpEnd);
}

// @ 0x00ff1fb0
void cCivData::EraseCity(int index)
{
    cCityData* city = mpCities3c[index];
    if (city != 0) {
        city->~cCityData();
        operator_delete_array(city);
    }
    mpCities3c[index] = mpCitiesEnd40[-1];
    --mpCitiesEnd40;
}

// @ 0x00ff1ff0
void cCivData::EraseValue(int value)
{
    int* first = mpValues28;
    int* last = mpValuesEnd2c;
    while (first != last && *first != value)
        ++first;
    if (first != last) {
        if (value != 0)
            operator_delete_array((void*)value);
        if (first + 1 < last)
            memcpy_fn(first, first + 1, (unsigned int)((char*)last - (char*)(first + 1)));
        mpValuesEnd2c = last - 1;
    }
}

// @ 0x00ff21d0
void __cdecl FUN_00ff21d0(SerHost* host, VecOrn* vec)
{
    vec->Erase(vec->mBegin, vec->mEnd);

    u32 count = 0;
    SerObj* s = host->Stream();
    void* stream = s->Channel();
    FUN_0093a780(stream, &count, 1, 0);
    vec->Resize(count);

    u32 i = 0;
    while (i < count) {
        cOrnamentData buf;
        buf.f00 = *(float*)&g_16dad08;
        buf.f04 = *(float*)&g_16dad0c;
        buf.f08 = *(float*)&g_16dad10;
        buf.f0c = *(float*)&g_15b4e38;
        buf.f10 = *(float*)&g_15b4e3c;
        buf.f14 = *(float*)&g_15b4e40;
        buf.f18 = *(float*)&g_15b4e44;
        buf.f1c = 0.0f;
        buf.u20 = 0;
        buf.u24 = 0;
        buf.u28 = 0;
        buf.u2c = 0;
        buf.u30 = 0;

        cVarListSerializer ser;
        ser.Ctor((void*)0x015b52b0, &buf, 0x1a80d26);
        ser.Serialize(host);

        cOrnamentData* pos = (cOrnamentData*)vec->mEnd;
        if ((char*)pos < (char*)vec->mCap) {
            vec->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                pos->f00 = buf.f00;
                pos->f04 = buf.f04;
                pos->f08 = buf.f08;
                pos->f0c = buf.f0c;
                pos->f10 = buf.f10;
                pos->f14 = buf.f14;
                pos->f18 = buf.f18;
                pos->f1c = buf.f1c;
                pos->u20 = buf.u20;
                pos->u24 = buf.u24;
                pos->u28 = buf.u28;
                pos->u2c = buf.u2c;
                pos->u30 = buf.u30;
            }
        } else {
            vec->InsertSlow(pos, &buf);
        }
        ++i;
    }

    host->Close();
}

// @ 0x00ff23b0
cCityData_s00ff_21d0* __fastcall FUN_00ff23b0(cCityData_s00ff_21d0* ecx_this, void* edx, cCity* city)
{
    ecx_this->mFlags = 0;
    ecx_this->mBeg = g_emptyString16_begin;
    ecx_this->mEnd = g_emptyString16_begin;
    ecx_this->mCap = g_emptyString16_end;
    ecx_this->m2Beg = g_emptyString16_begin;
    ecx_this->m2End = g_emptyString16_begin;
    ecx_this->m2Cap = g_emptyString16_end;
    ecx_this->mBuildings.mBegin = 0;
    ecx_this->mBuildings.mEnd = 0;
    ecx_this->mBuildings.mCap = 0;
    ecx_this->mOrnaments.mBegin = 0;
    ecx_this->mOrnaments.mEnd = 0;
    ecx_this->mOrnaments.mCap = 0;
    ecx_this->m4.mBegin = 0;
    ecx_this->m4.mEnd = 0;
    ecx_this->m4.mCap = 0;

    if (city == 0) {
        return ecx_this;
    }

    Spatial* sp = &city->mSpatial120;
    ecx_this->mPos = *sp->GetPosition();
    ecx_this->mOri = *sp->GetOrientation();

    ecx_this->u20 = city->Query8110();
    ecx_this->u24 = ((city->mVecEnd344 - city->mVecBeg340) >> 2)
                  + ((city->mVecEnd358 - city->mVecBeg354) >> 2);
    ecx_this->u2c = city->Query8b80();
    ecx_this->f30 = city->Query7d00();
    ecx_this->u34 = city->GetVehicleSpecialty();
    ecx_this->u38 = city->u74c;
    ecx_this->f3c = city->f748;
    ecx_this->f1c = 0.0f;

    cActionCircle* circle = (cActionCircle*)((char*)city + 0x3ec);
    for (u32 slot = 0; slot < 0xe; ++slot) {
        void* s = circle->SlotAt(slot);
        if (s == 0) {
            continue;
        }
        CityVehicle* ent = ((SlotObject*)s)->ToVehicle();
        if (ent == 0) {
            continue;
        }
        ent = (CityVehicle*)ent->AsInterface(0xe9cb8ba);
        if (ent == 0) {
            continue;
        }
        cBuildingData rec;
        EntitySpatial* es = &ent->mSpatial34;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = ent->f158;
        rec.u20 = ent->mFiles.Count();
        rec.b24 = ent->u289;
        rec.b25 = ent->SpecialByte();
        rec.u28 = ent->i28c;
        rec.u2c = ent->i290;
        rec.u30 = slot;
        rec.u34 = ent->GetId();

        VectorEC* v = &ecx_this->mBuildings;
        cBuildingData* pos = (cBuildingData*)v->mEnd;
        if (pos < (cBuildingData*)v->mCap) {
            v->mEnd = (char*)pos + 0x38;
            if (pos != 0) {
                pos->Assign(&rec);
            }
        } else {
            v->InsertBld(pos, &rec);
        }
    }

    VecHolder* src = city->OrnamentVec();
    u32 n = (u32)(((int*)src->mEnd - (int*)src->mBegin) >> 2);
    for (u32 i = 0; i < n; ++i) {
        CityVehicle* ent = (CityVehicle*)src->mBegin[i];
        EntitySpatial* es = &ent->mSpatial70;
        cOrnamentData2 rec;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = 0.0f;
        rec.u20 = 0;
        rec.u24 = ent->u22c;
        rec.u28 = 0;
        rec.u2c = 0;
        rec.u30 = ent->GetId();

        VectorEC* v = &ecx_this->mOrnaments;
        cOrnamentData2* pos = (cOrnamentData2*)v->mEnd;
        if (pos < (cOrnamentData2*)v->mCap) {
            v->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertOrn(pos, &rec);
        }
    }

    TileEntity* tiles = city->TileEntity();
    ecx_this->uB8 = tiles->GetPackedId();

    u16* dst = ecx_this->mSummary;
    for (u32 i = 0; i < 0xc4; i += 0xe) {
        *dst = 0;
        u16 bit = 1;
        for (u32 j = 0; j < 0xe; ++j) {
            u8 b = *((u8*)tiles + i + j + 0x274);
            if (b != 0) {
                *dst |= bit;
            }
            bit = (u16)(bit << 1);
        }
        ++dst;
    }

    cActionCircle* flagsCircle = (cActionCircle*)city->ActionCircle();
    int cnt = (flagsCircle->mCap54 - flagsCircle->mBeg50) / 0x18;
    for (int i = 0; i < cnt; ++i) {
        u8* pc = (u8*)flagsCircle->SlotAt((u32)i);
        if (*pc != 0) {
            ecx_this->mFlags |= (u8)(1 << i);
        }
    }

    return ecx_this;
}

// @ 0x00ff2810
void __fastcall FUN_00ff2810(cCityData_s00ff_21d0* ecx_this, void* edx, cCity* city, int arg)
{
    if (city == 0) {
        return;
    }

    ecx_this->uBC = city->u2e8;
    ecx_this->uC0 = city->u2ec;

    Spatial* sp = &city->mSpatial120;
    ecx_this->mPos = *sp->GetPosition();
    ecx_this->mOri = *sp->GetOrientation();

    ecx_this->u20 = city->Query8110();
    ecx_this->u24 = ((city->mVecEnd344 - city->mVecBeg340) >> 2)
                  + ((city->mVecEnd358 - city->mVecBeg354) >> 2);
    ecx_this->u2c = city->Query8b80();
    FUN_00ff08b0(ecx_this, city->Query7d00(), arg);
    ecx_this->u38 = city->u74c;
    ecx_this->f3c = city->f748;

    ecx_this->mBuildings.EraseBld();

    cActionCircle* circle = (cActionCircle*)((char*)city + 0x3ec);
    for (u32 slot = 0; slot < 0xe; ++slot) {
        void* s = circle->SlotAt(slot);
        if (s == 0) {
            continue;
        }
        CityVehicle* ent = ((SlotObject*)s)->ToVehicle();
        if (ent == 0) {
            continue;
        }
        ent = (CityVehicle*)ent->AsInterface(0xe9cb8ba);
        if (ent == 0) {
            continue;
        }
        cBuildingData rec;
        EntitySpatial* es = &ent->mSpatial34;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = ent->f158;
        rec.u20 = ent->mFiles.Count();
        rec.b24 = ent->u289;
        rec.b25 = ent->SpecialByte();
        rec.u28 = ent->i28c;
        rec.u2c = ent->i290;
        rec.u30 = slot;
        rec.u34 = ent->GetId();

        VectorEC* v = &ecx_this->mBuildings;
        cBuildingData* pos = (cBuildingData*)v->mEnd;
        if (pos < (cBuildingData*)v->mCap) {
            v->mEnd = (char*)pos + 0x38;
            if (pos != 0) {
                pos->Assign(&rec);
            }
        } else {
            v->InsertBld(pos, &rec);
        }
    }

    ecx_this->mOrnaments.EraseOrn();

    VecHolder* src = city->OrnamentVec();
    u32 n = (u32)(((int*)src->mEnd - (int*)src->mBegin) >> 2);
    for (u32 k = 0; k < n; ++k) {
        CityVehicle* ent = (CityVehicle*)src->mBegin[k];
        cOrnamentData2 rec;
        EntitySpatial* es = &ent->mSpatial70;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = 0.0f;
        rec.u20 = 0;
        rec.u24 = ent->u22c;
        rec.u28 = 0;
        rec.u2c = 0;
        rec.u30 = ent->GetId();

        VectorEC* v = &ecx_this->mOrnaments;
        cOrnamentData2* pos = (cOrnamentData2*)v->mEnd;
        if (pos < (cOrnamentData2*)v->mCap) {
            v->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertOrn(pos, &rec);
        }
    }

    TileEntity* nb = city->TileEntity();
    ecx_this->uB8 = nb->GetPackedId();

    u16* dst = ecx_this->mSummary;
    for (u32 off = 0; off < 0xc4; off += 0xe) {
        *dst = 0;
        u32 bit = 1;
        for (u32 b = 0; b < 0xe; ++b) {
            u8 flag = nb->mFlags274[off + b];
            *dst |= (u16)((flag != 0) ? bit : 0);
            bit = (bit << 1) | (bit >> 31);
        }
        ++dst;
    }

    cActionCircle* flagsCircle = (cActionCircle*)city->ActionCircle();
    ecx_this->mFlags = 0;
    int cnt = (flagsCircle->mCap54 - flagsCircle->mBeg50) / 0x18;
    for (int i = 0; i < cnt; ++i) {
        u8* s = (u8*)flagsCircle->SlotAt((u32)i);
        if (*s != 0) {
            ecx_this->mFlags |= (u8)(1 << i);
        }
    }
}

// @ 0x00ff2c70
void cCitySummary::AddRecord(cCityData_s00ff_21d0* rec)
{
    if (rec == 0) {
        return;
    }

    u32 pc1 = PopCount8((u32)rec->mFlags);
    mPackCnt20 += (int)pc1;

    u32 pc2 = PopCount8((u32)rec->mFlags);
    mPackSum24 += (int)(rec->u24 - pc2);

    VectorEC* v = &mBuildingList;
    cCityData_s00ff_21d0** pos = (cCityData_s00ff_21d0**)v->mEnd;
    if (pos < (cCityData_s00ff_21d0**)v->mCap) {
        v->mEnd = (char*)pos + 4;
        if (pos != 0) {
            *pos = rec;
            return;
        }
    } else {
        v->InsertSlow(pos, &rec);
    }
}

// @ 0x00ff2d50
void __fastcall FUN_00ff2d50(cCitySummary* ecx_this, void* edx, int index, cCitySummary* target)
{
    int idx = index;
    cCityData_s00ff_21d0** vec = (cCityData_s00ff_21d0**)ecx_this->mBuildingList.mBegin;
    target->AddRecord(vec[idx]);
    cCityData_s00ff_21d0** v2 = (cCityData_s00ff_21d0**)ecx_this->mBuildingList.mBegin;
    cCityData_s00ff_21d0** end = (cCityData_s00ff_21d0**)ecx_this->mBuildingList.mEnd;
    v2[idx] = end[-1];
    ecx_this->mBuildingList.mEnd = (char*)ecx_this->mBuildingList.mEnd - 4;
}

// @ 0x00ff2d80
void cCitySummary::ResetForward()
{
    int n = (int)(((char*)mBuildingList.mEnd - (char*)mBuildingList.mBegin) >> 2);
    for (int i = 0; i < n; ++i) {
        cCityData_s00ff_21d0* pc = ((cCityData_s00ff_21d0**)mBuildingList.mBegin)[i];
        if (pc != 0) {
            pc->Destroy();
            FUN_00f47380(pc);
        }
    }
    int m = (int)(((char*)mCityData.mEnd - (char*)mCityData.mBegin) >> 2);
    for (int i = 0; i < m; ++i) {
        cCityData_s00ff_21d0* pc = ((cCityData_s00ff_21d0**)mCityData.mBegin)[i];
        if (pc != 0) {
            FUN_00f47380(pc);
        }
    }
    // vector::erase(begin(), end()) on mBuildingList
    cCityData_s00ff_21d0** bEnd = (cCityData_s00ff_21d0**)mBuildingList.mEnd;
    cCityData_s00ff_21d0** bBeg = (cCityData_s00ff_21d0**)mBuildingList.mBegin;
    cCityData_s00ff_21d0** bLast = (cCityData_s00ff_21d0**)mBuildingList.mEnd;
    memcpy(bBeg, bLast, (unsigned)((char*)bEnd - (char*)bLast));
    *(char* volatile*)&mBuildingList.mEnd = (char*)mBuildingList.mEnd - (((int)((char*)bEnd - (char*)bBeg) >> 2) * 4);
    // vector::erase(begin(), end()) on mCityData
    cCityData_s00ff_21d0** cEnd = (cCityData_s00ff_21d0**)mCityData.mEnd;
    cCityData_s00ff_21d0** cLast = (cCityData_s00ff_21d0**)mCityData.mEnd;
    cCityData_s00ff_21d0** cBeg = *(cCityData_s00ff_21d0** volatile*)&mCityData.mBegin;
    memcpy(cBeg, cLast, (unsigned)((char*)cEnd - (char*)cLast));
    mCityData.mEnd = (char*)mCityData.mEnd - (((int)((char*)cEnd - (char*)cBeg) >> 2) * 4);
}

// @ 0x01397130
namespace Simulator {
void InitE231()
{
    ADD2(0, "mPosition",     0x34da7b6, 0x00, IRead<C0>, IWrite<C0>, IReadText<C0>, IWriteText<C0>, IValid<C0>, IToXml<C0>)
    ADD2(1, "mOrientation",  0x34da7b7, 0x0c, IRead<C1>, IWrite<C1>, IReadText<C1>, IWriteText<C1>, IValid<C1>, IToXml<C1>)
    ADD2(2, "mClassId",      0x34da7b8, 0x34, INT_ROW(C2))
    ADD2(3, "mHealthPoints", 0x3def5f4, 0x1c, IRead<C3>, IWrite<C3>, IReadText<C3>, IWriteText<C3>, IValid<C3>, IToXml<C3>)
    ADD2(4, "mDamageState",  0x3df010e, 0x20, INT_ROW(C4))
    ADD2(5, "mConnected",    0x4bee126, 0x24, IRead<C5>, IWrite<C5>, IReadText<C5>, IWriteText<C5>, IValid<C5>, IToXml<C5>)
    ADD2(6, "mIrradiated",   0x5e4ee09, 0x25, IRead<C6>, IWrite<C6>, IReadText<C6>, IWriteText<C6>, IValid<C6>, IToXml<C6>)
    ADD2(7, "mEffectiveness",0x4bee127, 0x28, INT_ROW(C7))
    ADD2(8, "mFreezeCount",  0x4bee12a, 0x2c, INT_ROW(C8))
    ADD2(9, "mSlot",         0x5761ca2, 0x30, INT_ROW(C9))
}
}  // namespace Simulator

// @ 0x01397520
namespace Simulator {
void InitE235()
{
    ADD(0, "mPosition",     0x4acb9a9, 0x00, R0, W0, RT0, WT0, V0, X0)
    ADD(1, "mOrientation",  0x4acb9b7, 0x0c, R1, W1, RT1, WT1, V1, X1)
    ADD(2, "mModelKey",     0x4acb9ba, 0x24, R2, W2, RT2, WT2, V2, X2)
    ADD(3, "mClassId",      0x4acb9bc, 0x30, R3, W3, RT3, WT3, V3, X3)
    ADD(4, "mHealthPoints", 0x4acb9bf, 0x1c, R4, W4, RT4, WT4, V4, X4)
    ADD(5, "mDamageState",  0x4acb9c1, 0x20, R5, W5, RT5, WT5, V5, X5)
}
}  // namespace Simulator
