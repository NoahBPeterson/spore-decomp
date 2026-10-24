// Slice s009d46d0: camera follow/blend update (0x009d49b0), a float-heavy per-frame routine.
// Two paths: a "constrained" path (when the global enable flag and both targets are set) and a
// plain path driven by the Bias() easing helper. Both end by blending an orbit offset into the
// camera position with sin/cos of an accumulated angle (this+0xec).
// /O2 /arch:SSE /fp:fast (scalar SSE for float math, x87 for sin/cos/pow).
#include "types.h"
#include <math.h>

// ---- tunables (.data) ----
extern int   g_15515dc;      // path-1 enable
extern char  g_1551256;      // "damp" flag
extern float g_155125c;      // 100.0
extern float g_155151c;      // 2.5
extern float g_1551258;      // 1e-12 (min squared length)
extern float g_1551518;      // 1.2
extern float g_1551510;      // 1.2
extern float g_1551514;      // 2.5
extern float g_1551458;      // pi/2
extern float g_15514e0;      // 1.0 (extent scale)

struct Vec3 { float x, y, z; };

// Callees (calling conventions checked at the call sites).
float FUN_009a49b0(const Vec3* v);                                        // cdecl, returns |v|^2 in st0
float FUN_009cdbe0(float x, float a, float b, float c, float d);          // cdecl, 5 floats, returns st0

// Register-convention helpers of this TU (static, so cl picks the register conventions).
static __declspec(noinline) float Sign(float x)                  // 0x009cddc0: arg in xmm1, result in xmm0
{
    if (1e-6f > x) return -1.0f;
    if (x > 1e-6f) return 1.0f;
    return 0.0f;
}
static __declspec(noinline) float Bias(float a, float b)         // 0x009cdb20: stack args, result in xmm0
{
    float r;
    if (fabs(b) < 1.0f) {
        r = (a * b - b + 1.0f) * a;
    } else if (0.0f > b) {
        r = (float)(1.0 - pow((double)(1.0f - a), pow(2.0, (double)-b)));
    } else {
        r = (float)pow((double)a, pow(2.0, (double)b));
    }
    if (!(r > 0.0f)) return 0.0f;
    if (r > 1.0f) return 1.0f;
    return r;
}

// Sub-object at obj+0x15b8: its method at 0x009d3530 returns max(|f64|*scale, |(f4c,f50,f54)|).
struct ExtentSrc { float sub_9d3530(); };       // thiscall, st0

struct Rec { char pad[0x138]; float f138; float f13c; char pad2[0x468 - 0x140]; };   // 0x468 bytes
struct Q { char pad[0x384]; Rec* recs; };
struct Arr108 { char* b; char* e; };
struct Obj {
    Q* q;
    char pad04[0x15b8 - 4];
    char ext[0x24];                // 0x15b8: ExtentSrc
    Arr108 arr;                    // 0x15dc
    char pad15e4[0x1604 - 0x15e4];
    float f1604, f1608, f160c;
    char pad1610[0x161c - 0x1610];
    float f161c;
    char pad1620[0x1638 - 0x1620];
    float f1638;
};
struct Params {
    char pad00[0x7c];
    float f7c, f80, f84, f88;
    char pad8c[4];
    float f90, f94, f98;
    char pad9c[0xa4 - 0x9c];
    float fa4;                     // 0xa4 zoom scale
    char padA8[0xf8 - 0xa8];
    float ff8;
};

struct Cam {
    float x, y, z;                 // 0x00
    char pad0c[0x0c];
    float px, py, pz;              // 0x18
    char pad24[0x58 - 0x24];
    int idx;                       // 0x58
    char pad5c[0x64 - 0x5c];
    void* p64; void* p68;          // 0x64
    char pad6c[0x78 - 0x6c];
    float f78, f7c, f80, f84;      // 0x78
    char pad88[0xb4 - 0x88];
    Vec3 fb4;                      // 0xb4  orbit velocity result
    float fc0; float pad_c4; Obj* obj; float pad_cc;   // 0xc0
    Vec3 d;                        // 0xd0
    Vec3 off;                      // 0xdc
    float fe8, fec, ff0, ff4, ff8, ffc;                // 0xe8
    float f100, f104;              // 0x100 zoom range

    Vec3* sub_9cede0(Vec3* out, float t);            // thiscall, ret 8
    float sub_9cf740(Params* p, float ext);          // thiscall, ret 8, st0
    void Update(Params* p, int unused, float t);     // @ 0x009d49b0, ret 0xc
    void UpdateOrbit(Params* p);                     // @ 0x009d46d0, ret 4
    void UpdateSpin(Params* p, float step, float blend, float spinRate,
                    float driveX, float driveY, float driveZ);        // @ 0x009d52f0
};

// @ 0x009d49b0
void Cam::Update(Params* p, int unused, float t) {
    (void)unused;
    float v1c, v20, v24;
    if (g_15515dc && p64 && p68) {
        v1c = f7c; v20 = f80; v24 = f84;
        Vec3 out;
        sub_9cede0(&out, (1.0f - f78) * g_155125c * t);
        float ext = ((ExtentSrc*)obj->ext)->sub_9d3530();
        float r = sub_9cf740(p, ext);
        ff4 = r;
        float f7s = f7c;
        v24 = r * out.z + v24;
        float s = (1e-6f > f7c) ? -1.0f : ((f7c > 1e-6f) ? 1.0f : 0.0f);
        float fx = s * r * out.x + v1c;
        float mod = 1.0f;
        if (g_1551256)
            mod = 1.0f - FUN_009cdbe0(ext, 0.0f, g_155151c, 0.0f, 1.0f) * fc0;
        float pf8 = p->ff8;
        v1c = (fx - pf8) * p->f84 * mod + pf8;
        Arr108* arr = &obj->arr;
        if (arr && ((int)(arr->e - arr->b)) / 0x108 == 2) {
            Rec* rec = obj->q->recs + idx;
            float r13c = rec->f13c;
            float dd = fabs(f7s) - rec->f138;
            if (dd > 1e-6f) {
                float q = r13c / dd;
                if (q <= 1.0f) {
                    float l2 = FUN_009a49b0(&d);
                    if (l2 > g_1551258) {
                        float xx = d.x;
                        float w = (float)(fabs((double)xx) / sqrt((double)l2));
                        float sg = Sign(f7s);
                        if (dd > 1e-6f) sg = xx / dd * sg;
                        if (!(sg > -1.0f)) sg = -1.0f;
                        else if (sg > 1.0f) sg = 1.0f;
                        v20 = v20 - sg * g_1551518 * w * r13c;
                    }
                }
            }
        }
        double c = cos((double)(t * 3.1415927f));   // stays in st0 (not rounded to float) in the original
        float dpos = out.y - ff8;
        off.y = d.y * dpos + off.y;
        off.x = dpos * d.x + off.x;
        off.z = off.z + d.z * dpos;
        ff8 = out.y;
        fec = (float)((c - ffc) * fe8 + fec);
        float v = *(volatile float*)&fec;   // reloaded from memory (rounded to float) for sin/cos
        ffc = (float)c;
        float sn = (float)sin((double)v);
        float cs = (float)cos((double)v);
        float ox = off.x + v1c;
        float oy = off.y + v20;
        float oz = off.z + v24;
        float vt = v * t;
        float it = 1.0f - t;
        x = px * it + (cs * ox - sn * oy);
        y = py * it + (cs * oy + sn * ox);
        z = pz * it + oz;
        ff0 = ff0 * it + vt;
    } else {
        v1c = f7c; v20 = f80; v24 = f84;
        float a1 = Bias(t, p->f90);
        float p88 = p->f88;
        float a2 = Bias(t, p->f94);
        float sA = (float)sin((double)(((a2 - 0.5f) * p88 + 0.5f) * 3.1415927f));
        float cB = (float)cos((double)(((a1 - 0.5f) * p88 + 0.5f) * 3.1415927f));
        float o2c = cB + p->f98 * sA;
        float ca = (float)cos((double)(a1 * 3.1415927f));
        float ext2;
        {
            Obj* o = obj;
            float a = (float)fabs((double)o->f161c) * g_15514e0;
            float len = (float)sqrt((double)(o->f1604 * o->f1604 + o->f1608 * o->f1608 + o->f160c * o->f160c));
            ext2 = (a > len) ? a : len;
        }
        float r = sub_9cf740(p, ext2);
        ff4 = r;
        float c88 = (float)cos((double)(p88 * 1.5707964f));
        float q = (sA - c88) / (1.0f - c88) * r;
        v24 = v24 + q;
        float s = (1e-6f > v1c) ? -1.0f : ((v1c > 1e-6f) ? 1.0f : 0.0f);
        float p80 = p->f80;
        float e;
        if (!(p80 < t))
            e = (float)sin((double)(g_1551458 / p80 * t));
        else
            e = (float)cos((double)((t - p80) / (1.0f - p80) * g_1551458));
        float vx = p->f7c * e * e * s * q + v1c;
        float mod = 1.0f;
        if (g_1551256)
            mod = 1.0f - FUN_009cdbe0(ext2, 0.0f, g_1551514, 0.0f, 1.0f) * fc0;
        float pf8 = p->ff8;
        vx = (vx - pf8) * p->f84 * mod + pf8;
        float dpos = o2c - ff8;
        off.x = dpos * d.x + off.x;
        off.y = d.y * dpos + off.y;
        off.z = off.z + d.z * dpos;
        ff8 = o2c;
        Arr108* arr = &obj->arr;
        if (arr && ((int)(arr->e - arr->b)) / 0x108 == 2) {
            Rec* rec = obj->q->recs + idx;
            float r13c = rec->f13c;
            float dd = fabs(f7c) - rec->f138;
            if (dd > 1e-6f) {
                float qq = r13c / dd;
                if (qq <= 1.0f) {
                    if (fabs(d.x) > fabs(d.y)) {
                        float sg = Sign(f7c);
                        if (dd > 1e-6f) sg = d.x / dd * sg;
                        if (!(sg > -1.0f)) sg = -1.0f;
                        else if (sg > 1.0f) sg = 1.0f;
                        v20 = v20 - sg * r13c * g_1551510;
                    }
                }
            }
        }
        float v = (ca - ffc) * fe8 + fec;
        ffc = ca;
        fec = v;
        float sn = (float)sin((double)v);
        float cs = (float)cos((double)v);
        float oz = (off.z + v24) * t;
        float ox = off.x + vx;
        float oy = off.y + v20;
        float vt = v * t;
        float it = 1.0f - t;
        float X = cs * ox - sn * oy;
        float Y = cs * oy + sn * ox;
        x = X * t + x * it;
        y = Y * t + y * it;
        z = oz + z * it;
        ff0 = ff0 * it + vt;
    }
}

// ---- 009d46d0: orbit-velocity update driven by the target's phase parameters ----------------
// The "ease" of a phase parameter: values inside [-1,1) are shifted to [0,2), negative values
// past -1 clamp to 0 and positive values past 1 are squared.
static __forceinline float EasePhase(float x)
{
    if (fabs(x) < 1.0f)
        return x + 1.0f;
    if (0.0f <= x)
        return (float)pow((double)x, 2.0);
    return 0.0f;
}

// @ 0x009d46d0
void Cam::UpdateOrbit(Params* p)
{
    if (g_15515dc && p64 && p68) {
        Vec3 out;
        sub_9cede0(&out, (1.0f - f78) * g_155125c);
        float ex = d.x * out.x;
        float ey = d.y * (out.y - -1.0f);
        py = ey;
        pz = d.z * out.z;
        px = ex;
        float s = sin(fec);
        float c = cos(fec);
        px = ex * c + ey * s;
        py = ey * c - ex * s;
        pz = pz;
    }

    float phaseA = EasePhase(p->f94);
    float phaseB = EasePhase(p->f90);

    double ang = ((p->f88 + 1.0f) * 0.5f) * 3.1415927;
    float lift = (float)(cos(ang) * p->f88) * phaseA;
    float swerve = -((float)(sin(ang) * p->f88) * phaseB);

    float extFlag = fabs(obj->f161c) * g_15514e0;
    float extPos = sqrt(obj->f1604 * obj->f1604 + obj->f1608 * obj->f1608 +
                        obj->f160c * obj->f160c);
    float extent = (extFlag <= extPos) ? extPos : extFlag;
    float radius = sub_9cf740(p, extent);
    ff4 = radius;

    swerve = p->f98 * lift + swerve;

    float halfTurn = cos(p->f88 * 1.5707964f);
    float scale = (1.0f / (f104 - f100)) * p->fa4;
    fb4.x = (d.x * swerve) * scale;
    fb4.y = (d.y * swerve) * scale;
    fb4.z = (d.z * swerve + (radius / (1.0f - halfTurn)) * lift) * scale;
}

// ---- 009d52f0: spin/dead-stop update --------------------------------------------------------
// Global tuning flags shared with the camera driver.
extern char g_166c6b0;       // force full damping
extern char g_166c6b1;       // freeze the spin

// @ 0x009d52f0
void Cam::UpdateSpin(Params* p, float step, float blend, float spinRate,
                     float driveX, float driveY, float driveZ)
{
    float scale = obj->f1638;
    float spin = (scale * step) * spinRate;
    float s = sin(spin);
    float c = cos(spin);

    float ox = px;
    float oy = py;
    px = (py * s + px * c) - (driveX * step) * scale;
    py = (py * c - ox * s) - (driveY * step) * scale;
    pz = f84 - (driveZ * step) * scale;

    float damp = 1.0f;
    if (g_166c6b1)
        damp = 0.0f;
    if (g_166c6b0)
        damp = 1.0f;
    if (!g_166c6b1 && !g_166c6b0) {
        static const float s_spinMin = 0.349f;
        static const float s_spinMax = 1.395f;
        damp = FUN_009cdbe0(fabs(ff0), s_spinMin, s_spinMax, 1.0f, 0.0f);
    }
    ff0 = ff0 - damp * spin;

    if (g_15515dc && p64 && p68) {
        Vec3 out;
        float one = 1.0f;
        sub_9cede0(&out, (one - (one - blend) * f78) * g_155125c);

        float ext = ((ExtentSrc*)obj->ext)->sub_9d3530();
        float radius = sub_9cf740(p, ext);
        ff4 = radius;

        x = x - px;
        y = y - py;
        z = z - pz;

        float sign;
        if (1e-6f <= f7c) {
            if (f7c <= 1e-6f)
                sign = 0.0f;
            else
                sign = 1.0f;
        } else {
            sign = -1.0f;
        }
        out.x = (radius * sign) * out.x;

        float fy = ((out.y - blend * 2.0f) + 1.0f) * d.y;
        py = fy * c - out.x * s;
        pz = pz;
        float fx = out.x * c + fy * s;
        px = fx;
        x = fx + x;
        y = py + y;
        z = (out.z * ff4 + pz) + z;
    }
}
