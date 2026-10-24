// Spore - SporeApp.exe (32-bit x86, MSVC 2008 SP1)
// slice s00a099e0 - EA resource / animation / feedback utilities.
//
// Every function below is emitted as a non-inline (out-of-line) definition so MSVC
// actually places it in the object file; most take their object pointer in ecx
// (__thiscall), so they are declared as members of the opaque struct SL71.
//
//   VA 00a099e0  eastl::vector<Vector3>::insert(pos,count,val)
//   VA 00a09cf0  rbtree node insert
//   VA 00a09e70  ctor for an animation-resource object
//   VA 00a09f90  dtor for an animation-resource object
//   VA 00a0a020  dtor for an animation-resource object
//   VA 00a0a0b0  queue-blend helper
//   VA 00a0a120  (free) resource-cheat execute
//   VA 00a0a360  pointer-vector insert
//   VA 00a0a520  vector-of-vectors append
//   VA 00a0a580  (free) destroy a range of 0x18-byte structs
//   VA 00a0a600  teardown job / reporter
//   VA 00a0a6d0  release a cAnimatingCreature
//   VA 00a0a930  advance animation feedback events
//   VA 00a0aa20  cancel a queued feedback job by key
//   VA 00a0aaa0  destructor for the editor resource subsystem
//   VA 00a0ab90  rbtree insert (extract element)
//   VA 00a0ac10  vector<Vector3> resize / erase
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define EASTL_TAG "EASTL"

// ---- callees / data, resolved into the original image by the tools ----------
extern "C" void* FUN_00f473a0(unsigned size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  FUN_00f47380(void* p);
extern "C" void* FUN_00a11310(void* first, void* last, void* dest);
extern "C" void* FUN_006e5760(void* dest, unsigned count, void* val);
extern "C" void  FUN_00898b80(void* a, void* b, void* c, void* d, void* e);
extern "C" void  FUN_00abced0(void* a, void* b, void* c);
extern "C" void  FUN_00a177f0(void* first, void* last, void* val);
extern "C" void  FUN_009216a0(void* node, void* where, void* header, int flag);
extern "C" void* FUN_00921580(void* node);
extern "C" void  FUN_00921880(void* node, void* header);
extern "C" void* FUN_00e5c780(void* tree, void* key);
extern "C" void  FUN_0068f950();
extern "C" void  FUN_00579a90();                       // eastl::basic_string<wchar_t>::RangeInitialize
extern "C" void* FUN_0067dcd0();                       // EA::ResourceMan::GetManager
extern "C" char  FUN_0093d470(void*, void*, void*);    // EA::Text::WildcardMatch
extern "C" int   FUN_00a088e0(void* p);
extern "C" void  FUN_009a0d60(void* p, int a, void* b);
extern "C" void  FUN_00a05830(int n, void* p);
extern "C" void  FUN_00a09560(void* out, void* a, void* b, void* c, void* d);
extern "C" void  FUN_009c67e0(void* a, void* b);
extern "C" void  FUN_009b3450();
extern "C" void  FUN_00a09420(void* a, void* b, void* c);
extern "C" void  FUN_009c26a0(void* p);
extern "C" void  FUN_00a05270(void* p);                // SP::cAnimatingCreature::Release
extern "C" void  FUN_009c4d10(void* p);
extern "C" int   FUN_009aa820(int p);
extern "C" int   FUN_009a37e0(int p);
extern "C" void  FUN_00a05730(void* out, void* p);
extern "C" int   FUN_009a3f50(int p, unsigned n);
extern "C" void  FUN_00a007d0(int a);
extern "C" void  FUN_00a01c70();
extern "C" void  FUN_009ac130(int p);
extern "C" int   FUN_0068f970();                       // SP::cJobManager::ContinueJob
extern "C" void  FUN_00692400(int a);
extern "C" int   FUN_00690120();                       // SP::cJob::GetStatus
extern "C" void  FUN_00a09890(int p);
extern "C" void  FUN_00a09850(int p);
extern "C" void  FUN_00a098d0(void* a, void* b, void* c, void* d);
extern "C" void  FUN_00a057f0(void* a, void* b);
extern "C" void  FUN_00ac97a0(void* a, void* b, void* c);
extern "C" void* FUN_009e0480(void* a, void* b);       // eastl vector<AnalysisInfo>::erase

extern uint32 g_166c084;                               // DAT_0166c084
extern uint32 g_164dc58;                               // DAT_0164dc58

static inline void* vfn(void* o, int off) { return *(void**)(*(char**)o + off); }

typedef void     (__thiscall *vt_v)(void*);
typedef int      (__thiscall *vt_i)(void*);
typedef unsigned (__thiscall *vt_u)(void*);
typedef int      (__thiscall *vt_i_i)(void*, int);
typedef void     (__thiscall *vt_v_i)(void*, int);
typedef void*    (__thiscall *vt_p_i)(void*, int);

struct SL71
{
    void     v099e0(void* pos, unsigned count, void* val);
    void**   v09cf0(void** out, void* where, unsigned* key, char flag);
    void*    v09e70(void* a2, void* a3);
    void     v09f90();
    void     v0a020();
    unsigned v0a0b0(void* a1, unsigned a2, unsigned a3);
    void     v0a360(void* a2, void* a3);
    void*    v0a520(void* a2);
    unsigned v0a600();
    void     v0a6d0(void* a2);
    void     v0a930();
    void     v0aa20(unsigned key);
    void     v0aaa0();
    void*    v0ab90(void* a2);
    void     v0ac10(unsigned n);
    void     FUN_00a05830(int n, void* p);   // 0x00a05830
};

// 00a099e0 - eastl::vector<rw::math::fpu::Vector3Template<float,0> >::insert(pos,count,val)
//            (element size 0xc)
// @ 0x00a099e0
void SL71::v099e0(void* pos, unsigned count, void* val)
{
    char* self = (char*)this;
    char* begin = *(char**)self;
    char* end   = *(char**)(self + 4);
    unsigned room = (unsigned)((*(char**)(self + 8) - end) / 0xc);
    if (room < count)
    {
        unsigned size = (unsigned)((end - begin) / 0xc);
        unsigned newCap = size * 2;
        if (size == 0)
            newCap = 1;
        unsigned need = size + count;
        if (need < newCap)
            need = newCap;
        char* buf;
        if (need == 0)
            buf = 0;
        else
            buf = (char*)FUN_00f473a0(need * 0xc, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1);
        char* p1 = (char*)FUN_00a11310(begin, pos, buf);
        FUN_006e5760(p1, count, val);
        char* p2 = (char*)FUN_00a11310(pos, end, p1 + count * 0xc);
        char* old = begin;
        if (old != 0 && old != *(char**)(self + 0x10))
            FUN_00f47380(old);
        *(char**)self = buf;
        *(char**)(self + 4) = p2;
        *(char**)(self + 8) = buf + need * 0xc;
    }
    else if (count != 0)
    {
        struct FillValue { unsigned x, y, z; };
        FillValue local;
        local.x = ((unsigned*)val)[0];
        local.y = ((unsigned*)val)[1];
        local.z = ((unsigned*)val)[2];
        unsigned avail = (unsigned)((end - (char*)pos) / 0xc);
        if (count < avail)
        {
            char* src = end - count * 0xc;
            FUN_00898b80(&val, src, end, end, pos);
            *(char**)(self + 4) = end + count * 0xc;
            FUN_00abced0(pos, src, end);
            FUN_00a177f0(pos, (char*)pos + count * 0xc, &local);
            return;
        }
        unsigned extra = count - avail;
        FUN_006e5760(end, extra, &local);
        *(char**)(self + 4) = end + extra * 0xc;
        FUN_00898b80(&pos, pos, end, *(char**)(self + 4), pos);
        *(char**)(self + 4) = *(char**)(self + 4) + avail * 0xc;
        FUN_00a177f0((char*)pos, end, &local);
    }
}

// 00a09cf0 - rbtree::DoInsertValue; the node key {dword,dword} is built at +0x10
// @ 0x00a09cf0
void** SL71::v09cf0(void** out, void* where, unsigned* key, char flag)
{
    char* self = (char*)this;
    int b;
    if (flag == 0 && where != (void*)(self + 4) &&
        *(unsigned*)((char*)where + 0x10) <= *key)
        b = 1;
    else
        b = 0;
    char* node = (char*)FUN_00f473a0(0x18, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1);
    char* n16 = node + 0x10;
    if (n16 != 0)
    {
        *(unsigned*)n16 = key[0];
        unsigned v = key[1];
        *(unsigned*)(n16 + 4) = v;
        if (v != 0)
            ((void (__fastcall *)(void*))FUN_0068f950)((void*)v);
    }
    FUN_009216a0(node, where, self + 4, b);
    *(int*)(self + 0x14) += 1;
    *out = node;
    return out;
}

// 00a09e70 - constructor of an animation-resource object
// @ 0x00a09e70
void* SL71::v09e70(void* a2, void* a3)
{
    char* self = (char*)this;
    *(void**)(self + 0)    = (void*)0x1448f68;
    *(void**)(self + 4)    = (void*)0x1448f54;
    *(void**)(self + 8)    = 0;
    *(void**)(self + 0xc)  = 0;
    *(void**)(self + 0x10) = 0;
    *(void**)(self + 0x14) = 0;
    ((void (__fastcall *)(void*))FUN_00579a90)(a3);   // RangeInitialize(a3), ecx = this+0x18
    *(void**)(self + 0x1c) = a2;
    if (a2 != 0)
        ((vt_v)*(void**)a2)(a2);
    *(unsigned*)(self + 0x20) = 1;
    *(void**)(self + 0x24) = 0;
    *(void**)(self + 0x28) = 0;
    *(void**)(self + 0x2c) = 0;
    *(uint8*)(self + 0x38) = 0;
    *(void**)(self + 0x3c) = 0;
    *(void**)(self + 0x40) = 0;
    *(void**)(self + 0x44) = 0;
    *(uint8*)(self + 0x48) = 1;
    *(void**)(self + 0x4c) = 0;
    char* p = self + 0x68;
    char* q = self + 0x90;
    for (int i = 0xfe; i >= 0; --i)
    {
        *(void**)(p + 4) = 0;
        *(void**)(p + 8) = 0;
        *(void**)(p + 0xc) = 0;
        *(void**)(p + 0x10) = 0;
        *(void**)(p + 0x14) = 0;
        *(void**)(p + 0x18) = 0;
        *(void**)(p + 0x1c) = 0;
        *(void**)(p + 0x20) = 0;
        *(unsigned*)(q - 8) = 0x3f800000;
        *(unsigned*)(q - 24) = 0x3f800000;
        *(unsigned*)p = 0x3f800000;
        *(void**)(q + 4) = 0;
        *(void**)q = 0;
        *(void**)(q - 4) = 0;
        p += 0x30;
        q += 0x30;
    }
    *(uint8*)(self + 0x303a) = 0;
    *(uint8*)(self + 0x3038) = 1;
    *(uint8*)(self + 0x3039) = 1;
    return self;
}

// 00a09f90 - destructor of the animation-resource object
// @ 0x00a09f90
void SL71::v09f90()
{
    char* self = (char*)this;
    void* p;
    p = *(void**)(self + 0x4c);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0x44);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0x24);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    p = *(void**)(self + 0x1c);
    if (p) ((vt_v)vfn(p, 4))(p);
    p = *(void**)(self + 0xc);
    if (p && (2 < (int)((*(char**)(self + 0x14) - (char*)p) & 0xfffffffeU)))
        FUN_00f47380(p);
    *(void**)(self + 4) = (void*)0x13ec458;
    *(void**)(self + 0) = (void*)0x13eb938;
}

// 00a0a020 - destructor of an animation-resource holder
// @ 0x00a0a020
void SL71::v0a020()
{
    char* self = (char*)this;
    FUN_009c67e0(*(void**)(self + 0x28), *(void**)(self + 0x2c));
    void* p = *(void**)(self + 0x28);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    p = *(void**)(self + 0x10);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    void* q = *(void**)(self + 8);
    if (q)
    {
        if ((int)*(unsigned*)((char*)q + 0x40) < 2)
            ((vt_v_i)vfn(q, 0x170))(q, *(unsigned*)((char*)q + 4) >> 0x1f);
        else
            *(int*)((char*)q + 0x40) -= 1;
    }
    void* r = *(void**)(self + 4);
    if (r)
        ((vt_v)vfn(r, 4))(r);
}

// 00a0a0b0 - insert one entry into the queue-blend structure (this+0x18)
// @ 0x00a0a0b0
unsigned SL71::v0a0b0(void* a1, unsigned a2, unsigned a3)
{
    if (a3 == 0)
        return 0;
    unsigned local_10 = (unsigned)(size_t)a1;
    unsigned local_c  = a2;
    unsigned local_8  = a3;
    ((void (__fastcall *)(void*))FUN_009b3450)((void*)(size_t)a3);
    FUN_00a09420(&a1, &local_10, (void*)(size_t)(a3 & 0xffffff00));
    FUN_009c26a0((void*)(size_t)a3);
    return a2 & 0xff;
}

// 00a0a120 - (free) anonymous-namespace cResourceCheat::Execute over all resources
// @ 0x00a0a120
unsigned f0a120()
{
    void* local_40 = (void*)0x13eb428;
    unsigned local_3c = 0xee17c6ad;
    unsigned local_20 = 0;
    void* mgr = FUN_0067dcd0();
    if (((vt_i)vfn(mgr, 0x38))(mgr) != 0)
    {
        // The full resource walk / WildcardMatch / job kick-off sequence is not
        // reconstructed (unreachable-block warnings in the original). best-effort.
    }
    if (local_20 && *(int*)(local_20 - 4) != 0)
        FUN_00f47380((void*)local_20);
    (void)local_40;
    (void)local_3c;
    return 0;
}

// 00a0a360 - insert one AutoRefCount element into the pointer vector
// @ 0x00a0a360
void SL71::v0a360(void* a2, void* a3)
{
    char* self = (char*)this;
    char* end = *(char**)(self + 4);
    if (end != *(char**)(self + 8))
    {
        if ((char*)a2 <= (char*)a3 && (char*)a3 < end)
            a3 = (char*)a3 + 1;
        if (end)
        {
            void* ref = *(void**)(end - 4);
            *(void**)end = ref;
            if (ref)
                ((vt_v)*(void**)ref)(ref);
        }
        FUN_00ac97a0(a2, *(char**)(self + 4) - 4, *(char**)(self + 4));
        a3 = *(void**)a3;
        void* old = *(void**)a2;
        if (a3 != old)
        {
            if (a3)
                ((vt_v)*(void**)a3)(a3);
            *(void**)a2 = a3;
            if (old)
                ((vt_v)vfn(old, 4))(old);
        }
        *(char**)(self + 4) += 4;
        return;
    }
    int n = (int)(end - *(char**)self) >> 2;
    if (n == 0)
        n = 1;
    else
        n *= 2;
    void* buf = n ? FUN_00f473a0(n * 4, EASTL_TAG, 0, 0, ALLOC_FILE, 0xd1) : 0;
    size_t bytes = (char*)a2 - *(char**)self;
    char* d = (char*)FUN_00a11310(*(void**)self, a2, buf);
    void* elem = *(void**)a3;
    if (d)
    {
        *(void**)d = elem;
        if (elem)
            ((vt_v)*(void**)elem)(elem);
    }
    char* d2 = (char*)FUN_00a11310(a2, *(void**)end, d + 4);
    char* oldp = *(char**)self;
    if (oldp != 0 && *(int*)(oldp - 4) != 0)
        FUN_00f47380(oldp);
    *(char**)(self + 4) = d2;
    *(char**)self = (char*)buf;
    *(char**)(self + 8) = (char*)buf + n * 4;
    (void)bytes;
}

// 00a0a520 - append a vector-of-vectors (element stride 0x1c)
// @ 0x00a0a520
void* SL71::v0a520(void* a2)
{
    char* c = (char*)a2;
    FUN_00a05830((int)((*(char**)(c + 4) - *(char**)c) / 0x1c), c + 0xc);
    FUN_00a09560(&a2, *(void**)c, *(void**)(c + 4), *(void**)this, c);
    *((void**)this + 1) = a2;
    return this;
}

// 00a0a580 - (free) destroy each 0x18-byte element in [a1,a2), then the outer array
// @ 0x00a0a580
int f0a580(unsigned* a1, unsigned* a2, int a3)
{
    if (a1 == a2)
        return a3;
    do
    {
        char* p = (char*)a1;
        char* e = *(char**)(p + 4);
        for (char* q = *(char**)p; q < e; q += 0x1c)
        {
            char* r = *(char**)(q + 0xc);
            if (2 < (int)((*(char**)(q + 0x14) - r) & 0xfffffffeU) && r != 0)
                FUN_00f47380(r);
        }
        char* base = *(char**)p;
        if (base != 0 && *(int*)(base - 4) != 0)
            FUN_00f47380(base);
        a1 += 6;
        a3 += 0x18;
    } while (a1 != a2);
    return a3;
}

// 00a0a600 - teardown of the job / reporter lists
// @ 0x00a0a600
unsigned SL71::v0a600()
{
    char* self = (char*)this;
    unsigned count = (unsigned)((*(char**)(self + 0x28) - *(char**)(self + 0x24)) >> 2);
    for (unsigned i = 0; i < count; ++i)
        ((vt_v_i)vfn(self, 0x3c))(self, *(int*)(*(char**)(self + 0x24) + i * 4));
    void* src = *(void**)(self + 0x28);
    void* dst = *(void**)(self + 0x24);
    FUN_00a11310(dst, src, 0);
    int diff = (int)((char*)src - (char*)dst) >> 2;
    *(int*)(self + 0x28) = *(int*)(self + 0x28) + diff * -4;
    void* r = *(void**)(self + 0x44);
    if (r)
    {
        *(void**)(self + 0x44) = 0;
        ((vt_v)vfn(r, 4))(r);
    }
    char* base = *(char**)(self + 0x1c);
    char* stop = *(char**)(base + 0x6c);
    char* it = *(char**)(base + 0x68);
    while (it != stop && *(int*)it != (int)(size_t)self)
        it += 4;
    if ((char*)it + 4 < stop)
        FUN_00898b80(it + 4, stop, it, 0, 0);
    *(char**)(base + 0x6c) = stop - 4;
    void* r2 = *(void**)(base + 0x6c);
    if (*(int*)r2 != 0)
        ((vt_v)vfn((void*)(size_t)*(int*)r2, 4))((void*)(size_t)*(int*)r2);
    void* r3 = *(void**)(self + 0x1c);
    if (r3)
    {
        *(void**)(self + 0x1c) = 0;
        ((vt_v)vfn(r3, 4))(r3);
    }
    return 1;
}

// 00a0a6d0 - release an animating creature and detach it from its owner
// @ 0x00a0a6d0
void SL71::v0a6d0(void* a2)
{
    char* self = (char*)this;
    char* c = (char*)a2;
    if (c == 0 || *(void**)c == 0)
        return;
    if (*(void**)(c + 0x15c))
    {
        *(void**)(c + 0x15c) = 0;
        FUN_00a05270(c);
    }
    int inst = *(int*)c;
    if (*(int*)(inst + 0x294))
    {
        *(int*)(inst + 0x294) = 0;
        FUN_009c26a0((void*)(size_t)inst);
    }
    int saved = *(int*)inst;
    if (saved)
        FUN_009b3450();
    void* v2 = *(void**)(c + 0x30);
    if (v2)
    {
        FUN_00a007d0(1);
        FUN_00a01c70();
        FUN_00f47380(v2);
        *(void**)(c + 0x30) = 0;
    }
    *(void**)(c + 4) = 0;
    int obj = *(int*)(inst + 0x2c0);
    void* keep = 0;
    if (obj)
    {
        void* inner = *(void**)(obj + 8);
        if (inner)
        {
            *(int*)((char*)inner + 0x40) += 1;
            keep = inner;
        }
    }
    if (obj)
    {
        ((SL71*)(size_t)obj)->v0a020();
        FUN_00f47380((void*)(size_t)obj);
    }
    *(int*)(inst + 0x2c0) = 0;
    if (keep)
    {
        unsigned* k = (unsigned*)keep;
        if ((int)k[0x10] < 2)
            ((vt_v_i)vfn(keep, 0x170))(keep, k[1] >> 0x1f);
        else
            k[0x10] -= 1;
    }
    FUN_009c4d10((void*)(size_t)inst);
    if (*(void**)c)
    {
        *(void**)c = 0;
        FUN_009c26a0((void*)(size_t)inst);
    }
    if (saved)
    {
        int iVar6 = FUN_009aa820(saved);
        int lc = FUN_009a37e0(saved);
        int slot = *(int*)(self + 0x1c);
        int local_4 = 0;
        lc = iVar6 + 1 + lc;
        FUN_00a05730(&local_4, (void*)((char*)(size_t)saved + 0x310));
        int b = local_4 != slot + 0x1c;
        if (b)
            lc += 1;
        if (*(int*)(saved + 0x348) == lc)
        {
            *(uint8*)(saved + 0x34c) = 1;
            if (!b)
            {
                FUN_009a3f50(saved, 0xffffffff);
                if (saved)
                    FUN_009c26a0((void*)(size_t)saved);
            }
        }
    }
    FUN_00a05270(c);
}

// 00a0a930 - advance the animation feedback event queue
// @ 0x00a0a930
void SL71::v0a930()
{
    char* self = (char*)this;
    ((vt_v)vfn(self, 0x38))((void*)self);
    if (g_166c084 != 0)
        FUN_009ac130(*(int*)(self + 0x10));
    void* sobj = *(void**)(self + 0x50);
    unsigned* node = (unsigned*)((vt_p_i)vfn(sobj, 0x28))(sobj, 0xce55aeb1);
    short s = *(short*)((char*)node + 0x12);
    unsigned* pv;
    if (s == 10 || s == 0x10)
    {
        if ((*((uint8*)node + 0x10) & 0x30) == 0)
            pv = (unsigned*)(-(unsigned)(s != 0) & (unsigned)(size_t)node);
        else
            pv = *(unsigned**)node;
    }
    else
        pv = &g_164dc58;
    unsigned total = *pv;
    unsigned done = 0;
    char* it = *(char**)(self + 0x20);
    if (it == self + 0x1c)
        return;
    do
    {
        if (total <= done)
            return;
        int inst = *(int*)(it + 0x18);
        if (inst != 0 && *(char*)(inst + 0x34c) != 0)
        {
            int n = FUN_009a3f50(inst, total - done);
            done += n;
            if (*(int*)(inst + 0x348) == 1)
            {
                *(int*)(self + 0x2c) -= 1;
                void* next = FUN_00921580(it);
                FUN_00921880(it, self + 0x1c);
                if (*(int*)(it + 0x18) != 0)
                    FUN_009c26a0((void*)(size_t)*(int*)(it + 0x18));
                FUN_00f47380(it);
                done += 1;
                it = (char*)next;
                continue;
            }
        }
        it = (char*)FUN_00921580(it);
    } while (it != self + 0x1c);
}

// 00a0aa20 - cancel a queued feedback job selected by key
// @ 0x00a0aa20
void SL71::v0aa20(unsigned key)
{
    char* self = (char*)this;
    unsigned k = key;
    void* node = FUN_00e5c780(self + 0x30, &k);
    char* n = (char*)node;
    if (n != self + 0x38)
    {
        if (*(int*)(n + 0x14) != 0)
        {
            int st = FUN_0068f970();
            if (1 < (unsigned)(st - 7))
                FUN_00692400(1);
        }
        *(int*)(self + 0x48) -= 1;
        FUN_00921580(n);
        FUN_00921880(n, self + 0x38);
        if (*(int*)(n + 0x14) != 0)
            FUN_00690120();
        FUN_00f47380(n);
    }
}

// 00a0ab90 - rbtree insert for one 0x18-byte element
// @ 0x00a0ab90
void* SL71::v0ab90(void* a2)
{
    char* self = (char*)this;
    unsigned* p = (unsigned*)a2;
    unsigned* q = p;
    FUN_00a057f0(&q, p);
    unsigned* r = q;
    if (r == (unsigned*)(self + 4) ||
        (p[1] <= r[5] && (p[1] < r[5] || *p < r[4])))
    {
        unsigned local_10 = p[0];
        unsigned local_c  = p[1];
        unsigned local_8  = 0;
        unsigned* masked = (unsigned*)((size_t)r & 0xffffff00);
        FUN_00a098d0(&masked, r, &local_10, masked);
        r = masked;
    }
    return (char*)r + 0x18;
}

// 00a0ac10 - resize the Vector3 vector (fill) / erase the tail
// @ 0x00a0ac10
void SL71::v0ac10(unsigned n)
{
    char* self = (char*)this;
    char* begin = *(char**)self;
    char* end   = *(char**)(self + 4);
    unsigned size = (unsigned)((end - begin) / 0xc);
    if (size < n)
    {
        struct { unsigned a; unsigned b; unsigned c; } v;
        v.c = 0x3f800000;
        v.a = 0;
        v.b = 0xbf800000;
        v099e0(end, n - size, &v);
        return;
    }
    FUN_009e0480(begin + n * 0xc, end);
}

// 00a0aaa0 - destructor of the editor resource subsystem
// @ 0x00a0aaa0
void SL71::v0aaa0()
{
    char* self = (char*)this;
    *(void**)(self + 0) = (void*)0x1448fe8;
    *(void**)(self + 4) = (void*)0x1448fd4;
    *(void**)(self + 8) = (void*)0x1448fc4;
    void* pu = *(void**)(self + 0x84);
    if (pu)
    {
        int* pc = (int*)((char*)pu + 4);
        int v = *pc;
        *pc = v - 1;
        if (v == 1)
        {
            *pc = 1;
            ((vt_v_i)*(void**)pu)(pu, 1);
        }
    }
    void* r = *(void**)(self + 0x50);
    if (r)
        ((vt_v)vfn(r, 4))(r);
    FUN_00a09890(*(int*)(self + 0x40));
    FUN_00a09850(*(int*)(self + 0x24));
    *(void**)(self + 8) = (void*)0x13ec458;
    *(void**)(self + 4) = (void*)0x1448f54;
    *(void**)(self + 0) = (void*)0x13eb938;
}
