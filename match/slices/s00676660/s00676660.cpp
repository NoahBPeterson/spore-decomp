// Slice s00676660: SP::Achievements::Controller and related UI message handlers.
// Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
void* operator new(unsigned int, void*);

void  EAFree(void* p);                                                                    // 0x00F47380
void* EAAllocate(unsigned int n, const char* name, int a, int b, const char* file, int line); // 0x00F473A0

struct LayoutWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual unsigned v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B();
    virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B();
    virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual void SetTooltip(int, int);   // +0x7c
};

void  __fastcall FUN_00828BE0(void* pThis);   // 0x00828BE0
void  FUN_00808B20(void* a, void* b);      // 0x00808B20
void  __stdcall FUN_00599BE0(void* a);     // 0x00599BE0
void  __fastcall FUN_00599530(void* a);    // 0x00599530 (thiscall receiver)
void  __fastcall FUN_00599560(void* a);    // 0x00599560 (thiscall receiver)
struct PropertyLayout {
    void* GetRootWindow(int a);            // 0x00828100
};

// ---------------------------------------------------------------------------
// Host object owning the layout window pointers.
// ---------------------------------------------------------------------------
struct UIHost {
    char          mPad00[0x78];
    LayoutWindow* mp78;   // +0x78
    LayoutWindow* mp7c;   // +0x7c
    void*         mp80;   // +0x80
    char          mPad84[0x18];
    void*         mp9c;   // +0x9c

    void FUN_00677360(uint32_t arg);
    void FUN_00677380();
    void FUN_006773B0(void* p);
    void FUN_00677470(uint32_t arg);
    char FUN_006774C0(uint32_t arg, int* msg);
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
        FUN_00599BE0(mp9c);
        mp7c->v08();
        FUN_00599530(mp7c);
        void* root = ((PropertyLayout*)mp7c)->GetRootWindow(1);
        FUN_00808B20((void*)arg, root);
    }
}

// @ 0x006774C0
char UIHost::FUN_006774C0(uint32_t arg, int* msg)
{
    if (msg[2] == 0x1b) {
        if (msg[1]) {
            LayoutWindow* w = (LayoutWindow*)msg[1];
            if (w->v07() == 0x54f63a3e) {
                FUN_00677470((uint32_t)msg[1]);
                return 0;
            }
            FUN_006773B0((void*)msg[1]);
        }
    } else if (msg[2] == 0x1c) {
        if (mp7c)
            FUN_00599560(mp7c);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// SP::Achievements::Controller
// ---------------------------------------------------------------------------
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

    char  mPad04[0x20];
    char  mFlag24;                   // +0x24
    char  mPad25[0x57];

    char  Init();                       // 0x00676C80
    char  FUN_006754D0();               // 0x006754D0
    void  DecrementAccumulatorValue();  // 0x00676F20
    void  AwardAchievement(uint32_t id); // 0x00676710
    void  FUN_00676F60(uint32_t a);     // 0x00676F60
    char  FUN_00677140(uint32_t id, uint32_t arg);
};

Controller* __fastcall FUN_006763E0(Controller* p);   // 0x006763E0 (ctor)
Controller* FUN_00676660(uint32_t id);     // 0x00676660

extern Controller* g_pController;          // 0x015FC250

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
        FUN_00676F60(arg);
        return 1;
    default:
        break;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// Remaining functions: skeletons.
// ---------------------------------------------------------------------------
// @ 0x00676660
void FUN_00676660_() {}
// @ 0x006766E0
void FUN_006766E0() {}
// @ 0x006766F0
void FUN_006766F0() {}
// @ 0x00676710
void FUN_00676710() {}
// @ 0x00676810
void FUN_00676810() {}
// @ 0x006768B0
void FUN_006768B0() {}
// @ 0x00676910
void FUN_00676910() {}
// @ 0x00676A20
void FUN_00676A20() {}
// @ 0x00676C80
void FUN_00676C80() {}
// @ 0x00676E90
void FUN_00676E90() {}
// @ 0x00676ED0
void FUN_00676ED0() {}
// @ 0x00676F20
void FUN_00676F20() {}
// @ 0x00676F60
void FUN_00676F60() {}
// @ 0x00676FC0
void FUN_00676FC0() {}
// @ 0x00677190
void FUN_00677190() {}
// @ 0x00677220
void FUN_00677220() {}
// @ 0x006773B0
void UIHost::FUN_006773B0(void* p) { (void)p; }
// @ 0x00677530
void FUN_00677530() {}
