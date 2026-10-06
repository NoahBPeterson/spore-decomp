// Slice s00efd020 — Simulator camera/selection helpers and editor UI update.
// /O2 /MD /Gy /EHsc /TP region.
#include "types.h"
#include <math.h>

struct VObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* s3(unsigned);
};

struct SelCtx {
    bool FUN_00efde90(int param_2);
};

// @ 0x00efde90
bool SelCtx::FUN_00efde90(int param_2) {
    int* base = (int*)param_2;
    int* p = *(int**)((char*)base + 0x20);
    if (*(char*)((char*)p + 0x18) == 1) {
        int* q = (int*)((char*)p + *(int*)((char*)p + 0x10));
        if (q != 0) {
            int* piVar1 = (int*)q[3];
            if (piVar1 != 0 && *(char*)((char*)this + 4) != 0) {
                if (((VObj*)piVar1)->s3(0x137e8e0) != 0)
                    return false;
            }
        }
    }
    return true;
}


// ---------------------------------------------------------------------------
// Editor tool-state update (everything keyed off the global at 0x016c7b88) and the
// camera-ray helpers it uses.  Layouts come from the retail disassembly; real class names are
// unknown.  Helpers that take implicit register arguments (esi/edi/eax) in the original are
// written with explicit parameters.  Offsets use the AT() accessor where only a few fields are touched.
// ---------------------------------------------------------------------------
#define AT(T, p, off) (*(T*)((char*)(p) + (off)))

struct V3 { float x, y, z; };
struct V4 { float x, y, z, w; };

// A tool slot; vtable slot 21 (+0x54) sets its target object.
struct Widget {
  virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20();
  virtual void SetTarget(void* v);   // +0x54
  void F658e0(void* a);              // 0x00c658e0 (Simulator::cMorphHandle)
  void F666f0(float a, float b);     // 0x00c666f0
  void SetTLerp(float t);            // 0x00c65b50 (cSimpleRotationRing::SetTLerp)
  void SetT(float t);                // 0x00c65af0 (cSimpleRotationRing::SetT)
  void F68ae0(void* a);              // 0x00c68ae0
};
struct Setter {
  void F68d70(void* a, void* b);     // 0x00c68d70
  void F68850(void* a);              // 0x00c68850
};

struct Viewer {
  void GetCameraRay(V3* origin, V3* dir);                          // 0x007c4900
  void GetCameraLocationInfo(int a, V3* out, int b, int c);         // 0x007c3d30
  void F7c46f0(V3* origin, V3* dir);                                // 0x007c46f0
};
struct AppObj {
  virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
  virtual Viewer* GetViewer();   // +0x58
};
AppObj* AppGet();                // 0x0067dd10 (SP::App)

struct Obj;
struct ThingA {                  // object wrapper used by the pick helpers
  virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10();
  virtual V3* GetPos();          // +0x2c
  virtual V4* GetRot();          // +0x30
};
ThingA* GetThingA(Obj* o);                       // 0x00b18e00
float* GetRefCounted18(Obj* o);                  // 0x00eebf80
V3* __cdecl FUN_0059aed0(V3* sret, const V3* a, const V3* b);   // 0x0059aed0 (hidden sret first)
struct Picker { bool F35bf0(); };                // 0x00b35bf0
Picker* __stdcall FUN_00b3d240(ThingA* t, V3* origin, V3* dir, V3* out);  // 0x00b3d240

struct UICtx {
  int idx;           // +0x00
  Obj* obj;          // +0x04
  int p8;
  int fc;            // +0x0c
  void* f10;         // +0x10
  Widget* f14;
  Widget* f18;
  Widget* f1c;
  Widget* f20;
  Widget* f24;
  Widget* f28;
  Widget* f2c;
  char setter30[0x24];   // +0x30 (Setter)
  Widget* f54;
  Widget* f58;
  char pad_5c[0x6c - 0x5c];
  V3 v6c;            // +0x6c
  char pad_78[4];
  V3 v7c;            // +0x7c
  char pad_88[4];
  char v8c[0x14];    // +0x8c
  float fa0;         // +0xa0
};
extern UICtx* g_UI;          // 0x016c7b88

// @ 0x00efd6e0 -- camera ray against the plane through *plane (esi) whose normal is the
// negated camera location vector; hit point written to *out (edi).
__declspec(noinline) bool RayHitPlane(const V3* plane, V3* out) {
  V3 dir, origin, cam;
  AppGet()->GetViewer()->GetCameraRay(&origin, &dir);
  AppGet()->GetViewer()->GetCameraLocationInfo(0, &cam, 0, 0);
  float nx = -cam.x, ny = -cam.y, nz = -cam.z;
  float denom = dir.z * nz + dir.y * ny + dir.x * nx;
  float pn = -(plane->z * nz + plane->y * ny + plane->x * nx);
  if (denom == 0.0f)
    return false;
  float t = -(((origin.z * nz + origin.y * ny + origin.x * nx) + pn) / denom);
  if (t < 0.0f)
    return false;
  out->x = origin.x + dir.x * t;
  out->y = origin.y + dir.y * t;
  out->z = origin.z + dir.z * t;
  return true;
}

// @ 0x00efd830 -- projects the plane hit onto the normalized vector *s (ecx); hit buffer in eax.
__declspec(noinline) void ProjectHit(const V3* s, V3* hit, float* out) {
  if (RayHitPlane(s, hit)) {
    float dx = hit->x - s->x, dy = hit->y - s->y, dz = hit->z - s->z;
    float inv = 1.0f / (float)sqrt((double)(s->x * s->x + s->y * s->y + s->z * s->z));
    *out = (s->x * inv) * dx + (inv * s->z) * dz + (s->y * inv) * dy;
  }
}

// @ 0x00efd8e0 -- esi = result vec3, edi = object.
__declspec(noinline) V3* ObjPlaneVec(Obj* obj, V3* result) {
  ThingA* t = GetThingA(obj);
  float* rc = GetRefCounted18(obj);
  V4* src = rc ? (V4*)((char*)rc + 0x10) : t->GetRot();
  V4 q = *src;
  V3 tmp;
  V3* r = FUN_0059aed0(&tmp, &g_UI->v6c, (V3*)&q);
  result->x = r->x;
  result->y = r->y;
  result->z = r->z;
  return result;
}

// @ 0x00efd970
char PickUpdate(Obj* obj) {
  V3 origin, dir;
  AppGet()->GetViewer()->F7c46f0(&origin, &dir);
  ThingA* t = GetThingA(obj);
  V3 q1 = *t->GetPos();
  V4 q2 = *t->GetRot();
  V3 hit;
  Picker* pk = FUN_00b3d240(t, &origin, &dir, &hit);
  bool ok = pk->F35bf0();
  if (!ok) {
    if (!RayHitPlane(&q1, &hit))
      return ok;
  }
  float* rc = GetRefCounted18(obj);
  V3 sret, delta, n;
  if (rc) {
    float px = AT(float, rc, 0x10), py = AT(float, rc, 0x14), pz = AT(float, rc, 0x18), pw = AT(float, rc, 0x1c);
    float inv = 1.0f / (((pw * pw + pz * pz) + py * py) + px * px);
    n.x = -(px * inv);
    n.y = -(py * inv);
    n.z = -(pz * inv);
    delta.x = AT(float, rc, 4) - hit.x;
    delta.y = AT(float, rc, 8) - hit.y;
    delta.z = AT(float, rc, 0xc) - hit.z;
    sret.x = q2.x; sret.y = q2.y; sret.z = q2.z;
  } else {
    float inv = 1.0f / ((((q2.z * q2.z + q2.w * q2.w) + q2.y * q2.y) + q2.x * q2.x));
    n.x = -(q2.x * inv);
    n.y = -(q2.y * inv);
    n.z = -(q2.z * inv);
    delta.x = q1.x - hit.x;
    delta.y = q1.y - hit.y;
    delta.z = q1.z - hit.z;
    sret = q1;
  }
  V3* r = FUN_0059aed0(&sret, &delta, &n);
  g_UI->v6c.x = r->x;
  g_UI->v6c.y = r->y;
  g_UI->v6c.z = r->z;
  return ok;
}

struct ThingC {                      // object at g->fc, its refcounted part at +0x00eebf80
};
struct SelState {
  int a, b, c;
  float d;
  uint32_t flags;
};
int __cdecl FUN_00eed720(float* rc, ThingA* t, SelState* st);       // 0x00eed720
float __cdecl FUN_00eec370(float* pos, int b, int* one);              // 0x00eec370
void __cdecl FUN_00eec8e0(float* rc, char* x, char* y);              // 0x00eec8e0
struct PlanetModelRes { V3* F82df0(); };                              // 0x00b82df0
PlanetModelRes* __stdcall PlanetModelCtor(V3* buf, float* pos, int b, int c, int d, int e);   // 0x00b3d350
struct Mgr { void F3da90(float* rc, int a); };                        // 0x00f3da90
struct G2 { char pad_0[0x14]; void* f14; char pad_18[0x74 - 0x18]; Mgr* f74; };
extern G2* g_G2;                                                      // 0x016c7aa4
extern char g_15acb40;
void __cdecl FUN_00eee760(float* rc, void* v8c);                      // 0x00eee760

// @ 0x00efdc00
void ToolSnapUpdate() {
  UICtx* g = g_UI;
  Obj* obj = (Obj*)g->fc;
  float* rc = GetRefCounted18(obj);
  ThingA* t = GetThingA(obj);
  const V3* s = &g_UI->v7c;
  V3 r;
  float f;
  if (RayHitPlane(s, &r)) {
    float dx = r.x - s->x, dy = r.y - s->y, dz = r.z - s->z;
    float inv = 1.0f / (float)sqrt((double)(s->x * s->x + s->y * s->y + s->z * s->z));
    f = (s->x * inv) * dx + (inv * s->z) * dz + (inv * s->y) * dy;
  }
  g = g_UI;
  f = f - g->fa0;
  float inv2 = 1.0f / (float)sqrt((double)(g->v7c.x * g->v7c.x + g->v7c.y * g->v7c.y + g->v7c.z * g->v7c.z));
  r.x = g->v7c.x + (g->v7c.x * inv2) * f;
  r.y = g->v7c.y + (g->v7c.y * inv2) * f;
  r.z = g->v7c.z + (g->v7c.z * inv2) * f;
  float* pos = rc + 1;
  AT(float, rc, 4) = r.x;
  AT(float, rc, 8) = r.y;
  AT(float, rc, 0xc) = r.z;
  SelState st;
  st.a = 2; st.b = 0; st.c = 1; st.d = 0.0f; st.flags = 0;
  FUN_00eed720(rc, t, &st);
  int b = (st.flags >> 4) & 1;
  int one = 1;
  AT(float, rc, 0x220) = FUN_00eec370(pos, b, &one);
  char bx, by;
  FUN_00eec8e0(rc, &bx, &by);
  float v = AT(float, rc, 0x220);
  if ((v > 0.0f && by == 0) || (v < 0.0f && bx == 0)) {
    V3 buf;
    V3* p = PlanetModelCtor(&buf, pos, b, 1, 1, 0)->F82df0();
    AT(float, rc, 4) = p->x;
    AT(float, rc, 8) = p->y;
    AT(float, rc, 0xc) = p->z;
    AT(float, rc, 0x220) = 0.0f;
  }
  g_G2->f74->F3da90(rc, 0);
  if (g_15acb40)
    FUN_00eee760(rc, g_UI->v8c);
}

struct Sub14 {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual bool V5();             // +0x14
};
struct ObjQ {
  virtual void o0(); virtual void o1(); virtual void o2();
  virtual void* Query(unsigned id);   // +0x0c
  uint32_t pad_4[4];
  Sub14* f14;                         // +0x14
};
struct ThingB;
struct Thing2 {
  char pad_0[0x54];
  struct SubQ* f54;
};
struct SubQ {
  virtual void q0(); virtual void q1(); virtual void q2();
  virtual void* Query(unsigned id);   // +0x0c
};
struct ThingB {
  virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10();
  virtual int V11(float f);           // +0x2c
  virtual void V12();
  virtual float V13(void* a);         // +0x34
  virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30(); virtual void c31();
  virtual Thing2* V46(unsigned id);   // +0xb8
  bool F88940(unsigned id);           // 0x00c88940
  void F8b1a0(unsigned id);           // 0x00c8b1a0
  void F88a00(unsigned id, float v);  // 0x00c88a00
  void F8a020(unsigned id, float v);  // 0x00c8a020
  void F8ad30(unsigned id, int v);    // 0x00c8ad30
};
float __cdecl ResourceScaledFloat(ThingB* p);    // 0x00eec820
ThingB* GetThingB(ObjQ* o);                       // 0x00b18e00
float* GetRefCountedQ(ObjQ* o);                   // 0x00eebf80
struct Owner { void* F3e900(ObjQ* o); };          // 0x00f3e900
struct Res {                                      // object returned by Owner::F3e900
  bool F253e0();                                  // 0x00f253e0
  bool F255d0();                                  // 0x00f255d0
};
bool __cdecl IsInState2or10(void* p);             // 0x00efcfb0 (ScenarioTutorials_IsInState2or10)
struct InputMgr { virtual void i0(); virtual void i1(); virtual void i2(); virtual void i3(); virtual void i4(); virtual void i5(); virtual bool IsKey(unsigned k); };
InputMgr* GameInputManager();                     // 0x00b3d250
extern unsigned g_15ad294;
bool __cdecl FUN_00f212c0(int v);                 // 0x00f212c0
struct ObjQ2 : ObjQ {
  void F5ce30(void* a, void* b, float c);         // 0x00efce30
};
struct Mgr2 { int F3dc70(Thing2* t); };           // 0x00f3dc70
struct G2b { char pad_0[0x14]; void* f14; char pad_18[0x74 - 0x18]; Mgr2* f74; };
extern G2b* g_G2b;
void FUN_00ed4e90(void* a);                       // 0x00ed4e90 (tail call, arg ecx)
struct CtlQ {
  char pad_0[6]; bool b6; char pad_7; Owner* f8;
  void Update();
};
struct UICtx2 {
  int idx; ObjQ* obj; int p8; int fc; void* f10;
  Widget* f14; Widget* f18; Widget* f1c; Widget* f20; Widget* f24; Widget* f28; Widget* f2c;
  char setter30[0x24];
  Widget* f54; Widget* f58;
};
extern UICtx2* g_UI2;

// @ 0x00efd020 -- per-frame update of the editor tool slots (g_UI->f14..f2c, f54, f58).
void CtlQ::Update() {
  UICtx2* g = g_UI2;
  if (!g->f18)
    return;
  ObjQ* obj = g->obj;
  void *A = 0, *B = 0, *C = 0, *D = 0, *F = 0, *G = 0, *H = 0, *I = 0, *J = 0, *K = 0;
  ThingB* p = GetThingB(obj);
  if (p) {
    float* q = GetRefCountedQ(obj);
    if (q) {
      Res* r = (Res*)f8->F3e900(obj);
      g = g_UI2;
      int mode;
      if (r)
        mode = *(int*)(*(char**)((char*)r + 0x70) + g->idx * 0x4e0 + 0x4b8);
      else
        mode = 1;
      bool flag4;
      if (obj && obj->f14)
        flag4 = obj->f14->V5();
      else
        flag4 = true;
      if (!b6 && r) {
        int idx = g->idx;
        if (IsInState2or10(*(char**)((char*)r + 0x70) + idx * 0x4e0)) {
          H = p;
          ((Setter*)g->setter30)->F68d70((char*)q + 4, *(char**)((char*)q + 0x28) + idx * 0x34 + 0x1c);
        } else if (r->F253e0()) {
          g = g_UI2;
          G = p;
          g->f28->F68ae0((char*)q + 0x1e8);
          ((ObjQ2*)obj)->F5ce30((char*)q + 0x1e8, (char*)q + 0x1f4, AT(float, q, 0x204));
        }
      }
      if (obj) {
        void* X = obj->Query(0x74e0069);
        if (X) {
          if (AT(float, X, 0x178) != AT(float, X, 0x17c)) {
            J = p;
            g_UI2->f54->F658e0((char*)X + 0x18c);
            g_UI2->f54->F666f0(AT(float, X, 0x178), AT(float, X, 0x17c));
            g_UI2->f54->SetTLerp(AT(float, X, 0x164) / (AT(float, X, 0x16c) - AT(float, X, 0x168)));
          }
          if (AT(float, X, 0x180) != AT(float, X, 0x184)) {
            K = p;
            g_UI2->f58->F658e0((char*)X + 0x198);
            g_UI2->f58->F666f0(AT(float, X, 0x180), AT(float, X, 0x184));
            g_UI2->f58->SetTLerp(AT(float, X, 0x98) / (AT(float, X, 0x174) - AT(float, X, 0x170)));
          }
        }
        void* Y = obj->Query(0x7b38ba7);
        if (Y) {
          if (AT(float, Y, 0x138) != AT(float, Y, 0x13c)) {
            J = p;
            g_UI2->f54->F658e0((char*)Y + 0x150);
            g_UI2->f54->F666f0(AT(float, Y, 0x138), AT(float, Y, 0x13c));
            g_UI2->f54->SetTLerp(AT(float, Y, 0x124) / (AT(float, Y, 0x12c) - AT(float, Y, 0x128)));
          }
          if (AT(float, Y, 0x140) != AT(float, Y, 0x144)) {
            K = p;
            g_UI2->f58->F658e0((char*)Y + 0x15c);
            g_UI2->f58->F666f0(AT(float, Y, 0x140), AT(float, Y, 0x144));
            g_UI2->f58->SetTLerp(AT(float, Y, 0x98) / (AT(float, Y, 0x134) - AT(float, Y, 0x130)));
          }
        }
      }
      Thing2* t = p->V46(0x175cdc9);
      g = g_UI2;
      if (g->obj) {
        if ((g->fc == 0 || g->f10 != g->f28) && t && G)
          D = GetThingB((ObjQ*)t->f54);
        g = g_UI2;
        if (g->obj && (g->fc == 0 || g->f10 != 0)) {
          if (flag4)
            C = p;
          if (r) {
            if (flag4 && r->F255d0()) {
              F = p; A = p; B = p;
            }
            if (mode == 3) {
              float lf = ResourceScaledFloat(p);
              float* tbl = (float*)(g_UI2->idx * 0x34 + *(char**)((char*)q + 0x28));
              float v = (*tbl > lf) ? *tbl : lf;
              g_UI2->f2c->SetT(v);
              I = p;
              if (!p->F88940(0x65640a90)) {
                p->F8b1a0(0x65640a90);
                p->F88a00(0x65640a90, 1000000.0f);
              }
              p->F8a020(0x65640a90, v);
            } else {
              p->F8ad30(0x65640a90, 1);
            }
            g = g_UI2;
          }
          if (g->f10 == g->f18) {
            C = 0; B = 0; F = 0;
          } else if (g->f10 == g->f1c) {
            C = 0; A = 0; F = 0;
          } else if (g->f10 == g->f20) {
            B = 0; A = 0; F = 0;
          } else {
            if (GameInputManager()->IsKey(g_15ad294)) {
              F = 0;
            } else {
              B = 0; A = 0;
            }
          }
        }
      }
      if (G) {
        Thing2* t2 = ((ThingB*)G)->V46(0x175cdc9);
        int rv = g_G2b->f74->F3dc70(t2);
        void* sub = t2->f54 ? t2->f54->Query(0x1186577) : 0;
        ThingB* gt = (ThingB*)G;
        float fv = gt->V13((char*)rv + 0x1e8);
        int iv = gt->V11(fv);
        if (FUN_00f212c0(iv)) {
          AT(char, gt, 0x6e) = 0;
          if (sub)
            AT(char, sub, 0x6e) = 0;
        } else {
          AT(char, gt, 0x6e) = 1;
          if (sub)
            AT(char, sub, 0x6e) = 1;
        }
      }
    }
  }
  g = g_UI2;
  g->f18->SetTarget(A);
  g_UI2->f1c->SetTarget(B);
  g_UI2->f20->SetTarget(C);
  g_UI2->f14->SetTarget(D);
  g_UI2->f24->SetTarget(F);
  g_UI2->f28->SetTarget(G);
  g_UI2->f2c->SetTarget(I);
  ((Setter*)g_UI2->setter30)->F68850(H);
  g_UI2->f54->SetTarget(J);
  g_UI2->f58->SetTarget(K);
  if (!obj)
    FUN_00ed4e90(g_G2b->f14);
}
