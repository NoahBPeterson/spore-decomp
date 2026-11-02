// src/game/SPGonzago/_at_00b30000.cpp -- migrated from slice(s) s00b3fe40, s00b3ef30, s00b3cf00, s00b3ac20, s00b3aaf0, s00b38190, s00b362c0, s00b35300 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b30000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyList.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include <math.h>
#include <new.h>
#include <EASTL/map.h>
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cLocomotiveObject.h"
#include <float.h>

// ---- items of slice s00b35300 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
#define VP16 VP4 VP4 VP4 VP4
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct RefObj {
    virtual int AddRef();
    virtual int Release();
};
struct Filter {
    u32 w0, w1, w2, w3;
    u32 e;
    u8  type;
    u8  z;
};
struct Prop {
    char pad[0x12];
    u16 type;
    float* GetFloat();                                   // 0x41ea70
};
struct PropBase {
    int GetModificationCount();                          // 0x6237a0
};
struct PropList {
    VP4 VP4 VP
    virtual bool Get(u32 id, Prop** out);                // 0x24
    char pad[0x2c];
    PropBase* parent;                                    // 0x30
    int count;                                           // 0x34
    int GetIntProperty(u32 id);                          // 0x6a2660
};
struct Obj;
struct ObjMgr {
    VP16 VP16 VP16 VP16 VP16 VP4 VP4 VP4
    virtual void Destroy(Obj* o, int flag);              // 0x170
};
struct Comp : RefObj {
    VP
    virtual RefObj* Query(u32 id);                       // 0xc
    VP4 VP VP VP
    virtual bool Fn2c();                                 // 0x2c
};
struct Key {
    u32 a, b, c;
    bool operator==(const Key& o) const { return a == o.a && b == o.b && c == o.c; }
};
struct CompA : RefObj {
    VP16 VP16 VP4
    virtual Key* GetKey();                               // 0x98
};
struct Obj {
    ObjMgr* mgr;                                         // 0
    int f4;
    int f8;
    float x, y, z;                                       // 0xc
    char pad1[0x28];
    int rc;                                              // 0x40
    char pad2[0x20];
    Comp* comp;                                          // 0x64
    char pad3[0x24];
    float f8c;                                           // 0x8c
};
struct Handle { int a; Obj* b; };
struct Res { bool Fn(); };                               // 0xb33e10
Res* __stdcall GetRes(u32 key);                          // 0xb3d240
struct RefPtr { RefObj* p; RefPtr& operator=(RefObj* o); };   // 0xb5f950
static inline RefObj* QueryComp(Comp* c, u32 id) { return c ? c->Query(id) : 0; }
static inline RefObj* QueryCompP(Comp** pc, u32 id) { Comp* c = *pc; return c ? c->Query(id) : 0; }
struct Thing2 { bool Fn(Vec3* a, Vec3* b, Vec3* c); };   // 0xc0f2e0
struct Thing {
    VP16 VP16 VP4 VP4 VP VP VP
    virtual Handle* GetHandle();                         // 0xac
    VP VP
    virtual Thing2* GetComp(u32 id);                     // 0xb8
};
struct World : RefObj {
    VP4 VP VP VP
    virtual Obj* Pick(int a, int b, int c, Vec3* out, int d, Filter* f, int e, int g);   // 0x24
    VP4
    virtual bool Cast(Vec3* p, float t, void* list, Filter* f);                      // 0x38
    VP VP
    virtual bool Cast2(Vec3* a, Vec3* b, Handle* h, float* t, Filter* f);            // 0x44
    VP16 VP16 VP16 VP4 VP VP VP
    virtual void SetInt(int a, int b, int v);            // 0x124
    VP VP VP
    virtual void SetFlag(int v);                         // 0x134
    VP
    virtual RefObj* GetLayer();                          // 0x13c
    VP4 VP
    virtual void SetFloat(float v);                      // 0x154
};
struct Elem {
    Obj* p;
    float f;
    Elem(const Elem& o) : p(o.p) { if (p) ++p->rc; f = o.f; }
};
struct LNode {
    LNode*  a;                                           // 4
    LNode** b;                                           // 8
    virtual ~LNode();
};
struct Listed : RefObj {
    VP4 VP4 VP4
    virtual void Detach();                               // 0x38
    char pad[0x10];
    LNode* node;                                         // 0x14
};
struct cSPEditorPhysicsWorld {
    char pad[0x174];
    cSPEditorPhysicsWorld();                             // 0x7c3f70
    ~cSPEditorPhysicsWorld();                            // 0x7c4000
    void Init(int);                                      // 0x7c4dd0
    void SetMode(int a, int b);                          // 0x7c3ce0
    void Shutdown();                                     // 0x7c3ba0
};
struct SceneB {                                          // FUN_00b3d320 result
    PropList* Fn2();                                     // 0xb1de80
};
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);
inline void* operator new(unsigned n, const char* name, int a, int b, int c, int d) {
    return operator_new(n, name, a, b, c, d);
}
World*       __cdecl GetGonzagoModelWorld();             // 0xb3d520
SceneB*      __cdecl GetSceneB();                        // 0xb3d320
struct NounInfo { char pad[0xc4]; Vec3 v; };
struct NounMgr { NounInfo* Get(); };                     // 0xb25f40
NounMgr*     __stdcall GetNounManager(u32 id);           // 0xb3d300
extern Vec3 g_defVec;                                    // 0x1569494
extern PropList* g_Props;                                // 0x15fd918
struct Owner {
    char pad0[0x2c];
    Obj** vbeg;                                          // 0x2c
    Obj** vend;                                          // 0x30
    char pad1[0x88 - 0x34];
    Listed* sel;                                         // 0x88
    char pad2[0xe4 - 0x8c];
    World* w1;                                           // 0xe4
    World* w2;                                           // 0xe8
    cSPEditorPhysicsWorld* phys;                         // 0xec
    char pad3[0x104 - 0xf0];
    int modCount;                                        // 0x104
    RefObj* fx;                                          // 0x108

    void Setup();                                        // 0xb35300
    void Teardown();                                     // 0xb35860
    void OnRemove(Listed* e);                            // 0xb35af0
    bool FindNearest(Vec3* pos, float t, u32 p4, RefObj** out);   // 0xb35d30
    bool Pick(int a, int b, u32 d, RefPtr* r, Vec3* out, u8 e);   // 0xb35ec0
};
static inline u8 IsFlagBit(int v) { u8 b = (u8)((u32)v >> 31); b &= 1; return b; }
float __fastcall SortKey(Obj* o);                        // 0xc887c0 (thiscall, float result)
void SiftDown_b33ea0(Obj** arr, int first, int hole, u32 v1, u32 v2);   // 0xb33ea0
struct Iter { Elem* p; Iter(Elem* q) : p(q) {} };
// ---- items of slice s00b35300 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vec3 g_defVec;                                    // 0x1569494
extern PropList* g_Props;                                // 0x15fd918

// ---- items of slice s00b362c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
extern "C" void  operator_delete(void* p);                                                    // 0xf47380
extern void* __stdcall SP_PlanetModel();                 // 0xb3d350
extern void* __stdcall SP_GonzagoModelWorld();           // 0xb3d520
extern void* __stdcall SP_EffectsManager();              // 0x67ddd0
extern const char g_str_Simulator[];   // 0x13f09b4
extern float g_f1486110;   // 5.0f
extern float g_f1418ef4;   // -5.0f
extern void* __stdcall RbtreeIncrement(void* node);            // 0x921580
extern void  __stdcall RBTreeErase(void* node, void* header);  // 0x921880
extern void __stdcall RBTreeInsert(void* node, void* parent, void* header, int side); // 0x9216a0
extern void __stdcall SortFunc1(void* a, void* b, void* c);   // 0xb363b0
extern void __stdcall SortFunc2(void* a, void* b, void* c);   // 0xb363f0
extern void __stdcall SortInsert(void* a, int b, int c, int d, void* e, void* f); // 0xb36180
extern float __fastcall SortKey(void* self);   // 0xc887c0 (ecx-based)
extern void* __stdcall Gonzago_Fn1(void* a, int b);    // 0xb3d320
extern void* __stdcall TerrainMgr_Fn1(void* a, int b); // 0xb1daf0
extern void* __stdcall GalaxyImpl_Fn7360(void* a);     // 0xad7360
extern "C" void* SlotMessage_Construct(void* self, int a);   // 0x421c80
extern "C" void  SlotMessage_Destruct(void* self);           // 0x421cf0
extern void* __stdcall PlanetModel_Fn0(void* a, int b);   // 0xb532b0
extern void* __fastcall PlanetModel_Fn1(void* self);       // 0xaef2e0
extern void* __stdcall PlanetModel_Fn2(void* a, int b);    // 0xad7360
extern void* g_167ecd0;   // 0x0167ecd0 planet placement manager
#define VS1(p)  virtual void p##_a();
#define VS2(p)  VS1(p##0) VS1(p##1)
#define VS4(p)  VS2(p##0) VS2(p##1)
#define VS8(p)  VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)
struct RefHandle;
struct RefOwner {
    VS64(v0) VS16(v1) VS8(v2) VS4(v3)
    virtual void Release(RefHandle* obj, bool sign);   // slot 92 (+0x170)
};
struct RefHandle {
    RefOwner* vtable;      // +0x00
    int field04;           // +0x04
    int pad[14];           // +0x08..0x40
    int refCount;          // +0x40

    // Decrement with release-to-pool when the last reference drops.
    void Decrement() {
        if (refCount > 1) {
            --refCount;
        } else {
            vtable->Release(this, (bool)((unsigned int)field04 >> 31));
        }
    }
};
struct RefPair {
    RefHandle* ptr;
    float value;
};
struct SmartPtrSlot { void Assign(RefHandle* p); };   // 0x478db0 (thiscall)
struct RbtreeOps {
    void* Find(void* resultOut, const void* key);   // 0xe39fb0 (thiscall)
};
struct MapHolder {
    char pad0[0xc1];
    unsigned char alive;      // +0xc1
    char pad1[0xc8 - 0xc2];
    void* tree;               // +0xc8

    bool Lookup(int key);
};
struct MapErase {
    void* header;   // +0x00
    int   pad;      // +0x04 (header+0 = sentinel; +4 is next)
    char  pad2[0x14 - 8];
    int   count;    // +0x14

    bool Erase(void* key);
};
struct MapInsert {
    void* header;  // +0x00
    char  pad2[0x14 - 4];
    int   count;   // +0x14

    void Insert(void** out, void* parent, const int* key, char flag);
};
typedef void* (__thiscall* Thiscall0)(void*);
typedef void* (__thiscall* Thiscall1)(void*, int);
typedef void* (__thiscall* Thiscall1p)(void*, void*);
struct GonzagoModelWorld {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18(void*, int);
};
class cGalaxyGameEntryImpl {
public:
    unsigned int SetGameToEnter(unsigned int msg, unsigned int arg);
};
struct EffectsManager2 {
virtual bool v00();
virtual bool v04();
virtual bool v08();
virtual bool v0c();
virtual bool v10();
virtual bool v14();
virtual bool v18();
virtual bool v1c();
virtual bool v20();
virtual bool v24();
virtual bool v28();
    virtual bool Fn2c(int a, int b, void** out);   // +0x2c
};
struct HashOps {
    char pad0[4];
    void* buckets;   // +0x04
    int   mask;      // +0x08

    void* Find(void* resultOut, const void* key);   // 0x5538f0 (thiscall)
};
struct HashHolder {
    char pad0[0x8c];
    char hashobj[0x10];   // +0x8c hash table object

    void Drive(unsigned int id);
};
// ---- items of slice s00b362c0 end

// ---- items of slice s00b38190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int* g_setBegin;                            // 0x0167ea68
extern unsigned int* g_setEnd;                              // 0x0167ea6c
extern unsigned char g_setFlag;                             // 0x0167ea7c
extern unsigned int* eastl_lower_bound(unsigned int* first, unsigned int* last,
                                       const unsigned int* key, unsigned char cmp);  // 0x00555a20
struct RefHandle_s00b3_8190;
struct RefOwner_s00b3_8190 {
    VS64(v0) VS16(v1) VS8(v2) VS4(v3)
    virtual void Release(RefHandle_s00b3_8190* obj, bool sign);        // +0x170
};
struct RefHandle_s00b3_8190 {
    RefOwner_s00b3_8190* mpOwner;      // +0x00
    int       mFlags;       // +0x04
    int       mPad08[14];   // +0x08 .. +0x3f
    int       mRefCount;    // +0x40

    void Decrement() {
        if (mRefCount > 1) {
            --mRefCount;
        } else {
            mpOwner->Release(this, (bool)(((unsigned int)mFlags) >> 31));
        }
    }
};
struct RefPair_s00b3_8190 {
    RefHandle_s00b3_8190* mpHandle;    // +0x00
    float      mValue;      // +0x04

    void Assign(const RefPair_s00b3_8190& r) {
        RefHandle_s00b3_8190* nv = r.mpHandle;
        RefHandle_s00b3_8190* ov = mpHandle;
        if (nv != ov) {
            if (nv) ++nv->mRefCount;
            mpHandle = nv;
            if (ov) ov->Decrement();
        }
        mValue = r.mValue;
    }
};
struct SortCmp {
    int mState;             // +0x00 (unused by the comparison itself)
    bool FUN_00b385d0(RefPair_s00b3_8190* a, RefPair_s00b3_8190* b) const;        // 0x00b385d0
};
extern void FUN_00b36610(RefPair_s00b3_8190* a, RefPair_s00b3_8190* b);           // 0x00b36610 (swap)
extern RefPair_s00b3_8190* FUN_00b38b40(RefPair_s00b3_8190* first, RefPair_s00b3_8190* last, RefPair_s00b3_8190 pivot, SortCmp cmp);
extern void FUN_00b38bf0(RefPair_s00b3_8190* base, int first, int hole, RefPair_s00b3_8190 value, SortCmp cmp);
struct Vec8Pair {
    RefHandle_s00b3_8190* mpHandle;    // +0x00
    int32_t    mValueBits;  // +0x04
};
struct Vec8Ins {
    Vec8Pair* mpBegin;      // +0x00
    Vec8Pair* mpEnd;        // +0x04
    Vec8Pair* mpCapacity;   // +0x08
    void Insert(void* pos, const void* value);              // 0x0074bf10
    void FUN_00b38260(const Vec8Pair* p);
};
struct AutoRefVec {
    void** mpBegin;         // +0x00
    void** mpEnd;           // +0x04
    void** mpCapacity;      // +0x08
    void**  erase(void** first, void** last);               // 0x00b48e40
    void    SetCapacity(unsigned int count);                // 0x00d01790
    void    GrowPush(void** pos, void** value);             // 0x00bab900
};
struct IQuerySource {
    virtual void  q00();                                    // +0x00
    virtual void  q04();                                    // +0x04
    virtual void  q08();                                    // +0x08
    virtual void* QueryInterface(unsigned int id);          // +0x0c
};
struct HitObject {
    unsigned int  mPad00[25];                               // +0x00 .. +0x63
    IQuerySource* mpHolder;                                 // +0x64
};
struct IRefCountedObj {
    VS32(a) VS8(b) VS4(c) VS2(d) VS1(e)                     // 47 slots: +0x00 .. +0xb8
    virtual void AddRef();                                  // +0xbc
    virtual void Release();                                 // +0xc0
};
struct FilterSpec {
    unsigned int  mField00;                                 // +0x00
    unsigned int  mField04;                                 // +0x04
    unsigned int  mField08;                                 // +0x08
    unsigned int  mField0c;                                 // +0x0c
    unsigned int  mField10;                                 // +0x10
    unsigned char mFlag;                                    // +0x14
    unsigned char mPad15;                                   // +0x15
};
struct IModelWorld {
    virtual void Lock();                                    // +0x00
    virtual void Unlock();                                  // +0x04
    VS8(w0) VS4(w1)                                         // +0x08 .. +0x34
    virtual bool Filter38(void* a1, float f, void* hits, FilterSpec* spec);   // +0x38
};
struct IModelWorld30 {
    virtual void Lock();                                    // +0x00
    virtual void Unlock();                                  // +0x04
    VS8(x0) VS2(x1)                                         // +0x08 .. +0x2c
    virtual bool Filter30(void* a1, void* a2, void* hits, FilterSpec* spec, float f);  // +0x30
};
struct PtrVec {                 // hit list held by the owner object (4-byte entries)
    HitObject** mpBegin;    // +0x00
    HitObject** mpEnd;      // +0x04
    HitObject** mpCapacity; // +0x08
};
struct WorldHit {               // one entry of the world filter's 8-byte hit buffer
    HitObject* mpObject;    // +0x00
    float      mDistance;   // +0x04
};
struct HitVec {
    WorldHit* mpBegin;      // +0x00
    WorldHit* mpEnd;        // +0x04
    WorldHit* mpCapacity;   // +0x08
};
struct FilterOwner {
    unsigned int mPad00[0x2c / 4];                          // +0x00 .. +0x2b
    PtrVec       mHitList;                                  // +0x2c
    unsigned int mPad38[(0xe4 - 0x38) / 4];                 // +0x38 .. +0xe3
    IModelWorld* mpWorld;                                   // +0xe4

    bool FUN_00b382a0(void* a1, float f, AutoRefVec* out, unsigned char flag,
                      bool (*fn)(void*, void*), void* ctx);
    bool FUN_00b38420(void* a1, void* a2, AutoRefVec* out, unsigned char flag);
};
// ---- items of slice s00b38190 end

// ---- items of slice s00b3aaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
struct Handle_s00b3_aaf0
{
	int*  ptr;      // +0
	float value;    // +4

	Handle_s00b3_aaf0() {}
	Handle_s00b3_aaf0(const Handle_s00b3_aaf0& o)
	{
		ptr = o.ptr;
		if (ptr != NULL)
			((int*)ptr)[0x10]++;
		value = o.value;
	}
};
struct VecStub
{
	void Insert(Handle_s00b3_aaf0* where, unsigned int count, const Handle_s00b3_aaf0* value);   // 0x00b38690
	void Destroy(Handle_s00b3_aaf0* first, Handle_s00b3_aaf0* last);                             // 0x00b36130
};
extern "C" Handle_s00b3_aaf0* __cdecl FUN_00b36530(Handle_s00b3_aaf0* first, Handle_s00b3_aaf0* last, Handle_s00b3_aaf0* dst);
extern "C" void __cdecl FUN_00b39970(Handle_s00b3_aaf0* first, int holeIndex, int length,
                                     int topIndex, Handle_s00b3_aaf0 value, int ctx);
struct HandleVec
{
	Handle_s00b3_aaf0* mpBegin;     // +0
	Handle_s00b3_aaf0* mpEnd;       // +4
	Handle_s00b3_aaf0* mpCapacity;  // +8

	void Resize(unsigned int newSize);
};
// ---- items of slice s00b3aaf0 end

// ---- items of slice s00b3ac20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8_s00b3_ac20;
typedef unsigned short u16_s00b3_ac20;
typedef unsigned int   u32_s00b3_ac20;
struct Bits64 {
    u32_s00b3_ac20 w[2];
    Bits64() { w[0] = 0; w[1] = 0; }
    void set(u32_s00b3_ac20 i)   { if (i < 0x40) w[i >> 5] |= 1u << (i & 0x1f); }
    void reset(u32_s00b3_ac20 i) { if (i < 0x40) w[i >> 5] &= ~(1u << (i & 0x1f)); }
};
struct World_s00b3_ac20 : RefObj {
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
virtual void p47();
virtual void p48();
virtual void p49();
virtual void p50();
virtual void p51();
virtual void p52();
virtual void p53();
virtual void p54();
virtual void p55();
virtual void p56();
virtual void p57();
virtual void p58();
virtual void p59();
virtual void p60();
virtual void p61();
virtual void p62();
virtual void p63();
virtual void p64();
virtual void p65();
virtual void p66();
virtual void p67();
virtual void p68();
virtual void p69();
virtual void p70();
    virtual void SetMasks(Bits64* a, Bits64* b, int slot);      // 0x11c (71)
    virtual void ClearMasks(Bits64* a, Bits64* b, int slot);    // 0x120 (72)
virtual void p73();
virtual void p74();
virtual void p75();
virtual void p76();
virtual void p77();
virtual void p78();
virtual void p79();
    virtual void SetRenderer(RefObj* r, int slot, int enable);  // 0x140 (80)
};
struct ResManager {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
    virtual World_s00b3_ac20* Get(u32_s00b3_ac20 id, int a, int b);              // 0x14
    virtual void m6();
    virtual World_s00b3_ac20* Find(u32_s00b3_ac20 id);                           // 0x1c
virtual void m8();
virtual void m9();
    virtual u32_s00b3_ac20 GetIndex(u32_s00b3_ac20 id, const char* name);        // 0x28
};
struct Effect : RefObj {
    virtual void SetQuality(int q);                        // 0xc
};
struct EffectsManager {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void e10();
virtual void e11();
virtual void e12();
virtual void e13();
virtual void e14();
virtual void e15();
virtual void e16();
virtual void e17();
virtual void e18();
    virtual Effect* Get(u32_s00b3_ac20 id, int flags);                // 0x4c
};
struct LightingMgr {
virtual void l0();
virtual void l1();
virtual void l2();
virtual void l3();
virtual void l4();
    virtual void l5();
    virtual RefObj* Get(u32_s00b3_ac20 id, int a, int b);             // 0x18
};
struct Lighting : RefObj {
virtual void l2();
virtual void l3();
virtual void l4();
virtual void l5();
virtual void l6();
virtual void l7();
virtual void l8();
virtual void l9();
virtual void l10();
    virtual void Apply(u32_s00b3_ac20 id);                            // 0x30 (12)
};
struct cCommandBase {
    int cb[3];
    cCommandBase();                                         // 0x0083c800
    virtual ~cCommandBase() {}
};
struct cViewManagerCommand : cCommandBase { virtual void Run() {} };
struct cSuperHighLODCheat  : cCommandBase { virtual void Run() {} };
struct CheatManager {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
    virtual void c5();
    virtual void AddCheat(const char* name, cCommandBase* cmd, int flags);  // 0x18
};
struct IListener { virtual void l0(); };
struct MessageServer {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    virtual void AddListener(IListener* l, u32_s00b3_ac20 msg);       // 0x20
};
struct ViewerSetup2 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void Run();                                     // 0x1c
};
struct RasterInfo { u32_s00b3_ac20 handle; u32_s00b3_ac20 pad[2]; u16_s00b3_ac20 w; u16_s00b3_ac20 h; };
struct cSPEditorPhysicsWorld_s00b3_ac20 {
    char pad[0x174];
    cSPEditorPhysicsWorld_s00b3_ac20();                                // 0x007c3f70
    void Init(int);                                         // 0x007c4dd0
    RasterInfo* GetRasterInfo();                            // 0x007c3cd0
};
struct InitArea {
    void Init(int);                                         // 0x00c77b60
};
struct V { u32_s00b3_ac20 a, b; };
struct ValueMap {
    char pad[0x34];
    V& operator[](const u32_s00b3_ac20& key);                          // 0x005526a0
};
namespace SP {
    CheatManager*   __cdecl GetCheatManager();    // 0x67de20
}
namespace SP {
    MessageServer*  __cdecl GetMessageServer();   // 0x67dcc0
}
namespace SP {
    LightingMgr*    __cdecl GetLightingManager(); // 0x67dd90
}
namespace SP {
    ResManager*     __cdecl GetModelManager();    // 0x67dd80
}
namespace SP {
    EffectsManager* __cdecl GetEffectsManager();  // 0x67ddd0
}
namespace SP {
    World_s00b3_ac20*          __cdecl GetGonzagoModelWorld_s00b3_ac20(); // 0xb3d520
}
namespace SP {
    int __cdecl CreateRaster(int, int, int, int, u32_s00b3_ac20);  // 0x761420
}
ViewerSetup2* __cdecl GetViewerSetup();           // 0x67dd50
extern RefObj* g_Lighting;                        // 0x167ea54
struct A0 { virtual void a0(); };
struct C0 : IListener { virtual void c0(); };
struct B {
    virtual void b0();
    char pad0[0x20];
    InitArea area;          // 0x24 ... (0x60 bytes)
    char pad1[0x5f];
    ValueMap m;             // 0x84
    u8_s00b3_ac20  f_b8, f_b9, f_ba;
    char pad2[0x21];
    RefObj* p_dc;
    RefObj* p_e0;
    char pad3[4];
    cSPEditorPhysicsWorld_s00b3_ac20* phys;   // 0xe8
    char pad4[4];
    int raster;                    // 0xf0

    void Setup();
};
struct Outer : A0, C0, B {
    void Prepare();                                         // 0x00b39b70
};
static inline void AssignRef(RefObj*& dst, RefObj* src) {
    RefObj* old = dst;
    if (src != old) {
        if (src) src->AddRef();
        dst = src;
        if (old) old->Release();
    }
}
// ---- items of slice s00b3ac20 end

// ---- items of slice s00b3cf00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_167ece0;      // 0x0167ece0
extern float g_167ec2c, g_167ec30, g_167ec34; // 0x0167ec2c
extern float g_167eb8c, g_167eb90, g_167eb94; // 0x0167eb8c
extern float g_15695fc;              // 0x015695fc
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
#define G48 G47 virtual void z48();
#define G49 G48 virtual void z49();
#define G50 G49 virtual void z50();
#define G51 G50 virtual void z51();
#define G52 G51 virtual void z52();
#define G53 G52 virtual void z53();
struct V20 { G7  virtual void      f20(void* a, unsigned id); };
struct V48 { G17 virtual bool      f48(); };
struct V68 { G25 virtual void*     f68(); };
struct V6C { G26 virtual void*     f6C(void* out); };
struct VB8 { G45 virtual void*     fB8(unsigned id); };
struct VD8 { G53 virtual float     fD8(); };
void* __cdecl SP_GetCurrentGameMode();       // 0x00b5b800
void* __cdecl SP_PropertyManager();           // 0x0067de30
void* __cdecl SP_MessageServer();             // 0x0067dcc0
void  __cdecl FUN_00b50ff0();                 // 0x00b50ff0
struct Obj40 {
    char pad0[0x44];
    float f44;                       // +0x44
    char pad48[0x70 - 0x48];
    unsigned char b70;               // +0x70
    unsigned char b71;               // +0x71
    char pad72[0x75 - 0x72];
    unsigned char b75;               // +0x75
    char pad76[0x1f0 - 0x76];
    int  n1f0;                       // +0x1f0

    float* GetVelocity();            // 0x00d20610
    float* GetBounding();            // 0x00c41d50
};
struct C101 {
    char  pad0[4];
    int   nMode;                     // +0x04
    char  pad8[0xc - 8];
    int   nC;                        // +0x0c
    float f10;                       // +0x10
    float f14;                       // +0x14
    float f18;                       // +0x18
    float f1c, f20, f24;             // +0x1c
    float f28, f2c, f30;             // +0x28
    unsigned char b34, b35, b36, b37;// +0x34
    char  pad38[0x40 - 0x38];
    Obj40* p40;                      // +0x40
    char  pad44[0x68 - 0x44];
    int   n68, n6c;                  // +0x68
    char  pad70[0xe0 - 0x70];
    float e0, e4, e8;                // +0xe0
    float ec, f0, f4;                // +0xec
    char  padf8[0x1f8 - 0xf8];
    float arr;                       // +0xf8 (base of per-index vec3 array)

    float M_cf00();
    void  M_cf40();
    bool  M_d5f0();
    float M_d630();
    void* M_d6a0();
    void  M_d730();
    void  M_d7a0();
    void* M_d8c0();
    void  M_d9c0(float* out);
    void  M_da90(float* out, int idx, C101* other);
    void  M_dbb0();
    float M_dcd0();
    bool  M_dd40();
    void  M_dda0(float* a, float* b);
    void  M_dec0(float* v);
};
struct Neigh { bool IsValid(void* e); };          // 0x00c02600
struct Neigh2 { bool IsValid(void* e); };         // 0x00c03520
struct FB57  { void f515e0(); void f5a2d0(); };   // thiscall on C101
struct PropObj { char pad[0x12]; short mType; };  // has GetFloat()
struct PropObjF : PropObj { float* GetFloat(); }; // 0x0041ea70
struct C0C { void* f(); };                        // 0x00c0c2f0 (ecx = object)
struct PropGroup { G8  virtual bool GetProp(unsigned id, PropObjF** out); }; // slot 0x24
struct PropMgr   { G11 virtual bool GetGroup(unsigned id, PropGroup** out); }; // slot 0x30
static void ReadFloatProp(PropGroup* pg, unsigned id, float* dst)
{
    PropObjF* p = 0;
    if (pg->GetProp(id, &p)) {
        if (p && p->mType == 0xd)
            *dst = *p->GetFloat();
    }
}
struct S16 { unsigned short lo, hi; };
// ---- items of slice s00b3cf00 end

// ---- items of slice s00b3ef30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*    DAT_0167eb70;
extern float    DAT_015696d8;
extern float    DAT_015696dc;
extern float    DAT_015696e0;
extern float    DAT_015696e4;
extern uint8_t  DAT_0167ec08;
extern float    DAT_0167ec2c;
extern float    DAT_0167ec30;
extern float    DAT_0167ec34;
extern float    DAT_0167ec38;
extern float    DAT_0167ec3c;
extern float    DAT_0167ec40;
extern float    DAT_0167ec44;
extern float    DAT_0167ec48;
extern float    DAT_0167ec4c;
extern float    DAT_0167eb8c;
extern float    DAT_0167eb90;
extern float    DAT_0167eb94;
extern float    DAT_01461150;   // FLT_MAX
extern float    DAT_01461154;   // 1.5258789e-05f
extern float    DAT_013f51ac;   // -FLT_MAX
extern float    DAT_01485720;   // 1.0f
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix33
{
    float m[9];
    void Assign(const Matrix33& src);       // 0x0041cb40
    void FromMatrix(const void* src);       // 0x0040ce80
};
struct cSPBoundingBox_s00b3_ef30
{
    Vector3 mMin;                           // +0x00
    Vector3 mMax;                           // +0x0c
    void Extend(const Vector3* v);          // 0x0041bd50
    void Transform(const void* m);          // 0x00409dd0
};
struct cSPTransform_s00b3_ef30
{
    uint16_t mFlags;                        // +0x00
    uint16_t mModCount;                     // +0x02
    Vector3  mPos;                          // +0x04
    float    mScale;                        // +0x10
    Matrix33 mRot;                          // +0x14
    cSPTransform_s00b3_ef30() {}                       // default ctor
    cSPTransform_s00b3_ef30(const cSPTransform_s00b3_ef30& src);  // 0x0040ce80 (out of line)
};
struct cSPTransformOps
{
    cSPTransformOps* Assign(const void* p); // 0x00537dc0
};
struct cSpatialObject
{
    cSPTransform_s00b3_ef30* FUN_00b73e70();           // 0x00b73e70
    void  LocalToWorldTransform(cSPTransform_s00b3_ef30* out);  // 0x00c897e0
};
struct cSpatialProxy;
struct cSpatialDB
{
    cSpatialProxy* Find(int id);            // 0x00b721d0
};
struct cSpatialProxy
{
    Quaternion* GetQuaternion(Quaternion* out);          // 0x00b3f300
    Matrix33*   GetMatrix(Matrix33* out);                // 0x00b3f3a0
    void        GetBoundingBox(cSPBoundingBox_s00b3_ef30* out);     // 0x00b3f420
    void        GetTransform(cSPTransform_s00b3_ef30* out);         // 0x00b3f6c0
    cSPBoundingBox_s00b3_ef30* GetScaledBoundingBox(cSPBoundingBox_s00b3_ef30* out); // 0x00b3f730
    void        Integrate();                             // 0x00b3f940
    void        IntegrateCollide(float* p2, float* p3);  // 0x00b3faa0
    int         FUN_00b3ef30(void* obj, int count, void* vec, int idx,
                             void* b, int* outCount);    // 0x00b3ef30
    char        FUN_00b3eb90(void* buf, int idx, void* b, int* outCount,
                             float* v, float f);         // 0x00b3eb90
    float       TimeScale();                             // 0x00b3dcd0
    void        GetPosition(float* out);                 // 0x00b3d9c0
    bool        IsValid();                               // 0x00b3d5f0
};
Matrix33&   Matrix3FromQuaternion(Matrix33& out, const Quaternion& q);        // 0x0059c190
Quaternion& QuaternionFromMatrix33(Quaternion& out, const Matrix33& m, float w); // 0x00472b80
void        FUN_00b3d8d0(float* out, void* a, void* b, float x, float y, float z);
bool        FUN_0059ab70(float* v);
void        eastl_vector_insert(void* vec, void* pos, int size);              // 0x011e0744
static void ScaleBox(cSPBoundingBox_s00b3_ef30* out, float s)
{
    float cx = (out->mMin.x + out->mMax.x) * 0.5f;
    float cy = (out->mMin.y + out->mMax.y) * 0.5f;
    float cz = (out->mMin.z + out->mMax.z) * 0.5f;
    out->mMin.x = (out->mMin.x - cx) * s + cx;
    out->mMin.y = (out->mMin.y - cy) * s + cy;
    out->mMin.z = (out->mMin.z - cz) * s + cz;
    out->mMax.x = (out->mMax.x - cx) * s + cx;
    out->mMax.y = (out->mMax.y - cy) * s + cy;
    out->mMax.z = (out->mMax.z - cz) * s + cz;
}
struct Elem3c
{
    float   f0, f1, f2, f3;                             // +0x00
    void*   p;                                          // +0x10
    float   f4, f5, f6, f7, f8, f9, f10, f11, f12;      // +0x14
    uint8_t b;                                          // +0x38
    uint8_t pad[3];
};
// ---- items of slice s00b3ef30 end

// ---- items of slice s00b3fe40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00b3_fe40 {
    float x, y, z;
    Vector3_s00b3_fe40() {}
    Vector3_s00b3_fe40(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    __forceinline Vector3_s00b3_fe40 operator+(const Vector3_s00b3_fe40& b) const { return Vector3_s00b3_fe40(x + b.x, y + b.y, z + b.z); }
    __forceinline Vector3_s00b3_fe40 operator-(const Vector3_s00b3_fe40& b) const { return Vector3_s00b3_fe40(x - b.x, y - b.y, z - b.z); }
    __forceinline Vector3_s00b3_fe40 operator*(float s) const { return Vector3_s00b3_fe40(x * s, y * s, z * s); }
    __forceinline Vector3_s00b3_fe40 operator-() const { return Vector3_s00b3_fe40(-x, -y, -z); }
    __forceinline Vector3_s00b3_fe40& operator*=(float s) { x = s * x; y = s * y; z = s * z; return *this; }
};
__forceinline Vector3_s00b3_fe40 operator*(float s, const Vector3_s00b3_fe40& v) { return Vector3_s00b3_fe40(s * v.x, s * v.y, s * v.z); }
__forceinline float Dot(const Vector3_s00b3_fe40& a, const Vector3_s00b3_fe40& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
struct Matrix3 { float m[3][3]; };
__forceinline Vector3_s00b3_fe40 operator*(const Matrix3& m, const Vector3_s00b3_fe40& v)
{
    return Vector3_s00b3_fe40(m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
                   m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
                   m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z);
}
__forceinline Vector3_s00b3_fe40 operator*(const Vector3_s00b3_fe40& v, const Matrix3& m)
{
    return Vector3_s00b3_fe40(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
                   v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
                   v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]);
}
struct BoundingBox {
    Vector3_s00b3_fe40 lower, upper;
    __forceinline bool Contains(const Vector3_s00b3_fe40& p) const
    {
        return p.x >= lower.x && p.x <= upper.x && p.y >= lower.y && p.y <= upper.y &&
               p.z >= lower.z && p.z <= upper.z;
    }
};
struct cSPTransform_s00b3_fe40 {
    enum { kTransformFlagScale = 1, kTransformFlagRotation = 2, kTransformFlagOffset = 4 };
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s00b3_fe40 mTranslation;   // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14
};
struct Plane {
    Vector3_s00b3_fe40 n;
    float d;
    Plane() {}
    __forceinline Plane(const Vector3_s00b3_fe40& normal, const Vector3_s00b3_fe40& point) : n(normal), d(-Dot(normal, point)) {}
    __forceinline float Distance(const Vector3_s00b3_fe40& p) const { return Dot(n, p) + d; }
};
struct ContactManifold {
    Vector3_s00b3_fe40 mPoints[16];        // +0x000
    Vector3_s00b3_fe40 mPointsB[16];       // +0x0c0
    int mCount;                 // +0x180
    Vector3_s00b3_fe40 mNormal;            // +0x184
    float mf190;                // +0x190
    Vector3_s00b3_fe40 mPenetration;       // +0x194
};
extern const Vector3_s00b3_fe40 kBoxAxes[3];   // @ 0x167ec2c: X, Y, Z axes (runtime-initialized)
template <class T> __forceinline T Clamp(T v, T lo, T hi) { return (v < lo) ? lo : ((v > hi) ? hi : v); }
__forceinline unsigned int EaxBits(float v) { union { float f; unsigned int u; } t; t.f = v; return t.u; }
// ---- items of slice s00b3fe40 end

// @ 0x00b35b80
Vec3 __stdcall GetNounOffset(u32 id)
{
    NounInfo* n = GetNounManager(id)->Get();
    if (n)
        return n->v;
    return g_defVec;
}

// @ 0x00b35bf0
bool __stdcall PickSegment(Thing* obj, Vec3* a, Vec3* b, Vec3* out)
{
    if (obj) {
        Thing2* c = obj->GetComp(0xce9f6639);
        if (c)
            return c->Fn(a, b, out);
    }
    World* w = GetGonzagoModelWorld();
    if (w)
        w->AddRef();
    Handle* h = obj->GetHandle();
    if (w) {
        if (h) {
            Filter f;
            float t;
            f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0; f.e = 0; f.z = 0;
            f.type = 4;
            if (w->Cast2(a, b, h, &t, &f)) {
                Vec3 A(*a);
                Vec3 B(*b);
                out->x = A.x + (B.x - A.x) * t;
                out->y = A.y + (B.y - A.y) * t;
                out->z = A.z + (B.z - A.z) * t;
                w->Release();
                return true;
            }
        }
        w->Release();
    }
    return false;
}

// @ 0x00b35d30
bool Owner::FindNearest(Vec3* pos, float r, u32 p4, RefObj** out)
{
    Filter f;
    f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0;
    f.e = p4;
    f.type = 3;
    f.z = 0;
    RefObj* old = *out;
    if (old) {
        *out = 0;
        old->Release();
    }
    World* w = GetGonzagoModelWorld();
    if (w)
        w->AddRef();
    if ((w && w->Cast(pos, r, &vbeg, &f)) || w1->Cast(pos, r, &vbeg, &f)) {
        Obj** end = vend;
        float best = 3.4028234e+38f;
        for (Obj** p = vbeg; p != end; ++p) {
            Obj* o = *p;
            if (o->comp) {
                float dx = o->x - pos->x;
                float dy = o->y - pos->y;
                float dz = o->z - pos->z;
                float d = sqrtf(dz * dz + dy * dy + dx * dx);
                if (d <= best) {
                    best = d;
                    RefObj* q = QueryComp(o->comp, 0x17f243b);
                    RefObj* prev = *out;
                    if (q != prev) {
                        if (q) q->AddRef();
                        *out = q;
                        if (prev) prev->Release();
                    }
                }
            }
        }
    }
    bool ok = *out != 0;
    if (w)
        w->Release();
    return ok;
}

// @ 0x00b35ec0
bool Owner::Pick(int a, int b, u32 d, RefPtr* r, Vec3* out, u8 e)
{
    Vec3 loc;
    Filter f;
    f.w0 = 0; f.w1 = 0; f.w2 = 0; f.w3 = 0;
    f.type = e;
    f.z = 0;
    f.e = d;
    Obj* o = GetGonzagoModelWorld()->Pick(a, b, 0, &loc, 0, &f, 0, 0);
    if (!o) {
        o = w1->Pick(a, b, 0, &loc, 0, &f, 0, 0);
        if (!o)
            return false;
    }
    if (o->comp) {
        RefObj* q = QueryComp(o->comp, 0x17f243b);
        if (q) {
            *r = q;
            *out = loc;
            return true;
        }
    }
    return false;
}

// @ 0x00b35fa0
float GetEditorFloat()
{
    float f = 0.0f;
    Prop* p;
    if (g_Props && g_Props->Get(0x26b7d69, &p) && p->type == 0xd)
        f = *p->GetFloat();
    PropList* t = GetSceneB()->Fn2();
    if (t && t->Get(0x26b7d69, &p) && p->type == 0xd)
        f = *p->GetFloat();
    return f;
}

// @ 0x00b36030
bool CanSelect(Obj* o)
{
    if (o->f8c > 0.0f)
        return false;
    CompA* a = (CompA*)QueryComp(o->comp, 0x1186577);
    Comp* b = (Comp*)QueryComp(o->comp, 0x17f243b);
    if (!a || !b)
        return false;
    return !b->Fn2c() && GetRes(a->GetKey()->b)->Fn();
}

// @ 0x00b360d0
Elem* FindByKey(Elem* first, Elem* last, Key key)
{
    while (first != last) {
        CompA* a = (CompA*)QueryCompP(&first->p->comp, 0x1186577);
        if (*a->GetKey() == key)
            break;
        ++first;
    }
    return first;
}

// @ 0x00b36130
void __stdcall ReleaseRange(Elem* first, Elem* last)
{
    for (; first < last; ++first) {
        Obj* o = first->p;
        if (o) {
            int rc = o->rc;
            if (rc > 1)
                o->rc = rc - 1;
            else
                o->mgr->Destroy(o, IsFlagBit(o->f4));
        }
    }
}

// @ 0x00b36180
void HeapPercolate(Obj** arr, int first, int len, int hole, u32 v1, u32 v2)
{
    int child = hole * 2 + 2;
    while (child < len) {
        Obj* right = arr[child];
        Obj* left = arr[child - 1];
        float r = SortKey(right);
        if (SortKey(left) > r)
            --child;
        arr[hole] = arr[child];
        hole = child;
        child = child * 2 + 2;
    }
    if (child == len) {
        arr[hole] = arr[child - 1];
        hole = child - 1;
    }
    SiftDown_b33ea0(arr, first, hole, v1, v2);
}

// @ 0x00b36200
Iter CopyRange(Elem* first, Elem* last, Elem* dest)
{
    Iter r(dest);
    Elem* d = dest;
    for (; first != last; ++first, ++d)
        new (d) Elem(*first);
    r.p = d;
    return r;
}

// @ 0x00b36250
void FillN(Elem* dest, unsigned n, const Elem* src)
{
    Elem* d = dest;
    for (; n > 0; --n, ++d)
        new (d) Elem(*src);
}

// @ 0x00b36280
void CopyTo(Elem* first, Elem* last, Elem* dest)
{
    Elem* d = dest;
    for (; first != last; ++first, ++d)
        new (d) Elem(*first);
}

// @ 0x00b362c0
RefPair* RefPair_DestroyRange(RefPair* first, RefPair* last, RefPair* out)
{
    while (first != last) {
        RefHandle* p = first->ptr;
        if (p) p->Decrement();
        first += 1;
        out += 1;
    }
    return out;
}

// @ 0x00b36320
bool MapHolder::Lookup(int key)
{
    if (!alive) return false;
    void* dummy;
    void* node = ((RbtreeOps*)((char*)this + 0xc8))->Find(&dummy, &key);
    return *(void**)node == (char*)this + 0xcc;
}

// @ 0x00b36360
bool MapErase::Erase(void* key)
{
    void* node;
    ((RbtreeOps*)&header)->Find(&node, key);
    if (node == &header) return false;
    --count;
    RbtreeIncrement(node);
    RBTreeErase(node, &header);
    operator_delete(node);
    return true;
}

// @ 0x00b36440
void MapInsert::Insert(void** out, void* parent, const int* key, char flag)
{
    unsigned int side;
    if (flag == 0 && parent != &header && *key <= *(int*)((char*)parent + 0x10))
        side = 1;
    else
        side = 0;

    char* node = (char*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
    if (node + 0x10)
        *(int*)(node + 0x10) = *key;
    RBTreeInsert(node, parent, &header, side);
    ++count;
    *out = node;
}

// @ 0x00b364c0
void RefPair_CopyAssign(RefPair* dst, RefPair* last, const RefPair* src)
{
    for (; dst != last; dst += 1) {
        RefHandle* nv = src->ptr;
        RefHandle* ov = dst->ptr;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            dst->ptr = nv;
            if (ov) ov->Decrement();
        }
        dst->value = src->value;
    }
}

// @ 0x00b36530
RefPair* RefPair_CopyConstruct(RefPair* first, RefPair* last, RefPair* out)
{
    while (first != last) {
        RefHandle* nv = first->ptr;
        RefHandle* ov = out->ptr;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            out->ptr = nv;
            if (ov) ov->Decrement();
        }
        out->value = first->value;
        first += 1;
        out += 1;
    }
    return out;
}

// @ 0x00b365a0
RefPair* RefPair_CopyConstructBackward(RefPair* first, RefPair* last, RefPair* out)
{
    while (last != first) {
        RefHandle* nv = (last - 1)->ptr;
        RefHandle* ov = (out - 1)->ptr;
        --last;
        --out;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            out->ptr = nv;
            if (ov) ov->Decrement();
        }
        out->value = last->value;
    }
    return out;
}

// @ 0x00b36610
void RefPair_Swap(RefPair* a, RefPair* b)
{
    RefHandle* pa = a->ptr;
    if (pa) ++pa->refCount;
    float tmp = a->value;
    ((SmartPtrSlot*)&a->ptr)->Assign(b->ptr);
    a->value = b->value;
    ((SmartPtrSlot*)&b->ptr)->Assign(pa);
    b->value = tmp;
    if (pa) pa->Decrement();
}

// @ 0x00b36690
unsigned int cGalaxyGameEntryImpl::SetGameToEnter(unsigned int msg, unsigned int arg)
{
    unsigned int result;
    if (msg < 0x4b719d5u) {
        if (msg == 0x4b719d4u) {
            void* p = *(void**)(arg + 8);
            GonzagoModelWorld* w = (GonzagoModelWorld*)SP_GonzagoModelWorld();
            result = 0;
            if (w) {
                w->v00();
                void* a = Gonzago_Fn1(p, 0);
                void* b = TerrainMgr_Fn1(a, 0);
                w->v18(b, 0);
                w->v04();
                return 0;
            }
        } else if (msg == 0x1a0219eu) {
            void* p = *(void**)(arg + 0x10);
            if (p) {
                if (*(int*)(arg + 8) == 3)
                    ((Thiscall1p)((void**)*(void**)((char*)this - 4))[0x54/4])((char*)this - 4, p);
                if (*(int*)(arg + 8) == 4) {
                    ((Thiscall1p)((void**)*(void**)((char*)this - 4))[0x58/4])((char*)this - 4, p);
                    return 0;
                }
            }
        } else if (msg == 0x30c11c7u && arg != 0) {
            int v = (int)GalaxyImpl_Fn7360((void*)(arg + 0x10));
            result = 0;
            if (v) {
                unsigned char buf[0x40];
                SlotMessage_Construct(buf, 0);
                *(unsigned int*)(buf + 0x20) = 0x3047cb34;
                SlotMessage_Destruct(buf);
                return 0;
            }
        }
    } else if (msg == 0x3047cb34u) {
        result = arg;
        if (*(void**)(arg + 8)) {
            unsigned int a = *(unsigned int*)(arg + 0x10);
            unsigned int b = *(unsigned int*)(arg + 0x18);
            unsigned int c = *(unsigned int*)(arg + 0x20);
            (void)a; (void)b; (void)c;
        }
    }
    return result & 0xffffff00u;
}

// @ 0x00b36820
float Planet_PlaceDistance(void* entry, void* model, float* pos, void* out, int a4, char flag)
{
    void* pm = SP_PlanetModel();
    if (!pm || !g_167ecd0) return 0.0f;

    if (flag != 0) {
        void* p = *(void**)((char*)pm + 0x24);
        if (!p) return 0.0f;
        void* r = ((Thiscall0)((void**)*(void**)p)[0xc/4])(p);
        return *(float*)((char*)r + 0x3c) * *(float*)((char*)r + 0x38) + *(float*)((char*)r + 0x34);
    }

    float lo = g_f1418ef4;   // -5.0f
    float hi = g_f1486110;   // 5.0f
    int found = 0;
    char ch = 0;
    if (entry && *(void**)((char*)entry + 0x180)) {
        void* p = *(void**)((char*)entry + 0x180);
        p = (char*)p + 100;
        void* h = PlanetModel_Fn2(p, 0);
        found = h ? (int)PlanetModel_Fn0(h, 0) : 0;
        if (found) {
            void* v = PlanetModel_Fn1((void*)found);
            if (v) {
                void* v2 = PlanetModel_Fn1((void*)found);
                void* obj = *(void**)((char*)v2 + 0x58);
                hi = *(float*)((char*)obj + 0x98);
                ch = *(char*)((char*)h + 0x77);
                lo = -hi;
            }
        }
    }
    (void)lo; (void)hi; (void)ch;
    return 0.0f;
}

// @ 0x00b36bb0
void HashHolder::Drive(unsigned int id)
{
    void* node;
    void* dummy;
    (void)dummy;
    HashOps* h = (HashOps*)((char*)this + 0x8c);
    h->Find(&node, &id);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (ok) ((Thiscall1)((void**)*(void**)node)[8/4])(node, 0);
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}

// @ 0x00b36c40
void HashHolder_PushOrientation(HashHolder* self, void* p1, void* p2, void* out)
{
    void* node;
    HashOps* h = (HashOps*)((char*)self + 0x8c);
    h->Find(&node, &p1);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (!ok) {
        if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
        return;
    }

    float* a = (float*)p1;
    float* b = (float*)p2;
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    float len = dz * dz + dy * dy + dx * dx;
    (void)len;

    void* pm = SP_PlanetModel();
    (void)pm;
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}

// @ 0x00b36f30
void HashHolder_PushOrientation2(HashHolder* self, void* p)
{
    void* node;
    HashOps* h = (HashOps*)((char*)self + 0x8c);
    h->Find(&node, &p);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (!ok) {
        if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
        return;
    }

    void* pm = SP_PlanetModel();
    (void)pm;
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}

// @ 0x00b370f0
void RefPair_Sort(void* base, void* mid, void* end, void* key)
{
    SortFunc1(base, mid, key);
    for (char* p = (char*)mid; p < (char*)end; p += 4) {
        float a = SortKey(*(void**)p);
        float b = SortKey(*(void**)base);
        if (a < b) {
            void* v = *(void**)p;
            *(void**)p = *(void**)base;
            SortInsert(base, 0, (int)((char*)mid - (char*)base) >> 2, 0, v, key);
        }
    }
    SortFunc2(base, mid, key);
}

// @ 0x00b38260
void Vec8Ins::FUN_00b38260(const Vec8Pair* p)
{
    Vec8Pair* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e != 0) {
            e->mpHandle = p->mpHandle;
            e->mValueBits = p->mValueBits;
            return;
        }
    } else {
        Insert(mpEnd, p);
    }
}

// @ 0x00b382a0
bool FilterOwner::FUN_00b382a0(void* a1, float f, AutoRefVec* out, unsigned char flag, bool (*fn)(void*, void*), void* ctx)
{
    out->erase(out->mpBegin, out->mpEnd);
    out->SetCapacity(0x80);

    FilterSpec spec;
    spec.mField00 = 0;
    spec.mField04 = 0;
    spec.mField08 = 0;
    spec.mField0c = 0;
    spec.mField10 = 0;
    spec.mFlag = flag;
    spec.mPad15 = 0;

    IModelWorld* world = (IModelWorld*)SP_GonzagoModelWorld();
    bool ok = false;
    if (world != 0) {
        world->Lock();
        ok = world->Filter38(a1, f, &mHitList, &spec);
    }
    if (!ok) {
        ok = ((IModelWorld*)mpWorld)->Filter38(a1, f, &mHitList, &spec);
    }
    if (ok) {
        HitObject** it = mHitList.mpBegin;
        HitObject** end = mHitList.mpEnd;
        while (it != end) {
            HitObject* p = *it;
            IRefCountedObj* q = 0;
            if (p->mpHolder != 0) {
                q = (IRefCountedObj*)((IQuerySource*)p->mpHolder)->QueryInterface(0x01186577);
            }
            if (q != 0 && (fn == 0 || fn(p, ctx))) {
                q->AddRef();
                IRefCountedObj* tmp = q;
                if ((void**)out->mpEnd < out->mpCapacity) {
                    IRefCountedObj** slot = (IRefCountedObj**)out->mpEnd;
                    out->mpEnd = (void**)(slot + 1);
                    if (slot != 0) {
                        *slot = q;
                        q->AddRef();
                    }
                } else {
                    out->GrowPush(out->mpEnd, (void**)&tmp);
                    q = tmp;
                }
                if (q != 0) q->Release();
            }
            ++it;
        }
    }
    bool result = (out->mpBegin != out->mpEnd);
    if (world != 0) world->Unlock();
    return result;
}

// @ 0x00b38420
bool FilterOwner::FUN_00b38420(void* a1, void* a2, AutoRefVec* out, unsigned char flag)
{
    out->erase(out->mpBegin, out->mpEnd);
    out->SetCapacity(0x80);

    WorldHit buffer[16];
    HitVec hits;
    hits.mpBegin = buffer;
    hits.mpEnd = buffer;
    hits.mpCapacity = buffer + 16;

    FilterSpec spec;
    spec.mField00 = 0;
    spec.mField04 = 0;
    spec.mField08 = 0;
    spec.mField0c = 0;
    spec.mField10 = 0;
    spec.mFlag = flag;
    spec.mPad15 = 0;

    IModelWorld30* world = (IModelWorld30*)SP_GonzagoModelWorld();
    bool ok = false;
    if (world != 0) {
        world->Lock();
        ok = world->Filter30(a1, a2, &hits, &spec, 0.0f);
    }
    if (!ok) {
        ok = ((IModelWorld30*)mpWorld)->Filter30(a1, a2, &hits, &spec, 0.0f);
    }
    if (ok) {
        WorldHit* it = hits.mpBegin;
        WorldHit* end = hits.mpEnd;
        if (it != end) {
            do {
                HitObject* p = it->mpObject;
                IRefCountedObj* q = 0;
                if (p->mpHolder != 0) {
                    q = (IRefCountedObj*)((IQuerySource*)p->mpHolder)->QueryInterface(0x01186577);
                }
                if (q != 0) {
                    q->AddRef();
                    IRefCountedObj* tmp = q;
                    if ((void**)out->mpEnd < out->mpCapacity) {
                        IRefCountedObj** slot = (IRefCountedObj**)out->mpEnd;
                        out->mpEnd = (void**)(slot + 1);
                        if (slot != 0) {
                            *slot = q;
                            q->AddRef();
                        }
                    } else {
                        out->GrowPush(out->mpEnd, (void**)&tmp);
                        q = tmp;
                    }
                    if (q != 0) q->Release();
                }
                ++it;
            } while (it != end);
        }
    }
    bool result = (out->mpBegin != out->mpEnd);
    if (world != 0) world->Unlock();
    if (hits.mpBegin != 0 && hits.mpBegin != buffer) operator_delete(hits.mpBegin);
    return result;
}

// @ 0x00b385d0
bool SortCmp::FUN_00b385d0(RefPair_s00b3_8190* a, RefPair_s00b3_8190* b) const
{
    unsigned int keyA = (unsigned int)a->mpHandle;
    unsigned int* itA = eastl_lower_bound(g_setBegin, g_setEnd, &keyA, g_setFlag);
    if (itA == g_setEnd || keyA < *itA) itA = g_setEnd;
    bool inA = (itA != g_setEnd);

    unsigned int keyB = (unsigned int)b->mpHandle;
    unsigned int* itB = eastl_lower_bound(g_setBegin, g_setEnd, &keyB, g_setFlag);
    if (itB == g_setEnd || keyB < *itB) itB = g_setEnd;
    bool inB = (itB != g_setEnd);

    if (inA != inB) return inA;
    return a->mValue > b->mValue;
}

// @ 0x00b388a0
void FUN_00b388a0(RefPair_s00b3_8190* first, RefPair_s00b3_8190* last, SortCmp cmp)
{
    if (first == last) return;
    for (RefPair_s00b3_8190* i = first + 1; i != last; ++i) {
        RefPair_s00b3_8190 temp;
        temp.mpHandle = i->mpHandle;
        if (temp.mpHandle) ++temp.mpHandle->mRefCount;
        temp.mValue = i->mValue;

        RefPair_s00b3_8190* j = i;
        while (j != first) {
            if (!cmp.FUN_00b385d0(&temp, j - 1)) break;
            j->Assign(*(j - 1));
            j -= 1;
        }
        j->Assign(temp);
        if (temp.mpHandle) temp.mpHandle->Decrement();
    }
}

// @ 0x00b389f0
void FUN_00b389f0(RefPair_s00b3_8190* first, RefPair_s00b3_8190* last, SortCmp cmp)
{
    for (RefPair_s00b3_8190* cur = first; cur != last; ++cur) {
        RefHandle_s00b3_8190* keyH = cur->mpHandle;
        if (keyH != 0) ++keyH->mRefCount;
        RefPair_s00b3_8190 key;
        key.mpHandle = keyH;
        key.mValue = cur->mValue;

        RefPair_s00b3_8190* h = cur;
        if (cmp.FUN_00b385d0(&key, cur - 1)) {
            bool c;
            do {
                RefPair_s00b3_8190* prev = h - 1;
                RefHandle_s00b3_8190* a = prev->mpHandle;
                RefHandle_s00b3_8190* b = h->mpHandle;
                if (a != b) {
                    if (a != 0) ++a->mRefCount;
                    h->mpHandle = a;
                    if (b != 0) b->Decrement();
                }
                h = prev;
                (h + 1)->mValue = h->mValue;
                c = cmp.FUN_00b385d0(&key, h - 1);
            } while (c);
        }
        RefHandle_s00b3_8190* hp = h->mpHandle;
        if (keyH != hp) {
            if (keyH != 0) ++keyH->mRefCount;
            h->mpHandle = keyH;
            if (hp != 0) hp->Decrement();
        }
        h->mValue = key.mValue;
        if (keyH != 0) keyH->Decrement();
    }
}

// @ 0x00b38b40
RefPair_s00b3_8190* FUN_00b38b40(RefPair_s00b3_8190* first, RefPair_s00b3_8190* last, RefPair_s00b3_8190 pivot, SortCmp cmp)
{
    for (;;) {
        while (cmp.FUN_00b385d0(first, &pivot)) ++first;
        do {
            --last;
        } while (cmp.FUN_00b385d0(&pivot, last));
        if (last <= first) break;
        FUN_00b36610(first, last);
        ++first;
    }
    if (pivot.mpHandle) pivot.mpHandle->Decrement();
    return first;
}

// @ 0x00b38bf0
void FUN_00b38bf0(RefPair_s00b3_8190* base, int first, int hole, RefPair_s00b3_8190 value, SortCmp cmp)
{
    while (first < hole) {
        int parent = (hole - 1) >> 1;
        if (!cmp.FUN_00b385d0(base + parent, &value)) break;
        base[hole].Assign(base[parent]);
        hole = parent;
    }
    base[hole].Assign(value);
    if (value.mpHandle) value.mpHandle->Decrement();
}

// @ 0x00b3aaf0
void HandleVec::Resize(unsigned int newSize)
{
	Handle_s00b3_aaf0* end = mpEnd;
	unsigned int size = (unsigned int)(end - mpBegin);
	if (newSize > size)
	{
		Handle_s00b3_aaf0 local;
		local.ptr = NULL;
		local.value = 0.0f;
		((VecStub*)this)->Insert(end, newSize - size, &local);
		return;
	}
	Handle_s00b3_aaf0* p = mpBegin + newSize;
	Handle_s00b3_aaf0* e = FUN_00b36530(end, end, p);
	((VecStub*)this)->Destroy(e, mpEnd);
	mpEnd += -(end - p);
}

// @ 0x00b3ab70
void FUN_00b3ab70(Handle_s00b3_aaf0* first, Handle_s00b3_aaf0* last, volatile int ctx)
{
	int length = (int)(last - first);
	if (length < 2)
		return;
	int parent = ((length - 2) >> 1) + 1;
	do
	{
		--parent;
		FUN_00b39970(first, parent, length, parent, first[parent], (int)ctx);
	} while (parent != 0);
}

// @ 0x00b3ac20
void B::Setup()
{
    if (f_b8)
        return;
    f_ba = 1;
    f_b9 = 1;
    area.Init(0x80);
    new ("App/cViewManagerCommand", 0, 0, 0, 0) cViewManagerCommand();
    SP::GetCheatManager();
    cSuperHighLODCheat* cheat = new ("App/cSuperHighLODCheat", 0, 0, 0, 0) cSuperHighLODCheat();
    SP::GetCheatManager()->AddCheat("highresTextureLevel", cheat, 0);
    MessageServer* ms = SP::GetMessageServer();
    Outer* o = (Outer*)((char*)this - 8);
    ms->AddListener((C0*)o, 0x30c11c7);
    ms->AddListener((C0*)o, 0x3047cb34);
    ms->AddListener((C0*)o, 0x1a0219e);
    ms->AddListener((C0*)o, 0x4b719d4);
    ms->AddListener((C0*)o, 0x712924f2);
    ms->AddListener((C0*)o, 0x712924f3);
    f_b8 = 1;
    AssignRef(g_Lighting, SP::GetLightingManager()->Get(0x4a4dea0, 0, 0));
    ((Lighting*)g_Lighting)->Apply(0x5f848353);

    phys = new ("Simulator", 0, 0, 0, 0) cSPEditorPhysicsWorld_s00b3_ac20();
    phys->Init(0);
    GetViewerSetup()->Run();
    RasterInfo* ri = phys->GetRasterInfo();
    raster = SP::CreateRaster((u16_s00b3_ac20)ri->h, (u16_s00b3_ac20)ri->w, 1, 2, ri->handle);

    ResManager* mm = SP::GetModelManager();
    World_s00b3_ac20* w = SP::GetGonzagoModelWorld_s00b3_ac20();
    if (w) {
        w->AddRef();
    } else {
        w = mm->Get(0xeb9968, 0, 0);
        if (w) w->AddRef();
        u32_s00b3_ac20 mask   = mm->GetIndex(0x31e5f0f, "Mask");
        u32_s00b3_ac20 post   = mm->GetIndex(0x420b420, "PostEffects");
        u32_s00b3_ac20 back   = mm->GetIndex(0x64ac354, "BackgroundEffects");
        u32_s00b3_ac20 noshad = mm->GetIndex(0x6669387, "NoShadowCast");
        u32_s00b3_ac20 over   = mm->GetIndex(0x7aa969b, "overdraw");
        Bits64 a, b;
        a.set(mask); a.set(post); a.set(back);
        w->SetMasks(&b, &a, 0);
        a = Bits64(); b = Bits64();
        b.set(mask);
        w->SetMasks(&b, &a, 1);
        a = Bits64(); b = Bits64();
        b.set(post);
        w->SetMasks(&b, &a, 2);
        a = Bits64(); b = Bits64();
        b.set(over);
        w->SetMasks(&b, &a, 7);
        w->ClearMasks(&b, &a, 0);
        a.reset(post);
        a.set(noshad);
        w->SetMasks(&b, &a, 3);
        a = Bits64(); b = Bits64();
        b.set(back);
        w->SetMasks(&b, &a, 4);
    }
    RefObj* r;
    r = mm->Find(0x317ccba) ? mm->Find(0x317ccba) : mm->Get(0x317ccba, 0, 0);
    AssignRef(p_dc, r);
    r = mm->Find(0x5de6030) ? mm->Find(0x5de6030) : mm->Get(0x5de6030, 0, 0);
    AssignRef(p_e0, r);

    Effect* e1 = SP::GetEffectsManager()->Get(0xeb9968, 0);
    if (e1) e1->AddRef();
    e1->SetQuality(2);
    Effect* e2 = SP::GetEffectsManager()->Get(0x23541242, 0);
    if (e2) e2->AddRef();
    e2->SetQuality(2);
    SP::GetEffectsManager()->Get(0x3701a5c, 0);
    w->SetRenderer(g_Lighting, 0, 1);
    w->SetRenderer(g_Lighting, 1, 1);
    w->SetRenderer(g_Lighting, 4, 1);
    RefObj* mv = SP::GetModelManager()->Find(0x3fbae24);
    if (mv) {
        mv->AddRef();
        ((World_s00b3_ac20*)mv)->SetRenderer(g_Lighting, 0, 1);
        ((World_s00b3_ac20*)mv)->SetRenderer(g_Lighting, 1, 1);
    }
    ((Outer*)((char*)this - 8))->Prepare();
    { V& v = m[0x0147e293u]; v.a = 0x3596af86u; v.b = 0; }
    { V& v = m[0x014fc194u]; v.a = 0x98ff936au; v.b = 0; }
    { V& v = m[0x01511148u]; v.a = 0xc07ea120u; v.b = 0; }
    { V& v = m[0x015b6c56u]; v.a = 0x5faed94cu; v.b = 0; }
    { V& v = m[0x1b559d6u]; v.a = 0xeab8865cu; v.b = 0; }
    { V& v = m[0x1b559d7u]; v.a = 0x927be8cau; v.b = 0; }
    { V& v = m[0x4c9bc66u]; v.a = 0x6a934f8eu; v.b = 0; }
    { V& v = m[0x1b55d9au]; v.a = 0xef8f883fu; v.b = 0; }
    { V& v = m[0x1b55d9bu]; v.a = 0x882f73b0u; v.b = 0; }
    { V& v = m[0x33ce1f4u]; v.a = 0xa58cc82du; v.b = 0; }
    { V& v = m[0x33ce359u]; v.a = 0xf0556401u; v.b = 0; }
    { V& v = m[0x4fd21bbcu]; v.a = 0x4fd21bbcu; v.b = 0; }
    { V& v = m[0xd3520187u]; v.a = 0xd3520187u; v.b = 0; }
    { V& v = m[0x534a52c0u]; v.a = 0x534a52c0u; v.b = 0; }
    { V& v = m[0xe4141994u]; v.a = 0xe4141994u; v.b = 0; }
    { V& v = m[0xed8c1210u]; v.a = 0xed8c1210u; v.b = 0; }
    { V& v = m[0xf7129557u]; v.a = 0xf7129557u; v.b = 0; }
    { V& v = m[0x1c0ffcfu]; v.a = 0xc07ea120u; v.b = 0; }
    { V& v = m[0x1d1109fu]; v.a = 0x384e54a4u; v.b = 0; }
    { V& v = m[0x1d110a0u]; v.a = 0x384e54a4u; v.b = 0; }
    { V& v = m[0x70f4ed3fu]; v.a = 0x4c216c78u; v.b = 0; }
    { V& v = m[0x70f4ed48u]; v.a = 0xdd480fccu; v.b = 0; }
    { V& v = m[0x22941e7u]; v.a = 0x696fc076u; v.b = 0; }
    { V& v = m[0x110f08c3u]; v.a = 0x3a616feeu; v.b = 0; }
    { V& v = m[0x2818ee0u]; v.a = 0x2090a5c4u; v.b = 0; }
    { V& v = m[0x2c4a8c2u]; v.a = 0x13505630u; v.b = 0; }
    { V& v = m[0x2c4a8cfu]; v.a = 0x2af2f191u; v.b = 0; }
    { V& v = m[0x2df3696u]; v.a = 0x6f1a1f1cu; v.b = 0; }
    { V& v = m[0x2e5d3a1u]; v.a = 0xb6f9b664u; v.b = 0; }
    { V& v = m[0x2df3697u]; v.a = 0xb6f9b679u; v.b = 0; }
    { V& v = m[0x2e5d3a6u]; v.a = 0x841a4016u; v.b = 0; }
    { V& v = m[0x30e8e52u]; v.a = 0x557b9e43u; v.b = 0; }
    { V& v = m[0x3f970d5u]; v.a = 0x6857b824u; v.b = 0; }
    { V& v = m[0x3704925u]; v.a = 0xf42bc0cau; v.b = 0; }
    { V& v = m[0x498da10u]; v.a = 0xf3043512u; v.b = 0; }
    { V& v = m[0x498ef27u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef28u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef29u]; v.a = 0x13714350u; v.b = 0; }
    { V& v = m[0x498ef2au]; v.a = 0xaa8e5065u; v.b = 0; }
    { V& v = m[0x498ef2bu]; v.a = 0x35d90ae0u; v.b = 0; }
    { V& v = m[0x3967564u]; v.a = 0x94f98b88u; v.b = 0; }
    { V& v = m[0x4288912u]; v.a = 0xd409170au; v.b = 0; }
    { V& v = m[0x4288913u]; v.a = 0x2e779a5bu; v.b = 0; }
    { V& v = m[0x4288915u]; v.a = 0x8c556f0fu; v.b = 0; }
    { V& v = m[0x4288916u]; v.a = 0x75f3c47au; v.b = 0; }
    { V& v = m[0x42a3491u]; v.a = 0x26a290fbu; v.b = 0; }
    { V& v = m[0x4aef54cu]; v.a = 0x61247e8au; v.b = 0; }
    { V& v = m[0x5f2281eu]; v.a = 0x8742f960u; v.b = 0; }
    { V& v = m[0x5f22835u]; v.a = 0x3600a13cu; v.b = 0; }
    { V& v = m[0x9d10712au]; v.a = 0x9d10712au; v.b = 0; }
    { V& v = m[0x631456d0u]; v.a = 0x631456d0u; v.b = 0; }
    { V& v = m[0x5dfc872u]; v.a = 0x147e73aau; v.b = 0; }
    { V& v = m[0x5dfc876u]; v.a = 0x8e205c26u; v.b = 0; }
    { V& v = m[0x5dfc877u]; v.a = 0x9eea0c4du; v.b = 0; }
    { V& v = m[0x674a629u]; v.a = 0x94e81dau; v.b = 0; }
    { V& v = m[0x5f4d3ceu]; v.a = 0x6cc01c53u; v.b = 0; }
    { V& v = m[0x5f4e0a8u]; v.a = 0xea04f48cu; v.b = 0; }
    { V& v = m[0x5f4e0b2u]; v.a = 0xb8888214u; v.b = 0; }
    { V& v = m[0x6257fd5u]; v.a = 0x18d072fbu; v.b = 0; }
    { V& v = m[0x6257fd6u]; v.a = 0x284f0d6du; v.b = 0; }
    { V& v = m[0x64bf470u]; v.a = 0x8b47348u; v.b = 0; }
    { V& v = m[0x64d02d1u]; v.a = 0x5b83cc01u; v.b = 0; }
    { V& v = m[0x64d03a2u]; v.a = 0x3a2ebdf1u; v.b = 0; }
    { V& v = m[0x65baa81u]; v.a = 0x653a14b2u; v.b = 0; }
    { V& v = m[0x71d8ae1u]; v.a = 0x86eac279u; v.b = 0; }
    { V& v = m[0x71d8ae2u]; v.a = 0xc3e33771u; v.b = 0; }
    { V& v = m[0x7b11813u]; v.a = 0x8b00b61bu; v.b = 0; }
    { V& v = m[0x303426c3u]; v.a = 0x64b8ee25u; v.b = 0; }
    { V& v = m[0x903426cdu]; v.a = 0xa4f9b7e1u; v.b = 0; }
    { V& v = m[0xf03426e2u]; v.a = 0xd2f96c5du; v.b = 0; }
    { V& v = m[0xf03426ebu]; v.a = 0x59627979u; v.b = 0; }
    { V& v = m[0x90342700u]; v.a = 0x236675a1u; v.b = 0; }
    { V& v = m[0x3034270eu]; v.a = 0xda408635u; v.b = 0; }
    { V& v = m[0x90342759u]; v.a = 0x84bf60c5u; v.b = 0; }
    { V& v = m[0xf0342787u]; v.a = 0x41fbaff5u; v.b = 0; }
    { V& v = m[0x70342790u]; v.a = 0x8a3f628fu; v.b = 0; }
    { V& v = m[0xb034279cu]; v.a = 0x5c53082fu; v.b = 0; }
    { V& v = m[0xb03427a8u]; v.a = 0x5bbb080eu; v.b = 0; }
    { V& v = m[0x903427bfu]; v.a = 0x3830077fu; v.b = 0; }
    { V& v = m[0x703427c9u]; v.a = 0x4717946au; v.b = 0; }
    { V& v = m[0xd03427ceu]; v.a = 0x7a23d986u; v.b = 0; }
    { V& v = m[0x903427dau]; v.a = 0xffd97cdau; v.b = 0; }
    { V& v = m[0x303d8d78u]; v.a = 0xc3a516aau; v.b = 0; }
    { V& v = m[0xd03d8d89u]; v.a = 0xff9d0821u; v.b = 0; }
    { V& v = m[0x703d8d99u]; v.a = 0x8618c23au; v.b = 0; }
    { V& v = m[0x1046f5efu]; v.a = 0x70071e35u; v.b = 0; }
    { V& v = m[0x37ac469u]; v.a = 0xdd64cccau; v.b = 0; }
    { V& v = m[0x37ac46au]; v.a = 0x1f7d424bu; v.b = 0; }
    { V& v = m[0xf046f5fdu]; v.a = 0xfafe30f5u; v.b = 0; }
    { V& v = m[0xf046f60au]; v.a = 0x81e1fb19u; v.b = 0; }
    { V& v = m[0x1046f612u]; v.a = 0x118baa1u; v.b = 0; }
    { V& v = m[0x7046f646u]; v.a = 0x17d5bd7bu; v.b = 0; }
    { V& v = m[0x7046f656u]; v.a = 0x20f1d4edu; v.b = 0; }
    { V& v = m[0xb062b167u]; v.a = 0x245cb231u; v.b = 0; }
    { V& v = m[0xf062b161u]; v.a = 0x68e34bdu; v.b = 0; }
    { V& v = m[0xd062b171u]; v.a = 0x1939bc61u; v.b = 0; }
    { V& v = m[0x3062b66bu]; v.a = 0xc273c016u; v.b = 0; }
    { V& v = m[0x5062b673u]; v.a = 0xa2d7c12du; v.b = 0; }
    { V& v = m[0x2e63e90u]; v.a = 0x60bad155u; v.b = 0; }
    { V& v = m[0x2e63e91u]; v.a = 0x63e4b4f4u; v.b = 0; }
    { V& v = m[0x2e63e92u]; v.a = 0x3d2f6e8eu; v.b = 0; }
    { V& v = m[0x2e63e93u]; v.a = 0x275cdfceu; v.b = 0; }
    { V& v = m[0x2e65455u]; v.a = 0x62065c42u; v.b = 0; }
    { V& v = m[0x11c8ccdfu]; v.a = 0x57ad4e74u; v.b = 0; }
    if (mv) mv->Release();
    e2->Release();
    e1->Release();
    w->Release();
}

// @ 0x00b3cf00
float C101::M_cf00()
{
    void* m = SP_GetCurrentGameMode();
    if (m == (void*)0x01654c01)
        return f14;
    if (m == (void*)0x01654c02)
        return f1c;
    if (m == (void*)0x01654c04)
        return f24;
    if (m == (void*)0x01654c05)
        return f2c;
    return 1000.0f;
}

// @ 0x00b3cf40
void C101::M_cf40()
{
    PropGroup* pg = 0;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    pm->GetGroup(0x39393837u, &pg);
    if (pg) {
        ReadFloatProp(pg, 0x041bacb8u, (float*)((char*)this + 0x00));
        ReadFloatProp(pg, 0x041b8f40u, (float*)((char*)this + 0x04));
        ReadFloatProp(pg, 0x041b8f45u, (float*)((char*)this + 0x08));
        ReadFloatProp(pg, 0x041b8f48u, (float*)((char*)this + 0x0c));
        ReadFloatProp(pg, 0x05dfdaaau, (float*)((char*)this + 0x10));
        ReadFloatProp(pg, 0x05dfdaaeu, (float*)((char*)this + 0x14));
        ReadFloatProp(pg, 0x05dfdab2u, (float*)((char*)this + 0x18));
        ReadFloatProp(pg, 0x05dfdab5u, (float*)((char*)this + 0x1c));
        ReadFloatProp(pg, 0x05dfdab8u, (float*)((char*)this + 0x20));
        ReadFloatProp(pg, 0x05dfdabau, (float*)((char*)this + 0x24));
        ReadFloatProp(pg, 0x05dfdabdu, (float*)((char*)this + 0x28));
        ReadFloatProp(pg, 0x05dfdac2u, (float*)((char*)this + 0x2c));
    }
}

// @ 0x00b3d700
S16 __cdecl FUN_00b3d700(unsigned a, unsigned b)
{
    S16 r;
    if (a < b) { r.hi = (unsigned short)a; r.lo = (unsigned short)b; }
    else       { r.hi = (unsigned short)b; r.lo = (unsigned short)a; }
    return r;
}

// @ 0x00b3d730
void C101::M_d730()
{
    void* self = (char*)this - 4;
    void* ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x0182c582u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x01a0219eu);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x025630b7u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x031018b9u);
    ms = SP_MessageServer();
    ((V20*)ms)->f20(self, 0x00f62defu);
    FUN_00b50ff0();
}

// @ 0x00b3d7a0
void C101::M_d7a0()
{
    ((FB57*)this)->f515e0();
    ((FB57*)this)->f5a2d0();
    g_167ece0 = 1;
}

// @ 0x00b3d850
void** __fastcall FUN_00b3d850(void** self)
{
    do {
        *(int*)self += 4;
        if (*self == self[1])
            break;
    } while (!((Neigh*)((char*)self + 8))->IsValid(*(void**)*self));
    return self;
}

// @ 0x00b3d870
void** __fastcall FUN_00b3d870(void** self)
{
    do {
        *(int*)self += 4;
        if (*self == self[1])
            break;
    } while (!((Neigh2*)((char*)self + 8))->IsValid(*(void**)*self));
    return self;
}

// @ 0x00b3d8c0
void* C101::M_d8c0()
{
    n68 = 0;
    n6c = 0;
    return this;
}

// @ 0x00b3d8d0
void __cdecl FUN_00b3d8d0(float* out, float* b, float* c, float p4, float p5, float p6)
{
    float c0 = c[0], c1 = c[1], c2 = c[2];
    float f1 = c0 - b[0];
    float f2 = c1 - b[1];
    float f3 = c2 - b[2];
    p4 = p4 - c0;
    p5 = p5 - c1;
    p6 = p6 - c2;
    float f4 = p6 * f2 - p5 * f3;
    f2 = p5 * f1 - p4 * f2;
    f3 = p4 * f3 - p6 * f1;
    // The original sums the three squares on the x87 (24-bit mantissa, extended exponent, i.e. the
    // device-thread FPCW) and takes fsqrt/fdivrp there; volatile doubles keep MSVC on the x87 path.
    // In the float range sqrtf/1.0f reproduce fsqrt/fdivrp exactly; outside it the sqrt is scaled by
    // a power of two so it still rounds to 24 bits before the reciprocal.
    volatile double v4 = f4, v3 = f3, v2 = f2;
    double d = v2 * v2 + v3 * v3 + v4 * v4;
    float inv;
    if (d >= 1.17549435e-38 && d <= 3.4028234663852886e38) {
        inv = 1.0f / sqrtf((float)d);
    } else {
        double fwd = (d > 3.4028234663852886e38) ? 1.2621774483536189e-29
                                                 : 3.402823669209385e38;
        double sf = (float)(sqrt(d) * fwd);
        inv = (float)((1.0 / sf) * fwd);
    }
    out[0] = inv * f4;
    out[1] = f3 * inv;
    out[2] = f2 * inv;
}

// @ 0x00b3d9c0
void C101::M_d9c0(float* out)
{
    float b0[6], b1[6];
    float* p;
    float v;
    switch (nMode) {
    case 0:
        p = (float*)((V6C*)p40)->f6C(b1);
        v = p[0] + p[3];
        break;
    case 1:
        p = (float*)((V6C*)p40)->f6C(b0);
        v = p[3] + p[0];
        break;
    case 2: {
        Obj40* o = p40;
        out[0] = *(float*)((char*)o + 0x38);
        out[1] = *(float*)((char*)o + 0x3c);
        out[2] = *(float*)((char*)o + 0x40);
        return;
    }
    default:
        return;
    }
    out[0] = v * 0.5f;
    out[1] = (p[4] + p[1]) * 0.5f;
    out[2] = (p[5] + p[2]) * 0.5f;
}

// @ 0x00b3da90
void C101::M_da90(float* out, int idx, C101* other)
{
    switch (nC) {
    case 2: {
        float* p = (float*)((char*)this + 0xf8 + idx * 0xc);
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
        return;
    }
    case 0:
    case 1: {
        float a[3], b[3];
        M_d9c0(a);
        other->M_d9c0(b);
        float x = b[0] - a[0];
        float y = b[1] - a[1];
        float z = b[2] - a[2];
        volatile double vx = x, vy = y, vz = z;
        double d = vx * vx + (vy * vy + vz * vz) + 1e-08;
        float s = (float)(1.0 / sqrt(d));
        out[0] = s * x;
        out[1] = y * s;
        out[2] = z * s;
        return;
    }
    default:
        out[0] = g_167ec2c;
        out[1] = g_167ec30;
        out[2] = g_167ec34;
    }
}

// @ 0x00b3dbb0
void C101::M_dbb0()
{
    b37 = 0;
    switch (nMode) {
    case 0: {
        b36 = 0;
        float* v = p40->GetVelocity();
        f1c = v[0]; f20 = v[1]; f24 = v[2];
        v = p40->GetBounding();
        f28 = v[0]; f2c = v[1]; f30 = v[2];
        switch (p40->n1f0) {
        case 0: case 1: case 6: case 7:
            b34 = 1;
            return;
        default:
            b34 = 0;
            return;
        }
    }
    case 1:
        if (f1c == g_167eb8c && f20 == g_167eb90 && f24 == g_167eb94)
            b36 = 0;
        else
            b36 = 1;
        return;
    case 2:
        b36 = 0;
        f1c = g_167eb8c; f20 = g_167eb90; f24 = g_167eb94;
        f28 = g_167eb8c; f2c = g_167eb90; f30 = g_167eb94;
        return;
    }
}

// @ 0x00b3dcd0
float C101::M_dcd0()
{
    void* volatile self = this;
    switch (nMode) {
    case 0: {
        Obj40* o = p40;
        if (o->b71 != 0) {
            self = this;
            return 0.0f;
        }
        float r0 = 1.0f / ((VD8*)o)->fD8();
        self = this;
        return r0;
    }
    case 1: {
        Obj40* o = p40;
        if (o->b71 == 0) {
            float* p = (float*)((V68*)o)->f68();
            float r1 = 1.0f / (((p[3] - p[0]) * (p[4] - p[1])) * (p[5] - p[2]) * g_15695fc);
            self = this;
            return r1;
        }
        break;
    }
    }
    self = this;
    return 0.0f;
}

// @ 0x00b3dd40
bool C101::M_dd40()
{
    if (nMode != 0)
        return false;
    Obj40* o = p40;
    if (o != 0) {
        void* e = ((VB8*)o)->fB8(0xce9f6639u);
        if (e != 0) {
            if (*((unsigned char*)e + 0xf90) != 0) {
                void* r = ((C0C*)e)->f();
                if (r != 0)
                    return false;
            }
            return true;
        }
    }
    return ((V48*)o)->f48() == false;
}

// @ 0x00b3dda0
void C101::M_dda0(float* pa, float* pb)
{
    char c;
    switch (nMode) {
    case 0: goto get;
    case 1: goto get;
    default:
        return;
    }
get:
    c = p40->b71;
    if (c != 0)
        return;

    float local[3];
    M_d9c0(local);
    e8 = pb[2] + e8;
    e4 = e4 + pb[1];
    e0 = e0 + pb[0];
    ec = ec + (pb[2] * (pa[1] - local[1]) - pb[1] * (pa[2] - local[2]));
    f0 = f0 + (pb[0] * (pa[2] - local[2]) - pb[2] * (pa[0] - local[0]));
    f4 = f4 + (pb[1] * (pa[0] - local[0]) - pb[0] * (pa[1] - local[1]));
}

// @ 0x00b3dec0
void C101::M_dec0(float* v)
{
    float s = M_dcd0();
    if (s > 1.5258789e-05f) {
        if (nMode == 0) {
            f1c = f1c + v[0] * s;
            f20 = v[1] * s + f20;
            f24 = v[2] * s + f24;
            b36 = 1;
        } else if (nMode == 1) {
            f1c = v[0] * s + f1c;
            f20 = f20 + v[1] * s;
            f24 = f24 + v[2] * s;
            b36 = 1;
        }
    }
}

// @ 0x00b3ef30
int cSpatialProxy::FUN_00b3ef30(void* obj, int count, void* vec, int idx, void* b, int* outCount)
{
    *outCount = 0;
    if (count < 3)
        return 0;

    float l1a0, l19c, l198;
    FUN_00b3d8d0(&l1a0, obj, (char*)obj + 0xc,
                 *(float*)((char*)obj + 0x18),
                 *(float*)((char*)obj + 0x1c),
                 *(float*)((char*)obj + 0x20));

    char buf[384];
    eastl_vector_insert(buf, vec, idx * 0xc);

    int i = 0;
    if (count > 0)
    {
        int off = (count * 3 - 3) * 4;
        float* p = (float*)((char*)obj + 8);
        do
        {
            float f1 = *(float*)(off + 4 + (char*)obj);
            float f2 = *(float*)(off + 8 + (char*)obj);
            float f7 = p[-2] - *(float*)(off + (char*)obj);
            float f8 = p[0] - f2;
            float f9 = p[-1] - f1;
            float l18c = l198 * f9 - l19c * f8;
            float l188 = f8 * l1a0 - l198 * f7;
            float l184 = l19c * f7 - f9 * l1a0;
            char ok = FUN_00b3eb90(buf, idx, b, outCount, &l18c,
                                   (l188 * f1 + l18c * *(float*)(off + (char*)obj)) + l184 * f2);
            if (!ok)
                return 0;
            idx = *outCount;
            eastl_vector_insert(buf, b, idx * 0xc);
            off = (-8 - (int)obj) + (int)p;
            i++;
            p += 3;
        } while (i < count);
    }
    return 1;
}

// @ 0x00b3f260
void FUN_00b3f260(Elem3c** out, Elem3c* first, Elem3c* last, Elem3c* dst)
{
    Elem3c* d = dst;
    *out = d;
    for (; first != last; ++first, ++d)
    {
        if (d != 0)
        {
            d->f0 = first->f0;
            d->f1 = first->f1;
            d->f2 = first->f2;
            d->f3 = first->f3;
            d->p = first->p;
            d->f4 = first->f4;
            d->f5 = first->f5;
            d->f6 = first->f6;
            d->f7 = first->f7;
            d->f8 = first->f8;
            d->f9 = first->f9;
            d->f10 = first->f10;
            d->f11 = first->f11;
            d->f12 = first->f12;
            d->b = first->b;
        }
    }
    *out = d;
}

// @ 0x00b3f300
Quaternion* cSpatialProxy::GetQuaternion(Quaternion* out)
{
    int state = *(int*)((char*)this + 4);
    Quaternion* q;
    switch (state)
    {
    case 0:
    {
        void* obj = *(void**)((char*)this + 0x40);
        q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        break;
    }
    case 1:
    {
        void* obj = *(void**)((char*)this + 0x40);
        q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        break;
    }
    case 2:
    {
        cSPTransform_s00b3_ef30* m = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        Quaternion local;
        q = &QuaternionFromMatrix33(local, m->mRot, 0.0f);
        break;
    }
    default:
        out->x = DAT_015696d8;
        out->y = DAT_015696dc;
        out->z = DAT_015696e0;
        out->w = DAT_015696e4;
        return out;
    }
    out->x = q->x;
    out->y = q->y;
    out->z = q->z;
    out->w = q->w;
    return out;
}

// @ 0x00b3f3a0
Matrix33* cSpatialProxy::GetMatrix(Matrix33* out)
{
    int state = *(int*)((char*)this + 4);
    switch (state)
    {
    case 0:
    {
        void* obj = *(void**)((char*)this + 0x40);
        Quaternion* q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        Matrix3FromQuaternion(*out, *q);
        return out;
    }
    case 1:
    {
        void* obj = *(void**)((char*)this + 0x40);
        Quaternion* q = (*(Quaternion* (__thiscall**)(void*))(*(char**)obj + 0x30))(obj);
        Matrix3FromQuaternion(*out, *q);
        return out;
    }
    case 2:
    {
        cSPTransform_s00b3_ef30* m = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        cSPTransform_s00b3_ef30 local(*m);
        out->Assign(local.mRot);
        return out;
    }
    default:
        out->Assign(*(Matrix33*)&DAT_0167ec08);
        return out;
    }
}

// @ 0x00b3f420
void cSpatialProxy::GetBoundingBox(cSPBoundingBox_s00b3_ef30* out)
{
    int state = *(int*)((char*)this + 4);
    if (state == 0 || state == 1)
    {
        void* obj = *(void**)((char*)this + 0x40);
        cSPBoundingBox_s00b3_ef30* b = (*(cSPBoundingBox_s00b3_ef30* (__thiscall**)(void*))(*(char**)obj + 0x68))(obj);
        out->mMax = b->mMax;
        out->mMin = b->mMin;
    }
    else if (state == 2)
    {
        void* obj = *(void**)((char*)this + 0x40);
        float v = *(float*)((char*)obj + 0x44);
        Vector3 a;
        a.x = v * DAT_0167ec2c;
        a.y = v * DAT_0167ec30;
        a.z = v * DAT_0167ec34;
        out->Extend(&a);
        a.x = -a.x; a.y = -a.y; a.z = -a.z;
        out->Extend(&a);

        float v2 = *(float*)((char*)obj + 0x44);
        Vector3 b;
        b.x = v2 * DAT_0167ec44;
        b.y = v2 * DAT_0167ec48;
        b.z = v2 * DAT_0167ec4c;
        out->Extend(&b);
        b.x = -b.x; b.y = -b.y; b.z = -b.z;
        out->Extend(&b);

        float v3 = *(float*)((char*)obj + 0x4c);
        Vector3 c;
        c.x = v3 * DAT_0167ec38;
        c.y = v3 * DAT_0167ec3c;
        c.z = v3 * DAT_0167ec40;
        out->Extend(&c);
    }
    ScaleBox(out, *(float*)((char*)this + 0x14));
}

// @ 0x00b3f6c0
void cSpatialProxy::GetTransform(cSPTransform_s00b3_ef30* out)
{
    int state = *(int*)((char*)this + 4);
    switch (state)
    {
    case 0:
        ((cSpatialObject*)*(void**)((char*)this + 0x40))->LocalToWorldTransform(out);
        break;
    case 1:
        ((cSpatialObject*)*(void**)((char*)this + 0x40))->LocalToWorldTransform(out);
        break;
    case 2:
    {
        cSPTransform_s00b3_ef30* r = ((cSpatialObject*)*(void**)((char*)this + 0x40))->FUN_00b73e70();
        ((cSPTransformOps*)out)->Assign(r);
        uint8_t* p = (uint8_t*)((char*)*(void**)((char*)this + 0x40) + 0x34);
        if (*p & 4)
        {
            ++out->mModCount;
            out->mScale = 1.0f;
        }
        break;
    }
    }
}

// @ 0x00b3f730
cSPBoundingBox_s00b3_ef30* cSpatialProxy::GetScaledBoundingBox(cSPBoundingBox_s00b3_ef30* out)
{
    out->mMin.x = DAT_01461150;
    out->mMin.y = DAT_01461150;
    out->mMin.z = DAT_01461150;
    out->mMax.x = DAT_013f51ac;
    out->mMax.y = DAT_013f51ac;
    out->mMax.z = DAT_013f51ac;

    int state = *(int*)((char*)this + 4);
    if (state == 0 || state == 1)
    {
        void* obj = *(void**)((char*)this + 0x40);
        cSPBoundingBox_s00b3_ef30* b = (*(cSPBoundingBox_s00b3_ef30* (__thiscall**)(void*))(*(char**)obj + 0x6c))(obj);
        out->mMax = b->mMax;
        out->mMin = b->mMin;
    }
    else if (state == 2)
    {
        GetBoundingBox(out);
        cSPTransform_s00b3_ef30 local;
        local.mFlags = 0;
        local.mModCount = 0;
        local.mPos.x = DAT_0167eb8c;
        local.mPos.y = DAT_0167eb90;
        local.mPos.z = DAT_0167eb94;
        local.mScale = DAT_01485720;
        local.mRot.Assign(*(Matrix33*)&DAT_0167ec08);
        GetTransform(&local);
        out->Transform(&local);
        return out;
    }
    ScaleBox(out, *(float*)((char*)this + 0x14));
    return out;
}

// @ 0x00b3f940
void cSpatialProxy::Integrate()
{
    float v = TimeScale();
    if (v > 0.0f)
    {
        float vx = *(float*)((char*)this + 0x44) * v;
        float vy = *(float*)((char*)this + 0x48) * v;
        float vz = *(float*)((char*)this + 0x4c) * v;
        *(float*)((char*)this + 0x1c) = *(float*)((char*)this + 0x1c) + vx;
        *(float*)((char*)this + 0x20) = *(float*)((char*)this + 0x20) + vy;
        *(float*)((char*)this + 0x24) = *(float*)((char*)this + 0x24) + vz;

        float px = *(float*)((char*)this + 0x50);
        float py = *(float*)((char*)this + 0x54);
        float pz = *(float*)((char*)this + 0x58);

        *(float*)((char*)this + 0x2c) =
            ((*(float*)((char*)this + 0xa8) * px + *(float*)((char*)this + 0xb4) * py) +
             *(float*)((char*)this + 0xc0) * pz) + *(float*)((char*)this + 0x2c);
        *(float*)((char*)this + 0x30) =
            ((*(float*)((char*)this + 0xac) * px + *(float*)((char*)this + 0xb8) * py) +
             *(float*)((char*)this + 0xc4) * pz) + *(float*)((char*)this + 0x30);
        *(float*)((char*)this + 0x28) =
            *(float*)((char*)this + 0x28) +
            ((*(float*)((char*)this + 0xb0) * py + *(float*)((char*)this + 0xbc) * pz) +
             *(float*)((char*)this + 0xa4) * px);

        *(Vector3*)((char*)this + 0x44) = *(Vector3*)&DAT_0167eb8c;
        *(Vector3*)((char*)this + 0x50) = *(Vector3*)&DAT_0167eb8c;
    }
}

// @ 0x00b3faa0
void cSpatialProxy::IntegrateCollide(float* p2, float* p3)
{
    float v = TimeScale();
    if (v > DAT_01461154 && *(uint32_t*)((char*)this + 4) <= 1)
    {
        float f5 = p3[0];
        float f1 = p3[2];
        *(float*)((char*)this + 0x20) = *(float*)((char*)this + 0x20) + p3[1] * v;
        *(float*)((char*)this + 0x1c) = *(float*)((char*)this + 0x1c) + f5 * v;
        *(float*)((char*)this + 0x24) = *(float*)((char*)this + 0x24) + f1 * v;

        float lc, l8, l4;
        GetPosition(&lc);

        float dy = p2[1] - l8;
        float dx = p2[0] - lc;
        float dz = p2[2] - l4;
        lc = p3[2] * dy - p3[1] * dz;
        l8 = p3[0] * dz - p3[2] * dx;
        l4 = p3[1] * dx - p3[0] * dy;

        if (FUN_0059ab70(&lc))
        {
            *(float*)((char*)this + 0x28) =
                ((*(float*)((char*)this + 0xbc) * l4 + *(float*)((char*)this + 0xb0) * l8) +
                 *(float*)((char*)this + 0xa4) * lc) + *(float*)((char*)this + 0x28);
            *(float*)((char*)this + 0x2c) =
                *(float*)((char*)this + 0x2c) +
                ((*(float*)((char*)this + 0xc0) * l4 + *(float*)((char*)this + 0xb4) * l8) +
                 *(float*)((char*)this + 0xa8) * lc);
            *(float*)((char*)this + 0x30) =
                *(float*)((char*)this + 0x30) +
                ((*(float*)((char*)this + 0xc4) * l4 + *(float*)((char*)this + 0xb8) * l8) +
                 *(float*)((char*)this + 0xac) * lc);
        }
        *(uint8_t*)((char*)this + 0x36) = 1;
    }
}

// @ 0x00b3fc80
int FUN_00b3fc80(void* self)
{
    cSpatialDB* db = (cSpatialDB*)((char*)DAT_0167eb70 + 0x3c);
    cSpatialProxy* a = db->Find(*(int*)((char*)self + 4));
    cSpatialProxy* b = db->Find(*(int*)((char*)self + 8));
    if (a == 0 || b == 0)
        return 0;

    int state = *(int*)((char*)a + 4);
    if (state == 0 || state == 1)
    {
        if (*(uint8_t*)(*(int*)((char*)a + 0x40) + 0x75) == 0)
            return 0;
        if (*(uint8_t*)(*(int*)((char*)a + 0x40) + 0x70) == 0 &&
            *(uint8_t*)((char*)a + 0x35) == 0)
            return 0;
    }
    else if (state != 2)
    {
        return 0;
    }

    if (!b->IsValid())
        return 0;

    float s = *(float*)((char*)DAT_0167eb70 + 0xb0) - DAT_01485720;
    float old = *(float*)((char*)self + 0x28);
    float t1 = (*(float*)((char*)b + 0x24) - *(float*)((char*)a + 0x24)) * s;
    float t2 = (*(float*)((char*)b + 0x20) - *(float*)((char*)a + 0x20)) * s;
    float t3 = (*(float*)((char*)b + 0x1c) - *(float*)((char*)a + 0x1c)) * s;
    float m = ((((*(float*)((char*)self + 0x20) * t1 +
                  *(float*)((char*)self + 0x1c) * t2) +
                 *(float*)((char*)self + 0x18) * t3) +
                *(float*)((char*)self + 0x34)) * *(float*)((char*)self + 0x30)) + old;
    if (m < 0.0f)
        m = 0.0f;
    *(float*)((char*)self + 0x28) = m;

    float d = m - old;
    Vector3 n;
    n.x = *(float*)((char*)self + 0x18) * d;
    n.y = *(float*)((char*)self + 0x1c) * d;
    n.z = *(float*)((char*)self + 0x20) * d;
    if (0.0f <= ((*(float*)((char*)self + 0x20) * n.z +
                  *(float*)((char*)self + 0x1c) * n.y) +
                 n.x * *(float*)((char*)self + 0x18)))
    {
        Vector3 neg;
        neg.x = -n.x;
        neg.y = -n.y;
        neg.z = -n.z;
        a->IntegrateCollide((float*)((char*)self + 0xc), (float*)&neg);
        b->IntegrateCollide((float*)((char*)self + 0xc), (float*)&n);
    }
    return 1;
}

// @ 0x00b3fe40
unsigned int SphereVsBoxContact(const Vector3_s00b3_fe40& center, float radius, const BoundingBox& box, const cSPTransform_s00b3_fe40& xform, bool bAllFaces, ContactManifold* out)
{
    Vector3_s00b3_fe40 p = center - xform.mTranslation;
    if (xform.mScale != 1.0f) {
        float invScale = 1.0f / xform.mScale;
        p *= invScale;
    }
    if (xform.mFlags & cSPTransform_s00b3_fe40::kTransformFlagRotation)
        p = xform.mRotation * p;

    BoundingBox expanded;
    expanded.lower = Vector3_s00b3_fe40(box.lower.x - radius, box.lower.y - radius, box.lower.z - radius);
    expanded.upper = Vector3_s00b3_fe40(box.upper.x + radius, box.upper.y + radius, box.upper.z + radius);
    // The six rejection exits at 0x00b3ffd0..0xb40009 still hold the box pointer loaded at 0x00b3ff88.
    if (!expanded.Contains(p))
        return (unsigned int)(size_t)&box;

    Vector3_s00b3_fe40 normal;
    float depth;
    unsigned int eaxResidue;
    if (!box.Contains(p)) {
        // Center outside the box: closest point on the box surface.
        Vector3_s00b3_fe40 q;
        q.x = Clamp(p.x, box.lower.x, box.upper.x);
        q.y = Clamp(p.y, box.lower.y, box.upper.y);
        q.z = Clamp(p.z, box.lower.z, box.upper.z);
        eaxResidue = EaxBits(q.y);      // 0x00b400d4 `mov eax,dword ptr [esp+0x38]` (the clamped y)
        p = q;
        if (xform.mFlags & cSPTransform_s00b3_fe40::kTransformFlagRotation)
            p = p * xform.mRotation;
        p = xform.mTranslation + xform.mScale * p;
        Vector3_s00b3_fe40 d = p - center;
        float invLen = (float)(1.0 / sqrt((double)d.x * d.x + (double)d.y * d.y + (double)d.z * d.z + 1e-8f));
        normal = -(invLen * d);
        depth = (float)(radius - sqrt((double)d.x * d.x + (double)d.y * d.y + (double)d.z * d.z));
    } else {
        // Center inside the box: push out through the nearest face.
        Plane planes[6] = {
            Plane(-kBoxAxes[0], box.lower),
            Plane(-kBoxAxes[2], box.lower),
            Plane(kBoxAxes[2], box.upper),
            Plane(kBoxAxes[0], box.upper),
            Plane(kBoxAxes[1], box.upper),
            Plane(-kBoxAxes[1], box.lower),
        };
        float minDist = FLT_MAX;
        Plane best = planes[0];
        int numPlanes = bAllFaces ? 6 : 4;
        // The original searches planes 0..3 with a 4x-unrolled loop that finishes by leaving the index
        // (4) in eax (0x00b405bb / 0x00b406dd) and only the two leftover planes write a plane's d back
        // to eax (0x00b40727 `mov eax,dword ptr [ecx+8]`): the residue is 4 unless plane 4 or 5 wins.
        unsigned int residue = 4;
        for (int i = 0; i < numPlanes; i++) {
            float dist = (float)fabs(planes[i].Distance(p));
            if (dist < minDist) {
                minDist = dist;
                best = planes[i];
                if (i >= 4)
                    residue = EaxBits(planes[i].d);
            }
        }
        if (minDist == FLT_MAX)             // 0x00b4076e `jnp 0xb40a12`: eax is still that index
            return residue;
        p = p - best.n * radius;
        if (xform.mFlags & cSPTransform_s00b3_fe40::kTransformFlagRotation)
            p = p * xform.mRotation;
        p = xform.mScale * p + xform.mTranslation;
        normal = best.n;
        if (xform.mFlags & cSPTransform_s00b3_fe40::kTransformFlagRotation)
            normal = normal * xform.mRotation;
        normal = xform.mScale * normal;
        depth = minDist + radius;
        // 0x00b40795 `mov ax,word ptr [esp+0x40]` replaces the low word of eax with (mFlags & 2).
        eaxResidue = (residue & 0xFFFF0000u) | (unsigned int)(xform.mFlags & 2);
    }
    if (depth > 1.0f / 65536.0f) {
        out->mPoints[0] = p;
        out->mPointsB[0] = p;
        out->mCount = 1;
        out->mNormal = -normal;
        out->mf190 = 0.0f;
        out->mPenetration = depth * -normal;
        return (unsigned int)(size_t)out;   // 0x00b40982 `mov eax,dword ptr [esp+0xe8]`
    }
    return eaxResidue;
}
