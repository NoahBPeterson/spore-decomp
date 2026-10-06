// Slice s0092b840: mostly large EA/RefPack string-splitting and decompression routines.
// Only the small big-endian writer is reconstructed exactly; the rest are skeletons (partial.txt).
#include <intrin.h>

// @ 0x0092C2D0  EA::Util::WriteToBigEndian
void WriteToBigEndian(void* dst, unsigned value, int size) {
    if (size == 1) { *(unsigned char*)dst = (unsigned char)value; return; }
    if (size == 4) { *(unsigned*)dst = _byteswap_ulong(value); return; }
    unsigned char hi = (unsigned char)(value >> 8);
    if (size == 2) { *(unsigned short*)dst = _byteswap_ushort((unsigned short)value); return; }
    if (size == 3) {
        ((unsigned char*)dst)[0] = (unsigned char)(value >> 16);
        ((unsigned char*)dst)[1] = hi;
        ((unsigned char*)dst)[2] = (unsigned char)value;
    }
}

// ================================================================== skeletons (partial)
// @ 0x0092B840  split/parse helper
void FUN_0092b840(int* a, int* b) { (void)a; (void)b; }
// @ 0x0092BBE0  large string-table builder
int FUN_0092bbe0(int* a, int b) { (void)a; (void)b; return 0; }
// @ 0x0092C0C0
struct Splitable1 { void Set(const short* s); };
void Splitable1::Set(const short* s) { (void)s; }
// @ 0x0092C130
struct Splitable2 { void Set(const char* s); };
void Splitable2::Set(const char* s) { (void)s; }
// @ 0x0092C1B0
struct Splitable3 { Splitable3(int arg); };
Splitable3::Splitable3(int arg) { (void)arg; }
// @ 0x0092C210
struct Splitable4 { Splitable4(int arg); };
Splitable4::Splitable4(int arg) { (void)arg; }
// @ 0x0092C340  RefPack::DecodeUnchecked
int DecodeUnchecked(unsigned char* dst, unsigned hint, unsigned char* src) {
    (void)dst; (void)hint; (void)src; return 0;
}
