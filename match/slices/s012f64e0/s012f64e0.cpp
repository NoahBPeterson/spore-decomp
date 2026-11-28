// Slice s012f64e0 -- dynamic initializers for global math objects (vectors,
// 3x3/4x4 matrices) plus their accessors.  /O2 /arch:SSE (movss/xmm stores).

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1547690[];
extern "C" char g_154df38[];
extern "C" char g_164b210[];
extern "C" char g_164b25c[];
extern "C" char g_164b260[];
extern "C" char g_164b264[];
extern "C" char g_164b268[];
extern "C" char g_164b28c[];
extern "C" char g_164b290[];
extern "C" char g_164b294[];
extern "C" char g_164b2d0[];
extern "C" char g_164b35c[];
extern "C" char g_164b360[];
extern "C" char g_164b364[];
extern "C" char g_164b368[];
extern "C" char g_164b384[];
extern "C" char g_164b388[];
extern "C" char g_164b38c[];
extern "C" char g_164b390[];
extern "C" char g_164b3a0[];
extern "C" char g_164b3f0[];
extern "C" char g_164b400[];
extern "C" char g_164b404[];
extern "C" char g_164b408[];
extern "C" char g_164b40c[];
extern "C" char g_164b42c[];
extern "C" char g_164b430[];
extern "C" char g_164b434[];
extern "C" char g_164b438[];
extern "C" char g_164b45c[];
extern "C" char g_164b460[];
extern "C" char g_164b468[];
extern "C" char g_164b4e0[];
extern "C" char g_164b4e4[];
extern "C" char g_164b4e8[];
extern "C" char g_164b4ec[];
extern "C" char g_164b4f0[];
extern "C" char g_164f018[];
extern "C" char g_164f03c[];
extern "C" char g_16514ec[];
extern "C" char g_16679d0[];
extern "C" char g_1667a58[];
extern "C" char g_1667c00[];
extern "C" char g_16688a0[];
extern "C" char g_1668ef8[];
extern "C" char g_1668efc[];

#include <intrin.h>
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// Global object whose "lock/bootstrap" member is called before the stores
// (FUN_00572590 / FUN_00402ab0).
struct GlobalLock {
    void bootstrap();          // FUN_00572590
    void bootstrapMatrix();    // FUN_00402ab0
};

// Opaque constructors writing into a caller-provided buffer.
extern void Vector2_SetZero(void* out);      // 0x00401160
extern void Vector2_SetOne(void* out);       // 0x00401190
extern void Matrix3_SetIdentity(void* out);  // 0x00401490
extern void Matrix3_SetZero(void* out);      // 0x00401540
extern void Matrix4_SetIdentity(void* out);  // 0x004015f0
extern void Matrix4_SetZero(void* out);      // 0x00401720

struct Vector2f { float x, y; };
struct Vector4f {
    float x, y, z, w;
    void Set(float ax, float ay, float az, float aw)
    {
        x = ax;
        y = ay;
        z = az;
        w = aw;
    }
};
struct Mat3 { uint32_t d[9]; };
struct Mat4 { uint32_t d[16]; };

// @ 0x012f64e0
void init_164b42c()
{
    ((GlobalLock*)g_164b42c)->bootstrap();
    *(float*)g_164b42c = 1.0f;
    *(float*)g_164b430 = 0.0f;
    *(float*)g_164b434 = 1.0f;
    *(float*)g_164b438 = 1.0f;
}

// @ 0x012f6520
void init_164b400()
{
    ((GlobalLock*)g_164b400)->bootstrap();
    *(float*)g_164b400 = 1.0f;
    *(float*)g_164b404 = 1.0f;
    *(float*)g_164b408 = 0.0f;
    *(float*)g_164b40c = 1.0f;
}

// @ 0x012f6560
void init_164b384()
{
    ((GlobalLock*)g_164b384)->bootstrap();
    *(float*)g_164b384 = 0.0f;
    *(float*)g_164b388 = 1.0f;
    *(float*)g_164b38c = 1.0f;
    *(float*)g_164b390 = 1.0f;
}

// @ 0x012f65a0
void init_164b3f0()
{
    ((GlobalLock*)g_164b3f0)->bootstrap();
    ((Vector4f*)g_164b3f0)->Set(1.0f, 0.5f, 0.0f, 1.0f);
}

// @ 0x012f65e0
void init_164b25c()
{
    ((GlobalLock*)g_164b25c)->bootstrap();
    *(float*)g_164b25c = 1.0f;
    *(float*)g_164b260 = 1.0f;
    *(float*)g_164b264 = 1.0f;
    *(float*)g_164b268 = 0.0f;
}

// @ 0x012f6620
void init_164b35c()
{
    ((GlobalLock*)g_164b35c)->bootstrap();
    *(float*)g_164b35c = 0.0f;
    *(float*)g_164b360 = 0.0f;
    *(float*)g_164b364 = 0.0f;
    *(float*)g_164b368 = 0.0f;
}

// @ 0x012f6650
extern float g_13eb188;  // 0x3e991687
extern float g_13eb184;  // 0x3f1645a2
extern float g_13eb180;  // 0x3de978d5
void init_164b28c()
{
    ((GlobalLock*)g_164b28c)->bootstrap();
    *(float*)g_164b28c = g_13eb188;
    *(float*)g_164b290 = g_13eb184;
    *(float*)g_164b294 = g_13eb180;
}

// @ 0x012f6690
extern float g_13eb194;
extern float g_13eb190;
extern float g_13eb18c;
void init_164b4e8()
{
    ((GlobalLock*)g_164b4e8)->bootstrap();
    *(float*)g_164b4e8 = g_13eb194;
    *(float*)g_164b4ec = g_13eb190;
    *(float*)g_164b4f0 = g_13eb18c;
}

// @ 0x012f66f0
void init_164b4e0()
{
    Vector2f v;
    Vector2_SetZero(&v);
    ((GlobalLock*)g_164b4e0)->bootstrap();
    *(float*)g_164b4e0 = v.x;
    *(float*)g_164b4e4 = v.y;
}

// @ 0x012f6730
void init_164b45c()
{
    Vector2f v;
    Vector2_SetOne(&v);
    ((GlobalLock*)g_164b45c)->bootstrap();
    *(float*)g_164b45c = v.x;
    *(float*)g_164b460 = v.y;
}

// @ 0x012f6b40
void init_164b3a0()
{
    Mat3 m;
    Matrix3_SetIdentity(&m);
    ((GlobalLock*)g_164b3a0)->bootstrapMatrix();
    *(Mat3*)g_164b3a0 = m;
}

// @ 0x012f6b80
void init_164b210()
{
    Mat3 m;
    Matrix3_SetZero(&m);
    ((GlobalLock*)g_164b210)->bootstrapMatrix();
    *(Mat3*)g_164b210 = m;
}

// @ 0x012f6bc0
void init_164b468()
{
    Mat4 m;
    Matrix4_SetIdentity(&m);
    ((GlobalLock*)g_164b468)->bootstrapMatrix();
    *(Mat4*)g_164b468 = m;
}

// @ 0x012f6c00
void init_164b2d0()
{
    Mat4 m;
    Matrix4_SetZero(&m);
    ((GlobalLock*)g_164b2d0)->bootstrapMatrix();
    *(Mat4*)g_164b2d0 = m;
}

// ---------------------------------------------------------------------------
// Static initializers (the "type registry" ones are /Od: frame pointer, and
// 16-bit fields are materialized through a register).
// ---------------------------------------------------------------------------
extern "C" int atexit(void (__cdecl*)());

#include <stddef.h>
// Descriptive view of the 20-byte vector storage at 0x01651994.
struct InitVectorStorage {
    void* begin;
    void* end;
    void* capacity;
    void* allocator;
    int state;
};
typedef char InitVectorStorageSize[(sizeof(InitVectorStorage) == 20) ? 1 : -1];
typedef char InitVectorStorageBeginOffset[(offsetof(InitVectorStorage, begin) == 0) ? 1 : -1];
typedef char InitVectorStorageEndOffset[(offsetof(InitVectorStorage, end) == 4) ? 1 : -1];
typedef char InitVectorStorageCapacityOffset[(offsetof(InitVectorStorage, capacity) == 8) ? 1 : -1];
typedef char InitVectorStorageStateOffset[(offsetof(InitVectorStorage, state) == 16) ? 1 : -1];
typedef char InitVectorStorageAllocatorOffset[(offsetof(InitVectorStorage, allocator) == 12) ? 1 : -1];
extern InitVectorStorage g_1651994;

struct C0 { void m(); };
struct TextStyle { void ctor(); };
struct SetMode { void SetMode2(int); };
struct BufC { void init(void* alloc); };

extern void FUN_013c0300(void);
extern void FUN_013c0320(void);
extern void FUN_013c08c0(void);
extern void FUN_013c0930(void);
extern void FUN_013c0940(void);
extern void FUN_013c0ba0(void);
extern void FUN_013c0c00(void);
extern void FUN_013c0c50(void);
extern void FUN_013c0cc0(void);
extern void FUN_013c0d40(void);

extern void* EAAlloc(unsigned int size, void* name, int a, int b, const char* file, int line);
extern void* __stdcall GetDefaultAllocator2(int a, int b);
extern void* GetDefaultAllocator0();
extern void* FUN_0089a570(void);
extern int   InitXInputFunctions();
extern "C" int __declspec(dllimport) __stdcall TlsAlloc();
extern "C" void __declspec(dllimport) __stdcall InitializeCriticalSection(void* cs);

// Type-registry entry layout (stride 0x18).  f0 is a pointer for the first
// entry of each table, otherwise a small integer id.
struct TypeRegEntry {
    void* f0;       // +0x00
    int   f1;       // +0x04
    short f2;       // +0x08
    short f3;       // +0x0a
    int   f4;       // +0x0c
    int   f5;       // +0x10
    int   f6;       // +0x14
};

// @ 0x012f6d30
void init_164b410()
{
    *(int*)0x164b410 = 0;
    atexit(&FUN_013c0300);
}

// @ 0x012f6d50
void init_164b414()
{
    ((C0*)0x164b414)->m();
    atexit(&FUN_013c0320);
}

// @ 0x012f6d80
void init_154273c()
{
    *(int*)0x154273c = 1;
    *(int*)0x1542740 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x1542744;
    e[0].f0 = (void*)0x1415464; e[0].f1 = 0x3335c13; e[0].f2 = 0x13; e[0].f4 = 0x28; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = (void*)0x1415464; e[1].f1 = 0x3335c14; e[1].f2 = 0x13; e[1].f4 = 0x2c; e[1].f5 = 1; e[1].f6 = 0;
    e[2].f0 = (void*)0x1415464; e[2].f1 = 0x3335c15; e[2].f2 = 0x13; e[2].f4 = 0x30; e[2].f5 = 1;
}

// @ 0x012f6e50
void init_154279c()
{
    *(int*)0x154279c = 1;
    *(int*)0x15427a0 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x15427a4;
    e[0].f0 = (void*)0x1415464; e[0].f1 = 0x3335c13; e[0].f2 = 0x13; e[0].f4 = 0x30; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = (void*)0x1415464; e[1].f1 = 0x3335c14; e[1].f2 = 0x13; e[1].f4 = 0x34; e[1].f5 = 1; e[1].f6 = 0;
    e[2].f0 = (void*)0x1415464; e[2].f1 = 0x3335c15; e[2].f2 = 0x13; e[2].f4 = 0x38; e[2].f5 = 1; e[2].f6 = 0;
    e[3].f0 = (void*)0x1415b08; e[3].f1 = 0x3335c41; e[3].f2 = 0x13; e[3].f4 = 0x4c; e[3].f5 = 1; e[3].f6 = 0;
    e[4].f0 = (void*)0x1415b08; e[4].f1 = 0x3335c42; e[4].f2 = 0x13; e[4].f4 = 0x50; e[4].f5 = 1; e[4].f6 = 0;
    e[5].f0 = (void*)0x1415b08; e[5].f1 = 0x3335c43; e[5].f2 = 0x13; e[5].f4 = 0x54; e[5].f5 = 1; e[5].f6 = 0;
    e[6].f0 = (void*)0x1415b08; e[6].f1 = 0x3335c44; e[6].f2 = 0x13; e[6].f4 = 0x58; e[6].f5 = 1;
}

// @ 0x012f7570
void init_1542c44()
{
    *(int*)0x1542c44 = 1;
    *(int*)0x1542c48 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x1542c4c;
    e[0].f0 = (void*)0x1416034; e[0].f1 = 0x254cdfc; e[0].f2 = 0x13; e[0].f4 = 0x40; e[0].f5 = 1;
}

// @ 0x012fc2b0
void init_1546064()
{
    *(int*)0x1546064 = 1;
    *(int*)0x1546068 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x154606c;
    e[0].f0 = (void*)0x1418fd8; e[0].f1 = 0x4c9a86d; e[0].f2 = 0x13; e[0].f4 = 0x88c; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = (void*)0x1418fd8; e[1].f1 = 0x4c9a86e; e[1].f2 = 0x13; e[1].f4 = 0x890; e[1].f5 = 1;
}

// @ 0x012fdc00
void init_164e9f8()
{
    void* p = EAAlloc(0x40, (void*)0x13f6b3c, 0, 0,
                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    *(void**)0x164e9f8 = p;
    *(void**)0x164ea00 = (char*)p + 0x40;
    ((int*)p)[0] = 0;
    ((int*)*(void**)0x164e9f8)[1] = 0;
    ((int*)*(void**)0x164e9f8)[2] = 0;
    ((int*)*(void**)0x164e9f8)[3] = 0;
    ((int*)*(void**)0x164e9f8)[4] = 0;
    ((int*)*(void**)0x164e9f8)[5] = 0;
    ((int*)*(void**)0x164e9f8)[6] = 0;
    ((int*)*(void**)0x164e9f8)[7] = 0;
    ((int*)*(void**)0x164e9f8)[8] = 0;
    ((int*)*(void**)0x164e9f8)[9] = 0;
    ((int*)*(void**)0x164e9f8)[10] = 0;
    ((int*)*(void**)0x164e9f8)[11] = 0;
    ((int*)*(void**)0x164e9f8)[12] = 0;
    ((int*)*(void**)0x164e9f8)[13] = 0;
    ((int*)*(void**)0x164e9f8)[14] = 0;
    ((int*)*(void**)0x164e9f8)[15] = 0;
    *(void**)0x164e9fc = (char*)*(void**)0x164e9f8 + 0x40;
    atexit(&FUN_013c08c0);
}

// @ 0x012fdfe0
void init_1547690()
{
    ((SetMode*)g_1547690)->SetMode2(2);
}

// @ 0x012fe000
void init_15477a4()
{
    *(int*)0x15477a4 = 1;
    *(int*)0x15477a8 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x15477ac;
    e[0].f0 = (void*)0x14150a8; e[0].f1 = 2; e[0].f2 = 0x13; e[0].f4 = 0x10; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = 0; e[1].f1 = 3; e[1].f2 = 9; e[1].f4 = 0x14; e[1].f5 = 1; e[1].f6 = 0;
    e[2].f0 = 0; e[2].f1 = 4; e[2].f2 = 9; e[2].f4 = 0x18; e[2].f5 = 1; e[2].f6 = 0;
    e[3].f0 = 0; e[3].f1 = 5; e[3].f2 = 9; e[3].f4 = 0x1c; e[3].f5 = 1; e[3].f6 = 0;
    e[4].f0 = 0; e[4].f1 = 6; e[4].f2 = 0x11; e[4].f4 = 0x38; e[4].f5 = 1; e[4].f6 = 0;
    e[5].f0 = 0; e[5].f1 = 7; e[5].f2 = 0x11; e[5].f4 = 0x40; e[5].f5 = 1; e[5].f6 = 0;
    e[6].f0 = 0; e[6].f1 = 8; e[6].f2 = 9; e[6].f4 = 0x20; e[6].f5 = 1; e[6].f6 = 0;
    e[7].f0 = 0; e[7].f1 = 9; e[7].f2 = 9; e[7].f4 = 0x24; e[7].f5 = 1; e[7].f6 = 0;
    e[8].f0 = (void*)0x141a7fc; e[8].f1 = 0xa; e[8].f2 = 0x14; e[8].f4 = 0x48; e[8].f5 = 1; e[8].f6 = 0;
    e[9].f0 = (void*)0x141a7fc; e[9].f1 = 0xb; e[9].f2 = 0x14; e[9].f4 = 0x70; e[9].f5 = 1; e[9].f6 = 0;
    e[10].f0 = 0; e[10].f1 = 0xc; e[10].f2 = 0x11; e[10].f4 = 0x28; e[10].f5 = 1; e[10].f6 = 0;
    e[11].f0 = 0; e[11].f1 = 0xd; e[11].f2 = 0x11; e[11].f4 = 0x30; e[11].f5 = 1;
}

// @ 0x012fe300
void init_15476e4()
{
    *(int*)0x15476e4 = 1;
    *(int*)0x15476e8 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x15476ec;
    e[0].f0 = (void*)0x141a690; e[0].f1 = 0x54010a1; e[0].f2 = 0x13; e[0].f4 = 0x114 + 4; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = (void*)0x141a690; e[1].f1 = 0x54010a2; e[1].f2 = 0x13; e[1].f4 = 0x114 + 8; e[1].f5 = 1; e[1].f6 = 0;
    e[2].f0 = (void*)0x141a690; e[2].f1 = 0x54010a3; e[2].f2 = 0x13; e[2].f4 = 0x114 + 0xc; e[2].f5 = 1; e[2].f6 = 0;
    e[3].f0 = (void*)0x141a690; e[3].f1 = 0x54010a4; e[3].f2 = 0x13; e[3].f4 = 0x114 + 0x10; e[3].f5 = 1; e[3].f6 = 0;
    e[4].f0 = (void*)0x141a690; e[4].f1 = 0x54010a5; e[4].f2 = 0x13; e[4].f4 = 0x114 + 0x14; e[4].f5 = 1; e[4].f6 = 0;
    e[5].f0 = (void*)0x141a690; e[5].f1 = 0x54010a6; e[5].f2 = 0x13; e[5].f4 = 0x114 + 0x18; e[5].f5 = 1; e[5].f6 = 0;
    e[6].f0 = (void*)0x141a690; e[6].f1 = 0x54010a7; e[6].f2 = 0x13; e[6].f4 = 0x114 + 0x1c; e[6].f5 = 1;
}

// @ 0x012fede0
void init_164f018()
{
    void* a = GetDefaultAllocator2(0x20, 0x14);
    ((BufC*)g_164f018)->init(a);
    atexit(&FUN_013c0930);
}

// @ 0x012fee10
void init_164f03c()
{
    void* a = GetDefaultAllocator2(0x80, 0x14);
    ((BufC*)g_164f03c)->init(a);
    atexit(&FUN_013c0940);
}

// @ 0x012ffaf0
void init_1548764()
{
    *(int*)0x1548764 = 1;
    *(int*)0x1548768 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x154876c;
    e[0].f0 = 0; e[0].f1 = 0xeec1d001; e[0].f2 = 9; e[0].f4 = 0x10; e[0].f5 = 1;
}

// @ 0x012ffef0
void init_16514ec()
{
    *(void**)g_16514ec = GetDefaultAllocator0();
}

// Hash table storage at 0x016519ac (static-initialised below, destroyed by FUN_013c0c00).
struct InitHashTableStorage {
    void* p00;          // +0x00
    int   n04;          // +0x04
    int   n08;          // +0x08
    float f0c;          // +0x0c
    float f10;          // +0x10
    int   n14;          // +0x14
    void* allocator;    // +0x18
    int   n1c;          // +0x1c
};
extern InitHashTableStorage g_16519ac;
extern "C" char g_154df28[];

// @ 0x012fff30
void init_16519ac()
{
    void* a = GetDefaultAllocator0();
    g_16519ac.allocator = a;
    g_16519ac.f0c = 1.0f;
    g_16519ac.f10 = 2.0f;
    g_16519ac.n1c = 0;
    g_16519ac.n04 = 1;
    g_16519ac.p00 = g_154df28;
    g_16519ac.n08 = 0;
    g_16519ac.n14 = 0;
    atexit(&FUN_013c0c00);
}

// @ 0x012fff90
void init_1651994()
{
    void* a = GetDefaultAllocator0();
    g_1651994.begin = 0;
    g_1651994.end = 0;
    g_1651994.capacity = 0;
    g_1651994.allocator = a;
    g_1651994.state = 0;
    atexit(&FUN_013c0ba0);
}

// @ 0x012fffc0
void init_16679d0()
{
    InitializeCriticalSection((void*)g_16679d0);
    atexit(&FUN_013c0c50);
}

// The global at 0x01549834 that init_1549834 constructs (layout from the stores; 0x388 bytes).
struct TextHolderPart { void Ctor(); };                 // ctor 0x0089a570
struct TextHolder_1549834 {
    char           pad00[0x0c];
    int            m0c;                                   // +0x0c
    int            m10;                                   // +0x10
    int            m14;                                   // +0x14
    char           pad18[0x08];
    TextHolderPart mPart;                                 // +0x20
    char           pad21[0xdf];
    bool           mb100;                                 // +0x100
    char           pad101[3];
    TextStyle      mStyle;                                // +0x104
    char           pad105[0x277];
    bool           mb37c;                                 // +0x37c
    bool           mb37d;                                 // +0x37d
    char           pad37e[2];
    float          mf380;                                 // +0x380
    bool           mb384;                                 // +0x384
    bool           mb385;                                 // +0x385
    bool           mb386;                                 // +0x386
};
extern TextHolder_1549834 g_1549834;                      // 0x01549834

// @ 0x01300010
void init_1549834()
{
    TextHolder_1549834& h = g_1549834;
    h.mPart.Ctor();
    h.mb100 = true;
    h.mStyle.ctor();
    h.mb37c = false;
    h.mb37d = true;
    h.mf380 = 1.0f;
    h.mb384 = false;
    h.mb385 = false;
    h.mb386 = false;
    h.m0c = 0;
    h.m10 = 0;
    h.m14 = 0;
    atexit(&FUN_013c0cc0);
}

// @ 0x01300080
void init_1667a58()
{
    *(char*)g_1667a58 = (char)InitXInputFunctions();
}

// @ 0x013000d0
void init_1667c00()
{
    InitializeCriticalSection((void*)g_1667c00);
    atexit(&FUN_013c0d40);
}

// @ 0x013000f0
void init_154df38()
{
    if (*(int*)g_154df38 == -1)
        *(int*)g_154df38 = TlsAlloc();
}

// @ 0x01300110
long take_16688a0()
{
    return _InterlockedExchange((volatile long*)g_16688a0, 0);
}

// @ 0x01300230
long take_1668ef8()
{
    return _InterlockedExchange((volatile long*)g_1668ef8, 0);
}

// @ 0x01300240
long take_1668efc()
{
    return _InterlockedExchange((volatile long*)g_1668efc, 0);
}
