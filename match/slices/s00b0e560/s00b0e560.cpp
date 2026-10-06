// Slice s00b0e560 (batch bfs1) — 19 functions.
// Module "Spore".  Source for every VA in the slice; each block starts with its
// original address.  See s00b0e560.h for the recovered class shapes.
//
// Functions 00b0e560..00b0ee10 operate on a serialization / render-queue manager
// that owns several spstl::slot_vector and EASTL list members; the virtual calls
// go through the interfaces returned by the reader chain.  They are behaviourally
// complete but not byte-exact (the spstl container templates are not reproduced).

#include "s00b0e560.h"
#include "types.h"
#include <math.h>

extern "C" void ResetEffectStates();                          // 0x006f3290
extern "C" void ReadInt32(void*, void*, int, int);            // EA::IO::ReadInt32 0x0093a780
extern "C" void ctor_00afb7a0();                              // 0x00afb7a0
extern "C" void* SP_BehaviorManager();                        // 0x00b3d260
extern "C" void destructor_00f47380(void*);                   // operator delete 0x00f47380
extern "C" void eastl_list_erase(void*);                      // 0x0075f3f0
extern "C" void FUN_00b0d710(void*, int, void*);
extern "C" void FUN_00b0dec0(void*, ...);
extern "C" void FUN_00b0e250(void*, void*);
extern "C" void FUN_00b0e490(void*);
extern "C" void* FUN_00b0d1d0(void*, void*, void*);
extern "C" void FUN_00b0cfd0(void*, void*);
extern "C" void FUN_00b0cf80(void*, void*, void*, void*);
extern "C" void FUN_00b0d500(void*, void*);
extern "C" void FUN_00b0d050(void*);
extern "C" void FUN_00abec70(void*);
extern "C" void FUN_00abf2b0();
extern "C" void FUN_00abf110(void*);
extern "C" void FUN_00ac0010(void*);
extern "C" void FUN_00b0dc60();
extern float g_2pi;                                           // +0x167bd10

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

template<class R> static inline R vcall0(void* p, int off)
{ return ((R(__thiscall*)(void*))g_vfn(p, off))(p); }
template<class R, class A1> static inline R vcall1(void* p, int off, A1 a1)
{ return ((R(__thiscall*)(void*, A1))g_vfn(p, off))(p, a1); }
template<class R, class A1, class A2> static inline R vcall2(void* p, int off, A1 a1, A2 a2)
{ return ((R(__thiscall*)(void*, A1, A2))g_vfn(p, off))(p, a1, a2); }
template<class R, class A1, class A2, class A3> static inline R vcall3(void* p, int off, A1 a1, A2 a2, A3 a3)
{ return ((R(__thiscall*)(void*, A1, A2, A3))g_vfn(p, off))(p, a1, a2, a3); }

// ===========================================================================
// Polymorphic input host (vtable + cLocalInputState at +0x31c)
// ===========================================================================

// @ 0x00b0f140
bool InputHost::FUN_00b0f140(int /*unused*/)
{
    mInput.Reset();
    return false;
}

// @ 0x00b0f170
void InputHost::FUN_00b0f170()
{
    v50();
    ResetEffectStates();
}

// @ 0x00b0f190
bool InputHost::FUN_00b0f190(int vkCode, int modifiers)
{
    mInput.OnKeyDown(vkCode, modifiers);
    return false;
}

// @ 0x00b0f1b0
bool InputHost::FUN_00b0f1b0(int button, float x, float y, int state)
{
    mInput.OnMouseDown(button, x, y, state);
    return true;
}

// @ 0x00b0f1e0
bool InputHost::FUN_00b0f1e0(int button, float x, float y, int state)
{
    mInput.OnMouseUp(button, x, y, state);
    return false;
}

// @ 0x00b0f210
void InputHost::FUN_00b0f210(float* out0, float* out1, float* out2)
{
    *out0 = m15c;
    *out1 = m138;
    *out2 = m114;
}

// @ 0x00b0f240
void InputHost::FUN_00b0f240(float* out0, float* out1, float* out2)
{
    *out0 = m154;
    *out1 = m130;
    *out2 = m10c;
}

// ===========================================================================
// Math helpers
// ===========================================================================

// @ 0x00b0f060
// Hermite smoothstep: clamp x into [lo,hi], normalise, then t*t*(3 - 2t).
// The Clamp step is the module's SSE __asm helper (maxss/minss), as used by the
// /arch:SSE math code in this binary.
static __forceinline float ClampSSE(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x;
        maxss xmm0, lo;
        minss xmm0, hi;
        movss x, xmm0;
    }
    return x;
}

float FUN_00b0f060(float lo, float hi, float x)
{
    float v = ClampSSE(x, lo, hi);
    float t = (v - lo) / (hi - lo);
    return t * t * (3.0f - 2.0f * t);
}

// @ 0x00b0f0c0
// Wraps the delta (b - a) into (-pi, pi] and returns a + delta * t.
extern float g_pi;                              // +0x1567dc8
float FUN_00b0f0c0(float a, float b, float t)
{
    float d = b - a;
    float r = (float)fmod((double)d, (double)g_2pi);
    if (r > g_pi)
        r = r - g_2pi;
    else if (r < -g_pi)
        r = r + g_2pi;
    return r * t + a;
}

// ===========================================================================
// Serialization / render-queue manager
// ===========================================================================

// @ 0x00b0e560
// Reads a count from the stream, resizes the slot vector, then for each slot
// releases the old element and lets the host re-create it.
void cRenderQueue::FUN_00b0e560(int host_, int vec_, uint32_t flags)
{
    char* host = (char*)host_;
    uint32_t* vec = (uint32_t*)vec_;
    void* obj = vcall0<void*>(host, 0x20);
    void* reader = vcall0<void*>(obj, 0x18);
    int count = 0;
    ReadInt32(reader, &count, 1, (int)flags);

    uint32_t beg = vec[0], end = vec[1];
    int n = (int)(end - beg) >> 2;
    if (n < count)
    {
        int zero = 0;
        FUN_00b0d710((void*)end, count - n, &zero);
    }
    else
    {
        FUN_00b0dec0((void*)(beg + count * 4), (void*)end);
    }

    for (int i = 0; i < count; ++i)
    {
        char* slot = (char*)(vec[0] + i * 4);
        void* p = *(void**)slot;
        if (p)
        {
            *(void**)slot = 0;
            vcall0<void>(p, 0x5c);
        }
        vcall3<void, uint32_t, void*, int>(host, 0x28, flags, slot, 0);
    }
}

// @ 0x00b0e610
// Clears the +0x20 slot vector then reads a replacement from the stream.
bool cRenderQueue::FUN_00b0e610(int host_)
{
    char* self = (char*)this;
    char* host = (char*)host_;
    uint32_t tmp[3] = { 0, 0, 0 };
    FUN_00b0e250(tmp, self + 0x20);
    FUN_00b0dec0(tmp, (void*)0, (void*)0);
    void* obj = vcall0<void*>(host, 0x20);
    void* reader = vcall0<void*>(obj, 0x18);
    ReadInt32(reader, self + 0x94, 1, 0);
    FUN_00b0e560(host_, (int)(self + 0x20), 0x11c0ba3u);
    ctor_00afb7a0();
    return true;
}

// @ 0x00b0e6a0
// Resets the two slot vectors at +0x5c and +0x78 and empties the render-job list.
void cRenderQueue::FUN_00b0e6a0()
{
    char* self = (char*)this;
    uint32_t tmp[3] = { 0, 0, 0 };
    FUN_00b0e250(tmp, self + 0x20);
    FUN_00b0dec0(tmp, (void*)0, (void*)0);

    {   // slot vector at +0x5c
        void* b = *(void**)(self + 0x5c);
        void* e = *(void**)(self + 0x60);
        void* p = FUN_00b0d1d0(e, e, b);
        FUN_00b0cfd0(p, *(void**)(self + 0x60));
        *(int*)(self + 0x60) = *(int*)(self + 0x60) + ((int)((char*)e - (char*)b) >> 3) * -8;
        *(uint32_t*)(self + 0x70) = 0x3fffffffu;
        *(uint32_t*)(self + 0x74) = 0x3fffffffu;
    }
    {   // slot vector at +0x78
        void* b = *(void**)(self + 0x78);
        void* e = *(void**)(self + 0x7c);
        void* p = FUN_00b0d1d0(e, e, b);
        FUN_00b0cfd0(p, *(void**)(self + 0x7c));
        *(int*)(self + 0x7c) = *(int*)(self + 0x7c) + ((int)((char*)e - (char*)b) >> 3) * -8;
        *(uint32_t*)(self + 0x8c) = 0x3fffffffu;
        *(uint32_t*)(self + 0x90) = 0x3fffffffu;
    }
    eastl_list_erase(self + 0x34);            // eastl::list<cRenderJob>::clear()
    *(int*)(self + 0x34) = (int)(self + 0x34);
    *(int*)(self + 0x38) = (int)(self + 0x34);
    *(int*)(self + 0x98) = 0;
    ctor_00afb7a0();
}

// @ 0x00b0e780
// Iterates a bit-index range and relocates the referenced slot entries.
cRenderQueue* cRenderQueue::FUN_00b0e780(int src_)
{
    char* self = (char*)this;
    uint32_t* src = (uint32_t*)src_;
    FUN_00abec70(src);

    uint32_t count = (((src[1] - src[0]) >> 2) << 7) + src[5] - 0x7f;
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t* s = (uint32_t*)(*(uint32_t*)(src[0] + (i >> 7) * 4) + (i & 0x7f) * 8);
        FUN_00abf2b0();
        uint32_t* d = (uint32_t*)(*(uint32_t*)(*(uint32_t*)(self + 4) - 4) + *(uint32_t*)(self + 0x14) * 8);
        if (d)
        {
            *d = *s;
            if ((*s & 0x80000000u) == 0 && d + 1)
            {
                d[1] = s[1];
                if (s[1])
                    vcall0<void>((void*)s[1], 0x60);
            }
        }
    }
    return this;
}

// @ 0x00b0e810
// Refcounts one element into the +0x60 slot vector and swaps it out.
void cRenderQueue::FUN_00b0e810(int p_)
{
    char* self = (char*)this;
    void* p = (void*)p_;
    if (p)
        vcall0<void>(p, 0x0);
    FUN_00b0e490(&p);
    if (p)
        vcall0<void>(p, 0x4);

    char* v = self + 0x44;
    uint32_t idx = *(uint32_t*)(v + 0x14);
    void* cur = (idx < 0x3fffffffu)
        ? (void*)(*(uint32_t*)v + idx * 8)
        : *(void**)(v + 4);
    uint32_t out = 0;
    FUN_00b0cf80(&p, cur, *(void**)(v + 4), &out);
    FUN_00b0d500(&out, p);
}

// @ 0x00b0e890
// Removes all dead jobs from the +0x38 list.
void cRenderQueue::FUN_00b0e890()
{
    char* self = (char*)this;
    char* sentinel = self + 0x38;
    char* it = *(char**)sentinel;
    while (it != sentinel)
    {
        void* job = *(void**)(it + 8);
        char* next;
        if (job)
            vcall0<void>(job, 0x0);
        if (!vcall0<int>(job, 0x58))
        {
            next = *(char**)it;
        }
        else
        {
            vcall0<void>(job, 0x20);
            FUN_00b0e490(&job);
            next = *(char**)it;
            char* node = *(char**)(next + 4);
            *(int*)(*(int*)(node + 4)) = *(int*)node;
            *(int*)(*(int*)node + 4) = *(int*)(node + 4);
            if (*(void**)(node + 8))
                vcall0<void>(*(void**)(node + 8), 0x4);
            destructor_00f47380(node);
        }
        if (job)
            vcall0<void>(job, 0x4);
        it = next;
    }
}

// @ 0x00b0e920
// Removes unused entries from the +0x7c and +0x5c slot vectors.
void cRenderQueue::FUN_00b0e920()
{
    char* self = (char*)this;
    {   // clear +0x7c
        char* v = self + 0x7c;
        void* b = *(void**)v;
        void* e = *(void**)(v + 4);
        void* p = FUN_00b0d1d0(e, e, b);
        FUN_00b0cfd0(p, *(void**)(v + 4));
        *(int*)(v + 4) = *(int*)(v + 4) + ((int)((char*)e - (char*)b) >> 3) * -8;
        *(uint32_t*)(v + 0x14) = 0x3fffffffu;
        *(uint32_t*)(v + 0x18) = 0x3fffffffu;
    }
    char* v = self + 0x5c;
    uint32_t* cur = (*(uint32_t*)(v + 0x14) < 0x3fffffffu)
        ? (uint32_t*)(*(uint32_t*)(v + 4) + *(uint32_t*)(v + 0x14) * 8)
        : *(uint32_t**)(v + 8);
    uint32_t* end = *(uint32_t**)(v + 8);
    while (cur != end)
    {
        FUN_00b0e490(cur + 1);
        do
        {
            uint32_t w = *cur; cur += 2;
            if (w >> 30 & 1) break;
        } while ((int)*cur >= 0);
    }
    uint32_t* a = *(uint32_t**)(v + 8);
    uint32_t* b = *(uint32_t**)(v + 4);
    for (uint32_t* q = b; q != a; q += 2)
        FUN_00b0d050(q);
    for (uint32_t* q = b; q < a; q += 2)
        if ((-1 < (int)q[0]) && q[1])
            vcall0<void>((void*)q[1], 0x4);
    *(int*)(v + 8) = *(int*)(v + 8) + ((int)((char*)a - (char*)b) >> 3) * -8;
    *(uint32_t*)(v + 0x18) = 0x3fffffffu;
    *(uint32_t*)(v + 0x1c) = 0x3fffffffu;
}

// @ 0x00b0ea30
// Destroys the per-frame jobs and empties the manager.
void cRenderQueue::FUN_00b0ea30()
{
    char* self = (char*)this;
    uint32_t n = (uint32_t)((*(int*)(self + 0x28) - *(int*)(self + 0x24)) >> 2);
    for (uint32_t i = 0; i < n; ++i)
        vcall0<void>(*(void**)(*(uint32_t*)(self + 0x24) + i * 4), 0x34);

    while (*(uint32_t*)(self + 0x58) != 0x3fffffffu)
        vcall1<void, uint32_t>(self, 0x18, *(uint32_t*)(self + 0x58));
    while (*(uint32_t*)(self + 0x9c) != 0x3fffffffu || *(uint32_t*)(self + 0xb8) != 0x3fffffffu)
    {
        FUN_00b0dc60();
        FUN_00b0e920();
    }
    char* sentinel = self + 0x38;
    char* it = *(char**)sentinel;
    while (it != sentinel)
    {
        char* next = *(char**)it;
        if (*(void**)(it + 8))
            vcall0<void>(*(void**)(it + 8), 0x4);
        destructor_00f47380(it);
        it = next;
    }
    *(int*)(self + 0x3c) = (int)sentinel;
    *(int*)sentinel = (int)sentinel;
}

// @ 0x00b0eae0
// Interaction-agent tick: rebuild the +0x44 slots, then run each agent's
// interactions into the +0x20 vector.
void cRenderQueue::FUN_00b0eae0(int agents_, int flag)
{
    char* self = (char*)this;
    (void)agents_; (void)flag;
    FUN_00b0dc60();
    FUN_00b0e920();

    if (*(int*)(self + 0x50) == 0 || *(char*)(self + 0x9c) != 0)
        return;
    *(int*)(self + 0x98) = *(int*)(self + 0x50);

    char* v = self + 0x40;
    uint32_t* it = (*(uint32_t*)(v + 0x14) < 0x3fffffffu)
        ? (uint32_t*)(*(uint32_t*)(v + 4) + *(uint32_t*)(v + 0x14) * 8)
        : *(uint32_t**)(v + 8);
    uint32_t* vend = *(uint32_t**)(v + 8);
    while (it != vend)
    {
        void* agent = (void*)it[1];
        if (agent)
            vcall0<void>(agent, 0x0);
        if (*(int*)((char*)agent + 0x70) == 1)
            FUN_00ac0010(agent);
        *(int*)((char*)agent + 0x70) = vcall0<int>(agent, 0x18);
        if (!vcall0<int>(agent, 0x58))
        {
            void* bm = SP_BehaviorManager();
            vcall1<void, void*>(bm, 0x18, agent);
        }
        vcall0<void>(agent, 0x4);
        do { uint32_t w = *it; it += 2; if (w >> 30 & 1) break; } while ((int)*it >= 0);
    }

    char* w = self + 0x20;
    uint32_t* q = *(uint32_t**)w;
    uint32_t* qend = *(uint32_t**)(w + 4);
    void* alive = 0;
    for (; q != qend; ++q)
    {
        void* x = (void*)*q;
        if (x != alive)
        {
            if (x) vcall0<void>(x, 0x60);
            if (alive) vcall0<void>(alive, 0x5c);
            alive = x;
        }
        if (vcall0<char>(alive, 0x1c))
        {
            void* y = vcall0<void*>(alive, 0x20);
            if (*(int*)((char*)y + 0x70) == 0)
            {
                void* old = 0;
                if (y != old)
                {
                    if (y) vcall0<void>(y, 0x0);
                    if (old) vcall0<void>(old, 0x4);
                }
                FUN_00abf110(y);
                uint32_t a = 0, b = 0, c = 0, d = 0, e = 0, f2 = 0;
                if (a + b != c + d)
                    vcall2<void, uint32_t, uint32_t>(alive, 0x44, a, b);
                (void)e; (void)f2;
            }
        }
    }
    FUN_00b0e890();
    if (alive) vcall0<void>(alive, 0x4);
}

// @ 0x00b0ee10
// Selects the next live job, advancing past dead slots.
void cRenderQueue::FUN_00b0ee10(int start_, int flag)
{
    char* self = (char*)this;
    (void)flag;
    char* v = self + 0x44;
    uint32_t* it = (*(uint32_t*)(v + 0x14) < 0x3fffffffu)
        ? (uint32_t*)(*(uint32_t*)v + *(uint32_t*)(v + 0x14) * 8)
        : *(uint32_t**)(v + 4);
    uint32_t* end = *(uint32_t**)(v + 4);
    int budget = (start_ != -1) ? (start_ + 1) : 0;
    uint32_t local[3] = { 0, 0, 0 };
    (void)local;
    while (it != end)
    {
        char* job = (char*)it[1];
        if (job)
        {
            void* obj = vcall1<void*, int>(job, 0x8, 0x1186577);
            if (obj && vcall0<char>(obj, 0x58))
            {
                if (budget) { --budget; }
                else
                {
                    FUN_00abec70(local);
                    break;
                }
            }
        }
        do { uint32_t w = *it; it += 2; if (w >> 30 & 1) break; } while ((int)*it >= 0);
    }
}