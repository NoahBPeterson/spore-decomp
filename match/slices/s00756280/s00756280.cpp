// slice s00756280 -- SP model-region / material / job helpers (BuildRegionToInfoMap etc).
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2.  No byte-exact matches yet;
// FUN_007565a0 has a complete translation, the rest are compiling skeletons.
// See nonmatching.txt / partial.txt.

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations): signatures/conventions only.
// ---------------------------------------------------------------------------
void* operator new(unsigned int n, const char* name, int, int, int, int);
void operator delete(void* p);
char FUN_007564b0(int param_1);
void FUN_0071ddc0(int, int, int, int, int);
void FUN_0041d8b0(void*);
void FUN_006df280(void*);
void FUN_006909b0();
void FUN_006913c0(int);
void FUN_0068f4d0();
void FUN_0068f950(void*);
void FUN_0068f9b0(void*);
void FUN_00728020(void*, float, int, void*);
void FUN_007387f0(void*);
void FUN_007389c0(void*, int);
void FUN_00738900(void*);
void FUN_00753dc0(int, unsigned char);
void FUN_00753fe0(void*, void*);

class X_7565a0 {
 public:
  virtual void a0();
  virtual void a1();
  virtual void a2(int);
  char pad_0[0x6c - 4];
  X_7565a0(int, int);
};

// @ 0x00756280  (539 bytes) -- skeleton
void FUN_00756280(void* self) { (void)self; }

// @ 0x007564b0  (197 bytes) EH job start -- skeleton
void FUN_007564b0(void* self) { (void)self; }

// @ 0x007565a0
unsigned int FUN_007565a0(int param_1, int param_2, int param_3) {
  if (param_1 != 0 && param_2 != 0) {
    X_7565a0* p = new ("Graphics", 0, 0, 0, 0) X_7565a0(param_1, param_2);
    if (p != 0) {
      char c = FUN_007564b0(param_3);
      if (c != 0) {
        return 1;
      }
      p->a2(1);
    }
  }
  return 0;
}

// @ 0x00756650  (316 bytes) EH job ctor -- skeleton
void FUN_00756650(void* self) { (void)self; }

// @ 0x00756790  (194 bytes) EH refcounted new -- skeleton
void FUN_00756790(void* self) { (void)self; }

// @ 0x00756860  SP::BuildRegionToInfoMap (439 bytes) -- skeleton
void FUN_00756860(void* self) { (void)self; }

// @ 0x00756a20  (284 bytes) EH job step -- skeleton
void FUN_00756a20(void* self) { (void)self; }

// @ 0x00756b50  (288 bytes) refcount swap + part update -- skeleton
void FUN_00756b50(void* self) { (void)self; }

// @ 0x00756c70  (262 bytes) part holder resolve -- skeleton
void FUN_00756c70(void* self) { (void)self; }

// @ 0x00756d80  (575 bytes) -- skeleton
void FUN_00756d80(void* self) { (void)self; }

// @ 0x00756fc0  (417 bytes) -- skeleton
void FUN_00756fc0(void* self) { (void)self; }
