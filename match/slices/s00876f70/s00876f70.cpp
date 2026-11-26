// 0x00876f70: C++ lifted from retail's machine code by vs2005-cpp lift2il + l2c_search (a meaning-preserving rewrite, see the step list below); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: none yet.

// lifted by il2c_lift + l2c_search (swap@8); CI scorer MATCH; corpus status nonmatching/residual
// @ 0x00876f70
extern "C" void __cdecl FUN_00876f70(int a4, int a8)
{
    int t1000;
    int t1001;
    int t1002;
    int t1003;
    int t1005;
    t1000 = (int)((int)(a4));
    if ((unsigned char)*(unsigned char*)((char*)(t1000) + 9) == (unsigned char)16) {
        t1001 = (int)(*(unsigned char*)((char*)(t1000) + 10));
        t1003 = (int)((int)(a8));
        t1002 = (int)(t1001 * (int)*(int*)((char*)(t1000)));
        if ((unsigned int)(t1002) > (unsigned int)0) {
            t1005 = (int)(t1002);
            do {
                *(unsigned char*)&(t1002) = (unsigned char)(*(unsigned char*)((char*)(t1003)));
                *(unsigned char*)&(t1000) = (unsigned char)(*(unsigned char*)((char*)(t1003) + 1));
                *(unsigned char*)((char*)(t1003)) = (unsigned char)((unsigned char)(t1000));
                *(unsigned char*)((char*)(t1003) + 1) = (unsigned char)((unsigned char)(t1002));
                t1003 = (int)(t1003 + (int)2);
                t1005 = (int)(t1005 - (int)1);
            } while (t1005 != (int)0);
        }
    }
    return;
}
