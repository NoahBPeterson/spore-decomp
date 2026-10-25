// slice s00e707d0 -- SPCellGame.obj (batch gold8): cell effect/command helpers.
// FUN_00e707d0 (0x00e707d0, 374 bytes): per-tick update of a timed-effect record. A borrowed
//   record handle (mLayerId via FUN_00e4cc40) is held in a scoped ref, two countdown timers are
//   decremented and, once the record's position is close enough to the avatar, an 8-arg
//   FUN_00e6f800 dispatch is issued.
// FUN_00e70950/00e70bc0: build a "cell command" record (kind 12 / 13) in the command pool.
// FUN_00e70a90/00e70b20: emit a command for one cell (and optionally the pair) unless the cell
//   already carries the pending-command flag at +0x17f.
// FUN_00e70cf0: resolve the current look-at target (own or foreign record) into the +0x220/+0x22c
//   slot pair and load the associated timer from the record.
// FUN_00e70e30 (0x00e70e30, 236 bytes): per-tick countdown of a timed-effect record.
//   Two pool handles (+0x220, +0x22c) are validated through gspCellGame->mCells.GetSafe (thiscall,
//   ret 4); a stale handle clears its timer. The main timer at +0x238 is decremented by dt and,
//   when it goes negative, FUN_00e70cf0(self, arg) runs and the timer is reset to 0.25.
//   Called only from FUN_00e7a0a0 (cdecl, three stack args: self, arg, dt).
// FUN_00e70f20 (0x00e70f20, 992 bytes): the look-at/command driver for one cell: three pool
//   handles (+0x20c/+0x210/+0x214) are pruned when stale, the record is re-read (FUN_00e67cb0)
//   and the selected handle is dispatched through FUN_00e6f940/FUN_00e6f800/FUN_00e6ff60.
// FUN_00e71300 (0x00e71300, 535 bytes): LTCG custom-register ABI -- the cell arrives in ESI and
//   the record id in EDI (see the call site at 0x00e7a44d, which only pushes dt). Plain C++
//   cannot express that frame; reproduced here with explicit parameters (not byte-exact).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef uint32_t uint32;

// gspCellGame (cCellGame*), global at 0x016b3c04; mCells (cObjectPool) is at +0x1c,
// the cell-command pool at +0x54 and the "link" pool at +0xa8; avatar handle at +0x411c.
// Retail loads the singleton pointer from 0x016b3c04 (mov ecx, dword ptr [0x16b3c04]) and then
// adds the pool offset, so the pools are reached through the loaded pointer.
extern char* gspCellGame;
inline char* GetCellGameAddr() { return gspCellGame; }

// 0x016b3c14: the level's default food resource handle (read as the actor entity of the
// borrowed layer record, and used as the avatar entity in the distance test).
extern int g_keyDefaultFood;

namespace SP { extern int memcpy(void* dst, const void* src, unsigned n); }

struct cObjectPool {
    // 0x00b721d0: handle -> element pointer, 0 when the handle is stale. thiscall, `ret 4`.
    void* GetSafe(uint32 handle);
    // 0x00b72210: handle -> element pointer (assumes live). thiscall, `ret 4`.
    void* Get(uint32 handle);
    // 0x00b72160: allocate an element, returns its handle. thiscall, no arguments.
    uint32 Alloc();
};

// 0x00743b50 clears the handle (cModelWorld::VecClear in other TUs), 0x00e82130 releases it.
struct RefHandle {
    void* mPtr;      // +0x00
    void  Clear();   // 0x00743b50 thiscall
    void  Release(); // 0x00e82130 thiscall
};

// Cell-command record handed to the command pool (layout shared with slice s00e71520).
struct cCellCmd {
    int   mPad00;      // +0x00
    int   mFlags04;    // +0x04
    char  mFlag08;     // +0x08
    char  mPad09[0x1c - 0x09];
    float mTime1c;     // +0x1c
    float mTime20;     // +0x20
    int   mKind24;     // +0x24
    int   mSrc28;      // +0x28
    int   mArg2c;      // +0x2c
    int   mArg30;      // +0x30
    int   mArg34;      // +0x34
    int   mArg38;      // +0x38
    int   mArg3c;      // +0x3c
    float mF40;        // +0x40
    float mF44;        // +0x44
    float mDir48;      // +0x48 (camera forward, twice)
    float mDir4c;      // +0x4c
    float mDir50;      // +0x50
    float mDir54;      // +0x54
    float mDir58;      // +0x58
    float mDir5c;      // +0x5c
    float mBasis60;    // +0x60 (orthogonal basis)
    float mBasis64;    // +0x64
    float mBasis68;    // +0x68
    float mBasis6c;    // +0x6c
    int   mArg70;      // +0x70
    char  mFlag74;     // +0x74
    int   mArg78;      // +0x78
};

// Owner of the timed-effect fields (the cell record; retail offsets from the asm).
struct cTimedHandles {
    int   mId;                            // +0x00 (pool handle)
    int   mPad004;                        // +0x04
    int   mPad008;                        // +0x08
    char  mPad00c[0x14 - 0x0c];           // +0x0c
    int   mQuat[4];                       // +0x14 facing quaternion
    char  mPad024[0x4c - 0x24];           // +0x24
    float mPosX;                          // +0x4c
    float mPosY;                          // +0x50
    float mPosZ;                          // +0x54
    float mRadius;                        // +0x58
    char  mPad05c[0x108 - 0x5c];          // +0x5c
    int   mLayerId;                       // +0x108 (borrowed record handle)
    char  mPad10c[0x170 - 0x10c];         // +0x10c
    int   mTarget;                        // +0x170 (look-at target handle)
    int   mTargetBusy;                    // +0x174
    char  mPad178[0x17e - 0x178];         // +0x178
    char  mFlag17e;                       // +0x17e
    char  mFlag17f;                       // +0x17f (pending command)
    char  mPad180[0x18c - 0x180];         // +0x180
    int   mState18c;                      // +0x18c (command state)
    char  mPad190[0x1f4 - 0x190];         // +0x190
    float mTimerD;                        // +0x1f4
    float mTimerE;                        // +0x1f8
    char  mPad1fc[0x208 - 0x1fc];         // +0x1fc
    int   mCur208;                        // +0x208 (currently dispatched handle)
    int   mHandleC;                       // +0x20c (pool handle)
    int   mHandleD;                       // +0x210 (pool handle)
    int   mHandleE;                       // +0x214 (pool handle)
    float mTimerF;                        // +0x218
    float mTimerA;                        // +0x21c
    int   mHandleA;                       // +0x220 (pool handle)
    float mValueA;                        // +0x224 (must be <= 0 for the update to run)
    float mValueB;                        // +0x228 (must be <= 0 for the update to run)
    int   mHandleB;                       // +0x22c (pool handle)
    float mTimerB;                        // +0x230
    int   mPad234;                        // +0x234
    float mTimerC;                        // +0x238 (main countdown)
    char  mPad23c[0x38c - 0x23c];         // +0x23c
    int   mHandleF;                       // +0x38c (pool handle)
    char  mPad390[0x490 - 0x390];         // +0x390
};

extern const float g_13eb8a0;     // 0.25f
extern const float g_13eb8b0;     // sign-bit mask (negation)
extern const float g_1486110;     // 5.0f
extern const float g_14851ec;     // 1.52587890625e-05f
// The command-record "from"/"to" points and its orthogonal basis are plain floats that may be
// read at 4-byte alignment, so cl folds the loads into the movss stores (retail has a separate
// `mov`/`movss` per field).
extern __declspec(align(4)) float gFwd_16b3c28;    // 0x016b3c28 camera forward
extern __declspec(align(4)) float gFwd_16b3c2c;    // 0x016b3c2c
extern __declspec(align(4)) float gFwd_16b3c30;    // 0x016b3c30
extern __declspec(align(4)) float gBasis_15a7c4c;  // 0x015a7c4c orthogonal basis
extern __declspec(align(4)) float gBasis_15a7c50;  // 0x015a7c50
extern __declspec(align(4)) float gBasis_15a7c54;  // 0x015a7c54
extern __declspec(align(4)) float gBasis_15a7c58;  // 0x015a7c58
extern const float gUp_15a7c40[3]; // 0x015a7c40 up vector

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();     // 0x009360d0 thiscall
};
} }
extern EA::Random::RandomLinearCongruential sMathRandom;  // 0x01601760

// ---------------------------------------------------------------- callees
extern "C" int*   __cdecl FUN_00e4cc40(int id, RefHandle* out);   // thunk_FUN_00e823a0
extern "C" char*  __cdecl FUN_00e52910(int id);extern "C" char   __cdecl FUN_00e52960(int obj);                  // reads its object from ESI
extern "C" float  __cdecl FUN_00e6d200(void* obj, int a, int b, int c);
extern "C" void*  __cdecl FUN_00e51ee0(int kind, float t, int a, int b, int c, int d, int e,
                                       int f, float g, float h, int i, int j, int k, int l,
                                       int m, int n);
extern "C" void   __cdecl FUN_00e57b50(int id, int a, int b, int c);
extern "C" void   __cdecl FUN_00e57a60(int id, int id2, int a, int b, int c);
extern "C" char   __cdecl FUN_00e57460(void* a, void* b);
extern "C" char   __cdecl FUN_00e57ce0(void* self, void* other);
extern "C" void   __cdecl FUN_00e68b30(void* self, int arg, void* buf);
extern "C" void   __cdecl FUN_00e68990(void* self, void* rec, int* a, int* b, int c);
extern "C" void   __cdecl FUN_00e686c0(void* cell, int other, float* outA, float* outB);
extern "C" void   __cdecl FUN_00e67cb0(void* self, void* out);    // fills 4 floats
extern "C" int    __cdecl FUN_00e67c40(void* self, void* other);
extern "C" void   __cdecl FUN_00e6f800(void* self, int handle, float a, float b, float c,
                                       int id, int zero, int extra);
extern "C" void   __cdecl FUN_00e6f940(void* self, int handle, float a, float b, int c,
                                       int d, float e);
extern "C" void   __cdecl FUN_00e6ff60(void* self, float* buf, float a, float b, int byte,
                                       float dt);
extern "C" void   __cdecl FUN_00e61e20(void* self, float a, float b);   // sCellOrientToward
extern "C" float* __cdecl SP_normalized_safe(float* out, const float* v);  // 0x00449c20
extern "C" int*   __cdecl QuaternionFromFacingAndUp(int* out, const float* facing,
                                                    const float* up);     // 0x0069b600

// 0x00e70cf0 (cdecl, two stack args: self, arg).
char FUN_00e70cf0(cTimedHandles* self, int arg);
// 0x00e70f20 (cdecl, six stack args).
void FUN_00e70f20(cTimedHandles* self, void* rec, float p3, int p4, int p5, float dt);
// ---------------------------------------------------------------- 0x00e707d0
// Borrow the layer record, run the two short countdowns and, when the avatar is inside the
// record's radius, hand the look-at to the 8-arg dispatcher.
// @ 0x00e707d0
void __cdecl FUN_00e707d0(cTimedHandles* self, float dt)
{
    RefHandle ref;
    ref.Clear();
    int id = (int)FUN_00e4cc40(self->mLayerId, &ref);

    if (self->mTimerD > 0.0f) {
        float v = self->mTimerD - dt;
        self->mTimerD = v;
        if (v < 0.0f) {
            int* rec = (int*)FUN_00e52910(id);
            self->mTimerE = *(float*)(rec + 0x25);
        }
        ref.Release();
        return;
    }
    if (self->mTimerE >= 0.0f) {
        float v = self->mTimerE - dt;
        self->mTimerE = v;
        if (v < 0.0f) {
            int* rec = (int*)FUN_00e52910(id);
            self->mTimerD = *(float*)(rec + 0x26);
            ref.Release();
            return;
        }
    }

    cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
    cTimedHandles* avatar = (cTimedHandles*)cells->GetSafe((uint32)g_keyDefaultFood);
    if (avatar != 0) {
        float dx = avatar->mPosX - self->mPosX;
        float dy = avatar->mPosY - self->mPosY;
        float dz = avatar->mPosZ - self->mPosZ;
        int* rec = (int*)FUN_00e52910(id);
        float radius = *(float*)(rec + 1);
        if ((dz * dz + dx * dx) + dy * dy <= radius * radius) {
            int extra = *((unsigned char*)FUN_00e52910(id) + 0x44);
            int n = FUN_00e67c40(self, avatar);
            float a = *(float*)((int*)FUN_00e52910(id) + 0x10);
            float b = *(float*)((int*)FUN_00e52910(id) + 6);
            FUN_00e6f800(self, avatar->mId, dt, b, a, n, 0, extra);
        }
    }
    ref.Release();
}

// ---------------------------------------------------------------- 0x00e70950
// Build the kind-12 "enter look-at" command record for one cell.
// @ 0x00e70950
void __cdecl FUN_00e70950(int* cell, int arg)
{
    cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
    cTimedHandles* obj = (cTimedHandles*)cells->Get(cell[0]);
    float t = FUN_00e6d200(obj, 0, 0x15, *(int*)((char*)obj + 0x1b0));
    int id = cell[0];

    cObjectPool* cmds = (cObjectPool*)((char*)GetCellGameAddr() + 0x54);
    cCellCmd* cmd = (cCellCmd*)cmds->Get(cmds->Alloc());
    cmd->mTime1c = t;
    cmd->mSrc28 = id;
    cmd->mTime20 = t;
    cmd->mKind24 = 0xc;
    cmd->mArg2c = arg;
    cmd->mArg38 = 0;
    cmd->mArg3c = 0;
    cmd->mF40 = 0.0f;
    cmd->mF44 = 0.0f;
    cmd->mArg30 = -1;
    cmd->mArg34 = -1;
    cmd->mDir48 = gFwd_16b3c28;
    cmd->mDir4c = gFwd_16b3c2c;
    cmd->mDir50 = gFwd_16b3c30;
    cmd->mDir54 = gFwd_16b3c28;
    cmd->mDir58 = gFwd_16b3c2c;
    cmd->mDir5c = gFwd_16b3c30;
    cmd->mBasis60 = gBasis_15a7c4c;
    cmd->mBasis64 = gBasis_15a7c50;
    cmd->mBasis68 = gBasis_15a7c54;
    cmd->mBasis6c = gBasis_15a7c58;
    cmd->mArg70 = 0;
    cmd->mFlag74 = 0;
    cmd->mArg78 = 0;
    cmd->mFlags04 = 0;
    cmd->mFlag08 = 0;

    cTimedHandles* c = (cTimedHandles*)cells->GetSafe(id);
    if (c != 0) {
        c->mFlag17e = 1;
        c->mTarget = arg;
        if (c->mState18c == 0 || (unsigned)(c->mState18c - 0x15) <= 1)
            c->mState18c = 0x15;
    }
}

// ---------------------------------------------------------------- 0x00e70a90
// Emit command kind 11 for one cell and record it as pending.
// @ 0x00e70a90
void __cdecl FUN_00e70a90(int* cell, int a2, int a3, int a4)
{
    if (*(char*)((char*)cell + 0x17f) != 0)
        return;
    cTimedHandles* obj = (cTimedHandles*)((cObjectPool*)((char*)GetCellGameAddr() + 0x1c))->Get(cell[0]);
    float t = FUN_00e6d200(obj, 0, a3, *(int*)((char*)obj + 0x1b0));
    FUN_00e51ee0(0xb, t, cell[0], 0, a2, -1, a3, 0, 0.0f, 0.0f, a4, 0, 0, 0, 0, 0);
    FUN_00e57b50(cell[0], a2, a3, a4);
}

// ---------------------------------------------------------------- 0x00e70b20
// Emit command kind 9 for a cell pair and record it as pending.
// @ 0x00e70b20
void __cdecl FUN_00e70b20(int* cell, int* other, int a3, int a4, int a5)
{
    if (*(char*)((char*)cell + 0x17f) != 0)
        return;
    if (FUN_00e57460(cell, other))
        return;
    char* base = GetCellGameAddr();
    cObjectPool* cells = (cObjectPool*)(base + 0x1c);
    cTimedHandles* obj = (cTimedHandles*)cells->Get(cell[0]);
    float t = FUN_00e6d200(obj, 0, a5, *(int*)((char*)obj + 0x1b0));
    FUN_00e51ee0(9, t, cell[0], other[0], a3, -1, a5, 0, 0.0f, 0.0f, a4, 0, 0, 0, 0, 0);
    FUN_00e57a60(cell[0], other[0], a3, a5, a4);
}

// ---------------------------------------------------------------- 0x00e70bc0
// Build the kind-13 "leave look-at" command record for one cell.
// @ 0x00e70bc0
void __cdecl FUN_00e70bc0(int* cell, int arg)
{
    cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
    cTimedHandles* obj = (cTimedHandles*)cells->Get(cell[0]);
    float t = FUN_00e6d200(obj, 0, 0x16, *(int*)((char*)obj + 0x1b0));
    int id = cell[0];

    cObjectPool* cmds = (cObjectPool*)((char*)GetCellGameAddr() + 0x54);
    cCellCmd* cmd = (cCellCmd*)cmds->Get(cmds->Alloc());
    cmd->mTime1c = t;
    cmd->mSrc28 = id;
    cmd->mTime20 = t;
    cmd->mKind24 = 0xd;
    cmd->mArg2c = arg;
    cmd->mArg38 = 0;
    cmd->mArg3c = 0;
    cmd->mF40 = 0.0f;
    cmd->mF44 = 0.0f;
    cmd->mArg30 = -1;
    cmd->mArg34 = -1;
    cmd->mDir48 = gFwd_16b3c28;
    cmd->mDir4c = gFwd_16b3c2c;
    cmd->mDir50 = gFwd_16b3c30;
    cmd->mDir54 = gFwd_16b3c28;
    cmd->mDir58 = gFwd_16b3c2c;
    cmd->mDir5c = gFwd_16b3c30;
    cmd->mBasis60 = gBasis_15a7c4c;
    cmd->mBasis64 = gBasis_15a7c50;
    cmd->mBasis68 = gBasis_15a7c54;
    cmd->mBasis6c = gBasis_15a7c58;
    cmd->mArg70 = 0;
    cmd->mFlag74 = 0;
    cmd->mArg78 = 0;
    cmd->mFlags04 = 0;
    cmd->mFlag08 = 0;

    cTimedHandles* c = (cTimedHandles*)cells->GetSafe(id);
    if (c != 0) {
        c->mFlag17e = 1;
        c->mTarget = arg;
        if (c->mState18c == 0 || c->mState18c == 0x16)
            c->mState18c = 0x16;
    }
}

// ---------------------------------------------------------------- 0x00e70cf0
// Pick the active look-at slot: a foreign link record wins over the two own handles; the
// winning slot's timer is reloaded from the record (0x7c for +0x220, 0x84 for +0x22c).
// @ 0x00e70cf0
char __cdecl FUN_00e70cf0(cTimedHandles* self, int arg)
{
    cObjectPool* links = (cObjectPool*)((char*)GetCellGameAddr() + 0xa8);
    cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
    int* link = (int*)links->GetSafe(self->mHandleF);
    if (link != 0 && link[2] != self->mId) {
        cTimedHandles* other = (cTimedHandles*)cells->GetSafe(link[2]);
        if (other != 0) {
            self->mTimerA = other->mTimerA;
            self->mHandleA = other->mHandleA;
            self->mTimerB = other->mTimerB;
            self->mHandleB = other->mHandleB;
            self->mCur208 = other->mCur208;
            return 0;
        }
    }

    char local[0x10];
    FUN_00e68b30(self, arg, local);
    FUN_00e68990(self, local, &self->mHandleA, &self->mHandleB, 0);

    int a = self->mHandleA;
    if (a != 0) {
        if (a != self->mCur208) {
            FUN_00e70950((int*)self, a);
            self->mCur208 = self->mHandleA;
        }
        self->mTimerA = *(float*)((int*)FUN_00e52910(arg) + 0x1f);
        return 1;
    }
    int b = self->mHandleB;
    if (b != 0) {
        if (b != self->mCur208) {
            FUN_00e70bc0((int*)self, b);
            self->mCur208 = self->mHandleB;
        }
        self->mTimerB = *(float*)((int*)FUN_00e52910(arg) + 0x21);
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00e70f20
// Drive the look-at command state for one cell: prune stale pool handles, re-read the record,
// then dispatch the currently selected handle.  p3/p4 are the two float payload values and p5
// the per-record byte that travels with them.
// @ 0x00e70f20
void __cdecl FUN_00e70f20(cTimedHandles* self, void* rec, float p3, int p4, int p5, float dt)
{
    float buf[4];
    cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);

    float v = self->mTimerF - dt;
    self->mTimerF = v;
    if (v < 0.0f) {
        FUN_00e68990(self, rec, &self->mHandleC, &self->mHandleE, 0);
        float t = (float)(sMathRandom.RandomDoubleUniform() * 0.0625);
        if (t >= 0.0625f || 0.0f <= t)
            self->mTimerF = 0.0625f + 0.25f;
        else
            self->mTimerF = 0.0f + 0.25f;
    } else {
        if ((self->mHandleC != 0 && cells->GetSafe(self->mHandleC) == 0) ||
            (self->mHandleE != 0 && cells->GetSafe(self->mHandleE) == 0) ||
            (self->mHandleD != 0 && cells->GetSafe(self->mHandleD) == 0)) {
            int h;
            self->mHandleC = 0;
            self->mHandleE = 0;
            self->mHandleD = 0;
            FUN_00e68990(self, rec, &self->mHandleC, &h, 0);
            cTimedHandles* obj = (cTimedHandles*)cells->GetSafe(h);
            if (obj != 0) {
                if (FUN_00e52960((int)obj) != 0)
                    self->mHandleD = h;
                else
                    self->mHandleE = h;
            }
        }
    }

    FUN_00e67cb0(self, buf);

    int h = self->mHandleC;
    if (h != 0) {
        if (h != self->mCur208) {
            self->mCur208 = h;
            FUN_00e70950((int*)self, h);
            self->mTimerB = 5.0f;
            return;
        }
        if (self->mState18c == 0)
            self->mState18c = 0x13;
        if (cells->GetSafe(h) == 0) {
            self->mHandleC = 0;
            self->mTimerA = 0.0f;
        } else {
            FUN_00e6f940(self, h, buf[3], p3, p4, p5, dt);
            float t = self->mTimerA - dt;
            self->mTimerA = t;
            if (t < 0.0f)
                self->mHandleC = 0;
            return;
        }
    }

    if (self->mHandleD != 0) {
        cTimedHandles* cur = (cTimedHandles*)cells->GetSafe(self->mCur208);
        int flag = 0;
        if (cur != 0 && FUN_00e57ce0(self, cur) != 0) {
            int d = self->mHandleD;
            if (d != self->mCur208) {
                self->mCur208 = d;
                FUN_00e70bc0((int*)self, d);
                return;
            }
            if (self->mState18c == 0)
                self->mState18c = 0x14;
            flag = 1;
        }
        if (cells->GetSafe(self->mHandleD) != 0) {
            FUN_00e6f800(self, self->mHandleD, dt, buf[1], p3, p4, flag, p5);
            return;
        }
        self->mHandleD = 0;
    }

    int e = self->mHandleE;
    if (e != 0) {
        if (e != self->mCur208) {
            self->mCur208 = e;
            FUN_00e6f800(self, e, dt, buf[2], p3, p4, 0, p5);
            return;
        }
        if (cells->GetSafe(e) != 0) {
            FUN_00e6f800(self, e, dt, buf[2], p3, p4, 0, p5);
            return;
        }
        self->mHandleE = 0;
    }

    FUN_00e6ff60(self, &buf[2], p3, p4, *(unsigned char*)((char*)rec + 0xd), dt);
}

// ---------------------------------------------------------------- 0x00e71300

// ---------------------------------------------------------------- 0x00e70e30
// 0x00e70e30 (cdecl, `ret`, caller pops 3 args).
void FUN_00e70e30(cTimedHandles* p, uint32 arg, float dt)
{
    if (!(p->mValueA > 0.0f) && !(p->mValueB > 0.0f)) {
        if (p->mTimerA > 0.0f) {
            uint32 h = p->mHandleA;
            cObjectPool* pool = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
            void* r = pool->GetSafe(h);
            if (r != 0)
                return;
            p->mHandleA = (uint32)r;
            p->mTimerA = 0.0f;
            p->mTimerC = 0.0f;
        }
        if (p->mTimerB > 0.0f) {
            uint32 h = p->mHandleB;
            cObjectPool* pool = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
            void* r = pool->GetSafe(h);
            if (r != 0)
                return;
            p->mHandleB = (uint32)r;
            p->mTimerB = 0.0f;
            p->mTimerC = 0.0f;
        }
        if (p->mTimerC >= 0.0f) {
            p->mTimerC = p->mTimerC - dt;
            if (p->mTimerC < 0.0f) {
                FUN_00e70cf0(p, arg);
                p->mTimerC = g_13eb8a0;
            }
        }
    }
}
// Per-tick look-at update. The retail body is entered with the cell in ESI and the record id in
// EDI (LTCG custom-register ABI at the 0x00e7a44d call site), so this reconstruction takes both
// explicitly; it cannot be byte-exact.
// @ 0x00e71300
struct LookSeed {
    float f00;    // +0x00 look-at seed (FUN_00e686c0 out A)
    float f04;    // +0x04                       (out B)
    char  b08;    // +0x08
    char  b09;    // +0x09
    char  b0a;    // +0x0a
    char  b0b;    // +0x0b
    char  b0c;    // +0x0c
    char  b0d;    // +0x0d (consumed by FUN_00e70f20)
};

void __cdecl FUN_00e71300(cTimedHandles* self, int id, float dt)
{
    if (self->mTimerD > 0.0f) {
        float v = self->mTimerD - dt;
        self->mTimerD = v;
        if (v <= 0.0f)
            self->mTimerE = *(float*)(FUN_00e52910(id) + 0x94);
        self->mState18c = 0x17;
        return;
    }

    float v = self->mTimerE - dt;
    self->mTimerE = v;
    if (v <= 0.0f)
        self->mTimerD = *(float*)(FUN_00e52910(id) + 0x98);

    if (self->mFlag17e != 0) {
        cObjectPool* cells = (cObjectPool*)((char*)GetCellGameAddr() + 0x1c);
        cTimedHandles* target = (cTimedHandles*)cells->GetSafe(self->mTarget);
        if (target == 0)
            return;
        if (self->mTargetBusy != 0)
            return;

        float dir[3];
        float out[3];
        dir[0] = target->mPosX - self->mPosX;
        dir[1] = target->mPosY - self->mPosY;
        dir[2] = target->mPosZ - self->mPosZ;
        SP_normalized_safe(out, dir);
        dir[0] = out[0];
        dir[1] = out[1];
        dir[2] = out[2];
        if (dir[2] * dir[2] + dir[1] * dir[1] + dir[0] * dir[0] <= g_14851ec)
            return;
        dir[0] = -dir[0];
        dir[1] = -dir[1];
        dir[2] = -dir[2];
        int quat[4];
        QuaternionFromFacingAndUp(quat, dir, gUp_15a7c40);
        self->mQuat[0] = quat[0];
        self->mQuat[1] = quat[1];
        self->mQuat[2] = quat[2];
        self->mQuat[3] = quat[3];
        FUN_00e61e20(self, 5.0f, dt);
        return;
    }

    LookSeed seed;
    FUN_00e686c0(self, id, &seed.f00, &seed.f04);
    seed.b09 = 1;
    seed.b0a = 1;
    seed.b0b = 1;
    seed.b08 = 0;
    int extra = *(unsigned char*)((int*)FUN_00e52910(id) + 0x11);
    int n = FUN_00e67c40(self, (void*)id);
    float f = *(float*)((int*)FUN_00e52910(id) + 0x10);
    FUN_00e70f20(self, &seed, f, n, extra, dt);
}