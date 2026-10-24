// Slice s00b6d3c0 -- 0x00b6d3c0 (2056 bytes): per-frame dispatcher over the world-label event queue.
// It walks every pending queue entry that is armed (+0x50) and, by the kind of the object the entry refers to
// (FUN_00b67c70 -> 0..16), hands the entry's position/flag, the object's name and a few of its properties to
// one of 12 per-kind handlers (spawn a floating label / marker for that kind).  Names are Claude-coined.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

#define PV(n) virtual void pv##n();

// ---- object interfaces reached through vf+0xc (QueryInterface-like: Cast(id)) ----
struct SubD {                                                   // embedded at ObjD+0x34
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32)
    virtual float V51();                                        // +0xcc
};
struct ObjD {                                                   // id 0x0137e8e0
    int pad_vptr;
    char pad04[0x34 - 4];
    SubD mSub;                                                  // +0x34
    char pad38[0xb1c - 0x38];
    int mY1;                                                    // +0xb1c
    int mY2;                                                    // +0xb20
    float FUN_00c9f330();                                       // 0x00c9f330
};
struct ObjA {                                                   // id 0x0116d858
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual int V22();                                          // +0x58
};
struct ObjC {                                                   // id 0xce9f6639 (creature)
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual bool V53();                                         // +0xd4
};
struct ObjB {                                                   // id 0x4f176642
    int FUN_00c22dc0();                                         // 0x00c22dc0
};
struct IWinObj;                                                 // a tooltip/label window (see below)
struct Obj {                                                    // the thing a queue entry refers to
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t id);                            // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsLabelAlive();                                // +0x2c
};

void __cdecl EA_Free(void* p);                                    // 0x00f47380 (operator delete[])

// ---- eastl::fixed_string<wchar_t, 35>: begin/end/cap, allocator pad, 36-wchar buffer ----
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      pad;
    wchar_t  mBuffer[36];
    ~WString() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin && mpBegin != mBuffer)
            EA_Free(mpBegin);
    }
};

// ---- empire colour ----
struct cEmpire { Vec3 GetColor(); };                            // 0x00c32cd0 (sret, ret 4)
cEmpire* GetPlayerEmpire();                                     // 0x01021300 (cdecl)

struct Event {
    int mKey;                                                   // +0x00
    Obj* mpObj;                                                 // +0x04
    char mFlag;                                                 // +0x08
    float mX;                                                   // +0x0c
    float mY;                                                   // +0x10
    char pad14[4];
    float mLimitY;                                              // +0x18
    char pad1c[0x50 - 0x1c];
    int mArmed;                                                 // +0x50
    IWinObj* mpWin54;                                           // +0x54
    IWinObj* mpWin58;                                           // +0x58
    char pad5c[0x70 - 0x5c];
    IWinObj* mpWin70;                                           // +0x70
    char pad74[0x90 - 0x74];
    Obj* mpField90;                                             // +0x90
    char pad94[0xb8 - 0x94];
    IWinObj* mpLayout;                                          // +0xb8
    IWinObj* mpWinBC;                                           // +0xbc
    char padC0[0x120 - 0xc0];
    IWinObj* mpWin120;                                          // +0x120
    char pad124[4];
    int mState128;                                              // +0x128
};

struct Mgr {
    char pad00[0x38];
    int f38, f3c;
    char pad40[0x50 - 0x40];
    int f50;                                                    // +0x50
    Event* FUN_00b72230(int* cookie);                           // 0x00b72230 (thiscall, next entry)
};
extern Mgr* g_pMgr;                                             // 0x01687348

extern const Vec3 kLabelColor;                                  // 0x0156b008
extern const wchar_t kEmptyStr[];                               // 0x013ec468

void  FUN_00b6d1d0(int a);                                      // 0x00b6d1d0 (cdecl)
int   FUN_00e31100();                                           // 0x00e31100 (cdecl, GetPriority)
unsigned FUN_00b67c70(Obj* o);                                  // 0x00b67c70 (cdecl, kind 0..16)
int   FUN_00b67b90(Obj* o);                                     // 0x00b67b90 (cdecl)
int   FUN_00b681d0(Obj* o);                                     // 0x00b681d0 (cdecl)
int   FUN_00b68250(Obj* o);                                     // 0x00b68250 (cdecl)
int   FUN_00b682a0(Obj* o);                                     // 0x00b682a0 (cdecl)
float FUN_00b685e0(Obj* o);                                     // 0x00b685e0 (cdecl)
Vec3  FUN_00b677e0(Obj* o);                                     // 0x00b677e0 (cdecl, sret)
WString FUN_00b6baf0(Obj* o);                                   // 0x00b6baf0 (cdecl, sret)

// per-kind handlers (the first group takes the entry in EAX in the original: approximated as arg 1)
bool FUN_00b6a970(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, Vec3 col, int a, int b, float dt);   // 0x00b6a970
void FUN_00b6a9d0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6a9d0
void FUN_00b6adf0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6adf0
void FUN_00b6b0a0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6b0a0
void FUN_00b6aae0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6aae0
void FUN_00b6abc0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, float f1, float f2, int c, int d, float dt);   // 0x00b6abc0
void FUN_00b6cc50(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cc50
void FUN_00b6c870(Event* e, int flag, const Vec2* pos, bool b, float dt);   // 0x00b6c870
void FUN_00b6cde0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cde0
void FUN_00b6cf70(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cf70
void FUN_00b6d060(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6d060
void FUN_00b6ca10(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6ca10
void FUN_00b6cba0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cba0
#undef PV

// @ 0x00b6d3c0
void ProcessLabelEvents(float dt)
{
    if (g_pMgr->f38 || g_pMgr->f3c) FUN_00b6d1d0(g_pMgr->f50);
    int cookie = FUN_00e31100();
    for (Event* e = g_pMgr->FUN_00b72230(&cookie); e; e = g_pMgr->FUN_00b72230(&cookie)) {
        if (!e->mArmed) continue;
        char flag = e->mFlag;
        Vec2 pos;
        pos.x = e->mX;
        pos.y = e->mY;
        switch (FUN_00b67c70(e->mpObj)) {
        case 13: {
            Obj* o = e->mpObj;
            FUN_00b6a970(e, flag, &pos, 0.0f, L"Food Pile", FUN_00b677e0(o), FUN_00b682a0(o), 0, dt);
            break;
        }
        case 0:
            FUN_00b6a970(e, flag, &pos, 0.0f, kEmptyStr, kLabelColor, 0, 0, dt);
            break;
        case 10: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6a970(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, GetPlayerEmpire()->GetColor(),
                         FUN_00b67b90(o), 0, dt);
            break;
        }
        case 2: {
            Obj* o = e->mpObj;
            int a = 0;
            if (o) {
                ObjA* r = (ObjA*)o->Cast(0x116d858);
                a = r ? r->V22() : 0;
            }
            WString name = FUN_00b6baf0(e->mpObj);
            FUN_00b6a9d0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), a,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 4: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6adf0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 5: {
            Obj* o = e->mpObj;
            WString name = FUN_00b6baf0(o);
            FUN_00b6b0a0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), dt);
            break;
        }
        case 3: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            Obj* o = e->mpObj;
            int b = 0;
            if (o) {
                ObjB* r = (ObjB*)o->Cast(0x4f176642);
                b = r ? r->FUN_00c22dc0() : 0;
            }
            WString name = FUN_00b6baf0(e->mpObj);
            FUN_00b6aae0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), b,
                         FUN_00b682a0(o), FUN_00b67b90(o), bv, dt);
            break;
        }
        case 6: {
            Obj* o = e->mpObj;
            ObjD* d1 = o ? (ObjD*)o->Cast(0x137e8e0) : 0;
            float x1 = d1 ? d1->mSub.V51() : 0.0f;
            ObjD* d2 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            float x2 = d2 ? d2->FUN_00c9f330() : 0.0f;
            ObjD* d3 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y1 = d3 ? d3->mY1 : 0;
            ObjD* d4 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y2 = d4 ? d4->mY2 : -1;
            Obj* oe = e->mpObj;
            WString name = FUN_00b6baf0(oe);
            FUN_00b6abc0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(oe), y2, y1, x2, x1,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 11:
            FUN_00b6cc50(e, flag, &pos, dt);
            break;
        case 12: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            FUN_00b6c870(e, flag, &pos, bv, dt);
            break;
        }
        case 9:
            FUN_00b6cde0(e, flag, &pos, dt);
            break;
        case 7:
            FUN_00b6cf70(e, flag, &pos, dt);
            break;
        case 8:
            FUN_00b6d060(e, flag, &pos, dt);
            break;
        case 14:
            FUN_00b6ca10(e, flag, &pos, dt);
            break;
        case 16:
            FUN_00b6cba0(e, flag, &pos, dt);
            break;
        case 1:
        case 15:
            break;
        }
    }
}

// ---------------------------------------------------------------------------------------------------
// 0x00b6dbd0 .. 0x00b6e2d0: the per-frame pass over the UI context records of the label system (retire
// dead contexts, re-anchor the live ones' label windows and scroll them into the visible area), the
// ring-buffer slot helpers and the var-list save helper of the same manager.  Names are Claude-coined.
// ---------------------------------------------------------------------------------------------------

#define PVCAT(a, b) a##b
#define PVCAT2(a, b) PVCAT(a, b)
#define PVQ virtual void PVCAT2(pvq_, __COUNTER__)();
#define PVQ8 PVQ PVQ PVQ PVQ PVQ PVQ PVQ PVQ

struct IHostObj;

struct IWinObj {                                                // a label/tooltip window of a context record
    PVQ PVQ PVQ PVQ
    virtual IHostObj* GetHost();                                // +0x10
    PVQ PVQ PVQ PVQ PVQ
    virtual int V0A();                                          // +0x28
    PVQ PVQ PVQ
    virtual float* GetPos();                                    // +0x38
    PVQ8 PVQ PVQ PVQ PVQ PVQ
    virtual void SetPos(float x, float y);                      // +0x70
};

struct IHostObj {                                               // the host of a label window
    PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ PVQ
    virtual void V3A(IWinObj* w);                               // +0xe8
};

struct IWindowMgr {
    PVQ8 PVQ8 PVQ8 PVQ8 PVQ
    virtual int V21();                                          // +0x84
};

struct CTriggerMgr {
    char pad00[0x2c];
    int mMode;                                                  // +0x2c
};

struct CState {
    bool ShouldShow();                                          // 0x00e18c70
};

void* GetTriggerMgr();                                          // 0x00b3d4d0 (cdecl)
IWindowMgr* WindowManager();                                    // 0x0067caa0 (cdecl)
void* CommManager();                                            // 0x00b3d4a0 (cdecl)
bool CommManagerIsActive();                                     // 0x00ae9390 (thiscall, ecx = CommManager())
void* FUN_00b3d3f0(int a);                                      // 0x00b3d3f0 (cdecl)
void FUN_00b6c200(int key);                                     // 0x00b6c200 (cdecl, RemoveUICtx)
void FUN_00b686a0(int key);                                     // 0x00b686a0 (key in EAX originally)
void FUN_00b6a610(Event* e);                                    // 0x00b6a610 (cdecl)
void FUN_00b6c710(float dt);                                    // 0x00b6c710 (cdecl, UpdateUIContexts)
void FUN_00b69890();                                            // 0x00b69890 (cdecl)
void AnchorWindowToWindow(IWinObj* win, IWinObj* base, int mode, IWinObj* p4);   // 0x00807340
float* SPUIHelpers_GetBoundingScreenRect(float* out, IWinObj* win, char flag);   // 0x00808d20

// @ 0x00b6dbd0
void FUN_00b6dbd0(float dt)
{
    // retire the contexts whose label died, drop the slots of the ones that cannot be shown any more
    int cookie = FUN_00e31100();
    for (Event* e = g_pMgr->FUN_00b72230(&cookie); e != 0; e = g_pMgr->FUN_00b72230(&cookie)) {
        if (e->mpObj->IsLabelAlive()) {
            FUN_00b6c200(e->mKey);
            continue;
        }
        if (e->mArmed) {
            int mode = ((CTriggerMgr*)GetTriggerMgr())->mMode;
            if (mode == 1 || mode == 2
                || WindowManager()->V21() != 0
                || CommManagerIsActive()
                || ((CState*)FUN_00b3d3f0(0))->ShouldShow())
                FUN_00b686a0(e->mKey);
        }
        if (e->mArmed) {
            FUN_00b6a610(e);
        }
        else if (e->mpLayout == 0 && e->mpWin120 == 0) {
            FUN_00b6c200(e->mKey);
        }
        else {
            FUN_00b6a610(e);
        }
    }

    ProcessLabelEvents(dt);
    FUN_00b6c710(dt);
    FUN_00b69890();

    // anchor the label windows of the live records
    cookie = FUN_00e31100();
    Event* e;
    while ((e = g_pMgr->FUN_00b72230(&cookie)) != 0) {
        if (!e->mFlag)
            continue;
        if (e->mArmed) {
            if (e->mpWin120 != 0 && e->mState128 == 2) {
                IWinObj* base = e->mpWin58;
                if (base == 0)
                    base = e->mpWin70;
                if (base != 0)
                    AnchorWindowToWindow(e->mpWin120, base, 0x102, e->mpWin54);
                float* pos = e->mpWin54->GetPos();
                e->mpWin54->SetPos(pos[0], pos[1] - 12.0f);
            }
            if (e->mpLayout != 0) {
                IWinObj* target = 0;
                if (e->mpField90 != 0)
                    target = (IWinObj*)e->mpField90->Cast(0xeeee8218);
                e->mpWinBC->GetHost()->V3A(e->mpWinBC);
                if (target != 0) {
                    if ((target->V0A() & 1) != 0)
                        AnchorWindowToWindow(target, e->mpWinBC, 0x220, 0);
                    else
                        AnchorWindowToWindow(target, e->mpWinBC, 0x300, 0);
                }
                else if (e->mpWin58 != 0 && (e->mpWin58->V0A() & 1) != 0) {
                    AnchorWindowToWindow(e->mpWin58, e->mpWinBC, 0x102, 0);
                }
                else if (e->mpWin70 != 0 && (e->mpWin58->V0A() & 1) != 0) {
                    AnchorWindowToWindow(e->mpWin70, e->mpWinBC, 0x102, 0);
                }
            }
        }
        else if (e->mpLayout != 0 && e->mpWin120 != 0 && e->mpWinBC != 0 && e->mState128 == 2) {
            AnchorWindowToWindow(e->mpWin120, e->mpWinBC, 0x102, 0);
        }
    }

    // scroll the visible records so their label windows stay inside the screen
    cookie = FUN_00e31100();
    while ((e = g_pMgr->FUN_00b72230(&cookie)) != 0) {
        if (!e->mFlag)
            continue;
        float off;
        if (e->mpLayout != 0) {
            float rect[4];
            SPUIHelpers_GetBoundingScreenRect(rect, e->mpWinBC, 0);
            off = 20.0f - rect[2];
        }
        else if (e->mArmed != 0) {
            float rect[4];
            SPUIHelpers_GetBoundingScreenRect(rect, e->mpWin58, 0);
            off = 20.0f - rect[2];
        }
        else {
            if (e->mpWin120 == 0)
                continue;
            float rect[4];
            SPUIHelpers_GetBoundingScreenRect(rect, e->mpWin120, 0);
            off = 20.0f - rect[2];
        }
        if (off > 0.0f) {
            float y = e->mY + off;
            float over = y - e->mLimitY;
            if (over > 0.0f) {
                off -= over;
                y -= over;
            }
            e->mY = y;
            if (e->mArmed != 0 && e->mpWin54 != 0) {
                float* pos = e->mpWin54->GetPos();
                e->mpWin54->SetPos(pos[0], pos[1] + off);
            }
            if (e->mpLayout != 0 && e->mpWinBC != 0) {
                float* pos = e->mpWinBC->GetPos();
                e->mpWinBC->SetPos(pos[0], pos[1] + off);
            }
            if (e->mpWin120 != 0) {
                float* pos = e->mpWin120->GetPos();
                e->mpWin120->SetPos(pos[0], pos[1] + off);
            }
        }
    }
}

// ---- ring buffer of the 12 UI slot ids (0x53dbcf3 .. 0x53dbcfe) ----
extern uint32_t g_slot01687968;                                 // 0x01687968 (last handed out slot id)
extern char g_slots0168795c[];                                  // 0x0168795c (occupied flags, 12 entries)

struct SimState {                                               // the simulator's global state object
    char pad00[0x28];
    int mField28;                                               // +0x28
    int mField2c;                                               // +0x2c
    int mField30;                                               // +0x30
};
extern SimState* g_pSimState;                                   // 0x01687978
extern int g_flag0156b0cc;                                      // 0x0156b0cc
extern int g_dataset0156b0d8;                                   // 0x0156b0d8

// One ring step: advance the slot id (wrapping at the last slot) and leave if the reached slot is free.
#define NEXT_SLOT(cur)                                                   \
    do {                                                                 \
        ++(cur);                                                         \
        g_slot01687968 = (cur);                                          \
        int index;                                                       \
        if ((cur) > 0x53dbcfe) {                                         \
            (cur) = 0x53dbcf3;                                           \
            g_slot01687968 = (cur);                                      \
            index = (int)((cur) - 0x53dbcf3);                            \
        }                                                                \
        else if ((cur) >= 0x53dbcf3) {                                   \
            index = (int)((cur) - 0x53dbcf3);                            \
        }                                                                \
        else {                                                           \
            index = 0;                                                   \
        }                                                                \
        if (g_slots0168795c[index] == 0)                                 \
            return;                                                      \
    } while (0)

// @ 0x00b6e050
void FUN_00b6e050()
{
    uint32_t cur = g_slot01687968;
    if (cur < 0x53dbcf3)
        cur = 0x53dbcf2;
    int remaining = 12;
    do {
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        remaining -= 6;
    } while (remaining > 0);
}

// @ 0x00b6e1e0
char FUN_00b6e1e0(int index)
{
    return g_slots0168795c[index];
}

struct cSimUIObject {
    void* GetInterface(uint32_t id);                            // 0x00b6e210
};

// @ 0x00b6e210
void* cSimUIObject::GetInterface(uint32_t id)
{
    void* result = 0;
    if (id == 0x5593a1a)
        result = this;
    return result;
}

// @ 0x00b6e250
int FUN_00b6e250()
{
    if (g_pSimState != 0 && g_flag0156b0cc != 0)
        return 1;
    return 0;
}

// @ 0x00b6e270
int FUN_00b6e270(int value)
{
    int old = g_pSimState->mField28;
    g_pSimState->mField28 = value;
    return old;
}

// @ 0x00b6e290
int FUN_00b6e290(int value)
{
    int old = g_pSimState->mField2c;
    g_pSimState->mField2c = value;
    return old;
}

// @ 0x00b6e2b0
int FUN_00b6e2b0(int value)
{
    int old = g_pSimState->mField30;
    g_pSimState->mField30 = value;
    return old;
}

// ---- saving: the record id goes out as a Uint32, then the whole record through a var-list serializer ----
struct IStreamObj {
    PVQ PVQ PVQ PVQ PVQ PVQ
    virtual void* V6();                                         // +0x18
};

struct IStreamHost {
    PVQ8
    virtual IStreamObj* V8();                                   // +0x20
};

struct cVarListSerializer {                                     // 0xa14-byte serializer, built on the stack
    uint8_t mData[0xa14];
    void Init(void* owner, void* dataset, uint32_t tag);         // 0x00692f90
    void Serialize(void* obj);                                  // 0x00692900
};

namespace EA { namespace IO {
void WriteUint32(void* stream, const uint32_t* value, int count, int mode);   // 0x0093aa70
} }

struct cSimulatorUIStore {
    void Save(IStreamHost* owner);                              // 0x00b6e2d0
};

// @ 0x00b6e2d0
void cSimulatorUIStore::Save(IStreamHost* owner)
{
    IStreamObj* streamObj = owner->V8();
    uint32_t id = 0x5593a1a;
    void* stream = streamObj->V6();
    EA::IO::WriteUint32(stream, &id, 1, 0);
    cVarListSerializer ser;
    ser.Init(this, &g_dataset0156b0d8, 0x1a80d26);
    ser.Serialize(owner);
}
