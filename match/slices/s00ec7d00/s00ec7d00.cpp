// Scenario/tutorial command-list builders for the Spore UI.
// Built with /O2 (EASTL containers inlined).  EASTL vector<T> is 3 pointers
// (begin,end,capacity); a full element takes the out-of-line DoPushBack path.
//
// Flags: /O2 /MD /Gy /TP

#include <new>

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

// ---------------------------------------------------------------------------
// minimal EASTL
// ---------------------------------------------------------------------------
template <class T>
struct evec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;

    void DoPushBack(T* end, const T* v);

    void push_back(const T& v) {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                ::new ((void*)p) T(v);
        } else {
            DoPushBack(mpEnd, &v);
        }
    }
};

struct Pair {                             // 8 bytes
    int first;
    int second;
    Pair() {}
    Pair(int a, int b) : first(a), second(b) {}
};
struct Big  { uint32_t d[8]; };           // 0x20 bytes

// ---------------------------------------------------------------------------
// globals / imports
// ---------------------------------------------------------------------------
extern char*     g_pScenario;        // 0x016c757c
extern char*     g_pMagic;           // 0x016c7aa4
extern uint8_t   g_bFlag;            // 0x015abcd0
extern uint8_t   g_ScenarioFlags[8]; // 0x016c7574

extern void* operator_new(uint32_t size, const char* name, int flags, int align,
                          const char* file, int line);   // 0x00f473a0
extern void  operator_delete(void* p);                   // 0x00f47380

extern int  ScenarioTutorials_GetActive();               // 0x00efc520
extern int  FUN_00f3e8a0(int id);                        // 0x00f3e8a0
extern bool FUN_00ec6d70(Pair* p);                       // 0x00ec6d70
extern bool FUN_00ec7640(Pair* p);                       // 0x00ec7640
extern void FUN_00ec6e00();                              // 0x00ec6e00

struct GObj {
    bool FUN_00f254d0();                                 // 0x00f254d0
    bool FUN_00f25330();                                 // 0x00f25330
};
struct TutorialFlags {
    bool FUN_00f25640();                                 // 0x00f25640
};
struct TutorialCmd {
    void FUN_00c06b10(char* other);                      // 0x00c06b10
};
struct Key {
    void FUN_00ec7ca0(const void* v);                    // 0x00ec7ca0
};

// world object list: *(*(g_pMagic+0x74)+0x10), elements are 0x27e8 bytes
struct WorldMgr {
    uint32_t pad0[0x2bf4 / 4];
    char*    begin;   // +0x2bf4
    char*    end;     // +0x2bf8
};

inline WorldMgr* GetWorld() {
    return (WorldMgr*)*(char**)(*(char**)(g_pMagic + 0x74) + 0x10);
}

inline char* GetScenarioBase() {
    return *(char**)(*(char**)g_pScenario + 0x70);
}

// ---------------------------------------------------------------------------
// 0x00ec7d00  vector<Big>::insert(position, count, value)
// ---------------------------------------------------------------------------
struct BigVec : evec<Big> {
    void Insert(Big* position, uint32_t count, const Big* value);  // 0x00ec7d00
};

// @ 0x00ec7d00
void BigVec::Insert(Big* position, uint32_t count, const Big* value)
{
    if (count == 0)
        return;
    uint32_t idx = (uint32_t)(position - mpBegin);
    uint32_t oldSize = (uint32_t)(mpEnd - mpBegin);
    if ((uint32_t)(mpCapacity - mpEnd) < count) {
        uint32_t newCap = oldSize * 2;
        if (oldSize == 0)
            newCap = 1;
        if (oldSize + count > newCap)
            newCap = oldSize + count;
        Big* buf = (Big*)operator_new(newCap * sizeof(Big), "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        if (buf) {
            for (uint32_t i = 0; i < idx; ++i)
                buf[i] = mpBegin[i];
            for (uint32_t i = 0; i < count; ++i)
                buf[idx + i] = *value;
            for (uint32_t i = idx; i < oldSize; ++i)
                buf[i + count] = mpBegin[i];
        }
        if (mpBegin && mpBegin[-1].d[7])
            operator_delete(mpBegin);
        mpBegin = buf;
        mpEnd = buf + oldSize + count;
        mpCapacity = buf + newCap;
    } else {
        Big tmp = *value;
        uint32_t after = oldSize - idx;
        Big* oldEnd = mpEnd;
        if (after <= count) {
            uint32_t fill = count - after;
            for (uint32_t i = 0; i < fill; ++i)
                oldEnd[i] = tmp;
            for (uint32_t i = 0; i < after; ++i)
                oldEnd[fill + i] = position[i];
            mpEnd += fill + after;
            for (uint32_t i = 0; i < after; ++i)
                position[i] = tmp;
        } else {
            Big* src = oldEnd - count;
            for (uint32_t i = 0; i < count; ++i)
                oldEnd[i] = src[i];
            for (uint32_t i = after - count; i > 0; --i)
                position[i + count - 1] = position[i - 1];
            mpEnd += count;
            for (uint32_t i = 0; i < count; ++i)
                position[i] = tmp;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00ec7e90  mark tutorials matching the active scenario
// ---------------------------------------------------------------------------
// @ 0x00ec7e90
void FUN_00ec7e90()
{
    int idx = ScenarioTutorials_GetActive();
    char* sBase = GetScenarioBase() + idx * 0x4e0;
    char* local = sBase + 0x4cc;
    WorldMgr* w = GetWorld();
    char* it = w->begin;
    if (it == w->end)
        return;
    do {
        char* e = it + 8;
        if (*(char**)g_pScenario != e) {
            char* a = *(char**)(e + 0x70) + idx * 0x4e0;
            char* b = sBase;
            if (*(uint32_t*)(a + 0x4a8) == *(uint32_t*)(b + 0x4a8)) {
                ((TutorialCmd*)(a + 0x4cc))->FUN_00c06b10(local);
            }
        }
        it += 0x27e8;
    } while (it != GetWorld()->end);
}

// ---------------------------------------------------------------------------
// 0x00ec7f40  rbtree insert (out, parent, value, unique)
// ---------------------------------------------------------------------------
struct RBNode { uint32_t d[10]; };   // 0x28

extern void RBTreeInsert(void* node, void* parent, void* anchor, int b); // 0x009216a0

struct RBTree {
    uint32_t m_pad0;       // +0
    uint32_t mAnchor;      // +4
    uint32_t m_pad1[3];    // +8
    uint32_t mnSize;       // +0x14

    void Insert(void** out, void* parent, const void* value, bool b);  // 0x00ec7f40
};

// @ 0x00ec7f40
void RBTree::Insert(void** out, void* parent, const void* value, bool b)
{
    int t;
    char* anchor = (char*)&mAnchor;
    if (!b && (char*)parent != anchor && (int)*(const uint32_t*)value >= (int)*(uint32_t*)((char*)parent + 0x10))
        t = 1;
    else
        t = 0;
    RBNode* node = (RBNode*)operator_new(0x28, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    ((Key*)((char*)node + 0x10))->FUN_00ec7ca0(value);
    RBTreeInsert(node, parent, anchor, t);
    mnSize++;
    *out = node;
}

// ---------------------------------------------------------------------------
// 0x00ec8050  push 15 command ids
// ---------------------------------------------------------------------------
// @ 0x00ec8050
void FUN_00ec8050(evec<int>* v)
{
    int ids[15] = {1, 0xd, 4, 3, 0xc, 0xe, 0xb, 0, 5, 8, 9, 2, 6, 0xa, 7};
    for (int i = 0; i < 15; ++i)
        v->push_back(ids[i]);
}

// ---------------------------------------------------------------------------
// 0x00ec8110  push 9 (3,id) pairs
// ---------------------------------------------------------------------------
// @ 0x00ec8110
void FUN_00ec8110(evec<Pair>* v)
{
    int arr[9] = {8, 7, 1, 2, 3, 0, 4, 5, 6};
    Pair p;
    p.first = 3;
    unsigned int i = 0;
    do {
        p.second = arr[i];
        v->push_back(p);
        ++i;
    } while (i < 9);
}

// ---------------------------------------------------------------------------
// 0x00ec81b0  push (0,-1) then (2,id) for valid world objects
// ---------------------------------------------------------------------------
// @ 0x00ec81b0
void FUN_00ec81b0(evec<Pair>* v)
{
    v->push_back(Pair(0, -1));
    WorldMgr* w = GetWorld();
    char* it = w->begin;
    if (it == w->end)
        return;
    do {
        int id = *(int*)it;
        if (((GObj*)FUN_00f3e8a0(id))->FUN_00f254d0() == 1)
            v->push_back(Pair(2, id));
        it += 0x27e8;
    } while (it != GetWorld()->end);
}

// ---------------------------------------------------------------------------
// 0x00ec8270  push (0,-1),(8,-1) then (2,id)
// ---------------------------------------------------------------------------
// @ 0x00ec8270
void FUN_00ec8270(evec<Pair>* v)
{
    v->push_back(Pair(0, -1));
    v->push_back(Pair(8, -1));
    WorldMgr* w = GetWorld();
    for (char* it = w->begin; it != w->end; it += 0x27e8) {
        int id = *(int*)it;
        if (((GObj*)FUN_00f3e8a0(id))->FUN_00f25330() == 1)
            v->push_back(Pair(2, id));
    }
}

// ---------------------------------------------------------------------------
// 0x00ec8370
// ---------------------------------------------------------------------------
// @ 0x00ec8370
void FUN_00ec8370(evec<Pair>* v)
{
    v->push_back(Pair(0, -1));
    int idx = ScenarioTutorials_GetActive();
    if (*(uint32_t*)(GetScenarioBase() + idx * 0x4e0 + 0x4a8) != 2)
        v->push_back(Pair(8, -1));

    for (int i = 1; i <= 4; ++i) {
        if (g_bFlag)
            FUN_00ec6e00();
        if (g_ScenarioFlags[i]) {
            Pair p(0, 0);
            p.first = 1;
            p.second = i;
            if (FUN_00ec6d70(&p))
                v->push_back(p);
        }
    }
    WorldMgr* w = GetWorld();
    for (char* it = w->begin; it != w->end; it += 0x27e8) {
        Pair p(0, 0);
        p.first = 2;
        p.second = *(int*)it;
        if (FUN_00ec6d70(&p) == 1)
            v->push_back(p);
    }
}

// ---------------------------------------------------------------------------
// 0x00ec8510
// ---------------------------------------------------------------------------
// @ 0x00ec8510
void FUN_00ec8510(evec<Pair>* v)
{
    v->push_back(Pair(0, -1));
    int idx = ScenarioTutorials_GetActive();
    if (*(uint32_t*)(GetScenarioBase() + idx * 0x4e0 + 0x4a8) != 2)
        v->push_back(Pair(8, -1));

    for (int i = 1; i <= 4; ++i) {
        if (g_bFlag)
            FUN_00ec6e00();
        if (g_ScenarioFlags[i]) {
            Pair p(0, 0);
            p.first = 1;
            p.second = i;
            if (FUN_00ec7640(&p))
                v->push_back(p);
        }
    }
    WorldMgr* w = GetWorld();
    for (char* it = w->begin; it != w->end; it += 0x27e8) {
        Pair p(0, 0);
        p.first = 2;
        p.second = *(int*)it;
        if (FUN_00ec7640(&p) == 1)
            v->push_back(p);
    }
}

// ---------------------------------------------------------------------------
// 0x00ec86b0  push (8,-1) then (2,id) for valid objects
// ---------------------------------------------------------------------------
// @ 0x00ec86b0
void FUN_00ec86b0(evec<Pair>* v)
{
    v->push_back(Pair(8, -1));
    WorldMgr* w = GetWorld();
    for (char* it = w->begin; it != w->end; it += 0x27e8) {
        if (((TutorialFlags*)(it + 8))->FUN_00f25640()) {
            int id = *(int*)it;
            v->push_back(Pair(2, id));
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00ec8780
// ---------------------------------------------------------------------------
// @ 0x00ec8780
void FUN_00ec8780(evec<Pair>* v)
{
    v->push_back(Pair(0, -1));
    v->push_back(Pair(8, -1));
    for (int i = 1; i <= 4; ++i) {
        if (g_bFlag)
            FUN_00ec6e00();
        if (g_ScenarioFlags[i])
            v->push_back(Pair(1, i));
    }
    WorldMgr* w = GetWorld();
    for (char* it = w->begin; it != w->end; it += 0x27e8) {
        if (((TutorialFlags*)(it + 8))->FUN_00f25640()) {
            int id = *(int*)it;
            v->push_back(Pair(2, id));
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00ec88e0  command dispatch
// ---------------------------------------------------------------------------
// @ 0x00ec88e0
void FUN_00ec88e0(int cmd, void* v, void* v2)
{
    switch (cmd) {
    case 1: case 0xd:       FUN_00ec8110((evec<Pair>*)v); return;
    case 4: FUN_00ec81b0((evec<Pair>*)v); FUN_00ec8270((evec<Pair>*)v2); return;
    case 3: case 0xc: case 0xe: FUN_00ec81b0((evec<Pair>*)v); return;
    case 0: case 5: case 8: FUN_00ec8510((evec<Pair>*)v); return;
    case 7: FUN_00ec86b0((evec<Pair>*)v); return;
    }
}

// ---------------------------------------------------------------------------
// 0x00ec8970  command dispatch issuing int vectors
// ---------------------------------------------------------------------------
// @ 0x00ec8970
void FUN_00ec8970(int cmd, evec<int>* v)
{
    switch (cmd) {
    case 0: case 5: case 8:
        v->push_back(0); v->push_back(1); v->push_back(5); v->push_back(4);
        v->push_back(2); v->push_back(6); v->push_back(7); v->push_back(8);
        return;
    case 1:
        v->push_back(0); v->push_back(1); v->push_back(3);
        v->push_back(7); v->push_back(8);
        return;
    case 2: case 4: case 6: case 7: case 10: case 0xe:
        v->push_back(0); v->push_back(1); v->push_back(5); v->push_back(3);
        v->push_back(2); v->push_back(6); v->push_back(7); v->push_back(8);
        return;
    case 3:
        v->push_back(0); v->push_back(1); v->push_back(5); v->push_back(2);
        v->push_back(6); v->push_back(7); v->push_back(8);
        return;
    case 9:
        v->push_back(2);
        return;
    case 11: case 12:
        v->push_back(0); v->push_back(5);
        v->push_back(6); v->push_back(7); v->push_back(8);
        return;
    case 13:
        v->push_back(5); v->push_back(6);
        return;
    }
}
