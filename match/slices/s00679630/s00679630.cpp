// Slice s00679630 - property-UI element/container (SP::cPropertyUI) and
// SP::Achievements::Controller::Shutdown.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

struct VObj { void** vt; };
typedef void   (__thiscall *FnV1)(void*);
typedef void   (__thiscall *FnV3pii)(void*, void*, int, int);
void DeleteObj(void* p);              // 0x00f47380
void* __cdecl OperatorNew(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void* __cdecl MessageServer();        // 0x0067dcc0
void  __fastcall FUN_00929c60(char* p);
void  __fastcall FUN_00816990(char* p);
void  __fastcall FUN_00678f70(char* p);   // = 0x00678f70 (matched in s006783c0)

struct Elem {
    char data[0x134];
    void CopyFrom(Elem* other);   // 0x00679b40 (defined elsewhere)
    void AssignFrom(Elem* other); // 0x00679c90 (defined elsewhere)
};

struct Container {
    void Push(Elem* other);    // 0x00679ff0
    void Process(Elem* local); // 0x00679e50 (defined elsewhere)
    void Shutdown();           // 0x0067a090
};
struct Grow { void GrowVec(int a, int b); };       // 0x006780a0

// ---- 0x00679630 : cPropertyUI::ModifyBool (partial skeleton) ---------
struct PropertyUI { char ModifyBool(char* a); };
// @ 0x00679630
char PropertyUI::ModifyBool(char* a) { (void)a; return 0; }

// ---- 0x00679b40 : Elem copy-construct (partial skeleton) -------------
// @ 0x00679b40
void Elem_CopyFromSkeleton(Elem* self, Elem* other) { (void)self; (void)other; }

// ---- 0x00679c90 : Elem assign (partial skeleton) ---------------------
// @ 0x00679c90
void Elem_AssignFromSkeleton(Elem* self, Elem* other) { (void)self; (void)other; }

// ---- 0x00679e50 : container reset (partial skeleton) -----------------
// @ 0x00679e50
void Container_ProcessSkeleton(Container* self, Elem* local) { (void)self; (void)local; }

// ---- 0x0067a090 : SP::Achievements::Controller::Shutdown -------------
// @ 0x0067a090
void Container::Shutdown() {
    char* thisp = (char*)this;
    void* set = thisp ? thisp + 0xc : 0;
    void* srv = MessageServer();
    ((FnV3pii)((VObj*)srv)->vt[0x2c / 4])(srv, set, 0x670eccd, -0x270f);
    FUN_00929c60(thisp + 0x1b4);
    FUN_00929c60(thisp + 0x1d8);
    FUN_00929c60(thisp + 0x1fc);
    int e = *(int*)(thisp + 0x18);
    if (e != *(int*)(thisp + 0x28)) {
        Elem local;
        local.CopyFrom((Elem*)e);
        char* lp = (char*)&local;
        if (*(void**)(lp + 0xac)) FUN_00816990(*(char**)(lp + 0xac));
        FUN_00678f70(lp);
    }
}

// ---- 0x00679ff0 : container push (copies into a new block slot) ------
// @ 0x00679ff0
void Container::Push(Elem* other) {
    char* thisp = (char*)this;
    Elem local;
    local.CopyFrom(other);
    int n = (*(int*)(thisp + 0x24) - *(int*)thisp) >> 2;
    if (n + 1 >= *(int*)(thisp + 4))
        ((Grow*)thisp)->GrowVec(1, 1);
    void* p = OperatorNew(0x4d0, "Editor", 0, 0, "allocator.h", 0xd1);
    *(void**)(*(int*)(thisp + 0x24) + 4) = p;
    if (*(int*)(thisp + 0x18) != 0)
        (*(Elem**)(thisp + 0x18))->CopyFrom(&local);
    int q = *(int*)(thisp + 0x24);
    *(int*)(thisp + 0x24) = q + 4;
    int v = *(int*)(q + 4);
    *(int*)(thisp + 0x1c) = v;
    *(int*)(thisp + 0x20) = v + 0x4d0;
    *(int*)(thisp + 0x18) = *(int*)(thisp + 0x1c);
    FUN_00678f70((char*)&local);
}

// ---- 0x0067a120 : destroy every element ------------------------------
// @ 0x0067a120
void __fastcall FUN_0067a120(char* p) {
    if (*(int*)(p + 0x18) == *(int*)(p + 0x28)) return;
    do {
        Elem local;
        char* elem = *(char**)(p + 0x18);
        local.CopyFrom((Elem*)elem);
        int n = (int)elem + 0x134;
        if (n == *(int*)(p + 0x20)) {
            FUN_00678f70(elem);
            if (*(int*)(p + 0x1c)) DeleteObj(*(void**)(p + 0x1c));
            int* q = (int*)(*(int*)(p + 0x24) + 4);
            *(int**)(p + 0x24) = q;
            int v = *q;
            *(int*)(p + 0x1c) = v;
            *(int*)(p + 0x20) = v + 0x4d0;
            *(int*)(p + 0x18) = *(int*)(p + 0x1c);
        } else {
            *(int*)(p + 0x18) = n;
            FUN_00678f70(elem);
        }
        ((Container*)p)->Process(&local);
        FUN_00678f70((char*)&local);
    } while (*(int*)(p + 0x18) != *(int*)(p + 0x28));
}

// ---- 0x0067a1b0 : property UI update (partial skeleton) --------------
struct PropUI2 { char Update(char* a); };
// @ 0x0067a1b0
char PropUI2::Update(char* a) { (void)a; return 0; }
