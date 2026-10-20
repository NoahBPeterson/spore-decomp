// Slice s00a2af30 - EA::Audio factory / submix / system resource parsing helpers.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stdlib.h>
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define EASTL_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* __cdecl eaNew(size_t size, const char* name, int flags, unsigned dbgFlags,
                    const char* file, int line);            // 0x00f473a0  EAAllocate
void  __cdecl operator_delete(void* p);                     // 0x00f47380

// ---------------------------------------------------------------------------
// 20-byte element (4 words + intrusive-refcounted pointer)
// ---------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();      // slot 0
    virtual void Release();     // slot 1
};

inline void* operator new(unsigned, void* p) { return p; }
inline void  operator delete(void*, void*) {}

struct ARef {
    IRef* p;
    ARef() : p(0) {}
    ARef(const ARef& o) : p(o.p) { if (p) p->AddRef(); }
    ARef& operator=(const ARef& o);
};

struct AR {
    u32  a, b, c, d;
    ARef r;
    AR() {}
    AR(const AR& o) : a(o.a), b(o.b), c(o.c), d(o.d), r(o.r) {}
    AR& operator=(const AR& o);
};

// Helpers defined in neighbouring slices (shared TU).
AR* __cdecl ARUninitCopy(AR* first, AR* last, AR* dst);     // 0x00a225d0
AR* __cdecl ARCopyBackward(AR* first, AR* last, AR* dst);   // 0x00a226c0
AR* __cdecl ARCopy(AR* first, AR* last, AR* dst);           // 0x00a22730
AR* __cdecl CopyElems20(AR** out, AR* first, AR* last, AR* dst, AR* end);  // 0x00a24750
                                                             // 0x00a27e00 (thiscall below)
AR* __cdecl ARDestroyRange(AR* first, AR* last, AR* out);   // 0x00a22680

// ---------------------------------------------------------------------------
// eastl::vector<AR, fixed_vector_allocator>
// ---------------------------------------------------------------------------
struct ARVector {
    AR* mpBegin;        // +0
    AR* mpEnd;          // +4
    AR* mpCap;          // +8
    u32 pad_c;
    AR* mpFixed;        // +0x10
    void DoInsertValue(AR* pos, const AR* value);   // 0xa2af30
    void assign(const AR* first, const AR* last, const AR* last2);  // 0xa2b2e0
    void Destroy(AR* first, AR* end);               // 0xa24500 (declared only)
    AR*  DoAllocate(u32 n, const AR* first, const AR* last);   // 0xa27e00
};

// @ 0x00a2af30
void ARVector::DoInsertValue(AR* pos, const AR* value)
{
    if (mpEnd != mpCap) {
        const AR* pv = value;
        if (pv >= pos && pv < mpEnd) ++pv;
        ::new (mpEnd) AR(*(mpEnd - 1));
        ARCopyBackward(pos, mpEnd - 1, mpEnd);
        *pos = *pv;
        ++mpEnd;
    } else {
        size_t nPrev = mpEnd - mpBegin;
        size_t nNew = nPrev ? nPrev * 2 : 1;
        AR* pNew = nNew ? (AR*)eaNew(nNew * sizeof(AR), "EASTL", 0, 0, EASTL_FILE, 0xd1) : 0;
        AR* pNewEnd = ARUninitCopy(mpBegin, pos, pNew);
        ARDestroyRange(mpBegin, pos, pNew);
        ::new (pNewEnd) AR(*value);
        pNewEnd = ARUninitCopy(pos, mpEnd, pNewEnd + 1);
        ARDestroyRange(pos, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mpFixed) operator_delete(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNew;
        mpCap = pNew + nNew;
    }
}

// @ 0x00a2b2e0
void ARVector::assign(const AR* first, const AR* last, const AR* last2)
{
    (void)last2;
    size_t n = (size_t)(last - first);
    if (n > (size_t)(mpCap - mpBegin)) {
        AR* pNew = DoAllocate((u32)n, (AR*)first, (AR*)last);
        Destroy(mpBegin, mpEnd);
        if (mpBegin && mpBegin != mpFixed) operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNew + n;
        mpCap = pNew + n;
        return;
    }
    size_t size = (size_t)(mpEnd - mpBegin);
    if (n <= size) {
        AR* pNewEnd = ARCopy((AR*)first, (AR*)last, mpBegin);
        Destroy(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
        return;
    }
    AR* mid = (AR*)first + size;
    ARCopy((AR*)first, mid, mpBegin);
    AR* out;
    CopyElems20(&out, mid, (AR*)last, mpEnd, (AR*)last);
    mpEnd = out;
}

// ===========================================================================
//  Remaining slice functions (EA::Audio resource parsing / submix / system).
//  Reconstructed behaviourally from the retail disassembly; class layouts use
//  raw offsets because the retail build differs from the 2008 dev PDB.
// ===========================================================================
#include <stdio.h>

#define VFN(p, off) ((*(void***)(p))[(off) / 4])
#define BSWAP(x) ((u32)((((u32)(x) >> 24) | (((u32)(x) >> 8) & 0xff00) | \
                         (((u32)(x) << 8) & 0xff0000) | ((u32)(x) << 24))))

extern void* g_pSystem;                                       // 0x0166d9f4

unsigned int __cdecl ReadLine(void* s, char* b, int n);       // 0x0093a8b0
bool __cdecl TokLine(char* a, char* b, int d, char** x, char** y, char** z); // 0x0093d110
u32  __cdecl FNV1_String8(const char* s, u32 seed, int len);  // 0x00932e80
float __cdecl ParseFloat8(const char* s);                     // 0x00838740
void* __cdecl ConvertToString8Impl(void* out, const void* w, int n); // 0x0093c440
void* __cdecl cString8Assign(void* d, const void* s);         // 0x00579c60
void  __cdecl eastlStringDtor(void* s);                       // 0x00530670
void* __cdecl ObjectError();                                  // 0x008de1a0
void  __cdecl RelLocal(void* p);                              // 0x007a9610
void  __cdecl fnA34d70(void* a, void* b);                     // 0x00a34d70
void  __fastcall Disconnect(void* p);                         // 0x00a21590 (arg in ecx)
struct EraseVecT { void erase(void* first, void* last); };    // 0x009e0480 (vector::erase)

// Small thiscall helpers, declared as members so `this` lands in ecx.
struct Vec12 { void pushEmpty(); };                           // 0x00a2ab40
struct Vec18 { void pushEmpty(); };                           // 0x00a2ab80
struct ZoneVec { void push_back(const void* z); };            // 0x00a2abe0
struct SimpleVec { void DoInsertValue(void** pos, void** value); }; // 0x00a80dd0
struct PHTable { void FreeBuckets(void** buckets, u32 n); };  // 0x00a24480
struct SubTable { void DoFreeNodes(void* a, void* b); };      // 0x00a1b6c0
struct VoiceContainer {
    bool ConstructVoice(void* tmpl);                          // 0x00a12f90
    bool Create(int flag);                                    // 0x00a342c0
    void MaskPluginBindings(const void* p, int n);            // 0x00a340b0
    void CommitBoundProperties();                             // 0x00a33dc0
    void Destroy();                                           // 0x00a343e0
};

// ---------------------------------------------------------------------------
// @ 0x00a2b3e0  EA::Audio::FactoryVoiceTemplate::ReadResource
// ---------------------------------------------------------------------------
struct OutRes {
    u32 pad0, pad1;          // +0/+4
    u32 h0, h1, h2;          // +8/+0xc/+0x10
    Vec12  vecA;             // +0x14  (12-byte elements)
    u32    pad20[0x194 / 4 - 7];
    Vec18  vecB;             // +0x194 (24-byte elements)
};

bool __stdcall FactoryVoiceTemplate_ReadResource(void* obj, OutRes* out, int, int);

// @ 0x00a2b3e0
bool __stdcall FactoryVoiceTemplate_ReadResource(void* obj, OutRes* out, int, int)
{
    if (!obj || !out) return false;
    int stream = ((int(__thiscall*)(void*))VFN(obj, 0x18))(obj);
    if (!stream) return false;
    void* sys = g_pSystem;
    if (!sys) return false;

    u32* hdr = (u32*)((void*(__thiscall*)(void*))VFN(obj, 0x10))(obj);
    out->h0 = hdr[0];
    out->h1 = hdr[1];
    out->h2 = hdr[2];

    char buf[1024];
    if (!ReadLine((void*)stream, buf, 0x400)) return false;
    if (atol(buf) != 1) return false;
    int len = (int)ReadLine((void*)stream, buf, 0x400);
    if (!len) return false;

    char *tb = 0, *te = 0, *cur = buf;
    char* end = buf + len;
    if (TokLine(buf, end, ' ', &tb, &te, &cur)) {
        do {
            ((Vec12*)((char*)out + 0x14))->pushEmpty();
            u8* rec = *(u8**)((char*)out + 0x18) - 0xc;
            int n = (int)(te - tb);
            char tmp[1024];
            strncpy(tmp, tb, n);
            tmp[n] = 0;
            *(u32*)(rec + 4) = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
            u32 k;
            memcpy(&k, tb, 4);
            k = BSWAP(k);
            *(u32*)(rec + 0) = k;
            *(u32*)(rec + 8) = 0;
            if (k == 0x53656e30u && (int)(te - tb) > 6) {
                int n2 = (int)(te - tb) - 6;
                strncpy(tmp, tb + 5, n2);
                tmp[n2] = 0;
                *(u32*)(rec + 8) = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
            }
        } while (TokLine(cur, end, ' ', &tb, &te, &cur));
    }

    len = (int)ReadLine((void*)stream, buf, 0x400);
    while (len > 0) {
        char* e2 = buf + len;
        if (!TokLine(buf, e2, '=', &tb, &te, &cur)) return true;
        u32 hash;
        {
            u8 c = (u8)*te; *te = 0;
            hash = FNV1_String8(tb, 0x811c9dc5u, 1);
            *te = (char)c;
        }
        cur += 1;
        if (!TokLine(cur, e2, ':', &tb, &te, &cur)) return true;
        char tmp[1024];
        int n = (int)(te - tb);
        strncpy(tmp, tb, n);
        tmp[n] = 0;
        u32 id = (u32)((int(__thiscall*)(void*, char*))VFN(sys, 0xf4))(sys, tmp);
        u32 key;
        memcpy(&key, tmp, 4);
        key = BSWAP(key);
        cur += 1;
        if (!TokLine(cur, e2, ',', &tb, &te, &cur)) return true;
        u32 num;
        {
            u8 c = (u8)*te; *te = 0;
            num = (u32)atol(tb);
            *te = (char)c;
        }
        ((Vec18*)((char*)out + 0x194))->pushEmpty();
        u8* rec = *(u8**)((char*)out + 0x198) - 0x18;
        *(u32*)(rec + 0x00) = hash;
        *(u32*)(rec + 0x04) = num;
        *(u32*)(rec + 0x08) = key;
        *(u32*)(rec + 0x0c) = id;
        cur += 1;
        if (TokLine(cur, e2, ',', &tb, &te, &cur)) {
            u8 c = (u8)*te; *te = 0;
            *(float*)(rec + 0x10) = ParseFloat8(tb);
            *(u32*)(rec + 0x14) |= 1;
            *te = (char)c;
        }
        len = (int)ReadLine((void*)stream, buf, 0x400);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a2b7d0  EA::Audio::Submix::Init
// @ 0x00a2bb30  EA::Audio::Submix::Shutdown
// ---------------------------------------------------------------------------
struct Submix {
    bool Init(void* param);
    bool Shutdown();
};

// @ 0x00a2b7d0
bool Submix::Init(void* param)
{
    char* self = (char*)this;
    if (!g_pSystem) return false;
    char* esi = (char*)param + 0x14;
    if (!((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x544e850b)) return false;
    if (!((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x2f8b3bf4)) return false;

    void* v = ((void*(__thiscall*)(void*))VFN(g_pSystem, 0xbc))(g_pSystem);
    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0xed4c265f))
        ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x28))(esi, 0xed4c265f, &v);
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x28))(esi, 0xb2550953, self + 0x15f8);
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x24))(esi, 0x6b16ae3d, self + 0x15fc);

    void* ws = ((void*(__thiscall*)(void*, int))VFN(esi, 0x3c))(esi, 0x2f8b3bf4);
    if (ws) {
        u32 tmp[4];
        ConvertToString8Impl(tmp, ws, -1);
        cString8Assign(self + 0x988, tmp);
        eastlStringDtor(tmp);
        *(u32*)(self + 0x970) =
            ((int(__thiscall*)(void*, void*))VFN(g_pSystem, 0xf4))(g_pSystem, *(void**)(self + 0x988));
    }

    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x2fe09c83)) {
        void* sid = ((void*(__thiscall*)(void*, int))VFN(esi, 0x3c))(esi, 0x2fe09c83);
        if (sid) {
            u32 tmp[4];
            ConvertToString8Impl(tmp, sid, -1);
            cString8Assign(self + 0x978, tmp);
            eastlStringDtor(tmp);
            *(u32*)(self + 0x974) =
                ((int(__thiscall*)(void*, void*))VFN(g_pSystem, 0xf0))(g_pSystem, sid);
        }
    }

    u32 arr[3] = { 0, 0, 0 };
    ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x34))(esi, 0x544e850b, arr);
    arr[1] = 0x29e333b;
    arr[2] = 0x21407ee;

    void* q = 0;
    void* err = ObjectError();
    bool ok = ((bool(__thiscall*)(void*, void**, u32*, int, int, int, int))VFN(err, 0xc))
                  (err, &q, arr, 0, 0, 0, 0);
    if (q) {
        void* r = q;
        q = 0;
        ((void(__thiscall*)(void*))VFN(r, 4))(r);
    }
    if (!ok) return false;

    VoiceContainer* vc = (VoiceContainer*)(self + 0x10);
    if (!vc->ConstructVoice(v)) {
        RelLocal(&q);
        return false;
    }
    if (*(void**)(self + 0x18) == *(void**)(self + 0x1c)) {
        RelLocal(&q);
        return false;
    }
    {
        u32 name = *(u32*)(self + 0x988);
        char* slot = self + 0x1978;
        *(u32*)slot = name;
        *(void**)(*(void**)(self + 0x18)) = slot;
    }
    fnA34d70(vc, *(void**)(self + 0x974));
    if (((bool(__thiscall*)(void*, int))VFN(esi, 0x18))(esi, 0x8a69beee))
        ((void(__thiscall*)(void*, int, void*))VFN(esi, 0x2c))(esi, 0x8a69beee, self + 0x1608);
    vc->Create(*(u8*)(self + 0x1608));
    if (*(void**)(self + 0x10) == 0) {
        RelLocal(&q);
        return false;
    }

    void* plugins[2] = { 0, 0 };
    ((void(__thiscall*)(void*, int, void**))VFN(g_pSystem, 0x184))(g_pSystem, 0, plugins);
    vc->MaskPluginBindings(plugins[0], (int)plugins[1]);
    vc->CommitBoundProperties();
    ((void(__thiscall*)(void*, void*))VFN(g_pSystem, 0x70))(g_pSystem, self + 4);
    *(u8*)(self + 0x998) = 1;
    RelLocal(&q);
    return true;
}

// @ 0x00a2bb30
bool Submix::Shutdown()
{
    char* self = (char*)this;
    if (g_pSystem && *(u8*)(self + 0x998))
        ((void(__thiscall*)(void*, void*))VFN(g_pSystem, 0x74))(g_pSystem, self + 4);
    *(u8*)(self + 0x998) = 0;
    ((VoiceContainer*)(self + 0x10))->Destroy();
    ((EraseVecT*)(self + 0x18))->erase(*(void**)(self + 0x18), *(void**)(self + 0x1c));
    *(u32*)(self + 0x14) = 0;
    *(u32*)(self + 0x10) = 0;
    *(u32*)(self + 0x970) = 0;
    Disconnect(self);

    {
        int* buckets = *(int**)(self + 0x9a0);
        u32 n = *(u32*)(self + 0x9a4);
        int* p = buckets;
        int node = *p;
        if (node == 0) { do { ++p; node = *p; } while (node == 0); }
        int endNode = buckets[n];
        while (node != endNode) {
            void* obj = *(void**)(node + 4);
            if (((void*(__thiscall*)(void*))VFN(obj, 0x30))(obj) == self)
                ((void(__thiscall*)(void*))VFN(obj, 0x14))(obj);
            node = *(int*)(node + 8);
            while (node == 0) { ++p; node = *p; }
        }
    }

    ((PHTable*)(self + 0x99c))->FreeBuckets((void**)*(void**)(self + 0x9a0), *(u32*)(self + 0x9a4));
    *(u32*)(self + 0x99c + 0xc) = 0;
    ((SubTable*)(self + 0xdd4))->DoFreeNodes(*(void**)(self + 0xdd4 + 4), *(void**)(self + 0xdd4 + 8));
    *(u32*)(self + 0xde0) = 0;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a2bc40  EA::Audio::FactoryInstrumentBank::ReadResource
// ---------------------------------------------------------------------------
struct Zone {
    u8    pad[0x2c];
    float f[6];              // +0x2c
    u32   h[6];              // +0x44
    u32   extra[3];          // +0x5c
};
struct InstOut {
    u32 pad0, pad1;          // +0/+4
    u32 h0, h1, h2;          // +8/+0xc/+0x10
    int lastId;              // +0x14
    ZoneVec zones;           // +0x18
};

bool __stdcall FactoryInstrumentBank_ReadResource(void* obj, InstOut* out, int, int);

// @ 0x00a2bc40
bool __stdcall FactoryInstrumentBank_ReadResource(void* obj, InstOut* out, int, int)
{
    if (!obj || !out) return false;
    int stream = ((int(__thiscall*)(void*))VFN(obj, 0x18))(obj);
    if (!stream) return false;

    u32* hdr = (u32*)((void*(__thiscall*)(void*))VFN(obj, 0x10))(obj);
    out->h0 = hdr[0];
    out->h1 = hdr[1];
    out->h2 = hdr[2];

    char buf[1024];
    if (!ReadLine((void*)stream, buf, 0x400)) return false;
    if (atol(buf) != 1) return false;
    int len = (int)ReadLine((void*)stream, buf, 0x400);
    while (len > 0) {
        if (buf[0] != '#') {
            Zone z;
            sscanf(buf, "%f %f %f %f %f %f %x %x %x %x %x %x",
                   &z.f[0], &z.f[1], &z.f[2], &z.f[3], &z.f[4], &z.f[5],
                   &z.h[0], &z.h[1], &z.h[2], &z.h[3], &z.h[4], &z.h[5]);
            z.extra[0] = z.h[0];
            z.extra[1] = 0x1a527db;
            z.extra[2] = 0x21407ee;
            if (((bool(__thiscall*)(void*, Zone*))VFN(g_pSystem, 0x188))(g_pSystem, &z)) {
                int r = ((int(__thiscall*)(void*, u32))VFN(g_pSystem, 0x1a4))(g_pSystem, z.h[0]);
                if (out->lastId == -1 && r != -1)
                    out->lastId = r;
            }
            out->zones.push_back(&z);
        }
        len = (int)ReadLine((void*)stream, buf, 0x400);
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a2be10  EA::Audio::System::StopAllSounds
// @ 0x00a2bf30  intrusive list insert
// ---------------------------------------------------------------------------
struct System {
    void StopAllSounds(int param);
    void InsertSound(void* item);
};

// @ 0x00a2be10
struct VecP { void** begin; void** end; void** cap; };

void System::StopAllSounds(int param)
{
    char* self = (char*)this;
    VecP v;
    v.begin = 0;
    v.end   = 0;
    v.cap   = 0;

    void** anchor = (void**)(self + 0x157438);
    char* raw  = (char*)*anchor;         // first node (+0x10 into object)
    char* stop = (char*)anchor;          // sentinel node link address
    while (raw != stop) {
        char* obj = raw - 0x10;
        if (v.end < v.cap) {
            *v.end++ = obj;
        } else {
            ((SimpleVec*)&v)->DoInsertValue(v.end, (void**)&obj);
        }
        raw = *(char**)raw;              // link field == stored node pointer
    }

    void** it = v.end;
    while (it != v.begin) {
        void* obj = *--it;
        if (obj) {
            ((void(__thiscall*)(void*))VFN(obj, 0))(obj);
            ((void(__thiscall*)(void*, int, int))VFN(obj, 0x18))(obj, 3, param);
            ((void(__thiscall*)(void*))VFN(obj, 4))(obj);
        }
    }
    if (v.begin && ((u32*)v.begin)[-1]) operator_delete(v.begin);
}

// @ 0x00a2bf30
void System::InsertSound(void* item)
{
    if (!item) return;
    ((void(__thiscall*)(void*))VFN(item, 0))(item);

    void** node = *(void***)((char*)this + 0x157c68);
    char*  list = (char*)this + 0x157c60;
    if (node)
        *(void**)(list + 8) = *node;
    else
        node = (void**)eaNew(*(u32*)((char*)this + 0x157c78), "EASTL", 0, 0, EASTL_FILE, 0xd1);
    void** body = node + 2;
    if (body) *body = item;
    node[0] = list;
    node[1] = *(void**)(list + 4);
    *(void**)*(void**)(list + 4) = node;
    *(void**)(list + 4) = node;
}
