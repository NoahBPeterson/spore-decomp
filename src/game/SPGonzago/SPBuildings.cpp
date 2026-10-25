// src/game/SPGonzago/SPBuildings.cpp -- migrated from slice(s) s0132abc0, s00bce1e0, s00bcc010 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBuildings.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cCombatant.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cSPTimer.h"
#include "SP/cSpatialObject.h"
#include "SP/cTribeTool.h"
#include "SP/cVarListSerializer.h"
#include "SP/cVehicle.h"
#include "SP/cBuilding.h"
#include "SP/cCommunity.h"

// ---- items of slice s00bcc010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VF(obj, slot) (*(void**)((char*)*(void**)(obj) + (slot) * 4))
void  __cdecl FUN_0093aa70(void* w, void* p, int n, int b);    // 0x0093aa70 EA::IO::WriteUint32
void* __cdecl FUN_00b5b800();                                  // 0x00b5b800 SP::GetCurrentGameMode
struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    void __thiscall Construct(void* obj, int idA, int idB);    // 0x00692f90 ret 0xc
    char __thiscall Serialize(void* s);                        // 0x00692900 ret 4
    char __thiscall Deserialize(void* s);                      // 0x00693e10 ret 4
    int  __thiscall GetFields(void* s);                        // 0x00695960 ret 4
};
class cGameData {
 public:
    void __thiscall Write(void* s);                            // 0x00b18590 ret 4
    void __thiscall Read(void* s);                             // 0x00b18600 ret 4
    void __thiscall WriteAsText(void* s);                      // 0x00b18420 ret 4
    void __thiscall IsDestroyed(int a);                        // 0x00bfd0d0 ret 4
    void* __thiscall GetProperty(int iid);                     // 0x00b18460 ret 4
};
class cSpatialObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c88a90 ret 4
    char __thiscall Read(void* s);                             // 0x00c88b00 ret 4
    void __thiscall SetLocalExtents(int a, float f);           // 0x00c89160 ret 8
    char __thiscall bcc570();                                  // 0x00bcc570
    void __thiscall bcc5e0(int a, float f);                    // 0x00bcc5e0
    char __thiscall bccdc0();                                  // 0x00bccdc0
    void __thiscall bcc6e0(char v);                            // 0x00bcc6e0
    float __thiscall bcc640();                                 // 0x00bcc640
};
class cLocomotiveObject {
 public:
    char __thiscall Write(void* s);                            // 0x00c448a0 ret 4
};
class cCombatant {
 public:
    char __thiscall Write(void* s);                            // 0x00bfc4a0 ret 4
    char __thiscall Read(void* s);                             // 0x00bfc540 ret 4
    char __thiscall IsSomething();                             // 0x00bfc600 ret
    void __thiscall Do(void* p);                               // 0x00bd7f20 ret 4
};
class PropHost {
 public:
    void* __thiscall Get108(int iid);                          // 0x00ac0320 ret 4
    void* __thiscall Get51C(int iid);                          // 0x00abf740 ret 4
    void* __thiscall GetBase(int iid);                         // 0x00b18460 ret 4
    void* __thiscall Get120(int iid);                          // 0x00bfc380 ret 4
    void* __thiscall Get34a(int iid);                          // 0x00c884f0 ret 4
    void* __thiscall Get1E8(int iid);                          // 0x00c751c0 ret 4
    void* __thiscall Get34b(int iid);                          // 0x00c41d00 ret 4
};
class cSerializableNoun {
 public:
    char __thiscall WriteBase(void* s);                        // 0x00bcc350
    char __thiscall ReadBase(void* s);                         // 0x00bcc400
};
class cVehicle : public cSerializableNoun {
 public:
    void __thiscall Write1(void* s);                           // 0x00bcc8b0
    void __thiscall Read1(void* s);                            // 0x00bcc920
    void __thiscall Write2(void* s);                           // 0x00bcc9f0
    void __thiscall Read2(void* s);                            // 0x00bcca60
    void __thiscall Write3(void* s);                           // 0x00bccb30
    void __thiscall Read3(void* s);                            // 0x00bccba0
    bool __thiscall Write4(void* s);                           // 0x00bccc70
    bool __thiscall Read4(void* s);                            // 0x00bccd10
    void* __thiscall GetProp(int iid);                         // 0x00bcce20
    void __thiscall bccf20();
    bool __thiscall Write5(void* s);                           // 0x00bccf80
    void __thiscall WriteAsText(void* s);                      // 0x00bcd030
    void __thiscall bcd130(int delta);                         // 0x00bcd130
    int  __thiscall bcd250();
};
// ---- items of slice s00bcc010 end

// ---- items of slice s00bce1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_f15d9c6c;   // 0x015d9c6c
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;
#define VS(o, off)   (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)  ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1) \
    ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vec3u   { u32 x, y, z; };
struct cGameNounManager {
    void* mVtbl;                  // +0
    void RemoveNoun(void* noun);  // 0x00b225d0
    void* CreateNoun(u32 id);     // 0x00b20c60
};
cGameNounManager* SP_NounManager();                          // 0x00b3d300
void* PropertyManager();                                    // 0x0067de30
bool  GetPropertyAsVector3(void* list, u32 id, void* out);  // 0x006a1110
struct Sub34 {                       // +0x34
    void* mVtbl;                     // +0x00
    u8    d[0x64];
    void FUN_00c8b2e0();             // 0x00c8b2e0
    bool Read(void* stream);         // 0x00c88b00
    bool ReadBig(void* stream);      // 0x00c43c10
    void FUN_00c43f90(void);         // 0x00c43f90  (Shutdown)
    void FUN_00c421b0(void* p);      // 0x00c421b0
};
struct SubC4  { u8 d[0x3c]; };                              // +0xc4
struct Sub108 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x108
struct Sub120 {                                             // +0x120
    u8 d[0xcc];
    void FUN_00bfc720();                                     // 0x00bfc720
    void FUN_00bfc470(u8 b);                                 // 0x00bfc470
};
struct Sub504 { u8 d[0x18]; void FUN_00ac0450(); };         // +0x504
struct Sub51C { u8 d[0x6c]; void FUN_00abf710(); };         // +0x51c
struct Sub588 {                                             // +0x588
    u8   d[0xf8];
    bool FUN_00bfc540(void* stream);                         // 0x00bfc540
    void FUN_00bfc720();                                     // 0x00bfc720
};
struct cToolData {
    bool FUN_0104bd50();         // 0x0104bd50
    void UseToolStop();          // 0x0104fa90
};
cToolData* __stdcall FUN_00b3d390(cToolData* p);   // 0x00b3d390
struct cCity;
struct Sub508 {
    void* mVtbl;          // +0x000
    u8    d[0x614];       // +0x004 .. +0x618
    int   FUN_00vt10();   // vtable slot 0x10
};
struct RType660 {
    void*  mVtbl;         // +0x000
    u8     m04[0x504];    // +0x004 .. +0x508
    Sub508 m508;          // +0x508 .. +0xb20
    u32    mB20;          // +0xb20
};
struct cVt8Obj {
    void*    mVtbl;       // +0
    Vector3* FUN_00vt2c();    // vtable slot 0x2c
};
struct cCiv {
    void* mVtbl;
    void FUN_00bf02b0();      // 0x00bf02b0
};
struct cCity {
    void* mVtbl;
    cCiv* GetCivilization(int uVar5, Vector3 v);   // 0x00bd9bf0
    void  FUN_00c00b00(int a, int b);              // 0x00c00b00
};
struct cBuilding {
    u8             m00[0x2c];
    void*          mpRef2c;      // +0x2c
    u8             m30[0x04];
    Sub34          m34;          // +0x34 .. +0x9c
    u8             m9c[0x28];    // +0x9c .. +0xc4
    SubC4          mC4;          // +0xc4 .. +0x100
    cCity*         mp100;        // +0x100  (cCity)
    u8             m104[0x04];
    Sub108         m108;         // +0x108 .. +0x120
    Sub120         m120;         // +0x120 .. +0x1ec
    void*          mp1ec;        // +0x1ec  (space inventory)
    void*          mp1f0;        // +0x1f0  (owner city)
    u8             m1f4[0x30];   // +0x1f4 .. +0x224
    u32            m224;         // +0x224
    u8             m228[0xe4];   // +0x228 .. +0x30c
    u8             m30c;         // +0x30c
    u8             m30d[0x1f7];  // +0x30d .. +0x504
    Sub504         m504;         // +0x504 .. +0x51c
    Sub51C         m51C;         // +0x51c .. +0x588
    Sub588         m588;         // +0x588 .. +0x680
    void*          mp680;        // +0x680
    u8             m684[0x04];
    void*          mp688;        // +0x688
    void*          mp68c;        // +0x68c
    cToolData*     mp690;        // +0x690
    cToolData*     mp694;        // +0x694
    cToolData*     mp698;        // +0x698
    cToolData*     mp69c;        // +0x69c
    void*          mp6a0;        // +0x6a0
    void*          mp6a4;        // +0x6a4

    float GetCost();                       // 0x00bce9a0
    int   FUN_00bce5d0();                  // 0x00bce5d0
    void  FUN_00bce970();                  // 0x00bce970
    void  FUN_00bce9b0();                  // 0x00bce9b0
    void  SetOwnerCity1(void* param_2);    // 0x00bce8e0
    void  FUN_00bcea10(u32 param_2);       // 0x00bcea10
    void  FUN_00bce660(void* param_2);     // 0x00bce660
    void  FUN_00bce1e0();                  // 0x00bce1e0
    void  SetGameDataOwner2(void* p);      // 0x00b18550
    void  FUN_00bcd4e0(u32 param_2);       // 0x00bcd4e0
};
struct cSpatialObject_s00bc_e1e0 {
    void* mVtbl;        // +0x00
    u8    m04[0x98];    // +0x04 .. +0x9c
    void* mp9c;         // +0x9c
    u8    mA0[0x580];   // +0xa0 .. +0x620
    Vec3u m620;         // +0x620
    bool LoadModel(u32 id);        // 0x00c8a550
    bool FUN_00bce5f0(u32 param_2);
};
struct RType { u8 m00; u8 m01; };
struct F3F950Target {
    RType* FUN_00f3f950(void* arg);   // 0x00f3f950
};
struct GlobalsTable {
    u8              m00[0x74];
    F3F950Target*   mp74;             // +0x74
};
extern GlobalsTable* g_globals16c7aa4;   // 0x016c7aa4
struct cCommunity {
    u8    m00[0x66c];
    void* mp66c;                     // +0x66c
    void  func54h(void* param_2);    // 0x00c88670
    void  FUN_00bce8b0(u32 param_2);
};
struct cVariant {
    void* mPtr;         // +0x000
    u8    m04[0x0c];    // +0x004 .. +0x010
    u8    mFlags;       // +0x010
    u8    m11;          // +0x011
    u16   mType;        // +0x012
};
// ---- items of slice s00bce1e0 end

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
template<typename T> bool Valid();                                    // 0x00b1fbf0
template<typename T> bool Read4(void*, void*);                        // 0x00572810
template<typename T> bool Write4(void*, void*);                       // 0x00572840
template<typename T> void ReadTextT(const string8_s0132_abc0&, void*);           // 0x00692ff0
template<typename T> void WriteTextT(char*, void*);                   // 0x00694ee0
template<typename T> bool ToXmlT(void*, const char*, int);            // 0x0057cde0
bool Valid_00b1fbf0();                                                // 0x00b1fbf0
bool ToXml_0057cde0(void*, const char*, int);                         // 0x0057cde0
struct TBld0{}; struct TBld1{}; struct TBld2{}; struct TBld3{}; struct TBld4{}; struct TBld5{};
struct TBld6{}; struct TBld7{}; struct TBld8{}; struct TBld9{}; struct TBld10{}; struct TBld11{}; struct TBld12{};
void ReadText_00c2e4e0(const string8_s0132_abc0&, void*);                        // 0x00c2e4e0
void WriteText_00692fb0(char*, void*);                                // 0x00692fb0
bool ToXml_00ac8050(void*, const char*, int);                         // 0x00ac8050
struct AttrSlot { uint32_t d[15]; };
#define ADD_ATTR(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
extern AttrSlot sBuildingsAttributes[13];
struct TW0{}; struct TW1{}; struct TW2{}; struct TW3{}; struct TW4{};
struct TW5{}; struct TW6{}; struct TW7{}; struct TW8{}; struct TW9{};
extern AttrSlot sBuildingWeaponsAttributes[10];
// ---- items of slice s0132abc0 end

// @ 0x00bcc570
char __thiscall cSpatialObject::bcc570()
{
    if (FUN_00b5b800() == (void*)0x1654c10) return 1;
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcc5e0
void __thiscall cSpatialObject::bcc5e0(int a, float f)
{
    ((cSpatialObject*)this)->SetLocalExtents(a, f);
    char* obj = (char*)this - 0x34;
    void* x = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (x != 0) {
        void* y = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (y != 0 && ((int(__thiscall*)(void*))VF(y, 8))(y) == 0x18c43e8)
            ((cCombatant*)y)->Do(obj);
    }
}

// @ 0x00bcc640
float __thiscall cSpatialObject::bcc640()
{
    float c = ((float(__thiscall*)(void*))VF(this, 0x5c / 4))(this);
    return c * *(float*)0x1485544;
}

// @ 0x00bccdc0
char __thiscall cSpatialObject::bccdc0()
{
    char* obj = (char*)this - 0x34;
    void* a = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
    if (a != 0) {
        void* b = ((void*(__thiscall*)(void*))VF(obj, 12))(obj);
        if (b != 0) {
            if (((int(__thiscall*)(void*))VF(b, 8))(b) == 0x18c43e8)
                if (!((char(__thiscall*)(void*))VF(b, 11))(b))
                    return ((char(__thiscall*)(void*))VF((char*)b + 0x120, 0x16))((char*)b + 0x120);
        }
    }
    return 0;
}

// @ 0x00bcce20
void* __thiscall cVehicle::GetProp(int iid)
{
    if (iid == 0x436f315) return this;
    void* r = ((PropHost*)((char*)this + 0x504))->Get108(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x51c))->Get51C(iid);
    if (r == 0) r = ((PropHost*)this)->GetBase(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x588))->Get120(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x34))->Get34b(iid);
    if (r == 0) r = ((PropHost*)((char*)this + 0x650))->Get1E8(iid);
    return r;
}

// @ 0x00bccf80
bool __thiscall cVehicle::Write5(void* s)
{
    void* x = ((void*(__thiscall*)(void*))VF(s, 8))(s);
    int   ver = 0x436f315;
    void* w = ((void*(__thiscall*)(void*))VF(x, 6))(x);
    FUN_0093aa70(w, &ver, 1, 0);
    ((cGameData*)this)->Write(s);
    bool ok = ((cLocomotiveObject*)((char*)this + 0x34))->Write(s) != 0 &&
              ((cCombatant*)((char*)this + 0x588))->Write(s) != 0;
    cVarListSerializer vl;
    vl.Construct(this, 0x156dc20, 0x1a80d26);
    if (ok && vl.Serialize(s) != 0)
        return true;
    return false;
}

// @ 0x00bcd030
void __thiscall cVehicle::WriteAsText(void* s)
{
    ((cGameData*)this)->WriteAsText(s);
    cVarListSerializer v1;
    cVarListSerializer v2;
    v1.Construct((char*)this + 0x34, 0x157a1f8, 0x1a80d26);
    v1.GetFields(s);
    v1.Construct((char*)this + 0x120, 0x1570858, 0x1a80d26);
    v1.GetFields(s);
    v2.Construct(this, 0x156d770, 0x1a80d26);
    v2.GetFields(s);
}

// @ 0x00bce1e0
void cBuilding::FUN_00bce1e0()
{
    if (mp690 != 0 && mp690->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp690);
        r->UseToolStop();
    }
    if (mp694 != 0 && mp694->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp694);
        r->UseToolStop();
    }
    if (mp698 != 0 && mp698->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp698);
        r->UseToolStop();
    }
    if (mp69c != 0 && mp69c->FUN_0104bd50()) {
        cToolData* r = FUN_00b3d390(mp69c);
        r->UseToolStop();
    }

    {
        void* p = mp68c;
        if (p != 0) {
            mp68c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp690;
        if (p != 0) {
            mp690 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp694;
        if (p != 0) {
            mp694 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp698;
        if (p != 0) {
            mp698 = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp69c;
        if (p != 0) {
            mp69c = 0;
            VC0(void, p, 8);
        }
    }
    {
        void* p = mp6a4;
        if (p != 0) {
            mp6a4 = 0;
            VC0(void, p, 0x64);
        }
    }

    if (mp680 != 0) {
        if (VC0(bool, mp680, 0x10))
            VC1(void, mp680, 0xc, void*, 0);
    }
    {
        void* p = mp680;
        if (p != 0) {
            mp680 = 0;
            VC0(void, p, 4);
        }
    }

    if (mp6a0 != 0) {
        SP_NounManager()->RemoveNoun(mp6a0);
        void* p = mp6a0;
        mp6a0 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }
    {
        void* p = mp688;
        mp688 = 0;
        if (p != 0)
            VC0(void, p, 4);
    }

    m588.FUN_00bfc720();
    m504.FUN_00ac0450();
    m51C.FUN_00abf710();

    {
        void* p = mpRef2c;
        if (p != 0) {
            mpRef2c = 0;
            VC0(void, p, 4);
        }
    }

    m34.FUN_00c43f90();
}

// @ 0x00bce5d0
int cBuilding::FUN_00bce5d0()
{
    void* p = mp100;
    if (p == 0)
        return -1;
    return VC0(int, p, 0x4c);
}

// @ 0x00bce5f0
bool cSpatialObject_s00bc_e1e0::FUN_00bce5f0(u32 param_2)
{
    if (LoadModel(param_2)) {
        void* p = mp9c;
        void* q = *(void**)((char*)p + 0x90);
        if (q != 0) {
            Vec3u v;
            if (GetPropertyAsVector3(q, 0x475062du, &v))
                m620 = v;
        }
        return true;
    }
    return false;
}

// @ 0x00bce660
void cBuilding::FUN_00bce660(void* param_2)
{
    bool bVar1 = false;
    int uVar5 = -1;

    if (param_2 == 0)
        return;

    RType660* r = VC1(RType660*, param_2, 0x5c, u32, 0x137e8e0u);
    if (r != 0 && r->mB20 == 0) {
        bVar1 = true;
        uVar5 = VC0(int, &r->m508, 0x10);
    }

    void* p = VC1(void*, param_2, 0x5c, u32, 0xb033b403u);
    if (p != 0) {
        bVar1 = true;
        uVar5 = VC0(int, p, 0x4c);
    }

    void* q = VC1(void*, param_2, 0x5c, u32, 0xd0036e08u);
    if (q != 0) {
        uVar5 = VC0(int, q, 0x4c);
    } else if (!bVar1) {
        return;
    }

    cVt8Obj* r2 = VC0(cVt8Obj*, param_2, 8);
    Vector3* pv = VC0(Vector3*, r2, 0x2c);

    cCiv* civ = mp100->GetCivilization(uVar5, *pv);
    civ->FUN_00bf02b0();
    mp100->FUN_00c00b00(0, uVar5);
}

// @ 0x00bce8b0
void cCommunity::FUN_00bce8b0(u32 param_2)
{
    func54h((void*)param_2);
    void* p = mp66c;
    if (p != 0)
        VC1(void, (char*)p + 0x70, 0x38, u32, param_2);
}

// @ 0x00bce8e0
void cBuilding::SetOwnerCity1(void* param_2)
{
    SetGameDataOwner2(param_2);

    void* oldCity = mp1f0;
    if (param_2 != oldCity) {
        if (param_2 != 0)
            VC0(void, param_2, 0);
        mp1f0 = param_2;
        if (oldCity != 0)
            VC0(void, oldCity, 4);
    }

    void* noun = SP_NounManager()->CreateNoun(0x21ffa3fu);

    void* inv;
    if (noun != 0)
        inv = VC1(void*, noun, 0xc, u32, 0xb075dec5u);
    else
        inv = 0;

    void* oldInv = mp1ec;
    if (inv != oldInv) {
        if (inv != 0)
            VC0(void, inv, 0);
        mp1ec = inv;
        if (oldInv != 0)
            VC0(void, oldInv, 4);
    }
}

// @ 0x00bce970
void cBuilding::FUN_00bce970()
{
    RType* r = g_globals16c7aa4->mp74->FUN_00f3f950(this);
    if (r != 0)
        m120.FUN_00bfc470(r->m01);
}

// @ 0x00bce9a0
float cBuilding::GetCost()
{
    VC0(void, this, 0x4c);
    return 0.0f;
}

// @ 0x00bce9b0
void cBuilding::FUN_00bce9b0()
{
    m120.FUN_00bfc720();
    m108.FUN_00ac0450();
    m34.FUN_00c8b2e0();

    void* p = mp1f0;
    if (p != 0) {
        mp1f0 = 0;
        VC0(void, p, 4);
    }
    if (mp1ec != 0)
        SP_NounManager()->RemoveNoun(mp1ec);
}

// @ 0x00bcea10
void cBuilding::FUN_00bcea10(u32 param_2)
{
    FUN_00bcd4e0(param_2);
    m30c = 1;
}

// @ 0x00bcea30
float FUN_00bcea30(u32 a, u32 b, u32 c, float def)
{
    void* local = 0;
    void* pm = PropertyManager();
    if (local != 0) {
        void* old = local;
        local = 0;
        VC0(void, old, 4);
    }
    if (VC3(bool, pm, 0x2c, u32, a, u32, b, void**, &local)) {
        cVariant* out;
        if (VC2(bool, local, 0x24, u32, c, cVariant**, &out)) {
            u16 t = out->mType;
            float* pf;
            if (t == 0xd || t == 0x10) {
                if ((out->mFlags & 0x30) != 0)
                    pf = (float*)out->mPtr;
                else
                    pf = (t != 0) ? (float*)out : 0;
            } else {
                pf = &g_f15d9c6c;
            }
            float f = *pf;
            if (local != 0)
                VC0(void, local, 4);
            return f;
        }
    }
    if (local != 0)
        VC0(void, local, 4);
    return def;
}

// @ 0x0132abc0
void FUN_0132abc0()
{
    ADD_ATTR(sBuildingsAttributes, 0, "mIsOn", 0x02416eb8, 0x1f4, Read4<TBld0>, Write4<TBld0>, ReadTextT<TBld0>, WriteTextT<TBld0>, Valid<TBld0>, ToXmlT<TBld0>)              // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 1, "mpOwnerCity", 0x02416ebb, 0x1f0, Read4<TBld1>, Write4<TBld1>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld1>, ToXmlT<TBld1>)       // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingsAttributes, 2, "mEvents", 0x041614aa, 0x1f8, Read4<TBld2>, Write4<TBld2>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld2>, ToXmlT<TBld2>)           // 0xbd16d0 0xbd0bb0 0xc2e4e0 0x692fb0 0xbd0c80 0xbd2840
    ADD_ATTR(sBuildingsAttributes, 3, "mAttackTimer", 0x04ac7af1, 0x238, Read4<TBld3>, Write4<TBld3>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld3>, ToXmlT<TBld3>)       // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 4, "mDestroyTimer", 0x05b9555b, 0x258, Read4<TBld4>, Write4<TBld4>, ReadText_00c2e4e0, WriteText_00692fb0, Valid<TBld4>, ToXmlT<TBld4>)      // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingsAttributes, 5, "mConnected", 0x04b74e33, 0x289, Read4<TBld5>, Write4<TBld5>, ReadTextT<TBld5>, WriteTextT<TBld5>, Valid<TBld5>, ToXmlT<TBld5>)           // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
    ADD_ATTR(sBuildingsAttributes, 6, "mEffectiveness", 0x04b74e34, 0x28c, Read4<TBld6>, Write4<TBld6>, ReadTextT<TBld6>, WriteTextT<TBld6>, Valid_00b1fbf0, ToXml_0057cde0)     // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 7, "mFreezeCount", 0x04b74e37, 0x290, Read4<TBld7>, Write4<TBld7>, ReadTextT<TBld7>, WriteTextT<TBld7>, Valid_00b1fbf0, ToXml_0057cde0)       // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 8, "mMoneyCount", 0x04efa697, 0x294, Read4<TBld8>, Write4<TBld8>, ReadTextT<TBld8>, WriteTextT<TBld8>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 9, "mHappyCount", 0x04efa698, 0x298, Read4<TBld9>, Write4<TBld9>, ReadTextT<TBld9>, WriteTextT<TBld9>, Valid_00b1fbf0, ToXml_0057cde0)        // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 10, "mUnhappyCount", 0x04efa699, 0x29c, Read4<TBld10>, Write4<TBld10>, ReadTextT<TBld10>, WriteTextT<TBld10>, Valid_00b1fbf0, ToXml_0057cde0)  // 0x572810 0x572840 0x692ff0 0x694ee0
    ADD_ATTR(sBuildingsAttributes, 11, "mNormalModelKey", 0x05e4d3d3, 0x224, Read4<TBld11>, Write4<TBld11>, ReadTextT<TBld11>, WriteTextT<TBld11>, Valid<TBld11>, ToXmlT<TBld11>)  // 0xae3430 0xae3450 0x693150 0x695080 0xb1fbf0 0xae5720
    ADD_ATTR(sBuildingsAttributes, 12, "mbIrradiated", 0x05e4d3d4, 0x230, Read4<TBld12>, Write4<TBld12>, ReadTextT<TBld12>, WriteTextT<TBld12>, Valid<TBld12>, ToXmlT<TBld12>)     // 0xac8750 0xac8780 0x693090 0x694fa0 0xb1fbf0 0x57ce00
}

// @ 0x0132b1f0
void FUN_0132b1f0()
{
    ADD_ATTR(sBuildingWeaponsAttributes, 0, "mpCity", 0x044585b1, 0x688, Read4<TW0>, Write4<TW0>, ReadTextT<TW0>, WriteText_00692fb0, Valid<TW0>, ToXml_00ac8050)                    // 0xae9e00 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 1, "mpWeapon", 0x044585b2, 0x68c, Read4<TW1>, Write4<TW1>, ReadTextT<TW1>, WriteText_00692fb0, Valid<TW1>, ToXml_00ac8050)                  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 2, "mpCivTurretWeapon", 0x04c5a1ef, 0x690, Read4<TW2>, Write4<TW2>, ReadTextT<TW2>, WriteText_00692fb0, Valid<TW2>, ToXml_00ac8050)         // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 3, "mpSpaceBeamWeapon", 0x04c5a1f5, 0x694, Read4<TW3>, Write4<TW3>, ReadTextT<TW3>, WriteText_00692fb0, Valid<TW3>, ToXml_00ac8050)          // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 4, "mpSpaceDefenseMissileWeapon", 0x05790752, 0x698, Read4<TW4>, Write4<TW4>, ReadTextT<TW4>, WriteText_00692fb0, Valid<TW4>, ToXml_00ac8050)  // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 5, "mpSpaceTurretFlak", 0x0579fa14, 0x69c, Read4<TW5>, Write4<TW5>, ReadTextT<TW5>, WriteText_00692fb0, Valid<TW5>, ToXml_00ac8050)           // 0xbceb00 0xbd1780 0xc2e4e0 0x692fb0 0xc87090 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 6, "mDestroyTimer", 0x04161444, 0x660, Read4<TW6>, Write4<TW6>, ReadTextT<TW6>, WriteText_00692fb0, Valid<TW6>, ToXml_00ac8050)             // 0xae3470 0xae3490 0xc2e4e0 0x692fb0 0xae3310 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 7, "mFreezeCount", 0x04161445, 0x684, Read4<TW7>, Write4<TW7>, ReadTextT<TW7>, WriteTextT<TW7>, Valid<TW7>, ToXmlT<TW7>)                    // 0x572810 0x572840 0x692ff0 0x694ee0 0xb1fbf0 0x57cde0
    ADD_ATTR(sBuildingWeaponsAttributes, 8, "mpHitSphere", 0x04161446, 0x6a0, Read4<TW8>, Write4<TW8>, ReadTextT<TW8>, WriteText_00692fb0, Valid<TW8>, ToXml_00ac8050)                // 0xbd0cb0 0xbca960 0xc2e4e0 0x692fb0 0xb6f550 0xac8050
    ADD_ATTR(sBuildingWeaponsAttributes, 9, "mpFacingTarget", 0x04161447, 0x6a4, Read4<TW9>, Write4<TW9>, ReadTextT<TW9>, WriteText_00692fb0, Valid<TW9>, ToXml_00ac8050)             // 0xbd0d50 0xbd17b0 0xc2e4e0 0x692fb0 0xbcd450 0xac8050
}
