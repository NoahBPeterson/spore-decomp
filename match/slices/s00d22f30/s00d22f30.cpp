// s00d22f30 -- three __thiscall member functions of the creature / space
// camera object recovered from 0x00d22f30, 0x00d23320 and 0x00d23840.
// Every field touched is named on a real class declaration.  The compiler's
// float constant pool (loaded through absolute addresses) is expressed as
// plain literals / named globals so the relocation masker sees an identical
// operand shape.
//
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          i16;
typedef int            i32;
typedef float          f32;
typedef double         f64;

// Small vector/quad aggregates.  The camera caches whole frames at once, so the
// copies in FUN_00d23840 are modelled as aggregate assignments over the named
// members (the compiler emits 32-bit integer moves for these, as the original
// does).
struct SP_Vector3 { f32 x, y, z; };
struct SP_Vector4 { f32 x, y, z, w; };

// ---------------------------------------------------------------------------
// global camera tuning block (raw game globals)
// ---------------------------------------------------------------------------
extern u8  DAT_01582784;      // 0x01582784  master enable gate
extern u8  DAT_01582785;      // 0x01582785  "accumulate into local anchor" gate
extern f32 DAT_01582788;      // 0x01582788  distance clamp lo
extern f32 DAT_0158278c;      // 0x0158278c  distance clamp hi
extern f32 DAT_01582790;      // 0x01582790  smoothstep amplitude lo
extern f32 DAT_01582794;      // 0x01582794  smoothstep amplitude hi
extern f32 DAT_01582798;      // 0x01582798  secondary amplitude lo
extern f32 DAT_0158279c;      // 0x0158279c  secondary amplitude hi
extern f32 DAT_015827a0;      // 0x015827a0  pitch limit scale
extern f32 DAT_015827f0;      // 0x015827f0  ground clearance

extern f32 DAT_0169deb0;      // 0x0169deb0  terrain basis row 0
extern f32 DAT_0169deb4;      // 0x0169deb4  terrain basis row 1
extern f32 DAT_0169deb8;      // 0x0169deb8  terrain basis row 2
extern f32 DAT_0169df44;      // 0x0169df44  forward basis x
extern f32 DAT_0169df48;      // 0x0169df48  forward basis y
extern f32 DAT_0169df4c;      // 0x0169df4c  forward basis z
extern f32 DAT_0169df50;      // 0x0169df50  right basis x
extern f32 DAT_0169df54;      // 0x0169df54  right basis y
extern f32 DAT_0169df58;      // 0x0169df58  right basis z

extern f32 _HK_REAL_ZERO;     // 0x01485378  Havok 0.0f
extern f32 _HK_REAL_ONE;      // 0x01485720  Havok 1.0f

// ---------------------------------------------------------------------------
// planet model (SP::cPlanetModel) -- only the members used here
// ---------------------------------------------------------------------------
class SP_cPlanetModel {
public:
    u8   mPad_000[0x24];      // 0x00
    void* mpISphere;          // 0x24  terrain sphere interface

    f32  GetRadiusAt(f32* p); // 0xb7ef70
    f32  GetWaterHeight();    // 0xb7e390
};

// ---------------------------------------------------------------------------
// the creature / space camera
// ---------------------------------------------------------------------------
class cCreatureCamera {
public:
    void FUN_00d22f30();                                  // 0x00d22f30
    void FUN_00d23320();                                  // 0x00d23320
    void FUN_00d23840();                                  // 0x00d23840
    f32  FUN_00d20880(f32* p, void* v);                   // 0x00d20880
    void FUN_00d21bc0(f32 a, f32 b, f32 c);               // 0x00d21bc0

    u8  mPad_000[0x1c];       // 0x00
    f32 m01c;                 // 0x1c  pitch cos scale
    f32 m020;                 // 0x20  yaw accumulator
    u8  mPad_024[0x04];       // 0x24
    f32 m028;                 // 0x28  position x
    f32 m02c;                 // 0x2c  position y
    f32 m030;                 // 0x30  position z
    f32 m034;                 // 0x34  pitch
    u8  mPad_038[0x0c];       // 0x38
    f32 m044;                 // 0x44  "attached / cockpit" flag value
    f32 m048;                 // 0x48  accumulated anchor x
    f32 m04c;                 // 0x4c  accumulated anchor y
    f32 m050;                 // 0x50  accumulated anchor z
    f32 m054;                 // 0x54  velocity x
    f32 m058;                 // 0x58  velocity y
    f32 m05c;                 // 0x5c  velocity z
    u8  mPad_060[0x1c];       // 0x60
    f32 m07c;                 // 0x7c  strafe x
    f32 m080;                 // 0x80  strafe y
    f32 m084;                 // 0x84  strafe z
    f32 m088;                 // 0x88  bob x
    f32 m08c;                 // 0x8c  bob y
    f32 m090;                 // 0x90  bob z
    u8  mPad_094[0x18];       // 0x94
    f32 m0ac;                 // 0xac  accel x
    f32 m0b0;                 // 0xb0  accel y
    f32 m0b4;                 // 0xb4  accel z
    u8  mPad_0b8[0x5c];       // 0xb8
    f32 m114;                 // 0x114  desired position x
    f32 m118;                 // 0x118  desired position y
    f32 m11c;                 // 0x11c  desired position z
    u8  mPad_120[0x1c];       // 0x120
    f32 m13c;                 // 0x13c  eye anchor x
    f32 m140;                 // 0x140  eye anchor y
    f32 m144;                 // 0x144  eye anchor z
    u8  mPad_148[0x0c];       // 0x148
    f32 m154;                 // 0x154  orientation / basis x
    f32 m158;                 // 0x158  orientation / basis y
    f32 m15c;                 // 0x15c  orientation / basis z
    f32 m160;                 // 0x160  orientation / basis w
    u8  m164;                 // 0x164  "use +0x168 anchor" flag
    u8  mPad_165[0x03];       // 0x165
    f32 m168;                 // 0x168  alternate anchor x
    f32 m16c;                 // 0x16c  alternate anchor y
    f32 m170;                 // 0x170  alternate anchor z
    u8  mPad_174[0x38];       // 0x174
    f32 m1ac;                 // 0x1ac  cached desired x
    f32 m1b0;                 // 0x1b0  cached desired y
    f32 m1b4;                 // 0x1b4  cached desired z
    f32 m1b8;                 // 0x1b8  cached basis x
    f32 m1bc;                 // 0x1bc  cached basis y
    f32 m1c0;                 // 0x1c0  cached basis z
    f32 m1c4;                 // 0x1c4  cached basis w
    u8  mPad_1c8[0x58];       // 0x1c8
    f32 m220;                 // 0x220  field of view / unit scale
    u8  mPad_224[0x34];       // 0x224
    f32 m258;                 // 0x258  planet water-line angle
    f32 m25c;                 // 0x25c  surface offset angle
    u16 m260;                 // 0x260  state flags
    i16 m262;                 // 0x262  surface-contact counter
    f32 m264;                 // 0x264  orientation basis x
    f32 m268;                 // 0x268  orientation basis y
    f32 m26c;                 // 0x26c  orientation basis z
    f32 m270;                 // 0x270  current radius
    f32 m274;                 // 0x274  basis x row 0
    f32 m278;                 // 0x278  basis y row 0
    f32 m27c;                 // 0x27c  basis z row 0
    f32 m280;                 // 0x280  basis x row 1
    f32 m284;                 // 0x284  basis y row 1
    f32 m288;                 // 0x288  basis z row 1
    f32 m28c;                 // 0x28c  basis x row 2
    f32 m290;                 // 0x290  basis y row 2
    f32 m294;                 // 0x294  basis z row 2
};

// ---------------------------------------------------------------------------
// free helpers
// ---------------------------------------------------------------------------
namespace SP {
    SP_cPlanetModel* PlanetModel();                       // 0xb3d350
    f32* normalized_safe(f32* a, f32* b);                 // 0x449c20
}

extern "C" f32* FUN_0059aed0(void* out, void* basis, void* orient);  // 0x0059aed0

// ===========================================================================
// 0x00d22f30 -- per-frame creature-camera update: pick the smaller of the two
// speed magnitudes, clamp it, run it through a smoothstep and integrate the
// orbit displacement + pitch.
// ===========================================================================
// @ 0x00d22f30
void cCreatureCamera::FUN_00d22f30()
{
    if (DAT_01582784 == 0) {
        m034 = 0.0f;
        return;
    }

    f32 m1 = sqrt((f64)m054 * (f64)m054 + (f64)m058 * (f64)m058 + (f64)m05c * (f64)m05c);
    f32 m2 = sqrt((f64)m0ac * (f64)m0ac + (f64)m0b0 * (f64)m0b0 + (f64)m0b4 * (f64)m0b4);
    f32* pf = &m1;
    if (m2 <= m1)
        pf = &m2;
    f32 v = *pf;
    if (v <= DAT_01582788)
        v = DAT_01582788;
    if (DAT_0158278c <= v)
        v = DAT_0158278c;

    f32 a = m020;
    f32 b = m01c;
    v = (v - DAT_01582788) / (DAT_0158278c - DAT_01582788);
    v = ((3.0f - v * 2.0f) * v) * v;
    f32 s1 = (DAT_01582794 - DAT_01582790) * v + DAT_01582790;
    f32 s2 = (DAT_0158279c - DAT_01582798) * v + DAT_01582798;

    f32 c4 = cos((f64)a * (s1 * 1.9f) + 1.0);
    f32 c7 = cos((f64)a * s1);
    f32 e1 = ((c7 * b) * s2) * s1 + (((c4 * b) * (s1 * 1.9f)) * s2) * 0.5f;

    f32 c4b = cos((f64)a * (s1 * 1.3f) + 0.3);
    f32 c2 = cos((f64)a * (s1 * 2.1f) + 1.2);
    f32 e2 = (((c2 * b) * (s1 * 2.1f)) * s2) * 0.35f
           + (((c4b * b) * (s1 * 1.3f)) * s2) * 0.7f;

    m02c = m02c + m08c * e1;
    m028 = m028 + m088 * e1;
    m030 = m030 + m090 * e1;

    f32 pz = m084 * e2 + m030;
    f32 px = e2 * m07c + m028;
    m028 = px;
    m02c = m080 * e2 + m02c;
    m030 = pz;

    f32 py = m02c;
    f32 lim = s2 * 2.0f;
    f32 len = (px * px + py * py) + pz * pz;
    if (lim * lim < len) {
        lim = lim / sqrt((f64)len);
        m028 = px * lim;
        m02c = py * lim;
        m030 = lim * pz;
    }

    s2 = DAT_015827a0 * s2;
    f32 c2b = cos((f64)m020 * (s1 * 1.7f) + 0.8);
    f32 val = ((c2b * (s1 * 1.7f)) * s2) * m01c + m034;
    m034 = val;
    if (val <= -s2)
        val = -s2;
    if (s2 <= val)
        val = s2;
    m034 = val;

    if (DAT_01582785 != 0) {
        m048 = m028 + m048;
        m04c = m02c + m04c;
        m050 = m030 + m050;
        return;
    }
    m13c = m13c + m028;
    m140 = m02c + m140;
    m144 = m030 + m144;
    m048 = m13c;
    m04c = m140;
    m050 = m144;
}

// ===========================================================================
// 0x00d23320 -- per-frame planet-surface camera projection: build the eye
// frame from the terrain basis, project four sample points (base, radius
// forward, A+C, A-C) onto the globe, keep the highest clearance and
// lift/orthonormalise the resulting orientation/position.
// ===========================================================================
// @ 0x00d23320
void cCreatureCamera::FUN_00d23320()
{
    SP_cPlanetModel* pm = SP::PlanetModel();
    if (pm == 0 || pm->mpISphere == 0)
        return;

    f32 b0 = DAT_0169deb0;
    f32 b1 = DAT_0169deb4;
    f32 b2 = DAT_0169deb8;
    if ((m260 & 2) != 0) {
        b0 = (m274 * DAT_0169deb0 + m280 * DAT_0169deb4) + m28c * DAT_0169deb8;
        b1 = (m278 * DAT_0169deb0 + m284 * DAT_0169deb4) + m290 * DAT_0169deb8;
        b2 = (m27c * DAT_0169deb0 + m288 * DAT_0169deb4) + m294 * DAT_0169deb8;
    }
    f32 rad0 = m270;
    f32 p0x = m264 + rad0 * b0;
    f32 p0y = m268 + rad0 * b1;
    f32 p0z = m26c + rad0 * b2;
    f32 ang = m25c;

    f32 fx = DAT_0169df44;
    f32 fy = DAT_0169df48;
    f32 fz = DAT_0169df4c;
    if ((m260 & 2) != 0) {
        fx = (m274 * DAT_0169df44 + m280 * DAT_0169df48) + m28c * DAT_0169df4c;
        fy = (m278 * DAT_0169df44 + m284 * DAT_0169df48) + m290 * DAT_0169df4c;
        fz = (m27c * DAT_0169df44 + m288 * DAT_0169df48) + m294 * DAT_0169df4c;
    }
    f32 rad1 = m270;

    f32 rx = DAT_0169df50;
    f32 ry = DAT_0169df54;
    f32 rz = DAT_0169df58;
    if ((m260 & 2) != 0) {
        rx = (m274 * DAT_0169df50 + m280 * DAT_0169df54) + m28c * DAT_0169df58;
        ry = (m278 * DAT_0169df50 + m284 * DAT_0169df54) + m290 * DAT_0169df58;
        f32 t = m27c * DAT_0169df50 + m288 * DAT_0169df54;
        rz = t + m294 * DAT_0169df58;
    }
    f32 rad2 = m270;

    f32 unit = m220;
    f32 tanf = tan((f64)m258);
    f32 scale = (f32)((f64)tanf * (f64)unit);

    f32 ax = (rad0 * fx) * unit + p0x;
    f32 ay = (rad0 * fy) * unit + p0y;
    f32 az = (rad0 * fz) * unit + p0z;

    f32 cx = (rx * rad1) * scale;
    f32 cy = (ry * rad2) * scale;
    f32 cz = (rz * rad2) * scale;

    f32 bx = cx + ax;
    f32 by = cy + ay;
    f32 bz = cz + az;
    cx = ax - cx;
    cy = ay - cy;
    cz = az - cz;

    f32 h0 = pm->GetRadiusAt(&p0x);
    f32 h1 = pm->GetRadiusAt(&ax);
    f32 w  = pm->GetWaterHeight();
    if (h1 < w)
        h1 = w;
    f32 h2 = pm->GetRadiusAt(&bx);
    if (h2 < w)
        h2 = w;
    f32 h3 = pm->GetRadiusAt(&cx);
    if (h3 < w)
        h3 = w;

    f32* pa = (h3 > h2) ? &h3 : &h2;
    f32* pb = (h1 > h0) ? &h1 : &h0;
    if (*pb <= *pa && *pa != *pb)
        pb = pa;

    ang = tan((f64)ang) * (f64)m220 + (f64)*pb + DAT_015827f0;

    if ((f64)p0z * (f64)p0z + ((f64)p0y * (f64)p0y + (f64)p0x * (f64)p0x) < (f64)ang * (f64)ang) {
        f32* n = SP::normalized_safe(&cx, &p0x);
        f32 nx = n[0];
        f32 ny = n[1];
        f32 nz = n[2];
        m260 = (u16)(m260 | 4);
        m264 = nx * ang;
        m262 = (i16)(m262 + 1);
        m268 = ny * ang;
        m26c = nz * ang;
    }
}

// ===========================================================================
// 0x00d23840 -- creature-camera eye update: blend the currently selected
// anchor with the orientation-scaled sample, cache the desired/basis frame
// when "attached", then push the resulting radius to the camera solver.
// ===========================================================================
// @ 0x00d23840
void cCreatureCamera::FUN_00d23840()
{
    f32* pa = (m164 != 0) ? &m168 : &m13c;
    f32 vx = pa[0];
    f32 vy = pa[1];
    f32 vz = pa[2];

    f32 tmp[3];
    f32* pf = FUN_0059aed0(tmp, &DAT_0169df44, &m154);

    f32 f = sqrt(((f64)m114 - (f64)m13c) * ((f64)m114 - (f64)m13c)
               + ((f64)m118 - (f64)m140) * ((f64)m118 - (f64)m140)
               + ((f64)m11c - (f64)m144) * ((f64)m11c - (f64)m144));

    vx = pf[0] * f + vx;
    vy = pf[1] * f + vy;
    vz = pf[2] * f + vz;

    f32 val = f;
    if (m044 > _HK_REAL_ZERO) {
        // cache the desired position and the orientation frame
        *(SP_Vector3 *)&m1ac = *(SP_Vector3 *)&m114;
        *(SP_Vector4 *)&m1b8 = *(SP_Vector4 *)&m154;
    } else {
        val = FUN_00d20880(&vx, &m154);
    }
    FUN_00d21bc0(0.0f, 0.0f, val);
}