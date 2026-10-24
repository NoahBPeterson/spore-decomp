// Slice s00b894a0 -- Simulator-side eastl vector helpers for cNatlBounds (the
// 20-byte sp_vector boundary vectors and the 0x1c-byte element insert) plus the
// cube-face cell lookup that turns a direction vector into a noun id.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <new>
#include "types.h"

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { return (float)fabs(x); }

#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

void* FUN_00f473a0(unsigned int, const char*, int, int, const char*, int);  // 0x00f473a0 operator new[]
void  FUN_00f47380(void*);                                                  // 0x00f47380 operator delete[]
void* FUN_00b850c0(void*, void*, void*);                                    // 0x00b850c0 uninitialized_copy
void  FUN_00b7f6d0(void*, void*, void*);                                    // 0x00b7f6d0 destroy-after-move
void  FUN_00b86390(void*, void*, void*);                                    // 0x00b86390 copy_backward
void  FUN_00b88430(void*, void*, void*);                                    // 0x00b88430 (thiscall, ret 8)
void  FUN_00b86270(void*, void*, void*, void*);                             // 0x00b86270 (thiscall, ret 0xc)
void  FUN_00473460(void*, void*);                                           // 0x00473460 (thiscall, ret 4)
void* FUN_00473500(void*, void*);                                           // 0x00473500 (thiscall, ret 4)
void  FUN_04558a0(void*, void*, void*);                                     // 0x04558a0 (thiscall, ret 8)
void  FUN_00bd9480(void*, void*);                                           // 0x00bd9480 (thiscall, ret 4)
void* FUN_00b3d300(void);                                                   // 0x00b3d300 SP::NounManager
void* FUN_00b21340(void*, void*, void*, void*, void*, void*);               // 0x00b21340 (thiscall, ret 0x14)

extern const float kZero;   // 0x01485378  (0.0f)

void FUN_00cd7d10(void);   // 0x00cd7d10
void FUN_00d3d420(void);   // 0x00d3d420
void FUN_00acdff0(void);   // 0x00acdff0
void FUN_00b1e500(void);   // 0x00b1e500
extern char DAT_018c43e8;  // 0x018c43e8

struct Vec3 { float x, y, z; };   // 0x0c

// ---------------------------------------------------------------------------
// eastl::sp_vector<cSPVector3> -- 0x14 bytes: 3 pointers + a 2-int allocator.
// ---------------------------------------------------------------------------
class Vec3Vec {
 public:
    Vec3* mpBegin;        // +0x00
    Vec3* mpEnd;          // +0x04
    Vec3* mpCapacity;     // +0x08
    int   mAllocator[2];  // +0x0c

    Vec3Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Vec3Vec(const Vec3Vec&) throw();          // 0x00473460
    Vec3Vec& operator=(const Vec3Vec&) throw();  // 0x00473500
    void assignRange(const Vec3*, const Vec3*, uint32_t);  // 0x00b86270
    void Free() {
        if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
            FUN_00f47380(mpBegin);
    }
};

// eastl::sp_vector<Vec3Vec> -- 0x14-byte elements, begin/end/capacity + allocator.
class OuterVec {
 public:
    Vec3Vec* mpBegin;     // +0x00
    Vec3Vec* mpEnd;       // +0x04
    Vec3Vec* mpCapacity;  // +0x08
    int      mAllocator[2];

    void DoInsertValue(Vec3Vec*, const Vec3Vec&);  // 0x00b88430
    void PushDefault();                            // 0x00b89770
};

// ---------------------------------------------------------------------------
// 0x1c-byte vector element and its 12-byte container.
// ---------------------------------------------------------------------------
struct Elem1c {
    uint32_t mA;      // +0x00
    uint32_t mB;      // +0x04
    Vec3Vec  mVec;    // +0x08
};

class Vec1c {
 public:
    Elem1c* mpBegin;     // +0x00
    Elem1c* mpEnd;       // +0x04
    Elem1c* mpCapacity;  // +0x08

    void DoInsertValue28(Elem1c*, const Elem1c&);  // 0x00b89830
};

// eastl::SPVector<unsigned int> -- 0x0c bytes (no allocator member).
class SPVectorI {
 public:
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;

    void DoInsertValueI(uint32_t*, const uint32_t&);  // 0x04558a0
    void push_back(const uint32_t& value) {
        uint32_t* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e)
                *e = value;
        } else {
            DoInsertValueI(e, value);
        }
    }
};

class cNatlBounds {
 public:
    char      _p00[0x0c];
    OuterVec  mVec0c;   // +0x0c
    OuterVec  mVec20;   // +0x20
    SPVectorI mVec34;   // +0x34

    void AddBoundary(const Vec3*, const Vec3*, uint32_t, uint32_t);  // 0x00b899b0
};

// ---------------------------------------------------------------------------
// @ 0x00b89770  push a default (empty) element into the outer vector.
// ---------------------------------------------------------------------------
void OuterVec::PushDefault()
{
    Vec3Vec* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            e->mpBegin = 0;
            e->mpEnd = 0;
            e->mpCapacity = 0;
        }
        return;
    }
    Vec3Vec value;
    DoInsertValue(e, value);
    value.Free();
}

// ---------------------------------------------------------------------------
// @ 0x00b899b0  cNatlBounds::AddBoundary
// ---------------------------------------------------------------------------
void cNatlBounds::AddBoundary(const Vec3* p2, const Vec3* p3, uint32_t count, uint32_t id)
{
    mVec34.push_back(id);
    mVec0c.PushDefault();
    mVec20.PushDefault();
    mVec0c.mpEnd[-1].assignRange(p3, p3 + count, id);
    mVec20.mpEnd[-1].assignRange(p2, p2 + count, id);
}

// ---------------------------------------------------------------------------
// @ 0x00b89830  insert one 0x1c-byte element (pos, value).
// ---------------------------------------------------------------------------
void Vec1c::DoInsertValue28(Elem1c* position, const Elem1c& value)
{
    Elem1c* pEnd = mpEnd;
    if (pEnd != mpCapacity) {
        const Elem1c* pv = &value;
        if (pv >= position && pv < pEnd)
            pv = pv + 1;
        if (pEnd) {
            pEnd->mA = pEnd[-1].mA;
            pEnd->mB = pEnd[-1].mB;
            TCS(void, (void*, void*), FUN_00473460)(&pEnd->mVec, (void*)&pEnd[-1].mVec);
        }
        FUN_00b86390(position, mpEnd - 1, mpEnd);
        position->mA = pv->mA;
        position->mB = pv->mB;
        position->mVec = pv->mVec;
        mpEnd += 1;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    uint32_t newCap = (count != 0) ? (uint32_t)(count * 2) : 1;
    Elem1c* pNewData = newCap
        ? (Elem1c*)FUN_00f473a0(newCap * 0x1c, "Simulator", 0, 0, ALLOC_FILE, 0xd1)
        : 0;
    Elem1c* dst = (Elem1c*)FUN_00b850c0(mpBegin, position, pNewData);
    FUN_00b7f6d0(mpBegin, position, pNewData);
    if (dst) {
        dst->mA = value.mA;
        dst->mB = value.mB;
        TCS(void, (void*, void*), FUN_00473460)(&dst->mVec, (void*)&value.mVec);
    }
    Elem1c* pNewEnd = (Elem1c*)FUN_00b850c0(position, mpEnd, dst + 1);
    FUN_00b7f6d0(position, mpEnd, dst + 1);
    if (mpBegin && ((int32_t*)mpBegin)[-1] != 0)
        FUN_00f47380(mpBegin);
    mpEnd = pNewEnd;
    mpBegin = pNewData;
    mpCapacity = (Elem1c*)((char*)pNewData + (uint32_t)newCap * 0x1c);
}

// ---------------------------------------------------------------------------
// Cell lookup: a cube-face grid of 6 faces of 64 x 64 signed-byte indices into
// the 0x18-byte cell records; each record carries a noun id at +0x14.
// ---------------------------------------------------------------------------
struct CellRec {                       // 0x18
    char    _p00[0x14];
    int32_t mId;                       // +0x14
};

struct GameDataVec {                   // returned by cGameNounManager::GetGameDataVector
    char      _p00[4];
    int32_t*  mpBegin;                 // +0x04
    int32_t*  mpEnd;                   // +0x08
};

class cCellGrid {
 public:
    char        _p00[0x80];
    CellRec*    mpCells;    // +0x80
    char        _p84[0x10];
    int8_t*     mpGrid;     // +0x94

    int32_t CellFromDirection(float* dir);   // 0x00b894a0
};

// ---------------------------------------------------------------------------
// @ 0x00b894a0  cCellGrid::CellFromDirection
// ---------------------------------------------------------------------------
int32_t cCellGrid::CellFromDirection(float* dir)
{
    float x = dir[0];
    float ax = Abs(x);
    float y = dir[1];
    float ay = Abs(y);
    float z = dir[2];
    float az = Abs(z);

    int iX, iY, iFace;
    if (az < ax || az < ay) {
        if (ay < ax) {
            iX = (int)((y / x + 1.0f) * 32.0f);
            iY = (int)((z / ax + 1.0f) * 32.0f);
            if (x < kZero)
                iFace = 3;
            else
                iFace = 2;
        } else {
            iX = (int)((z / y + 1.0f) * 32.0f);
            iY = (int)((x / ay + 1.0f) * 32.0f);
            if (y < kZero)
                iFace = 5;
            else
                iFace = 4;
        }
    } else {
        iX = (int)((x / z + 1.0f) * 32.0f);
        iY = (int)((y / az + 1.0f) * 32.0f);
        if (z < kZero)
            iFace = 1;
        else
            iFace = 0;
    }
    if (iX == 0x40) iX = 0x3f;
    if (iY == 0x40) iY = 0x3f;

    int32_t result = mpCells[mpGrid[(iFace * 0x40 + iY) * 0x40 + iX]].mId;
    if (result == 0) {
        void* nounMgr = FUN_00b3d300();
        GameDataVec* gv = TCS(GameDataVec*, (void*, void*, void*, void*, void*, void*), FUN_00b21340)(
            nounMgr, (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
            (void*)FUN_00b1e500, (void*)&DAT_018c43e8);
        int32_t* it = gv->mpBegin;
        if (it != gv->mpEnd) {
            Vec3 local;
            float* c = (float*)TCS(Vec3*, (void*, void*), FUN_00bd9480)((void*)(uint32_t)*it, &local);
            result = *it;
            float best = (dir[1] - c[1]) * (dir[1] - c[1]) + (dir[2] - c[2]) * (dir[2] - c[2]) +
                         (dir[0] - c[0]) * (dir[0] - c[0]);
            while (++it != gv->mpEnd) {
                c = (float*)TCS(Vec3*, (void*, void*), FUN_00bd9480)((void*)(uint32_t)*it, &local);
                float d = (dir[1] - c[1]) * (dir[1] - c[1]) + (dir[2] - c[2]) * (dir[2] - c[2]) +
                          (dir[0] - c[0]) * (dir[0] - c[0]);
                if (best > d) {
                    result = *it;
                    best = d;
                }
            }
            return result;
        }
        result = 0;
    }
    return result;
}