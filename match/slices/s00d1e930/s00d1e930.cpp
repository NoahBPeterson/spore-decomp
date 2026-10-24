// Slice s00d1e930 -- SP::UseAbility and the ability-slot bookkeeping helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker, so only the call
// encoding / ABI matters)
// ---------------------------------------------------------------------------
void* SP_NounManager();                                      // 0x00b3d300 cdecl
void* SP_PropertyManager();                                  // 0x0067de30 cdecl
void* SP_GetCurrentGameMode();                               // 0x00b5b800 cdecl
void* FUN_00f473a0(size_t, const char*, int, int, int, int); // 0x00f473a0 cdecl operator new
void  FUN_004d3760(void*);                                   // 0x004d3760 thiscall ctor
void  FUN_00f47380(void*);                                   // 0x00f47380 cdecl operator delete
char  FUN_004d92b0(void*, void*);                            // 0x004d92b0 cdecl ReadAbilityData
char  FUN_00685520(int);                                     // 0x00685520 cdecl
void  FUN_00555e80(void*, void*);                            // 0x00555e80 cdecl
void  FUN_00d1f160(uint32_t, uint32_t*, int, void**);        // 0x00d1f160 cdecl
__declspec(noinline) void __cdecl FUN_00d1f250(void**, uint32_t); // 0x00d1f250 cdecl

// ---------------------------------------------------------------------------
// ability-slot tables (populated by FUN_00d1f2a0)
// ---------------------------------------------------------------------------
void* g_169de30[3];   // 0x0169de30
void* g_169de3c[2];   // 0x0169de3c
void* g_169de44[2];   // 0x0169de44
void* g_169de4c[6];   // 0x0169de4c
void* g_169de64[6];   // 0x0169de64

// ---------------------------------------------------------------------------
// ref-counted object: vtable at +0x00, ref count at +0x04
// ---------------------------------------------------------------------------
struct RCObj {
    virtual void vf0(int arg);      // vtable[0]  (destroy/release with a flag)
    int mRef;                       // +0x04
};

// shared release step used by the slot tables and the ability holder
static inline void rc_release(RCObj* p)
{
    int n = p->mRef;
    p->mRef = --n;
    if (n == 0) {
        p->mRef = 1;
        p->vf0(1);
    }
}

// ---------------------------------------------------------------------------
// property list (the object held by FUN_00d1f160's local): vtable[1] releases.
// ---------------------------------------------------------------------------
struct PropList {
    virtual void vf0(int arg);      // vtable[0]
    virtual void vf1();             // vtable[1]  (release)
};

// ===========================================================================
// @ 0x00d1f250
// ===========================================================================
void __cdecl FUN_00d1f250(void** arr, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++) {
        RCObj* p = (RCObj*)arr[i];
        if (p != 0) {
            arr[i] = 0;
            int n = p->mRef;
            p->mRef = --n;
            if (n == 0) {
                p->mRef = 1;
                p->vf0(1);
            }
        }
    }
}

// ===========================================================================
// @ 0x00d1f3c0
// ===========================================================================
void __cdecl FUN_00d1f3c0(void)
{
    FUN_00d1f250(g_169de30, 3);
    FUN_00d1f250(g_169de3c, 2);
    FUN_00d1f250(g_169de44, 2);
    FUN_00d1f250(g_169de4c, 6);
    FUN_00d1f250(g_169de64, 6);
}

// ===========================================================================
// @ 0x00d1f2a0
// ===========================================================================
void __cdecl FUN_00d1f2a0(void)
{
    uint32_t a[6];

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    FUN_00d1f160(0xdd91ac58, a, 3, g_169de30);

    a[0] = 0x93f63c50; a[1] = 0x854f28cd;
    FUN_00d1f160(0xdd91ac58, a, 2, g_169de3c);

    if (FUN_00685520(2)) {
        a[0] = 0x672b9a9f; a[1] = 0x0f27ecc2;
        FUN_00d1f160(0xdd91ac58, a, 2, g_169de44);
    }

    a[0] = 0x6282938f; a[1] = 0xe10f1680; a[2] = 0x042592a5;
    a[3] = 0x5a93b784; a[4] = 0xe5aa4c4d; a[5] = 0xdf4f5863;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de4c);

    a[0] = 0xb522e3ee; a[1] = 0x515b7e25; a[2] = 0x166a2770;
    a[3] = 0xc60fc2ec; a[4] = 0xec13fdbe; a[5] = 0x2b2f0629;
    FUN_00d1f160(0xc85c1f8b, a, 6, g_169de64);
}

// ===========================================================================
// ability holder (the object whose destructor FUN_00d1f070 is)
// ===========================================================================
struct AbilitySet {
    RCObj* mArr00[3];   // +0x00
    RCObj* mArr0c[2];   // +0x0c
    RCObj* mArr14[2];   // +0x14
    RCObj* mArr1c[6];   // +0x1c
    RCObj* mArr34[6];   // +0x34
    void destroy();
};

// @ 0x00d1f070
void AbilitySet::destroy()
{
    for (int i = 5; i >= 0; i--) rc_release(mArr34[i]);
    for (int i = 5; i >= 0; i--) rc_release(mArr1c[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr14[i]);
    for (int i = 1; i >= 0; i--) rc_release(mArr0c[i]);
    for (int i = 2; i >= 0; i--) rc_release(mArr00[i]);
}

// ===========================================================================
// @ 0x00d1f160
// ===========================================================================
void __cdecl FUN_00d1f160(uint32_t id, uint32_t* data, int count, void** arr)
{
    void* local4 = 0;
    void* pm = SP_PropertyManager();

    for (int n = count; n != 0; n--) {
        if (local4 != 0) {
            PropList* t = (PropList*)local4;
            local4 = 0;
            t->vf1();
        }

        ((void(__thiscall*)(void*, uint32_t, uint32_t, void**))
             (*(void***)pm)[0x2c / 4])(pm, *data, id, &local4);

        if (local4 != 0) {
            RCObj* nc = (RCObj*)FUN_00f473a0(0x13c, "Simulator/cCreatureAbility", 0, 0, 0, 0);
            if (nc != 0)
                FUN_004d3760(nc);

            RCObj* old = (RCObj*)arr[0];
            if (nc != old) {
                if (nc != 0)
                    nc->mRef++;
                arr[0] = nc;
                if (old != 0)
                    rc_release(old);
            }

            FUN_004d92b0(arr[0], local4);
        }

        data++;
        arr++;
    }

    if (local4 != 0) {
        PropList* t = (PropList*)local4;
        t->vf1();
    }
}

// ===========================================================================
// @ 0x00d1f400   (partial reconstruction -- see partial.txt)
// ===========================================================================
struct TerrainSphere {
    char  _p000[0x10fc];
    void* mpListA;                        // +0x10fc
    void* mpListB;                        // +0x1100
};

struct IdVec {                            // grow-able uint32 vector
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCap;                      // +0x08
};

char g_1654c01;                           // 0x01654c01  game-mode tag
char g_1654c02;                           // 0x01654c02

void  FUN_00c79f00(const char*, uint32_t);          // 0x00c79f00 cdecl
char  FUN_00c77380p(void*, const char*, uint32_t*); // 0x00c77380 thiscall
void* FUN_00f67d90(void*);                          // 0x00f67d90 thiscall GetCurrentTerrainSphere

bool __cdecl FUN_00d1f400(uint32_t param_1)
{
    uint32_t tag = *(uint32_t*)(param_1 + 8);
    (void)tag;

    void* terr = SP_NounManager();
    TerrainSphere* sphere = (TerrainSphere*)
        ((void*(__thiscall*)(void*)) FUN_00f67d90)(terr);

    uint32_t foundA = 0;
    uint32_t foundB = 0;
    IdVec vec;
    vec.mpBegin = 0; vec.mpEnd = 0; vec.mpCap = 0;

    const char* nameA;
    const char* nameB;

    void* mode = SP_GetCurrentGameMode();
    if (mode == (void*)&g_1654c01) {
        nameA = "ability-5ff7927";
        nameB = "ability-5ff7928";
        FUN_00555e80(sphere->mpListA, &vec);
    } else if (mode == (void*)&g_1654c02) {
        nameA = "ability-5ff7baf";
        nameB = "ability-5ff7bb6";
        FUN_00555e80(sphere->mpListA, &vec);
        FUN_00555e80(sphere->mpListB, &vec);
    } else {
        if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
            FUN_00f47380(vec.mpBegin);
        return false;
    }

    char okA = FUN_00c77380p(terr, nameA, &foundA);
    char okB = FUN_00c77380p(terr, nameB, &foundB);
    if (okA == 0 || okB == 0) {
        void* mode2 = SP_GetCurrentGameMode();
        uint32_t n = (uint32_t)(vec.mpEnd - vec.mpBegin);
        uint32_t flags = 0;
        if (mode2 == (void*)&g_1654c01) {
            for (uint32_t i = 0; i < n; i++) {
                uint32_t id = vec.mpBegin[i];
                if (id == 0xe4237bd6)          flags |= 0x20000;
                else if (id == 0x03419db6)     flags |= 0x40000;
                else if (id == 0x630ad0eb)     flags |= 0x80000;
            }
        } else if (mode2 == (void*)&g_1654c02) {
            for (uint32_t i = 0; i < n; i++) {
                int id = (int)vec.mpBegin[i];
                if (id < -0x11f3edc6) {
                    if (id == -0x11f3edc7)         flags |= 0x200000;
                    else if (id == -0x49d6a8dc)    flags |= 0x800000;
                    else if (id == -0x3867e9cf)    flags |= 0x1000000;
                    else if (id == -0x1a0caa4d)    flags |= 0x100000;
                } else if (id == 0x27cb4512)       flags |= 0x2000000;
                else if (id == 0x5961d110)         flags |= 0x400000;
            }
        }
        foundB = 0;
        foundA = flags;
        FUN_00c79f00(nameA, flags);
        FUN_00c79f00(nameB, 0);
    }

    if (vec.mpBegin != 0 && *((int*)vec.mpBegin - 1) != 0)
        FUN_00f47380(vec.mpBegin);

    // tail: 64-bit allshl bit test over (foundA, foundB) -- omitted, see partial.txt
    return false;
}

// ===========================================================================
// @ 0x00d1e930   (partial reconstruction -- see partial.txt)
// ===========================================================================
struct AbilityEntry {
    char  _p000[0x08];
    void* mpParam;                        // +0x08
    int   mMode;                          // +0x0c
    char  _p010[0x115 - 0x10];
    char  mFlag;                          // +0x115
};

struct CreatureFields {
    char  _p000[0xc0];
    void* mpSubVtbl;                      // +0xc0
    char  _p0c4[0xe70 - 0xc4];
    void* mpE70;                          // +0xe70
    void* mpE74;                          // +0xe74
};

void* FUN_00d51660();                     // 0x00d51660 cdecl
void  FUN_00ac80d0(void*, const char*);   // 0x00ac80d0 cdecl
void* FUN_00c0ee70(void*);                // 0x00c0ee70 thiscall GetTargetAsCreature
void  FUN_00c196a0(void*, void*, int, int); // 0x00c196a0 cdecl
char  FUN_00c0c120(void*);                // 0x00c0c120 thiscall
void* FUN_00b1f9c0(void*);                // 0x00b1f9c0 thiscall GetItemID
void  FUN_00c1ad10(void*, int);           // 0x00c1ad10 thiscall SetSprinting

void __cdecl SP_UseAbility(void* self, int param_2)
{
    if (param_2 == -1)
        return;

    int count = ((int(__thiscall*)(void*)) (*(void***)self)[0xb0 / 4])(self);
    if (param_2 >= count)
        return;

    AbilityEntry* entry = (AbilityEntry*)
        ((void*(__thiscall*)(void*, int)) (*(void***)self)[0xb4 / 4])(self, param_2);

    CreatureFields* cf = (CreatureFields*)self;
    void* target = entry->mpParam;
    if (entry->mMode == 0)
        cf->mpE74 = (void*)param_2;
    else if (entry->mMode == 1)
        cf->mpE70 = (void*)param_2;

    char c = ((char(__thiscall*)(void*))
              (*(void***)((char*)self + 0xc0))[0x58 / 4])((char*)self + 0xc0);

    if (c != 0 && entry->mFlag != 0) {
        void* x = FUN_00d51660();
        if (((unsigned char)(*(uint32_t*)((char*)x + 0x6c) >> 4) & 1) != 0) {
            FUN_00ac80d0(self, "/");
            ((void(__thiscall*)(void*, int, int, float, int, int, int, int))
                 (*(void***)x)[0xff / 4])(x, 0, 0x10, 0x7f7fffff, param_2, 0, 0, 0);
            return;
        }
    }

    // dispatch on param_2: 45 cases (0x0d..0x56).  A representative subset is
    // reconstructed here; the remaining action bodies are omitted -- see
    // partial.txt.
    switch (param_2) {
    case 0x28: {
        void* tc = FUN_00c0ee70(self);
        if (tc != 0) {
            FUN_00c196a0((void*)target, (void*)param_2, 1, 0);
            return;
        }
        break;
    }
    case 0x27:
    case 0x50: {
        char sprinting = FUN_00c0c120(self);
        if (sprinting == 0) {
            FUN_00c196a0((void*)target, (void*)param_2, 1, 0);
            FUN_00c1ad10(self, 1);
        } else {
            FUN_00c1ad10(self, 0);
        }
        void* mgr = SP_NounManager();
        int* list = (int*)FUN_00b1f9c0(mgr);
        for (int* it = (int*)list[0]; it != (int*)list[1]; ++it)
            FUN_00c1ad10((void*)*it, sprinting ? 0 : 1);
        return;
    }
    default:
        break;
    }
}