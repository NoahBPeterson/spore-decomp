// Decompiled from SporeApp.exe (gold6 batch, worker 33).
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// 0x3c-byte property-descriptor records (same shape as slice s01351ae0)
// ---------------------------------------------------------------------------
struct PropDesc {
    const char* mName;    // +0x00
    u32 mHash;            // +0x04
    u32 mType;            // +0x08
    u32 mPad0C;           // +0x0c
    u32 mPad10;           // +0x10
    u32 mPad14;           // +0x14
    u32 mZero18;          // +0x18
    u32 mZero1C;          // +0x1c
    void* mDefault;       // +0x20
    void* mFn24;          // +0x24
    void* mFn28;          // +0x28
    void* mFn2C;          // +0x2c
    void* mFn30;          // +0x30
    void* mFn34;          // +0x34
    void* mFn38;          // +0x38
};

// 01356230 callback symbols (one per occurrence; shared only where the
// original keeps the pointer in a register across structs 2..5).
extern void E209_1_24();   // 0x00aca090
extern void E209_1_28();   // 0x00bca960
extern void E209_1_2C();   // 0x00c2e4e0
extern void E209_1_30();   // 0x00692fb0
extern void E209_1_34();   // 0x00b6f550
extern void E209_1_38();   // 0x00ac8050
extern void E209_2_24();   // 0x00ae3430
extern void E209_2_28();   // 0x00ae3450
extern void E209_2_2C();   // 0x00693150
extern void E209_2_30();   // 0x00695080
extern void E209_3_24();   // 0x00ae3430
extern void E209_3_28();   // 0x00ae3450
extern void E209_3_2C();   // 0x00693150
extern void E209_3_30();   // 0x00695080
extern void E209_4_24();   // 0x00ae3430
extern void E209_4_28();   // 0x00ae3450
extern void E209_4_2C();   // 0x00693150
extern void E209_4_30();   // 0x00695080
extern void E209_5_24();   // 0x00ae3430
extern void E209_5_28();   // 0x00ae3450
extern void E209_5_2C();   // 0x00693150
extern void E209_5_30();   // 0x00695080
extern void E209_F34();    // 0x00b1fbf0
extern void E209_F38();    // 0x00ae5720
extern void E209_6_24();   // 0x00bd0cb0
extern void E209_6_28();   // 0x00bca960
extern void E209_6_2C();   // 0x00c2e4e0
extern void E209_6_30();   // 0x00692fb0
extern void E209_6_34();   // 0x00b6f550
extern void E209_6_38();   // 0x00ac8050

// 01357d00 callback symbols
extern void E607_1_24();   // 0x00aca060
extern void E607_1_28();   // 0x00bca960
extern void E607_1_2C();   // 0x00c2e4e0
extern void E607_1_30();   // 0x00692fb0
extern void E607_1_34();   // 0x00b6f550
extern void E607_1_38();   // 0x00ac8050
extern void E607_2_24();   // 0x00572810
extern void E607_2_28();   // 0x00572840
extern void E607_2_2C();   // 0x00692ff0
extern void E607_2_30();   // 0x00694ee0
extern void E607_2_34();   // 0x00b1fbf0
extern void E607_2_38();   // 0x0057cde0
extern void E607_3_24();   // 0x00b6e3a0
extern void E607_3_28();   // 0x00ac88c0
extern void E607_3_2C();   // 0x006930f0
extern void E607_3_30();   // 0x00695010
extern void E607_3_34();   // 0x00b1fbf0
extern void E607_3_38();   // 0x00acbba0
extern void E607_4_24();   // 0x00572810
extern void E607_4_28();   // 0x00572840
extern void E607_4_2C();   // 0x00693090
extern void E607_4_30();   // 0x00694f00
extern void E607_4_34();   // 0x00b1fbf0
extern void E607_4_38();   // 0x00675ca0

// 01357eb0 callback symbols
extern void E611_24();     // 0x00bceb00
extern void E611_28();     // 0x00bd1780
extern void E611_2C();     // 0x00c2e4e0
extern void E611_30();     // 0x00692fb0
extern void E611_34();     // 0x00c87090
extern void E611_38();     // 0x00ac8050

extern "C" void* __cdecl memset(void*, int, u32);
extern "C" int   __cdecl lib_atexit(void (__cdecl*)());   // 0x011e07ef

// ---------------------------------------------------------------------------
// 01355f90 -- static array constructor (0x60 entries of 0xb8 bytes)
// ---------------------------------------------------------------------------
struct EntryB8 {
    u32 m00;          // +0x00
    u32 m04;          // +0x04
    u32 m08;          // +0x08
    u8  m0C[0x40];    // +0x0c
    u32 m4C;          // +0x4c
    u32 m50;          // +0x50
    u8  m54[0x38];    // +0x54
    u32 m8C;          // +0x8c
    f32 m90;          // +0x90
    f32 m94;          // +0x94
    u8  m98[0x08];    // +0x98
    u32 mA0;          // +0xa0
    u32 mA4;          // +0xa4
    u32 mA8;          // +0xa8
    u8  mAC[0x08];    // +0xac
    u32 mB4;          // +0xb4
};

// @ 0x01355f90
void FUN_01355f90(void)
{
    EntryB8* e = (EntryB8*)0x1695458;
    for (s32 i = 0x5f; i >= 0; --i) {
        f32 v = *(f32*)0x1473c70;
        e->m00 = 3;
        e->m04 = 0;
        e->m08 = 0xa;
        e->m50 = 0xb750af68;
        e->m8C = 0;
        e->m90 = v;
        e->m94 = v;
        memset(e->m0C, 0, 0x40);
        e->mA0 = 0;
        e->mA4 = 0;
        e->mA8 = 0;
        e->mB4 = 0;
        e->m4C = 0;
        memset(e->m54, 0, 0x38);
        ++e;
    }
    lib_atexit((void (__cdecl*)())0x13c42d0);
}

// ---------------------------------------------------------------------------
// 01356230 -- six property descriptors
// ---------------------------------------------------------------------------
// @ 0x01356230
void FUN_01356230(void)
{
    PropDesc d;

    d.mName = (const char*)0x145a45c;
    d.mHash = 0x33e0b60;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_1_24;
    d.mFn28 = (void*)E209_1_28;
    d.mFn2C = (void*)E209_1_2C;
    d.mFn30 = (void*)E209_1_30;
    d.mFn34 = (void*)E209_1_34;
    d.mFn38 = (void*)E209_1_38;
    d.mType = 0x230;
    *(PropDesc*)0x157c3d0 = d;

    d.mName = (const char*)0x14745ac;
    d.mHash = 0x33e0b61;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_2_24;
    d.mFn28 = (void*)E209_2_28;
    d.mFn2C = (void*)E209_2_2C;
    d.mFn30 = (void*)E209_2_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x20c;
    *(PropDesc*)0x157c40c = d;

    d.mName = (const char*)0x1474598;
    d.mHash = 0x33e0b62;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_3_24;
    d.mFn28 = (void*)E209_3_28;
    d.mFn2C = (void*)E209_3_2C;
    d.mFn30 = (void*)E209_3_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x200;
    *(PropDesc*)0x157c448 = d;

    d.mName = (const char*)0x1474584;
    d.mHash = 0x33e0b63;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_4_24;
    d.mFn28 = (void*)E209_4_28;
    d.mFn2C = (void*)E209_4_2C;
    d.mFn30 = (void*)E209_4_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1e8;
    *(PropDesc*)0x157c484 = d;

    d.mName = (const char*)0x1474570;
    d.mHash = 0x33e0b64;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_5_24;
    d.mFn28 = (void*)E209_5_28;
    d.mFn2C = (void*)E209_5_2C;
    d.mFn30 = (void*)E209_5_30;
    d.mFn34 = (void*)E209_F34;
    d.mFn38 = (void*)E209_F38;
    d.mType = 0x1f4;
    *(PropDesc*)0x157c4c0 = d;

    d.mName = (const char*)0x1467dac;
    d.mHash = 0x5651e69;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E209_6_24;
    d.mFn28 = (void*)E209_6_28;
    d.mFn2C = (void*)E209_6_2C;
    d.mFn30 = (void*)E209_6_30;
    d.mFn34 = (void*)E209_6_34;
    d.mFn38 = (void*)E209_6_38;
    d.mType = 0x234;
    *(PropDesc*)0x157c4fc = d;
}

// ---------------------------------------------------------------------------
// 013579e0 -- flat global initializer
// ---------------------------------------------------------------------------
// @ 0x013579e0
void FUN_013579e0(void)
{
    u32 z = 0;
    *(u32*)0x169a118 = 0x4c0cd24;
    *(u32*)0x169a11c = z;
    *(u32*)0x169a120 = z;
    *(u32*)0x169a124 = 0x4c0cd27;
    *(u32*)0x169a128 = z;
    *(u32*)0x169a12c = z;
    *(u32*)0x169a130 = 0x4c0cd26;
    *(u32*)0x169a134 = z;
    *(u32*)0x169a138 = z;
    *(u32*)0x169a13c = 0x4c0cd21;
    *(u32*)0x169a140 = z;
    *(u32*)0x169a144 = z;
    *(u32*)0x169a148 = 0x4c0cd20;
    *(u32*)0x169a14c = z;
    *(u32*)0x169a150 = z;
    *(u32*)0x169a154 = 0x4c0cd23;
    *(u32*)0x169a158 = z;
    *(u32*)0x169a15c = z;
    *(u32*)0x169a160 = 0x4c0cd22;
    *(u32*)0x169a164 = z;
    *(u32*)0x169a168 = z;
    *(u32*)0x169a16c = 0x4c0cd2d;
    *(u32*)0x169a170 = z;
    *(u32*)0x169a174 = z;
    *(u32*)0x169a178 = 0x4c0cd2c;
    *(u32*)0x169a17c = z;
    *(u32*)0x169a180 = z;
    *(u32*)0x169a184 = 0x9f82ef9c;
    *(u32*)0x169a188 = z;
    *(u32*)0x169a18c = z;
    *(u32*)0x169a190 = 0x9f82ef9d;
    *(u32*)0x169a194 = z;
    *(u32*)0x169a198 = z;
    *(u32*)0x169a19c = 0x9f82ef9e;
    *(u32*)0x169a1a0 = z;
    *(u32*)0x169a1a4 = z;
}

// ---------------------------------------------------------------------------
// 01357ae0 -- flat global initializer
// ---------------------------------------------------------------------------
// @ 0x01357ae0
void FUN_01357ae0(void)
{
    u32 z = 0;
    *(u32*)0x169a1a8 = 0xfe53e4ad;
    *(u32*)0x169a1ac = z;
    *(u32*)0x169a1b0 = z;
    *(u32*)0x169a1b4 = 0xfe53e4ae;
    *(u32*)0x169a1b8 = z;
    *(u32*)0x169a1bc = z;
    *(u32*)0x169a1c0 = 0xfe53e4af;
    *(u32*)0x169a1c4 = z;
    *(u32*)0x169a1c8 = z;
    *(u32*)0x169a1cc = 0xfe53e4a8;
    *(u32*)0x169a1d0 = z;
    *(u32*)0x169a1d4 = z;
    *(u32*)0x169a1d8 = 0xfe53e4a9;
    *(u32*)0x169a1dc = z;
    *(u32*)0x169a1e0 = z;
    *(u32*)0x169a1e4 = 0xfe53e4aa;
    *(u32*)0x169a1e8 = z;
    *(u32*)0x169a1ec = z;
    *(u32*)0x169a1f0 = 0xfe53e4ab;
    *(u32*)0x169a1f4 = z;
    *(u32*)0x169a1f8 = z;
    *(u32*)0x169a1fc = 0xfe53e4a4;
    *(u32*)0x169a200 = z;
    *(u32*)0x169a204 = z;
    *(u32*)0x169a208 = 0xfe53e4a5;
    *(u32*)0x169a20c = z;
    *(u32*)0x169a210 = z;
    *(u32*)0x169a214 = 0xff53e61c;
    *(u32*)0x169a218 = z;
    *(u32*)0x169a21c = z;
    *(u32*)0x169a220 = 0xff53e61b;
    *(u32*)0x169a224 = z;
    *(u32*)0x169a228 = z;
    *(u32*)0x169a22c = 0xff53e61a;
    *(u32*)0x169a230 = z;
    *(u32*)0x169a234 = z;
    *(u32*)0x169a238 = 0xff53e619;
    *(u32*)0x169a23c = z;
    *(u32*)0x169a240 = z;
    *(u32*)0x169a244 = 0xff53e618;
    *(u32*)0x169a248 = z;
    *(u32*)0x169a24c = z;
    *(u32*)0x169a250 = 0xff53e617;
    *(u32*)0x169a254 = z;
    *(u32*)0x169a258 = z;
    *(u32*)0x169a25c = 0xff53e616;
    *(u32*)0x169a260 = z;
    *(u32*)0x169a264 = z;
}

// ---------------------------------------------------------------------------
// 01357d00 -- four property descriptors
// ---------------------------------------------------------------------------
// @ 0x01357d00
void FUN_01357d00(void)
{
    PropDesc d;

    d.mName = (const char*)0x14669f8;
    d.mHash = 0x3b0990b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E607_1_24;
    d.mFn28 = (void*)E607_1_28;
    d.mFn2C = (void*)E607_1_2C;
    d.mFn30 = (void*)E607_1_30;
    d.mFn34 = (void*)E607_1_34;
    d.mFn38 = (void*)E607_1_38;
    d.mType = 0x0;
    *(PropDesc*)0x157c920 = d;

    d.mName = (const char*)0x1474f20;
    d.mHash = 0x3b0990c;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E607_2_24;
    d.mFn28 = (void*)E607_2_28;
    d.mFn2C = (void*)E607_2_2C;
    d.mFn30 = (void*)E607_2_30;
    d.mFn34 = (void*)E607_2_34;
    d.mFn38 = (void*)E607_2_38;
    d.mType = 0x10;
    *(PropDesc*)0x157c95c = d;

    d.mName = (const char*)0x1474f14;
    d.mHash = 0x5135515;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E607_3_24;
    d.mFn28 = (void*)E607_3_28;
    d.mFn2C = (void*)E607_3_2C;
    d.mFn30 = (void*)E607_3_30;
    d.mFn34 = (void*)E607_3_34;
    d.mFn38 = (void*)E607_3_38;
    d.mType = 0x4;
    *(PropDesc*)0x157c998 = d;

    d.mName = (const char*)0x1474f08;
    d.mHash = 0x3b0990e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E607_4_24;
    d.mFn28 = (void*)E607_4_28;
    d.mFn2C = (void*)E607_4_2C;
    d.mFn30 = (void*)E607_4_30;
    d.mFn34 = (void*)E607_4_34;
    d.mFn38 = (void*)E607_4_38;
    d.mType = 0x14;
    *(PropDesc*)0x157c9d4 = d;
}

// ---------------------------------------------------------------------------
// 01357eb0 -- one property descriptor
// ---------------------------------------------------------------------------
// @ 0x01357eb0
void FUN_01357eb0(void)
{
    PropDesc d;

    d.mName = (const char*)0x1474f28;
    d.mHash = 0x4179882;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)E611_24;
    d.mFn28 = (void*)E611_28;
    d.mFn2C = (void*)E611_2C;
    d.mFn30 = (void*)E611_30;
    d.mFn34 = (void*)E611_34;
    d.mFn38 = (void*)E611_38;
    d.mType = 0x0;
    *(PropDesc*)0x157ca50 = d;
}
