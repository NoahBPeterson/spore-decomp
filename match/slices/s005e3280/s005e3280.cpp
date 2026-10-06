#include "types.h"
#include <math.h>

// Slice s005e3280: SP::cSPEditorVerbIcon (per-frame Update, transition and Disappear).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
// Offsets are RETAIL offsets (the 2008 PDB layout differs from retail in this class).

// UI window stub: vtable slots used by the icon (0x34 = 13, 0x7c = 31, 0x90 = 36).
struct IWin {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual void Slot13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30();
    virtual void SetVisibleFlags(int a, int b);   // slot 31 (+0x7c)
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void Slot36();                        // slot 36 (+0x90)
};

namespace SPUIHelpers {
    void SetWindowAlpha(IWin* w, float a);
    void SetWindowScale(IWin* w, float s);
}
namespace UI { namespace cWindowTransform { void SetScale(IWin* w, float x, float y); } }
float FUN_00805040(IWin* w);
float FUN_00805200(IWin* w);
float FUN_00805230(IWin* w);

// Audio
struct AudioSystemAT { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                       virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
                       virtual int GetId(); };
AudioSystemAT* GetSystemAT();
void KillSetiEffects(unsigned int id, int a);

// Linear interpolation value (5 floats).
struct LinInterp {
    float target, cur, elapsed, start, dur;
    bool IsDone() { return cur == target && elapsed >= dur; }
    void Update(float dt)
    {
        if (!IsDone()) {
            elapsed = elapsed + dt;
            if (elapsed >= dur) {
                cur = target;
                elapsed = dur;
            } else {
                cur = (elapsed / dur) * (target - start) + start;
            }
        }
    }
};

struct LinInterp2 : LinInterp {
    void Update(float dt)
    {
        if (!IsDone()) {
            elapsed = dt + elapsed;
            if (elapsed >= dur) {
                cur = target;
                elapsed = dur;
            } else {
                cur = (elapsed / dur) * (target - start) + start;
            }
        }
    }
};

// Overshooting scale interpolation (0x1c bytes), updated out of line.
struct ScaleInterp {
    float target, cur, elapsed, start, dur, f5, f6;
    bool IsDone() { return cur == target && elapsed >= dur; }
    void Update(float dt);        // 0x5e1d00
};
struct AlphaInterp {              // 0x20 bytes, updated out of line (0x5e1e90)
    float target, f1, cur, elapsed, f4, f5, f6, dur;
    bool IsDone() { return cur == target && elapsed >= dur; }
    void Update(float dt);
};
// Three-segment interpolation (0x20 bytes).
struct MidInterp {
    float target, mid, cur, elapsed, start, t1, t2, dur, pad;
    bool IsDone() { return cur == target && elapsed >= dur; }
    void Update(float dt)
    {
        if (!IsDone()) {
            float t = dt + elapsed;
            elapsed = t;
            if (t >= dur) {
                cur = target;
                elapsed = dur;
            } else {
                float u = t / dur;
                if (u < t1) {
                    cur = (mid - start) * (u / t1) + start;
                } else if (u > t2) {
                    cur = ((u - t2) / (1.0f - t2)) * (target - mid) + mid;
                } else {
                    cur = mid;
                }
            }
        }
    }
};
// Oscillating alpha (0x14 bytes).
struct FlashInterp {
    float target, cur, elapsed, dur, speed;
    bool IsDone() { return cur == target && elapsed >= dur; }
    void Update(float dt)
    {
        if (!IsDone()) {
            float t = elapsed + dt;
            elapsed = t;
            if (t >= dur) {
                cur = target;
                elapsed = dur;
            } else {
                cur = ((float)sin(speed * t) + 1.0f) * 0.5f;
            }
        }
    }
};

static inline const float& MaxRef(const float& a, const float& b) { return a < b ? b : a; }

static inline float ClampF(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct VerbIcon {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void SetUpgradeScale(float v);        // slot 14 (+0x38)

    char pad04[0x0c];
    IWin* win10;          // +0x10
    IWin* win14;          // +0x14
    IWin* win18;          // +0x18
    char pad1c[4];
    IWin* win20;          // +0x20
    char pad24[4];
    void* img28;          // +0x28
    char pad2c[0x64 - 0x2c];
    int state;            // +0x64
    bool active;          // +0x68
    bool animate;         // +0x69
    char pad6a[7];
    bool chargeOn;        // +0x71
    char pad72[2];
    unsigned int key;     // +0x74
    char pad78[0x98 - 0x78];
    LinInterp charge;     // +0x98
    ScaleInterp sa;       // +0xac
    ScaleInterp sb;       // +0xc8
    LinInterp2 upg;        // +0xe4
    ScaleInterp sc;       // +0xf8
    AlphaInterp al;       // +0x114
    MidInterp mid;        // +0x134
    FlashInterp flash;    // +0x158

    bool Update(unsigned int dtMs);
    void EndCharge();                // 0x5e2e50
    void EndFlashing();              // 0x5e3180
    void FUN_005e2ce0();
    void FUN_005e3920();
    void FUN_005e3d40();
    void Disappear();
};

// @ 0x005e3280
bool VerbIcon::Update(unsigned int dtMs)
{
    bool result = false;
    float dt = ClampF((float)dtMs * 0.001f, 0.0f, 0.1f);

    if (chargeOn && !charge.IsDone()) {
        charge.Update(dt);
        if (win18)
            win18->Slot36();
        if (charge.IsDone())
            EndCharge();
    }

    if (img28 && !flash.IsDone()) {
        flash.Update(dt);
        if (img28)
            SPUIHelpers::SetWindowAlpha((IWin*)img28, flash.cur);
        if (flash.IsDone())
            EndFlashing();
    }

    if (active) {
        if (win10)
            win10->Slot13();
        if (animate) {
            if (!(sa.IsDone() && sb.IsDone())) {
                sa.Update(dt);
                sb.Update(dt);
                if (win10)
                    UI::cWindowTransform::SetScale(win10, fabsf(sa.cur), fabsf(sb.cur));
                if (sa.IsDone() && sb.IsDone()) {
                    if (state == 0)
                        FUN_005e2ce0();
                    if (state == 2)
                        state = 3;
                }
                result = true;
            }
        }
        if (!mid.IsDone()) {
            mid.Update(dt);
            SPUIHelpers::SetWindowAlpha(win10, mid.cur);
        }
        if (!upg.IsDone()) {
            upg.Update(dt);
            if (state == 4 || state == 5) {
                if (state == 4) {
                    AudioSystemAT* at = GetSystemAT();
                    KillSetiEffects(0xdf9a2ce0, at ? at->GetId() : 0);
                } else {
                    AudioSystemAT* at = GetSystemAT();
                    KillSetiEffects(0x89770505, at ? at->GetId() : 0);
                }
                if (animate)
                    SetUpgradeScale(upg.cur);
                if (upg.IsDone())
                    state = 3;
            }
        }
        if (animate) {
            if (!sc.IsDone()) {
                sc.Update(dt);
                if (win14)
                    SPUIHelpers::SetWindowScale(win14, fabsf(sc.cur));
                if (win20)
                    SPUIHelpers::SetWindowScale(win20, fabsf(sc.cur) * 0.75f);
            }
        }
        if (animate) {
            if (!al.IsDone()) {
                al.Update(dt);
                SPUIHelpers::SetWindowAlpha(win20, al.cur);
            }
        }
    }
    return result;
}

// @ 0x005e3920
void VerbIcon::FUN_005e3920()
{
    if (active) {
        bool all = false;
        bool flag = false;
        if (sa.target == 0.08f || sb.target == 0.08f) {
            flag = true;
            if (sb.IsDone() && sa.IsDone()) {
                all = flag;
                SPUIHelpers::SetWindowAlpha(win10, 0.0f);
            }
        }
        float f = 0.0f;
        if (!all) {
            f = MaxRef(sa.elapsed, sb.elapsed);
            if (flag)
                f = 0.7f - f;
        }
        if (!animate)
            return;
        win10->SetVisibleFlags(1, 1);
        if (key == 0xe816f049 || key == 0x3eb432) {
            if (all) {
                UI::cWindowTransform::SetScale(win10, 0.08f, 1.0f);
                sa.start = 0.08f;
                sa.cur = 0.08f;
                sa.dur = 0.7f;
                sa.f5 = 0.1f;
                sa.f6 = 0.5f;
                sa.target = 1.0f;
                sa.elapsed = 0.0f;
                sb.start = 1.0f;
                sb.cur = 1.0f;
                sb.target = 1.0f;
            } else {
                sa.elapsed = f;
                sa.target = 1.0f;
                sa.start = 0.08f;
                sb.start = 1.0f;
                sb.cur = 1.0f;
                sb.target = 1.0f;
            }
            sb.f6 = 0.0f;
            sb.f5 = 0.0f;
            sb.dur = 0.0f;
            sb.elapsed = 0.0f;
        } else {
            if (all) {
                UI::cWindowTransform::SetScale(win10, 1.0f, 0.08f);
                sa.start = 1.0f;
                sa.cur = 1.0f;
                sa.target = 1.0f;
                sa.dur = 0.0f;
                sa.f5 = 0.0f;
                sa.f6 = 0.0f;
                sa.elapsed = 0.0f;
                sb.target = 1.0f;
                sb.dur = 0.7f;
                sb.f5 = 0.1f;
                sb.start = 0.08f;
                sb.cur = 0.08f;
                sb.f6 = 0.5f;
                sb.elapsed = 0.0f;
            } else {
                sa.start = 1.0f;
                sa.cur = 1.0f;
                sa.target = 1.0f;
                sa.dur = 0.0f;
                sa.f5 = 0.0f;
                sa.f6 = 0.0f;
                sa.elapsed = 0.0f;
            }
        }
        float g = FUN_00805040(win10);
        if (all) {
            mid.start = g;
            mid.cur = g;
            mid.mid = 1.0f;
            mid.target = 1.0f;
            mid.dur = 0.7f;
            mid.t1 = 0.75f;
            mid.t2 = 0.75f;
            mid.elapsed = 0.0f;
        } else {
            mid.target = 1.0f;
            mid.mid = 1.0f;
            mid.elapsed = f;
            mid.start = 0.0f;
        }
    } else {
        state = 3;
        if (animate && win10)
            win10->SetVisibleFlags(1, 1);
    }
}

// @ 0x005e3d40  (matched): set state then tail-call the transition update.
void VerbIcon::FUN_005e3d40()
{
    state = 2;
    FUN_005e3920();
}

// @ 0x005e3d50  SP::cSPEditorVerbIcon::Disappear
void VerbIcon::Disappear()
{
    if (active) {
        bool all = false;
        bool flag = false;
        if (sa.target == 1.0f || sb.target == 1.0f) {
            flag = true;
            if (sb.IsDone() && sa.IsDone())
                all = flag;
        }
        float f = 0.0f;
        if (!all) {
            f = MaxRef(sa.elapsed, sb.elapsed);
            if (flag)
                f = 0.7f - f;
        }
        state = 0;
        if (animate) {
            float a = win10 ? FUN_00805200(win10) : 1.0f;
            float b = win10 ? FUN_00805230(win10) : 1.0f;
            if (key == 0xe816f049 || key == 0x3eb432) {
                if (all) {
                    sa.start = a;
                    sa.cur = a;
                    sa.target = 0.08f;
                    sa.f5 = 0.1f;
                    sa.dur = 0.7f;
                    sa.f6 = 0.5f;
                    sa.elapsed = 0.0f;
                } else {
                    sa.target = 0.08f;
                    sa.elapsed = f;
                    sa.start = 1.0f;
                }
                sb.f6 = 0.0f;
                sb.f5 = 0.0f;
                sb.dur = 0.0f;
                sb.target = b;
                sb.cur = b;
                sb.start = b;
                sb.elapsed = 0.0f;
            } else if (all) {
                sa.start = a;
                sa.cur = a;
                sa.target = a;
                sa.dur = 0.0f;
                sa.f5 = 0.0f;
                sa.f6 = 0.0f;
                sa.elapsed = 0.0f;
                sb.start = b;
                sb.cur = b;
                sb.target = 0.08f;
                sb.f5 = 0.1f;
                sb.dur = 0.7f;
                sb.f6 = 0.5f;
                sb.elapsed = 0.0f;
            } else {
                sb.target = 0.08f;
                sb.elapsed = f;
                sa.start = a;
                sa.cur = a;
                sa.target = a;
                sa.dur = 0.0f;
                sa.f5 = 0.0f;
                sa.f6 = 0.0f;
                sa.elapsed = 0.0f;
            }
            float g = FUN_00805040(win10);
            if (all) {
                mid.start = g;
                mid.cur = g;
                mid.mid = 1.0f;
                mid.t1 = 0.25f;
                mid.t2 = 0.25f;
                mid.target = 0.0f;
                mid.dur = 0.7f;
                mid.elapsed = 0.0f;
            } else {
                mid.target = 0.0f;
                mid.mid = 1.0f;
                mid.elapsed = f;
                mid.start = 1.0f;
            }
        }
        if (all) {
            float t = upg.cur;
            upg.start = t;
            upg.cur = t;
            upg.target = 0.0f;
            upg.dur = 0.7f;
            upg.elapsed = 0.0f;
        } else {
            upg.target = 0.0f;
            upg.elapsed = f;
        }
    } else {
        state = 1;
        if (animate && win10)
            win10->SetVisibleFlags(1, 0);
    }
}
