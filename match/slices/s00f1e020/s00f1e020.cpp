// slice s00f1e020 -- UI::cScenarioPlayProgressBar and the 0x1ac-byte goal record
// it stores in an eastl::vector.
//
// Retail build: VS2008 era (cl 15) -- NOT RenderWare, so byte-exactness is expected.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
//
// Recovered model
// ---------------
//  * goal record, 0x1ac bytes:
//      +0x00 bool, +0x01 bool, +0x04 int, +0x08 an eastl container (0x1c bytes,
//      out-of-line copy/assign at 0x00b96560 / 0x00b962d0), +0x24 a 0x188-byte
//      "act step" record.  act step: +0x24..+0x38 scalars, +0x3c an inline-buffer
//      vector of 0x44-byte elements (0x154 bytes of inline storage at +0x54),
//      +0x1a8 a trailing scalar.  Its default ctor is 0x00f2bd10, the copy-ctor
//      body 0x00dfd020, and the vector element assign 0x00dfcb00.
//  * the range algorithms 0x00f1e880 / 0x00f1e940 / 0x00f1e9f0 are the
//    uninitialised-copy / forward-assign / copy-backward used by vector growth.
//  * 0x00f1e450/0x00f1e580/0x00f1e620/0x00f1e6a0/0x00f1e020/0x00f1ecf0 are the
//    bar's ctor / dtor / init / per-frame scans / config read / update.

#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// external helpers (bodies live in other slices)
// ---------------------------------------------------------------------------
void operator_delete__(void*);                      // 0x00f47380  ??3@YAXPAX@Z
void operator_delete_array(void*);                  // same crt helper

struct Stopwatch                                 // EA::Stopwatch, 0x18 bytes
{
    char raw[0x18];
    void Init(int a, int b);                     // 0x0093a560
    void SetUnits(int units);                    // 0x0093a1a0
};

typedef void (__thiscall *MsgSendFn)(void*, void*, uint);   // vtable slot +0x24

struct BarIface                                     // object released through slot +0x100
{
    virtual void vt00();
    virtual void vt04();
};
void* SP_MessageServer();                           // 0x0067dcc0
void  Messaging__RemoveHandler(void*, void*, void*, void*, void*);   // 0x00571db0
void* SP_NounManager();                             // 0x00b3d300
void* SP_TerrainMgr();                              // 0x00b3d320
struct TerrainMgr
{
    void* GetTerrain();                             // 0x00b1de80
};
struct ActHost
{
    void* GetAct(void* id);                         // 0x00f3be60
    void* FindCreature(void* id);                   // 0x00f3e8a0
    void* BuildGoal(void* a, void* e, void* b, void* g, int, int, int, int);  // 0x00f416b0
};
struct CreatureObj
{
    int IsMarked();                                 // 0x00f25ed0
};
struct Inventory
{
    void* GetItemID();                              // 0x00b1f9c0
};
struct ItemObj
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void* v3(int, int);
};
void* GetGameDataVector(void*, int, int, int, int, int);   // 0x00b21340
void* EachChild2(void*);                            // 0x00f196f0
void* EachChild(void*, uint*, uint);                // 0x00f19660
void  FUN_00f190a0(void*);                          // UI::cScenarioPlayProgressBar::Reset
void  FUN_00f1ae10(void*, void*, void*);            // 0x00f1ae10
void  FUN_00f1dcc0(void* vec, void* first, void* last);    // string16 vector assign
void  StringVec__resize(void* vec, unsigned n);     // 0x00553be0
void  FUN_006a0b50(void* obj, int key, int* count, void** data);   // 0x006a0b50
float* SP_GetPropertyAsFloat(void* p);              // 0x0041ea70
uint*  SP_GetPropertyAsUInt(void* p);               // 0x0041ea00
void*  Alloc(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0

int   FUN_00ca6db0(void*);                          // 0x00ca6db0
void* FUN_00989360(void*);                          // 0x00989360
void* FUN_00c04590(void*);                          // 0x00c04590
void  FUN_00c06f70(void*);                          // 0x00c06f70
void* FUN_00b1f9c0(void*);                          // 0x00b1f9c0  GetItemID
void* FUN_00f3be60(void*);                          // 0x00f3be60  GetAct
void* FUN_00f3e8a0(void*, void*);                   // 0x00f3e8a0
int   FUN_00f25ed0(void*);                          // 0x00f25ed0
void* FUN_00f416b0(void*, void*, void*, void*, int, int, int, int);   // 0x00f416b0
uint8_t FUN_00f3b390(void*);                          // 0x00f3b390
float* GetProperty(void* prop);                     // 0x0041ea70 (float accessor body)

// ---------------------------------------------------------------------------
// layout
// ---------------------------------------------------------------------------
struct GoalMap                                      // eastl container at goal+0x08 (0x1c bytes)
{
    char raw[0x1c];
    void      Construct(const GoalMap&);            // 0x00b96560  copy-ctor body
    GoalMap&  operator=(const GoalMap&);            // 0x00b962d0  operator=
};

struct Vec44                                        // inline-buffer vector at goal+0x3c
{
    void* b; void* e; void* c;                      // +0x3c / +0x40 / +0x44
    int   f48; int f4c; int f50;                    // +0x48 / +0x4c / +0x50
    char  buf[0x154];                               // +0x54
    void  assignFrom(const Vec44&);                 // 0x00dfcb00  operator=
    void  Construct(const Vec44& x)                 // fixed_vector copy-construction
    {
        f50 = 0;
        b = buf;
        e = buf;
        c = buf + 0x154;
        assignFrom(x);
    }
};

struct ActStep                                      // 0x188-byte act-step record at goal+0x24
{
    int f0; int f4; int f8; int fc;                 // +0x24 .. +0x30
    char f10; char pad11[3]; int f14;               // +0x34, +0x38
    Vec44 vec;                                      // +0x3c
    int f184;                                       // +0x1a8
    void Construct(const ActStep&);                 // 0x00dfd020  copy-ctor body
    __declspec(noinline) void ctor();               // 0x00f2bd10  default-ctor body
};

struct Goal                                         // 0x1ac bytes
{
    uint8_t b0; uint8_t b1; char pad2[2]; int i4;       // +0x00 .. +0x08
    GoalMap map;                                    // +0x08 (0x1c)
    ActStep act;                                    // +0x24 (0x188)
    Goal();
    void destroy();                                 // 0x00f1dec0
    Goal& operator=(const Goal&);                   // 0x00f1e810
};

struct GoalVec                                      // eastl::vector<Goal, ...>
{
    Goal* b; Goal* e; Goal* c;
    __declspec(noinline) void destroyRange(Goal* first, Goal* last);     // 0x00f1dfa0
    void Insert(Goal* pos, const Goal& val);        // 0x00f1eaa0
    void emplace_back();                            // 0x00f1ec50
};

// destroy helpers shared by the range algorithms
void  DestroyActElem(ActStep* p);                   // 0x00f280f0
void* DestroyActRange(ActStep* first, ActStep* last);   // 0x00f1df10
void  DestroyMapList(GoalMap* map, int a);          // 0x009a9600

// ---------------------------------------------------------------------------
// @ 0x00f2bd10  default construction of the act-step record
// ---------------------------------------------------------------------------
// @ 0x00f2bd10
void ActStep::ctor()
{
    f0 = 0;
    f4 = -1;
    f8 = -1;
    f10 = 1;
    f14 = 0;
    vec.f50 = 0;
    vec.b = vec.buf;
    vec.e = vec.b;
    vec.c = (uint8_t*)vec.b + 0x154;
    f184 = -1;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e880  uninitialised copy of a goal range (constructs map + act step)
// ---------------------------------------------------------------------------
// @ 0x00f1e880
Goal* MoveRangeUninit(Goal* first, Goal* last, Goal* out)
{
    if (first != last) {
        do {
            if (out) {
                out->b0 = first->b0;
                out->b1 = first->b1;
                out->i4 = first->i4;
                out->map.Construct(first->map);
                out->act.f0 = first->act.f0;
                out->act.f4 = first->act.f4;
                out->act.f8 = first->act.f8;
                out->act.fc = first->act.fc;
                out->act.f10 = first->act.f10;
                out->act.f14 = first->act.f14;
                out->act.vec.Construct(first->act.vec);
                out->act.f184 = first->act.f184;
            }
            first += 1;
            out += 1;
        } while (first != last);
        return out;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e940  assign a goal range onto existing goals
// ---------------------------------------------------------------------------
// @ 0x00f1e940
Goal* MoveRangeAssign(Goal* first, Goal* last, Goal* out)
{
    if (first != last) {
        do {
            *out = *first;
            first += 1;
            out += 1;
        } while (first != last);
        return out;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e9f0  copy_backward over a goal range
// ---------------------------------------------------------------------------
// @ 0x00f1e9f0
Goal* MoveRangeBack(Goal* first, Goal* last, Goal* out)
{
    if (last != first) {
        do {
            last -= 1;
            out -= 1;
            out->b0 = last->b0;
            out->b1 = last->b1;
            out->i4 = last->i4;
            out->map = last->map;
            out->act.f0 = last->act.f0;
            out->act.f4 = last->act.f4;
            out->act.f8 = last->act.f8;
            out->act.fc = last->act.fc;
            out->act.f10 = last->act.f10;
            out->act.f14 = last->act.f14;
            out->act.vec.assignFrom(last->act.vec);
            out->act.f184 = last->act.f184;
        } while (last != first);
        return out;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e810  Goal::operator=
// ---------------------------------------------------------------------------
// @ 0x00f1e810
Goal& Goal::operator=(const Goal& s)
{
    b0 = s.b0;
    b1 = s.b1;
    i4 = s.i4;
    map = s.map;
    act.f0 = s.act.f0;
    act.f4 = s.act.f4;
    act.f8 = s.act.f8;
    act.fc = s.act.fc;
    act.f10 = s.act.f10;
    act.f14 = s.act.f14;
    act.vec.assignFrom(s.act.vec);
    act.f184 = s.act.f184;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00f1eaa0  eastl::vector<Goal>::insert(pos, value)
// ---------------------------------------------------------------------------
// @ 0x00f1eaa0
void GoalVec::Insert(Goal* pos, const Goal& val)
{
    Goal* end = e;
    if (end != c) {
        if (pos <= &val && &val < end)
            pos += 1;
        if (end) {
            end->b0 = end[-1].b0;
            end->b1 = end[-1].b1;
            end->i4 = end[-1].i4;
            end->map.Construct(end[-1].map);
            end->act.Construct(end[-1].act);
        }
        MoveRangeBack(pos, e - 1, e);
        *pos = val;
        e = e + 1;
        return;
    }
    int n = (int)((e - b) / 0x1ac);
    int cap;
    void* mem;
    if (n == 0) {
        cap = 1;
    } else {
        cap = n * 2;
        if (cap == 0) {
            mem = 0;
            goto alloc_done;
        }
    }
    mem = Alloc(cap * 0x1ac, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
alloc_done:
    Goal* raw = (Goal*)mem;
    Goal* newEnd = MoveRangeUninit(b, pos, raw);
    DestroyActRange((ActStep*)b, (ActStep*)pos);
    if (newEnd) {
        newEnd->b0 = val.b0;
        newEnd->b1 = val.b1;
        newEnd->i4 = val.i4;
        newEnd->map.Construct(val.map);
        newEnd->act.Construct(val.act);
    }
    Goal* last = e;
    Goal* ret = MoveRangeUninit(pos, last, newEnd + 1);
    DestroyActRange((ActStep*)pos, (ActStep*)last);
    if (b && ((int*)b)[-1] != 0)
        operator_delete__(b);
    b = raw;
    e = ret;
    c = (Goal*)((char*)raw + cap * 0x1ac);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
static inline void InitGoal(Goal* p)
{
    char* q = (char*)p;
    char* s = q + 0xc;
    *(void**)(q + 0x10) = 0;
    *(void**)(q + 0x14) = 0;
    *(void**)(q + 0x18) = 0;
    *(void**)s = s;
    *(void**)(q + 0x10) = s;
    *(void**)(q + 0x14) = 0;
    *(uint8_t*)(q + 0x18) = 0;
    *(void**)(q + 0x1c) = 0;
    p->act.ctor();
}

// @ 0x00f1ec50
void GoalVec::emplace_back()
{
    char tmpbuf[0x1ac];
    Goal* p = e;
    if (p < c) {
        e = p + 1;
        if (p)
            InitGoal(p);
        return;
    }
    Goal* t = (Goal*)tmpbuf;
    InitGoal(t);
    Insert(e, *t);
    t->destroy();
}

// ---------------------------------------------------------------------------
// goal record ctor / dtor
// ---------------------------------------------------------------------------
Goal::Goal()
{
    char* q = (char*)this;
    char* s = q + 0xc;
    *(void**)(q + 0x10) = 0;
    *(void**)(q + 0x14) = 0;
    *(void**)(q + 0x18) = 0;
    *(void**)s = s;
    *(void**)(q + 0x10) = s;
    *(void**)(q + 0x14) = 0;
    *(uint8_t*)(q + 0x18) = 0;
    *(void**)(q + 0x1c) = 0;
    act.ctor();
}

// @ 0x00f1dfa0  GoalVec::destroyRange
void GoalVec::destroyRange(Goal* first, Goal* last)
{
    Goal* p = first;
    while (p < last) {
        DestroyActElem((ActStep*)p);
        p += 1;
    }
}

// ===========================================================================
// UI::cScenarioPlayProgressBar
// ===========================================================================
typedef void (*MsgFn24)(void*, void*, uint);

struct Bar
{
    void* v00;                       // +0x00
    void* v04;                       // +0x04
    void* v08;                       // +0x08
    char  pad0c[0x10];               // +0x0c .. +0x1b
    void* f1c;
    char  pad20[0x28];               // +0x20 .. +0x47
    float f48; float f4c; float f50; // +0x48 ..
    void* f54; void* f58; void* f5c; // string16 at +0x54
    char  pad60[4];
    GoalVec goals;                   // +0x64 .. +0x6f
    void* f70; void* f74; void* f78; // +0x70 ..
    void* f7c;                       // +0x7c  message server + handler args
    void* f80; void* f84; void* f88; void* f8c;
    char  pad90[8];                  // +0x90
    char  sw98[0x18];                // +0x98  EA::Stopwatch
    char  padb0[8];                  // +0xb0
    void* fb8;                       // +0xb8
    int   fbc;                       // +0xbc
    void* fc0;                       // +0xc0
    char  padc4[0x18];               // +0xc4 .. +0xdb
    float fdc;                       // +0xdc
    float fe0; float fe4; float fe8; // +0xe0 ..
    uint8_t fec;                       // +0xec
    char  paded[3];
    void* ff0; void* ff4;            // +0xf0
    float ff8;                       // +0xf8
    uint8_t ffc; uint8_t ffd;            // +0xfc, +0xfd
    uint8_t pade[2];
    void* f100;                      // +0x100

    Bar();
    ~Bar();
    void Init();
    void Update();
    void Scans();
    void Reset();                                   // 0x00f190a0
    void* EachChild(void* id, int cnt);             // 0x00f19660
    void AddGoal8(void* g, void* c, int x);         // 0x00f1ae10
    void AddGoal5(void* g, void* c);                // 0x00f1ae10
};

extern char gBarVtbl0[];             // 0x0148c2fc
extern char gBarVtbl1[];             // 0x0148c2ec
extern char gBaseVtbl1[];            // 0x013ec458
extern char gBaseVtbl0[];            // 0x013eb394
extern void* gMsgIdTable[20];        // 0x0148c268
extern uint8_t gEmptyString16[];     // 0x01667bac

extern float gCfg0;                  // 0x016c826c
extern float gCfg1;                  // 0x016c8270
extern float gCfg2;                  // 0x016c8274
extern float gFtoc;                  // 0x0148c2b8

extern float gT924;                  // 0x015ad924
extern float gT928;                  // 0x015ad928
extern float gT92c;                  // 0x015ad92c
extern float gT930;                  // 0x015ad930
extern float gT934;                  // 0x015ad934
extern float gT938;                  // 0x015ad938
extern float gT93c;                  // 0x015ad93c
extern float gT940;                  // 0x015ad940
extern float gT944;                  // 0x015ad944
extern float gT948;                  // 0x015ad948
extern float gT958;                  // 0x015ad958
extern float gT95c;                  // 0x015ad95c
extern uint  gT94c;                  // 0x015ad94c
extern uint  gT950;                  // 0x015ad950
extern uint  gT954;                  // 0x015ad954

extern void* gT82bc;                 // 0x016c82bc
extern void* gT82d0;                 // 0x016c82d0
extern void* gT82e4;                 // 0x016c82e4
extern void* gT82f8;                 // 0x016c82f8
extern void* gStartup;               // 0x016c7aa4

// ---------------------------------------------------------------------------
// @ 0x00f1e450
Bar::Bar()
{
    char* p = (char*)this;
    v04 = gBaseVtbl1;
    v08 = 0;
    v00 = gBarVtbl0;
    v04 = gBarVtbl1;
    *(void**)(p + 0x0c) = 0;
    *(void**)(p + 0x10) = 0;
    *(void**)(p + 0x14) = 0;
    *(void**)(p + 0x18) = 0;
    *(void**)(p + 0x1c) = 0;
    *(void**)(p + 0x20) = 0;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x28) = 0;
    *(void**)(p + 0x2c) = 0;
    *(void**)(p + 0x30) = 0;
    *(void**)(p + 0x34) = 0;
    *(void**)(p + 0x38) = 0;
    *(void**)(p + 0x3c) = 0;
    *(void**)(p + 0x40) = 0;
    *(void**)(p + 0x44) = 0;
    *(float*)(p + 0x48) = 0.0f;
    *(float*)(p + 0x4c) = 0.0f;
    *(float*)(p + 0x50) = 0.0f;
    *(void**)(p + 0x5c) = gEmptyString16 + 2;
    *(void**)(p + 0x54) = gEmptyString16;
    *(void**)(p + 0x58) = gEmptyString16;
    *(void**)(p + 0x64) = 0;
    *(void**)(p + 0x68) = 0;
    *(void**)(p + 0x6c) = 0;
    ((Stopwatch*)sw98)->Init(0, 0);
    *(void**)(p + 0x7c) = 0;
    *(void**)(p + 0x80) = 0;
    *(void**)(p + 0x84) = 0;
    *(void**)(p + 0x88) = 0;
    *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xc0) = 0;
    *(float*)(p + 0xdc) = 0.0f;
    *(float*)(p + 0xe0) = gCfg0;
    *(float*)(p + 0xe4) = gCfg1;
    *(float*)(p + 0xe8) = gCfg2;
    *(uint8_t*)(p + 0xec) = 0;
    *(void**)(p + 0xf0) = 0;
    *(void**)(p + 0xf4) = 0;
    *(uint8_t*)(p + 0xfc) = 0;
    *(uint8_t*)(p + 0xfd) = 0;
    *(float*)(p + 0xf8) = 0.0f;
    *(void**)(p + 0x100) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e580  UI::cScenarioPlayProgressBar::~cScenarioPlayProgressBar
// ---------------------------------------------------------------------------
// @ 0x00f1e580
Bar::~Bar()
{
    if (f100)
        ((BarIface*)f100)->vt04();
    if (f7c) {
        void* h = f7c;
        f7c = 0;
        Messaging__RemoveHandler(h, f80, f84, f88, f8c);
    }
    goals.destroyRange(goals.b, goals.e);
    if (goals.b && ((int*)goals.b)[-1] != 0)
        operator_delete__(goals.b);
    if ((((char*)f5c - (char*)f54) & ~1) > 2 && f54)
        operator_delete__(f54);
    v04 = gBaseVtbl1;
    v00 = gBaseVtbl0;
}

// ---------------------------------------------------------------------------
// @ 0x00f1e020  UI::cScenarioPlayProgressBar::ReadConfig
// ---------------------------------------------------------------------------
struct Prop;
// property lookup: object vtable slot +0x24, returns non-zero when found
static inline bool GETPROP(void* obj, int id, void** out)
{
    void* p;
    return ((uint8_t(*)(void*, int, void**))(*(void**)((*(char**)obj) + 0x24)))(obj, id, out) != 0;
}

#define PROP(id, type, dst)                                              \
    if (GETPROP(t, id, &prop) && *(short*)((uint8_t*)prop + 0x12) == (type)) {   \
        dst = *GetProperty(prop);                                        \
    }

// @ 0x00f1e020
void ReadConfig()
{
    void* t = ((TerrainMgr*)SP_TerrainMgr())->GetTerrain();
    if (t) {
        void* prop;
        PROP(0x6d95f3cc, 0xd, gT924)
        PROP(0x75960042, 0xd, gT928)
        PROP(0x557d26dd, 0xd, gT92c)
        PROP(0x5d7d3333, 0xd, gT930)
        PROP(0xf1088439, 0xd, gT934)
        PROP(0xe90877c7, 0xd, gT938)
        PROP(0xf5a523fa, 0xd, gT93c)
        PROP(0x11fbb285, 0xd, gT940)
        PROP(0x4c764f09, 0xd, gT944)
        PROP(0x5830f113, 0xd, gT948)
        if (GETPROP(t, 0xc4331ecc, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT94c = *SP_GetPropertyAsUInt(prop);
        }
        if (GETPROP(t, 0x9944b6fb, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT950 = *SP_GetPropertyAsUInt(prop);
        }
        if (GETPROP(t, 0x5356e603, &prop) && *(short*)((uint8_t*)prop + 0x12) == 0xa) {
            gT954 = *SP_GetPropertyAsUInt(prop);
        }

        unsigned n = 0;
        void* data = 0;
        FUN_006a0b50(t, 0x10f28fd, (int*)&n, &data);
        StringVec__resize(&gT82bc, n);
        FUN_00f1dcc0(&gT82bc, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0x3ddba715, (int*)&n, &data);
        StringVec__resize(&gT82d0, n);
        FUN_00f1dcc0(&gT82d0, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0xb7afd508, (int*)&n, &data);
        StringVec__resize(&gT82e4, n);
        FUN_00f1dcc0(&gT82e4, data, (char*)data + (n << 4));

        n = 0; data = 0;
        FUN_006a0b50(t, 0x5a651c41, (int*)&n, &data);
        StringVec__resize(&gT82f8, n);
        FUN_00f1dcc0(&gT82f8, data, (char*)data + (n << 4));

        PROP(0x92c289d3, 0xd, gT958)
        PROP(0x8ea88cc3, 0xd, gT95c)
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1e620  UI::cScenarioPlayProgressBar::Init
// ---------------------------------------------------------------------------
// @ 0x00f1e620
void Bar::Init()
{
    ((Stopwatch*)sw98)->SetUnits(4);
    ReadConfig();
    ffd = 0;
    void* m = SP_MessageServer();
    f7c = m;
    f80 = this;
    f84 = gMsgIdTable;
    f88 = (void*)0x14;
    f8c = 0;
    if (m) {
        uint i = 0;
        do {
            ((MsgSendFn)(*(void**)((char*)(*(void**)m) + 0x24)))(m, this, *(uint*)((char*)gMsgIdTable + i));
            i += 4;
        } while (i < 0x50);
    }
    Reset();
}

// ---------------------------------------------------------------------------
// @ 0x00f1e6a0  UI::cScenarioPlayProgressBar::Scans
// ---------------------------------------------------------------------------
// @ 0x00f1e6a0
void Bar::Scans()
{
    // creature-base pass
    {
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xae72d0, 0xb1e500, 0x18c6de8);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            FUN_00ca6db0(o);
            EachChild2(o ? o + 0x508 : 0);
        }
    }
    // creature pass (skipping the active one)
    {
        void* active = FUN_00989360(SP_NounManager());
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xace0f0, 0xb1e500, 0x18eb45e);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            if (FUN_00c04590(o) != active) {
                FUN_00c06f70(o);
                EachChild2(o ? o + 0x5a8 : 0);
            }
        }
    }
    // space-inventory pass
    {
        uint8_t* v = (uint8_t*)GetGameDataVector(SP_NounManager(), 0xcd7d10, 0xd3d420,
                                            0xb5f990, 0xb1e520, 0x70704db);
        void** b = (void**)(v + 4);
        void** e = (void**)(v + 8);
        for (void** i = b; i != e; ++i) {
            uint8_t* o = (uint8_t*)*i;
            uint8_t* q = o ? (uint8_t*)(*(void*(**)(uint8_t*, int))((char*)(*(void**)o) + 0xc))(o, 0x70704db) : 0;
            (*(void(**)(uint8_t*))((char*)(*(void**)q) + 0x90))(q);
            EachChild2(q + 0x120);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1ecf0  UI::cScenarioPlayProgressBar::Update
// ---------------------------------------------------------------------------
// @ 0x00f1ecf0
void Bar::Update()
{
    Goal* ob = goals.b;
    Goal* oe = goals.e;
    Goal* r = MoveRangeAssign(oe, oe, ob);
    goals.destroyRange(r, goals.e);
    goals.e += (oe - ob);

    uint8_t* base = (uint8_t*)this;
    base[0x78] = 0;
    base[0x79] = 0;
    fdc = gFtoc;
    fe0 = gCfg0;
    fe4 = gCfg1;
    fe8 = gCfg2;

    if ((char*)f54 != (char*)f58) {
        *(short*)f54 = 0;
        f58 = f54;
    }

    void* host = *(void**)((char*)gStartup + 0x74);
    void* act = ((ActHost*)host)->GetAct(fb8);
    if (act) {
        uint8_t* a = (uint8_t*)act;
        *(int*)(base + 0xbc) = *(int*)(a + 0x78) * 1000;
        uint8_t* ei = *(uint8_t**)(a + 0x84);
        uint8_t* ee = *(uint8_t**)(a + 0x88);
        int idx = 0;
        int goalOff = 0;
        if (ei != ee) {
            do {
                goals.emplace_back();
                uint8_t* g = (uint8_t*)goals.e - 0x1ac;
                g[0x00] = 0;
                g[0x01] = FUN_00f3b390(*(void**)ei);
                *(int*)(g + 0x04) = 0;
                *(void**)(g + 0x24) = *(void**)(ei + 0x00);
                *(void**)(g + 0x28) = *(void**)(ei + 0x04);
                *(void**)(g + 0x2c) = *(void**)(ei + 0x08);
                *(void**)(g + 0x30) = *(void**)(ei + 0x0c);
                g[0x34] = ei[0x10];
                *(void**)(g + 0x38) = *(void**)(ei + 0x14);
                *(Vec44*)(g + 0x3c) = *(Vec44*)(ei + 0x18);
                *(void**)(g + 0x1a8) = *(void**)(ei + 0x184);
                if (*(int*)(ei + 0x0c) == 0) {
                    void* p = ((ActHost*)host)->FindCreature(*(void**)(ei + 0x04));
                    if (p == 0 || ((CreatureObj*)p)->IsMarked() == 0) {
                        void* rr = ((ActHost*)host)->BuildGoal(fb8, ei, *(void**)(ei + 4), g, 0, 0, 0, 1);
                        *(void**)(g + 0x30) = rr;
                    }
                }
                if (*(int*)(g + 0x24) == 8) {
                    if (*(int*)(g + 0x30) != 1)
                        *(int*)(g + 0x30) = 1;
                    int cnt = 0;
                    void* c = EachChild(*(void**)(ei + 4), (int)&cnt);
                    if (c) {
                        AddGoal8(g, c, 0);
                        if (cnt > 1)
                            *(int*)(g + 0x04) += cnt - 1;
                    }
                }
                if (*(int*)(g + 0x24) == 5) {
                    uint8_t* inv = (uint8_t*)((Inventory*)SP_NounManager())->GetItemID();
                    int cnt = (int)(*(uint8_t**)(inv + 4) - *(uint8_t**)inv) >> 2;
                    for (int j = 0; j < cnt; ++j) {
                        uint8_t* it = *(uint8_t**)(*(uint8_t**)inv + j * 4);
                        if (*(int*)(it + 0x1c) == *(int*)(g + 0x28)) {
                            void* rv = ((ItemObj*)it)->v3(0x1186577, 0);
                            AddGoal5(g, rv);
                        }
                    }
                }
                int total = (int)(goals.e - goals.b);
                int g24 = *(int*)((char*)goals.b + goalOff + 0x24);
                if (idx < total && (g24 == 10 || g24 == 11))
                    base[0x79] = 1;
                else
                    base[0x78] = 1;
                ++idx;
                goalOff += 0x1ac;
                ei += 0x188;
            } while (ei != ee);
        }
    }
}
