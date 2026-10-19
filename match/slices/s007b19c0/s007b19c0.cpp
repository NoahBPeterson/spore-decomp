// Slice s007b19c0 — SP::cTexturePreload / cThumbnailManager helpers and small accessor/setter
// routines in the texture/thumbnail subsystem. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <intrin.h>
#include <new>

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067dd60();                       // 0x0067DD60 (RTT manager / factory)
void* __cdecl FUN_0067dcc0();                       // 0x0067DCC0 MessageServer()

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
void FUN_007b1f40(void*) {}
void FUN_007b2270(void*) {}
void FUN_007b2320(void*) {}
void FUN_007b2380(void*) {}
void FUN_007b2600(void*) {}
void FUN_007b26a0(void*) {}

// ---------------------------------------------------------------------------
// intrusive texture-instance pointers (same shape as TexPtr in s00776730)
// ---------------------------------------------------------------------------
static __forceinline long AtomicAdd(volatile long* p, long v)
{
    return _InterlockedExchangeAdd(p, v);
}
struct cTexInst {
    void* vt; unsigned flags; volatile long refCount;
    void AddRef() { AtomicAdd(&refCount, 1); }
    void Release()
    {
        volatile long* rc = &refCount;
        AtomicAdd(rc, -1);
        long v = AtomicAdd(rc, 0);
        if (v < 1)
            AtomicAdd(rc, 1);
        else
            AtomicAdd(rc, 0);
    }
};
struct TexRef {
    cTexInst* p;
    TexRef() : p(0) {}
    TexRef(cTexInst* o) : p(o) { if (o) o->AddRef(); }
    TexRef(const TexRef& o) : p(o.p) { if (p) p->AddRef(); }
    ~TexRef() { if (p) p->Release(); }
};
struct TexRefVec {
    TexRef* mpBegin; TexRef* mpEnd; TexRef* mpCap;
    void DoInsertValue(TexRef* pos, const TexRef* v);   // 0x00425a80
    void push_back(cTexInst* raw, const TexRef& v) {
        if (mpEnd < mpCap) {
            TexRef* d = mpEnd;
            mpEnd = d + 1;
            if (d) {
                d->p = raw;
                raw->AddRef();
            }
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
    void push_back(const TexRef& v) {
        if (mpEnd < mpCap) {
            TexRef* d = mpEnd;
            mpEnd = d + 1;
            if (d) new (d) TexRef(v);
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
};

struct IPropList { virtual void v0(); virtual void Release(); };
struct PropListRef {
    IPropList* p;
    PropListRef() : p(0) {}
    ~PropListRef() { if (p) p->Release(); }
    void reset() { if (p) { IPropList* q = p; p = 0; q->Release(); } }
};
struct IPropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(unsigned grp, unsigned inst, PropListRef* out);   // +0x2c
};
IPropMgr* __cdecl PropertyManager();                 // 0x0067DE30
bool __cdecl GetPropArray(void* list, unsigned id, int* count, char** data);   // 0x006A0AE0
struct PropKey { unsigned group, x, inst; };

struct TexPreload {
    char pad0[0xc];
    TexRefVec mQueue;                               // +0x0c
    char pad1[8];
    TexRefVec mReady;                               // +0x20
    bool MoveReady();                               // 0x007B19C0
    void Push(cTexInst* t);                         // 0x007B1AF0
    void PreloadTextureList(void* list);            // 0x007B1DE0
    void PreloadTextureList(PropKey* key);          // 0x007B1E90
};

// @ 0x007b19c0
bool TexPreload::MoveReady()
{
    while (mQueue.mpBegin != mQueue.mpEnd) {
        cTexInst* raw = mQueue.mpEnd[-1].p;
        if (!(raw->flags & 1))
            return false;
        {
            TexRef t(raw);
            mReady.push_back(raw, t);
        }
        --mQueue.mpEnd;
        mQueue.mpEnd->~TexRef();
    }
    return true;
}

// @ 0x007b1af0
void TexPreload::Push(cTexInst* raw)
{
    if (raw) {
        TexRef t(raw);
        mQueue.push_back(raw, t);
    }
}

// @ 0x007b1de0
void TexPreload::PreloadTextureList(void* list)
{
    char* data = 0;
    int count = 0;
    if (GetPropArray(list, 0x85155a0c, &count, &data)) {
        int off = 0;
        for (int i = 0; i < count; i++) {
            S3* e = (S3*)(data + off);
            IFac* fac = (IFac*)FUN_0067dd60();
            Push((cTexInst*)fac->v7(*e, 0));
            off += 12;
        }
    }
}

// @ 0x007b1e90
void TexPreload::PreloadTextureList(PropKey* key)
{
    unsigned id = key->inst;
    if (id == 0x40464100) id = 0x40464200;
    PropListRef list;
    IPropMgr* mgr = PropertyManager();
    list.reset();
    if (mgr->GetPropertyList(key->group, id, &list))
        PreloadTextureList((void*)list.p);
}

// ---------------------------------------------------------------------------
// 0x007b1bb0 rectangle-packing tree node placement (returns node index or -1)
// ---------------------------------------------------------------------------
struct Span { int d[8]; Span* Init(int, int, int, int, int); };   // 0x007AE920
struct PackNode {                                   // 0x20 bytes
    int x0, y0, x1, y1;
    int unk;
    int c1, c2;
    unsigned char used; char padn[3];
    void Set(Span*);                                // 0x0076D9A0
};
struct PackTree {
    PackNode* nodes;
    int Alloc();                                    // 0x007B10A0
    int Place(int idx, int w, int h);               // 0x007B1BB0
};
// @ 0x007b1bb0
int PackTree::Place(int idx, int w, int h)
{
    PackNode* n = &nodes[idx];
    if (n->x1 - n->x0 >= w) {
        while (n->y1 - n->y0 >= h) {
            if (n->c1 >= 0) {
                int r = Place(nodes[idx].c1, w, h);
                if (r < 0)
                    r = Place(nodes[idx].c2, w, h);
                return r;
            }
            if (n->used)
                return -1;
            if (n->x1 - n->x0 == w && n->y1 - n->y0 == h) {
                nodes[idx].used = 1;
                return idx;
            }
            int a = Alloc();
            int b = Alloc();
            nodes[idx].c1 = a;
            nodes[idx].c2 = b;
            PackNode* base = nodes;
            int dw = (base[idx].x1 - base[idx].x0) - w;
            int dh = (base[idx].y1 - base[idx].y0) - h;
            Span sp;
            int ex, ey, ew, eh;
            if (dh < dw) {
                base[a].Set(sp.Init(base[idx].x0, base[idx].y0, w, base[idx].y1 - base[idx].y0, idx));
                base = nodes;
                ex = base[idx].x0 + w; ey = base[idx].y0; ew = dw; eh = base[idx].y1 - base[idx].y0;
            } else {
                base[a].Set(sp.Init(base[idx].x0, base[idx].y0, base[idx].x1 - base[idx].x0, h, idx));
                base = nodes;
                ex = base[idx].x0; ey = base[idx].y0 + h; ew = base[idx].x1 - base[idx].x0; eh = dh;
            }
            base[b].Set(sp.Init(ex, ey, ew, eh, idx));
            idx = nodes[idx].c1;
            n = &nodes[idx];
            if (n->x1 - n->x0 < w)
                return -1;
        }
    }
    return -1;
}
