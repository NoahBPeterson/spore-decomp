// slice s005d53e0 -- 2D path-shape helpers (circle/line intersections, intersection lists, path segment
// list), SP::cEditorsTokenTranslator (ctor, deleting dtor, TranslateToken) and small editor helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc; no security cookie on TranslateToken's buffer).
#include <new>
#include <math.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags, const char* file,
                   int line);  // 0x00f473a0
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags, const char* file,
                     int line);

#define PV(n) virtual void pv##n();

struct Vector2 {
  float x, y;
  Vector2() {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
struct Point2 {
  float x, y;
};

namespace eastl {
template <typename T>
inline const T& min(const T& a, const T& b) {
  return (b < a) ? b : a;
}
template <typename T>
inline const T& max(const T& a, const T& b) {
  return (a < b) ? b : a;
}

template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value);
  void push_back_inline(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
class cPathShape;

struct PathIntersection {
  PathIntersection() {}
  PathIntersection(cPathShape* shape, cPathShape* other, const Vector2& position, int flags)
      : mpShape(shape), mpOther(other), mFlags(flags) {
    mPosition = position;
  }
  cPathShape* mpShape;   // +0x0
  cPathShape* mpOther;   // +0x4
  Vector2 mPosition;     // +0x8
  int mFlags;            // +0x10
};

extern float kTwoPi;  // 0x015ee798

int CircleLineIntersection(Vector2 p1, Vector2 p2, Vector2 center, float radius, float* result);  // below

struct Circle {
  Vector2 mCenter;
  float mRadius;
  int Intersect(const Circle& other, Vector2* points);  // 0x005d5250
};
struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
Vector3 GetPosition(const void* desc);  // 0x004a5d10
float GetRadius(const void* desc);    // 0x004a5bd0

class cPathShape {
 public:
  cPathShape(int type, const void* desc);
  float FindNextIntersection(const Vector2& point, bool clockwise, PathIntersection** result);
  void AddIntersection(const Vector2& position, int flags, cPathShape* other);
  void IntersectWith(cPathShape* other);
  void IntersectLine(const Vector2& p1, const Vector2& p2, cPathShape* other);

  int mType;                                       // +0x0
  Circle mCircle;                                  // +0x4
  eastl::sp_vector<PathIntersection> mIntersections;  // +0x10
};

// @ 0x005D53E0
float cPathShape::FindNextIntersection(const Vector2& point, bool clockwise, PathIntersection** result) {
  float px = point.x;
  float py = point.y;
  float dx = px - mCircle.mCenter.x;
  float dy = py - mCircle.mCenter.y;
  float invLength = 1.0f / (float)sqrt(dx * dx + dy * dy);
  float dirX = invLength * dx;
  float dirY = invLength * dy;
  PathIntersection* best = 0;
  float bestAngle = kTwoPi;
  for (unsigned int i = 0; i < mIntersections.size(); i++) {
    PathIntersection& entry = mIntersections[i];
    if (fabs(px - entry.mPosition.x) > 1.52587890625e-05f || fabs(py - entry.mPosition.y) > 1.52587890625e-05f) {
      float ex = entry.mPosition.x;
      float ey = entry.mPosition.y;
      float edx = ex - mCircle.mCenter.x;
      float edy = ey - mCircle.mCenter.y;
      float invLen = 1.0f / (float)sqrt(edx * edx + edy * edy);
      float dot = invLen * edx * dirX + invLen * edy * dirY;
      if (dot > 1.0f)
        dot = 1.0f;
      else if (dot < -1.0f)
        dot = -1.0f;
      float angle = (float)acos(dot);
      float cross = (px - mCircle.mCenter.x) * (ey - mCircle.mCenter.y) -
                    (py - mCircle.mCenter.y) * (ex - mCircle.mCenter.x);
      if (!(cross < 0.0f))
        angle = kTwoPi - angle;
      if (!clockwise)
        angle = kTwoPi - angle;
      if (angle < bestAngle) {
        bestAngle = angle;
        best = &entry;
      }
    }
  }
  *result = best;
  return clockwise ? bestAngle : -bestAngle;
}

// @ 0x005D5630
int CircleLineIntersection(Vector2 p1, Vector2 p2, Vector2 center, float radius, float* result) {
  float x2 = p2.x - center.x;
  float x1 = p1.x - center.x;
  float y2 = p2.y - center.y;
  float y1 = p1.y - center.y;
  float dy = y2 - y1;
  float dx = x2 - x1;
  float dr = (float)sqrt(dx * dx + dy * dy);
  float det = y2 * x1 - y1 * x2;
  float sign = dy < 0.0f ? -1.0f : 1.0f;
  float dr2 = dr * dr;
  float disc = dr2 * radius * radius - det * det;
  float root = (float)sqrt(disc);
  float absTerm = (float)(fabs(dy) * root);
  float signTerm = root * sign * dx;
  result[2] = (det * dy - signTerm) / dr2;
  result[0] = (det * dy + signTerm) / dr2 + center.x;
  result[1] = (absTerm - det * dx) / dr2 + center.y;
  result[3] = (-(det * dx) - absTerm) / dr2;
  result[2] = result[2] + center.x;
  result[3] = center.y + result[3];
  if (disc < 0.0f)
    return 0;
  return disc == 0.0f ? 1 : 2;
}

// @ 0x005D57D0
cPathShape::cPathShape(int type, const void* desc) {
  mIntersections.mpBegin = 0;
  mIntersections.mpEnd = 0;
  mIntersections.mpCapacity = 0;
  mType = type;
  Vector3 position = GetPosition(desc);
  mCircle.mCenter.x = position.y;
  mCircle.mCenter.y = position.z;
  mCircle.mRadius = GetRadius(desc);
}

// @ 0x005D5B60
void cPathShape::AddIntersection(const Vector2& position, int flags, cPathShape* other) {
  mIntersections.push_back_inline(PathIntersection(this, other, position, flags));
}

// @ 0x005D5BE0
void cPathShape::IntersectWith(cPathShape* other) {
  Vector2 points[2];
  int count = mCircle.Intersect(other->mCircle, points);
  if (count >= 1) {
    PathIntersection entry(this, other, points[0], 0);
    mIntersections.push_back_inline(entry);
    other->mIntersections.push_back_inline(entry);
    if (count >= 2) {
      entry.mPosition = points[1];
      mIntersections.push_back(entry);
      other->mIntersections.push_back(entry);
    }
  }
}

// @ 0x005D5CF0
void cPathShape::IntersectLine(const Vector2& p1, const Vector2& p2, cPathShape* other) {
  float points[4];
  int count = CircleLineIntersection(p1, p2, mCircle.mCenter, mCircle.mRadius, points);
  if (count > 0) {
    float minX = eastl::min(p1.x, p2.x);
    float maxY = eastl::max(p1.y, p2.y);
    float maxX = eastl::max(p1.x, p2.x);
    float minY = eastl::min(p1.y, p2.y);
    if (points[0] >= minX && maxX >= points[0] && points[1] >= minY && maxY >= points[1])
      AddIntersection(*(Vector2*)&points[0], 1, other);
    if (count > 1 && points[2] >= minX && maxX >= points[2] && points[3] >= minY && maxY >= points[3])
      AddIntersection(*(Vector2*)&points[2], 1, other);
  }
}

// vector<PathIntersection>::DoInsertValue / push_back (x87 float copies: a TU without /arch:SSE)
// @ 0x005D5830  (source in s005d53e0_nosse.cpp)
// @ 0x005D5970  (source in s005d53e0_nosse.cpp)

// ---------------------------------------------------------------------------------------------
class cPathSegment {
 public:
  virtual float GetLength();
};
class cArcSegment : public cPathSegment {
 public:
  cArcSegment(const Point2& center, float sweep, const Point2& start, float radius)
      : mCenter(center), mStart(start), mRadius(radius), mSweep(sweep) {}
  virtual float GetLength();
  Point2 mCenter;  // +0x4
  Point2 mStart;   // +0xc
  float mRadius;    // +0x14
  float mSweep;     // +0x18
};
class cLineSegment : public cPathSegment {
 public:
  cLineSegment(const Point2& start, const Point2& end) : mStart(start), mEnd(end) {}
  virtual float GetLength();
  Point2 mStart;  // +0x4
  Point2 mEnd;    // +0xc
};

class cPathSegmentList {
 public:
  cPathSegmentList();
  ~cPathSegmentList();
  void AddArc(const Point2& center, float sweep, const Point2& start, float radius);
  void AddLine(const Point2& start, const Point2& end);

  eastl::sp_vector<cPathSegment*> mSegments;  // +0x0
  float mLength;                              // +0x14
};

// @ 0x005D57B0
cPathSegmentList::cPathSegmentList() {
  mSegments.mpBegin = 0;
  mSegments.mpEnd = 0;
  mSegments.mpCapacity = 0;
  mLength = 0.0f;
}

// @ 0x005D59C0
cPathSegmentList::~cPathSegmentList() {
  for (unsigned int i = 0; i < mSegments.size(); i++)
    EASTL_allocator_deallocate(mSegments[i]);
  {
    cPathSegment** first = mSegments.mpBegin;
    cPathSegment** last = mSegments.mpEnd;
    EASTL_memmove(first, last, (unsigned int)((char*)mSegments.mpEnd - (char*)last));
    mSegments.mpEnd -= (last - first);
  }
  if (mSegments.mpBegin && ((int*)mSegments.mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mSegments.mpBegin);
}

// @ 0x005D5A30
void cPathSegmentList::AddArc(const Point2& center, float sweep, const Point2& start, float radius) {
  cArcSegment* segment = new ("Editor", 0, 0, 0, 0) cArcSegment(center, sweep, start, radius);
  mLength += segment->GetLength();
  mSegments.push_back_inline(segment);
}

// @ 0x005D5AD0
void cPathSegmentList::AddLine(const Point2& start, const Point2& end) {
  cLineSegment* segment = new ("Editor", 0, 0, 0, 0) cLineSegment(start, end);
  mLength += segment->GetLength();
  mSegments.push_back_inline(segment);
}

// ---------------------------------------------------------------------------------------------
namespace eastl {
class string16 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  string16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
  ~string16() {
    if (((mpCapacity - mpBegin) > 1) && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);         // 0x00579a90
  string16& operator=(const string16& x);         // 0x0057cb60
  string16& operator=(const wchar_t* p);          // 0x005c3d90
  string16& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  string16& assign(const wchar_t* p) {
    const wchar_t* end = p;
    while (*end)
      ++end;
    return assign(p, p + (end - p));
  }
};
}  // namespace eastl

namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseMode);  // 0x00932f30
}
namespace Locale {
int SetNumberString(double value, wchar_t* buffer, int bufferSize, int flags);  // 0x00881ea0
}
}  // namespace EA

namespace SP {
class cStringTokenTranslator {
 public:
  cStringTokenTranslator();           // 0x006b5870
  virtual ~cStringTokenTranslator();  // 0x005725a0
  virtual int AddRef();
  virtual int Release();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16& result);
  int mRefCount;
};

class cEditorsTokenTranslator : public cStringTokenTranslator {
 public:
  cEditorsTokenTranslator();
  virtual ~cEditorsTokenTranslator();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16& result);

  unsigned int mAmount;               // +0x8
  eastl::string16 mOldModelName;      // +0xc
  eastl::string16 mNewModelName;      // +0x1c
  const wchar_t* mUserName;           // +0x2c
  const wchar_t* mYear;               // +0x30
  const wchar_t* mMonth;              // +0x34
  const wchar_t* mDayOfMonth;         // +0x38
  const wchar_t* mTime;               // +0x3c
};

// @ 0x005D5E40
cEditorsTokenTranslator::cEditorsTokenTranslator()
    : mAmount(0), mOldModelName(L"UnsetName"), mNewModelName(L"UnsetName") {}

// @ 0x005D5E90  scalar deleting dtor (??_G, inlines the dtor)
cEditorsTokenTranslator::~cEditorsTokenTranslator() {}

// @ 0x005D5EF0
bool cEditorsTokenTranslator::TranslateToken(const wchar_t* token, eastl::string16& result) {
  switch (EA::Hash::FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x37f56d0a:
      result = mOldModelName;
      return true;
    case 0xe736e65:
      result = mMonth;
      return true;
    case 0x540e2100:
      result.assign(mTime);
      return true;
    case 0xda3ea6ed:
      result = mNewModelName;
      return true;
    case 0xc534734a:
      result = mYear;
      return true;
    case 0xe7d52113:
      result = mDayOfMonth;
      return true;
    case 0xed0db5e3:
      result = mUserName;
      return true;
    case 0xef91ad29: {
      result = L"";
      wchar_t buffer[64];
      EA::Locale::SetNumberString((double)mAmount, buffer, 64, 0);
      buffer[63] = 0;
      result = buffer;
      return true;
    }
  }
  return false;
}
}  // namespace SP

// ---------------------------------------------------------------------------------------------
class cResourceLoader {
 public:
  void* Load(void* a, void* b, int c, int d, int e, int f, int g, int h);  // 0x00928a30
};
extern cResourceLoader* gResourceLoader;  // 0x016c8b44

// @ 0x005D60F0
void* LoadResource(void* a, void* b) {
  return gResourceLoader->Load(a, b, 0, 0, 0, 0, 0, 0);
}

class cSharedObject {
 public:
  virtual ~cSharedObject();
  short mbRefCounted;  // +0x4
  short mRefCount;     // +0x6
  void Release() {
    if (mbRefCounted) {
      if (--mRefCount == 0)
        delete this;
    }
  }
};
extern cSharedObject* gSharedObject;  // 0x016e4184

// @ 0x005D6120
void SetSharedObject(cSharedObject* object) {
  if (gSharedObject)
    gSharedObject->Release();
  gSharedObject = object;
}

class cDataDirectory {
 public:
  const wchar_t* GetDirectoryName(int index);
};

// @ 0x005D6170
const wchar_t* cDataDirectory::GetDirectoryName(int index) {
  return index == 0 ? L"data" : 0;
}

namespace SP {
class IEditorSubsystem {
 public:
  PV(0) PV(1) PV(2)
  virtual void PreShutdown();  // +0xc
};
class cEditorSystem {
 public:
  bool PreShutdown();
  uint32_t pad00[8];
  IEditorSubsystem* mpSubsystem;  // +0x20
};

// @ 0x005D6190
bool cEditorSystem::PreShutdown() {
  if (IEditorSubsystem* subsystem = mpSubsystem)
    subsystem->PreShutdown();
  return true;
}
}  // namespace SP
