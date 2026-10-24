// Gold batch "gold1" slice s00a21130 — 32 functions.
// Complete, compilable reconstruction. Byte-exact functions are listed in manifest.txt;
// behaviourally complete but non-byte-exact functions are listed in nonmatching.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// ---------------------------------------------------------------------------------------
// External callees (address-labelled).
// ---------------------------------------------------------------------------------------
extern void* f_00a158d0(void);
extern void* f_00a151c0(void);
extern void* f_00a149a0(void);
extern void* f_00a161b0(void);
extern void* f_00a15d30(void);
extern void* f_00a14800(void);
extern void  f_00f47380(void* p);
extern void* f_00f473a0(unsigned size, void* name, void* a3, void* a4, void* file, unsigned line);

// Thiscall callees (receiver in ECX), modeled as members of stub classes.
struct Callee_Th {
    void* m_0112ce00(); void m_0112dca0(); void m_0112cd60(void* v); void* m_0112dc80(); void m_0112dbd0();
    void* m_00a34230(unsigned tag); void m_00a34890(); void m_0112c600(); void m_0112c620();
    void m_0112ccc0(int a, void* b);
};
#define TH(p) ((Callee_Th*)(p))

// ---------------------------------------------------------------------------------------
// Dispatch helper: VPTR(ret, obj, slot, argtypes...)(obj, args...)
// ---------------------------------------------------------------------------------------
#define VPTR(ret, obj, slot, ...) \
    ((ret (__thiscall*)(void*, __VA_ARGS__))((void**)*(void**)obj)[(slot) / 4])

// Property-sink interface implemented by the object under +4 of a message target:
//   slot 0x38: Begin(name)
//   slot 0x3c: SetFloat(name, value)
//   slot 0x40: SetInt(name, value)
//   slot 0x44: SetInt2(name, value, flag)
//   slot 0x48: SetBool(name, value)
//   slot 0x4c: SetIntPtrs(name, a, b)
//   slot 0x58: End()
struct PropSink {
    // +0 vtable pointer
    void*  vt;          // 0x00
    // ... payload ...
};

// Stub receiver classes: the originals take `this` in ECX (thiscall members).
struct AudioSystem_00a21170 { void RegisterBuiltInModules(); };
struct Submix_00a21390 { bool DisconnectFromSubmix(); };
struct VoiceContainer { bool Connect(int a1, int a2); bool Connect4(int a1, int a2, int a3, int a4); };
struct MsgTarget_00a21630 { bool Handle(int a1, int a2); };
struct VoiceVec_00a21c00 { void Destroy(); };
struct RbTree_00a21dc0 { void* Find(void** out, void* key); };
struct HashA_00a21eb0 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct HashB_00a22060 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct HashC_00a22110 { void Rehash(unsigned a); void* Alloc(unsigned n); };
struct AudioSys_00a21a80 { void* FindVoice(unsigned tag); };
struct AudioSys_00a21b20 { bool Command(int a1, int a2, int a3, int a4, int a5); };
struct AudioSys_00a21b90 { bool Command4(int a1, int a2, int a3, int a4, int a5); };
struct MsgSystem_00a21710 { bool HandleMessage(unsigned msg, void* info); };

// ---------------------------------------------------------------------------------------
// 0x00A21130  EA::Audio message predicate (41-plot / voice tags)
// ---------------------------------------------------------------------------------------
// @ 0x00A21130
int __stdcall isVoiceShareMsg_00a21130(void* msg) {
    unsigned* m = (unsigned*)msg;
    if (m[2] == 0x21407ee) {
        unsigned v = m[1];
        if (v == 0x1a527db || v == 0x1eef63a || v == 0x42c9cbb || v == 0x3055f61)
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------
// 0x00A21170  EA::Audio::System::RegisterBuiltInModules
// ---------------------------------------------------------------------------------------
// @ 0x00A21170
void AudioSystem_00a21170::RegisterBuiltInModules() {
    void* self = this;
    void* sys = TH(*(void**)((char*)self + 0xa4))->m_0112ce00();
    if (sys != 0) {
        TH(sys)->m_0112dca0();
        TH(sys)->m_0112cd60((void*)f_00a158d0());
        TH(sys)->m_0112cd60((void*)f_00a151c0());
        TH(sys)->m_0112cd60((void*)f_00a149a0());
        TH(sys)->m_0112cd60((void*)f_00a161b0());
        TH(sys)->m_0112cd60((void*)f_00a15d30());
        TH(sys)->m_0112cd60((void*)f_00a14800());
    }
    void* reg = TH(*(void**)((char*)self + 0xa4))->m_0112dc80();
    if (reg != 0)
        TH(reg)->m_0112dbd0();
}

// ---------------------------------------------------------------------------------------
// 0x00A21200  EA::Audio message predicate (0x2c9eff2)
// ---------------------------------------------------------------------------------------
// @ 0x00A21200
bool __stdcall isMsg00a21200(void* msg) {
    return *(unsigned*)((char*)msg + 4) == 0x2c9eff2;
}

// ---------------------------------------------------------------------------------------
// 0x00A21220  EA::Audio::SystemAccess::GlobalTime (double) + trailing 0x2b9f662 predicate
// ---------------------------------------------------------------------------------------
// @ 0x00A21220
double globalTime_00a21220() {
    void* p = *(void**)0x16e61a8;
    if (p != 0) return *(double*)((char*)p + 8);
    return 0.0;
}

// @ 0x00A21230
bool isMsg00a21230(void* msg) {
    unsigned* m = (unsigned*)msg;
    if (m[2] != 0x21407ee) return false;
    return m[1] == 0x2b9f662;
}

// ---------------------------------------------------------------------------------------
// 0x00A21260  AutoRefCount::Release (refcount -> -1, then virtual Delete(1))
// ---------------------------------------------------------------------------------------
// @ 0x00A21260
void __fastcall release_00a21260(void* self) {
    int* rc = *(int**)((char*)self + 4);
    if (rc == 0) return;
    int n = rc[1] - 1;
    rc[1] = n;
    if (n == 0) {
        rc[1] = 1;
        void* vt = *(void**)rc;
        ((void (__thiscall*)(void*, int))((void**)vt)[0])(rc, 1);
    }
}

// ---------------------------------------------------------------------------------------
// 0x00A21290  intrusive-list head reset to prev(-0x10) or null
// ---------------------------------------------------------------------------------------
// @ 0x00A21290
// The original keeps its receiver (ECX) in EAX and returns it; caller 0x00A2E650 reads EAX.
void** __fastcall resetHead_00a21290(void** self) {
    char* v = (char*)*self;
    v = *(char**)(v + 0x10);
    if (v != 0) { *self = v - 0x10; return self; }
    *self = 0;
    return self;
}

// ---------------------------------------------------------------------------------------
// 0x00A212B0  eastl list splice helper
// ---------------------------------------------------------------------------------------
// @ 0x00A212B0
void __stdcall splice_00a212b0(void* a1, void* dummy, void* pos, void* last) {
    if (pos == last) return;
    char* p1 = (char*)a1;
    char* p3 = (char*)pos;
    char* p4 = (char*)last;
    unsigned v = *(unsigned*)(p4 + 0x14);
    char* q = (v != 0) ? (char*)(v - 0x10) : (char*)0;
    char* piVar1 = q + 0x10;
    unsigned esi = *(unsigned*)(p3 + 0x14);
    char* ecx = p3 + 0x14;
    *(unsigned*)(*(unsigned*)piVar1 + 4) = esi;
    *(unsigned*)*(unsigned*)ecx = *(unsigned*)piVar1;
    unsigned v2 = *(unsigned*)(p1 + 0x14);
    char* iVar2 = (v2 != 0) ? (char*)(v2 - 0x10) : (char*)0;
    *(unsigned*)(iVar2 + 0x10) = (unsigned)(p3 + 0x10);
    *(unsigned*)ecx = (unsigned)(iVar2 + 0x10);
    *(unsigned*)piVar1 = (unsigned)(p1 + 0x10);
    *(unsigned*)(p1 + 0x14) = (unsigned)piVar1;
}

// ---------------------------------------------------------------------------------------
// 0x00A21310  eastl list erase helper
// ---------------------------------------------------------------------------------------
// @ 0x00A21310
void __stdcall erase_00a21310(void* a1, void* holder) {
    char* eax_p = (char*)holder;
    unsigned edx = *(unsigned*)eax_p;
    if (edx == (unsigned)holder) return;
    char* ecx_p = (char*)a1;
    char* ebx_p = (char*)(ecx_p + 0x14);
    unsigned c = *(unsigned*)ebx_p;
    char* ebp_p = (c != 0) ? (char*)(c - 0x10) : (char*)0;
    char* esi_0 = (edx != 0) ? (char*)(edx - 0x10) : (char*)0;
    unsigned c2 = *(unsigned*)(eax_p + 4);
    char* edi_p = (c2 != 0) ? (char*)(c2 - 0x10) : (char*)0;
    char* edx2 = (esi_0 != 0) ? (char*)(esi_0 + 0x10) : (char*)0;
    *(unsigned*)(ebp_p + 0x10) = (unsigned)edx2;
    unsigned edx3 = (unsigned)a1;
    char* ecx2 = (char*)(ebp_p + 0x10);
    *(unsigned*)(esi_0 + 0x14) = (unsigned)ecx2;
    char* ecx3 = (char*)(edi_p + 0x10);
    edx3 += 0x10;
    *(unsigned*)ecx3 = edx3;
    *(unsigned*)ebx_p = (unsigned)ecx3;
    *(unsigned*)eax_p = (unsigned)eax_p;
    *(unsigned*)(eax_p + 4) = (unsigned)eax_p;
}

// ---------------------------------------------------------------------------------------
// 0x00A21390  EA::Audio::Submix::DisconnectFromSubmix
// ---------------------------------------------------------------------------------------
// @ 0x00A21390
bool Submix_00a21390::DisconnectFromSubmix() {
    void* self = this;
    void* m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c600();
    void* esi = (char*)self + 0x10;
    void* p = TH(esi)->m_00a34230(0x41695730);
    if (p != 0)
        TH(p)->m_0112ccc0(1, 0);
    TH(esi)->m_00a34890();
    m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c620();
    return true;
}

// ---------------------------------------------------------------------------------------
// 0x00A21410  EA::Audio::VoiceContainer::Connect
// ---------------------------------------------------------------------------------------
// @ 0x00A21410
bool VoiceContainer::Connect(int a1, int a2) {
    char* self = (char*)this;
    void* p = TH(self + 0x10)->m_00a34230(0x53747030);
    if (p == 0) return false;
    void* m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c600();
    char buf[8];
    *(int*)(buf + 0) = a1;
    *(int*)(buf + 4) = a2;
    TH(p)->m_0112ccc0(2, buf);
    m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c620();
    return true;
}

// ---------------------------------------------------------------------------------------
// 0x00A214B0  EA::Audio::VoiceContainer::Connect4
// ---------------------------------------------------------------------------------------
// @ 0x00A214B0
bool VoiceContainer::Connect4(int a1, int a2, int a3, int a4) {
    char* self = (char*)this;
    char cached = (*(int*)(self + 0x15f4) != 0);
    if (!cached)
        *(void**)(self + 0x15f4) = TH(self + 0x10)->m_00a34230(0x53747030);
    if (*(int*)(self + 0x15f4) == 0) return false;
    void* m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c600();
    if (!cached) {
        char buf[16];
        *(int*)(buf + 0)  = a1;
        *(int*)(buf + 4)  = a2;
        *(int*)(buf + 8)  = a3;
        *(int*)(buf + 12) = a4;
        TH(*(void**)(self + 0x15f4))->m_0112ccc0(0, buf);
    }
    m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c620();
    return true;
}

// ---------------------------------------------------------------------------------------
// 0x00A21590  EA::Audio::VoiceContainer::Disconnect
// ---------------------------------------------------------------------------------------
__declspec(noinline) void __fastcall disconnect_00a21590(char* self);
// @ 0x00A21590
void __fastcall disconnect_00a21590(char* self) {
    if (*(int*)(self + 0x15f4) == 0) return;
    void* m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c600();
    TH(*(void**)(self + 0x15f4))->m_0112ccc0(1, 0);
    *(void**)(self + 0x15f4) = 0;
    m = *(void**)0x16e61a8;
    if (m != 0) TH(m)->m_0112c620();
}

// ---------------------------------------------------------------------------------------
// 0x00A21630  EA::Audio message handler (vtable factory + dispatch)
// ---------------------------------------------------------------------------------------
// @ 0x00A21630
bool MsgTarget_00a21630::Handle(int a1, int a2) {
    void* self = this;
    void* eax = *(void**)((char*)*(void**)self + 0x1d4);
    void* p = ((void* (__thiscall*)(void*, int))eax)(self, a1);
    void* esi = p;
    if (esi != 0)
        VPTR(void, esi, 0)(esi);
    if (esi == 0) return false;
    VPTR(void, esi, 0x18, int, int)(esi, 2, a2);
    VPTR(void, esi, 4)(esi);
    return true;
}

// ---------------------------------------------------------------------------------------
// 0x00A216D0  three-outparam component getter
// ---------------------------------------------------------------------------------------
// @ 0x00A216D0
void __fastcall get3_00a216d0(char* self, void* dummy, int* a, int* b, int* c) {
    if (a != 0) *a = *(int*)(self + 0x200);
    if (b != 0) *b = *(int*)(self + 0x15bb7c);
    if (c != 0) *c = (*(int*)(self + 0x15bb80) - *(int*)(self + 0x15bb7c)) >> 2;
}

// ---------------------------------------------------------------------------------------
// 0x00A21710  EA::Audio::System::HandleMessage (big property dispatch)
// ---------------------------------------------------------------------------------------
// @ 0x00A21710
bool MsgSystem_00a21710::HandleMessage(unsigned msg, void* info) {
    char* self = (char*)this;
    char* esi = self - 4;
    void* vt;
    char* edi;

    switch (msg) {
    case 0xff0f31:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475373);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475391, *(float*)(edi + 0x10));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475395, *(float*)(edi + 0x18));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475398, *(float*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0xff0ed1:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475365);
        edi = (char*)info;
        if (*(unsigned*)(edi + 0x88) & 1)
            VPTR(void, esi, 0x44, unsigned, int, int)(esi, 0x347537e, *(int*)(edi + 8), 0);
        if ((*(unsigned*)(edi + 0x88) >> 1) & 1)
            VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475381, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 0x18));
        if ((*(unsigned*)(edi + 0x88) >> 8) & 1)
            VPTR(void, esi, 0x48, unsigned, int)(esi, 0x347539c, *(int*)(edi + 0x48));
        if (((*(unsigned*)(edi + 0x88) >> 5) & 1) && ((*(unsigned*)(edi + 0x88) >> 6) & 1)
            && ((*(unsigned*)(edi + 0x88) >> 7) & 1)) {
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475391, *(float*)(edi + 0x30));
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475395, *(float*)(edi + 0x38));
            VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x3475398, *(float*)(edi + 0x40));
            VPTR(void, esi, 0x58)(esi);
            return true;
        }
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0xff0ee1:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347536b);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a0, *(int*)(edi + 0x10));
        return true;
    case 0xff0f01:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347536f);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x34753a4, *(float*)(edi + 0x10));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x1956125:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475376);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a7, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x3c, unsigned, float)(esi, 0x34753aa, *(float*)(edi + 0x18));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753ad, *(int*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x19aa8ab:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x3475331);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475381, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x58)(esi);
        return true;
    case 0x24255a9:
        vt = *(void**)esi;
        VPTR(void, esi, 0x38, unsigned)(esi, 0x347537a);
        edi = (char*)info;
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x3475385, *(int*)(edi + 8));
        VPTR(void, esi, 0x40, unsigned, int)(esi, 0x34753a7, *(int*)(edi + 0x10));
        VPTR(void, esi, 0x4c, unsigned, int, int)(esi, 0x34753b0, *(int*)(edi + 0x18), *(int*)(edi + 0x20));
        VPTR(void, esi, 0x58)(esi);
        return true;
    default:
        break;
    }
    return true;
}

// ---------------------------------------------------------------------------------------
// 0x00A21A60  reference holder virtual forward
// ---------------------------------------------------------------------------------------
// @ 0x00A21A60
void __fastcall forward_00a21a60(void* self) {
    void* p = *(void**)((char*)self + 0xc);
    if (p == 0) return;
    char* q = (char*)p + 4;
    void* vt = *(void**)q;
    void* fn = *(void**)((char*)vt + 4);
    ((void (__thiscall*)(void*))fn)(q);
}

// ---------------------------------------------------------------------------------------
// 0x00A21A80  EA::Audio::Voice::FindByTag
// ---------------------------------------------------------------------------------------
// @ 0x00A21A80
void* AudioSys_00a21a80::FindVoice(unsigned tag) {
    char* self = (char*)this;
    if (tag == 0) tag = 0xf1cc1687;
    char* end = *(char**)(self + 0x119ba8);
    char* it  = *(char**)(self + 0x119ba4);
    if (it == end) return 0;
    do {
        void* v = *(void**)it;
        if (v != 0) VPTR(void, v, 0)(v);
        if (tag == *(unsigned*)((char*)v + 0x970)) {
            VPTR(void, v, 4)(v);
            return v;
        }
        VPTR(void, v, 4)(v);
        it += 4;
    } while (it != end);
    return 0;
}

// ---------------------------------------------------------------------------------------
// 0x00A21B20  EA::Audio multi-arg commander
// ---------------------------------------------------------------------------------------
// @ 0x00A21B20
bool AudioSys_00a21b20::Command(int a1, int a2, int a3, int a4, int a5) {
    void* self = (void*)this;
    if (a2 == 0 || a3 == 0) return false;
    void* p = VPTR(void*, self, 0x17c, int)(self, a1);
    if (p != 0) {
        if (((VoiceContainer*)p)->Connect(a2, a3)) {
            return true;
        }
    }
    if (a4 == 0) return false;
    unsigned n = (unsigned)a3;
    for (unsigned i = 0; i < n; ++i) {
        void* v = *(void**)(a2 + i * 4);
        ((void (__cdecl*)(void*, void*))a4)(v, (void*)a5);
    }
    return false;
}

// ---------------------------------------------------------------------------------------
// 0x00A21B90  EA::Audio multi-arg commander (4 args)
// ---------------------------------------------------------------------------------------
// @ 0x00A21B90
bool AudioSys_00a21b90::Command4(int a1, int a2, int a3, int a4, int a5) {
    void* self = (void*)this;
    if (a4 == 0) return false;
    void* p = VPTR(void*, self, 0x17c, int)(self, a1);
    if (p == 0) return false;
    return ((VoiceContainer*)p)->Connect4(a2, a3, a4, a5);
}

// ---------------------------------------------------------------------------------------
// 0x00A21BD0  EA::Audio commander (release a voice)
// ---------------------------------------------------------------------------------------
// @ 0x00A21BD0
void __fastcall command_00a21bd0(void* self, void* dummy, int a) {
    void* p = VPTR(void*, self, 0x17c, int)(self, a);
    if (p != 0)
        disconnect_00a21590((char*)p);
}

// ---------------------------------------------------------------------------------------
// 0x00A21C00  eastl::vector<EA::AutoRefCount<...>>::~vector
// ---------------------------------------------------------------------------------------
// @ 0x00A21C00
void VoiceVec_00a21c00::Destroy() {
    int* self = (int*)this;
    int* end = (int*)self[1];
    int* it  = (int*)self[0];
    while (it < end) {
        void* p = (void*)*it;
        if (p != 0)
            VPTR(void, p, 8)(p);
        ++it;
    }
    void* begin = (void*)self[0];
    if (begin != 0)
        f_00f47380(begin);
}

// -------------------------------------------------------------------------------------
// 0x00A21C70  list node -> payload (out) then optional
// -------------------------------------------------------------------------------------
// @ 0x00A21C70
// The original loads the out-pointer into EAX and returns it; caller 0x00A2E650 reads EAX.
void** __fastcall nodeToPayload_00a21c70(void* self, void* dummy, void** out) {
    void* v = *(void**)self;
    if (v != 0) *out = (char*)v - 0x10;
    else *out = 0;
    return out;
}

// @ 0x00A21C90
// The original loads the out-pointer into EAX and returns it; caller 0x00A2E650 reads EAX.
void** __fastcall nodeToPayload_00a21c90(void* self, void* dummy, void** out) {
    if (self != 0) *out = (char*)self - 0x10;
    else *out = 0;
    return out;
}

// ---------------------------------------------------------------------------------------
// 0x00A21CB0  eastl list insert helper
// ---------------------------------------------------------------------------------------
// @ 0x00A21CB0
void* __stdcall listInsert_00a21cb0(void* a1, void* holder, void* newnode) {
    char* eax_p = (char*)holder;
    char* edx_p = (char*)(eax_p + 0x14);
    unsigned e = *(unsigned*)edx_p;
    char* esi_p = (e != 0) ? (char*)(e - 0x10) : (char*)0;
    char* ecx_p = (char*)newnode;
    char* eax2 = (ecx_p != 0) ? (char*)(ecx_p + 0x10) : (char*)0;
    *(unsigned*)edx_p = (unsigned)eax2;
    unsigned edx2 = *(unsigned*)edx_p;
    char* eax3 = (char*)(esi_p + 0x10);
    *(unsigned*)eax3 = edx2;
    *(unsigned*)(ecx_p + 0x14) = (unsigned)eax3;
    char* eax4 = (char*)(eax_p + 0x10);
    *(unsigned*)(ecx_p + 0x10) = (unsigned)eax4;
    *(unsigned*)a1 = (unsigned)ecx_p;
    return a1;
}

// ---------------------------------------------------------------------------------------
// 0x00A21D00  copy-construct an AutoRefCount (addref)
// ---------------------------------------------------------------------------------------
// @ 0x00A21D00
void* __fastcall copyRef_00a21d00(char* self, void* dummy, void* src, unsigned** ref) {
    *(unsigned*)(self + 0) = *(unsigned*)((char*)src + 0);
    *(unsigned*)(self + 4) = *(unsigned*)((char*)src + 4);
    *(unsigned*)(self + 8) = *(unsigned*)((char*)src + 8);
    unsigned r = (unsigned)*ref;
    *(unsigned*)(self + 0xc) = r;
    if (r != 0) VPTR(void, (void*)r, 0)((void*)r);
    return self;
}

// ---------------------------------------------------------------------------------------
// 0x00A21D30  ring-buffer push (voice-id queue)
// ---------------------------------------------------------------------------------------
// @ 0x00A21D30
void __fastcall ringPush_00a21d30(char* self, void* dummy, unsigned* v) {
    unsigned* p = *(unsigned**)(self + 0xfc0);
    *p = *v;
    *(unsigned*)(self + 0xfc0) += 4;
    unsigned* end = *(unsigned**)(self + 4);
    if (*(unsigned**)(self + 0xfc0) == end)
        *(unsigned*)(self + 0xfc0) = *(unsigned*)self;
    unsigned* begin = *(unsigned**)(self + 0xfbc);
    if (*(unsigned**)(self + 0xfc0) == begin) {
        begin = begin + 1;
        *(unsigned*)(self + 0xfbc) = (unsigned)begin;
        if (begin == end)
            *(unsigned*)(self + 0xfbc) = *(unsigned*)self;
        return;
    }
    ++*(unsigned*)(self + 0xfc4);
}

// ---------------------------------------------------------------------------------------
// 0x00A21D90  copy-construct a ref pair (addref second)
// ---------------------------------------------------------------------------------------
// @ 0x00A21D90
void* __fastcall copyRef2_00a21d90(char* self, void* dummy, unsigned** a, unsigned** b) {
    *(unsigned*)(self + 0) = (unsigned)*a;
    unsigned r = (unsigned)*b;
    *(unsigned*)(self + 4) = r;
    if (r != 0) VPTR(void, (void*)r, 0)((void*)r);
    return self;
}

// ---------------------------------------------------------------------------------------
// 0x00A21DC0  eastl::rbtree<Key,...>::find
// ---------------------------------------------------------------------------------------
// @ 0x00A21DC0
void* RbTree_00a21dc0::Find(void** out, void* key) {
    char* self = (char*)this;
    unsigned node = *(unsigned*)(self + 0xc);
    char* root = self + 4;
    char* it = root;
    if (node != 0) {
        unsigned* k = (unsigned*)key;
        do {
            unsigned k0 = k[0];
            unsigned v10 = *(unsigned*)(node + 0x10);
            bool less;
            if (v10 != k0) {
                less = v10 < k0;
            } else {
                unsigned v18 = *(unsigned*)(node + 0x18);
                unsigned k8 = k[2];
                if (v18 != k8) {
                    less = v18 < k8;
                } else {
                    less = *(unsigned*)(node + 0x14) < k[1];
                }
            }
            if (!less) {
                it = (char*)node;
                node = *(unsigned*)(node + 4);
            } else {
                node = *(unsigned*)(node + 0);
            }
        } while (node != 0);
    }
    if (it != root) {
        unsigned* k = (unsigned*)key;
        unsigned k0 = k[0];
        unsigned v10 = *(unsigned*)((char*)it + 0x10);
        bool less;
        if (v10 != k0) {
            less = k0 < v10;
        } else {
            unsigned k8 = k[2];
            unsigned v18 = *(unsigned*)((char*)it + 0x18);
            if (v18 != k8) {
                less = k8 < v18;
            } else {
                less = k[1] < *(unsigned*)((char*)it + 0x14);
            }
        }
        if (!less) { *out = it; return out; }
    }
    *out = root;
    return out;
}

// ---------------------------------------------------------------------------------------
// 0x00A21EB0  EA::Audio::System::RemoveVoice (hash-bucket unlink)
// ---------------------------------------------------------------------------------------
// @ 0x00A21EB0
void HashA_00a21eb0::Rehash(unsigned a) {
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashA_00a21eb0*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned h = (unsigned)(node[2] ^ node[0]);
            unsigned bucket = h % a;
            int* next = (int*)node[4];
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            node[4] = (int)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)) {
            if ((char*)p >= *(char**)(self + 0x24) && (char*)p < *(char**)(self + 0x28)) {
                *(void**)p = *(void**)(self + 0x1c);
                *(void**)(self + 0x1c) = p;
            } else {
                f_00f47380(p);
            }
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}

// ---------------------------------------------------------------------------------------
// 0x00A21F60  allocate an AutoRefCount record
// ---------------------------------------------------------------------------------------
// @ 0x00A21F60
void* __stdcall allocRef_00a21f60(void* src) {
    unsigned char* esi = (unsigned char*)f_00f473a0(0x14, (void*)0x13f2150, 0, 0, (void*)0x13ebb38, 0xd1);
    if (esi != 0) {
        *(unsigned*)(esi + 0) = *(unsigned*)((char*)src + 0);
        *(unsigned*)(esi + 4) = *(unsigned*)((char*)src + 4);
        *(unsigned*)(esi + 8) = *(unsigned*)((char*)src + 8);
        unsigned c = *(unsigned*)((char*)src + 0xc);
        *(unsigned*)(esi + 0xc) = c;
        if (c != 0) VPTR(void, (void*)c, 0)((void*)c);
        *(unsigned*)(esi + 0x10) = 0;
    }
    return esi;
}

// ---------------------------------------------------------------------------------------
// 0x00A22060  EA::Audio hash-bucket rehash (stride +0x1e4)
// ---------------------------------------------------------------------------------------
// @ 0x00A22060
void HashB_00a22060::Rehash(unsigned a) {
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashB_00a22060*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned bucket = (unsigned)node[0] % a;
            int* next = *(int**)((char*)node + 0x1e4);
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            *(unsigned*)((char*)node + 0x1e4) = (unsigned)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)
            && !((char*)p < *(char**)(self + 0x24) || (char*)p >= *(char**)(self + 0x28))) {
            f_00f47380(p);
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}

// ---------------------------------------------------------------------------------------
// 0x00A22110  EA::Audio hash-bucket rehash (stride +0x24)
// ---------------------------------------------------------------------------------------
// @ 0x00A22110
void HashC_00a22110::Rehash(unsigned a) {
    char* self = (char*)this;
    int count = (int)a;
    void* newTable = ((HashC_00a22110*)self)->Alloc(a);
    int i = 0;
    for (i = 0; (unsigned)i < *(unsigned*)(self + 8); ++i) {
        int* node = *(int**)((char*)*(void**)(self + 4) + i * 4);
        if (node == 0) continue;
        for (;;) {
            unsigned bucket = (unsigned)node[0] % a;
            int* next = *(int**)((char*)node + 0x24);
            *(unsigned*)((char*)*(void**)(self + 4) + i * 4) = (unsigned)next;
            int** head = (int**)((char*)newTable + bucket * 4);
            *(unsigned*)((char*)node + 0x24) = (unsigned)*head;
            *head = node;
            node = *(int**)((char*)*(void**)(self + 4) + i * 4);
            if (node == 0) break;
        }
    }
    if (*(unsigned*)(self + 8) > 1) {
        void* p = *(void**)(self + 4);
        if (p != *(void**)(self + 0x30)) {
            if ((char*)p >= *(char**)(self + 0x24) && (char*)p < *(char**)(self + 0x28)) {
                *(void**)p = *(void**)(self + 0x1c);
                *(void**)(self + 0x1c) = p;
            } else {
                f_00f47380(p);
            }
        }
    }
    *(void**)(self + 4) = newTable;
    *(unsigned*)(self + 8) = (unsigned)count;
}