// 0x005462f0: C++ lifted from retail's machine code by vs2005-cpp lift2il, /Od mode (il2c_od); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPBake/SPFeedXml.cpp, match/slices/s00546160/s00546160.cpp.

extern "C" unsigned char g_013f3ae0[];
struct C_004228e0 { void FUN_004228e0(unsigned int); void FUN_004228e0(unsigned int, unsigned int); };
struct C_00545aa0 { int FUN_00545aa0(); };
struct C_00545b20 { int FUN_00545b20(); };
struct C_00545bf0 { int FUN_00545bf0(); };
struct C_00545c10 { int FUN_00545c10(); };
struct C_00545c60 { int FUN_00545c60(); };
struct C_00545cc0 { int FUN_00545cc0(); };
struct C_00545ce0 { int FUN_00545ce0(); };
struct C_00545d30 { int FUN_00545d30(); };
struct C_00545d80 { int FUN_00545d80(); };
struct C_00545fa0 { int FUN_00545fa0(); };
struct C_00546020 { int FUN_00546020(); };
struct C_00546050 { int FUN_00546050(); };
struct C_00546090 { int FUN_00546090(); };
struct C_005460d0 { int FUN_005460d0(); };
struct C_00546110 { int FUN_00546110(); };
struct C_00547900 { int FUN_00547900(unsigned int, unsigned int, unsigned int); };
struct C_00547970 { int FUN_00547970(unsigned int, unsigned int, unsigned int, unsigned int); };
extern "C" int __cdecl FUN_00932f30(...);

// @ 0x005462f0
extern "C" void __cdecl FUN_005462f0(int a4, int a8)
{
    int v_l16_i;
    int v_l12_40;
    int v_l8;
    int v_l20;
    int dead_0[2];
    int v_l32;
    int dead_1[2];
    v_l16_i = a4;
    v_l8 = v_l16_i + 16;
    v_l20 = (int)g_013f3ae0;
    while ((int)*(unsigned short*)(char*)v_l20 != 0) {
        v_l20 = v_l20 + 2;
    }
    ((C_004228e0*)v_l8)->FUN_004228e0((unsigned int)0, (unsigned int)((C_00547900*)v_l8)->FUN_00547900((unsigned int)(int)g_013f3ae0, (unsigned int)0, (unsigned int)(v_l20 - (int)g_013f3ae0 >> 1)));
    v_l32 = (int)g_013f3ae0;
    while ((int)*(unsigned short*)(char*)v_l32 != 0) {
        v_l32 = v_l32 + 2;
    }
    ((C_004228e0*)v_l8)->FUN_004228e0((unsigned int)(int)(((C_00547970*)v_l8)->FUN_00547970((unsigned int)(int)g_013f3ae0, (unsigned int)-1, (unsigned int)(v_l32 - (int)g_013f3ae0 >> 1), (unsigned int)-1) + 1));
    v_l12_40 = (int)(int)FUN_00932f30((unsigned int)a8, (unsigned int)-2128831035, (unsigned int)0);
    switch ((unsigned int)((v_l12_40))) {
    case 1556742160:
        L546554:;
        ((C_00545aa0*)v_l16_i)->FUN_00545aa0();
        break;
    case -2074397404:
        L546561:;
        ((C_00546050*)v_l16_i)->FUN_00546050();
        break;
    case 1287754890:
        L54656e:;
        ((C_00546090*)v_l16_i)->FUN_00546090();
        break;
    case 1542007429:
        L546578:;
        ((C_005460d0*)v_l16_i)->FUN_005460d0();
        break;
    case -431502949:
        L546582:;
        ((C_00546110*)v_l16_i)->FUN_00546110();
        break;
    case -4936033:
    case 1614666929:
    case 1918600745:
        L54658c:;
        ((C_00545cc0*)v_l16_i)->FUN_00545cc0();
        break;
    case -2110676301:
    case -1015726594:
        L546596:;
        ((C_00545b20*)v_l16_i)->FUN_00545b20();
        break;
    case -322031280:
    case 249251079:
        L5465a0:;
        ((C_00545bf0*)v_l16_i)->FUN_00545bf0();
        break;
    case 120691491:
    case 797654004:
        L5465aa:;
        ((C_00545c10*)v_l16_i)->FUN_00545c10();
        break;
    case -1749308580:
    case 996836781:
        L5465b4:;
        ((C_00545c60*)v_l16_i)->FUN_00545c60();
        break;
    case -589240787:
    case 513994172:
        L5465be:;
        ((C_00545ce0*)v_l16_i)->FUN_00545ce0();
        break;
    case -837215646:
    case -701100687:
        L5465c8:;
        ((C_00545d30*)v_l16_i)->FUN_00545d30();
        break;
    case 426171525:
    case 1752637606:
        L5465d2:;
        ((C_00545fa0*)v_l16_i)->FUN_00545fa0();
        break;
    case -881585110:
    case 34912047:
        L5465dc:;
        ((C_00546020*)v_l16_i)->FUN_00546020();
        break;
    case 334643013:
    case 1900784230:
        L5465e6:;
        ((C_00545d80*)v_l16_i)->FUN_00545d80();
    }
    return;
}
