// Slice s005bdca0 -- SP::cSPEditorManipulation* (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

// ---------------------------------------------------------------------------
// Global float constants referenced by this region.
extern "C" const float F_013f7944;        // 0x013f7944  FLT_MAX
extern "C" const float F_013f51ac;        // 0x013f51ac  -FLT_MAX
extern "C" const float G_015eabf4[9];     // 0x015eabf4  orientation basis table
extern "C" void* memcpy(void*, const void*, unsigned int);  // 0x011e0744

// ---------------------------------------------------------------------------
// Callees (original VAs resolved from the annotation).

void FUN_00454280(void* a, void* b);                 // 0x00454280
int  FUN_00435d40();                                 // 0x00435d40  Entity::HasAnyBlockFlag
int  FUN_004a6270(void* block);                      // 0x004a6270  SP::EditorUtils::IsLimbPart
void FUN_00454ee0(void* end, void* value);           // 0x00454ee0
int  FUN_004accf0();                                 // 0x004accf0  cSPEditorModel::GetBlockCount
void* FUN_004accb0(uint i);                          // 0x004accb0  cSPEditorModel::GetBlock
char FUN_004adaa0();                                 // 0x004adaa0
float FUN_004adb00();                                // 0x004adb00
float FUN_004adb40();                                // 0x004adb40
void FUN_00448e90(void* p, int n);                   // 0x00448e90  cSPEditorBlock::SetPosition
char FUN_004adc40();                                 // 0x004adc40  cSPEditorModel::UsingSymmetry
void FUN_004adc20(uint x);                           // 0x004adc20
void* FUN_007f99a0();                                // 0x007f99a0
void FUN_004890e0(int x);                            // 0x004890e0
void FUN_00489ae0();                                 // 0x00489ae0
void FUN_004a6d20(int* vertebrae, int a, int b, int c,
                  int d, int e, int f, int g);       // 0x004a6d20
void FUN_00409dd0(void* box, const void* xform);     // 0x00409dd0  BoundingBox_TransformBy
void FUN_005ce680(void* spine, float a, uchar* p,
                  float* out);                       // 0x005ce680  CalcVertebraPhysicsBoundingBox
void FUN_0049fbd0(void* block, const float* vec,
                  const float* mat, int flag);       // 0x0049fbd0  RepinBlockToTorso
void FUN_005bdd90(void* key, void* parent, void* val, uint flag);  // 0x005bdd90
void FUN_00f47380(void* p);                          // 0x00f47380  operator delete
void* FUN_005b0f80(void* self);                      // 0x005b0f80  base ctor
void FUN_00488900(void* p);                          // 0x00488900  ~cSPEditorLimbStructure
void FUN_00488980(void* p);                          // 0x00488980
void* FUN_0044ae00(void* blk, int a, int b);         // 0x0044ae00  cSPEditorBlock::GetBBox
void* FUN_005bd7c0(void* self, void* out, float a,
                   float b, float c);                // 0x005bd7c0  PickPlaneOfSymmetry

// ---------------------------------------------------------------------------
// cSPEditorBlock: refcounted editor block.  Slots 1 and 2 are AddRef/Release.
struct cSPEditorBlock {
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
};

// cSPEditorLimbStructure: refcounted limb.  Slots reached directly by the
// clear loop (005bde60).
struct cSPEditorLimbStructure {
  void Release();                 // 0x00488980
  void Destroy();                 // 0x00488900
};

// ---------------------------------------------------------------------------
// cSPEditorManipulationTranslateCreature.
//
// Field map (used by the functions in this slice):
//   +0x04  std::map sentinel header (node with left/right/key)
//   +0x0c  map root
//   +0x20  mSpine.mpObject
//   +0x24  mLimbs.begin    (+0x28 end, +0x2c cap)
//   +0x30  mModel.mpObject
//   +0x38  mOriginalPositions.begin
//   +0x48  mOriginalPlanarPosition.x (+0x4c .y, +0x50 .z)
//   +0x54  mCurrModelBounds.mMin (+0x60 .mMax)
//   +0x60  mCurrModelBounds.mMax
//   +0x84  vertex basis copy target
//   +0xa8  limb phyiscs basis copy source

struct cSPEditorManipulationTranslateCreature {
  char  pad04[0x04];
  int   mMapHead[4];              // +0x04
  char  pad14[0x0c];
  void* mSpine;                   // +0x20
  void* mLimbsBegin;              // +0x24
  void* mLimbsEnd;                // +0x28
  void* mLimbsCap;                // +0x2c
  void* mModel;                   // +0x30
  void* mOrigPosBegin;            // +0x38 (heading used by 005be500)
  float mOrigPlanar_x;            // +0x48
  float mOrigPlanar_y;            // +0x4c
  float mOrigPlanar_z;            // +0x50
  float mCurrBounds[6];           // +0x54  min.xyz max.xyz
  char  pad6c[0x18];
  int   mChangedObject;           // +0xa4 (byte)
  void  fn5de60();                // 0x005bde60
  float* fn5ded0(float* key);     // 0x005bded0
  void  CalcBoundsForMovement(float* offset, float* boxA,
                              float* boxB, void* vec);      // 0x005bdf70
  uint  fn5e500(float a, float b);                          // 0x005be500
};

// ---------------------------------------------------------------------------
// cSPEditorManipulationObject constructor target (202 bytes).
// Derived object: vtable at +0x00, second vtable at +0x14 (IUnknown32 mixin).

struct CSpEditorManip {
  void* vt00;             // +0x00
  char  f04;              // +0x04
  char  pad05[0x0f];
  void* vt14;             // +0x14
  int   f18;              // +0x18
  int   f1c;              // +0x1c
  int   f20;              // +0x20
  int   f24;              // +0x24
  int   f28;              // +0x28
  int   f2c;              // +0x2c
  char  pad30[8];
  char  f38;              // +0x38
  float f3c, f40, f44;    // +0x3c
  char  pad48[4];
  int   f4c;              // +0x4c
  int   f50;              // +0x50
  int   f54;              // +0x54
  int   f58;              // +0x58
  int   f5c;              // +0x5c
  float f64, f68, f6c;    // +0x64
  float f70, f74, f78;    // +0x70
  CSpEditorManip* init();
};

// @ 0x005bdca0
CSpEditorManip* CSpEditorManip::init() {
  FUN_005b0f80(this);                       // SP::cSPEditorManipulationObject::ctor
  vt14 = (void*)0x013ec458;                 // vtbl_cContentValidationSummarizer
  f18 = 0;
  vt00 = (void*)0x013f796c;
  vt14 = (void*)0x013f795c;
  f1c = 0; f20 = 0; f24 = 0; f28 = 0; f2c = 0;
  f38 = 0;
  f3c = 0.0f; f40 = 0.0f; f44 = 0.0f;
  float c0 = F_013f7944;
  f50 = 0; f54 = 0; f58 = 0;
  int head = (int)this + 0x4c;
  f50 = head;
  f4c = head;
  f54 = 0;
  *(char*)&f58 = 0;
  f5c = 0;
  f64 = c0; f68 = c0; f6c = c0;
  float c1 = F_013f51ac;
  f70 = c1; f74 = c1; f78 = c1;
  f04 = 0;
  return this;
}

// @ 0x005bde60  eastl::vector<SP::cSPEditorLimbStructure*>::clear
void cSPEditorManipulationTranslateCreature::fn5de60() {
  int n = (int)((char*)mLimbsEnd - (char*)mLimbsBegin) >> 2;
  for (int i = 0; i < n; ++i) {
    void* p = ((void**)mLimbsBegin)[i];
    ((cSPEditorLimbStructure*)p)->Release();
    p = ((void**)mLimbsBegin)[i];
    if (p != 0) {
      ((cSPEditorLimbStructure*)p)->Destroy();
      FUN_00f47380(p);
    }
  }
  void* s = mLimbsEnd;
  void* d = mLimbsBegin;
  memcpy(d, s, 0);
  mLimbsEnd = (void*)((char*)mLimbsEnd + (((char*)s - (char*)d) >> 2) * -4);
}

// @ 0x005bded0  std::map<float, cSPVector3> find-or-insert, returns &value
float* cSPEditorManipulationTranslateCreature::fn5ded0(float* key) {
  char* header = (char*)this + 0x04;
  char* parent = header;
  char* node = *(char**)((char*)this + 0x0c);
  while (node != 0) {
    if (*(float*)(node + 0x10) < *key) {
      node = *(char**)(node + 0x00);
    } else {
      parent = node;
      node = *(char**)(node + 0x04);
    }
  }
  if (parent != header && *key >= *(float*)(parent + 0x10))
    return (float*)(parent + 0x14);
  float k = *key;
  void* out = 0;
  FUN_005bdd90(key, parent, &k, 0);
  return (float*)((char*)out + 0x14);
}

// ---------------------------------------------------------------------------
// Bounding-box helpers.

struct cSPVector3 { float x, y, z; };
struct cSPBoundingBox { cSPVector3 mMin; cSPVector3 mMax; };

// @ 0x005bdf70  SP::cSPEditorManipulationTranslateCreature::CalcBoundsForMovement
void cSPEditorManipulationTranslateCreature::CalcBoundsForMovement(
    float* offset, float* boxA, float* boxB, void* vec) {
  for (int i = 0; i < 3; ++i) {
    boxA[i] = F_013f7944;
    boxA[3 + i] = F_013f51ac;
    boxB[i] = F_013f7944;
    boxB[3 + i] = F_013f51ac;
  }
  if (vec != 0 && *(void**)vec != 0)
    FUN_00454280(*(void**)vec, ((void**)vec)[1]);

  int count = FUN_004accf0();
  for (int i = 0; i < count; ++i) {
    cSPEditorBlock* blk = (cSPEditorBlock*)FUN_004accb0((uint)i);
    if (blk != 0) blk->AddRef();
    if (FUN_00435d40() == 0 || FUN_004a6270(blk) != 0) {
      if (blk != 0) blk->Release();
      continue;
    }

    cSPEditorBlock* key = blk;
    float* v = fn5ded0((float*)&key);
    float pos[3];
    pos[0] = v[0] + offset[0];
    pos[1] = v[1] + offset[1];
    pos[2] = v[2] + offset[2];

    float xform[12];
    xform[0] = G_015eabf4[0];
    xform[1] = G_015eabf4[1];
    xform[2] = G_015eabf4[2];
    xform[3] = G_015eabf4[3];
    xform[4] = G_015eabf4[4];
    xform[5] = G_015eabf4[5];
    xform[6] = G_015eabf4[6];
    xform[7] = G_015eabf4[7];
    xform[8] = G_015eabf4[8];
    xform[9] = pos[0];
    xform[10] = pos[1];
    xform[11] = pos[2];

    cSPBoundingBox box;
    box.mMin.x = F_013f7944; box.mMin.y = F_013f7944; box.mMin.z = F_013f7944;
    box.mMax.x = F_013f51ac; box.mMax.y = F_013f51ac; box.mMax.z = F_013f51ac;

    if (((*(uint*)((char*)blk + 0x60) >> 7) & 1) == 0) {
      float* bb = (float*)FUN_0044ae00(blk, 0, 0);
      box.mMax.x = bb[3]; box.mMax.y = bb[4]; box.mMax.z = bb[5];
      box.mMin.x = bb[0]; box.mMin.y = bb[1]; box.mMin.z = bb[2];
      FUN_00409dd0(&box, xform);
    } else {
      FUN_005ce680(mSpine, *(float*)((char*)blk + 0x3c), (uchar*)xform,
                   &box.mMin.x);
    }

    if (boxA[0] <= boxA[3]) {
      if (box.mMin.x < boxA[0]) boxA[0] = box.mMin.x;
      if (boxA[3] < box.mMax.x) boxA[3] = box.mMax.x;
      if (box.mMin.y < boxA[1]) boxA[1] = box.mMin.y;
      if (boxA[4] <= box.mMax.y && box.mMax.y != boxA[4]) boxA[4] = box.mMax.y;
      if (box.mMin.z < boxA[2]) boxA[2] = box.mMin.z;
      if (boxA[5] <= box.mMax.z && box.mMax.z != boxA[5]) boxA[5] = box.mMax.z;
    } else {
      boxA[0] = box.mMin.x; boxA[1] = box.mMin.y;
      boxA[3] = box.mMax.x; boxA[4] = box.mMax.y;
      boxA[2] = box.mMin.z; boxA[5] = box.mMax.z;
    }

    if (((*(uint*)((char*)blk + 0x60) >> 7) & 1) != 0) {
      if (boxB[0] <= boxB[3]) {
        if (box.mMin.x < boxB[0]) boxB[0] = box.mMin.x;
        if (boxB[3] < box.mMax.x) boxB[3] = box.mMax.x;
        if (box.mMin.y < boxB[1]) boxB[1] = box.mMin.y;
        if (boxB[4] <= box.mMax.y && box.mMax.y != boxB[4]) boxB[4] = box.mMax.y;
        if (box.mMin.z < boxB[2]) boxB[2] = box.mMin.z;
        if (boxB[5] <= box.mMax.z && box.mMax.z != boxB[5]) boxB[5] = box.mMax.z;
      } else {
        boxB[0] = box.mMin.x; boxB[1] = box.mMin.y;
        boxB[3] = box.mMax.x; boxB[4] = box.mMax.y;
        boxB[2] = box.mMin.z; boxB[5] = box.mMax.z;
      }
    }

    if (vec != 0) {
      void** end = (void**)((char*)vec + 4);
      void** cap = (void**)((char*)vec + 8);
      if (*end < *cap) {
        void* slot = *end;
        *end = (char*)slot + 4;
        if (slot != 0) {
          *(void**)slot = blk;
          blk->AddRef();
        }
      } else {
        FUN_00454ee0(*end, &blk);
      }
    }

    if (blk != 0) blk->Release();
  }
}

// @ 0x005be500  SP::cSPEditorManipulationTranslateCreature::ApplyPlanarSymmetry
uint cSPEditorManipulationTranslateCreature::fn5e500(float param_2, float param_3) {
  if (mModel == 0 || mSpine == 0) return 0;

  float planar[3];
  FUN_005bd7c0(this, planar, param_2, param_3, 0.0f);

  float offX = planar[0] - mOrigPlanar_x;
  float offY = planar[1] - mOrigPlanar_y;
  float offZ = planar[2] - mOrigPlanar_z;

  float boxA[6], boxB[6];
  void* list[4];
  list[0] = 0; list[1] = 0; list[2] = 0; list[3] = 0;

  float cur[3];
  cur[0] = offX; cur[1] = offY; cur[2] = offZ;
  CalcBoundsForMovement(cur, boxA, boxB, list);

  cur[1] = 0.0f; cur[2] = 0.0f;

  char sym = FUN_004adaa0();
  float wide = (float)FUN_004adb00() * 0.5f;
  float tall = (float)FUN_004adb40();

  float dMinY, dMaxX;
  if (-wide <= boxA[3]) {
    dMinY = cur[1];
    if (wide < boxA[4]) dMinY = -(boxA[4] - wide);
  } else {
    dMinY = -(boxA[3] + wide);
  }
  if (boxA[5] <= tall) {
    dMaxX = cur[2];
    if (boxA[2] < tall) {
      float t = tall;
      if (t > boxA[2]) t = boxA[2];
      dMaxX = t - boxA[2];
    }
  } else {
    dMaxX = -(boxA[5] - tall);
  }

  mCurrBounds[1] = boxA[4];
  mCurrBounds[2] = boxA[5];
  float f18v = mCurrBounds[1];
  mCurrBounds[2] = mCurrBounds[2] + dMinY;
  mCurrBounds[1] = f18v;
  mCurrBounds[0] = boxA[0] + dMaxX;
  float f23v = mCurrBounds[1];
  mCurrBounds[2] = mCurrBounds[2] + dMinY;
  mCurrBounds[1] = f23v;
  (void)sym;

  int n = (int)((char*)list[1] - (char*)list[0]) >> 2;
  float base = offX;
  for (int i = 0; i < n; ++i) {
    float key = ((float*)list[0])[i];
    float* v = fn5ded0(&key);
    float p[3];
    p[0] = v[0] + base;
    p[1] = v[1] + (dMinY + offY);
    p[2] = v[2] + offZ;
    FUN_00448e90(p, 1);
  }

  uchar old = FUN_004adc40();
  FUN_004adc20(0);

  int limbs = (int)((char*)mLimbsEnd - (char*)mLimbsBegin) >> 2;
  for (int i = 0; i < limbs; ++i) {
    void* limb = FUN_007f99a0();
    if (limb != 0) {
      float mat[9];
      float pos[3];
      mat[0] = *(float*)((char*)limb + 0xd8);
      mat[1] = *(float*)((char*)limb + 0xdc);
      mat[2] = *(float*)((char*)limb + 0xe0);
      mat[3] = *(float*)((char*)limb + 0xe4);
      mat[4] = *(float*)((char*)limb + 0xe8);
      mat[5] = *(float*)((char*)limb + 0xec);
      mat[6] = *(float*)((char*)limb + 0xf0);
      mat[7] = *(float*)((char*)limb + 0xf4);
      mat[8] = *(float*)((char*)limb + 0xf8);
      pos[0] = *(float*)((char*)limb + 0xac);
      pos[1] = *(float*)((char*)limb + 0xb0);
      pos[2] = *(float*)((char*)limb + 0xb4);
      float* v = fn5ded0(pos);
      FUN_0049fbd0(limb, v, mat, 0);
    }
    FUN_004890e0(1);
    FUN_00489ae0();
  }

  FUN_004adc20(old);

  int blocks = FUN_004accf0();
  for (int i = 0; i < blocks; ++i) {
    char* blk = (char*)FUN_004accb0((uint)i);
    *(uint*)(blk + 0x54) = *(uint*)(blk + 0x48);
    *(uint*)(blk + 0x58) = *(uint*)(blk + 0x4c);
    *(uint*)(blk + 0x5c) = *(uint*)(blk + 0x50);
    for (int j = 0; j < 9; ++j) {
      *(uint*)(blk + 0x84 + j * 4) = *(uint*)(blk + 0x60 + j * 4);
      *(uint*)(blk + 0xcc + j * 4) = *(uint*)(blk + 0xa8 + j * 4);
    }
  }

  if (mChangedObject == 0) mChangedObject = 1;

  int* vertebra = (int*)((char*)mSpine + 0x00);
  FUN_004a6d20(vertebra, 0, 0, 0, 0, 0, 1, 1);

  void** p3 = (void**)list[0];
  void** p4 = (void**)list[1];
  for (void** it = p3; it < p4; ++it) {
    if (*it != 0) {
      void** vtbl = *(void***)it;
      ((void (*)(void))vtbl[2])();
    }
  }
  if (p3 != 0 && p3[-1] != 0) FUN_00f47380(p3);

  return 1;
}