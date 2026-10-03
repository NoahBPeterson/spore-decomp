// Object assignment operator (field-wise copy with intrusive refcount handling) and a per-frame tick routine.
// Built /Od /Ob1 /MD /Gy /TP /arch:SSE. Neither function is byte-exact (see nonmatching.txt).
#include "types.h"
namespace A {
struct Counted { char pad[0x40]; int refCount; };
struct Owned { void __thiscall AddRef(); void __thiscall Release(); };   // 68f950 / 690120
struct Shared { char pad[0x40]; int refCount; void __thiscall Release(); };
inline void AssignShared(Shared** pdst, Shared* src) {
    if (src != *pdst) { Shared* old = *pdst; if (src) src->refCount++; *pdst = src; if (old) old->Release(); }
}                            // 40f360

struct Opaque4 { uint32_t pad; void __thiscall Set(uint32_t); };
struct SeqA { uint32_t pad[5]; void __thiscall Assign(const SeqA&); };    // 41ebe0
struct SeqB { uint32_t pad[5]; void __thiscall Assign(const SeqB&); };    // 420e30
struct SeqC { uint32_t pad[5]; void __thiscall Assign(const SeqC&); };    // 41e0d0
struct SeqD { uint32_t pad[5]; void __thiscall Assign(const SeqD&); };    // 41f320
struct Block80 { uint32_t pad[5]; uint8_t flag; uint8_t q[3]; void __thiscall CopyBase(const Block80&);
    inline void Assign(const Block80& o) { const Block80* sr = &o; Block80* d = this; d->CopyBase(*sr); uint8_t t = sr->flag; d->flag = t; } }; // 4269b0
struct SeqE { uint32_t pad[5]; void __thiscall Assign(const SeqE&); };    // 421290
struct Range { uint32_t* first; uint32_t* last; void __thiscall Assign(uint32_t*, uint32_t*); }; // 423650

struct SeqF { uint32_t pad[5]; void __thiscall Assign(const SeqF&); };    // 421670
struct SeqG { uint32_t pad[5]; void __thiscall Assign(const SeqG&); };    // 406ac0

struct Obj {
    Owned* owned;        // 0x00
    Opaque4 f04;         // 0x04
    SeqA f08;            // 0x08
    SeqA f1c;            // 0x1c
    SeqB f30;            // 0x30
    SeqC f44;            // 0x44
    SeqD f58;            // 0x58
    SeqA f6c;            // 0x6c
    Block80 f80;         // 0x80
    SeqE f98;            // 0x98
    SeqA fac;            // 0xac
    Shared* c0;         // 0xc0
    Shared* c4;         // 0xc4
    uint32_t c8, cc;
    Range d0;            // 0xd0 (container header)
    uint32_t pad2[2];
    SeqF fe0;
    uint8_t f4a, f4b; uint8_t pp[2];
    uint32_t f8;
    SeqG fc;
    uint32_t big[(0xdc8 - 0x110) / 4];
    uint32_t t0, t1;
    Obj& operator=(const Obj&);
};

// @ 0x00411b90
Obj& Obj::operator=(const Obj& o)
{
    Owned* old;
    Owned* n = o.owned;
    if (n != owned) {
        old = owned;
        if (n) n->AddRef();
        owned = n;
        if (old) old->Release();
    }
    f04.Set(o.f04.pad);
    f08.Assign(o.f08);
    f1c.Assign(o.f1c);
    f30.Assign(o.f30);
    f44.Assign(o.f44);
    f58.Assign(o.f58);
    f6c.Assign(o.f6c);
    f80.Assign(o.f80);
    f98.Assign(o.f98);
    fac.Assign(o.fac);
    AssignShared(&c0, o.c0);
    AssignShared(&c4, o.c4);
    c8 = o.c8;
    cc = o.cc;
    if (&o.d0 != &d0) d0.Assign(o.d0.first, o.d0.last);
    fe0.Assign(o.fe0);
    f4a = o.f4a;
    f4b = o.f4b;
    f8 = o.f8;
    fc.Assign(o.fc);
    t0 = o.t0; t1 = o.t1;
    return *this;
}
}
namespace B {

struct IRelease { virtual void v0(); virtual void Release(); };
struct IProps {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetValue(uint32_t id, void* v);
};
struct IResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool Open(uint32_t inst, uint32_t key, uint32_t arg);
};
struct IIter {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Next(void* key, IRelease** out, int, int, int, int);
};
struct TransformHdr { uint32_t pad; float x, y, pad2, z; };
struct ModelEntry { uint32_t pad; uint16_t type; uint16_t pad2; TransformHdr* hdr; };
struct ModelList { uint32_t pad[2]; ModelEntry** items; bool __thiscall IsEmpty(); };
struct Inner { uint32_t pad[0x2e]; ModelList* models; };
struct Mid { uint32_t pad[2]; Inner* inner; };
struct Cam { char pad[0x70]; float x, y, z; };
struct Cell { uint32_t pad[2]; Mid* mid; };
struct Counter { uint32_t pad[5]; float scale; };
struct Obj2;

IResMgr* GetResMgr();
int64_t __fastcall ReadCounter(Counter*);
void __fastcall UpdateCounter(Counter*);
IIter* GetIter();
bool __cdecl GetBoolProperty(IProps*, uint32_t, bool*);
uint32_t __cdecl GetNameId(uint32_t);
void* __cdecl AllocBuf(uint32_t);
void __cdecl BindKey(uint32_t, uint32_t, void*, int);
void __cdecl PutBack(void*, int);
void __cdecl ApplyProps(IProps*, uint32_t, int);
void __cdecl FreeText(int);

struct Obj2 {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void vf26();
    virtual void vf27();
    virtual void SetPreBaked(uint32_t* key, bool v, const wchar_t* name);
    char pad0[0x74 - 4];
    uint32_t f74;
    char pad1[0x228 - 0x78];
    uint32_t keyInst, keyType, keyGroup;   // 0x228
    uint32_t f234;
    uint16_t flags;                        // 0x238
    char pad3[0x240 - 0x23a];
    Cell* cell;                            // 0x240
    char pad4[0x1114 - 0x244];
    int cntA;
    char pad5[0x1120 - 0x1118];
    int cntB;
    float sumA;
    float lastA;
    char pad6[0x1138 - 0x112c];
    Counter c1;
    Counter c2;
    void ApplyBlend(uint32_t* key, float a, float b);
    void Tick();
};


struct IKeyHolder { virtual void v0(); virtual void Release(); };
bool __cdecl FindEntry(IKeyHolder*, uint32_t, uint32_t*);   // 0x6a1250
struct Str16 { uint32_t pad[4]; uint16_t kind; uint16_t flags; };
void __fastcall MakeStr(Str16* s, uint32_t* v);   // 0x422eb0
void __cdecl FreeStr(int);                          // 0x93db80
void __cdecl StartIter(uint32_t);                   // placeholder not used

// @ 0x00411e50
void Obj2::Tick()
{
    uint32_t keyI = keyInst;
    uint32_t keyT = keyType;
    uint32_t keyG = keyGroup;
    ModelList* list = cell->mid->inner->models;
    if (list) {
        if (!list->IsEmpty() && (*list->items)->type == 0x210) {
            TransformHdr* h = (*list->items)->hdr;
            h->x = ((Cam*)cell)->x;
            h->y = ((Cam*)cell)->y;
            h->z = ((Cam*)cell)->z;
        }
    }
    IProps* props = 0;
    IResMgr* mgr = GetResMgr();
    if (mgr->Open(keyI, (keyG & 0xffff00ff) | 0x6200, 0)) {
        bool flag;
        if (GetBoolProperty(props, 0x3f32ad2, &flag) && flag) {
            if (keyT == 0x438f6347) {
                uint32_t nameId = GetNameId(0);
                Str16 s;
                s.kind = 2;
                s.flags = 9;
                MakeStr(&s, &nameId);
                props->SetValue(0x4239b99, &s);
                if (s.kind & 4) FreeStr(0);
            }
            ApplyProps(props, f74, 0);
        }
    }
    float a = 0.0f, b = 0.0f;
    UpdateCounter(&c2);
    b = (float)ReadCounter(&c2) * c2.scale;
    a = (float)ReadCounter(&c1) * c1.scale + b;
    lastA = b;
    sumA = sumA + b;
    cntB = cntB + 1;
    if (flags & 0x40)
        SetPreBaked(&keyI, (flags & 0x80) != 0, L"PreBaked");
    cntA = cntA + 1;
    if (!(flags & 2)) {
        void* buf = AllocBuf(0x11ac1ac);
        BindKey(keyInst, keyGroup, buf, 1);
        uint32_t g2 = (keyGroup & 0xffff00ff) | 0xe300;
        BindKey(keyInst, g2, buf, 1);
        if (((keyG >> 16) & 0xff) == 0x62) {
            IKeyHolder* holder = 0;
            IResMgr* m2 = GetResMgr();
            if (holder) { IKeyHolder* t = holder; holder = 0; t->Release(); }
            if (m2->Open(keyI, (keyG & 0xe0ffffff) | 0x01000000, 0)) {
                IIter* it = GetIter();
                for (int i = 0; i < 4; ++i) {
                    uint32_t k[4] = { 0, 0, 0, 0 };
                    if (FindEntry(holder, 0xf9efbb + i, k) && ((k[2] >> 24) & 0x1f) == 1) {
                        IRelease* out = 0;
                        if (it->Next(k, &out, 0, 0, 0, 0)) PutBack(out, 1);
                        if (out) out->Release();
                    }
                }
            }
            if (holder) holder->Release();
        }
    }
    ApplyBlend(&keyInst, a, b);
    if (props) ((IRelease*)props)->Release();
}
}
