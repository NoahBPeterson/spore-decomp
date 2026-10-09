// Slice s0055dce0: Skinner::PaintSystem save/load of paint resource-id tables plus
// EASTL rbtree/vector helpers emitted in this module.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380

struct V32 { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };

namespace eastl { struct allocator { allocator() {} }; }

// Helpers used by this module (call targets are relocated).
void FUN_004769b0(void* p, unsigned n);
void FUN_0050f0d0(void* p, void* q);
void FUN_00425990();
void FUN_004e1780(void* p);
void* FUN_00569980(void* key);
void* FUN_00569b80(void* key);
void* FUN_00569b10(void* key);
void FUN_005699f0(void* src, void* dst);
void FUN_005699f0_2();
void FUN_0056a1a0();
void FUN_00565920(void* p);
void FUN_00564470(void* p);
void FUN_00553fb0(void* p);
void FUN_00548400(void* p);
void FUN_00511f70(void* first, void* last, void* dst);
void* FUN_0042dee0(void* a, int size, int align, int flags);
void FUN_0067dea0();
void* FUN_00572590();
void FUN_00540470(void* p);
void FUN_00554020(void* out, void* val);
void FUN_0055dce0(void* p);
void FUN_004f6b70(void* first, void* last);   // eastl::sort<Key*>, cdecl
void FUN_0055de60(int* p);
void FUN_005699f0_copy();
void RBTreeInsert(void* node, void* where, void* anchor, char flag);
bool EA_IO_WriteUint32(void* stream, void* val, int n, int f);   // 0x93aa70
bool EA_IO_ReadInt32(void* stream, void* val, int n, int f);     // 0x93a780
void* GetManager();                                              // 0x67dcd0
void* GetSaveArea(uint32_t id);                                  // 0x6b1f90
void* FUN_00567190(void* a, void* b, void* c);
void FUN_00568740(int* dst, int* first, int* last, uint32_t flag);
namespace SP { uint32_t EditorEntityToResourceType(uint32_t modelType, int a); }
static uint32_t SP_EditorEntityToResourceType(uint32_t a, int b) { return SP::EditorEntityToResourceType(a, b); }

// PaintSystem's save-area interface: Open is at +0x34, Close at +0x3c, GetStream at +0x18,
// Release at +0x08.
typedef bool (__thiscall *OpenFn)(void* self, void* key, void** out, int a, int b, int c, int d);
typedef void (__thiscall *CloseFn)(void* self, void* out);
typedef void* (__thiscall *GetStreamFn)(void* self);
typedef int  (__thiscall *ReleaseFn)(void* self);
typedef bool (__thiscall *GetRes58Fn)(void* self, void* key);

// @ 0x0055dce0
void FUN_0055dce0(void* pList) {
    uint32_t* v = (uint32_t*)pList;
    FUN_004769b0((void*)*v, v[1]);
    uint32_t key[3];
    key[0] = 0x727e3e7; key[1] = 0x727e3e7; key[2] = 0x11ac19c;
    void* mgr = GetManager();
    void* obj = (void*)((GetRes58Fn)(*(void***)mgr)[0x58 / 4])(mgr, key);
    if (obj) {
        void* stream = 0;
        if (((OpenFn)(*(void***)obj)[0x34 / 4])(obj, key, &stream, 1, 3, 1, 0)) {
            void* io = ((GetStreamFn)(*(void***)stream)[0x18 / 4])(stream);
            int a = 0;
            if (EA_IO_ReadInt32(io, &a, 1, 0) && a == 0) {
                uint32_t n = 0;
                if (EA_IO_ReadInt32(io, &n, 1, 0)) {
                    bool ok = true;
                    for (uint32_t i = 0; ok && i < n; ++i) {
                        uint32_t val = 0;
                        ok = EA_IO_ReadInt32(io, &val, 1, 0);
                        if (ok) {
                            uint32_t tmp[3];
                            FUN_00554020(tmp, &val);
                        }
                    }
                }
            }
            ((CloseFn)(*(void***)obj)[0x3c / 4])(obj, stream);
        }
        if (stream)
            ((ReleaseFn)(*(void***)stream)[8 / 4])(stream);
    }
}

// @ 0x0055de60
void FUN_0055de60(int* pList) {
    void* area = GetSaveArea(0x11ac19c);
    uint32_t key[3];
    key[0] = 0x727e3e7; key[1] = 0x727e3e7; key[2] = 0x11ac19c;
    void* stream = 0;
    if (((OpenFn)(*(void***)area)[0x34 / 4])(area, key, &stream, 2, 2, 1, 0)) {
        void* io = ((GetStreamFn)(*(void***)stream)[0x18 / 4])(stream);
        uint32_t zero = 0;
        if (EA_IO_WriteUint32(io, &zero, 1, 0)) {
            uint32_t count = (uint32_t)(pList[1] - *pList) >> 2;
            uint32_t out = count;
            if (EA_IO_WriteUint32(io, &out, 1, 0)) {
                bool ok = true;
                uint32_t* end = (uint32_t*)pList[1];
                for (uint32_t* it = (uint32_t*)*pList; ok && it != end; ++it) {
                    uint32_t v = *it;
                    ok = EA_IO_WriteUint32(io, &v, 1, 0);
                }
            }
        }
        uint32_t trailer = 4;
        EA_IO_WriteUint32(io, &trailer, 1, 0);
        ((CloseFn)(*(void***)area)[0x3c / 4])(area, stream);
    }
    if (stream)
        ((ReleaseFn)(*(void***)stream)[8 / 4])(stream);
}

// @ 0x0055dfe0
unsigned char FUN_0055dfe0(void* this_) {
    FUN_0067dea0();
    int* list = (int*)FUN_00572590();
    int count = (int)(list[1] - *list) >> 2;
    uint32_t tmpA[3];
    FUN_00540470(&tmpA);
    uint32_t* end = (uint32_t*)list[1];
    for (uint32_t* it = (uint32_t*)*list; it != end; ++it) {
        uint32_t v = *(uint32_t*)*it;
        FUN_00554020(&count, &v);
    }
    uint32_t tmpB[3];
    FUN_00540470(&tmpB);
    int a[3];
    FUN_0055dce0(a);
    bool equal = ((a[1] - a[0]) >> 2) == ((int)(tmpA[2] - tmpA[0]) >> 2);
    if (equal) {
        uint32_t* p = (uint32_t*)a[0];
        uint32_t* q = (uint32_t*)tmpA[0];
        for (; p != (uint32_t*)a[1]; ++p, ++q) {
            if (*p != *q) {
                equal = false;
                break;
            }
        }
    }
    if (equal) {
        FUN_00553fb0(&tmpB);
        FUN_00553fb0(&tmpA);
        return 0;
    }
    FUN_0055de60((int*)&tmpA);
    unsigned char r = 1;
    for (int* p = (int*)a[0]; p < (int*)a[1]; ++p) {
    }
    FUN_00548400(&a);
    for (uint32_t* p = (uint32_t*)tmpA[0]; p < (uint32_t*)tmpA[1]; ++p) {
    }
    FUN_00548400(&tmpA);
    return r;
}

// ---- 0x0055e190 support types (stub layouts; member names carry the callee VA) ----
struct Key3 { uint32_t a, b, c; };
struct TreeIt {
    uint32_t node;
    TreeIt* sub_566c50(uint32_t n);          // ctor(node), ret 4
    TreeIt* sub_5673e0(const TreeIt* o);     // copy ctor, ret 4
    TreeIt* sub_422c50();                    // operator++
    uint32_t* sub_564f50();                  // operator*  (&node->value, node+0x10)
};
struct VecSet32;
struct InsertIt {                            // insert-iterator {container, position}
    VecSet32* c; uint32_t* pos;
    InsertIt* sub_565a80(const uint32_t* v); // ret 4
};
struct RangeU { uint32_t* lo; uint32_t* hi; };
struct VecSet32 {                            // eastl::vector_set<uint32_t>, begin/end at +0/+4
    uint32_t* b; uint32_t* e; uint32_t* cap;
    bool sub_526430() const;
    uint32_t* sub_566060(uint32_t* pos, const uint32_t* v);   // ret 8
    void sub_555980(RangeU* out, const void* key);            // ret 8
    void sub_4769b0(uint32_t* first, uint32_t* last);         // ret 8 (erase)
};
struct KVec3 {
    Key3* b; Key3* e; Key3* cap;
    KVec3* sub_540470(char* tag);            // ret 4
    void sub_540520();
};
struct PSVec { uint32_t* b; uint32_t* e; uint32_t* cap; void sub_4e1bf0(); };
struct PSys {
    void** vptr; PSVec v; uint32_t pad;
    PSys* sub_55eae0(uint32_t* first, uint32_t cnt);          // ret 8
};
struct KeySet {                              // eastl::rbtree<Key3>
    uint32_t pad0; uint32_t aRight, aLeft, aParent; uint32_t color; uint32_t size;
    KeySet* sub_4b5980(char* tag);           // ret 4
    void sub_4290c0(uint32_t* out, const void* key, bool f);  // ret 0xc
    void sub_4e8a30(uint32_t root);          // ret 4
};
struct HTab {
    uint32_t pad0; uint32_t** buckets; uint32_t nBuckets; uint32_t pad3[5];
    HTab* sub_5640f0(char* tag);             // ret 4
    void sub_421a50(uint32_t* out, const uint32_t* kv, bool f); // ret 0xc
    void sub_564140(uint32_t** it);          // begin(), ret 4
    void sub_5534b0();
};
struct Tree7 { uint32_t anchor, left, rest[5]; };
struct Owner {
    void** vptr; uint32_t pad04[4];
    uint32_t* vecBegin; uint32_t* vecEnd;
    uint32_t pad1c[0x75];
    Tree7 t1; Tree7 t2; VecSet32 vs;
    unsigned char sub_55dfe0();
    unsigned char sub_55e190(char forceAll, char skipRebuild);
};
void SP_WritePillRecord(uint32_t a, uint32_t b);              // 0x558d50, cdecl
typedef void* (__thiscall *MgrQueryFn)(void* self, KVec3* out, PSys* ps, int z);
typedef uint32_t (__thiscall *ObjGetFn)(void* self);
typedef void (__thiscall *OwnerFn1)(void* self, const void* key);
typedef void (__thiscall *OwnerFn2)(void* self, const void* key, int z);
typedef void (__thiscall *AreaFn)(void* self);

// @ 0x0055e190
unsigned char Owner::sub_55e190(char forceAll, char skipRebuild) {
    unsigned char r0 = sub_55dfe0();
    if (r0 || forceAll) {
        // mirror the member-set tables (t1, then t2) into the sorted id set
        InsertIt out;
        TreeIt itEnd, itBeg;
        itEnd.sub_566c50((uint32_t)&t1.anchor);
        itBeg.sub_566c50(t1.left);
        out.c = &vs; out.pos = vs.b;
        for (; itBeg.node != itEnd.node; itBeg.sub_422c50()) {
            uint32_t* v = itBeg.sub_564f50();
            out.sub_565a80(v);
        }
        InsertIt res1 = out;
        uint32_t* pos = vs.b;
        TreeIt jEnd, jBeg;
        jEnd.sub_566c50((uint32_t)&t2.anchor);
        jBeg.sub_566c50(t2.left);
        for (; jBeg.node != jEnd.node; jBeg.sub_422c50()) {
            uint32_t* v = jBeg.sub_564f50();
            pos = vs.sub_566060(pos, v);
            pos += 1;
        }
        InsertIt res2; res2.c = &vs; res2.pos = pos;
    }
    char tag;
    KeySet keys;
    keys.sub_4b5980(&tag);
    if (!vs.sub_526430()) {
        if (!skipRebuild) {
            KVec3 tmp;
            tmp.sub_540470(&tag);
            uint32_t count = (uint32_t)(vs.e - vs.b);
            PSys ps;
            ps.sub_55eae0(vs.b, count);
            void* mgr = GetManager();
            ((MgrQueryFn)(*(void***)mgr)[0x38 / 4])(mgr, &tmp, &ps, 0);
            FUN_004f6b70(tmp.b, tmp.e);
            Key3 last = { 0, 0, 0 };
            for (Key3* k = tmp.b; k != tmp.e; ++k) {
                if (k->c != 0 && (k->c != last.c || k->a != last.a)) {
                    last = *k;
                    uint32_t t = k->c;
                    last.b = SP_EditorEntityToResourceType((t >> 16) & 0xff, 1);
                    uint32_t res[2];
                    keys.sub_4290c0(res, &last, false);
                }
            }
            ps.v.sub_4e1bf0();
            ps.vptr = (void**)0x13eb394;
            tmp.sub_540520();
        }
        for (uint32_t* e = vecBegin; e != vecEnd; e += 0x14) {
            RangeU rg;
            vs.sub_555980(&rg, e + 1);
            uint32_t* p = (rg.lo != rg.hi) ? rg.lo : vs.e;
            if (p != vs.e) {
                uint32_t res[2];
                keys.sub_4290c0(res, e, false);
            }
        }
        vs.sub_4769b0(vs.b, vs.e);
    }
    if (keys.size != 0) {
        TreeIt ka, kb;
        ka.sub_566c50(keys.aLeft);
        kb.sub_566c50((uint32_t)&keys.aRight);
        for (; ka.node != kb.node; ka.sub_422c50()) {
            uint32_t* kp0 = ka.sub_564f50();
            uint32_t* kp = kp0;
            ((OwnerFn2)vptr[0x74 / 4])(this, kp, 0);
            ((OwnerFn1)vptr[0x70 / 4])(this, kp);
        }
        HTab ht;
        ht.sub_5640f0(&tag);
        TreeIt cb, ce, d, f;
        cb.sub_566c50(t1.left);
        d.sub_5673e0(&cb);
        ce.sub_566c50((uint32_t)&t1.anchor);
        f.sub_5673e0(&ce);
        for (; d.node != f.node; d.sub_422c50()) {
            void* obj = (void*)d.sub_564f50()[1];
            uint32_t second = ((ObjGetFn)(*(void***)obj)[0x14 / 4])(obj);
            uint32_t first = ((ObjGetFn)(*(void***)obj)[0x10 / 4])(obj);
            uint32_t kv[2] = { first, second };
            uint32_t res[3];
            ht.sub_421a50(res, kv, false);
        }
        TreeIt gb, ge, h, i;
        gb.sub_566c50(t2.left);
        h.sub_5673e0(&gb);
        ge.sub_566c50((uint32_t)&t2.anchor);
        i.sub_5673e0(&ge);
        for (; h.node != i.node; h.sub_422c50()) {
            void* obj = (void*)h.sub_564f50()[1];
            uint32_t second = ((ObjGetFn)(*(void***)obj)[0x14 / 4])(obj);
            uint32_t first = ((ObjGetFn)(*(void***)obj)[0x10 / 4])(obj);
            uint32_t kv[2] = { first, second };
            uint32_t res[3];
            ht.sub_421a50(res, kv, false);
        }
        // iterator = {node, bucket}; end = first node of the bucket past the last
        struct { uint32_t* n; uint32_t** b; } cur;
        ht.sub_564140((uint32_t**)&cur);
        uint32_t** endB = ht.buckets + ht.nBuckets;
        uint32_t* endN = (uint32_t*)*endB;
        while ((uint32_t*)cur.n != endN) {
            SP_WritePillRecord(cur.n[0], cur.n[1]);
            cur.n = (uint32_t*)cur.n[2];
            while (!cur.n) { ++cur.b; cur.n = (uint32_t*)*cur.b; }
        }
        void* area = GetSaveArea(0x11ac19c);
        ((AreaFn)(*(void***)area)[0x24 / 4])(area);
        ht.sub_5534b0();
    }
    keys.sub_4e8a30(keys.aParent);
    return 0;
}

// @ 0x0055eae0
void* FUN_0055eae0(void* this_, int* first, int count) {
    *(void**)this_ = (void*)0x13eb394;
    *(void**)this_ = (void*)0x13f4af0;
    ((int*)this_)[1] = 0;
    ((int*)this_)[2] = 0;
    ((int*)this_)[3] = 0;
    uint32_t flag;
    FUN_00568740((int*)this_ + 1, first, first + count, flag);
    FUN_0050f0d0((void*)((int*)this_)[1], (void*)((int*)this_)[2]);
    return this_;
}

// @ 0x0055eb70
char FUN_0055eb70(void* this_, int* p) {
    int key = p[1];
    if (key == 0x1a99b06b)
        key = (int)SP_EditorEntityToResourceType((uint32_t)p[2] >> 16 & 0xff, 1);
    void* end = (void*)((int*)this_)[2];
    void* it = (void*)FUN_00567190((void*)((int*)this_)[1], end, &key);
    bool r = (it != end) && (key < *(int*)it);
    return (char)r;
}

// @ 0x0055ec10
void* FUN_0055ec10(void* this_, unsigned flags) {
    uint32_t* v = (uint32_t*)((char*)this_ + 4);
    for (uint32_t* p = (uint32_t*)v[0]; p < (uint32_t*)v[1]; ++p) {
    }
    FUN_00425990();
    *(void**)this_ = (void*)0x13eb394;
    if (flags & 1)
        EASTL_allocator_deallocate(this_);
    return this_;
}
