// src/game/mix/smixfilt.cpp.cpp -- migrated from slice(s) s01159630, s01156960 by tools/migrate/rewrite.py
// Object file: mix/smixfilt.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/audio/core/System.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char g_mixvoices;      // 0x016e8174
extern "C" char g_strUserFilter[];// 0x014ce834

// ---- items of slice s01156960 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef unsigned int   u32;
struct System {
    void* Alloc(int size, const char* name, int align, int flags);  // 0x112c820
    void  Free(void* p, int flags);                                 // 0x112c850
};
extern "C" System* g_system;      // 0x016e61a8
extern "C" char g_mixvoices;      // 0x016e8174
extern "C" char g_strUserFilter[];// 0x014ce834
void  FUN_011596d0(void* dst, void* src);                       // 0x11596d0
// ---- items of slice s01156960 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" System* g_system;      // 0x016e61a8

// ---- items of slice s01159630 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace audio {
namespace core {
struct MpegListNode {
    char          pad00[8];
    MpegListNode* child;        // +0x08
    char          pad0c[4];
    MpegListNode* parent;       // +0x10
    char          pad14[4];
    uint16_t      key;          // +0x18
    char          pad1a[2];
};
}
}
}
// ---- items of slice s01159630 end

// @ 0x01156b40
extern "C" void MIX_filteradd(int voice, int unused, int* desc)
{
    char* v = (char*)&g_mixvoices + voice * 0x5c;
    char* st = (char*)g_system->Alloc(desc[1], g_strUserFilter, 0x10, 0);
    ((void (__cdecl*)(void*, int, int))desc[3])(st, desc[0], unused);
    *(u16*)(st + 0x18) = *(u16*)((char*)desc + 8);
    *(u32*)st = desc[4];
    *(u32*)(st + 4) = desc[5];
    st[0x1a] = 0;
    FUN_011596d0(v + 0x40, st);
}

// @ 0x011596d0
namespace rw { namespace audio { namespace core {
void MpegList_Insert(void** head, MpegListNode* node)
{
    MpegListNode* cur = (MpegListNode*)*head;
    MpegListNode* prev = 0;
    while (cur != 0 && cur->key < node->key) {
        prev = cur;
        cur = cur->child;
    }
    node->child = cur;
    if (cur != 0)
        cur->parent = node;
    if (prev == 0)
        *head = node;
    else {
        prev->child = node;
        node->parent = prev;
    }
}
}}}  // namespace rw::audio::core
