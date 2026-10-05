#pragma once
// Stub declarations for slice s006b37d0 (SP default save areas).
#include "types.h"

// object with a counter at +0x40 (0x6b42f0).
struct Counter40 {
  uint32_t pad[0x10];
  uint32_t m40;
  bool Inc();
};

// secondary-vtable object referenced through a pointer slot (0x6b4390).
struct SecBase6 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual uint32_t Call0c(uint32_t);
};
struct ObjSec6 { uint32_t pad0; SecBase6 sec; };

// job holder at 0x01604b48 with an EA mutex.
struct Mutex6 { Mutex6(int, int); ~Mutex6(); };
struct Job6 { void GetStatus(); };
struct JobPtr6 { void* p; JobPtr6() : p(0) {} ~JobPtr6(); };
struct JobHolder6 {
  JobPtr6 job;      // +0x00
  uint32_t pad;     // +0x04
  Mutex6 mutex;     // +0x08
  JobHolder6();
  ~JobHolder6();
};
extern JobHolder6 g_jobHolder6;   // 0x01604b48
extern uint32_t  g_1604b80;
inline void* operator new(uint32_t, void* p) { return p; }
