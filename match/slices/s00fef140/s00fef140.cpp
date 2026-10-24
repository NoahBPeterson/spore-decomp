// Slice s00fef140 -- SPGonzago/SPSMission.obj (SP::cSPMissionManager +
// SP::cMissionRequisitesParser, plus the eastl sp_vector<0x38-element> helpers they use).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail layout differs,
// so members are declared at their retail offsets with named fields and padN gaps, and vtable
// slots are reached through stub interfaces that declare the slot at its index (VPad<N,B>).
//
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef int           s32;

// =============================================================================================
// vtable / container helpers
// =============================================================================================
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

struct IRefCount {
    virtual void AddRef();                               // +0x00 (slot 0)
    virtual void Release();                              // +0x04 (slot 1)
};

struct IHTTPRequest {
    virtual void FUN_00(int);                            // +0x00 (slot 0)
};

// =============================================================================================
// external retail callees (cdecl / stdcall)
// =============================================================================================
struct cReqElem;
struct cReqVec;
void* __cdecl FUN_00fef670();
void  __cdecl FUN_00fef6b0();
void  __cdecl FUN_00fef9f0(u32, void*);
void* __cdecl FUN_00fef810(cReqElem*, cReqElem*, cReqElem*);
cReqElem* __cdecl FUN_00fef6d0(cReqElem*, cReqElem*, cReqElem*);

extern "C" {
void* __cdecl FUN_01021300();                            // cSPLivingUniverse::GetPlayerEmpire
void* __cdecl FUN_00b3d300();                            // SP::NounManager
void* __cdecl FUN_00b3d4a0();                            // SP::CommManager
void* __cdecl FUN_01021260();                            // cSPLivingUniverse::GetActivePlanet
void* __cdecl FUN_010212a0();                            // ...GetActivePlanetRecord
void* __cdecl FUN_01021370();                            // ...GetPlayerHomePlanet
void* __cdecl FUN_00b3d3e0(u32, u32, u32, u32, u32, u32); // SP::EventLog
void* __cdecl FUN_00b3d350();                            // SP::PlanetModel
void* __cdecl FUN_00b3d260();                            // SP::BehaviorManager
void* __cdecl FUN_00b3d480();
void* __cdecl FUN_00b3d2a0(void*, int);                  // SP::StarManager
void* __cdecl FUN_0067dcd0();                            // ::EA::ResourceMan::GetManager
void* __cdecl FUN_00bba790();
void* __cdecl FUN_00c099e0(void*, void*, int, void*, int, int);
void  __cdecl FUN_00b81780(void*, void*, void*);
u32   __cdecl FUN_00a68fb0(u32);                         // EA::Random::RandomUint32Uniform
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);
void  __cdecl operator_delete_array(void*);
void* __cdecl memcpy(void*, const void*, unsigned);
void* __cdecl FUN_00b8de30();
void* __cdecl FUN_00401090(void*, void*);
void* __cdecl FUN_00c8b450(u32);                         // IsGasStarType
void* __cdecl FUN_00c8b520(u32);
void* __cdecl FUN_00b3d330();                            // SP::SimTicker
void* __cdecl FUN_01075500();
void* __cdecl FUN_00cd7d10();
void* __cdecl FUN_00d3d420();
void* __cdecl FUN_00fed010();
void* __cdecl FUN_00b1e520();
void* __cdecl FUN_00fef7d0(cReqElem*, cReqElem*, cReqElem*);
void* __cdecl FUN_00fee2b0(void*, void*, void*);
u8    __cdecl FUN_00fefcd0(u32, void**, u8*, u8*);
void* __cdecl FUN_00c6acc0(int, float);
void* __cdecl FUN_00681a10(void*);
void* __cdecl FUN_00c03170(u32);
void* __cdecl FUN_00c1d430(u32);
void* __cdecl FUN_00acd2d0(void*);
u32   __cdecl FUN_00bb9ae0();
}

// =============================================================================================
// globals
// =============================================================================================
IHTTPRequest* g_16dacb8;                                 // 0x016dacb8  HTTPRequest singleton
void*         g_16dac64;                                 // 0x016dac64

// =============================================================================================
// sp_vector<float, sp_vector_allocator> -- 0x14 bytes
// =============================================================================================
struct spVecF {
    float* mpBegin;                                      // +0x00
    float* mpEnd;                                        // +0x04
    u32    mCap;                                         // +0x08
    u32    mAlloc;                                       // +0x0c
    u32    mExtra;                                       // +0x10

    void* FUN_004aa350(int count, u32* alloc);           // 0x004aa350 (ret 8)  allocate
    void  FUN_0050d4e0(spVecF* src);                     // 0x0050d4e0 (ret 4)  operator=
    void  FUN_00fecc40(void* a, void* b);                // 0x00fecc40 (ret 8)
    void* FUN_00fef570(void* a, void* b);                // 0x00fef570 (ret 8)  our target
};

// =============================================================================================
// cReqElem -- one requisites element, 0x38 bytes
// =============================================================================================
struct cReqElem {
    u32    mField_00;                                    // +0x00
    u32    mField_04;                                    // +0x04
    spVecF mVec_08;                                      // +0x08
    spVecF mVec_1c;                                      // +0x1c
    u32    mField_30;                                    // +0x30
    u32    mField_34;                                    // +0x34

    cReqElem* FUN_00fef730(cReqElem* src);               // 0x00fef730 (ret 4)  copy-construct
};

// =============================================================================================
// cReqVec -- vector<cReqElem>
// =============================================================================================
struct cReqVec {
    cReqElem* mpBegin;                                   // +0x00
    cReqElem* mpEnd;                                     // +0x04
    cReqElem* mpCap;                                     // +0x08

    void FUN_00fef870(cReqElem* pos, cReqElem* val);     // 0x00fef870 (ret 8)
};

// =============================================================================================
// cSPMission virtual table (only the slots this slice calls are named)
// =============================================================================================
struct IVM00 : VPad<3, IEmpty>  { virtual void* FUN_0c(u32); };              // +0x0c
struct IVM01 : VPad<7, IVM00>   { virtual bool  FUN_2c(); };                  // +0x2c
struct IVM02 : VPad<9, IVM01>   { virtual void  FUN_54(); };                  // +0x54
struct IVM03 : VPad<2, IVM02>   { virtual int   FUN_60(); };                  // +0x60
struct IVM04 : VPad<6, IVM03>   { virtual int   FUN_7c(void*); };             // +0x7c
struct IVM05 : VPad<2, IVM04>   { virtual void  FUN_88(); };                  // +0x88
struct IVM06 : IVM05            { virtual void  FUN_8c(); };                   // +0x8c
struct IVM07 : IVM06            { virtual void  FUN_90(); };                   // +0x90
struct IVM08 : IVM07            { virtual void  FUN_94(); };                   // +0x94
struct IVM09 : IVM08            { virtual void  FUN_98(); };                   // +0x98
struct IVM10 : VPad<2, IVM09>   { virtual void* FUN_a4(void*, void*, void*, void*); }; // +0xa4

struct IBehaviorMgr : VPad<14, IEmpty> { virtual void FUN_38(void*); };       // +0x38 (slot 14)

struct cSourcePlanet;
struct cSPMission : IVM10 {
    u8  pad004[0x130 - 0x04];
    u32 mField_130;                                      // +0x130
    u8  pad134[0x17c - 0x134];
    u32 mField_17c;                                      // +0x17c

    cSourcePlanet* GetSourcePlanet();                    // 0x00c45ce0 (ret 0)
    void           SetState(int);                        // 0x00c47cc0 (ret 4)
    u32            GetMissionID();                       // 0x01030e10 (ret 0)
};

struct cSourcePlanet {
    u8  pad000[0x13c];
    u32 mField_13c;                                      // +0x13c
};

// =============================================================================================
// other retail objects
// =============================================================================================
struct cEmpire {
    u8  pad000[0x84];
    void* mpField_84;                                    // +0x84

    void* GetHomePlanet();                               // 0x00c31730
};

struct cGameNounManager {
    void* GetGameDataVector(void*, void*, void*, void*, u32);  // 0x00b21340 (ret 0x14)
    void  RemoveNounsWithInterface(u32);                       // 0x00b227c0 (ret 4)
};

struct cMissionVec {                                     // vector<cSPMission*> result view
    u8            pad00[4];
    cSPMission**  mpBegin;                               // +0x04
    cSPMission**  mpEnd;                                 // +0x08
};

struct cStarRecordRef {
    void* GetCommContext(u32, int, u32);                 // 0x00ce6950 (ret 0x0c)
};

struct cCommScreen {
    void* FindEntry(void*, void*);                       // 0x00ae93f0 (ret 8)
    void  RemoveMatching(void*, void*);                  // 0x00aea720 (ret 8)
    void  FUN_00aeb7a0(void*, void*);                    // 0x00aeb7a0 (ret 8)
    bool  IsActive();                                    // 0x00ae9390
};

struct cSerializerUser {
    void SetSerializer();                                // 0x00c2e4e0
};

struct cSimTicker : VPad<21, IEmpty> {
    virtual void FUN_54(void*);                          // +0x54 (slot 21)
};

struct cFeedHelper {                                     // g_16dac64
    void* FUN_00feed30(void*, void*);                    // 0x00feed30 (ret 8)
};

struct cSpaceGame {                                      // SpaceGameGet() result
    bool FUN_01075500();                                 // 0x01075500
};

struct cBioFunctor {                                     // FUN_00fefe90 argument
    void* FUN_00b8de30();                                // 0x00b8de30
};

struct cSpeciesMgr {
    void* FUN_004e0050();                                // 0x004e0050 (GetSpeciesArchetype)
};

struct IVt0 { virtual void slot0(); virtual void slot1(); };  // refcounted object vtable

struct cNearNoun {
    void* GetPosition(float, float);                     // 0x00c6acc0
};

// =============================================================================================
// cSPMissionManager (retail layout)
// =============================================================================================
struct cSPMissionManager {
    u8    pad000[0x16];
    u8    mFlag_16;                                      // +0x16
    u8    pad017[0x20 - 0x17];
    spVecF mReq_20;                                      // +0x20  mTutorialMissionReqList
    spVecF mReq_34;                                      // +0x34  mNPCMissionReqList
    spVecF mReq_48;                                      // +0x48  mColonyMissionReqList
    u8    pad5c[0xc0 - 0x5c];
    void* mpField_c0;                                    // +0xc0  refcounted
    void* mpField_c4;                                    // +0xc4  refcounted

    void  CleanupArchive(void*);                         // 0x00fef140 (ret 4)
    void  OnTick(void*);                                 // 0x00fef3b0 (ret 8)
    void  ShutdownForGame();                             // 0x00fef5d0

    bool  FUN_00fee930(u32);                             // 0x00fee930 (ret 4)
    int   GetNextAvailableTutorialMission();             // 0x00feea60
    void  FUN_00fec4e0();                                // 0x00fec4e0
    void  FUN_00fec430(void*);                           // 0x00fec430 (ret 4)
    void  FUN_00fedca0(cSPMission*);                     // 0x00fedca0 (ret 4)
};

// =============================================================================================
// 00fef140  SP::cSPMissionManager::CleanupArchive
// =============================================================================================
// @ 0x00fef140  SP::cSPMissionManager::CleanupArchive
void cSPMissionManager::CleanupArchive(void* param2) {
    cEmpire* empire = (cEmpire*)FUN_01021300();
    if (empire == 0)
        return;
    void* homePlanet = empire->GetHomePlanet();
    if (homePlanet == 0)
        return;
    void* hp = empire->GetHomePlanet();

    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    cMissionVec* v = (cMissionVec*)nm->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00fed010, FUN_00b1e520, 0x2aa5ada);
    cSPMission** hi = v->mpEnd;
    for (cSPMission** it = v->mpBegin; it != hi; ++it) {
        cSPMission* m = *it;
        if (((m->mField_130 >> 3) & 1) != 0 && m->FUN_60() == 3
            && m->GetSourcePlanet()->mField_13c == (u32)hp)
            return;
    }

    void* stars = *(void**)((u8*)empire + 0x84);
    cStarRecordRef* rec = (cStarRecordRef*)hp;
    void* ctx = rec->GetCommContext(0x8b756f4b, -1, 0);
    cCommScreen* cs = (cCommScreen*)FUN_00b3d4a0();
    void* entry = cs->FindEntry(stars, ctx);
    if (entry != 0 && *(void**)((u8*)entry + 0x40) != 0) {
        u32 id = ((cSPMission*)*(void**)((u8*)entry + 0x40))->GetMissionID();
        if (FUN_00fee930(id)) {
            void* obj = *(void**)((u8*)entry + 0x40);
            void* stars2 = *(void**)((u8*)empire + 0x84);
            void* ctx2 = rec->GetCommContext(0x8b756f4b, -1, 0);
            cCommScreen* cs2 = (cCommScreen*)FUN_00b3d4a0();
            cs2->RemoveMatching(stars2, ctx2);
        }
    }

    void* stars3 = *(void**)((u8*)empire + 0x84);
    void* ctx3 = rec->GetCommContext(0x8b756f4b, -1, 0);
    cCommScreen* cs3 = (cCommScreen*)FUN_00b3d4a0();
    if (cs3->FindEntry(stars3, ctx3) != 0)
        return;

    if (GetNextAvailableTutorialMission() == -1)
        return;

    if (mFlag_16 != 0) {
        cFeedHelper* fh = (cFeedHelper*)g_16dac64;
        void* obj = fh->FUN_00feed30(empire, hp);
        if (obj != 0) {
            void* r = ((IVM10*)obj)->FUN_a4((void*)0x8b756f4b, obj, 0, 0);
            void* stars4 = *(void**)((u8*)empire + 0x84);
            void* ctx4 = rec->GetCommContext(0x8b756f4b, -1, 0);
            cCommScreen* cs4 = (cCommScreen*)FUN_00b3d4a0();
            cs4->FUN_00aeb7a0(stars4, ctx4);
        }
        mFlag_16 = 0;
        return;
    }

    cCommScreen* cs5 = (cCommScreen*)FUN_00b3d4a0();
    if (!cs5->IsActive()) {
        cSpaceGame* sg = (cSpaceGame*)FUN_01075500();
        if (!sg->FUN_01075500())
            goto LAB_32a;
    }
    {
        void* ap = FUN_01021260();
        void* a1 = ((cStarRecordRef*)*(void**)((u8*)ap + 0x13c))->GetCommContext(0, 0, 0);
        void* a2 = rec->GetCommContext(0, 0, 0);
        if (a2 == a1)
            return;
    }
LAB_32a:
    {
        cFeedHelper* fh = (cFeedHelper*)g_16dac64;
        void* obj = fh->FUN_00feed30(empire, hp);
        if (obj != 0) {
            ((IVM10*)obj)->FUN_a4((void*)0x8b756f4b, obj, 0, 0);
            void* stars6 = *(void**)((u8*)empire + 0x84);
            void* ctx6 = rec->GetCommContext(0x8b756f4b, -1, 0);
            cCommScreen* cs6 = (cCommScreen*)FUN_00b3d4a0();
            cs6->FUN_00aeb7a0(stars6, ctx6);
        }
    }
    {
        void* a = FUN_010212a0();
        void* b = FUN_01021370();
        if (a != b) {
            cSerializerUser* u =
                (cSerializerUser*)FUN_00b3d3e0(0xe737105a, 0x131a9f54, 0, 0, 1, 0);
            u->SetSerializer();
        }
    }
}

// =============================================================================================
// 00fef3b0  SP::cSPMissionManager::OnTick
// =============================================================================================
// @ 0x00fef3b0  SP::cSPMissionManager::OnTick
void cSPMissionManager::OnTick(void* param2) {
    cGameNounManager* nm = (cGameNounManager*)FUN_00b3d300();
    cMissionVec* v = (cMissionVec*)nm->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00fed010, FUN_00b1e520, 0x2aa5ada);
    cSPMission** hi = v->mpEnd;
    for (cSPMission** it = v->mpBegin; it != hi; ++it) {
        cSPMission* m = *it;
        if (m == 0)
            continue;
        if (m->FUN_2c())
            continue;
        if (m->FUN_60() == 10)
            continue;
        int prev = m->FUN_60();
        do {
            switch (m->FUN_60()) {
            case 1:
                FUN_00fedca0(m);
                break;
            case 2:
                m->FUN_88();
                m->SetState(3);
                break;
            case 3: {
                int r = m->FUN_7c(param2);
                if (r != 3)
                    m->SetState(r);
            } break;
            case 4:
                break;
            case 5:
                m->FUN_94();
                if (m->mField_17c != 0)
                    m->SetState(9);
                else
                    m->SetState(1);
                break;
            case 6:
                m->FUN_98();
                m->SetState(1);
                break;
            case 7:
                m->FUN_90();
                m->SetState(1);
                break;
            case 8:
                m->FUN_8c();
                m->SetState(1);
                break;
            }
        } while (prev != m->FUN_60());
    }
    CleanupArchive(param2);
    FUN_00fec4e0();
    FUN_00fec430(param2);
}

// =============================================================================================
// 00fef570  spVecF::FUN_00fef570 -- erase [a,b) rotation helper
// =============================================================================================
// @ 0x00fef570  spVecF::FUN_00fef570
void* spVecF::FUN_00fef570(void* a, void* b) {
    void* mid = FUN_00fee2b0(b, mpEnd, a);
    FUN_00fecc40(mid, mpEnd);
    int count = (int)((char*)b - (char*)a) / -0x38;
    mpEnd = (float*)((char*)mpEnd + count * 0x38);
    return a;
}

// =============================================================================================
// 00fef5d0  SP::cSPMissionManager::ShutdownForGame
// =============================================================================================
// @ 0x00fef5d0  SP::cSPMissionManager::ShutdownForGame
void cSPMissionManager::ShutdownForGame() {
    cSimTicker* t = (cSimTicker*)FUN_00b3d330();
    t->FUN_54(this);
    ((cSerializerUser*)FUN_00fef670())->SetSerializer();
    FUN_00fef6b0();
    mReq_20.FUN_00fef570(mReq_20.mpBegin, mReq_20.mpEnd);
    mReq_34.FUN_00fef570(mReq_34.mpBegin, mReq_34.mpEnd);
    mReq_48.FUN_00fef570(mReq_48.mpBegin, mReq_48.mpEnd);
    ((cGameNounManager*)FUN_00b3d300())->RemoveNounsWithInterface(0x2aa5ada);
    if (mpField_c0 != 0) {
        void* p = mpField_c0;
        mpField_c0 = 0;
        ((IRefCount*)p)->Release();
    }
    if (mpField_c4 != 0) {
        void* p = mpField_c4;
        mpField_c4 = 0;
        ((IRefCount*)p)->Release();
    }
}

// =============================================================================================
// 00fef670  HTTPRequest singleton get-or-create
// =============================================================================================
// @ 0x00fef670  FUN_00fef670
void* FUN_00fef670() {
    if (g_16dacb8 == 0) {
        void* p = operator_new(4, "Simulator", 0, 0, 0, 0);
        if (p != 0) {
            *(u32*)p = 0x13fb19c;                        // vtbl_UTFInternet::HTTPRequest
            g_16dacb8 = (IHTTPRequest*)p;
            return p;
        }
        g_16dacb8 = 0;
    }
    return g_16dacb8;
}

// =============================================================================================
// 00fef6b0  HTTPRequest singleton release
// =============================================================================================
// @ 0x00fef6b0  FUN_00fef6b0
void FUN_00fef6b0() {
    if (g_16dacb8 != 0)
        g_16dacb8->FUN_00(1);
    g_16dacb8 = 0;
}

// =============================================================================================
// 00fef6d0  destroy a [a,b) range of cReqElem
// =============================================================================================
// @ 0x00fef6d0  FUN_00fef6d0
cReqElem* FUN_00fef6d0(cReqElem* a, cReqElem* b, cReqElem* d) {
    while (a != b) {
        float* p = a->mVec_1c.mpBegin;
        if (p != 0 && *(int*)((u8*)p - 4) != 0)
            operator_delete_array(p);
        p = a->mVec_08.mpBegin;
        if (p != 0 && *(int*)((u8*)p - 4) != 0)
            operator_delete_array(p);
        a = (cReqElem*)((u8*)a + 0x38);
        d = (cReqElem*)((u8*)d + 0x38);
    }
    return d;
}

// =============================================================================================
// 00fef730  cReqElem::FUN_00fef730 -- copy-construct one element
// =============================================================================================
// @ 0x00fef730  cReqElem::FUN_00fef730
cReqElem* cReqElem::FUN_00fef730(cReqElem* src) {
    mField_00 = src->mField_00;
    mField_04 = src->mField_04;

    spVecF* v = &mVec_08;
    int count = src->mVec_08.mpEnd - src->mVec_08.mpBegin;
    v->FUN_004aa350(count, &src->mVec_08.mAlloc);
    int bytes = (int)((char*)src->mVec_08.mpEnd - (char*)src->mVec_08.mpBegin);
    v->mpEnd = (float*)((char*)memcpy(v->mpBegin, src->mVec_08.mpBegin, bytes) + (bytes >> 2) * 4);

    spVecF* w = &mVec_1c;
    int count2 = src->mVec_1c.mpEnd - src->mVec_1c.mpBegin;
    w->FUN_004aa350(count2, &src->mVec_1c.mAlloc);
    int bytes2 = (int)((char*)src->mVec_1c.mpEnd - (char*)src->mVec_1c.mpBegin);
    w->mpEnd = (float*)((char*)memcpy(w->mpBegin, src->mVec_1c.mpBegin, bytes2) + (bytes2 >> 2) * 4);

    mField_30 = src->mField_30;
    mField_34 = src->mField_34;
    return this;
}

// =============================================================================================
// 00fef810  copy-assign a range backwards
// =============================================================================================
// @ 0x00fef810  FUN_00fef810
void* FUN_00fef810(cReqElem* a, cReqElem* b, cReqElem* d) {
    while (b != a) {
        b = (cReqElem*)((u8*)b - 0x38);
        d = (cReqElem*)((u8*)d - 0x38);
        d->mField_00 = b->mField_00;
        d->mField_04 = b->mField_04;
        d->mVec_08.FUN_0050d4e0(&b->mVec_08);
        d->mVec_1c.FUN_0050d4e0(&b->mVec_1c);
        d->mField_30 = b->mField_30;
        d->mField_34 = b->mField_34;
    }
    return d;
}

// =============================================================================================
// 00fef870  cReqVec::FUN_00fef870 -- insert `val` at `pos`
// =============================================================================================
// @ 0x00fef870  cReqVec::FUN_00fef870
void cReqVec::FUN_00fef870(cReqElem* pos, cReqElem* val) {
    cReqElem* end = mpEnd;
    if (end != mpCap) {
        if (pos <= val && val < end)
            val = (cReqElem*)((u8*)val + 0x38);
        if (end != 0)
            end->FUN_00fef730((cReqElem*)((u8*)end - 0x38));
        FUN_00fef810(pos, (cReqElem*)((u8*)mpEnd - 0x38), mpEnd);
        pos->mField_00 = val->mField_00;
        pos->mField_04 = val->mField_04;
        pos->mVec_08.FUN_0050d4e0(&val->mVec_08);
        pos->mVec_1c.FUN_0050d4e0(&val->mVec_1c);
        pos->mField_30 = val->mField_30;
        pos->mField_34 = val->mField_34;
        mpEnd = (cReqElem*)((u8*)mpEnd + 0x38);
        return;
    }

    int cnt = (int)(((char*)end - (char*)mpBegin) / 0x38);
    int cap;
    cReqElem* buf;
    if (cnt == 0) {
        cap = 1;
    } else {
        cap = cnt * 2;
        if (cap == 0) {
            buf = 0;
            goto LAB;
        }
    }
    buf = (cReqElem*)operator_new(cap * 0x38, "Simulator", 0, 0,
                                 (const char*)0x13ebb38, 0xd1);
LAB:;
    cReqElem* old = mpBegin;
    cReqElem* r1 = (cReqElem*)FUN_00fef7d0(old, pos, buf);
    FUN_00fef6d0(old, pos, buf);
    if (r1 != 0)
        r1->FUN_00fef730(val);
    cReqElem* oldEnd = mpEnd;
    cReqElem* r2 = (cReqElem*)FUN_00fef7d0(pos, oldEnd, (cReqElem*)((u8*)r1 + 0x38));
    FUN_00fef6d0(pos, oldEnd, (cReqElem*)((u8*)r1 + 0x38));
    if (old != 0 && *(int*)((u8*)old - 4) != 0)
        operator_delete_array(old);
    mpEnd = r2;
    mpBegin = buf;
    mpCap = (cReqElem*)((u8*)buf + cap * 0x38);
}

// =============================================================================================
// 00fef9f0  SP::cMissionRequisitesParser::FillList
// =============================================================================================
struct IResMan : VPad<3, IEmpty> {
    virtual char FUN_0c(u32*, u32*, int, int, int, int); // +0x0c
};
struct cReqHolder {                                      // vector<cReqElem>
    cReqElem* mpBegin;                                   // +0x00
    cReqElem* mpEnd;                                     // +0x04
    cReqElem* mpCap;                                     // +0x08
};
struct cReqSource {
    u8  pad00[0x6c];
    u8* mpBegin;                                         // +0x6c
    u8* mpEnd;                                           // +0x70
};
struct cReqBuildBlock {                                  // 0x60-byte source item
    u8 pad00[0x60];
};

// @ 0x00fef9f0  SP::cMissionRequisitesParser::FillList
void FUN_00fef9f0(u32 param1, void* param2v) {
    cReqHolder* dst = (cReqHolder*)param2v;
    u32 local_a8 = 0;
    u32 local_a4 = param1;
    u32 local_a0 = 0x55ada24;
    u32 local_9c = 0x2ae1a8e;
    spVecF* vec = (spVecF*)dst;
    vec->FUN_00fef570(vec->mpBegin, vec->mpEnd);
    (void)local_a0; (void)local_9c;

    IResMan* mgr = (IResMan*)FUN_0067dcd0();
    cReqSource* src = 0;
    char ok = mgr->FUN_0c(&local_a4, &local_a8, 0, 0, 0, 0);
    if (ok != 0) {
        u8* it = src->mpBegin;
        u8* end = src->mpEnd;
        while (it != end) {
            FUN_00681a10(&local_a4);
            it += 0x60;
        }
    }
    (void)local_a8;
}

// =============================================================================================
// 00fefbb0  SP::AddInfectedAnimalsToHerd
// =============================================================================================
// @ 0x00fefbb0  SP::AddInfectedAnimalsToHerd
void FUN_00fefbb0(void* param1, void* param2, int count, u32 param4, u32 param5) {
    void* u1 = FUN_00b3d480();
    void* planet = FUN_00b3d350();
    void* nm = FUN_00b3d300();
    (void)u1; (void)nm;
    if (count > 0) {
        int n = count;
        do {
            float pos[3];
            void* ret = ((cNearNoun*)param2)->GetPosition(0.0f, 10.0f);
            FUN_00b81780(planet, pos, ret);
            u32 r = FUN_00a68fb0(10);
            void* o = FUN_00c099e0(pos, param1, r >= 2 ? 1 : 0, param2, 0, 1);
            if (o != 0) {
                FUN_00c03170(param4);
                *(u8*)((u8*)o + 0xb62) = 1;
                FUN_00c1d430(param5);
                FUN_00acd2d0(o);
                void* bm = FUN_00b3d260();
                void* g = ((IVM00*)o)->FUN_0c(0x11c0ba3);
                ((IBehaviorMgr*)bm)->FUN_38(g);
                u8* g2 = (u8*)((IVM00*)o)->FUN_0c(0x116dd1b);
                if (g2 != 0) {
                    g2[0x71] = 0;
                    g2[0x75] = 1;
                }
                ((IVM02*)o)->FUN_54();
            }
        } while (--n != 0);
    }
}

// =============================================================================================
// 00fefcd0  UFO / gas-star mission helper
// =============================================================================================
// @ 0x00fefcd0  FUN_00fefcd0
__declspec(noinline) u8 FUN_00fefcd0(u32 param1, void** param2, u8* param3, u8* param4) {
    if (param3 != 0)
        *param3 = 0;
    if (param4 != 0)
        *param4 = 0;

    void* u = FUN_00b8de30();
    (void)u;
    char g = (char)(u32)FUN_00c8b450(param1);
    if (g == 0)
        return 0;
    char s = (char)(u32)FUN_00c8b520(param1);
    if (s == 0)
        return 0;
    int i = (int)(u32)FUN_00bb9ae0();
    if (i >= 2)
        return 0;
    return 0;
}

// =============================================================================================
// 00fefe70  FUN_00fefe70
// =============================================================================================
// @ 0x00fefe70  FUN_00fefe70
void FUN_00fefe70(u32 param1) {
    FUN_00fefcd0(param1, 0, 0, 0);
}

// =============================================================================================
// 00fefe90  FUN_00fefe90
// =============================================================================================
// @ 0x00fefe90  FUN_00fefe90
void FUN_00fefe90(u32 param1, u32 param2, u32 param3) {
    u32 buf[1];
    void* r = ((cBioFunctor*)param1)->FUN_00b8de30();
    buf[0] = param1;
    FUN_00fefcd0((u32)r, (void**)buf, (u8*)param2, (u8*)param3);
}

// =============================================================================================
// 00fefec0  FUN_00fefec0 -- remove-invalid pass
// =============================================================================================
// @ 0x00fefec0  FUN_00fefec0
void FUN_00fefec0(void** vec) {
    u32 i = 0;
    while (i < (u32)((int)((u8*)vec[1] - (u8*)vec[0]) >> 2)) {
        u32 off = i * 4;
        u8* el = *(u8**)((u8*)vec[0] + off);
        void* s = FUN_00401090(*(void**)(el + 0x88), *(void**)(el + 0xf0));
        void* sp = ((cSpeciesMgr*)s)->FUN_004e0050();
        if (sp == 0 || *(u8*)((u8*)sp + 0x388) == 0) {
            ++i;
        } else {
            u8* base = (u8*)vec[0];
            IVt0* cur = *(IVt0**)(base + off);
            IVt0* last = *(IVt0**)((u8*)vec[1] - 4);
            if (last != cur) {
                if (last != 0)
                    last->slot0();
                *(IVt0**)(base + off) = last;
                if (cur != 0)
                    cur->slot1();
            }
            vec[1] = (void*)((u8*)vec[1] - 4);
            IVt0* e2 = *(IVt0**)vec[1];
            if (e2 != 0)
                e2->slot1();
        }
    }
}