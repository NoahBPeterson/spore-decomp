// Slice s00d5b0c0: SP::cCityVisualizer::UpdateBackgroundNoise (0x00d5b0c0).
//
// Retail layout differs from the 2008 PDB, so members are accessed by retail byte offset
// (F<T>(p, off)), as in the sibling slices s00d5fb60 / s00d60ce0.
//
// Picks the background noise (crowd / siren / religious ...) from the visualised city's state, then
// starts or stops the looping sounds: the event noise (timer 0xb28), the "set-i" noise (0xb50/0xb54)
// and the capture noise (0xb4c).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <string.h>
typedef unsigned int u32;
typedef unsigned long long u64;

template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }

struct Vec3 { float x, y, z; };

template <class R> static inline R VC0(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}

struct Timer {
    u64  GetElapsedTime();          // 0x00bc3190
    void Restart();                 // 0x00bc3130
};
struct AudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual u32  Create();                           // 0x20
    virtual void v24();
    virtual bool IsPlaying(u32 h);                   // 0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void Begin(u32 id);                      // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);        // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void Commit();                           // 0x58
};
AudioSystem* GetSystemAT();                          // 0x00a206f0

struct NounMgr { int GetPlayerEmpireOrMinus1(); };   // 0x00b1f9d0
NounMgr* __cdecl NounManager();                      // 0x00b3d300
struct CivStrategy { bool FUN_00cf7a90(); };         // 0x00cf7a90
CivStrategy* __cdecl CivModeStrategyGet();           // 0x00cf74c0

struct CityEntryList;
struct City {
    bool  FUN_00bd7df0();                            // 0x00bd7df0
    float FUN_00bd7d00();                            // 0x00bd7d00
    bool  FUN_00c004c0(int);                         // 0x00c004c0
    bool  FUN_00bd8f30();                            // 0x00bd8f30
    void* FUN_00bd8d60(int i);                       // 0x00bd8d60
    void  FUN_00bd9480(Vec3* out);                   // 0x00bd9480
    void  FUN_00c00510(int);                         // 0x00c00510
    struct Vec* GetMembers();                        // 0x00c8e810
    CityEntryList* FUN_00bd7f40();                   // 0x00bd7f40  patrol entry list
    int   GetVehicleSpecialty();                     // 0x00bd81d0
};
struct Vec { int begin, end; };
struct Creature {
    void StartIndependentSound(u32 snd, void* pos, void* handles);   // 0x00c1db40
};
struct SimGlobal {
    char pad[0x2c];
    int mode;                                        // +0x2c
};

u32 SP_GetCurrentGameMode();                         // 0x00b5b800
SimGlobal* FUN_00b3d4d0();                           // 0x00b3d4d0
void __cdecl FUN_00572020(u32 handle, int);          // 0x00572020
void __cdecl Start3dSoundByName(u32 snd, u32 handle, float x, float y, float z);   // 0x00571f80
void __cdecl KillSetiEffects(u32 a, u32 handle);     // 0x00435ed0
extern u32 g_tab147ba00[];                           // 0x0147ba00
extern u32 g_tab147b9f4[];                           // 0x0147b9f4
extern u32 g_tab01583e6c[];                          // 0x01583e6c


// Same body as the standalone StopAndClearSoundList (0x00d5adf0): stop every handle, then clear the vector.
static inline void StopSounds(Vec* hv)
{
    int i = 0;
    if (((hv->end - hv->begin) & ~3) > 0) {
        do {
            u32 hh = ((u32*)hv->begin)[i];
            AudioSystem* at = GetSystemAT();
            if (at) {
                at->Begin(0x347536b);
                at->SetParam(0x3475385, hh);
                at->SetParam(0x34753a0, 0);
                at->Commit();
            }
            i++;
        } while (i < (hv->end - hv->begin) >> 2);
    }
    u32* last = (u32*)hv->end;
    u32* first = (u32*)hv->begin;
    memcpy(first, last, (char*)last - (char*)last);
    hv->end += -((((int)last - (int)first) >> 2)) * 4;
}

struct Viz {
    void UpdateBackgroundNoise();                    // 0x00d5b0c0
    int  FUN_00d5b6c0();                             // 0x00d5b6c0
    void FUN_00d5b8d0();                             // 0x00d5b8d0
    void FUN_00d5b9f0();                             // 0x00d5b9f0
};

#define CITY F<City*>(this, 0xaf0)

// @ 0xd5b0c0
void Viz::UpdateBackgroundNoise()
{
    if (F<int>(this, 0xa64) == F<int>(this, 0xa68)) return;

    int  noise = 1;
    bool haveVec = false;
    Vec3 v = { 0.0f, 0.0f, 0.0f };
    Vec3 tmp;

    if (CITY->FUN_00bd7df0()) noise = 2;
    if (CITY->FUN_00bd7d00() > F<float>(this, 0xb18)) noise = 3;

    if (F<int>(this, 0xb20) < 8) {
        float delta = CITY->FUN_00bd7d00() - F<float>(this, 0xb58);
        F<float>(this, 0xb58) = CITY->FUN_00bd7d00();
        if (delta > 2.0f) {
            F<int>(this, 0xb20) = 5;
            F<u32>(this, 0xb48) = 3000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        } else if (delta < -2.0f) {
            F<int>(this, 0xb20) = 6;
            F<u32>(this, 0xb48) = 3000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        } else if (F<int>(this, 0x38c) != 0) {
            F<int>(this, 0xb20) = 7;
            F<u32>(this, 0xb48) = 2000;
            ((Timer*)((char*)this + 0xb28))->Restart();
        }
        if (CITY->FUN_00c004c0(0)) noise = 4;
    }

    if (CITY->FUN_00bd8f30()) {
        int pid = NounManager()->GetPlayerEmpireOrMinus1();
        int found = -1, other = -1;
        bool sawOwn = false;
        for (int i = 0; i < 4; i++) {
            void* c = CITY->FUN_00bd8d60(i);
            if (F<int>(c, 0x1d8) == 2) {
                if (i == F<int>(this, 0xb1c)) sawOwn = true;
                if (F<int>(c, 0x1dc) == pid) found = i;
                else other = i;
            }
        }
        if (found > -1) other = found;
        else if (sawOwn) other = F<int>(this, 0xb1c);
        F<int>(this, 0xb1c) = other;
        void* c2 = CITY->FUN_00bd8d60(other);
        if (F<float>(c2, 0x20c) > 0.85f) {
            noise = 0xb;
        } else if (F<float>(c2, 0x210) > 0.85f) {
            noise = 0xc;
        } else {
            goto noVec;
        }
        {
            haveVec = true;
            Vec3* p = VC0<Vec3*>((char*)c2 + 0x100, 0x2c / 4);
            ((u32*)&v)[0] = ((u32*)p)[0]; ((u32*)&v)[1] = ((u32*)p)[1]; ((u32*)&v)[2] = ((u32*)p)[2];
        }
    } else {
        F<int>(this, 0xb1c) = -1;
    }

noVec:
    Vec* members = CITY->GetMembers();
    if ((u32)((members->end - members->begin) >> 2) < 2 && SP_GetCurrentGameMode() == 0x1654c05)
        noise = 0;

    u32 h = F<u32>(this, 0xb50);
    if (h != 0) {
        AudioSystem* at = GetSystemAT();
        if (at == 0 || !at->IsPlaying(h)) {
            F<u32>(this, 0xb50) = 0;
            F<bool>(this, 0xb54) = false;
        }
    }
    if (F<u32>(this, 0xb50) != 0 && F<bool>(this, 0xb54)) {
        int mode = FUN_00b3d4d0()->mode;
        if (mode != 1 && mode != 2) {
            FUN_00572020(F<u32>(this, 0xb50), 0);
            F<bool>(this, 0xb54) = false;
            F<u32>(this, 0xb50) = 0;
        }
    }

    if (F<char>(CITY, 0x2a0) != 0) {
        int mode = FUN_00b3d4d0()->mode;
        bool indoors = (mode == 1 || mode == 2);
        F<int>(this, 0xb20) = F<int>(CITY, 0x29c) + 8;
        F<u32>(this, 0xb48) = 10000;
        ((Timer*)((char*)this + 0xb28))->Restart();
        AudioSystem* at = GetSystemAT();
        u32 nh = at ? at->Create() : 0;
        F<u32>(this, 0xb50) = nh;
        if (indoors) {
            KillSetiEffects(g_tab147ba00[F<int>(CITY, 0x29c)], nh);
            F<bool>(this, 0xb54) = true;
        } else if (!VC0<bool>((char*)CITY + 0x120, 0x58 / 4)) {
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(g_tab147b9f4[F<int>(CITY, 0x29c)], F<u32>(this, 0xb50), tmp.x, tmp.y, tmp.z);
        }
    }

    u64 elapsed = ((Timer*)((char*)this + 0xb28))->GetElapsedTime();
    if (elapsed < (u64)F<u32>(this, 0xb48) && F<int>(this, 0xb20) != 0)
        noise = F<int>(this, 0xb20);
    else
        F<int>(this, 0xb20) = 0;

    if (noise != F<int>(this, 0xb14)) {
        Vec* hv = (Vec*)((char*)this + 0xb00);
        F<int>(this, 0xb14) = noise;
        if (hv->begin != hv->end)
            StopSounds(hv);
        if (noise != 0) {
            Vec3* pos;
            if (haveVec) pos = &v;
            else pos = VC1<Vec3*, Vec3*>(CITY, 0x58 / 4, &tmp);
            ((Creature*)F<void*>(F<void*>(this, 0xa64), 0))->StartIndependentSound(g_tab01583e6c[noise], pos, hv);
        }
    }

    if (CivModeStrategyGet()->FUN_00cf7a90())
        CITY->FUN_00c00510(0);

    if (CITY->FUN_00c004c0(0)) {
        if (F<u32>(this, 0xb4c) == 0) {
            AudioSystem* at = GetSystemAT();
            F<u32>(this, 0xb4c) = at ? at->Create() : 0;
            CITY->FUN_00bd9480(&tmp);
            Start3dSoundByName(0xc0ba2669, F<u32>(this, 0xb4c), tmp.x, tmp.y, tmp.z);
        }
    } else if (F<u32>(this, 0xb4c) != 0) {
        u32 bh = F<u32>(this, 0xb4c);
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Begin(0x347536b);
            at->SetParam(0x3475385, bh);
            at->SetParam(0x34753a0, 0);
            at->Commit();
        }
        F<u32>(this, 0xb4c) = 0;
    }
}

// ---------------------------------------------------------------------------
// The two uninitialized-copy loops (eastl::uninitialized_copy and its
// backward twin) instantiated for the action-circle slot record: copy the
// scalar header (int + three flag bytes) into raw storage, then construct the
// nested slot vector from the source one.
// ---------------------------------------------------------------------------

inline void* operator new(unsigned int, void* p) { return p; }

void __cdecl operator_delete__(void* p);        // 0x00f47380  operator delete

struct SlotVector {                             // 0x14 bytes, nested in tSlot
    void*         mpBegin;      // +0x00
    void*         mpEnd;        // +0x04
    void*         mpCap;        // +0x08
    unsigned      mAlloc[2];    // +0x0c
    SlotVector& operator=(const SlotVector& other);   // 0x01011cc0
};

struct tSlot {
    int           mType;        // +0x00
    char          mFlag04;      // +0x04
    char          mFlag05;      // +0x05
    char          mFlag06;      // +0x06
    SlotVector    mSlots;       // +0x08
};

template <class T>
T* UninitializedCopy(const T* first, const T* last, T* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
    return out;
}

template <class T>
T* UninitializedCopyBackward(const T* first, const T* last, T* outEnd)
{
    while (last != first) {
        --last;
        --outEnd;
        *outEnd = *last;
    }
    return outEnd;
}

// @ 0x00d5bf00
template tSlot* UninitializedCopy<tSlot>(const tSlot*, const tSlot*, tSlot*);

// @ 0x00d5bf50
template tSlot* UninitializedCopyBackward<tSlot>(const tSlot*, const tSlot*, tSlot*);

// ---------------------------------------------------------------------------
// 0x00d5b9f0: gather the visible patrol positions of the city into a temporary
// Vector3 list, turn them into an action circle and emit the surface decal.
// ---------------------------------------------------------------------------

struct CityEntry {                              // 0x18-byte entry in the city list
    char  mFlag00;                              // +0x00  skip when set
    char  mPad01[0x0b];                         // +0x01
    Vec3  mPosition;                            // +0x0c
};

struct CityEntryList {                          // returned by cCity::FUN_00bd7f40
    char        mPad00[0x50];                   // +0x00
    CityEntry*  mpBegin;                        // +0x50
    CityEntry*  mpEnd;                          // +0x54
};

struct Vec3Vector {                             // eastl vector<Vector3> with the sp allocator
    Vec3* mpBegin;                              // +0x00
    Vec3* mpEnd;                                // +0x04
    Vec3* mpCap;                                // +0x08
    Vec3Vector() : mpBegin(0), mpEnd(0), mpCap(0) {}
    void DoInsertValue(Vec3* pos, const Vec3& value);       // 0x004b5ad0
    void push_back(const Vec3& value)
    {
        if (mpEnd < mpCap) {
            *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    ~Vec3Vector()
    {
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__((void*)mpBegin);
    }
};

struct cActionCircle {
    void SetAtCenter(void* which, Vec3* center, float radius, void* info);   // 0x00af9cf0
    void EmitCopy(void* points, float scale);                                // 0x00afec00
};

extern const float g_14853e0;                   // 0x014853e0  decal scale

// ---------------------------------------------------------------------------
// 0x00d5b8d0: teardown of the staged culture scenes - walk the four 0x198-byte
// scene slots and their pointer vectors, release each reference-counted
// object, then drop the vectors.
// ---------------------------------------------------------------------------

struct RefObj {                                  // reference-counted object
    virtual void Slot00();
    virtual void Release();                      // +0x04
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Slot28();
    virtual void Slot2c();
    virtual void Slot30();
    virtual void Slot34();
    virtual void Slot38();
    virtual void Slot3c();
    virtual void Slot40();
    virtual void Slot44();
    virtual void StopAll(void* unused);          // +0x48
};

void FUN_00c0d3a0(void* o);                      // 0x00c0d3a0
void FUN_00bcb3d0(void* h);                      // 0x00bcb3d0
void FUN_00accf80(void* o);                      // 0x00accf80
void FUN_00c227c0(void* o);                      // 0x00c227c0
void* FUN_00b3d480(void* o);                     // 0x00b3d480

struct ObjVector {                               // eastl vector of AutoRefCount pointers
    RefObj** mpBegin;                            // +0x00
    RefObj** mpEnd;                              // +0x04
    RefObj** mpCap;                              // +0x08
};

struct CultureSlot {                             // 0x198-byte staged scene slot
    unsigned      mFlag00;                       // +0x00  cleared when emptied
    unsigned char mPad04[0xa78];                 // +0x04
};

RefObj** CopyObjectRange(RefObj** dst, RefObj** first, RefObj** last);   // 0x006782c0

// @ 0x00d5b8d0
void Viz::FUN_00d5b8d0()
{
    if (!F<unsigned char>(this, 0xaf5))
        return;

    FUN_00b3d480(this);                          // 0x00b3d480
    CultureSlot* slot = (CultureSlot*)((char*)this + 0x394);
    for (int i = 0; i < 4; ++i) {
        ObjVector* v = (ObjVector*)((char*)this + 0xa7c + i * 0x14);
        if (v->mpBegin != v->mpEnd) {
            for (RefObj** it = v->mpBegin; it != v->mpEnd; ++it) {
                RefObj* o = *it;
                o->StopAll((void*)0xffffffff);
                if (F<void*>(o, 0xb54) != 0) {
                    void* p = F<void*>(F<void*>(o, 0xb54), 0x180);
                    if (p != 0)
                        F<u32>(p, 4) &= 0xfffff7ff;
                }
                FUN_00c0d3a0(o);                 // 0x00c0d3a0
                FUN_00bcb3d0(F<void*>(o, 0xb4c));// 0x00bcb3d0
                FUN_00accf80(FUN_00b3d480(o));   // 0x00b3d480, 0x00accf80
                FUN_00c227c0(o);                 // 0x00c227c0
            }
            slot->mFlag00 = 0;
            RefObj** first = v->mpBegin;
            RefObj** last = v->mpEnd;
            RefObj** q = CopyObjectRange(last, first, first);   // 0x006782c0
            for (; q < v->mpEnd; ++q) {
                if (*q != 0)
                    (*q)->Release();
            }
            v->mpEnd += -(((int)last - (int)first) >> 2) * 4;
        }
        slot = (CultureSlot*)((char*)slot + 0x198);
    }
    F<unsigned char>(this, 0xaf5) = 0;
}

// ---------------------------------------------------------------------------
// 0x00d5b6c0: choose the background ambience track for the visualised city
// (distance band, vehicle specialty, time of day, civ-trigger state), returning
// the randomly chosen track id or -1.
// ---------------------------------------------------------------------------

struct TimeOfDay { int FUN_00bc2b80(); };        // 0x00bc2b80
TimeOfDay* FUN_00bc30b0(int unused);             // 0x00bc30b0
void* __stdcall FUN_00bd9480(City* c, Vec3* out);// 0x00bd9480

struct FixedIntVec16 {                           // eastl::fixed_vector<int,16>
    int  mBuffer[16];                            // +0x00
    int* mpEnd;                                  // +0x40
    void push_back(const int* value) { *mpEnd++ = *value; }   // 0x00422380
};

struct RandomLCG {                               // EA::RandomLinearCongruential
    u32 RandomUint32Uniform(u32 range);          // 0x00a68fb0
};
extern RandomLCG g_randomGlobal;                 // 0x01601760

void FUN_00c0d3a0(void* o);                      // 0x00c0d3a0
void FUN_00bcb3d0(void* h);                      // 0x00bcb3d0
void FUN_00accf80(void* o);                      // 0x00accf80
void FUN_00c227c0(void* o);                      // 0x00c227c0
void* FUN_00b3d480(void* o);                     // 0x00b3d480

struct CityVehicles {
    float         mMinBand;         // +0x78c
    float         mMaxBand;         // +0x790
    int           mSpecialty;       // +0x794
    int           mSize;            // +0x798
    unsigned char mFlags;           // +0x79c
    int           mTier;            // +0x7a0
};

// @ 0x00d5b6c0
int Viz::FUN_00d5b6c0()
{
    int prev = F<int>(this, 0xc3c);
    if (prev >= 0) {
        F<int>(this, 0xc3c) = -1;
        return prev;
    }

    City* city = CITY;
    float dist = city->FUN_00bd7d00();
    int specialty = city->GetVehicleSpecialty() + 1;
    Vec3 pos;
    void* tod = FUN_00bd9480(city, &pos);
    int time = FUN_00bc30b0((int)tod)->FUN_00bc2b80();
    int tierWant = (time != 0) + 1;
    int sizeWant = F<unsigned char>(city, 0x2a0) ? F<int>(city, 0x29c) + 1 : 0;
    unsigned char flagWant = city->FUN_00bd7df0() ? 1 : 0;
    CivStrategy* strat = CivModeStrategyGet();
    bool active = strat->FUN_00cf7a90();
    if (!active || F<unsigned char>(city, 0x2a0)) {
        int n = (int)(F<int>(this, 0xbac) - F<int>(this, 0xba8)) / (int)sizeof(CityVehicles);        FixedIntVec16 found;
        found.mpEnd = found.mBuffer;
        for (int i = 0; i < n; ++i) {
            CityVehicles* v = (CityVehicles*)(F<int>(this, 0xba8) + i * (int)sizeof(CityVehicles));
            if (v->mMinBand <= dist && dist <= v->mMaxBand
                && (v->mSpecialty == 0 || v->mSpecialty == specialty)
                && (v->mTier == 0 || v->mTier == tierWant)
                && v->mSize == sizeWant
                && v->mFlags == flagWant)
                found.push_back(&i);
        }
        if (found.mpEnd != found.mBuffer) {
            int pick = found.mBuffer[g_randomGlobal.RandomUint32Uniform(
                            ((u32)found.mpEnd - (u32)found.mBuffer) >> 2)];
            if (found.mBuffer != 0 && found.mBuffer != (int*)&found)
                operator_delete__(found.mBuffer);
            return pick;
        }
        if (found.mBuffer != 0 && found.mBuffer != (int*)&found)
            operator_delete__(found.mBuffer);
    } else {
        flagWant = 0;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x00d5bdb0: eastl::vector<tSlot>::operator= - reuse the existing storage,
// grow it or shrink it to match the source vector.
// ---------------------------------------------------------------------------

struct SlotRange {
    void* mpBegin;                               // +0x00
    void* mpEnd;                                 // +0x04
    void* mpCap;                                 // +0x08
    void Assign(const SlotRange* src);           // 0x00d5bdb0
};

void* AllocSlotRange(unsigned n, void* first, void* last);              // 0x00d596f0
void* AskCopySlots(void* dst, void* first, void* last);                 // 0x00afa430
void  DestroySlotRange(void* first, void* end);                         // 0x00afa150
void  SlotCopyCtorWrap(void* result, void* srcEnd, void* dstEnd);       // 0x00c266c0

// @ 0x00d5bdb0
void SlotRange::Assign(const SlotRange* src)
{
    if (src == this)
        return;
    unsigned n = (unsigned)((char*)src->mpEnd - (char*)src->mpBegin) / 0x18;
    if ((unsigned)((char*)mpCap - (char*)mpBegin) / 0x18 < n) {
        void* mem = AllocSlotRange(n, src->mpBegin, src->mpEnd);
        DestroySlotRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpCap = (char*)mem + n * 0x18;
        mpBegin = mem;
        mpEnd = (char*)mem + n * 0x18;
        return;
    }
    unsigned have = (unsigned)((char*)mpEnd - (char*)mpBegin) / 0x18;
    if (have < n) {
        AskCopySlots(mpBegin, src->mpBegin, (char*)src->mpBegin + have * 0x18);
        SlotCopyCtorWrap(src->mpEnd, (char*)src->mpBegin + have * 0x18, mpEnd);
        mpEnd = (char*)mpBegin + n * 0x18;
        return;
    }
    AskCopySlots(mpBegin, src->mpBegin, src->mpEnd);
    DestroySlotRange((char*)mpBegin + n * 0x18, mpEnd);
    mpEnd = (char*)mpBegin + n * 0x18;
}

// ---------------------------------------------------------------------------
// 0x00d5bc30: eastl::vector<Vector3>::DoInsertValue(index, value) - grow,
// fill or shift into place for a 12-byte element vector.
// ---------------------------------------------------------------------------

struct Vec3Slots {
    Vec3* mpBegin;                               // +0x00
    Vec3* mpEnd;                                 // +0x04
    Vec3* mpCap;                                 // +0x08
    char  mAlloc[0x10];                          // +0x0c
    void DoInsertValue(unsigned index, const Vec3* value);   // 0x00d5bc30
};

void* DoInsertGrow(unsigned n, const Vec3* value, void* alloc);         // 0x00d596a0
void  AssignTempGuard(Vec3Slots* self, void* result);                   // 0x00d5acc0
void  FillVec3Range(void* first, void* last, const Vec3* value);        // 0x00a177f0
void  CopyVec12(void* dst, unsigned count, const void* src);            // 0x006a4100
void  CopyVec3Range(void* dst, unsigned n, const Vec3* value);          // 0x00cca0e0
void* EraseVec3(Vec3Slots* self, Vec3* first, Vec3* last);              // 0x009e0480

// @ 0x00d5bc30
void Vec3Slots::DoInsertValue(unsigned index, const Vec3* value)
{
    void* mem[4];
    unsigned capCount = (unsigned)((int)((char*)mpCap - (char*)mpBegin) / 12);
    if (index > capCount) {
        mem[0] = DoInsertGrow(index, value, mAlloc);
        AssignTempGuard(this, mem);
        if (mem[0] != 0 && mem[0] != mem[2])
            operator_delete__(mem[0]);
        return;
    }
    unsigned endCount = (unsigned)((int)((char*)mpEnd - (char*)mpBegin) / 12);
    if (index > endCount) {
        FillVec3Range(mpBegin, mpEnd, value);
        int have = (int)((char*)mpEnd - (char*)mpBegin) / 12;
        CopyVec12(mpEnd, index - have, value);
        mpEnd = (Vec3*)((char*)mpEnd + (index - have) * 12);
        return;
    }
    CopyVec3Range(mpBegin, index, value);
    EraseVec3(this, (Vec3*)((char*)mpBegin + index * 12), mpEnd);
}

// @ 0x00d5b9f0
void Viz::FUN_00d5b9f0()
{
    Vec3Vector pts;

    CityEntryList* list = CITY->FUN_00bd7f40();
    int count = (int)(list->mpEnd - list->mpBegin) / (int)sizeof(CityEntry);
    for (int i = 0; i < count; ++i) {
        CityEntry* e = (CityEntry*)((char*)list->mpBegin + i * sizeof(CityEntry));
        if (e->mFlag00 == 0)
            pts.push_back(e->mPosition);
    }

    void* cityInfo = VC0<void*>(CITY, 0x6c / 4);
    float radius = *(float*)((char*)cityInfo + 0x258);

    Vec3 center1, center2;
    void* sub = (char*)CITY + 0x120;
    typedef void* (__thiscall* SubGet)(void*, Vec3*, float);
    typedef void* (__thiscall* CityGet)(void*, Vec3*, float, void*);
    void* r1 = ((SubGet)(*(void***)sub)[0x5c / 4])(sub, &center1, 0.0f);
    void* r2 = ((CityGet)(*(void***)CITY)[0x58 / 4])(CITY, &center2, radius, r1);

    ((cActionCircle*)((char*)this + 0xbd4))->SetAtCenter(r2, &center2, radius, r1);
    ((cActionCircle*)((char*)this + 0xbd4))->EmitCopy(&pts, g_14853e0);
}
