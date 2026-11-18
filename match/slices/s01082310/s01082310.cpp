// @ 0x01082310  hkQuaternion::setAxisAngle (Havok 3.1.0 math)
//
// this = (axis * sin(angle/2), cos(angle/2)), built component by component.
// The x87 unit keeps the half angle and sin on its stack: `fld st(0)` before
// fsin keeps the angle for the fcos at the end, and the last component's
// multiply is still performed (and stored) before cos overwrites w.
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sin, cos)

class hkVector4
{
public:
    float x, y, z, w;
};

class hkQuaternion
{
public:
    float m_vec[4];                                 // x y z w

    void setAxisAngle(const hkVector4& axis, float angle);
};

// @ 0x01082310
void hkQuaternion::setAxisAngle(const hkVector4& axis, float angle)
{
    float half = angle * 0.5f;
    double s = sin(half);

    m_vec[0] = (float)(axis.x * s);
    m_vec[1] = (float)(axis.y * s);
    m_vec[2] = (float)(axis.z * s);
    // X87-PRECISION: the binary still multiplies w by sin and stores it here
    // before the cosine overwrites it, so the store must not be folded away.
    *(volatile float*)&m_vec[3] = (float)(axis.w * s);
    m_vec[3] = (float)cos(half);
}
