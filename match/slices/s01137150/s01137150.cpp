// 0x01137150: C++ lifted from retail's machine code by vs2005-cpp lift2il; proven equivalent, not byte-exact under /vc71.
// VS2008 (cl 15.00) builds this source to retail's exact bytes; its translation unit is cl 13.10, whose build differs.

// @ 0x01137150
extern "C" int __cdecl FUN_01137150(int a4)
{
    int t1000;
    int t1001;
    int t1;
    int t1002;
    int t1003;
    int t2;
    int t1004;
    t1000 = (int)((int)(a4));
    t1001 = (int)(*(unsigned char*)((char*)(t1000) + 8));
    t1 = (int)(t1001 << (int)3);
    t1002 = (int)(t1);
    t1003 = (int)(t1002 - t1001);
    t2 = (int)(t1003 << (int)2);
    t1004 = (int)(t2 + (int)128);
    return (int)(t1004);
}
