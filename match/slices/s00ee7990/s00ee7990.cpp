// Slice s00ee7990 — SPUI asset/palette editor UI object: destructors, layout
// init/shutdown, message handlers and category helpers.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <intrin.h>
#include "s00ee7990.h"

// @ 0x00ee7990 — reset the base vtables and drop every owned child object.
void __thiscall SpuEd::BaseDtor()
{
    o000 = 0x148abd0;
    o008 = 0x148abc8;
    _ReadWriteBarrier();
    if (o02c)
    {
        u32 h = o02c;
        o02c = 0;
        RemoveHandler((void*)h, (void*)o030, o034, (int)o038, (int)o03c);
    }
    if (o024) ((VI*)o024)->v01();
    if (o020) ((VI*)o020)->v01();
    if (o01c) ((VI*)o01c)->v02();
    if (o018) ((VI*)o018)->v02();
    if (o014) ((VI*)o014)->v02();
    if (o010) ((VI*)o010)->v02();
    if (o00c) ((VI*)o00c)->v02();
    o008 = 0x13eb394;
    o000 = 0x13ec458;
}

// @ 0x00ee7a50 — unregister the message handler and release the derived children.
void __thiscall SpuEd::DtorDerived()
{
    void* h = this ? (void*)((char*)this + 8) : 0;
    ((XMsgSrv*)MessageServer())->m11(h, 0x44ef2b8, 0xffffd8f1);
    if (o024)
    {
        ((VI*)o024)->v09();
        if (o024) { VI* p = (VI*)o024; o024 = 0; p->v01(); }
    }
    if (o020)
    {
        ((XPaletteUI*)o020)->Shutdown();
        if (o020) { VI* p = (VI*)o020; o020 = 0; p->v01(); }
    }
    if (o00c)
    {
        ((VIN*)o00c)->n06();
        if (o00c) { VI* p = (VI*)o00c; o00c = 0; p->v02(); }
    }
    if (o014)
    {
        ((VI*)o014)->v05();
        if (o014) { VI* p = (VI*)o014; o014 = 0; p->v02(); }
    }
    if (o018)
    {
        ((VI*)o018)->v05();
        if (o018) { VI* p = (VI*)o018; o018 = 0; p->v02(); }
    }
    if (o010)
    {
        ((VI*)o010)->v05();
        if (o010) { VI* p = (VI*)o010; o010 = 0; p->v02(); }
    }
}

// @ 0x00ee7b40 — enable/disable one of the editor's five modes.
void __thiscall SpuEd::SetMode(int mode, u8 on)
{
    if (mode == -1) return;
    switch (mode)
    {
    case 0:
        if (on)
        {
            char* u = (char*)g_universe;
            ((XHint*)*(u32*)(u + 0xd4))->ToggleHint(0x89, 0x8a);
        }
        break;
    case 1: ((VI*)o00c)->v08(on); break;
    case 2: ((VI*)o018)->v06(on); break;
    case 3: ((VI*)o014)->v06(on); break;
    case 4: ((VI*)o010)->v06(on); break;
    }
    if (on) o028 = (u32)mode;
    else o028 = 0xffffffff;
}

// @ 0x00ee7c60 — refresh the currently selected category view.
void __thiscall SpuEd::Update(void* arg)
{
    VI* p = (VI*)o00c;
    if (p) p->v07((int)arg);
    if (o020) ((XPaletteUI*)o020)->UpdateCategories(arg);
    if (o010)
    {
        if (((XPaletteUI*)o020)->FindCategoryIndex() == 4)
            ((VI*)o010)->v07((int)arg);
    }
}

// @ 0x00ee7cb0 — find the planet slot whose key/offset pair matches id.
int __cdecl FindPlanetSlot(u32 id, int* outA, int* outB)
{
    u32 key, off;
    if (id >= 0x72c2826u) { key = 0x3a8be428; off = id + 0xf8d3d7da; }
    else if (id >= 0x72c2823u) { key = 0x29c388a; off = id + 0xf8d3d7dd; }
    else { key = 0x6d60a1cc; off = id + 0xf8d3d7e0; }

    char* rec = (char*)GetPlanetRec();
    void* mgr = GetSpeciesMgr();
    int count = (*(int*)(rec + 0xc0) - *(int*)(rec + 0xbc)) / 0xc;
    int found = -1;
    int i = 0;
    if (count > 0)
    {
        int walk = 0;
        do
        {
            XSpecies* sp = (XSpecies*)((XSpecMgr*)mgr)->GetAt(*(u32*)(rec + 0xbc) + walk);
            if (sp->GetID() == key && *(int*)(*(int*)(rec + 0xf8) + i * 4) == (int)off)
            {
                found = i;
                break;
            }
            i++;
            walk += 0xc;
        } while (i < count);
    }
    if (outA) *outA = (int)key;
    if (outB) *outB = (int)off;
    return found;
}

// @ 0x00ee7da0 — construct: set vtables, init the three sub-objects, hook messages.
SpuEd* __thiscall SpuEd::Ctor()
{
    o004 = 0;
    o008 = 0x14426a0;
    o00c = 0x13eb394;
    o010 = 0x140b5a0;
    _ReadWriteBarrier();
    o000 = 0x148ac18;
    o008 = 0x148abfc;
    o00c = 0x148abf4;
    o010 = 0x148abf0;
    char* p = (char*)this + 0x18;
    int n = 2;
    do { ((XSub*)p)->Ctor(); p += 0x70; } while (--n >= 0);
    o168 = 0;
    o16c = 0;
    o170 = 0;
    if (MessageServer())
        ((XMsgSrv*)MessageServer())->m09((void*)((char*)this + 0xc), 0x65ff54a);
    return this;
}

// @ 0x00ee7e50 — tear the class down again (derived level 3).
void __thiscall SpuEd::Dtor3()
{
    o000 = 0x148ac18;
    o008 = 0x148abfc;
    o00c = 0x148abf4;
    o010 = 0x148abf0;
    if (MessageServer())
        ((XMsgSrv*)MessageServer())->m11((void*)((char*)this + 0xc), 0x65ff54a, 0xffffd8f1);
    if (o170) ((VI*)o170)->v01();
    if (o16c) ((VI*)o16c)->v01();
    if (o168) ((VI*)o168)->v02();
    char* p = (char*)this + 0x168;
    int n = 2;
    do { p -= 0x70; ((XSub*)p)->Dtor(); } while (--n >= 0);
    o008 = 0x13eb938;
    o000 = 0x13ec458;
    o00c = 0x13eb394;
}

// @ 0x00ee7f00 — create and wire up the SPUI layout; returns whether it is live.
u8 __thiscall SpuEd::InitLayout(void* parent)
{
    u8 ret = 0;
    void* mem = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    XDialog* dlg = mem ? ((XDialog*)mem)->Ctor() : 0;
    XDialog* old = (XDialog*)o168;
    if (dlg != old)
    {
        if (dlg) ((VI*)dlg)->v00();
        o168 = (u32)dlg;
        if (old) ((VI*)old)->v02();
    }
    if (!((XLayout*)o168)->Init((const void*)0x15ac800, 0, 0x5b598fa))
    {
        ((XLayout*)o168)->Shutdown(1);
        if (o168)
        {
            VI* p = (VI*)o168;
            o168 = 0;
            p->v02();
        }
        return 0;
    }
    XWin* w = (XWin*)((XLayout*)o168)->FindWindowByID(0x7355a68, 1);
    if (parent && w)
    {
        ((XLayout*)o168)->SetParentWin(parent, 1, 0x5b598fa);
        Rect* rf = ((XWin*)parent)->w14();
        Rect rc;
        rc.x = 0.0f;
        rc.y = 0.0f;
        rc.w = rf->w - rf->x;
        rc.h = rf->h - rf->y;
        ((XWin*)w)->w27(&rc);
        ((XWin*)w)->w65((void*)((char*)this + 8));
        ret = 1;
    }
    int tag = 0x72c2820;
    char* kp = (char*)0x15ac80c;
    char* sub = (char*)this + 0x18;
    int n = 3;
    int k = 0;
    do
    {
        Rect r2;
        r2.x = 0.0f; r2.y = 0.0f; r2.w = 0.0f; r2.h = 0.0f;
        void* win = ((XLayout*)o168)->FindWindowByID((u32)(k + 0x78fea00), 1, &r2);
        if (((XSub*)sub)->Check(win))
        {
            if (((XSub*)sub)->CheckKey(kp, 3))
            {
                for (int i = 0; i < 3; i++)
                {
                    XLayout* l2 = (XLayout*)((XSub*)sub)->Get(i);
                    XWin* ww = (XWin*)l2->FindWindowByID(0x4a1cb70, 1);
                    if (ww) ((XWin*)ww)->w20(tag);
                    tag++;
                }
            }
        }
        kp += 0xc;
        sub += 0x70;
        k++;
    } while (--n);
    return ret;
}

// @ 0x00ee8110 — reset the sub-objects and drop the layout.
void __thiscall SpuEd::ShutdownLayout()
{
    char* p = (char*)this + 0x18;
    int n = 3;
    do { ((XSub*)p)->Reset(); p += 0x70; } while (--n);
    if (o168)
    {
        ((XLayout*)o168)->SetParentWin((void*)n, 1, 0x5b598fa);
        ((XLayout*)o168)->Shutdown(1);
        if (o168)
        {
            VI* p2 = (VI*)o168;
            o168 = (u32)n;
            p2->v02();
        }
    }
}

// @ 0x00ee8180 — message handler: toggle the asset view for palette messages.
u8 __thiscall SpuEd::OnMsg2(u32 msg, void* p)
{
    if (msg == 0x65ff54a && *(u32*)((char*)p + 0x10) == 0x40464100)
    {
        u32 v = *(u32*)((char*)p + 0x18);
        switch (v)
        {
        case 0x7ec9d82e:
        case 0x556c486:
        case 0x3b0ac2c4:
        case 0xd5521361:
            break;
        default:
            return 1;
        }
        XLayout* lay = (XLayout*)o15c;
        u8 vis = lay->IsVisible();
        XWin* w = (XWin*)lay->GetWin();
        if (w) ((VIN*)w)->n00();
        if (vis) ((VI*)((char*)this - 0xc))->v06(0);
        ((VI*)((char*)this - 0xc))->v05();
        ((VI*)((char*)this - 0xc))->v04((int)w);
        if (vis) ((VI*)((char*)this - 0xc))->v06(1);
        if (w) ((VIN*)w)->n01();
    }
    return 1;
}

// @ 0x00ee8240 — re-select the category slot for the active universe record.
void __thiscall XCat::Refresh(u8 which)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (!rec) return;
    u32 id = *(u32*)(rec + 0x160);
    int outCat = -1;
    u8 flag;
    FindCategory(id, &outCat, &flag);
    if (outCat < 0) return;
    if ((u32)outCat >= 0xf) return;
    u32 chosen = which ? g_catA[outCat] : g_catB[outCat];
    if (chosen == id) return;
    XUniv* u = (XUniv*)rec;
    u->F33bf0();
    u->F352c0(chosen);
    u->F34560();
    u->F31ea0();
}

// @ 0x00ee82c0 — apply a palette selection change to the active record.
void __thiscall SpuEd::UpdateCategory(u32 sel)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (!rec) return;
    u32 id = *(u32*)(rec + 0x160);
    int outCat;
    u8 flag = 0;
    ((XCat*)this)->FindCategory(id, &outCat, &flag);
    u32 idx = sel + 0xe94e7f70;
    if ((int)idx < 0 || idx >= 0xf) return;
    u32 chosen = flag ? g_catA[idx] : g_catB[idx];
    if (chosen == id) return;
    XUniv* u = (XUniv*)rec;
    u->F33bf0();
    u->F352c0(chosen);
    u->F34560();
    u->F31ea0();
    XWin* w = (XWin*)((XLayout*)o168)->FindWindowByID(0x16b1858d, 1);
    if (!w) return;
    u8 inTable = ((XCat*)this)->IsInTable(chosen);
    Fn1350(w, flag && inTable);
    Fn2fa0(w, sel);
}

// @ 0x00ee83a0 — set the object the asset browser edits and launch its context.
void __thiscall SpuEd::SetObject(void* obj)
{
    void* old = (void*)o170;
    if (obj != old)
    {
        if (obj) ((VI*)obj)->v00();
        o170 = (u32)obj;
        if (old) ((VI*)old)->v01();
    }
    FindPlanetSlot((u32)((XW2*)(void*)o170)->x07(), (int*)&obj, 0);
    u32 tag;
    switch ((u32)obj)
    {
    default:         tag = (u32)obj;   break;
    case 0x29c388a:  tag = 0xdc1ff56b; break;
    case 0x3a8be428: tag = 0xc86f310d; break;
    case 0x6d60a1cc: tag = 0xcece845;  break;
    }
    XLaunchCtx ctx;
    ctx.Ctor();
    ctx.v[0] = tag;
    ctx.v[14] = (u32)((char*)this + 0x10);
    LaunchCtx(&ctx);
    ctx.Dtor();
}

// @ 0x00ee8460 — show/hide the three editor overlay windows for a selection.
void __thiscall SpuEd::Select(void* win)
{
    u8 x = (FindPlanetSlot((u32)((XW2*)win)->x07(), 0, 0) != -1);
    void* cur = WindowManager()->w18(1);
    u8 b;
    if (win == cur) b = 1;
    else b = ((XWin*)win)->w62((int)cur);
    u8 y = b;
    XWin* wa = (XWin*)((XWin*)win)->w60(0x73272b0, 0);
    if (wa) wa->w31(1, y);
    if (b) y = x ? 1 : 0; else y = 0;
    XWin* wb = (XWin*)((XWin*)win)->w60(0x4a1cb6d, 0);
    if (wb) wb->w31(1, y);
    if (b) x = y ? 1 : 0; else x = 0;
    XWin* wc = (XWin*)((XWin*)win)->w60(0x7b6b2cd, 0);
    if (wc) wc->w31(1, x);
}

// @ 0x00ee8570 — tear down the base level 4 object.
void __thiscall SpuEd::Dtor4()
{
    o000 = 0x148ac3c;
    o008 = 0x148ac34;
    _ReadWriteBarrier();
    if (o024) ((VI*)o024)->v01();
    if (o020) ((VI*)(o020 + 0xc))->v01();
    if (o00c)
    {
        u32 h = o00c;
        o00c = 0;
        RemoveHandler((void*)h, (void*)o010, o014, (int)o018, (int)o01c);
    }
    o008 = 0x13eb394;
    o000 = 0x13ec458;
}

// @ 0x00ee85e0 — enable/disable editor editing (hook or unhook the handler).
void __thiscall SpuEd::Enable2(u8 on)
{
    char* rec = *(char**)((char*)g_universe + 0x18);
    if (on)
    {
        if (o00c == 0)
        {
            void* p = (void*)((char*)this + 8);
            o00c = (u32)MessageServer();
            o010 = (u32)p;
            o014 = 0x15ac738;
            o018 = 1;
            o01c = 0;
            if (o00c && p)
                ((XMsgSrv*)o00c)->m09(p, *(u32*)0x15ac738);
            ((XUniv*)rec)->F36380();
        }
        char* u = (char*)g_universe;
        ((XHint*)*(u32*)(u + 0xd4))->ToggleHint(0xa5, 0xa6);
        return;
    }
    ((XUniv*)rec)->F363c0();
    if (o024)
    {
        ((VI*)o024)->v03(0);
        if (o024) { VI* p = (VI*)o024; o024 = 0; p->v01(); }
    }
    if (o00c)
    {
        u32 h = o00c;
        o00c = 0;
        RemoveHandler((void*)h, (void*)o010, o014, (int)o018, (int)o01c);
    }
}

// @ 0x00ee86c0 — message handler: adopt a new message target object.
u8 __thiscall SpuEd::OnMsg3(u32 msg, void* p)
{
    if (msg == 0x73e7eb7)
    {
        void* old = (void*)o018;
        if (p != old)
        {
            if (p) ((VI*)((char*)p + 0xc))->v00();
            o018 = (u32)p;
            if (old) ((VI*)((char*)old + 0xc))->v01();
        }
        g_univ18 = o018;
        g_launchObj.Add(0);
    }
    return 0;
}

// @ 0x00ee8720 — adopt a new source object and rebuild the editor helper.
u8 __thiscall SpuEd::SetSource(void* src)
{
    void* old = (void*)o00c;
    if (src != old)
    {
        if (src) ((VI*)src)->v00();
        o00c = (u32)src;
        if (old) ((VI*)old)->v01();
    }
    if (o00c)
    {
        void* mem = EAAllocate(0x3c, (const char*)0x13eb430, 0, 0, 0, 0);
        void* obj = mem ? ((XObj3c*)mem)->Init() : 0;
        void* old2 = (void*)o010;
        if (obj != old2)
        {
            if (obj) ((VI*)obj)->v02();
            o010 = (u32)obj;
            if (old2) ((VIN*)old2)->n03();
        }
        void* a = (void*)o00c;
        VI* pb = (VI*)o010;
        void* r = ((XWin*)a)->w60(0xd68dd230, 1);
        pb->v04((int)r);
    }
    return 1;
}

// @ 0x00ee87f0 — close the editor: hide and release the helper objects.
void __thiscall SpuEd::Close()
{
    ((VI*)this)->v08(0);
    if (o010)
    {
        ((VI*)o010)->v05();
        if (o010) { VI* p = (VI*)o010; o010 = 0; ((VIN*)p)->n03(); }
    }
    if (o00c) { VI* q = (VI*)o00c; o00c = 0; q->v01(); }
}
