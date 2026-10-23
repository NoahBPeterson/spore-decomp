// Slice s00e65ad0 -- SPGonzago/SPCellGame.obj (cell stage): the cPartGfx teardown, the
// part/effect release + continuous-death helpers, the recursive effect-event fan-out and the
// layer-catalog effect registration.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(u32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
#define B(p,o) (*(u8*)((char*)(p) + (o)))
#define VT(p)  (*(void***)(p))

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- globals
extern char*  gspCellGame;        // 0x016b3c04
extern char*  gspCellGfx;         // 0x016b3c08
extern Vec3   gCellWorldCenter;   // 0x016b3c28
extern float  g_15a7c4c[4];       // 0x015a7c4c  (0,0,0,1)
extern float  g_one_1485720;      // 0x01485720  1.0f
extern char   g_16b3dac[36];      // 0x016b3dac  identity rotation matrix

// ---------------------------------------------------------------- pools / helper objects
struct Pool {
    void* GetSafe(int h);      // 0x00b721d0, thiscall ret 4
    void* Get(int h);          // 0x00b72210, thiscall ret 4
    int   Alloc();             // 0x00b72160, thiscall ret
    void  Free(int h);         // 0x00b72260, thiscall ret 4
};
static Pool* cells() { return (Pool*)(gspCellGame + 0x1c); }

typedef void (__thiscall *PFN_v)(void*);
typedef void (__thiscall *PFN_i)(void*, int);
typedef void (__thiscall *PFN_vp)(void*, void*);
typedef void (__stdcall  *PFN_sb)(void*, unsigned);

struct cCellGfxStub { void pushObj(void* p); };            // 0x00e653a0, thiscall (this = gspCellGfx)
struct RefVecOwner  { void push(void* p); };               // 0x00e65970, thiscall (this = gspCellGfx)
struct Obj74        { char d[0x74]; void ctor(const void* src); }; // 0x00e61750
struct ObjVec74 {
    void* b; void* e; void* c;
    void insertGrow(void* pos, void* val);                 // 0x00e65200
};
struct XForm { char d[0x38]; void assign(const void* src); }; // 0x00537dc0
struct RbTree {
    void find(void** out, const unsigned* key);            // 0x00e5c780
    void* operatorIndex(const int* key);                   // 0x00badea0 eastl::map<K,int>::operator[]
};

// ---------------------------------------------------------------- callees
extern "C" void  FUN_00e65a00(int* ref);                    // 0x00e65a00
extern "C" void  FUN_00e826e0(int sound);                   // 0x00e826e0
extern "C" int   FUN_00e57340(void* part);                  // 0x00e57340
extern "C" void  FUN_00e4f680(int val);                     // 0x00e4f680
extern "C" void  FUN_00e4ec30(int base, int idx);           // 0x00e4ec30
extern "C" void* FUN_00e4cce0(int idx);                     // 0x00e4cce0  (layer-catalog entry)
extern "C" void* FUN_00e4cc40(int id, void* out);           // 0x00e4cc40  (thunk_FUN_00e823a0)
extern "C" void* FUN_00e4ce40(void* out);                   // 0x00e4ce40
extern "C" void  FUN_00e4fc20(int idx, int handle);         // 0x00e4fc20
extern "C" void  __fastcall FUN_00743b50(void* ref);        // 0x00743b50
extern "C" void  __fastcall FUN_00e82130(void* ref);        // 0x00e82130
extern "C" void* CreateEffectSafe(void* world, u32 id, int flags, void* out); // 0x00628450
extern "C" void  FUN_00e63480(void* effect, int a, void* desc);  // 0x00e63480  sPartIntersectTarget
extern "C" void  FUN_00e65410(int id, int flag);            // 0x00e65410
extern "C" void  FUN_00e64980(int id);                      // 0x00e64980
extern "C" u32   FNV1_String8(const char* s, u32 seed, int one); // 0x00932e80
extern "C" void* FUN_0067ddd0();                            // 0x0067ddd0  SP::EffectsManager
extern "C" void* FUN_0067dd60();                            // 0x0067dd60
extern "C" void  __fastcall FUN_00e619a0(void* p);          // 0x00e619a0  Obj ctor (this = ecx)
extern "C" void* FUN_005f4e10(void* a, void* b, void* c);   // 0x005f4e10  eastl copy_impl::do_copy
extern "C" void  FUN_005f3680(void* a, void* b);            // 0x005f3680  DoDestroyValues (thiscall)
extern "C" void* FUN_006f43e0(void* a, void* b, void* c);   // 0x006f43e0  intrusive copy
extern "C" void  FUN_0070f520(void* a, void* b);            // 0x0070f520  DestroyRange (thiscall)
extern "C" void* FUN_011e0744(void* begin, void* end, int v);// 0x011e0744  eastl vector DoInsertValue
extern "C" void  FUN_009a9600(void* tree, void* node);      // 0x009a9600  DoNukeSubtree (thiscall)
extern "C" void  __cdecl FUN_00f47380(void* p);             // 0x00f47380  operator delete
extern "C" void* memcpy(void* dst, const void* src, unsigned n);

// forward decls (mutually recursive)
void FUN_00e66280(int a, int b);
void FUN_00e663b0(int map, int key);
void FUN_00e665c0(int map, int id);

// ------------------------------------------------------------------ 0x00e65ad0
// SP::cPartGfx::Clear -- release every effect/resource owned by a part.  The three pointer
// vectors at +0x78/+0x64/+0xb0 are drained (each element released then the vector reset), the
// ten single effect handles at +0x60/+0x90/+0x94/+0x8c/+0x98/+0x9c/+0xa0/+0xa4/+0xa8/+0xac are
// released, then sound (+0x10), creature (+0x24) and the attachment list (+0x28/+0x2c) are torn
// down and the per-attachment slots are released according to their descriptor kind.
// @ 0x00e65ad0
void FUN_00e65ad0(void* self, u8 destroy)
{
    char* this_ = (char*)self;

    // release one effect handle: route through FUN_00e65a00 when destroying, else vtable-release
    #define RELS(off) do {                                                       \
        void* p_ = *(void**)(this_ + (off));                                     \
        if (destroy == 0) { int loc_ = (int)p_; FUN_00e65a00(&loc_); }           \
        else if (p_ != 0) {                                                      \
            ((PFN_i)VT(p_)[0xc / 4])(p_, 1);                                     \
            ((PFN_v)VT(p_)[4 / 4])(p_);                                          \
        }                                                                        \
    } while (0)

    // drain one pointer vector [b,e): release each element, then eastl erase-all
    #define DRAIN(b, e) do {                                                     \
        int i_ = 0;                                                              \
        int n_ = (I(this_, (e)) - I(this_, (b))) >> 2;                           \
        if (n_ > 0) {                                                            \
            do {                                                                 \
                void* p_ = *(void**)((char*)(long)I(this_, (b)) + i_ * 4);       \
                if (destroy == 0) { int loc_ = (int)p_; FUN_00e65a00(&loc_); }   \
                else if (p_ != 0) {                                              \
                    ((PFN_i)VT(p_)[0xc / 4])(p_, 1);                             \
                    ((PFN_v)VT(p_)[4 / 4])(p_);                                  \
                }                                                                \
                ++i_;                                                            \
                n_ = (I(this_, (e)) - I(this_, (b))) >> 2;                       \
            } while (i_ < n_);                                                   \
        }                                                                        \
        int d_ = I(this_, (e)) - I(this_, (b));                                  \
        FUN_011e0744(*(void**)(this_ + (b)), *(void**)(this_ + (e)), 0);         \
        I(this_, (e)) = I(this_, (e)) - d_;                                      \
    } while (0)

    // ---- pointer vectors 0x78, 0x64, 0xb0 ----
    DRAIN(0x78, 0x7c);
    DRAIN(0x64, 0x68);
    DRAIN(0xb0, 0xb4);

    // ---- ten single effect handles ----
    RELS(0x60);
    RELS(0x90);
    RELS(0x94);
    RELS(0x8c);
    RELS(0x98);
    RELS(0x9c);
    RELS(0xa0);
    RELS(0xa4);
    RELS(0xa8);
    RELS(0xac);

    #undef RELS
    #undef DRAIN

    // ---- sound ----
    if (I(this_, 0x10) != 0)
        FUN_00e826e0(I(this_, 0x10));

    // ---- creature (+0x24), released through its own interface ----
    if (I(this_, 0x24) != 0) {
        void* c = (void*)I(this_, 0x24);
        void* iface = *(void**)((char*)c + 0x190);
        ((void(__thiscall*)(void*))VT(iface)[0x3c / 4])(c);
    }

    // ---- attachment +0x28 ----
    if (I(this_, 0x28) != 0) {
        void* a = (void*)I(this_, 0x28);
        ((PFN_i)VT(a)[0x16c / 4])(a, 0);
        a = (void*)I(this_, 0x28);
        if (a != 0) {
            I(this_, 0x28) = 0;
            if (I(a, 0x40) > 1) {
                I(a, 0x40) = I(a, 0x40) - 1;
            } else {
                ((PFN_sb)VT(a)[0x170 / 4])(a, (u32)I(a, 4) >> 31);
            }
        }
    }

    // ---- per-attachment slots at +0x2c + i*4 ----
    {
        char ref[4];
        FUN_00743b50(ref);
        char* att = (char*)FUN_00e4cc40(I(this_, 0x14), ref);
        int n = I(att, 0x18);
        if (n > 0) {
            char* base = *(char**)(att + 0x14);
            char* slot = this_ + 0x2c;
            for (int i = 0; i < n; ++i, slot += 4, base += 0x28) {
                int kind = I(base, 4);
                if (kind == 0) {
                    void* p = *(void**)slot;
                    if (p != 0) {
                        ((PFN_i)VT(p)[0x16c / 4])(p, 0);
                        if (I(p, 0x40) < 2)
                            ((PFN_sb)VT(p)[0x170 / 4])(p, (u32)I(p, 4) >> 31);
                        else
                            I(p, 0x40) = I(p, 0x40) - 1;
                    }
                } else if (kind == 1) {
                    void* p = *(void**)slot;
                    if (destroy == 0) {
                        int loc = (int)p;
                        FUN_00e65a00(&loc);
                    } else if (p != 0) {
                        ((PFN_i)VT(p)[0xc / 4])(p, 1);
                        ((PFN_v)VT(p)[4 / 4])(p);
                    }
                } else if (kind == 3) {
                    void* p = *(void**)slot;
                    if (p != 0) {
                        void* iface = *(void**)((char*)p + 0x190);
                        ((void(__thiscall*)(void*))VT(iface)[0x3c / 4])(p);
                    }
                }
            }
        }
        I(this_, 0x54) = 0;
        FUN_00e82130(ref);
    }
}

// ------------------------------------------------------------------ 0x00e66010
// Destroy a part's cPartGfx: resolve the cell (handle arrives in EAX), resolve its part-gfx
// (+0x248), drop it from the gfx list, clear it, free it, then recycle any overflow cell refs.
// @ 0x00e66010
void FUN_00e66010(int hCell, u8 destroy)
{
    char* cell = (char*)cells()->Get(hCell);
    int hParts = I(cell, 0x248);
    char* parts = (char*)((Pool*)(gspCellGfx + 0x168))->Get(hParts);
    if (I(cell, 0x35c) == I(gspCellGame, 0x4100))
        FUN_00e4f680(I(cell, 0x35c));
    I(cell, 0x248) = 0;
    FUN_00e65ad0(parts, destroy);
    ((Pool*)(gspCellGfx + 0x168))->Free(hParts);
    int n = I(cell, 0x250);
    if (n > 1) {
        int* q = (int*)(cell + 0x254);
        int cnt = n;
        do {
            FUN_00e4ec30(I(gspCellGame, 0x4108), *q);
            *q = -1;
            ++q;
            --cnt;
        } while (cnt != 0);
        I(cell, 0x250) = 0;
    } else {
        I(cell, 0x250) = 0;
    }
}

// ------------------------------------------------------------------ 0x00e660e0
// Refresh the "continuous death" effect attached to a cell part when the part is being
// destroyed (1 < refcount < 3): create the effect once at +0xac, then retarget it.  Otherwise
// just release the stored effect.
// @ 0x00e660e0
void FUN_00e660e0(int part, int owner)
{
    if (B(part, 0x112) != 0 &&
        FUN_00e57340((void*)part) > 1 &&
        FUN_00e57340((void*)part) < 3) {
        int* slot = (int*)(owner + 0xac);
        if (*slot == 0) {
            char* wp = (I(part, 0x35c) == I(gspCellGame, 0x40fc))
                     ? (gspCellGfx + 0x161c8)
                     : (gspCellGfx + 0x161bc);
            void* world = *(void**)wp;
            int old = *(volatile int*)(owner + 0xac);  // reload (cl would otherwise fold to 0)
            if (old != 0) {
                *slot = 0;
                ((PFN_v)VT(old)[4 / 4])((void*)old);
            }
            u32 id = FNV1_String8("cell_death_continuous", 0x811c9dc5, 1);
            CreateEffectSafe(world, id, 0, slot);
            void* e = (void*)*slot;
            ((PFN_i)VT(e)[8 / 4])(e, 0);
        }
        FUN_00e63480((void*)*slot, part + 0xc0, (void*)(part + 0x48));
    } else {
        if (I(owner, 0xac) != 0)
            FUN_00e65a00((int*)(owner + 0xac));
    }
}

// ------------------------------------------------------------------ 0x00e661c0
// Reset an effect-owner record (arrives in ECX): clear four intrusive pointer ranges and the
// object-vector at +0x28 (releasing each object through its interface).
// @ 0x00e661c0
void FUN_00e661c0(int* p)
{
    int beg = p[0], end = p[1];
    void* r = FUN_005f4e10((void*)end, (void*)end, (void*)beg);
    FUN_005f3680(r, (void*)p[1]);
    p[1] = p[1] - ((end - beg) >> 2) * 4;

    int beg2 = p[5], end2 = p[6];
    void* r2 = FUN_006f43e0((void*)end2, (void*)end2, (void*)beg2);
    FUN_0070f520(r2, (void*)p[6]);
    p[6] = p[6] - ((end2 - beg2) >> 2) * 4;

    int n = (p[0xb] - p[10]) >> 2;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            void* obj = (void*)*(int*)(p[10] + i * 4);
            void* iface = *(void**)(gspCellGfx + 0x58);
            ((PFN_i)VT(iface)[0x3c / 4])(iface, (int)obj);
        }
    }
    FUN_011e0744((void*)p[10], (void*)p[0xb], 0);
    p[0xb] = p[10];
}

// ------------------------------------------------------------------ 0x00e66280
// Resolve an effect event (a,b) through the effects manager and dispatch each sub-event:
// type 0x12 recurses, type 0 spawns a model/part and pushes it, type 2 forwards to 0xe65410,
// type 0x102 instantiates an object through the gfx factory and tracks it.
// @ 0x00e66280
struct EffEntry { int a, b, type; int pad; };

void FUN_00e66280(int a, int b)
{
    if ((a | b) == 0)
        return;

    void* mgr = FUN_0067ddd0();
    EffEntry buf[0x80];
    typedef int (__thiscall *PFN_mgr)(void*, int, int, void*, int);
    PFN_mgr fn = *(PFN_mgr*)((char*)VT(mgr) + 0x6c);
    int count = fn(mgr, a, b, buf, 0x80);
    if (count <= 0)
        return;

    EffEntry* e = buf;
    do {
        switch (e->type) {
        case 0x12:
            FUN_00e66280(e->a, e->b);
            break;
        case 0: {
            int x = e->a, y = e->b;
            void* obj = FUN_0067dd60();
            typedef void* (__thiscall *PFN_20)(void*, int, int, int);
            void* res = ((PFN_20)VT(obj)[0x20 / 4])(obj, x, y, 0);
            ((RefVecOwner*)gspCellGfx)->push(res);
            break;
        }
        case 2:
            FUN_00e65410(e->a, 0);
            break;
        case 0x102: {
            void* iface = *(void**)(gspCellGfx + 0x54);
            typedef void* (__thiscall *PFN_c)(void*, int, int, int);
            void* obj = ((PFN_c)VT(iface)[0xc / 4])(iface, e->a, 0, 0);
            if (obj != 0) {
                I(obj, 0x40) = I(obj, 0x40) + 1;
                ((cCellGfxStub*)gspCellGfx)->pushObj(obj);
                int rc = I(obj, 0x40);
                if (rc > 1) {
                    I(obj, 0x40) = rc - 1;
                } else {
                    ((PFN_sb)VT(obj)[0x170 / 4])(obj, ((u32)I(obj, 4) >> 31) & 1);
                }
            }
            break;
        }
        default:
            break;
        }
        ++e;
        --count;
    } while (count != 0);
}

// ------------------------------------------------------------------ 0x00e663b0
// Walk the effect descriptor for (map,key): mark the key as visited, then for each sub-entry
// (kind 0 spawns an object through the gfx factory, kind 1 recurses into 0xe66280, kind 3
// spawns via 0xe64980), recurse into sat/sub nodes, and finally grant three collectables.
// @ 0x00e663b0
void FUN_00e663b0(int map, int key)
{
    if (key == 0)
        return;

    void* out;
    char* m = (char*)map;
    ((RbTree*)m)->find(&out, (const unsigned*)&key);
    if (*(int*)out != (map + 4))
        return;

    int* val = (int*)((RbTree*)m)->operatorIndex(&key);
    *val = 1;

    char ref1[4];
    FUN_00743b50(ref1);
    char* a = (char*)FUN_00e4cc40(key, ref1);
    char ref2[4];
    FUN_00743b50(ref2);
    char* b = (char*)FUN_00e4cc40(*a, ref2);

    int n = I(b, 0x18);
    for (int i = 0; i < n; ++i) {
        char* desc = *(char**)(b + 0x14) + i * 0x28;
        int kind = I(desc, 4);
        if (kind == 0) {
            void* iface = *(void**)(gspCellGfx + 0x54);
            typedef void* (__thiscall *PFN_c)(void*, int, int, int);
            void* obj = ((PFN_c)VT(iface)[0xc / 4])(iface, I(desc, 0x10), 0, 0);
            if (obj != 0) {
                I(obj, 0x40) = I(obj, 0x40) + 1;
                ((cCellGfxStub*)gspCellGfx)->pushObj(obj);
                int rc = I(obj, 0x40);
                if (rc < 2)
                    ((PFN_sb)VT(obj)[0x170 / 4])(obj, (u32)I(obj, 4) >> 31);
                else
                    I(obj, 0x40) = rc - 1;
            }
        } else if (kind == 1) {
            FUN_00e66280(I(desc, 0x10), 0);
        } else if (kind == 3) {
            FUN_00e64980(I(desc, 0x10));
        }
    }

    for (int i = 0; i < 5; ++i)
        FUN_00e66280(I(b, i * 4), 0);

    FUN_00e663b0(map, val[0x37]);
    FUN_00e663b0(map, val[0x34]);
    FUN_00e663b0(map, val[0x33]);
    if (val[0x92] == 0x1008)
        FUN_00e663b0(map, val[0xaa]);
    if (val[0x38] == 0x1008)
        FUN_00e663b0(map, val[0x50]);
    if (val[0x65] == 0x1008)
        FUN_00e663b0(map, val[0x7d]);

    FUN_00e4fc20(map, val[0x35]);
    FUN_00e4fc20(map, val[0x32]);
    FUN_00e4fc20(map, val[0x36]);

    FUN_00e82130(ref1);
    FUN_00e82130(ref2);
}

// ------------------------------------------------------------------ 0x00e665c0
// Walk the layer-catalog entry list for `id` and dispatch each descriptor by its selector:
// 0/1 recurse into 0xe663b0 with the descriptor's key; 2 recurses into a group of layer
// entries chosen by a sub-index; 3 recurses into this function for a nested id list.
// @ 0x00e665c0
void FUN_00e665c0(int map, int id)
{
    char ref[4];
    FUN_00743b50(ref);
    char* list = (char*)FUN_00e4cc40(id, ref);
    int n = I(list, 8);
    if (n > 0) {
        char* base = *(char**)(list + 0xc);
        for (int i = 0; i < n; ++i, base += 0x4c) {
            int sel = I(base, 0x28);
            switch (sel) {
            case 0:
                FUN_00e663b0(map, I(base, 0x18));
                break;
            case 1:
                FUN_00e663b0(map, I(base, 0x1c));
                break;
            case 3:
                FUN_00e665c0(map, I(base, 0x20));
                break;
            case 2: {
                int sub = I(base, 0x24);
                if (sub == 0) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0(10));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0xb));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0xc));
                } else if (sub == 1) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0xd));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0xe));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0xf));
                } else if (sub == 2) {
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0x10));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0x11));
                    FUN_00e663b0(map, (int)FUN_00e4cce0(0x12));
                }
                break;
            }
            default:
                break;
            }
        }
    }
    FUN_00e82130(ref);
}

// ------------------------------------------------------------------ 0x00e666f0
// Build the whole-cell effect set: seed the local map from the layer-catalog info, walk the
// five layer lists, then register the fixed collectable/effect layer entries.
// @ 0x00e666f0
void FUN_00e666f0(void)
{
    // local eastl map/tree (anchor at +0, root at +4)
    struct LocalMap {
        void* anchor;   // +0
        void* root;     // +4
        void* node;     // +8
        int   pad0c;
        char  flag;     // +0x10
        char  pad11[0x1c - 0x11];
    } lm;
    lm.anchor = &lm.anchor;
    lm.node = 0;
    lm.pad0c = 0;
    lm.flag = 0;
    lm.root = 0;

    char ref[4];
    FUN_00743b50(ref);
    char* info = (char*)FUN_00e4ce40(ref);
    FUN_00e663b0((int)&lm.anchor, I(info, 0x34));

    char* cur = info + 4;
    for (int k = 5; k != 0; --k, cur += 4) {
        char ref2[4];
        FUN_00743b50(ref2);
        char* lst = (char*)FUN_00e4cc40(I(cur, 0), ref2);
        int n = I(lst, 0);
        if (n > 0) {
            char* base = *(char**)(lst + 4);
            for (int i = 0; i < n; ++i, base += 0xc)
                FUN_00e665c0((int)&lm.anchor, I(base, 0));
        }
        FUN_00e82130(ref2);
    }

    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0(1));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0(2));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0(4));
    FUN_00e663b0((int)&lm.anchor, (int)FUN_00e4cce0(8));
    FUN_00e4fc20((int)&lm.anchor, (int)FUN_00e4cce0(7));

    FUN_00e82130(ref);

    // drain the sub-tree
    void* node = lm.root;
    while (node != 0) {
        FUN_009a9600(&lm.anchor, *(void**)node);
        void* next = *(void**)((char*)node + 4);
        FUN_00f47380(node);
        node = next;
    }
}

// ------------------------------------------------------------------ 0x00e66840
// Spawn a world effect (world chosen by the owner cell's list) at the cell's transform:
// build the effect descriptor (identity rotation, world-centre position), create it, append it
// to the cell-gfx object vector, retarget it to the cell transform and return it.
// @ 0x00e66840
struct EffDesc { u16 a, b; Vec3 pos; float scale; float m[9]; };

int* FUN_00e66840(int cell, u32 id)
{
    char* wp = (I(cell, 0x35c) == I(gspCellGame, 0x40fc))
             ? (gspCellGfx + 0x161c8)
             : (gspCellGfx + 0x161bc);
    void* world = *(void**)wp;

    EffDesc d;
    FUN_00e619a0(&d);
    XForm xf;
    xf.assign((void*)(cell + 0x48));

    d.pos = gCellWorldCenter;
    d.scale = g_one_1485720;
    memcpy(&d.m, g_16b3dac, 36);
    d.a = 0;
    d.b = 0;

    int* effect;                 // original reads this uninitialised local before the create
    int* old = effect;
    if (old != 0) {
        effect = 0;
        ((PFN_v)VT(old)[4 / 4])(old);
    }
    CreateEffectSafe(world, id, 0, &effect);

    // append to the object vector at gspCellGfx + 0x161dc (0x74-byte elements)
    char* g = gspCellGfx;
    char* pos = *(char**)(g + 0x161e0);
    if (pos < *(char**)(g + 0x161e4)) {
        *(char**)(g + 0x161e0) = pos + 0x74;
        if (pos != 0)
            ((Obj74*)pos)->ctor(&d);
    } else {
        ((ObjVec74*)(g + 0x161dc))->insertGrow(pos, &d);
    }

    ((PFN_vp)VT(effect)[0x18 / 4])(effect, (void*)(cell + 0x48));
    ((PFN_i)VT(effect)[8 / 4])(effect, 0);
    int* ret = effect;
    if (effect != 0)
        ((PFN_v)VT(effect)[4 / 4])(effect);
    return ret;
}
