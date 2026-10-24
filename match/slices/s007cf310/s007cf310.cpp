// Slice s007cf310 (w2g5 slice 8).  Region: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// eastl vector/map instances, small factories, allocation helpers, map insert/find,
// property-model compilation and an EA::IO serialization cluster.
#include "types.h"

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
extern "C" void* __cdecl EAlloc(uint32_t, const char*, int, int, const char*, int);
extern "C" void  __cdecl EFree(void*);

// ---------------------------------------------------------------- extern callees
extern "C" void __cdecl FUN_004b5440();
extern "C" void __cdecl FUN_004b54b0(void*);
extern "C" const char s_vec16[];   // 0x13ebb38 allocator.h site string
extern "C" const char n_vec16[];   // 0x13ebc58 "App"
extern "C" void* __cdecl FUN_007cde30(void*, void*, void*);   // uninitialized copy (ret dst)
extern "C" void  __cdecl FUN_007cede0(void*, void*, void*);   // uninitialized copy (no ret)
extern "C" void  __cdecl FUN_007ceec0(void*, void*, void*);   // shift range back
extern "C" void* __cdecl FUN_00ec4ac0(void*, void*, void*, int);   // lower_bound (map A)
extern "C" void* __cdecl FUN_007c8160(void*, void*, void*, int);   // lower_bound (map B)
extern "C" void  __cdecl FUN_007cf630(unsigned);                   // Vec8::resize
extern "C" void  __cdecl FUN_00d018d0(void*, void*);               // vector erase
extern "C" void  __cdecl FUN_007cfae0(void*, void*);               // PtrX2::reset helper
extern "C" void  __cdecl FUN_007cabc0(void*, void*);               // vector_map insert
extern "C" void  __cdecl FUN_006130e0(void*, void*);               // vector<bool> clear
extern "C" void  __cdecl FUN_00ac9480(void*);
extern "C" void* __cdecl FUN_0067dcd0_GetManager();
extern "C" void* __cdecl FUN_0067dd60();
extern "C" void* __cdecl SP_EffectsManager();
extern "C" bool  __cdecl SP_GetPropertyAsKey(void*, int, void*);

// placement new: only used so that a ref-counted field copy emits the original's
// external copy-constructor call instead of expanding the addref inline.
inline void* operator new(unsigned, void* p) { return p; }
struct AutoRef {
    void* p;
    AutoRef() {}
    AutoRef(const AutoRef& o) {
        p = o.p;
        if (p)
            _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
    }
};
// A ref-counted pointer field whose copy must go through the external constructor.
struct RefField {
    void* p;
    void ctor(const RefField& src);
};

// ---------------------------------------------------------------- shared layouts
// A generic eastl vector prefix.  Member functions declared here exist only to
// produce the original's __thiscall call sites (they are defined in the binary).
struct VecCommon {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
    void destructRange(void* first, void* last);   // 0x007cefd0  (thiscall, ret 8)
    void destroy();                                // 0x007cef60  (~vector)
};
struct Pair8   { uint32_t key, sub; };                 // 8-byte key view of a map element
struct MapElem { unsigned ka, kb; AutoRef ref; unsigned d; };   // 16-byte map element
struct ResKey  { unsigned a, b, c; };                  // 12-byte resource key passed by value
struct Id2     { int a, b; };
struct Vec3    { void* begin; void* end; void* cap; }; // plain 3-pointer vector
struct Elem16  { unsigned a, b, kind, d; };            // 16-byte property-model element
struct Slot8   { uint32_t a, b; };

static void AddRef(void* p)
{
    if (p)
        _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1);
}


// ===========================================================================
// 0x007cf310  Vec16::insert(pos,n,value)
// ===========================================================================
struct E16 { unsigned a, b, c, d; };
extern "C" void* __cdecl UninitCopy16(E16** out, E16* first, E16* last, E16* dst, E16* pos);
extern "C" E16*  __cdecl eastl_copy_backward(E16* first, E16* last, E16* dst);
extern "C" void  __cdecl eastl_fill_n(E16* dst, unsigned n, const E16* value, E16* pos);
extern "C" void  __cdecl eastl_fill(E16* first, E16* last, const E16* value);
extern "C" E16*  __cdecl eastl_move(E16* first, E16* last, E16* dst);

struct Vec16 {
    E16*  mpBegin;   // +0x0
    E16*  mpEnd;     // +0x4
    E16*  mpCap;     // +0x8
    char  pad0c[4];  // +0xc
    E16*  mpInline;  // +0x10
    void insert(E16* pos, unsigned n, const E16* pv);
};
// @ 0x007cf310
void Vec16::insert(E16* pos, unsigned n, const E16* pv)
{
    if (n <= (unsigned)(mpCap - mpEnd)) {
        if (n > 0) {
            E16 t = *pv;
            unsigned nx = (unsigned)(mpEnd - pos);
            E16* oe = mpEnd;
            if (n < nx) {
                UninitCopy16((E16**)&pv, oe - n, oe, oe, pos);
                mpEnd += n;
                eastl_copy_backward(pos, oe - n, oe);
                eastl_fill(pos, pos + n, &t);
            } else {
                eastl_fill_n(oe, n - nx, &t, pos);
                mpEnd += n - nx;
                E16* p0 = pos;
                UninitCopy16((E16**)&pos, p0, oe, mpEnd, p0);
                mpEnd += nx;
                eastl_fill(p0, oe, &t);
            }
        }
    } else {
        unsigned old = (unsigned)(mpEnd - mpBegin);
        unsigned nc = old > 0 ? 2 * old : 1;
        unsigned want = old + n;
        if ((int)nc <= (int)want) { nc = want; } else { want = nc; }
        E16* nb = want ? (E16*)EAlloc(want * sizeof(E16), n_vec16, 0, 0, s_vec16, 0xd1) : 0;
        E16* np = eastl_move(mpBegin, pos, nb);
        eastl_fill_n(np, n, pv, pos);
        np = eastl_move(pos, mpEnd, np + n);
        if (mpBegin && mpBegin != mpInline)
            EFree(mpBegin);
        mpBegin = nb; mpEnd = np; mpCap = nb + want;
    }
}

// ===========================================================================
// 0x007cf4b0  V16::clear
// ===========================================================================
struct V16 {
    void* mBegin;    // +0
    void* mEnd;      // +4
    void* mCap;      // +8
    void* mMid;      // +0xc  (object whose dtor is FUN_007cef60)
    void* mInline;   // +0x10
    void clear();
};
// @ 0x007cf4b0
void V16::clear()
{
    ((VecCommon*)this)->destructRange(mBegin, mEnd);
    if (mBegin)
        EFree(mBegin);
}

// ===========================================================================
// 0x007cf4e0  Big2::dtor
// ===========================================================================
struct Big2 {
    char   pad00[4];
    void*  m04;          // +0x04
    char   pad08[0x1c - 0x08];
    V16    m1c;          // +0x1c
    char   pad28[0x34 - 0x28];
    void*  m34;          // +0x34
    void*  m38;          // +0x38
    char   pad3c[0x4c - 0x3c];
    void*  m4c;          // +0x4c
    void dtor();
};
// @ 0x007cf4e0
void Big2::dtor()
{
    FUN_004b5440();
    if (m4c)
        EFree(m4c);
    ((VecCommon*)((char*)this + 0x34))->destructRange(m34, m38);
    if (m34)
        EFree(m34);
    ((VecCommon*)((char*)this + 0x1c))->destroy();
    if (m04)
        EFree(m04);
}

// ===========================================================================
// 0x007cf5d0  createBig
// ===========================================================================
struct Big {
    int f0, f4, f8, fc;
    char p10[0xc];
    int f1c, f20, f24;
    char p28[0xc];
    int f34, f38, f3c;
    char p40[0xc];
    int f4c, f50, f54;
    char p58[0xc];
    int f64, f68, f6c;
    char p70[8];
};
Big** __fastcall createBig(Big** out)
{
    Big* p = (Big*)EAlloc(0x78, "App", 0, 0, 0, 0);
    if (p) {
        p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fc = 0;
        p->f1c = 0; p->f20 = 0; p->f24 = 0;
        p->f34 = 0; p->f38 = 0; p->f3c = 0;
        p->f4c = 0; p->f50 = 0; p->f54 = 0;
        p->f64 = 0; p->f68 = 0; p->f6c = 0;
        *out = p;
        return out;
    }
    *out = 0;
    return out;
}

// ===========================================================================
// 0x007cf630  Vec8::resize
// ===========================================================================
struct Vec8 {
    Slot8* mpBegin;
    Slot8* mpEnd;
    Slot8* mpCap;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void insert(Slot8* pos, uint32_t n, const Slot8& value);   // 0x007cf030 external
    void erase(Slot8* first, Slot8* last);                     // 0x00d018d0 external
    void resize(uint32_t n);
};
void Vec8::resize(uint32_t n)
{
    if (n > size()) {
        Slot8 z;
        z.a = 0;
        z.b = 0;
        insert(mpEnd, n - size(), z);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// 0x007cf570  map A insert-at (helper of 007cf690)
// ===========================================================================
struct MapX {
    void*  mpTree;    // +0
    void*  mpBegin;   // +4  (end of the node vector)
    char   pad8[0x14 - 8];
    bool   mb14;      // +0x14
    char   pad15[0x18 - 0x15];
    void*  mpRoot;    // +0x18
    Pair8* insertAt(void* pos, Pair8* kv);
    Pair8* findOrInsert(char* out, Pair8* kv);
};
// @ 0x007cf570
Pair8* MapX::insertAt(void* pos, Pair8* kv)
{
    unsigned cap = (unsigned)((char*)mpBegin - (char*)mpTree) >> 4;
    unsigned want = cap == 0 ? 1 : cap * 2;
    void* nb = want ? EAlloc(want * 0x10, n_vec16, 0, 0, s_vec16, 0xd1) : 0;
    void* a = FUN_007cde30(mpTree, pos, nb);
    FUN_007cede0(mpTree, pos, nb);
    if (a) {
        MapElem* d = (MapElem*)a;
        MapElem* s = (MapElem*)kv;
        d->ka = s->ka;
        d->kb = s->kb;
        new (&d->ref) AutoRef(s->ref);
    }
    void* e = FUN_007cde30(pos, mpBegin, (char*)a + 0x10);
    FUN_007cede0(pos, mpBegin, (char*)a + 0x10);
    if (mpTree)
        EFree(mpTree);
    mpTree = nb;
    mpBegin = e;
    mpRoot = (char*)nb + want * 0x10;
    return (Pair8*)0;
}

// ===========================================================================
// 0x007cf690  map A find-or-insert result
// ===========================================================================
// @ 0x007cf690
Pair8* MapX::findOrInsert(char* out, Pair8* kv)
{
    void* end = mpBegin;
    Pair8* r = (Pair8*)FUN_00ec4ac0(mpTree, end, kv, mb14);
    if ((void*)r != end) {
        Pair8* k = kv;
        if (r->sub < k->sub)
            goto doInsert;
        if (r->sub == k->sub) {
            if (r->key < k->key)
                goto doInsert;
        }
        *(Pair8**)out = r;
        out[4] = 0;
        return (Pair8*)out;
    }
doInsert:
    {
        Pair8* ins = this->insertAt(r, kv);
        *(Pair8**)out = ins;
        out[4] = 1;
        return (Pair8*)out;
    }
}

// ===========================================================================
// 0x007cf760  map B insert-pair
// ===========================================================================
struct MapY {
    void* mpTree;    // +0
    void* mpEnd;     // +4
    void* mpRoot;    // +8
    void insertPair(void* pos, void* value);
};
// @ 0x007cf760
void MapY::insertPair(void* pos, void* value)
{
    void* p = mpEnd;
    if (p != mpRoot) {
        if (pos <= value && value < p)
            value = (char*)value + 0x10;
        if (p) {
            MapElem* d = (MapElem*)p;
            MapElem* s = (MapElem*)((char*)p - 0x10);
            d->ka = s->ka;
            d->kb = s->kb;
            new (&d->ref) AutoRef(s->ref);
        }
        FUN_007ceec0(pos, (char*)p - 0x10, p);
        {
            MapElem* d = (MapElem*)pos;
            MapElem* s = (MapElem*)value;
            d->ka = s->ka;
            d->kb = s->kb;
        }
        ((RefField*)((char*)pos + 8))->ctor(*(RefField*)((char*)value + 8));
        mpEnd = (char*)p + 0x10;
        return;
    }
    {
        unsigned old = (unsigned)((char*)p - (char*)mpTree) >> 4;
        unsigned want = old == 0 ? 1 : old * 2;
        void* nb = want ? EAlloc(want * 0x10, n_vec16, 0, 0, s_vec16, 0xd1) : 0;
        void* a = FUN_007cde30(mpTree, pos, nb);
        FUN_007cede0(mpTree, pos, nb);
        if (a) {
            MapElem* d = (MapElem*)a;
            MapElem* s = (MapElem*)value;
            d->ka = s->ka;
            d->kb = s->kb;
            new (&d->ref) AutoRef(s->ref);
        }
        void* b = FUN_007cde30(pos, mpEnd, (char*)a + 0x10);
        FUN_007cede0(pos, mpEnd, (char*)a + 0x10);
        if (mpTree)
            EFree(mpTree);
        mpTree = nb;
        mpEnd = b;
        mpRoot = (char*)nb + want * 0x10;
    }
}

// ===========================================================================
// 0x007cf8d0  MapZ::setSlot
// ===========================================================================
struct MapZ {
    char    pad0[8];
    Slot8*  mpBegin;   // +8
    Slot8*  mpEnd;     // +0xc
    char    pad10[0x1c - 0x10];
    int     m1c;       // +0x1c
    int     m20;       // +0x20
    bool setSlot(int handle, uint32_t* rec);
};
// @ 0x007cf8d0
bool MapZ::setSlot(int handle, uint32_t* rec)
{
    if (handle != m1c)
        return false;
    uint32_t u = rec[0];
    int i = rec[10], a = rec[2], idx = rec[8];
    if (a != 0 && i != 0) {
        if (mpBegin == mpEnd)
            FUN_007cf630((unsigned)i);
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx].a == 0)
            m20 = m20 + 1;
        mpBegin[idx].a = a;
        mpBegin[idx].b = u;
        return true;
    }
    if (mpBegin != mpEnd) {
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx].a != 0)
            m20 = m20 - 1;
        mpBegin[idx].a = 0;
        mpBegin[idx].b = 0;
        if (m20 == 0)
            FUN_00d018d0(mpBegin, mpEnd);
    }
    return true;
}

// ===========================================================================
// 0x007cf9b0  ObjX2::clear
// ===========================================================================
struct IObj {
    virtual bool probe();                 // +0x10
    virtual void fillTmp(void* t);        // +0x14
};
struct RefPtr {
    void* p;          // +0
    int   refs;       // +4
    void release() {
        if (p)
            ((void(__thiscall*)(void*))*(void**)(*(char**)p + 4))(p);
    }
};
struct ObjX2 {
    int   m0;             // +0
    char  pad04[0x1c - 4];
    void* m1c;            // +0x1c  begin
    void* m20;            // +0x20  end
    char  pad24[0x34 - 0x24];
    void* m34;            // +0x34  begin
    void* m38;            // +0x38  end
    void  clear();
};
// @ 0x007cf9b0
void ObjX2::clear()
{
    m0 = 0;
    for (char* e = (char*)m1c; e != (char*)m20; e += 0x10) {
        IObj* o = *(IObj**)(e + 8);
        if (!o)
            continue;
        if (!o->probe()) {
            m0 = m0 + 1;
            continue;
        }
        RefPtr tmp;
        tmp.p = 0;
        tmp.refs = 0;
        o->fillTmp(&tmp);
        FUN_004b54b0(&tmp);
        IObj* q = *(IObj**)(e + 8);
        if (q) {
            *(void**)(e + 8) = 0;
            ((void(__thiscall*)(void*))*(void**)(*(char**)q + 4))(q);
        }
        tmp.refs = -1;
        tmp.release();
    }
    for (char* e = (char*)m34; e != (char*)m38; e += 0x10) {
        RefPtr* r = *(RefPtr**)(e + 8);
        if (r && !(r->refs & 1))
            m0 = m0 + 1;
    }
}

// ===========================================================================
// 0x007cfa90  PtrX::reset
// ===========================================================================
struct ObjX { void destroy(); };   // 0x007cf4e0 external thiscall
struct PtrX {
    ObjX* p;
    void reset();
};
void PtrX::reset()
{
    ObjX* q = p;
    if (q) {
        q->destroy();
        EFree(q);
    }
    p = 0;
}

// ===========================================================================
// 0x007cfac0  checkPtr
// ===========================================================================
bool __fastcall checkPtr(ObjX2** pp)
{
    if ((*pp)->m0 != 0)
        (*pp)->clear();
    return (*pp)->m0 == 0;
}

// ===========================================================================
// 0x007cfb40  MapW::tryInsert
// ===========================================================================
struct MapW {
    void* mpTree;    // +0
    void* mpEnd;     // +4
    void* mpRoot;    // +8
    char  pad0c[0x10 - 0xc];
    void* mpCap;     // +0x10
    void* tryInsert(void* pos, void* value);
};
// @ 0x007cfb40
void* MapW::tryInsert(void* pos, void* value)
{
    void* p = mpEnd;
    int idx = (int)((char*)pos - (char*)mpTree) >> 4;
    if (pos == p && p != mpRoot) {
        mpEnd = (char*)p + 0x10;
        if (p) {
            MapElem* d = (MapElem*)p;
            MapElem* s = (MapElem*)value;
            d->ka = s->ka;
            d->kb = s->kb;
            new (&d->ref) AutoRef(s->ref);
        }
        return (char*)mpTree + idx * 0x10;
    }
    ((MapY*)(void*)this)->insertPair(pos, value);
    return (char*)mpTree + idx * 0x10;
}

// ===========================================================================
// 0x007cfbb0  InnerC::clear
// ===========================================================================
extern "C" void* __cdecl VecBoolDoInsertValue(void*, void*, int);  // 0x11e0744
extern "C" void* __cdecl FUN_007cee40(void*, void*, void*);
extern "C" void  __cdecl FUN_00533500(void*, void*);

struct InnerC {
    char  pad00[0x34];
    void* m34;           // +0x34
    void* m38;           // +0x38
    char  pad3c[0x4c - 0x3c];
    void* m4c;           // +0x4c
    void* m50;           // +0x50
    void  clear();
};
// @ 0x007cfbb0
void InnerC::clear()
{
    // +0x00 : vector<bool>  (begin/end/cap at +0/+4/+8)
    char* v0 = (char*)this;
    char* b0 = *(char**)(v0 + 4);
    char* e0 = *(char**)(v0 + 8);
    VecBoolDoInsertValue(b0, e0, 0);
    *(char**)(v0 + 8) = e0 + ((e0 - b0) >> 3) * -8;

    // +0x34 : vector<Entry16>
    char* v1 = (char*)this + 0x34;
    char* b1 = *(char**)(v1 + 4);
    char* e1 = *(char**)(v1 + 8);
    void* r = FUN_007cee40(e1, e1, b1);
    ((VecCommon*)((char*)this + 0x34))->destructRange(r, e1);
    *(char**)(v1 + 4) = e1 + ((e1 - b1) >> 4) * -0x10;

    // +0x1c : vector<bool-ish>
    char* v2 = (char*)this + 0x1c;
    FUN_006130e0(*(void**)v2, *(void**)(v2 + 4));

    // +0x4c : vector<bool>
    char* v3 = (char*)this + 0x4c;
    char* b3 = *(char**)(v3);
    char* e3 = *(char**)(v3 + 4);
    VecBoolDoInsertValue(b3, e3, 0);
    *(char**)(v3 + 4) = e3 + ((e3 - b3) >> 3) * -8;

    FUN_00533500(*(void**)((char*)this + 0x64), *(void**)((char*)this + 0x68));
}

// ===========================================================================
// 0x007cfc60  W::clear
// ===========================================================================
struct W {
    InnerC* m;
    void clear();
};
void W::clear()
{
    m->clear();
}

// ===========================================================================
// 0x007cfc70  map B find-or-insert result
// ===========================================================================
struct MapV {
    void*  mpTree;    // +0
    void*  mpBegin;   // +4
    char   pad8[0x14 - 8];
    bool   mb14;      // +0x14
    char   pad15[0x18 - 0x15];
    void*  mpRoot;    // +0x18
    void*  tryInsert(void* pos, Pair8* kv);
    Pair8* findOrInsert2(char* out, Pair8* kv);
};
// @ 0x007cfc70
Pair8* MapV::findOrInsert2(char* out, Pair8* kv)
{
    void* end = mpBegin;
    Pair8* r = (Pair8*)FUN_007c8160(mpTree, end, kv, mb14);
    if ((void*)r != end) {
        if (r->sub <= kv->sub && (kv->sub != r->sub || r->key <= kv->key)) {
            *(Pair8**)out = r;
            out[4] = 0;
            return (Pair8*)out;
        }
    }
    Pair8* ins = (Pair8*)tryInsert(r, kv);
    *(Pair8**)out = ins;
    out[4] = 1;
    return (Pair8*)out;
}

// ===========================================================================
// 0x007cfcd0  SP::CompileToPropertyModel
// ===========================================================================
struct MgrObj;
struct PMObj;
struct FxObj;
typedef bool  (MgrObj::*MgrFind)(void*, void**, void**, int, int, int, int);
typedef bool  (MgrObj::*MgrQuery)(unsigned __int64, void**);
typedef void* (PMObj::*PMGet)(ResKey, int);
typedef void* (FxObj::*FxGet)(int, int, void*, int);
static void* VTSlot(void* o, unsigned off) { return *(void**)((char*)o + off); }

struct PMOwner {
    char pad[0x100];
    void compile(int count, Elem16* items);
    void allegianceUpdate(int a, int b);
};
// @ 0x007cfcd0
void PMOwner::compile(int count, Elem16* items)
{
    MapX* mx4c = (MapX*)((char*)this + 0x4c);
    MapV* mv34 = (MapV*)((char*)this + 0x34);
    for (int i = 0; i < count; i++) {
        Elem16& it = items[i];
        unsigned kind = it.kind;
        if (kind > 0x12) {
            if (kind == 0x102) {
                char res[8];
                mx4c->findOrInsert(res, (Pair8*)&it);
                if (res[4]) {
                    void* t = 0;
                    void* mgr = FUN_0067dcd0_GetManager();
                    void* qf = VTSlot(mgr, 0x2c);
                    bool ok = (((MgrObj*)mgr)->*(*(MgrQuery*)&qf))(
                            *(unsigned __int64*)&it, &t);
                    if (ok) {
                        for (int j = 0; j < 4; j++) {
                            Id2 k;
                            if (SP_GetPropertyAsKey(t, j + 0xf9efbb, &k)) {
                                Elem16 sub;
                                sub.a = k.a; sub.b = k.b;
                                sub.kind = 0; sub.d = 0;
                                compile(1, &sub);
                            }
                        }
                    }
                    if (t)
                        ((void(__thiscall*)(void*))VTSlot(t, 4))(t);
                }
            }
        } else if (kind == 0x12) {
            allegianceUpdate((int)it.a, (int)it.b);
        } else if (kind == 0) {
            char out[0x10];
            MapElem tmp;
            tmp.ka = it.a; tmp.kb = it.b; tmp.ref.p = 0; tmp.d = 0;
            mv34->findOrInsert2(out, (Pair8*)&tmp);
            if (tmp.ref.p) {
                long* cnt = (long*)((char*)tmp.ref.p + 8);
                long v = _InterlockedExchangeAdd(cnt, -1) - 1;
                if (v < 1)
                    _InterlockedExchangeAdd(cnt, 1);
            }
            if (out[4]) {
                void* pm = FUN_0067dd60();
                void* pf = VTSlot(pm, 0x1c);
                ResKey rk;
                rk.a = it.a; rk.b = 0; rk.c = it.b;
                void* rv = (((PMObj*)pm)->*(*(PMGet*)&pf))(rk, 0);
                AutoRef* dst = (AutoRef*)(out + 8);
                new (dst) AutoRef(*(const AutoRef*)&rv);
            }
        } else if (kind == 2) {
            char out[0x10];
            MapElem tmp;
            tmp.ka = it.a; tmp.kb = it.b; tmp.ref.p = 0; tmp.d = 0;
            FUN_007cabc0(out, &tmp);
            if (tmp.ref.p)
                ((void(__thiscall*)(void*))VTSlot(tmp.ref.p, 4))(tmp.ref.p);
            if (out[4]) {
                ResKey kk;
                kk.a = it.a;
                kk.b = 0xe6bce5;
                kk.c = it.b;
                void* p2 = 0, *p3 = 0;
                void* mgr = FUN_0067dcd0_GetManager();
                void* qf = VTSlot(mgr, 0x10);
                bool ok = (((MgrObj*)mgr)->*(*(MgrFind*)&qf))(
                        &kk, &p3, &p2, 0, 0, 0, 0);
                if (!ok) {
                    kk.b = 0x2f4e681b;
                    mgr = FUN_0067dcd0_GetManager();
                    qf = VTSlot(mgr, 0x10);
                    (((MgrObj*)mgr)->*(*(MgrFind*)&qf))(&kk, &p3, &p2, 0, 0, 0, 0);
                }
                if (!p3) {
                    if (p2)
                        FUN_004b54b0(&p2);
                } else {
                    FUN_00ac9480(&p3);
                }
                if (p2)
                    ((void(__thiscall*)(void*))VTSlot(p2, 4))(p2);
            }
        }
    }
}

// ===========================================================================
// 0x007d00e0  SP::cCityVisualizer::AllegianceUpdate
// ===========================================================================
// @ 0x007d00e0
void PMOwner::allegianceUpdate(int a, int b)
{
    char res[8];
    int arg = a;
    ((MapX*)((char*)this + 4))->findOrInsert(res, (Pair8*)&arg);
    if (!res[4])
        return;
    Vec3 tmp;
    tmp.begin = 0; tmp.end = 0; tmp.cap = 0;
    void* mgr = SP_EffectsManager();
    void* ff = VTSlot(mgr, 0x6c);
    void* v = (((FxObj*)mgr)->*(*(FxGet*)&ff))(a, b, 0, 0);
    FUN_007cfae0(&tmp, v);
    Vec3 out;
    out.begin = 0; out.end = 0; out.cap = 0;
    mgr = SP_EffectsManager();
    ff = VTSlot(mgr, 0x6c);
    unsigned n = (unsigned)((char*)tmp.end - (char*)tmp.begin) >> 4;
    (((FxObj*)mgr)->*(*(FxGet*)&ff))(a, b, out.begin, (int)n);
    compile(1, (Elem16*)out.begin);
    char* base = (char*)this;
    *(int*)base = (int)((*(char**)(base + 0x20) - *(char**)(base + 0x1c)) >> 4)
                + (int)((*(char**)(base + 0x38) - *(char**)(base + 0x34)) >> 4);
    if (out.begin)
        EFree(out.begin);
}

// ===========================================================================
// 0x007d01d0  W2::f
// ===========================================================================
struct InnerD {
    char pad[0x40];
    void g(int, int);
};
struct W2 {
    InnerD* m;
    void f(int a, int b);
};
void W2::f(int a, int b)
{
    m->g(a, b);
}

// ===========================================================================
// 0x007d01f0  serialization cluster
// ===========================================================================
void WriteUint16(void*, const uint16_t&, int, int);   // 0x0093a9d0
void WriteUint32(void*, const uint32_t&, int, int);   // 0x0093aa70
void WriteFloat32(void*, const float&, int, int);     // 0x0093aa70
void WriteByte(void*, const uint8_t&, int);           // 0x0093a9a0  (operator<<)

struct IStream {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual void Write(void*, int);   // slot 14 (0x38)
};
// @ 0x007d01f0
void* Ser1F0(IStream* s, char* p)
{
    uint16_t v16 = *(uint16_t*)p;
    float vf;
    WriteUint16(s, v16, 1, 0);
    vf = *(float*)(p + 0x10);
    WriteFloat32(s, vf, 1, 0);
    s->Write(p + 0x14, 0x24);
    s->Write(p + 4, 0xc);
    return s;
}

// @ 0x007d0250
void* Ser250(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 2;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++)
        WriteFloat32(s, (float)*(float*)(vec[0] + i * 4), 1, 0);
    return s;
}

// @ 0x007d02b0
void* Ser2B0(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 3;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++) {
        int* e = (int*)(vec[0] + i * 8);
        WriteUint32(s, (uint32_t)e[0], 1, 0);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 4), 1);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 5), 1);
    }
    return s;
}

// @ 0x007d0360
void Ser360(IStream* s, char* p)
{
    s->Write(p, 8);
    Ser250(s, (int*)(p + 8));
    WriteFloat32(s, (float)*(float*)(p + 0x1c), 1, 0);
    WriteUint32(s, (uint32_t)*(uint32_t*)(p + 0x24), 1, 0);
    WriteByte(s, (uint8_t)*(uint8_t*)(p + 0x28), 1);
}
