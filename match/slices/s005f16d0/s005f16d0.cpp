// Slice s005f16d0: SP::cSPSwatchPlanner / cSwatch3DView area.  Field offsets taken from the
// binary; the many small predicates are reconstructed exactly, large Init/DoMessage stubbed.
#include "types.h"

#define PV(n) virtual void _pv##n();

class cWriter {
 public:
  int GetBuffer();
};

class cObj2 {
 public:
  int Get();
};

class cRenderSomething {
 public:
  void Render(int arg);
};

int Fun_005a8ed0(int a, int b, int c, int d);

namespace SP {
class cSPSwatchPlanner {
 public:
  int m00;      // +0x00
  void* m04;    // +0x04
  int m08;      // +0x08
  int m0c;      // +0x0c
  char pad10[0x1c];
  void* m2c;    // +0x2c
  char pad30[0x64];
  float m94;    // +0x94
  char pad98[0x53];
  bool mEB;     // +0xeb
  char padEC[0x14];
  int m100;     // +0x100
  char pad104[0x5c];
  bool m160;    // +0x160
  char pad161[2];
  bool m163;    // +0x163
  char pad164[2];
  bool m166;    // +0x166
  char pad167[0x31];
  bool m198;    // +0x198

  int Check();
  void SetModel(int arg);
  void* Cast(uint32_t id);
  int CheckType();
  float GetDouble94();
  int Contains(const float* point);
  int GetBuffer();
  void DoMessage();
  void Init();
  void Init3D();
};

// @ 0x005f2180
int cSPSwatchPlanner::Check() {
  if (mEB != 0) {
    if (m166 != 0 && m160 != 0 && m163 != 0)
      return 1;
    return 0;
  }
  if (m166 != 0 && m160 != 0)
    return 1;
  return 0;
}

// @ 0x005f22d0
int cSPSwatchPlanner::CheckType() {
  if (m198 != 0 && m100 == 0x71fa7d3f)
    return 1;
  return 0;
}

// @ 0x005f2310
float cSPSwatchPlanner::GetDouble94() {
  return m94 + m94;
}

// @ 0x005f2350
int cSPSwatchPlanner::Contains(const float* point) {
  const float* self = (const float*)this;
  return point[0] >= self[0] && point[1] >= self[1] && point[0] < self[2] && point[1] < self[3];
}

// @ 0x005f22a0
void* cSPSwatchPlanner::Cast(uint32_t id) {
  if (id == 0x3349c94)
    return this;
  if (id == 0xee3f516e)
    return this;
  if (id == 0x2f009dd0)
    return this;
  return id == 0x31e56741 ? this : 0;
}

// @ 0x005f2740
int cSPSwatchPlanner::GetBuffer() {
  if (m04)
    return ((cWriter*)m04)->GetBuffer();
  if (m2c)
    return ((cObj2*)m2c)->Get();
  return 0;
}

// @ 0x005f21d0
void cSPSwatchPlanner::SetModel(int arg) { (void)arg; }

// @ 0x005f16d0
void cSPSwatchPlanner::DoMessage() {}

// @ 0x005f1960
void cSPSwatchPlanner::Init() {}

// @ 0x005f24e0
void cSPSwatchPlanner::Init3D() {}

// @ 0x005f2390
void SizeViewportToWindowAndRemainOnScreen() {}
}  // namespace SP
