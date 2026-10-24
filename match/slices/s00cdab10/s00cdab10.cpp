// match/slices/s00cdab10/s00cdab10.cpp
// SP::cTribeModeStrategy goal-progress bookkeeping and tribe-simulator helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;
typedef double         f64;

#define VT(p)   (*(void***)(p))
#define MOPS(p) ((COps*)(p))

// ---------------------------------------------------------------------------
// Placeholder struct: every ecx-passed callee is declared here as a member so
// the call site emits `mov ecx, <this>` + `call rel32`.
// ---------------------------------------------------------------------------
struct COps {
    void  FUN_00bc3110();                          // 0x00bc3110 cSPTimer::Stop
    void  FUN_00bc3130();                          // 0x00bc3130 cSPTimer::Restart
    void* FUN_00bfc5f0();                          // 0x00bfc5f0 GetPlayerTribe
    void* FUN_00c90460();                          // 0x00c90460
    void* FUN_00c8e820();                          // 0x00c8e820 GetSlot0
    void  FUN_00c8dc10(u32, void*);                // 0x00c8dc10 TP_AddSegment
    void* FUN_00f67d90();                          // 0x00f67d90 GetCurrentTerrainSphere
    void* FUN_00b21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void  FUN_00676e90(u32, u32);                  // 0x00676e90 AutoTest
    void  FUN_00b48770(u32);                       // 0x00b48770
    f32   FUN_00e3f7a0();                          // 0x00e3f7a0
    f32   FUN_00d05a20(void*, void*, void*);       // 0x00d05a20 CalculateRelationshipAbsolute
    void  FUN_00ad7a30(void*, void*);              // 0x00ad7a30 cActionTarget ctor
    void  FUN_00ad7ad0();                          // 0x00ad7ad0 cActionTarget dtor
    void  FUN_00adde90(u32, void*, void*);         // 0x00adde90 cStringContext
    void* FUN_00ae0930(u32, u32, u32, u32, u32, u32); // 0x00ae0930 PostTrigger
    void  FUN_00ae09b0(u32, void*);                // 0x00ae09b0 PostAction
    void  FUN_00c79f00(u32, void*);                // 0x00c79f00
    void  FUN_00cda370();                          // 0x00cda370 UpgradePlayerTribe
    void  FUN_00cd7c70(u32);                       // 0x00cd7c70
    void  FUN_00cd3ee0();                          // 0x00cd3ee0
    void* FUN_00cd4720(u32, u32);                  // 0x00cd4720 record ctor
    void  FUN_00ce0a20();                          // 0x00ce0a20 cTribePlanner::Shutdown
    u8    FUN_00c744e0(void*);                     // 0x00c744e0
};

void* __cdecl FUN_00b3d300();                       // 0x00b3d300 NounManager
void* __cdecl FUN_00b3d330();                       // 0x00b3d330 SimTicker
void* __cdecl FUN_00b3d4d0();                       // 0x00b3d4d0 GetTriggerMgr
void* __cdecl FUN_00675250(u32, u32);               // 0x00675250 Achievements::Controller
void* __cdecl FUN_0067dcc0();                       // 0x0067dcc0 MessageServer
void  __cdecl FUN_00cd98e0(u32);                    // 0x00cd98e0
void  __cdecl FUN_00cd3f20(u32);                    // 0x00cd3f20 SetTerrainSphereParam
void* __cdecl FUN_00b6f0c0(u32);                    // 0x00b6f0c0
void  __cdecl FUN_00e398e0(u32, void*);             // 0x00e398e0
void* __cdecl FUN_00b3d310(void*, u32);             // 0x00b3d310
void  __cdecl FUN_00cd9660(void*);                  // 0x00cd9660
void  __cdecl FUN_00f47380(void*);                  // 0x00f47380 operator_delete_array
void* __cdecl FUN_00f473a0(u32, const char*, u32, u32, const char*, u32); // 0x00f473a0 operator_new
void* __cdecl FUN_00b3d2c0();                       // 0x00b3d2c0 RelationshipManager
void* __cdecl FUN_01021260();                       // 0x01021260
s32   __cdecl FUN_00ac8fa0(u32, u32, u32);          // 0x00ac8fa0
void  __cdecl FUN_0093a780(void*, void*, u32, u32); // 0x0093a780 ReadInt32
void  __cdecl FUN_00567e70(u32*, void*);            // 0x00567e70
void* __cdecl FUN_011e0744(void*, const void*, u32); // 0x011e0744 memcpy

// EASTL container helpers used by the insert paths.
void  __cdecl FUN_00cd7010(void*);                  // 0x00cd7010
void  __cdecl FUN_00cd67b0(void*, void*, void*);    // 0x00cd67b0
void* __cdecl FUN_00cd70c0(void*, void*, void*);    // 0x00cd70c0
void  __cdecl FUN_00cd6710(void*, void*, void*);    // 0x00cd6710
void  __cdecl FUN_00cd6030(void*, void*);           // 0x00cd6030 eastl::wstring::assign
void  __cdecl FUN_00cd7d60(void*, u32, void*);      // 0x00cd7d60 uninitialized_fill_n
f32   __cdecl FUN_00cdb8b0();                       // 0x00cdb8b0
void* __cdecl FUN_00b3d410(u32);                    // 0x00b3d410

extern f32 gF_013f26dc;   // 0x013f26dc  ( 1/3)
extern f32 gF_0140d0cc;   // 0x0140d0cc  (-1/3)
extern f32 gF_013eb1bc;   // 0x013eb1bc  (-1.0)
extern f32 gF_01485720;   // 0x01485720  ( 1.0)

struct Global169b41c {
    u8    pad000[0x1c];
    void* mpObj;          // 0x1c
};
extern Global169b41c* gP_0169b41c;   // 0x0169b41c

// ---------------------------------------------------------------------------
// Slice-local record / container layouts.
// ---------------------------------------------------------------------------
struct Rec16 {
    void* mpVtbl;         // 0x00
    void* mU_04;          // 0x04
    void* mpObj;          // 0x08
    u8    mB_0c;          // 0x0c
    u8    mPad0d[3];      // 0x0d
};

struct Rec1c {
    void* mpBegin;        // 0x00  eastl::wstring storage
    void* mpEnd;          // 0x04
    void* mpCap;          // 0x08
    u32   mU_0c;          // 0x0c
    u32   mU_10;          // 0x10
    u32   mU_14;          // 0x14
    u32   mU_18;          // 0x18
};

struct cSPVector3 {
    f32 x, y, z;          // 0x00
    f32 mF_0c;            // 0x0c
    f32 mF_10;            // 0x10
};

struct TerrainSphere {
    u8  mPad0000[0x10f0];
    f32 mF_10f0;          // 0x10f0
    f32 mF_10f4;          // 0x10f4
};

struct TribeData {
    u8   mPad000[0x108];
    u32* mpIndexArray;    // 0x108
    u8   mPad10c[0x11c - 0x10c];
    u32* mpBegin;         // 0x11c
    u32* mpEnd;           // 0x120
};

struct GameData {
    u8   mPad000[0x11c];
    u32* mpBegin;         // 0x11c
    u32* mpEnd;           // 0x120
    u8   mPad124[0x234 - 0x124];
    void* mpTribe;        // 0x234
};

// Generic eastl vector of pointers, as returned by GetGameDataVector.
struct PtrVec {
    u32    mU_00;         // 0x00
    void** mpBegin;       // 0x04
    void** mpEnd;         // 0x08
};

class cVec16 {
public:
    Rec16* mpBegin;       // 0x00
    Rec16* mpEnd;         // 0x04
    Rec16* mpCap;         // 0x08
    void FUN_00cd9440(Rec16*, Rec16*);  // 0x00cd9440
    void FUN_00cd9490(Rec16*, Rec16*);  // 0x00cd9490
    void FUN_00cd7c70(u32);             // 0x00cd7c70
    void FUN_00cdafb0(Rec16*);          // 0x00cdafb0
};

class cVec1c {
public:
    Rec1c* mpBegin;       // 0x00
    Rec1c* mpEnd;         // 0x04
    Rec1c* mpCap;         // 0x08
    void FUN_00cdb1f0(Rec1c*, Rec1c*);  // 0x00cdb1f0
    void FUN_00cdb430();                // 0x00cdb430
};

class cVec14 {
public:
    cSPVector3* mpBegin;  // 0x00
    cSPVector3* mpEnd;    // 0x04
    cSPVector3* mpCap;    // 0x08
    void FUN_00cdb6a0(cSPVector3*, u32, cSPVector3*); // 0x00cdb6a0
};

class cTribeModeStrategy {
public:
    u8     mPad000[0x40];
    Rec16* mpHistBegin;   // 0x40
    Rec16* mpHistEnd;     // 0x44
    u8     mPad048[0x10];
    u8     mTimer[8];     // 0x58
public:
    void FUN_00cdab10();                // 0x00cdab10 IncrementGoalProgress
    void FUN_00cdb3a0(u32, u32);        // 0x00cdb3a0
    u32  FUN_00cdba50();                // 0x00cdba50
    void FUN_00cdba90();                // 0x00cdba90 UnregisterTribeSimulators
};

// ===========================================================================
// 0x00cdafb0: append a 0x10-byte record, AddRef-ing the embedded object.
// ===========================================================================
// @ 0x00cdafb0
void cVec16::FUN_00cdafb0(Rec16* src)
{
    Rec16* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mpVtbl = (void*)0x14774c4;
            end->mU_04 = src->mU_04;
            void* obj = src->mpObj;
            end->mpObj = obj;
            if (obj != 0)
                ((void (__thiscall*)(void*))VT(obj)[0])(obj);
            end->mB_0c = src->mB_0c;
        }
    } else {
        FUN_00cd9490(end, src);
    }
}

// ===========================================================================
// 0x00cdb430: append an empty 0x1c-byte string record (slow path inserts it).
// ===========================================================================
// @ 0x00cdb430
void cVec1c::FUN_00cdb430()
{
    Rec1c* end = mpEnd;
    if (end < mpCap) {
        mpEnd = end + 1;
        if (end != 0) {
            end->mpBegin = (void*)0x1667bac;
            end->mpEnd   = (void*)0x1667bac;
            end->mpCap   = (void*)0x1667bae;
            end->mU_14 = 0;
            end->mU_18 = 0;
        }
    } else {
        Rec1c tmp;
        tmp.mpBegin = (void*)0x1667bac;
        tmp.mpEnd   = (void*)0x1667bac;
        tmp.mpCap   = (void*)0x1667bae;
        tmp.mU_14 = 0;
        tmp.mU_18 = 0;
        FUN_00cdb1f0(end, &tmp);
        s32 rem = (s32)((u32)((u8*)tmp.mpCap - (u8*)tmp.mpBegin) & 0xfffffffe);
        if (rem > 2 && tmp.mpBegin != 0)
            FUN_00f47380(tmp.mpBegin);
    }
}

// ===========================================================================
// 0x00cdb1f0: insert a 0x1c-byte string record at pos.
// ===========================================================================
// @ 0x00cdb1f0
void cVec1c::FUN_00cdb1f0(Rec1c* pos, Rec1c* src)
{
    Rec1c* end = mpEnd;
    if (end != mpCap) {
        if (pos <= src && src < end)
            src += 1;
        if (end != 0)
            FUN_00cd7010(end - 1);
        FUN_00cd67b0(pos, end - 1, end);
        if (src != pos)
            FUN_00cd6030(src->mpBegin, src->mpEnd);
        pos->mU_10 = src->mU_10;
        pos->mU_14 = src->mU_14;
        pos->mU_18 = src->mU_18;
        mpEnd = end + 1;
        return;
    }
    u32 oldCount = (u32)((u8*)end - (u8*)mpBegin) / 0x1c;
    u32 newCap = oldCount == 0 ? 1 : oldCount * 2;
    Rec1c* buf = (Rec1c*)FUN_00f473a0(newCap * 0x1c, "Simulator", 0, 0, "allocator.h", 0xd1);
    Rec1c* mid = (Rec1c*)FUN_00cd70c0(mpBegin, pos, buf);
    FUN_00cd6710(mpBegin, pos, buf);
    if (mid != 0)
        FUN_00cd7010(src);
    Rec1c* newEnd = (Rec1c*)FUN_00cd70c0(pos, end, mid + 1);
    FUN_00cd6710(pos, end, mid + 1);
    if (mpBegin != 0 && *(u32*)((u8*)mpBegin - 4) != 0)
        FUN_00f47380(mpBegin);
    mpEnd = newEnd;
    mpBegin = buf;
    mpCap = (Rec1c*)((u8*)buf + newCap * 0x1c);
}

// ===========================================================================
// 0x00cdb3a0: if the terrain sphere has room, record the current goal object
// and bump the sphere parameter / restart the timer.
// ===========================================================================
// @ 0x00cdb3a0
void cTribeModeStrategy::FUN_00cdb3a0(u32 a1, u32 a2)
{
    void* te = FUN_00b3d300();
    TerrainSphere* ts = (TerrainSphere*)MOPS(te)->FUN_00f67d90();
    if (ts->mF_10f4 > ts->mF_10f0) {
        u8 recbuf[0x10];
        ((cVec16*)((u8*)this + 0x40))->FUN_00cdafb0(
            (Rec16*)MOPS(recbuf)->FUN_00cd4720(a1, a2));
        Rec16* rec = (Rec16*)recbuf;
        rec->mpVtbl = (void*)0x14774c4;
        void* obj = rec->mpObj;
        if (obj != 0)
            ((void (__thiscall*)(void*))VT(obj)[1])(obj);
        ts->mF_10f0 += gF_01485720;
        MOPS((u8*)this + 0x58)->FUN_00bc3130();
    }
}

// ===========================================================================
// 0x00cdba90: shut down every tribe planner registered with the simulator.
// ===========================================================================
// @ 0x00cdba90
void cTribeModeStrategy::FUN_00cdba90()
{
    void* ticker = FUN_00b3d330();
    void* noun = FUN_00b3d300();
    PtrVec* vec = (PtrVec*)MOPS(noun)->FUN_00b21340((void*)0x00cd7d10,
                                                     (void*)0x00d3d420,
                                                     (void*)0x00accbb0,
                                                     (void*)0x00b1e500,
                                                     (void*)0x018c6d19);
    void*** pbegin = &vec->mpBegin;
    s32 count = (s32)((u8*)vec->mpEnd - (u8*)vec->mpBegin) >> 2;
    for (u32 i = 0; i < (u32)count; i++) {
        u32 item = (u32)(*pbegin)[i];
        void* planner = *(void**)(item + 0x290);
        if (planner != 0) {
            ((void (__thiscall*)(void*, void*))VT(ticker)[0x54 / 4])(ticker, planner);
            MOPS(planner)->FUN_00ce0a20();
        }
    }
}

// ===========================================================================
// 0x00cdba50: classify the relationship score into one of three constants.
// ===========================================================================
// @ 0x00cdba50
u32 cTribeModeStrategy::FUN_00cdba50()
{
    f32 v = FUN_00cdb8b0();
    if (v >= gF_013f26dc)
        return 0x0cac124d;
    if (v >= gF_0140d0cc)
        return 0xc2ca9495;
    return 0x60a78928;
}

// ===========================================================================
// 0x00cdb000: de-serialise a 0x10-byte-record vector from the reader stream.
// ===========================================================================
// @ 0x00cdb000
void __cdecl FUN_00cdb000(void* a1, void* a2)
{
    cVec16* v = (cVec16*)a2;
    v->FUN_00cd9440(v->mpBegin, v->mpEnd);

    u32 count = 0;
    void* reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
    void* stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
    FUN_0093a780(stream, &count, 1, 0);
    v->FUN_00cd7c70(count);

    for (u32 i = 0; i < count; i++) {
        Rec16 tmp;
        tmp.mpVtbl = (void*)0x14774c4;
        tmp.mU_04 = 0;
        tmp.mpObj = 0;
        tmp.mB_0c = 0;
        (*(void (__thiscall**)(void*))0x14774cc)(&tmp);
        v->FUN_00cdafb0(&tmp);
        tmp.mpVtbl = (void*)0x14774c4;
        if (tmp.mpObj != 0)
            ((void (__thiscall*)(void*))VT(tmp.mpObj)[1])(tmp.mpObj);
    }
    ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);
}

// ===========================================================================
// 0x00cdb4c0: de-serialise an ordered pair map (eastl::map-like vector).
// ===========================================================================
// @ 0x00cdb4c0
void __cdecl FUN_00cdb4c0(void* a1, void* a2)
{
    cVec16* v = (cVec16*)a2;
    v->FUN_00cd9440(v->mpBegin, v->mpEnd);

    void* reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
    void* stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
    u32 count = 0;
    FUN_0093a780(stream, &count, 1, 0);

    u32* begin = *(u32**)a2;
    for (u32 i = 0; i < count; i++) {
        u32 key = 0, val = 0;
        reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
        stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
        FUN_0093a780(stream, &key, 1, 0);
        ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);

        reader = ((void* (__thiscall*)(void*))VT(a1)[0x20 / 4])(a1);
        stream = ((void* (__thiscall*)(void*))VT(reader)[0x18 / 4])(reader);
        FUN_0093a780(stream, &val, 1, 0);
        ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);

        u32* end = *(u32**)((u8*)a2 + 4);
        u32* lo = begin;
        u32 n = (u32)(end - begin) / 2;
        while (n > 0) {
            u32 half = n >> 1;
            if ((s32)lo[half * 2] < (s32)key) {
                lo += half * 2 + 2;
                n -= half + 1;
            } else {
                n = half;
            }
        }
        if (lo != end && lo[0] == key) {
            lo[1] = val;
        } else if (end == *(u32**)((u8*)a2 + 8)) {
            u32 pair[2];
            pair[0] = key;
            pair[1] = val;
            FUN_00567e70(lo, pair);
        } else {
            u32* p = end;
            while (p > lo) {
                p[0] = p[-2];
                p[1] = p[-1];
                p -= 2;
            }
            lo[0] = key;
            lo[1] = val;
            *(u32**)((u8*)a2 + 4) = end + 2;
        }
        begin = *(u32**)a2;
    }
    ((void (__thiscall*)(void*))VT(a1)[0x1c / 4])(a1);
}

// ===========================================================================
// 0x00cdb6a0: insert `count` copies of `value` at `pos`.
// ===========================================================================
// @ 0x00cdb6a0
void cVec14::FUN_00cdb6a0(cSPVector3* pos, u32 count, cSPVector3* value)
{
    u32 cur = (u32)((u8*)mpEnd - (u8*)mpBegin) / 0x14;
    if (cur < count) {
        u32 oldCount = (u32)((u8*)mpEnd - (u8*)mpBegin) / 0x14;
        u32 newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        u32 newSize = oldCount + count;
        if (newSize < newCap)
            newSize = newCap;
        cSPVector3* buf = 0;
        if (newSize != 0)
            buf = (cSPVector3*)FUN_00f473a0(newSize * 0x14, "Simulator", 0, 0, "allocator.h", 0xd1);
        u32 pre = (u32)((u8*)pos - (u8*)mpBegin);
        FUN_011e0744(buf, mpBegin, pre);
        cSPVector3* mid = (cSPVector3*)((u8*)buf + pre);
        FUN_00cd7d60(mid, count, value);
        u32 post = (u32)((u8*)mpEnd - (u8*)pos);
        FUN_011e0744((u8*)mid + count * 0x14, pos, post);
        if (mpBegin != 0 && *(u32*)((u8*)mpBegin - 4) != 0)
            FUN_00f47380(mpBegin);
        mpBegin = buf;
        mpEnd = (cSPVector3*)((u8*)mid + post + count * 0x14);
        mpCap = (cSPVector3*)((u8*)buf + newSize * 0x14);
    } else {
        u32 tail = (u32)((u8*)mpEnd - (u8*)pos);
        FUN_011e0744((u8*)pos + count * 0x14, pos, tail);
        FUN_00cd7d60(pos, count, value);
        mpEnd = (cSPVector3*)((u8*)mpEnd + count * 0x14);
    }
}

// ===========================================================================
// 0x00cdb8b0: aggregate the tribe's relationships into a normalised score.
// ===========================================================================
// @ 0x00cdb8b0
f32 __cdecl FUN_00cdb8b0()
{
    void* rm = FUN_00b3d2c0();
    f32 lo = *(f32*)((u8*)rm + 0x10);
    rm = FUN_00b3d2c0();
    f32 hi = *(f32*)((u8*)rm + 0x1c);

    void* planet = FUN_01021260();
    f32 sum = 0.0f;
    if (planet != 0) {
        s32 total = FUN_00ac8fa0(0x01581288, 0xc9ce093a, 5);
        void* noun = FUN_00b3d300();
        void* tribe = MOPS(noun)->FUN_00bfc5f0();
        noun = FUN_00b3d300();
        PtrVec* vec = (PtrVec*)MOPS(noun)->FUN_00b21340((void*)0x00cd7d10,
                                                         (void*)0x00d3d420,
                                                         (void*)0x00accbb0,
                                                         (void*)0x00b1e500,
                                                         (void*)0x018c6d19);
        void** end = vec->mpEnd;
        for (void** p = vec->mpBegin; p != end; p++) {
            void* other = (void*)*p;
            if (other != tribe) {
                u32 id = 0;
                if (MOPS(other)->FUN_00c744e0(&id)) {
                    void* a = ((void* (__thiscall*)(void*))VT(tribe)[0x4c / 4])(tribe);
                    void* b = ((void* (__thiscall*)(void*))VT(other)[0x4c / 4])(other);
                    f32 rel = MOPS(FUN_00b3d2c0())->FUN_00d05a20(a, b, 0);
                    if (rel < lo)
                        rel = lo;
                    if (rel > hi)
                        rel = hi;
                    sum += rel;
                }
            }
        }
        f32 denom = (f32)(u32)total;
        if (total < 0)
            denom += 4294967296.0f;
        sum = -sum / (denom * hi);
    }

    void* g = FUN_00b3d410(0);
    if (g != 0) {
        void* gm = FUN_00b3d410(0xad56080c);
        sum += MOPS(gm)->FUN_00e3f7a0();
    }

    if (sum < gF_013eb1bc)
        sum = gF_013eb1bc;
    if (sum > gF_01485720)
        sum = gF_01485720;
    return sum;
}

// ===========================================================================
// 0x00cdab10: advance the current tribe goal once the goal timer fires.
// ===========================================================================
// @ 0x00cdab10
void cTribeModeStrategy::FUN_00cdab10()
{
    MOPS((u8*)this + 0x58)->FUN_00bc3110();     // stop the goal timer

    void* noun = FUN_00b3d300();
    void* tribe = MOPS(noun)->FUN_00bfc5f0();
    if (tribe == 0)
        return;

    Rec16* end = mpHistEnd;
    if (mpHistBegin == end)
        return;
    Rec16* last = end - 1;
    if (last->mB_0c != 0)
        return;
    last->mB_0c = 1;

    u32 n = (u32)((u8*)end - (u8*)mpHistBegin) >> 4;
    FUN_00cd98e0(n);
    FUN_00cd3f20(n);

    u32 goalId = (u32)last->mU_04;
    void* tribeObj = last->mpObj;
    GameData* gd = (GameData*)MOPS(tribe)->FUN_00c90460();
    if (gd == 0)
        return;

    gP_0169b41c->mpObj = (tribeObj != 0) ? tribeObj : tribe;

    u32 segCount = (u32)((u8*)gd->mpEnd - (u8*)gd->mpBegin) >> 2;

    if (goalId == 1) {
        void* seg = (tribeObj != 0) ? FUN_00b6f0c0(((u32*)tribeObj)[0x8d]) : (void*)0x0157ef60;
        MOPS(gd)->FUN_00c8dc10(0, seg);
        void* ctrl = FUN_00675250(0x8aa440ab, 1);
        MOPS(ctrl)->FUN_00676e90(0x8aa440ab, 1);
        if (tribeObj != 0) {
            void* msg = FUN_0067dcc0();
            ((void (__thiscall*)(void*, u32, u32, u32))VT(msg)[0x14 / 4])(msg, 0x6579712, 0x2ab05c28, 0);
            void* g = MOPS(FUN_00b3d300())->FUN_00bfc5f0();
            void* slot = MOPS(tribeObj)->FUN_00c8e820();
            FUN_00e398e0(0x2a4cbb17, (u8*)slot + 0x504);
            void* list = ((void* (__thiscall*)(void*))VT(tribeObj)[0xbc / 4])(tribeObj);
            u32* lb = *(u32**)list;
            u32* le = *(u32**)((u8*)list + 4);
            for (u32* it = lb; it != le; it++) {
                void* ent = (void*)*it;
                u32 ds = ((u32 (__thiscall*)(void*))VT(ent)[0x58 / 4])(ent);
                if (ds != 10) {
                    u32 dmg = ((u32 (__thiscall*)(void*))VT(ent)[0x48 / 4])(ent);
                    if (dmg != 2) {
                        // feed the combatant position back into the goal record
                        (void)segCount;
                    }
                }
            }
        }
    } else if (goalId == 2) {
        void* seg = (tribeObj != 0) ? FUN_00b6f0c0(((u32*)tribeObj)[0x8d]) : (void*)0x0157ef6c;
        MOPS(gd)->FUN_00c8dc10(1, seg);
        void* ctrl = FUN_00675250(0x7859c5da, 1);
        MOPS(ctrl)->FUN_00676e90(0x7859c5da, 1);
        if (tribeObj != 0) {
            void* msg = FUN_0067dcc0();
            ((void (__thiscall*)(void*, u32, u32, u32))VT(msg)[0x14 / 4])(msg, 0x6579712, 0x2ab05c28, 0);
            void* g = MOPS(FUN_00b3d300())->FUN_00bfc5f0();
            void* slot = MOPS(tribeObj)->FUN_00c8e820();
            FUN_00e398e0(0xf9f6f3dd, (u8*)slot + 0x504);
        }
    }

    // post the totem-pole trigger / action pair
    void* trig = FUN_00b3d4d0();
    void* handle = MOPS(trig)->FUN_00ae0930(0x14777e4, 1, 1, 0, 0, 0);
    u8 action[0x20];
    MOPS(&action)->FUN_00ad7a30((u8*)tribe + 0x34, handle);
    void* trig2 = FUN_00b3d4d0();
    MOPS(trig2)->FUN_00ae09b0(0xa69cf7a6, &action);
    MOPS(&action)->FUN_00ad7ad0();
    u8 ctx[0x20];
    void* trig3 = FUN_00b3d4d0();
    MOPS(trig3)->FUN_00adde90(0x3468d1e3, &ctx, handle);

    TribeData* td = (TribeData*)tribe;
    if (td->mpBegin != td->mpEnd) {
        u32 cnt = (u32)(td->mpEnd - td->mpBegin);
        u32* item = (u32*)td->mpIndexArray[cnt - 1];
        item[1] &= 0xfffffffe;
    }

    void* t2 = FUN_00b3d310(tribe, 1);
    MOPS(t2)->FUN_00b48770(1);
    FUN_00cd9660(tribeObj);
}
