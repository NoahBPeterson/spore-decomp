// Slice s00e3eca0: keyframe-style interpolation over a map<int, IObj*> (function 00e3ee30).
// Keys are hashed state ids; each step looks up two objects (member map at this+0xc8 and a global
// map<int,uint32> at 0x015a59fc used for range bounds), calls GetVec4 (slot 14) and SetVec4 (slot 27).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// Virtual placeholders: slots 0..13 and 15..26 are never called from this function.
struct IObj {
  virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
  virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
  virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13();
  virtual float* GetVec4();  // slot 14 (+0x38)
  virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
  virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
  virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
  virtual void SetVec4(float* v);  // slot 27 (+0x6c)
};

struct MapIntU32 {  // global map<int, uint32_t> at 0x015a59fc; operator[] 0x00de7630
  uint32_t& operator[](const int& key);  // 0x00de7630
};

struct MapIntObj {  // map<int, IObj*> member at this+0xc8; operator[] 0x00e3ec20 (thiscall, ret 4)
  IObj*& operator[](const int& key);  // 0x00e3ec20
};

struct Interp {
  char pad[0xc8];
  // float Run(float acc, int key, int end): thiscall, ret 0xc
  float Run(float acc, int key, int end);
};

float Interp::Run(float acc, int key, int end) {
  MapIntU32& g = *(MapIntU32*)0x015a59fc;
  uint32_t* a = &g[key];
  uint32_t* b = &g[end];
  if (*a > *b) return acc;
  if (key == end) return acc;
  MapIntObj& m = *(MapIntObj*)((char*)this + 0xc8);
  do {
    IObj* o = m[key];
    float* p = o->GetVec4();
    float v[4];
    v[0] = p[0];
    v[1] = p[1];
    v[2] = p[2];
    v[3] = p[3];
    if (key < -0x414ad734) {
      if (key == -0x414ad735) {
        v[2] = v[0] + acc;
        o->SetVec4(v);
        key = 0x2db6dad3;
      } else if (key == -0x5bd98cf5) {
        v[2] = v[0] + acc;
        o->SetVec4(v);
        key = -0x52a9f7f4;
      } else {
        if (key != -0x52a9f7f4) goto LAB_step2;
        v[2] = v[0] + acc;
        o->SetVec4(v);
        key = -0x8e05cef;
      }
      acc = 5.0f;
    } else if (key == -0x8e05cef) {
      v[2] = v[0] + acc;
      o->SetVec4(v);
      key = -0x414ad735;
      acc = 5.0f;
    }
LAB_step2:
    IObj* o2 = m[key];
    float* q = o2->GetVec4();
    float w[4];
    w[0] = v[2];
    w[1] = q[1];
    w[2] = (q[2] - q[0]) + v[2];
    w[3] = q[3];
    o2->SetVec4(w);
  } while (key != end);
  return acc;
}
