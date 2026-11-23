// @ 0x00dc4ac0
// cdecl: the embedded object at offset 0x34 performs its vtable call at slot 59
// (offset 0xec) on itself (this adjusted by add ecx, 0x34); the result is ignored and
// the wrapper returns true.
#define PV(n) virtual void pv##n();
struct Inner_00dc4ac0 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
    virtual bool F59();                             // slot 59, offset 0xec
};

struct Outer_00dc4ac0 {
    char pad_0x34[0x34];
    Inner_00dc4ac0 mInner;
};

bool FUN_00dc4ac0(Outer_00dc4ac0* p)
{
    p->mInner.F59();
    return true;
}
