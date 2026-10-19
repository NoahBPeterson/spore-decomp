// src/game/UTFSpore_Win32/Heaps.cpp -- migrated from slice(s) s009568c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Heaps.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/DisplayListEntry.h"
#include "EA/Thread/Mutex.h"

// unnamed retail callees and globals (address in the comment)
extern void*  g_pFreeRLChunk;        // 0x166b0f8
extern void*  g_pFreeDLHead;         // 0x154ed20
extern char   g_mutexHeaps[0x18];    // 0x166b100
extern const char g_scopeHeaps[];    // 0x1440548
#include <intrin.h>

// ---- items of slice s009568c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);        // 0xf473a0 (EA allocator, name/flags form)
void* __cdecl operator_new(unsigned int, const char*, int, int, const char*, int); // 0xf473a0 (EASTL allocator.h form)
void  __cdecl operator_delete__(void*) throw();                                    // 0xf47380
extern void*  g_pFreeRLChunk;        // 0x166b0f8
extern void*  g_pFreeDLHead;         // 0x154ed20
extern char   g_mutexHeaps[0x18];    // 0x166b100
extern const char g_scopeHeaps[];    // 0x1440548
struct Mutex {
    void Lock(const char*);   // 0x9221b0
    void Unlock();            // 0x922270
};
struct RLChunk { RLChunk* p0; void* p4; };
struct DLNode { DLNode* mpNext; DLNode* mpPrev; };
struct DisplayList : DLNode {
    char pad[0x10];
    int  f18;
    int  f1c;
    char rest[0xe0];
    DisplayList() { mpNext = 0; mpPrev = 0; }
};
extern DLNode g_freeDL;                  // 0x154ed20 (next), 0x154ed24 (prev)
void* __cdecl operator new(unsigned int, void* p) { return p; }
// ---- items of slice s009568c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern DLNode g_freeDL;                  // 0x154ed20 (next), 0x154ed24 (prev)

// @ 0x00956e30
void __cdecl FreeRenderableListChunks(RLChunk* p, RLChunk* q)
{
    if (p == 0) return;
    if (q == 0) {
        q = p;
        while (q->p0)
            q = q->p0;
    }
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    q->p0 = (RLChunk*)g_pFreeRLChunk;
    g_pFreeRLChunk = p;
    m->Unlock();
}

// @ 0x00956e90
void __cdecl FreeDisplayListEntry(int* e)
{
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    e[0] = (int)g_pFreeDLHead;
    e[1] = (int)&g_pFreeDLHead;
    g_pFreeDLHead = e;
    *(int**)(e[0] + 4) = e;
    m->Unlock();
}

// @ 0x00956ed0
RLChunk* __cdecl AllocRenderableListChunk()
{
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    RLChunk* p = (RLChunk*)g_pFreeRLChunk;
    if (p != 0)
        g_pFreeRLChunk = p->p0;
    m->Unlock();
    if (p == 0)
        p = (RLChunk*)operator_new(0x30, "UTFWin/RenderableListChunk", 0, 0, 0, 0);
    p->p4 = 0;
    p->p0 = 0;
    return p;
}

// @ 0x00956f30
void __cdecl FUN_00956f30()
{
    DLNode* pAnchor = &g_freeDL;
    while (g_freeDL.mpPrev != pAnchor) {
        DLNode* p = g_freeDL.mpNext;
        p->mpNext->mpPrev = pAnchor;
        g_freeDL.mpNext = g_freeDL.mpNext->mpNext;
        if (p != pAnchor) {
            p->mpPrev = 0;
            p->mpNext = 0;
        }
        operator_delete__(p);
    }
    RLChunk* pChunk = (RLChunk*)g_pFreeRLChunk;
    while (pChunk) {
        RLChunk* pNext = pChunk->p0;
        operator_delete__(pChunk);
        pChunk = pNext;
    }
    g_pFreeRLChunk = 0;
}

// @ 0x00956fa0
void __cdecl FreeDisplayListEntries(DLNode* pList)
{
    Mutex* m = (Mutex*)g_mutexHeaps;
    m->Lock(g_scopeHeaps);
    DLNode* pFirst = pList->mpNext;
    if (pFirst != pList) {
        DLNode* pPos = g_freeDL.mpNext;
        DLNode* pBefore = pPos->mpPrev;
        DLNode* pLast = pList->mpPrev;
        pBefore->mpNext = pFirst;
        pFirst->mpPrev = pBefore;
        pLast->mpNext = pPos;
        pPos->mpPrev = pLast;
        pList->mpNext = pList;
        pList->mpPrev = pList;
    }
    m->Unlock();
}

// @ 0x00956ff0
DisplayList* __cdecl AllocDisplayListEntry()
{
    Mutex* m = (Mutex*)g_mutexHeaps;
    DisplayList* p = 0;
    m->Lock(g_scopeHeaps);
    DLNode* pAnchor = &g_freeDL;
    if (g_freeDL.mpPrev != pAnchor) {
        p = (DisplayList*)g_freeDL.mpNext;
        p->mpNext->mpPrev = pAnchor;
        g_freeDL.mpNext = g_freeDL.mpNext->mpNext;
        if (p != pAnchor) {
            p->mpPrev = 0;
            p->mpNext = 0;
        }
    }
    m->Unlock();
    if (p == 0)
        p = new("UTFWin/DisplayList", 0, 0, 0, 0) DisplayList;
    p->f1c = 0;
    p->f18 = 0;
    return p;
}
