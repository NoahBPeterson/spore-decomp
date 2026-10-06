// Slice s00676660: SP::Achievements::Controller and related UI message handlers.
// Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char*, char**, int);

void  EAFree(void* p);                                                                    // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0

struct LayoutWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual int v04(); virtual void v05(); virtual void v06(); virtual unsigned v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual float* v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B();
    virtual void v1C(float, float); virtual void v1D(); virtual void v1E();
    virtual void SetTooltip(int, int);   // +0x7c
};

// Window parent with +0xd8 (add child) / +0xe8 (layout child)
struct WinParent {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03(); virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07(); virtual void p08(); virtual void p09(); virtual void p0A(); virtual void p0B(); virtual void p0C(); virtual void p0D(); virtual void p0E(); virtual void p0F(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p1A(); virtual void p1B(); virtual void p1C(); virtual void p1D(); virtual void p1E(); virtual void p1F(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p2A(); virtual void p2B(); virtual void p2C(); virtual void p2D(); virtual void p2E(); virtual void p2F(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
    virtual void AddChild(LayoutWindow*);   // +0xd8
    virtual void p37(); virtual void p38(); virtual void p39();
    virtual void LayoutChild(LayoutWindow*); // +0xe8
};

struct ResKey { uint32_t instance, type, group; };
struct ResMgr {
    virtual void m0(); virtual void m1(); virtual void m2();
    virtual char Get(ResKey* k, int, int, int, int, int);   // +0xc
};
ResMgr* GetManager();                                      // 0x0067DCD0

void  __fastcall FUN_00828BE0(void* pThis);   // 0x00828BE0
void  FUN_00808B20(void* a, void* b, int c);      // 0x00808B20
struct Inv599 { void FUN_00599BE0(void* a); };  // 0x00599BE0 thiscall
void  __fastcall FUN_00599530(void* a);    // 0x00599530 (thiscall receiver)
void  __fastcall FUN_00599560(void* a);    // 0x00599560 (thiscall receiver)
void* __fastcall FUN_005994D0(void* a);    // 0x005994D0 (cSpaceInventory ctor)
struct PropertyLayout {
    void* GetRootWindow();                 // 0x00828100
};
struct LayoutHolder {
    LayoutWindow* FindWindowByID(uint32_t id, int a);   // 0x008105B0
};
void SetWindowImage(LayoutWindow* w, ResKey* k, int a);  // 0x00807BB0 cdecl
void SetWindowAreaToParent(LayoutWindow* w);             // 0x00806BF0 cdecl
void* GetImageFromLayout(LayoutHolder* l, uint32_t id);  // 0x008061C0 cdecl
struct ImgObj { virtual void AddRef(); virtual void Release(); };
void CreateImageFromResource(ResKey* k, ImgObj** out, int a, int w, int h); // 0x00806230 cdecl
void SetDrawableImage(LayoutWindow* w, ImgObj* img, int a);                  // 0x008068D0 cdecl
struct Inv827 { void FUN_00827FA0(uint32_t id, uint32_t g); };                // 0x00827FA0 thiscall
void FUN_006A0AE0(void* a, uint32_t id, int* o1, void** o2);                 // 0x006A0AE0 cdecl
extern uint32_t g_0152976C;                                                  // 0x0152976C

struct SmartObj {
    virtual void o0(); virtual void o1(); virtual void o2();
};

// ---------------------------------------------------------------------------
// Host object owning the layout window pointers.
// ---------------------------------------------------------------------------
struct UIHost {
    char          mPad00[0xc];
    LayoutHolder  mLayout;          // +0x0c
    char          mPad0d[0x6b];
    LayoutWindow* mp78;   // +0x78
    LayoutWindow* mp7c;   // +0x7c
    void*         mp80;   // +0x80
    char          mPad84[0x14];
    char          mp98;   // +0x98
    char          mPad99[3];
    void*         mp9c;   // +0x9c

    void FUN_00677360(uint32_t arg);
    void FUN_00677380();
    void FUN_006773B0(WinParent* p);
    void FUN_00677470(uint32_t arg);
    char FUN_006774C0(uint32_t arg, int* msg);
    char FUN_00677220(WinParent* parent, char a, char b);
    void FUN_00677530(LayoutWindow* w, ResKey* k);
    void FUN_00677190(int* msg);

    char InitCursor();                                      // 0x00828250 (UI::CursorAttachment::Initialize)
    void SetFlag(int a);                                    // 0x00828020
};

// @ 0x00677360
void UIHost::FUN_00677360(uint32_t arg)
{
    LayoutWindow* w = mp78;
    if (w)
        w->SetTooltip(2, (int)arg);
}

// @ 0x00677380
void UIHost::FUN_00677380()
{
    LayoutWindow* w = mp7c;
    if (w) {
        w->v09();
        w = mp7c;
        if (w) {
            mp7c = 0;
            w->v01();
        }
    }
    FUN_00828BE0(this);
}

// @ 0x00677470
void UIHost::FUN_00677470(uint32_t arg)
{
    if (mp7c) {
        ((Inv599*)mp7c)->FUN_00599BE0(mp9c);
        mp7c->v08();
        FUN_00599530(mp7c);
        FUN_00808B20((void*)arg, ((PropertyLayout*)mp7c)->GetRootWindow(), 1);
    }
}

struct TooltipRec { uint32_t a, b, c; };
struct SetupHolder { void SetupTooltip(void* a, uint32_t v); };   // 0x00599C40

// @ 0x006773B0
void UIHost::FUN_006773B0(WinParent* p)
{
    if (p && mp7c && mp80) {
        TooltipRec* data = 0;
        int base = 0;
        FUN_006A0AE0(mp80, 0x54d95163, &base, (void**)&data);
        if (data) {
            uint32_t idx = ((LayoutWindow*)p)->v07() + base - 0x4c01bc2;
            if (idx <= 3)
                ((SetupHolder*)mp7c)->SetupTooltip(mp9c, data[idx].a);
        }
        mp7c->v08();
        FUN_00599530(mp7c);
        FUN_00808B20(p, ((PropertyLayout*)mp7c)->GetRootWindow(), 1);
    }
}

// @ 0x006774C0
char UIHost::FUN_006774C0(uint32_t arg, int* msg)
{
    switch (msg[2]) {
    case 0x1b:
        if (msg[1]) {
            if (((LayoutWindow*)msg[1])->v07() == 0x54f63a3e) {
                FUN_00677470((uint32_t)msg[1]);
                return 0;
            }
            FUN_006773B0((WinParent*)msg[1]);
        }
        break;
    case 0x1c:
        if (mp7c) {
            FUN_00599560(mp7c);
            return 0;
        }
        break;
    }
    return 0;
}

// @ 0x00677190
void UIHost::FUN_00677190(int* msg)
{
    LayoutWindow* w = mLayout.FindWindowByID(0x6679bc8, 1);
    if (w) {
        ResKey key;
        key.instance = msg[0];
        key.type = 0x2f7d0004;
        key.group = msg[2];
        w->SetTooltip(1, 0);
        if (GetManager()->Get(&key, 0, 0, 0, 0, 0)) {
            w->SetTooltip(1, 1);
            SetWindowImage(w, &key, -1);
        }
    }
}

// @ 0x00677220
char UIHost::FUN_00677220(WinParent* parent, char a, char b)
{
    mp98 = a;
    char ok = InitCursor();
    if (ok) {
    SetFlag(0);
    LayoutWindow* w = mLayout.FindWindowByID(0x125f2c4f, 1);
    LayoutWindow* old = mp78;
    if (w != old) {
        if (w)
            w->v00();
        mp78 = w;
        if (old)
            old->v01();
    }
    if (mp78 && parent) {
        if (mp78->v04() == 0) {
            parent->AddChild(mp78);
            parent->LayoutChild(mp78);
            mp78->v1C(0.0f, 0.0f);
            SetWindowAreaToParent(mp78);
        }
    }
    if (b) {
        LayoutWindow* n = (LayoutWindow*)EAAllocate(0xb0, "Editor", 0, 0, 0, 0);
        if (n)
            n = (LayoutWindow*)FUN_005994D0(n);
        else
            n = 0;
        LayoutWindow* o2 = mp7c;
        if (n != o2) {
            if (n)
                n->v00();
            mp7c = n;
            if (o2)
                o2->v01();
        }
        ((Inv827*)mp7c)->FUN_00827FA0(0x14e46c34, g_0152976C);
        mp7c->v07();
    }
    }
    return ok;
}

struct ImgRef {
    ImgObj* p;
    void reset() { ImgObj* t = p; if (t) { p = 0; t->Release(); } }
};

static __forceinline int RoundToInt(float f)
{
    __asm cvtss2si eax, f
}

// @ 0x00677530
void UIHost::FUN_00677530(LayoutWindow* w, ResKey* k)
{
    ImgObj* img = (ImgObj*)GetImageFromLayout(&mLayout, k->instance);
    if (img)
        img->AddRef();
    if (!img) {
        float* r = w->v0D();
        int h = RoundToInt(r[3] - r[1]);
        int wd = RoundToInt(r[2] - r[0]);
        ImgObj* t = img;
        if (t) {
            img = 0;
            t->Release();
        }
        CreateImageFromResource(k, &img, 0, wd, h);
    }
    SetDrawableImage(w, img, -1);
    if (img)
        img->Release();
}

// ---------------------------------------------------------------------------
// SP::Achievements::Controller
// ---------------------------------------------------------------------------
struct Rec {                 // accumulator record (12 bytes)
    uint32_t f0 : 1;         // +0 bit 0: achievement enabled
    uint32_t f1 : 1;         // bit 1: resets on load
    uint32_t fpad : 6;
    uint32_t f8 : 3;         // bits 8-10
    uint32_t frest : 21;
    int      value;          // +4
    int      threshold;      // +8
    Rec() : f0(0), f1(0), fpad(0), f8(0), value(0), threshold(0) {}
};
struct Entry { uint32_t key; Rec rec; };    // 16 bytes
struct VMap {
    Entry* mBegin; Entry* mEnd; Entry* mCap;
    int a1, a2;
    char cmp; char pad[3];
};
struct PairPB { uint32_t* it; char ok; PairPB(); };
struct USet {
    uint32_t* mBegin; uint32_t* mEnd; uint32_t* mCap;
    int a1, a2;
    char cmp; char pad[3];
    PairPB insert(const uint32_t& v);          // 0x00554020
};
struct Variant {
    uint32_t data; uint32_t pad[3];
    uint16_t flags; uint16_t typeId;
    void SetInt(const uint32_t* v);            // 0x00427FD0
    void Destruct(int a);                      // 0x0093DB80
};
struct SerObj {                                // AchievementsSerializer (0xbc bytes)
    virtual void AddRef();
    virtual void Release();
    char pad[0x20];
    USet set;                                  // +0x24
};
struct StreamObj { virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void* GetHandle(); };
struct Stream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual StreamObj* GetObj(); virtual void s9(); virtual void sA(); virtual void sB();
    virtual int Read(void* buf, int n);        // +0x30
};
struct MsgServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void Send(uint32_t id, void* data, int z);       // +0x14
    virtual void m6(); virtual void m7(); virtual void m8();
    virtual void Register(void* handler, uint32_t id);       // +0x24
};
MsgServer* GetServer();                        // 0x00883860
MsgServer* MessageServer();                    // 0x0067DCC0
struct VarSink { void FUN_0061FDB0(uint32_t id, Variant* v); };   // 0x0061FDB0
VarSink* FUN_0061DF20();                       // 0x0061DF20

struct Prop {
    char pad[0x12]; uint16_t typeId;
    bool*     GetBool();                       // 0x0041E920
    uint32_t* GetUInt();                       // 0x0041EA00
};
struct PropList {
    virtual void q0(); virtual void Release(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6();
    virtual char Has(uint32_t id);                      // +0x1c
    virtual void q8();
    virtual char GetProp(uint32_t id, Prop** out);      // +0x24
};
struct PropMgr {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
    virtual void r8(); virtual void r9(); virtual void rA();
    virtual char GetList(uint32_t a, uint32_t b, PropList** out);   // +0x2c
};
PropMgr* PropertyManager();                    // 0x0067DE30

struct KeyVec { uint32_t* mBegin; uint32_t* mEnd; uint32_t* mCap; };
struct KeyBase { virtual ~KeyBase() {} };
struct KeyList : KeyBase {
    uint32_t type, group;
    KeyVec   keys;
    uint32_t extra[2];
    KeyList() { keys.mBegin = 0; keys.mEnd = 0; keys.mCap = 0; type = 0xb1b104; group = 0x5befd27; }
    ~KeyList() { if (keys.mBegin && ((int*)keys.mBegin)[-1]) EAFree(keys.mBegin); }
};
struct FileMgr {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
    virtual void f8(); virtual void f9(); virtual void fA(); virtual void fB();
    virtual void fC(); virtual void fD();
    virtual int GetKeys(KeyVec* out, KeyList* filter, int a);   // +0x38
};
FileMgr* GetFileMgr();                         // 0x008DE1A0

struct VarListSer {
    int buf[0x285];
    VarListSer(void* owner, void* a, uint32_t b);   // 0x00692F90
    char Serialize(Stream* s);                      // 0x00693E10
};
int ReadInt32(void* handle, int* out, int count, int endian);   // 0x0093A780

struct Controller {
    virtual void v00(int);           // +0x00
    virtual void v01(int);
    virtual void v02(int);
    virtual void v03(int);
    virtual void v04(int);
    virtual void v05(int);
    virtual void v06(int);
    virtual void v07(int);
    virtual void v08(int);
    virtual void v09(int);
    virtual void v0A(int);

    SmartObj* mpNotifier;            // +0x04
    SerObj*   mpSer;                 // +0x08
    VMap      map;                   // +0x0c
    char      mFlag24;               // +0x24
    char      mPad25[0x83];

    __declspec(noinline) Rec*  FUN_00676660(uint32_t id);
    __declspec(noinline) int   FUN_006766E0(uint32_t id);
    __declspec(noinline) void  FUN_006766F0(uint32_t id);
    __declspec(noinline) char  AwardAchievement(uint32_t id);
    __declspec(noinline) char  FUN_00676810(Stream* s);
    __declspec(noinline) void  FUN_006768B0(Stream* s, uint32_t ver);
    __declspec(noinline) char  ParsePropFiles();
    __declspec(noinline) char  Init();                       // 0x00676C80
    __declspec(noinline) void  AutoTest(uint32_t id, int n);
    __declspec(noinline) void  FUN_00676ED0(uint32_t id, uint32_t bits, char on);
    __declspec(noinline) void  DecrementAccumulatorValue();  // 0x00676F20
    __declspec(noinline) void  FUN_00676F60(int* msg);
    char  FUN_00677140(uint32_t id, uint32_t arg);
    __forceinline void OrBits(uint32_t id, uint32_t bits)
    {
        if (!mFlag24) {
            Rec* r = FUN_00676660(id);
            r->value |= bits;
            if (r->f0 && FUN_006751C0(r))
                AwardAchievement(id);
        }
    }

    char  FUN_00675700(uint32_t id);    // 0x00675700
    char  FUN_006751C0(Rec* r);         // 0x006751C0
    char  FUN_006754D0();               // 0x006754D0
    void  FUN_00675ED0();               // 0x00675ED0
};

Controller* __fastcall FUN_006763E0(Controller* p);   // 0x006763E0 (ctor)
Entry* LowerBoundEntry(Entry* b, Entry* e, const Entry* k, char c);   // 0x00E23EE0 cdecl
struct VMapIns { Entry* insert(Entry* pos, const Entry* v); };         // 0x00676370 (thiscall)
uint32_t* LowerBoundU32(uint32_t* b, uint32_t* e, const uint32_t& v, char c);   // 0x00555A20 cdecl

extern Controller* g_pController;          // 0x015FC250

// @ 0x00676660
Rec* Controller::FUN_00676660(uint32_t id)
{
    Entry key;
    key.key = id;
    Controller* t = this;
    if (!FUN_00675700(id))
        t = (Controller*)mpSer;
    VMap* v = &t->map;
    Entry* end = v->mEnd;
    Entry* e = LowerBoundEntry(v->mBegin, end, &key, v->cmp);
    if (e == end || id < e->key)
        e = ((VMapIns*)v)->insert(e, &key);
    return &e->rec;
}

// @ 0x006766E0
int Controller::FUN_006766E0(uint32_t id)
{
    return FUN_00676660(id)->threshold;
}

// @ 0x006766F0
void Controller::FUN_006766F0(uint32_t id)
{
    FUN_006751C0(FUN_00676660(id));
}

// @ 0x00676710
char Controller::AwardAchievement(uint32_t id)
{
    SerObj* d = mpSer;
    uint32_t key = id;
    uint32_t* begin = d->set.mBegin;
    uint32_t* end = d->set.mEnd;
    uint32_t* found = LowerBoundU32(begin, end, key, d->set.cmp);
    if (found == end || id < *found)
        found = end;
    if (!mFlag24) {
        char ok = d->set.insert(id).ok;
        if (ok) {
            if (found == end) {
                MsgServer* srv = GetServer();
                if (srv)
                    srv->Send(0x5c6930e, &id, 0);
            }
            VarSink* v = FUN_0061DF20();
            if (v) {
                Variant var;
                var.flags = 0;
                var.typeId = 0;
                var.SetInt(&id);
                v->FUN_0061FDB0(0x1edc82b0, &var);
                if (var.flags & 4)
                    var.Destruct(0);
            }
            FUN_006754D0();
            return ok;
        }
    }
    return 0;
}

// @ 0x00676810
static __forceinline bool ReadOk(Stream* s, void* p) { return s->Read(p, 4) == 4; }
char Controller::FUN_00676810(Stream* s)
{
    int a;
    bool ok;
    if (ReadOk(s, &a) && a == 1) {
        int id;
        while (true) {
            ok = ReadOk(s, &id);
            if (!ok || id == -1)
                return ok;
            Rec* r = FUN_00676660(id);
            int v;
            ok = ReadOk(s, &v);
            if (!ok)
                return ok;
            if (r->f1)
                r->value = v;
        }
    }
    return 0;
}

// @ 0x006768B0
void Controller::FUN_006768B0(Stream* s, uint32_t ver)
{
    Entry* e = map.mBegin;
    Entry* end = map.mEnd;
    for (; e != end; ++e)
        if (e->rec.f1)
            e->rec.value = 0;
    mFlag24 = 0;
    if (ver >= 0x230001) {
        int v;
        s->Read(&v, 4);
        mFlag24 = v != 0;
    }
    FUN_00676810(s);
}

// ParsePropFiles helpers
static __forceinline bool GetBoolProp(PropList* pl, uint32_t id, Prop** pp)
{
    bool r = false;
    Prop* p = *pp;
    if (pl && pl->GetProp(id, pp) && (p = *pp)->typeId == 1)
        r = *p->GetBool();
    return r;
}
static __forceinline uint32_t GetUIntProp(PropList* pl, uint32_t id, Prop** pp)
{
    uint32_t r = 0;
    Prop* p = *pp;
    if (pl && pl->GetProp(id, pp) && (p = *pp)->typeId == 10)
        r = *p->GetUInt();
    return r;
}

// @ 0x00676A20
char Controller::ParsePropFiles()
{
    PropMgr* mgr = PropertyManager();
    FileMgr* fm = GetFileMgr();
    KeyList list;
    Prop *pa, *pb, *pc, *pd;
    if (fm && fm->GetKeys(&list.keys, &list, 0)) {
        uint32_t* it = list.keys.mBegin;
        uint32_t* end = list.keys.mEnd;
        if (it != end) {
            do {
                uint32_t k = *it;
                PropList* pl = 0;
                if (mgr->GetList(k, 0x5befd27, &pl)) {
                    if (pl->Has(0x5bef2bb)) {
                        bool b = GetBoolProp(pl, 0x5bef2bb, &pa);
                        unsigned char* fb = (unsigned char*)FUN_00676660(k);
                        unsigned c = *fb;
                        if (b)
                            c |= 1;
                        else
                            c &= ~1u;
                        *fb = (unsigned char)c;
                    }
                    if (pl->Has(0x5bef2cd)) {
                        bool b = GetBoolProp(pl, 0x5bef2cd, &pb);
                        unsigned char* fb = (unsigned char*)FUN_00676660(k);
                        unsigned c = *fb;
                        if (b)
                            c |= 2;
                        else
                            c &= ~2u;
                        *fb = (unsigned char)c;
                    }
                    if (pl->Has(0x5bef2f7)) {
                        uint32_t v = GetUIntProp(pl, 0x5bef2f7, &pc);
                        FUN_00676660(k)->f8 = v;
                    }
                    if (pl->Has(0x5bef305)) {
                        uint32_t v = GetUIntProp(pl, 0x5bef305, &pd);
                        FUN_00676660(k)->threshold = v;
                    }
                }
                if (pl)
                    pl->Release();
                it += 3;
            } while (it != end);
        }
    }
    return 1;
}

struct CmdBase { CmdBase(); virtual void Execute(void* args) = 0; char pad[8]; };
struct Args {
    char HasFlag(const char* s);               // 0x008380B0
    char HasArgument(const char* s);           // 0x00837EE0
    char** OptionArguments(const char* s, int n);   // 0x00838330
};
struct cAchievementsTestCheat : CmdBase {
    virtual void Execute(void* args);          // 0x00676FC0
};
void* CheatManager();                          // 0x0067DE20
struct NotifierObj : SmartObj {
    void Setup();                              // 0x005FE050
};
void* __fastcall FUN_005FDEB0(void* p);        // ctor (thiscall)
void FUN_0067CBE0(void* p);                    // cdecl
void* __fastcall FUN_00675D70(void* p);        // Serializer ctor (thiscall)

// @ 0x00676C80
char Controller::Init()
{
    void* mem = EAAllocate(0xbc, "AchievementsSerializer", 0, 0, 0, 0);
    SerObj* d;
    if (mem)
        d = (SerObj*)FUN_00675D70(mem);
    else
        d = 0;
    SerObj* old = mpSer;
    if (d != old) {
        if (d)
            d->AddRef();
        mpSer = d;
        if (old)
            old->Release();
    }
    if (!ParsePropFiles()) {
        SerObj* x = mpSer;
        if (x) {
            mpSer = 0;
            x->Release();
        }
        return 0;
    }
    FUN_00675ED0();
    CheatManager();
    void* cm = EAAllocate(0x10, "AchievementsTestCheat", 0, 0, 0, 0);
    if (cm)
        new (cm) cAchievementsTestCheat;
    MsgServer* srv = GetServer();
    srv->Register(this, 0x212d3e7);
    srv->Register(this, 0x238de9c);
    srv->Register(this, 0x4bef1e3);
    srv->Register(this, 0x9421c619);
    void* nm = EAAllocate(0x64, "UI/AchievementNotifier", 0, 0, 0, 0);
    NotifierObj* n;
    if (nm)
        n = (NotifierObj*)FUN_005FDEB0(nm);
    else
        n = 0;
    SmartObj* oldn = mpNotifier;
    if (n != oldn) {
        if (n)
            n->o1();
        mpNotifier = n;
        if (oldn)
            oldn->o2();
    }
    ((NotifierObj*)mpNotifier)->Setup();
    FUN_0067CBE0(mpNotifier);
    VarSink* v = FUN_0061DF20();
    if (v) {
        uint32_t* it = mpSer->set.mBegin;
        uint32_t* end = mpSer->set.mEnd;
        if (it != end) {
            do {
                Variant var;
                var.data = *it;
                var.typeId = 10;
                var.flags = 0;
                v->FUN_0061FDB0(0x1edc82b0, &var);
                if (var.flags & 4)
                    var.Destruct(0);
                ++it;
            } while (it != end);
        }
    }
    return 1;
}

// @ 0x00676E40
void FUN_00676E40()
{
    Controller* p = (Controller*)EAAllocate(0xa8, "Pollinator", 0, 0, 0, 0);
    if (p)
        p = FUN_006763E0(p);
    else
        p = 0;
    g_pController = p;
    char c = g_pController->Init();
    if (!c && g_pController) {
        g_pController->v00(1);
    }
}

// @ 0x00676E90
void Controller::AutoTest(uint32_t id, int n)
{
    if (!mFlag24) {
        Rec* r = FUN_00676660(id);
        r->value += n;
        if (r->f0 && FUN_006751C0(r))
            AwardAchievement(id);
    }
}

// @ 0x00676ED0
void Controller::FUN_00676ED0(uint32_t id, uint32_t bits, char on)
{
    if (!mFlag24) {
        Rec* r = FUN_00676660(id);
        if (on)
            r->value |= bits;
        else
            r->value &= ~bits;
        if (r->f0 && FUN_006751C0(r))
            AwardAchievement(id);
    }
}

// @ 0x00676F20
void Controller::DecrementAccumulatorValue()
{
    if (!mFlag24) {
        Rec* r = FUN_00676660(0xa3434a32);
        r->value++;
        if (r->f0 && FUN_006751C0(r))
            AwardAchievement(0xa3434a32);
        mFlag24 = 1;
    }
}

// @ 0x00676F60
void Controller::FUN_00676F60(int* pmsg)
{
    int msg[3];
    msg[0] = pmsg[0]; msg[1] = pmsg[1]; msg[2] = pmsg[2];
    if (msg[1] == 0x366a930d && !mFlag24) {
        Rec* r = FUN_00676660(0xcccf91a1);
        r->value++;
        if (r->f0 && FUN_006751C0(r))
            AwardAchievement(0xcccf91a1);
    }
}

// @ 0x00676FC0
void cAchievementsTestCheat::Execute(void* argsv)
{
    Args* args = (Args*)argsv;
    uint32_t id = 0x5c030ce;
    if (args->HasFlag("cheater"))
        MessageServer()->Send(0x4bef1e3, 0, 0);
    if (args->HasArgument("give")) {
        char** p = args->OptionArguments("give", 1);
        if (p)
            id = strtoul(*p, 0, 16);
        g_pController->AwardAchievement(id);
        return;
    }
    if (args->HasArgument("ui")) {
        Entry* it = g_pController->map.mBegin;
        Entry* end = g_pController->map.mEnd;
        MsgServer* srv = GetServer();
        if (it != end) {
            do {
                if (srv) {
                    uint32_t k = it->key;
                    srv->Send(0x5c6930e, &k, 0);
                }
                ++it;
            } while (it != end);
        }
        return;
    }
    if (args->HasArgument("guid")) {
        char** p = args->OptionArguments("guid", 1);
        if (p)
            id = strtoul(*p, 0, 10);
    }
    if (args->HasArgument("bits")) {
        char** p = args->OptionArguments("bits", 1);
        if (p) {
            g_pController->OrBits(id, strtoul(*p, 0, 10));
        }
    } else {
        g_pController->AutoTest(id, 1);
    }
}

// @ 0x00676910
struct SerOwner {
    char FUN_00676910(Stream* s);
};
static __forceinline void ReadI(Stream* s, int* out)
{
    void* h = s->GetObj()->GetHandle();
    ReadInt32(h, out, 1, 0);
}
char SerOwner::FUN_00676910(Stream* s)
{
    int tag;
    ReadI(s, &tag);
    if (tag != 1)
        return 0;
    int n;
    ReadI(s, &n);
    for (uint32_t i = 0; i < (uint32_t)n; i++) {
        int id;
        ReadI(s, &id);
        Rec* r = g_pController->FUN_00676660(id);
        ReadI(s, &r->value);
    }
    VarListSer vs(this, (void*)0x1529330, 0x1a80d26);
    return vs.Serialize(s);
}

// @ 0x00677140
char Controller::FUN_00677140(uint32_t id, uint32_t arg)
{
    switch (id) {
    case 0x4bef1e3:
        DecrementAccumulatorValue();
        return 1;
    case 0x212d3e7:
    case 0x238de9c:
        FUN_006754D0();
        return 1;
    case 0x9421c619:
        FUN_00676F60((int*)arg);
        return 1;
    default:
        break;
    }
    return 1;
}
