// Graphics/Editor sprite-bake job: a big /Od routine that builds a bake job, runs it for the
// main list (and optionally the editor list) and publishes the resulting resource.
// Built unoptimized: /Od /Ob1 /arch:SSE.
#include <intrin.h>
#include <new>
#include "types.h"

extern "C" {
extern void* vtbl_Editor_cEditorResource[];
extern void* vtbl_Graphics_BakeSprites[];
extern void* vtbl_Simulator_cCreatureAbility[];
extern void* vtbl_BakeJob_Final0[];   // 0x013eb928
extern void* vtbl_BakeJob_Final1[];   // 0x013eb924
}

// ---- helper types -------------------------------------------------------------------------

// Intrusive-ref-counted resource (Resource::ThreadedObject): refcount at +4.
struct ThreadedObject {
    void** vptr; volatile long mnRefCount;
    void Release();
};

struct PtrVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };

// Reference-counted handle used for the bake result (releases through FUN_00690120).
struct ResultRef { void* p; };

// The BakeSprites job: vptr at +0 (three base ctors rewrite it), a sub-interface at +4
// whose refcount lives at +8.
struct RC { volatile long n; RC() { _InterlockedExchange(&n, 0); } };
struct SubBase { void** vp; SubBase() { vp = vtbl_Simulator_cCreatureAbility; } };
struct SubIface : SubBase { RC rc; };
struct JobBase0 { void** vp; JobBase0() { vp = vtbl_Editor_cEditorResource; } };
struct JobBase1 : JobBase0 { JobBase1() { vp = vtbl_Graphics_BakeSprites; } };

struct BakeJob : JobBase1 {
    SubIface iface;           // +4 (vptr), +8 (refcount)
    bool     mbDone;          // +0xC
    uint32_t mKeyLow;         // +0x10
    uint32_t mKeyHigh;        // +0x14
    BakeJob(uint32_t keyLow, uint32_t keyHigh);
};

// @ 0x00410cc0
BakeJob::BakeJob(uint32_t keyLow, uint32_t keyHigh)
{
    vp = vtbl_BakeJob_Final0;
    iface.vp = vtbl_BakeJob_Final1;
    mbDone = false;
    mKeyLow = keyLow;
    mKeyHigh = keyHigh;
}

// @ 0x00410d40
void __cdecl EASTL_allocator_deallocate(void* p);  // 0x00f47380
struct BakeJobBaseDtor {
    int x;
    BakeJobBaseDtor* dtor();                       // FUN_00410d70
    BakeJobBaseDtor* scalarDeletingDtor(unsigned flags);
};
BakeJobBaseDtor* BakeJobBaseDtor::scalarDeletingDtor(unsigned flags)
{
    dtor();
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// ---- 0x004103c0 ---------------------------------------------------------------------------

struct Interface { virtual void v0(); virtual void v1(); };  // slot 0 = AddRef, slot 1 = Release

struct Manager { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
                 virtual void s8(); virtual void s9(); };

struct Queue {              // vtable slots used: 0x10, 0x20, 0x24
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(uint32_t arg);       // +0x10
    virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8();                   // +0x20
    virtual void q9();                   // +0x24
};

struct PropertyList { virtual void AddRef(); virtual void Release(); };
struct EditorMgr {          // vtable slots 0x2c, 0x34
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9(); virtual void e10();
    virtual void RegisterProperties(uint32_t id, uint32_t key, void* ref);   // +0x2c
    virtual void e12();
    virtual void SetPropertyList(PropertyList* pl, uint32_t a, uint32_t b);  // +0x34
};
struct ServiceHub { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
                    virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7();
                    virtual void h8(); virtual void h9(); virtual void Prepare(); /* +0x28 */ };

extern ServiceHub* GetServiceHub();                       // 0x0067dd40
extern EditorMgr*  GetEditorMgr();                        // 0x0067de30
extern uint32_t    GetBakeContext(uint32_t id);           // 0x006b1f90
extern void        BakeOne(uint32_t item, uint32_t flag); // 0x00756280
extern void        InitThreadedObject(ThreadedObject* o, uint32_t a, uint32_t b);   // 0x00430450
extern Queue*      GetQueue();                            // 0x0068f4d0
extern void*       __fastcall GetRefSlot(void* ref);      // 0x0041d940
extern void        __fastcall QueueSubmit(void* ref, void* job);   // 0x004223f0
extern void        __fastcall QueueSubmit2(void* ref, void* job);  // 0x0068f9b0
extern void        __fastcall ReleaseRef(void* p);        // 0x00690120
extern void        __fastcall FlushRef(void* p);          // 0x006909b0
extern void        __fastcall AssignRef(void* dst, void* src);   // 0x0041cd10
extern void        Publish(void* x);                      // 0x00430900
extern bool        RunBake(void** outRef, void* list, uint32_t a, uint32_t b, void* c, void* d,
                           uint32_t e, void* f, uint32_t g, uint32_t h, void* i, void* j);  // 0x007573a0
extern void* ThreadedObjectNew();                         // ctor 0x0077d1d0
extern void* PropertyListNew();                           // ctor 0x006a1c40
extern void* AllocateGraphics(uint32_t sz, const char* tag, int, int, int, int);

struct BakeRequest {
    char pad0[0x228];
    uint32_t mKeyLow;            // +0x228
    uint32_t pad1;
    uint32_t mKeyHigh;           // +0x230
    uint32_t pad2;
    uint16_t mFlags;             // +0x238
    char pad3[0x338 - 0x23A];
    PtrVector mMainList;         // +0x338
    PtrVector mEditorList;       // +0x34c
    char pad4[0x388 - 0x360];
    uint32_t mOptions;           // +0x388
    char pad5[0x3dc - 0x38c];
    uint32_t mEditorOptions;     // +0x3dc
    char pad6[0x424 - 0x3e0];
    bool mbPrepared;             // +0x424
    bool mbPublishMain;          // +0x425

    bool Bake();
};

// @ 0x004103c0
bool BakeRequest::Bake()
{
    if (!mbPrepared)
        GetServiceHub()->Prepare();

    bool hasEditor = (mFlags & 0x100) != 0;
    uint32_t keyLow = mKeyLow;
    uint32_t keyHigh = mKeyHigh;
    void* result = 0;
    uint32_t ctx = GetBakeContext(0x11ac1ac);

    unsigned n = (unsigned)(mMainList.mpEnd - mMainList.mpBegin);
    for (unsigned i = 0; i < n; ++i)
        BakeOne(mMainList.mpBegin[i], 0x9cff27c);

    if (hasEditor) {
        unsigned m = (unsigned)(mEditorList.mpEnd - mEditorList.mpBegin);
        for (unsigned i = 0; i < m; ++i)
            BakeOne(mEditorList.mpBegin[i], 0x9cff27c);
    }

    ThreadedObject* threaded = 0;
    void* mem = AllocateGraphics(0x1c, "Graphics", 0, 0, 0, 0);
    ThreadedObject* created = mem ? (ThreadedObject*)ThreadedObjectNew() : 0;
    if (created != threaded) {
        ThreadedObject* old = threaded;
        if (created)
            _InterlockedExchangeAdd(&created->mnRefCount, 1);
        threaded = created;
        if (old)
            old->Release();
    }
    InitThreadedObject(threaded, keyLow, keyHigh);

    Queue* queue = GetQueue();
    void* mem2 = AllocateGraphics(0x18, "Graphics", 0, 0, 0, 0);
    BakeJob* job = mem2 ? new (mem2) BakeJob(keyLow, keyHigh) : 0;
    if (job)
        ((Interface*)job)->v0();
    queue->q8();
    queue->q4((uint32_t)GetRefSlot(&result));
    QueueSubmit(result, job);
    QueueSubmit2(result, job);
    *(uint32_t*)((char*)result + 0x18) = 1;
    queue->q9();

    if (mbPublishMain) {
        void* tmp = 0;
        uint32_t flags = (keyHigh & 0xffff00ff) | (0x7e << 8);
        Publish(RunBake /* placeholder: see nonmatching.txt */ ? GetRefSlot(&tmp) : 0);
        if (tmp) {
            FlushRef(result);
            AssignRef(&result, tmp);
        }
        if (tmp)
            ReleaseRef(tmp);
        (void)flags;
    }

    if (hasEditor) {
        void* tmp = 0;
        PropertyList* props = 0;
        uint32_t flags = (keyHigh & 0xffff00ff) | (0x71 << 8);
        EditorMgr* ed = GetEditorMgr();
        ed->RegisterProperties(0x4529f96f, flags, GetRefSlot(&tmp));
        void* pm = AllocateGraphics(0x38, "Editor", 0, 0, 0, 0);
        PropertyList* newProps = pm ? (PropertyList*)PropertyListNew() : 0;
        if (newProps != props) {
            PropertyList* old = props;
            if (newProps)
                newProps->AddRef();
            props = newProps;
            if (old)
                old->Release();
        }
        ed = GetEditorMgr();
        ed->SetPropertyList(props, keyLow, flags);
        queue->q8();
        queue->q4((uint32_t)GetRefSlot(&result));
        QueueSubmit(result, job);
        QueueSubmit2(result, job);
        queue->q9();
        if (tmp)
            ReleaseRef(tmp);
        void* out = 0;
        if (!RunBake(&out, &mEditorList, keyLow, flags, 0, &mEditorOptions, 0, &mOptions, 0, ctx, 0, result)) {
            if (props)
                props->Release();
            if (out)
                ReleaseRef(out);
            if (job)
                ((Interface*)job)->v1();
            if (threaded)
                threaded->Release();
            if (result)
                ReleaseRef(result);
            return false;
        }
        FlushRef(out);
        AssignRef(&out, out);
        if (props)
            props->Release();
        if (out)
            ReleaseRef(out);
    }

    uint32_t flags2 = (keyHigh & 0xffff00ff) | (0x71 << 8);
    uint32_t unusedKey = keyLow;
    void* out2 = 0;
    (void)flags2; (void)unusedKey;
    bool ok = RunBake(&out2, &mMainList, keyLow, keyHigh, threaded, 0, 0, &mOptions, 0, ctx, &unusedKey, result);
    if (!ok) {
        if (out2)
            ReleaseRef(out2);
        if (job)
            ((Interface*)job)->v1();
        if (threaded)
            threaded->Release();
        if (result)
            ReleaseRef(result);
        return false;
    }
    FlushRef(out2);
    if (out2 != result) {
        void* old = result;
        if (out2)
            ReleaseRef(out2);   // stands in for AddRef (FUN_0068f950)
        result = out2;
        if (old)
            ReleaseRef(old);
    }
    FlushRef(out2);
    if (out2)
        ReleaseRef(out2);
    if (job)
        ((Interface*)job)->v1();
    if (threaded)
        threaded->Release();
    if (result)
        ReleaseRef(result);
    return true;
}
