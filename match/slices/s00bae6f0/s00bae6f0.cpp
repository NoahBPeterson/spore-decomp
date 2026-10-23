// Slice s00bae6f0 - Simulator scenario setup / star-system and planet helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include <stdlib.h>

typedef unsigned int uint;
typedef unsigned char uint8;

// ---------------------------------------------------------------------------
// shared helpers / interfaces
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EAAllocate(uint size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void __cdecl operator_delete__(void* p);                                                     // 0x00f47380

struct IRefCount
{
    virtual void v0();
    virtual void v1();
};

// eastl::vector<T> with sp_vector_allocator (begin, end, cap)
template <class T>
struct Vec3f
{
    T* begin;
    T* end;
    T* cap;
    void __thiscall DoInsertValue(T* pos, T* v);   // 0x00b96600
    void push_back(T v)
    {
        if (end < cap) {
            T* p = end++;
            if (p) *p = v;
        } else {
            DoInsertValue(end, &v);
        }
    }
};

// eastl::map<K,V> header (rbtree): root pointer followed by the anchor node,
// whose address is map::end().
struct MapHeader
{
    int   pad0;                                     // +0x00
    void* endNode;                                  // +0x04 (map::end())
    char  pad1[0x14];
};

struct IntMap : MapHeader
{
    uint* operator[](const uint& key);              // 0x00badea0
};

struct MapIter
{
    void* p;
    bool operator!=(const MapIter& o) const { return p != o.p; }
};
struct KeyRange { MapIter first; MapIter second; };
struct StringMap : MapHeader
{
    void equal_range(KeyRange* out, const void* key); // 0x00bab8a0
};

// ---------------------------------------------------------------------------
// 0x00baecc0: append an object to a vector if not already present
// ---------------------------------------------------------------------------
struct Entry : IRefCount {};

struct EntryVec
{
    Entry** begin;
    Entry** end;
    Entry** cap;
    void __thiscall DoInsertValue(Entry** pos, Entry** v);   // 0x00aea5d0
};

struct cUberTool
{
    char  pad0[0xf0];
    EntryVec mEntries;                             // +0xf0
    void AppendEntry(void* src, bool add);          // 0x00baecc0
};

// @ 0x00baecc0
void __thiscall cUberTool::AppendEntry(void* src, bool add)
{
    if (!add) return;
    Entry** __restrict end = mEntries.end;
    Entry* e = *(Entry**)((char*)src + 0x48);
    EntryVec* v = &mEntries;
    Entry** it = v->begin;
    if (it != end) {
        do {
            if (*it == e) break;
            it++;
        } while (it != end);
        if (it != end) return;
    }
    Entry* tmp = e;
    if (tmp) tmp->v0();
    if (v->end < v->cap) {
        Entry** p = v->end++;
        if (p) {
            *p = e;
            if (e) e->v0();
        }
    } else {
        v->DoInsertValue(v->end, &tmp);
        e = tmp;
    }
    if (e) e->v1();
}

// ---------------------------------------------------------------------------
// 0x00baf0b0: create an empire and store it in a map slot
// ---------------------------------------------------------------------------
struct cEmpire : IRefCount
{
    char pad0[0x80];
    uint field84;                                   // +0x84
};
cEmpire* __fastcall cEmpire_ctor(cEmpire* self);    // 0x00c34830

struct EmpireMap : MapHeader
{
    cEmpire** operator[](const uint& key);          // 0x00dd85c0
};

struct EmpireHolder
{
    char      pad0[0x150];
    EmpireMap mEmpires;                             // +0x150
    cEmpire*  CreateEmpire(uint arg);               // 0x00baf0b0
};

// @ 0x00baf0b0
cEmpire* __thiscall EmpireHolder::CreateEmpire(uint arg)
{
    void* mem = EAAllocate(0x158, "Simulator/cEmpire", 0, 0, 0, 0);
    cEmpire* e = mem ? cEmpire_ctor((cEmpire*)mem) : 0;
    e->field84 = arg;
    cEmpire** slot = mEmpires[arg];
    cEmpire* old = *slot;
    if (e != old) {
        e->v0();
        *slot = e;
        if (old) old->v1();
    }
    return e;
}

// ---------------------------------------------------------------------------
// 0x00baf590: insert value into both a map (keyed by civilization) and a vector
// ---------------------------------------------------------------------------
struct Civilization;
struct CivMap : MapHeader
{
    uint* operator[](Civilization* const& key);     // 0x00badea0
};

struct CivTool
{
    char       pad0[0x20];
    CivMap     mMap;                                // +0x20 (ends +0x3c)
    Vec3f<uint> mVec;                               // +0x3c
    void Insert(Civilization* civ, uint value);     // 0x00baf590
};

// @ 0x00baf590
void __thiscall CivTool::Insert(Civilization* civ, uint value)
{
    uint* __restrict slot = mMap[civ];
    Vec3f<uint>* v = &mVec;
    *slot = value;
    uint* end = v->end;
    if (end < v->cap) {
        v->end = end + 1;
        if (end) {
            *end = value;
            return;
        }
    } else {
        v->DoInsertValue(end, &value);
    }
}

// ---------------------------------------------------------------------------
// 0x00baf5d0: range membership test on a string-keyed map
// ---------------------------------------------------------------------------
struct StringTool
{
    char      pad0[0x16c];
    StringMap mMap;                                 // +0x16c
    bool Contains(const void* key);                 // 0x00baf5d0
};

// @ 0x00baf5d0
bool __thiscall StringTool::Contains(const void* key)
{
    KeyRange r;
    StringMap* __restrict m = &mMap;
    m->equal_range(&r, key);
    MapIter it = r.first;
    MapIter last = r.second;
    if (it != last) {
        if (it.p != *(void**)((char*)this + 0x170)) return true;
        return false;
    }
    void* e = *(void**)((char*)m + 4);
    if (e != *(void**)((char*)this + 0x170)) return true;
    return false;
}

// ---------------------------------------------------------------------------
// 0x00baf460: append the terrain sphere's object list to an entry vector
// ---------------------------------------------------------------------------
extern "C" void* __cdecl NounManager_b3d300();                              // 0x00b3d300
extern "C" void* __cdecl crt_memcpy(void* dst, const void* src, uint size); // 0x011e0744

struct TerrainSphere
{
    char pad0[0x1184];
    uint* begin;                                    // +0x1184
    uint* end;                                      // +0x1188
    uint* cap;                                      // +0x118c/0x1190 region
};

struct SphereAccess
{
    virtual void* GetCurrentTerrainSphere();        // 0x00f67d90
};

struct TempVec
{
    uint* begin;
    uint* end;
    uint* cap;
    void __thiscall DoAllocate(int count, void* allocSrc); // 0x004aa350
};

struct TerrainTool
{
    char pad0[0xc8];
    void** mObjTable;                               // +0xc8
    char pad1[0x80];
    Entry* mDefault;                                // +0x14c
    int Walk(EntryVec* out);                        // 0x00baf460
};

// @ 0x00baf460
int __thiscall TerrainTool::Walk(EntryVec* out)
{
    int result = 0;
    SphereAccess* nm = (SphereAccess*)NounManager_b3d300();
    TerrainSphere* sphere = (TerrainSphere*)nm->GetCurrentTerrainSphere();
    uint* sb = sphere->begin;
    uint* se = sphere->end;
    TempVec tmp;
    tmp.begin = tmp.end = tmp.cap = 0;
    int count = (int)(se - sb);
    tmp.DoAllocate(count, (char*)sphere + 0x1190);
    int nbytes = (int)((char*)se - (char*)sb);
    void* r = crt_memcpy(tmp.begin, sb, nbytes);
    tmp.end = (uint*)((char*)r + nbytes);
    int n = (int)((char*)r + (nbytes >> 2) * 4 - (char*)tmp.begin) >> 2;
    if (n > 0) {
        result = n;
        for (int i = 0; i < n; ++i) {
            uint id = tmp.begin[i];
            Entry* e;
            if (id == 0) {
                e = mDefault;
            } else if (id == 0xffffffffu) {
                e = 0;
            } else {
                void* slot = *(void**)((char*)mObjTable + (id >> 12) * 0x14);
                e = *(Entry**)((char*)slot + (id & 0xfff) * 4);
            }
            Entry* local = e;
            if (e) e->v0();
            if (out->end < out->cap) {
                Entry** p = out->end++;
                if (p) {
                    *p = e;
                    if (e) e->v0();
                }
            } else {
                out->DoInsertValue(out->end, &local);
                e = local;
            }
            if (e) e->v1();
        }
    }
    if (tmp.begin && *(int*)((char*)tmp.begin - 4) != 0)
        operator_delete__(tmp.begin);
    return result;
}

// ---------------------------------------------------------------------------
// 0x00baf130: create/configure a space inventory item from a planet state
// ---------------------------------------------------------------------------
extern "C" void* __cdecl NounManager_920090();                              // 0x00920090
extern "C" int __cdecl SpaceItem_GetID(void* item);                      // 0x00c87040
extern "C" void __cdecl SpaceItem_Init(void* item, void* state);         // 0x00c71750
extern "C" void __cdecl SpaceItem_SetState2(void* item, void* arg);      // 0x00c714f0
extern "C" void __cdecl SpaceItem_Bind(void* owner, void* state);        // 0x00ba91b0
extern "C" char __cdecl SpaceItem_Flag(void* item);                      // 0x00c708f0
extern "C" void* __cdecl SpaceItem_DataGet(void* item);                  // 0x00c70930
extern "C" void __cdecl QuaternionFromDirections(void* out, const void* a, const void* b); // 0x00698180
extern "C" void __cdecl RangeInitialize(void* str, const wchar_t* text); // 0x00579a90
extern "C" void __cdecl SpaceItem_SetName(void* item, void* str, int value); // 0x00c72a10
extern "C" void* __cdecl SpaceItem_StateDefault(void* item);             // 0x00b8d8e0
extern "C" void __cdecl SpaceItem_StateA(void* item);                    // 0x00ba5fd0
extern "C" void __cdecl SpaceItem_StateB(void* item);                    // 0x00ba6120
extern "C" void* __cdecl BioSortCall(int a, int b, int c);               // 0x00b8de30
extern "C" void __cdecl AddEntryHelper(void* owner, void* a, int b, int c, int d); // 0x00badae0

struct PtrVec
{
    void** begin;
    void** end;
    void** cap;
    void __thiscall DoInsertValue(void** pos, void** v); // 0x00b96600
};

struct InvObj
{
    void** vtbl;
};

struct PlanetState
{
    char pad0[0x28];
    int  state;                                     // +0x28
    int  flags;                                     // +0x2c
    char pad1[0x18];
    float pos[3];                                   // +0x44
    char pad2[0x40];
    char byte98;                                    // +0x98
    char pad3[0x14];
    char indexAD;                                   // +0xad
    char pad4[6];
    float fB0;                                      // +0xb0
    float fB4;                                      // +0xb4
};

struct SpaceTool
{
    char   pad0[0x50];
    PtrVec mItems;                                  // +0x50
    void*  Create(InvObj* item, PlanetState* st, InvObj* opt); // 0x00baf130
};

// @ 0x00baf130
void* __thiscall SpaceTool::Create(InvObj* item, PlanetState* st, InvObj* opt)
{
    void* mgr = NounManager_920090();
    typedef void* (__thiscall *CreateFn)(void*, unsigned, unsigned, int);
    InvObj* obj = (InvObj*)((CreateFn)(*(void***)mgr)[0x20 / 4])(mgr, 0x3275728, 0x3275872, 0);
    if (mItems.end < mItems.cap) {
        void** p = mItems.end++;
        if (p) *p = obj;
    } else {
        mItems.DoInsertValue(mItems.end, (void**)&obj);
    }
    if ((SpaceItem_GetID(item) & 3) != 0)
        st->flags |= 0x20;
    SpaceItem_Init(obj, st);
    if (st->state == 0) {
        st->byte98 = 1;
        ((void (__thiscall*)(InvObj*, void*))(*(void***)obj)[0x38 / 4])(obj, (void*)0x168965c);
    } else {
        if (opt) {
            void* src = ((void* (__thiscall*)(InvObj*))(*(void***)opt)[0x2c / 4])(opt);
            *(int*)((char*)obj + 0x148) = ((int*)src)[0];
            *(int*)((char*)obj + 0x14c) = ((int*)src)[1];
            *(int*)((char*)obj + 0x150) = ((int*)src)[2];
            src = ((void* (__thiscall*)(InvObj*))(*(void***)opt)[0x2c / 4])(opt);
            float p[3];
            p[0] = ((float*)src)[0] + st->pos[0];
            p[1] = ((float*)src)[1] + st->pos[1];
            p[2] = ((float*)src)[2] + st->pos[2];
            ((void (__thiscall*)(InvObj*, float*))(*(void***)obj)[0x38 / 4])(obj, p);
            SpaceItem_SetState2(obj, opt);
        } else {
            ((void (__thiscall*)(InvObj*, float*))(*(void***)obj)[0x38 / 4])(obj, st->pos);
        }
        SpaceItem_Bind(this, st);
        const void* dir = SpaceItem_Flag(obj) ? (const void*)0x156c538 : SpaceItem_DataGet(obj);
        float quat[4];
        QuaternionFromDirections(quat, (const void*)0x156c538, dir);
        ((void (__thiscall*)(InvObj*, float*))(*(void***)obj)[0x3c / 4])(obj, quat);
        if (st->state != 1 && st->state != 0) {
            if (!(st->fB4 > 0.0f) || !(st->fB0 > 0.0f)) {
                void* v = BioSortCall(0, 0, 0);
                AddEntryHelper(obj, v, 0, 0, 0);
            }
            if (*(int*)SpaceItem_StateDefault(obj) == 0) {
                if (st->state == 2) SpaceItem_StateA(obj);
                else SpaceItem_StateB(obj);
            }
        }
    }
    int value = 0;
    if (st->state == 0) {
        value = st->indexAD;
    } else if (st->state == 1) {
        value = (int)(unsigned char)st->indexAD;
    } else {
        value = 0;
    }
    void* str[3];
    str[0] = str[1] = str[2] = 0;
    RangeInitialize(str, L"planet_radius5_terraformed");
    SpaceItem_SetName(obj, str, value);
    if (str[0] && (((char*)str[1] - (char*)str[0]) & 0xfffffffe) > 2)
        operator_delete__(str[0]);
    return obj;
}

// ---------------------------------------------------------------------------
// 0x00bae6f0: rebuild the star record and reset the editor view
// ---------------------------------------------------------------------------
extern "C" void* __cdecl cStarRecord_ctor(void* rec);                       // 0x00bba130
extern "C" void __cdecl StarRecord_SetMode(void* rec, int mode);         // 0x00bb9ad0
extern "C" void __cdecl StarRecord_ResetList(void* rec, void* list);     // 0x00bb9b90
extern "C" void __cdecl Canvas_SetMessageServer(void* canvas, void* s);  // 0x00a16a30
extern "C" void __cdecl StarManager_SetStar(void* mgr, void* a, void* b); // 0x00bbac80
extern "C" void __cdecl StarRecord_SetSomething(void* rec, int v);       // 0x00a16a90
extern "C" void __cdecl StarRecord_SetFlag(void* rec, int v);            // 0x00bb9c10
extern "C" void __cdecl StarRecord_SetBox(void* rec, float* box);        // 0x00bb9ab0
extern "C" void __cdecl StarRecord_SetWindow(void* rec, unsigned v);     // 0x00c87bc0
extern "C" void* __cdecl GameData_4010a0();                                 // 0x004010a0
extern "C" void* __cdecl GameData_AddRef(void* g);                       // 0x00801920
extern "C" double __cdecl GameData_Float(void* g, int i);                // 0x00c84c60
extern "C" void __cdecl StarRecord_MakeBody(void* owner, void* rec, float a, float b, int c); // 0x00ba8c40

struct StarTool
{
    char  pad0[0x14c];
    void* mStar;                                    // +0x14c
    void  Build();                                  // 0x00bae6f0
};

// @ 0x00bae6f0
void __thiscall StarTool::Build()
{
    void* rec = EAAllocate(0xb0, "Simulator/cStarRecord", 0, 0, 0, 0);
    if (rec) rec = cStarRecord_ctor(rec);
    void* old = mStar;
    if (rec != old) {
        if (rec) ((IRefCount*)rec)->v0();
        mStar = rec;
        if (old) ((IRefCount*)old)->v1();
    }
    StarRecord_SetMode(mStar, 5);
    void* list[3] = {0, 0, 0};
    StarRecord_ResetList(mStar, list);
    Canvas_SetMessageServer(mStar, 0);
    StarManager_SetStar(mStar, 0, 0);
    StarRecord_SetSomething(mStar, -1);
    StarRecord_SetFlag(mStar, 0);
    float box[3] = {1.0f, 1.0f, 0.0f};
    StarRecord_SetBox(mStar, box);
    StarRecord_SetWindow(mStar, 4);
    *(int*)((char*)mStar + 0x70) = 0;
}

// ---------------------------------------------------------------------------
// 0x00bae9b0: create the three moon bodies around the current planet
// ---------------------------------------------------------------------------
extern "C" void __cdecl Planet_MakeBodyID(uint id, void** out);          // 0x00ba61b0
extern "C" void* __cdecl PropertyManager_5ecf80(void* list, int key);       // 0x005ecf80

struct BodyTool
{
    char  pad0[0xac];
    char  count;                                    // +0xac
    char  pad1[0x9f];
    int   field70;                                  // +0x70
    void  MakeMoons(PlanetState* st);               // 0x00bae9b0
};

// @ 0x00bae9b0
void __thiscall BodyTool::MakeMoons(PlanetState* st)
{
    if (st->byte98) return;
    void* g = GameData_4010a0();
    void* h = GameData_AddRef(g);
    float a = (float)GameData_Float(h, 0);
    float b = (float)GameData_Float(h, 1);
    float c = (float)GameData_Float(h, 2);
    for (int i = 0; i < 3; ++i) {
        void* body = 0;
        Planet_MakeBodyID((unsigned)(unsigned char)st->byte98 * 0x1000000 + field70, &body);
        if (body) {
            ((IRefCount*)body)->v1();
            *(int*)((char*)body + 0x2c) = 0;
            *(int*)((char*)body + 0x28) = 2;
            *(int*)((char*)body + 0x194) = 1;
            float px = st->pos[0], py = st->pos[1], pz = st->pos[2];
            if (i == 0) SpaceItem_Bind(this, st);
            else if (i == 1) SpaceItem_SetState2(body, st);
            else SpaceItem_Init(body, st);
            (void)px; (void)py; (void)pz;
            (void)a; (void)b; (void)c;
            st->byte98++;
            ((IRefCount*)body)->v1();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00baed60: editor event dispatcher
// ---------------------------------------------------------------------------
extern "C" void __cdecl Banner_Event(void* self, void* data);             // 0x00ba6e00
extern "C" void __cdecl Star_Event(void* self, void* data);               // 0x00bad7a0
extern "C" void __cdecl StarCore_Event(void* self, int* data);               // 0x00ba7220

struct EventTool
{
    char pad0[0x1c];
    char Dispatch(unsigned id, void* data);         // 0x00baed60
};

// @ 0x00baed60
char __thiscall EventTool::Dispatch(unsigned id, void* data)
{
    char* self = (char*)this - 0x1c;
    if (id < 0x4b719d5u) {
        if (id == 0x4b719d4u) {
            void* args = *(void**)((char*)data + 0x10);
            void* pmgr = 0;
            (void)args; (void)pmgr;
            return 0;
        }
        if (id == 0x4249453u) {
            int v[3];
            v[0] = *(int*)((char*)data + 0x18);
            v[1] = *(int*)((char*)data + 0x8);
            v[2] = *(int*)((char*)data + 0x10);
            StarCore_Event(self, v);
            return 0;
        }
        if (id == 0x4b33711u) {
            void* p = *(void**)((char*)data + 0x8);
            if (p) Star_Event(self, p);
            return 1;
        }
    } else if (id == 0x5e631c9u) {
        Banner_Event(self, 0);
    }
    return 0;
}
