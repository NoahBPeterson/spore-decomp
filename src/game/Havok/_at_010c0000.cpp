// src/game/Havok/_at_010c0000.cpp -- migrated from slice(s) s010cea90, s010cda80, s010cca60, s010caa30, s010c90a0, s010c44d0, s010c3860, s010c2890, s010c19a0 by tools/migrate/rewrite.py
// Object file: Havok/_at_010c0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include <string.h>
#include <math.h>
#include <new>
#include <xmmintrin.h>

// ---- items of slice s010c19a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct hkCollisionDispatcherOps
{
    void setFlag(char v);                       // 0x010ccbc0
    void registerAlternateShapeTypes();         // 0x010e7d70
    void reg010e7ce0();                         // 0x010e7ce0
    void reg010e6a70();                         // 0x010e6a70
    void reg010e5540();                         // 0x010e5540
    void reg010e1c70();                         // 0x010e1c70
    void reg010ceee0();                         // 0x010ceee0
    void reg010e1720();                         // 0x010e1720
    void reg010e1510();                         // 0x010e1510
    void reg010e0500();                         // 0x010e0500
    void reg010df500();                         // 0x010df500
    void reg010df2c0();                         // 0x010df2c0
    void reg010de080();                         // 0x010de080
    void reg010cef70();                         // 0x010cef70
    void reg010dcfc0();                         // 0x010dcfc0
    void reg010d9f10();                         // 0x010d9f10
    void registerAgentFuncs(int, int);          // 0x01100cf0
    void reg010ff6d0();                         // 0x010ff6d0
    void reg010d9e50();                         // 0x010d9e50
    void reg010fdec0();                         // 0x010fdec0
    void reg010d92a0();                         // 0x010d92a0
    void reg010d8940();                         // 0x010d8940
    void reg010d75f0();                         // 0x010d75f0
    void reg010d64a0();                         // 0x010d64a0
    void reg010d5320();                         // 0x010d5320
    void reg010d41f0();                         // 0x010d41f0
    void reg010fda70();                         // 0x010fda70
    void reg010d2730();                         // 0x010d2730
    void reg010cff70();                         // 0x010cff70
    void reg010cf000();                         // 0x010cf000
};
// ---- items of slice s010c19a0 end

// ---- items of slice s010c2890 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern "C" float __cdecl fabsf(float);
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34
extern const char hkTtrcCapsule[];                  // 0x014a28bc ("TtrcCapsule")
typedef float hkReal;
struct __declspec(align(16)) hkVector4_s010c_2890          // 16 bytes, HK_ALIGN16
{
	union
	{
		hkReal m_quad[4];     // +0x00
		struct { hkReal x, y, z, w; };
	};
};
class hkBool_s010c_2890
{
public:
	hkBool_s010c_2890() {}
	hkBool_s010c_2890(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};
struct hkShapeRayCastInput
{
	hkVector4_s010c_2890 m_from;                    // +0x00
	hkVector4_s010c_2890 m_to;                      // +0x10
	unsigned int m_filterInfo;           // +0x20
	void* m_rayShapeCollectionFilter;    // +0x24
};
struct hkShapeRayCastOutput
{
	float m_normal[4];                   // +0x00
	unsigned int m_shapeKey;             // +0x10
	float m_hitFraction;                 // +0x14
};
struct hkMonitorCommand { const char* m_command; unsigned int m_time0; unsigned int m_pad; };
static __forceinline void hkTimerCommand(const char* name)
{
	void* end = TlsGetValue(g_hkMonitorStreamEndTls);
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
		c->m_command = name;
		volatile unsigned int t = (unsigned int)__rdtsc();
		c->m_time0 = t;
		TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
	}
}
struct hkAabb_s010c_2890             // two vectors
{
	hkVector4_s010c_2890 m_min;      // +0x00
	hkVector4_s010c_2890 m_max;      // +0x10
};
struct hkTransform_s010c_2890
{
	hkReal    m_rotation[12];   // +0x00
	hkVector4_s010c_2890 m_translation;    // +0x30
};
struct hkShape_s010c_2890
{
	unsigned short m_memSizeAndFlags;  // +0x04
	unsigned short m_referenceCount;   // +0x06
	void*          m_userData;         // +0x08
	hkReal         m_radius;           // +0x0c

	hkShape_s010c_2890(hkReal radius) : m_referenceCount(1), m_userData(0), m_radius(radius) {}

	virtual hkReal getMaximumProjection(const hkVector4_s010c_2890& dir) const;   // 0x010c3510

	void setTypeInfo(void* target);                                    // 0x010c3730
};
struct hkSphereShape : public hkShape_s010c_2890
{
	hkSphereShape(hkReal radius);                                      // 0x010c3770

	virtual void getSupportingVertex(const hkVector4_s010c_2890& dir, hkVector4_s010c_2890& vertex) const;   // 0x010c3790
	virtual void convertVertexIdsToVertices(const unsigned short* ids, int numIds,
	                                        hkVector4_s010c_2890* vertices) const;                // 0x010c37b0
	virtual void getFirstVertex(hkVector4_s010c_2890& v) const;                                   // 0x010c37e0
	virtual void getAabb(const hkTransform_s010c_2890& t, hkReal tol, hkAabb_s010c_2890& aabb) const;        // 0x010c3800
	virtual hkBool_s010c_2890 castRay(const hkShapeRayCastInput& input,
	                       hkShapeRayCastOutput& output) const;                        // 0x010c3880
};
struct hkCapsuleShape : public hkSphereShape
{
	hkVector4_s010c_2890 m_vertexA;   // +0x10
	hkVector4_s010c_2890 m_vertexB;   // +0x20

	virtual void getAabb(const hkTransform_s010c_2890& t, hkReal tol, hkAabb_s010c_2890& aabb) const;        // 0x010c2c10
	virtual hkBool_s010c_2890 castRay(const hkShapeRayCastInput& input,
	                       hkShapeRayCastOutput& output) const;                        // 0x010c2e30

	// Static __cdecl helpers (HK_CALL): the addresses carry the identical-code-folded
	// static copies, so the emitted epilogue is a plain `ret`, not thiscall's `ret N`.
	static void closestInfLineSegInfLineSeg(const hkVector4_s010c_2890& p0, const hkVector4_s010c_2890& d0,
	                                        const hkVector4_s010c_2890& p1, const hkVector4_s010c_2890& d1,
	                                        hkReal* outDistance, hkReal* outS, hkReal* outT,
	                                        hkVector4_s010c_2890* outP0, hkVector4_s010c_2890* outP1);        // 0x010c2890
	static void closestPointLineSeg(const hkVector4_s010c_2890& p, const hkVector4_s010c_2890& a, const hkVector4_s010c_2890& b,
	                                hkVector4_s010c_2890& out);                                   // 0x010c2ad0
};
static const hkReal HK_EPSILON = 9.5367431640625e-07f;
static const hkReal HK_RAY_EPS = 1.1920929e-07f;
// ---- items of slice s010c2890 end

// ---- items of slice s010c3860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkTtrcSphere[];                   // 0x014a2934 ("TtrcSphere")
extern char hkGroupFilter_vtbl0[];             // 0x014a2970
extern char hkGroupFilter_vtbl1[];             // 0x014a2968
extern char hkGroupFilter_vtbl2[];             // 0x014a2960
extern char hkGroupFilter_vtbl3[];             // 0x014a2958
extern char hkGroupFilter_vtbl4[];             // 0x014a2950
extern void* hkMemory_s_instance;                             // 0x016e4178
struct hkMonitorCommand_s010c_3860 { const char* m_command; uint32_t m_time0; uint32_t m_pad; };
static __forceinline void hkTimerCommand_s010c_3860(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
    {
        hkMonitorCommand_s010c_3860* c = (hkMonitorCommand_s010c_3860*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        c->m_command = name;
        volatile uint32_t t = (uint32_t)__rdtsc();
        c->m_time0 = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
    }
}
class hkBool_s010c_3860
{
public:
    hkBool_s010c_3860() {}
    hkBool_s010c_3860(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    char m_bool;
};
class __declspec(align(16)) hkVector4_s010c_3860 { public: float x, y, z, w; };
class __declspec(align(16)) hkSphere { public: float x, y, z, w; };
struct hkShapeRayCastInput_s010c_3860
{
    hkVector4_s010c_3860 m_from;                   // +0
    hkVector4_s010c_3860 m_to;                     // +0x10
    uint32_t m_filterInfo;              // +0x20
    void* m_rayShapeCollectionFilter;   // +0x24
};
struct hkShapeRayCastOutput_s010c_3860
{
    float m_normal[4];                  // +0
    uint32_t m_shapeKey;                // +0x10
    float m_hitFraction;                // +0x14
};
class hkAabb_s010c_3860
{ public:
    hkVector4_s010c_3860 m_min;
    hkVector4_s010c_3860 m_max;
};
class hkTransform_s010c_3860;
extern "C" void hkVector4__setTransformedPos(hkVector4_s010c_3860* self, const hkTransform_s010c_3860* t, const hkVector4_s010c_3860* v);
class hkShape_s010c_3860
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual hkBool_s010c_3860 castRay(const hkShapeRayCastInput_s010c_3860& input, hkShapeRayCastOutput_s010c_3860& output) const;
    virtual void getAabb(const hkTransform_s010c_3860& t, float tolerance, hkAabb_s010c_3860& aabb) const;
    virtual void getSupportingVertex(const hkVector4_s010c_3860& dir, void* v) const;
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;
    uint32_t m_memSizeAndFlags;         // +4
    uint32_t m_userData;                // +8
};
class hkSphereShape_s010c_3860 : public hkShape_s010c_3860
{
public:
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;                                  // 0x010c3860
    virtual hkBool_s010c_3860 castRay(const hkShapeRayCastInput_s010c_3860& input, hkShapeRayCastOutput_s010c_3860& output) const;    // 0x010c3880
    float m_radius;                     // +0xc
};
class hkTriangleShape : public hkShape_s010c_3860
{
public:
    virtual void getAabb(const hkTransform_s010c_3860& t, float tolerance, hkAabb_s010c_3860& aabb) const;                 // 0x010c4140
    virtual hkSphere* getCollisionSpheres(hkSphere* spheres) const;                                  // 0x010c4390
    virtual void getSupportingVertex(const hkVector4_s010c_3860& dir, void* v) const;                           // 0x010c4400
    void initShape(void* shape);                                                                     // 0x010c3fc0
    float m_radius;                     // +0xc
    hkVector4_s010c_3860 m_vertexA;                // +0x10
    hkVector4_s010c_3860 m_vertexB;                // +0x20
    hkVector4_s010c_3860 m_vertexC;                // +0x30
};
struct hkCollisionInput_s010c_3860;
class hkCdBody_s010c_3860;
struct hkShapeCollection;
class hkGroupFilter
{
public:
    hkGroupFilter();                    // 0x010c3cb0
    virtual void v0();
    virtual void v1();
    virtual hkBool_s010c_3860 isCollisionEnabled(const hkCollisionInput_s010c_3860& input, const hkCdBody_s010c_3860& bodyA,
                                      const hkCdBody_s010c_3860& bodyB, const hkShapeCollection& collection,
                                      uint32_t filterInfo) const;                          // 0x010c3df0
    hkBool_s010c_3860 testAgainstBody(hkBool_s010c_3860* out, hkCdBody_s010c_3860* body, void* collection, uint32_t key);   // 0x010c3bf0
    hkGroupFilter* destroy(char flags);                                                    // 0x010c3ef0
    void enableCollisionsBetween(int a, int b);   // 0x010c3c20
    uint16_t m_refCount;                // +4
    uint16_t m_lockCount;               // +6
    void* m_filter0;                    // +8
    void* m_filter1;                    // +0xc
    void* m_filter2;                    // +0x10
    void* m_filter3;                    // +0x14
    uint32_t m_defaultIsColliding;      // +0x18
    uint32_t m_groupBits[32];           // +0x1c
};
class hkGroupFilterBase
{
public:
    char pad[0x1c];
    uint32_t m_groupBits[32];           // +0x1c
    void testEnabled(hkBool_s010c_3860* out, uint32_t c, uint32_t d) const;
    void disableCollisionsBetween(uint32_t a, uint32_t b);   // 0x010c3c60
};
class hkCollisionFilterBase
{
public:
    void dtor();        // 0x005efd40, __thiscall (ecx = this)
};
class hkCdBody_s010c_3860
{ public:
    void* m_shape;          // +0
    int   m_shapeKey;       // +4
    void* m_motion;         // +8
    void* m_child;          // +0xc
};
// ---- items of slice s010c3860 end

// ---- items of slice s010c44d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned long g_hkMonitorStreamCurTls;   // 0x016e42a4
extern const char    hkTimerEnd[];              // 0x0149cc34 (timer end marker)
extern const char    hkTtrcTriangle[];          // 0x014a3c30 ("TtrcTriangle")
extern "C" void hkArrayUtil_grow(void* array, int elemSize);                  // 0x0107f530
extern "C" void hkArrayUtil_reserveExactly(void* array, int n, int elemSize); // 0x0107f4a0
#pragma pack(push, 4)
struct hkMonitorRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; };
static void hkTimerBegin(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorRecord* r = (hkMonitorRecord*)cur;
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
static void hkTimerEndStamp()
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorRecord* r = (hkMonitorRecord*)cur;
        r->m_name = hkTimerEnd;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
class hkReferencedObject_s010c_44d0 {
public:
    virtual void v0();          // +0x00 (dtor slot, scalar deleting)
    virtual void v1();          // +0x04 (dtor slot)
    uint16_t m_memSizeAndFlags;   // +0x04  (note: real layout +4/+6)
    uint16_t m_referenceCount;    // +0x06
    void removeReference()
    {
        if (m_memSizeAndFlags != 0 && --m_referenceCount == 0)
            delete this;
    }
};
class __declspec(align(16)) hkVector4_s010c_44d0 { public: float x, y, z, w; };
class hkTransform_s010c_44d0 { public: hkVector4_s010c_44d0 m_rotation[3]; hkVector4_s010c_44d0 m_translation; };   // 0x40
class hkAabb_s010c_44d0      { public: hkVector4_s010c_44d0 m_min, m_max; };                            // 0x20
class hkBool_s010c_44d0 {
public:
    char m_bool;
    hkBool_s010c_44d0() {}
    hkBool_s010c_44d0(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};
struct hkShapeRayCastInput_s010c_44d0 {
    hkVector4_s010c_44d0 m_from;          // +0x00
    hkVector4_s010c_44d0 m_to;            // +0x10
    uint32_t    m_filterInfo;    // +0x20
    void*     m_filter;        // +0x24
};
struct hkShapeRayCastOutput_s010c_44d0 {
    float     m_normal[4];     // +0x00
    uint32_t    m_shapeKey;      // +0x10
    float     m_hitFraction;   // +0x14
};
struct hkArrayU32 { uint32_t* m_data; int m_size; int m_capacityAndFlags; };
class hkSphere_s010c_44d0 { public: hkVector4_s010c_44d0 m_center; float m_radius; };
class hkShape_s010c_44d0 : public hkReferencedObject_s010c_44d0 {
public:
    uint32_t m_userData;                                                            // +0x08
    // slots 0 (+0x00) and 1 (+0x04) are the destructors inherited from hkReferencedObject
    virtual void vslot2();                                                          // +0x08
    virtual void getAabb(const hkTransform_s010c_44d0& t, float tol, hkAabb_s010c_44d0& out) const;        // +0x0c
    virtual void vslot4();                                                          // +0x10
    virtual hkBool_s010c_44d0 castRay(const hkShapeRayCastInput_s010c_44d0& in, hkShapeRayCastOutput_s010c_44d0& out) const;  // +0x14
    virtual void vslot6();                                                          // +0x18
    virtual void vslot7();                                                          // +0x1c
    virtual void vslot8();                                                          // +0x20
};
class hkShapeCollection_s010c_44d0 : public hkShape_s010c_44d0 {
public:
    uint8_t m_disableWelding;   // +0x0c
    virtual uint32_t getNextKey(uint32_t k) const;                                      // +0x24
    virtual const hkShape_s010c_44d0* getChildShape(uint32_t k, char (&buf)[512]) const;            // +0x28
};
class hkHeightFieldShape : public hkShape_s010c_44d0 {
public:
    // slot +0x24 of a heightfield is getHeight(x, z)
    virtual float getHeight(int x, int z) const;
    virtual const hkShape_s010c_44d0* getChildShape(uint32_t k, char (&buf)[512]) const;            // +0x28
};
class hkSampledHeightFieldShape : public hkHeightFieldShape {
public:
    int32_t     m_xRes;                            // +0x0c
    int32_t     m_zRes;                            // +0x10
    float     m_heightCenter;                    // +0x14
    hkVector4_s010c_44d0 m_intToFloatScale;                 // +0x20
    hkVector4_s010c_44d0 m_floatToIntScale;                 // +0x30
    hkVector4_s010c_44d0 m_floatToIntOffsetFloorCorrected;  // +0x40
};
class hkTriangleShape_s010c_44d0 : public hkShape_s010c_44d0 {
public:
    float     m_radius;        // +0x0c
    hkVector4_s010c_44d0 m_vertexA;       // +0x10
    hkVector4_s010c_44d0 m_vertexB;       // +0x20
    hkVector4_s010c_44d0 m_vertexC;       // +0x30
    hkBool_s010c_44d0 castRay(const hkShapeRayCastInput_s010c_44d0& in, hkShapeRayCastOutput_s010c_44d0& out) const;
};
class hkTriSampledHeightFieldCollection : public hkShapeCollection_s010c_44d0 {
public:
    hkSampledHeightFieldShape* m_heightfield;   // +0x10
    float                      m_radius;        // +0x14

    ~hkTriSampledHeightFieldCollection();

    void getAabb(const hkTransform_s010c_44d0& t, float tol, hkAabb_s010c_44d0& out) const;
    uint32_t getNextKey(uint32_t key) const;
    const hkShape_s010c_44d0* getChildShape(uint32_t key, char (&buf)[512]) const;
};
class hkBvTreeShape : public hkShape_s010c_44d0 {
public:
    hkShapeCollection_s010c_44d0* m_shapeCollection;   // +0x0c
    virtual void queryAabb(const hkAabb_s010c_44d0& aabb, hkArrayU32& hits) const;   // +0x24
    virtual void queryObb(const hkTransform_s010c_44d0& t, const hkVector4_s010c_44d0& extents, float tol,
                          hkArrayU32& hits) const;                        // +0x28
};
class hkTriSampledHeightFieldBvTreeShape : public hkBvTreeShape {
public:
    hkBool_s010c_44d0 m_wantAabbRejectionTest;         // +0x10

    ~hkTriSampledHeightFieldBvTreeShape();

    hkBool_s010c_44d0 castRay(const hkShapeRayCastInput_s010c_44d0& in, hkShapeRayCastOutput_s010c_44d0& out) const;
    void castRayWithCollector(const hkShapeRayCastInput_s010c_44d0& in, const void* body, void* collector) const;
    void queryAabb(const hkAabb_s010c_44d0& aabb, hkArrayU32& hits) const;
    void querySphere(const hkSphere_s010c_44d0& s, hkArrayU32& hits) const;
    void queryObb(const hkTransform_s010c_44d0& t, const hkVector4_s010c_44d0& extents, float tol, hkArrayU32& hits) const;
};
// ---- items of slice s010c44d0 end

// ---- items of slice s010c90a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_hkSupportScale;       // 0x015ba2d0  scale applied to the supporting-vertex angle
extern float g_hkAngleStep;          // 0x015ba2d4  (2*pi / 16, the 16-fold angle step)
extern float g_hkFpuRoundingValue;   // 0x015ba2d8  initialised by the ctor below
struct hkVector4_s010c_90a0
{
    float x, y, z, w;
};
struct hkCdVertex
{
    float x, y, z, w;
};
struct hkAabb_s010c_90a0
{
    hkVector4_s010c_90a0 m_min;   // +0x00
    hkVector4_s010c_90a0 m_max;   // +0x10
};
struct hkSphere_s010c_90a0
{
    hkVector4_s010c_90a0 m_pos;
};
struct hkTransform_s010c_90a0
{
    float m[16];   // 3x3 rotation in the leading 12 floats, translation in the last vector
};
struct hkCylinderShape
{
    virtual void v00();                                                             // slot 0  0x010dd550
    virtual void v01();                                                             // slot 1  0x010c9030
    virtual void v02();                                                             // slot 2  0x010c9020
    virtual void getAabb(const hkTransform_s010c_90a0& transform, float tolerance, hkAabb_s010c_90a0& aabb) const;  // slot 3
    virtual void v04();                                                             // slot 4  0x010c0f80
    virtual void v05();                                                             // slot 5  0x010c9c70
    virtual void v06();                                                             // slot 6  0x010c0fc0
    virtual void v07();                                                             // slot 7  0x010c9000
    virtual const hkSphere_s010c_90a0* getCollisionSpheres(hkSphere_s010c_90a0* spheres) const;           // slot 8
    virtual void getSupportingVertex(const hkVector4_s010c_90a0& direction, hkCdVertex& vertex) const;  // slot 9
    virtual void convertVertexIdsToVertices(const unsigned short* ids, int numIds,
                                            hkCdVertex* vertices) const;            // slot 10
    virtual void getFirstVertex(hkVector4_s010c_90a0& vertex) const;                           // slot 11

    uint16_t m_memSizeAndFlags;   // +0x04
    uint16_t m_referenceCount;    // +0x06
    int32_t  m_userData;          // +0x08
    float    m_radius;            // +0x0c
    float    m_cylRadius;         // +0x10
    uint32_t m_pad14[3];          // +0x14
    hkVector4_s010c_90a0 m_vertexA;          // +0x20
    hkVector4_s010c_90a0 m_vertexB;          // +0x30
    hkVector4_s010c_90a0 m_perpendicular1;   // +0x40
    hkVector4_s010c_90a0 m_perpendicular2;   // +0x50
};
// ---- items of slice s010c90a0 end

// ---- items of slice s010caa30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned long g_hkThreadMemoryTls;                        // 0x016e4174
extern "C" void* hkConvexPieceShape_ctor(void* self, float radius);              // 0x010eb440
extern "C" void  hkThreadMemory_deallocateChunk(void* self, void* p, int n, int c); // 0x0107db10
typedef unsigned char  hkUint8;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
class hkBool_s010c_aa30 { public: hkUint8 m_bool; hkBool_s010c_aa30() {} hkBool_s010c_aa30(const hkBool_s010c_aa30& o) : m_bool(o.m_bool) {} };
class hkReferencedObject_s010c_aa30 { public:
    void**   m_vptr;              // +0x0
    hkUint16 m_memSizeAndFlags;   // +0x4
    hkUint16 m_referenceCount;    // +0x6
};
class hkShape_s010c_aa30 : public hkReferencedObject_s010c_aa30 { public: hkUint32 m_pad08; };  // size 0xc
class hkShapeCollection_s010c_aa30_s010c_aa30 : public hkShape_s010c_aa30 { public:                      // size 0x10
    hkUint8 m_disableWelding;     // +0xc
    hkUint8 m_pad0d[3];
};
class hkConvexShape : public hkShape_s010c_aa30 { public: };
class hkVector4_s010c_aa30 { public: float x, y, z, w; };
class hkTransform_s010c_aa30 { public:                                             // size 0x40
    float m_col[16];              // +0x00  (4 columns of hkVector4)
};
struct hkConvexTransformShape : public hkConvexShape {           // size 0x60
    hkUint32       m_pad0c;       // +0xc
    hkConvexShape* m_childShape;  // +0x10
    float          m_pad14[3];    // +0x14
    hkTransform_s010c_aa30    m_transform;   // +0x20
    float          m_pad60;       // +0x60

    void convertVertexIdsToVertices(const void* ids, int num, hkVector4_s010c_aa30* out);  // 0x010caa30
    void getFirstVertex(hkVector4_s010c_aa30& out);                                        // 0x010cadb0
    int  getCollisionSpheres(void* out);                                        // 0x010cae40
};
template<class T> class hkArray { public:
    T*  m_data;                   // +0x0
    int m_size;                   // +0x4
    int m_capacityAndFlags;       // +0x8
};
struct hkConvexPieceStreamData : public hkReferencedObject_s010c_aa30 {     // size 0x2c
    hkArray<hkUint32> m_convexPieceStream;              // +0x8
    hkArray<hkUint32> m_convexPieceOffsets;             // +0x14
    hkArray<hkUint32> m_convexPieceSingleTriangles;     // +0x20
};
class hkAabb_s010c_aa30 { public:                                                  // size 0x20
    hkVector4_s010c_aa30 m_min;              // +0x0
    hkVector4_s010c_aa30 m_max;              // +0x10
};
struct hkConvexPieceMeshShape : public hkShapeCollection_s010c_aa30_s010c_aa30 {       // size 0x1c
    hkConvexPieceStreamData* m_convexPieceStream;   // +0x10
    hkShapeCollection_s010c_aa30_s010c_aa30*       m_displayMesh;         // +0x14
    hkReal                   m_radius;              // +0x18

    hkUint32 getNextKey(hkUint32 key);              // @ 0x010cb230
    void*    getChildShape(hkUint32 key, char (&storage)[0xc0]);  // @ 0x010cb250
    hkUint32 getCollisionFilterInfo(hkUint32 key);// @ 0x010cb490
    void     getAabb(const hkTransform_s010c_aa30&, float, hkAabb_s010c_aa30&);  // @ 0x010cb4d0
    void     calcStatistics(void* collector);       // @ 0x010cb6a0
    void*    scalarDeletingDtor(hkUint32 flags);    // @ 0x010cb630
};
class hkCollisionFilter_s010c_aa30 : public hkReferencedObject_s010c_aa30 { public: hkUint32 m_pad[4]; };   // size 0x18
struct hkCollidable; struct hkCollisionInput; struct hkCdBody; class hkShapeCollection_s010c_aa30_s010c_aa30;
struct hkShapeRayCastInput; struct hkWorldRayCastInput;
struct hkCollisionFilterList : public hkCollisionFilter_s010c_aa30 {        // size 0x24
    hkArray<void*> m_collisionFilters;   // +0x18

    hkBool_s010c_aa30 isCollisionEnabled(const hkCollidable&, const hkCollidable&);          // 0x010cb7b0
    hkBool_s010c_aa30 isCollisionEnabled2(const hkCollisionInput&, const hkCdBody&,
                               const hkCollisionFilterList&, const hkShapeCollection_s010c_aa30_s010c_aa30&, hkUint32); // 0x010cb800
    hkBool_s010c_aa30 isCollisionEnabled3(const hkShapeRayCastInput&, const hkShapeCollection_s010c_aa30_s010c_aa30&, hkUint32); // 0x010cb860
    hkBool_s010c_aa30 isCollisionEnabled4(const hkWorldRayCastInput&, const hkCollidable&);   // 0x010cb8c0

    void dtor();                                                                    // 0x010cb9a0
};
struct hkShapeIface {
virtual void d00();
virtual void d01();
virtual void d02();
virtual void d03();
virtual void d04();
virtual void d05();
virtual void d06();
virtual void d07();
virtual void d08();
virtual void d09();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual void d23();
virtual void d24();
virtual void d25();
virtual void d26();
virtual void d27();
virtual void d28();
virtual void d29();
virtual void d30();
virtual void d31();
virtual void d32();
virtual void d33();
virtual void d34();
virtual void d35();
virtual void d36();
virtual void d37();
virtual void d38();
virtual void d39();
    virtual void getAabb(const hkTransform_s010c_aa30&, float, hkAabb_s010c_aa30&);   // +0xa0
};
struct hkShapeVtbl {
virtual void   d00();
virtual void   d01();
virtual void   d02();
virtual void   d03();
virtual void   d04();
virtual void   d05();
virtual void   d06();
virtual void   d07();
    virtual hkUint32 getFirstKey();                        // +0x20
    virtual hkUint32 getNextKey(hkUint32);                 // +0x24
    virtual void*  getChildShape(hkUint32);                // +0x28
    virtual hkUint32 getCollisionFilterInfo(hkUint32);     // +0x2c
    virtual void   getAabb(const hkTransform_s010c_aa30&, float, hkAabb_s010c_aa30&);  // +0x30
};
struct hkConvexShapeVtbl {
virtual void   d00();
virtual void   d01();
virtual void   d02();
virtual void   d03();
virtual void   d04();
virtual void   d05();
virtual void   d06();
virtual void   d07();
virtual void   d08();
virtual void   d09();
virtual void   d10();
virtual void   d11();
    virtual int    getFirstVertex(hkVector4_s010c_aa30& out);                                  // +0x20
    virtual void   convertVertexIdsToVertices(const void* ids, int num, hkVector4_s010c_aa30* out); // +0x28
virtual void   d14();
virtual void   d15();
    virtual int    getCollisionSpheres(void* out);                                  // +0x3c
};
struct RefObj {
    virtual void* dtor(hkUint32 flags);    // +0x0
    hkUint16     m_memSizeAndFlags;        // +0x4
    hkUint16     m_referenceCount;         // +0x6
};
// ---- items of slice s010caa30 end

// ---- items of slice s010cca60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char hkBool;
typedef int hkShapeType;
class hkStatisticsCollector;
class hkpContactMgrFactory;
class hkCollisionDispatcher_s010c_ca60;
struct hkRefCounted
{
	void** m_vptr;                          // 0x000
	unsigned short m_memSizeAndFlags;       // 0x004
	unsigned short m_referenceCount;        // 0x006

	typedef void (hkRefCounted::*DeletingDtor)(int);

	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			m_referenceCount = (unsigned short)(m_referenceCount - 1);
			if (m_referenceCount == 0)
			{
				union { void* p; DeletingDtor d; } u;
				u.p = m_vptr[0];
				(this->*u.d)(1);
			}
		}
	}
};
class hkpContactMgrFactory : public hkRefCounted {};
class hkStatisticsCollector
{
public:
	virtual void v00();                                                     // +0x00
	virtual void beginObject(const char* name, int mode, const void* obj);  // +0x04
	virtual void addArray(const char* name, int elemSize, const void* ptr,
	                      int usedBytes, int allocBytes);                   // +0x08
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void endObject();                                               // +0x18
};
struct hkArrayUtil
{
	static void _reserveMore(void* arrayBase, int elemSize);    // 0x0107F530
};
enum { HK_ARRAY_CAPACITY_MASK = 0x3fffffff };
template <typename T>
class hkArray_s010c_ca60
{
public:
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
	void pushBack(const T& t)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		T* slot = &m_data[m_size];
		m_size = m_size + 1;
		*slot = t;
	}
};
struct hkCollisionQualityInfo_s010c_ca60
{
	float m_keepContact;                    // 0x00
	float m_create4dContact;                // 0x04
	float m_createContact;                  // 0x08
	float m_manifoldTimDistance;            // 0x0c
	hkBool m_useContinuousPhysics;          // 0x10
	float m_minSeparation;                  // 0x14
	float m_minExtraSeparation;             // 0x18
	float m_minSafeDeltaTime;               // 0x1c
	float m_minAbsoluteSafeDeltaTime;       // 0x20
	float m_toiSeparation;                  // 0x24
	float m_toiExtraSeparation;             // 0x28
	float m_toiAccuracy;                    // 0x2c
	float m_maxContraintViolation;          // 0x30
	float m_minToiDeltaTime;                // 0x34
	unsigned short m_constraintPriority;    // 0x38
};
struct AgentFuncs
{
	void (*m_createFunc)();             // 0x00
	void (*m_getPenetrationsFunc)();    // 0x04
	void (*m_getClosestPointFunc)();    // 0x08
	void (*m_linearCastFunc)();         // 0x0c
	hkBool m_isFlipped;                 // 0x10
	hkBool m_isPredictive;              // 0x11
};
struct Agent3Funcs
{
	void (*m_createFunc)();             // 0x00
	void (*m_destroyFunc)();            // 0x04
	void (*m_cleanupFunc)();            // 0x08
	void (*m_removePointFunc)();        // 0x0c
	void (*m_commitPotentialFunc)();    // 0x10
	void (*m_createZombieFunc)();       // 0x14
	void (*m_updateFilterFunc)();       // 0x18
	void (*m_invalidateTimFunc)();      // 0x1c
	void (*m_warpTimeFunc)();           // 0x20
	void (*m_sepNormalFunc)();          // 0x24
	void (*m_processFunc)();            // 0x28
	hkBool m_isPredictive;              // 0x2c
	hkBool m_ignoreSymmetricVersion;    // 0x2d
};
struct Agent3FuncsIntern : Agent3Funcs
{
	int m_symmetric;                    // 0x30
};
struct DebugEntry
{
	char m_typeA;                       // 0x00
	char m_typeB;                       // 0x01
	char m_priority;                    // 0x02
};
struct ShapeInheritance
{
	hkShapeType m_primaryType;          // 0x00
	hkShapeType m_alternateType;        // 0x04
};
struct InitCollisionQualityInfo
{
	float m_gravityLength;                          // 0x00
	float m_collisionTolerance;                     // 0x04
	float m_minDeltaTime;                           // 0x08
	float m_maxLinearVelocity;                      // 0x0c
	unsigned short m_defaultConstraintPriority;     // 0x10
	unsigned short m_toiConstraintPriority;         // 0x12
	unsigned short m_toiHigherConstraintPriority;   // 0x14
	unsigned short m_toiForcedConstraintPriority;   // 0x16
	hkBool m_wantContinuousCollisionDetection;      // 0x18
	hkBool m_enableNegativeManifoldTims;            // 0x19
	hkBool m_enableNegativeToleranceToCreateNon4dContacts; // 0x1a
};
class hkCollisionDispatcher_s010c_ca60
{
public:
	void** m_vptr;                                          // 0x000
	unsigned short m_memSizeAndFlags;                       // 0x004
	unsigned short m_referenceCount;                        // 0x006
	void (*m_defaultCollisionAgent)();                      // 0x008
	hkpContactMgrFactory* m_contactMgrFactory[8][8];        // 0x00c
	unsigned int m_hasAlternateType[32];                    // 0x10c
	int m_numAgent2Types;                                   // 0x18c
	unsigned char m_agent2Types[32][32];                    // 0x190
	unsigned char m_agent2TypesPred[32][32];                // 0x590
	AgentFuncs m_agent2Func[64];                            // 0x990
	int m_numAgent3Types;                                   // 0xe90
	unsigned char m_agent3Types[32][32];                    // 0xe94
	unsigned char m_agent3TypesPred[32][32];                // 0x1294
	Agent3FuncsIntern m_agent3Func[16];                     // 0x1694
	char m_collisionQualityTable[8][8];                     // 0x19d4
	hkCollisionQualityInfo_s010c_ca60 m_collisionQualityInfo[8];       // 0x1a14
	hkBool m_collisionAgentRegistered;                      // 0x1bf4
	hkBool m_agent3Registered;                              // 0x1bf5
	int m_agent3SectorSize;                                 // 0x1bf8
	int m_agent3AgentSize;                                  // 0x1bfc
	hkBool m_checkEnabled;                                  // 0x1c00
	hkArray_s010c_ca60<ShapeInheritance> m_shapeInheritance;           // 0x1c04
	DebugEntry (*m_debugAgent2Table)[32][32];               // 0x1c10
	DebugEntry (*m_debugAgent2TablePred)[32][32];           // 0x1c14
	DebugEntry (*m_debugAgent3Table)[32][32];               // 0x1c18
	DebugEntry (*m_debugAgent3TablePred)[32][32];           // 0x1c1c
	float m_expectedMaxLinearVelocity;                      // 0x1c20
	float m_expectedMinPsiDeltaTime;                        // 0x1c24

	void resetCreationFunctions();
	void registerContactMgrFactoryWithAll(hkpContactMgrFactory* factory, int responseA);
	void calcStatistics(hkStatisticsCollector* c) const;
	void disableDebugging();
	void internalRegisterCollisionAgent(unsigned char (*agentTypes)[32], int agentType,
	                                    hkShapeType typeA, hkShapeType typeB,
	                                    hkShapeType typeAReg, hkShapeType typeBReg,
	                                    DebugEntry (*debugTable)[32][32], int level);
	void updateHasAlternateType(hkShapeType typeA, hkShapeType typeB, int level);
	void initCollisionQualityInfo(InitCollisionQualityInfo& info);
	void registerCollisionAgent(AgentFuncs& funcs, hkShapeType typeA, hkShapeType typeB);
	int registerAgent3(Agent3Funcs& funcs, hkShapeType typeA, hkShapeType typeB);
	void registerAlternateShapeType(hkShapeType typeA, hkShapeType typeB);
	hkCollisionDispatcher_s010c_ca60* init(hkpContactMgrFactory* factory);
	~hkCollisionDispatcher_s010c_ca60();
};
const char* hkShapeType_toString(int type);                         // 0x010E7E30
int hkString_snprintf(char* buf, int size, const char* fmt, ...);   // 0x0107F390
// ---- items of slice s010cca60 end

// ---- items of slice s010cda80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void hkAgent1nMachine_UpdateShapeCollectionFilter(void* machine,
                                                            void* args);   // 0x01104740
struct hkCollisionInput_s010c_da80;                     // opaque
class hkStatisticsCollector_s010c_da80 { public:
    virtual void v00();                                                    // +0x00
    virtual void addObjectStat(const char* name, int id, const void* obj);// +0x04
    virtual void addBufferStat(const char* name, int id, const void* p,
                               unsigned size, unsigned cap);              // +0x08
};
struct hkArrayInt {
    int* m_data;                 // +0x00
    int  m_size;                 // +0x04
    int  m_capacityAndFlags;     // +0x08

    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }
};
struct hkBvTreeStreamAgent {
    unsigned char pad_000[0x10];
    hkUint32      v10, v14, v18, v1c;        // +0x10..+0x1c
    hkUint32      v20, v24, v28, v2c;        // +0x20..+0x2c
    hkArrayInt    m_sectors;                 // +0x30 (hkArray<int> sector list)

    void invalidateTim(hkCollisionInput_s010c_da80& in);                        // 010cda80
    void warpTime(float dt, float t, hkCollisionInput_s010c_da80& in);          // 010cdaa0
    void updateShapeCollectionFilter(void* a, void* b, void* c);     // 010cdac0
    void* scalarDeletingDtor(unsigned int flags);                    // 010cdca0
    void calcStatistics(hkStatisticsCollector_s010c_da80* c) const;             // 010cdcd0
};
void hkTrackerCalcStatistics(void* machine, hkStatisticsCollector_s010c_da80* c);     // 0x010fce10
struct hkLessUint { };
// ---- items of slice s010cda80 end

// ---- items of slice s010cea90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0107f4a0(void* arr, int n, int elem);                // hkArrayUtil::_reserveExactly
extern "C" void  FUN_010e49c0(int a, int b, void* cp, void* c1, void* c2);
extern "C" void  FUN_010e4d50(int a, int b, int c, void* collector);
extern "C" void  FUN_010810f0(void* dst, int dummy, float* a, float* b);  // __thiscall setMulInverseMul
extern "C" void  FUN_01081360(void* dst, int dummy, void* tr, float* v);  // __thiscall setTransformedPos
extern "C" void  FUN_010814a0(void* dst, int dummy, void* tr, void* v);   // __thiscall setRotatedDir
extern "C" void __stdcall FUN_01103bc0(void* p);                          // hkAgent1nMachine::Create
extern "C" __declspec(dllimport) void* __stdcall TlsSetValue_s010c_ea90(unsigned idx, void* v);
struct HkMemory {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int align);                 // vtbl +0x10
    virtual void  release(void* p, unsigned short f, int a);  // vtbl +0x14
};
#define HKMEM (*(HkMemory**)0x016e4178)
struct HkThreadMemory {
    void __thiscall deallocateChunk(void* p, int bytes, int align);
};
#define THREADMEM(p) ((HkThreadMemory*)(p))
struct BvAgentApi {
    void __thiscall processCollision(int a, int b, int c, int* d);   // 0x010cdd30
};
struct ContactMgr {
    virtual void v0();
    virtual void v1();
    virtual unsigned short makeContact(int* a, int* b, int* in, void* pt); // vtbl +8
    virtual void v2();
    virtual void release(int id);                                       // vtbl +0x10
};
struct RayShape {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual char castRay(char* hit, float* p0, float* nrm);             // vtbl +0x14
};
struct PointCollector {
    virtual void v0();
    virtual char addPoint(void* pt);                                    // vtbl +4
};
struct HkTransform {
    float m[16];
};
struct CdPoint {
    float pos[4];     // +0x00
    float nrm[3];     // +0x10
    float dist;       // +0x1c
    int   pad[4];     // +0x20 .. +0x2f
};
struct HkArray {
    void* begin;      // +0x00
    int   count;      // +0x04
    int   cap;        // +0x08
};
struct MRayAgent {
    void*        vtbl;   // +0x00
    unsigned short tag4;  // +0x04 class tag (0x20)
    unsigned short flags; // +0x06
    int          mgr;    // +0x08
    unsigned short* map; // +0x0c
    int          count;  // +0x10
    int          cap;    // +0x14
};
struct BvStreamAgent {
    void*        vtbl;       // +0x00
    unsigned short tag4;     // +0x04 class tag (0x40)
    unsigned short flags;    // +0x06
    int          mgr;        // +0x08
    int          field0c;    // +0x0c
    int          pad10[8];   // +0x10 .. +0x2f
    void*        arr;        // +0x30 begin
    int          arrCount;   // +0x34
    int          arrCap;     // +0x38
};
#define BV_ARR(p) (*(HkArray*)((char*)(p) + 0x30))
struct V4 { float v[4]; };
struct ContactPoint {
    V4 p;   // +0x00
    V4 n;   // +0x10
};
static void __fastcall cpSetFlipped(ContactPoint* self, int, const ContactPoint* o)
{
    float d = o->n.v[3];
    self->p = o->p;
    self->p.v[0] = d * o->n.v[0] + self->p.v[0];
    self->p.v[1] = d * o->n.v[1] + self->p.v[1];
    self->p.v[2] = d * o->n.v[2] + self->p.v[2];
    self->p.v[3] = d * o->n.v[3] + self->p.v[3];
    self->n.v[0] = -o->n.v[0];
    self->n.v[1] = -o->n.v[1];
    self->n.v[2] = -o->n.v[2];
    *(int*)&self->n.v[3] = *(int*)&o->n.v[3];
}
static void monMark(int tag)
{
    void* end = TlsGetValue(0x016e42a8);
    void* cur = TlsGetValue(0x016e42a4);
    if (cur < end) {
        int* p = (int*)TlsGetValue(0x016e42a4);
        p[0] = tag;
        p[1] = (int)__rdtsc();
        TlsSetValue_s010c_ea90(0x016e42a4, p + 3);
    }
}
struct QueryResult {
    void* vtbl;   // +0x00
    int   dist;   // +0x04
    float p[4];   // +0x08 .. +0x17
    int   user;   // +0x18
};
static __forceinline void mrClosestPoints(int* bodyA, int* bodyB, int* input, int* collector)
{
    int* shapeA = (int*)*bodyA;
    RayShape* shapeB = (RayShape*)*bodyB;
    HkTransform t;
    int n;
    float* ray;
    int i;

    monMark(0x14a4478);   // "TtmultiRay-cvx"
    FUN_010810f0(&t, 0, (float*)bodyB[2], (float*)bodyA[2]);

    n = shapeA[4];
    ray = (float*)shapeA[3];
    for (i = 0; i < n; i++) {
        __declspec(align(16)) float p0[4], p1[4], nrm[4];
        char hit;

        p0[0] = t.m[0] * ray[0] + (t.m[4] * ray[1] + t.m[8] * ray[2]) + t.m[12];
        p0[1] = t.m[1] * ray[0] + (t.m[5] * ray[1] + t.m[9] * ray[2]) + t.m[13];
        p0[2] = t.m[2] * ray[0] + (t.m[6] * ray[1] + t.m[10] * ray[2]) + t.m[14];
        p0[3] = 0.0f;

        p1[0] = t.m[0] * ray[4] + (t.m[4] * ray[5] + t.m[8] * ray[6]) + t.m[12];
        p1[1] = t.m[1] * ray[4] + (t.m[5] * ray[5] + t.m[9] * ray[6]) + t.m[13];
        p1[2] = t.m[2] * ray[4] + (t.m[6] * ray[5] + t.m[10] * ray[6]) + t.m[14];
        p1[3] = 0.0f;

        shapeB->castRay(&hit, p0, nrm);
        if (hit) {
            float* T = (float*)bodyB[2];
            CdPoint pt;
            float f;
            int j;

            f = 1.0f - 1.0f;
            pt.pos[0] = (p1[0] * 1.0f + p0[0] * f) * T[0]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[4]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[8]) + T[12];
            pt.pos[1] = (p1[0] * 1.0f + p0[0] * f) * T[1]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[5]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[9]) + T[13];
            pt.pos[2] = (p1[0] * 1.0f + p0[0] * f) * T[2]
                      + ((p1[1] * 1.0f + p0[1] * f) * T[6]
                      +  (p1[2] * 1.0f + p0[2] * f) * T[10]) + T[14];
            pt.pos[3] = 0.0f;
            pt.nrm[0] = nrm[0] * T[0] + (nrm[1] * T[4] + nrm[2] * T[8]);
            pt.nrm[1] = nrm[0] * T[1] + (nrm[1] * T[5] + nrm[2] * T[9]);
            pt.nrm[2] = nrm[0] * T[2] + (nrm[1] * T[6] + nrm[2] * T[10]);
            pt.dist = (1.0f - 1.0f) * ray[3] + *(float*)((char*)shapeA + 0x18);
            for (j = 0; j < 4; j++)
                pt.pad[j] = 0;
            ((PointCollector*)collector)->addPoint(&pt);
        }
        ray += 8;
    }
    monMark(0x149cc34);
}
// ---- items of slice s010cea90 end

// @ 0x010c25a0
void FUN_010c25a0(void* mgr_)
{
    hkCollisionDispatcherOps* mgr = (hkCollisionDispatcherOps*)mgr_;
    mgr->registerAlternateShapeTypes();
    mgr->reg010e7ce0();
    mgr->reg010e6a70();
    mgr->setFlag(0);
    mgr->reg010e5540();
    mgr->reg010e1c70();
    mgr->reg010ceee0();
    mgr->reg010e1720();
    mgr->setFlag(1);
    mgr->setFlag(0);
    mgr->reg010e1510();
    mgr->setFlag(1);
    mgr->reg010e0500();
    mgr->reg010df500();
    mgr->setFlag(0);
    mgr->reg010df2c0();
    mgr->setFlag(1);
    mgr->reg010de080();
    mgr->reg010cef70();
    mgr->reg010dcfc0();
    mgr->reg010d9f10();
    mgr->registerAgentFuncs(1, 1);
    mgr->reg010ff6d0();
    mgr->reg010d9e50();
    mgr->reg010fdec0();
    mgr->reg010d92a0();
    mgr->reg010d8940();
    mgr->reg010d75f0();
    mgr->registerAgentFuncs(6, 4);
    mgr->registerAgentFuncs(4, 6);
    mgr->reg010d64a0();
    mgr->reg010d5320();
    mgr->reg010d41f0();
    mgr->reg010fda70();
    mgr->reg010d2730();
    mgr->reg010cff70();
    mgr->reg010cf000();
}

// @ 0x010c2890
void hkCapsuleShape::closestInfLineSegInfLineSeg(const hkVector4_s010c_2890& p0, const hkVector4_s010c_2890& d0, const hkVector4_s010c_2890& p1, const hkVector4_s010c_2890& d1, hkReal* outDistance, hkReal* outS, hkReal* outT, hkVector4_s010c_2890* outP0, hkVector4_s010c_2890* outP1)
{
	hkVector4_s010c_2890 e;
	e.m_quad[0] = p1.m_quad[0] - p0.m_quad[0];
	e.m_quad[1] = p1.m_quad[1] - p0.m_quad[1];
	e.m_quad[2] = p1.m_quad[2] - p0.m_quad[2];
	e.m_quad[3] = p1.m_quad[3] - p0.m_quad[3];

	hkReal b = d0.m_quad[2] * d1.m_quad[2] + d0.m_quad[1] * d1.m_quad[1] +
	           d0.m_quad[0] * d1.m_quad[0];
	hkReal eDotD1 = e.m_quad[0] * d1.m_quad[0] + e.m_quad[2] * d1.m_quad[2] +
	                e.m_quad[1] * d1.m_quad[1];
	hkReal c = d1.m_quad[2] * d1.m_quad[2] + (d1.m_quad[0] * d1.m_quad[0] +
	                                          d1.m_quad[1] * d1.m_quad[1]);
	hkReal a = (d0.m_quad[2] * d0.m_quad[2] + (d0.m_quad[0] * d0.m_quad[0] +
	                                           d0.m_quad[1] * d0.m_quad[1])) * c;
	hkReal denom = a - b * b;

	hkReal s;
	if (fabsf(denom) <= (fabsf(a) + b * b) * HK_EPSILON)
	{
		s = 0.0f;
	}
	else
	{
		s = ((e.m_quad[0] * d0.m_quad[0] + e.m_quad[2] * d0.m_quad[2] +
		      e.m_quad[1] * d0.m_quad[1]) * c - eDotD1 * b) / denom;
	}
	*outS = s;
	hkReal t = (b * s - eDotD1) / c;
	*outT = t;

	hkReal q0x = p0.m_quad[0] + s * d0.m_quad[0];
	hkReal q0y = p0.m_quad[1] + s * d0.m_quad[1];
	hkReal q0z = p0.m_quad[2] + s * d0.m_quad[2];
	hkReal q0w = p0.m_quad[3] + s * d0.m_quad[3];
	hkReal q1x = p1.m_quad[0] + t * d1.m_quad[0];
	hkReal q1y = p1.m_quad[1] + t * d1.m_quad[1];
	hkReal q1z = p1.m_quad[2] + t * d1.m_quad[2];
	hkReal q1w = p1.m_quad[3] + t * d1.m_quad[3];

	hkReal dx = q0x - q1x;
	hkReal dy = q0y - q1y;
	hkReal dz = q0z - q1z;

	outP0->m_quad[0] = q0x;
	outP0->m_quad[1] = q0y;
	outP0->m_quad[2] = q0z;
	outP0->m_quad[3] = q0w;
	outP1->m_quad[0] = q1x;
	outP1->m_quad[1] = q1y;
	outP1->m_quad[2] = q1z;
	outP1->m_quad[3] = q1w;
	*outDistance = dx * dx + (dy * dy + dz * dz);
}

// @ 0x010c2ad0
void hkCapsuleShape::closestPointLineSeg(const hkVector4_s010c_2890& p, const hkVector4_s010c_2890& a, const hkVector4_s010c_2890& b, hkVector4_s010c_2890& out)
{
	hkVector4_s010c_2890 d;
	d.m_quad[0] = b.m_quad[0] - a.m_quad[0];
	d.m_quad[1] = b.m_quad[1] - a.m_quad[1];
	d.m_quad[2] = b.m_quad[2] - a.m_quad[2];
	d.m_quad[3] = b.m_quad[3] - a.m_quad[3];

	hkReal magSqr = d.m_quad[2] * d.m_quad[2] + d.m_quad[1] * d.m_quad[1] +
	                d.m_quad[0] * d.m_quad[0];
	hkReal t = -(d.m_quad[1] * (a.m_quad[1] - p.m_quad[1]) +
	             d.m_quad[2] * (a.m_quad[2] - p.m_quad[2]) +
	             d.m_quad[0] * (a.m_quad[0] - p.m_quad[0]));

	// Nested tests as in the original: only a strictly smaller t lands on the
	// segment interior; an unordered compare picks the far endpoint.
	if (t <= 0.0f)
	{
		out = a;
	}
	else
	{
		if (t < magSqr)
		{
			t = t / magSqr;
			out = a;
			out.m_quad[0] = d.m_quad[0] * t + out.m_quad[0];
			out.m_quad[1] = d.m_quad[1] * t + out.m_quad[1];
			out.m_quad[2] = d.m_quad[2] * t + out.m_quad[2];
			out.m_quad[3] = d.m_quad[3] * t + out.m_quad[3];
		}
		else
		{
			out = b;
		}
	}
}

// @ 0x010c2c10
void hkCapsuleShape::getAabb(const hkTransform_s010c_2890& t, hkReal tol, hkAabb_s010c_2890& aabb) const
{
	hkReal r = m_radius + tol;

	hkReal ax = m_vertexA.m_quad[0], ay = m_vertexA.m_quad[1], az = m_vertexA.m_quad[2];
	hkReal bx = m_vertexB.m_quad[0], by = m_vertexB.m_quad[1], bz = m_vertexB.m_quad[2];

	hkReal pax = (t.m_rotation[0] * ax + (t.m_rotation[4] * ay + t.m_rotation[8] * az)) +
	             t.m_translation.m_quad[0];
	hkReal pay = (t.m_rotation[1] * ax + (t.m_rotation[5] * ay + t.m_rotation[9] * az)) +
	             t.m_translation.m_quad[1];
	hkReal paz = (t.m_rotation[2] * ax + (t.m_rotation[6] * ay + t.m_rotation[10] * az)) +
	             t.m_translation.m_quad[2];

	hkReal pbx = (t.m_rotation[0] * bx + (t.m_rotation[4] * by + t.m_rotation[8] * bz)) +
	             t.m_translation.m_quad[0];
	hkReal pby = (t.m_rotation[1] * bx + (t.m_rotation[5] * by + t.m_rotation[9] * bz)) +
	             t.m_translation.m_quad[1];
	hkReal pbz = (t.m_rotation[2] * bx + (t.m_rotation[6] * by + t.m_rotation[10] * bz)) +
	             t.m_translation.m_quad[2];

	hkReal mnx = (pax < pbx) ? pax : pbx;
	hkReal mny = (pay < pby) ? pay : pby;
	hkReal mnz = (paz < pbz) ? paz : pbz;
	hkReal mxx = (pax < pbx) ? pbx : pax;
	hkReal mxy = (pay < pby) ? pby : pay;
	hkReal mxz = (paz < pbz) ? pbz : paz;

	aabb.m_min.m_quad[0] = mnx - r;
	aabb.m_min.m_quad[1] = mny - r;
	aabb.m_min.m_quad[2] = mnz - r;
	aabb.m_min.m_quad[3] = -r;
	aabb.m_max.m_quad[0] = mxx;
	aabb.m_max.m_quad[1] = mxy;
	aabb.m_max.m_quad[2] = mxz;
	aabb.m_max.m_quad[3] = 0.0f;
	aabb.m_max.m_quad[0] = r + aabb.m_max.m_quad[0];
	aabb.m_max.m_quad[1] = r + aabb.m_max.m_quad[1];
	aabb.m_max.m_quad[2] = r + aabb.m_max.m_quad[2];
	aabb.m_max.m_quad[3] = r + aabb.m_max.m_quad[3];
}

// @ 0x010c2e30
hkBool_s010c_2890 hkCapsuleShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	hkTimerCommand(hkTtrcCapsule);

	const hkVector4_s010c_2890& A = m_vertexA;
	const hkVector4_s010c_2890& B = m_vertexB;
	const hkVector4_s010c_2890& from = input.m_from;
	const hkVector4_s010c_2890& to = input.m_to;

	{
		hkVector4_s010c_2890 pt;
		hkCapsuleShape::closestPointLineSeg(from, A, B, pt);
		const float dx = from.x - pt.x, dy = from.y - pt.y, dz = from.z - pt.z;
		const float dist = (float)sqrt((double)(dx * dx + dz * dz + dy * dy));
		if (dist < m_radius)
			goto fail;
	}

	{
		hkVector4_s010c_2890 d;
		d.x = to.x - from.x; d.y = to.y - from.y; d.z = to.z - from.z; d.w = to.w - from.w;
		hkVector4_s010c_2890 e;
		e.x = B.x - A.x; e.y = B.y - A.y; e.z = B.z - A.z; e.w = B.w - A.w;

		float distSq = 3.40282e+38f;
		float tRay, tSeg;
		hkVector4_s010c_2890 pA, pB;
		hkCapsuleShape::closestInfLineSegInfLineSeg(from, d, A, e, &distSq, &tRay, &tSeg, &pA, &pB);

		const float r2 = m_radius * m_radius;
		if (distSq > r2)
			goto fail;

		// unit axis a and its length
		float ax, ay, az, len;
		const float len2 = e.x * e.x + e.z * e.z + e.y * e.y;
		if (len2 > HK_RAY_EPS)
		{
			len = (float)sqrt((double)len2);
			const float inv = 1.0f / len;
			ax = e.x * inv; ay = e.y * inv; az = e.z * inv;
		}
		else
		{
			ax = 0.0f; ay = 0.0f; az = 0.0f;
			len = 0.0f;
		}

		// component of the ray direction perpendicular to the axis
		const float s = -(d.x * ax + d.z * az + d.y * ay);
		const float px = ax * s + d.x;
		const float py = ay * s + d.y;
		const float pz = az * s + d.z;
		const float h = (float)sqrt((double)(m_radius * m_radius - distSq));
		const float q = px * px + pz * pz + py * py;
		float invq;
		if (q == 0.0f) invq = 0.0f; else invq = 1.0f / (float)sqrt((double)q);
		volatile float f = tRay - invq * h;       // entry fraction on the cylinder

		volatile float along;
		if (!(f >= output.m_hitFraction))
		{
			const float ap = az * A.z + ay * A.y + ax * A.x;
			const float omf = 1.0f - f;
			volatile hkVector4_s010c_2890 hit;
			hit.x = omf * from.x + f * to.x;
			hit.y = f * to.y + omf * from.y;
			hit.z = f * to.z + omf * from.z;
			hit.w = f * to.w + omf * from.w;
			along = (hit.x * ax + hit.z * az + hit.y * ay) - ap;

			if (f >= 0.0f && along > 0.0f && along < len)
			{
				const float u = along / len;
				const float omu = 1.0f - u;
				volatile float spx = u * B.x + omu * A.x;
				volatile float spy = omu * A.y + u * B.y;
				volatile float spz = omu * A.z + u * B.z;
				const float spw = omu * A.w + u * B.w;
				volatile float nrmx = hit.x - spx;
				volatile float nrmy = hit.y - spy;
				volatile float nrmz = hit.z - spz;
				const float nrmw = hit.w - spw;
				const double nq = (double)nrmx * nrmx + (double)nrmz * nrmz + (double)nrmy * nrmy;
				double invn;
				if (nq == 0.0) invn = 0.0; else invn = 1.0 / sqrt(nq);
				output.m_shapeKey = 0xffffffff;
				output.m_normal[1] = (float)((double)nrmy * invn);
				output.m_normal[2] = (float)((double)nrmz * invn);
				output.m_hitFraction = f;
				output.m_normal[3] = (float)((double)nrmw * invn);
				output.m_normal[0] = (float)((double)nrmx * invn);
				hkTimerCommand(hkMonitorTimerEndTag);
				return true;
			}

			// missed the cylinder body: test the nearer end cap sphere
			const float v = ((ax * from.x + az * from.z + ay * from.y) - ap) / len;
			const float omv = 1.0f - v;
			hkVector4_s010c_2890 cp;
			cp.x = omv * A.x + v * B.x;
			cp.y = omv * A.y + v * B.y;
			cp.z = omv * A.z + v * B.z;
			const float ex = from.x - cp.x, ey = from.y - cp.y, ez = from.z - cp.z;
			const float cd = (float)sqrt((double)(ez * ez + ey * ey + ex * ex));
			if (cd > m_radius && f < 0.0f)
				goto fail;

			hkShapeRayCastInput sin;
			sin.m_filterInfo = 0;
			sin.m_rayShapeCollectionFilter = 0;
			const hkVector4_s010c_2890& c = (along <= 0.0f) ? A : B;
			sin.m_from.x = from.x - c.x; sin.m_from.y = from.y - c.y; sin.m_from.z = from.z - c.z; sin.m_from.w = from.w - c.w;
			sin.m_to.x = to.x - c.x; sin.m_to.y = to.y - c.y; sin.m_to.z = to.z - c.z; sin.m_to.w = to.w - c.w;
			hkSphereShape sphere(m_radius);
			hkTimerCommand(hkMonitorTimerEndTag);
			return sphere.castRay(sin, output);
		}
	}

fail:
	hkTimerCommand(hkMonitorTimerEndTag);
	return false;
}

// @ 0x010c3880
hkBool_s010c_3860 hkSphereShape_s010c_3860::castRay(const hkShapeRayCastInput_s010c_3860& input, hkShapeRayCastOutput_s010c_3860& output) const
{
    hkTimerCommand_s010c_3860(hkTtrcSphere);

    const hkVector4_s010c_3860& from = input.m_from;
    const hkVector4_s010c_3860& to   = input.m_to;

    const float radius2 = m_radius * m_radius;

    const float dx = to.x - from.x;
    const float dy = to.y - from.y;
    const float dz = to.z - from.z;
    const float dot = dz * from.z + (dy * from.y + dx * from.x);

    if (dot < 0.0f)
    {
        const float len2 = dx * dx + (dy * dy + dz * dz);
        float px, py, pz, vs, vo;
        if (dot * dot <= (len2 * radius2) * 100.0f)
        {
            px = from.x; py = from.y; pz = from.z;
            vs = dot;
            vo = 0.0f;
        }
        else
        {
            if (len2 < radius2)
            {
                hkTimerCommand_s010c_3860(hkMonitorTimerEndTag);
                return false;
            }
            vs = 0.0f;
            vo = -dot;
            const float t = vo / len2;
            const float s = 1.0f - t;
            px = t * to.x + s * from.x;
            py = s * from.y + t * to.y;
            pz = s * from.z + t * to.z;
        }
        const float c = (vs * vs) - ((px * px + (py * py + pz * pz)) - radius2) * len2;
        if (c < 0.0f)
        {
            hkTimerCommand_s010c_3860(hkMonitorTimerEndTag);
            return false;
        }
        float hit = (-vs - sqrtf(c)) + vo;
        if (!(len2 * output.m_hitFraction < hit) || !(hit >= 0.0f))
        {
            hkTimerCommand_s010c_3860(hkMonitorTimerEndTag);
            return false;
        }
        hit = hit / len2;
        output.m_hitFraction = hit;
        const float s = 1.0f - hit;
        output.m_normal[0] = s * from.x + hit * to.x;
        output.m_normal[1] = s * from.y + hit * to.y;
        output.m_normal[2] = s * from.z + hit * to.z;
        output.m_normal[3] = s * from.w + hit * to.w;
        const float invR = 1.0f / m_radius;
        output.m_shapeKey = 0xffffffff;
        output.m_normal[0] = invR * output.m_normal[0];
        output.m_normal[1] = invR * output.m_normal[1];
        output.m_normal[2] = invR * output.m_normal[2];
        output.m_normal[3] = invR * output.m_normal[3];
        hkTimerCommand_s010c_3860(hkMonitorTimerEndTag);
        return true;
    }

    hkTimerCommand_s010c_3860(hkMonitorTimerEndTag);
    return false;
}

// @ 0x010c3bf0
hkBool_s010c_3860 hkGroupFilter::testAgainstBody(hkBool_s010c_3860* out, hkCdBody_s010c_3860* body, void* collection, uint32_t key)
{
    typedef uint32_t (__stdcall *FilterInfoFn)(uint32_t);
    uint32_t fi = ((FilterInfoFn)(*(void***)collection)[0x2c / 4])(key);
    ((hkGroupFilterBase*)((char*)this - 0x10))->testEnabled(out, *(uint32_t*)((char*)body + 0x20), fi);
    return *out;
}

// @ 0x010c3df0
hkBool_s010c_3860 hkGroupFilter::isCollisionEnabled(const hkCollisionInput_s010c_3860& input, const hkCdBody_s010c_3860& bodyA, const hkCdBody_s010c_3860& bodyB, const hkShapeCollection& collection, uint32_t filterInfo) const
{
    typedef uint32_t (__stdcall *FilterInfoFn)(uint32_t);
    typedef int      (__stdcall *ShapeKeyFn)();
    void** cvt = *(void***)&collection;
    uint32_t fi = ((FilterInfoFn)cvt[0x2c / 4])(filterInfo);

    uint32_t a;
    const hkCdBody_s010c_3860* b = &bodyA;
    if (bodyA.m_shapeKey == -1)
    {
        const void* p = *(const void**)((const char*)b + 0xc);
        while (p)
        {
            b = (const hkCdBody_s010c_3860*)p;
            p = *(const void**)((const char*)p + 0xc);
        }
        a = *(const uint32_t*)((const char*)b + 0x1c);
    }
    else
    {
        const char* n = *(const char**)((const char*)b + 0xc);
        int key = 0;
        for (;;)
        {
            void** svt = *(void***)n;
            key = ((ShapeKeyFn)svt[8 / 4])();
            uint32_t bits = *(const uint32_t*)((const char*)*(const void**)&input + 0x10c + key * 4);
            if ((bits >> 2) & 1)
            {
                a = ((FilterInfoFn)(*(void***)n)[0x2c / 4])(*(uint32_t*)((const char*)b + 4));
                break;
            }
            if ((bits >> 3) & 1)
            {
                a = ((FilterInfoFn)(*(void***)(*(const char**)(n + 0xc)))[0x2c / 4])(*(uint32_t*)((const char*)b + 4));
                break;
            }
            if ((bits >> 0xb) & 1)
            {
                const char* p = n;
                const char* q = *(const char**)(p + 0xc);
                while (q) { p = q; q = *(const char**)(q + 0xc); }
                a = *(const uint32_t*)(p + 0x1c);
                break;
            }
            n = *(const char**)(n + 0xc);
            if (!n) { a = 0; break; }
        }
    }
    hkBool_s010c_3860 r;
    ((hkGroupFilterBase*)((char*)this - 0xc))->testEnabled(&r, a, fi);
    return r;
}

// @ 0x010c3ef0
hkGroupFilter* hkGroupFilter::destroy(char flags)
{
    *(void**)((char*)this + 0x00) = hkGroupFilter_vtbl0;
    *(void**)((char*)this + 0x08) = hkGroupFilter_vtbl1;
    *(void**)((char*)this + 0x0c) = hkGroupFilter_vtbl2;
    *(void**)((char*)this + 0x10) = hkGroupFilter_vtbl3;
    *(void**)((char*)this + 0x14) = hkGroupFilter_vtbl4;
    ((hkCollisionFilterBase*)this)->dtor();
    if (flags & 1)
    {
        void** mem = *(void***)hkMemory_s_instance;
        typedef void (__stdcall *FreeFn)(void*, unsigned, int);
        ((FreeFn)mem[0x14 / 4])(this, (unsigned)*(unsigned short*)((char*)this + 4), 0x24);
    }
    return this;
}

// @ 0x010c4000
void hkShape__expandIndices(const uint16_t* idx, char* verticesBase, unsigned count, void* outp)
{
    float* out = (float*)outp;
    int remaining = (int)count - 1;
    if ((int)count > 3)
    {
        unsigned n = count >> 2;
        remaining = remaining - (int)n * 4;
        do
        {
            unsigned e0 = idx[0];
            const float* v0 = (const float*)(verticesBase + e0 + 0x10);
            out[0] = v0[0]; out[1] = v0[1]; out[2] = v0[2]; out[3] = v0[3];
            *(unsigned*)(out + 3) = e0 | 0x3f000000u;

            unsigned e1 = idx[1];
            const float* v1 = (const float*)(verticesBase + e1 + 0x10);
            out[4] = v1[0]; out[5] = v1[1]; out[6] = v1[2]; out[7] = v1[3];
            *(unsigned*)(out + 7) = e1 | 0x3f000000u;

            unsigned e2 = idx[2];
            const float* v2 = (const float*)(verticesBase + e2 + 0x10);
            out[8] = v2[0]; out[9] = v2[1]; out[10] = v2[2]; out[11] = v2[3];
            *(unsigned*)(out + 11) = e2 | 0x3f000000u;

            unsigned e3 = idx[3];
            const float* v3 = (const float*)(verticesBase + e3 + 0x10);
            out[12] = v3[0]; out[13] = v3[1]; out[14] = v3[2]; out[15] = v3[3];
            *(unsigned*)(out + 15) = e3 | 0x3f000000u;

            idx += 4;
            out += 0x10;
        } while (--n);
    }
    if (remaining >= 0)
    {
        int k = 0;
        do
        {
            unsigned e = idx[k];
            const float* v = (const float*)(verticesBase + e + 0x10);
            out[k * 4 + 0] = v[0];
            out[k * 4 + 1] = v[1];
            out[k * 4 + 2] = v[2];
            out[k * 4 + 3] = v[3];
            *(unsigned*)(out + k * 4 + 3) = e | 0x3f000000u;
            k++;
        } while (k <= remaining);
    }
}

// @ 0x010c4140
void hkTriangleShape::getAabb(const hkTransform_s010c_3860& t, float tolerance, hkAabb_s010c_3860& aabb) const
{
    const float tol = tolerance + m_radius;

    hkVector4_s010c_3860 a, b, c;
    hkVector4__setTransformedPos(&a, &t, &m_vertexA);
    hkVector4__setTransformedPos(&b, &t, &m_vertexB);
    hkVector4__setTransformedPos(&c, &t, &m_vertexC);

    aabb.m_min.x = (c.x <= b.x) ? c.x : b.x;    // fold A/B later
    aabb.m_min.y = (c.y <= b.y) ? c.y : b.y;
    aabb.m_min.z = (c.z <= b.z) ? c.z : b.z;
    aabb.m_min.w = (c.w <= b.w) ? c.w : b.w;
    aabb.m_max.x = (c.x > b.x) ? c.x : b.x;
    aabb.m_max.y = (c.y > b.y) ? c.y : b.y;
    aabb.m_max.z = (c.z > b.z) ? c.z : b.z;
    aabb.m_max.w = (c.w > b.w) ? c.w : b.w;

    // fold in A
    if (a.x <= aabb.m_min.x) aabb.m_min.x = a.x;
    if (a.y <= aabb.m_min.y) aabb.m_min.y = a.y;
    if (a.z <= aabb.m_min.z) aabb.m_min.z = a.z;
    if (a.w <= aabb.m_min.w) aabb.m_min.w = a.w;
    if (a.x > aabb.m_max.x) aabb.m_max.x = a.x;
    if (a.y > aabb.m_max.y) aabb.m_max.y = a.y;
    if (a.z > aabb.m_max.z) aabb.m_max.z = a.z;
    if (a.w > aabb.m_max.w) aabb.m_max.w = a.w;

    aabb.m_min.x -= tol; aabb.m_min.y -= tol; aabb.m_min.z -= tol; aabb.m_min.w -= tol;
    aabb.m_max.x += tol; aabb.m_max.y += tol; aabb.m_max.z += tol; aabb.m_max.w += tol;
}

// @ 0x010c4400
void hkTriangleShape::getSupportingVertex(const hkVector4_s010c_3860& dir, void* v) const
{
    const float dx = dir.x, dy = dir.y, dz = dir.z;
    float dA = dx * m_vertexA.x + (dy * m_vertexA.y + dz * m_vertexA.z);
    float dB = dx * m_vertexB.x + (dy * m_vertexB.y + dz * m_vertexB.z);
    float dC = dx * m_vertexC.x + (dy * m_vertexC.y + dz * m_vertexC.z);

    unsigned int sel;
    float best;
    if (dC <= dB) { sel = 0x10; best = dB; }
    else          { sel = 0x20; best = dC; }
    if (best < dA) sel = 0;

    const hkVector4_s010c_3860* src = (const hkVector4_s010c_3860*)((const char*)this + sel + 0x10);
    float* out = (float*)v;
    out[0] = src->x;
    out[1] = src->y;
    out[2] = src->z;
    out[3] = src->w;
    *(unsigned int*)(out + 3) = sel | 0x3f000000;
}

// @ 0x010c44d0
hkBool_s010c_44d0 hkTriangleShape_s010c_44d0::castRay(const hkShapeRayCastInput_s010c_44d0& in, hkShapeRayCastOutput_s010c_44d0& out) const
{
    hkTimerBegin(hkTtrcTriangle);

    const float Ax = m_vertexA.x, Ay = m_vertexA.y, Az = m_vertexA.z;

    // edge vectors
    float e0x = m_vertexB.x - Ax;
    float e0y = m_vertexB.y - Ay;
    float e0z = m_vertexB.z - Az;
    float e1x = m_vertexC.x - Ax;
    float e1y = m_vertexC.y - Ay;
    float e1z = m_vertexC.z - Az;

    // normal = -(e0 x e1)
    float nx = e1z * e0y - e1y * e0z;
    float ny = e0z * e1x - e1z * e0x;
    float nz = e1y * e0x - e0y * e1x;

    float d  = nx * Ax + (ny * Ay + nz * Az);

    float fFrom = (ny * in.m_from.y + (nz * in.m_from.z + nx * in.m_from.x)) - d;
    float fTo   = (nx * in.m_to.x   + (ny * in.m_to.y   + nz * in.m_to.z))   - d;

    if ((fTo * fFrom < 0.0f) || (fFrom == 0.0f && fTo != 0.0f)) {
        float t = fFrom / (fFrom - fTo);
        if (t < out.m_hitFraction) {
            float eps = (ny * ny + (nz * nz + nx * nx)) * -0.0001f;
            float om  = 1.0f - t;
            float px  = t * in.m_to.x + om * in.m_from.x;
            float py  = om * in.m_from.y + t * in.m_to.y;
            float pz  = om * in.m_from.z + t * in.m_to.z;

            float ax = Ax - px, ay = Ay - py, az = Az - pz;
            float bx = m_vertexB.x - px, by = m_vertexB.y - py, bz = m_vertexB.z - pz;

            if (eps <= (az * bx - bz * ax) * ny +
                       ((by * ax - ay * bx) * nz +
                        (bz * ay - by * az) * nx)) {
                float cx = m_vertexC.x - px, cy = m_vertexC.y - py, cz = m_vertexC.z - pz;
                if ((eps <= (bz * cx - cz * bx) * ny +
                            ((cy * bx - by * cx) * nz +
                             (cz * by - cy * bz) * nx)) &&
                    (eps <= (cz * ax - az * cx) * ny +
                            ((ay * cx - cy * ax) * nz +
                             (cy * az - cz * ay) * nx))) {
                    out.m_hitFraction = t;
                    out.m_normal[3]   = 0.0f;
                    if (fFrom <= 0.0f) {
                        out.m_normal[0] = -nx; out.m_normal[1] = -ny; out.m_normal[2] = -nz;
                    } else {
                        out.m_normal[0] =  nx; out.m_normal[1] =  ny; out.m_normal[2] =  nz;
                    }
                    float len2 = out.m_normal[2] * out.m_normal[2] +
                                 (out.m_normal[1] * out.m_normal[1] +
                                  out.m_normal[0] * out.m_normal[0]);
                    float inv = (len2 == 0.0f) ? 0.0f : 1.0f / (float)sqrt(len2);
                    out.m_shapeKey   = 0xffc00000u;     // original stores -NAN here
                    out.m_normal[0]  = inv * out.m_normal[0];
                    out.m_normal[1]  = inv * out.m_normal[1];
                    out.m_normal[2]  = inv * out.m_normal[2];
                    out.m_normal[3]  = inv * 0.0f;
                    hkTimerEndStamp();
                    return hkBool_s010c_44d0(true);
                }
            }
        }
    }
    hkTimerEndStamp();
    return hkBool_s010c_44d0(false);
}

// @ 0x010c4a20
void hkTriangleShapeCtor(hkTriangleShape_s010c_44d0* self)
{
    // 0x010e7fd0 (hkShapeCollection/hkShape ctor) sets the base vptr; the retail
    // sequence is: if (this) { baseCtor(this); this->vtbl = &hkTriangleShape::vtbl; }
    if (self != 0)
        *(void**)self = (void*)0x014a3c54;   // hkTriangleShape vtable
}

// @ 0x010c4a40
const hkShape_s010c_44d0* hkTriSampledHeightFieldCollection::getChildShape(uint32_t key, char (&buf)[512]) const
{
    uint32_t xIdx = (key >> 1) & 0x7fff;
    uint32_t zIdx = key >> 16;

    hkTriangleShape_s010c_44d0* tri = 0;
    if (&buf[0] != 0) {
        hkTriangleShape_s010c_44d0* t = (hkTriangleShape_s010c_44d0*)&buf[0];
        t->m_memSizeAndFlags = 1;                              // word at +6
        t->m_radius          = m_radius;                       // dword at +0x0c
        t->m_userData        = 0;                              // dword at +0x08
        *(void**)t           = (void*)0x014a3bfc;              // hkTriangleShape vtable
        tri = t;
    }

    const hkSampledHeightFieldShape* hf = m_heightfield;

    float h00 = hf->getHeight((int)xIdx,     (int)zIdx);
    float h10 = hf->getHeight((int)xIdx + 1, (int)zIdx);
    float h01 = hf->getHeight((int)xIdx,     (int)zIdx + 1);
    float h11 = hf->getHeight((int)xIdx + 1, (int)zIdx + 1);

    float sx = hf->m_intToFloatScale.x, sy = hf->m_intToFloatScale.y,
          sz = hf->m_intToFloatScale.z;

    float x0 = (float)(int)xIdx       * sx;
    float x1 = (float)((int)xIdx + 1) * sx;
    float z0 = (float)(int)zIdx       * sz;
    float z1 = (float)((int)zIdx + 1) * sz;
    float y00 = h00 * sy, y10 = h10 * sy, y01 = h01 * sy, y11 = h11 * sy;

    if ((key & 1) == 0) {
        tri->m_vertexA.x = x1; tri->m_vertexA.y = y10; tri->m_vertexA.z = z0;
        tri->m_vertexA.w = 0.0f;
        tri->m_vertexB.x = x0; tri->m_vertexB.y = y01; tri->m_vertexB.z = z1;
        tri->m_vertexB.w = 0.0f;
        tri->m_vertexC.x = x1; tri->m_vertexC.y = y11; tri->m_vertexC.z = z1;
        tri->m_vertexC.w = 0.0f;
    } else {
        tri->m_vertexA.x = x0; tri->m_vertexA.y = y00; tri->m_vertexA.z = z0;
        tri->m_vertexA.w = 0.0f;
        tri->m_vertexB.x = x0; tri->m_vertexB.y = y01; tri->m_vertexB.z = z1;
        tri->m_vertexB.w = 0.0f;
        tri->m_vertexC.x = x1; tri->m_vertexC.y = y10; tri->m_vertexC.z = z0;
        tri->m_vertexC.w = 0.0f;
    }
    return tri;
}

// @ 0x010c4d40
hkTriSampledHeightFieldCollection::~hkTriSampledHeightFieldCollection()
{
    m_heightfield->removeReference();
}

// @ 0x010c4d90
hkBool_s010c_44d0 hkTriSampledHeightFieldBvTreeShape::castRay(const hkShapeRayCastInput_s010c_44d0& in, hkShapeRayCastOutput_s010c_44d0& out) const
{
    hkTriSampledHeightFieldCollection* coll =
        (hkTriSampledHeightFieldCollection*)m_shapeCollection;
    return coll->m_heightfield->castRay(in, out);
}

// @ 0x010c4dc0
void hkTriSampledHeightFieldBvTreeShape::castRayWithCollector(const hkShapeRayCastInput_s010c_44d0& in, const void* body, void* collector) const
{
    hkTriSampledHeightFieldCollection* coll =
        (hkTriSampledHeightFieldCollection*)m_shapeCollection;
    void** vtbl = *(void***)coll->m_heightfield;
    ((void(*)(const hkShapeRayCastInput_s010c_44d0&, const void*, void*))vtbl[6])(in, body, collector);
}

// @ 0x010c4dd0
hkTriSampledHeightFieldBvTreeShape::~hkTriSampledHeightFieldBvTreeShape()
{
    m_shapeCollection->removeReference();
}

// @ 0x010c4e20
void hkTriSampledHeightFieldBvTreeShape::querySphere(const hkSphere_s010c_44d0& s, hkArrayU32& hits) const
{
    float r  = s.m_radius;
    float nr = -r;
    hkAabb_s010c_44d0 box;
    box.m_min.x = nr + s.m_center.x;
    box.m_min.y = nr + s.m_center.y;
    box.m_min.z = nr + s.m_center.z;
    box.m_min.w = nr + s.m_center.w;
    box.m_max.x = r + s.m_center.x;
    box.m_max.y = r + s.m_center.y;
    box.m_max.z = r + s.m_center.z;
    box.m_max.w = r + s.m_center.w;
    queryAabb(box, hits);
}

// @ 0x010c4f50
void hkTriSampledHeightFieldBvTreeShape::queryAabb(const hkAabb_s010c_44d0& aabb, hkArrayU32& hits) const
{
    const hkTriSampledHeightFieldCollection* coll =
        (const hkTriSampledHeightFieldCollection*)m_shapeCollection;
    const hkSampledHeightFieldShape* hf = coll->m_heightfield;
    float r  = coll->m_radius;
    float nr = -r;

    uint32_t zMin = (uint32_t)(((nr + aabb.m_min.z) + hf->m_floatToIntOffsetFloorCorrected.z) *
                           hf->m_floatToIntScale.z + 196608.0f) >> 6 & 0xffff;
    uint32_t xMin = (uint32_t)(((nr + aabb.m_min.x) + hf->m_floatToIntOffsetFloorCorrected.x) *
                           hf->m_floatToIntScale.x + 196608.0f) >> 6 & 0xffff;
    uint32_t xMax = (uint32_t)((( r + aabb.m_max.x) + hf->m_floatToIntOffsetFloorCorrected.x) *
                           hf->m_floatToIntScale.x + 196608.0f) >> 6 & 0xffff;
    uint32_t zMax = (uint32_t)((( r + aabb.m_max.z) + hf->m_floatToIntOffsetFloorCorrected.z) *
                           hf->m_floatToIntScale.z + 196608.0f) >> 6 & 0xffff;

    uint32_t xLim = (uint32_t)(hf->m_xRes - 1);
    uint32_t zLim = (uint32_t)(hf->m_zRes - 1);
    if ((xMin < xLim || xMax < xLim) && (zMin < zLim || zMax < zLim)) {
        if (xLim <= xMin) xMin = 0;
        if (zLim <= zMin) zMin = 0;
        if (xLim <= xMax) xMax = (uint32_t)(hf->m_xRes - 2);
        if (zLim <= zMax) zMax = (uint32_t)(hf->m_zRes - 2);

        int size = hits.m_size;
        float y0 = nr + aabb.m_min.y;
        float y1 =  r + aabb.m_max.y;

        if (!m_wantAabbRejectionTest.m_bool) {
            for (uint32_t x = xMin; x <= xMax; ++x) {
                if (zMin <= zMax) {
                    uint32_t base  = (zMin * 0x8000 + x) * 2;
                    int    count = (int)(zMax - zMin) + 1;
                    do {
                        if (hits.m_size == (hits.m_capacityAndFlags & 0x3fffffff))
                            hkArrayUtil_grow(&hits, 4);
                        hits.m_data[hits.m_size] = base;
                        size = hits.m_size;
                        hits.m_size = size + 1;
                        if ((uint32_t)(size + 1) == (uint32_t)(hits.m_capacityAndFlags & 0x3fffffff))
                            hkArrayUtil_grow(&hits, 4);
                        hits.m_data[hits.m_size] = base | 1;
                        base += 0x10000;
                        count = count - 1;
                        hits.m_size = hits.m_size + 1;
                    } while (count != 0);
                }
            }
            return;
        }

        bool testLow = true, testHigh = true;
        for (uint32_t x = xMin; x <= xMax; ++x) {
            if (zMin <= zMax) {
                uint32_t e = (zMin * 0x8000 + x) * 2;
                for (uint32_t z = zMin; z <= zMax; ++z) {
                    if (hits.m_size == (hits.m_capacityAndFlags & 0x3fffffff))
                        hkArrayUtil_grow(&hits, 4);
                    hits.m_data[hits.m_size] = e;
                    int i = hits.m_size;
                    hits.m_size = i + 1;
                    if ((uint32_t)(i + 1) == (uint32_t)(hits.m_capacityAndFlags & 0x3fffffff))
                        hkArrayUtil_grow(&hits, 4);
                    hits.m_data[hits.m_size] = e | 1;
                    hits.m_size = hits.m_size + 1;
                    if (testLow || testHigh) {
                        float h  = hf->getHeight((int)x, (int)z);
                        float hs = h * hf->m_floatToIntScale.w;
                        if (y0 < hs) testLow = false;
                        if (hs < y1) testHigh = false;
                    }
                    e += 0x10000;
                }
            }
        }
        if (!testLow && !testHigh)
            return;

        for (uint32_t x = xMin; x <= xMax + 1; ++x) {
            float h  = hf->getHeight((int)x, (int)(zMax + 1));
            float hs = h * hf->m_floatToIntScale.w;
            if (y0 < hs) testLow = false;
            if (hs < y1) testHigh = false;
        }
        for (uint32_t z = zMin; z <= zMax + 1; ++z) {
            float h  = hf->getHeight((int)(xMax + 1), (int)z);
            float hs = h * hf->m_floatToIntScale.w;
            if (y0 < hs) testLow = false;
            if (hs < y1) testHigh = false;
        }
        if (testLow || testHigh) {
            if ((int)(hits.m_capacityAndFlags & 0x3fffffff) < size) {
                int want = (hits.m_capacityAndFlags & 0x3fffffff) * 2;
                if (want <= size) want = size;
                hkArrayUtil_reserveExactly(&hits, want, 4);
            }
            hits.m_size = size;
        }
    }
}

// @ 0x010c5470
void hkTriSampledHeightFieldBvTreeShape_calcStatistics(const void* self, void* collector)
{
    uint8_t* p  = (uint8_t*)self;
    void** vt = *(void***)collector;
    ((void(*)(void*, const char*, int, const void*))vt[1])(collector, "TransformShp", 1, self);
    ((void(*)(void*, const char*, int, const void*))vt[3])(collector, "ChildShape", 1,
                                                          *(void**)(p + 0x0c));
    ((void(*)(void*))vt[6])(collector);
}
#pragma pack(pop)

// @ 0x010c90a0
void hkCylinderShape::getSupportingVertex(const hkVector4_s010c_90a0& direction, hkCdVertex& vertex) const
{
    float d1 = m_perpendicular1.x * direction.x
             + (m_perpendicular1.y * direction.y + m_perpendicular1.z * direction.z);
    float d2 = m_perpendicular2.x * direction.x
             + (m_perpendicular2.y * direction.y + m_perpendicular2.z * direction.z);
    float len2 = d1 * d1 + d2 * d2;

    int   d2Sign;
    float n1, n2;                       // normalised projections onto m_perpendicular1 / 2
    if (len2 < 1.4210855e-14f)
    {
        d2Sign = 1;
        n2 = 0.0f;
        n1 = 1.0f;
    }
    else
    {
        float inv = 1.0f / sqrtf(len2);
        n2 = inv * d2;
        n1 = inv * d1;
        d2Sign = (n2 < 0.0f) ? 0 : 1;
    }

    float a1 = fabsf(n1);
    float a2 = fabsf(n2);
    int   n2Smaller = (a2 < a1);
    float minAbs = n2Smaller ? a2 : a1;

    float height = (m_vertexB.x - m_vertexA.x) * direction.x
                 + ((m_vertexB.y - m_vertexA.y) * direction.y
                  + (m_vertexB.z - m_vertexA.z) * direction.z);

    int n1Sign = (n1 >= 0.0f) ? 1 : 0;
    int heightNeg = (height < 0.0f) ? 1 : 0;
    unsigned int id = (unsigned int)(n2Smaller
                      + (n1Sign + (d2Sign + heightNeg * 2) * 2) * 2) * 0x10
                      + (int)(g_hkSupportScale * minAbs - g_hkFpuRoundingValue + 0.05f);

    // Decode the id into the base vertex plus a scaled perpendicular offset.
    unsigned char b = (unsigned char)id;
    float angle = ((float)(id & 0xf) + 0.5f) * g_hkAngleStep;
    float c, s;
    if ((b >> 4 & 1) == 0)
    {
        c = sqrtf(1.0f - angle * angle);
        s = angle;
    }
    else
    {
        c = angle;
        s = sqrtf(1.0f - angle * angle);
    }
    if ((b >> 6 & 1) == 0) c = -c;
    if ((b >> 5 & 1) == 0) s = -s;

    const hkVector4_s010c_90a0& base = (b & 0x80) ? m_vertexA : m_vertexB;
    float r = m_cylRadius;
    vertex.x = (c * m_perpendicular2.x + s * m_perpendicular1.x) * r + base.x;
    vertex.y = (c * m_perpendicular2.y + s * m_perpendicular1.y) * r + base.y;
    vertex.z = (c * m_perpendicular2.z + s * m_perpendicular1.z) * r + base.z;
    vertex.w = (c * m_perpendicular2.w + s * m_perpendicular1.w) * r + base.w;
    *(uint32_t*)&vertex.w = id | 0x3f000000u;
}

// @ 0x010c9360
void hkCylinderShape::convertVertexIdsToVertices(const unsigned short* ids, int numIds, hkCdVertex* vertices) const
{
    for (int i = numIds - 1; i >= 0; --i)
    {
        unsigned int id = (unsigned int)*ids;
        unsigned char b = (unsigned char)id;
        float angle = ((float)(id & 0xf) + 0.5f) * g_hkAngleStep;
        float c, s;
        if ((b >> 4 & 1) == 0)
        {
            c = sqrtf(1.0f - angle * angle);
            s = angle;
        }
        else
        {
            c = angle;
            s = sqrtf(1.0f - angle * angle);
        }
        if ((b >> 6 & 1) == 0) c = -c;
        if ((b >> 5 & 1) == 0) s = -s;

        const hkVector4_s010c_90a0& base = (b & 0x80) ? m_vertexA : m_vertexB;
        float r = m_cylRadius;
        vertices->x = (c * m_perpendicular2.x + s * m_perpendicular1.x) * r + base.x;
        vertices->y = (c * m_perpendicular2.y + s * m_perpendicular1.y) * r + base.y;
        vertices->z = (c * m_perpendicular2.z + s * m_perpendicular1.z) * r + base.z;
        vertices->w = (c * m_perpendicular2.w + s * m_perpendicular1.w) * r + base.w;
        *(uint32_t*)&vertices->w = id | 0x3f000000u;

        ++ids;
        ++vertices;
    }
}

// @ 0x010c9920
void hkCylinderShape::getAabb(const hkTransform_s010c_90a0& transform, float tolerance, hkAabb_s010c_90a0& aabb) const
{
    const float* t = transform.m;

    float ax = m_vertexA.x, ay = m_vertexA.y, az = m_vertexA.z;
    float bx = m_vertexB.x, by = m_vertexB.y, bz = m_vertexB.z;

    float awx = t[0] * ax + (t[4] * ay + t[8] * az) + t[0xc];
    float awy = t[1] * ax + (t[5] * ay + t[9] * az) + t[0xd];
    float awz = t[2] * ax + (t[10] * az + t[6] * ay) + t[0xe];
    float bwx = t[0] * bx + (t[4] * by + t[8] * bz) + t[0xc];
    float bwy = t[1] * bx + (t[5] * by + t[9] * bz) + t[0xd];
    float bwz = t[2] * bx + (t[10] * bz + t[6] * by) + t[0xe];

    float dx = bwx - awx;
    float dy = bwy - awy;
    float dz = bwz - awz;
    float len2 = dx * dx + (dy * dy + dz * dz);

    float inv;
    if (len2 == 0.0f)
        inv = 0.0f;
    else
        inv = 1.0f / sqrtf(len2);

    float r = m_cylRadius;
    float tol = tolerance + m_radius;

    // Per-axis extension of the capsule: the disc radius plus the 1.01-fattened slant term.
    float ex = tol + r * sqrtf(1.01f - (dx * inv) * (dx * inv));
    float ey = sqrtf(1.01f - (dy * inv) * (dy * inv)) * r + tol;
    float ez = sqrtf(1.01f - (dz * inv) * (dz * inv)) * r + tol;

    float minx = (awx < bwx) ? awx : bwx;
    float miny = (awy < bwy) ? awy : bwy;
    float minz = (awz < bwz) ? awz : bwz;
    aabb.m_min.x = minx - ex;
    aabb.m_min.y = miny - ey;
    aabb.m_min.z = minz - ez;
    aabb.m_min.w = -tol;

    float maxx = (bwx < awx) ? awx : bwx;
    float maxy = (bwy < awy) ? awy : bwy;
    float maxz = (bwz < awz) ? awz : bwz;
    aabb.m_max.x = maxx + ex;
    aabb.m_max.y = maxy + ey;
    aabb.m_max.z = maxz + ez;
    aabb.m_max.w = tol;
}

// @ 0x010caa30
void hkConvexTransformShape::convertVertexIdsToVertices(const void* p1, int numIds, hkVector4_s010c_aa30* out)
{
    ((hkConvexShapeVtbl*)(*(void**)m_childShape))
        ->convertVertexIdsToVertices(p1, numIds, out);

    const float* m = m_transform.m_col;
    float m00 = m[0], m01 = m[1], m02 = m[2];
    float m10 = m[4], m11 = m[5], m12 = m[6];
    float m20 = m[8], m21 = m[9], m22 = m[10];
    float tx  = m[12], ty = m[13], tz = m[14];

    hkVector4_s010c_aa30* v = out;
    for (int i = 0; i < numIds; ++i) {
        float x = v[i].x, y = v[i].y, z = v[i].z;
        v[i].x = m00 * x + m10 * y + m20 * z + tx;
        v[i].y = m01 * x + m11 * y + m21 * z + ty;
        v[i].z = m02 * x + m12 * y + m22 * z + tz;
    }
}

// @ 0x010cadb0
void hkConvexTransformShape::getFirstVertex(hkVector4_s010c_aa30& out)
{
    hkVector4_s010c_aa30 v;
    ((hkConvexShapeVtbl*)(*(void**)m_childShape))->getFirstVertex(v);

    const float* m = m_transform.m_col;
    out.x = m[0] * v.x + m[4] * v.y + m[8]  * v.z + m[12];
    out.y = m[1] * v.x + m[5] * v.y + m[9]  * v.z + m[13];
    out.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
    out.w = 0.0f;
}

// @ 0x010cae40
int hkConvexTransformShape::getCollisionSpheres(void* p1)
{
    hkConvexShape* child = m_childShape;
    hkConvexShapeVtbl* cv = (hkConvexShapeVtbl*)(*(void**)child);
    int num = cv->getCollisionSpheres(p1);
    (void)num;
    return (int)p1;
}

// @ 0x010cb250
void* hkConvexPieceMeshShape::getChildShape(hkUint32 key, char (&storage)[0xc0])
{
    hkConvexShape* child = (hkConvexShape*)storage;
    void* shape = (child == 0) ? 0 : hkConvexPieceShape_ctor(child, m_radius);
    *(float*)((char*)shape + 0x18) = m_radius;

    hkConvexPieceStreamData* s = m_convexPieceStream;
    hkVector4_s010c_aa30* verts = (hkVector4_s010c_aa30*)(((uintptr_t)storage + 0x33) & ~(uintptr_t)0xf);

    if (key < (hkUint32)s->m_convexPieceOffsets.m_size) {
        void* iVar3 = ((void**)s->m_convexPieceStream.m_data)[key];
        int   iVar4 = ((int*)s->m_convexPieceOffsets.m_data)[(int)iVar3];
        int*  piVar1 = &((int*)s->m_convexPieceOffsets.m_data)[(int)iVar3];
        *(void**)((char*)shape + 0x1c) = piVar1 + 1;
        *(int*)((char*)shape + 0x20) = iVar4;
        *(void**)((char*)shape + 0x10) = verts;
        *(int*)((char*)shape + 0x14) = 0;
        if (0 < iVar4) {
            hkUint32 local_224 = 2;
            int local_21c = 0;
            do {
                int idx = ((int*)(*(void**)((char*)shape + 0x1c)))[local_21c];
                hkShape_s010c_aa30* childShape = m_displayMesh;
                hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)childShape);
                void* info = v->getChildShape((hkUint32)idx);
                if ((piVar1[piVar1[0] + (local_224 - 2) / 0x1f + 1] &
                     (1u << ((local_224 - 2) % 0x1f))) != 0) {
                    verts[0] = *(hkVector4_s010c_aa30*)((char*)info + 0x10);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                if ((piVar1[piVar1[0] + (local_224 - 1) / 0x1f + 1] &
                     (1u << ((local_224 - 1) % 0x1f))) != 0) {
                    verts[0] = *(hkVector4_s010c_aa30*)((char*)info + 0x20);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                if ((piVar1[piVar1[0] + local_224 / 0x1f + 1] &
                     (1u << (local_224 % 0x1f))) != 0) {
                    verts[0] = *(hkVector4_s010c_aa30*)((char*)info + 0x30);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                ++local_21c;
                local_224 += 3;
            } while (local_21c < *(int*)((char*)shape + 0x20));
            return shape;
        }
    } else {
        *(int*)((char*)shape + 0x20) = 1;
        void* puVar2 = (void*)((char*)s->m_convexPieceSingleTriangles.m_data +
                               (key - (hkUint32)s->m_convexPieceOffsets.m_size) * 4);
        *(void**)((char*)shape + 0x1c) = puVar2;
        *(void**)((char*)shape + 0x10) = verts;
        *(int*)((char*)shape + 0x14) = 3;
        hkShape_s010c_aa30* childShape = m_displayMesh;
        hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)childShape);
        void* info = v->getChildShape(*(hkUint32*)puVar2);
        verts[0] = *(hkVector4_s010c_aa30*)((char*)info + 0x10);
        verts[1] = *(hkVector4_s010c_aa30*)((char*)info + 0x20);
        verts[2] = *(hkVector4_s010c_aa30*)((char*)info + 0x30);
    }
    return shape;
}

// @ 0x010cb490
hkUint32 hkConvexPieceMeshShape::getCollisionFilterInfo(hkUint32 key)
{
    hkConvexPieceStreamData* s = m_convexPieceStream;
    hkUint32 info;
    if (key < (hkUint32)s->m_convexPieceOffsets.m_size) {
        int i = ((int*)s->m_convexPieceOffsets.m_data)[key];
        info = ((hkUint32*)s->m_convexPieceStream.m_data)[i + 1];
    } else {
        int i = (int)key - s->m_convexPieceOffsets.m_size;
        info = ((hkUint32*)s->m_convexPieceSingleTriangles.m_data)[i];
    }
    hkShapeCollection_s010c_aa30_s010c_aa30* display = m_displayMesh;
    hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)display);
    return v->getCollisionFilterInfo(info);
}

// @ 0x010cb4d0
void hkConvexPieceMeshShape::getAabb(const hkTransform_s010c_aa30& t, float radius, hkAabb_s010c_aa30& aabb)
{
    aabb.m_min.x = 3.402823466e+38f;
    aabb.m_min.y = 3.402823466e+38f;
    aabb.m_min.z = 3.402823466e+38f;
    aabb.m_min.w = 0.0f;
    aabb.m_max.w = 0.0f;
    aabb.m_max.x = -3.402823466e+38f;
    aabb.m_max.y = -3.402823466e+38f;
    aabb.m_max.z = -3.402823466e+38f;

    hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)this);
    hkUint32 k = v->getFirstKey();
    if (k == 0xffffffffu) return;
    do {
        hkShapeVtbl* v2 = (hkShapeVtbl*)(*(void**)this);
        void* child = v2->getChildShape(k);
        hkAabb_s010c_aa30 childAabb;
        ((hkShapeIface*)(*(void**)child))->getAabb(t, radius, childAabb);

        aabb.m_min.x = (aabb.m_min.x < childAabb.m_min.x) ? aabb.m_min.x : childAabb.m_min.x;
        aabb.m_min.y = (aabb.m_min.y < childAabb.m_min.y) ? aabb.m_min.y : childAabb.m_min.y;
        aabb.m_min.z = (aabb.m_min.z < childAabb.m_min.z) ? aabb.m_min.z : childAabb.m_min.z;
        aabb.m_min.w = (aabb.m_min.w < childAabb.m_min.w) ? aabb.m_min.w : childAabb.m_min.w;
        aabb.m_max.x = (aabb.m_max.x < childAabb.m_max.x) ? childAabb.m_max.x : aabb.m_max.x;
        aabb.m_max.y = (aabb.m_max.y < childAabb.m_max.y) ? childAabb.m_max.y : aabb.m_max.y;
        aabb.m_max.z = (aabb.m_max.z < childAabb.m_max.z) ? childAabb.m_max.z : aabb.m_max.z;
        aabb.m_max.w = (aabb.m_max.w < childAabb.m_max.w) ? childAabb.m_max.w : aabb.m_max.w;

        hkShapeVtbl* v3 = (hkShapeVtbl*)(*(void**)this);
        k = v3->getNextKey(k);
    } while (k != 0xffffffffu);
}

// @ 0x010cb9a0
void hkCollisionFilterList::dtor()
{
    hkCollisionFilterList* self = this;
    *(void**)self = (void*)0x014a4210;
    *(void**)((char*)self + 8)  = (void*)0x014a4208;
    *(void**)((char*)self + 0xc) = (void*)0x014a4200;
    *(void**)((char*)self + 0x10) = (void*)0x014a41f8;
    *(void**)((char*)self + 0x14) = (void*)0x014a41f0;

    int n = *(int*)((char*)self + 0x1c);
    for (int i = 0; i < n; ++i) {
        RefObj* f = ((RefObj**)(*(void**)((char*)self + 0x18)))[i];
        if (f->m_memSizeAndFlags != 0) {
            if (--f->m_referenceCount == 0)
                f->dtor(1);
        }
    }
    if (*(int*)((char*)self + 0x20) >= 0) {
        void* mem = TlsGetValue(g_hkThreadMemoryTls);
        hkThreadMemory_deallocateChunk(mem, *(void**)((char*)self + 0x18),
                                       (*(int*)((char*)self + 0x20) & 0x3fffffff) << 2, 0x14);
    }
    *(void**)((char*)self + 0x14) = (void*)0x013ef82c;
    *(void**)((char*)self + 0x10) = (void*)0x013ef824;
    *(void**)((char*)self + 0xc)  = (void*)0x013ef824;
    *(void**)((char*)self + 8)   = (void*)0x013ef82c;
    *(void**)self = (void*)0x013ef094;
}

// @ 0x010ccd60
void hkCollisionDispatcher_s010c_ca60::internalRegisterCollisionAgent( unsigned char (*agentTypes)[32], int agentType, hkShapeType typeA, hkShapeType typeB, hkShapeType typeAReg, hkShapeType typeBReg, DebugEntry (*debugTable)[32][32], int level)
{
	m_collisionAgentRegistered = 1;

	for (int i = 0; i < m_shapeInheritance.m_size; i++)
	{
		if (m_shapeInheritance.m_data[i].m_alternateType == typeA)
		{
			internalRegisterCollisionAgent(agentTypes, agentType,
				m_shapeInheritance.m_data[i].m_primaryType, typeB,
				typeAReg, typeBReg, debugTable, level + 1);
		}
		else if (m_shapeInheritance.m_data[i].m_alternateType == typeB)
		{
			if (m_shapeInheritance.m_data[i].m_alternateType == typeA)
			{
				internalRegisterCollisionAgent(agentTypes, agentType,
					m_shapeInheritance.m_data[i].m_primaryType, typeB,
					typeAReg, typeBReg, debugTable, level + 1);
			}
			else
			{
				internalRegisterCollisionAgent(agentTypes, agentType,
					typeA, m_shapeInheritance.m_data[i].m_primaryType,
					typeAReg, typeBReg, debugTable, level + 1);
			}
		}
	}

	int aStart = typeA;
	int aEnd = typeA + 1;
	int bStart = typeB;
	int bEnd = typeB + 1;
	if (typeA == -1)
	{
		aStart = 1;
		aEnd = 32;
		level++;
	}
	if (typeB == -1)
	{
		bStart = 1;
		bEnd = 32;
		level++;
	}

	for (int a = aStart; a < aEnd; a++)
	{
		for (int b = bStart; b < bEnd; b++)
		{
			agentTypes[a][b] = (unsigned char)agentType;
			if (debugTable)
			{
				DebugEntry* e = &(*debugTable)[a][b];
				if (m_checkEnabled && level > e->m_priority)
				{
					char buf[1000];
					hkString_snprintf(buf, 1000,
						"Agent handling types <%s-%s> would override more specialized agent <%s-%s>\n"
						"Maybe the order of registering your collision agent is wrong, make sure you register your alternate type agents first",
						hkShapeType_toString(typeA), hkShapeType_toString(typeB),
						hkShapeType_toString(e->m_typeA), hkShapeType_toString(e->m_typeB));
				}
				e->m_typeA = (char)typeAReg;
				e->m_typeB = (char)typeBReg;
				e->m_priority = (char)level;
			}
		}
	}
}

// @ 0x010cd700
hkCollisionDispatcher_s010c_ca60* hkCollisionDispatcher_s010c_ca60::init(hkpContactMgrFactory* factory)
{
	m_defaultCollisionAgent = (void (*)())factory;
	m_referenceCount = 1;
	m_vptr = (void**)0x014a4360;

	for (int i = 0; i < 64; i++)
	{
		m_agent2Func[i].m_isFlipped = 0;
		m_agent2Func[i].m_isPredictive = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		m_agent3Func[i].m_updateFilterFunc = 0;
		m_agent3Func[i].m_invalidateTimFunc = 0;
		m_agent3Func[i].m_warpTimeFunc = 0;
		m_agent3Func[i].m_sepNormalFunc = 0;
		m_agent3Func[i].m_isPredictive = 0;
		m_agent3Func[i].m_ignoreSymmetricVersion = 0;
	}

	m_shapeInheritance.m_data = 0;
	m_shapeInheritance.m_size = 0;
	m_shapeInheritance.m_capacityAndFlags = (int)0x80000000;
	m_debugAgent2Table = 0;
	m_debugAgent2TablePred = 0;
	m_debugAgent3Table = 0;
	m_debugAgent3TablePred = 0;
	m_collisionAgentRegistered = 0;
	m_checkEnabled = 1;
	m_numAgent3Types = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_contactMgrFactory[i][j] = factory;
			if (factory)
				factory->addReference();
		}
	}

	for (int i = 0; i < 32; i++)
		m_hasAlternateType[i] = 1 << i;

	resetCreationFunctions();

	m_agent3AgentSize = 0x80;
	m_agent3SectorSize = 0x200;
	m_agent3Registered = 0;
	return this;
}

// @ 0x010cdac0
void hkBvTreeStreamAgent::updateShapeCollectionFilter(void* a, void* b, void* c)
{
    v1c = 0; v18 = 0; v14 = 0; v10 = 0;
    v2c = 0; v28 = 0; v24 = 0; v20 = 0;

    // Caller-provided block handed to the machine by address.  Field order follows the
    // original's stack stores: arg1, arg2->vtable[3], arg2, arg3, this->+0x08.
    struct Args {
        void* a;             // +0x00  (first argument)
        void* slot;          // +0x04  (b->vtable[3])
        void* b;             // +0x08  (second argument)
        void* c;             // +0x0c  (third argument)
        void* d;             // +0x10  (this->+0x08)
    } args;

    args.a    = a;
    args.slot = *(void**)(*(char**)b + 0xc);
    args.b    = b;
    args.c    = c;
    args.d    = *(void**)((char*)this + 8);

    hkAgent1nMachine_UpdateShapeCollectionFilter((char*)this + 0x30, &args);
}

// @ 0x010cdc20
void hkAlgorithm_quickSortRecursive(unsigned int* base, int lo, int hi, hkLessUint)
{
    do {
        unsigned int pivot = base[(lo + hi) >> 1];
        int i = hi;
        int j = lo;
        do {
            while (base[j] < pivot)
                ++j;
            while (pivot < base[i])
                --i;
            if (i < j)
                break;
            if (i != j) {
                unsigned int t = base[i];
                base[i] = base[j];
                base[j] = t;
            }
            --i;
            ++j;
        } while (j <= i);
        if (lo < i)
            hkAlgorithm_quickSortRecursive(base, lo, i, hkLessUint());
        lo = j;
        if (hi <= j)
            return;
    } while (true);
}

// @ 0x010cdcd0
void hkBvTreeStreamAgent::calcStatistics(hkStatisticsCollector_s010c_da80* c) const
{
    c->addObjectStat("BvTreeAgt3", 8, (void*)this);

    // A negative m_capacityAndFlags means the sector storage is not owned by this agent (the
    // top flag bit is set), in which case it is not reported.
    if ((m_sectors.m_capacityAndFlags & 0x80000000) == 0)
        c->addBufferStat("SectorPtrs", 8, m_sectors.m_data,
                         m_sectors.m_size * 4, m_sectors.getCapacity() * 4);

    hkTrackerCalcStatistics((char*)this + 0x30, c);
}

// @ 0x010cea90
void* __fastcall FUN_010cea90(BvStreamAgent* self, int, unsigned flags)
{
    self->vtbl = (void*)0x14a43f8;
    {
        int cap = *(int*)((char*)self + 0x38);
        if ((cap & 0x80000000) == 0) {
            void* tm = TlsGetValue(*(unsigned*)0x016e4174);
            THREADMEM(tm)->deallocateChunk(*(void**)((char*)self + 0x30),
                (*(int*)((char*)self + 0x38) & 0x3fffffff) << 2, 0x14);
        }
    }
    self->vtbl = (void*)0x13ef094;
    if (flags & 1)
        HKMEM->release(self, self->flags, 0x1c);
    return self;
}

// @ 0x010ceaf0
BvStreamAgent* __fastcall FUN_010ceaf0(BvStreamAgent* self, int, int a, int b, int* c, int d)
{
    self->mgr = d;
    self->flags = 1;
    self->vtbl = (void*)0x14a43f8;
    BV_ARR(self).begin = (char*)self + 0x3c;
    BV_ARR(self).count = 0;
    BV_ARR(self).cap = 0x80000001;
    self->field0c = *c;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
    *(int*)((char*)self + 0x1c) = 0;
    *(int*)((char*)self + 0x20) = 0;
    *(int*)((char*)self + 0x24) = 0;
    *(int*)((char*)self + 0x28) = 0;
    *(int*)((char*)self + 0x2c) = 0;
    FUN_01103bc0((char*)self + 0x30);
    return self;
}

// @ 0x010ceb50
void* FUN_010ceb50(int a, int b, int* c, int d)
{
    BvStreamAgent* p = (BvStreamAgent*)HKMEM->alloc(0x40, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x40;
    return FUN_010ceaf0(p, 0, a, b, c, d);
}

// @ 0x010ceb90
void __fastcall FUN_010ceb90(BvStreamAgent* self, int)
{
    self->vtbl = (void*)0x14a43f8;
    {
        int cap = *(int*)((char*)self + 0x38);
        if ((cap & 0x80000000) == 0) {
            void* tm = TlsGetValue(*(unsigned*)0x016e4174);
            THREADMEM(tm)->deallocateChunk(*(void**)((char*)self + 0x30),
                (*(int*)((char*)self + 0x38) & 0x3fffffff) << 2, 0x14);
        }
    }
    self->vtbl = (void*)0x13ef094;
}

// @ 0x010cec10
void __stdcall FUN_010cec10(int a, int b, int c, int d)
{
    int local[3];
    local[2] = d;
    local[1] = 0x7f7fffee;
    local[0] = 0x14a43a4;
    FUN_010e4d50(b, a, c, local);
}

// @ 0x010cec70
void __fastcall FUN_010cec70(void* self, int, int a, int b, int c, int* d)
{
    float old = *(float*)((char*)d + 0x3034);
    int* first = (int*)*d;

    ((BvAgentApi*)self)->processCollision(b, a, c, d);
    while (first < (int*)*d) {
        cpSetFlipped((ContactPoint*)first, 0, (ContactPoint*)first);
        first += 0xc;
    }
    if (old != *(float*)((char*)d + 0x3034)) {
        *(float*)((char*)d + 0x20) = -*(float*)((char*)d + 0x20);
        *(float*)((char*)d + 0x24) = -*(float*)((char*)d + 0x24);
        *(float*)((char*)d + 0x28) = -*(float*)((char*)d + 0x28);
    }
}

// @ 0x010cecf0
void __fastcall FUN_010cecf0(ContactPoint* self, int, const ContactPoint* o)
{
    float d = o->n.v[3];
    self->p = o->p;
    self->p.v[0] = d * o->n.v[0] + self->p.v[0];
    self->p.v[1] = d * o->n.v[1] + self->p.v[1];
    self->p.v[2] = d * o->n.v[2] + self->p.v[2];
    self->p.v[3] = d * o->n.v[3] + self->p.v[3];
    self->n.v[0] = -o->n.v[0];
    self->n.v[1] = -o->n.v[1];
    self->n.v[2] = -o->n.v[2];
    *(int*)&self->n.v[3] = *(int*)&o->n.v[3];
}

// @ 0x010ced60
void __stdcall FUN_010ced60(int a, int b, float* c, int d, int e)
{
    float cp[12];
    QueryResult col1;
    QueryResult col2;
    int i;

    cp[0] = c[0];
    cp[1] = c[1];
    cp[2] = c[2];
    cp[3] = c[3];
    cp[4] = -c[4];
    cp[5] = -c[5];
    cp[6] = -c[6];
    cp[7] = -c[7];
    cp[8] = c[8];
    cp[9] = c[9];
    cp[10] = c[10];
    cp[11] = c[11];

    col1.vtbl = (void*)0x14a43ac;
    col1.dist = 0x7f7fffee;
    for (i = 0; i < 4; i++)
        col1.p[i] = c[i];
    col1.user = d;

    if (e != 0) {
        col2.vtbl = (void*)0x14a43ac;
        col2.dist = 0x7f7fffee;
        for (i = 0; i < 4; i++)
            col2.p[i] = c[4 + i];
        col2.user = e;
        FUN_010e49c0(b, a, cp, &col1, &col2);
        return;
    }
    FUN_010e49c0(b, a, cp, &col1, 0);
}

// @ 0x010ceea0
void* FUN_010ceea0(int a, int b, int* c, int d)
{
    BvStreamAgent* p = (BvStreamAgent*)HKMEM->alloc(0x40, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x40;
    FUN_010ceaf0(p, 0, b, a, c, d);
    p->vtbl = (void*)0x14a442c;
    return p;
}

// @ 0x010cf090
void __fastcall FUN_010cf090(MRayAgent* self, int)
{
    int n = self->count;
    int i;
    for (i = 0; i < n; i++) {
        unsigned short raw = self->map[i];
        int id = raw;
        if (id != 0xffff)
            ((ContactMgr*)self->mgr)->release(id);
    }
    (*(void (__thiscall**)(MRayAgent*, int))self->vtbl)(self, 1);
}

// @ 0x010cf0d0
void __fastcall FUN_010cf0d0(int, int, int* bodyA, int* bodyB, int* input, int* collector)
{
    mrClosestPoints(bodyA, bodyB, input, collector);
}

// @ 0x010cf470
void __stdcall FUN_010cf470(int* bodyA, int* bodyB, int* input, int* collector)
{
    mrClosestPoints(bodyA, bodyB, input, collector);
}

// @ 0x010cf850
MRayAgent* __fastcall FUN_010cf850(MRayAgent* self, int, int* a, int b, int c, int d)
{
    int n;
    int i;

    self->mgr = d;
    self->flags = 1;
    self->vtbl = (void*)0x14a4488;
    self->map = (unsigned short*)((char*)self + 0x18);
    self->count = 0;
    self->cap = 0x80000004;

    n = *(int*)(*a + 0x10);
    if ((self->cap & 0x3fffffff) < n) {
        int m = (self->cap & 0x3fffffff) * 2;
        if (m <= n)
            m = n;
        FUN_0107f4a0(&self->map, m, 2);
    }
    self->count = n;
    for (i = 0; i < n; i++)
        self->map[i] = -1;
    return self;
}

// @ 0x010cf8d0
void __fastcall FUN_010cf8d0(MRayAgent* self, int, int* bodyA, int* bodyB, int* input, int** out)
{
    int* shapeA = (int*)*bodyA;
    RayShape* shapeB = (RayShape*)*bodyB;
    HkTransform t;
    int n;
    float* ray;
    int i;

    monMark(0x14a4478);
    FUN_010810f0(&t, 0, (float*)bodyB[2], (float*)bodyA[2]);

    n = shapeA[4];
    ray = (float*)shapeA[3];
    for (i = 0; i < n; i++) {
        __declspec(align(16)) float p0[4], p1[4], nrm[4];
        char hit;

        p0[0] = t.m[0] * ray[0] + (t.m[4] * ray[1] + t.m[8] * ray[2]) + t.m[12];
        p0[1] = t.m[1] * ray[0] + (t.m[5] * ray[1] + t.m[9] * ray[2]) + t.m[13];
        p0[2] = t.m[2] * ray[0] + (t.m[6] * ray[1] + t.m[10] * ray[2]) + t.m[14];
        p0[3] = 0.0f;

        p1[0] = t.m[0] * ray[4] + (t.m[4] * ray[5] + t.m[8] * ray[6]) + t.m[12];
        p1[1] = t.m[1] * ray[4] + (t.m[5] * ray[5] + t.m[9] * ray[6]) + t.m[13];
        p1[2] = t.m[2] * ray[4] + (t.m[6] * ray[5] + t.m[10] * ray[6]) + t.m[14];
        p1[3] = 0.0f;

        shapeB->castRay(&hit, p0, nrm);
        if (!hit) {
            int id = self->map[i];
            if (id != -1) {
                ((ContactMgr*)self->mgr)->release(id);
                self->map[i] = -1;
            }
        } else {
            ContactPoint* pt = (ContactPoint*)*out;
            float f = 1.0f - 1.0f;
            int id;

            pt->p.v[0] = p1[0] * 1.0f + p0[0] * f;
            pt->p.v[1] = p1[1] * 1.0f + p0[1] * f;
            pt->p.v[2] = p1[2] * 1.0f + p0[2] * f;
            pt->p.v[3] = p1[3] * 1.0f + p0[3] * f;
            FUN_01081360(pt, 0, (void*)bodyB[2], pt->p.v);
            FUN_010814a0(pt->n.v, 0, (void*)bodyB[2], nrm);
            pt->n.v[3] = (1.0f - 1.0f) * ray[3] + *(float*)((char*)shapeA + 0x18);

            id = self->map[i];
            if (id == -1) {
                id = ((ContactMgr*)self->mgr)->makeContact(bodyA, bodyB, input, pt);
                self->map[i] = id;
            }
            if (self->map[i] != -1) {
                *out = (int*)((char*)*out + 0x30);
                *(short*)((char*)pt + 0x20) = self->map[i];
            }
        }
        ray += 8;
    }
    monMark(0x149cc34);
}

// @ 0x010cfc70
void* FUN_010cfc70(int a, int b, int c, int d)
{
    MRayAgent* p = (MRayAgent*)HKMEM->alloc(0x20, 0x1c);
    *(unsigned short*)((char*)p + 4) = 0x20;
    return FUN_010cf850(p, 0, (int*)a, b, c, d);
}
