// Slice s00f2c470.  Scenario resource / building-data copy and serialization
// helpers.  Built /O2 /MD /Gy /TP.

typedef unsigned int uint;
typedef unsigned int size_t;

struct VOp { void copyFrom(const void* p); };
struct Big { int tag; char rest[0x234]; };   // size 0x238

// @ 0x00f2d5e0
Big* fn2d5e0(Big* p, Big* e, Big* out) {
  if (p != e) {
    do {
      if (out) {
        out->tag = p->tag;
        unsigned u = (unsigned)p->tag;
        if ((u >> 31) & 1) {
        } else if ((char*)out + 4 != 0) {
          (*(VOp*)((char*)out + 4)).copyFrom((char*)p + 4);
        }
      }
      p = (Big*)((char*)p + 0x238);
      out = (Big*)((char*)out + 0x238);
    } while (p != e);
  }
  return out;
}

// @ 0x00f2cfa0
int* fn2cfa0(int* first, int* last, int* out) {
  if (last == first) return out;
  do {
    last = (int*)((char*)last - 0x188);
    out = (int*)((char*)out - 0x188);
    out[0] = last[0];
    out[1] = last[1];
    out[2] = last[2];
    out[3] = last[3];
    *(char*)(out + 4) = *(char*)(last + 4);
    out[5] = last[5];
    (*(VOp*)(out + 6)).copyFrom(last + 6);
    *(int*)((char*)out + 0x184) = *(int*)((char*)last + 0x184);
  } while (last != first);
  return out;
}

// ---------------------------------------------------------------------------
// Remaining functions (not fully reconstructed).

// @ 0x00f2c470
void fn2c470() {}
// @ 0x00f2c5d0
void fn2c5d0() {}
// @ 0x00f2c6a0
void fn2c6a0() {}
// @ 0x00f2c810
void fn2c810() {}
// @ 0x00f2c950
void fn2c950() {}
// @ 0x00f2cb50
void fn2cb50() {}
// @ 0x00f2ced0
int* fn2ced0(int* p, int* e, int* out) { (void)p; (void)e; (void)out; return out; }
// @ 0x00f2d090
void fn2d090() {}
// @ 0x00f2d260
void fn2d260() {}
// @ 0x00f2d330
void fn2d330() {}
// @ 0x00f2d3d0
void fn2d3d0() {}
