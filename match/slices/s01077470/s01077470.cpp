// Slice s01077470 (worker 9) -- the space-trading UI panel block at 0x01077470.
//   SP::cSPUISpaceTrading::FUN_01077470 / FUN_01077550   (scrolling frames)
//   ::FUN_01077630 (panel construction), ::FUN_01077830, ::FUN_01077860
//   (cell <-> element mapping), ::FUN_01077900 / FUN_01077960 / FUN_01077990
//   (inventory hooks), ::FUN_010779e0 (teardown), FUN_01077ae0 (FindUIWindow),
//   FUN_01077b40, ::FUN_01077b70 / FUN_01077bf0 / FUN_01077ce0 (row update),
//   ::FUN_01077d30 (visibility refresh), ::FUN_01077e20 (scroll-bar flags) and
//   the four cdecl vector-copy helpers FUN_01077f10 / FUN_01077f70 /
//   FUN_01077fb0 / FUN_01078000 / FUN_01078060.
//
// None of these carry real PDB names; the FUN_ names are the caller-scored
// candidates.  vftable dispatch goes through the VTSLOT macro (slot dispatch is
// the accepted convention here).  Engine entry points are modelled as named
// collaborators.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;

struct Obj;

#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void  (__thiscall *Fn_v_pii)(void*, int, int);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, int);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_ppi)(void*, void*, int);
typedef void  (__thiscall *Fn_v_ppp)(void*, void*, void*);
typedef void  (__thiscall *Fn_v_pf)(void*, float);
typedef void  (__thiscall *Fn_v_pff)(void*, float, float);
typedef Obj*  (__thiscall *Fn_p_p)(void*);
typedef Obj*  (__thiscall *Fn_p_pi)(void*, int);
typedef Obj*  (__thiscall *Fn_p_pii)(void*, int, int);
typedef Obj*  (__thiscall *Fn_p_pp)(void*, void*);
typedef Obj*  (__thiscall *Fn_p_ppp)(void*, void*, void*);
typedef bool  (__thiscall *Fn_b_p)(void*);
typedef bool  (__thiscall *Fn_b_pp)(void*, void*);

// ---- engine data globals ----------------------------------------------------
extern "C" u32 DAT_015b9550 = 0;    // 0x015b9550  tooltip window id
extern "C" u32 DAT_015b9554 = 0;    // 0x015b9554  tooltip layout id
extern "C" u32 DAT_015b9558 = 0;    // 0x015b9558  tooltip style id
extern "C" float DAT_013eb1bc = -1.0f;  // 0x013eb1bc  OUT OF RANGE (spatial id)
extern "C" int DAT_0149c5c4[3] = {0, 0, 0}; // 0x0149c5c4  NPC message list
extern "C" int DAT_0149c608[3] = {0, 0, 0}; // 0x0149c608  user message list

// ---- collaborator objects ---------------------------------------------------
// A 12-byte element of the cSPUISpaceTrading cell vector at +0x30.
struct cScrollElem {
    void* mpObj;         // +0x00
    float mField4;       // +0x04
    u8    mByte8;        // +0x08
    u8    mPad9[3];
};

// The window list returned by cSPUILayout::GetObjects (begin/end).
struct cObjVec {
    Obj** begin;         // +0x00
    Obj** end;           // +0x04
};

struct cSPUILayout {
    cObjVec* GetObjects();                  // 0x008100c0
    Obj*     FindWindowByID(int id, int flag); // 0x008105b0
};

// Embedded tooltip window controller at cSPUISpaceTrading+0x50.
struct cUITimedTooltip {
    u8   mPad00[0x30];
    char Init(u32 a1, u32 a2, u32 a3, u32 a4, int a5, int a6); // 0x00e36b30
    Obj* FindWindow(int id, bool flag);                          // 0x00e36650
};

struct cPlayerInventory {
    void* FUN_00ff3f00();        // 0x00ff3f00  currently shown item
    void  FUN_00ff4540(void* p); // 0x00ff4540
    void  FUN_00ff4470(void* p); // 0x00ff4470
};

struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();  // 0x00a1ad60
};

struct cTerrainEditor {
    bool  FUN_00c772c0(int id);     // 0x00c772c0
    void  FUN_00c77bf0(int id);     // 0x00c77bf0
    Obj*  GetCurrentTerrainSphere(); // 0x00f67d90
};

struct cSPSpaceTrading {
    void* CreateNPCInventory();     // 0x0103e8e0
};

struct cSporeItem {
    void* FUN_0106edc0();           // 0x0106edc0
};

struct TradeCtl {
    void* FUN_0067aaf0();           // 0x0067aaf0
};

struct TradeId  { u32 a, b, c; };
struct TradePos { float x, y, z; };

// ---- engine entry points ----------------------------------------------------
void* __cdecl FUN_00807600(const wchar_t* name, void* pOut, int flag); // 0x00807600
bool  __cdecl FUN_00807690(void* p, int flag);                         // 0x00807690
Obj*  __cdecl SP_GetActivePlanet();                                    // 0x01021260
Obj*  __cdecl SP_MessageServer();                                      // 0x0067dcc0
void* __cdecl SP_NounManager();                                        // 0x00b3d300
Obj*  __cdecl SP_SpaceGameGet();                                       // 0x01002bd0
void* __stdcall FUN_00b3d3d0(void* a, void* b);                        // 0x00b3d3d0
void* __cdecl FUN_0067caf0(TradeId ids, int a, int b, TradePos pos, int c, int d); // 0x0067caf0
void  __cdecl EA_Messaging_RemoveHandler(void*, void*, void*, void*, void*); // 0x00571db0
void  __cdecl EA_Locale_SetNumberString(int value, int a, char* buf, int len); // 0x00881ae0

namespace SP {

// The space-trading UI panel.  Field offsets recovered from this slice.
struct cSPUISpaceTrading {
    u8    mPad00[0x0c];
    void* mpField0C;             // +0x00c  message-handler target (&mField0C)
    void* mpField10;             // +0x010  NPC scroll container
    void* mpScroll14;            // +0x014  NPC scroll frame (FUN_01077470)
    void* mpOwner18;             // +0x018  NPC scroll frame owner slot
    void* mpField1C;             // +0x01c  user scroll container
    void* mpField20;             // +0x020  user scroll frame (FUN_01077550)
    void* mpField24;             // +0x024  user scroll frame owner slot
    void* mpField28;             // +0x028
    void* mpField2C;             // +0x02c  window collection
    cScrollElem* mpVec30;        // +0x030  cell vector begin
    cScrollElem* mpVecEnd34;     // +0x034  cell vector end
    u8    mPad38[0x50 - 0x38];
    cUITimedTooltip mTooltip;    // +0x050
    u32   mField80;              // +0x080  layout tag (0x120ad1fb)
    u32   mPad84;
    int   mField88;              // +0x088  divisor
    int   mField8C;              // +0x08c  divisor
    u32   mPad90;
    float mField94;              // +0x094  cell pitch x
    float mField98;              // +0x098  cell pitch y
    u8    mByte9C;               // +0x09c  "use window index" flag
    u8    mPad9D[0xac - 0x9d];
    float mFieldAC;              // +0x0ac  tooltip row height (empty)
    float mFieldB0;              // +0x0b0  tooltip row height
    float mFieldB4;              // +0x0b4  cell width
    float mFieldB8;              // +0x0b8  cell height
    float mFieldBC;              // +0x0bc
    float mFieldC0;              // +0x0c0
    u8    mPadC4[0xe0 - 0xc4];
    float mFieldE0;              // +0x0e0  scroll extent (x)
    float mFieldE4;              // +0x0e4  scroll extent (y)
    u8    mByteE8;               // +0x0e8  NPC panel visible
    u8    mByteE9;               // +0x0e9  user panel visible
    u8    mPadEA[2];
    void* mpHandlerEC;           // +0x0ec  registered message handler
    void* mArgsF0[4];            // +0x0f0  handler arguments
    union {
        struct { void* h; void* a1; void* a2; void* a3; void* a4; } mBlk100;
        struct { u32 p0; u32 p1; void* h; void* a1; void* a2; void* a3; void* a4; } mBlk108;
    };
    u8    mByte11C;              // +0x11c
    u8    mByte11D;              // +0x11d
    u16   mPad11E;
    int   mField120;             // +0x120
    u32   mPad124;
    void* mpHandler128;          // +0x128  registered message handler
    void* mArgs12C[4];           // +0x12c  handler arguments

    void  Init();                          // 0x01076180
    void  SetMidPanel();                   // 0x010755d0
    void  FUN_01076a00();                  // 0x01076a00
    void  FUN_01076a60();                  // 0x01076a60
    void* FUN_010666a0(void* p);           // 0x010666a0
    void* FUN_0106edc0(void* p);           // 0x0106edc0 (on FUN_010666a0 result)

    void  FUN_01077470();
    void  FUN_01077550();
    void  FUN_01077630();
    bool  FUN_01077830(void* p);
    int   FUN_01077860(float a, float b);
    u8    FUN_01077900(void* p);
    u32   FUN_01077960(void* p);
    void  FUN_01077990(void* p);
    void  FUN_010779e0();
    bool  FUN_01077b70(void* a1, u32* pOut);
    void  FUN_01077bf0(void* a1);
    void  FUN_01077ce0(void* a1);
    void  FUN_01077d30();
    void  FUN_01077e20();
};

}  // namespace SP

// 0x01077ae0  SP::`anonymous namespace'::FindUIWindow
u32 __stdcall FUN_01077ae0(cSPUILayout* layout);

// 0x01077b40  plain helper, __cdecl
u32 __cdecl FUN_01077b40(void* p);

// ============================================================================
// @ 0x01077470 SP::cSPUISpaceTrading::FUN_01077470
// Rebuild the NPC scrolling frame (owner slot +0x18, frame +0x14).
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077470()
{
    if (mpOwner18 != 0) {
        Obj* old = (Obj*)mpOwner18;
        mpOwner18 = 0;
        ((Fn_v_p)VTSLOT(old, 4))(old);
    }
    Obj* nw = (Obj*)FUN_00807600(L"ScrollFrameVerticalGeneric", &mpOwner18, 1);
    Obj* prev = (Obj*)mpScroll14;
    if (nw != prev) {
        if (nw != 0)
            ((Fn_v_p)VTSLOT(nw, 0))(nw);
        mpScroll14 = nw;
        if (prev != 0)
            ((Fn_v_p)VTSLOT(prev, 4))(prev);
    }
    if (((Fn_p_p)VTSLOT(mpScroll14, 0x10))(mpScroll14) != 0) {
        Obj* t = ((Fn_p_p)VTSLOT(mpScroll14, 0x10))(mpScroll14);
        ((Fn_v_pp)VTSLOT(t, 0xdc))(t, mpScroll14);
    }
    ((Fn_v_pp)VTSLOT(mpField10, 0xd8))(mpField10, mpScroll14);
    Obj* child = ((Fn_p_p)VTSLOT(mpField10, 0x38))(mpField10);
    ((Fn_v_pp)VTSLOT(mpScroll14, 0x60))(mpScroll14, child);
    ((Fn_v_pff)VTSLOT(mpScroll14, 0x64))(mpScroll14, 0.0f, 0.0f);
    FUN_01076a00();
    FUN_00807690(mpScroll14, 0);
}

// ============================================================================
// @ 0x01077550 SP::cSPUISpaceTrading::FUN_01077550
// The user-scrolling twin of FUN_01077470 (owner slot +0x24, frame +0x20).
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077550()
{
    if (mpField24 != 0) {
        Obj* old = (Obj*)mpField24;
        mpField24 = 0;
        ((Fn_v_p)VTSLOT(old, 4))(old);
    }
    Obj* nw = (Obj*)FUN_00807600(L"ScrollFrameVerticalGeneric", &mpField24, 1);
    Obj* prev = (Obj*)mpField20;
    if (nw != prev) {
        if (nw != 0)
            ((Fn_v_p)VTSLOT(nw, 0))(nw);
        mpField20 = nw;
        if (prev != 0)
            ((Fn_v_p)VTSLOT(prev, 4))(prev);
    }
    if (((Fn_p_p)VTSLOT(mpField20, 0x10))(mpField20) != 0) {
        Obj* t = ((Fn_p_p)VTSLOT(mpField20, 0x10))(mpField20);
        ((Fn_v_pp)VTSLOT(t, 0xdc))(t, mpField20);
    }
    ((Fn_v_pp)VTSLOT(mpField1C, 0xd8))(mpField1C, mpField20);
    Obj* child = ((Fn_p_p)VTSLOT(mpField1C, 0x38))(mpField1C);
    ((Fn_v_pp)VTSLOT(mpField20, 0x60))(mpField20, child);
    ((Fn_v_pff)VTSLOT(mpField20, 0x64))(mpField20, 0.0f, 0.0f);
    FUN_01076a60();
    FUN_00807690(mpField20, 0);
}

// ============================================================================
// @ 0x01077630 SP::cSPUISpaceTrading::FUN_01077630
// Panel construction: builds both scrolling frames, wires the message handler
// and starts the NPC/terrain trading query.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077630()
{
    u8 local[0x14];
    Obj* planet = SP_GetActivePlanet();
    ((cUITimedTooltip*)&mTooltip)->Init(DAT_015b9550, DAT_015b9554, DAT_015b9558,
                                        0x5fd4ce0, 200, 0xfa);
    Obj* w = ((cUITimedTooltip*)&mTooltip)->FindWindow(0x51a37b8, true);
    float* r = (float*)((Fn_p_p)VTSLOT(w, 0x38))(w);
    mFieldB0 = r[2] - r[0];
    Init();
    mByte11C = 1;
    mField120 = -1;
    mByte11D = 0;
    cSPSpaceTrading* inv =
        (cSPSpaceTrading*)FUN_00b3d3d0(*(void**)((char*)planet + 0x13c), local);
    inv->CreateNPCInventory();
    FUN_01077550();
    FUN_01077470();
    SetMidPanel();
    Obj* ms = SP_MessageServer();
    ((Fn_v_piii)VTSLOT(ms, 0x14))(ms, 0x4c70cc0, 0, 0);
    void* target = &mpField0C;
    Obj* ms2 = SP_MessageServer();
    mBlk108.h = ms2;
    mBlk108.a1 = target;
    mBlk108.a2 = (void*)DAT_0149c5c4;
    mBlk108.a3 = (void*)3;
    mBlk108.a4 = 0;
    if (ms2 != 0 && target != 0) {
        u8* ids = (u8*)DAT_0149c5c4;
        for (u32 o = 0; o < 0xc; o += 4)
            ((Fn_v_ppi)VTSLOT(ms2, 0x24))(ms2, target, *(int*)(ids + o));
    }
    cTerrainEditor* te = (cTerrainEditor*)SP_NounManager();
    Obj* ts = te->GetCurrentTerrainSphere();
    if (ts != 0) {
        if (te->FUN_00c772c0(0x670c73c) == false) {
            te->FUN_00c77bf0(0x670c73c);
            TradeId ids;
            ids.a = 0x8af87c97;
            ids.b = 0xb1b104;
            ids.c = 0x3629f036;
            TradePos pos;
            pos.x = -1.0f;
            pos.y = -1.0f;
            pos.z = 0.0f;
            TradeCtl* t = (TradeCtl*)FUN_0067caf0(ids, 0, 0, pos, 0, 0);
            t->FUN_0067aaf0();
        }
    }
}

// ============================================================================
// @ 0x01077830 SP::cSPUISpaceTrading::FUN_01077830
// Is the object behind p the current NPC container?
// ============================================================================
bool SP::cSPUISpaceTrading::FUN_01077830(void* p)
{
    int local[3];
    Obj* r = ((Fn_p_pp)VTSLOT(p, 0x38))(p, local);
    return *(void**)r == mpField10;
}

// ============================================================================
// @ 0x01077860 SP::cSPUISpaceTrading::FUN_01077860
// Map a local (x,y) inside a cell to a flat element index.
// ============================================================================
int SP::cSPUISpaceTrading::FUN_01077860(float a, float b)
{
    int xi = (int)(__int64)(a / (mFieldB4 + mField94));
    int yi = (int)(__int64)(b / (mFieldB8 + mField98));
    if (mField80 == 0x120ad1fb)
        return mField88 * yi + xi;
    return mField8C * xi + yi;
}

// ============================================================================
// @ 0x01077900 SP::cSPUISpaceTrading::FUN_01077900
// Toggle an object's inventory entry (returns the object's flag byte).
// ============================================================================
u8 SP::cSPUISpaceTrading::FUN_01077900(void* p)
{
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)SP_SpaceGameGet())->GetPlayerInventory();
    if (inv != 0) {
        if (((Fn_b_p)VTSLOT(p, 0x40))(p)) {
            if (*(u8*)((char*)p + 0x28) != 0)
                inv->FUN_00ff4540(p);
            else
                inv->FUN_00ff4470(p);
        }
    }
    return *(u8*)((char*)p + 0x28);
}

// ============================================================================
// @ 0x01077960 SP::cSPUISpaceTrading::FUN_01077960
// Is p the inventory's currently selected item?
// ============================================================================
u32 SP::cSPUISpaceTrading::FUN_01077960(void* p)
{
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)SP_SpaceGameGet())->GetPlayerInventory();
    if (inv != 0) {
        if (inv->FUN_00ff3f00() == p)
            return 1;
    }
    return 0;
}

// ============================================================================
// @ 0x01077990 SP::cSPUISpaceTrading::FUN_01077990
// Forward window slot 0x48 on p.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077990(void* p)
{
    ((Fn_v_p)VTSLOT(p, 0x48))(p);
}

// ============================================================================
// @ 0x010779e0 SP::cSPUISpaceTrading::FUN_010779e0
// Teardown: deactivate, unregister both message handlers and release the
// child windows.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_010779e0()
{
    ((Fn_v_p)VTSLOT(this, 0x28))(this);

    void* h = mpHandlerEC;
    if (h != 0) {
        mpHandlerEC = 0;
        EA_Messaging_RemoveHandler(h, mArgsF0[0], mArgsF0[1], mArgsF0[2], mArgsF0[3]);
    }
    void* h2 = mBlk100.h;
    if (h2 != 0) {
        mBlk100.h = 0;
        EA_Messaging_RemoveHandler(h2, mBlk100.a1, mBlk100.a2, mBlk100.a3, mBlk100.a4);
    }
    if (mpField1C != 0) {
        Obj* x = (Obj*)mpField1C;
        mpField1C = 0;
        ((Fn_v_p)VTSLOT(x, 8))(x);
    }
    if (mpField20 != 0) {
        Obj* x = (Obj*)mpField20;
        mpField20 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField24 != 0)
        ((Fn_v_pp)VTSLOT(mpField24, 0x108))(mpField24, this);
    if (mpField28 != 0 && mpField2C != 0)
        ((Fn_v_pp)VTSLOT(mpField28, 0xe0))(mpField28, mpField2C);
    if (mpField24 != 0) {
        Obj* x = (Obj*)mpField24;
        mpField24 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField28 != 0) {
        Obj* x = (Obj*)mpField28;
        mpField28 = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
    if (mpField2C != 0) {
        Obj* x = (Obj*)mpField2C;
        mpField2C = 0;
        ((Fn_v_p)VTSLOT(x, 4))(x);
    }
}

// ============================================================================
// @ 0x01077ae0 FUN_01077ae0   (__stdcall) -- SP::`anonymous namespace'::FindUIWindow
// ============================================================================
u32 __stdcall FUN_01077ae0(cSPUILayout* layout)
{
    u32 ret = 0;
    if (layout == 0)
        return ret;
    cObjVec* vec = layout->GetObjects();
    Obj** cur = vec->begin;
    Obj** end = vec->end;
    while (cur != end) {
        u32 v = 0;
        if (*cur != 0)
            v = (u32)((Fn_p_pi)VTSLOT(*cur, 0xc))(*cur, 0xeeee8218);
        if (v != 0) {
            ret = v;
            break;
        }
        ++cur;
    }
    return ret;
}

// ============================================================================
// @ 0x01077b40 FUN_01077b40   (__cdecl)
// Two-stage window lookup.
// ============================================================================
u32 __cdecl FUN_01077b40(void* p)
{
    Obj* a = ((Fn_p_pi)VTSLOT(p, 0xb4))(p, 0x600db9c);
    if (a != 0)
        return (u32)((Fn_p_pi)VTSLOT(a, 0xc))(a, 0x707459dd);
    return 0;
}

// ============================================================================
// @ 0x01077b70 SP::cSPUISpaceTrading::FUN_01077b70
// Resolve the element index of the window behind a1.
// ============================================================================
bool SP::cSPUISpaceTrading::FUN_01077b70(void* a1, u32* pOut)
{
    bool bRet = false;
    if (mByte9C != 0) {
        *pOut = *(u32*)((char*)a1 + 0x24);
        bRet = true;
    } else {
        void* item = ((cSporeItem*)FUN_010666a0(a1))->FUN_0106edc0();
        Obj* r = ((Fn_p_ppp)VTSLOT(mpField2C, 0xf0))(mpField2C, item, 0);
        if (r != 0) {
            float* v = (float*)((Fn_p_p)VTSLOT(r, 0x38))(r);
            float f[2];
            f[0] = v[0];
            f[1] = v[1];
            *pOut = (u32)FUN_01077860(f[0], f[1]);
            bRet = true;
        }
    }
    return bRet;
}

// ============================================================================
// @ 0x01077bf0 SP::cSPUISpaceTrading::FUN_01077bf0
// Refresh the tooltip row that follows the window behind a1.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077bf0(void* a1)
{
    int local;
    void* item = ((cSporeItem*)FUN_010666a0(a1))->FUN_0106edc0();
    Obj* a = ((Fn_p_ppp)VTSLOT(mpField2C, 0xf0))(mpField2C, item, 0);
    if (a == 0)
        return;
    Obj* b = ((Fn_p_ppp)VTSLOT(a, 0xf0))(a, (void*)0x5f72e19, 0);
    if (b == 0)
        return;
    if (((Fn_b_pp)VTSLOT((void*)a1, 0x3c))((void*)a1, &local) == false) {
        ((Fn_v_pii)VTSLOT(b, 0x7c))(b, 1, 0);
        return;
    }
    char buf[0x20];
    EA_Locale_SetNumberString(local, 0, buf, 0x20);
    ((Fn_v_pp)VTSLOT(b, 0x80))(b, buf);
    if (local == 0)
        ((Fn_v_pf)VTSLOT(b, 0x5c))(b, mFieldB0);
    else
        ((Fn_v_pf)VTSLOT(b, 0x5c))(b, mFieldAC);
    ((Fn_v_pii)VTSLOT(b, 0x7c))(b, 1, 1);
}

// ============================================================================
// @ 0x01077ce0 SP::cSPUISpaceTrading::FUN_01077ce0
// Clear the element picked by the window behind a1.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077ce0(void* a1)
{
    if (FUN_01077b70(a1, (u32*)&a1)) {
        cScrollElem* e = mpVec30 + (u32)a1;
        if (e->mByte8 == 0) {
            void* p = e->mpObj;
            e->mByte8 = 1;
            if (p != 0) {
                e->mpObj = 0;
                ((Fn_v_p)VTSLOT(p, 8))(p);
            }
            e->mField4 = 0.0f;
        }
    }
}

// ============================================================================
// @ 0x01077d30 SP::cSPUISpaceTrading::FUN_01077d30
// Refresh cell visibility and (un)register the user-panel message handler.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077d30()
{
    cScrollElem* cur = mpVec30;
    cScrollElem* end = mpVecEnd34;
    while (cur != end) {
        if (cur->mpObj != 0) {
            Obj* w = ((cSPUILayout*)cur->mpObj)->FindWindowByID(0x62840d8, 1);
            if (w != 0)
                ((Fn_v_pii)VTSLOT(w, 0x7c))(w, 1, mByteE9);
        }
        ++cur;
    }
    if (mByteE8 != 0 && mByteE9 != 0) {
        void* target = &mpField0C;
        Obj* ms = SP_MessageServer();
        mpHandler128 = ms;
        mArgs12C[0] = target;
        mArgs12C[1] = (void*)DAT_0149c608;
        mArgs12C[2] = (void*)3;
        mArgs12C[3] = 0;
        if (ms != 0 && target != 0) {
            u8* ids = (u8*)DAT_0149c608;
            for (u32 o = 0; o < 0xc; o += 4)
                ((Fn_v_ppi)VTSLOT(ms, 0x24))(ms, target, *(int*)(ids + o));
        }
    } else {
        void* h = mpHandler128;
        if (h != 0) {
            mpHandler128 = 0;
            EA_Messaging_RemoveHandler(h, mArgs12C[0], mArgs12C[1], mArgs12C[2], mArgs12C[3]);
        }
    }
}

// ============================================================================
// @ 0x01077e20 SP::cSPUISpaceTrading::FUN_01077e20
// Push the scroll-bar limit flags to both scrolling frames.
// ============================================================================
void SP::cSPUISpaceTrading::FUN_01077e20()
{
    float* v = (float*)((Fn_p_p)VTSLOT(mpField2C, 0x38))(mpField2C);
    float a = v[0];
    float b = v[1];
    float c = v[2];
    float d = v[3];
    bool flag1 = true;
    bool flag2 = true;
    if (mField80 == 0x120ad1fb) {
        if (!(mFieldE4 > (mFieldC0 - (d - b))))
            flag1 = false;
        if (!(0.0f > mFieldE4))
            flag2 = false;
    } else {
        if (!(mFieldE0 > (mFieldBC - (c - a))))
            flag1 = false;
        if (!(0.0f > mFieldE0))
            flag2 = false;
    }
    Obj* w1 = ((Fn_p_ppp)VTSLOT(mpField24, 0xf0))(mpField24, (void*)0x5f72d7c, (void*)1);
    if (w1 != 0)
        ((Fn_v_pii)VTSLOT(w1, 0x7c))(w1, 1, flag1);
    Obj* w2 = ((Fn_p_ppp)VTSLOT(mpField24, 0xf0))(mpField24, (void*)0x5f72d8a, (void*)1);
    if (w2 != 0)
        ((Fn_v_pii)VTSLOT(w2, 0x7c))(w2, 1, flag2);
}

// ============================================================================
// @ 0x01077f10 FUN_01077f10   (__cdecl) -- fill [first,last) through the output
// cursor *pOut and return the cursor object.
// ============================================================================
cScrollElem** __cdecl FUN_01077f10(cScrollElem** pOut, cScrollElem* first,
                                   cScrollElem* last, cScrollElem* value)
{
    *pOut = value;
    while (first != last) {
        cScrollElem* d = *pOut;
        if (d != 0) {
            void* p = first->mpObj;
            d->mpObj = p;
            if (p != 0)
                ((Fn_v_p)VTSLOT(p, 4))(p);
            d->mField4 = first->mField4;
            d->mByte8 = first->mByte8;
        }
        ++(*pOut);
        ++first;
    }
    return pOut;
}

// ============================================================================
// @ 0x01077f70 FUN_01077f70   (__cdecl) -- fill count elements
// ============================================================================
void __cdecl FUN_01077f70(cScrollElem* dst, u32 count, cScrollElem* src)
{
    cScrollElem* p = dst;
    for (; 0 < count; --count, ++p) {
        if (p != 0) {
            void* q = src->mpObj;
            p->mpObj = q;
            if (q != 0)
                ((Fn_v_p)VTSLOT(q, 4))(q);
            p->mField4 = src->mField4;
            p->mByte8 = src->mByte8;
        }
    }
}

// ============================================================================
// @ 0x01077fb0 FUN_01077fb0   (__cdecl) -- copy a range
// ============================================================================
cScrollElem* __cdecl FUN_01077fb0(cScrollElem* first, cScrollElem* last,
                                  cScrollElem* dst)
{
    if (first != last) {
        do {
            if (dst != 0) {
                void* p = first->mpObj;
                dst->mpObj = p;
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mField4 = first->mField4;
                dst->mByte8 = first->mByte8;
            }
            ++first;
            ++dst;
        } while (first != last);
    }
    return dst;
}

// ============================================================================
// @ 0x01078000 FUN_01078000   (__cdecl) -- assign a range (addref/release pair)
// ============================================================================
cScrollElem* __cdecl FUN_01078000(cScrollElem* first, cScrollElem* last,
                                  cScrollElem* dst)
{
    if (first != last) {
        do {
            void* p = first->mpObj;
            void* q = dst->mpObj;
            if (p != q) {
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mpObj = p;
                if (q != 0)
                    ((Fn_v_p)VTSLOT(q, 8))(q);
            }
            dst->mField4 = first->mField4;
            dst->mByte8 = first->mByte8;
            ++first;
            ++dst;
        } while (first != last);
    }
    return dst;
}

// ============================================================================
// @ 0x01078060 FUN_01078060   (__cdecl) -- reverse-assign a range
// ============================================================================
cScrollElem* __cdecl FUN_01078060(cScrollElem* first, cScrollElem* last,
                                  cScrollElem* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            void* p = last->mpObj;
            void* q = dst->mpObj;
            if (p != q) {
                if (p != 0)
                    ((Fn_v_p)VTSLOT(p, 4))(p);
                dst->mpObj = p;
                if (q != 0)
                    ((Fn_v_p)VTSLOT(q, 8))(q);
            }
            dst->mField4 = last->mField4;
            dst->mByte8 = last->mByte8;
        } while (last != first);
    }
    return dst;
}