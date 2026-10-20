// Slice s00ae6240 -- the city simulator object (retail: SPGonzago/SPMissionUtilities.obj).
//
// Recovered layout of the object (offsets come from the asm; the 2008 PDB layout is older):
//   +0x00  vtable 1        +0x08 vtable 2        +0x10 vtable 3 (IMsgHandler)
//   +0x14  eastl vector (member subsystems)      +0x28 eastl vector (member subsystems)
//   +0x38  cSPTimer (simulation clock)           +0x78 cSPTimer (city timer)
//   +0x98  string16 display name                 +0xa8 bool terraform pending
//   +0xa9  bool first-city posted                +0xac int city count
//   +0xb0  int previous city count
// Member / helper names are Claude-coined where no symbol is known.
//
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

typedef unsigned int size_type;
typedef unsigned int uint32_t;

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);                                   // 0x00f473a0
void operator delete[](void* p);                                                 // 0x00f47380

extern "C" unsigned __int64 _aulldiv(unsigned __int64 a, unsigned __int64 b);     // 0x011e0970
extern "C" unsigned __int64 _allmul(unsigned __int64 a, unsigned __int64 b);      // 0x011e0a90

// ------------------------------------------------------------------ interface stand-ins
// Element type of the "A" vectors: AddRef is vtable+0x0c, Release is vtable+0x08.
struct IRefA {
    virtual void v0();
    virtual void v4();
    virtual int  Release();          // +0x08
    virtual int  AddRef();           // +0x0c
};
// Element type of the "B" vectors: AddRef is vtable+0x60, Release is vtable+0x64.
struct IRefB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual int  AddRef();           // +0x60
    virtual int  Release();          // +0x64
};
// Source noun handed to the collection callbacks: AsInterface (IID in vtable+0x0c).
struct IQuery0C {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void* AsInterface(const void* iid);   // +0x0c
};
// cNoun handed to AddSubsystem: AsInterface sits in vtable+0x04.
struct IQuery04 {
    virtual void* AsInterface(const void* iid);   // +0x04
    virtual int  AddRef();                        // +0x0c
};

// ------------------------------------------------------------------ eastl vectors
// Recovered from the out-of-line instances (0xae6bd0/6cc0/6e70/7020) and their helpers.

// Helper instances (other slices / same object; declared only).
// Calling conventions reconstructed from the call sites: the ones the callers do not
// clean up after are callee-cleans (__stdcall / __fastcall-with-edx-hole = thiscall).
struct VecT;
struct VecTB;

void* vec_alloc_copy(int n, IRefA** first, IRefA** last);                                  // 0x00ae6a10 (see VecT::allocCopy)
void  vec_destroy_range(IRefA** first, IRefA** last);                                      // 0x00ae6710
void  vec_destroy_range_b(IRefB** first, IRefB** last);                                    // 0x00ae6ed0-adjacent
IRefA** vec_copy_construct(IRefA*** out, IRefA** first, IRefA** last, IRefA** dst);        // 0x00ae6780
IRefA** vec_copy_assign(IRefA** first, IRefA** last, IRefA** result);                      // 0x00ae67d0
IRefB** vec_copy_assign_b(IRefB** first, IRefB** last, IRefB** result);                    // 0x00ae6880
IRefA** vec_copy_backward(IRefA** last, IRefA** first, IRefA** resultLast);                // 0x00ae6820
void  vec_insert(VecT* self, int, IRefA** pos, IRefA* const* value);                        // 0x00ae6d20 (see VecT::Insert below)
void  vec_insert_b(VecTB* self, int, IRefB** pos, IRefB* const* value);                     // 0x00ae6ed0

struct VecT {
    IRefA** mpBegin;
    IRefA** mpEnd;
    IRefA** mpCapacity;

    void push_back(IRefA* const& value);
    void erase(IRefA** first, IRefA** last);
    void Insert(IRefA** pos, IRefA* const* value);    // 0x00ae6d20
    VecT* assign(const VecT* src);                    // 0x00ae6bd0
    void* allocCopy(int n, IRefA** first, IRefA** last);  // 0x00ae6a10
};

struct VecTB {
    IRefB** mpBegin;
    IRefB** mpEnd;
    IRefB** mpCapacity;

    void push_back(IRefB* const& value);
    void erase(IRefB** first, IRefB** last);
    void Insert(IRefB** pos, IRefB* const* value);    // 0x00ae6ed0
};

// vector<AutoRefCount<SharedLibrary>> destructor instance, called by the owner destructor (thiscall).
struct SharedLibVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void Destroy();                                  // 0x005c7f10
};

// ------------------------------------------------------------------ external functions
struct cSPTimer {
    unsigned __int64 GetElapsedTime();                    // 0x00bc3190
    bool             IsRunning();                         // 0x00feba90
    void             SetElapsedTime(unsigned __int64 v);  // 0x00bc3150
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Method20(void* a, int msg);              // +0x20
    virtual void v24(); virtual void v28();
    virtual void Method2c(void* a, int msg, int arg);     // +0x2c
};
IMessageServer* MessageServer();                          // 0x0067dcc0

void* GameTimeManager();                                  // 0x00b3d380
void* NounManager();                                      // 0x00b3d300
int   GetCurrentGameMode();                               // 0x00b5b800
void* ConfigManager();                                    // 0x0067dd30
void* GetTriggerMgr();                                    // 0x00b3d4d0
void* TerraformingManager(int);                           // 0x00b3d430

// cGonzagoSimulator base of the simulator singleton: its ctor and the register helpers are
// thiscall members (ecx = the object).
struct cGonzagoSimulatorBase {
    void BaseInit();                  // 0x00b5b6c0 (the base ctor, ecx = this)
};
void RegisterSingleton(void* self);       // 0x00b5b6f0
void UnregisterSingleton(void* self);     // 0x00b5b690

struct IConfig {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual int  IsEnabled(const void* id);               // +0x30
};

struct cTriggerMgr;
void PostTrigger(cTriggerMgr*, const wchar_t* name, int a, int b, int c, int d, int e);  // 0x00ae0930

// cGameNounManager::GetGameDataVector (thiscall member: ecx = the noun manager).
// (key, filter, visitor, keyFilter, nounId) -> pointer to the collection descriptor.
struct cGameNounManager {
    int* GetGameDataVector(void* key, void* fn1, void* fn2, void* fn3, void* extra);  // 0x00b21340
    int* GetSubsystemVec(void* extra);                                                // 0x00ae7200
};
inline int* GDV(void* gdm, void* key, void* fn1, void* fn2, void* extra)
{
    return ((cGameNounManager*)gdm)->GetGameDataVector(key, fn1, fn2, (void*)0xb1e520, extra);
}
inline int* GDV(void* gdm, void* key, void* fn1, void* fn2)
{
    return GDV(gdm, key, fn1, fn2, 0);
}

// 0x00829110: copy a range of pointers into raw storage, reporting the end pointer.
void  ptr_copy_range(int** outEnd, const int* first, const int* last, int* dst, int unused);

void  WStr_Format(void* out, const wchar_t* fmt, ...);     // 0x0041e050
void  PreUpdate(void*);                                    // 0x00ae58c0
void  PostUpdate(void* p, void* noun, unsigned __int64 t);  // 0x00ae5840
int   HasCityRoom(void*);                                  // 0x00ae2f70
void  SpawnCity(void* p, int, int);                        // 0x00ae3b30
void  FirstCity(void*);                                    // 0x00ae4610
void  NounStep1(void*);                                    // 0x00beb6d0
void  NounStep2(void*);                                    // 0x00bfbbf0
void  NounStep3(void*);                                    // 0x00bff7a0
void  TerraformReset(void*);                               // 0x00bc08d0
void* CivModeStrategy();                                   // 0x00cf74c0
void  CivModeNotify(void*);                                // 0x00cf9310
void  RemoveNoun(void* gdm, void* noun);                   // 0x00b225d0
void* GetCivilizationList(void* gdm);                      // 0x00b25ca0
void* cVarList_Construct(void* self, void* obj, const void* field, unsigned id);   // 0x00692f90
bool  cVarList_Serialize(void* self, void* stream);        // 0x00693e10

// ------------------------------------------------------------------ literals / vtables
extern char str_eastl_allocator[];        // 0x013ebb38  "...EASTL/allocator.h"
extern char str_simulator[];              // 0x013f09b4  "Simulator"
extern wchar_t str_city_simulator[];      // 0x0145bb28  L"City Simulator"
extern wchar_t str_cities_fmt[];          // 0x0145baf4  L"cities: %d, sim timer: %d"
extern char str_trigger_new_city[];       // 0x0145badc  "CVG_PRE_NewCityAppears"
extern void* vtbl_sim_base[];             // 0x0145bcf8
extern void* vtbl_sim_base2[];            // 0x0145bcd4
extern void* vtbl_sim_derived[];          // 0x0145bd48
extern void* vtbl_sim_derived2[];         // 0x0145bd24
extern void* vtbl_sim_derived3[];         // 0x0145bd14
extern void* vtbl_msg_handler[];          // 0x013eb384 / 0x013eb394
extern void* vtbl_msg_handler2[];         // 0x013eb394
extern void* vtbl_refcount[];             // 0x013ec458
extern void* vtbl_resbase[];              // 0x013eb938
extern char iid_subsystem[];              // 0x0142db2a
#define iid_noun ((const void*)0x017f243b) // interface id literal (not a data object)
extern char iid_subsystem_b[];            // 0x013f94d4
extern void* g_sim_singleton;             // 0x0167a690

// ------------------------------------------------------------------ the object
// Two timer-like sub-objects with different footprints; modelled as opaque payloads so the
// member offsets stay exactly as the retail object has them.
struct SimClock {
    char mData[0x40];
    unsigned __int64 GetElapsedTime();                    // 0x00bc3190
    void             SetElapsedTime(unsigned __int64 v);  // 0x00bc3150
};
struct CityClock {
    char mData[0x20];
    bool             IsRunning();                         // 0x00feba90
    unsigned __int64 GetElapsedTime();                    // 0x00bc3190
};

struct cCitySimulator {
    void*  mpVtbl;          // +0x00
    char   mPad04[0x04];    // +0x04
    void*  mpVtbl2;         // +0x08
    char   mPad0c[0x04];    // +0x0c
    void*  mpVtbl3;         // +0x10
    VecT   mV0;             // +0x14
    char   mPad20[0x08];    // +0x20
    VecT   mV1;             // +0x28
    SimClock mSimClock;     // +0x38
    CityClock mCityClock;   // +0x78
    void*  mpName;          // +0x98
    char   mPad9c[0x0c];
    char   mTerraformPending;// +0xa8
    char   mFirstCityPosted;// +0xa9
    char   mPadAa[2];
    int    mCityCount;      // +0xac
    int    mPrevCityCount;  // +0xb0

    void PostMsg();         // 0x00ae6570
    void AttachSubsystems();// 0x00ae7350
    void AddSubsystem(IQuery04* noun);  // 0x00ae7100
    const wchar_t* GetName(int kind);   // 0x00ae6500
    void SerializeStream(void* stream); // 0x00ae6610
    cCitySimulator();                   // 0x00ae6a70
    ~cCitySimulator();                  // 0x00ae6b40
};

// ------------------------------------------------------------------ definitions

// @ 0x00ae6240
// sym=SP::CreateInfectedAnimalsOnPlanet
void cCitySimulator_Update(cCitySimulator* p)
{
    PreUpdate(p);
    if (((char*)GameTimeManager())[0x48] & 1)
        goto checkMode;

    {
        const unsigned __int64 elapsed = p->mSimClock.GetElapsedTime();
        const bool bNewCity = elapsed > 1000;

        {
            int* const data = GDV(NounManager(), (void*)0xcd7d10, (void*)0xd3d420,
                                                (void*)0xacdff0);
            int* const begin = data + 1;
            const int n = (data[2] - data[1]) >> 2;
            int i = 0;
            if (n > 0) {
                do {
                    void* const noun = (void*)*(int*)(begin[0] + i * 4);
                    NounStep1(noun);
                    if (bNewCity)
                        PostUpdate(p, noun, elapsed);
                    ++i;
                } while (i < n);
            }

            if (!bNewCity)
                goto checkMode;

            {
                int* const civ = (int*)GetCivilizationList(NounManager());
                const int cnt = (civ[1] - civ[0]) >> 2;
                int* tmp;
                if (cnt == 0) {
                    tmp = 0;
                } else {
                    tmp = (int*)operator new((unsigned)(cnt * 4), str_simulator, 0, 0,
                                             str_eastl_allocator, 0xd1);
                }
                int* end = tmp;
                ptr_copy_range(&end, (const int*)civ[0], (const int*)civ[1], tmp, 0);
                const int count = (int)(end - tmp);
                for (int k = 0; k < count; ++k)
                    NounStep2((void*)tmp[k]);

                {
                    const unsigned __int64 whole = _aulldiv(p->mSimClock.GetElapsedTime(), 1000);
                    p->mSimClock.SetElapsedTime(_allmul(whole, 1000));
                }

                if (p->mPrevCityCount > 0 && HasCityRoom(p) == 1 &&
                    p->mCityCount - p->mPrevCityCount < 2) {
                    if (((IConfig*)ConfigManager())->IsEnabled((void*)0x4ea96cb))
                        PostTrigger((cTriggerMgr*)GetTriggerMgr(), (const wchar_t*)str_trigger_new_city,
                                    1, 0, 0, 0, 0);
                    else
                        SpawnCity(p, 0, 0);
                } else if (GetCurrentGameMode() == 0x1654c04 && !p->mFirstCityPosted &&
                           p->mCityClock.IsRunning() && p->mCityClock.GetElapsedTime() > 3000) {
                    FirstCity(p);
                    CivModeNotify(CivModeStrategy());
                    p->mFirstCityPosted = 1;
                }

                {
                    int* const d2 = GDV(NounManager(), (void*)0xcd7d10, (void*)0xae5ea0,
                                                      (void*)0x403df5c);
                    int* it = d2 + 1;
                    int* const stop = d2 + 2;
                    for (; it != stop; ++it)
                        NounStep3((void*)*it);
                }

                for (int* q = tmp; q < end; ++q)
                    if ((IRefA*)*q != 0)
                        ((IRefA*)*q)->Release();
                if (tmp != 0 && ((int*)tmp)[-1] != 0)
                    operator delete[](tmp);
            }
        }
    }

checkMode:
    if (GetCurrentGameMode() == 0x1654c05 && p->mTerraformPending) {
        TerraformReset(TerraformingManager(0));
        p->mTerraformPending = 0;
    }
}

// @ 0x00ae6500
const wchar_t* cCitySimulator::GetName(int kind)
{
    if (kind == 2)
        return str_city_simulator;
    int* const data = GDV(NounManager(), (void*)0xcd7d10, (void*)0xd3d420,
                          (void*)0xacdff0, (void*)0x18c43e8);
    const int n = (data[2] - data[1]) >> 2;
    const unsigned __int64 t = mSimClock.GetElapsedTime();
    WStr_Format(&mpName, str_cities_fmt, n, (int)(unsigned int)t);
    return (const wchar_t*)mpName;
}

// @ 0x00ae6570
void cCitySimulator::PostMsg()
{
    void* const handler = this ? (void*)((char*)this + 0x10) : 0;
    IMessageServer* const ms = MessageServer();
    ms->Method2c(handler, 0x1a0219e, 0xffffd8f1);
}

// @ 0x00ae6610
void cCitySimulator::SerializeStream(void* stream)
{
    char serializer[0xa14];
    cVarList_Construct(serializer, (char*)this - 8, (const void*)0x1566b98, 0x1a80d26);
    cVarList_Serialize(serializer, stream);
    *((char*)this + 0x35) = 1;
}

// @ 0x00ae6670
struct RefHolder { IRefB* mpObj; void Release(); };
void RefHolder::Release()
{
    IRefB* const old = mpObj;
    mpObj = 0;
    if (old)
        old->Release();
}

// @ 0x00ae6a70
cCitySimulator::cCitySimulator()
{
    ((cGonzagoSimulatorBase*)this)->BaseInit();
    mpVtbl = vtbl_sim_base;
    mpVtbl2 = vtbl_sim_base2;
    g_sim_singleton = this;
    RegisterSingleton(this);
    mpVtbl3 = vtbl_msg_handler;
    mpVtbl = vtbl_sim_derived;
    mpVtbl2 = vtbl_sim_derived2;
    mpVtbl3 = vtbl_sim_derived3;
    mV0.mpBegin = 0;
    mV0.mpEnd = 0;
    mV0.mpCapacity = 0;
    mV1.mpBegin = 0;
    mV1.mpEnd = 0;
    mV1.mpCapacity = 0;
    *((char*)this + 0x3c) = 0;
    *((char*)this + 0x3d) = 0;
}

// @ 0x00ae6b40
cCitySimulator::~cCitySimulator()
{
    mpVtbl = vtbl_sim_derived;
    mpVtbl2 = vtbl_sim_derived2;
    mpVtbl3 = vtbl_sim_derived3;
    ((SharedLibVec*)&mV1)->Destroy();
    ((SharedLibVec*)&mV0)->Destroy();
    mpVtbl3 = vtbl_msg_handler2;
    mpVtbl = vtbl_sim_base;
    mpVtbl2 = vtbl_sim_base2;
    UnregisterSingleton(this);
    if (g_sim_singleton == this)
        g_sim_singleton = 0;
    mpVtbl = vtbl_refcount;
    mpVtbl2 = vtbl_resbase;
}

// @ 0x00ae6bd0
VecT* VecT::assign(const VecT* src)
{
    VecT* const self = this;
    if (src == self)
        return self;
    const int n = (int)(src->mpEnd - src->mpBegin);
    if ((unsigned)n > (unsigned)(self->mpCapacity - self->mpBegin)) {
        IRefA** const pNew = (IRefA**)self->allocCopy(n, src->mpBegin, src->mpEnd);
        vec_destroy_range(self->mpBegin, self->mpEnd);
        if (self->mpBegin != 0 && ((int*)self->mpBegin)[-1] != 0)
            operator delete[](self->mpBegin);
        self->mpCapacity = pNew + n;
        self->mpEnd = pNew + n;
        self->mpBegin = pNew;
        return self;
    }
    const int cap = (int)(self->mpEnd - self->mpBegin);
    if (n > cap) {
        vec_copy_assign(src->mpBegin, src->mpBegin + cap, self->mpBegin);
        IRefA** mid = self->mpBegin + cap;
        vec_copy_construct(&mid, src->mpBegin + cap, src->mpEnd, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
        return self;
    }
    IRefA** const pEnd = vec_copy_assign(src->mpBegin, src->mpEnd, self->mpBegin);
    vec_destroy_range(pEnd, self->mpEnd);
    self->mpEnd = self->mpBegin + n;
    return self;
}

// @ 0x00ae6cc0
void VecT::erase(IRefA** first, IRefA** last)
{
    IRefA** const pLast = last;
    IRefA** const pFirst = first;
    IRefA** p = vec_copy_assign(pLast, mpEnd, pFirst);
    IRefA** const end = mpEnd;
    for (; p < end; ++p)
        if (*p != 0)
            (*p)->Release();
    mpEnd += pFirst - pLast;
}

// @ 0x00ae6e70
void VecTB::erase(IRefB** first, IRefB** last)
{
    IRefB** const pLast = last;
    IRefB** const pFirst = first;
    IRefB** p = vec_copy_assign_b(pLast, mpEnd, pFirst);
    IRefB** const end = mpEnd;
    for (; p < end; ++p)
        if (*p != 0)
            (*p)->Release();
    mpEnd += pFirst - pLast;
}

// @ 0x00ae7020
void VecT::push_back(IRefA* const& value)
{
    IRefA** p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            *p = value;
            if (*p != 0)
                (*p)->AddRef();
        }
    } else {
        Insert(p, &value);
    }
}

// @ 0x00ae7060
void VecT_clear_cb(void* db)
{
    VecT* const v = (VecT*)((char*)db + 4);
    v->erase(v->mpBegin, v->mpEnd);
}

// @ 0x00ae7080
void CollectSubsystemA(void* db, IQuery0C* noun)
{
    IRefA* obj = noun ? (IRefA*)noun->AsInterface(iid_subsystem) : 0;
    if (obj != 0)
        obj->AddRef();
    VecT* const v = (VecT*)((char*)db + 4);
    IRefA* tmp = obj;
    v->push_back(tmp);
    if (obj != 0)
        obj->Release();
}

// @ 0x00ae7100
void cCitySimulator::AddSubsystem(IQuery04* noun)
{
    if (mpName == 0 && *((char*)this + 0x3c) == 0)
        return;
    if (*((char*)this + 0x3c) == 0) {
        RemoveNoun(NounManager(), noun ? noun->AsInterface(iid_noun) : 0);
        return;
    }
    if (noun != 0)
        noun->AddRef();
    IRefA* tmp = (IRefA*)noun;
    mV1.push_back(tmp);
    if (noun != 0)
        ((IRefA*)noun)->Release();
}

// @ 0x00ae71a0
bool cCitySimulator_HandleMessage(cCitySimulator* p, unsigned int msg, int* data)
{
    if (msg == 0x1a0219e && data[2] == 3 && (IQuery0C*)data[4] != 0) {
        IRefA* obj = (IRefA*)((IQuery0C*)data[4])->AsInterface(iid_subsystem);
        if (obj != 0) {
            obj->AddRef();
            IRefA* tmp = obj;
            p->mV0.push_back(tmp);
            obj->Release();
        }
    }
    return false;
}

// @ 0x00ae7200
int* cGameNounManager::GetSubsystemVec(void* extra)
{
    return (int*)((char*)GetGameDataVector((void*)0xcd7d10, (void*)0xae7060,
                                           (void*)0xae7080, (void*)0xb1e520, extra) + 4);
}
// @ 0x00ae7230
void VecTB_clear_cb(void* db)
{
    VecTB* const v = (VecTB*)((char*)db + 4);
    v->erase(v->mpBegin, v->mpEnd);
}

// @ 0x00ae7250
void CollectSubsystemB(void* db, IQuery0C* noun)
{
    IRefB* obj = noun ? (IRefB*)noun->AsInterface(iid_subsystem_b) : 0;
    if (obj != 0)
        obj->AddRef();
    VecTB* const v = (VecTB*)((char*)db + 4);
    IRefB* tmp = obj;
    v->push_back(tmp);
    if (obj != 0)
        obj->Release();
}

// @ 0x00ae7350
void cCitySimulator::AttachSubsystems()
{
    int* const db = (int*)((char*)GDV(NounManager(), (void*)0xcd7d10, (void*)0xae7060,
                                                    (void*)0xae7080, iid_subsystem) + 4);
    mV0.assign((const VecT*)db);
    *((char*)this + 0x3c) = 0;
    *((char*)this + 0x3d) = 0;
    IMessageServer* const ms = MessageServer();
    ms->Method20((char*)this + 0x10, 0x1a0219e);
}
