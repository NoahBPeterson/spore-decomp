// Slice s00ba5650 -- Simulator::cPlanetRecord telemetry/report family and the
// cStarManager planet-add helpers that follow it (0x00ba5650..0x00ba6748).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: no unwind frames)
//
// The telemetry record is the "SP::cTelemetryRecord" bucket written through
// FUN_0067de90(modeIndex, key0, key1, key2) -> provider*: the record lives at
// +0x0c of the provider container, and its fields are
//    +00 clock/1000  +04 key1  +08 key0  +0c key2  +10 modeType
//    +14 commContext +18 eventKind +1c colorID +20 value +24 planetID
//    +28 flags +2c floatParam
// The helper routines FUN_00ba5410..FUN_00ba55d0 are the EASTL cursor-map lookups
// shared with slice s00ba47b0 (external relocations, declared by address).
#include "types.h"

typedef unsigned int uint;

#pragma warning(disable: 4100)

// ---- runtime / allocator ---------------------------------------------------------------
void* __cdecl operator_new(unsigned size, const char* name, int a, int b,
                           int c, int d);                             // 0x00f473a0 (EAAllocate)
void* __cdecl FUN_00f48a80();                                         // 0x00f48a80
int   __cdecl FUN_00e3ea00(int, int);                                 // 0x00e3ea00

// ---- framework -------------------------------------------------------------------------
void* __cdecl FUN_0067de90(...);                                      // 0x0067de90 (variadic)
void* __cdecl FUN_007ec160(int, ...);                                 // 0x007ec160
void  __cdecl FUN_007eb820(int, ...);                                 // 0x007eb820
int   __cdecl SP_GetCurrentGameMode();                                // 0x00b5b800
void* __cdecl SP_GameTimeManager();                                   // 0x00b3d380
uint64_t __cdecl FUN_00b316c0(void* self);                            // 0x00b316c0
extern "C" uint64_t __cdecl _aulldiv(uint64_t, uint64_t);             // 0x011e0970
void* __cdecl FUN_010212a0();                                         // 0x010212a0
void* __cdecl cStarRecordRef_GetCommContext(void* self);              // 0x00ce6950
void* __cdecl SP_NounManager(int);                                    // 0x00b3d300
int   __cdecl FUN_00b1f9d0();                                         // 0x00b1f9d0
void* __cdecl SP_RelationshipManager(...);                            // 0x00b3d2c0
int   __cdecl FUN_00ba3f90(void* self, int);                          // 0x00ba3f90
char  __cdecl FUN_00c8eb50(void* obj, int* out);                      // 0x00c8eb50
void* __cdecl FUN_00bef950(int* obj);                                 // 0x00bef950
void* __cdecl FUN_00c0bc00(void* obj, int a);                         // 0x00c0bc00
char  __cdecl FUN_00c0c0e0(void* obj);                                // 0x00c0c0e0
char  __cdecl FUN_00c0c100(void* obj);                                // 0x00c0c100
int   __cdecl FUN_00fc2080(float, float);                             // 0x00fc2080
extern "C" int __cdecl FUN_00b8d8e0(void);                          // 0x00b8d8e0 (thiscall: this=ecx)
extern "C" void __cdecl FUN_00b8dde0(void);                            // 0x00b8dde0 (thiscall: this=ecx)
void* __cdecl SP_IDGenerator();                                       // 0x0067de60
void  __cdecl FUN_00b8da80(int obj, int id);                          // 0x00b8da80
int   __cdecl FUN_00b8e180(int obj);                                  // 0x00b8e180
void  __cdecl SetCachingType(int a, int b);                           // 0x006ac040
void  __cdecl FUN_006ad010(int obj);                                  // 0x006ad010
struct PlanetObj {
    char pad00[0xac];
    char mFlagAC;        // +0xac
    char padAD[0x1d4 - 0xad];
    int  mField1D4;      // +0x1d4
    uint AllocID(char b);                             // 0x00ba6630
    char SomeIsTrue();                                // 0x00bb9c60
};
int __stdcall FUN_00ba6460(PlanetObj* obj);                           // 0x00ba6460
void  __cdecl SP_PostGameModeTransition(int, int, int);               // 0x00b5b900
void  __cdecl SP_PreGameModeTransition(int, int, int);                // 0x00b5b930
struct cGonzagoSubsystem {
    void PostGameModeTransition(int a, int b);                        // 0x00b5b900
    void PreGameModeTransition(int a, int b);                         // 0x00b5b930
    void PostGameModeTransition2(int a, int b);                       // 0x00ba63d0
    void PreGameModeTransition2(int a, int b);                        // 0x00ba6400
};

// RelationshipManager::GetRelationLevel(planetID, empireOrMinus1, mode): thiscall,
// this in ecx, three stack args (mode last) -> ret 0xc.
struct RelationshipManager {
    int GetRelationLevel(void* a, void* b, int mode);                 // 0x00d00a70
};
void  __cdecl cVarListSerializer_Construct(void* self, int a, const void* p, uint tag); // 0x00692f90
char  __cdecl cVarListSerializer_Serialize(void* self, void* stream); // 0x00693e10
extern int g_fieldName;                                               // 0x0156cb18 (placeholder)
extern int g_168964c;                                                 // 0x0168964c
uint  __cdecl SC_RandomUint32Uniform(void* rng, uint n);              // 0x00a68fb0
extern char g_sMathRandom;                                            // 0x01601760
struct RandomLC { uint __thiscall RandomUint32Uniform(uint n); };     // 0x00a68fb0
#define RNG(n) (((RandomLC*)&g_sMathRandom)->RandomUint32Uniform(n))

extern "C" void* __cdecl FUN_00ba5220();                              // 0x00ba5220
extern "C" void* __cdecl FUN_00ba5410(void* self, uint key, int m);   // 0x00ba5410
extern "C" void* __cdecl FUN_00ba5470(void* self, uint* key, int a, int b, int c); // 0x00ba5470
extern "C" void* __cdecl FUN_00ba54f0(void* self, uint* key, int a, int b, int c); // 0x00ba54f0
extern "C" void* __cdecl FUN_00ba5570(void);                          // 0x00ba5570 (thiscall: this=ecx, key on stack)
extern "C" void* __cdecl FUN_00ba55d0(void* self, uint key, int a, int b, int c,
                                      int d, int e, int f);           // 0x00ba55d0
void* __cdecl FUN_00ba57f0(int* coords, int modeType);                // 0x00ba57f0

// ---- the telemetry record --------------------------------------------------------------
struct TelemetryRecord {
    int   mClock;      // +00
    int   mKey1;       // +04
    int   mKey0;       // +08
    int   mKey2;       // +0c
    int   mModeType;   // +10
    void* mComm;       // +14
    int   mKind;       // +18
    int   mColorID;    // +1c
    int   mValue;      // +20
    int   mPlanetID;   // +24
    int   mFlags;      // +28
    float mParam;      // +2c
};

struct cEmpire {
    char pad00[0x10];
    int  mField10;      // +10
    char pad14[0x84 - 0x14];
    int  mField84;      // +84
};

void* __cdecl FUN_00c30c80(cEmpire* obj);                             // 0x00c30c80
void* __cdecl SP_cEmpire_GetHomePlanet(cEmpire* obj);                 // 0x00c31730

// Provider container: +0x0c holds a base pointer whose [3] is the record array.
static inline TelemetryRecord* RecOf(void* rec)
{
    return (TelemetryRecord*)(*(void**)((char*)rec + 0x0c));
}

// ---------------------------------------------------------------- 0x00ba5650
// @ 0x00ba5650
void* __cdecl FUN_00ba5650(int* coords, int modeType)
{
    void* prov = FUN_00ba5220();
    void* rec;
    if (modeType == 7) {
        rec = FUN_00ba5410(FUN_0067de90((int)prov, 7), 7, modeType);
    } else if (modeType == 8) {
        rec = FUN_00ba5410(FUN_0067de90((int)prov, 8), 8, modeType);
    } else {
        rec = FUN_00ba5470(FUN_0067de90((int)prov, coords[0], coords[1], coords[2]),
                           (uint*)coords, coords[0], coords[1], coords[2]);
    }
    if (rec == 0) {
        rec = FUN_007ec160((int)FUN_0067de90((int)prov, 0), 0);
        FUN_007eb820((int)rec, 0xc);
        if (rec == 0)
            return 0;
    }
    void* gt = SP_GameTimeManager();
    uint64_t t = FUN_00b316c0(gt);
    TelemetryRecord* r = RecOf(rec);
    r->mClock = (int)_aulldiv(t, 1000);
    r->mKey1 = coords[1];
    r->mKey0 = coords[0];
    r->mKey2 = coords[2];
    r->mModeType = modeType;
    void* u = FUN_010212a0();
    r->mComm = u ? cStarRecordRef_GetCommContext(u) : 0;
    r->mKind = 1;
    r->mColorID = (int)0xff576f79;
    if (SP_GetCurrentGameMode() == 0x1654c10) {
        r->mValue = -1;
    } else {
        void* e = SP_RelationshipManager((void*)coords, 0);
        r->mValue = FUN_00ba3f90(e, 0);
    }
    r->mPlanetID = -1;
    r->mFlags = (uint)(SP_GetCurrentGameMode() + 0xfe9ab3fc) <= 1u;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba57a0
// @ 0x00ba57a0
void* __cdecl FUN_00ba57a0(int* obj, int a)
{
    if (obj == 0)
        return 0;
    int* v = (int*)((int (__thiscall*)(void*, int))((void**)*(void**)((char*)obj + 0x34))[0x26])((char*)obj + 0x34, a);
    void* rec = FUN_00ba57f0(v, a);
    if (rec != 0) {
        int v2 = ((int (__thiscall*)(void*))((void**)*obj)[0x13])(obj);
        *(int*)((char*)RecOf(rec) + 0x24) = v2;
    }
    return rec;
}

// ---------------------------------------------------------------- 0x00ba57f0
// @ 0x00ba57f0
void* __cdecl FUN_00ba57f0(int* coords, int modeType)
{
    void* prov = FUN_00ba5220();
    void* rec = FUN_00ba54f0(FUN_0067de90((int)prov, coords[0], coords[1], coords[2]),
                             (uint*)coords, coords[0], coords[1], coords[2]);
    if (rec == 0) {
        rec = FUN_007ec160((int)FUN_0067de90((int)prov, 0), 0);
        FUN_007eb820((int)rec, 0xc);
        if (rec == 0)
            return 0;
    }
    void* gt = SP_GameTimeManager();
    uint64_t t = FUN_00b316c0(gt);
    TelemetryRecord* r = RecOf(rec);
    r->mClock = (int)_aulldiv(t, 1000);
    r->mKey1 = coords[1];
    r->mKey0 = coords[0];
    r->mKey2 = coords[2];
    r->mModeType = modeType;
    void* u = FUN_010212a0();
    r->mComm = u ? cStarRecordRef_GetCommContext(u) : 0;
    r->mKind = 0;
    r->mColorID = (int)0xff576f79;
    r->mValue = -1;
    r->mPlanetID = -1;
    r->mFlags = 0;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba58e0
// @ 0x00ba58e0
void* __cdecl FUN_00ba58e0(int* obj, int modeType)
{
    if (obj == 0)
        return 0;
    void* prov = FUN_00ba5220();
    int v = ((int (__thiscall*)(void*))((void**)*obj)[0x13])(obj);
    void* rec;
    if (modeType == 7)
        rec = FUN_00ba5410(FUN_0067de90((int)prov, 7), 7, modeType);
    else
        rec = ((void*(__thiscall*)(void*, int))FUN_00ba5570)(FUN_0067de90((int)prov, v), v);
    if (rec == 0) {
        rec = FUN_007ec160((int)FUN_0067de90((int)prov, 0), 0);
        FUN_007eb820((int)rec, 0xc);
        if (rec == 0)
            return 0;
    }
    void* gt = SP_GameTimeManager();
    uint64_t t = FUN_00b316c0(gt);
    TelemetryRecord* r = RecOf(rec);
    r->mClock = (int)_aulldiv(t, 1000);
    int v3[3] = { 0, 0, 0 };
    if (FUN_00c8eb50(obj, v3)) {
        r->mKey1 = v3[1];
        r->mKey0 = v3[0];
        r->mKey2 = v3[2];
    }
    r->mModeType = modeType;
    void* u = FUN_010212a0();
    r->mComm = u ? cStarRecordRef_GetCommContext(u) : 0;
    r->mKind = 2;
    r->mColorID = obj[0x8d];
    void* nm = SP_NounManager(1);
    int emp = FUN_00b1f9d0();
    r->mValue = ((RelationshipManager*)SP_RelationshipManager((void*)v, emp))->GetRelationLevel((void*)v, (void*)emp, 1);
    void* lst = ((int* (__thiscall*)(void*))((void**)*obj)[0x24])(obj);
    if (*(int*)lst != *(int*)((char*)lst + 4)) {
        void* p = *(void**)(*(int*)((char*)lst + 4) - 4);
        r->mParam = ((float (__thiscall*)(void*))((void**)*(void**)p)[0x1f])(p);
    }
    r->mPlanetID = v;
    r->mFlags = 1;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba5a60
// @ 0x00ba5a60
void* __cdecl FUN_00ba5a60(int* obj, int modeType)
{
    if (obj == 0)
        return 0;
    if (SP_RelationshipManager((void*)0, 0) == 0)
        return 0;
    void* prov = FUN_00ba5220();
    int v = ((int (__thiscall*)(void*))((void**)*obj)[0x13])(obj);
    void* rec;
    if (modeType == 7)
        rec = FUN_00ba5410(FUN_0067de90((int)prov, 7), 7, modeType);
    else
        rec = ((void*(__thiscall*)(void*, int))FUN_00ba5570)(FUN_0067de90((int)prov, v), v);
    if (rec == 0) {
        rec = FUN_007ec160((int)FUN_0067de90((int)prov, 0), 0);
        FUN_007eb820((int)rec, 0xc);
        if (rec == 0)
            return 0;
    }
    void* gt = SP_GameTimeManager();
    uint64_t t = FUN_00b316c0(gt);
    TelemetryRecord* r = RecOf(rec);
    r->mClock = (int)_aulldiv(t, 1000);
    void* s = FUN_00bef950(obj);
    int* v3 = s ? (int*)((char*)s + 0x504) : (int*)0;
    if (!s) {
        static int zero[3] = { 0, 0, 0 };
        v3 = zero;
    }
    r->mKey1 = v3[1];
    r->mKey0 = v3[0];
    r->mKey2 = v3[2];
    r->mModeType = modeType;
    void* u = FUN_010212a0();
    r->mComm = u ? cStarRecordRef_GetCommContext(u) : 0;
    r->mKind = 4;
    r->mColorID = obj[0x10];
    r->mParam = -1.0f;
    void* nm = SP_NounManager(1);
    int emp = FUN_00b1f9d0();
    r->mValue = ((RelationshipManager*)SP_RelationshipManager((void*)v, emp))->GetRelationLevel((void*)v, (void*)emp, 1);
    r->mPlanetID = v;
    r->mFlags = 1;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba5bc0
// @ 0x00ba5bc0
void* __cdecl FUN_00ba5bc0(cEmpire* obj, int modeType)
{
    if (obj == 0)
        return 0;
    void* prov = FUN_00ba5220();
    int field84 = obj->mField84;
    void* rec;
    if (modeType == 7)
        rec = FUN_00ba5410(FUN_0067de90((int)prov, 7), 7, modeType);
    else
        rec = ((void*(__thiscall*)(void*, int))FUN_00ba5570)(FUN_0067de90((int)prov, field84), field84);
    if (rec == 0) {
        rec = FUN_007ec160((int)FUN_0067de90((int)prov, 0), 0);
        FUN_007eb820((int)rec, 0xc);
        if (rec == 0)
            return 0;
    }
    void* gt = SP_GameTimeManager();
    uint64_t t = FUN_00b316c0(gt);
    TelemetryRecord* r = RecOf(rec);
    r->mClock = (int)_aulldiv(t, 1000);
    void* s = FUN_00c30c80(obj);
    int* v3 = s ? (int*)((char*)s + 0x504) : (int*)0;
    if (!s) {
        static int zero[3] = { 0, 0, 0 };
        v3 = zero;
    }
    r->mKey1 = v3[1];
    r->mKey0 = v3[0];
    r->mKey2 = v3[2];
    r->mModeType = modeType;
    void* home = SP_cEmpire_GetHomePlanet(obj);
    if (home)
        r->mComm = cStarRecordRef_GetCommContext(home);
    r->mKind = 5;
    r->mColorID = obj->mField10;
    r->mParam = -1.0f;
    int val = 4;
    if (modeType != 7) {
        void* nm = SP_NounManager(1);
        int emp = FUN_00b1f9d0();
        val = ((RelationshipManager*)SP_RelationshipManager((void*)field84, emp))->GetRelationLevel((void*)field84, (void*)emp, 1);
    }
    r->mValue = val;
    r->mPlanetID = obj->mField84;
    r->mFlags = 1;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba5d30
// @ 0x00ba5d30
void __cdecl FUN_00ba5d30(int* obj)
{
    if (obj == 0)
        return;
    void* prov = FUN_00ba5220();
    int v = ((int (__thiscall*)(void*))((void**)*obj)[0x13])(obj);
    int v2 = v;
    void* rec = ((void*(__thiscall*)(void*, int))FUN_00ba5570)(FUN_0067de90(), v2);
    if (rec != 0) {
        ((void (__stdcall*)(int))SP_NounManager)(1);
        int emp = FUN_00b1f9d0();
        void* rm = ((void* (__stdcall*)(int, int))SP_RelationshipManager)(v2, emp);
        *(int*)((char*)RecOf(rec) + 0x20) =
            ((int (__thiscall*)(void*, void*, int))rm)((void*)v2, (void*)emp, 1);
    }
}

// ---------------------------------------------------------------- 0x00ba5d90
// @ 0x00ba5d90
void __cdecl FUN_00ba5d90(int* a, int* b)
{
    void* prov = FUN_0067de90();
    for (int i = 7; i <= 0xb; i++)
        FUN_00ba55d0(prov, i, a[0], a[1], a[2], b[0], b[1], b[2]);
}

// ---------------------------------------------------------------- 0x00ba5df0
// @ 0x00ba5df0
void __cdecl FUN_00ba5df0(int* a, int* b)
{
    FUN_00ba5d90(a, b);
    FUN_00e3ea00((int)a, (int)b);
}

// ---------------------------------------------------------------- 0x00ba5e10
// @ 0x00ba5e10
void* __cdecl FUN_00ba5e10(int* obj, int a)
{
    if (obj == 0)
        return 0;
    int v = (int)FUN_00c0bc00(obj, a);
    void* rec = FUN_00ba5650((int*)&v, v);
    if (rec == 0)
        return rec;
    *(int*)((char*)RecOf(rec) + 0x24) =
        ((int (__thiscall*)(void*))((void**)*obj)[0x13])(obj);
    if (FUN_00c0c0e0(obj)) {
        void* p = (void*)obj[0x16a];
        *(float*)((char*)RecOf(rec) + 0x2c) =
            ((float (__thiscall*)(void*))((void**)*(void**)p)[0x16])(p);
        *(int*)((char*)RecOf(rec) + 0x1c) = 2;
        return rec;
    }
    if (FUN_00c0c100(obj)) {
        void* p = (void*)obj[0x16a];
        *(float*)((char*)RecOf(rec) + 0x2c) =
            ((float (__thiscall*)(void*))((void**)*(void**)p)[0x16])(p);
        *(int*)((char*)RecOf(rec) + 0x1c) = 3;
        return rec;
    }
    *(float*)((char*)RecOf(rec) + 0x2c) =
        ((float (__thiscall*)(void*))((void**)*obj)[0x1f])(obj);
    *(int*)((char*)RecOf(rec) + 0x1c) = 1;
    return rec;
}

// ---------------------------------------------------------------- 0x00ba5ee0
// @ 0x00ba5ee0
int __cdecl FUN_00ba5ee0(int param)
{
    switch (param) {
    case 0:
        switch (RNG(2)) {
        case 0: return 0;
        case 1: return 5;
        }
        return 0;
    case 1:
        switch (RNG(2)) {
        case 0: return 6;
        case 1: return 1;
        }
        return 0;
    case 2:
        switch (RNG(4)) {
        case 0: return 2;
        case 1: return 3;
        case 2: return 4;
        case 3: return 7;
        }
        return 0;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ba5f80
// @ 0x00ba5f80
void __cdecl FUN_00ba5f80(int obj)
{
    void* g = FUN_00f48a80();
    float tmp1;
    float tmp2;
    void* vt = *(void**)(char*)g;
    int v = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, &tmp1);
    ((void (__thiscall*)(void*, int))((void**)vt)[2])(g, v);
    *(float*)(obj + 0xb0) = tmp2;
    *(float*)(obj + 0xb4) = tmp1;
}

// ---------------------------------------------------------------- 0x00ba5fd0
// @ 0x00ba5fd0
void __cdecl FUN_00ba5fd0(int obj)
{
    float save0 = *(float*)(obj + 0xb0);
    float dup = *(float*)(obj + 0xb4);
    bool gt = 0.66f < dup;
    bool lt = dup < 0.34f;
    for (int i = 100; ; ) {
        if (--i < 0) {
            *(float*)(obj + 0xb0) = save0;
            *(float*)(obj + 0xb4) = dup;
            return;
        }
        ((void (__thiscall*)(void*, void*, int))FUN_00b8dde0)((void*)obj, (void*)0, 0);
        void* g = FUN_00f48a80();
        float tmp[2];
        int v = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, tmp);
        ((void (__thiscall*)(void*, int))((void**)*(void**)g)[2])(g, v);
        *(float*)(obj + 0xb0) = tmp[1];
        float f = tmp[0];
        *(float*)(obj + 0xb4) = f;
        if ((0.66f < f) != gt || (f < 0.34f) != lt)
            return;
    }
}

// ---------------------------------------------------------------- 0x00ba6120
// @ 0x00ba6120
void __cdecl FUN_00ba6120(int obj)
{
    int local[3];
    local[0] = 0; local[1] = 0; local[2] = 0;
    int off = *(int*)(obj + 0x28) + 0xae;
    void* gen = SP_IDGenerator();
    ((void (__thiscall*)(void*, int*, int, int, int, int, int))((void**)*(void**)gen)[1])(
        gen, local, 0xb1b104, 0x84, 0, off, 0);
    float tmp1[2];
    ((void (__thiscall*)(void*, void*, int))FUN_00b8dde0)((void*)obj, tmp1, 0);
    void* g = FUN_00f48a80();
    float tmp2[2];
    int key = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, tmp2);
    ((void (__thiscall*)(void*, int, int))((void**)*(void**)g)[4])(g, key, off);
    void* g2 = FUN_00f48a80();
    float tmp3[2];
    int v2 = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, tmp3);
    ((void (__thiscall*)(void*, int))((void**)*(void**)g2)[2])(g2, v2);
    *(float*)(obj + 0xb0) = tmp2[1];
    *(float*)(obj + 0xb4) = tmp2[0];
}

// ---------------------------------------------------------------- 0x00ba61b0
// @ 0x00ba61b0
void __cdecl FUN_00ba61b0(int planetID, int* dst)
{
    int o = (int)operator_new(0x1b0, "Simulator/cPlanetRecord", 0, 0, 0, 0);
    o = o ? FUN_00b8e180(o) : 0;
    *dst = o;
    FUN_00b8da80(o, planetID);
    *(int*)(o + 8) = planetID;
    *(int*)(o + 0xc) = 0x05220cb8;
    *(int*)(o + 0x10) = 1;
    ((void (__thiscall*)(int))((void**)*(void**)o)[0])(o);
    SetCachingType(1, o);
    FUN_006ad010(o);
}

// ---------------------------------------------------------------- 0x00ba6230
// @ 0x00ba6230
int __stdcall FUN_00ba6230(int obj)
{
    return *(int*)(obj + 0x70);
}

// ---------------------------------------------------------------- 0x00ba6310
// @ 0x00ba6310
void __stdcall FUN_00ba6310(int a, int planetID, uint flags)
{
    int local[3];
    local[0] = 0; local[1] = 0; local[2] = 0;
    void* gen = SP_IDGenerator();
    ((void (__thiscall*)(void*, int*, int, int, int, int, int))((void**)*(void**)gen)[1])(
        gen, local, 0xb1b104, 0x84, 0, planetID, 0);
    float tmp1[2];
    ((void (__thiscall*)(void*, void*, int))FUN_00b8dde0)((void*)a, tmp1, 0);
    void* g = FUN_00f48a80();
    float tmp2[2];
    int key = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)a, tmp2);
    ((void (__thiscall*)(void*, int, uint))((void**)*(void**)g)[4])(
        g, key, (flags & 0xff | 0x418400) << 8);
    void* g2 = FUN_00f48a80();
    float tmp3[2];
    int v2 = ((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)a, tmp3);
    ((void (__thiscall*)(void*, int))((void**)*(void**)g2)[2])(g2, v2);
    *(float*)(a + 0xb0) = tmp2[1];
    *(float*)(a + 0xb4) = tmp2[0];
}

// ---------------------------------------------------------------- 0x00ba63d0
// @ 0x00ba63d0
void cGonzagoSubsystem::PostGameModeTransition2(int a, int b)
{
    if (a != -1 && b == -1)
        *(char*)((char*)this + 0x21c) = 0;
    PostGameModeTransition(a, b);
}

// ---------------------------------------------------------------- 0x00ba6400
// @ 0x00ba6400
void cGonzagoSubsystem::PreGameModeTransition2(int a, int b)
{
    if (a != -1 && b == -1)
        *(char*)((char*)this + 0x21c) = 0;
    PreGameModeTransition(a, b);
}

// ---------------------------------------------------------------- 0x00ba6440
// @ 0x00ba6440
uint __stdcall FUN_00ba6440(uint id)
{
    if (id == 0xffffffffu)
        return id | 0;
    return id & 0xffffff;
}

// ---------------------------------------------------------------- 0x00ba6460
// @ 0x00ba6460
int __stdcall FUN_00ba6460(PlanetObj* obj)
{
    char c = obj->mFlagAC;
    if (c == 0 && !obj->SomeIsTrue())
        return 0;
    return 1;
}

// ---------------------------------------------------------------- 0x00ba64a0
// @ 0x00ba64a0
void __stdcall FUN_00ba64a0(int obj, int star, int parent)
{
    switch (*(int*)(obj + 0x28)) {
    case 0:
    case 1:
        *(float*)(obj + 0xb0) = 0.0f;
        *(float*)(obj + 0xb4) = 0.0f;
        *(float*)(obj + 0xb8) = 0.0f;
        return;
    case 3:
    case 4:
    case 5:
        if (((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, (void*)0) == 0)
            FUN_00ba6120(obj);
        return;
    case 6:
        if (((int (__thiscall*)(void*, void*))FUN_00b8d8e0)((void*)obj, (void*)0) == 0)
            ((void (__thiscall*)(void*, void*, int))FUN_00b8dde0)((void*)obj, (void*)0, 0);
        FUN_00ba5f80(obj);
        *(int*)(obj + 0x28) = FUN_00fc2080(*(float*)(obj + 0xb0), *(float*)(obj + 0xb4)) + 2;
        return;
    }
}

// ---------------------------------------------------------------- 0x00ba65e0
// @ 0x00ba65e0
char __stdcall FUN_00ba65e0(int a, int* stream)
{
    char buf[0xa14];
    cVarListSerializer_Construct(buf, a, &g_fieldName, 0x1a80d26);
    char ok = cVarListSerializer_Serialize(buf, stream);
    g_168964c = ((int (__thiscall*)(int*))((void**)*stream)[0xf])(stream);
    return ok;
}

// ---------------------------------------------------------------- 0x00ba6630
// @ 0x00ba6630
uint PlanetObj::AllocID(char b)
{
    uint v = (uint)mField1D4++;
    if (b != 0)
        v |= 0x80000000u;
    return v;
}

// ---------------------------------------------------------------- 0x00ba6650
// @ 0x00ba6650
uint __cdecl FUN_00ba6650(uint v)
{
    return v >> 31;
}

// ---------------------------------------------------------------- 0x00ba6660
// @ 0x00ba6660
void __stdcall FUN_00ba6660(int obj)
{
    if (*(int*)(obj + 0x28) != 2) {
        if ((uint)(*(int*)(obj + 0x28) - 3) > 2u)
            return;
        FUN_00ba6120(obj);
        return;
    }
    FUN_00ba5fd0(obj);
}

// ---------------------------------------------------------------- 0x00ba6710
// @ 0x00ba6710
char __cdecl FUN_00ba6710(int v, int** pp)
{
    int* p = *pp;
    ((void (__thiscall*)(void*, int))((void**)*(void**)((char*)p + 0xc))[5])((char*)p + 0xc, v);
    return 1;
}

// ---------------------------------------------------------------- 0x00ba6730
// @ 0x00ba6730
char __cdecl FUN_00ba6730(int v, int** pp)
{
    int* p = *pp;
    ((void (__thiscall*)(void*, int))((void**)*(void**)((char*)p + 0xc))[4])((char*)p + 0xc, v);
    return 1;
}
