// Havok 3.1.0: hkInertiaTensorComputer::computeCapsuleVolumeMassProperties (0x01126100).
// A capsule = a cylinder plus two hemispheres. The capsule frame (capsuleToLocal) rotates the canonical Z axis
// onto (endAxis - startAxis) and is centred halfway between the two ends; the cylinder's diagonal inertia and
// each hemisphere's (half a sphere, shifted to its centre of mass 3/8 r from the flat face) become
// hkMassElements that combineMassProperties() merges into `result`.
// No Havok 3.1 source is available; reconstructed from the binary. Names from symbols/havok_names.txt and the
// Havok 6.x header (hkpInertiaTensorComputer.h). Conventions as in match/slices/s0111b170 / s01125560.
// Built /O2 /MD /Gy /TP /fp:fast (Havok module, x87, no /EHsc).
#include "types.h"
#include <math.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

// Havok 3.1 loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }

struct hkMath
{
	static float acos(float r);   // 0x01082160
	static __forceinline float fabs(float r) { return (float)::fabs((double)r); }
};

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory::s_threadMemoryInstance TLS slot)
class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
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

	hkArray(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
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

template <class T, unsigned N>
class hkInplaceArray : public hkArray<T>
{
public:
	__forceinline hkInplaceArray(int size = 0) : hkArray<T>(m_storage, size, N) {}
	T m_storage[N];
};

class __declspec(align(16)) hkVector4
{
public:
	hkReal x, y, z, w;

	__forceinline void set(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
	__forceinline void setZero4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void mul4(hkReal s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	__forceinline void setCross(const hkVector4& a, const hkVector4& b)
	{
		const hkReal nx = a.y * b.z - a.z * b.y;
		const hkReal ny = a.z * b.x - a.x * b.z;
		const hkReal nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	__forceinline hkReal dot3(const hkVector4& a) const { return z * a.z + y * a.y + x * a.x; }
	__forceinline hkReal lengthSquared3() const { return z * z + y * y + x * x; }
	__forceinline hkReal length3() const { return hkMath_sqrt(lengthSquared3()); }
	static __forceinline hkReal invSqrtOrZero(hkReal len2) { return (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2); }
	__forceinline void normalize3() { mul4(invSqrtOrZero(lengthSquared3())); }
	void setRotatedDir(const class hkRotation& r, const hkVector4& v);   // 0x010814A0
};

class hkMatrix3
{
public:
	hkVector4 m_col0, m_col1, m_col2;
	void operator=(const hkMatrix3& m);   // 0x0044A8C0
	void mul(hkReal s);                   // 0x01081BB0
	__forceinline void setZero()
	{
		m_col0.setZero4();
		m_col1.setZero4();
		m_col2.setZero4();
	}
};

class hkQuaternion
{
public:
	hkVector4 m_vec;
	void setAxisAngle(const hkVector4& axis, hkReal angle);   // 0x01082310
};

class hkRotation : public hkMatrix3
{
public:
	void set(const hkQuaternion& q);   // 0x010824A0
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
	void operator=(const hkTransform& t);   // 0x01088410
	__forceinline hkRotation& getRotation() { return m_rotation; }
	__forceinline hkVector4& getTranslation() { return m_translation; }
	__forceinline void setTranslation(const hkVector4& t) { m_translation = t; }
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
	static hkResult __cdecl computeSphereVolumeMassProperties(hkReal radius, hkReal sphereMass, hkMassProperties& result);   // 0x01124060
	static void __cdecl shiftInertiaToCom(hkVector4& shift, hkReal mass, hkMatrix3& inertia);                                // 0x011241E0
	static hkResult __cdecl combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result);          // 0x011249C0
	static hkResult __cdecl computeCapsuleVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
	                                                           hkReal radius, hkReal mass, hkMassProperties& result);
};

#define HK_REAL_PI 3.14159265358979f

// @ 0x01126100
hkResult __cdecl hkInertiaTensorComputer::computeCapsuleVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
                                                                             hkReal radius, hkReal mass, hkMassProperties& result)
{
	if (mass <= kZero)
		return HK_FAILURE;
	if (radius <= kZero)
		return HK_FAILURE;

	// The capsule frame: canonical Z rotated onto the axis, centred between the ends.
	hkVector4 axis;
	axis.setSub4(endAxis, startAxis);
	const hkReal height = axis.length3();

	hkTransform capsuleToLocal;
	if (height > kZero)
	{
		axis.normalize3();

		hkVector4 canonicalZ;
		canonicalZ.set(kZero, kZero, kOne, kZero);
		const hkReal axisDot = axis.dot3(canonicalZ);
		if (hkMath::fabs(axisDot) < 1.0f - 1e-5f)
		{
			hkVector4 rotAxis;
			rotAxis.setCross(canonicalZ, axis);
			rotAxis.normalize3();

			hkQuaternion q;
			q.setAxisAngle(rotAxis, hkMath::acos(axisDot));
			capsuleToLocal.getRotation().set(q);
		}
		else
		{
			capsuleToLocal.getRotation().setIdentity();
		}
	}
	else
	{
		capsuleToLocal.getRotation().setIdentity();
	}

	{
		hkVector4 centre;
		centre.setAdd4(startAxis, endAxis);
		centre.mul4(0.5f);
		capsuleToLocal.setTranslation(centre);
	}

	// Volumes and the mass split between the cylinder and the two hemispheres.
	const hkReal radius2 = radius * radius;
	const hkReal sphereVolume = radius2 * radius * (4.0f / 3.0f * HK_REAL_PI);
	const hkReal cylinderVolume = height * radius * radius * HK_REAL_PI;
	const hkReal invTotalVolume = 1.0f / (cylinderVolume + sphereVolume);
	const hkReal sphereMass = sphereVolume * invTotalVolume * mass;
	const hkReal cylinderMass = invTotalVolume * cylinderVolume * mass;

	hkInplaceArray<hkMassElement, 3> elements;

	// Cylinder (along local Z)
	{
		hkMassElement cylinderElement;
		cylinderElement.m_transform = capsuleToLocal;
		hkMassProperties& props = cylinderElement.m_properties;
		props.m_centerOfMass.setZero4();
		hkMatrix3& inertia = props.m_inertiaTensor;
		inertia.m_col0.set(radius2 * 0.25f + height * height * 0.25f * (1.0f / 3.0f), 0.0f, 0.0f, 0.0f);
		inertia.m_col1.set(0.0f, inertia.m_col0.x, 0.0f, 0.0f);
		inertia.m_col2.set(0.0f, 0.0f, radius2 * 0.5f, 0.0f);
		inertia.mul(cylinderMass);
		props.m_mass = cylinderMass;
		props.m_centerOfMass.setZero4();
		props.m_volume = cylinderVolume;
		elements.pushBack(cylinderElement);
	}

	const hkReal halfHeight = height * 0.5f;
	const hkReal hemisphereMass = sphereMass * 0.5f;
	const hkReal hemisphereVolume = sphereVolume * 0.5f;

	// Hemisphere at the end (+Z)
	{
		hkMassElement hemisphereElement;
		hemisphereElement.m_transform = capsuleToLocal;
		hkVector4 shift;
		shift.set(0.0f, 0.0f, halfHeight, 0.0f);
		shift.setRotatedDir(capsuleToLocal.getRotation(), shift);
		shift.setAdd4(hemisphereElement.m_transform.getTranslation(), shift);
		hemisphereElement.m_transform.setTranslation(shift);

		hkMassProperties& props = hemisphereElement.m_properties;
		props.m_centerOfMass.set(0.0f, 0.0f, radius * 0.375f, 0.0f);
		hkMassProperties sphereProps;
		computeSphereVolumeMassProperties(radius, sphereMass, sphereProps);
		props.m_inertiaTensor = sphereProps.m_inertiaTensor;
		props.m_inertiaTensor.mul(0.5f);
		shiftInertiaToCom(props.m_centerOfMass, hemisphereMass, props.m_inertiaTensor);
		props.m_mass = hemisphereMass;
		props.m_volume = hemisphereVolume;
		elements.pushBack(hemisphereElement);
	}

	// Hemisphere at the start (-Z)
	{
		hkMassElement hemisphereElement;
		hemisphereElement.m_transform = capsuleToLocal;
		hkVector4 shift;
		shift.set(0.0f, 0.0f, -halfHeight, 0.0f);
		shift.setRotatedDir(capsuleToLocal.getRotation(), shift);
		shift.setAdd4(hemisphereElement.m_transform.getTranslation(), shift);
		hemisphereElement.m_transform.setTranslation(shift);

		hkMassProperties& props = hemisphereElement.m_properties;
		props.m_centerOfMass.set(0.0f, 0.0f, radius * -0.375f, 0.0f);
		hkMassProperties sphereProps;
		computeSphereVolumeMassProperties(radius, sphereMass, sphereProps);
		props.m_inertiaTensor = sphereProps.m_inertiaTensor;
		props.m_inertiaTensor.mul(0.5f);
		shiftInertiaToCom(props.m_centerOfMass, hemisphereMass, props.m_inertiaTensor);
		props.m_mass = hemisphereMass;
		props.m_volume = hemisphereVolume;
		elements.pushBack(hemisphereElement);
	}

	combineMassProperties(elements, result);
	return HK_SUCCESS;
}
