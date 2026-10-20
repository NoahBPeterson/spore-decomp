// Slice s00a07ae0: SP::cSPCreatureAnimManager script bindings (the anim target
// property setters), the feedback-map queries, the anim-list / parts-caps stream
// writers and the anim / gait static-data loaders.
//
// Layouts are retail offsets read off the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;
typedef unsigned long long uint64;

// =========================================================================== base vtables
// Layout-only bases: we only ever cast to these, never instantiate, so the
// declared-but-undefined virtuals cost nothing at link time.

struct V12 {                            // virtual slots 0x00 .. 0x2c
    virtual void a0();  virtual void a1();  virtual void a2();  virtual void a3();
    virtual void a4();  virtual void a5();  virtual void a6();  virtual void a7();
    virtual void a8();  virtual void a9();  virtual void a10(); virtual void a11();
};
struct V13 {                            // virtual slots 0x00 .. 0x30
    virtual void c0();  virtual void c1();  virtual void c2();  virtual void c3();
    virtual void c4();  virtual void c5();  virtual void c6();  virtual void c7();
    virtual void c8();  virtual void c9();  virtual void c10(); virtual void c11();
    virtual void c12();
};
struct V37 {                            // virtual slots 0x00 .. 0x90
    virtual void d0();  virtual void d1();  virtual void d2();  virtual void d3();
    virtual void d4();  virtual void d5();  virtual void d6();  virtual void d7();
    virtual void d8();  virtual void d9();  virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36();
};

// script host object; this+4  (slots 0x94 / 0x9c / 0xa0)
struct Host : V37 {
    virtual int  h37(void*);            // 0x94
    virtual void h38();                 // 0x98
    virtual int  h39(void*);            // 0x9c
    virtual int  h40(void*);            // 0xa0
};

// stream / file object (IFile, IOStream)
struct IStream {
    virtual void  s0();                                    // 0x00
    virtual void  s1();                                    // 0x04
    virtual void  s2();                                    // 0x08
    virtual void  s3();                                    // 0x0c
    virtual void  s4();                                    // 0x10
    virtual void  s5();                                    // 0x14
    virtual void* s6();                                    // 0x18
    virtual void  s7();                                    // 0x1c
    virtual void  s8();                                    // 0x20
    virtual void  s9();                                    // 0x24
    virtual void  s10();                                   // 0x28
    virtual void  s11();                                   // 0x2c
    virtual void  s12();                                   // 0x30
    virtual bool  s13(void*, void*, int, int, int, int);   // 0x34
    virtual void  s14(void*, int);                         // 0x38
};

// resource-manager singleton
struct ResMan : V13 {
    virtual void  m13(); virtual void m14(); virtual void m15(); virtual void m16();
    virtual void  m17(); virtual void m18(); virtual void m19(); virtual void m20();
    virtual void  m21();
    virtual void* m22(void*);                             // 0x58
};

// global at 0x0166cc08 (animation resource lookup singleton)
struct ResObj : V13 {
    virtual void  o13(void*);                             // 0x34
    virtual void  o14(); virtual void o15(); virtual void o16(); virtual void o17();
    virtual void  o18(); virtual void o19(); virtual void o20(); virtual void o21();
    virtual void  o22(); virtual void o23();
    virtual void* o24(void*, int);                        // 0x60
};

// async load request object
struct RespObj {
    virtual void  r0();
    virtual void  r1();
    virtual void  r2();                                   // 0x08
    virtual void  r3(); virtual void r4(); virtual void r5();
    virtual void* r6();                                   // 0x18
    virtual void  r7(); virtual void r8();
    virtual void  r9();                                   // 0x24
    virtual void  r10();
    virtual int   r11();                                  // 0x2c
    virtual int   r12(void*, int);                        // 0x30
};

// object whose slot 0x30 is called from the feedback walker
struct WObj : V12 {
    virtual void* w12(void*);                             // 0x30
};

struct OutObj {                                          // job output object
    virtual void o0(); virtual void o1(); virtual void o2();
};

struct TreeObj {                                         // eastl::rbtree anchor
    void* find(void** out, const void* key);             // 0x00e5c780
};

struct Job {                                             // SP::cJob-ish
    uint32_t pad00[8];                                   // +0x00 .. +0x1f
    OutObj*  out;                                        // +0x20
    int  ContinueJob();                                  // 0x0068f970 (thiscall)
    void Wait();                                         // 0x006926b0 (thiscall)
};

struct JobNode {                                         // node of the manager map
    uint32_t pad00[5];                                   // +0x00 .. +0x13
    Job*     job;                                        // +0x14
};

// =========================================================================== script objects
struct AnimInfo {                                        // *(cmd + 0xc)
    uint32_t pad00[3];                                   // +0x00 .. +0x0b
    int32_t  f0c;                                        // +0x0c
    uint32_t pad10[6];                                   // +0x10 .. +0x27
    uint8_t  b28, b29, b2a;
    uint8_t  pad2b;
    uint32_t f2c;                                        // +0x2c
    uint32_t f30;                                        // +0x30
    uint32_t f34;                                        // +0x34
    uint32_t f38;                                        // +0x38
    uint32_t f3c;                                        // +0x3c
    uint32_t f40;                                        // +0x40
    uint32_t f44;                                        // +0x44
};

struct CArgs {                                           // EA::ArgScript::cArguments
    int*         MainArguments(int n);                                    // 0x00838320
    const char** MainArguments(int* pCount, int a, int b);                // 0x00838020
};

struct Cmd {
    void*     f0;                                        // +0x00
    Host*     host;                                      // +0x04
    void*     f8;                                        // +0x08
    AnimInfo* data;                                      // +0x0c

    void Set0c(CArgs*);       // 0xa0 -> +0x0c
    void Set34(CArgs*);       // 0x9c -> +0x34
    void Set28(CArgs*);       // 0x94 -> +0x28
    void Set29(CArgs*);       // 0x94 -> +0x29
    void Set2a(CArgs*);       // 0x94 -> +0x2a
    void Mask2c(CArgs*);
    void Mask30(CArgs*);
};

// =========================================================================== manager (cSPCreatureAnimManager-ish)
// The free __thiscall entry points are modelled as members of a stub so that
// the compiler emits the ecx (=this) setup the retail code has.
struct Mgr {
    void* FbApplyFilter(const void* key, uint* filter);   // 0x00a07fc0
    Job*  FeedbackJob(uint key, char flag);    // 0x00a08090
    bool  SelectFeedbackRecord(uint key);      // 0x00a08110
    bool  WriteAnimList(IStream* s);           // 0x00a081b0
    bool  WriteAnimListFile(IStream* file);    // 0x00a08490
};

// =========================================================================== feedback map
struct FbRecord {                                        // 0x1c
    float    f0, f4;
    uint32_t f8, fC, f10, f14, f18;
};
struct FbEvent {                                         // 0x18
    uint8_t* begin;                                      // +0x00
    uint8_t* end;                                        // +0x04
    uint32_t f08, f0c, f10;
    float    time;                                       // +0x14
};
struct FbNode {
    uint32_t pad00[0x10];                                // +0x00 .. +0x3f
    uint8_t* evBegin;                                    // +0x40
    uint8_t* evEnd;                                      // +0x44
};

extern TreeObj  g_fbTree;            // 0x01551a68
extern FbNode   g_fbEnd;             // 0x01551a6c (end sentinel)
extern FbNode*  g_fbRoot;            // 0x01551a70
extern int      g_fbCount;           // 0x01551a7c

extern void* RBTreeIncrement(void* node);            // 0x00921580

// =========================================================================== anim-list nodes
struct AnimRecord {                                      // 0x1c
    float     f0, f4;
    uint32_t  f8;
    uint16_t* v_c;                                       // +0x0c
    uint16_t* v_10;                                      // +0x10
    uint32_t  pad14, pad18;
};
struct AnimEvent {                                       // 0x18
    AnimRecord* begin;                                   // +0x00
    AnimRecord* end;                                     // +0x04
    uint32_t    pad08, pad0c, pad10;
    float       time;                                    // +0x14
};
struct AnimNode {
    uint32_t    pad00[5];                                // +0x00 .. +0x13
    int32_t     key;                                     // +0x14
    uint16_t*   seqBegin;                                // +0x18
    uint16_t*   seqEnd;                                  // +0x1c
    uint32_t    pad20, pad24;
    float       f28;                                     // +0x28
    float       f2c;                                     // +0x2c
    uint8_t     b30, b31, b32;
    uint8_t     pad33;
    uint32_t    d34, d38, d3c;                           // +0x34 / +0x38 / +0x3c
    AnimEvent*  evBegin;                                 // +0x40
    AnimEvent*  evEnd;                                   // +0x44
};

// =========================================================================== manager globals
struct Vec14 {                                           // {u8* p0; u8* p4;}
    uint8_t* p0;                                         // +0x00
    uint8_t* p4;                                         // +0x04
};
struct Elem14 {                                          // 0x14
    uint8_t*  str;                                       // +0x00
    uint8_t*  strEnd;                                    // +0x04
    uint32_t  pad08, pad0c;
    uint32_t  f10;                                       // +0x10
};
struct Node3 {                                           // node value at +0x10
    uint32_t pad00[4];                                   // +0x00 .. +0x0f
    uint32_t a10;                                        // +0x10
    uint32_t a14;                                        // +0x14
    uint32_t a18;                                        // +0x18
};
struct NodeVec {                                         // node value {key; u32 vec}
    uint32_t  pad00[4];                                  // +0x00 .. +0x0f
    uint32_t  key;                                       // +0x10
    uint32_t* vecBegin;                                  // +0x14
    uint32_t* vecEnd;                                    // +0x18
};
struct Elem16 {                                          // 0x10
    uint32_t a0;
    float    f4, f8;
    uint32_t aC;
};
struct NodeVec16 {                                       // node value {key; Elem16 vec}
    uint32_t pad00[4];                                   // +0x00 .. +0x0f
    uint32_t key;                                        // +0x10
    Elem16*  vecBegin;                                   // +0x14
    Elem16*  vecEnd;                                     // +0x18
};
struct MapHead {                                         // {node* end@4; node* root@8; ... count@0x14}
    uint32_t pad00;
    uint8_t* end;                                        // +0x04
    uint8_t* root;                                       // +0x08
    uint32_t pad0c, pad10;
    uint32_t count;                                      // +0x14
};

extern Vec14*   g_p070;              // 0x0166c070
extern MapHead* g_p074;              // 0x0166c074
extern MapHead* g_p078;              // 0x0166c078
extern MapHead* g_p080;              // 0x0166c080
extern ResObj*  g_p166cc08;          // 0x0166cc08
extern float    g_f1550b84;          // 0x01550b84

// =========================================================================== free callees
void*   __cdecl GetManager();                                       // 0x0067dcd0
void    __cdecl GetTickCount100ns(uint64* out);                     // 0x0091ffd0
void*   __cdecl FUN_009a4430(int a, void* b, int c);                // 0x009a4430
void*   __cdecl ZoneObject_new(int size, const char* name, int, int, int, int);   // 0x00926020
void*   __cdecl EAAllocate(uint size, const char* name, int, int, int, int);      // 0x00f473a0
bool    __cdecl FUN_00a057a0(void* a, void* b);                     // 0x00a057a0
void*   __cdecl ReadAnimationStaticDataFromStreamWrapper(void*, void*, void*);    // 0x0099ed90
void*   __cdecl ReadGaitRecordStaticDataFromStreamWrapper(void*);   // 0x009e59b0
void*   __cdecl operator_new_arr(void* p, int a, int b);            // 0x011e073e

bool __cdecl WriteU32(IStream* s, void* p, int n, int a);           // 0x0093aa70
bool __cdecl StreamWrite(IStream* s, void* p, int n);               // 0x0093a9a0
bool __cdecl WriteCString(IStream* s, void* p, int n, int a);       // 0x0093adb0

// members reached through a raw `this` in ecx
struct Blob {
    uint32_t pad0;                                       // +0x00
    void*    obj;                                        // +0x04
    volatile long refs;                                  // +0x08
    uint32_t padc;                                       // +0x0c
    int32_t  f10;                                        // +0x10
    void* Init(void* a, const char* s);                  // 0x0093bca0 (thiscall)
};
struct GFAR {                                            // GraphicsFactoryAsyncRequest
    void* Cons(void* a, void* b, const char* s);         // 0x0093c270 (thiscall)
};
struct Slot {                                            // object at cmd+0x14
    void* v;                                             // +0x00
    void set(void* v);                                   // 0x0099ecb0 (thiscall)
};
struct SharedObj {                                       // blob payload
    virtual void sd0(int);
};

inline void BlobAddRef(Blob* b)
{
    if (b)
        _InterlockedIncrement(&b->refs);
}
inline void BlobRelease(Blob* b)
{
    if (!b)
        return;
    if (_InterlockedDecrement(&b->refs) == 0) {
        b->refs = 1;
        if (b->obj)
            ((SharedObj*)b->obj)->sd0(1);
    }
}

// =========================================================================== 0x00a07ae0
// @ 0x00a07ae0
void Cmd::Set0c(CArgs* a)
{
    int* r = a->MainArguments(1);
    int v = host->h40((void*)r[0]);
    *(int*)((char*)data + 0xc) = v;
}

// =========================================================================== 0x00a07b70
// @ 0x00a07b70
void Cmd::Set34(CArgs* a)
{
    int* r = a->MainArguments(1);
    int v = host->h39((void*)r[0]);
    *(int*)((char*)data + 0x34) = v;
}

// =========================================================================== 0x00a07ba0
// @ 0x00a07ba0
void Cmd::Set28(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b28 = v;
}

// =========================================================================== 0x00a07c00
// @ 0x00a07c00
void Cmd::Set29(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b29 = v;
}

// =========================================================================== 0x00a07c30
// @ 0x00a07c30
void Cmd::Mask2c(CArgs* a)
{
    int count = 0;
    const char** argv = a->MainArguments(&count, 1, 0x7fffffff);
    int i = 0;
    if (count > 0) {
        do {
            int v = host->h39((void*)argv[i]);
            if (v < 0) {
                data->f2c = 0xffffffff;
                return;
            }
            unsigned m = 1u << v;
            ++i;
            data->f2c |= m;
        } while (i < count);
    }
}

// =========================================================================== 0x00a07cb0
// @ 0x00a07cb0
void Cmd::Mask30(CArgs* a)
{
    int count = 0;
    const char** argv = a->MainArguments(&count, 1, 0x7fffffff);
    int i = 0;
    if (count > 0) {
        do {
            int v = host->h39((void*)argv[i]);
            if (v < 0) {
                data->f30 = 0xffffffff;
                return;
            }
            unsigned m = 1u << v;
            ++i;
            data->f30 |= m;
        } while (i < count);
    }
}

// =========================================================================== 0x00a07d60
// @ 0x00a07d60
void Cmd::Set2a(CArgs* a)
{
    int* r = a->MainArguments(1);
    uint8_t v = (uint8_t)host->h37((void*)r[0]);
    data->b2a = v;
}

// =========================================================================== 0x00a07d90
// @ 0x00a07d90
void __stdcall FUN_00a07d90(uint key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return;

    int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
    if (evCount == 0)
        return;

    for (int i = 0; i < evCount; ++i) {
        uint8_t* ev = n->evBegin + i * 0x18;
        uint8_t* recBegin = *(uint8_t**)ev;
        uint8_t* recEnd   = *(uint8_t**)(ev + 4);
        int recCount = (int)((recEnd - recBegin) / 0x1c);
        for (int j = 0; j < recCount; ++j)
            FUN_009a4430(0, *(void**)(recBegin + j * 0x1c + 8), 0);
    }
}

// =========================================================================== 0x00a07e40
// @ 0x00a07e40
bool __cdecl FUN_00a07e40(void* a1, RespObj* req)
{
    void* p = req->r6();
    int n = ((RespObj*)p)->r11();
    if (n == -1) {
        req->r2();
        return false;
    }

    Blob* b = (Blob*)ZoneObject_new(0x18, "Anim/BackgroundLoading", 0, 0, 0, 0);
    if (b)
        b = (Blob*)b->Init((void*)n, "Anim/BackgroundLoading/SharedPointer");
    BlobAddRef(b);

    char* dst = (char*)b->f10;
    int rem = n;
    while (rem > 0) {
        int wrote = ((RespObj*)p)->r12(dst, rem);
        if (wrote == -1)
            break;
        rem -= wrote;
        dst += wrote;
    }

    req->r9();

    if (rem != 0) {
        BlobRelease(b);
        req->r2();
        return false;
    }

    RespObj* rq = (RespObj*)EAAllocate(0x24, "Anim/BackgroundLoading", 0, 0, 0, 0);
    if (rq) {
        rq = (RespObj*)((GFAR*)rq)->Cons(b, (void*)n, "Anim/BackgroundLoading/MemoryStream");
        rq->r1();
    }

    bool res = FUN_00a057a0(a1, rq);
    if (rq)
        rq->r2();
    BlobRelease(b);
    req->r2();
    return res;
}

// =========================================================================== 0x00a07fc0
// @ 0x00a07fc0
void* Mgr::FbApplyFilter(const void* key, uint* filter)
{
    FbNode* n;
    void* last = g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return last;

    int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
    for (int i = 0; i < evCount; ++i) {
        if (filter == 0 || *filter == (uint)i) {
            uint8_t* ev = n->evBegin + i * 0x18;
            uint8_t* recBegin = *(uint8_t**)ev;
            uint8_t* recEnd   = *(uint8_t**)(ev + 4);
            int recCount = (int)((recEnd - recBegin) / 0x1c);
            for (int j = 0; j < recCount; ++j)
                last = ((WObj*)this)->w12(*(void**)(recBegin + j * 0x1c + 8));
        }
    }
    return last;
}

// =========================================================================== 0x00a08090
// @ 0x00a08090
Job* Mgr::FeedbackJob(uint key, char flag)
{
    JobNode* n;
    ((TreeObj*)((char*)this + 0x34))->find((void**)&n, &key);
    if (n == (JobNode*)((char*)this + 0x38))
        return 0;

    if (!flag && n->job != 0 && (uint)(n->job->ContinueJob() - 7) > 1)
        return 0;

    if (n->job != 0) {
        n->job->Wait();
        OutObj* p = n->job->out;
        if (p) {
            p->o1();
            p->o2();
            return (Job*)p;
        }
    }
    return 0;
}

// =========================================================================== 0x00a08110
// @ 0x00a08110
bool Mgr::SelectFeedbackRecord(uint key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n == &g_fbEnd)
        return false;

    uint8_t* ev = n->evBegin;
    if (ev == n->evEnd)
        return false;

    uint8_t* rec = *(uint8_t**)ev;
    if (rec == *(uint8_t**)(ev + 4))
        return false;

    Slot* slot = (Slot*)((char*)this + 0x14);
    void* r = FUN_009a4430(0, *(void**)(rec + 8), 0);
    slot->set(r);
    return slot->v != 0;
}

// =========================================================================== 0x00a08180
// @ 0x00a08180
void* __stdcall FUN_00a08180(const uint* key)
{
    FbNode* n;
    g_fbTree.find((void**)&n, &key);
    if (n != &g_fbEnd)
        return (char*)n + 0x14;
    return 0;
}

// =========================================================================== 0x00a081b0
// @ 0x00a081b0
bool Mgr::WriteAnimList(IStream* s)
{
    uint32_t magic = 0x74736c61;
    WriteU32(s, &magic, 1, 0);
    uint32_t ver = 0xa;
    WriteU32(s, &ver, 1, 0);
    uint32_t count = (uint32_t)g_fbCount;
    WriteU32(s, &count, 1, 0);

    for (AnimNode* n = (AnimNode*)g_fbRoot; n != (AnimNode*)&g_fbEnd;
         n = (AnimNode*)RBTreeIncrement(n)) {
        int32_t key = n->key;
        WriteU32(s, &key, 1, 0);

        int seqN = (int)((n->seqEnd - n->seqBegin) >> 1);
        WriteU32(s, &seqN, 1, 0);
        s->s14(n->seqBegin, (int)((n->seqEnd - n->seqBegin) >> 1) * 2);

        uint32_t f28 = *(uint32_t*)&n->f28;
        WriteU32(s, &f28, 1, 0);
        uint32_t f2c = *(uint32_t*)&n->f2c;
        WriteU32(s, &f2c, 1, 0);

        uint8_t b30 = n->b30 != 0;
        StreamWrite(s, &b30, 1);
        uint8_t b31 = n->b31 != 0;
        StreamWrite(s, &b31, 1);
        uint8_t b32 = n->b32 != 0;
        StreamWrite(s, &b32, 1);

        uint32_t d34 = n->d34;
        WriteU32(s, &d34, 1, 0);
        uint32_t d38 = n->d38;
        WriteU32(s, &d38, 1, 0);
        uint32_t d3c = n->d3c;
        WriteU32(s, &d3c, 1, 0);

        int evCount = (int)((n->evEnd - n->evBegin) / 0x18);
        WriteU32(s, &evCount, 1, 0);
        if (evCount > 0) {
            for (int i = 0; i < evCount; ++i) {
                AnimEvent* ev = n->evBegin + i;
                uint32_t t = *(uint32_t*)&ev->time;
                WriteU32(s, &t, 1, 0);

                int recCount = (int)((ev->end - ev->begin) / 0x1c);
                WriteU32(s, &recCount, 1, 0);
                if (recCount > 0) {
                    for (int j = 0; j < recCount; ++j) {
                        AnimRecord* r = ev->begin + j;
                        uint32_t f0 = *(uint32_t*)&r->f0;
                        WriteU32(s, &f0, 1, 0);
                        uint32_t f4 = *(uint32_t*)&r->f4;
                        WriteU32(s, &f4, 1, 0);
                        uint32_t f8 = r->f8;
                        WriteU32(s, &f8, 1, 0);
                        int vn = (int)((r->v_10 - r->v_c) >> 1);
                        WriteU32(s, &vn, 1, 0);
                        s->s14(r->v_c, (int)((r->v_10 - r->v_c) >> 1) * 2);
                    }
                }
            }
        }
    }
    return true;
}

// =========================================================================== 0x00a08490
// @ 0x00a08490
bool Mgr::WriteAnimListFile(IStream* file)
{
    uint64 ts = 0;
    GetTickCount100ns(&ts);

    struct { uint32_t lo; uint32_t magic; uint32_t hi; } k;
    k.lo = (uint32_t)ts;
    k.magic = 0x4aeb6bc6;
    k.hi = (uint32_t)(ts >> 32);

    IStream* h = 0;
    if (!file->s13(&k, &h, 2, 6, 1, 0)) {
        if (h)
            h->s2();
        return false;
    }

    void* r = h->s6();
    bool res = WriteAnimList((IStream*)r);
    h->s9();
    if (h)
        h->s2();
    return res;
}

// =========================================================================== 0x00a08540
// @ 0x00a08540
bool __cdecl FUN_00a08540(IStream* s)
{
    uint64 ts = 0;
    GetTickCount100ns(&ts);

    struct { uint32_t lo; uint32_t magic; uint32_t hi; } k;
    k.lo = (uint32_t)ts;
    k.magic = 0x7c19aa7a;
    k.hi = (uint32_t)(ts >> 32);

    IStream* h = 0;
    if (!s->s13(&k, &h, 2, 6, 1, 0)) {
        if (h)
            h->s2();
        return false;
    }

    IStream* r = (IStream*)h->s6();

    uint32_t magic = 0x70637470;
    WriteU32(r, &magic, 1, 0);
    uint32_t ver = 4;
    WriteU32(r, &ver, 1, 0);
    uint32_t f = *(uint32_t*)&g_f1550b84;
    WriteU32(r, &f, 1, 0);

    Vec14* v = g_p070;
    uint32_t n0 = (uint32_t)((v->p4 - v->p0) / 0x14);
    WriteU32(r, &n0, 1, 0);
    for (uint32_t i = 0; i < n0; ++i) {
        Elem14* e = (Elem14*)(v->p0 + i * 0x14);
        WriteCString(r, e->str, (int)(e->strEnd - e->str), 0);
        uint32_t x = e->f10;
        WriteU32(r, &x, 1, 0);
    }

    MapHead* m1 = g_p074;
    uint32_t c1 = m1->count;
    WriteU32(r, &c1, 1, 0);
    for (uint8_t* nd = m1->root; nd != m1->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        Node3* v1 = (Node3*)nd;
        WriteU32(r, &v1->a10, 1, 0);
        WriteU32(r, &v1->a14, 1, 0);
        WriteU32(r, &v1->a18, 1, 0);
    }

    MapHead* m2 = g_p080;
    uint32_t c2 = m2->count;
    WriteU32(r, &c2, 1, 0);
    for (uint8_t* nd = m2->root; nd != m2->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        NodeVec* nv = (NodeVec*)nd;
        WriteU32(r, &nv->key, 1, 0);
        int cnt = (int)((nv->vecEnd - nv->vecBegin) >> 2);
        WriteU32(r, &cnt, 1, 0);
        for (int i = 0; i < cnt; ++i) {
            uint32_t x = nv->vecBegin[i];
            WriteU32(r, &x, 1, 0);
        }
    }

    MapHead* m3 = g_p078;
    uint32_t c3 = m3->count;
    WriteU32(r, &c3, 1, 0);
    for (uint8_t* nd = m3->root; nd != m3->end; nd = (uint8_t*)RBTreeIncrement(nd)) {
        NodeVec16* nv = (NodeVec16*)nd;
        WriteU32(r, &nv->key, 1, 0);
        int cnt = (int)((nv->vecEnd - nv->vecBegin) >> 4);
        WriteU32(r, &cnt, 1, 0);
        for (int i = 0; i < cnt; ++i) {
            Elem16* e = nv->vecBegin + i;
            WriteU32(r, &e->a0, 1, 0);
            uint32_t f4 = *(uint32_t*)&e->f4;
            WriteU32(r, &f4, 1, 0);
            uint32_t f8 = *(uint32_t*)&e->f8;
            WriteU32(r, &f8, 1, 0);
            WriteU32(r, &e->aC, 1, 0);
        }
    }

    h->s9();
    if (h)
        h->s2();
    return true;
}

// =========================================================================== 0x00a088e0
// @ 0x00a088e0
void* __cdecl FUN_00a088e0(void* param)
{
    void* result = 0;
    IStream* handle = 0;
    bool didRead = false;

    struct { void* p; uint32_t magic; uint32_t pad; } key;
    key.p = param;
    key.magic = 0xee17c6ad;
    key.pad = 0;

    IStream* obj = (IStream*)g_p166cc08->o24(param, 1);
    if (obj == 0) {
        ResMan* m = (ResMan*)GetManager();
        IStream* r = (IStream*)m->m22(&key);
        if (r == 0)
            goto done;
        if (handle) {
            handle->s2();
            handle = 0;
        }
        if (!r->s13((void*)&key, &handle, 1, 6, 1, 0))
            goto done;
        obj = (IStream*)handle->s6();
    } else {
        didRead = true;
    }

    if (obj != 0) {
        struct { void** vtbl; IStream* obj; } w;
        w.vtbl = (void**)0x1448b30;
        w.obj = obj;
        obj->s1();

        char buf[0x100];
        buf[0] = 0;
        operator_new_arr(buf, 0, 0xff);
        result = ReadAnimationStaticDataFromStreamWrapper(&w, buf, &key);
        if (didRead)
            g_p166cc08->o13(param);
        w.obj->s2();
    }

done:
    if (handle) {
        handle->s9();
        handle->s2();
    }
    return result;
}

// =========================================================================== 0x00a08a20
// @ 0x00a08a20
void* __cdecl FUN_00a08a20(void* param)
{
    void* result = 0;
    IStream* handle = 0;

    struct { void* p; uint32_t magic; uint32_t pad; } key;
    key.p = param;
    key.magic = 0x25df0112;
    key.pad = 0;

    ResMan* m = (ResMan*)GetManager();
    IStream* r = (IStream*)m->m22(&key);
    if (r != 0) {
        if (handle) {
            handle->s2();
            handle = 0;
        }
        if (r->s13((void*)&key, &handle, 1, 6, 1, 0)) {
            IStream* obj = (IStream*)handle->s6();
            if (obj != 0) {
                struct { void** vtbl; IStream* obj; } w;
                w.vtbl = (void**)0x1448b30;
                w.obj = obj;
                obj->s1();
                result = ReadGaitRecordStaticDataFromStreamWrapper(&w);
                w.vtbl = (void**)0x1448b30;
                if (w.obj)
                    w.obj->s2();
            }
        }
    }

    if (handle) {
        handle->s9();
        handle->s2();
    }
    return result;
}
