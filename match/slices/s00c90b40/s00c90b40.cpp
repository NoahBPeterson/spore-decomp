// match/slices/s00c90b40/s00c90b40.cpp
// Object file: SPGameSystems/SPTribe.obj (SP::cTribe and eastl helpers).
// Functions: 00c90b40 00c90da0 00c90df0 00c90e40 00c90e80 00c90f50 00c91030
//            00c91190 00c91250 00c91700 00c91800 00c91970 00c919e0
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2
//        (00c90b40, 00c90f50, 00c91250, 00c91700 and 00c91800 use scalar SSE;
//         the POD element copies 00c90da0/df0/e40 use x87 fld/fstp in retail,
//         which one TU-wide flag set cannot also produce.)
//
// The tribe object layout is only partly known; it is modelled with named
// role+offset stub structs so that every field access stays a named member.

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   SIZE_T;

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Quat { float x, y, z, w; };
struct Matrix33 { float m[9]; };

extern "C" {
double __cdecl sin(double);              // x87 fsin in retail
double __cdecl cos(double);              // x87 fcos in retail
double __cdecl sqrt(double);
}

// ---------------------------------------------------------------------------
// The 0x14-byte vector element used by the eastl copy/fill helpers:
// four floats followed by one trailing byte.
// ---------------------------------------------------------------------------
struct Elem14 {
  float mX, mY, mZ, mW;                  // 0x00
  u8    mB_10;                           // 0x10
  u8    mPad_11[3];                      // 0x11
};

// ---------------------------------------------------------------------------
// Intrusive ref-counted object: slot 0 AddRef, slot 4 Release.
// ---------------------------------------------------------------------------
struct RefCnt {
  virtual void AddRef();                 // 0x00
  virtual void Release();                // 0x04
};

// ---------------------------------------------------------------------------
// Spatial object: the tribe's placement interface.  Slot offsets are the
// retail vtable byte offsets.
// ---------------------------------------------------------------------------
struct cSpatial {
  virtual void  v00();                   // 0x00
  virtual void  v04();                   // 0x04
  virtual void  v08();                   // 0x08
  virtual void  v0c();                   // 0x0c
  virtual void  v10();                   // 0x10
  virtual void  v14();                   // 0x14
  virtual void  v18();                   // 0x18
  virtual void  v1c();                   // 0x1c
  virtual void  v20();                   // 0x20
  virtual void  v24();                   // 0x24
  virtual void  v28();                   // 0x28
  virtual Vec3* GetPosition();           // 0x2c
  virtual Quat* GetRotation();           // 0x30
  virtual void  v34();                   // 0x34
  virtual void  SetPosition(Vec3* p);    // 0x38
  virtual void  v3c();                   // 0x3c
  virtual void  v40();                   // 0x40
  virtual void  v44();                   // 0x44
  virtual void  v48();                   // 0x48
  virtual void  v4c();                   // 0x4c
  virtual void  v50();                   // 0x50
  virtual s32   v54();                   // 0x54
  virtual u8    IsValid();               // 0x58
  virtual void  v5c(Vec3* out);          // 0x5c
  virtual void  v60();  virtual void v64();  virtual void v68();  virtual void v6c();
  virtual void  v70();  virtual void v74();  virtual void v78();  virtual void v7c();
  virtual void  v80();  virtual void v84();  virtual void v88();  virtual void v8c();
  virtual void  v90();  virtual void v94();  virtual void v98();  virtual void v9c();
  virtual void  va0();
  virtual s32   vA4();                   // 0xa4 (tribe money getter)
  u8 mBody_04[0x5c];                     // 0x04
};

// ---------------------------------------------------------------------------
// The planet body that accepts a placement transform.
// ---------------------------------------------------------------------------
struct cPlanetBody {
  virtual void v00();                    // 0x00
  virtual void v04();  virtual void v08();  virtual void v0c();
  virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
  virtual void v20();  virtual void v24();  virtual void v28();  virtual void v2c();
  virtual void v30();  virtual void v34();  virtual void v38();  virtual void v3c();
  virtual void v40();  virtual void v44();  virtual void v48();  virtual void v4c();
  virtual void v50();
  virtual u32  AddTransform(void* xform, u32 id);   // 0x54
};

struct cPlanetModel {
  u8           mPad_00[0x24];           // 0x00
  cPlanetBody* mpBody_24;                // 0x24
};

// A placement transform: flags word, stamp word, position, scale and a 3x3
// rotation.
struct cTransform {
  u16      mFlags_00;                    // 0x00
  u16      mStamp_02;                    // 0x02
  Vec3     mPos_04;                      // 0x04
  float    mScale_10;                    // 0x10
  Matrix33 mRot_14;                      // 0x14
};

// Matrix33 builder from a named preset.
struct Matrix33Obj {
  Matrix33 mMat_00;                      // 0x00
  void ctor(const void* preset);         // 0x0041cb40
};

// ---------------------------------------------------------------------------
// Interactable object owned by the fishing hot spot.
// ---------------------------------------------------------------------------
struct cInteractable {
  virtual void  AddRef();                // 0x00
  virtual void  Release();               // 0x04
  virtual void* QueryInterface(u32 id);  // 0x08
  virtual void  v0c();                   // 0x0c
  void SetAreaData(Vec3* pos, float radius);   // 0x00c3f160
  void SetParams(float a, float b);            // 0x00c3f1b0
  void AttachEffect(void* effect);             // 0x00c3f2d0
};

// The splash effect object (a cVisualEffect).
struct cSplashEffect {
  virtual void  AddRef();                // 0x00
  virtual void  Release();               // 0x04
  virtual void  v08();  virtual void v0c();
  virtual void  v10();  virtual void v14();  virtual void v18();  virtual void v1c();
  virtual void  v20();  virtual void v24();  virtual void v28();  virtual void v2c();
  virtual void  v30();  virtual void v34();
  virtual void  SetPosition(Vec3* p);    // 0x38
  u8        mPad_04[0x70 - 0x04];        // 0x04
  cSpatial  mPlacement_70;               // 0x70
  u8        mPad_d0[0xe1 - 0xd0];        // 0xd0
  u8        mVisible_e1;                 // 0xe1
};

// ---------------------------------------------------------------------------
// A tool: the anchor sub-object sits at +0x34 and exposes GetPosition at 0x2c.
// ---------------------------------------------------------------------------
struct cTool {
  u8       mPad_00[0x34];                // 0x00
  cSpatial mAnchor_34;                   // 0x34
};

// The area object a tool is placed against.
struct cPlacementArea {
  u8       mPad_00[0x34];                // 0x00
  cSpatial mAnchor_34;                   // 0x34
  u8       mPad_94[0xa3 - 0x94];         // 0x94
  u8       mB_a3;                        // 0xa3
  u8       mPad_a4[0x12c - 0xa4];        // 0xa4
  u32      mFlags_12c;                   // 0x12c (0 means "3")
  u32      mConnected_130;               // 0x130
};

// The tribe's tool placements.  cTribe derives from the spatial interface so
// its own vtable (including the money getter at 0xa4) starts at offset 0.
struct cTribe : cSpatial {
  u8       mPad_60[0x120 - 0x60];        // 0x60
  cSpatial mSpatial_120;                 // 0x120
  u8       mPad_180[0x1d4 - 0x180];      // 0x180
  s32      mMoney_1d4;                   // 0x1d4 (tribe funds)
  u8       mPad_1d8[0x2d4 - 0x1d8];      // 0x1d8
  u32      mEffectId_2d4;                // 0x2d4
  u8       mPad_2d8[4];                  // 0x2d8
  Vec3     mToolSlots_2dc[3];            // 0x2dc (per-kind tool anchors)
  u8       mPad_300[0x504 - 0x300];     // 0x300
  Vec3     mToolAnchor_504;              // 0x504 (kind-0 anchor)
  u8       mPad_510[0x19d4 - 0x510];     // 0x510
  u32      mAreaEffect_19d4;             // 0x19d4

  cTool* GetToolOfType(s32 type);                 // 0x00c8f6e0
  float* GetToolPosition(float* out, s32 kind);    // 0x00c91190
  void   UpdateToolPositions();                   // 0x00c91250
  void   UpgradeHut();                            // 0x00c919e0
  void   CheckFoodTutorialComplete();             // 0x00c91970
  void   FUN_00c8f3d0(s32 a, void* b, float c, s32 d, Vec3* e, u32 f); // 0x00c8f3d0
  void   RefreshAreaEffect();                     // 0x00c91700
};

// The sub-object at cTribe+0xec that tracks the current tool placement.
struct cToolPlacement {
  virtual void  v00();                   // 0x00
  virtual void  v04();  virtual void v08();  virtual void v0c();
  virtual void  v10();  virtual void v14();  virtual void v18();  virtual void v1c();
  virtual void  v20();  virtual void v24();  virtual void v28();  virtual void v2c();
  virtual void  v30(cPlacementArea* area);   // 0x30
  u8     mPad_04[0xdc - 0x04];           // 0x04
  Vec3   mOffset_dc;                     // 0xdc
  u8     mPad_e8[0x100 - 0xe8];          // 0xe8

  void SetPlacementArea(cPlacementArea* area);     // 0x00c91800
  cTribe* Tribe() { return (cTribe*)((u8*)this - 0xec); }
};

// The fishing hot spot: an interactable plus a splash effect.
struct cFishingHotSpot {
  u8              mPad_00[0x24];         // 0x00
  cInteractable*  mpInteractable_24;     // 0x24
  cSplashEffect*  mpSplashEffect_28;     // 0x28
  u8              mPad_2c[0x3c - 0x2c];  // 0x2c

  void SetupArea(Vec3* pos, float radius);    // 0x00c91030
};

// ---------------------------------------------------------------------------
// Imported helpers (declared, never defined in this TU).
// ---------------------------------------------------------------------------
struct cGameNounManager {
  void* CreateNoun(u32 id);              // 0x00b20c60
};

struct cTribeModeStrategy {
  virtual void* v00();  virtual void* v04();  virtual void* v08();  virtual void* v0c();
  virtual void* v10();  virtual void* v14();  virtual void* v18();  virtual void* v1c();
  virtual void* v20();  virtual void* v24();  virtual void* v28();  virtual void* v2c();
  virtual void* v30();  virtual void* v34();  virtual void* v38();  virtual void* v3c();
  virtual void* v40();  virtual void* v44();  virtual void* v48();  virtual void* v4c();
  virtual void* v50();  virtual void* v54();  virtual void* v58();  virtual void* v5c();
  virtual void* v60();  virtual void* v64();  virtual void* v68();
  virtual void* v6c(void* splash, Vec3 v, s32 a, s32 b);   // 0x6c
  u8   TerrainHasKey(u32 key);           // 0x00cd4460
  void SignalTribeEvent(u32 key);        // 0x00cd6980
};

struct cGameData {
  void* GetPlayerTribe();                // 0x00bfc5f0
};

extern "C" {
void*  __cdecl GetCurrentGameMode();              // 0x00b5b800
void*  __cdecl NounManager();                     // 0x00b3d300
void*  __cdecl PlanetModel();                     // 0x00b3d350
void*  __cdecl ModeStrategyInstance();            // 0x00cd40b0
s32    __cdecl GetTutorialToolPrice(u32 tbl, u32 key, s32 idx);  // 0x004e1c30
void*  __cdecl FUN_00c6f770(void* self, u32 key, s32 a, s32 b);  // 0x00c6f770
void*  __cdecl FUN_00ac8fa0(u32 tbl, u32 key, s32 idx);          // 0x00ac8fa0
void*  __cdecl FUN_00cc9740(void* self);                         // 0x00cc9740
void*  __cdecl Matrix3FromQuaternion(void* out, const Quat* q);  // 0x0059c190
void*  __cdecl FUN_0059aed0(void* out, const void* m, const Quat* q); // 0x0059aed0
Vec3*  __cdecl DirectionToSurfacePosition(cPlanetModel* model, Vec3* out,
                                          Vec3* dir);            // 0x00b815a0
u8     __cdecl GetPropertyAsVector3(void* obj, u32 key, Vec3* out); // 0x00b81d50
}

// ---------------------------------------------------------------------------
// @ 0x00c90b40
// Pick the nearest of three points: returns whichever of a/b/c is closest to
// (x, y, z), with retail's exact comparison order.
// ---------------------------------------------------------------------------
float* __cdecl NearestOfThree(float* a, float* b, float* c,
                              float x, float y, float z)
{
  float daY = y - a[1];
  float dbY = y - b[1];
  float dcY = y - c[1];
  float dbX = x - b[0];
  float dbZ = z - b[2];
  float daX = x - a[0];
  float dcX = x - c[0];
  float daZ = z - a[2];
  float dcZ = z - c[2];

  if ((dbX * dbX + dbZ * dbZ) + dbY * dbY <=
      (daX * daX + daY * daY) + daZ * daZ) {
    if ((daX * daX + daZ * daZ) + daY * daY <
        (dcZ * dcZ + dcY * dcY) + dcX * dcX)
      return a;
    if ((dcZ * dcZ + dcY * dcY) + dcX * dcX <=
        (dbZ * dbZ + dbY * dbY) + dbX * dbX)
      return b;
  } else {
    if ((dbX * dbX + dbZ * dbZ) + dbY * dbY <
        (dcX * dcX + dcZ * dcZ) + dcY * dcY)
      return b;
    if ((dcX * dcX + dcZ * dcZ) + dcY * dcY <=
        (daX * daX + daZ * daZ) + daY * daY)
      return a;
  }
  return c;
}

// ---------------------------------------------------------------------------
// @ 0x00c90da0
// eastl::uninitialized_copy over 0x14-byte elements; *out tracks the cursor.
// ---------------------------------------------------------------------------
void __cdecl CopyElems14(Elem14** out, const Elem14* first, const Elem14* last,
                         Elem14* dst)
{
  *out = dst;
  if (first != last) {
    do {
      if (dst != 0) {
        dst->mX = first->mX;
        dst->mY = first->mY;
        dst->mZ = first->mZ;
        dst->mW = first->mW;
        dst->mB_10 = first->mB_10;
      }
      first++;
      dst++;
    } while (first != last);
    *out = dst;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c90df0
// eastl::uninitialized_fill_n over 0x14-byte elements.
// ---------------------------------------------------------------------------
void __cdecl FillElems14(Elem14* dst, u32 count, const Elem14* value)
{
  if (count != 0) {
    do {
      if (dst != 0) {
        dst->mX = value->mX;
        dst->mY = value->mY;
        dst->mZ = value->mZ;
        dst->mW = value->mW;
        dst->mB_10 = value->mB_10;
      }
      count--;
      dst++;
    } while (count != 0);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c90e40
// eastl::copy over 0x14-byte elements (no cursor out-parameter).
// ---------------------------------------------------------------------------
void __cdecl CopyElems14Range(Elem14* first, const Elem14* last, Elem14* dst)
{
  for (; first != last; first++) {
    if (dst != 0) {
      dst->mX = first->mX;
      dst->mY = first->mY;
      dst->mZ = first->mZ;
      dst->mW = first->mW;
      dst->mB_10 = first->mB_10;
    }
    dst++;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c90e80
// Segmented assign: walks a paged range, replacing each destination ref-counted
// pointer (AddRef on the new value, Release on the old) and writes the final
// destination cursor to *out.
// ---------------------------------------------------------------------------
struct SegIter {
  RefCnt**  mpCur;                       // 0x00
  RefCnt**  mpBegin;                     // 0x04
  RefCnt**  mpEnd;                       // 0x08
  RefCnt*** mppPage;                     // 0x0c (slot holding the next page)
};

void __cdecl AssignRefRange(SegIter* out, SegIter src, SegIter dst,
                            RefCnt*** dstPageSlot)
{
  while (src.mpCur != dst.mpEnd) {
    RefCnt* value = *src.mpCur;
    RefCnt* old   = *dst.mpCur;
    if (value != old) {
      if (value != 0)
        value->AddRef();
      *dst.mpCur = value;
      if (old != 0)
        old->Release();
    }
    dst.mpCur++;
    if (dst.mpCur == dst.mpEnd) {
      dst.mpBegin = (RefCnt**)*dstPageSlot;
      dst.mpEnd   = dst.mpBegin + 0x40;
      dst.mpCur   = dst.mpBegin;
      dstPageSlot++;
    }
    src.mpCur++;
    if (src.mpCur == src.mpEnd) {
      src.mppPage++;
      src.mpBegin = (RefCnt**)*src.mppPage;
      src.mpEnd   = src.mpBegin + 0x40;
      src.mpCur   = src.mpBegin;
    }
  }
  out->mpCur   = dst.mpCur;
  out->mpBegin = dst.mpBegin;
  out->mpEnd   = dst.mpEnd;
  out->mppPage = dst.mppPage;
}

// ---------------------------------------------------------------------------
// @ 0x00c90f50
// eastl::promote_heap<Vec3*, int, Vec3, ComparePositions>: sift the new
// position (x,y,z) up from `hole` while its distance to (px,py,pz) is smaller
// than the parent's.
// ---------------------------------------------------------------------------
void __cdecl PromoteHeap(Vec3* heap, s32 size, s32 hole,
                         float x, float y, float z,
                         float px, float py, float pz)
{
  while (size < hole) {
    s32 parent = (hole - 1) >> 1;
    Vec3* p = &heap[parent];
    if (((pz - z) * (pz - z) + (py - y) * (py - y)) + (px - x) * (px - x) <=
        ((px - p->x) * (px - p->x) + (pz - p->z) * (pz - p->z)) +
            (py - p->y) * (py - p->y))
      break;
    Vec3* dst = &heap[hole];
    dst->x = p->x;
    dst->y = p->y;
    dst->z = p->z;
    hole = parent;
  }
  Vec3* out = &heap[hole];
  out->x = x;
  out->y = y;
  out->z = z;
}

// ---------------------------------------------------------------------------
// @ 0x00c91030
// Place the fishing hot spot: create/attach the splash effect and the
// interactable, then register the area with the tribe mode strategy.
// ---------------------------------------------------------------------------
void cFishingHotSpot::SetupArea(Vec3* pos, float radius)
{
  if (GetCurrentGameMode() != (void*)0x1654c02)
    return;

  if (mpSplashEffect_28 == 0) {
    cSplashEffect* noun = (cSplashEffect*)((cGameNounManager*)NounManager())
                              ->CreateNoun(0x18c88e4);
    cSplashEffect* old = mpSplashEffect_28;
    if (noun != old) {
      if (noun != 0)
        noun->AddRef();
      mpSplashEffect_28 = noun;
      if (old != 0)
        old->Release();
    }
  }

  FUN_00c6f770(mpSplashEffect_28, 0x356eb8a, -1, 0);
  mpSplashEffect_28->mPlacement_70.SetPosition(pos);
  mpSplashEffect_28->mVisible_e1 = 1;

  if (mpInteractable_24 == 0) {
    cInteractable* noun = (cInteractable*)((cGameNounManager*)NounManager())
                              ->CreateNoun(0x2e72cae);
    cInteractable* itr = 0;
    if (noun != 0)
      itr = (cInteractable*)noun->QueryInterface(0x2e71a5a);
    cInteractable* old = mpInteractable_24;
    if (itr != old) {
      if (itr != 0)
        itr->AddRef();
      mpInteractable_24 = itr;
      if (old != 0)
        old->Release();
    }
  }

  mpInteractable_24->SetAreaData(pos, radius);
  mpInteractable_24->SetParams(0.0f, *(float*)0x14763b8);
  mpInteractable_24->AttachEffect(mpSplashEffect_28);

  cTribeModeStrategy* strat = (cTribeModeStrategy*)ModeStrategyInstance();
  void* target = strat->v6c(0, Vec3(), 0, 0);
  if (target == 0)
    return;
  cTribeModeStrategy* strat2 = (cTribeModeStrategy*)ModeStrategyInstance();
  void* obj = strat2->v6c(mpSplashEffect_28, *pos, 0, 1);
  FUN_00cc9740(obj);
}

// ---------------------------------------------------------------------------
// @ 0x00c91190
// Read the anchor position for the given tool kind into *out.
// ---------------------------------------------------------------------------
float* cTribe::GetToolPosition(float* out, s32 kind)
{
  switch (kind) {
  case 0:
    if (GetToolOfType(10) != 0) {
      out[0] = mToolAnchor_504.x;
      out[1] = mToolAnchor_504.y;
      out[2] = mToolAnchor_504.z;
      return out;
    }
    break;
  case 2:
    {
      cTool* tool = GetToolOfType(9);
      if (tool != 0) {
        Vec3* p = tool->mAnchor_34.GetPosition();
        out[0] = p->x;
        out[1] = p->y;
        out[2] = p->z;
        return out;
      }
    }
    break;
  default:
    {
      Vec3* p = mSpatial_120.GetPosition();
      out[0] = p->x;
      out[1] = p->y;
      out[2] = p->z;
    }
    return out;
  }
  out[0] = mToolSlots_2dc[kind].x;
  out[1] = mToolSlots_2dc[kind].y;
  out[2] = mToolSlots_2dc[kind].z;
  return out;
}

// ---------------------------------------------------------------------------
// @ 0x00c91250
// Recompute the four tool ring positions (90 degree sweep), project them onto
// the planet surface and refresh the social-tool anchor from the tribe's
// "vector3" property.
// ---------------------------------------------------------------------------
void cTribe::UpdateToolPositions()
{
  cPlanetModel* planet = (cPlanetModel*)PlanetModel();

  Vec3 center = *GetPosition();
  Vec3 up;
  v5c(&up);

  float sum = (center.z * center.z + (center.x * center.x + center.y * center.y))
              + 1e-08f;
  float invLen = 1.0f / (float)sqrt((double)sum);
  Vec3 axis = { center.z * invLen, center.x * invLen, center.y * invLen };

  Vec3 ring[3];
  for (s32 i = 0; i < 3; i++) {
    float angle = (float)i * 90.0f;
    float s = (float)sin((double)angle);
    float c = (float)cos((double)angle);
    float ax = axis.x * s;
    float ay = axis.y * s;
    float az = axis.z * s;
    Vec3 dir;
    dir.x = (((c * ay + az * ax) * up.z + (ay * ax - c * az) * up.x) * 2.0f +
             (1.0f - (az * az + ay * ay) * 2.0f) * up.y) * 9.5f + center.x;
    dir.y = (((c * az + ay * ax) * up.y + (az * ay - c * ax) * up.z) * 2.0f +
             (1.0f - (az * az + ax * ax) * 2.0f) * up.x) * 9.5f + center.y;
    dir.z = (((az * ax - c * ay) * up.y + (c * ax + az * ay) * up.x) * 2.0f +
             (1.0f - (ax * ax + ay * ay) * 2.0f) * up.z) * 9.5f + center.z;
    Vec3 projected;
    DirectionToSurfacePosition(planet, &projected, &dir);
    ring[i] = projected;
  }

  Vec3 social;
  if (GetPropertyAsVector3(mToolSlots_2dc, 0x5777f17, &social) != 0) {
    Quat* q = GetRotation();
    float qx = q->x, qy = q->y, qz = q->z, qw = q->w;
    float sx = social.x, sy = social.y, sz = social.z;
    float tx = (qz * qx - qw * qy) * sx;
    float ty = (qw * qz + qy * qx) * sx;
    Vec3 r;
    r.x = ((qy * qx - qw * qz) * sy + (qw * qy + qz * qx) * sz) * 2.0f +
          (1.0f - (qz * qz + qy * qy) * 2.0f) * sx;
    float t2 = (qw * qx + qz * qy) * sy;
    r.y = ((qz * qy - qw * qx) * sz + ty) * 2.0f +
          (1.0f - (qz * qz + qx * qx) * 2.0f) * sy;
    r.z = (t2 + tx) * 2.0f +
          (1.0f - (qy * qy + qx * qx) * 2.0f) * sz;
    Vec3* pos = GetPosition();
    r.x += pos->x;
    r.y += pos->y;
    r.z += pos->z;
    Vec3 out;
    DirectionToSurfacePosition(planet, &out, &r);
    mToolSlots_2dc[1] = out;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c91700
// Build the area-effect transform once: identity rotation preset, the tribe
// position, then the rotation from the spatial quaternion.
// ---------------------------------------------------------------------------
void cTribe::RefreshAreaEffect()
{
  cPlanetModel* planet = (cPlanetModel*)PlanetModel();
  cPlanetBody* body = planet->mpBody_24;
  if (body == 0 || mAreaEffect_19d4 != 0)
    return;

  cTransform t;
  t.mFlags_00 = 0;
  t.mStamp_02 = 0;
  t.mPos_04.x = *(float*)0x1695374;
  t.mPos_04.y = *(float*)0x1695378;
  t.mPos_04.z = *(float*)0x169537c;
  t.mScale_10 = 1.0f;
  ((Matrix33Obj*)&t.mRot_14)->ctor((const void*)0x1695418);

  Vec3* pos = mSpatial_120.GetPosition();
  t.mPos_04 = *pos;
  t.mFlags_00 |= 4;
  t.mStamp_02++;

  Quat* rot = mSpatial_120.GetRotation();
  float* src = (float*)Matrix3FromQuaternion(&t.mRot_14, rot);
  for (s32 i = 0; i < 9; i++)
    t.mRot_14.m[i] = src[i];
  t.mFlags_00 |= 2;
  t.mStamp_02++;

  mAreaEffect_19d4 = body->AddTransform(&t, mEffectId_2d4);
}

// ---------------------------------------------------------------------------
// @ 0x00c91800
// Snap the tool placement to the area: local offset transformed by the area's
// axis pair and written through the anchor.
// ---------------------------------------------------------------------------
void cToolPlacement::SetPlacementArea(cPlacementArea* area)
{
  cTribe* tribe = Tribe();
  Vec3 right;
  FUN_0059aed0(&right, (const void*)0x169543c, tribe->GetRotation());

  Vec3 fwd;
  FUN_0059aed0(&fwd, (const void*)0x1695448, tribe->GetRotation());

  u32 flags = area->mFlags_12c;
  if (flags == 0)
    flags = 3;
  float c = *(float*)0x15812f0;
  float sx = (flags & 1) ? c : -c;
  float sz = (flags & 2) ? c : -c;

  Vec3 target;
  target.x = fwd.x * sz + (right.x * sx + mOffset_dc.x);
  target.y = fwd.y * sz + (right.y * sx + mOffset_dc.y);
  target.z = fwd.z * sz + (right.z * sx + mOffset_dc.z);

  area->mAnchor_34.SetPosition(&target);
  v30(area);
  area->mConnected_130 = 1;
  area->mB_a3 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00c91970
// Award the food tutorial once the player tribe can afford the tutorial tool.
// ---------------------------------------------------------------------------
void cTribe::CheckFoodTutorialComplete()
{
  cGameData* data = (cGameData*)NounManager();
  if (this != (cTribe*)data->GetPlayerTribe())
    return;

  s32 value = vA4();
  s32 price = GetTutorialToolPrice(*(u32*)0x1581288, 0xb79e0065, 0x28);
  if (value < price)
    return;

  if (((cTribeModeStrategy*)ModeStrategyInstance())->TerrainHasKey(0x14363974) == 0) {
    ((cTribeModeStrategy*)ModeStrategyInstance())->SignalTribeEvent(0x14363974);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00c919e0
// Upgrade the tribe hut: place the upgraded hut model at the current position.
// ---------------------------------------------------------------------------
void cTribe::UpgradeHut()
{
  if (mSpatial_120.IsValid() == 0)
    return;

  void* key = FUN_00ac8fa0(*(u32*)0x158128c, 0x93c8ee8, 5);
  Vec3* pos = mSpatial_120.GetPosition();
  FUN_00c8f3d0(0, (void*)1, *(float*)0x1486110, 0x2cc62c6, pos,
               (u32)(SIZE_T)key);
}
