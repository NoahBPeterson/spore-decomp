// Slice s0120ae50 -- Havok hkMatrix6 helpers, hkUnaryAction/hkBinaryAction, and
// RenderWare DocMessage debug-output helpers.
//
// The hkMatrix6 float kernels (582/260/347/1384 B) are reconstructed from their
// unrolled source form; the exception-cleanup fragments at 0x0120bcb0..0x0120c360
// are compiler-generated EH funclets (no prologue; they read the enclosing
// function's frame through EBP) and are recorded as partial in partial.txt.
#include "types.h"

extern "C" {
__declspec(dllimport) int __cdecl _vsnprintf(char*, unsigned int, const char*, void*);
__declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
}

void FUN_01086030(void*);          // hkWorld::removeActionImmediately
void* hkReferencedObject_addReference(void*);   // 0x01082590
void  hkWorldObject_removeReference(void*);     // 0x0109ae60
void FUN_011e090c();
void FUN_00680930(void*);
void FUN_00680730(void*);
void FUN_0067e0f0();
void FUN_00472540(void*);
void FUN_00f47410(void*, const char*, int, int, int, int);
void FUN_01081c30(float*, int, int);   // hkMatrix6 4x4 block multiply-accumulate

#define HK_ARRAY_CAPACITY_MASK 0x3fffffff
void hkArrayUtil_reserveMore(void* a, int elemSize);   // 0x0107f530

template <typename T>
struct hkArray
{
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
    void pushBack(const T& t)
    {
        if (m_size == getCapacity())
            hkArrayUtil_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
};

struct hkEntity
{
    virtual ~hkEntity();
    void addReference();      // 0x01082590
    void removeReference();   // 0x0109ae60
};

struct hkReferencedObject
{
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(void*) const {}
    short m_memSizeAndFlags;   // +4
    short m_referenceCount;    // +6
    hkReferencedObject() { m_referenceCount = 1; }
};

struct hkAction : hkReferencedObject
{
    int m_pad8;                // +8
    int m_padc;                // +0xc
    unsigned int m_userData;   // +0x10
    int m_pad14;               // +0x14
    virtual void getEntities(hkArray<hkEntity*>&) {}
};

struct hkUnaryAction : hkAction
{
    hkEntity* m_entity;        // +0x18
    hkUnaryAction(hkEntity* e, unsigned int u);
    ~hkUnaryAction();
    void getEntities(hkArray<hkEntity*>& out);
    void removeFromWorld();
};

struct hkBinaryAction : hkAction
{
    hkEntity* m_entityA;       // +0x18
    hkEntity* m_entityB;       // +0x1c
    hkBinaryAction(hkEntity* a, hkEntity* b, unsigned int u);
    ~hkBinaryAction();
    void getEntities(hkArray<hkEntity*>& out);
};

// @ 0x0120b890
hkUnaryAction::hkUnaryAction(hkEntity* e, unsigned int u)
{
    m_pad8 = 0;
    m_padc = 0;
    m_userData = u;
    m_pad14 = 0;
    m_entity = e;
    if (e)
        e->addReference();
}

// @ 0x0120b8d0
void hkUnaryAction::removeFromWorld()
{
    if (m_pad8 != 0)
        FUN_01086030(this);
}

// @ 0x0120b8f0
hkUnaryAction::~hkUnaryAction()
{
    if (m_entity)
    {
        hkWorldObject_removeReference(m_entity);
        m_entity = 0;
    }
}

// @ 0x0120b920
void hkUnaryAction::getEntities(hkArray<hkEntity*>& out)
{
    out.pushBack(m_entity);
}

// @ 0x0120b960
hkBinaryAction::hkBinaryAction(hkEntity* a, hkEntity* b, unsigned int u)
{
    m_pad8 = 0;
    m_padc = 0;
    m_userData = u;
    m_pad14 = 0;
    m_entityA = a;
    m_entityB = b;
    if (a)
        a->addReference();
    if (b)
        b->addReference();
}

// @ 0x0120b9c0
hkBinaryAction::~hkBinaryAction()
{
    if (m_entityA)
    {
        hkWorldObject_removeReference(m_entityA);
        m_entityA = 0;
    }
    if (m_entityB)
    {
        hkWorldObject_removeReference(m_entityB);
        m_entityB = 0;
    }
}

// @ 0x0120ba00
void hkBinaryAction::getEntities(hkArray<hkEntity*>& out)
{
    out.pushBack(m_entityA);
    out.pushBack(m_entityB);
}

// @ 0x0120bbf0
__declspec(noinline) void __cdecl f_0120bc40(char* buf, unsigned int size, const char* fmt, void* args);
void f_0120bbf0(unsigned int, unsigned int, unsigned int, const char* fmt, void* args)
{
    char buf[0x100];
    f_0120bc40(buf, 0x100, fmt, args);
    if (buf[0] != 0)
    {
        OutputDebugStringA(buf);
        OutputDebugStringA("\n");
    }
}

// @ 0x0120bc40
__declspec(noinline) void __cdecl f_0120bc40(char* buf, unsigned int size, const char* fmt, void* args)
{
    _vsnprintf(buf, size, fmt, args);
    buf[size - 1] = 0;
}

// ---------------------------------------------------------------------------
// Havok hkMatrix6 float kernels.  hkMatrix6 is a 0xc0-byte (48 float) matrix.
// ---------------------------------------------------------------------------

struct hkMatrix6;
struct hkMatrix6Ctor { void ctor(const hkMatrix6 *src); };   // 0x010ad140

// @ 0x0120ae50
extern "C" void _hkMatrix6Sub(float *param_1, const float *param_2)
{
    param_1[0] = param_1[0] - param_2[0];
    param_1[1] = param_1[1] - param_2[1];
    param_1[2] = param_1[2] - param_2[2];
    param_1[3] = param_1[3] - param_2[3];
    param_1[4] = param_1[4] - param_2[4];
    param_1[5] = param_1[5] - param_2[5];
    param_1[6] = param_1[6] - param_2[6];
    param_1[7] = param_1[7] - param_2[7];
    param_1[8] = param_1[8] - param_2[8];
    param_1[9] = param_1[9] - param_2[9];
    param_1[10] = param_1[10] - param_2[10];
    param_1[0xb] = param_1[0xb] - param_2[0xb];
    param_1[0xc] = param_1[0xc] - param_2[0xc];
    param_1[0xd] = param_1[0xd] - param_2[0xd];
    param_1[0xe] = param_1[0xe] - param_2[0xe];
    param_1[0xf] = param_1[0xf] - param_2[0xf];
    param_1[0x10] = param_1[0x10] - param_2[0x10];
    param_1[0x11] = param_1[0x11] - param_2[0x11];
    param_1[0x12] = param_1[0x12] - param_2[0x12];
    param_1[0x13] = param_1[0x13] - param_2[0x13];
    param_1[0x14] = param_1[0x14] - param_2[0x14];
    param_1[0x15] = param_1[0x15] - param_2[0x15];
    param_1[0x16] = param_1[0x16] - param_2[0x16];
    param_1[0x17] = param_1[0x17] - param_2[0x17];
    param_1[0x18] = param_1[0x18] - param_2[0x18];
    param_1[0x19] = param_1[0x19] - param_2[0x19];
    param_1[0x1a] = param_1[0x1a] - param_2[0x1a];
    param_1[0x1b] = param_1[0x1b] - param_2[0x1b];
    param_1[0x1c] = param_1[0x1c] - param_2[0x1c];
    param_1[0x1d] = param_1[0x1d] - param_2[0x1d];
    param_1[0x1e] = param_1[0x1e] - param_2[0x1e];
    param_1[0x1f] = param_1[0x1f] - param_2[0x1f];
    param_1[0x20] = param_1[0x20] - param_2[0x20];
    param_1[0x21] = param_1[0x21] - param_2[0x21];
    param_1[0x22] = param_1[0x22] - param_2[0x22];
    param_1[0x23] = param_1[0x23] - param_2[0x23];
    param_1[0x24] = param_1[0x24] - param_2[0x24];
    param_1[0x25] = param_1[0x25] - param_2[0x25];
    param_1[0x26] = param_1[0x26] - param_2[0x26];
    param_1[0x27] = param_1[0x27] - param_2[0x27];
    param_1[0x28] = param_1[0x28] - param_2[0x28];
    param_1[0x29] = param_1[0x29] - param_2[0x29];
    param_1[0x2a] = param_1[0x2a] - param_2[0x2a];
    param_1[0x2b] = param_1[0x2b] - param_2[0x2b];
    param_1[0x2c] = param_1[0x2c] - param_2[0x2c];
    param_1[0x2d] = param_1[0x2d] - param_2[0x2d];
    param_1[0x2e] = param_1[0x2e] - param_2[0x2e];
    param_1[0x2f] = param_1[0x2f] - param_2[0x2f];
}

// @ 0x0120b0a0
extern "C" void _hkMatrix6SetMul(int param_1, int param_2, int param_3)
{
    int iVar1;
    float *pfVar2;
    float *pfVar3;
    int local_4c;
    int local_48;
    int local_44;
    __declspec(align(16)) float local_40[12];

    local_4c = param_2;
    pfVar2 = (float *)(param_1 + 0x18);
    local_44 = 2;
    do
    {
        local_48 = 2;
        iVar1 = param_3;
        pfVar3 = pfVar2;
        do
        {
            FUN_01081c30(local_40, local_4c, iVar1);
            pfVar2 = pfVar3 - 6;
            FUN_01081c30(pfVar2, local_4c + 0x30, iVar1 + 0x60);
            iVar1 = iVar1 + 0x30;
            pfVar2[0] = local_40[0] + pfVar2[0];
            pfVar2 = pfVar3 + 0xc;
            local_48 = local_48 + -1;
            pfVar3[-5] = local_40[1] + pfVar3[-5];
            pfVar3[-4] = local_40[2] + pfVar3[-4];
            pfVar3[-3] = local_40[3] + pfVar3[-3];
            pfVar3[-2] = local_40[4] + pfVar3[-2];
            pfVar3[-1] = local_40[5] + pfVar3[-1];
            pfVar3[0] = local_40[6] + pfVar3[0];
            pfVar3[1] = local_40[7] + pfVar3[1];
            pfVar3[2] = local_40[8] + pfVar3[2];
            pfVar3[3] = local_40[9] + pfVar3[3];
            pfVar3[4] = local_40[10] + pfVar3[4];
            pfVar3[5] = local_40[11] + pfVar3[5];
            pfVar3 = pfVar2;
        } while (local_48 != 0);
        local_4c = local_4c + 0x60;
        local_44 = local_44 + -1;
    } while (local_44 != 0);
}

// @ 0x0120b1b0
extern "C" void _hkMatrix6SetTranspose(int *param_1, const int *param_2)
{
    param_1[0] = param_2[0];
    param_1[5] = param_2[5];
    param_1[10] = param_2[10];
    param_1[3] = 0;
    param_1[7] = 0;
    param_1[0xb] = 0;
    param_1[1] = param_2[4];
    param_1[4] = param_2[1];
    param_1[2] = param_2[8];
    param_1[8] = param_2[2];
    param_1[6] = param_2[9];
    param_1[9] = param_2[6];
    param_1[0xc] = param_2[0x18];
    param_1[0x11] = param_2[0x1d];
    param_1[0x16] = param_2[0x22];
    param_1[0xf] = 0;
    param_1[0x13] = 0;
    param_1[0x17] = 0;
    param_1[0xd] = param_2[0x1c];
    param_1[0x10] = param_2[0x19];
    param_1[0xe] = param_2[0x20];
    param_1[0x14] = param_2[0x1a];
    param_1[0x12] = param_2[0x21];
    param_1[0x15] = param_2[0x1e];
    param_1[0x18] = param_2[0xc];
    param_1[0x1d] = param_2[0x11];
    param_1[0x22] = param_2[0x16];
    param_1[0x1b] = 0;
    param_1[0x1f] = 0;
    param_1[0x23] = 0;
    param_1[0x19] = param_2[0x10];
    param_1[0x1c] = param_2[0xd];
    param_1[0x1a] = param_2[0x14];
    param_1[0x20] = param_2[0xe];
    param_1[0x1e] = param_2[0x15];
    param_1[0x21] = param_2[0x12];
    param_1[0x24] = param_2[0x24];
    param_1[0x29] = param_2[0x29];
    param_1[0x2e] = param_2[0x2e];
    param_1[0x27] = 0;
    param_1[0x2b] = 0;
    param_1[0x2f] = 0;
    param_1[0x25] = param_2[0x28];
    param_1[0x28] = param_2[0x25];
    param_1[0x26] = param_2[0x2c];
    param_1[0x2c] = param_2[0x26];
    param_1[0x2a] = param_2[0x2d];
    param_1[0x2d] = param_2[0x2a];
}

struct hkMatrix6
{
    int m[0x30];
    void setInvert(const hkMatrix6 &src);
};

// @ 0x0120b310
void hkMatrix6::setInvert(const hkMatrix6 &param_2)
{
    float fVar1;
    float *pfVar2;
    int iVar3, iVar4, iVar5, iVar6, iVar7, iVar8, iVar9, iVar10, iVar11;
    float *pfVar12, *pfVar13, *pfVar14;
    int iVar15;
    int local_114, local_110, local_108;
    float *local_104, *local_100;
    float local_d0[0x30];
    int *param_1 = m;

    ((hkMatrix6Ctor *)local_d0)->ctor(&param_2);

    param_1[0] = 0; param_1[1] = 0; param_1[2] = 0; param_1[3] = 0;
    param_1[4] = 0; param_1[5] = 0; param_1[6] = 0; param_1[7] = 0;
    param_1[8] = 0; param_1[9] = 0; param_1[10] = 0; param_1[0xb] = 0;
    param_1[0] = 0x3f800000;
    param_1[5] = 0x3f800000;
    param_1[10] = 0x3f800000;
    param_1[0xc] = 0; param_1[0xd] = 0; param_1[0xe] = 0; param_1[0xf] = 0;
    param_1[0x10] = 0; param_1[0x11] = 0; param_1[0x12] = 0; param_1[0x13] = 0;
    param_1[0x14] = 0; param_1[0x15] = 0; param_1[0x16] = 0; param_1[0x17] = 0;
    param_1[0x18] = 0; param_1[0x19] = 0; param_1[0x1a] = 0; param_1[0x1b] = 0;
    param_1[0x1c] = 0; param_1[0x1d] = 0; param_1[0x1e] = 0; param_1[0x1f] = 0;
    param_1[0x20] = 0; param_1[0x21] = 0; param_1[0x22] = 0; param_1[0x23] = 0;
    pfVar14 = (float *)(param_1 + 2);
    param_1[0x24] = 0; param_1[0x25] = 0; param_1[0x26] = 0; param_1[0x27] = 0;
    param_1[0x28] = 0; param_1[0x29] = 0; param_1[0x2a] = 0; param_1[0x2b] = 0;
    param_1[0x2c] = 0; param_1[0x2d] = 0; param_1[0x2e] = 0; param_1[0x2f] = 0;
    param_1[0x24] = 0x3f800000;
    param_1[0x29] = 0x3f800000;
    param_1[0x2e] = 0x3f800000;
    iVar3 = (int)local_d0 + (4 - (int)param_1);
    iVar4 = (int)local_d0 + (0xc - (int)param_1);
    iVar5 = (int)local_d0 + (0x10 - (int)param_1);
    local_110 = 0;
    iVar6 = (int)local_d0 + (0x14 - (int)param_1);
    iVar7 = (int)local_d0 + (0x1c - (int)param_1);
    iVar8 = (int)local_d0 + (0x20 - (int)param_1);
    iVar9 = (int)local_d0 + (0x24 - (int)param_1);
    iVar10 = (int)local_d0 + (8 - (int)param_1);
    iVar11 = (int)local_d0 + (0x18 - (int)param_1);
    local_104 = local_d0;
    pfVar12 = local_d0 + 2;
    iVar15 = (int)param_1 - (int)pfVar12;
    local_114 = 0;
    local_100 = local_104;
    while (true)
    {
        do
        {
            fVar1 = 1.0f / *local_104;
            local_108 = 0;
            pfVar13 = local_d0 + 2;
            pfVar12[-2] = fVar1 * pfVar12[-2];
            pfVar12[-1] = fVar1 * pfVar12[-1];
            *pfVar12 = fVar1 * *pfVar12;
            pfVar12[1] = fVar1 * pfVar12[1];
            pfVar12[0x16] = fVar1 * pfVar12[0x16];
            pfVar12[0x17] = fVar1 * pfVar12[0x17];
            pfVar12[0x18] = fVar1 * pfVar12[0x18];
            pfVar12[0x19] = fVar1 * pfVar12[0x19];
            *(float *)(iVar15 + (int)pfVar12) = fVar1 * *(float *)(iVar15 + (int)pfVar12);
            pfVar14[-1] = fVar1 * pfVar14[-1];
            *pfVar14 = fVar1 * *pfVar14;
            pfVar14[1] = fVar1 * pfVar14[1];
            pfVar14[0x16] = fVar1 * pfVar14[0x16];
            pfVar14[0x17] = fVar1 * pfVar14[0x17];
            pfVar14[0x18] = fVar1 * pfVar14[0x18];
            pfVar14[0x19] = fVar1 * pfVar14[0x19];
            pfVar2 = (float *)(param_1 + 0x1a);
            do
            {
                if ((local_108 != local_110) || (local_114 != 0))
                {
                    fVar1 = -local_d0[local_114 + (local_108 + local_110 * 2) * 0xc];
                    pfVar13[-2] = fVar1 * pfVar12[-2] + pfVar13[-2];
                    pfVar13[-1] = fVar1 * pfVar12[-1] + pfVar13[-1];
                    *pfVar13 = fVar1 * *pfVar12 + *pfVar13;
                    pfVar13[1] = fVar1 * pfVar12[1] + pfVar13[1];
                    pfVar13[0x16] = fVar1 * pfVar12[0x16] + pfVar13[0x16];
                    pfVar13[0x17] = fVar1 * pfVar12[0x17] + pfVar13[0x17];
                    *(float *)((int)pfVar2 + ((int)local_d0 - (int)param_1)) =
                        fVar1 * pfVar12[0x18] + *(float *)((int)pfVar2 + ((int)local_d0 - (int)param_1));
                    *(float *)((int)pfVar2 + iVar3) = fVar1 * pfVar12[0x19] + *(float *)((int)pfVar2 + iVar3);
                    pfVar2[-0x1a] = fVar1 * *(float *)(iVar15 + (int)pfVar12) + pfVar2[-0x1a];
                    pfVar2[-0x19] = fVar1 * *(float *)(iVar15 + 4 + (int)pfVar12) + pfVar2[-0x19];
                    pfVar2[-0x18] = fVar1 * *(float *)(iVar15 + 8 + (int)pfVar12) + pfVar2[-0x18];
                    pfVar2[-0x17] = fVar1 * *(float *)(iVar15 + 0xc + (int)pfVar12) + pfVar2[-0x17];
                    pfVar2[-2] = fVar1 * pfVar14[0x16] + pfVar2[-2];
                    pfVar2[-1] = fVar1 * pfVar14[0x17] + pfVar2[-1];
                    *pfVar2 = fVar1 * pfVar14[0x18] + *pfVar2;
                    pfVar2[1] = fVar1 * pfVar14[0x19] + pfVar2[1];
                }
                if ((local_108 != local_110) || (local_114 != 1))
                {
                    fVar1 = -local_d0[local_114 + (local_108 + local_110 * 2) * 0xc + 4];
                    pfVar13[2] = fVar1 * pfVar12[-2] + pfVar13[2];
                    pfVar13[3] = fVar1 * pfVar12[-1] + pfVar13[3];
                    pfVar13[4] = fVar1 * *pfVar12 + pfVar13[4];
                    pfVar13[5] = fVar1 * pfVar12[1] + pfVar13[5];
                    *(float *)((int)pfVar2 + iVar10) = fVar1 * pfVar12[0x16] + *(float *)((int)pfVar2 + iVar10);
                    *(float *)((int)pfVar2 + iVar4) = fVar1 * pfVar12[0x17] + *(float *)((int)pfVar2 + iVar4);
                    *(float *)((int)pfVar2 + iVar5) = fVar1 * pfVar12[0x18] + *(float *)((int)pfVar2 + iVar5);
                    *(float *)((int)pfVar2 + iVar6) = fVar1 * pfVar12[0x19] + *(float *)((int)pfVar2 + iVar6);
                    pfVar2[-0x16] = fVar1 * *(float *)(iVar15 + (int)pfVar12) + pfVar2[-0x16];
                    pfVar2[-0x15] = fVar1 * *(float *)(iVar15 + 4 + (int)pfVar12) + pfVar2[-0x15];
                    pfVar2[-0x14] = fVar1 * *(float *)(iVar15 + 8 + (int)pfVar12) + pfVar2[-0x14];
                    pfVar2[-0x13] = fVar1 * *(float *)(iVar15 + 0xc + (int)pfVar12) + pfVar2[-0x13];
                    pfVar2[2] = fVar1 * pfVar14[0x16] + pfVar2[2];
                    pfVar2[3] = fVar1 * pfVar14[0x17] + pfVar2[3];
                    pfVar2[4] = fVar1 * pfVar14[0x18] + pfVar2[4];
                    pfVar2[5] = fVar1 * pfVar14[0x19] + pfVar2[5];
                }
                if ((local_108 != local_110) || (local_114 != 2))
                {
                    fVar1 = -local_d0[local_114 + (local_108 + local_110 * 2) * 0xc + 8];
                    pfVar13[6] = fVar1 * pfVar12[-2] + pfVar13[6];
                    pfVar13[7] = fVar1 * pfVar12[-1] + pfVar13[7];
                    pfVar13[8] = fVar1 * *pfVar12 + pfVar13[8];
                    pfVar13[9] = fVar1 * pfVar12[1] + pfVar13[9];
                    *(float *)((int)pfVar2 + iVar11) = fVar1 * pfVar12[0x16] + *(float *)((int)pfVar2 + iVar11);
                    *(float *)((int)pfVar2 + iVar7) = fVar1 * pfVar12[0x17] + *(float *)((int)pfVar2 + iVar7);
                    *(float *)((int)pfVar2 + iVar8) = fVar1 * pfVar12[0x18] + *(float *)((int)pfVar2 + iVar8);
                    *(float *)((int)pfVar2 + iVar9) = fVar1 * pfVar12[0x19] + *(float *)((int)pfVar2 + iVar9);
                    pfVar2[-0x12] = fVar1 * *(float *)(iVar15 + (int)pfVar12) + pfVar2[-0x12];
                    pfVar2[-0x11] = fVar1 * *(float *)(iVar15 + 4 + (int)pfVar12) + pfVar2[-0x11];
                    pfVar2[-0x10] = fVar1 * *(float *)(iVar15 + 8 + (int)pfVar12) + pfVar2[-0x10];
                    pfVar2[-0xf] = fVar1 * *(float *)(iVar15 + 0xc + (int)pfVar12) + pfVar2[-0xf];
                    pfVar2[6] = fVar1 * pfVar14[0x16] + pfVar2[6];
                    pfVar2[7] = fVar1 * pfVar14[0x17] + pfVar2[7];
                    pfVar2[8] = fVar1 * pfVar14[0x18] + pfVar2[8];
                    pfVar2[9] = fVar1 * pfVar14[0x19] + pfVar2[9];
                }
                local_108 = local_108 + 1;
                pfVar13 = pfVar13 + 0xc;
                pfVar2 = pfVar2 + 0xc;
            } while (local_108 < 2);
            local_114 = local_114 + 1;
            local_104 = local_104 + 5;
            pfVar12 = pfVar12 + 4;
            pfVar14 = pfVar14 + 4;
        } while (local_114 < 3);
        local_110 = local_110 + 1;
        local_104 = local_100 + 0x24;
        if (1 < local_110)
            break;
        local_114 = 0;
        local_100 = local_104;
    }
}

// ---------------------------------------------------------------------------
// RenderWare DocMessage debug dispatch.
// ---------------------------------------------------------------------------

typedef void (__cdecl *DocHandler)(unsigned, unsigned, unsigned, const char *, void *);
extern unsigned int g_docInitFlag;   // 0x171e744
extern DocHandler   g_docHandler;    // 0x171e740
extern DocHandler  *g_docShared;     // 0x171e73c

// @ 0x0120bb70
void __cdecl f_0120bb70(unsigned int *param_1, unsigned int param_2, unsigned int param_3, ...)
{
    DocHandler *slot;
    unsigned int flag = g_docInitFlag;

    if ((flag & 1) == 0)
    {
        flag = flag | 1;
        g_docInitFlag = flag;
        g_docHandler = &f_0120bbf0;
    }
    slot = g_docShared ? (DocHandler *)g_docShared : &g_docHandler;
    if (*slot != 0)
    {
        unsigned int *p = param_1;
        if ((flag & 1) == 0)
        {
            flag = flag | 1;
            g_docInitFlag = flag;
            g_docHandler = &f_0120bbf0;
        }
        slot = g_docShared ? g_docShared : &g_docHandler;
        (*slot)(p[0], p[1], param_2, (const char *)param_3, (void *)(&param_3 + 1));
    }
}

// @ 0x0120bcb0
void __cdecl FUN_0120bcb0() {}

// @ 0x0120bd30
void __cdecl FUN_0120bd30() {}

// @ 0x0120be20
void __cdecl FUN_0120be20() {}

// @ 0x0120be90
void __cdecl FUN_0120be90() {}

void f_0120bf00() {}   // @ 0x0120bf00  EH cleanup fragment
void f_0120bfc0() {}   // @ 0x0120bfc0  EH cleanup fragment
void f_0120c0f0() {}   // @ 0x0120c0f0  EH cleanup fragment
void f_0120c2a0() {}   // @ 0x0120c2a0  EH cleanup fragment
void f_0120c330() {}   // @ 0x0120c330  EH cleanup fragment
void f_0120c360() {}   // @ 0x0120c360  EH cleanup fragment
