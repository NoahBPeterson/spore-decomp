// src/game/SPEditors/SPPlayMode_Creature.cpp -- migrated from slice(s) s0062da00, s0062ca80 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayMode_Creature.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayMode_Creature.h"
#include "SP/cSPEditorAnimatedCreatureData.h"
#include "SP/cSPPlayMode.h"
#include "cSPVector3.h"

// unnamed retail callees and globals (address in the comment)
extern const float kZeroA; // 0x1485378
extern const float kZeroB; // 0x1522600
#include <math.h>
#include <new>

// ---- items of slice s0062ca80 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct AnimCreature { char pad0[4]; Vec3 mPosition; Quat mRotation; };
struct AnimData {
  char pad0[0x2c];                 // +0x00
  Vec3 mTargetPosition;            // +0x2c
  Vec3 mActualPosition;            // +0x38
  char pad1[0x4c - 0x44];          // +0x44
  float mMovementSpeed;            // +0x4c
  float mRotationSpeed;            // +0x50
  void SetTargetPosition(const Vec3* p, int a, int b);  // 0x59b0f0
  void SetTargetAngle(float angle, int b);              // 0x59b2f0
};
struct PlayMode {
  char pad[0x7c];
  struct { ARC<PlayModeCreature>* mpBegin; ARC<PlayModeCreature>* mpEnd; } mCreatures;
  void StopWalk(AnimCreature* c, unsigned id);  // 0x62a1a0
  void FUN_00628960(AnimCreature* c, unsigned id);  // 0x00628960
};
struct CasualPath {
  void SetPositionOffset(float x, float y);                      // 0x62da00
  bool FindPath(float x, float y, float tx, float ty);           // 0x62e010
  void StartPath();                                              // 0x62dbf0
  bool GetNextPathPoint(Vec3* out);                              // 0x62de30
};
struct PathVec {
  ARC<PathT>* mpBegin;
  ARC<PathT>* mpEnd;
  ARC<PathT>* mpCap;
  void EraseFirst(ARC<PathT>* it);                              // 0x6b5990
  void PushBack(ARC<PathT>* end, ARC<PathT>* value);            // 0x5c8480
};
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
  bool AtFirstTarget(const Vec3* p);                                      // 0x62cbc0
  void BlockOthers();                                                      // 0x62ca80
  void AddPathTarget(PathT* p, bool replace);                              // 0x62ce00

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
enum { kPathIdA = 0x452b634, kPathIdB = 0x452b64a };
// ---- items of slice s0062ca80 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vec3 kUp;    // 0x15f70e8
extern const Vec3 kFwd;   // 0x15f7164

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall FUN_0062cb90(void* self);  // 0x0062cb90 (stays in the slice: not this object's)

// ---- items of slice s0062da00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void* p);                      // 0x00f47380 (EASTL/EA allocator free)
void* memcpy(void*, const void*, unsigned int); // 0x011e0744
struct Vec2 { float x, y; };
struct PathNode {
  Vec2 mPosition;            // +0x00
  PathNode* mLinks[8];       // +0x08
  PathNode* mParent;         // +0x28
  PathNode* mChild;          // +0x2c
  uint8_t mPassable;         // +0x30
  bool mProcessed;           // +0x31
  float mEstDistToGoal;      // +0x34
  float mDistFromStart;      // +0x38
  float mTotalDistance;      // +0x3c
};
struct NodeVector {
  PathNode** mpBegin;
  PathNode** mpEnd;
  PathNode** mpCapacity;
  ~NodeVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin); }
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  bool empty() const { return mpEnd == mpBegin; }
  PathNode*& operator[](uint32_t i) { return mpBegin[i]; }
  void DoInsertValue(PathNode** pos, PathNode* const& value);
  void push_back(PathNode* const& value) {
    if (mpEnd < mpCapacity) {
      new (mpEnd++) PathNode*(value);
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
  PathNode** erase(PathNode** first, PathNode** last) {
    memcpy(first, last, (mpEnd - last) * sizeof(PathNode*));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
class RefCountVTemplate {
 public:
  int mRefCount;
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
};
class cSPCasual_Path : public RefCountVTemplate {
 public:
  float mWidth;              // +0x08
  float mLength;             // +0x0c
  float mWidthIncr;          // +0x10
  float mLengthIncr;         // +0x14
  Vec2 mStartingOffset;      // +0x18
  Vec2 mPositionOffset;      // +0x20
  bool mPathFound;           // +0x28
  bool mDebugging;           // +0x29
  PathNode* mStartNode;      // +0x2c
  PathNode* mGoalNode;       // +0x30
  PathNode* mCurrentPathNode;// +0x34
  PathNode mGrid[64][64];    // +0x38
  NodeVector mOpenList;      // +0x40038

  cSPCasual_Path();
  virtual ~cSPCasual_Path();
  void SetPositionOffset(float x, float y);
  PathNode* FindPassableNeighbor(PathNode* node, PathNode* exclude);
  bool StartPath();
  void RemoveFromOpenList(PathNode* node);
  PathNode* GetBestOpenNode();
  void BlockCircle(float x, float y, float radius, bool blocked);
  bool GetNextPathPoint(Vec2* out);
  void ExpandNode(PathNode* node);
  bool FindPath(float sx, float sy, float gx, float gy);
};
// ---- items of slice s0062da00 end

// @ 0x0062cc20
void __fastcall FUN_0062cc20(void* self, int unused, const Vec3* p, int unused2)
{
  PlayModeCreature* c = (PlayModeCreature*)self;
  AnimData* d = c->mData;
  d->SetTargetPosition(p, 0, 1);
  Vec3 pos = d->mActualPosition;
  if (p->x == pos.x && p->y == pos.y && p->z == pos.z) return;
  Vec3 fwd;
  fwd.x = -kFwd.x;
  fwd.y = -kFwd.y;
  fwd.z = -kFwd.z;
  Vec3 dir;
  dir.x = p->x - pos.x;
  dir.y = p->y - pos.y;
  dir.z = p->z - pos.z;
  float angle = -SignedDot(&dir, &fwd, &kUp);
  d->SetTargetAngle(angle, 0);
}

// @ 0x0062ce00
void PlayModeCreature::AddPathTarget(PathT* p, bool replace)
{
  if (replace) FUN_0062cb90(this);
  if (Empty(mPathList)) {
    unsigned id;
    void* vt = *(void**)mAnimCreature;
    typedef void (__thiscall* PartIdFn)(void*, unsigned*, int, int, int);
    ((PartIdFn)(*(void**)((char*)vt + 0x58)))(mAnimCreature, &id, 0, 0, 0);
    if (id == kPathIdA || id == kPathIdB) {
      FUN_0062cc20(this, 0, &p->mTarget, 0);
    } else {
      FUN_0062cc20(this, 0, &p->mTarget, 0);
      mPlayMode->FUN_00628960(mAnimCreature, mCreatureID);
    }
    int* dst = (int*)&p->mTarget;
    const int* src = (const int*)&mData->mTargetPosition;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
  }
  ARC<PathT> tmp;
  tmp.p = p;
  if (p != 0) p->AddRef();
  if (mPathList.mpEnd < mPathList.mpCap) {
    ARC<PathT>* slot = mPathList.mpEnd;
    mPathList.mpEnd = slot + 1;
    if (slot != 0) {
      slot->p = p;
      if (p != 0) p->AddRef();
    }
  } else {
    mPathList.PushBack(mPathList.mpEnd, &tmp);
  }
  if (tmp.p != 0) tmp.p->Release();
}

// @ 0x0062cef0
void __fastcall FUN_0062cef0(void* self, int unused, unsigned int dtMs)
{
  PlayModeCreature* c = (PlayModeCreature*)self;
  if (!c->mAnimCreature) return;
  float dt = dtMs * 0.001f;
  if (c->mWaitAfter > 0.0f) {
    c->mWaitAfter -= dt;
    if (c->mWaitAfter < 0.0f) c->mWaitAfter = 0.0f;
  }
  if (Empty(c->mPathList)) {
    PathT* w = c->mPathInWaiting.p;
    if (!w) return;
    c->mPathWaitTime -= dt;
    if (c->mPathWaitTime > 0.0f) return;
    w->mReached = (float)w->mCount * 0.3f + w->mReached + 0.6f;
    float ax = c->mAnimCreature->mPosition.x;
    float ay = c->mAnimCreature->mPosition.y;
    float az = c->mAnimCreature->mPosition.z;
    float dx = ax - w->mTarget.x;
    float dy = ay - w->mTarget.y;
    float dz = az - w->mTarget.z;
    if (w->mReached < sqrtf(dx * dx + dy * dy + dz * dz)) {
      w->mCount = w->mCount + 1;
      c->AddPathTarget(c->mPathInWaiting.p, 0);
      c->mPathWaitTime = 0.5f;
      return;
    }
    if (w->mType == 1) c->mWaitAfter = 2.0f;
    c->mPlayMode->StopWalk(c->mAnimCreature, c->mCreatureID);
    c->mPathInWaiting.Reset();
    return;
  }
  PathT* first = c->mPathList.mpBegin[0].p;
  float ax = c->mAnimCreature->mPosition.x;
  float ay = c->mAnimCreature->mPosition.y;
  float az = c->mAnimCreature->mPosition.z;
  float dx = ax - first->mTarget.x;
  float dy = ay - first->mTarget.y;
  float dz = az - first->mTarget.z;
  if (first->mReached < sqrtf(dx * dx + dy * dy + dz * dz)) return;
  unsigned count = (unsigned)(c->mPathList.mpEnd - c->mPathList.mpBegin);
  if (count > 1) {
    FUN_0062cc20(c, 0, &c->mPathList.mpBegin[1].p->mTarget, 0);
    c->mPathList.mpBegin[1].p->mTarget = c->mData->mTargetPosition;
    c->mPathList.EraseFirst(c->mPathList.mpBegin);
    return;
  }
  if (first->mType == 1) c->mWaitAfter = 2.0f;
  c->mPlayMode->StopWalk(c->mAnimCreature, c->mCreatureID);
  c->mPathInWaiting.Reset();
  c->mPathList.EraseFirst(c->mPathList.mpBegin);
}

// @ 0x0062d0f0
bool PlayModeCreature::MoveTo(int, int, bool go, bool follow)
{
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

// @ 0x0062da00
void cSPCasual_Path::SetPositionOffset(float x, float y)
{
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 64; j++) {
      if (mGrid[i][j].mPassable == 1) mGrid[i][j].mPassable = 0;
      mGrid[i][j].mProcessed = false;
      mGrid[i][j].mChild = 0;
    }
  }
  float cx = x;
  float cy = y;
  float hw = mWidthIncr * 0.5f;
  float hl = mLengthIncr * 0.5f;
  if (cx < mStartingOffset.x - hw) cx = mStartingOffset.x;
  if (cy < mStartingOffset.y - hl) cy = mStartingOffset.y;
  float maxX = mWidth + mStartingOffset.x;
  if (maxX + hw < cx) cx = maxX;
  float maxY = mLength + mStartingOffset.y;
  if (maxY + hl < cy) cy = maxY;
  PathNode* node = &mGrid[0][0] + ((int)(((cx - mStartingOffset.x) + hw) / mWidthIncr) * 64 +
                                   (int)(((cy - mStartingOffset.y) + hl) / mLengthIncr));
  if (node != 0) {
    mPositionOffset.x = x - node->mPosition.x;
    mPositionOffset.y = y - node->mPosition.y;
  } else {
    mPositionOffset.x = 0.0f;
    mPositionOffset.y = 0.0f;
  }
}
