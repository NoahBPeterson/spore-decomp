// Decompilation slice s00fdf9f0
// Region flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// All four targets belong to SP::cAppModeSpace (the space-view application
// mode): the simulator/planet refresh (00fdf9f0), the "first wild planet"
// query (00fdfb10), the message dispatcher (00fdfbc0 = HandleMessage) and the
// civilisation-to-space transition setup (00fe0160).
//
// Field offsets, helper signatures and the class hierarchy were recovered from
// the disassembly; call targets are declared as external symbols so that the
// linker records a relocation for them (relocations are masked when scoring).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
typedef double         f64;

extern "C" void* memcpy(void* dst, const void* src, u32 size);
extern "C" char* strncpy(char* dst, const char* src, u32 size);

struct Vec3 { f32 x, y, z; };

namespace SP { class cAppModeSpace; }
class cTerraformingManager;
class cGameNounManager;

// ---------------------------------------------------------------------------
// external data
// ---------------------------------------------------------------------------
extern f32  DAT_013ec4d0;              // 0x013ec4d0  planet-grid scale
extern u8   DAT_018c43e8;              // 0x018c43e8

// ---------------------------------------------------------------------------
// call targets
// ---------------------------------------------------------------------------
extern "C" void* FUN_00f473a0(u32 size, const char* tag, int a, int b, int c, int d); // 0x00f473a0 operator_new
extern "C" void* FUN_01021260();                                               // 0x01021260 GetActivePlanet
extern "C" i32   FUN_01021230();                                               // 0x01021230
extern "C" void* FUN_01021300(void*);                                          // 0x01021300
extern "C" void* FUN_00b3d300();                                               // 0x00b3d300 NounManager
extern "C" void* FUN_00b3d310();                                               // 0x00b3d310
extern "C" void* FUN_00b3d350();                                               // 0x00b3d350 PlanetModel
extern "C" void* FUN_00b3d430();                                               // 0x00b3d430 TerraformingManager
extern "C" void* FUN_00b3d450(...);                                            // 0x00b3d450
extern "C" void  FUN_00b3d3d0(...);                                            // 0x00b3d3d0
extern "C" void  FUN_00b3d4d0(...);                                            // 0x00b3d4d0
extern "C" void* FUN_00ffbe50();                                               // 0x00ffbe50 GetUFOSimulator
extern "C" void  FUN_00fdc340(Vec3 const* v, f32 scale);                       // 0x00fdc340 UpdateSpaceGrid
extern "C" void* FUN_00fdb280(void* begin, Vec3 const* v, u32 flags);          // 0x00fdb280
extern "C" i32   FUN_00c772c0(u32 key);                                        // 0x00c772c0
extern "C" u32   FUN_0100a7c0(...);                                            // 0x0100a7c0
extern "C" void  FUN_01044360();                                               // 0x01044360
extern "C" void* FUN_00c71e30(void*);                                          // 0x00c71e30
extern "C" void* FUN_00fee0a0(...);                                            // 0x00fee0a0
extern "C" i32   FUN_00c308b0();                                               // 0x00c308b0
extern "C" i32   FUN_00bba100();                                               // 0x00bba100
extern "C" i32   FUN_00bb9d40();                                               // 0x00bb9d40
extern "C" void  FUN_00bb9b50();                                               // 0x00bb9b50
extern "C" void  FUN_00fdda10(...);                                            // 0x00fdda10
extern "C" void* FUN_00ad4930();                                               // 0x00ad4930
extern "C" void  FUN_00ad79d0(...);                                            // 0x00ad79d0
extern "C" void  FUN_00ad7ad0();                                               // 0x00ad7ad0
extern "C" void  FUN_00ad7a30(...);                                            // 0x00ad7a30
extern "C" void  FUN_00ae09b0(...);                                            // 0x00ae09b0
extern "C" void* FUN_00e0b3f0(...);                                            // 0x00e0b3f0 GetPropertyAsKey
extern "C" void* FUN_00e0b420(...);                                            // 0x00e0b420 GetPropertyAsInt
extern "C" void* FUN_0103a760(u32);                                            // 0x0103a760
extern "C" void* FUN_0103a020();                                               // 0x0103a020
extern "C" void* FUN_01039ff0(void*);                                          // 0x01039ff0
extern "C" void* FUN_01039fb0(...);                                            // 0x01039fb0
extern "C" void  FUN_0103ac40(void*);                                          // 0x0103ac40
extern "C" i32   FUN_00c8b5a0();                                               // 0x00c8b5a0
extern "C" void* FUN_00401010();                                               // 0x00401010
extern "C" void* FUN_00401090();                                               // 0x00401090
extern "C" void  FUN_004df3e0(...);                                            // 0x004df3e0
extern "C" void* FUN_004df400();                                               // 0x004df400
extern "C" void* FUN_004df420();                                               // 0x004df420
extern "C" void* FUN_00bef950();                                               // 0x00bef950
extern "C" void* FUN_00eeee40(...);                                            // 0x00eeee40
extern "C" void* FUN_00ac10a0(...);                                            // 0x00ac10a0
extern "C" void* FUN_00b25fb0();                                               // 0x00b25fb0 GetPlayerCivilization
extern "C" void  FUN_00b515e0();                                               // 0x00b515e0
extern "C" void  FUN_00b87bb0();                                               // 0x00b87bb0
extern "C" void  FUN_00b88420(...);                                            // 0x00b88420
extern "C" void  FUN_00b8d750(...);                                            // 0x00b8d750
extern "C" void  FUN_00b8de30(...);                                            // 0x00b8de30
extern "C" void  FUN_010219b0(...);                                            // 0x010219b0
extern "C" void  FUN_01066d60(...);                                            // 0x01066d60
extern "C" void* FUN_00c75770();                                               // 0x00c75770
extern "C" void  FUN_00c75740(void*);                                          // 0x00c75740
extern "C" void* FUN_00c713c0();                                               // 0x00c713c0
extern "C" void* FUN_00c713e0(u32);                                            // 0x00c713e0
extern "C" void  FUN_00c70de0(u32);                                            // 0x00c70de0
extern "C" void  FUN_00c73b60(u32);                                            // 0x00c73b60
extern "C" void* FUN_00c71030(u32);                                            // 0x00c71030
extern "C" i32   FUN_00c710c0();                                               // 0x00c710c0
extern "C" i32   FUN_00c6ffc0(u32);                                            // 0x00c6ffc0
extern "C" i32   FUN_00c70bf0(u32);                                            // 0x00c70bf0
extern "C" i32   FUN_00c6ffa0();                                               // 0x00c6ffa0
extern "C" i32   FUN_00c73cf0(u32);                                            // 0x00c73cf0
extern "C" i32   FUN_00c73ff0(void*);                                          // 0x00c73ff0
extern "C" i32   FUN_00c74280(void*);                                          // 0x00c74280
extern "C" i32   FUN_00c70e00();                                               // 0x00c70e00
extern "C" i32   FUN_00c70fb0();                                               // 0x00c70fb0
extern "C" i32   FUN_00fda750(void*);                                          // 0x00fda750
extern "C" void* FUN_00f67d90(void*);                                          // 0x00f67d90 GetCurrentTerrainSphere
extern "C" void* FUN_00a1c4e0(void*);                                          // 0x00a1c4e0
extern "C" u32   FUN_00b1e700();                                               // 0x00b1e700
extern "C" void  FUN_00ff3540();                                               // 0x00ff3540
extern "C" void  FUN_00ff0940();                                               // 0x00ff0940
extern "C" void  FUN_00ffd390(...);                                            // 0x00ffd390
extern "C" void  FUN_01003690();                                               // 0x01003690
extern "C" void* FUN_00b21080();                                               // 0x00b21080
extern "C" void* FUN_00b236c0();                                               // 0x00b236c0
extern "C" void* FUN_00cd7d10();                                               // 0x00cd7d10
extern "C" void* FUN_00d3d420();                                               // 0x00d3d420
extern "C" void* FUN_00acdff0();                                               // 0x00acdff0
extern "C" void* FUN_00ae5ea0();                                               // 0x00ae5ea0
extern "C" void* FUN_00b1e500();                                               // 0x00b1e500
extern "C" void* FUN_00b93c60(...);                                            // 0x00b93c60
extern "C" void  FUN_00829110(...);                                            // 0x00829110
extern "C" void  FUN_0102f660_hook(void*);                                     // 0x0102f660
extern "C" void  FUN_00c75770_hook();                                          // 0x00c75770
extern "C" void  FUN_00fdba50(SP::cAppModeSpace*, i32, i32);                   // 0x00fdba50

// ---------------------------------------------------------------------------
// reference-counted / virtual object bases
// ---------------------------------------------------------------------------
class cRefObj {
public:
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04  AddRef
    virtual void v08();                  // +0x08  Release
};

// a result object carrying the game-data record at its +0x34 tail
class cResultObj {
public:
    virtual void r00();                  // +0x00
    virtual void r04();                  // +0x04
};

// virtual sub-object embedded at cSpaceObj+0x120 (takes a scale argument)
class cGridQuery {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual Vec3* s2c();                 // +0x2c  current position
};

// virtual sub-object embedded at cPlayerInventory+0x34 (no argument)
class cGridQuery2 {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual Vec3* s2c();                 // +0x2c  current position
};

// a space-grid element; only the virtual sub-object at +0x120 is modelled
class cSpaceObj {
public:
    u8         mPad_000[0x120];
    cGridQuery mSub_120;                 // +0x120
};

// ---------------------------------------------------------------------------
// the "Simulator" object referenced through cAppModeSpace::mp_15c
// ---------------------------------------------------------------------------
class cSPSimPlanetHighLOD : public cRefObj {
public:
    cSPSimPlanetHighLOD* FUN_00ff8970(); // 0x00ff8970 (build / install vtable)
    void ActivatePlanet(void* planet);   // 0x00ff9800
};

class cSimGame {
public:
    void FUN_01005130();                 // 0x01005130
    u8   mPad_000[0x54];
    cSPSimPlanetHighLOD* mp_54;          // +0x54
};

// ---------------------------------------------------------------------------
// the noun-manager helper object that owns the data vectors
// ---------------------------------------------------------------------------
class cGameNounManager {
public:
    void* FUN_00b21340(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340 GetGameDataVector
};

// grow vector returned by GetGameDataVector; only begin (+0x04) and end
// (+0x08) are read.
struct cDataVec {
    u32    mUnk_00;                      // +0x00
    void** mpBegin;                      // +0x04
    void** mpEnd;                        // +0x08
};

// ---------------------------------------------------------------------------
// inventory / simulator refs used by the "first wild planet" query
// ---------------------------------------------------------------------------
class cPlayerInventory {
public:
    u8          mPad_000[0x34];
    cGridQuery2 mSub_34;                 // +0x34
};

class cSPSimulatorSpaceGame {
public:
    cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};

class cTerraformingManager {
public:
    void FUN_00bbe740(void* planet);     // 0x00bbe740
    void FUN_00bc1450(void* planet);     // 0x00bc1450
};

// ---------------------------------------------------------------------------
// SP::cAppModeSpace
// ---------------------------------------------------------------------------
namespace SP
{
class cAppModeSpace {
public:
    void  FUN_00fdf9f0();
    void* FUN_00fdfb10();
    void  HandleMessage();
    void  FUN_00fe0160();

    u8        mPad_000[0x24];
    u8        mb_24;                     // +0x24 transition-data initialised flag
    u8        mPad_025[0x15c - 0x25];
    cSimGame* mp_15c;                    // +0x15c
};
} // namespace SP

using SP::cAppModeSpace;

// ---------------------------------------------------------------------------
// 00fdf9f0  - rebuild the high-LOD planet simulator and refresh every grid
// ---------------------------------------------------------------------------
// @ 0x00fdf9f0
void cAppModeSpace::FUN_00fdf9f0()
{
    if (mp_15c->mp_54 == 0) {
        cSPSimPlanetHighLOD* p = (cSPSimPlanetHighLOD*)FUN_00f473a0(0x1e8, "Simulator", 0, 0, 0, 0);
        cSPSimPlanetHighLOD* np = (p != 0) ? p->FUN_00ff8970() : 0;

        cSPSimPlanetHighLOD** slot = &mp_15c->mp_54;
        cSPSimPlanetHighLOD* old = *slot;
        if (np != old) {
            if (np != 0)
                np->v04();
            *slot = np;
            if (old != 0)
                old->v08();
        }
    }

    void* planet = FUN_01021260();
    mp_15c->FUN_01005130();
    mp_15c->mp_54->ActivatePlanet(planet);
    ((cTerraformingManager*)FUN_00b3d430())->FUN_00bbe740(planet);
    ((cTerraformingManager*)FUN_00b3d430())->FUN_00bc1450(planet);

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    cDataVec* dv = (cDataVec*)nm->FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                               (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
    void*** pB = &dv->mpBegin;
    for (u32 i = 0; i < (u32)(pB[1] - pB[0]); ++i) {
        cSpaceObj* o = (cSpaceObj*)pB[0][i];
        FUN_00fdc340(o->mSub_120.s2c(), DAT_013ec4d0);
    }
}

// ---------------------------------------------------------------------------
// 00fdfb10  - "first wild planet" query: pick a UFO target from the inventory
// ---------------------------------------------------------------------------
// @ 0x00fdfb10
void* cAppModeSpace::FUN_00fdfb10()
{
    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    void* dvp = nm->FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                 (void*)FUN_00ae5ea0, (void*)FUN_00b1e500, (void*)0x0403df5c);

    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)FUN_00ffbe50();
    cPlayerInventory* inv = sim->GetPlayerInventory();
    Vec3* src = inv->mSub_34.s2c();

    Vec3 v;
    v.x = src->x;
    v.y = src->y;
    v.z = src->z;

    u32 flag;
    *(u8*)&flag = 0;

    cResultObj* r = (cResultObj*)FUN_00fdb280((void*)((char*)dvp + 4), &v, flag);
    if (r != 0) {
        r->r00();
        r->r04();
        return (void*)((char*)r + 0x34);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 00fdfbc0  - SP::cAppModeSpace::HandleMessage
// ---------------------------------------------------------------------------
// @ 0x00fdfbc0
void cAppModeSpace::HandleMessage()
{
    void* sphere = FUN_00f67d90(FUN_00b3d300());
    (void)sphere;

    if (FUN_00c772c0(0x5f1f0bc) == 0)
        return;
    if (FUN_00c772c0(0x5f1f0ca) != 0)
        return;

    FUN_01021230();
    void* planet = FUN_01021260();
    (void)planet;

    if (FUN_00bba100() != 0 && FUN_00bb9d40() == 0)
        FUN_00fdda10(FUN_00c772c0(0x5b15554));

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    cDataVec* dv = (cDataVec*)nm->FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                               (void*)FUN_00ad4930, (void*)FUN_00b1e500, (void*)0x02dd8c42);
    void*** pB = &dv->mpBegin;
    for (void** it = pB[0]; it != pB[1]; ++it) {
        u32* o = (u32*)*it;
        if (o[0x658 / 4] == 2) {
            if (FUN_00c772c0(0x4ac8010) == 0) {
                char buf[0x18];
                memcpy(buf, "SPG_TerraformToolClose", 0x17);
                buf[0x17] = 0;
                if (FUN_0100a7c0(buf) != 0) {
                    void* rec = (void*)((char*)o + 0x34);
                    FUN_00ad79d0(rec, rec);
                    FUN_00ad7ad0();
                }
            }
        } else if (o[0x658 / 4] == 4) {
            u32 key[3];
            key[0] = key[1] = key[2] = 0;
            FUN_00e0b3f0(key);
            if (key[0] == 0x7ecbe6f5) {
                if (FUN_00c772c0(0x4ac800c) == 0) {
                    char buf[0xe];
                    memcpy(buf, "SPG_RareClose", 0xd);
                    buf[0xe] = 0;
                    FUN_0100a7c0(buf);
                } else if (FUN_00c772c0(0x4ed1364) == 0) {
                    u32 n;
                    FUN_00e0b420(&n);
                    FUN_00b3d3d0();
                    u32 a = (u32)FUN_0103a760(n);
                    FUN_00b3d3d0();
                    u32 b = (u32)FUN_0103a020();
                    if (a < b) {
                        FUN_00b3d3d0();
                        u32 cnt = (u32)FUN_01039ff0((void*)a);
                        for (u32 k = 0; k < cnt; ++k) {
                            void* tmp[3];
                            FUN_00b3d3d0(tmp);
                            void* e = FUN_01039fb0(tmp);
                            FUN_0103ac40(e);
                        }
                    }
                }
            }
        }
    }

    i32 s = FUN_00c8b5a0();
    if (s == 1 && FUN_00c70e00() == 1) {
        if (FUN_00c70fb0() == 0) {
            char buf[0x24];
            memcpy(buf, "SPG_FirstBarrenPlanetInEmptySystem", 0x23);
            buf[0x23] = 0;
            FUN_0100a7c0(buf);
            return;
        }
        if (FUN_00fdfb10() != 0) {
            char buf[0x22];
            memcpy(buf, "SPG_FirstWildPlanetInEmptySystem", 0x21);
            buf[0x21] = 0;
            if (FUN_0100a7c0(buf) != 0)
                FUN_00ad7ad0();
        }
    }
}

// ---------------------------------------------------------------------------
// 00fe0160  - civilisation -> space transition setup
// ---------------------------------------------------------------------------
// @ 0x00fe0160
void cAppModeSpace::FUN_00fe0160()
{
    void* planet = FUN_01021260();
    if (planet != 0)
        FUN_0102f660_hook(planet);

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    nm->FUN_00b21340((void*)FUN_00b21080, (void*)FUN_00d3d420,
                     (void*)FUN_00b236c0, (void*)FUN_00b1e500, (void*)0x018c816a);

    FUN_01021230();
    void* pmodel = FUN_00b3d350();
    if (*(u32*)((char*)pmodel + 0x24) == 0) {
        FUN_00b8d750(FUN_00c713e0(1));
    } else {
        FUN_00b8d750(FUN_00c713c0());
    }

    FUN_00b515e0();
    FUN_00b88420(FUN_00b3d310());
    FUN_00ffd390(FUN_00ffbe50());

    FUN_01003690();
    FUN_00fdf9f0();

    mb_24 = 1;

    FUN_00fda750(this);
    FUN_00b8de30((void*)planet);
    FUN_010219b0();
    FUN_01066d60(FUN_00c70e00());

    FUN_00c73b60(0);
    for (i32 i = 0; i < FUN_00c710c0(); ++i) {
        void* node = FUN_00c71030((u32)i);
        if ((i32)FUN_00a1c4e0(node) == (i32)FUN_00b1e700()) {
            void* node2 = FUN_00c71030((u32)i);
            FUN_00ff0940();
            FUN_00b25fb0();
            (void)node2;
            FUN_00c71030((u32)i);
            FUN_00ff3540();
        }
    }
    FUN_00c6ffc0(0);
    FUN_00c70bf0(0);
    FUN_00c6ffa0();

    FUN_00c73ff0(this);
    FUN_00c74280(this);
    FUN_00c73cf0(0);
    FUN_00b87bb0();

    FUN_00c75770_hook();
    FUN_00fdba50(this, 1, 1);
    FUN_00401010();
}