// Slice s00f2c470.  Scenario-resource / building-data copy and serialization
// helpers.  Built /O2 /MD /Gy /TP.

typedef unsigned int uint;
typedef unsigned int size_t;

// ---------------------------------------------------------------------------
// cString and the 0x3c-byte sub-object used by the constructors below.
struct CS {                       // 0x3c bytes
    void Ctor();                  // 0x6b5060
    void Dtor();                  // 0x6b5240
    void* GetText();              // 0x6b55c0
    uint  pad0[5];                // 0x00
    void* mTableId;               // 0x14
    void* mInstanceId;            // 0x18
    void* mPtr1c;                 // 0x1c
    uint  pad20;                  // 0x20
    void* mStr24;                 // 0x24
    void* mStr28;                 // 0x28
    void* mPtr2c;                 // 0x2c
    void* mPtr30;                 // 0x30
    void* mPtr34;                 // 0x34
    uint  f38;                    // 0x38
};
extern int g_1667bac;
extern int g_1667bae;

// ---------------------------------------------------------------------------
// 0x44-byte record and its 0x3c-byte payload; Val is the same layout with a
// cString payload (used by the serialization loops).
struct Sub { uint pad[15]; };
struct Rec {                      // 0x44
    int kind;                     // 0x00
    Sub sub;                      // 0x04
    int icon;                     // 0x40
};
struct Val {                      // 0x44
    int kind;                     // 0x00
    CS  cs;                       // 0x04
    int icon;                     // 0x40
};
struct SubOp { void copyFrom(const void* p); };   // 0xdfb280

// ---------------------------------------------------------------------------
// Helpers resolved against the original image (targets are masked as relocs).
extern "C" void* operator_new(uint size, const char* tag, int a, int b, const char* file, int line);  // 0xf473a0
extern "C" void  operator_delete__(void* p);                     // 0xf47380
extern "C" void* FUN_00f2b040(void* out, int a, int b);          // 0x00f2b040
extern "C" int*  FUN_0067dcd0();                                 // 0x0067dcd0 GetManager
extern "C" void  FUN_004f5720(void* a, void* b);                 // 0x004f5720
extern "C" void  FUN_00f2ba80(void* a, void* b);                 // 0x00f2ba80
extern "C" void* FUN_00f09db0(void* a, void* b, void* c);        // 0x00f09db0
extern "C" void  FUN_00f07bd0(void* a, void* b, void* c);        // 0x00f07bd0
extern "C" void  FUN_00f09880(void* a, void* b, void* c);        // 0x00f09880
extern "C" void  FUN_00f2a430(void* a, void* b, void* c);        // 0x00f2a430
extern "C" void  FUN_00f2a490(void* a, void* b, void* c);        // 0x00f2a490
extern "C" void  FUN_00f292c0(void* a, uint n, void* c, void* d);// 0x00f292c0
extern "C" void* FUN_00f29330(void* a, void* b, void* c);        // 0x00f29330
extern "C" void  FUN_00f28070(void* a, void* b, void* c);        // 0x00f28070
extern "C" void  FUN_00dfb890();
extern "C" void  FUN_00dfbc80(void* a, void* b, void* c, void* d); // 0x00dfbc80
extern "C" void  FUN_00dfb280();
extern "C" void  FUN_00dfb3c0();
extern "C" void  FUN_00dfcb00();
extern "C" void* FUN_00dfaaf0();
extern "C" void* FUN_00dfb930(void* a, void* b, void* c);        // 0x00dfb930 eastl::copy
extern "C" char  FUN_00f25f80();
extern "C" char  FUN_00f2bd50();
extern "C" void* FUN_0067da60(int a, int b);                     // 0x0067da60
extern "C" void  FUN_00dfae00();

extern "C" void  __fastcall FUN_00f2c5d0(void* self, int edx, uint n);            // 0x00f2c5d0
extern "C" void  __fastcall FUN_00f2c6a0(void* self, int edx, Rec* position, Rec* val); // 0x00f2c6a0
extern "C" void  FUN_00f0b390();
extern "C" void* DoInsertValueBool(void* b, void* e, int v);     // 0x11e0744

typedef void  (__thiscall *TC1)(void*, void*);
typedef void  (__thiscall *TC0)(void*);
typedef void  (__thiscall *TC3v)(void*, void*, void*);
typedef char  (__thiscall *TC1r)(void*, void*);
typedef char  (__thiscall *TC2rc)(void*, void*, int);
typedef void  (__thiscall *TC1i)(void*, int);
typedef void* (__thiscall *TC2p)(void*, void*);

struct Ser {                      // cVarListSerializer
    void ctor(void* a, void* b, uint tag);                       // 0x692f90
    char Serialize(void* o);                                     // 0x693e10
};
extern "C" void SCtor(Ser* self, void* a, void* b, uint tag);    // 0x692f90
extern "C" char SSer(Ser* self, void* o);                        // 0x693e10
extern "C" bool ReadInt32(void* stream, void* dst, int count, int b); // 0x93a780

// Generic object with a full vtable (slots at the byte offsets the targets use).
struct VObj {
    virtual void s00();                 // +0x00
    virtual void Release();             // +0x04
    virtual void s08();                 // +0x08
    virtual VObj* Query(uint id);       // +0x0c
    virtual void s10();
    virtual void s14();
    virtual VObj* V18();                // +0x18
    virtual void s1c();                 // +0x1c
    virtual VObj* V20();                // +0x20
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual int  V3c(int a);            // +0x3c
    virtual void s40();
    virtual void s44();
    virtual bool V48(VObj* p, int a);   // +0x48
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual bool V98(int a, int b);     // +0x98
};

struct Ctx2c60 { char pad[0x2c60]; };

struct Man {                                  // ResourceManager-shaped
    virtual void s00();                       // +0x00
    virtual void Release();                   // +0x04
    virtual void s08();                       // +0x08
    virtual void Q(void* a, void** b, int, int, int, int);  // +0x0c
};

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------
// @ 0x00f2c470
void __fastcall FUN_00f2c470(Ctx2c60* p)
{
    uint* base = (uint*)((char*)p + 0x2c54);
    void* b = (void*)base[0];
    void* e = (void*)base[1];
    DoInsertValueBool(b, e, 0);
    base[1] = (uint)((char*)base[1] + ((int)((char*)e - (char*)b) >> 2) * -4);

    uint a28 = 0, a24 = 0, a20 = 0;
    uint a14 = 0, a10 = 0, a0c = 0;
    FUN_00f2b040(&a28, 7, 0);
    uint n = (a24 - a28) >> 2;
    for (uint i = 0; i < n; ++i) {
        uint* el = *(uint**)(a28 + i * 4);
        uint v34 = el[0], v30 = el[1], v2c = el[2];
        VObj* res = 0;
        Man* man = (Man*)FUN_0067dcd0();
        if (res) { VObj* t = res; res = 0; t->Release(); }
        man->Q(&v34, (void**)&res, 0, 0, 0, 0);
        if (res) {
            VObj* q = res->Query(0x3c609f8);
            if (q) {
                FUN_004f5720(q, &a14);
                FUN_00f2ba80((void*)a14, (void*)a10);
            }
            res->Release();
        }
    }
    if (a28 && *(int*)(a28 - 4)) operator_delete__((void*)a28);
    if (a14 && *(int*)(a14 - 4)) operator_delete__((void*)a14);
}

// @ 0x00f2c5d0
void __fastcall FUN_00f2c5d0(void* self, int edx, uint n)
{
    uint* v = (uint*)self;
    if ((uint)((int)(v[2] - v[0]) / 0x44) < n) {
        void* mem = 0;
        if (n == 0) {
            mem = 0;
        } else {
            mem = operator_new(n * 0x44, "Simulator", 0, 0, kEastlFile, 0xd1);
        }
        uint e = v[1];
        uint saved = v[0];
        FUN_00f09db0((void*)saved, (void*)e, mem);
        FUN_00f07bd0((void*)saved, (void*)e, mem);
        if (v[0] && *(int*)(v[0] - 4)) operator_delete__((void*)v[0]);
        v[0] = (uint)mem;
        v[1] = (uint)((char*)mem + ((int)(v[1] - saved) / 0x44) * 0x44);
        v[2] = (uint)mem + n * 0x44;
    }
}

// @ 0x00f2c6a0
void __fastcall FUN_00f2c6a0(void* self, int edx, Rec* position, Rec* val)
{
    uint* v = (uint*)self;
    Rec* pos = (Rec*)v[1];
    if (pos != (Rec*)v[2]) {
        Rec* next = val;
        if (val >= position && val < pos) next = (Rec*)((char*)val + 0x44);
        if (pos) {
            pos->kind = *(int*)((char*)pos - 0x44);
            ((SubOp*)((char*)pos + 4))->copyFrom((char*)pos - 0x44 + 4);
            pos->icon = *(int*)((char*)pos - 4);
        }
        FUN_00f09880(position, (char*)pos - 0x44, pos);
        ((TC1)FUN_00dfb3c0)(position, next);
        v[1] = (uint)((char*)pos + 0x44);
        return;
    }
    uint size = (uint)((v[1] - v[0]) / 0x44);
    void* mem = 0;
    uint newCap;
    if (size == 0) {
        newCap = 1;
    } else {
        newCap = size * 2;
        if (newCap == 0) goto alloc;
    }
    {
        uint count = newCap;
        mem = operator_new(count * 0x44, "Simulator", 0, 0, kEastlFile, 0xd1);
    }
    goto setup;
alloc:
    mem = 0;
setup:
    void* b = (void*)v[0];
    Rec* p1 = (Rec*)FUN_00f09db0(b, position, mem);
    FUN_00f07bd0(b, position, mem);
    if (p1) {
        p1->kind = val->kind;
        ((SubOp*)&p1->sub)->copyFrom(&val->sub);
        p1->icon = val->icon;
    }
    void* e = (void*)v[1];
    Rec* p2 = (Rec*)FUN_00f09db0(position, e, (char*)p1 + 0x44);
    FUN_00f07bd0(position, e, (char*)p1 + 0x44);
    if (v[0] && *(int*)(v[0] - 4)) operator_delete__((void*)v[0]);
    v[1] = (uint)p2;
    v[0] = (uint)mem;
    v[2] = (uint)mem + newCap * 0x44;
}

// @ 0x00f2c810
bool __stdcall FUN_00f2c810(VObj* a0, void* a1, VObj* a2, int type)
{
    (void)a1;
    if (!a0) return false;
    VObj* r = a0->Query(0xe742574a);
    if (!r) return false;
    if (type == 0x191c3c61) {
        VObj* o = a2->V18();
        if (!((TC2rc)FUN_00f2bd50)(r, o, 1)) return false;
        return o->V18() != 0;
    }
    if (type != 0xe22261b7)
        return ((TC1r)FUN_00f25f80)(r, a2->V18()) != 0;
    VObj* o = (VObj*)operator_new(0x30, "Simulator", 0, 0, 0, 0);
    if (o) o = (VObj*)FUN_0067da60(0, -1);
    if (!o->V3c(1)) goto L;
    if (!o->V48(a2->V18(), -1)) goto L;
    if (!((TC2rc)FUN_00f2bd50)(r, o, 0)) goto L;
    if (o->V18()) {
        o->s08();
        return true;
    }L:
    o->s08();
    return false;
}

// @ 0x00f2c950
void FUN_00f2c950(VObj* p, uint* v)
{
    uint b = v[0];
    uint e = v[1];
    void* r = FUN_00dfb930((void*)e, (void*)e, (void*)b);
    ((TC3v)FUN_00dfaaf0)((void*)v, r, (void*)e);
    v[1] = (uint)((int)e + (((int)(e - b) / 0x44) * 0x44));

    char frame[0xa60];
    uint count = 0;
    VObj* s = p->V20();
    ReadInt32(s->V18(), &count, 1, 0);
    FUN_00f2c5d0(v, 0, count);
    for (uint i = 0; i < count; ++i) {
        Val val;
        val.kind = 0;
        val.icon = 0;
        val.cs.Ctor();
        val.cs.mTableId = &g_1667bac;
        val.cs.mInstanceId = &g_1667bac;
        val.cs.mPtr1c = &g_1667bae;
        val.cs.mStr24 = 0;
        val.cs.mStr28 = 0;
        val.cs.mPtr2c = &g_1667bac;
        val.cs.mPtr30 = &g_1667bac;
        val.cs.mPtr34 = &g_1667bae;
        Ser ser;
        SCtor(&ser, &val, (void*)0x15adae0, 0x1a80d26);
        SSer(&ser, p);
        Rec* pos = (Rec*)v[1];
        if (pos < (Rec*)v[2]) {
            v[1] = (uint)((char*)pos + 0x44);
            if (pos) {
                pos->kind = val.kind;
                ((SubOp*)&pos->sub)->copyFrom(&val.cs);
                pos->icon = val.icon;
            }
        } else {
            FUN_00f2c6a0(v, 0, pos, (Rec*)&val);
        }
        val.cs.Dtor();
        (void)frame;
    }
    p->s1c();
}

// @ 0x00f2cb50
struct E34 { uint w[12]; int f30; };
void __fastcall FUN_00f2cb50(uint* v, int edx, void* pos, uint n, void* val)
{
    if ((uint)((v[2] - v[1]) / 0x34) < n) {
        uint size = (uint)((v[1] - v[0]) / 0x34);
        uint cap = size * 2;
        if (size == 0) cap = 1;
        uint newn = size + n;
        if (newn < cap) newn = cap;
        void* mem = 0;
        if (newn) mem = operator_new(newn * 0x34, "Simulator", 0, 0, kEastlFile, 0xd1);
        void* p2 = FUN_00f29330((void*)v[0], pos, mem);
        FUN_00f28070((void*)v[0], pos, mem);
        FUN_00f292c0(p2, n, val, p2);
        void* mid = (char*)p2 + n * 0x34;
        void* end = (void*)v[1];
        void* p3 = FUN_00f29330(pos, end, mid);
        FUN_00f28070(pos, end, mid);
        if (v[0] && *(int*)(v[0] - 4)) operator_delete__((void*)v[0]);
        v[1] = (uint)p3;
        v[0] = (uint)mem;
        v[2] = (uint)mem + newn * 0x34;
    } else if (n != 0) {
        E34 tmp;
        ((TC1)FUN_00dfb890)(&tmp, val);
        void* end = (void*)v[1];
        uint have = (uint)((v[1] - (uint)pos) / 0x34);
        if (n < have) {
            char* back = (char*)end - n * 0x34;
            FUN_00dfbc80(&val, back, end, end);
            void* p = pos;
            v[1] = (uint)((char*)v[1] + n * 0x34);
            FUN_00f2a490(pos, back, end);
            FUN_00f2a430(p, (char*)p + n * 0x34, &tmp);
        } else {
            FUN_00f292c0(end, n - have, &tmp, pos);
            void* p = pos;
            v[1] = (uint)((char*)v[1] + (n - have) * 0x34);
            FUN_00dfbc80(&pos, pos, end, (void*)v[1]);
            v[1] = (uint)((char*)v[1] + have * 0x34);
            FUN_00f2a430(p, end, &tmp);
        }
        if (tmp.f30 && *(int*)(tmp.f30 - 4)) operator_delete__((void*)tmp.f30);
    }
}

// @ 0x00f2ced0
char* FUN_00f2ced0(char* first, char* last, char* out)
{
    while (first != last) {
        if (out) {
            *(int*)(out + 0x00) = *(int*)(first + 0x00);
            *(int*)(out + 0x04) = *(int*)(first + 0x04);
            *(int*)(out + 0x08) = *(int*)(first + 0x08);
            *(int*)(out + 0x0c) = *(int*)(first + 0x0c);
            *(char*)(out + 0x10) = *(char*)(first + 0x10);
            *(int*)(out + 0x14) = *(int*)(first + 0x14);
            *(int*)(out + 0x2c) = 0;
            *(void**)(out + 0x18) = out + 0x30;
            *(void**)(out + 0x1c) = out + 0x30;
            *(void**)(out + 0x20) = out + 0x184;
            ((TC1)FUN_00dfcb00)(out + 0x18, first + 0x18);
            *(int*)(out + 0x184) = *(int*)(first + 0x184);
        }
        first += 0x188;
        out += 0x188;
    }
    return out;
}

// @ 0x00f2d090
char __fastcall FUN_00f2d090(char* p, int edx, VObj* obj)
{
    Ser s;
    SCtor(&s, p, (void*)0x15adf20, 0x1a80d26);
    char ret = SSer(&s, obj);
    uint* u = (uint*)p;
    uint n;
    if (u[0x470 / 4] && u[0x46c / 4]) {
        char* t = (char*)u[0x46c / 4];
        char* t0 = t + 2;
        while (*(short*)t) t += 2;
        n = (uint)(t - t0);
    } else {
        n = u[0x460 / 4] - u[0x45c / 4];
    }
    if ((int)(n >> 1) > 0)
        ((TC1)FUN_00dfae00)((void*)(u[1] + 4), p + 0x448);
    if ((uint)obj->V3c(0) <= 5) {
        uint cnt = (u[8 / 4] - u[4 / 4]) / 0x44;
        if ((int)cnt > 0) {
            uint off = 0;
            uint left = cnt;
            do {
                char* el = (char*)u[4 / 4] + off;
                if (*(int*)el == 3) {
                    char* v = (char*)u[0x174 / 4];
                    if (v < (char*)u[0x178 / 4]) {
                        u[0x174 / 4] = (uint)(v + 0x44);
                        if (v) {
                            *(int*)v = *(int*)el;
                            ((SubOp*)(v + 4))->copyFrom(el + 4);
                            *(int*)(v + 0x40) = *(int*)(el + 0x40);
                        }
                    } else {
                        FUN_00f2c6a0(p + 0x170, 0, (Rec*)v, (Rec*)el);
                    }
                    Val val;
                    val.kind = 0;
                    val.icon = 0;
                    val.cs.Ctor();
                    val.cs.mTableId = &g_1667bac;
                    val.cs.mInstanceId = &g_1667bac;
                    val.cs.mPtr1c = &g_1667bae;
                    val.cs.mStr24 = 0;
                    val.cs.mStr28 = 0;
                    val.cs.mPtr2c = &g_1667bac;
                    val.cs.mPtr30 = &g_1667bac;
                    val.cs.mPtr34 = &g_1667bae;
                    ((TC1)FUN_00dfb3c0)(el, &val);
                    val.cs.Dtor();
                }
                off += 0x44;
            } while (--left);
        }
    }
    ((TC1i)FUN_00f0b390)(p + 4, 5);
    ((TC1i)FUN_00f0b390)(p + 0x170, 5);
    return ret;
}

// ---------------------------------------------------------------------------
// The 0x27e0+ object built by the big constructor.
struct BigObj {
    int f000, f004, f008, f00c, f010, f014, f018;
    char f01c; char _p1[3];
    char f020; char _p2[3];
    int f024, f028, f02c, f030, f034, f038, f03c, f040;
    char f044; char _p3[3];
    int f048;
    int f050, f054, f058, f05c, f060, f064, f068;
    char f06c; char _p4[3];
    void* f070; void* f074; void* f078;
    int f07c, f080, f084;
    char buf[0x2700];
    CS cs;                                   // 0x2788
    int f27c4, f27c8, f27cc;
    int f27d0, f27d4, f27d8, f27dc;
};

// @ 0x00f2d260
BigObj* __fastcall FUN_00f2d260(BigObj* p)
{
    p->f000 = 0; p->f004 = 0; p->f008 = 0; p->f00c = 0;
    p->f010 = -1; p->f014 = -1; p->f018 = -1;
    p->f01c = 0;
    p->f020 = 1;
    p->f024 = 0; p->f028 = 0; p->f02c = 0; p->f030 = 0; p->f034 = 0;
    p->f038 = -1; p->f03c = -1; p->f040 = -1;
    p->f044 = 0;
    p->f048 = 0;
    p->f050 = 0; p->f054 = 0; p->f058 = 0; p->f05c = 0;
    p->f060 = -1; p->f064 = -1; p->f068 = -1;
    p->f06c = 0;
    p->f070 = p->buf;
    p->f074 = p->buf;
    p->f078 = p->buf + 0x2700;
    p->f084 = 0;
    CS* c = &p->cs;
    c->Ctor();
    c->mTableId = &g_1667bac;
    c->mInstanceId = &g_1667bac;
    c->mPtr1c = &g_1667bae;
    c->mStr24 = 0;
    c->mStr28 = 0;
    c->mPtr2c = &g_1667bac;
    c->mPtr30 = &g_1667bac;
    c->mPtr34 = &g_1667bae;
    p->f27c4 = 0;
    p->f27c8 = 0;
    p->f27cc = 0;
    p->f27d0 = -1;
    p->f27d8 = -1;
    p->f27dc = -1;
    return p;
}

// ---------------------------------------------------------------------------
// The 0x534-byte two-cString object built by the small constructor.
struct SmallObj {
    CS a;                        // 0x00
    CS b;                        // 0x3c
    int f078;                    // 0x78
    char f07c; char _p[3];       // 0x7c
    int f080;                    // 0x80
    void* f084; void* f088; void* f08c;  // 0x84
    int f090, f094, f098;        // 0x90
    char buf[0x498];             // 0x9c
};

// @ 0x00f2d330
SmallObj* __fastcall FUN_00f2d330(SmallObj* p)
{
    p->a.Ctor();
    p->a.mTableId = &g_1667bac;
    p->a.mInstanceId = &g_1667bac;
    p->a.mPtr1c = &g_1667bae;
    p->a.mStr24 = 0;
    p->a.mStr28 = 0;
    p->a.mPtr2c = &g_1667bac;
    p->a.mPtr30 = &g_1667bac;
    p->a.mPtr34 = &g_1667bae;
    CS* c = &p->b;
    c->Ctor();
    c->mTableId = &g_1667bac;
    c->mInstanceId = &g_1667bac;
    c->mPtr1c = &g_1667bae;
    c->mStr24 = 0;
    c->mStr28 = 0;
    c->mPtr34 = &g_1667bae;
    c->mPtr2c = &g_1667bac;
    c->mPtr30 = &g_1667bac;
    p->f080 = 0;
    p->f078 = -1;
    p->f07c = 1;
    p->f084 = p->buf;
    p->f088 = p->buf;
    p->f08c = p->buf + 0x498;
    p->f098 = 0;
    return p;
}

// ---------------------------------------------------------------------------
// eastl::vector<E34>: begin/end/capacity at +0x00/+0x04/+0x08, 0x34-byte elements.
// DoInsertValues is FUN_00f2cb50; its recorded free-function spelling carries the vector in
// ecx (plus an unused register arg), so the member ABI is used through this cast.
typedef void (__thiscall *TCins34)(void* self, E34* pos, uint n, const E34& value);

struct Vec34 {
    E34* mBegin;      // +0x00
    E34* mEnd;        // +0x04
    E34* mCapacity;   // +0x08
    uint size() const { return (uint)(mEnd - mBegin); }   // element count (0x34 stride)
    void DoErase(E34* first, E34* last);                  // 0x00f2cb00
    void resize(uint n, const E34& value);                // 0x00f2d3d0
};

// @ 0x00f2d3d0
// resize(n, value): shrink by erasing the tail (n <= size) or grow by inserting
// size()-to-n copies of value at the end (n > size).
void Vec34::resize(uint n, const E34& value)
{
    if (n > size()) {
        ((TCins34)FUN_00f2cb50)(this, mEnd, n - size(), value);
    } else {
        DoErase(mBegin + n, mEnd);
    }
}

// ---------------------------------------------------------------------------
// The remaining 0x238-stride and 0x188-stride helpers.

// @ 0x00f2d5e0
struct Big238 { int tag; char rest[0x234]; };
Big238* FUN_00f2d5e0(Big238* p, Big238* e, Big238* out)
{
    if (p != e) {
        do {
            if (out) {
                out->tag = p->tag;
                unsigned u = (unsigned)p->tag;
                if ((u >> 31) & 1) {
                } else if ((char*)out + 4 != 0) {
                    ((SubOp*)((char*)out + 4))->copyFrom((char*)p + 4);
                }
            }
            p = (Big238*)((char*)p + 0x238);
            out = (Big238*)((char*)out + 0x238);
        } while (p != e);
    }
    return out;
}

// @ 0x00f2cfa0
char* FUN_00f2cfa0(char* first, char* last, char* out)
{
    if (last == first) return out;
    do {
        last -= 0x188;
        out -= 0x188;
        *(int*)(out + 0x00) = *(int*)(last + 0x00);
        *(int*)(out + 0x04) = *(int*)(last + 0x04);
        *(int*)(out + 0x08) = *(int*)(last + 0x08);
        *(int*)(out + 0x0c) = *(int*)(last + 0x0c);
        *(char*)(out + 0x10) = *(char*)(last + 0x10);
        *(int*)(out + 0x14) = *(int*)(last + 0x14);
        ((TC1)FUN_00dfcb00)(out + 0x18, last + 0x18);
        *(int*)(out + 0x184) = *(int*)(last + 0x184);
    } while (last != first);
    return out;
}
