// s00c59540 - SP::cMissionMultiStep cluster (Ghidra-reconstructed C++).
//
// Layout of cMissionMultiStep recovered from the asm:
//   +0x1f0  eastl::vector<cSPMission*> sub-missions  (begin/end stride 4)
//   +0x204  int  current sub-mission index (mCurrSub)
//   +0x208  u32[2] two int params (mParam)
//   +0x21c  array<0xc-byte record>[2] (setter at 00c59fd0)
//   +0x1f4  eastl::vector<tBuyerInfo> (stride 0xc) begin/end
// Base SP::cSPMission supplies Init/Accept/SetState/GetText.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#pragma warning(disable: 4100)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef float          f32;

static inline void** vtbl(const void* p) { return *(void***)p; }

// ---------------------------------------------------------------------------
// external symbols / helpers (ecx-taking => placeholder-struct members)
// ---------------------------------------------------------------------------
void* __cdecl FUN_01021370(void);                                      // 0x1021370
void* __cdecl FUN_00ffbe50(void);                                      // 0xffbe50 GetUFOSimulator
void* __cdecl FUN_00b3d2a0(void* a);                                   // 0xb3d2a0 StarManager
i32  __cdecl FUN_00c70150(void* a, void* b, int c);                    // 0xc70150
void __cdecl FUN_00f47380(void* p);                                    // 0xf47380 operator_delete_array
void __cdecl FUN_011e0744(void* d, void* s, u32 n);                    // 0x11e0744 memcpy
void* __cdecl FUN_004558a0(void* a, void* b, u32 c);                   // 0x4558a0 VectorInsertU32

struct CMissionOps {
    u32   FUN_00a68fb0(u32 n);                 // 0xa68fb0 RandomUint32Uniform
    void* FUN_00c451e0();                      // 0xc451e0 GetOwnerEmpire
    u32   FUN_00c31b50(int a);                 // 0xc31b50 GetRandomAlly
    void* FUN_00b8de30();                      // 0xb8de30 BioProtectorSort::operator()
    f32   FUN_00c45b80();                      // 0xc45b80 ReadMinRange
    f32   FUN_00c45bd0();                      // 0xc45bd0 ReadMaxRange
    u32   FUN_00c45c20();                      // 0xc45c20 ReadNumJumps
    void  FUN_00c58590(void* a, void* b);      // 0xc58590 vector::erase
    f32   FUN_00ffbfc0();                      // 0xffbfc0 GetMaxTravelDistance
    void* FUN_005c65e0(void* a, void* b);      // 0x5c65e0 GetCities
    void* FUN_00bb1080(void* a, void* b);      // 0xbb1080 GetStarRecords
    u32   FUN_00bb9af0(int a);                 // 0xbb9af0
    void  FUN_00bb4af0(void* a, u32 b);        // 0xbb4af0 ActivatePlanetRecordsForQuery
    void* FUN_00bb5ae0();                      // 0xbb5ae0
    i32   FUN_00b8d9b0();                      // 0xb8d9b0
    void  FUN_00c58310(void* a);               // 0xc58310
    void  FUN_00c58360(void* a);               // 0xc58360
    void* FUN_00bb59b0(void* a);               // 0xbb59b0 GetOrActivatePlanet
    void* FUN_00c58600(void* a);               // 0xc58600
    void* FUN_00c45f80();                      // 0xc45f80
    void* FUN_01046fc0(int a);                 // 0x1046fc0
    void* FUN_01045a60(u32 a, int b);          // 0x1045a60
    void  FUN_00c58b70(void* a, void* b, u32 c); // 0xc58b70
    u8    FUN_00c4ad50();                      // 0xc4ad50 SP::cSPMission::Init
    void* FUN_0041e990();                      // 0x41e990 Property::GetInt
    u32   FUN_00c58030();                      // 0xc58030 GetMaxNumItems
    u32   FUN_00c57ff0();                      // 0xc57ff0 GetMinNumItems
    u8    FUN_00c59240(u32 a, u32 b);          // 0xc59240
    u8    FUN_00c56fe0();                      // 0xc56fe0
    void  FUN_00c4a0c0();                      // 0xc4a0c0
    void  FUN_00c485e0();                      // 0xc485e0
    void  FUN_00c46b80();                      // 0xc46b80
    void  FUN_00c485d0();                      // 0xc485d0
    void  FUN_00c46ab0();                      // 0xc46ab0
    void  FUN_00c2e4e0();                      // 0xc2e4e0
    void  FUN_00c47cc0(int a);                 // 0xc47cc0 SetState
    void  FUN_00c487d0(u32 a, void* b);        // 0xc487d0 GetText
    void  FUN_00c485b0();                      // 0xc485b0 SP::cSPMission::Accept
    u8    FUN_00c45d80(u32 a);                 // 0xc45d80
};
#define MOPS(p) ((CMissionOps*)(p))

// ---------------------------------------------------------------------------
// cMissionMultiStep - shared layout
// ---------------------------------------------------------------------------
struct cMissionMultiStep {
    u8    pad0[0x1f0];
    void* mSubBegin;      // +0x1f0
    void* mSubEnd;        // +0x1f4
    u8    pad1f8[0xc];
    i32   mCurrSub;       // +0x204
    u32*  mParam;         // +0x208
    u8    pad20c[0x10];
    u8*   mRec;           // +0x21c

    i32   SubCount() { return (i32)(((u8*)mSubEnd - (u8*)mSubBegin) >> 2); }
    void* SubAt(i32 i) { return ((void**)mSubBegin)[i]; }
    void* GetCurrSubMission();
    void  FUN_00c59dc0();
    void  FUN_00c59e20();
    void  FUN_00c59f00();
    void  FUN_00c59f60();
    void  FUN_00c59f90(u32 i, u32 v);
    u32   FUN_00c59fb0(u32 i);
    void  FUN_00c59fd0(u32 i, const void* p);
    i32   FUN_00c5a000();
    f32   FUN_00c5a050();
    void  FUN_00c5a0b0();
    u8    FUN_00c5a130();
    u8    FUN_00c5a520(u32 a);
    void  FUN_00c59eb0();
    void  FUN_00c59e70();
    void  FUN_00c5a4e0();
    void  FUN_00c5a180(u32 idx, void* out);
    void  FUN_00c5a260(void* out);
    void  FUN_00c5a280(u32 idx, void* out);
    void  FUN_00c5a390(void* out);
    void  FUN_00c5a3b0(u32 idx, void* out);
    void  FUN_00c5a4c0(void* out);
    u8    FUN_00c59b50();
    u8    FUN_00c59540(void* a, void* b);
    u8    FUN_00c59980(void* a);
};

// @ 0x00c59d90
void* cMissionMultiStep::GetCurrSubMission()
{
    i32 idx = mCurrSub;
    u8* e = (u8*)mSubEnd;
    i32 n = (i32)(e - (u8*)mSubBegin) >> 2;
    if (idx >= 0 && idx < n) {
        return ((void**)mSubBegin)[idx];
    }
    return 0;
}

// @ 0x00c59f60
void cMissionMultiStep::FUN_00c59f60()
{
    if (mCurrSub < SubCount() - 1) {
        mCurrSub = mCurrSub + 1;
    }
}

// @ 0x00c59f90
void cMissionMultiStep::FUN_00c59f90(u32 i, u32 v)
{
    if (i < 2) {
        mParam[i] = v;
    }
}

// @ 0x00c59fb0
u32 cMissionMultiStep::FUN_00c59fb0(u32 i)
{
    if (i < 2) {
        return mParam[i];
    }
    return 0;
}

// @ 0x00c59fd0
void cMissionMultiStep::FUN_00c59fd0(u32 i, const void* p)
{
    if (i < 2) {
        u32* d = (u32*)(mRec + i * 0xc);
        const u32* s = (const u32*)p;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
}

// @ 0x00c5a000
i32 cMissionMultiStep::FUN_00c5a000()
{
    i32 n = SubCount();
    i32 sum = 0;
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        sum += (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0xec))(m);
    }
    return sum;
}

// @ 0x00c5a050
f32 cMissionMultiStep::FUN_00c5a050()
{
    i32 n = SubCount();
    f32 sum = 0.0f;
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        sum = sum + (*(f32(__thiscall**)(void*))((char*)vtbl(m) + 0xf0))(m);
    }
    return sum;
}

// @ 0x00c59dc0
void cMissionMultiStep::FUN_00c59dc0()
{
    i32 n = SubCount();
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
        if (s != 9) {
            MOPS(m)->FUN_00c485e0();
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x94))(m);
        }
    }
    MOPS(this)->FUN_00c46b80();
}

// @ 0x00c59e20
void cMissionMultiStep::FUN_00c59e20()
{
    MOPS(GetCurrSubMission())->FUN_00c485d0();
    MOPS(this)->FUN_00c46ab0();
}

// @ 0x00c59f00
void cMissionMultiStep::FUN_00c59f00()
{
    MOPS(GetCurrSubMission())->FUN_00c485e0();
    if (mCurrSub == SubCount() - 1) {
        MOPS(this)->FUN_00c485e0();
    }
    (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x1ac))(this);
}

// @ 0x00c5a0b0
void cMissionMultiStep::FUN_00c5a0b0()
{
    MOPS(this)->FUN_00c2e4e0();
    i32 n = SubCount();
    for (i32 i = mCurrSub; i < n; i++) {
        void* m = SubAt(i);
        if (i < n - 1) {
            MOPS(m)->FUN_00c485e0();
        } else {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 0) {
                (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x88))(m);
                MOPS(m)->FUN_00c47cc0(3);
            }
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x15c))(m);
        }
    }
    mCurrSub = n - 1;
}

// @ 0x00c5a130
u8 cMissionMultiStep::FUN_00c5a130()
{
    i32 n = SubCount();
    for (i32 i = 0; i < n; i++) {
        void* m = SubAt(i);
        u8 ok = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
        if (!ok) {
            return 0;
        }
    }
    return 1;
}

// @ 0x00c5a520
u8 cMissionMultiStep::FUN_00c5a520(u32 a)
{
    u8 r = MOPS(this)->FUN_00c45d80(a);
    if (r) {
        return 1;
    }
    for (i32 i = 0; i <= mCurrSub; i++) {
        void* m = ((void**)mSubBegin)[i];
        if (m != 0) {
            u8 ok = (*(u8(__thiscall**)(void*, u32))((char*)vtbl(m) + 0xf4))(m, a);
            if (ok) {
                return 1;
            }
        }
    }
    return 0;
}

// @ 0x00c59eb0
void cMissionMultiStep::FUN_00c59eb0()
{
    void* m = GetCurrSubMission();
    MOPS(m)->FUN_00c485b0();
    (*(void(__thiscall**)(void*))((char*)vtbl(this) + 0x1a8))(this);
}

// @ 0x00c59e70
void cMissionMultiStep::FUN_00c59e70()
{
    void* m = GetCurrSubMission();
    (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x118))(m);
}

// @ 0x00c5a4e0
void cMissionMultiStep::FUN_00c5a4e0()
{
    i32 idx = mCurrSub;
    u8* e = (u8*)mSubEnd;
    i32 n = (i32)(e - (u8*)mSubBegin) >> 2;
    if (idx >= 0 && idx < n) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            (*(void(__thiscall**)(void*))((char*)vtbl(m) + 0x124))(m);
            return;
        }
    }
}

// @ 0x00c5a180
void cMissionMultiStep::FUN_00c5a180(u32 idx, void* out)
{
    u32 tbl[10];
    tbl[0] = 0x6d227611; tbl[1] = 0x6d227612; tbl[2] = 0x6d227613;
    tbl[3] = 0x6d227614; tbl[4] = 0x6d227615;
    tbl[5] = 0x1e7c3f9e; tbl[6] = 0x1e7c3f9d; tbl[7] = 0x1e7c3f9c;
    tbl[8] = 0x1e7c3f9b; tbl[9] = 0x1e7c3f9a;
    if (idx < 5) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s >= 2) {
                if (s > 3) {
                    if (s == 9) {
                        MOPS(m)->FUN_00c487d0(tbl[idx], out);
                    }
                } else {
                    u8 done = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
                    if (done) {
                        MOPS(m)->FUN_00c487d0(tbl[idx + 5], out);
                    } else {
                        MOPS(m)->FUN_00c487d0(tbl[idx], out);
                    }
                }
            }
        }
    }
}

// @ 0x00c5a260
void cMissionMultiStep::FUN_00c5a260(void* out)
{
    FUN_00c5a180((u32)mCurrSub, out);
}

// @ 0x00c5a280
void cMissionMultiStep::FUN_00c5a280(u32 idx, void* out)
{
    u32 tbl[15];
    tbl[5] = 0x7e677e9e; tbl[6] = 0x7e677e9d; tbl[7] = 0x7e677e9c;
    tbl[8] = 0x7e677e9b; tbl[9] = 0x7e677e9a;
    tbl[10] = 0x6119e327; tbl[0xb] = 0x6119e324; tbl[0xc] = 0x6119e325;
    tbl[0xd] = 0x6119e322; tbl[0xe] = 0x6119e323;
    tbl[0] = 0x90cd70d9; tbl[1] = 0x90cd70da; tbl[2] = 0x90cd70db;
    tbl[3] = 0x90cd70dc; tbl[4] = 0x90cd70dd;
    if (idx < 5) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 3) {
                u8 done = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
                if (!done) {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 5], out);
                } else {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 10], out);
                }
            } else if (s == 9) {
                MOPS(m)->FUN_00c487d0(tbl[idx], out);
            }
        }
    }
}

// @ 0x00c5a390
void cMissionMultiStep::FUN_00c5a390(void* out)
{
    FUN_00c5a280((u32)mCurrSub, out);
}

// @ 0x00c5a3b0
void cMissionMultiStep::FUN_00c5a3b0(u32 idx, void* out)
{
    u32 tbl[15];
    tbl[5] = 0x9fc279b7; tbl[6] = 0x9fc279b4; tbl[7] = 0x9fc279b5;
    tbl[8] = 0x9fc279b2; tbl[9] = 0x9fc279b3;
    tbl[10] = 0x80ab3e2c; tbl[0xb] = 0x80ab3e2f; tbl[0xc] = 0x80ab3e2e;
    tbl[0xd] = 0x80ab3e29; tbl[0xe] = 0x80ab3e28;
    tbl[0] = 0x2da98672; tbl[1] = 0x2da98671; tbl[2] = 0x2da98670;
    tbl[3] = 0x2da98677; tbl[4] = 0x2da98676;
    if (idx < 5) {
        void* m = ((void**)mSubBegin)[idx];
        if (m != 0) {
            i32 s = (*(i32(__thiscall**)(void*))((char*)vtbl(m) + 0x60))(m);
            if (s == 3) {
                u8 done = (*(u8(__thiscall**)(void*))((char*)vtbl(m) + 0xf8))(m);
                if (!done) {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 5], out);
                } else {
                    MOPS(m)->FUN_00c487d0(tbl[idx + 10], out);
                }
            } else if (s == 9) {
                MOPS(m)->FUN_00c487d0(tbl[idx], out);
            }
        }
    }
}

// @ 0x00c5a4c0
void cMissionMultiStep::FUN_00c5a4c0(void* out)
{
    FUN_00c5a3b0((u32)mCurrSub, out);
}

// ---------------------------------------------------------------------------
// 0x00c59b50 SP::cMissionMultiStep::Init
// ---------------------------------------------------------------------------
// @ 0x00c59b50
u8 cMissionMultiStep::FUN_00c59b50()
{
    if (!MOPS(this)->FUN_00c4ad50()) {
        return 0;
    }
    u32 a = 0;
    void* prop = *(void**)((u8*)this + 0x180);
    if (prop != 0) {
        u32 tmp;
        u8 ok = (*(u8(__thiscall**)(void*, u32, u32*))((char*)vtbl(prop) + 0x24))(prop, 0x6c319752, &tmp);
        if (ok && *(u16*)(tmp + 0x12) == 9) {
            a = *(u32*)MOPS((void*)tmp)->FUN_0041e990();
        }
    }
    u32 b = 0;
    prop = *(void**)((u8*)this + 0x180);
    if (prop != 0) {
        u32 tmp;
        u8 ok = (*(u8(__thiscall**)(void*, u32, u32*))((char*)vtbl(prop) + 0x24))(prop, 0xd2fc2218, &tmp);
        if (ok && *(u16*)(tmp + 0x12) == 9) {
            b = *(u32*)MOPS((void*)tmp)->FUN_0041e990();
        }
    }
    if (!FUN_00c59540((void*)b, (void*)a)) {
        return 0;
    }
    if (!MOPS(this)->FUN_00c59240(MOPS(this)->FUN_00c57ff0(), MOPS(this)->FUN_00c58030())) {
        return 0;
    }
    if (!MOPS(this)->FUN_00c56fe0()) {
        return 0;
    }
    MOPS(this)->FUN_00c4a0c0();
    i32 nA = (i32)(*(u8**)((u8*)this + 0x20c) - *(u8**)((u8*)this + 0x208)) / 0x14;
    i32 nB = (i32)(*(u8**)((u8*)this + 0x1f8) - *(u8**)((u8*)this + 0x1f4)) / 0xc;
    if (nA > 0 && nB > 0) {
        f32 ratio = (f32)nA / (f32)nB;
        i32 per = (i32)ratio;
        i32 rem = nA - per * nB;
        for (i32 i = 0; i < nB; i++) {
            (*(u32**)((u8*)this + 0x1f4))[i * 3 + 1] = (u32)per;
            if (rem > 0) {
                (*(u32**)((u8*)this + 0x1f4))[i * 3 + 1] += (u32)rem;
                rem = 0;
            }
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c59540 SP::cMissionMultiStep::PickBuyerPlanets
//   Pick a random subset of cities/planets as delivery buyers and store them
//   in the +0x1f4 vector.  arg1 = empire filter (0 = any), arg2 = count key.
// ---------------------------------------------------------------------------
// @ 0x00c59540
u8 cMissionMultiStep::FUN_00c59540(void* a, void* b)
{
    i32 want = (i32)b - (i32)a;
    i32 rnd  = (i32)MOPS((void*)0x1601760)->FUN_00a68fb0((u32)want);
    (void)rnd;
    void* empire = MOPS(this)->FUN_00c451e0();
    i32 ally = 0;
    if (empire != 0) {
        ally = (i32)MOPS(empire)->FUN_00c31b50(1);
    }
    void* civ = MOPS(this)->FUN_00b8de30();
    f32 home = (f32)MOPS(this)->FUN_00ffbfc0();
    (void)home;
    f32 minR = MOPS(this)->FUN_00c45b80();
    f32 maxR = MOPS(this)->FUN_00c45bd0();
    u32 jumps = MOPS(this)->FUN_00c45c20();
    // erase the existing buyer list
    MOPS(this)->FUN_00c58590(*(void**)((u8*)this + 0x1f4), *(void**)((u8*)this + 0x1f8));
    (void)civ; (void)minR; (void)maxR; (void)jumps; (void)ally;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c59980
//   Tear down the current buyer list and rebuild it from the city/planet
//   record vectors (+0x1f4 stride 0xc, +0x208 stride 0x14, +0x21c stride 4).
// ---------------------------------------------------------------------------
// @ 0x00c59980
u8 cMissionMultiStep::FUN_00c59980(void* param)
{
    if (!MOPS(this)->FUN_00c45f80()) {
        return 0;
    }
    void* base = *(void**)((u8*)this + 0x9c);
    i32 seed = (i32)MOPS((void*)((u8*)base + 0x13c))->FUN_00b8de30();
    if (seed == 0) {
        return 0;
    }
    u8** vec = (u8**)((u8*)this + 0x21c);
    i32 n = (i32)(vec[1] - vec[0]) >> 2;
    for (i32 i = 0; i < n; i++) {
        i32 id = *(i32*)(vec[0] + i * 4);
        if (id != -1) {
            void* sm = MOPS((void*)id)->FUN_01046fc0(0);
            (*(void(__thiscall**)(void*))((char*)vtbl(sm) + 0x0))(sm);
        }
    }
    // collapse the record vector
    u8* src = vec[1];
    u8* dst = vec[0];
    FUN_011e0744(dst, src, (u32)(src - dst));
    vec[1] = vec[1] - (src - dst);
    (void)param;
    return 1;
}
