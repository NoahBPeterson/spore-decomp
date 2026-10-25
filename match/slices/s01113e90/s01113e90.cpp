// Slice s01113e90: Havok contact-point generation helpers (body pair / triangle).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

class hkVector4
{
public:
    __declspec(align(16)) float x;
    float y, z, w;

    void setTransformedPos(const class hkTransform& t, const hkVector4& p);     // 0x01081360
    void setRotatedInverseDir(const class hkRotation& r, const hkVector4& v);   // 0x01081440
};

class __declspec(align(16)) hkMatrix3
{
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;
};

class hkRotation : public hkMatrix3
{
};

class hkTransform
{
public:
    hkRotation m_rotation;      // 0x00
    hkVector4   m_translation;  // 0x30
};

// Shape/body interface: only the slots this file dispatches through are named.
class hkBody
{
public:
    virtual void vt00();
    virtual void vt04();
    virtual void vt08();
    virtual void vt0c();
    virtual void vt10();
    virtual void vt14();
    virtual void vt18();
    virtual void vt1c();
    virtual void vt20();
    virtual void vt24(hkVector4& dir, hkVector4& out);
    virtual void vt28();
    virtual void vt2c(hkVector4& out);
    virtual uint8_t vt30();
};

// 12-byte feature pair written into the contact point record.
struct hkContactFeaturePair
{
    uint16_t m_featureA;    // +0x0
    uint16_t m_featureB;    // +0x2
    uint16_t m_indexA;      // +0x4
    uint16_t m_indexB;      // +0x6
    uint8_t  m_typeA;       // +0x8
    uint8_t  m_typeB;       // +0x9
    uint8_t  m_idA;         // +0xa
    uint8_t  m_idB;         // +0xb

    void buildFromBodyPair(hkBody* bodyA, hkBody* bodyB, const hkTransform* xform);
    void buildFromTriangle(hkBody* body, const void* triangle, const hkTransform* xform);
};

// Triangle whose three vertices live at +0x10/+0x20/+0x30.
struct hkContactTriangle
{
    uint8_t   m_pad[0x10];  // +0x00
    hkVector4 m_v0;         // +0x10
    hkVector4 m_v1;         // +0x20
    hkVector4 m_v2;         // +0x30
};

// 0x34-byte contact record copied verbatim.
struct hkCollisionContact
{
    int m00;    // +0x00
    int m04;    // +0x04
    int m08;    // +0x08
    int m0c;    // +0x0c
    int m10;    // +0x10
    int m14;    // +0x14
    int m18;    // +0x18
    int m1c;    // +0x1c
    int m20;    // +0x20
    int m24;    // +0x24
    int m28;    // +0x28
    int m2c;    // +0x2c
    int m30;    // +0x30

    hkCollisionContact* assign(const hkCollisionContact* other);
};

// @ 0x01113e90  hkContactFeaturePair::buildFromBodyPair
void hkContactFeaturePair::buildFromBodyPair(hkBody* bodyA, hkBody* bodyB,
                                             const hkTransform* xform)
{
    hkVector4 posA;
    hkVector4 posB;
    hkVector4 pos;
    hkVector4 dir;
    hkVector4 cpA;
    hkVector4 cpB;
    hkVector4 rot;

    bodyA->vt2c(posA);
    bodyB->vt2c(posB);
    pos.setTransformedPos(*xform, posB);

    dir.x = pos.x - posA.x;
    dir.y = pos.y - posA.y;
    dir.z = pos.z - posA.z;
    dir.w = pos.w - posA.w;
    bodyA->vt24(dir, cpA);

    m_featureA = *(const uint16_t*)&cpA.w;

    dir.x = pos.x - cpA.x;
    dir.y = pos.y - cpA.y;
    dir.z = pos.z - cpA.z;
    dir.w = pos.w - cpA.w;
    rot.setRotatedInverseDir(xform->m_rotation, dir);
    rot.x = -rot.x;
    rot.y = -rot.y;
    rot.z = -rot.z;
    rot.w = -rot.w;
    bodyB->vt24(rot, cpB);

    m_featureB = *(const uint16_t*)&cpB.w;
    m_indexA = 0xffff;
    m_indexB = 0xffff;
    m_typeA = 1;
    m_typeB = 1;
    m_idA = bodyA->vt30();
    m_idB = bodyB->vt30();
}

// @ 0x01113fd0  hkContactFeaturePair::buildFromTriangle
void hkContactFeaturePair::buildFromTriangle(hkBody* body, const void* triangle,
                                             const hkTransform* xform)
{
    const hkContactTriangle* tri = (const hkContactTriangle*)triangle;

    m_featureB = 0;
    m_indexA = 0x10;
    m_indexB = 0x20;

    hkVector4 v0;
    hkVector4 v1;
    hkVector4 v2;
    v0.setTransformedPos(*xform, tri->m_v0);
    v1.setTransformedPos(*xform, tri->m_v1);
    v2.setTransformedPos(*xform, tri->m_v2);

    hkVector4 e1;
    hkVector4 e2;
    e1.x = v1.x - v0.x;
    e1.y = v1.y - v0.y;
    e1.z = v1.z - v0.z;
    e1.w = v1.w - v0.w;
    e2.x = v2.x - v1.x;
    e2.y = v2.y - v1.y;
    e2.z = v2.z - v1.z;
    e2.w = v2.w - v1.w;

    hkVector4 normal;
    normal.x = e1.y * e2.z - e2.y * e1.z;
    normal.y = e1.z * e2.x - e2.z * e1.x;
    normal.z = e2.y * e1.x - e1.y * e2.x;
    normal.w = 0.0f;

    hkVector4 bodyPos;
    body->vt2c(bodyPos);
    float dx = bodyPos.x - v0.x;
    float dy = bodyPos.y - v0.y;
    float dz = bodyPos.z - v0.z;
    if (normal.x * dx + (normal.y * dy + normal.z * dz) < 0.0f)
    {
        normal.x = -normal.x;
        normal.y = -normal.y;
        normal.z = -normal.z;
        normal.w = -normal.w;
    }

    hkVector4 out;
    body->vt24(normal, out);

    m_featureA = *(const uint16_t*)&out.w;
    m_typeA = 1;
    m_typeB = 3;
    m_idA = body->vt30();
    m_idB = 3;
}

// @ 0x01114310  hkCollisionContact::assign
hkCollisionContact* hkCollisionContact::assign(const hkCollisionContact* other)
{
    m00 = other->m00;
    m04 = other->m04;
    m08 = other->m08;
    m0c = other->m0c;
    m10 = other->m10;
    m14 = other->m14;
    m18 = other->m18;
    m1c = other->m1c;
    m20 = other->m20;
    m24 = other->m24;
    m28 = other->m28;
    m2c = other->m2c;
    m30 = other->m30;
    return this;
}
