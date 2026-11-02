// src/game/Spui/_at_007f0000.cpp -- migrated from slice(s) s007ffc70, s007fed20, s007fd840, s007fc880, s007f8540 by tools/migrate/rewrite.py
// Object file: Spui/_at_007f0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <new>
#include <cstddef>
#include "EA/Stopwatch.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s007f8540 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t, const char* name, int a, int b, int c, int d);
// ---- items of slice s007f8540 end

// ---- items of slice s007fc880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_ser_type_7fd430[];
inline void* VCallR(void* o, int off) {
    return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline bool VCallB(void* o, int off) {
    return ((bool(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
inline void VCallV(void* o, int off) {
    ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
void* f_5701b0(void* a, void* b, void* c, unsigned d); // hash find
void  f_50e200(void* p);                              // hash free node
void  f_56f3e0(void* a, void* b);                     // hash lookup
void* f_8ac360(int n, void* p);                       // allocate raw
void  f_7fcff0(void* p);                              // refcount release
void  f_7fd140(void* p);                              // refcount add
struct FlagObj {
    char pad0[0x10];
    unsigned mFlags;        // +0x10
    char pad1[0x24];        // +0x14 .. +0x37
    void* mpOwner;          // +0x38
    void SetFlag(unsigned mask, bool on);   // @ 0x007fd200
};
struct SerBuffer {
    void* type;      // +0
    void* base;      // +4
    unsigned count;  // +8
};
struct SerItem14 {
    char pad[0x14];
    unsigned count;  // +0x14
};
struct C53 {
    char pad0[4];
    unsigned off;
    void* M(SerItem14* item);
};
struct Vec8 {
    void* b; void* e; void* c; void* alloc;
    void* Insert(void* pos, void* value);
    void* Emplace(void* pos, void* value);
};
// ---- items of slice s007fc880 end

// ---- items of slice s007fd840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_f164b620;   // 0x0164b620 (equiv t3)
inline void* VCallR1(void* o, int off, int a) {
    return ((void*(__thiscall*)(void*, int))(*(void**)((char*)*(void**)o + off)))(o, a);
}
struct IObj {
    virtual void AddRef();
    virtual void Release();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
};
struct Damped {
    char  pad0[0xc];
    float mParamDuration;        // +0x0c
    float mParamFrequency;       // +0x10
    float mParamDamping;         // +0x14
    char  pad18[8];
    float mParamPreDelayFactor;  // +0x20
    float mParamPostDelayFactor; // +0x24
    char  pad28[0x18];
    float mWorkTimeFrom;         // +0x40
    float mWorkTimeTo;           // +0x44
    char  mbCeilingMode;         // +0x48
    char  pad49[3];
    unsigned mPeriodicType;      // +0x4c
    float v25(float t);          // @ 0x007fd840
    bool  v24();                 // @ 0x007fd890
};
struct SerItem { void* type; void* base; unsigned count; void* extra; };
// ---- items of slice s007fd840 end

// ---- items of slice s007fed20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vt_sc_a[], vt_sc_b[];                                  // 0x14163f8 0x14163e8
inline int VCallI(void* o, int off) {
    return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)o + off)))(o);
}
struct SerItem3 { void* f0; void* f4; void* f8; void* fC; };
struct Obj7fb250 {
    void f(SerItem3* out);                            // 0x7fb250 ret 4
};
struct EvApi {                                          // thiscall helpers
    void BaseCtor();                                    // 0x7fbf40 ret 0
    void SetWinMessageType(unsigned);                   // 0x7fec00 ret 4
    void SetMessageWinId(unsigned);                     // 0x7fec90 ret 4
    void InterpBaseCtor();                              // 0x7fba00 ret 0
};
struct PredState {
    char pad0[0x14];
    void* mpEvent;            // +0x14
    unsigned mWinStateQuery;  // +0x18
    void* mpQueryWindow;      // +0x1c
    unsigned mQueryWindowId;  // +0x20
    unsigned mQueryHexParam;  // +0x24
    unsigned mRelationToWindow; // +0x28
    int Refresh();
};
struct ShadeColorFull {
    char pad0[0xc];
    char mbFrom;          // +0xc
    char mbUseWin;        // +0xd
    char padE[2];
    void* mpWindow;       // +0x10
    unsigned mColorTo;    // +0x14
    unsigned mColorFrom;  // +0x18
    ShadeColorFull* Ctor();
};
// ---- items of slice s007fed20 end

// ---- items of slice s007ffc70 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(p, off) (*(void***)(p))[((off) >> 2)]
void* __cdecl f_7ffa50();
uint8_t __cdecl f_809700(void* a, void* b, void* c);
class cSPUIBehaviorPredicateWinState { public:
  char pad0[0x14];
  void* mpQueryWindow;        // +0x14
  uint32_t mWinStateQuery;    // +0x18
  char pad1c[0x8];
  uint32_t mQueryHexParam;    // +0x24
  char pad28[4];
  uint8_t Evaluate();
};
// ---- items of slice s007ffc70 end

// ---- items of slice s007fc880_o2 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PrimBase {
    virtual void  v00();
    virtual void  v01();
    virtual void  v02();
    virtual void  v03();
    virtual void  v04();
    virtual void  v05();
    virtual void  v06();
    virtual void  v07();
    virtual void  v08();
    virtual void  v09();      // +0x24
    virtual void  v10();
    virtual void  v11();
    virtual void  v12(bool);  // +0x30
    virtual void  v13();
    virtual bool  v14();      // +0x38
    virtual bool  v15();      // +0x3c
    virtual void  v16();
    virtual void  v17();
    virtual void  v18();
    virtual void  v19();
    virtual void  v20();
    virtual void  v21();
    virtual float v22(float); // +0x58
    virtual void  v23();
    virtual bool  v24();      // +0x60
    virtual float v25(float); // +0x64
};
struct RefCountBase {
    virtual long AddRef();
    virtual long Release();
    virtual long GetRefCount();
    int mRefCount;            // +0x08
};
class cSPUIBehaviorTimeFunction_s007f_c880__o2 : public PrimBase, public RefCountBase { public:
    float mParamDuration;         // +0x0c
    float mParamFrequency;        // +0x10
    float mParamDamping;          // +0x14
    float mParamEaseInTimeFactor; // +0x18
    float mParamEaseOutTimeFactor;// +0x1c
    float mParamPreDelayFactor;   // +0x20
    float mParamPostDelayFactor;  // +0x24
    float mParamUser1;            // +0x28
    float mParamUser2;            // +0x2c
    float mParamUser3;            // +0x30
    float mParamUser4;            // +0x34
    bool  mbExpired;              // +0x38
    bool  mbNegated;              // +0x39
    bool  mbDirty;                // +0x3a
    float mTime;                  // +0x3c
    float mWorkTimeFrom;          // +0x40
    float mWorkTimeTo;            // +0x44

    float Ease(float t);          // @ 0x007fae90 (non-virtual)
    void  SetParams(float duration, float pre, float post);
    cSPUIBehaviorTimeFunction_s007f_c880__o2();
    // base virtuals referenced out of line
    virtual void  v12(bool);
    virtual bool  v15();
    virtual bool  v24();
    virtual float v22(float);
};
class cSPUIBehaviorTimeFunctionRamp : public cSPUIBehaviorTimeFunction_s007f_c880__o2 { public:
    cSPUIBehaviorTimeFunctionRamp();
    virtual float v22(float t);   // @ 0x007fd4e0
    virtual bool  v24();          // @ 0x007fd540
    void SetParams(float duration, float pre, float post); // @ 0x007fd4a0
};
class cSPUIBehaviorTimeFunctionDampedPeriodic : public cSPUIBehaviorTimeFunction_s007f_c880__o2 { public:
    bool  mbCeilingMode;          // +0x48
    bool  mbInitialized;          // +0x49
    char  pad4a[2];
    unsigned int mPeriodicType;   // +0x4c

    cSPUIBehaviorTimeFunctionDampedPeriodic(bool ceiling);
    void  SetParams(float duration, float pre, float post, float freq, float damping, int periodicType);
    virtual void  v12(bool param);          // @ 0x007fd6b0
    virtual bool  v15();                    // @ 0x007fd700
    virtual float v22(float t);             // 0x007fd790
};
// ---- items of slice s007fc880_o2 end

// @ 0x007f9340
void* FUN_007f9340(void** p, void** out)
{
    p[0] = (void*)0x13f6400;
    p[2] = (void*)0x13f63fc;
    p[3] = 0;
    void** obj = (void**)operator new(0x1c, "UI/cSPUIAnimationSequence", 0, 0, 0, 0);
    if (obj != 0) {
        obj[0] = (void*)0x141542c;
        obj[1] = 0;
        obj[2] = 0;
        obj[3] = 0;
        obj[4] = 0;
    } else {
        obj = 0;
    }
    p[4] = obj;
    if (out != 0) *out = obj;
    p[1] = (void*)0x7f9230;
    return p;
}

// @ 0x007fcf40
void* Vec8::Emplace(void* pos, void* value)
{
    void** self = (void**)this;
    void* begin = *self;
    int idx = ((char*)pos - (char*)begin) >> 3;
    if (pos == self[1] && self[1] != self[2]) {
        void* slot = self[1];
        self[1] = (char*)self[1] + 8;
        void* m = f_8ac360(8, slot);
        if (m) {
            *(void**)m = *(void**)value;
            *((void**)m + 1) = *((void**)value + 1);
        }
    } else {
        Insert(pos, value);
    }
    return (char*)*self + idx * 8;
}

// @ 0x007fcff0
void RefCountRelease(void* p)
{
    if (p == 0)
        return;
    void* node;
    f_56f3e0(&node, &p);
    void* n = (node == 0) ? 0 : node;
    if (n != 0 && (*(int*)((char*)n + 4) = *(int*)((char*)n + 4) - 1, *(int*)((char*)n + 4) == 0)) {
        VCallV(p, 0xa0);
        f_50e200(n);
        VCallV(p, 4);
    }
}

// @ 0x007fd090
void** MapFindInsert(void** self, void** out, unsigned* key)
{
    unsigned* found = (unsigned*)f_5701b0(*self, self[1], key, *(unsigned char*)(self + 5));
    if (found == (unsigned*)self[1] || *key < *found) {
        *out = ((Vec8*)0)->Emplace(found, key);
        *((unsigned char*)out + 4) = 1;
    } else {
        *out = found;
        *((unsigned char*)out + 4) = 0;
    }
    return out;
}

// @ 0x007fd140
void RefCountAdd(void* p)
{
    if (p == 0)
        return;
    int c = 1;
    void* node;
    f_56f3e0(&node, &p);
    void* n = (node == 0) ? 0 : node;
    if (n == 0) {
        void* v = p;
        int cc = c;
        unsigned char res[8];
        MapFindInsert((void**)0, (void**)res, (unsigned*)&v);
        VCallV(p, 0);
    } else {
        *(int*)((char*)n + 4) = *(int*)((char*)n + 4) + 1;
        c = *(int*)((char*)n + 4);
    }
    if (c == 1)
        VCallV(p, 0x9c);
}

// @ 0x007fd200
void FlagObj::SetFlag(unsigned mask, bool on)
{
    unsigned old = mFlags;
    unsigned nv = old & ~mask;
    if (on)
        nv |= mask;
    if (old == nv)
        return;
    mFlags = nv;
    void* p;
    if (mpOwner == 0)
        p = 0;
    else
        p = VCallR(mpOwner, 0x1c);
    if (p != 0 && ((old ^ nv) & 1) != 0 && VCallB(mpOwner, 0x54)) {
        if ((mFlags & 1) == 0)
            f_7fcff0(p);
        else
            f_7fd140(p);
    }
}

// @ 0x007fd390
bool WriteSerItem(SerBuffer* p, C53* self, SerItem14* item, void* alloc)
{
    void* begin = self->M(item);
    void* dst = (void*)((void*(__thiscall*)(void*, int, int))VCallR(alloc, 0))(alloc, item->count << 2, 4);
    if (dst == 0)
        return false;
    p->base = dst;
    p->count = item->count;
    p->type = g_ser_type_7fd430;
    void* s = begin;
    void* d = dst;
    for (unsigned i = 0; i < item->count; ++i) {
        *(void**)d = *(void**)s;
        s = (char*)s + 4;
        d = (char*)d + 4;
    }
    return true;
}

// @ 0x007fd430
bool ReadSerItem(SerBuffer* p, C53* self, SerItem14* item)
{
    p->type = g_ser_type_7fd430;
    p->base = self->M(item);
    p->count = item->count;
    return true;
}

// @ 0x007fd4a0
void cSPUIBehaviorTimeFunctionRamp::SetParams(float duration, float pre, float post)
{
    v09();
    mParamPreDelayFactor = pre;
    mParamPostDelayFactor = post;
    mParamDuration = duration;
    v24();
}

// @ 0x007fd4e0
float cSPUIBehaviorTimeFunctionRamp::v22(float t)
{
    float r = 0.0f;
    if (mWorkTimeFrom <= t) {
        if (mTime <= mWorkTimeTo)
            r = (t - mWorkTimeFrom) / (mWorkTimeTo - mWorkTimeFrom);
        else
            r = 1.0f;
    }
    return r;
}

// @ 0x007fd540
bool cSPUIBehaviorTimeFunctionRamp::v24()
{
    if (mParamDuration >= 0.0f && mParamDuration < 1.52587890625e-05f)
        mParamDuration = 1.52587890625e-05f;
    return cSPUIBehaviorTimeFunction_s007f_c880__o2::v24();
}

// @ 0x007fd650
void cSPUIBehaviorTimeFunctionDampedPeriodic::SetParams(float duration, float pre, float post, float freq, float damping, int periodicType)
{
    if (periodicType != -1)
        mPeriodicType = periodicType;
    v09();
    mParamPreDelayFactor = pre;
    mParamPostDelayFactor = post;
    mParamFrequency = freq;
    mParamDamping = damping;
    mParamDuration = duration;
    v24();
    mbInitialized = true;
}

// @ 0x007fd700
bool cSPUIBehaviorTimeFunctionDampedPeriodic::v15()
{
    if (mParamDamping < 0.0f)
        return cSPUIBehaviorTimeFunction_s007f_c880__o2::v15();
    float t = mTime;
    float wf = mWorkTimeFrom;
    if (wf < t) {
        float e = expf(-(t - wf) * mParamDamping);
        if (e < 0.001f) {
            return mTime > mParamDuration;
        }
    }
    return false;
}

// @ 0x007fd790
float cSPUIBehaviorTimeFunctionDampedPeriodic::v22(float t)
{
    float f5 = 1.0f;
    float f1 = 0.0f;
    float orig = t;
    t = t - mWorkTimeFrom;
    if (t > 0.0f) {
        if (mParamDamping > 0.0f) {
            f1 = mParamDamping;
            f5 = expf(-(f1 * t));
        } else if (mParamDamping < 0.0f && orig > mWorkTimeTo) {
            t = mWorkTimeTo - mWorkTimeFrom;
        }
        float v = v25(t);
        return 1.0f - v * f5;
    }
    return f1;
}

// @ 0x007fd840
float Damped::v25(float t)
{
    float r = 1.0f;
    if (mPeriodicType == 1)
        r = cosf(mParamFrequency * g_f164b620 * t);
    if (mbCeilingMode)
        r = (r + 1.0f) * 0.5f;
    return r;
}

// @ 0x007fda80
bool SerReadA(SerItem* out, void* src)
{
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->base = p;
    out->count = 1;
    out->type = 0;
    return true;
}

// @ 0x007fe690
bool SerLoadVector2(SerBuffer* p, void* self, SerItem14* item)
{
    IObj** src = *(IObj***)((char*)self + 4);
    IObj** dst = (IObj**)(*(int*)((char*)p + 4) + *(int*)((char*)item + 0x10));
    for (unsigned i = 0; i < item->count; i++) {
        void* created = 0;
        if (*dst) VCallV(*dst, 4);
        if (*src) {
            created = VCallR1(*src, 0xc, 0x243c076);
            if (created) VCallV(created, 0);
        }
        *dst = (IObj*)created;
        ++dst;
        ++src;
    }
    return true;
}

// @ 0x007ff510
ShadeColorFull* ShadeColorFull::Ctor()
{
    ((EvApi*)this)->InterpBaseCtor();
    mbFrom = 0;
    mbUseWin = 1;
    *(void**)((char*)this + 0x00) = (void*)vt_sc_a;
    *(void**)((char*)this + 0x04) = (void*)vt_sc_b;
    mColorTo = 0xffffffff;
    mColorFrom = 0xff000000;
    return this;
}

// @ 0x007ff8c0
bool SerReadC(SerItem3* out, void* src)
{
    IObj* p = *(IObj**)((char*)src + 4);
    VCallV(p, 0x14);
    out->f4 = p;
    out->f8 = (void*)1;
    out->f0 = 0;
    return true;
}

// @ 0x007ff8f0
bool PredCheck(void* self, char* p)
{
    if (*p == 0) {
        void* r = VCallR(self, 0x14);
        r = VCallR(r, 0x48);
        if (r != self) { *p = 0; return true; }
    }
    *p = 1;
    return false;
}

// @ 0x007ff940
bool CopyThing(SerItem3* out, void* src)
{
    Obj7fb250* o = *(Obj7fb250**)((char*)src + 4);
    SerItem3 tmp;
    o->f(&tmp);
    out->f4 = tmp.f4;
    out->f8 = tmp.f8;
    out->f0 = tmp.f0;
    return true;
}

// @ 0x007ff9f0
void PredStateCtor(void* self)
{
    *(unsigned*)((char*)self + 0x18) = 1;
    *(void**)((char*)self + 0x1c) = 0;
    *(unsigned*)((char*)self + 0x20) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x24) = 0x7fffffff;
    *(unsigned*)((char*)self + 0x28) = 0;
}

// @ 0x007ffa50
int PredState::Refresh()
{
    void** slot = (void**)((char*)this + 0x1c);
    if (*slot && (VCallI(*slot, 0x10) == 0 ||
        (*(int*)((char*)this + 0x20) != 0x7fffffff && VCallI(*slot, 0x1c) != *(int*)((char*)this + 0x20)))) {
        void* p = *slot;
        if (p) { *slot = 0; VCallV(p, 4); }
    }
    if (*slot == 0) {
        if (*(int*)((char*)this + 0x28) == 3) {
            void* w = *(void**)((char*)this + 0x14);
            void* np = w ? VCallR(w, 0x58) : 0;
            if (np != *slot) {
                if (np) VCallV(np, 0);
                void* op = *slot;
                *slot = np;
                if (op) VCallV(op, 4);
            }
            if (VCallI(*slot, 0x10) == 0) {
                void* p = *slot;
                if (p) { *slot = 0; VCallV(p, 4); }
            }
        } else if (*(int*)((char*)this + 0x20) == 0x7fffffff) {
            void* w = *(void**)((char*)this + 0x14);
            if (w) {
                void* np = VCallR(w, 0x1c);
                if (np && VCallI(np, 0x10) != 0 && np != *slot) {
                    if (np) VCallV(np, 0);
                    void* op = *slot;
                    *slot = np;
                    if (op) VCallV(op, 4);
                }
            }
        }
    }
    return (int)(intptr_t)*slot;
}

// @ 0x007ffc70
uint8_t cSPUIBehaviorPredicateWinState::Evaluate()
{
  void* p = f_7ffa50();
  if (!p)
    return 0;
  void* p3 = (void*)((void* (__thiscall*)(void*))VFN(p, 0x14))(p);
  uint8_t r = 0;
  switch (mWinStateQuery) {
    case 0:
      return (uint8_t)(((uint32_t(__thiscall*)(void*))VFN(p, 0x28))(p) & 1);
    case 1:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x28))(p) >> 1) & 1);
    case 2:
      if (p3)
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 1) == p);
      break;
    case 3:
      if (p3)
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 0) == p);
      break;
    case 4:
      if (p3) {
        if (((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 0) == p)
          return 1;
        return (uint8_t)(((void* (__thiscall*)(void*, int))VFN(p3, 0x48))(p3, 1) == p);
      }
      break;
    case 5:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 2) & 1);
    case 6: {
      uint32_t v = ((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p);
      if (!(v & 1))
        return 0;
      v = ((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p);
      if ((v & 0x1e) == 0)
        return 1;
      return 0;
    }
    case 7:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 3) & 1);
    case 8:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 1) & 1);
    case 9:
      return (uint8_t)((((uint32_t(__thiscall*)(void*))VFN(p, 0x2c))(p) >> 4) & 1);
    case 10: {
      uint32_t stack20 = 0, stack1c = 0;
      ((void (__thiscall*)(void*, uint32_t*))VFN(p3, 0x3c))(p3, &stack20);
      ((void (__thiscall*)(void*, uint32_t*, uint32_t*, int))VFN(p, 0xc4))(p, &stack1c, &stack20, 0);
      uint32_t* q = (uint32_t*)((uint32_t* (__thiscall*)(void*))VFN(p, 0x38))(p);
      uint32_t s14 = q[0], s18 = q[1], s1c = q[2], s20 = q[3];
      return (uint8_t)f_809700(&s14, 0, 0);
    }
    case 0xb:
      if (mQueryHexParam != 0x7fffffff) {
        void* r2 = (void*)((void* (__thiscall*)(void*, uint32_t, int))VFN(p, 0xf0))(p, mQueryHexParam, 0);
        return (uint8_t)(r2 != 0);
      }
      break;
    case 0xc:
      if (mQueryHexParam != 0x7fffffff) {
        p = (void*)((void* (__thiscall*)(void*))VFN(p, 0x10))(p);
        if (p) {
          while (!r) {
            uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0x1c))(p);
            r = (uint8_t)(id == mQueryHexParam);
          }
        }
      }
      break;
    case 0xd: {
      uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0x30))(p);
      return (uint8_t)(mQueryHexParam == id);
    }
    case 0xe: {
      uint32_t id = ((uint32_t(__thiscall*)(void*))VFN(p, 0xa4))(p);
      return (uint8_t)(mQueryHexParam == id);
    }
    case 0xf:
      if (mpQueryWindow) {
        void* r2 = (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x44))(mpQueryWindow);
        return (uint8_t)(r2 != 0);
      }
      break;
    case 0x10:
    case 0x11:
    case 0x12: {
      void* a = mpQueryWindow ? (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x1c))(mpQueryWindow) : 0;
      void* b = mpQueryWindow ? (void*)((void* (__thiscall*)(void*))VFN(mpQueryWindow, 0x58))(mpQueryWindow) : 0;
      if (a && b) {
        if (mWinStateQuery == 0x10)
          return (uint8_t)((uint32_t(__thiscall*)(void*, void*))VFN(b, 0xf8))(b, a);
        uint32_t u = ((uint32_t(__thiscall*)(void*, void*))VFN(a, 0xf8))(a, b);
        if (mWinStateQuery == 0x11)
          return (uint8_t)u;
        if ((uint8_t)u)
          return 1;
        uint8_t c = (uint8_t)((uint32_t(__thiscall*)(void*, void*))VFN(b, 0xf8))(b, a);
        return c ? 1 : 0;
      }
      break;
    }
    case 0x13: {
      uint32_t s20 = 0;
      f_809700(p, 0, &s20);
      r = (uint8_t)s20;
      break;
    }
    default:
      break;
  }
  return r;
}
