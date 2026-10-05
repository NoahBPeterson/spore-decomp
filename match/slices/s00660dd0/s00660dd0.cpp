// Slice s00660dd0: SP::cSPUIFeedFilter and its filter-button/asset-key containers.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" void  FUN_00d0c930(void* p);
extern "C" void  FUN_00646d70(void* first, void* last);
extern "C" void* SP_PropertyManager();
extern "C" void* SP_ObjectTemplateDB();
extern "C" void  FUN_0066a5e0(void* self, int a, int b);
extern "C" void* FUN_00660720(void* a, void* b);
extern "C" void  FUN_00660d70(void* a, void* b, void* c);
extern "C" void* FUN_00660fc0(unsigned n, void* a, void* b);
extern "C" void* FUN_00660ad0(void* a, void* b, void* c, void* d, void* e);
extern "C" void* FUN_00660b30(void* a, void* b, void* c);
extern "C" void  FUN_00660510(void* a, void* b, void* c);
extern "C" void  EA_Messaging_RemoveHandler(void* a, void* b, void* c, void* d, void* e);

// ---------------------------------------------------------------------------
// Element type of the 0x34-byte filter-button vector.
// ---------------------------------------------------------------------------
struct Blob14 { uint8_t x[0x14]; void Assign(Blob14* src); void FUN_006606a0(Blob14* src); };
struct E34 {
    uint32_t a;          // 0x00
    uint8_t  b;          // 0x04
    char     pad5[3];
    Blob14   c;          // 0x08
    uint8_t  d;          // 0x1c
    char     pad1d[3];
    Blob14   e;          // 0x20
};
struct Vec34 { E34* begin; E34* end; E34* cap; };
struct SubD8 { void FUN_0065f9e0(); };

// @ 0x00660dd0  eastl::copy_backward over 0x34-byte elements.
E34* CopyBackward34(E34* first, E34* last, E34* dest) {
    while (last != first) {
        --last; --dest;
        dest->a = last->a;
        dest->b = last->b;
        dest->c.Assign(&last->c);
        dest->d = last->d;
        dest->e.Assign(&last->e);
    }
    return dest;
}

// ---------------------------------------------------------------------------
// cSPUIFeedFilter (retail layout).
// ---------------------------------------------------------------------------
struct cSPUIFeedFilter {
    void* vt;                          // 0x00
    char  pad04[0xc];                  // 0x04
    char  mIsVisible;                  // 0x10
    char  pad11[3];
    void* mpLayout;                    // 0x14
    void* mpWinParent;                 // 0x18
    Vec34 mV0;                         // 0x1c
    char  pad28[8];                    // 0x28
    Vec34 mV1;                         // 0x30
    char  pad3c[8];                    // 0x3c
    char  m44[0x20];                   // 0x44
    void* mp64;                        // 0x64
    void* mp68;                        // 0x68
    void* mp6c;                        // 0x6c
    void* mp70;                        // 0x70
    void* mp74;                        // 0x74
    void* mp78;                        // 0x78
    void* mp7c;                        // 0x7c
    void* mp80;                        // 0x80
    void* mp84;                        // 0x84
    void* mp88;                        // 0x88
    void* mp8c;                        // 0x8c
    float mf90;                        // 0x90
    float mf94;                        // 0x94
    float mf98;                        // 0x98
    char  m9c[0x1c];                   // 0x9c..0xb7
    Vec34 mVb8;                        // 0xb8
    void* mC4;                         // 0xc4
    float mfC8;                        // 0xc8
    float mfCc;                        // 0xcc
    void* mD0;                         // 0xd0
    void* mD4;                         // 0xd4
    char  mD8[0x1c];                   // 0xd8..0xf3
    Vec34 mVf4;                        // 0xf4
    void* m100;                        // 0x100
    void* m104;                        // 0x104
    char  mb108;                       // 0x108
    char  pad109[3];
    char  mb10c;                       // 0x10c
};

// @ 0x00661020
void* cSPUIFeedFilter_ctor(cSPUIFeedFilter* s) {
    char* p = (char*)s;
    *(void**)(p + 4) = (void*)0x13eb384;
    *(void**)(p + 8) = (void*)0x13ec458;
    *(void**)(p + 0xc) = 0;
    *(void**)(p + 0) = (void*)0x14000e0;
    *(void**)(p + 4) = (void*)0x14000d0;
    *(void**)(p + 8) = (void*)0x14000c0;
    *(char*)(p + 0x10) = 0;
    *(void**)(p + 0x1c) = 0; *(void**)(p + 0x20) = 0; *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x30) = 0; *(void**)(p + 0x34) = 0; *(void**)(p + 0x38) = 0;
    FUN_0066a5e0(p + 0x44, 1, *(int*)0x140042c);
    *(void**)(p + 0x64) = 0; *(void**)(p + 0x68) = 0; *(void**)(p + 0x6c) = 0;
    *(void**)(p + 0x70) = 0; *(void**)(p + 0x74) = 0; *(void**)(p + 0x78) = 0;
    *(void**)(p + 0x7c) = 0; *(void**)(p + 0x80) = 0; *(void**)(p + 0x84) = 0;
    *(void**)(p + 0x88) = 0; *(void**)(p + 0x8c) = 0;
    *(float*)(p + 0x90) = 0.0f; *(float*)(p + 0x94) = 0.0f; *(float*)(p + 0x98) = 0.0f;
    *(void**)(p + 0xa0 + 4) = 0; *(void**)(p + 0xa0 + 8) = 0; *(void**)(p + 0xa0 + 0xc) = 0;
    *(void**)(p + 0xa4) = p + 0xa0;
    *(void**)(p + 0xa8) = 0;
    *(char*)(p + 0xac) = 0;
    *(void**)(p + 0xb0) = 0;
    *(void**)(p + 0xa0) = p + 0xa0;
    *(float*)(p + 0xc8) = 1.0f;
    *(float*)(p + 0xcc) = *(float*)0x1470f1c;
    *(void**)(p + 0xc4) = 0;
    *(void**)(p + 0xd0) = 0;
    *(void**)(p + 0xc0) = (void*)1;
    *(void**)(p + 0xbc) = (void*)0x154df28;
    *(void**)(p + 0xe0) = 0; *(void**)(p + 0xe4) = 0; *(void**)(p + 0xe8) = 0;
    *(void**)(p + 0xec) = 0; *(void**)(p + 0xf0) = 0; *(void**)(p + 0xf4) = 0;
    *(void**)(p + 0xf8) = 0; *(void**)(p + 0xfc) = 0;
    *(char*)(p + 0x10c) = 0;
    return s;
}

// @ 0x00660e30
void cSPUIFeedFilter_dtor(cSPUIFeedFilter* s) {
    char* p = (char*)s;
    *(void**)(p + 0) = (void*)0x14000e0;
    *(void**)(p + 4) = (void*)0x14000d0;
    *(void**)(p + 8) = (void*)0x14000c0;
    void* v = *(void**)(p + 0xf4);
    if (v) EASTL_allocator_deallocate(v);
    ((SubD8*)(p + 0xd8))->FUN_0065f9e0();
    FUN_00660720(*(void**)(p + 0xbc), *(void**)(p + 0xc0));
    *(void**)(p + 0xc4) = 0;
    if (*(uint32_t*)(p + 0xc0) > 1) EASTL_allocator_deallocate(*(void**)(p + 0xbc));
    FUN_00d0c930(*(void**)(p + 0xa8));
    void* h = *(void**)(p + 0x7c);
    if (h) { *(void**)(p + 0x7c) = 0; EA_Messaging_RemoveHandler(h, *(void**)(p + 0x80), *(void**)(p + 0x84), *(void**)(p + 0x88), *(void**)(p + 0x8c)); }
    void* a = *(void**)(p + 0x78); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x74); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x70); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x6c); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x68); if (a) (*(FnP)Vslot(a, 4))(a);
    a = *(void**)(p + 0x64); if (a) (*(FnP)Vslot(a, 8))(a);
    { Vec34* w = (Vec34*)(p + 0x30);
      FUN_00646d70(w->begin, w->end);
      if (w->begin && *(int*)((char*)w->begin - 4) != 0) EASTL_allocator_deallocate(w->begin); }
    { Vec34* w = (Vec34*)(p + 0x1c);
      FUN_00646d70(w->begin, w->end);
      if (w->begin && *(int*)((char*)w->begin - 4) != 0) EASTL_allocator_deallocate(w->begin); }
    *(void**)(p + 8) = (void*)0x13ec458;
    *(void**)(p + 4) = (void*)0x13eb394;
    *(void**)(p + 0) = (void*)0x13eb938;
}

// The 0x34-element vector algorithms below mirror the annotated decompile; helper
// calls are relocations so only the control flow matters.
extern "C" void  DoCopyKeys(void* first, void* last, void* dest);
extern "C" void  Fun0066_0ad0(void* a, void* b, void* c, void* d, void* e);
extern "C" void* Fun0066_0b30(void* a, void* b, void* c);
extern "C" void  Fun0066_0510(void* a, void* b, void* c);
extern "C" void* Fun0066_0d70(void* a, void* b, void* c);
extern "C" void* Fun0066_0fc0(unsigned n, void* a, void* b);
struct Key3 { uint32_t a, b, c; };
extern "C" void* FUN_006603d0(void* key, void* out);
extern "C" char  FUN_006a12a0(void* obj, int k, void* out);
extern "C" char  FUN_006a0ae0(void* obj, int k, void* a, void* b);

// @ 0x00661180
char FUN_00661180(void* vec, void* key) {
    DoCopyKeys(*(void**)((char*)vec + 0), *(void**)((char*)vec + 4), key);
    void* pm = SP_PropertyManager();
    void* local = 0;
    (*(void(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0xcc489c6f, &local);
    char r = 0;
    if (local) {
        Key3 k;
        r = FUN_006a12a0(local, 0x14593fac, &k);
        if (r) { r = 1; }
        if (r == 0 && local) (*(FnP)Vslot(local, 4))(local);
    }
    return r;
}

// @ 0x006612b0  eastl::map<unsigned,E34>::find-or-insert
void* FUN_006612b0(void* self, void* key) {
    char* p = (char*)self;
    uint32_t k = *(uint32_t*)key;
    E34* node = *(E34**)(p + 0xc);
    E34* found = (E34*)(p + 4);
    while (node) {
        if (node->a < k) node = *(E34**)node;
        else { found = node; node = *(E34**)((char*)node + 4); }
    }
    if (found == (E34*)(p + 4) || k < found->a) {
        E34* newn = (E34*)FUN_006603d0(key, 0);
        Fun0066_0b30(*(void**)p, found, newn);
        found = newn;
    }
    return found;
}

// @ 0x00661390  vector<E34>::operator=
void* FUN_00661390(void* self, void* other) {
    Vec34* v = (Vec34*)self;
    Vec34* o = (Vec34*)other;
    if (o != v) {
        unsigned n = (unsigned)(o->end - o->begin);
        unsigned cap = (unsigned)(v->cap - v->begin);
        if (cap < n) {
            E34* buf = (E34*)Fun0066_0fc0(n, o->begin, o->end);
            FUN_00646d70(v->begin, v->end);
            if (v->begin && *(int*)((char*)v->begin - 4) != 0) EASTL_allocator_deallocate(v->begin);
            v->end = buf + n; v->begin = buf; v->cap = buf + n;
            return self;
        }
        unsigned have = (unsigned)(v->end - v->begin);
        if (have < n) {
            E34* mid = v->begin + have;
            Fun0066_0d70(o->begin, o->begin + have, v->begin);
            Fun0066_0ad0(o->begin + have, o->end, mid, v->end, o->end);
            v->end = v->begin + n;
            return self;
        }
        Fun0066_0d70(o->begin, o->end, v->begin);
        FUN_00646d70(v->begin + n, v->end);
        v->end = v->begin + n;
    }
    return self;
}

// @ 0x006614d0  vector<E34>::insert(position, value)
void* FUN_006614d0(void* self, void* pos, void* value) {
    Vec34* v = (Vec34*)self;
    E34* end = v->end;
    if (end != v->cap) {
        E34* val = (E34*)value;
        if (pos <= val && val < end) val = (E34*)((char*)val + 0x34);
        if (end) {
            end->a = ((E34*)((char*)end - 0x34))->a;
            end->b = ((E34*)((char*)end - 0x34))->b;
            end->c.FUN_006606a0(&((E34*)((char*)end - 0x34))->c);
            end->d = ((E34*)((char*)end - 0x34))->d;
            end->e.FUN_006606a0(&((E34*)((char*)end - 0x34))->e);
        }
        CopyBackward34((E34*)pos, (E34*)((char*)v->end - 0x34), v->end);
        E34* p = (E34*)pos; E34* s = val;
        p->a = s->a; p->b = s->b; p->c.Assign(&s->c); p->d = s->d; p->e.Assign(&s->e);
        v->end = (E34*)((char*)v->end + 0x34);
        return pos;
    }
    unsigned n = (unsigned)(end - v->begin);
    unsigned nc = n ? n * 2 : 1;
    E34* buf = 0;
    if (nc) buf = (E34*)EASTL_allocator_allocate(nc * 0x34, "Editor", 0, 0,
                                                (const char*)0x13ebb38, 0xd1);
    if (buf) {
        E34* p = (E34*)Fun0066_0b30(v->begin, pos, buf);
        Fun0066_0510(v->begin, pos, buf);
        if (p) { E34* s = (E34*)value; p->a=s->a; p->b=s->b; p->c.Assign(&s->c); p->d=s->d; p->e.Assign(&s->e); }
        E34* p2 = (E34*)Fun0066_0b30(pos, v->end, (char*)p + 0x34);
        Fun0066_0510(pos, v->end, (char*)p + 0x34);
        if (v->begin && *(int*)((char*)v->begin - 4) != 0) EASTL_allocator_deallocate(v->begin);
        v->end = p2; v->begin = buf; v->cap = buf + nc;
    }
    return pos;
}

// @ 0x00661670  vector<E34>::push_back() (default)
void FUN_00661670(void* self) {
    Vec34* v = (Vec34*)self;
    E34* e = v->end;
    if (e < v->cap) {
        v->end = e + 1;
        if (e) {
            *(uint32_t*)(e->c.x + 0) = 0; *(uint32_t*)(e->c.x + 4) = 0; *(uint32_t*)(e->c.x + 8) = 0;
            *(uint32_t*)(e->e.x + 0) = 0; *(uint32_t*)(e->e.x + 4) = 0; *(uint32_t*)(e->e.x + 8) = 0;
        }
        return;
    }
    E34 tmp;
    *(uint32_t*)(tmp.c.x + 0) = 0; *(uint32_t*)(tmp.c.x + 4) = 0; *(uint32_t*)(tmp.c.x + 8) = 0;
    *(uint32_t*)(tmp.e.x + 0) = 0; *(uint32_t*)(tmp.e.x + 4) = 0; *(uint32_t*)(tmp.e.x + 8) = 0;
    FUN_006614d0(self, e, &tmp);
}

// @ 0x00661700  vector<E34>::pop_back()
void FUN_00661700(void* self) {
    Vec34* v = (Vec34*)self;
    E34* begin = v->begin;
    E34* end = v->end;
    Fun0066_0d70(end, end, begin);
    FUN_00646d70(begin, end);
    v->end = (E34*)((char*)v->end - 0x34);
}

// @ 0x00661740
char FUN_00661740(void* vec, void* key) {
    (void)vec; (void)key;
    void* pm = SP_PropertyManager();
    void* local = 0;
    (*(void(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0xcc489c6f, &local);
    char r = 0;
    if (local) { r = 1; (*(FnP)Vslot(local, 4))(local); }
    return r;
}

// @ 0x00661900
void FUN_00661900(int param, void* out) { (void)param; (void)out; }

// @ 0x00661a10
char FUN_00661a10(void* self, unsigned key) {
    char* p = (char*)self;
    if (*(void**)(p + 0xf4) == *(void**)(p + 0xf8)) return 1;
    (void)key;
    return 0;
}

// @ 0x00661b10
char FUN_00661b10(void* self, int param) { (void)self; (void)param; return 0; }

// @ 0x00661c00
char FUN_00661c00(void* self, void* a, void* b) { (void)self; (void)a; (void)b; return 0; }
