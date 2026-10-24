// Slice s0102af80 - SP living-universe / allied-UFO / space-combat helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int       uint32_t;
typedef unsigned short     uint16_t;
typedef unsigned char      uint8_t;
typedef int                int32_t;
typedef unsigned long long uint64_t;

// virtual call: (*obj)->vtable[off]
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

// ---------------------------------------------------------------------------
// Free (__cdecl) callees.  Their call relocations are masked by the checker, so
// the exact symbol names do not affect matching; the calling shape does.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_01002bd0(void);          // SP::SpaceGameGet()
extern "C" void* __cdecl FUN_00ffbe50(void);          // SP::GetUFOSimulator()
extern "C" bool  __cdecl FUN_010299c0(void);          // SP::PlayerHasAnyAutoblaster
extern "C" void* __cdecl FUN_00b3d350(void);          // SP::PlanetModel()
extern "C" void* __cdecl FUN_00b3d300(void);          // SP::NounManager()
extern "C" void* __cdecl FUN_00b3d2a0(int);          // SP::StarManager()
extern "C" int   __cdecl FUN_01021080(void);          // cSPLivingUniverse::GetUniverseContext
extern "C" int   __cdecl FUN_01021090(void);          // cSPLivingUniverse::GetPlayerEmpireID
extern "C" void* __cdecl FUN_01021260(void);          // cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_010212a0(void);          // cSPLivingUniverse::GetActivePlanetRecord
extern "C" void* __cdecl FUN_01021300(void);          // cSPLivingUniverse::GetPlayerEmpire
extern "C" void* __cdecl FUN_01021240(void);          // cCivData / SP::GetCivData
extern "C" void* __cdecl FUN_0102acb0(int type, void* a, void* b);  // SP::CreateUFO
extern "C" void* __cdecl FUN_0102ac50(int type, void* globe);       // CreateUFOForSolarOrGalaxy
extern "C" bool  __cdecl FUN_0102aa50(void* t, void* self, void* p); // cSPSpaceCommCanTarget
extern "C" void* __cdecl FUN_010666a0(void*);
extern "C" void  __cdecl FUN_006a07d0(void* p, uint32_t prop, void* outCount, void* outArr);
extern "C" void  __cdecl FUN_006a12a0(void* p, uint32_t key, void* out);
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line);
extern "C" void  __cdecl FUN_00f47380(void*);
extern "C" uint32_t __cdecl FUN_011e0970(uint32_t lo, uint32_t hi, uint32_t b, uint32_t z);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// global state used by these functions
extern float DAT_016de6d4, DAT_016de6d8, DAT_016de6dc, DAT_016de6e0;
extern float DAT_016de6e4, DAT_016de6e8, DAT_016de6ec, DAT_016de6f0, DAT_016de6f4, DAT_016de6f8;
extern float DAT_016dc060[];
extern float DAT_0147c308, DAT_0147c310;
extern float DAT_01465544, DAT_01477fc0, DAT_01465160;
extern float DAT_0146e6d4;
extern float DAT_013ef54c, DAT_013ef53c;
extern float DAT_013ebc5c;
extern float DAT_0145c12c;
extern float DAT_013f56a4;
extern double DAT_01452f48, DAT_0140ebb0, DAT_014995a0;
extern int   DAT_015b7518;
extern int   DAT_018ebadc;
extern char  DAT_0149954c[];
extern char  DAT_014995a8[];
extern int   DAT_01601760;

// ---------------------------------------------------------------------------
// Generic thiscall receiver.  Every callee that takes its object in ECX is
// declared as a member here; the class name never reaches the target symbol.
// ---------------------------------------------------------------------------
class Obj {
public:
    void* F_inv();                                   // 0x00a1ad60 GetPlayerInventory
    void* F_sgd();                                   // 0x00bfc5f0 SetGameDataOwner2 -> owner
    int   F_42a0();                                  // 0x00fe42a0
    void* F_4bb0(int);                               // 0x01004bb0 f4bb0
    void  F_9a40(void*);                             // 0x01009a40
    void* F_8db30();                                 // 0x0108db30
    bool  F_cce0();                                  // 0x0104cce0
    bool  F_cdb0(void*);                             // 0x0104cdb0
    bool  F_8990(int);                               // 0x00c38990
    void  F_b500();                                  // 0x0106b500
    void  F_7b0(int, int);                           // 0x010027b0 AddPosseMember
    float* F_f70();                                  // 0x0041ea70 Property::GetFloat
    void  F_dstruct();                               // 0x00421cf0 ~MessageBasicRC
    void* F_a9370(int);                              // 0x00ba9370 GetEmpireByID
    int   F_17a0();                                  // 0x00c317a0 GetWeaponryLevel
    void* F_26b0();                                  // 0x00c326b0 GetUFOKey
    float* F_65e0();                                 // 0x005c65e0 GetCities
    int*  F_21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void* F_7d90();                                  // 0x00f67d90 GetCurrentTerrainSphere
    void  F_76790(int, int);                         // 0x00c76790
    char  F_784c0(int);                              // 0x00c784c0 TestPlayerWarVictory
    void  F_75520(int);                              // 0x00c75520 DoPlayerWarVictory
    void  F_e5430(int, int);                         // 0x00fe5430
    void* F_5d20(void*);                             // 0x00ff5d20 SpawnArtifact
    void* F_b1fdb0();                                // 0x00b1fdb0 GetAvatar
    void  F_81780(void*, void*, float, float);       // 0x00b81780 MakeRandomWorldPosition
    void* F_7f190(void*, void*);                     // 0x00b7f190 BuildSurfaceOrientation
    void  F_aa40(void*, void*);                      // 0x00c3aa40
    void  F_dae0(void*);                             // 0x00c3dae0
    void  F_be70(void*);                             // 0x00c3be70
    void  F_21b0(void*);                             // 0x00c421b0
    char  F_e040(void*);                             // 0x00b8e040
    void  F_9200(void*);                             // 0x00ac9200
    void  F_b810(unsigned, void*);                   // 0x00acb810
    void  F_f950(void*);                             // 0x00b5f950
    void  F_bfc470(int);                             // 0x00bfc470
    float F_06240(int, int, int, float);             // 0x00d06240 RecordEvent
    float F_2a230(int);                              // 0x0102a230 GetLootCityMinMoneyDrop
    float F_2a2a0(int);                              // 0x0102a2a0 GetLootCityMaxMoneyDrop
    float F_29f60(int);                              // 0x01029f60 GetLootMinMoneyDrop
    float F_29fd0(int);                              // 0x01029fd0 GetLootMaxMoneyDrop
    int   F_2a360(float, float, float);              // 0x0102a360 GetWeaponLevel
    uint64_t F_316c0();                              // 0x00b316c0 GameTimeManager::GetGameTime
};

// 0x1601760 - the shared EA random stream object.
class RLC {
public:
    uint32_t RandomUint32Uniform(uint32_t n);        // 0x00a68fb0
    double   RandomDoubleUniform();                  // 0x009360d0
};
extern RLC DAT_1601760;

// 0x15b7510 - the shared SP::cSPSpaceCombatTuning singleton.
extern Obj DAT_015b7510;

// address-taken call targets referenced as function objects
extern "C" void* __cdecl FUN_010666a0(void*);
extern "C" float* __cdecl FUN_0059aed0(void*, void*, void*);
extern "C" void  __cdecl FUN_00435ed0(uint32_t, void*);
extern "C" void* __cdecl FUN_00cd7d10(void);
extern "C" void* __cdecl FUN_00d3d420(void);
extern "C" void* __cdecl FUN_00ad48b0(void);
extern "C" void* __cdecl FUN_00b1e500(void);

// driver-only receivers
extern "C" void* __cdecl FUN_0067de30(void);         // PropertyManager
extern "C" void* __cdecl FUN_0067dcc0(void);         // MessageServer
extern "C" void* __cdecl FUN_00a206f0(void);         // Audio::GetSystemAT
extern "C" void* __cdecl FUN_00b3d2c0(void);         // RelationshipManager
extern "C" void* __cdecl FUN_00b3d380(void);         // GameTimeManager
extern "C" void  __cdecl FUN_01009a40(void*, void*);

// ===========================================================================
// 0x0102b140 - destroying destructor of a two-level refcount owner.
// ===========================================================================
class Owner01402 {
public:
    uint32_t vtbl;    // @0x00
    uint32_t pad04;   // @0x04
    uint32_t child;   // @0x08
    void* FUN_0102b140(uint8_t flags);
};

// @ 0x0102b140
void* Owner01402::FUN_0102b140(uint8_t flags) {
    this->vtbl = 0x1499570;
    _ReadWriteBarrier();
    uint32_t p = this->child;
    if (p != 0) {
        this->child = 0;
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    p = this->child;
    if (p != 0) {
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    this->vtbl = 0x1416f14;
    if ((flags & 1) != 0) {
        FUN_00f47380(this);
    }
    return this;
}

// ===========================================================================
// 0x0102b190 - SP::cSPSpaceCombatTuning::Init
// ===========================================================================
namespace SP {
struct cSPSpaceCombatTuning {
    uint32_t vtbl;    // @0x00
    uint32_t pad04;   // @0x04
    uint32_t prop;    // @0x08  AutoRefCount<cPropertyList>
    void Init();
};
}

// @ 0x0102b190
void SP::cSPSpaceCombatTuning::Init() {
    void* pm = FUN_0067de30();
    uint32_t p = this->prop;
    if (p != 0) {
        this->prop = 0;
        ((void(__thiscall*)(uint32_t))VF(p, 4))(p);
    }
    (*(void(__thiscall**)(void*, uint32_t, uint32_t, void*))(*(uint32_t*)pm + 0x2c))
        (pm, 0x9f9f0139, 0x2ae0c7e, &this->prop);
}

// ===========================================================================
// 0x0102af80 - true when the two refcount objects are alive and p2 validates.
// ===========================================================================
// ---------------------------------------------------------------------------
// A polymorphic receiver used where the original stored a pointer to a
// sub-object at +0x508 and dispatched through vtable slot 0x14.
// ---------------------------------------------------------------------------
class VObj {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void* v14();
};

// @ 0x0102af80
bool __cdecl FUN_0102af80(void* p1, void* p2) {
    if (p1 != 0) {
        if (((Obj*)p1)->F_cce0()) {
            if (((Obj*)p1)->F_cdb0(p2)) {
                return true;
            }
        }
    }
    bool result = false;
    ((Obj*)FUN_01002bd0())->F_inv();
    if (FUN_010299c0()) {
        void* v = ((VObj*)((char*)((Obj*)FUN_00ffbe50())->F_inv() + 0x508))->v14();
        if (v != 0) {
            if (((Obj*)v)->F_cce0()) {
                if (((Obj*)v)->F_cdb0(p2)) {
                    return true;
                }
            }
        }
        return false;
    }
    return result;
}

// ===========================================================================
// 0x0102b010 - SP::sGetNumUFOs
// ===========================================================================
// @ 0x0102b010
int __cdecl FUN_0102b010(void* p1, uint32_t param_2, uint32_t param_3) {
    int result = 0;
    if (p1 != 0) {
        int iVar4 = ((Obj*)((Obj*)FUN_01002bd0())->F_sgd())->F_42a0();
        int local_18, local_14, local_10, local_c;
        int local_8[2];
        int param_1;
        param_1 = 0;
        local_18 = 0;
        local_10 = 0;
        local_14 = 0;
        FUN_006a07d0(p1, param_2, &local_14, &local_10);
        if (local_14 == 0xb) {
            param_1 = *(int*)(local_10 + iVar4 * 4);
        }
        local_8[0] = 0;
        local_c = 0;
        FUN_006a07d0(p1, param_3, &local_c, local_8);
        if (local_c == 0xb) {
            local_18 = *(int*)(local_8[0] + iVar4 * 4);
        }
        local_8[1] = 0;
        int* pi = &param_1;
        if (param_1 < 1) {
            pi = &local_8[1];
        }
        int iVar1 = *pi;
        int* pi2 = &local_18;
        if (local_18 <= iVar1) {
            pi2 = &param_1;
        }
        result = DAT_1601760.RandomUint32Uniform((*pi2 - iVar1) + 1) + iVar1;
    }
    return result;
}

extern "C" float sinf(float);
extern "C" float cosf(float);
extern "C" float sqrtf(float);

// ===========================================================================
// 0x0102b620 - SP::AddAlliedUFOs
// ===========================================================================
// @ 0x0102b620
void __cdecl FUN_0102b620(void) {
    Obj* sg = (Obj*)FUN_01002bd0();
    char* list = (char*)((Obj*)FUN_00ffbe50())->F_8db30();
    char* p1 = *(char**)list;
    for (char* p2 = p1; p2 != list; p2 = *(char**)p2) {
    }
    for (; p1 != list; p1 = *(char**)p1) {
        void* r = sg->F_4bb0(*(int*)(p1 + 8));
        if (r == 0) {
            ((Obj*)FUN_00ffbe50())->F_7b0(*(int*)(p1 + 8), 0);
        } else {
            ((Obj*)FUN_010666a0(r))->F_b500();
        }
    }
}

// ===========================================================================
// 0x0102b4f0 - scatter a run of decorative allied UFOs around the planet.
// ===========================================================================
// @ 0x0102b4f0
void __cdecl FUN_0102b4f0(int param_1, void* param_2) {
    Obj* planet = (Obj*)FUN_00b3d350();
    void* inv = ((Obj*)FUN_00ffbe50())->F_inv();
    if (param_1 > 0) {
        int i = 0;
        do {
            void* ufo = FUN_0102acb0(0xb, DAT_0149954c, param_2);
            if (ufo != 0) {
                float pos[3];
                float scaled[3];
                char buf[16];
                planet->F_81780(pos, (char*)inv + 0x718, DAT_01477fc0, DAT_01465544);
                scaled[0] = pos[0] * DAT_013ef54c;
                scaled[1] = pos[1] * DAT_013ef54c;
                scaled[2] = pos[2] * DAT_013ef54c;
                void* u = planet->F_7f190(buf, pos);
                ((Obj*)ufo)->F_aa40(scaled, u);
                float f = (float)(i + 1) * DAT_0147c308;
                *(float*)((char*)ufo + 0x694) = DAT_016de6e4 * f;
                *(float*)((char*)ufo + 0x698) = DAT_016de6e8 * f;
                *(float*)((char*)ufo + 0x69c) = DAT_016de6ec * f;
            }
            i++;
        } while (i < param_1);
    }
}

// ===========================================================================
// 0x0102b690 - SP::CaptureStar
// ===========================================================================
struct MsgRC5 {
    uint32_t vtbl;      // @0x00
    uint32_t d0;        // @0x04
    uint32_t d8;        // @0x08
    uint32_t pad[9];    // @0x0c..0x2f
    uint32_t m30;       // @0x30
    uint32_t m34;       // @0x34
    uint32_t m38;       // @0x38
    void F_dstruct();   // 0x00421cf0
};

// @ 0x0102b690
bool __cdecl FUN_0102b690(int param_1, int param_2, uint32_t param_3) {
    int pid = FUN_01021090();
    bool bCaptured = false;
    if (param_1 != pid && param_2 == pid) {
        ((Obj*)FUN_00b3d2c0())->F_06240(param_1, param_2, 0x57b9100, 1.0f);
        Obj* te = (Obj*)((Obj*)FUN_00b3d300())->F_7d90();
        te->F_76790(param_2, param_1);
        char c = te->F_784c0(param_1);
        bCaptured = c != 0;
        if (bCaptured) {
            te->F_75520(param_1);
        }
        ((Obj*)((Obj*)FUN_01002bd0())->F_sgd())->F_e5430(0x1b, 1);
        MsgRC5 msg;
        msg.m30 = 0xf46092da;
        msg.vtbl = 0x13eb90c;
        msg.d0 = 0;
        msg.vtbl = 0x13eb844;
        msg.m38 = 0;
        msg.d8 = param_3;
        void* ms = FUN_0067dcc0();
        ((void(__thiscall*)(void*, uint32_t, void*, int))VF(ms, 0x14))(ms, 0xf46092da, &msg, 0);
        msg.F_dstruct();
    }
    return bCaptured;
}

// ===========================================================================
// 0x0102b780 - SP::AddHighLODUberTurretUFO
// ===========================================================================
// @ 0x0102b780
void __cdecl FUN_0102b780(void* param_1, float* param_2) {
    Obj* rec = *(Obj**)((char*)FUN_01021260() + 0x13c);
    if (rec->F_e040(param_1) == 0) {
        uint8_t rbuf[0x2c] = {0};
        *(void**)(rbuf + 0x00) = param_1;
        *(float*)(rbuf + 0x04) = param_2[0];
        *(float*)(rbuf + 0x08) = param_2[1];
        *(float*)(rbuf + 0x0c) = param_2[2];
        rbuf[0x28] = 1;
        uint32_t uVar1 = *(uint32_t*)((char*)rec + 0x138);
        if (uVar1 < *(uint32_t*)((char*)rec + 0x13c)) {
            *(uint32_t*)((char*)rec + 0x138) = uVar1 + 0x2c;
            if (uVar1 != 0) {
                ((Obj*)((char*)rec + 0x134))->F_9200(rbuf);
            }
        } else {
            ((Obj*)((char*)rec + 0x134))->F_b810(uVar1, rbuf);
        }
    }
    Obj* pm = (Obj*)FUN_0067de30();
    uint32_t prop = 0;
    if (prop != 0) {
        uint32_t t = prop;
        prop = 0;
        ((void(__thiscall*)(uint32_t))VF(t, 4))(t);
    }
    (*(void(__thiscall**)(void*, void*, uint32_t, void*))(*(uint32_t*)pm + 0x2c))
        (pm, param_1, 0x30608f0b, &prop);
    uint32_t key = 0;
    FUN_006a12a0((void*)prop, 0x4e3eca1, &key);
    int pe = *(int*)((char*)FUN_01021300() + 0x84);
    uint32_t key2 = 0;
    void* ufo = FUN_0102acb0(1, &pe, &key2);
    Obj* planet = (Obj*)FUN_00b3d350();
    float scaled[3];
    char buf[16];
    scaled[0] = param_2[0] * DAT_01465160;
    scaled[1] = param_2[1] * DAT_01465160;
    scaled[2] = param_2[2] * DAT_01465160;
    void* u = planet->F_7f190(buf, param_2);
    ((Obj*)ufo)->F_aa40(scaled, u);
    scaled[0] = param_2[0] * DAT_013f56a4;
    scaled[1] = param_2[1] * DAT_013f56a4;
    scaled[2] = param_2[2] * DAT_013f56a4;
    ((Obj*)ufo)->F_be70(scaled);
    float ang = (float)(DAT_1601760.RandomDoubleUniform() * 50.0);
    float clamped = 50.0f;
    if (ang < clamped) {
        clamped = ang;
        if (ang < 0.0f) {
            clamped = 0.0f;
        }
    }
    float a = clamped - 25.0f;
    *(float*)((char*)ufo + 0x694) = DAT_016de6f0 * a + DAT_016de6e4 * DAT_0147c308;
    *(float*)((char*)ufo + 0x698) = DAT_016de6f4 * a + DAT_016de6e8 * DAT_0147c308;
    *(float*)((char*)ufo + 0x69c) = DAT_016de6f8 * a + DAT_016de6ec * DAT_0147c308;
    float ang2 = (float)(DAT_1601760.RandomDoubleUniform() * 20.0 - 10.0);
    float clamped2 = 10.0f;
    if (ang2 < clamped2) {
        clamped2 = ang2;
        if (ang2 < -10.0f) {
            clamped2 = -10.0f;
        }
    }
    *(float*)((char*)ufo + 0x6ac) = clamped2;
    ((Obj*)((char*)ufo + 0x508))->F_bfc470(1);
}

// ===========================================================================
// 0x0102b1d0 - SP::AddHighLODAlliedUFO
// ===========================================================================
// @ 0x0102b1d0
int* __cdecl FUN_0102b1d0(void* param_1, int param_2, int param_3) {
    int ctx = FUN_01021080();
    int* piVar2;
    if (ctx == 0) {
        void* key = ((Obj*)param_1)->F_26b0();
        void* sp = *(void**)((char*)param_1 + 0x84);
        piVar2 = (int*)FUN_0102acb0(3, &sp, key);
        uint32_t q = (uint32_t)piVar2[0x1a3];
        if (q != 0) {
            piVar2[0x1a3] = 0;
            ((void(__thiscall*)(uint32_t))VF(q, 4))(q);
        }
        Obj* planet = (Obj*)FUN_00b3d350();
        void* u = (void*)((float*(__thiscall*)(void*, float, float))VF((char*)piVar2 + 0x34, 0x2c))
                             ((char*)piVar2 + 0x34, 40.0f, 100.0f);
        float pos[3];
        float scaled[3];
        char buf[16];
        planet->F_81780(pos, u, DAT_01477fc0, DAT_01465544);
        scaled[0] = pos[0] * DAT_013ef54c;
        scaled[1] = pos[1] * DAT_013ef54c;
        scaled[2] = pos[2] * DAT_013ef54c;
        void* u2 = planet->F_7f190(buf, pos);
        ((Obj*)piVar2)->F_aa40(scaled, u2);
        float f = ((float)param_2 / (float)param_3) * DAT_016de6d4 * 0.5f;
        float s = sinf(f);
        float c = cosf(f);
        float qf[4];
        qf[0] = s * DAT_016de6d8;
        qf[1] = s * DAT_016de6dc;
        qf[2] = s * DAT_016de6e0;
        qf[3] = c;
        char buf2[16];
        float* quat = FUN_0059aed0(buf2, &DAT_016de6e4, qf);
        piVar2[0x1a8] = *(int*)&quat[0];
        piVar2[0x1a9] = *(int*)&quat[1];
        piVar2[0x1aa] = *(int*)&quat[2];
        piVar2[0x1a5] = *(int*)&DAT_016dc060[param_2 * 3];
        piVar2[0x1a6] = *(int*)&DAT_016dc060[param_2 * 3 + 1];
        piVar2[0x1a7] = *(int*)&DAT_016dc060[param_2 * 3 + 2];
        piVar2[0x1ac] = param_2;
        ((void(__thiscall*)(void*, void*))VF(piVar2, 0x48))(piVar2, *(void**)((char*)param_1 + 0x84));
    } else {
        if ((uint32_t)(ctx - 1) > 1) {
            return 0;
        }
        piVar2 = (int*)FUN_0102ac50(3, param_1);
        int inv = (int)((Obj*)FUN_00ffbe50())->F_inv();
        piVar2[0x1a5] = *(int*)&DAT_016dc060[param_2 * 3];
        piVar2[0x1a6] = *(int*)&DAT_016dc060[param_2 * 3 + 1];
        int iVar1 = *(int*)&DAT_016dc060[param_2 * 3 + 2];
        piVar2[0x1ac] = param_2;
        piVar2[0x1a7] = iVar1;
        float f = ((float)param_2 / (float)param_3) * DAT_016de6d4 * 0.5f;
        float s = sinf(f);
        float c = cosf(f);
        float qf[4];
        qf[0] = s * DAT_016de6d8;
        qf[1] = s * DAT_016de6dc;
        qf[2] = s * DAT_016de6e0;
        qf[3] = c;
        char buf2[16];
        float* quat = FUN_0059aed0(buf2, &DAT_016de6e4, qf);
        piVar2[0x1a8] = *(int*)&quat[0];
        piVar2[0x1a9] = *(int*)&quat[1];
        piVar2[0x1aa] = *(int*)&quat[2];
        ((void(__thiscall*)(void*, void*))VF(piVar2, 0x48))(piVar2, *(void**)((char*)param_1 + 0x84));
        void* u = (void*)((float*(__thiscall*)(void*))VF((char*)inv + 0x34, 0x2c))((char*)inv + 0x34);
        ((Obj*)((char*)piVar2 + 0x508))->F_dae0(u);
        int* pv = (int*)((float*(__thiscall*)(void*))VF((char*)inv + 0x34, 0x30))((char*)inv + 0x34);
        piVar2[0x1cc] = pv[0];
        piVar2[0x1cd] = pv[1];
        piVar2[0x1ce] = pv[2];
        piVar2[0x1cf] = pv[3];
    }
    FUN_01009a40(FUN_01002bd0(), piVar2);
    return piVar2;
}

// ===========================================================================
// 0x0102ba30 - SP::DropLoot
// ===========================================================================
// @ 0x0102ba30
void __cdecl FUN_0102ba30(uint32_t param_1, uint32_t param_2, uint32_t param_3, void* param_4) {
    void* planetRec = FUN_010212a0();
    int iVar4 = ((int(__thiscall*)(void*))VF(param_4, 0x4c))(param_4);
    uint32_t uVar6 = 0;
    bool have = false;
    if (iVar4 != -1) {
        Obj* sm = (Obj*)FUN_00b3d2a0(iVar4);
        Obj* emp = (Obj*)sm->F_a9370(iVar4);
        if (emp != 0) {
            uVar6 = (uint32_t)emp->F_17a0();
            have = true;
        }
    }
    if (!have) {
        float* cities = ((Obj*)FUN_01021240())->F_65e0();
        uVar6 = (uint32_t)DAT_015b7510.F_2a360(cities[0], cities[1], cities[2]);
    }
    int iVar4b = ((int(__thiscall*)(void*))VF(param_4, 0x38))(param_4);
    float fMin = 0.0f;
    float fMax = 0.0f;
    if (iVar4b == (int)0xb033b403u) {
        fMin = DAT_015b7510.F_29f60((int)uVar6);
        fMax = DAT_015b7510.F_29fd0((int)uVar6);
    } else if (iVar4b == (int)0xee9b2232u) {
        fMin = DAT_015b7510.F_2a230((int)uVar6);
        fMax = DAT_015b7510.F_2a2a0((int)uVar6);
    }
    double rd = DAT_1601760.RandomDoubleUniform();
    float res = (float)(rd * ((double)fMax - (double)fMin) + (double)fMin);
    float val = fMax;
    if (res < fMax) {
        val = res;
        if (res < fMin) {
            val = fMin;
        }
    }
    int count = (int)(val * 0.04f + 0.5f) * 0x19;
    if (count > 0) {
        uint8_t rbuf[0x2c] = {0};
        *(uint32_t*)(rbuf + 0x00) = 0x2cb59744;
        *(uint32_t*)(rbuf + 0x04) = param_1;
        *(uint32_t*)(rbuf + 0x08) = param_2;
        *(uint32_t*)(rbuf + 0x0c) = param_3;
        *(uint16_t*)(rbuf + 0x10) = (uint16_t)count;
        *(uint8_t*)(rbuf + 0x12) = 7;
        Obj* gtm = (Obj*)FUN_00b3d380();
        uint64_t t = gtm->F_316c0();
        *(uint32_t*)(rbuf + 0x18) = FUN_011e0970((uint32_t)t, (uint32_t)(t >> 32), 1000, 0);
        uint32_t uVar2 = *(uint32_t*)((char*)planetRec + 0x138);
        if (uVar2 < *(uint32_t*)((char*)planetRec + 0x13c)) {
            *(uint32_t*)((char*)planetRec + 0x138) = uVar2 + 0x2c;
            if (uVar2 != 0) {
                ((Obj*)((char*)planetRec + 0x134))->F_9200(rbuf);
            }
        } else {
            ((Obj*)((char*)planetRec + 0x134))->F_b810(uVar2, rbuf);
        }
        Obj* avatar = (Obj*)((Obj*)FUN_01002bd0())->F_b1fdb0();
        int artifact = (int)avatar->F_5d20(rbuf);
        *(uint32_t*)(artifact + 0x224) = 4;
        void* loco = FUN_00f473a0(0x14, "Simulator/cDropToGroundLocomotion", 0, 0, 0, 0);
        if (loco != 0) {
            *(uint32_t*)((char*)loco + 8) = 0x13ec458;
            *(uint32_t*)((char*)loco + 0xc) = 0;
            *(uint32_t*)((char*)loco + 0) = 0x1499590;
            *(uint32_t*)((char*)loco + 8) = 0x1499580;
            *(uint32_t*)((char*)loco + 0x10) = 0;
        } else {
            loco = 0;
        }
        ((Obj*)((char*)artifact + 0x34))->F_21b0(loco);
        *(float*)(artifact + 0x660) = 0.0f;
        int* audio = (int*)FUN_00a206f0();
        int r2 = 0;
        if (audio != 0) {
            r2 = ((int(__thiscall*)(void*))VF(audio, 0x20))(audio);
        }
        FUN_00435ed0(0xa9cf08ea, (void*)r2);
    }
}

// ===========================================================================
// 0x0102bc90 - SP::GetBestUFOTarget
// ===========================================================================
// @ 0x0102bc90
int __cdecl FUN_0102bc90(void* param_1, void* param_2, char param_3) {
    float local_10 = 0.0f;
    int local_8 = 0;
    if (DAT_015b7518 != 0) {
        void* gm = (void*)DAT_015b7518;
        char c = ((char(__thiscall*)(void*, uint32_t, int*))VF(gm, 0x24))(gm, 0x304039c, &local_8);
        if (c != 0 && *(short*)(local_8 + 0x12) == 0xd) {
            local_10 = *((Obj*)local_8)->F_f70();
        } else {
            local_10 = 0.0f;
        }
    }
    if (*(int*)((char*)param_1 + 0x714) == 1 || param_3 != 0) {
        local_10 = DAT_0145c12c;
    }
    int local_14 = 0;
    float local_c = 0.0f;
    int* vec = ((Obj*)FUN_00b3d300())->F_21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                               (void*)FUN_00ad48b0, (void*)FUN_00b1e500, &DAT_018ebadc);
    int n = (vec[2] - vec[1]) >> 2;
    if (n > 0) {
        int i = 0;
        do {
            int obj = *(int*)(vec[1] + i * 4);
            if (!((Obj*)obj)->F_8990(1)) {
                float* pf3 = (float*)((float*(__thiscall*)(void*))VF((char*)obj + 0x34, 0x2c))((char*)obj + 0x34);
                float* pf6 = (float*)((float*(__thiscall*)(void*))VF((char*)param_1 + 0x34, 0x2c))((char*)param_1 + 0x34);
                float dx = pf6[0] - pf3[0];
                float dy = pf6[1] - pf3[1];
                float dz = pf6[2] - pf3[2];
                float d = sqrtf(dz * dz + (dy * dy + dx * dx));
                if (d <= local_10 && FUN_0102aa50((void*)obj, param_1, param_2)) {
                    if (local_14 == 0 || d < local_c) {
                        local_c = d;
                        local_14 = obj;
                    }
                }
            }
            i++;
        } while (i < n);
        if (local_14 != 0) {
            return local_14 + 0x508;
        }
    }
    return 0;
}