// Slice s00ae2e20 -- Spore "tribe simulator"/city-descriptor cluster (unnamed FUN_* functions):
// stream read/write of a small triple, a per-frame tribe-simulator update, timer control,
// per-record bookkeeping over a 0x64-stride array, and a couple of descriptor copies.
//
//   * 0x00ae2e20  compare helper over FUN_00d00a70
//   * 0x00ae2e40  write a 3-field triple to a stream
//   * 0x00ae2ed0  read a 3-field triple from a stream
//   * 0x00ae2f70  per-frame tribe-simulator gating update
//   * 0x00ae3230  timer reset / restart
//   * 0x00ae32e0  timer stop
//   * 0x00ae34b0  per-record timer re-seed + nearest-record selection
//   * 0x00ae3600  find lowest-timer active record, return its +0x26 byte
//   * 0x00ae3660  city creature-count driven feedback
//   * 0x00ae3740  list-head check
//   * 0x00ae3750  tally record kinds into three counters
//   * 0x00ae37c0  build and publish a simulator descriptor
//   * 0x00ae3a10  copy a 0x64-byte descriptor record
//   * 0x00ae3b30  select and trigger the next record
//   * 0x00ae3d40  is the given id present in the record array
//   * 0x00ae3d70  property-driven terraforming pass
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <string.h>
#include <math.h>

typedef unsigned int   uint;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long long uint64;

// ---------------------------------------------------------------------------------------------
// External helpers (retail addresses). Only the small, stable-arity ones are declared with their
// real argument lists; the heavier game-manager entry points are declared as opaque calls.
extern "C" int  __stdcall FUN_00d00a70(int a, int b, int c);                  // 0x00d00a70
extern "C" bool __cdecl WriteTriple_WriteUint32(void* io, const void* p, int n, int endian); // 0x0093aa70
extern "C" bool __cdecl ReadTriple_ReadInt32(void* io, void* p, int n, int endian);          // 0x0093a780
extern "C" void* __cdecl EAAllocate(uint size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl FUN_00b9f9b0(void* p);                               // 0x00b9f9b0
extern "C" void  __cdecl FUN_00bbf730(void* a, float b);                      // 0x00bbf730
extern "C" int   __cdecl FUN_00bef920(int a);                                 // 0x00bef920
extern "C" void* __cdecl FUN_00b993c0(int a);                                 // 0x00b993c0
extern "C" uint  __cdecl FUN_00b6f0c0(void* a);                               // 0x00b6f0c0
extern "C" uint  __cdecl FUN_00458a40(uint color);                            // 0x00458a40
extern "C" void* __stdcall FUN_0067de90(int a, int b);                          // 0x0067de90
extern "C" uint64 __stdcall FUN_011e0970(uint lo, uint hi, uint div, uint pad); // 0x011e0970  (__aulldiv)
extern "C" int   __cdecl FUN_00bf01e0(void);                                  // 0x00bf01e0
extern "C" void  __cdecl FUN_00bf2ae0(double* out);                           // 0x00bf2ae0
extern "C" void  __cdecl FUN_00bf6fa0(void* self, double* out);               // 0x00bf6fa0
extern "C" int   __cdecl FUN_00bf7150(void);                                  // 0x00bf7150
extern "C" int   __cdecl FUN_00bf0c50(void);                                  // 0x00bf0c50
extern "C" bool  __cdecl FUN_00c77c50(void* sphere, void* key);               // 0x00c77c50
extern "C" int   __cdecl FUN_00c75420(void* sphere);                          // 0x00c75420
extern "C" int   __cdecl FUN_00ceec50(int a);                                 // 0x00ceec50
struct MathRandom { uint Uint32Uniform(uint n); };                            // 0x00a68fb0
extern "C" int   __cdecl FUN_00bc3170(void* timer);                           // 0x00bc3170
extern "C" void  __cdecl FUN_00e0a970_rand(void* rng, int n);                 // 0x00a68fb0

// Game managers / accessors.
struct ObjFactory { void* Make(); };                     // 0x007ec160 (thiscall)
struct IntVec     { void  Resize(int n); };              // 0x007eb820 (thiscall)
struct GameClock  { uint64 Ticks(); };                   // 0x00b316c0 (thiscall)

struct cCity {
    int  GetCreatureCount();          // 0x00bd8120  (thiscall)
    int  Find(void* key, int n);      // 0x00bda190  (thiscall)
    void SetFeedback(float v);        // 0x00be3f00  (thiscall)
};

// 0x00ae3660 is a thiscall whose `this` is not used; it takes the city plus an int.
struct TribeCtl {
    void Feedback(cCity* city, int ms, int x);   // 0x00ae3660
};

extern "C" void* __cdecl NounManager(void);                                   // 0x00b3d300
extern "C" void* __cdecl GetPlayerCivilization(void* mgr);                    // 0x00b25fb0
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);  // intrinsic
extern "C" void  __cdecl GetTerrainSphereOut(void* mgr, void* out);           // 0x00f67d90
extern "C" int   __cdecl GetCurrentTerrainSphere(void* mgr);                  // 0x00f67d90
extern "C" void* __cdecl PropertyManager(void);                               // 0x00a7de30
extern "C" void* __cdecl ConfigManager(void);                                 // 0x00a7dd30
extern "C" void* __cdecl TriggerMgr(void);                                    // 0x00b3d4d0
extern "C" void* __cdecl TerraformingManager(void* out, float v);             // 0x00b3d430
extern "C" void* __cdecl GameTimeManager(void);                               // 0x00b3d380
struct cSPTimer {                 // 0x00bc30f0 area
    void Restart();                                                           // 0x00bc3130
    void Stop();                                                              // 0x00bc3170
};
extern "C" uint64 __cdecl TimerElapsed(void* t);                              // 0x00bc3190
extern "C" bool  __cdecl TimerIsRunning(void* t);                             // 0x00feba90
extern "C" void  __cdecl TimerStart(void* t);                                 // 0x00bc30f0
extern "C" void  __cdecl SpatialObjectCtor(void* self);                       // 0x00c89630
extern "C" void* __cdecl cActionTarget_ctor(void* self, void* a, int b);      // 0x00ad7a30
extern "C" void  __cdecl cActionTarget_dtor(void* self);                      // 0x00ad7ad0
extern "C" void  __cdecl cTriggerMgr_PostAction(void* self, uint key, void* tgt, int z); // 0x00ae09b0
extern "C" void* __cdecl FUN_00bef6c0(void);                                  // 0x00bef6c0
extern "C" void  __cdecl FUN_00bf0c50_void(void);                             // 0x00bf0c50

// External data.
extern const float DAT_013f4fd0;   // 4294967296.0f
extern const float DAT_013f9428;
extern const float DAT_01470f1c;
extern const float DAT_013ec4d0;   // 100.0f
extern const float DAT_01471064;
extern const float DAT_014013c0;
extern const float DAT_0145b974;
extern const float DAT_0145b9bc;
extern const float DAT_0145b9c0;
extern const float DAT_0145b9c4;
extern const float DAT_01441a88;
extern int         DAT_0169c088;
extern void*       DAT_01601760;   // RandomLinearCongruential singleton
extern char        DAT_018eb106;

// ---------------------------------------------------------------------------------------------
// The object this slice operates on. Its layout is read directly from the disassembly; only the
// fields the slice touches are named. Records live in an array of 0x64-byte elements.
struct Rec {
    void*  mObj00;      // +0x00
    float  pad04[7];    // +0x04..+0x20
    int    mKey20;      // +0x20   (compared against *(obj+0x20))
    uint8  mKind21;     // +0x24 (mKind)
    uint8  mActive25;   // +0x25
    uint8  mSel26;      // +0x26
    uint8  pad27;
    int    mTimer28;    // +0x28
    int    mDead2c;     // +0x2c
    uint8  mDone30;     // +0x30
    uint8  pad31;
    uint8  pad32[2];
    int    mHandle34;   // +0x34
    int    mHandle38;   // +0x38 (server id)
    int    mTgt3c;      // +0x3c
    uint8  mFlag40;     // +0x40
    uint8  pad41[7];
    uint   mProp48;     // +0x48
    uint   mProp4c;     // +0x4c
    uint   pad50;
    uint   pad54;
    uint8  pad58[0xc];
};

struct Sim {
    char   pad00[0x14];
    Rec*   mpBegin;     // +0x14
    Rec*   mpEnd;       // +0x18
    uint   pad1c;
    uint8  pad20[0x38];
    void*  mTimer58;    // +0x58 (cSPTimer)
    char   pad5c[0x50];
    int    mDeclAc;     // +0xac
    int    mCurB0;      // +0xb0
    uint8  mFlagb4;     // +0xb4
    char   padb5[0x13];

    bool   Gating();              // 0x00ae2f70
    void   SetTimer(char on);     // 0x00ae3230
    void   StopTimer();           // 0x00ae32e0
    void   ReseedTimers(float* pos); // 0x00ae34b0
    uint8  PickLowest();          // 0x00ae3600
    bool   Head();                // 0x00ae3740
    void   Tally(int* a, int* b, int* c); // 0x00ae3750
    bool   Select(char flag, void* key);  // 0x00ae3b30
    bool   HasId(int id);         // 0x00ae3d40
    void   TerraformPass();       // 0x00ae3d70
};

// ---------------------------------------------------------------------------------------------
// 0x00ae2e20 -- `FUN_00d00a70(a, b, 1) <= 1`.
// @ 0x00ae2e20
bool __stdcall FUN_00ae2e20(int a, int b)
{
    return FUN_00d00a70(a, b, 1) <= 1;
}

// =============================================================================================
// 0x00ae2e40 -- write a 3-field triple to a stream (fields 2, 1, 0 in that order).
// @ 0x00ae2e40
void* FUN_00ae2e40(void* self, uint* triple)
{
    int v;
    void* w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    v = triple[2];
    void* io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    WriteTriple_WriteUint32(io, &v, 1, 0);

    w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    v = triple[1];
    io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    WriteTriple_WriteUint32(io, &v, 1, 0);

    w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    v = triple[0];
    io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    WriteTriple_WriteUint32(io, &v, 1, 0);
    return self;
}

// =============================================================================================
// 0x00ae2ed0 -- read a 3-field triple from a stream into +8, +4, +0.
// @ 0x00ae2ed0
void* FUN_00ae2ed0(void* self, char* triple)
{
    void* w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    void* io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    ReadTriple_ReadInt32(io, triple + 8, 1, 0);

    w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    ReadTriple_ReadInt32(io, triple + 4, 1, 0);

    w = (*(void*(__thiscall**)(void*))(*(uint*)self + 0x20))(self);
    io = (*(void*(__thiscall**)(void*))(*(uint*)w + 0x18))(w);
    ReadTriple_ReadInt32(io, triple, 1, 0);
    return self;
}

// =============================================================================================
// 0x00ae2f70 -- per-frame tribe-simulator gating; returns true when the timer target is met.
// @ 0x00ae2f70
bool Sim::Gating()
{
    if (mFlagb4 != 0)
        return false;

    void* civ = GetPlayerCivilization((void*)NounManager());
    if (civ == 0)
        return false;

    int span = mDeclAc - mCurB0;
    if (span > 1) {
        int c = FUN_00bf01e0();
        if (span == 2) {
            if (c >= span)
                return true;
        } else {
            if (c >= span - 1)
                return true;
            c = FUN_00bf01e0();
            if (c > span / 2)
                return true;
        }
    }

    uint key0 = 0x0521f703, key1 = 0, key2 = 0xaa9a8ed7;
    void* sphere = (void*)GetCurrentTerrainSphere((void*)NounManager());
    if (sphere == 0)
        return false;
    if (!FUN_00c77c50(sphere, &key0))
        return false;

    int   limit = 0;
    float bound = 0.0f;
    void* sphere2 = (void*)GetCurrentTerrainSphere((void*)NounManager());
    int   tier = FUN_00c75420(sphere2);
    if (tier == 0) {
        bound = DAT_0145b9bc;
        limit = 9000;
    } else if (tier == 1) {
        bound = DAT_0145b9c0;
        limit = 7000;
    } else if (tier == 2) {
        bound = 0.0f;
        limit = 0;
    }

    double a, b;
    FUN_00bf2ae0(&a);
    if ((double)limit < a) {
        goto hit;
    }
    FUN_00bf6fa0(civ, &b);
    if (!((double)bound < b))
        return false;

hit:
    int sel = 0;
    void* s3 = (void*)GetCurrentTerrainSphere((void*)NounManager());
    int t3 = FUN_00c75420(s3);
    if (t3 == 1) sel = -1;
    else if (t3 == 2) sel = -2;

    void* s4 = (void*)GetCurrentTerrainSphere((void*)NounManager());
    int   t4 = FUN_00c75420(s4);
    if (t4 > 1)
        goto post;
    if (FUN_00bf01e0() > 1)
        goto post;
    double c;
    FUN_00bf2ae0(&c);
    if ((double)((sel + 4) * 3000) < c)
        goto post;
    double d;
    FUN_00bf6fa0(civ, &d);
    if ((double)(sel * 800 + 0xaf0) < d)
        goto post;
    if (FUN_00bf7150() > sel + 3)
        goto post;
    if (FUN_00bf7150() >= sel + span)
        goto post;
    {
        if (!TimerIsRunning(&mTimer58))
            TimerStart(&mTimer58);

        int base = FUN_00ceec50(span) * 1000;
        void* s5 = (void*)GetCurrentTerrainSphere((void*)NounManager());
        int t5 = FUN_00c75420(s5);
        if (t5 == 0)
            base = FUN_00ceec50(span) * 3000;
        else if (t5 == 2)
            base = base / 3;

        int target;
        if (mCurB0 < span)
            target = (base * 3) / 2;
        else {
            target = base;
            if (span == 1)
                target = base / 2;
            void* s6 = (void*)GetCurrentTerrainSphere((void*)NounManager());
            int t6 = FUN_00c75420(s6);
            if (t6 > 1)
                target = target / 8;
        }
        if ((uint64)target < TimerElapsed(&mTimer58))
            return true;
    }
post:
    return false;
}

// =============================================================================================
// 0x00ae3230 -- start or restart the +0x78 timer, clear +0xa9.
// @ 0x00ae3230
void Sim::SetTimer(char on)
{
    if (on != 0) {
        ((cSPTimer*)((char*)this + 0x78))->Restart();
        *(uint8*)((char*)this + 0xa9) = 0;
    } else {
        ((cSPTimer*)((char*)this + 0x78))->Stop();
        *(uint8*)((char*)this + 0xa9) = 0;
    }
}

// =============================================================================================
// 0x00ae32e0 -- stop the +0x78 timer, clear +0xa9.
// @ 0x00ae32e0
void Sim::StopTimer()
{
    ((cSPTimer*)((char*)this + 0x78))->Stop();
    *(uint8*)((char*)this + 0xa9) = 0;
}

// =============================================================================================
// 0x00ae34b0 -- re-seed per-record timers and mark the nearest active record's timer zero.
// @ 0x00ae34b0
void Sim::ReseedTimers(float* pos)
{
    int ref = *(int*)((char*)mpBegin + 0x20);
    for (int i = 1; i < mDeclAc; ++i) {
        Rec* r = (Rec*)((char*)mpBegin + i * 0x64);
        int seed;
        if (r->mKey20 == ref)
            seed = (r->mActive25 != 0 ? 99 : 0) + 1;
        else
            seed = (r->mActive25 != 0 ? 9000 : 0) + 1000;
        r->mDead2c = seed + (int)((MathRandom*)0x1601760)->Uint32Uniform(100);
    }

    float best = DAT_0145b974;
    int   idx = -1;
    for (int i = 1; i < mDeclAc; ++i) {
        Rec* r = (Rec*)((char*)mpBegin + i * 0x64);
        if (r->mKey20 == ref && r->mActive25 == 1) {
            void* o = FUN_00b993c0((int)r->mObj00);
            float* p = (float*)(*(void*(__thiscall**)(void*))(*(uint*)((char*)o + 0x34) + 0x2c))((char*)o + 0x34);
            double dx = p[0] - pos[0];
            double dy = p[1] - pos[1];
            double dz = p[2] - pos[2];
            float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
            if (dist < best) {
                best = dist;
                idx = i;
            }
        }
    }
    if (idx != -1)
        *(int*)((char*)mpBegin + idx * 0x64 + 0x2c) = 0;
}

// =============================================================================================
// 0x00ae3600 -- return +0x26 of the lowest-timer active record, or 0.
// @ 0x00ae3600
uint8 Sim::PickLowest()
{
    int idx = -1;
    int best = 0x7fffffff;
    int n = mDeclAc;
    if (n > 1) {
        char* r = (char*)mpBegin + 0x90;
        for (int i = 1; i < n; ++i) {
            if (*(uint8*)(r + 4) == 0 && *(int*)r < best) {
                best = *(int*)r;
                idx = i;
            }
            r += 0x64;
        }
    }
    if (idx == -1)
        return 0;
    return *(uint8*)((char*)mpBegin + idx * 0x64 + 0x26);
}

// =============================================================================================
// 0x00ae3660 -- city creature-count driven feedback (thiscall; this unused, city is arg 0).
// @ 0x00ae3660
void TribeCtl::Feedback(cCity* city, int ms, int x)
{
    (void)x;
    double dsecs = (double)ms;
    if (ms < 0)
        dsecs = dsecs + DAT_013f4fd0;
    dsecs = dsecs * DAT_013f9428;
    float secs = (float)dsecs;
    if (secs > DAT_01470f1c)
        secs = DAT_01470f1c;

    float count = (float)city->GetCreatureCount();
    int   c2 = city->Find((void*)&DAT_018eb106, -1) + 1;
    float thr = DAT_013ec4d0;     // 100.0f
    float scaled = (float)(c2 * DAT_0169c088);
    float* use = scaled < thr ? &scaled : &thr;
    float out;
    if (*use > count)
        out = secs * DAT_01471064;
    else if (count > *use)
        out = secs * DAT_014013c0;
    else
        out = 0.0f;
    city->SetFeedback(out);
}

// =============================================================================================
// 0x00ae3740 -- list-head not-self check at +0x28.
// @ 0x00ae3740
bool Sim::Head()
{
    void** p = (void**)((char*)this + 0x28);
    return *p != p;
}

// =============================================================================================
// 0x00ae3750 -- tally record kinds into three counters.
// @ 0x00ae3750
void Sim::Tally(int* a, int* b, int* c)
{
    *a = 0;
    *b = 0;
    *c = 0;
    Rec* r = mpBegin;
    Rec* e = mpEnd;
    for (; r != e; r = (Rec*)((char*)r + 0x64)) {
        int k = FUN_00bef920(r->mTimer28);
        switch (k) {
        case 0: ++*a; break;
        case 1: ++*b; break;
        default: ++*c; break;
        }
    }
}

// =============================================================================================
// 0x00ae37c0 -- build a simulator descriptor and publish it (4 stack args, returns the object).
// @ 0x00ae37c0
void* __stdcall FUN_00ae37c0(int a1, float p2, float p3, float p4)
{
    void* obj = ((ObjFactory*)FUN_0067de90(3, a1))->Make();
    if (obj == 0)
        return 0;

    ((IntVec*)obj)->Resize(9);
    uint64 t = ((GameClock*)GameTimeManager())->Ticks();
    union { uint64 u; struct { uint lo, hi; } p; } tv; tv.u = t;
    uint64 secs = FUN_011e0970(tv.p.lo, tv.p.hi, 1000, 0);

    int* data = *(int**)((char*)obj + 0xc);
    data[0] = (int)secs;

    void* civ = GetPlayerCivilization((void*)NounManager());
    void* vec = (void*)FUN_00bef6c0();
    data[1] = (*(int*)((char*)vec + 4) - *(int*)vec) >> 2;

    civ = GetPlayerCivilization((void*)NounManager());
    data[2] = (int)*(float*)((char*)civ + 0x98);

    civ = GetPlayerCivilization((void*)NounManager());
    data[3] = FUN_00bf0c50();

    civ = GetPlayerCivilization((void*)NounManager());
    data[4] = FUN_00bf7150();

    *(float*)((char*)data + 0x14) = p2;
    *(float*)((char*)data + 0x18) = p3;
    *(float*)((char*)data + 0x1c) = p4;

    civ = GetPlayerCivilization((void*)NounManager());
    uint col = FUN_00b6f0c0(*(void**)((char*)civ + 0x40));
    data[8] = (int)FUN_00458a40(col);
    return obj;
}

// =============================================================================================
// 0x00ae3a10 -- copy a 0x64-byte descriptor record (memberwise; refcounts the two refs).
struct Desc {
    uint   m00;
    float  m04, m08, m0c, m10, m14, m18, m1c;
    int    m20;
    uint8  m24, m25, m26, m27;
    int    m28, m2c;
    uint8  m30, m31, m32, m33;
    int    m34, m38;
    int    m3c;
    uint8  m40;
    uint8  m41, m42, m43;
    int    m44, m48, m4c, m50, m54, m58, m5c, m60;

    Desc* CopyFrom(const Desc* s);   // 0x00ae3a10
};

// @ 0x00ae3a10
Desc* Desc::CopyFrom(const Desc* s)
{
    Desc* d = this;
    d->m00 = s->m00;
    d->m04 = s->m04;
    d->m08 = s->m08;
    d->m0c = s->m0c;
    d->m10 = s->m10;
    d->m14 = s->m14;
    d->m18 = s->m18;
    d->m1c = s->m1c;
    d->m20 = s->m20;
    d->m24 = s->m24;
    d->m25 = s->m25;
    d->m26 = s->m26;
    d->m28 = s->m28;
    d->m2c = s->m2c;
    d->m30 = s->m30;
    d->m31 = s->m31;
    d->m34 = s->m34;
    d->m38 = s->m38;
    if (d->m38 != 0)
        (*(void(__thiscall**)(int))(*(uint*)d->m38))(d->m38);
    d->m3c = s->m3c;
    d->m40 = s->m40;
    d->m44 = s->m44;
    d->m48 = s->m48;
    d->m4c = s->m4c;
    d->m50 = s->m50;
    d->m54 = s->m54;
    d->m58 = s->m58;
    d->m5c = s->m5c;
    d->m60 = s->m60;
    if (d->m60 != 0) {
        volatile long* p = (volatile long*)((char*)d->m60 + 8);
        long one = 1;
        _InterlockedExchangeAdd(p, one);
    }
    return d;
}

// =============================================================================================
// 0x00ae3b30 -- select the next record (by key or by lowest timer) and trigger it.
// @ 0x00ae3b30
bool Sim::Select(char flag, void* key)
{
    int idx = -1;
    if (key != 0) {
        idx = 1;
        for (; idx < mDeclAc; ++idx) {
            Rec* r = (Rec*)((char*)mpBegin + idx * 0x64);
            int mine = r->mHandle38;
            int theirs = (*(int(__thiscall**)(void*))(*(uint*)key + 0x58))(key);
            if (mine != theirs)
                continue;
            if (r->mDone30 != 0)
                break;
        }
        if (idx >= mDeclAc)
            return false;
    } else {
        int best = 0x7fffffff;
        for (int i = 1; i < mDeclAc; ++i) {
            Rec* r = (Rec*)((char*)mpBegin + i * 0x64);
            if (r->mDone30 == 0 && *(int*)((char*)r + 0x28) < best) {
                best = *(int*)((char*)r + 0x28);
                idx = i;
            }
        }
    }
    if (idx == -1)
        return false;

    --mCurB0;
    ((cSPTimer*)&mTimer58)->Restart();
    Rec* r = (Rec*)((char*)mpBegin + idx * 0x64);
    r->mDone30 = 1;
    r->mFlag40 = (uint8)flag;
    FUN_00b9f9b0(r);

    if (mDeclAc - mCurB0 - 1 < 2) {
        void* cfg = (void*)ConfigManager();
        if ((*(int(__thiscall**)(void*, int))(*(uint*)cfg + 0x30))(cfg, 0x04ea96cb) != 0 &&
            flag == 0) {
            void* o = FUN_00b993c0((int)r->mObj00);
            (*(void(__thiscall**)(void*))(*(uint*)((char*)o + 0x34) + 0x2c))((char*)o + 0x34);

            void* so = EAAllocate(0xdc, "Simulator", 0, 0, 0, 0);
            if (so != 0) {
                SpatialObjectCtor(so);
                *(uint*)((char*)so + 0xd4) = 0x013ef094;
                *(uint*)((char*)so + 0xd8) = 0;
                *(uint*)((char*)so + 0x00) = 0x0145a5d8;
                *(uint*)((char*)so + 0xd4) = 0x0145a5d0;
                (*(void(__thiscall**)(void*))(*(uint*)so + 0xbc))(so);
            }
            (*(void(__thiscall**)(void*, void*))(*(uint*)so + 0x38))(so, key);
            void* o2 = FUN_00b993c0((int)r->mObj00);
            uint  v = (*(uint(__thiscall**)(void*))(*(uint*)((char*)o2 + 0x34) + 0x30))((char*)o2 + 0x34);
            (*(void(__thiscall**)(void*, uint))(*(uint*)so + 0x3c))(so, v);

            char tgt[8];
            cActionTarget_ctor(tgt, so, 0);
            cTriggerMgr_PostAction((void*)TriggerMgr(), 0xb232ef6d, tgt, 0);
            cActionTarget_dtor(tgt);
            (*(void(__thiscall**)(void*))(*(uint*)so + 0xc0))(so);
        }
    }
    return true;
}

// =============================================================================================
// 0x00ae3d40 -- is the given id present among the record +0x38 fields?
// @ 0x00ae3d40
bool Sim::HasId(int id)
{
    int i = 0;
    char* r = (char*)mpBegin + 0x38;
    int n = mDeclAc;
    for (; i < n; ++i, r += 0x64) {
        if (*(int*)r == id)
            return false;
    }
    return true;
}

// =============================================================================================
// 0x00ae3d70 -- property-driven terraforming pass over the record array.
// @ 0x00ae3d70
void Sim::TerraformPass()
{
    char* end = (char*)mpEnd;
    for (char* r = (char*)mpBegin; r != end; r += 0x64) {
        void* pm = (void*)PropertyManager();
        void* prop = 0;
        bool ok = (*(bool(__thiscall**)(void*, uint, uint, void**))(*(uint*)pm + 0x2c))(
                      pm, *(uint*)(r + 0x40), *(uint*)(r + 0x48), &prop);
        if (ok) {
            float a = DAT_0145b9c4;
            float b = DAT_01441a88;
            if (prop != 0) {
                void* q;
                if ((*(bool(__thiscall**)(void*, uint, void**))(*(uint*)prop + 0x24))(prop, 0x04408ed7, &q) &&
                    *(uint16*)((char*)q + 0x12) == 0xd) {
                    if ((*(uint*)((char*)q + 0x10) & 0x30) != 0)
                        q = *(void**)q;
                    a = *(float*)q;
                }
                void* q2;
                if ((*(bool(__thiscall**)(void*, uint, void**))(*(uint*)prop + 0x24))(prop, 0x05d52e51, &q2) &&
                    *(uint16*)((char*)q2 + 0x12) == 0xd) {
                    if ((*(uint*)((char*)q2 + 0x10) & 0x30) != 0)
                        q2 = *(void**)q2;
                    b = *(float*)q2;
                }
            }
            float pos[3];
            pos[0] = *(float*)(r + 4);
            pos[1] = *(float*)(r + 8);
            pos[2] = *(float*)(r + 0xc);
            void* tm = TerraformingManager(pos, a + b);
            FUN_00bbf730(tm, a + b);
        }
    }
}
