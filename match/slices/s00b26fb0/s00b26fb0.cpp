// Slice s00b26fb0 -- SP::Simulator saved-game / editor-command helpers.
//
// Object: Simulator (EA framework). Reconstructed from annotated disassembly
// and Ghidra decompiles (work/match/scratch_s00b26fb0_cards.txt).
// Compiled __thiscall / cdecl, MSVC 2008 /O2.
//
// Absolute data addresses are accessed through reinterpret_cast<T*>(0x...),
// matching the convention used elsewhere in this project.

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef int            int32_t;

template <class T> static inline T& At(uint32_t a) { return *reinterpret_cast<T*>(a); }
static inline uint32_t Addr(const void* p) { return (uint32_t)(int)p; }

// Absolute-address objects (declared as extern objects so taking their
// address yields the original immediate constants).
extern uint8_t  DAT_015689ac;
extern uint32_t DAT_015689a8;
extern uint8_t  DAT_0167df50;
extern void*    DAT_0167df60;
extern void*    DAT_0167df64;
extern uint8_t  gDefaultSavedGameFilename;   // 0x0167df50, eastl::wstring
extern uint8_t  DAT_01654c00;
extern uint8_t  DAT_01654c01;
extern uint8_t  DAT_01654c02;
extern uint8_t  DAT_01654c04;
extern uint8_t  DAT_01654c05;
extern uint8_t  DAT_01654c08;
extern uint8_t  DAT_013ec460;

// --- external engine entry points ------------------------------------------
extern "C" {
void  WStr_AllocateSelf(void*, void*);                   // 0x00429760
void* EAAllocate(unsigned int, const char*, int, int, int, int); // 0x00f473a0
void  operator_delete(void*);                            // 0x00f47380
}

// 0x00423650 -- eastl wide-string assign (__thiscall: ecx = this, 2 stack
// args). Declared as a struct member so the call sequence matches exactly.
struct WStringFwd {
    void Assign(const void* first, const void* last);    // 0x00423650
};
#define WString_Assign(t, a, b) (((WStringFwd*)(t))->Assign((a), (b)))
extern void* __stdcall FUN_00b3d320(const void*);         // 0x00b3d320
extern void  __fastcall FUN_00b1e410(int x);             // 0x00b1e410
extern void* SP_StarManager();                           // 0x00b3d2a0
extern void  FUN_00bad940(void*);                        // 0x00bad940
extern void* SP_NounManager();                           // 0x00b3d300
extern void* GetCurrentTerrainSphere(void*);             // 0x00f67d90
extern void  FUN_00c75a20(void*);                        // 0x00c75a20
extern void  FUN_00c75580(void*);                        // 0x00c75580
extern void  FUN_00c75410(void*);                        // 0x00c75410
extern void* AchievementsController();                   // 0x00675250
extern void  AchievementsReset(void*);                   // 0x00675590
extern void* FUN_0057cba0(void*, const void*, const void*); // 0x0057cba0
extern void  DoNukeSubtree(void*);                       // 0x009a9600 (thiscall, DoNukeSubtree)
extern void* SP_GetSaveArea(uint32_t);                   // 0x006b1f90
extern void  RangeInitialize(void*, const wchar_t*);     // 0x00579a90
extern void  WString_Assign_CopyCtor(void*, const void*); // 0x0056e2d0
extern void  FUN_00692f60(int);                          // 0x00692f60 (thiscall-ish)
extern int   FUN_00ab30c0();                             // 0x00ab30c0
extern void  FUN_00692850();                             // 0x00692850
extern void* SP_GetDataDir();                            // 0x00b3d2e0-ish data dir
extern void  Stopwatch_SetUnits(void*, int);             // 0x00b1e410-style timer
extern void* SP_MessageServer();                         // 0x00b3d300-like server getter
extern void  FUN_013c2240();                             // 0x013c2240 atexit callback
extern void  FUN_013c2230();                             // 0x013c2230 atexit callback
extern "C" int atexit(void (*)(void));
extern void* FUN_00688f00(void* out, void* a, void* b);  // 0x00688f00 path normalize
extern void* FUN_00693cd0(void* a, void* b, void* c, void* d); // 0x00693cd0
extern void  FUN_00693900();                             // 0x00693900
extern void  FUN_00692ec0(uint32_t);                     // 0x00692ec0
extern void  FUN_00692ea0();                             // 0x00692ea0
extern void* FUN_00b3d230(void);                         // 0x00b3d230
extern void  FUN_00ba7dc0();                             // 0x00ba7dc0
extern void  FUN_00b5cd90(void*);                        // 0x00b5cd90
extern void  FUN_00b22960();                             // 0x00b22960
extern void* SP_NounManager2();                          // 0x00b3d300
extern void* FUN_00f48a80();                             // 0x00f48a80
extern void  FUN_00675250(void*);                        // 0x00675250
extern void  FUN_006768b0(void*, void*);                 // 0x006768b0
extern void  FUN_00e61510(void*);                        // 0x00e61510
extern void  FUN_00d414e0(int);                          // 0x00d414e0
extern void* PropertyManager();                          // 0x00b3d260
extern uint32_t g_dat_1568b08;                           // 0x01568b08
extern void  operator_delete__(void*);                   // 0xf47380
extern int   File_Exists(const void*);                   // 0x004e5b70-ish EA::IO::File::Exists
extern void* ZoneObject_New(unsigned size, const char* pool, int a, int b, int c, int d);
extern void* DatabasePackedFile_Ctor(void*, int, int);
extern void* cObjectDatabase_Ctor(void*, void*);
extern void* cVarListSerializer_Ctor(void*, void*, void*, int);
extern void  cVarListSerializer_Serialize(void*, void*);

static const uint32_t ADDR_df50 = 0x0167df50;
static const uint32_t ADDR_df60 = 0x0167df60;
static const uint32_t ADDR_df64 = 0x0167df64;
static const uint32_t ADDR_c00  = 0x01654c00;
static const uint32_t ADDR_c01  = 0x01654c01;
static const uint32_t ADDR_c02  = 0x01654c02;
static const uint32_t ADDR_c04  = 0x01654c04;
static const uint32_t ADDR_c05  = 0x01654c05;
static const uint32_t ADDR_c08  = 0x01654c08;
static const uint32_t ADDR_3ec460 = 0x013ec460;

// ===========================================================================
// @ 0x00b26fb0  copy-assign a cSavedGameHeader-like block
// ===========================================================================
void* SavedGameHeader_Assign(void* pself, void* src)
{
    void* pself_ = pself;    uint8_t* d = (uint8_t*)pself;
    uint8_t* s = (uint8_t*)src;

    if (s != d)
        WString_Assign(d, *(void**)s, *(void**)(s + 4));
    if (s + 0x10 != d + 0x10)
        WString_Assign(d + 0x10, *(void**)(s + 0x10), *(void**)(s + 0x14));
    if (s + 0x20 != d + 0x20)
        WString_Assign(d + 0x20, *(void**)(s + 0x20), *(void**)(s + 0x24));

    *(uint32_t*)(d + 0x30) = *(uint32_t*)(s + 0x30);
    *(uint32_t*)(d + 0x34) = *(uint32_t*)(s + 0x34);
    *(uint32_t*)(d + 0x38) = *(uint32_t*)(s + 0x38);
    *(uint32_t*)(d + 0x3c) = *(uint32_t*)(s + 0x3c);
    *(uint32_t*)(d + 0x40) = *(uint32_t*)(s + 0x40);
    *(uint32_t*)(d + 0x44) = *(uint32_t*)(s + 0x44);
    *(uint32_t*)(d + 0x48) = *(uint32_t*)(s + 0x48);
    *(uint32_t*)(d + 0x4c) = *(uint32_t*)(s + 0x4c);
    *(uint32_t*)(d + 0x50) = *(uint32_t*)(s + 0x50);
    *(uint32_t*)(d + 0x54) = *(uint32_t*)(s + 0x54);
    *(uint32_t*)(d + 0x58) = *(uint32_t*)(s + 0x58);
    *(uint32_t*)(d + 0x5c) = *(uint32_t*)(s + 0x5c);
    *(uint32_t*)(d + 0x60) = *(uint32_t*)(s + 0x60);
    *(uint32_t*)(d + 0x64) = *(uint32_t*)(s + 0x64);
    *(uint32_t*)(d + 0x68) = *(uint32_t*)(s + 0x68);
    *(uint32_t*)(d + 0x6c) = *(uint32_t*)(s + 0x6c);
    *(uint32_t*)(d + 0x70) = *(uint32_t*)(s + 0x70);
    *(uint32_t*)(d + 0x74) = *(uint32_t*)(s + 0x74);
    *(uint32_t*)(d + 0x78) = *(uint32_t*)(s + 0x78);
    *(uint32_t*)(d + 0x7c) = *(uint32_t*)(s + 0x7c);
    *(uint32_t*)(d + 0x80) = *(uint32_t*)(s + 0x80);
    *(uint32_t*)(d + 0x84) = *(uint32_t*)(s + 0x84);
    *(uint32_t*)(d + 0x88) = *(uint32_t*)(s + 0x88);
    *(uint32_t*)(d + 0x8c) = *(uint32_t*)(s + 0x8c);
    *(uint32_t*)(d + 0x90) = *(uint32_t*)(s + 0x90);
    *(uint32_t*)(d + 0x94) = *(uint32_t*)(s + 0x94);
    *(uint32_t*)(d + 0x98) = *(uint32_t*)(s + 0x98);
    *(uint32_t*)(d + 0x9c) = *(uint32_t*)(s + 0x9c);
    *(uint32_t*)(d + 0xa0) = *(uint32_t*)(s + 0xa0);
    *(uint32_t*)(d + 0xa4) = *(uint32_t*)(s + 0xa4);
    *(uint32_t*)(d + 0xa8) = *(uint32_t*)(s + 0xa8);
    d[0xac] = s[0xac];
    d[0xad] = s[0xad];
    *(uint32_t*)(d + 0xb0) = *(uint32_t*)(s + 0xb0);
    *(uint32_t*)(d + 0xb4) = *(uint32_t*)(s + 0xb4);
    *(uint32_t*)(d + 0xb8) = *(uint32_t*)(s + 0xb8);
    (void)pself_;
    return pself;
}

// ===========================================================================
// @ 0x00b27170  reset the default saved-game filename and notify
// ===========================================================================
bool ResetDefaultSavedGame()
{
    if ((void*)&DAT_0167df60 != (void*)&gDefaultSavedGameFilename) {
        ((WStringFwd*)&gDefaultSavedGameFilename)->Assign(DAT_0167df60, DAT_0167df64);
    }
    void* p = FUN_00b3d320(&DAT_01654c08);
    FUN_00b1e410((int)p);
    return true;
}

// ===========================================================================
// @ 0x00b271b0  scalar-deleting destructor for the saved-game object
// ===========================================================================
void* SavedGame_Dtor(void* self, uint8_t flags)
{
    uint8_t* s = (uint8_t*)self;
    *(void**)s = (void*)0x0145faa8;
    *(void**)(s + 4) = (void*)0x0145fa98;
    DoNukeSubtree((void*)*(uint32_t*)(s + 0x20));
    *(void**)(s + 4) = (void*)0x013ec458;
    *(void**)s = (void*)0x013eb938;
    if (flags & 1)
        operator_delete(s);
    return self;
}

// ===========================================================================
// @ 0x00b271f0  load the saved game named by the command string
// ===========================================================================
void LoadSavedGame(void* p)
{
    uint8_t* s = (uint8_t*)p;
    At<uint8_t>(0x015689ac) = 1;
    uint8_t* name = (uint8_t*)ADDR_c00;

    if (*(void**)s == *(void**)(s + 4)) {
        WString_Assign((void*)ADDR_3ec460, (void*)ADDR_3ec460, (void*)ADDR_3ec460);
    } else {
        uint32_t tmp[3];
        void* r = FUN_0057cba0(tmp, s, (void*)At<uint32_t>(0x015689a8));
        if (r != (void*)ADDR_df60) {
            WString_Assign((void*)ADDR_df60, r, *(void**)((uint8_t*)r + 4));
        }
        if (2 < (int)((tmp[2] - tmp[0]) & 0xfffffffeu) && tmp[0] != 0) {
            operator_delete((void*)tmp[0]);
        }
    }

    switch (*(uint32_t*)(s + 0xa4)) {
    case 0: name = (uint8_t*)ADDR_c00; break;
    case 1: name = (uint8_t*)ADDR_c01; break;
    case 2: name = (uint8_t*)ADDR_c02; break;
    case 3: name = (uint8_t*)ADDR_c00; break;
    case 4: name = (uint8_t*)ADDR_c04; break;
    case 5: name = (uint8_t*)ADDR_c05; break;
    default: name = (uint8_t*)ADDR_c00; break;
    }

    SP_StarManager();
    FUN_00bad940(p);
    void* nt = SP_NounManager();
    if (GetCurrentTerrainSphere(nt) != 0) {
        SP_NounManager();
        FUN_00c75a20(s + 0x58);
        SP_NounManager();
        FUN_00c75580(*(void**)(s + 0xb0));
        uint32_t k = *(uint32_t*)(s + 0xa0);
        if (k == 0) {
            SP_NounManager();
            FUN_00c75410(0);
        } else if (k == 1) {
            SP_NounManager();
            FUN_00c75410((void*)1);
        } else if (k == 2) {
            SP_NounManager();
            FUN_00c75410((void*)2);
        }
    }

    AchievementsReset(AchievementsController());
    FUN_00b1e410((int)FUN_00b3d320(name));
}

// ===========================================================================
// @ 0x00b27360  (large) simulator saved-game handler
// ===========================================================================
void SimSavedGameHandler2(void* p)
{
    uint8_t* self = (uint8_t*)p;
    static uint32_t s_flag094 = 0;

    if ((s_flag094 & 1) == 0) {
        s_flag094 |= 1;
        FUN_00692f60(0);
        *(void**)(0x0167e080) = (void*)0x0145f948;
        atexit(FUN_013c2240);
    }
    if (FUN_00ab30c0() == 0)
        FUN_00692850();

    if ((s_flag094 & 2) == 0) {
        s_flag094 |= 2;
        FUN_00692f60(0);
        *(void**)(0x0167e06c) = (void*)0x0145f958;
        atexit(FUN_013c2230);
    }
    if (FUN_00ab30c0() == 0)
        FUN_00692850();

    uint16_t* dir = (uint16_t*)SP_GetDataDir();
    uint16_t* end = dir;
    while (*end != 0)
        ++end;
    ((WStringFwd*)dir)->Assign(dir, end);

    int local_10[2];
    int local_8;
    void* r = FUN_0057cba0(local_10, self + 0x30, L"TestScripts\\");
    if (r != (void*)(self + 0x30))
        ((WStringFwd*)(*(void**)r))->Assign(*(void**)r, *(void**)((char*)r + 4));
    if (((local_8 - local_10[0]) & 0xfffffffeu) > 2 && local_10[0] != 0)
        operator_delete((void*)local_10[0]);

    Stopwatch_SetUnits((void*)0x0167df70, 4);
    Stopwatch_SetUnits((void*)0x0167df88, 4);

    int iVar1 = (int)self - 4;
    int* msgSrv = (int*)SP_MessageServer();
    *(int*)(self + 0x1c) = (int)msgSrv;
    *(int*)(self + 0x20) = iVar1;
    *(uint32_t*)(self + 0x24) = 0x0145f8e0;
    *(uint32_t*)(self + 0x28) = 4;
    *(uint32_t*)(self + 0x2c) = 0;
    if (msgSrv != 0 && iVar1 != 0) {
        uint32_t off = 0;
        do {
            ((void (*)(int, int))*(int*)(*msgSrv + 0x24))(
                iVar1, *(int*)(0x0145f8e0 + off));
            off += 4;
        } while (off < 0x10);
    }
}

// ===========================================================================
// @ 0x00b274e0  factory: allocate + construct a 0x68-byte saved-game header
// ===========================================================================
void* CreateSavedGameHeader()
{
    uint8_t* o = (uint8_t*)EAAllocate(0x68, (const char*)0x0145fb0c, 0, 0, 0, 0);
    if (o != 0) {
        *(uint32_t*)(o + 8) = 0;
        *(void**)(o + 4) = (void*)0x013ec458;
        *(void**)(o) = (void*)0x0145faa8;
        *(void**)(o + 4) = (void*)0x0145fa98;

        uint8_t* c = o + 0x18;
        uint32_t z = 0;
        *(uint32_t*)(c + 4) = z;
        *(uint32_t*)(c + 8) = z;
        *(uint32_t*)(c + 0xc) = z;
        *(uint32_t*)(o + 0x20) = 0;
        o[0x24] = 0;
        *(uint32_t*)(o + 0x28) = 0;
        *(uint32_t*)(c) = (uint32_t)(int)c;
        *(uint32_t*)(o + 0x1c) = (uint32_t)(int)c;
        *(uint32_t*)(o + 0x5c) = 0;
        *(uint32_t*)(o + 0x60) = 0;
        *(uint32_t*)(o + 0x64) = 0;
        return o;
    }
    return 0;
}

// ===========================================================================
// @ 0x00b27540  build the saved-game path string (copy ctor or save-area name)
// ===========================================================================
void* GetSavedGamePath(uint8_t* self, void* outv)
{
    uint8_t* out = (uint8_t*)outv;
    if (self[0x44] != 0) {
        WString_Assign_CopyCtor(out, self + 0x34);
        return out;
    }
    void* area = SP_GetSaveArea(0x4729a47);
    void* nm = ((void* (*)(void*))*(void**)(*(uint32_t*)area + 0x28))(area);
    *(uint32_t*)out = 0;
    *(uint32_t*)(out + 4) = 0;
    *(uint32_t*)(out + 8) = 0;
    RangeInitialize(out, (const wchar_t*)nm);
    return out;
}

// ===========================================================================
// @ 0x00b275a0  validate a saved-game file, reporting via the command string
// ===========================================================================
void ValidateSavedGameFile(void* self, void* a2, void* a3)
{
    uint8_t* p = (uint8_t*)self;
    int* out1 = (int*)a2;
    int* out2 = (int*)a3;
    uint32_t local_ab0 = 0, local_aac = 0, local_aa8 = 0;
    uint32_t flags = 0;

    // build the full saved-game path into a wide string
    RangeInitialize(p, 0);
    void* local_aa0 = 0; void* local_a9c = 0; int local_a98 = 0;
    GetSavedGamePath(p, &local_aa0);
    void* src = local_aa0;
    int len = ((int)local_a9c - (int)local_aa0) >> 1;

    wchar_t buf[520];
    for (int i = 0; i < len; ++i)
        buf[i] = ((wchar_t*)src)[i];
    buf[len] = 0;

    void* norm = FUN_00688f00(&buf, &buf, 0);
    if (norm != &buf)
        ((WStringFwd*)(*(void**)norm))->Assign(*(void**)norm,
                                              *(void**)((char*)norm + 4));
    if (norm != 0)
        operator_delete__(norm);

    if (File_Exists(buf) == 0) {
        *out1 = 0;
        *out2 = 0;
        if (src) operator_delete__(src);
        flags = local_aa8 - local_ab0;
        if (flags > 2 && local_ab0 != 0)
            operator_delete__((void*)local_ab0);
        return;
    }

    void* pHdr = ZoneObject_New(0x388, "Simulator", 0, 0, 0, 0);
    int res = 0;
    if (pHdr != 0) {
        res = (int)DatabasePackedFile_Ctor(pHdr, 0, 0);
        if (res != 0)
            (*(void(**)(int))*(int*)(res + 4))(res);
    }
    void* pDb = ZoneObject_New(0x24, "Simulator", 0, 0, 0, 0);
    int* piVar9 = 0;
    if (pDb != 0) {
        piVar9 = (int*)cObjectDatabase_Ctor(pDb, (void*)res);
        if (piVar9 != 0)
            (*(void(**)(int*))*piVar9)(piVar9);
    }
    (*(void(**)(void))(piVar9[1] + 4))();
    (*(void(**)(int*, wchar_t*))(*(int*)(piVar9 + 1) + 0x2c))(piVar9 + 1, buf);
    char ok = (*(char(**)(int*, int, int))(*piVar9 + 0x3c))(piVar9, 1, 0);
    if (ok != 0) {
        void* local_a8c = 0, *local_a88 = 0;
        FUN_00693cd0(piVar9, &local_a88, &local_a88, &local_a88);
        int serial = (int)local_a8c;
        char sz[0x20];
        cVarListSerializer_Ctor(sz, &local_a8c, &g_dat_1568b08, 0x1a0d26);
        cVarListSerializer_Serialize(sz, (void*)serial);
        FUN_00693900();
        (*(void(**)(void))(piVar9[1] + 0x1c))();
        (*(void(**)(void))(piVar9[1] + 8))();
        *out2 = (int)0x0145fa98;
        *out1 = (int)0x0145faa8;
        uint32_t r = (uint32_t)*out1;
        (*(void(**)(int*))*piVar9)(piVar9);
        if (res != 0)
            (*(void(**)(int))*(int*)(res + 4))(res);
        if (src) operator_delete__(src);
        flags = local_aa8 - local_ab0;
        if (flags > 2 && local_ab0 != 0)
            operator_delete__((void*)local_ab0);
        return;
    }
    *out1 = 0;
    *out2 = 0;
    (*(void(**)(int*))*piVar9)(piVar9);
    if (res != 0)
        (*(void(**)(int))*(int*)(res + 4))(res);
    if (src) operator_delete__(src);
    flags = local_aa8 - local_ab0;
    if (flags > 2 && local_ab0 != 0)
        operator_delete__((void*)local_ab0);
}

// ===========================================================================
// @ 0x00b279e0  (large) load saved game from stream
// ===========================================================================
void LoadSavedGameStream(void* self, void* a2)
{
    uint8_t* p = (uint8_t*)self;
    int local_adc = 0;
    uint32_t local_ae0 = 0;

    ValidateSavedGameFile(p, &local_adc, &local_ae0);

    RangeInitialize(p, 0);
    void* local_aa0 = 0; void* local_a9c = 0; int local_a98 = 0;
    GetSavedGamePath(p, &local_aa0);
    void* src = local_aa0;
    int len = ((int)local_a9c - (int)local_aa0) >> 1;

    wchar_t buf[520];
    for (int i = 0; i < len; ++i)
        buf[i] = ((wchar_t*)src)[i];
    buf[len] = 0;

    void* norm = FUN_00688f00(&buf, &buf, 0);
    if (norm != &buf)
        ((WStringFwd*)(*(void**)norm))->Assign(*(void**)norm,
                                              *(void**)((char*)norm + 4));
    if (norm != 0)
        operator_delete__(norm);

    void* pHdr = ZoneObject_New(0x388, "Simulator", 0, 0, 0, 0);
    int res = 0;
    if (pHdr != 0) {
        res = (int)DatabasePackedFile_Ctor(pHdr, 0, 0);
        local_adc = res;
        if (res != 0)
            (*(void(**)(int))*(int*)(res + 4))(res);
    }
    void* pDb = ZoneObject_New(0x24, "Simulator", 0, 0, 0, 0);
    int* piVar6 = 0;
    if (pDb != 0) {
        piVar6 = (int*)cObjectDatabase_Ctor(pDb, (void*)res);
        if (piVar6 != 0)
            (*(void(**)(int*))*piVar6)(piVar6);
    }
    int* piVar1 = piVar6 + 1;
    (*(void(**)(void))(piVar6[1] + 4))();
    (*(void(**)(int*, wchar_t*))(*(int*)piVar1 + 0x2c))(piVar1, buf);
    (*(void(**)(int*, int, int))(*piVar6 + 0x3c))(piVar6, 1, 0);

    void* local_a8c = 0, *local_a88 = 0;
    FUN_00693cd0(piVar6, &local_a88, &local_a88, &local_a88);
    int serial = (int)local_a8c;
    char sz[0x40];
    cVarListSerializer_Ctor(sz, &local_a8c, &g_dat_1568b08, 0x1a0d26);
    cVarListSerializer_Serialize(sz, (void*)serial);

    uint32_t packed = ((uint32_t)(unsigned long)local_a88 << 16) |
                      (uint32_t)(unsigned long)local_a8c;
    FUN_00692ec0(packed);
    FUN_00692ea0();
    void* pm = FUN_00b3d230();
    FUN_00d414e0((int)pm);

    char ok = (*(char(**)(int*, uint32_t))(*piVar6 + 0x20))(piVar6, packed);
    if (ok != 0) {
        int* piVar7 = (int*)PropertyManager();
        (*(char(**)(int*, uint32_t, void*))(*piVar7 + 0x2c))(piVar7, 0xbb3685dc, 0);
        void* nm = (void*)FUN_00b3d230();
        (*(void(**)(void*, void*))(*(int*)nm + 0x4c))(nm, src);
        FUN_00693900();
    }
    FUN_00693900();
    (*(void(**)(void))(*piVar1 + 0x1c))();
    (*(void(**)(void))(*piVar1 + 8))();
    (*(void(**)(int*))(*piVar6))(piVar6);
    if (res != 0)
        (*(void(**)(int))*(int*)(res + 4))(res);
    if (src) operator_delete__(src);
}
