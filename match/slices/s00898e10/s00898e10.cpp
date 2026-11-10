// Slice s00898e10 -- two-phase "report buffer" builder: allocate (count * 0x20)
// bytes through an allocator object's vtable slot 2, then hand the request to a
// reporting helper (0x00c04920) together with the float that the 0x00898ce0
// initialiser leaves in the caller's stack slot just above `this`.
//
// The helper takes 5 arguments (out, a, b, c, buf) but ret 0xc: the last push
// belongs to a callee that cleans only four of them, so the request is written
// as two nested calls -- Emit builds `out = this + 1` and calls Fill, whose 4th
// argument is the buffer returned by the allocation.  Residual diff: cl 15
// keeps `this`/`buf` in edi (push edi) where the original keeps them in esi and
// frees edx (mov edx, ecx).

#include "game/types.h"

// Flags: /O2 /MD /Gy /EHsc /TP /Isrc/game/include

struct AllocObj {
    virtual void* f0();                             // +0x00
    virtual void* f1();                             // +0x04
    virtual void* allocate(unsigned size, int align, void* tag);   // +0x08
};

struct ReportHelper;

struct Reporter {
    void* m00;                                      // +0x00
    void* m04;                                      // +0x04
    void* m08;                                      // +0x08
    void* m0c;                                      // +0x0c  allocator object
    void* m10;                                      // +0x10  allocation tag

    void* Build(int count, void* a, void* b, void* c);   // 0x00898e10
    void  Emit(ReportHelper* out, void* a, void* b, void* c, void* buf);
};

struct ReportHelper {
    void* m00;                                      // +0x00
    float m04;                                      // +0x04  set up by 0x00898ce0
    void* m08;                                      // +0x08
    void* m0c;                                      // +0x0c
    void* m10;                                      // +0x10

    void Fill(void* p0, void* p1, void* p2, void* p3);   // 0x00c04920
};

// @ 0x00898e10
void* Reporter::Build(int count, void* a, void* b, void* c)
{
    void* buf;
    if (count != 0)
    {
        AllocObj* alloc = (AllocObj*)m0c;
        void* tag = m10;
        buf = alloc->allocate((unsigned)(count << 5), 0, tag);
    }
    else
    {
        buf = 0;
    }
    Emit((ReportHelper*)(this + 1), a, b, c, buf);
    return buf;
}

void Reporter::Emit(ReportHelper* out, void* a, void* b, void* c, void* buf)
{
    out->Fill(buf, a, b, c);
}
