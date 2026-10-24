typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
typedef double f64;

#define VT(p) (*(void***)(p))

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct cSPUISocialRainbow;

// Placeholder for the many callees that take ecx=this.
struct COps {
    // cSPUILayout
    u8    FUN_008120d0(void* key, u8 b, u32 hash);   // 0x008120d0 Init
    void  FUN_00810090(void* cb, void* user);        // 0x00810090 SetReloadCallback
    void* FUN_008105b0(u32 id, u8 b);                // 0x008105b0 FindWindowByID
    void  FUN_00810000();                            // 0x00810000 ctor
    void  FUN_00811fe0();                            // 0x00811fe0 dtor
    // cSPUIAnimator
    void  FUN_007f83e0();                            // 0x007f83e0 ctor
    void  FUN_007f8c20();                            // 0x007f8c20 dtor
    u8    FUN_007f6210(void* win, s32 id);           // 0x007f6210 RemoveAnimation
};

#define MOPS(p) ((COps*)(p))

struct cSPUILayout {
    u8 pad0[0x18];
};

struct cSPUIAnimator {
    u8    pad0[0x20];
    void* mOwner;
};

struct cSide {
    void* mBegin;       // +0x00
    void* mEnd;         // +0x04
    void* mCap;         // +0x08
    u8    pad0c[4];     // +0x0c
    void* mBase;        // +0x10
    u8    pad14[4];     // +0x14
    u8    mBuf[0x78];   // +0x18
    f32   m90;          // +0x90
    f32   m94;          // +0x94
    f32   m98;          // +0x98
    u8    m9c;          // +0x9c
    u8    m9d;          // +0x9d
    u8    pad9e[2];     // +0x9e
    void* mObj;         // +0xa0
};

struct cSPUISocialRainbow {
    void* mVtbl;            // 0x000
    void* mVtbl2;           // 0x004
    u32   m08;              // 0x008
    cSPUILayout mLayout;    // 0x00c
    u8    m24;              // 0x024
    u8    m25;              // 0x025
    u8    m26;              // 0x026
    u8    pad27;            // 0x027
    f32   m28;              // 0x028
    f32   m2c;              // 0x02c
    f32   m30;              // 0x030
    f32   m34;              // 0x034
    f32   m38;              // 0x038
    f32   m3c;              // 0x03c
    f32   m40;              // 0x040
    u32   m44;              // 0x044
    cSPUIAnimator mAnimator; // 0x048
    void* m6c;              // 0x06c
    void* m70;              // 0x070
    void* m74;              // 0x074
    void* m78;              // 0x078
    void* m7c;              // 0x07c
    void* m80;              // 0x080
    void* m84;              // 0x084
    void* m88;              // 0x088
    void* m8c;              // 0x08c
    void* m90;              // 0x090
    u8    pad94[0xc];       // 0x094
    u32   mA0;              // 0x0a0
    cSide mSide0;           // 0x0a4
    cSide mSide1;           // 0x148
    void* m1ec;             // 0x1ec
    void* m1f0;             // 0x1f0
    void* m1f4;             // 0x1f4
    void* m1f8;             // 0x1f8
    void* m1fc;             // 0x1fc

    void FUN_00e32160(s32); // 0x00e32160
    void FUN_00e32c80();
    u8   FUN_00e32de0();
    void FUN_00e32f00();
    cSPUISocialRainbow* FUN_00e330c0();
};

struct cB20Arg {
    u8  pad0[0x1c];
    s32 m1c;    // +0x1c
    s32 m20;    // +0x20
};

extern f32 g13f0e84;
extern f32 g15a5794;
extern f32 g1477fc0;
extern f32 g13ec4d0;
extern f32 g15a5790;
extern f32 g1471064;
extern f32 g1485720;
extern f32 g13eb1bc;
extern f32 g1485378;

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl atan2(double, double);
extern "C" double __cdecl acos(double);
extern "C" double __cdecl sqrt(double);
extern "C" float __cdecl sqrtf(float);

void  __cdecl FUN_00f47380(void*);                 // 0x00f47380 operator delete[]
void* __cdecl FUN_00e232b0(void*);                 // 0x00e232b0 sGetWindowImage
void  __cdecl FUN_00808230(void*, f32*);           // 0x00808230
void* __cdecl FUN_00805ea0(void*);                 // 0x00805ea0 GetMainWindowArea

// @ 0x00e32580
void __cdecl FUN_00e32580(cSPUISocialRainbow* self, void* layout, u8 reload)
{
    if (self)
        ((void (__thiscall*)(void*))VT(self)[0])(self);

    void* winC = 0;
    if (reload == 0) {
        void* w = MOPS(&self->mLayout)->FUN_008105b0(0x562bd40, 1);
        if (w)
            ((void (__thiscall*)(void*, void*))VT(w)[0x108 / 4])(w, self);
    } else {
        self->mAnimator.mOwner = self;
        void* w = MOPS(&self->mLayout)->FUN_008105b0(0x562bd40, 1);
        ((void (__thiscall*)(void*, void*))VT(w)[0x104 / 4])(w, self);

        void* img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb08, 1));
        void* old = self->m6c;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m6c = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb10, 1));
        old = self->m70;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m70 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        winC = MOPS(&self->mLayout)->FUN_008105b0(0x563bb18, 1);
        img = FUN_00e232b0(winC);
        old = self->m74;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m74 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }
        ((void (__thiscall*)(void*, s32, s32))VT(winC)[0x7c / 4])(winC, 1, 0);

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x563bb38, 1));
        old = self->m78;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m78 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x564eeb8, 1));
        old = self->m7c;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m7c = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        img = FUN_00e232b0(MOPS(&self->mLayout)->FUN_008105b0(0x564ee80, 1));
        old = self->m80;
        if (img != old) {
            if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
            self->m80 = img;
            if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
        }

        void* winA = MOPS(&self->mLayout)->FUN_008105b0(0x563bb50, 1);
        f32 apos[4];
        f32* ap = (f32*)((void* (__thiscall*)(void*))VT(winA)[0x38 / 4])(winA);
        apos[0] = ap[0];
        apos[1] = ap[1];
        apos[2] = ap[2];
        apos[3] = ap[3];
        ((void (__thiscall*)(void*, void*))VT(winA)[0x104 / 4])(winA, self);

        void* winB = MOPS(&self->mLayout)->FUN_008105b0(0x562c1a0, 1);
        f32 bpos[4];
        f32* bp = (f32*)((void* (__thiscall*)(void*))VT(winB)[0x38 / 4])(winB);
        bpos[0] = bp[0];
        bpos[1] = bp[1];
        bpos[2] = bp[2];
        bpos[3] = bp[3];
        ((void (__thiscall*)(void*, f32, f32))VT(winB)[0x70 / 4])(winB, bpos[0], apos[1]);
        bp = (f32*)((void* (__thiscall*)(void*))VT(winB)[0x38 / 4])(winB);
        bpos[0] = bp[0];
        bpos[2] = bp[2];
        ((void (__thiscall*)(void*, void*))VT(winB)[0x104 / 4])(winB, self);

        f32* cp = (f32*)((void* (__thiscall*)(void*))VT(winC)[0x38 / 4])(winC);
        f32 s0 = (apos[2] + apos[0]) * 0.5f;
        f32 s1 = (bpos[2] + bpos[0]) * 0.5f;
        f32 s2 = (apos[3] + apos[1]) * 0.5f;
        f32 s3 = (cp[3] + cp[1]) * 0.5f;
        f32 num = s2 - s3;
        f32 den = s0 - (s1 + s0) * 0.5f;
        f32 q = g13eb1bc / (den / num);
        f32 ang = (f32)atan2((f64)q, 1.0);

        f32 mat[5];
        mat[0] = 0.0f;
        mat[1] = 0.0f;
        mat[2] = 1.0f;
        mat[3] = -ang - g15a5794;
        FUN_00808230(winA, mat);
        mat[0] = 0.0f;
        mat[1] = 0.0f;
        mat[2] = 1.0f;
        mat[3] = g15a5794 + ang;
        FUN_00808230(winB, mat);

        f32 out1[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(winA)[0xc0 / 4])(winA, out1, s0 - s1, 0.0f);
        void* tr1 = (void*)((void* (__thiscall*)(void*))VT(winA)[0x10 / 4])(winA);
        f32 out2[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr1)[0xc4 / 4])(tr1, out2, s0, s2);

        f32 out3[2];
        ((void (__thiscall*)(void*, f32*, s32, s32))VT(winB)[0xc0 / 4])(winB, out3, 0, 0);
        void* tr2 = (void*)((void* (__thiscall*)(void*))VT(winB)[0x10 / 4])(winB);
        f32 out4[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr2)[0xc4 / 4])(tr2, out4, out2[0], out2[1]);

        f32 out5[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(winA)[0xc0 / 4])(winA, out5, s1, s3);
        void* tr3 = (void*)((void* (__thiscall*)(void*))VT(winA)[0x10 / 4])(winA);
        f32 out6[2];
        ((void (__thiscall*)(void*, f32*, f32, f32))VT(tr3)[0xc4 / 4])(tr3, out6, out4[0], out4[1]);

        f32 A = out5[0];
        f32 B = out6[0];
        f32 C = s1;
        f32 D = out5[1];
        f32 E = out6[1];
        f32 r = ((E - D) * (C - A)) / (B - A) + D;
        f32 t = D - r;
        self->m30 = C;
        self->m34 = r;
        self->m38 = (f32)sqrt((f64)(t * t + C * (C - A)));
        f32 ac = (f32)acos((f64)(t / num));
        self->m24 = 1;
        self->m3c = g15a5794 - ac;
        self->m40 = g15a5794 + ac;
    }

    self->m25 = reload;
    ((void (__thiscall*)(void*))VT(self)[1])(self);
}

// @ 0x00e32b20
void __cdecl FUN_00e32b20(void* a1, f32 a2, f32 a3, f32 a4, u32 a5, u32 a6, f32 a7, void* a8)
{
    cB20Arg* arg = (cB20Arg*)a8;
    f32 sn = (f32)sin((f64)a7);
    f32 cs = (f32)cos((f64)a7);

    f32 x = cs * a4 + a2;
    f32 y = a3 - sn * a4;
    f32 a4b = a4 - (f32)arg->m20;
    f32 x2 = cs * a4b + a2;
    f32 y2 = a3 - sn * a4b;
    f32 h = ((f32)arg->m1c * cs) * 0.5f;
    f32 v = (-sn * (f32)arg->m1c) * 0.5f;

    f32 m[16];
    m[0]  = x - v;
    m[1]  = y + h;
    m[2]  = (f32)a6;
    m[3]  = 1.0f;
    m[4]  = 0.0f;
    m[5]  = x + v;
    m[6]  = y - h;
    m[7]  = (f32)a6;
    m[8]  = 0.0f;
    m[9]  = 0.0f;
    m[10] = x2 + v;
    m[11] = y2 - h;
    m[12] = (f32)a5;
    m[13] = 0.0f;
    m[14] = 1.0f;
    m[15] = x2 - v;

    ((void (__thiscall*)(void*, f32*, s32, void*))VT(a1)[0x54 / 4])(a1, m, 1, a8);
}

// @ 0x00e32c80
void cSPUISocialRainbow::FUN_00e32c80()
{
    *(volatile void**)&mVtbl = (void*)0x14819b0;
    *(volatile void**)&mVtbl2 = (void*)0x1481994;
    _ReadWriteBarrier();
    if (m1fc) ((void (__thiscall*)(void*))VT(m1fc)[1])(m1fc);
    if (m1f8) ((void (__thiscall*)(void*))VT(m1f8)[1])(m1f8);
    if (m1f4) ((void (__thiscall*)(void*))VT(m1f4)[1])(m1f4);
    if (m1f0) ((void (__thiscall*)(void*))VT(m1f0)[1])(m1f0);
    if (m1ec) ((void (__thiscall*)(void*))VT(m1ec)[1])(m1ec);
    _ReadWriteBarrier();

    cSide* p = &mSide1 + 1;
    for (s32 i = 1; i >= 0; i--) {
        void* obj = p[-1].mObj;
        p--;
        if (obj) ((void (__thiscall*)(void*))VT(obj)[1])(obj);
        if (p->mBegin && p->mBegin != p->mBase)
            FUN_00f47380(p->mBegin);
    }

    if (m88 && ((u32*)m88)[-1] != 0)
        FUN_00f47380(m88);
    if (m84) ((void (__thiscall*)(void*))VT(m84)[1])(m84);
    if (m80) ((void (__thiscall*)(void*))VT(m80)[1])(m80);
    if (m7c) ((void (__thiscall*)(void*))VT(m7c)[1])(m7c);
    if (m78) ((void (__thiscall*)(void*))VT(m78)[1])(m78);
    if (m74) ((void (__thiscall*)(void*))VT(m74)[1])(m74);
    if (m70) ((void (__thiscall*)(void*))VT(m70)[1])(m70);
    if (m6c) ((void (__thiscall*)(void*))VT(m6c)[1])(m6c);

    MOPS(&mAnimator)->FUN_007f8c20();
    MOPS(&mLayout)->FUN_00811fe0();
    mVtbl2 = (void*)0x13eb938;
    mVtbl = (void*)0x13eb938;
}

// @ 0x00e32de0
u8 cSPUISocialRainbow::FUN_00e32de0()
{
    union {
        u32 key[4];
        u8  area[0x10];
    } buf;
    buf.key[0] = 0xe539924e;
    buf.key[1] = 0x0510a95b;
    buf.key[2] = 0x40464100;
    if (!MOPS(&mLayout)->FUN_008120d0(buf.key, 1, 0x3f608b3e))
        return 0;

    MOPS(&mLayout)->FUN_00810090((void*)FUN_00e32580, this);
    FUN_00e32580(this, &mLayout, 1);

    void* win = MOPS(&mLayout)->FUN_008105b0(0x53daa60, 1);
    if (win) {
        void** vt = VT(win);
        void* p = FUN_00805ea0(buf.area);
        ((void (__thiscall*)(void*, void*))vt[0x6c / 4])(win, p);
        ((void (__thiscall*)(void*))VT(win)[0x94 / 4])(win);
    }

    void* w2 = MOPS(&mLayout)->FUN_008105b0(0x53daa70, 1);
    void* img = (void*)((void* (__thiscall*)(void*, u32))VT(w2)[0x0c / 4])(w2, 0x105a93d);
    void* old = m1f8;
    if (img != old) {
        if (img) ((void (__thiscall*)(void*))VT(img)[0])(img);
        m1f8 = img;
        if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
    }

    void* w3 = MOPS(&mLayout)->FUN_008105b0(0x741ff10a, 1);
    old = m1fc;
    if (w3 != old) {
        if (w3) ((void (__thiscall*)(void*))VT(w3)[0])(w3);
        m1fc = w3;
        if (old) ((void (__thiscall*)(void*))VT(old)[1])(old);
    }

    return m25;
}

// @ 0x00e32f00
void cSPUISocialRainbow::FUN_00e32f00()
{
    if (m26 != 0)
        return;

    *(volatile u8*)&m24 = 1;
    *(volatile f32*)&mSide1.m98 = *(volatile f32*)&mSide1.m94;
    FUN_00e32160(1);
    if (mSide1.m98 == 0.0f) {
        void* win = MOPS(&mLayout)->FUN_008105b0(0x562c170, 1);
        if (((u8 (__thiscall*)(void*))VT(win)[0x28 / 4])(win) & 1)
            ((void (__thiscall*)(void*, s32, s32))VT(win)[0x7c / 4])(win, 1, 0);
    }

    *(volatile u8*)&m24 = 1;
    *(volatile f32*)&mSide0.m98 = *(volatile f32*)&mSide0.m94;
    FUN_00e32160(0);
    if (mSide0.m98 == 0.0f) {
        void* win = MOPS(&mLayout)->FUN_008105b0(0x562c1b8, 1);
        if (((u8 (__thiscall*)(void*))VT(win)[0x28 / 4])(win) & 1)
            ((void (__thiscall*)(void*, s32, s32))VT(win)[0x7c / 4])(win, 1, 0);
    }

    MOPS(&mAnimator)->FUN_007f6210(MOPS(&mLayout)->FUN_008105b0(0x562c170, 1), -1);

    void* arr[2];
    arr[0] = MOPS(&mLayout)->FUN_008105b0(0x562c1b8, 1);
    arr[1] = MOPS(&mLayout)->FUN_008105b0(0x562c170, 1);
    for (u32 k = 0; k < 2; k++) {
        void* w = arr[k];
        if (w) {
            MOPS(&mAnimator)->FUN_007f6210(w, -1);
            void** vt = VT(w);
            u32 v = ((u32 (__thiscall*)(void*))vt[0x30 / 4])(w);
            ((void (__thiscall*)(void*, u32))vt[0x5c / 4])(w, (v & 0xffffff) - 0x1000000);
        }
    }

    arr[0] = MOPS(&mLayout)->FUN_008105b0(0x562c178, 1);
    arr[1] = MOPS(&mLayout)->FUN_008105b0(0x564f020, 1);
    u32 i2;
    for (i2 = 0; i2 < 2; i2++) {
        void* w = arr[i2];
        if (w) {
            ((void (__thiscall*)(void*, s32, s32))VT(w)[0x7c / 4])(w, 1, 1);
            u32* vt2 = (u32*)VT(w);
            u32 v = ((u32 (__thiscall*)(void*))vt2[0x30 / 4])(w);
            ((void (__thiscall*)(void*, u32))vt2[0x5c / 4])(w, (v & 0xffffff) - 0x1000000);
        }
    }

    m24 = 1;
    m26 = 1;
}

// @ 0x00e330c0
cSPUISocialRainbow* cSPUISocialRainbow::FUN_00e330c0()
{
    *(volatile void**)&mVtbl2 = (void*)0x13fa72c;
    m08 = 0;
    *(volatile void**)&mVtbl = (void*)0x14819b0;
    *(volatile void**)&mVtbl2 = (void*)0x1481994;
    MOPS(&mLayout)->FUN_00810000();

    m24 = 1;
    m25 = 0;
    m26 = 0;
    m28 = g13f0e84;
    m2c = g1477fc0;
    *(volatile f32*)&m30 = *(volatile f32*)&m28;
    m34 = g1477fc0 + m38;
    m38 = g13ec4d0;
    m3c = g15a5790;
    m40 = g15a5794 + g15a5790;
    m44 = 0;

    MOPS(&mAnimator)->FUN_007f83e0();

    m6c = 0;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    m8c = 0;
    m90 = 0;
    mA0 = 0;
    _ReadWriteBarrier();

    mSide0.mBase = mSide0.mBuf;
    mSide0.mEnd = mSide0.mBuf;
    mSide0.mBegin = mSide0.mBuf;
    *(volatile f32*)&mSide0.m90 = 0.0f;
    *(volatile f32*)&mSide0.m94 = 0.0f;
    *(volatile f32*)&mSide0.m98 = 0.0f;
    mSide0.m9c = 0;
    mSide0.m9d = 0;
    mSide0.mCap = mSide0.mBuf + 0x78;
    mSide0.mObj = 0;

    mSide1.mBase = mSide1.mBuf;
    mSide1.mEnd = mSide1.mBuf;
    mSide1.mBegin = mSide1.mBuf;
    *(volatile f32*)&mSide1.m90 = 0.0f;
    *(volatile f32*)&mSide1.m94 = 0.0f;
    *(volatile f32*)&mSide1.m98 = 0.0f;
    mSide1.m9c = 0;
    mSide1.m9d = 0;
    mSide1.mCap = mSide1.mBuf + 0x78;
    mSide1.mObj = 0;

    m1ec = 0;
    m1f0 = 0;
    m1f4 = 0;
    m1f8 = 0;
    m1fc = 0;
    _ReadWriteBarrier();

    ((void (__thiscall*)(void*))VT(&mLayout)[1])(&mLayout);

    return this;
}
