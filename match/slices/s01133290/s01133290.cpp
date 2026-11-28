// 0x01133290: C++ lifted from retail's machine code by vs2005-cpp lift2il; proven equivalent, not byte-exact under /vc71.
// VS2008 (cl 15.00) builds this source to retail's exact bytes; its translation unit is cl 13.10, whose build differs.

extern "C" unsigned char g_016e6268[];

// @ 0x01133290
extern "C" int __cdecl FUN_01133290(void)
{
    int t1000;
    int t1004;
    int t1005;
    int t1006;
    t1000 = (int)((int)(*(int*)g_016e6268));
    if (t1000 != (int)0) {
        do {
            t1004 = (int)(*(int*)((char*)(t1000) + 12));
            t1005 = (int)(*(int*)((char*)(t1000) + 8));
            t1006 = (int)(*(int*)((char*)(t1000)));
            ((void (__cdecl*)(int))(t1005))((int)(t1004));
            t1000 = (int)(t1006);
        } while (t1006 != (int)0);
    }
    return (int)(t1000);
}
