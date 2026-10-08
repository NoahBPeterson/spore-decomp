// Slice s01079260: SP::cSPUISpace message handler (space-game toolbar buttons / hover glow).
// Optimized module: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE.
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Stub types (offsets / vtable slots recovered from 0x01079260)
// ---------------------------------------------------------------------------
struct Image { char pad[0x1c]; int width; int height; };                       // +0x1c / +0x20

struct RenderContext {
    uint Begin2D(int flags);                                                    // 0x0095bc10 (ret 4)
    void End2D();                                                               // 0x0095bb20
};

struct IObj {                                                                   // generic UI object
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj* Query(uint id);                                               // slot 3 (+0xc)
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint GetFlags();                                                    // slot 8 (+0x20)
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15();
    virtual bool CheckFlag();                                                   // slot 16 (+0x40)
};

struct IWin {                                                                   // window (arg1)
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual IObj* Query(uint id);                                               // slot 3 (+0xc)
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual uint Get30();                                                       // slot 12 (+0x30)
    virtual void s13();
    virtual const float* GetRect();                                             // slot 14 (+0x38)
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40();
    virtual uint GetA4();                                                       // slot 41 (+0xa4)
    virtual uint GetA8();                                                       // slot 42 (+0xa8)
    virtual void s43(); virtual void s44();
    virtual IObj* QueryB4(uint id);                                             // slot 45 (+0xb4)
};

struct Msg {                                                                    // message
    IObj* src;                                                                  // +0
    int pad4;
    uint type;                                                                  // +8
    char pad[0xc];
    RenderContext* ctx;                                                         // +0x18
};

struct ImageSource {                                                            // secondary base at +0xc of Painter
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual Image* GetImage(int which);                                         // slot 4 (+0x10)
};

struct DrawParams { uint a; uint b; uint c; uint d; };

struct Painter {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void Prepare(RenderContext* ctx, const float* rect, const DrawParams* p);   // slot 4 (+0x10)
    int pad4[2];
    ImageSource src;                                                            // +0xc
    float* A830c90(float* tmp, int n);                                          // 0x00830c90 ret 8
    float* A830cc0(float* tmp, int n);                                          // 0x00830cc0 ret 8
    uint   A830c80(int n);                                                      // 0x00830c80 ret 4
    Image* A830cf0(int n);                                                      // 0x00830cf0 ret 4
    float* A830d30(float* tmp, int n);                                          // 0x00830d30 ret 8
    float* A830d60(float* tmp, int n);                                          // 0x00830d60 ret 8
    uint   A830d10(int n);                                                      // 0x00830d10 ret 4
};

struct Item {
    float F1050a60();                                                           // 0x01050a60
    bool  F104feb0();                                                           // 0x0104feb0
    float F0ce6920();                                                           // 0x00ce6920 (fld [ecx+0x1a8])
};
struct Inventory {
    Item* F00ff3fb0(IObj* o);    // 0x00ff3fb0 ret 4
};
struct Game {
    Inventory* GetPlayerInventory();    // 0x00a1ad60
};
struct Comm {
    bool F0ae9390();    // 0x00ae9390
};
struct Marker {
    void F106dcd0(uint id);    // 0x0106dcd0 ret 4
};
struct TSphere {
    bool F00c772c0(uint id);                                                    // 0x00c772c0 ret 4
    void F00c77bf0(uint id);                                                    // 0x00c77bf0 ret 4
};
struct NounMgr {
    TSphere* GetCurrentTerrainSphere();    // 0x00f67d90
};

Game*    SpaceGameGet();                      // 0x01002bd0
Comm*    CommManager();                       // 0x00b3d4a0
NounMgr* NounManager();                       // 0x00b3d300
Marker*  F010666a0();                         // 0x010666a0 (cdecl, no args)
IObj*    F01077b40(IObj* src);                // 0x01077b40 (cdecl)
Painter* F0059ed00(uint v);                   // 0x0059ed00 (cdecl)
uint     GetRecorderState();                  // 0x00435e90
void     KillSetiEffects(uint id, uint arg);  // 0x00435ed0
IObj*    GetSystemAT();                       // 0x00a206f0 (returns global)
void F00805bb0(uint ctxToken, float a, float b, float c, float d, uint e, uint f,
               float g, float h, Image* img, float i);                          // 0x00805bb0 (cdecl, 11 args)

extern float g_UIGlowScale;                   // 0x016e339c

struct UISpace {
    char pad[0x24];
    IWin* mpCurrent;                          // +0x24
    void F1078ec0();                          // 0x01078ec0
    void F1078fa0();                          // 0x01078fa0
    void F1079040(uint index);                // 0x01079040 (ret 4)
    bool F1077900(IObj* o);                   // 0x01077900 (ret 4)
    bool HandleMessage(IWin* win, Msg* msg);  // 0x01079260 (ret 8)
};

// @ 0x01079260
bool UISpace::HandleMessage(IWin* win, Msg* msg)
{
    bool result = false;
    if (msg->type == 0xd) {
        if (mpCurrent != win) {
            IObj* a = win ? win->Query(0x8ed27e7a) : 0;
            IObj* o2 = win->QueryB4(0x600db9c);
            IObj* b = o2 ? o2->Query(0x707459dd) : 0;
            Inventory* inv = SpaceGameGet()->GetPlayerInventory();
            if (a && inv && b) {
                float f = inv->F00ff3fb0(b)->F1050a60() * 0.95f + 0.05f;
                uint8_t flag = (uint8_t)(a->GetFlags() >> 2);
                flag &= 1;
                RenderContext* ctx = msg->ctx;
                Painter* p = F0059ed00(win->GetA8());
                const float* r = win->GetRect();
                float rect[4];
                rect[0] = 0.0f; rect[1] = 0.0f;
                rect[2] = r[2] - r[0]; rect[3] = r[3] - r[1];
                uint v30 = win->Get30();
                DrawParams dp;
                dp.a = 1; dp.b = 0; dp.c = win->GetA4(); dp.d = v30;
                p->Prepare(ctx, rect, &dp);
                float u0, u1;
                if (flag) {
                    u0 = 1.5707964f;
                    u1 = 1.5707964f - g_UIGlowScale * f;
                } else {
                    u1 = 1.5707964f - g_UIGlowScale;
                    u0 = 1.5707964f - g_UIGlowScale * f;
                }
                float hw = (rect[2] - rect[0]) * 0.5f;
                float hh = (rect[3] - rect[1]) * 0.5f;
                ImageSource* is = &p->src;
                Image* img = is->GetImage(4);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830c90(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830cc0(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830c80(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                img = p->A830cf0(0);
                if (img) {
                    float w = (float)img->width;
                    float h = (float)img->height;
                    float t0[2], t1[2];
                    float* q0 = p->A830d30(t0, 4);
                    float x0 = q0[0], y0 = q0[1];
                    float* q1 = p->A830d60(t1, 4);
                    float x1 = q1[0], y1 = q1[1];
                    uint c = p->A830d10(4);
                    uint tok = ctx->Begin2D(0);
                    F00805bb0(tok, x1 + hw, y1 + hh, x0 * w, y0 * h, c, c, u1, u0, img, 0.05f);
                    ctx->End2D();
                }
                result = true;
            }
        }
    } else if (msg->type == 0x287259f6) {
        uint id = msg->src->GetFlags();
        switch (id) {
        case 0x5f72d7c:
            F1078ec0();
            KillSetiEffects(0xa25c8861, GetRecorderState());
            return true;
        case 0x5f72d8a: {
            F1078fa0();
            IObj* at = GetSystemAT();
            KillSetiEffects(0xa25c8861, at ? at->GetFlags() : 0);
            return true;
        }
        case 0x34ef68d:
        case 0x70648eae: {
            IObj* o = F01077b40(msg->src);
            bool ok = F1077900(o);
            IObj* at = GetSystemAT();
            uint v = at ? at->GetFlags() : 0;
            KillSetiEffects(ok ? 0xa9c4342u : 0x42f52773u, v);
            result = true;
            if (ok && o && o->CheckFlag() && !CommManager()->F0ae9390()) {
                Inventory* inv = SpaceGameGet()->GetPlayerInventory();
                if (inv) {
                    Item* it = inv->F00ff3fb0(o);
                    if (it && !it->F104feb0()) {
                        TSphere* ts = NounManager()->GetCurrentTerrainSphere();
                        if (ts && !ts->F00c772c0(0x65fef10)) {
                            ts->F00c77bf0(0x65fef10);
                            F010666a0()->F106dcd0(0x34235299);
                        }
                        if (it->F0ce6920() > 0.0f && ts && !ts->F00c772c0(0x6788f1c)) {
                            ts->F00c77bf0(0x6788f1c);
                            F010666a0()->F106dcd0(0xb396e5bb);
                        }
                    }
                }
            }
            return result;
        }
        default:
            if (id - 0x5f72da0u <= 9u) {
                F1079040(id - 0x5f72da0u);
                KillSetiEffects(0xa25c8861, GetRecorderState());
                return true;
            }
            return false;
        }
    }
    return result;
}
