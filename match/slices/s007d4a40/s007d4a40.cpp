// EA::Swarm::cEffectParams and its transform/parameter helpers
// (0x007d4a40..0x007d56e8).  No function in this slice is byte-exact; see
// nonmatching.txt / partial.txt.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <math.h>

void* operator new[](size_t size);
void  operator delete[](void* p) throw();
void  operator delete(void* p);

struct Obj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void AddRef();    // +0x34
    virtual void Release();   // +0x38
};
// Reference-counted object stored at cEffectParams+0x38: vtable at +0, flags at
// +4 (bit 31 selects the destroy flag), refcount at +0x40. Release decrements
// and, at <=1, dispatches the destroying destructor at vtable+0x170. An
// AutoRefCount-based handle lives at +0x64 (used by Handle2 kind 1).
struct AddRefObj {
    virtual void AddRef();          // vtable[0]
    virtual void Release();         // vtable[1]
};
struct AutoRefCountH {
    AddRefObj* mpObject;
    AutoRefCountH& operator=(AddRefObj* p) {
        if (p != mpObject) {
            AddRefObj* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct RefCounted {
    virtual void v0();          // +0x00 vtable
    uint32_t mFlags;            // +0x04
    uint32_t mPad[0x38 / 4];    // +0x08 ..
    int32_t mRefCount;          // +0x40
    uint32_t mPad2[0x20 / 4];   // +0x44 ..
    AutoRefCountH mHandle;      // +0x64
    void Release();
};
typedef void(__cdecl* VDestroy)(RefCounted*, int);
inline void RefCounted::Release() {
    int32_t c = mRefCount;
    if (c > 1) { mRefCount = c - 1; return; }
    // The destroying destructor is reached through two indirections
    // ([[vtbl]] + 0x170) and takes (this, destroy-flag) on the stack. The flag
    // is formed first so the indirect load keeps the inner table in ecx.
    char flag = (char)(mFlags >> 31);
    void** vtbl = *(void***)this;
    VDestroy dtor = *(VDestroy*)((char*)*(void**)vtbl + 0x170);
    dtor(this, (int)flag);
}
struct AutoRefCount {
    Obj* mpObject;
    AutoRefCount& operator=(Obj* p) {
        if (p != mpObject) {
            Obj* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

struct cSPTransform {   // size 0x38
    float m[0x38 / 4];
    cSPTransform& operator=(const cSPTransform& o) {
        for (int i = 0; i < 0x38 / 4; ++i) m[i] = o.m[i];
        return *this;
    }
};
struct Matrix3 { float m[9]; void Assign(const Matrix3& o); };     // 0x41cb40
struct ElemPart { void Init(void* a); };                           // 0x537f40
// cLabelOps::Propagate(const void*) @ 0x79a0d0: thiscall, the label object is
// passed in ecx and the single stack argument is the source blob.
struct cLabelOps { void Propagate(const void* src); };
typedef void(__thiscall* VCall1)(void*, int);
typedef char(__thiscall* VCall3)(Obj*, int, void*, int);
typedef char(__thiscall* VCall2)(Obj*, int, void*);
typedef int(__thiscall* VCall1i)(void*, int);

struct TransformInit { void* Init(const void* src, void* a, char flag); };
// @ 0x007d4a40
void* TransformInit::Init(const void* src, void* a, char flag) {
    void* self = this;
    char* s = (char*)self; const char* o = (const char*)src;
    s[0] = flag;
    *(uint16_t*)(s + 4) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 6) = *(const uint16_t*)(o + 2);
    *(float*)(s + 8) = *(const float*)(o + 4);
    *(float*)(s + 0xc) = *(const float*)(o + 8);
    *(float*)(s + 0x10) = *(const float*)(o + 0xc);
    *(float*)(s + 0x14) = *(const float*)(o + 0x10);
    ((Matrix3*)(s + 0x18))->Assign(*(const Matrix3*)(o + 0x14));
    *(uint16_t*)(s + 0x3e) = 0;
    *(uint16_t*)(s + 0x3c) = 0;
    *(float*)(s + 0x40) = *(const float*)0x1637118;
    *(float*)(s + 0x44) = *(const float*)0x163711c;
    *(float*)(s + 0x48) = *(const float*)0x1637120;
    *(float*)(s + 0x4c) = 1.0f;
    ((Matrix3*)(s + 0x50))->Assign(*(const Matrix3*)0x163725c);
    ((cLabelOps*)self)->Propagate(a);
    return self;
}

struct IUnk32 { virtual int AddRef(); virtual int Release(); };
struct UnkRef {
    IUnk32* mpObject;
    UnkRef() : mpObject(0) {}
    ~UnkRef() throw() { if (mpObject) mpObject->Release(); }
};
struct cParamRec {
    uint16_t mOffset, mCount;
    cParamRec() : mOffset(0), mCount(0) {}
};
// eastl::vector<T, sp_vector_allocator>: 0x14 bytes; deallocate frees only when the size header is non-zero.
template<class T> struct spvec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    uint32_t mAlloc[2];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spvec() throw() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct cEffectParams {
    cParamRec mFloatParams[25];     // +0x00
    spvec<float> mFloatStorage;     // +0x64
    cParamRec mIntParams[10];       // +0x78
    spvec<int> mIntStorage;         // +0xa0
    UnkRef mUnknownParams[9];       // +0xb4
    cEffectParams();
    ~cEffectParams();
    bool Handle(int kind, void* a, int b);
    char Handle2(int kind, void* a);
    void Tick(float param_2, float param_3, int param_4);
    // Swap the (lo,hi) parameter pair while honouring the visibility flag at
    // +0x14 and dropping the previous referenced object at +0x38. The original
    // inlines this block into Handle/Handle2, so keep it inline here too.
    void SetPairVisible(int lo, int hi) {
        char* s = (char*)this;
        char oldVisible = s[0x14];
        if (oldVisible) {
            void** vt = *(void***)s;
            ((VCall1)vt[0xc / 4])(s, 1);
        }
        RefCounted* p = *(RefCounted**)(s + 0x38);
        if (p) {
            *(void**)(s + 0x38) = 0;
            p->Release();
        }
        *(int*)(s + 0x18) = lo;
        *(int*)(s + 0x1c) = hi;
        if (oldVisible) {
            void** vt = *(void***)s;
            ((VCall1)vt[8 / 4])(s, 1);
        }
    }
};
// @ 0x007d4ae0
cEffectParams::~cEffectParams() {
}

// @ 0x007d4b60
bool cEffectParams::Handle(int kind, void* pa, int n) {
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    char oldVisible = 0;
    if (kind == 6) {
        if (*(int*)(s + 0x18) != a[0] || (n == 2 && *(int*)(s + 0x1c) != a[1])) {
            oldVisible = s[0x14];
            if (oldVisible) {
                ((VCall1)(*(void***)s)[0xc / 4])(s, 1);
            }
            RefCounted* p = *(RefCounted**)(s + 0x38);
            if (p) {
                *(void**)(s + 0x38) = 0;
                p->Release();
            }
            *(int*)(s + 0x18) = a[0];
            if (n >= 2) *(int*)(s + 0x1c) = a[1];
            if (oldVisible) {
                ((VCall1)(*(void***)s)[8 / 4])(s, 1);
            }
        }
        changed = 1;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = ((VCall3)(*(void***)c)[0x20 / 4])(c, kind, pa, n);
        if (r || changed) changed = 1;
    }
    return changed != 0;
}

// @ 0x007d4c60
char cEffectParams::Handle2(int kind, void* pa) {
    char* s = (char*)this;
    int* a = (int*)pa;
    char changed = 0;
    if (kind == 1) {
        if (*(void**)(s + 0x38)) {
            ((RefCounted*)*(void**)(s + 0x38))->mHandle.operator=((AddRefObj*)a);
            changed = 1;
        }
    } else if (kind == 3) {
        int n = a[3];
        int i;
        for (i = 0; i < n; ++i) {
            if (*(int*)((char*)a + 0x18 + i * 0x10) == (int)*(uint8_t*)(*(int*)(s + 0xc) + 0x85)) break;
        }
        if (i < n) {
            // The matched key sits at record+8, so the (lo,hi) pair lives one
            // stride on from the key slot.
            int lo = *(int*)((char*)a + (i + 1) * 0x10);
            int hi = *(int*)((char*)a + (i + 1) * 0x10 + 4);
            if ((lo & hi) != -1) {
                char oldVisible = s[0x14];
                if (oldVisible) {
                    void** vt = *(void***)s;
                    ((VCall1)vt[0xc / 4])(s, 1);
                }
                RefCounted* p = *(RefCounted**)(s + 0x38);
                if (p) {
                    *(void**)(s + 0x38) = 0;
                    p->Release();
                }
                *(int*)(s + 0x18) = lo;
                *(int*)(s + 0x1c) = hi;
                if (oldVisible) {
                    void** vt = *(void***)s;
                    ((VCall1)vt[8 / 4])(s, 1);
                }
            }
        }
        return 1;
    } else if (kind == 6 && *(int*)(*(int*)(s + 0xc) + 0x2c) == 0) {
        int r = ((VCall1i)(*(void***)a)[0xc / 4])(a, 0);
        if (r) *(int*)(s + 0xc4) = r;
    }
    unsigned cnt = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < cnt; ++i) {
        Obj* c = *(Obj**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = ((VCall2)(*(void***)c)[0x24 / 4])(c, kind, pa);
        if (r || changed) changed = 1;
    }
    return changed;
}

// --- helpers for cEffectParams::Tick (0x007d4dd0) ---------------------------
// this+0x0c is the component-set object: 0x0c holds flags, 0x30 holds a
// 0x2c-stride descriptor array, 0x88 holds the message id.
struct EffectCompSet {
    char m_00[0x0c];
    uint32_t mFlags;            // +0x0c
    char m_10[0x20];
    void* mpDescs;              // +0x30
    char m_34[0x54];
    int mId;                    // +0x88
};
struct EffectDesc {             // 0x2c-stride
    char m_00[0x08];
    float* mpValueBegin;        // +0x08
    float* mpValueEnd;          // +0x0c
    char m_10[0x10];
    float mRate;                // +0x20
    int mId;                    // +0x24
    uint8_t mMode;              // +0x28
    char m_29[3];
};
struct EffectHandler {          // 0x40-stride, object pointer at +0x3c
    char m_00[0x3c];
    void* mpObject;             // +0x3c
};
struct EffectRangeSet {         // pointed to by this+0xa8
    char m_00[0x40];
    char* mpBegin;              // +0x40 (0x1c-stride records, +0x18 tested)
    char* mpEnd;                // +0x44
};
typedef char (__thiscall* EffectHandlerTest)(void*);
typedef void (__thiscall* EffectHandlerApply)(void*, float, float, int);
typedef void (__thiscall* NotifyV70)(void*, void*, int, int, float, int);
typedef void (__thiscall* NotifyV74)(void*, void*, int, float, int);
typedef void (__thiscall* NotifyV80)(void*, void*, int, float*, float*, int);
struct MsgServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void Send(uint32_t id, void* data, int z);     // +0x14
};
// Payload handed to MsgServer::Send: only +0x00, +0x08 and +0x10 are set.
struct MsgPayload {
    void* mpObject;             // +0x00
    int   m_04;                 // +0x04 (unused)
    int   mFlag;                // +0x08
    int   m_0c;                 // +0x0c (unused)
    int   mZero;                // +0x10
};
struct cSPTransformOps { void* Assign(const void* src); };   // 0x537dc0
MsgServer* GetServer();                              // 0x883860 EA::Messaging::GetServer
double FUN_007cdb90(float* p);                       // 0x7cdb90

// @ 0x007d4dd0
void cEffectParams::Tick(float param_2, float param_3, int param_4) {
    char* s = (char*)this;

    // Phase 1: drain the 0x40-stride handler array at +0xac/+0xb0.  An empty
    // array goes straight to the target update.  If any handler reports a
    // change (its +0x10 predicate), apply it (+0x14) and fall through to the
    // target update as well; otherwise keep looking.
    {
        char* hbase = (char*)*(int*)(s + 0xac);
        char* hend = (char*)*(int*)(s + 0xb0);
        if (hbase == hend)
            goto update;
        int n = (int)(hend - hbase) >> 6;
        bool none = true;
        if (n > 0) {
            int off = 0;
            int left = n;
            do {
                void* h = *(void**)(hbase + off + 0x3c);
                if (((EffectHandlerTest)(*(void***)h)[0x10 / 4])(h)) {
                    none = false;
                    ((EffectHandlerApply)(*(void***)h)[0x14 / 4])(h, param_2, param_3, param_4);
                }
                off += 0x40;
            } while (--left);
            if (!none)
                goto update;
        }
    }

    // Phase 2: no handler changed anything.  If every 0x1c-stride record in
    // the range set at +0xa8 has a zero at +0x18, the effect is finished:
    // call vtable[3](1) and return.
    {
        int set = *(int*)(s + 0xa8);
        int diff = *(int*)(set + 0x44) - *(int*)(set + 0x40);
        int sign = diff >> 31;
        int n = diff / 0x1c + sign;
        unsigned cnt = (unsigned)(n - sign);
        char* rec = (char*)(*(int*)(set + 0x40) + 0x18);
        for (unsigned i = 0; i < cnt; ++i) {
            if (*(int*)rec != 0)
                goto update;
            rec += 0x1c;
        }
        ((VCall1)(*(void***)s)[0xc / 4])(s, 1);
        return;
    }

update:
    // Phase 3: push the template transform at +0x3c into the target object at
    // +0x38, then interpolate the target's scale/position by param_3.
    {
        char* tgt = *(char**)(s + 0x38);
        cSPTransformOps* xf = (cSPTransformOps*)(tgt + 8);
        xf->Assign(s + 0x3c);
        *(float*)(tgt + 0x4c) = *(float*)(s + 0x20);
        *(float*)(tgt + 0x50) = *(float*)(s + 0x24);
        *(float*)(tgt + 0x54) = *(float*)(s + 0x28);
        *(float*)(tgt + 0x58) = *(float*)(s + 0x2c);
        *(uint32_t*)(tgt + 4) |= 2;

        float f0 = *(float*)(s + 0x80);
        float f1 = *(float*)(s + 0x84);
        if (f0 != 1.0f || f1 != 1.0f) {
            tgt = *(char**)(s + 0x38);
            *(uint16_t*)(tgt + 8) = (uint16_t)(*(uint16_t*)(tgt + 8) | 1);
            *(uint16_t*)(tgt + 0x0a) = (uint16_t)(*(uint16_t*)(tgt + 0x0a) + 1);
            // Each step is rounded to float, matching the original's
            // subss/mulss/addss/mulss chain (not 80-bit x87 intermediates).
            float df = f1 - f0;
            float mf = df * param_3;
            float sf = mf + f0;
            *(float*)(tgt + 0x18) = sf * *(float*)(tgt + 0x18);
        }
        tgt = *(char**)(s + 0x38);
        float g0 = *(float*)(s + 0x88);
        float g1 = *(float*)(s + 0x8c);
        {
            float dg = g1 - g0;
            float mg = dg * param_3;
            float sg = mg + g0;
            *(float*)(tgt + 0x58) = sg * *(float*)(tgt + 0x58);
        }

        // Phase 4: when the 0xc-stride animation array at +0x90/+0x94 is
        // non-empty and the target carries flag bit 14, advance every entry.
        if (*(int*)(s + 0x90) != *(int*)(s + 0x94) &&
            (((*(uint32_t*)(tgt + 4)) >> 14) & 1)) {
            int count = (*(int*)(s + 0x94) - *(int*)(s + 0x90)) / 0xc;
            float dx = *(float*)(s + 0x74) - *(float*)(s + 0x40);
            float dy = *(float*)(s + 0x78) - *(float*)(s + 0x44);
            float dz = *(float*)(s + 0x7c) - *(float*)(s + 0x48);
            float dist = (float)(sqrt((double)dx * dx + (double)dy * dy + (double)dz * dz)
                                 / (double)*(float*)(s + 0x4c));
            if (count != 0) {
                void* notify = *(void**)(s + 0xc4);
                EffectDesc* descBase = (EffectDesc*)(*(EffectCompSet**)(s + 0x0c))->mpDescs;
                int animOff = 0;
                int descOff = 0;
                int left = count;
                do {
                    float* pf = (float*)(*(int*)(s + 0x90) + animOff);
                    EffectDesc* d = (EffectDesc*)((char*)descBase + descOff);
                    float rate = d->mRate;
                    float step = param_2;
                    if (0.0f < rate)
                        step = rate * dist;
                    float v0 = step * pf[1];
                    float v = v0 + pf[0];
                    pf[0] = v;
                    if (1.0f < v) {
                        uint8_t mode = d->mMode;
                        if (mode == 1) {
                            pf[0] = 1.0f;
                        } else if (mode == 2) {
                            pf[0] = 1.0f;
                            ((VCall1)(*(void***)s)[0xc / 4])(s, 0);
                        } else {
                            pf[0] = 0.0f;
                            double fv = FUN_007cdb90((float*)d);
                            pf[1] = (fv <= 0.0) ? 0.0f : 1.0f / (float)fv;
                        }
                    }
                    if (*(char*)(s + 0x16) == 0)
                        ((NotifyV70)(*(void***)notify)[0x70 / 4])
                            (notify, *(void**)(s + 0x38), d->mId, 3, 0.0f, 0);
                    float outA;
                    ((NotifyV80)(*(void***)notify)[0x80 / 4])
                        (notify, *(void**)(s + 0x38), d->mId, &outA, (float*)&param_4, 0);
                    float w = pf[0];
                    float* vals = d->mpValueBegin;
                    int idx = (int)(d->mpValueEnd - d->mpValueBegin) - 1;
                    float out;
                    if (idx == 0) {
                        out = vals[0];
                    } else {
                        float fi = (float)idx;
                        if (idx < 0)
                            fi += 4294967296.0f;
                        w = fi * w;
                        idx = (int)w;
                        float frac = w - (float)idx;
                        if (frac <= 0.0f) {
                            out = vals[idx];
                        } else {
                            float lo = vals[idx];
                            float hi = vals[idx + 1];
                            float dh = hi - lo;
                            float mh = dh * frac;
                            out = mh + lo;
                        }
                    }
                    float dt = *(float*)&param_4 - outA;
                    float pw = pf[2] * out;
                    float arg = pw * dt;
                    ((NotifyV74)(*(void***)notify)[0x74 / 4])
                        (notify, *(void**)(s + 0x38), d->mId, arg, 0);
                    animOff += 0xc;
                    descOff += 0x2c;
                } while (--left);
            }
            *(float*)(s + 0x74) = *(float*)(s + 0x40);
            *(float*)(s + 0x78) = *(float*)(s + 0x44);
            *(float*)(s + 0x7c) = *(float*)(s + 0x48);
        }

        // Phase 5: once the target is live, notify it and broadcast the
        // completion through the messaging server.
        if (*(char*)(s + 0x16) == 0) {
            char* t2 = *(char**)(s + 0x38);
            if (((*(uint32_t*)(t2 + 4)) >> 14) & 1) {
                ((VCall1)(*(void***)t2)[0x16c / 4])(t2, 1);
                EffectCompSet* comps = *(EffectCompSet**)(s + 0x0c);
                if (((comps->mFlags) >> 2) & 1) {
                    MsgServer* srv = GetServer();
                    if (srv) {
                        MsgPayload p;
                        p.mpObject = t2;
                        p.mFlag = 1;
                        p.mZero = 0;
                        srv->Send((uint32_t)comps->mId, &p, 0);
                    }
                }
                *(char*)(s + 0x16) = 1;
            }
        }
    }
}

struct TransformBig { void* Init(int a, unsigned pair, float f1, float f2, float f3, float f4,
                       Matrix3 m, Obj* obj); };
// @ 0x007d5240
void* TransformBig::Init(int a, unsigned pair, float f1, float f2, float f3, float f4,
                       Matrix3 m, Obj* obj) {
    void* self = this;
    char* s = (char*)self;
    *(uint16_t*)(s) = (uint16_t)pair;
    *(uint16_t*)(s + 2) = (uint16_t)(pair >> 16);
    *(float*)(s + 4) = f1;
    *(float*)(s + 8) = f2;
    *(float*)(s + 0xc) = f3;
    *(float*)(s + 0x10) = f4;
    ((Matrix3*)(s + 0x14))->Assign(m);
    *(int*)(s + 0x38) = a;
    *(void**)(s + 0x3c) = 0;
    ((AutoRefCount*)(s + 0x3c))->operator=(obj);
    return self;
}

struct Elem40 {
    uint16_t a, b;
    float f4, f8, fc, f10;
    Matrix3 mat;        // +0x14
    uint32_t f38;       // +0x38
    AutoRefCount ref;   // +0x3c
    Elem40(const Elem40& o);
};
// @ 0x007d5300
Elem40::Elem40(const Elem40& o) {
    a = o.a; b = o.b;
    f4 = o.f4; f8 = o.f8; fc = o.fc; f10 = o.f10;
    mat.Assign(o.mat);
    f38 = o.f38;
    // The copy ctor stores the source pointer first (no release of the
    // not-yet-constructed member) and then takes its own reference.
    Obj* p = o.ref.mpObject;
    ref.mpObject = p;
    if (p) p->AddRef();
}

// @ 0x007d53a0
void* CopyElemRange40(void* first, void* last, void* dst) {
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    while (f != l) {
        *(uint16_t*)(d) = *(const uint16_t*)(f);
        *(uint16_t*)(d + 2) = *(const uint16_t*)(f + 2);
        *(float*)(d + 4) = *(const float*)(f + 4);
        *(float*)(d + 8) = *(const float*)(f + 8);
        *(float*)(d + 0xc) = *(const float*)(f + 0xc);
        *(float*)(d + 0x10) = *(const float*)(f + 0x10);
        *(cSPTransform*)(d + 0x14) = *(const cSPTransform*)(f + 0x14);
        *(int*)(d + 0x38) = *(const int*)(f + 0x38);
        Obj* p = *(Obj**)(f + 0x3c);
        *(Obj**)(d + 0x3c) = p;
        if (p) p->AddRef();
        f += 0x40; d += 0x40;
    }
    return d;
}

// @ 0x007d5520
void* CopyBackwardsTransforms(void* first, void* last, void* dst) {
    char* f = (char*)first; char* l = (char*)last; char* d = (char*)dst;
    if (l == f) return d;
    do {
        l -= 0x40; d -= 0x40;
        *(cSPTransform*)(d) = *(const cSPTransform*)(l);
        *(int*)(d + 0x38) = *(const int*)(l + 0x38);
        AutoRefCount* r = (AutoRefCount*)(d + 0x3c);
        r->operator=(*(Obj**)(l + 0x3c));
    } while (l != f);
    return d;
}

// @ 0x007d5590
void* CopyElem38(void* self, void* a, const void* src) {
    char* s = (char*)self; const char* o = (const char*)src;
    *(uint16_t*)(s) = *(const uint16_t*)(o);
    *(uint16_t*)(s + 2) = *(const uint16_t*)(o + 2);
    *(float*)(s + 4) = *(const float*)(o + 4);
    *(float*)(s + 8) = *(const float*)(o + 8);
    *(float*)(s + 0xc) = *(const float*)(o + 0xc);
    *(float*)(s + 0x10) = *(const float*)(o + 0x10);
    ((Matrix3*)(s + 0x14))->Assign(*(const Matrix3*)(o + 0x14));
    ((ElemPart*)s)->Init(a);
    return self;
}

// @ 0x007d55e0
cEffectParams::cEffectParams() {
}
