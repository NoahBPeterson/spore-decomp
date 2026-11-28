// 0x01134ae0: C++ lifted from retail's machine code by vs2005-cpp lift2il; proven equivalent, not byte-exact under /vc71.
// VS2008 (cl 15.00) builds this source to retail's exact bytes; its translation unit is cl 13.10, whose build differs.

struct il2c_vc0 {
    virtual void s0();
    virtual int s1(int);
};


// @ 0x01134ae0
extern "C" void __cdecl FUN_01134ae0(int a4)
{
    int t1000;
    t1000 = (int)((int)(a4));
    ((il2c_vc0*)(t1000))->s1((int)((int)0));
    return;
}
