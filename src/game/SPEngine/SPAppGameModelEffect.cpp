// src/game/SPEngine/SPAppGameModelEffect.cpp -- migrated from slice(s) s007d4a40, s007d3930 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppGameModelEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Swarm/cEffectParams.h"
#include <intrin.h>

// ---- items of slice s007d3930 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
struct IUnknown32 { virtual void AddRef(); virtual void Release(); };
struct EffComp {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9();
    virtual void SetFlag(int f);   // +0x28
};
struct EffOwner { void SetVisible(int param); };
struct VecOut {
    void* b; void* e; void* c;
    VecOut* Allocate(unsigned n, void* alloc);
};
struct cEffectParams {
    char pad[0xb4];
    IUnknown32* mUnknown[9];
    void UnknownStore(int idx, IUnknown32* p);
};
// UTFWin::Message layout used by the effect tick's messaging dispatch.
struct cEffectMessage {
    void* mpSource;         // +0x00
    uint32_t mPad4;         // +0x04
    uint32_t mEventType;    // +0x08
    uint32_t mPadc;         // +0x0c
    uint32_t mKey;          // +0x10
};
// Messaging context hung off the effect node at +0x0c.
struct cEffectMsgContext {
    char pad00[0x0c];
    uint32_t mFlags;        // +0x0c
    char pad10[0x78];
    uint32_t mMessageId;    // +0x88
};
struct cMessageServer;
cMessageServer* __cdecl GetServer();   // 0x00883860
struct cEffectNode { void Tick(void* arg); char HandleParam(int kind, float* value, void* extra); };
// ---- items of slice s007d3930 end

// ---- items of slice s007d4a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete[](void* p) throw();
void  operator delete(void* p);
struct Matrix3 { float m[9]; void Assign(const Matrix3& o); };     // 0x41cb40
void ElemCtor(void* self, const void* src);                       // 0x79a0d0
// cLabelOps::Propagate(const void*) @ 0x79a0d0: thiscall, the label object is
// passed in ecx and the single stack argument is the source blob.
struct cLabelOps { void Propagate(const void* src); };
struct TransformInit { void* Init(const void* src, void* a, char flag); };
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
template<class T> struct spvec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    uint32_t mAlloc[2];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~spvec() throw() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete[](mpBegin); }
};
struct cEffectParams_s007d_4a40 {
    cParamRec mFloatParams[25];     // +0x00
    spvec<float> mFloatStorage;     // +0x64
    cParamRec mIntParams[10];       // +0x78
    spvec<int> mIntStorage;         // +0xa0
    UnkRef mUnknownParams[9];       // +0xb4
    cEffectParams_s007d_4a40();
    ~cEffectParams_s007d_4a40();
    bool Handle(int kind, void* a, int b);
    char Handle2(int kind, void* a);
    void Tick(void* arg);
};
// ---- items of slice s007d4a40 end

// @ 0x007d4620
void cEffectParams::UnknownStore(int idx, IUnknown32* p)
{
    IUnknown32* old = mUnknown[idx];
    if (p != old) {
        if (p) p->AddRef();
        mUnknown[idx] = p;
        if (old) old->Release();
    }
}

// @ 0x007d4670
void cEffectNode::Tick(void* arg)
{
    char* s = (char*)this;
    if (s[0x14]) {
        s[0x14] = 0;
        unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
        for (unsigned i = 0; i < n; ++i) {
            void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
            ((void (__thiscall*)(void*, void*))(*(void***)c)[0xc / 4])(c, arg);
        }
        void* p = *(void**)(s + 0x38);
        if (p && *(int*)((char*)p + 0x40) < 2) {
            void* const pOwner = *(void**)p;   // +0x00: the released object
            ((void (__thiscall*)(void*, void*, int))(*(void***)pOwner)[0x16c / 4])(pOwner, p, 0);
        }
        cEffectMsgContext* const ctx = (cEffectMsgContext*)*(void**)(s + 0xc);
        if ((ctx->mFlags >> 2) & 1) {
            cMessageServer* const pServer = GetServer();
            if (pServer) {
                cEffectMessage msg;
                msg.mpSource = p;
                msg.mEventType = 0;
                msg.mKey = 0;
                ((void (__thiscall*)(void*, uint32_t, cEffectMessage*, int))(*(void***)pServer)[0x14 / 4])(
                    pServer, ctx->mMessageId, &msg, 0);
            }
        }
    }
}

// @ 0x007d4730
char cEffectNode::HandleParam(int kind, float* value, void* extra)
{
    char* s = (char*)this;
    char any = 0;
    switch (kind) {
        case 4:
            *(float*)(s + 0x2c) = *(float*)(*(int*)(s + 0xc) + 0x20) * value[0];
            any = 1; break;
        case 5:
            *(float*)(s + 0x20) = *(float*)(*(int*)(s + 0xc) + 0x14) * value[0];
            *(float*)(s + 0x24) = value[1] * *(float*)(*(int*)(s + 0xc) + 0x18);
            *(float*)(s + 0x28) = value[2] * *(float*)(*(int*)(s + 0xc) + 0x1c);
            any = 1; break;
        case 0x101:
            *(float*)(s + 0x80) = value[1];
            *(float*)(s + 0x88) = value[2];
            *(float*)(s + 0x84) = value[4];
            *(float*)(s + 0x8c) = value[5];
            any = 1; break;
        default: break;
    }
    unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < n; ++i) {
        void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(void*, int, float*, void*))((*(void***)c)[0x1c / 4]))(c, kind, value, extra);
        if (r || any) any = 1;
    }
    return any;
}

// @ 0x007d4820
void EffOwner::SetVisible(int param)
{
    *(uint8_t*)((char*)this + 0x15) = (uint8_t)param;
    _ReadWriteBarrier();
    unsigned count = (unsigned)((*(char**)((char*)this + 0xb0) - *(char**)((char*)this + 0xac)) >> 6);
    if (count != 0) {
        for (unsigned i = 0; i < count; ++i) {
            EffComp* c = *(EffComp**)(*(char**)((char*)this + 0xac) + i * 0x40 + 0x3c);
            c->SetFlag(param);
        }
    }
    void* p = *(void**)((char*)this + 0x38);
    if (p) {
        if ((char)param) *(uint32_t*)((char*)p + 4) |= 1;
        else *(uint32_t*)((char*)p + 4) &= ~1u;
    }
}

// @ 0x007d48e0
VecOut* VecOut::Allocate(unsigned n, void* alloc)
{
    void* buf = n ? operator new(n * 0x78, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    b = buf;
    e = buf;
    c = (char*)buf + n * 0x78;
    return this;
}

// @ 0x007d4980
void AssignTransforms(void* self, void* src)
{
    (void)self; (void)src;
}

// @ 0x007d4a40
void* TransformInit::Init(const void* src, void* a, char flag)
{
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

// @ 0x007d4ae0
cEffectParams_s007d_4a40::~cEffectParams_s007d_4a40()
{
}

// @ 0x007d55e0
cEffectParams_s007d_4a40::cEffectParams_s007d_4a40()
{
}
