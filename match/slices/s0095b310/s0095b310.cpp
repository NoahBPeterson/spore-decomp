// Slice s0095b310 -- EA::UTFWin::WindowMgr display-list update, RenderContext 2D batching, rect clipping.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast  (no /EH: member dtors are not EH-registered)
#include "../s00958a70/s00958a70.h"

typedef float f32;
typedef uint16_t u16;

// ---------------------------------------------------------------- stubs
struct RectF {
    float x0, y0, x1, y1;
    void __thiscall Intersect(const RectF& a, const RectF& b);     // 0x634b60
};
struct Xform {
    float m[17];                                                    // 0x44 bytes (Matrix43)
    void __thiscall Init(const float* trans, const float* scale);   // 0x95e810
    void __thiscall Multiply(const Xform* o);                       // 0x95f860
};
struct RenderCtx;
struct IRenderable {
    virtual void AddRef();                                          // +0
    virtual void Release();                                         // +4
    virtual void r2();
    virtual void Render(RenderCtx* c);                              // +0xc
};
struct IRenderMode {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void Begin();                                           // +0x10
    virtual void Render(IRenderable* r, RenderCtx* c);              // +0x14
    virtual void End();                                             // +0x18
    virtual bool vFlag();                                           // +0x1c
};
struct IRenderer {
    virtual void AddRef(); virtual void Release(); virtual void r2();
    virtual bool NeedsPrepass();                                    // +0xc
    virtual void* CreateData(IWin* w);                              // +0x10
    virtual void  FreeData(void* d);                                // +0x14
    virtual void  RenderBatch(void* data, RenderCtx* c, Node** begin, int n, int flag);   // +0x18
    virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16();
    virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
    virtual void DrawRect(const RectF* dst, const RectF* clip, const RectF* uv);   // +0x58
};
struct Base2D {                                                  // size 0x24
    Base2D(void* a);                                             // 0x9520a0
    virtual ~Base2D();                                           // 0x951ba0
    u32 d[8];
};
struct Builder {
    Builder();                                                   // 0x952aa0
    ~Builder();                                                  // 0x952f80
    u32 d[40];
};
struct Batch2D : Base2D {
    Builder b;                                                       // +0x24
    Batch2D(void* a) : Base2D(a) {}
    IRenderable* __thiscall Take();                                  // 0x9557c0
};
struct RenderData {                                                  // 0x5c
    Xform xf;                                                        // +0
    float r0, r1, r2, r3;                                            // +0x44 clip rect
    u32 shade;                                                       // +0x54
    void* rdata;                                                     // +0x58
};
struct DispEntry {                                                   // 0x100
    Node link;                                                       // +0
    DispEntry* prevEntry;                                            // +8
    u8 bReplace, bActive, bSecond, pad0f;                            // +0xc..
    u16 depth, lowest;                                               // +0x10 / +0x12
    IRenderer* renderer;                                             // +0x14
    Chunk chunks;                                                    // +0x18 (0x30)
    RenderData data[2];                                              // +0x48
};
struct EVec {                                                        // eastl::fixed_vector<DispEntry*,64> header
    DispEntry** begin; DispEntry** end; DispEntry** cap; u32 pad; DispEntry** buf;
    void __thiscall Overflow(DispEntry** pos, DispEntry** val);      // 0x899480
};
struct RenderCtx {
    Xform* xf;          // 0
    u32    shade;       // 4
    RectF  clip;        // 8
    RectF  vp;          // 0x18
    float  trans[3];    // 0x28
    float  scale[3];    // 0x34
    IRenderMode* mode;  // 0x40
    IRenderMode* defMode;   // 0x44
    Node*  list;        // 0x48
    Xform* mat;         // 0x4c
    u32    colorMod;    // 0x50
    Chunk* chunks;      // 0x54
    Batch2D batch;      // 0x58

    // @ 0x95bb80
    RenderCtx(void* a) : mode(0), defMode(0), mat(0), colorMod(0xffffffff), chunks(0), batch(a) {}
    // @ 0x95bb20
    void __thiscall End2D();
    // @ 0x95bbc0
    void __thiscall AddRenderable(IRenderable* r);
    // @ 0x95bc10
    Batch2D* __thiscall Begin2D(IRenderMode* m);
    // @ 0x95bc40
    Node** __thiscall RenderBatch(Node** pIt, DispEntry* head, int flag);
    // @ 0x95bd60
    void __thiscall RenderList(Node* lst, const RectF* r);
};
extern IRenderMode* __cdecl GetDefaultMode();                        // 0x951d50
extern Chunk* __cdecl AllocRenderableListChunk();                    // 0x956ed0
extern DispEntry* __cdecl AllocDisplayListEntry();                   // 0x956ff0
extern u32 __cdecl ModulateARGB32(u32 a, u32 b);                     // 0x95f8c0
extern u32 g_tbl_1440748[29];
extern const float g_1471064, g_1485720, g_1470f1c, g_13eb1bc_f;
extern float g_sign_mask_13eb8b0;
extern void __cdecl MergePending(Node* lD, Node* L1, Node* L2);      // 0x958570
struct MutexOps {
    void __thiscall Lock(const void* name);                      // 0x9221b0
    void __thiscall Unlock();                                    // 0x922270
};

#define WB(w, o)   (*(u8*)((u8*)(w) + (o)))
#define WD(w, o)   (*(u32*)((u8*)(w) + (o)))

// ---------------------------------------------------------------- tiny intrusive-list helpers
static inline bool Empty(Node* a) { return a->next == a; }
static inline void PopFront(Node* a) {
    Node* n = a->next;
    n->next->prev = a;
    a->next = n->next;
    if (n != a) { n->prev = 0; n->next = 0; }
}
static inline void PopBack(Node* a) {
    Node* n = a->prev;
    n->prev->next = a;
    a->prev = n->prev;
    if (n != a) { n->prev = 0; n->next = 0; }
}
static inline void PushBack(Node* a, Node* n) {
    n->prev = a->prev;
    n->next = a;
    a->prev = n;
    n->prev->next = n;
}
// move all of src to the end of dst (src must be non-empty)
static inline void AppendAll(Node* dst, Node* src) {
    Node* first = src->next;
    Node* last = src->prev;
    Node* tail = dst->prev;
    tail->next = first;
    first->prev = tail;
    last->next = dst;
    dst->prev = last;
    src->prev = src;
    src->next = src;
}
static inline void SwapLists(Node* a, Node* b) {
    Node* an = a->next; Node* ap = a->prev;
    a->next = b->next; a->prev = b->prev;
    b->next = an; b->prev = ap;
    if (a->next == b) { a->prev = a; a->next = a; }
    else { a->prev->next = a; a->next->prev = a; }
    if (b->next == a) { b->prev = b; b->next = b; }
    else { b->prev->next = b; b->next->prev = b; }
}
static inline void ClearLinks(Node* a) {
    for (Node* n = a->next; n != a; ) { Node* nx = n->next; n->prev = 0; n->next = 0; n = nx; }
}

// @ 0x95b310
void __thiscall WM::UpdateVisuals()
{
    Node L1; L1.prev = &L1; L1.next = &L1;
    Node L2;
    if (mainWin)
        UpdateRenderState(mainWin, 0, 0);
    bool b27 = false;
    bool b13 = false;
    if (f25 == 0) {
        if (lA.n.prev != &lA.n) {
            b13 = true;
            do {
                u8* nb = (u8*)lA.n.next;
                Win* w = (Win*)((nb - 8) ? nb - 0x10 : 0);
                PopFront(&lA.n);
                WB(w, 0x30) &= 0xef;
                WD(w, 0x14) = 0;
                DispEntry* e = AllocDisplayListEntry();
                RenderCtx ctx(this);
                ctx.chunks = &e->chunks;
                RenderWindow(w, &ctx);
                DispEntry* old = (DispEntry*)WD(w, 0x78);
                e->prevEntry = old;
                e->bReplace = 1;
                e->bActive = 0;
                e->depth = ((DispEntry*)WD(w, 0x78))->depth;
                e->lowest = ((DispEntry*)WD(w, 0x78))->lowest;
                e->renderer = (IRenderer*)WD(w, 0x1e8);
                if (e->renderer) {
                    e->renderer->AddRef();
                    e->data[0].rdata = e->renderer->CreateData((IWin*)w);
                    e->data[1].rdata = 0;
                }
                e->bSecond = 0;
                e->data[0].xf = *(Xform*)((u8*)w + 0x14c);
                ComputeClip(&e->data[0].r0, w);
                e->data[0].shade = WD(w, 0x1d4);
                PushBack(&L1, &e->link);
                if (e->chunks.count == 0 && ((DispEntry*)WD(w, 0x78))->renderer == 0)
                    WD(w, 0x78) = 0;
                else
                    WD(w, 0x78) = (u32)e;
            } while (lA.n.prev != &lA.n);
            b27 = true;
        }
    } else {
        f25 = 0;
        if (mainWin) {
            u32 tmp[2];
            tmp[0] = 0; tmp[1] = 0;
            BuildDisplayList(&L1, mainWin, tmp);
        }
        ClearLinks(&lA.n);
        lA.n.prev = &lA.n;
        lA.n.next = &lA.n;
        b27 = true;
    }
    L2.prev = &L2; L2.next = &L2;
    ((MutexOps*)&mxA)->Lock((const void*)0x1440688);
    if (lC.n.prev != &lC.n) {
        do {
            u8* nb = (u8*)lC.n.prev;
            Win* w = (Win*)((nb - 0x18) ? nb - 0x20 : 0);
            PopBack(&lC.n);
            WD(w, 0x24) = 0;
            DispEntry* e = (DispEntry*)WD(w, 0x78);
            if (e) {
                RenderData* d = &e->data[e->bSecond == 0];
                if (e->renderer) {
                    if (d->rdata)
                        e->renderer->FreeData(d->rdata);
                    d->rdata = e->renderer->CreateData((IWin*)w);
                }
                d->xf = *(Xform*)((u8*)w + 0x14c);
                ComputeClip(&d->r0, w);
                d->shade = WD(w, 0x1d4);
                e->bSecond = (e->bSecond == 0);
            }
        } while (lC.n.prev != &lC.n);
    }
    SwapLists(&lE.n, &L2);
    if (b27) {
        if (f58 != 0) {
            if (f59 == 0 && b13) {
                MergePending(&lD.n, &L1, &L2);
                b13 = false;
                goto L7cd;
            }
            for (Node* it = L1.next; it != &L1; it = it->next) {
                DispEntry* e = (DispEntry*)it;
                DispEntry* p = e->prevEntry;
                if (p && !p->bActive) {
                    e->prevEntry = p->prevEntry;
                    if (p->bReplace && !e->bReplace) {
                        e->bReplace = 1;
                        e->chunks.Swap(&p->chunks);
                    }
                    p->link.prev->next = p->link.next;
                    p->link.next->prev = p->link.prev;
                    p->link.next = 0;
                    p->link.prev = 0;
                    PushBack(&L2, &p->link);
                }
            }
            if (b13) {
                if (lD.n.next != &lD.n)
                    AppendAll(&L1, &lD.n);
            }
        }
        if (lD.n.next != &lD.n)
            AppendAll(&L2, &lD.n);
        SwapLists(&lD.n, &L1);
    L7cd:
        if (lE.n.next != &lE.n)
            AppendAll(&L2, &lE.n);
        f58 = 1;
        f59 = b13;
    }
    ((MutexOps*)&mxA)->Unlock();
    DestroyDisplayList(&L2);
    ClearLinks(&L2);
    L2.prev = 0; L2.next = 0;
    ClearLinks(&L1);
}

// @ 0x95b860
void __thiscall WM::Shutdown()
{
    ResetChildWindowCache();
    FlushMessageQueue();
    s02(0, 1);
    s0e(0);
    s08(0);
    DestroyDisplayList(&lF.n);
    DestroyDisplayList(&lD.n);
    DestroyDisplayList(&lE.n);
}

// @ 0x95b8c0
WM::~WM()
{
    Shutdown();
}

// @ 0x95ba70
u32 __cdecl GetTableEntry(u32 i)
{
    if (i < 0x1d)
        return g_tbl_1440748[i];
    return 0x80;
}

// @ 0x95ba90
void __thiscall Chunk::Swap(Chunk* o)
{
    Chunk* tn = next; next = o->next; o->next = tn;
    int tc = count; count = o->count; o->count = tc;
    u32 n = (u32)o->count;
    if ((u32)count > n)
        n = (u32)count;
    for (int i = (int)n; i > 0; i--) {
        IRel* a = items[i - 1].obj; items[i - 1].obj = o->items[i - 1].obj; o->items[i - 1].obj = a;
        u32 b = items[i - 1].b; items[i - 1].b = o->items[i - 1].b; o->items[i - 1].b = b;
    }
}

// @ 0x95bb20
void __thiscall RenderCtx::End2D()
{
    IRenderable* r = batch.Take();
    if (r) {
        Chunk* c = chunks;
        while (c->next)
            c = c->next;
        if (c->count == 5) {
            Chunk* n = AllocRenderableListChunk();
            c->next = n;
            c = n;
        }
        int i = c->count;
        c->count = i + 1;
        r->AddRef();
        c->items[i].obj = (IRel*)r;
        c->items[i].b = (u32)mode;
    }
}

// @ 0x95bbc0
void __thiscall RenderCtx::AddRenderable(IRenderable* r)
{
    End2D();
    Chunk* c = chunks;
    while (c->next)
        c = c->next;
    if (c->count == 5) {
        Chunk* n = AllocRenderableListChunk();
        c->next = n;
        c = n;
    }
    int i = c->count;
    c->count = i + 1;
    r->AddRef();
    c->items[i].obj = (IRel*)r;
    c->items[i].b = 0;
}

// @ 0x95bc10
Batch2D* __thiscall RenderCtx::Begin2D(IRenderMode* m)
{
    if (!m)
        m = defMode;
    if (m != mode) {
        End2D();
        mode = m;
    }
    return &batch;
}

// @ 0x95bc40
Node** __thiscall RenderCtx::RenderBatch(Node** pIt, DispEntry* head, int flag)
{
    DispEntry* buf[64];
    EVec vec;
    vec.begin = buf; vec.end = buf; vec.cap = buf + 64; vec.buf = buf;
    DispEntry* first = head;
    u32 depth = head->depth;
    Node* anchor = list;
    *pIt = &head->link;
    if (&head->link != anchor) {
        do {
            DispEntry* cur = (DispEntry*)*pIt;
            int lowest = cur->lowest;
            if (!(lowest > (int)(depth + 1))) {
                if (cur != head && lowest <= (int)depth)
                    break;
                DispEntry* v = cur;
                if (vec.end < vec.cap) {
                    DispEntry** p = vec.end;
                    vec.end = p + 1;
                    if (p)
                        *p = v;
                } else {
                    vec.Overflow(vec.end, &v);
                }
            }
            *pIt = (*pIt)->next;
        } while (*pIt != anchor);
    }
    Xform* savedMat = mat;
    u32 savedCol = colorMod;
    int n = (int)(vec.end - vec.begin);
    first->renderer->RenderBatch(first->data[first->bSecond].rdata, this, (Node**)vec.begin, n, flag);
    mat = savedMat;
    colorMod = savedCol;
    if (vec.begin && vec.begin != vec.buf)
        operator delete(vec.begin);
    return pIt;
}

// @ 0x95bd60
void __thiscall RenderCtx::RenderList(Node* lst, const RectF* r)
{
    list = lst;
    float sy, sx;
    sx = g_1470f1c / (r->x1 - r->x0);
    sy = g_1470f1c / (r->y1 - r->y0);
    vp.x0 = r->x0;
    vp.y0 = r->y0;
    vp.x1 = r->x1;
    vp.y1 = r->y1;
    IRenderMode* dm = defMode;
    if (!dm)
        dm = GetDefaultMode();
    bool flag = dm->vFlag();
    float* t = trans;
    if (!flag) {
        t[1] = sy * r->y0 + g_1485720;
        t[0] = g_13eb1bc_f - r->x0 * sx;
        t[2] = g_1471064;
    } else {
        t[0] = g_13eb1bc_f - (r->x0 + g_1471064) * sx;
        t[1] = (r->y0 + g_1471064) * sy + g_1485720;
        t[2] = g_1471064;
    }
    float* s = scale;
    s[0] = sx;
    s[1] = -sy;
    s[2] = 0.0f;
    Xform xf0;
    xf0.Init(trans, scale);
    mat = &xf0;
    if (lst->prev == lst)
        return;
    {
        Node* it = list;
        Node* first = it->next;
        for (; it != first; it = it->prev) {
            DispEntry* e = (DispEntry*)it->prev;
            if (e->renderer && e->renderer->NeedsPrepass()) {
                Node* tmp;
                RenderBatch(&tmp, e, 1);
            }
        }
    }
    DispEntry* cur = (DispEntry*)lst->next;
    Node* anchor = list;
    u32 firstLowest = cur->lowest;
    IRenderMode* curMode = 0;
    bool first = true;
    if ((Node*)cur == anchor)
        return;
    for (;;) {
        if (!first && !(cur->lowest > (u16)firstLowest))
            break;
        RenderData* d = &cur->data[cur->bSecond];
        first = false;
        xf = &d->xf;
        Xform tmpx;
        if (mat) {
            tmpx = d->xf;
            tmpx.Multiply(mat);
            xf = &tmpx;
        }
        float cx0, cy0, cx1, cy1;
        if (vp.x0 >= d->r2 || d->r0 >= vp.x1 || vp.y0 >= d->r3 || d->r1 >= vp.y1) {
            cx0 = 0.0f; cy0 = 0.0f; cx1 = 0.0f; cy1 = 0.0f;
        } else {
            cx0 = (d->r0 > vp.x0) ? d->r0 : vp.x0;
            cy0 = (d->r1 > vp.y0) ? d->r1 : vp.y0;
            cx1 = (vp.x1 > d->r2) ? d->r2 : vp.x1;
            cy1 = (vp.y1 > d->r3) ? d->r3 : vp.y1;
        }
        clip.x0 = cx0; clip.y0 = cy0; clip.x1 = cx1; clip.y1 = cy1;
        shade = d->shade;
        if (colorMod != 0xffffffff)
            shade = ModulateARGB32(d->shade, colorMod);
        if (cur->renderer) {
            if (curMode) {
                curMode->End();
                curMode = 0;
            }
            Node* it2;
            Node** res = RenderBatch(&it2, cur, 0);
            cur = (DispEntry*)*res;
        } else {
            for (Chunk* c = &cur->chunks; c; c = c->next) {
                int cnt = c->count;
                for (int i = 0; i < cnt; i++) {
                    if (curMode != (IRenderMode*)c->items[i].b) {
                        if (curMode)
                            curMode->End();
                        curMode = (IRenderMode*)c->items[i].b;
                        if (curMode)
                            curMode->Begin();
                    }
                    if (curMode)
                        curMode->Render((IRenderable*)c->items[i].obj, this);
                    else
                        ((IRenderable*)c->items[i].obj)->Render(this);
                }
            }
            cur = (DispEntry*)cur->link.next;
        }
        if ((Node*)cur == anchor)
            break;
    }
    if (curMode)
        curMode->End();
}

// @ 0x95c0d0
void __cdecl DrawClippedRect(IRenderer* obj, const RectF* a, const RectF* c, const RectF* b)
{
    float x0 = a->x0;
    RectF R;
    if (x0 >= b->x0 && b->x1 >= a->x1 && a->y0 >= b->y0 && b->y1 >= a->y1) {
        R.x0 = 0.0f; R.y0 = 0.0f; R.x1 = g_1485720; R.y1 = g_1485720;   // full-texture uv
        obj->DrawRect(a, c, &R);
        return;
    }
    float x1 = a->x1;
    float y1 = a->y1;
    float y0 = a->y0;
    float w = x1 - x0;
    float h = y1 - y0;
    if (g_1485720 > w || g_1485720 > h)
        return;
    R.x0 = x0; R.y0 = y0; R.x1 = x1; R.y1 = y1;
    R.Intersect(*a, *b);
    if (R.x0 == R.x1 || R.y0 == R.y1)
        return;
    float sx = g_1485720 / w;
    float sy = g_1485720 / h;
    RectF uv;
    uv.x0 = (R.x0 - x0) * sx;
    uv.y0 = (R.y0 - a->y0) * sy;
    uv.x1 = (R.x1 - x0) * sx;
    uv.y1 = (R.y1 - a->y0) * sy;
    obj->DrawRect(&R, c, &uv);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct WM {
    void UpdateRenderState(void*, int, int); // 0x0095a140
    void RenderWindow(void*, void*); // 0x0095a510
    void ComputeClip(void*, void*); // 0x00958150
};
struct Builder {
    Builder(); // 0x00952aa0
};
struct Base2D {
    Base2D(void*); // 0x009520a0
};
}
