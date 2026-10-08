// SP::cTerrainSphere::UpdateQuadsPostCamera: after the camera moved, walk the quad tree from the six
// face roots, cull by distance/facing and frustum, refine, and fill the per-frame render arrays.
// Retail layout of cTerrainSphere differs from the 2008 PDB here; offsets below come from the disassembly.
#include <new>
#include <math.h>
#include <string.h>
#include "types.h"

struct Vec3f { float x, y, z; };

extern float g_ZeroX;                                   // 0x016c9e8c
extern float g_ZeroY;                                   // 0x016c9e90
extern float g_ZeroZ;                                   // 0x016c9e94
extern float g_Ident[9];                                // 0x016c9f24 (3x3 block to 0x016c9f44)

struct cQuad {
    char pad0[8];
    cQuad* children[4];            // +8
    char pad1[0x34 - 0x18];
    Vec3f centre;                  // +0x34
    char pad2[0x64 - 0x40];
    float lodKey;                  // +0x64
    char pad3[0x70 - 0x68];
    Vec3f sphereCentre;            // +0x70
    float sphereRadius;            // +0x7c
    void Refine();                 // 0x00fb77b0
    void MarkChild();              // 0x00fb5090
};

struct QItem { cQuad* quad; uint32_t flags; };
struct QContainer { cQuad* quad; float lod; uint32_t key; uint32_t zero; };

struct QuadStack {                 // global at 0x016ca24c
    QItem* mpBegin;
    QItem* mpEnd;
    QItem* mpCapacity;
    void DoInsertValue(QItem* pos, const QItem& v);     // 0x00b534c0 (ret 8)
    void push_back(const QItem& v)
    {
        if (mpEnd < mpCapacity) {
            QItem* p = mpEnd++;
            ::new ((void*)p) QItem(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
extern QuadStack g_QuadStack;   // 0x016ca24c

struct QCVector {                  // eastl::vector<QContainer, sp_vector_allocator>, 0x14 bytes
    QContainer* mpBegin;
    QContainer* mpEnd;
    QContainer* mpCapacity;
    uint32_t alloc[2];
    void DoInsertValue(QContainer* pos, const QContainer& v);   // 0x00c19d10 (ret 8)
    void push_back(const QContainer& v)
    {
        if (mpEnd < mpCapacity) {
            QContainer* p = mpEnd++;
            ::new ((void*)p) QContainer(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    void clear()
    {
        QContainer* first = mpBegin;
        QContainer* last = mpEnd;
        CopyRange(last, last, first);
        mpEnd += (first - last);
    }
    static void* CopyRange(QContainer* a, QContainer* b, QContainer* c);   // 0x00705250 (cdecl)
};

struct Property {
    char pad[0x12];
    short type;
    float* GetFloat();             // 0x0041ea70
};

struct cDirectPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);       // +0x24
    bool GetDescription(uint32_t id);                            // 0x006a25a0 (ret 4)
    float GetFloatProperty(uint32_t id);                         // 0x006a2710 (ret 4)
};
extern cDirectPropertyList* sAppProperties;                      // 0x015fd918

struct cFrustumCull {
    uint32_t buf[0x3b];
    cFrustumCull(void* camera);                                  // 0x006ffe00 (ret 4)
    void SetNear(float f);                                       // 0x006ffa80 (ret 4)
    uint32_t FrustumTestSphere(const Vec3f* centre, const float* radius, uint32_t flags);   // 0x00700120
};

struct SPTransform {
    short a, b;
    Vec3f pos;
    float scale;
    float rot[9];
    SPTransform() : a(0), b(0), scale(1.0f)
    {
        pos.x = g_ZeroX; pos.y = g_ZeroY; pos.z = g_ZeroZ;
        for (int i = 0; i < 9; ++i) rot[i] = g_Ident[i];
    }
};

struct cViewer { void GetTransform(SPTransform* out); };          // 0x007c40f0 (ret 4)

struct cTerrainInfo { char pad[0x34]; float radius; };

bool QuadDetailTest(cQuad* q, void* terrain, float* outDist);    // 0x00f97960 (stdcall, ret 0xc)
void SortQuads(QContainer* first, QContainer* last, bool flag);  // 0x00fa2660 (cdecl)

class cTerrainSphere {
public:
    virtual void vfn0(); virtual void vfn1(); virtual void vfn2();
    virtual cTerrainInfo* GetInfo();                             // +0xc
    void UpdateQuadsPostCamera(void* camera);                    // 0x00fa5610

    char pad0[0x118 - 4];
    cQuad* faceRoots[6];             // +0x118
    cQuad* atmoRoots[6];             // +0x130
    char pad1[0x190 - 0x148];
    QCVector renderQuads;            // +0x190
    QCVector faceRootArray;          // +0x1a4
    QCVector atmoRootArray;          // +0x1b8
    char pad2[0x1e8 - 0x1cc];
    bool flagA;                      // +0x1e8
    char pad3[0x30c - 0x1e9];
    char decalState[0x8e4 - 0x30c];  // +0x30c
    cViewer* viewer;                 // +0x8e4
};

// @ 0x00fa5610
void cTerrainSphere::UpdateQuadsPostCamera(void* camera)
{
    renderQuads.clear();
    faceRootArray.clear();
    atmoRootArray.clear();

    cDirectPropertyList* props = sAppProperties;
    flagA = props->GetDescription(0x563886c);
    bool markChildren = props->GetDescription(0x563886d);

    cFrustumCull cull((char*)camera + 0xc0);
    Property* prop;
    if (props && props->GetProperty(0x13d7382, &prop) && prop->type == 0xd) {
        float f = *prop->GetFloat();
        cull.SetNear(f);
    }

    for (int i = 0; i < 6; ++i) {
        QItem it = { faceRoots[i], 0 };
        g_QuadStack.push_back(it);
    }

    bool useDistCull = sAppProperties->GetDescription(0x541a775);
    float maxCamDist = sAppProperties->GetFloatProperty(0x62f89dc);
    float cullDist = sAppProperties->GetFloatProperty(0x63fe1bc);
    float facing = sAppProperties->GetFloatProperty(0x541ac31);
    float radiusScale = GetInfo()->radius;

    SPTransform xf;
    viewer->GetTransform(&xf);
    if (maxCamDist < sqrtf(xf.pos.z * xf.pos.z + (xf.pos.y * xf.pos.y + xf.pos.x * xf.pos.x)))
        useDistCull = false;

    while (g_QuadStack.mpBegin != g_QuadStack.mpEnd) {
        QItem item = g_QuadStack.mpEnd[-1];
        --g_QuadStack.mpEnd;
        cQuad* q = item.quad;
        bool test = true;
        if (useDistCull) {
            float vz = q->centre.z * radiusScale - xf.pos.z;
            float vx = q->centre.x * radiusScale - xf.pos.x;
            float vy = q->centre.y * radiusScale - xf.pos.y;
            if ((vx * vx + vz * vz) + vy * vy > cullDist * cullDist) {
                float nx = -vx, nz = -vz, ny = -vy;
                float inv = 1.0f / sqrtf((nx * nx + nz * nz + ny * ny) + 1e-08f);
                float dot = ((nz * inv) * q->centre.z + (ny * inv) * q->centre.y) + (inv * nx) * q->centre.x;
                if (facing > dot)
                    test = false;
            }
        }
        if (!test)
            continue;
        uint32_t fl = cull.FrustumTestSphere(&q->sphereCentre, &q->sphereRadius, item.flags);
        if (fl & 0x40)
            continue;
        float dist;
        if (!QuadDetailTest(q, decalState, &dist)) {
            if (q->children[0] == 0)
                q->Refine();
            if (q->children[0] != 0) {
                cQuad** pc = q->children;
                for (int i = 4; i; --i) {
                    QItem ci = { *pc, fl };
                    g_QuadStack.push_back(ci);
                    ++pc;
                }
            }
            if (q->children[0] != 0)
                continue;
        }
        float lod = q->lodKey;
        uint32_t bits;
        memcpy(&bits, &dist, 4);
        QContainer c = { q, lod, (uint32_t)((int)bits >> 31) ^ (bits | 0x80000000u), 0 };
        renderQuads.push_back(c);
        if (markChildren && q->children[0] != 0) {
            cQuad** pc = q->children;
            for (int i = 4; i; --i) {
                if ((*pc)->children[0] != 0)
                    (*pc)->MarkChild();
                ++pc;
            }
        }
    }
    SortQuads(renderQuads.mpBegin, renderQuads.mpEnd, false);

    for (int i = 0; i < 6; ++i) {
        QContainer a = { faceRoots[i], 1.0f, 0, 0 };
        faceRootArray.push_back(a);
        QContainer b = { atmoRoots[i], 1.0f, 0, 0 };
        atmoRootArray.push_back(b);
    }
}
