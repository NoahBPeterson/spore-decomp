// Slice s0095a580 -- EA::UTFWin::WindowMgr message-queue processing + display-list rebuild.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast  (no /EH: member dtors not EH-registered)
#include "s0095a580.h"
#include "../s00958a70/s00958a70.h"   // sibling header: its annotations count for equiv.py

struct MutexOps {
    void __thiscall Lock(const void* name);                        // 0x9221b0
    void __thiscall Unlock();                                      // 0x922270
};

#define LMUTEX() ((MutexOps*)&mxC)->Lock((const void*)0x1440688)
#define UMUTEX() ((MutexOps*)&mxC)->Unlock()

struct RawMsgList { Node anchor; IAlloc* alloc; u32 allocFlags; };

static inline Iter MkIter(Node* n) { Iter i; i.n = n; return i; }
static inline Win* NodeToWin(Node* n) { return n ? (Win*)((u8*)n - 8) : 0; }

// eastl intrusive range splice: move [first,last) to just before pos.
static void Splice(Node* pos, Node* first, Node* last)
{
    Node* after = last->prev;
    after->next = pos;
    first->prev->next = last;
    pos->prev->next = first;
    Node* old = pos->prev;
    pos->prev = last->prev;
    last->prev = first->prev;
    first->prev = old;
}

// Shared display-list entry fill (lines 53-96 / 115-138 of BuildDisplayList).
static void FillDLEntry(WindowMgr* self, DLEntry* e, Win* w, u32* info, u8 b0c)
{
    e->prevEntry = (DLEntry*)w->f78;
    e->b0c = b0c;
    e->b0d = 0;
    e->b0e = 0;
    e->depth  = (u16)info[0];
    e->lowest = (u16)info[1];
    IRenderer* r = *(IRenderer**)((u8*)w + 0x1e8);
    e->renderer = r;
    if (r != 0) {
        ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
        e->fA0 = (u32)((void*(__thiscall*)(void*, void*))(*(void***)r)[0x10 / 4])(r, (void*)((u8*)w + 4));
    }
    e->fFC = 0;
    {
        u32* d = (u32*)e->data;
        u32* s = (u32*)((u8*)w + 0x14c);
        for (int i = 0; i < 0x11; i++) d[i] = s[i];
    }
    self->ComputeClip(e->clip, w);
    e->f9c = *(u32*)((u8*)w + 0x1d4);
}

// ------------------------------------------------------------------ 0x95a580
// @ 0x95a580
void __thiscall WindowMgr::BuildDisplayList(Node* out, Win* w, void* info_)
{
    u32* info = (u32*)info_;
    bool go = !(w->b30 & 4) && ((w->b30 & 1) != 0 || (w->flags & 1) != 0);
    if (info[1] > info[0]) info[1] = info[0];
    if (!go) {
        if (!(w->b30 & 8)) MarkTree(w);
        return;
    }

    if (w->b30 & 0x10) {
        DLEntry* e = AllocDisplayListEntry();
        {
            RenderCtx ctx((void*)this);
            ctx.chunks = &e->chunks;
            RenderWindow(w, &ctx);
            if (e->chunks.count == 0 && *(IRenderer**)((u8*)w + 0x1e8) == 0) {
                FreeDisplayListEntry(e);
                w->f78 = 0;
            } else {
                FillDLEntry(this, e, w, info, 1);
                Node* prev = out->prev;
                e->link.prev = prev;
                e->link.next = out;
                out->prev = &e->link;
                prev->next = &e->link;
                w->f78 = (u32)e;
            }
        }
    } else {
        DLEntry* e = (DLEntry*)w->f78;
        if (e != 0) {
            if (e->b0c == 0 || e->chunks.count != 0 || e->renderer != 0) {
                e = AllocDisplayListEntry();
                FillDLEntry(this, e, w, info, 0);
                Node* prev = out->prev;
                e->link.prev = prev;
                e->link.next = out;
                out->prev = &e->link;
                prev->next = &e->link;
                w->f78 = (u32)e;
            } else {
                w->f78 = 0;
            }
        }
    }

    if (w->f78 != 0) info[1] = 0x7fffffff;
    w->b30 &= 0xe7;
    w->f14 = 0;

    Node* head = &w->children;
    if (head->prev != head) {
        (*info)++;
        Node* stop = head->next;
        for (Node* n = head->prev; ; n = n->prev) {
            Win* child = (Win*)((u8*)n - 8);
            BuildDisplayList(out, child, info);
            if (n == stop) break;
        }
        (*info)--;
    }
}

// ------------------------------------------------------------------ 0x95a820
// @ 0x95a820
void __thiscall FocusListX::InsertFront(const void* value)
{
    Node* first = anchor.next;
    u8* n = (u8*)alloc->Alloc(0x10, 0, allocFlags);
    u8* v = n + 8;
    if (v != 0) {
        ((u32*)v)[0] = ((const u32*)value)[0];
        ((u32*)v)[1] = ((const u32*)value)[1];
    }
    ((Node*)n)->next = first;
    ((Node*)n)->prev = first->prev;
    first->prev->next = (Node*)n;
    first->prev = (Node*)n;
}

// ------------------------------------------------------------------ 0x95a870
// @ 0x95a870
MsgListX* __thiscall MsgListX::AssignFrom(MsgListX* src)
{
    if (this == src) return this;
    Node* d = anchor.next;
    Node* s = src->anchor.next;
    for (;;) {
        if (d == &anchor) break;
        if (s == &src->anchor) {
            EraseRange(MkIter(d), MkIter((Node*)this));
            return this;
        }
        ((MsgNode*)d)->msg = ((MsgNode*)s)->msg;
        d = d->next;
        s = s->next;
    }
    if (s != &src->anchor)
        InsertRange(&anchor, MkIter(s), MkIter((Node*)src), (int)src);
    return this;
}

// ------------------------------------------------------------------ 0x95a8e0
// @ 0x95a8e0
void __thiscall WindowMgr::SetViewportSize(float vw, float vh)
{
    LMUTEX();
    Msg msg;
    msg.src = 0;
    msg.dst = 0;
    msg.rest[0] = 0x4ecd5687;
    *(float*)&msg.rest[1] = vw;
    *(float*)&msg.rest[2] = vh;
    Node* first = q0.anchor.next;
    MsgNode* n = (MsgNode*)q0.alloc->Alloc(0x24, 0, q0.allocFlags);
    Msg* pm = &n->msg;
    if (pm != 0)
        *(Msg*)pm = msg;
    n->link.next = first;
    n->link.prev = first->prev;
    first->prev->next = &n->link;
    first->prev = &n->link;
    UMUTEX();
}

// ------------------------------------------------------------------ 0x95a980
// @ 0x95a980
bool __thiscall WindowMgr::SendMsg(IWin* src, IWin* win, Msg* m, bool a4)
{
    return SendMsgFull(src, win, m, a4, false);
}

// ------------------------------------------------------------------ 0x95a9a0
// @ 0x95a9a0
void __thiscall WindowMgr::PostMsg(IWin* src, IWin* dst, const Msg* m)
{
    MutexOps* mx = (MutexOps*)&mxC;
    mx->Lock((const void*)0x1440688);
    if (q4.anchor.next == &q4.anchor) {
        MsgNode* n = (MsgNode*)q0.alloc->Alloc(0x24, 0, q0.allocFlags);
        Msg* pm = &n->msg;
        if (pm != 0) *pm = *m;
        n->link.next = &q0.anchor;
        n->link.prev = q0.anchor.prev;
        q0.anchor.prev->next = &n->link;
        q0.anchor.prev = &n->link;
    } else {
        Node* first = q4.anchor.next;
        Node* second = first->next;
        if (&q0.anchor != first && &q0.anchor != second)
            Splice(&q0.anchor, first, second);
        ((MsgNode*)q0.anchor.prev)->msg = *m;
        f124--;
    }
    MsgNode* last = (MsgNode*)q0.anchor.prev;
    last->msg.src = src;
    last->msg.dst = dst;
    mx->Unlock();
}

// ------------------------------------------------------------------ 0x95aa80
// @ 0x95aa80
void __thiscall WindowMgr::ProcessMessages()
{
    MsgList mA(EAlloc((void*)GetAlloc()));
    MsgList mB(EAlloc((void*)GetAlloc()));

    LMUTEX();
    if (q0.anchor.next != &q0.anchor)
        Splice(&q1.anchor, q0.anchor.next, &q0.anchor);
    u32 count = f124;
    UMUTEX();

    u32 saved = f688;
    f688 = 0;

    if (q1.anchor.next != &q1.anchor) {
        int deferred = 0;
        while (q1.anchor.next != &q1.anchor) {
            Node* first = q1.anchor.next;
            Node* second = first->next;
            if (&mA.anchor != first && &mA.anchor != second)
                Splice(&mA.anchor, first, second);
            Node* cur = mA.anchor.prev;
            Msg* msg = (Msg*)((u8*)cur + 8);
            if (hook)
                hook->Notify(1, (IWin*)0, msg);
            bool ok;
            if (msg->dst == 0) {
                ok = FCtx(msg, 1);
            } else {
                ok = DispatchMsgToWindow((Win*)((u8*)msg->dst - 4), msg, 0);
            }
            if (hook)
                hook->Notify(ok ? 4 : 5, (IWin*)0, msg);
            if (count < 0x10) {
                Node* c2 = mA.anchor.prev;
                Splice(&mB.anchor, c2, c2->next);
                deferred++;
                count++;
            } else {
                Node* c2 = mA.anchor.prev;
                c2->prev->next = c2->next;
                c2->next->prev = c2->prev;
                mA.alloc->Free(c2, 0x24);
            }
        }
        if (mB.anchor.next != &mB.anchor) {
            LMUTEX();
            Splice(q4.anchor.next, mB.anchor.next, &mB.anchor);
            f124 += (u32)deferred;
            UMUTEX();
        }
    }

    for (int i = 0; i < 10; i++) {
        u8* cb = (u8*)this + 0x6a0 + i * 0x28;
        if (*(u32*)cb != 0) {
            Msg m;
            {
                u32* d = (u32*)&m;
                u32* s = (u32*)(cb - 8);
                for (int j = 0; j < 7; j++) d[j] = s[j];
            }
            *(u32*)cb = 0;
            FCtx(&m, 0);
        }
    }

    {
        tickIter = lB.n.next;
        while (tickIter != &lB.n) {
            Node* it = tickIter;
            IWin* iw = (IWin*)((u8*)it - 0x14);
            Msg m;
            m.rest[0] = 0xc;
            SendMsgFull((IWin*)0, iw, &m, false, false);
            if (f24) f24 = 0;
            else tickIter = tickIter->next;
        }
    }

    f688 = saved;
}

// ------------------------------------------------------------------ 0x95add0
// @ 0x95add0
void __thiscall WindowMgr::AttachWindow(Win* w)
{
    w->b30 &= 0xef;
    w->f34 = (u32)this;
    w->f78 = 0;
    *(u32*)((u8*)w + 0x1c) = 0;
    w->f14 = 0;
    w->f24 = 0;
    *(u32*)((u8*)w + 0x7c) = fcc;
    fcc++;
    w->b30 &= 0x9f;
    F959fe0(w);
    if (!(w->b30 & 0x14)) {
        w->b30 |= 0x10;
        if (w->f78 == 0) {
            F958110();
        } else {
            Node* node   = (Node*)((u8*)w + 0x10);
            Node* anchor = (Node*)((u8*)this + 8);
            node->prev = anchor->prev;
            node->next = anchor;
            anchor->prev = node;
            node->prev->next = node;
        }
    }
    F9588c0(w);
    F958860(w);
    if ((w->b31 & 1) != 0 || (w->flags & 8) != 0) {
        if (*(u32*)((u8*)w + 0x1c) == 0) {
            Node* node   = (Node*)((u8*)w + 0x18);
            Node* anchor = (Node*)((u8*)this + 0x10);
            node->prev = anchor->prev;
            node->next = anchor;
            anchor->prev = node;
            node->prev->next = node;
        }
    } else {
        if (*(u32*)((u8*)w + 0x1c) != 0)
            F9587d0(w);
    }
    F958110();

    Node* head = &w->children;
    for (Node* n = head->next; n != head; n = n->next)
        AttachWindow(NodeToWin(n));

    IWin* iw = (IWin*)((u8*)w + 4);
    Msg m;
    m.rest[0] = 0x11;
    SendMsgFull(iw, iw, &m, false, false);
    m.rest[0] = 0xe;
    m.rest[1] = 0xffffffff;
    SendMsgFull(iw, iw, &m, false, false);
}

// ------------------------------------------------------------------ 0x95af00
// @ 0x95af00
void __thiscall WindowMgr::UpdateWindowCachedTransforms(Win* w)
{
    UpdateRenderState(w, 0, 0);
}

// ------------------------------------------------------------------ 0x95af20
// @ 0x95af20
bool __thiscall WindowMgr::SetFocusWindow(IWin* w, ICb* cb)
{
    if (w != 0) {
        if (!((bool(__thiscall*)(void*, IWin*))(*(void***)this)[0x80 / 4])(this, w)) {
            if (cur != 0)
                ((FocusListX*)&focusList)->InsertFront(&cur);
            curCb = cb;
            cur = w;
            void* v = ((void*(__thiscall*)(void*))(*(void***)w)[0x10 / 4])(w);
            if (v != 0) {
                ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 0x40, 1);
                void* v2 = ((void*(__thiscall*)(void*))(*(void***)w)[0x10 / 4])(w);
                ((void(__thiscall*)(void*, IWin*))(*(void***)v2)[0xe8 / 4])(v2, w);
                ((void(__thiscall*)(void*, int, IWin*))(*(void***)this)[0x4c / 4])(this, 0, w);
            }
            if (curCb != 0)
                ((void(__thiscall*)(void*, IWin*))(*(void***)curCb)[0])(curCb, w);
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------------------ 0x95afd0
// @ 0x95afd0
void __thiscall MsgListX::Swap(MsgListX& other)
{
    if (alloc == other.alloc && allocFlags == other.allocFlags) {
        EastlListSwap(this, &other);
        return;
    }
    RawMsgList tmp;
    tmp.anchor.next = &tmp.anchor;
    tmp.anchor.prev = &tmp.anchor;
    tmp.alloc = alloc;
    tmp.allocFlags = allocFlags;
    ((MsgList*)&tmp)->InsertRange(&tmp.anchor, MkIter(anchor.next), MkIter((Node*)this), 0);
    AssignFrom(&other);
    other.AssignFrom((MsgListX*)&tmp);
    Node* p = tmp.anchor.next;
    while (p != &tmp.anchor) {
        Node* n = p;
        p = p->next;
        tmp.alloc->Free(n, 0x24);
    }
}

// ------------------------------------------------------------------ 0x95b080
// @ 0x95b080
bool __thiscall WindowMgr::SetMainWindow(IWin* w, char release)
{
    Win* nw = (w == 0) ? 0 : (Win*)((u8*)w - 4);
    Win* old = mainWin;
    if (old == nw) return true;

    if (old != 0) {
        for (int i = 0; i < 10; i++) {
            u8* b = (u8*)this + 0x68c + i * 0x28;
            *(u32*)(b + 0x00) = 0;
            *(u32*)(b + 0x04) = 0;
            *(u32*)(b + 0x08) = 0;
            *(u32*)(b + 0x14) = 0;
        }
        DetachWindow(old);
        old = mainWin;
        mainWin.p = 0;
        if (release)
            ((void(__thiscall*)(void*))(*(void***)old)[7])(old);
        if (old)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }

    Win* old2 = mainWin;
    if (nw != old2) {
        if (nw)
            ((void(__thiscall*)(void*))(*(void***)nw)[0])(nw);
        mainWin.p = nw;
        if (old2)
            ((void(__thiscall*)(void*))(*(void***)old2)[1])(old2);
    }

    if (nw != 0) {
        AttachWindow(nw);
        if (!((bool(__thiscall*)(void*))(*(void***)nw)[6])(nw)) {
            DetachWindow(nw);
            return false;
        }
        IWin* iw = (IWin*)((u8*)nw + 4);
        float r[4];
        r[0] = 0.0f;
        r[1] = 0.0f;
        r[2] = fa8 * g_1470f1c;
        r[3] = fac * g_1470f1c;
        ((void(__thiscall*)(void*, void*))(*(void***)iw)[0x60 / 4])(iw, r);
        for (int i = 0; i < 10; i++)
            SetFocus(i, iw);
    }
    return true;
}

// ------------------------------------------------------------------ 0x95b290
// @ 0x95b290
void __thiscall WindowMgr::FlushMessageQueue()
{
    LMUTEX();
    ((MsgListX*)&q1)->Swap(*(MsgListX*)&q0);
    UMUTEX();

    Node* n = q1.anchor.next;
    while (n != &q1.anchor) {
        if (*(u32*)((u8*)n + 0x10) == 0x74d2e9 && *(u32*)((u8*)n + 0x18) != 0) {
            void* p = *(void**)((u8*)n + 0x18);
            ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        }
        n = n->next;
    }
    n = q1.anchor.next;
    while (n != &q1.anchor) {
        Node* nx = n->next;
        q1.alloc->Free(n, 0x24);
        n = nx;
    }
    q1.anchor.prev = &q1.anchor;
    q1.anchor.next = &q1.anchor;
}
