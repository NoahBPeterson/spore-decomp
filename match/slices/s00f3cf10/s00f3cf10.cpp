// Slice s00f3cf10: an editor-side "catalog / thumbnail" helper class.
// Optimized module: /O2 /MD /Gy /EHsc /TP.
//
// Recovered `this` offsets (used directly to avoid anonymous-field layout drift):
//   +0x10  Inner*  (Inner+0x68 = mode: 0/2)
//   +0x18  int f18, +0x1c char f1c
//   +0x30  void* f30, +0x38 ImageRes
//   +0x8c  int f8c
//   +0xb4  int** fB4, +0xb8 int fB8
//   +0xe8 int fE8, +0xf0 int fF0
//   +0x124 char f124
typedef unsigned int uint32_t;

struct IObj20 {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0C();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1C();
    virtual void* v20(int, int, int);
};
struct cImgRes { void GetImageResource(void* p); };
struct cLayoutCollection { void Show(); };

struct cSec3 {
    virtual void v00();
    int   FUN_00ebebc0();
    void  FUN_00f3d210();
    void  FUN_00f3d7e0(int a);
    void* FUN_00f3d780(int p);
    void* FUN_00f3d880();
    void  FUN_00f3d8a0();
    void  FUN_00f3d8c0(char p);
};

#define F(off) (*(int*)((char*)this + (off)))

// Externals (defined elsewhere in the binary).
int* FUN_0067dd60();
void* FUN_0067cab0();

// Skeleton targets defined below; noinline + opaque call so callers keep the calls
// and must save `this` across them.
extern int g_dummy_s00f3cf10;
extern void g_opaque_sink(int);
__declspec(noinline) void __stdcall FUN_00f3cf10(int);
__declspec(noinline) void FUN_00f3d260();
__declspec(noinline) void FUN_00f3d3e0();
__declspec(noinline) void FUN_00f3d5d0();
__declspec(noinline) void FUN_00f3d900();
__declspec(noinline) void FUN_00f3da90();
__declspec(noinline) void FUN_00f3dc70();
__declspec(noinline) void FUN_00f3dce0();

// ---------------------------------------------------------------------------
// @ 0x00f3d210
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d210() {
    int t = *(int*)(*(int*)((char*)this + 0x10) + 0x68);
    switch (t) {
    case 0:
        ((cImgRes*)((char*)this + 0x38))->GetImageResource(*(void**)((char*)this + 0x30));
        break;
    case 2: {
        IObj20* o = (IObj20*)FUN_0067dd60();
        void* r = o->v20(F(0xe8), F(0xf0), 0);
        ((cImgRes*)((char*)this + 0x38))->GetImageResource(r);
        break;
    }
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d780  (skeleton: EASTL hashtable find)
// ---------------------------------------------------------------------------
__declspec(noinline) void* cSec3::FUN_00f3d780(int p) {
    g_dummy_s00f3cf10 += p;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3d7e0  (skeleton: hashtable iteration)
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d7e0(int a) {
    g_dummy_s00f3cf10 += a;
}

// ---------------------------------------------------------------------------
// @ 0x00f3d880
// ---------------------------------------------------------------------------
void* cSec3::FUN_00f3d880() {
    int iVar1 = FUN_00ebebc0();
    if (iVar1 != 0) {
        return FUN_00f3d780(iVar1);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3d8a0
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d8a0() {
    if (*(char*)((char*)this + 0x124) != 0) {
        FUN_00f3cf10(0);
        *(char*)((char*)this + 0x124) = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d8c0
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d8c0(char p) {
    if (*(int*)((char*)this + 0x18) == 0) {
        FUN_00f3cf10(0);
        *(int*)((char*)this + 0x18) = 1;
        *(char*)((char*)this + 0x1c) = (p == 0);
        cLayoutCollection* c = (cLayoutCollection*)FUN_0067cab0();
        c->Show();
    }
}

// ---------------------------------------------------------------------------
// Skeleton definitions (listed in partial.txt).
// ---------------------------------------------------------------------------
int g_dummy_s00f3cf10 = 0;

__declspec(noinline) void __stdcall FUN_00f3cf10(int x) { g_opaque_sink(x); }
__declspec(noinline) void FUN_00f3d260() { g_dummy_s00f3cf10 += 1; }
__declspec(noinline) void FUN_00f3d3e0() { g_dummy_s00f3cf10 += 2; }
__declspec(noinline) void FUN_00f3d5d0() { g_dummy_s00f3cf10 += 3; }
__declspec(noinline) void FUN_00f3d900() { g_dummy_s00f3cf10 += 4; }
__declspec(noinline) void FUN_00f3da90() { g_dummy_s00f3cf10 += 5; }
__declspec(noinline) void FUN_00f3dc70() { g_dummy_s00f3cf10 += 6; }
__declspec(noinline) void FUN_00f3dce0() { g_dummy_s00f3cf10 += 7; }
