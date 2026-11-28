// 0x011374f0: C++ lifted from retail's machine code by vs2005-cpp lift2il; proven equivalent, not byte-exact under /vc71.
// VS2008 (cl 15.00) builds this source to retail's exact bytes; its translation unit is cl 13.10, whose build differs.

extern "C" unsigned char g_016e628c[];
struct C_0112c850 { int FUN_0112c850(unsigned int, unsigned int); };

// @ 0x011374f0
extern "C" int __fastcall FUN_011374f0(char* self, int edx_unused)
{
    int t1001;
    int t1003;
    int t1006;
    int t1007;
    int t1008;
    int t1009;
    int t1010;
    int t1011;
    int t1012;
    int t1013;
    int t1014;
    int t1015;
    int t1016;
    int t1017;
    int t1018;
    int t1019;
    int t1020;
    int t1021;
    t1001 = (int)(*(int*)((char*)((int)(self)) + 40));
    t1003 = (int)((int)0);
    if (t1001 != t1003) {
        goto L1137500;
        L1137500:;
        t1006 = (int)(*(int*)((char*)(t1001) + 12));
        if (t1006 != t1003) {
            t1007 = (int)(*(int*)((char*)(t1006) + 40));
            if (t1001 == t1007) {
                t1008 = (int)(*(int*)((char*)(t1007)));
                *(int*)((char*)(t1006) + 40) = (int)(t1008);
            }
            t1009 = (int)(*(int*)((char*)(t1001) + 4));
            if (t1009 != t1003) {
                t1010 = (int)(*(int*)((char*)(t1001)));
                *(int*)((char*)(t1009)) = (int)(t1010);
            }
            t1011 = (int)(*(int*)((char*)(t1001)));
            if (t1011 != t1003) {
                t1012 = (int)(*(int*)((char*)(t1001) + 4));
                *(int*)((char*)(t1011) + 4) = (int)(t1012);
            }
            *(int*)((char*)(t1001) + 12) = (int)(t1003);
            *(int*)((char*)(t1001) + 8) = (int)(t1003);
            *(unsigned char*)((char*)(t1001) + 16) = (unsigned char)((unsigned char)(t1003));
        }
        t1001 = (int)(*(int*)((char*)((int)(self)) + 40));
        if (t1001 != t1003) goto L1137500;
    }
    if ((unsigned char)*(unsigned char*)((char*)((int)(self)) + 142) != (unsigned char)(t1003)) {
        t1013 = (int)((int)(*(int*)g_016e628c));
        t1014 = (int)((int)(self) + (int)44);
        if (t1014 == t1013) {
            t1015 = (int)(*(int*)((char*)(t1013)));
            *(int*)g_016e628c = (int)(t1015);
        }
        t1016 = (int)(*(int*)((char*)(t1014) + 4));
        if (t1016 != t1003) {
            t1017 = (int)(*(int*)((char*)(t1014)));
            *(int*)((char*)(t1016)) = (int)(t1017);
        }
        t1018 = (int)(*(int*)((char*)(t1014)));
        if (t1018 != t1003) {
            t1019 = (int)(*(int*)((char*)(t1014) + 4));
            *(int*)((char*)(t1018) + 4) = (int)(t1019);
        }
    }
    t1020 = (int)(*(int*)((char*)((int)(self)) + 36));
    if (t1020 != t1003) {
        t1021 = (int)(*(int*)((char*)((int)(self)) + 4));
        t1020 = (int)((C_0112c850*)(t1021))->FUN_0112c850((unsigned int)(t1020), (unsigned int)(t1003));
    }
    return (int)(t1020);
}
