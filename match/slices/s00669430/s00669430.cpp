// Slice s00669430: SP::cSPUIFeedListItem::ReloadCallback and the constraint-lookup callback.
// Both are large and are represented here only in outline (see partial.txt).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_ObjectTemplateDB();               // 0x0067cb40
void* __cdecl SP_MessageServer();                  // 0x0067dcc0
void* __cdecl cSPUILayout_FindWindow(void* self, unsigned id, int flag);
void  __cdecl FUN_00644a80(void* a, void* b, void* c, int d);
void  __cdecl FUN_006066f0(void* a);               // Constraint dtor
bool  __cdecl FUN_00664550(int v);
void  __cdecl FUN_00829d30_stub(void* p);

struct Component {
    virtual void c0();
    virtual int  Release();       // +0x04
    virtual void c2();
    virtual void c3();
};

// -----------------------------------------------------------------------------
// @ 0x00669430  SP::cSPUIFeedListItem::ReloadCallback
// -----------------------------------------------------------------------------
void __cdecl FUN_00669430(void* self, int a2, int a3) {
    (void)a2;
    if (!a3) {
        void* w = *(void**)((char*)self + 0xa0);
        if (w) ((FnVoid)VT(w)[0x42])(w);
        void* p = *(void**)((char*)self + 0x184);
        if (p) {
            FUN_00829d30_stub(p);
            if (*(void**)((char*)self + 0x184)) {
                *(uint32_t*)((char*)self + 0x184) = 0;
                ((FnVoid)VT(p)[2])(p);
            }
        }
        return;
    }
    // Skeleton: the real body rebuilds the whole feed list (window refcount swaps,
    // layout FindWindow, per-item GetAssetList/Refresh and an EA::Messaging post).
    void* layout = *(void**)((char*)self + 0x94);
    if (layout) cSPUILayout_FindWindow(layout, 0xf3c6dc19, 1);
}

void __cdecl FUN_00829d30_stub(void* p) { ((FnVoid)VT(p)[0])(p); }

// -----------------------------------------------------------------------------
// @ 0x00669c90  constraint-lookup callback (IWinProc DoMessage override)
// -----------------------------------------------------------------------------
bool __fastcall FUN_00669c90(void* self, int a1, unsigned* a2) {
    void* item = (char*)self - 4;
    if (!*(uint8_t*)((char*)self + 0x10)) return false;
    if (!*(void**)((char*)item + 0x90)) return false;
    if (!FUN_00664550(1)) return false;
    if (*(int*)((char*)self + 0x174) != 0x11f44f6b) return false;
    if (a1 != 0x064e5bda && a1 != (int)0x9421c619) return false;
    (void)a2;
    // Skeleton: the real body dispatches on the feed-type/query hashes, builds
    // SP::FunctionalMatch::Constraint objects and probes SP::ObjectTemplateDB.
    return false;
}
