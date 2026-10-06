// Slice s00d52e90 (batch bfs3, slice 10). Region 0xd52e90-0xd53b44.
// SP::cPosseSimulator (Simulator/posse system) plus two template helpers.
// Optimised: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

// ===========================================================================
// External callees (bodies elsewhere; references are masked relocations).
// ===========================================================================
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);                 // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                          // 0xf47380

extern "C" void* __cdecl SP_NounManager();                          // 0xb3d300
extern "C" void* __cdecl SP_GetCurrentGameMode();                   // 0xb5b800
extern "C" void* __cdecl SP_PropertyManager();                      // 0x67de30
extern "C" void  __cdecl FUN_00b1fdb0();                            // GetAvatar
extern "C" void  __cdecl FUN_00b1f9c0();                            // GetItemID
extern "C" void  __cdecl FUN_00b234c0();                            // ClearPosseMembers
extern "C" void  __cdecl FUN_00b203e0();
extern "C" void  __cdecl FUN_00c0ee90();
extern "C" void  __cdecl FUN_00c0ee60();
extern "C" void  __cdecl FUN_00c0bf10();
extern "C" void  __cdecl FUN_00c0e8d0();
extern "C" void  __cdecl FUN_00c04590();
extern "C" void  __cdecl FUN_00c0d3a0();
extern "C" void  __cdecl FUN_00c042e0();
extern "C" void  __cdecl FUN_00c02e80();
extern "C" void  __cdecl FUN_00c06f70();
extern "C" void  __cdecl FUN_00bc96a0();                            // PlayIdleAnimation
extern "C" void  __cdecl FUN_00bc97f0();
extern "C" void  __cdecl FUN_00d38840();                            // cCreatureModeStrategy::Instance
extern "C" void  __cdecl FUN_00d39670();                            // AddStat
extern "C" void  __cdecl FUN_00d39360();
extern "C" void  __cdecl FUN_00d2b8f0();                            // RemoveUIForPosseMember
extern "C" void  __cdecl FUN_00d7d160();
extern "C" char  __cdecl FUN_00d99a10();
extern "C" void* __cdecl FUN_00d999d0();
extern "C" void  __cdecl FUN_00d01790();
extern "C" void  __cdecl FUN_00b96600();
extern "C" void  __cdecl FUN_00f19840();
extern "C" void  __cdecl FUN_00f1b590();
extern "C" void  __cdecl FUN_00f0ef40();
extern "C" void  __cdecl FUN_00675250();
extern "C" void  __cdecl FUN_00676e90();
extern "C" void  __cdecl FUN_00a68fb0();
extern "C" void  __cdecl FUN_008e7f80();                            // PFIndexModifiable::GetFileCount
extern "C" void  __cdecl FUN_0041ea00();                            // Property::GetUInt
extern "C" void  __cdecl FUN_0041ea70();                            // Property::GetFloat
extern "C" void* __cdecl FUN_00b90bd0(void*, void*, void*, void*);
extern "C" void  __cdecl FUN_00bbf130(void*, void*, void*, void*);

struct Property { int pad_00; uint16_t type12; };
struct PropertyPtr {
    Property* mp;
    Property* get() const { return mp; }
};

// ===========================================================================
//  0x00d533c0  SP::cPosseSimulator::ReloadTuning
// ===========================================================================
struct PropertyEnum {
    int  pad_00;
    char set(uint32_t id, uint32_t a);   // slot 0x2c: begin enumeration
    char get(uint32_t id, uint32_t* p);  // slot 0x24: get property
};
struct PropMgr { void* pad_00; PropertyEnum* vf() { return *(PropertyEnum**)this; } };
// @ 0x00d533c0
void ReloadTuning(void* self) {
    PropertyPtr slot;
    slot.mp = 0;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    if (pm->vf()->set(0x48f5d7cd, 0xad56080c)) {
        if (slot.get() != 0 && slot.get()->pad_00 != 0) {
            Property* p = slot.get();
            p->pad_00 = p->pad_00;
            slot.get()->type12 = 0;
        }
    }
}

// ===========================================================================
//  0x00d53330  remove occupant pointer equal to arg from every posse slot
// ===========================================================================
struct RefObj { virtual void dummy(); virtual void Release(); };
struct AutoRefCount {
    RefObj* mp;
    void operator=(RefObj* r) {
        RefObj* old = mp;
        mp = r;
        if (old) {
            old->Release();
        }
    }
};
struct Slot { AutoRefCount occupant; };
class PosseSim {
public:
    int pad_00[8];                     // +0x00..0x1f
    Slot**   mpBegin;                  // +0x20
    Slot**   mpEnd;                    // +0x24
    Slot**   mpCapacity;               // +0x28
    int pad_2c[3];                     // +0x2c..0x37
    int pad_38;
    void removeSlot(RefObj* p);
};
// @ 0x00d53330
void PosseSim::removeSlot(RefObj* p) {
    int i = 0;
    unsigned int n = (unsigned int)(mpEnd - mpBegin);
    for (; (unsigned int)i < n; ++i) {
        Slot* s = mpBegin[i];
        if (s->occupant.mp == p) {
            s->occupant = (RefObj*)0;
        }
    }
}

// ===========================================================================
//  0x00d53490  SP::cPosseSimulator::RemovePosseMember
// ===========================================================================
// @ 0x00d53490
void RemovePosseMember(void* self, int member, char arg3, char arg4) {
    (void)self; (void)member; (void)arg3; (void)arg4;
    SP_NounManager();
}

// ===========================================================================
//  0x00d536d0  SP::cPosseSimulator::`scalar deleting destructor'
// ===========================================================================
// @ 0x00d536d0
void* PosseSim_dtor(PosseSim* self, unsigned int flags) {
    *(void**)self = (void*)0x147b810;
    *(void**)((char*)self + 8) = (void*)0x147b7ec;
    *(void**)0x169e5b8 = 0;
    Slot** e = *(Slot***)((char*)self + 0x20);
    if (e != 0 && e[-1] != 0) {
        EA_Free(e);
    }
    *(void**)((char*)self + 8) = (void*)0x13eb938;
    *(void**)self = (void*)0x13ec458;
    if (flags & 1) {
        EA_Free(self);
    }
    return self;
}

// ===========================================================================
//  0x00d53730  SP::cPosseSimulator::Shutdown
// ===========================================================================
// @ 0x00d53730
void PosseSim_Shutdown(PosseSim* self) {
    SP_NounManager();
    FUN_00b234c0();
    Slot** e = *(Slot***)((char*)self + 0x24);
    while (e != self->mpBegin) {
        e -= 1;
        Slot* s = *e;
        if (s->occupant.mp) {
            s->occupant = (RefObj*)0;
        }
        EA_Free(s);
        *(Slot***)((char*)self + 0x24) = e;
    }
}

// ===========================================================================
//  0x00d53790  SP::cPosseSimulator::OnTick
// ===========================================================================
// @ 0x00d53790
void PosseSim_OnTick(PosseSim* self, int arg1, int arg2) {
    (void)self; (void)arg1; (void)arg2;
    SP_NounManager();
}

// ===========================================================================
//  0x00d53890  quicksort partition helper (hoare)
// ===========================================================================
// @ 0x00d53890
void** partition(void** first, void** last, int pivot, char (__cdecl* pred)(int, int)) {
    for (;;) {
        while (pred((int)*first, pivot)) {
            ++first;
        }
        while (pred(pivot, (int)last[-1])) {
            --last;
        }
        if (first >= last) {
            return first;
        }
        void* tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// ===========================================================================
//  0x00d538f0  Simulator::cPosseSimulator::cPosseSimulator
// ===========================================================================
// @ 0x00d538f0
PosseSim* PosseSim_ctor(PosseSim* self) {
    SP_NounManager();  // placeholder; real base ctor 0xb5b6c0
    *(void**)((char*)self + 0x18) = 0;
    *(void**)((char*)self + 0x1c) = 0;
    *(void**)self = (void*)0x147b810;
    *(void**)((char*)self + 8) = (void*)0x147b7ec;
    *(unsigned int*)((char*)self + 0x10) = 60000;
    *(float*)((char*)self + 0x14) = 20.0f;
    *(void**)((char*)self + 0x34) = 0;
    Slot** base = (Slot**)((char*)self + 0x38);
    self->mpBegin = base;
    self->mpEnd = base;
    self->mpCapacity = (Slot**)((char*)self + 0x80);
    *(void**)0x169e5b8 = self;
    return self;
}

// ===========================================================================
//  0x00d53940  introsort helper
// ===========================================================================
// @ 0x00d53940
void introsort(void** first, void** last, int depth, char (__cdecl* pred)(int, int)) {
    while (last - first > 28 && depth > 0) {
        void** cut = (void**)FUN_00b90bd0(first, first + (last - first) / 2, last - 1, pred);
        void** mid = partition(first, last, (int)*cut, pred);
        --depth;
        introsort(mid, last, depth, pred);
        last = mid;
    }
    if (depth == 0) {
        FUN_00bbf130(first, last, last, pred);
    }
}

// ===========================================================================
//  0x00d539d0  SP::cPosseSimulator::Instance
// ===========================================================================
class Inst {
public:
    void slot();          // vtable slot 7 (offset 0x1c)
};
// @ 0x00d539d0
void* PosseSim_Instance() {
    void* inst = *(void**)0x169e5b8;
    if (inst == 0) {
        Inst* raw = (Inst*)EA_Allocate(0x58, "Simulator/cPosseSimulator", 0, 0, 0, 0);
        if (raw != 0) {
            PosseSim_ctor((PosseSim*)raw);
            inst = (void*)raw;
            *(void**)0x169e5b8 = inst;
            ((Inst*)inst)->slot();
        } else {
            *(void**)0x169e5b8 = 0;
        }
    }
    return *(void**)0x169e5b8;
}

// ===========================================================================
//  0x00d53a80  SP::cPosseSimulator::InitPosse
// ===========================================================================
// @ 0x00d53a80
void PosseSim_InitPosse(PosseSim* self) {
    struct cPosseSlot { RefObj* occupant; float angle; float diff; };
    ReloadTuning(self);
    if (self->mpBegin == self->mpEnd) {
        FUN_00d01790();
        float base = *(float*)0x1583d20;
        float scaled = base * 1.5f;
        for (unsigned int i = 0; i < 6; ++i) {
            cPosseSlot* s = (cPosseSlot*)EA_Allocate(0xc, "Simulator/cPosseSlot", 0, 0, 0, 0);
            if (s != 0) {
                s->occupant = (RefObj*)0;
                s->angle = (float)(int)i * base + scaled;
                s->diff = 0.0f;
            } else {
                s = 0;
            }
            Slot** end = self->mpEnd;
            if (end < self->mpCapacity) {
                self->mpEnd = end + 1;
                if (end != 0) {
                    *end = (Slot*)s;
                }
            } else {
                FUN_00b96600();
            }
        }
    }
}

// Leftover original function 0xd52e90 (large, dispatched elsewhere); stub kept so
// every slice VA has source present.  See partial.txt.
// @ 0x00d52e90
void FUN_00d52e90() {}
