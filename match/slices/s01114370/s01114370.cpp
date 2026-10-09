// Havok 3.1 MOPP machine: hkMoppAabbCastVirtualMachine, recursive bytecode interpreter
// (".\collide\mopp\machine\hkMoppAabbCastVirtualMachine.cpp").
#include "types.h"

struct hkBool {
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool((char)b) {}
    operator bool() const { return m_bool != 0; }
};
struct hkOstream {
    hkOstream(void* mem, int memSize, hkBool isString);   // 0x0107EF80
    ~hkOstream();                                         // 0x0107EFD0
    hkOstream& operator<<(const char* s);                 // 0x0107EE30
    uint32_t m_impl[3];
};
struct hkErrorIface {
    virtual void v0();
    virtual void v1();
    virtual void message(int msg, int id, const char* desc, const char* file, int line) = 0;
};
extern hkErrorIface* g_hkError;   // 0x016E4184

// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool.
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720

struct hkMoppShape {
    virtual void v0();
    virtual void v1();
    virtual int getType() = 0;
};
struct hkMoppContainer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual hkMoppShape* getChildShape(int key, void* buffer) = 0;   // slot 10 (+0x28)
};
struct hkMoppChildRef {
    hkMoppShape* m_shape;
    int m_key;
    uint32_t m_a;
    uint32_t m_b;
};
struct hkMoppFilter {
    virtual hkBool check(void* a, void* b, void* c, hkMoppContainer* container, int key) = 0;
};
struct hkMoppDispatch {
    char pad[4];
    hkMoppFilter* m_filter;   // +4
};
typedef void (__cdecl *hkMoppHitFn)(void*, hkMoppChildRef*, void*, void*, void*);

// Per-subtree transform, 13 dwords copied by FUN_01114310 (the 4th dword array element beyond is scratch)
struct hkMoppXform {
    __declspec(align(16)) float o[4];   // +0x00 offset (aligns the struct to 16)
    float f[5];            // +0x10 scale factors / extents (+0x20 used as the diagonal term)
    int   m_idx;           // +0x24
    float m_scale;         // +0x28
    int   m_primOffset;    // +0x2c
    uint32_t m_prop[4];    // +0x30 properties
    void assign(const hkMoppXform& o);   // 0x01114310
};

struct hkMoppQueryInput {
    float p[8];            // +0x00 start, +0x10 end
    char pad[0x10];
    hkMoppDispatch* m_a;   // +0x30
    void* m_b;             // +0x34
    char** m_c;            // +0x38
};
struct hkMoppRayInfo {
    char pad[0x10];
    float v[4];            // +0x10
};

struct hkMoppAabbCastVirtualMachine {
    char pad0[0x10];
    hkMoppRayInfo* m_info;      // +0x10
    float m_errScale;           // +0x14
    int   m_axisIdx;            // +0x18
    float m_frac;               // +0x1c
    float m_best;               // +0x20
    struct Hit { uint32_t a; float frac; }* m_hit;   // +0x24
    void* m_out;                // +0x28
    hkMoppQueryInput* m_in;     // +0x2c

    void cast(const hkMoppXform* xf, const uint8_t* pc, float* seg);   // 0x01114370
};

// @ 0x01114370
void hkMoppAabbCastVirtualMachine::cast(const hkMoppXform* xf, const uint8_t* pc, float* seg)
{
    hkMoppXform local;
    for (;;) {
        unsigned op = *pc;
        int axis = 999;
        float lo, hi, p1;
        double p0;   // the original keeps p0 in an x87 register (never rounded to float)
        unsigned skipA, skipB;
        switch (op) {
        case 0:
            return;
        case 1: case 2: case 3: case 4: {
            float x = (float)pc[1];
            float y = (float)pc[2];
            float z = (float)pc[3];
            float s = (float)(1 << op);
            seg[3] = seg[3];
            seg[0] = seg[0] - x;
            seg[1] = seg[1] - y;
            seg[2] = seg[2] - z;
            seg[7] = seg[7];
            seg[4] = seg[4] - x;
            seg[5] = seg[5] - y;
            seg[6] = seg[6] - z;
            seg[0] = s * seg[0];
            seg[1] = s * seg[1];
            seg[2] = s * seg[2];
            seg[3] = s * seg[3];
            seg[4] = s * seg[4];
            seg[5] = s * seg[5];
            seg[6] = s * seg[6];
            seg[7] = s * seg[7];
            local.o[0] = x + xf->o[0];
            local.o[1] = y + xf->o[1];
            local.o[2] = z + xf->o[2];
            local.o[0] = local.o[0] * s;
            local.o[1] = local.o[1] * s;
            local.o[2] = local.o[2] * s;
            local.o[3] = xf->o[3] * s;
            local.m_idx = xf->m_idx + (int)op;
            pc += 4;
            local.m_scale = s * xf->m_scale;
            local.f[0] = s * xf->f[0];
            local.f[1] = s * xf->f[1];
            local.f[2] = s * xf->f[2];
            local.f[3] = s * xf->f[3];
            local.f[4] = s * xf->f[4];
            local.m_prop[0] = xf->m_prop[0];
            local.m_primOffset = xf->m_primOffset;
            xf = &local;
            continue;
        }
        case 5:
            pc += pc[1] + 2;
            continue;
        case 6:
            pc += (unsigned)pc[1] * 0x100 + pc[2] + 3;
            continue;
        case 7:
            pc += ((unsigned)pc[1] * 0x100 + pc[2]) * 0x100 + pc[3] + 4;
            continue;
        case 9: {
            unsigned v = pc[1];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset += v;
            pc += 2;
            continue;
        }
        case 10: {
            unsigned v = pc[1] * 0x100 + pc[2];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset += v;
            pc += 3;
            continue;
        }
        case 11: {
            unsigned v = ((pc[1] * 0x100 + pc[2]) * 0x100 + pc[3]) * 0x100 + pc[4];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset = v;
            pc += 5;
            continue;
        }
        case 0x10: case 0x11: case 0x12:
            axis = op - 0x10;
            lo = (float)pc[2] - xf->f[axis];
            hi = (float)pc[1] + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x13: {
            lo = (float)(pc[2] << 1) - ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            hi = (float)(pc[1] << 1) + ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            p0 = seg[2] + seg[1];
            p1 = seg[6] + seg[5];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x14: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            p0 = seg[1] - seg[2];
            p1 = seg[5] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x15: {
            lo = (float)(pc[2] << 1) - ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            hi = (float)(pc[1] << 1) + ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            p0 = seg[2] + seg[0];
            p1 = seg[6] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x16: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            p0 = seg[0] - seg[2];
            p1 = seg[4] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x17: {
            lo = (float)(pc[2] << 1) - ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            hi = (float)(pc[1] << 1) + ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            p0 = seg[1] + seg[0];
            p1 = seg[5] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x18: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            p0 = seg[0] - seg[1];
            p1 = seg[4] - seg[5];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x19:
            lo = (float)(pc[2] * 3) - xf->f[4];
            hi = (float)(pc[1] * 3) + xf->f[4];
            p0 = seg[2] + seg[1] + seg[0];
            p1 = seg[6] + seg[5] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1a:
            lo = (float)(((int)pc[2] - 0x55) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0x55) * 3) + xf->f[4];
            p0 = seg[1] + seg[0] - seg[2];
            p1 = seg[5] + seg[4] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1b:
            lo = (float)(((int)pc[2] - 0x55) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0x55) * 3) + xf->f[4];
            p0 = seg[0] - seg[1] + seg[2];
            p1 = seg[4] - seg[5] + seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1c:
            lo = (float)(((int)pc[2] - 0xaa) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0xaa) * 3) + xf->f[4];
            p0 = seg[0] - seg[1] - seg[2];
            p1 = seg[4] - seg[5] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x20: case 0x21: case 0x22:
            axis = op - 0x20;
            lo = (float)pc[1] - xf->f[axis];
            hi = ((float)pc[1] + kOne) + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipA = pc[2];
            pc += 3;
            skipB = 0;
            break;
        case 0x23: case 0x24: case 0x25:
            axis = op - 0x23;
            lo = (float)pc[2] - xf->f[axis];
            hi = (float)pc[1] + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipB = (pc[3] << 8) + pc[4];
            skipA = (pc[5] << 8) + pc[6];
            pc += 7;
            break;
        case 0x26: case 0x27: case 0x28:
        case 0x29: case 0x2a: case 0x2b: {
            int a;
            float lo2, hi2, q0, q1;
            if (op < 0x29) {
                a = op - 0x26;
                lo2 = (float)pc[1] - xf->f[a];
                hi2 = (float)pc[2];
                pc += 3;
            } else {
                a = op - 0x29;
                unsigned v1 = ((pc[1] << 8) + pc[2]) * 0x100 + pc[3];
                unsigned v2 = ((pc[4] << 8) + pc[5]) * 0x100 + pc[6];
                lo2 = (((float)(int)v1 * m_errScale) * xf->m_scale - xf->o[a]) - xf->f[a];
                hi2 = ((float)(int)v2 * m_errScale) * xf->m_scale - xf->o[a];
                pc += 7;
            }
            hi2 = hi2 + xf->f[a];
            q0 = seg[a];
            q1 = seg[a + 4];
            int side;
            if (q1 <= q0) {
                if (q0 < lo2) return;
                if (hi2 < q1) return;
                side = 1;
            } else {
                if (q1 < lo2) return;
                if (hi2 < q0) return;
                side = 0;
            }
            __declspec(align(16)) float t0[8];
            t0[0] = seg[0]; t0[1] = seg[1]; t0[2] = seg[2]; t0[3] = seg[3];
            float d = q0 - hi2;
            t0[4] = seg[4]; t0[5] = seg[5]; t0[6] = seg[6]; t0[7] = seg[7];
            if (d * (q1 - hi2) < kZero) {
                float* dst = seg + (4 - side * 4);
                dst[0] = t0[0] * (kOne - (d / (d - (q1 - hi2)))) + t0[4] * (d / (d - (q1 - hi2)));
                dst[1] = t0[1] * (kOne - (d / (d - (q1 - hi2)))) + t0[5] * (d / (d - (q1 - hi2)));
                dst[2] = t0[2] * (kOne - (d / (d - (q1 - hi2)))) + t0[6] * (d / (d - (q1 - hi2)));
                dst[3] = t0[3] * (kOne - (d / (d - (q1 - hi2)))) + t0[7] * (d / (d - (q1 - hi2)));
            }
            d = q0 - lo2;
            if (d * (q1 - lo2) < kZero) {
                float* dst = seg + side * 4;
                dst[0] = t0[0] * (kOne - (d / (d - (q1 - lo2)))) + t0[4] * (d / (d - (q1 - lo2)));
                dst[1] = t0[1] * (kOne - (d / (d - (q1 - lo2)))) + t0[5] * (d / (d - (q1 - lo2)));
                dst[2] = t0[2] * (kOne - (d / (d - (q1 - lo2)))) + t0[6] * (d / (d - (q1 - lo2)));
                dst[3] = t0[3] * (kOne - (d / (d - (q1 - lo2)))) + t0[7] * (d / (d - (q1 - lo2)));
            }
            continue;
        }
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
        case 0x50: case 0x51: case 0x52: case 0x53: {
            unsigned v;
            if (op < 0x50)
                v = op - 0x30;
            else if (op == 0x50)
                v = pc[1];
            else if (op == 0x51)
                v = (pc[1] << 8) + pc[2];
            else if (op == 0x52)
                v = ((pc[1] << 8) + pc[2]) * 0x100 + pc[3];
            else
                v = (((pc[1] << 8) + pc[2]) << 16) + pc[4] + (pc[3] << 8);
            int key = v + xf->m_primOffset;
            hkMoppQueryInput* in = m_in;
            hkMoppContainer* container = (hkMoppContainer*)(*(char***)in->m_c)[3];
            hkMoppDispatch* disp = in->m_a;
            if (!disp->m_filter->check(disp, in->m_b, in->m_c, container, key))
                return;
            char buf[0x100];
            hkMoppChildRef ref;
            ref.m_shape = container->getChildShape(key, buf);
            ref.m_key = key;
            ref.m_a = ((uint32_t*)in->m_c)[2];
            ref.m_b = (uint32_t)in->m_c;
            int type = ref.m_shape->getType();
            char* tbl = *(char**)in->m_a;
            hkMoppHitFn fn = ((hkMoppHitFn*)tbl)[(*(uint8_t*)(tbl + m_axisIdx * 0x20 + 0x190 + type) + 0x7b) * 5];
            fn(in->m_b, &ref, in->m_a, m_hit, m_out);
            m_frac = m_hit->frac;
            return;
        }
        case 0x60: case 0x61: case 0x62: case 0x63: {
            local.m_prop[op - 0x60] = pc[1];
            pc += 2;
            goto setProp;
        }
        case 0x64: case 0x65: case 0x66: case 0x67:
            local.m_prop[op - 0x64] = (pc[1] << 8) + pc[2];
            pc += 3;
            goto setProp;
        case 0x68: case 0x69: case 0x6a: case 0x6b:
            local.m_prop[op - 0x68] = (((pc[1] << 8) + pc[2]) * 0x100 + pc[3]) * 0x100 + pc[4];
            pc += 5;
        setProp: {
            uint32_t p0v = local.m_prop[0];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_prop[0] = p0v;
            continue;
        }
        default: {
            char buf[0x200];
            hkOstream os(buf, 0x200, true);
            os << "Unknown command - This mopp data has been corrupted (check for memory trashing), or an hkMoppBvTreeShape has been pointed at invalid mopp data.\n";
            g_hkError->message(3, 0x1298fedd, buf, ".\\collide\\mopp\\machine\\hkMoppAabbCastVirtualMachine.cpp", 0x1c7);
            continue;
        }
        }

        // interval test on the selected axis / combination
        if (lo <= p1 || lo <= p0) {
            pc += skipA;
            if (p0 <= hi || p1 <= hi) {
                __declspec(align(16)) float t0[8];
                t0[0] = seg[0]; t0[1] = seg[1]; t0[2] = seg[2]; t0[3] = seg[3];
                float d0 = p0 - hi;
                t0[4] = seg[4]; t0[5] = seg[5]; t0[6] = seg[6]; t0[7] = seg[7];
                float d1 = p0 - lo;
                float d2 = p1 - hi;
                float d3 = p1 - lo;
                if (d2 <= d0) {
                    if (d3 * d1 < kZero) {
                        t0[4] = (kOne - (d1 / (d1 - d3))) * seg[0] + (d1 / (d1 - d3)) * seg[4];
                        t0[5] = (d1 / (d1 - d3)) * seg[5] + (kOne - (d1 / (d1 - d3))) * seg[1];
                        t0[6] = (d1 / (d1 - d3)) * seg[6] + (kOne - (d1 / (d1 - d3))) * seg[2];
                        t0[7] = (d1 / (d1 - d3)) * seg[7] + (kOne - (d1 / (d1 - d3))) * seg[3];
                    }
                    cast(xf, pc, t0);
                    if (d2 * d0 < kZero) {
                        seg[0] = (d0 / (d0 - d2)) * seg[4] + (kOne - (d0 / (d0 - d2))) * seg[0];
                        seg[1] = (d0 / (d0 - d2)) * seg[5] + (kOne - (d0 / (d0 - d2))) * seg[1];
                        seg[2] = (d0 / (d0 - d2)) * seg[6] + (kOne - (d0 / (d0 - d2))) * seg[2];
                        seg[3] = (d0 / (d0 - d2)) * seg[7] + (kOne - (d0 / (d0 - d2))) * seg[3];
                    }
                    if (m_frac < m_best) {
                        float* in = m_in->p;
                        m_best = m_frac;
                        __declspec(align(16)) float p[4];
                        p[0] = (kOne - m_frac) * in[0] + m_frac * in[4];
                        p[1] = (kOne - m_frac) * in[1] + m_frac * in[5];
                        p[2] = (kOne - m_frac) * in[2] + m_frac * in[6];
                        const float* base = m_info->v;
                        seg[4] = p[0] - base[0];
                        seg[5] = p[1] - base[1];
                        seg[6] = p[2] - base[2];
                        seg[7] = ((kOne - m_frac) * in[3] + m_frac * in[7]) - base[3];
                        float s = xf->m_scale;
                        seg[4] = s * seg[4];
                        seg[5] = s * seg[5];
                        seg[6] = s * seg[6];
                        seg[7] = s * seg[7];
                        seg[4] = seg[4] - xf->o[0];
                        seg[5] = seg[5] - xf->o[1];
                        seg[6] = seg[6] - xf->o[2];
                        seg[7] = seg[7] - xf->o[3];
                        if (axis < 3 && hi < seg[axis + 4])
                            return;
                    }
                    pc += skipB - skipA;
                } else {
                    if (d2 * d0 < kZero) {
                        t0[4] = (d0 / (d0 - d2)) * seg[4] + (kOne - (d0 / (d0 - d2))) * seg[0];
                        t0[5] = (kOne - (d0 / (d0 - d2))) * seg[1] + (d0 / (d0 - d2)) * seg[5];
                        t0[6] = (kOne - (d0 / (d0 - d2))) * seg[2] + (d0 / (d0 - d2)) * seg[6];
                        t0[7] = (kOne - (d0 / (d0 - d2))) * seg[3] + (d0 / (d0 - d2)) * seg[7];
                    }
                    cast(xf, pc + (skipB - skipA), t0);
                    if (d3 * d1 < kZero) {
                        seg[0] = (kOne - (d1 / (d1 - d3))) * seg[0] + (d1 / (d1 - d3)) * seg[4];
                        seg[1] = (kOne - (d1 / (d1 - d3))) * seg[1] + (d1 / (d1 - d3)) * seg[5];
                        seg[2] = (kOne - (d1 / (d1 - d3))) * seg[2] + (d1 / (d1 - d3)) * seg[6];
                        seg[3] = (kOne - (d1 / (d1 - d3))) * seg[3] + (d1 / (d1 - d3)) * seg[7];
                    }
                    if (m_frac < m_best) {
                        float* in = m_in->p;
                        m_best = m_frac;
                        __declspec(align(16)) float p[4];
                        p[0] = (kOne - m_frac) * in[0] + m_frac * in[4];
                        p[1] = (kOne - m_frac) * in[1] + m_frac * in[5];
                        p[2] = (kOne - m_frac) * in[2] + m_frac * in[6];
                        const float* base = m_info->v;
                        seg[4] = p[0] - base[0];
                        seg[5] = p[1] - base[1];
                        seg[6] = p[2] - base[2];
                        seg[7] = ((kOne - m_frac) * in[3] + m_frac * in[7]) - base[3];
                        float s = xf->m_scale;
                        seg[4] = s * seg[4];
                        seg[5] = s * seg[5];
                        seg[6] = s * seg[6];
                        seg[7] = s * seg[7];
                        seg[4] = seg[4] - xf->o[0];
                        seg[5] = seg[5] - xf->o[1];
                        seg[6] = seg[6] - xf->o[2];
                        seg[7] = seg[7] - xf->o[3];
                        if (axis < 3 && !(seg[axis + 4] >= lo))
                            return;
                    }
                }
            }
        } else {
            pc += skipB;
        }
    }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkMoppXform {
    void assign(int&); // 0x01114310
};
}
