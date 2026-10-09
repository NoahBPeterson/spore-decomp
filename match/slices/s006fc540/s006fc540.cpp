// SP fragment-shader module (part 5): cFragmentDecl binary Write/Read, vector set_capacity,
// ClearPSFragment, and cFragmentShader::Write.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

// ==========================================================================================
// Binary (de)serialization of the 0x19-byte fragment-decl record.
// IO::Put/Get are inline forwarding overloads: they build a by-value temporary and pass its
// address to the underlying cdecl stream call, which is what the original compiler emitted.
struct IO;
extern "C" IO* IOPut(IO* io, const void* p, int n);          // operator<<
extern "C" IO* IOGetB(IO* io, const void* p, int n);         // byte read
extern "C" IO* IOWriteU16(IO* io, const uint16_t* p, int n, int f);
extern "C" IO* IOWriteU32(IO* io, const uint32_t* p, int n, int f);
extern "C" IO* IOGet16(IO* io, const void* p, int n, int f);
extern "C" IO* IOGet32(IO* io, const void* p, int n, int f);

struct IO {
  IO* Put(uint8_t v)  { return IOPut(this, &v, 1); }
  IO* Put(uint16_t v) { return IOWriteU16(this, &v, 1, 0); }
  IO* Put(uint32_t v) { return IOWriteU32(this, &v, 1, 0); }
  IO* Get(uint8_t& v)  { return IOGetB(this, &v, 1); }
  IO* Get(uint16_t& v) { return IOGet16(this, &v, 1, 0); }
  IO* Get(uint32_t& v) { return IOGet32(this, &v, 1, 0); }
};

struct FragRec {
  uint8_t  pad0;
  uint8_t  m1;    // +1
  uint16_t m2;    // +2
  uint16_t m4;    // +4
  uint16_t m6;    // +6
  uint32_t m8;    // +8
  uint32_t mc;    // +0xc
  uint32_t m10;   // +0x10
  uint32_t m14;   // +0x14
  uint8_t  m18;   // +0x18
  bool Write(IO* io);                     // 0x006fceb0
  bool Read(IO* io, uint32_t version);    // 0x006fcdc0
};

// @ 0x006fceb0
bool FragRec::Write(IO* io) {
  io->Put(m1);
  io->Put(m2);
  io->Put(m4);
  io->Put(m6);
  io->Put(m8);
  io->Put(mc);
  io->Put(m10);
  io->Put(m14);
  io->Put(m18);
  return true;
}

// @ 0x006fcdc0
bool FragRec::Read(IO* io, uint32_t version) {
  io->Get(m1);
  if (version <= 6) {
    uint8_t tmp;
    io->Get(tmp);
  }
  io->Get(m2);
  io->Get(m4);
  io->Get(m6);
  if (version <= 6) {
    uint16_t tmp;
    io->Get(tmp);
    io->Get(tmp);
    io->Get(tmp);
  }
  io->Get(m8);
  io->Get(mc);
  io->Get(m10);
  io->Get(m14);
  io->Get(m18);
  return true;
}

// ==========================================================================================
// Larger members (see partial.txt).
struct Vec25 {
  char pad[0x40];
  void set_capacity(unsigned n);   // 0x006fc540
  void AppendMoved(void* p, unsigned n);  // 0x006fc780
  void ClearRegions();             // 0x006fcb90
};

// @ 0x006fc540
void Vec25::set_capacity(unsigned n) { (void)n; }

// @ 0x006fc780
void Vec25::AppendMoved(void* p, unsigned n) { (void)p; (void)n; }

// @ 0x006fcb90
void Vec25::ClearRegions() {}

// @ 0x006fc6a0
void ClearPSFragment() {}

// @ 0x006fcf90
bool FragmentShaderWrite(void* io) { (void)io; return true; }

// @ 0x006fd1b0
void DestroyShaderArrays(void* self) { (void)self; }

// @ 0x006fd280
void* ConstructShaderArrays(void* self) { return self; }

// @ 0x006fd300
int ReleaseShader(void* self) { (void)self; return 0; }

// @ 0x006fd330
void SerializeShaderBlock(void* a, void* b) { (void)a; (void)b; }
