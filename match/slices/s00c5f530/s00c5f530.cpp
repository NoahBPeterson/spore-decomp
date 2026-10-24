// Slice s00c5f530: 0x00C5F530..0x00C60120.
//  0x00c5f530  SP::cSPMissionStory201::PickUFOWreckPlanet   (187 B)
//  0x00c5f5f0  FUN_00c5f5f0                                  ( 80 B)
//  0x00c5f640  SP::cSPMissionStory201::GetTagString          ( 72 B)
//  0x00c5f690  SP::cSPMissionStory201::GetUIShortDescription (212 B)
//  0x00c5f770  FUN_00c5f770                                  (1273 B)
//  0x00c5fcf0  FUN_00c5fcf0                                  (104 B)
//  0x00c5fd90  FUN_00c5fd90                                  (111 B)
//  0x00c5fe00  FUN_00c5fe00                                  (334 B)
//  0x00c5ff50  FUN_00c5ff50                                  (456 B)
//  0x00c60120  SP::cSPMissionStory201::OnArtifactScanned      (399 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

class wstring {
public:
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    void assign(const unsigned short* first, const unsigned short* last);  // 0x00423650
};

// Planet: has a vtable (slot +0xc0 is used), a +0x13c id/pointer and a name.
struct cPlanet {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0();   // +0xc0

    char    pad_04[0x13c - 0x04];
    void*   m13c;          // +0x13c

    wstring* GetName();        // 0x00c707e0
    int      FUN_00c70fb0();   // 0x00c70fb0
};

struct cSolarSystem {
    char      pad_00[0x10];
    cPlanet** m10;   // +0x10  begin
    cPlanet** m14;   // +0x14  end
};

struct cStar {
    cSolarSystem* GetSolarSystem();   // 0x00c8b770
};

struct cBioElemSort {
    cBioElemSort* SortBanners();      // 0x00b8de30
    void FUN_00bb9b00(int a, int b);  // 0x00bb9b00
    void FUN_00bb9c30();              // 0x00bb9c30
};

struct cStarManager {
    void GetOrActivatePlanet(void* id, cPlanet** out);   // 0x00bb59b0
};

struct cMissionMgr {
    void FUN_00feba80();   // 0x00feba80
};

// Game-data vector returned by cGameNounManager::GetGameDataVector.

struct cSub { int _; };
struct cNoun {
    char  pad_00[0x70];
    cSub  m070;                    // +0x70
    char  pad_74[0x228 - 0x74];
    int   m228;                    // +0x228
};

struct tVecData {
    int       m00;        // +0x00
    cNoun**   mItems[2];  // +0x04 begin, +0x08 end
};

struct cGameNounManager {
    tVecData* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
};

// ---------------------------------------------------------------- externs

void  FUN_00c46b80();      // 0x00c46b80
void* FUN_01021260();      // 0x01021260  (cSPLivingUniverse::GetActivePlanet)
void* FUN_01021230();      // 0x01021230
void* FUN_01021370();      // 0x01021370  (cSPLivingUniverse::GetPlayerHomePlanet)
void* StarManager();       // 0x00b3d2a0
void* NounManager();       // 0x00b3d300
void* GetCurrentGameMode();// 0x00b5b800
void* GetUniverseContext();// 0x01021080
cMissionMgr* __stdcall GetMissionManager(int id);   // 0x00feb9f0
void  TryGetUIntProperty(void* obj, unsigned id, unsigned* out);  // 0x00410370

// ---------------------------------------------------------------- base class

struct cSPMission {
    char pad_00[0x180];

    void     FUN_00c46b80();                            // 0x00c46b80
    bool     Init();                                    // 0x00c4ad50
    cPlanet* GetTargetPlanet();                         // 0x00970b30
    bool     GetTagString(unsigned tag, wstring* out);  // 0x00c491c0
    void     FUN_00c4a0c0();                            // 0x00c4a0c0
};

struct cSPMissionStory201 : cSPMission {
    void*    m180;   // +0x180
    char     pad_184[0x1f4 - 0x184];
    cPlanet* m1f4;   // +0x1f4
    unsigned m1f8;   // +0x1f8
    unsigned m1fc;   // +0x1fc

    bool PickUFOWreckPlanet();                          // 0x00c5f530
    void FUN_00c5f5f0();                                // 0x00c5f5f0
    bool GetTagString(unsigned tag, wstring* out);      // 0x00c5f640
    void GetUIShortDescription();                       // 0x00c5f690
    bool FUN_00c5f770();                                // 0x00c5f770
    bool FUN_00c5fcf0();                                // 0x00c5fcf0
    void FUN_00c5fe00();                                // 0x00c5fe00
    void FUN_00c5ff50();                                // 0x00c5ff50
    void OnArtifactScanned();                           // 0x00c60120
};

// ---------------------------------------------------------------- 0x00c5f530

// @ 0x00c5f530
bool cSPMissionStory201::PickUFOWreckPlanet()
{
    FUN_01021260();
    cStar* star = (cStar*)FUN_01021230();
    if (star == 0)
        return false;

    cSolarSystem* ss = star->GetSolarSystem();
    if (ss != 0) {
        int count = ss->m14 - ss->m10;
        for (int i = 0; i < count; i++) {
            cPlanet* p = ss->m10[i];
            if (p != 0) {
                void* a = p->m13c;
                if (a != FUN_01021370()) {
                    if (p->FUN_00c70fb0() > 0) {
                        cPlanet* old = m1f4;
                        if (old != 0) {
                            m1f4 = 0;
                            old->v0c0();
                        }
                        ((cStarManager*)StarManager())->GetOrActivatePlanet(p->m13c, &m1f4);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------- 0x00c5f5f0

// @ 0x00c5f5f0
void cSPMissionStory201::FUN_00c5f5f0()
{
    FUN_00c46b80();
    cBioElemSort* s;
    if (GetTargetPlanet())
        s = ((cBioElemSort*)GetTargetPlanet()->m13c)->SortBanners();
    else
        s = ((cBioElemSort*)0)->SortBanners();
    s->FUN_00bb9b00(0x40000, 0);
    s->FUN_00bb9c30();
    GetMissionManager(1)->FUN_00feba80();
}

// ---------------------------------------------------------------- 0x00c5f640

static bool TagNameHelper(cPlanet* planet, wstring* out)
{
    wstring* name = planet->GetName();
    if (name != out)
        out->assign(name->mpBegin, name->mpEnd);
    return true;
}

// @ 0x00c5f640
bool cSPMissionStory201::GetTagString(unsigned tag, wstring* out)
{
    if (tag == 0x7a216096)
        return TagNameHelper(m1f4, out);
    if (tag == 0xe3d3c424)
        return TagNameHelper(GetTargetPlanet(), out);
    return cSPMission::GetTagString(tag, out);
}

// ---------------------------------------------------------------- 0x00c5f690

// @ 0x00c5f690
void cSPMissionStory201::GetUIShortDescription() {}

// ---------------------------------------------------------------- 0x00c5f770

// @ 0x00c5f770
__declspec(noinline) bool cSPMissionStory201::FUN_00c5f770() { return GetUniverseContext() != 0; }

// ---------------------------------------------------------------- 0x00c5fcf0

// @ 0x00c5fcf0
bool cSPMissionStory201::FUN_00c5fcf0()
{
    if (!Init())
        return false;
    if (!PickUFOWreckPlanet())
        return false;
    if (!FUN_00c5f770())
        return false;
    FUN_00c4a0c0();
    if (m180 != 0) {
        TryGetUIntProperty(m180, 0x637cf275, &m1f8);
        TryGetUIntProperty(m180, 0x637cf276, &m1fc);
    }
    return true;
}

// ---------------------------------------------------------------- 0x00c5fd90

// @ 0x00c5fd90
void* FUN_00c5fd90()
{
    if (GetCurrentGameMode() == (void*)0x01654c05) {
        if (GetUniverseContext() == 0) {
            cGameNounManager* nm = (cGameNounManager*)NounManager();
            tVecData* v = nm->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                                (void*)0x00c5fc70, (void*)0x00b1e500,
                                                (void*)0x018c88e4);
            cNoun*** items = &v->mItems[0];
            cNoun** begin = items[0];
            cNoun** end = items[1];
            int n = end - begin;
            int i = 0;
            for (cNoun** q = begin; i < n; i++, q++) {
                cNoun* p = *q;
                if (p->m228 == 0x611a05f)
                    return &p->m070;
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00c5fe00

// @ 0x00c5fe00
void cSPMissionStory201::FUN_00c5fe00() {}

// ---------------------------------------------------------------- 0x00c5ff50

// @ 0x00c5ff50
void cSPMissionStory201::FUN_00c5ff50() {}

// ---------------------------------------------------------------- 0x00c60120

// @ 0x00c60120
void cSPMissionStory201::OnArtifactScanned() {}