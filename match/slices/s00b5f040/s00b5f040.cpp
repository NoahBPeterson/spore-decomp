// Spore retail 00b5f040..00b600a0 -- App::cSuperPowersCommand and related UI helpers.
// The larger functions are game-side and are reconstructed approximately here.

#include "types.h"
#include <intrin.h>

typedef unsigned int uint32;
typedef unsigned int size_type;

extern "C" void* EASTL_deallocate(void* p);      // 0x00f47380
extern "C" int   strcmp(const char*, const char*);
extern "C" int   atoi(const char*);

// ---------------------------------------------------------------------------
// Small exact helpers
// ---------------------------------------------------------------------------

void FUN_00b5e0b0();                             // 0x00b5e0b0 (thiscall: ecx=self, stack arg a)

// @ 0x00b5f1b0
unsigned char FUN_00b5f1b0(int a, int b)
{
    if (b != 0)
        ((void(__thiscall*)(void*, int))FUN_00b5e0b0)((void*)b, a);
    return 1;
}

// @ 0x00b5f950  EA::AutoRefCount<EA::UTFWinControls::IWinText>::operator=
namespace EA { namespace UTFWinControls {
class IWinText {
public:
    virtual int AddRef();
    virtual int Release();
};
} }

namespace EA {
template <typename T> class AutoRefCount { public:
    T* mpObject;
    AutoRefCount& operator=(T* p);
};
template class AutoRefCount<UTFWinControls::IWinText>;
}

EA::AutoRefCount<EA::UTFWinControls::IWinText>&
EA::AutoRefCount<EA::UTFWinControls::IWinText>::operator=(UTFWinControls::IWinText* p)
{
    UTFWinControls::IWinText* old = mpObject;
    if (p != old) {
        if (p != 0)
            p->AddRef();
        mpObject = p;
        if (old != 0)
            old->Release();
    }
    return *this;
}

// @ 0x00b60070
int* __fastcall FUN_00b60070(int* self)
{
    int z = 0;
    self[1] = z;
    self[0] = 0x1462d70;
    self[4] = z;
    self[5] = z;
    int d = 0x1667bac;
    self[6] = d;
    self[7] = d;
    self[8] = 0x1667bad;
    return self;
}

// ---------------------------------------------------------------------------
// Calling-convention thunks for virtual dispatch / callbacks
// ---------------------------------------------------------------------------

typedef void (__thiscall *Thunk0)(void*);
typedef void (__thiscall *Thunk1i)(void*, int);
typedef void (__thiscall *Thunk2i)(void*, int, int);
typedef void (__thiscall *Thunk3i)(void*, int, int, int);
typedef int  (__thiscall *Thunk0r)(void*);
typedef int  (__thiscall *Thunk1r)(void*, int);
typedef float(__thiscall *ThunkF0)(void*);

// Virtual call: read the vtable pointer at +vtOff of *obj, take slot +slot, call on obj.
#define VTBLPTR(o, vtOff)   (*(void**)((char*)(*(void**)(o)) + (vtOff)))
#define VTSLOT(o, slot)     (*(void**)((char*)(*(void**)(o)) + (slot)))

// ---------------------------------------------------------------------------
// Externals
// ---------------------------------------------------------------------------

extern "C" void*  FUN_00b3d320(void);            // 0x00b3d320
extern "C" void   FUN_00b2fbe0(void);            // 0x00b2fbe0
extern "C" void   FUN_00b33970(int, int);        // 0x00b33970
extern "C" void*  FUN_0067caa0(void);            // 0x0067caa0 SP::WindowManager
extern "C" void*  FUN_0067cab0(void);            // 0x0067cab0
extern "C" void*  FUN_0067dcc0(void);            // 0x0067dcc0 SP::MessageServer
extern "C" void*  FUN_0067de30(void);            // 0x0067de30 SP::PropertyManager
extern "C" void*  FUN_00b3d380(void);            // 0x00b3d380 SP::GameTimeManager
extern "C" void*  FUN_00805070(void);            // 0x00805070 SPUIHelpers::GetLayoutManager
extern "C" void*  FUN_00b3d300(void);            // 0x00b3d300 SP::NounManager
extern "C" int    FUN_00b5b800(void);            // 0x00b5b800 SP::GetCurrentGameMode
extern "C" void   FUN_00b6d190(void);            // 0x00b6d190
extern "C" void   FUN_00b6e6d0(void);            // 0x00b6e6d0
extern "C" void*  FUN_00b3d220(void);            // 0x00b3d220
extern "C" void   FUN_00571db0(int, int, int, int, int);  // 0x00571db0 EA::Messaging::RemoveHandler
extern "C" void   FUN_00ea5380(void);            // 0x00ea5380
extern "C" void   FUN_00b7c810(int);             // 0x00b7c810 SP::cSPPieMenu::HideUTFMenu
extern "C" void   FUN_00e25bd0(void*, void*);    // 0x00e25bd0 vector erase
extern "C" void*  FUN_00c37370(void);            // 0x00c37370
extern "C" void*  FUN_010407c0(void);            // 0x010407c0 SP::GetSpaceRelationshipTuning
extern "C" void   FUN_00c14530(void);            // 0x00c14530
extern "C" void   FUN_00d1f3c0(void);            // 0x00d1f3c0
extern "C" void   FUN_00c9e530(void);            // 0x00c9e530
extern "C" void   FUN_00b5b730(void);            // 0x00b5b730
extern "C" void   FUN_00d1e670(void);            // 0x00d1e670
extern "C" void   FUN_00d49450(void);            // 0x00d49450
extern "C" int    FUN_00555dd0(int);             // 0x00555dd0
extern "C" void*  FUN_01002bd0(int, int);        // 0x01002bd0 SP::SpaceGameGet
extern "C" void   FUN_00b3d3d0(void);            // 0x00b3d3d0
extern "C" void   FUN_00e5c560(void);            // 0x00e5c560
extern "C" void*  FUN_00ad49b0(void);            // 0x00ad49b0
extern "C" int    FUN_0104cbc0(void);            // 0x0104cbc0
extern "C" void   FUN_0104cbd0(int);             // 0x0104cbd0
extern "C" void*  FUN_00446ff0(void);            // 0x00446ff0
extern "C" void   FUN_00841000(void*, const char*, ...);  // 0x00841000 Output
extern "C" void*  FUN_00fd9c60(void);            // 0x00fd9c60
extern "C" void*  FUN_00feb9f0(void);            // 0x00feb9f0 SP::GetMissionManager
extern "C" void*  FUN_00d38840(void);            // 0x00d38840 SP::cCreatureModeStrategy::Instance
extern "C" void*  FUN_00cd40b0(void);            // 0x00cd40b0 SP::cTribeModeStrategy::Instance
extern "C" void*  FUN_00cf74c0(void);            // 0x00cf74c0 SP::cCivModeStrategy::Get
extern "C" void*  FUN_00d1bf00(void);            // 0x00d1bf00 GetEditSelection
extern "C" void*  FUN_00a1ad60(void*);           // 0x00a1ad60
extern "C" void   FUN_00bf23d0(void*);           // 0x00bf23d0
extern "C" int    FUN_00bf0f40(void*);           // 0x00bf0f40
extern "C" void   FUN_00c389f0(int);             // 0x00c389f0
extern "C" void   FUN_00c0b950(void);            // 0x00c0b950
extern "C" void   FUN_00cd7d10(void);            // 0x00cd7d10
extern "C" void   FUN_00d3d420(void);            // 0x00d3d420
extern "C" void   FUN_00b5f990(void);            // 0x00b5f990
extern "C" void   FUN_00b5fa10(void);            // 0x00b5fa10
extern "C" void   FUN_00ae72d0(void);            // 0x00ae72d0
extern "C" void   FUN_00b1e520(void);            // 0x00b1e520
extern "C" void   FUN_00b1e500(void);            // 0x00b1e500
extern "C" void   FUN_00572620(void*);           // 0x00572620
extern "C" void   FUN_00572660(void*);           // 0x00572660
extern "C" int    FUN_00571ef0(void);            // 0x00571ef0

extern unsigned char DAT_01686af0;               // 0x01686af0
extern unsigned char DAT_01686b50;               // 0x01686b50
extern unsigned char DAT_0168bd6c;               // 0x0168bd6c
extern int* DAT_0168df68;                        // 0x0168df68
extern unsigned char DAT_018c6de8;               // 0x018c6de8
extern int g_156acd0;                             // 0x0156acd0

// ---------------------------------------------------------------------------
// Opaque receiver types
// ---------------------------------------------------------------------------

struct cGameTimeManager { void FUN_00b31a90(); };                   // 0x00b31a90
struct cLayoutManager   { bool FUN_00810760(uint32 id);             // 0x00810760 IsWorldVisible
                          void FUN_00810660(uint32 id, bool on); }; // 0x00810660
struct MainWin_s0081    { void FUN_008153e0();                      // 0x008153e0 CloseAll
                          void FUN_00812d60(int); };                // 0x00812d60
struct C_8017f0         { bool FUN_008017f0(void* p); };            // 0x008017f0 Set
struct cSphereObj       { int  FUN_00c756e0(int id);                // 0x00c756e0
                          void FUN_00c75cc0(int a, int b); };       // 0x00c75cc0
struct cGameNounManager { int  FUN_00b25fb0();                      // 0x00b25fb0 GetPlayerCivilization
                          int  FUN_00b1fdb0();                      // 0x00b1fdb0 GetAvatar
                          int  FUN_00b1f9c0();                      // 0x00b1f9c0 GetItemID
                          int  FUN_00b1fef0();                      // 0x00b1fef0 GetPlayerTribe
                          int  FUN_00f67d90();                      // 0x00f67d90 GetCurrentTerrainSphere
                          int  FUN_00b21340(int, void*, void*, void*, void*); }; // 0x00b21340 GetGameDataVector
struct cCombatant       { void FUN_00bfd1a0(float amount); };       // 0x00bfd1a0 PartialRepair
struct cTribe           { void FUN_00c8fb50(); };                   // 0x00c8fb50
struct cPlayerInventory { void FUN_0104e340(int*, void*); };        // 0x0104e340 CreateToolFromToolID
struct cSPSimulatorSpaceGame { int FUN_00a1ad60(); };               // 0x00a1ad60 GetPlayerInventory
struct cMissionManager  { void FUN_00feba60(int);                   // 0x00feba60
                          void FUN_00feba80(int); };                // 0x00feba80

// ---------------------------------------------------------------------------
// cSuperPowersCommand
// ---------------------------------------------------------------------------

struct cArgumentSpec {
    char m_data[0x30];
    cArgumentSpec(bool b);                                          // 0x0083a9f0
    void Parse(int args, int parser);                               // 0x0083b9d0
    static void ConstructSpec(cArgumentSpec* self, const char* desc, const char* keyword,
                              void* p1, const char* spec, void* out,
                              const char* name, int d);             // 0x0083bcd0
};

class cCommandBase {
public:
    virtual int FUN_vtbl0();                                        // forces the vfptr at +0x00
    int mArguments;                                                 // +0x04
    int mField08;                                                   // +0x08
    unsigned char mSuperPowersEnabled;                              // +0x0c
    unsigned char mPad0D[3];                                        // +0x0d
    cCommandBase();                                                 // 0x0083c800
};

class cSuperPowersCommand : public cCommandBase {
public:
    cArgumentSpec mSpec;                                            // +0x10
    int     mField40[7];                                            // +0x40 .. 0x5c
    void**  mVecBegin;                                              // +0x5c
    void**  mVecEnd;                                                // +0x60
    int     mField64[0x1d];                                         // +0x64 .. 0xd8
    int     mTrait;                                                 // +0xd8

    cSuperPowersCommand();                                          // 0x00b5f620
    void FUN_00b5f040(int a, int b);                                // 0x00b5f040
    void FUN_00b5f670(int a);                                       // 0x00b5f670
    void FUN_00b5f7b0(int a);                                       // 0x00b5f7b0
    void FUN_00b5fa90(int a);                                       // 0x00b5fa90
    void FUN_00b5fde0(int a);                                       // 0x00b5fde0
    void FUN_00b5e3f0(int a);                                       // 0x00b5e3f0
};

// @ 0x00b5f620  App::cSuperPowersCommand::cSuperPowersCommand
cSuperPowersCommand::cSuperPowersCommand() : cCommandBase(), mSpec(true)
{
    cArgumentSpec::ConstructSpec(&mSpec,
        "Sets the trait which will determine what super powers are available.",
        ":trait", &g_156acd0, "<specificTrait:trait>", &mTrait, "the trait", 0);
}

// @ 0x00b5f040
void cSuperPowersCommand::FUN_00b5f040(int a, int b)
{
    char* t = (char*)FUN_00b3d320();
    *(int*)(t + 0x24) = a;
    *(int*)(t + 0x20) = b;
    *(char*)(t + 0x28) = 0;
    DAT_01686af0 = 0;
    if (a == 0x2ccd1d2)
        mSuperPowersEnabled = (unsigned char)(b != 0xdbdba1);

    ((cGameTimeManager*)FUN_00b3d380())->FUN_00b31a90();

    if (b == 0x2ccd1d2 || b == -1 || b == 0x1654c08)
        FUN_00b2fbe0();
    FUN_00b5e3f0(b);

    cLayoutManager* lm = (cLayoutManager*)FUN_00805070();
    if (!lm->FUN_00810760(0x5b598f6u))
        lm->FUN_00810660(0x5b598f6u, true);

    FUN_00b33970(a, b);

    void* wm = FUN_0067caa0();
    int r = ((Thunk0r)VTSLOT(wm, 4))(wm);
    MainWin_s0081* mw = (MainWin_s0081*)(r ? (char*)(r - 4) : 0);
    mw->FUN_008153e0();
    mw->FUN_00812d60(0);

    int n = (int)(((char*)mVecEnd - (char*)mVecBegin) >> 2);
    for (int i = 0; i < n; i++) {
        void* item = mVecBegin[i];
        ((Thunk2i)VTSLOT(item, 0x14))(item, a, b);
    }

    void* cs;
    cs = (char*)FUN_00d38840() + 8;
    ((Thunk2i)VTSLOT(cs, 0x14))(cs, a, b);

    cs = (char*)FUN_00cd40b0() + 0xc;
    ((Thunk2i)VTSLOT(cs, 0x14))(cs, a, b);

    cs = (char*)FUN_00cf74c0() + 4;
    ((Thunk2i)VTSLOT(cs, 0x14))(cs, a, b);

    cs = (char*)FUN_00fd9c60() + 8;
    ((Thunk2i)VTSLOT(cs, 0x14))(cs, a, b);

    cs = (char*)FUN_00d1bf00() + 8;
    ((Thunk2i)VTSLOT(cs, 0x14))(cs, a, b);

    ((Thunk0)VTSLOT(this, 0x44))(this);

    void* q = FUN_0067cab0();
    ((C_8017f0*)q)->FUN_008017f0(0);
}

// @ 0x00b5f670
void cSuperPowersCommand::FUN_00b5f670(int a)
{
    mSpec.Parse(a, mArguments);

    int u = FUN_00555dd0(mTrait);
    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    cSphereObj* sph = (cSphereObj*)nm->FUN_00f67d90();
    sph->FUN_00c75cc0(u, mTrait);

    int mode = FUN_00b5b800();
    switch (mode) {
    case 0x1654c01:
    case 0x1654c02:
        FUN_00d1e670();
        FUN_00d49450();
        return;

    case 0x1654c04: {
        cGameNounManager* n2 = (cGameNounManager*)FUN_00b3d300();
        int c = n2->FUN_00b25fb0();
        if (c != 0) {
            FUN_00bf23d0((void*)c);
            return;
        }
        break;
    }

    case 0x1654c05: {
        int id = mTrait;
        bool bMatched = (id == 0x2b35f523 || id == (int)0xd9c806e4 || id == (int)0xf966d429 ||
                         id == (int)0xcf6c2ab4 || id == (int)0xb40d2187 || id == (int)0x9ce4639c ||
                         id == (int)0xa5656e84 || id == 0x50fee6bf || id == (int)0xb436c0bc ||
                         id == (int)0xb7cb9f7a);
        int uVar3 = bMatched ? 0 : 1;
        void* sg = FUN_01002bd0(uVar3, 1);
        ((Thunk2i)VTSLOT(sg, 0x0))(sg, uVar3, 1);
        FUN_00b3d3d0();
        void* ms = FUN_0067dcc0();
        ((Thunk3i)VTSLOT(ms, 0x2c))(ms, 1, 0x10bdd7cc, 0);
        break;
    }

    default:
        break;
    }
}

// @ 0x00b5f7b0
void cSuperPowersCommand::FUN_00b5f7b0(int a)
{
    (void)a;
    if (FUN_00b5b800() != 0x1654c04)
        return;

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    int civ = nm->FUN_00b25fb0();
    if (civ == 0) {
        DAT_0168bd6c = 1;
        return;
    }

    static const int kBases[3] = { (int)0xa426730b, (int)0xad56080c, (int)0xf71fa311 };
    static const int kAlts[3][3] = {
        { (int)0xcfb01b93, (int)0x5ece4770, (int)0xa8ec6f99 },
        { (int)0x17e5ef84, (int)0xb9de15f2, (int)0xfd159d91 },
        { (int)0x0cac124d, (int)0xc2ca9495, (int)0x60a78928 }
    };

    for (int g = 0; g < 3; g++) {
        cGameNounManager* n2 = (cGameNounManager*)FUN_00b3d300();
        cSphereObj* sph = (cSphereObj*)n2->FUN_00f67d90();
        if (sph->FUN_00c756e0(kBases[g]) == 0) {
            int which = FUN_00bf0f40((void*)civ);
            int alt;
            if (which == 0)
                alt = kAlts[g][0];
            else if (which == 1)
                alt = kAlts[g][1];
            else if (which == 2)
                alt = kAlts[g][2];
            else
                continue;
            cGameNounManager* n3 = (cGameNounManager*)FUN_00b3d300();
            cSphereObj* sph2 = (cSphereObj*)n3->FUN_00f67d90();
            sph2->FUN_00c75cc0(kBases[g], alt);
        }
    }

    FUN_00bf23d0((void*)civ);
    DAT_0168bd6c = 1;
}

// @ 0x00b5fa90
void cSuperPowersCommand::FUN_00b5fa90(int a)
{
    mSpec.Parse(a, mArguments);

    int mode = FUN_00b5b800();
    switch (mode) {
    case 0x1654c00:
        FUN_00e5c560();
        return;

    case 0x1654c01: {
        cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
        int vec = nm->FUN_00b1f9c0();
        int begin = *(int*)(vec + 0);
        int end = *(int*)(vec + 4);
        for (int p = begin; p != end; p += 4) {
            int obj = *(int*)p;
            if (obj != 0) {
                void* cmb = (char*)obj + 0x5a8;
                float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
                ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
                FUN_00c0b950();
            }
        }
        cGameNounManager* n2 = (cGameNounManager*)FUN_00b3d300();
        int av = n2->FUN_00b1fdb0();
        if (av != 0) {
            void* cmb = (char*)av + 0x5a8;
            float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
            ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
            FUN_00c0b950();
            return;
        }
        break;
    }

    case 0x1654c02: {
        cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
        int tribe = nm->FUN_00b1fef0();
        if (tribe != 0) {
            ((cTribe*)tribe)->FUN_00c8fb50();
            return;
        }
        break;
    }

    case 0x1654c03:
        break;

    case 0x1654c04: {
        cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
        int civ = nm->FUN_00b25fb0();
        int id = ((Thunk0r)VTSLOT((void*)civ, 0x4c))((void*)civ);

        cGameNounManager* n2 = (cGameNounManager*)FUN_00b3d300();
        char* v1 = (char*)n2->FUN_00b21340(0, (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420,
                                            (void*)&FUN_00b5f990, (void*)&FUN_00b1e520);
        {
            int begin = *(int*)(v1 + 4);
            int n = (*(int*)(v1 + 8) - begin) >> 2;
            for (int i = 0; i < n; i++) {
                int obj = *(int*)(begin + i * 4);
                int oid = ((Thunk0r)VTSLOT((void*)obj, 0x4c))((void*)obj);
                if (oid == id) {
                    void* cmb = (char*)obj + 0x120;
                    float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
                    ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
                }
            }
        }

        cGameNounManager* n3 = (cGameNounManager*)FUN_00b3d300();
        char* v2 = (char*)n3->FUN_00b21340(0, (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420,
                                            (void*)&FUN_00ae72d0, (void*)&DAT_018c6de8);
        {
            int begin = *(int*)(v2 + 4);
            int n = (*(int*)(v2 + 8) - begin) >> 2;
            for (int i = 0; i < n; i++) {
                int obj = *(int*)(begin + i * 4);
                int oid = ((Thunk0r)VTSLOT((void*)obj, 0x4c))((void*)obj);
                if (oid == id) {
                    void* cmb = (char*)obj + 0x508;
                    float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
                    ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
                }
            }
        }

        cGameNounManager* n4 = (cGameNounManager*)FUN_00b3d300();
        char* v3 = (char*)n4->FUN_00b21340(0, (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420,
                                            (void*)&FUN_00b5fa10, (void*)&FUN_00b1e500);
        {
            int begin = *(int*)(v3 + 4);
            int n = (*(int*)(v3 + 8) - begin) >> 2;
            for (int i = 0; i < n; i++) {
                int obj = *(int*)(begin + i * 4);
                int oid = ((Thunk0r)VTSLOT((void*)obj, 0x4c))((void*)obj);
                if (oid == id) {
                    void* cmb = (char*)obj + 0x588;
                    float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
                    ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
                }
            }
        }
        break;
    }

    case 0x1654c05: {
        FUN_00b3d300();
        int* v = (int*)FUN_00ad49b0();
        int begin = v[0];
        int n = (v[1] - begin) >> 2;
        for (int i = 0; i < n; i++) {
            int obj = *(int*)(begin + i * 4);
            if (obj != 0 && (*(int*)(obj + 0x714) == 3 || *(int*)(obj + 0x714) == 0)) {
                void* cmb = (char*)obj + 0x508;
                float amt = ((ThunkF0)VTSLOT(cmb, 0x58))(cmb);
                ((cCombatant*)cmb)->FUN_00bfd1a0(amt);
                FUN_00c389f0(*(int*)(obj + 0x7f8));
            }
        }
        break;
    }

    default:
        break;
    }
}

// @ 0x00b5fde0
void cSuperPowersCommand::FUN_00b5fde0(int a)
{
    mSpec.Parse(a, mArguments);

    if (FUN_00b5b800() != 0x1654c05)
        return;

    void* sg = FUN_01002bd0(0, 1);
    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)FUN_01002bd0(0, 1);
    int inv = sim->FUN_00a1ad60();
    cPlayerInventory* pinv = (cPlayerInventory*)inv;
    (void)sg;

    int ok = ((Thunk1r)VTSLOT(pinv, 0x74))(pinv, (int)&DAT_01686b50);
    if ((char)ok == '\0') {
        FUN_00841000((void*)(int)mArguments,
                     "Advance further in the game before using this tool!\n");
        return;
    }

    char* m1 = (char*)FUN_00fd9c60();
    *(unsigned char*)(*(int*)(m1 + 0x188) + 0x48) = 0;
    char* m2 = (char*)FUN_00fd9c60();
    *(unsigned char*)(*(int*)(m2 + 0x188) + 0x49) = 0;

    int mm1 = (int)FUN_00feb9f0();
    ((cMissionManager*)mm1)->FUN_00feba60(1);
    int mm2 = (int)FUN_00feb9f0();
    ((cMissionManager*)mm2)->FUN_00feba80(1);

    int pm = (int)FUN_0067de30();
    int local = 0;
    ((Thunk3i)VTSLOT((void*)pm, 0x2c))((void*)pm, (int)0x59252ee9, (int)0x30608f0b, (int)&local);

    void* sg2 = FUN_01002bd0(0, 1);
    (void)sg2;
    int* ebp = 0;                 // unaff_EBP in the original; guarded like it
    int* ebx = 0;                 // unaff_EBX in the original
    if (ebp == 0)
        return;

    int has = ((Thunk1r)VTSLOT(ebp, 0x1c))(ebp, 0x68c20e1);
    if ((char)has != '\0') {
        int* apiStack = 0;
        ((Thunk1i)VTSLOT(ebp, 0x28))(ebp, 0x68c20e1);
        int count = FUN_00571ef0();
        int* p = (int*)FUN_00446ff0();
        for (int i = 0; i < count; i++) {
            int item = *p;
            int r = ((Thunk1r)VTSLOT(pinv, 0x74))(pinv, (int)&item);
            if ((char)r == '\0') {
                if (apiStack != 0) {
                    int* saved = apiStack;
                    apiStack = 0;
                    ((Thunk0)VTSLOT(saved, 8))(saved);
                }
                ((cPlayerInventory*)pinv)->FUN_0104e340((int*)&item, &apiStack);
                if (apiStack != 0)
                    ((Thunk2i)VTSLOT(pinv, 0x80))(pinv, (int)apiStack, 1);
            } else {
                FUN_00572620((void*)item);
                if ((char)FUN_0104cbc0() != '\0') {
                    FUN_0104cbd0(5);
                    void* ms = FUN_0067dcc0();
                    ((Thunk3i)VTSLOT(ms, 0x14))(ms, 0x635ae73, (int)apiStack, 0);
                }
            }
            p += 3;
        }
        if (apiStack != 0)
            ((Thunk0)VTSLOT(apiStack, 8))(apiStack);
        if (ebx != 0)
            ((Thunk0)VTSLOT(ebx, 4))(ebx);
    }
    if (ebp != 0)
        ((Thunk0)VTSLOT(ebp, 4))(ebp);
}

// Teardown context for the cSuperPowersCommand family object.
struct cCommandTeardown {
    void* mVtbl;                    // +0x00
    int   m04;                      // +0x04
    int   m08;                      // +0x08
    unsigned char mPad0C;           // +0x0c
    unsigned char mFlag0D;          // +0x0d
    unsigned char mPad0E[2];        // +0x0e
    int   mField10[3];              // +0x10 .. 0x1c
    void* mRef1C;                   // +0x1c
    int   mField20[5];              // +0x20 .. 0x34
    void* mHandler34;               // +0x34
    int   mH34a, mH34b, mH34c, mH34d;  // +0x38,0x3c,0x40,0x44
    void* mHandler48;               // +0x48
    int   mH48a, mH48b, mH48c, mH48d;  // +0x4c,0x50,0x54,0x58
    void** mVecBegin;               // +0x5c
    void** mVecEnd;                 // +0x60
    int FUN_00b5f1d0();             // 0x00b5f1d0
};

#define REL_SLOT(mgr, off, vtOff)                                            \
    do {                                                                     \
        void* p_ = *(void**)((char*)(mgr) + (off));                          \
        if (p_ != 0) {                                                       \
            void* vt_ = *(void**)((char*)p_ + (vtOff));                      \
            ((Thunk0)*(void**)((char*)vt_ + 0xc))(p_);                       \
            *(void**)((char*)(mgr) + (off)) = 0;                             \
        }                                                                    \
    } while (0)

#define REL_SLOTX(mgr, off, vtOff, slot)                                     \
    do {                                                                     \
        void* p_ = *(void**)((char*)(mgr) + (off));                          \
        if (p_ != 0) {                                                       \
            void* vt_ = *(void**)((char*)p_ + (vtOff));                      \
            ((Thunk0)*(void**)((char*)vt_ + (slot)))(p_);                    \
            *(void**)((char*)(mgr) + (off)) = 0;                             \
        }                                                                    \
    } while (0)

// @ 0x00b5f1d0
int cCommandTeardown::FUN_00b5f1d0()
{
    if (mHandler34 != 0) {
        int h = (int)mHandler34;
        mHandler34 = 0;
        FUN_00571db0(h, mH34a, mH34b, mH34c, mH34d);
    }
    if (mHandler48 != 0) {
        int h = (int)mHandler48;
        mHandler48 = 0;
        FUN_00571db0(h, mH48a, mH48b, mH48c, mH48d);
    }

    char* mgr = (char*)FUN_00b3d220();
    if (*(int*)mgr == 0)
        return 0;

    FUN_00b6d190();
    {
        void* ms = FUN_0067dcc0();
        ((Thunk3i)VTSLOT(ms, 0x2c))(ms, (int)this, 0x223f8c5, -9999);
        ms = FUN_0067dcc0();
        ((Thunk3i)VTSLOT(ms, 0x2c))(ms, (int)this, 0x472daaf, -9999);
        ms = FUN_0067dcc0();
        ((Thunk3i)VTSLOT(ms, 0x2c))(ms, 0, (int)this, 0x5b7e2ba);
    }

    mFlag0D = 0;
    FUN_00b7c810(0);
    FUN_00b2fbe0();

    if (mRef1C != 0) {
        FUN_00ea5380();
        void* p = mRef1C;
        if (p != 0) {
            mRef1C = 0;
            ((Thunk0)VTSLOT(p, 0xc))(p);
        }
    }

    REL_SLOT(mgr, 0x90, 4);
    REL_SLOT(mgr, 0x7c, 0);
    REL_SLOT(mgr, 0x3c, 4);
    REL_SLOT(mgr, 0x38, 4);
    REL_SLOT(mgr, 0x40, 0);
    REL_SLOT(mgr, 0x78, 0);
    REL_SLOT(mgr, 0x44, 0);
    REL_SLOTX(mgr, 0x10, 0xc, 0xc);
    REL_SLOT(mgr, 0x04, 8);
    REL_SLOT(mgr, 0x14, 4);
    REL_SLOT(mgr, 0x18, 4);
    REL_SLOT(mgr, 0x1c, 0);
    REL_SLOT(mgr, 0x28, 4);
    REL_SLOT(mgr, 0x2c, 0);
    REL_SLOT(mgr, 0x30, 0);
    REL_SLOT(mgr, 0x34, 4);
    REL_SLOT(mgr, 0x48, 0);
    REL_SLOT(mgr, 0x4c, 4);
    REL_SLOT(mgr, 0x70, 0);
    REL_SLOT(mgr, 0x50, 4);
    REL_SLOT(mgr, 0x54, 4);
    REL_SLOT(mgr, 0x58, 0);
    REL_SLOT(mgr, 0x80, 0);
    REL_SLOT(mgr, 0x84, 0);
    REL_SLOT(mgr, 0x5c, 0);
    REL_SLOT(mgr, 0x24, 0);
    REL_SLOT(mgr, 0x60, 0);
    REL_SLOT(mgr, 0x64, 4);
    REL_SLOT(mgr, 0x68, 8);
    REL_SLOT(mgr, 0x6c, 0);
    REL_SLOT(mgr, 0x74, 4);
    REL_SLOT(mgr, 0x20, 4);
    REL_SLOT(mgr, 0x8c, 4);
    REL_SLOT(mgr, 0x9c, 4);
    REL_SLOT(mgr, 0xa4, 0);
    REL_SLOT(mgr, 0xa0, 0);
    REL_SLOT(mgr, 0xa8, 0);
    REL_SLOT(mgr, 0xac, 0);

    FUN_00e25bd0(mVecBegin, mVecEnd);
    FUN_00b6e6d0();

    if (DAT_0168df68 != 0) {
        FUN_00c37370();
        if (DAT_0168df68 != 0)
            ((Thunk1i)VTSLOT(DAT_0168df68, 0))(DAT_0168df68, 1);
        DAT_0168df68 = 0;
    }

    {
        void* srt = FUN_010407c0();
        ((Thunk0)VTSLOT(srt, 0x0))(srt);
        ((Thunk0)VTSLOT(srt, 0x0))(srt);
        ((Thunk0)VTSLOT(srt, 0x0))(srt);
    }
    FUN_00c14530();
    FUN_00d1f3c0();
    FUN_00c9e530();
    FUN_00b5b730();
    *(int*)mgr = 0;
    return 1;
}

// @ 0x00b600a0
void __fastcall FUN_00b600a0(int* self)
{
    int a = self[6];
    int b = self[8];
    if (b - a > 1 && a != 0)
        EASTL_deallocate((void*)a);

    int* ref = (int*)self[5];
    if (ref != 0) {
        volatile long* cnt = (volatile long*)(ref + 2);
        long n;
        _InterlockedExchangeAdd(cnt, -1);
        if ((n = _InterlockedExchangeAdd(cnt, 0)) < 1)
            _InterlockedExchangeAdd(cnt, 1);
        else
            _InterlockedExchangeAdd(cnt, 0);
    }

    int* obj = (int*)self[4];
    if (obj != 0)
        ((Thunk0)VTSLOT(obj, 4))(obj);
    self[0] = 0x13ef094;
}