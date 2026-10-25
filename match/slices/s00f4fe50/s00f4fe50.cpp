// Slice s00f4fe50: 4x4 transform helpers (column/row setup, direction query) and the
// teardown of a container of 12 sub-objects.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------

struct cVec3 {
    float x;
    float y;
    float z;

    cVec3() {}                  // empty user-provided ctor: guards the function-local static below
};

// Four-float vector: rows of the transform, and its two derived vectors.
struct cVec4 {
    float x;
    float y;
    float z;
    float w;
};

extern "C" void  FUN_00f47380(void* p);   // 0x00f47380  null-checked operator delete (cdecl)
extern "C" void* FUN_00f48aa0();          // 0x00f48aa0  reads the active global at 0x016c8ebc

// The object GetDirection hands its scratch vector to; only the (this, out, dir) ABI matters.
struct cViewTarget {
    void Project(cVec3* out, const cVec3* dir);   // 0x00f98800  thiscall, callee pops 8
};

// One 0x14-byte sub-object of cContainer.  Only the leading payload pointer is touched by
// the teardown; the remaining 0x10 bytes belong to the same slot.
struct cSub {
    void* mpData;                         // +0x00
    unsigned char mPad04[0x10];           // +0x04

    inline void Release();
};

// 4x4 transform: two byte flags, two floats, the row-major matrix (four cVec4 rows), then
// two derived four-float vectors.
struct cMat4 {
    unsigned char mb00;                   // +0x00
    unsigned char mb01;                   // +0x01
    unsigned char mPad02[2];              // +0x02
    float mf04;                           // +0x04
    float mf08;                           // +0x08
    cVec4 mRows[4];                       // +0x0c  rows 0..3
    cVec4 mQ;                             // +0x4c
    cVec4 mS;                             // +0x5c

    void   SetColumns(cVec4 v);           // 0x00f4fe50
    void   SetRow(const float* src, char flag);   // 0x00f4ff00
    cVec3* GetDirection(cVec3* out);      // 0x00f501d0
};

// Container whose 12 sub-objects live at +0x16c with a 0x14 stride, plus a trailing
// owned object at +0x30c.
struct cContainer {
    void* volatile mvp00;                 // +0x00
    void* volatile mvp04;                 // +0x04
    void* volatile mvp08;                 // +0x08
    unsigned char mPad0C[0x160];          // +0x0c
    cSub mSubs[12];                       // +0x16c .. +0x25b
    unsigned char mPad25C[0xb0];          // +0x25c
    void* volatile mpExtra;               // +0x30c

    void Destroy();                       // 0x00f50040
};

inline void cSub::Release()
{
    int* p = (int*)mpData;
    if (p != 0 && p[-1] != 0)
        FUN_00f47380(p);
}

// Scratch direction vector shared by both paths of GetDirection (one-shot init guard at
// +0x0c), declared at its retail address so the equivalence harness can bind it.
extern cVec3 g_scratchDirection;          // 0x016c91b4
extern int   g_scratchDirectionInit;      // 0x016c91c0

inline cVec3& ScratchDirection()
{
    if (!(g_scratchDirectionInit & 1))
        g_scratchDirectionInit |= 1;
    return g_scratchDirection;
}

// ---------------------------------------------------------------------------------------------
// Implementations
// ---------------------------------------------------------------------------------------------

// @ 0x00f4fe50
void cMat4::SetColumns(cVec4 v)
{
    const float zero = 0.0f;

    // All four rows get the same (a, b, c, d) vector.
    mRows[3] = v;
    mRows[2] = v;
    mRows[1] = v;
    mRows[0] = v;

    mb00 = 0;
    mb01 = 0;
    mf08 = zero;
    mf04 = zero;

    mQ.x = v.x * zero;
    mQ.y = v.y * zero;
    mQ.z = v.z * zero;
    mQ.w = v.w * zero;

    mS = mQ;
}

// @ 0x00f4ff00
void cMat4::SetRow(const float* src, char flag)
{
    if (flag != 0) {
        const float zero = 0.0f;

        // Replicate the source vector into every row of the matrix (top row last).
        mRows[3] = *(const cVec4*)src;
        mRows[2] = *(const cVec4*)src;
        mRows[1] = *(const cVec4*)src;
        mRows[0] = *(const cVec4*)src;

        const float qx = src[0] * zero;
        const float qy = src[1] * zero;
        const float qz = src[2] * zero;
        const float qw = src[3] * zero;

        mQ.x = qx;
        mQ.y = qy;
        mQ.z = qz;
        mQ.w = qw;

        mS = mQ;

        mb00 = 0;
        mb01 = 0;
        return;
    }

    // Flag clear: only rebase when the source vector differs from the last row.
    if (src[0] == mRows[3].x && src[1] == mRows[3].y &&
        src[2] == mRows[3].z && src[3] == mRows[3].w)
        return;

    mRows[0] = mRows[1];
    mRows[3] = *(const cVec4*)src;
    mb00 = 1;
}

// @ 0x00f50040
void cContainer::Destroy()
{
    mvp00 = (void*)0x148e810;
    mvp04 = (void*)0x148e7fc;
    mvp08 = (void*)0x148e7f8;

    // Release the owned trailing object through its vtable slot 1.
    void* extra = mpExtra;
    if (extra != 0)
        ((void (__thiscall*)(void*))(*(void***)extra)[1])(extra);

    // Release the 12 sub-objects, last slot first.
    mSubs[11].Release();
    mSubs[10].Release();
    mSubs[9].Release();
    mSubs[8].Release();
    mSubs[7].Release();
    mSubs[6].Release();
    mSubs[5].Release();
    mSubs[4].Release();
    mSubs[3].Release();
    mSubs[2].Release();
    mSubs[1].Release();
    mSubs[0].Release();

    mvp08 = (void*)0x13ef094;
    mvp04 = (void*)0x13eb394;
    mvp00 = (void*)0x13eb938;
}

// @ 0x00f501d0
cVec3* cMat4::GetDirection(cVec3* out)
{
    void* target = FUN_00f48aa0();
    if (target != 0) {
        cVec3& d = ScratchDirection();
        const float scale = mRows[1].w;
        d.x = scale * mQ.z;
        d.y = scale * mQ.w;
        d.z = scale * mS.x;
        ((cViewTarget*)target)->Project(out, &d);
        return out;
    }

    cVec3& d = ScratchDirection();
    const float scale = mRows[1].w;
    d.x = scale * mQ.z;
    d.y = scale * mQ.w;
    d.z = scale * mS.x;
    out->x = d.x;
    out->y = d.y;
    out->z = d.z;
    return out;
}
