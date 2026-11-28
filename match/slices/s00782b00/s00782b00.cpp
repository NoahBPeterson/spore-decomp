// 0x00782b00: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: match/slices/s00782860/s00782860.cpp, src/game/SPEngine/_at_00780000.cpp.

struct il2c_vc0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
};

struct C_007806a0 { void FUN_007806a0(); };
struct C_00782800 { void FUN_00782800(unsigned int, unsigned int); };

// @ 0x00782b00
// @ 0x00782b00
extern "C" void __fastcall FUN_00782b00(char* self, int edx_unused)
{
    int t1002;
    int t1006;
    int t1007;
    int t1008;
    t1002 = (int)((int)(self));
    ((C_007806a0*)((int)(self)))->FUN_007806a0();
    t1006 = (int)(*(int*)((char*)(t1002) + 52));
    t1007 = (int)(*(int*)((char*)(t1002) + 48));
    t1008 = (int)(t1002 + (int)48);
    ((C_00782800*)(t1008))->FUN_00782800((unsigned int)(t1007), (unsigned int)(t1006));
    ((il2c_vc0*)((t1002 + (int)(8))))->s9();
    return;
}
