// Slice s00ebc2f0 -- PARTIAL. Function 00ebc2f0 (2436 bytes): thiscall(this in ecx, Obj* a0 at [esp+4], float scale at [esp+8]), ret 8.
// Verified so far: prologue, model/manager queries, center/height math, the vt+0x38 query, and the
// per-item loop header. NOT yet written: loop body (property queries, feedback-event lookup, the
// vt+0x58 matrix call, Matrix3 assign + vt+0x18 submit, vector cleanup on the early-return paths).
// Built /O2 /MD /Gy /EHsc /TP.
typedef unsigned char  u8;
typedef unsigned int   u32;

#define VT(p) (*(void***)(p))

struct Box { float a[3]; float b[3]; };   // vt+0x6c / vt+0x68 return Box*: a = min, b = max

struct BakeTest {
    void Run(void* a0, float scale);      // 00ebc2f0
};

void BakeTest::Run(void* a0, float scale)
{
    void* esi = a0;
    void* p4c = 0;   // [esp+0x4c]
    void* p48 = 0;   // [esp+0x48]
    if (esi) {
        // vt+0x5c(id): ids 0x1186577 (discarded), 0xb033b403, 0xce9f6639, then 0x1186577 kept in esi
        typedef void* (__thiscall *F1)(void*, u32);
        ((F1)VT(esi)[0x5c / 4])(esi, 0x1186577u);
        p4c = ((F1)VT(esi)[0x5c / 4])(esi, 0xb033b403u);
        p48 = ((F1)VT(esi)[0x5c / 4])(esi, 0xce9f6639u);
        esi = ((F1)VT(esi)[0x5c / 4])(esi, 0x1186577u);
    } else {
        p4c = 0; p48 = 0; esi = 0;
    }
    (void)p4c; (void)p48; (void)scale;
    // TODO(partial): center = ((a[0]+b[0])*.5, (a[1]+b[1])*.5, (a[2]+b[2])*.5) from esi->vt+0x6c(&tmp); h = (b[2]-a[2])*.5 from vt+0x68.
    // TODO(partial): bVar20/flag from p4c (+0x714, vt c3be10 -> h), p48 early-return if byte[+0x137]==0.
    // TODO(partial): ModelManager()->GetIndex(0x6086e65,0) and Find(0x3fbae24)->vt+0x38 (4 args, see asm 00ebc4af..00ebc51e).
    // TODO(partial): per-item loop over vector at [esp+0x110..0x114] with the body described in the asm.
}
