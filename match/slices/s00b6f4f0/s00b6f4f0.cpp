// Slice s00b6f4f0: mission-manager helpers -- ARC vector copy/filter, per-object notifications,
// mission-card panel refresh, spin/hash lookups, and vtable walks.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;

void* __cdecl opnew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  __cdecl opdel(void* p);                                                                     // 0x00f47380
#define ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define SPORE_NEW(n) opnew((n), "Simulator", 0, 0, ALLOC_FILE, 0xd1)

// reference-counted interface
struct IRefLite {
    virtual int  AddRef();                 // 0x00
    virtual int  Release();                // 0x04
    virtual void g2();                     // 0x08
    virtual void* Cast(unsigned id);       // 0x0c
    virtual void g4(); virtual void g5();  // 0x10,0x14
    virtual void g6();                     // 0x18
    virtual void Notify(unsigned a);       // 0x1c
    virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
    virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
    virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
    virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
    virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31();
    virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
    virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39();
    virtual void f40(); virtual void f41(); virtual void f42(); virtual void f43();
    virtual void f44(); virtual void f45();
    virtual void NotifyB8();               // 0xb8
};

struct ARCObj { IRefLite* p; };

// @ 0x00b6f4f0
ARCObj* __cdecl FUN_00b6f4f0(ARCObj* first, ARCObj* last, ARCObj* dest, IRefLite** skip)
{
    for (; first != last; ++first) {
        IRefLite* p = first->p;
        if (p != *skip) {
            IRefLite* old = dest->p;
            if (p != old) {
                if (p) p->AddRef();
                dest->p = p;
                if (old) old->Release();
            }
            dest++;
        }
    }
    return dest;
}

// @ 0x00b6f550
bool __cdecl FUN_00b6f550(unsigned a, IRefLite** p)
{
    if (*p) (*p)->Notify(a);
    return true;
}

// @ 0x00b6f7d0
struct MMgr {
    void NotifyAll();               // 0x00b6f7d0
    bool IsTracked(void* p);        // 0x00b6f800
    void ClearCard(void* p);        // 0x00b6f820
};
// @ 0x00b6f7d0
void __thiscall MMgr::NotifyAll()
{
    IRefLite** end = *(IRefLite***)((char*)this + 0x18);
    for (IRefLite** p = *(IRefLite***)((char*)this + 0x14); p != end; p++)
        (*p)->NotifyB8();
}

// @ 0x00b6f800
bool __thiscall MMgr::IsTracked(void* p)
{
    if (p == *(void**)((char*)this + 0x68)) return true;
    return (char)(p == *(void**)((char*)this + 0x6c));
}

// @ 0x00b6f820
extern void* __cdecl FUN_00b3d400();
struct CardPanel {
    void RemoveMissionCard(void* card);                                              // 0x00e17fb0 (thiscall)
};
void __thiscall MMgr::ClearCard(void* p)
{
    if (p == *(void**)((char*)this + 0x68)) {
        if (FUN_00b3d400()) {
            ((CardPanel*)FUN_00b3d400())->RemoveMissionCard(*(void**)((char*)this + 0x68));
        }
        IRefLite* c = *(IRefLite**)((char*)this + 0x68);
        if (c) {
            *(void**)((char*)this + 0x68) = 0;
            c->Release();
        }
    }
}

// @ 0x00b6f860
bool __cdecl FUN_00b6f860(unsigned a, ARCObj** vec)
{
    ARCObj* last = vec[1];
    for (ARCObj* p = vec[0]; p != last; p++)
        if (p->p) p->p->Notify(a);
    return true;
}

// @ 0x00b6f890
struct SmallC {
    void* p0;
    IRefLite* p4;
    int   p8;
    static SmallC* __stdcall Create(SmallC* src);   // 0x00b6f890
};
// @ 0x00b6f890
SmallC* __stdcall SmallC::Create(SmallC* src)
{
    SmallC* p = (SmallC*)SPORE_NEW(0xc);
    if (p) {
        p->p0 = src->p0;
        p->p4 = src->p4;
        if (p->p4) p->p4->AddRef();
    }
    p->p8 = 0;
    return p;
}

// @ 0x00b6f8e0
struct SmallE {
    void* p0; void* p4; void* p8; IRefLite* pC; int p10;
};
// @ 0x00b6f8e0
SmallE* __stdcall FUN_00b6f8e0(SmallE* src)
{
    SmallE* p = (SmallE*)SPORE_NEW(0x14);
    if (p) {
        p->p0 = src->p0;
        p->p4 = src->p4;
        p->p8 = src->p8;
        p->pC = src->pC;
        if (p->pC) p->pC->AddRef();
    }
    p->p10 = 0;
    return p;
}

// ------------------------------------------------------------------ remaining helpers

// ---- object model -------------------------------------------------------------------------
// The class is SP::cSPMissionManagerBase (a cGonzagoSimulator). Only the fields this slice
// touches are named. An "ARC" (EA::AutoRefCount<T>) is a single pointer to a ref-counted object
// whose vtable slot 0 is AddRef and slot 1 (+0x04) is Release.
//
//   +0x14 / +0x18  eastl::vector<AutoRefCount<...>> of mission/tool objects (mpBegin/mpEnd)
//   +0x28          eastl::hashtable<uint, pair<uint_const, AutoRefCount<cSPToolStrategy>>>
//                  node = { key(+0); ARC value(+4); next(+8) }   (bucket ptr +4, count +8, +0xc)
//   +0x48          eastl::hashtable<TripleKey, AutoRefCount<...>>
//                  node = { k0(+0); k1(+4); k2(+8); ARC value(+0xc); next(+0x10) }
//   +0x68 / +0x6c  mission-card handles (ARC)

struct TripleKey { unsigned k0, k1, k2; };

struct NodeUIntARC {              // node of the +0x28 hashtable
    unsigned  key;                // +0x00
    IRefLite* value;              // +0x04  (AutoRefCount payload)
    NodeUIntARC* next;            // +0x08
};

struct NodeTripleARC {            // node of the +0x48 hashtable
    unsigned  k0, k1, k2;         // +0x00..+0x08
    IRefLite* value;              // +0x0c
    NodeTripleARC* next;          // +0x10
};

struct HashUIntARC {              // +0x28 hashtable header
    void*         mAlloc;         // +0x00
    NodeUIntARC** mpBucket;       // +0x04
    unsigned      mnBucketCount;  // +0x08
    unsigned      mnElementCount; // +0x0c
    void*         mHashPolicy;    // +0x10
};

struct HashTripleARC {
    void*           mAlloc;         // +0x00
    NodeTripleARC** mpBucket;       // +0x04
    unsigned        mnBucketCount;  // +0x08
    unsigned        mnElementCount; // +0x0c
    void*           mHashPolicy;    // +0x10
};

// Lookup/hidden-return iterator written by eastl::hashtable::find / DoInsertValue: {node, bucket}.
struct HashIt { void* node; void* bucket; };
// DoInsertValue's out iterator adds an inserted flag in the byte after the bucket slot.
struct InsIt  { void* node; void* bucket; unsigned char flag; };

// The serializer interface used by the stream helpers. Slots are the retail ISerializer /
// ISerializerStream vtables; only the ones this slice calls are named.
struct IStreamHandle;             // EA::IO stream (opaque, passed to the Read/Write helpers)
struct ISerializerStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual IStreamHandle* GetStream();               // slot 6 (+0x18)
};
struct ISerializer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void EndItem();                           // slot 7  (+0x1c)
    virtual ISerializerStream* GetStreamHolder();     // slot 8  (+0x20)
    virtual void v9();                                // slot 9  (+0x24)
    virtual IRefLite* ReadObject(unsigned classid, IRefLite** out, int flags); // slot 10 (+0x28)
    virtual void WriteObject(IRefLite* obj);          // slot 11 (+0x2c)
};

// ---- callees (retail addresses) -----------------------------------------------------------
extern "C" bool __cdecl ReadInt32(void* stream, void* dst, int count, int endian);          // 0x0093a780
extern "C" bool __cdecl WriteUint32(void* stream, const void* src, int count, int endian);  // 0x0093aa70
struct HashFind {
    HashIt* find(HashIt* out, const unsigned* key);                                  // 0x00645ed0
};
struct HashOps {
    void DoFreeNodes(void** bucket, unsigned count);                                 // 0x00961d60
};
struct NodeAlloc {
    void GetNeeded(void* out, unsigned buckets, unsigned elems, int add);            // 0x00921440
};
struct RehashA {
    void rehash(unsigned n);                                                         // 0x00b3f1b0  (this = hashtable)
};
struct RehashB {
    void rehash(unsigned n);                                                         // 0x00b4fb20  (this = hashtable)
};
// eastl::basic_string<wchar_t> (12 bytes) + its out-of-line members.
struct WString16 {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void RangeInitialize(const wchar_t* s);   // 0x00579a90
    void CopyCtor(const WString16& o);        // 0x0056e2d0
};
WString16* __cdecl ConvertToString16(WString16* out, const char* s, int n);  // 0x0093c5a0
char __cdecl FUN_00ac8050(void* obj, int zero, void* triple);                // 0x00ac8050// vtable used by 0x00b70410 for the "set/compare name" object.
struct NameObj {
    virtual void SetName(const wchar_t* s);   // slot 0
    virtual void GetName(const wchar_t* s);   // slot 1
};
void __cdecl FUN_00ae2ed0(void* ser, void* out);     // 0x00ae2ed0  read triple from stream
void __cdecl FUN_00ae2e40(void* ser, void* node);    // 0x00ae2e40  write triple to stream
void __cdecl FUN_00aea5d0(void* vecEnd, void* pV);   // 0x00aea5d0  vector push_back grow
struct VecOps {
    void __thiscall Dtor();                                                          // 0x00ae6970  eastl vector range dtor (this = &vec)
};
struct VecOps2 {
    void __thiscall EraseRange(void* first, void* last);                             // 0x00e25bd0 (this = &vec)
};
void* __cdecl FUN_00b3d400();                        // 0x00b3d400  mission-card panel getter
void* __cdecl FUN_00b3d330();                        // 0x00b3d330  SimTicker getter
void* __cdecl FUN_00b3d300();                        // 0x00b3d300  noun-manager getter
// thiscall callees modelled as members of dummy structs (this = the object in ecx).
struct StrategyCallee {
    float BestTime();                                                                // 0x00c2e9b0
};
struct TutCallee {
    void Init(unsigned id);                                                          // 0x00c2fd20
};
struct PanelCallee {
    void AddMissionCard(void* card, int a, int b, int c);  // 0x00e18200 (4 args)
    void RemoveMissionCard(void* card);               // 0x00e17fb0
    bool HasMissionCard(void* card);                  // 0x00e15cd0
    void Refresh();                                   // 0x00e17df0
};
// cdecl thiscall-style helpers (ecx = first arg) modelled via free __fastcall with a dummy edx:
// expected by the retail /GL build.  Rebound below where used.
struct MessageServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                       virtual void v4(); virtual void v5(); virtual void v6();
                       virtual void Send(unsigned a, int b, int c, int d); }; // slot 6 (+0x18)
MessageServer* __cdecl FUN_0067dcc0();               // 0x0067dcc0 MessageServer()

// noun-manager member wrappers (this = noun manager, ecx)
struct NounMgr {
    void* __thiscall CreateNoun(unsigned type);   // 0x00b20c60
    void  __thiscall RemoveNoun(void* noun);      // 0x00b225d0
    void  __thiscall RemoveNounType(unsigned id); // 0x00b227c0
};

// SimTicker virtual calls (this = SimTicker singleton)
struct SimTicker { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                   virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                   virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
                   virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                   virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
                   virtual void AddTicker(void* obj);       // slot 0x50
                   virtual void RemoveTicker(void* obj); }; // slot 0x54

// Mission strategy / tutorial mission interfaces (only virtual slots touched are named).
struct MissionStrategy {              // AutoRefCount payload of the +0x28 map
    virtual int  AddRef();            // +0x00
    virtual void Release();           // +0x04
    virtual void g08();               // +0x08
    virtual void* Cast(unsigned id);  // +0x0c
    virtual void g10(); virtual void g14(); virtual void g18();
    virtual void Notify(unsigned a);  // +0x1c
    virtual void g20(); virtual void g24(); virtual void g28();
    virtual void g2c(); virtual void g30(); virtual void g34(); virtual void g38();
    virtual void g3c(); virtual void g40(); virtual void g44(); virtual void g48();
    virtual void g4c(); virtual void g50(); virtual void g54(); virtual void g58();
    virtual void g5c(); virtual void g60(); virtual void g64(); virtual void g68();
    virtual void g6c(); virtual void g70(); virtual void g74();
    virtual void Step();              // +0x78
};
struct TutorialMission {
    virtual int  AddRef();            // +0x00
    virtual void Release();           // +0x04
    virtual void g08();               // +0x08
    virtual void* Cast(unsigned id);  // +0x0c
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
    virtual void g30(); virtual void g34(); virtual void g38(); virtual void g3c();
    virtual void g40(); virtual void g44(); virtual void g48(); virtual void g4c();
    virtual void g50(); virtual void g54(); virtual void g58(); virtual void g5c();
    virtual void g60(); virtual void g64(); virtual void g68(); virtual void g6c();
    virtual void g70(); virtual void g74();
    virtual void* GetNextMission();   // +0x78
};

// cVarListSerializer (0x40 bytes of state) + its out-of-line ctor/serialize.
struct cVarListSerializer {
    unsigned mData[0x40 / 4];
    cVarListSerializer(void* object, unsigned listId, unsigned id);  // 0x00692f90
    void Serialize(ISerializer* s);                                  // 0x00692900
};

// ---- free hashtable helpers (this = the hashtable header, ecx) -----------------------------

// 0x00b6f940  DoInsertValue(outIter, &value, flags) for the +0x28<uint,ARC> hashtable.
struct InsUIntARC {
    void Ins(InsIt* out, NodeUIntARC* value, int flags);                             // 0x00b6f940
};

// 0x00b6fe40  DoInsertValue(outIter, &value, flags) for the +0x48<TripleKey,ARC> hashtable.
struct InsTripleARC {
    void Ins(InsIt* out, NodeTripleARC* value, int flags);                           // 0x00b6fe40
};

// 0x00b6fdf0  free every node of a TripleKey hashtable (the value is an AutoRefCount).
struct TriOps {
    void __thiscall FreeNodes(void** bucket, unsigned count);                        // 0x00b6fdf0
};

// ---- the mission manager ------------------------------------------------------------------
struct MissionMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual unsigned g28(int a);                   // slot 10 (+0x28)
    virtual void g2c();                            // slot 11 (+0x2c)

    char            mPad00[0x14 - 4];               // vptr at 0, so four bytes are consumed
    IRefLite**      mObjectsBegin;                 // +0x14
    IRefLite**      mObjectsEnd;                   // +0x18
    IRefLite**      mObjectsCapacity;              // +0x1c
    char            mPad20[0x28 - 0x20];
    HashUIntARC     mStrategyMap;                  // +0x28
    char            mPad3c[0x48 - 0x28 - sizeof(HashUIntARC)];
    HashTripleARC   mTripleMap;                    // +0x48
    char            mPad5c[0x68 - 0x48 - sizeof(HashTripleARC)];
    IRefLite*       mCard68;                       // +0x68
    IRefLite*       mCard6c;                       // +0x6c
    unsigned char   mFlag70;                       // +0x70

    void __thiscall Write(ISerializer* s);              // 0x00b6f570
    void __thiscall RefreshAll(int a, int b);           // 0x00b6f650
    void __thiscall RefreshCards();                     // 0x00b6f760
    IRefLite* __thiscall LookupStrategy(unsigned key);  // 0x00b6fa60
    void __thiscall Shutdown();                         // 0x00b70070
    void __thiscall OnStrategyGone(unsigned id);        // 0x00b700f0
    void __thiscall Dtor();                             // 0x00b705a0
    IRefLite* __thiscall Hint(unsigned key);            // 0x00b706a0
    unsigned __thiscall HintClear(unsigned id);         // 0x00b707a0
};

// @ 0x00b6f570  write the serializer-id then the var list.
void __thiscall MissionMgr::Write(ISerializer* s)
{
    ISerializerStream* holder = s->GetStreamHolder();
    IStreamHandle* stream = holder->GetStream();
    unsigned id = 0x54361546;
    WriteUint32(stream, &id, 1, 0);
    cVarListSerializer ser(this, 0x0156b198, 0x01a80d26);
    ser.Serialize(s);
}

// @ 0x00b6f650  scan the tracked objects for the one with the largest best-time and make it the
//              active mission card (removing/re-adding it on the card panel).
void __thiscall MissionMgr::RefreshAll(int a, int b)
{
    (void)a; (void)b;
    PanelCallee* panel = (PanelCallee*)FUN_00b3d400();
    MissionStrategy* best = 0;
    float bestTime = 0.0f;
    for (IRefLite** it = mObjectsBegin; it != mObjectsEnd; ++it) {
        if (!*it) continue;
        MissionStrategy* m = (MissionStrategy*)(*it)->Cast(0xd4066db3);
        if (!m) continue;
        float t = ((StrategyCallee*)m)->BestTime();
        if (bestTime < t) { best = m; bestTime = t; }
    }
    if (best != (MissionStrategy*)mCard6c) {
        if (panel && mCard6c)
            panel->RemoveMissionCard(mCard6c);
        IRefLite* old = mCard6c;
        if ((void*)best != (void*)old) {
            if (best) best->AddRef();
            mCard6c = (IRefLite*)best;
            if (old) old->Release();
        }
        if (!panel) return;
        if (mCard6c && !panel->HasMissionCard(mCard6c)) {
            panel->AddMissionCard(mCard6c, 0, 1, 0);
            MessageServer* ms = FUN_0067dcc0();
            ms->Send(0x06417958, 0, 0, 0);
        }
    }
    if (panel) panel->Refresh();
}

// @ 0x00b6f760  re-register both tracked mission cards with the SimTicker/card panel.
void __thiscall MissionMgr::RefreshCards()
{
    SimTicker* ticker = (SimTicker*)FUN_00b3d330();
    ticker->AddTicker(this);
    PanelCallee* panel = (PanelCallee*)FUN_00b3d400();
    if (!panel) return;
    if (mCard68 && !panel->HasMissionCard(mCard68))
        panel->AddMissionCard(mCard68, 0, 1, 0);
    if (mCard6c && !panel->HasMissionCard(mCard6c))
        panel->AddMissionCard(mCard6c, 0, 1, 0);
}

// @ 0x00b6fa60  look up a strategy in the +0x28 map (returns its AutoRefCount payload or null).
IRefLite* __thiscall MissionMgr::LookupStrategy(unsigned key)
{
    HashUIntARC* map = &mStrategyMap;
    HashIt it;
    HashIt* r = ((HashFind*)map)->find(&it, &key);
    if (r->node != map->mpBucket[map->mnBucketCount])
        return *(IRefLite**)((char*)r->node + 4);
    return 0;
}

// @ 0x00b6faa0  erase every entry with the given key from a uint hashtable; return count removed.
// `this` is the hashtable header itself (HashUIntARC layout), not the owning MissionMgr.
struct StratMapErase {
    int __thiscall Erase(unsigned* key);                // 0x00b6faa0
};

int __thiscall StratMapErase::Erase(unsigned* key)
{
    HashUIntARC* map = (HashUIntARC*)this;
    unsigned before = map->mnElementCount;
    unsigned idx    = *key % map->mnBucketCount;
    NodeUIntARC** pp = &map->mpBucket[idx];
    if (*pp) {
        while (*pp && (*pp)->key != *key)
            pp = &(*pp)->next;
        while (*pp && (*pp)->key == *key) {
            NodeUIntARC* node = *pp;
            *pp = node->next;
            IRefLite* v = node->value;
            if (v) v->Release();
            opdel(node);
            map->mnElementCount--;
        }
    }
    return before - map->mnElementCount;
}

// @ 0x00b6fb20  read a <uint, AutoRefCount<strategy>> map from the stream.
void __cdecl FUN_00b6fb20(ISerializer* s, HashUIntARC* map)
{
    ((HashOps*)map)->DoFreeNodes((void**)map->mpBucket, map->mnBucketCount);
    map->mnElementCount = 0;
    unsigned count = 0;
    IStreamHandle* stream = s->GetStreamHolder()->GetStream();
    ReadInt32(stream, &count, 1, 0);
    IRefLite* obj = 0;
    for (unsigned i = 0; i < count; i++) {
        unsigned key = 0;
        stream = s->GetStreamHolder()->GetStream();
        ReadInt32(stream, &key, 1, 0);
        s->EndItem();
        if (obj) { obj = 0; obj->Release(); }
        s->ReadObject(0x14066ce5, &obj, 0);
        s->EndItem();
        NodeUIntARC value;
        value.key = key;
        value.value = obj;
        value.next = 0;
        InsIt it;
        ((InsUIntARC*)map)->Ins(&it, &value, 0);
        if (it.flag == 0) {
            NodeUIntARC* node = (NodeUIntARC*)it.node;
            IRefLite* old = node->value;
            if (obj != old) {
                if (obj) obj->AddRef();
                node->value = obj;
                if (old) old->Release();
            }
        }
        if (obj) obj->Release();
    }
    s->EndItem();
}

// @ 0x00b6fc90  write a <uint, AutoRefCount<strategy>> map to the stream.
void __cdecl FUN_00b6fc90(ISerializer* s, HashUIntARC* map)
{
    unsigned count = map->mnElementCount;
    IStreamHandle* stream = s->GetStreamHolder()->GetStream();
    WriteUint32(stream, &count, 1, 0);

    NodeUIntARC** bucket = map->mpBucket;
    NodeUIntARC*  node = bucket[0];
    if (!node) {
        if (bucket[1] != 0) {
            bucket += 1;
        } else {
            do { ++bucket; } while (bucket[0] == 0);
        }
        node = bucket[0];
    }
    NodeUIntARC* end = map->mpBucket[map->mnBucketCount];
    while (node != end) {
        unsigned key = node->key;
        stream = s->GetStreamHolder()->GetStream();
        WriteUint32(stream, &key, 1, 0);
        s->EndItem();
        IRefLite* obj = 0;
        if (node->value) obj = (IRefLite*)((MissionStrategy*)node->value)->Cast(0x179c807);
        s->WriteObject(obj);
        s->EndItem();
        node = node->next;
        if (!node) do { ++bucket; node = bucket[0]; } while (!node);
    }
    s->EndItem();
}

// @ 0x00b6fd80  broadcast a notification to every strategy in the +0x48 triple map.
bool __cdecl FUN_00b6fd80(unsigned a, HashTripleARC* map)
{
    NodeTripleARC** bucket = map->mpBucket;
    NodeTripleARC*  node = bucket[0];
    if (!node) {
        if (bucket[1] != 0) {
            bucket += 1;
        } else {
            do { ++bucket; } while (bucket[0] == 0);
        }
        node = bucket[0];
    }
    NodeTripleARC* end = map->mpBucket[map->mnBucketCount];
    while (node != end) {
        if (node->value) ((MissionStrategy*)node->value)->Notify(a);
        node = node->next;
        if (!node) do { ++bucket; node = bucket[0]; } while (!node);
    }
    return true;
}

// @ 0x00b6ff20  find a strategy entry in the +0x28 map, inserting the key on miss.
struct StratMapEntry {
    IRefLite** __thiscall Lookup(unsigned* key);        // 0x00b6ff20
};

IRefLite** __thiscall StratMapEntry::Lookup(unsigned* key)
{
    HashUIntARC* self = (HashUIntARC*)this;
    HashIt it;
    ((HashFind*)self)->find(&it, key);
    if (it.node != self->mpBucket[self->mnBucketCount])
        return (IRefLite**)((char*)it.node + 4);
    NodeUIntARC value;
    value.key = *key;
    value.value = 0;
    value.next = 0;
    HashIt res;
    ((InsUIntARC*)self)->Ins((InsIt*)&res, &value, 0);
    if (value.value) value.value->Release();
    return (IRefLite**)((char*)res.node + 4);
}

// @ 0x00b6ffa0  write the +0x48 map (3-uint keys, referenced objects) to the stream.
void __cdecl FUN_00b6ffa0(ISerializer* s, HashTripleARC* map)
{
    unsigned count = map->mnElementCount;
    IStreamHandle* stream = s->GetStreamHolder()->GetStream();
    WriteUint32(stream, &count, 1, 0);
    for (unsigned b = 0; b <= map->mnBucketCount; b++) {
        for (NodeTripleARC* node = map->mpBucket[b]; node != 0; node = node->next) {
            FUN_00ae2e40(s, node);
            s->EndItem();
            IRefLite* obj = 0;
            if (node->value) obj = (IRefLite*)((MissionStrategy*)node->value)->Cast(0x179c807);
            s->WriteObject(obj);
            s->EndItem();
        }
    }
    s->EndItem();
}

// @ 0x00b70070  tear the manager down: unregister from the ticker, free all four containers,
//              release the card handle and remove the noun.
void __thiscall MissionMgr::Shutdown()
{
    SimTicker* ticker = (SimTicker*)FUN_00b3d330();
    ticker->RemoveTicker(this);
    ((VecOps2*)&mObjectsBegin)->EraseRange(mObjectsBegin, mObjectsEnd);
    ((HashOps*)&mStrategyMap)->DoFreeNodes((void**)mStrategyMap.mpBucket, mStrategyMap.mnBucketCount);
    mStrategyMap.mnElementCount = 0;
    ((TriOps*)&mTripleMap)->FreeNodes((void**)mTripleMap.mpBucket, mTripleMap.mnBucketCount);
    mTripleMap.mnElementCount = 0;
    if (mCard68) {
        IRefLite* c = mCard68;
        mCard68 = 0;
        c->Release();
    }
    NounMgr* nm = (NounMgr*)FUN_00b3d300();
    nm->RemoveNounType(0x14066ce5);
}

// @ 0x00b700f0  a strategy object has gone away: drop it from the object vector, erase it from
//              the +0x28 map and remove its noun.
void __thiscall MissionMgr::OnStrategyGone(unsigned id)
{
    HashUIntARC* map = &mStrategyMap;
    HashIt it;
    HashIt* r = ((HashFind*)map)->find(&it, &id);
    if (r->node == map->mpBucket[map->mnBucketCount]) return;
    IRefLite* obj = *(IRefLite**)((char*)r->node + 4);
    if (!obj) return;
    IRefLite* nounObj = (IRefLite*)((MissionStrategy*)obj)->Cast(0xd4066db3);
    if (!nounObj) return;

    IRefLite** end = mObjectsEnd;
    IRefLite** p = mObjectsBegin;
    while (p != end && *p != nounObj) ++p;
    if (p != end) {
        IRefLite* skip = 0;
        FUN_00b6f4f0((ARCObj*)p + 1, (ARCObj*)end, (ARCObj*)p, &skip);
    }
    ((VecOps2*)&mObjectsBegin)->EraseRange(p, end);
    unsigned key = (unsigned)((char*)nounObj + 0x78);
    ((StratMapErase*)&mStrategyMap)->Erase(&key);
    NounMgr* nm = (NounMgr*)FUN_00b3d300();
    nm->RemoveNoun(nounObj);
    this->g28(0);
}

// @ 0x00b70290  read the +0x48 map (3-uint keys) from the stream.
void __cdecl FUN_00b70290(ISerializer* s, HashTripleARC* map)
{
    ((TriOps*)map)->FreeNodes((void**)map->mpBucket, map->mnBucketCount);
    map->mnElementCount = 0;
    unsigned count = 0;
    IStreamHandle* stream = s->GetStreamHolder()->GetStream();
    ReadInt32(stream, &count, 1, 0);
    for (unsigned i = 0; i < count; i++) {
        TripleKey key;
        key.k0 = 0; key.k1 = 0; key.k2 = 0;
        FUN_00ae2ed0(s, &key);
        s->EndItem();
        IRefLite* obj = 0;
        s->ReadObject(0x7406a570, 0, 0);
        s->ReadObject(0x7406a570, &obj, 0);
        s->EndItem();
        NodeTripleARC entry;
        entry.k0 = key.k0; entry.k1 = key.k1; entry.k2 = key.k2;
        entry.value = obj;
        entry.next = 0;
        InsIt it;
        ((InsTripleARC*)map)->Ins(&it, &entry, 0);
        if (obj) obj->Release();
    }
    s->EndItem();
}

// @ 0x00b70410  does the +0x48 map hold a live entry matching the given name/triple?
// @ 0x00b70410  does the +0x48 map hold a live entry whose key string differs from the given
//              name?  (Walks the buckets comparing each node's stored name via 0x00ac8050.)
bool __cdecl FUN_00b70410(void* nameObj, unsigned name, HashTripleARC* map)
{
    bool result = true;
    if (map->mnElementCount != 0) {
        WString16 ws;
        ws.mpBegin = 0; ws.mpEnd = 0; ws.mpCapacity = 0;
        if (name)
            ConvertToString16(&ws, (const char*)name, -1);
        else
            ws.RangeInitialize(0);
        WString16 copy;
        copy.CopyCtor(ws);
        if ((ws.mpCapacity - ws.mpBegin) > 1 && ws.mpBegin) opdel(ws.mpBegin);

        ((NameObj*)nameObj)->SetName(copy.mpBegin ? copy.mpBegin : L"");

        NodeTripleARC** bucket = map->mpBucket;
        NodeTripleARC*  node = *bucket;
        if (!node) {
            if (bucket[1] != 0) { bucket += 1; }
            else { do { ++bucket; } while (*bucket == 0); }
            node = *bucket;
        }
        NodeTripleARC* end = map->mpBucket[map->mnBucketCount];
        while (node != end) {
            if (!result) {
                result = false;
            } else {
                result = FUN_00ac8050(nameObj, 0, (char*)node + 0xc) != 0;
            }
            node = node->next;
            while (!node) { ++bucket; node = *bucket; }
        }
        ((NameObj*)nameObj)->GetName(copy.mpBegin ? copy.mpBegin : L"");
        if ((copy.mpCapacity - copy.mpBegin) > 1 && copy.mpBegin) opdel(copy.mpBegin);
    }
    return result;
}

// @ 0x00b705a0  destructor: reset the three vtables, release the card handles, free containers.
void __thiscall MissionMgr::Dtor()
{
    *(void**)this                 = (void*)0x01464e18;
    *(void**)((char*)this + 8)    = (void*)0x01464df4;
    *(void**)((char*)this + 0x10) = (void*)0x01464de4;
    if (mCard6c) mCard6c->Release();
    if (mCard68) mCard68->Release();
    HashTripleARC* tm = &mTripleMap;
    ((TriOps*)tm)->FreeNodes((void**)tm->mpBucket, tm->mnBucketCount);
    tm->mnElementCount = 0;
    if (tm->mnBucketCount > 1) opdel(tm->mpBucket);
    HashUIntARC* sm = &mStrategyMap;
    ((HashOps*)sm)->DoFreeNodes((void**)sm->mpBucket, sm->mnBucketCount);
    sm->mnElementCount = 0;
    if (sm->mnBucketCount > 1) opdel(sm->mpBucket);
    ((VecOps*)&mObjectsBegin)->Dtor();
    *(void**)((char*)this + 0x10) = (void*)0x013eb394;
    *(void**)((char*)this + 8)    = (void*)0x013eb938;
    *(void**)this                 = (void*)0x013ec458;
}

// @ 0x00b706a0  hint: create a tutorial-mission noun for the given tool id and remember it.
IRefLite* __thiscall MissionMgr::Hint(unsigned key)
{
    unsigned keyLocal = key;
    HashIt it;
    ((HashFind*)&mStrategyMap)->find(&it, &keyLocal);
    if (it.node != mStrategyMap.mpBucket[mStrategyMap.mnBucketCount] &&
        *(IRefLite**)((char*)it.node + 4) != 0)
        return 0;

    NounMgr* nm = (NounMgr*)FUN_00b3d300();
    IRefLite* noun = (IRefLite*)nm->CreateNoun(0x34066dba);
    ((TutCallee*)noun)->Init(key);
    if (noun) noun->AddRef();

    IRefLite** pEnd = mObjectsEnd;
    if (pEnd < mObjectsCapacity) {
        mObjectsEnd = pEnd + 1;
        if (pEnd) {
            *pEnd = noun;
            if (noun) noun->AddRef();
        }
    } else {
        FUN_00aea5d0(pEnd, &noun);
    }
    if (noun) noun->Release();

    IRefLite** slot = ((StratMapEntry*)&mStrategyMap)->Lookup(&key);
    IRefLite* old = *slot;
    if (noun != old) {
        if (noun) noun->AddRef();
        *slot = noun;
        if (old) old->Release();
    }
    this->g28(0);
    return noun;
}

// @ 0x00b707a0  advance the mission for the given tool id.
unsigned __thiscall MissionMgr::HintClear(unsigned id)
{
    HashIt it;
    ((HashFind*)&mStrategyMap)->find(&it, &id);
    unsigned val = (unsigned)it.node;
    if (it.node != mStrategyMap.mpBucket[mStrategyMap.mnBucketCount]) {
        MissionStrategy* s = *(MissionStrategy**)((char*)it.node + 4);
        if (s) {
            s->Step();
            TutorialMission* t = (TutorialMission*)s->Cast(0xd4066db3);
            if (t) {
                void* next = t->GetNextMission();
                if (next) Hint((unsigned)next);
            }
            val = this->g28(0);
        }
    }
    return val & 0xffffff00u;
}
