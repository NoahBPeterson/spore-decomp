// Slice s0071f410: SP::cFaceCluster / Text vertex helpers.  Optimized module:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

void Obj15_Init(void* p);                                  // 0x00720070
void Obj15_Assign(void* src, void* dst, int flag);         // 0x0071fce0

// Small record: dword at +0, 16-bit at +8.
struct Obj15 {
    uint32_t m0;        // +0x0
    uint32_t m4;        // +0x4
    uint16_t m8;        // +0x8
};

// 0x18-byte Text::Vertex3D (6 dwords).
struct Vertex3D {
    uint32_t m[6];
};

// @ 0x00720190
void Obj15_ctor(uint32_t a, uint16_t b, Obj15* out)
{
    out->m0 = a;
    out->m8 = b;
    Obj15_Init(out);
}

// @ 0x007201b0
void Obj15_copy(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
}

// @ 0x007201d0
void Obj15_copyAssign(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
    Obj15_Assign((void*)src, dst, 0);
}

// @ 0x00720250
void CopyVertex3D(Vertex3D* first, Vertex3D* last, Vertex3D* dest)
{
    while (first != last) {
        *dest = *first;
        ++first;
        ++dest;
    }
}

// ---------------------------------------------------------------------------
// Remaining functions: skeletons (partial).
// ---------------------------------------------------------------------------
// @ 0x0071f410
void Obj15_f410(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071f590
void Obj15_f590(void* self, void* a, void* b, void* c) { (void)self; (void)a; (void)b; (void)c; }
// @ 0x0071f7e0
void Obj15_f7e0(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071f8f0
void Obj15_f8f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071fce0
void Obj15_fce0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071fd60
void Obj15_fd60(void* a, void* b) { (void)a; (void)b; }
// @ 0x0071fe10
void Obj15_fe10(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x0071ff50
void Obj15_ff50(void* a, void* b) { (void)a; (void)b; }
// @ 0x00720010
void Obj15_20010(void* a, void* b) { (void)a; (void)b; }
// @ 0x00720070
void Obj15_20070(void* a) { (void)a; }
// @ 0x007200f0
void Obj15_200f0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }
// @ 0x00720200
void Obj15_20200(void* a, void* b) { (void)a; (void)b; }
