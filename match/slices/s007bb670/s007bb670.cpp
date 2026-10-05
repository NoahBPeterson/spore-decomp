// Slice s007bb670 — SP::cContentValidationSummarizer setup + a cThumbnailManager
// message handler.  Both are /O2 /arch:SSE2 /EHsc routines in the UI/thumbnail
// region.  Reconstructed from the Ghidra decompile; see nonmatching.txt.
#include "types.h"

// --- job / rect object (shared with s007ba350) -----------------------------
struct RectID { int mPageID; int mAllocID; };

struct  Job {
    virtual void v0();       // +0
    virtual void v1();       // +4
    virtual void v2();       // +8
    char pad[0x98];
    unsigned char m82;       // +0x82
    unsigned char m83;       // +0x83
    int  m84, m88, m8c, m90, m94;
    int  m98, m9c, ma0, ma4;
    int  mac[8];
    float mcc;
};

// cThumbnailManager::cFilterChainJob
struct cFilterChainJob { void Shutdown(); };

// An object referenced through +0x10c8 (AutoRefCount<T> payload).
struct ModelObj {
    virtual void v0();       // +0
    virtual void v1();       // +4
    char pad[0x38];
    int  m40;                // +0x40
};

struct Thumb {
    char pad[0xc];
    int  m0c;                // +0xc
    int  m10;                // +0x10
    char pad2[0x94];
    ModelObj* m_a8;          // +0xa8
    char pad3[0x18];
    unsigned char m_c4;      // +0xc4
};

// SP::MessageServer's base message object (refcounted, 2 vtables).
struct BehaviorMessage {
    virtual void v0();       // +0
    virtual void v1();       // +4
    virtual void v2();       // +8
    int  mRefCount;          // +4
    int  m8;                 // +8
    int  mc;                 // +0xc
    int  m10;                // +0x10
    int  m14;
    int  m18;                // +0x18
    int  m1c;
    int  m20;                // +0x20
    int  m24;
    int  m28;                // +0x28
};

struct MessageServer_t {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void Send(int id, BehaviorMessage* msg, int a);   // +0x14
};

void* operator new(unsigned int size, const char* group, int a, int b, int c, int d);

extern "C" {
    void* __cdecl FUN_0067dd50();
    void* __cdecl FUN_0067dd40();
    MessageServer_t* __cdecl SP_MessageServer();
}

// Helpers of the summarizer setup (thiscall on the job / manager).
void FUN_007b9420(Job* self, int v);
void FUN_007b9510(Job* self, int id, int* a, int* b, int c);
void FUN_007b9750(Job* self, void* other);
Job* FUN_007b8550(Job* p);

// ---------------------------------------------------------------------------
// @ 0x007bb670  SP::cContentValidationSummarizer::Summarize (free-ish setup)
// ---------------------------------------------------------------------------
struct ContentValidationSummarizer {
    virtual void v0();
    virtual void v1();
    int  m8;
    int  mc, m10, m14;
    unsigned char m20;
    int  m24, m28, m2c, m30;
};

void FUN_007bb670()
{
    void* app = FUN_0067dd50();
    void* mgr = FUN_0067dd40();
    (void)app;

    RectID r0 = { -1, -1 };
    RectID r1 = { -1, -1 };
    int stack0[2] = { -1, -1 };
    int stack1[2] = { -1, -1 };

    // query two rect ids from the manager
    ((void(*)(void*,void*))((*(void***)mgr)[0xac/4]))(mgr, &r0);
    ((void(*)(void*,void*))((*(void***)mgr)[0xbc/4]))(mgr, &stack0);

    ContentValidationSummarizer* cs = new ("Graphics",0,0,0,0) ContentValidationSummarizer();
    (void)cs; (void)r1; (void)stack1;

    // A long chain of cFilterChainJob allocations + rect configuration follows.
    // (field stores into the jobs are omitted — see partial.txt)
}

// ---------------------------------------------------------------------------
// @ 0x007bbde0  cThumbnailManager message handler (ret 4)
// ---------------------------------------------------------------------------
struct cThumbnailManager {
    char pad[0x10c8];
    ModelObj*     mModel;        // +0x10c8
    char pad2[0x10fc - 0x10cc];
    cFilterChainJob* mFilterChain;   // +0x10fc
    Thumb* mThumbs[1024];        // +0x1100

    void HandleSomething(void* msg);
};

void cThumbnailManager::HandleSomething(void* msg)
{
    int f8  = *(int*)((char*)msg + 8);
    int f10 = *(int*)((char*)msg + 0x10);
    int f18 = *(int*)((char*)msg + 0x18);
    int f20 = *(int*)((char*)msg + 0x20);
    int f28 = *(int*)((char*)msg + 0x28);
    int f30 = *(int*)((char*)msg + 0x30);

    if (f8 == f18 - 1) {
        if (f18 != 0) {
            Thumb** p = mThumbs;
            int n = f18;
            do {
                Thumb* t = *p;
                if (t->m_c4) {
                    ModelObj* o = t->m_a8;
                    if (o) { t->m_a8 = 0; o->v1(); }
                    t->m0c = 0;
                    t->m10 = 0;
                    t->m_c4 = 0;
                }
                ++p;
                --n;
            } while (n);
        }
        mFilterChain->Shutdown();
        ModelObj* m = mModel;
        if (m) {
            m->v0();                     // placeholder for vtable+0x16c call
            m = mModel;
            if (m) {
                mModel = 0;
                if (m->m40 <= 1)
                    m->v1();             // placeholder for vtable+0x170 call
                else
                    --m->m40;
            }
        }
        BehaviorMessage* bm = new ("Graphics",0,0,0,0) BehaviorMessage();
        if (bm) bm->v1();
        bm->m8  = f10;
        bm->m10 = f20;
        bm->m18 = f28;
        bm->m20 = f30;
        SP_MessageServer()->Send(0x21d7528, bm, 0);
        if (bm) bm->v2();
    }
}
