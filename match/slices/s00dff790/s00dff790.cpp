// Slice s00dff790 (batch bfs1 #38).  Galaxy/simulator input strategies.
// 32-bit MSVC 2008 SP1, /O2 /arch:SSE.
//
// The large inlined functions are stubbed (see partial.txt).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_SporeGuide();
extern "C" void* __cdecl SP_MessageServer();
extern "C" void* __cdecl SP_MovieSystem();
extern "C" void* __cdecl SP_GetCurrentGameMode();
extern "C" void* __cdecl SP_ResourceMan_GetManager();
extern "C" void  __cdecl sub_644b10(void*);
extern "C" void  __cdecl sub_644b60(void*);
extern "C" void  __cdecl sub_e02040(void*);
extern "C" void  __cdecl sub_ec5a60(void*, int, int);
struct EC { char sub_ec4320(); };
struct GObj { char pad_00[0x108]; int field108; char pad_10c[0x270 - 0x10c]; u8 b270; void sub_de52d0(); };

// ===========================================================================
//  0x00e00630  base-class ctor (vtable + one flag byte)
// ===========================================================================
struct VBase {
    void** vftable;              // +0x00
    u8     b4;                   // +0x04
    VBase();
};
// @ 0x00e00630
VBase::VBase() {
    vftable = (void**)0x147dba8;
    b4 = 0;
}

// ===========================================================================
//  0x00e00560  conditional helper call
// ===========================================================================
struct Thisc { int m(); };
// @ 0x00e00560
void __stdcall e00560(int dummy) {
    (void)dummy;
    void* ab = SP_AssetBrowser();
    GObj* g = *(GObj**)0x16a1344;
    if (g->field108 == 7 &&
        *(char*)((char*)ab + 0x1c) == 0 &&
        g->b270 == 0) {
        int* mm = *(int**)0x16c7aa4;
        EC* ec = *(EC**)((char*)mm + 0x1c);
        if (!ec->sub_ec4320()) {
            (*(GObj**)0x16a1344)->sub_de52d0();
        }
    }
}

// ===========================================================================
//  0x00e005b0  open Sporepedia if in the right game mode
// ===========================================================================
// @ 0x00e005b0
void __cdecl e005b0() {
    char buf[0x48];
    sub_644b10(buf);
    if ((int)SP_GetCurrentGameMode() == 0x2ccd1d2) {
        int* p = (int*)operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
        if (p) {
            int* g = *(int**)0x16a1344;
            p[1] = 0x13ec458;
            p[2] = 0;
            p[0] = 0x147dc04;
            p[1] = 0x149bad8;
            p[3] = (int)g;
            *(u8*)(p + 4) = 0;
        }
        sub_e02040(buf);
    }
    sub_644b60(buf);
}

// ===========================================================================
//  0x00e00670  key dispatch (this + 2 args)
// ===========================================================================
struct KeyObj { char pad[0x44]; int key44(); void Dispatch(int, int); };
// @ 0x00e00670
void KeyObj::Dispatch(int param2, int param3) {
    KeyObj* self = this;
    if (param3 == 0) {
        if (param2 == 0x48) goto joined;
    } else {
        if (param3 != 1) goto after;
    }
joined:
    if (param2 != 0xbf) goto after;
    {
        void* sg = SP_SporeGuide();
        int* ms;
        int msg;
        if (*(char*)((char*)sg + 0x1c) == 0) { ms = (int*)SP_MessageServer(); msg = 0x5120263; }
        else                                  { ms = (int*)SP_MessageServer(); msg = 0x5b9ba6c; }
        ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, msg, 0, 0);
    }
after:
    if (param2 != 0x42 || param3 != 0) return;
    if (*(char*)(*(int**)0x16a1344 + 0xef) != 0) return;
    {
        int* mv = (int*)SP_MovieSystem();
        char c = ((char(__thiscall*)(void*))(*(void***)mv)[0x14 / 4])(mv);
        if (c) return;
    }
    if (*(int*)(*(char**)0x16a1344 + 0x1ec) == 1) return;
    {
        void* ab = SP_AssetBrowser();
        if (*(char*)((char*)ab + 0x1c) != 0) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x574f0a6, 0, 0);
            return;
        }
        if (self->key44()) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x5120264, 0, 0);
        }
    }
}

// ===========================================================================
//  0x00e000a0  resource-manager lookup
// ===========================================================================
// @ 0x00e000a0
void __cdecl e000a0_code(void* self, void* param) { (void)self; (void)param; }

// ===========================================================================
//  0x00e001a0  input dispatch
// ===========================================================================
// @ 0x00e001a0
void __cdecl e001a0_code(void* self, int* param) { (void)self; (void)param; }

// ===========================================================================
//  0x00e002b0  big key switch
// ===========================================================================
// @ 0x00e002b0
int __cdecl e002b0_code(void* self, int key, int* param) {
    (void)self; (void)key; (void)param; return 0;
}

// ===========================================================================
//  Stubs for the large inlined functions (partial)
// ===========================================================================
// @ 0x00dff790
void __fastcall dff790(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x00dff8e0
void __fastcall dff8e0(void* self, void* a) { (void)self; (void)a; }
// @ 0x00dffa30
void __fastcall dffa30(void* self, void* a) { (void)self; (void)a; }
// @ 0x00dffda0
void __fastcall dffda0(void* self) { (void)self; }
