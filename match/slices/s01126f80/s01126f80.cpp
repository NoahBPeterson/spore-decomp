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
	void setRotatedDir(const class hkMatrix3& r, const hkVector4& v);         // 0x010814A0
};

class hkMatrix3
{
public:
	hkVector4 m_col0, m_col1, m_col2;
	void mul(hkReal s);   // 0x01081BB0
	void setCrossSkewSymmetric(const hkVector4& v);            // 0x010817C0
	void setMul(const hkMatrix3& a, const hkMatrix3& b);       // 0x01081DB0
	void sub(const hkMatrix3& m);                              // 0x01081B40
	hkResult invert(hkReal epsilon);                           // 0x01081810
	__forceinline void setDiagonal(hkReal d)
	{
		m_col0.set(d, 0.0f, 0.0f, 0.0f);
		m_col1.set(0.0f, d, 0.0f, 0.0f);
		m_col2.set(0.0f, 0.0f, d, 0.0f);
	}
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

// =====================================================================================================
// hkMouseSpringAction (the mouse-spring joint driven by the editors) and
// hkKeyFrameUtility::AccelerationInfo.  Reconstructed from the binary; no Havok 3.1 source.
// =====================================================================================================
#include <new>

extern "C" double __cdecl sqrt(double);

struct hkStepInfo
{
	hkReal m_startTime;      // +0x0
	hkReal m_invDeltaTime;   // +0x4
	hkReal m_deltaTime;      // +0x8
	hkReal m_endTime;        // +0xc
};

// Allocator interface behind the hkMemory singleton; slot 4 (+0x10) hands out a block.
class hkMemory
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void* allocate(int nbytes, int memClass);   // +0x10
};

extern hkMemory* g_hkMemory;   // 0x016E4178

class hkEntity;
class hkPhantom;

// Motion state of an entity: world transform, mass properties and the velocities an action drives.
class hkRigidMotion
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
	virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
	virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
	virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
	virtual void getInertiaInvWorld(hkMatrix3& out) const;                 // +0x40
	virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void r21();
	virtual void setLinearVelocity(const hkVector4& v);                    // +0x58
	virtual void setAngularVelocity(const hkVector4& v);                   // +0x5c
	virtual void r24();                                                    // +0x60
	virtual void applyImpulse(const hkVector4& impulse, const hkVector4& point);   // +0x64

	uint32_t m_pad04[3];          // +0x04
	hkTransform m_transform;      // +0x10
	hkVector4 m_position;         // +0x60
	uint32_t m_pad70[0x14];       // +0x70
	hkReal m_massInv;             // +0xc0
	uint32_t m_padC4[3];          // +0xc4
	hkVector4 m_linearVelocity;   // +0xd0
	hkVector4 m_angularVelocity;  // +0xe0

	hkReal getMass() const;       // 0x01088270
};

class hkEntity
{
public:
	virtual void e00();
	virtual void e01();
	uint32_t m_pad08[0x15];       // +0x08
	hkRigidMotion* m_motion;      // +0x58

	void activate();                                                              // 0x01088AE0
	void getPointVelocity(const hkVector4& point, hkVector4& velocityOut) const;   // 0x0108CF90
};

// Actions: reference-counted objects with an entity list.
class hkAction : public hkReferencedObject
{
public:
	virtual void a01();
	uint32_t m_pad08[2];          // +0x08
};

class hkUnaryAction : public hkAction
{
public:
	hkUnaryAction(hkEntity* entity = 0, int flags = 0);   // 0x0120B890 (ret 8)
	void removeFromWorld(hkEntity* entity);               // 0x0120B8D0 (ret 4)

	void* m_pUserData;            // +0x10
	uint32_t m_pad14;             // +0x14
	hkEntity* m_entity;           // +0x18
};

class hkMouseSpringAction : public hkUnaryAction
{
public:
	hkMouseSpringAction() {}
	hkMouseSpringAction(hkEntity* body);   // 0x01127850 (ret 4)
	// 0x011278B0 (ret 0x18); the editor call sites reach it as hkMouseSpringAction::Construct
	hkMouseSpringAction(const hkVector4& posInRb, const hkVector4& mousePos, hkReal damping,
	                    hkReal elasticity, hkReal maxForce, hkEntity* body);
	virtual void entityRemovedCallback(hkEntity* entity);                            // 0x01127920
	virtual hkAction* clone(const hkArray<hkEntity*>& entities,
	                        const hkArray<hkPhantom*>& phantoms) const;              // 0x01127970
	virtual void applyAction(const hkStepInfo& stepInfo);                            // 0x01127A10

	hkVector4 m_positionInRb;     // +0x20
	hkVector4 m_mousePosition;    // +0x30
	hkReal m_damping;             // +0x40
	hkReal m_elasticity;          // +0x44
	hkReal m_strength;            // +0x48
	hkReal m_velocityDecay;       // +0x4c
};

// @ 0x01127680
void __cdecl computeShapeVolumeMassProperties(const hkShape* shape, hkReal mass, hkMassProperties* result)
{
	hkMassProperties props;
	hkTransform xform;
	xform.m_rotation.m_col0.set(1.0f, 0.0f, 0.0f, 0.0f);
	xform.m_rotation.m_col1.set(0.0f, 1.0f, 0.0f, 0.0f);
	xform.m_rotation.m_col2.set(0.0f, 0.0f, 1.0f, 0.0f);
	xform.m_translation.setZero4();

	computeShapeMassProperties(shape, &xform, &props);
	if (props.m_volume != 0.0f)
	{
		hkReal scale = mass / props.m_volume;
		props.m_mass = scale * props.m_mass;
		props.m_inertiaTensor.mul(scale);
		*result = props;
	}
}

// @ 0x01127830
void __cdecl constructMouseSpringAction(hkMouseSpringAction* action)
{
	if (action != 0)
		new (action) hkMouseSpringAction();
}

// @ 0x01127850
hkMouseSpringAction::hkMouseSpringAction(hkEntity* body) : hkUnaryAction(body, 0)
{
	m_damping = 0.5f;
	m_elasticity = 0.3f;
	m_strength = 250.0f;
	m_velocityDecay = 0.95f;
	m_positionInRb.setZero4();
	m_mousePosition.setZero4();
}

// @ 0x011278B0
hkMouseSpringAction::hkMouseSpringAction(const hkVector4& posInRb, const hkVector4& mousePos,
                                         hkReal damping, hkReal elasticity, hkReal maxForce, hkEntity* body)
    : hkUnaryAction(body, 0)
{
	m_positionInRb.x = posInRb.x;
	m_positionInRb.y = posInRb.y;
	m_positionInRb.z = posInRb.z;
	m_positionInRb.w = posInRb.w;
	m_mousePosition.x = mousePos.x;
	m_mousePosition.y = mousePos.y;
	m_mousePosition.z = mousePos.z;
	m_mousePosition.w = mousePos.w;
	m_damping = damping;
	m_elasticity = elasticity;
	m_velocityDecay = maxForce;
	m_strength = 250.0f;
}

// @ 0x01127920
void hkMouseSpringAction::entityRemovedCallback(hkEntity* entity)
{
	removeFromWorld(entity);
	m_entity = 0;
}

// @ 0x01127970
hkAction* hkMouseSpringAction::clone(const hkArray<hkEntity*>& entities,
                                     const hkArray<hkPhantom*>& phantoms) const
{
	if (entities.m_size != 1 || phantoms.m_size != 0)
		return 0;

	void* mem = g_hkMemory->allocate(0x50, 0x26);
	((hkReferencedObject*)mem)->m_memSize = 0x50;
	hkMouseSpringAction* spring = new (mem) hkMouseSpringAction(entities.m_data[0]);
	spring->m_positionInRb.x = m_positionInRb.x;
	spring->m_positionInRb.y = m_positionInRb.y;
	spring->m_positionInRb.z = m_positionInRb.z;
	spring->m_positionInRb.w = m_positionInRb.w;
	spring->m_mousePosition.x = m_mousePosition.x;
	spring->m_mousePosition.y = m_mousePosition.y;
	spring->m_mousePosition.z = m_mousePosition.z;
	spring->m_mousePosition.w = m_mousePosition.w;
	spring->m_damping = m_damping;
	spring->m_elasticity = m_elasticity;
	spring->m_strength = m_strength;
	spring->m_velocityDecay = m_velocityDecay;
	spring->m_pUserData = m_pUserData;
	return spring;
}

// @ 0x01127A10
void hkMouseSpringAction::applyAction(const hkStepInfo& stepInfo)
{
	hkEntity* body = m_entity;
	hkRigidMotion* motion = body->m_motion;

	hkVector4 point;
	point.setTransformedPos(motion->m_transform, m_positionInRb);

	hkVector4 offset;
	offset.x = point.x - m_mousePosition.x;
	offset.y = point.y - m_mousePosition.y;
	offset.z = point.z - m_mousePosition.z;
	offset.w = point.w - m_mousePosition.w;

	hkVector4 r;
	r.x = point.x - motion->m_position.x;
	r.y = point.y - motion->m_position.y;
	r.z = point.z - motion->m_position.z;
	r.w = point.w - motion->m_position.w;

	hkMatrix3 skew;
	skew.setCrossSkewSymmetric(r);

	hkMatrix3 inertiaInvWorld;
	motion->getInertiaInvWorld(inertiaInvWorld);

	hkMatrix3 effectiveMass;
	effectiveMass.setDiagonal(motion->m_massInv);

	hkMatrix3 tmp;
	tmp.setMul(skew, inertiaInvWorld);
	hkMatrix3 tmp2;
	tmp2.setMul(tmp, skew);
	effectiveMass.sub(tmp2);

	if (effectiveMass.invert(1.0e-7f) != HK_SUCCESS)
		return;

	hkVector4 linearVelocity;
	linearVelocity.x = motion->m_linearVelocity.x * m_velocityDecay;
	linearVelocity.y = motion->m_linearVelocity.y * m_velocityDecay;
	linearVelocity.z = motion->m_linearVelocity.z * m_velocityDecay;
	linearVelocity.w = motion->m_linearVelocity.w * m_velocityDecay;
	body->activate();
	motion->setLinearVelocity(linearVelocity);

	hkVector4 angularVelocity;
	angularVelocity.x = motion->m_angularVelocity.x * m_velocityDecay;
	angularVelocity.y = motion->m_angularVelocity.y * m_velocityDecay;
	angularVelocity.z = motion->m_angularVelocity.z * m_velocityDecay;
	angularVelocity.w = motion->m_angularVelocity.w * m_velocityDecay;
	body->activate();
	motion->setAngularVelocity(angularVelocity);

	hkVector4 velocity;
	body->getPointVelocity(point, velocity);

	hkReal springRate = m_elasticity * stepInfo.m_endTime;
	hkVector4 force;
	force.x = velocity.x * m_damping + offset.x * springRate;
	force.y = velocity.y * m_damping + offset.y * springRate;
	force.z = velocity.z * m_damping + offset.z * springRate;
	force.w = velocity.w * m_damping + offset.w * springRate;

	hkVector4 impulse;
	impulse.setRotatedDir(effectiveMass, force);
	impulse.x = -impulse.x;
	impulse.y = -impulse.y;
	impulse.z = -impulse.z;
	impulse.w = -impulse.w;

	hkReal maxImpulse = motion->getMass() * m_strength * stepInfo.m_deltaTime;
	hkReal lenSq = impulse.z * impulse.z + impulse.y * impulse.y + impulse.x * impulse.x;
	if (maxImpulse * maxImpulse < lenSq)
	{
		hkReal scale = maxImpulse / (hkReal)sqrt((double)lenSq);
		impulse.x = impulse.x * scale;
		impulse.y = impulse.y * scale;
		impulse.z = impulse.z * scale;
		impulse.w = impulse.w * scale;
	}

	body->activate();
	motion->applyImpulse(impulse, point);
}

// ---------------------------------------------------------------------------------------------------
// hkQuaternion::getAxis / hkKeyFrameUtility::AccelerationInfo
// ---------------------------------------------------------------------------------------------------
class hkQuaternion : public hkVector4
{
public:
	void getAxis(hkVector4& axis) const;   // 0x01127DC0
};

// @ 0x01127DC0
void hkQuaternion::getAxis(hkVector4& axis) const
{
	axis.x = x;
	axis.y = y;
	axis.z = z;
	axis.w = w;

	hkReal len2 = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
	hkReal inv;
	if (len2 != kZero)
		inv = kOne / (hkReal)sqrt((double)len2);
	else
		inv = kZero;

	hkReal nx = inv * axis.x;
	axis.x = nx;
	hkReal ny = inv * axis.y;
	axis.y = ny;
	hkReal nz = inv * axis.z;
	axis.z = nz;
	hkReal nw = inv * axis.w;
	axis.w = nw;

	if (w < kZero)
	{
		axis.x = -nx;
		axis.y = -ny;
		axis.z = -nz;
		axis.w = -nw;
	}
}

struct hkKeyFrameUtility
{
	// Key-frame acceleration state: four 1.0 factors and three (practically unlimited) limits.
	struct AccelerationInfo
	{
		hkVector4 m_linearPositionFactor;    // +0x00
		hkVector4 m_angularPositionFactor;   // +0x10
		hkVector4 m_linearVelocityFactor;    // +0x20
		hkVector4 m_angularVelocityFactor;   // +0x30
		hkReal m_maxLinearAcceleration;      // +0x40
		hkReal m_maxAngularAcceleration;     // +0x44
		hkReal m_maxAllowedDistance;         // +0x48

		AccelerationInfo();                  // 0x01127E90
	};
};

// @ 0x01127E90 -- every factor is 1.0, every limit is HK_REAL_MAX (0x7f7fffee == 3.40282e38f).
hkKeyFrameUtility::AccelerationInfo::AccelerationInfo()
{
	m_linearPositionFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	m_angularPositionFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	m_linearVelocityFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	m_angularVelocityFactor.set(1.0f, 1.0f, 1.0f, 1.0f);
	m_maxLinearAcceleration = 3.40282e38f;
	m_maxAngularAcceleration = 3.40282e38f;
	m_maxAllowedDistance = 3.40282e38f;
}
