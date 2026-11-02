// src/game/UTFSpore_Win32/WatchGraph.cpp -- migrated from slice(s) s00992480 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/WatchGraph.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00992480 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
static inline u32  ld32(char* b, u32 off) { return *(u32*)(b + off); }
static inline void st32(char* b, u32 off, u32 v) { *(u32*)(b + off) = v; }
void  IntrusiveList_dtor(char* list);                                // 0x00620230
void  Obj962740_f(char* p);                                          // 0x00962740  base dtor
void  MultiHeapObject_delete(void* p);                               // 0x00951330
void  FUN_00991f90(char* p);                                         // WatchGraph::Clear
// ---- items of slice s00992480 end

// @ 0x00992480
u8 __fastcall WatchGraph_OnTick(char* self, int)
{
    // Rings the history buffer: for each live history node, sample the graph value into the ring
    // at index mRingIndex (self+0x224), then advance the ring and repaint.
    char* head = (char*)ld32(self, 0x20c);
    char* node = head ? head - 4 : 0;
    char* end  = (self + 0x20c) ? self + 0x20c - 4 : 0;
    while (node != end) {
        if (ld32(node, 0x14) != 0) {
            float v = (*(float(__fastcall**)(char*))(*(u32*)node + 4))(node);
            float* dest = (float*)ld32(node, 0x14);
            dest[ld32(self, 0x224)] = v;
        }
        char* next = (char*)ld32(node, 4);
        node = next ? next - 4 : 0;
    }
    u32 idx = ld32(self, 0x224) + 1;
    st32(self, 0x224, idx);
    if (idx >= ld32(self, 0x220)) st32(self, 0x224, 0);
    (*(void(__fastcall**)(char*))(*(u32*)(self + 4) + 0x90))(self + 4);
    return 1;
}

// @ 0x00992550
void* __fastcall WatchGraph_scalarDtor(char* self, int, u8 flags)
{
    st32(self, 0, 0x1446078u);            // vtbl WatchGraph
    st32(self, 4, 0x1445f58u);
    FUN_00991f90(self);
    IntrusiveList_dtor(self + 0x20c);
    Obj962740_f(self);
    if (flags & 1) MultiHeapObject_delete(self);
    return self;
}
