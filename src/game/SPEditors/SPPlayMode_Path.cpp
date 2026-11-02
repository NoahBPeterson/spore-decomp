// src/game/SPEditors/SPPlayMode_Path.cpp -- migrated from slice(s) s0062da00 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayMode_Path.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <new>

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

// @ 0x0062db30
PathNode* cSPCasual_Path::FindPassableNeighbor(PathNode* node, PathNode* exclude)
{
  int i2 = 0;
  PathNode** p7 = &node->mLinks[0];
  PathNode** p5 = p7;
  do {
    PathNode* n3 = *p5;
    if (n3 && n3->mPassable == 0 && n3 != exclude) return n3;
    i2++;
    p5++;
  } while (i2 < 8);
  i2 = 0;
  p5 = p7;
  do {
    if (*p5 != 0) {
      int i3 = 0;
      PathNode** p6 = &(*p5)->mLinks[0];
      do {
        PathNode* n4 = *p6;
        if (n4 && n4->mPassable == 0 && n4 != exclude) return n4;
        i3++;
        p6++;
      } while (i3 < 8);
    }
    i2++;
    p5++;
  } while (i2 < 8);
  i2 = 0;
  do {
    if (*p7 != 0) {
      int i3 = 0;
      p5 = &(*p7)->mLinks[0];
      do {
        if (*p5 != 0) {
          PathNode** p6 = &(*p5)->mLinks[0];
          int i4 = 0;
          do {
            PathNode* n1 = *p6;
            if (n1 && n1->mPassable == 0 && n1 != exclude) return n1;
            i4++;
            p6++;
          } while (i4 < 8);
        }
        i3++;
        p5++;
      } while (i3 < 8);
    }
    i2++;
    p7++;
    if (7 < i2) return 0;
  } while (true);
}

// @ 0x0062dc10
void cSPCasual_Path::RemoveFromOpenList(PathNode* node)
{
  int n = (int)mOpenList.size();
  int i = 0;
  if (0 < n) {
    PathNode** p = mOpenList.mpBegin;
    do {
      if (node == *p) break;
      i++;
      p++;
    } while (i < n);
  }
  if (i != n) {
    for (; i < n - 1; i++) mOpenList[i] = mOpenList[i + 1];
    mOpenList.mpEnd--;
  }
}

// @ 0x0062dc70
PathNode* cSPCasual_Path::GetBestOpenNode()
{
  if (((uint32_t)((char*)mOpenList.mpEnd - (char*)mOpenList.mpBegin) & 0xfffffffcu) != 0) {
    PathNode** p = mOpenList.mpBegin;
    PathNode* best = *p;
    uint32_t i = 1;
    if (1 < (uint32_t)(mOpenList.mpEnd - p)) {
      do {
        p++;
        if (best->mTotalDistance > (*p)->mTotalDistance) best = *p;
        i++;
      } while (i < mOpenList.size());
    }
    return best;
  }
  return 0;
}

// @ 0x0062de70
cSPCasual_Path::cSPCasual_Path()
{
  mPathFound = false;
  mDebugging = false;
  mOpenList.mpBegin = 0;
  mOpenList.mpEnd = 0;
  mOpenList.mpCapacity = 0;
}

// @ 0x0062dea0
cSPCasual_Path::~cSPCasual_Path()
{}

// @ 0x0062df10
void cSPCasual_Path::ExpandNode(PathNode* node)
{
  PathNode* cur;
  PathNode* pn = node;
  node->mProcessed = true;
  if (node->mParent == 0) {
    node->mDistFromStart = 0.0f;
    node->mEstDistToGoal = 0.0f;
    node->mTotalDistance = 0.0f;
  } else {
    node->mParent->mChild = node;
  }
  RemoveFromOpenList(node);
  PathNode** pl = &node->mLinks[0];
  int i = 0;
  do {
    cur = *pl;
    if (cur == mGoalNode) {
      cur->mParent = pn;
      pn->mChild = cur;
      mPathFound = true;
      return;
    }
    if (cur != 0 && cur->mPassable == 0 && !cur->mProcessed) {
      cur->mParent = pn;
      float dx = cur->mPosition.x - mGoalNode->mPosition.x;
      float dy = cur->mPosition.y - mGoalNode->mPosition.y;
      cur->mEstDistToGoal = sqrtf(dy * dy + dx * dx);
      float d = sqrtf((cur->mPosition.y - pn->mPosition.y) * (cur->mPosition.y - pn->mPosition.y) +
                      (cur->mPosition.x - pn->mPosition.x) * (cur->mPosition.x - pn->mPosition.x)) +
                pn->mDistFromStart;
      cur->mDistFromStart = d;
      cur->mTotalDistance = d + cur->mEstDistToGoal;
      cur->mProcessed = true;
      mOpenList.push_back(cur);
    }
    pl++;
    i++;
  } while (i < 8);
}

// @ 0x0062e010
bool cSPCasual_Path::FindPath(float sx, float sy, float gx, float gy)
{
  float cx = sx;
  float cy = sy;
  float hw = mWidthIncr * 0.5f;
  float hl = mLengthIncr * 0.5f;
  if (cx < mStartingOffset.x - hw) cx = mStartingOffset.x;
  if (cy < mStartingOffset.y - hl) cy = mStartingOffset.y;
  float maxX = mWidth + mStartingOffset.x;
  if (maxX + hw < cx) cx = maxX;
  float maxY = mLength + mStartingOffset.y;
  if (maxY + hl < cy) cy = maxY;
  PathNode* start = &mGrid[0][0] + ((int)(((cx - mStartingOffset.x) + hw) / mWidthIncr) * 64 +
                                    (int)(((cy - mStartingOffset.y) + hl) / mLengthIncr));
  mStartNode = start;
  float ex = gx;
  float ey = gy;
  if (ex < mStartingOffset.x - hw) ex = mStartingOffset.x;
  if (ey < mStartingOffset.y - hl) ey = mStartingOffset.y;
  if (maxX + hw < ex) ex = maxX;
  if (maxY + hl < ey) ey = maxY;
  PathNode* goal = &mGrid[0][0] + ((int)(((ex - mStartingOffset.x) + hw) / mWidthIncr) * 64 +
                                   (int)(((ey - mStartingOffset.y) + hl) / mLengthIncr));
  mGoalNode = goal;
  if (start == 0 || goal == 0 || start == goal) return false;
  if (goal->mPassable != 0) {
    PathNode* n = FindPassableNeighbor(goal, start);
    if (n == 0) return false;
    mGoalNode = n;
  }
  if (start->mPassable != 0) {
    PathNode* n = FindPassableNeighbor(start, 0);
    if (n != 0) mStartNode = n;
  }
  mOpenList.clear();
  mOpenList.push_back(mStartNode);
  PathNode* cur = mStartNode;
  mPathFound = false;
  cur->mParent = 0;
  if (!mPathFound) {
    while (ExpandNode(cur), !mPathFound) {
      cur = GetBestOpenNode();
      if (cur == 0) return false;
      if (mPathFound) return true;
    }
    PathNode* n = mGoalNode;
    if (n != mStartNode) {
      do {
        n->mParent->mChild = n;
        n = n->mParent;
      } while (n != mStartNode);
    }
  }
  return true;
}
