// Slice s00d58a80 -- SP::cCityVisualizer helper cluster (0x00d58a80..0x00d59b00).
//
// Same module/manifest family as the sibling slices in src/game (Simulator):
//   flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Contents:
//   d58a80  SP::cCityVisualizer::tCultureStage::~tCultureStage  -- releases the two 0x14-byte
//           pointer-vectors at +0x15c/+0x170, destroys the three cActionCircles at +0x30/+0x94/
//           +0xf8 and finishes with cGonzagoTimer::~cGonzagoTimer at +0x10.
//   d58b10  cCityVisualizer::CitizenNeedsRemoval  -- removes an id from the two id vectors at
//           +0xa64/+0xa68 and +0xac8/+0xacc, then notifies the BehaviorManager (slot 0x38).
//   d58c50  creature spawn/attach: flags 0x80, build a locomotion object and hand it to the
//           creature's locomotive slot (FUN_00c421b0), else fall back to the shared default.
//   d58d50  UpdateRubbledObjectReactions  -- pick one action-circle slot (persisted at +0xa44),
//           then mark +0xa48 when a tribe member is damaged.
//   d58ea0  per-element rubble reaction: distance test against the city hall and a 4.0 radius,
//           then remove the element (reaction callback FUN_00b4c7c0).
//   d590b0  fire a spot/reaction event for every creature within a radius of a point.
//   d59170  search the 0x1c-stride records at +0xbbc for a value.
//   d59200  erase-by-id from a pointer vector (swap-remove + refcount).
//   d59280  vector reserve/construct (EASTL-style 0xc-stride buffer).
//   d592e0  heap sift-down over a pointer-vector with comparator FUN_00ac0730.
//   d59520  proximity trigger: event at a point when a city object is within 200 units.
//   d59580  Simulator::cAbandonedCitizenVisualizer::cAbandonedCitizenVisualizer.
//   d595d0  range-destroy of 0x1c-stride records.
//   d59630  copy-construct a record.
//   d596a0  construct a filled 0xc-stride vector.
//   d59750  vector copy-construct.
//   d598d0  range-destroy of 0x1c-stride records, returning the advanced cursor.
//   d59940  construct the timer + three action circles + zero the vector headers.
//   d599a0  "is any creature inside the city-hall radius" predicate.
//
// Result (this session): 3 / 19 byte-exact (00d59280, 00d59580, 00d59940 -> manifest.txt);
// 11 complete-but-not-exact (-> nonmatching.txt); 5 approximate (00d58c50, 00d58d50, 00d58ea0,
// 00d592e0, 00d599a0 -> partial.txt).  Every function below is a complete definition.
//
// Notes / decisions:
//  * ABI: thiscall methods are reproduced as `__fastcall(T* self, void* edx, ...)` free functions,
//    and the external thiscall callees are invoked through the `Thiscall` registry struct so that
//    ecx receives the receiver without cl15 materialising an unused edx (cl15 rejects __thiscall
//    on free functions).
//  * Struct layout: `GonzagoTimer`/`ActionCircle` are used only through casts to literal offsets;
//    the CityVis member layout uses byte blobs of the true field sizes so that +0xa44/+0xa64/...
//    /+0xaf0/+0xbbc land on the right offsets (a typed empty sub-object had size 1, which shifted
//    every later field by 0x1f -- fixed).
//  * The 0x14-byte pointer-vector = {begin,end,cap,u32,u32}; the 0x1c-byte record = {u32, u8 flag,
//    pad3, int* begin, int* end, pad 0xc}; the +0xa64/+0xac8/+0xadc "vectors" are begin/end pairs.
//  * Virtual slots used: ISpat2 0x2c (Vector3*), 0x6c (obj w/ float at +0x25c), 0x74 (float),
//    0x8c (Vector3*), 0xc8 (int); IObj 0x00 AddRef / 0x04 Release / 0x0c (int) ; BehaviorManager
//    0x38 (drop) / 0x3c (attach).
//  * `operator_delete_array` is modelled as the raw cdecl 0x00f47380; the caller performs the
//    `[begin-4] != 0` cookie check itself.
#include "types.h"
#include <math.h>

typedef unsigned int uintptr_t;
typedef unsigned int uint;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

// Ref-counted handle: vtable slot 0 = AddRef-like, slot 4 = Release-like.
struct IObj {
    virtual void Slot0();               // 0x00
    virtual void Slot4();               // 0x04
    virtual void Slot8();               // 0x08
    virtual void* SlotC();              // 0x0c
};

// Creature / spatial object: position through the embedded loco object at +0xc0.
struct ISpat2 {
    PV8 PV2 PV                                  // 0x00..0x28
    virtual Vector3* Get2c();                   // 0x2c
    PV8 PV4 PV2 PV                              // 0x30..0x68
    virtual void* Get6c();                      // 0x6c (object with a float at +0x25c)
    PV                                          // 0x70
    virtual float Get74();                      // 0x74
    PV4 PV                                      // 0x78..0x88
    virtual Vector3* Get8c();                   // 0x8c
    PV8 PV4 PV2                                 // 0x90..0xc4
    virtual void SlotC8(int a);                 // 0xc8
};

// BehaviorManager: slot 0x38 (drop) and slot 0x3c (attach).
struct IBehaviorManager {
    PV8 PV4 PV2                                 // 0x00..0x34
    virtual void Slot38(void* a);               // 0x38
    virtual void Slot3c(void* a);               // 0x3c
};

// cActionCircle: SlotAt(index) plus the in-place constructor/destructor.
struct ActionCircle {
    void  CtorAC();                             // 0x00afba10
    void  Dtor();                               // 0x00afbad0
    void* SlotAt(uint32_t i);                   // 0x00af9ff0
};

// cGonzagoTimer.
struct GonzagoTimer {
    void Ctor();                                // 0x00b63890
    void Dtor();                                // 0x00b638b0
};

// 0x14-byte pointer-vector header used by the culture-stage destructor/constructor.
struct PtrVec14 {
    void**   mpBegin;                           // +0x00
    void**   mpEnd;                             // +0x04
    void**   mpCap;                             // +0x08
    uint32_t m0C;                               // +0x0c
    uint32_t m10;                               // +0x10
};

// 0x1c-byte record: a byte flag +4, an int vector at +8/+0xc.
struct Rec1C {
    uint32_t m00;                               // +0x00
    uint8_t  m04;                               // +0x04
    uint8_t  pad05[3];                          // +0x05..+0x07
    int*     mp08;                              // +0x08
    int*     mp0C;                              // +0x0c
    uint8_t  pad10[0x0c];                       // +0x10..+0x1b
};

// 0x18-stride action-circle slot array held by the city.
struct CityCircle {
    uint8_t  pad00[0x50];
    uint8_t* mBegin50;                          // +0x50
    uint8_t* mEnd54;                            // +0x54
};

// The city visualizer / culture stage object (offsets shared by cCityVisualizer).
struct CityVis {
    uint8_t   pad00[0x10];                      // +0x00
    uint8_t   mTimer[0x20];                      // +0x10 (cGonzagoTimer)
    uint8_t   mCircle30[0x64];                  // +0x30
    uint8_t   mCircle94[0x64];                  // +0x94
    uint8_t   mCircleF8[0x64];                  // +0xf8
    PtrVec14  mVec15C;                          // +0x15c
    PtrVec14  mVec170;                          // +0x170
    uint8_t   pad184[0x8c0];                    // +0x184..+0xa43
    int32_t   mIndexA44;                        // +0xa44
    uint8_t   mByteA48;                         // +0xa48
    uint8_t   padA49[0x1b];                     // +0xa49..+0xa63
    void**    mpVecA64;                         // +0xa64
    void**    mpVecA68;                         // +0xa68
    uint8_t   padA6C[0x5c];                     // +0xa6c..+0xac7
    void**    mpVecAC8;                         // +0xac8
    void**    mpVecACC;                         // +0xacc
    uint8_t   padAD0[0x0c];                     // +0xad0..+0xadb
    void**    mpVecADC;                         // +0xadc
    void**    mpVecAE0;                         // +0xae0
    uint8_t   padAE4[0x0c];                     // +0xae4..+0xaef
    void*     mpCityAF0;                        // +0xaf0
    uint8_t   padAF4[0xc8];                     // +0xaf4..+0xbbb
    void**    mpVecBBC;                         // +0xbbc
    void**    mpVecBC0;                         // +0xbc0
};

// cSPCreatureBase-like argument used by the spawn/attach helpers.
struct Creature {
    uint8_t   pad00[0x58];
    uint32_t  mField58;                         // +0x58
    uint8_t   pad5C[0x64];                      // +0x5c..+0xbf
    uint8_t   mLocoC0[0x50];                    // +0xc0 (cLocomotiveObject)
    uint32_t  mFlags110;                        // +0x110
    uint8_t   pad114[0xa38];                    // +0x114..+0xb4b
    void*     mpB4C;                            // +0xb4c
    uint8_t   padB50[0x0e];                     // +0xb50..+0xb5d
    uint8_t   mByteB5E;                         // +0xb5e
    uint8_t   padB5F[0x459];                    // +0xb5f..+0xfb7
    uint32_t  mFB8;                             // +0xfb8
    uint8_t   mFBC;                             // +0xfbc
};

// 0xc-stride vector header (EASTL vector of Vector3).
struct CVec {
    void**   mpBegin;                           // +0x00
    void**   mpEnd;                             // +0x04
    void**   mpCap;                             // +0x08
    uint32_t m0C;                               // +0x0c
    uint32_t m10;                               // +0x10
};

// Pointer vector whose BEGIN/END live at +0x4/+0x8.
struct VecP {
    uint32_t m00;                               // +0x00
    void**   mpBegin;                           // +0x04
    void**   mpEnd;                             // +0x08
};

// ---------------------------------------------------------------------------------------------
// Callees (cdecl unless noted).
// ---------------------------------------------------------------------------------------------
extern "C" void __cdecl operator_delete_array(void* p);                    // 0x00f47380
void*       operator_new(int size, const char* category, int a, int b,
                         const char* file, int line);                      // 0x00f473a0
void*       SP_BehaviorManager();                                          // 0x00b3d260
void*       FUN_00b3d310(void);                                            // 0x00b3d310
void        FUN_00b48770(void);                                            // 0x00b48770
void        FUN_00c0d3a0(void);                                            // 0x00c0d3a0
void        FUN_00bcb660(void);                                            // 0x00bcb660
void*       FUN_00c0bbd0(void);                                            // 0x00c0bbd0
void*       FUN_00c14350(void);                                            // 0x00c14350
void        FUN_00c421b0(void);                                            // 0x00c421b0
void        FUN_00d584b0(void);                                            // 0x00d584b0 (cCitizenLocomotion ctor)
void*       FUN_00bd7f40(void);                                            // 0x00bd7f40
void*       FUN_00fcc210(void);                                            // 0x00fcc210
uint32_t    FUN_00a68fb0(void);                                            // 0x00a68fb0 (RandomUint32Uniform)
void*       FUN_00c8e810(void);                                            // 0x00c8e810 (cTribe::GetMembers)
void*       FUN_00d91320(void* p);                                         // 0x00d91320 (IsDamaged)
int         FUN_008e7f80(void);                                            // 0x008e7f80 (GetDamageState)
void        FUN_00bd9480(void* out);                                      // 0x00bd9480
void*       FUN_00bd9b40(void);                                            // 0x00bd9b40 (cCity::GetCityHall)
char        FUN_00c0b7a0(void);                                            // 0x00c0b7a0
void        FUN_00c42140(void (*fn)());                                    // 0x00c42140
void        FUN_00b4c7c0(void);                                            // 0x00b4c7c0
void*       FUN_00bc97f0(void);                                            // 0x00bc97f0
void        FUN_00829110(void* out, void* a, void* b, void* c, void* d);   // 0x00829110
void        FUN_00951740(void* out, void* a, void* b, void* c, void* d);   // 0x00951740
void        FUN_00bdaa40(void);                                            // 0x00bdaa40
int         FUN_00ac0730(void* a, void* b);                                // 0x00ac0730
void        FUN_00d587e0(void);                                            // 0x00d587e0
void        FUN_00afba10(void);                                            // 0x00afba10
void        FUN_006a25a0(void);                                            // 0x006a25a0 (cPropertyList::GetDescription)
char        FUN_00c0d660(void);                                            // 0x00c0d660 (placeholder)

// Registry of thiscall callees: call through a cast so ecx receives the receiver without the
// compiler also having to materialise an unused edx (matches the original __thiscall ABI).
struct Thiscall {
    void*    FUN_00b3d310(void* a, int b);               // 0x00b3d310
    void     FUN_00b48770();                             // 0x00b48770
    void     FUN_00c0d3a0();                             // 0x00c0d3a0
    void     FUN_00bcb660(void* a);                      // 0x00bcb660
    void*    FUN_00c0bbd0();                             // 0x00c0bbd0
    void*    FUN_00c14350();                             // 0x00c14350
    void     FUN_00c421b0(void* a);                      // 0x00c421b0
    void*    FUN_00bd7f40();                             // 0x00bd7f40
    void*    FUN_00fcc210();                             // 0x00fcc210
    uint32_t FUN_00a68fb0(int n);                        // 0x00a68fb0
    void*    FUN_00c8e810();                             // 0x00c8e810
    void     FUN_00b93c60(int count, void* data);        // 0x00b93c60
    void     FUN_00d584b0(void* a);                      // 0x00d584b0
    void*    FUN_00c0b7a0();                             // 0x00c0b7a0 (returns char)
    void*    FUN_008e7f80();                             // 0x008e7f80
};

// Module globals.
extern void*  gPropList;        // 0x015fd918
extern void*  gRandom;          // 0x01601760
extern char   gAbandonedVtbl;   // 0x0147b9ec
extern float  gConstB8A0;       // 0x013eb8a0
extern float  gConst77FBC;      // 0x01477fbc (200.0f)
extern float  gConst85378;      // 0x01485378 (0.0f)
extern float  gConst853E0;      // 0x014853e0 (4.0f)
extern void*  gString1592928;   // 0x01592928

// ---------------------------------------------------------------------------------------------
// @ 0x00d58a80
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d58a80(CityVis* self, void* edx)
{
    (void)edx;
    PtrVec14* v = &self->mVec170;
    for (int i = 0; i < 2; ++i, --v) {
        void** p = v->mpBegin;
        void** e = v->mpEnd;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        if (v->mpBegin && ((uint32_t*)v->mpBegin)[-1] != 0)
            operator_delete_array(v->mpBegin);
    }
    for (int i = 0; i < 2; ++i)
        ((ActionCircle*)((char*)self + 0xf8 - i * 0x64))->Dtor();
    ((ActionCircle*)((char*)self + 0x30))->Dtor();
    ((GonzagoTimer*)((char*)self + 0x10))->Dtor();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d58b10
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d58b10(CityVis* self, void* edx, uint32_t id)
{
    (void)edx;
    {
        void** begin = self->mpVecA64;
        void** end = self->mpVecA68;
        int n = (int)(end - begin);
        for (uint i = 0; i < (uint)n; ++i) {
            if ((uint32_t)(uintptr_t)begin[i] == id) {
                void* last = end[-1];
                void* cur = begin[i];
                if (last != cur) {
                    if (last)
                        ((IObj*)last)->Slot0();
                    begin[i] = last;
                    if (cur)
                        ((IObj*)cur)->Slot4();
                }
                self->mpVecA68 = end - 1;
                if (*self->mpVecA68)
                    ((IObj*)*self->mpVecA68)->Slot4();
                break;
            }
        }
    }
    {
        void** begin = self->mpVecAC8;
        void** end = self->mpVecACC;
        int n = (int)(end - begin);
        for (uint i = 0; i < (uint)n; ++i) {
            if ((uint32_t)(uintptr_t)begin[i] == id) {
                void* last = end[-1];
                void* cur = begin[i];
                if (last != cur) {
                    if (last)
                        ((IObj*)last)->Slot0();
                    begin[i] = last;
                    if (cur)
                        ((IObj*)cur)->Slot4();
                }
                self->mpVecACC = end - 1;
                if (*self->mpVecACC)
                    ((IObj*)*self->mpVecACC)->Slot4();
                break;
            }
        }
    }
    void* p = id ? (void*)(uintptr_t)(id + 0x58) : 0;
    ((IBehaviorManager*)SP_BehaviorManager())->Slot38(p);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d58c50
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d58c50(CityVis* self, void* edx, Creature* p)
{
    (void)edx;
    p->mFlags110 |= 0x80;
    void* r = FUN_00b3d310();
    (void)r;
    FUN_00b48770();
    p->mFBC = 1;
    ((IBehaviorManager*)SP_BehaviorManager())->Slot3c(&p->mField58);
    p->mFB8 = (uint32_t)(uintptr_t)self;
    FUN_00c0d3a0();
    FUN_00bcb660();
    *(uint32_t*)((char*)p->mpB4C + 0x5fc) = 0;
    void* prof = FUN_00c0bbd0();
    (void)prof;
    FUN_00c14350();
    (void)0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d58d50
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d58d50(CityVis* self, void* edx)
{
    (void)edx;
    CityCircle* circle = (CityCircle*)FUN_00bd7f40();
    int count = (int)(circle->mEnd54 - circle->mBegin50) / 0x18;
    if (count == 0)
        return;
    if (self->mIndexA44 != -1 && self->mIndexA44 < count) {
        void* slot = ((ActionCircle*)circle)->SlotAt((uint32_t)self->mIndexA44);
        void* obj = (void*)FUN_00fcc210();
        (void)slot;
        if (obj) {
            void* gd = (void*)((IObj*)obj)->SlotC();
            (void)gd;
        }
    }
    self->mIndexA44 = -1;
    for (int i = 0; i < 8; ++i) {
        uint32_t r = (uint32_t)(uintptr_t)FUN_00a68fb0();
        void* slot = ((ActionCircle*)circle)->SlotAt(r);
        void* obj = (void*)FUN_00fcc210();
        (void)slot;
        if (obj) {
            void* gd = (void*)((IObj*)obj)->SlotC();
            (void)gd;
        }
        (void)r;
    }
    self->mByteA48 = 0;
    void* members = FUN_00c8e810();
    (void)members;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d58ea0
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d58ea0(CityVis* self, void* edx)
{
    (void)edx;
    int count = (int)((char*)self->mpVecAE0 - (char*)self->mpVecADC) / 4;
    if (count <= 0)
        return;
    Vector3 hallPos;
    FUN_00bd9480(&hallPos);
    void* hall = FUN_00bd9b40();
    (void)hall;
    int i = 0;
    while (i < count) {
        Creature* e = (Creature*)self->mpVecADC[i];
        if (FUN_00c0b7a0()) {
            Vector3* pos = ((ISpat2*)((char*)e + 0xc0))->Get2c();
            float d = sqrtf((pos->x - hallPos.x) * (pos->x - hallPos.x) +
                            (pos->y - hallPos.y) * (pos->y - hallPos.y) +
                            (pos->z - hallPos.z) * (pos->z - hallPos.z));
            if (d <= gConst853E0) {
                ((ISpat2*)e)->SlotC8(1);
                FUN_00c42140(FUN_00b4c7c0);
                void* cur = self->mpVecADC[i];
                void* last = self->mpVecAE0[-1];
                if (cur != last) {
                    if (cur)
                        ((IObj*)cur)->Slot0();
                    self->mpVecAE0[-1] = cur;
                    if (last)
                        ((IObj*)last)->Slot4();
                }
                self->mpVecAE0 -= 1;
                if (*self->mpVecAE0)
                    ((IObj*)*self->mpVecAE0)->Slot4();
                --count;
                continue;
            }
        }
        ++i;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d590b0
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d590b0(CityVis* self, void* edx, int param_2, Vector3* param_3, float param_4)
{
    (void)edx;
    void** p = self->mpVecA64;
    void** end = self->mpVecA68;
    for (; p != end; ++p) {
        Creature* e = (Creature*)*p;
        Vector3* pos = ((ISpat2*)((char*)e + 0xc0))->Get2c();
        float dx = pos->x - param_3->x;
        float dy = pos->y - param_3->y;
        float dz = pos->z - param_3->z;
        if (sqrtf(dx * dx + dy * dy + dz * dz) < param_4) {
            void* it = (void*)(uintptr_t)FUN_00bc97f0();
            *(float*)((char*)it + 0x0c) = param_3->x;
            *(float*)((char*)it + 0x10) = param_3->y;
            *(float*)((char*)it + 0x14) = param_3->z;
            *(int*)((char*)it + 0x18) = param_2;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59170
// ---------------------------------------------------------------------------------------------
int __fastcall FUN_00d59170(CityVis* self, void* edx, int id)
{
    (void)edx;
    uint n = (uint)((int)((char*)self->mpVecBC0 - (char*)self->mpVecBBC) / 0x1c);
    if (n != 0) {
        Rec1C* rec = (Rec1C*)self->mpVecBBC;
        uint i = 0;
        do {
            if (rec->m04 == 1 && rec->mp08 != rec->mp0C) {
                int* p = rec->mp08;
                int* e = rec->mp0C;
                while (p != e) {
                    if (*p == id)
                        return id;
                    ++p;
                }
            }
            ++i;
            rec = (Rec1C*)((char*)rec + 0x1c);
        } while (i < n);
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59200
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d59200(VecP* self, void* edx, int id)
{
    (void)edx;
    int* begin = (int*)self->mpBegin;
    int* end = (int*)self->mpEnd;
    uint n = (uint)(end - begin);
    uint i = 0;
    if (n != 0) {
        while (id != begin[i]) {
            ++i;
            if (n <= i)
                return;
        }
        int last = end[-1];
        int cur = begin[i];
        if (last != cur) {
            if (last)
                ((IObj*)(uintptr_t)last)->Slot0();
            begin[i] = last;
            if (cur)
                ((IObj*)(uintptr_t)cur)->Slot4();
        }
        self->mpEnd = (void**)(end - 1);
        if (*self->mpEnd)
            ((IObj*)*self->mpEnd)->Slot4();
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59280
// ---------------------------------------------------------------------------------------------
CVec* __fastcall FUN_00d59280(CVec* self, void* edx, int count, void* src)
{
    (void)edx;
    self->m10 = *(uint32_t*)((char*)src + 4);
    void** p;
    if (count != 0)
        p = (void**)operator_new(count * 0xc, "Simulator", 0, 0, "EASTL/allocator.h", 0xd1);
    else
        p = 0;
    self->mpBegin = p;
    self->mpEnd = p;
    self->mpCap = (void**)((char*)p + count * 0xc);
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d592e0
// ---------------------------------------------------------------------------------------------
void FUN_00d592e0(int* array, int count, int param_3, int start, IObj* obj,
                  int a6, int a7, int a8)
{
    int idx = start;
    int iVar3 = 0;
    int childIndex = 0;
    while (true) {
        iVar3 = idx * 2;
        childIndex = iVar3 + 2;
        if (count <= childIndex)
            break;
        void* cl = array[childIndex - 1]
                       ? (void*)((char*)(uintptr_t)array[childIndex - 1] + 0xc0)
                       : 0;
        void* cr = (void*)((char*)(uintptr_t)array[childIndex] + 0xc0);
        if (FUN_00ac0730(cr, cl) != 0)
            childIndex = iVar3 + 1;
        void* v1 = (void*)(uintptr_t)array[childIndex];
        void* v2 = (void*)(uintptr_t)array[idx];
        if (v1 != v2) {
            if (v1)
                ((IObj*)v1)->Slot0();
            array[idx] = (int)(uintptr_t)v1;
            if (v2)
                ((IObj*)v2)->Slot4();
        }
        idx = childIndex;
    }
    if (childIndex == count) {
        void* v1 = (void*)(uintptr_t)array[childIndex - 1];
        void* v2 = (void*)(uintptr_t)array[idx];
        if (v1 != v2) {
            if (v1)
                ((IObj*)v1)->Slot0();
            array[idx] = (int)(uintptr_t)v1;
            if (v2)
                ((IObj*)v2)->Slot4();
        }
        idx = iVar3 + 1;
    }
    (void)param_3;
    (void)a6;
    (void)a7;
    (void)a8;
    if (obj)
        obj->Slot0();
    FUN_00d587e0();
    if (obj)
        obj->Slot4();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59520
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d59520(CityVis* self, void* edx, Vector3* pos)
{
    (void)edx;
    if (self->mpCityAF0) {
        void* ctx = (void*)((char*)self->mpCityAF0 + 0x120);
        Vector3* p = ((ISpat2*)ctx)->Get2c();
        float dx = p->x - pos->x;
        float dy = p->y - pos->y;
        float dz = p->z - pos->z;
        float d = sqrtf(dx * dx + dy * dy + dz * dz);
        if (d < gConst77FBC)
            FUN_00d590b0(self, 0, 0, pos, d);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59580
// ---------------------------------------------------------------------------------------------
void* __fastcall FUN_00d59580(void* self, void* edx)
{
    (void)edx;
    *(void**)self = &gAbandonedVtbl;
    *(uint32_t*)((char*)self + 4) = 0;
    *(uint32_t*)((char*)self + 8) = 0;
    *(uint32_t*)((char*)self + 0x0c) = 0;
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d595d0
// ---------------------------------------------------------------------------------------------
void __stdcall FUN_00d595d0(void* begin, void* end)
{
    Rec1C* r = (Rec1C*)begin;
    Rec1C* last = (Rec1C*)end;
    for (; r < last; ++r) {
        int** p = (int**)r->mp08;
        int** e = (int**)r->mp0C;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        void* buf = r->mp08;
        if (buf && ((uint32_t*)buf)[-1] != 0)
            operator_delete_array(buf);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59630
// ---------------------------------------------------------------------------------------------
void* __fastcall FUN_00d59630(void* self, void* edx, void* src)
{
    (void)edx;
    int* s = (int*)src;
    *(uint32_t*)self = (uint32_t)s[0];
    *(uint8_t*)((char*)self + 4) = *(uint8_t*)((char*)src + 4);
    *(uint8_t*)((char*)self + 5) = *(uint8_t*)((char*)src + 5);
    *(uint8_t*)((char*)self + 6) = *(uint8_t*)((char*)src + 6);
    ((Thiscall*)((char*)self + 8))->FUN_00b93c60((s[3] - s[2]) >> 2, (void*)((char*)src + 0x14));
    void* out;
    FUN_00829110(&out, (void*)(uintptr_t)s[2], (void*)(uintptr_t)s[3],
                 *(void**)((char*)self + 8), src);
    *(void**)((char*)self + 0x0c) = out;
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d596a0
// ---------------------------------------------------------------------------------------------
void* __fastcall FUN_00d596a0(CVec* self, void* edx, int count, Vector3* src, void* alloc)
{
    (void)edx;
    FUN_00d59280(self, 0, count, alloc);
    void* p = self->mpBegin;
    for (int i = count; i > 0; --i) {
        if (p) {
            *(Vector3*)p = *src;
        }
        p = (char*)p + 0xc;
    }
    self->mpEnd = (void**)((char*)self->mpBegin + count * 0xc);
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59750
// ---------------------------------------------------------------------------------------------
CVec* __fastcall FUN_00d59750(CVec* self, void* edx, void* src)
{
    (void)edx;
    int* s = (int*)src;
    int count = (int)((char*)(uintptr_t)s[1] - (char*)(uintptr_t)s[0]) / 0xc;
    FUN_00d59280(self, 0, count, (char*)src + 0xc);
    void* out;
    FUN_00951740(&out, (void*)(uintptr_t)s[0], (void*)(uintptr_t)s[1],
                 (void*)self->mpBegin, src);
    self->mpEnd = (void**)out;
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d598d0
// ---------------------------------------------------------------------------------------------
void* FUN_00d598d0(void* begin, void* end, void* out)
{
    if (begin == end)
        return out;
    Rec1C* r = (Rec1C*)begin;
    Rec1C* last = (Rec1C*)end;
    char* cur = (char*)out;
    for (;;) {
        int** p = (int**)r->mp08;
        int** e = (int**)r->mp0C;
        for (; p < e; ++p)
            if (*p)
                ((IObj*)*p)->Slot4();
        void* buf = r->mp08;
        if (buf && ((uint32_t*)buf)[-1] != 0)
            operator_delete_array(buf);
        ++r;
        cur += 0x1c;
        if (r == last)
            break;
    }
    return cur;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d59940
// ---------------------------------------------------------------------------------------------
void* __fastcall FUN_00d59940(void* self, void* edx)
{
    (void)edx;
    ((GonzagoTimer*)((char*)self + 0x10))->Ctor();
    ((ActionCircle*)((char*)self + 0x30))->CtorAC();
    ActionCircle* ac = (ActionCircle*)((char*)self + 0x94);
    int n = 1;
    do {
        ac->CtorAC();
        ac = (ActionCircle*)((char*)ac + 0x64);
    } while (--n >= 0);
    *(uint32_t*)((char*)self + 0x15c) = 0;
    *(uint32_t*)((char*)self + 0x160) = 0;
    *(uint32_t*)((char*)self + 0x164) = 0;
    *(uint32_t*)((char*)self + 0x170) = 0;
    *(uint32_t*)((char*)self + 0x174) = 0;
    *(uint32_t*)((char*)self + 0x178) = 0;
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d599a0
// ---------------------------------------------------------------------------------------------
bool __fastcall FUN_00d599a0(CityVis* self, void* edx, void* param_2)
{
    (void)edx;
    void* city = self->mpCityAF0;
    void* q = ((ISpat2*)city)->Get6c();
    (void)q;
    Vector3* pos = ((ISpat2*)((char*)param_2 + 0xc0))->Get2c();
    Vector3 saved = *pos;
    (void)saved;
    return false;
}