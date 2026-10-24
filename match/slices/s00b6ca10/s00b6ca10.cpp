// Slice s00b6ca10: FUN_00b6cde0 (VA 00b6cde0, 396 bytes, cdecl, args (P, int, float*, float), plain ret).
//
// Classifies two queries on P->mpA into a mode (-1 = none, 0..3), drives P->mpB with that mode, then
// runs the tail helpers and the string temporary's destructor.
//
// Status: calling convention of three callees (FUN_00b686a0, FUN_00b6a720) is partly register-based
// (EAX = P->vptr, EDI = P, EAX = pair pointer), which C++ cannot express; stand-ins take the stack args only.
#include "types.h"

#define P4(n) virtual void n##0(); virtual void n##1(); virtual void n##2(); virtual void n##3();

struct IMode {                       // result of P->mpA->Query(...); Mode() at +0x20
    P4(a) P4(b)
    virtual int Mode();
};
struct IQuery {                      // P->mpA; Query() at +0x0c
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual IMode* Query(uint32_t id);
};
struct IApply {                      // Query() result of P->mpB; Apply() at +0x7c
    P4(a) P4(b) P4(c) P4(d) P4(e) P4(f) P4(g)
    virtual void h0(); virtual void h1(); virtual void h2();
    virtual void Apply(int a, int b);
};
struct IObjB {                       // P->mpB; Query() at +0x0c, Notify() at +0x14
    virtual void a0(); virtual void a1(); virtual void a2();
    virtual IApply* Query(uint32_t id);
    virtual void a4();
    virtual void Notify(int mode);
};

struct cCtx {                        // P (polymorphic: P->vptr is read by the 0xb686a0 path)
    virtual void v0();
    IQuery* mpA;                     // +0x04
    uint8_t pad08[0xb4 - 0x08];
    IObjB* mpB;                      // +0xb4
};

// Helpers (cdecl: plain ret; the caller's pops are batched, so there is no add after each call).
uint32_t* FUN_00b6baf0(void* tmpStr, void* a);                    // 0x00b6baf0
void FUN_00b677e0(float* out3, void* a);                          // 0x00b677e0
float FUN_00b685e0(void* a);                                      // 0x00b685e0
int FUN_00b682a0(void* a);                                        // 0x00b682a0
int FUN_00b67b90(void* a);                                        // 0x00b67b90
char FUN_00b69010(float f, float g);                              // 0x00b69010
void FUN_00b686a0();                                              // 0x00b686a0
void FUN_00b6a720(int param2, uint32_t v, float* out3, int b1, int b2);   // 0x00b6a720

// eastl::basic_string<wchar_t>-style temporary: begin, end, capacity, allocator, then a sentinel dword.
struct TmpStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t mSentinel;
};
void operator_delete_array(void* p);                              // 0x00f47380

void FUN_00b6cde0(cCtx* p, int param2, float* param3, float param4)
{
    IMode* m1 = p->mpA ? p->mpA->Query(0xe9cb8ba) : 0;
    IMode* m2 = p->mpA ? p->mpA->Query(0x436f315) : 0;

    if (m1 || m2) {
        int mode = -1;
        int r = m1 ? m1->Mode() : m2->Mode();
        if (r > 0x1a56aba) {
            if (r == 0x436f342) mode = 0;
            else if (r == 0x70703b3) mode = 1;
        } else {
            if (r == 0x1a56aba) mode = 2;
            else if (r == 0x18ea2cc) mode = 3;
            else if (r == 0x18eb106) mode = 1;
        }
        IObjB* b = p->mpB;
        IApply* ap = b ? b->Query(0xeeee8218) : 0;
        if (mode == -1) {
            ap->Apply(1, 0);
        } else {
            ap->Apply(1, 1);
            b->Notify(mode);
        }
    }

    TmpStr str;
    float out3[3];
    uint32_t v = *FUN_00b6baf0(&str, p->mpA);
    FUN_00b677e0(out3, p->mpA);
    float f = FUN_00b685e0(p->mpA);
    int b1 = FUN_00b682a0(p->mpA);
    int b2 = FUN_00b67b90(p->mpA);
    if (!FUN_00b69010(f, param4)) {
        FUN_00b686a0();
    } else {
        FUN_00b6a720(param2, v, out3, b1, b2);
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}

// ---------------------------------------------------------------------------------------------------
// Tool-trigger handlers built on the same ResolveVar / 0xb69010 / 0xb6a720 tail.  Several callees take
// register arguments (0xb686a0: EAX = P->vptr, 0xb6a720: EDI = P, 0xb6c2d0: EAX = object,
// 0xb69460: EDI/ESI) which C++ cannot express; they are called as ordinary functions here.
// ---------------------------------------------------------------------------------------------------

uint32_t* ResolveVar(void* tmp, void* obj);                           // 0x00b6baf0
int  FUN_00b5b800(void);                                             // 0x00b5b800 GetCurrentGameMode
void FUN_00b6b1a0(void* self, void* a);                              // 0x00b6b1a0 Execute
void FUN_00b6c280(void);                                             // 0x00b6c280 RefreshUITooltips
void* FUN_00b6c2d0(void* self);                                      // 0x00b6c2d0 ShowHealthBar
void FUN_00b69460(void* self, int level);                            // 0x00b69460 SetCtxWindow
int  FUN_00b67610(int id);                                           // 0x00b67610
void* FUN_00b68aa0(void* obj, int a, float f);                       // 0x00b68aa0 sFindOrCreateUI
int  FUN_00b67c70(void* obj);                                        // 0x00b67c70
void* FUN_00b3d300(void);                                            // 0x00b3d300 SP::NounManager
void* FUN_00b3d2a0(void);                                            // 0x00b3d2a0 SP::StarManager
void* FUN_00401090(void);                                            // 0x00401090
void* FUN_00d40b40(int a);                                           // 0x00d40b40 GetDesiredAvatarHerd
void FUN_00cd7d10(void);                                             // 0x00cd7d10
void FUN_00ae7230(void);                                             // 0x00ae7230 VecTB_clear_cb
void FUN_00ae7250(void);                                             // 0x00ae7250 CollectSubsystemB
void FUN_00b1e520(void);                                             // 0x00b1e520
extern void (*PTR_FUN_013f94d4)(void);                                // 0x013f94d4
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t*);  // 0x013cc2b8

struct IProfile {                        // cSpeciesProfile subset
    uint8_t pad0[0xa4];
    void* mpAvatarProfile;               // +0xa4
};
struct ISpeciesMgr { void* GetAvatarProfile(); };                    // 0x004df420
struct IEmpire {                         // SP::cEmpire subset
    uint8_t pad0[0x50];
    uint32_t mFlags;                     // +0x50
    int GetWeaponryLevel();              // 0x00c317a0
};
struct IStarMgr { void* GetEmpireByID(int id); };                    // 0x00ba9370

struct IItem7c {                         // object at P+0x8c: Apply at +0x7c
    P4(k0) P4(k1) P4(k2) P4(k3) P4(k4) P4(k5) P4(k6)
    virtual void k70(); virtual void k74(); virtual void k78();
    virtual void Apply(int a, int b);                                // +0x7c
};

struct IUIItem {                         // Query(0xeeee8218) result: +0x28, +0x7c
    P4(l0) P4(l1)
    virtual void lA0(); virtual void lA4();
    virtual int Slot28();                                            // +0x28
    P4(l2) P4(l3) P4(l4) P4(l5) P4(l6)
    virtual void Apply(int a, int b);                                // +0x7c
};

struct IObjA {                           // P->mpA / P->mpB0: +0x0c, +0x10, +0x20, +0x4c, +0x84, +0x128
    virtual void a00(); virtual void a04(); virtual void a08();
    virtual void* Query(uint32_t id);                                // +0x0c
    virtual int a10();                                               // +0x10
    virtual void a14(); virtual void a18(); virtual void a1c();
    virtual int Mode();                                              // +0x20
    P4(b0) P4(b1)
    virtual void c44(); virtual void c48();
    virtual int Slot4c();                                            // +0x4c
    P4(d0) P4(d1)
    virtual void e70(); virtual void e74(); virtual void e78();
    virtual void Apply(int a, int b);                                // +0x7c
    virtual void f80();
    virtual void* Slot84();                                          // +0x84
    uint8_t pad88[0x128 - 0x88];
    IProfile* mpProfile;                                             // +0x128
};

struct cTool {                           // trigger context for the handlers below
    virtual void v0();                                                // +0x00
    IObjA* mpA;                                                      // +0x04
    uint8_t pad08[0x8c - 0x08];
    IItem7c* mp8c;                                                   // +0x8c
    IObjA* mp90;                                                     // +0x90
    uint8_t pad94[0xb0 - 0x94];
    IObjA* mpB0;                                                     // +0xb0
};

struct IObjB2 {                          // noun-list entry object: +0x08, +0x0c
    virtual void b00(); virtual void b04();
    virtual void* Slot08();                                          // +0x08
    virtual void* Slot0c();                                          // +0x0c
};
struct IObjData {                        // Slot08() result
    P4(c0) P4(c1) P4(c2) P4(c3)                                      // 0x00..0x3c
    virtual void c40(); virtual void c44();
    virtual bool Slot48();                                           // +0x48
    uint8_t pad4c[0x75 - 0x4c];
    uint8_t f75;                                                     // +0x75
};
struct IObjData2 {                       // Slot0c() result
    P4(d0) P4(d1) P4(d2)                                             // 0x00..0x2c
    virtual void d30(); virtual void d34();
    virtual void* Slot38();                                          // +0x38
};
struct ItEntry { void* p0; IObjB2* p4; };
struct DataVec { uint32_t pad0; IObjB2** mpBegin; IObjB2** mpEnd; };
struct cGameNounManager {                // SP::cGameNounManager subset
    void* GetGameDataVector(void (*)(), void (*)(), void (*)(), void (*)(), uint32_t);  // 0x00b21340
};

struct CTimer {                          // EA::Stopwatch subset (at *0x01687348 + 0x38)
    int64_t mStart;                      // +0x00
    int64_t mPad08;                      // +0x08 (cleared by the reset below)
    int mMode;                           // +0x10 (1 = rdtsc)
    float mRate;                         // +0x14
    int64_t GetElapsedTimeFloat();       // 0x0093a3a0
};
struct TooltipMgr {                      // singleton at 0x01687348
    uint8_t pad00[0x1c];
    float f1c;                           // +0x1c
    float f20;                           // +0x20
    uint8_t pad24[0x38 - 0x24];
    CTimer timer;                        // +0x38
    void F00b720e0();                    // 0x00b720e0
    int F00e31100();                     // 0x00e31100
    void* F00b72230(int* p);             // 0x00b72230
    void F00c2e4e0();                    // 0x00c2e4e0
};
extern TooltipMgr* s_pTooltip;            // 0x01687348

extern const float _HK_REAL_ONE;          // 0x01485720
struct IHealthBar {                      // ShowHealthBar() result
    uint8_t pad0[0x118];
    int f118;                            // +0x118
    float f11c;                          // +0x11c
};
struct IHealthOwner { IHealthBar* ShowHealthBar(); };                 // 0x00b6c2d0 (EAX-reg arg in the binary)
struct IUIElem {                         // sFindOrCreateUI() result
    uint8_t pad0[0x3c];
    float f3c;                           // +0x3c
    float f40;                           // +0x40
};

// @ 0x00b6ca10
void FUN_00b6ca10(cTool* P, char param2, int param3, float param4)
{
    FUN_00b5b800();

    IObjA* a = P->mpA;
    TmpStr str;
    float out3[3];
    uint32_t v = *ResolveVar(&str, a);
    FUN_00b677e0(out3, a);
    float f = FUN_00b685e0(a);
    int b1 = FUN_00b682a0(a);
    int b2 = FUN_00b67b90(a);

    bool ok;
    if (FUN_00b69010(f, param4)) {
        FUN_00b6a720(param2, v, out3, b1, b2);
        ok = true;
    } else {
        FUN_00b686a0();
        ok = false;
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);

    if (!ok) return;
    if (!param2) return;

    IObjA* m = P->mpA;
    bool show;
    if (m && m->Mode() == 0x52aa6122 && m->mpProfile &&
        m->mpProfile->mpAvatarProfile == ((ISpeciesMgr*)FUN_00401090())->GetAvatarProfile() &&
        m->mpProfile == FUN_00d40b40(0)) {
        show = true;
    } else {
        show = false;
    }

    P->mp8c->Apply(1, show);

    IUIItem* item = P->mp90 ? (IUIItem*)P->mp90->Query(0xeeee8218) : 0;
    bool vis = ((item->Slot28() & 1) != 0) && !show;
    item->Apply(1, vis);
}

// @ 0x00b6cba0
void FUN_00b6cba0(cTool* P, uint32_t param2, int param3, float param4)
{
    float vec[3];
    vec[0] = 0.28f;                      // 0x3e8f5c29
    vec[1] = 0.375f;                     // 0x3ec00000
    vec[2] = 0.41f;                      // 0x3ed1eb85

    TmpStr str;
    uint32_t v = *ResolveVar(&str, P->mpA);
    if (FUN_00b69010(0.0f, param4)) {
        FUN_00b6a720(param2, v, vec, 0, 0);
    } else {
        FUN_00b686a0();
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}

// @ 0x00b6cc50
void FUN_00b6cc50(cTool* P, uint32_t param2, int param3, float param4)
{
    IObjA* b = P->mpB0;
    if (b) {
        IUIItem* ap = (IUIItem*)b->Query(0xeeee8218);
        if (ap) {
            ap->Apply(1, 0);
            if (FUN_00b5b800() == 0x1654c05) {
                IObjA* m = P->mpA;
                if (m) {
                    IObjA* q = (IObjA*)m->Query(0xb033b403);
                    if (q) {
                        IEmpire* e = (IEmpire*)((IStarMgr*)FUN_00b3d2a0())->GetEmpireByID(q->Slot4c());
                        if (e && !(e->mFlags & 0x40)) {
                            int level = b->a10() - 1;
                            int maxLevel = e->GetWeaponryLevel() + 1;
                            int chosen = level < maxLevel ? level : maxLevel;
                            FUN_00b69460(P, chosen);
                            ap->Apply(1, 1);
                        }
                    }
                }
            }
        }
    }

    IObjA* a = P->mpA;
    TmpStr str;
    float out3[3];
    uint32_t v = *ResolveVar(&str, a);
    FUN_00b677e0(out3, a);
    float f = FUN_00b685e0(a);
    int b1 = FUN_00b682a0(a);
    int b2 = FUN_00b67b90(a);
    if (FUN_00b69010(f, param4)) {
        FUN_00b6a720(param2, v, out3, b1, b2);
    } else {
        FUN_00b686a0();
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}

// @ 0x00b6cf70
void FUN_00b6cf70(cTool* P, uint32_t param2, int param3, float param4)
{
    if (FUN_00b5b800() == 0x1654c05)
        FUN_00b6b1a0(P, P->mpA ? P->mpA->Query(0xee9b2232) : 0);

    IObjA* a = P->mpA;
    TmpStr str;
    float out3[3];
    uint32_t v = *ResolveVar(&str, a);
    FUN_00b677e0(out3, a);
    float f = FUN_00b685e0(a);
    int b1 = FUN_00b682a0(a);
    int b2 = FUN_00b67b90(a);
    if (FUN_00b69010(f, param4)) {
        FUN_00b6a720(param2, v, out3, b1, b2);
    } else {
        FUN_00b686a0();
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}

// @ 0x00b6d060
void FUN_00b6d060(cTool* P, uint32_t param2, int param3, float param4)
{
    if (FUN_00b5b800() == 0x1654c05) {
        IObjA* m = P->mpA;
        if (m) {
            IObjA* q = (IObjA*)m->Query(0x1007ae63);
            if (q) FUN_00b6b1a0(P, q->Slot84());
        }
    }

    IObjA* a = P->mpA;
    TmpStr str;
    float out3[3];
    uint32_t v = *ResolveVar(&str, a);
    FUN_00b677e0(out3, a);
    float f = FUN_00b685e0(a);
    int b1 = FUN_00b682a0(a);
    int b2 = FUN_00b67b90(a);
    if (FUN_00b69010(f, param4)) {
        FUN_00b6a720(param2, v, out3, b1, b2);
    } else {
        FUN_00b686a0();
    }
    if ((((int)((uint32_t)str.mpCapacity - (uint32_t)str.mpBegin)) & ~1) > 2 &&
        str.mpBegin && (uint32_t)str.mpBegin != str.mSentinel)
        operator_delete_array(str.mpBegin);
}

// @ 0x00b6d160
void FUN_00b6d160(IHealthOwner* self, int param2)
{
    IHealthBar* bar = self->ShowHealthBar();
    if (!bar) return;
    bar->f118 = param2;
    bar->f11c = _HK_REAL_ONE;
}

// @ 0x00b6d190
void FUN_00b6d190(void)
{
    if (!s_pTooltip) return;
    FUN_00b6c280();
    s_pTooltip->F00b720e0();
    TooltipMgr* p = s_pTooltip;
    if (p) {
        p->F00c2e4e0();
        operator_delete_array(p);
    }
    s_pTooltip = 0;
}

// @ 0x00b6d1d0
void FUN_00b6d1d0(uint32_t param1)
{
    CTimer* timer = &s_pTooltip->timer;
    int64_t elapsed = timer->GetElapsedTimeFloat();
    if ((float)elapsed * timer->mRate <= 25.0f) {
        int key = s_pTooltip->F00e31100();
        for (void* it = s_pTooltip->F00b72230(&key); it;
             it = s_pTooltip->F00b72230(&key)) {
            ItEntry* entry = (ItEntry*)it;
            IObjB2* b = entry->p4;
            IObjData* o = b ? (IObjData*)b->Slot0c() : 0;
            if (o->Slot48()) {
                IObjData2* u = (IObjData2*)entry->p4;
                int a = FUN_00b67c70(u);
                IUIElem* ui = (IUIElem*)FUN_00b68aa0(u, a, 0.0f);
                if (ui) {
                    ui->f40 = s_pTooltip->f1c;
                    ui->f3c = s_pTooltip->f20;
                }
            }
        }
        return;
    }

    void* nm = FUN_00b3d300();
    DataVec* dv = (DataVec*)((cGameNounManager*)nm)->GetGameDataVector(
        FUN_00cd7d10, FUN_00ae7230, FUN_00ae7250, FUN_00b1e520, (uint32_t)&PTR_FUN_013f94d4);
    IObjB2** begin = dv->mpBegin;
    IObjB2** end = dv->mpEnd;
    int count = 0;
    while (begin != end) {
        IObjB2* obj = *begin;
        IObjData* a = (IObjData*)obj->Slot08();
        IObjData2* b = (IObjData2*)obj->Slot0c();
        if (a->f75 && a->Slot48()) {
            int mask = FUN_00b67610((int)b->Slot38());
            if (mask & param1) {
                int x = FUN_00b67c70(b);
                IUIElem* ui = (IUIElem*)FUN_00b68aa0(b, x, 0.0f);
                if (ui) {
                    ui->f40 = s_pTooltip->f1c;
                    ui->f3c = s_pTooltip->f20;
                }
                count++;
            }
        }
        begin++;
        if (count >= 0x20) break;
    }

    if (timer->mMode == 1) {
        uint64_t cyc;
        __asm { rdtsc } __asm { mov dword ptr [cyc+4], edx } __asm { mov dword ptr [cyc], eax }
        timer->mStart = cyc;
        timer->mPad08 = 0;
    } else {
        int64_t now;
        QueryPerformanceCounter(&now);
        timer->mStart = now;
        timer->mPad08 = 0;
    }
}
