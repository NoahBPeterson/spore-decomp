// Slice s00e6e8c0 -- SP cell TU: per-step motion update of a cell (0x00e6eec0, 1772 bytes).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc).
//
// In the original this is a `static` function of the big Cell TU: the cell arrives in ESI and the five
// remaining arguments are on the stack (cdecl-style, the caller cleans up). It is emitted here with a
// non-static stand-in caller so cl gives the static the same register convention. Its callees (all in
// the same TU) are declared as plain extern cdecl functions, even where the original gave them custom
// register conventions (the speed factor 0x00e56b50 comes back in XMM0; sGetSourceLevel takes EDX).
#include "types.h"
#include <math.h>
typedef uint32_t uint32;

struct Vec3 { float x, y, z; };

// A simulated cell (only the fields this function touches).
struct Cell {
    int   mIndex;                 // +0x00 index in gspCellGame->mCells
    char  mDone;                  // +0x04 set once the cell has (almost) reached its target
    char  pad05[3];
    Vec3  mPos;                   // +0x08
    char  pad14[0x4c - 0x14];
    Vec3  mTarget;                // +0x4c (the position it is moving toward)
    char  pad58[0x90 - 0x58];
    Vec3  mHeading;               // +0x90 current v
    char  pad9c[0xb8 - 0x9c];
    float mVelocityScale;         // +0xb8
    char  padbc[0x17e - 0xbc];
    char  mSuppressed;            // +0x17e
    char  pad17f[0x18c - 0x17f];
    int   mState;                 // +0x18c motion state
    char  pad190[4];
    float mTurnDistance;          // +0x194 (flags & 1 / & 8)
    float mTurnRateB;             // +0x198 (flags & 4)
    float mTurnRateC;             // +0x19c (flags & 2)
    char  pad1a0[0x1c4 - 0x1a0];
    Vec3  mAccum;                 // +0x1c4 accumulated displacement
    char  pad1d0[0x248 - 0x1d0];
    int   mHasPath;               // +0x248
    char  pad24c[0x358 - 0x24c];
    int   mLevel;                 // +0x358
};

struct LevelInfo { char pad[0x1c]; int mLevel; };
struct cGameStub {                // gspCellGame
    char pad0[0x411c];
    int mAvatarCellIndex;         // +0x411c
    char pad4120[0x5190 - 0x4120];
    LevelInfo* mpLevelInfo;       // +0x5190
};
extern cGameStub* gspCellGame;                // 0x016b3c04

// 4-byte handle holder (ctor 0x00743b50, dtor 0x00e82130)
struct cHandleRef {
    int mp;
    cHandleRef();
    ~cHandleRef();
};
struct CellScales {               // 0x00e4ce40 result
    char pad0[0x48];
    float f48;
    float f4c;
    float f50;
    float f54;
};

extern const float kLevelSize[];              // 0x01483bd0
extern float kQuarterPi;                      // 0x015a7c1c
extern float kPi;                             // 0x015a7c24
extern Vec3 kFallbackDir;                     // 0x016b3c28

// callees (all 0x00e5xxxx..0x00e8xxxx are in the cell TU)
void  CellDelta(Vec3* out, Cell* self);                                    // 0x00e56560
float CellSpeedFactor(Cell* self, unsigned flags, float dist);             // 0x00e56b50 (XMM0 in the original)
float CellLevelRatio(Cell* self);                                          // 0x00e56450
float CellTurnLimit(Cell* self);                                           // 0x00e56510
float CellTurnAngle(Cell* self);                                           // 0x00e5ef40
void  CellStartTurn(Cell* self);                                           // 0x00e6ee10
void  CellApplyTurn(Cell* self, float rate, float angle);                  // 0x00e61e20
bool  CellCanTurn(Cell* self, float angle);                                // 0x00e56ae0
void  CellSteerA(const Vec3* pos2, Vec3* v, const Vec3* pos, float a2, float a1, Vec3* out);   // 0x00e55f60
const Vec3* CellFacing(Vec3* out, Cell* self);                             // 0x00e5eb20
float CellSteerRateB(Cell* self);                                          // 0x00e56200
float CellSteerRateC(Cell* self);                                          // 0x00e56300
bool  CellSteerB(const Vec3* facing, const Vec3* pos2, Vec3* v, const Vec3* pos,
                 float a2, float s, float a3, int flag, float a1, Vec3* out);   // 0x00e558c0
bool  CellSteerC(const Vec3* facing, const Vec3* pos2, Vec3* v, const Vec3* pos,
                 float a2, float s, float a3, int flag, float a1, Vec3* out);   // 0x00e55c40
void  CellMove(Cell* self, const Vec3* v);                                 // 0x00e560d0
CellScales* GetCellScales(cHandleRef* tmp);                                // 0x00e4ce40
float CellScaleById(uint32 id, float ratio);                               // 0x00e837c0
int   __fastcall SP_sGetSourceLevel(void* unused, int level);              // 0x00e4ee60 (level in EDX)
const Vec3* NormalizedSafe(Vec3* out, const Vec3* in);                     // 0x00449c20
float Dot3(const Vec3* a, const Vec3* b);                                  // 0x00455cc0

static __forceinline Vec3 Scaled(const Vec3& v, float s) { Vec3 r = { v.x * s, v.y * s, v.z * s }; return r; }

// @ 0x00e6eec0  (static, self in ESI)
static void StepCell(Cell* self, float a1, float a2, float a3, unsigned flags, int mode)
{
    Vec3 v;                       // per-step delta; later reused as the steering vector
    CellDelta(&v, self);
    self->mAccum.x = self->mAccum.x + v.x;
    self->mAccum.y = v.y + self->mAccum.y;
    self->mAccum.z = v.z + self->mAccum.z;
    if (self->mDone)
        return;

    const Vec3* pos = &self->mPos;
    const Vec3* target = &self->mTarget;
    double ddx = (double)pos->x - target->x;
    double ddy = (double)pos->y - target->y;
    double ddz = (double)pos->z - target->z;
    double dist = sqrt(ddx * ddx + ddy * ddy + ddz * ddz);
    if (dist < 0.5f) {
        self->mDone = 1;
        return;
    }

    float speed = CellSpeedFactor(self, flags, (float)dist);
    a2 = (self->mHasPath ? 1.0f : 0.5f) * (float)((double)a2 / CellLevelRatio(self));
    if (self->mIndex != gspCellGame->mAvatarCellIndex) {
        cHandleRef h;
        CellScales* sc = GetCellScales(&h);
        a2 = sc->f48 * a2;
        if (flags & 8)
            speed = sc->f50 * speed;
        else if (flags & 1)
            speed = sc->f50 * speed;
        else if (flags & 2)
            speed = sc->f54 * speed;
        else if (flags & 4)
            speed = sc->f4c * speed;
        int src = SP_sGetSourceLevel(0, gspCellGame->mpLevelInfo->mLevel);
        speed = CellScaleById(0x1106a9e2, kLevelSize[self->mLevel] / kLevelSize[src]) * speed;
    }
    speed = speed * a3;

    if (self->mState == 0 || self->mState == 0x28 || !(1.5258789e-05f > CellTurnLimit(self))) {
        float angle = CellTurnAngle(self);
        static float sQuarter = kQuarterPi;
        float absAngle = (float)fabs(angle);
        if (absAngle > kPi - sQuarter && (flags & 2)) {
            CellStartTurn(self);
        } else {
            static float sEighth = kQuarterPi * 0.5f;
            if (absAngle > sEighth) {
                mode = 3;
                if (!(angle > 0.0f))
                    mode = 4;
            }
            CellApplyTurn(self, speed, a1);
        }
    }

    if (self->mSuppressed == 1)
        return;

    bool pickMode = false;
    switch (self->mState) {
    case 0:
    case 0x12:
    case 0x30:
        pickMode = true;
        break;
    case 0x28:
        if (self->mIndex == gspCellGame->mAvatarCellIndex)
            pickMode = true;
        break;
    }
    if (pickMode) {
        switch (mode) {
        case 0: self->mState = CellCanTurn(self, a1) ? 0x30 : 0x12; break;
        case 1: self->mState = 0x14; break;
        case 2: self->mState = 0x13; break;
        case 3: self->mState = 0x32; break;
        case 4: self->mState = 0x33; break;
        }
    }

    float scale = CellTurnLimit(self);
    Vec3 n1, n2;
    if (flags & 8) {
        CellSteerA(target, &self->mHeading, pos, a2, a1, &v);
        const Vec3* p = NormalizedSafe(&n1, &v);
        const Vec3* q = CellFacing(&n2, self);
        float dot = q->z * p->z + (q->y * p->y + q->x * p->x);
        if ((float)fabs(dot) < 0.9f)
            v = kFallbackDir;
        v = Scaled(v, scale);
        self->mTurnDistance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    } else if (flags & 4) {
        float s = CellSteerRateB(self);
        bool ok = CellSteerB(CellFacing(&n2, self), target, &self->mHeading, pos, a2, s, a3,
                             (flags & 2) == 2, a1, &v);
        if (!ok) {
            int st = self->mState;
            if (st == 0x13 || st == 0x14 || st == 0x12 || st == 0x30)
                self->mState = 0;
        }
        v = Scaled(v, scale);
        const Vec3* p = NormalizedSafe(&n1, &v);
        const Vec3* h = NormalizedSafe(&n2, &self->mHeading);
        float dot = Dot3(h, p);
        self->mTurnRateB = (float)(sqrt((double)(v.x * v.x + v.y * v.y + v.z * v.z)) * dot
                                   + 1.5258789e-05f);
    } else if (flags & 1) {
        CellSteerC(CellFacing(&n2, self), target, &self->mHeading, pos, a2, 1.0f, a3, 0, a1, &v);
        v = Scaled(v, scale);
        self->mTurnDistance = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)
                              + 1.5258789e-05f;
    } else if (flags & 2) {
        float s = CellSteerRateC(self);
        CellSteerC(CellFacing(&n2, self), target, &self->mHeading, pos, a2, s, a3, 1, a1, &v);
        v = Scaled(v, scale);
        self->mTurnRateC = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)
                           + 1.5258789e-05f;
    }

    v = Scaled(v, self->mVelocityScale);
    CellMove(self, &v);
}

// Stand-in caller so the static helper is emitted with its register convention.
void StepCellEntry(Cell* self, float a1, float a2, float a3, unsigned flags, int mode)
{
    StepCell(self, a1, a2, a3, flags, mode);
}

// ---------------------------------------------------------------------------
// 0x00e6e8c0 -- cell-stage "cell_ending" handler (SPGonzago/SPCellGame).
//
// 0x00e7ce10 calls it with 0 when the level clock reaches 1000, 0x00e80ba0
// with 1 (immediate).  When the layer catalog's +0xe0 word is clear and the
// flag is not set it only fires the two level-end callouts; otherwise it emits
// the "cell_ending" spawn record (kind 0x2f, mode 0x44, the cell_Eggkid
// archetype) and passes the two timing floats to 0x00e53c70.
//
// Field offsets are kept as raw offsets because the cCellGame/cCell layouts are
// owned by the other functions in this translation unit.
#define BYTE_AT(p, o) (*(unsigned char*)((char*)(p) + (o)))
#define INT_AT(p, o)  (*(int*)((char*)(p) + (o)))
#define FLT_AT(p, o)  (*(float*)((char*)(p) + (o)))

struct Vec4 { float x, y, z, w; };

// The handle pools at cCellGame+0x1c / +0x54 (0x00b721d0 / 0x00b72210 / 0x00b72160).
struct cHandlePool {
    char  mReserved[0x38];
    void* GetSafe(int handle);      // 0x00b721d0  thiscall
    void* Get(int handle);          // 0x00b72210  thiscall
    int   Alloc();                  // 0x00b72160  thiscall
};

// Key object returned by 0x00b3d4d0 (0x00ae0930 is its thiscall Init).
struct cTempKey { void Init(); };

// Notification/spawn record handed out by the +0x54 pool (see s00e6eb60.cpp).
struct cSpawnRecord {
    int           mField00;
    int           mField04;
    unsigned char mField08;
    char          mPad09[0x1c - 0x09];
    float         mField1c;
    float         mField20;
    int           mField24;         // record kind (0x2f here, 0x1c / 0x1b elsewhere)
    int           mField28;
    int           mField2c;
    int           mField30;
    int           mField34;
    int           mField38;
    int           mField3c;
    float         mField40;
    float         mField44;
    Vec3          mPos48;
    Vec3          mPos54;
    Vec4          mQuat60;
    int           mField70;
    unsigned char mField74;
    char          mPad75[3];
    int           mField78;
};

// 0x015a8434 holds the archetype pointer of cell_Eggkid (0x0148533c, whose
// first word is the 0x00e566e0 factory); the source passes the slot's address.
struct cArchetypeSlot { const void* mpArchetype; };

extern char*            gspCellUI;          // 0x016b3c0c
extern Vec3             gCellWorldCenter;   // 0x016b3c28 (also kFallbackDir above)
extern Vec4             gCellSpawnQuat;     // 0x015a7c4c (0, 0, 0, 1)
extern cArchetypeSlot   gEggkidArchetype;   // 0x015a8434

extern "C" unsigned FNV1_String8(const char* text, unsigned seed, int flag);  // 0x00932e80
extern "C" void  FUN_00e53660(int a, int b);                          // 0x00e53660
extern "C" int   FUN_00e4fca0(void);                                  // 0x00e4fca0
extern "C" void  FUN_00e50450(unsigned id, const void* param);        // 0x00e50450
extern "C" unsigned FUN_00e571cf0(const char* text);                  // 0x00e571cf0
extern "C" float FUN_00e52b70(void);                                  // 0x00e52b70
extern "C" void  FUN_00e53c70(float a, float b);                      // 0x00e53c70
extern "C" float FUN_00e6d200(void* cell, int a, int mode, int field);// 0x00e6d200

// 6 arguments, callee-cleaned (stdcall, ret 0x18).
extern "C" cTempKey* __stdcall FUN_00b3d4d0(const char* name, int, int, int, int, int);

// @ 0x00e6e8c0
void FUN_00e6e8c0(bool skip)
{
    cHandleRef ref;
    char* catalog = (char*)GetCellScales(&ref);

    if (INT_AT(catalog, 0xe0) == 0 && !skip) {
        FUN_00e53660(2, 1);
        BYTE_AT(gspCellUI, 0x938) = 1;
        int mode = FUN_00e4fca0();
        if (mode == 1) {
            FUN_00e50450(FNV1_String8("Callout_CLG_Ending", 0x811c9dc5u, mode), 0);
            FUN_00e50450(FNV1_String8("Callout_CLG_TransitionButton", 0x811c9dc5u, 1),
                         &gEggkidArchetype);
        } else if (FUN_00e4fca0() == 2) {
            FUN_00e50450(FUN_00e571cf0("Callout_CLG_Ending"), &gEggkidArchetype);
        }
        return;
    }

    int handle = INT_AT(gspCellGame, 0x411c);
    cHandlePool* cells = (cHandlePool*)((char*)gspCellGame + 0x1c);
    char* cell = (char*)cells->GetSafe(handle);
    if (cell == 0)
        return;
    if (BYTE_AT(cell, 0x112) != 0 || BYTE_AT(cell, 0x113) != 0 || BYTE_AT(cell, 0x188) != 0)
        return;

    if (INT_AT(gspCellGame, 0x51b4) == 3) {
        FLT_AT(gspCellGame, 0x51bc) = FUN_00e52b70();
        INT_AT(*(char**)((char*)gspCellGame + 0x5190), 0xb0) = 3;
        FLT_AT(*(char**)((char*)gspCellGame + 0x5190), 0xbc) = 5.0f;
        INT_AT(gspCellGame, 0x51b4) = -1;
        INT_AT(gspCellGame, 0x51b0) = 0;
    }

    FUN_00b3d4d0("cell_ending", 0, 0, 0, 0, 0)->Init();

    int subjectHandle = INT_AT(gspCellGame, 0x411c);
    cHandlePool* cellPool = (cHandlePool*)((char*)gspCellGame + 0x1c);
    char* subject = (char*)cellPool->Get(subjectHandle);
    float time = FUN_00e6d200(subject, 0, 0x44, INT_AT(subject, 0x1b0));

    cHandlePool* allocPool = (cHandlePool*)((char*)gspCellGame + 0x54);
    int slot = allocPool->Alloc();
    cHandlePool* spawnPool = (cHandlePool*)((char*)gspCellGame + 0x54);
    cSpawnRecord* rec = (cSpawnRecord*)spawnPool->Get(slot);

    rec->mField1c = time;
    rec->mField20 = time;
    rec->mField24 = 0x2f;
    rec->mField28 = 0;
    rec->mField2c = 0;
    rec->mField30 = -1;
    rec->mField34 = -1;
    rec->mField38 = 0;
    rec->mField3c = 0;
    rec->mField40 = 0.0f;
    rec->mField44 = 0.0f;
    rec->mPos48 = gCellWorldCenter;
    rec->mPos54 = gCellWorldCenter;
    rec->mQuat60 = gCellSpawnQuat;
    rec->mField70 = 0;
    rec->mField74 = 0;
    rec->mField78 = 0;
    rec->mField04 = 0;
    rec->mField08 = 0;
    INT_AT(gspCellGame, 0x5194) = slot;
    INT_AT(gspCellGame, 0x5198) = slot;
    FUN_00e53c70(time, 0.0f);
}
