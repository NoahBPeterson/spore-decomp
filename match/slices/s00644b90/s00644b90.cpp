// SP::cSPUIAssetBrowser helpers (0x00644b90..0x0064562f). Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "../s00642530/s00642530.h"

// ---- virtual-slot call helpers (the exact class declarations of these UI objects live elsewhere) ----
#define VSLOT(o, byteoff) ((*(void***)(o))[(byteoff) / 4])
typedef void  (__thiscall *Fn_v0)(void*);
typedef int   (__thiscall *Fn_i0)(void*);
typedef void* (__thiscall *Fn_p2)(void*, uint32_t, uint32_t);
typedef void  (__thiscall *Fn_v2)(void*, uint32_t, uint32_t);
typedef void  (__thiscall *Fn_v2b)(void*, uint32_t, bool);
typedef void  (__thiscall *Fn_v1)(void*, void*);
typedef uint8_t (__thiscall *Fn_b0)(void*);

struct WinV {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void SetFlag(uint32_t f, bool v);
};
struct ListDataV {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual WinV* GetWin(uint32_t id, uint32_t f);
};

void* AuthManager();                                      // SP::Pollen::AuthManager (0x607a60)
struct WebBrowser { void SetActive(bool a); void Navigate(uint32_t a, uint32_t b); };
struct SubA { void Set(uint32_t a); void Fn_e720(); void Fn_ef30(uint32_t a, uint32_t b); };

#define AT(T, off) (*(T*)((char*)this + (off)))

struct Browser {
    void SetWebBrowserVisibility(char vis, uint32_t x);
    void Fn_c50(char vis, uint32_t a, uint32_t b);
    void Fn_d10(char vis, int x);
    int IsA();
    int IsB();
    int CanSporepediaShowSporeGuide();
    void Fn_e20(char flag);
    void Fn_eb0();
    void PreloadTextures();
    void Fn_160();
    void Fn_260();
    uint32_t Get_c();
    uint32_t Get_10();
    void SetCallToActionMessage(const short* msg);
    uint8_t Query(const Key3* in, Key3* out);
};

// @ 0x644b90
void Browser::SetWebBrowserVisibility(char vis, uint32_t x) {
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    WinV* lv = AT(WinV*, 0x90);
    if (lv) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        lv->SetFlag(1, f != 0);
    }
    WebBrowser* wb = AT(WebBrowser*, 0x21c);
    if (wb) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        wb->SetActive(f);
        if (!bl && vis) MessageServer()->Send(0xd4231540, &x, 0);
    }
}

// @ 0x644c50
void Browser::Fn_c50(char vis, uint32_t a, uint32_t b) {
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    WinV* lv = AT(WinV*, 0x94);
    if (lv) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        lv->SetFlag(1, f != 0);
    }
    WebBrowser* wb = AT(WebBrowser*, 0x220);
    if (wb) {
        uint8_t f;
        if (!bl && vis) f = 1; else f = 0;
        wb->SetActive(f);
        if (!bl && vis) AT(WebBrowser*, 0x220)->Navigate(a, b);
    }
}

// @ 0x644d10
void Browser::Fn_d10(char vis, int x) {
    void* am = AuthManager();
    uint8_t bl = ((Fn_b0)VSLOT(am, 0x24))(am);
    ListDataV* ld = AT(ListDataV*, 0x64);
    if (ld) {
        WinV* w = ld->GetWin(0x561e0a8, 1);
        if (w) {
            uint8_t f;
            if (bl && vis) f = 1; else f = 0;
            w->SetFlag(1, f != 0);
        }
    }
    if (AT(SubA*, 0xc4)) {
        if (vis && !bl) {
            AT(SubA*, 0xc4)->Set(1);
            if (x) { AT(SubA*, 0xc4)->Fn_ef30(x, 0); return; }
            AT(SubA*, 0xc4)->Fn_e720();
            return;
        }
        AT(SubA*, 0xc4)->Set(0);
    }
}

// @ 0x644db0
int Browser::IsA() {
    void* p = AT(void*, 0x98);
    if (p) {
        uint32_t r = (uint32_t)((Fn_i0)VSLOT(p, 0x28))(p);
        if (r & 1) return 1;
    }
    return 0;
}

// @ 0x644dd0
int Browser::IsB() {
    void* p = AT(void*, 0x90);
    if (p) {
        uint32_t r = (uint32_t)((Fn_i0)VSLOT(p, 0x28))(p);
        if (r & 1) return 1;
    }
    return 0;
}

// @ 0x644df0
int Browser::CanSporepediaShowSporeGuide() {
    if (AT(uint8_t, 0x1c) != 0 && AT(uint32_t, 0x158) == 0 && AT(uint32_t, 0x230) == 0) return 1;
    return 0;
}

// @ 0x644e20
void Browser::Fn_e20(char flag) {
    void* w = AT(void*, 0x80);
    if (w && AT(void*, 0x5c)) {
        if (flag) {
            ((Fn_v2)VSLOT(w, 0x7c))(w, 1, 1);
            w = AT(void*, 0x80);
            ((Fn_v2)VSLOT(w, 0x7c))(w, 0x40, 1);
            void* p = AT(void*, 0x5c);
            ((Fn_v1)VSLOT(p, 0xe8))(p, AT(void*, 0x80));
            AT(uint8_t, 0x1f) = 1;
            return;
        }
        ((Fn_v2)VSLOT(w, 0x7c))(w, 1, AT(uint8_t, 0x1c));
        w = AT(void*, 0x80);
        ((Fn_v2)VSLOT(w, 0x7c))(w, 0x40, 0);
        if (AT(void*, 0x64)) {
            void* p = AT(void*, 0x5c);
            ((Fn_v1)VSLOT(p, 0xe8))(p, AT(void*, 0x64));
        }
        AT(uint8_t, 0x1f) = 0;
    }
}

// @ 0x644eb0
struct StyleMgr { void* GetStyle(uint32_t id, uint32_t z); };
StyleMgr* GetStyleManager(uint32_t a);                    // EA::Text::GetStyleManager (0x885bd0)
void GetBounds(float* out, void* win);                    // FUN_00805ef0
typedef void (__thiscall *Fn_rect)(void*, float*, uint32_t, uint32_t);
void Browser::Fn_eb0() {
    void* cfg = AT(void*, 0xb0);
    if (!cfg) return;
    uint32_t id = (uint32_t)((Fn_i0)VSLOT(cfg, 0x40))(cfg);
    char* st = (char*)GetStyleManager(1)->GetStyle(id, 0);
    cfg = AT(void*, 0xb0);
    if (!cfg) return;
    void* prop = ((Fn_p2)VSLOT(cfg, 0xc))(cfg, 0xf15f4bd, 0);
    if (!prop || !st) return;
    *(float*)(st + 0x200) = AT(float, 0x214);
    if (*(int*)(st + 0x254) != 2) return;
    *(int*)(st + 0x254) = 0;
    float r0[4];
    GetBounds(r0, AT(void*, 0xb0));
    while (*(float*)(st + 0x200) > 8.0f) {
        float r1[4];
        ((Fn_rect)VSLOT(prop, 0x20))(prop, r1, 0, 1);
        if (!((r1[2] - r1[0]) > (r0[2] - r0[0]))) break;
        *(float*)(st + 0x200) = *(float*)(st + 0x200) - 1.0f;
    }
    *(int*)(st + 0x254) = 2;
}

// ---- 20-byte element {a, b, c, plain-refcounted d, intrusive-refcounted e} ----
struct PlainRC { virtual void AddRef(); virtual void Release(); };
struct Ent20 { uint32_t a, b, c; PlainRC* d; RCObj* e; };
struct VecEnt20 { Ent20 *mpBegin, *mpEnd, *mpCap; bool empty() const { return mpBegin == mpEnd; } uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); } };

// @ 0x644fc0
struct RelPair { PlainRC* b; RCObj* a; void Release2(); };
void RelPair::Release2() {
    if (a) a->Release();
    if (b) b->Release();
}

// @ 0x644ff0
struct LocaleMsg2 { uint32_t vt0, vt1, f8, fc; PlainRC* owner; void Dtor(); };
void LocaleMsg2::Dtor() {
    if (owner) owner->Release();
    vt1 = 0x13ef094;
    vt0 = 0x13eb918;
}

// @ 0x645010
struct ResourceKey {
    uint32_t inst, type, group;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : inst(i), type(t), group(g) {}
};
struct TexturePreload { TexturePreload* ctor(int n); void PreloadTextureList(const ResourceKey* k); };
void* Alloc6b(size_t, const char*, int, int, int, int);
void Browser::PreloadTextures() {
    static ResourceKey keys[8] = {
        ResourceKey(0x7c6511a1, 0x510a95b, 0x851d4139), ResourceKey(0x0ab75403, 0x510a95b, 0x851d4139),
        ResourceKey(0x84f7a71d, 0x510a95b, 0x851d4139), ResourceKey(0xdecdb609, 0x510a95b, 0x851d4139),
        ResourceKey(0xc1966e00, 0x510a95b, 0x851d4139), ResourceKey(0x5a71fb79, 0x510a95b, 0x851d4139),
        ResourceKey(0xd525562b, 0x510a95b, 0x851d4139), ResourceKey(0x993618cc, 0x510a95b, 0x851d4139) };
    void* mem = EASTL_allocator_allocate(0x34, "", 0, 0, 0, 0);
    TexturePreload* tp = mem ? ((TexturePreload*)mem)->ctor(-1) : 0;
    PlainRC* old = AT(PlainRC*, 0x218);
    if (tp != (TexturePreload*)old) {
        if (tp) ((PlainRC*)tp)->AddRef();
        AT(TexturePreload*, 0x218) = tp;
        if (old) old->Release();
    }
    for (ResourceKey* k = keys; k < keys + 8; ++k)
        AT(TexturePreload*, 0x218)->PreloadTextureList(k);
}

// @ 0x645160
struct BrowserB { void Fn990(); };
struct Obj3 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual Key3* GetKey(); };
struct WinMgr { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void SetWin(uint32_t, void*); };
WinMgr* GetWindowManager();                               // SP::WindowManager (0x67caa0)
void ErrDlg(void* a, const Key3* k);                      // FUN_00809db0
void Browser::Fn_160() {
    Ent20* begin = AT(Ent20*, 0xcc);
    Ent20* end = AT(Ent20*, 0xd0);
    uint32_t i = 0;
    Key3 out; out.a = 0; out.b = 0; out.c = 0;
    uint32_t n = (uint32_t)(end - begin);
    if (n != 0) {
        int off = 0;
        do {
            Obj3* o = (Obj3*)((Ent20*)((char*)AT(Ent20*, 0xcc) + off))->e;
            Key3 k; k.a = 0; k.b = 0; k.c = 0;
            if (o) {
                Key3* kp = o->GetKey();
                k.a = kp->a; k.b = kp->b; k.c = kp->c;
            }
            if (!Query(&k, &out)) {
                AT(uint32_t, 0x230) = 7;
                ErrDlg(&AT(char, 4), &out);
                return;
            }
            ++i;
            off += 0x14;
        } while (i < (uint32_t)(AT(Ent20*, 0xd0) - AT(Ent20*, 0xcc)));
    }
    GetWindowManager()->SetWin(0, AT(void*, 0x64));
    ((BrowserB*)this)->Fn990();
}

// @ 0x645260
bool Fn_666480(void* p);                                  // FUN_00666480 (thiscall on [this+0x228])
struct Obj6 { bool Check(); };
struct Mgr6 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void Get(); };
struct SvcA { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void Do13(uint32_t a, uint32_t b); };
struct SvcB { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual SvcA* Get(); };
SvcB* GetSvcB();                                          // FUN_0067de40
extern Key3 g1525894, g15258a0;
struct Obj6p { char pad[0x28]; uint32_t f28; };
struct Obj6c { bool Check(); };
void Browser::Fn_260() {
    const Key3* p;
    Obj6p* o = AT(Obj6p*, 0x228);
    if (o && ((Obj6c*)o)->Check()) {
        GetSvcB()->Get()->Do13(AT(Obj6p*, 0x228)->f28, 0);
        p = &g1525894;
    } else {
        p = &g15258a0;
    }
    ErrDlg(&AT(char, 4), p);
    AT(uint32_t, 0x230) = 5;
}

// @ 0x6452c0
uint32_t Browser::Get_c() {
    VecEnt20& v = AT(VecEnt20, 0xcc);
    if (!v.empty() && v.size() == 1) return (uint32_t)v.mpBegin->d;
    return 0;
}

// @ 0x645300
uint32_t Browser::Get_10() {
    VecEnt20& v = AT(VecEnt20, 0xcc);
    if (!v.empty() && v.size() == 1) return (uint32_t)v.mpBegin->e;
    return 0;
}

// @ 0x645340
struct Node12 { uint32_t a; PlainRC* b; uint32_t c; };
Node12* __stdcall AllocNode12(const Node12* src) {
    Node12* n = (Node12*)EASTL_allocator_allocate(0xc, "Editor", 0, 0, EASTL_ALLOC_FILE, 0xd1);
    if (n) {
        n->a = src->a;
        n->b = src->b;
        if (n->b) n->b->AddRef();
    }
    n->c = 0;
    return n;
}

// @ 0x645390
struct Ent20x : Ent20 { Ent20x* Copy(const Ent20* o); };
Ent20x* Ent20x::Copy(const Ent20* o) {
    a = o->a; b = o->b; c = o->c;
    d = o->d; if (d) d->AddRef();
    e = o->e; if (e) e->AddRef();
    return this;
}

// @ 0x6453e0
Ent20** UninitCopyOut(Ent20** out, Ent20* first, Ent20* last, Ent20* dest) {
    *out = dest;
    for (; first != last; ++first) {
        Ent20* p = *out;
        if (p) {
            p->a = first->a; p->b = first->b; p->c = first->c;
            p->d = first->d; if (p->d) p->d->AddRef();
            p->e = first->e; if (p->e) p->e->AddRef();
        }
        *out = *out + 1;
    }
    return out;
}

// @ 0x645450
Ent20* UninitCopy(Ent20* first, Ent20* last, Ent20* dest) {
    if (first != last) {
        do {
            if (dest) {
                dest->a = first->a; dest->b = first->b; dest->c = first->c;
                dest->d = first->d; if (dest->d) dest->d->AddRef();
                dest->e = first->e; if (dest->e) dest->e->AddRef();
            }
            ++first;
            ++dest;
        } while (first != last);
        return dest;
    }
    return dest;
}

// @ 0x6454c0
Ent20* DestroyRange(Ent20* first, Ent20* last, Ent20* dest) {
    if (first != last) {
        do {
            if (first->e) first->e->Release();
            PlainRC* x = first->d;
            if (x) x->Release();
            ++first;
            ++dest;
        } while (first != last);
        return dest;
    }
    return dest;
}

// @ 0x645510
void UninitFillN(Ent20* dest, uint32_t n, const Ent20* v) {
    while (n > 0) {
        if (dest) {
            dest->a = v->a; dest->b = v->b; dest->c = v->c;
            dest->d = v->d; if (dest->d) dest->d->AddRef();
            dest->e = v->e; if (dest->e) dest->e->AddRef();
        }
        n--;
        ++dest;
    }
}

// @ 0x6455b0
struct cString { char buf[20]; cString(); const short* c_str(); const short* ValueOrDefault(); };
struct MsgHandlerObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void SetText(const short* t);
};
void GetPropertyAsText(void* list, uint32_t id, cString* out);   // SP::GetPropertyAsText (0x6a1360)
void Browser::SetCallToActionMessage(const short* msg) {
    if (AT(MsgHandlerObj*, 0xb0)) {
        cString s;
        if (!msg || *msg == 0) {
            GetPropertyAsText(AT(void*, 0x194), 0x344ec74e, &s);
            msg = s.ValueOrDefault();
        }
        AT(MsgHandlerObj*, 0xb0)->SetText(msg);
        ((BrowserB*)this)->Fn990();
        s.c_str();
    }
}
// --- equivalence checker address annotations
    void MessageServer(...); // 0x0067dcc0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
