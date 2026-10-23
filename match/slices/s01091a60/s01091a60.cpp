// s01091a60 -- Havok constraint-data methods (gold5 worker 4).
// Compiled with /O2 /MD /Gy /TP.

typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;

// ---------------------------------------------------------------------------
// hkBool -- returned by value through a hidden pointer (non-trivial class)
// ---------------------------------------------------------------------------
class hkBool {
public:
    char m_bool;
    hkBool(bool b) : m_bool((char)b) {}
};

class hkConstraintQueryIn;
class hkConstraintQueryOut;

extern void hkBeginConstraints(const hkConstraintQueryIn &in,
                               hkConstraintQueryOut &out, int n, int size);   // FUN_010aa080

// ===========================================================================
// 0x01091ff0  hkPulleyConstraintData::isValid
// ===========================================================================
class hkPulleyConstraintData {
public:
    hkBool isValid() const;
    void buildJacobian(const hkConstraintQueryIn &in,
                       hkConstraintQueryOut &out) const;
};

// @ 0x01091ff0
hkBool hkPulleyConstraintData::isValid() const
{
    if (*(const float *)((const char *)this + 0xc) <= 0.0f ||
        *(const float *)((const char *)this + 0x10) <= 0.0f) {
        return hkBool(false);
    }
    return hkBool(true);
}

// ===========================================================================
// 0x01092090  hkPulleyConstraintData::buildJacobian
// ===========================================================================
struct __declspec(align(16)) PulleyJacobianData {
    float posA[4];      // +0x00  transformed pivot A (w = 0)
    float posB[4];      // +0x10  transformed pivot B (w = 0)
    int   p[4];         // +0x20  this+0x40 .. this+0x4c
    int   q[4];         // +0x30  this+0x50 .. this+0x5c
    float f0;           // +0x40  this+0x0c
    float f1;           // +0x44  this+0x10
};

extern void hkPulleyConstraintBuildJacobian(const PulleyJacobianData *d,
                                            const hkConstraintQueryIn &in,
                                            hkConstraintQueryOut &out);

// @ 0x01092090
void hkPulleyConstraintData::buildJacobian(const hkConstraintQueryIn &in,
                                           hkConstraintQueryOut &out) const
{
    const char *c = (const char *)this;
    hkBeginConstraints(in, out, *(const int *)((const char *)&in + 0x44), 8);

    const float *mA = *(const float **)((const char *)&in + 0x30);
    const float *mB = *(const float **)((const char *)&in + 0x34);
    float x, y, z;

    PulleyJacobianData d;
    x = *(const float *)(c + 0x20);
    y = *(const float *)(c + 0x24);
    z = *(const float *)(c + 0x28);
    d.posA[0] = x * mA[0] + (y * mA[4] + z * mA[8]) + mA[0xc];
    d.posA[1] = x * mA[1] + (y * mA[5] + z * mA[9]) + mA[0xd];
    d.posA[2] = x * mA[2] + (y * mA[6] + z * mA[10]) + mA[0xe];
    d.posA[3] = 0.0f;
    x = *(const float *)(c + 0x30);
    y = *(const float *)(c + 0x34);
    z = *(const float *)(c + 0x38);
    d.posB[0] = x * mB[0] + (y * mB[4] + z * mB[8]) + mB[0xc];
    d.posB[1] = x * mB[1] + (y * mB[5] + z * mB[9]) + mB[0xd];
    d.posB[2] = x * mB[2] + (y * mB[6] + z * mB[10]) + mB[0xe];
    d.posB[3] = 0.0f;
    d.p[0] = *(const int *)(c + 0x40);
    d.p[1] = *(const int *)(c + 0x44);
    d.p[2] = *(const int *)(c + 0x48);
    d.p[3] = *(const int *)(c + 0x4c);
    d.q[0] = *(const int *)(c + 0x50);
    d.q[1] = *(const int *)(c + 0x54);
    d.q[2] = *(const int *)(c + 0x58);
    d.q[3] = *(const int *)(c + 0x5c);
    d.f0 = *(const float *)(c + 0xc);
    d.f1 = *(const float *)(c + 0x10);
    hkPulleyConstraintBuildJacobian(&d, in, out);
}

// ===========================================================================
// 0x010921f0  scalar deleting destructor
// ===========================================================================
struct hkRefCountedObject {
    virtual void __deleteThis(int flag) = 0;   // vtable slot 0
    ushort m_memSizeAndFlags;                  // +4
    ushort m_referenceCount;                   // +6
};

class hkMemory {
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void deallocate(void *p, uint size, int align) = 0;   // +0x14
};
extern hkMemory *g_hkMemory;                   // 0x016e4178

extern int vtbl_014a1aa8;
extern int vtbl_013ef094;

struct hkConstraintAtomBase {
    void *scalarDeletingDtor(byte flags);
};

// @ 0x010921f0
void *hkConstraintAtomBase::scalarDeletingDtor(byte flags)
{
    char *self = (char *)this;
    *(int *)self = (int)&vtbl_014a1aa8;
    hkRefCountedObject *p = *(hkRefCountedObject **)(self + 0xc);
    if (p != 0 && p->m_memSizeAndFlags != 0) {
        if (--p->m_referenceCount == 0) {
            p->__deleteThis(1);
        }
    }
    *(int *)self = (int)&vtbl_013ef094;
    if ((flags & 1) != 0) {
        g_hkMemory->deallocate(self, *(const ushort *)(self + 4), 0x29);
    }
    return self;
}

// ===========================================================================
// 0x01092270  hkPrismaticConstraintData::isValid
// ===========================================================================
class hkPrismaticConstraintData {
public:
    hkBool isValid() const;
};

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Fabs(float x) { return (float)fabs(x); }

// @ 0x01092270
hkBool hkPrismaticConstraintData::isValid() const
{
    const float *f = (const float *)this;
    float dot = f[0x80 / 4] * f[0x70 / 4] +
                (f[0x84 / 4] * f[0x74 / 4] + f[0x88 / 4] * f[0x78 / 4]);
    float n1 = f[0x80 / 4] * f[0x80 / 4] + f[0x84 / 4] * f[0x84 / 4] +
               f[0x88 / 4] * f[0x88 / 4];
    float n0 = f[0x70 / 4] * f[0x70 / 4] + f[0x74 / 4] * f[0x74 / 4] +
               f[0x78 / 4] * f[0x78 / 4];
    if (Fabs(dot) < 1.0e-5f &&
        Fabs(n1 - 1.0f) < 1.0e-5f &&
        Fabs(n0 - 1.0f) < 1.0e-5f &&
        f[0x90 / 4] <= f[0x94 / 4]) {
        return hkBool(true);
    }
    return hkBool(false);
}

// ===========================================================================
// 0x01091a60  hkRelativeOrientationConstraintData::buildJacobian
// ===========================================================================
class hkRelativeOrientationConstraintData {
public:
    virtual void buildJacobian(const hkConstraintQueryIn &in,
                               hkConstraintQueryOut &out) const;
};

struct hkQuaternion {
    float x, y, z, w;
    void set(const void *rotation);                            // FUN_01082490
    void setMul(const hkQuaternion &a, const hkQuaternion &b); // FUN_01082210
};

extern const float hk_identityBasis[12];                       // 0x015b9b20
extern const float hk_zero;                                    // 0x01485378

extern void hk1dAngularBilateralJacobian(const float *axis,
                                         const hkConstraintQueryIn &in,
                                         hkConstraintQueryOut &out);   // FUN_010aa1e0

// Builds three angular bilateral constraints: for each of the three basis
// rows it emits the axis taken from the relative rotation A*qB^-1, using a
// second axis derived from the untouched B rotation as the companion row.
// @ 0x01091a60
void hkRelativeOrientationConstraintData::buildJacobian(
        const hkConstraintQueryIn &in, hkConstraintQueryOut &out) const
{
    const char *self = (const char *)this;

    hkBeginConstraints(in, out, *(const int *)((const char *)&in + 0x44), 8);

    hkQuaternion qA, qB, qC;
    qA.set(*(const void **)((const char *)&in + 0x30));
    qB.set(*(const void **)((const char *)&in + 0x34));
    qC.setMul(qA, *(const hkQuaternion *)(self + 0x10));

    const float cx = qC.x, cy = qC.y, cz = qC.z, cw = qC.w;
    const float bx = qB.x, by = qB.y, bz = qB.z, bw = qB.w;

    float fVar1 = cw * cw;
    int   iVar8 = 2;
    const float *pfVar7 = hk_identityBasis + 2;
    int   local_f8 = 3;

    do {
        float axes[12];

        // ---- first axis: qC against basis row (iVar8 - 2) -----------------
        float fVar2 = cy * pfVar7[-1] + (cx * pfVar7[-2] + cz * pfVar7[0]);
        float v18   = cx * pfVar7[-1] - cy * pfVar7[-2];
        float a90 = cw * (cy * pfVar7[0] - cz * pfVar7[-1]) +
                    (fVar2 * cx + (fVar1 - 0.5f) * pfVar7[-2]);
        float a8c = (cz * pfVar7[-2] - cx * pfVar7[0]) * cw +
                    (cy * fVar2 + (fVar1 - 0.5f) * pfVar7[-1]);
        float a88 = v18 * cw + (cz * fVar2 + (fVar1 - 0.5f) * pfVar7[0]);
        float a84 = (cw * fVar2 + (fVar1 - 0.5f) * pfVar7[1]) + cw * hk_zero;
        axes[4] = a90 + a90;
        axes[5] = a8c + a8c;
        axes[6] = a88 + a88;
        axes[7] = a84 + a84;

        // ---- second axis: qC against basis row (iVar8 - 1); passed on -----
        int iVar4 = (iVar8 - 1) % 3;
        float v68 = fVar1 - 0.5f;
        float v64 = fVar1 - 0.5f;
        const float *pfVar5 = hk_identityBasis + iVar4 * 4;
        fVar2 = cy * pfVar5[1] + (cz * pfVar5[2] + cx * pfVar5[0]);
        int iVar6 = iVar8 % 3;
        float v48 = cx * pfVar5[1] - cy * pfVar5[0];
        float b0 = (cy * pfVar5[2] - cz * pfVar5[1]) * cw +
                   (fVar2 * cx + (fVar1 - 0.5f) * pfVar5[0]);
        float b1 = (cz * pfVar5[0] - cx * pfVar5[2]) * cw +
                   (cy * fVar2 + (fVar1 - 0.5f) * pfVar5[1]);
        float b2 = v48 * cw + (cz * fVar2 + v68 * pfVar5[2]);
        float b3 = (fVar2 * cw + v64 * pfVar5[3]) + cw * hk_zero;
        axes[0] = b0 + b0;
        axes[1] = b1 + b1;
        axes[2] = b2 + b2;
        axes[3] = b3 + b3;

        // ---- companion axis: qB against basis row iVar8 -------------------
        pfVar5 = hk_identityBasis + iVar6 * 4;
        float fVar2b = bw * bw;
        float fVar3 = by * pfVar5[1] + (bz * pfVar5[2] + bx * pfVar5[0]);
        float v38 = bx * pfVar5[1] - by * pfVar5[0];
        float c80 = bw * (by * pfVar5[2] - bz * pfVar5[1]) +
                    (fVar3 * bx + (fVar2b - 0.5f) * pfVar5[0]);
        float c7c = (bz * pfVar5[0] - bx * pfVar5[2]) * bw +
                    (by * fVar3 + (fVar2b - 0.5f) * pfVar5[1]);
        float c78 = v38 * bw + (bz * fVar3 + (fVar2b - 0.5f) * pfVar5[2]);
        float c74 = bw * hk_zero + (bw * fVar3 + (fVar2b - 0.5f) * pfVar5[3]);
        axes[8]  = c80 + c80;
        axes[9]  = c7c + c7c;
        axes[10] = c78 + c78;
        axes[11] = c74 + c74;

        hk1dAngularBilateralJacobian(axes, in, out);

        pfVar7 = pfVar7 + 4;
        iVar8 = iVar8 + 1;
        local_f8 = local_f8 - 1;
    } while (local_f8 != 0);
}
