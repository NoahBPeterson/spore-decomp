// Slice s01244f50 (/Od part) -- compiler-generated global dynamic initializers
// ($E / ??__E style: table of property descriptors, eastl containers, atexit
// registrations) and small global setters that copy defaults into the live
// globals.  Code shape: ebp frame, everything materialised in memory.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE
#include <stddef.h>
#include <math.h>
#pragma intrinsic(log)

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

extern "C" int atexit(void (__cdecl*)());

// --- callees ---------------------------------------------------------------
extern void FUN_004be950(void);   // 0x4be950
extern void FUN_004bead0(void);   // 0x4bead0
extern void FUN_004beb70(void);   // 0x4beb70
extern void FUN_004bebd0(void);   // 0x4bebd0
extern void FUN_004bec30(void);   // 0x4bec30
extern void FUN_004bec80(void);   // 0x4bec80
extern void FUN_004be8d0(void);   // 0x4be8d0
extern void FUN_004be820(void);   // 0x4be820
extern void FUN_013bcc30(void);   // 0x13bcc30
extern void FUN_013bcc50(void);   // 0x13bcc50
extern void FUN_013bcc70(void);   // 0x13bcc70
extern void FUN_013bcd30(void);   // 0x13bcd30
extern void FUN_013bcd70(void);   // 0x13bcd70
extern void FUN_013bce80(void);   // 0x13bce80
extern void FUN_013bcea0(void);   // 0x13bcea0
extern void FUN_013bcec0(void);   // 0x13bcec0

extern "C" void __stdcall vector_constructor_iterator(
    void* p, unsigned int elemSize, unsigned int count, void (*ctor)(void*));  // 0x401930
extern void FUN_00402ab0(void* p);  // 0x402ab0

struct AllocTag { AllocTag() {} };
struct Rbtree {
    Rbtree* ctor(const AllocTag& tag);   // 0x4b5980
};

extern "C" void* __cdecl EAAllocate(
    unsigned int size, const char* name, int a, int b, int c, int d);  // 0xf473a0

struct NewObj;
struct NewObj {
    NewObj* Ctor(int a, int b, int c);   // 0x51d690
    void V0();
};

struct FixedAllocatorBase {
    void ctor(unsigned int a, unsigned int b, unsigned int c, void* d,
              unsigned int e, void* (*f)(unsigned int, void*),
              void (*g)(void*, void*), unsigned int h);   // 0x926720
};

// --- property descriptor table --------------------------------------------
struct PropDesc {
    uint32_t offset;      // +0x00
    uint32_t size;        // +0x04
    uint32_t reserved;    // +0x08
    const wchar_t* name;  // +0x0c
    uint32_t type;        // +0x10
    void* getter;         // +0x14
};

// Views of the object the property descriptors point into; the byte layout is
// only used for offsetof() (the descriptor stores the byte offset).  The rows
// members are 12-byte elements so offsetof(S, rows[k]) == base + 12*k, which is
// exactly the imul/add sequence the original emits.
struct Vec3 { float x, y, z; };
struct ViewRowsA { int paintregion; char pad[0x34]; Vec3 rows[3]; };  // rows at 0x38
struct ViewRowsB { char pad[0x5c]; Vec3 rows[3]; };                    // rows at 0x5c
struct ViewPaint { int paintregion; };                                 // at 0x00
struct ViewPaintId { char pad[0xd8]; int paintid; };
struct ViewColor1 { char pad[0xf8]; int color1; };
struct ViewColor2 { char pad[0x118]; Vec3 color2; };
struct ViewPaintBlob { char pad[0x178]; Vec3 paint; };
struct ViewBlockRef { int blockref; };
struct ViewZCorpScore { int zcorpscore; };
struct ViewAsym { char pad[4]; int isasymmetric; };

#define FLD(i, m) (*(uint32_t*)(0x150c720 + (i) * 0xc + (m)))
#define OFF(S, m) ((uint32_t)offsetof(S, m))

// @ 0x01244f50
void init_150c720()
{
    FLD(0, 0) = OFF(ViewRowsA, rows[0]);
    FLD(0, 4) = 12;
    FLD(0, 8) = 0;
    FLD(0, 12) = (uint32_t)L"row1";
    FLD(0, 16) = 1;
    FLD(0, 20) = (uint32_t)FUN_004be950;

    FLD(1, 0) = OFF(ViewRowsA, rows[1]);
    FLD(1, 4) = 12;
    FLD(1, 8) = 0;
    FLD(1, 12) = (uint32_t)L"row2";
    FLD(1, 16) = 1;
    FLD(1, 20) = (uint32_t)FUN_004be950;

    FLD(2, 0) = OFF(ViewRowsA, rows[2]);
    FLD(2, 4) = 12;
    FLD(2, 8) = 0;
    FLD(2, 12) = (uint32_t)L"userorientation_row0";
    FLD(2, 16) = 1;
    FLD(2, 20) = (uint32_t)FUN_004be950;

    FLD(3, 0) = OFF(ViewRowsB, rows[0]);
    FLD(3, 4) = 12;
    FLD(3, 8) = 0;
    FLD(3, 12) = (uint32_t)L"userorientation_row1";
    FLD(3, 16) = 1;
    FLD(3, 20) = (uint32_t)FUN_004be950;

    FLD(4, 0) = OFF(ViewRowsB, rows[1]);
    FLD(4, 4) = 12;
    FLD(4, 8) = 0;
    FLD(4, 12) = (uint32_t)L"userorientation_row2";
    FLD(4, 16) = 1;
    FLD(4, 20) = (uint32_t)FUN_004be950;

    FLD(5, 0) = OFF(ViewRowsB, rows[2]);
    FLD(5, 4) = 12;
    FLD(5, 8) = 0;
    FLD(5, 12) = (uint32_t)L"weight";
    FLD(5, 16) = 1;
    FLD(5, 20) = (uint32_t)FUN_004bead0;

    FLD(6, 0) = 0;
    FLD(6, 4) = 4;
    FLD(6, 8) = 0;
    FLD(6, 12) = (uint32_t)L"paintregion";
    FLD(6, 16) = 1;
    FLD(6, 20) = (uint32_t)FUN_004beb70;

    FLD(7, 0) = OFF(ViewPaintId, paintid);
    FLD(7, 4) = 4;
    FLD(7, 8) = 0;
    FLD(7, 12) = (uint32_t)L"paintid";
    FLD(7, 16) = 1;
    FLD(7, 20) = (uint32_t)FUN_004beb70;

    FLD(8, 0) = OFF(ViewColor1, color1);
    FLD(8, 4) = 4;
    FLD(8, 8) = 0;
    FLD(8, 12) = (uint32_t)L"color1";
    FLD(8, 16) = 1;
    FLD(8, 20) = (uint32_t)FUN_004bebd0;

    FLD(9, 0) = OFF(ViewColor2, color2);
    FLD(9, 4) = 12;
    FLD(9, 8) = 0;
    FLD(9, 12) = (uint32_t)L"color2";
    FLD(9, 16) = 1;
    FLD(9, 20) = (uint32_t)FUN_004bebd0;

    FLD(10, 0) = OFF(ViewPaintBlob, paint);
    FLD(10, 4) = 12;
    FLD(10, 8) = 0;
    FLD(10, 12) = (uint32_t)L"paint";
    FLD(10, 16) = 1;
    FLD(10, 20) = (uint32_t)FUN_004bec30;

    FLD(11, 0) = 0;
    FLD(11, 4) = 4;
    FLD(11, 8) = 0;
    FLD(11, 12) = (uint32_t)L"blockref";
    FLD(11, 16) = 1;
    FLD(11, 20) = (uint32_t)FUN_004bec80;

    FLD(12, 0) = 0;
    FLD(12, 4) = 4;
    FLD(12, 8) = 0;
    FLD(12, 12) = (uint32_t)L"zcorpscore";
    FLD(12, 16) = 0;
    FLD(12, 20) = (uint32_t)FUN_004be8d0;

    FLD(13, 0) = 4;
    FLD(13, 4) = 4;
    FLD(13, 8) = 0;
    FLD(13, 12) = (uint32_t)L"isasymmetric";
    FLD(13, 16) = 1;
    FLD(13, 20) = (uint32_t)FUN_004be820;

    FLD(28, 0) = 0x81;
    FLD(28, 4) = 1;
}

// @ 0x0124aa60  (compiled with /Oi so log() is the _CIlog intrinsic)
void init_15d98f0()
{
    float t = 1e-6f;
    *(float*)0x15d98f0 = (float)log(t);
}

// @ 0x0124aab0
void init_15d9834()
{
    *(float*)0x15d9834 = *(float*)0x15d9bc4;
    *(float*)0x15d9838 = *(float*)0x15d9bc8;
}

// @ 0x0124aae0
void init_15d9764()
{
    *(float*)0x15d9764 = *(float*)0x15d9bc4;
    *(float*)0x15d9768 = *(float*)0x15d9bc8;
}

// @ 0x0124ab10
void init_15d9a68()
{
    *(float*)0x15d9a68 = *(float*)0x15d9bc4;
    *(float*)0x15d9a6c = *(float*)0x15d9bc8;
}

// @ 0x0124ab80
void init_15d992c()
{
    *(float*)0x15d992c = 1.0f;
    *(float*)0x15d9930 = 1.0f;
}

// @ 0x01250270
void init_15da7d4()
{
    extern const wchar_t g_1667bac;   // 0x1667bac  eastl::gEmptyString16
    uint32_t unused;
    *(void**)0x15da7d4 = 0;
    *(void**)0x15da7d8 = 0;
    *(void**)0x15da7dc = 0;
    *(const wchar_t**)0x15da7d4 = &g_1667bac;
    *(void**)0x15da7d8 = *(void**)0x15da7d4;
    *(const wchar_t**)0x15da7dc = (const wchar_t*)((uint32_t)*(void**)0x15da7d4 + 2);
    atexit(&FUN_013bcc30);
}

// @ 0x012502d0
void init_15da960()
{
    AllocTag tag;
    ((Rbtree*)0x15da960)->ctor(tag);
    atexit(&FUN_013bcc50);
}

// @ 0x01250300
void init_15da884()
{
    AllocTag tag;
    ((Rbtree*)0x15da884)->ctor(tag);
    atexit(&FUN_013bcc70);
}

struct PackedColor {
    uint32_t low : 8;    // bits 0-7
    uint32_t g : 8;      // bits 8-15
    uint32_t r : 8;      // bits 16-23
    uint32_t hi : 8;     // bits 24-31
};

// @ 0x01250330
void init_15dacc8()
{
    uint32_t v = 0;
    v = (v & 0x3fffffffu) | 0x40000000u;
    ((PackedColor&)v).r = 0x62;
    ((PackedColor&)v).g = 0x60;
    *(uint32_t*)0x15dacc8 = 0xa077208c;
    *(uint32_t*)0x15daccc = 0;
    *(uint32_t*)0x15dacd0 = v;
}

// @ 0x012503b0
void init_15dabcc()
{
    uint32_t v = 0;
    v = (v & 0x3fffffffu) | 0x40000000u;
    ((PackedColor&)v).r = 0x62;
    ((PackedColor&)v).g = 0x60;
    *(uint32_t*)0x15dabcc = 0x6b2c0771;
    *(uint32_t*)0x15dabd0 = 0;
    *(uint32_t*)0x15dabd4 = v;
}

// @ 0x01259610
void init_15dd784()
{
    *(float*)0x15dd784 = 1.0f / (*(float*)0x15dd6e0 * 0.3f);
}

// @ 0x0125bd80
void init_15de138()
{
    extern const char kEditorAllocName;   // 0x13eb430
    void* p = EAAllocate(0x2c, &kEditorAllocName, 0, 0, 0, 0);
    NewObj* obj = p ? ((NewObj*)p)->Ctor(4, 4, -1) : 0;
    *(NewObj**)0x15de138 = obj;
    if (*(NewObj**)0x15de138)
        (*(NewObj**)0x15de138)->V0();
    atexit(&FUN_013bcd30);
}

// @ 0x0125dbc0
void init_15de57c()
{
    uint32_t v = 0;
    v = (v & 0x3fffffffu) | 0x40000000u;
    ((PackedColor&)v).r = 0;
    ((PackedColor&)v).g = 0x22;
    *(uint32_t*)0x15de57c = v;
}

// @ 0x0125dc40
void init_15de2a0()
{
    ((FixedAllocatorBase*)0x15de2a0)->ctor(0x50, 0, 0x80, 0, 0xffffffffu, 0, 0, 0);
    atexit(&FUN_013bcd70);
}

// @ 0x0125fa80
void init_15dec08()
{
    *(uint32_t*)0x15dec08 = 0;
    *(uint32_t*)0x15dec0c = 0;
    *(uint32_t*)0x15dec10 = 0;
}

// @ 0x01261040
void init_15df0f0()
{
    *(float*)0x15df0f0 = *(float*)0x15df2cc;
    *(float*)0x15df0f4 = *(float*)0x15df2d0;
    *(float*)0x15df0f8 = *(float*)0x15df2d4;
    *(float*)0x15df0fc = *(float*)0x15df2cc;
    *(float*)0x15df100 = *(float*)0x15df2d0;
    *(float*)0x15df104 = *(float*)0x15df2d4;
    *(float*)0x15df108 = *(float*)0x15df2cc;
    *(float*)0x15df10c = *(float*)0x15df2d0;
    *(float*)0x15df110 = *(float*)0x15df2d4;
}

// @ 0x012610e0
void init_15df204()
{
    *(float*)0x15df204 = 0.0f;
    *(float*)0x15df208 = 0.0f;
    *(float*)0x15df20c = 1.0f;
    *(float*)0x15df210 = 0.0f;
    *(float*)0x15df214 = 0.0f;
    *(float*)0x15df218 = 1.0f;
    *(float*)0x15df21c = 0.0f;
    *(float*)0x15df220 = 0.0f;
    *(float*)0x15df224 = 1.0f;
}

// @ 0x0126c8c0
void init_15e2d08()
{
    int n = 8;
    char* p = (char*)0x15e2d08;
    for (;;) {
        n--;
        if (n < 0)
            break;
        p += 4;
    }
}

// @ 0x0126c8f0
void init_15e2a38()
{
    int n = 6;
    char* p = (char*)0x15e2a38;
    for (;;) {
        n--;
        if (n < 0)
            break;
        vector_constructor_iterator(p + 0x10, 4, 4, &FUN_00402ab0);
        p += 0x20;
    }
}

// @ 0x0126dae0
void init_15e2e48()
{
    *(uint32_t*)0x15e2e48 = 0;
    *(uint32_t*)0x15e2e4c = 0;
    *(uint32_t*)0x15e2e50 = 0;
    bool b = false;
    atexit(&FUN_013bce80);
}

// @ 0x0126db20
void init_15e2da8()
{
    *(uint32_t*)0x15e2da8 = 0;
    *(uint32_t*)0x15e2dac = 0;
    *(uint32_t*)0x15e2db0 = 0;
    bool b = false;
    atexit(&FUN_013bcea0);
}

// @ 0x0126db60
void init_15e2f54()
{
    *(uint32_t*)0x15e2f54 = 0;
    *(uint32_t*)0x15e2f58 = 0;
    *(uint32_t*)0x15e2f5c = 0;
    bool b = false;
    atexit(&FUN_013bcec0);
}

// @ 0x0126ecd0
void init_15e3294()
{
    *(uint32_t*)0x15e3294 = 0x1749a6e;
    *(uint32_t*)0x15e3298 = 0x1749a6e;
    *(uint32_t*)0x15e329c = 1;
}

// @ 0x0126ed00
void init_15e3188()
{
    *(void**)0x15e3188 = (void*)0x140b5a0;
    *(void**)0x15e3188 = (void*)0x13f3da8;
}

// @ 0x01274080
void init_15e3f18()
{
    *(uint32_t*)0x15e3f18 = 0x5358d0c;
    *(uint32_t*)0x15e3f1c = 0x5358d0c;
    *(uint32_t*)0x15e3f20 = 1;
}
