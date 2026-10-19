// src/game/Spui/SPUILaunchScreenWinProc.cpp -- migrated from slice(s) s0080c5d0 by tools/migrate/rewrite.py
// Object file: Spui/SPUILaunchScreenWinProc.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern int gChildNodeOff;   // 0x1440aec: node-to-object offset of the child list

// ---- items of slice s0080c5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
struct Rect4 { float x1, y1, x2, y2; };
struct IWin;
struct WinAux {                       // object returned by IWin slot 0x2a
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual IWin* Query(u32 id);      // 0x0c
};
struct Dims { char pad[0x1c]; int w; int pad2; int h; };   // h at +0x20, w at +0x1c
struct WinInner {                     // object returned by Query(0xef3c47cf)
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
    virtual Dims* GetDims();          // 0x18
};
struct IWin {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
    virtual IWin* GetParent();                          // 0x10
    virtual void s5();
    virtual void s6();
    virtual u32 GetControlID();                         // 0x1c
virtual void s8();
virtual void s9();
virtual void s10();
    virtual u32 GetFlagsValue();                        // 0x2c
virtual void s12();
virtual void s13();
    virtual Rect4* GetArea();                           // 0x38
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual void SetShadeColor(u32 c);                  // 0x5c
    virtual void SetArea(Rect4* r);                     // 0x60
    virtual void SetLocation(float x, float y);         // 0x64
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
    virtual void SetFlag(int flag, int on);             // 0x7c
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
    virtual void s37();
    virtual void Invalidate();                          // 0x98
virtual void s39();
virtual void s40();
virtual void s41();
    virtual WinAux* GetAux();                           // 0xa8
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
    virtual int** ChildBegin(int** out);                // 0xcc
    virtual int** ChildEnd(int** out);                  // 0xd0
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
    virtual IWin* FindWindowByID(u32 id, int flag);     // 0xf0
};
struct Xform { char pad[0x40]; int dirty; char pad2[0x10]; void __thiscall Scale(const float* v); };  // 0x95ea30
struct WinMsg {
    IWin* source;     // +0
    u32   pad4;
    u32   type;       // +8
    u32   flagsNew;   // +0xc
    u32   flagsOld;   // +0x10
    u32   pad14;
    Xform* xform;     // +0x18
};
extern int gChildNodeOff;   // 0x1440aec: node-to-object offset of the child list
static inline IWin* ChildOf(int* node) { return (IWin*)((char*)node + gChildNodeOff); }
struct cSPUILaunchScreenWinProc {
    void** vtbl;   // +0
    void** vtbl2;  // +4
    u32    f8;     // +8
    u32    fC;     // +0xc
    i32    f10;    // +0x10

    cSPUILaunchScreenWinProc* __thiscall ctor();             // 0x80cf00
    u8   __thiscall DoMessage(IWin* window, WinMsg* msg);    // 0x80cf80
};
// ---- items of slice s0080c5d0 end

// @ 0x0080cf80
u8 __thiscall cSPUILaunchScreenWinProc::DoMessage(IWin* window, WinMsg* msg)
{
    u32 type = msg->type;
    if (type == 0x11) {
        IWin* top = window->FindWindowByID(0x279b810, 0);
        if (top) top->SetShadeColor(0xffffff);
        u32 kIds[3] = { 0x279bad0, 0x279bad4, 0 };
        for (const u32* pid = kIds; *pid; ++pid) {
            IWin* c = window->FindWindowByID(*pid, 0);
            Rect4* r = c->GetArea();
            Rect4 local;
            float nx = -r->x1, ny = -r->y1;
            local.x1 = nx + r->x1;
            local.y1 = ny + r->y1;
            local.x2 = r->x2 + nx;
            local.y2 = r->y2 + ny;
            int* tmp1; int* tmp2;
            int* it = *c->ChildBegin(&tmp1);
            if (it != *c->ChildEnd(&tmp2)) {
                float cx = (local.x2 + local.x1) * 0.5f;
                float cy = (local.y2 + local.y1) * 0.5f;
                int* next;
                do {
                    next = (int*)*it;
                    IWin* ch = ChildOf(it);
                    ch->SetFlag(1, ch->GetControlID() == 0x279e540);
                    WinAux* aux = ch->GetAux();
                    if (aux) {
                        WinInner* in = (WinInner*)aux->Query(0xef3c47cf);
                        if (in && in->GetDims()) {
                            int h = in->GetDims()->h;
                            Rect4 sz;
                            sz.x1 = 0.0f;
                            sz.y1 = 0.0f;
                            sz.x2 = (float)in->GetDims()->w;
                            sz.y2 = (float)h;
                            ch->SetArea(&sz);
                        }
                    }
                    Rect4* a = ch->GetArea();
                    ch->SetLocation(a->x1 - ((a->x2 + a->x1) * 0.5f - cx),
                                    a->y1 - ((a->y2 + a->y1) * 0.5f - cy));
                    it = next;
                } while (next != *c->ChildEnd(&tmp2));
            }
        }
        window->SetFlag(1, 0);
        window->Invalidate();
        return 0;
    }
    if (type == 0x12) return 0;
    if (type == 0x287259f6) {
        IWin* src = msg->source;
        if (src->GetControlID() == 0x279b810) {
            IWin* t = window->FindWindowByID(0x279bd58, 0);
            if (t) {
                u8 on = (u8)((src->GetFlagsValue() >> 2) & 1);
                t->SetFlag(1, on);
                if (on) src->SetShadeColor(0xffffffff);
                else    src->SetShadeColor(0xffffff);
                return 0;
            }
        }
        return 0;
    }
    if (type == 0xc) return 0;
    if (type == 0x15) {
        IWin* parent = window->GetParent();
        Rect4 A = *window->GetArea();
        Rect4* P = parent->GetArea();
        float p0 = P->x1, p2 = P->x2, p1 = P->y1, p3 = P->y2;
        window->SetLocation(A.x1 - ((A.x2 + A.x1) * 0.5f - (p2 + p0) * 0.5f),
                            A.y1 - ((A.y2 + A.y1) * 0.5f - (p3 + p1) * 0.5f));
        float sx = (p2 - p0) / (A.x2 - A.x1);
        float sy = (p3 - p1) / (A.y2 - A.y1);
        if (sx > sy) sx = sy;
        float v[3];
        v[0] = sx; v[1] = sx; v[2] = 1.0f;
        msg->xform->Scale(v);
        window->SetFlag(1, 1);
        window->Invalidate();
        return 0;
    }
    if (type == 0x13) {
        if (((msg->flagsOld ^ msg->flagsNew) & 8) == 0) return 0;
        u32 id = msg->source->GetControlID();
        if (id == 0 || id == 0x279b810) return 0;
        u8 on = (u8)((msg->flagsNew >> 3) & 1);
        if (on) f10 = id;
        else if (f10 == (i32)id) f10 = -1;
        u32 kIds[3] = { 0x279bad0, 0x279bad4, 0 };
        for (const u32* pid = kIds; *pid; ++pid) {
            IWin* c = window->FindWindowByID(*pid, 0);
            if (!c) continue;
            int* tmp1; int* tmp2;
            int* it = *c->ChildBegin(&tmp1);
            if (it != *c->ChildEnd(&tmp2)) {
                int* next;
                do {
                    next = (int*)*it;
                    IWin* ch = ChildOf(it);
                    u8 sel = on && ch->GetControlID() == (u32)f10;
                    ch->SetFlag(1, sel);
                    if (!on && f10 < 0 && ch->GetControlID() == 0x279e540)
                        ch->SetFlag(1, 1);
                    it = next;
                } while (next != *c->ChildEnd(&tmp2));
            }
        }
        return 0;
    }
    return 0;
}
