// Havok 3.1.0 reflection registration for Spore's creature/tool property set, plus a block of
// Havok class/typeinfo dynamic initializers and singleton/atexit glue (0x013AC650..0x013BED00).
// Reconstructed from the retail binary. Relocations are masked by the matcher, so external
// reflection tables and callees are declared as externs with the right shape.
#include <intrin.h>

// ------------------------------------------------------------------ CRT / Win32 imports
extern "C" __declspec(dllimport) unsigned long __stdcall TlsAlloc();
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void*);
extern "C" int __cdecl atexit(void (__cdecl*)());

// ================================================================== 0x013AC650
// Sixteen 60-byte property descriptors { name, hash, offset, <3 unused>, 0, 0, f[7] } copied into the
// global table at 0x015B8850 (stride 0x3C). f[0] is shared (0x00692CA0) and hoisted into edx.
typedef void (__cdecl *fp)();
struct PropDesc {
    const char* name;
    unsigned    hash;
    int         off;
    int         p3, p4, p5;
    int         z0, z1;
    fp          f[7];
    PropDesc(const char* n, unsigned h, int o, fp f0, fp a, fp b, fp c, fp d, fp e, fp ff)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = a; f[2] = b; f[3] = c; f[4] = d; f[5] = e; f[6] = ff; off = o;
    }
};
extern PropDesc g_015b8850, g_015b888c, g_015b88c8, g_015b8904, g_015b8940, g_015b897c,
                g_015b89b8, g_015b89f4, g_015b8a30, g_015b8a6c, g_015b8aa8, g_015b8ae4,
                g_015b8b20, g_015b8b5c, g_015b8b98, g_015b8bd4;

// @ 0x013AC650
void FUN_013ac650() {
    g_015b8850 = PropDesc("mCurrentAmmoCount", 0x0385030du, 124, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00572840, (fp)0x00692ff0, (fp)0x00694ee0, (fp)0x00b1fbf0, (fp)0x0057cde0);
    g_015b888c = PropDesc("mRechargeTimer", 0x0385031du, 136, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b88c8 = PropDesc("mAutoFireTimer", 0x03850360u, 168, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b8904 = PropDesc("mChargeTimer", 0x03850362u, 200, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b8940 = PropDesc("mMissCheckTimer", 0x03850364u, 232, (fp)0x00692ca0,
        (fp)0x00ae3470, (fp)0x00ae3490, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00ae3310, (fp)0x00ac8050);
    g_015b897c = PropDesc("mpToolOwner", 0x03850690u, 276, (fp)0x00692ca0,
        (fp)0x00bdc650, (fp)0x00bdd350, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b89b8 = PropDesc("mpToolTarget", 0x038506b6u, 280, (fp)0x00692ca0,
        (fp)0x00bdc650, (fp)0x00bdd350, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b89f4 = PropDesc("mTargetDamagePointId", 0x063fc849u, 284, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00572840, (fp)0x00692ff0, (fp)0x00694ee0, (fp)0x00b1fbf0, (fp)0x0057cde0);
    g_015b8a30 = PropDesc("mpArea", 0x03850926u, 288, (fp)0x00692ca0,
        (fp)0x0104e750, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b8a6c = PropDesc("mpBeam", 0x03850927u, 292, (fp)0x00692ca0,
        (fp)0x0104e780, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00b6f550, (fp)0x00ac8050);
    g_015b8aa8 = PropDesc("mpAppTarget", 0x03850929u, 300, (fp)0x00692ca0,
        (fp)0x00bca770, (fp)0x00bca960, (fp)0x00c2e4e0, (fp)0x00692fb0, (fp)0x00bca7e0, (fp)0x00ac8050);
    g_015b8ae4 = PropDesc("mInterruptedByDamage", 0x03850952u, 316, (fp)0x00692ca0,
        (fp)0x00ac8750, (fp)0x00ac8780, (fp)0x00693090, (fp)0x00694fa0, (fp)0x00b1fbf0, (fp)0x0057ce00);
    g_015b8b20 = PropDesc("mDamageMultiplier", 0x038509c7u, 324, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8b5c = PropDesc("mRangeMultiplier", 0x038509d5u, 328, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8b98 = PropDesc("mProjectileScale", 0x039fb1a8u, 332, (fp)0x00692ca0,
        (fp)0x00572810, (fp)0x00ac88f0, (fp)0x006930b0, (fp)0x00694fc0, (fp)0x00b1fbf0, (fp)0x00acbb80);
    g_015b8bd4 = PropDesc("mIsInUse", 0x057f830fu, 128, (fp)0x00692ca0,
        (fp)0x00ac8750, (fp)0x00ac8780, (fp)0x00693090, (fp)0x00694fa0, (fp)0x00b1fbf0, (fp)0x0057ce00);
}

// ================================================================== singleton / atexit glue
struct TlsData {
    unsigned long idx;
    TlsData() { idx = TlsAlloc(); }
    ~TlsData() {}
};
TlsData g_016e4174;

struct TlsArray {
    unsigned long idx[5];
    TlsArray() { unsigned long* p = idx; unsigned n = 5; do { *p++ = TlsAlloc(); } while (n--); }
    ~TlsArray() {}
};
TlsArray g_016e42a0;

struct TlsData2 {
    unsigned long idx;
    TlsData2() { idx = TlsAlloc(); }
    ~TlsData2() {}
};
TlsData2 g_016e42b8;

// @ 0x013B34F0
void FUN_013b34f0() { (void)&g_016e4174; }
// @ 0x013B3650
void FUN_013b3650() { (void)&g_016e42a0; }
// @ 0x013B3680
void FUN_013b3680() { (void)&g_016e42b8; }

// ---- intrusive list registration: node.next = head; head = &node
struct ListNode; struct ListNode2; struct ListNode3;
extern ListNode*  g_head;             // 0x016E429C
extern ListNode2* g_head2;            // 0x016E429C
extern ListNode3* g_head3;            // 0x016E429C
struct ListNode  { int id; ListNode*  next; ListNode()  { next = g_head;  g_head = this;  } };
struct ListNode2 { int id; ListNode2* next; ListNode2() { next = g_head2; g_head2 = this; } };
struct ListNode3 { int id; ListNode3* next; ListNode3() { next = g_head3; g_head3 = this; } };
ListNode  g_015b9a3c;
ListNode2 g_015ba420;
ListNode3 g_015d0b80;

// @ 0x013B3510
void FUN_013b3510() { (void)&g_015b9a3c; }
// @ 0x013B5C00
void FUN_013b5c00() { (void)&g_015ba420; }
// @ 0x013BC940
void FUN_013bc940() { (void)&g_015d0b80; }

// ---- Havok hkClass dynamic initializers
struct hkClassMember; struct hkClassEnum;
class hkClass {
public:
    hkClass(const char* name, const hkClass* parent, int objectSize,
            const hkClass** implementedInterfaces, int numImplementedInterfaces,
            const hkClassEnum* declaredEnums, int numDeclaredEnums,
            const hkClassMember* declaredMembers, int numDeclaredMembers,
            const void* defaults);
    void* m_data[10];
};
extern hkClass g_016e4930, g_016e4b28, g_016e4278, g_016e49c0;
extern const hkClassMember g_0149f0b8[], g_015b9c38[],
                          g_014a1120[], g_014a55e0[];
extern const hkClassEnum g_0149fd00[], g_014a0004[], g_014a0240[];
extern char g_0149f130[], g_014a0270[], g_014a1288[], g_014a5694[];

// @ 0x013B3CA0
hkClass g_016e4810("hkLimitedHingeConstraintData", &g_016e4930, 0x90,
    (const hkClass**)0, 0, (const hkClassEnum*)0, 0, g_0149f0b8, 6, (const void*)g_0149f130);
// @ 0x013B3FD0
hkClass g_016e4a74("hkRigidBodyDeactivator", &g_016e4b28, 8,
    (const hkClass**)0, 0, g_0149fd00, 1, (const hkClassMember*)0, 0, (const void*)0);
// @ 0x013B40F0
hkClass g_016e4b4c("hkConstraintMotor", &g_016e4278, 8,
    (const hkClass**)0, 0, g_014a0004, 1, (const hkClassMember*)0, 0, (const void*)0);
// @ 0x013B41E0
hkClass g_016e4c00("hkWorldCinfo", &g_016e4278, 0xa0,
    (const hkClass**)0, 0, g_014a0240, 4, g_015b9c38, 0x1b, (const void*)g_014a0270);
// @ 0x013B4640
hkClass g_016e4f3c("hkEntity", &g_016e49c0, 0xd0,
    (const hkClass**)0, 0, (const hkClassEnum*)0, 0, g_014a1120, 0x12, (const void*)g_014a1288);
// @ 0x013B5440
hkClass g_016e59b0("hkRagdollConstraintData", &g_016e4930, 0x90,
    (const hkClass**)0, 0, (const hkClassEnum*)0, 0, g_014a55e0, 9, (const void*)g_014a5694);

// ---- concrete class registration: construct a default instance, register {name, finishFn, vtable}
struct TypeInfo { const char* name; void (*finish)(void*); const void* vtbl; };

struct __declspec(align(16)) hkShapeCollection { unsigned pad[0x20/4]; hkShapeCollection(); };
extern TypeInfo g_016e58b0, g_016e58ec, g_016e5c70, g_016e58e0;

// @ 0x013B51D0
void FUN_013b51d0() {
    hkShapeCollection shape;
    g_016e58b0.name   = "hkTriSampledHeightFieldCollection";
    g_016e58b0.finish = (void (*)(void*))0x010c4a20;
    g_016e58b0.vtbl   = (const void*)0x014a3c54;
    (void)shape;
}
// @ 0x013B5300
void FUN_013b5300() {
    hkShapeCollection shape;
    g_016e58ec.name   = "hkConvexPieceMeshShape";
    g_016e58ec.finish = (void (*)(void*))0x010cb210;
    g_016e58ec.vtbl   = (const void*)0x014a416c;
    (void)shape;
}
// @ 0x013B55D0
struct __declspec(align(16)) hkUnaryAction { unsigned pad[0x48/4]; hkUnaryAction(void*, unsigned); };
void FUN_013b55d0() {
    hkUnaryAction action((void*)0, 0);
    g_016e5c70.name   = "hkMouseSpringAction";
    g_016e5c70.finish = (void (*)(void*))0x01127830;
    g_016e5c70.vtbl   = (const void*)0x014a6254;
    (void)action;
}
// @ 0x013B52D0
extern float FUN_010c9050();
extern float g_015ba2d8;
void FUN_013b52d0() {
    float probe = FUN_010c9050();
    g_016e58e0.name   = "hkCylinderShape";
    g_016e58e0.finish = (void (*)(void*))0x010c98e0;
    g_015ba2d8 = 1.0f - probe;
    g_016e58e0.vtbl   = (const void*)0x014a40c4;
}

// ---- simple global stores / getters
extern int g_014a7638;
extern unsigned char g_015ba42d;
// @ 0x013B5C20
void FUN_013b5c20() { g_015ba42d = (unsigned char)(g_014a7638 == 1); }

extern int FUN_01156530();
extern int g_016f16f0;
// @ 0x013B5D80
void FUN_013b5d80() { g_016f16f0 = FUN_01156530(); }

extern unsigned char FUN_01170140();
extern unsigned int g_016f1734, g_016f1840;
// @ 0x013B5D90
void FUN_013b5d90() { g_016f1734 = FUN_01170140(); }
// @ 0x013B5DA0
void FUN_013b5da0() { g_016f1840 = FUN_01170140(); }

extern int g_016f2974, g_016f2978;
extern void FUN_011eaa50();
extern void FUN_011eaaa0();
// @ 0x013B5DB0
void FUN_013b5db0() {
    int n = g_016f2974;
    g_016f2974 = g_016f2974 + 1;
    if (n == 0) FUN_011eaa50();
    atexit((void (__cdecl*)())0x013cb300);
}
// @ 0x013B5DE0
void FUN_013b5de0() {
    int n = g_016f2978;
    g_016f2978 = g_016f2978 + 1;
    if (n == 0) FUN_011eaaa0();
    atexit((void (__cdecl*)())0x013cb320);
}

// @ 0x013B5EB0
extern unsigned __int64 g_015d0358, g_015d0360;
extern "C" void __cdecl GetFrequencies(unsigned __int64*, unsigned __int64*);
extern void FUN_011e80a0();
void FUN_013b5eb0() {
    GetFrequencies(&g_015d0358, &g_015d0360);
    FUN_011e80a0();
}

// @ 0x013B64C0
struct CriticalSection { unsigned char cs[0x18]; CriticalSection() { InitializeCriticalSection(cs); } ~CriticalSection() {} };
CriticalSection g_016f4e98;

extern unsigned long g_015d0690;
// @ 0x013B64E0
void FUN_013b64e0() { if (g_015d0690 == 0xfffffffful) g_015d0690 = TlsAlloc(); }

extern volatile long g_016f5b38;
// @ 0x013B6500
long FUN_013b6500() { return _InterlockedExchange(&g_016f5b38, 0); }

// ---- global destructors
struct RBTree { void DoNuke(void*); };
extern RBTree g_0151102c;
extern void *g_01511038;
// @ 0x013BD0D0
void FUN_013bd0d0() { g_0151102c.DoNuke(g_01511038); }

// ---- static vector-dtor style frees
extern "C" void __cdecl eastl_deallocate(void*);
extern char *g_0151d8b8, *g_0151d8c0, *g_0151d8c8;
// @ 0x013BD9D0
void FUN_013bd9d0() {
    if ((((int)(g_0151d8c0 - g_0151d8b8) & ~1) > 2) && g_0151d8b8 && g_0151d8b8 != g_0151d8c8)
        eastl_deallocate(g_0151d8b8);
}
extern char *g_015f3584, *g_015f358c;
// @ 0x013BDA60
void FUN_013bda60() {
    if ((int)(g_015f358c - g_015f3584) > 1 && g_015f3584)
        eastl_deallocate(g_015f3584);
}
extern char *g_015f496c, *g_015f4974;
// @ 0x013BDC30
void FUN_013bdc30() {
    if ((int)(g_015f4974 - g_015f496c) > 1 && g_015f496c)
        eastl_deallocate(g_015f496c);
}
extern char *g_01523ad4, *g_01523adc, *g_01523ae4;
// @ 0x013BE2F0
void FUN_013be2f0() {
    if ((((int)(g_01523adc - g_01523ad4) & ~1) > 2) && g_01523ad4 && g_01523ad4 != g_01523ae4)
        eastl_deallocate(g_01523ad4);
}

// @ 0x013BED00
struct Variant { void Destruct(int); };
extern Variant g_016027d0;
extern unsigned char g_016027e0;
void FUN_013bed00() { if (g_016027e0 & 4) g_016027d0.Destruct(0); }
