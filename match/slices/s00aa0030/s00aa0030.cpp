// Slice s00aa0030: creature emitter component (GmeIComponent/GmeRefCount derived):
// constructor, destructor, intrusive-list/vector helpers, virtual binding and emit step.
// Reconstructed from the original disassembly.

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct GObj;

typedef void (__thiscall* VFn)(void*);
typedef void (__thiscall* VFnI)(void*, int);
typedef void* (__thiscall* VFnP)(void*, uint, uint);
typedef void (__thiscall* VFnVP)(void*, void*);

struct RefNode {
    RefNode* next;      // 0x00
    RefNode* prev;      // 0x04
};

// allocations / helpers living in the original binary
struct Vec250   { void destroy(); void erase(void* a, void* b); };  // 0x4b5440 / 0x533500
struct SpVec    { void destroy(); void clear(int a, int b); };       // 0xa8c440 / 0xa8d020
struct ListHead { void destroy(); };                                 // 0x620230
struct BoolVec  { void resize(int n); };                             // 0x4c0410
struct PoolAlloc{ int add(void* a, uint b); };                       // 0x926650
struct MatDst   { void assign(const void* src); };                   // 0x41cb40
struct EffVec   { void push(void* p); };                             // 0xa7f430
extern "C" void* __cdecl op_new(int a, int b, int size);   // 0x11e073e
extern "C" void __cdecl operator_delete(void* p);          // ??3@YAXPAX@Z
extern "C" void __cdecl spherical_dir(const void* v, float* out1, float* out2);  // FUN_00a78fd0
extern "C" void __cdecl ins_vec(int begin, int end, int count);            // 0x11e0744
extern "C" void __cdecl build_tables(void* mgr, void* src, void* vec, void* out,
                                     void* p1fc, void* p214);              // 0x00a7fc10
struct TextSvc { void* find(int a, int b, int c); };      // FUN_00a71410
struct TextRef { int* assign(void* p); };                 // FUN_00b5f950
struct MsgSelf { void notify(void* m); };                 // FUN_00a9ef80
struct Quat { void to_matrix(void* dst, void* q); };      // FUN_004a9b40
struct IntVec { void insert(void* pos, void* val); };     // FUN_004558a0

struct XformMsg {                                         // ctor 0x434040, 0x40 bytes
    ushort flags;        // 0x00
    ushort seq;          // 0x02
    float  pos[3];       // 0x04
    int    pad0[3];      // 0x10
    float  mtx[9];       // 0x1c
    XformMsg();
};

extern "C" uchar g_alloc_pool[0x40];      // 0x1678fc8
extern "C" void* g_free_list;             // 0x1678fd8

// constants used by the constructor
extern "C" const float  g_axis_x[3];      // 0x1678f44
extern "C" const float  g_axis_y[3];      // 0x1678f48
extern "C" const float  g_one;            // 0x1485720
extern "C" const float  g_vec_a[3];       // 0x1678ef0
extern "C" const float  g_vec_b[3];       // 0x1678f20
extern "C" const float  g_minf;           // 0x13f0620
extern "C" const float  g_maxf;           // 0x1418f90
extern "C" const uchar  g_ident_mat[0x30]; // 0x1679010
extern "C" const uchar  g_mat_const[0x30]; // 0x1678ef0 area
extern "C" const float  g_half;           // 0x1565420
extern "C" const double g_neg_one;        // 0x1454410

struct GObj {
    // 0x000 vtable ptr
    // 0x004 vtable ptr (second base)
    // 0x008..0x023 scalars
    RefNode     head;       // 0x024 (next/prev), count at 0x02c

    GObj* ctor(int a, int b);
    void  dtor();
    void  compact();
    void  node_destroy(void* e);
    void  clear_list();
    void* pool_alloc();
    void  set_target(int t);
    void  bind_cfg(void* mgr);
    void  on_msg(void* m);
};

inline char* op(GObj* o, int off) { return (char*)o + off; }

template<class T> inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
template<class T> inline T& at(int p, int off) { return *(T*)((char*)(long)p + off); }
inline char* op(int o, int off) { return (char*)(long)o + off; }

// ------------------------------------------------------------------ 00aa0030
// @ 0x00aa0030
GObj* GObj::ctor(int a, int b)
{
    at<int>(this, 4) = (int)0x13ef094;
    at<int>(this, 8) = 0;
    at<int>(this, 0xc) = a;
    at<int>(this, 0x10) = b;
    at<int>(this, 0) = (int)0x1458c3c;
    at<int>(this, 4) = (int)0x1458c38;
    at<int>(this, 0x14) = 0;
    at<int>(this, 0x18) = 0;
    at<int>(this, 0x1c) = 0;
    at<uchar>(this, 0x20) = 0;
    at<uchar>(this, 0x21) = 0;
    at<uchar>(this, 0x22) = 1;
    *(int*)op(this, 0x28) = (int)op(this, 0x24);
    *(int*)op(this, 0x24) = (int)op(this, 0x24);
    at<int>(this, 0x2c) = 0;
    at<ushort>(this, 0x30) = 0;
    at<ushort>(this, 0x32) = 0;
    at<float>(this, 0x34) = g_axis_x[0];
    at<float>(this, 0x38) = g_axis_y[0];
    at<float>(this, 0x3c) = g_axis_x[2];
    at<float>(this, 0x40) = g_one;
    ((MatDst*)op(this, 0x44))->assign(g_ident_mat);
    at<ushort>(this, 0x68) = 0;
    at<ushort>(this, 0x6a) = 0;
    at<float>(this, 0x6c) = g_axis_x[0];
    at<float>(this, 0x70) = g_axis_y[0];
    at<float>(this, 0x74) = g_axis_x[2];
    at<float>(this, 0x78) = g_one;
    ((MatDst*)op(this, 0x7c))->assign(g_ident_mat);
    at<double>(this, 0xa0) = 0.0;
    at<double>(this, 0xb0) = 0.0;
    at<uchar>(this, 0xa8) = 0;
    at<int>(this, 0xb8) = 0;
    at<double>(this, 0xc0) = g_neg_one;
    at<float>(this, 0xc8) = 0.0f;
    at<float>(this, 0xcc) = g_axis_x[0];
    at<float>(this, 0xd0) = g_axis_y[0];
    at<float>(this, 0xd4) = g_axis_x[2];
    at<uchar>(this, 0x108) = 0;
    at<float>(this, 0x10c) = 0.0f;
    at<float>(this, 0x110) = 0.0f;
    at<float>(this, 0x114) = g_axis_x[0];
    at<float>(this, 0x118) = g_axis_y[0];
    at<float>(this, 0x11c) = g_axis_x[2];
    at<float>(this, 0x120) = 0.0f;
    at<int>(this, 0x124) = 1;
    at<int>(this, 0x128) = 1;
    at<float>(this, 0x12c) = 0.0f;
    at<float>(this, 0x130) = g_axis_x[0];
    at<float>(this, 0x134) = g_axis_y[0];
    at<float>(this, 0x138) = g_axis_x[2];
    at<float>(this, 0x13c) = g_one;
    at<float>(this, 0x140) = g_one;
    at<float>(this, 0x144) = g_one;
    at<float>(this, 0x148) = g_one;
    at<float>(this, 0x14c) = g_one;
    at<float>(this, 0x150) = g_vec_a[0];
    at<float>(this, 0x154) = g_vec_a[1];
    at<float>(this, 0x158) = g_vec_a[2];
    at<float>(this, 0x15c) = g_maxf;
    at<float>(this, 0x160) = g_minf;
    at<float>(this, 0x164) = g_vec_b[0];
    at<float>(this, 0x168) = g_vec_b[1];
    at<float>(this, 0x16c) = g_vec_b[0];
    at<float>(this, 0x170) = g_vec_b[1];
    at<float>(this, 0x174) = g_vec_b[0];
    at<float>(this, 0x178) = g_vec_b[1];
    at<float>(this, 0x17c) = g_one;
    at<float>(this, 0x180) = g_one;
    at<float>(this, 0x184) = g_one;
    at<float>(this, 0x188) = g_vec_a[0];
    at<float>(this, 0x18c) = g_vec_a[1];
    at<int>(this, 0x194) = 0;
    at<int>(this, 0x198) = 0;
    at<int>(this, 0x19c) = 0;
    at<float>(this, 0x190) = g_vec_a[2];
    at<uchar>(this, 0x1a0) = 0;
    at<uchar>(this, 0x1a1) = 0;
    at<uchar>(this, 0x1a2) = 0;
    at<float>(this, 0x1a4) = g_half;
    at<float>(this, 0x1a8) = g_half;
    at<float>(this, 0x1ac) = g_half;
    at<float>(this, 0x1b0) = -g_half;
    at<float>(this, 0x1b4) = -g_half;
    at<float>(this, 0x1b8) = -g_half;
    at<int>(this, 0x1bc) = 0;
    at<int>(this, 0x1c0) = 0;
    at<int>(this, 0x1c4) = 0;
    at<uchar>(this, 0x1d0) = 0;
    at<int>(this, 0x1d4) = 0;
    at<int>(this, 0x1d8) = 0;
    at<int>(this, 0x1dc) = 0;
    at<int>(this, 0x1e8) = 0;
    at<int>(this, 0x1ec) = 0;
    at<int>(this, 0x1f0) = 0;
    at<int>(this, 0x1fc) = 0;
    at<int>(this, 0x200) = 0;
    at<int>(this, 0x204) = 0;
    at<int>(this, 0x208) = 0;
    at<uchar>(this, 0x214) = 0;
    at<int>(this, 0x218) = 0;
    at<int>(this, 0x21c) = 0;
    at<int>(this, 0x220) = 0;
    at<uchar>(this, 0x22c) = 0;
    at<int>(this, 0x230) = 0;
    at<int>(this, 0x234) = -1;
    at<int>(this, 0x238) = -1;
    at<int>(this, 0x23c) = -1;
    at<int>(this, 0x240) = -1;
    at<int>(this, 0x244) = -1;
    at<int>(this, 0x248) = 0;
    at<uchar>(this, 0x24c) = 0;
    at<int>(this, 0x250) = 0;
    at<int>(this, 0x254) = 0;
    at<int>(this, 0x258) = 0;
    return this;
}

// ------------------------------------------------------------------ 00aa04a0
// @ 0x00aa04a0
void GObj::dtor()
{
    at<int>(this, 0) = (int)0x1458c3c;
    at<int>(this, 4) = (int)0x1458c38;
    ((Vec250*)op(this, 0x250))->destroy();
    void* p;
    p = at<void*>(this, 0x248);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[0x38 / 4])(p);
    p = at<void*>(this, 0x230);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x218);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x200);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x1e8);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    p = at<void*>(this, 0x1d4);
    if (p != 0 && at<int>(p, -4) != 0)
        operator_delete(p);
    ((SpVec*)op(this, 0x1bc))->destroy();
    p = at<void*>(this, 0x19c);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x198);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    p = at<void*>(this, 0x194);
    if (p != 0)
        ((VFn)((void**)*(void**)p)[4 / 4])(p);
    ((ListHead*)op(this, 0x24))->destroy();
    at<int>(this, 0) = (int)0x13f21d4;
    at<int>(this, 4) = (int)0x13ef094;
}

// ------------------------------------------------------------------ 00aa0ba0
// Re-reads the configuration object at +0x0c: scale/bounds tables, the three
// spawner interfaces (indices +0x1e8/+0x1ec, +0x1f0/+0x1f4, +0x1f8/+0x1fc), the
// spherical direction flag and the per-spawner value tables.
// @ 0x00aa0ba0
void GObj::bind_cfg(void* mgr)
{
    int cfg = at<int>(this, 0xc);
    float* pf = (float*)((char*)cfg + 0x7c);
    float tiny = 1e-06f;

    if (!(at<float>(cfg, 0x7c) > 1e-06f))
        pf = &tiny;
    at<double>(this, 0xc0) = 1.0 / (double)*pf;
    at<int>(this, 0x1b0) = at<int>(cfg, 0x58);
    at<int>(this, 0x1b4) = at<int>(cfg, 0x5c);
    at<int>(this, 0x1b8) = at<int>(cfg, 0x60);
    at<int>(this, 0x1a4) = at<int>(cfg, 0x4c);
    at<int>(this, 0x1a8) = at<int>(cfg, 0x50);
    at<int>(this, 0x1ac) = at<int>(cfg, 0x54);
    cfg = at<int>(this, 0xc);
    uchar diff = (uchar)(at<float>(cfg, 0x268) != g_axis_x[0] ||
                         at<float>(cfg, 0x26c) != g_axis_y[0] ||
                         at<float>(cfg, 0x270) != g_axis_x[2]);
    at<uchar>(this, 0x108) = diff;
    if (diff)
        spherical_dir(op(cfg, 0x268), (float*)op(this, 0x10c), (float*)op(this, 0x110));

    for (int k = 0; k < 3; k++) {
        int offs[3] = { 0x1e8, 0x1f0, 0x1f8 };
        int dst[3] = { 0x194, 0x198, 0x19c };
        int cfgo = at<int>(this, 0xc);
        uint a = at<uint>(cfgo, offs[k]);
        uint b = at<uint>(cfgo, offs[k] + 4);
        if ((a & b) != 0xffffffffu) {
            void* np = ((void* (__thiscall*)(void*, uint, uint))
                        ((void**)*(void**)mgr)[0x8c / 4])(mgr, a, b);
            void* old = at<void*>(this, dst[k]);
            if (np != old) {
                if (np != 0)
                    ((VFn)((void**)*(void**)np)[0 / 4])(np);
                at<void*>(this, dst[k]) = np;
                if (old != 0)
                    ((VFn)((void**)*(void**)old)[4 / 4])(old);
            }
        }
    }

    cfg = at<int>(this, 0xc);
    at<int>(this, 0x15c) = at<int>(cfg, 0x1e0);
    at<int>(this, 0x160) = at<int>(cfg, 0x1e4);
    for (int k = 0; k < 3; k++) {
        int dst[3] = { 0x194, 0x198, 0x19c };
        void* p = at<void*>(this, dst[k]);
        if (p != 0) {
            ((VFn)((void**)*(void**)p)[8 / 4])(p);
            at<uchar>(this, 0x1a0 + k) =
                ((uchar (__thiscall*)(void*))((void**)*(void**)p)[0x1c / 4])(p);
        }
    }
    ((SpVec*)op(this, 0x1bc))->clear(at<int>(this, 0x1bc), at<int>(this, 0x1c0));

    int e0 = at<int>(this, 0x1d4);
    int b0 = at<int>(this, 0x1d8);
    ins_vec(e0, b0, 0);
    at<int>(this, 0x1d8) += (e0 - b0);

    at<int>(this, 0x1fc) = 0;

    int e1 = at<int>(this, 0x1e8);
    int b1 = at<int>(this, 0x1ec);
    ins_vec(e1, b1, 0);
    at<int>(this, 0x1ec) += (e1 - b1);

    cfg = at<int>(this, 0xc);
    at<uchar>(this, 0x214) = 0;
    if (at<int>(cfg, 0x1b0) != at<int>(cfg, 0x1b4)) {
        float n = 0.0f;
        at<int>(this, 0x1fc) = 0;
        build_tables(mgr, op(cfg, 0x1b0), op(this, 0x1bc), &n,
                     op(this, 0x1fc), op(this, 0x214));
        at<uchar>(this, 0x1d0) = 0;
        ((BoolVec*)op(this, 0x1d4))->resize(*(int*)&n);
    }
}

// @ 0x00aa0600
void GObj::compact()
{
    int* vec = (int*)op(this, 0x250);
    unsigned i = 0;
    unsigned j = 0;

    if (((vec[1] - vec[0]) >> 2) != 0) {
        do {
            void* e = ((void**)vec[0])[i];
            if (((uchar (__thiscall*)(void*))((void**)*(void**)e)[0x10 / 4])(e)) {
                if (i > j) {
                    void* a = ((void**)vec[0])[i];
                    void* b = ((void**)vec[0])[j];
                    if (a != b) {
                        if (a != 0)
                            ((VFn)((void**)*(void**)a)[0 / 4])(a);
                        ((void**)vec[0])[j] = a;
                        if (b != 0)
                            ((VFn)((void**)*(void**)b)[4 / 4])(b);
                    }
                }
                j++;
            }
            i++;
        } while (i < (unsigned)((vec[1] - vec[0]) >> 2));
    }
    ((Vec250*)vec)->erase((void*)((int*)vec[0] + j), (void*)vec[1]);
}

// ------------------------------------------------------------------ 00aa06b0
// Effect message handler: conditional re-dispatch, released text binding update
// (position/quaternion transform message), spawner index bookkeeping and the
// message's return to the free list.
// @ 0x00aa06b0
void GObj::on_msg(void* msg)
{
    int* m = (int*)msg;
    int* comp = (int*)at<int>(this, 0x248);

    if (comp != 0 && at<int>(comp, 0xc) != 0) {
        uint fl = *(uint*)(at<int>(this, 0xc) + 0xc);
        if ((fl >> 6 & 1) != 0 ||
            (uint)(fl >> 7 & 1) != (uint)(at<float>(m, 8) >= at<float>(m, 0xc))) {
            ((MsgSelf*)this)->notify(m);
            goto done;
        }
    }
    if (at<int>(m, 0x7c) != 0) {
        void* sp = (void*)at<int>(m, 0x7c);
        ((VFnI)((void**)*(void**)sp)[0xc / 4])(sp, at<int>(this, 0x128));
        if (*(int*)(at<int>(this, 0xc) + 0x12c) == 0) {
            if (at<int>(this, 0x128) == 0 &&
                ((uchar (__thiscall*)(void*))((void**)*(void**)sp)[0x10 / 4])(sp)) {
                void* tmp = (void*)((int*)sp - 1);
                if (tmp != 0)
                    ((VFn)((void**)*(void**)tmp)[0 / 4])(tmp);
                ((EffVec*)op(this, 0x250))->push(&tmp);
                if (tmp != 0)
                    ((VFn)((void**)*(void**)tmp)[4 / 4])(tmp);
            }
        } else {
            ((VFn)((void**)*(void**)sp)[4 / 4])(sp);
        }
        sp = (void*)at<int>(m, 0x7c);
        if (sp != 0) {
            at<int>(m, 0x7c) = 0;
            ((VFn)((void**)*(void**)sp)[0x38 / 4])(sp);
        }
    }

    int local = 0;
    int idx = *(int*)(at<int>(this, 0xc) + 0x130);
    if (idx >= 0 && at<int>(this, 0x128) == 0 && at<uchar>(this, 0x22) != 0) {
        void* txt = ((TextSvc*)at<void*>(this, 0x14))->find(idx, at<int>(this, 0x10),
                                                           at<int>(this, 0x1c));
        int* arc = ((TextRef*)&local)->assign(txt);
        if (arc[0] != 0) {
            XformMsg xf;
            xf.flags |= 4;
            xf.seq++;
            xf.pos[0] = at<float>(m, 0x10);
            xf.pos[1] = at<float>(m, 0x14);
            xf.pos[2] = at<float>(m, 0x18);
            if ((*(uint*)(at<int>(this, 0xc) + 0xc) >> 2 & 1) != 0) {
                float mt[9];
                ((Quat*)((char*)m + 0x80))->to_matrix(mt, (char*)m + 0x80);
                for (int k = 0; k < 9; k++)
                    xf.mtx[k] = mt[k];
                xf.flags |= 2;
                xf.seq++;
            }
            void* txtobj = (void*)arc[0];
            ((VFnVP)((void**)*(void**)txtobj)[0x14 / 4])(txtobj, op(this, 0x68));
            if ((*(uint*)(at<int>(this, 0xc) + 0xc) >> 5 & 1) == 0 || at<int>(m, 0x7c) == 0) {
                ((VFnVP)((void**)*(void**)txtobj)[0x18 / 4])(txtobj, &xf);
            } else {
                XformMsg xf2;
                void* blk = (void*)((int*)at<int>(m, 0x7c) - 1);
                ((VFnVP)((void**)*(void**)blk)[0x20 / 4])(blk, &xf2);
                ((VFnVP)((void**)*(void**)txtobj)[0x18 / 4])(txtobj, &xf2);
            }
            if (at<uchar>(this, 0x22c) != 0)
                ((void (__thiscall*)(void*, int, int))
                 ((void**)*(void**)txtobj)[0x4c / 4])(txtobj, 0, at<int>(this, 0x230));
            ((VFnI)((void**)*(void**)txtobj)[0x30 / 4])(txtobj, at<uchar>(this, 0x22) == 0);
            ((VFnI)((void**)*(void**)txtobj)[8 / 4])(txtobj, 0);
            ((EffVec*)op(this, 0x250))->push(&local);
        }
    }

    if (at<int>(this, 0x1fc) != 0) {
        int i = at<int>(m, 0x24);
        int* p = (int*)at<int>(this, 0x1bc);
        int base = at<int>(this, 0x1e8);
        while (p != (int*)at<int>(this, 0x1c0)) {
            if (p[4] != 0)
                ((VFnI)((void**)*(void**)p[0])[0x30 / 4])((void*)p[0],
                                                           p[5] + i * at<int>(this, 0x1fc) + base);
            p += 6;
        }
        int* dst = (int*)at<int>(this, 0x204);
        if (dst < (int*)at<int>(this, 0x208)) {
            at<int>(this, 0x204) = (int)(dst + 1);
            if (dst != 0)
                *dst = at<int>(m, 0x24);
        } else {
            ((IntVec*)op(this, 0x200))->insert(dst, (char*)m + 0x90);
        }
    }
    m[0] = *(int*)&g_free_list;
    g_free_list = m;
    if (local != 0)
        ((VFn)((void**)*(void**)local)[4 / 4])((void*)local);

done:
    if (at<int>(this, 0x248) != 0 && at<int>(this, 0x2c) == 0 &&
        at<uchar>(this, 0x21) != 0)
        ((VFnI)((void**)*(void**)at<int>(this, 0x248))[0xc / 4])((void*)at<int>(this, 0x248), 0);
}

// ------------------------------------------------------------------ 00aa09e0
// @ 0x00aa09e0
void* GObj::pool_alloc()
{
    void* p;
    uchar ok;

    p = g_free_list;
    while (p == 0) {
        ok = (uchar)((PoolAlloc*)g_alloc_pool)->add(0, 0);
        if (!ok)
            break;
        p = g_free_list;
    }
    if (p != 0)
        g_free_list = *(void**)p;
    void* obj = op_new((int)p, 0, 0xa0);
    if (at<int>(this, 0x1fc) != 0) {
        if (at<int>(this, 0x200) != at<int>(this, 0x204)) {
            at<int>(obj, 0x90) = *(int*)(at<int>(this, 0x204) - 4);
            at<int>(this, 0x204) -= 4;
            return obj;
        }
        at<int>(obj, 0x90) = (at<int>(this, 0x1ec) - at<int>(this, 0x1e8)) / at<int>(this, 0x1fc);
        ((BoolVec*)op(this, 0x1e8))->resize(
            (at<int>(this, 0x1ec) - at<int>(this, 0x1e8)) + at<int>(this, 0x1fc));
    }
    return obj;
}

// ------------------------------------------------------------------ 00aa0a90
// @ 0x00aa0a90
void GObj::clear_list()
{
    RefNode* head = (RefNode*)op(this, 0x24);
    RefNode* p = head->next;

    while (p != head) {
        RefNode* prev = p->prev;
        RefNode* next = p->next;
        prev->next = next;
        next->prev = prev;
        p->next = 0;
        p->prev = 0;
        node_destroy(p);
        at<int>(this, 0x2c)--;
        p = next;
    }
    RefNode* q = head->next;
    while (q != head) {
        RefNode* next = q->next;
        q->prev = 0;
        q->next = 0;
        q = next;
    }
    head->next = head;
    head->prev = head;
}

// ------------------------------------------------------------------ 00aa0b00
// @ 0x00aa0b00
void GObj::set_target(int t)
{
    if (at<uchar>(this, 0x20) != 0) {
        void* c = at<void*>(this, 0x248);
        if (c != 0 && at<int>(this, 0x2c) == 0)
            ((VFnI)((void**)*(void**)c)[0xc / 4])(c, t);
        uchar zero = (uchar)(t == 0);
        at<int>(this, 0x128) = t;
        at<uchar>(this, 0x21) = zero;
        if (!zero) {
            at<uchar>(this, 0x20) = zero;
            clear_list();
            unsigned i = 0;
            if (((at<int>(this, 0x254) - at<int>(this, 0x250)) >> 2) != 0) {
                do {
                    void* e = ((void**)at<int>(this, 0x250))[i];
                    if (((uchar (__thiscall*)(void*))((void**)*(void**)e)[0x10 / 4])(e)) {
                        void* e2 = ((void**)at<int>(this, 0x250))[i];
                        ((VFnI)((void**)*(void**)e2)[0xc / 4])(e2, t);
                    }
                    i++;
                } while (i < (unsigned)((at<int>(this, 0x254) - at<int>(this, 0x250)) >> 2));
            }
            ((Vec250*)op(this, 0x250))->erase((void*)at<int>(this, 0x250), (void*)at<int>(this, 0x254));
        }
    }
}
