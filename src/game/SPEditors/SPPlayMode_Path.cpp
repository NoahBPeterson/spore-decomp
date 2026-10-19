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
