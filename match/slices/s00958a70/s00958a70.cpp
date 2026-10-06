// Slice s00958a70 -- EA::UTFWin::WindowMgr hit-testing / message dispatch helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00958a70.h"

#define W(o) (*(u32*)((u8*)this + (o)))
#define WB(o) (*(u8*)((u8*)this + (o)))
#define WF(o) (*(float*)((u8*)this + (o)))
#define NODE(o) ((Node*)((u8*)this + (o)))

static __forceinline void InitNode(Node* n) { n->prev = n; n->next = n; }
static inline Win* NodeToWin(Node* n) { return n ? (Win*)((u8*)n - 8) : 0; }

// @ 0x958a70
Win* __thiscall WM::HitTest(Win* w, V2* pt, const V2& p3, V2* outLocal)
{
    if (!(w->flags & 1))
        return 0;
    Node* head = &w->children;
    Node* n = head->next;
    if (!(w->flags & 0x1000)) {
        for (; n != head; n = n->next) {
            Win* r = HitTest(NodeToWin(n), pt, p3, outLocal);
            if (r)
                return r;
        }
    }
    if (w->flags & 0x10)
        return 0;
    V2 loc;
    IWin* iw = w;
    if (!iw->vHit(*pt, &loc))
        return 0;
    if (!iw->vHitLocal(loc))
        return 0;
    if (outLocal) { outLocal->x = loc.x; outLocal->y = loc.y; }
    return w;
}

// @ 0x958b60
void __thiscall WM::MarkTree(Win* w)
{
    Node* head = &w->children;
    Node* n = head->next;
    w->b30 = (w->b30 & 0xef) | 8;
    w->f14 = 0;
    w->f78 = 0;
    for (; n != head; n = n->next)
        MarkTree(NodeToWin(n));
}

// @ 0x958bb0
void __thiscall WM::DestroyDisplayList(Node* head)
{
    for (Node* e = head->next; e != head; e = e->next) {
        u8* ep = (u8*)e;
        Chunk* c = (Chunk*)(ep + 0x18);
        Chunk* last;
        for (;;) {
            last = c;
            int cnt = c->count;
            for (int i = 0; i < cnt; i++) {
                IRel* o = c->items[i].obj;
                if (o) o->Release();
            }
            if (!c->next) break;
            c = c->next;
        }
        if (*(u32*)(ep + 0x18))
            FreeRenderableListChunks(*(void**)(ep + 0x18), last);
        if (*(u32*)(ep + 0x14)) {
            if (*(u32*)(ep + 0xa0)) (*(IObj**)(ep + 0x14))->Destroy(*(void**)(ep + 0xa0));
            if (*(u32*)(ep + 0xfc)) (*(IObj**)(ep + 0x14))->Destroy(*(void**)(ep + 0xfc));
            (*(IObj**)(ep + 0x14))->Release();
        }
    }
    FreeDisplayListEntries(head);
}

// @ 0x958c60
bool __thiscall WM::IsFocusWindow(IWin* w)
{
    if (w) {
        if (cur == w)
            return true;
        Node* head = &focusList.anchor;
        for (Node* n = head->next; n != head; n = n->next) {
            if (((IWin**)n)[2] == w)
                return true;
        }
    }
    return false;
}

// @ 0x958ca0
Iter __thiscall MsgList::EraseRange(Iter first, Iter last)
{
    while (first.n != last.n) {
        Node* nx = first.n->next;
        Node* n = nx->prev;
        n->prev->next = n->next;
        n->next->prev = n->prev;
        alloc->Free(n, 0x24);
        first.n = nx;
    }
    return last;
}

// @ 0x9595e0
void __thiscall MsgList::InsertRange(Node* where, Iter first, Iter last, int tag)
{
    if (first.n == last.n)
        return;
    do {
        const Msg& sm = ((MsgNode*)first.n)->msg;
        MsgNode* n = (MsgNode*)alloc->Alloc(0x24, 0, allocFlags);
        new (&n->msg) Msg(sm);
        n->link.next = where;
        n->link.prev = where->prev;
        where->prev->next = &n->link;
        where->prev = &n->link;
        first.n = first.n->next;
    } while (first.n != last.n);
}

// @ 0x958cf0
WM::WM()
    : mainWin(0), tickIter(&lB.n), f24(0), f25(0), mxA(0, 1), f58(0), f59(0), mxB(0, 1),
      fa8(0.0f), fac(0.0f), fb0(0.0f), fb4(0.0f), fb8(0), mx(0.0f), my(0.0f), fc4(0), hook(0),
      fcc(1), fd0(0), q0(EAlloc(GetAlloc())), q1(EAlloc(GetAlloc())), q2(EAlloc(GetAlloc())), q3(EAlloc(GetAlloc())), q4(EAlloc(GetAlloc())), f124(0), ts(0), mxC(0, 1), f688(0), focusList(EAlloc(GetAlloc())), cur(0), curCb(0), f834(0)
{
    W(0x68c) = 0;
    W(0x6b4) = 0;
    W(0x690) = 0;
    W(0x694) = 0;
    W(0x6a0) = 0;
    W(0x6b8) = 0;
    W(0x6bc) = 0;
    W(0x6c8) = 0;
    W(0x6dc) = 0;
    W(0x6e0) = 0;
    W(0x6e4) = 0;
    W(0x6f0) = 0;
    W(0x704) = 0;
    W(0x708) = 0;
    W(0x70c) = 0;
    W(0x718) = 0;
    W(0x72c) = 0;
    W(0x730) = 0;
    W(0x734) = 0;
    W(0x740) = 0;
    W(0x754) = 0;
    W(0x758) = 0;
    W(0x75c) = 0;
    W(0x768) = 0;
    W(0x77c) = 0;
    W(0x780) = 0;
    W(0x784) = 0;
    W(0x790) = 0;
    W(0x7a4) = 0;
    W(0x7a8) = 0;
    W(0x7ac) = 0;
    W(0x7b8) = 0;
    W(0x7cc) = 0;
    W(0x7d0) = 0;
    W(0x7d4) = 0;
    W(0x7e0) = 0;
    W(0x7f4) = 0;
    W(0x7f8) = 0;
    W(0x7fc) = 0;
    W(0x808) = 0;
}

// @ 0x958fa0
bool __thiscall WM::SendModifiedMsg(IWin* w, IWin* src, Msg* m)
{
    WM* self = this;
    Win* t = static_cast<Win*>(w);
    Msg msg = *m;
    msg.src = src;
    IWin* wi = t;
    msg.dst = wi;
    if (self->hook)
        self->hook->Notify(2, 0, &msg);
    bool r = false;
    if (self->DispatchMsgToWindow(t, &msg, 0))
        r = true;
    if (self->hook)
        self->hook->Notify(r ? 4 : 5, 0, &msg);
    return r;
}

// @ 0x959050
IWin* __thiscall WM::UpdateCursorWindow(V2* out, bool flag)
{
    V2 loc(g_1440738, g_1440738);
    float q[4];
    q[0] = g_13eb1bc; q[1] = mx; q[2] = my; q[3] = 0.0f;
    Win* hit = HitTest(mainWin, (V2*)&q[1], V2(0.0f, 0.0f), &loc);
    IWin* hw = hit;
    if (cur == 0 || cur->vAccepts(hw)) {
        SetFocus(1, hw);
    } else {
        SetFocus(1, cur);
        loc = cur->vToLocal(V2(mx, my));
    }
    Win* f = f6b4;
    if (f6bc) {
        IWin* b = f6bc;
        loc = b->vToLocal(V2(mx, my));
    }
    if (!f6bc && f && flag) {
        IWin* par = f->parent;
        if (par && (f->flags & 4))
            par->vSetOwner(f);
        SetFocus(0, f);
    }
    if (out) {
        out->x = loc.x;
        out->y = loc.y;
    }
    return f;
}

// @ 0x959230
IWin* __thiscall WM::FindWindowAt(const V2* pt)
{
    if (!mainWin)
        return 0;
    V2 zero(0.0f, 0.0f);
    float q[4];
    q[0] = g_13eb1bc; q[1] = pt->x; q[2] = pt->y; q[3] = 0.0f;
    Win* hit = HitTest(mainWin, (V2*)&q[1], zero, 0);
    if (hit)
        return hit;
    return 0;
}

// @ 0x9592a0
void __thiscall WM::LinkTickable(Win* w)
{
    if (!(w->b31 & 1) && !(w->flags & 8)) {
        if (*(u32*)((u8*)w + 0x1c))
            F9587d0(w);
        return;
    }
    if (*(u32*)((u8*)w + 0x1c) == 0) {
        Node* n = &w->n18;
        Node* a = &lB.n;
        n->prev = a->prev;
        n->next = a;
        a->prev = n;
        n->prev->next = n;
    }
}

// @ 0x9592e0
bool __thiscall WM::DispatchTree(Msg* m, bool flag)
{
    if (flag) {
        Win* t = static_cast<Win*>(m->src);
        if (DispatchMsgToWindow(t, m, 1)) {
            IHook* h = hook;
            if (h) {
                Win* t2 = static_cast<Win*>(m->src);
                IWin* a = t2;
                h->Notify(4, a, m);
            }
            return false;
        }
    }
    Win* t = static_cast<Win*>(m->dst);
    for (; t; t = t->parent) {
        if (DispatchMsgToWindow(t, m, 0)) {
            IHook* h = hook;
            if (h) {
                IWin* a = t;
                h->Notify(4, a, m);
            }
            return true;
        }
    }
    {
        IHook* h = hook;
        if (h)
            h->Notify(5, 0, m);
    }
    return false;
}

// @ 0x9593d0
bool __thiscall WM::DispatchUp(Win* w, Msg* m, bool flag)
{
    Win* p = w->parent;
    if (p && DispatchUp(p, m, flag))
        return true;
    if (DispatchMsgToWindow(w, m, 0)) {
        IHook* h = hook;
        if (h)
            h->Notify(4, w, m);
        return true;
    }
    if (flag) {
        Win* t = static_cast<Win*>(m->src);
        if (DispatchMsgToWindow(t, m, 1)) {
            IHook* h = hook;
            if (h) {
                Win* t2 = static_cast<Win*>(m->src);
                IWin* a = t2;
                h->Notify(4, a, m);
            }
            return true;
        }
    }
    IHook* h2 = hook;
    if (h2 && (IWin*)w == m->dst)
        h2->Notify(5, 0, m);
    return false;
}

// @ 0x9594b0
bool __thiscall WM::PopFocus(IWin* w, IWin* arg)
{
    IWin* oldCur;
    ICb* oldCb;
    if (w == 0)
        return false;
    if (cur == w) {
        oldCur = cur;
        oldCb = curCb;
        Node* head = &focusList.anchor;
        if (head->next != head) {
            Node* node = head->next;
            cur = ((IWin**)node)[2];
            curCb = ((ICb**)node)[3];
            if (cur->vGetParent()) {
                cur->vSetFlags(0x40, 1);
                cur->vGetParent()->vSetOwner(cur);
                SetFocus(0, cur);
            }
            node = head->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            focusList.alloc->Free(node, 0x10);
        } else {
            cur = 0;
            curCb = 0;
        }
    } else {
        Node* head = &focusList.anchor;
        Node* node = head->next;
        if (node == head)
            return false;
        while (((IWin**)node)[2] != w) {
            node = node->next;
            if (node == head)
                return false;
        }
        oldCur = ((IWin**)node)[2];
        oldCb = ((ICb**)node)[3];
        node = node->next->prev;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        focusList.alloc->Free(node, 0x10);
    }
    if (oldCur == 0)
        return false;
    if (oldCb)
        oldCb->Call(oldCur, arg);
    return true;
}

// @ 0x959640
bool __thiscall WM::SendMsgFull(IWin* src, IWin* win, Msg* m, bool a4, bool a5)
{
    u32 saved = f688;
    f688 = 0;
    Win* w = static_cast<Win*>(win);
    Msg msg = *m;
    msg.src = src;
    IWin* wi = w;
    msg.dst = wi;
    if (hook)
        hook->Notify(0, 0, &msg);
    bool r = false;
    if (a5) {
        r = DispatchUp(w, &msg, 0);
        f688 = saved;
        return r;
    }
    if (a4) {
        r = DispatchTree(&msg, 0);
        f688 = saved;
        return r;
    }
    if (DispatchMsgToWindow(w, &msg, 0)) {
        if (hook) {
            IWin* a = w;
            hook->Notify(4, a, &msg);
        }
        r = true;
    }
    if (hook && !r)
        hook->Notify(5, 0, &msg);
    f688 = saved;
    return r;
}
