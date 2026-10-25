// Slice s00ecda80 (bfs3 slice 23) -- SP editor palette/swatch UI + scenario helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---- vtable call helpers (__thiscall in a cast is legal; free __thiscall decls are not)
#define C0(p, off)      ((void(__thiscall*)(void*))(((void**)(p))[(off) / 4]))(p)
#define C1(p, off, a)   ((void(__thiscall*)(void*, int))(((void**)(p))[(off) / 4]))(p, a)
#define C2(p, off, a, b) ((void(__thiscall*)(void*, int, int))(((void**)(p))[(off) / 4]))(p, a, b)
#define C3(p, off, a, b, c) ((void(__thiscall*)(void*, int, int, int))(((void**)(p))[(off) / 4]))(p, a, b, c)
#define K0(p, off)      ((int(__thiscall*)(void*))(((void**)(p))[(off) / 4]))(p)
#define K1(p, off, a)   ((int(__thiscall*)(void*, int))(((void**)(p))[(off) / 4]))(p, a)
#define P1(p, off, a)   ((void*(__thiscall*)(void*, int))(((void**)(p))[(off) / 4]))(p, a)
// object -> vtable -> slot (the macros above index the object itself)
#define VTB(p, off)     (*(void***)(p))[(off) / 4]

// ---- stub types for thiscall callees / manager globals (fix pass)
struct FindWindowStub { void* FindWindowByID(int id, int flags); };  // 0x008105b0
struct LookupOwner    { int* FUN_00f3e8a0(int id); };               // 0x00f3e8a0
struct PropObj        { int* GetFloat(); };                          // 0x0041ea70
struct PaletteStore   { void Set(int obj, float v); };               // 0x005f0c60
struct CastObj        { int Cast(int id); };                         // 0x00ecde00
struct SelObj_ecdb50  { void Set(int v); };                          // __thiscall, 1 stack arg
struct WinObj_ece110  { void Activate(int arg); };                   // __thiscall, 1 stack arg
struct CastObj_ece370 { int Cast(int id); };                         // __thiscall, 1 stack arg
struct ColorStore     { void Set(float v); void FUN_007a4c80(int mode); void FUN_005f49a0(int mode); };  // 0x005f22f0 / 0x007a4c80 / 0x005f49a0
// The 0x007a4c80 helper's argument arrives in EAX (a register convention), so
// the idiomatic member call is modelled as a static helper.
static inline ColorStore* __cdecl PaletteTarget(void* obj)
{
    return (ColorStore*)((int(__thiscall*)(void*, int))VTB(obj, 0xc))(obj, 0x3349c94);
}
struct Mgr167eaec     { int* Fn_b1de80(); };                         // 0x00b1de80
struct GameMgr_16c7aa4 { char pad0[0x74]; LookupOwner* pOwner_74; };
extern GameMgr_16c7aa4* g_pGameMgr_16c7aa4;   // 0x016c7aa4
extern PaletteStore* g_pPaletteStore_15d0c08; // 0x015d0c08
int* __cdecl FUN_00401020_get();              // 0x00401020
int* __cdecl FUN_00b3d320_get();              // 0x00b3d320
void __fastcall FUN_00834e30_tc(void* self);  // 0x00834e30
void __fastcall FUN_00ecde60_tc(void* self);  // 0x00ecde60

// ---- globals
extern int* g_15ad298;       // PTR_PTR_015ad298
extern int* g_15abf0c;       // PTR_DAT_015abf0c
extern int* g_15abf1c;       // PTR_DAT_015abf1c
extern float g_15abee4;      // DAT_015abee4
extern float g_13ec468;      // DAT_013ec468
extern char vtbl_BakeSprites[];
extern char vtbl_cSPScenarioSwatchItemUI[];
extern char vtbl_PaintSystem[];
extern char vtbl_cEditorResource[];
extern char vtbl_cContentValidationSummarizer[];

// ---- callees
int* __cdecl GetSystemAT();
int* __cdecl FUN_00efc910();
void __cdecl FUN_00f00380(int a);
int* __cdecl SP_MessageServer();
int  __cdecl FUN_00eece20(int a);
bool __cdecl FUN_005f3060();
void __cdecl FUN_00805fe0(void* out, int a);
bool __cdecl FUN_00efc9c0();
void __cdecl FUN_005f4750();
void __cdecl FUN_00401020();
int* __cdecl FUN_0113ae10();
int* __cdecl SP_WindowManager();
void __cdecl cSPUIPropertyLayout_SetPositionAndOffset(void* self, float a, float b, float c, float d);
void __cdecl FUN_005c6c50();
int  __cdecl FUN_005c6a30();
int* __cdecl EA_Messaging_GetServer();
void __cdecl SP_cSPPaletteItemUI_Shutdown();
void __cdecl cSPUILayout_Shutdown(void* self, int a);
void __cdecl FUN_005f0a60(int a);
void __cdecl FUN_005f0ca0(void* a);
void __cdecl FUN_00ecde60();
void __cdecl FUN_005c6c50_v();
void __cdecl FUN_005f22f0(int a);
int* __cdecl cSPUILayout_FindWindowByID2(void* l, int id);
void __cdecl FUN_00807bb0(void* w, void* v, int a);   // 0x00807bb0 SPUIHelpers_SetWindowImage
void __cdecl FUN_008068d0(int a, int b, int c);
void __cdecl FUN_00ece140(int a);
void __cdecl FUN_00efbbe0(int a, int b);
void __cdecl SP_cSPPaletteItemUI_DoMessage(void* self, int* msg, int a);
void __cdecl FUN_00834e30();
void __cdecl SPUIHelpers_VisitWindowTreeDepthFirst(int a, void* f, int b);
void __cdecl FUN_00ecd9c0();
int  __cdecl FUN_00f3e8a0(int a);
int  __cdecl FUN_00ecda00(void* obj);   // 0x00ecda00 (its argument arrives in EAX)
void* __cdecl FUN_008de1a0();           // 0x008de1a0 global object getter
void __cdecl FUN_005f0c60(int a, int b);
int* __fastcall FUN_01137690(void* self);   // 0x01137690
void* __fastcall FUN_005f33f0(void* self);  // 0x005f33f0
int  __cdecl FUN_005ff1c0();
void __cdecl FUN_00ecda80(int a);
void __cdecl EA_LimitStopwatch_SetTimeLimit(void* self, int a, int b);
int* __cdecl FUN_00b1de80();
void __cdecl FUN_00b3d320();
int* __cdecl SP_GetPropertyAsFloat();
struct LimitStopwatch { char pad[8]; };
void __cdecl FUN_006a1400(int* a, int b, void* c);
void __cdecl FUN_00ef0b80();
void __cdecl SP_cSPPaletteItemUI_ctor(void* self);
void __cdecl FUN_005f7380();

// ---- rework stubs (0x00ecde00 .. 0x00ece4d0) -------------------------------
struct CastBase        { int FUN_005c6a30(int id); };                    // 0x005c6a30 helper on the +0x28 sub-object
struct PaletteMessage  { char pad00[8]; int32_t mKind08; char pad0c[0x0c]; int32_t mValue18; };
struct SysAT_15ad328   { void FUN_00f00380(int reason); };               // 0x00f00380, object at 0x015ad328
struct MsgSink         { void FUN_00efbbe0(int a, int b); };             // 0x00efbbe0
struct PaletteMgr      { char pad00[0xd4]; MsgSink* mpSink_d4; };        // view of the 0x016c7aa4 manager
struct PaletteItemBase { void DoMessage(void* msg, PaletteMessage* data); };  // 0x005c6d70 base handler
struct PaletteItemUI_ece200 { void DoMessage(void* msg, PaletteMessage* data); };
struct ColorSource     { char pad00[0x18]; int32_t mRgb[3]; };           // +0x18 colour triple
struct PaletteItem_ece010 {
    char         pad00[0x48];
    ColorSource* mpColorSource_48;   // +0x48  colour triple owner
    char         pad4c[0x50 - 0x4c];
    void*        mpLayout_50;        // +0x50  UI layout that owns the preview window
    void SetColors(int* rgb, bool highlight);
};
struct PaletteSwatch_ece140 {
    char  pad00[0x4c];
    void* mpTarget_4c;               // +0x4c  palette target object
    char  pad50[0x5c - 0x50];
    void* mpWindow_5c;               // +0x5c  preview window
    char  pad60[0x64 - 0x60];
    float mAmount_64;                // +0x64  amount (negative -> default)
    void SetMode(int mode);
};
struct CompareObj      { char pad00[0x0c]; int32_t mValue0c; int32_t mValue10; };  // +0x0c / +0x10
struct PaletteItemHandle { int32_t mHandle00; };                          // enclosing item seen from the +0x20 handler
struct NotifySink      { int32_t mpObj; void FUN_00b5f950(void* p); };    // 0x00b5f950
struct MsgTarget       { void FUN_00ef0b80(); };                          // 0x00ef0b80
struct PayloadTriple   { char pad00[0xc]; int32_t mValue0c; int32_t mValue10; int32_t mValue14; };
struct PaletteItemFull {
    char    mCastFace_08[0x08];      // +0x08  interface-cast sub-object (vtable)
    int32_t mHandle_10;              // +0x10  handle passed to 0x00ecda80
    char    pad14[0x48 - 0x14];
    PayloadTriple* mpPayload_48;     // +0x48  payload triple owner
};
struct MsgArgs {
    int32_t    mA00;                 // +0x00
    int32_t    mA04;                 // +0x04
    int32_t    mA08;                 // +0x08
    int32_t    mMsgId;               // +0x0c  id passed to the message sink
    int32_t    mA10;                 // +0x10  (not initialised by the original)
    int32_t    mPayload0;            // +0x14
    int32_t    mPayload1;            // +0x18
    int32_t    mPayload2;            // +0x1c
    NotifySink mSlot20;              // +0x20  notification slot
    int32_t    mSlot24;              // +0x24  ref-counted object
};
struct MsgArgsDtor     { void FUN_005c12c0(); };                          // 0x005c12c0 (thiscall-0)
struct PaletteItemMsg  { bool Dispatch(int unused1, void* msg, int unused3); };

void* __cdecl FUN_0067dcc0();                          // 0x0067dcc0 message sink getter
void* __cdecl FUN_00a206f0();                          // 0x00a206f0 secondary getter
int   __cdecl FUN_00435e90();                          // 0x00435e90
void  __cdecl FUN_00435ed0(int id, int value);         // 0x00435ed0

// ============================================================ 0x00ecda80
// @ 0x00ecda80
void FUN_00ecda80_fn(int param_1)
{
    int u = 0;
    int* at = GetSystemAT();
    if (at)
        u = K0(at, 0x20);
    at = GetSystemAT();
    if (at) {
        C1(at, 0x38, 0x3475365);
        C2(at, 0x40, 0x3475381, 0x72d342a9);
        C2(at, 0x40, 0x3475385, u);
        C0(at, 0x58);
    }
    int* p = FUN_00efc910();
    if (p == 0 || *p != param_1) {
        C1(g_15ad298, 0x20, 0);
        FUN_00f00380(param_1);
    }
    int tmp = param_1;
    int* ms = SP_MessageServer();
    C3(ms, 0x14, 0x7465518, (int)&tmp, 0);
}

// ============================================================ 0x00ecdb30
// @ 0x00ecdb30
void __fastcall FUN_00ecdb30(int* p)
{
    int a = 0, b = 0, c = 0;
    C1(p, 0x30, (int)&a);
    (void)b; (void)c;
}

// ============================================================ 0x00ecdb50
// @ 0x00ecdb50
void SelObj_ecdb50::Set(int param_2)
{
    int* p = (int*)this;
    if (param_2 == -1) {
        p[4] = -1;
        ((void(__thiscall*)(void*))VTB(p, 0x18))(p);
    } else {
        p[4] = param_2;
        ((void(__thiscall*)(void*))VTB(p, 0x14))(p);
    }
}

// ============================================================ 0x00ecdb80
bool __fastcall FUN_00ecdb80(int p)
{
    return *(int*)(p + 0x10) == -1;
}

// ============================================================ 0x00ecdb90
// @ 0x00ecdb90
void __fastcall FUN_00ecdb90(int* p)
{
    // real vtable call: slot = *(*(int**)p + 0x1c), this = p
    if (p[4] != -1)
        ((void(__thiscall*)(void*, int))(((void**)(*(void**)p))[0x1c / 4]))(p, -1);
}

// ============================================================ 0x00ecdbb0
// @ 0x00ecdbb0
void __fastcall FUN_00ecdbb0(int p)
{
    if (*(int*)(p + 0x14) == (int)0x867a9ee9)
        FUN_00eece20(p + 0x18);
}

// ============================================================ 0x00ecdc20
struct Obj_ecdc20 { void FUN_00ecdc20(int param_2); };
// @ 0x00ecdc20
void Obj_ecdc20::FUN_00ecdc20(int param_2)
{
    int* p = (int*)this;
    p[5] = *(int*)(param_2 + 0x14);
    p[3] = *(int*)(param_2 + 0xc);
    C1(p, 0x1c, *(int*)(param_2 + 0x10));
}

// ============================================================ 0x00ecdc70
struct Obj_ecdc70 { int FUN_00ecdc70(); };
// @ 0x00ecdc70
int Obj_ecdc70::FUN_00ecdc70()
{
    int param_1 = (int)this;
    char c = FUN_005f3060();
    if (c) {
        char buf[8];
        FUN_00805fe0(buf, *(int*)(param_1 + 0x18c));
        float f = *(float*)(buf + 8);
        if (f < *(float*)(param_1 + 0x84)) {
            if (FUN_00efc9c0())
                return 1;
        }
    }
    return 0;
}

// ============================================================ 0x00ecdcc0
// @ 0x00ecdcc0
void __fastcall FUN_00ecdcc0(int param_1)
{
    FUN_005f4750();
    FUN_00401020();
    void* prop = (void*)FUN_0113ae10();
    void* cand = *(void**)(*(int*)(param_1 + 0x17c) + 0x14);
    if (cand && *(char*)(*(int*)(param_1 + 0x17c) + 0x31) != 0)
        prop = cand;
    if (prop && *(char*)(param_1 + 0x16b) != 0) {
        int* wm = SP_WindowManager();
        int* w = (int*)K0(wm, 4);
        float* r = (float*)K0(w, 0x34);
        cSPUIPropertyLayout_SetPositionAndOffset(prop, *(float*)(param_1 + 0x84),
            *(float*)(param_1 + 0x88), (r[2] - r[0]) * 0.09375f, (r[3] - r[1]) * -0.025f);
    }
}

// ============================================================ 0x00ecdd70
// @ 0x00ecdd70
void __fastcall FUN_00ecdd70(int* p)
{
    if ((int*)p[0x18]) C1((int*)p[0x18], 4, 0);
    if ((int*)p[0x17]) C1((int*)p[0x17], 4, 0);
    if ((int*)p[0x16]) C1((int*)p[0x16], 4, 0);
    if ((int*)p[0x15]) C1((int*)p[0x15], 4, 0);
    if ((int*)p[0x14]) C1((int*)p[0x14], 8, 0);
    if ((int*)p[0x13]) C1((int*)p[0x13], 4, 0);
    if ((int*)p[0x12]) C1((int*)p[0x12], 8, 0);
    p[0x11] = (int)vtbl_PaintSystem;
    FUN_005c6c50();
    p[2] = (int)vtbl_cEditorResource;
    p[0] = (int)vtbl_cContentValidationSummarizer;
}

// ============================================================ 0x00ecde00
// Interface cast/adjustor for a sub-object that sits 8 bytes into the object.
// `this` is the +8 sub-object; the ids pick one of the object's interfaces.
// @ 0x00ecde00
__declspec(noinline) int CastObj::Cast(int id)
{
    int base = (int)this - 8;                  // enclosing object
    if (id == 0x4785a3d) {
        if (base == 0)
            return 0;
        return (int)this + 0x1c;
    }
    if (id == 0x722de52)
        return base;

    int iface = 0;
    if (id == 0xee3f516e) {
        if (base != 0)
            iface = (int)this;
    } else if (id == 0x82a70e8) {
        iface = base;
    }
    if (iface != 0)
        return iface;
    return ((CastBase*)((char*)this + 0x28))->FUN_005c6a30(id);
}

// ============================================================ 0x00ecde60
// @ 0x00ecde60
void __fastcall FUN_00ecde60_fn(int param_1)
{
    SP_cSPPaletteItemUI_Shutdown();
    int iVar2 = (param_1 == 0x24) ? 0 : param_1 + 0x20;
    int* srv = EA_Messaging_GetServer();
    C3(srv, 0x2c, iVar2, 0x72304d0, 0xffffd8f1);
    iVar2 = *(int*)(param_1 + 0x28);
    if (iVar2) {
        FUN_00401020();
        FUN_005f0a60(iVar2);
    }
    if (*(int**)(param_1 + 0x2c))
        cSPUILayout_Shutdown(*(void**)(param_1 + 0x2c), 1);
    int* p;
    p = *(int**)(param_1 + 0x24);
    if (p) { *(int*)(param_1 + 0x24) = 0; C1(p, 8, 0); }
    p = *(int**)(param_1 + 0x2c);
    if (p) { *(int*)(param_1 + 0x2c) = 0; C1(p, 8, 0); }
    p = *(int**)(param_1 + 0x28);
    if (p) { *(int*)(param_1 + 0x28) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x34);
    if (p) { *(int*)(param_1 + 0x34) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x38);
    if (p) { *(int*)(param_1 + 0x38) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x3c);
    if (p) { *(int*)(param_1 + 0x3c) = 0; C1(p, 4, 0); }
    p = *(int**)(param_1 + 0x30);
    if (p) { *(int*)(param_1 + 0x30) = 0; C1(p, 4, 0); }
    // ctor/dtor tail emitted via FUN_00ecdd70 chain in the real code
    FUN_00ecdd70((int*)param_1);
}

// ============================================================ 0x00ecdf60
// @ 0x00ecdf60
void FUN_00ecdf60_fn(void)
{
    int* p = (int*)operator new(0x1c8);
    if (p) {
        FUN_005f7380();
        p[0] = (int)vtbl_BakeSprites;
        p[1] = (int)vtbl_cSPScenarioSwatchItemUI;
        p[3] = (int)vtbl_PaintSystem;
        FUN_00401020();
        FUN_005f0ca0(p);
        return;
    }
    FUN_00401020();
    FUN_005f0ca0(0);
}

// ============================================================ 0x00ecdfc0
// @ 0x00ecdfc0
void __fastcall FUN_00ecdfc0(int param_1)
{
    void* obj = *(void**)(param_1 + 0x4c);
    if (obj != 0) {
        float f = *(float*)(param_1 + 0x64);
        if (f < 0.0f)
            f = g_15abee4;
        ColorStore* u = (ColorStore*)((int(__thiscall*)(void*, int))VTB(obj, 0xc))(obj, 0x3349c94);
        if (u != 0)
            u->Set(f);
    }
}

// ============================================================ 0x00ece010
// Refresh the preview colours of the palette item: validate the requested
// triple against the UI helpers, falling back to the item's own colours and
// finally to "no image"; then tint the window's text.
// @ 0x00ece010
void PaletteItem_ece010::SetColors(int* rgb, bool highlight)
{
    if (mpLayout_50 == 0)
        return;

    int* w = (int*)((FindWindowStub*)mpLayout_50)->FindWindowByID(0x4a1cb6e, 1);
    if (w == 0)
        return;

    int local[3];
    local[0] = rgb[0];
    local[1] = rgb[1];
    local[2] = rgb[2];

    void* sys = FUN_008de1a0();
    if (((int(__thiscall*)(void*, int*, int, int))VTB(sys, 0x30))(sys, local, 0, 0) != 0)
        goto useImage;

    local[2] = 0x65928944;
    sys = FUN_008de1a0();
    if (((int(__thiscall*)(void*, int*, int, int))VTB(sys, 0x30))(sys, local, 0, 0) != 0)
        goto useImage;

    local[0] = mpColorSource_48->mRgb[0];
    local[1] = mpColorSource_48->mRgb[1];
    local[2] = mpColorSource_48->mRgb[2];
    sys = FUN_008de1a0();
    if (((int(__thiscall*)(void*, int*, int, int))VTB(sys, 0x30))(sys, local, 0, 0) == 0)
        goto clearImage;

useImage:
    FUN_00807bb0(w, local, -1);
    goto tint;

clearImage:
    FUN_008068d0((int)w, 0, -1);

tint:
    if (highlight)
        C1(w, 0x5c, 0x77ffffff);
    else
        C1(w, 0x5c, -1);
}

// ============================================================ 0x00ece110
// @ 0x00ece110
void WinObj_ece110::Activate(int param_2)
{
    int param_1 = (int)this;
    if (*(int**)(param_1 + 0x50) == 0)
        return;
    int* w = (int*)((FindWindowStub*)*(void**)(param_1 + 0x50))->FindWindowByID(0x79591e0, 1);
    if (w == 0)
        return;
    ((void(__thiscall*)(void*, int))VTB(w, 0x80))(w, param_2);
}

// ============================================================ 0x00ece140
// Apply the swatch mode to the palette target: notify it, recolour it and
// tint its preview window; then push the amount into the colour store.
// The target is revalidated between the two steps (it is released and
// reallocated by the notifications in between).
// @ 0x00ece140
void PaletteSwatch_ece140::SetMode(int mode)
{
    if (mpTarget_4c == 0)
        return;

    ColorStore* store = PaletteTarget(mpTarget_4c);
    store->FUN_007a4c80(mode);
    ((void(__thiscall*)(ColorStore*, int))VTB(store, 0x38))(store, mode);
    store->FUN_005f49a0(mode);

    if (mpWindow_5c != 0)
        C2(mpWindow_5c, 0x7c, mode != 0 ? 1 : 0, 0x1000);

    if (mpTarget_4c == 0)
        return;

    float f = mAmount_64;
    if (f < 0.0f)
        f = g_15abee4;

    store = PaletteTarget(mpTarget_4c);
    if (store != 0)
        store->Set(f);
}

// ============================================================ 0x00ece200
// Palette-item message hook: on the "swatch activated" message, ask the system
// AT to refresh the item, releasing the palette when it was left empty.
// @ 0x00ece200
void PaletteItemUI_ece200::DoMessage(void* msg, PaletteMessage* data)
{
    if (data->mKind08 == 6) {
        if (((int(__thiscall*)(void*))VTB(msg, 0x1c))(msg) == 0x4a1cb6e &&
            data->mValue18 == 0x3ea) {
            int handle = ((PaletteItemHandle*)((char*)this - 0x20))->mHandle00;
            ((SysAT_15ad328*)0x015ad328)->FUN_00f00380(handle);
            if (handle == -2)
                ((PaletteMgr*)g_pGameMgr_16c7aa4)->mpSink_d4->FUN_00efbbe0(6, 7);
        }
    }
    ((PaletteItemBase*)this)->DoMessage(msg, data);
}

// ============================================================ 0x00ece270
// @ 0x00ece270
void __fastcall FUN_00ece270(int* p)
{
    int local[3] = {0, 0, 0};
    C1(p, 0x30, (int)&local);
    FUN_008068d0(p[0x16], p[0x15], 0);
    int a = 0, b = 0;
    C2(p, 0x38, (int)&a, 1);
    int* q = 0;
    C2(p, 0x3c, (int)&q, 1);
    C1(p, 0x40, (int)&g_13ec468);
    FUN_00ece140(0);
}

// ============================================================ 0x00ece300
// @ 0x00ece300
void __fastcall FUN_00ece300(int param_1)
{
    int v = *(int*)(param_1 + 0x4c);
    PaletteStore* s = (PaletteStore*)FUN_00401020_get();
    s->Set(v, 5.0f);
}

// ============================================================ 0x00ece320
// @ 0x00ece320
void __fastcall FUN_00ece320(int param_1)
{
    if (*(int*)(param_1 + 0x58) != 0) {
        FUN_00834e30_tc(*(void**)(param_1 + 0x58));
        int* p = *(int**)(param_1 + 0x58);
        if (p) { *(int*)(param_1 + 0x58) = 0; ((void(__thiscall*)(void*))VTB(p, 8))(p); }
    }
    if (*(int*)(param_1 + 0x1c) != 0) {
        int iVar2 = (param_1 == 0x24) ? 0 : param_1 + 0x48;
        SPUIHelpers_VisitWindowTreeDepthFirst(*(int*)(param_1 + 0x1c), (void*)&FUN_00ecd9c0, iVar2);
    }
    FUN_00ecde60_tc((void*)param_1);
}

// ============================================================ 0x00ece370
// @ 0x00ece370
int CastObj_ece370::Cast(int param_2)
{
    int param_1 = (int)this;
    if (param_2 == 0x722de63)
        return param_1 - 8;
    if (param_2 == 0x2f009dd0) {
        if (param_1 != 8)
            return param_1 + 0x64;
        return 0;
    }
    return ((CastObj*)param_1)->Cast(param_2);
}

// ============================================================ 0x00ece3b0
// @ 0x00ece3b0
int FUN_00ece3b0(int* param_1)
{
    if (param_1 != 0) {
        int i = ((int(__thiscall*)(void*, int))VTB(param_1, 0xc))(param_1, 0x3349c94);
        if (i != 0) {
            int* p = (int*)FUN_01137690(FUN_005f33f0((void*)i));
            if (p != 0) {
                int j = ((int(__thiscall*)(void*, int))VTB(p, 0xc))(p, 0x722de52);
                if (j != 0)
                    return j;
            }
        }
    }
    return 0;
}

// ============================================================ 0x00ece3f0
void* __stdcall FUN_00ece3f0(char param_1)
{
    void* v = (void*)g_15abf0c;
    if (param_1 == 0)
        v = (void*)g_15abf1c;
    return v;
}

// ============================================================ 0x00ece410
// Compare two palette entries by their identifiers.  The original receives its
// second argument in EAX and picks the evaluation order from that: with the
// first entry in EAX it tests the identifiers before the -2/-1 states.
// @ 0x00ece410
bool __cdecl FUN_00ece410(int* self, int* other)
{
    int a = K0(other, 0x28);
    int b = K0(self, 0x28);
    if (a != b)
        return ((b == (int)0xd37c1045) || (a == (int)0xd37c1045)) &&
               ((b == 0x5b3d1d0d) || (a == 0x5b3d1d0d));

    CompareObj* lhs = (CompareObj*)self;
    CompareObj* rhs = (CompareObj*)other;
    if (lhs->mValue10 == -1 && rhs->mValue10 != -2 && lhs->mValue10 != -2)
        return lhs->mValue0c != 7;
    if (lhs->mValue10 == -2 || rhs->mValue10 == -2)
        return false;

    int* py = g_pGameMgr_16c7aa4->pOwner_74->FUN_00f3e8a0(rhs->mValue10);
    g_pGameMgr_16c7aa4->pOwner_74->FUN_00f3e8a0(lhs->mValue10);
    if (py == 0)
        return false;
    return false;
}

// ============================================================ 0x00ece4d0
// Palette-item message dispatcher: a handful of editor messages are turned
// into sink notifications carrying the item's current payload; anything else
// falls through untouched.
static inline int MessageId(void* msg)
{
    return ((int(__thiscall*)(void*))VTB(msg, 0x1c))(msg);
}

// @ 0x00ece4d0
bool PaletteItemMsg::Dispatch(int unused1, void* msg, int unused3)
{
    (void)unused1;
    (void)unused3;
    PaletteItemFull* item = (PaletteItemFull*)((char*)this - 0x6c);

    if (MessageId(msg) == 0x4a1cb6d || MessageId(msg) == 0x73d54a0) {
        ((MsgTarget*)g_pGameMgr_16c7aa4)->FUN_00ef0b80();

        MsgArgs args;
        args.mA00 = 0x13f7e34;
        args.mA04 = 0x13f7e30;
        args.mA08 = 0;
        args.mMsgId = 0x72ab904;
        args.mPayload0 = item->mpPayload_48->mValue0c;
        args.mPayload1 = item->mpPayload_48->mValue10;
        args.mPayload2 = item->mpPayload_48->mValue14;
        args.mSlot20.mpObj = 0;
        args.mSlot24 = 0;

        if (item != 0) {
            int* cast = (int*)((int(__thiscall*)(void*, int))VTB(item->mCastFace_08, 0xc))(item->mCastFace_08, 0xee3f516e);
            int* old = (int*)args.mSlot20.mpObj;
            if (cast != old) {
                if (cast != 0)
                    C0(cast, 0);                        // add-ref through slot 0
                args.mSlot20.mpObj = (int32_t)cast;
                if (old != 0)
                    C0(old, 4);                         // release through slot 4
            }
        }

        void* sink = FUN_0067dcc0();
        ((void(__thiscall*)(void*, int, void*, int))VTB(sink, 0x14))(sink, args.mMsgId, &args, 0);

        if (args.mSlot24 != 0)
            C0((void*)args.mSlot24, 4);
        if (args.mSlot20.mpObj != 0)
            C0((void*)args.mSlot20.mpObj, 4);
        return true;
    }

    if (MessageId(msg) == 0x73272b0) {
        MsgArgs args;
        args.mA00 = 0x13f7e34;
        args.mA04 = 0x13f7e30;
        args.mA08 = 0;
        args.mMsgId = 0x73e7b71;
        args.mPayload0 = item->mpPayload_48->mValue0c;
        args.mPayload1 = item->mpPayload_48->mValue10;
        args.mPayload2 = item->mpPayload_48->mValue14;
        args.mSlot20.mpObj = 0;
        args.mSlot24 = 0;

        if (item != 0) {
            int* cast = (int*)((int(__thiscall*)(void*, int))VTB(item->mCastFace_08, 0xc))(item->mCastFace_08, 0xee3f516e);
            args.mSlot20.FUN_00b5f950(cast);
        }

        void* sink = FUN_0067dcc0();
        ((void(__thiscall*)(void*, int, void*, int))VTB(sink, 0x14))(sink, args.mMsgId, &args, 0);

        void* extra = FUN_00a206f0();
        int value = 0;
        if (extra != 0)
            value = ((int(__thiscall*)(void*))VTB(extra, 0x20))(extra);
        FUN_00435ed0(0x13bed0aa, value);

        ((MsgArgsDtor*)&args)->FUN_005c12c0();
        return true;
    }

    if (MessageId(msg) == 0x7464588) {
        FUN_00ecda80(item->mHandle_10);
        return true;
    }

    if (MessageId(msg) == 0x7b6b2cd) {
        void* sink = FUN_0067dcc0();
        ((void(__thiscall*)(void*, int, void*, int))VTB(sink, 0x14))(sink, 0x7326686, (void*)item->mHandle_10, 0);
        FUN_00435ed0(0x956eae88, FUN_00435e90());
        return true;
    }
    return false;
}

// ============================================================ 0x00ece730
struct Obj_ece730 { bool FUN_00ece730(int* param_2, int param_3, int param_4, int param_5, int param_6); };
// @ 0x00ece730
bool Obj_ece730::FUN_00ece730(int* param_2, int param_3, int param_4, int param_5, int param_6)
{
    int param_1 = (int)this;
    (void)param_3; (void)param_4; (void)param_6;
    int i = K0(param_2, 0x1c);
    if (i == 0x4a1cb6e && param_5 == 1000) {
        if (*(int*)(param_1 + 0x14) != 0 || *(int*)(param_1 + 0x18) != 0) {
            if (!FUN_005ff1c0()) {
                FUN_00ecda80(*(int*)(param_1 - 0x5c));
                return 1;
            }
        }
        EA_LimitStopwatch_SetTimeLimit((void*)(param_1 + 0x14), 0xfa, 1);
    }
    return 0;
}

// ============================================================ 0x00ece790
// @ 0x00ece790
void __fastcall FUN_00ece790(int* p)
{
    if (p[4] != -1 && p[0x17] != 0) {
        if (((char(__thiscall*)(void*))VTB(p, 0x44))(p) != 0) {
            int u = ((int(__thiscall*)(void*))VTB((void*)p[0x17], 0x30))((void*)p[0x17]);
            ((void(__thiscall*)(void*, int))VTB((void*)p[0x17], 0x5c))((void*)p[0x17], (u & 0xff000000) + 0xaa2222);
            return;
        }
        int u = ((int(__thiscall*)(void*))VTB((void*)p[0x17], 0x30))((void*)p[0x17]);
        ((void(__thiscall*)(void*, int))VTB((void*)p[0x17], 0x5c))((void*)p[0x17], (u & 0xff000000) + 0xffffff);
    }
}

// ============================================================ 0x00ece7f0
// @ 0x00ece7f0
bool __fastcall FUN_00ece7f0(int param_1)
{
    int* i = g_pGameMgr_16c7aa4->pOwner_74->FUN_00f3e8a0(*(int*)(param_1 + 0x10));
    if (i == 0)
        return false;
    char* b = (char*)i;
    if (b[0x1c] == 0 && b[0x44] == 0 && b[0x6c] == 0)
        return 0;
    return true;
}

// ============================================================ 0x00ece870
// @ 0x00ece870
int* FUN_00ece870(int* param_1, int param_2)
{
    param_1[1] = 0;
    param_1[2] = (int)vtbl_BakeSprites;
    param_1[0] = (int)vtbl_cSPScenarioSwatchItemUI;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[5] = *(int*)(param_2 + 0x14);
    param_1[3] = *(int*)(param_2 + 0xc);
    C1(param_1, 0x1c, *(int*)(param_2 + 0x10));
    return param_1;
}

// ============================================================ 0x00ece8c0
// @ 0x00ece8c0
void __fastcall FUN_00ece8c0(int* p)
{
    if (p[4] != -1) {
        int* u = g_pGameMgr_16c7aa4->pOwner_74->FUN_00f3e8a0(p[4]);
        ((void(__thiscall*)(void*, int*))VTB(p, 0x30))(p, u);
    }
}

// ============================================================ 0x00ece8f0
// @ 0x00ece8f0
int __fastcall FUN_00ece8f0(int param_1)
{
    if (*(int*)(param_1 + 0x10) != -1) {
        int* i = g_pGameMgr_16c7aa4->pOwner_74->FUN_00f3e8a0(*(int*)(param_1 + 0x10));
        if (i != 0)
            return FUN_00eece20((int)i);
    }
    return *(int*)(param_1 + 0x14);
}

// ============================================================ 0x00ece920
// @ 0x00ece920
void FUN_00ece920(void)
{
    int* p = ((Mgr167eaec*)FUN_00b3d320_get())->Fn_b1de80();
    if (p != 0) {
        int local = 0;
        char c = ((char(__thiscall*)(void*, int, int*))VTB(p, 0x24))(p, 0xa143f717, &local);
        if (c != 0 && *(short*)((char*)local + 0x12) == 0xd) {
            int* v = ((PropObj*)local)->GetFloat();
            g_15abee4 = *(float*)v;
        }
    }
    FUN_006a1400(p, 0x27c26ec0, &g_15abf0c);
    FUN_006a1400(p, 0x92bb2e5f, &g_15abf1c);
}

// ============================================================ 0x00ece990
// @ 0x00ece990
int* __fastcall FUN_00ece990(int* param_1)
{
    param_1[1] = 0;
    param_1[2] = (int)vtbl_BakeSprites;
    param_1[0] = (int)vtbl_cSPScenarioSwatchItemUI;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[3] = -1;
    param_1[4] = -1;
    param_1[5] = (int)0x867a9ee9;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    SP_cSPPaletteItemUI_ctor((void*)(param_1 + 9));
    param_1[0x11] = (int)vtbl_PaintSystem;
    param_1[0] = (int)vtbl_PaintSystem;
    param_1[2] = (int)vtbl_PaintSystem;
    param_1[0xc] = (int)vtbl_PaintSystem;
    param_1[0xd] = (int)vtbl_PaintSystem;
    param_1[0x11] = (int)vtbl_PaintSystem;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    param_1[0x18] = 0;
    *(char*)(param_1 + 0x1a) = 0;
    param_1[0x19] = (int)0xbf800000;
    return param_1;
}
