// @ 0x0108f400
// guarded two-store init: word at offset 6, then the vtable pointer at 0x14a1838.
// Flags: /vc71 /O2 /MD /Gy /TP

extern void* kVtbl14a1838[];

struct S_0108f400 {
    void* vtbl;
    short f4;
    short f6;
};

void FUN_0108f400(S_0108f400* p)
{
    if (p)
    {
        p->f6 = 1;
        p->vtbl = kVtbl14a1838;
    }
}
