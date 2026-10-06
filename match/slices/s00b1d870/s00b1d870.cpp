// Slice s00b1d870 -- Simulator object factories, Gonzago/window toggles, terrain accessors.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
int GetCurrentGameMode();   // 0x00b5b800
int GetPlayerEmpireID();    // 0x1021090

// ------------------------------------------------------------ tiny accessors
struct VObj {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual int  v0c(int a);
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual int  v20();
};

// @ 0x00b1e500
bool EqualsStreamId(VObj* o, int id) {
    return o->v20() == id;
}

// @ 0x00b1e520
bool CheckId(VObj* o, int a) {
    return o->v0c(a) != 0;
}

namespace Simulator {
struct cSpaceInventoryItem {
    bool mFlag;
    bool IsAvailableInCurrentPlanet();
    void* SetAvailable();
};
}
// @ 0x00b1e4d0
bool Simulator::cSpaceInventoryItem::IsAvailableInCurrentPlanet() { return false; }
// @ 0x00b1e540
void* Simulator::cSpaceInventoryItem::SetAvailable() { mFlag = true; return this; }

// ------------------------------------------------------------ object factories
struct cCelestialBody { void* ctor(int a); };
struct cPlanet { void* ctor(); };
struct cVisiblePlanet { void* ctor(); };
struct cSolarSystem { void* ctor(); };
struct cTribePlanner { void* ctor(); };
struct cGenericPressureEvent { void ctor(); };
extern void* gVtblPressureA;
extern void* gVtblPressureB;
extern void* gVtblPressureC;

// @ 0x00b1eba0
void* New_cCelestialBody() {
    cCelestialBody* p = (cCelestialBody*)operator new(0xcc, "Simulator/cCelestialBody", 0, 0, 0, 0);
    if (p)
        return p->ctor(-1);
    return 0;
}

// @ 0x00b1f590
void* New_cPlanet() {
    cPlanet* p = (cPlanet*)operator new(0x1c8, "Simulator/cPlanet", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 0xd4);
    }
    return 0;
}

// @ 0x00b1f5d0
void* New_cVisiblePlanet() {
    cVisiblePlanet* p = (cVisiblePlanet*)operator new(0x10c, "Simulator/cVisiblePlanet", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 0xd4);
    }
    return 0;
}

// @ 0x00b1f640
void* New_cSolarSystem() {
    cSolarSystem* p = (cSolarSystem*)operator new(0x54, "Simulator/cSolarSystem", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 8);
    }
    return 0;
}

// @ 0x00b1f790
void* New_cTribePlanner() {
    cTribePlanner* p = (cTribePlanner*)operator new(0x7c, "Simulator/cTribePlanner", 0, 0, 0, 0);
    if (p) {
        void* q = p->ctor();
        if (q)
            return (void*)((char*)q + 8);
    }
    return 0;
}

// @ 0x00b1e820
void* New_cGenericPressureEvent() {
    cGenericPressureEvent* p = (cGenericPressureEvent*)operator new(0x1f8, "Simulator/cGenericPressureEvent", 0, 0, 0, 0);
    if (p) {
        p->ctor();
        *(void**)p = &gVtblPressureA;
        *(void**)((char*)p + 4) = &gVtblPressureB;
        *(void**)((char*)p + 0x34) = &gVtblPressureC;
        *(uint32_t*)((char*)p + 0x1f0) = 0x78;
        return p;
    }
    return 0;
}

// @ 0x00b1fc30
void* New_cMissionHappinessEvent() {
    cGenericPressureEvent* p = (cGenericPressureEvent*)operator new(0x1f0, "Simulator/cMissionHappinessEvent", 0, 0, 0, 0);
    if (p) {
        p->ctor();
        *(void**)p = &gVtblPressureA;
        *(void**)((char*)p + 4) = &gVtblPressureB;
        *(void**)((char*)p + 0x34) = &gVtblPressureC;
        return p;
    }
    return 0;
}

// @ 0x00b1f9d0
int GetPlayerEmpireOrMinus1() {
    int id = -1;
    switch (GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        id = GetPlayerEmpireID();
        break;
    }
    return id;
}

namespace UTFWin {
struct Window { bool Initialize(); };
}
// @ 0x00b1fbf0
bool UTFWin::Window::Initialize() { return true; }

// ------------------------------------------------------------ window toggles
struct SubObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void v7c(int, int);
};
struct WMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void v58(int, void*);
    virtual void v5c(int, void*);
};
void* WindowManager();   // 0x0067caa0

struct Host {
    char  pad00[0x38];
    void* mpSub;   // 0x38
    void Fn1();
    void Fn2();
};

// @ 0x00b1db60  (complete, near miss: window-manager toggle)
void Host::Fn1() {
    void* p = mpSub;
    if (p) {
        ((SubObj*)((char*)p + 4))->v7c(1, 1);
        ((WMgr*)WindowManager())->v58(1, mpSub ? (char*)mpSub + 4 : 0);
        void* q = mpSub;
        if (q) {
            ((WMgr*)WindowManager())->v58(0, (char*)q + 4);
            return;
        }
        ((WMgr*)WindowManager())->v58(0, 0);
    }
}

// @ 0x00b1dbd0  (complete, near miss)
void Host::Fn2() {
    void* p = mpSub;
    if (p) {
        ((SubObj*)((char*)p + 4))->v7c(1, 0);
        ((WMgr*)WindowManager())->v5c(1, mpSub ? (char*)mpSub + 4 : 0);
        void* q = mpSub;
        if (q) {
            ((WMgr*)WindowManager())->v5c(0, (char*)q + 4);
            return;
        }
        ((WMgr*)WindowManager())->v5c(0, 0);
    }
}

// ------------------------------------------------------------ terrain accessors
struct cTerrainEditor { int GetCurrentTerrainSphere(); };
cTerrainEditor* SP_NounManager();   // 0x00b3d300
int FUN_00c75420();                 // 0x00c75420

struct TerrainMgr {
    char pad00[0x20];
    void* mId;              // 0x20
    char padTo90[0x90 - 0x24];
    int  Fn1(int id, bool flag);
    int  Fn2();
};

// @ 0x00b1daf0  (complete, near miss)
int TerrainMgr::Fn1(int id, bool flag) {
    int idx = 1;
    if (flag) {
        cTerrainEditor* te = SP_NounManager();
        if (te->GetCurrentTerrainSphere())
            idx = FUN_00c75420();
    }
    if ((unsigned)(id - 0x1654c00) <= 6)
        return ((int*)this)[idx + (id - 0x1654bfb) * 3];
    if (id == 0x1654c10)
        return *(int*)((char*)this + 0x90 + idx * 4);
    return 0;
}

// @ 0x00b1de80  (complete, near miss)
int TerrainMgr::Fn2() {
    void* id = mId;
    int idx = 1;
    cTerrainEditor* te = SP_NounManager();
    if (te->GetCurrentTerrainSphere())
        idx = FUN_00c75420();
    if ((unsigned)((int)id - 0x1654c00) <= 6)
        return ((int*)this)[idx + ((int)id - 0x1654bfb) * 3];
    if (id != (void*)0x1654c10)
        return 0;
    return *(int*)((char*)this + 0x90 + idx * 4);
}

// @ 0x00b1dfc0  (complete, near miss: refcounted member reset)
struct RefHolder {
    char pad00[0x30];
    int* mpMgr;   // 0x30
    int* mpObj;   // 0x34
    void Reset();
};
void RefHolder::Reset() {
    int* p = mpObj;
    if (p) {
        mpObj = 0;
        (*(void(**)(void))(*(int*)p + 4))();
    }
    char r = (*(char(**)(int, int, void*))(*(int*)mpMgr + 8))(0xf08ce134, 0, &mpObj);
    if (r) {
        int* q = mpObj;
        (*(void(**)(int))(*(int*)q + 8))(0);
        q = mpObj;
        if (q) {
            mpObj = 0;
            (*(void(**)(void))(*(int*)q + 4))();
        }
    }
}

// =====================================================================
// Partially-reconstructed functions (see partial.txt).
// =====================================================================

// @ 0x00b1d870  (partial)
void* FUN_b1d870() { return 0; }

// @ 0x00b1d970  (partial)
void* FUN_b1d970() { return 0; }

// @ 0x00b1da20  (partial)
void* FUN_b1da20() { return 0; }

// @ 0x00b1dc60  (partial)
void* FUN_b1dc60() { return 0; }

// @ 0x00b1dee0  (partial)
void* FUN_b1dee0() { return 0; }

// @ 0x00b1e020  (partial)
int FUN_b1e020() { return 0; }

// @ 0x00b1e0c0  (partial: 836-byte play-mode environmental transition)
int FUN_b1e0c0() { return 0; }

// @ 0x00b1e410  (partial)
int FUN_b1e410() { return 0; }

// @ 0x00b1f960  (partial)
void FUN_b1f960(bool flag) { (void)flag; }

// @ 0x00b1fbb0  (partial)
bool FUN_b1fbb0(void* self, int id) { (void)self; (void)id; return false; }

// @ 0x00b1fc80  (partial)
void FUN_b1fc80(void* self, void* reader) { (void)self; (void)reader; }