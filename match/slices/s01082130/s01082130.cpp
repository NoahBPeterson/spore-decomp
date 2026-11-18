// Havok 3.1.0 math: hkMatrix3::changeBasis (base change: this = r * this * inverse(r)).
// Two out-of-line calls; the single hkMatrix3 temporary is 16-byte aligned, which is why the
// function aligns the frame (and esp,-16) and reserves 0x38 bytes for the 48-byte temporary.
#include "types.h"

class hkRotation;

class __declspec(align(16)) hkMatrix3
{ public:
	float m_el[12];                                            // three hkVector4 columns (col*4 + row)
	void setMul(const hkMatrix3& a, const hkMatrix3& b);       // 0x01081DB0
	void changeBasis(const hkRotation& r);                     // 0x01082130
};

class hkRotation : public hkMatrix3
{ public:
	void setMulInverse(const hkMatrix3& a, const hkRotation& b);   // 0x01081F20
};

// @ 0x01082130
void hkMatrix3::changeBasis(const hkRotation& r)
{
	// tmp = this * inverse(r); then this = r * tmp
	hkRotation tmp;
	tmp.setMulInverse(*this, r);
	setMul(r, tmp);
}
