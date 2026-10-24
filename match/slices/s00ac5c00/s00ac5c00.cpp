// Slice s00ac5c00: FUN_00ac5c00 (VA 0x00ac5c00, 2498 bytes), __fastcall(int) with a 256-entry
// stack array. Not started: no decompiled body yet. This file only keeps the slice compiling.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Shared declarations for the cAStar request helpers.
// ---------------------------------------------------------------------------

typedef unsigned char u8;
typedef unsigned int  u32;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct LargeInteger { int low; int high; };

struct VTable { void* slots[0x50 / 4]; };
struct Obj    { VTable* vt; };

struct Vec8 {
    void* begin;
    void* end;
    void* cap;
    void reserve(u32 n);            // 0xac4280
    void swap(Vec8* other);        // 0xac4d50
};
struct ListNode { ListNode* next; ListNode* prev; };

struct FixedAllocatorBase {
    char  pad[0x10];
    void* freeList;                 // +0x10
    bool AddCore(void* block, u32 size); // 0x926650
};

struct Request7;

struct CAStar {
    char  pad[0x1c];
    void* field1c;                  // +0x1c
    void* light1;                   // +0x20
    void* light2;                   // +0x24
    Vec8  pathVec;                  // +0x28
    char  pad2[0x3c - 0x34];
    FixedAllocatorBase* alloc;      // +0x3c
    ListNode sentinel;              // +0x40
    void release(void* handle);     // 0xac4ef0
    int step();                     // 0xac5c00
    int run(u32 limit);             // 0xac68e0
    u8 findPath(void* a1, void* a2, void* a3, void* a4, float f5, float f6); // 0xac6960
    void findPathFast(void* a1, void* a2, void* a3, void* a4, void* a5,
                      int a6, void* a7); // 0xac6a10
    void addRequest(void* a1, void* a2, void* a3, float f1, float f2,
                    void* a6, Request7* a7, int flag, void* a9); // 0xac65d0
};

struct ShadowMgr {
    char  pad[0x1c];
    void* field1c;                  // +0x1c
    u8    flag;                     // +0x20
    char  pad20[3];
    void* material;                 // +0x24
    float f28;                      // +0x28
    float f2c;                      // +0x2c
    float f30;                      // +0x30
    float f34;                      // +0x34
    void setMaterial();             // 0xac6a50
    void readProperties(int, int);  // 0xac6aa0
};

struct Chunk {
    Chunk* next;                    // +0x00
    Chunk* prev;                    // +0x04
    void*  owner;                   // +0x08
    void*  param6;                  // +0x0c
    u32    a2[3];                   // +0x10
    u32    a3[3];                   // +0x1c
    float  lo;                      // +0x28
    float  hi;                      // +0x2c
    u8     flag;                    // +0x30
    u8     pad[3];
    u32    a1[5];                   // +0x34
    void*  a9;                      // +0x48
};

struct Request7 {
    char   pad[4];
    Chunk* chunk;                   // +0x04
};

struct PathResult {
    void* vt;                       // +0x00
    void* field4;                   // +0x04
    u8    field8;                   // +0x08
};

struct LimitStopwatch {
    char pad[0x18];
    int  endLow;                    // +0x18
    int  endHigh;                   // +0x1c
    void ctor(int type, int start);            // 0x93a560
    void SetTimeLimit(u32 limit, int start);   // 0x93a480
};

struct MemPool {
    void* LockedAligned(u32 a, u32 b, int c, int d, int e, int f, int g, int h); // 0x928a30
    void releaseLight(void* light);                                             // 0x9276c0
};

struct PlanetModelOps { int update(); };   // 0xb88420
struct TerrainOps     { void* getList(); };// 0xb1de80

extern "C" void* __cdecl SP_MaterialManager();                    // 0x67dd70
extern "C" void* __cdecl FUN_0067dd50();                          // 0x67dd50
extern "C" void* __cdecl PlanetModel_0b3d350();                   // 0xb3d350
extern "C" void* __cdecl FUN_00b3d290();                          // 0xb3d290
extern "C" __declspec(dllimport) int __stdcall
QueryPerformanceCounter(LargeInteger*);                           // IAT 0x13cc2b8

void __cdecl Free_47380(void* p);                                 // 0xf47380
void* __cdecl FUN_00b3d320();                                     // 0xb3d320
bool __cdecl GetPropertyAsVector2(void* list, u32 key, float* out); // 0x6a10c0

struct cProperty {
    char  pad[0x12];
    short kind;                     // +0x12
    bool* __thiscall GetBool();     // 0x41e920
};

extern Obj*     g_appProperties_15fd918;   // 0x15fd918
extern MemPool* g_16c8b44;                 // 0x16c8b44

extern u32 g_167a220;                      // 0x167a220
extern u32 g_167a224;                      // 0x167a224
extern u32 g_167a228;                      // 0x167a228
extern u32 g_167a22c;                      // 0x167a22c
extern u32 g_167a230;                      // 0x167a230

extern float kf_1471064;                   // 0x1471064 = 0.5f
extern float kf_1459e18;                   // 0x1459e18 = 7.04f
extern float kf_1485378;                   // 0x1485378 = 0.0f

extern char VT_1459ed0[];              // 0x1459ed0
extern char VT_1459e50[];              // 0x1459e50

// @ 0x00ac68e0
// Run the A* request queue until the stopwatch expires.
int CAStar::run(u32 limit)
{
    LimitStopwatch sw;
    sw.ctor(4, 0);
    sw.SetTimeLimit(limit, 1);
    void* pm = PlanetModel_0b3d350();
    int result = ((PlanetModelOps*)pm)->update();
    ListNode* sentinel = &this->sentinel;
    if (sentinel->prev == sentinel)
        return result;
    do {
        LargeInteger now;
        QueryPerformanceCounter(&now);
        long long diff = *(long long*)&sw.endLow - *(long long*)&now;
        if (diff < 0)
            return (int)diff;
        result = this->step();
    } while (sentinel->prev != sentinel);
    return result;
}

// @ 0x00ac6960
// Build one request, drain it, release the temporary path.
u8 CAStar::findPath(void* a1, void* a2, void* a3, void* a4, float f5, float f6)
{
    PathResult result;
    result.field4 = 0;
    result.vt = VT_1459ed0;
    result.field8 = 0;
    void* pm = PlanetModel_0b3d350();
    ((PlanetModelOps*)pm)->update();
    this->addRequest(a1, a2, a3, f5, f6, a4, (Request7*)&result, 1, 0);
    int count = (int)result.field4;
    if (count != 0) {
        do {
            this->step();
            count = (int)result.field4;
        } while (count != 0);
    }
    u8 ret = result.field8;
    result.vt = VT_1459e50;
    if (count != 0) {
        void* p = FUN_00b3d290();
        if (result.field4 != 0 && p != 0)
            ((CAStar*)p)->release(&result);
    }
    return ret;
}

// @ 0x00ac6a10
// Forward a request with a zero-width band.
void CAStar::findPathFast(void* a1, void* a2, void* a3, void* a4, void* a5,
                          int a6, void* a7)
{
    this->addRequest(a1, a2, a3, 0.0f, 0.0f, a4, (Request7*)a5, a6, a7);
}

// @ 0x00ac6a50
// Attach a material and register the light slot.
void ShadowMgr::setMaterial()
{
    ShadowMgr* self = this;
    int* piVar1 = (int*)SP_MaterialManager();
    typedef u32 (__thiscall* Fn1)(int*, u32);
    u32 uVar2 = (*(Fn1*)(*piVar1 + 0x28))(piVar1, 0x605e24f5u);
    *(u32*)((char*)self + 0x24) = uVar2;
    self = (ShadowMgr*)((char*)self + 0x1c);
    _ReadWriteBarrier();
    piVar1 = (int*)FUN_0067dd50();
    typedef void (__thiscall* Fn2)(int*, void*, int, int);
    (*(Fn2*)(*piVar1 + 0x4c))(piVar1, self, 0xb, 0);
}

// @ 0x00ac6aa0
// Read the shadow/light properties.
void ShadowMgr::readProperties(int, int)
{
    this->flag = 1;
    if (g_appProperties_15fd918 != 0) {
        cProperty* prop;
        typedef bool (__thiscall* Fn)(void*, u32, cProperty**);
        Fn fn = *(Fn*)((char*)g_appProperties_15fd918->vt + 0x24);
        if (fn(g_appProperties_15fd918, 0x539d9e5u, &prop) && prop->kind == 1) {
            u8 v = *(u8*)prop->GetBool();
            this->flag = v;
        }
    }
    if (this->flag != 0) {
        void* x = FUN_00b3d320();
        void* list = ((TerrainOps*)x)->getList();
        struct Vector2 { float x; float y; };
        Vector2 v;
        float y;
        if (GetPropertyAsVector2(list, 0x539d9e6u, &v.x)) {
            this->f30 = v.x;
            y = v.y;
        } else {
            this->f30 = 0.0f;
            y = 0.0f;
        }
        this->f34 = y;
        if (GetPropertyAsVector2(list, 0x539d9e7u, &v.x)) {
            this->f2c = v.x;
            this->f28 = v.y;
        } else {
            extern float kf_13ec4d0;    // 0x13ec4d0 = 100.0f
            extern float kf_14763b8;    // 0x14763b8 = 150.0f
            this->f2c = kf_13ec4d0;
            this->f28 = kf_14763b8;
        }
    }
}

// @ 0x00ac65d0
// Queue (or immediately execute) one A* request.
void CAStar::addRequest(void* a1, void* a2, void* a3, float f1, float f2,
                        void* a6, Request7* a7, int flag, void* a9)
{
    if (a7->chunk != 0)
        this->release(a7);

    float center = (f1 + f2) * kf_1471064;
    float half = (float)fabs(f2 - f1) * kf_1471064;
    if (half < kf_1459e18)
        half = kf_1459e18;

    FixedAllocatorBase* alloc = this->alloc;
    Chunk* chunk;
    for (;;) {
        if (alloc->freeList != 0) {
            chunk = (Chunk*)alloc->freeList;
            alloc->freeList = chunk->next;
            chunk->prev = 0;
            chunk->next = 0;
            break;
        }
        if (!alloc->AddCore(0, 0)) {
            chunk = 0;
            break;
        }
    }

    a7->chunk = chunk;
    chunk->owner = a7;
    chunk->param6 = a6;
    u32* s2 = (u32*)a2;
    chunk->a2[0] = s2[0];
    chunk->a2[1] = s2[1];
    chunk->a2[2] = s2[2];
    u32* s3 = (u32*)a3;
    chunk->a3[0] = s3[0];
    chunk->a3[1] = s3[1];
    chunk->a3[2] = s3[2];
    chunk->lo = center - half;
    chunk->hi = half + center;
    u32* s1 = (u32*)a1;
    chunk->a1[0] = s1[0];
    chunk->a1[1] = s1[1];
    chunk->a1[2] = s1[2];
    chunk->a1[3] = s1[3];
    chunk->a1[4] = s1[4];
    chunk->flag = (f1 == kf_1485378);
    chunk->a9 = a9;

    if ((char)flag != 0) {
        void* old1 = this->light1;
        void* old2 = this->light2;
        this->light1 = g_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
        this->light2 = g_16c8b44->LockedAligned(0x60000, 0x10, 0, 0, 0, 0, 0, 0);
        u32 g0, g1, g2, g3, g4;
        Vec8 oldPath;
        oldPath.begin = 0;
        oldPath.end = 0;
        oldPath.cap = 0;
        oldPath.swap(&this->pathVec);
        this->pathVec.reserve((u32)(((char*)oldPath.end - (char*)oldPath.begin) >> 3));
        g0 = g_167a220;
        g1 = g_167a224;
        g2 = g_167a228;
        g3 = g_167a22c;
        g4 = g_167a230;
        void* pm = PlanetModel_0b3d350();
        ((PlanetModelOps*)pm)->update();
        Chunk* head2 = (Chunk*)&this->sentinel;
        chunk->next = head2->next;
        chunk->prev = head2;
        head2->next = chunk;
        chunk->next->prev = chunk;
        while (a7->chunk != 0)
            this->step();
        g_16c8b44->releaseLight(this->light1);
        g_16c8b44->releaseLight(this->light2);
        this->light1 = old1;
        this->light2 = old2;
        this->pathVec.swap(&oldPath);
        g_167a220 = g0;
        g_167a224 = g1;
        g_167a228 = g2;
        g_167a22c = g3;
        g_167a230 = g4;
        if (oldPath.begin != 0 && *(int*)((char*)oldPath.begin - 4) != 0)
            Free_47380(oldPath.begin);
    } else {
        Chunk* head = (Chunk*)&this->sentinel;
        if (a9 == 0) {
            chunk->prev = head->prev;
            chunk->next = head;
            head->prev = chunk;
            chunk->prev->next = chunk;
            return;
        }
        Chunk* node = head->next;
        while (node != head) {
            if (node->a9 == a9) {
                Chunk* prev = node->prev;
                node->prev = chunk;
                prev->next = chunk;
                chunk->prev = prev;
                chunk->next = node;
                return;
            }
            node = node->next;
        }
        chunk->prev = head->prev;
        chunk->next = head;
        head->prev = chunk;
        chunk->prev->next = chunk;
    }
}
