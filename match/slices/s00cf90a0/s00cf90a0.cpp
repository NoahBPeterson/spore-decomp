// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct V {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int Query(int id); // slot +0x0c
};
struct Manager {
    int Method(int x); // 0x00cfe780
};
struct Thing {
    int Get(); // 0x00dd8640
};
extern Manager* g_manager; // 0x0169d3c8
Thing* __stdcall Make(int a, int b, int c, int d, int e, int f); // 0x00b3d3e0

// @ 0x00cf90a0
int __stdcall FUN_00cf90a0(V* a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    Manager* m = g_manager;
    int id = a1 ? a1->Query(0x017f243b) : 0;
    int saved = m->Method(id);
    int result = Make(a2, a3, a4, a5, a6, a7)->Get();
    m->Method(saved);
    return result;
}
