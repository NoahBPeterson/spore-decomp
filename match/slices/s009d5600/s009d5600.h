// Slice s009d5600 — an anonymous animated-event/player object (Ghidra FUN_*;
// a related symbol is SP::cSPEditorAnimatedEventInfo).  Four quaternion/
// stepping helpers operating on a shared object plus an external "info"
// object.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#pragma once

typedef unsigned int u32;
typedef unsigned char u8;

struct Q4 { float x, y, z, w; };

struct Ent;

// ---------------------------------------------------------------------------
// The second object (the "info"): the one reached through Ent::o_c8 in the
// rotation helpers and through Ent::o48 in the distance helper.
// ---------------------------------------------------------------------------
struct Obj48
{
    u8     pad00[8];
    float  f08;            // +0x08
    float  f0c;            // +0x0c
    u8     pad10[0x24 - 0x10];
    void*  o24;            // +0x24
    u8     pad28[0x80 - 0x28];
    float  f80;            // +0x80
};

// The animated-event info object; only ever accessed through byte offsets.
struct Obj2
{
    u8 raw[0x1700];
};

// ---------------------------------------------------------------------------
// The object itself.  Field names are raw offsets, because the same storage is
// reinterpreted at several layers.
// ---------------------------------------------------------------------------
struct Ent
{
    u8     pad00[0x24];
    Q4     v24;            // +0x24
    u8     pad34[0x48 - 0x34];
    Obj48* o48;            // +0x48
    u8     pad4c[0x58 - 0x4c];
    int    o58;            // +0x58
    u8     o5c;            // +0x5c
    u8     o5d;            // +0x5d
    u8     pad5e[2];
    float  f60;            // +0x60
    void*  o64;            // +0x64
    void*  o68;            // +0x68
    float  f6c;            // +0x6c
    u8     pad70[8];
    float  f78;            // +0x78
    float  f7c;            // +0x7c
    float  f80;            // +0x80
    float  f84;            // +0x84
    Q4     q88;            // +0x88
    float  f98;            // +0x98
    float  f9c;            // +0x9c
    float  fa0;            // +0xa0
    float  fa4;            // +0xa4
    float  fa8;            // +0xa8
    float  fac;            // +0xac
    float  fb0;            // +0xb0
    float  fb4;            // +0xb4
    u8     padb8[4];
    int*   o_bc;           // +0xbc
    u8     padc0[8];
    Obj2*  o_c8;           // +0xc8
    u8     padcc[4];
    float  fd0;            // +0xd0
    float  fd4;            // +0xd4
    float  fd8;            // +0xd8
    float  fdc;            // +0xdc
    u8     pade0[8];
    float  fe8;            // +0xe8
    u8     padec[4];
    float  ff0;            // +0xf0
    u8     padf4[4];
    float  ff8;            // +0xf8
    u8     padfc[4];
    float  f100;           // +0x100
    float  f104;           // +0x104

    void  Fn5600(Ent* p, float a);                                        // 0x009d5600
    void  Fn5b50(Ent* p, float a);                                        // 0x009d5b50
    void  Fn5f10(Ent* p, float a, float b, float c, float d);             // 0x009d5f10
    float Fn62a0(float d);                                                // 0x009d62a0

    // Collaborators (bodies live in other translation units of the original).
    void  FnCeec0(float* out, float v);                                   // 0x009ceec0
    void  FnCf080(Ent* p, float a, float b);                              // 0x009cf080
    void  Fn49b0(Ent* p, float a, float b);                               // 0x009d49b0
    void  Fn42b0(Ent* p);                                                 // 0x009d42b0
    void  Fn46d0(Ent* p);                                                 // 0x009d46d0
    void  Fn52f0(Ent* p, float a, float b, float c, float d, float e, float f); // 0x009d52f0
};

// ---------------------------------------------------------------------------
// Free functions.
// ---------------------------------------------------------------------------
// 0x009b3050 — table probe; the object sits at info+0x150.
struct XKey { bool IsInTable(u32 key, u8 def); };                 // 0x009b3050
// 0x0099c0b0 — quaternion multiply; returns its destination pointer.
Q4*  __cdecl QuatMul(Q4* out, const Q4* a, const Q4* b);          // 0x0099c0b0

// 0x009ce010 — static leaf helper: pointer in eax, float on the stack.
static __declspec(noinline) void H9ce010(Q4* out, float v);

// ---------------------------------------------------------------------------
// Float/int constants (names carry the address so the relocation resolver can
// bind them).
// ---------------------------------------------------------------------------
extern const float g_1470f1c;   // 0x01470f1c  2.0f
extern const float g_1485720;   // 0x01485720  1.0f
extern const float g_13eb8b0;   // 0x013eb8b0 -0.0f
extern const float g_1485378;   // 0x01485378  0.0f
extern const float g_14479b0;   // 0x014479b0  1e-6f
extern const float g_13eb1bc;   // 0x013eb1bc -1.0f
extern const float g_1471064;   // 0x01471064  0.5f
extern const float g_13ec488;   // 0x013ec488 -0.5f
extern const float g_155125c;   // 0x0155125c  100.0f
extern const float g_1551520;   // 0x01551520  3.0f
extern const float g_13f89bc;   // 0x013f89bc  1e-5f
extern const float g_15514e4;   // 0x015514e4  1.0f
extern const float g_1551524;   // 0x01551524  0.1f
extern const int   g_15515dc;   // 0x015515dc  int 1
extern const int   g_15509e0;   // 0x015509e0  int 1
