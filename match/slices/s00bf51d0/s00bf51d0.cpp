// Slice s00bf51d0: Spore Simulator routines (C++ reconstruction).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------
// External routines.  Every symbol keeps its FUN_<address> name so that the
// verifier can bind the call target; __thiscall targets are called through an
// explicit __thiscall function-pointer cast (this in ecx, callee pops the
// stack arguments).
// ---------------------------------------------------------------------------
extern "C" {
// cdecl helpers
void* __cdecl FUN_00f473a0(int size, const char* name, int a, int b,
                            const char* file, int line);            // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                                // 0x00f47380
void  __cdecl FUN_00bf4a90(void);                                   // 0x00bf4a90
void  __cdecl FUN_00bf49e0(void* handle);                           // 0x00bf49e0
void* __cdecl FUN_00b3d300(void);                                   // 0x00b3d300 NounManager
void* __cdecl FUN_00b3d260(void);                                   // 0x00b3d260 BehaviorManager
void* __cdecl FUN_00b3d350(void);                                   // 0x00b3d350 PlanetModel
void* __cdecl FUN_00b3d4a0(void);                                   // 0x00b3d4a0 CommManager
void* __cdecl FUN_01021260(void);                                   // 0x01021260 GetActivePlanet
void* __cdecl FUN_00bf2960(void* first, void* last, void* out);      // 0x00bf2960 uninitialized copy
void  __cdecl FUN_00befb80(void* first, void* last, void* out);      // 0x00befb80 destroy range
void  __cdecl FUN_00bf28f0(void* dst, unsigned count, const void* value, void* pos); // 0x00bf28f0
void  __cdecl FUN_00bf2840(void* out, void* a, void* b, void* c, void* d);           // 0x00bf2840
void  __cdecl FUN_00bf28b0(void* a, void* b, void* c);               // 0x00bf28b0
void  __cdecl FUN_00bf2a10(void* dst, void* first, void* last);      // 0x00bf2a10 move
void* __cdecl FUN_00bf29c0(void* a, void* b, void* c);               // 0x00bf29c0 erase move
int   __fastcall FUN_00bd8210(void* obj);                            // 0x00bd8210 (this in ecx)

// thiscall targets (declared unprototyped, always called through a cast)
void FUN_006a46a0();   // 0x006a46a0 VecC::InitValue
void FUN_009a9600();   // 0x009a9600 rbtree::DoNukeSubtree
void FUN_00a110b0();   // 0x00a110b0
void FUN_00ae9390();   // 0x00ae9390 CommScreen::IsActive
void FUN_00b20c60();   // 0x00b20c60 cGameNounManager::CreateNoun
void FUN_00aea5d0();   // 0x00aea5d0 SPVector<AutoRefCount>::DoInsertPtr
void FUN_00bab900();   // 0x00bab900 SPVector<AutoRefCount> insert (slow path)
void FUN_00b21340();   // 0x00b21340 cGameNounManager::GetGameDataVector
void FUN_00b25ca0();   // 0x00b25ca0 cGameNounManager::GetCivilizationList
void FUN_00b638b0();   // 0x00b638b0 cGonzagoTimer::~cGonzagoTimer
void FUN_00b81470();   // 0x00b81470 cPlanetModel::DistanceBetweenPoints
void FUN_00b88590();   // 0x00b88590 cPlanetModel::GetContinent
void FUN_00bd9bf0();   // 0x00bd9bf0 cCity::GetCivilization
void FUN_00be5be0();   // 0x00be5be0 city event dispatch
void FUN_00bf0f90();   // 0x00bf0f90 UpdateCityMusicPosition
void FUN_00bf5050();   // 0x00bf5050 cVector3Map::FindOrInsert
void FUN_00c71040();   // 0x00c71040
void FUN_00c9eae0();   // 0x00c9eae0
void FUN_00ca6630();   // 0x00ca6630 cVehicle::Init
void FUN_00ff0db0();   // 0x00ff0db0 cSpatialSnapshot::Init
void FUN_00ff2d20();   // 0x00ff2d20
}

typedef unsigned int uint;

static const char kAllocatorPath[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// virtual dispatch: function stored in slot <byteOffset> of the object's vtable
static inline void* _vt(void* obj, int byteOffset)
{
    return ((void**)*(void***)obj)[byteOffset / 4];
}

// ---------------------------------------------------------------------------
// Shared records.
// ---------------------------------------------------------------------------
struct Vec3
{
    float x, y, z;
};

// cGonzagoTimer: 0x20-byte element of the timer vectors.
struct GonzagoTimer
{
    void*         m_vtable;          // +0x00
    int           m_refCount;        // +0x04
    unsigned int  mElapsedTimeLo;    // +0x08
    unsigned int  mElapsedTimeHi;    // +0x0c
    unsigned int  mBaseTimeLo;       // +0x10
    unsigned int  mBaseTimeHi;       // +0x14
    unsigned char mRunning;          // +0x18
    void*         mTimeFn;           // +0x1c
};

// Vector of 0x20-byte cGonzagoTimer records (begin/end/cap at +0/+4/+8).
struct TimerVec
{
    GonzagoTimer* m_begin;           // +0x00
    GonzagoTimer* m_end;             // +0x04
    GonzagoTimer* m_cap;             // +0x08

    // 0x00bf51d0 erase [first, last)
    GonzagoTimer* eraseRange(GonzagoTimer* first, GonzagoTimer* last);
    // 0x00bf5220 insert <count> copies of value at pos
    void insertN(GonzagoTimer* pos, unsigned count, const GonzagoTimer* value);
    // 0x00bf5420 insert one copy of value at pos
    void insertOne(GonzagoTimer* pos, const GonzagoTimer* value);
};

// vector of reference-counted pointers: base+0 begin, base+4 end, base+8 cap
struct PtrVecAt
{
    void** m_begin;                  // +0x00
    void** m_end;                    // +0x04
    void** m_cap;                    // +0x08
};

// object owning the two feedback vectors (0x00bf5630)
struct FeedbackSink
{
    void**  m_vtable;                // +0x00
    char    m_pad4[0xb0 - 0x04];     // +0x04 .. +0xaf
    PtrVecAt m_events;               // +0xb0
    char    m_padBC[0xd4 - 0xbc];    // +0xbc .. +0xd3
    PtrVecAt m_sounds;               // +0xd4

    void AddPair(void* obj);         // 0x00bf5630
};

// opaque 3D-point map at this+0x410
struct Vector3Map
{
    char m_bytes[0x10];
};

// city/tribe record used by 0x00bf59d0 and 0x00bf5b90
struct CityThing
{
    char       m_pad0[0x9c];         // +0x000
    void**     m_citiesBegin;        // +0x09c
    void**     m_citiesEnd;          // +0x0a0
    char       m_padA4[0x410 - 0xa4];// +0x0a4
    Vector3Map m_map;                // +0x410

    void  UpdateDistances();         // 0x00bf59d0
    float GetDistance(void* key);    // 0x00bf5b90
};

// event-handler subobject living 0x38 bytes inside a city
struct CityEventSub
{
    char          m_pad0[0x51];      // +0x000
    unsigned char m_flag51;          // +0x051
    char          m_pad52[0x46c - 0x52]; // +0x052
    void*         m_civ;             // +0x46c
    int           m_soundId;         // +0x470

    bool OnEvent(int eventId, void* data); // 0x00bf5be0
};

// object that checks cities against the planet model (0x00bf5720)
struct PlanetChecker
{
    int CheckPlanet(void* obj);      // 0x00bf5720
};

// vehicle factory (0x00bf57b0)
struct VehicleFactory
{
    void* CreateVehicle(void* p2, void* p3, void* p4, void* p5,
                        void* p6, void* p7);  // 0x00bf57b0
};

// local EASTL vector of Vec3 used by UpdateDistances
struct VecC
{
    Vec3* m_data;                    // +0x00
    int   m_count;                   // +0x04
    int   m_cap;                     // +0x08
};

// snapshot record handed to the spatial vtable slot 0xdc
struct VehicleSnapshot
{
    void* m_alloc;                   // +0x00
    char  m_pad4[0x0c];              // +0x04
    Vec3  m_pos;                     // +0x10
    char  m_pad1C[0x24 - 0x1c];      // +0x1c
    float m_f24;                     // +0x24
    char  m_pad28[0x70 - 0x28];      // +0x28
    float m_f70;                     // +0x70
    float m_f74;                     // +0x74
    char  m_pad78[0x7c - 0x78];      // +0x78
    float m_f7c;                     // +0x7c
    float m_f80;                     // +0x80
    int   m_i84;                     // +0x84
};

// ---------------------------------------------------------------------------
// 0x00bf51d0 - erase [first,last) from a cGonzagoTimer vector.
// ---------------------------------------------------------------------------
// @ 0x00bf51d0
GonzagoTimer* TimerVec::eraseRange(GonzagoTimer* first, GonzagoTimer* last)
{
    GonzagoTimer* newEnd = (GonzagoTimer*)FUN_00bf29c0(last, m_end, first);

    for (GonzagoTimer* p = newEnd; p < m_end; ++p)
        ((void (__thiscall*)(GonzagoTimer*, int))_vt(p, 0))(p, 0);

    m_end = (GonzagoTimer*)((char*)m_end +
                            (((char*)last - (char*)first) >> 5) * -0x20);
    return first;
}

// ---------------------------------------------------------------------------
// 0x00bf5220 - insert <count> copies of value before pos (0x20-byte records).
// ---------------------------------------------------------------------------
// @ 0x00bf5220
void TimerVec::insertN(GonzagoTimer* pos, unsigned count, const GonzagoTimer* value)
{
    unsigned freeSlots = (unsigned)((char*)m_cap - (char*)m_end) >> 5;

    if (freeSlots < count) {
        unsigned size    = (unsigned)((char*)m_end - (char*)m_begin) >> 5;
        unsigned newCap  = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + count;
        if (need < newCap)
            need = newCap;

        GonzagoTimer* block = 0;
        if (need != 0)
            block = (GonzagoTimer*)FUN_00f473a0((int)(need << 5), "Simulator",
                                                0, 0, kAllocatorPath, 0xd1);

        GonzagoTimer* oldBegin = m_begin;
        GonzagoTimer* oldPos   = pos;
        GonzagoTimer* newMid   = (GonzagoTimer*)FUN_00bf2960(oldBegin, oldPos, block);
        FUN_00befb80(oldBegin, oldPos, block);
        FUN_00bf28f0(newMid, count, value, newMid);

        GonzagoTimer* afterInsert =
            (GonzagoTimer*)((char*)newMid + (count << 5));
        GonzagoTimer* oldEnd = m_end;
        GonzagoTimer* newEnd = (GonzagoTimer*)FUN_00bf2960(oldPos, oldEnd, afterInsert);
        FUN_00befb80(oldPos, oldEnd, afterInsert);

        if (m_begin != 0 && *(int*)((char*)m_begin - 4) != 0)
            FUN_00f47380(m_begin);

        m_end   = newEnd;
        m_begin = block;
        m_cap   = (GonzagoTimer*)((char*)block + (need << 5));
    }
    else if (count != 0) {
        GonzagoTimer local;
        local.mElapsedTimeLo = value->mElapsedTimeLo;
        local.mElapsedTimeHi = value->mElapsedTimeHi;
        local.mBaseTimeLo    = value->mBaseTimeLo;
        local.mBaseTimeHi    = value->mBaseTimeHi;
        local.mRunning       = value->mRunning;
        local.mTimeFn        = value->mTimeFn;
        local.m_refCount     = 0;
        local.m_vtable       = (void*)0x01464450;

        GonzagoTimer* oldEnd = m_end;
        unsigned tail = (unsigned)((char*)oldEnd - (char*)pos) >> 5;

        if (tail <= count) {
            unsigned extra = count - tail;
            FUN_00bf28f0(oldEnd, extra, &local, pos);
            m_end = (GonzagoTimer*)((char*)m_end + (extra << 5));
            FUN_00bf2840(&pos, pos, oldEnd, m_end, pos);
            m_end = (GonzagoTimer*)((char*)m_end + (tail << 5));
            FUN_00bf28b0(pos, oldEnd, &local);
            ((void (__thiscall*)(GonzagoTimer*))FUN_00b638b0)(&local);
            return;
        }

        unsigned countBytes = count << 5;
        GonzagoTimer* split = (GonzagoTimer*)((char*)oldEnd - countBytes);
        ((void (__cdecl*)(void*, void*, void*, void*))FUN_00bf2840)
            (&value, split, oldEnd, oldEnd);
        GonzagoTimer* oldPos = pos;
        m_end = (GonzagoTimer*)((char*)m_end + countBytes);
        FUN_00bf2a10(pos, split, oldEnd);
        FUN_00bf28b0(oldPos, (char*)oldPos + countBytes, &local);
        ((void (__thiscall*)(GonzagoTimer*))FUN_00b638b0)(&local);
    }
}

// ---------------------------------------------------------------------------
// 0x00bf5420 - insert one copy of value before pos.
// ---------------------------------------------------------------------------
// @ 0x00bf5420
void TimerVec::insertOne(GonzagoTimer* pos, const GonzagoTimer* value)
{
    if (m_end != m_cap) {
        if (pos <= value && value < m_end)
            value = (GonzagoTimer*)((char*)value + 0x20);

        if (m_end != 0) {
            GonzagoTimer* prev = m_end - 1;
            m_end->m_vtable       = (void*)0x01465d54;
            m_end->m_refCount     = 0;
            m_end->mElapsedTimeLo = prev->mElapsedTimeLo;
            m_end->mElapsedTimeHi = prev->mElapsedTimeHi;
            m_end->mBaseTimeLo    = prev->mBaseTimeLo;
            m_end->mBaseTimeHi    = prev->mBaseTimeHi;
            m_end->mRunning       = prev->mRunning;
            m_end->mTimeFn        = prev->mTimeFn;
            m_end->m_vtable       = (void*)0x01464450;
        }

        FUN_00bf2a10(pos, (char*)m_end - 0x20, m_end);
        pos->mElapsedTimeLo = value->mElapsedTimeLo;
        pos->mElapsedTimeHi = value->mElapsedTimeHi;
        pos->mBaseTimeLo    = value->mBaseTimeLo;
        pos->mBaseTimeHi    = value->mBaseTimeHi;
        pos->mRunning       = value->mRunning;
        pos->mTimeFn        = value->mTimeFn;
        m_end = (GonzagoTimer*)((char*)m_end + 0x20);
        return;
    }

    unsigned size = (unsigned)((char*)m_end - (char*)m_begin) >> 5;
    unsigned newCap;
    if (size == 0)
        newCap = 1;
    else {
        newCap = size * 2;
        if (newCap == 0)
            newCap = 0;
    }

    GonzagoTimer* block = 0;
    if (newCap != 0)
        block = (GonzagoTimer*)FUN_00f473a0((int)(newCap << 5), "Simulator",
                                            0, 0, kAllocatorPath, 0xd1);

    GonzagoTimer* oldBegin = m_begin;
    GonzagoTimer* mid = (GonzagoTimer*)FUN_00bf2960(oldBegin, pos, block);
    FUN_00befb80(oldBegin, pos, block);

    if (mid != 0) {
        mid->m_vtable       = (void*)0x01465d54;
        mid->m_refCount     = 0;
        mid->mElapsedTimeLo = value->mElapsedTimeLo;
        mid->mElapsedTimeHi = value->mElapsedTimeHi;
        mid->mBaseTimeLo    = value->mBaseTimeLo;
        mid->mBaseTimeHi    = value->mBaseTimeHi;
        mid->mRunning       = value->mRunning;
        mid->mTimeFn        = value->mTimeFn;
        mid->m_vtable       = (void*)0x01464450;
    }

    GonzagoTimer* oldEnd = m_end;
    GonzagoTimer* newEnd =
        (GonzagoTimer*)FUN_00bf2960(pos, oldEnd, (char*)mid + 0x20);
    FUN_00befb80(pos, oldEnd, (char*)mid + 0x20);

    if (m_begin != 0 && *(int*)((char*)m_begin - 4) != 0)
        FUN_00f47380(m_begin);

    m_begin = block;
    m_end   = newEnd;
    m_cap   = (GonzagoTimer*)((char*)block + (newCap << 5));
}

// ---------------------------------------------------------------------------
// 0x00bf55d0 - reset the two global SPUI layout rbtrees.
// ---------------------------------------------------------------------------
// @ 0x00bf55d0
void FUN_00bf55d0()
{
    ((void (__thiscall*)(void*))FUN_00bf4a90)((void*)0x0168caf0);

    unsigned char* tree = (unsigned char*)0x0168cb0c;
    do {
        unsigned char* node = *(unsigned char**)(tree + 0x0c);
        while (node != 0) {
            unsigned char* next = *(unsigned char**)(node + 4);
            ((void (__thiscall*)(void*, void*))FUN_009a9600)(tree, *(void**)node);
            FUN_00f47380(node);
            node = next;
        }

        unsigned char* head = tree + 4;
        *(void**)(tree + 0x08) = head;
        *(void**)(tree + 0x0c) = 0;
        *(unsigned char*)(tree + 0x10) = 0;
        *(int*)(tree + 0x14) = 0;
        tree += 0x1c;
        *(void**)head = head;
    } while ((int)tree < 0x0168cb44);
}

// ---------------------------------------------------------------------------
// 0x00bf5630 - push a feedback object into the event/sound vectors.
// ---------------------------------------------------------------------------
// @ 0x00bf5630
void FeedbackSink::AddPair(void* obj)
{
    void* value = obj;

    if (obj != 0)
        ((void (__thiscall*)(void*))_vt(obj, 0))(obj);

    if (m_events.m_end < m_events.m_cap) {
        void** slot = m_events.m_end;
        m_events.m_end = slot + 1;
        if (slot != 0) {
            *slot = obj;
            if (obj != 0)
                ((void (__thiscall*)(void*))_vt(obj, 0))(obj);
        }
    }
    else {
        ((void (__thiscall*)(void*, void**, void* const&))FUN_00aea5d0)
            (&m_events, m_events.m_end, value);
    }

    if (value != 0)
        ((void (__thiscall*)(void*))_vt(value, 4))(value);

    void* entry = obj;
    void* id = ((void* (__thiscall*)(void*))_vt(this, 0x4c))(this);
    ((void (__thiscall*)(void*, void*))_vt(entry, 0x48))(entry, id);

    void* other = ((void* (__thiscall*)(void*, void*))_vt(obj, 0x0c))(obj, (void*)0x01186577);
    if (other != 0) {
        ((void (__thiscall*)(void*))_vt(other, 0xbc))(other);

        if (m_sounds.m_end < m_sounds.m_cap) {
            void** slot = m_sounds.m_end;
            m_sounds.m_end = slot + 1;
            if (slot != 0) {
                *slot = other;
                ((void (__thiscall*)(void*))_vt(other, 0xbc))(other);
            }
        }
        else {
            ((void (__thiscall*)(void*, void**, void* const&))FUN_00bab900)
                (&m_sounds, m_sounds.m_end, other);
        }

        ((void (__thiscall*)(void*))_vt(other, 0xc0))(other);
    }
}

// ---------------------------------------------------------------------------
// 0x00bf5720 - is there a city of this tribe on the given planet?
// ---------------------------------------------------------------------------
// @ 0x00bf5720
int PlanetChecker::CheckPlanet(void* obj)
{
    void* mgr = FUN_00b3d300();
    void* vec = ((void* (__thiscall*)(void*, void*, void*, void*, void*, void*))
                 FUN_00b21340)(mgr, (void*)0x00cd7d10, (void*)0x00d3d420,
                               (void*)0x00acdff0, (void*)0x00b1e500,
                               (void*)0x018c43e8);

    int count = (*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) >> 2;

    void* model = FUN_00b3d350();
    int continent = ((int (__thiscall*)(void*))FUN_00b88590)(model);

    for (int i = 0; i < count; ++i) {
        void* city = *(void**)(*(int*)((char*)vec + 4) + i * 4);
        int civ = ((int (__thiscall*)(void*))FUN_00bd9bf0)(city);
        if (civ != (int)this) {
            int c = FUN_00bd8210(city);
            if (c == continent)
                return 1;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00bf57b0 - create and initialise a vehicle noun.
// ---------------------------------------------------------------------------
// @ 0x00bf57b0
void* VehicleFactory::CreateVehicle(void* p2, void* p3, void* p4, void* p5,
                                    void* p6, void* p7)
{
    void* mgr = FUN_00b3d300();
    void* noun = ((void* (__thiscall*)(void*, void*))FUN_00b20c60)
                    (mgr, (void*)0x018c6de8);

    void* vehicle = 0;
    if (noun != 0) {
        vehicle = ((void* (__thiscall*)(void*, int))_vt(noun, 0x0c))(noun, 0x137e8e0);
        if (vehicle != 0)
            ((void (__thiscall*)(void*))_vt(vehicle, 0))(vehicle);
    }

    ((FeedbackSink*)this)->AddPair(vehicle);

    Vec3 pos;
    pos.x = *(float*)&p4;
    pos.y = *(float*)&p5;
    pos.z = *(float*)&p6;
    ((void (__thiscall*)(void*, void*, void*, Vec3))FUN_00ca6630)
        (vehicle, p3, p2, pos);

    void* spatial = (char*)vehicle + 0x34;
    ((void (__thiscall*)(void*, void*))_vt(spatial, 0x38))(spatial, p7);

    VehicleSnapshot snap;
    snap.m_alloc = 0;
    snap.m_pos.x = *(float*)0x0168c514;
    snap.m_pos.y = *(float*)0x0168c518;
    snap.m_pos.z = *(float*)0x0168c51c;
    snap.m_f24 = *(float*)0x01485720;
    snap.m_f70 = *(float*)0x01470f1c;
    snap.m_f74 = *(float*)0x013ec4b4;
    snap.m_f7c = *(float*)0x0146933c;
    snap.m_f80 = 0.0f;
    snap.m_i84 = 0;

    ((void (__thiscall*)(void*, VehicleSnapshot*))_vt(spatial, 0xdc))(spatial, &snap);

    if (snap.m_alloc != 0 && *(int*)((char*)snap.m_alloc - 4) != 0)
        FUN_00f47380(snap.m_alloc);

    ((void (__thiscall*)(void*, int, float))_vt(spatial, 0xc4))(spatial, 0, 0.0f);

    void* behavior = FUN_00b3d260();
    ((void (__thiscall*)(void*, void*))_vt(behavior, 0x38))
        (behavior, (char*)vehicle + 0x5d0);

    ((void (__thiscall*)(void*, void*))_vt(vehicle, 0x0c))(vehicle, (void*)0x01186577);

    if ((unsigned char)(int)p2 != 0) {
        void* planet = FUN_01021260();
        if (planet != 0) {
            void* id = ((void* (__thiscall*)(void*))_vt(this, 0x4c))(this);
            void* planetData = ((void* (__thiscall*)(void*, void*))FUN_00c71040)
                                   (planet, id);
            if (planetData != 0) {
                void* recorder = FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
                void* snapshot = 0;
                if (recorder != 0)
                    snapshot = ((void* (__thiscall*)(void*, void*))FUN_00ff0db0)
                                   (recorder, vehicle);

                ((void (__thiscall*)(void*, void*))FUN_00ff2d20)(planetData, snapshot);
                ((void (__thiscall*)(void*, void*))FUN_00c9eae0)(vehicle, planetData);
                ((void (__thiscall*)(void*, void*))FUN_00a110b0)(vehicle, snapshot);
            }
        }
    }

    ((void (__thiscall*)(void*))_vt(vehicle, 4))(vehicle);
    return vehicle;
}

// ---------------------------------------------------------------------------
// 0x00bf59d0 - recompute the per-city minimum distance to this tribe.
// ---------------------------------------------------------------------------
// @ 0x00bf59d0
void CityThing::UpdateDistances()
{
    VecC pts;
    unsigned char flag;
    int count = (int)((char*)m_citiesEnd - (char*)m_citiesBegin) >> 2;

    ((VecC* (__thiscall*)(VecC*, unsigned, unsigned char*))FUN_006a46a0)
        (&pts, (unsigned)count, &flag);

    if (count > 0) {
        Vec3* dst = pts.m_data;
        for (int i = 0; i < count; ++i) {
            void* city = m_citiesBegin[i];
            void* sub = (char*)city + 0x120;
            Vec3* src = (Vec3*)((void* (__thiscall*)(void*))_vt(sub, 0x2c))(sub);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            ++dst;
        }
    }

    void* model = FUN_00b3d350();
    void* mgr = FUN_00b3d300();
    void** civVec = (void**)((void* (__thiscall*)(void*))FUN_00b25ca0)(mgr);

    void** civIt  = (void**)*civVec;
    void** civEnd = (void**)civVec[1];

    for (; civIt != civEnd; ++civIt) {
        void* civ = *civIt;
        if (civ == this)
            continue;

        void** cityIt  = *(void***)((char*)civ + 0x9c);
        void** cityEnd = *(void***)((char*)civ + 0xa0);
        for (; cityIt != cityEnd; ++cityIt) {
            void* city = *cityIt;
            void* sub = (char*)city + 0x120;
            Vec3* src = (Vec3*)((void* (__thiscall*)(void*))_vt(sub, 0x2c))(sub);

            Vec3 cur;
            cur.x = src->x;
            cur.y = src->y;
            cur.z = src->z;

            float best = 3.402823466e38f;
            for (int i = 0; i < count; ++i) {
                float d = ((float (__thiscall*)(void*, Vec3*, Vec3*))FUN_00b81470)
                              (model, &cur, &pts.m_data[i]);
                if (d < best)
                    best = d;
            }

            ((void (__thiscall*)(void*))_vt(city, 0))(city);
            void* key = city;
            float* slot = ((float* (__thiscall*)(void*, void*))FUN_00bf5050)
                              (&m_map, &key);
            *slot = best;
            ((void (__thiscall*)(void*))_vt(city, 4))(city);
        }
    }

    if (pts.m_data != 0 && *(int*)((char*)pts.m_data - 4) != 0)
        FUN_00f47380(pts.m_data);
}

// ---------------------------------------------------------------------------
// 0x00bf5b90 - read the stored distance for a city.
// ---------------------------------------------------------------------------
// @ 0x00bf5b90
float CityThing::GetDistance(void* key)
{
    if (key != 0)
        ((void (__thiscall*)(void*))_vt(key, 0))(key);

    void* local = key;
    float* slot = ((float* (__thiscall*)(void*, void*))FUN_00bf5050)(&m_map, &local);
    float value = *slot;

    if (key != 0)
        ((void (__thiscall*)(void*))_vt(key, 4))(key);

    return value;
}

// ---------------------------------------------------------------------------
// 0x00bf5be0 - city event handler.
// ---------------------------------------------------------------------------
// @ 0x00bf5be0
bool CityEventSub::OnEvent(int eventId, void* data)
{
    if (eventId == 0x1a0219e) {
        if (*(void**)((char*)data + 0x10) != 0 && *(int*)((char*)data + 8) == 4)
            FUN_00bf49e0(*(void**)((char*)data + 0x10));
    }
    else if (eventId == 0x20c089c) {
        void* comm = FUN_00b3d4a0();
        if (((unsigned char (__thiscall*)(void*))FUN_00ae9390)(comm) == 0) {
            ((void (__thiscall*)(void*))FUN_00bf0f90)((char*)this - 0x38);
            return true;
        }
    }
    else if (eventId == 0x6524f8f) {
        if (m_civ != 0) {
            int civ = ((int (__thiscall*)(void*))FUN_00bd9bf0)(m_civ);
            if (civ == (int)((char*)this - 0x38) && m_flag51 != 0 && m_soundId != -1)
                ((void (__thiscall*)(void*, int, void*))FUN_00be5be0)
                    (m_civ, m_soundId, (void*)0x0168c514);
        }

        void* old = m_civ;
        m_civ = 0;
        if (old != 0)
            ((void (__thiscall*)(void*))_vt(old, 4))(old);
        m_soundId = -1;
        return true;
    }
    return true;
}
