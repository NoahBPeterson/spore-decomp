// Slice s007fa520 functions that live in an /O2 module.
// They call the SerItem initialiser out of line; keeping its body out of this
// translation unit reproduces the original register allocation.
#include <cstddef>

struct SerItem { void* type; void* base; unsigned count; void* extra; };
void f_7fb040(void** p, void* a);
void f_7fb1a0(void** p, void* a);

struct VSer {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void* vf();   // +0x14
};

struct C_7fb0e0 : VSer { void f(SerItem* p); };
// @ 0x007fb0e0
void C_7fb0e0::f(SerItem* p) {
  f_7fb040((void**)p, this);
  p->extra = vf();
}

struct C_7fb220 : VSer { void f(SerItem* p); };
// @ 0x007fb220
void C_7fb220::f(SerItem* p) {
  f_7fb1a0((void**)p, (char*)this - 4);
  p->extra = vf();
}
