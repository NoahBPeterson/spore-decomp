// src/game/cmn/system.cpp.cpp -- migrated from slice(s) s0112be40 by tools/migrate/rewrite.py
// Object file: cmn/system.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Thread/Mutex.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void  __stdcall GetSystemInfo(void* info);
extern void ThreadSleep(const int* ms);    // @ 0x921df0

// ---- items of slice s0112be40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
extern "C" __declspec(dllimport) void  __stdcall GetSystemInfo(void* info);
struct MutexParameters
{
    u8  pad[0x10];
    MutexParameters* ctor(int a, int b);   // @ 0x921e00
};
struct Mutex
{
    u8 m_data[0x30];

    Mutex* ctor(void* p, int recursive);   // @ 0x9222a0
    void   Lock(u32 id);                   // @ 0x9221b0
    void   Unlock();                       // @ 0x922270
    void   dtor();                         // @ 0x922130
    void   Init(const MutexParameters* p); // @ 0x922150
};
struct Voice
{
    u8    pad0[0x28];
    float m_f28;               // +0x28
    float m_f2c;               // +0x2c
    float m_f30;               // +0x30
    u8    pad1[0x47 - 0x34];
    u8    m_state;             // +0x47

    void Release(u32 flags);   // @ 0x112e600
    void Stop(int reason);     // @ 0x112e690
};
struct TimerManager
{
    u8   pad0[0x20];
    void ExecuteTimers(int reset);  // @ 0x112d9b0
    void Defragment();              // @ 0x112da30
    void Release();                 // @ 0x112da60
    void dtor();                    // @ 0xc2e4e0
};
struct ICoreAllocator
{
    virtual void  v0();
    virtual void* Alloc(u32 a1, u32 a2, int a3, u32 a4, int a5); // +0x4
    virtual void  v2();
    virtual void  Free(void* p, int a2);                         // +0xc
};
struct Cmd
{
    virtual void v0();
    virtual void exec(float f);    // +0x4

    void* mpNext;                  // +0x4
    u32   m_a8;                    // +0x8
    float m_fc;                    // +0xc
};
struct CompiledCmd
{
    int (*mpFn)(void*);        // +0x0
    void* mpThis;              // +0x4
    u32   m_a8;                // +0x8
    float m_fc;                // +0xc
};
extern void ThreadSleep(const int* ms);    // @ 0x921df0
struct System;
struct AudioObject
{
    u8      pad0[4];
    System* mpSystem;          // +0x4
    u32     m_a8;              // +0x8
    void*   m_ac;              // +0xc
    void*   m_a10;             // +0x10
    u8      pad1[0x10];
    u8      m_a20;             // +0x20
    u8      m_a21;             // +0x21

    void IsCommandComplete(u32 a, float f);   // @ 0x112ccf0
};
struct RtCommandHandler
{
    static u32 execute(CompiledCmd* cmd);     // @ 0x112ccd0
};
struct Node;
struct NodeList
{
    Node* m_head;              // +0x0
    Node* m_tail;              // +0x4
    int   m_count;             // +0x8
    u8    pad0[8];
    u8    m_tag;               // +0x14

    Node* find(u32 id);        // @ 0x112cd30
    Node* insert(Node* n);     // @ 0x112cd60
};
struct Node
{
    Node* pnext;               // +0x0
    u32   m_id;                // +0x4
    u8    pad1[0x1c];
};
struct System
{
    u8  pad00[0x14];
    ICoreAllocator* mpAllocator;   // +0x14
    u32 m_a18;                     // +0x18
    u32 m_a1c;                     // +0x1c
    void* mpCmdBuffer;             // +0x20
    u32 m_a24;                     // +0x24
    void* m_a28;                   // +0x28
    void* m_a2c;                   // +0x2c
    void* m_a30;                   // +0x30
    void* m_a34;                   // +0x34
    u32 m_a38;                     // +0x38
    u32 m_a3c;                     // +0x3c
    void* mpLockFn;                // +0x40
    void* mpUnlockFn;              // +0x44
    Mutex* mpMutexA;               // +0x48
    Mutex* mpMutexB;               // +0x4c
    void* mp_a50;                  // +0x50
    void* mp_a54;                  // +0x54
    void* mpVoiceNodes;            // +0x58
    void* mpCmdList;               // +0x5c
    u8  m_timer[0x50];             // +0x60 .. +0xb0
    u32 m_b0;                      // +0xb0
    u32 m_b4;                      // +0xb4
    u32 m_b8;                      // +0xb8
    float m_bc;                    // +0xbc
    float m_c0;                    // +0xc0
    float m_c4;                    // +0xc4
    float m_c8;                    // +0xc8
    u32 m_cc;                      // +0xcc
    u32 m_d0;                      // +0xd0
    u32 m_d4;                      // +0xd4
    u32 m_d8;                      // +0xd8
    u32 m_dc;                      // +0xdc
    u32 m_e0;                      // +0xe0
    u32 m_e4;                      // +0xe4
    u32 m_e8;                      // +0xe8
    u32 m_ec;                      // +0xec
    u16 m_f0;                      // +0xf0
    u16 m_f2;                      // +0xf2
    u8  m_f4;                      // +0xf4
    u8  m_f5;                      // +0xf5
    u8  m_f6;                      // +0xf6
    u8  m_f7[6];                   // +0xf7

    System* ctor0();                          // @ 0x11341c0
    void Lock();                              // @ 0x112c600
    void Unlock();                            // @ 0x112c620
    bool someCheck(u32 v);                    // @ 0x112c640
    void updateVoices();                      // @ 0x112c690
    void pump();                              // @ 0x112c6e0
    __declspec(noinline) void* Alloc(u32 size, u32 flags, int align, ICoreAllocator* a); // @ 0x112c820
    void  Free(void* ptr, ICoreAllocator* a); // @ 0x112c850
    void  shutdown();                         // @ 0x112c880
    static System* CreateInstance(ICoreAllocator* alloc, u32 cmdBufBytes); // @ 0x112c9e0
    void lockVoiceList();                     // @ 0x112c560
    void setValue(u32* v);                    // @ 0x112c5f0

    TimerManager* timer() { return (TimerManager*)m_timer; }
};
struct AttributeSet
{
    u8  pad0[0xc];
    void* m_array;             // +0xc

    void getFloat(int i, float* out);   // @ 0x112cc80
    void getDouble(int i, double* out); // @ 0x112cca0
};
struct AllocNode
{
    System* mpSystem;          // +0x10
    void freeSelf();           // @ 0x112cdf0
};
struct AVoiceNode
{
    void dtorA();              // @ 0x1133ea0
};
struct VoiceList
{
    u8  pad0[0x28];
    void* m_a28;               // +0x28
    void* getOrCreate();       // @ 0x112ce00
};
struct Factory
{
    virtual void v0();                       // +0x0
    void* m_pad4;                            // +0x4
    bool (*mpCreate)(void* obj, u32 arg);    // +0x8
};
struct BaseObject
{
    virtual void dtor();                     // +0x0
    virtual void v1();
    virtual void v2();
    virtual void release(int);               // +0xc
};
extern System* g_audioSystem;   // @ 0x16e61a8
struct InitData
{
    u8  m_a0;
    u8  pad0[7];
    u8  m_a8;
};
// ---- items of slice s0112be40 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern System* g_audioSystem;   // @ 0x16e61a8

// callees this slice defines outside this object (rewrite.py held_callee_protos)
u32 audio_cmd_releaseVoices(void* cmd);  // 0x0112c5a0 (stays in the slice: not this object's)

// @ 0x0112c690
void System::updateVoices()
{
    for (int i = 0; i < (int)m_f0; ++i)
    {
        Voice* v = *(Voice**)((char*)*(void**)((char*)this + 0x58) + i * 8);
        if (v->m_state == 1)
        {
            float f = v->m_f28;
            if (f > v->m_f30)
                v->m_f30 = f;
            if (v->m_f2c >= v->m_f30)
                v->Stop(3);
        }
    }
}

// @ 0x0112c6e0
void System::pump()
{
    Lock();

    void* p = mpCmdList;
    if (p != 0)
    {
        Cmd* c = (Cmd*)((char*)p - 4);
        while (c != 0)
        {
            void* np = *(void**)((char*)c + 4);
            Cmd* next = np ? (Cmd*)((char*)np - 4) : 0;
            c->exec(m_bc);
            c = next;
        }
    }

    timer()->ExecuteTimers(0);
    Unlock();

    updateVoices();
    m_dc = 0;
    Lock();

    u8* cmd = (u8*)mpCmdBuffer;
    u8* end = cmd + m_b4;
    while (cmd < end)
    {
        int sz = ((int (__cdecl*)(void*))*(void**)cmd)(cmd);
        cmd += sz;
        if (cmd >= end)
            break;
    }

    if (m_b4 > m_b8)
        m_b8 = m_b4;
    ++m_e0;
    m_b4 = 0;
    m_d0 = 0;
    Unlock();

    Lock();
    timer()->ExecuteTimers(1);
    timer()->Defragment();
    m_d4 = 0;
    Unlock();
}

// @ 0x0112c820
void * rw::audio::core::System::Alloc(unsigned int size, char const * flags, unsigned int align, EA::Allocator::ICoreAllocator * a)
{
    if (a == 0)
        a = mpAllocator;
    return a->Alloc(size, flags, 1, (u32)align, 0);
}

// @ 0x0112c850
void rw::audio::core::System::Free(void * ptr, EA::Allocator::ICoreAllocator * a)
{
    if (a == 0)
        a = mpAllocator;
    a->Free(ptr, 0);
}

// @ 0x0112c880
void System::shutdown()
{
    Lock();
    {
        u8* slot = (u8*)mpCmdBuffer + m_b4;
        m_b4 += 8;
        *(void**)slot = (void*)&audio_cmd_releaseVoices;
        *(void**)(slot + 4) = this;
    }
    Unlock();

    mpMutexA->Lock(0x14a7c44);
    while (m_b4 != 0 || (int)m_e4 > 0)
    {
        pump();
        int one = 1;
        ThreadSleep(&one);
    }
    mpMutexA->Unlock();

    Lock();

    if (m_a28 != 0)
        ((AllocNode*)m_a28)->freeSelf();
    if (m_a2c != 0)
        ((AVoiceNode*)m_a2c)->dtorA();
    if (m_a30 != 0)
        ((AVoiceNode*)m_a30)->dtorA();
    if (m_a34 != 0)
        (*(void (__fastcall**)(void*))*(void**)m_a34)((void*)m_a34);

    timer()->Release();
    Unlock();

    if (mpCmdBuffer != 0)
        mpAllocator->Free(mpCmdBuffer, 0);
    if (mpVoiceNodes != 0)
        mpAllocator->Free(mpVoiceNodes, 0);

    {
        TimerManager* t = (TimerManager*)((char*)this + 0x98);
        for (int i = 1; i >= 0; --i)
        {
            t = (TimerManager*)((char*)t - 0x1c);
            t->dtor();
        }
    }

    mpAllocator->Free(this, 0);
    g_audioSystem = 0;
}

// @ 0x0112c9e0
System* System::CreateInstance(ICoreAllocator* alloc, u32 cmdBufBytes)
{
    MutexParameters params;
    params.ctor(1, 0);

    // The original loads the allocator's vtable slot into a register before the call
    // (mov edx,[eax+4]; call edx).  Model that explicitly with an __fastcall thunk:
    // ecx = this, edx = scratch, remaining arguments on the stack exactly as pushed.
    typedef void* (__fastcall* AllocFn)(void* self, int edxArg, u32 size,
                                        u32 flags, int one, u32 align, int zero);
    AllocFn fn = *(AllocFn*)(*(u32**)alloc + 1);
    System* s = (System*)fn(alloc, 0, 0x16c, (u32)"rw::audio::core::System", 1, 0x10, 0);
    if (s == 0)
        return 0;

    s = s->ctor0();

    u8* p = (u8*)(((u32)s + 0x107) & ~7u);
    s->mpCmdBuffer = 0;
    s->mpVoiceNodes = 0;
    s->m_c4 = 1.0f;
    g_audioSystem = s;
    s->mpAllocator = alloc;
    s->m_a18 = 0;
    s->m_a1c = 0;
    s->mpMutexB = (Mutex*)p;
    s->mpMutexB = p ? ((Mutex*)p)->ctor(0, 1) : 0;

    p = (u8*)(((u32)(p + 0x37)) & ~7u);
    s->mpMutexA = (Mutex*)p;
    s->mpMutexA = p ? ((Mutex*)p)->ctor(0, 1) : 0;

    s->mp_a50 = (void*)(((u32)(p + 0x37)) & ~7u);
    s->mp_a54 = (void*)((((u32)s->mp_a50) + 0xb) & ~7u);

    s->mpMutexB->Init(&params);
    s->mpMutexA->Init(&params);

    *(u32*)((char*)s + 0xf7) = 0x1010101;
    *(u16*)((char*)s + 0xfb) = 0x101;
    *(double*)((char*)s + 8) = 0.0;
    s->m_c0 = 0.0f;
    s->m_e4 = 0;
    s->m_a24 = 0;
    s->m_a28 = 0;
    s->m_c8 = 90.0f;
    s->m_cc = 0;
    s->m_d0 = 0;
    s->m_d4 = 0;
    s->m_d8 = 0;
    s->m_dc = 0;

    s->mpVoiceNodes = alloc->Alloc(8, (u32)"rw::audio::core::System::mpVoiceListNodes", 1, 0x10, 0);
    if (s->mpVoiceNodes == 0)
        goto cleanup;

    s->m_f0 = 0;
    s->m_b0 = cmdBufBytes;
    s->m_f2 = 0;
    s->m_e0 = 1;
    s->m_b8 = 0;
    s->m_b4 = 0;

    s->mpCmdBuffer = alloc->Alloc(cmdBufBytes, (u32)"rw::audio::core::CommandBuffer", 1, 4, 0);
    if (s->mpCmdBuffer == 0)
        goto cleanup;

    s->m_a2c = 0;
    s->m_a30 = 0;
    s->m_a34 = 0;
    s->m_a38 = 0;
    s->mpLockFn = 0;
    s->mpUnlockFn = 0;
    s->m_a3c = 0;

    {
        u8 si[0x24];
        GetSystemInfo(si);
        s->m_ec = 0;
        s->m_f6 = (u8)(si[0x14] - 1);
    }
    s->m_e8 = 0xf;
    return s;

cleanup:
    if (s->mpCmdBuffer != 0)
        alloc->Free(s->mpCmdBuffer, 0);
    if (s->mpVoiceNodes != 0)
        alloc->Free(s->mpVoiceNodes, 0);

    {
        TimerManager* t = (TimerManager*)((char*)s + 0x98);
        for (int i = 1; i >= 0; --i)
        {
            t = (TimerManager*)((char*)t - 0x1c);
            t->dtor();
        }
    }
    alloc->Free(s, 0);
    return 0;
}

// @ 0x0112cc10
u8* audio_createObject(u8* obj, u32 a2, Factory* factory, const InitData* init, u8 flag)
{
    *(u32*)(obj + 8) = a2;
    *(float*)(obj + 0x14) = 0.0f;
    *(float*)(obj + 0x18) = 0.0f;
    *(u32*)(obj + 0x1c) = 0;
    *(u32*)(obj + 0x10) = (u32)factory;
    *(u32*)(obj + 4) = (u32)g_audioSystem;
    obj[0x20] = flag;
    obj[0x21] = init->m_a8;

    bool ok = factory->mpCreate(obj, *(u32*)init);
    if (!ok)
    {
        ((BaseObject*)obj)->dtor();
        ((BaseObject*)obj)->release(0);
        return 0;
    }
    return obj;
}

// @ 0x0112cc80
void AttributeSet::getFloat(int i, float* out)
{
    *out = *(float*)((char*)m_array + i * 8);
}

// @ 0x0112cca0
void AttributeSet::getDouble(int i, double* out)
{
    *out = *(double*)((char*)m_array + i * 8);
}

// @ 0x0112ccd0
u32 RtCommandHandler::execute(CompiledCmd* cmd)
{
    char* base = *(char**)((char*)cmd->mpThis + 0xc);
    *(float*)(base + cmd->m_a8 * 8) = cmd->m_fc;
    return 0x10;
}

// @ 0x0112ccf0
void AudioObject::IsCommandComplete(u32 a, float f)
{
    System* s = mpSystem;
    CompiledCmd* c = (CompiledCmd*)((char*)s->mpCmdBuffer + s->m_b4);
    s->m_b4 += 0x10;
    c->mpFn = (int (__cdecl*)(void*))&RtCommandHandler::execute;
    c->mpThis = this;
    c->m_a8 = a;
    c->m_fc = f;
}

// @ 0x0112cd30
Node* NodeList::find(u32 id)
{
    Node* n = m_head;
    while (n != 0)
    {
        Node* base = (Node*)((char*)n - 0x24);
        Node* next = n->pnext;
        if (n->m_id == id)
            return base;
        n = next;
    }
    return 0;
}

// @ 0x0112cd60
Node* NodeList::insert(Node* e)
{
    u32 id = *(u32*)((char*)e + 0x28);
    for (Node* n = m_head; n != 0; n = n->pnext)
    {
        if (n->m_id == id)
            return (Node*)((char*)n - 0x24);
    }

    Node* node = (Node*)((char*)e + 0x24);
    node->pnext = m_head;
    if (m_tail == 0)
        m_tail = node;
    ++m_count;
    m_head = node;
    *(u8*)((char*)e + 0x32) = m_tag;
    ++m_tag;
    return e;
}

// @ 0x0112cdb0
__declspec(noinline) u32* audio_allocNode(System* sys)
{
    u32* p = (u32*)sys->Alloc(0x18, 0, 0x10, 0);
    if (p != 0)
    {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        *(u8*)(p + 5) = 0;
        p[4] = (u32)sys;
        return p;
    }
    return 0;
}

// @ 0x0112cdf0
void AllocNode::freeSelf()
{
    System* s = (System*)*(void**)((char*)this + 0x10);
    s->Free(this, 0);
}

// @ 0x0112ce00
void* VoiceList::getOrCreate()
{
    if (m_a28 == 0)
        m_a28 = audio_allocNode(g_audioSystem);
    return m_a28;
}
