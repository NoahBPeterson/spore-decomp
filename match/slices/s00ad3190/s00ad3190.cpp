// Slice s00ad3190. Compiled with /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// (the original uses scalar SSE: ucomiss/subss without double promotion).

struct Vector3 {
  float x, y, z;
  Vector3() {}
  Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
  bool operator==(const Vector3& o) const { return x == o.x && y == o.y && z == o.z; }
  bool operator!=(const Vector3& o) const { return x != o.x || y != o.y || z != o.z; }
  Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
};

struct Quaternion {
  float x, y, z, w;
};

struct Transform {
  Vector3 mPosition;        // +0x00
  Quaternion mOrientation;  // +0x0C
  int mUnknown[5];          // +0x1C .. 0x30
  void Init();     // 0x00AD7940
  void Release();  // 0x00AD7AD0
};

// Object returned by the vtable cast (id 0x0447FF9B).
struct PlacementData {
  int pad0[3];
  int mTarget;             // +0x0C
  int mA0, mA1, mShared;   // +0x10 +0x14 +0x18
  float ax, ay, az;        // +0x1C
  int mB0, mB1;            // +0x28 +0x2C
  float bx, by, bz;        // +0x30
};

struct Component {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual PlacementData* Cast(unsigned int id);  // slot 3
};

struct MathUtil {
  Quaternion RotationFrom(const Vector3& a);                       // 0x00B7F190
  Quaternion RotationBetween(const Vector3& a, const Vector3& b);  // 0x00B7F250
};

struct Manager {
  int pad[0x148 / 4];
  int mField148;
  void Apply(int target, Transform* xf, int arg);  // 0x00AE09B0
};

MathUtil* GetMathUtil();  // 0x00B3D350
Manager* GetManager();    // 0x00B3D4D0
void ComputePoint(Vector3& out, Transform* xf, int a, int b, int c, const Vector3& v);  // 0x00AD2AE0
Vector3 Normalize(const Vector3& v);  // 0x00449C20
extern Vector3 kZeroVector;           // 0x0167A4BC

// @ 0x00AD3190
int FUN_00ad3190(Component* c) {
  if (c) {
    PlacementData* d = c->Cast(0x447ff9b);
    if (d) {
      Transform xf;
      xf.Init();
      Vector3 a, b;
      {
        Vector3 p0(d->ax, d->ay, d->az);
        Vector3 p1(d->bx, d->by, d->bz);
        ComputePoint(a, &xf, d->mA0, d->mA1, d->mShared, p0);
        ComputePoint(b, &xf, d->mB0, d->mB1, d->mShared, p1);
      }
      xf.mPosition = a;
      if (b != kZeroVector && b != a) {
        Vector3 n = Normalize(b - a);
        xf.mOrientation = GetMathUtil()->RotationBetween(a, n);
      } else
        xf.mOrientation = GetMathUtil()->RotationFrom(a);
      int arg = GetManager()->mField148;
      GetManager()->Apply(d->mTarget, &xf, arg);
      xf.Release();
    }
  }
  return 1;
}
