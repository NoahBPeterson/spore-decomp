// s00b832d0: 8 functions, 0x00b832d0..0x00b841a0, SP::cPlanetModel surface/terrain helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (region has no stack cookies, no /EHsc)
#include "types.h"
#include <math.h>

#pragma warning(disable: 4100)

typedef unsigned int uint;

struct Vec3POD { float x, y, z; };

// Terrain map set (see s00b84270). Only the floats read here are named.
struct cTerrainMapSet {
    char pad0[0x34];
    float f34;                                  // mRadius
    float f38;                                  // mMaxHeight
    float f3c;                                  // mWaterHeight
    float GetHeightAt(const Vec3POD* pos);      // 0x00f927c0, thiscall ret 4
};

// Interface behind cPlanetModel::mpISphere (+0x24). Slot +0xC (index 3) returns a map set.
struct cITerrainSphere {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual cTerrainMapSet* s3();               // +0xC
};

struct cPlanetModel {
    char pad0[0x20];
    void* mpSphere;                             // +0x20
    cITerrainSphere* mpISphere;                 // +0x24
    char pad1[0x4c - 0x28];
    void* mpContinentMap;                       // +0x4c
    char pad2[0x7c - 0x50];
    void* mpBitmap;                             // +0x7c
    char pad3[0xf0 - 0x80];
    char mFlagF0;                               // +0xf0

    int FUN_00b832d0(const float* dir, float step);
    float FUN_00b83620(int a, float b);
    uint FUN_00b83870(int arg);
    void FUN_00b83c40(const float* dir, float radius, uint flags, char (*cb)(float*));
    void MakeRandomWorldPosition(Vec3POD* out, int a, float b, float c);
};

cPlanetModel* PlanetModel();                    // 0x00b3d350, cdecl
void QuaternionFromDirections(float* out, const float* a, const float* b); // 0x698180, cdecl
float* FUN_0059aed0(float* out, const float* m, const float* q);           // 0x59aed0, cdecl
void FUN_00ac1510(unsigned x, unsigned y, unsigned z, float* out);         // 0x00ac1510, cdecl
int FUN_00685450(int a, int* b, int c, void* out);                         // 0x685450, cdecl
void FUN_00b81630(Vec3POD* out, const Vec3POD* in);                        // 0x00b81630, cdecl
void* PropertyManager();                        // 0x67de30, cdecl
void* MessageServer();                          // 0x67dcc0, cdecl
void* operator_new(int size, const char* a, int b, int c, const char* d, int e);

extern const float kSpiralMaxAngle;             // 0x01688274
extern const Vec3POD kQuatRef;                  // 0x01688278
extern const float kBasis9[9];                  // 0x01688284
extern const float kNoTerrain;                  // 0x0156b624
extern const float kHeightUnit;                 // 0x0140d4f8
extern const float kOne;                        // 0x01485720
extern const float kHalf;                       // 0x01471064
extern const float kTwo;                        // 0x01470f1c
extern const float kNine;                       // 0x013f8734
extern const float kFifteen;                    // 0x01457e0c
extern const float kSmallEps;                   // 0x01485378
extern const float kCellScale;                  // 0x01688274 unused placeholder

// @ 0x00b832d0
int cPlanetModel::FUN_00b832d0(const float* dir, float step)
{
    float local_38 = dir[0];
    if ((dir[1] * dir[1] + dir[2] * dir[2]) + local_38 * local_38 != 0.0f) {
        float local_30 = 1.0f / (float)sqrt((double)((dir[1] * dir[1] + dir[2] * dir[2]) + local_38 * local_38));
        local_38 = local_38 * local_30;
        float local_34 = local_30 * dir[1];
        local_30 = local_30 * dir[2];
        float local_10[4];
        QuaternionFromDirections(local_10, (const float*)&kQuatRef, &local_38);
        float local_20[3];
        float* pfVar5 = FUN_0059aed0(local_20, kBasis9, local_10);
        float fVar1 = pfVar5[0];
        float fVar2 = pfVar5[1];
        float fVar3 = pfVar5[2];
        float angle = 0.0f;
        if (0.0f < kSpiralMaxAngle) {
            do {
                float s = (float)sin((double)(angle * 0.5f));
                float c = (float)cos((double)(angle * 0.5f));
                float fVar10 = local_34 * s;
                float fVar11 = local_30 * s;
                float fVar9 = s * local_38;
                float local_2c = ((c * fVar10 + fVar11 * fVar9) * fVar3 +
                                  (fVar10 * fVar9 - c * fVar11) * fVar2) * 2.0f +
                                 (1.0f - (fVar11 * fVar11 + fVar10 * fVar10) * 2.0f) * fVar1;
                float local_28 = ((fVar11 * fVar10 - c * fVar9) * fVar3 +
                                  (c * fVar11 + fVar10 * fVar9) * fVar1) * 2.0f +
                                 (1.0f - (fVar11 * fVar11 + fVar9 * fVar9) * 2.0f) * fVar2;
                float local_24 = ((c * fVar9 + fVar11 * fVar10) * fVar2 +
                                  (fVar11 * fVar9 - c * fVar10) * fVar1) * 2.0f +
                                 (1.0f - (fVar9 * fVar9 + fVar10 * fVar10) * 2.0f) * fVar3;
                local_2c = (dir[0] + local_2c * step) + local_2c;
                local_28 = (local_28 * step + dir[1]) + local_28;
                local_24 = (local_24 * step + dir[2]) + local_24;
                if (mpISphere != 0) {
                    Vec3POD p;
                    p.x = local_2c; p.y = local_28; p.z = local_24;
                    cTerrainMapSet* pcVar6 = mpISphere->s3();
                    float h = pcVar6->GetHeightAt(&p);
                    cTerrainMapSet* pc2 = mpISphere->s3();
                    if (h < pc2->f3c * pc2->f38 + pc2->f34)
                        return 1;
                }
                angle = angle + 1.0f / step;
            } while (angle < kSpiralMaxAngle);
        }
    }
    return 0;
}

// @ 0x00b83620
float cPlanetModel::FUN_00b83620(int a, float b)
{
    int iVar3 = 0;
    int iVar4 = 100;
    do {
        Vec3POD local_c;
        MakeRandomWorldPosition(&local_c, a, 0.0f, b);
        if (mpISphere != 0) {
            float h = mpISphere->s3()->GetHeightAt(&local_c);
            cTerrainMapSet* m = mpISphere->s3();
            if (h < m->f3c * m->f38 + m->f34)
                iVar3 = iVar3 + 1;
        }
        iVar4 = iVar4 - 1;
    } while (iVar4 != 0);
    return (float)iVar3 * 0.01f;
}

// @ 0x00b836b0
float FUN_00b836b0(uint param_1, uint param_2)
{
    cPlanetModel* iVar2 = PlanetModel();
    int iVar4 = *(int*)((char*)iVar2 + 0x4c);
    cTerrainMapSet* iVar3 = iVar2->mpISphere->s3();
    float fVar5 = iVar3->f34;
    uint uVar1 = *(uint*)(iVar4 + (((param_2 >> 8 & 0xff) + (param_2 >> 0x11) * 0x80) * 0x80 +
                                   (param_2 & 0xff)) * 4);
    float fVar6 = iVar3->f38;
    float fVar7;
    if (iVar2->mpISphere == 0) {
        fVar7 = 0.0f;
    } else {
        cTerrainMapSet* p = iVar2->mpISphere->s3();
        fVar7 = p->f3c * p->f38 + p->f34;
    }
    fVar5 = ((float)(int)((uVar1 & 0xffff) - 0x8000) * fVar6) * kHeightUnit + fVar5;
    if (fVar7 <= fVar5)
        return kNoTerrain;
    fVar5 = (fVar7 - fVar5) * 0.06666667f;
    float fStack_10 = 0.0f;
    if (0.0f <= fVar5)
        fStack_10 = fVar5;
    if (1.0f <= fStack_10)
        fStack_10 = 1.0f;
    float fVar5b = fStack_10 * 9.0f;
    Vec3POD A, B;
    FUN_00ac1510(param_1 >> 0x11, param_1 & 0xff, param_1 >> 8 & 0xff, (float*)&A);
    FUN_00ac1510(param_2 >> 0x11, param_2 & 0xff, param_2 >> 8 & 0xff, (float*)&B);
    float dz = B.z - A.z;
    if (iVar2->mpISphere == 0) {
        fVar6 = 0.0f;
    } else {
        cTerrainMapSet* p = iVar2->mpISphere->s3();
        fVar6 = p->f3c * p->f38 + p->f34;
    }
    return fVar6 * (float)sqrt((double)(((B.y - A.y) * (B.y - A.y) + (B.x - A.x) * (B.x - A.x)) + dz * dz)) *
           (10.0f - fVar5b);
}

// @ 0x00b83870
uint cPlanetModel::FUN_00b83870(int arg)
{
    void* pm = PropertyManager();
    int listA = 0, listB = 0;
    // mpISphere slot +0xb4: return two parallel arrays (A stride 0xc, B stride 0x38) + count.
    uint count = ((uint (__thiscall*)(void*, int*, int*))(*(void***)mpISphere)[0xb4 / 4])(mpISphere, &listA, &listB);
    float* ref = (float*)((char*)this + 0x28);
    for (uint i = 0; i < count; ++i) {
        int item = listA + (int)i * 0xc;
        void* prop = 0;
        ((char (__thiscall*)(void*, int, int, void**))(*(void***)pm)[0x2c / 4])(
            pm, *(int*)(item), *(int*)(item + 8), &prop);
        if (prop != 0) {
            float va = 0.0f, vb = 0.0f;
            char fa = 0, fb = 0;
            void* p = 0;
            if (((char (__thiscall*)(void*, int, void**))(*(void***)prop)[0x24 / 4])(prop, 0x254cf89, &p) &&
                p != 0 && *(short*)((char*)p + 0x12) == 0xd) {
                if ((*(unsigned char*)((char*)p + 0x10) & 0x30) != 0)
                    p = *(void**)p;
                va = *(float*)p;
                fa = 1;
            }
            p = 0;
            if (((char (__thiscall*)(void*, int, void**))(*(void***)prop)[0x24 / 4])(prop, 0x4ee9f45, &p) &&
                p != 0 && *(short*)((char*)p + 0x12) == 0xd) {
                if ((*(unsigned char*)((char*)p + 0x10) & 0x30) != 0)
                    p = *(void**)p;
                vb = *(float*)p;
                fb = 1;
            }
            if (fa || fb) {
                float v = (vb > va) ? vb : va;
                float* pos = (float*)(listB + (int)i * 0x38);
                float dx = pos[1] - ref[0];
                float dy = pos[2] - ref[1];
                float dz = pos[3] - ref[2];
                if (v * v >= dx * dx + dz * dz + dy * dy)
                    return 1;
            }
        }
        if (prop != 0)
            ((void (__thiscall*)(void*))(*(void***)prop)[4 / 4])(prop);
    }
    return 0;
}

// @ 0x00b83af0
// hash-table find: table at +4, bucket count at +8, chain next at +0x20.
struct HashTableA {
    char pad0[4];
    int* table;      // +4
    uint size;       // +8
    void Find(int** out, int* key);
};
struct FindResult { int* node; int* slot; };
void HashTableA::Find(int** out, int* key)
{
    uint uVar2 = (uint)(*key * 0x25 + key[2] * 0xfd + key[1]) % size;
    int* slot = table + uVar2;
    int* node = (int*)table[uVar2];
    for (; node != 0; node = (int*)node[8]) {
        if ((*key == node[0]) && (key[1] == node[1]) && (key[2] == node[2]))
            break;
    }
    if (node == 0) {
        slot = table + size;
        node = (int*)*slot;
    }
    FindResult r;
    r.node = node;
    r.slot = slot;
    *(FindResult*)out = r;
}

// @ 0x00b83b70
// node pool: free list at +0x1c, node size at +0x2c; node = 8 dwords {3 int, 3 float, 2 int} + next.
struct HashNode {
    int a, b, c;
    float x, y, z;
    int d, e;
    void* next;      // +0x20
};
struct HashTableB {
    char pad0[0x1c];
    void* freeList;  // +0x1c
    char pad1[0x2c - 0x20];
    int nodeSize;    // +0x2c
    void Insert(const HashNode* src);
};
void HashTableB::Insert(const HashNode* src)
{
    HashNode* node;
    void* fl = freeList;
    if (fl != 0) {
        node = (HashNode*)fl;
        freeList = *(void**)fl;
    } else {
        node = (HashNode*)operator_new(nodeSize, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                    0xd1);
    }
    if (node != 0) {
        node->a = src->a;
        node->b = src->b;
        node->c = src->c;
        node->x = src->x;
        node->y = src->y;
        node->z = src->z;
        node->d = src->d;
        node->e = src->e;
    }
    node->next = 0;
}

// @ 0x00b83c40
void cPlanetModel::FUN_00b83c40(const float* dir, float radius, uint flags, char (*cb)(float*))
{
    float local_b8 = dir[0];
    float local_b4 = dir[1];
    float local_b0 = dir[2];
    float fVar13 = (float)sqrt((double)((local_b0 * local_b0 + local_b4 * local_b4) + local_b8 * local_b8));
    if (1.5258789e-05f < fVar13) {
        fVar13 = 1.0f / fVar13;
        float local_88 = (fVar13 * 128.0f) * radius;
        int iVar7 = (int)(local_88 + 0.5f);
        if ((float)iVar7 < local_88)
            iVar7 = iVar7 + 1;
        if (iVar7 != 0) {
            local_b8 = fVar13 * local_b8;
            float local_c8 = fabsf(local_b8);
            local_b4 = local_b4 * fVar13;
            local_b0 = local_b0 * fVar13;
            float fVar12 = fabsf(local_b4);
            float local_8c = (fVar13 * radius) * (fVar13 * radius);
            float local_c0 = fabsf(local_b0);
            int local_d8, local_d4;
            uint local_d0;
            if ((local_c0 < local_c8) || (local_c0 < fVar12)) {
                if (fVar12 < local_c8) {
                    local_d8 = (int)((local_b4 / local_b8 + 1.0f) * 64.0f);
                    local_d4 = (int)((local_b0 / local_c8 + 1.0f) * 64.0f);
                    local_d0 = 2;
                    if (local_b8 < 0.0f)
                        local_d0 = 3;
                } else {
                    local_d8 = (int)((local_b0 / local_b4 + 1.0f) * 64.0f);
                    local_d4 = (int)((local_b8 / fVar12 + 1.0f) * 64.0f);
                    if (local_b4 < 0.0f)
                        local_d0 = 5;
                    else
                        local_d0 = 4;
                }
            } else {
                local_d8 = (int)((local_b8 / local_b0 + 1.0f) * 64.0f);
                local_d4 = (int)((local_b4 / local_c0 + 1.0f) * 64.0f);
                if (local_b0 < 0.0f)
                    local_d0 = 1;
                else
                    local_d0 = 0;
            }
            if (local_d8 == 0x80)
                local_d8 = 0x7f;
            if (local_d4 == 0x80)
                local_d4 = 0x7f;
            int local_d8b = local_d8, local_d4b = local_d4;
            unsigned local_78[29];
            int local_dc = FUN_00685450(0x80, &local_d8b, iVar7, local_78);
            unsigned* local_94 = *(unsigned**)((char*)this + 0x4c);
            flags = flags & 0x3c000000;
            unsigned char* local_90 = *(unsigned char**)((char*)this + 0x7c);
            unsigned char cc[4];
            cc[0] = (unsigned char)(flags >> 0x16);
            cc[1] = (unsigned char)(flags >> 0x1a);
            if (0 < local_dc) {
                float local_c8f = 0.0f;
                do {
                    int local_bc = *(int*)((char*)local_78 + (int)local_c8f + 8);
                    float fVar13b = local_c8f;
                    if (local_bc < *(int*)((char*)local_78 + (int)local_c8f + 0x10)) {
                        do {
                            int local_a0 = *(int*)((char*)local_78 + (int)fVar13b + 4);
                            if (local_a0 < *(int*)((char*)local_78 + (int)fVar13b + 0xc)) {
                                do {
                                    uint uVar4 = *(uint*)((char*)local_78 + (int)fVar13b);
                                    uint uVar9 = (uVar4 * 0x80 + local_bc) * 0x80 + local_a0;
                                    unsigned char* pbVar10 = (unsigned char*)((uVar9 >> 1) + (unsigned)local_90);
                                    unsigned char bVar2 = cc[uVar9 & 1];
                                    if ((*pbVar10 & bVar2) != bVar2) {
                                        int iVar7b = ((int)uVar4 >> 1) * 4;
                                        float local_98 = ((float)local_a0 + 0.5f) * 0.015625f - 1.0f;
                                        float local_c4 = ((float)local_bc + 0.5f) * 0.015625f - 1.0f;
                                        float local_c0b = 1.0f / (float)sqrt((double)((local_c4 * local_c4 + local_98 * local_98) + 1.0f));
                                        float fVar12b = local_c0b;
                                        if ((uVar4 & 1) != 0)
                                            fVar12b = -local_c0b;
                                        float local_ac[3];
                                        const unsigned char* tab = (const unsigned char*)&kBasis9[0];
                                        local_ac[(unsigned char)tab[iVar7b]] = fVar12b * local_98;
                                        unsigned char bVar3 = tab[iVar7b + 2];
                                        local_ac[(unsigned char)tab[iVar7b + 1]] = local_c0b * local_c4;
                                        local_ac[bVar3] = fVar12b;
                                        if (((local_ac[0] - local_b8) * (local_ac[0] - local_b8) +
                                             (local_ac[2] - local_b0) * (local_ac[2] - local_b0)) +
                                            (local_ac[1] - local_b4) * (local_ac[1] - local_b4) <= local_8c) {
                                            if (cb != 0) {
                                                float local_88b, fStack_84, fStack_80b;
                                                if (mFlagF0 == '\0') {
                                                    if (mpSphere == 0) {
                                                        cTerrainMapSet* p = (mpISphere == 0) ? 0 : mpISphere->s3();
                                                        if (p == 0)
                                                            fStack_80b = 500.0f;
                                                        else
                                                            fStack_80b = p->f34;
                                                    } else {
                                                        cTerrainMapSet* p = mpISphere->s3();
                                                        fStack_80b = p->GetHeightAt((const Vec3POD*)local_ac);
                                                    }
                                                    local_c4 = 1.0f / (float)sqrt((double)((local_ac[2] * local_ac[2] + (local_ac[0] * local_ac[0] + local_ac[1] * local_ac[1])) + 1e-08f));
                                                    local_88b = (local_c4 * local_ac[0]) * fStack_80b;
                                                    fStack_84 = (local_c4 * local_ac[1]) * fStack_80b;
                                                    fStack_80b = (local_ac[2] * local_c4) * fStack_80b;
                                                } else {
                                                    Vec3POD out;
                                                    FUN_00b81630(&out, (const Vec3POD*)local_ac);
                                                    local_88b = out.x; fStack_84 = out.y; fStack_80b = out.z;
                                                }
                                                float r[4];
                                                r[0] = local_88b; r[1] = fStack_84; r[2] = fStack_80b;
                                                char cVar6 = cb(r);
                                                fVar13b = local_c8f;
                                                if (cVar6 == '\0')
                                                    goto LAB_00b84137;
                                            }
                                            *pbVar10 = *pbVar10 | bVar2;
                                            unsigned* puVar1 = (unsigned*)((char*)local_94 + uVar9 * 4);
                                            *puVar1 = *puVar1 | flags;
                                        }
                                    }
                                LAB_00b84137:
                                    local_a0 = local_a0 + 1;
                                } while (local_a0 < *(int*)((char*)local_78 + (int)fVar13b + 0xc));
                            }
                            local_bc = local_bc + 1;
                        } while (local_bc < *(int*)((char*)local_78 + (int)fVar13b + 0x10));
                    }
                    local_dc = local_dc - 1;
                    local_c8f = (float)((int)fVar13b + 0x14);
                } while (local_dc != 0);
            }
        }
    }
}

// @ 0x00b841a0
// eastl::vector<cSPColorRGB,eastl::sp_vector_allocator>::DoInsertValue
struct MessageBasicRC5 {
    void* vftable;          // +0
    int mRefCount;          // +4
    int mId;                // +8
    int mFieldC;            // +0xc
    int mField10;           // +0x10
    int mField14;           // +0x14
    int mField18;           // +0x18
    int mField1c;           // +0x1c
};
struct ColorVector {
    char pad0[0x80];
    int mBegin;             // +0x80
    int mEnd;               // +0x84
    char pad2[0xa8 - 0x88];
    void* mOwner;           // +0xa8
    void DoInsertValue(uint index, uint value, int param4);
};
void ColorVector::DoInsertValue(uint index, uint value, int param4)
{
    if ((0 < (int)index) && (index < (uint)((mEnd - mBegin) / 0x18))) {
        uint* puVar3 = (uint*)(mBegin + index * 0x18);
        if (*puVar3 != value) {
            *puVar3 = value;
            *(char*)((char*)mOwner + 0xc) = 1;
            MessageBasicRC5 local_40;
            local_40.mId = 0x66603cd;
            local_40.mRefCount = 0;
            local_40.vftable = 0;
            local_40.mFieldC = 0;
            local_40.mField10 = value;
            void** piVar1 = (void**)MessageServer();
            ((void (__thiscall*)(void*, int, void*, int))(*(void***)piVar1)[0x14 / 4])(piVar1, 0x66603cd, &local_40, 0);
        }
        int iVar2 = mBegin + index * 0x18;
        if (*(char*)(iVar2 + 0x10) != '\0')
            *(int*)(iVar2 + 0x14) = param4;
    }
}
