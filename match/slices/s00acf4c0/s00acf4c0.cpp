// Per-frame update of the planet's plant/vegetation spawner (cube-face tiles around the camera).
// Complete behavioural reconstruction; callees are declared with the calling conventions seen at the call sites.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };

// Intrusive refcounted object: slot 0 = AddRef, slot 1 = Release.
struct RefObj {
    virtual void AddRef();
    virtual void Release();
};

// Position provider living at noun-model+0x34 (vtable slot 11 returns the position).
struct PosHolder {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10();
    virtual Vector3* GetPosition();
};
struct NounInfo { char pad[0x504]; Vector3 spawnPos; };   // +0x504

// Model object returned by plant vtable slot 27: radius at +0x25c, position provider (own vtable) at +0x34.
struct PlantModel {
    char pad0[0x34];
    PosHolder holder;                   // +0x34
    char pad38[0x25c - 0x38];
    float radius;                       // +0x25c
};

// A plant noun (only the fields used here).
struct Plant : RefObj {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual PlantModel* GetModel();     // slot 27 (+0x6c)
    char pad04[0x40 - 4];
    void* childBegin;                   // +0x40
    void* childEnd;                     // +0x44
    char pad48[0xa4 - 0x48];
    NounInfo* info;                     // +0xa4
    char pada8[0xf4 - 0xa8];
    uint32_t fadeTime;                  // +0xf4
    char padf8[0x108 - 0xf8];
    float spawnTime;                    // +0x108
    char pad10c[0x192 - 0x10c];
    char flag192;                       // +0x192
    Vector3* __thiscall GetPlantPosition();     // 0xc6acc0
    char __thiscall PlantIsBusy();              // 0xc6a020
    void __thiscall SetPlantFlag(bool b);       // 0xc6ace0
};

struct IRefVec { RefObj** begin; RefObj** end; RefObj** cap;
    void __thiscall Append(RefObj** where, uint32_t n, RefObj** val); };   // 0xbabb70

// hashtable node of the tile map (value starts at +4)
struct TileNode {
    uint32_t key;                       // +0x00
    Vector3 pos;                        // +0x04
    float dist;                         // +0x10
    char pad14[0x28 - 0x14];
    IRefVec plants;                     // +0x28 (AutoRefCount<Plant>)
    char pad34[0x3c - 0x34];
    IRefVec extras;                     // +0x3c
    char pad48[0x68 - 0x48];
    TileNode* next;                     // +0x68
};

struct TileMap {
    char pad[4];
    TileNode** buckets;                 // +4
    uint32_t bucketCount;               // +8
};

struct CullEntry { float x, y, z, rx2, rz2; };   // 0x14 bytes
struct CullVec { CullEntry* begin; CullEntry* end; CullEntry* cap; };

// ---- external classes / functions ----
struct cViewer {
    void __thiscall GetCameraLocationInfo(Vector3* pos, Vector3* dir, void* a, void* b);   // 0x7c3d30
};
struct IViewerSource {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6();
    virtual cViewer* GetViewer();       // +0x1c
};
struct IApp {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual IViewerSource* GetViewerSource();   // +0x50
};
struct ISphereData { char pad[8]; int dim; char pad2[4]; uint8_t* data; };   // +8 dim, +0x10 data
struct ISphereLevel { char pad[0xc]; ISphereData* d; };
struct ISphereIface {
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual ISphereLevel* GetLevel();   // +0xc
};
struct cPlanetModel {
    char pad[0x24];
    ISphereIface* mpISphere;                                                       // +0x24
    float   __thiscall GetWaterHeight();                                            // 0xb7e390
    Vector3* __thiscall FUN_00b81630(Vector3* out, Vector3* in);                    // 0xb81630
    void    __thiscall FUN_00b82060(Vector3* out, Vector3* cam, Vector3* dir);      // 0xb82060
    float   __thiscall GetRadiusAt(Vector3* dir);                                   // 0xb7ef70
    Vector3* __thiscall DirectionToSurfacePosition(Vector3* out, Vector3* dir);     // 0xb815a0
    Vector3* __thiscall MakeRandomWorldPosition(Vector3* out, Vector3* center, float r0, float r1); // 0xb81780
    uint32_t __thiscall GetAverageRadius(Vector3* pos);                             // 0xb7e840
    Plant*   __thiscall FindPlantNear(Vector3* pos);                                // 0xb894a0
};
struct cTerrainCameraController { Vector3* __thiscall GetAnchorDirection0(); };    // 0xb10200
struct cPlanet {
    char pad[0x13c];
    char* pTreeData;                                                                // +0x13c
    int __thiscall PlantSpeciesToTypeIndex(void* species);                          // 0xc70d70
    char* __thiscall GetTileBase();                                                 // 0x8414c0
};
struct cGameNounManager {
    void __thiscall RemoveNoun(Plant* noun);                                        // 0xb225d0
    Plant* __thiscall CreateNoun(Vector3* pos, void* profile, uint32_t scale, int a, int b, int c); // 0xb23940
};
struct cDirectPropertyList { int __thiscall GetIntProperty(uint32_t id); };         // 0x6a2660

IApp*             SP_App();                                         // 0x67dd10
cPlanetModel*     SP_PlanetModel();                                 // 0xb3d350
cGameNounManager* SP_NounManager();                                 // 0xb3d300
cTerrainCameraController* GetTerrainCameraController();             // 0xb3d280
cPlanet*          GetActivePlanet();                                // 0x1021260
void*             GetCurrentGameMode();                             // 0xb5b800
void*             __stdcall GetSpeciesManagerFor(void* key);        // 0x401090
struct SpeciesManager { void* __thiscall GetProfile(); };           // 0x4df550
void __cdecl operator_delete_array(void* p);                        // 0xf47380

extern Vector3 g_InvalidPos;        // 0x167a390
extern uint32_t g_ViewStamp;        // 0x167a378
extern uint32_t g_CurStamp;         // 0x16881e4
extern float g_ElapsedSec;          // 0x167a494
extern char g_ForceRefresh;         // 0x1565cfc
extern float g_RefreshPeriod;       // 0x1565ce0
extern float g_DensityMax;          // 0x1565ce4
extern float g_DensityThresh;       // 0x1565ce8
extern float g_SpawnTime;           // 0x1565cec
extern uint32_t g_SpawnTries;       // 0x1565cf0
extern float g_PlantRadiusBias;     // 0x1565cf8
extern float g_RingMin;             // 0x1565d54
extern float g_RingMax;             // 0x1565d58
extern float g_CullRadiusX;         // 0x1565d5c
extern float g_CullRadiusZ;         // 0x1565d60
extern uint8_t g_FaceAxes[];        // 0x145a090 : 3 axis indices per cube-face pair, stride 4
extern cDirectPropertyList* g_AppProperties;   // 0x15fd918
extern void* g_ModeSpecial;         // 0x1654c04

// fixed_vector<float, 32> with a header word in front of its buffer (a non-zero header marks a heap block)
struct FixedFloatVec {
    float* begin; float* end; float* cap;
    void __thiscall Fill(float* where, uint32_t n, const float* val);   // 0x4b0a10
};

struct cPlantSpawner {
    char pad0[0x20];
    CullVec cull;                       // +0x20
    char pad2c[0xc0 - 0x2c];
    TileMap tiles;                      // +0xc0

    TileNode* __thiscall TileAt(uint32_t* key);                                  // 0xace170 (operator[])
    void __thiscall UpdateCullCenter(Vector3* v, float rx, float rz);            // 0xacc700
    void __thiscall GrowCull(CullEntry* where, CullEntry* val);                  // 0xacb680
    void __thiscall Tail(uint32_t a, uint32_t b);                                // 0xace5a0
    void Update(uint32_t dt, uint32_t dtAlt);
};

// @ 0x00acf4c0
void cPlantSpawner::Update(uint32_t dt, uint32_t dtAlt)
{
    // drop any previous culling regions
    cull.end = cull.begin;

    cPlanetModel* model = SP_PlanetModel();
    float waterHeight = model->GetWaterHeight();
    float cullRX = g_CullRadiusX;
    float cullRZ = g_CullRadiusZ;

    Vector3 camPos, camDir;
    cViewer* viewer = SP_App()->GetViewerSource()->GetViewer();
    viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    Vector3 tmp;
    cTerrainCameraController* ctl = GetTerrainCameraController();
    if (ctl) {
        Vector3 a = *ctl->GetAnchorDirection0();
        if (a.x != g_InvalidPos.x || a.y != g_InvalidPos.y || a.z != g_InvalidPos.z) {
            Vector3 t;
            Vector3* r = model->FUN_00b81630(&t, &a);
            a = *r;
            UpdateCullCenter(&a, cullRX, cullRZ);
        }
    } else {
        Vector3 d;
        model->FUN_00b82060(&d, &camPos, &camDir);
        if (d.x != g_InvalidPos.x || d.y != g_InvalidPos.y || d.z != g_InvalidPos.z)
            UpdateCullCenter(&d, cullRX, cullRZ);
    }

    {
        Vector3* r = model->FUN_00b81630(&tmp, &camPos);
        camPos = *r;
    }
    float hx = cullRX * 0.5f;
    float hz = cullRZ * 0.5f;
    if (cull.end < cull.cap)
        ++cull.end;
    else {
        CullEntry scratch;
        GrowCull(cull.end, &scratch);
    }
    CullEntry* e = cull.end - 1;
    e->x = camPos.x; e->y = camPos.y; e->z = camPos.z;
    e->rx2 = hx * hx;
    e->rz2 = hz * hz;

    if (g_ViewStamp != g_CurStamp) {
        g_ViewStamp = g_CurStamp;
        g_ForceRefresh = 1;
    }

    uint32_t ms = dtAlt ? dtAlt : dt;
    g_ElapsedSec = g_ElapsedSec + (float)ms * 0.001f;

    if (g_ElapsedSec > g_RefreshPeriod || g_ForceRefresh) {
        g_ElapsedSec = 0.0f;

        cGameNounManager* nouns = SP_NounManager();
        cPlanet* planet = GetActivePlanet();
        char* tileBase = planet->GetTileBase();
        char* treeData = *(char**)((char*)planet + 0x13c);
        bool singlePerCell = ((*(uint32_t*)(treeData + 0x2c) >> 11) & 1) != 0;
        uint32_t plantTypes = (uint32_t)((*(int*)(treeData + 0xd4) - *(int*)(treeData + 0xd0)) / 12);
        if (GetCurrentGameMode() == g_ModeSpecial)
            plantTypes = 5;

        ISphereLevel* lvl = model->mpISphere->GetLevel();
        uint8_t* texels = lvl->d->data;
        int dim = lvl->d->dim;
        int faceSize = dim * dim;
        float densityThresh = g_DensityThresh;

        int densityCap = (int)g_DensityMax;
        int density = g_AppProperties->GetIntProperty(0x4a5bf9e);
        int perCell = density < densityCap ? density : densityCap;
        uint32_t spawnLimit;
        if (singlePerCell) {
            uint32_t d1 = plantTypes > 1 ? plantTypes : 1;
            uint32_t q = (uint32_t)perCell / d1;
            spawnLimit = q > 1 ? q : 1;
        } else {
            spawnLimit = perCell / 2;
        }

        for (int face = 0; face < 6; ++face) {
            for (int ty = 0; ty < 4; ++ty) {
                for (int tx = 0; tx < 4; ++tx) {
                    uint32_t cell = (uint32_t)((ty + face * 4) * 4 + tx);
                    char* cellData = tileBase + cell * 0x54 + 0x50;

                    // look the tile up; create and initialize it if it doesn't exist yet
                    uint32_t bc = tiles.bucketCount;
                    TileNode* n = tiles.buckets[cell % bc];
                    while (n && n->key != cell)
                        n = n->next;
                    if (!n) {
                        uint32_t k = cell;
                        TileNode* node = TileAt(&k);
                        float fu = (float)ty;
                        float fv = (float)tx;
                        float u = (fu + 0.5f) * 0.5f - 1.0f;
                        float v = (fv + 0.5f) * 0.5f - 1.0f;
                        float len = 1.0f / sqrt(v * v + u * u + 1.0f);
                        float sl = len;
                        if (face & 1) sl = -len;
                        const uint8_t* ax = &g_FaceAxes[(face >> 1) * 4];
                        float dir[3];
                        dir[ax[0]] = sl * v;
                        dir[ax[1]] = len * u;
                        dir[ax[2]] = sl;
                        float rad = model->GetRadiusAt((Vector3*)dir);
                        float r = rad > waterHeight ? rad : waterHeight;
                        float u2 = (fu * 0.25f) * 2.0f - 1.0f;
                        float v2 = (fv * 0.25f) * 2.0f - 1.0f;
                        float len2 = 1.0f / sqrt(v2 * v2 + u2 * u2 + 1.0f);
                        float sl2 = len2;
                        if (face & 1) sl2 = -len2;
                        float dir2[3];
                        dir2[ax[0]] = sl2 * v2;
                        dir2[ax[1]] = len2 * u2;
                        dir2[ax[2]] = sl2;
                        Vector3 other;
                        model->FUN_00b81630(&other, (Vector3*)dir2);
                        node->pos.x = dir[0] * r;
                        node->pos.y = dir[1] * r;
                        node->pos.z = dir[2] * r;
                        float dx = node->pos.x - other.x;
                        float dy = node->pos.y - other.y;
                        float dz = node->pos.z - other.z;
                        node->dist = sqrt(dy * dy + (dz * dz + dx * dx));
                    }

                    uint32_t key2 = cell;
                    TileNode* node = TileAt(&key2);

                    if (!singlePerCell) {
                        // make sure the plant slot vector has at least plantTypes entries
                        IRefVec* pv = &node->plants;
                        if ((uint32_t)(pv->end - pv->begin) < plantTypes) {
                            uint32_t sz = (uint32_t)(pv->end - pv->begin);
                            if (plantTypes > sz) {
                                RefObj* nul = 0;
                                pv->Append(pv->end, plantTypes - sz, &nul);
                            } else {
                                RefObj** newEnd = pv->begin + plantTypes;
                                for (RefObj** p = newEnd; p < pv->end; ++p)
                                    if (*p) (*p)->Release();
                                pv->end = newEnd;
                            }
                        }
                        uint32_t have = (uint32_t)(pv->end - pv->begin);
                        uint32_t n = have >= plantTypes ? have : plantTypes;

                        // fixed_vector<float,32>, zero-filled
                        struct { int hdr; float buf[32]; } store;
                        store.hdr = 0;
                        FixedFloatVec acc;
                        acc.begin = store.buf;
                        acc.end = store.buf;
                        acc.cap = store.buf + 32;
                        float zero = 0.0f;
                        if (n != 0)
                            acc.Fill(store.buf, n, &zero);
                        else
                            acc.end = acc.begin;

                        // accumulate the two species weights of this cell
                        int* sp = (int*)(cellData + 0x40);
                        for (int j = 2; j != 0; --j) {
                            int idx = planet->PlantSpeciesToTypeIndex(sp - 3);
                            if (idx >= 0 && (uint32_t)idx < n)
                                acc.begin[idx] = (float)*sp + acc.begin[idx];
                            sp += 4;
                        }

                        for (uint32_t i = 0; i < n; ++i) {
                            RefObj** slot = &node->plants.begin[i];
                            Plant* noun = (Plant*)*slot;
                            bool removeIt = false;
                            if (acc.begin[i] > 0.0f) {
                                Vector3* key = (Vector3*)(*(char**)(treeData + 0xd0) + i * 12);
                                if (noun) {
                                    Vector3* np = noun->GetPlantPosition();
                                    NounInfo* info = noun->info;
                                    bool differs = !(info->spawnPos.x == key->x && info->spawnPos.y == key->y &&
                                                     info->spawnPos.z == key->z);
                                    if (np->x == g_InvalidPos.x && np->y == g_InvalidPos.y && np->z == g_InvalidPos.z) {
                                        if (differs) removeIt = true;
                                        else noun->fadeTime = spawnLimit;
                                    } else if (differs) {
                                        removeIt = true;
                                    } else {
                                        Vector3 sp2;
                                        Vector3* s = model->DirectionToSurfacePosition(&sp2, np);
                                        float d2 = (np->x - s->x) * (np->x - s->x) +
                                                   (np->z - s->z) * (np->z - s->z) +
                                                   (np->y - s->y) * (np->y - s->y);
                                        if (d2 > 1.0f) {
                                            removeIt = true;
                                        } else {
                                            Plant* near1 = model->FindPlantNear(np);
                                            if (near1) {
                                                float rr = near1->GetModel()->radius + g_PlantRadiusBias;
                                                Vector3* q = near1->GetModel()->holder.GetPosition();
                                                float d3 = (np->x - q->x) * (np->x - q->x) +
                                                           (np->z - q->z) * (np->z - q->z) +
                                                           (np->y - q->y) * (np->y - q->y);
                                                if (rr * rr > d3) removeIt = true;
                                            }
                                            if (!removeIt) noun->fadeTime = spawnLimit;
                                        }
                                    }
                                } else {
                                    // no plant here yet: try to spawn one
                                    SpeciesManager* mgr = (SpeciesManager*)GetSpeciesManagerFor(key);
                                    void* profile = mgr->GetProfile();
                                    if (profile) {
                                        bool placed = false;
                                        Vector3 cand;
                                        uint32_t t = 0;
                                        bool again;
                                        do {
                                            Vector3 tmpv;
                                            Vector3* pr = model->MakeRandomWorldPosition(&tmpv, &node->pos,
                                                node->dist * g_RingMin, node->dist * g_RingMax);
                                            cand = *pr;
                                            uint32_t flags = model->GetAverageRadius(&cand);
                                            if ((flags & 0x98000000) == 0) {
                                                float h = (float)dim * 0.5f;
                                                float axx = fabs(cand.x);
                                                float ayy = fabs(cand.y);
                                                float azz = fabs(cand.z);
                                                int iu, iv, f;
                                                if (azz < axx || azz < ayy) {
                                                    if (ayy < axx) {
                                                        iu = (int)((cand.y / cand.x + 1.0f) * h);
                                                        iv = (int)((cand.z / axx + 1.0f) * h);
                                                        f = 2;
                                                        if (cand.x < 0.0f) f = 3;
                                                    } else {
                                                        iu = (int)((cand.z / cand.y + 1.0f) * h);
                                                        iv = (int)((cand.x / ayy + 1.0f) * h);
                                                        if (cand.y < 0.0f) f = 5; else f = 4;
                                                    }
                                                } else {
                                                    iu = (int)((cand.x / cand.z + 1.0f) * h);
                                                    iv = (int)((cand.y / azz + 1.0f) * h);
                                                    if (cand.z < 0.0f) f = 1; else f = 0;
                                                }
                                                if (iu == dim) iu = iu - 1;
                                                if (iv == dim) iv = iv - 1;
                                                if ((float)texels[3 + (iv * dim + f * faceSize + iu) * 4] * 0.3921569f <= densityThresh) {
                                                    Plant* near2 = model->FindPlantNear(&cand);
                                                    bool blocked = false;
                                                    if (near2) {
                                                        float rr = near2->GetModel()->radius + g_PlantRadiusBias;
                                                        Vector3* q = near2->GetModel()->holder.GetPosition();
                                                        float d3 = (cand.x - q->x) * (cand.x - q->x) +
                                                                   (cand.z - q->z) * (cand.z - q->z) +
                                                                   (cand.y - q->y) * (cand.y - q->y);
                                                        if (d3 < rr * rr) blocked = true;
                                                    }
                                                    if (!blocked) {
                                                        placed = true;
                                                        goto doCreate;
                                                    }
                                                }
                                            }
                                            again = t < g_SpawnTries;
                                            ++t;
                                        } while (again);
                                        cand = g_InvalidPos;
                                    doCreate:
                                        Plant* np2 = nouns->CreateNoun(&cand, profile, spawnLimit, 0, 0, 0);
                                        if (np2) {
                                            np2->SetPlantFlag(placed);
                                            np2->spawnTime = g_SpawnTime;
                                            RefObj** s2 = &node->plants.begin[i];
                                            RefObj* old = *s2;
                                            if (np2 != (Plant*)old) {
                                                np2->AddRef();
                                                *s2 = np2;
                                                if (old) old->Release();
                                            }
                                        }
                                    }
                                }
                            } else {
                                removeIt = noun != 0;
                            }
                            if (removeIt && noun) {
                                nouns->RemoveNoun(noun);
                                RefObj** s3 = &node->plants.begin[i];
                                RefObj* old = *s3;
                                if (old) {
                                    *s3 = 0;
                                    old->Release();
                                }
                            }
                        }

                        if (acc.begin && *((int*)acc.begin - 1) != 0)
                            operator_delete_array(acc.begin);
                    }

                    // reap finished extra objects
                    for (uint32_t i = 0; i < (uint32_t)(node->extras.end - node->extras.begin); ++i) {
                        Plant* ex = (Plant*)node->extras.begin[i];
                        if (ex && ex->flag192 && !ex->PlantIsBusy() && ex->childBegin == ex->childEnd) {
                            nouns->RemoveNoun(ex);
                            RefObj** slot = &node->extras.begin[i];
                            RefObj* last = node->extras.end[-1];
                            RefObj* old = *slot;
                            if (last != old) {
                                if (last) last->AddRef();
                                *slot = last;
                                if (old) old->Release();
                            }
                            --node->extras.end;
                            if (*node->extras.end) (*node->extras.end)->Release();
                        }
                    }
                }
            }
        }
    }
    g_ForceRefresh = 0;
    Tail(dt, dtAlt ? dtAlt : dt);
}
