// Slice s00c3daa0 - SPGonzago/SPGameDataUFO.obj region 0x00c3daa0..0x00c3ee20:
// cSPGameDataUFO destination/init/NPC, cGamePlant ctor/dtor + serialization, and
// cGameplayMarker / cCommunity helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include  (no /EHsc)
#include "types.h"
#include <math.h>
#include <stdlib.h>

typedef unsigned int uint;

// ---- external callees (addresses in comments) -------------------------
void* __cdecl FUN_00c3be70(void*);                            // 0x00c3be70
void  __cdecl WString_Assign(void*, void*);                    // 0x00423650
void* __cdecl GetUniverseContext();                            // 0x01021080 SP::cSPLivingUniverse::GetUniverseContext
void  __cdecl FUN_00c37e60(void*);                             // 0x00c37e60 PopToDestination
void* __cdecl FUN_00c3bfe0(void*, void*);                      // 0x00c3bfe0 SetDestination
void  __stdcall FUN_00c3c810(void*, void*);                    // 0x00c3c810
void* __cdecl NounManager();                                   // 0x00b3d300
void* __cdecl FUN_00b20c60(void*, int);                        // 0x00b20c60 cGameNounManager::CreateNoun
void* __cdecl PlanetModel();                                   // 0x00b3d350
float __cdecl FUN_00b7e4d0(void*);                             // 0x00b7e4d0
void* __cdecl GetSpaceCombatTuning();                          // 0x01029940
int   __cdecl FUN_01021240();                                  // 0x01021240 cSPMission::IsArchived
float* __cdecl FUN_005c65e0(void*);                            // 0x005c65e0 cCivData::GetCities
int   __cdecl FUN_0102a360(void*, void*, void*, void*);        // 0x0102a360 cSPSpaceCombatTuning::GetWeaponLevel
int   __cdecl FUN_00c317a0(void*);                             // 0x00c317a0 cEmpire::GetWeaponryLevel
double __cdecl FUN_0059da80(float);                            // 0x0059da80 RandomRange
void  __cdecl FUN_00c3f160(void*, float);                      // 0x00c3f160
void  __cdecl FUN_00c3f1b0(void*, int, float);                 // 0x00c3f1b0
void  __cdecl FUN_00c3f2d0(void*, void*);                      // 0x00c3f2d0
void  __cdecl FUN_00c385d0(void*);                             // 0x00c385d0
float __cdecl FUN_0102a630(void*, float, int);                 // 0x0102a630 cSPSpaceCombatTuning::GetUFOHealth
void  __cdecl FUN_00c3a220(int, float, void*);                 // 0x00c3a220 enableWeapon
void  __cdecl FUN_00c3a2b0(void*, int);                        // 0x00c3a2b0 OnContextChange
void* __cdecl FUN_00c463d0(void*);                             // 0x00c463d0
void  __cdecl FUN_00b3d390(void*, void*);                      // 0x00b3d390 eastl vector erase
void* __cdecl FUN_0104e340(void*, void*);                      // 0x0104e340 cSPToolManager::CreateToolFromToolID
struct Fn455d60 { void __thiscall append(const char*, const char*); };  // 0x00455d60 eastl string::append
void* __cdecl FUN_005f9450(void*, const char*, ...);           // 0x005f9450 append_sprintf
void  __cdecl FUN_00563de0(void*, void*);                      // 0x00563de0
void* __cdecl FUN_00ffbe50();                                  // 0x00ffbe50 GetUFOSimulator
float __cdecl FUN_00ffd8e0(void*);                             // placeholder unused
struct FnFFd8e0 { float __thiscall f(); };                     // 0x00ffd8e0 CalculateMaxHealth
struct FnFFda80 { float __thiscall f(); };                     // 0x00ffda80 CalculateMaxEnergy
void* __cdecl FUN_0067dcc0();                                  // 0x0067dcc0 MessageServer
struct FnC326b0 { void* __thiscall f(int); };                 // 0x00c326b0 cEmpire::GetUFOKey
struct FnC37180 { void* __thiscall f(void*); };                // 0x00c37180 SetDesiredModel
struct FnC43fe0 { void* __thiscall f(void*); };                // 0x00c43fe0
void  __cdecl FUN_00c41d00(void*, int);                        // 0x00c41d00
void* __cdecl FUN_00b18460(int);                               // 0x00b18460
struct FnB184c0 { void __thiscall f(); };                      // 0x00b184c0 cGameData::~cGameData
struct FnA05270 { void __thiscall f(); };                      // 0x00a05270 cAnimatingCreature::Release
struct FnAbfec0 { void __thiscall f(); };                      // 0x00abfec0
struct FnBfcd00 { void __thiscall f(); };                      // 0x00bfcd00
struct FnAc0520 { void __thiscall f(); };                      // 0x00ac0520
struct FnC432e0 { void __thiscall f(); };                      // 0x00c432e0
void  __cdecl FUN_00a05270(void*);                             // 0x00a05270 cAnimatingCreature::Release
struct FnA02c30 { void __thiscall f(); };                      // 0x00a02c30 cAnimatingCreature::AddRef
void* __cdecl FUN_00b18660(void*);                             // 0x00b18660 cGameData::cGameData
void  __cdecl FUN_00c43860(void*);                             // 0x00c43860
void  __cdecl FUN_00ac03d0(void*);                             // 0x00ac03d0 cInteractionTarget::cInteractionTarget
void  __cdecl FUN_00bfd4e0(void*);                             // 0x00bfd4e0 cCombatant::cCombatant
void  __cdecl FUN_00abfe50(void*);                             // 0x00abfe50
void* __cdecl FUN_00b18420(void*, void*);                      // 0x00b18420 cGameData::WriteAsText
void  __cdecl FUN_00692f90(void*, void*, void*, int);          // 0x00692f90 cVarListSerializer::cVarListSerializer
int   __cdecl FUN_00695960(void*, void*);                      // 0x00695960 cVarListSerializer::GetFields
bool  __cdecl FUN_00693e10(void*, void*);                      // 0x00693e10 Serialize(in)
bool  __cdecl FUN_00692900(void*, void*);                      // 0x00692900 Serialize(out)
void* __cdecl FUN_00b18600(void*, void*);                      // 0x00b18600 cGameData::Read
void* __cdecl FUN_00b18590(void*, void*);                      // 0x00b18590 cGameData::Write
void* __cdecl FUN_00c88a90(void*, void*);                      // 0x00c88a90 cSpatialObject::Write
void* __cdecl FUN_00c88b00(void*, void*);                      // 0x00c88b00
bool  __cdecl FUN_0093a780(void*, void*, int, int);            // 0x0093a780 ReadInt32
bool  __cdecl FUN_0093aa70(void*, void*, int, int);            // 0x0093aa70 WriteUint32
bool  __cdecl FUN_0093a9d0(void*, void*, int, int);            // 0x0093a9d0 WriteUint16
struct FnC8a420 { void __thiscall f(); };                      // 0x00c8a420
struct Fn88670 { void __thiscall f(void*); };                 // 0x00c88670
struct Fn886d0 { void __thiscall f(void*); };                 // 0x00c886d0
void* __cdecl FUN_00401090(void*);                             // 0x00401090 GetSetting
void* __cdecl FUN_004df440(void*);                             // 0x004df440 GetPlantProfile

// __thiscall member-method stubs (free functions cannot be __thiscall)
struct C3ebd0 { void f(int* p); };                             // 0x00c3ebd0
struct C3ec00 { void f(int* p); };                             // 0x00c3ec00
struct C3ec40 { void f(); };                                   // 0x00c3ec40
struct C3eac0 { void* f(void* other); };                       // 0x00c3eac0
struct C3e510 { void* f(); };                                  // 0x00c3e510
struct C3e700 { void f(); };                                   // 0x00c3e700
struct C3e800 { void f(void* p); };                            // 0x00c3e800
struct C3e8e0 { void f(int* p); };                             // 0x00c3e8e0

extern float gF_146bb6c;   // 0x0146bb6c  float constant
extern float gF_146be54;   // 0x0146be54  "%f" format
extern float gF_13f7670;   // 0x013f7670  35.0f
extern float gF_13eecd8;   // 0x013eecd8  RandomRange bound
extern float gF_1473c70;   // 0x01473c70  RandomRange bound
extern float gF_13ec488;   // 0x013ec488  0.5f
extern float gF_13eb8b0;   // 0x013eb8b0  sign-mask
extern float gF_1485378;   // 0x01485378  0.0f
extern float gF_1485720;   // 0x01485720  1.0f
extern float gF_13eb1bc;   // 0x013eb1bc  -1.0f
extern float gF_142eae0;   // 0x0142eae0  float constant
extern void* g_168df68;    // 0x0168df68
extern float gF_168df74;   // 0x0168df74
extern void* g_168e568;    // 0x0168e568
extern int   g_168e56c;    // 0x0168e56c
extern int   g_168e570;    // 0x0168e570
extern int   g_168e57c;    // 0x0168e57c  (dword guard, tested as byte)

// ---- object layouts (retail offsets) ----------------------------------
struct Obj { char b[0x1000]; };
struct Fn3be70 { void __thiscall f(void*); };                  // 0x00c3be70
struct Fn37e60 { void __thiscall f(); };                       // 0x00c37e60 PopToDestination
struct Fn3bfe0 { void __thiscall f(void*); };                  // 0x00c3bfe0 SetDestination
struct Fn3c810 { void __thiscall f(void*); };                  // 0x00c3c810
struct Fn3f160 { void __thiscall f(float); };                  // 0x00c3f160
struct Fn3f1b0 { void __thiscall f(float, float); };           // 0x00c3f1b0
struct Fn3f2d0 { void __thiscall f(void*); };                  // 0x00c3f2d0
struct Fn385d0 { void __thiscall f(); };                       // 0x00c385d0
struct Fn3a2b0 { void __thiscall f(int); };                    // 0x00c3a2b0 OnContextChange
struct Fn3e8e0 { void __thiscall f(void*); };                  // 0x00c3e8e0
struct Fn3dba0 { void __thiscall f(int, float); };             // 0x00c3dba0 InitNPC
struct Fn3dae0 { void __thiscall f(void*); };                  // 0x00c3dae0
struct Fn437e60 { void __thiscall f(); };                      // 0x00c37e60

// cSPGameDataUFO retail layout (generated header drifts; use retail offsets)
struct UFO {
    char  pad0[0x34];
    void* mpSpatial;          // +0x34   cSpatialObject
    char  pad1[0x4f8 - 0x38];
    char  padMove[0x20];      // +0x4f8  mMovementTimer
    char  padHover[0x20];     // +0x518  mHoverTimer
    char  padColl[0x20];      // +0x538  mCollisionTimer
    char  pad2[0x68c - 0x558];
    uint8_t mFlag690;         // +0x690
    char  pad3[0x714 - 0x691];
    int   mType714;           // +0x714
    char  pad4[0x750 - 0x718];
    float pos750;             // +0x750
    char  pad5[0x768 - 0x754];
    float field768;           // +0x768
    char  pad6[0x7d8 - 0x76c];
    void* mpNoun7d8;          // +0x7d8  noun object
    char  pad7[0x7e0 - 0x7dc];
    char  str7e0[0x8];        // +0x7e0  eastl string

    void func3daa0(float val);     // 0x00c3daa0
    void func3dac0(void* p);       // 0x00c3dac0
    void func3dae0(float* p);      // 0x00c3dae0
    void func3db50(void* a, void* b); // 0x00c3db50
    void func3dba0(int a, float b);   // 0x00c3dba0
    void func3e0b0(float a, void* b); // 0x00c3e0b0
    void func3e010(void* s);       // 0x00c3e010
};

struct Plant { char b[0x1000]; };
struct Fn43e700 { void __thiscall f(); };   // 0x00c3e700
struct Fn43e800 { void __thiscall f(void*); };  // 0x00c3e800
struct Fn43ec40 { void __thiscall f(); };   // 0x00c3ec40
struct Fn43eac0 { void __thiscall f(void*); };  // 0x00c3eac0
struct Fn43ebd0 { void __thiscall f(void*); };  // 0x00c3ebd0
struct Fn43ec00 { void __thiscall f(void*); };  // 0x00c3ec00

// =======================================================================
// cSPGameDataUFO::SetDestination (0x00c3daa0) -- 29 bytes
// =======================================================================
// @ 0x00c3daa0
void UFO::func3daa0(float val)
{
    char* self = (char*)this;
    *(float*)(self + 0x768) = val;
    void* key = self + 0x750;
    ((Fn3be70*)self)->f(key);
}

// =======================================================================
// cSPGameDataUFO (0x00c3dac0) -- 29 bytes
// =======================================================================
struct Str { void __thiscall assign(void*, void*); };
// @ 0x00c3dac0
void UFO::func3dac0(void* p)
{
    char* self = (char*)this;
    char* dst = self + 0x7e0;
    if ((char*)p != dst) {
        void** v = (void**)p;
        ((Str*)dst)->assign(v[0], v[1]);
    }
}

// =======================================================================
// 0x00c3dae0 -- 104 bytes
// =======================================================================
// @ 0x00c3dae0
void UFO::func3dae0(float* p)
{
    char* self = (char*)this;
    if (GetUniverseContext() == 0) {
        ((Fn3be70*)self)->f(p);
        *(float*)(self + 0x768) = (float)sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
        ((Fn3be70*)self)->f(self + 0x750);
    } else {
        ((Fn3bfe0*)self)->f(p);
    }
    ((Fn37e60*)self)->f();
}

// =======================================================================
// 0x00c3db50 -- 68 bytes
// =======================================================================
// @ 0x00c3db50
void UFO::func3db50(void* a, void* b)
{
    char* self = (char*)this;
    struct { int a; float b, c, d; } tmp;
    float* v = (float*)b;
    tmp.a = (int)a;
    tmp.b = v[0];
    tmp.c = v[1];
    tmp.d = v[2];
    FUN_00c3c810(self + 0x770, &tmp);
}

// =======================================================================
// SP::cSPGameDataUFO::AddDebugInfo (0x00c3e010) -- 145 bytes
// =======================================================================
// @ 0x00c3e010
void UFO::func3e010(void* s)
{
    char* self = (char*)this;
    char* q = (char*)s;
    if (*(int*)(self + 0x714) == 0) {
        ((Fn455d60*)q)->append("== Player UFO ==", (const char*)0x146be9c);
    } else {
        ((Fn455d60*)q)->append("== NPC UFO ==", (const char*)0x146be89);
    }
    FUN_005f9450(q, (const char*)0x146be68, (double)*(float*)(self + 0x768));

    float hp = *(float*)(self + 0x540);
    void* sub = self + 0x508;
    typedef float(__thiscall* GetF)(void*);
    float maxf = ((GetF)(*(void**)(*(char**)sub + 0x58)))(sub);
    FUN_005f9450(q, (const char*)0x146be54, (double)hp, (double)maxf);

    FUN_00563de0(self + 0x780, q);
}

// =======================================================================
// SP::cSPGameDataUFO::Init (0x00c3e0b0) -- 252 bytes
// =======================================================================
// @ 0x00c3e0b0
void UFO::func3e0b0(float a, void* empire)
{
    char* self = (char*)this;
    *(int*)(self + 0x714) = *(int*)&a;
    if (empire != 0) {
        char* e = (char*)empire;
        typedef void(__thiscall* Vf)(void*, void*);
        ((Vf)(*(void**)(*(char**)self + 0x48)))(self, *(void**)(e + 0x84));
        void* key = ((FnC326b0*)e)->f(1);
        ((FnC37180*)self)->f(key);
    }
    if (*(int*)(self + 0x714) == 0) {
        float h = ((FnFFd8e0*)FUN_00ffbe50())->f();
        *(float*)(self + 0x534) = h;
        *(float*)(self + 0x540) = h;
        float en = ((FnFFda80*)FUN_00ffbe50())->f();
        *(float*)(self + 0x7f8) = en;
        *(float*)(self + 0x7f4) = en;

        void* sub = self + 0x5e8;
        void* ms = FUN_0067dcc0();
        *(void**)(self + 0x804) = ms;
        *(void**)(self + 0x808) = sub;
        *(int*)(self + 0x80c) = 0x146bb58;
        *(int*)(self + 0x810) = 2;
        *(int*)(self + 0x814) = 0;
        if (ms != 0 && sub != 0) {
            unsigned int off = 0;
            do {
                typedef void(__thiscall* Vf)(void*, void*, void*);
                ((Vf)(*(void**)(*(char**)ms + 0x24)))(ms, sub, *(void**)(off + 0x146bb58));
                off += 4;
            } while (off < 8);
        }
        ((FnC43fe0*)(self + 0x34))->f((void*)0xb4c850);
        return;
    }
    ((Fn3dba0*)self)->f((int)empire, -1.0f);
    ((FnC43fe0*)(self + 0x34))->f((void*)0xb4c850);
}

// =======================================================================
// Object::Cast (0x00c3e2c0) -- 133 bytes
// =======================================================================
// @ 0x00c3e2c0
void* __cdecl FUN_00c3e2c0(void* self, int type)
{
    if ((unsigned)type < 0x11c0ba4) {
        if (type != 0x11c0ba3) {
            if (type == (int)0xaeb336b4 || type == (int)0xee3f516e) {
                return self;
            }
        } else {
            if (self != 0) return (char*)self + 0x5e8;
            return 0;
        }
    } else if (type == 0x13f94d4) {
        if (self != 0) return (char*)self + 0x520;
        return 0;
    } else if (type == 0x102a041a) {
        if (self != 0) return (char*)self + 0x504;
        return 0;
    }
    void* r = FUN_00b18460(type);
    if (r != 0) return r;
    FUN_00c41d00((char*)self + 0x34, type);
    return 0;
}

// =======================================================================
// 0x00c3e350 -- 11 bytes
// =======================================================================
// @ 0x00c3e350
void __fastcall FUN_00c3e350(char* self)
{
    typedef void(__fastcall* Vf)(void*);
    ((Vf)(*(void**)(*(char**)(self + 0x34) + 0x2c)))(self + 0x34);
}

// =======================================================================
// SP::cGamePlant::Write (0x00c3e3b0) -- 159 bytes
// =======================================================================
// @ 0x00c3e3b0
char __cdecl FUN_00c3e3b0(char* self, void* stream)
{
    char buf[8];
    char ser[0x18];  // cVarListSerializer (>=0x14)
    typedef void* (__thiscall* M0)(void*);
    void* s2 = ((M0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* M1)(void*);
    void* s3 = ((M1)(*(void**)(*(char**)s2 + 0x18)))(s2);
    *(int*)buf = (int)0xaeb336b4;
    FUN_0093aa70(s3, buf, 1, 0);
    char ok = (char)FUN_00b18590(self, stream);
    if (ok) {
        ok = (char)FUN_00c88a90(self + 0x34, stream);
        if (ok) ok = 1; else ok = 0;
    } else {
        ok = 0;
    }
    FUN_00692f90(ser, self, (void*)0x1573a60, 0x1a80d26);
    if (ok) {
        if (FUN_00692900(ser, stream)) {
            return 1;
        }
    }
    return 0;
}

// =======================================================================
// 0x00c3e460 -- 33 bytes
// =======================================================================
// @ 0x00c3e460
float __fastcall FUN_00c3e460(char* self)
{
    float v = *(float*)(self + 0x640);
    if (v >= 0.0f) return v;
    return *(float*)(self + 0x5c);
}

// =======================================================================
// Simulator::cGameData::WriteAsText (0x00c3e490) -- 115 bytes
// =======================================================================
// @ 0x00c3e490
int __cdecl FUN_00c3e490(char* self, void* stream)
{
    char serA[0x14];
    char serB[0x1414];
    int n = (int)FUN_00b18420(self, stream);
    FUN_00692f90(serA, self + 0x34, (void*)0x157a1f8, 0x1a80d26);
    n += FUN_00695960(serA, stream);
    FUN_00692f90(serB, self, (void*)0x1573a60, 0x1a80d26);
    n += FUN_00695960(serB, stream);
    return n;
}

// =======================================================================
// Simulator::cGamePlant::cGamePlant (0x00c3e510) -- 248 bytes
// =======================================================================
// @ 0x00c3e510
void* C3e510::f()
{
    char* self = (char*)this;
    FUN_00b18660(self);
    char* p34 = self + 0x34;
    FUN_00c43860(p34);
    char* p504 = self + 0x504;
    FUN_00ac03d0(p504);
    char* p520 = self + 0x520;
    FUN_00bfd4e0(p520);
    FUN_00abfe50(self + 0x5e8);

    *(int*)(self) = 0x146c308;
    *(int*)(self + 4) = 0x146c2f4;
    *(int*)(p34) = 0x146c1f8;
    *(int*)(self + 0x108) = 0x146c1ec;
    *(int*)(p504) = 0x146c1d0;
    *(int*)(p520) = 0x146c168;
    *(int*)(self + 0x5e8) = 0x146c100;

    *(int*)(self + 0x650) = 0;
    *(int*)(self + 0x654) = 0;
    *(int*)(self + 0x658) = 0;
    *(int*)(self + 0x65c) = *(int*)0x168e5b0;
    *(int*)(self + 0x660) = *(int*)0x168e5b4;
    *(int*)(self + 0x668) = 0;
    *(int*)(self + 0x664) = *(int*)0x168e5b8;
    *(float*)(self + 0x66c) = gF_1485720;
    *(int*)(self + 0x670) = 0;
    *(uint8_t*)(self + 0xa3) = 0;
    *(float*)(self + 0x674) = gF_13eb1bc;
    *(float*)(self + 0x678) = gF_1485720;
    *(int*)(self + 0x88) = 2;
    *(uint8_t*)(self + 0xa5) = 1;
    return self;
}

// =======================================================================
// 0x00c3e700 -- 131 bytes
// =======================================================================
// @ 0x00c3e700
void C3e700::f()
{
    char* self = (char*)this;
    char* p34 = self + 0x34;
    char* p504 = self + 0x504;
    char* p520 = self + 0x520;
    *(int*)(self) = 0x146c308;
    *(int*)(self + 4) = 0x146c2f4;
    *(int*)(p34) = 0x146c1f8;
    *(int*)(self + 0x108) = 0x146c1ec;
    *(int*)(p504) = 0x146c1d0;
    *(int*)(p520) = 0x146c168;
    *(int*)(self + 0x5e8) = 0x146c100;

    void* p = *(void**)(self + 0x670);
    if (p != 0) ((FnA05270*)p)->f();
    ((FnAbfec0*)(self + 0x5e8))->f();
    ((FnBfcd00*)p520)->f();
    ((FnAc0520*)p504)->f();
    ((FnC432e0*)p34)->f();
    ((FnB184c0*)self)->f();
}

// =======================================================================
// 0x00c3e800 -- 224 bytes
// =======================================================================
// @ 0x00c3e800
void C3e800::f(void* p2)
{
    char* self = (char*)this;
    char* q = (char*)p2;
    char* old = *(char**)(self + 0x670);
    if (q != old) {
        if (q != 0) ((FnA02c30*)q)->f();
        *(char**)(self + 0x670) = q;
        if (old != 0) ((FnA05270*)old)->f();
    }
    if (q != 0) {
        float f = *(float*)(q + 0x3c);
        void* pIdx = *(void**)(q + 0x17c);
        void* v = *(void**)pIdx;
        float buf[6];
        buf[0] = (*(float*)((char*)v + 0x364) * f) * gF_13ec488;
        buf[1] = (*(float*)((char*)v + 0x368) * f) * gF_13ec488;
        buf[2] = 0.0f;
        buf[3] = -buf[0];
        buf[4] = -buf[1];
        buf[5] = *(float*)((char*)v + 0x36c) * f;

        char* sp = self + 0x34;
        void* sub = *(void**)sp;
        typedef float(__thiscall* G)(void*);
        float r = ((G)(*(void**)((char*)sub + 0x34)))(sp);
        typedef void(__thiscall* Vf)(void*, void*, float);
        ((Vf)(*(void**)((char*)sub + 0x64)))(sp, buf, r);
    }
}

// =======================================================================
// 0x00c3e8e0 -- 228 bytes
// =======================================================================
// @ 0x00c3e8e0
void C3e8e0::f(int* p)
{
    char* self = (char*)this;
    if (*p != 0) {
        void* prof = FUN_004df440(FUN_00401090(p));
        *(void**)(self + 0x668) = prof;
        if (prof != 0) {
            char* pr = (char*)prof;
            float s = *(float*)(self + 0x66c);
            float x = (*(float*)(pr + 0x554) * 0.5f) * s;
            float y = (*(float*)(pr + 0x558) * 0.5f) * s;
            float buf[6];
            buf[0] = x;
            buf[1] = y;
            buf[2] = 0.0f;
            buf[3] = -y;
            buf[4] = -x;
            buf[5] = *(float*)(pr + 0x55c) * s;

            char* sp = self + 0x34;
            void* sub = *(void**)sp;
            typedef void(__thiscall* Vf)(void*, void*, float);
            ((Vf)(*(void**)((char*)sub + 0x64)))(sp, buf, 1.0f);
        }
    }
    *(int*)(self + 0x650) = p[0];
    *(int*)(self + 0x654) = p[1];
    *(int*)(self + 0x658) = p[2];
}

// =======================================================================
// Simulator::cGamePlant::Read (0x00c3e9d0) -- 157 bytes
// =======================================================================
// @ 0x00c3e9d0
char __cdecl FUN_00c3e9d0(char* self, void* stream)
{
    char buf[4];
    char ser[0x18];
    typedef void* (__thiscall* M0)(void*);
    void* s2 = ((M0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* M1)(void*);
    void* s3 = ((M1)(*(void**)(*(char**)s2 + 0x18)))(s2);
    FUN_0093a780(s3, buf, 1, 0);

    char bl;
    if ((char)FUN_00b18600(self, stream)) {
        if ((char)FUN_00c88b00(self + 0x34, stream)) bl = 1;
        else bl = 0;
    } else bl = 0;

    FUN_00692f90(ser, self, (void*)0x1573a60, 0x1a80d26);
    if (bl) {
        if (FUN_00693e10(ser, stream)) bl = 1; else bl = 0;
    } else bl = 0;
    ((Fn3e8e0*)self)->f(self + 0x650);
    return bl;
}

// =======================================================================
// 0x00c3ea80 -- 55 bytes (static local guard)
// =======================================================================
// @ 0x00c3ea80
void* __cdecl FUN_00c3ea80()
{
    int one = 1;
    if (((char)g_168e57c & one) == 0) {
        g_168e57c |= one;
        g_168e568 = 0;
        g_168e56c = 0;
        g_168e570 = 0;
        atexit((void(__cdecl*)(void))0x13c3880);
    }
    return &g_168e568;
}

// =======================================================================
// 0x00c3eac0 -- 120 bytes
// =======================================================================
// @ 0x00c3eac0
void* C3eac0::f(void* other_)
{
    char* self = (char*)this;
    char* other = (char*)other_;
    *(int*)(self + 0x108) = *(int*)(other + 0x108);
    *(int*)(self + 0x10c) = *(int*)(other + 0x10c);
    *(int*)(self + 0x110) = *(int*)(other + 0x110);

    int* src = (int*)(other + 0x114);
    int* dst = (int*)(self + 0x114);
    for (int i = 0x22; i != 0; i--) *dst++ = *src++;

    char* oSub = *(char**)(other + 0x34);
    char* sSub = *(char**)(self + 0x34);
    typedef void* (__thiscall* G)(void*);
    typedef void  (__thiscall* S)(void*, void*);
    void* a = ((G)(*(void**)(oSub + 0x2c)))(other + 0x34);
    ((S)(*(void**)(sSub + 0x38)))(self + 0x34, a);
    oSub = *(char**)(other + 0x34);
    sSub = *(char**)(self + 0x34);
    void* b = ((G)(*(void**)(oSub + 0x30)))(other + 0x34);
    ((S)(*(void**)(sSub + 0x3c)))(self + 0x34, b);
    return self;
}

// =======================================================================
// 0x00c3ebd0 -- 45 bytes
// =======================================================================
// @ 0x00c3ebd0
void C3ebd0::f(int* p)
{
    char* self = (char*)this;
    ((Fn88670*)self)->f(p);
    *(int*)(self + 0x174) = p[0];
    *(int*)(self + 0x178) = p[1];
    *(int*)(self + 0x17c) = p[2];
}

// =======================================================================
// 0x00c3ec00 -- 54 bytes
// =======================================================================
// @ 0x00c3ec00
void C3ec00::f(int* p)
{
    char* self = (char*)this;
    ((Fn886d0*)self)->f(p);
    *(int*)(self + 0x180) = p[0];
    *(int*)(self + 0x184) = p[1];
    *(int*)(self + 0x188) = p[2];
    *(int*)(self + 0x18c) = p[3];
}

// =======================================================================
// 0x00c3ec40 -- 93 bytes
// =======================================================================
// @ 0x00c3ec40
void C3ec40::f()
{
    char* self = (char*)this;
    char* p34 = self + 0x34;
    *(int*)(self) = 0x146c460;
    *(int*)(self + 4) = 0x146c44c;
    *(int*)(p34) = 0x146c388;

    void* p;
    p = *(void**)(self + 0x1a4);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }
    p = *(void**)(self + 0x1a0);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }
    p = *(void**)(self + 0x19c);
    if (p) { typedef void(__thiscall* Vf)(void*); ((Vf)(*(void**)(*(char**)p + 4)))(p); }

    ((FnC8a420*)p34)->f();
    ((FnB184c0*)self)->f();
}

// =======================================================================
// SP::cGameplayMarker::Write (0x00c3ed20) -- 252 bytes
// =======================================================================
// @ 0x00c3ed20
char __cdecl FUN_00c3ed20(char* self, void* stream)
{
    char buf[8];
    char ser[0x18];
    typedef void* (__thiscall* M0)(void*);
    void* s2 = ((M0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* M1)(void*);
    void* s3 = ((M1)(*(void**)(*(char**)s2 + 0x18)))(s2);
    *(int*)buf = 0x36be278;
    FUN_0093aa70(s3, buf, 1, 0);

    char bl = (char)FUN_00b18590(self, stream) & 1;
    bl &= (char)FUN_00c88a90(self + 0x34, stream);

    void* p1a4 = *(void**)(self + 0x1a4);
    if (p1a4 != 0) {
        typedef char(__thiscall* Vf)(void*);
        if (((Vf)(*(void**)(*(char**)p1a4 + 0x2c)))(p1a4)) {
            void* q = *(void**)(self + 0x1a4);
            if (q != 0) {
                *(void**)(self + 0x1a4) = 0;
                typedef void(__thiscall* D)(void*);
                ((D)(*(void**)(*(char**)q + 4)))(q);
            }
            *(uint8_t*)(self + 0x1c4) = 1;
        }
    }

    FUN_00692f90(ser, self, (void*)0x1573ad8, 0x1a80d26);
    bl &= (char)FUN_00692900(ser, stream);

    typedef void* (__thiscall* N0)(void*);
    void* n2 = ((N0)(*(void**)(*(char**)stream + 0x20)))(stream);
    typedef void* (__thiscall* N1)(void*);
    void* n3 = ((N1)(*(void**)(*(char**)n2 + 0x18)))(n2);
    *(int*)buf = 0x88;
    FUN_0093a9d0(n3, buf, 1, 0);

    typedef void(__thiscall* W)(void*, void*, int);
    ((W)(*(void**)(*(char**)stream + 0x34)))(stream, self + 0x114, 0x88);
    return bl;
}

// =======================================================================
// SP::cSPGameDataUFO::InitNPC (0x00c3dba0) -- 1136 bytes
// =======================================================================
// @ 0x00c3dba0
void UFO::func3dba0(int param_2, float param_3)
{
    char* self = (char*)this;
    char* ctx = (char*)GetUniverseContext();
    char bUniv0 = (ctx == 0) ? 1 : 0;

    void* nm = NounManager();
    void* noun = FUN_00b20c60(nm, 0x2e72cae);
    char* npc;
    if (noun != 0) {
        typedef void* (__thiscall* M)(void*, int);
        npc = (char*)((M)(*(void**)(*(char**)noun + 0xc)))(noun, 0x2e71a5a);
    } else {
        npc = 0;
    }
    void* old = *(void**)(self + 0x7d8);
    if (npc != old) {
        if (npc != 0) {
            typedef void(__thiscall* A)(void*);
            ((A)(*(void**)(*(char**)npc + 0)))(npc);
        }
        *(char**)(self + 0x7d8) = npc;
        if (old != 0) {
            typedef void(__thiscall* R)(void*);
            ((R)(*(void**)(*(char**)old + 4)))(old);
        }
    }

    void* glob = g_168df68;
    float fA;
    if (*(int*)(self + 0x714) == 3) fA = *(float*)((char*)glob + 0x20);
    else                          fA = *(float*)((char*)glob + 0x1c);
    float fB = *(float*)((char*)glob + 0x24);

    char* sp34 = self + 0x34;
    void* sub = *(void**)sp34;
    typedef float(__thiscall* G)(void*);
    float rr = ((G)(*(void**)((char*)sub + 0x34)))(sp34);

    ((Fn3f160*)(*(void**)(self + 0x7d8)))->f(rr * fA);
    ((Fn3f1b0*)(*(void**)(self + 0x7d8)))->f(fB, 3.402823466e+38F);
    ((Fn3f2d0*)(*(void**)(self + 0x7d8)))->f(self);

    float radius;
    if (bUniv0) radius = 0.0f;
    else        radius = (float)FUN_00b7e4d0(PlanetModel());

    void* tune = GetSpaceCombatTuning();
    int level = param_2;
    if (level == -1) {
        void* empire = ctx;
        if (empire != 0) {
            level = FUN_00c317a0(empire);
        } else {
            if (GetSpaceCombatTuning() != 0 && FUN_01021240() != 0) {
                void* cities = (void*)(int)FUN_01021240();
                float* c = FUN_005c65e0(cities);
                float v0 = c[0], v1 = c[1], v2 = c[2];
                level = FUN_0102a360(GetSpaceCombatTuning(), &v0, &v1, &v2);
            } else {
                level = 0;
            }
        }
    }

    float hp = FUN_0102a630(tune, param_3, level);
    *(float*)(self + 0x534) = hp;
    *(float*)(self + 0x540) = hp;
    *(int*)(self + 0x7fc) = level;
    ((Fn385d0*)self)->f();

    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = gF_142eae0;
    v[3] = 0.0f;
    ((Fn3dae0*)self)->f(v);

    int t = *(int*)(self + 0x714) - 1;
    switch (t) {
    case 0:  // 0x00c3dd6e
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x6170e8b, param_3, self + 0x7a0);
        FUN_00c3a220(0x6170e8d, param_3, self + 0x794);
        *(uint8_t*)(self + 0x690) = 1;
        return;
    case 1:  // 0x00c3ddca
        *(float*)(self + 0x768) = (float)(FUN_0059da80(gF_13eecd8) + (double)radius) + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x578e8f0, param_3, self + 0x798);
        FUN_00c3a220(0x616df37, param_3, self + 0x79c);
        FUN_00c3a220(0x616df39, param_3, self + 0x7a0);
        FUN_00c3a220(0x578ec56, param_3, self + 0x794);
        return;
    case 2:  // 0x00c3de4f
        *(float*)(self + 0x768) = (float)(FUN_0059da80(gF_1473c70) + (double)radius) + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        {
            void* tool = FUN_00c463d0(self + 0x7a4);
            FUN_00b3d390((void*)0x168e0a4, tool);
        }
        return;
    case 3:  // 0x00c3dea6
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        FUN_00c3a220(0x578f417, param_3, self + 0x798);
        FUN_00c3a220(0x6170e66, param_3, self + 0x79c);
        FUN_00c3a220(0x6170e68, param_3, self + 0x7a0);
        FUN_00c3a220(0x6171707, param_3, self + 0x794);
        return;
    case 4:  // 0x00c3df1f
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        ((Fn3a2b0*)self)->f((int)ctx);
        return;
    case 5:  // 0x00c3df59
        {
            void* tool = FUN_00c463d0(self + 0x798);
            FUN_00b3d390((void*)0x168e230, tool);
        }
        return;
    case 6:  // 0x00c3df80
        if ((int)ctx == 2) *(int*)(self + 0x76c) = 2;
        ((Fn3a2b0*)self)->f((int)ctx);
        return;
    case 7:  // 0x00c3dfa1
        FUN_00c3a220(0x578e8f0, param_3, self + 0x798);
        *(float*)(self + 0x768) = radius + gF_13f7670;
        ((Fn3be70*)self)->f(self + 0x750);
        return;
    default:
        return;
    }
}
