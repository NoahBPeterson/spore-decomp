// Slice s00b6f4f0: mission-manager helpers -- ARC vector copy/filter, per-object notifications,
// mission-card panel refresh, spin/hash lookups, and vtable walks.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;

void* __cdecl opnew(unsigned size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  __cdecl opdel(void* p);                                                                     // 0x00f47380
#define ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define SPORE_NEW(n) opnew((n), "Simulator", 0, 0, ALLOC_FILE, 0xd1)

// reference-counted interface
struct IRefLite {
    virtual int  AddRef();                 // 0x00
    virtual int  Release();                // 0x04
    virtual void g2();                     // 0x08
    virtual void* Cast(unsigned id);       // 0x0c
    virtual void g4(); virtual void g5();  // 0x10,0x14
    virtual void g6();                     // 0x18
    virtual void Notify(unsigned a);       // 0x1c
    virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
    virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
    virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
    virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
    virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31();
    virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
    virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39();
    virtual void f40(); virtual void f41(); virtual void f42(); virtual void f43();
    virtual void f44(); virtual void f45();
    virtual void NotifyB8();               // 0xb8
};

struct ARCObj { IRefLite* p; };

// @ 0x00b6f4f0
ARCObj* __cdecl FUN_00b6f4f0(ARCObj* first, ARCObj* last, ARCObj* dest, IRefLite** skip)
{
    for (; first != last; ++first) {
        IRefLite* p = first->p;
        if (p != *skip) {
            IRefLite* old = dest->p;
            if (p != old) {
                if (p) p->AddRef();
                dest->p = p;
                if (old) old->Release();
            }
            dest++;
        }
    }
    return dest;
}

// @ 0x00b6f550
bool __cdecl FUN_00b6f550(unsigned a, IRefLite** p)
{
    if (*p) (*p)->Notify(a);
    return true;
}

// @ 0x00b6f7d0
struct MMgr {
    void NotifyAll();               // 0x00b6f7d0
    bool IsTracked(void* p);        // 0x00b6f800
    void ClearCard(void* p);        // 0x00b6f820
};
// @ 0x00b6f7d0
void __thiscall MMgr::NotifyAll()
{
    IRefLite** end = *(IRefLite***)((char*)this + 0x18);
    for (IRefLite** p = *(IRefLite***)((char*)this + 0x14); p != end; p++)
        (*p)->NotifyB8();
}

// @ 0x00b6f800
bool __thiscall MMgr::IsTracked(void* p)
{
    if (p == *(void**)((char*)this + 0x68)) return true;
    return p == *(void**)((char*)this + 0x6c);
}

// @ 0x00b6f820
extern void* __cdecl FUN_00b3d400();
struct CardPanel { void RemoveMissionCard(void* card); };   // 0x00e17fb0 (thiscall)
void __thiscall MMgr::ClearCard(void* p)
{
    if (p == *(void**)((char*)this + 0x68)) {
        if (FUN_00b3d400()) {
            ((CardPanel*)FUN_00b3d400())->RemoveMissionCard(*(void**)((char*)this + 0x68));
        }
        IRefLite* c = *(IRefLite**)((char*)this + 0x68);
        if (c) {
            *(void**)((char*)this + 0x68) = 0;
            c->Release();
        }
    }
}

// @ 0x00b6f860
bool __cdecl FUN_00b6f860(unsigned a, ARCObj** vec)
{
    ARCObj* last = vec[1];
    for (ARCObj* p = vec[0]; p != last; p++)
        if (p->p) p->p->Notify(a);
    return true;
}

// @ 0x00b6f890
struct SmallC {
    void* p0;
    IRefLite* p4;
    int   p8;
    static SmallC* __stdcall Create(SmallC* src);   // 0x00b6f890
};
// @ 0x00b6f890
SmallC* __stdcall SmallC::Create(SmallC* src)
{
    SmallC* p = (SmallC*)SPORE_NEW(0xc);
    if (p) {
        p->p0 = src->p0;
        p->p4 = src->p4;
        if (p->p4) p->p4->AddRef();
    }
    p->p8 = 0;
    return p;
}

// @ 0x00b6f8e0
struct SmallE {
    void* p0; void* p4; void* p8; IRefLite* pC; int p10;
};
// @ 0x00b6f8e0
SmallE* __stdcall FUN_00b6f8e0(SmallE* src)
{
    SmallE* p = (SmallE*)SPORE_NEW(0x14);
    if (p) {
        p->p0 = src->p0;
        p->p4 = src->p4;
        p->p8 = src->p8;
        p->pC = src->pC;
        if (p->pC) p->pC->AddRef();
    }
    p->p10 = 0;
    return p;
}

// ------------------------------------------------------------------ remaining (partial / complete-best-effort)
struct Mgr {
    void Write(void* ser);                 // 0x00b6f570
    void RefreshAll();                     // 0x00b6f650
    void RefreshCards();                   // 0x00b6f760
    void* LookupA(unsigned key);           // 0x00b6fa60
    int   EraseMission(unsigned* key);     // 0x00b6faa0
    void* LookupB(unsigned key);           // 0x00b6ff20
};
// @ 0x00b6f570
void __thiscall Mgr::Write(void* ser) { (void)ser; }
// @ 0x00b6f650
void __thiscall Mgr::RefreshAll() {}
// @ 0x00b6f760
void __thiscall Mgr::RefreshCards() {}
// @ 0x00b6fa60
void* __thiscall Mgr::LookupA(unsigned key) { (void)key; return 0; }
// @ 0x00b6faa0
int __thiscall Mgr::EraseMission(unsigned* key) { (void)key; return 0; }
// @ 0x00b6ff20
void* __thiscall Mgr::LookupB(unsigned key) { (void)key; return 0; }
// @ 0x00b6fb20
void __cdecl FUN_00b6fb20(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b6fc90
void __cdecl FUN_00b6fc90(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b6fd80
bool __cdecl FUN_00b6fd80(unsigned a, void* b) { (void)a; (void)b; return true; }
// @ 0x00b6ffa0
void __cdecl FUN_00b6ffa0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b70070
void __cdecl FUN_00b70070(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b700f0
void __cdecl FUN_00b700f0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b70290
void __cdecl FUN_00b70290(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b70410
void __cdecl FUN_00b70410(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b705a0
void __cdecl FUN_00b705a0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b706a0
void __cdecl FUN_00b706a0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00b707a0
void __cdecl FUN_00b707a0(void* a, void* b) { (void)a; (void)b; }
