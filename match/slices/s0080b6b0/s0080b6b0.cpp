// Slice s0080b6b0: cSPUILayoutObjectCollection / atlas-map vector helpers.
// The small vector-teardown and window-lookup helpers are byte-exact; the larger layout and
// scrolling routines are only partially reconstructed.
#include "types.h"

extern "C" void efree(void* p);

// ================= 0x0080b8a0: find/refresh a window from the layout
struct Layout {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    void* FindWindowByID(int id, int recurse);
};

struct Big3 {
    char pad[0x418];
    Layout* layout;      // +0x418
    char flag;           // +0x41c
    void* method(int a);
    void FUN_0080b4d0(int a);
    void FUN_0080b6b0();
    void FUN_0080b000();
};

// @ 0x0080b8a0
void* Big3::method(int a)
{
    if (layout != 0 && flag != 0) {
        void* w = layout->FindWindowByID(0x79830aa, 0);
        FUN_0080b4d0(a);
        FUN_0080b6b0();
        FUN_0080b000();
        return w;
    }
    return 0;
}

// ================= 0x0080b8f0: destroy a vector of 0x34-stride elements + free storage
struct E34 { virtual void Fn(int v); char pad[0x30]; };
// @ 0x0080b8f0
void __fastcall Vec34Dtor(int* v)
{
    E34* p = (E34*)v[0];
    E34* e = (E34*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// ================= 0x0080b930: same with 0x42c stride
struct E42C { virtual void Fn(int v); char pad[0x428]; };
// @ 0x0080b930
void __fastcall Vec42CDtor(int* v)
{
    E42C* p = (E42C*)v[0];
    E42C* e = (E42C*)v[1];
    for (; p < e; ++p)
        p->Fn(0);
    int d = v[0];
    if (d != 0 && d != v[4])
        efree((void*)d);
}

// ================= 0x0080ba10: initialise an inline-buffered container (complete, non-exact)
struct ObjB {
    void* vtbl;
    int f1, f2, f3, f4, f5, f6, f7;
};
extern char ObjB_vtable[];
ObjB* __fastcall ObjBCtor(ObjB* o)
{
    o->vtbl = (void*)ObjB_vtable;
    o->f1 = 0;
    o->f2 = 0;
    void* p = (char*)o + 0x24;
    o->f7 = (int)p;
    o->f4 = (int)p;
    o->f3 = (int)p;
    p = (char*)p + 0x5370;
    o->f5 = (int)p;
    return o;
}

// ================= 0x0080bcf0: vector erase (complete, non-exact)
struct RecC { virtual void Fn(int v); int w[10]; void* r; int tail; };
RecC* copyFwd(RecC* begin, RecC* end, RecC* dst);
struct Vec {
    RecC* begin;     // +0
    RecC* end;       // +4
    RecC* cap;       // +8
    int pad;         // +0xc
    RecC* inlineBuf; // +0x10
    RecC* erase(RecC* first, RecC* last);
};
// @ 0x0080bcf0
RecC* Vec::erase(RecC* first, RecC* last)
{
    RecC* newEnd = copyFwd(last, end, first);
    RecC* e = end;
    for (RecC* p = newEnd; p < e; ++p)
        p->Fn(0);
    end = end + (last - first);
    return first;
}

// ================= remaining (partial)
// @ 0x0080b6b0
void FUN_0080b6b0() { /* layout refresh; not reconstructed */ }
// @ 0x0080b9b0
void FUN_0080b9b0() { /* deleting destructor with an inline vector member; not reconstructed */ }
// @ 0x0080baa0
void FUN_0080baa0() { /* not reconstructed */ }
// @ 0x0080bbe0
void FUN_0080bbe0() { /* not reconstructed */ }
// @ 0x0080bd50
void FUN_0080bd50() { /* scroll/layout update; not reconstructed */ }
// @ 0x0080bfb0
void FUN_0080bfb0() { /* large scroll/layout routine; not reconstructed */ }
// @ 0x0080c520
void FUN_0080c520() { /* modal scroll dispatch; not reconstructed */ }
