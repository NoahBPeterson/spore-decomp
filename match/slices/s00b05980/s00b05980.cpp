// Slice s00b05980 (frozen batch gold1, slice 94).
//
// A cluster of eastl container instantiations and EffectsManager helpers:
//   * 00b05980  bit-count lookup in a bucket
//   * 00b05a00  per-element placement transform
//   * 00b05b40  vector<AutoRefCount>::insert (fast path)
//   * 00b05c60  vector<EffectRec>::operator=
//   * 00b05d50  vector<EffectRec>::erase
//   * 00b05d80  vector<AutoRefCount<cMWModel>>::erase
//   * 00b05fa0  tree deserialisation
//   * 00b06190  vector<EffectRec>::insert (grow path)
//   * 00b06500  glyph-record copy forward
//   * 00b06550  glyph-record copy backward
//   * 00b065c0  cTreeData rebuild
//   * 00b06740  cInteractableObject::InitFromDefinition wrapper
//   * 00b06810  EffectRec removal by key
//   * 00b068c0  range scan / noun removal
//   * 00b06a40  object teardown + list removal
//   * 00b06bd0  proximity gather
//   * 00b06cd0  model-list teardown
//   * 00b06d90  vector<AutoRefCount>::resize
//
// Reconstructed from the retail disassembly.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

template<class T> static inline T& At(void* p, unsigned o) { return *(T*)((char*)p + o); }

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// indirect (this-call) helper plumbing
// ---------------------------------------------------------------------------
typedef void  (__thiscall *F0v)(void*);
typedef int   (__thiscall *F0i)(void*);
typedef void* (__thiscall *F0p)(void*);
typedef void  (__thiscall *F1i)(void*, int);
typedef void  (__thiscall *F1p)(void*, void*);
typedef void  (__thiscall *F2)(void*, void*, int);

static inline void* VS(void* o, int off) { return *(void**)((char*)(*(void**)o) + off); }
static inline int   vc_i(void* o, int off)          { return ((F0i)VS(o, off))(o); }
static inline void* vc_p(void* o, int off)          { return ((F0p)VS(o, off))(o); }
static inline void  vc_v(void* o, int off)          { ((F0v)VS(o, off))(o); }
static inline void  vc_vi(void* o, int off, int a)  { ((F1i)VS(o, off))(o, a); }
static inline void  vc_vp(void* o, int off, void* a){ ((F1p)VS(o, off))(o, a); }

// ---------------------------------------------------------------------------
// opaque helpers (definitions live elsewhere in the image)
// ---------------------------------------------------------------------------
extern "C" {
    void*  FUN_00b3d440();                                        // manager singleton
    void*  FUN_00b3d300(void* obj);                               // SP::NounManager(obj)
    void   FUN_00f47380(void* p);                                 // operator delete
    void*  FUN_00f473a0(uint32_t sz, const char* name, int a, int b, const char* file, int line);
    void   FUN_006271a0(Vec3* out, void* elem, void* xform);      // translateTransform
    void   FUN_0093a780(void* dst, void* count, int n, int c);    // ReadInt32
    void   FUN_0093a800(void* dst, void* val, int n, int c);      // ReadXXX
    void   FUN_00ac44a0(void* self, void* other);                 // vector<GlyphInfo>::operator=
    void*  FUN_00921580(void* node);                              // eastl::RBTreeIncrement
    void   FUN_00537dc0(void* self, void* other);                 // cSPTransform::operator=
    void*  FUN_00b027f0(void* first, void* last, void* dst);      // move-back 0x20 elems
    void*  FUN_00b027b0(void* first, void* last, void* dst);      // construct-copy range
    void   FUN_00b01470(void* first, void* last, void* dst);      // destroy range
    void   FUN_00b02b50(void* a, void* b, void* c);               // move one 0x20 elem
    void   FUN_00b02710(void* a, void* b, void* c, void* d, void* e);  // tail copy w/ allocator
    void   FUN_005f4e10(void* first, void* last, void* dst);      // 4-byte copy-back
    void   FUN_006782c0(void* first, void* last, void* dst);      // 4-byte copy-back
    void   FUN_011e0744(void* self, void* value, int n);          // vector<bool>::DoInsertValue
}

extern float g_167af5c, g_167af60, g_167af64;   // default placement (Vec3)
extern float g_156741c;                          // default orientation
extern uint32_t g_15673b8;                       // list capacity limit

// ---------------------------------------------------------------------------
// element / container models
// ---------------------------------------------------------------------------
struct Bucket { void** begin; void** end; };

struct Mgr {
    Bucket* GetBucket(uint32_t key, uint32_t kind);   // 0xb04ba0
};

// 0x20-byte serialisation record
struct EffectRec {
    uint32_t f00;   // +0x00
    uint32_t f04;   // +0x04
    uint32_t f08;   // +0x08
    uint32_t f0c;   // +0x0c
    void*    f10;   // +0x10  (Release at vtable+4)
    void*    f14;   // +0x14  (Release at vtable+0x38)
    uint32_t f18;   // +0x18
    uint32_t f1c;   // +0x1c
    void Reset();                          // 0xb00150
    void copyFrom(const EffectRec&);       // 0xb01cb0
    void construct(const EffectRec&);      // 0xb01d30
};

// 4-byte AutoRefCount vector
struct RefVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    void* erase(void* first, void* last);                  // 0xe25bd0
    void  insertSlow(void* pos, void* value);              // 0xaea5d0
    void  growAt(void* where, unsigned n, void* value);    // 0xbabb70
    void** F05b40(void** pos, void** value);               // 0x00b05b40
    void*  F05d80(void* pos);                              // 0x00b05d80
    void   F06d90(uint32_t n);                             // 0x00b06d90
};

// 0x20-byte EffectRec vector
struct EffectVec {
    EffectRec* begin;   // +0
    EffectRec* end;     // +4
    EffectRec* cap;     // +8
    EffectRec* allocateCopy(unsigned n, EffectRec* first, EffectRec* last);  // 0xb044c0
    void       destroyRange(EffectRec* first, EffectRec* last);              // 0xb006f0
    EffectVec* F05c60(EffectVec* other);                                     // 0x00b05c60
    EffectRec* F05d50(EffectRec* pos);                                       // 0x00b05d50
    void       F06190(EffectRec* pos, EffectRec* value);                     // 0x00b06190
};

struct XformObj {
    Vec3*    F05a00(Vec3* out, uint32_t index);   // 0x00b05a00
    uint32_t Count();                             // 0xb058f0
};

struct Tree {
    void  reset(void* a);                  // 0xb04350
    void  add(void* a, void* b, uint32_t c);   // 0xb04f70
    void  addRange(void* a, void* b, void* c); // 0xb04ed0
    int*  lowerBound(void* out, const void* key);    // 0xb02430
};

struct Interactable {
    bool InitFromDefinition(void* a, void* b, void* c);   // 0xc3fc80
    bool F06740(void* a, void* b, void* c);                // 0x00b06740
};

struct NounMgr {
    void RemoveNoun(void* obj);   // 0xb225d0
};

struct CTreeData {
    void* ctor();   // 0xb01770
};

// ---------------------------------------------------------------------------
// 00b05980  popcount of the bucket node selected by [this+0x54]
// ---------------------------------------------------------------------------
struct BitRec {
    uint32_t F05980();
    uint8_t  pad[0x58];
};

uint32_t BitRec::F05980() {
    uint32_t index = At<uint32_t>(this, 0x54);
    uint32_t kind  = At<uint32_t>(this, 0x50);
    uint32_t key   = At<uint32_t>(this, 0x4c);
    uint32_t result = 0;
    Mgr* mgr = (Mgr*)FUN_00b3d440();
    Bucket* b = mgr->GetBucket(key, kind);
    if (b != 0) {
        if (index < (uint32_t)(((char*)b->end - (char*)b->begin) >> 2)) {
            void* node = ((void**)b->begin)[index];
            if (node != 0) {
                uint32_t v = At<uint32_t>(node, 0x48);
                v = v - ((v >> 1) & 0x55555555);
                v = ((v >> 2) & 0x33333333) + (v & 0x33333333);
                v = (v + (v >> 4)) & 0x0F0F0F0F;
                result = (v * 0x01010101) >> 24;
            }
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 00b05a00  placement transform of element #index
// ---------------------------------------------------------------------------
// @ 0x00b05a00
Vec3* XformObj::F05a00(Vec3* out, uint32_t index) {
    out->x = g_167af5c;
    out->y = g_167af60;
    out->z = g_167af64;
    uint32_t n = Count();
    if (index < n) {
        Vec3 tmp;
        void* list = At<void*>(this, 0xa4);
        FUN_006271a0(&tmp, (char*)list + index * 0x38, (char*)this + 0x58);
        out->x = tmp.x;
        out->y = tmp.y;
        out->z = tmp.z;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 00b05b40  RefVec::insert(pos, value) - returns iterator to the slot
// ---------------------------------------------------------------------------
void** RefVec::F05b40(void** pos, void** value) {
    void** e = (void**)end;
    int index = (int)((char*)pos - (char*)begin) >> 2;
    if (pos != e || e == (void**)cap) {
        insertSlow(pos, value);
    } else {
        end = (char*)e + 4;
        if (e != 0) {
            void* p = *value;
            *e = p;
            if (p != 0) vc_v(p, 0);
        }
    }
    return (void**)((char*)begin + index * 4);
}

// ---------------------------------------------------------------------------
// 00b05c60  EffectVec::operator=
// ---------------------------------------------------------------------------
// @ 0x00b05c60
EffectVec* EffectVec::F05c60(EffectVec* other) {
    if (other == this) return this;
    EffectRec* ob = other->begin;
    EffectRec* oe = other->end;
    unsigned otherN = (unsigned)((char*)oe - (char*)ob) >> 5;
    if ((unsigned)((char*)cap - (char*)begin) >> 5 < otherN) {
        EffectRec* nb = allocateCopy(otherN, ob, oe);
        destroyRange(begin, end);
        EffectRec* old = begin;
        if (old != 0 && *(int*)((char*)old - 4) != 0) FUN_00f47380(old);
        end   = (EffectRec*)((char*)nb + otherN * 0x20);
        cap   = (EffectRec*)((char*)nb + otherN * 0x20);
        begin = nb;
        return this;
    }
    unsigned myN = (unsigned)((char*)end - (char*)begin) >> 5;
    if (myN < otherN) {
        FUN_00b027f0((char*)ob + myN * 0x20, oe, begin);
        void* mid = (char*)other->begin + ((unsigned)((char*)end - (char*)begin) >> 5) * 0x20;
        FUN_00b02710(&other, mid, other->end, end, other);
        end = (EffectRec*)((char*)begin + otherN * 0x20);
        return this;
    }
    void* stop = FUN_00b027f0(ob, oe, begin);
    destroyRange((EffectRec*)stop, end);
    end = (EffectRec*)((char*)begin + otherN * 0x20);
    return this;
}

// ---------------------------------------------------------------------------
// 00b05d50  EffectVec::erase(pos)
// ---------------------------------------------------------------------------
EffectRec* EffectVec::F05d50(EffectRec* pos) {
    if (pos + 1 < end) {
        FUN_00b027f0(pos + 1, end, pos);
    }
    end = (EffectRec*)((char*)end - 0x20);
    end->Reset();
    return pos;
}

// ---------------------------------------------------------------------------
// 00b05d80  RefVec::erase(pos) for AutoRefCount<cMWModel>
// ---------------------------------------------------------------------------
// @ 0x00b05d80
void* RefVec::F05d80(void* pos) {
    if ((char*)pos + 4 < (char*)end) {
        FUN_005f4e10((char*)pos + 4, end, pos);
    }
    end = (char*)end - 4;
    void* v = *(void**)end;
    if (v != 0) {
        int cnt = At<int>(v, 0x40);
        if (cnt > 1) {
            At<int>(v, 0x40) = cnt - 1;
        } else {
            bool flag = (At<uint32_t>(v, 4) >> 31) & 1;
            void* inner = *(void**)v;
            ((F2)VS(inner, 0x170))(inner, v, (int)flag);
        }
    }
    return pos;
}

// ---------------------------------------------------------------------------
// 00b05fa0  deserialise a tree
// ---------------------------------------------------------------------------
struct Pair { void* a; void* b; };
struct Rec3 { void* a; void* b; void* c; };

// @ 0x00b05fa0
void FUN_00b05fa0(int* src, int* tree) {
    Tree* t = (Tree*)tree;
    t->reset((void*)tree[3]);
    int* self1 = tree + 1;
    tree[1] = (int)self1;
    tree[2] = (int)self1;
    tree[3] = 0;
    *((uint8_t*)tree + 0x10) = 0;
    tree[5] = 0;

    uint32_t count = 0;
    void* q = vc_p(vc_p(src, 0x20), 0x18);
    FUN_0093a780(q, &count, 1, 0);

    uint32_t i = 0;
    while (i < count) {
        void* obj = 0;
        void* s = vc_p(vc_p(src, 0x20), 0x18);
        Pair val;
        FUN_0093a800(s, &val, 1, 0);
        vc_v(src, 0x1c);
        if (obj != 0) { void* h = obj; obj = 0; vc_v(h, 4); }
        vc_vp(src, 0x28, (void*)0x02e9688e);
        vc_v(src, 0x1c);
        if (obj != 0) vc_v(obj, 0);
        Rec3 out;
        out.a = val.a;
        out.b = val.b;
        out.c = obj;
        uint32_t flags = 0;
        t->add(&out, &val, flags);
        if (obj != 0) vc_v(obj, 4);
        i++;
    }
    vc_v(src, 0x1c);
}

// ---------------------------------------------------------------------------
// 00b06190  EffectVec::insert(pos, value) - grow path
// ---------------------------------------------------------------------------
// @ 0x00b06190
void EffectVec::F06190(EffectRec* pos, EffectRec* value) {
    EffectRec* e = end;
    if (e != cap) {
        if (value >= pos && value < e) {
            value = (EffectRec*)((char*)value + 0x20);
        }
        if (e != 0) e->copyFrom(*(EffectRec*)((char*)e - 0x20));
        FUN_00b02b50(pos, (char*)end - 0x20, end);
        pos->construct(*value);
        end = (EffectRec*)((char*)end + 0x20);
        return;
    }
    int n = (int)((char*)end - (char*)begin) >> 5;
    EffectRec* nb;
    if (n != 0) {
        n = n * 2;
        if (n == 0) { nb = 0; goto have_nb; }
    } else {
        n = 1;
    }
    nb = (EffectRec*)FUN_00f473a0(n << 5, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
have_nb:
    EffectRec* old = begin;
    EffectRec* mid = (EffectRec*)FUN_00b027b0(old, pos, nb);
    FUN_00b01470(old, pos, nb);
    if (mid != 0) {
        mid->copyFrom(*value);
    }
    EffectRec* e2 = end;
    void* ret = FUN_00b027b0(pos, e2, (char*)mid + 0x20);
    FUN_00b01470(pos, e2, (char*)mid + 0x20);
    if (old != 0 && *(int*)((char*)old - 4) != 0) FUN_00f47380(old);
    begin = nb;
    end   = (EffectRec*)ret;
    cap   = (EffectRec*)((char*)nb + n * 0x20);
}

// ---------------------------------------------------------------------------
// 00b06500  forward copy of 0x24-byte glyph records
// ---------------------------------------------------------------------------
struct GlyphVec { void* begin; void* end; void* cap; };
struct GlyphSub { void assign(const GlyphSub& other); };   // vector<GlyphInfo>::operator= @0xac44a0
struct GlyphElem {
    uint32_t f00;   // +0x00
    uint8_t  f04;   // +0x04
    uint8_t  pad[3];
    GlyphVec vec;   // +0x08
    uint32_t f14;   // +0x14
    uint32_t f18;   // +0x18
    uint32_t f1c;   // +0x1c
    uint32_t f20;   // +0x20
};

GlyphElem* FUN_00b06500(GlyphElem* first, GlyphElem* last, GlyphElem* dst) {
    if (first != last) {
        do {
            dst->f04 = first->f04;
            ((GlyphSub*)&dst->vec)->assign(*(GlyphSub*)&first->vec);
            dst->f1c = first->f1c;
            dst->f20 = first->f20;
            first = (GlyphElem*)((char*)first + 0x24);
            dst   = (GlyphElem*)((char*)dst + 0x24);
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 00b06550  backward copy of 0x24-byte glyph records
// ---------------------------------------------------------------------------
GlyphElem* FUN_00b06550(GlyphElem* first, GlyphElem* last, GlyphElem* dst) {
    if (last != first) {
        do {
            last = (GlyphElem*)((char*)last - 0x24);
            dst  = (GlyphElem*)((char*)dst - 0x24);
            dst->f04 = last->f04;
            ((GlyphSub*)&dst->vec)->assign(*(GlyphSub*)&last->vec);
            dst->f1c = last->f1c;
            dst->f20 = last->f20;
        } while (last != first);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 00b065c0  rebuild the cTreeData list from a source ref vector
// ---------------------------------------------------------------------------
// @ 0x00b065c0
void FUN_00b065c0(RefVec* out, RefVec* src) {
    unsigned want = (unsigned)((char*)out->end - (char*)out->begin) >> 7;
    unsigned have = (unsigned)((char*)src->end - (char*)src->begin) >> 2;
    if (have < want) {
        uint32_t zero = 0;
        src->growAt(src->end, want - have, &zero);
    } else {
        src->erase((char*)src->begin + want * 4, src->end);
    }

    unsigned n = (unsigned)((char*)out->end - (char*)out->begin) >> 7;
    uint32_t zero = 0;
    unsigned i = 0;
    if (n == 0) return;
    unsigned off = 0;
    do {
        char* e  = (char*)out->begin + off;
        void* td = FUN_00f473a0(0x80, "Simulator/cTreeData_BackwardsCompatibility", 0, 0, 0, 0);
        if (td != 0) td = ((CTreeData*)td)->ctor();
        void** slot = (void**)((char*)src->begin + i * 4);
        void* old = *slot;
        if (td != old) {
            if (td != 0) vc_v(td, 0);
            *slot = td;
            if (old != 0) vc_v(old, 4);
        }
        FUN_00537dc0((char*)td + 0x0c, e + 0x0c);
        At<uint32_t>(td, 0x48) = At<uint32_t>(e, 0x48);
        At<uint32_t>(td, 0x4c) = At<uint32_t>(e, 0x4c);
        At<uint32_t>(td, 0x50) = At<uint32_t>(e, 0x50);
        At<uint32_t>(td, 0x54) = At<uint32_t>(e, 0x54);
        At<uint32_t>(td, 0x58) = At<uint32_t>(e, 0x58);
        void* p1 = At<void*>(e, 0x68);
        void* p2 = At<void*>(td, 0x68);
        if (p1 != p2) {
            if (p1 != 0) vc_v(p1, 0);
            At<void*>(td, 0x68) = p1;
            if (p2 != 0) vc_v(p2, 4);
        }
        off += 0x80;
        At<uint32_t>(td, 0x5c) = At<uint32_t>(e, 0x5c);
        At<uint32_t>(td, 0x60) = At<uint32_t>(e, 0x60);
        At<uint32_t>(td, 0x64) = At<uint32_t>(e, 0x64);
        At<uint32_t>(td, 0x6c) = At<uint32_t>(e, 0x6c);
        At<uint32_t>(td, 0x70) = At<uint32_t>(e, 0x70);
        At<uint32_t>(td, 0x74) = At<uint32_t>(e, 0x74);
        At<uint8_t>(td, 0x7c)  = At<uint8_t>(e, 0x7c);
        i++;
    } while (i < n);
    (void)zero;
}

// ---------------------------------------------------------------------------
// 00b06740  cInteractableObject::InitFromDefinition wrapper
// ---------------------------------------------------------------------------
// @ 0x00b06740
bool Interactable::F06740(void* a, void* b, void* c) {
    if (InitFromDefinition(a, b, c)) {
        vc_v(this, 0x5c);
        vc_vp((char*)this + 0x34, 0x94, (void*)&g_156741c);
        uint32_t v = 2;
        if (At<uint32_t>(this, 0x16c) != v) {
            At<uint32_t>(this, 0x168) = 0;
            At<uint32_t>(this, 0x16c) = v;
        }
        At<uint32_t>(this, 0x148) |= 1;
        void* self = this;
        vc_v(this, 0);
        Mgr* mgr = (Mgr*)FUN_00b3d440();
        RefVec* vec = (RefVec*)((char*)mgr + 0x1b905c);
        if ((char*)vec->end < (char*)vec->cap) {
            void** e = (void**)vec->end;
            vec->end = (char*)e + 4;
            if (e != 0) {
                *e = this;
                vc_v(this, 0);
            }
        } else {
            vec->insertSlow(vec->end, &self);
        }
        if (self != 0) vc_v(self, 4);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 00b06810  remove the first EffectRec whose +0x10 matches key
// ---------------------------------------------------------------------------
struct EffectOwner {
    bool F06810(uint32_t key);
};

// @ 0x00b06810
bool EffectOwner::F06810(uint32_t key) {
    EffectRec* it  = *(EffectRec**)((char*)this + 0x160e8);
    EffectRec* end = *(EffectRec**)((char*)this + 0x160ec);
    if (it == end) return false;
    do {
        uint32_t f = At<uint32_t>(it, 0x10);
        if (f != 0 && f == key) {
            if (it + 1 < end) {
                FUN_00b027f0(it + 1, end, it);
            }
            *(EffectRec**)((char*)this + 0x160ec) = (EffectRec*)((char*)end - 0x20);
            EffectRec* e = *(EffectRec**)((char*)this + 0x160ec);
            e->f00 = 0;
            e->f08 = 0;
            e->f0c = 0;
            void* p = e->f10;
            if (p != 0) { e->f10 = 0; vc_v(p, 4); }
            p = e->f14;
            if (p != 0) { e->f14 = 0; vc_v(p, 0x38); }
            e->f18 = 0;
            if (e->f14 != 0) vc_v(e->f14, 0x38);
            if (e->f10 != 0) vc_v(e->f10, 4);
            return true;
        }
        it = (EffectRec*)((char*)it + 0x20);
    } while (it != end);
    return false;
}

// ---------------------------------------------------------------------------
// 00b068c0  range scan: retire each noun in the range
// ---------------------------------------------------------------------------
struct RangeScan {
    void F068c0(void* range, uint32_t a, uint32_t b);
};

// @ 0x00b068c0
void RangeScan::F068c0(void* range, uint32_t a, uint32_t b) {
    if (At<uint32_t>(range, 0x14) == 0) return;
    int* node = (int*)At<void*>(range, 8);
    int* stop = (int*)((char*)range + 4);
    if (a != 0 || b != 0) {
        int pair[2];
        ((Tree*)range)->lowerBound(pair, &a);
        stop = (int*)pair[1];
        node = (int*)pair[0];
    }
    int* cur = node;
    if (cur != stop) {
        char* base = (char*)this + 0x1b9174;
        do {
            int* obj = (int*)At<void*>(cur, 0x18);
            int* held = obj;
            if (obj != 0) {
                vc_v(obj, 0);
                int* sub = *(int**)((char*)obj + 0x1c4);
                if (sub != 0) {
                    vc_vi(sub, 0x0c, 1);
                    sub = *(int**)((char*)obj + 0x1c4);
                    if (sub != 0) {
                        *(int**)((char*)obj + 0x1c4) = 0;
                        vc_v(sub, 4);
                    }
                }
                void* vd = *(void**)((char*)obj + 0x1a0);
                void* vs = *(void**)((char*)obj + 0x19c);
                FUN_011e0744(vs, vd, 0);
                *(int*)((char*)obj + 0x1a0) =
                    *(int*)((char*)obj + 0x1a0) + ((int)vd - (int)vs >> 2) * -4;
            }
            RefVec* vec = (RefVec*)base;
            if ((unsigned)((char*)vec->end - (char*)vec->begin) >> 2 < g_15673b8) {
                vc_v(obj, 0x44);
                void** e = (void**)vec->end;
                if (e < (void**)vec->cap) {
                    vec->end = (char*)e + 4;
                    if (e != 0) { *e = obj; vc_v(obj, 0); }
                } else {
                    vec->insertSlow(vec->end, &held);
                    obj = held;
                }
            } else {
                void* nm = FUN_00b3d300(obj);
                ((NounMgr*)nm)->RemoveNoun(obj);
            }
            if (obj != 0) vc_v(obj, 4);
            cur = (int*)FUN_00921580(cur);
        } while (cur != stop);
    }
    ((Tree*)range)->addRange((void*)&a, (void*)node, (void*)stop);
}

// ---------------------------------------------------------------------------
// 00b06a40  object teardown + removal from the manager list
// ---------------------------------------------------------------------------
struct TearDown {
    void** F06a40(void** slot, int flag);
};

// @ 0x00b06a40
void** TearDown::F06a40(void** slot, int flag) {
    void* obj = *slot;
    if (obj != 0) {
        vc_v(obj, 0);
        At<uint32_t>(obj, 0x154) = 0;
        At<uint32_t>(obj, 0x158) = 0x6d60a1cc;
        At<uint32_t>(obj, 0x15c) = 0xffffffff;
        At<uint32_t>(obj, 0x160) = 0xffffffff;
        At<uint32_t>(obj, 0x164) = 0xffffffff;
        void* p = At<void*>(obj, 0x108);
        if (p != 0) { At<void*>(obj, 0x108) = 0; vc_v(p, 4); }
        At<uint32_t>(obj, 0x16c) = 6;
        At<uint32_t>(obj, 0x148) &= ~2u;
        p = At<void*>(obj, 0x108);
        if (p != 0) { At<void*>(obj, 0x108) = 0; vc_v(p, 4); }
        vc_vp((char*)obj + 0x34, 0x38, (void*)&g_167af5c);
        At<uint8_t>(obj, 0xa5) = 1;
        At<uint8_t>(obj, 0xa9) = 0;
        vc_vi((char*)obj + 0x34, 0x40, 0x3f800000);
        if (vc_i((char*)obj + 0x34, 0xac) != 0) {
            void* q = vc_p((char*)obj + 0x34, 0xac);
            At<uint32_t>(q, 4) &= ~1u;
            q = vc_p((char*)obj + 0x34, 0xac);
            void* inner = *(void**)q;
            ((F2)VS(inner, 0x16c))(inner, q, 0);
        }
        if (flag != 0) {
            vc_vi((char*)obj + 0x34, 0x40, 0x3f800000);
            RefVec* vec = (RefVec*)((char*)this + 0x1b8f44);
            if ((char*)vec->end < (char*)vec->cap) {
                void** e = (void**)vec->end;
                vec->end = (char*)e + 4;
                if (e != 0) { *e = obj; vc_v(obj, 0); }
            } else {
                vec->insertSlow(vec->end, &obj);
                obj = *(void**)vec->end;
            }
        }
    }
    RefVec* vec = (RefVec*)((char*)this + 0x1b905c);
    if ((char*)slot + 4 < (char*)vec->end) {
        FUN_006782c0((char*)slot + 4, vec->end, slot);
    }
    vec->end = (char*)vec->end - 4;
    void* last = *(void**)vec->end;
    if (last != 0) vc_v(last, 4);
    if (obj != 0) vc_v(obj, 4);
    return slot;
}

// ---------------------------------------------------------------------------
// 00b06bd0  gather objects within radius of a point
// ---------------------------------------------------------------------------
struct Proximity {
    void F06bd0(Vec3* point, float radius, RefVec* out);
};

// @ 0x00b06bd0
void Proximity::F06bd0(Vec3* point, float radius, RefVec* out) {
    out->erase(out->begin, out->end);
    float rr = radius * radius;
    void** it  = (void**)*(void**)((char*)this + 0x1b905c);
    void** end = (void**)*(void**)((char*)this + 0x1b9060);
    while (it != end) {
        void* obj = *it;
        Vec3* p = (Vec3*)vc_p((char*)obj + 0x34, 0x2c);
        float dx = p->x - point->x;
        float dy = p->y - point->y;
        float dz = p->z - point->z;
        if (dx * dx + dy * dy + dz * dz < rr) {
            vc_v(obj, 0);
            if ((char*)out->end < (char*)out->cap) {
                void** e = (void**)out->end;
                out->end = (char*)e + 4;
                if (e != 0) { *e = obj; vc_v(obj, 0); }
            } else {
                out->insertSlow(out->end, &obj);
                obj = *(void**)out->end;
            }
            if (obj != 0) vc_v(obj, 4);
        }
        it = it + 1;
    }
    volatile int selfbits = (int)this;
    if (selfbits == *(volatile int*)((char*)this + 0x1b905c)) return;
}

// ---------------------------------------------------------------------------
// 00b06cd0  tear down every model in the +0x16504 list
// ---------------------------------------------------------------------------
struct ModelList {
    void F06cd0();
};

// @ 0x00b06cd0
void ModelList::F06cd0() {
    void* it  = *(void**)((char*)this + 0x16504);
    void* end = *(void**)((char*)this + 0x16508);
    while (it != end) {
        void* o = *(void**)it;
        if (o != 0) {
            void* p = At<void*>(o, 0x64);
            if (p != 0) { At<void*>(o, 0x64) = 0; vc_v(p, 4); }
            At<uint32_t>(o, 4) &= ~1u;
            void* inner = *(void**)o;
            ((F2)VS(inner, 0x16c))(inner, o, 0);
        }
        void* e2 = *(void**)((char*)this + 0x16508);
        if ((char*)it + 4 < (char*)e2) {
            FUN_005f4e10((char*)it + 4, e2, it);
        }
        *(char**)((char*)this + 0x16508) -= 4;
        void* v = *(void**)*(void**)((char*)this + 0x16508);
        if (v != 0) {
            int cnt = At<int>(v, 0x40);
            if (cnt > 1) {
                At<int>(v, 0x40) = cnt - 1;
            } else {
                int flag = (int)(At<uint32_t>(v, 4) >> 31) & 1;
                void* inner = *(void**)v;
                ((F2)VS(inner, 0x170))(inner, v, flag);
            }
        }
        end = *(void**)((char*)this + 0x16508);
    }
}

// ---------------------------------------------------------------------------
// 00b06d90  RefVec::resize(n)
// ---------------------------------------------------------------------------
void RefVec::F06d90(uint32_t n) {
    if (n > (uint32_t)(((char*)end - (char*)begin) >> 2)) {
        uint32_t cur = (uint32_t)(((char*)end - (char*)begin) >> 2);
        uint32_t zero = 0;
        growAt(end, n - cur, &zero);
    } else {
        erase((char*)begin + n * 4, end);
    }
}
