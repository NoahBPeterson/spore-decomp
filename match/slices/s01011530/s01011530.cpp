// Slice s01011530: 0x01011530..0x01012640 (12 functions).
//
//   0x01011530  eastl::partial_sort<AutoRefCount<cPlanetRecord>*, BioProtectorSort>   (497 B)
//   0x010117c0  partial_sort sibling over the AutoRefCount list                       (309 B)
//   0x01011a40  eastl::pop_heap<tGrobShockData>  (adjust_heap_grob + timer temp)      (266 B)
//   0x01011b50  SP::cSimulatorUniverse::~cSimulatorUniverse (rbtree/timer teardown)   (314 B)
//   0x01011cc0  eastl vector assignment (DoResize / copy_impl)                        (234 B)
//   0x01011db0  list serialiser (ConvertToString16 + wstring node walk)               (326 B)
//   0x01012030  eastl vector grow + range copy                                        (453 B)
//   0x01012330  eastl::make_heap<tGrobShockData, tGrobLess>                           (151 B)
//   0x010123d0  eastl::sort_heap<tGrobShockData, tGrobLess>                           ( 92 B)
//   0x01012450  SP::WarRaid::Start                                                    (225 B)
//   0x01012540  SP::GrobWarRaid::Start                                                (251 B)
//   0x01012640  SP::GrobTeaseRaid::Start                                              (229 B)
//
// Module is SporeApp Simulator/game code (VC9 SP1), not Havok.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

// SP::cSPTimer sub-object (0x20 bytes), embedded in tGrobShockData at +0x08.
struct cSPTimer {
    void* mVtbl;        // +0x00  (0x01465d54 -> 0x01464450)
    int   mRefCount;    // +0x04
    int   mElapsedLo;   // +0x08
    int   mElapsedHi;   // +0x0c
    int   mBaseLo;      // +0x10
    int   mBaseHi;      // +0x14
    char  mRunning;     // +0x18
    char  mPad19[3];
    int   mGetMs;       // +0x1c

    void Dtor();        // 0x00b638b0  SP::cGonzagoTimer::~cGonzagoTimer
};

// SP::cSimulatorUniverse::tGrobShockData (0x28 bytes).
struct tGrobShockData {
    int      mField00;  // +0x00
    int      mField04;  // +0x04
    cSPTimer mTimer;    // +0x08

    tGrobShockData(const tGrobShockData& o)
    {
        mField00 = o.mField00;
        mField04 = o.mField04;
        mTimer.mVtbl = (void*)0x01465d54;
        mTimer.mRefCount = 0;
        mTimer.mElapsedLo = o.mTimer.mElapsedLo;
        mTimer.mElapsedHi = o.mTimer.mElapsedHi;
        mTimer.mBaseLo    = o.mTimer.mBaseLo;
        mTimer.mBaseHi    = o.mTimer.mBaseHi;
        mTimer.mRunning   = o.mTimer.mRunning;
        mTimer.mGetMs     = o.mTimer.mGetMs;
        mTimer.mVtbl = (void*)0x01464450;
    }

    // Copy-assignment copies the head dwords and the timer payload but leaves the
    // timer vtable/refcount alone (matches 0x01011a7d..0x01011aae).
    tGrobShockData& operator=(const tGrobShockData& o)
    {
        mField00 = o.mField00;
        mField04 = o.mField04;
        mTimer.mElapsedLo = o.mTimer.mElapsedLo;
        mTimer.mElapsedHi = o.mTimer.mElapsedHi;
        mTimer.mBaseLo    = o.mTimer.mBaseLo;
        mTimer.mBaseHi    = o.mTimer.mBaseHi;
        mTimer.mRunning   = o.mTimer.mRunning;
        mTimer.mGetMs     = o.mTimer.mGetMs;
        return *this;
    }
};

// eastl comparator functor used by the grob-shock heap helpers.
typedef bool (__cdecl *tGrobLess)(const tGrobShockData&, const tGrobShockData&);

// 0x01011900  SP::cSimulatorUniverse::adjust_heap_grob
//   adjust_heap(first, holeIndex, heapLength, topIndex, value, compare) -- the heap
//   value is passed by value (0x28 bytes) in the outgoing argument area.
void __cdecl adjust_heap_grob(tGrobShockData* first, int holeIndex, int heapLength,
                              int topIndex, tGrobShockData value, tGrobLess compare);

// eastl::pop_heap<tGrobShockData*, tGrobLess>  (kept out-of-line: 0x010123d0 has a real
// call to it, matching the original build).
void __declspec(noinline) __cdecl FUN_01011a40(tGrobShockData* first, tGrobShockData* last,
                                               tGrobLess compare);

// ---------------------------------------------------------------- 0x01011530

// @ 0x01011530
void __cdecl FUN_01011530(void) {}

// ---------------------------------------------------------------- 0x010117c0

// @ 0x010117c0
void __cdecl FUN_010117c0(void) {}

// ---------------------------------------------------------------- 0x01011a40

// eastl::pop_heap<tGrobShockData*, tGrobLess>
//
//   value = *(last - 1);
//   *(last - 1) = *first;
//   adjust_heap_grob(first, 0, (last - first) - 1, 0, value, compare);
//   ~value;
//
// @ 0x01011a40
void __cdecl FUN_01011a40(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    tGrobShockData value(last[-1]);
    last[-1] = *first;
    adjust_heap_grob(first, 0, (int)(last - first) - 1, 0, value, compare);
    value.mTimer.Dtor();
}

// ---------------------------------------------------------------- 0x01011b50

// @ 0x01011b50
void __cdecl FUN_01011b50(void) {}

// ---------------------------------------------------------------- 0x01011cc0

// eastl vector (EA::AutoRefCount<EA::Trace::ILogReporter>) operator=.
struct VecAutoRef {
    void** mpBegin;   // +0x00
    void** mpEnd;     // +0x04
    void** mpCap;     // +0x08

    void** DoResize(unsigned n, void** begin, void** end);   // 0x00b95280
    void   FreeOld(void** begin, void** end);                // 0x00b007f0
    VecAutoRef* Assign(const VecAutoRef& o);                 // 0x011cc0
};

void** __cdecl copy_impl_do_copy(void** first, void** last, void** dst);   // 0x006782c0
void*  __cdecl move_range_range(const void* dst, void** first, void** last, void** dlast, void* src); // 0x00829110
void   __cdecl operator_delete_(void* p);                                  // 0x00f47380

// @ 0x01011cc0
VecAutoRef* VecAutoRef::Assign(const VecAutoRef& o)
{
    if (&o == this)
        return this;
    unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
    if ((unsigned)(mpCap - mpBegin) < n) {
        void** p = DoResize(n, o.mpBegin, o.mpEnd);
        FreeOld(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete_(mpBegin);
        mpCap  = p + n;
        mpEnd  = p + n;
        mpBegin = p;
        return this;
    }
    unsigned have = (unsigned)(mpEnd - mpBegin);
    if (have < n) {
        copy_impl_do_copy(o.mpBegin, o.mpBegin + have, mpBegin);
        move_range_range(&o, o.mpBegin + (mpEnd - mpBegin), o.mpEnd, mpEnd, 0);
        mpEnd = mpBegin + n;
        return this;
    }
    void* p = copy_impl_do_copy(o.mpBegin, o.mpEnd, mpBegin);
    FreeOld((void**)p, mpEnd);
    mpEnd = mpBegin + n;
    return this;
}

// ---------------------------------------------------------------- 0x01011db0

// @ 0x01011db0
void __cdecl FUN_01011db0(void) {}

// ---------------------------------------------------------------- 0x01012030

// @ 0x01012030
void __cdecl FUN_01012030(void) {}

// ---------------------------------------------------------------- 0x01012330

// eastl::make_heap<tGrobShockData*, tGrobLess>
//
//   length = last - first;
//   if (length > 1) {
//       n = (length - 2) / 2 + 1;
//       do { --n; adjust_heap_grob(first, n, length, n, first[n], compare); } while (n);
//   }
//
// @ 0x01012330
void __cdecl FUN_01012330(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    int length = (int)(last - first);
    if (length > 1) {
        int n = (length - 2) / 2 + 1;
        do {
            --n;
            adjust_heap_grob(first, n, length, n, first[n], compare);
        } while (n != 0);
    }
}

// ---------------------------------------------------------------- 0x010123d0

// eastl::sort_heap<tGrobShockData*, tGrobLess>
//
//   while (last - first > 1) { pop_heap(first, last, compare); --last; }
//
// @ 0x010123d0
void __cdecl FUN_010123d0(tGrobShockData* first, tGrobShockData* last, tGrobLess compare)
{
    while (last - first > 1) {
        FUN_01011a40(first, last, compare);
        --last;
    }
}

// ---------------------------------------------------------------- mission objects

struct cEmpire {
    int GetRandomEnemy(int flag);                     // 0x00c31a90
};

struct cStarManager {
    void* GetEmpireByID(void* key);                   // 0x00ba9370
    void* FUN_ba93b0();                               // 0x00ba93b0
};

struct cSPMissionManager {
    void* CreateMissionFromID(int id, int a, void* b, int c);   // 0x00fec590
};

struct cMission {
    virtual void  v0();                               // +0x00
    virtual void  v1();                               // +0x04
    virtual void  v2();                               // +0x08
    virtual void* GetEvent(int id);                   // +0x0c
    virtual void  d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void  d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void  d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void  d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void  d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void  d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void  d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void  d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void  d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void  d40();
    virtual void* vA4(int id, void* self, int a, int b);  // +0x0a4
};

struct cRaidEvent {
    int  GenerateBomberCount();                       // 0x00c5b530
    void SetTarget(int target);                       // 0x00c5b370
    void FUN_c47180(int a);                           // 0x00c47180
    void FUN_c5b390(int a);                           // 0x00c5b390
    void Accept();                                    // 0x00c485b0
};

struct cNounMgr {
    void* FUN_b8de30();                               // 0x00b8de30
    void* FUN_b1fdb0();                               // 0x00b1fdb0
};

struct cSimCtx {
    void FUN_e1c7f0(void** p);                        // 0x00e1c7f0
};

struct cStarRecordRef {
    void* GetCommContext(int id);                     // 0x00ce6950
};

struct cThunk {
    void* FUN_aeb7a0(void* a, void* b);               // 0x00aeb7a0
};

void* __cdecl GetPlayerEmpire();       // 0x01021300
void* __cdecl GetMissionManager();     // 0x00feb9f0
void* __cdecl StarManager();           // 0x00b3d2a0
void* __cdecl CommManager();           // 0x00b3d4a0

// ---------------------------------------------------------------- 0x01012450

struct cWarRaid {
    int Start(int arg1, void* arg2);      // 0x01012450  (ret 8)
};

// @ 0x01012450
int cWarRaid::Start(int arg1, void* arg2)
{
    int enemy = ((cEmpire*)GetPlayerEmpire())->GetRandomEnemy(1);
    if (enemy == 0)
        return 0;
    cSPMissionManager* mm = (cSPMissionManager*)GetMissionManager();
    if (arg1 == 0)
        return 0;

    void* avatar = ((cNounMgr*)arg1)->FUN_b8de30();
    void* av2    = ((cNounMgr*)avatar)->FUN_b1fdb0();
    void* civ    = ((cStarManager*)StarManager())->GetEmpireByID(av2);

    void* mission = mm->CreateMissionFromID(0x77184bae, arg1, civ, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->SetTarget(enemy);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}

// ---------------------------------------------------------------- 0x01012540

struct cGrobWarRaid {
    int Start(int arg1, int arg2);        // 0x01012540  (ret 8)
};

// @ 0x01012540
int cGrobWarRaid::Start(int arg1, int arg2)
{
    if (arg1 == 0)
        return 0;
    void* empire = GetPlayerEmpire();
    void* x      = ((cStarManager*)StarManager())->FUN_ba93b0();
    void* mm = GetMissionManager();
    if (mm == 0)
        return 0;

    void* mission = ((cSPMissionManager*)mm)->CreateMissionFromID(0x25089345, arg1, empire, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    ((cRaidEvent*)raid)->SetTarget((int)x);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* a = ((cMission*)mission)->vA4(0x8b756f4b, mission, 0, 0);
    void* b = ((cStarRecordRef*)arg1)->GetCommContext((int)a);
    ((cThunk*)CommManager())->FUN_aeb7a0(b, *(void**)((char*)empire + 0x84));

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}

// ---------------------------------------------------------------- 0x01012640

struct cGrobTeaseRaid {
    int Start(int arg1, int arg2);        // 0x01012640  (ret 8)
};

// @ 0x01012640
int cGrobTeaseRaid::Start(int arg1, int arg2)
{
    if (arg1 == 0)
        return 0;
    GetPlayerEmpire();
    void* x   = ((cStarManager*)StarManager())->FUN_ba93b0();
    void* av2 = ((cNounMgr*)((cNounMgr*)arg1)->FUN_b8de30())->FUN_b1fdb0();
    void* esi = ((cStarManager*)StarManager())->GetEmpireByID(av2);
    if (esi == 0)
        return 0;
    void* mm = GetMissionManager();
    if (mm == 0)
        return 0;

    void* mission = ((cSPMissionManager*)mm)->CreateMissionFromID(0x56afe39d, arg1, esi, 0);
    if (mission == 0)
        return 0;

    void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
    if (raid == 0)
        return 0;

    ((cRaidEvent*)raid)->SetTarget((int)x);
    ((cRaidEvent*)raid)->FUN_c47180(arg1);
    int count = ((cRaidEvent*)raid)->GenerateBomberCount();
    ((cRaidEvent*)raid)->FUN_c5b390(count);
    ((cRaidEvent*)raid)->Accept();

    void* tmp = mission;
    ((cMission*)mission)->v0();
    ((cSimCtx*)arg2)->FUN_e1c7f0(&tmp);
    if (tmp)
        ((cMission*)tmp)->v1();
    return 1;
}