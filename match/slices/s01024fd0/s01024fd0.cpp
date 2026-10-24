// Slice s01024fd0: eastl::vector helpers over a 0x1c-byte element plus a space-cheat command.
//
// Classification
//   01025750  byte-exact   (eastl::vector<eastl::set<int> >::resize)
//   01024fd0  nonmatching  (eastl::vector<eastl::set<int> >::DoInsertValues)
//   010255f0  nonmatching  (eastl::vector<byte[0x14]>::DoInsertValue)
//   010251e0  nonmatching  (SP::nSpaceCheats::cCommandRaidCheat::Execute)
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc: retail has no EH frames)
typedef unsigned int  u32;
typedef unsigned char u8;

inline void* operator new(unsigned, void* p) { return p; }

extern "C" {
void* memcpy(void*, const void*, unsigned);
}

// ---------------------------------------------------------------------------
// Shared: eastl::set<int> (0x1c bytes) and the rbtree anchor it embeds.
// ---------------------------------------------------------------------------
struct RBNodeBase {
    RBNodeBase* mpNodeRight;
    RBNodeBase* mpNodeLeft;
    RBNodeBase* mpNodeParent;
    char        mColor;
};

struct SetInt {                                  // eastl::set<int>  (0x1c)
    int          mCompare;                       // +0x00 eastl::less<int>
    RBNodeBase   mAnchor;                        // +0x04
    u32          mnSize;                         // +0x14
    u32          mAllocator;                     // +0x18
    void DoNukeSubtree(RBNodeBase* p);           // 0x9a9600
    SetInt() : mAnchor()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    ~SetInt() { DoNukeSubtree(mAnchor.mpNodeParent); }
};

// Generic algorithms instantiated for SetInt (all external).
void CopyConstruct(SetInt* to, const SetInt* from);          // 0x7d0ac0  (thiscall)
void UninitCopyFill(SetInt* p, u32 n, const SetInt& v);      // 0x10249c0
void AssignRange(SetInt* first, SetInt* last, SetInt* dest); // 0x1023180
SetInt* UninitMove(SetInt* first, SetInt* last, SetInt* dest);// 0x1023230
void CopyRange(SetInt* first, SetInt* last, SetInt* dest);   // 0x10233e0
SetInt* CopyBackward(SetInt* first, SetInt* last, SetInt* dest); // 0x1023460
void FillRange(SetInt* first, SetInt* last, const SetInt& v);// 0x1024e60
void* DoAlloc28(u32 n, const char*, int, int, const char*, int); // 0xf473a0
void  DoFree28(void* p);                                     // 0xf47380

inline SetInt* AllocSetInt(u32 n)
{
    return n ? (SetInt*)DoAlloc28(n * 0x1c, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
             : 0;
}

struct VecSet {                                  // eastl::vector<eastl::set<int> >
    SetInt* mpBegin;
    SetInt* mpEnd;
    SetInt* mpCapacity;
    void DoFillInsert(SetInt* position, u32 n, const SetInt& value);   // 0x1024fd0
    void erase(SetInt* first, SetInt* last);                           // 0x1024f70 (external)
    void resize(u32 n);                                                // 0x1025750
};

// @ 0x01024fd0
void VecSet::DoFillInsert(SetInt* position, u32 n, const SetInt& value)
{
    SetInt* const destPosition = position;

    if (n <= (u32)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const SetInt temp = value;                    // 0x7d0ac0
            const u32 nExtra = (u32)(mpEnd - destPosition);
            if (n < nExtra) {
                CopyRange(mpEnd - n, mpEnd, mpEnd);        // 0x10233e0
                CopyBackward(destPosition, mpEnd - n, mpEnd); // 0x1023460
                FillRange(destPosition, destPosition + n, temp); // 0x1024e60
            } else {
                UninitCopyFill(mpEnd, n - nExtra, temp);   // 0x10249c0
                CopyRange(destPosition, mpEnd, mpEnd + n - nExtra); // 0x10233e0
                FillRange(destPosition, mpEnd, temp);      // 0x1024e60
            }
            mpEnd += n;
        }
    } else {
        const u32 nPrevSize = (u32)(mpEnd - mpBegin);
        const u32 nGrowSize = nPrevSize ? (2 * nPrevSize) : 1;
        const u32 nNewSize  = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        SetInt* const pNewData = AllocSetInt(nNewSize);
        SetInt* pNewEnd = UninitMove(mpBegin, destPosition, pNewData);   // 0x1023230
        AssignRange(mpBegin, destPosition, pNewData);                    // 0x1023180
        UninitCopyFill(pNewEnd, n, value);                               // 0x10249c0
        pNewEnd = UninitMove(destPosition, mpEnd, pNewEnd + n);          // 0x1023230
        AssignRange(destPosition, mpEnd, pNewEnd);                       // 0x1023180
        if (mpBegin && ((int*)mpBegin)[-1])
            DoFree28(mpBegin);
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// SP::nSpaceCheats::cCommandRaidCheat::Execute
// ---------------------------------------------------------------------------
struct cArguments {
    void** OptionArguments(const char* name, int* out, int a, int b); // 0x838130
    int    NumArguments();                                            // 0x837f30
    char   HasFlag(const char* name);                                 // 0x8380b0
};

template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

struct ParserBase {};
struct Parser : VPad<39, ParserBase> {             // slot 0x9c
    virtual u32 Convert(void* arg);
};

struct cCommandRaidCheat {
    void*   mPad0;                                // +0x00
    Parser* mParser;                              // +0x04
    void Execute(cArguments* args);               // 0x10251e0
};

// free helpers.  The game objects reached through these have no reconstructed
// types yet, so their `this` pointer is spelled out as the first parameter.
void* FUN_01021260();                                         // 0x1021260  GetActivePlanet
int   FUN_01021080();                                         // 0x1021080  GetUniverseContext
int   FUN_01021090();                                         // 0x1021090  GetPlayerEmpireID
void* FUN_01021240(int a);                                    // 0x1021240  cSPMission::IsArchived
void* FUN_01021300();                                         // 0x1021300  GetPlayerEmpire
void* FUN_00fd9c60();                                         // 0xfd9c60
void* FUN_0102f660(void* p);                                  // 0x102f660
void* FUN_0102acb0(int a, void* b, void* c);                  // 0x102acb0  CreateUFO
void  FUN_00c3aa40(void* a, u32 b);                           // 0xc3aa40
u32   FUN_00c37120();                                         // 0xc37120
void  FUN_00c3daa0(float f);                                  // 0xc3daa0
void* FUN_00b3d2a0(void* p);                                  // 0xb3d2a0  StarManager
void* FUN_00b3d300();                                         // 0xb3d300  NounManager
void* FUN_00b3d350();                                         // 0xb3d350  PlanetModel
void* FUN_00ffbe50();                                         // 0xffbe50  GetUFOSimulator
void* FUN_00bb57b0(void* p);                                  // 0xbb57b0
void* FUN_00bba790(void* p);                                  // 0xbba790
u32   FUN_00b8dab0(void* p);                                  // 0xb8dab0
void* FUN_00b8de30(void* p);                                  // 0xb8de30  cBioElemSort
void* FUN_00b1fdb0(void* p);                                  // 0xb1fdb0  GetAvatar
void* FUN_00ba9370(void* p, void* a);                         // 0xba9370  GetEmpireByID
void  FUN_00b5f950(void* p, void* v);                         // 0xb5f950  AutoRefCount::operator=
void* FUN_00b81780(void* p, void* a, void* b);                // 0xb81780  MakeRandomWorldPosition
u32   FUN_00b7f190(void* p, void* a, void* b);                // 0xb7f190  BuildSurfaceOrientation
void* FUN_00b21340(void*, void*, void*, void*, void*, void*); // 0xb21340  GetGameDataVector
void* FUN_00a1ad60(void* p);                                  // 0xa1ad60  GetPlayerInventory
void* FUN_00c8e810(void* p);                                  // 0xc8e810  cTribe::GetMembers
void  FUN_00be3850(void* p);                                  // 0xbe3850
void  FUN_00c5b370(void* p, int t);                           // 0xc5b370  SetTarget
void  FUN_00c47180(void* p, void* a);                         // 0xc47180
int   FUN_00c5b530(void* p);                                  // 0xc5b530  GenerateBomberCount
void  FUN_00c5b390(void* p, int n);                           // 0xc5b390
void  FUN_00c485b0(void* p);                                  // 0xc485b0  Accept
void* GetMissionManager(void*, void*, void*, void*);          // 0xfeb9f0
void* FUN_00fec590(void*, void*, void*, void*);               // 0xfec590  CreateMissionFromID

extern void* gSimUniverse;                                    // 0x16dc798
extern float g_f100;                                          // 0x13ec4d0  100.0f
extern float g_f50;                                           // 0x13ebc5c   50.0f
extern float g_f1_1;                                          // 0x13ef54c    1.1f

struct PtrVecT {                                              // eastl::vector<T*> view
    u32    pad0;                                              // +0x00
    void** mpBegin;                                           // +0x04
    void** mpEnd;                                             // +0x08
};

struct cActivePlanetT {                                       // active planet (partial)
    u8  pad0[0x13c];
    u32 mRaidID;                                              // +0x13c
};

struct cUfoT {                                                // created UFO (partial)
    u8    pad0[0x68c];
    void* mRefCounted68c;                                     // +0x68c
};

struct cSimulatorUniverseT {
    void RemoveRaid(int a, u32 id, u32 what);                 // 0x100e780
    void FUN_01012aa0(void* empire, u32 id);                  // 0x1012aa0
};

struct Field34Base {};
struct Field34 : VPad<11, Field34Base> {                      // vtable slot 0x2c
    virtual u32 Axis(float, float);
};

struct Vt120Base {};
struct Vt120 : VPad<11, Vt120Base> {                          // vtable slot 0x2c
    virtual void f(int);
};

struct MissionBase {};
struct Mission : VPad<3, MissionBase> {                       // vtable slot 0x0c
    virtual void* GetEvent(void* id);
};

// @ 0x010251e0
void cCommandRaidCheat::Execute(cArguments* args)
{
    cActivePlanetT* planet = (cActivePlanetT*)FUN_01021260();
    if (planet != 0) {
        int local38 = 0;
        void** puVar3 = args->OptionArguments("start", &local38, 0, 1);
        if (puVar3 != 0 && gSimUniverse != 0) {
            u32 uVar12 = 2;
            if (args->NumArguments() == 3)
                uVar12 = mParser->Convert(*puVar3);
            ((cSimulatorUniverseT*)gSimUniverse)->RemoveRaid(0, planet->mRaidID, uVar12);
        }

        if (args->HasFlag("test") && FUN_01021080() == 0) {
            int v18 = 0, v1c = 0, v20 = 0;
            void* pcVar5 = FUN_00fd9c60();
            FUN_0102f660((char*)pcVar5 + 0x160);
            cUfoT* iVar4 = (cUfoT*)FUN_0102acb0(10, (void*)0x1495c6c, &v18);
            void* inv = FUN_00a1ad60(FUN_00ffbe50());
            FUN_00b5f950((char*)iVar4 + 0x68c, inv);
            void* pcVar6 = FUN_00b3d350();
            void* ref = iVar4->mRefCounted68c;
            u32 uVar12 = ((Field34*)((char*)ref + 0x34))->Axis(g_f50, g_f100);
            float f28, f24, f20;
            FUN_00b81780(pcVar6, &f28, (void*)uVar12);
            float f1c = f28 * g_f1_1;
            float f18 = f24 * g_f1_1;
            float f14 = f20 * g_f1_1;
            u8 auStack_10[16];
            u32 uVar13 = FUN_00b7f190(pcVar6, auStack_10, &f28);
            FUN_00c3aa40(&f1c, uVar13);
            FUN_00a1ad60(FUN_00ffbe50());
            float f = (float)FUN_00c37120();
            FUN_00c3daa0(f);
        }

        if (args->HasFlag("brad")) {
            void* a = FUN_01021240(0);
            FUN_00b3d2a0(a);
            FUN_00bb57b0(a);
            PtrVecT* list = (PtrVecT*)FUN_00bba790(FUN_01021240(0));
            u32 i = 0;
            u32 n = (u32)(list->mpEnd - list->mpBegin);
            void* found = args;
            if (n != 0) {
                do {
                    found = list->mpBegin[i];
                    if (FUN_00b8dab0(found) == 5)
                        break;
                    ++i;
                    found = args;
                } while (i < n);
            }
            if (found != 0) {
                void* nm = FUN_00b1fdb0(FUN_00b8de30(found));
                void* emp = FUN_00ba9370(FUN_00b3d2a0(nm), 0);
                GetMissionManager((void*)0xbbae6b99, found, emp, 0);
                Mission* mgr = (Mission*)FUN_00fec590((void*)0xbbae6b99, found, emp, 0);
                void* ev = (mgr != 0) ? mgr->GetEvent((void*)0x3960c0a) : 0;
                if (ev != 0) {
                    u32 pe = (u32)FUN_01021300();
                    FUN_00c5b370(ev, (int)pe);
                    FUN_00c47180(ev, found);
                    int n2 = FUN_00c5b530(ev);
                    FUN_00c5b390(ev, n2);
                    void* av = FUN_00b1fdb0(FUN_01021240(0));
                    int id = FUN_01021090();
                    if ((int)av != id)
                        ((u8*)ev)[0x21e] = 0;
                    FUN_00c485b0(ev);
                }
            }
        }

        if (args->HasFlag("plunder") && gSimUniverse != 0) {
            void* av = FUN_00b1fdb0(FUN_01021240(0));
            void* emp = FUN_00ba9370(FUN_00b3d2a0(av), 0);
            ((cSimulatorUniverseT*)gSimUniverse)->FUN_01012aa0(emp, planet->mRaidID);
        }
    }

    if (args->HasFlag("repair") && FUN_01021080() == 0) {
        PtrVecT* vec = (PtrVecT*)FUN_00b21340(FUN_00b3d300(),
                        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0,
                        (void*)0xb1e500, (void*)0x18c43e8);
        int local38 = (int)(vec->mpEnd - vec->mpBegin);
        int local3c = 0;
        if (local38 > 0) {
            do {
                PtrVecT* members = (PtrVecT*)FUN_00c8e810(vec->mpBegin[local3c]);
                int n = (int)(members->mpEnd - members->mpBegin);
                for (int j = 0; j < n; ++j) {
                    void* obj = members->mpBegin[j];
                    ((Vt120*)((char*)obj + 0x120))->f(0);
                }
                ++local3c;
            } while (local3c < local38);
        }
    }

    if (args->HasFlag("turrets") && FUN_01021080() == 0) {
        PtrVecT* vec = (PtrVecT*)FUN_00b21340(FUN_00b3d300(),
                        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0,
                        (void*)0xb1e500, (void*)0x18c43e8);
        int n = (int)(vec->mpEnd - vec->mpBegin);
        for (int i = 0; i < n; ++i)
            FUN_00be3850(vec->mpBegin[i]);
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<byte[0x14]>::DoInsertValue
// ---------------------------------------------------------------------------
struct T14 {
    int d[5];
    T14(const T14&);                        // 0x50d440 (copy ctor)
    T14& operator=(const T14&);             // 0x50d4e0
};

void  MoveBackward14(T14* first, T14* last, T14* dest);        // 0x758b20
void* DoAlloc14(u32 n, const char*, int, int, const char*, int); // 0xf473a0
void  DoFree14(void* p);                                       // 0xf47380

inline T14* AllocT14(u32 n)
{
    return n ? (T14*)DoAlloc14(n * 0x14, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
             : 0;
}

inline T14* UninitMove14(T14* first, T14* last, T14* dest)
{
    memcpy(dest, first, (unsigned)((char*)last - (char*)first));
    return dest + (last - first);
}

struct Vec14 {
    T14*  mpBegin;
    T14*  mpEnd;
    T14*  mpCapacity;
    u32   mAlloc[2];
    void DoInsertValue(T14* position, const T14& value);           // 0x10255f0
};

// @ 0x010255f0
void Vec14::DoInsertValue(T14* position, const T14& value)
{
    T14* const destPosition = position;
    if (mpEnd != mpCapacity) {
        const T14* pValue = &value;
        if ((pValue >= destPosition) && (pValue < mpEnd))
            ++pValue;
        ::new ((void*)mpEnd) T14(*(mpEnd - 1));
        MoveBackward14(destPosition, mpEnd - 1, mpEnd);
        *destPosition = *pValue;
        ++mpEnd;
    } else {
        const u32 nPosSize  = (u32)(destPosition - mpBegin);
        const u32 nPrevSize = (u32)(mpEnd - mpBegin);
        const u32 nNewSize  = nPrevSize ? (2 * nPrevSize) : 1;
        T14* const pNewData = AllocT14(nNewSize);
        ::new ((void*)(pNewData + nPosSize)) T14(value);
        T14* pNewEnd = UninitMove14(mpBegin, destPosition, pNewData);
        pNewEnd = UninitMove14(destPosition, mpEnd, ++pNewEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            DoFree14(mpBegin);
        mpBegin    = pNewData;
        mpEnd      = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<eastl::set<int> >::resize      (byte-exact)
// ---------------------------------------------------------------------------
// @ 0x01025750
void VecSet::resize(u32 n)
{
    if (n > (u32)(mpEnd - mpBegin)) {
        SetInt v;
        DoFillInsert(mpEnd, n - (u32)(mpEnd - mpBegin), v);
    } else
        erase(mpBegin + n, mpEnd);
}