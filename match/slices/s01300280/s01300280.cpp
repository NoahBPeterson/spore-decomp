// Slice s01300280, /O2 part -- library/Windows init, float-derived globals and
// zero-fill routines.  /O2 /arch:SSE.
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

extern "C" int atexit(void (__cdecl*)());
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
extern "C" __declspec(dllimport) int __stdcall WSAStartup(uint16_t ver, void* data);
extern void* __cdecl GetDefaultAllocator0();
extern void InitOSGlobalSystem();
extern int FUN_00957a60(void* a, void* b);
extern int FUN_00957880(void* a, void* b);
extern void FUN_009577b0(void);
extern void FUN_009577f0(void);
extern void FUN_005ed340(void);
extern void FUN_00957790(void);
extern void FUN_013c0f40(void);
extern void FUN_013c0f50(void);
extern void FUN_013c0fc0(void);
extern void FUN_013c1150(void);

// @ 0x01300280
void init_1668f1c()
{
    void* h = LoadLibraryA("kernel32.dll");
    *(void**)0x1668f1c = h;
    if (h != 0) {
        *(void**)0x1668f20 = GetProcAddress(h, "ReadDirectoryChangesW");
        atexit(&FUN_013c0f40);
    } else {
        *(void**)0x1668f20 = 0;
        atexit(&FUN_013c0f40);
    }
}

// @ 0x013002d0
void init_1668f50()
{
    InitOSGlobalSystem();
    atexit(&FUN_013c0f50);
}

// @ 0x01300330
void init_166aa7c()
{
    uint32_t wsaData[100];
    int r = WSAStartup(2, wsaData);
    *(char*)0x166aa7c = (char)(r == 0);
    atexit(&FUN_013c0fc0);
}

// @ 0x01300370
void init_166aab4()
{
    *(void**)0x166aab4 = GetDefaultAllocator0();
}

// @ 0x01300760
void init_166b194()
{
    void* a = GetDefaultAllocator0();
    *(void**)0x166b1ac = a;
    *(float*)0x166b1a0 = 1.0f;
    *(float*)0x166b1a4 = 2.0f;
    *(int*)0x166b1b0 = 0;
    *(int*)0x166b198 = 1;
    *(void**)0x166b194 = (void*)0x154df28;
    *(int*)0x166b19c = 0;
    *(int*)0x166b1a8 = 0;
    atexit(&FUN_013c1150);
}

// @ 0x01301b20
extern float g_1550b8c;
void init_166c090()
{
    *(float*)0x166c090 = 1.0f / g_1550b8c;
}

// @ 0x01301b40
void init_166c098()
{
    *(float*)0x166c098 = (g_1550b8c - 1.0f) / g_1550b8c;
}

// @ 0x01302200
void init_166c350()
{
    *(float*)0x166c350 = 0.0f;
    *(float*)0x166c354 = 0.0f;
    *(float*)0x166c358 = 1.0f;
    *(float*)0x166c35c = 0.0f;
}

// @ 0x01302e90
extern float g_155145c;
void init_166c78c()
{
    *(float*)0x166c78c = 1.0f / g_155145c;
}

// @ 0x01302ef0
extern float g_155160c;
void init_166c938()
{
    *(float*)0x166c938 = 1.0f / g_155160c;
}

// @ 0x01302f50
extern float g_155163c;
void init_166c990()
{
    *(float*)0x166c990 = 1.0f / g_155163c;
}

// @ 0x01302f70
extern float g_1550b90;
extern float g_166c964;
extern float g_1551644;
extern float g_1551640;
void init_166c97c()
{
    *(float*)0x166c97c = -((g_1550b90 - g_166c964) / (g_1551644 - g_1551640));
}

// @ 0x01302fb0
extern float g_1551648;
void init_166c980()
{
    *(float*)0x166c980 = g_1551648 * g_1551648;
}

// @ 0x01307ea0
void zero_1675eb8()
{
    uint32_t* p = (uint32_t*)0x1675eb8;
    for (int i = 0x3f; i >= 0; --i) {
        p[-2] = 0; p[-1] = 0; p[0] = 0; p[1] = 0;
        p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
        p += 8;
    }
}

// @ 0x01307ed0
void zero_1675a00()
{
    uint32_t* p = (uint32_t*)0x1675a00;
    for (int i = 0x1f; i >= 0; --i) {
        p[-2] = 0; p[-1] = 0; p[0] = 0; p[1] = 0;
        p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
        p[6] = 0;
        p += 9;
    }
}

// @ 0x01308d20
// PARTIAL: Ghidra folds this to four packed constants; the float->byte
// conversion pipeline is not reconstructed.
void init_1676bfc()
{
    *(int*)0x1676bfc = (int)0xffffff00;
    *(int*)0x1676c00 = (int)0xffff00ff;
    *(int*)0x1676c04 = (int)0xff0000ff;
    *(int*)0x1676c08 = (int)0xff000000;
}

// @ 0x0130fcc0
struct TwoInts { int a, b; void init(int x, int y) { a = x; b = y; } };
void init_1679034()
{
    ((TwoInts*)0x1679034)->init(0x2903000, 0);
}

// @ 0x0130fce0
void init_1678f3c()
{
    ((TwoInts*)0x1678f3c)->init(0xe0, 0);
}

// @ 0x013107d0
void init_1679394()
{
    ((TwoInts*)0x1679394)->init(0x803000, 0);
}

// @ 0x01310bc0
void init_1679564()
{
    ((TwoInts*)0x1679564)->init(0x803000, 0);
}

// @ 0x01310be0
void init_167946c()
{
    ((TwoInts*)0x167946c)->init(0xe0, 0);
}
