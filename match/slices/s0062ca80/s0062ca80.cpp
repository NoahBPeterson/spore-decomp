// SP::cSPPlayMode / cSPPlayMode_Creature helpers. Region 0x62ca80-0x62da05.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);

extern void* gThemeMusicVt; // 0x14774b0
extern void* gVt13fe1bc;    // 0x13fe1bc
extern void* gVt13ec458;    // 0x13ec458

struct Vec12 { void* a; void* b; void* c; };

// @ 0x0062ca80
struct BlockPath { void BlockCircle(float x, float y, float z, int one); };
void __fastcall FUN_0062ca80(void* self) {
  char* s = (char*)self;
  char* mgr = *(char**)(s + 0x14);
  int n = (*(int*)(mgr + 0x80) - *(int*)(mgr + 0x7c)) >> 2;
  if (n == 1) return;
  for (int i = 0; i < n; ++i) {
    char* c = *(char**)(*(int*)(mgr + 0x7c) + i * 4);
    if (c == s) continue;
    char* e = *(char**)(*(char**)(c + 8) + 0x180);
    float x = *(float*)(c + 0x20) + *(float*)(s + 0x20);
    ((BlockPath*)*(void**)(s + 0x18))->BlockCircle(*(float*)(e + 0xc), *(float*)(e + 0x10), x, 1);
  }
}

// @ 0x0062cb20
extern "C" void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b, int c, int d);
struct ThemeMusic { int pad[16]; };
void* __stdcall FUN_0062cb20(void* src, float a, char b, float c) {
  char* o = (char*)EA_Allocate(0x2c, "Casual", 0, 0, 0, 0);
  if (o != 0) {
    *(void**)(o + 4) = 0;
    *(void**)o = (void*)&gThemeMusicVt;
  } else {
    o = 0;
  }
  int s0 = ((int*)src)[0];
  int s1 = ((int*)src)[1];
  int s2 = ((int*)src)[2];
  *(int*)(o + 8) = s0;
  *(int*)(o + 0xc) = s1;
  *(int*)(o + 0x10) = s2;
  *(float*)(o + 0x20) = a;
  *(unsigned char*)(o + 0x2a) = 0;
  *(unsigned char*)(o + 0x29) = 0;
  *(unsigned char*)(o + 0x2b) = 0;
  *(unsigned char*)(o + 0x28) = b;
  *(float*)(o + 0x24) = c;
  return o;
}

// @ 0x0062cb90
void __fastcall FUN_0062cb90(void* self) {
  char* s = (char*)self;
  int n = (*(int*)(s + 0x40) - *(int*)(s + 0x3c)) >> 2;
  if (n > 0) {
    do {
      *(int*)(s + 0x40) -= 4;
      int o = **(int**)(s + 0x40);
      if (o != 0) {
        char* vt = *(char**)o;
        ((TF0)(*(void**)(vt + 8)))((void*)o);
      }
      --n;
    } while (n != 0);
  }
}

// @ 0x0062cbc0
int __fastcall FUN_0062cbc0(void* self, float* p) {
  int obj = **(int**)((char*)self + 0x3c);
  if (fabsf(*(float*)(obj + 8) - p[0]) < 1.52587890625e-05f &&
      fabsf(*(float*)(obj + 0xc) - p[1]) < 1.52587890625e-05f)
    return 1;
  return 0;
}

// @ 0x0062cc20
void __fastcall FUN_0062cc20(void* self, float* p) { (void)self; (void)p; }

// @ 0x0062cd30
void* __fastcall FUN_0062cd30(void* self) {
  char* s = (char*)self;
  *(int*)(s + 4) = 0;
  *(void**)s = (void*)&gVt13fe1bc;
  *(int*)(s + 0x18) = 0;
  *(int*)(s + 0x38) = 0;
  Vec12* vec = (Vec12*)(s + 0x3c);
  vec->a = 0; vec->b = 0; vec->c = 0;
  *(int*)(s + 8) = 0;
  *(int*)(s + 0xc) = 0;
  *(int*)(s + 0x10) = 0;
  *(int*)(s + 0x1c) = -1;
  *(float*)(s + 0x20) = 0.0f;
  *(unsigned char*)(s + 0x24) = 0;
  *(float*)(s + 0x28) = 0.0f;
  *(float*)(s + 0x34) = 0.0f;
  return self;
}

// @ 0x0062cdb0
extern void __fastcall VecDtorFn(void*);
extern "C" void __cdecl EASTL_free(void*);
void* __fastcall FUN_0062cdb0(void* self, char flag) {
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe1bc;
  VecDtorFn(s + 0x3c);
  {
    void* p = *(void**)(s + 0x38);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  {
    void* p = *(void**)(s + 0x18);
    if (p != 0) { ((TF0)(*(void**)(*(char**)p + 8)))(p); }
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) {
    EASTL_free(s);
  }
  return self;
}

// @ 0x0062ce00
void __fastcall FUN_0062ce00(void* self, void*, char) { (void)self; }

// @ 0x0062cef0
void __fastcall FUN_0062cef0(void* self) { (void)self; }

// ---- 0x0062d0f0 (cSPPlayMode_Creature: walk / dodge-around-other-creature controller) ----

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

Vec3* __cdecl Normalize(Vec3* out, const Vec3* in);                       // 0x436ce0
Vec3* __cdecl RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);      // 0x59aed0
float __cdecl SignedDot(const Vec3* a, const Vec3* b, const Vec3* axis);  // 0x69b760

extern const Vec3 kUp;    // 0x15f70e8
extern const Vec3 kFwd;   // 0x15f7164
extern const float kZeroA; // 0x1485378
extern const float kZeroB; // 0x1522600

struct RefCountObj {
  virtual void slot0();
  virtual int AddRef();
  virtual int Release();
  int mnRefCount;
};

struct PathT : RefCountObj {
  Vec3 mTarget;
  Vec3 mTeleport;
  float mSpeed;
  float mReached;
  unsigned char mType, mCount, mPriority, mRoom;
  PathT() { mnRefCount = 0; }
};

template <class T> struct ARC {
  T* p;
  __forceinline ARC& operator=(T* q) {
    if (q != p) {
      T* old = p;
      if (q) q->AddRef();
      p = q;
      if (old) old->Release();
    }
    return *this;
  }
  __forceinline void Reset() {
    T* t = p;
    if (t) { p = 0; t->Release(); }
  }
};

struct PlayModeCreature;
struct AnimCreature { char pad[0x10]; Quat mRotation; };
struct AnimData {
  char pad0[0x38];
  Vec3 mActualPosition;
  char pad1[0x4c - 0x44];
  float mMovementSpeed;
  float mRotationSpeed;
  void SetTargetPosition(const Vec3* p, int a, int b);  // 0x59b0f0
};
struct PlayMode {
  char pad[0x7c];
  struct { ARC<PlayModeCreature>* mpBegin; ARC<PlayModeCreature>* mpEnd; } mCreatures;
  void StopWalk(AnimCreature* c, unsigned id);  // 0x62a1a0
};
struct CasualPath {
  void SetPositionOffset(float x, float y);                      // 0x62da00
  bool FindPath(float x, float y, float tx, float ty);           // 0x62e010
  void StartPath();                                              // 0x62dbf0
  bool GetNextPathPoint(Vec3* out);                              // 0x62de30
};
struct PathVec { ARC<PathT>* mpBegin; ARC<PathT>* mpEnd; ARC<PathT>* mpCap; };

struct PlayModeCreature : RefCountObj {
  AnimCreature* mAnimCreature;   // +8
  void* mEditorBaseMode;         // +0xc
  AnimData* mData;               // +0x10
  PlayMode* mPlayMode;           // +0x14
  CasualPath* mPath;             // +0x18
  unsigned mCreatureID;          // +0x1c
  float mCollisionRadius;        // +0x20
  bool mCollision;               // +0x24
  float mPathWaitTime;           // +0x28
  float mSaveSpeed;              // +0x2c
  float mSaveRot;                // +0x30
  float mWaitAfter;              // +0x34
  ARC<PathT> mPathInWaiting;     // +0x38
  PathVec mPathList;             // +0x3c

  PathT* NewPath(const Vec3* pos, float speed, char type, float reached);  // 0x62cb20
  void BlockOthers();                                                      // 0x62ca80
  void AddPathTarget(PathT* p, int replace);                               // 0x62ce00

  bool MoveTo(int unused, int unused2, bool go, bool follow);  // @ 0x0062d0f0
};

static inline bool Empty(const PathVec& v) { return ((((char*)v.mpEnd - (char*)v.mpBegin) >> 2) == 0); }

static __forceinline void ClearList(PathVec& v) {
  int n = ((char*)v.mpEnd - (char*)v.mpBegin) >> 2;
  if (n > 0) {
    do {
      v.mpEnd--;
      PathT* t = v.mpEnd->p;
      if (t) t->Release();
      --n;
    } while (n != 0);
  }
}

// @ 0x0062d0f0
bool PlayModeCreature::MoveTo(int, int, bool go, bool follow) {
  if (!go) {
    if (Empty(mPathList)) return false;
    float spd = mData->mMovementSpeed;
    float rot = mData->mRotationSpeed;
    if (spd != kZeroA) {
      mSaveSpeed = spd;
      mSaveRot = rot;
      mPlayMode->StopWalk(mAnimCreature, mCreatureID);
    }
    AnimData* d = mData;
    d->mMovementSpeed = 0.0f;
    d->mRotationSpeed = rot;
    return true;
  }
  PlayModeCreature* other = mPlayMode->mCreatures.mpBegin[0].p;
  if (follow && !Empty(other->mPathList)) {
    if (!Empty(mPathList) && mPathList.mpBegin[0].p->mType == 1) return true;
    Vec3 v30, v24, v18, v3c, tmp;
    AnimData* od = other->mData;
    v18 = od->mActualPosition;
    v24 = other->mPathList.mpBegin[0].p->mTarget;
    v30.x = v24.x - v18.x;
    v30.y = v24.y - v18.y;
    v30.z = 0.0f;
    v30 = *Normalize(&v24, &v30);
    v24.x = v30.y * kUp.z - kUp.y * v30.z;
    v24.y = kUp.x * v30.z - v30.x * kUp.z;
    v24.z = v30.x * kUp.y - v30.y * kUp.x;
    v24 = *Normalize(&v30, &v24);
    v3c = mData->mActualPosition;
    v18.x = v3c.x - v18.x;
    v18.y = v3c.y - v18.y;
    v18.z = 0.0f;
    v18 = *Normalize(&v30, &v18);
    v30 = kFwd;
    v30 = *RotateByQuat(&tmp, &v30, &other->mAnimCreature->mRotation);
    v30 = *Normalize(&tmp, &v30);
    float dot = SignedDot(&v30, &v18, &kUp);
    float rad = other->mCollisionRadius + mCollisionRadius;
    float ox = v24.x * rad, oy = v24.y * rad, oz = v24.z * rad;
    float nx, ny, nz;
    if (kZeroB <= dot) {
      ny = v3c.y - oy; nx = v3c.x - ox; nz = v3c.z - oz;
    } else {
      ny = v3c.y + oy; nx = v3c.x + ox; nz = v3c.z + oz;
    }
    if (5.0f < sqrtf(ny * ny + (nz * nz + nx * nx))) {
      if (kZeroB <= dot) {
        ny = oy * 2.0f + v3c.y; nx = ox * 2.0f + v3c.x; nz = oz * 2.0f + v3c.z;
      } else {
        ny = v3c.y - oy * 2.0f; nx = v3c.x - ox * 2.0f; nz = v3c.z - oz * 2.0f;
      }
    }
    v3c.x = nx; v3c.y = ny; v3c.z = nz;
    PathT* np = NewPath(&v3c, 2.0f, 0, 0.2f);
    if (np) {
      np->mType = 1;
      np->mPriority = 1;
      AddPathTarget(np, 1);
      return true;
    }
    return true;
  }

  {
  Vec3 cur = mData->mActualPosition;
  if (Empty(mPathList)) {
    mData->SetTargetPosition(&cur, 0, 1);
    return mPathInWaiting.p != 0;
  }
  unsigned i = 0;
  if (((char*)mPathList.mpEnd - (char*)mPathList.mpBegin) >> 2 != 1) {
    ARC<PathT>* pp = mPathList.mpBegin;
    do {
      if (pp->p->mPriority == 1) break;
      ++i;
      ++pp;
    } while (i < (unsigned)((((char*)mPathList.mpEnd - (char*)mPathList.mpBegin) >> 2) - 1));
  }
  PathT* sp = mPathList.mpBegin[i].p;
  unsigned char type = sp->mType;
  unsigned char prio = sp->mPriority;
  float speed = sp->mSpeed;
  mPath->SetPositionOffset(cur.x, cur.y);
  BlockOthers();
  sp = mPathList.mpBegin[i].p;
  if (mPath->FindPath(cur.x, cur.y, sp->mTarget.x, sp->mTarget.y)) {
    ClearList(mPathList);
    mPath->StartPath();
    float z = 0.0f;
    bool done;
    do {
      Vec3 pt;
      done = mPath->GetNextPathPoint(&pt);
      float px = pt.x, py = pt.y;
      if (px != cur.x || py != cur.y || cur.z != 0.0f) {
        PathT* o = new ("Casual", 0, 0, 0, 0) PathT();
        o->mTarget.x = px;
        o->mSpeed = speed;
        o->mTarget.y = py;
        o->mTarget.z = z;
        o->mType = 0;
        o->mReached = 0.2f;
        o->mPriority = 0;
        o->mCount = 0;
        o->mRoom = 0;
        if (done) {
          o->mType = type;
          o->mPriority = prio;
        }
        AddPathTarget(o, 0);
      }
    } while (!done);
    return true;
  }
  mData->SetTargetPosition(&cur, 0, 1);
  mPlayMode->StopWalk(mAnimCreature, mCreatureID);
  if (mPathList.mpBegin[i].p->mPriority == 1) {
    if (mPathInWaiting.p != 0) mPathInWaiting.Reset();
    PathT* np = NewPath(&mPathList.mpBegin[i].p->mTarget, 1.5f, 0, 0.2f);
    mPathInWaiting = np;
    mPathInWaiting.p->mSpeed = mPathList.mpBegin[i].p->mSpeed;
    mPathInWaiting.p->mType = mPathList.mpBegin[i].p->mType;
    mPathInWaiting.p->mPriority = mPathList.mpBegin[i].p->mPriority;
    mPathInWaiting.p->mReached = mPathList.mpBegin[i].p->mReached;
    mPathInWaiting.p->mRoom = mPathList.mpBegin[i].p->mRoom;
    PathT* s2 = mPathList.mpBegin[i].p;
    PathT* d2 = mPathInWaiting.p;
    d2->mTeleport.x = s2->mTeleport.x;
    d2->mTeleport.y = s2->mTeleport.y;
    d2->mTeleport.z = s2->mTeleport.z;
    mPathInWaiting.p->mCount = mPathList.mpBegin[i].p->mCount;
    mPathWaitTime = 0.5f;
  } else {
    mPathInWaiting.Reset();
  }
  ClearList(mPathList);
  return true;
  }
}

// @ 0x0062d8a0
void __fastcall FUN_0062d8a0(void* self, float, float) { (void)self; }
