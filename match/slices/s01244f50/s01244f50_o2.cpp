// Slice s01244f50 (/O2 part) -- FNV-1 string-hash table initializers and a
// float sign-flip global setter, plus a cWString global initializer.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
typedef unsigned int uint32_t;

extern "C" uint32_t __cdecl FNV1_String8(const char* s, uint32_t hash, unsigned int mode);  // 0x932e80

struct cWString { void RangeInitialize(const wchar_t* s); };   // 0x579a90

extern "C" int atexit(void (__cdecl*)());
extern void FUN_013bd740(void);   // 0x13bd740

// @ 0x0127caa0
void init_15e6c58()
{
    *(float*)0x15e6c58 = -*(float*)0x150f2c4;
}

// @ 0x012817b0
void init_15e8840()
{
    uint32_t hBall = FNV1_String8("Ball", 0x811c9dc5, 1);
    uint32_t hEye  = FNV1_String8("Eye", 0x811c9dc5, 1);
    uint32_t hCell = FNV1_String8("Cell", 0x811c9dc5, 1);
    *(uint32_t*)0x15e8840 = hEye;
    *(uint32_t*)0x15e8848 = hBall;
    *(uint32_t*)0x15e8844 = hCell;
}

// @ 0x01281800
void init_15e89f8()
{
    uint32_t hStalk = FNV1_String8("Stalk", 0x811c9dc5, 1);
    uint32_t hEye   = FNV1_String8("Eye", 0x811c9dc5, 1);
    uint32_t hCell  = FNV1_String8("Cell", 0x811c9dc5, 1);
    *(uint32_t*)0x15e89f8 = hEye;
    *(uint32_t*)0x15e8a00 = hStalk;
    *(uint32_t*)0x15e89fc = hCell;
}

// @ 0x012967b0
void init_15f0a1c()
{
    ((cWString*)0x15f0a1c)->RangeInitialize(*(const wchar_t**)0x151ac94);
    atexit(&FUN_013bd740);
}

// --- serializable-field descriptor table -----------------------------------
// 15-dword record: [0] name, [1] hash, [2] editorId, [3..5] unused,
// [6] storeFn3, [7] storeFn4, [8] storeFn5, [9] fn, [A] fn, [B] fn,
// [C] fn, [D] fn, [E] fn.
struct FieldDesc {
    const char* name;     // +0x00
    uint32_t    hash;     // +0x04
    uint32_t    editorId; // +0x08
    uint32_t    pad0c;    // +0x0c
    uint32_t    pad10;    // +0x10
    uint32_t    pad14;    // +0x14
    uint32_t    zero0;    // +0x18
    uint32_t    zero1;    // +0x1c
    uint32_t    offset;   // +0x20
    void*       f24;      // +0x24
    void*       f28;      // +0x28
    void*       f2c;      // +0x2c
    void*       f30;      // +0x30
    void*       f34;      // +0x34
    void*       f38;      // +0x38
};

extern char FUN_00692ca0;   // 0x692ca0 (Simulator::Attribute::DefaultOffset)
extern char FUN_00572810;   // 0x572810
extern char FUN_00572840;   // 0x572840
extern char FUN_00692ff0;   // 0x692ff0
extern char FUN_00694ee0;   // 0x694ee0
extern char FUN_0057cde0;   // 0x57cde0
extern char FUN_00584230;   // 0x584230
extern char FUN_005767f0;   // 0x5767f0
extern char FUN_00c2e4e0;   // 0xc2e4e0
extern char FUN_00692fb0;   // 0x692fb0
extern char FUN_00b1fbf0;   // 0xb1fbf0
extern char FUN_0057efa0;   // 0x57efa0
extern char FUN_00576880;   // 0x576880
extern char FUN_00572880;   // 0x572880
extern char FUN_00576f60;   // 0x576f60

// @ 0x01277f40
void init_150d100()
{
    FieldDesc r;
    r.name     = "mNumEditorEntries";
    r.hash     = 0x5344d71;
    r.editorId = 0x4ec;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00572810;
    r.f28      = &FUN_00572840;
    r.f2c      = &FUN_00692ff0;
    r.f30      = &FUN_00694ee0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057cde0;
    *(FieldDesc*)0x150d100 = r;

    r.name     = "mActionStatus";
    r.hash     = 0x5344d70;
    r.editorId = 0x4d8;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d13c = r;

    r.name     = "mNumEditorEntriesByEditor";
    r.hash     = 0x63bdb1a;
    r.editorId = 0x4f0;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00576880;
    r.f28      = &FUN_00572880;
    r.f2c      = &FUN_00692ff0;
    r.f30      = &FUN_00694ee0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057cde0;
    *(FieldDesc*)0x150d178 = r;

    r.name     = "mActionStatusByEditor [kEditorTypeCell]";
    r.hash     = 0x63bdb1b;
    r.editorId = 0x508;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d1b4 = r;

    r.name     = "mActionStatusByEditor [kEditorTypeCreature]";
    r.hash     = 0x63bdb1c;
    r.editorId = 0x51c;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d1f0 = r;

    r.name     = "mActionStatusByEditor [kEditorTypeBuilding]";
    r.hash     = 0x63bdb1d;
    r.editorId = 0x530;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d22c = r;

    r.name     = "mActionStatusByEditor [kEditorTypeVehicle]";
    r.hash     = 0x63bdb1e;
    r.editorId = 0x544;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d268 = r;

    r.name     = "mActionStatusByEditor [kEditorTypeAccessories]";
    r.hash     = 0x63bdb1f;
    r.editorId = 0x558;
    r.zero0    = 0;
    r.zero1    = 0;
    r.offset   = 0x692ca0;
    r.f24      = &FUN_00584230;
    r.f28      = &FUN_005767f0;
    r.f2c      = &FUN_00c2e4e0;
    r.f30      = &FUN_00692fb0;
    r.f34      = &FUN_00b1fbf0;
    r.f38      = &FUN_0057efa0;
    *(FieldDesc*)0x150d2a4 = r;
}
