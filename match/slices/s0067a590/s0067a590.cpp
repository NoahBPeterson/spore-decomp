// Slice s0067a590: UI/HintManager region functions (0x0067a590-0x0067b370).
// Mostly /O2 with SSE, no /EHsc, no /GS cookie in the big locals.
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }

// ---- masked callees (addresses are relocations) ----
extern "C" void* __cdecl ConfigManager();     // FUN_0067dd30
extern "C" void* __cdecl MessageServer();     // FUN_0067dcc0
extern "C" void* __cdecl GetManager();        // FUN_00957f30
extern "C" void* __cdecl FUN_0067caf0();
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);

// ===========================================================================
// @ 0x0067AC80  color pack helper (cdecl, 4 dwords)
// ===========================================================================
uint32_t __cdecl PackColor_67ac80(uint32_t a, uint32_t r, uint32_t g, uint32_t b)
{
    return (a << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

// ===========================================================================
// @ 0x0067AEE0  find element by +8 id in a pointer array at +0x20/+0x24
// ===========================================================================
struct E_aee0 { char pad[8]; int id; };
struct C_aee0 {
    char pad0[0x20];
    E_aee0** begin;   // +0x20
    E_aee0** end;     // +0x24
    E_aee0* find(int id);
};

E_aee0* C_aee0::find(int id)
{
    E_aee0** p = begin;
    for (; p != end; ++p) {
        E_aee0* e = *p;
        if (e->id == id)
            return e;
    }
    return 0;
}

// ===========================================================================
// @ 0x0067AC C0  enable/bring-forward the window referenced at +0x4c
// ===========================================================================
struct C_acc0 {
    char pad0[0x4c];
    void* p4c;        // +0x4c
    int toggle();
};

int C_acc0::toggle()
{
    if (!p4c || !*(void**)((char*)p4c + 0x6c))
        return 0;
    void* m = GetManager();
    void* sub = ((void* (__thiscall*)(void*))VT(m)[1])(m);
    return ((int (__thiscall*)(void*, void*, int))VT(sub)[0xf0 / 4])
               (sub, *(void**)((char*)p4c + 0x6c), 1);
}

// ===========================================================================
// @ 0x0067A120  the primary HintManager subobject method (outside slice)
// ===========================================================================
struct HM590;

// ===========================================================================
// @ 0x0067A590  PossiblyStartSpiceTutorial
// ===========================================================================
struct Elem134 {
    char data[0x134];
    Elem134(Elem134* src);   // 679b40
    ~Elem134();              // 678f70
};

struct Sub10 {
    char p0[8];
    Elem134* begin;          // +8  (abs +0x18)
    char p1[0xc];
    Elem134* end;            // +0x18 (abs +0x28)
    void Release();          // 6792f0
};

struct Sub1fc {
    void method(int);        // 92a7a0
};

struct HM590 {
    char pad0[0x10];
    Sub10 sub;               // +0x10
    char pad1[0x1cc];
    void Start();            // 67a120
    bool Check(Elem134*);    // 67a1b0
    void Add(Elem134*);      // 679e50
    void possibly(char a, char b);
};

void HM590::possibly(char a, char b)
{
    (void)a;
    void* cm = ConfigManager();
    if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
        Start();
    if (b) {
        ((Sub1fc*)((char*)this + 0x1fc))->method(1);
        return;
    }
    if (sub.begin != sub.end) {
        Elem134 t(sub.begin);
        if (*(int*)((char*)&t + 0xac) != 0) {
            sub.Release();
            Add(&t);
        }
        while (sub.begin != sub.end) {
            if (Check(sub.begin))
                break;
            Elem134 t2(sub.begin);
            sub.Release();
            Add(&t2);
            t2.~Elem134();
        }
        t.~Elem134();
    }
}

// ===========================================================================
// @ 0x0067A680  __cdecl callback: find manager, start tutorial flag
// ===========================================================================
struct C_a590_fwd {
    void possibly(int a, int b);
};

void __stdcall cb_67a680(void* unused, void* data)
{
    C_a590_fwd* r = (C_a590_fwd*)FUN_0067caf0();
    if (r)
        r->possibly((int)data, 1);
}

// ===========================================================================
// @ 0x0067A6A0  message-id filter member (secondary subobject at -0xc)
// ===========================================================================
struct C_a120_h {
    void f_67a120();
};

struct C_a6a0 {
    bool handle(int msg, void* data);
};

bool C_a6a0::handle(int msg, void* data)
{
    (void)data;
    if (msg == 0x670eccd) {
        void* cm = ConfigManager();
        if (((int (__thiscall*)(void*, int))VT(cm)[0x30 / 4])(cm, 0x4ea96cb) == 0)
            ((C_a120_h*)((char*)this - 0xc))->f_67a120();
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x0067A850  callback: release, reset tutorial, release again
// ===========================================================================
void __cdecl cb_67a850(void* p)
{
    C_a590_fwd* o = (C_a590_fwd*)p;
    if (o)
        ((void (__thiscall*)(void*))VT(o)[1])(o);
    o->possibly(0, 0);
    if (o)
        ((void (__thiscall*)(void*))VT(o)[2])(o);
}

// ===========================================================================
// @ 0x0067AF10 / 0x0067AF70 / 0x0067AFD0  condition processors
// ===========================================================================
struct Proc {
    virtual bool Evaluate(int conditionID) = 0;
};
struct VecU {
    int* begin;   // +0
    int* end;     // +4
};
struct C_af {
    char pad0[0xc];
    Proc** pbegin;   // +0xc
    Proc** pend;     // +0x10
    bool All(VecU* v);
    bool Any(VecU* v);
    bool Check(void* a);
};

bool C_af::All(VecU* v)
{
    unsigned n = (unsigned)(v->end - v->begin) >> 2;
    for (unsigned i = 0; i < n; ++i) {
        if (pend == pbegin)
            return false;
        Proc* p = *(pend - 1);
        if (!p->Evaluate(v->begin[i]))
            return false;
    }
    return true;
}

bool C_af::Any(VecU* v)
{
    unsigned n = (unsigned)(v->end - v->begin) >> 2;
    for (unsigned i = 0; i < n; ++i) {
        if (pend != pbegin) {
            Proc* p = *(pend - 1);
            if (p->Evaluate(v->begin[i]))
                return false;
        }
    }
    return true;
}

bool C_af::Check(void* a)
{
    char* b = (char*)a;
    if (!All((VecU*)(b + 0xc)))
        return false;
    if (((*(int*)(b + 0x24) - *(int*)(b + 0x20)) & 0xfffffffc) != 0
        && !Any((VecU*)(b + 0x20)))
        return false;
    if (((*(int*)(b + 0x38) - *(int*)(b + 0x34)) & 0xfffffffc) != 0
        && All((VecU*)(b + 0x34)))
        return false;
    return true;
}

// ===========================================================================
// @ 0x0067B150  cUIHints::cHint constructor
// ===========================================================================
extern char g_vtbl_cHint[];          // 0x14014ec
extern char g_vtbl_cHint_base[];     // 0x13ef094
extern "C" void* __cdecl EASTL_deallocate(void*);   // f47380

struct cString14 {
    char d[0x14];
    void construct();      // 6b5060
    char* c_str();         // 6b5240
};

struct cHint {
    void* vt;      // +0x00
    int ref;       // +0x04
    int f8;        // +0x08
    int* p0c; int* p10; int* p14;   // +0x0c
    int f18; int f1c;
    int* p20; int* p24; int* p28;   // +0x20
    int f2c; int f30;
    int* p34; int* p38; int* p3c;   // +0x34
    int f40; int f44;
    float mPeriod; float f4c; float f50; float f54; float f58;  // +0x48
    int f5c; int f60; int f64; int f68; int f6c; int f70;
    char f74; char f75; char f76; char f77;
    cString14 mText;   // +0x78
    int f8c; int f90;  // +0x8c
    float f94;         // +0x94

    cHint* init();
    void dtor();
};

cHint* cHint::init()
{
    ref = 0;
    vt = g_vtbl_cHint;
    p0c = p10 = p14 = 0;
    p20 = p24 = p28 = 0;
    p34 = p38 = p3c = 0;
    mPeriod = 1.0e10f;
    f4c = 1.0f;
    f54 = 1.0f;
    f50 = 0.0f;
    f58 = 2.0f;
    f5c = f60 = f64 = f68 = f6c = 0;
    f70 = 0x1f9e21e8;
    f74 = f75 = f76 = 0;
    mText.construct();
    f8c = -1;
    f94 = 0.0f;
    return this;
}

void cHint::dtor()
{
    mText.c_str();
    if (p34 && *((int*)p34 - 1) != 0)
        EASTL_deallocate(p34);
    if (p20 && *((int*)p20 - 1) != 0)
        EASTL_deallocate(p20);
    if (p0c && *((int*)p0c - 1) != 0)
        EASTL_deallocate(p0c);
    vt = g_vtbl_cHint_base;
}

// ===========================================================================
// @ 0x0067B270  UI::cHintManager constructor
// ===========================================================================
extern char g_HM_14426a0[];   // 0x14426a0
extern char g_HM_1401510[];   // 0x1401510
extern char g_HM_14014f4[];   // 0x14014f4
extern char g_HM_13eb938[];   // 0x13eb938
extern char g_HM_13ec458[];   // 0x13ec458

struct cHintManager {
    void* vt0; int f4; void* vt8;   // +0x00
    int* p0c; int* p10; int* p14;   // +0x0c
    int f18; int f1c;
    int* p20; int* p24; int* p28;   // +0x20
    int f2c; int f30;
    float f34; float f38; int f3c; float f40; float f44; int f48; int f4c; float f50;

    cHintManager* init();
    void dtor();
};

cHintManager* cHintManager::init()
{
    f4 = 0;
    vt8 = g_HM_14426a0;
    vt0 = g_HM_1401510;
    vt8 = g_HM_14014f4;
    p0c = p10 = p14 = 0;
    p20 = p24 = p28 = 0;
    f34 = 0.0f; f38 = 0.0f; f3c = 0; f40 = 0.0f; f44 = 0.0f;
    f48 = 3; f4c = 0; f50 = 0.0f;
    return this;
}

struct VecHM {
    void clear(int* begin, int* end);   // FUN_00a693f0
    int* begin;
    int* end;
    int* cap;
};

void cHintManager::dtor()
{
    vt0 = g_HM_1401510;
    vt8 = g_HM_14014f4;
    VecHM* v = (VecHM*)&p20;
    v->clear(p20, p24);
    if (p20 && *((int*)p20 - 1) != 0)
        EASTL_deallocate(p20);
    if (p0c && *((int*)p0c - 1) != 0)
        EASTL_deallocate(p0c);
    vt8 = g_HM_13eb938;
    vt0 = g_HM_13ec458;
}

// ===========================================================================
// @ 0x0067A6E0  hint-manager message handler
// ===========================================================================
extern "C" void __cdecl BeginModal(void*, int, int);   // SPUIHelpers::BeginModal
extern "C" void __cdecl EndModal(void*, int, int);     // SPUIHelpers::EndModal
extern "C" float __cdecl sinf_(float);

struct Layout2;
struct HM6e0 {
    char pad0[0xec];
    void* p_ec;          // +0xec
    char padF0[0x199 - 0xf0];
    char b199;           // +0x199
    char pad19a[0x1f4 - 0x19a];
    char sub1f4[4];      // +0x1f4
    bool handle(void* a, int* b);
};

bool HM6e0::handle(void* a, int* b)
{
    if (!p_ec)
        return false;
    int type = b[2];
    if (type != 8) {
        if (type != 6 && type != 0x287259f6)
            return false;
        if (a != p_ec)
            return false;
        b199 = 1;
        ((C_a590_fwd*)((char*)this - 8))->possibly(0, 0);
        ((VecHM*)((char*)this + 0x1f4))->clear(0, 0);
        return false;
    }
    float v0 = *(float*)((char*)b + 0xc);
    float v1 = *(float*)((char*)b + 0x10);
    float loc[2];
    loc[0] = v0;
    loc[1] = v1;
    float out[2];
    ((void (__thiscall*)(void*, float*, float, float))VT(a)[0xc0 / 4])(a, out, v0, v1);
    void* p2 = ((void* (__thiscall*)(void*))VT(a)[0x14 / 4])(a);
    void* p3 = ((void* (__thiscall*)(void*, float*))VT(p2)[0x44 / 4])(p2, loc);
    void* m = GetManager();
    int c = ((int (__thiscall*)(void*, void*))VT(m)[0x80 / 4])(m, p_ec);
    void* cur = p_ec;
    if (cur == a) {
        if (c == 0) {
            if (p3 != cur)
                return false;
            BeginModal(cur, 0, 0);
        } else {
            if (p3 == cur)
                return false;
            EndModal(cur, 0, 0);
        }
    } else {
        if (c != 0)
            return false;
        if (p3 != cur)
            return false;
        BeginModal(cur, 0, 0);
    }
    float saved = loc[1];
    for (int i = 0; i < 7; ++i)
        ((int*)loc)[i] = b[i];
    loc[0] = v1;
    loc[1] = out[0];
    void* m2 = GetManager();
    ((void (__thiscall*)(void*, int, int, float*))VT(m2)[0x18 / 4])(m2, 0, 0, loc);
    return true;
}

// ===========================================================================
// @ 0x0067A880  hint-manager window/timer setup
// ===========================================================================
extern "C" void* __cdecl FUN_009512c0();
extern "C" void* __cdecl FUN_009512d0(int, int, const char*, void*);
extern "C" void __cdecl FUN_00929da0(void*, void*, void*);

struct SmoothRamp {
    SmoothRamp* init(float a, float b);   // 7fd570
};

struct Sub1b4 {
    void Register(void* cb, void* a, void* b);   // 929da0
};

struct HM880 {
    char pad0[0x1a4];
    SmoothRamp* t1;   // +0x1a4
    SmoothRamp* t2;   // +0x1a8
    SmoothRamp* t3;   // +0x1ac
    SmoothRamp* t4;   // +0x1b0
    char sub1b4[0x24];   // +0x1b4 .. +0x1d8
    char pad1d8[0x24];
    char pad1fc[4];
    void setup();
    void Start();
};

static SmoothRamp* MakeCallout_67a880(float a, float b)
{
    void* u = FUN_009512c0();
    void* mem = FUN_009512d0(0x48, 4, "CalloutTimer", u);
    if (!mem)
        return 0;
    return ((SmoothRamp*)mem)->init(a, b);
}

static void SetTimer_67a880(SmoothRamp** slot, SmoothRamp* nv)
{
    SmoothRamp* old = *slot;
    if (nv != old) {
        if (nv)
            ((void (__thiscall*)(void*))VT(nv)[0])(nv);
        *slot = nv;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[1])(old);
    }
}

void HM880::setup()
{
    ((Sub1b4*)((char*)this + 0x1b4))->Register((void*)0x678670, this, (char*)this + 8);
    ((Sub1b4*)((char*)this + 0x1d8))->Register((void*)0x678910, this, (char*)this + 8);
    ((Sub1b4*)((char*)this + 0x1fc))->Register((void*)0x67a850, this, (char*)this + 8);
    SetTimer_67a880(&t1, MakeCallout_67a880(0.0f, 0.1f));
    ((void (__thiscall*)(void*, int, float))VT(t1)[0x40 / 4])(t1, 0, 0.2f);
    SetTimer_67a880(&t2, MakeCallout_67a880(0.1f, 0.1f));
    ((void (__thiscall*)(void*, int, float))VT(t2)[0x40 / 4])(t2, 0, 0.8f);
    SetTimer_67a880(&t3, MakeCallout_67a880(0.1f, 0.1f));
    ((void (__thiscall*)(void*, int, float))VT(t3)[0x40 / 4])(t3, 0, 0.16f);
    SetTimer_67a880(&t4, MakeCallout_67a880(0.1f, 0.1f));
    ((void (__thiscall*)(void*, int, float))VT(t4)[0x40 / 4])(t4, 0, 0.48f);
    Start();
    void* ms = MessageServer();
    ((void (__thiscall*)(void*, void*, int))VT(ms)[0x20 / 4])(ms, (char*)this + 0xc, 0x670eccd);
}

// ===========================================================================
// @ 0x0067AAF0  insert a hint element (ret 0x28)
// ===========================================================================
struct HMAdd {
    char pad0[0x10];
    int* e10; int* e14; int* e18;
    int* e1c;
    int* e20; int* e24;
    int* e28; int* e2c;
    int* e30; int* e34;
    char pad38[4];
    void add(int a, int b, int c, int d, void* e, int f, int g, int h, int i, void* j);
};

struct Elem134b {
    char data[0x134];
};

void HMAdd::add(int a, int b, int c, int d, void* e, int f, int g, int h, int i, void* j)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i; (void)j;
    Elem134b tmp;
    // NOTE: incomplete reconstruction (bookkeeping-heavy container insert).
    (void)tmp;
}

// ===========================================================================
// @ 0x0067AD00  cUIHints::UpdateVisibleHint
// ===========================================================================
extern "C" float __cdecl sinf_f(float);

struct LayoutD {
    void* FindWindowByID(unsigned int id, int mode);   // 8105b0
};

struct cUIHintsD {
    char pad0[0x3c];
    LayoutD* p3c;   // +0x3c
    char pad40[0xc];
    void* p4c;      // +0x4c
    float f50;      // +0x50
    float f54;      // +0x54
    float f58;      // +0x58
    void update(int b, float dt);
};

void cUIHintsD::update(int b, float dt)
{
    if (p4c && *(void**)((char*)p4c + 0x6c)) {
        void* m = GetManager();
        void* sub = ((void* (__thiscall*)(void*))VT(m)[1])(m);
        void* win = ((void* (__thiscall*)(void*, void*, int))VT(sub)[0xf0 / 4])
                        (sub, *(void**)((char*)p4c + 0x6c), 1);
        if (win) {
            dt = f50 + dt;
            f50 = dt;
            float s = sinf_f(dt * 10.0f);
            int alpha = (int)(((s + 1.0f) * 0.5f) * 255.0f);
            unsigned arg = (unsigned)(alpha << 24) | 0xffffff;
            ((void (__thiscall*)(void*, unsigned))VT(win)[0x5c / 4])(win, arg);
            ((void (__thiscall*)(void*))VT(win)[0x90 / 4])(win);
        }
    }
    float f = 1.0f;
    int t = *(int*)(b + 0x90);
    if (t == 4)
        f = *(float*)(b + 0x94) / *(float*)(b + 0x54);
    else if ((unsigned)(t - 6) < 2)
        f = 1.0f - *(float*)(b + 0x94) / *(float*)(b + 0x58);
    unsigned hi = (unsigned)(int)(f * 255.0f) << 24;
    void* w1 = p3c->FindWindowByID(0x52432e0, 1);
    void* w2 = p3c->FindWindowByID(0x5244c68, 1);
    void* w3 = p3c->FindWindowByID(0x5244c08, 1);
    unsigned col = (((unsigned (__thiscall*)(void*))VT(w1)[0x30 / 4])(w1) & 0xffffff) | hi;
    ((void (__thiscall*)(void*, unsigned))VT(w1)[0x5c / 4])(w1, col);
    ((void (__thiscall*)(void*, unsigned))VT(w2)[0x5c / 4])(w2, col);
    ((void (__thiscall*)(void*, unsigned))VT(w3)[0x5c / 4])(w3, col);
}

// ===========================================================================
// @ 0x0067B030 / 0x0067B370  eastl vector inserts (template instantiations)
// ===========================================================================
extern "C" int* __cdecl EASTL_alloc16(unsigned int, const char*, int, int, const char*, int); // f473a0
extern "C" void __cdecl DoInsertValueVec(int*, void*, unsigned int);  // 11e0744
extern "C" void __cdecl FUN_00a690d0(void*, void*, void*);           // a690d0

struct Vec16 {
    char* begin; char* end; char* cap;
    char* insert(char* pos, unsigned short v);
};
char* Vec16::insert(char* pos, unsigned short v)
{
    char* next = end + 2;
    if (next < cap) {
        *(unsigned short*)next = 0;
        memmove(pos + 2, pos, (unsigned)(end - pos));
        *(unsigned short*)pos = v;
        end += 2;
        return pos;
    }
    unsigned cnt = (unsigned)((cap - begin) >> 1) - 1;
    unsigned used = (unsigned)((end - begin) >> 1) + 1;
    unsigned want = cnt > 8 ? cnt * 2 : 8;
    unsigned capNew = (want > used ? want : used) + 1;
    char* mem = (char*)EASTL_alloc16(capNew * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    DoInsertValueVec((int*)mem, begin, (unsigned)(pos - begin));
    char* p = mem + (pos - begin);
    *(unsigned short*)p = v;
    DoInsertValueVec((int*)(p + 2), pos, (unsigned)(end - pos));
    char* newEnd = p + 2 + (end - pos);
    if (begin && (int)((cap - begin) & 0xfffffffe) > 2)
        EASTL_deallocate(begin);
    begin = mem;
    end = newEnd;
    cap = mem + capNew * 2;
    return p;
}

// ===========================================================================
// @ 0x0067B370  eastl vector insert of AutoRefCount<cHint>
// ===========================================================================
struct VecRef {
    int* begin; int* end; int* cap;
    void insert(int* pos, int** value);
};
void VecRef::insert(int* pos, int** value)
{
    int* e = end;
    if (e != cap) {
        if (pos <= *value && *value < e)
            *value += 1;
        if (e) {
            int v = e[-1];
            *e = v;
            if (v)
                (*(int*)(v + 4))++;
        }
        FUN_00a690d0(pos, end - 1, end);
        int nv = **value;
        int ov = *pos;
        if (nv != ov) {
            if (nv)
                (*(int*)(nv + 4))++;
            *pos = nv;
            if (ov) {
                int rc = (*(int*)(ov + 4)) - 1;
                *(int*)(ov + 4) = rc;
                if (rc == 0) {
                    *(int*)(ov + 4) = 1;
                    ((void (__thiscall*)(void*, int))VT((void*)ov)[0])((void*)ov, 1);
                }
            }
        }
        end += 1;
        return;
    }
    unsigned n = (unsigned)(e - begin);
    unsigned capNew = n ? n * 2 : 1;
    int* mem = (int*)EASTL_alloc16(capNew * 4, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    DoInsertValueVec(mem, begin, (unsigned)(pos - begin));
    int* p = (int*)((char*)mem + ((char*)pos - (char*)begin));
    if (p) {
        int v = **value;
        *p = v;
        if (v)
            (*(int*)(v + 4))++;
    }
    DoInsertValueVec(p + 1, pos, (unsigned)(e - pos) * 4);
    int* newEnd = (int*)((char*)(p + 1) + ((char*)e - (char*)pos));
    if (begin && begin[-1] != 0)
        EASTL_deallocate(begin);
    begin = mem;
    end = newEnd;
    cap = mem + capNew;
}
