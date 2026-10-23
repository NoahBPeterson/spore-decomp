// Slice s00e73390 -- SPGonzago/SPCellGame.obj (cell stage): part-collision resolution family.
// 0x00e73dd0 dispatches on which of the two cells has a resolved collision model; the other four
// are the per-case resolvers.  0x00e73e50 is the log-space smooth-damp of the cell world scale.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

#pragma intrinsic(sqrt, log, exp)
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl log(double);
extern "C" double __cdecl exp(double);

typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint8_t uint8;

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};

struct ResourceKey {
    uint32 instanceID;   // +0x00
    uint32 typeID;       // +0x04
    uint32 groupID;      // +0x08
};

struct cSPTransform {                // 0x38 bytes
    uint16 mFlags;                   // +0x00
    uint16 mModificationCount;       // +0x02
    Vector3 mTranslation;            // +0x04
    float mScale;                    // +0x10
    float mRotation[9];              // +0x14
};

struct cCell {
    uint32 pad000[0x48 / 4];
    cSPTransform mTransform;         // +0x48 (flags +0x48, translation +0x4c, scale +0x58, rot +0x5c)
    float mRelativeElevation;        // +0x80
    uint32 pad084[3];
    Vector3 mVelocity;               // +0x90
    uint32 pad09c;
    float mOpacity;                  // +0x0a0
    uint32 pad0a4[0x58 / 4];
    ResourceKey mModelKey;           // +0x0fc
    uint32 pad108[(0x248 - 0x108) / 4];
    int mField248;                   // +0x248
};

// One collision part (stride 0x48) inside a cell definition's part set.
struct cCollPart {
    uint32 pad00;
    int kind;                        // +0x04 (1 and 0xc are skipped)
    float lx, ly, lz;                // +0x08 local position
    uint32 pad14[(0x38 - 0x14) / 4];
    float radius;                    // +0x38
    uint32 pad3c[(0x48 - 0x3c) / 4];
};

// Part set: count at +0x00, parts from +0x04 (first part's kind lands at +0x08).
struct cPartSet {
    int count;                       // +0x00
    cCollPart parts[];
};

// ---------------------------------------------------------------- globals
extern cCell* gspCellGame;                        // 0x016b3c04 (raw pointer here)
extern void*  g_16b3c0c;                          // 0x016b3c0c (gspCellUI)
extern int    gVal_1550ad4;                       // 0x01550ad4

struct cCellGameF {
    uint32 pad0000[(0x514c) / 4];
    float field_514c;                // +0x514c
    float field_5150;                // +0x5150
    float field_5154;                // +0x5154
};
struct cCellUI {
    uint32 pad000[(0x48) / 4];
    Vector3 mCursorPosition;         // +0x48
};

// ---------------------------------------------------------------- callees
// Static cell-TU helpers with custom register conventions in the original; declared as ordinary
// free functions here (the byte diff does not check register conventions).
void  FUN_00e6d790(cCell* cell, Vector3* center, float* radius);      // 0x00e6d790
void  FUN_00e6ad80(int, cCell*, cCell*, cCell*, cCell*);              // 0x00e6ad80
int   FUN_00e573e0(cCell* cell, cCell* other);                        // 0x00e573e0
cPartSet* FUN_00e679e0(ResourceKey key);                              // 0x00e679e0
void  FUN_00e5f360();                                                 // 0x00e5f360
void  FUN_00e6db70(const Vector3& center, float scale);               // 0x00e6db70
int   FUN_00e50a10(float* cur, float* vel, float target, float speed, float dt);  // 0x00e50a10 (slide)

// sResolvePartCollision (0x00e6a3f0): 14 args, cdecl, void.  a4 is a cell (first dword = owner id);
// a1/a2 are the contact point and contact normal.
void sResolvePartCollision(int a0, const Vector3* a1, const Vector3* a2, float a3, void* a4,
                           int a5, int a6, int a7, void* a8, int a9, int a10, int a11,
                           int a12, int a13);

// Transform a part's local position by the cell transform; returns the world-space part radius.
static float PartWorldPos(cCell* cell, cCollPart* part, float* px, float* py, float* pz)
{
    float x = part->lx, y = part->ly, z = part->lz;
    if (cell->mTransform.mFlags & 2) {
        *px = cell->mTransform.mRotation[0] * x + cell->mTransform.mRotation[3] * y +
              cell->mTransform.mRotation[6] * z;
        *py = cell->mTransform.mRotation[1] * x + cell->mTransform.mRotation[4] * y +
              cell->mTransform.mRotation[7] * z;
        *pz = cell->mTransform.mRotation[2] * x + cell->mTransform.mRotation[5] * y +
              cell->mTransform.mRotation[8] * z;
    } else {
        *px = x; *py = y; *pz = z;
    }
    float scale = cell->mTransform.mScale;
    *px = cell->mTransform.mTranslation.x + scale * (*px);
    *py = cell->mTransform.mTranslation.y + scale * (*py);
    *pz = cell->mTransform.mTranslation.z + scale * (*pz);
    return part->radius * scale;
}

// @ 0x00e73390
void FUN_00e73390(int a0, cCell* cell, int a2, int count, cCollPart* parts, cCell* boundsCell,
                  int a6, int a7, int a8)
{
    Vector3 center;
    float radius;
    FUN_00e6d790(boundsCell, &center, &radius);
    for (int i = 0; i < count; i++) {
        cCollPart* part = &parts[i];
        if (part->kind == 1 || part->kind == 0xc)
            continue;
        float wx, wy, wz;
        float partRadius = PartWorldPos(cell, part, &wx, &wy, &wz);
        float dx = center.x - wx, dy = center.y - wy, dz = center.z - wz;
        float d2 = dx * dx + dy * dy + dz * dz;
        float penetration;
        Vector3 contact, normal;
        if (d2 >= 1.5258789e-05f) {
            float dist = (float)sqrt(d2);
            penetration = (partRadius + radius) - dist;
            if (penetration < 0.0f)
                continue;
            float inv = 1.0f / dist;
            float d = partRadius - radius;
            normal = Vector3(inv * dx, inv * dy, inv * dz);
            contact = Vector3((center.x + wx + normal.x * d) * 0.5f,
                              (center.y + wy + normal.y * d) * 0.5f,
                              (center.z + wz + normal.z * d) * 0.5f);
        } else {
            penetration = partRadius + radius;
        }
        sResolvePartCollision(a0, &contact, &normal, penetration, cell, a2, part->kind, i,
                              boundsCell, a6, a7, a8, 0xc, -1);
    }
}

// @ 0x00e73620
void FUN_00e73620(int a0, cCell* a1, cCell* cell, cCell* a3, cCell* a4)
{
    int uVar3 = FUN_00e573e0(a1, cell);
    cPartSet* set = FUN_00e679e0(cell->mModelKey);
    Vector3 center;
    float radius;
    FUN_00e6d790(cell, &center, &radius);
    for (int i = 0; i < set->count; i++) {
        cCollPart* part = &set->parts[i];
        if (part->kind == 1)
            continue;
        float wx, wy, wz;
        float partRadius = PartWorldPos(cell, part, &wx, &wy, &wz);
        float dx = center.x - wx, dy = center.y - wy, dz = center.z - wz;
        float d2 = dx * dx + dy * dy + dz * dz;
        float penetration;
        Vector3 contact, normal;
        if (d2 >= 1.5258789e-05f) {
            float dist = (float)sqrt(d2);
            penetration = (partRadius + radius) - dist;
            if (penetration < 0.0f)
                continue;
            float inv = 1.0f / dist;
            float d = partRadius - radius;
            normal = Vector3(inv * dx, inv * dy, inv * dz);
            contact = Vector3((center.x + wx + normal.x * d) * 0.5f,
                              (center.y + wy + normal.y * d) * 0.5f,
                              (center.z + wz + normal.z * d) * 0.5f);
        } else {
            penetration = partRadius + radius;
        }
        sResolvePartCollision(a0, &contact, &normal, penetration, a1,
                              *(int*)((char*)a3 + 0xb4), 0xc, -1, cell,
                              *(int*)((char*)a4 + 0xb4), *(int*)((char*)a4 + 0xb0), uVar3,
                              part->kind, i);
    }
}

// @ 0x00e738f0
void FUN_00e738f0(int a0, cCell* cell, cCell* a2, cCell* a3, cCell* a4)
{
    int uVar3 = FUN_00e573e0(cell, a2);
    cPartSet* set = FUN_00e679e0(cell->mModelKey);
    Vector3 center;
    float radius;
    FUN_00e6d790(cell, &center, &radius);
    for (int i = 0; i < set->count; i++) {
        cCollPart* part = &set->parts[i];
        if (part->kind == 1)
            continue;
        float wx, wy, wz;
        float partRadius = PartWorldPos(cell, part, &wx, &wy, &wz);
        float dx = center.x - wx, dy = center.y - wy, dz = center.z - wz;
        float d2 = dx * dx + dy * dy + dz * dz;
        float penetration;
        Vector3 contact, normal;
        if (d2 >= 1.5258789e-05f) {
            float dist = (float)sqrt(d2);
            penetration = (partRadius + radius) - dist;
            if (penetration < 0.0f)
                continue;
            float inv = 1.0f / dist;
            float d = partRadius - radius;
            normal = Vector3(inv * dx, inv * dy, inv * dz);
            contact = Vector3((center.x + wx + normal.x * d) * 0.5f,
                              (center.y + wy + normal.y * d) * 0.5f,
                              (center.z + wz + normal.z * d) * 0.5f);
        } else {
            penetration = partRadius + radius;
        }
        sResolvePartCollision(a0, &contact, &normal, penetration, cell,
                              *(int*)((char*)a3 + 0xb4), part->kind, i, a2,
                              *(int*)((char*)a4 + 0xb4), *(int*)((char*)a4 + 0xb0), uVar3, 0xc, -1);
    }
}

// @ 0x00e73bb0
void FUN_00e73bb0(int p1, cCell* cellA, cCell* p3, cCell* arg3, cCell* p5)
{
    Vector3 centerA;
    float radiusA;
    Vector3 centerB;
    float radiusB;
    FUN_00e6d790(cellA, &centerA, &radiusA);
    FUN_00e6d790(arg3, &centerB, &radiusB);

    float dx = centerA.x - centerB.x;
    float dy = centerA.y - centerB.y;
    float dz = centerA.z - centerB.z;
    float d2 = dx * dx + dy * dy + dz * dz;
    float penetration;
    Vector3 contact, normal;
    if (d2 >= 1.5258789e-05f) {
        float dist = (float)sqrt(d2);
        penetration = (radiusA + radiusB) - dist;
        if (penetration < 0.0f)
            return;
        float inv = 1.0f / dist;
        float d = radiusA - radiusB;
        normal = Vector3(inv * dx, inv * dy, inv * dz);
        contact = Vector3((centerB.x + centerA.x + normal.x * d) * 0.5f,
                          (centerB.y + centerA.y + normal.y * d) * 0.5f,
                          (centerB.z + centerA.z + normal.z * d) * 0.5f);
    } else {
        penetration = radiusA + radiusB;
    }

    int uVar4 = FUN_00e573e0(cellA, p3);
    if (cellA->mModelKey.instanceID != 0) {
        cPartSet* set = FUN_00e679e0(cellA->mModelKey);
        FUN_00e73390(p1, cellA, *(int*)((char*)arg3 + 0xb4), set->count, set->parts, p3,
                     *(int*)((char*)p5 + 0xb4), *(int*)((char*)p5 + 0xb0), uVar4);
    }
    sResolvePartCollision(p1, &contact, &normal, penetration, cellA,
                          *(int*)((char*)arg3 + 0xb4), 0xc, -1, p3,
                          *(int*)((char*)p5 + 0xb4), *(int*)((char*)p5 + 0xb0),
                          uVar4, 0xc, -1);
}

// @ 0x00e73dd0
void FUN_00e73dd0(int p1, cCell* p2, cCell* p3, cCell* p4, cCell* p5)
{
    if (p3->mField248 != 0 && p3->mModelKey.instanceID != 0) {
        if (p2->mField248 != 0 && p2->mModelKey.instanceID != 0) { FUN_00e6ad80(p1, p2, p3, p4, p5); return; }
        FUN_00e73620(p1, p2, p3, p4, p5); return;
    }
    if (p2->mField248 != 0 && p2->mModelKey.instanceID != 0) { FUN_00e738f0(p1, p2, p3, p4, p5); return; }
    FUN_00e73bb0(p1, p2, p3, p4, p5);
}

// @ 0x00e73e50
void FUN_00e73e50(float dt)
{
    cCellGameF* g = (cCellGameF*)gspCellGame;
    if (g->field_514c == g->field_5150) {
        gVal_1550ad4 = 1;
        return;
    }
    gVal_1550ad4 = 0;

    float fCur = (float)log(g->field_514c);
    float fTarget = (float)log(g->field_5150);
    FUN_00e50a10(&fCur, &g->field_5154, fTarget, 1.0f, dt * 0.75f);

    float fNew = (float)exp(fCur);
    if (fCur == fTarget)
        fNew = g->field_5150;

    float old = g->field_514c;
    float ratio = fNew / old;
    g->field_514c = fNew;

    FUN_00e6db70(((cCellUI*)g_16b3c0c)->mCursorPosition, ratio);
    FUN_00e5f360();
}
