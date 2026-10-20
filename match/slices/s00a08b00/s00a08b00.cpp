// Slice s00a08b00: the anim-command script registration blocks (the
// `ArgScript/...` cCommandBase factories), the rbtree insert / insert-with-hint
// helpers for the anim feedback map, the layout-manager visual-state reset, the
// animating-creature deleting destructor, the anim-manager Init walk and the
// 0x1c-byte anim-record range algorithms (copy / destroy / merge).
//
// Layouts are retail offsets read off the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;
typedef unsigned long long uint64;

// =========================================================================== free callees
void* __cdecl GetManager();                                          // 0x0067dcd0
void* __cdecl FUN_0068f4d0();                                        // 0x0068f4d0
void* __cdecl FUN_009de6e0(void* a, const void* b);                  // 0x009de6e0
void* __cdecl FUN_00a08a20(const void* key);                         // 0x00a08a20
void* __cdecl WCopy(void* dst, const void* src, uint n);             // 0x011e0744

void* __cdecl RBTreeIncrement(void* node);                           // 0x00921580
void* __cdecl RBTreeDecrement(void* node);                           // 0x009215c0
void  __cdecl RBTreeInsert(void* node, void* hint, void* anchor, int side);   // 0x009216a0

void* __cdecl EAAllocate(uint size, const char* name, int, int, const char* file, int line); // 0x00f473a0
void  __cdecl operator_delete__(void* p);                            // 0x00f47380

bool  __cdecl FUN_00a07e40(void* a, void* b);                        // 0x00a07e40

// =========================================================================== little classes
// Placement-new'd script command objects: we only need their vtable slot so the
// factory can store `*(void**)obj = <vtbl>`.
struct CmdBase { void Ctor(); };                                     // 0x0083c800
struct ChoiceBase { void Ctor(); };                                  // 0x0083cdd0
struct BaseReg { void OnReg(void* parser, int state); };             // 0x0083c780

struct StaticData {                                                  // nSPCreatureAnim::creature_static_data
    int AddRef() const;                                              // 0x009b3450
    int Release() const;                                             // 0x009c26a0
};
struct InstanceData { int Release() const; };                        // 0x009c4cc0
struct AnimCreatureBase { int Release(); };                          // 0x00a05270

struct Job {                                                         // SP::cJob-ish
    void*    f00;                                                    // +0x00
    void*    f04;                                                    // +0x04
    uint32_t pad08[4];                                               // +0x08 .. +0x17
    uint32_t f18;                                                    // +0x18
    int  AddRef();                                                   // 0x0068f950
    int  Release();                                                  // 0x00690120
    void Arm();                                                      // 0x006909b0
};

struct WideStr {                                                     // 3-pointer string
    uint16_t* begin;                                                 // +0x00
    uint16_t* end;                                                   // +0x04
    uint16_t* cap;                                                   // +0x08
    void AllocateSelf(int n);                                        // 0x00429760
    void Assign(const uint16_t* b, const uint16_t* e);               // 0x00423650
};

struct Rec {                                                         // 0x1c anim record
    float    f0;                                                     // +0x00
    float    f4;                                                     // +0x04
    uint32_t f8;                                                     // +0x08
    WideStr  s;                                                      // +0x0c
    uint32_t f18;                                                    // +0x18
    Rec();
    Rec(const Rec& o);
};

// =========================================================================== trees
struct TreeNode {                                                    // 0x20
    void*    left;                                                   // +0x00
    void*    right;                                                  // +0x04
    void*    up;                                                     // +0x08
    uint32_t color;                                                  // +0x0c
    uint32_t key0;                                                   // +0x10
    uint32_t key1;                                                   // +0x14
    void*    obj;                                                    // +0x18
};
struct Pair { void* node; uint8_t inserted; };                       // 8 bytes

struct Tree {
    uint32_t pad00;                                                  // +0x00
    void*    anchor;                                                 // +0x04
    void*    endNode;                                                // +0x08
    void*    root;                                                   // +0x0c
    uint32_t pad10;                                                  // +0x10
    uint32_t count;                                                  // +0x14

    void* insertAt(void** out, void* hint, uint* key, char flag);            // 0x00a08b00
    Pair* insertHint(Pair* out, const uint* key, void* dummy);               // 0x00a09420
    Pair* insertOrFind(Pair* out, void* hint, uint* key, int unused);        // 0x00a098d0
};

// recursive map-node destroyers (each walks left recursively, frees right-linked list)
struct MapNodeA {                                                    // +0x18 = static data
    MapNodeA* left;                                                  // +0x00
    MapNodeA* right;                                                 // +0x04
    uint32_t  pad08[4];                                              // +0x08 .. +0x17
    void*     obj;                                                   // +0x18
};
struct MapNodeB {                                                    // +0x14 = job
    MapNodeB* left;                                                  // +0x00
    MapNodeB* right;                                                 // +0x04
    uint32_t  pad08[3];                                              // +0x08 .. +0x13
    void*     job;                                                   // +0x14
};
struct MapA { void Destroy(MapNodeA* n); };                          // 0x00a09850
struct MapB { void Destroy(MapNodeB* n); };                          // 0x00a09890

// =========================================================================== layout manager
struct LayoutMgr {                                                   // 0x0166c06c
    uint32_t pad00;                                                  // +0x00
    void*    f04;                                                    // +0x04
    void*    f08;                                                    // +0x08
    void*    child;                                                  // +0x0c
    uint32_t f10;                                                    // +0x10
    uint32_t count;                                                  // +0x14
    void FreeTree(void* p);                                          // 0x009a9600
};
extern LayoutMgr* g_p166c06c;                                        // 0x0166c06c

struct RObj {                                                        // 0x0166cc08
    uint32_t pad00[26];                                              // +0x00 .. +0x67
    void**   v68;                                                    // +0x68
    void**   v6c;                                                    // +0x6c
};
extern RObj* g_p166cc08;                                             // 0x0166cc08

struct ElemA {                                                       // element of v68
    uint32_t pad00[9];                                               // +0x00 .. +0x23
    void**   v24;                                                    // +0x24
    void**   v28;                                                    // +0x28
};
struct StateObj {
    uint8_t  pad0[0x17c];                                            // +0x000
    void*    obj;                                                    // +0x17c
    uint8_t  pad180[0x2f8 - 0x180];                                  // +0x180
    int32_t  nStates;                                                // +0x2f8
    int32_t  counts[1];                                              // +0x2fc (stride 0x10, data at +0x314)
};

// =========================================================================== script registration object
struct ICmdReg {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();
    virtual void AddCommand(const void* name, void* cmd);            // +0x18
    void OnReg(void* parser, int state);                             // 0x0083c780
};

struct OnRegObj {
    ICmdReg  reg;                                                    // vtable @ +0x00
    uint32_t pad04[0xb];                                             // +0x04 .. +0x2f
    uint32_t f30;                                                    // +0x30 = state

    void OnRegisterAnimCommand(void* parser, int state);             // 0x00a08cf0
    void OnRegisterAnim(void* parser, int state);                    // 0x00a08fc0
    void OnRegisterChoice(void* parser, int state);                  // 0x00a09020
};

// command-name static pointers (0x01551xxx) and their command vtables
extern void* g_s_animID;             // 0x0155181c
extern void* g_s_animName;           // 0x01551820
extern void* g_s_duration;           // 0x01551824
extern void* g_s_durationScale;      // 0x01551828
extern void* g_s_endMode;            // 0x015517fc
extern void* g_s_idle;               // 0x01551800
extern void* g_s_blendInTime;        // 0x01551804
extern void* g_s_allowLocomotion;    // 0x015517f8
extern void* g_s_disableToolOverlay; // 0x01551808
extern void* g_s_matchVariantForTool;// 0x0155180c
extern void* g_s_priorityOverride;   // 0x01551814
extern void* g_s_choice;             // 0x015517ec
extern void* g_s_randomizeChoice;    // 0x015517f4
extern void* g_s_animation;          // 0x015517f0

// =========================================================================== animating creature
struct cAnimatingCreature {
    virtual void ac0();                                              // vtable @ +0x00
    uint8_t  pad04[0x15c - 0x04];                                    // +0x004 .. +0x15b
    void*    f15c;                                                   // +0x15c
    uint8_t  pad160[0x17c - 0x160];                                  // +0x160 .. +0x17b
    void*    f17c;                                                   // +0x17c
    void* scalar_deleting_destructor(uint8_t param_2);               // 0x00a08cb0
};

// =========================================================================== manager Init walker
struct ResMan {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual bool v14(void* out, const void* key, int zero);          // +0x38
};
struct HostObj {                                                     // the Init argument
    virtual void h0();  virtual void h1();  virtual void h2();  virtual void h3();
    virtual void h4();  virtual void h5();  virtual void h6();  virtual void h7();
    virtual void h8();  virtual void h9();  virtual void h10(); virtual void h11();
    virtual void h12();
    virtual bool h13(void* elem, void** out, int a, int b, int c, int d);   // +0x34
};
struct CRes {
    virtual void r0();  virtual void r1();  virtual void r2();  virtual void r3();
    virtual void r4();  virtual void r5();
    virtual void* r6();                                              // +0x18
    virtual void r7();  virtual void r8();
    virtual void r9();                                               // +0x24
};
struct JobMgr {
    virtual void j0();  virtual void j1();  virtual void j2();  virtual void j3();
    virtual bool j4(void** out);                                     // +0x10
};
struct VTwo { virtual void v0(); virtual void v1(); };               // obj->v1()

// =========================================================================== 0x00a08b00
// @ 0x00a08b00
void* Tree::insertAt(void** out, void* hint, uint* key, char flag)
{
    int side;
    if (flag == 0
        && hint != (void*)((char*)this + 4)
        && key[1] >= *(uint*)((char*)hint + 0x14)
        && (key[1] != *(uint*)((char*)hint + 0x14) || key[0] >= *(uint*)((char*)hint + 0x10)))
        side = 1;
    else
        side = 0;

    TreeNode* n = (TreeNode*)EAAllocate(
        0x20, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    uint32_t* dst = (uint32_t*)((char*)n + 0x10);
    if (dst != 0) {
        dst[0] = key[0];
        dst[1] = key[1];
        void* o = *(void**)((char*)key + 8);
        *(void**)((char*)dst + 8) = o;
        if (o != 0)
            ((StaticData*)o)->AddRef();
    }
    RBTreeInsert(n, hint, (char*)this + 4, side);
    ++*(uint32_t*)((char*)this + 0x14);
    *out = n;
    // Retail leaves the `out` slot pointer in eax at the ret (dead for callers, but the
    // LTCG contract compares it), so hand it back here.
    return out;
}

// =========================================================================== 0x00a08ba0
// @ 0x00a08ba0
void __cdecl FUN_00a08ba0(void)
{
    if (g_p166cc08 == 0)
        return;
    LayoutMgr* mgr = g_p166c06c;
    if (mgr == 0)
        return;

    mgr->FreeTree(mgr->child);
    mgr->f08 = (char*)mgr + 4;
    mgr->child = 0;
    mgr->f10 = 0;
    mgr->count = 0;
    mgr->f04 = (char*)mgr + 4;

    uint nOuter = (uint)((g_p166cc08->v6c - g_p166cc08->v68) >> 2);
    for (uint i = 0; i < nOuter; ++i) {
        ElemA* e = (ElemA*)g_p166cc08->v68[i];
        uint nMid = (uint)((e->v28 - e->v24) >> 2);
        for (uint j = 0; j < nMid; ++j) {
            void* o = e->v24[j];
            if (o != 0) {
                StateObj* q = *(StateObj**)((char*)o + 0x17c);
                if (q != 0) {
                    int n = q->nStates;
                    if (n > 0) {
                        int* cnt = q->counts;
                        uint8_t* vec = (uint8_t*)q + 0x314;
                        for (int a = 0; a < n; ++a) {
                            int m = *cnt;
                            if (m > 0) {
                                uint32_t* v = (uint32_t*)vec;
                                for (int b = 0; b < m; ++b)
                                    v[b] = 0;
                            }
                            *cnt = 0;
                            ++cnt;
                            vec += 0x10;
                        }
                    }
                    q->nStates = 0;
                }
            }
        }
    }
}

// =========================================================================== 0x00a08cb0
// @ 0x00a08cb0
void* cAnimatingCreature::scalar_deleting_destructor(uint8_t param_2)
{
    *(void**)this = (void*)0x1448b48;
    _ReadWriteBarrier();
    if (f17c != 0)
        ((InstanceData*)f17c)->Release();
    if (f15c != 0)
        ((AnimCreatureBase*)f15c)->Release();
    if ((param_2 & 1) != 0)
        operator_delete__(this);
    return this;
}

// =========================================================================== 0x00a08cf0
// @ 0x00a08cf0
void OnRegObj::OnRegisterAnimCommand(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x10, "ArgScript/OldAnimID", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c08;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animID, c);

    c = EAAllocate(0x10, "ArgScript/OldAnimName", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c20;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animName, c);

    c = EAAllocate(0x10, "ArgScript/OldDuration", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c38;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_duration, c);

    c = EAAllocate(0x10, "ArgScript/OldDurationScale", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c50;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_durationScale, c);

    c = EAAllocate(0x10, "ArgScript/EndMode", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c68;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_endMode, c);

    c = EAAllocate(0x10, "ArgScript/Idle", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c80;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_idle, c);

    c = EAAllocate(0x10, "ArgScript/BlendInTime", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c98;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_blendInTime, c);

    c = EAAllocate(0x10, "ArgScript/AllowLocomotion", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cb0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_allowLocomotion, c);

    c = EAAllocate(0x10, "ArgScript/DisableToolOverlayMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cc8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_disableToolOverlay, c);

    c = EAAllocate(0x10, "ArgScript/MatchVariantForToolMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448ce0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_matchVariantForTool, c);

    c = EAAllocate(0x10, "ArgScript/PriorityOverride", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cf8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_priorityOverride, c);
}

// =========================================================================== 0x00a08fc0
// @ 0x00a08fc0
void OnRegObj::OnRegisterAnim(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x10, "ArgScript/Animation", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448d58;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_animation, c);
}

// =========================================================================== 0x00a09020
// @ 0x00a09020
void OnRegObj::OnRegisterChoice(void* parser, int state)
{
    f30 = state;
    reg.OnReg(parser, state);

    void* c = EAAllocate(0x34, "ArgScript/Choice", 0, 0, 0, 0);
    if (c != 0) {
        ((ChoiceBase*)c)->Ctor();
        *(void**)c = (void*)0x1448d34;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_choice, c);

    c = EAAllocate(0x10, "ArgScript/RandomizeChoicePerLoop", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448d70;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_randomizeChoice, c);

    c = EAAllocate(0x10, "ArgScript/EndMode", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c68;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_endMode, c);

    c = EAAllocate(0x10, "ArgScript/Idle", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c80;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_idle, c);

    c = EAAllocate(0x10, "ArgScript/BlendInTime", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448c98;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_blendInTime, c);

    c = EAAllocate(0x10, "ArgScript/AllowLocomotion", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cb0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_allowLocomotion, c);

    c = EAAllocate(0x10, "ArgScript/DisableToolOverlayMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cc8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_disableToolOverlay, c);

    c = EAAllocate(0x10, "ArgScript/MatchVariantForToolMask", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448ce0;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_matchVariantForTool, c);

    c = EAAllocate(0x10, "ArgScript/PriorityOverride", 0, 0, 0, 0);
    if (c != 0) {
        ((CmdBase*)c)->Ctor();
        *(void**)c = (void*)0x1448cf8;
    } else {
        c = 0;
    }
    reg.AddCommand(g_s_priorityOverride, c);
}

// =========================================================================== 0x00a09280
// @ 0x00a09280
bool __stdcall FUN_00a09280(void* mgr)
{
    bool     ok = true;
    void**   vecBegin = 0;
    void**   vecEnd = 0;
    void**   vecCap = 0;
    struct { const void* p; uint32_t h; } key;
    key.p = (const void*)0x13eb428;
    key.h = 0x25df0112;

    ResMan* rm = (ResMan*)GetManager();
    if (!rm->v14(&vecBegin, &key, 0))
        goto cleanup;
    if (vecBegin == vecEnd)
        goto cleanup;

    {
        HostObj* host = (HostObj*)mgr;
        const void* type = (const void*)0x1448b30;
        for (void** it = vecBegin; it != vecEnd; it += 3) {
            void* out = 0;
            if (host->h13(*it, &out, 2, 6, 1, 0)) {
                CRes* r = (CRes*)out;
                void* p = r->r6();
                struct { const void* t; void* p; } sp;
                sp.t = type;
                sp.p = p;
                if (p != 0)
                    ((CRes*)p)->r1();
                void* q = FUN_00a08a20(*it);
                if (q != 0)
                    FUN_009de6e0(q, &sp);
                sp.t = type;
                if (p != 0)
                    ((CRes*)p)->r2();
                out = sp.p;
            } else {
                ok = false;
            }
            if (out != 0) {
                ((CRes*)out)->r9();
                ((CRes*)out)->r2();
            }
        }
    }

cleanup:
    if (vecBegin != 0 && *(void**)((char*)vecBegin - 4) != 0)
        operator_delete__(vecBegin);
    return ok;
}

// =========================================================================== 0x00a093b0
// @ 0x00a093b0
Rec::Rec(const Rec& o)
{
    f0 = o.f0;
    f4 = o.f4;
    f8 = o.f8;
    s.begin = 0;
    s.end = 0;
    s.cap = 0;
    uint16_t* src = o.s.begin;
    int n = (int)(o.s.end - src);
    s.AllocateSelf(n + 1);
    uint16_t* dst = s.begin;
    WCopy(dst, src, (uint)n * 2);
    s.end = (uint16_t*)((char*)dst + n * 2);
    *s.end = 0;
}

// =========================================================================== 0x00a09420
// @ 0x00a09420
Pair* Tree::insertHint(Pair* out, const uint* key, void* dummy)
{
    char  side = 1;
    void* pos = (char*)this + 4;
    void* cur = *(void**)((char*)this + 0xc);
    if (cur != 0) {
        uint k0 = key[0];
        uint k1 = key[1];
        do {
            uint n1 = *(uint*)((char*)cur + 0x14);
            uint n0 = *(uint*)((char*)cur + 0x10);
            if (k1 > n1)
                side = 0;
            else if (k1 < n1)
                side = 1;
            else
                side = (k0 < n0);
            pos = cur;
            cur = side ? *(void**)((char*)cur + 4) : *(void**)cur;
        } while (cur != 0);
    }

    void* probe = pos;                       // the node the insert is parented to
    void* prev  = pos;                       // the neighbour the lower-bound test uses
    if (side) {
        if (pos == *(void**)((char*)this + 8))
            goto doInsert;
        prev = RBTreeDecrement(pos);
    }
    if (*(uint*)((char*)prev + 0x14) > key[1]
        || (*(uint*)((char*)prev + 0x14) == key[1]
            && *(uint*)((char*)prev + 0x10) >= key[0])) {
        out->node = prev;
        out->inserted = 0;
        return out;
    }

doInsert:
    {
        void* n;
        insertAt(&n, probe, (uint*)key, 0);
        out->node = n;
        out->inserted = 1;
    }
    return out;
}

// =========================================================================== 0x00a094d0
// @ 0x00a094d0
void* __cdecl FUN_00a094d0(void** first1, void** last1, void** first2, void** last2, void** out)
{
    for (;;) {
        if (first1 == last1 || first2 == last2) {
            uint n1 = (uint)(last1 - first1);
            out = (void**)WCopy(out, first1, n1 * 4);
            out += n1;
            uint n2 = (uint)(last2 - first2);
            out = (void**)WCopy(out, first2, n2 * 4);
            out += n2;
            return out;
        }
        void* b = *first2;
        void* a = *first1;
        if (b == 0) goto takeA;
        if (a == 0) goto takeB;
        if (*(uint8_t*)((char*)b + 0x5c) == 0) goto takeA;
        if (*(uint8_t*)((char*)a + 0x5c) == 0) goto takeB;
        {
            float fb = *(float*)((char*)b + 0x60);
            float fa = *(float*)((char*)a + 0x60);
            if (fb > fa) goto takeB;
        }
    takeA:
        *out = a; ++first1;
    next:
        ++out;
        continue;
    takeB:
        *out = b; ++first2;
        goto next;
    }
}

// =========================================================================== 0x00a095a0
// @ 0x00a095a0
void __cdecl FUN_00a095a0(Rec* dst, Rec* last, const Rec* value)
{
    while (dst != last) {
        dst->f0 = value->f0;
        dst->f4 = value->f4;
        dst->f8 = value->f8;
        if (&dst->s != &value->s)
            dst->s.Assign(value->s.begin, value->s.end);
        ++dst;
    }
}

// =========================================================================== 0x00a09630
// @ 0x00a09630
Rec* __cdecl FUN_00a09630(Rec* first, Rec* last, Rec* dst)
{
    if (first != last) {
        do {
            uint16_t* p = first->s.begin;
            int len = (int)((char*)first->s.cap - (char*)p) & 0xfffffffe;
            if (len > 2 && p != 0)
                operator_delete__(p);
            ++first;
            ++dst;
        } while (first != last);
        return dst;
    }
    return dst;
}

// =========================================================================== 0x00a09680
// @ 0x00a09680
Rec* __cdecl FUN_00a09680(Rec* first, Rec* last, Rec* dst)
{
    if (first != last) {
        Rec* d = dst;
        do {
            d->f0 = first->f0;
            d->f4 = first->f4;
            d->f8 = first->f8;
            if (&first->s != &d->s)
                d->s.Assign(first->s.begin, first->s.end);
            ++first;
            ++d;
        } while (first != last);
        return d;
    }
    return dst;
}

// =========================================================================== 0x00a096e0
// @ 0x00a096e0
Rec* __cdecl FUN_00a096e0(Rec* first, Rec* last, Rec* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            dst->f0 = last->f0;
            dst->f4 = last->f4;
            dst->f8 = last->f8;
            if (&last->s != &dst->s)
                dst->s.Assign(last->s.begin, last->s.end);
        } while (last != first);
        return dst;
    }
    return dst;
}

// =========================================================================== 0x00a09740
// @ 0x00a09740
bool __cdecl FUN_00a09740(void* obj, Job** out)
{
    ((VTwo*)obj)->v1();

    Job* job = 0;
    JobMgr* mgr = (JobMgr*)FUN_0068f4d0();
    if (job != 0) {
        job = 0;
        job->Release();
    }
    if (!mgr->j4((void**)&job)) {
        if (job != 0)
            job->Release();
        return false;
    }

    job->f00 = (void*)&FUN_00a07e40;
    job->f04 = obj;
    job->f18 = 4;
    job->Arm();

    Job* held = job;
    if (held != 0)
        held->AddRef();

    Job* old = *out;
    if (held != old) {
        if (held != 0)
            held->AddRef();
        *out = held;
        if (old != 0)
            old->Release();
    }
    if (held != 0)
        held->Release();
    if (job != 0)
        job->Release();
    return true;
}

// =========================================================================== 0x00a09810
// @ 0x00a09810
void __stdcall FUN_00a09810(Rec* first, Rec* last)
{
    for (; first < last; ++first) {
        uint16_t* p = first->s.begin;
        int len = (int)((char*)first->s.cap - (char*)p) & 0xfffffffe;
        if (len > 2 && p != 0)
            operator_delete__(p);
    }
}

// =========================================================================== 0x00a09850
// @ 0x00a09850
void MapA::Destroy(MapNodeA* n)
{
    while (n != 0) {
        Destroy(n->left);
        MapNodeA* next = n->right;
        if (n->obj != 0)
            ((StaticData*)n->obj)->Release();
        operator_delete__(n);
        n = next;
    }
}

// =========================================================================== 0x00a09890
// @ 0x00a09890
void MapB::Destroy(MapNodeB* n)
{
    while (n != 0) {
        Destroy(n->left);
        MapNodeB* next = n->right;
        if (n->job != 0)
            ((Job*)n->job)->Release();
        operator_delete__(n);
        n = next;
    }
}

// =========================================================================== 0x00a098d0
// @ 0x00a098d0
Pair* Tree::insertOrFind(Pair* out, void* hint, uint* key, int unused)
{
    void* root = *(void**)((char*)this + 4);
    if (hint == root || hint == (void*)((char*)this + 4)) {
        if (*(uint*)((char*)this + 0x14) != 0
            && *(uint*)((char*)root + 0x14) <= key[1]
            && (*(uint*)((char*)root + 0x14) < key[1]
                || *(uint*)((char*)root + 0x10) < key[0])) {
            insertAt((void**)out, root, key, 0);
            return out;
        }
        Pair local;
        insertHint(&local, key, (void*)((uint)key & 0xffffff00u));
        out->node = local.node;
        return out;
    }

    void* inc = RBTreeIncrement(hint);
    uint k0 = key[0];
    uint k1 = key[1];
    if (*(uint*)((char*)hint + 0x14) <= k1
        && (*(uint*)((char*)hint + 0x14) < k1 || *(uint*)((char*)hint + 0x10) < k0)
        && k1 <= *(uint*)((char*)inc + 0x14)
        && (k1 < *(uint*)((char*)inc + 0x14) || k0 < *(uint*)((char*)inc + 0x10))) {
        int side;
        void* h;
        if (*(int*)hint != 0) {
            h = inc;
            side = 1;
        } else {
            h = hint;
            side = 0;
        }
        insertAt((void**)out, h, key, side);
        return out;
    }

    Pair local;
    insertHint(&local, key, (void*)((uint)key & 0xffffff00u));
    out->node = local.node;
    return out;
}
