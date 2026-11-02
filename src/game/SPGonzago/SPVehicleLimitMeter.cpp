// src/game/SPGonzago/SPVehicleLimitMeter.cpp -- migrated from slice(s) s00d1df40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPVehicleLimitMeter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommunity.h"
#include "SP/cCity.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern const char   kEditorAllocName[];// 0x013eb430
#include <math.h>
#include <wchar.h>

// ---- items of slice s00d1df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct IWin {
    PV8 PV4 PV                                   // 0x00..0x30
    virtual float* Slot34();                     // 0x34  (returns a pointer to a rect/vector)
    PV8 PV                                       // 0x38..0x58
    virtual void   Slot5c(uint argb);            // 0x5c  (set colour)
    PV                                           // 0x60
    virtual void   Slot64(float a, float b);     // 0x64  (set range)
    PV4 PV                                       // 0x68..0x78
    virtual void   Slot7c(int a, int b);         // 0x7c  (set visible/toggle)
    virtual void   Slot80(const wchar_t* text);  // 0x80  (set caption)
};
struct IRefS {
    PV                                           // 0x00
    virtual void Slot4();                        // 0x04
    virtual void Slot8();                        // 0x08
};
struct Civ;
struct cCity {
    Civ* GetCivilization();                      // 0x00bd9bf0
    int  GetVehicleSpecialty();                  // 0x00bd81d0
};
struct Civ {
    int FUN_00bf1fd0(int a);                     // 0x00bf1fd0
    int FUN_00bf0c60(int a, int b, int c, int d); // 0x00bf0c60
};
struct ResKey { uint a, b, c; };
struct cSPUILayout_s00d1_df40 {
    void* FindWindowByID(uint id, int a);              // 0x008105b0
    bool  Init(const ResKey* key, int flag, uint id);  // 0x008120d0
    bool  SetParentWin(void* win, int flag, uint id);  // 0x008121b0
};
struct ConnectionDialog {
    void* ctor();                                      // 0x00810000
};
struct Wrapper {
    cSPUILayout_s00d1_df40* mpLayout;                             // +0x04
    cCity*       mpCity;                               // +0x08
};
int   __cdecl Sprintf16(wchar_t* out, const wchar_t* fmt, ...);   // 0x009399c0
void* __cdecl OpNew(uint size, const char* name, int, int, int, int); // 0x00f473a0
uint  __cdecl FUN_00b6f0c0(uint id);                // 0x00b6f0c0
uint  __cdecl SP_ColorRGBToU32(uint rgb);           // 0x00458a40
extern const char   kEditorAllocName[];// 0x013eb430
// ---- items of slice s00d1df40 end

// @ 0x00d1df40
void __fastcall FUN_00d1df40(Wrapper* self, void* edx)
{
    (void)edx;
    Civ* civ = self->mpCity->GetCivilization();
    int a0 = civ->FUN_00bf1fd0(0);
    int b0 = civ->FUN_00bf0c60(0, -1, -1, 0);
    int a1 = civ->FUN_00bf1fd0(1);
    int b1 = civ->FUN_00bf0c60(1, -1, -1, 0);
    int a2 = civ->FUN_00bf1fd0(2);
    int b2 = civ->FUN_00bf0c60(2, -1, -1, 0);
    cSPUILayout_s00d1_df40* layout = self->mpLayout;
    wchar_t buf[32];
    IWin* w;
    w = (IWin*)layout->FindWindowByID(0x6256701, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b0, a0); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256702, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b0, a0); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256705, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b1, a1); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256706, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b1, a1); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256703, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b2, a2); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256704, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b2, a2); w->Slot80(buf); }
}

// @ 0x00d1e180
bool __fastcall FUN_00d1e180(Wrapper* self, void* edx, void* param_2)
{
    (void)edx;
    Wrapper* wself = self;
    ConnectionDialog* d = (ConnectionDialog*)OpNew(0x18, kEditorAllocName, 0, 0, 0, 0);
    if (d)
        d = (ConnectionDialog*)d->ctor();
    void* old = wself->mpLayout;
    if (d != old) {
        if (d) ((IRefS*)d)->Slot4();
        wself->mpLayout = (cSPUILayout_s00d1_df40*)d;
        if (old) ((IRefS*)old)->Slot8();
    }
    cSPUILayout_s00d1_df40* layout = wself->mpLayout;
    ResKey key;
    key.a = 0x996e6398;
    key.b = 0x0510a95b;
    key.c = 0x40464100;
    if (!layout->Init(&key, 1, 0x5b598fa))
        return false;
    layout->SetParentWin(param_2, 1, 0x5b598fa);
    IWin* w;
    w = (IWin*)layout->FindWindowByID(0x53439d0, 1);
    if (w) {
        float* r = w->Slot34();
        w->Slot64(-(r[2] - r[0]), 0.0f);
    }
    uint color = SP_ColorRGBToU32(FUN_00b6f0c0(0x53dbcf1));
    w = (IWin*)layout->FindWindowByID(0x6256751, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256752, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256755, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256756, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256753, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256754, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x62583c0, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c1, 1); if (w) w->Slot7c(1, 0);
    w = (IWin*)layout->FindWindowByID(0x62583c4, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c5, 1); if (w) w->Slot7c(1, 0);
    w = (IWin*)layout->FindWindowByID(0x62583c2, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c3, 1); if (w) w->Slot7c(1, 0);
    uint show;
    switch (wself->mpCity->GetVehicleSpecialty()) {
    case 0:
        w = (IWin*)layout->FindWindowByID(0x62583c0, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c1;
        break;
    case 1:
        w = (IWin*)layout->FindWindowByID(0x62583c4, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c5;
        break;
    case 2:
        w = (IWin*)layout->FindWindowByID(0x62583c2, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c3;
        break;
    default:
        return true;
    }
    w = (IWin*)layout->FindWindowByID(show, 1);
    if (w)
        w->Slot7c(1, 1);
    return true;
}
