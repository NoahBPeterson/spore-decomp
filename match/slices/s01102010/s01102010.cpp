// Slice s01102010: hkMoppLongRayVirtualMachine::queryRay (recursive MOPP bytecode walker, Havok 3.1, x87).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

struct hkBool {
    char m_b;
    hkBool() {}
    hkBool(bool b) : m_b(b) {}
    operator bool() const { return m_b != 0; }
};

struct hkShapeRayCastOutput { float m_pad[4]; int m_shapeKey; float m_hitFraction; };   // +0x10 key, +0x14 fraction
struct hkRayShapeCollectionFilter;
struct hkShapeRayCastInput {
    float m_from[4];                  // +0
    float m_to[4];                    // +0x10
    uint32_t m_filterInfo;            // +0x20
    hkRayShapeCollectionFilter* m_rayShapeCollectionFilter;   // +0x24
};
struct hkRayHitCollector { virtual void v0(); float m_earlyOutHitFraction; };
struct hkCdBody { const void* m_shape; uint32_t m_shapeKey; const void* m_motion; const hkCdBody* m_parent; };
struct hkCdBodyMotionHolder { uint8_t pad[8]; const void* m_motion; };

struct hkShape {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;          // slot 5 (+0x14)
    virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& body, hkRayHitCollector& collector) const;   // slot 6 (+0x18)
};
struct hkShapeCollection {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual const hkShape* getChildShape(uint32_t key, void* buffer) const;                                // slot 10 (+0x28)
};
struct hkRayShapeCollectionFilter {
    virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection, uint32_t key) const;   // slot 0
};
struct hkMoppCodeRef { uint8_t pad[0x10]; float m_offset[4]; };

struct hkOstream {
    hkOstream(char* buf, int size, bool flag);
    ~hkOstream();
    hkOstream& operator<<(const char* s);
};
struct hkError {
    virtual void v0(); virtual void v1();
    virtual int message(int level, int id, const char* desc, const char* file, int line);   // slot 2
    static hkError* s_instance;      // 0x016e4184
};

extern "C" char hkSolverCheckKeycode(int);   // 0x010bfbe0
extern char g_hkKeycodeOk;                   // 0x016e5ac0

// MOPP traversal state (7 live words copied between levels; props are written in place).
struct hkMoppState {
    float m_off[4];       // +0x00 offset xyz, +0x0c w
    int   m_shift;        // +0x10
    float m_scale;        // +0x14
    int   m_primOffset;   // +0x18
    int   m_prop[4];      // +0x1c..0x28  (word 7 is carried across the copy)
    void copyFrom(const hkMoppState& src);   // 0x01101fd0
};

struct hkMoppLongRayVirtualMachine {
    uint8_t m_pad0[0x10];
    const hkMoppCodeRef* m_code;                // +0x10
    float m_invScale;                           // +0x14
    uint8_t m_pad1[8];
    hkShapeRayCastInput m_rayInput;             // +0x20 (0x28 bytes)
    uint8_t m_pad2[8];
    hkBool m_hit;                               // +0x50
    uint8_t m_pad3[3];
    float m_hitFraction;                        // +0x54
    hkShapeRayCastOutput* m_output;             // +0x58
    hkRayHitCollector* m_collector;             // +0x5c
    const hkCdBody* m_cdBody;                   // +0x60
    const hkShapeCollection* m_shapeCollection; // +0x64
    void queryRay(hkMoppState* st, const uint8_t* p, float* ray);
};

// @ 0x01102010
void hkMoppLongRayVirtualMachine::queryRay(hkMoppState* st, const uint8_t* p, float* ray)
{
    hkMoppState local;
    float rayCopy[8];
    char textBuf[0x200];
    float a, b, lo, hi;
    int axis;
    uint32_t skipHi, skipLo;
    const uint8_t* next;
    float u, t;
    int ax, hiIdx;
    float fa, fb, d, c[8];

    if (!g_hkKeycodeOk) {
        g_hkKeycodeOk = hkSolverCheckKeycode(4);
        if (!g_hkKeycodeOk) return;
    }

    for (;;) {
        uint32_t op = p[0];
        axis = 999;

        switch (op) {
        case 0:
            return;
        case 1: case 2: case 3: case 4: {
            float x = (float)p[1], y = (float)p[2], z = (float)p[3];
            float f = (float)(1 << (op & 0x1f));
            ray[0] = ray[0] - x; ray[1] = ray[1] - y; ray[2] = ray[2] - z;
            ray[4] = ray[4] - x; ray[5] = ray[5] - y; ray[6] = ray[6] - z;
            ray[0] = f * ray[0]; ray[1] = f * ray[1]; ray[2] = f * ray[2]; ray[3] = f * ray[3];
            ray[4] = f * ray[4]; ray[5] = f * ray[5]; ray[6] = f * ray[6]; ray[7] = f * ray[7];
            local.m_off[0] = (x + st->m_off[0]) * f;
            local.m_off[1] = (y + st->m_off[1]) * f;
            local.m_off[2] = (z + st->m_off[2]) * f;
            local.m_off[3] = st->m_off[3] * f;
            local.m_shift = st->m_shift + (int)op;
            p += 4;
            local.m_scale = f * st->m_scale;
            local.m_prop[0] = st->m_prop[0];
            local.m_primOffset = st->m_primOffset;
            st = &local;
            continue;
        }
        case 5: p += p[1] + 2; continue;
        case 6: p += (uint32_t)p[1] * 0x100 + p[2] + 3; continue;
        case 7: p += (uint32_t)((p[1] << 8) | p[2]) * 0x100 + p[3] + 4; continue;
        case 9: {
            uint32_t v = p[1];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 2;
            continue;
        }
        case 10: {
            uint32_t v = (p[1] << 8) | p[2];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 3;
            continue;
        }
        case 0xb: {
            uint32_t v = (((p[1] << 8) | p[2]) << 8 | p[3]) << 8 | p[4];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset = v;
            p += 5;
            continue;
        }
        case 0x10: case 0x11: case 0x12:
            axis = op - 0x10;
            lo = (float)p[1]; hi = (float)p[2];
            a = ray[axis]; b = ray[op - 0xc];
            goto splitCommon;
        case 0x13:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[2] + ray[1]; b = ray[6] + ray[5];
            goto splitCommon;
        case 0x14:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[1] - ray[2]; b = ray[5] - ray[6];
            goto splitCommon;
        case 0x15:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[2] + ray[0]; b = ray[6] + ray[4];
            goto splitCommon;
        case 0x16:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[0] - ray[2]; b = ray[4] - ray[6];
            goto splitCommon;
        case 0x17:
            lo = (float)(p[1] << 1); hi = (float)(p[2] << 1);
            a = ray[1] + ray[0]; b = ray[5] + ray[4];
            goto splitCommon;
        case 0x18:
            lo = (float)(int)(p[1] * 2 - 0xff); hi = (float)(int)(p[2] * 2 - 0xff);
            a = ray[0] - ray[1]; b = ray[4] - ray[5];
            goto splitCommon;
        case 0x19:
            lo = (float)(p[1] * 3); hi = (float)(p[2] * 3);
            a = (ray[2] + ray[1]) + ray[0]; b = (ray[6] + ray[5]) + ray[4];
            goto splitCommon;
        case 0x1a:
            lo = (float)(int)((p[1] - 0x55) * 3); hi = (float)(int)((p[2] - 0x55) * 3);
            a = (ray[1] + ray[0]) - ray[2]; b = (ray[5] + ray[4]) - ray[6];
            goto splitCommon;
        case 0x1b:
            lo = (float)(int)((p[1] - 0x55) * 3); hi = (float)(int)((p[2] - 0x55) * 3);
            a = (ray[0] - ray[1]) + ray[2]; b = (ray[4] - ray[5]) + ray[6];
            goto splitCommon;
        case 0x1c:
            lo = (float)(int)((p[1] - 0xaa) * 3); hi = (float)(int)((p[2] - 0xaa) * 3);
            a = (ray[0] - ray[1]) - ray[2]; b = (ray[4] - ray[5]) - ray[6];
            goto splitCommon;
        case 0x20: case 0x21: case 0x22:
            skipHi = p[2];
            axis = op - 0x20;
            next = p + 3;
            hi = (float)p[1];
            lo = hi + 1.0f;
            a = ray[axis]; b = ray[op - 0x1c];
            skipLo = 0;
            goto splitBody;
        case 0x23: case 0x24: case 0x25:
            lo = (float)p[1]; hi = (float)p[2];
            axis = op - 0x23;
            a = ray[axis];
            next = p + 7;
            b = ray[op - 0x1f];
            skipLo = (p[3] << 8) | p[4];
            skipHi = (p[5] << 8) | p[6];
            goto splitBody;
        case 0x26: case 0x27: case 0x28:
            ax = op - 0x26;
            a = (float)p[1];
            b = (float)p[2];
            p += 3;
            goto planeClip;
        case 0x29: case 0x2a: case 0x2b:
            ax = op - 0x29;
            a = ((float)(int)(((p[1] << 8 | p[2]) << 8) | p[3]) * m_invScale) * st->m_scale - ((float*)st)[ax];
            b = ((float)(int)(((p[4] << 8 | p[5]) << 8) | p[6]) * m_invScale) * st->m_scale - ((float*)st)[ax];
            p += 7;
            goto planeClip;
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
            skipHi = op - 0x30;
            goto leaf;
        case 0x50: skipHi = p[1]; goto leaf;
        case 0x51: skipHi = (p[1] << 8) | p[2]; goto leaf;
        case 0x52: skipHi = ((p[1] << 8) | p[2]) << 8 | p[3]; goto leaf;
        case 0x53: skipHi = p[4] + (uint32_t)((p[1] << 8) | p[2]) * 0x10000 + (uint32_t)p[3] * 0x100; goto leaf;
        case 0x60: case 0x61: case 0x62: case 0x63:
            local.m_prop[op - 0x60] = p[1];
            p += 2;
            goto propDone;
        case 0x64: case 0x65: case 0x66: case 0x67:
            local.m_prop[op - 0x64] = (p[1] << 8) | p[2];
            p += 3;
            goto propDone;
        case 0x68: case 0x69: case 0x6a: case 0x6b:
            local.m_prop[op - 0x68] = (((p[1] << 8 | p[2]) << 8) | p[3]) << 8 | p[4];
            p += 5;
        propDone:
            {
                int keep = local.m_prop[0];
                if (st != &local) { local.copyFrom(*st); st = &local; }
                local.m_prop[0] = keep;
            }
            continue;
        default: {
            hkOstream os(textBuf, 0x200, true);
            os << "Unknown command - This mopp data has been corrupted (check for memory trashing), or an hkMoppBvTreeShape has been pointed at invalid mopp data.\n";
            hkError::s_instance->message(3, 0x1298fedd, textBuf, ".\\collide\\mopp\\machine\\hkMoppLongRayVirtualMachine.cpp", 0x1c9);
            continue;
        }
        }

        // ---- ops 0x26..0x2b: clip the ray against a plane slab ----
    planeClip:
        fa = ray[ax]; fb = ray[ax + 4];
        if (fb <= fa) {
            if (fa < a) return;
            if (b < fb) return;
            hiIdx = 1;
        } else {
            if (fb < a) return;
            if (b < fa) return;
            hiIdx = 0;
        }
        for (int i = 0; i < 8; i++) c[i] = ray[i];
        d = fa - b;
        if (d * (fb - b) < 0.0f) {
            t = d / (d - (fb - b));
            u = 1.0f - t;
            ray[hiIdx * -4 + 4] = c[4] * t + c[0] * u;
            ray[hiIdx * -4 + 5] = c[1] * u + c[5] * t;
            ray[hiIdx * -4 + 6] = c[6] * t + c[2] * u;
            ray[hiIdx * -4 + 7] = c[7] * t + c[3] * u;
        }
        fa = fa - a;
        if (fa * (fb - a) < 0.0f) {
            float* q = ray + hiIdx * 4;
            t = fa / (fa - (fb - a));
            u = 1.0f - t;
            q[0] = c[4] * t + c[0] * u;
            q[1] = c[5] * t + c[1] * u;
            q[2] = c[6] * t + c[2] * u;
            q[3] = c[7] * t + c[3] * u;
        }
        continue;

        // ---- leaf: report primitive ----
    leaf:
        {
            int key = (int)skipHi + st->m_primOffset;
            hkBool enabled;
            if (m_rayInput.m_rayShapeCollectionFilter) {
                if (!m_rayInput.m_rayShapeCollectionFilter->isCollisionEnabled(m_rayInput, *m_shapeCollection, key)) return;
            }
            char shapeBuf[0x100];
            const hkShape* shape = m_shapeCollection->getChildShape(key, shapeBuf);
            if (m_output) {
                if (!shape->castRay(m_rayInput, *m_output)) return;
                m_hit = 1;
                m_hitFraction = m_output->m_hitFraction;
                m_output->m_shapeKey = key;
                return;
            }
            hkCdBody body;
            body.m_shape = shape;
            body.m_shapeKey = key;
            body.m_motion = ((const hkCdBodyMotionHolder*)m_cdBody)->m_motion;
            body.m_parent = m_cdBody;
            shape->castRayWithCollector(m_rayInput, body, *m_collector);
            m_hitFraction = m_collector->m_earlyOutHitFraction;
            return;
        }

        // ---- ops 0x10..0x1c: tail shared by the split ops ----
    splitCommon:
        skipHi = p[3];
        next = p + 4;
        skipLo = 0;
        // fallthrough
    splitBody:
        if (hi <= b || hi <= a) {
            p = next + skipHi;
            if (a <= lo || b <= lo) {
                float cal = a - lo;      // local_2c4
                float cah = a - hi;      // local_2bc
                float cbl = b - lo;      // local_2b4
                float cbh = b - hi;
                for (int i = 0; i < 8; i++) rayCopy[i] = ray[i];
                if (cbl <= cal) {
                    if (cbh * cah < 0.0f) {
                        t = cah / (cah - cbh);
                        u = 1.0f - t;
                        rayCopy[4] = t * ray[4] + u * ray[0];
                        rayCopy[5] = u * ray[1] + t * ray[5];
                        rayCopy[6] = u * ray[2] + t * ray[6];
                        rayCopy[7] = u * ray[3] + t * ray[7];
                    }
                    queryRay(st, p, rayCopy);
                    if (cbl * cal < 0.0f) {
                        t = cal / (cal - cbl);
                        u = 1.0f - t;
                        ray[0] = u * ray[0] + t * ray[4];
                        ray[1] = u * ray[1] + t * ray[5];
                        ray[2] = u * ray[2] + t * ray[6];
                        ray[3] = u * ray[3] + t * ray[7];
                    }
                    if (m_hitFraction < 1.0f) {
                        float f = m_hitFraction, g = 1.0f - f;
                        float x = f * m_rayInput.m_to[0] + g * m_rayInput.m_from[0];
                        float y = f * m_rayInput.m_to[1] + g * m_rayInput.m_from[1];
                        float z = f * m_rayInput.m_to[2] + g * m_rayInput.m_from[2];
                        float wv = f * m_rayInput.m_to[3] + g * m_rayInput.m_from[3];
                        const hkMoppCodeRef* c = m_code;
                        ray[4] = x - c->m_offset[0];
                        ray[5] = y - c->m_offset[1];
                        ray[6] = z - c->m_offset[2];
                        ray[7] = wv - c->m_offset[3];
                        float s = st->m_scale;
                        ray[4] = s * ray[4]; ray[5] = s * ray[5]; ray[6] = s * ray[6]; ray[7] = s * ray[7];
                        ray[4] = ray[4] - st->m_off[0]; ray[5] = ray[5] - st->m_off[1];
                        ray[6] = ray[6] - st->m_off[2]; ray[7] = ray[7] - st->m_off[3];
                        if (axis < 3 && lo < ray[axis + 4]) return;
                    }
                    p += skipLo - skipHi;
                } else {
                    if (cbl * cal < 0.0f) {
                        t = cal / (cal - cbl);
                        u = 1.0f - t;
                        rayCopy[4] = t * ray[4] + u * ray[0];
                        rayCopy[5] = u * ray[1] + t * ray[5];
                        rayCopy[6] = u * ray[2] + t * ray[6];
                        rayCopy[7] = u * ray[3] + t * ray[7];
                    }
                    queryRay(st, p + (skipLo - skipHi), rayCopy);
                    if (cbh * cah < 0.0f) {
                        t = cah / (cah - cbh);
                        u = 1.0f - t;
                        ray[0] = t * ray[4] + u * ray[0];
                        ray[1] = u * ray[1] + t * ray[5];
                        ray[2] = u * ray[2] + t * ray[6];
                        ray[3] = u * ray[3] + t * ray[7];
                    }
                    if (m_hitFraction < 1.0f) {
                        float f = m_hitFraction, g = 1.0f - f;
                        float x = f * m_rayInput.m_to[0] + g * m_rayInput.m_from[0];
                        float y = f * m_rayInput.m_to[1] + g * m_rayInput.m_from[1];
                        float z = f * m_rayInput.m_to[2] + g * m_rayInput.m_from[2];
                        float wv = f * m_rayInput.m_to[3] + g * m_rayInput.m_from[3];
                        const hkMoppCodeRef* c = m_code;
                        ray[4] = x - c->m_offset[0];
                        ray[5] = y - c->m_offset[1];
                        ray[6] = z - c->m_offset[2];
                        ray[7] = wv - c->m_offset[3];
                        float s = st->m_scale;
                        ray[4] = s * ray[4]; ray[5] = s * ray[5]; ray[6] = s * ray[6]; ray[7] = s * ray[7];
                        ray[4] = ray[4] - st->m_off[0]; ray[5] = ray[5] - st->m_off[1];
                        ray[6] = ray[6] - st->m_off[2]; ray[7] = ray[7] - st->m_off[3];
                        if (axis < 3 && ray[axis + 4] < hi) return;
                    }
                }
            }
        } else {
            p = next + skipLo;
        }
    }
}
