typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef double f64;
typedef long long s64;

#define VT(p) (*(void***)(p))

struct cSub;
struct cObj;

struct COps {
    // cSPCreatureBase / cLocomotiveObject / cSpatialObject
    u8    FUN_00c42e20();                 // 0x00c42e20 IsNearGoal
    void* FUN_00c42de0();                 // 0x00c42de0 position
    u8    FUN_00c123f0(u32);              // 0x00c123f0 AnimationFinished
    void  FUN_00c12190(u32, u32, u32);    // 0x00c12190 PlayAnimation
    void  FUN_00c12310(u32, u32, u32);    // 0x00c12310 InterruptAnimation
    void  FUN_00c1c1d0(u32, const void*, f32, f32);           // 0x00c1c1d0 MoveToPointAtSpeed
    void  FUN_00c1c5c0(u32, const void*, const void*, f32, f32); // 0x00c1c5c0 MoveToPointAndFacingAtSpeed
    void  FUN_00c1ad10(bool);             // 0x00c1ad10 SetSprinting
    void* FUN_00c23e40();                 // 0x00c23e40 GetCity

    // cBehavior / cActionCircle
    void* FUN_00afad70(void*);            // 0x00afad70 slot lookup
    void  FUN_00afa030(void*);            // 0x00afa030 tSlot::Reserve
    u32   FUN_00af9fa0();                 // 0x00af9fa0 CountOccupiedSlots
    void  FUN_00afae50(void*);            // 0x00afae50 RemoveAgent

    // misc
    void  FUN_00bc98f0(u32, u32);         // 0x00bc98f0 behavior_stimuli::ClearAll
    void  FUN_00bec2d0(const void*, u32); // 0x00bec2d0 RequestPosition
    void* FUN_00b81780();                 // 0x00b81780 MakeRandomWorldPosition
    void  FUN_00b815a0(const void*);      // 0x00b815a0 DirectionToSurfacePosition
    u32   FUN_00a68fb0(u32);              // 0x00a68fb0 RandomUint32Uniform
    f32   FUN_009360d0();                 // 0x009360d0 RandomDoubleUniform
};

#define MOPS(p) ((COps*)(p))

struct cSub {
    u8    pad000[0x1bc];
    u8    m1bc;
    u8    pad1bd[0x1d0 - 0x1bd];
    f32   m1d0, m1d4, m1d8;
    u8    pad1dc[0x220 - 0x1dc];
    u32   m220;
    u32   m224;
    u8    pad228[0x38c - 0x228];
    void* m38c;
    u8    pad390[0x9f4 - 0x390];
    u32   m9f4;
    u8    pad9f8[0xa14 - 0x9f8];
    f32   mA14, mA18, mA1c, mA20, mA24, mA28;
    u8    padA2c[0xa38 - 0xa2c];
    s32   mA38, mA3c;
    u8    padA40[0xa44 - 0xa40];
    s32   mA44;
    u8    padA48[0xaf0 - 0xa48];
    void* mAF0;
    u8    padAF4[0xb80 - 0xaf4];
    u8*   mB80;
    u8*   mB84;
    u8    padB88[0xb94 - 0xb88];
    u8*   mB94;
    u8*   mB98;
};

struct cEntry {
    u32 key;
    u32 count;
};

struct cState {
    u8  m0;
    u8  pad1[3];
    u32 m4;
};

struct cSlot {
    u8  pad0[0xc];
    f32 x, y, z;
};

struct cCityData {
    u8  pad0[0x258];
    f32 m258;
};

struct cStimuli {
    u8  pad0[8];
    u8  mOp;
};

struct cObj {
    u8    pad000[0xc0];
    u8    mC0[0xb4c - 0xc0];
    void* mB4c;
    u8    padB50[0xfb8 - 0xb50];
    cSub* mFB8;
    u8    padFBC[0xff0 - 0xfbc];
    u32   mFF0;
};

extern f32 g14853e0;   // 4.0f
extern f32 g1470f1c;   // 2.0f
extern f32 g1471064;   // 0.5f
extern f32 g13ec4b8;   // 1e-8f
extern f32 g13f6b68;   // 12.0f
extern f32 g140c6e8;   // 32.0f
extern f32 g1485378;   // 0.0f
extern f32 g13eecd8;   // 20.0f
extern f32 g1488874;   // 0.1f
extern f32 g13ec480;   // 0.2f
extern f32 g1486374;   // 0.8f
extern f32 g13f8698;   // 7.0f
extern f32 g169ec74, g169ec78, g169ec7c;
extern f32 g169f20c, g169f210, g169f214;

extern "C" float __cdecl sqrtf(float);
extern "C" double __cdecl sqrt(double);
void* __stdcall FUN_00b3d350(void*, void*, f32, f32);   // 0x00b3d350 PlanetModel
f32* __cdecl FUN_00449c20(f32*, const f32*);            // 0x00449c20 normalized_safe

// @ 0x00d93230
u8 __cdecl FUN_00d93230(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    cSub* sub = a1->mFB8;
    if (sub->mA38 > sub->mA3c)
        return 0;
    switch (*a6) {
    case 0:
        if (!MOPS(a1->mC0)->FUN_00c42e20())
            goto ret1;
        *a6 = 1;
        break;
    case 1:
        if (!MOPS(a1)->FUN_00c123f0(0))
            goto ret1;
        break;
    default:
        goto ret1;
    }
    u32 r = MOPS((void*)0x1601760)->FUN_00a68fb0(3);
    switch (r) {
    case 0:
        MOPS(a1)->FUN_00c12190(0x2d5f9be, 1, -1);
        return 1;
    case 1:
        MOPS(a1)->FUN_00c12190(0x2d5f9cc, 1, -1);
        return 1;
    case 2:
        MOPS(a1)->FUN_00c12190(0x2d5f9c1, 1, -1);
        return 1;
    default:
        return 1;
    }
ret1:
    return 1;
}

// @ 0x00d932e0
u8 __cdecl FUN_00d932e0(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    if (a6 != 0) {
        a6[2] = 0xffffffff;
        a6[3] = 0xffffffff;
    }
    cSub* sub = a1->mFB8;
    void* viz = sub->mAF0;
    sub->m9f4 -= 1;
    f32 pos[3];
    u32 v5 = 5;
    void* city = ((void* (__thiscall*)(void*, f32*, u32))VT(viz)[0x6c / 4])(viz, pos, v5);
    MOPS(city)->FUN_00bec2d0(pos, v5);

    f32 dir[3];
    void* planet = FUN_00b3d350(dir, pos, 0.0f, 4.0f);
    f32* rp = (f32*)MOPS(planet)->FUN_00b81780();
    pos[0] = rp[0];
    pos[1] = rp[1];
    pos[2] = rp[2];

    void* city2 = ((void* (__thiscall*)(void*, f32*))VT(viz)[0x6c / 4])(viz, pos);
    f32 face[3];
    ((void (__thiscall*)(void*, f32*))VT(city2)[0x70 / 4])(city2, face);

    MOPS(a1)->FUN_00c12310(0x2481db0, 0xffffffff, 0);
    f32 speed = g14853e0;
    f32 f1 = g1470f1c;
    MOPS(a1)->FUN_00c1c5c0(3, dir, face, f1, speed);

    a6[0] = 0;
    a6[1] = 0;
    return 1;
}

// @ 0x00d933d0
u8 __cdecl FUN_00d933d0(cObj* a1)
{
    f32 c4 = g14853e0;
    f32 c2 = g1470f1c;
    MOPS(a1)->FUN_00c1c1d0(2, &g169ec74, c2, c4);
    f32 r = MOPS((void*)0x1601760)->FUN_009360d0();
    if (r < 0.5f) {
        MOPS(a1)->FUN_00c1ad10(1);
    } else {
        MOPS(a1)->FUN_00c1ad10(0);
    }
    return 1;
}

// @ 0x00d93430
u8 __cdecl FUN_00d93430(cObj* a1)
{
    if (MOPS(a1->mC0)->FUN_00c42e20())
        return 0;
    f32* p = (f32*)MOPS(a1->mC0)->FUN_00c42de0();
    if (p[0] == g169ec74 && p[1] == g169ec78 && p[2] == g169ec7c)
        return 1;
    if (g169ec74 != g169f20c || g169ec78 != g169f210 || g169ec7c != g169f214) {
        MOPS(a1)->FUN_00c1c1d0(2, &g169ec74, g1470f1c, g14853e0);
        return 1;
    }
    return 0;
}

// @ 0x00d934f0
u8 __cdecl FUN_00d934f0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    u8** pBegin = &sub->mB94;
    u8* begin = *pBegin;
    u8* end = sub->mB98;
    s32 count = (s32)(end - begin) >> 3;
    s32 i = 0;
    if (count > 0) {
        u32 key = a1->mFF0;
        for (; i < count; i++) {
            if (((cEntry*)begin)[i].key == key) {
                if (((cEntry*)begin)[i].count > 0) {
                    u32 v = ((u32 (__thiscall*)(void*))VT(a1)[0x4c / 4])(a1);
                    a1->mFF0 = v;
                    u8* p = *pBegin;
                    ((cEntry*)p)[i].count -= 1;
                }
                break;
            }
        }
    }
    return 0;
}

// @ 0x00d93560
u8 __cdecl FUN_00d93560(cObj* a1)
{
    cSub* sub = a1->mFB8;
    u8* begin = sub->mB80;
    u8* end = sub->mB84;
    s32 count = (s32)(end - begin) >> 3;
    u8** pBegin = &sub->mB80;
    s32 i = 0;
    for (; i < count; i++) {
        if (((cEntry*)begin)[i].count > 0) {
            a1->mFF0 = ((cEntry*)begin)[i].key;
            u8* q = *pBegin;
            ((cEntry*)q)[i].count -= 1;
            MOPS(a1)->FUN_00c12310(0x4fe76c4, 0xffffffff, 0);
            return 1;
        }
    }
    return 0;
}

// @ 0x00d935d0
f32 __cdecl FUN_00d935d0(cObj* a1)
{
    void* q = a1->mFB8->m38c;
    if (q != 0) {
        f32* a = (f32*)((void* (__thiscall*)(void*))VT(q)[0x2c / 4])(q);
        f32* b = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
        f64 dx = (f64)b[0] - a[0];
        f64 dy = (f64)b[1] - a[1];
        f64 dz = (f64)b[2] - a[2];
        if (sqrt(dy * dy + (dz * dz + dx * dx)) < g140c6e8) {
            f32* c = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
            if (MOPS(&a1->mFB8->m1bc)->FUN_00afad70(c) != 0)
                return 1.0f;
        }
    }
    MOPS(&((cStimuli*)a1->mB4c)->mOp)->FUN_00bc98f0(0x400, 0);
    return 0.0f;
}

// @ 0x00d93670
u8 __cdecl FUN_00d93670(cObj* a1, void* a2, void* a3, void* a4, void* a5, u8* a6)
{
    if (a6 != 0)
        ((cState*)a6)->m4 = 0;
    f32* pos = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
    void* slot = MOPS(&a1->mFB8->m1bc)->FUN_00afad70(pos);
    if (slot == 0)
        return 0;
    MOPS(slot)->FUN_00afa030(a1);
    MOPS(a1)->FUN_00c12310(0x2481db0, 0xffffffff, 0);
    cSub* sub = a1->mFB8;
    cSlot* s = (cSlot*)slot;
    f32 dx = sub->m1d0 - s->x;
    f32 dy = sub->m1d4 - s->y;
    f32 dz = sub->m1d8 - s->z;
    f32 inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + g13ec4b8);
    f32 nx = inv * dx;
    f32 ny = inv * dy;
    f32 nz = inv * dz;
    MOPS(a1)->FUN_00c1c5c0(2, &s->x, &nx, 1.0f, g1470f1c);
    MOPS(a1)->FUN_00c1ad10(1);
    ((cState*)a6)->m0 = 1;
    return 1;
}

// @ 0x00d937b0
f32 __cdecl FUN_00d937b0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    f32 radius = sub->mA24;
    if (radius > g1485378) {
        f32 pos[3];
        pos[0] = sub->mA14;
        pos[1] = sub->mA18;
        pos[2] = sub->mA1c;
        f32* p = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
        f32 d[3];
        d[0] = p[0] - pos[0];
        d[1] = p[1] - pos[1];
        d[2] = p[2] - pos[2];
        if (sqrt((f64)d[2] * d[2] + (f64)d[1] * d[1] + (f64)d[0] * d[0]) < radius + 12.0f)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d93880
u8 __cdecl FUN_00d93880(cObj* a1, f32 a2)
{
    cSub* sub = a1->mFB8;
    f32 radius = sub->mA24;
    if (radius <= 0.0f)
        return 0;
    f32 lx = sub->mA14;
    f32 ly = sub->mA18;
    f32 lz = sub->mA1c;
    f32* p = (f32*)((void* (__thiscall*)(void*))VT(a1->mC0)[0x2c / 4])(a1->mC0);
    f32 px = p[0], py = p[1], pz = p[2];
    f32 dx = lx - px;
    f32 dy = ly - py;
    f32 dz = lz - pz;
    f32 dist = sqrtf(dy * dy + (dz * dz + dx * dx)) - a2;

    if (dist < g1488874) {
        f32 ex = px - lx;
        f32 ey = py - ly;
        f32 ez = pz - lz;
        f32 inv = 1.0f / sqrtf(ey * ey + (ez * ez + ex * ex) + g13ec4b8);
        f32 ux = inv * ex;
        f32 uy = ey * inv;
        f32 uz = ez * inv;
        f32 reach = ((f32 (__thiscall*)(void*))VT(a1->mC0)[0x74 / 4])(a1->mC0) + a2;
        f32 tx = ux * reach + lx;
        f32 ty = uy * reach + ly;
        f32 tz = uz * reach + lz;

        void* city = MOPS(a1)->FUN_00c23e40();
        f32 cityPos[3];
        f32* cp = (f32*)((void* (__thiscall*)(void*, f32*))VT(city)[0x58 / 4])(city, cityPos);
        f32 cx = tx - cp[0];
        f32 cy = ty - cp[1];
        f32 cz = tz - cp[2];
        dist = sqrtf(cy * cy + (cz * cz + cx * cx));

        void* city2 = MOPS(a1)->FUN_00c23e40();
        void* cityData = (void*)((void* (__thiscall*)(void*))VT(city2)[0x6c / 4])(city2);
        f32 limit = ((cCityData*)cityData)->m258;
        if (limit < dist) {
            dist -= limit;
            void* city3 = MOPS(a1)->FUN_00c23e40();
            f32 cityPos2[3];
            f32* cp2 = (f32*)((void* (__thiscall*)(void*, f32*))VT(city3)[0x58 / 4])(city3, cityPos2);
            f32 sx = cp2[0] - tx;
            f32 sy = cp2[1] - ty;
            f32 sz = cp2[2] - tz;
            f32 ndir[3];
            f32* np = FUN_00449c20(ndir, &sx);
            tx = np[0] * dist + tx;
            ty = np[1] * dist + ty;
            tz = np[2] * dist + tz;
        }
        ((void (__thiscall*)(void*, f32*))VT(a1->mC0)[0x38 / 4])(a1->mC0, &tx);
    }

    if (dist < radius * g13ec480) {
        f32 ex = px - lx;
        f32 ey = py - ly;
        f32 ez = pz - lz;
        f32 inv = 1.0f / sqrtf(ex * ex + (ey * ey + ez * ez) + g13ec4b8);
        f32 tx = (inv * ex) * g13f8698 + px;
        f32 ty = (ey * inv) * g13f8698 + py;
        f32 tz = (ez * inv) * g13f8698 + pz;
        f32 out[3];
        f32* rp = FUN_00449c20(out, &tx);
        void* planet = FUN_00b3d350(out, rp, 0.0f, 4.0f);
        MOPS(planet)->FUN_00b815a0(out);
        f32* lim = &sub->mA20;
        if (*lim < g13eecd8) {
            MOPS(a1)->FUN_00c1c1d0(2, &lx, 1.0f, g1470f1c);
            MOPS(a1)->FUN_00c1ad10(dist < g1471064);
            MOPS(a1)->FUN_00c12310(0x2481db0, 0xffffffff, 0);
            return 1;
        }
        MOPS(a1)->FUN_00c1c1d0(2, &lx, 1.0f, g1470f1c);
        MOPS(a1)->FUN_00c1ad10(1);
        MOPS(a1)->FUN_00c12310(0x2481dc8, 0xffffffff, 0);
        return 1;
    }

    if (MOPS(a1->mC0)->FUN_00c42e20()) {
        f32 vx = lx - px;
        f32 vy = ly - py;
        f32 vz = lz - pz;
        f32 nv[3];
        FUN_00449c20(nv, &vx);
        f32 out[3];
        f32* face = (f32*)((void* (__thiscall*)(void*, f32*))VT(a1->mC0)[0x5c / 4])(a1->mC0, out);
        f32 dot = (face[1] * nv[0] + face[2] * nv[1]) + nv[2] * face[0];
        if (dot < g1486374) {
            MOPS(a1)->FUN_00c1ad10(0);
            MOPS(a1)->FUN_00c1c5c0(2, &vz, &nv[0], 1.0f, g1470f1c);
            return 1;
        }
        MOPS(a1)->FUN_00c12190(0x2481de3, 1, 0xffffffff);
    }
    return 1;
}

// @ 0x00d93df0
f32 __cdecl FUN_00d93df0(cObj* a1)
{
    cSub* sub = a1->mFB8;
    s32 idx = sub->mA44;
    if (idx != -1) {
        u32 base = sub->m220;
        void* circle = (void*)(base + idx * 100);
        if (MOPS(circle)->FUN_00af9fa0() < 5)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00d93f70
void __cdecl FUN_00d93f70(cObj* a1, void* a2, void* a3, void* a4, void* a5, u32* a6)
{
    s32 idx = (s32)a6[1];
    if (idx != -1) {
        cSub* sub = a1->mFB8;
        s32 count = (s32)(sub->m224 - sub->m220) / 100;
        if (count > idx) {
            void* circle = (void*)(sub->m220 + idx * 100);
            MOPS(circle)->FUN_00afae50(a1);
        }
    }
    MOPS(a1)->FUN_00c1ad10(0);
}
