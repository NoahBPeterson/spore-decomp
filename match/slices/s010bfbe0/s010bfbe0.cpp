// Havok 3.1.0 slice s010bfbe0 (0x010BFBE0..0x010C0AF0): the licence/keycode check, _hkSolverGetSystemTime,
// hkConvexTranslateShape, hkAabbUtil::calcAabb and the first half of hkBoxShape.
// Functionally equivalent portable source (not byte exact). 32-bit layout comments throughout.
// Float math: hkConvexTranslateShape::getMaximumProjection / getAabb / castRay, hkAabbUtil::calcAabb,
// hkBoxShape ctor / getSupportingVertex / convertVertexIdsToVertices / getCollisionSpheres.
// Values the asm keeps on the x87 stack without storing are typed hkX87Real and marked "X87-PRECISION".
// No inline fsqrt/fsin/fcos here (only fabs/fchs).
#include "s010bfbe0.h"
#include <string.h>
#include <time.h>
#include <math.h>

// ---- externals ------------------------------------------------------------------------------------------------------
void hkErrorMessage(const char* msg);                    // 0x0107EDB0 (cdecl)
extern const hkUint32 g_hkKeycodeSeeds[3];               // 0x014A24A4 : 72e6ef51 6e453245 4caea74a
extern char g_hkKeycodeString[];                         // 0x013F8B98 : "CLIENT.Ph.Spore"
extern hkUint32 g_hkKeycodeHash;                         // 0x013F8BA8 : 0x731521CF (bit 31 = time-limited key)
extern const char* const g_hkComponentNames[];           // 0x015BA0D8 : "Constraint Solver", "Ragdoll Technology", "Vehicles", ...

class hkStatisticsCollector
{
public:
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);                                     // 1 (+4)
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // 2 (+8)
    virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // 3 (+0xc)
    virtual void s4(); virtual void s5();
    virtual void endObject();                                                                                  // 6 (+0x18)
};

struct hkAabb { hkVector4 m_min; hkVector4 m_max; };                        // 0x20
struct hkCdVertex : public hkVector4 {};                                     // 0x10
struct hkSphere { hkVector4 m_pos; };                                        // 0x10
struct hkCollisionSpheresInfo { int m_numSpheres; bool m_useBuffer; };      // hkSphereRepShape::hkCollisionSpheresInfo
struct hkShapeRayCastInput                                                   // 0x30
{
    hkVector4 m_from;                    // +0x00
    hkVector4 m_to;                      // +0x10
    hkUint32 m_filterInfo;               // +0x20
    void* m_rayShapeCollectionFilter;    // +0x24
    hkUint32 m_pad[2];                   // +0x28
};
struct hkShapeRayCastOutput { hkVector4 m_normal; hkUint32 m_shapeKey; float m_hitFraction; hkUint32 m_pad[2]; };   // 0x20

// ---- shape hierarchy (vtable slots from the retail vtables) -------------------------------------------------------
class hkShape : public hkReferencedObject
{
public:
    virtual int getType() const;                                                                                  // 2
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;                     // 3
    virtual float getMaximumProjection(const hkVector4& dir) const;                                                // 4
    virtual hkBool castRay(const struct hkShapeRayCastInput& input, struct hkShapeRayCastOutput& output) const;    // 5
    virtual void castRayWithCollector();                                                                           // 6
    int32_t m_userData;                                                                                            // +0x08
};
class hkSphereRepShape : public hkShape
{
public:
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;                                      // 7
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;                                     // 8
};
class hkConvexShape : public hkSphereRepShape
{
public:
    virtual void getSupportingVertex(const hkVector4& direction, hkCdVertex& supportingVertexOut) const;          // 9
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* verticesOut) const;       // 10
    virtual void getFirstVertex(hkVector4& v) const;                                                               // 11
    float m_radius;                                                                                                // +0x0c
};

struct hkAabbUtil
{
    // out = |R * halfExtents| + extraRadius, centred on the transform's translation
    static void calcAabb(const hkTransform& t, const hkVector4& halfExtents, float extraRadius, hkAabb& out);   // 0x010C03A0 (cdecl)
};

class hkConvexTranslateShape : public hkConvexShape
{
public:
    hkConvexTranslateShape(const hkConvexShape* childShape, const hkVector4& translation);                        // 0x010BFEB0
    virtual ~hkConvexTranslateShape();                                                                            // 0x010C0110 (scalar deleting form)
    virtual void calcStatistics(hkStatisticsCollector* c) const;                                                  // 0x010BFE50 (slot 1)
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;                     // 0x010C0160
    virtual float getMaximumProjection(const hkVector4& dir) const;                                                // 0x010BFF00
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;                  // 0x010C0220
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;                                      // 0x010BFE30
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;                                     // 0x010C00A0
    virtual void getSupportingVertex(const hkVector4& direction, hkCdVertex& supportingVertexOut) const;          // 0x010BFF30
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* verticesOut) const;       // 0x010BFF70
    virtual void getFirstVertex(hkVector4& v) const;                                                               // 0x010C0060

    hkConvexShape* m_childShape;                  // +0x10
    hkUint32 m_pad14[3];                          // +0x14..+0x1f
    hkVector4 m_translation;                      // +0x20 (w forced to 0)
};

class hkBoxShape : public hkConvexShape
{
public:
    hkBoxShape(const hkVector4& halfExtents, float radius);                                                       // 0x010C05D0
    virtual void calcStatistics(hkStatisticsCollector* c) const;                                                  // 0x010C0360 (slot 1)
    virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;                     // 0x010C0660
    virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;                                      // 0x010C0380
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;                                     // 0x010C0910
    virtual void getSupportingVertex(const hkVector4& direction, hkCdVertex& supportingVertexOut) const;          // 0x010C0690
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* verticesOut) const;       // 0x010C0780
    virtual void getFirstVertex(hkVector4& v) const;                                                               // 0x010C0640
    hkVector4 m_halfExtents;                      // +0x10 (w = min(x, y, z))
};

// =====================================================================================================================
// licence / keycode check
// =====================================================================================================================

// Pointer to the first '.' of the string, or 0 when the terminating NUL comes first.
static const char* hkFindDot(const char* p)
{
    char c = *p;
    if (c == '.')
        return p;
    for (;;)
    {
        if (c == 0)
            return 0;
        c = p[1];
        ++p;
        if (c == '.')
            return p;
    }
}

// @ 0x010bfbe0
// Checks the Havok keycode for a component (0 = no component check). Name inferred from its neighbour
// _hkSolverGetSystemTime; the strings and the time-limit test show it validates the evaluation keycode.
bool hkSolverCheckKeycode(int component);
bool hkSolverCheckKeycode(int component)
{
    static const char kPrefix[] = "The following component is not enabled in Havok Prime:\n\n\t\t";
    hkUint8 timeLimited = (hkUint8)((g_hkKeycodeHash >> 31) & 1);       // bit 31 of the key hash (time limited key)

    for (int i = 0; i < 3; ++i)
    {
        hkUint32 seed = g_hkKeycodeSeeds[i];
        const char* firstDot = hkFindDot(g_hkKeycodeString);
        if (firstDot == 0)
            break;

        // Prime keys: warn when a component is queried that Havok Prime does not enable
        if (strstr(firstDot, "Prime") != 0 && component != 0)
        {
            char msg[256];
            msg[0] = '\0';
            size_t n = strlen(kPrefix);
            size_t room = 0xfe - strlen(msg);
            strncat(msg, kPrefix, (n < room) ? n : room);
            // the count is again derived from the prefix length (as compiled), not from the component name
            n = strlen(kPrefix);
            room = 0xfe - strlen(msg);
            strncat(msg, g_hkComponentNames[component], (n < room) ? n : room);
            hkErrorMessage(msg);
        }

        const char* secondDot = hkFindDot(firstDot + 1);
        if (secondDot == 0)
            break;
        const char* p = secondDot + 1;

        bool accepted = false;
        if (!timeLimited)
        {
            // hash of the text after the second '.', starting at its second character (and ending with one extra NUL step)
            hkUint32 h = 0;
            char c = *p;
            if (c != 0)
            {
                do
                {
                    c = p[1];
                    h = h * 0x17 + (hkUint32)(int)c;       // movsx
                    ++p;
                } while (c != 0);
            }
            accepted = ((int)g_hkKeycodeHash == (int)((h ^ seed) & 0x7fffffff));
        }
        else
        {
            int expiry = (int)((g_hkKeycodeHash & 0x7fffffff) ^ seed);
            int now = (int)time(0);                            // _hkSolverGetSystemTime()
            accepted = (expiry > now) && (expiry - now < 0xed4e00);   // less than 180 days left
        }

        if (accepted)
        {
            if (component != 0 && i == 2)
            {
                hkErrorMessage("Product mismatch: Prime keyvalue detected in non prime keycode.\nPlease check your keycode or contact your Havok Account Manager.");
                return false;
            }
            return true;
        }
    }
    hkErrorMessage("Havok Physics evaluation key has expired or is invalid.\nPlease contact Havok.com for an extension.\nNo simulation possible.");
    return false;
}

// @ 0x010bfe20
int _hkSolverGetSystemTime()
{
    return (int)time(0);        // _time32(NULL)
}

// =====================================================================================================================
// hkConvexTranslateShape
// =====================================================================================================================

// @ 0x010bfe30
void hkConvexTranslateShape::getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const
{
    m_childShape->getCollisionSpheresInfo(info);
    info.m_useBuffer = true;
}

// @ 0x010bfe50
void hkConvexTranslateShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("CvxTranslate", 1, this);
    c->addReferencedObject("Child", 1, m_childShape);
    c->endObject();
}

// @ 0x010bfeb0
hkConvexTranslateShape::hkConvexTranslateShape(const hkConvexShape* childShape, const hkVector4& translation)
{
    m_childShape = const_cast<hkConvexShape*>(childShape);
    m_radius = childShape->m_radius;
    m_userData = 0;
    m_translation.x = translation.x;
    m_translation.y = translation.y;
    m_translation.z = translation.z;
    m_translation.w = 0.0f;                    // the w copy is overwritten with 0
    m_childShape->addReference();
}

// @ 0x010bff00
float hkConvexTranslateShape::getMaximumProjection(const hkVector4& dir) const
{
    float childProjection = m_childShape->getMaximumProjection(dir);
    // X87-PRECISION: the translation's projection and the final sum stay on the x87 stack
    hkX87Real proj = (hkX87Real)m_translation.z * dir.z + (hkX87Real)m_translation.y * dir.y;
    proj = proj + (hkX87Real)m_translation.x * dir.x;
    return (float)(childProjection + proj);
}

// @ 0x010bff30
void hkConvexTranslateShape::getSupportingVertex(const hkVector4& direction, hkCdVertex& supportingVertexOut) const
{
    m_childShape->getSupportingVertex(direction, supportingVertexOut);
    supportingVertexOut.x = m_translation.x + supportingVertexOut.x;
    supportingVertexOut.y = m_translation.y + supportingVertexOut.y;
    supportingVertexOut.z = m_translation.z + supportingVertexOut.z;
}

// @ 0x010bff70
void hkConvexTranslateShape::convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* verticesOut) const
{
    m_childShape->convertVertexIdsToVertices(ids, numIds, verticesOut);
    for (int i = 0; i < numIds; ++i)            // the binary unrolls by four; same order
    {
        verticesOut[i].x = m_translation.x + verticesOut[i].x;
        verticesOut[i].y = verticesOut[i].y + m_translation.y;
        verticesOut[i].z = verticesOut[i].z + m_translation.z;
    }
}

// @ 0x010c0060
void hkConvexTranslateShape::getFirstVertex(hkVector4& v) const
{
    m_childShape->getFirstVertex(v);
    v.x = m_translation.x + v.x;
    v.y = m_translation.y + v.y;
    v.z = m_translation.z + v.z;
    v.w = m_translation.w + v.w;
}

// @ 0x010c00a0
const hkSphere* hkConvexTranslateShape::getCollisionSpheres(hkSphere* sphereBuffer) const
{
    const hkSphere* spheres = m_childShape->getCollisionSpheres(sphereBuffer);
    hkCollisionSpheresInfo info;
    m_childShape->getCollisionSpheresInfo(info);
    for (int i = 0; i < info.m_numSpheres; ++i)
    {
        sphereBuffer[i].m_pos.x = spheres[i].m_pos.x + m_translation.x;
        sphereBuffer[i].m_pos.y = spheres[i].m_pos.y + m_translation.y;
        sphereBuffer[i].m_pos.z = spheres[i].m_pos.z + m_translation.z;
        sphereBuffer[i].m_pos.w = spheres[i].m_pos.w + m_translation.w;
    }
    return sphereBuffer;
}

// @ 0x010c0110
hkConvexTranslateShape::~hkConvexTranslateShape()
{
    m_childShape->removeReference();
    // scalar deleting form: (flag & 1) -> hkMemory::deallocateChunk(this, memSize, 0x24)
}

// @ 0x010c0160
void hkConvexTranslateShape::getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const
{
    m_childShape->getAabb(localToWorld, tolerance, out);
    const float* m = localToWorld.m;
    // X87-PRECISION: the sums of products are stored to floats only for x and y; z stays in a register
    float tx = m_translation.x, ty = m_translation.y, tz = m_translation.z;
    hkX87Real offX = (hkX87Real)tx * m[0] + ((hkX87Real)ty * m[4] + (hkX87Real)tz * m[8]);
    float ox = (float)offX;
    hkX87Real offY = (hkX87Real)tx * m[1] + ((hkX87Real)ty * m[5] + (hkX87Real)tz * m[9]);
    float oy = (float)offY;
    hkX87Real oz = (hkX87Real)tx * m[2] + ((hkX87Real)ty * m[6] + (hkX87Real)tz * m[10]);
    // w is copied onto itself
    out.m_min.w = out.m_min.w;
    out.m_max.w = out.m_max.w;
    out.m_min.x = ox + out.m_min.x;
    out.m_min.y = oy + out.m_min.y;
    out.m_min.z = (float)(oz + out.m_min.z);
    out.m_max.x = ox + out.m_max.x;
    out.m_max.y = oy + out.m_max.y;
    out.m_max.z = (float)(oz + out.m_max.z);
}

// @ 0x010c0220
hkBool hkConvexTranslateShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
    HK_TIMER_BEGIN("TtrcConvTransl");

    hkShapeRayCastInput local = input;                  // 12 dword copy (filter info and filter pointer ride along)
    local.m_from.x = input.m_from.x - m_translation.x;
    local.m_from.y = input.m_from.y - m_translation.y;
    local.m_from.z = input.m_from.z - m_translation.z;
    local.m_from.w = input.m_from.w - m_translation.w;
    local.m_to.x = input.m_to.x - m_translation.x;
    local.m_to.y = input.m_to.y - m_translation.y;
    local.m_to.z = input.m_to.z - m_translation.z;
    local.m_to.w = input.m_to.w - m_translation.w;
    hkBool hit = m_childShape->castRay(local, output);

    HK_TIMER_END();
    return hit;
}

// =====================================================================================================================
// hkBoxShape (first half) and hkAabbUtil
// =====================================================================================================================

// @ 0x010c0360
void hkBoxShape::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("BoxShape", 1, this);
    c->endObject();
}

// @ 0x010c03a0
void hkAabbUtil::calcAabb(const hkTransform& t, const hkVector4& halfExtents, float extraRadius, hkAabb& out)
{
    const float* m = t.m;
    float hx = halfExtents.x;
    float hy = halfExtents.y;
    float hz = halfExtents.z;
    float r = extraRadius;

    // column products (stored to float slots, except those the asm leaves in registers)
    float a0 = hx * m[0];
    float a1 = hx * m[1];
    float a2 = hx * m[2];
    float a3 = hx * m[3];
    float b0 = hy * m[4];
    float b1 = hy * m[5];
    float b2 = hy * m[6];
    hkX87Real b3reg = (hkX87Real)hy * m[7];             // X87-PRECISION: register until its fabs is stored
    hkX87Real c0reg = (hkX87Real)hz * m[8];             // X87-PRECISION
    float c1 = hz * m[9];
    float c2 = hz * m[10];
    float c3 = hz * m[11];

    a0 = fabsf(a0); a1 = fabsf(a1); a2 = fabsf(a2); a3 = fabsf(a3);
    b0 = fabsf(b0); b1 = fabsf(b1); b2 = fabsf(b2);
    float b3 = (float)fabs(b3reg);
    hkX87Real ac0 = fabs(c0reg);
    c2 = fabsf(c2);
    c3 = fabsf(c3);

    float e0 = (float)(ac0 + r);                         // stored
    hkX87Real e1 = (hkX87Real)fabsf(c1) + r;             // X87-PRECISION: not stored
    hkX87Real e2 = (hkX87Real)c2 + r;                    // X87-PRECISION: not stored
    float e3 = (float)((hkX87Real)c3 + r);               // stored

    // half-size of the box in world space: (|b| + |a|) + (|c| + radius)
    float x0 = (float)(((hkX87Real)b0 + a0) + e0);
    float x1 = (float)(((hkX87Real)b1 + a1) + e1);
    float s2 = (float)((hkX87Real)b2 + a2);
    hkX87Real x2 = (hkX87Real)s2 + e2;                   // X87-PRECISION: stays on the x87 stack
    float s3 = (float)((hkX87Real)b3 + a3);
    float x3 = (float)((hkX87Real)s3 + e3);

    float n0 = -x0;
    float n1 = -x1;
    float n2 = (float)(-x2);
    float n3 = -x3;

    out.m_max.z = (float)(x2 + m[14]);
    out.m_max.w = x3 + m[15];
    out.m_min.x = n0 + m[12];
    out.m_min.y = n1 + m[13];
    out.m_min.z = n2 + m[14];
    out.m_min.w = n3 + m[15];
    out.m_max.x = x0 + m[12];
    out.m_max.y = x1 + m[13];
}

// @ 0x010c05d0
hkBoxShape::hkBoxShape(const hkVector4& halfExtents, float radius)
{
    m_radius = radius;
    m_userData = 0;
    m_halfExtents.x = halfExtents.x;
    m_halfExtents.y = halfExtents.y;
    m_halfExtents.z = halfExtents.z;
    m_halfExtents.w = halfExtents.w;
    // w = min(x, y, z), with the compare/NaN behaviour of the fcomp sequence
    float m = (m_halfExtents.x < m_halfExtents.y) ? m_halfExtents.x : m_halfExtents.y;
    m_halfExtents.w = m;
    if (m > m_halfExtents.z)
        m = m_halfExtents.z;
    m_halfExtents.w = m;
}

// @ 0x010c0640
void hkBoxShape::getFirstVertex(hkVector4& v) const
{
    v.x = m_halfExtents.x;
    v.y = m_halfExtents.y;
    v.z = m_halfExtents.z;
    v.w = m_halfExtents.w;
}

// @ 0x010c0660
void hkBoxShape::getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const
{
    hkAabbUtil::calcAabb(localToWorld, m_halfExtents, tolerance + m_radius, out);
}

// @ 0x010c0690
void hkBoxShape::getSupportingVertex(const hkVector4& direction, hkCdVertex& supportingVertexOut) const
{
    // vertex = halfExtents with each component's sign taken from the direction's sign bit
    hkUint32 hx, hy, hz, hw, dx, dy, dz, dw;
    memcpy(&hx, &m_halfExtents.x, 4); memcpy(&hy, &m_halfExtents.y, 4);
    memcpy(&hz, &m_halfExtents.z, 4); memcpy(&hw, &m_halfExtents.w, 4);
    memcpy(&dx, &direction.x, 4); memcpy(&dy, &direction.y, 4);
    memcpy(&dz, &direction.z, 4); memcpy(&dw, &direction.w, 4);
    hx ^= (dx & 0x80000000u);
    hy ^= (dy & 0x80000000u);
    hz ^= (dz & 0x80000000u);
    hw ^= (dw & 0x80000000u);
    memcpy(&supportingVertexOut.x, &hx, 4); memcpy(&supportingVertexOut.y, &hy, 4);
    memcpy(&supportingVertexOut.z, &hz, 4); memcpy(&supportingVertexOut.w, &hw, 4);

    // vertex id (even number 0..14) packed into the low bits of w: bit3 = x<0, bit2 = y<0, bit1 = z<0
    hkUint32 xNeg = (supportingVertexOut.x < 0.0f) ? 1u : 0u;
    hkUint32 yNeg = (supportingVertexOut.y < 0.0f) ? 1u : 0u;
    hkUint32 zNeg = (supportingVertexOut.z < 0.0f) ? 1u : 0u;
    hkUint32 wNeg = (supportingVertexOut.w < 0.0f) ? 1u : 0u;
    hkUint32 id = ((zNeg << 1) | (yNeg << 2) | ((0u - xNeg) << 3) | wNeg) & 0xe;
    hkUint32 wBits = id | 0x3f000000u;
    memcpy(&supportingVertexOut.w, &wBits, 4);
}

// sign table of the eight box corners (0x014A2680), indexed by vertex id / 2
static const float s_boxCorner[8][4] =
{
    {  1.0f,  1.0f,  1.0f, 0.0f }, {  1.0f,  1.0f, -1.0f, 0.0f },
    {  1.0f, -1.0f,  1.0f, 0.0f }, {  1.0f, -1.0f, -1.0f, 0.0f },
    { -1.0f,  1.0f,  1.0f, 0.0f }, { -1.0f,  1.0f, -1.0f, 0.0f },
    { -1.0f, -1.0f,  1.0f, 0.0f }, { -1.0f, -1.0f, -1.0f, 0.0f },
};

// @ 0x010c0780
void hkBoxShape::convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* verticesOut) const
{
    for (int i = 0; i < numIds; ++i)         // the binary unrolls by four; same order
    {
        const float* corner = s_boxCorner[ids[i] >> 1];
        verticesOut[i].x = corner[0] * m_halfExtents.x;
        verticesOut[i].y = corner[1] * m_halfExtents.y;
        verticesOut[i].z = corner[2] * m_halfExtents.z;
        verticesOut[i].w = corner[3] * m_halfExtents.w;       // dead store: overwritten below
        hkUint32 wBits = (hkUint32)ids[i] | 0x3f000000u;
        memcpy(&verticesOut[i].w, &wBits, 4);
    }
}

// @ 0x010c0910
const hkSphere* hkBoxShape::getCollisionSpheres(hkSphere* sphereBuffer) const
{
    // the eight corners (+-x, +-y, +-z) with the shape radius in w; negation is a multiply by -1.0
    float x = m_halfExtents.x;
    float y = m_halfExtents.y;
    float z = m_halfExtents.z;
    float r = m_radius;
    float nx = x * -1.0f;
    float ny = y * -1.0f;
    float nz = z * -1.0f;
    hkVector4* s = &sphereBuffer[0].m_pos;
    s[0].x = x;  s[0].y = y;  s[0].z = z;  s[0].w = r;
    s[1].x = nx; s[1].y = y;  s[1].z = z;  s[1].w = r;
    s[2].x = x;  s[2].y = ny; s[2].z = z;  s[2].w = r;
    s[3].x = nx; s[3].y = ny; s[3].z = z;  s[3].w = r;
    s[4].x = x;  s[4].y = y;  s[4].z = nz; s[4].w = r;
    s[5].x = nx; s[5].y = y;  s[5].z = nz; s[5].w = r;
    s[6].x = x;  s[6].y = ny; s[6].z = nz; s[6].w = r;
    s[7].x = nx; s[7].y = ny; s[7].z = nz; s[7].w = r;
    return sphereBuffer;
}
