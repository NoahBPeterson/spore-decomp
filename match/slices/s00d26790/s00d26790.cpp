// ===========================================================================
// slice s00d26790 -- SPStarManager.obj camera / view-transform cluster.
// Reconstructed from work/SporeApp.analysis.bin.
//
//   0x00d26790  cCamView::FUN_00d26790   camera-follow / view refresh
//   0x00d26bb0  cCamView::FUN_00d26bb0   one-time lazy init
//   0x00d26c90  cCamView::FUN_00d26c90   rebuild the world transform
//   0x00d26ed0  cCamView::FUN_00d26ed0   apply a pose + clamp a distance
//   0x00d270a0  cCamView::FUN_00d270a0   fetch the eye point (with translation)
//   0x00d271d0  cCamView::FUN_00d271d0   fetch the eye point (untranslated)
//   0x00d272e0  cCamView::FUN_00d272e0   op-mode toggle
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
// ===========================================================================

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#pragma warning(disable: 4100 4189 4244 4311 4312 4244)

#include <math.h>

// ---- free / runtime callees ----------------------------------------------
void* FUN_00883860();                                // 0x00883860
void* FUN_00d2e340();                                // 0x00d2e340
void* FUN_00d21d10(void* pA, void* pB, void* pC, float f);   // 0x00d21d10
void* FUN_0067dcc0();                                // 0x0067dcc0
void  FUN_00421cf0(void* p);                         // 0x00421cf0
void* FUN_0041cb40(void* pOut, void* pArg);          // 0x0041cb40
void* FUN_0059c190(void* pOut, void* pArg);          // 0x0059c190
void  FUN_0040ccb0(void* pOut, void* pArg);          // 0x0040ccb0
void* FUN_00537dc0(void* pSelf, void* pArg);         // 0x00537dc0
void* FUN_0059aed0(void* pOut, void* pA, void* pB);  // 0x0059aed0
bool  FUN_00c0b770(void* pSelf);                     // 0x00c0b770
void* FUN_00b3d300();                                // 0x00b3d300  (global manager E)

// ---- thiscall callees (ecx = the receiver passed as pSelf) ----------------
struct CalleeSet {
    void  FUN_00d38840();                            // 0x00d38840
    void  FUN_00d247f0();                            // 0x00d247f0
    void  FUN_00d21d90();                            // 0x00d21d90
    void  FUN_00d21b10(float a, float b, float c);   // 0x00d21b10
    void  FUN_00d26c90();                            // 0x00d26c90
    void  FUN_00d100b0(int a, int b);                // 0x00d100b0
    void  FUN_00d263d0(int n);                       // 0x00d263d0
};
void  FUN_00d266c0(void* pOut, void* pIn);           // 0x00d266c0
void  FUN_00d265c0(void* pIn, float f);              // 0x00d265c0
#define SELF(o) ((CalleeSet*)(o))

// global manager E helper (0xb1fdb0 is a thiscall on the 0xb3d300 result)
struct MgrE { void* FUN_00b1fdb0(); };               // 0x00b1fdb0
#define SELFE(o) ((MgrE*)(o))

// ---- vtable dispatch through a member pointer (thiscall) ------------------
struct VtblObj {
    void  C0(); void  C1(void*); void  C2(void*, void*); void  C3(void*, void*, void*);
    void* R0(); void* R1(void*); void* R2(void*, void*); void* R3(void*, void*, void*);
    u8    B0();
};
typedef void  (VtblObj::*PMF0)();
typedef void  (VtblObj::*PMF1)(void*);
typedef void  (VtblObj::*PMF2)(void*, void*);
typedef void  (VtblObj::*PMF3)(void*, void*, void*);
typedef void* (VtblObj::*PMR0)();
typedef void* (VtblObj::*PMR1)(void*);
typedef void* (VtblObj::*PMR2)(void*, void*);
typedef void* (VtblObj::*PMR3)(void*, void*, void*);
typedef u8    (VtblObj::*PMB0)();

inline void  VCall0(void* p, u32 o)                            { (((VtblObj*)p)->*(*(PMF0*)((u8*)*(void**)p + o)))(); }
inline void  VCall1(void* p, u32 o, void* a)                   { (((VtblObj*)p)->*(*(PMF1*)((u8*)*(void**)p + o)))(a); }
inline void  VCall2(void* p, u32 o, void* a, void* b)          { (((VtblObj*)p)->*(*(PMF2*)((u8*)*(void**)p + o)))(a, b); }
inline void  VCall3(void* p, u32 o, void* a, void* b, void* c) { (((VtblObj*)p)->*(*(PMF3*)((u8*)*(void**)p + o)))(a, b, c); }
inline void* VRet0(void* p, u32 o)                             { return (((VtblObj*)p)->*(*(PMR0*)((u8*)*(void**)p + o)))(); }
inline void* VRet1(void* p, u32 o, void* a)                    { return (((VtblObj*)p)->*(*(PMR1*)((u8*)*(void**)p + o)))(a); }
inline void* VRet2(void* p, u32 o, void* a, void* b)           { return (((VtblObj*)p)->*(*(PMR2*)((u8*)*(void**)p + o)))(a, b); }
inline void* VRet3(void* p, u32 o, void* a, void* b, void* c)  { return (((VtblObj*)p)->*(*(PMR3*)((u8*)*(void**)p + o)))(a, b, c); }
inline u8    VBool0(void* p, u32 o)                            { return (((VtblObj*)p)->*(*(PMB0*)((u8*)*(void**)p + o)))(); }

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Mat3 { float r0c0, r0c1, r0c2, r1c0, r1c1, r1c2, r2c0, r2c1, r2c2; };

// the 0xd2e340 result blob (a small frame record)
struct Frame {
    u8    mGap00[0x0e];
    u8    mB0e;                // +0x0e
    u8    mB0f;                // +0x0f
    u8    mB10;                // +0x10
    u8    mB11;                // +0x11
    float mF14;                // +0x14
    u32   mW18;                // +0x18
    u32   mW1c;                // +0x1c
    u32   mW20;                // +0x20
};

// descriptor blob handed to 0x421cf0 (the 0x60e4e46e message)
struct DescMsg {
    u16   mW00;                // +0x00
    u16   mW02;                // +0x02
    u32   mP04;                // +0x04
    u32   mGap08[3];           // +0x08 .. +0x14
    u32   mP14;                // +0x14
    float mF18;                // +0x18
    u32   mGap1c;              // +0x1c
    float mF20;                // +0x20
    u8    mTail[0x1c];         // +0x24 .. +0x40
};

// descriptor blob handed to 0x41cb40 / 0x40ccb0 / 0x537dc0
struct Desc {
    u16   mW00;                // +0x00
    u16   mW02;                // +0x02
    u32   mP04;                // +0x04
    u32   mGap08[2];           // +0x08 .. +0x10
    float mF10;                // +0x10
    float mF14;                // +0x14
    float mF18;                // +0x18
    float mF1c;                // +0x1c
    u8    mTail[0x20];         // +0x20 .. +0x40
};

struct Mat9 { float f[9]; };

// the object the cluster operates on (a camera / view transform)
struct cCamView {
    u8      mGap00[0x04];
    void*   mp04;              // +0x004  container handle
    u8      mGap08[0x14];
    float   mF1c;              // +0x01c
    u8      mGap20[0x18];
    Vec3    mF38;              // +0x038
    u8      mGap44[0x04];
    Vec3    mA48;              // +0x048
    u8      mGap54[0x0c];
    Vec4    mB60;              // +0x060
    Vec3    mC70;              // +0x070
    Vec3    mD7c;              // +0x07c
    Vec3    mE88;              // +0x088
    Vec3    mF94;              // +0x094
    u8      mGapA0[0x58];
    float   mFf8;              // +0x0f8
    float   mFfc;              // +0x0fc
    float   mF100;             // +0x100
    u8      mGap104[0x04];
    Vec3    mF108;             // +0x108  direction (3 floats)
    Vec3    mF114;             // +0x114
    u8      mGap120[0x34];
    Vec4    mF154;             // +0x154
    u8      mGap164[0x10];
    float   mF174;             // +0x174
    float   mF178;             // +0x178
    float   mF17c;             // +0x17c
    u8      mGap180[0x0c];
    float   mF18c;             // +0x18c
    float   mF190;             // +0x190
    float   mF194;             // +0x194
    u8      mGap198[0x14];
    Vec3    mF1ac;             // +0x1ac
    Vec4    mF1b8;             // +0x1b8
    Vec3    mF1c8;             // +0x1c8
    Vec4    mF1d4;             // +0x1d4
    u8      mGap1e4[0x08];
    u32     mW1ec;             // +0x1ec
    u8      mGap1f0[0x18];
    float   mF208;             // +0x208
    float   mF20c;             // +0x20c
    float   mF210;             // +0x210
    float   mF214;             // +0x214
    u8      mGap218[0x08];
    float   mF220;             // +0x220
    u8      mGap224[0x14];
    float   mF238;             // +0x238
    u8      mGap23c[0x24];
    u32     mW260;             // +0x260
    float   mF264;             // +0x264
    float   mF268;             // +0x268
    float   mF26c;             // +0x26c
    float   mF270;             // +0x270
    Mat3    mMat274;           // +0x274
    u8      mB298;             // +0x298
    u8      mGap299[0x03];
    void*   mp29c;             // +0x29c
    void*   mp2a0;             // +0x2a0
    void*   mp2a4;             // +0x2a4
    u32     mW2a8;             // +0x2a8
    void*   mp2ac;             // +0x2ac
    u8      mGap2b0[0x0c];
    u32     mW2bc;             // +0x2bc
    u8      mGap2c0[0x44];
    u8      mB304;             // +0x304

    void FUN_00d26790();
    void FUN_00d26bb0();
    void FUN_00d26c90();
    void FUN_00d26ed0(const Vec3* pA, const Vec4* pB, float c, float d, float e);
    void FUN_00d270a0(Vec3* pOut);
    void FUN_00d271d0(Vec3* pOut);
    void FUN_00d272e0();
};

// @ 0x00d26790
void cCamView::FUN_00d26790()
{
    // target rate from the +0x2bc flag, clamped upward against +0x17c
    float m0 = ((mW2bc >> 0x12) & 1) ? mF220 : mF210;
    float v = (mF17c > m0) ? mF17c : m0;
    mF17c = v;

    // exponential approach of +0x100 toward v
    float arg = (mF1c / mF238) * *(float*)0x13fdf1c;
    float e = 1.0f - (float)exp(arg);
    float nv = v + (v - mF100) * e;

    if ((float)fabs(mF100 - nv) < *(float*)0x147a31c) {
        void* sys = FUN_0067dcc0();
        if (sys) {
            DescMsg desc;
            desc.mW00 = 0;
            desc.mW02 = 0;
            desc.mP04 = 0x13eb90c;
            desc.mP14 = 0x13eb844;
            desc.mF18 = mF214;
            desc.mF20 = nv;
            VCall3(sys, 0x14, (void*)0x60e4e46e, &desc, (void*)0);
            FUN_00421cf0(&desc);
        }
    }
    mF100 = nv;

    // orthonormalise +0x114..+0x11c and derive the heading
    float nx = mF114.x, ny = mF114.y, nz = mF114.z;
    float inv = 1.0f / (float)sqrt(nx * nx + ny * ny + nz * nz + *(float*)0x13ec4b8);
    nx *= inv; ny *= inv; nz *= inv;

    // +0x174 scaled by 0x1471064
    mFf8 = mF174;
    float ang = mF174 * *(float*)0x1471064;
    float s = (float)sin(ang), c = (float)cos(ang);

    Vec3 axis;
    FUN_0059aed0(&axis, &mF38, 0);

    float ax = axis.x, ay = axis.y, az = axis.z;
    float rx = (nx * c + ay * s);
    float ry = (ny * c + az * s);
    float rz = (nz * c + ax * s);

    if (mGap104[0] == 0) {
        float dx = rx - nx, dy = ry - ny, dz = rz - nz;
        float linv = 1.0f / (float)sqrt(dx * dx + dy * dy + dz * dz + *(float*)0x13ec4b8);
        if (mB298 != 0 && mF100 != 0.0f) {
            Vec3 p;
            FUN_00d21d10(&p, &mF108, &mC70, *(float*)0x1582810);
            ax = p.x; ay = p.y; az = p.z;
        } else {
            ax = dx * linv; ay = dy * linv; az = dz * linv;
        }
    }

    mFfc = mF178;
    float bs = (float)sin(mF178) * nv;
    float bc = (float)cos(mF178) * nv;
    mF108.x = mF114.x - ax + bs;
    mF108.y = mF114.y - ay + bc;
    mF108.z = mF114.z - az + bs;
}

// @ 0x00d26bb0
void cCamView::FUN_00d26bb0()
{
    if (mB304 != 0)
        return;
    SELF(this)->FUN_00d38840();
    SELF(this)->FUN_00d247f0();
    SELFE(FUN_00b3d300())->FUN_00b1fdb0();
    SELF(this)->FUN_00d21d90();
    void* d = FUN_00883860();
    mp29c = d;
    mp2a0 = (u8*)this + 4;
    mp2a4 = (void*)0x147a338;
    mW2a8 = 0x13;
    mp2ac = 0;
    if (d && mp2a0) {
        for (u32 i = 0; i < 0x4c; i += 4)
            VCall2(d, 0x24, mp2a0, (void*)(*(const u32*)(0x147a338 + i)));
    }
    Frame* q = (Frame*)FUN_00d2e340();
    if (q) {
        q->mB0e = 0;
        q->mB0f = 0;
        q->mB10 = 0;
        q->mB11 = 0;
        q->mF14 = 0.0f;
        q->mW18 = *(u32*)0x169deb0;
        q->mW1c = *(u32*)0x169deb4;
        q->mW20 = *(u32*)0x169deb8;
    }
    mB304 = 1;
}

// @ 0x00d26c90
void cCamView::FUN_00d26c90()
{
    float tx = *(float*)0x169deb0, ty = *(float*)0x169deb4, tz = *(float*)0x169deb8;
    Vec3 local;
    local.x = tx; local.y = ty; local.z = tz;

    float sc = *(float*)0x1485720;
    Desc tmp;
    tmp.mW00 = 0;
    tmp.mW02 = 0;
    tmp.mP04 = 0x169df20;
    tmp.mF18 = sc;
    FUN_0041cb40(&tmp, (void*)0x169df20);

    float s0 = *(float*)0x169df44;
    float s1 = *(float*)0x169df48;
    float s2 = *(float*)0x169df4c;
    float k = mF194;
    s0 *= k; s1 *= k; s2 *= k;
    Vec3 dir;
    dir.x = s0; dir.y = s1; dir.z = s2;
    Vec3 v;
    FUN_00d266c0(&v, &dir);
    FUN_00d265c0(&v, mF190);
    FUN_00d265c0(&v, mF18c);

    if (sc > mF1d4.w) {
        Desc tmp2;
        tmp2.mW00 = 0;
        tmp2.mW02 = 0;
        tmp2.mP04 = 0x169df20;
        tmp2.mF10 = tx;
        tmp2.mF14 = ty;
        tmp2.mF18 = tz;
        tmp2.mF1c = sc;
        FUN_0041cb40(&tmp2, (void*)0x169df20);
        Vec3 m;
        FUN_0059c190(&m, &mF1d4);
        Mat9 res;
        for (int i = 0; i < 9; ++i) res.f[i] = 0.0f;
        FUN_0041cb40(&res, (void*)0x169df20);
        FUN_0040ccb0(&res, &m);
        FUN_00537dc0((u8*)this + 0x260, &res);
    }
    FUN_00d266c0(&v, (u8*)this + 0x1c8);
    FUN_00537dc0((u8*)this + 0x260, &local);
    mB298 = 0;
}

// @ 0x00d26ed0
void cCamView::FUN_00d26ed0(const Vec3* pA, const Vec4* pB, float c, float d, float e)
{
    mF1c8 = *pA;
    mA48  = *pA;
    mB60  = *pB;
    mF154 = *pB;
    mF1d4 = *pB;

    void* em = SELFE(FUN_00b3d300())->FUN_00b1fdb0();
    u8* edi = (u8*)em + 0xc0;
    Vec3 v = *(Vec3*)VRet0(edi, 0x2c);
    mF1ac = v;
    mF114 = v;

    Vec4 w = *(Vec4*)VRet0(edi, 0x30);
    mF1b8 = w;
    mF1c8 = *(Vec3*)&w;

    SELF(this)->FUN_00d21b10(c, d, e);

    mF174 = 0.0f;
    mFf8 = 0.0f;

    float cl = d;
    if (cl < mF208) cl = mF208;
    if (cl > mF20c) cl = mF20c;
    mF178 = cl;
    mFfc = cl;
    mF17c = mF210;
    mF100 = mF210;
    SELF(this)->FUN_00d26c90();
}

// @ 0x00d270a0
void cCamView::FUN_00d270a0(Vec3* pOut)
{
    if (mB298 != 0)
        SELF(this)->FUN_00d26c90();
    Vec3 t;
    t.x = *(float*)0x169deb0;
    t.y = *(float*)0x169deb4;
    t.z = *(float*)0x169deb8;
    pOut->x = t.x; pOut->y = t.y; pOut->z = t.z;
    if (mW260 & 2) {
        pOut->x = mMat274.r0c0 * t.x + mMat274.r0c1 * t.y + mMat274.r0c2 * t.z;
        pOut->y = mMat274.r1c0 * t.x + mMat274.r1c1 * t.y + mMat274.r1c2 * t.z;
        pOut->z = mMat274.r2c0 * t.x + mMat274.r2c1 * t.y + mMat274.r2c2 * t.z;
    }
    float s = mF270;
    pOut->x = pOut->x * s + mF264;
    pOut->y = pOut->y * s + mF268;
    pOut->z = pOut->z * s + mF26c;
}

// @ 0x00d271d0
void cCamView::FUN_00d271d0(Vec3* pOut)
{
    if (mB298 != 0)
        SELF(this)->FUN_00d26c90();
    float x = *(float*)0x169df44;
    float y = *(float*)0x169df48;
    float z = *(float*)0x169df4c;
    pOut->x = x; pOut->y = y; pOut->z = z;
    if (mW260 & 2) {
        pOut->x = mMat274.r0c0 * x + mMat274.r0c1 * y + mMat274.r0c2 * z;
        pOut->y = mMat274.r1c0 * x + mMat274.r1c1 * y + mMat274.r1c2 * z;
        pOut->z = mMat274.r2c0 * x + mMat274.r2c1 * y + mMat274.r2c2 * z;
    }
    float s = mF270;
    pOut->x = s * pOut->x;
    pOut->y = s * pOut->y;
    pOut->z = s * pOut->z;
}

// @ 0x00d272e0
void cCamView::FUN_00d272e0()
{
    if (mW1ec == 2)
        SELF(this)->FUN_00d263d0(0);
    else
        SELF(this)->FUN_00d263d0(2);
}