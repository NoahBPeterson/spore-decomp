#pragma once
// Havok 3.1.0 (statically linked into SporeApp.exe) - shared declarations for batch b005 slices
// s010cbaa0, s010869e0, s010e1340 and s010e6530. Layouts come from the binary (vtable dumps, member offsets),
// the dev PDB (tools/pdb_type.py) and match/include/havok31/hkReflectedClasses.h. The Havok 6.x headers were
// used for naming only. "32-bit layout" comments flag pointer-size assumptions; the classes themselves are
// written with real pointers, so a 64-bit build compiles but its offsets differ from the binary's.
#include "types.h"
#include <stddef.h>
#if defined(_MSC_VER)
#include <intrin.h>
#endif

// Value the x87 keeps on its stack without ever storing it (80-bit in 53/64-bit mode, 24-bit mantissa when the
// main thread has the D3D9 single-precision control word). Spots are marked "// X87-PRECISION:".
typedef double hkX87Real;

#if defined(_MSC_VER)
#define HK_CALL __cdecl
#else
#define HK_CALL
#endif
typedef float hkReal;
typedef unsigned int hkUint32;
typedef uint64_t hkUint64;
typedef short hkInt16;

// A user-declared constructor makes this non-POD so MSVC returns it through a hidden pointer, as the binary does.
class hkBool
{
public:
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

enum
{
	HK_MEMORY_CLASS_ARRAY = 0x14,
	HK_MEMORY_CLASS_COLLIDE = 0x1c,
	HK_MEMORY_CLASS_CDINFO = 0x1e
};

// ---------------------------------------------------------------------------------------------------------
// memory
// ---------------------------------------------------------------------------------------------------------
// hkMemory::s_instance is the global at 0x016E4178. Slot numbers match the binary's vtable.
class hkMemory
{
public:
	virtual void* allocate(int nbytes, int cl);                          // 0
	virtual void deallocate(void* p);                                    // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);    // 2
	virtual void alignedDeallocate(void* p);                             // 3
	virtual void* allocateChunk(int nbytes, int cl);                     // 4 (+0x10)
	virtual void deallocateChunk(void* p, int nbytes, int cl);           // 5 (+0x14)
	static hkMemory* s_instance;
};

struct hkArrayUtil
{
	static void _reserveMore(void* arrayBase, int elemSize);             // 0x0107F530
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize); // 0x0107F4A0
};

enum { HK_ARRAY_CAPACITY_MASK = 0x3fffffff };

// hkArray<T>: m_data / m_size / m_capacityAndFlags (bit 31: memory not owned).
template <typename T>
struct hkArray
{
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
	void pushBack(const T& t)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size = m_size + 1;
	}
	void setSize(int n)
	{
		int cap = getCapacity();
		if (cap < n)
		{
			int newCap = cap * 2;
			if (newCap <= n) newCap = n;
			hkArrayUtil::_reserveExactly(this, newCap, (int)sizeof(T));
		}
		m_size = n;
	}
};

// ---------------------------------------------------------------------------------------------------------
// monitor stream (timers). TLS slot 0x016E42A4 = current write pointer, 0x016E42A8 = end pointer.
// ---------------------------------------------------------------------------------------------------------
#if defined(_WIN32)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
static inline void* hkTlsGet(unsigned long i) { return TlsGetValue(i); }
static inline void hkTlsSet(unsigned long i, void* v) { TlsSetValue(i, v); }
#else
#include <pthread.h>
// Porting note: on POSIX the TLS indices would be pthread_key_t values created at hkMonitorStream::init.
static inline void* hkTlsGet(unsigned long i) { return pthread_getspecific((pthread_key_t)i); }
static inline void hkTlsSet(unsigned long i, void* v) { pthread_setspecific((pthread_key_t)i, v); }
#endif
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern const char hkMonitorTimerEndTag[];           // string at 0x0149cc34 (end of a plain timer)
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
#if defined(_MSC_VER)
#define HK_RDTSC32() ((uint32_t)__rdtsc())
#else
#define HK_RDTSC32() ((uint32_t)__builtin_ia32_rdtsc())
#endif
#define HK_TIMER_COMMAND(name) do { \
	void* hkEnd_ = hkTlsGet(g_hkMonitorStreamEndTls); \
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		c_->m_time0 = HK_RDTSC32(); \
		hkTlsSet(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)

// ---------------------------------------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------------------------------------
#if defined(_MSC_VER)
#define HK_ALIGN16 __declspec(align(16))
#else
#define HK_ALIGN16 __attribute__((aligned(16)))
#endif
struct hkRotation;
struct HK_ALIGN16 hkVector4
{
	float x, y, z, w;
	void setRotatedInverseDir(const hkRotation& a, const hkVector4& b);     // 0x01081440 (this = transpose(a) * b)
};
struct hkAabb { hkVector4 m_min; hkVector4 m_max; };
struct hkRotation { hkVector4 m_col[3]; };
// hkMotionState: m_transform is the first member (rotation rows at +0..+0x2f, translation at +0x30).
struct hkTransform
{
	hkVector4 m_rot[3];
	hkVector4 m_trans;
	void setMulInverseMul(const hkTransform& a, const hkTransform& b);      // 0x010810F0 (this = inverse(a) * b)
};

// ---------------------------------------------------------------------------------------------------------
// referenced objects
// ---------------------------------------------------------------------------------------------------------
class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}                                     // 0
	virtual void calcStatistics(struct hkStatisticsCollector* c) const {} // 1 (0x0052E650 is the empty default)

	// HK_DECLARE_CLASS_ALLOCATOR: chunk allocation, size stored in m_memSizeAndFlags.
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_COLLIDE);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_COLLIDE);
	}
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}

	// memSize == 0 means "not heap owned": never reference counted.
	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			m_referenceCount = (hkInt16)(m_referenceCount - 1);
			if (m_referenceCount == 0)
				delete this;
		}
	}

	hkInt16 m_memSizeAndFlags;  // 0x04
	hkInt16 m_referenceCount;   // 0x06

protected:
	hkReferencedObject() : m_referenceCount(1) {}
};

// hkStatisticsCollector vtable slots as called by the binary.
struct hkStatisticsCollector
{
	virtual void s0();
	virtual void beginObject(const char* name, int mode, const void* obj);                                     // +4
	virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // +8
	virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // +0xc
	virtual void s4();
	virtual void s5();
	virtual void endObject();                                                                                  // +0x18
};

// ---------------------------------------------------------------------------------------------------------
// shapes and collision bodies
// ---------------------------------------------------------------------------------------------------------
struct hkCdBody;
struct hkShapeRayCastInput
{
	hkVector4 m_from;                          // +0
	hkVector4 m_to;                            // +0x10
	uint32_t m_filterInfo;                     // +0x20
	const void* m_rayShapeCollectionFilter;    // +0x24 (hkRayShapeCollectionFilter*)
	uint32_t m_pad[2];                         // size 0x30
};
struct hkShapeRayCastOutput
{
	hkVector4 m_normal;                        // +0
	uint32_t m_shapeKey;                       // +0x10
	float m_hitFraction;                       // +0x14
	uint32_t m_pad[2];                         // size 0x20
};
struct hkWorldRayCastOutput : hkShapeRayCastOutput
{
	const struct hkCollidable* m_rootCollidable;   // +0x20 (size 0x30)
};
struct hkWorldRayCastInput
{
	hkVector4 m_from;                          // +0
	hkVector4 m_to;                            // +0x10
	hkBool m_enableShapeCollectionFilter;      // +0x20
	uint32_t m_filterInfo;                     // +0x24
	uint32_t m_pad[2];                         // size 0x30
	hkWorldRayCastInput() : m_enableShapeCollectionFilter(false) {}
};

// A virtual function table with the Havok 3.1 hkRayHitCollector shape: slot 0 addRayHit, slot 1 destructor.
struct hkRayHitCollector
{
	virtual void addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo) = 0;   // 0
	virtual ~hkRayHitCollector() {}                                                              // 1
	float m_earlyOutHitFraction;               // +4
};

struct hkShape : hkReferencedObject
{
	int m_userData;                            // +8
	virtual int getType() const = 0;                                                                   // 2
	virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const = 0;    // 3 (+0xc)
	virtual float getMaximumProjection(const hkVector4& direction) const = 0;                         // 4 (0x010c3510 is hkShape's)
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const = 0; // 5 (+0x14)
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody,
	                                  hkRayHitCollector& collector) const = 0;                        // 6 (+0x18)
protected:
	hkShape() : m_userData(0) {}
};

// hkCdBody (0x10 bytes in the 32-bit binary).
struct hkCdBody
{
	const hkShape* m_shape;                    // +0
	uint32_t m_shapeKey;                       // +4
	const void* m_motion;                      // +8 (hkMotionState*)
	const hkCdBody* m_parent;                  // +0xc
};
