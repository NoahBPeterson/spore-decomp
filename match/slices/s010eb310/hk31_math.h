#pragma once
// Havok 3.1.0 (as linked into SporeApp.exe): math / collision / dynamics class stubs shared by the slices
// s010eb310, s0111c7f0, s010813d0 and s0108c140 (batch b005). Member offsets are the 32-bit offsets seen in the
// binary; pointers are real pointers, so struct sizes differ on 64-bit (behaviour is what is ported).
// Names follow the symbols in symbols/havok_names.txt; the Havok 6.x headers were used for naming only.
#include "types.h"
#include <stddef.h>
#include <math.h>
#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
#endif

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef int16_t hkInt16;
typedef uint8_t hkUint8;
typedef uint64_t hkUint64;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

// A user-declared constructor makes this non-POD, so MSVC returns it through a hidden pointer, as the binary does.
class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

// hkMemory::s_instance is the global at 0x016E4178 (slot 4 = allocateChunk, slot 5 = deallocateChunk).
struct hkMemory
{
	virtual void* allocate(int nbytes, int cl);
	virtual void deallocate(void* p);
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);
	virtual void alignedDeallocate(void* p);
	virtual void* allocateChunk(int nbytes, int cl);
	virtual void deallocateChunk(void* p, int nbytes, int cl);
	static hkMemory* s_instance;
};

class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}   // 0
	virtual void slot1() {}            // 1 (0x0052E650, empty)
	hkInt16 m_memSizeAndFlags;         // +4
	hkInt16 m_referenceCount;          // +6
protected:
	hkReferencedObject() : m_referenceCount(1) {}
};

// Pointer-sized stand-in for values the original keeps on the x87 stack (80-bit) without storing them.
// Spore runs the main-thread x87 at 24-bit precision (docs/floating_point.md), so float would also be right.
// X87-PRECISION: change here to experiment.
typedef double hkX87Real;
typedef float hkReal;
typedef float hkTime;
typedef uint32_t hkShapeKey;
typedef uint16_t hkContactPointId;

// HK_REAL_MAX in this build is 3.40282e+38f == 0x7f7fffee (NOT FLT_MAX).
#define HK_REAL_MAX 3.40282e+38f

struct hkRotation;
struct hkTransform;
struct hkVector4
{
	float x, y, z, w;
	void setTransformedInversePos(const hkTransform& t, const hkVector4& v);   // 0x010813D0
	void setRotatedInverseDir(const hkRotation& r, const hkVector4& v);        // 0x01081440
	void setRotatedDir(const hkRotation& r, const hkVector4& v);               // 0x010814A0
};

struct hkTransform
{
	hkVector4 m_rot[3];   // columns of the rotation (x,y,z; w unused)
	hkVector4 m_trans;
};

struct hkAabb
{
	hkVector4 m_min;
	hkVector4 m_max;
};

// Layouts of the cdbody / input / output structures used by the collision and phantom code.
struct hkMotionState   // size 0xb0 (dev PDB)
{
	hkTransform m_transform;          // +0
	hkVector4 m_centerOfMass0;        // +0x40  (hkSweptTransform)
	hkVector4 m_centerOfMass1;        // +0x50
	hkVector4 m_rotation0;            // +0x60  (hkQuaternion)
	hkVector4 m_rotation1;            // +0x70
	hkVector4 m_centerOfMassLocal;    // +0x80
	hkVector4 m_deltaAngle;           // +0x90
	hkReal m_objectRadius;            // +0xa0
	hkReal m_maxLinearVelocity;       // +0xa4
	hkReal m_maxAngularVelocity;      // +0xa8
	uint16_t m_deactivationClass;     // +0xac
	uint16_t m_deactivationCounter;   // +0xae
	hkMotionState& operator=(const hkMotionState&);   // 0x010DF5D0
};

struct hkContactPoint
{
	hkVector4 m_position;
	hkVector4 m_separatingNormal;   // w = distance
	void setFlipped(const hkContactPoint& other);                                        // 0x010CECF0
	void setSeparatingNormal(const hkVector4& normal, hkReal dist);                      // 0x010D0040
};

struct hkShape;
struct hkCdBody
{
	const hkShape* m_shape;        // +0
	hkShapeKey m_shapeKey;         // +4
	const void* m_motion;          // +8 (hkMotionState* / hkTransform*)
	const hkCdBody* m_parent;      // +0xc
};
struct hkCdPoint
{
	hkContactPoint m_contact;      // +0
	const hkCdBody* m_cdBodyA;     // +0x20
	const hkCdBody* m_cdBodyB;     // +0x24
};
struct hkCdVertex { float x, y, z; union { float w; uint32_t wBits; }; };
struct hkSphere { hkVector4 m_pos; };

struct hkCdPointCollector
{
	virtual ~hkCdPointCollector() {}                     // 0
	virtual void addCdPoint(const hkCdPoint& p) = 0;     // 1
	hkReal m_earlyOutDistance;                           // +4
	hkCdPointCollector() : m_earlyOutDistance(HK_REAL_MAX) {}
};
struct hkCdBodyPairCollector
{
	virtual ~hkCdBodyPairCollector() {}                                       // 0
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;     // 1
	hkBool m_earlyOut;                                                        // +4
	hkCdBodyPairCollector() : m_earlyOut(false) {}
};

// Havok monitor stream timers: TLS slot 0x016e42a4 = write pointer, 0x016e42a8 = end pointer.
// The stream is a debug aid; on 64-bit the command records grow with the pointer size. rdtsc keeps the low 32 bits.
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndTag[];                // 0x00149cc34
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
#ifdef _MSC_VER
#include <intrin.h>
#define HK_RDTSC32() ((uint32_t)__rdtsc())
#else
#define HK_RDTSC32() 0u
#endif
#define HK_TIMER_SPLIT_LIST(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		c_->m_time0 = HK_RDTSC32(); \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_END_LIST() HK_TIMER_SPLIT_LIST(hkMonitorEndTag)

// ---- shapes (vtable slots counted from the binary: 0 dtor, 1 empty, 2 getType, 3 getAabb, 4 getMaximumProjection,
//      5 castRay, 6 castRayWithCollector; hkConvexShape adds 7..11) ------------------------------------------------
struct hkShapeRayCastInput;
struct hkShapeRayCastOutput
{
	hkVector4 m_normal;      // +0
	int m_extraInfo;         // +0x10
	hkReal m_hitFraction;    // +0x14
	hkShapeRayCastOutput() : m_hitFraction(1.0f) {}
};
struct hkShapeCollection;
struct hkRayShapeCollectionFilter
{
	virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection, hkShapeKey key) const = 0;   // 0
};
struct hkShapeRayCastInput
{
	hkVector4 m_from;                                              // +0
	hkVector4 m_to;                                                // +0x10
	uint32_t m_filterInfo;                                         // +0x20
	const hkRayShapeCollectionFilter* m_rayShapeCollectionFilter;  // +0x24
};
struct hkCollisionSpheresInfo { int m_numSpheres; hkBool m_useBuffer; };

struct hkShape : hkReferencedObject
{
	hkUint32 m_userData;   // +8
	hkShape() : m_userData(0) {}
	virtual int getType() const;                                                                                  // 2
	virtual void getAabb(const hkTransform& t, hkReal tolerance, hkAabb& out) const = 0;                          // 3
	virtual hkReal getMaximumProjection(const hkVector4& dir) const;                                              // 4
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const = 0;             // 5
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& body, void* collector) const; // 6
};
struct hkConvexShape : hkShape
{
	hkReal m_radius;   // +0xc
	explicit hkConvexShape(hkReal radius) : m_radius(radius) {}
	virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const = 0;                                 // 7
	virtual const hkSphere* getCollisionSpheres(hkSphere* buffer) const = 0;                                      // 8
	virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const = 0;                            // 9
	virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* out) const = 0;         // 10
	virtual void getFirstVertex(hkVector4& v) const = 0;                                                          // 11
};
#define HK_SHAPE_BUFFER_SIZE 512
struct hkShapeCollection : hkShape
{
	virtual void sc7(); virtual void sc8(); virtual void sc9();                                                   // 7..9
	virtual const hkShape* getChildShape(hkShapeKey key, void* buffer) const;                                     // 10 (0x28)
};

// ---- arrays: layout shared by every hkArray<T> (data, size, capacity | flags) -----------------------------------
struct hkArrayUtil { static void _reserveMore(void* array, int elemSize); };   // 0x0107F530
template <class T>
struct hkArray
{
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;
	void pushBack(const T& t)
	{
		if (m_size == (int)((unsigned)m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size = m_size + 1;
	}
};

// ---- matrices / quaternions (hkMatrix3 = three hkVector4 columns, m_el[col*4 + row]; the 4th row is written as 0) ---
struct hkMatrix3
{
	float m_el[12];
	void transpose();                                                    // 0x01081520
	hkBool isApproximatelyEqual(const hkMatrix3& m, hkReal eps) const;   // 0x010815A0
	void setCrossSkewSymmetric(const hkVector4& v);                      // 0x010817C0
	hkResult invert(hkReal epsilon);                                     // 0x01081810
	void invertSymmetric();                                              // 0x01081990
	void add(const hkMatrix3& m);                                        // 0x01081AD0 (name guessed from the arithmetic)
	void sub(const hkMatrix3& m);                                        // 0x01081B40 (name guessed from the arithmetic)
	void mul(hkReal scale);                                              // 0x01081BB0
	void setMul(const hkMatrix3& a, const hkMatrix3& b);                 // 0x01081DB0
	void mul(const hkMatrix3& m);                                        // 0x010820B0
	void changeBasis(const hkRotation& r);                               // 0x01082130
};
struct hkRotation : hkMatrix3
{
	void setTranspose(const hkRotation& r);                              // 0x01081550
	void setMulInverse(const hkMatrix3& a, const hkRotation& b);         // 0x01081F20
};
struct hkQuaternion
{
	float m_vec[4];   // x y z w
	void normalize();                                                    // 0x010821A0 (name guessed from the arithmetic)
	void setMul(const hkQuaternion& a, const hkQuaternion& b);           // 0x01082210
	void setAxisAngle(const hkVector4& axis, hkReal angle);              // 0x01082310
};

// ---- collision inputs / dispatcher (layouts from the dev PDB, offsets confirmed in the binary) ---------------------
struct hkContactMgr;
struct hkCollisionAgent;
struct hkShapeCollectionFilter;
struct hkProcessCollisionInput;
struct hkProcessCollisionOutput;
struct hkCollisionDispatcher;
struct hkCollisionInput
{
	hkCollisionDispatcher* m_dispatcher;         // +0
	hkShapeCollectionFilter* m_filter;           // +4
	hkReal m_tolerance;                          // +8
	hkBool m_createPredictiveAgents;             // +0xc
};
struct hkCollisionAgentConfig
{
	hkReal m_iterativeLinearCastEarlyOutDistance;   // +0
	int m_iterativeLinearCastMaxIterations;         // +4
};
struct hkProcessCollisionInput : hkCollisionInput
{
	char m_stepInfo[0x10];                       // +0x10 hkStepInfo
	hkCollisionAgentConfig* m_config;            // +0x20
	void* m_dynamicsInfo;                        // +0x24
	void* m_collisionQualityInfo;                // +0x28
};
struct hkLinearCastCollisionInput : hkCollisionInput
{
	hkVector4 m_path;                            // +0x10
	hkReal m_maxExtraPenetration;                // +0x20
	hkReal m_cachedPathLength;                   // +0x24
	const hkCollisionAgentConfig* m_config;      // +0x28
};
typedef hkCollisionAgent* (*hkAgent2CreateFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
typedef void (*hkAgent2GetPenetrationsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
typedef void (*hkAgent2GetClosestPointsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
typedef void (*hkAgent2LinearCastFunc)(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
// 0x14 bytes on 32-bit (5 pointers); the table lives in hkCollisionDispatcher at +0x990 and is indexed by the agent type.
struct hkAgent2Func
{
	hkAgent2CreateFunc m_createFunc;                       // +0
	hkAgent2GetPenetrationsFunc m_getPenetrationsFunc;     // +4
	hkAgent2GetClosestPointsFunc m_getClosestPointFunc;    // +8
	hkAgent2LinearCastFunc m_linearCastFunc;               // +0xc
	void* m_flags;                                         // +0x10
};
struct hkCollisionDispatcher
{
	// 32-bit layout assumption: the byte tables sit at fixed offsets (0x190, 0x590) and the function table at 0x990.
	char m_pad0[0x190];
	uint8_t m_agent2TypesDiscrete[32][32];                 // +0x190 [shapeTypeA][shapeTypeB] -> agent type
	uint8_t m_agent2TypesPredictive[32][32];               // +0x590
	hkAgent2Func m_agent2Func[1];                          // +0x990
	struct Agent3Funcs;
	int registerAgent3(Agent3Funcs& funcs, int typeA, int typeB);   // 0x010CD4C0
};

// ---- hkThreadMemory (per-thread allocator; TLS slot 0x016E4174) -------------------------------------------------------
enum { HK_MEMORY_CLASS_ARRAY_T = 0x14, HK_MEMORY_CLASS_PHANTOM_T = 0x2e };
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174
struct hkThreadMemory
{
	virtual void tm0(); virtual void tm1(); virtual void tm2();
	virtual void* allocateStackChunk(int nbytes);       // 3 (0xc)
	virtual void releaseStackChunk(void* p);            // 4 (0x10)
	void* allocateChunk(int nbytes, int memClass);               // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int memClass);     // 0x0107DB10
	char m_pad[0x20 - sizeof(void*)];
	char* m_stackTop;      // +0x20 (32-bit offset)
	char* m_pad24;
	char* m_stackBase;     // +0x28
	char* m_stackEnd;      // +0x2c
};
static inline hkThreadMemory* hkThreadMemory_getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
