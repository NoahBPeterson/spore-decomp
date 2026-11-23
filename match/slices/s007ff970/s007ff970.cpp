// @ 0x007ff970
// cdecl: reads the object from the first argument and tail-performs its vtable call
// at slot 13 (offset 0x34) with the second argument as the only stack argument.
#define PV(n) virtual void pv##n();
struct V_007ff970 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    virtual void F13(int a);                        // slot 13, offset 0x34
};

void FUN_007ff970(V_007ff970* p, int a)
{
    p->F13(a);
}
