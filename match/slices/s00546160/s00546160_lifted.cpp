// 0x00546160: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPFeedXml.cpp, match/slices/s00546160/s00546160.cpp.

struct C_00429520 { void FUN_00429520(unsigned int); };
struct C_005459a0 { int FUN_005459a0(); };
struct C_00545ad0 { int FUN_00545ad0(); };
struct C_00545bd0 { int FUN_00545bd0(); };
struct C_00545ca0 { int FUN_00545ca0(unsigned int, unsigned int); };
struct C_00545dc0 { int FUN_00545dc0(unsigned int); };
extern "C" int __cdecl FUN_00685520(...);
extern "C" int __cdecl FUN_00932f30(...);

// @ 0x00546160
// @ 0x00546160
extern "C" void __cdecl FUN_00546160(int a4, int a8, int a12)
{
    int v_l8;
    int v_l12;
    v_l12 = a4;
    ((C_00429520*)(v_l12 + 16))->FUN_00429520((unsigned int)0);
    v_l8 = (int)(int)FUN_00932f30((unsigned int)a8, (unsigned int)-2128831035, (unsigned int)0);
    switch ((unsigned int)((v_l8))) {
    case 1556742160:
        L54624b:;
        ((C_005459a0*)v_l12)->FUN_005459a0();
        break;
    case -4936033:
        L546258:;
        ((C_00545ca0*)v_l12)->FUN_00545ca0((unsigned int)(int)*(int*)((char*)v_l12 + 32), (unsigned int)v_l8);
        break;
    case 1614666929:
        L54626d:;
        ((C_00545ca0*)v_l12)->FUN_00545ca0((unsigned int)(int)*(int*)((char*)v_l12 + 36), (unsigned int)v_l8);
        break;
    case 1918600745:
        L546282:;
        if ((int)(unsigned char)(int)FUN_00685520((unsigned int)2) != 0) {
            ((C_00545ca0*)v_l12)->FUN_00545ca0((unsigned int)(int)*(int*)((char*)v_l12 + 36), (unsigned int)v_l8);
        }
        break;
    case -905792094:
        L5462a8:;
        ((C_00545ca0*)v_l12)->FUN_00545ca0((unsigned int)(int)*(int*)((char*)v_l12 + 40), (unsigned int)v_l8);
        break;
    case -2110676301:
    case -1015726594:
        L5462bd:;
        ((C_00545ad0*)v_l12)->FUN_00545ad0();
        break;
    case -507048242:
    case 136358817:
        L5462c7:;
        ((C_00545dc0*)v_l12)->FUN_00545dc0((unsigned int)a12);
        break;
    case -322031280:
    case 249251079:
        L5462d5:;
        ((C_00545bd0*)v_l12)->FUN_00545bd0();
    }
    return;
}
