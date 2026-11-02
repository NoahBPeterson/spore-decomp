// src/game/SPGonzago/_at_00c20000.cpp -- migrated from slice(s) s00c2d220, s00c2b030, s00c299e0, s00c289b0, s00c278e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c20000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cActionCircle.h"
#include "SP/cCommunity.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern char DAT_018eb45e;                       // 0x018eb45e
extern char DAT_018eb4b7;                       // 0x018eb4b7
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_01654c05;                       // 0x01654c05
extern char DAT_01654c10;                       // 0x01654c10
#include <math.h>
#include <string.h>
#include <xmmintrin.h>
#include "SP/cAnimatingCreature.h"
#include "SP/cLocomotiveObject.h"
#include <float.h>

// ---- items of slice s00c278e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
#define nullptr 0
struct Vec3 { f32 x, y, z; };
class cVTable { public: void* mpSlots[0x100]; };
class cDispatchObject {
public:
    void* Call(i32 nSlot) {
        return ((void* (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    i32 CallInt(i32 nSlot) {
        return ((i32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    f32 CallFloat(i32 nSlot) {
        return ((f32 (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    void CallVoid(i32 nSlot) {
        ((void (__thiscall*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }
    void CallVoidArg(i32 nSlot, i32 nArg) {
        ((void (__thiscall*)(cDispatchObject*, i32))mpTable->mpSlots[nSlot >> 2])(this, nArg);
    }
    void* CallArg(i32 nSlot, void* pArg) {
        return ((void* (__thiscall*)(cDispatchObject*, void*))mpTable->mpSlots[nSlot >> 2])(this, pArg);
    }
    cVTable* mpTable;                           // +0x000
};
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
class cStarRecordVector {
public:
    void Destroy();                             // 0x00ae6970
    cStarRecordVector& CopyFrom(cStarRecordVector* pOther);   // 0x00c277f0

    void* mpBegin;                              // +0x000
    void* mpEnd;                                // +0x004
    void* mpCapacity;                           // +0x008
};
class cRefVector {
public:
    void Resize(i32 nCount, void* pSrc);        // 0x00b93c60
    void Erase(void* pBegin, void* pEnd);       // 0x00e25bd0

    void* mpBegin;                              // +0x000
    void* mpEnd;                                // +0x004
    void* mpCapacity;                           // +0x008
};
class cActionCircle {
public:
    cActionCircle* FUN_00afba10();              // 0x00afba10 (construct)
    void FUN_00afbad0();                        // 0x00afbad0 (destroy)
    cActionCircle* CopyFrom(cActionCircle* pSrc);   // 0x00c278e0

    f32 m00, m04, m08, m0c, m10, m14, m18, m1c, m20;   // +0x00
    i32 m24;                                    // +0x24
    u8  m28;                                    // +0x28
    u8  mPad29[3];                              // +0x29
    f32 m2c, m30, m34, m38;                     // +0x2c
    cRefVector mVec;                            // +0x3c
    void* m48;                                  // +0x48
    u8  mPad4c[4];                              // +0x4c
    cStarRecordVector mStars;                   // +0x50
    u8 mPad5c[0x0c];                            // +0x5c
};
struct cMapIterator { void* mpNode; void* mpEnd; u32 mPad; };
struct cMapRecord { u32 mKey; cActionCircle mCircle; };
class cActionCircleMap {
public:
    void Find(cMapIterator* pOut, u32* pKey);               // 0x00ac9d30
    void Insert(cMapIterator* pIt, cMapRecord* pRec, bool flag);  // 0x00c27a80
    cActionCircle* FindOrAdd(i32* pKey);                    // 0x00c27d20

    u8    mPad00[4];                            // +0x00
    void** mpBuckets;                           // +0x04
    u32   mnCount;                              // +0x08
    u8    mPad0c[4];                            // +0x0c
    u8    mPad10[0x10];                         // +0x10
};
class cActionMapOwner {
public:
    i32 FindOrAddKey(i32 nKey);                 // 0x00c27db0

    u8 mPad000[0x394];                          // +0x000
    cActionCircleMap mMap;                      // +0x394
};
class cBodyObject {
public:
    void* FUN_00c41ec0();                       // 0x00c41ec0 -> this+0x1f4
};
class cCreatureBase {
public:
    void FUN_00c1fe80();                        // 0x00c1fe80
    void FUN_00c1c8e0();                        // 0x00c1c8e0
    i32  FUN_00c0c2f0();                        // 0x00c0c2f0
    bool Flag388();                             // 0x00c0c0e0
    void* FUN_00c0b750();                       // 0x00c0b750
    void* FUN_00c04590();                       // 0x00c04590
    void* GetTribe();                           // 0x00c22f50
    void* FUN_00c41ec0();                       // 0x00c41ec0
    void funcC4h();                             // 0x00c27b70
    void MoveToPointAndFacingAtSpeed(i32 nMode, float* pPos, float* pDir, f32 s0, f32 s1); // 0x00c1c5c0
    void MoveToPointAtSpeedPathPlan(void* pPlan, i32* pTarget, f32 s0, f32 s1, i32 nZero); // 0x00c1c310

    u8   mPad000[0x110];                        // +0x000
    u32  m110;                                  // +0x110
    u8   mPad114[0x23];                         // +0x114
    u8   m137;                                  // +0x137
    u8   mPad138[0x118];                        // +0x138
    Vec3 m250;                                  // +0x250
    u8   m25c;                                  // +0x25c
    u8   mPad25d[0xd3];                         // +0x25d
    u32  m330;                                  // +0x330
    u8   mPad334[0xcdc];                        // +0x334
    cRefCounted* mpOwnerCity;                   // +0x1010
    cRefCounted* mpOwnerTribe;                  // +0x1014
    cRefVector   mVec1018;                      // +0x1018
    i32  mnSpecializedTool;                     // +0x1024
    cRefCounted* mpHitSphere;                   // +0x1028
    i32  mnToolEffectIndex;                     // +0x102c
    cRefCounted* mpNoun;                        // +0x1030
};
class cCreatureCitizen {
public:
    void SetSpecializedTool(i32 nTool);         // 0x00c279a0
    void* FUN_00c27dd0(void* pObj);             // 0x00c27dd0
    void MoveToPointAndFacingAtSpeed(i32 nMode, float* pPos, float* pDir, f32 s0, f32 s1); // 0x00c1c5c0

    u8   mPad000[0xe8c];                        // +0x000
    i32  mnE8c;                                 // +0x0e8c
    i32  mnE90;                                 // +0x0e90
    f32  mfE94;                                 // +0x0e94
    void* mpE98;                                // +0x0e98
    void* mpE9c;                                // +0x0e9c
    u8   mPadEA0[0x170];                        // +0x0ea0
    cRefCounted* mpOwnerCity;                   // +0x1010
    cRefCounted* mpOwnerTribe;                  // +0x1014
    u8   mPad1018[0x14];                        // +0x1018
    i32  mnToolEffectIndex;                     // +0x102c
};
class cPlanetModel {
public:
    void  FUN_00b7e430(void* pOut, i32 nFlag);            // 0x00b7e430
    void* FUN_00b816f0(void* pOut, void* pIn);            // 0x00b816f0
    void  FUN_00b7f250(void* pOut, void* pPos, void* pDir); // 0x00b7f250
};
cPlanetModel* __cdecl PlanetModel();            // 0x00b3d350
class cTribe {
public:
    void FUN_00c8f540(Vec3* pOut, f32 fA, i32 nB, void* pC, void* pD, void* pE);  // 0x00c8f540
};
class cCreatureList {
public:
    u8 mPad40[0x40];                            // +0x00
    cCreatureBase** mpBegin;                    // +0x40
    cCreatureBase** mpEnd;                      // +0x44
};
class cOtherMgr {
public:
    void FUN_00bc97f0(u32 a, u32 b, f32 c, void* d);   // 0x00bc97f0
};
void* __cdecl FUN_00b3d310();                   // 0x00b3d310
void* __cdecl GetCurrentGameMode();             // 0x00b5b800
void* __cdecl FUN_00b532b0(void* pKey);         // 0x00b532b0
void* __cdecl FUN_00ac80d0(void* pObj, void* pType);  // 0x00ac80d0
void* __cdecl FUN_00c423c0(void* pSelf);        // 0x00c423c0
void* __cdecl FUN_00c986d0(void* pContainer, i32 nKey, i32* pOut, void* pSelf);  // 0x00c986d0
extern Vec3 g_168dd78;                          // 0x0168dd78
extern char DAT_018eb45e;                       // 0x018eb45e
extern char DAT_018eb4b7;                       // 0x018eb4b7
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_01654c05;                       // 0x01654c05
extern char DAT_01654c10;                       // 0x01654c10
struct cRecord3c { u32 m[0xf]; };
// ---- items of slice s00c278e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vec3 g_168dd78;                          // 0x0168dd78

// ---- items of slice s00c289b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s00c289b0 { float x, y, z; };
struct Vec4_s00c289b0 { float x, y, z, w; };
typedef void* (__thiscall *VtFnP)(void*);
typedef float (__thiscall *VtFnF)(void*);
typedef void  (__thiscall *VtFnV)(void*);
static inline void* VtCall0(void* obj, int slot) { return ((VtFnP)(*(void***)obj)[slot / 4])(obj); }
static inline float VtCallF(void* obj, int slot) { return ((VtFnF)(*(void***)obj)[slot / 4])(obj); }
static inline void  VtCallV0(void* obj, int slot) { ((VtFnV)(*(void***)obj)[slot / 4])(obj); }
static inline Vec3_s00c289b0* BodyPos(void* bodyObj) { return (Vec3_s00c289b0*)VtCall0(bodyObj, 0x2c); }
static inline float           BodyFlt(void* bodyObj) { return VtCallF(bodyObj, 0x74); }
struct Timing_s00c289b0 { char _pad[0x10]; float step; };
struct Body_s00c289b0 {
	char           _pad000[0x14];
	Vec3_s00c289b0 pos;      // +0x14
	char           _pad020[0x50 - 0x20];
	Vec3_s00c289b0 vel;      // +0x50
	int            m5c;      // +0x5c
	char           _pad060[0x68 - 0x60];
	float          m68;      // +0x68
	float          m6c;      // +0x6c
};
struct Motion_s00c28b40 {
	Vec3_s00c289b0 v;        // +0x00
	char           _pad00c[0x10 - 0xc];
	float          step;     // +0x10
	void*          obj14;    // +0x14
};
struct PathRec_s00c290d0 { Vec3_s00c289b0 p; char _pad[0x3c - 12]; };
struct Path_s00c290d0 {
	PathRec_s00c290d0* begin;   // +0x00
	PathRec_s00c290d0* end;     // +0x04
	char               _pad008[0x14 - 8];
	Vec3_s00c289b0     base;    // +0x14
};
struct XformMsg_s00c289b0 {
	unsigned short m0;       // +0x00
	unsigned short mCount;   // +0x02
	Vec3_s00c289b0 pos;      // +0x04
	float          mScale;   // +0x10
	float          mRot[9];  // +0x14
	void Ctor();             // 0x00434040
};
struct Eff_s00c289b0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
	virtual void SetXform(XformMsg_s00c289b0* m);   // +0x18
	virtual void v1c();                             // +0x1c
	virtual void GetXform(XformMsg_s00c289b0* m);   // +0x20
};
struct C_s00c289b0 {
	char     _pad000[0x110];
	unsigned m110;           // +0x110
	char     _pad114[0x137 - 0x114];
	char     m137;           // +0x137
	char     _pad138[0x2b0 - 0x138];
	int      m2b0;           // +0x2b0
	char     _pad2b4[0x330 - 0x2b4];
	unsigned m330;           // +0x330
	char     _pad334[0xb54 - 0x334];
	void*    mB54;           // +0xb54
	char     _padB58[0xb5e - 0xb58];
	char     mB5e;           // +0xb5e
	char     _padB5f[0xf90 - 0xb5f];
	char     mF90;           // +0xf90

	void  SetFlagPair(bool b, unsigned a, unsigned c);                               // 0x00c201a0
	void* GetEffect(unsigned id);                                                    // 0x00c14e70
	bool  Flag388();                                                                 // 0x00c0c0e0
	int   FnC0C2F0();                                                                // 0x00c0c2f0
	void* FnC0EE60();                                                                // 0x00c0ee60
	float* PathAverage(float* out, Path_s00c290d0* path, const float* inEAX);        // 0x00c290d0
};
struct Pm_s00c289b0 {
	Vec3_s00c289b0* Transform(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);       // 0x00b816f0
	Vec3_s00c289b0* TransformClamp(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);  // 0x00b81630
	float GetWaterHeight();                                                          // 0x00b7e390
	float GetRadius();                                                               // 0x00b7e490
	void  BuildSurfaceOrientation(void* out, const void* pos, const void* dir);      // 0x00b7f250
	Vec3_s00c289b0* RotateTo(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);        // 0x00b7ee70
	float HeightAt(const Vec3_s00c289b0* in);                                        // 0x00b7ecc0
};
struct Chunk_s00c296b0 { char _pad[0x100]; void Ctor(); };   // 0x00af4da0
void*  __cdecl F_PlanetModel();                          // 0x00b3d350
void*  __cdecl F_GetTriggerMgr();                        // 0x00b3d4d0
void*  __cdecl F_b3d310();                               // 0x00b3d310
void*  __cdecl F_GetCurrentGameMode();                   // 0x00b5b800
Vec3_s00c289b0* __cdecl F_normalized_safe(Vec3_s00c289b0* out, const Vec3_s00c289b0* in);   // 0x00449c20
extern Vec3_s00c289b0 g_168dd78_s00c2_89b0;   // 0x0168dd78
struct C_s00c296b0
{
	char m_storage[0x800];
	int  m_zero[8];           // +0x800 .. +0x81f
	C_s00c296b0* Init();
};
// ---- items of slice s00c289b0 end

// ---- items of slice s00c299e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_1485720;   // 1.0f                 0x01485720
extern float g_13eb1bc;   // -1.0f                0x013eb1bc
extern float g_1470f1c;   // 2.0f                 0x01470f1c
extern float g_1471064;   // 0.5f                 0x01471064
extern float g_1572420;   // PI                   0x01572420
extern float g_1572484;   // 1.5f                 0x01572484
extern char  g_1572480;   // global flag          0x01572480
extern char  g_168de1c;   //                      0x0168de1c
extern float g_168de28;   //                      0x0168de28
typedef unsigned int  uint;
typedef unsigned char uchar;
void   FUN_00c293f0(void* out, void* a, int b);                     // 0x00c293f0
float* FUN_0059aed0(void* out, void* dat, void* in);                // 0x0059aed0
bool   FUN_00b3d550(void* q);                                       // 0x00b3d550
float* FUN_005b2500(void* out, void* a, void* b, float t);          // 0x005b2500  Slerp
void*  FUN_005b26f0(void* out, void* a, void* b, float t);          // 0x005b26f0  SlerpWrap
void*  operator_delete__(void*);                                    // 0x00f47380
struct cOrientSub {
    void* vtbl;   // +0x00
};
struct cOrientation {
    uchar      pad00[0xc0];
    cOrientSub m_sub;                  // +0x0c0
    uchar      pad_c4[0xf0 - 0xc4];
    float      m_f0, m_f4, m_f8, m_fc; // +0x0f0..+0x0fc
    uchar      pad_100[0x2ac - 0x100];
    float      m_2ac;                  // +0x2ac

    void*  CopyFrom(const cOrientation* src);                       // 0x00c29ab0
    void   CopyBase(const void* src);                              // 0x00af6250
    int    GetSubCount();                                          // 0x00c0c2f0
};
struct cNodeSub {
    uchar m[0x100];
    void Destroy();            // 0x00c2e4e0  SetSerializer / destructor
};
struct ConstraintNode {
    uint  key;                 // +0x000
    uchar sub[0x800];          // +0x004 .. +0x804  (eight 0x100-byte sub-objects)
    void* ptrs[8];             // +0x804 .. +0x824
    ConstraintNode* next;      // +0x824
};
struct ConstraintTable {
    uchar pad00[4];
    ConstraintNode** buckets;  // +0x04
    uint  size;                // +0x08
    int   count;               // +0x0c

    int remove(uint* key);                                          // 0x00c299e0
};
extern ConstraintTable g_1572460;                                   // 0x01572460
// ---- items of slice s00c299e0 end

// ---- items of slice s00c2b030 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __stdcall FUN_00406540(void* dst, const void* src, int stride, int count, void* fn);
struct Node;
struct TraceCache;
struct Hit
{
	char mBytes[0x100];          // cached trace entry; only its size matters to this slice
};
struct TraceCache
{
	Hit   hits[8];               // +0x000 .. +0x7ff
	void* objects[8];            // +0x800 .. +0x81f
	TraceCache* Init();          // 0x00c296b0
	void        Destroy();       // 0x00cadb00
};
extern "C" void __cdecl FUN_00cadb50(TraceCache* cache);
struct Value                   // what the table stores: the key plus the mapped cache
{
	unsigned   mKey;             // +0x000
	TraceCache mValue;           // +0x004 .. +0x823
	__declspec(noinline) Value* CopyFrom(const unsigned* key, TraceCache* src);   // 0x00c2b030
};
struct Node : Value            // 0x828-byte bucket node; only the allocated nodes carry the link
{
	Node* mpNext;                // +0x824
};
struct Iter                    // eastl hash iterator (8 bytes)
{
	Node*  mpNode;               // +0x00
	Node** mpBucket;             // +0x04
};
struct InsertResult : Iter     // eastl insert() result, the iterator plus the "already present" flag
{
	bool mInserted;              // +0x08
};
struct Ht                      // global instance at 0x01572460
{
	void*    mField00;           // +0x00 (hash functor)
	Node**   mpBuckets;          // +0x04
	unsigned mBucketCount;       // +0x08
	unsigned mSize;              // +0x0c
	void*    mAllocator;         // +0x10
	void Find(Iter* out, const unsigned* key);                          // 0x00cb00d0
	// 0x00cb1110 only tests the low byte of `existing` (cmp byte [esp+0x10], 0).
	void Insert(InsertResult* out, const Value* value, unsigned existing);
	__declspec(noinline) TraceCache* FindOrInsert(const unsigned* key);  // 0x00c2b080
};
// ---- items of slice s00c2b030 end

// ---- items of slice s00c2d220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t g_169e381, g_169e37e, g_169e37f;
extern float g_169e384, g_169e388, g_169e38c, g_169e390;
struct Vector3 { float x, y, z; };
inline bool TestBit(unsigned v, unsigned n) { return ((v >> n) & 1) != 0; }
#define LO ((Loco*)((char*)c + 0xc0))
#define F(T, p, off) (*(T*)((char*)(p) + (off)))
struct StEntry { uint32_t d[15]; };
struct St {
    StEntry* begin;            // +0x00
    StEntry* end;              // +0x04
    uint32_t pad0[3];
    Vector3 pos;               // +0x14
    float f20;                 // +0x20
    uint32_t pad1[10];
    uint8_t flags4c;           // +0x4c
    uint8_t pad2[3];
    Vector3 dir;               // +0x50
    int mode;                  // +0x5c
    uint32_t pad3;
    float f64;                 // +0x64
    float f68;                 // +0x68
    uint32_t pad4;
    uint8_t flags70;           // +0x70
    void F47520(const StEntry* e);
};
struct Obj3 {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual float V74();   // slot 29
};
struct Obj2 {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual Vector3* GetPosition();   // slot 11
};
struct Obj1 {
    virtual void pad0();
    virtual void pad1();
    virtual Obj2* Get8();   // slot 2
};
struct Loco {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual Vector3* GetPosition();                // slot 11 (+0x2c)
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual Vector3* GetHeading(Vector3* out);     // slot 23 (+0x5c)
    virtual void pad24();
    virtual void pad25();
    virtual void pad26();
    virtual void pad27();
    virtual void pad28();
    virtual float GetRadius();                     // slot 29 (+0x74)
    virtual void pad30();
    virtual void pad31();
    virtual void pad32();
    virtual void pad33();
    virtual void pad34();
    virtual void pad35();
    virtual void pad36();
    virtual void pad37();
    virtual void pad38();
    virtual void pad39();
    virtual void pad40();
    virtual void pad41();
    virtual void pad42();
    virtual void pad43();
    virtual void pad44();
    virtual void pad45();
    virtual void* Query(unsigned id);              // slot 46 (+0xb8)
    virtual void pad47();
    virtual void pad48();
    virtual void* V_c4(float f, int i);              // slot 49 (+0xc4)
    virtual float GetDesiredSpeed();                 // slot 50 (+0xc8)
    virtual void pad51();
    virtual void pad52();
    virtual void pad53();
    virtual void pad54();
    virtual void V_dc(void* p);                      // slot 55 (+0xdc)
    Vector3* GetVelocity();   // 0xd20610
    bool IsNearGoal();   // 0xc42e20
    void UpdateSteeringForMovementStyle();   // 0xc44610
    St* GetState();                                  // 0xC41EC0
    bool Within(float a, float b);                   // 0xC41ED0
    float* F421f0();   // 0xc421f0
    void F44080(Vector3* out);   // 0xc44080
};
struct Sub15b8 {
    void F9ce740(float f);   // 0x9ce740
};
struct Anim {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void Q58(int* out, int a, int b, void** p);   // slot 22 (+0x58)
    virtual bool Q5c(void* p, float* den, float* num);    // slot 23 (+0x5c)
    bool IsOrientStartAnim(int id);   // 0xa02710
};
struct Creature {
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual unsigned GetType();    // slot 8 (+0x20)
    int GetStyle();                      // 0xC0C2F0
    Obj1* F0ee60();                      // 0xC0EE60
    Vector3* F290d0(Vector3* out, St* st, ...);   // 0xC290D0
};
struct Ctx {
    Vector3 out;     // +0x00
    uint32_t pad[1];
    float f10;       // +0x10
    Loco* obj;       // +0x14
};
struct Info2b110 { uint32_t pad[1]; int f4; float f8; };
struct Info532b0 { uint32_t pad[0x33]; int fcc; };
void operator delete[](void* p);   // 0x00f47380
struct ArrObj {
    void* p;
    uint32_t rest[0x1c];
    ArrObj();   // 0xac9850
    ~ArrObj() { if (p && ((int*)p)[-1] != 0) operator delete[](p); }
};
extern Vector3 g_168dd78_s00c2_d220;
unsigned GetCurrentGameMode_s00c2_d220();   // 0xb5b800
void F2a190(Ctx* ctx, Creature* c);   // 0xc2a190
void F28290(Creature* c, Vector3* p, float* dist);   // 0xc28290
Info532b0* F0b532b0(Loco* l);   // 0xb532b0
char F28870(Ctx* ctx, Creature* c, Vector3* pos, St* st);   // 0xc28870
Info2b110* F2b110(Creature* c);   // 0xc2b110
void F0cadb50(Info2b110* p);   // 0xcadb50
void F289b0(Ctx* ctx, Creature* c, St* st, bool nearFlag, float dist);   // 0xc289b0
char F2c7b0(Creature* c, St* st, Vector3* heading, float* scale, const int& style);   // 0xc2c7b0
void F2cac0(Creature* c, Vector3* heading, St* st, bool* nearFlag, float* dist, float* scale, const int& style);   // 0xc2cac0
char F283d0(Ctx* ctx, Creature* c);   // 0xc283d0
void F28700(Ctx* ctx, Creature* c, St* st, Vector3* heading, float dist, float st20, float* speed);   // 0xc28700
float F29b10(Creature* c, Vector3* heading, Vector3* goal, float f10, float speed, float turn, int flag);   // 0xc29b10
float F29d80(Vector3* heading, float f10, float speed, float turn);   // 0xc29d80
char F28b40(Ctx* ctx, Creature* c, Vector3* dir, char f7c);   // 0xc28b40
void F29940(Creature* c);   // 0xc29940
void normalized_safe(Vector3* out, const Vector3* in);   // 0x449c20
char F41dd30(const Vector3* v, const Vector3* ref);   // 0x41dd30
Vector3* Vector3_Normalize(Vector3* out, const Vector3* in);   // 0x436ce0
// ---- items of slice s00c2d220 end

// @ 0x00c27d20
cActionCircle* cActionCircleMap::FindOrAdd(i32* pKey)
{
    cMapIterator it;
    Find(&it, (u32*)pKey);

    if (it.mpNode == mpBuckets[mnCount]) {
        cActionCircle temp;
        cMapRecord rec;
        cActionCircle* p = temp.FUN_00afba10();
        rec.mKey = (u32)*pKey;
        rec.mCircle.CopyFrom(p);
        Insert(&it, &rec, false);
        rec.mCircle.FUN_00afbad0();
        temp.FUN_00afbad0();
    }

    return (cActionCircle*)((u8*)it.mpNode + 4);
}

// @ 0x00c27db0
i32 cActionMapOwner::FindOrAddKey(i32 nKey)
{
    i32 k = nKey;
    return (i32)mMap.FindOrAdd(&k);
}

// @ 0x00c27dd0
void* cCreatureCitizen::FUN_00c27dd0(void* pObj)
{
    i32 nIndex = -1;
    float* pSrc = (float*)FUN_00c986d0(*(void**)((u8*)pObj + 0x10c), 0xd, &nIndex, this);
    if (nIndex < 0)
        return (void*)nIndex;

    i32 nKey = 0xd;
    cActionCircle* pRec = ((cActionMapOwner*)(*(void**)((u8*)pObj + 0x10c)))->mMap.FindOrAdd(&nKey);

    float fScale = ((cDispatchObject*)((u8*)this + 0xc0))->CallFloat(0x74);
    f32 cx = *(f32*)((u8*)pRec + 0x14);
    f32 cy = *(f32*)((u8*)pRec + 0x18);
    f32 cz = *(f32*)((u8*)pRec + 0x1c);
    f32 dx = pSrc[0] - cx;
    f32 dy = pSrc[1] - cy;
    f32 dz = pSrc[2] - cz;
    f32 fInv = 1.0f / sqrtf(dx * dx + (dy * dy + dz * dz) + 1e-08f);

    f32 fRadius = (*(f32*)((u8*)pRec + 0xc) + fScale) + 0.4f;
    f32 px = (fInv * dx) * fRadius + cx;
    f32 py = (fInv * dy) * fRadius + cy;
    f32 pz = (fInv * dz) * fRadius + cz;

    if (((pz - cz) * (pz - cz) + (px - cx) * (px - cx)) + (py - cy) * (py - cy) <
        (dz * dz + dy * dy) + dx * dx) {
        px = pSrc[0];
        py = pSrc[1];
        pz = pSrc[2];
    }

    f32 fx = -(fInv * dx);
    f32 fy = -(fInv * dy);
    f32 fz = -(fInv * dz);

    MoveToPointAndFacingAtSpeed(2, &px, &fx, 0.4f, 0.6f);
    return (void*)nIndex;
}

// @ 0x00c27ff0
u8 __cdecl FUN_00c27ff0(cActionCircle* pCircle)
{
    return *(u8*)((u8*)pCircle + 0x38) & 1;
}

// @ 0x00c28000
u8* __cdecl FUN_00c28000(u8* pBegin, u8* pEnd, u8* pOut, bool (__cdecl* pPred)(u8*))
{
    while (pBegin != pEnd) {
        if (!pPred(pBegin)) {
            *(cRecord3c*)pOut = *(cRecord3c*)pBegin;
            pOut += 0x3c;
        }
        pBegin += 0x3c;
    }
    return pOut;
}

// @ 0x00c28050
void __cdecl FUN_00c28050(float* p1, float* p2, char bUseModel, char bUseDir, float* p5, float* p6, float* p7)
{
    if (bUseModel != 0) {
        PlanetModel()->FUN_00b7e430(p5, 1);

        f32 dx = p5[0] - p1[0];
        f32 dy = p5[1] - p1[1];
        f32 dz = p5[2] - p1[2];
        f32 d = (p2[1] * dy + p2[0] * dx) + p2[2] * dz;

        f32 x = p5[0] - p2[0] * d;
        f32 y = p5[1] - p2[1] * d;
        f32 z = p5[2] - p2[2] * d;
        p6[0] = x;
        p6[1] = y;
        p6[2] = z;

        x -= p1[0];
        y -= p1[1];
        z -= p1[2];
        *p7 = sqrtf(x * x + (y * y + z * z));
        return;
    }

    if (bUseDir != 0) {
        f32 dx = p5[0] - p1[0];
        f32 dy = p5[1] - p1[1];
        f32 dz = p5[2] - p1[2];
        f32 d = (p2[0] * dx + p2[1] * dy) + p2[2] * dz;

        f32 x = p5[0] - p2[0] * d;
        f32 y = p5[1] - p2[1] * d;
        f32 z = p5[2] - p2[2] * d;
        p6[0] = x;
        p6[1] = y;
        p6[2] = z;

        x -= p1[0];
        y -= p1[1];
        z -= p1[2];
        *p7 = sqrtf(x * x + (y * y + z * z));
        return;
    }

    Vec3 local;
    PlanetModel()->FUN_00b816f0(&local, p5);
    p6[0] = local.x;
    p6[1] = local.y;
    p6[2] = local.z;
}

// @ 0x00c28290
void __cdecl FUN_00c28290(cCreatureBase* self, void* p2, void* p3)
{
    Vec3 pos;
    float* pPos = (float*)((cDispatchObject*)((u8*)self + 0xc0))->Call(0x2c);
    pos.x = pPos[0];
    pos.y = pPos[1];
    pos.z = pPos[2];

    char b137 = (char)self->m137;
    bool bFlag = (self->m110 & 0x1000) == 0x1000;
    void* pElem = FUN_00b532b0((u8*)self + 0xc0);
    bool bTest = (b137 != 0 && pElem != nullptr && *(i32*)((u8*)pElem + 0xcc) == 3);

    f32 fInv = 1.0f / sqrtf(pos.x * pos.x + (pos.y * pos.y + pos.z * pos.z) + 1e-08f);
    Vec3 dir;
    dir.x = fInv * pos.x;
    dir.y = fInv * pos.y;
    dir.z = fInv * pos.z;

    if (!bFlag) {
        if (b137 == 0)
            return;
        void* pMgr = FUN_00b3d310();
        if (*(i32*)((u8*)pMgr + 0x20) != 0)
            return;
    }

    FUN_00c28050(&pos.x, &dir.x, bFlag, bTest, (float*)p2, (float*)p2, (float*)p3);
    if (self->m25c != 0)
        FUN_00c28050(&pos.x, &dir.x, bFlag, bTest, (float*)&self->m250, (float*)&self->m250,
                     (float*)p3);
}

// @ 0x00c283d0
u8 __cdecl FUN_00c283d0(Vec3* pOut, cCreatureBase* self)
{
    u8 bResult = 0;
    void* pMode = GetCurrentGameMode();
    u32 nFlags = self->m330;
    bool bMode10 = (pMode == (void*)&DAT_01654c10);

    if ((nFlags & 0xb) == 0)
        return bResult;

    bResult = 1;
    void* pBody = (u8*)self + 0xc0;
    void* pField = ((cBodyObject*)pBody)->FUN_00c41ec0();
    float fLimit = *(float*)((u8*)pField + 0x6c);

    if ((nFlags & 2) != 0 && 2.0f < fLimit && !bMode10) {
        self->m330 = nFlags & 0xfffffffd;
        return 0;
    }
    if (30.0f < fLimit && !bMode10)
        return 0;

    pOut->x = g_168dd78.x;
    pOut->y = g_168dd78.y;
    pOut->z = g_168dd78.z;

    void* pClass = ((cDispatchObject*)self)->Call(0x20);
    if (pClass == (void*)&DAT_018eb45e) {
        if (self->FUN_00c0c2f0() != 2)
            return bResult;

        cCreatureBase* pCitizen = (cCreatureBase*)FUN_00ac80d0(self, (void*)&DAT_018eb45e);
        cCreatureList* pList = (cCreatureList*)pCitizen->FUN_00c04590();

        Vec3 v;
        float fDist;
        if ((nFlags & 0x10) == 0) {
            fDist = ((cDispatchObject*)pBody)->CallFloat(0x74);
            fDist = fDist + fDist;
            float* pPos = (float*)((cDispatchObject*)pBody)->Call(0x2c);
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
        }
        else {
            float* pPos = (float*)FUN_00c423c0(self);
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            fDist = ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74) +
                    *(float*)((u8*)pField + 0x20);
        }

        i32 nCount = (i32)(pList->mpEnd - pList->mpBegin);
        for (i32 i = 0; i < nCount; ++i) {
            cCreatureBase* pOther = pList->mpBegin[i];
            if (pOther == pCitizen)
                continue;
            float* pPos = (float*)((cDispatchObject*)((u8*)pOther + 0xc0))->Call(0x2c);
            float ox = pPos[0];
            float oy = pPos[1];
            float oz = pPos[2];
            float fOther = ((cDispatchObject*)((u8*)pOther + 0xc0))->CallFloat(0x74);
            float fSum = fOther + fDist;
            if ((v.z - oz) * (v.z - oz) + (v.y - oy) * (v.y - oy) +
                (v.x - ox) * (v.x - ox) < fSum * fSum)
                ((cOtherMgr*)((u8*)pOther + 0xb4c + 8))->FUN_00bc97f0(
                    (u32)0x2000000, 0, 5.0f, pCitizen);
        }
    }
    else if (pClass == (void*)&DAT_018eb4b7) {
        cCreatureBase* pCitizen = self;
        cTribe* pTribe = (cTribe*)pCitizen->GetTribe();
        if ((nFlags & 0x10) == 0) {
            float fDist = 2.0f * ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74);
            float* pPos = (float*)((cDispatchObject*)((u8*)pCitizen + 0xc0))->Call(0x2c);
            Vec3 v;
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            pTribe->FUN_00c8f540(&v, fDist, 0, (void*)0x2000000, (void*)0x40a00000, pCitizen);
        }
        else {
            float fDist = ((cDispatchObject*)((u8*)pCitizen + 0xc0))->CallFloat(0x74) +
                          *(float*)((u8*)pField + 0x20);
            float* pPos = (float*)FUN_00c423c0(pCitizen);
            Vec3 v;
            v.x = pPos[0];
            v.y = pPos[1];
            v.z = pPos[2];
            pTribe->FUN_00c8f540(&v, fDist, 0, (void*)0x2000000, (void*)0x40a00000, pCitizen);
        }
    }
    return bResult;
}

// @ 0x00c28700
void __cdecl FUN_00c28700(cCreatureBase* self, u32 nArg2, i32* pVec, u32 nArg4, f32 fA, f32 fB, f32* pOut)
{
    if (*pVec != pVec[1])
        return;

    f32 fDiff = fA - fB;
    void* pMgr = FUN_00b3d310();
    if (*(char*)((u8*)pMgr + 0x31) != 0) {
        f32 fT = fDiff / *(f32*)((u8*)self + 0x10);
        if (*pOut > fT)
            *pOut = fT;
        return;
    }

    f32 fVal = ((cDispatchObject*)((u8*)self + 0x14))->CallFloat(0xd4);
    f32 fBase = *(f32*)((u8*)self + 0x10);
    f32 fCur = *pOut;
    f32 fNew;
    if (fBase * fBase <= (fDiff / fVal) * 2.0f) {
        f32 fTemp = fDiff - fCur * fBase;
        f32 fClamped = (fTemp < 0.0f) ? 0.0f : fTemp;
        if ((fClamped * fVal) * 2.0f < fCur * fCur)
            fNew = sqrtf((fVal * fDiff + fVal * fDiff) + (fBase * fVal) * (fBase * fVal)) -
                   fBase * fVal;
        else
            fNew = fCur;
    }
    else {
        fNew = fDiff / fBase;
    }

    if (fNew < 1.0f)
        fNew = 1.0f;
    if (fCur <= fNew)
        fNew = fCur;
    *pOut = fNew;
}

// @ 0x00c28870
u8 __cdecl FUN_00c28870(Vec3* pOut, cCreatureBase* self, float* pPos, i32* pVec)
{
    if (*pVec != pVec[1])
        return 1;

    bool bFlag = false;
    if (self->Flag388()) {
        void* pMode = GetCurrentGameMode();
        if (pMode == (void*)&DAT_01654c04)
            bFlag = true;
        else {
            pMode = GetCurrentGameMode();
            if (pMode == (void*)&DAT_01654c05)
                bFlag = true;
        }
    }

    f32 fA = (f32)pVec[8];
    f32 fB = (f32)pVec[0x18];
    f32 fRadius = (fA + fB) + 100.0f;

    if (!bFlag && (self->m330 & 4) == 0) {
        f32 dx = (f32)pVec[5] - pPos[0];
        f32 dy = (f32)pVec[6] - pPos[1];
        f32 dz = (f32)pVec[7] - pPos[2];
        if (fRadius * fRadius < (dz * dz + dx * dx) + dy * dy) {
            i32 nField = pVec[0x17];
            pOut->x = 0.0f;
            pOut->y = 0.0f;
            pOut->z = 0.0f;

            void* pPlan = self->FUN_00c0b750();
            self->MoveToPointAtSpeedPathPlan(pPlan, pVec + 5, fA, fB, 0);
            void* pField = ((cBodyObject*)((u8*)self + 0xc0))->FUN_00c41ec0();
            *(i32*)((u8*)pField + 0x5c) = nField;
            *(i32*)((u8*)pField + 0x50) = pVec[0x14];
            *(i32*)((u8*)pField + 0x54) = pVec[0x15];
            *(i32*)((u8*)pField + 0x58) = pVec[0x16];
            return 0;
        }
    }
    return 1;
}

// @ 0x00c289b0
void __cdecl f_00c289b0(Timing_s00c289b0* timing, C_s00c289b0* self, Body_s00c289b0* body, char flag, float thresh)
{
	if (thresh < body->m68 && (*(unsigned char*)((char*)self + 0x330) & 0xb) == 0)
	{
		body->m6c = 0.0f;
		return;
	}

	float t = timing->step + body->m6c;
	body->m6c = t;
	if (t > 0.25f)
	{
		if ((self->m110 & 0x1000) == 0)
		{
			Vec3_s00c289b0 tmp;
			body->pos = *((Pm_s00c289b0*)F_PlanetModel())->Transform(&tmp, &body->pos);
		}

		if (body->m6c > 2.0f)
		{
			if (flag == '\0' || body->m5c != 3)
			{
				self->m330 |= 1;
				return;
			}

			void* bodyObj = (char*)self + 0xc0;
			float s = BodyFlt(bodyObj);
			Vec3_s00c289b0 p;
			p.x = body->pos.x + s * body->vel.x;
			p.y = body->pos.y + s * body->vel.y;
			p.z = body->pos.z + s * body->vel.z;
			Vec3_s00c289b0* bp = BodyPos(bodyObj);
			p.x -= bp->x;
			p.y -= bp->y;
			p.z -= bp->z;
			Vec3_s00c289b0 tmp2;
			body->vel = *F_normalized_safe(&tmp2, &p);
			self->m330 &= 0xfffffff4;
		}
	}
}

// @ 0x00c28b40
bool __cdecl f_00c28b40(Motion_s00c28b40* p1, C_s00c289b0* self, Vec3_s00c289b0* dir3, char param4)
{
	bool bVar3 = false;
	Pm_s00c289b0* pm = (Pm_s00c289b0*)F_PlanetModel();
	Vec3_s00c289b0* pfVar7 = BodyPos((char*)self + 0xc0);
	int iVar8 = self->FnC0C2F0();

	float* q = (float*)VtCall0(p1->obj14, 0x68);
	float fVar17 = q[0x14 / 4];
	float fVar1 = q[8 / 4];

	if (self->mB5e == 0 && (self->m110 & 0x1000) != 0)
	{
		bool c = self->Flag388();
		self->m2b0 = c ? 0 : 3;
		*(char*)(*(int*)((char*)self->mB54 + 0x17c) + 0x168c) = self->m137;
		return true;
	}

	if (self->m137 != 0)
		self->m2b0 = 0;

	if ((self->m110 & 0x1000) == 0)
	{
		int st = *(int*)((char*)F_GetTriggerMgr() + 0x2c);
		bool skip = (st == 1 || st == 2) || (iVar8 < 2 && self->mF90 == 0);
		if (skip)
		{
			if (param4 != 0)
				return !bVar3;
		}
		else
		{
			if (param4 != 0)
				return !bVar3;

			float len = sqrtf(pfVar7->x * pfVar7->x + pfVar7->y * pfVar7->y + pfVar7->z * pfVar7->z);
			float wh = pm->GetWaterHeight();
			float dist2 = 0.0f;
			float diff = len - wh;

			if (self->Flag388())
			{
				void* t = self->FnC0EE60();
				if (t)
				{
					void* a = VtCall0(t, 0x08);
					Vec3_s00c289b0* b = BodyPos(a);
					dist2 = sqrtf((b->y - pfVar7->y) * (b->y - pfVar7->y) +
					              ((b->z - pfVar7->z) * (b->z - pfVar7->z) +
					               (b->x - pfVar7->x) * (b->x - pfVar7->x)));
				}
			}

			void* g = F_b3d310();
			float f16 = (*(int*)((char*)g + 0x20) == 0) ? 1.0f : 10.0f;

			if (diff > f16 + dist2 + (fVar17 - fVar1))
			{
				float stp = p1->step;
				Vec3_s00c289b0 tmp;
				pm->RotateTo(&tmp, pfVar7);
				bool bVar2 = (dir3->y * tmp.y + dir3->z * tmp.z) + tmp.x * dir3->x > 0.3f;

				Vec3_s00c289b0 p;
				p.x = pfVar7->x + p1->v.x * stp;
				p.y = pfVar7->y + p1->v.y * stp;
				p.z = pfVar7->z + p1->v.z * stp;

				void* sph = *(void**)((char*)pm + 0x24);
				void* hit = VtCall0(sph, 0x0c);
				float lim = *(float*)((char*)hit + 0x4c);
				if (!(lim > 45.0f))
					lim = 45.0f;

				float fv = pm->HeightAt(&p);
				char* cls = (char*)VtCall0(self, 0x20);

				if (cls == &DAT_018eb45e)
				{
					if (fv > lim + 13.0f)
					{
						bVar3 = true;
						if (F_GetCurrentGameMode() != &DAT_01654c10)
							VtCallV0(p1->obj14, 0xec);
						p1->v.x = tmp.x * -30.0f;
						p1->v.y = tmp.y * -30.0f;
						p1->v.z = tmp.z * -30.0f;
					}
					else if (bVar2)
					{
						if (fv > lim + 10.0f)
						{
							bVar3 = true;
							if (F_GetCurrentGameMode() != &DAT_01654c10)
								VtCallV0(p1->obj14, 0xec);
							p1->v.x = 0.0f;
							p1->v.y = 0.0f;
							p1->v.z = 0.0f;
						}
						else if (lim < fv)
						{
							float sc = 1.0f - (fv - lim) / lim;
							p1->v.x *= sc;
							p1->v.y *= sc;
							p1->v.z *= sc;
						}
					}
				}
				else if (bVar2)
				{
					float sc;
					if (fv > lim + 13.0f)      sc = 0.1f;
					else if (fv > lim + 10.0f) sc = 0.25f;
					else if (fv > lim)         sc = 0.5f;
					else                       sc = -1.0f;
					if (sc >= 0.0f)
					{
						p1->v.x *= sc;
						p1->v.y *= sc;
						p1->v.z *= sc;
					}
				}
			}
		}
	}
	else
	{
		if (param4 != 0)
			return !bVar3;
	}

	if (self->m137 != 0)
	{
		if (p1->v.x != g_168dd78_s00c2_89b0.x || p1->v.y != g_168dd78_s00c2_89b0.y || p1->v.z != g_168dd78_s00c2_89b0.z)
		{
			float stp = p1->step;
			Vec3_s00c289b0 d;
			d.x = pfVar7->x + p1->v.x * stp;
			d.y = pfVar7->y + p1->v.y * stp;
			d.z = pfVar7->z + p1->v.z * stp;

			Vec3_s00c289b0 rt;
			Vec3_s00c289b0* r = pm->Transform(&rt, &d);
			Vec3_s00c289b0 dv;
			dv.x = r->x - pfVar7->x;
			dv.y = r->y - pfVar7->y;
			dv.z = r->z - pfVar7->z;

			Vec3_s00c289b0 nn;
			F_normalized_safe(&nn, &dv);

			float L = sqrtf(p1->v.x * p1->v.x + (p1->v.y * p1->v.y + p1->v.z * p1->v.z));
			p1->v.x = nn.x * L;
			p1->v.y = nn.y * L;
			p1->v.z = nn.z * L;
		}
	}
	return !bVar3;
}

// @ 0x00c290d0
float* C_s00c289b0::PathAverage(float* out, Path_s00c290d0* path, const float* inEAX)
{
	out[0] = inEAX[0];
	out[1] = inEAX[1];
	out[2] = inEAX[2];
	if (path->begin == path->end)
		return out;

	int* piVar4 = *(int**)(*(int*)((char*)this + 0xb54) + 0x17c);
	float fVar10 = *(float*)(*piVar4 + 0x370) * (float)piVar4[0x1c];
	Vec3_s00c289b0* pfVar5 = BodyPos((char*)this + 0xc0);

	Vec3_s00c289b0* pb = &path->base;
	float d0 = pfVar5->x - pb->x;
	float d1 = pfVar5->y - pb->y;
	float d2 = pfVar5->z - pb->z;
	float fVar11 = sqrtf(d0 * d0 + (d1 * d1 + d2 * d2));
	float fVar13 = 0.0f;
	if (fVar11 <= fVar10)
	{
		if (fVar10 * 0.2f <= fVar11)
		{
			if (fVar11 <= fVar10 * 0.8f)
				fVar13 = 1.0f;
			else
				fVar13 = (fVar10 - fVar11) / (fVar10 - fVar10 * 0.8f);
		}
		else
		{
			fVar13 = fVar11 / (fVar10 * 0.2f);
		}
		fVar13 = ((3.0f - fVar13 * 2.0f) * fVar13) * fVar13;
	}

	PathRec_s00c290d0* pfVar6 = path->begin;
	PathRec_s00c290d0* pfVar7 = path->begin;
	PathRec_s00c290d0* end = path->end;
	float fVar18 = pb->x * fVar13;
	float fVar17 = pb->y * fVar13;
	float fVar12 = pb->z * fVar13;
	if (pfVar6 != end)
	{
		unsigned uVar9 = 0;
		do
		{
			float e0 = pfVar7->p.x - pfVar6->p.x;
			float e1 = pfVar7->p.y - pfVar6->p.y;
			float e2 = pfVar7->p.z - pfVar6->p.z;
			fVar11 = sqrtf(e0 * e0 + (e1 * e1 + e2 * e2)) + fVar11;
			if (fVar11 > fVar10)
				break;
			float w = 0.0f;
			if (fVar11 <= fVar10)
			{
				if (fVar10 * 0.2f <= fVar11)
				{
					if (fVar11 <= fVar10 * 0.8f)
						w = 1.0f;
					else
						w = (fVar10 - fVar11) / (fVar10 - fVar10 * 0.8f);
				}
				else
				{
					w = fVar11 / (fVar10 * 0.2f);
				}
				w = ((3.0f - w * 2.0f) * w) * w;
			}
			fVar13 = w + fVar13;
			fVar18 = pfVar7->p.x * w + fVar18;
			fVar17 = pfVar7->p.y * w + fVar17;
			fVar12 = pfVar7->p.z * w + fVar12;
			pfVar6 = pfVar7;
			pfVar7++;
			uVar9++;
		} while (uVar9 < (unsigned)(path->end - path->begin));
	}

	if (fVar13 > 1e-06f)
	{
		fVar13 = 1.0f / fVar13;
		out[0] = fVar18 * fVar13 - pfVar5->x;
		out[1] = fVar17 * fVar13 - pfVar5->y;
		out[2] = fVar12 * fVar13 - pfVar5->z;
	}
	return out;
}

// @ 0x00c293f0
Vec4_s00c289b0* __cdecl f_00c293f0(Vec4_s00c289b0* out, void* obj, const Vec3_s00c289b0* dir)
{
	if (dir->x * dir->x + dir->y * dir->y + dir->z * dir->z > 0.0f)
	{
		Vec3_s00c289b0* p = (Vec3_s00c289b0*)VtCall0(obj, 0x2c);
		Vec3_s00c289b0 d;
		d.x = dir->x - p->x;
		d.y = dir->y - p->y;
		d.z = dir->z - p->z;
		float len = sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
		if (len > 1.52587890625e-05f)
		{
			float inv = 1.0f / len;
			Vec3_s00c289b0 n;
			n.x = d.x * inv;
			n.y = d.y * inv;
			n.z = d.z * inv;
			((Pm_s00c289b0*)F_PlanetModel())->BuildSurfaceOrientation(out, p, &n);
			return out;
		}
	}
	Vec4_s00c289b0* src = (Vec4_s00c289b0*)VtCall0(obj, 0x30);
	out->x = src->x;
	out->y = src->y;
	out->z = src->z;
	out->w = src->w;
	return out;
}

// @ 0x00c29530
float __cdecl f_00c29530(Vec3_s00c289b0* p1, Vec3_s00c289b0* p2, float param3)
{
	Vec3_s00c289b0 tmp;
	Vec3_s00c289b0* surf = ((Pm_s00c289b0*)F_PlanetModel())->TransformClamp(&tmp, p1);
	float fVar2 = sqrtf(p1->x * p1->x + (p1->y * p1->y + p1->z * p1->z)) -
	              sqrtf(surf->x * surf->x + (surf->y * surf->y + surf->z * surf->z));
	if (!(0.0f < fVar2))
		return 0.0f;

	float R = -((Pm_s00c289b0*)F_PlanetModel())->GetRadius();
	float inv = 1.0f / sqrtf((p1->x * p1->x + (p1->y * p1->y + p1->z * p1->z)) + 1e-08f);
	float n0 = p1->x * inv;
	float n1 = inv * p1->y;
	float n2 = inv * p1->z;
	float A = (p2->z * n2 + p2->y * n1) + p2->x * n0;
	float P = fVar2;
	if (0.0f < A)
	{
		P = ((A / R) * A) * 0.5f + fVar2;
		A = 0.0f;
	}
	if (0.0f < param3)
		R = R - param3;
	return (sqrtf(P * R + P * R + A * A) + A) / R;
}

// @ 0x00c296b0
C_s00c296b0* C_s00c296b0::Init()
{
	Chunk_s00c296b0* p = (Chunk_s00c296b0*)m_storage;
	for (int i = 7; i >= 0; i--)
	{
		p->Ctor();
		p++;
	}
	m_zero[0] = 0;
	m_zero[1] = 0;
	m_zero[2] = 0;
	m_zero[3] = 0;
	m_zero[4] = 0;
	m_zero[5] = 0;
	m_zero[6] = 0;
	m_zero[7] = 0;
	return this;
}

// @ 0x00c297d0
float __cdecl f_00c297d0(const Vec3_s00c289b0* a, const Vec3_s00c289b0* b, const Vec3_s00c289b0* c, const Vec3_s00c289b0* d)
{
	float dz = b->z - d->z;
	float dx = b->x - d->x;
	float dy = b->y - d->y;
	float len2 = (dx * dx + dz * dz) + dy * dy;
	if (len2 < 1.52587890625e-05f)
		return 0.0f;
	// x87, evaluated as ((a.x-c.x)*dx + (a.z-c.z)*dz) + (a.y-c.y)*dy
	return (-1.0f / len2) * (((a->x - c->x) * dx + (a->z - c->z) * dz) + (a->y - c->y) * dy);
}

// @ 0x00c29880
float __cdecl f_00c29880(const Vec3_s00c289b0* p1, const Vec3_s00c289b0* p2, const Vec3_s00c289b0* p3, const Vec3_s00c289b0* p4, float s)
{
	float fVar1 = (p1->z + p2->z * s) - (p3->z + p4->z * s);
	float fVar2 = (p1->y + p2->y * s) - (p3->y + p4->y * s);
	float fVar3 = (p1->x + p2->x * s) - (p3->x + p4->x * s);
	return sqrtf(fVar3 * fVar3 + (fVar2 * fVar2 + fVar1 * fVar1));
}

// @ 0x00c29940
void __cdecl f_00c29940(C_s00c289b0* self)
{
	bool b = (self->m110 & 0x1000) == 0x1000;
	self->SetFlagPair(b, 0x2775920e, 0x48021ef);
	if (b && self->mF90 != 0)
	{
		Eff_s00c289b0* e = (Eff_s00c289b0*)self->GetEffect(0x48021ef);
		if (e)
		{
			XformMsg_s00c289b0 x;
			x.Ctor();
			e->GetXform(&x);
			x.mScale = BodyFlt((char*)self + 0xc0);
			x.mCount++;
			e->SetXform(&x);
		}
	}
}

// @ 0x00c299e0
int ConstraintTable::remove(uint* keyPtr)
{
    int  before = count;
    ConstraintNode** slot = &buckets[*keyPtr % size];

    if (*slot == 0)
        goto done;

    // walk to the first node whose key matches (or to the end of the chain)
    while (*keyPtr != (*slot)->key && (*slot)->next != 0)
        slot = &(*slot)->next;

    if (*slot == 0)
        goto done;

    // unlink every consecutive node that carries this key
    while (*slot != 0 && *keyPtr == (*slot)->key) {
        ConstraintNode* node = *slot;
        *slot = node->next;

        uchar* p = (uchar*)node + 0x824;
        for (int i = 7; i >= 0; --i) {
            void* o = *(void**)(p - 4);
            p -= 4;
            if (o != 0)
                (*(void (__thiscall**)(void*))(*(int*)o + 4))(o);
        }

        uchar* q = (uchar*)node + 0x804;
        for (int i = 7; i >= 0; --i) {
            q -= 0x100;
            ((cNodeSub*)q)->Destroy();
        }

        operator_delete__(node);
        count--;
    }

done:
    return before - count;
}

// @ 0x00c29ab0
void* cOrientation::CopyFrom(const cOrientation* src)
{
    CopyBase(src);
    m_f0 = src->m_f0;
    m_f4 = src->m_f4;
    m_f8 = src->m_f8;
    m_fc = src->m_fc;
    return this;
}

// @ 0x00c29b00
int __cdecl FUN_00c29b00(uint key)
{
    return g_1572460.remove(&key);
}

// @ 0x00c29b10
float __cdecl FUN_00c29b10(cOrientation* obj, float* dir, int param3, float param4, float param5, float param6, char param7)
{
    uchar* sub = obj ? (uchar*)obj + 0xc0 : 0;

    int local[4];                                   // 16-byte working object
    FUN_00c293f0(local, sub, param3);

    cOrientSub* s = (cOrientSub*)((uchar*)obj + 0xc0);
    void* vt = s->vtbl;

    bool b = ((bool (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x48)))(s);
    if (!b && (uint)obj->GetSubCount() < 2) {
        ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, local);
        return param5;
    }

    float ref[4];
    float* pf = FUN_0059aed0(ref, &g_168de1c, local);

    float dot = (dir[2] * pf[2] + dir[1] * pf[1]) + dir[0] * pf[0];
    float d = dot;
    if (d > g_1485720) d = g_1485720;      // 1.0f
    if (d < g_13eb1bc) d = g_13eb1bc;      // -1.0f

    float zero = 0.0f;
    float* chosen = &zero;
    if (d > zero)
        chosen = &d;
    float rate = param5 * *chosen;

    float a = (float)acos(d);                        // arg passed in st0 (_CIacos)

    uint bits = *(uint*)&a;
    if ((bits & 0x7fffffff) != 0 && 0x7effffff < ((bits - 0x800000u) & 0x7f800000))
        return rate;

    if (zero < a) {
        float speed;
        if ((g_1572480 != 0 && param7 != 0) || a <= g_1471064) {
            speed = (param4 * param6) * g_1470f1c;
        } else {
            speed = (param4 * param6) / a;
        }
        if (speed > g_1485720)
            speed = g_1485720;

        void* q = ((void* (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x30)))(s);
        float* r = FUN_005b2500(&ref, q, local, speed);
        float quat[4];
        quat[0] = r[0];
        quat[1] = r[1];
        quat[2] = r[2];
        quat[3] = r[3];

        if (FUN_00b3d550(quat))
            ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, quat);
    }
    return rate;
}

// @ 0x00c29d80
void __cdecl FUN_00c29d80(cOrientation* self, float* dir, float param2, float param3, float param4)
{
    cOrientation* obj = self;
    uchar* sub = obj ? (uchar*)obj + 0xc0 : 0;

    float local[8];
    FUN_00c293f0(local, sub, (int)dir);

    cOrientSub* s = (cOrientSub*)((uchar*)obj + 0xc0);
    void* vt = s->vtbl;

    bool b = ((bool (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x48)))(s);
    if (!b && (uint)obj->GetSubCount() < 2) {
        ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, local);
        return;
    }

    float ref[4];
    float* pf = FUN_0059aed0(ref, &g_168de1c, local);

    float f0 = pf[0];
    float f1 = pf[1];
    float f2 = pf[2];

    float dot = (dir[0] * f0 + dir[2] * f2) + dir[1] * f1;
    if (dot <= g_13eb1bc)
        dot = g_13eb1bc;
    if (g_1485720 <= dot)
        dot = g_1485720;

    uint dbits = *(uint*)&dot;
    if ((dbits & 0x7fffffff) != 0 && 0x7effffff < ((dbits - 0x800000u) & 0x7f800000))
        return;

    float a = (float)acos(dot);
    uint abits = *(uint*)&a;
    if ((abits & 0x7fffffff) != 0 && 0x7effffff < ((abits - 0x800000u) & 0x7f800000))
        return;

    float cx = dir[2] * f1 - dir[1] * f2;
    float cy = dir[0] * f2 - dir[2] * f0;
    float cz = dir[1] * f0 - dir[0] * f1;

    float* axis = ((float* (__thiscall*)(void*))(*(void**)((uchar*)vt + 0x2c)))(s);
    if ((axis[2] * cz + axis[1] * cy) + axis[0] * cx < 0.0f)
        a = -a;

    if (fabsf(a) < 1e-6f)
        return;

    float rate  = obj->m_2ac;
    float scale = g_1572484 * param4;                 // 1.5f * dt
    float extra = 0.0f;
    if (1e-6f < param4) {
        float sign = g_168de28;
        if (rate <= (g_1572420 - a) * scale) {
            if ((-a - g_1572420) * scale <= rate)
                goto step;
            sign = -g_168de28;
        }
        *(uint*)&local[0] ^= 0x80000000;
        *(uint*)&local[1] ^= 0x80000000;
        *(uint*)&local[2] ^= 0x80000000;
        *(uint*)&local[3] ^= 0x80000000;
        extra = sign;
    }
step:
    {
        float d = a - extra;
        if (1e-6f <= fabsf(d)) {
            void* fn = *(void**)((uchar*)vt + 0x30);
            float w = (d * scale + rate) * param2;
            float e = (float)exp(-(scale * param2));
            obj->m_2ac = (rate - w * scale) * e;

            float* q = ((float* (__thiscall*)(void*))fn)(s);
            float cur[4];
            cur[0] = q[0];
            cur[1] = q[1];
            cur[2] = q[2];
            cur[3] = q[3];

            float out[8];
            FUN_005b26f0(out, cur, local, (a - ((w + d) * e + extra)) / d);

            if (FUN_00b3d550(out))
                ((void (__thiscall*)(void*, void*))(*(void**)((uchar*)vt + 0x3c)))(s, out);
        }
    }
}

// @ 0x00c2b030
Value* Value::CopyFrom(const unsigned* key, TraceCache* src)
{
	mKey = *key;
	// the helper walks byte offsets: the eight hit records (stride 0x100), then the eight object slots
	char*       pDst = (char*)&mValue;
	const char* pSrc = (const char*)src;
	FUN_00406540(pDst, pSrc, 0x100, 8, (void*)0x00c29ab0);
	FUN_00406540(pDst + 0x800, pSrc + 0x800, 4, 8, (void*)0x00ac8980);
	return this;
}

// @ 0x00c2b080
TraceCache* Ht::FindOrInsert(const unsigned* key)
{
	// The "already present" flag is passed through the first slot of the insert result: the original
	// stores it as a byte and reloads it as a dword, so the two share the slot.
	union InsertSlot
	{
		InsertResult res;        // +0x00
		unsigned     flags;      // +0x00 (low byte: the flag)
		bool         bExisting;  // +0x00
	} out;
	TraceCache temp;
	Value      value;

	Find(&out.res, key);
	if (out.res.mpNode != mpBuckets[mBucketCount])
		return &out.res.mpNode->mValue;

	Value* pValue = value.CopyFrom(key, temp.Init());
	out.bExisting = false;
	Insert(&out.res, pValue, out.flags);
	value.mValue.Destroy();
	temp.Destroy();
	return &out.res.mpNode->mValue;
}

// @ 0x00c2b110
TraceCache* __cdecl FUN_00c2b110(unsigned key)
{
	Ht* ht = (Ht*)0x01572460;
	Iter it;

	ht->Find(&it, &key);
	if (it.mpNode == ht->mpBuckets[ht->mBucketCount])
	{
		TraceCache* cache = ht->FindOrInsert(&key);
		FUN_00cadb50(cache);
		return cache;
	}
	return &it.mpNode->mValue;
}

// @ 0x00c2d220
void __stdcall F00c2d220(Ctx* ctx)
{
    Creature* c = ctx->obj ? (Creature*)ctx->obj->Query(0xce9f6639) : 0;
    Creature* cc = c;
    if (!c || c->GetType() != 0x18eb45e)
        cc = 0;

    uint8_t flagA = F(uint8_t, c, 0x137);
    bool flagB = (F(unsigned, c, 0x110) & 0x1000) == 0x1000;
    St* st = ctx->obj->GetState();
    bool isMode = GetCurrentGameMode_s00c2_d220() == 0x1654c10;

    if (!flagA) {
        if (!flagB) {
            F2a190(ctx, c); // 0x00c2a190
            return;
        }
        if (TestBit(F(unsigned, c, 0xb58), 9) && st->mode == 0 && !g_169e381) {
            Vector3* v = LO->GetVelocity();
            ctx->out = *v;
            return;
        }
    }

    ctx->obj->GetVelocity();
    int style = c->GetStyle();
    Vector3* pp = ctx->obj->GetPosition();
    Vector3 pos;
    pos.x = pp->x; pos.y = pp->y; pos.z = pp->z;
    float inv = 1.0f / (float)sqrt(pos.x * pos.x + pos.z * pos.z + pos.y * pos.y + 1e-8f);
    Vector3 up;
    up.x = inv * pos.x; up.y = inv * pos.y; up.z = inv * pos.z;
    Vector3 heading;
    ctx->obj->GetHeading(&heading);
    float speed = ctx->obj->GetDesiredSpeed();
    float turn = F(float, ctx->obj, 0x1e8);
    float st20 = st->f20;
    bool isMode0 = st->mode == 0;
    float dist;
    if (isMode0) {
        dist = 0.0f;
    } else {
        float dx = pos.x - st->pos.x;
        float dy = pos.y - st->pos.y;
        float dz = pos.z - st->pos.z;
        dist = (float)sqrt(dx * dx + dz * dz + dy * dy);
    }
    bool arrived;
    bool near_;
    if (ctx->obj->IsNearGoal() && !(st->flags70 & 4)) near_ = true; else near_ = false;
    arrived = near_;
    bool f13;
    if (st->mode == 3 || F(uint8_t, c, 0xb5c)) f13 = false; else f13 = true;
    float scale = 1.0f;
    F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x168c) = 1;
    Info532b0* x532 = F0b532b0(LO);
    bool f7c;
    if (flagA && x532 && x532->fcc == 3) f7c = true; else f7c = false;
    if (!isMode0)
        F28290(c, &st->pos, &dist);
    ((Sub15b8*)(F(char*, F(Anim*, c, 0xb54), 0x17c) + 0x15b8))->F9ce740(0.0f);
    if (F(unsigned, c, 0x330) & 4) {
        ctx->out.x = 0.0f; ctx->out.y = 0.0f; ctx->out.z = 0.0f;
        return;
    }
    if (arrived) {
        F(unsigned, c, 0x330) &= 0xfffffff4;
        goto L71a;
    }
    if (st->mode == 0)
        goto L71a;

    {
        bool f12 = F(float, ctx->obj, 0x1a0) != 0.0f;
        near_ = ctx->obj->Within(dist * dist, st20);
        if (f12) {
            F0cadb50(F2b110(c));
            F(unsigned, c, 0x330) &= 0xfffffff4;
            if (!F28870(ctx, c, &pos, st))
                return;
        }
        arrived = f12;
        if (!f12) {
            float lim;
            switch (style) {
            case 0: lim = 2.0f; break;
            case 1: lim = 1.0f; break;
            case 2: lim = 0.5f; break;
            default: lim = FLT_MAX; break;
            }
            float cur = F(float, ctx->obj, 0x1a0);
            if (cur > lim) {
                arrived = true;
                F(float, ctx->obj, 0x1a0) = cur - lim;
            }
        } else {
            if (style >= 0 && style <= 1)
                arrived = F(uint8_t, c, 0xf90) != 0;
        }
        F289b0(ctx, c, st, near_, dist);
        if (near_) {
            StEntry* b = st->begin;
            if (b == st->end) {
                arrived = false;
                if (st->mode != 3 && st->mode != 2)
                    speed = 0.0f;
                goto L66c;
            }
            if (st->flags4c & 1)
                arrived = true;
            memcpy(&st->pos, b, sizeof(StEntry));
            st->F47520(b);
            F28290(c, &st->pos, &dist);
            near_ = false;
        }
        if (!arrived)
            goto L66c;
        if (TestBit(F(unsigned, c, 0xb58), 9)) {
            if (g_169e381 || g_169e37e || isMode) {
                arrived = false;
                goto L66c;
            }
        }
        if (f12)
            goto L66c;
        if (!(st->flags4c & 1))
            goto L66c;
        arrived = F2c7b0(c, st, &heading, &scale, style) != 0;
        goto L693;
    L66c:
        {
            Info2b110* r = F2b110(c);
            if (r->f4 != 0 && 1.0f > r->f8)
                scale = r->f8;
        }
    L693:
        if (arrived)
            F2cac0(c, &heading, st, &near_, &dist, &scale, style);
        if (F283d0(ctx, c))
            return;
        if (!near_ && style > 0 && st->mode != 2 && !(st->flags70 & 1))
            F28700(ctx, c, st, &heading, dist, st20, &speed);
        st->f68 = dist;
    }

L71a:
    Vector3 dir;
    Vector3 goal;
    Vector3 tmp;
    float retSpeed;
    bool reached;
    ctx->obj->UpdateSteeringForMovementStyle();
    ctx->obj->F44080(&dir);
    {
        float len = (float)sqrt(dir.y * dir.y + dir.z * dir.z + dir.x * dir.x);
        if (len >= 1.5258789e-05f) {
            if (len > 1.0f || len < 1.0f) {
                float s = 1.0f / len;
                dir.x = s * dir.x;
                dir.y = s * dir.y;
                dir.z = s * dir.z;
            }
        } else {
            dir.x = heading.x; dir.y = heading.y; dir.z = heading.z;
        }
    }
    uint8_t bit9 = (uint8_t)TestBit(F(unsigned, c, 0xb58), 9);
    if (st->mode == 0) {
        speed = 0.0f;
        goto L9d9;
    }
    if (speed > 0.0f && (!near_ || !f13) && cc && F(uint8_t, cc, 0xf90)) {
        void* animPtr = 0;
        int animId;
        F(Anim*, cc, 0xb54)->Q58(&animId, 0, 0, &animPtr);
        if (F(Anim*, cc, 0xb54)->IsOrientStartAnim(animId)) {
            float num = 0.0f;
            float den = 0.0f;
            if (!F(Anim*, cc, 0xb54)->Q5c(animPtr, &den, &num)) {
                turn = 0.0f;
                speed = 0.0f;
            } else {
                float t = num / den;
                t = (t > 0.0f) ? t : 0.0f;
                t = (t < 1.0f) ? t : 1.0f;
                speed = t * speed;
                turn = t * turn;
            }
        }
    }
L9d9:
    float maxDist;
    {
        float cap = 20.0f;
        float* p = LO->F421f0() + 3;
        const float* m = (cap > *p) ? &cap : p;
        maxDist = *m;
    }
    reached = false;
    if (st->mode == 4) {
        Vector3* p = LO->GetPosition();
        goal.x = p->x + st->dir.x;
        goal.y = p->y + st->dir.y;
        goal.z = p->z + st->dir.z;
    } else if (F(uint8_t, c, 0xb5c) && c->F0ee60()) {
        if (!isMode) {
            Obj2* o2 = c->F0ee60()->Get8();
            Vector3* p2 = o2->GetPosition();
            Vector3* mp = LO->GetPosition();
            goal.x = mp->x - p2->x;
            goal.y = mp->y - p2->y;
            goal.z = mp->z - p2->z;
            Obj3* o3 = (Obj3*)c->F0ee60()->Get8();
            float r1 = o3->V74();
            float r0 = LO->GetRadius();
            float d = maxDist - (r0 + r1);
            float t = (0.0f > d) ? 0.0f : d;
            if (t * t <= goal.x * goal.x + goal.z * goal.z + goal.y * goal.y)
                goto Lbaa;
        }
        {
            Vector3* gp = c->F0ee60()->Get8()->GetPosition();
            goal = *gp;
            reached = true;
        }
    } else {
    Lbaa:
        if (near_) {
            float r = LO->GetRadius();
            goal.x = st->pos.x + dir.x * r;
            goal.y = st->pos.y + r * dir.y;
            goal.z = st->pos.z + r * dir.z;
        } else if (F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x2d5)) {
            Vector3* r = c->F290d0(&tmp, st);
            goal.x = r->x + pos.x;
            goal.y = r->y + pos.y;
            goal.z = r->z + pos.z;
        } else {
            st20 = LO->GetRadius() + st20;
            if (st->begin != st->end && !(dist > st20)) {
                Vector3* b = (Vector3*)st->begin;
                tmp.x = b->x - st->pos.x;
                tmp.y = b->y - st->pos.y;
                tmp.z = b->z - st->pos.z;
                normalized_safe(&goal, &tmp);
                float t = dist / st20;
                float s = (t * t) * 3.0f - ((t * t) * t) * 2.0f;
                float s1 = 1.0f - s;
                goal.x = (s * dir.x + pos.x) + goal.x * s1;
                goal.y = (s * dir.y + pos.y) + goal.y * s1;
                goal.z = (s * dir.z + pos.z) + goal.z * s1;
            } else {
                goal.x = dir.x + pos.x;
                goal.y = dir.y + pos.y;
                goal.z = dir.z + pos.z;
            }
        }
    }

    if (!bit9) {
        if (!F(uint8_t, F(char*, F(Anim*, c, 0xb54), 0x17c), 0x2d5))
            retSpeed = F29b10(c, &heading, &goal, ctx->f10, speed, turn, 0);
        else
            retSpeed = F29d80(&heading, ctx->f10, speed, turn);
    } else {
        retSpeed = speed;
        if (cc) {
            bool ok = true;
            if (reached && !g_169e37e) {
                if (!cc->F0ee60() || !F(uint8_t, cc, 0xb5c))
                    ok = false;
            }
            if (ok) {
                if (g_169e381 && g_169e37f && !reached) {
                    float dot = heading.x * g_169e388 + heading.y * g_169e38c + heading.z * g_169e390;
                    if (dot > 0.0f) {
                        goal.x = pos.x + g_169e388;
                        goal.y = g_169e38c + pos.y;
                        goal.z = pos.z + g_169e390;
                    } else {
                        goal.x = pos.x - g_169e388;
                        goal.y = pos.y - g_169e38c;
                        goal.z = pos.z - g_169e390;
                    }
                }
                retSpeed = F29b10(c, &heading, &goal, ctx->f10, speed, turn, bit9);
            }
        }
    }

    if (retSpeed > 0.0f || (bit9 && g_169e384 > 0.0f)) {
        if (!bit9 || !g_169e381) {
            ctx->out.x = dir.x * speed;
            ctx->out.y = dir.y * speed;
            ctx->out.z = dir.z * speed;
        } else if (GetCurrentGameMode_s00c2_d220() == 0x1654c05) {
            const float* m = (speed > g_169e384) ? &g_169e384 : &speed;
            ctx->out.x = *m * dir.x;
            ctx->out.y = *m * dir.y;
            ctx->out.z = *m * dir.z;
        } else {
            ctx->out.x = g_169e388 * g_169e384;
            ctx->out.y = g_169e38c * g_169e384;
            ctx->out.z = g_169e390 * g_169e384;
        }
    } else {
        ctx->out.y = 0.0f;
        ctx->out.z = 0.0f;
        ctx->out.x = 0.0f;
    }

    if (!F28b40(ctx, c, &dir, f7c))
        return;
    F29940(c);
    if (near_) {
        bool doReset = f13;
        if (!doReset) {
            tmp.x = goal.x - st->pos.x;
            tmp.y = goal.y - st->pos.y;
            tmp.z = goal.z - st->pos.z;
            normalized_safe(&goal, &tmp);
            float dot = up.x * goal.x + goal.z * up.z + goal.y * up.y;
            tmp.x = goal.x - up.x * dot;
            tmp.y = goal.y - dot * up.y;
            tmp.z = goal.z - dot * up.z;
            if (F41dd30(&tmp, &g_168dd78_s00c2_d220)) {
                Vector3* r = Vector3_Normalize(&heading, &tmp);
                goal = *r;
            }
            Vector3 hd;
            Vector3* h = ctx->obj->GetHeading(&hd);
            float dot2 = h->y * goal.y + h->z * goal.z + h->x * goal.x;
            doReset = dot2 > st->f64;
            if (!doReset) {
                Vector3* sp = &ctx->obj->GetState()->pos;
                sp->x = pos.x; sp->y = pos.y; sp->z = pos.z;
                if (F(int, ctx->obj, 0x1f0) == 0 && F41dd30(&pos, &g_168dd78_s00c2_d220)) {
                    float d3 = st->dir.z * up.z + st->dir.y * up.y + up.x * st->dir.x;
                    tmp.x = st->dir.x - up.x * d3;
                    tmp.y = st->dir.y - d3 * up.y;
                    tmp.z = st->dir.z - d3 * up.z;
                    if (F41dd30(&tmp, &g_168dd78_s00c2_d220)) {
                        Vector3* r = Vector3_Normalize(&heading, &tmp);
                        st->dir.x = r->x; st->dir.y = r->y; st->dir.z = r->z;
                    }
                }
            }
        }
        if (doReset) {
            Loco* o = ctx->obj;
            {
                ArrObj a;
                o->V_dc(&a);
            }
            ctx->obj->V_c4(0.0f, 1);
        }
        ctx->out.z = 0.0f;
        ctx->out.y = 0.0f;
        ctx->out.x = 0.0f;
    }
    if (1.0f > scale) {
        ctx->out.x = ctx->out.x * scale;
        ctx->out.y = scale * ctx->out.y;
        ctx->out.z = ctx->out.z * scale;
    }
}
