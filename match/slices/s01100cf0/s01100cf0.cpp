// Slice s01100cf0 (batch cl2 #513): 0x011014d0 hkMoppObbVirtualMachine::queryObb (Havok 3.1),
// the recursive MOPP bytecode walker for an integer OBB/AABB query. Emits primitive ids into
// an hkArray<unsigned int>. Same family as s01102010 (hkMoppLongRayVirtualMachine::queryRay).
// Flags: /O2 /MD /Gy /TP (no /EHsc: no EH frame in the original)
#include "types.h"

struct hkBool {
    char m_b;
    hkBool() {}
    hkBool(bool b) : m_b(b) {}
    operator bool() const { return m_b != 0; }
};

struct hkOstream {
    hkOstream(char* buf, int size, hkBool flag);      // 0x0107EF80
    ~hkOstream();                                      // 0x0107EFD0
    hkOstream& operator<<(const char* s);              // 0x0107EE30
};
struct hkError {
    virtual void v0(); virtual void v1();
    virtual int message(int level, int id, const char* desc, const char* file, int line);   // slot 2
    static hkError* s_instance;      // 0x016e4184
};

extern "C" char hkSolverCheckKeycode(int);   // 0x010bfbe0
extern char g_hkKeycodeOk;                   // 0x016e5abf

struct hkUintArray {
    unsigned int* m_data;
    int m_size;
    int m_capacityAndFlags;
    static void reserveMore(void* array, int elemSize);   // 0x0107F530 (hkArrayUtil::_reserveMore, cdecl)
    void pushBack(unsigned int e)
    {
        if (m_size == (m_capacityAndFlags & 0x3fffffff))
            reserveMore(this, 4);
        m_data[m_size++] = e;
    }
};

// MOPP traversal state: 14 live dwords copied between levels, then 3 extra register dwords.
struct hkMoppObbState {
    int m_hi[3];         // +0x00 query max, relative to the current cell origin (+1 applied)
    int m_pad0c;
    int m_lo[3];         // +0x10 query min, relative to the current cell origin
    int m_pad1c;
    int m_org[3];        // +0x20 current cell origin
    int m_primOffset;    // +0x2c
    int m_shift;         // +0x30
    int m_reg[4];        // +0x34 (only reg0 is part of the 14-dword copy)
    void copyFrom(const hkMoppObbState& s)
    {
        int* d = (int*)this;
        const int* c = (const int*)&s;
        for (int i = 0; i < 14; i++) d[i] = c[i];
    }
};

struct hkMoppObbVirtualMachine {
    hkUintArray* m_primitives;      // +0x00
    int m_pad04[3];
    int m_hi[3];                    // +0x10
    int m_pad1c;
    int m_lo[3];                    // +0x20
    void queryObb(const hkMoppObbState* st, const unsigned char* p);
};

void hkMoppObbVirtualMachine::queryObb(const hkMoppObbState* st, const unsigned char* p)
{
    hkMoppObbState local;
    int extraRegs[3];
    char textBuf[0x200];
    (void)extraRegs;

    if (!g_hkKeycodeOk) {
        g_hkKeycodeOk = hkSolverCheckKeycode(4);
        if (!g_hkKeycodeOk) return;
    }

    for (;;) {
        unsigned int op = p[0];
        int A, C, D, E;
        unsigned int emit;

        switch (op) {
        case 0:
            return;
        case 1: case 2: case 3: case 4: {
            int sh = (int)op;
            local.m_org[0] = (p[1] + st->m_org[0]) << sh;
            local.m_org[1] = (p[2] + st->m_org[1]) << sh;
            local.m_org[2] = (p[3] + st->m_org[2]) << sh;
            local.m_shift = st->m_shift + (int)op;
            int rs = 0x10 - local.m_shift;
            local.m_lo[0] = (m_lo[0] >> rs) - local.m_org[0];
            local.m_lo[1] = (m_lo[1] >> rs) - local.m_org[1];
            local.m_lo[2] = (m_lo[2] >> rs) - local.m_org[2];
            local.m_hi[0] = ((m_hi[0] >> rs) + 1) - local.m_org[0];
            local.m_hi[1] = ((m_hi[1] >> rs) + 1) - local.m_org[1];
            local.m_hi[2] = ((m_hi[2] >> rs) + 1) - local.m_org[2];
            local.m_reg[0] = st->m_reg[0];
            local.m_primOffset = st->m_primOffset;
            st = &local;
            p += 4;
            continue;
        }
        case 5: p += p[1] + 2; continue;
        case 6: p += (unsigned int)p[1] * 0x100 + p[2] + 3; continue;
        case 7: p += (unsigned int)((p[1] << 8) | p[2]) * 0x100 + p[3] + 4; continue;
        case 9: {
            unsigned int v = p[1];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 2;
            continue;
        }
        case 10: {
            unsigned int v = (p[1] << 8) | p[2];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset += v;
            p += 3;
            continue;
        }
        case 0xb: {
            unsigned int v = (((((p[1] << 8) | p[2]) << 8) | p[3]) << 8) | p[4];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_primOffset = (int)v;
            p += 5;
            continue;
        }
        case 0x10: case 0x11: case 0x12: {
            const int* s = (const int*)st;
            int lo = s[op - 0xc];
            if ((int)p[2] < s[op - 0x10]) {
                const unsigned char* q = p + 4 + p[3];
                if (lo < (int)p[1])
                    queryObb(st, p + 4);
                p = q;
            } else {
                if ((int)p[1] <= lo) return;
                p += 4;
            }
            continue;
        }
        case 0x13:
            A = st->m_lo[2] + st->m_lo[1]; C = st->m_hi[2] + st->m_hi[1];
            D = p[1] << 1; E = p[2] << 1;
            break;
        case 0x14:
            A = st->m_lo[1] - st->m_hi[2]; C = st->m_hi[1] - st->m_lo[2];
            D = p[1] * 2 - 0xff; E = p[2] * 2 - 0xff;
            break;
        case 0x15:
            A = st->m_lo[2] + st->m_lo[0]; C = st->m_hi[2] + st->m_hi[0];
            D = p[1] << 1; E = p[2] << 1;
            break;
        case 0x16:
            A = st->m_lo[0] - st->m_hi[2]; C = st->m_hi[0] - st->m_lo[2];
            D = p[1] * 2 - 0xff; E = p[2] * 2 - 0xff;
            break;
        case 0x17:
            A = st->m_lo[1] + st->m_lo[0]; C = st->m_hi[1] + st->m_hi[0];
            D = p[1] << 1; E = p[2] << 1;
            break;
        case 0x18:
            A = st->m_lo[0] - st->m_hi[1]; C = (st->m_hi[0] - st->m_lo[1]);
            D = p[1] * 2 - 0xff; E = p[2] * 2 - 0xff;
            break;
        case 0x19:
            D = p[1] * 3; E = p[2] * 3;
            A = st->m_lo[2] + st->m_lo[1] + st->m_lo[0];
            C = st->m_hi[2] + st->m_hi[1] + st->m_hi[0];
            break;
        case 0x1a:
            D = (p[1] - 0x55) * 3; E = (p[2] - 0x55) * 3;
            A = (st->m_lo[1] - st->m_hi[2]) + st->m_lo[0];
            C = (st->m_hi[1] - st->m_lo[2]) + st->m_hi[0];
            break;
        case 0x1b:
            D = (p[1] - 0x55) * 3; E = (p[2] - 0x55) * 3;
            A = (st->m_lo[2] - st->m_hi[1]) + st->m_lo[0];
            C = (st->m_hi[2] - st->m_lo[1]) + st->m_hi[0];
            break;
        case 0x1c:
            D = (p[1] - 0xaa) * 3; E = (p[2] - 0xaa) * 3;
            A = (st->m_lo[0] - st->m_hi[2]) - st->m_hi[1];
            C = (st->m_hi[0] - st->m_lo[2]) - st->m_lo[1];
            break;
        case 0x20: case 0x21: case 0x22: {
            const int* s = (const int*)st;
            const unsigned char* q = p + 3;
            if ((int)p[1] < s[op - 0x20]) {
                q = p + 3 + p[2];
                if (s[op - 0x1c] <= (int)p[1])
                    queryObb(st, p + 3);
            }
            p = q;
            continue;
        }
        case 0x23: case 0x24: case 0x25: {
            const int* s = (const int*)st;
            if ((int)p[2] < s[op - 0x23]) {
                int lim = p[1];
                unsigned int skipB = (p[5] << 8) | p[6];
                unsigned int skipA = (p[3] << 8) | p[4];
                p += skipB + 7;
                if (s[op - 0x1f] < lim)
                    queryObb(st, p + (skipA - skipB));
            } else {
                if ((int)p[1] <= s[op - 0x1f]) return;
                p += ((p[3] << 8) | p[4]) + 7;
            }
            continue;
        }
        case 0x26: case 0x27: case 0x28: {
            const int* s = (const int*)st;
            if (s[op - 0x26] < (int)p[1]) return;
            if ((int)p[2] <= s[op - 0x22]) return;
            p += 3;
            continue;
        }
        case 0x29: case 0x2a: case 0x2b: {
            const int* t = (const int*)this;
            if (t[op - 0x25] < (int)((((p[1] << 8) | p[2]) << 8) | p[3])) return;
            if ((int)((((p[4] << 8) | p[5]) << 8) | p[6]) < t[op - 0x21]) return;
            p += 7;
            continue;
        }
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
            emit = op - 0x30;
            goto doEmit;
        case 0x50:
            emit = p[1];
            goto doEmit;
        case 0x51:
            emit = (p[1] << 8) | p[2];
            goto doEmit;
        case 0x52:
            emit = (((p[1] << 8) | p[2]) << 8) | p[3];
            goto doEmit;
        case 0x53:
            emit = (((((p[1] << 8) | p[2]) << 8) | p[3]) << 8) | p[4];
            goto doEmit;
        case 0x60: case 0x61: case 0x62: case 0x63: {
            int keep;
            local.m_reg[op & 3] = p[1];
            p += 2;
            keep = local.m_reg[0];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_reg[0] = keep;
            continue;
        }
        case 0x64: case 0x65: case 0x66: case 0x67: {
            int keep;
            local.m_reg[op & 3] = (p[1] << 8) | p[2];
            p += 3;
            keep = local.m_reg[0];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_reg[0] = keep;
            continue;
        }
        case 0x68: case 0x69: case 0x6a: case 0x6b: {
            int keep;
            local.m_reg[op & 3] = (((((p[1] << 8) | p[2]) << 8) | p[3]) << 8) | p[4];
            p += 5;
            keep = local.m_reg[0];
            if (st != &local) { local.copyFrom(*st); st = &local; }
            local.m_reg[0] = keep;
            continue;
        }
        default: {
            hkOstream os(textBuf, 0x200, true);
            os << "Unknown command - This mopp data has been corrupted (check for memory trashing), or an hkMoppBvTreeShape has been pointed at invalid mopp data.\n";
            hkError::s_instance->message(3, 0x1298fedd, textBuf, ".\\collide\\mopp\\machine\\hkMoppObbVirtualMachine.cpp", 0x173);
            continue;
        }
        }

        // ops 0x13..0x1c: test the plane pair (A,C against D,E)
        p += 4;
        if (E < C) {
            unsigned int skip = p[-1];
            if (A < D)
                queryObb(st, p);
            p += skip;
        } else if (D <= A) {
            return;
        }
        continue;

    doEmit:
        m_primitives->pushBack(st->m_primOffset + emit);
        return;
    }
}
