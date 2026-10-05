// Slice s007b19c0 — SP::cTexturePreload / cThumbnailManager helpers and small accessor/setter
// routines in the texture/thumbnail subsystem. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067dd60();                       // 0x0067DD60 (RTT manager / factory)
void* __cdecl FUN_0067dcc0();                       // 0x0067DCC0 MessageServer()
bool  __cdecl FUN_007b1bb0(int, void*, void*);      // 0x007B1BB0

struct S3 { int a, b, c; };

struct IFac {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v7(S3 s, int z);                  // +0x1C
    virtual void* v8(int,int);                      // +0x20 (RTT create)
};
struct IMsg {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void v5(void*,int,int);                 // +0x14
};

// ---------------------------------------------------------------------------
// @ 0x007b1e70  (forwarder: m(0,a,b))
// ---------------------------------------------------------------------------
struct W1e70 {
    void helper(int, void*, void*);
    void f(void* a, void* b);
};
void W1e70::f(void* a, void* b) { helper(0, a, b); }

// ---------------------------------------------------------------------------
// @ 0x007b1da0
// ---------------------------------------------------------------------------
struct W1da0 {
    void Handler(void* r);                          // 0x007B1AF0 __thiscall
    void f(S3* p);
};
void W1da0::f(S3* p)
{
    IFac* fac = (IFac*)FUN_0067dd60();
    Handler(fac->v7(*p, 0));
}

// ---------------------------------------------------------------------------
// @ 0x007b2680  SP::cThumbnailManager::GetThumbRectID
// ---------------------------------------------------------------------------
struct RectID { int page, alloc; };
struct ThumbMgr {
    char pad0[0x14];
    RectID mThumbRectID;                            // +0x14
    void GetThumbRectID(RectID* out);
};
void ThumbMgr::GetThumbRectID(RectID* out)
{
    out->page = mThumbRectID.page;
    out->alloc = mThumbRectID.alloc;
}

// ---------------------------------------------------------------------------
// @ 0x007b27a0  (setter block A)
// ---------------------------------------------------------------------------
struct W27a0 {
    char pad[0x82];
    unsigned char m82;                              // +0x82
    char pad2[0x15];
    int m98, m9c, ma0, ma4;
    void f(int, int, int, int);
};
void W27a0::f(int a, int b, int c, int d)
{
    m98 = a; m9c = b; ma0 = c; m82 = 1; ma4 = d;
}

// ---------------------------------------------------------------------------
// @ 0x007b27e0  (setter block B)
// ---------------------------------------------------------------------------
struct W27e0 {
    char pad[0x83];
    unsigned char m83;                              // +0x83
    int m84, m88, m8c, m90, m94;
    void f(int, int, int, int, int);
};
void W27e0::f(int a, int b, int c, int d, int e)
{
    m84 = a; m88 = b; m8c = c; m83 = 1; m90 = d; m94 = e;
}

// ---------------------------------------------------------------------------
// @ 0x007b2820  (setter block C: four 2-dword values + float)
// ---------------------------------------------------------------------------
struct Pair { int x, y; };
struct W2820 {
    char pad[0xac];
    Pair a, b, c, d;                                // +0xac .. +0xc8
    float f;                                        // +0xcc
    void set(Pair*, Pair*, Pair*, Pair*, float);
};
void W2820::set(Pair* pa, Pair* pb, Pair* pc, Pair* pd, float v)
{
    a.x = pa->x; a.y = pa->y;
    b.x = pb->x; b.y = pb->y;
    c.x = pc->x; c.y = pc->y;
    d.x = pd->x; d.y = pd->y;
    f = v;
}

// ---------------------------------------------------------------------------
// @ 0x007b2890  (destructor: release member +0x10, restore base vtable)
// ---------------------------------------------------------------------------
struct IObj2 { virtual int AddRef(); virtual int Release(); };
struct B2890 { virtual int AddRef(); virtual int Release(); };
struct D2890 : B2890 {
    void* mObj;                                     // +0x10? (relative to +0x10 of full object)
    char pad[0xc];
    virtual int AddRef();
    virtual ~D2890();
};
D2890::~D2890() { if (mObj) ((IObj2*)mObj)->Release(); }

// ---------------------------------------------------------------------------
// @ 0x007b2900  (destructor: release member +0x24, restore base vtable)
// ---------------------------------------------------------------------------
struct B2900 { virtual int AddRef(); virtual int Release(); };
struct D2900 : B2900 {
    char pad[0x20];
    void* mObj;                                     // +0x24
    virtual int AddRef();
    virtual ~D2900();
};
D2900::~D2900() { if (mObj) ((IObj2*)mObj)->Release(); }

// ---------------------------------------------------------------------------
// @ 0x007b2970  (send a message then clear a flag)
// ---------------------------------------------------------------------------
struct Node2900 { char pad[0xc]; unsigned char mFlag; };   // +0xc
struct P2970 { char pad[8]; Node2900* mNode; char pad2[4]; void* mArg; };
void __stdcall FUN_007b2970(P2970* p)
{
    Node2900* node = p->mNode;
    void* arg = p->mArg;
    IMsg* s = (IMsg*)FUN_0067dcc0();
    s->v5(arg, 0, 0);
    if (node->mFlag)
        node->mFlag = 0;
}

// ---------------------------------------------------------------------------
// remaining entry points (best-effort / skeleton reconstruction)
// ---------------------------------------------------------------------------
void FUN_007b1de0(void*) {}
void FUN_007b1af0(void*) {}
void FUN_007b1e90(void*) {}
void FUN_007b19c0(void*) {}
void FUN_007b1f40(void*) {}
void FUN_007b2270(void*) {}
void FUN_007b2320(void*) {}
void FUN_007b2380(void*) {}
void FUN_007b2600(void*) {}
void FUN_007b26a0(void*) {}
