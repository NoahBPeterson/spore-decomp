// Slice s00f42a50 -- unnamed action/vector helpers + FunctionalMatch (bfs1 slice 6).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl eastl_alloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl eastl_free(void* p);                                                                   // 0x00f47380

// element whose stride is 0x34
struct T34 {
    char  pad00[0x1c];
    char* mpSub;                                   // +0x1c (owned buffer, header at -4)
    char  pad20[0x34 - 0x20];
    T34*  ConstructDefault();                          // 0xf280b0
    void  Construct(const T34&) throw();
};
struct Vec34 {
    T34* mpBegin; T34* mpEnd; T34* mpCapacity; char alloc[4];
    T34* insert(T34* pos, const T34& value);       // 0x00f42dc0
    void DoInsert(T34* pos, const T34& value);     // 0x00f2cd50
    void DoAssign(T34* pos, uint32_t n, const T34& value);   // 0x00f2cb50
    void eraseRange(T34* first, T34* last);        // 0x00f2cb00
    void resize(uint32_t n);                       // 0x00f42ef0
};

// @ 0x00f42dc0
T34* Vec34::insert(T34* pos, const T34& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T34* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// element whose stride is 0x4e0
struct T4e0 { char pad[0x4e0]; void Construct(const T4e0&) throw(); };
struct Vec4e0 {
    T4e0* mpBegin; T4e0* mpEnd; T4e0* mpCapacity; char alloc[4];
    T4e0* insert(T4e0* pos, const T4e0& value);    // 0x00f43880
    void DoInsert(T4e0* pos, const T4e0& value);   // 0x00f2df80
    void eraseRange(T4e0* first, T4e0* last);      // 0x00f2dd70
    Vec4e0* fillCtor(uint32_t n, const T4e0& value, const void* alloc);   // 0x00f42f90
    Vec4e0* rangeCtor(const Vec4e0& x);            // 0x00f42e60
    void swap(Vec4e0& other);                      // 0x00f437b0
    void dtor();                                   // 0x00dfcac0
    void assign(uint32_t n, const T4e0& value);    // 0x00f438f0
};
// fill(first, last, value), fill_n(first, n, value) and the vector's _Insert_n are
// plain cdecl helpers (the caller pops all arguments in one go).
void __cdecl fill4e0(T4e0* first, T4e0* last, const T4e0& value);         // 0x00f42a20
void __cdecl fill4e0n(T4e0* first, uint32_t n, const T4e0& value);        // 0x00f42780
void __cdecl assign4e0(T4e0* pos, uint32_t n, const T4e0& value);         // 0x00f42e30
// 0x00dfd570 uninitialized_copy for 0x4e0-stride elements (cursor returned via out-param)
extern "C" T4e0** __cdecl uninit_copy4e0(T4e0** out, const T4e0* first, const T4e0* last, T4e0* dest, const void* srcVec);

// @ 0x00f43880
T4e0* Vec4e0::insert(T4e0* pos, const T4e0& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T4e0* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// @ 0x00f42f90  vector(n, value, alloc)
Vec4e0* Vec4e0::fillCtor(uint32_t n, const T4e0& value, const void* alloc)
{
    (void)alloc;
    T4e0* p = n ? (T4e0*)eastl_alloc(n * 0x4e0, "Simulator", 0, 0,
                                     "eastl/allocator.h", 0xd1) : 0;
    uint32_t count = n;
    mpBegin = p;
    mpEnd = p;
    mpCapacity = (T4e0*)((char*)p + count * 0x4e0);
    T4e0* it = p;
    while (n > 0) {
        if (it)
            it->Construct(value);
        --n;
        it = (T4e0*)((char*)it + 0x4e0);
    }
    mpEnd = (T4e0*)((char*)mpBegin + count * 0x4e0);
    return this;
}

// element whose stride is 0x188; it owns a sub-vector at +0x18 (stride 0x44)
struct T188 {
    char   pad00[0x18];
    char*  mpSubBegin;   // +0x18
    char*  mpSubEnd;     // +0x1c
    char   pad20[0x188 - 0x20];
};
struct Vec188 {
    T188* mpBegin; T188* mpEnd; T188* mpCapacity; char alloc[4];
    T188* erase(T188* pos);   // 0x00f43740
};
void __cdecl eastl_copy188(T188* first, T188* last, T188* dest);  // 0x00dfd250
struct Sub { void destroy(); };                                   // 0x00f280f0

// @ 0x00f43740
T188* Vec188::erase(T188* pos)
{
    if ((char*)pos + 0x188 < (char*)mpEnd)
        eastl_copy188(pos + 1, mpEnd, pos);
    mpEnd = (T188*)((char*)mpEnd - 0x188);
    T188* last = mpEnd;
    char* end = last->mpSubEnd;
    for (char* it = last->mpSubBegin; it < end; it += 0x44)
        ((Sub*)(it + 4))->destroy();
    char* base = last->mpSubBegin;
    if (base != 0 && *(int*)(base - 4) != 0)
        eastl_free(base);
    return pos;
}

// @ 0x00f43830  erase element #idx from the 0x188 vector of the object returned by 0xf3be60
struct Obj188 {
    char   pad00[0x84];
    Vec188 vec;             // +0x84
};
void* __stdcall FUN_00f3be60(int a);   // 0x00f3be60
void __stdcall f_43830(int a, int idx)
{
    Obj188* o = (Obj188*)FUN_00f3be60(a);
    if (o != 0 && idx >= 0) {
        Vec188* v = &o->vec;
        int count = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x188);
        if (idx < count)
            v->erase((T188*)((char*)v->mpBegin + idx * 0x188));
    }
}

// ---------------------------------------------------------------- FunctionalMatch helpers
//
// The FunctionalMatch matching path was compiled with whole-program optimisation:
// 0x00f43010 receives its 3-dword return slot in `edi` and 0x00f42a50 receives the
// action object in `esi` plus its descriptor in `eax` -- neither has stack
// arguments.  Both are modelled below with explicit parameters, so their code
// cannot be byte-identical.  Every eastl container in this group is inlined in retail.

struct FmTriple {
    int32_t m00, m04, m08;
    void* Query(int32_t* key, float f);   // 0x00f3b5e0
};
struct FmQuad { int32_t m00, m04, m08, m0C; };

// inlined eastl string header (inside FmEntry at +0x10)
struct FmStr {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void  Destroy(void* begin, void* end);   // 0x4e39a0
};

// 0x24-byte lookup entry built by 0x558960
struct FmEntry {
    int32_t m00, m04, m08, m0C;   // +0x00
    FmStr   mStr;                 // +0x10
    int32_t m1C;                  // +0x1c
    int32_t m20;                  // +0x20
    FmEntry* Build(int32_t a, int32_t b, int32_t c);   // 0x558960
    void     Construct(const FmEntry& rhs);            // 0x606880
    void     Destroy();                                // 0x6066f0
};

// inlined eastl::vector<FmEntry>
struct FmEntryVec { FmEntry* mpBegin; FmEntry* mpEnd; FmEntry* mpCapacity; };
void __cdecl FmEntryVec_slow(FmEntryVec* v, FmEntry* end, FmEntry* value);   // 0x4e39d0
void __cdecl FmEntryVec_dtor(FmEntryVec* v);                                // 0x4e1780

static void fm_push(FmEntryVec* v, int32_t a, int32_t b, int32_t c)
{
    FmEntry tmp;
    FmEntry* e = tmp.Build(a, b, c);
    if (v->mpEnd < v->mpCapacity) {
        FmEntry* p = v->mpEnd++;
        if (p != 0)
            p->Construct(*e);
    } else {
        FmEntryVec_slow(v, v->mpEnd, e);
    }
    tmp.Destroy();
}

// COM-style release through vtable slot 1
static void fm_release(void* p)
{
    if (p != 0)
        ((void(__thiscall*)(void*))(*((char**)*(void**)p + 1)))(p);
}

// result holder used by 0xf42670
struct FmCode {
    int32_t m00;
    void Ctor();    // 0x00f28b30
    void Dtor();    // 0x00f280f0
};
struct FmApplyTarget {
    void Apply(int32_t n, FmCode* code);   // 0x00f42670
};

// description blob behind 0x00401090's result (only the fields touched here)
struct FmObj544 {
    char    pad000[0x544];
    int32_t m544;                       // +0x544 (int -> float)
    char    pad548[0x57C - 0x548];
    int32_t m57C;                       // +0x57c
    char    pad580[0x59C - 0x580];
    float   f59C;                       // +0x59c
    char    pad5A0[0x5AC - 0x5A0];
    float   f5AC;                       // +0x5ac
    float   f5B0;                       // +0x5b0
    FmObj544* FUN_004df550();           // 0x004df550
};
struct FmObj401090 {
    FmObj544* FUN_004df550();   // 0x004df550
};

struct FmSub5A8 {
    void BFC470(uint32_t v);    // 0x00bfc470
};
struct FmAvatar { char pad00[0x5A8]; FmSub5A8 m5A8; };
struct FmNounMgr {
    void* B1FDB0();             // 0x00b1fdb0
};

// per-frame match context reached through builder+0x10
struct FmCtx {
    char    pad000[0x128];
    char*   m128; char* m12C;           // +0x128  vector<0xc> begin/end
    int32_t m130, m134, m138;           // +0x130  current triple
    char    pad13C[0x150 - 0x13C];
    int32_t m150, m154, m158;           // +0x150  applied triple
    int32_t m15C, m160, m164, m168;     // +0x15c  applied quad
    float   f16C;                       // +0x16c
    int32_t m170;
    uint8_t m174;                       // +0x174
    char    pad175[0x178 - 0x175];
    char*   m178; char* m17C;           // +0x178  vector<0x38> begin/end
};

struct FmRecord {
    int32_t m00;                        // +0x00 (-2 sentinel)
    int32_t m04, m08, m0C;              // +0x04
    int32_t m10, m14, m18, m1C;         // +0x10
    float   f20;                        // +0x20
    char    pad24[0x234 - 0x24];
};

struct FmBuilder {
    char      pad00[0x10];
    FmCtx*    mp10;                     // +0x10
    char      pad14[0x8C - 0x14];
    FmRecord* mp8C;                     // +0x8c
    char      pad90[0x128 - 0x90];
    char*     m128; char* m12C;         // +0x128  vector<0xc> begin/end
    FmRecord* Build(const FmTriple& a, const FmQuad& b);   // 0x00f43420
};

// action object initialised by 0x00f42a50
struct ActionDesc { char pad00[4]; uint32_t m04; };
struct Action {
    uint8_t b000, b001, b002;
    char    pad003[1];
    int32_t m004;                       // +0x004
    char    pad008[0x170 - 0x008];
    int32_t m170;                       // +0x170
    char    pad174[0x484 - 0x174];
    float   f484;                       // +0x484
    char    pad488[0x48C - 0x488];
    float   f48C;                       // +0x48c
    float   f490;                       // +0x490
    char    pad494[4];
    void*   p498;                       // +0x498
    void*   p49C;                       // +0x49c
    void*   p4A0;                       // +0x4a0
    int32_t m4A4;                       // +0x4a4
    int32_t m4A8, m4AC, m4B0, m4B4, m4B8;   // +0x4a8
};

bool  FUN_004bbe20(void* a, int32_t b);                                  // 0x004bbe20
void  FUN_00eef810(void* out, int32_t tag, int32_t a, int32_t b);        // 0x00eef810
void* FUN_0067cb40(void);                                                // 0x0067cb40
void* FUN_0067dcd0(void);                                                // 0x0067dcd0
void* FUN_0067de30(void);                                                // 0x0067de30
void* FUN_00401090(const void* desc);                                    // 0x00401090
void* FUN_00b3d300(void);                                                // 0x00b3d300
void  FUN_00f3c1d0(const void* desc, void* a, void* b, void* c);         // 0x00f3c1d0
void  FUN_006a08b0(void* src, int32_t tag, void** arr, int32_t* count);  // 0x006a08b0
void  FUN_00f3fa20(void* dst, int32_t a);                                // 0x00f3fa20
void  FUN_00f3da90(void* self, FmRecord* rec, int32_t a);                // 0x00f3da90
void* FUN_00f2aac0(void* rec);                                           // 0x00f2aac0

extern float   g_148d33c;   // 0x0148d33c
extern void*   g_15b052c;   // 0x015b052c
extern int32_t g_16c8974;   // 0x016c8974
extern int32_t g_16c8964;   // 0x016c8964
extern int32_t g_16c8954;   // 0x016c8954
extern float   g_16c89a4;   // 0x016c89a4
extern float   g_16c8994;   // 0x016c8994
extern float   g_16c8984;   // 0x016c8984

// @ 0x00f42a50
// NOTE: retail takes the action object in `esi` and its descriptor in `eax`
// (whole-program register ABI).  Modelled with explicit parameters.
void __cdecl f_42a50(Action* self, const ActionDesc* desc)
{
    self->f484 = 0.0f;
    self->m4A8 = 1;
    self->m4AC = 1;
    self->m4B0 = 1;
    self->m4B4 = 1;
    self->m4B8 = 1;
    self->m4A4 = -1;
    self->b001 = 0;
    self->b002 = 0;

    FUN_00f3c1d0(desc, &self->p49C, &self->p498, &self->p4A0);

    FmCode code;
    code.Ctor();
    code.m00 = 2;

    switch (desc->m04) {
    case 0x2399be55: {
        self->b001 = 1;
        self->f48C = g_148d33c;
        void* obj = FUN_0067de30();
        void* sub = 0;
        void* arr = 0;
        int32_t count = 0;
        ((void(__thiscall*)(void*, uint32_t, void*, void**))(*((char**)*(void**)obj + 11)))(obj, 0x2980610e, g_15b052c, &sub);
        if (sub != 0) {
            FUN_006a08b0(sub, 0xf69d44ec, &arr, &count);
            if (arr != 0 && count > 0)
                self->f48C = ((float*)arr)[count - 1];
            fm_release(sub);
        }
        break;
    }
    case 0x2b978c46: {
        void* holder = FUN_00401090(desc);
        FmObj544* o = ((FmObj401090*)holder)->FUN_004df550();
        if (o != 0) {
            if (o->f5AC > o->f5B0)
                self->m4AC = 0;
            else if (o->f5B0 > o->f5AC)
                self->m4AC = 5;
            else
                self->m4AC = 4;

            float t = o->f59C;
            if (t >= (float)g_16c8974)
                self->f484 = g_16c89a4;
            else if (t >= (float)g_16c8964)
                self->f484 = g_16c8994;
            else if (t >= (float)g_16c8954)
                self->f484 = g_16c8984;

            self->f490 = (float)o->m544;
            self->m4B8 = 3;

            uint32_t k = (uint32_t)o->m57C;
            bool hit = (k == 0x372e2c04 || k == 0x9ea3031a || k == 0xccc35c46 ||
                        k == 0x4178b8e8 || k == 0x65672ade);
            code.m00 = hit ? 0 : 1;
        }
        break;
    }
    case 0x24682294:
    case 0x476a98c7: {
        self->m4AC = 3;
        void* obj = FUN_0067dcd0();
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, void*, void**, int, int, int, int))(*((char**)*(void**)obj + 3)))(obj, (void*)desc, &out, 0, 0, 0, 0);
        if (ok && out != 0) {
            void* r = ((void*(__thiscall*)(void*, uint32_t))(*((char**)*(void**)out + 3)))(out, 0x3c609f8);
            int32_t k = *(int32_t*)((char*)r + 0x18);
            switch (k) {
            case 0xbc1041e6: case 0x8f963dcb: case 0x9ad7d4aa: case 0xc15695da:
            case 0xf670aa43: case 0x1f2a25b6: case 0x2a5147a9: case 0x7d433fad:
                self->f484 = g_16c8994;
                break;
            case 0x1a4e0708: case 0x98e03c0d: case 0x441cd3e6: case 0x2090a11b:
            case 0x449c040f:
                self->f484 = g_16c89a4;
                break;
            default:
                break;
            }
        }
        fm_release(out);
        break;
    }
    default:
        break;
    }

    ((FmApplyTarget*)&self->m170)->Apply(5, &code);
    ((FmApplyTarget*)&self->m004)->Apply(5, &code);
    code.Dtor();
}

// @ 0x00f42e60
Vec4e0* Vec4e0::rangeCtor(const Vec4e0& x)
{
    uint32_t n = (uint32_t)(((char*)x.mpEnd - (char*)x.mpBegin) / 0x4e0);
    T4e0* p;
    if (n)
        p = (T4e0*)eastl_alloc(n * 0x4e0, "Simulator", 0, 0, "eastl/allocator.h", 0xd1);
    else
        p = 0;
    mpBegin = p;
    mpEnd = p;
    mpCapacity = (T4e0*)((char*)p + n * 0x4e0);
    T4e0* result;
    uninit_copy4e0(&result, x.mpBegin, x.mpEnd, p, &x);
    mpEnd = result;
    return this;
}

// @ 0x00f42ef0
void Vec34::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        T34 tmp;
        T34* pv = tmp.ConstructDefault();
        DoAssign(mpEnd, n - (uint32_t)(mpEnd - mpBegin), *pv);
        if (tmp.mpSub != 0 && *(int*)(tmp.mpSub - 4) != 0)
            eastl_free(tmp.mpSub);
    } else {
        eraseRange(mpBegin + n, mpEnd);
    }
}

// @ 0x00f43010
// NOTE: retail receives the 3-dword return slot in `edi` (whole-program register
// ABI; no stack arguments).  Modelled as a by-value struct return.
FmTriple __cdecl f_43010(void)
{
    FmEntryVec v;
    v.mpBegin = v.mpEnd = v.mpCapacity = 0;

    fm_push(&v, 0x02dc9d1e, 0, 0x4178b8e8);
    fm_push(&v, 0x54a32960, 0, 1);
    fm_push(&v, 0x03cc89b1, 0, 0x913b23be);

    FmTriple out;
    out.m00 = out.m04 = out.m08 = 0;

    void* q = FUN_0067cb40();
    bool ok = ((bool(__thiscall*)(void*, FmTriple*, FmEntryVec*, int))(*((char**)*(void**)q + 12)))(q, &out, &v, 1);
    if (ok && v.mpBegin != v.mpEnd) {
        out.m00 = v.mpBegin->m00;
        out.m04 = v.mpBegin->m04;
        out.m08 = v.mpBegin->m08;
    }
    FmEntryVec_dtor(&v);
    return out;
}

// result blob written by 0x00eef810: the object handle is the first dword
struct FmLookupResult { int32_t m00, m04, m08, m0C; };

// @ 0x00f43200
bool __cdecl f_43200(FmTriple* out, void* a, int32_t b)
{
    bool result = false;
    if (FUN_004bbe20(a, 0)) {
        FmEntryVec v;
        v.mpBegin = v.mpEnd = v.mpCapacity = 0;

        if (b == -1)
            fm_push(&v, 0x02dd90af, 0, (int32_t)(size_t)a);
        else
            fm_push(&v, 0x02dc9d1e, 0, b);
        fm_push(&v, 0x03cc89b1, 0, 0x913b23be);
        fm_push(&v, 0x54a32960, 0, 1);

        FmTriple tmp;
        tmp.m00 = tmp.m04 = tmp.m08 = 0;

        void* q = FUN_0067cb40();
        bool ok = ((bool(__thiscall*)(void*, FmTriple*, FmEntryVec*, int))(*((char**)*(void**)q + 12)))(q, &tmp, &v, 1);
        if (ok) {
            out->m00 = tmp.m00;
            out->m04 = tmp.m04;
            out->m08 = tmp.m08;
            result = true;
        } else if (b != -1) {
            result = f_43200(out, a, -1);
        }
        FmEntryVec_dtor(&v);
    } else {
        FmLookupResult r;
        FUN_00eef810(&r, 0x6031c03a, 0, 0);
        if (r.m00 != 0) {
            out->m00 = r.m00;
            out->m04 = r.m04;
            out->m08 = r.m08;
            result = true;
        }
    }
    return result;
}

// @ 0x00f43420
FmRecord* FmBuilder::Build(const FmTriple& a, const FmQuad& b)
{
    if (mp8C != 0) {
        mp8C->m04 = a.m00;
        mp8C->m08 = a.m04;
        mp8C->m0C = a.m08;
        mp8C->m10 = b.m00;
        mp8C->m14 = b.m04;
        mp8C->m18 = b.m08;
        mp8C->m1C = b.m0C;
        FUN_00f3da90(this, mp8C, 1);
        return mp8C;
    }

    FmCtx* ctx = mp10;
    ctx->m150 = a.m00;
    ctx->m154 = a.m04;
    ctx->m158 = a.m08;
    ctx->m15C = b.m00;
    ctx->m160 = b.m04;
    ctx->m164 = b.m08;
    ctx->m168 = b.m0C;

    FmRecord* rec = (FmRecord*)eastl_alloc(0x234, (const char*)0x148d340, 0, 0, (const char*)0, 0);
    if (rec != 0)
        rec = (FmRecord*)FUN_00f2aac0(rec);
    mp8C = rec;

    rec->m00 = -2;
    rec->m04 = ctx->m150;
    rec->m08 = ctx->m154;
    rec->m0C = ctx->m158;
    rec->m10 = ctx->m15C;
    rec->m14 = ctx->m160;
    rec->m18 = ctx->m164;
    rec->m1C = ctx->m168;
    rec->f20 = ctx->f16C;

    bool build = false;
    if (ctx->m130 == 0) {
        build = true;
    } else {
        void* o = FUN_0067dcd0();
        bool ok = ((bool(__thiscall*)(void*, int32_t*, int, int, int, int, int))(*((char**)*(void**)o + 3)))(o, &ctx->m130, 0, 0, 0, 0, 0);
        if (!ok)
            build = true;
    }
    if (build) {
        FmTriple t = f_43010();
        ctx->m130 = t.m00;
        ctx->m134 = t.m04;
        ctx->m138 = t.m08;
    }

    FUN_00f3fa20(&ctx->m130, 0);
    FUN_00f3da90(this, mp8C, 0);

    {
        uint32_t flag = ctx->m174;
        void* nm = FUN_00b3d300();
        void* avatar = ((FmNounMgr*)nm)->B1FDB0();
        ((FmAvatar*)avatar)->m5A8.BFC470(flag);
    }

    int32_t total = (int32_t)((ctx->m17C - ctx->m178) / 0x38);
    if (total > 0) {
        int32_t left = (int32_t)((m12C - m128) / 0xC);
        for (int32_t i = 0; i < total; ++i) {
            char* e = (char*)ctx->m178 + i * 0x38;
            FmTriple t;
            t.m00 = *(int32_t*)(e + 0);
            t.m04 = *(int32_t*)(e + 4);
            t.m08 = *(int32_t*)(e + 8);
            if (*(int32_t*)(e + 0x20) == 0 && left > 0) {
                int32_t n = (int32_t)((m12C - m128) / 0xC);
                char* s = (char*)m128 + (n - left) * 0xC;
                t.m00 = *(int32_t*)(s + 0);
                t.m04 = *(int32_t*)(s + 4);
                t.m08 = *(int32_t*)(s + 8);
                --left;
            }
            void* q = t.Query(&rec->m04, rec->f20);
            if (q != 0) {
                void* r = ((void*(__thiscall*)(void*, uint32_t))(*((char**)*(void**)q + 3)))(q, 0x13f94d4);
                if (r != 0)
                    ((FmSub5A8*)r)->BFC470(ctx->m174);
            }
        }
    }
    return mp8C;
}

// @ 0x00f438f0
void Vec4e0::assign(uint32_t n, const T4e0& value)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        struct { Vec4e0 v; char pad[4]; } tmp;
        tmp.v.fillCtor(n, value, &alloc[0]);
        swap(tmp.v);
        tmp.v.dtor();
    } else if (n > (uint32_t)(mpEnd - mpBegin)) {
        fill4e0(mpBegin, mpEnd, value);
        assign4e0(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
        uint32_t count = (uint32_t)(mpEnd - mpBegin);
        mpEnd = (T4e0*)((char*)mpEnd + (n - count) * 0x4e0);
    } else {
        fill4e0n(mpBegin, n, value);
        eraseRange((T4e0*)((char*)mpBegin + n * 0x4e0), mpEnd);
    }
}
