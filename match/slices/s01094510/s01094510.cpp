// Slice s01094510: hkPointToPathConstraintData::buildJacobian (Havok 3.1.0, 0x01094510, 1666 bytes).
// Flags: /vc71 /O2 /MD /Gy /TP /fp:fast  (cl 13.10 ignores /fp:fast; the VS2008 equivalence tester needs it for inline fsqrt)
//
// Layout: match/include/havok31/hkReflectedClasses.h (hkPointToPathConstraintData, 0xa0 bytes:
// m_path +0x0c, max friction +0x10, angular DOF mode +0x14, m_transform_OS_KS[2] at +0x20 / +0x60).
// The info structs of the hk1d* jacobian builders and the hkParametricCurve virtuals were read off the asm.
//
// Steps: frame 0 (body A * OS_KS[0]) and frame 1 (body B * OS_KS[1]) in world; pivot (frame 0 origin)
// in the path's space; nearest point on the path (runtime stores its parameter at +0x38); the path
// tangent and a perpendicular to it; optional linear friction row; two linear bilateral rows (perp
// and tangent x perp) pulling frame 0's origin onto the path; angular rows depending on the DOF mode
// (>1: two rows, 3: a third, tied to the path's binormal); a linear limit unless the path is closed.
#include "types.h"

typedef float hkReal;
typedef double hkX87Real;   // value the original keeps on the x87 stack (never stored)
// A float stack slot written and read back (rounds to float even under /fp:fast).
__forceinline float hkStoreF(hkX87Real v) { volatile float f = (float)v; return f; }

extern const float kZero;   // 0x01485378

class hkBool
{
public:
	char m_b;
	hkBool(bool b) : m_b(b) {}
	operator bool() const { return m_b != 0; }
};

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
	float& operator[](int i) { return (&x)[i]; }
	const float& operator[](int i) const { return (&x)[i]; }

	void setTransformedPos(const class hkTransform& t, const hkVector4& v);          // 0x01081360
	void setTransformedInversePos(const class hkTransform& t, const hkVector4& v);   // 0x010813d0
	void setRotatedDir(const struct hkRotation& r, const hkVector4& v);               // 0x010814a0
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};
class hkRotation : public hkMatrix3 {};

class hkTransform
{ public:
	hkRotation m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
	void setMul(const hkTransform& a, const hkTransform& b);   // 0x01080ef0
};

class hkSolverResults
{ public:
	hkReal m_impulseApplied;
	hkReal m_internalSolverData;
};

class hkConstraintQueryIn
{
public:
	float m_pad0[12];
	hkTransform* m_transformA;           // +0x30
	hkTransform* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	hkSolverResults* m_constraintRuntime;   // +0x44
};

class hkConstraintQueryOut
{
public:
	void* m_jacobians;
	void* m_jacobianSchemas;
};

struct hk1dLinearFrictionInfo
{
	hkVector4 m_pivot;                       // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkReal m_maxFrictionForce;               // +0x20
	hkSolverResults* m_lastSolverResults;    // +0x24
};

struct hk1dAngularBilateralConstraintInfo
{
	hkVector4 m_zeroErrorAxisAinW;           // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkVector4 m_perpZeroErrorAxisBinW;       // +0x20
};

struct hk1dLinearBilateralConstraintInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
};

struct hk1dLinearLimitInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
	hkReal m_min;                            // +0x30
	hkReal m_max;                            // +0x34
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dLinearFrictionBuildJacobian(const hk1dLinearFrictionInfo& info, const hkConstraintQueryIn& in,
                                                hkConstraintQueryOut& out);                               // 0x010AA5F0
extern "C" void hk1dAngularBilateralConstraintBuildJacobian(const hk1dAngularBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);                   // 0x010AA1E0
extern "C" void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                           const hkConstraintQueryIn& in,
                                                           hkConstraintQueryOut& out);                    // 0x010AA890
extern "C" void hk1dLinearLimitBuildJacobian(const hk1dLinearLimitInfo& info, const hkConstraintQueryIn& in,
                                             hkConstraintQueryOut& out);                                  // 0x010AAE10

extern const float kOne;   // 0x01485720
#include <math.h>
#define hkAbs(x) ((float)fabs((double)(x)))
#define hkSqrt(x) ((float)sqrt((double)(x)))

class hkParametricCurve
{
public:
	virtual ~hkParametricCurve();                                                         // +0x00
	virtual void vslot1();                                                                // +0x04
	virtual void vslot2();                                                                // +0x08
	virtual hkReal getNearestPoint(hkReal t0, const hkVector4& pos, hkVector4& out);      // +0x0c (in place)
	virtual void getPoint(hkReal t, hkVector4& out);                                      // +0x10
	virtual hkReal getStart();                                                            // +0x14
	virtual hkReal getEnd();                                                              // +0x18
	virtual hkReal getLength(hkReal t);                                                   // +0x1c
	virtual void getBinormal(hkReal t, hkVector4& out);                                   // +0x20
	virtual hkBool isClosed();                                                            // +0x24
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkPointToPathConstraintData : public hkConstraintData
{
public:
	hkParametricCurve* m_path;           // +0x0c
	hkReal m_maxFrictionForce;           // +0x10
	signed char m_angularConstrainedDOF; // +0x14 (1 none, 2 allow spin, 3 to path)
	char m_pad15[0x0b];
	hkTransform m_transform_OS_KS[2];    // +0x20 / +0x60

	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x01094510
void hkPointToPathConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, in.m_constraintRuntime, 8);

	hkTransform frame1;   // body B * OS_KS[1]: the path's frame
	frame1.setMul(*in.m_transformB, m_transform_OS_KS[1]);
	hkTransform frame0;   // body A * OS_KS[0]
	frame0.setMul(*in.m_transformA, m_transform_OS_KS[0]);

	hkSolverResults* runtime = in.m_constraintRuntime;
	hkReal* pathParam = &((hkReal*)runtime)[14];   // runtime +0x38: parameter of the nearest point
	hkVector4 v;
	v.setTransformedInversePos(frame1, frame0.m_translation);
	*pathParam = m_path->getNearestPoint(*pathParam, v, v);
	hkVector4 pointW;
	pointW.setTransformedPos(frame1, v);
	m_path->getPoint(*pathParam, v);
	hkVector4 tangent;
	tangent.setRotatedDir(frame1.m_rotation, v);

	// perpendicular to the tangent: zero its smallest component, swap-negate the other two
	hkVector4 perp;
	{
		const float a0 = hkAbs(tangent.x), a1 = hkAbs(tangent.y), a2 = hkAbs(tangent.z);
		int other = 1, mn = 0;
		float least = a0;
		if (a1 < a0) { other = 0; mn = 1; least = a1; }
		int big, small;
		if (a2 < least) { big = mn; small = 2; } else { big = 2; small = mn; }
		perp[small] = 0.0f;
		perp[3] = 0.0f;
		perp[other] = tangent[big];
		perp[big] = -tangent[other];
		const hkX87Real len2 = ((hkX87Real)perp.z * perp.z + (hkX87Real)perp.y * perp.y) + (hkX87Real)perp.x * perp.x;
		hkX87Real inv;
		if (len2 == kZero) inv = kZero; else inv = kOne / sqrt(len2);
		perp.x = hkStoreF(perp.x * inv);
		perp.y = hkStoreF(perp.y * inv);
		perp.z = hkStoreF(perp.z * inv);
		perp.w = hkStoreF(perp.w * inv);
	}
	// v = tangent x perp
	v.x = perp.z * tangent.y - perp.y * tangent.z;
	v.y = tangent.z * perp.x - perp.z * tangent.x;
	v.z = perp.y * tangent.x - tangent.y * perp.x;

	// pivot on the path's far end side: frame0 origin - length * tangent
	const hkX87Real len = -(hkX87Real)m_path->getLength(*pathParam);
	hkVector4 pivot;
	pivot.x = (float)(tangent.x * len + frame0.m_translation.x);
	pivot.y = (float)(tangent.y * len + frame0.m_translation.y);
	pivot.z = (float)(tangent.z * len + frame0.m_translation.z);
	pivot.w = (float)(tangent.w * len + frame0.m_translation.w);

	if (m_maxFrictionForce > kZero) {
		hk1dLinearFrictionInfo friction;
		friction.m_pivot = pivot;
		friction.m_constrainedDofW = tangent;
		friction.m_maxFrictionForce = m_maxFrictionForce;
		friction.m_lastSolverResults = runtime;
		hk1dLinearFrictionBuildJacobian(friction, in, out);
	}

	{
		hk1dLinearBilateralConstraintInfo lin;
		lin.m_pivotA = frame0.m_translation;
		lin.m_pivotB = pointW;
		lin.m_constrainedDofW = perp;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
		lin.m_constrainedDofW.x = v.x;
		lin.m_constrainedDofW.y = v.y;
		lin.m_constrainedDofW.z = v.z;
		lin.m_constrainedDofW.w = 0.0f;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
	}

	if (m_angularConstrainedDOF > 1) {
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = tangent;
		ang.m_constrainedDofW = frame0.m_rotation.m_col[1];
		ang.m_perpZeroErrorAxisBinW = frame0.m_rotation.m_col[2];
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);

		ang.m_constrainedDofW.x = -frame0.m_rotation.m_col[2].x;
		ang.m_constrainedDofW.y = -frame0.m_rotation.m_col[2].y;
		ang.m_constrainedDofW.z = -frame0.m_rotation.m_col[2].z;
		ang.m_constrainedDofW.w = -frame0.m_rotation.m_col[2].w;
		ang.m_perpZeroErrorAxisBinW = frame0.m_rotation.m_col[1];
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);

		if (m_angularConstrainedDOF == 3) {
			m_path->getBinormal(*pathParam, perp);
			hkVector4 binormalW;
			binormalW.setRotatedDir(frame1.m_rotation, perp);
			ang.m_zeroErrorAxisAinW = frame0.m_rotation.m_col[2];
			ang.m_constrainedDofW = frame0.m_rotation.m_col[0];
			ang.m_perpZeroErrorAxisBinW.x = -binormalW.x;
			ang.m_perpZeroErrorAxisBinW.y = -binormalW.y;
			ang.m_perpZeroErrorAxisBinW.z = -binormalW.z;
			ang.m_perpZeroErrorAxisBinW.w = -binormalW.w;
			hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
		}
	}

	if (!m_path->isClosed()) {
		hk1dLinearLimitInfo limit;
		limit.m_pivotA = frame0.m_translation;
		limit.m_pivotB = pivot;
		limit.m_constrainedDofW = tangent;
		limit.m_min = m_path->getLength(m_path->getStart());
		limit.m_max = m_path->getLength(m_path->getEnd());
		hk1dLinearLimitBuildJacobian(limit, in, out);
	}
}

// ---------------------------------------------------------------------------
// Curve / stream-proxy / array-container classes reached from this slice.

struct cArrayRef
{
	void** m_data;                 // +0x00
	int    m_size;                 // +0x04
	int    m_capacityAndFlags;     // +0x08
};

struct cRefObj
{
	virtual void Release(int flags);   // +0x00
	unsigned short m_memSize;          // +0x04
	short m_refCount;                  // +0x06
};

struct cCurveElem
{
	void Release();                    // 0x0109ae60
};

class cHeap
{
public:
	void Dealloc(void* p, int nBytes, int tag);   // 0x0107db10
};

struct cDeallocator
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void Dealloc(void* p, int nBytes, int tag);   // +0x14
};

extern cDeallocator* gDeallocator;    // 0x016e4178
extern void* gAllocator;              // 0x016e4174
typedef void* (__stdcall* cGetHeapFn)(void*);
extern cGetHeapFn gGetHeap;           // 0x013cc2bc (function-pointer variable)

class cCurveContainer
{
public:
	void* mpVtbl;              // +0x00
	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	cArrayRef m_arrays[4];     // +0x08 / +0x14 / +0x20 / +0x2c

	void Destroy();            // 0x01094bc0
};

class cStream : public cRefObj
{
public:
	virtual void v04();
	virtual void* v08(void* arg);         // +0x08
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c(void* a, void* b);   // +0x1c
	virtual void v20(void* s);            // +0x20
};

struct cCmdState
{
	unsigned int m00;
	unsigned int m04;
	unsigned int m08;
	unsigned int m0c;
};

struct cBlob48
{
	float m00, m04, m08, m0c, m10, m14;
	float m18;
	float m1c, m20, m24, m28, m2c, m30, m34, m38, m3c, m40, m44;
};

class cStreamProxy
{
public:
	void* mpVtbl;              // +0x00
	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	unsigned int m08;          // +0x08
	cStream* mpStream;         // +0x0c
	float m_scale;             // +0x10

	void To20(cCmdState* s);              // 0x01094d50
	void To1c(cBlob48* src, void* arg);   // 0x01094d90
	void* To08(void* arg);                // 0x01094dd0
	void* Destroy(int flags);             // 0x01094e10
};

class cKeyFrameCurve
{
public:
	virtual void v00();                                   // +0x00
	virtual void v04();                                   // +0x04
	virtual void v08();                                   // +0x08
	virtual hkReal NearestPoint(hkReal t, const hkVector4& pos, hkVector4& out);  // +0x0c

	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	unsigned int m08;          // +0x08
	unsigned char m_closed;    // +0x0c
	char m0d[3];               // +0x0d
	float m10;                 // +0x10
	char m14[0x0c];            // +0x14
	hkVector4* m_keys;         // +0x20
	int m_keyCount;            // +0x24

	char* IsClosed(char* out);                                            // 0x01094e60
	void GetPoint(hkReal t, hkVector4& out);                              // 0x01094e80
};

extern "C" int CurveIndex(hkReal t);   // 0x0120ad30

// @ 0x01094bc0
void cCurveContainer::Destroy()
{
	this->mpVtbl = (void*)0x014a1b88;
	int i;
	int n = this->m_arrays[0].m_size;
	for (i = 0; i < n; ++i)
		((cCurveElem*)this->m_arrays[0].m_data[i])->Release();
	n = this->m_arrays[3].m_size;
	for (i = 0; i < n; ++i)
		((cCurveElem*)this->m_arrays[3].m_data[i])->Release();
	n = this->m_arrays[1].m_size;
	for (i = 0; i < n; ++i) {
		cRefObj* p = (cRefObj*)this->m_arrays[1].m_data[i];
		if (p->m_memSize != 0) {
			if (--p->m_refCount == 0)
				p->Release(1);
		}
	}
	n = this->m_arrays[2].m_size;
	for (i = 0; i < n; ++i) {
		cRefObj* p = (cRefObj*)this->m_arrays[2].m_data[i];
		if (p != 0) {
			if (p->m_memSize != 0) {
				if (--p->m_refCount == 0)
					p->Release(1);
			}
		}
	}

	cGetHeapFn getHeap = gGetHeap;
	int mask = (int)0x80000000;
	int flags = this->m_arrays[3].m_capacityAndFlags;
	if (!(flags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[3].m_data,
		              (this->m_arrays[3].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[2].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[2].m_data,
		              (this->m_arrays[2].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[1].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[1].m_data,
		              (this->m_arrays[1].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[0].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[0].m_data,
		              (this->m_arrays[0].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	this->mpVtbl = (void*)0x013ef094;
}

// @ 0x01094d50
void cStreamProxy::To20(cCmdState* s)
{
	this->mpStream->v20(s);
	s->m08 += 0x40;
	s->m0c += 2;
}

// @ 0x01094d90
void cStreamProxy::To1c(cBlob48* src, void* arg)
{
	cBlob48 local = *src;
	local.m18 = local.m18 * this->m_scale;
	this->mpStream->v1c(&local, arg);
}

// @ 0x01094dd0
void* cStreamProxy::To08(void* arg)
{
	this->mpStream->v08(arg);
	return arg;
}

// @ 0x01094e10
void* cStreamProxy::Destroy(int flags)
{
	cRefObj* p = (cRefObj*)this->mpStream;
	this->mpVtbl = (void*)0x014a1b90;
	if (p->m_memSize != 0) {
		if (--p->m_refCount == 0)
			p->Release(1);
	}
	this->mpVtbl = (void*)0x013ef094;
	if (flags & 1)
		gDeallocator->Dealloc(this, this->m_memSize, 0x29);
	return this;
}

// @ 0x01094e60
char* cKeyFrameCurve::IsClosed(char* out)
{
	*out = (char)this->m_closed;
	return out;
}

// @ 0x01094e80
void cKeyFrameCurve::GetPoint(hkReal t, hkVector4& out)
{
	int idx;
	if (t < kZero)
		idx = 0;
	else
		idx = CurveIndex(t);
	if (idx + 1 < this->m_keyCount) {
		int i1 = idx + 1;
		hkReal frac = t - (hkReal)idx;
		hkReal u = 1 - frac;
		const hkVector4& a = this->m_keys[idx];
		const hkVector4& b = this->m_keys[i1];
		out.x = u * a.x + frac * b.x;
		out.y = u * a.y + frac * b.y;
		out.z = u * a.z + frac * b.z;
		out.w = u * a.w + frac * b.w;
	} else {
		out = this->m_keys[idx];
	}
}

// @ 0x01094f40
hkReal cKeyFrameCurve::NearestPoint(hkReal t, const hkVector4& pos, hkVector4& out)
{
	if (t < kZero)
		t = 0;
	int idx = CurveIndex(t);
	int count = this->m_keyCount;
	int i1 = idx + 1;
	int i0 = idx;
	if (i1 >= count) {
		i1 = count - 1;
		i0 = i1 - 1;
	}
	int nxt = i1 + 1;
	hkVector4* keys = this->m_keys;
	hkReal u = 0;
	for (;;) {
		hkVector4 D;
		D.x = keys[i1].x - keys[i0].x;
		D.y = keys[i1].y - keys[i0].y;
		D.z = keys[i1].z - keys[i0].z;
		hkReal ex = pos.x - keys[i0].x;
		hkReal ey = pos.y - keys[i0].y;
		hkReal ez = pos.z - keys[i0].z;
		hkReal dot = ez * D.z + ey * D.y + ex * D.x;
		hkReal den = D.z * D.z + D.y * D.y + D.x * D.x;
		u = dot / den;
		if (u < kZero) {
			if (i0 == 0)
				break;
			--i0;
			--i1;
			--nxt;
			continue;
		}
		hkReal fx = pos.x - keys[i1].x;
		hkReal fy = pos.y - keys[i1].y;
		hkReal fz = pos.z - keys[i1].z;
		hkReal dot2 = fz * D.z + fy * D.y + fx * D.x;
		if (dot2 <= kZero)
			break;
		if (nxt >= count)
			break;
		hkVector4 D2;
		D2.x = keys[nxt].x - keys[i1].x;
		D2.y = keys[nxt].y - keys[i1].y;
		D2.z = keys[nxt].z - keys[i1].z;
		hkReal dot3 = fz * D2.z + fy * D2.y + fx * D2.x;
		if (dot3 > kZero) {
			++i0;
			++i1;
			++nxt;
			continue;
		}
		hkReal len1 = D.z * D.z + D.y * D.y + D.x * D.x;
		hkReal inv1 = (len1 == 0) ? 0 : 1 / hkSqrt(len1);
		hkReal len2 = D2.z * D2.z + D2.y * D2.y + D2.x * D2.x;
		hkReal inv2 = (len2 == 0) ? 0 : 1 / hkSqrt(len2);
		hkReal side = (fz * (D.z * inv1) + fy * (D.y * inv1) + fx * (D.x * inv1))
		            + (fz * (D2.z * inv2) + fy * (D2.y * inv2) + fx * (D2.x * inv2));
		if (side >= 0) {
			++i0;
			++i1;
			u = 0.01f;
		} else {
			u = 0.99f;
		}
		break;
	}

	hkReal param = (hkReal)i0 + u;
	if (param == kZero)
		param = kZero;
	hkReal v = 1 - u;
	const hkVector4& a = keys[i0];
	const hkVector4& b = keys[i1];
	out.x = v * a.x + u * b.x;
	out.y = v * a.y + u * b.y;
	out.z = v * a.z + u * b.z;
	out.w = v * a.w + u * b.w;

	if (this->m_closed) {
		hkReal last = (hkReal)(this->m_keyCount - 1);
		if (param < 0.25f)
			return this->NearestPoint(last - (1 - param), pos, out);
		if (param > last - 0.25f)
			return this->NearestPoint(1 - (last - param), pos, out);
	}
	return param;
}
