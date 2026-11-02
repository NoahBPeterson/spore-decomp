// src/game/SPEngine/_at_00690000.cpp -- migrated from slice(s) s0069d090, s0069b910, s00696c80, s00695140, s006925c0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00690000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) double __cdecl strtod(const char*, char**);
#include <new>
#include <intrin.h>
#include <wchar.h>
#include "EA/CommandLine.h"
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include <string.h>
#include "EA/Variant.h"

// ---- items of slice s006925c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) double __cdecl strtod(const char*, char**);
__declspec(noinline) void* FUN_00920090();
struct cSerializerStatus {
    char mPad00[0x24];
    int mCount;     // +0x24
    int mReady;     // +0x28
    bool IsReady() const;
};
struct cSerializerDispatcher {
    char mPad00[0x20];
    void* mpGetContext;     // +0x20
    char mPad24[0x14];
    void* mpCallback;       // +0x38
    unsigned int Dispatch(void* a, void* b);
};
struct cSerializerLazy {
    char mPad00[8];
    void* mpContext;        // +0x08
    bool mbDone;            // +0x0c
    bool Resolve();
};
// ---- items of slice s006925c0 end

// ---- items of slice s00695140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0067e070(int x);   // 0x67e070
extern "C" void FUN_00883780();        // 0x883780
#define VFN(o,off) (*(void***)(o))[(off)/4]
// ---- items of slice s00695140 end

// ---- items of slice s0069b910 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Shape {
    unsigned short flags;   // +0  bit1 => apply orientation
    unsigned short pad;     // +2
    float base[3];          // +4
    float scale;            // +16
    float m[9];             // +20 orientation, rows m[0..2], m[3..5], m[6..8]
};
static inline void XForm(const Shape* s, float x, float y, float z, float* o)
{
    float tx = x;
    float ty = y;
    float tz = z;
    if (s->flags & 2) {
        tx = (s->m[3] * y + s->m[6] * z) + s->m[0] * x;
        ty = (s->m[1] * x + s->m[4] * y) + s->m[7] * z;
        tz = (s->m[2] * x + s->m[5] * y) + s->m[8] * z;
    }
    o[0] = s->base[0] + s->scale * tx;
    o[1] = s->base[1] + ty * s->scale;
    o[2] = s->base[2] + tz * s->scale;
}
static inline void Proj4A(const float* p, float v0, float v1, float v2, float len2,
                          float& mn, float& mx)
{
    for (int q = 0; q < 4; ++q, p += 3) {
        float r = ((p[0] * v0 + p[2] * v2) + v1 * p[1]) / len2;
        r = ((r * v0) * v0 + (r * v2) * v2) + (r * v1) * v1;
        if (mx < r) mx = r;
        if (r < mn) mn = r;
    }
}
static inline void Proj4B(const float* p, float v0, float v1, float v2, float len2,
                          float& mn, float& mx)
{
    for (int q = 0; q < 4; ++q, p += 3) {
        float r = ((p[0] * v0 + p[2] * v2) + p[1] * v1) / len2;
        r = ((r * v2) * v2 + (r * v1) * v1) + (r * v0) * v0;
        if (mx < r) mx = r;
        if (r < mn) mn = r;
    }
}
// ---- items of slice s0069b910 end

// ---- items of slice s0069d090 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void*, const void*, unsigned int);
extern "C" void* copy_705250(const void*, const void*, void*);  // 0x00705250
struct Quad16 { char b[16]; };
struct VecF {
    void* mBegin;   // +0x00
    void* mEnd;     // +0x04
    void* mCap;     // +0x08
    void* pad0;     // +0x0c
    void* pad1;     // +0x10
    void erase() {
        void* first = mBegin;
        void* last  = mEnd;
        memcpy(first, last, (unsigned)((char*)mEnd - (char*)last));
        mEnd = (void*)((int*)mEnd - ((int*)last - (int*)first));
    }
    void eraseQ() {
        Quad16* first = (Quad16*)mBegin;
        Quad16* last  = (Quad16*)mEnd;
        copy_705250(last, last, first);
        mEnd = (void*)((Quad16*)mEnd - (last - first));
    }
};
struct SpVector {
    void* mBegin; void* mEnd; void* mCap; void* pad0; void* pad1;
    void* erase(void* first, void* last);                 // 0x0050f740
    void eraseAll() { erase(mBegin, mEnd); }
};
struct ClrTriple {
    VecF v[3];      // +0x00, +0x14, +0x28
    void clr090();
    void clr100();
    void clr150();
};
// ---- items of slice s0069d090 end

// @ 0x00692700
double ReadDouble(const char* s)
{
    char* end;
    return strtod(s, &end);
}

// @ 0x00692800
bool cSerializerStatus::IsReady() const
{ return mCount != 0 && mReady != 0; }

// @ 0x00692820
unsigned int cSerializerDispatcher::Dispatch(void* a, void* b)
{
    if (mpCallback != 0 && mpGetContext != 0) {
        void* ctx = ((void*(*)(void*))mpGetContext)(this);
        return ((unsigned int(*)(void*,void*,void*))mpCallback)(a, b, ctx);
    }
    return 0;
}

// @ 0x00692850
bool cSerializerLazy::Resolve()
{
    if (!mbDone) {
        void* p = (void*)FUN_00920090();
        if (p) {
            void* q = (void*)FUN_00920090();
            bool r = ((bool(*)(cSerializerLazy*, void*))(((void**)q)[1]))(this, mpContext);
            mbDone = r;
        }
    }
    return mbDone;
}

// @ 0x00695c30
extern "C" bool __fastcall FUN_00695c30(void* self)
{
    if (*(char*)((char*)self + 8) != 0)
    {
        void* p = *(void**)((char*)self + 0x4c);
        if (p != 0)
            ((void(__thiscall*)(void*, int))VFN(p, 0))(p, 1);
        *(void**)((char*)self + 0x4c) = 0;
        FUN_0067e070(0);
        FUN_00883780();
    }
    *(char*)((char*)self + 8) = 0;
    return true;
}

// @ 0x00697960
void* __fastcall ZeroLocalInputState(void* p)
{
  memset(p, 0, 0x48);
  return p;
}

// @ 0x0069b910
extern "C" bool FUN_0069b910(const float* boxA, const Shape* shA, const float* boxB, const Shape* shB)
{
    float A[24];
    float B[24];
    XForm(shA, boxA[0], boxA[1], boxA[2], A + 0);
    XForm(shA, boxA[3], boxA[1], boxA[2], A + 3);
    XForm(shA, boxA[0], boxA[4], boxA[2], A + 6);
    XForm(shA, boxA[3], boxA[4], boxA[2], A + 9);
    XForm(shA, boxA[0], boxA[1], boxA[5], A + 12);
    XForm(shA, boxA[3], boxA[1], boxA[5], A + 15);
    XForm(shA, boxA[0], boxA[4], boxA[5], A + 18);
    XForm(shA, boxA[3], boxA[4], boxA[5], A + 21);
    XForm(shB, boxB[0], boxB[1], boxB[2], B + 0);
    XForm(shB, boxB[3], boxB[1], boxB[2], B + 3);
    XForm(shB, boxB[0], boxB[4], boxB[2], B + 6);
    XForm(shB, boxB[3], boxB[4], boxB[2], B + 9);
    XForm(shB, boxB[0], boxB[1], boxB[5], B + 12);
    XForm(shB, boxB[3], boxB[1], boxB[5], B + 15);
    XForm(shB, boxB[0], boxB[4], boxB[5], B + 18);
    XForm(shB, boxB[3], boxB[4], boxB[5], B + 21);

    float ax[18];
    for (int j = 0; j < 3; ++j) {
        ax[0 + j] = A[0 + j] - A[3 + j];
        ax[3 + j] = A[3 + j] - A[9 + j];
        ax[6 + j] = A[0 + j] - A[12 + j];
        ax[9 + j] = B[0 + j] - B[3 + j];
        ax[12 + j] = B[3 + j] - B[9 + j];
        ax[15 + j] = B[0 + j] - B[12 + j];
    }

    for (int k = 0; k < 6; ++k) {
        float v0 = ax[k * 3 + 0];
        float v1 = ax[k * 3 + 1];
        float v2 = ax[k * 3 + 2];
        float len2 = v0 * v0 + v1 * v1 + v2 * v2;
        float minA = 100000.0f, maxA = -100000.0f;
        float minB = 100000.0f, maxB = -100000.0f;
        Proj4A(A + 0, v0, v1, v2, len2, minA, maxA);
        Proj4A(A + 12, v0, v1, v2, len2, minA, maxA);
        Proj4B(B + 0, v0, v1, v2, len2, minB, maxB);
        Proj4B(B + 12, v0, v1, v2, len2, minB, maxB);
        if (maxA < minB || maxB < minA)
            return false;
    }
    return true;
}

// @ 0x0069d090
void ClrTriple::clr090()
{
    v[0].erase();
    v[1].erase();
    v[2].erase();
}

// @ 0x0069d100
void ClrTriple::clr100()
{
    v[0].erase();
    ((SpVector&)v[1]).eraseAll();
    ((SpVector&)v[2]).eraseAll();
}

// @ 0x0069d150
void ClrTriple::clr150()
{
    v[0].erase();
    v[1].eraseQ();
    v[2].eraseQ();
}
