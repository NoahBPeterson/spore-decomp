// src/game/SPMovie/videorenderablemanager.cpp -- migrated from slice(s) s00fce1e0, s00fcd210 by tools/migrate/rewrite.py
// Object file: SPMovie/videorenderablemanager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include <new>
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void EA_Thread_Mutex_dtor(void*);   // 0x922130
extern const char g_mutexName[];                        // 0x149219c

// ---- items of slice s00fcd210 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EA_Thread_Mutex_dtor(void*);   // 0x922130
struct EAThreadMutex {
    void  Lock(const char* name);
    void  Unlock();
};
struct RVRenderable {
    void ShutdownAll();
    void SetFrame0(int p2);
    int  GetFrame0();
    void SetFrame1(int p2);
    int  GetFrame1(int p2);
    int  GetFrame2();
};
extern const char g_mutexName[];                        // 0x149219c
// ---- items of slice s00fcd210 end

// ---- items of slice s00fce1e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_listLockToken[];
extern const void* g_videoRenderableComparatorVtbl[];
typedef unsigned int  u32;
namespace EA {
namespace Thread {
class Mutex_s00fc_e1e0 {
public:
    Mutex_s00fc_e1e0(const void* pParameters = 0, bool bDefaultParameters = true);  // 0x009222A0
    ~Mutex_s00fc_e1e0();                                                            // 0x00922130
    int Lock(const void* pTimeoutAbsolute);                              // 0x009221B0
    int Unlock();                                                        // 0x00922270
    u32 mData[0x30 / 4];
};
}
}
struct ICoreAllocator {
    virtual void* s00();                                           // +0x00
    virtual void* Alloc(u32 size, const char* name, int a, int b, int c);  // +0x04 (ret 0x14)
    virtual void  Free(void* p, int a);                            // +0x08
};
namespace rw {
 class SList {
public:
    virtual void  SetAllocator(ICoreAllocator* alloc);       // +0x00
    virtual void  s04();                                     // +0x04
    virtual void  Init(u32 elementSize);                     // +0x08
    virtual void  s0c();                                     // +0x0c
    virtual void  s10();                                     // +0x10
    virtual void  s14();                                     // +0x14
    virtual void  s18();                                     // +0x18
    virtual void  s1c();                                     // +0x1c
    virtual void  s20();                                     // +0x20
    virtual void  s24();                                     // +0x24
    virtual void* GetHead();                                 // +0x28
    virtual void  s2c();                                     // +0x2c
    virtual void* At(u32 i);                                 // +0x30
    virtual void  s34();                                     // +0x34
    virtual void  s38();                                     // +0x38
    virtual u32   Count();                                   // +0x3c
    virtual void  s40();                                     // +0x40
    virtual void  PushBack(void* node, int a);               // +0x44
    virtual void  s48();                                     // +0x48
    virtual void  s4c();                                     // +0x4c
    virtual void  s50();                                     // +0x50
    virtual void  s54();                                     // +0x54
    virtual void  s58();                                     // +0x58
    virtual void  s5c();                                     // +0x5c
    virtual void  s60();                                     // +0x60
    virtual void  s64();                                     // +0x64
    virtual void  s68();                                     // +0x68
    virtual void  s6c();                                     // +0x6c
    virtual void  s70();                                     // +0x70
    virtual void  Remove(void* node, int a);                 // +0x74
    SList();                                                 // 0x00FCCE10
}; 
}
struct VideoRenderable {
    virtual u32* GetFrame();                                 // +0x00
};
struct Comparator {
    void* vftable;                                           // +0x00
};
struct VideoRenderableManager {
    ICoreAllocator* mAllocator;        // +0x00
    rw::SList*      mEmptyList;        // +0x04
    rw::SList*      mFilledList;       // +0x08
    rw::SList*      mSentToDecoderList;  // +0x0c
    rw::SList*      mSentToRendererList; // +0x10
    u32             mPad14;            // +0x14
    EA::Thread::Mutex_s00fc_e1e0 mListMutex;      // +0x18
    Comparator      mComparator;       // +0x48

    VideoRenderableManager(ICoreAllocator* alloc);           // 0x00FCE560
    void  AddToRendererList(void* renderable);               // 0x00FCE1E0
    u32   GetRendererListSize();                             // 0x00FCE220
    void  AddToDecoderList(void* renderable);                // 0x00FCE250
    u32   GetDecoderListSize();                              // 0x00FCE290
    u32   PopFromEmptyList();                                // 0x00FCE2C0
    u32   PeekFilledList();                                  // 0x00FCE320
    u32   PopFromFilledList();                               // 0x00FCE380
    u32   PopFromRendererList();                             // 0x00FCE3E0
    u32   GetFromDecoderList(u32 index);                     // 0x00FCE440
    u32   RemoveFromDecoderList(u32 index);                  // 0x00FCE4C0
};
// ---- items of slice s00fce1e0 end

// @ 0x00fcdfe0
extern "C" int __stdcall FUN_00fcdfe0(int* a, int* b)
{
    int vb = *(int*)(*b + 0x34);
    int va = *(int*)(*a + 0x34);
    if (va == vb)
        return 0;
    return (va > vb) ? 1 : -1;
}

// @ 0x00fce010
void RVRenderable::ShutdownAll()
{
    char* self = (char*)this;
    ((void (*)(void*))((void**)*(void**)(self + 0x0c))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x0c), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x10))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x10), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x08))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x08), 0);
    ((void (*)(void*))((void**)*(void**)(self + 0x04))[0x88 / 4])(0);
    ((void (*)(int, int))((void**)*(void**)(self + 0x00))[3])(*(int*)(self + 0x04), 0);
    *(int*)(self + 0x48) = 0x14613b8;
    EA_Thread_Mutex_dtor((void*)(self + 0x18));
}

// @ 0x00fce0a0
void RVRenderable::SetFrame0(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int local = p2;
    ((void (*)(int*, int))((void**)*(void**)((char*)this + 0x04))[0x44 / 4])(&local, 0);
    mtx->Unlock();
}

// @ 0x00fce0e0
int RVRenderable::GetFrame0()
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int r = ((int (*)(void))((void**)*(void**)((char*)this + 0x04))[0x3c / 4])();
    mtx->Unlock();
    return r;
}

// @ 0x00fce110
void RVRenderable::SetFrame1(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int local = p2;
    ((void (*)(int*, char*, int))((void**)*(void**)((char*)this + 0x08))[0x68 / 4])(&local, (char*)this + 0x48, 0);
    mtx->Unlock();
}

// @ 0x00fce150
int RVRenderable::GetFrame1(int p2)
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    unsigned int n = ((unsigned int (*)(void))((void**)*(void**)((char*)this + 0x08))[0x3c / 4])();
    if (n <= (unsigned int)p2) {
        mtx->Unlock();
        return 0;
    }
    void* p = (void*)((void* (*)(int))((void**)*(void**)((char*)this + 0x08))[0x30 / 4])(p2);
    int* q = (int*)((int (*)(void*))((void**)p)[0])(p);
    int r = *q;
    mtx->Unlock();
    return r;
}

// @ 0x00fce1b0
int RVRenderable::GetFrame2()
{
    EAThreadMutex* mtx = (EAThreadMutex*)((char*)this + 0x18);
    mtx->Lock(g_mutexName);
    int r = ((int (*)(void))((void**)*(void**)((char*)this + 0x08))[0x3c / 4])();
    mtx->Unlock();
    return r;
}

// @ 0x00fce1e0
void VideoRenderableManager::AddToRendererList(void* renderable)
{
    mListMutex.Lock(g_listLockToken);
    int local = (int)renderable;
    mSentToRendererList->PushBack(&local, 0);
    mListMutex.Unlock();
}

// @ 0x00fce220
u32 VideoRenderableManager::GetRendererListSize()
{
    mListMutex.Lock(g_listLockToken);
    u32 n = mSentToRendererList->Count();
    mListMutex.Unlock();
    return n;
}

// @ 0x00fce250
void VideoRenderableManager::AddToDecoderList(void* renderable)
{
    mListMutex.Lock(g_listLockToken);
    int local = (int)renderable;
    mSentToDecoderList->PushBack(&local, 0);
    mListMutex.Unlock();
}

// @ 0x00fce290
u32 VideoRenderableManager::GetDecoderListSize()
{
    mListMutex.Lock(g_listLockToken);
    u32 n = mSentToDecoderList->Count();
    mListMutex.Unlock();
    return n;
}

// @ 0x00fce2c0
u32 VideoRenderableManager::PopFromEmptyList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mEmptyList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mEmptyList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce320
u32 VideoRenderableManager::PeekFilledList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mFilledList;
    VideoRenderable* item = 0;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    if (item != 0) {
        u32 frame = item->GetFrame()[0];
        mListMutex.Unlock();
        return frame;
    }
    mListMutex.Unlock();
    return 0;
}

// @ 0x00fce380
u32 VideoRenderableManager::PopFromFilledList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mFilledList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mFilledList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce3e0
u32 VideoRenderableManager::PopFromRendererList()
{
    mListMutex.Lock(g_listLockToken);
    rw::SList* list = mSentToRendererList;
    VideoRenderable* item;
    if (list->Count() != 0)
        item = (VideoRenderable*)list->GetHead();
    else
        item = 0;
    u32 frame = 0;
    if (item != 0) {
        frame = item->GetFrame()[0];
        mSentToRendererList->Remove(item, 0);
    }
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce440
u32 VideoRenderableManager::GetFromDecoderList(u32 index)
{
    mListMutex.Lock(g_listLockToken);
    VideoRenderable* item;
    if (index == 0) {
        if (mSentToDecoderList->Count() == 0)
            goto fail;
        item = (VideoRenderable*)mSentToDecoderList->GetHead();
    } else {
        if (mSentToDecoderList->Count() < index)
            goto fail;
        item = (VideoRenderable*)mSentToDecoderList->At(index);
    }
    if (item == 0)
        goto fail;
    {
        u32 frame = item->GetFrame()[0];
        mSentToDecoderList->Remove(item, 0);
        mListMutex.Unlock();
        return frame;
    }
fail:
    mListMutex.Unlock();
    return 0;
}

// @ 0x00fce4c0
u32 VideoRenderableManager::RemoveFromDecoderList(u32 index)
{
    mListMutex.Lock(g_listLockToken);
    VideoRenderable* item;
    u32 frame = 0;
    if (index == 0) {
        if (mSentToDecoderList->Count() == 0)
            goto done;
        item = (VideoRenderable*)mSentToDecoderList->GetHead();
        if (item == 0)
            goto done;
    } else {
        if (mSentToDecoderList->Count() < index)
            goto done;
        item = (VideoRenderable*)mSentToDecoderList->At(index);
        if (item == 0)
            goto done;
    }
    frame = item->GetFrame()[0];
    mSentToDecoderList->Remove(item, 0);
done:
    mListMutex.Unlock();
    return frame;
}

// @ 0x00fce560
VideoRenderableManager::VideoRenderableManager(ICoreAllocator* alloc)
{
    mComparator.vftable = (void*)g_videoRenderableComparatorVtbl;
    mAllocator = alloc;
    mEmptyList = (rw::SList*)mAllocator->Alloc(0x1c, "Empty List", 0, 4, 0);
    if (mEmptyList != 0)
        mEmptyList = new (mEmptyList) rw::SList;
    mEmptyList->Init(4);
    mEmptyList->SetAllocator(mAllocator);
    mFilledList = (rw::SList*)mAllocator->Alloc(0x1c, "Filled List", 0, 4, 0);
    if (mFilledList != 0)
        mFilledList = new (mFilledList) rw::SList;
    mFilledList->Init(4);
    mFilledList->SetAllocator(mAllocator);
    mSentToRendererList =
        (rw::SList*)mAllocator->Alloc(0x1c, "Sent To Renderer List", 0, 4, 0);
    if (mSentToRendererList != 0)
        mSentToRendererList = new (mSentToRendererList) rw::SList;
    mSentToRendererList->Init(4);
    mSentToRendererList->SetAllocator(mAllocator);
    mSentToDecoderList =
        (rw::SList*)mAllocator->Alloc(0x1c, "Sent To Decoder List", 0, 4, 0);
    if (mSentToDecoderList != 0)
        mSentToDecoderList = new (mSentToDecoderList) rw::SList;
    mSentToDecoderList->Init(4);
    mSentToDecoderList->SetAllocator(mAllocator);
}
