// src/game/SPGonzago/_at_00b60000.cpp -- migrated from slice(s) s00b6e3d0, s00b6d3c0, s00b6baf0, s00b6b1a0, s00b6a420, s00b68720, s00b677e0, s00b66aa0, s00b65b10, s00b64470, s00b634d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPTimer.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cVarListSerializer.h"
#include "SP/cModelInstance.h"
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>
#include "cSPUILayout.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyManager.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cCity.h"
#include "SP/cCivData.h"
#include "SP/cEmpire.h"
#include "SP/cStringTokenTranslator.h"

// unnamed retail callees and globals (address in the comment)
extern char gSig2;   // 0x0156ad88
extern "C" __declspec(dllimport) unsigned __stdcall IsDlgButtonChecked(void* hwnd, int id);
extern "C" __declspec(dllimport) void     __stdcall CheckDlgButton(void* hwnd, int id, unsigned check);
extern void* gVtbl63BD0;   // 0x0145e9a8
extern void* gMapEmpty;    // 0x0154df28

// ---- items of slice s00b634d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  uint;
typedef unsigned char uchar;
void __cdecl opdel_check(void* p);   // 0x00f47380 operator delete (eastl)
struct CSBase {
    void Init(void (*cb)());
    char IsRunning();            // 0x00feba90
    long long GetElapsedTime();  // 0x00bc3190
};
struct cGonzagoTimer : CSBase {
    char  pad04[4];
    long long mElapsed;  // +0x08
    long long mBase;     // +0x10
    int   mPad18;        // +0x18
    void* mGetMs;        // +0x1c
    cGonzagoTimer();
    ~cGonzagoTimer();
    void Write(void* ser);          // 0x00b638d0
    uchar Read(void* ser);          // 0x00b63930
    void AddElapsed(int v);         // 0x00b638c0
};
struct cVarListSerializer {
    char data[0xa14];
    cVarListSerializer(void* obj, void* info, unsigned sig);  // 0x00692f90
    void Serialize(void* ser);                                 // 0x00692900
    uchar SerializeB(void* ser);                               // 0x00693e10
};
extern char gSig2;   // 0x0156ad88
extern "C" __declspec(dllimport) unsigned __stdcall IsDlgButtonChecked(void* hwnd, int id);
extern "C" __declspec(dllimport) void     __stdcall CheckDlgButton(void* hwnd, int id, unsigned check);
struct WndObj { char pad[4]; void* hwnd; void FSet(int id, char check); void FGet(int id, uchar* out); };
struct MapU32 {
    char pad0[4];
    uint* mBuckets;   // +0x04
    uint  mCount;     // +0x08
    uchar mFlag;      // +0x0c
    void DoAllocateBuckets(uint a, uint b);   // 0x00693230 (thiscall)
};
struct Obj63BD0 {
    void* vt;                 // +0x00
    char  pad04[0x1118];
    MapU32 mapA;              // +0x1118
    MapU32 mapB;              // +0x1138
    void Init();              // 0x00b63bd0
};
extern void* gVtbl63BD0;   // 0x0145e9a8
extern void* gMapEmpty;    // 0x0154df28
struct Obj63B60 { void F(); };
struct Obj63A20 { uchar F(void* p); };                      // 0x00b63a20
struct Obj63C70 { void F(void* menu, int x, int y, int w, int h, void* text); };  // 0x00b63c70
struct Obj63D50 { void F(void* menu, int x, int y, int w, int h, void* text); };  // 0x00b63d50
// ---- items of slice s00b634d0 end

// ---- items of slice s00b64470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
void operator_delete__(void* p);   // 0x00f47380
struct cSPTransform_s00b6_4470 { uint8_t d[0x38]; };
struct MeshGroup {
    virtual void* Destroy(int flag);
    long mRefCount;
};
struct MGRefExt {
    MeshGroup* p;
    MGRefExt() : p(0) {}
    ~MGRefExt();                                   // 0x00472520
};
struct MGRef {
    MeshGroup* p;
    MGRef() : p(0) {}
    MGRef& operator=(const MGRefExt& o);           // 0x006df280 (AddRef new, Release old)
    void AssignRefPtr(const MGRef& src);           // 0x006df280 (AddRef src, Release old)
    __forceinline void Reset()
    {
        MeshGroup* g = p;
        if (g) {
            p = 0;
            if (_InterlockedDecrement(&g->mRefCount) == 0) {
                _InterlockedExchange(&g->mRefCount, 1);
                g->Destroy(1);
            }
        }
    }
    __forceinline ~MGRef()
    {
        MeshGroup* g = p;
        if (g) {
            long n = _InterlockedExchangeAdd(&g->mRefCount, -1) - 1;
            if (n == 0) {
                _InterlockedExchange(&g->mRefCount, 1);
                g->Destroy(1);
            }
        }
    }
};
struct RefVec3 {
    MGRef* mpBegin;
    MGRef* mpEnd;
    MGRef* mpCap;
    void push_back(const MGRef& r);                // 0x0041ef20
    void DestroyRange(MGRef* first, MGRef* last);  // 0x004243e0
    ~RefVec3()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
struct cModelInstance {
    bool GetMeshes(void* out);                                // 0x0073EB90 (fills a RefVec3)
};
void FUN_00734d00(const cSPTransform_s00b6_4470* xf, MeshGroup* group);  // 0x00734d00
void FUN_00b64390(MeshGroup* group, int* numVerts, int* numTris);      // 0x00b64390
// ---- items of slice s00b64470 end

// ---- items of slice s00b65b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float hkReal;
class __declspec(align(16)) hkVector4_s00b6_5b10 {
public:
    hkReal x, y, z, w;
    hkVector4_s00b6_5b10() {}
    hkVector4_s00b6_5b10(const hkVector4_s00b6_5b10& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    void operator=(const hkVector4_s00b6_5b10& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void setTransformedPos(const class hkTransform_s00b6_5b10& t, const hkVector4_s00b6_5b10& v);          // 0x01081360
    void setTransformedInversePos(const class hkTransform_s00b6_5b10& t, const hkVector4_s00b6_5b10& v);   // 0x010813d0
};
class hkTransform_s00b6_5b10 {
public:
    hkVector4_s00b6_5b10 m_col0, m_col1, m_col2, m_translation;
};
class hkBool_s00b6_5b10 {
public:
    hkBool_s00b6_5b10() {}
    hkBool_s00b6_5b10(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};
extern const hkVector4_s00b6_5b10 g_hkQuadRealMinusHalf;     // 0x0149d620 (-0.5 x4)
class hkQuaternion_s00b6_5b10 { public:
    hkVector4_s00b6_5b10 m_vec;
};
static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }
static __forceinline void rotateByInverseQuat(hkVector4_s00b6_5b10& out, const hkQuaternion_s00b6_5b10& q, const hkVector4_s00b6_5b10& v)
{
    const hkReal qw = q.m_vec.w;
    const hkReal q2 = qw * qw;
    hkVector4_s00b6_5b10 ret = g_hkQuadRealMinusHalf;
    ret.x = (ret.x + q2) * v.x;
    ret.y = (ret.y + q2) * v.y;
    ret.z = (ret.z + q2) * v.z;
    ret.w = (ret.w + q2) * v.w;
    const hkReal dot = (v.y * q.m_vec.y + v.z * q.m_vec.z) + q.m_vec.x * v.x;
    ret.x += q.m_vec.x * dot;
    ret.y += q.m_vec.y * dot;
    ret.z += q.m_vec.z * dot;
    ret.w += q.m_vec.w * dot;
    hkVector4_s00b6_5b10 c;
    c.x = v.y * q.m_vec.z - v.z * q.m_vec.y;
    c.y = v.z * q.m_vec.x - q.m_vec.z * v.x;
    c.z = q.m_vec.y * v.x - v.y * q.m_vec.x;
    c.w = 0.0f;
    ret.x += c.x * qw;
    ret.y += c.y * qw;
    ret.z += c.z * qw;
    ret.w += c.w * qw;
    out.x = ret.x * 2.0f; out.y = ret.y * 2.0f; out.z = ret.z * 2.0f; out.w = ret.w * 2.0f;
}
static __forceinline void rotateByQuat(hkVector4_s00b6_5b10& out, const hkQuaternion_s00b6_5b10& q, const hkVector4_s00b6_5b10& v)
{
    const hkReal qw = q.m_vec.w;
    const hkReal q2 = qw * qw;
    hkVector4_s00b6_5b10 ret = g_hkQuadRealMinusHalf;
    ret.x = (ret.x + q2) * v.x;
    ret.y = (ret.y + q2) * v.y;
    ret.z = (ret.z + q2) * v.z;
    ret.w = (ret.w + q2) * v.w;
    const hkReal dot = (q.m_vec.x * v.x + v.y * q.m_vec.y) + v.z * q.m_vec.z;
    ret.x += q.m_vec.x * dot;
    ret.y += q.m_vec.y * dot;
    ret.z += q.m_vec.z * dot;
    ret.w += q.m_vec.w * dot;
    hkVector4_s00b6_5b10 c;
    c.x = v.z * q.m_vec.y - v.y * q.m_vec.z;
    c.y = q.m_vec.z * v.x - v.z * q.m_vec.x;
    c.z = v.y * q.m_vec.x - q.m_vec.y * v.x;
    c.w = 0.0f;
    ret.x += c.x * qw;
    ret.y += c.y * qw;
    ret.z += c.z * qw;
    ret.w += c.w * qw;
    out.x = ret.x * 2.0f; out.y = ret.y * 2.0f; out.z = ret.z * 2.0f; out.w = ret.w * 2.0f;
}
struct hkShapeRayCastInput {
    hkVector4_s00b6_5b10 m_from;
    hkVector4_s00b6_5b10 m_to;
    uint32_t m_filterInfo;                         // +0x20
    const void* m_rayShapeCollectionFilter;        // +0x24
};
struct hkShapeRayCastOutput {
    hkVector4_s00b6_5b10 m_normal;
    int m_extraInfo;
    hkReal m_hitFraction;
    hkShapeRayCastOutput() : m_hitFraction(1.0f) {}
};
struct hkWorldRayCastInput {
    hkVector4_s00b6_5b10 m_from;
    hkVector4_s00b6_5b10 m_to;
    bool m_enableShapeCollectionFilter;            // +0x20
    uint32_t m_filterInfo;                         // +0x24
};
struct hkWorldRayCastOutput : hkShapeRayCastOutput {
    const class hkCollidable_s00b6_5b10* m_rootCollidable;
    hkWorldRayCastOutput() : m_rootCollidable(0) {}
};
class hkRayHitCollector { public:
    hkReal m_earlyOutHitFraction;
    hkRayHitCollector() : m_earlyOutHitFraction(1.0f) {}
};
class hkClosestRayHitCollector : public hkRayHitCollector { public:
    virtual void addRayHit(const hkShapeRayCastOutput& hitInfo);   // vtable 0x01464944
    hkWorldRayCastOutput m_rayHit;
};
class hkShape_s00b6_5b10 { public:
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual hkBool_s00b6_5b10 castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // slot 5
};
struct hkPropertyValue_s00b6_5b10 {
    uint32_t type, value;
    hkPropertyValue_s00b6_5b10() {}
};
class hkEntity_s00b6_5b10 {
public:
    uint32_t pad00[3];
    void* m_userData;                      // +0x0c
    uint32_t pad10[3];
    hkShape_s00b6_5b10* m_shape;                      // +0x1c
    uint32_t pad20[(0x58 - 0x20) / 4];
    class hkMotion_s00b6_5b10* m_motion;             // +0x58
    hkPropertyValue_s00b6_5b10 getProperty(uint32_t key) const;     // 0x00496140
};
class hkMotion_s00b6_5b10 { public:
    uint32_t pad00[4];
    hkTransform_s00b6_5b10 m_transform;               // +0x10
    uint32_t pad50[(0x80 - 0x50) / 4];
    hkQuaternion_s00b6_5b10 m_rotation;               // +0x80
};
class hkCollidable_s00b6_5b10 { public:
    uint32_t pad00[4];
    int m_ownerOffset;                     // +0x10
    uint32_t pad14;
    uint8_t m_broadPhaseType;              // +0x18 (1 = entity)
    hkEntity_s00b6_5b10* getOwner() const { return (hkEntity_s00b6_5b10*)((char*)this + m_ownerOffset); }
};
class hkWorld_s00b6_5b10 { public:
    uint32_t pad00[0x7c / 4];
    void* m_collisionFilter;               // +0x7c
    void castRay(const hkWorldRayCastInput& input, hkClosestRayHitCollector& output) const;   // 0x01082990
};
struct RayObj {
    uint32_t pad00[3];
    hkEntity_s00b6_5b10* m_entity;                    // +0x0c
};
struct RadialRay {
    hkVector4_s00b6_5b10 m_pos;
    hkReal m_h0, m_h1;
};
struct RayHitResult {
    int m_status;                          // +0x00
    uint32_t pad04[3];
    hkVector4_s00b6_5b10 m_pos;                       // +0x10
    hkVector4_s00b6_5b10* m_normalOut;                // +0x20
    hkReal* m_distOut;                     // +0x24
    void* m_userData;                      // +0x28
    hkEntity_s00b6_5b10* m_entity;                    // +0x2c
    void FUN_00b655f0(const RayHitResult* src);   // 0x00b655f0 (thiscall copy; defined out of line)
};
void __cdecl FUN_00b65710(hkVector4_s00b6_5b10* up, const RadialRay* ray);
struct Vec3 {
    float x, y, z;
};
class cPlanetModel {
public:
    uint32_t m_pad00[0x3c];                    // +0x000 .. +0x0ef
    uint8_t  m_useSurfaceF0;                   // +0x0f0
    void FUN_00b816f0(Vec3* out, const void* pos);                 // 0x00b816f0 (ret 8)
    Vec3* FUN_00b82060(Vec3* out, const void* pos, int h);         // 0x00b82060 (ret 0xc)
    Vec3* GetNormalAt(Vec3* out, const Vec3* at);                   // 0x00b7e3b0 (ret 8)
};
struct RayObjList {
    RayObj** m_objects;                        // +0x00
    int      m_count;                          // +0x04
};
void __cdecl FUN_00b65660(RayHitResult* a, const RayHitResult* b, RayHitResult* dst);   // 0x00b65660
template <class T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
// ---- items of slice s00b65b10 end

// ---- items of slice s00b66aa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef void* (__stdcall *TlsGetValueFn)(u32);
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(u32);
struct HkT { void FUN_0107db10(void* ptr, u32 size, u32 align); };
typedef void* (__thiscall *HkAllocFn)(void*, u32, u32);
typedef float*       (__thiscall *GetAabbFn)(void*);
typedef void*        (__thiscall *GetTransformFn)(void*, void*);
typedef unsigned int (__thiscall *ShapeIndexFn)(void*);
typedef void         (__thiscall *ShapeDtorFn)(void*, int);
struct XYZW { float x, y, z, w; };
struct C103 {
    int    m_status;      // +0x00
    u32    m_pad04[3];
    float  m_pos[4];      // +0x10
    float* m_normalOut;   // +0x20
    float* m_distOut;     // +0x24
    u32    m_userData;    // +0x28
    void*  m_entity;      // +0x2c

    void m655f0(C103* other);   // 0x00b655f0 copy hit record
};
struct HkWorld {
    void castRay(void* input, void* collector);   // 0x01082990
};
struct HkAllRayHitCollector {
    void sortHits();                              // 0x010cc160
};
struct D961 {
    int* Find(int* result, int);                  // 0x00496140
};
struct RayInput {
    XYZW from;      // +0x00
    XYZW to;        // +0x10
    u8   enable;    // +0x20
    u8   pad[3];
    u32  filter;    // +0x24
};
struct ClosestHitCollector {
    void* vt;              // +0x00
    u32   earlyOut;        // +0x04
    u32   pad08[2];        // +0x08
    float normal[4];       // +0x10
    u32   pad20;           // +0x20
    float hitFraction;     // +0x24
    u32   pad28[2];        // +0x28
    void* rootCollidable;  // +0x30
};
struct HitEntry {
    float normal[4];       // +0x00
    u32   pad10;           // +0x10
    float hitFraction;     // +0x14
    u32   pad18;           // +0x18
    u32   pad1c;           // +0x1c
    void* collidable;      // +0x20
    u32   pad24[3];        // +0x24
};
struct AllHitsCollector {
    void*      vt;         // +0x00
    u32        pad04;      // +0x04
    u32        pad08[2];   // +0x08
    HitEntry*  data;       // +0x10
    int        size;       // +0x14
    int        flags;      // +0x18
    u32        pad1c;      // +0x1c
    HitEntry   inlineHits[8];  // +0x20
};
struct RayPredicate {
    virtual char accept(void* hit);   // vtable slot 0
};
void* __cdecl FUN_00b53940(u32);
void  __cdecl FUN_00b65710(float* out, float* in);
void  __cdecl FUN_00b665c0(u32, u32, C103* out);
void  __cdecl FUN_00b66460(u32, u32, u32, u32, u32, C103* out);
void  __cdecl FUN_00b66740(u32, void*, u32, C103*);
void  __cdecl FUN_00b66ed0(const float*, void*, u32, C103* out);
void  __cdecl FUN_00b65660(C103* a, C103* b, C103* dst);
void* __fastcall FUN_010c3770(void* mem, int, float radius);
void* __fastcall Collector_DeletingDtor(void* self, int, char flag);
typedef int (__thiscall *HashFn)(void*);
void* __cdecl SP_GetCurrentGameMode(void);
u32   __cdecl ResourceKeyToIcon(u32 key);
struct ModeObj { char pad[0x74]; void* m_table; };
struct ModeTable { int __thiscall FUN_00f3e900(u32 key); };
// ---- items of slice s00b66aa0 end

// ---- items of slice s00b677e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec2 { float x, y; };
struct Vec4 { float x, y, z, w; };
struct Obj;
struct Vtbl
{
	void* s00;                                        // 0x000
	void* s04;                                        // 0x004
	void  (__thiscall* m08)(Obj*);                    // 0x008  release
	void* (__thiscall* query)(Obj*, int);             // 0x00c  interface cast
	void* s10;                                        // 0x010
	void* s14;                                        // 0x014
	void* s18;                                        // 0x018
	void* s1c;                                        // 0x01c
	int   (__thiscall* m20)(Obj*);                    // 0x020  class id
	void* s24;                                        // 0x024
	void* s28;                                        // 0x028
	float*(__thiscall* m2c)(Obj*);                    // 0x02c  world position
	void* (__thiscall* m30)(Obj*);                    // 0x030
	void* s34;                                        // 0x034
	int   (__thiscall* type)(Obj*);                   // 0x038  type hash
	void* s3c;                                        // 0x03c
	void* s40;                                        // 0x040
	void* s44;                                        // 0x044
	void* s48;                                        // 0x048
	int   (__thiscall* m4c)(Obj*);                    // 0x04c  owner id
	void* s50;                                        // 0x050
	void* s54;                                        // 0x054
	int   (__thiscall* m58)(Obj*);                    // 0x058
	void* (__thiscall* m5c)(Obj*);                    // 0x05c
	void* s60;                                        // 0x060
	void* s64;                                        // 0x064
	float*(__thiscall* m68)(Obj*);                    // 0x068
	void* s6c;                                        // 0x06c
	void* s70;                                        // 0x070
	void* s74;                                        // 0x074
	void* s78;                                        // 0x078
	void* s7c;                                        // 0x07c
	void* s80;                                        // 0x080
	void* (__thiscall* m84)(Obj*);                    // 0x084
	void* s88;                                        // 0x088
	void* s8c;                                        // 0x08c
	void* s90;                                        // 0x090
	void* s94;                                        // 0x094
	void* s98;                                        // 0x098
	void* s9c;                                        // 0x09c
	void* sa0;                                        // 0x0a0
	void* sa4;                                        // 0x0a4
	void* sa8;                                        // 0x0a8
	void* sac;                                        // 0x0ac
	void* sb0;                                        // 0x0b0
	void* sb4;                                        // 0x0b4
	void* sb8;                                        // 0x0b8
	void* sbc;                                        // 0x0bc
	void* sc0;                                        // 0x0c0
	void* sc4;                                        // 0x0c4
	void* sc8;                                        // 0x0c8
	void* scc;                                        // 0x0cc
	char  (__thiscall* md0)(Obj*);                    // 0x0d0
	void* sd4;                                        // 0x0d4
	void* sd8;                                        // 0x0d8
	void* sdc;                                        // 0x0dc
	float*(__thiscall* me0)(Obj*);                    // 0x0e0
	void* se4;                                        // 0x0e4
	void* se8;                                        // 0x0e8
	void* sec;                                        // 0x0ec
	void* sf0;                                        // 0x0f0
	void* sf4;                                        // 0x0f4
	void* sf8;                                        // 0x0f8
	void* sfc;                                        // 0x0fc
	void* s100;                                       // 0x100
	void* s104;                                       // 0x104
	void  (__thiscall* m108)(Obj*, void*);            // 0x108
};
struct Obj
{
	Vtbl* vt;                                         // 0x000
};
struct NounMgr
{
	void* Func_b25f40(int id);                        // 0x00b25f40  noun by id
	void* Func_bfc5f0();                              // 0x00bfc5f0  player tribe
	int   Func_b1f9d0();                              // 0x00b1f9d0  player empire or -1
};
struct StarMgr
{
	void* Func_ba9370(int id);                        // 0x00ba9370  empire by id
};
struct RelMgr
{
	char  Func_d01b50(int owner, int player);         // 0x00d01b50  at war
	int   Func_d00a70(int owner, int player, int f);  // 0x00d00a70  relation code
};
struct TribeObj
{
	int GetMaxPopulation();                           // 0x00c8eae0
	int GetAdultPopulation();                         // 0x00c8f370
};
struct EmpireObj
{
	Vec3 GetColor();                                  // 0x00c32cd0  (sret)
};
struct PropObj
{
	float Func_bfc490();                              // 0x00bfc490  float property
};
struct ObjBce5c0
{
	void* Func_bce5c0();                              // 0x00bce5c0
};
struct ObjC9d9e0
{
	void* Func_c9d9e0();                              // 0x00c9d9e0
};
struct ObjC04750
{
	void* Func_c04750();                              // 0x00c04750
};
struct ObjC37710
{
	void* Func_c37710();                              // 0x00c37710
};
struct CitizenObj
{
	char  Func_c232c0();                              // 0x00c232c0  is tribe member
	void* Func_c22f50();                              // 0x00c22f50  tribe
	void* Func_c23e40();                              // 0x00c23e40  city
};
struct PlacementObj
{
	void* Func_ba3f90(void* a, void* b, int c);       // 0x00ba3f90
};
struct SpeciesMgr
{
	void* Func_4e0050(int a, int b);                  // 0x004e0050  archetype
};
struct LayoutObj
{
	void Func_811ad0(int flag);                       // 0x00811ad0  shutdown
};
struct LabelMgr
{
	void* Func_b721d0(int* entry);                    // 0x00b721d0  find entry
};
void* __cdecl SP_NounManager();                       // 0x00b3d300
void* __cdecl SP_StarManager();                       // 0x00b3d2a0
void* __cdecl SP_RelationshipManager();               // 0x00b3d2c0
void* __cdecl SP_App();                               // 0x0067dd10
int   __cdecl FUN_01021090();                         // 0x01021090  player empire id
void* __cdecl FUN_00b3d4c0();                         // 0x00b3d4c0
void* __cdecl FUN_00401090();                         // 0x00401090  species manager
void* __cdecl FUN_00cd40b0();                         // 0x00cd40b0  tribe-mode strategy
void  __cdecl FUN_00805ea0(Vec4* area);               // 0x00805ea0  main window area
void* __cdecl FUN_00eec990(void*);                    // 0x00eec990
void* __cdecl FUN_00b6f0c0(int);                      // 0x00b6f0c0
void* __cdecl FUN_00b676c0(void*);                    // 0x00b676c0
void* __cdecl FUN_00b676e0(void*);                    // 0x00b676e0
void* __cdecl FUN_00b18700(void*);                    // 0x00b18700
char  __cdecl FUN_00b18760(void*);                    // 0x00b18760
void* __cdecl FUN_00c0c380(void*);                    // 0x00c0c380
void* __cdecl FUN_00ac80d0(void*, int);               // 0x00ac80d0
void* __cdecl FUN_00ac8960(void*);                    // 0x00ac8960
void* __cdecl FUN_00ac86d0(void*);                    // 0x00ac86d0
void* __cdecl FUN_00b1fc00(void*);                    // 0x00b1fc00
int   __cdecl FUN_00b677a0(void*);                    // 0x00b677a0
int   __cdecl FUN_00c00ad0(int);                      // 0x00c00ad0
void* __cdecl FUN_00b67700(void*);                    // 0x00b67700
char  __cdecl FUN_00c88e30(void*);                    // 0x00c88e30
struct AppVtbl
{
	char pad[0x58];
	void* (__thiscall* m58)(void*);                   // 0x058
};
struct App
{
	AppVtbl* vt;
	void Transform(Vec2* out, const Vec3* in);        // 0x007c4180
};
extern "C"
{
	extern const float DAT_01687910[3];               // 0x01687910
	extern const float DAT_0168791c[3];               // 0x0168791c
	extern const float DAT_01687928[3];               // 0x01687928
	extern const float DAT_01687934[3];               // 0x01687934
	extern const float DAT_0156b008[3];               // 0x0156b008
	extern float DAT_0168794c;                        // 0x0168794c
	extern float DAT_01687950;                        // 0x01687950
	extern float DAT_01687954;                        // 0x01687954
	extern int   DAT_01687958;                        // 0x01687958
	extern float DAT_01687940;                        // 0x01687940
	extern float DAT_01687944;                        // 0x01687944
	extern float DAT_01687948;                        // 0x01687948
	extern const float DAT_01485720;                  // 0x01485720  1.0
	extern const float DAT_013f6b64;                  // 0x013f6b64
	extern const float DAT_01464988;                  // 0x01464988
	extern const float DAT_013ec488;                  // 0x013ec488  -0.5
	extern const float DAT_01471064;                  // 0x01471064  0.5
	extern const float DAT_013eb1bc;                  // 0x013eb1bc  -1.0
	extern char DAT_01654c02;                         // 0x01654c02
	extern char DAT_01654c05;                         // 0x01654c05
	extern char DAT_01654c10;                         // 0x01654c10
	extern void* g_pLabelMgr;                         // 0x01687348
}
// ---- items of slice s00b677e0 end

// ---- items of slice s00b68720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kColourScale;              // 0x013f2100  255.0f
extern char gVtbl13f94d4;               // 0x013f94d4  RTTI-ish token passed to slot 3
extern int  __cdecl FUN_00bfc480();     // 0x00bfc480
extern void* __cdecl cConnectionDialog_ctor(void*);          // 0x00810000
extern int   __cdecl cSPUILayout_Init(void* self, const wchar_t* name, int a, int b, unsigned c); // 0x00812160
extern void* __cdecl cSPUILayout_FindWindowByID(void* self, unsigned id, int a);                  // 0x008105b0
extern void  __cdecl cSPUILayout_Shutdown(void* self, unsigned a);                                // 0x00811ad0
extern void  __cdecl cSPUILayout_dtor(void* self);                                               // 0x00811fe0
extern void  __cdecl AnchorWindowToWindow(void* a, void* b, int c, int d);                        // 0x00807340
extern const wchar_t kRolloverInvulnName[];   // 0x01464990 L"Rollover_ScenarioInvulnerableImage"
extern float kProbeLimit;                // 0x013eb1bc
extern int  __cdecl FUN_00b687d0(int* value);          // 0x00b687d0 (FindOrCreate)
extern float __cdecl FUN_00b685e0(int* value);         // 0x00b685e0
extern void* __cdecl operator_new(unsigned n, const char* file, int a, int b, int c, int d);  // FUN_00f473a0
extern void* __cdecl SPUIHelpers_CenterWindowInRect(void* obj);   // FUN_00b5b800
extern void* __cdecl GetCurrentGameMode();              // FUN_00cd40b0
extern int   __cdecl TribeModeStrategyInstance();       // 0x00cd40b0 SP::cTribeModeStrategy::Instance
extern const wchar_t kLayout_TribeTool[];               // L"Rollover_TribeTool"          0x01464b2c
extern const wchar_t kLayout_TribeCitizen[];            // L"Rollover_TribeCitizen"       0x01464b54
extern const wchar_t kLayout_TribeHut[];                // L"Rollover_TribeHut"           0x01464b08
extern const wchar_t kLayout_TribeMinimap[];            // L"Rollover_Tribe_Minimap"      0x01464ad8
extern const wchar_t kLayout_ScenarioVehicle[];         // L"Rollover_ScenarioVehicle"    0x01464bcc
extern const wchar_t kLayout_CivVehicle[];              // L"Rollover_CivVehicle"         0x01464ba4
extern const wchar_t kLayout_CityMinimap[];             // L"RolloverCity_Minimap"        0x01464a48
extern const wchar_t kLayout_SpaceCity[];               // L"RolloverSpaceCity"           0x01464a24
extern const wchar_t kLayout_SharedHealthBar[];         // L"SharedHealthBar"             0x01464a04
extern const wchar_t kLayout_Building[];                // L"Rollover_Building"           0x01464b80
extern const wchar_t kLayout_UFO[];                     // L"RolloverUFO"                 0x01464ac0
extern const wchar_t kLayout_Creature[];                // L"Rollover_Creature"           0x01464a9c
extern const wchar_t kLayout_CRGMinimap[];              // L"Rollover_CRGMinimap"         0x01464a74
extern const wchar_t kLayout_FixedObject[];             // L"Rollover_FixedObject"        0x014649d8
struct Obj_s00b6_8720 {
    unsigned char pad0[4];
    int mField4;                        // 0x04
    unsigned char pad8[0x14];
    float m1c;                          // 0x1c
    float m20;                          // 0x20
    float m24;                          // 0x24
    float m28;                          // 0x28
    float m2c;                          // 0x2c
    float m30;                          // 0x30
    unsigned char m34;                  // 0x34 active-layout flag
    unsigned char pad35[3];
    float m38;                          // 0x38
    float m3c;                          // 0x3c
    float m40;                          // 0x40
    float m44;                          // 0x44
    float m48;                          // 0x48
    float m4c;                          // 0x4c
    int m50;                            // 0x50 (layout)
    int m54, m58, m5c;                  // 0x54..
    int m60, m64, m68, m6c, m70;
    int m74, m78, m7c, m80, m84, m88, m8c;
    int m90, m94, m98, m9c, ma0, ma4, ma8, mac, mb0, mb4;
    int mb8;                            // 0xb8
    int mFieldBC;                       // 0xbc
    unsigned char padc0[0x58];
    int m118;                           // 0x118
    float m11c;                         // 0x11c
    int m120;                           // 0x120
    int m124;                           // 0x124
    int m128;                           // 0x128
};
struct Manager {
    unsigned char pad0[0x24];
    float mGlowDecay;                   // 0x24 damage-glow decay rate
    float mRefillRate;                  // 0x28 bar refill rate
    float mDrainRate;                   // 0x2c bar drain rate
    int GetPriority();                          // 0x00e31100 (thiscall)
    Obj_s00b6_8720* Find(const int& key);                  // 0x00b72230 (thiscall, ret 4)
    int Alloc();                                // 0x00b72160 (thiscall)
    Obj_s00b6_8720* Make(int handle);                      // 0x00b72210 (thiscall, ret 4)
};
struct cSPUILayout_s00b6_8720 {
    void* FindWindowByID(unsigned id, int a);   // 0x008105b0 (thiscall)
};
extern Manager* gManager;               // 0x01687348
struct Rect {
    float left;                         // 0x00
    float top;                          // 0x04
    float right;                        // 0x08
    float bottom;                       // 0x0c
};
static __inline float Clamp01Inline(float v)
{
    __m128 x = _mm_set_ss(v);
    x = _mm_max_ss(_mm_setzero_ps(), x);
    x = _mm_min_ss(x, _mm_set_ss(1.0f));
    return _mm_cvtss_f32(x);
}
// ---- items of slice s00b68720 end

// ---- items of slice s00b6a420 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" extern char DAT_01654c01[], DAT_01654c02_s00b6_a420[], DAT_01654c05_s00b6_a420[], DAT_01654c10_s00b6_a420[];
extern float DAT_01464980;                              // FLT_MAX sentinel
extern float DAT_01485378;                              // 0.0f sentinel
extern float DAT_01473c70;                              // subtract constant in FUN_00b6a720
extern float DAT_013f2100;                              // 255.0f
extern int   DAT_0156ae80, DAT_0156ae84, DAT_0156ae88, DAT_0156ae8c, DAT_0156ae90;
extern int   DAT_0158133c;
#undef VS
#define VS(n) virtual void vs##n();
struct IV {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66) VS(67)
};
#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
struct Obj_s00b6_a420 {
virtual void o00();
virtual void o01();
virtual void o02();
    virtual void* Cast(uint32_t id);          // +0x0c
virtual void o04();
virtual void o05();
virtual void o06();
virtual void o07();
virtual void o08();
virtual void o09();
virtual void o0a();
virtual void o0b();
virtual void o0c();
virtual void o0d();
    virtual uint32_t GetType();               // +0x38
};
struct Label {
    void*   mpObj0;   // +0x00  (object whose vtable the helpers use; [label] in the original)
    Obj_s00b6_a420*    mpObj;    // +0x04
    bool    mFlag;    // +0x08
    float   mX;       // +0x0c
    float   mY;       // +0x10
    float   mX2;      // +0x14
    float   mY2;      // +0x18
    float   f1c;      // +0x1c
    float   f20;      // +0x20
    float   f24;      // +0x24
    float   f28;      // +0x28
    float   f2c;      // +0x2c
    float   f30;      // +0x30
    uint8_t b34;      // +0x34
    float   f38;      // +0x38
    float   f3c;      // +0x3c
    float   f40;      // +0x40
    float   f44;      // +0x44
    float   f48;      // +0x48
    float   f4c;      // +0x4c
    void*   p50;      // +0x50
    IV*     p54;      // +0x54
    IV*     p58;      // +0x58
    IV*     p5c;      // +0x5c
    IV*     p60;      // +0x60
    void*   p64;      // +0x64
    void*   p68;      // +0x68
    void*   p6c;      // +0x6c
    IV*     p70;      // +0x70
    IV*     p74;      // +0x74
    void*   p78;      // +0x78
    IV*     p7c;      // +0x7c
    IV*     p80;      // +0x80
    IV*     p84;      // +0x84
    IV*     p88;      // +0x88
    void*   p8c;      // +0x8c
    IV*     p90;      // +0x90
    IV*     p94;      // +0x94
    IV*     p98;      // +0x98
    IV*     p9c;      // +0x9c
    void*   pA0;      // +0xa0
    void*   pA4;      // +0xa4
    IV*     pA8;      // +0xa8
    IV*     pAc;      // +0xac
};
void* __cdecl operator_new(uint32_t size, const char* name, int, int, int, int);   // 0x00f473a0
void  __fastcall FUN_00743b50(void** p);                                           // 0x00743b50
void* __cdecl GetMainWindowArea(float* out);                                        // 0x00805ea0
bool  __cdecl FUN_00b6a200(Obj_s00b6_a420* o, float* p2);                                     // 0x00b6a200
bool  __cdecl FUN_00b69cf0(void* c, float* p2, float* p3);                         // 0x00b69cf0
bool  __cdecl FUN_00b67ef0(void* c, float* p2, float* p3);                         // 0x00b67ef0
bool  __cdecl FUN_00b69010(Label* l, float a, float b);                            // 0x00b69010
void  __cdecl FUN_00b686a0(IV* p);                                                 // 0x00b686a0
int   __cdecl FUN_00b675a0(int a);                                                 // 0x00b675a0
int   __cdecl FUN_00b67530(int a, char b);                                         // 0x00b67530
int   __cdecl FUN_00b674d0(int a);                                                 // 0x00b674d0
void  __cdecl FUN_00b67440(IV* ui, int color, float a);                            // 0x00b67440
void  __cdecl FUN_00b693b0(void* src, IV* ui, float a);                            // 0x00b693b0
void  __cdecl FUN_00b6a720(Label* l, const float* pair, int v, int b1, int b2);    // 0x00b6a720
void  __cdecl SetNumberString(int value, int hi, wchar_t* buf, int count);         // 0x00881ae0
int   __cdecl WStr_Format(wchar_t* buf, const wchar_t* fmt, ...);                  // 0x0041e050
void  __cdecl SetTooltipText(IV* win, const wchar_t* text, int a, int b);          // 0x00806de0
void* __cdecl SP_cTribeModeStrategy_Instance(void);                                // 0x00cd40b0
int   __cdecl FUN_00d09660(void* p);                                               // 0x00d09660
int   __cdecl FUN_00cd5750(void* p);                                               // 0x00cd5750
IV*   __cdecl FindWindowByID(void* layout, uint32_t id, int);                      // 0x008105b0
void* __cdecl GetPlayerTribe(void);                                                // 0x00bfc5f0 chain
int   __cdecl FUN_00c8f3a0(void* tribe);                                           // 0x00c8f3a0
int   __cdecl SP_GetMaxPopulation(void* tribe);                                    // 0x00c8eae0
int   __cdecl FUN_00a1ad10(void* tribe);                                           // 0x00a1ad10
struct eastl_string {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; int mAlloc0; int mAlloc1;
    eastl_string& operator=(const wchar_t*);
    eastl_string& operator+=(const wchar_t*);
    const wchar_t* c_str() const { return mpBegin; }
};
struct cString {
    eastl_string mStr;
    cString(uint32_t table, uint32_t id, int flag);
    ~cString();
    const wchar_t* GetText();
};
struct Stopwatch {
    uint64_t mnStart;
    uint64_t mnTotal;
    int      mnUnits;
    float    mfCoeff;
    void Init(int units, int coeff);                                      // 0x0093a560
};
struct Mgr {
    void*   mpPool;      // +0x00
    int     f04;         // +0x04
    int     f08;         // +0x08
    int     f0c;         // +0x0c
    int     f10;         // +0x10
    int     f14;         // +0x14
    int     f18;         // +0x18
    int     g1c;         // +0x1c
    int     g20, g24, g28, g2c;
    uint8_t b30;         // +0x30
    uint8_t pad31[7];
    Stopwatch sw;        // +0x38
    int     f50;         // +0x50
    int     f54;         // +0x54
    void InitPool(int a, int b);                                          // 0x00b72080
};
Mgr* g_pMgr;             // 0x01687348
static int ModeFromValue(int v)
{
    switch (v + 1) {
    case 1: return 2;
    case 2: return 0;
    case 3: return 3;
    case 5: return 1;
    default: return -1;
    }
}
// ---- items of slice s00b6a420 end

// ---- items of slice s00b6b1a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t       gEmptyString16;    // 0x01667bac eastl::gEmptyString16 (L"")
extern const wchar_t gStr013ec468;      // 0x013ec468 default text key/name
extern float         kFloat100;         // 0x013ec4d0 100.0f
extern float         kFloat50;          // 0x013f1cac  50.0f
#pragma warning(disable : 4100)
struct cToolGate;
extern cToolGate* gToolGate;            // 0x0169d3c8
struct cTextRoot;
void EA_Locale_SetNumberString(int value, int sign, wchar_t* buf, int count);  // 0x00881ae0
cTextRoot* FUN_0067de40();                                                     // 0x0067de40
struct cToolGate {
    void FUN_00cfe780(void* obj);       // 0x00cfe780
};
struct WString {
    const wchar_t* mBegin;   // +0x00
    const wchar_t* mEnd;     // +0x04
    const wchar_t* mCap;     // +0x08

    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
    void RangeInitialize(const wchar_t* s);            // 0x00579a90
    ~WString() {
        if ((((u32)((const char*)mCap - (const char*)mBegin)) & 0xfffffffeu) > 2 && mBegin != 0)
            delete[] (wchar_t*)mBegin;
    }
};
struct cString_s00b6_b1a0 {
    u32 m00;        // +0x00
    u32 m04;        // +0x04
    u32 m08;        // +0x08
    u32 m0c;        // +0x0c
    u16 m10;        // +0x10
    u16 m12;        // +0x12

    cString_s00b6_b1a0();                                         // 0x006b5060
    cString_s00b6_b1a0(u32 a, u32 b, const wchar_t* text);        // 0x006b5770
    u8  Load(u32 a, u32 b, int c);                     // 0x006b54b0
    const wchar_t* GetText();                          // 0x006b55c0
    ~cString_s00b6_b1a0();                                        // 0x006b5240
};
struct EStr {
    wchar_t* mBegin;    // +0x00
    wchar_t* mEnd;      // +0x04
    wchar_t* mCap;      // +0x08
    u32      m0c;       // +0x0c
    wchar_t* m10;       // +0x10
                        // +0x14: 0x40-byte inline buffer

    EStr* Construct(const wchar_t* text);              // 0x006743f0
    EStr* Init(const wchar_t* a, const wchar_t* b);    // 0x00672750
};
struct cTextObj;
struct cTextRoot {
    virtual void      r00();
    virtual void      r04();
    virtual void      r08();
    virtual void      r0c();
    virtual void      r10();
    virtual void      r14();
    virtual void      r18();
    virtual void      r1c();
    virtual cTextObj* r20();                            // +0x20
};
struct cTextObj {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30(cString_s00b6_b1a0* out, u32* key, int flag); // +0x30
};
struct cUIWindow {
    virtual void       w00();
    virtual void       w04(float f);                    // +0x04
    virtual void       w08();
    virtual cUIWindow* w0c(u32 key);                    // +0x0c
    virtual void       w10();
    virtual void       w14();
    virtual void       w18();
    virtual void       w1c();
    virtual void       w20();
    virtual void       w24();
    virtual void       w28();
    virtual void       w2c();
    virtual void       w30();
    virtual void       w34();
    virtual void       w38();
    virtual void       w3c();
    virtual void       w40();
    virtual void       w44();
    virtual void       w48();
    virtual void       w4c();
    virtual void       w50();
    virtual void       w54();
    virtual void       w58();
    virtual void       w5c(u32 color);                 // +0x5c
    virtual void       w60();
    virtual void       w64();
    virtual void       w68();
    virtual void       w6c();
    virtual void       w70();
    virtual void       w74();
    virtual void       w78();
    virtual void       w7c();
    virtual void       w80(const wchar_t* text);        // +0x80
};
struct cSPUILayout_s00b6_b1a0 {
    cUIWindow* FindWindowByID(u32 id, int flag);        // 0x008105b0
};
struct cObjBase {                                       // anything with slot +0x0c
    virtual void  b00();
    virtual void  b04();
    virtual void  b08();
    virtual void* b0c(u32 key);                         // +0x0c
};
struct cSpeciesProfile {
    void GetUiName(WString* out);                       // 0x004da330
};
struct cSpeciesInfo {
    u8  pad000[0x15c];
    int m15c;                                           // +0x15c
};
struct cCreature {                                      // cSPCreatureCitizen-ish
    virtual void  c00();
    virtual void  c04();
    virtual void  c08();
    virtual void* c0c(u32 key);                         // +0x0c
    u8  pad010[0xb20 - 0x10];
    cSpeciesProfile* mSpecies;                          // +0xb20
    u8  padb24[0xb38 - 0xb24];
    WString mName;                                      // +0xb38
    u8  padb44[0xb58 - 0xb44];
    u8  mFlagsB58;                                      // +0xb58

    u8      FUN_00c0b770();                             // 0x00c0b770
    u8      IsLeader();                                 // 0x00c232d0
    u8      Flag388();                                  // 0x00c0c0e0
    u8      Flag389();                                  // 0x00c0c100
    int     FUN_00c22dc0();                             // 0x00c22dc0
    cSpeciesInfo* FUN_00c04590();                       // 0x00c04590  Get()
};
struct cConvSelf {
    u8 pad000[0x50];
    cSPUILayout_s00b6_b1a0* mLayout;                               // +0x50
    u8 pad054[0xa8 - 0x54];
    cUIWindow*   mWnd;                                  // +0xa8
};
struct cConvTarget {
    u8  pad000[0x668];
    int m668;                                           // +0x668
    int m66c;                                           // +0x66c

    int FUN_00bd8960();                                 // 0x00bd8960
    int FUN_00bd9b70();                                 // 0x00bd9b70
};
struct cConvInfo {
    u8  pad000[0x64c];
    u32 mId;                                            // +0x64c
};
struct cPropDesc {
    u8  pad000[0x12];
    u16 mType;                                          // +0x12
    u32* GetUInt();                                     // 0x0041ea00
};
struct cProp {
    virtual void p00();
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual u8   p24(u32 key, cPropDesc** out);         // +0x24
};
struct cPropertyManager {
    virtual void q00();
    virtual void q04();
    virtual void q08();
    virtual void q0c();
    virtual void q10();
    virtual void q14();
    virtual void q18();
    virtual void q1c();
    virtual void q20();
    virtual void q24();
    virtual void q28();
    virtual void q2c(void* owner, u32 key, cProp** out);  // +0x2c
};
struct cPropSetter { void* mPtr; };                     // first field of 0xb8dad0()'s result
struct cPlanet {
    u8 pad000[0x13c];
    cPropSetter* m13c;                                  // +0x13c

    cPropSetter* FUN_00b8dad0();                        // 0x00b8dad0
};
struct cLivingUniverse {
    u8 pad000[0x13c];
    cPlanet* mActivePlanet;                             // +0x13c
};
cPropertyManager* SP_PropertyManager();                 // 0x0067de30
cLivingUniverse*  SP_GetActivePlanet();                 // 0x01021260
// ---- items of slice s00b6b1a0 end

// ---- items of slice s00b6baf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t gEmptyStr[];       // 0x013EC468 (L"")
extern void* gEmptyRep;                 // 0x01667BAC (shared empty string rep)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
void  EAFree(void* p);                                                    // 0x00F47380
struct cVar {
    uint32_t mData[0x58 / 4];
    cVar(const wchar_t* psz);            // 0x006743F0
};
struct Str12 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacityEnd;
    Str12() {
        mpBegin = (wchar_t*)&gEmptyRep;
        mpEnd = (wchar_t*)&gEmptyRep;
        mpCapacityEnd = (wchar_t*)((char*)&gEmptyRep + 2);
    }
    ~Str12() {
        if ((((int)((char*)mpCapacityEnd - (char*)mpBegin)) & -2) > 2 && mpBegin)
            EAFree(mpBegin);
    }
};
class cString_s00b6_baf0 {
public:
    cString_s00b6_baf0();                                                                  // 0x006B5060
    cString_s00b6_baf0(uint32_t tableID, int instanceID, const wchar_t* defaultText);      // 0x006B5770
    ~cString_s00b6_baf0();                                                                 // 0x006B5240
    bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006B54B0
    const wchar_t* GetText();                                                   // 0x006B55C0
private:
    uint32_t mData[5];
};
struct NameSub {                         // sub-object with a vtable at +0x34 of "named" things
    virtual void n0();
    virtual const wchar_t* GetName();    // +0x04
};
struct Named {
    char pad[0x34];
    NameSub sub;
};
struct City;
struct VObj {                            // generic interface object
virtual void s00();
virtual void s01();
virtual void s02();
    virtual VObj* Cast(uint32_t id);     // +0x0c
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s0A();
virtual void s0B();
virtual void s0C();
virtual void s0D();
    virtual int GetVarID();              // +0x38
virtual void s0F();
virtual void s10();
virtual void s11();
virtual void s12();
    virtual int GetID();                 // +0x4c
virtual void s14();
virtual void s15();
    virtual int GetIndex();              // +0x58
    virtual Named* GetNamed();           // +0x5c
virtual void s18();
virtual void s19();
virtual void s1A();
virtual void s1B();
    virtual void s1C();
    virtual const wchar_t* GetText();    // +0x74
virtual void s1E();
virtual void s1F();
virtual void s20();
    virtual void* Get84();               // +0x84 (a City* or a Named*, depending on the object)
    City* GetCityMember();               // 0x00BCE5C0
};
struct Civ {                             // civilization (vtable object with a name and a string table)
virtual void c0();
virtual void c1();
virtual void c2();
    virtual struct TableOwner* Cast(uint32_t id);   // +0x0c
    char pad[0x38 - 4 - 12 + 0];
    const wchar_t* mpName;               // +0x3c
    const wchar_t** GetNamePtr();        // 0x005C65E0 (returns &mpName)
};
struct StarMgr_s00b6_baf0 {
    Civ* GetEmpireByID(int id);                 // 0x00BA9370
};
StarMgr_s00b6_baf0* StarManager();                                         // 0x00B3D2A0
struct StrNode {
    char pad[0x14]; const wchar_t* value;       // key at +0x10, value at +0x14
};
struct StrIter { StrNode* node; StrIter() {} StrIter(const StrIter& o) { node = o.node; } };
struct StrMap {
    StrIter find(const uint32_t& key);                          // 0x00E5C780
};
struct TableOwner {
    char pad[8];
    StrMap map;
};
struct Species {
    char pad[0x51c]; const wchar_t* mpName;
};
struct Herd {
    char pad[0x84];
    uint8_t b84;
    char pad2[0x1f];
    Species* ma4;                         // +0xa4
};
struct Creature {
    char pad0[0x124];
    uint8_t b124;
    char pad2[3];
    Herd* m128;
    char pad3[0x714 - 0x12c];
    int m714;
};
struct SpeciesMgr_s00b6_baf0 {
    Species* GetAvatarProfile();             // 0x004DF420
};
SpeciesMgr_s00b6_baf0* GetSetting9();                                      // 0x00401090
struct Terrain {
    bool Check(uint32_t id, uint32_t* out);     // 0x00C77380
};
struct NounMgr_s00b6_baf0 {
    Terrain* GetTerrain();                                      // 0x00F67D90
    Named* FindNamed(int id);                                   // 0x00B25F40
};
NounMgr_s00b6_baf0* NounManager();                                         // 0x00B3D300
struct City {
    Civ* GetCivilization();                        // 0x00BD9BF0
};
struct Rec {
    bool Get(Str12* out);                           // 0x00F28B80
};
struct RecMgr {
    Rec* Find(VObj* obj);                        // 0x00F3E900
};
struct Globals {
    char pad[0x74]; RecMgr* m74;
};
extern Globals* gGlobals16c7aa4;                                // 0x016C7AA4
struct TableRow {
    char pad[0x68]; cString_s00b6_baf0 str;
};
TableRow* LookupRow(int idx);                                   // 0x00C9CEC0
struct Planet {
    int GetState();                              // 0x00C70E00
};
struct UniCtx;
int GetCurrentGameMode_s00b6_baf0();                                       // 0x00B5B800
UniCtx* GetUniverseContext();                                   // 0x01021080
Planet* GetActivePlanet();                                      // 0x01021260
Herd* GetDesiredAvatarHerd(bool b);                             // 0x00D40B40
VObj*   CastB033(VObj* obj);                                    // 0x00B67740
VObj*   CastEE02(VObj* obj);                                    // 0x00B676E0
VObj*   CastE9CB(VObj* obj);                                    // 0x00B67720
Creature* CastB92(VObj* obj);                                   // 0x00B1FC00
Named*  CastEE9B(VObj* obj);                                    // 0x00AC86D0
Named*  CheckType(VObj* obj, uint32_t type);                    // 0x00AC80D0
cVar    ResolveRollover(VObj* obj);                             // 0x00B6B4C0
cVar    ResolveB6BA50(VObj* obj);                               // 0x00B6BA50
cVar    ResolveB6B810(VObj* obj);                               // 0x00B6B810
struct UICtx;
struct SimState;
struct SimView {
virtual void w00();
virtual void Release();
virtual void w02();
    virtual SimView* Cast(uint32_t id);                          // +0x0c
virtual void w04();
virtual void SetLayoutIndex(int index);
virtual void w06();
virtual int GetIndex();
virtual void w08();
virtual void w09();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual int GetVarID();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
    virtual void SetVisible(int a, int b);                       // +0x7c
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
virtual void w36();
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
virtual void w45();
virtual void w46();
virtual void w47();
virtual void w48();
virtual void w49();
virtual void w50();
virtual void w51();
    virtual bool IsBlockedPrimary();                             // +0xd0
    virtual bool IsBlockedSecondary();                           // +0xd4
virtual void w54();
virtual void w55();
virtual void w56();
virtual void w57();
virtual void w58();
virtual void w59();
    virtual SimView* FindWindow(int id, int flags);              // +0xf0
virtual void w61();
virtual void w62();
virtual void w63();
virtual void w64();
    virtual void w65();
    virtual void OnLayoutChange(void* pData);                    // +0x108
    virtual void w67();

    char mPad00[0xb58 - 4];
    uint32_t mFlags;                                             // +0xb58

    bool CheckActive();                                          // 0x00C0B770
    SimState* GetState();                                        // 0x00C0C1A0
};
struct SimState {
    char mPad00[0x32c];
    int mCount;                                                  // +0x32c
};
struct UIPtrVector {
    SimView** mpBegin;                                           // +0x00
    SimView** mpEnd;                                             // +0x04
    SimView** mpCapacityEnd;                                     // +0x08

    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }

    void push_back(SimView* const& value)
    {
        if (mpEnd < mpCapacityEnd)
        {
            SimView** pSlot = mpEnd++;
            if (pSlot)
                *pSlot = value;
        }
        else
            DoInsertValue(mpEnd, value);
    }

    void erase(SimView** first, SimView** last)
    {
        memcpy(first, last, (unsigned int)((char*)mpEnd - (char*)last));
        mpEnd -= last - first;
    }

    void DoInsertValue(SimView** pPosition, SimView* const& value);   // 0x00CD0550
};
struct RefObj {
    virtual void r00();
    virtual void Release();                                      // +0x04
    virtual void Destroy();                                      // +0x08
};
struct cSPUILayoutBase {
    virtual void l00();
    virtual void AddRef();                                       // +0x04
    virtual void Release();                                      // +0x08
};
struct cSPUILayout_s00b6_baf0 : cSPUILayoutBase {
    cSPUILayout_s00b6_baf0* ctor();                                                          // 0x00810000
    bool Init(const wchar_t* pName, int scale, bool bFlag, unsigned int key);     // 0x00812160
    SimView* FindWindowByID(int windowID, int flags);                             // 0x008105B0
    void Shutdown(unsigned int flags);                                            // 0x00811AD0
};
struct TribeStrategyData {
    int mValue;                                                  // +0x00
};
struct TribeModeStrategy {
    char mPad00[4];
    TribeStrategyData mData;                                     // +0x04
};
TribeModeStrategy* TribeModeStrategyInstance_s00b6_baf0();                  // 0x00CD40B0
struct UICtx {
    int mID;                                                     // +0x000
    VObj* mObj;                                                  // +0x004
    bool mVisible;                                               // +0x008
    char mPad09[3];
    float mX;                                                    // +0x00c
    float mY;                                                    // +0x010
    char mPad14[0x3c];
    cSPUILayout_s00b6_baf0* mSubLayout;                                     // +0x050
    char mPad54[0x24];
    SimView* mMainWindow;                                        // +0x078
    char mPad7C[0x24];
    SimView* mStateWindow;                                       // +0x0a0
    VObj* mOwnerObj;                                             // +0x0a4
    char mPadA8[4];
    SimView* mSubWindow;                                         // +0x0ac
    char mPadB0[8];
    cSPUILayout_s00b6_baf0* mLayout;                                        // +0x0b8
    SimView* mWindow;                                            // +0x0bc
    UIPtrVector mWindows;                                        // +0x0c0
    char mPadCC[0x4c];
    int mIndex;                                                  // +0x118
    float mTimer;                                                // +0x11c
    RefObj* mRef;                                                // +0x120

    void ClearWindows() { mWindows.erase(mWindows.mpBegin, mWindows.mpEnd); }

    // register-argument helpers of the original TU (record arrives in esi)
    bool UpdateSimulatorAnim(float value, float elapsed);        // 0x00B69010
    void ShowSimulatorText(float* pOffset, int a2, const void* pText,
                           Vec3* pPos, int a4, int a5);          // 0x00B6A720
};
struct UIMgr {
    UICtx* Find(int key);                                        // 0x00B721D0
    UICtx* GetSlot(int key);                                     // 0x00B72210
    UICtx* Next(int* pKey);                                      // 0x00B72230
    void   Remove(int key);                                      // 0x00B72260
    int    CurrentKey();                                         // 0x00E31100
};
extern UIMgr* gUIMgr;                                            // 0x01687348
void* SporeAlloc(int size, const wchar_t* pName, int a, int b, int c, int d);   // 0x00F473A0
int   FindOrCreateKey(int key);                                                  // 0x00B687D0
void  AnchorWindowToScreen(float* pRect, SimView* pWindow, int flags, int arg);  // 0x008070D0
Vec3  GetSimulatorPos(VObj* pObj);                                               // 0x00B677E0
float GetSimulatorFloat(VObj* pObj);                                             // 0x00B685E0
int   GetSimulatorInt1(VObj* pObj);                                              // 0x00B682A0
int   GetSimulatorInt2(VObj* pObj);                                              // 0x00B67B90
static void CleanupUICtx(int key);                               // 0x00B6C180 (key in eax)
static void RemoveUISlot(int key);                               // 0x00B686A0 (key in eax)
static void SetCtxWindow(SimView* pObj, int index);              // 0x00B69460
static UICtx* ShowHealthBar(int key);                            // 0x00B6C2D0 (key in eax)
__declspec(noinline) static void RemoveUISlot(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx || !pCtx->mSubLayout)
        return;

    if (GetCurrentGameMode_s00b6_baf0() == 0x1654c02 && pCtx->mObj->GetVarID() == 0xee02c7)
    {
        TribeModeStrategy* pStrategy = TribeModeStrategyInstance_s00b6_baf0();
        pCtx->mSubWindow->OnLayoutChange(pStrategy ? &pStrategy->mData : 0);
    }

    pCtx->mSubLayout->Shutdown(1);

    cSPUILayout_s00b6_baf0* pLayout = pCtx->mSubLayout;
    if (pLayout)
    {
        pCtx->mSubLayout = 0;
        pLayout->Release();
    }
}
static void SetCtxWindow(SimView* pObj, int index)
{
    SimView* pView = pObj ? pObj->Cast(0xeeee8218) : 0;

    if (index == -1)
    {
        pView->SetVisible(1, 0);
        return;
    }

    pView->SetVisible(1, 1);
    pObj->SetLayoutIndex(index);
}
static void ReleaseRefSlot(RefObj*& pSlot)
{
    RefObj* pRef = pSlot;
    if (pRef)
    {
        pSlot = 0;
        pRef->Release();
    }
}
// ---- items of slice s00b6baf0 end

// ---- items of slice s00b6d3c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kEmptyStr[];                               // 0x013ec468
extern uint32_t g_slot01687968;                                 // 0x01687968 (last handed out slot id)
extern char g_slots0168795c[];                                  // 0x0168795c (occupied flags, 12 entries)
extern int g_flag0156b0cc;                                      // 0x0156b0cc
extern int g_dataset0156b0d8;                                   // 0x0156b0d8
#undef PV
#define PV(n) virtual void pv##n();
struct SubD {                                                   // embedded at ObjD+0x34
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32)
    virtual float V51();                                        // +0xcc
};
struct ObjD {                                                   // id 0x0137e8e0
    int pad_vptr;
    char pad04[0x34 - 4];
    SubD mSub;                                                  // +0x34
    char pad38[0xb1c - 0x38];
    int mY1;                                                    // +0xb1c
    int mY2;                                                    // +0xb20
    float FUN_00c9f330();                                       // 0x00c9f330
};
struct ObjA {                                                   // id 0x0116d858
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual int V22();                                          // +0x58
};
struct ObjC {                                                   // id 0xce9f6639 (creature)
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c)
    PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual bool V53();                                         // +0xd4
};
struct ObjB {                                                   // id 0x4f176642
    int FUN_00c22dc0();                                         // 0x00c22dc0
};
struct IWinObj;                                                 // a tooltip/label window (see below)
struct Obj_s00b6_d3c0 {                                                    // the thing a queue entry refers to
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t id);                            // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsLabelAlive();                                // +0x2c
};
void __cdecl EA_Free(void* p);                                    // 0x00f47380 (operator delete[])
struct WString_s00b6_d3c0 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      pad;
    wchar_t  mBuffer[36];
    ~WString_s00b6_d3c0() {
        if ((int)(((unsigned)mpCapacity - (unsigned)mpBegin) & 0xfffffffe) > 2 && mpBegin && mpBegin != mBuffer)
            EA_Free(mpBegin);
    }
};
struct cEmpire { Vec3 GetColor(); };                            // 0x00c32cd0 (sret, ret 4)
cEmpire* GetPlayerEmpire();                                     // 0x01021300 (cdecl)
struct Event {
    int mKey;                                                   // +0x00
    Obj_s00b6_d3c0* mpObj;                                                 // +0x04
    char mFlag;                                                 // +0x08
    float mX;                                                   // +0x0c
    float mY;                                                   // +0x10
    char pad14[4];
    float mLimitY;                                              // +0x18
    char pad1c[0x50 - 0x1c];
    int mArmed;                                                 // +0x50
    IWinObj* mpWin54;                                           // +0x54
    IWinObj* mpWin58;                                           // +0x58
    char pad5c[0x70 - 0x5c];
    IWinObj* mpWin70;                                           // +0x70
    char pad74[0x90 - 0x74];
    Obj_s00b6_d3c0* mpField90;                                             // +0x90
    char pad94[0xb8 - 0x94];
    IWinObj* mpLayout;                                          // +0xb8
    IWinObj* mpWinBC;                                           // +0xbc
    char padC0[0x120 - 0xc0];
    IWinObj* mpWin120;                                          // +0x120
    char pad124[4];
    int mState128;                                              // +0x128
};
struct Mgr_s00b6_d3c0 {
    char pad00[0x38];
    int f38, f3c;
    char pad40[0x50 - 0x40];
    int f50;                                                    // +0x50
    Event* FUN_00b72230(int* cookie);                           // 0x00b72230 (thiscall, next entry)
};
extern Mgr_s00b6_d3c0* g_pMgr_s00b6_d3c0;                                             // 0x01687348
extern const Vec3 kLabelColor;                                  // 0x0156b008
void  FUN_00b6d1d0(int a);                                      // 0x00b6d1d0 (cdecl)
int   FUN_00e31100();                                           // 0x00e31100 (cdecl, GetPriority)
unsigned FUN_00b67c70(Obj_s00b6_d3c0* o);                                  // 0x00b67c70 (cdecl, kind 0..16)
int   FUN_00b67b90(Obj_s00b6_d3c0* o);                                     // 0x00b67b90 (cdecl)
int   FUN_00b681d0(Obj_s00b6_d3c0* o);                                     // 0x00b681d0 (cdecl)
int   FUN_00b68250(Obj_s00b6_d3c0* o);                                     // 0x00b68250 (cdecl)
int   FUN_00b682a0(Obj_s00b6_d3c0* o);                                     // 0x00b682a0 (cdecl)
float FUN_00b685e0(Obj_s00b6_d3c0* o);                                     // 0x00b685e0 (cdecl)
Vec3  FUN_00b677e0(Obj_s00b6_d3c0* o);                                     // 0x00b677e0 (cdecl, sret)
WString_s00b6_d3c0 FUN_00b6baf0(Obj_s00b6_d3c0* o);                                   // 0x00b6baf0 (cdecl, sret)
bool FUN_00b6a970(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, Vec3 col, int a, int b, float dt);   // 0x00b6a970
void FUN_00b6a9d0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6a9d0
void FUN_00b6adf0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6adf0
void FUN_00b6b0a0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt);   // 0x00b6b0a0
void FUN_00b6aae0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt);   // 0x00b6aae0
void FUN_00b6abc0(Event* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, float f1, float f2, int c, int d, float dt);   // 0x00b6abc0
void FUN_00b6cc50(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cc50
void FUN_00b6c870(Event* e, int flag, const Vec2* pos, bool b, float dt);   // 0x00b6c870
void FUN_00b6cde0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cde0
void FUN_00b6cf70(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cf70
void FUN_00b6d060(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6d060
void FUN_00b6ca10(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6ca10
void FUN_00b6cba0(Event* e, int flag, const Vec2* pos, float dt);   // 0x00b6cba0
#define PVCAT(a, b) a##b
#define PVCAT2(a, b) PVCAT(a, b)
#define PVQ virtual void PVCAT2(pvq_, __COUNTER__)();
#define PVQ8 PVQ PVQ PVQ PVQ PVQ PVQ PVQ PVQ
struct IHostObj;
struct IWinObj {                                                // a label/tooltip window of a context record
    PVQ PVQ PVQ PVQ
    virtual IHostObj* GetHost();                                // +0x10
    PVQ PVQ PVQ PVQ PVQ
    virtual int V0A();                                          // +0x28
    PVQ PVQ PVQ
    virtual float* GetPos();                                    // +0x38
    PVQ8 PVQ PVQ PVQ PVQ PVQ
    virtual void SetPos(float x, float y);                      // +0x70
};
struct IHostObj {                                               // the host of a label window
    PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ8 PVQ PVQ
    virtual void V3A(IWinObj* w);                               // +0xe8
};
struct SimState_s00b6_d3c0 {                                               // the simulator's global state object
    char pad00[0x28];
    int mField28;                                               // +0x28
    int mField2c;                                               // +0x2c
    int mField30;                                               // +0x30
};
extern SimState_s00b6_d3c0* g_pSimState;                                   // 0x01687978
#define NEXT_SLOT(cur)                                                   \
    do {                                                                 \
        ++(cur);                                                         \
        g_slot01687968 = (cur);                                          \
        int index;                                                       \
        if ((cur) > 0x53dbcfe) {                                         \
            (cur) = 0x53dbcf3;                                           \
            g_slot01687968 = (cur);                                      \
            index = (int)((cur) - 0x53dbcf3);                            \
        }                                                                \
        else if ((cur) >= 0x53dbcf3) {                                   \
            index = (int)((cur) - 0x53dbcf3);                            \
        }                                                                \
        else {                                                           \
            index = 0;                                                   \
        }                                                                \
        if (g_slots0168795c[index] == 0)                                 \
            return;                                                      \
    } while (0)
struct cSimUIObject {
    void* GetInterface(uint32_t id);                            // 0x00b6e210
};
struct IStreamObj {
    PVQ PVQ PVQ PVQ PVQ PVQ
    virtual void* V6();                                         // +0x18
};
struct IStreamHost {
    PVQ8
    virtual IStreamObj* V8();                                   // +0x20
};
struct cVarListSerializer_s00b6_d3c0 {                                     // 0xa14-byte serializer, built on the stack
    uint8_t mData[0xa14];
    void Init(void* owner, void* dataset, uint32_t tag);         // 0x00692f90
    void Serialize(void* obj);                                  // 0x00692900
};
namespace EA {
namespace IO {
void WriteUint32(void* stream, const uint32_t* value, int count, int mode);   // 0x0093aa70
}
}
struct cSimulatorUIStore {
    void Save(IStreamHost* owner);                              // 0x00b6e2d0
};
// ---- items of slice s00b6d3c0 end

// ---- items of slice s00b6e3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t kEmptyW[2];  // @ 0x1667bac
extern unsigned int g_x1687968;  // @ 0x1687968
extern unsigned int g_x156b018;  // @ 0x156b018
extern bool g_used[12];          // @ 0x168795c
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);
void __cdecl EASTLFree(void* p);  // @ 0xF47380 operator delete[]
struct Vec3F {
  float x, y, z;
  Vec3F() {}
  Vec3F& operator=(const Vec3F& v) { x = v.x; y = v.y; z = v.z; return *this; }
  Vec3F(const Vec3F& v) : x(v.x), y(v.y), z(v.z) {}
};
struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);  // @ 0x921580
void RBTreeInsert(rbtree_node_base* pNode, rbtree_node_base* pNodeParent, rbtree_node_base* pNodeAnchor, int side);  // @ 0x9216a0
struct wstr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAlloc;
  wstr() : mpBegin(kEmptyW), mpEnd(kEmptyW), mpCapacity(kEmptyW + 1) {}
  ~wstr() {
    if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2 && mpBegin) EASTLFree(mpBegin);
  }
  wstr& assign(const wchar_t* b, const wchar_t* e);  // @ 0x423650
  wstr& append(const wchar_t* p);                    // @ 0x5c3d90
  wstr& operator=(const wstr& o);                    // @ 0x57cb60
  void RangeInitialize(const wchar_t* p);            // @ 0x579a90
};
struct cString_s00b6_e3d0 {
  unsigned int pad[5];  // 0x14 bytes: the ctor writes bytes +0x10/+0x11
  cString_s00b6_e3d0();                                                                // @ 0x6b5060
  cString_s00b6_e3d0(unsigned int tbl, unsigned int key, const wchar_t* def);          // @ 0x6b5770
  void Load(unsigned int tbl, unsigned int key, const wchar_t* def);        // @ 0x6b54b0
  const wchar_t* GetText();                                                 // @ 0x6b55c0
  ~cString_s00b6_e3d0();                                                               // @ 0x6b5240
};
struct ColorNode : rbtree_node_base {
  unsigned int key;  // +0x10
  Vec3 val;          // +0x14
};
struct ColorIter { ColorNode* n; ColorIter(ColorNode* p) : n(p) {} };
struct ColorMap {
  int mCompare;              // +0
  rbtree_node_base mAnchor;  // +4
  unsigned int mnSize;       // +0x14
  void DoNukeSubtree(ColorNode* p);                                        // @ 0x9a9600
  Vec3& Index(const unsigned int& key);   // original 0xb6ee40 map::operator[] (named so the checker can find it)
  ColorNode** DoInsertValueImpl(ColorNode** out, ColorNode* parent, const void* v, bool left);  // @ 0xb6eb30
  void DoInsertValue(ColorNode** out, ColorIter parent, const void* v, bool left);       // @ 0xb6ed20
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
};
extern ColorMap g_colorMap;  // @ 0x156b0b8
struct NameMap {
  int mCompare;
  rbtree_node_base mAnchor;
  unsigned int mnSize;
  void DoNukeSubtree(void* p);        // @ 0x801ef0
  NameMap() : mAnchor() { reset(); }
  ~NameMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
  void reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  void clear() {
    DoNukeSubtree(mAnchor.mpNodeParent);
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  wstr& operator[](const unsigned int& key);  // @ 0x688ad0
};
struct PropList {
  virtual void v0();
  virtual void Release();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual bool HasProperty(unsigned int id);  // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void* GetProperty(unsigned int id);  // +0x28 (property record)
};
struct PropMgr {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual bool GetPropertyList(unsigned int id, PropList** out);  // +0x30
};
PropMgr* GetPropMgr();  // @ 0x67de30
struct cStringTokenTranslator {
  int mRefCount;
  cStringTokenTranslator();  // @ 0x6b5870
  virtual ~cStringTokenTranslator();
  virtual void AddRef();
  virtual void Release();
  virtual bool Translate(const wchar_t* token, wstr* out);
};
struct StrNode_s00b6_e3d0 : rbtree_node_base {
  unsigned int key;
  const wchar_t* val;
};
struct StrMap_s00b6_e3d0 {
  int mCompare;
  rbtree_node_base mAnchor;
  unsigned int mnSize;
  StrNode_s00b6_e3d0* find(const unsigned int& key);  // @ 0xe5c780
};
struct StringSetT {
  char pad[8];
  StrMap_s00b6_e3d0 mMap;
  const wchar_t* Get(int idx);  // @ 0xb6a6e0
};
unsigned int FNV1_String16(const wchar_t* s, unsigned int basis, int lower);  // @ 0x932f30
struct ColorTranslator : cStringTokenTranslator {
  wstr mText0;        // +8
  wstr mText1;        // +0x18
  StringSetT* mSetA;  // +0x28
  StringSetT* mSetB;  // +0x2c
  StringSetT* mSetC;  // +0x30
  ColorTranslator() : mSetA(0), mSetB(0), mSetC(0) {}
  virtual ~ColorTranslator() {}
  virtual bool Translate(const wchar_t* token, wstr* out);
};
extern ColorTranslator* g_translator;  // @ 0x1687978
struct UIMgr_s00b6_e3d0 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void Register(ColorTranslator* t);    // +0x1c
  virtual void Unregister(ColorTranslator* t);  // +0x20
};
struct UIMgrHolder {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual UIMgr_s00b6_e3d0* GetMgr();  // +0x20
};
UIMgrHolder* GetUIHolder();  // @ 0x67de40
extern Vec3F g_defaultColor;      // @ 0x168796c
void RGBToHSL(Vec3 rgb, float* h, float* s, float* l);                // @ 0x67ff30
Vec3* HSLToRGB(Vec3* out, float h, float s, float l);                 // @ 0x67fe30
struct cColorSet {
  virtual ~cColorSet();
  unsigned int mKey;   // +4
  NameMap mNames;      // +8
  unsigned int mPad;   // +0x20
  Vec3F mDefault;      // +0x24
  cColorSet();
  void clear();
  void LoadNames(wstr* out);
  void NotifyTicker();
  unsigned int GetARGB();
};
static __forceinline int F2IS(const float* p) {
  return _mm_cvtt_ss2si(_mm_mul_ss(_mm_load_ss(p), _mm_set_ss(255.0f)));
}
static __forceinline unsigned int PackARGB(const Vec3& c) {
  return (((F2IS(&c.x) | 0xffffff00u) << 8 | (F2IS(&c.y) & 0xff)) << 8) | (F2IS(&c.z) & 0xff);
}
// ---- items of slice s00b6e3d0 end

// @ 0x00b63930
uchar __thiscall cGonzagoTimer::Read(void* ser)
{
    cVarListSerializer s((char*)this, &gSig2, 0x1a80d26);
    uchar r = s.SerializeB(ser);
    long long b = ((long long(__thiscall*)(void*))mGetMs)(this);
    mBase = b;
    return r;
}

// @ 0x00b639b0
void __thiscall WndObj::FSet(int id, char check)
{
    int want = check != 0;
    unsigned cur = IsDlgButtonChecked(hwnd, id);
    if ((unsigned)want != cur) {
        CheckDlgButton(hwnd, id, (unsigned)want);
    }
}

// @ 0x00b639f0
void __thiscall WndObj::FGet(int id, uchar* out)
{
    unsigned cur = IsDlgButtonChecked(hwnd, id);
    switch (cur) {
    case 0: *out = 0; break;
    case 1: *out = 1; break;
    }
}

// @ 0x00b63a20
uchar __thiscall Obj63A20::F(void* p)
{ (void)p; return 0; }

// @ 0x00b63b60
void Obj63B60::F()
{
    void* self = this;
    *(void**)self = &gVtbl63BD0;
    MapU32* a = (MapU32*)((char*)self + 0x1138);
    a->DoAllocateBuckets(*(uint*)((char*)self + 0x113c), *(uint*)((char*)self + 0x1140));
    *(uint*)((char*)self + 0x1144) = 0;
    if (*(uint*)((char*)self + 0x1140) > 1) opdel_check(*(void**)((char*)self + 0x113c));
    MapU32* b = (MapU32*)((char*)self + 0x1118);
    b->DoAllocateBuckets(*(uint*)((char*)self + 0x111c), *(uint*)((char*)self + 0x1120));
    *(uint*)((char*)self + 0x1124) = 0;
    if (*(uint*)((char*)self + 0x1120) > 1) opdel_check(*(void**)((char*)self + 0x111c));
}

// @ 0x00b63bd0
void __thiscall Obj63BD0::Init()
{
    *(void**)this = &gVtbl63BD0;
    *(float*)((char*)this + 0x1128) = 1.0f;
    *(float*)((char*)this + 0x112c) = 2.0f;
    *(uint*)((char*)this + 0x1120) = 1;
    *(uint*)((char*)this + 0x1124) = 0;
    *(uint*)((char*)this + 0x1130) = 0;
    *(void**)((char*)this + 0x111c) = &gMapEmpty;
    *(float*)((char*)this + 0x1148) = 1.0f;
    *(float*)((char*)this + 0x114c) = 2.0f;
    *(uint*)((char*)this + 0x1140) = 1;
    *(void**)((char*)this + 0x113c) = &gMapEmpty;
    *(uint*)((char*)this + 0x1144) = 0;
    *(uint*)((char*)this + 0x1150) = 0;
}

// @ 0x00b63c70
void __thiscall Obj63C70::F(void* menu, int x, int y, int w, int h, void* text)
{ (void)menu; (void)x; (void)y; (void)w; (void)h; (void)text; }

// @ 0x00b63d50
void __thiscall Obj63D50::F(void* menu, int x, int y, int w, int h, void* text)
{ (void)menu; (void)x; (void)y; (void)w; (void)h; (void)text; }

// @ 0x00b63e30
void* __cdecl FUN_00b63e30(void* a, float s)
{ (void)a; (void)s; return 0; }

// @ 0x00b63f70
int __cdecl FUN_00b63f70(int base, int n)
{
    if (n >= 0) {
        int* p = (int*)(base + 0x9c + n * 4);
        for (; n >= 0; n--, p--) {
            if (*p != 0) return n;
        }
    }
    return -1;
}

// @ 0x00b63fb0
int __cdecl FUN_00b63fb0(void* a)
{ (void)a; return 0; }

// @ 0x00b64040
void __cdecl FUN_00b64040()
{}

// @ 0x00b64390
void __cdecl FUN_00b64390(void* a, int* b, int* c)
{ (void)a; *b = 0; *c = 0; }

// @ 0x00b64870
bool BuildMeshGroup(cModelInstance* model, int index, const cSPTransform_s00b6_4470* xf, MGRef* out, int unusedA, int unusedB, int* numVerts, int* numTris)
{
    RefVec3 meshes;
    meshes.mpBegin = 0;
    meshes.mpEnd = 0;
    meshes.mpCap = 0;
    if (!model->GetMeshes(&meshes))
        return false;
    int count = (int)(meshes.mpEnd - meshes.mpBegin);
    if (index >= count) {
        out->Reset();
        return false;
    }
    out->AssignRefPtr(meshes.mpBegin[index]);
    FUN_00734d00(xf, out->p);
    FUN_00b64390(out->p, numVerts, numTris);
    return true;
}

// @ 0x00b65b10
void __cdecl FUN_00b65b10(const RadialRay* r, hkWorld_s00b6_5b10* world, RayObj* obj, bool useWorld, uint32_t filterInfo, RayHitResult* out)
{
    const hkReal h0 = r->m_h0;
    const hkReal h1 = r->m_h1;
    const hkReal span = (hkReal)fabs(h0 - h1);
    if (obj)
    {
        hkEntity_s00b6_5b10* ent = obj->m_entity;

        // radial direction of the position, rotated into the body's local frame
        hkVector4_s00b6_5b10 d(r->m_pos);
        const hkReal lenSq = d.x * d.x + d.z * d.z + d.y * d.y;
        const hkReal inv = (lenSq == 0.0f) ? 0.0f : hkSqrtInverse(lenSq);
        d.x *= inv; d.y *= inv; d.z *= inv; d.w *= inv;
        hkVector4_s00b6_5b10 dir;
        rotateByInverseQuat(dir, ent->m_motion->m_rotation, d);

        hkVector4_s00b6_5b10 local;
        local.setTransformedInversePos(ent->m_motion->m_transform, r->m_pos);

        hkShapeRayCastInput input;
        input.m_rayShapeCollectionFilter =
            world->m_collisionFilter ? (const void*)((char*)world->m_collisionFilter + 0x10) : 0;
        input.m_from.x = r->m_h0 * dir.x + local.x;
        input.m_from.y = dir.y * r->m_h0 + local.y;
        input.m_from.z = dir.z * r->m_h0 + local.z;
        input.m_from.w = dir.w * r->m_h0 + local.w;
        input.m_to.x = r->m_h1 * dir.x + local.x;
        input.m_to.y = dir.y * r->m_h1 + local.y;
        input.m_to.z = dir.z * r->m_h1 + local.z;
        input.m_to.w = dir.w * r->m_h1 + local.w;
        input.m_filterInfo = filterInfo;

        hkShapeRayCastOutput result;
        ent->m_shape->castRay(input, result);
        if (result.m_hitFraction < 1.0f)
        {
            out->m_status = 3;
            if (out->m_distOut)
                *out->m_distOut = result.m_hitFraction * span - r->m_h0;
            const hkReal t = result.m_hitFraction;
            const hkReal s = 1.0f - t;
            hkVector4_s00b6_5b10 p;
            p.x = s * input.m_from.x + t * input.m_to.x;
            p.y = t * input.m_to.y + s * input.m_from.y;
            p.z = t * input.m_to.z + s * input.m_from.z;
            p.w = t * input.m_to.w + s * input.m_from.w;
            out->m_pos.setTransformedPos(ent->m_motion->m_transform, p);
            if (out->m_normalOut)
                rotateByQuat(*out->m_normalOut, ent->m_motion->m_rotation, result.m_normal);
            if (ent->getProperty(0).type == 3)
                out->m_userData = ent->m_userData;
            out->m_entity = ent;
        }
        else
            out->m_status = 0;
        return;
    }
    if (!useWorld)
    {
        out->m_status = 0;
        return;
    }

    hkVector4_s00b6_5b10 up;
    FUN_00b65710(&up, r);
    hkWorldRayCastInput input;
    input.m_from.x = up.x * h0 + r->m_pos.x;
    input.m_from.y = up.y * h0 + r->m_pos.y;
    input.m_from.z = up.z * h0 + r->m_pos.z;
    input.m_from.w = up.w * h0 + r->m_pos.w;
    input.m_to.x = up.x * h1 + r->m_pos.x;
    input.m_to.y = up.y * h1 + r->m_pos.y;
    input.m_to.z = up.z * h1 + r->m_pos.z;
    input.m_to.w = up.w * h1 + r->m_pos.w;
    input.m_filterInfo = filterInfo;
    input.m_enableShapeCollectionFilter = false;

    hkClosestRayHitCollector collector;
    world->castRay(input, collector);
    const hkCollidable_s00b6_5b10* hit = collector.m_rayHit.m_rootCollidable;
    if (hit)
    {
        out->m_status = 3;
        if (out->m_distOut)
            *out->m_distOut = collector.m_rayHit.m_hitFraction * span - r->m_h0;
        const hkReal t = collector.m_rayHit.m_hitFraction;
        const hkReal s = 1.0f - t;
        out->m_pos.x = t * input.m_to.x + s * input.m_from.x;
        out->m_pos.y = t * input.m_to.y + s * input.m_from.y;
        out->m_pos.z = t * input.m_to.z + s * input.m_from.z;
        out->m_pos.w = t * input.m_to.w + s * input.m_from.w;
        if (out->m_normalOut)
            *out->m_normalOut = collector.m_rayHit.m_normal;
        if (hit->m_broadPhaseType == 1)
        {
            hkEntity_s00b6_5b10* ent = hit->getOwner();
            if (ent)
            {
                if (ent->getProperty(0).type == 3)
                    out->m_userData = ent->m_userData;
            }
            out->m_entity = ent;
        }
        else
            out->m_entity = 0;
    }
    else
        out->m_status = 0;
}

// @ 0x00b66460
void __cdecl FUN_00b66460(const RadialRay* r, hkWorld_s00b6_5b10* world, RayObjList* list, bool useWorld, uint32_t filterInfo, RayHitResult* out)
{
    out->m_status = 0;
    int count = list->m_count;
    if (count == 0 && useWorld)
    {
        FUN_00b65b10(r, world, 0, true, filterInfo, out);
        return;
    }
    RayHitResult hit;
    hkVector4_s00b6_5b10 normal;
    float dist;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = &normal;
    if (count > 0)
    {
        int i = 0;
        do
        {
            FUN_00b65b10(r, world, list->m_objects[i], false, filterInfo, &hit);
            if (hit.m_status != 0)
            {
                if (out->m_status != 0)
                {
                    float hitDist2 = hit.m_pos.z * hit.m_pos.z + hit.m_pos.y * hit.m_pos.y +
                                     hit.m_pos.x * hit.m_pos.x;
                    float outDist2 = out->m_pos.x * out->m_pos.x + out->m_pos.y * out->m_pos.y +
                                     out->m_pos.z * out->m_pos.z;
                    if (hitDist2 > outDist2)
                        out->FUN_00b655f0(&hit);
                    else
                        out->FUN_00b655f0(out);
                }
                else
                {
                    out->FUN_00b655f0(&hit);
                }
            }
            else if (out->m_status != 0)
            {
                out->FUN_00b655f0(out);
            }
            else
            {
                out->m_status = 0;
            }
            i++;
        } while (i < count);
    }
}

// @ 0x00b665c0
void __cdecl FUN_00b665c0(const RadialRay* r, cPlanetModel* planet, RayHitResult* out)
{
    Vec3 point;
    Vec3 normal;
    planet->FUN_00b816f0(&point, r);
    if (out->m_distOut)
    {
        float d = (float)(sqrt(r->m_pos.x * r->m_pos.x + r->m_pos.y * r->m_pos.y +
                              r->m_pos.z * r->m_pos.z) -
                          sqrt(point.x * point.x + (point.z * point.z + point.y * point.y)));
        *out->m_distOut = d;
    }
    if (out->m_normalOut)
    {
        hkVector4_s00b6_5b10* n = out->m_normalOut;
        if (planet->m_useSurfaceF0 != 0)
        {
            n->x = r->m_pos.x;
            n->y = r->m_pos.y;
            n->z = r->m_pos.z;
            hkVector4_s00b6_5b10 tmp;
            tmp.w = r->m_pos.w;
            n->w = tmp.w;
            n = out->m_normalOut;
            const hkReal lenSq = n->x * n->x + n->y * n->y + n->z * n->z;
            hkReal inv;
            if (lenSq != 0.0f)
                inv = hkSqrtInverse(lenSq);
            else
                inv = 0.0f;
            n->z *= inv;
            n->x *= inv;
            n->y *= inv;
            n->w *= inv;
        }
        else
        {
            Vec3* nrm = planet->GetNormalAt(&normal, &point);
            hkVector4_s00b6_5b10 nv;
            nv.x = nrm->x;
            nv.y = nrm->y;
            nv.z = nrm->z;
            nv.w = 0.0f;
            *out->m_normalOut = nv;
        }
    }
    out->m_pos.x = point.x;
    out->m_pos.y = point.y;
    out->m_pos.z = point.z;
    out->m_pos.w = 0.0f;
    out->m_status = 2;
}

// @ 0x00b66740
void __cdecl FUN_00b66740(const RadialRay* r, float h, cPlanetModel* planet, RayHitResult* out)
{
    Vec3 point;
    Vec3 normal;
    planet->FUN_00b82060(&point, r, *(int*)&h);
    if (out->m_distOut)
    {
        float d = (float)(sqrt(r->m_pos.x * r->m_pos.x + r->m_pos.y * r->m_pos.y +
                              r->m_pos.z * r->m_pos.z) -
                          sqrt(point.x * point.x + (point.z * point.z + point.y * point.y)));
        *out->m_distOut = d;
    }
    if (out->m_normalOut)
    {
        hkVector4_s00b6_5b10* n = out->m_normalOut;
        if (planet->m_useSurfaceF0 != 0)
        {
            n->x = r->m_pos.x;
            n->y = r->m_pos.y;
            n->z = r->m_pos.z;
            hkVector4_s00b6_5b10 tmp;
            tmp.w = r->m_pos.w;
            n->w = tmp.w;
            n = out->m_normalOut;
            const hkReal lenSq = n->x * n->x + n->y * n->y + n->z * n->z;
            hkReal inv;
            if (lenSq != 0.0f)
                inv = hkSqrtInverse(lenSq);
            else
                inv = 0.0f;
            n->z *= inv;
            n->x *= inv;
            n->y *= inv;
            n->w *= inv;
        }
        else
        {
            Vec3* nrm = planet->GetNormalAt(&normal, &point);
            hkVector4_s00b6_5b10 nv;
            nv.x = nrm->x;
            nv.y = nrm->y;
            nv.z = nrm->z;
            nv.w = 0.0f;
            *out->m_normalOut = nv;
        }
    }
    out->m_pos.x = point.x;
    out->m_pos.y = point.y;
    out->m_pos.z = point.z;
    out->m_pos.w = 0.0f;
    out->m_status = 2;
}

// @ 0x00b668c0
void __cdecl FUN_00b668c0(RadialRay* r, cPlanetModel* planet, hkWorld_s00b6_5b10* world, RayObj* obj, bool useWorld, RayHitResult* out, bool adjust)
{
    RayHitResult hit;
    hkVector4_s00b6_5b10 normal;
    float dist;
    float d;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = &normal;
    FUN_00b665c0(r, planet, out);
    if (adjust && out->m_status == 2)
    {
        d = (float)(sqrt(out->m_pos.x * out->m_pos.x + out->m_pos.y * out->m_pos.y +
                         out->m_pos.z * out->m_pos.z) -
                    sqrt(r->m_pos.x * r->m_pos.x + r->m_pos.y * r->m_pos.y +
                         r->m_pos.z * r->m_pos.z));
        r->m_h1 = min(r->m_h1, d);
    }
    FUN_00b65b10(r, world, obj, useWorld, 6, &hit);
    FUN_00b65660(out, &hit, out);
}

// @ 0x00b669b0
void __cdecl FUN_00b669b0(RadialRay* r, cPlanetModel* planet, hkWorld_s00b6_5b10* world, RayObjList* list, bool useWorld, RayHitResult* out, bool adjust)
{
    RayHitResult hit;
    hkVector4_s00b6_5b10 normal;
    float dist;
    float d;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = &normal;
    FUN_00b665c0(r, planet, out);
    if (adjust && out->m_status == 2)
    {
        d = (float)(sqrt(out->m_pos.x * out->m_pos.x + out->m_pos.y * out->m_pos.y +
                         out->m_pos.z * out->m_pos.z) -
                    sqrt(r->m_pos.x * r->m_pos.x + r->m_pos.y * r->m_pos.y +
                         r->m_pos.z * r->m_pos.z));
        r->m_h1 = min(r->m_h1, d);
    }
    FUN_00b66460(r, world, list, useWorld, 6, &hit);
    FUN_00b65660(out, &hit, out);
}

// @ 0x00b66aa0
void __cdecl FUN_00b66aa0(u32 ray, u32 obj, u32 a, u32 b, u32 filter, C103* out)
{
    C103 hit;
    float normal[4];
    float dist;

    hit.m_status = 0;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = normal;

    FUN_00b665c0(ray, obj, out);
    FUN_00b66460(ray, a, b, filter, 6, &hit);

    // Inlined C103::FUN_00b659f0 (the original passes its two C103 pointers and the ray in
    // ecx/eax/edi, a register ABI C++ cannot spell): keep the closer of `out` and `hit`, and
    // when both missed accept `out` only if it lies within the ray's [pt[5], pt[4]] range.
    C103* src = out;
    C103* other = &hit;
    float* pt = (float*)ray;
    if (src->m_status == 0) {
        if (other->m_status != 0) {
            out->m655f0(other);
            return;
        }
    } else if (other->m_status != 0) {
        float m0 = src->m_pos[0] * src->m_pos[0] + src->m_pos[1] * src->m_pos[1] +
                   src->m_pos[2] * src->m_pos[2];
        float m1 = other->m_pos[0] * other->m_pos[0] + other->m_pos[1] * other->m_pos[1] +
                   other->m_pos[2] * other->m_pos[2];
        if (m0 <= m1) {
            out->m655f0(other);
            return;
        }
        out->m655f0(src);
        return;
    }
    if (src->m_status != 0) {
        float dz = src->m_pos[2] - pt[2];
        float dx = src->m_pos[0] - pt[0];
        float dy = src->m_pos[1] - pt[1];
        float n[4];
        FUN_00b65710(n, pt);
        float dot = (n[0] * dx + n[1] * dy) + n[2] * dz;
        if (pt[4] >= dot && dot >= pt[5]) {
            out->m655f0(src);
            return;
        }
    }
    out->m_status = 0;
}

// @ 0x00b66b20
char __cdecl FUN_00b66b20(u32 id, void* shapeOwner, u32 filterInfo)
{
    void* found = FUN_00b53940(id);
    if (!found)
        return 0;
    void* other = *(void**)((char*)found + 0x1c);
    if (!other)
        return 0;

    float* box = ((GetAabbFn)(*(void***)shapeOwner)[0x68 / 4])(shapeOwner);
    float extent = box[3] - box[0];
    if (box[4] - box[1] > extent)
        extent = box[4] - box[1];
    if (box[5] - box[2] > extent)
        extent = box[5] - box[2];
    float radius = extent * 0.5f;

    void* gMem = *(void**)0x16e4178;
    void* mem = ((HkAllocFn)(*(void***)gMem)[0x10 / 4])(gMem, 0x10, 0x24);
    *(u16*)((char*)mem + 4) = 0x10;
    void* shape = FUN_010c3770(mem, 0, radius);

    float m[16];
    ((GetTransformFn)(*(void***)shapeOwner)[0x6c / 4])(shapeOwner, m);
    XYZW centre;
    centre.x = (m[3] + m[0]) * 0.5f;
    centre.y = (m[7] + m[4]) * 0.5f;
    centre.z = (m[11] + m[8]) * 0.5f;

    float world[16];
    world[0] = 1.0f;  world[1] = 0.0f;  world[2] = 0.0f;   world[3] = 0.0f;
    world[4] = 0.0f;  world[5] = 1.0f;  world[6] = 0.0f;   world[7] = 0.0f;
    world[8] = 0.0f;  world[9] = 0.0f;  world[10] = 1.0f;  world[11] = 0.0f;
    world[12] = centre.x; world[13] = centre.y; world[14] = centre.z; world[15] = 0.0f;

    char* physics = *(char**)0x167ecd0;
    void* hkWorld = *(void**)(physics + 0x80);

    int i0 = ((ShapeIndexFn)(*(void***)shape)[2])(shape);
    int i1 = ((ShapeIndexFn)(*(void***)other)[2])(other);
    u8 type = *(u8*)((char*)hkWorld + i1 * 0x20 + i0 + 400);
    void* dispatch = *(void**)((char*)hkWorld + 0x994 + type * 0x14);

    // two collidable/shape-instance records handed to the collision dispatcher
    char recA[0x20];
    *(void**)(recA + 0x00) = other;
    *(int*)(recA + 0x04) = -1;
    *(void**)(recA + 0x08) = (char*)*(void**)((char*)found + 0x58) + 0x10;
    *(int*)(recA + 0x0c) = 0;
    *(int*)(recA + 0x10) = 0;
    recA[0x14] = 0;
    recA[0x15] = (char)-0x14;         // self-relative offset of the record
    *(int*)(recA + 0x18) = 0;
    *(int*)(recA + 0x1c) = 0;

    char recB[0x2c];
    *(void**)(recB + 0x00) = shape;
    *(int*)(recB + 0x04) = -1;
    *(void**)(recB + 0x08) = world;
    *(int*)(recB + 0x0c) = 0;
    *(int*)(recB + 0x10) = 0;
    recB[0x14] = 0;
    recB[0x15] = (char)-0x14;
    *(int*)(recB + 0x18) = 0;
    *(void**)(recB + 0x24) = hkWorld;
    void* filter = *(void**)(physics + 0x7c);
    *(void**)(recB + 0x28) = filter ? (char*)filter + 0xc : 0;

    struct QueryResult { XYZW p; u32 k10; u32 k14; char hit; char pad[3]; u32 k1c; };
    QueryResult res;
    res.k10 = 0;
    res.k14 = 0;
    res.hit = 0;
    res.k1c = 0;
    res.p.x = 0; res.p.y = 0; res.p.z = 0; res.p.w = 0;
    res.p.w = *(float*)&filterInfo;

    ((void(__cdecl*)(void*, void*, void*, void*))dispatch)(&res.p, recA, recB, &res);

    if (*(u16*)((char*)shape + 4) != 0) {
        if (--*(u16*)((char*)shape + 6) == 0)
            ((ShapeDtorFn)(*(void***)shape)[0])(shape, 1);
    }
    return (char)(res.hit + 1);
}

// @ 0x00b66e40
void* __fastcall FUN_00b66e40(void* self)
{
    *(void**)self = (void*)0x146494c;
    *(void**)((char*)self + 0x10) = (char*)self + 0x20;
    *(u32*)((char*)self + 0x18) = 0x80000008;
    char* e = (char*)self + 0x20;
    for (int i = 0; i < 8; ++i) {
        *(float*)(e + 0x14) = 1.0f;
        *(u32*)(e + 0x20) = 0;
        e += 0x30;
    }
    *(u32*)((char*)self + 0x14) = 0;
    *(float*)((char*)self + 4) = 1.0f;
    return self;
}

// @ 0x00b66ed0
void __cdecl FUN_00b66ed0(const float* ray, void* world, u32 filterInfo, C103* out)
{
    RayInput in;
    in.from.x = ray[0];
    in.from.y = ray[1];
    in.from.z = ray[2];
    in.from.w = ray[3];
    float len = ray[8];
    in.to.x = ray[4] * len + in.from.x;
    in.to.y = ray[5] * len + in.from.y;
    in.to.z = ray[6] * len + in.from.z;
    in.to.w = ray[7] * len + in.from.w;
    in.enable = 0;
    in.filter = filterInfo;

    void* predicate = (void*)(unsigned)((const u32*)ray)[9];
    if (predicate == 0) {
        // Closest-hit collector: no heap allocation, root collidable at +0x30.
        ClosestHitCollector c;
        c.vt = (void*)0x1464944;
        c.earlyOut = 0x3f800000;
        c.normal[0] = 0.0f;
        c.pad20 = 0;
        c.rootCollidable = 0;
        c.hitFraction = 1.0f;
        ((HkWorld*)world)->castRay(&in, &c);
        float frac = c.hitFraction;
        void* collidable = c.rootCollidable;
        if (!collidable) {
            out->m_status = 0;
            return;
        }
        out->m_status = 3;
        if (out->m_distOut)
            *out->m_distOut = frac * ray[8];
        if (out->m_normalOut) {
            out->m_normalOut[0] = c.normal[0];
            out->m_normalOut[1] = c.normal[1];
            out->m_normalOut[2] = c.normal[2];
            out->m_normalOut[3] = c.normal[3];
        }
        float s = 1.0f - frac;
        out->m_pos[0] = frac * in.to.x + s * in.from.x;
        out->m_pos[1] = frac * in.to.y + s * in.from.y;
        out->m_pos[2] = frac * in.to.z + s * in.from.z;
        out->m_pos[3] = frac * in.to.w + s * in.from.w;
        if (*(u8*)((char*)collidable + 0x18) == 1) {
            void* ent = (char*)collidable + *(int*)((char*)collidable + 0x10);
            if (ent) {
                int local[2];
                if (*((D961*)ent)->Find(local, 0) == 3)
                    out->m_userData = *(u32*)((char*)ent + 0xc);
            }
        }
        return;
    }

    // All-hits collector: sort, then let the caller's predicate accept the first hit.
    AllHitsCollector c;
    FUN_00b66e40(&c);
    ((HkWorld*)world)->castRay(&in, &c);
    if (c.size == 0) {
        out->m_status = 0;
    } else {
        ((HkAllRayHitCollector*)&c)->sortHits();
        int n = c.size;
        out->m_status = 0;
        for (int i = 0; i < n; ++i) {
            HitEntry* e = &c.data[i];
            if (!((RayPredicate*)predicate)->accept(e))
                continue;
            out->m_status = 3;
            float frac = e->hitFraction;
            if (out->m_distOut)
                *out->m_distOut = frac * ray[8];
            if (out->m_normalOut) {
                out->m_normalOut[0] = e->normal[0];
                out->m_normalOut[1] = e->normal[1];
                out->m_normalOut[2] = e->normal[2];
                out->m_normalOut[3] = e->normal[3];
            }
            float s = 1.0f - frac;
            out->m_pos[0] = frac * in.to.x + s * in.from.x;
            out->m_pos[1] = frac * in.to.y + s * in.from.y;
            out->m_pos[2] = frac * in.to.z + s * in.from.z;
            out->m_pos[3] = frac * in.to.w + s * in.from.w;
            void* collidable = e->collidable;
            if (*(u8*)((char*)collidable + 0x18) == 1) {
                void* ent = (char*)collidable + *(int*)((char*)collidable + 0x10);
                if (ent) {
                    int local[2];
                    if (*((D961*)ent)->Find(local, 0) == 3)
                        out->m_userData = *(u32*)((char*)ent + 0xc);
                }
            }
            break;
        }
    }
    if (c.flags >= 0) {
        void* tls = ((TlsGetValueFn)*(void**)0x13cc2bc)(*(u32*)0x16e4174);
        ((HkT*)tls)->FUN_0107db10(c.data, (c.flags & 0x3fffffff) * 0x30, 0x14);
    }
}

// @ 0x00b672e0
void __cdecl FUN_00b672e0(u32 ray, u32 obj, u32 world, C103* out)
{
    C103 hit;
    float normal[4];
    float dist;

    hit.m_status = 0;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = normal;

    FUN_00b66740(ray, (char*)ray + 0x10, obj, out);
    FUN_00b66ed0((const float*)ray, (void*)world, 6, &hit);
    FUN_00b65660(out, &hit, out);
}

// @ 0x00b67360
void* __fastcall Collector_DeletingDtor(void* self, int, char flag)
{
    *(void**)self = (void*)0x146494c;
    _ReadWriteBarrier();
    u32 n = *(u32*)((char*)self + 0x18);
    if ((int)n >= 0) {
        n &= 0x3fffffff;
        void* tls = TlsGetValue(*(u32*)0x16e4174);
        ((HkT*)tls)->FUN_0107db10(*(void**)((char*)self + 0x10), n * 0x30, 0x14);
    }
    *(void**)self = (void*)0x14613b8;
    if (flag & 1)
        operator delete(self);
    return self;
}

// @ 0x00b673c0
bool __cdecl FUN_00b673c0(void* obj)
{
    int h = ((HashFn)(*(void***)obj)[0x38 / 4])(obj);
    switch (h) {
    case 0x0436f315:
    case 0x0116d858:
    case 0xb033b403:
    case 0xd0036e08:
    case 0x00ee02c7:
    case 0x0137e8e0:
    case 0x01a55e4d:
    case 0x01b92b27:
    case 0x1007ae63:
    case 0x04e3faaf:
    case 0x0ecade42:
    case 0x0ff10521:
    case 0x4f176642:
    case 0x4f396a66:
        return true;
    }
    return false;
}

// @ 0x00b67440
void __cdecl FUN_00b67440(u32 color, float alpha, void* self)
{
    void*** vt = (void***)self;
    if (alpha == 0.0f) {
        ((void(__thiscall*)(void*, int, int))(*vt)[0x7c / 4])(self, 1, 0);
        return;
    }
    u32 rgba;
    if (color == 0) {
        rgba = ((u32)(int)(alpha * 255.0f) << 24) | 0xffffff;
    } else {
        rgba = ((u32)(int)(alpha * 255.0f) << 24) |
               (*(u32(__cdecl**)(u32))0x00458a40)(color) & 0xffffff;
    }
    ((void(__thiscall*)(void*, u32))(*vt)[0x5c / 4])(self, rgba);
    ((void(__thiscall*)(void*, int, int))(*vt)[0x7c / 4])(self, 1, 1);
}

// @ 0x00b674d0
int __cdecl FUN_00b674d0(u32 mode)
{
    switch (mode) {
    case 0: return -1;
    case 1: return 5;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 5: return 0;
    case 6: return 4;
    }
    return -1;
}

// @ 0x00b67530
int __cdecl FUN_00b67530(u32 mode, char flag)
{
    if (flag != 0)
        return 7;
    switch (mode) {
    case 0: return -1;
    case 1: return 2;
    case 2: return 1;
    case 3: return 3;
    case 4: return 4;
    case 5: return 0;
    case 6: return 5;
    case 7: return 6;
    }
    return -1;
}

// @ 0x00b675a0
int __cdecl FUN_00b675a0(u32 mode)
{
    switch (mode) {
    case 7: return 0;
    case 1: return 2;
    case 8: return 3;
    case 3: return 4;
    case 2: return 5;
    case 5: return 6;
    case 6: return 7;
    case 4: return 8;
    case 9: return 9;
    default: return -1;
    }
}

// @ 0x00b67610
int __cdecl FUN_00b67610(int key)
{
    switch (key) {
    case 0xd0036e08: return 1;
    case 0xb033b403: return 0x40;
    case 0x0137e8e0: return 4;
    case 0x00ee02c7: return 8;
    case 0x0116d858: return 8;
    case 0x0ff10521: return 0x10;
    case 0x0ecade42: return 0x10;
    case 0x01a55e4d: return 0x10;
    case 0x1007ae63: return 0x10;
    case 0x0436f315: return 0x20;
    case 0x4f176642: return 2;
    }
    return 0;
}

// @ 0x00b676a0
void __cdecl FUN_00b676a0(void)
{
    char* p = *(char**)0x1687348;
    if (p)
        p[0x30] = (char)(p[0x30] == 0);
}

// @ 0x00b677a0
u32 __cdecl FUN_00b677a0(u32 key)
{
    if (SP_GetCurrentGameMode() == (void*)0x01654c10) {
        ModeObj* o = *(ModeObj**)0x016c7aa4;
        ModeTable* t = (ModeTable*)o->m_table;
        u32 k = key;
        int icon = t->FUN_00f3e900(k);
        if (icon != 0)
            return ResourceKeyToIcon(icon);
    }
    return 0x867a9ee9;
}

// @ 0x00b677e0
Vec3 FUN_00b677e0(Obj* o)
{
	Vec3 out;

	if (SP_GetCurrentGameMode() == &DAT_01654c10)
	{
		switch ((int)FUN_00eec990(o))
		{
		case 2:
			out.x = DAT_01687910[0]; out.y = DAT_01687910[1]; out.z = DAT_01687910[2];
			return out;
		case 3:
			out.x = DAT_0168791c[0]; out.y = DAT_0168791c[1]; out.z = DAT_0168791c[2];
			return out;
		case 4:
			out.x = DAT_01687928[0]; out.y = DAT_01687928[1]; out.z = DAT_01687928[2];
			return out;
		case 5:
			out.x = DAT_01687934[0]; out.y = DAT_01687934[1]; out.z = DAT_01687934[2];
			return out;
		default:
			out.x = DAT_0156b008[0]; out.y = DAT_0156b008[1]; out.z = DAT_0156b008[2];
			return out;
		}
	}

	switch (o->vt->type(o))
	{
	case 0x436f315:
	case 0xee9b2232:
	case 0x137e8e0:
	case 0x1a55e4d:
	case 0xff10521:
	case 0x70704db:
	case 0xecade42:
	case 0x1007ae63:
		{
			void* v = ((NounMgr*)SP_NounManager())->Func_b25f40(o->vt->m4c(o));
			if (v != 0)
				return *(Vec3*)((char*)v + 0xc4);
		}
		break;

	case 0x116d858:
		{
			void* v = ((ObjC9d9e0*)FUN_00b18700(o))->Func_c9d9e0();
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	case 0xb033b403:
		{
			int id = o->vt->m4c(o);
			EmpireObj* e = (EmpireObj*)((StarMgr*)SP_StarManager())->Func_ba9370(id);
			if (e != 0)
				return e->GetColor();
		}
		break;

	case 0xd0036e08:
		if (FUN_00b18760(o) != 0)
		{
			if ((DAT_01687958 & 1) == 0)
			{
				DAT_01687958 |= 1;
				DAT_0168794c = DAT_01485720;
				DAT_01687950 = DAT_013f6b64;
				DAT_01687954 = DAT_01464988;
			}
			out.x = DAT_0168794c; out.y = DAT_01687950; out.z = DAT_01687954;
			return out;
		}
		break;

	case 0xee02c7:
		{
			Obj* p = (Obj*)FUN_00b676e0(o);
			if (p != 0)
			{
				Obj* q = (Obj*)p->vt->m5c(p);
				if (q != 0)
					return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)q + 0x234)));
			}
		}
		break;

	case 0x629baec:
		{
			void* v = (void*)*(int*)((char*)FUN_00b676c0(o) + 0x10c);
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	case 0x4f176642:
		{
			Obj* p = (Obj*)FUN_00c0c380(o);
			return *(Vec3*)p->vt->me0(p);
		}

	case 0x4f396a66:
		{
			void* v = FUN_00ac80d0(o, 0x18c6d19);
			if (v != 0)
				return *(Vec3*)((char*)FUN_00b6f0c0(*(int*)((char*)v + 0x234)));
		}
		break;

	default:
		break;
	}

	out.x = DAT_0156b008[0]; out.y = DAT_0156b008[1]; out.z = DAT_0156b008[2];
	return out;
}

// @ 0x00b67b90
int FUN_00b67b90(Obj* o)
{
	void* p = o != 0 ? o->vt->query(o, 0x13f94d4) : 0;

	switch (o->vt->type(o))
	{
	case 0x436f315:
	case 0x116d858:
	case 0xb033b403:
	case 0xd0036e08:
	case 0xee02c7:
	case 0x137e8e0:
	case 0x1a55e4d:
	case 0xff10521:
	case 0x4e3faaf:
	case 0x70704db:
	case 0xecade42:
	case 0x1007ae63:
	case 0x4f176642:
		{
			float f = *(float*)((char*)p + 0x38);
			int n = _mm_cvtss_si32(_mm_set_ss(f));
			if ((float)n < f)
				n++;
			return n;
		}
	case 0xee9b2232:
		return 0;
	case 0x1b92b27:
		return 0;
	default:
		return 0;
	}
}

// @ 0x00b67c70
int FUN_00b67c70(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x436f315:
		return 9;
	case 0x116d858:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x116d858);
			if (p != 0 && p->vt->m58(p) == 10)
				return 0x11;
			return 2;
		}
	case 0xee9b2232:
		return 7;
	case 0xb033b403:
		return 0xb;
	case 0xd0036e08:
		return 0xc;
	case 0xee02c7:
		return 4;
	case 0x137e8e0:
		return 6;
	case 0x1a55e4d:
		return 9;
	case 0x1b92b27:
		return 0xe;
	case 0xff10521:
		return 9;
	case 0x4e3faaf:
		return 10;
	case 0x70704db:
		return 9;
	case 0xecade42:
		return 9;
	case 0x1007ae63:
		return 8;
	case 0x4f176642:
		return 3;
	case 0x4f396a66:
		return 5;
	case 0x629baec:
		return 0xd;
	default:
		{
			int h = FUN_00b677a0(o);
			if (h == (int)0xcf56099a || h == 0x6031c03a)
				return 0x10;
			return 0x11;
		}
	}
}

// @ 0x00b67dc0
bool FUN_00b67dc0(const Vec3* in, Vec2* out)
{
	App* app = (App*)SP_App();
	float* m = (float*)app->vt->m58(app);
	float x = in->x, y = in->y, z = in->z;

	float w = DAT_01687948 * (m[0x68 / 4] * z + m[0x48 / 4] * x + m[0x58 / 4] * y + m[0x78 / 4])
	        + DAT_01687940 * (m[0x60 / 4] * z + m[0x50 / 4] * y + m[0x40 / 4] * x + m[0x70 / 4])
	        + DAT_01687944 * (m[0x64 / 4] * z + m[0x44 / 4] * x + m[0x54 / 4] * y + m[0x74 / 4]);

	if (w < 0.0f)
		return false;

	Vec2 p;
	app->Transform(&p, in);
	*out = p;

	return p.x <= DAT_01485720 && p.x >= DAT_013eb1bc &&
	       p.y <= DAT_01485720 && p.y >= DAT_013eb1bc;
}

// @ 0x00b67ef0
bool FUN_00b67ef0(Obj* o, Vec2* out, Vec2* out2)
{
	float def[6] = { DAT_013ec488, DAT_013ec488, 0.0f,
	                 DAT_01471064, DAT_01471064, DAT_01485720 };
	float* pos;

	if ((*(unsigned int*)((char*)o + 0x50) & 0x10) == 0 ||
	    (*(unsigned int*)((char*)o + 0x50) & 0x20) != 0)
		pos = o->vt->m68(o);
	else
		pos = def;

	float h = pos[5];
	float* v = o->vt->m2c(o);
	float x = v[0], y = v[1], z = v[2];
	float inv = 1.0f / sqrtf(x * x + y * y + z * z);

	Vec3 p;
	p.x = x + (inv * x) * h;
	p.y = y + (inv * y) * h;
	p.z = z + (inv * z) * h;

	Vec2 s;
	bool ok = FUN_00b67dc0(&p, &s);

	FUN_00805ea0((Vec4*)def);

	float fx = ((s.x + DAT_01485720) * def[2]) * DAT_01471064;
	float fy = ((DAT_01485720 - s.y) * def[3]) * DAT_01471064;

	out->x = fx;
	out->y = fy;
	if (out2 != 0)
	{
		out2->x = fx;
		out2->y = fy;
	}

	return FUN_00c88e30(o) == 0 && ok;
}

// @ 0x00b68090
int FUN_00b68090(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0xee9b2232:
	case 0x901f1362:
	case 0xb033b403:
	case 0x4f396a66:
		break;
	default:
		return 0;
	}

	int player;
	if (SP_GetCurrentGameMode() == &DAT_01654c02)
	{
		Obj* t = (Obj*)((NounMgr*)SP_NounManager())->Func_bfc5f0();
		player = t->vt->m4c(t);
	}
	else if (SP_GetCurrentGameMode() == &DAT_01654c05)
	{
		player = FUN_01021090();
	}
	else
	{
		player = ((NounMgr*)SP_NounManager())->Func_b1f9d0();
	}

	int owner = o->vt->m4c(o);
	if (player == owner)
		return 0;
	if (owner == -1)
		return 5;

	Obj* c = (Obj*)o->vt->query(o, 0xb033b403);
	if (c != 0 && ((ObjC37710*)c)->Func_c37710() != 0)
	{
		if (!((RelMgr*)SP_RelationshipManager())->Func_d01b50(owner, player))
		{
			void* v = FUN_00b67700(((ObjC37710*)c)->Func_c37710());
			if (v != 0 && *(char*)((char*)v + 0x21c) != 0)
				return 5;
		}
	}

	switch (((RelMgr*)SP_RelationshipManager())->Func_d00a70(owner, player, 1))
	{
	case 0:
		return 5;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	case 4:
		return 6;
	}
	return 0;
}

// @ 0x00b681d0
int FUN_00b681d0(Obj* o)
{
	void* tribe = 0;

	if (o != 0)
	{
		if (o->vt->m20(o) == 0x18c6d19)
		{
			tribe = o;
		}
		else
		{
			Obj* p = (Obj*)o->vt->query(o, 0xee02c7);
			if (p != 0)
				tribe = p->vt->m5c(p);
		}
	}

	if (tribe == 0)
		return 0;

	int max = ((TribeObj*)tribe)->GetMaxPopulation();
	for (int i = 0; i < 7; i++)
	{
		int v = FUN_00c00ad0(i);
		if (v >= max)
			return v;
	}
	return ((TribeObj*)tribe)->GetMaxPopulation();
}

// @ 0x00b68250
int FUN_00b68250(Obj* o)
{
	if (o != 0)
	{
		if (o->vt->m20(o) == 0x18c6d19)
		{
			TribeObj* t = (TribeObj*)o;
			return t->GetAdultPopulation();
		}

		Obj* p = (Obj*)o->vt->query(o, 0xee02c7);
		if (p == 0)
			return 0;
		TribeObj* t = (TribeObj*)p->vt->m5c(p);
		if (t == 0)
			return 0;
		return t->GetAdultPopulation();
	}
	return 0;
}

// @ 0x00b682a0
int FUN_00b682a0(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x436f315:
		{
			void* v = ((ObjBce5c0*)o->vt->query(o, 0x436f315))->Func_bce5c0();
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0x116d858:
		{
			void* v = ((ObjC9d9e0*)o->vt->query(o, 0x116d858))->Func_c9d9e0();
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0xee9b2232:
		{
			void* v = FUN_00ac86d0(o);
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}
	case 0xb033b403:
		return FUN_00b68090(o);

	case 0xd0036e08:
		{
			Obj* c = (Obj*)FUN_00ac8960(o);
			char* v = (char*)((ObjC04750*)c)->Func_c04750();
			if (v != 0 && *(int*)(v + 0x4ac) == 3 && *(char*)(v + 0x4c8) == 0)
				return 0;
			if ((*(unsigned int*)((char*)c + 0xb58) >> 8) & 1)
				return 6;
			if (((*(unsigned int*)((char*)c + 0xb58) >> 4) & 1) && c->vt->md0(c))
				return 7;
			return (int)((PlacementObj*)FUN_00b3d4c0())->Func_ba3f90((char*)c + 0xb28, c, 0);
		}

	case 0xee02c7:
		{
			Obj* p = (Obj*)FUN_00b676e0(o);
			Obj* v = (Obj*)p->vt->m5c(p);
			if (v == 0)
				return 0;
			return FUN_00b68090(v);
		}

	case 0x137e8e0:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x137e8e0);
			if (SP_GetCurrentGameMode() == &DAT_01654c10)
				return 0;
			void* v = ((NounMgr*)SP_NounManager())->Func_b25f40(p->vt->m4c(p));
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}

	case 0x1b92b27:
		{
			char* x = (char*)FUN_00b1fc00(o);
			if (x == 0)
				return 0;
			if (*(int*)(x + 0x128) == 0)
				return 0;
			if ((*(unsigned char*)(x + 0x124) & 1) == 0)
				return 0;
			int base = *(int*)(*(int*)(x + 0x128) + 0xa4) + 0x504;
			int v = (int)((PlacementObj*)FUN_00b3d4c0())->Func_ba3f90((void*)base, 0, 0);
			if (v == 0)
			{
				char* s = (char*)*(int*)(x + 0x128);
				void* a = ((SpeciesMgr*)FUN_00401090())->Func_4e0050(
					*(int*)(s + 0x88), *(int*)(s + 0xf0));
				if (a != 0)
					v = *(int*)((char*)a + 0x390);
			}
			return v;
		}

	case 0x1a55e4d:
	case 0xff10521:
	case 0xecade42:
	case 0x1007ae63:
		{
			Obj* p = (Obj*)o->vt->query(o, 0xe9cb8ba);
			void* v = p->vt->m84(p);
			if (v == 0)
				return 0;
			return FUN_00b68090((Obj*)v);
		}

	case 0x4e3faaf:
	case 0x70704db:
		return 0;

	case 0x4f176642:
		{
			CitizenObj* p = (CitizenObj*)o->vt->query(o, 0x4f176642);
			if (p->Func_c232c0())
			{
				void* t = p->Func_c22f50();
				if (t == 0)
					return 0;
				return FUN_00b68090((Obj*)t);
			}
			void* c = p->Func_c23e40();
			if (c == 0)
				return 0;
			return FUN_00b68090((Obj*)c);
		}

	case 0x4f396a66:
		{
			void* t = FUN_00ac80d0(o, 0x18c6d19);
			if (t == 0)
				return 0;
			return FUN_00b68090((Obj*)t);
		}

	case 0x629baec:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x629baec);
			return FUN_00b68090((Obj*)p->vt->m30(p));
		}

	default:
		return 0;
	}
}

// @ 0x00b685e0
float FUN_00b685e0(Obj* o)
{
	switch (o->vt->type(o))
	{
	case 0x116d858:
	case 0xb033b403:
	case 0xd0036e08:
	case 0xee02c7:
	case 0x1a55e4d:
	case 0x137e8e0:
	case 0xecade42:
	case 0x4e3faaf:
	case 0x436f315:
	case 0x70704db:
	case 0x4f176642:
	case 0xff10521:
	case 0x1007ae63:
		{
			Obj* p = (Obj*)o->vt->query(o, 0x13f94d4);
			return ((PropObj*)p)->Func_bfc490();
		}
	case 0x2a8fe3c:
		return 0.0f;
	case 0xee9b2232:
		return 0.0f;
	case 0x175cdc9:
		return 0.0f;
	case 0x1b92b27:
		return 0.0f;
	case 0x3a25119:
		return 0.0f;
	default:
		return 0.0f;
	}
}

// @ 0x00b686a0
void FUN_00b686a0(int* entry)
{
	int* e = (int*)((LabelMgr*)g_pLabelMgr)->Func_b721d0(entry);
	if (e == 0 || e[0x50 / 4] == 0)
		return;

	if (SP_GetCurrentGameMode() == &DAT_01654c02)
	{
		Obj* o = (Obj*)e[1];
		if (o->vt->type(o) == 0xee02c7)
		{
			char* s = (char*)FUN_00cd40b0();
			if (s != 0)
				s += 4;
			else
				s = 0;
			Obj* c = (Obj*)e[0xac / 4];
			c->vt->m108(c, s);
		}
	}

	((LayoutObj*)e[0x50 / 4])->Func_811ad0(1);

	Obj* p = (Obj*)e[0x50 / 4];
	if (p != 0)
	{
		e[0x50 / 4] = 0;
		p->vt->m08(p);
	}
}

// @ 0x00b68720
int __cdecl FindWindow(unsigned char flags)
{
    int key = gManager->GetPriority();
    Obj_s00b6_8720* o;
    while ((o = gManager->Find(key)) != 0) {
        if (o->mField4 != 0) {
            if ((flags & 8) != 0) {
                if (o->mFieldBC != 0)
                    return o->mField4;
            } else if ((flags & 2) != 0) {
                if (o->m50 != 0 && o->m44 == 0.0f)
                    return o->mField4;
            } else if ((flags & 4) != 0) {
                if (o->m50 != 0 && o->m44 != 0.0f)
                    return o->mField4;
            } else if ((flags & 0x10) != 0) {
                if (o->m120 != 0)
                    return o->mField4;
            }
        }
    }
    return 0;
}

// @ 0x00b687d0
int __cdecl FindOrCreate(int* value)
{
    int key = gManager->GetPriority();
    int* o;
    while ((o = (int*)gManager->Find(key)) != 0) {
        if ((int*)o[1] == value)
            return *o;
    }

    int handle = gManager->Alloc();             // 0x00b72160
    if (handle == 0)
        return 0;
    Obj_s00b6_8720* rec = (Obj_s00b6_8720*)gManager->Make(handle);    // 0x00b72210
    int* old = (int*)rec->mField4;
    if (value != old) {
        if (value != 0)
            (*(void(__thiscall**)(int*))value[0])(value);            // slot 0
        rec->mField4 = (int)value;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 4))(old);          // slot 1
    }
    rec->m1c = 0.0f;
    rec->m30 = 0.0f;
    rec->m28 = 0.0f;
    rec->m24 = 0.0f;
    rec->m2c = 0.0f;
    rec->m38 = 0.0f;
    rec->m3c = 0.0f;
    rec->m40 = 0.0f;
    rec->m44 = 0.0f;
    rec->m48 = 0x7f7fffff;
    rec->m4c = 0x7f7fffff;
    int* p = (int*)rec->m50;
    if (p != 0) {
        rec->m50 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m118 = 0x075f3ea8;
    p = (int*)rec->mb8;
    if (p != 0) {
        rec->mb8 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m11c = 0.0f;
    p = (int*)rec->m120;
    if (p != 0) {
        rec->m120 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 4))(p);                  // slot 1
    }
    rec->m124 = 0;
    rec->m128 = 0;
    return handle;
}

// @ 0x00b68910
void FUN_00b68910(void* pOwner, Obj_s00b6_8720* self)
{
    void* pWin = 0;
    if (pOwner != 0)
        pWin = (*(void*(__thiscall**)(void*, void*))(*(int*)pOwner + 0x0c))(pOwner, (void*)&gVtbl13f94d4);
    self->m34 = 0;
    if (pWin == 0)
        return;
    if (!FUN_00bfc480())
        return;

    self->m34 = 1;
    if (self->m64 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m64 + 0x7c))((void*)self->m64, 1, 0);
    if (self->m68 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m68 + 0x7c))((void*)self->m68, 1, 0);
    if (self->m6c != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m6c + 0x7c))((void*)self->m6c, 1, 0);
    if (self->m74 != 0)
        (*(void(__thiscall**)(void*, int, int))(*(int*)self->m74 + 0x7c))((void*)self->m74, 1, 0);

    // cSPUILayout instance (0x18 bytes); ctor/Init/Shutdown/dtor are the same
    // thiscall helpers the original invokes, modelled with an explicit self.
    char layout[0x18];
    cConnectionDialog_ctor(layout);
    if (!cSPUILayout_Init(layout, kRolloverInvulnName, 0x40464100, 0, 0x5b598fa)) {
        cSPUILayout_dtor(layout);
        return;
    }

    void* pItem = cSPUILayout_FindWindowByID(layout, 0x26e0df3, 1);
    if (pItem != 0)
        (*(void(__thiscall**)(void*))(*(int*)pItem + 0x00))(pItem);
    void* pR = (*(void*(__thiscall**)(void*))(*(int*)pItem + 0x10))(pItem);
    if (pR != 0) {
        void* pR2 = (*(void*(__thiscall**)(void*))(*(int*)pItem + 0x10))(pItem);
        (*(void(__thiscall**)(void*, void*))(*(int*)pR2 + 0xdc))(pR2, pItem);
    }
    cSPUILayout_Shutdown(layout, 1);

    void* pPanel = (void*)self->m70;
    (*(void(__thiscall**)(void*, void*))(*(int*)pPanel + 0xd8))(pPanel, pItem);
    (*(void(__thiscall**)(void*, float, float))(*(int*)pItem + 0x70))(pItem, 0.0f, 0.0f);

    const Rect* a = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pPanel + 0x38))(pPanel);
    float height = a->bottom - a->top;
    const Rect* b = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pPanel + 0x38))(pPanel);
    float width = b->right - b->left;
    (*(void(__thiscall**)(void*, float, float))(*(int*)pItem + 0x74))(pItem, width, height);
    AnchorWindowToWindow(pPanel, pItem, 0x300, 0);
    (*(void(__thiscall**)(void*))(*(int*)pItem + 0x04))(pItem);

    cSPUILayout_dtor(layout);
}

// @ 0x00b68aa0
int __cdecl sFindOrCreateUI(int* param_1, int param_2, float param_3)
{
    int handle = FUN_00b687d0(param_1);
    Obj_s00b6_8720* rec = gManager->Make(handle);
    if (rec->m50 != 0)
        return (int)rec;

    if (param_3 == -1.0f)
        param_3 = FUN_00b685e0(param_1);

    rec->m1c = param_3;
    rec->m30 = param_3;
    rec->m28 = param_3;

    int* nw = (int*)operator_new(0x18, "Simulator/HealthBar", 0, 0, 0, 0);
    int* win = 0;
    if (nw != 0)
        win = (int*)SPUIHelpers_CenterWindowInRect(nw);

    int* old = (int*)rec->m50;
    if (win != old) {
        if (win != 0)
            (*(void(__thiscall**)(int*))(win[0] + 4))(win);      // slot 1
        rec->m50 = (int)win;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 8))(old);      // slot 2
    }

    void* mode = GetCurrentGameMode();
    unsigned flags;
    const wchar_t* name;
    switch (param_2) {
    case 2:  flags = 0xe9f70df9; name = kLayout_TribeTool;        break;
    case 3:  flags = 0xe9f70df9; name = kLayout_TribeCitizen;     break;
    case 4:  flags = 0xe9f70df9; name = kLayout_TribeHut;         break;
    case 5:  flags = 0x5b598f6;  name = kLayout_TribeMinimap;     break;
    case 6:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c10) ? kLayout_ScenarioVehicle : kLayout_CivVehicle;
        break;
    case 7:
        if (mode != (void*)0x01654c05)
            goto default_case;
        flags = 0x5b598f6;  name = kLayout_CityMinimap;           break;
    case 8:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c05) ? kLayout_SpaceCity : kLayout_SharedHealthBar;
        break;
    case 9:  flags = 0xe9f70df9; name = kLayout_Building;         break;
    case 11: flags = 0xe9f70df9; name = kLayout_UFO;              break;
    case 12:
        if (mode != (void*)0x01654c01 && mode != (void*)0x01654c10)
            goto default_case;
        flags = 0xe9f70df9;  name = kLayout_Creature;             break;
    case 14: flags = 0x5b598f6;  name = kLayout_CRGMinimap;       break;
    case 16: flags = 0xe9f70df9; name = kLayout_FixedObject;      break;
    default:
    default_case:
        flags = 0xe9f70df9;  name = kLayout_SharedHealthBar;      break;
    }

    cSPUILayout_Init((void*)rec->m50, name, 0x40464100, 1, flags);

    cSPUILayout_s00b6_8720* lay = (cSPUILayout_s00b6_8720*)rec->m50;
    if (lay != 0)
        (*(void(__thiscall**)(cSPUILayout_s00b6_8720*, int))(*(int*)lay + 0x7c))(lay, 1);  // SetVisibility

    rec->m54 = (int)lay->FindWindowByID(0x93310e4a, 1);
    rec->m58 = (int)lay->FindWindowByID(0x933103eb, 1);
    rec->m5c = (int)lay->FindWindowByID(0x31e94d0, 1);
    rec->m60 = (int)lay->FindWindowByID(0x933103ea, 1);
    rec->m64 = (int)lay->FindWindowByID(0x26e0df0, 1);
    rec->m68 = (int)lay->FindWindowByID(0x26e0df1, 1);
    rec->m6c = (int)lay->FindWindowByID(0x26e0df2, 1);
    rec->m70 = (int)lay->FindWindowByID(0x26e0df3, 1);
    rec->m74 = (int)lay->FindWindowByID(0x46adf86, 1);
    rec->m78 = (int)lay->FindWindowByID(0x3caf1f4, 1);
    rec->m7c = (int)lay->FindWindowByID(0x2b0e0f6, 1);
    rec->m80 = (int)lay->FindWindowByID(0x3f8a0d2, 1);
    rec->m84 = (int)lay->FindWindowByID(0x4c1f3a0, 1);
    rec->m88 = (int)lay->FindWindowByID(0x5d2a1b9, 1);
    rec->m8c = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w90 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    if (w90 != 0) {
        int* p = w90;
        int* r = 0;
        if (w90 != 0)
            r = (int*)(*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
        rec->m90 = (int)r;
    }
    rec->m94 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->m98 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w74 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->m74 = (int)w74;
    if (w74 != 0) {
        unsigned vis = *((unsigned char*)gManager + 0x30);
        (*(void(__thiscall**)(int*, unsigned, int))(*(int*)w74 + 0x7c))(w74, vis, 1);
    }
    FUN_00b68910(param_1, rec);
    rec->m9c = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma0 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma4 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma8 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* wac = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mac = (int)wac;
    if (wac != 0 && GetCurrentGameMode() == (void*)0x01654c02) {
        int gm = (*(int(__thiscall**)(int*))(*param_1 + 0x38))(param_1);
        if (gm == 0xee02c7) {
            int inst = TribeModeStrategyInstance();
            void* arg = (inst == 0) ? 0 : (void*)(inst + 4);
            (*(void(__thiscall**)(int*, void*))(wac[0] + 0x104))(wac, arg);
        }
    }

    int* p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb0 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
    p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb4 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);

    return (int)rec;
}

// @ 0x00b69010
bool FUN_00b69010(float target, float dt, Obj_s00b6_8720* self)
{
    // damage-glow decay (inline clamp at 0x00b6904a)
    self->m44 = Clamp01Inline(self->m44 - gManager->mGlowDecay * dt);

    self->m20 = target;
    if (target > self->m1c) {
        self->m28 = target;
        self->m30 = target;
    }
    if (self->m1c == kProbeLimit)
        self->m1c = target;

    if (self->m40 > 0.0f) {
        self->m40 -= dt;
        return self->m38 > 0.0f;
    }

    // flash still growing
    if (self->m38 < 1.0f) {
        if (self->m1c != target) {
            self->m38 = Clamp01Inline(self->m38 + gManager->mRefillRate * dt);
            if (self->m44 > self->m38)
                self->m38 = self->m44;
        }
        return self->m38 > 0.0f;
    }

    // bar below target: ramp the chase value down, then the bar up
    if (target > self->m1c) {
        if (self->m24 > 0.0f)
            self->m24 = Clamp01Inline(self->m24 - gManager->mRefillRate * dt);
        if (self->m2c < 1.0f) {
            self->m2c = Clamp01Inline(self->m2c + gManager->mRefillRate * dt);
        } else {
            self->m1c += gManager->mDrainRate * dt;
            if (self->m1c >= self->m20)
                self->m1c = self->m20;
        }
        return self->m38 > 0.0f;
    }

    // bar above target: drain the cooldown, then chase or snap
    if (target < self->m1c) {
        bool cooldownWasZero = true;
        if (self->m2c > 0.0f) {
            self->m2c = Clamp01Inline(self->m2c - gManager->mRefillRate * dt);
            cooldownWasZero = false;
        }
        if (self->m24 < 1.0f && self->m28 > self->m1c) {
            self->m24 = Clamp01Inline(self->m24 + gManager->mRefillRate * dt);
            return self->m38 > 0.0f;
        }
        self->m24 = 1.0f;
        if (cooldownWasZero) {
            self->m1c -= gManager->mDrainRate * dt;
            if (self->m1c < self->m20)
                self->m1c = self->m20;
        }
        return self->m38 > 0.0f;
    }

    // bar at target
    if (self->m24 > 0.0f && self->m28 > self->m1c) {
        self->m24 = Clamp01Inline(self->m24 - dt);
        return self->m38 > 0.0f;
    }
    self->m28 = target;
    self->m30 = target;
    if (self->m3c > 0.0f) {
        if (self->m38 < 1.0f)
            self->m38 = Clamp01Inline(self->m38 + gManager->mRefillRate * dt);
        else
            self->m3c -= dt;
    } else {
        self->m38 -= gManager->mRefillRate * dt;
        if (self->m44 > self->m38)
            self->m38 = self->m44;
    }
    return self->m38 > 0.0f;
}

// @ 0x00b693b0
void FUN_00b693b0(void* pProvider, void* pTarget, float alpha)
{
    const Rect* r = (const Rect*)(*(void*(__thiscall**)(void*))(*(int*)pProvider + 0x34))(pProvider);
    Rect rc;
    rc.left = 0.0f;
    rc.top = 0.0f;
    rc.right = (r->right - r->left) * alpha;
    rc.bottom = r->bottom - r->top;
    (*(void(__thiscall**)(void*, Rect*))(*(int*)pTarget + 0x60))(pTarget, &rc);

    if (alpha == 0.0f) {
        (*(void(__thiscall**)(void*, int, int))(*(int*)pTarget + 0x7c))(pTarget, 1, 0);
        return;
    }
    int level = _mm_cvtss_si32(_mm_set_ss(alpha * kColourScale));
    (*(void(__thiscall**)(void*, unsigned int))(*(int*)pTarget + 0x5c))(
        pTarget, ((unsigned int)level << 0x18) | 0xffffffu);
    (*(void(__thiscall**)(void*, int, int))(*(int*)pTarget + 0x7c))(pTarget, 1, 1);
}

// @ 0x00b69460
void FUN_00b69460(void* pWindow, int mode)
{
    void* pCtx = 0;
    if (pWindow != 0)
        pCtx = (*(void*(__thiscall**)(void*, void*))(*(int*)pWindow + 0x0c))(pWindow, (void*)0xeeee8218);
    if (mode == -1) {
        (*(void(__thiscall**)(void*, int, int))(*(int*)pCtx + 0x7c))(pCtx, 1, 0);
        return;
    }
    (*(void(__thiscall**)(void*, int, int))(*(int*)pCtx + 0x7c))(pCtx, 1, 1);
    (*(void(__thiscall**)(void*, int))(*(int*)pWindow + 0x14))(pWindow, mode);
}

// @ 0x00b6a420
bool FUN_00b6a420(Obj_s00b6_a420* obj, float* p2, float* p3)
{
    int t = (int)obj->GetType();
    switch (t) {
    case 0x3a25119:
    case 0x137e8e0:
    case 0xee02c7:
    case 0xd0036e08:
    case 0x116d858:
    case 0x1b92b27:
    case 0x175cdc9:
    case 0x1a55e4d:
    case 0x2a8fe3c:
    case 0xecade42:
    case 0x629baec:
    case 0x436f315:
    case 0x4e3faaf:
    case 0x70704db:
    case 0x4f176642:
    case 0xff10521:
    case 0x1007ae63:
    case 0x4f396a66:
        break;
    case 0xb033b403:
        return FUN_00b6a200(obj, p2);
    default:
        return false;
    }
    void* c = obj->Cast(0x1186577);
    if (SP_GetCurrentGameMode() == (void*)DAT_01654c10_s00b6_a420)
        return FUN_00b69cf0(c, p2, p3);
    return FUN_00b67ef0(c, p2, p3);
}

// @ 0x00b6a530
void FUN_00b6a530(void)
{
    Mgr* p = (Mgr*)operator_new(0x58, "Simulator", 0, 0, 0, 0);
    if (p) {
        FUN_00743b50((void**)p);
        p->sw.Init(0, 0);
    }
    g_pMgr = p;
    p->InitPool(0x130, 0x20);
    Mgr* m = g_pMgr;
    m->g1c = DAT_0156ae80;
    m->g20 = DAT_0156ae84;
    m->g24 = DAT_0156ae88;
    m->g28 = DAT_0156ae8c;
    m->g2c = DAT_0156ae90;
    g_pMgr->b30 = 1;
    Stopwatch tmp;
    tmp.Init(4, 0);
    g_pMgr->sw = tmp;
    g_pMgr->f50 = -1;
}

// @ 0x00b6a610
void FUN_00b6a610(Label* p)
{
    float lim = DAT_01464980;
    if (p->f48 == lim || p->f4c == lim) {
        p->mFlag = FUN_00b6a420(p->mpObj, &p->mX, &p->mX2);
        return;
    }
    p->mX = p->f48;
    p->mY = p->f4c;
    float fVar1 = p->mX;
    float fVar2 = p->mY;
    p->mX2 = p->mX;
    p->mY2 = p->mY;
    float local[4];
    float* r = (float*)GetMainWindowArea(local);
    if (r[0] <= fVar1 && r[1] <= fVar2 && fVar1 < r[2] && fVar2 < r[3])
        p->mFlag = true;
    else
        p->mFlag = false;
}

// @ 0x00b6a720
void FUN_00b6a720(Label* l, const float* pair, int v, int b1, int b2)
{
    IV* w54 = l->p54;
    float x = pair[0];
    float y = pair[1];
    ((void(__thiscall*)(IV*, float, float))VT(w54, 0x64))(w54, x, y - DAT_01473c70);

    if (!b1) {
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 0);
        return;
    }
    if (l->f38 == DAT_01485378) {
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 0);
    } else {
        int a = (int)(l->f38 * DAT_013f2100);
        ((void(__thiscall*)(IV*, uint32_t))VT(w54, 0x5c))(w54, ((uint32_t)a << 24) | 0xffffff);
        ((void(__thiscall*)(IV*, int, int))VT(w54, 0x7c))(w54, 1, 1);
    }
    IV* w58 = l->p58;
    if (l->f44 == DAT_01485378) {
        ((void(__thiscall*)(IV*, int, int))VT(w58, 0x7c))(w58, 1, 0);
    } else {
        int a = (int)(l->f44 * DAT_013f2100);
        ((void(__thiscall*)(IV*, uint32_t))VT(w58, 0x5c))(w58, ((uint32_t)a << 24) | 0xffffff);
        ((void(__thiscall*)(IV*, int, int))VT(w58, 0x7c))(w58, 1, 1);
    }
    if (l->p5c)
        ((void(__thiscall*)(IV*, int))VT(l->p5c, 0x80))(l->p5c, v);
    FUN_00b67440(l->p60, (int)(unsigned int)pair, 1.0f);
    if (l->p70 && !l->b34) {
        FUN_00b693b0(l->p64, l->p70, 1.0f);
        FUN_00b693b0(l->p68, l->p70, 1.0f);
        FUN_00b693b0(l->p6c, l->p70, 1.0f);
    }
    void* mode = SP_GetCurrentGameMode();
    int r = -1;
    if (mode == (void*)DAT_01654c01 || mode == (void*)DAT_01654c10_s00b6_a420) {
        r = FUN_00b67530(b2, 0);
    } else if (mode == (void*)DAT_01654c02_s00b6_a420 || mode == (void*)DAT_01654c05_s00b6_a420) {
        r = FUN_00b674d0(b2);
    }
    IV* w90 = l->p90;
    IV* q = w90 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w90, 0x0c))(w90, 0xeeee8218)) : 0;
    if (r == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w90, 0x14))(w90, r);
    }
    if (l->p74) {
        wchar_t buf[32];
        SetNumberString(b2, b2 >> 31, buf, 0x20);
        ((void(__thiscall*)(IV*, const wchar_t*))VT(l->p74, 0x80))(l->p74, buf);
    }
}

// @ 0x00b6a970
bool FUN_00b6a970(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, Vec3 col, int a, int b, float dt)
{
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return false;
    }
    FUN_00b6a720(e, (const float*)pos, a, b, (int)dt);
    return true;
}

// @ 0x00b6a9d0
void FUN_00b6a9d0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt)
{
    int m = FUN_00b675a0(a);
    IV* w = e->p94;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    IV* w2 = e->p98;
    IV* q2 = w2 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w2, 0x0c))(w2, 0xeeee8218)) : 0;
    ((void(__thiscall*)(IV*, int, int))VT(q2, 0x7c))(q2, 1, 1);
    ((void(__thiscall*)(IV*, int))VT(w2, 0x14))(w2, 0);
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, c, (int)dt);
}

// @ 0x00b6aae0
void FUN_00b6aae0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt)
{
    int m = FUN_00b675a0(c);
    IV* w = e->p9c;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// @ 0x00b6abc0
void FUN_00b6abc0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, float f1, float f2, int c, int d, float dt)
{
    int m = ModeFromValue(c);
    IV* w = e->p9c;
    IV* q = w ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w, 0x0c))(w, 0xeeee8218)) : 0;
    if (m == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q, 0x7c))(q, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w, 0x14))(w, m);
    }
    wchar_t buf1[64];
    SetNumberString((int)f1, (int)f1 >> 31, buf1, 0x40);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->p7c, 0x80))(e->p7c, buf1);
    wchar_t buf2[64];
    SetNumberString((int)f2, (int)f2 >> 31, buf2, 0x40);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->p84, 0x80))(e->p84, buf2);

    int m2 = ModeFromValue(c);
    IV* w80 = e->p80;
    IV* q80 = w80 ? (IV*)(((void*(__thiscall*)(IV*, uint32_t))VT(w80, 0x0c))(w80, 0xeeee8218)) : 0;
    if (m2 == -1) {
        ((void(__thiscall*)(IV*, int, int))VT(q80, 0x7c))(q80, 1, 0);
    } else {
        ((void(__thiscall*)(IV*, int, int))VT(q80, 0x7c))(q80, 1, 1);
        ((void(__thiscall*)(IV*, int))VT(w80, 0x14))(w80, m2);
    }
    ((void(__thiscall*)(IV*, int, int))VT(e->p88, 0x7c))(e->p88, 1, 1);
    if (!FUN_00b69010(e, x, dt)) {
        FUN_00b686a0((IV*)e->mpObj0);
        return;
    }
    FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// @ 0x00b6adf0
void FUN_00b6adf0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, int d, float dt)
{
    wchar_t buf[128];
    WStr_Format(buf, L"%d / %d", c, d);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->pA8, 0x80))(e->pA8, buf);

    if (SP_GetCurrentGameMode() == (void*)DAT_01654c02_s00b6_a420) {
        bool show = false;
        if (e->mpObj) {
            Obj_s00b6_a420* t = (Obj_s00b6_a420*)e->mpObj->Cast(0xee02c7);
            if (t && ((bool(__thiscall*)(Obj_s00b6_a420*))VT(t, 0x58))(t)) {
                void* tribe = SP_cTribeModeStrategy_Instance();
                int v2 = ((int(__thiscall*)(void*))VT(tribe, 0x70))(tribe);
                if (!FUN_00d09660((void*)v2)) {
                    show = true;
                    IV* win = FindWindowByID(e->p50, 0x625cd52, 1);
                    if (win) {
                        void* tribe2 = SP_cTribeModeStrategy_Instance();
                        char bv = (char)FUN_00cd5750(tribe2);
                        ((void(__thiscall*)(IV*, int, int))VT(win, 0x7c))(win, 2, bv);
                        eastl_string tt;
                        tt = L"";
                        cString s1(0xc0152a6d, 0x65fc366, 0);
                        tt += s1.GetText();
                        void* tr = GetPlayerTribe();
                        if (tr) {
                            if (FUN_00c8f3a0(tr) < DAT_0158133c) {
                                cString s2(0xc0152a6d, 0x65fc367, 0);
                                tt += s2.GetText();
                            } else if (FUN_00c8f3a0(tr) >= SP_GetMaxPopulation(tr)) {
                                cString s3(0xc0152a6d, FUN_00a1ad10(tr) < 2 ? 0x65fc368 : 0x65fc369, 0);
                                tt += s3.GetText();
                            }
                        }
                        SetTooltipText(win, tt.c_str(), -1, 1);
                    }
                }
            }
        }
        ((void(__thiscall*)(IV*, int, int))VT(e->pAc, 0x7c))(e->pAc, 1, show ? 1 : 0);
    }
    if (!FUN_00b69010(e, x, dt))
        FUN_00b686a0((IV*)e->mpObj0);
    else
        FUN_00b6a720(e, (const float*)pos, b, d, (int)dt);
}

// @ 0x00b6b0a0
void FUN_00b6b0a0(Label* e, int flag, const Vec2* pos, float x, const wchar_t* name, const Vec3& v, int a, int b, int c, float dt)
{
    wchar_t buf[128];
    WStr_Format(buf, L"%d / %d", b, c);
    ((void(__thiscall*)(IV*, const wchar_t*))VT(e->pA8, 0x80))(e->pA8, buf);
    if (SP_GetCurrentGameMode() == (void*)DAT_01654c02_s00b6_a420 && e->mpObj)
        ((void(__thiscall*)(Obj_s00b6_a420*))VT(e->mpObj, 0x20))(e->mpObj);
    if (!FUN_00b69010(e, x, dt))
        FUN_00b686a0((IV*)e->mpObj0);
    else
        FUN_00b6a720(e, (const float*)pos, a, 0, (int)dt);
}

// @ 0x00b6b1a0
void FUN_00b6b1a0(cConvSelf* self, cConvTarget* obj)
{
    WString text;
    text.mBegin = &gEmptyString16;
    text.mEnd   = &gEmptyString16;
    text.mCap   = &gEmptyString16 + 1;

    if (obj != 0) {
        wchar_t buf[0x28];
        buf[0] = 0;
        int n = obj->FUN_00bd8960();
        EA_Locale_SetNumberString(n, n >> 31, buf, 0x28);
        wchar_t* end = buf;
        while (*end != 0)
            ++end;
        text.assign(buf, end);

        int diff = obj->m668 - obj->m66c;

        for (int i = 0; i < 5; ++i) {
            cUIWindow* win = self->mLayout->FindWindowByID(i + 0x4fe1aa0, 1);
            cUIWindow* fill = win->w0c(0x10edf11);
            if (fill != 0) {
                float f = 0.0f;
                if (diff > 0) {
                    if (i < diff)
                        f = kFloat100;
                } else if (diff < 0) {
                    if (i < -diff)
                        f = kFloat50;
                }
                fill->w04(f);
            }
        }

        cUIWindow* caption = self->mLayout->FindWindowByID(0x2cf2f74, 1);
        if (caption != 0) {
            gToolGate->FUN_00cfe780(obj);
            {
                cString_s00b6_b1a0 s;
                s.Load(0xdc351566, 0x68c71fb, 0);
                {
                    WString cap;
                    cap.mBegin = 0;
                    cap.mEnd   = 0;
                    cap.mCap   = 0;
                    cap.RangeInitialize(s.GetText());
                    caption->w80(cap.mBegin);
                }
            }
        }

        cUIWindow* swatch = self->mLayout->FindWindowByID(0x68da668, 1);
        if (swatch != 0) {
            u32 color = 0xffffffffu;
            cLivingUniverse* universe = SP_GetActivePlanet();
            if (universe != 0) {
                cPlanet* planet = universe->mActivePlanet;
                if (planet != 0) {
                    cPropertyManager* pm = SP_PropertyManager();
                    cProp* prop = 0;
                    cPropSetter* holder = planet->FUN_00b8dad0();
                    pm->q2c(holder->mPtr, 0x34d97fa, &prop);
                    if (prop != 0) {
                        cPropDesc* desc = 0;
                        if (prop->p24(0x58cbb75, &desc) && desc->mType == 0x000a)
                            color = *desc->GetUInt();
                    }
                    if (prop != 0)
                        prop->p04();
                }
            }
            color |= 0xff000000u;
            swatch->w5c(color);
        }

        int count = obj->FUN_00bd9b70();
        for (int i = 0; i < 5; ++i) {
            cUIWindow* win = self->mLayout->FindWindowByID(i + 0x4fe38f0, 1);
            cUIWindow* fill = win->w0c(0x10edf11);
            if (fill != 0) {
                float f = (i < count) ? kFloat100 : 0.0f;
                fill->w04(f);
            }
        }
    }

    self->mWnd->w80(text.mBegin);
}

// @ 0x00b6b810
EStr* FUN_00b6b810(EStr* result, void* obj)
{
    cCreature* creature = 0;
    if (obj != 0)
        creature = (cCreature*)((cObjBase*)obj)->b0c(0x4f176642);

    WString name;
    name.mBegin = &gEmptyString16;
    name.mEnd   = &gEmptyString16;
    name.mCap   = &gEmptyString16 + 1;

    u32 key = 0xcb37547d;
    if (&creature->mName != &name)
        name.assign(creature->mName.mBegin, creature->mName.mEnd);

    if (creature->IsLeader()) {
        cString_s00b6_b1a0 s(0xf71fa311, 0x4bd540b, name.mBegin);
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &key, 1);
        result->Construct(s.GetText());
    } else if (creature->FUN_00c0b770() == 0) {
        key = 0xcaa303ac;
        cString_s00b6_b1a0 s(0xad56080c, 0xb32fe522, L"~Baby");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &key, 1);
        result->Construct(s.GetText());
    } else {
        u32 sub;
        switch (creature->FUN_00c22dc0()) {
        case 1: sub = 0x567d1d3; break;
        case 2: sub = 0x567d1d2; break;
        case 3: sub = 0x567d1d1; break;
        case 4: sub = 0x567d1d6; break;
        case 5: sub = 0x567d1d7; break;
        case 6: sub = 0x567d1d8; break;
        case 7: sub = 0x567d1d5; break;
        case 8: sub = 0x567d1d4; break;
        case 9: sub = 0x567d1d0; break;
        default:
            result->Construct(name.mBegin);
            goto epilogue;
        }
        {
            cString_s00b6_b1a0 s(0xf71fa311, sub, name.mBegin);
            cTextObj* t = FUN_0067de40()->r20();
            t->v30(&s, &key, 1);
            result->Construct(s.GetText());
        }
    }

epilogue:
    return result;
}

// @ 0x00b6ba50
EStr* FUN_00b6ba50(EStr* result, void* obj)
{
    if (obj != 0) {
        cConvInfo* info = (cConvInfo*)((cObjBase*)obj)->b0c(0x4e3faaf);
        if (info != 0) {
            u32 id = info->mId;
            cString_s00b6_b1a0 s;
            if (s.Load(0x2db6dad3, id, 0)) {
                result->Construct(s.GetText());
                return result;
            }
        }
    }

    result->m10    = (wchar_t*)((char*)result + 0x14);
    wchar_t* base  = result->m10;
    result->mCap   = base + 0x20;
    result->mEnd   = base;
    result->mBegin = base;
    base[0]        = 0;
    result->Init(&gStr013ec468, &gStr013ec468);
    return result;
}

// @ 0x00b6baf0
cVar ResolveVar(VObj* obj)
{
    if (GetCurrentGameMode_s00b6_baf0() == 0x1654c10)
    {
        Rec* rec = gGlobals16c7aa4->m74->Find(obj);
        Str12 v;
        if (rec && rec->Get(&v))
            return cVar(v.mpBegin);
    }

    Named* x;
    int key;
    switch (obj->GetVarID())
    {
        case 0xd0036e08:
            return ResolveRollover(obj);

        case 0xb033b403:
        {
            VObj* p = CastB033(obj);
            int id = p->GetID();
            Civ* e = StarManager()->GetEmpireByID(id);
            if (e)
                return cVar(*e->GetNamePtr());
            cString_s00b6_baf0 s;
            if ((((Creature*)p)->m714 == 0xb && s.Load(0x2db6dad3, 0x6749c10, 0)) ||
                s.Load(0x2db6dad3, 0x678cddf, 0))
                return cVar(s.GetText());
            return cVar(gEmptyStr);
        }

        case 0xee9b2232:
            x = CastEE9B(obj);
            goto chk;

        case 0xee02c7:
            x = CastEE02(obj)->GetNamed();
            goto chk;

        case 0x116d858:
        {
            VObj* a = obj->Cast(0x116d858);
            TableRow* r = LookupRow(a->GetIndex());
            return cVar(r->str.GetText());
        }

        case 0x137e8e0:
        {
            int id = obj->GetID();
            Named* n = NounManager()->FindNamed(id);
            obj->Cast(0x137e8e0);
            if (n)
                return cVar(n->sub.GetName());
            goto dflt;
        }

        case 0x1a55e4d:
            key = 9;
            goto lookup;

        case 0x1b92b27:
        {
            Creature* c = CastB92(obj);
            if (!c) goto dflt;
            Herd* h = c->m128;
            if (!h) goto dflt;
            if (h->ma4 == GetSetting9()->GetAvatarProfile())
            {
                uint32_t k;
                if (NounManager()->GetTerrain()->Check(0x514a219, &k))
                {
                    if (GetDesiredAvatarHerd(false) == c->m128)
                        return cVar(cString_s00b6_baf0(0xad56080c, 0x658f2d1, L"~New Nest").GetText());
                    if (c->m128->b84)
                        return cVar(cString_s00b6_baf0(0xad56080c, 0x658f2d2, L"~Old Nest").GetText());
                }
                else if (c->m128->b84)
                    return cVar(cString_s00b6_baf0(0xad56080c, 0x658f2d0, L"~Home Nest").GetText());
            }
            if (!(c->b124 & 1))
                return cVar(cString_s00b6_baf0(0xad56080c, 0x658f2d3, L"~Unknown Species").GetText());
            return cVar(c->m128->ma4->mpName);
        }

        case 0x436f315:
            key = 0xa;
            goto lookup;

        case 0x4e3faaf:
            return ResolveB6BA50(obj);

        case 0x70704db:
        {
            VObj* p = CastE9CB(obj);
            if (!p) goto dflt;
            return cVar(p->GetText());
        }

        case 0xff10521:
            key = 7;
            goto lookup;

        case 0xecade42:
            key = 8;
            goto lookup;

        case 0x1007ae63:
            if (GetCurrentGameMode_s00b6_baf0() == 0x1654c05)
            {
                VObj* a = obj->Cast(0x1007ae63);
                if (a)
                {
                    x = (Named*)a->Get84();
                    goto nochk;
                }
                key = 0xc;
            }
            else
                key = 6;
            goto lookup;

        case 0x4f176642:
            return ResolveB6B810(obj);

        case 0x4f396a66:
            x = CheckType(obj, 0x18c6d19);
            goto chk;

        default:
            goto dflt;
    }

chk:
    if (!x) goto dflt;
nochk:
    return cVar(x->sub.GetName());

lookup:
    {
        VObj* bld = obj->Cast(0xe9cb8ba);
        VObj* oth = obj->Cast(0x436f315);
        int mode = GetCurrentGameMode_s00b6_baf0();
        Civ* civ = 0;
        City* city;
        switch (mode)
        {
            case 4:
            cityPath:
                if (bld)
                    city = (City*)bld->Get84();
                else if (oth)
                    city = oth->GetCityMember();
                else
                    break;
                civ = city->GetCivilization();
                break;
            case 5:
            {
                if (!GetUniverseContext() && GetActivePlanet()->GetState() == 4)
                    goto cityPath;
                int id = -1;
                if (bld)
                    id = bld->GetID();
                else if (oth)
                    id = oth->GetID();
                civ = StarManager()->GetEmpireByID(id);
                break;
            }
            default:
                __assume(0);
        }
        bool bNoCiv = (civ == 0);
        TableOwner* t = civ ? civ->Cast(0x5593a1a) : 0;
        const wchar_t* text;
        if (bNoCiv)
            text = gEmptyStr;
        else
        {
            uint32_t k = key;
            text = t->map.find(k).node->value;
        }
        return cVar(text);
    }

dflt:
    return cVar(gEmptyStr);
}

// @ 0x00b6c180
__declspec(noinline) static void CleanupUICtx(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx)
        return;
    if (!pCtx->mLayout)
        return;

    pCtx->mLayout->Shutdown(1);

    cSPUILayout_s00b6_baf0* pLayout = pCtx->mLayout;
    if (pLayout)
    {
        pCtx->mLayout = 0;
        pLayout->Release();
    }

    pCtx->ClearWindows();
}

// @ 0x00b6c200
__declspec(noinline) void RemoveUICtx(int key)
{
    UICtx* pCtx = gUIMgr->Find(key);
    if (!pCtx)
        return;

    RemoveUISlot(key);
    CleanupUICtx(key);

    UICtx* pRefCtx = gUIMgr->Find(key);
    if (pRefCtx && pRefCtx->mRef)
        ReleaseRefSlot(pRefCtx->mRef);

    if (pCtx->mObj)
    {
        VObj* pObj = pCtx->mObj;
        pCtx->mObj = 0;
        pObj->s01();
    }

    gUIMgr->Remove(key);
}

// @ 0x00b6c280
void RefreshUITooltips()
{
    if (!gUIMgr)
        return;

    int key = gUIMgr->CurrentKey();
    UICtx* pCtx = gUIMgr->Next(&key);
    while (pCtx)
    {
        RemoveUICtx(pCtx->mID);
        pCtx = gUIMgr->Next(&key);
    }
}

// @ 0x00b6c2d0
__declspec(noinline) static UICtx* ShowHealthBar(int key)
{
    int slotKey = FindOrCreateKey(key);
    UICtx* pCtx = gUIMgr->GetSlot(slotKey);

    if (!pCtx->mLayout)
    {
        void* pMem = SporeAlloc(0x18, L"Simulator/HealthBar", 0, 0, 0, 0);
        cSPUILayout_s00b6_baf0* pLayout = pMem ? ((cSPUILayout_s00b6_baf0*)pMem)->ctor() : 0;
        cSPUILayout_s00b6_baf0* pOld = pCtx->mLayout;

        if (pLayout != pOld)
        {
            if (pLayout)
                pLayout->AddRef();
            pCtx->mLayout = pLayout;
            if (pOld)
                pOld->Release();
        }

        pCtx->mLayout->Init(L"GoalIcons", 0x40464100, true, 0xe9f70df9);

        pCtx->mWindow = pCtx->mLayout->FindWindowByID(0x75de460, 1);

        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x75f3ea8, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x75de461, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37790, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37793, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37794, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c37799, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c3779d, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a1, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a5, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a6, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377a9, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377ad, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377b1, 0));
        pCtx->mWindows.push_back(pCtx->mWindow->FindWindow(0x7c377b6, 0));

        if (!pCtx->mWindow)
            CleanupUICtx(slotKey);
    }

    return pCtx;
}

// @ 0x00b6c710
void UpdateUIContexts(float dt)
{
    int key = gUIMgr->CurrentKey();
    UICtx* pCtx = gUIMgr->Next(&key);
    if (!pCtx)
        return;

    do
    {
        if (pCtx->mLayout)
        {
            float timeLeft = pCtx->mTimer - dt;
            pCtx->mTimer = timeLeft;

            if (timeLeft >= 0)
            {
                for (unsigned int i = 0; i < pCtx->mWindows.size(); ++i)
                {
                    SimView* pChild = pCtx->mWindows.mpBegin[i];
                    if (pChild)
                    {
                        if (pChild->GetIndex() == pCtx->mIndex)
                            pChild->SetVisible(1, 1);
                        else
                            pChild->SetVisible(1, 0);
                    }
                }

                pCtx->mWindow->SetVisible(1, pCtx->mVisible);

                if (pCtx->mVisible)
                {
                    float x = pCtx->mX;
                    float y = pCtx->mY;
                    float rect[4];
                    rect[0] = x - 0.5f;
                    rect[1] = y - 0.5f;
                    rect[2] = x + 0.5f;
                    rect[3] = y + 0.5f;
                    AnchorWindowToScreen(rect, pCtx->mWindow, 0x102, 0);
                }
            }
            else
                CleanupUICtx(pCtx->mID);
        }

        pCtx = gUIMgr->Next(&key);
    } while (pCtx);
}

// @ 0x00b6c870
void UpdateSimulatorUI(UICtx* pCtx, int a2, float* pOffset, int a4, float a5)
{
    int mode = GetCurrentGameMode_s00b6_baf0();

    if (mode == 0x1654c01)
    {
        pCtx->mMainWindow->SetVisible(1, a4);

        VObj* pSimObj = pCtx->mObj;
        SimView* pSim = pSimObj ? (SimView*)pSimObj->Cast(0xd0036e08) : 0;

        if (pSim->CheckActive() &&
            (pSim->mFlags & 2) == 0 &&
            (pSim->mFlags & 1) != 0 &&
            !pSim->IsBlockedPrimary() &&
            !pSim->IsBlockedSecondary())
        {
            pCtx->mStateWindow->SetVisible(1, 1);

            SimState* pState = pSim->GetState();
            int index = pState->mCount - 1;
            if (index < 0)
                index = 0;

            SetCtxWindow((SimView*)pCtx->mOwnerObj, index);
        }
        else
            pCtx->mStateWindow->SetVisible(1, 0);
    }
    else if (mode == 0x1654c10)
        pCtx->mMainWindow->SetVisible(1, 0);

    VObj* pObj = pCtx->mObj;
    cVar text = ResolveVar(pObj);
    int textID = (int)text.mData[0];
    Vec3 pos = GetSimulatorPos(pObj);
    float value = GetSimulatorFloat(pObj);
    int i1 = GetSimulatorInt1(pObj);
    int i2 = GetSimulatorInt2(pObj);

    if (pCtx->UpdateSimulatorAnim(value, a5))
        pCtx->ShowSimulatorText(pOffset, a2, (const void*)textID, &pos, i1, i2);
    else
        RemoveUISlot(pCtx->mID);
}

// @ 0x00b6d3c0
void ProcessLabelEvents(float dt)
{
    if (g_pMgr_s00b6_d3c0->f38 || g_pMgr_s00b6_d3c0->f3c) FUN_00b6d1d0(g_pMgr_s00b6_d3c0->f50);
    int cookie = FUN_00e31100();
    for (Event* e = g_pMgr_s00b6_d3c0->FUN_00b72230(&cookie); e; e = g_pMgr_s00b6_d3c0->FUN_00b72230(&cookie)) {
        if (!e->mArmed) continue;
        char flag = e->mFlag;
        Vec2 pos;
        pos.x = e->mX;
        pos.y = e->mY;
        switch (FUN_00b67c70(e->mpObj)) {
        case 13: {
            Obj_s00b6_d3c0* o = e->mpObj;
            FUN_00b6a970(e, flag, &pos, 0.0f, L"Food Pile", FUN_00b677e0(o), FUN_00b682a0(o), 0, dt);
            break;
        }
        case 0:
            FUN_00b6a970(e, flag, &pos, 0.0f, kEmptyStr, kLabelColor, 0, 0, dt);
            break;
        case 10: {
            Obj_s00b6_d3c0* o = e->mpObj;
            WString_s00b6_d3c0 name = FUN_00b6baf0(o);
            FUN_00b6a970(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, GetPlayerEmpire()->GetColor(),
                         FUN_00b67b90(o), 0, dt);
            break;
        }
        case 2: {
            Obj_s00b6_d3c0* o = e->mpObj;
            int a = 0;
            if (o) {
                ObjA* r = (ObjA*)o->Cast(0x116d858);
                a = r ? r->V22() : 0;
            }
            WString_s00b6_d3c0 name = FUN_00b6baf0(e->mpObj);
            FUN_00b6a9d0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), a,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 4: {
            Obj_s00b6_d3c0* o = e->mpObj;
            WString_s00b6_d3c0 name = FUN_00b6baf0(o);
            FUN_00b6adf0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 5: {
            Obj_s00b6_d3c0* o = e->mpObj;
            WString_s00b6_d3c0 name = FUN_00b6baf0(o);
            FUN_00b6b0a0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(o), FUN_00b682a0(o),
                         FUN_00b68250(o), FUN_00b681d0(o), dt);
            break;
        }
        case 3: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            Obj_s00b6_d3c0* o = e->mpObj;
            int b = 0;
            if (o) {
                ObjB* r = (ObjB*)o->Cast(0x4f176642);
                b = r ? r->FUN_00c22dc0() : 0;
            }
            WString_s00b6_d3c0 name = FUN_00b6baf0(e->mpObj);
            FUN_00b6aae0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(e->mpObj), b,
                         FUN_00b682a0(o), FUN_00b67b90(o), bv, dt);
            break;
        }
        case 6: {
            Obj_s00b6_d3c0* o = e->mpObj;
            ObjD* d1 = o ? (ObjD*)o->Cast(0x137e8e0) : 0;
            float x1 = d1 ? d1->mSub.V51() : 0.0f;
            ObjD* d2 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            float x2 = d2 ? d2->FUN_00c9f330() : 0.0f;
            ObjD* d3 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y1 = d3 ? d3->mY1 : 0;
            ObjD* d4 = e->mpObj ? (ObjD*)e->mpObj->Cast(0x137e8e0) : 0;
            int y2 = d4 ? d4->mY2 : -1;
            Obj_s00b6_d3c0* oe = e->mpObj;
            WString_s00b6_d3c0 name = FUN_00b6baf0(oe);
            FUN_00b6abc0(e, flag, &pos, FUN_00b685e0(e->mpObj), name.mpBegin, FUN_00b677e0(oe), y2, y1, x2, x1,
                         FUN_00b682a0(o), FUN_00b67b90(o), dt);
            break;
        }
        case 11:
            FUN_00b6cc50(e, flag, &pos, dt);
            break;
        case 12: {
            bool bv = false;
            if (e->mpObj) {
                ObjC* r = (ObjC*)e->mpObj->Cast(0xce9f6639);
                bv = r ? r->V53() : false;
            }
            FUN_00b6c870(e, flag, &pos, bv, dt);
            break;
        }
        case 9:
            FUN_00b6cde0(e, flag, &pos, dt);
            break;
        case 7:
            FUN_00b6cf70(e, flag, &pos, dt);
            break;
        case 8:
            FUN_00b6d060(e, flag, &pos, dt);
            break;
        case 14:
            FUN_00b6ca10(e, flag, &pos, dt);
            break;
        case 16:
            FUN_00b6cba0(e, flag, &pos, dt);
            break;
        case 1:
        case 15:
            break;
        }
    }
}

// @ 0x00b6e050
void FUN_00b6e050()
{
    uint32_t cur = g_slot01687968;
    if (cur < 0x53dbcf3)
        cur = 0x53dbcf2;
    int remaining = 12;
    do {
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        NEXT_SLOT(cur);
        remaining -= 6;
    } while (remaining > 0);
}

// @ 0x00b6e1e0
char FUN_00b6e1e0(int index)
{
    return g_slots0168795c[index];
}

// @ 0x00b6e210
void* cSimUIObject::GetInterface(uint32_t id)
{
    void* result = 0;
    if (id == 0x5593a1a)
        result = this;
    return result;
}

// @ 0x00b6e250
int FUN_00b6e250()
{
    if (g_pSimState != 0 && g_flag0156b0cc != 0)
        return 1;
    return 0;
}

// @ 0x00b6e270
int FUN_00b6e270(int value)
{
    int old = g_pSimState->mField28;
    g_pSimState->mField28 = value;
    return old;
}

// @ 0x00b6e290
int FUN_00b6e290(int value)
{
    int old = g_pSimState->mField2c;
    g_pSimState->mField2c = value;
    return old;
}

// @ 0x00b6e2b0
int FUN_00b6e2b0(int value)
{
    int old = g_pSimState->mField30;
    g_pSimState->mField30 = value;
    return old;
}

// @ 0x00b6e2d0
void cSimulatorUIStore::Save(IStreamHost* owner)
{
    IStreamObj* streamObj = owner->V8();
    uint32_t id = 0x5593a1a;
    void* stream = streamObj->V6();
    EA::IO::WriteUint32(stream, &id, 1, 0);
    cVarListSerializer_s00b6_d3c0 ser;
    ser.Init(this, &g_dataset0156b0d8, 0x1a80d26);
    ser.Serialize(owner);
}

// @ 0x00b6e3d0
unsigned int FindNearestColorKey(const Vec3* c)
{
  static const unsigned int kMaxBits = 0x7f7fffff;
  float best = *(const float*)&kMaxBits;
  unsigned int bestKey = 0x53dbcf3;
  float x = c->x, y = c->y, z = c->z;
  for (rbtree_node_base* n = g_colorMap.mAnchor.mpNodeLeft; n != &g_colorMap.mAnchor; n = RBTreeIncrement(n)) {
    ColorNode* cn = (ColorNode*)n;
    Vec3 d;
    d.x = cn->val.x - x;
    d.y = cn->val.y - y;
    d.z = cn->val.z - z;
    float dist = (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    if (dist < best) {
      bestKey = cn->key;
      best = dist;
    }
  }
  return bestKey;
}

// @ 0x00b6e4b0
Vec3* AdjustColor(Vec3* out, float r, float g, float b, float minS, float minL)
{
  out->x = r;
  out->y = g;
  out->z = b;
  if (fabs(r - g) < 0.1f && fabs(r - b) < 0.1f && fabs(g - b) < 0.1f) {
    if (r > g && r > b) {
      r = (1.0f - r) * 0.1f + r;
      g = g * 0.9f;
      b = b * 0.9f;
    } else if (g > r && g > b) {
      r = r * 0.9f;
      g = (1.0f - g) * 0.1f + g;
      b = b * 0.9f;
    } else {
      r = r * 0.9f;
      g = g * 0.9f;
      b = (1.0f - b) * 0.1f + b;
    }
  }
  float h, s, l;
  Vec3 rgb;
  rgb.x = r;
  rgb.y = g;
  rgb.z = b;
  RGBToHSL(rgb, &h, &s, &l);
  if (s <= minS) s = minS;
  if (1.0f <= s) s = 1.0f;
  if (l <= minL) l = minL;
  if (1.0f <= l) l = 1.0f;
  Vec3 tmp;
  *out = *HSLToRGB(&tmp, h, s, l);
  return out;
}

// @ 0x00b6e6d0
void ShutdownColorManager()
{
  if (g_translator && g_colorMap.mnSize) {
    g_colorMap.DoNukeSubtree((ColorNode*)g_colorMap.mAnchor.mpNodeParent);
    g_colorMap.reset();
    GetUIHolder()->GetMgr()->Unregister(g_translator);
    ColorTranslator* t = g_translator;
    if (t) {
      g_translator = 0;
      t->Release();
    }
  }
}

// @ 0x00b6e7b0
bool ColorTranslator::Translate(const wchar_t* token, wstr* out)
{
  unsigned int key;
  bool ok = true;
  switch (FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x24b3c25fu: out->append(mSetC->Get(1)); break;
    case 0x0e76b271u: out->append(mSetA->Get(0)); break;
    case 0x04603dc6u: out->append(mSetC->Get(0)); break;
    case 0x2bcf1d11u: key = 5; out->append(mSetC->mMap.find(key)->val); break;
    case 0x35dae791u: key = 0xf; out->append(mSetA->mMap.find(key)->val); break;
    case 0x5d7860fau: out->append(mSetB->Get(1)); break;
    case 0x5f960254u: {
      key = 5;
      const wchar_t* p = mSetB->mMap.find(key)->val;
      const wchar_t* e = p;
      while (*e) e++;
      out->assign(p, e);
      break;
    }
    case 0x9825819au: out->append(mSetC->Get(4)); break;
    case 0x94730909u: out->append(mSetA->Get(0x10)); break;
    case 0x7e5504edu: out->append(mSetB->Get(0)); break;
    case 0xa708d495u: out->append(mSetB->Get(4)); break;
    case 0xa9813ec0u: out->append(mSetC->Get(3)); break;
    case 0xaf5632a7u: out->append(mSetA->Get(2)); break;
    case 0xc4bee3d5u:
      if (&mText1 != out) out->assign(mText1.mpBegin, mText1.mpEnd);
      break;
    case 0xdd67ded2u: out->append(mSetC->Get(2)); break;
    case 0xcd335100u: out->append(mSetA->Get(0x11)); break;
    case 0xccd6c165u: out->append(mSetB->Get(3)); break;
    case 0xdf44b8c0u: *out = mText0; break;
    case 0xeaadf55bu: out->append(mSetA->Get(0xd)); break;
    case 0xf174ab9eu: key = 2; out->append(mSetB->mMap.find(key)->val); break;
    default: ok = false;
  }
  return ok;
}

// @ 0x00b6eb30
ColorNode** ColorMap::DoInsertValueImpl(ColorNode** out, ColorNode* parent, const void* v, bool bForceToLeft)
{
  struct Pair { unsigned int first; Vec3 second; };
  const Pair& value = *(const Pair*)v;
  int side;
  if (bForceToLeft || (parent == (ColorNode*)&mAnchor) || (value.first < parent->key))
    side = 0;
  else
    side = 1;
  ColorNode* n = (ColorNode*)operator new(
      0x20, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (&n->key) {
    n->key = value.first;
    n->val = value.second;
  }
  RBTreeInsert(n, parent, &mAnchor, side);
  mnSize++;
  *out = n;
  return out;
}

// @ 0x00b6ec50
void LoadColorNames(wstr* out, unsigned int key, unsigned int idx, cString_s00b6_e3d0* str)
{
  cString_s00b6_e3d0 s;
  s.Load(0xcdf005ab, key, L"!!!Color Name");
  wstr tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCapacity = 0;
  tmp.RangeInitialize(s.GetText());
  if (&tmp != &g_translator->mText0) g_translator->mText0.assign(tmp.mpBegin, tmp.mpEnd);
  if (out != &g_translator->mText1) g_translator->mText1.assign(out->mpBegin, out->mpEnd);
  str->Load(0xcdf005ab, idx, L"!!!Entity Name");
}

// @ 0x00b6edf0
cColorSet::~cColorSet()
{}

// @ 0x00b6ee10
void cColorSet::clear()
{ mNames.clear(); }

// @ 0x00b6ee40
Vec3& ColorMap::Index(const unsigned int& key)
{
  ColorNode* parent = (ColorNode*)&mAnchor;
  ColorNode* n = (ColorNode*)mAnchor.mpNodeParent;
  while (n) {
    if (!(n->key < key)) {
      parent = n;
      n = (ColorNode*)n->mpNodeLeft;
    } else {
      n = (ColorNode*)n->mpNodeRight;
    }
  }
  if (parent == (ColorNode*)&mAnchor || key < parent->key) {
    struct Pair {
      unsigned int first; Vec3F second;
      Pair(const unsigned int& k, const Vec3F& s) : first(k), second(s) {}
    } v(key, Vec3F());   // eastl: value_type(key, T()); T() is an uninitialised temp, copied
    ColorNode* r;
    DoInsertValue(&r, ColorIter(parent), &v, false);
    return r->val;
  }
  return parent->val;
}

// @ 0x00b6eee0
void InitColorManager()
{
  if (g_translator == 0 || g_colorMap.mnSize == 0) {
    PropList* list = 0;
    PropMgr* pm = GetPropMgr();
    if (list) {
      PropList* t = list;
      list = 0;
      t->Release();
    }
    if (pm->GetPropertyList(0x5c770db7, &list) && list->HasProperty(0x5515ffd)) {
      struct Prop {
        char* data;
        int pad[1];
        unsigned int count;
        int pad2;
        unsigned short flags;
        unsigned short has;
      };
      Prop* p = (Prop*)list->GetProperty(0x5515ffd);
      Vec3* d;
      unsigned int count;
      if (p->flags & 0x30) {
        d = (Vec3*)p->data;
        count = p->count;
      } else {
        d = (Vec3*)(-(unsigned int)(p->has != 0) & (unsigned int)p);
        count = (p->has != 0);
      }
      for (unsigned int i = 0; i < count; i++) {
        Vec3 v = d[i];
        unsigned int k = 0x53dbcf1 + i;
        g_colorMap.Index(k) = v;
      }
    }
    g_x1687968 = 0x53dbcf2;
    g_x156b018 = 0x53dbcf3;
    {
      cString_s00b6_e3d0 nm(0xcdf005ab, 0x53dbcf2, L"!!!Color 0");
      ColorTranslator* t = new ("Simulator", 0, 0, 0, 0) ColorTranslator;
      ColorTranslator* old = g_translator;
      if (t != old) {
        if (t) t->AddRef();
        g_translator = t;
        if (old) old->Release();
      }
      GetUIHolder()->GetMgr()->Register(g_translator);
    }
    if (list) list->Release();
  }
}

// @ 0x00b6f0c0
Vec3& GetColor(unsigned int key)
{
  return g_colorMap.Index(key);
}

// @ 0x00b6f0d0
unsigned int GetColorARGB(unsigned int key)
{
  return PackARGB(g_colorMap.Index(key));
}

// @ 0x00b6f140
void SetBaseColor(Vec3 col)
{
  if (g_translator && g_colorMap.mnSize) {
    unsigned int k = 0x53dbcf1;
    Vec3& c = g_colorMap.Index(k);
    c = col;
  }
}

// @ 0x00b6f180
void MarkNearestColors()
{
  g_used[0] = 0;
  g_used[4] = 0;
  g_used[8] = 0;
  *(unsigned int*)&g_used[0] = 0;
  *(unsigned int*)&g_used[4] = 0;
  *(unsigned int*)&g_used[8] = 0;
  unsigned int k0 = 0x53dbcf1;
  const Vec3& base = g_colorMap.Index(k0);
  for (int n = 2; n != 0; n--) {
    unsigned int found = 0xffffffff;
    float best = 0.25f;
    for (unsigned int i = 0; (int)i < 0xc; i++) {
      unsigned int k = i + 0x53dbcf3;
      if (!g_used[i]) {
        if (i > 0xb) k = 0x53dbcf3;
        const Vec3& c = g_colorMap.Index(k);
        float d = (c.x - base.x) * (c.x - base.x) + (c.y - base.y) * (c.y - base.y) + (c.z - base.z) * (c.z - base.z);
        if (d < best) {
          found = i;
          best = d;
        }
      }
    }
    if (found != 0xffffffff) g_used[found] = 1;
  }
}

// @ 0x00b6f280
cColorSet::cColorSet()
: mKey(0x53dbcf1) {
  mDefault = g_defaultColor;
}

// @ 0x00b6f310
unsigned int cColorSet::GetARGB()
{
  unsigned int k = mKey;
  return PackARGB(g_colorMap.Index(k));
}

// @ 0x00b6f380
void cColorSet::LoadNames(wstr* out)
{
  cString_s00b6_e3d0 s;
  s.Load(0xcdf005ab, mKey, L"!!!Color Name");
  wstr tmp;
  tmp.mpBegin = 0;
  tmp.mpEnd = 0;
  tmp.mpCapacity = 0;
  tmp.RangeInitialize(s.GetText());
  if (&tmp != &g_translator->mText0) g_translator->mText0.assign(tmp.mpBegin, tmp.mpEnd);
  if (out != &g_translator->mText1) g_translator->mText1.assign(out->mpBegin, out->mpEnd);
  for (unsigned int i = 0; i < 0x12; i++) {
    s.Load(0xcdf005ab, i, L"!!!Entity Name");
    const wchar_t* p = s.GetText();
    wstr& dst = mNames[i];
    const wchar_t* e = p;
    while (*e) e++;
    dst.assign(p, e);
  }
}
