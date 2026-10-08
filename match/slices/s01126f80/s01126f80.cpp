// Havok 3.1.0: recursive shape -> hkMassProperties walker (0x01126f80), the helper behind
// hkInertiaTensorComputer::computeShapeVolumeMassProperties. For one shape: containers recurse into their children,
// transform-like shapes compose the transform and recurse into the single child, a multi-sphere is walked one sphere
// at a time through a stack temp hkSphereShape, and the convex primitives call the matching
// hkInertiaTensorComputer::compute*VolumeMassProperties with unit mass. The primitive's properties are then scaled by
// its volume and combined (via hkMassElement x2 + combineMassProperties) with the running `result`, rotated by `xform`.
// Reconstructed from the binary; no Havok 3.1 source. Built /vc71 /O2 /MD /Gy /TP (Havok module).
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174

class hkThreadMemory
{
public:
	struct Stack
	{
		char* m_current;   // +0x20
		Stack* m_prev;     // +0x24
		char* m_base;      // +0x28
		char* m_end;       // +0x2c
	};
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void* onStackOverflow(int nbytes);   // slot 3 (+0xc)
	virtual void onStackUnderflow(void* p);      // slot 4 (+0x10)

	uint32_t m_pad4[7];
	Stack m_stack;   // +0x20

	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

	inline void* allocateStack(int nbytesin)
	{
		int actualBytes = (nbytesin + 16) & ~15;
		char* p = m_stack.m_current;
		char* end = p + actualBytes;
		if (end <= m_stack.m_end)
		{
			m_stack.m_current = end;
			return p;
		}
		return onStackOverflow(actualBytes);
	}
	inline void deallocateStack(void* p)
	{
		m_stack.m_current = (char*)p;
		if (p == m_stack.m_base)
			onStackUnderflow(p);
	}
};

struct hkArrayUtil
{
	static void _reserveMore(void* array, int sizeElem);   // 0x0107F530
};

template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	__forceinline ~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	__forceinline void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
};

class __declspec(align(16)) hkVector4
{
public:
	hkReal x, y, z, w;
	__forceinline void setZero4() { x = y = z = w = 0.0f; }
	__forceinline void setZeroAscending() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	__forceinline void set(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
	void setTransformedPos(const class hkTransform& t, const hkVector4& v);   // 0x01081360
};

class hkMatrix3
{
public:
	hkVector4 m_col0, m_col1, m_col2;
	void mul(hkReal s);   // 0x01081BB0
	__forceinline void setZero()
	{
		m_col0.setZeroAscending();
		m_col1.setZeroAscending();
		m_col2.setZeroAscending();
	}
};

class hkRotation : public hkMatrix3
{
public:
	__forceinline void setIdentity()
	{
		m_col0.set(kOne, kZero, kZero, kZero);
		m_col1.set(kZero, kOne, kZero, kZero);
		m_col2.set(kZero, kZero, kOne, kZero);
	}
};

class hkTransform
{
public:
	hkRotation m_rotation;
	hkVector4 m_translation;
	void operator=(const hkTransform& t);                      // 0x01088410
	void setMul(const hkTransform& a, const hkTransform& b);   // 0x01080EF0
};

struct hkMassProperties
{
	hkReal m_volume;                 // +0x0
	hkReal m_mass;                   // +0x4
	hkVector4 m_centerOfMass;        // +0x10
	hkMatrix3 m_inertiaTensor;       // +0x20
	__forceinline hkMassProperties() : m_volume(0.0f), m_mass(0.0f)
	{
		m_centerOfMass.setZero4();
		m_inertiaTensor.setZero();
	}
	void operator=(const hkMassProperties& p);   // 0x00B4D3F0
};

struct hkMassElement
{
	hkMassProperties m_properties;   // +0x0
	hkTransform m_transform;         // +0x50
	hkMassElement();                 // 0x01124930
};

class hkInertiaTensorComputer
{
public:
	static hkResult __cdecl computeSphereVolumeMassProperties(hkReal radius, hkReal mass, hkMassProperties& result);                       // 0x01124060
	static hkResult __cdecl computeBoxVolumeMassProperties(const hkVector4& halfExtents, hkReal mass, hkMassProperties& result);          // 0x01124110
	static hkResult __cdecl combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result);                       // 0x011249C0
	static hkResult __cdecl computeVertexHullVolumeMassProperties(const hkReal* vertexIndices, int striding, int numVertices,
	                                                              hkReal mass, hkMassProperties& result);                                   // 0x011252D0
	static hkResult __cdecl computeTriangleSurfaceMassProperties(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2,
	                                                             hkReal thickness, hkReal mass, hkMassProperties& result);                  // 0x01125560
	static hkResult __cdecl computeCapsuleVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
	                                                           hkReal radius, hkReal mass, hkMassProperties& result);                       // 0x01126100
	static hkResult __cdecl computeCylinderVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
	                                                            hkReal radius, hkReal mass, hkMassProperties& result);                      // 0x01126B40
};

// ---- shape stubs (retail 3.1 layouts, read off the disassembly) ----
class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}   // vtable 0x013EF094 after the dtor chain
	uint16_t m_memSize;
	uint16_t m_refCount;
};

class hkShape : public hkReferencedObject
{
public:
	virtual void s1();
	virtual int getType() const = 0;   // slot 2 (+8)
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
};

// Convex shapes: slot 7 reports the vertex count through an out-parameter, slot 8 fills an aligned vertex buffer.
class hkConvexView : public hkShape
{
public:
	virtual void getNumVertices(int* out) const;                // +0x1c
	virtual const hkReal* getVertices(void* buffer) const;      // +0x20
};

// Shape collections (list, mopp, ...): key-based child access.
class hkCollectionView : public hkShape
{
public:
	virtual void s7();
	virtual int getFirstKey() const;                                  // +0x20
	virtual int getNextKey(int key) const;                            // +0x24
	virtual const hkShape* getChildShape(int key, void* buffer) const; // +0x28
};

// hkSphereShape is built on the stack for each sphere of a multi-sphere (ctor 0x010C3770).
class hkSphereShape : public hkShape
{
public:
	hkSphereShape(hkReal radius);   // 0x010C3770 (thiscall)
	virtual ~hkSphereShape() {}
	virtual int getType() const { return 4; }
	hkReal m_radius;                // +0xc
};

// field views at the retail offsets
struct hkShapeFields
{
	uint32_t m_vtbl, m_pad4, m_pad8;
	hkReal m_radius;       // +0xc (sphere, capsule, triangle)
	uint32_t m_child10;    // +0x10
};

struct hkSphereFields { uint32_t pad[3]; hkReal radius; };
struct hkBoxFields { uint32_t pad[4]; hkReal halfExtents[4]; };
struct hkTriangleFields { uint32_t pad[3]; hkReal radius; hkReal v[3][4]; };
struct hkCapsuleFields { uint32_t pad[3]; hkReal radius; hkReal v[2][4]; };
struct hkCylinderShapeView
{
	uint32_t pad[4];
	hkReal m_cylinderRadius;   // +0x10
	uint32_t pad2[3];
	hkReal vertexA[4];         // +0x20
	hkReal vertexB[4];         // +0x30
	__forceinline hkReal getCylinderRadius() const { return m_cylinderRadius; }
};
struct hkMultiSphereFields
{
	uint32_t pad[3];
	int m_numSpheres;          // +0xc
	hkReal m_spheres[1][4];    // +0x10: x y z radius
};
struct hkChild10Fields { uint32_t pad[4]; const hkShape* m_child; };         // convex-translate / type 0x16
struct hkTranslateFields { uint32_t pad[4]; const hkShape* m_child; uint32_t pad2[2]; hkReal translation[4]; };   // +0x20
struct hkTransformFields10 { uint32_t pad[4]; const hkShape* m_child; uint32_t pad2[2]; hkTransform m_transform; };
struct hkTransformFields0c { uint32_t pad[3]; const hkShape* m_child; uint32_t pad2[4]; hkTransform m_transform; };

typedef uint32_t hkShapeBuffer[124];

// @ 0x01126f80
void __cdecl computeShapeMassProperties(const hkShape* shape, const hkTransform* xform, hkMassProperties* result)
{
	hkMassProperties props;
	hkTransform composed;

	switch (shape->getType())
	{
	case 4:
		hkInertiaTensorComputer::computeSphereVolumeMassProperties(((const hkSphereFields*)shape)->radius, 1.0f, props);
		break;
	case 7:
	{
		hkVector4 halfExtents = *(const hkVector4*)((const hkBoxFields*)shape)->halfExtents;
		hkInertiaTensorComputer::computeBoxVolumeMassProperties(halfExtents, 1.0f, props);
		break;
	}
	case 9:
	{
		const hkConvexView* convex = (const hkConvexView*)shape;
		int numVertices;
		convex->getNumVertices(&numVertices);
		void* mem = hkThreadMemory::getInstance().allocateStack(numVertices * 16);
		const hkReal* vertices = convex->getVertices(mem);
		hkInertiaTensorComputer::computeVertexHullVolumeMassProperties(vertices, 16, numVertices, 1.0f, props);
		hkThreadMemory::getInstance().deallocateStack(mem);
		break;
	}
	case 6:
	{
		const hkTriangleFields* t = (const hkTriangleFields*)shape;
		hkVector4 v0 = *(const hkVector4*)t->v[0];
		hkVector4 v1 = *(const hkVector4*)t->v[1];
		hkVector4 v2 = *(const hkVector4*)t->v[2];
		hkInertiaTensorComputer::computeTriangleSurfaceMassProperties(v0, v1, v2, t->radius, 1.0f, props);
		break;
	}
	case 0x16:
		computeShapeMassProperties(((const hkChild10Fields*)shape)->m_child, xform, result);
		return;
	case 0xe:
	{
		const hkTranslateFields* tf = (const hkTranslateFields*)shape;
		hkTransform t;
		t.m_rotation.setIdentity();
		t.m_translation = *(const hkVector4*)tf->translation;
		composed.setMul(*xform, t);
		computeShapeMassProperties(tf->m_child, &composed, result);
		return;
	}
	case 0xf:
	{
		const hkTransformFields10* tf = (const hkTransformFields10*)shape;
		composed.setMul(*xform, tf->m_transform);
		computeShapeMassProperties(tf->m_child, &composed, result);
		return;
	}
	case 0x19:
	{
		const hkTransformFields0c* tf = (const hkTransformFields0c*)shape;
		composed.setMul(*xform, tf->m_transform);
		computeShapeMassProperties(tf->m_child, &composed, result);
		return;
	}
	case 0xb:
	{
		const hkMultiSphereFields* ms = (const hkMultiSphereFields*)shape;
		for (int i = 0; i < ms->m_numSpheres; i++)
		{
			hkTransform t = *xform;
			t.m_translation.setTransformedPos(t, *(const hkVector4*)ms->m_spheres[i]);
			hkSphereShape sphere(ms->m_spheres[i][3]);
			computeShapeMassProperties(&sphere, &t, result);
		}
		return;
	}
	case 2:
	case 3:
	case 0xc:
	case 0xd:
	case 0x10:
	case 0x18:
	{
		if (shape->getType() == 3 || shape->getType() == 0x18)
			shape = ((const hkTransformFields0c*)shape)->m_child;
		const hkCollectionView* coll = (const hkCollectionView*)shape;
		hkShapeBuffer buffer;
		int key = coll->getFirstKey();
		if (key == -1)
			return;
		do
		{
			const hkShape* child = coll->getChildShape(key, buffer);
			if (child)
				computeShapeMassProperties(child, xform, result);
			key = coll->getNextKey(key);
		} while (key != -1);
		return;
	}
	case 8:
	{
		const hkCapsuleFields* c = (const hkCapsuleFields*)shape;
		hkInertiaTensorComputer::computeCapsuleVolumeMassProperties(*(const hkVector4*)c->v[0], *(const hkVector4*)c->v[1],
		                                                            c->radius, 1.0f, props);
		break;
	}
	case 5:
	{
		const hkCylinderShapeView* c = (const hkCylinderShapeView*)shape;
		hkInertiaTensorComputer::computeCylinderVolumeMassProperties(*(const hkVector4*)c->vertexA, *(const hkVector4*)c->vertexB,
		                                                             c->getCylinderRadius(), 1.0f, props);
		break;
	}
	case 0x17:
		break;
	default:
		return;
	}

	if (props.m_volume != kZero)
	{
		props.m_mass = props.m_mass * props.m_volume;
		props.m_inertiaTensor.mul(props.m_volume);

		hkArray<hkMassElement> elements;
		{
			hkMassElement e;
			e.m_properties = *result;
			elements.pushBack(e);
		}
		{
			hkMassElement e;
			e.m_properties = props;
			e.m_transform = *xform;
			elements.pushBack(e);
		}
		hkInertiaTensorComputer::combineMassProperties(elements, *result);
	}
}
