// Slice s00a691c0: EA/Spore framework message dispatch, serialization and
// EASTL ref-counted-container helpers.
// flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int); // 0x00f473a0
void  __cdecl operator_delete__(void*);                                      // 0x00f47380
void* __cdecl SporeMemcpy(void*, const void*, unsigned);                     // 0x011e0744
extern const char kEastlAllocFile[];  // 0x013ebb38
extern const char kEastlTag[];        // 0x013f2150

// ---------------------------------------------------------------------------
struct RefObject {
    virtual void Destroy(int flag);   // vtable slot 0
    int mnRefCount;                   // +0x04
};

struct RefVecSlot {
    RefObject** mpBegin;      // +0x00
    RefObject** mpEnd;        // +0x04
    RefObject** mpCapacity;   // +0x08
    uint32_t    mx0c;         // +0x0c
    uint32_t    mx10;         // +0x10
};

struct RefVec {
    RefObject** mpBegin;
    RefObject** mpEnd;
    RefObject** mpCapacity;

    void DestroyRange(RefObject** first, RefObject** last);            // 0x00a693f0
    RefVec& assign(const RefVec& o);                                // 0x00a69e50
    void insert(RefObject** position, RefObject** value);              // 0x00a69f90
    void insert(RefObject** position, unsigned n, RefObject** value);  // 0x00a6a120
};

void  __cdecl UninitCopyRef(void** result, RefObject** first, RefObject** last, RefObject** dest); // 0x00a69490
void  __cdecl FillRef(RefObject** dest, unsigned n, RefObject** src);       // 0x00a695a0
void* __stdcall AllocCopy(unsigned n, RefObject** first, RefObject** last); // 0x00a695d0
RefObject** __cdecl CopyRefs(RefObject** dest, RefObject** end, RefObject** src);              // 0x00a69070
RefObject** __cdecl CopyBackwardRef(RefObject** first, RefObject** last, RefObject** destEnd); // 0x00a690d0
void __stdcall DestroyElems84(void* first, void* last);                     // 0x00a69be0
void* __cdecl DoFindNodeStr(void* node, const char* key);                   // 0x00555020

// ---------------------------------------------------------------------------
struct RegRec24 {
    void*    pf0;        // +0x00
    void*    pf4;        // +0x04
    uint32_t pad8;       // +0x08
    uint16_t w0c;        // +0x0c
    uint16_t padE;       // +0x0e
    uint32_t pad10[5];   // +0x10
};
extern RegRec24 g_RegA[32];        // 0x01675a00

struct RegRec20 {
    void*    pf0;        // +0x00
    uint32_t pad4;       // +0x04
    uint32_t pad8;       // +0x08
    uint16_t w0c;        // +0x0c
    uint16_t padE;       // +0x0e
    uint32_t pad10[4];   // +0x10
};
extern RegRec20 g_RegB[64];        // 0x01675ec0

// vtable-only view used for the indirect virtual calls
struct VtWrap {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual int  v08(void* a, void* b);                    // +0x20
    virtual void v09(); virtual void v0a();
    virtual int  v0b(void* a, void* out, int n);           // +0x2c
};

struct Ctx {
    int  DispatchLookup(uint32_t key, uint32_t* out, int count);   // 0x00a691c0
    void ForEachRegA(uint32_t arg);                                // 0x00a69310
    void ForEachRegB(uint32_t arg);                                // 0x00a69380
    void Serialize(void* stream);                                  // 0x00a69630
};

// ===========================================================================
// @ 0x00a691c0
int Ctx::DispatchLookup(uint32_t key, uint32_t* out, int count)
{
    char* self = (char*)this;
    int result = 0;
    if ((key & 0xff000000) == 0x7f000000) {
        uint32_t* tab = *(uint32_t**)(self + 0x88);
        uint32_t lo = tab[(key & 0xffffff) * 2];
        uint32_t hi = tab[(key & 0xffffff) * 2 + 1];
        if ((lo & hi) != 0xffffffff) {
            result = 1;
            if (count > 0) {
                out[0] = lo;
                out[1] = hi;
                out[2] = 0x12;
            }
        }
    } else {
        char* rec = *(char**)(self + 0x34) + key * 0x58;
        int n = (*(int*)(rec + 0x48) - *(int*)(rec + 0x44)) / 0x84;
        int idx = 0;
        if (n > 0) {
            int off = 0;
            do {
                char* elem = (char*)(off + *(int*)(rec + 0x44));
                uint32_t k = *(uint32_t*)elem;
                int val = *(int*)(elem + 0x80);
                int wrote = 0;
                if (k == 0) {
                    wrote = ((VtWrap*)self)->v0b((void*)val, out, count);
                } else if (*(void**)((char*)0x01675ec4 + k * 32) != 0) {
                    int a = ((VtWrap*)self)->v08((void*)val, (void*)k);
                    wrote = (*(int(__cdecl*)(void*, int, uint32_t*, int))(*(void**)((char*)0x01675ec4 + k * 32)))(self, a, out, count);
                }
                result += wrote;
                if (out != 0) {
                    count -= wrote;
                    out += wrote * 4;
                    if (count < 1)
                        return result;
                }
                off += 0x84;
                ++idx;
            } while (idx < n);
        }
    }
    return result;
}

// ===========================================================================
// @ 0x00a69310
void Ctx::ForEachRegA(uint32_t arg)
{
    char* self = (char*)this;
    int k = 0;
    RegRec24* rec = g_RegA;
    do {
        if (rec->pf0 != 0) {
            RefVecSlot* slot = (RefVecSlot*)(*(char**)(self + 0x20) + k);
            int n = (int)(slot->mpEnd - slot->mpBegin);
            int i = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(RefObject*, uint32_t))rec->pf0)(slot->mpBegin[i], arg);
                    ++i;
                } while (i < n);
            }
        }
        ++rec;
        k += 0x14;
    } while (rec < (RegRec24*)0x01675e80);
}

// ===========================================================================
// @ 0x00a69380
void Ctx::ForEachRegB(uint32_t arg)
{
    char* self = (char*)this;
    int k = 0;
    RegRec24* rec = g_RegA;
    do {
        if (rec->pf4 != 0) {
            RefVecSlot* slot = (RefVecSlot*)(*(char**)(self + 0x20) + k);
            int n = (int)(slot->mpEnd - slot->mpBegin);
            int i = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(RefObject*, uint32_t))rec->pf4)(slot->mpBegin[i], arg);
                    ++i;
                } while (i < n);
            }
        }
        ++rec;
        k += 0x14;
    } while (rec < (RegRec24*)0x01675e84);
}

// ===========================================================================
// @ 0x00a693f0
void RefVec::DestroyRange(RefObject** first, RefObject** last)
{
    for (; first < last; ++first) {
        RefObject* o = *first;
        if (o) {
            int rc = o->mnRefCount + -1;
            o->mnRefCount = rc;
            if (rc == 0) {
                o->mnRefCount = 1;
                o->Destroy(1);
            }
        }
    }
}

// ===========================================================================
// @ 0x00a69490
void __cdecl UninitCopyRef(void** result, RefObject** first, RefObject** last, RefObject** dest)
{
    *result = dest;
    if (first != last) {
        do {
            if (dest) {
                RefObject* o = *first;
                *dest = o;
                if (o)
                    ++o->mnRefCount;
            }
            ++first;
            ++dest;
        } while (first != last);
        *result = dest;
    }
}

// ===========================================================================
// @ 0x00a695a0
void __cdecl FillRef(RefObject** dest, unsigned n, RefObject** src)
{
    for (; n > 0; --n) {
        if (dest) {
            RefObject* o = *src;
            *dest = o;
            if (o)
                ++o->mnRefCount;
        }
        ++dest;
    }
}

// ===========================================================================
// @ 0x00a69630
struct ISink {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d();
    virtual void Write(const void* p, int n);   // vtable +0x38
};
void WriteUint16(void* stream, void* p, unsigned n, int endian);   // 0x0093a9d0
void WriteUint32(void* stream, void* p, unsigned n, int endian);   // 0x0093aa70
void WriteUint64(void* stream, void* p, unsigned n, int endian);   // 0x0093ab10
void SerializeRecord(void* stream, void* rec);                     // 0x00a84720

void Ctx::Serialize(void* stream)
{
    char* self = (char*)this;
    uint32_t tmp;
    struct { void* pf; uint32_t v; } blob;
    uint32_t acc = 0;

    tmp = 4;
    WriteUint16(stream, &tmp, 1, 0);
    blob.pf = (void*)0x01455910;
    blob.v = 0;
    tmp = 0;
    uint32_t off = 0;
    RegRec20* rec = g_RegB;
    do {
        if (*(int*)(*(char**)(self + 0x0c) + off) != *(int*)(*(char**)(self + 0x0c) + off + 4) && rec->pf0 != 0) {
            uint32_t a = tmp & 0xffff;
            WriteUint16(stream, &a, 1, 0);
            a = rec->w0c;
            WriteUint16(stream, &a, 1, 0);
            int n = (*(int*)(*(char**)(self + 0x0c) + off + 4) - *(int*)(*(char**)(self + 0x0c) + off)) / 4;
            acc = 0;
            a = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(void*, void*))rec->pf0)((char*)(*(void**)(*(char**)(self + 0x0c) + off)) + (a & 0xffff), &blob);
                    ++a;
                } while ((int)a < n);
            }
            a = acc + 4;
            WriteUint32(stream, &a, 1, 0);
            a = n;
            WriteUint32(stream, &a, 1, 0);
            a = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(void*, void*))rec->pf0)((char*)(*(void**)(*(char**)(self + 0x0c) + off)) + (a & 0xffff), stream);
                    ++a;
                } while ((int)a < n);
            }
        }
        ++tmp;
        off += 0x14;
        ++rec;
    } while (rec < (RegRec20*)0x016766c0);

    void* p = (void*)0xffff;
    WriteUint16(stream, &p, 1, 0);
    uint32_t c2 = 0;
    off = 0;
    RegRec24* r2 = g_RegA;
    do {
        if (*(int*)(*(char**)(self + 0x20) + off) != *(int*)(*(char**)(self + 0x20) + off + 4) && r2->pf0 != 0) {
            uint32_t a = c2 & 0xffff;
            WriteUint16(stream, &a, 1, 0);
            a = r2->w0c;
            WriteUint16(stream, &a, 1, 0);
            int n = (*(int*)(*(char**)(self + 0x20) + off + 4) - *(int*)(*(char**)(self + 0x20) + off)) / 4;
            acc = 0;
            a = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(void*, void*))r2->pf0)((char*)(*(void**)(*(char**)(self + 0x20) + off)) + (a & 0xffff), &blob);
                    ++a;
                } while ((int)a < n);
            }
            a = acc + 4;
            WriteUint32(stream, &a, 1, 0);
            a = n;
            WriteUint32(stream, &a, 1, 0);
            a = 0;
            if (n > 0) {
                do {
                    ((void(__cdecl*)(void*, void*))r2->pf0)((char*)(*(void**)(*(char**)(self + 0x20) + off)) + (a & 0xffff), stream);
                    ++a;
                } while ((int)a < n);
            }
        }
        ++c2;
        off += 0x14;
        r2 = (RegRec24*)((char*)r2 + 0x24);
    } while (r2 < (RegRec24*)0x01675e8c);

    void* q = (void*)0xffff;
    WriteUint16(stream, &q, 1, 0);
    q = (void*)1;
    WriteUint16(stream, &q, 1, 0);
    int nrec = (*(int*)(self + 0x38) - *(int*)(self + 0x34)) / 0x58;
    WriteUint32(stream, &nrec, 1, 0);
    if (nrec > 0) {
        int o = 0;
        int left = nrec;
        do {
            SerializeRecord(stream, *(char**)(self + 0x34) + o);
            o += 0x58;
            --left;
        } while (left != 0);
    }

    {
        char* base = *(char**)(self + 0x6c);
        uint32_t* cur = *(uint32_t**)base;
        if (cur == 0) {
            base += 4;
            while (*(uint32_t*)base == 0)
                base += 4;
            cur = *(uint32_t**)base;
        }
        if (cur != *(uint32_t**)(*(char**)(self + 0x6c) + *(int*)(self + 0x70) * 4)) {
            do {
                void* a = (void*)cur[2];
                WriteUint32(stream, &a, 1, 0);
                struct { uint32_t lo, hi; } pr = { cur[0], cur[1] };
                WriteUint64(stream, &pr, 1, 0);
                cur = (uint32_t*)cur[4];
                while (cur == 0) {
                    base += 4;
                    cur = *(uint32_t**)base;
                }
            } while (cur != *(uint32_t**)(*(char**)(self + 0x6c) + *(int*)(self + 0x70) * 4));
        }
    }

    void* r = (void*)0xffffffff;
    WriteUint32(stream, &r, 1, 0);
    {
        char* base = *(char**)(self + 0x4c);
        int* cur = *(int**)base;
        if (cur == 0) {
            base += 4;
            while (*(int*)base == 0)
                base += 4;
            cur = *(int**)base;
        }
        if (cur != *(int**)(*(char**)(self + 0x4c) + *(int*)(self + 0x50) * 4)) {
            do {
                uint32_t a = cur[4];
                WriteUint32(stream, &a, 1, 0);
                ((ISink*)stream)->Write((void*)cur[0], cur[1] - cur[0]);
                acc &= 0xffffff00;
                ((ISink*)stream)->Write(&acc, 1);
                cur = (int*)cur[5];
                while (cur == 0) {
                    base += 4;
                    cur = *(int**)base;
                }
            } while (cur != *(int**)(*(char**)(self + 0x4c) + *(int*)(self + 0x50) * 4));
        }
    }

    void* s = (void*)0xffffffff;
    WriteUint32(stream, &s, 1, 0);
    uint32_t cnt = (*(int*)(self + 0x8c) - *(int*)(self + 0x88)) >> 3;
    WriteUint32(stream, &cnt, 1, 0);
    uint32_t i = 0;
    if (cnt != 0) {
        do {
            uint32_t* p32 = (uint32_t*)(*(char**)(self + 0x88) + i * 8);
            struct { uint32_t lo, hi; } vv = { p32[0], p32[1] };
            WriteUint64(stream, &vv, 1, 0);
            ++i;
        } while (i < cnt);
    }
}

// ===========================================================================
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mpAllocator;
    void RangeInitialize(int n);                            // 0x00475ab0
    EString& assign(const char* first, const char* last);  // 0x00454cb0
};

struct IInterface {
    virtual void AddRef();
    virtual void Release();
};

struct StrRec {
    EString s0;            // +0x00
    EString s1;            // +0x10
    IInterface* p;         // +0x20

    StrRec* Ctor(const StrRec* o);        // 0x00a69b20
    StrRec* assign_rec(const StrRec* o);  // 0x00a69c20
};

// ===========================================================================
// @ 0x00a69b20
StrRec* StrRec::Ctor(const StrRec* o)
{
    s0.mpBegin = 0;
    s0.mpEnd = 0;
    s0.mpCapacity = 0;
    unsigned n0 = (unsigned)(o->s0.mpEnd - o->s0.mpBegin);
    s0.RangeInitialize(n0 + 1);
    SporeMemcpy(s0.mpBegin, o->s0.mpBegin, n0);
    s0.mpEnd = s0.mpBegin + n0;
    *s0.mpEnd = 0;

    s1.mpBegin = 0;
    s1.mpEnd = 0;
    s1.mpCapacity = 0;
    unsigned n1 = (unsigned)(o->s1.mpEnd - o->s1.mpBegin);
    s1.RangeInitialize(n1 + 1);
    SporeMemcpy(s1.mpBegin, o->s1.mpBegin, n1);
    s1.mpEnd = s1.mpBegin + n1;
    *s1.mpEnd = 0;

    p = o->p;
    if (p)
        p->AddRef();
    return this;
}

// ===========================================================================
// @ 0x00a69c20
StrRec* StrRec::assign_rec(const StrRec* o)
{
    if (o != this) {
        s0.assign(o->s0.mpBegin, o->s0.mpEnd);
    }
    const EString* ps = &o->s1;
    if (ps != &s1) {
        s1.assign(ps->mpBegin, ps->mpEnd);
    }
    IInterface* np = o->p;
    IInterface* op = p;
    if (np != op) {
        if (np)
            np->AddRef();
        p = np;
        if (op)
            op->Release();
    }
    return this;
}

// ===========================================================================
// @ 0x00a69c80
struct HTNode {
    uint32_t mHashAndFlags;   // +0x00
    uint32_t mPad04;
    void*    mKey;            // +0x08
    uint32_t mPad0c;
    uint32_t mPad10;
    HTNode*  mpNext;          // +0x14
};
struct Hashtable {
    uint32_t mPad00;
    HTNode** mpBuckets;       // +0x04
    uint32_t mnBucketCount;   // +0x08

    void find_as(void** out, const char** keyp, int a2, int a3);   // 0x00a69c80
};

void Hashtable::find_as(void** out, const char** keyp, int a2, int a3)
{
    const char* s = *keyp;
    unsigned h = 0x811c9dc5;
    unsigned char c = (unsigned char)*s;
    const char* p = s;
    while (c != 0) {
        ++p;
        h = h * 0x1000193 ^ c;
        c = (unsigned char)*p;
    }
    unsigned idx = h % mnBucketCount;
    HTNode** buckets = mpBuckets;
    HTNode* node = buckets[idx];
    HTNode** slot = &buckets[idx];
    for (;;) {
        if (node == 0) {
            out[0] = (void*)buckets[mnBucketCount];
            out[1] = (void*)&buckets[mnBucketCount];
            return;
        }
        if ((char)DoFindNodeStr(node, s) != 0) {
            out[0] = (void*)node;
            out[1] = (void*)slot;
            return;
        }
        node = node->mpNext;
    }
}

// ===========================================================================
// @ 0x00a69d60
RefVecSlot* __cdecl DestroySlotRange(RefVecSlot* first, RefVecSlot* last, RefVecSlot* out)
{
    if (first == last)
        return out;
    do {
        ((RefVec*)first)->DestroyRange(((RefVec*)first)->mpBegin, ((RefVec*)first)->mpEnd);
        RefObject** b = ((RefVec*)first)->mpBegin;
        if (b && ((int*)b)[-1] != 0)
            operator_delete__(b);
        first = (RefVecSlot*)((char*)first + 0x14);
        out = (RefVecSlot*)((char*)out + 0x14);
    } while (first != last);
    return out;
}

// ===========================================================================
// @ 0x00a69db0
StrRec* __cdecl StrRecMoveBackward(StrRec* first, StrRec* last, StrRec* out)
{
    if (last == first)
        return out;
    StrRec* src = last;
    do {
        src = (StrRec*)((char*)src - 0x24);
        out = (StrRec*)((char*)out - 0x24);
        if (src != out) {
            out->s0.assign(src->s0.mpBegin, src->s0.mpEnd);
        }
        if ((char*)&src->s1 != (char*)&out->s1) {
            out->s1.assign(src->s1.mpBegin, src->s1.mpEnd);
        }
        IInterface* np = src->p;
        IInterface* op = out->p;
        if (np != op) {
            if (np)
                np->AddRef();
            out->p = np;
            if (op)
                op->Release();
        }
    } while (src != first);
    return out;
}

// ===========================================================================
// @ 0x00a69e50
RefVec& RefVec::assign(const RefVec& o)
{
    if (&o != this) {
        RefObject** srcBegin = o.mpBegin;
        RefObject** srcEnd = o.mpEnd;
        unsigned uVar7 = (unsigned)(srcEnd - srcBegin);
        if ((unsigned)(mpCapacity - mpBegin) < uVar7) {
            RefObject** buf = (RefObject**)AllocCopy(uVar7, srcBegin, srcEnd);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1] != 0)
                operator_delete__(mpBegin);
            mpCapacity = buf + uVar7;
            mpEnd = buf + uVar7;
            mpBegin = buf;
            return *this;
        }
        unsigned uVar6 = (unsigned)(mpEnd - mpBegin);
        if (uVar6 < uVar7) {
            CopyRefs(srcBegin, srcBegin + uVar6, mpBegin);
            void* res;
            UninitCopyRef(&res, srcBegin + uVar6, srcEnd, mpEnd);
            mpEnd = mpBegin + uVar7;
            return *this;
        }
        CopyRefs(srcBegin, srcEnd, mpBegin);
        DestroyRange(mpBegin + uVar7, mpEnd);
        mpEnd = mpBegin + uVar7;
    }
    return *this;
}

// ===========================================================================
// @ 0x00a69f40
struct BigThing {
    char pad0[0x1c];
    void* mpAt1c;         // +0x1c
    char pad20[0x24];
    RefVec mVec44;        // +0x44
    void Destroy();       // 0x00a69f40
};

void BigThing::Destroy()
{
    DestroyElems84(*(void**)((char*)this + 0x44), *(void**)((char*)this + 0x48));
    void* a = *(void**)((char*)this + 0x44);
    if (a && ((int*)a)[-1] != 0)
        operator_delete__(a);
    void* b = *(void**)((char*)this + 0x1c);
    if (b && ((int*)b)[-1] != 0)
        operator_delete__(b);
}

// ===========================================================================
// @ 0x00a69f90
void RefVec::insert(RefObject** position, RefObject** value)
{
    RefObject** oldEnd = mpEnd;
    if (oldEnd != mpCapacity) {
        RefObject** src = value;
        if (value >= position && value < oldEnd)
            src = value + 1;
        if (oldEnd) {
            RefObject* last = oldEnd[-1];
            *oldEnd = last;
            if (last)
                ++last->mnRefCount;
        }
        CopyBackwardRef(position, mpEnd - 1, mpEnd);
        RefObject* nv = *src;
        RefObject* ov = *position;
        if (nv != ov) {
            if (nv)
                ++nv->mnRefCount;
            *position = nv;
            if (ov) {
                if (--ov->mnRefCount == 0) {
                    ov->mnRefCount = 1;
                    ov->Destroy(1);
                }
            }
        }
        mpEnd += 1;
        return;
    }
    unsigned n = (unsigned)(oldEnd - mpBegin);
    unsigned cap;
    if (n > 0)
        cap = n * 2;
    else
        cap = 1;
    RefObject** buf = 0;
    if (cap)
        buf = (RefObject**)operator_new(cap * 4, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
    unsigned before = (unsigned)(position - mpBegin);
    SporeMemcpy(buf, mpBegin, before);
    RefObject** mid = buf + (before >> 2);
    if (mid) {
        RefObject* v = *value;
        *mid = v;
        if (v)
            ++v->mnRefCount;
    }
    unsigned after = (unsigned)(mpEnd - position);
    SporeMemcpy(mid + 1, position, after);
    RefObject** newEnd = mid + 1 + (after >> 2);
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
        operator_delete__(mpBegin);
    mpBegin = buf;
    mpEnd = newEnd;
    mpCapacity = buf + cap;
}

// ===========================================================================
// @ 0x00a6a0e0
void __stdcall DestroySlotRange2(RefVecSlot* first, RefVecSlot* last)
{
    for (; first < last; first = (RefVecSlot*)((char*)first + 0x14)) {
        ((RefVec*)first)->DestroyRange(((RefVec*)first)->mpBegin, ((RefVec*)first)->mpEnd);
        RefObject** b = ((RefVec*)first)->mpBegin;
        if (b && ((int*)b)[-1] != 0)
            operator_delete__(b);
    }
}

// ===========================================================================
// @ 0x00a6a120
void RefVec::insert(RefObject** position, unsigned n, RefObject** value)
{
    unsigned freeSlots = (unsigned)(mpCapacity - mpEnd);
    if (n > freeSlots) {
        unsigned oldSize = (unsigned)(mpEnd - mpBegin);
        unsigned grow = oldSize * 2;
        if (oldSize == 0)
            grow = 1;
        unsigned newCap = oldSize + n;
        if (grow > newCap)
            newCap = grow;
        RefObject** buf = 0;
        if (newCap)
            buf = (RefObject**)operator_new(newCap * 4, kEastlTag, 0, 0, kEastlAllocFile, 0xd1);
        unsigned before = (unsigned)(position - mpBegin);
        SporeMemcpy(buf, mpBegin, before);
        RefObject** mid = buf + (before >> 2);
        FillRef(mid, n, value);
        RefObject** midEnd = mid + n;
        unsigned after = (unsigned)(mpEnd - position);
        SporeMemcpy(midEnd, position, after);
        RefObject** newEnd = midEnd + (after >> 2);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCapacity = buf + newCap;
        return;
    }
    if (n == 0)
        return;
    {
        RefObject* tmp = *value;
        if (tmp)
            ++tmp->mnRefCount;
        RefObject** oldEnd = mpEnd;
        unsigned extra = (unsigned)(oldEnd - position);
        if (n < extra) {
            RefObject** saved = mpEnd - n;
            void* res;
            UninitCopyRef(&res, saved, oldEnd, oldEnd);
            mpEnd += n;
            CopyBackwardRef(position, saved, oldEnd);
            FillRef(position, n, &tmp);
        } else {
            FillRef(oldEnd, n - extra, &tmp);
            mpEnd += (n - extra);
            void* res;
            UninitCopyRef(&res, position, oldEnd, mpEnd);
            mpEnd += extra;
            CopyBackwardRef(position, oldEnd, oldEnd);
            FillRef(position, n, &tmp);
        }
        if (tmp) {
            if (--tmp->mnRefCount == 0) {
                tmp->mnRefCount = 1;
                tmp->Destroy(1);
            }
        }
    }
}
