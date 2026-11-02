// src/game/SPGonzago/SPMissionExplore.cpp -- migrated from slice(s) s0133ed00, s00c5b9c0, s00c4fe60 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionExplore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cSPMission.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_010666a0();                        // get minimap provider
extern "C" void  __cdecl FUN_006a1250(void* a, int key, void* out);           // 0x006a1250 SP::GetPropertyAsKey
extern "C" int   __cdecl FUN_00e31100d();                       // 0x00e31100 UTFWin::IWinProc::GetPriority
#pragma warning(disable : 4100)

// ---- items of slice s00c4fe60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_0093ac80(void* stream, void* p);   // 0x0093ac80 ReadBool
extern "C" void  __cdecl FUN_0093a780(void* stream, void* p, int n, int f);   // 0x0093a780
extern "C" char  __cdecl FUN_0093a9a0v(void* s, void* p, int n);          // 0x0093a9a0 WriteBool-ish
extern "C" void  __cdecl FUN_0093aa70v(void* s, void* p, int n, int f);    // 0x0093aa70 WriteUint32
typedef unsigned int u32;
typedef unsigned char u8;
class Mob
{
  public:
    void* GetTargetPlanet();              // 0x00970b30 SP::cSPMission::GetTargetPlanet
    void  OnCombatantKilled(void* p);     // 0x00c4fe60
    void  OnCityDestroyed(void* p);       // 0x00c50190
    void  DestroyHerds();                 // 0x00c504a0
    void  OnPlanetDeactivate();           // 0x00c505a0
    void  OnPlanetActivate();             // 0x00c50600
    void  HandleMessage(u32 msg, void* arg);  // 0x00c4a6b0 cSPMission::HandleMessage
    int   GetTagStringBase(int tag, void* o); // 0x00c491c0 cSPMission::GetTagString
    int   GetDiseaseEffectID(int a);      // 0x00c4bd60
    void  GetText(int key, void* out);    // 0x00c487d0 SP::cSPMission::GetText
    void  TriggerUIUpdate();              // 0x00c47d80
    void  PostWarningEvent();             // 0x00c4f9d0
    void  UnkEin();                       // 0x00c4ed20
    void  UnkFfa();                       // 0x00c4fa40
    void  UnkF160();                      // 0x00c4f160
    void  UnkF320();                      // 0x00c4f320
    void  UnkFC00(void* a);               // 0x00c4fc00
    void  Unk471c0();                     // 0x00c471c0
    void  Unk472e0();                     // 0x00c472e0
    void  Unk47a10();                     // 0x00c47a10
    void  Unk48e50(int id);               // 0x00c48e50
    void  SetState(int v);                // 0x00c4eec0
    int   UnkC2b0();                      // 0x00c4c2b0
    void  BaseGetProp(void* out);          // 0x00c4bda0
    void  SerializeRecord(void* rec);     // 0x00c50ba0
    int   GetClosestDiseasedAnimalInner(void* a, void* out); // 0x00c4bdc0
    int   GetUIntField();                 // 0x008e7f80
};
class Win
{
  public:
    void  RemoveIcon(void* city, int a, int b);            // 0x00e0f9c0
    void  AddIcon(void* city, void* local, int a, int b);  // 0x00e10580
    Win*  GetWin();                                        // 0x01067e60
};
class Prop
{
  public:
    char GetKey(int key, void* out);      // vtable slot 0x24
    int* GetUInt();                       // 0x0041ea00
};
class Ref
{
  public:
    void* Assign(void* p);                // 0x00b5f950 AutoRefCount<IWinText>::operator=
};
class IOutStream
{
  public:
virtual void* s0();
virtual void* s1();
virtual void* s2();
virtual void* s3();
virtual void* s4();
virtual void* s5();
virtual void* s6();
    virtual void  Finish_1c();      // slot 7 (0x1c)
    virtual void* GetWriter_20();   // slot 8 (0x20)
virtual void* s9();
virtual void* s10();
virtual void* s11();
virtual void* s12();
virtual void* s13();
virtual void* s14();
    virtual u32   GetVersion_3c();  // slot 15 (0x3c)
};
class IWriter
{
  public:
virtual void* w0();
virtual void* w1();
virtual void* w2();
virtual void* w3();
virtual void* w4();
virtual void* w5();
    virtual void* GetStream_18();   // slot 6 (0x18)
};
static inline int  ld32(void* p, int off) { return *(int*)((char*)p + off); }
static inline u8   ldb(void* p, int off) { return *(u8*)((char*)p + off); }
static inline void** vtbl(void* p) { return *(void***)p; }
struct Rec20 { u32 a, b, c, d, e; };
struct Rec20f { float x, y, z; u8 b; float w; };
// ---- items of slice s00c4fe60 end

// ---- items of slice s00c5b9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete_array(void* p);                            // 0x00f47380
struct SPVecU32 {
  u32* begin; u32* end; u32* cap;
  void DoInsertValue(u32* pos, const u32* val);      // 0x004558a0
};
struct cSPMission {
  u32   vtbl000;                   // 0x000
  u32   vtbl004;                   // 0x004
  u32   pad008[11];                // 0x008
  u32   vtbl034;                   // 0x034
  u32   pad038[23];                // 0x038
  u32   targetEmpireID;            // 0x094
  u32   pad098[39];                // 0x098
  SPVecU32 ev134;                  // 0x134
  u32   pad140[16];                // 0x140
  void* p180;                      // 0x180
  u32   pad184[24];                // 0x184
  void* p1e4;                      // 0x1e4
  u32   pad1e8[2];                 // 0x1e8

  void  InitGeneric();             // 0x00c48e90
  void  Destroy();                 // 0x00c47680
  void* GetTargetPlanet();         // 0x00970b30
  u32   GetMissionID();            // 0x01030e10
  void  GetText(u32 tag, void* out);            // 0x00c487d0
  u8    GetTagString(u32 tag, void* out);       // 0x00c491c0
  void  OnAcceptBase();                         // 0x00c47a10
  void  HandlerComplete();                      // 0x00c46b80
  void  HandlerFail();                          // 0x00c469f0
};
struct cRaidPlunderEvent : cSPMission {
  u32   f1f0, f1f4, f1f8;
  u8    b1fc; u8 pad1fd[3];
  u32   f200, f204, f208;
  float f20c, f210;
  u32   f214, f218, f21c;
};
// ---- items of slice s00c5b9c0 end

// ---- items of slice s0133ed00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (*AttrFn)();
struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};
Attribute s_exploreAttrs[9];          // 0x01575978
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)
// ---- items of slice s0133ed00 end

// @ 0x00c50a80
int __fastcall FUN_00c50a80(void* ecx_this, void* edx)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0)
        return ld32(ecx_this, 0x208);
    return FUN_00e31100d();
}

// @ 0x00c50aa0
int __fastcall FUN_00c50aa0(void* ecx_this, void* edx)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0)
        return ld32(ecx_this, 0x204);
    return FUN_00e31100d();
}

// @ 0x00c50ac0
bool __fastcall FUN_00c50ac0(void* ecx_this, void* edx)
{
    (void)edx;
    if (*(char*)((char*)ecx_this + 0x1f4)) return true;
    return false;
}

// @ 0x00c50ad0
void __cdecl FUN_00c50ad0(Rec20* first, Rec20* last, Rec20* dstEnd)
{
    while (last != first) {
        --last;
        --dstEnd;
        *dstEnd = *last;
    }
}

// @ 0x00c50b10
void* __cdecl FUN_00c50b10(IOutStream* stream, char* rec)
{
    IWriter* w = (IWriter*)stream->GetWriter_20();
    FUN_0093ac80(w->GetStream_18(), rec + 0xc);
    IWriter* w2 = (IWriter*)stream->GetWriter_20();
    void* s2 = w2->GetStream_18();
    FUN_0093a780(s2, rec + 0x10, 1, 0);
    if (stream->GetVersion_3c() >= 0x21000eu) {
        IWriter* w3 = (IWriter*)stream->GetWriter_20();
        void* s3 = w3->GetStream_18();
        FUN_0093a780(s3, rec, 3, 0);
    }
    return stream;
}

// @ 0x00c50ba0
void* __cdecl FUN_00c50ba0(IOutStream* self, char* rec)
{
    bool b = rec[0xc] != 0;
    IWriter* w = (IWriter*)self->GetWriter_20();
    FUN_0093a9a0v(w->GetStream_18(), &b, 1);
    IWriter* w2 = (IWriter*)self->GetWriter_20();
    float f = *(float*)(rec + 0x10);
    FUN_0093aa70v(w2->GetStream_18(), &f, 1, 0);
    IWriter* w3 = (IWriter*)self->GetWriter_20();
    FUN_0093aa70v(w3->GetStream_18(), rec, 3, 0);
    return self;
}

// @ 0x00c50c30
void __fastcall FUN_00c50c30(void* ecx_this, void* edx, void* city)
{
    (void)ecx_this; (void)edx;
    if (!city)
        return;
    void* provider = FUN_010666a0();
    if (!provider)
        return;
    if (!((Win*)provider)->GetWin())
        return;
    // local 0x24-byte city icon descriptor: { color, pos.x, pos.y, pos.z, flags,
    //   mpText, zero, zero, zero }
    struct CityIcon {
        int   color;        // +0x00
        float x;            // +0x04
        float y;            // +0x08
        float z;            // +0x0c
        int   flags;        // +0x10
        void* mpText;       // +0x14
        int   pad[3];       // +0x18
    };
    CityIcon d;
    d.color = 0;
    d.x = 0.0f;
    d.y = 0.0f;
    d.z = -1.0f;                 // 0x13eb1bc = -1.0f
    d.flags = 0x20000;
    d.mpText = 0;
    d.pad[0] = 0;
    d.pad[1] = 0;
    d.pad[2] = 0;
    // city +0x120 vtable slot 0x2c -> returns const Vector3*
    float* pos = (float*)(*(void* (__thiscall**)(void*))((char*)vtbl((char*)city + 0x120) + 0x2c))((char*)city + 0x120);
    d.x = pos[0];
    d.y = pos[1];
    d.z = pos[2];
    d.color = (int)0xff000000;
    ((Ref*)&d.mpText)->Assign(0);
    ((Win*)FUN_010666a0())->GetWin()->RemoveIcon(city, 1, 0);
    ((Win*)FUN_010666a0())->GetWin()->AddIcon(city, &d, 0, 0);
    if (d.mpText)
        (*(void (__thiscall**)(void*))((char*)vtbl(d.mpText) + 4))(d.mpText);
}

// @ 0x00c50d20
float* __fastcall FUN_00c50d20(void* ecx_this, void* edx, void* city)
{
    (void)edx;
    float* pos = (float*)(*(void* (__thiscall**)(void*))((char*)vtbl((char*)city + 0x120) + 0x2c))((char*)city + 0x120);
    struct CityRec { float x, y, z; unsigned char b; float w; };  // 0x14 bytes
    char* begin = (char*)ld32(ecx_this, 0x214);
    int count = (ld32(ecx_this, 0x218) - (int)begin) / 0x14;
    if (count <= 0)
        return 0;
    CityRec* rec = (CityRec*)begin;
    for (int i = 0; i < count; i++, rec++) {
        float dx = rec->x - pos[0];
        float dz = rec->z - pos[2];
        float dy = rec->y - pos[1];
        float dist = dx * dx + dz * dz + dy * dy;
        if (100.0f > dist)
            return (float*)rec;
    }
    return 0;
}

// @ 0x00c50dd0
void __fastcall FUN_00c50dd0(void* ecx_this, void* edx, void* out)
{
    (void)edx;
    if (ldb(ecx_this, 0x1f4) != 0) {
        FUN_006a1250((void*)ld32(ecx_this, 0x180), (int)0xff60c676, out);
        return;
    }
    ((Mob*)ecx_this)->BaseGetProp(out);
}

// @ 0x00c50e00
void __cdecl FUN_00c50e00(IOutStream* self, void* vec)
{
    int n = (ld32(vec, 4) - ld32(vec, 0)) / 0x14;
    IWriter* w = (IWriter*)self->GetWriter_20();
    FUN_0093aa70v(w->GetStream_18(), &n, 1, 0);
    char* p = (char*)ld32(vec, 0);
    char* e = (char*)ld32(vec, 4);
    while (p != e) {
        FUN_00c50ba0(self, p);
        p += 0x14;
    }
    self->Finish_1c();
}

// @ 0x00c50e70
void __cdecl FUN_00c50e70(Rec20f* s, Rec20f* srcEnd, Rec20f* d)
{
    while (s != srcEnd) {
        if (d) {
            d->x = s->x;
            d->y = s->y;
            d->z = s->z;
            d->b = s->b;
            d->w = s->w;
        }
        s++;
        d++;
    }
}

// @ 0x00c50eb0
int __fastcall FUN_00c50eb0(void* ecx_this, void* edx)
{
    (void)edx;
    void* key;
    if (ldb(ecx_this, 0x1f4) != 0) {
        int result = 0;
        void* prop = (void*)ld32(ecx_this, 0x180);
        if (prop) {
            if ((*(char (__thiscall**)(void*, int, void**))((char*)vtbl(prop) + 0x24))(prop, 0x5d6796fd, &key)) {
                if (*(short*)((char*)key + 0x12) == 10)
                    result = *((Prop*)key)->GetUInt();
            }
        }
        return result;
    }
    return ((Mob*)ecx_this)->UnkC2b0();
}

// @ 0x00c5bd00
void* __fastcall FUN_00c5bd00(cRaidPlunderEvent* self, void* dummy, u32 flags)
{
  (void)dummy;
  if (self->f214 != 0 && ((u32*)self->f214)[-1] != 0)
    operator_delete_array((void*)self->f214);
  self->Destroy();
  if ((flags & 1) != 0)
    operator_delete_array(self);
  return self;
}

// @ 0x013413f0
void FUN_013413f0()
{
    ATTR(s_exploreAttrs[0], "mExploreMissionState", 0x3852454, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[1], "mVisitCities", 0x3852455, 0x1f4,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_exploreAttrs[2], "mVisitRadius", 0x3852456, 0x1f8,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_exploreAttrs[3], "mNumVisitedCities", 0x3852457, 0x208,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[4], "mCityVisitInfosInitialized", 0x3852459, 0x210,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_exploreAttrs[5], "mEffectHeight", 0x3852460, 0x1fc,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_exploreAttrs[6], "mNumCitiesToVisit", 0x3852461, 0x204,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[7], "mExploreType", 0x3852462, 0x20c,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_exploreAttrs[8], "mCityVisitInfos", 0x3852463, 0x214,
         0x692ca0, 0xc51630, 0xc50e00, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xc51440);
}
