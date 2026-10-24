// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// gold7 batch, worker 5 / slice s00c67560: six companions of the committed
// Ctrl::Update (0x00c678f0).
//
//   0x00c67560  12-byte-element eastl vector insert(pos, n, value) (grow / shift / fill paths)
//   0x00c67730  Ctrl::Fn67730(target): refresh cached target position + orientation quaternion,
//                scale factor (state 0/1 vs 2), then republish if anything changed
//   0x00c680d0  Ctrl::SetState(state): store the state, rebuild the cache and flush orientation
//   0x00c68100  remove one ref-counted noun from a 4-byte-pointer vector
//   0x00c68190  PathObj::Fn68190(h): drop h's neighbours while they sit within 2.0 units of it,
//                reset the anchor triple to a global, then re-propagate positions
//   0x00c68250  PathObj::Fn68250(h): remove h unless it is the only path point
//
// Type model follows the committed s00c67560.cpp (Ctrl), s00c63a60.cpp (PathObj) and
// s00f8f4d0.cpp / s00d9ec20.cpp (the same 12-byte vector insert).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();

struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// ---------------------------------------------------------------------------
// Vector helpers (out-of-line eastl internals, called directly by the retail code)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl F7ec550(void* first, void* last, void* result);   // 0x007ec550 eastl::copy
extern "C" void  __cdecl F6a4100(void* dst, unsigned n, const void* src);  // 0x006a4100 CopyVec12
extern "C" void  __cdecl Fabced0(void* first, void* last, void* result);   // 0x00abced0 copy_backward
extern "C" void  __cdecl Fa177f0(void* first, void* last, const void* v);  // 0x00a177f0 fill
extern "C" void  __cdecl F4797a0(const void* value, void* a, void* b, void* c, void* pos);  // 0x004797a0
extern "C" void* __cdecl Ff473a0(int size, const char* name, int flags, int align,
                                 const char* file, int line);              // 0x00f473a0 operator new
extern "C" void  __cdecl Ff47380(void* p);                                 // 0x00f47380 operator delete
extern "C" void  __cdecl F6782c0(void* first, void* last, void* result);   // 0x006782c0 do_copy
extern "C" char  __cdecl Fc64400(void* a, void* b);                        // 0x00c64400 ComparePairDist

struct cGameNounManager {
    void RemoveNoun(void* noun);                                           // 0x00b225d0
};
cGameNounManager* __cdecl NounManager();                                   // 0x00b3d300

#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------
// 0x00c67560: eastl vector<12-byte element>::insert(pos, n, value)
// ---------------------------------------------------------------------------
struct Vec12 { float x, y, z; };

struct Vec12Vector {
    Vec12*   mpBegin;        // +0x00
    Vec12*   mpEnd;          // +0x04
    Vec12*   mpCapacity;     // +0x08
    uint32_t mPad0c;         // +0x0c
    Vec12*   mpInlineBuf;    // +0x10 (inline storage; never freed)

    void Insert(Vec12* pos, unsigned n, const Vec12& value);
};

// @ 0x00c67560
void Vec12Vector::Insert(Vec12* pos, unsigned n, const Vec12& value)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            Vec12 saved = value;
            unsigned elems = (unsigned)(mpEnd - pos);
            if (n < elems) {
                Vec12* oldEnd = mpEnd;
                Vec12* p = oldEnd - n;
                F4797a0(&value, p, oldEnd, oldEnd, pos);
                mpEnd += n;
                Fabced0(pos, p, oldEnd);
                Fa177f0(pos, pos + n, &saved);
                return;
            }
            unsigned extra = n - elems;
            Vec12* oldEnd = mpEnd;
            F6a4100(mpEnd, extra, &saved);
            mpEnd += extra;
            F4797a0(pos, pos, oldEnd, mpEnd, pos);
            mpEnd += elems;
            Fa177f0(pos, oldEnd, &saved);
        }
    } else {
        unsigned size = (unsigned)(mpEnd - mpBegin);
        unsigned newCap = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + n;
        if (newCap > need)
            need = newCap;

        Vec12* pNew;
        if (need == 0)
            pNew = 0;
        else
            pNew = (Vec12*)Ff473a0((int)(need * 0xc), "Simulator", 0, 0, ALLOC_FILE, 0xd1);

        Vec12* newPos = (Vec12*)F7ec550(mpBegin, pos, pNew);
        F6a4100(newPos, n, &value);
        Vec12* newEnd = (Vec12*)F7ec550(pos, mpEnd, newPos + n);

        if (mpBegin != 0 && mpBegin != mpInlineBuf)
            Ff47380(mpBegin);
        mpBegin = pNew;
        mpEnd = newEnd;
        mpCapacity = pNew + need;
    }
}

// ---------------------------------------------------------------------------
// Camera ring controller
// ---------------------------------------------------------------------------
struct CtrlTarget {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();   // slots 0..10
    virtual const V3* GetPosition();                                   // +0x2c
    virtual const Quat* GetOrientation();                              // +0x30
    virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual float GetSpan();                                           // +0x70
    virtual float GetSpan2();                                          // +0x74
};

// The object held through Ctrl::mpTargetRef; bit 0 of +0x04 marks it attached.
struct TrackedRef {
    void*    mVtbl;          // +0x00
    uint32_t mFlags;         // +0x04
};

struct Ctrl {
    uint8_t pad00[0xd0];
    TrackedRef* mpTargetRef;         // +0xd0
    uint8_t padD4[0x198 - 0xd4];
    V3   mPos;                       // +0x198
    Quat mOut;                       // +0x1a4
    float mScale;                    // +0x1b4
    int   mState;                    // +0x1b8

    void MarkChanged();              // 0x00c640e0
    void Recompute();                // 0x00c64170
    void FlushOrientation();         // 0x00c66c10

    void Attach(CtrlTarget* target);
    void SetState(int state);
};

// @ 0x00c67730
void Ctrl::Attach(CtrlTarget* target)
{
    if (mpTargetRef != 0) {
        if (target == 0) {
            mpTargetRef->mFlags &= ~1u;
            return;
        }
        mpTargetRef->mFlags |= 1u;
    }
    if (target == 0)
        return;

    bool changed = false;

    V3 pos = *target->GetPosition();
    if (mPos.x != pos.x || mPos.y != pos.y || mPos.z != pos.z) {
        mPos = pos;
        changed = true;
    }

    Quat q = *target->GetOrientation();
    if (mOut.x != q.x || mOut.y != q.y || mOut.z != q.z || mOut.w != q.w) {
        mOut = q;
        changed = true;
        FlushOrientation();
    }

    float f = (mState == 2) ? target->GetSpan2() : target->GetSpan();
    if (mScale != f) {
        mScale = f;
        Recompute();
    }

    if (changed)
        MarkChanged();
}

// @ 0x00c680d0
void Ctrl::SetState(int state)
{
    if (mState != state) {
        mState = state;
        MarkChanged();
        FlushOrientation();
    }
}

// ---------------------------------------------------------------------------
// Path object (see the committed s00c63a60.cpp model)
// ---------------------------------------------------------------------------
struct PtrVec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
};

struct Noun {
    virtual void v00();          // +0x00
    virtual void Release();      // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual void v0e(); virtual void v0f(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual void Detach(int arg);    // +0x54
};

// Remove one noun from the pointer vector (releases the vacated slot).
void RemoveFromVec(PtrVec* vec, void* noun);

// @ 0x00c68100
void RemoveFromVec(PtrVec* vec, void* noun)
{
    ((Noun*)noun)->Detach(0);
    NounManager()->RemoveNoun(noun);

    int i = 0;
    while (i < (int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2) {
        if (vec->mpBegin[i] == noun)
            goto found;
        ++i;
    }
    i = 0;
found:

    void** begin = vec->mpBegin;
    void** end = vec->mpEnd;
    void** p = begin + i;
    if (p + 1 < end)
        F6782c0(p + 1, end, p);

    vec->mpEnd -= 1;
    Noun* last = (Noun*)*vec->mpEnd;
    if (last != 0)
        last->Release();
}

struct PathObj {
    uint8_t mFlag;           // +0x00
    char    pad01[3];
    void**  mpBegin;         // +0x04
    void**  mpEnd;           // +0x08
    char    pad0c[0x0c];
    V3      mV;              // +0x18 (anchor triple)

    void Fn64460(void* h);   // 0x00c64460
    void Fn68190(void* h);
    bool Fn68250(void* h);
};

extern "C" V3 g1693d74;      // 0x01693d74: anchor position

// @ 0x00c68190
void PathObj::Fn68190(void* h)
{
    mV = g1693d74;
    PtrVec* vec = (PtrVec*)&mpBegin;

    for (;;) {
        void** p = vec->mpBegin;
        int count = (int)((char*)vec->mpEnd - (char*)p) >> 2;
        int i = 0;
        if (count > 0) {
            do {
                if (*p == h) {
                    if (i <= 0)
                        goto forward;
                    void* prev = vec->mpBegin[i - 1];
                    if (!Fc64400(prev, h))
                        goto forward;
                    RemoveFromVec(vec, prev);
                    goto top;
                }
                ++i;
                ++p;
            } while (i < count);
        }
        i = 0;

    forward:
        if (((int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2) - 1 <= i)
            break;
        void* next = vec->mpBegin[i + 1];
        if (!Fc64400(next, h))
            break;
        RemoveFromVec(vec, next);
    top:;
    }

    return Fn64460(0);
}

// @ 0x00c68250
bool PathObj::Fn68250(void* h)
{
    PtrVec* vec = (PtrVec*)&mpBegin;
    if (vec->mpEnd - vec->mpBegin == 1)
        return false;
    RemoveFromVec(vec, h);
    return true;
}
