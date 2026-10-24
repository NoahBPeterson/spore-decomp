// Havok 3.1.0: hkInertiaTensorComputer::computeCylinderVolumeMassProperties (0x01126B40).
// A cylinder is represented as one hkMassElement placed at the midpoint of its axis: the frame
// rotates the canonical Z axis onto (endAxis - startAxis), the volume is pi*r^2*length, and the
// diagonal inertia is (r^2/4 + length^2/12, r^2/4 + length^2/12, r^2/2) scaled by mass.
// Reconstructed from the binary; no Havok 3.1 source is available. Conventions and layouts follow
// match/slices/s01126f80 and the capsule slice.
// Built /vc71 /O2 /MD /Gy /TP (Havok module, x87, no /EHsc).
#include "types.h"
#include <math.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }

struct hkMath
{
	static float acos(float r);   // 0x01082160
	static __forceinline float fabs(float r) { return (float)::fabs((double)r); }
};

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174
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
	T& operator[](int i) { return m_data[i]; }
	__forceinline void setSize(int n)
	{
		if (n > getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_size = n;
	}
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
};

class hkMatrix3
{
public:
	hkVector4 m_col0, m_col1, m_col2;
	void mul(hkReal s);   // 0x01081BB0
	__forceinline void setZero()
	{
		m_col0.setZero4();
		m_col1.setZero4();
		m_col2.setZero4();
	}
	__forceinline void setIdentity()
	{
		m_col0.set(kOne, kZero, kZero, kZero);
		m_col1.set(kZero, kOne, kZero, kZero);
		m_col2.set(kZero, kZero, kOne, kZero);
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
	static hkResult __cdecl combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result);   // 0x011249C0
	static hkResult __cdecl computeCylinderVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
	                                                            hkReal radius, hkReal mass, hkMassProperties& result);
};

extern const hkVector4 hkZAxis;   // 0x015B9B40 = (0,0,1,0)

#define HK_REAL_PI 3.14159265358979f

// @ 0x01126B40
hkResult __cdecl hkInertiaTensorComputer::computeCylinderVolumeMassProperties(const hkVector4& startAxis, const hkVector4& endAxis,
                                                                              hkReal radius, hkReal mass, hkMassProperties& result)
{
	if (mass > kZero)
	{
		if (radius > kZero)
		{
			hkVector4 axis;
			axis.setSub4(endAxis, startAxis);
			const hkReal length = axis.length3();
			if (length > kZero)
			{
				axis.normalize3();

				hkTransform elementTransform;
				const hkReal axisDot = axis.dot3(hkZAxis);
				if (hkMath::fabs(axisDot) >= 0.99999f)
				{
					elementTransform.m_rotation.setIdentity();
				}
				else
				{
					hkVector4 rotAxis;
					rotAxis.setCross(hkZAxis, axis);
					rotAxis.normalize3();

					hkQuaternion q;
					q.setAxisAngle(rotAxis, hkMath::acos(axisDot));
					elementTransform.m_rotation.set(q);
				}

				hkVector4 centre;
				centre.setAdd4(startAxis, endAxis);
				centre.mul4(0.5f);
				elementTransform.m_translation = centre;

				const hkReal volume = length * radius * radius * HK_REAL_PI;

				hkInplaceArray<hkMassElement, 1> elements;
				elements.setSize(1);
				hkMassElement& element = elements[0];
				element.m_transform = elementTransform;

				hkMassProperties& props = element.m_properties;
				props.m_centerOfMass.setZero4();
				props.m_inertiaTensor.setIdentity();
				const hkReal radial = radius * radius * 0.25f;
				const hkReal axial = length * length * 0.25f * (1.0f / 3.0f);
				props.m_inertiaTensor.m_col0.x = radial + axial;
				props.m_inertiaTensor.m_col1.y = radial + axial;
				props.m_inertiaTensor.m_col2.z = radius * radius * 0.5f;
				props.m_inertiaTensor.mul(mass);
				props.m_centerOfMass.setZero4();
				props.m_volume = volume;
				props.m_mass = mass;

				return hkInertiaTensorComputer::combineMassProperties(elements, result);
			}
		}
	}
	return HK_FAILURE;
}
