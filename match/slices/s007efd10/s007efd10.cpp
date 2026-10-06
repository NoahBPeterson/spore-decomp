// s007efd10: original function @ 0x007efd10 (5389 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as s007eed10).
//
// VolState::BuildSlices(dir, outVerts, outCounts): view-aligned slicing of the
// volume's 8-corner box (corners at this+0x6c, 0x18 bytes each: position +
// 3D texcoord).  Classic incremental slicing:
//   * project the corners on dir, find the nearest/farthest corner;
//   * start three active edges at the farthest corner, keyed in a max-heap
//     (priority queue of 16-byte {double depth, Edge*} events) by the depth of
//     their far end;
//   * for every slice plane (from the farthest plane down to the nearest
//     corner, step = camera->mSliceSpacing), retire every corner above the
//     plane: a corner reached by one edge splits it into two new edges, a
//     corner reached by two adjacent edges merges them into one;
//   * emit the active-edge ring as one polygon (vertex list + vertex count)
//     and step every edge's position by its per-slice delta.
// The edge pool holds 12 edges (a box has 12 edges).
#include "types.h"
#include <math.h>
#include <new>

// ---------------------------------------------------------------------------
// Heap of 16-byte events (helpers matched in slice s007eed10).
// ---------------------------------------------------------------------------
struct Edge;

struct HeapNode {
  double d;      // event depth (heap key, max-heap)
  Edge* edge;    // edge whose far corner is at depth d
  uint32_t y;    // unused
};

struct EmptyCmp { char x; };

void AdjustHeap(HeapNode* first, int top, int length, int hole, HeapNode value, EmptyCmp cmp);
void MakeHeap(HeapNode* first, HeapNode* last, EmptyCmp cmp);

inline void PopHeap(HeapNode* first, HeapNode* last, EmptyCmp cmp) {
  const HeapNode tempBottom(*(last - 1));
  *(last - 1) = *first;
  AdjustHeap(first, 0, (int)((last - 1) - first), 0, tempBottom, cmp);
}

void SpVectorDealloc(void* p);  // operator delete[] (sp_vector_allocator)

// eastl::priority_queue<HeapNode, vector<HeapNode, sp_vector_allocator>, less>
struct PQ {
  HeapNode* mpBegin;     // +0x00
  HeapNode* mpEnd;       // +0x04
  HeapNode* mpCapacity;  // +0x08
  uint32_t mAlloc[2];    // +0x0c
  EmptyCmp mCmp;         // +0x14

  PQ() : mpBegin(0), mpEnd(0), mpCapacity(0) {
    mCmp.x = 0;
    MakeHeap(mpBegin, mpEnd, mCmp);
  }
  ~PQ() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) SpVectorDealloc(mpBegin);
  }
  const HeapNode& top() const { return *mpBegin; }
  void pop() {
    PopHeap(mpBegin, mpEnd, mCmp);
    --mpEnd;
  }
  void Push(const HeapNode& v);   // 0x007efc90
};

// ---------------------------------------------------------------------------
// Slice vertex: position + 3D texcoord.
// ---------------------------------------------------------------------------
struct SliceVertex {
  float x, y, z;
  float u, v, w;
};

inline SliceVertex Scaled(const SliceVertex& a, float s) {
  SliceVertex r;
  r.x = a.x * s; r.y = a.y * s; r.z = a.z * s;
  r.u = a.u * s; r.v = a.v * s; r.w = a.w * s;
  return r;
}
inline SliceVertex Diff(const SliceVertex& a, const SliceVertex& b) {
  SliceVertex r;
  r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z;
  r.u = a.u - b.u; r.v = a.v - b.v; r.w = a.w - b.w;
  return r;
}
inline SliceVertex AddScaled(const SliceVertex& a, const SliceVertex& d, float t) {
  SliceVertex r;
  r.x = a.x + d.x * t; r.y = a.y + d.y * t; r.z = a.z + d.z * t;
  r.u = a.u + d.u * t; r.v = a.v + d.v * t; r.w = a.w + d.w * t;
  return r;
}

struct SliceVertexVector {   // eastl::vector<SliceVertex>
  SliceVertex* mpBegin;
  SliceVertex* mpEnd;
  SliceVertex* mpCapacity;
  void DoInsertValue(SliceVertex* position, const SliceVertex& value);   // 0x007efa20
  void push_back(const SliceVertex& value) {
    if (mpEnd < mpCapacity)
      new (mpEnd++) SliceVertex(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

struct UIntVector {          // eastl::vector<unsigned int, sp_vector_allocator>
  unsigned* mpBegin;
  unsigned* mpEnd;
  unsigned* mpCapacity;
  void DoInsertValue(unsigned* position, const unsigned& value);   // 0x004558a0
  void push_back(const unsigned& value) {
    if (mpEnd < mpCapacity)
      new (mpEnd++) unsigned(value);
    else
      DoInsertValue(mpEnd, value);
  }
};

// Active edge of the slicing front.
struct Edge {
  bool done;           // +0x00 far corner already retired
  int from;            // +0x04 corner index
  int to;              // +0x08 corner index
  SliceVertex cur;     // +0x0c intersection with the current slice plane
  SliceVertex delta;   // +0x24 per-slice step
  Edge* prev;          // +0x3c
  Edge* next;          // +0x40
};

// Camera / slicing reference object (VolState::m10).
struct SliceCamera {
  char pad0[8];
  float px, py, pz;      // +0x08 reference point
  float mSliceSpacing;   // +0x14
};

struct VolState {
  char pad0[0x10];
  SliceCamera* mpCamera;       // +0x10
  char pad14[0x6c - 0x14];
  SliceVertex mCorners[8];     // +0x6c

  void BuildSlices(float dx, float dy, float dz, SliceVertexVector& verts, UIntVector& counts);
};

// Sets up edge e from corner `from` to corner `to` against the plane at sliceD.
__forceinline void InitEdge(VolState* self, Edge* e, int from, int to, float dFrom, float dTo, float sliceD) {
  e->done = false;
  e->from = from;
  e->to = to;
  float dd = dTo - dFrom;
  if (dd != 0.0f) {
    float inv = 1.0f / dd;
    e->delta = Scaled(Diff(self->mCorners[to], self->mCorners[from]), inv);
    e->cur = AddScaled(self->mCorners[from], e->delta, sliceD - dFrom);
    float s = self->mpCamera->mSliceSpacing;
    e->delta.x *= s; e->delta.y *= s; e->delta.z *= s;
    e->delta.u *= s; e->delta.v *= s; e->delta.w *= s;
  }
}

// @ 0x007efd10
void VolState::BuildSlices(float dx, float dy, float dz, SliceVertexVector& verts, UIntVector& counts) {
  // The three neighbours of each box corner.
  int neighbours[8][3] = {
    { 1, 2, 4 }, { 0, 5, 3 }, { 0, 3, 6 }, { 1, 7, 2 },
    { 0, 6, 5 }, { 1, 4, 7 }, { 2, 7, 4 }, { 3, 5, 6 },
  };
  // nextCorner[v][p]: walking around corner v, the neighbour that follows p.
  int nextCorner[8][8] = {
    { -1,  2,  4, -1,  1, -1, -1, -1 },
    {  5, -1, -1,  0, -1,  3, -1, -1 },
    {  3, -1, -1,  6, -1, -1,  0, -1 },
    { -1,  7,  1, -1, -1, -1, -1,  2 },
    {  6, -1, -1, -1, -1,  0,  5, -1 },
    { -1,  4, -1, -1,  7, -1, -1,  1 },
    { -1, -1,  7, -1,  2, -1, -1,  4 },
    { -1, -1, -1,  5, -1,  6,  3, -1 },
  };

  float depth[8];
  for (int i = 0; i < 8; ++i)
    depth[i] = mCorners[i].x * dx + mCorners[i].z * dz + mCorners[i].y * dy;

  float maxD = depth[0];
  float minD = depth[0];
  int maxIdx = 0;
  for (int i = 1; i < 8; ++i) {
    float d = depth[i];
    if (minD > d)
      minD = d;
    else if (d > maxD) {
      maxD = d;
      maxIdx = i;
    }
  }

  SliceCamera* cam = mpCamera;
  float spacing = cam->mSliceSpacing;
  float base = cam->px * dx + cam->pz * dz + cam->py * dy;
  float n = (float)floor((double)((maxD - base) / spacing));
  float sliceD = spacing * n + base;

  Edge edges[12];
  Edge* pFree = edges;
  Edge* pFirst = edges;
  PQ pq;

  // Three edges leave the farthest corner.
  float topD = depth[maxIdx];
  for (int i = 0; i < 3; ++i) {
    int to = neighbours[maxIdx][i];
    InitEdge(this, pFree, maxIdx, to, topD, depth[to], sliceD);
    pFree->prev = &edges[(i + 2) % 3];
    pFree->next = &edges[(i + 1) % 3];
    HeapNode ev;
    ev.d = depth[to];
    ev.edge = pFree;
    pq.Push(ev);
    ++pFree;
  }

  while (sliceD > minD) {
    // Retire every corner above the current plane.
    while (pq.top().d >= sliceD) {
      if (pFree - edges >= 12)
        break;
      Edge* e = pq.top().edge;
      int v = e->to;
      if (e->done) {
        pq.pop();
        continue;
      }
      if (v == e->prev->to || v == e->next->to) {
        // Two adjacent edges meet at v: replace them by one edge.
        Edge* a;
        Edge* b;
        if (v == e->prev->to) {
          a = e->prev;
          b = e;
        } else {
          a = e;
          b = e->next;
        }
        float dv = depth[v];
        b->done = true;
        a->done = true;
        int to = nextCorner[v][a->from];
        float dTo = depth[to];
        InitEdge(this, pFree, v, to, dv, dTo, sliceD);
        pFree->prev = a->prev;
        a->prev->next = pFree;
        pFree->next = b->next;
        b->next->prev = pFree;
        HeapNode ev = pq.top();
        pq.pop();
        ev.d = dTo;
        ev.edge = pFree;
        pFirst = pFree;
        pq.Push(ev);
        ++pFree;
      } else {
        // One edge reaches v: split it into two edges.
        float dv = depth[v];
        e->done = true;
        int to1 = nextCorner[v][e->from];
        float d1 = depth[to1];
        InitEdge(this, pFree, v, to1, dv, d1, sliceD);
        Edge* e1 = pFree;
        e1->prev = e->prev;
        e->prev->next = e1;
        e1->next = e1 + 1;
        HeapNode ev = pq.top();
        pq.pop();
        ev.d = d1;
        ev.edge = e1;
        pq.Push(ev);
        ++pFree;
        if (pFree - edges >= 12)
          break;

        int to2 = nextCorner[v][to1];
        float d2 = depth[to2];
        InitEdge(this, pFree, v, to2, dv, d2, sliceD);
        pFree->prev = pFree - 1;
        pFree->next = e->next;
        e->next->prev = pFree;
        pFirst = pFree;
        HeapNode ev2;
        ev2.d = d2;
        ev2.edge = pFree;
        pq.Push(ev2);
        ++pFree;
      }
    }

    // Drop events of retired edges.
    while (pq.top().edge->done)
      pq.pop();

    if (sliceD > pq.top().d) {
      // Emit the polygon and advance every edge to the next plane.
      unsigned count = 0;
      Edge* p = pFirst;
      do {
        verts.push_back(p->cur);
        ++count;
        p->cur.x -= p->delta.x;
        p->cur.y -= p->delta.y;
        p->cur.z -= p->delta.z;
        p->cur.u -= p->delta.u;
        p->cur.v -= p->delta.v;
        p->cur.w -= p->delta.w;
        p = p->next;
      } while (p != pFirst);
      counts.push_back(count);
    }

    sliceD -= mpCamera->mSliceSpacing;
  }
}
