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
extern void* FUN_00b3d320(const void*);                  // 0x00b3d320
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
int ResetDefaultSavedGame()
{
    if ((void*)&DAT_0167df60 != (void*)&DAT_0167df50) {
        ((WStringFwd*)0x0167df50)->Assign(*(void**)0x0167df60, *(void**)0x0167df64);
    }
    void* p = FUN_00b3d320(&DAT_01654c08);
    FUN_00b1e410((int)p);
    return 1;
}

// ===========================================================================
// @ 0x00b271b0  scalar-deleting destructor for the saved-game object
// ===========================================================================
void* SavedGame_Dtor(void* self, uint8_t flags)
{
    uint8_t* s = (uint8_t*)self;
    *(void**)s = (void*)0x0145faa8;
    *(void**)(s + 4) = (void*)0x0145fa98;
    DoNukeSubtree(*(void**)(s + 0x20));
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
    case 1: name = (uint8_t*)ADDR_c01; break;
    case 2: name = (uint8_t*)ADDR_c02; break;
    case 4: name = (uint8_t*)ADDR_c04; break;
    case 5: name = (uint8_t*)ADDR_c05; break;
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
    (void)p;
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
        *(uint32_t*)(o + 0x1c) = (uint32_t)(int)c;
        *(uint32_t*)(c) = (uint32_t)(int)c;
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
    (void)self; (void)a2; (void)a3;
}

// ===========================================================================
// @ 0x00b279e0  (large) load saved game from stream
// ===========================================================================
void LoadSavedGameStream(void* self, void* a2)
{
    (void)self; (void)a2;
}
