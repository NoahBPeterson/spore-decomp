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
struct AppObj {
  P4(0) P4(1) P4(2) P4(3) P4(4)
  virtual void p5a(); virtual void p5b();
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
  char pad10[0x78 - 0x10];
  float maxT;             // +0x78
  char pad7c[0x8c - 0x7c];
  char snapVec[0x14];     // +0x8c
};
struct Services {
  char pad[0x74];
  EntMgr* mgr;            // +0x74
};
extern UICtx* g_UI;           // 0x016c7b88
extern Services* g_Svc;       // 0x016c7aa4
extern char g_Flag;           // 0x015acb40
extern V3 g_Zero;             // 0x016c7b98

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
