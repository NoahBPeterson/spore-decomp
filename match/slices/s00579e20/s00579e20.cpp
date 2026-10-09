// slice s00579e20
// cAppModeEditorBase destructor + effects-mask helpers, optimized module (/O2 /arch:SSE).
#include "types.h"

extern "C" long _InterlockedExchange(long volatile*, long);
extern "C" long _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)

void operator_delete__(void* p);                  // 0x00f47380
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0 (EA)
inline void* operator new(size_t, void* p) { return p; }

struct Bits128 {
    unsigned w[4];
    Bits128() { w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; }
    struct Uninit {};
    Bits128(Uninit) {}
    Bits128(unsigned a, unsigned b, unsigned c, unsigned d) { w[0] = a; w[1] = b; w[2] = c; w[3] = d; }
};

// ---- generic vtable-slot stubs (slot 0 = deleting dtor, +4/+8/+0xc = AddRef/Release flavours)
struct V {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
};
// intrusive refcounted: vtbl[0] = deleting dtor, refcount at +4
struct RcObj {
    virtual void* Destroy(int flags);
    int rc;
};
// resource-manager tagged object: refcount at +0x40, owner (obj[0]) frees via vtbl slot 92
struct TagMgr;
struct TagObj {
    TagMgr* mgr;
    unsigned f4;
    char pad[0x40 - 8];
    int cnt;
};
struct TagMgr {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void Free(TagObj* o, unsigned flag);   // vtbl+0x170
};
struct VecStub {
    void DtorStarRecordVec();                     // 0x00ae6970 ~vector<AutoRefCount<cStarRecord>>
    void DtorSharedLibVec();                      // 0x005c7f10 ~vector<AutoRefCount<SharedLibrary>>
    void Fn5942e0();                              // 0x005942e0 (thiscall, no args)
};
struct RbTreeStub { void DoNukeSubtree(void* root); };     // 0x009a9600
void RemoveHandler(int h, int a, int b, int c, int d);    // 0x00571db0 EA::Messaging::RemoveHandler (cdecl)

// ---- app-level types
struct PropList {                                  // SP::cPropertyList
    bool GetDescription(unsigned id);              // 0x006a25a0
    char pad[0x3c];
};
extern PropList* g_sAppProperties;                 // 0x015fd918
struct PropRoot { char pad[0x3c]; struct PropSub* sub; };
struct PropSub { char pad[0x118]; int flag118; };

extern char vtbl_BehaviorMessage[];                // 0x013eb90c vtbl_UI::BehaviorMessage
extern char vtbl_13eb844[];                        // 0x013eb844
struct __declspec(novtable) BMsgBase {             // UI::BehaviorMessage base
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    long rc;                                       // +4
    unsigned data;                                 // +8
    char pad0c[0x30 - 0xc];
    unsigned id;                                   // +0x30
    unsigned pad34;
    __forceinline BMsgBase() : id(0) { *(void**)this = vtbl_BehaviorMessage; _InterlockedExchange(&rc, 0); }
};
struct __declspec(novtable) BMsg : BMsgBase {
    unsigned f38;                                  // +0x38
    unsigned pad3c;
    __forceinline BMsg() : f38(0) { *(void**)this = vtbl_13eb844; }
};
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Post(unsigned id, BMsg* m, int a, int b);     // vtbl+0x18
};
MsgServer* MessageServer();                        // 0x0067dcc0 (cdecl)
struct LayoutMgr {
    bool IsWorldVisible(unsigned id);              // 0x00810760
    void Method10660(unsigned id, int v);          // 0x00810660
};
LayoutMgr* GetLayoutManager();                     // 0x00805070 (cdecl)
struct ModelMgr { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
                  virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                  virtual unsigned GetIndex(unsigned id, int v); };  // vtbl+0x28
ModelMgr* ModelManager();                          // 0x0067dd80 (cdecl)
bool FUN_004f3d60(Bits128 a, Bits128 b);           // 0x004f3d60 (cdecl, by-value masks)

struct TorsoHolder { void* p;
    void Set(void* x);                                        // 0x00478db0
};
struct SceneObjA {
    void* GetSceneObject(int i);                              // 0x004c45d0
};
struct XformStub {
    void Assign(void* src);                                   // 0x00537dc0 cSPTransform::operator=
};

namespace SP {
class cAppModeEditorBase {
public:
    char pad[0x600];
    ~cAppModeEditorBase();                       // 0x579e20
    void RemoveTorsoFromEffectsMask();           // 0x5772b0
    void AddTorsoToEffectsMask(float x, float y, float z, int);   // 0x57a610
    void SendBehaviorMessage(BMsg*);             // 0x57a710
    __declspec(noinline) Bits128 GetMask();   // 0x57a960
    Bits128 GetDefaultMask();                    // 0x57a9e0
    int GetEditorSaveability();                  // 0x57aaa0
    void BuildPartMask(Bits128* out, void* p3, void* p4, int unused);   // 0x57ac00
};
}

using SP::cAppModeEditorBase;

extern unsigned g_mec;                           // 0x015da7ec
extern unsigned g_mf0;                           // 0x015da7f0
extern unsigned g_mf4;                           // 0x015da7f4
extern unsigned g_mf8;                           // 0x015da7f8
extern unsigned g_d40;                           // 0x015daa40
extern unsigned g_d44;                           // 0x015daa44
extern unsigned g_d48;                           // 0x015daa48
extern unsigned g_d4c;                           // 0x015daa4c
extern void* g_015e4ef0;                         // 0x015e4ef0
extern char vtbl_cAppModeEditorBase[], vtbl_13f57e4[], vtbl_13f57e0[], vtbl_13f57c8[], vtbl_13f57b8[], vtbl_13f57a8[], vtbl_13f57a4[];
extern char vtbl_cEditorResource[];             // 0x013eb938
extern char vtbl_PaintSystem[];                 // 0x013eb394
extern char vtbl_cContentValidationSummarizer[]; // 0x013ec458

#define F(T, off) (*(T**)((char*)this + (off)))
#define REL(off, slot) { V* p_ = F(V, off); if (p_) p_->s##slot(); }
#define ARRDEL(off) { void* a_ = F(void, off); if (a_ && ((int*)a_)[-1]) operator_delete__(a_); }
#define RCDEC(off) { RcObj* p_ = F(RcObj, off); if (p_) { int n_ = p_->rc - 1; p_->rc = n_; if (n_ == 0) { p_->rc = 1; p_->Destroy(1); } } }
#define RCDEC8(off) { char* b_ = F(char, off); if (b_) { RcObj* q_ = (RcObj*)(b_ + 4); int n_ = ((int*)q_)[1] - 1; ((int*)q_)[1] = n_; if (n_ == 0) { ((int*)q_)[1] = 1; q_->Destroy(1); } } }
#define TAGDEC(off) { TagObj* t_ = F(TagObj, off); if (t_) { if (t_->cnt < 2) t_->mgr->Free(t_, (t_->f4 >> 31) & 1); else t_->cnt--; } }
#define ATOMDEC(off) { char* b_ = F(char, off); if (b_) { volatile long* r_ = (volatile long*)(b_ + 8); \
    _InterlockedExchangeAdd(r_, -1); long v_ = _InterlockedExchangeAdd(r_, 0); \
    if (v_ < 1) _InterlockedExchangeAdd(r_, 1); else _InterlockedExchangeAdd(r_, 0); } }
#define STRDEL(boff, eoff) { char* b_ = F(char, boff); int d_ = (int)((char*)F(char, eoff) - b_) & ~1; if (d_ > 2 && b_) operator_delete__(b_); }
#define HANDLER(off) { int h_ = *(int*)((char*)this + (off)); if (h_) { int a_ = *(int*)((char*)this + (off) + 4); int b_ = *(int*)((char*)this + (off) + 8); \
    int c_ = *(int*)((char*)this + (off) + 12); int d_ = *(int*)((char*)this + (off) + 16); *(int*)((char*)this + (off)) = 0; RemoveHandler(h_, a_, b_, c_, d_); } }

// @ 0x00579E20
cAppModeEditorBase::~cAppModeEditorBase()
{
    *(void**)((char*)this + 0x00) = vtbl_cAppModeEditorBase;
    *(void**)((char*)this + 0x04) = vtbl_13f57e4;
    *(void**)((char*)this + 0x08) = vtbl_13f57e0;
    *(void**)((char*)this + 0x0c) = vtbl_13f57c8;
    *(void**)((char*)this + 0x10) = vtbl_13f57b8;
    *(void**)((char*)this + 0x14) = vtbl_13f57a8;
    *(void**)((char*)this + 0x1c) = vtbl_13f57a4;
    g_015e4ef0 = 0;
    HANDLER(0x5e8)
    HANDLER(0x5d4)
    HANDLER(0x5c0)
    ARRDEL(0x588)
    {
        char* e = (char*)this + 0x580;
        int i = 5;
        do {
            void* a = *(void**)(e - 0x14);
            e -= 0x14;
            if (a && ((int*)a)[-1]) operator_delete__(a);
            i--;
        } while (i >= 0);
    }
    ARRDEL(0x4d8)
    REL(0x4bc, 2)
    REL(0x4a4, 1)
    REL(0x4a0, 1)
    REL(0x49c, 1)
    REL(0x498, 1)
    REL(0x494, 1)
    ((RbTreeStub*)((char*)this + 0x454))->DoNukeSubtree(*(void**)((char*)this + 0x460));
    RCDEC(0x434)
    ARRDEL(0x41c)
    ARRDEL(0x408)
    REL(0x3c4, 1)
    REL(0x3c0, 2)
    REL(0x3bc, 1)
    REL(0x3b8, 2)
    ARRDEL(0x39c)
    REL(0x380, 2)
    ARRDEL(0x36c)
    RCDEC(0x360)
    REL(0x35c, 1)
    REL(0x358, 1)
    REL(0x354, 1)
    REL(0x350, 3)
    ARRDEL(0x334)
    ARRDEL(0x320)
    REL(0x30c, 1)
    REL(0x308, 1)
    REL(0x2a4, 1)
    REL(0x2a0, 1)
    REL(0x29c, 1)
    REL(0x294, 1)
    ATOMDEC(0x290)
    ATOMDEC(0x28c)
    STRDEL(0x1dc, 0x1e4)
    REL(0x1cc, 2)
    ((RbTreeStub*)((char*)this + 0x1b0))->DoNukeSubtree(*(void**)((char*)this + 0x1bc));
    REL(0x1ac, 1)
    ((VecStub*)((char*)this + 0x174))->DtorStarRecordVec();
    ((VecStub*)((char*)this + 0x160))->DtorSharedLibVec();
    REL(0x15c, 2)
    REL(0x158, 2)
    REL(0x154, 1)
    REL(0x150, 1)
    REL(0x14c, 2)
    REL(0x148, 1)
    TAGDEC(0xf0)
    REL(0xe4, 1)
    REL(0xdc, 2)
    REL(0xd8, 2)
    REL(0xd4, 2)
    REL(0xd0, 2)
    REL(0xcc, 2)
    STRDEL(0xb0, 0xb8)
    TAGDEC(0xac)
    TAGDEC(0xa8)
    TAGDEC(0xa4)
    TAGDEC(0xa0)
    RCDEC8(0x9c)
    RCDEC8(0x98)
    REL(0x94, 1)
    RCDEC(0x90)
    REL(0x8c, 1)
    REL(0x88, 1)
    REL(0x84, 1)
    REL(0x80, 1)
    REL(0x7c, 2)
    {
        char* p = F(char, 0x78);
        if (p) ((V*)(p + 4))->s1();
    }
    REL(0x24, 1)
    *(void**)((char*)this + 0x14) = vtbl_cContentValidationSummarizer;
    *(void**)((char*)this + 0x10) = vtbl_PaintSystem;
    *(void**)((char*)this + 0x04) = vtbl_cEditorResource;
    *(void**)((char*)this + 0x00) = vtbl_cEditorResource;
}

// @ 0x0057A610
// Re-create the torso scene object and flag the torso in the effects mask.
void cAppModeEditorBase::AddTorsoToEffectsMask(float x, float y, float z, int)
{
    if (*(int*)((char*)this + 0x150) != 0) {
        RemoveTorsoFromEffectsMask();
        TorsoHolder* h = (TorsoHolder*)((char*)this + 0xf0);
        void* r = (*(void*(__thiscall**)(void*, unsigned, unsigned, int))(**(int**)((char*)this + 0x84) + 0xc))(
            *(void**)((char*)this + 0x84), 0xfeb8102, 0xefeb80ec, 0);
        h->Set(r);
        if (h->p) {
            SceneObjA* so = *(SceneObjA**)((char*)this + 0x150);
            void* scene = so->GetSceneObject(0);
            ((XformStub*)((char*)h->p + 8))->Assign((char*)scene + 8);
            float* dst = (float*)((char*)h->p + 0x4c);   // Vector3 position passed by value
            dst[0] = x;
            dst[1] = y;
            dst[2] = z;
            ModelMgr* mm = ModelManager();
            char* obj = (char*)h->p;
            unsigned idx = mm->GetIndex(0x23008d4, 0);
            if (idx < 0x40)
                ((unsigned*)(obj + 0x44))[idx >> 5] |= 1u << (idx & 0x1f);
        }
    }
}

// ctor of the Editor cheat object (two-level MI vtables), 0x0057A6D0
extern char vtbl_RefObj[];           // 0x013ef094 ??_7RefObj@@6B@
struct __declspec(novtable) CheatBase2 {   // RefObj base at +4
    virtual void f0();
    unsigned f8;
    CheatBase2() { *(void**)this = vtbl_RefObj; f8 = 0; }
};
extern char vtbl_13f585c[], vtbl_13f5858[], g_01667bac[], g_01667bae[];
struct CheatObject2 {
    void* vt0;
    CheatBase2 b;
    char* s0c;
    char* s10;
    char* s14;
    CheatObject2();
};
// @ 0x0057A6D0
CheatObject2::CheatObject2() : b()
{
    vt0 = vtbl_13f585c;
    *(void**)&b = vtbl_13f5858;
    s0c = g_01667bac;
    s10 = g_01667bac;
    s14 = g_01667bae;
}

// @ 0x0057A710
// Post the behavior messages that close the current editor mode, then drop the held refs.
void cAppModeEditorBase::SendBehaviorMessage(BMsg* msg)
{
    char* self = (char*)this;
    if (msg != 0) {
        MessageServer()->Post(0x30c11c7, msg, 0, 0);
        if (((PropSub*)((PropRoot*)g_sAppProperties)->sub)->flag118 != 0) {
            BMsg* m = new ("Casual", 0, 0, 0, 0) BMsg();
            if (m) m->AddRef();
            char* src = *(char**)(self + 0x98);
            unsigned* dst = (unsigned*)(self + 0x1ec);
            dst[0] = *(unsigned*)(src + 0xc);
            dst[1] = *(unsigned*)(src + 0x10);
            dst[2] = *(unsigned*)(src + 0x14);
            m->data = (unsigned)dst;
            MessageServer()->Post(0x4a34c11, m, 0, 0);
            m->Release();
        } else {
            LayoutMgr* lm = GetLayoutManager();
            if (!lm->IsWorldVisible(0x614de4c))
                lm->Method10660(0x614de4c, 1);
        }
        BMsg* m2 = new ("App", 0, 0, 0, 0) BMsg();
        if (m2) m2->AddRef();
        m2->id = 0xe11332;
        m2->data = *(unsigned*)(*(char**)(self + 0x1cc) + 0x1c);
        MessageServer()->Post(m2->id, m2, 0, 0);
        char* cur = *(char**)(self + 0x1cc);
        if (cur && *(char**)(cur + 0x94)) {
            V* sub = *(V**)(cur + 0x94);
            if (sub) {
                void* r = (*(void*(__thiscall**)(void*, unsigned))(*(char**)sub + 0xc))(sub, 0x3a3aa3a);
                if (r) ((VecStub*)r)->Fn5942e0();
            }
        }
        m2->Release();
    } else {
        BMsg* m = new ("App", 0, 0, 0, 0) BMsg();
        if (m) m->AddRef();
        m->id = 0xe11332;
        m->data = 0x2ccd1d2;
        MessageServer()->Post(m->id, m, 0, 0);
        m->Release();
    }
    *(unsigned*)(self + 0x1d0) = 0;
    *(unsigned*)(self + 0x1d4) = 0;
    *(unsigned*)(self + 0x1d8) = 0;
    V* a = *(V**)(self + 0x1cc);
    if (a) { *(V**)(self + 0x1cc) = 0; a->s2(); }
    V* b = *(V**)(self + 0x4bc);
    if (b) { *(V**)(self + 0x4bc) = 0; b->s2(); }
}

// @ 0x0057A960
Bits128 cAppModeEditorBase::GetMask()
{
    Bits128 out;
    int p = *(int*)((char*)this + 0x1cc);
    if (p != 0) {
        out.w[0] = *(unsigned*)((char*)p + 0x24) & ~g_mec;
        out.w[1] = *(unsigned*)((char*)p + 0x28) & ~g_mf0;
        out.w[2] = *(unsigned*)((char*)p + 0x2c) & ~g_mf4;
        out.w[3] = *(unsigned*)((char*)p + 0x30) & ~g_mf8;
    } else {
        out.w[0] = 0;
        out.w[1] = 0;
        out.w[2] = 0;
        out.w[3] = 0;
    }
    return out;
}

// @ 0x0057A9E0
Bits128 cAppModeEditorBase::GetDefaultMask()
{
    Bits128 t(g_d40, g_d44, g_d48, g_d4c);
    Bits128 out;
    out = t;
    out.w[0] &= ~g_mec;
    out.w[1] &= ~g_mf0;
    out.w[2] &= ~g_mf4;
    out.w[3] &= ~g_mf8;
    if (*(int*)((char*)this + 0x1cc) != 0) {
        Bits128 m = GetMask();
        out.w[0] &= ~m.w[0];
        out.w[1] &= ~m.w[1];
        out.w[2] &= ~m.w[2];
        out.w[3] &= ~m.w[3];
    }
    return out;
}

// @ 0x0057AAA0
// 0 = saveable ... 4 = fails the largest mask check (graded by which mask checks fail).
int cAppModeEditorBase::GetEditorSaveability()
{
    bool enabled = !g_sAppProperties->GetDescription(0x55d7ca1);
    if (*((char*)this + 0x4b3) == 0 && *((char*)this + 0x4b4) == 0) {
        if (enabled) {
            if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetMask()))
                return 4;
        }
        return 3;
    }
    if (enabled) {
        if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetMask()))
            return 2;
        if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetDefaultMask()))
            return 1;
    }
    return 0;
}

static inline Bits128 BitsOr(const Bits128& a, const Bits128& b)
{
    return Bits128(a.w[0] | b.w[0], a.w[1] | b.w[1], a.w[2] | b.w[2], a.w[3] | b.w[3]);
}

// @ 0x0057AC00
// Build the part-visibility mask for the current mode: masks | defaults, then toggle the
// 0x400/0x40000/0x20/0x800 bits from abilities, properties and editor flags.
struct PartObj { void FUN_004bac30(Bits128* out, Bits128 mask, int v); };    // 0x004bac30
struct CritList { int FUN_004accf0(); void* FUN_004accb0(int i); };         // 0x004accf0, 0x004accb0
struct CritItem { int FUN_00435b60(unsigned key); };                         // 0x00435b60
struct Key3 { unsigned a, b, c; };
bool GetPropertyAsKey(void* props, unsigned id, Key3* out);                  // 0x006a1250 (cdecl)
bool FUN_004efb20(void* p3, unsigned k, void* m48);                          // 0x004efb20 (cdecl)
bool FUN_004ef880(void* p3, unsigned k, void* m48);                          // 0x004ef880 (cdecl)
void FUN_004edf40(void* p4, Bits128* mask);                                  // 0x004edf40 (cdecl)

void cAppModeEditorBase::BuildPartMask(Bits128* out, void* p3, void* p4, int)
{
    char* self = (char*)this;
    if (g_sAppProperties->GetDescription(0x55d7ca1)) {
        out->w[0] = 0; out->w[1] = 0; out->w[2] = 0; out->w[3] = 0;
        return;
    }
    Bits128 mk = GetMask();
    Bits128 u = BitsOr(mk, GetDefaultMask());
    Bits128 res((Bits128::Uninit()));
    ((PartObj*)p3)->FUN_004bac30(&res, u, 0);
    unsigned kind = *(unsigned*)(self + 0x2a8);
    if (kind == 0x2b978c46 || kind == 0x3d97a8e4) {
        CritList* list = *(CritList**)(self + 0x98);
        int i = 0;
        int n = list->FUN_004accf0();
        bool found = false;
        if (n > 0) {
            do {
                if (((CritItem*)list->FUN_004accb0(i))->FUN_00435b60(0xb00f0fec)) { found = true; break; }
                if (((CritItem*)list->FUN_004accb0(i))->FUN_00435b60(0x11b79301)) { found = true; break; }
                i++;
            } while (i < n);
        }
        if (found)
            res.w[0] &= 0xfffffbff;
        else
            res.w[0] |= 0x400;
    }
    void* props = *(void**)(self + 0x24);
    Key3 k1 = {0, 0, 0};
    if (props != 0 && GetPropertyAsKey(props, 0x7a926123, &k1) && !FUN_004efb20(p3, k1.a, self + 0x48))
        res.w[0] |= 0x40000;
    else
        res.w[0] &= 0xfffbffff;
    props = *(void**)(self + 0x24);
    Key3 k2 = {0, 0, 0};
    if (props != 0 && GetPropertyAsKey(props, 0xf5cbe065, &k2) && !FUN_004ef880(p3, k2.a, self + 0x48))
        res.w[0] |= 0x20;
    else
        res.w[0] &= 0xffffffdf;
    if (*(char*)(self + 0x4b1) != 0 && *(char*)(self + 0x4b2) == 0)
        res.w[0] |= 0x800;
    else
        res.w[0] &= 0xfffff7ff;
    FUN_004edf40(p4, &res);
    out->w[0] = res.w[0];
    out->w[1] = res.w[1];
    out->w[2] = res.w[2];
    out->w[3] = res.w[3];
}
// --- equivalence checker address annotations
    extern unsigned int g_d44; // 0x015daa44
    extern unsigned int g_d48; // 0x015daa48
    extern unsigned int g_d4c; // 0x015daa4c
    extern unsigned int g_mf0; // 0x015da7f0
    extern unsigned int g_mf4; // 0x015da7f4
    extern unsigned int g_mf8; // 0x015da7f8

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct XformStub {
    void Assign(void*); // 0x00537dc0
};
struct SceneObjA {
    void GetSceneObject(int); // 0x004c45d0
};
}
