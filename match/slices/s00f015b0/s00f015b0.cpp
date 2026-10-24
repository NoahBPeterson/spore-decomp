// Slice s00f015b0 -- editor tool: drag a placed object onto the planet surface and reorient it.
// /O2 /MD /Gy /EHsc /TP /arch:SSE region (neighbour of s00efd020).
#include "types.h"
extern "C" double sqrt(double);
extern "C" double fabs(double);

static inline float fabsf_(float v) { return (float)fabs((double)v); }
struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };

#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();

struct Viewer {
  void GetCameraRay(V3* origin, V3* dir);               // 0x007c4900 (ret 8)
};
struct cTutorialHost;
struct AppObj {
  P4(0) P4(1) P4(2) P4(3) P4(4)
  virtual cTutorialHost* GetTutorialHost();             // +0x50
  virtual void p5b();
  virtual Viewer* GetViewer();                          // +0x58
};
AppObj* AppGet();                                       // 0x0067dd10 (SP::App)

// Placed-object (entity) data block.
struct Ent {
  char pad0[4];
  float px, py, pz;       // +0x04
  float qx, qy, qz, qw;   // +0x10
  char pad20[0x220 - 0x20];
  float f220;             // +0x220
};

// Thing: object with an interface query at vtable +0xb8.
struct Thing {
  P4(0) P4(1) P4(2) P4(3) P4(4) P4(5) P4(6) P4(7) P4(8) P4(9) P4(10)
  virtual void p11a(); virtual void p11b();
  virtual void* QueryInterface(unsigned id);            // +0xb8
};
Thing* __cdecl GetThing(unsigned h);                    // 0x00b18e00
Ent* __cdecl GetEnt(unsigned h);                        // 0x00eebf80
V3* __cdecl ObjPlaneVec(unsigned h, V3* result);        // 0x00efd8e0 (esi = result, edi = h in the original)

struct Query {
  int mode;
  int a;
  int b;
  float c;
  unsigned flags;
};
void __cdecl EntQuery(Ent* e, Thing* t, Query* q);      // 0x00eed720

struct SnapOpt {
  virtual void f();                                     // vtable at 0x0148b6e4
  bool on;
  SnapOpt() : on(true) {}
};
struct Planet {
  V3* Project(V3* sret, V3* from, V3* dir);             // 0x00b82110 (ret 12)
  V3* ProjectOpt(V3* sret, V3* from, V3* dir, SnapOpt* o);  // 0x00b82620 (ret 16)
};
Planet* PlanetModel();                                  // 0x00b3d350

bool __cdecl RayPlanet(V3* from, V3* dir, V3* zero, float maxT, float* t);  // 0x00ebaa20
void __cdecl QuaternionFromDirections(Quat* out, const V3* a, const V3* b); // 0x00698180
Quat* __cdecl QuatMul(Quat* out, const Quat* a, const Quat* b);             // 0x007dcb00
float* __cdecl SurfaceDir(float* out, float* dir, int lead, int* flag, int a5);  // 0x00eec2b0
void __cdecl EntRefresh(Ent* e);                        // 0x00eec440
struct EntMgr {
  void Commit(Ent* e, int arg);                         // 0x00f3da90 (ret 8)
};
void __cdecl EntSnap(Ent* e, void* v);                  // 0x00eee760

struct UICtx {
  int idx;                // +0x00
  char pad4[8];
  unsigned handle;        // +0x0c
  char pad10[0x64 - 0x10];
  bool m64;               // +0x64  drag/placement pending flag
  char pad65[3];
  int m68;                // +0x68  active editor mode (1..3)
  char pad6c[0x78 - 0x6c];
  float maxT;             // +0x78
  V3 m7c;                 // +0x7c
  float m88;              // +0x88
  char snapVec[0x14];     // +0x8c
  char m_a0[0x10];        // +0xa0
};
struct Services {
  char pad[0x74];
  EntMgr* mgr;            // +0x74
};
#define g_UI (*(UICtx**)0x016c7b88)        // 0x016c7b88
#define g_Svc (*(Services**)0x016c7aa4)    // 0x016c7aa4
#define g_Flag (*(char*)0x015acb40)        // 0x015acb40
#define g_Zero (*(V3*)0x016c7b98)          // 0x016c7b98

// Rotate the entity so that its orientation follows the change from its old to its new position.
static __forceinline void Reorient(Ent* e, const V3* oldPos, const V3* newPos) {
  Quat q1;
  q1.x = e->qx; q1.y = e->qy; q1.z = e->qz; q1.w = e->qw;
  Quat dq, prod;
  QuaternionFromDirections(&dq, oldPos, newPos);
  Quat r = *QuatMul(&prod, &dq, &q1);
  float inv = 1.0f / (float)sqrt((double)(r.w * r.w + r.z * r.z + r.y * r.y + r.x * r.x));
  e->qx = r.x * inv;
  e->qy = r.y * inv;
  e->qz = r.z * inv;
  e->qw = r.w * inv;
}

// @ 0x00f015b0
void DragObjectToSurface() {
  unsigned h = g_UI->handle;
  Thing* thing = GetThing(h);
  Ent* e = GetEnt(h);
  V3 plane;
  ObjPlaneVec(h, &plane);
  Query q;
  q.mode = 2;
  q.a = 0;
  q.b = 1;
  q.c = 0.0f;
  q.flags = 0;
  EntQuery(e, thing, &q);
  bool lead = ((q.flags >> 4) & 1) != 0;
  V3 origin, dir;
  AppGet()->GetViewer()->GetCameraRay(&origin, &dir);
  V3 from;
  from.x = plane.x + origin.x;
  from.y = origin.y + plane.y;
  from.z = origin.z + plane.z;
  SnapOpt opt;
  bool has = false;
  if (thing != 0 && thing->QueryInterface(0x137e8e0) != 0)
    has = true;
  Planet* pm = PlanetModel();
  V3 sret;
  V3 hit;
  if (lead) {
    V3* r = pm->ProjectOpt(&sret, &from, &dir, has ? &opt : 0);
    hit.x = r->x; hit.y = r->y; hit.z = r->z;
  } else {
    V3* r = pm->Project(&sret, &from, &dir);
    hit.x = r->x; hit.y = r->y; hit.z = r->z;
  }
  bool moved;
  if (hit.x == g_Zero.x && hit.y == g_Zero.y && hit.z == g_Zero.z)
    moved = false;
  else
    moved = true;

  if (0.1f < fabsf_(e->f220)) {
    float t;
    if (!RayPlanet(&from, &dir, &g_Zero, g_UI->maxT, &t))
      return;
    V3 p2;
    p2.x = dir.x * t + from.x;
    p2.y = dir.y * t + from.y;
    p2.z = dir.z * t + from.z;
    if (moved) {
      float dx = hit.x - from.x, dy = hit.y - from.y, dz = hit.z - from.z;
      float d = (float)sqrt((double)(dz * dz + dy * dy + dx * dx)) /
                (float)sqrt((double)(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y));
      if (!(t > d))
        hit = p2;
    } else {
      hit = p2;
    }
    V3 oldPos;
    oldPos.x = e->px; oldPos.y = e->py; oldPos.z = e->pz;
    Reorient(e, &oldPos, &hit);
    V3 sdir = hit;
    float scratch[3];
    int dummy;
    float* np = SurfaceDir(scratch, &sdir.x, lead, &dummy, g_Flag == 0);
    e->px = np[0]; e->py = np[1]; e->pz = np[2];
    if (0.1f < fabsf_(e->f220)) {
      float s = e->f220 / (float)sqrt((double)(e->px * e->px + e->py * e->py + e->pz * e->pz));
      e->px = e->px + e->px * s;
      e->py = e->py * s + e->py;
      e->pz = e->pz * s + e->pz;
    }
    EntRefresh(e);
    g_Svc->mgr->Commit(e, 0);
    if (g_Flag != 0)
      EntSnap(e, g_UI->snapVec);
  } else if (moved) {
    V3 oldPos;
    oldPos.x = e->px; oldPos.y = e->py; oldPos.z = e->pz;
    Reorient(e, &oldPos, &hit);
    e->px = hit.x; e->py = hit.y; e->pz = hit.z;
    EntRefresh(e);
    g_Svc->mgr->Commit(e, 0);
    if (g_Flag != 0)
      EntSnap(e, g_UI->snapVec);
  }
}

// ---------------------------------------------------------------------------
// scenario tutorial / editor UI helpers
// ---------------------------------------------------------------------------

extern "C" long double sqrtl(long double);
extern "C" void __cdecl FUN_00f47380(void* pMemory);      // 0x00f47380 operator delete

class cRefCounted {
public:
  virtual void v00();
  virtual void Release();                                 // vtable +0x04
};

// Reference-counted pointer that releases (but keeps) whatever it points at.
template <class T>
class AutoRefCount {
public:
  T* mpPtr;                                               // +0x00
  ~AutoRefCount() { if (mpPtr) mpPtr->Release(); }
};

struct StarVector {                                       // eastl::vector<AutoRefCount<cStarRecord>>
  void* mpBegin;                                          // +0x00
  void* mpEnd;                                            // +0x04
  void* mpEndCapacity;                                    // +0x08
  ~StarVector();                                          // 0x00ae6970
};

// Buffer whose refcount lives just in front of the first element.
struct SpVectorPtr {
  void* mpBegin;                                          // +0x00
  ~SpVectorPtr() {
    if (mpBegin != 0 && ((int32_t*)mpBegin)[-1] != 0)
      FUN_00f47380(mpBegin);
  }
};

class cScenarioTutorialsList {
public:
  ~cScenarioTutorialsList();                              // 0x00f01d60
  uint32_t pad00;                                         // +0x00
  AutoRefCount<cRefCounted> m04;                          // +0x04
  AutoRefCount<cRefCounted> m08;                          // +0x08
  AutoRefCount<cRefCounted> m0c;                          // +0x0c
  AutoRefCount<cRefCounted> m10;                          // +0x10
  AutoRefCount<cRefCounted> m14;                          // +0x14
  AutoRefCount<cRefCounted> m18;                          // +0x18
  AutoRefCount<cRefCounted> m1c;                          // +0x1c
  AutoRefCount<cRefCounted> m20;                          // +0x20
  AutoRefCount<cRefCounted> m24;                          // +0x24
  AutoRefCount<cRefCounted> m28;                          // +0x28
  AutoRefCount<cRefCounted> m2c;                          // +0x2c
  uint32_t pad30;                                         // +0x30
  StarVector m34;                                         // +0x34
  uint8_t pad40[0x14];                                    // +0x40
  AutoRefCount<cRefCounted> m54;                          // +0x54
  AutoRefCount<cRefCounted> m58;                          // +0x58
  AutoRefCount<cRefCounted> m5c;                          // +0x5c
  AutoRefCount<cRefCounted> m60;                          // +0x60
  uint8_t pad64[0x28];                                    // +0x64
  SpVectorPtr m8c;                                        // +0x8c
};

// @ 0x00f01d60
cScenarioTutorialsList::~cScenarioTutorialsList()
{
}

// ---------------------------------------------------------------------------
// tutorial state consulted by the editor refresh / placement path
// ---------------------------------------------------------------------------

#define g_TutorialsEnabled (*(char*)0x016065f8)            // 0x016065f8
#define g_pActiveTutorial (*(void**)0x015ad298)            // 0x015ad298

struct cScenarioTutorials {
  bool CheckObject(uint32_t handle);                       // 0x00efeae0
};
extern cScenarioTutorials g_ScenarioTutorials;             // 0x015ad328
extern char g_ChecklistTutorialUI;                         // 0x016c7c08

struct cTutorialQuery {                                   // result of the 0x11966ed query
  void Finish();                                          // 0x00b16270
};

struct cTutorialManager {
  virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
  virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
  virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
  virtual void t30(); virtual void t34();
  virtual bool IsSuppressed();                            // +0x38
};

struct cTutorialEntry {
  virtual void e00(); virtual void e04(); virtual void e08();
  virtual cTutorialQuery* Query(unsigned id);             // +0x0c
};

struct cTutorialHost {
  virtual void h00(); virtual void h04(); virtual void h08(); virtual void h0c();
  virtual void h10(); virtual void h14(); virtual void h18(); virtual void h1c();
  virtual void h20(); virtual void h24(); virtual void h28(); virtual void h2c();
  virtual void h30(); virtual void h34();
  virtual cTutorialEntry* GetEntry();                     // +0x38
};

void __stdcall FUN_00efe930(uint32_t handle);             // 0x00efe930 ScenarioTutorials_SetSelectedWindow
void __stdcall FUN_00f00bd0(uint32_t handle);             // 0x00f00bd0 CommitPlacement

struct cPlacementThing {
  void SetPlacement();                                    // 0x00efccd0 (thing passed in eax)
};
struct cTutorialService {
  int32_t Place(uint32_t handle);                         // 0x00f32790
};

// @ 0x00f01e60
void FUN_00f01e60(uint32_t handle)
{
  if (g_TutorialsEnabled == 0)
    return;
  if (((cTutorialManager*)g_pActiveTutorial)->IsSuppressed())
    return;
  cTutorialHost* pHost = AppGet()->GetTutorialHost();
  cTutorialEntry* pEntry = pHost->GetEntry();
  if (pEntry == 0)
    return;
  cTutorialQuery* pQuery = pEntry->Query(0x11966ed);
  if (pQuery == 0)
    return;
  Ent* pEnt = GetEnt(handle);
  Thing* pThing = GetThing(handle);
  if (pEnt != 0) {
    if (g_pActiveTutorial == (void*)&g_ScenarioTutorials)
      FUN_00efe930(handle);
    ((cPlacementThing*)pThing)->SetPlacement();
    pQuery->Finish();
    return;
  }
  if (pThing != 0) {
    cTutorialService* pService = (cTutorialService*)*((void**)((uint8_t*)g_Svc + 0x18));
    int32_t placed = pService->Place(handle);
    if (g_pActiveTutorial == (void*)&g_ChecklistTutorialUI && placed != 0)
      FUN_00f00bd0(handle);
    ((cPlacementThing*)pThing)->SetPlacement();
    pQuery->Finish();
  }
}

// ---------------------------------------------------------------------------
// editor refresh
// ---------------------------------------------------------------------------

struct cProjection {                                     // object living at g_UI + 0x7c
  void ProjectHit(const V3* pScratch, const void* pBounds); // 0x00efd830 (first argument in eax)
};

void __cdecl FUN_00efd970(uint32_t handle);              // 0x00efd970
void __cdecl FUN_00efdc00();                             // 0x00efdc00
void __cdecl FUN_00f011b0();                             // 0x00f011b0 UI::cScenarioTutorialsChecklistUI::BuildScene
void __cdecl FUN_00ed4e90();                             // 0x00ed4e90
void __cdecl FUN_00ed54b0(Ent* pEnt);                    // 0x00ed54b0

struct cSelectionService {
  int32_t Select(uint32_t handle, int32_t unselect);      // 0x00f3bbd0
};

// @ 0x00f01c20
void FUN_00f01c20()
{
  uint32_t handle = g_UI->handle;
  Ent* pEnt = GetEnt(handle);
  if (pEnt == 0)
    return;
  if (g_UI->m64) {
    g_UI->m64 = false;
    switch (g_UI->m68) {
    case 1:
      g_UI->m88 = pEnt->f220;
      // fall through: modes 1 and 3 measure the offset of the object
    case 3:
      g_UI->maxT = (float)sqrtl((long double)pEnt->px * pEnt->px
                                + (long double)pEnt->py * pEnt->py
                                + (long double)pEnt->pz * pEnt->pz);
      FUN_00efd970(handle);
      break;
    case 2: {
      V3 scratch;
      g_UI->m7c = *(const V3*)&pEnt->px;
      ((cProjection*)&g_UI->m7c)->ProjectHit(&scratch, g_UI->m_a0);
      break;
    }
    }
  }
  switch (g_UI->m68) {
  case 1:
    DragObjectToSurface();
    break;
  case 2:
    FUN_00efdc00();
    break;
  case 3:
    FUN_00f011b0();
    break;
  }
  if (0.1f >= fabsf_(pEnt->f220)) {
    FUN_00ed4e90();
  } else {
    FUN_00ed54b0(pEnt);
  }
  cSelectionService* pService = (cSelectionService*)*((void**)((uint8_t*)g_Svc + 0x74));
  bool bFound = g_ScenarioTutorials.CheckObject(handle);
  pService->Select(handle, bFound ? 0 : 1);
}

// ---------------------------------------------------------------------------
// import a grid description and commit it to the scene
// ---------------------------------------------------------------------------

bool __cdecl FUN_00efc9c0();                              // 0x00efc9c0

// object the editor hands over: a count and a path/name for an import
struct cGridProvider {
  uint32_t GetCount();                                    // 0x008d3ac0
  void* GetPath(int32_t mode);                            // 0x00688ed0
};

// 0x90-byte EA::IO::FileStream
struct FileStream {
  void* mpVt00;                                           // +0x00
  uint8_t pad04[0x8c];
  void Ctor(const wchar_t* pName);                        // 0x00931e10
  void AddRef();                                          // 0x009317b0
  bool Open(unsigned f0, unsigned f1, unsigned f2, unsigned f3);  // 0x009318f0
  bool Close();                                           // 0x00931a70
  void Dtor();                                            // 0x00931e70
};

// 0x14-byte import record filled from the stream
struct cImportInfo {
  void* mpVt00;                                           // +0x00
  uint32_t mAsset;                                        // +0x04
  uint8_t pad08[0xc];
  void Ctor();                                            // 0x005f8e00
  void Dtor();                                            // 0x005f8e40
};

struct cImportReader {
  bool Read();                                            // 0x005fbb00
};
void* __stdcall FUN_005f7930(FileStream* pStream, cImportInfo* pInfo, int32_t zero); // 0x005f7930
bool __stdcall FUN_004bbe20(uint32_t asset, int32_t zero);                 // 0x004bbe20 SetAssetData

struct V3Vector {                                          // eastl::sp_vector<V3>
  V3* mpBegin;                                             // +0x00
  V3* mpEnd;                                               // +0x04
  V3* mpEndCapacity;                                       // +0x08
  void Destroy();                                          // 0x00540520
};
void* __stdcall FUN_005f7930(V3Vector* pGrid, void* pObj);                 // 0x005f7930 fill helper
struct cFillResult {
  void Commit();                                           // 0x005fd260
};
int32_t __cdecl FUN_00efe870(const V3* pPoint);           // 0x00efe870 FindSurfacePoint
int32_t __cdecl FUN_00eece20(const V3* pPoint);           // 0x00eece20 ResourceKeyToIcon

// icon bookkeeping service hanging off g_Svc + 0x14
struct cIconService {
  int32_t GetIconCount(int32_t key);                      // 0x00ed20c0
  void RemoveIcon(int32_t id);                            // 0x00ed38a0
};
// table owned by the editor, maps a grid point to an icon id
struct cPointTable {
  int32_t FindPoint(const V3* pPoint);                    // 0x00f46450
};

struct cSPEditorDevUI {
  virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
  virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
  virtual void g20(); virtual void g24(); virtual void g28(); virtual void g2c();
  virtual void g30();
  virtual bool RefreshGrid(int32_t id);                    // +0x34
  uint32_t pad04;                                          // +0x04
  void* mpTable08;                                         // +0x08
  bool RefreshGrids(int32_t argUnused, void* pObj);        // 0x00f01f40
};

// @ 0x00f01f40
bool cSPEditorDevUI::RefreshGrids(int32_t argUnused, void* pObj)
{
  (void)argUnused;
  if (g_UI->handle != 0)
    return false;
  if (!FUN_00efc9c0())
    return false;
  cGridProvider* pProvider = (cGridProvider*)pObj;
  if (pProvider->GetCount() >= 1) {
    FileStream stream;
    stream.Ctor((const wchar_t*)pProvider->GetPath(0));
    stream.AddRef();
    if (!stream.Open(1, 3, 1, 0)) {
      stream.Dtor();
      return false;
    }
    cImportInfo info;
    info.Ctor();
    cImportReader* pReader = (cImportReader*)FUN_005f7930(&stream, &info, 0);
    bool bRead = pReader->Read();
    uint32_t asset = bRead ? info.mAsset : 0;
    stream.Close();
    info.Dtor();
    if (asset == 0) {
      stream.Dtor();
      return false;
    }
    if (!FUN_004bbe20(asset, 0)) {
      stream.Dtor();
      return false;
    }
    stream.Dtor();
  }
  V3Vector grid;
  grid.mpBegin = 0;
  grid.mpEnd = 0;
  grid.mpEndCapacity = 0;
  cFillResult* pFill = (cFillResult*)FUN_005f7930(&grid, pObj);
  pFill->Commit();
  int32_t count = (int32_t)((uint8_t*)grid.mpEnd - (uint8_t*)grid.mpBegin) / 12;
  if (count == 0) {
    if (grid.mpBegin != 0 && ((int32_t*)grid.mpBegin)[-1] != 0)
      FUN_00f47380(grid.mpBegin);
    return false;
  }
  V3 first;
  first.x = grid.mpBegin[0].x;
  first.y = grid.mpBegin[0].y;
  first.z = grid.mpBegin[0].z;
  int32_t id = FUN_00efe870(&first);
  if (id == -1) {
    int32_t key = FUN_00eece20(&first);
    if (key == 0x867a9ee9) {
      grid.Destroy();
      return false;
    }
    void* pService = *((void**)((uint8_t*)g_Svc + 0x14));
    cIconService* pIcons = (cIconService*)*((void**)((uint8_t*)pService + 0x14));
    if (pIcons->GetIconCount(key) < 1) {
      grid.Destroy();
      return false;
    }
    id = ((cPointTable*)mpTable08)->FindPoint(&first);
    if (id == -1) {
      grid.Destroy();
      return false;
    }
    pIcons->RemoveIcon(id);
  }
  bool bDone = RefreshGrid(id);
  grid.Destroy();
  return bDone;
}
