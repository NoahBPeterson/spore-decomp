// Slice s00ac7ab0 - Spore gameplay: citizen/creature order helpers, serializer
// adapters, Gonzago/tribe subsystem bits.  (no PDB names)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;

// ---------------------------------------------------------------------------
// generic stub objects (only vtable slot offsets / fields matter; call targets
// and vtable pointers are masked relocations)
// ---------------------------------------------------------------------------
struct Stream {
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void* s18();                       // +0x18
};
struct SerObj {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual Stream* a20();                     // +0x20
};
struct IObj {                                  // +0x00 arg char, +0x18 ret ptr, +0x20 ret int
    virtual char  b00(void* v);
    virtual char  b04(void* v);
    virtual char  b08();
    virtual char  b0c(wchar_t* v);
    virtual void  b10();
    virtual void  b14();
    virtual void* b18();
    virtual void  b1c();
    virtual int   b20();
};
struct COrder {                                // citizen/order object (vptr at 0, fields at +4)
    virtual void  d00();
    virtual void  d04();
    virtual void  d08(int p);
    virtual void  d0c(); virtual void  d10(); virtual void  d14(); virtual void  d18();
    virtual void  d1c(); virtual void  d20(); virtual void  d24(); virtual void  d28();
    virtual void  d2c(); virtual void  d30(); virtual void  d34(); virtual void  d38();
    virtual float d3c();                       // +0x3c
    virtual float d40();                       // +0x40
    COrder* vecBegin;                          // +0x04
    COrder* vecEnd;                            // +0x08
    char    pad0[0x1c - 0x0c];
    int     field1c;                           // +0x1c
    char    pad1[0x128 - 0x20];
    void*   m128;                              // +0x128
    int     m12c;                              // +0x12c
    float   m134;                              // +0x134

    int   FUN_00ac7ab0(float amount, COrder* order, int kind);
    float FUN_00ac7d10(float amount, int list, int node);
    bool  FUN_00ac7de0(COrder* order);
    void  FUN_00ac7eb0(COrder* order);
    bool  FUN_00ac7ef0(int a, int b);
    void  FUN_00ac7f80();
};
struct CSub {                                  // object at COrder::m128
    virtual void e00(); virtual void e04(); virtual void e08();
    virtual void e0c(COrder* p);
    virtual void e10();
    virtual int  e14(int id);
    virtual void e18();
    virtual void e1c();
};

extern "C" void  ReadBool(void* stream, int value);                       // 0x93ac80
extern "C" void  WriteBool3(void* stream, void* pValue, int one);         // 0x93a9a0
extern "C" void  WriteUint32(void* stream, void* pValue, int one, int zero); // 0x93aa70
extern "C" void  FUN_00693890(void* a, int b);                            // 0x693890
extern "C" void  FUN_00692e50(void* a, int b);                            // 0x692e50
extern "C" void* operator_new6(int size, const char* tag, int a, int b, int c, int d); // 0xf473a0
extern "C" void  operator_delete(void* p);                                // 0xf47380
extern "C" void* SP_NounManager(int id);                                  // 0xb3d300
extern "C" void* SP_cGameNounManager_CreateNoun(void* mgr, void* id);     // 0xb20c60
extern "C" void* SP_BehaviorManager();                                    // 0xb3d260
extern "C" void  LoadArithmeticaFile(int a, int b, void* p);              // 0x7f2240
extern "C" void  SP_cDirectPropertyList_GetIntProperty(void* p, int id);  // 0x6a2660
extern "C" void  EA_ConvertToString16(void* out, int value, int flags);    // 0x93c5a0

// raw vtable-slot fetch (for objects whose class stub is not worth declaring)
inline void* vs(void* p, int off) { return *(void**)((char*)*(void**)p + off); }

// the "visualizer / tribe" object shared by several 0xac8xxx helpers
struct CVis {
    char  pad0[0xa4];
    void* mpA4;                 // +0xa4
    char  pad1[0xbc - 0xa8];
    void* mpBC;                 // +0xbc
    char  pad1b[0x12c - 0xc0];
    int   m12c;                 // +0x12c
    char  pad2[0x160 - 0x130];
    int   m160;                 // +0x160
    int*  FUN_00ac84d0(int which);
    void  FUN_00ac86b0(int v);
    void  FUN_00ac8130();
    void  FUN_00ac84f0(IObj* p);
    void  FUN_00ac8cd0(int a, int b);
};
struct CCityVis2 { void CitizenNeedsRemoval(IObj* p); };
struct CReceiver  { void FUN_00d59200(IObj* p); };
struct CG         { void FUN_00d5bfa0(int b); };

struct CDirectPropertyList {
    void GetIntProperty(int id);          // 0x6a2660
};
extern CDirectPropertyList* g_15fd918;
extern "C" int   FUN_00cee370(void* self);                                // 0xcee370
extern "C" float FUN_00cee380(void* self);                                // 0xcee380
extern "C" void* FUN_00cee330(void* self);                                // 0xcee330
extern "C" void  FUN_00cee820(void* self, void* p);                       // 0xcee820
extern "C" void  FUN_00cee650(void* self, void* p);                       // 0xcee650
extern "C" void  FUN_00c35b40(void* self, float v);                       // 0xc35b40
extern "C" void  FUN_00c35b20(void* self, int a, float b);                // 0xc35b20
extern "C" int   FUN_00ac7790(int* self, int a, int b);                   // 0xac7790
extern "C" void  FUN_00ac79e0(int* self, void* p);                        // 0xac79e0

// ===========================================================================
// @ 0x00ac7ab0
// ===========================================================================
int COrder::FUN_00ac7ab0(float amount, COrder* order, int kind)
{
    int result = 0;
    if (amount == 0.0f) {
        return FUN_00ac7790((int*)order, 0, kind);
    }
    float f0 = FUN_00cee380(order);
    float fmax = order->d40();
    if (fmax < f0 + amount) amount = fmax - f0;

    COrder* end;
    if (this->field1c == 0) end = 0;
    else end = (COrder*)(this->field1c + 0x34);

    if (order != end) {
        COrder* p = order->vecBegin;
        COrder* q = order->vecEnd;
        for (; p != q; ++p) {
            int node = *(int*)p;
            float was = *(float*)(node + 0x134);
            float cur = order->d3c();
            cur -= was;
            if (*(int*)(node + 0x12c) == kind && cur > 1.5258789e-05f) {
                float take = (cur <= amount) ? cur : amount;
                FUN_00c35b40((void*)node, take + was);
                amount -= take;
                result = node;
            }
        }
    }
    if (amount > 1.5258789e-05f) {
        float unit = order->d3c();
        int n = (int)(amount / unit);
        if (amount / unit < (float)n) n--;
        int i = n;
        if (n > 0) {
            do {
                float u = order->d3c();
                if (FUN_00cee370(order) < order->field1c) {
                    void* mgr = SP_NounManager(0x18c431c);
                    int obj = (int)SP_cGameNounManager_CreateNoun(mgr, (void*)0x18c431c);
                    FUN_00c35b20((void*)obj, kind, u);
                    FUN_00cee820(order, (void*)obj);
                    order->d08(obj);
                    result = obj;
                } else {
                    result = 0;
                }
            } while (--i);
        }
        float unit2 = order->d3c();
        amount -= unit2 * n;
        if (amount > 1.5258789e-05f) {
            if (FUN_00cee370(order) < order->field1c) {
                void* mgr = SP_NounManager(0x18c431c);
                int obj = (int)SP_cGameNounManager_CreateNoun(mgr, (void*)0x18c431c);
                FUN_00c35b20((void*)obj, kind, amount);
                FUN_00cee820(order, (void*)obj);
                order->d08(obj);
                return obj;
            }
            result = 0;
        }
    }
    return result;
}

// ===========================================================================
// @ 0x00ac7d10
// ===========================================================================
float COrder::FUN_00ac7d10(float amount, int list, int node)
{
    float done = 0.0f;
    if (node != 0) {
        float cap = *(float*)(node + 0x134);
        if (amount < cap) {
            FUN_00c35b40((void*)node, cap - amount);
            return amount;
        }
        FUN_00ac79e0((int*)node, *(void**)(node + 0x128));
        return cap;
    }
    if (list != 0 && amount > 0.0f) {
        for (;;) {
            if (FUN_00cee330(this) == 0) break;
            void* n = FUN_00cee330(this);
            float r = FUN_00ac7d10(amount - done, 0, (int)n) + done;
            done = r;
            if (amount <= r) return r;
        }
    }
    return done;
}

// ===========================================================================
// @ 0x00ac7de0
// ===========================================================================
bool COrder::FUN_00ac7de0(COrder* order)
{
    if (!order) return false;
    if (FUN_00cee370(this) < order->field1c) {
        CSub* sub = (CSub*)this->m128;
        if (sub) {
            sub->e18();
            sub->e0c(this);
            FUN_00cee650(this, this);
        }
        float cap = this->m134;
        float was = FUN_00cee380(this);
        float cur = order->d40();
        if (cur < was + cap) {
            FUN_00c35b40(this, cur - was);
        }
        FUN_00cee820(this, this);
        order->d08((int)this);
        if (sub) {
            sub->e1c();
        }
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00ac7eb0
// ===========================================================================
void COrder::FUN_00ac7eb0(COrder* order)
{
    FUN_00ac7ab0(this->m134, order, this->m12c);
    FUN_00ac79e0((int*)this, this->m128);
}

// ===========================================================================
// @ 0x00ac7ef0
// ===========================================================================
bool COrder::FUN_00ac7ef0(int a, int b)
{
    if (!b || !a) return false;
    CSub* sub = (CSub*)this->m128;
    if (sub && sub->e14(0xce9f6639)) return false;
    int v;
    if (!sub) v = 0;
    else v = sub->e14(0x135b1e8);
    int other = (this->field1c == 0) ? 0 : (this->field1c + 0x34);
    if (v == other) return true;
    if (sub && sub->e14(0x4f396a66)) return true;
    return false;
}

// ===========================================================================
// @ 0x00ac7f80
// ===========================================================================
struct CNoun {
    virtual void n00();
    virtual void n04();
    virtual void n08(); virtual void n0c(); virtual void n10(); virtual void n14();
    virtual void n18(); virtual void n1c(); virtual void n20(); virtual void n24();
    virtual void n28(int v);
};
void COrder::FUN_00ac7f80()
{
    if (this->field1c == 0) {
        void* mgr = SP_NounManager(0x1906183);
        CNoun* obj = (CNoun*)SP_cGameNounManager_CreateNoun(mgr, (void*)0x1906183);
        CNoun* old = (CNoun*)this->field1c;
        if (obj != old) {
            if (obj) obj->n00();
            this->field1c = (int)obj;
            if (old) old->n04();
        }
        obj->n28(0);
    }
}

// ===========================================================================
// @ 0x00ac7fe0
// ===========================================================================
struct GonzagoSub {
    virtual void g00(); virtual void g04(); virtual void g08(); virtual void g0c();
    virtual void g10(); virtual void g14(); virtual void g18(); virtual void g1c();
    void* scalarDtor(byte flags);
};
extern "C" void SP_cGonzagoSubsystem_dtor(void* p);       // 0xb5b9a0
void* GonzagoSub::scalarDtor(byte flags)
{
    *(void**)this = (void*)0x1459fc8;
    *((void**)this + 1) = (void*)0x1459fc0;
    GonzagoSub* p = *(GonzagoSub**)((char*)this + 0x1c);
    if (p) p->g04();
    (*((void (__thiscall*)(void*))SP_cGonzagoSubsystem_dtor))(this);
    if (flags & 1) operator_delete(this);
    return this;
}

// ===========================================================================
// @ 0x00ac8050
// ===========================================================================
bool FUN_00ac8050(IObj* p, int value)
{
    void* buf[2];
    EA_ConvertToString16(buf, value, -1);
    bool ok = false;
    if (p->b00(*(void**)buf)) {
        if (p->b0c(L"**unsupported type**")) {
            if (p->b04(*(void**)(buf))) {
                ok = true;
            }
        }
    }
    int len = *(int*)((char*)buf + 4) - *(int*)((char*)buf);
    if (len > 2 && *(int*)((char*)buf)) operator_delete(*(void**)((char*)buf));
    return ok;
}

// ===========================================================================
// @ 0x00ac80d0
// ===========================================================================
IObj* FUN_00ac80d0(IObj* p, int id)
{
    if (p && p->b20() == id) return p;
    return 0;
}

// ===========================================================================
// @ 0x00ac8130
// ===========================================================================
extern "C" void* FUN_00b95050(void* self);                     // 0xb95050
extern "C" void* FUN_00b93810(void* self, float a, float b);   // 0xb93810
extern "C" void* FUN_00b93840(void* self, float a, float b);   // 0xb93840
extern "C" void* FUN_00b94a90(void* self, float a, float b);   // 0xb94a90
extern "C" void  FUN_00b981a0(void* self, int idx, void* v);   // 0xb981a0

void CVis::FUN_00ac8130()
{
    void* a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    void* ta = a ? FUN_00b95050(a) : 0;
    void* b = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    void* tb = b ? FUN_00b93810(b, 0x41a00000, 0x41f00000) : 0;
    FUN_00b981a0(ta, 1, tb);
    void* c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    void* tc = c ? FUN_00b93840(c, 0x40a00000, 0x41000000) : 0;
    FUN_00b981a0(ta, 3, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    b = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tb = b ? FUN_00b93810(b, 0x41700000, 0x41a00000) : 0;
    FUN_00b981a0(ta, 1, tb);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93840(c, 0x40800000, 0x41000000) : 0;
    FUN_00b981a0(ta, 6, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b94a90(c, 0x40800000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 6, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x40400000, 0x40e00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x40400000, 0x40e00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b94a90(c, 0x40800000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 4, tc);
    FUN_00b981a0(ta, 1, tb);
    a = operator_new6(0x34, "Simulator", 0, 0, 0, 0);
    ta = a ? FUN_00b95050(a) : 0;
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93810(c, 0x41700000, 0x41a00000) : 0;
    FUN_00b981a0(ta, 1, tc);
    c = operator_new6(0x10, "Simulator", 0, 0, 0, 0);
    tc = c ? FUN_00b93840(c, 0x41000000, 0x40c00000) : 0;
    FUN_00b981a0(ta, 6, tc);
    FUN_00b981a0(ta, 1, tb);
}

// ===========================================================================
// @ 0x00ac84d0
// ===========================================================================
int* CVis::FUN_00ac84d0(int which)
{
    int* r = (int*)((char*)this + 0x12c);
    if (which != 1) r = (int*)((char*)this + 0x160);
    return r;
}

// ===========================================================================
// @ 0x00ac84f0
// ===========================================================================
extern "C" void SP_cCityVisualizer_CitizenNeedsRemoval(void* self, void* p);  // 0xd58b10
extern "C" void FUN_00d59200(void* p);                                        // 0xd59200
void CVis::FUN_00ac84f0(IObj* p)
{
    if (p && p->b20() == (int)0x18eb4b7) {
        ((CCityVis2*)mpA4)->CitizenNeedsRemoval(p);
        ((CReceiver*)mpBC)->FUN_00d59200(p);
    }
}

// ===========================================================================
// @ 0x00ac8550
// ===========================================================================
extern "C" void SP_cVarListSerializer_ctor(void* self, void* a, void* b, int c);  // 0x692f90
extern "C" char SP_cVarListSerializer_Serialize(void* self, void* p);              // 0x692900
extern "C" char FUN_00b930c0(void* p);                                             // 0xb930c0
bool FUN_00ac8550(void* self, IObj* p)
{
    IObj* q = (IObj*)p->b20();
    uint32 tag = 0x1f73e49;
    void* stream = q->b18();
    WriteUint32(stream, &tag, 1, 0);
    char srl[0xa14];
    SP_cVarListSerializer_ctor(srl, self, (void*)0x1565d68, 0x1a80d26);
    if (SP_cVarListSerializer_Serialize(srl, p)) {
        if (FUN_00b930c0(p)) return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00ac8660
// ===========================================================================
void FUN_00ac8660(void)
{
    LoadArithmeticaFile(0x25e94602, 0x24a4f5a, (void*)0x167a3d0);
}

// ===========================================================================
// @ 0x00ac8690
// ===========================================================================
void FUN_00ac8690(void)
{
    g_15fd918->GetIntProperty(0x625bf68);
}

// ===========================================================================
// @ 0x00ac86b0
// ===========================================================================
void CVis::FUN_00ac86b0(int v)
{
    void* g = mpA4;
    if (g) *(int*)((char*)g + 0xa4c) = v;
}

// ===========================================================================
// @ 0x00ac8750
// ===========================================================================
bool FUN_00ac8750(SerObj* p, int value)
{
    Stream* s = p->a20();
    ReadBool(s->s18(), value);
    return true;
}

// ===========================================================================
// @ 0x00ac8780
// ===========================================================================
bool FUN_00ac8780(SerObj* p, char* pValue)
{
    Stream* s = p->a20();
    char c = *pValue;
    void* st = s->s18();
    bool b = (c != 0);
    WriteBool3(st, &b, 1);
    return true;
}

// ===========================================================================
// @ 0x00ac87c0
// ===========================================================================
bool FUN_00ac87c0(SerObj* p, int value)
{
    Stream* s = p->a20();
    FUN_00693890(s->s18(), value);
    return true;
}

// ===========================================================================
// @ 0x00ac87f0
// ===========================================================================
bool FUN_00ac87f0(SerObj* p, int value)
{
    Stream* s = p->a20();
    FUN_00692e50(s->s18(), value);
    return true;
}

// ===========================================================================
// @ 0x00ac88f0
// ===========================================================================
bool FUN_00ac88f0(SerObj* p, float* pValue)
{
    Stream* s = p->a20();
    float f = *pValue;
    void* st = s->s18();
    WriteUint32(st, &f, 1, 0);
    return true;
}

// ===========================================================================
// @ 0x00ac8930
// ===========================================================================
void __stdcall FUN_00ac8930(char* first, char* last)
{
    for (; first < last; first += 0xc) {
        IObj* p = (IObj*)first;
        p->b00(0);
    }
}

// ===========================================================================
// @ 0x00ac8980
// ===========================================================================
struct RefPtr {
    void* mp;
    RefPtr* assign(void** src);
};
RefPtr* RefPtr::assign(void** src)
{
    void* p = *src;
    mp = p;
    if (p) ((void (__thiscall*)(void*))vs(p, 0))(p);
    return this;
}

// ===========================================================================
// @ 0x00ac89e0
// ===========================================================================
struct CAnim {
    void AddRef();     // 0xa02c30
    void Release();    // 0xa05270
};
void** FUN_00ac89e0(void** first, void** last, void** out)
{
    while (first != last) {
        void* a = *first;
        void* b = *out;
        if (a != b) {
            if (a) ((CAnim*)a)->AddRef();
            *out = a;
            if (b) ((CAnim*)b)->Release();
        }
        ++first;
        ++out;
    }
    return out;
}

// ===========================================================================
// @ 0x00ac8a30
// ===========================================================================
void** FUN_00ac8a30(void* last_, void* first_, void** out)
{
    char* last = (char*)last_;
    char* first = (char*)first_;
    while (first != last) {
        void* a = *(void**)(first - 4);
        void* b = out[-1];
        first -= 4;
        --out;
        if (a != b) {
            if (a) ((CAnim*)a)->AddRef();
            *out = a;
            if (b) ((CAnim*)b)->Release();
        }
    }
    return out;
}

// ===========================================================================
// @ 0x00ac8a80
// ===========================================================================
void FUN_00ac8a80(int self, int idx)
{
    byte* base = *(byte**)(self + 8);
    base[idx * 0xc + 4] = 1;
    int* p = *(int**)(base + idx * 0xc + 8);
    if (*(char*)(self + 5) != 0) {
        int* bm = (int*)SP_BehaviorManager();
        int v = 0;
        if (p) v = (*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0x11c0ba3);
        (*(void (__thiscall*)(int*, int))((char*)*(void**)bm + 0x38))(bm, v);
    }
    if (*(char*)(self + 4) != 0) {
        if (!p) return;
        int* q = (int*)(*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0x116dd1b);
        if (q) {
            q[0x14] &= ~0x1000;
            *(byte*)((char*)q + 0x71) = 0;
            *(byte*)((char*)q + 0x75) = 1;
            *(byte*)((char*)q + 0x70) = 1;
            *(byte*)((char*)q + 0x6f) = 1;
            *(byte*)((char*)q + 0x77) = 1;
            int* r = (int*)(*(int (__thiscall*)(int*))((char*)*(void**)q + 0xac))(q);
            if (r) {
                r[1] |= 1;
                (*(void (__thiscall*)(int*, int))((char*)*(void**)r + 0x16c))(r, 1);
            }
        }
    }
    if (p && (*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0xce9f6639)) {
        int* w = (int*)(*(int (__thiscall*)(int*, uint32))((char*)*(void**)p + 0xc))(p, 0xce9f6639);
        if (*(int*)((char*)w + 0xb54)) {
            *(byte*)(*(int*)((char*)w + 0xb54) + 0x64) = 1;
        }
    }
}

// ===========================================================================
// @ 0x00ac8b60
// ===========================================================================
extern "C" char FUN_00c24560(void* p);                       // 0xc24560
extern "C" float FUN_00572a10(float a, float b);             // 0x572a10
extern "C" void SP_cSPCreatureCitizen_GiveOrder(void* self, int order, int a, int b); // 0xc275b0
extern "C" void FUN_00c0ba10(void* p);                       // 0xc0ba10
extern "C" void* SP_cSPCreatureCitizen_GetTribe(void* p);    // 0xc22f50
extern "C" float FUN_00c91c80(void* tribe);                  // 0xc91c80

extern uint32 DAT_0167a38c;
extern uint32 DAT_0167a388;
extern float  DAT_0167a364, DAT_0167a368, DAT_0167a36c, DAT_0167a370, DAT_0167a374;

void __stdcall FUN_00ac8b60(void* self)
{
    if (!self) return;
    if (!FUN_00c24560(self)) return;
    if ((int)DAT_0167a38c >= (int)DAT_0167a388) return;
    float f = FUN_00572a10(0.0f, 1.0f);
    if (f < DAT_0167a364) {
        SP_cSPCreatureCitizen_GiveOrder(self, 10, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (f < DAT_0167a368 + DAT_0167a364) {
        FUN_00c0ba10(self);
        SP_cSPCreatureCitizen_GiveOrder(self, 0, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (f < (DAT_0167a36c + DAT_0167a368) + DAT_0167a364) {
        FUN_00c0ba10(self);
        SP_cSPCreatureCitizen_GiveOrder(self, 6, 0, 0);
        DAT_0167a38c++;
        return;
    }
    if (((DAT_0167a370 + DAT_0167a36c) + DAT_0167a368) + DAT_0167a364 <= f) {
        if (f < (((DAT_0167a374 + DAT_0167a370) + DAT_0167a36c) + DAT_0167a368) + DAT_0167a364) {
            FUN_00c0ba10(self);
            SP_cSPCreatureCitizen_GiveOrder(self, 0xb, 0, 0);
            DAT_0167a38c++;
            return;
        }
    } else {
        void* tribe = SP_cSPCreatureCitizen_GetTribe(self);
        if (FUN_00c91c80(tribe) < 100.0f) {
            FUN_00c0ba10(self);
            SP_cSPCreatureCitizen_GiveOrder(self, 1, 0, 0);
            DAT_0167a38c++;
            return;
        }
    }
}

// ===========================================================================
// @ 0x00ac8cd0
// ===========================================================================
extern "C" void FUN_00d5bfa0(int v);                          // 0xd5bfa0
void CVis::FUN_00ac8cd0(int a, int b)
{
    void* g = mpA4;
    if (g && *(int*)((char*)g + 0xaf0) == a) {
        ((CG*)g)->FUN_00d5bfa0(b);
    }
}
