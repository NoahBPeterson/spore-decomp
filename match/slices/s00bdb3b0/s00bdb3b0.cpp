// match/slices/s00bdb3b0/s00bdb3b0.cpp
// Slice s00bdb3b0 -- SPGonzago / SPGameNounManager: the SP::cCity "urban center"
// helper cluster.  Every function takes `this` in ecx (retail `mov esi,ecx` /
// `[ecx+N]`), so the whole set is modelled as __thiscall members of one stub
// struct carrying the retail field offsets and the vtable slots the disassembly
// addresses.  Callees without a name are declared (never defined) so a real
// `call rel32` is emitted and MSVC cannot fold them away; each callee's calling
// convention is taken from its own `ret N`.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /Isrc/game/include
#include <math.h>

typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// Free / singleton callees (__cdecl unless noted)
// ---------------------------------------------------------------------------
void* __cdecl SP_NounManager();                        // 0x00b3d300
void* __stdcall SP_PlanetModel(int model);             // 0x00b3d350 ret 4
void* __stdcall SP_PlanetModel0();                     // 0x00b3d350 (no-arg alias)
void* __stdcall SP_PlanetModel1(float* pos);           // 0x00b3d350 (pos alias)
void* __cdecl FUN_00b3d240();                          // 0x00b3d240
void* __cdecl SP_PropertyManager();                    // 0x0067de30
void* __cdecl SP_EffectsManager();                     // 0x0067ddd0
void* __cdecl FUN_01021260();                          // 0x01021260 GetActivePlanet
void* __stdcall FUN_01021260a(void* a);                // 0x01021260 (arg alias) ret 4
void* __stdcall SP_GetMissionManager(void* a);         // 0x00feb9f0 ret 4
u8    __cdecl FUN_00fedea0(void* a, void* b);          // 0x00fedea0 (placeholder, unused)
void* __cdecl SP_GetCurrentGameMode();                 // 0x00b5b800
void* __stdcall SP_SpaceGameGet(int a);                // 0x01002bd0 ret 4
void* __stdcall FUN_01005180(int a);                   // 0x01005180 ret 4
void* __cdecl SP_GetSpaceCombatTuning();               // 0x01029940
void* __cdecl FUN_00ff2810(void* a, void* b);          // 0x00ff2810 ret 8
void  __stdcall FUN_00bed3c0(void* out);               // 0x00bed3c0 ret 4
void* __cdecl FUN_00bda200(void* out, int a, int b);   // 0x00bda200 ret 0xc
float __cdecl SP_GetPropertyAsFloat();                 // 0x0041ea70 ret 0
void  __cdecl XformMsg_ctor(void* p);                  // 0x00434040 ret 0
int* __cdecl SP_Matrix3FromQuaternion(void* out, void* q); // 0x0059c190 ret 8
void  __cdecl operator_delete(void* p);                // 0x00f47380 ret 4
u8    __stdcall FUN_00bec190(void* out);               // 0x00bec190 ret 4
int   __cdecl FUN_00bd8b80(void* self);                // 0x00bd8b80 ret 0
u8    __cdecl FUN_00bd7e20(void* self);                // 0x00bd7e20 ret 0
u8    __cdecl FUN_00bda000(void* self, int a);         // 0x00bda000 ret 4
void  __cdecl FUN_00a04c80(void* self, int a);         // 0x00a04c80 ret 4
void  __cdecl FUN_00a047d0(void* self, int a);         // 0x00a047d0 ret 4

extern void* g_16dc798;                                // 0x016dc798 gSimUniverse

struct MissionMgrStub {
    u8 DoMissionsPreventHostility(void* b);            // 0x00fedea0 ret 4
};

struct XformMsg {
    XformMsg();
    char m[0x24];
};

struct SimGameStub {
    void* f5180();                                     // 0x01005180 ret 0
};

// ---------------------------------------------------------------------------
// Callee stubs -- calling convention from each callee's own `ret N`.
// ---------------------------------------------------------------------------
struct NounMgrStub {
    void* FUN_00b25f40(int id);                        // 0x00b25f40 ret 4
    void* FUN_00b25ca0();                              // 0x00b25ca0 GetCivilizationList ret 0
    void* FUN_00b25fb0();                              // 0x00b25fb0 GetPlayerCivilization ret 0
};

struct ActivePlanetStub {
    void* FUN_00c71e30();                              // 0x00c71e30 ret 0
    char pad04[0x13c - 0x04];
    int   m13c;                                        // +0x13c
};

struct DamageStub {
    int FUN_008e7f80();                                // 0x008e7f80 GetDamageState ret 0
};

struct ActionCircleStub {
    void* FUN_00af9ff0(u32 slot);                      // 0x00af9ff0 SlotAt ret 4
    char bytes[0x28];                                  // real cActionCircle extent
};

struct SlotObjStub {
    void* FUN_00fcc210();                              // 0x00fcc210 ret 0
};

struct PropObjStub {
    void** vt;                                         // +0x00 (+0x04, +0x0c, +0x18, +0x24, +0x2c, +0x30)
};

struct ToolMgrStub {
    void UseToolStart(void* slot, float* pos, int a, int b, int c, int d);
};

void* __cdecl SP_RelationshipManager();                // 0x00b3d2c0

struct CivStub {
    int* FUN_00bf9770(int key);                        // 0x00bf9770 GetModelTypeKey ret 4
    void FUN_00bf9780(int key);                        // 0x00bf9780 ret 4
    void FUN_00bef830();                               // 0x00bef830 ret 0
    int  FUN_00bef950();                               // 0x00bef950 ret 0
    void* FUN_00bf1780(int a);                         // 0x00bf1780 ret 4
    void** vt;                                         // +0x00
    char pad04[0x298 - 0x04];
    int  m298;                                         // +0x298
};

struct TimerStub {
    void FUN_00bc3110();                               // 0x00bc3110 Stop
    void FUN_00bc3130();                               // 0x00bc3130 Restart
    u64  FUN_00bc3190();                               // 0x00bc3190 GetElapsedTime
};

struct PlanetObjStub {
    void* FUN_00b81630();                              // 0x00b81630 ret 0
    float FUN_00b83620();                              // 0x00b83620 ret 0
};

struct Tuning2Stub {
    float FUN_01029b90();                              // 0x01029b90 GetCityAngerTime ret 0
};

struct SimUniverseStub {
    void FUN_01014a80(int a, int b);                   // 0x01014a80 AdjustAwareness ret 8
};

struct RefObj3 {
    void AddRef();                                     // 0x00a02c30 (cAnimatingCreature)
    void Release();                                    // 0x00a05270
};

// ---------------------------------------------------------------------------
// The stub class shared by all 15 members.
// ---------------------------------------------------------------------------
struct CStub {
    void** vt;                                         // +0x00
    char pad04[0x70 - 0x04];
    u8*  m70;                                          // +0x70 point-vector begin
    u8*  m74;                                          // +0x74 point-vector end
    char pad78[0x120 - 0x78];
    void* m120;                                        // +0x120 transform sub-object
    char pad124[0x220 - 0x124];
    float m220;                                        // +0x220 anger timer
    char pad224[0x274 - 0x224];
    u8   m274[0x14];                                   // +0x274 byte grid
    char pad288[0x2f0 - 0x288];
    void* m2f0;                                        // +0x2f0
    char pad2f4[0x304 - 0x2f4];
    float m304;                                        // +0x304
    char pad308[0x320 - 0x308];
    void* m320;                                        // +0x320
    void* m324;                                        // +0x324 zone
    char pad328[0x32c - 0x328];
    float m32c;                                        // +0x32c
    float m330;                                        // +0x330
    float m334;                                        // +0x334
    char pad338[0x340 - 0x338];
    int* m340;                                         // +0x340 map begin
    int* m344;                                         // +0x344 map end
    char pad348[0x354 - 0x348];
    int* m354;                                         // +0x354 vector begin
    int* m358;                                         // +0x358 vector end
    char pad35c[0x3ec - 0x35c];
    ActionCircleStub m3ec;                             // +0x3ec civic-object layout
    char pad414[0x508 - 0x414];    void* m508;                                        // +0x508
    char pad50c[0x53c - 0x50c];
    float m53c;                                        // +0x53c
    int   m540;                                        // +0x540
    char pad544[0x590 - 0x544];
    CivStub* m590;                                     // +0x590 civilization
    char pad594[0x640 - 0x594];
    int   m640;                                        // +0x640
    int   m644;                                        // +0x644
    u8    m648;                                        // +0x648
    char pad649[0x764 - 0x649];
    void* m764;                                        // +0x764 cAnimatingCreature
    char pad768[0x790 - 0x768];
    TimerStub m790;                                    // +0x790 cSPTimer
    int   m7b0;                                        // +0x7b0 effect id
    int   m7b4;                                        // +0x7b4 effect id

    void  FUN_00bdb3b0(int a, int b);                  // 0x00bdb3b0 ret 8
    u8    FUN_00bdb470(int key);                       // 0x00bdb470 ret 4
    int   FUN_00bdb590(int* key, int* out);            // 0x00bdb590 ret 8
    void  FUN_00bdb7f0(int obj, int kind);             // 0x00bdb7f0 ret 8
    u8    FUN_00bdb880(int spec);                      // 0x00bdb880 ret 4
    u8    FUN_00bdb930(int spec, int arg);             // 0x00bdb930 ret 8
    float FUN_00bdb960();                              // 0x00bdb960
    float FUN_00bdba80();                              // 0x00bdba80
    void  FUN_00bdbaa0();                              // 0x00bdbaa0
    void  FUN_00bdbbb0();                              // 0x00bdbbb0
    void  FUN_00bdbc20(int* flag);                     // 0x00bdbc20 ret 4
    void  FUN_00bdbe50();                              // 0x00bdbe50
    void  FUN_00bdbf10();                              // 0x00bdbf10
    void  FUN_00bdc050();                              // 0x00bdc050
    void  FUN_00bdc1a0(int kind, int param);           // 0x00bdc1a0 ret 8
    void  FUN_00bd9dd0();                              // 0x00bd9dd0 ret 0 (callee, ecx=this)
};

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern float g_168bd70;                                // 0x0168bd70
extern float g_168bd74;                                // 0x0168bd74
extern float g_168bd78;                                // 0x0168bd78
extern float g_14853bc;                                // 0x014853bc 30.0f
extern float g_1473c70;                                // 0x01473c70 10.0f
extern float g_13f4fd0;                                // 0x013f4fd0 4294967296.0f
extern float g_1485720;                                // 0x01485720 1.0f
extern float g_1486110;                                // 0x01486110 5.0f
extern float g_1488874;                                // 0x01488874 0.1f
extern float g_13eb8b0;                                // 0x013eb8b0 sign bit
extern float g_13ebc4c;                                // 0x013ebc4c
extern float g_1468468;                                // 0x01468468 4.0f
extern float g_13f9428;                                // 0x013f9428 0.001f
extern float g_13ebc68;                                // 0x013ebc68 18.0f
extern float g_13ec4b8;                                // 0x013ec4b8 1e-08f
extern float g_13ef580;                                // 0x013ef580 0.02f
extern float g_146869c[4];                             // 0x0146869c
extern float g_168c330;                                // 0x0168c330 matrix source
extern float g_168c354;                                // 0x0168c354
extern float g_168c358;                                // 0x0168c358
extern float g_168c35c;                                // 0x0168c35c
extern float g_168c3ac;                                // 0x0168c3ac
extern float g_168c3b0;                                // 0x0168c3b0
extern int   g_168c3b4;                                // 0x0168c3b4
extern void* g_168bda0;                                // 0x0168bda0
extern void* g_1654c04;                                // 0x01654c04 game-mode token
extern void* g_1654c05;                                // 0x01654c05 game-mode token
extern void* g_156e16c;                                // 0x0156e16c resource key

struct RelMgrStub {
    void FUN_00d06240(int a, int b, int c);            // 0x00d06240 RecordEvent ret 0xc
};

static inline void* vtp(void* o) { return *(void**)o; }
static inline char* vpt(void* o) { return *(char**)o; }

struct Matrix33Ctor {
    void FUN_0041cb40(void* src);                      // 0x0041cb40 ret 4
};

// cSPTimer member helpers (the timer's vtable lives at +0x00).
static inline void  timerRestart(void* p) { ((TimerStub*)p)->FUN_00bc3130(); }
static inline void  timerStop(void* p)    { ((TimerStub*)p)->FUN_00bc3110(); }
static inline u64   timerElapsed(void* p) { return ((TimerStub*)p)->FUN_00bc3190(); }
static inline void* nounMgr()             { return SP_NounManager(); }

// ===========================================================================
// @ 0x00bdb3b0
// ===========================================================================
void CStub::FUN_00bdb3b0(int a, int b)
{
    m648 = 1;
    m640 = a;
    m644 = b;
    if (SP_GetCurrentGameMode() == &g_1654c04) {
        CivStub* civ = m590;
        if (b == 0 ||
            (**(u8(__thiscall**)(void*))(vpt((void*)(b + 0x34)) + 0x58))(*(void**)(b + 0x34)) == 0) {
            if ((**(u8(__thiscall**)(void*))(vpt(m120) + 0x58))((char*)this + 0x120) != 0) {
                void* p = (**(void*(__thiscall**)(void*))(vpt((void*)(b + 0x508)) + 0x10))(*(void**)(b + 0x508));
                void* r = ((NounMgrStub*)nounMgr())->FUN_00b25f40((int)p);
                if (a == 0 && r != 0)
                    ((CivStub*)r)->FUN_00bef830();
            }
        } else if (a == 0 && civ != 0) {
            void* pl = ((NounMgrStub*)nounMgr())->FUN_00b25fb0();
            if (civ != pl)
                civ->FUN_00bef830();
        }
    }
}

// ===========================================================================
// @ 0x00bdb470
// ===========================================================================
u8 CStub::FUN_00bdb470(int key)
{
    int i = 0;
    if (key == 0x436f315) {
        int n = (int)((char*)m358 - (char*)m354) >> 2;
        if (n > 0) {
            do {
                int obj = (int)m354[i];
                void* c = obj ? (void*)(obj + 0x588) : 0;
                if (((DamageStub*)c)->FUN_008e7f80() == 2) {
                    (**(void(__thiscall**)(void*, int))(vpt(c) + 0x2c))(c, 0);
                    if (m2f0 == 0)
                        return 1;
                    ActivePlanetStub* pl = (ActivePlanetStub*)FUN_01021260();
                    FUN_00ff2810(this, (void*)pl->m13c);
                    return 1;
                }
                ++i;
            } while (i < n);
        }
    } else {
        int n = (int)((char*)m344 - (char*)m340) >> 2;
        if (n > 0) {
            do {
                void* p = (void*)m340[i];
                if ((**(int(__thiscall**)(void*))(vpt(p) + 0x38))(p) == key &&
                    ((DamageStub*)((char*)p + 0x120))->FUN_008e7f80() == 2) {
                    (**(void(__thiscall**)(void*, int))(vpt((char*)p + 0x120) + 0x2c))((char*)p + 0x120, 0);
                    if (m2f0 == 0)
                        return 1;
                    ActivePlanetStub* pl = (ActivePlanetStub*)FUN_01021260();
                    FUN_00ff2810(this, (void*)pl->m13c);
                    return 1;
                }
                ++i;
            } while (i < n);
        }
    }
    return 0;
}

// ===========================================================================
// @ 0x00bdb590
// ===========================================================================
int CStub::FUN_00bdb590(int* key, int* out)
{
    int best = 0;
    int bestScore = 0;
    int slotIdx = 0;
    int flag = 0;
    for (;;) {
        void* slot = m3ec.FUN_00af9ff0((u32)slotIdx);
        if (slot != 0) {
            void* prop = ((SlotObjStub*)slot)->FUN_00fcc210();
            if (prop != 0) {
                void* sub = (**(void*(__thiscall**)(void*, int))(vpt(prop) + 0xc))(prop, 0xe9cb8ba);
                if (sub != 0 && ((DamageStub*)((char*)sub + 0x120))->FUN_008e7f80() != 2)
                    goto nextSlot;
            }
            if (FUN_00bda000(this, slotIdx)) {
                int score = 0;
                for (u32 j = 0; j < 0xe; ++j) {
                    int cur = score;
                    if ((u32)slotIdx != j) {
                        int base = (**(int(__thiscall**)(CStub*))(vpt(this) + 0x6c))(this);
                        if (((u8*)(flag + base + 0x274))[j] != 0) {
                            void* s2 = m3ec.FUN_00af9ff0(j);
                            if (s2 != 0) {
                                void* p2 = ((SlotObjStub*)s2)->FUN_00fcc210();
                                if (p2 != 0) {
                                    void* sub2 = (**(void*(__thiscall**)(void*, int))(vpt(p2) + 0xc))(p2, 0xe9cb8ba);
                                    if (sub2 != 0) {
                                        int mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                        if (key == (int*)0x18ea2cc) {
                                            if (mt != 0x18eb106) {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt != 0x18ea1eb) {
                                                    mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                    if (mt == 0x1a56aba)
                                                        cur = score - 10;
                                                    goto store;
                                                }
                                            }
                                            if (FUN_00bd8b80(this))
                                                cur = score + 50;
                                            else
                                                cur = score + 80;
                                        } else if (key == (int*)0x1a56aba) {
                                            if (mt != 0x18eb106) {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt != 0x18ea1eb) {
                                                    mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                    if (mt == 0x18ea2cc)
                                                        cur = score - 10;
                                                    goto store;
                                                }
                                            }
                                            cur = score + (0x5a - (int)m304);
                                            if (FUN_00bd7e20(this))
                                                cur += 0x14;
                                        } else if (key == (int*)0x18eb106) {
                                            if (mt == 0x18ea2cc) {
                                                if (FUN_00bd8b80(this))
                                                    cur = score + 50;
                                                else
                                                    cur = score + 80;
                                            } else {
                                                mt = (**(int(__thiscall**)(void*))(vpt(sub2) + 0x20))(sub2);
                                                if (mt == 0x1a56aba) {
                                                    cur = score + (0x5a - (int)m304);
                                                    if (FUN_00bd7e20(this))
                                                        cur += 0x14;
                                                }
                                            }
                                        }
                                    }
                                    if (key == (int*)0x18eb106)
                                        cur = score + 10;
                                }
                            }
                        }
                    }
                store:
                    score = cur;
                }
                if (bestScore < score) {
                    bestScore = score;
                    best = (int)slot;
                }
            }
        }
    nextSlot:
        flag += 0xe;
        ++slotIdx;
        if ((u32)flag >= 0xc4) {
            if (out)
                *out = bestScore;
            return best;
        }
    }
}

// ===========================================================================
// @ 0x00bdb7f0
// ===========================================================================
void CStub::FUN_00bdb7f0(int obj, int kind)
{
    int model;
    if (kind < 0xff10522) {
        if (kind == 0x1a55e4d) {
            model = 0x72c49181;
            goto have;
        }
        if (kind == 0xecade42) {
            model = 0x47c10953;
            goto have;
        }
    } else if (kind == 0x1007ae63) {
        model = 0x99e92f05;
        goto have;
    }
    model = 0x4e3f7777;
have:
    CivStub* civ = m590;
    if (civ != 0) {
        if (*civ->FUN_00bf9770(model) == 0)
            civ->FUN_00bf9780(model);
        void* v = *(void**)(obj + 0x34);
        void* base = (char*)obj + 0x34;
        (**(void(__thiscall**)(void*, int*))(vpt(v) + 0x94))(base, civ->FUN_00bf9770(model));
    }
}

// ===========================================================================
// @ 0x00bdb880
// ===========================================================================
u8 CStub::FUN_00bdb880(int spec)
{
    switch (spec) {
    case 2:
        return m590->m298 >= 3;
    case 1:
        if ((m32c != g_168bd70 || m330 != g_168bd74 || m334 != g_168bd78) &&
            m590->m298 >= 2)
            return 1;
        return 0;
    case 0:
        return m590->m298 >= 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00bdb930
// ===========================================================================
u8 CStub::FUN_00bdb930(int spec, int arg)
{
    if (spec == 4)
        return 1;
    if (spec == -1)
        return 0;
    if (m540 != spec)
        return 0;
    return FUN_00bdb880(arg);
}

// ===========================================================================
// @ 0x00bdb960
// ===========================================================================
float CStub::FUN_00bdb960()
{
    float fBase = 10.0f;
    float fPer = 30.0f;
    PropObjStub* prop = 0;
    void* pm = SP_PropertyManager();
    if ((**(u8(__thiscall**)(void*, int, PropObjStub**))(vpt(pm) + 0x30))(pm, 0x6b3f727b, &prop) != 0
        && prop != 0) {
        int* got;
        if ((**(u8(__thiscall**)(PropObjStub*, int, int**))(vpt(prop) + 0x24))(prop, 0x39d48e7, &got) != 0
            && *(short*)((char*)got + 0x12) == 0xd)
            fBase = *(float*)got;
        if ((**(u8(__thiscall**)(PropObjStub*, int, int**))(vpt(prop) + 0x24))(prop, 0x78aeaf4b, &got) != 0
            && *(short*)((char*)got + 0x12) == 0xd)
            fPer = *(float*)got;
    }
    int n = (int)((char*)m344 - (char*)m340) >> 2;
    float f = (float)n * fPer + fBase;
    if (prop)
        (**(void(__thiscall**)(PropObjStub*))(vpt(prop) + 4))(prop);
    return f;
}

// ===========================================================================
// @ 0x00bdba80
// ===========================================================================
float CStub::FUN_00bdba80()
{
    return FUN_00bdb960() * sqrtf(m53c + 1.0f);
}

// ===========================================================================
// @ 0x00bdbaa0
// ===========================================================================
void CStub::FUN_00bdbaa0()
{
    int cnt = (int)((m74 - m70) / 0x14);
    if ((u32)cnt < 4)
        return;
    if (m324 == 0)
        return;
    void* pts = 0;
    FUN_00bed3c0(&pts);
    int* src = (int*)pts;
    int* dst = (int*)m70;
    for (int g = 0; g < 4; ++g) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        *(float*)(dst + 3) = 5.0f;
        src += 3;
        dst += 5;
    }
    if (pts != 0 && *((int*)pts - 1) != 0)
        operator_delete(pts);
}

// ===========================================================================
// @ 0x00bdbbb0
// ===========================================================================
void CStub::FUN_00bdbbb0()
{
    float acc = 0.0f;
    for (int i = 10; i != 0; --i) {
        float f = FUN_00bdb960();
        float tmp[3];
        int m = (**(int(__thiscall**)(CStub*, float*, float))(vpt(this) + 0x5c))(this, tmp, f);
        PlanetObjStub* pl = (PlanetObjStub*)SP_PlanetModel(m);
        acc += pl->FUN_00b83620();
    }
    m53c = acc * 0.1f;
}

// ===========================================================================
// @ 0x00bdbc20
// ===========================================================================
void CStub::FUN_00bdbc20(int* flag)
{
    if (m764 != 0) {
        FUN_00bd9dd0();
        return;
    }
    timerRestart(&m790);
    void* sp = FUN_00b3d240();
    void* a = (**(void*(__thiscall**)(void*))(vpt(sp) + 0x74))(sp);
    if (*flag == 0)
        flag = (int*)(m590->FUN_00bef950() + 0x504);
    void* cr = (**(void*(__thiscall**)(void*, int*, int, void*, void*, int))(vpt(a) + 0x30))
        (a, flag, 2, &g_168bd70, &g_156e16c, 1);
    void* old = m764;
    if (cr != old) {
        if (cr)
            ((RefObj3*)cr)->AddRef();
        m764 = cr;
        if (old)
            ((RefObj3*)old)->Release();
    }
    if (m764 != 0) {
        FUN_00a04c80(m764, 6);
        void* c = m764;
        void* p1 = (**(void*(__thiscall**)(void*))(vpt(m320) + 0x2c))((char*)m320 + 0x34);
        *(float*)((char*)c + 4) = ((float*)p1)[0];
        *(float*)((char*)c + 8) = ((float*)p1)[1];
        *(float*)((char*)c + 0xc) = ((float*)p1)[2];
        void* q = (**(void*(__thiscall**)(void*))(vpt(m320) + 0x30))((char*)m320 + 0x34);
        float* qf = (float*)q;
        c = m764;
        *(float*)((char*)c + 0x10) = qf[1];
        *(float*)((char*)c + 0x14) = -qf[0];
        *(float*)((char*)c + 0x18) = qf[3];
        *(float*)((char*)c + 0x1c) = -qf[2];
        *(float*)((char*)m764 + 0x3c) = 60.0f;
        float* civ = (float*)((char*)m590 + 0xc4);
        void* cc = m764;
        *(float*)((char*)cc + 0x74) = civ[0];
        *(float*)((char*)cc + 0x78) = civ[1];
        *(float*)((char*)cc + 0x7c) = civ[2];
        *(float*)((char*)cc + 0x80) = 1.0f;
        int e1 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 8))(m764, 0x8bff672a, 0);
        m7b0 = e1;
        (**(void(__thiscall**)(void*, int, int))(vpt(m764) + 0xc))(m764, e1, 1);
        (**(void(__thiscall**)(void*, int))(vpt(m764) + 0x18))(m764, e1);
        int e2 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 4))(m764, 0x8ff6177c, 0);
        (**(void(__thiscall**)(void*, int, int))(vpt(m764) + 0x24))(m764, e2, *(int*)&g_1468468);
        int e3 = (**(int(__thiscall**)(void*, int, int))(vpt(m764) + 4))(m764, 0x64be2be, 0);
        m7b4 = e3;
        FUN_00a047d0(m764, 1);
    }
}

// ===========================================================================
// @ 0x00bdbe50
// ===========================================================================
void CStub::FUN_00bdbe50()
{
    if (m764 != 0) {
        u64 t = timerElapsed(&m790);
        float f = (float)t * 0.001f;
        if ((g_168c3b4 & 1) == 0) {
            g_168c3b4 |= 1;
            g_168c3b0 = 18.0f;
        }
        if ((g_168c3b4 & 2) == 0) {
            g_168c3b4 |= 2;
            g_168c3ac = g_168c3b0 - 4.0f;
        }
        if (f > g_168c3b0)
            FUN_00bd9dd0();
    }
}

// ===========================================================================
// @ 0x00bdbf10
// ===========================================================================
void CStub::FUN_00bdbf10()
{
    if (((MissionMgrStub*)SP_GetMissionManager(FUN_01021260()))->DoMissionsPreventHostility(&g_168bda0))
        return;
    if (SP_GetCurrentGameMode() == &g_1654c05) {
        ((SimGameStub*)SP_SpaceGameGet(0x13))->f5180();
        if (m220 <= 0.0f) {
            PropObjStub* eff = 0;
            void* em = SP_EffectsManager();
            u8 found = (**(u8(__thiscall**)(void*, int, int, PropObjStub**))(vpt(em) + 0x2c))(em, 0x4dbd616, 0, &eff);
            if (found) {
                XformMsg msg;
                XformMsg_ctor(&msg);
                void* pos = 0;
                FUN_00bec190(&pos);
                *(u16*)msg.m |= 4;
                ++*(u16*)(msg.m + 2);
                *(void**)(msg.m + 4) = *(void**)pos;
                *(void**)(msg.m + 8) = *((void**)pos + 1);
                *(void**)(msg.m + 0xc) = *((void**)pos + 2);
                (**(void(__thiscall**)(PropObjStub*, void*))(vpt(eff) + 0x18))(eff, msg.m);
                (**(void(__thiscall**)(PropObjStub*, int))(vpt(eff) + 8))(eff, 0);
            }
            void* ap = FUN_01021260();
            if (ap != 0) {
                void* sub = ((ActivePlanetStub*)ap)->FUN_00c71e30();
                if (sub != 0)
                    ((SimUniverseStub*)g_16dc798)->FUN_01014a80(*(int*)((char*)sub + 0x84), 0);
            }
            if (eff)
                (**(void(__thiscall**)(PropObjStub*))(vpt(eff) + 4))(eff);
        }
    }
    m220 = ((Tuning2Stub*)SP_GetSpaceCombatTuning())->FUN_01029b90();
}

// ===========================================================================
// @ 0x00bdc050
// ===========================================================================
void CStub::FUN_00bdc050()
{
    PropObjStub* eff = 0;
    void* em = SP_EffectsManager();
    u8 found = (**(u8(__thiscall**)(void*, int, PropObjStub**))(vpt(em) + 0x2c))(em, 0x3d6fa45, &eff);
    if (!found)
        return;
    char buf[0x50];
    *(float*)(buf + 0x0c) = g_168c354;
    *(float*)(buf + 0x10) = g_168c358;
    *(float*)(buf + 0x14) = g_168c35c;
    *(u16*)(buf + 0x00) = 0;
    *(float*)(buf + 0x18) = 1.0f;
    ((Matrix33Ctor*)(buf + 0x1c))->FUN_0041cb40(&g_168c330);
    void* tr = (**(void*(__thiscall**)(void*))(vpt(m120) + 0x2c))((char*)this + 0x120);
    *(float*)(buf + 0x10) = ((float*)tr)[0];
    *(float*)(buf + 0x14) = ((float*)tr)[1];
    *(float*)(buf + 0x18) = ((float*)tr)[2];
    *(u16*)(buf + 0x0c) |= 4;
    ++*(u16*)(buf + 0x0e);
    void* q = (**(void*(__thiscall**)(void*))(vpt(m120) + 0x30))((char*)this + 0x120);
    float m[9];
    int* r = SP_Matrix3FromQuaternion(m, q);
    for (int i = 0; i < 9; ++i)
        ((int*)(buf + 0x1c))[i] = r[i];
    *(u16*)(buf + 0x14) |= 2;
    ++*(u16*)(buf + 0x16);
    float f = FUN_00bdb960() * g_13ef580;
    ++*(u16*)(buf + 0x02);
    *(float*)(buf + 0x1c) = f;
    (**(void(__thiscall**)(PropObjStub*, char*))(vpt(eff) + 0x18))(eff, buf);
    (**(void(__thiscall**)(PropObjStub*, int))(vpt(eff) + 8))(eff, 0);
    if (eff)
        (**(void(__thiscall**)(PropObjStub*))(vpt(eff) + 4))(eff);
}

// ===========================================================================
// @ 0x00bdc1a0
// ===========================================================================
void CStub::FUN_00bdc1a0(int kind, int param)
{
    void* tgt = m590->FUN_00bf1780(param);
    timerStop((char*)tgt + 0x88);
    float v[6];
    FUN_00bda200(v, kind, param);
    float len = 1.0f / sqrtf(v[0] * v[0] + (v[1] * v[1] + v[2] * v[2]) + g_13ec4b8);
    float scale = g_146869c[kind];
    float dx = scale * (len * v[0]);
    float dy = scale * (v[1] * len);
    float dz = scale * (v[2] * len);
    float pos[3];
    PlanetObjStub* pl = (PlanetObjStub*)SP_PlanetModel1(pos);
    float* base = (float*)pl->FUN_00b81630();
    pos[0] = base[0] + dx;
    pos[1] = base[1] + dy;
    pos[2] = base[2] + dz;
    float* circ = m320 ? (float*)((char*)m320 + 0x34) : 0;
    ((ToolMgrStub*)tgt)->UseToolStart(circ, pos, -1, 0, 0, 1);
    if (kind == 1) {
        void** list = (void**)((NounMgrStub*)nounMgr())->FUN_00b25ca0();
        void** begin = (void**)*list;
        int n = (int)((char*)list[1] - (char*)*list) >> 2;
        for (int i = 0; i < n; ++i) {
            void* civ = begin[i];
            if (civ == m590)
                continue;
            int id1 = (**(int(__thiscall**)(void*, int, int))(vpt(m590) + 0x4c))(m590, 0x5776d99, *(int*)&g_1485720);
            int id2 = (**(int(__thiscall**)(void*, int))(vpt(civ) + 0x4c))(civ, id1);
            ((RelMgrStub*)SP_RelationshipManager())->FUN_00d06240(id2, id1, *(int*)&g_1485720);
        }
    }
}
