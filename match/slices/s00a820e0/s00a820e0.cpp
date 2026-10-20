// Slice s00a820e0 -- EA::Swarm::cVisualEffect, the per-instance swarm visual-effect object
// (description pointer at +0x28, state flags at +0x2c, component list at +0x144..+0x148 with
// 0x5c-byte entries, effect-params block at +0x17c), its parameter accessors, and the
// cursor/preroll/start/stop logic.  The small accessors and the transform forwarders are
// reproduced exactly; the larger update routines keep the original field offsets, flag
// order and call sequence.
//
// Flags: default VS2008 (/O2 /MD /Gy /EHsc /TP).
#include "types.h"
#include <math.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed   int   i32;

// ---- generic virtual dispatch into the component / effect vtables -----------
typedef void (__thiscall *Fn0v)(void*);
typedef void (__thiscall *Fn1)(void*, int);
typedef void (__thiscall *Fn2)(void*, int, int);
typedef void (__thiscall *Fn3)(void*, int, int, int);
typedef int  (__thiscall *Fn0i)(void*);
typedef int  (__thiscall *Fn2i)(void*, int, int);
typedef void (__thiscall *FnF2)(void*, float, float, int*);

static inline void* comp(void* elem) { return *(void**)((char*)elem + 0x38); }

// ---- external helpers -------------------------------------------------------
struct cSPTransformOps {
    void FUN_00537dc0(const void* src);              // Assign, 0x00537dc0, thiscall ret 4
};

extern "C" void* FUN_00883860();                     // EA::Messaging::GetServer, 0x00883860
extern "C" void* FUN_00f473a0(u32 size, const char* name, int a, int b, int c, int d); // 0x00f473a0

struct RandomLCG {
    void FUN_00936090(u32 seed);                     // SetSeed, 0x00936090
};
extern RandomLCG g_rngLCG;                           // 0x016778dc

// Effect parameter block allocated on demand at +0x17c (0xd8 bytes).
struct cEffectParams {
    u8 data[0xd8];
    void FUN_007d55e0();                             // ctor, 0x007d55e0
    void FUN_007d4620(int idx, void* val);           // UnknownStore, 0x007d4620, ret 8
    bool GetIntParam(int idx, int* outPtr, u32* outCount);
};

struct cVisualEffect {
    void*  vft0;                                     // 0x00
    void*  vft1;                                     // 0x04 (second base subobject)
    u8     pad08[0x18];                              // 0x08
    i32    m20;                                      // 0x20 (packed name/id)
    i32    m24;                                      // 0x24 simulation time
    i32    m28;                                      // 0x28 description
    u32    m2c;                                      // 0x2c state flags
    u8     pad30[0x20];                              // 0x30
    u32    m50;                                      // 0x50
    u32    m54;                                      // 0x54
    u32    m58;                                      // 0x58
    i32    m5c;                                      // 0x5c notification id
    i32    m60;                                      // 0x60 notification user data
    float  mf64[0x12];                               // 0x64 rigid transform + source-transform head
    u8     padAC[0x94];                              // 0xac
    char*  p140;                                     // 0x140
    char*  p144;                                     // 0x144 component list begin
    char*  p148;                                     // 0x148 component list end
    u8     pad14C[0xc];                              // 0x14c
    void*  p158;                                     // 0x158
    i32    m15c;                                     // 0x15c
    void*  p160;                                     // 0x160
    i32    m164;                                     // 0x164
    u8     pad168[0xc];                              // 0x168
    void*  p174;                                     // 0x174 world/entity table
    void*  p178;                                     // 0x178 LOD object
    cEffectParams* p17c;                             // 0x17c effect params
    i32    m180;                                     // 0x180 seed

    void SetIsHidden(u8 hidden);
    void SetBone(void* bone, int which);
    void* GetBone(int which);
    void SetVectorParams(int a, int b, int c);
    u32* GetVectorParams(u32 idx, u32* count);
    u32* GetFloatParams(u32 idx, u32* count);
    u32* GetIntParams(u32 idx, u32* count);
    u32  GetUnknownParam(u32 idx);
    void SetIsVisible(int visible);
    void SetDescription(int desc);
    void UpdateDescription(int desc);
    bool CheckIfStopped();
    void SelectDescriptionState(int idx);
    void PrerollEffect(int unused, int* stats);
    void Start(int param);
    void SetRigidTransform(const void* src);
    void SetSourceTransform(const void* src);
    void GetTransform(void* out);
    void GetSourceTransform(void* out);
    void ApplyParams();
    void ApplyCursorControl(float* p);
    bool SetUnknownParam(u32 idx, void* val);
};

// @ 0x00a820e0
void cVisualEffect::SetIsHidden(u8 hidden)
{
    if (hidden == (u8)((m2c >> 1) & 1))
        return;
    void** vt = *(void***)((char*)this + 4);
    Fn1 f = (Fn1)vt[0x28 / 4];
    f((char*)this + 4, hidden == 0);
}

// @ 0x00a82130
void cVisualEffect::SetBone(void* bone, int which)
{
    if (which == 1) {
        void* old = p160;
        if (bone != old) {
            if (bone)
                ((Fn0v)(*(void***)bone)[1])(bone);
            p160 = bone;
            if (old)
                ((Fn0v)(*(void***)old)[2])(old);
        }
        m164 = 0;
        return;
    }
    void* old = p158;
    if (bone != old) {
        if (bone)
            ((Fn0v)(*(void***)bone)[1])(bone);
        p158 = bone;
        if (old)
            ((Fn0v)(*(void***)old)[2])(old);
    }
    m15c = 0;
}

// @ 0x00a821c0
void* cVisualEffect::GetBone(int which)
{
    if (which == 1)
        return p160;
    return p158;
}

// @ 0x00a821e0
void cVisualEffect::SetVectorParams(int a, int b, int c)
{
    void** vt = *(void***)this;
    Fn3 f = (Fn3)vt[0x44 / 4];
    f(this, a, b, c * 3);
}

// @ 0x00a82200
u32* cVisualEffect::GetVectorParams(u32 idx, u32* count)
{
    if (idx <= 0x19 && p17c) {
        u16 n = *(u16*)((char*)p17c + 2 + idx * 4);
        if (n) {
            int d = 3;
            if (n % d == 0) {
                if (count)
                    *count = n / d;
                return (u32*)(*(int*)((char*)p17c + 0x64) +
                              *(u16*)((char*)p17c + idx * 4) * 4);
            }
        }
    }
    return 0;
}

// @ 0x00a82260
u32* cVisualEffect::GetFloatParams(u32 idx, u32* count)
{
    if (idx <= 0x19 && p17c) {
        u16 n = *(u16*)((char*)p17c + 2 + idx * 4);
        if (n) {
            if (count)
                *count = n;
            return (u32*)(*(int*)((char*)p17c + 0x64) +
                          *(u16*)((char*)p17c + idx * 4) * 4);
        }
    }
    return 0;
}

// @ 0x00a822b0
u32* cVisualEffect::GetIntParams(u32 idx, u32* count)
{
    if (idx <= 0xa && p17c) {
        u16 n = *(u16*)((char*)p17c + 0x7a + idx * 4);
        if (n) {
            if (count)
                *count = n;
            return (u32*)(*(int*)((char*)p17c + 0xa0) +
                          *(u16*)((char*)p17c + 0x78 + idx * 4) * 4);
        }
    }
    return 0;
}

// @ 0x00a82300
u32 cVisualEffect::GetUnknownParam(u32 idx)
{
    if (idx <= 9 && p17c)
        return *(u32*)((char*)p17c + 0xb4 + idx * 4);
    return 0;
}

// @ 0x00a82330
void cVisualEffect::SetIsVisible(int visible)
{
    if (!(u8)visible)
        m28 |= 2;
    else
        m28 &= ~2;
    char* e = p140;
    char* end = p144;
    for (; e != end; e += 0x5c) {
        void* c = comp(e);
        ((Fn1)(*(void***)c)[0x28 / 4])(c, visible);
    }
}

// @ 0x00a82370
void cVisualEffect::SetDescription(int desc)
{
    m28 = desc;
    m5c = *(i32*)(desc + 8);
    if (*(i32*)(desc + 0x1c) != *(i32*)(desc + 0x20))
        m2c |= 0x800;
    else
        m2c &= ~0x800;
    if (*(float*)(m28 + 0x14) != 0.0f) {
        m2c |= 0x2000;
        m180 = *(i32*)(m28 + 0x40);
        return;
    }
    m2c &= ~0x2000;
    m180 = *(i32*)(m28 + 0x40);
}

// @ 0x00a823e0
void cVisualEffect::UpdateDescription(int desc)
{
    m28 = desc;
    m5c = *(i32*)(desc + 8);
    if (*(i32*)(desc + 0x1c) != *(i32*)(desc + 0x20))
        m2c |= 0x800;
    else
        m2c &= ~0x800;
    u32 a = *(u32*)0x016779fc;
    u32 b = *(u32*)0x01677a00;
    m50 = a;
    m54 = b;
    m180 = *(i32*)(m28 + 0x40);
}

// @ 0x00a82430
bool cVisualEffect::CheckIfStopped()
{
    u32 f = m2c;
    if (!(f & 0x200))
        return true;
    if (m20 < 0)
        return true;
    if (!(f & 0x400) && (*(u32*)m28 & 0x10))
        return false;
    char* end = p148;
    for (char* e = p144; e != end; e += 0x5c) {
        if ((*(u32*)(e + 0x44) & 1) == 0) {
            void* c = comp(e);
            if (((Fn0i)(*(void***)c)[0x10 / 4])(c))
                return false;
        }
    }
    ((Fn1)(*(void***)this)[0xc / 4])(this, 1);
    if (m5c) {
        void* srv = FUN_00883860();
        if (srv) {
            struct Msg { i32 id; void* obj; i32 zero; } msg;
            msg.id = m60;
            msg.obj = this;
            msg.zero = 0;
            ((Fn3)(*(void***)srv)[0x14 / 4])(srv, m5c, (int)&msg, 0);
        }
    }
    return true;
}

// @ 0x00a82500
void cVisualEffect::SelectDescriptionState(int idx)
{
    char* end = p148;
    for (char* e = p144; e != end; e += 0x5c) {
        if (!*(void**)(e + 0x38))
            continue;
        if (!(*(u32*)(e + 0x44) & 8))
            continue;
        if (idx < 0)
            continue;
        if (idx >= (*(i32*)(e + 0x4c) - *(i32*)(e + 0x48)) >> 2)
            continue;
        if (idx > 0)
            m2c |= 8;
        i32 id = *(i32*)(*(i32*)(e + 0x48) + idx * 4);
        int name = m20;
        void** wvt = *(void***)p174;
        int objs = ((Fn0i)wvt[0x30 / 4])(p174);
        int bundle = *(i32*)(*(i32*)(objs + 0x2c) + (name >> 24) * 4);
        int entry = id * 0x84 +
                    *(i32*)((name & 0xffffff) * 0x58 + *(i32*)(bundle + 0x34) + 0x44);
        int arr = *(i32*)(bundle + 0xc);
        int v = *(i32*)(*(i32*)(arr + *(i32*)entry * 0x14) + *(i32*)(entry + 0x80) * 4);
        if (v) {
            void* c = comp(e);
            ((Fn1)(*(void***)c)[0x30 / 4])(c, v);
        }
    }
}

// @ 0x00a825c0
void cVisualEffect::PrerollEffect(int unused, int* stats)
{
    float step = *(float*)0x01457e0c;
    float t = *(float*)(m28 + 0x3c);
    if (!(t > 0.0f))
        return;
    do {
        float f = (step > t) ? t : step;
        char* end = p148;
        for (char* e = p144; e != end; e += 0x5c) {
            void* c = comp(e);
            stats[2]++;
            if (((Fn0i)(*(void***)c)[0x10 / 4])(c)) {
                u32 fl = *(u32*)(e + 0x44);
                float b;
                stats[3]++;
                if (!(fl & 0x80))
                    b = *(float*)((char*)this + 0x4c);
                else if (!(fl & 0x100))
                    b = 1.0f;
                else
                    b = 0.0f;
                float amount = *(float*)(e + 0x40) * f;
                ((FnF2)(*(void***)c)[0x14 / 4])(c, amount, b, stats);
            }
        }
        t -= f;
    } while (t > 0.0f);
}

// @ 0x00a826c0
bool cEffectParams::GetIntParam(int idx, int* outPtr, u32* outCount)
{
    u16 n = *(u16*)((char*)this + 0x7a + idx * 4);
    if (n) {
        *outCount = n;
        int tbl = *(int*)((char*)this + 0xa0);
        *outPtr = tbl + *(u16*)((char*)this + 0x78 + idx * 4) * 4;
        return true;
    }
    return false;
}

// @ 0x00a82700
void cVisualEffect::Start(int param)
{
    int desc = m28;
    if (!desc)
        return;
    u32 f = m2c;
    if ((f & 0x2000) && !(f & 0x10))
        return;
    if ((f & 0x200) && !(f & 0x400))
        return;
    if (*(float*)(desc + 0x3c) > 0.0f && param == 1) {
        m2c |= 0x1000;
        m24 = 0;
    } else {
        m24 = param;
    }
    if (m180)
        g_rngLCG.FUN_00936090(m180);
    char* end = p148;
    for (char* e = p144; e != end; e += 0x5c) {
        void* c = comp(e);
        ((Fn1)(*(void***)c)[0x8 / 4])(c, param);
    }
    if (m5c) {
        void* srv = FUN_00883860();
        if (srv) {
            struct Msg { i32 id; i32 pad0; i32 type; i32 pad1; void* obj; i32 pad2; i32 zero; } msg;
            msg.id = m60;
            msg.type = 1;
            msg.obj = this;
            msg.zero = 0;
            ((Fn3)(*(void***)srv)[0x14 / 4])(srv, m5c, (int)&msg, 0);
        }
    }
    u32 f2 = m2c;
    if (!(f2 & 0x200) && (f2 & 8)) {
        SelectDescriptionState(0);
        m2c &= ~8;
    }
    m2c |= 0x200;
    m2c &= ~0x480;
    m2c |= 0x100;
}

// @ 0x00a82830
void cVisualEffect::SetRigidTransform(const void* src)
{
    ((cSPTransformOps*)mf64)->FUN_00537dc0(src);
    m2c |= 4;
}

// @ 0x00a82850
void cVisualEffect::SetSourceTransform(const void* src)
{
    ((cSPTransformOps*)((char*)this + 0x9c))->FUN_00537dc0(src);
    m2c |= 4;
}

// @ 0x00a82870
void cVisualEffect::GetTransform(void* out)
{
    ((cSPTransformOps*)out)->FUN_00537dc0(mf64);
}

// @ 0x00a82880
void cVisualEffect::GetSourceTransform(void* out)
{
    ((cSPTransformOps*)out)->FUN_00537dc0((char*)this + 0x9c);
}

// @ 0x00a828a0
void cVisualEffect::ApplyParams()
{
    cEffectParams* p = p17c;
    if (!p)
        return;
    for (int i = 0; i < 0x19; i++) {
        if (*(u16*)((char*)p + 2 + i * 4) == 0)
            continue;
        char* end = p148;
        for (char* e = p144; e != end; e += 0x5c) {
            if (*(u32*)(e + 0x44) & 0x20)
                continue;
            void* c = comp(e);
            ((Fn3)(*(void***)c)[0x1c / 4])(c, i,
                *(int*)((char*)p + 0x64) + *(u16*)((char*)p + i * 4) * 4,
                *(u16*)((char*)p + 2 + i * 4));
        }
    }
    for (int i = 0; i < 0xa; i++) {
        if (*(u16*)((char*)p + 0x7a + i * 4) == 0)
            continue;
        char* end = p148;
        for (char* e = p144; e != end; e += 0x5c) {
            if (*(u32*)(e + 0x44) & 0x20)
                continue;
            void* c = comp(e);
            ((Fn3)(*(void***)c)[0x20 / 4])(c, i,
                *(int*)((char*)p + 0xa0) + *(u16*)((char*)p + 0x78 + i * 4) * 4,
                *(u16*)((char*)p + 0x7a + i * 4));
        }
        if (i == 3)
            SelectDescriptionState(*(i32*)(*(i32*)((char*)p + 0xa0) +
                                           *(u16*)((char*)p + 0x84) * 4));
    }
    for (int i = 0; i < 9; i++) {
        i32 v = *(i32*)((char*)p + 0xb4 + i * 4);
        if (!v)
            continue;
        char* end = p148;
        for (char* e = p144; e != end; e += 0x5c) {
            if (*(u32*)(e + 0x44) & 0x20)
                continue;
            void* c = comp(e);
            ((Fn2)(*(void***)c)[0x24 / 4])(c, i, v);
        }
    }
}

// @ 0x00a82a10
void cVisualEffect::ApplyCursorControl(float* p)
{
    float a = mf64[15];                              // +0xa0
    float b = mf64[16];                              // +0xa4
    float c = mf64[17];                              // +0xa8
    if (((u8*)this)[0x64] & 2) {
        float x = mf64[11] * c + mf64[8] * b + mf64[5] * a;
        float y = mf64[12] * c + mf64[9] * b + mf64[6] * a;
        float z = mf64[13] * c + mf64[10] * b + mf64[7] * a;
        a = x;
        b = y;
        c = z;
    }
    float m = mf64[4];
    float qx = mf64[1] + m * a;
    float qy = mf64[2] + m * b;
    float qz = mf64[3] + m * c;
    float dx = p[0] - qx;
    float dy = p[1] - qy;
    float dz = p[2] - qz;
    float num = (p[5] * dz + p[4] * dy) + p[3] * dx;
    float den = (p[5] * p[5] + p[4] * p[4]) + p[3] * p[3];
    float s = -(num / den);
    dx += p[3] * s;
    dy += p[4] * s;
    dz += p[5] * s;
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);

    i32 desc = m28;
    u32 fl = m2c;
    u8 cur = (u8)((fl >> 4) & 1);
    u8 hit = cur;
    if (*(u32*)desc & 0x20000) {
        void* q = p178;
        if ((*(u32*)((char*)q + 0xb8) & *(u32*)((char*)q + 0xb4)) & 1) {
            if (*(float*)(desc + 0x14) > dist)
                hit = 1;
            else
                hit = 0;
        }
    } else if (*(u32*)desc & 0x40000) {
        if (*(float*)(desc + 0x14) > dist) {
            void* q = p178;
            if ((*(u32*)((char*)q + 0xb8) & *(u32*)((char*)q + 0xb4)) & 1)
                hit = cur == 0;
        }
    } else {
        hit = *(float*)(desc + 0x14) > dist;
    }
    if (hit != cur) {
        if (hit) {
            m2c |= 0x10;
            u32 f2 = m2c;
            if (!(f2 & 0x200) || (f2 & 0x400))
                ((Fn1)(*(void***)this)[0x8 / 4])(this, 0);
        } else {
            m2c &= ~0x10;
            u32 f2 = m2c;
            if ((f2 & 0x200) && !(f2 & 0x400))
                ((Fn1)(*(void***)this)[0xc / 4])(this, 0);
        }
    }
}

// @ 0x00a82cc0
bool cVisualEffect::SetUnknownParam(u32 idx, void* val)
{
    if (!p174)
        return false;
    if (m28 && (*(u32*)m28 & 0x80))
        return false;
    bool any = false;
    if (idx > 9)
        return false;
    if (!p17c) {
        cEffectParams* p = (cEffectParams*)FUN_00f473a0(0xd8, "Swarm/EffectParams", 0, 0, 0, 0);
        if (p)
            p->FUN_007d55e0();
        p17c = p;
    }
    p17c->FUN_007d4620(idx, val);
    char* end = p148;
    for (char* e = p144; e != end; e += 0x5c) {
        if (*(u32*)(e + 0x44) & 0x20)
            continue;
        void* c = comp(e);
        if (((Fn2i)(*(void***)c)[0x24 / 4])(c, idx, (int)val))
            any = true;
    }
    return any;
}
