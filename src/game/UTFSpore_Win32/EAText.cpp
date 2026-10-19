// src/game/UTFSpore_Win32/EAText.cpp -- migrated from slice(s) s00884a20 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAText.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/MessageQueue.h"
#include "EA/Thread/Mutex.h"
#include "EA/Messaging/Server.h"

// unnamed retail callees and globals (address in the comment)
extern void* e_defaultalloc();                       // 0x925cb0 ICoreAllocator::GetDefaultAllocator
extern const char g_str_fontserver_name[];  // 0x1427984 "EAText/FontServer"
extern void* g_16514d8;         // 0x16514d8  gpFontServer
extern void* g_16514dc;         // 0x16514dc  gpFontServerAllocated
extern void* g_16514ec;         // 0x16514ec  _gpCoreAllocator_Text

// ---- items of slice s00884a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* e_defaultalloc();                       // 0x925cb0 ICoreAllocator::GetDefaultAllocator
extern const char g_str_fontserver_name[];  // 0x1427984 "EAText/FontServer"
struct Allocator {
    virtual void  v0();                                                     // vtable[0]
    virtual void* alloc(int size, const char* name, int flags, int align, int offset); // vtable[1]
};
struct FontServerObj {
    virtual void v0();                                                      // vtable[0]
    virtual void method();                                                  // vtable[1]
    FontServerObj* ctor(int);                                               // 0x88f0f0
};
extern void* g_16514d8;         // 0x16514d8  gpFontServer
extern void* g_16514dc;         // 0x16514dc  gpFontServerAllocated
extern void* g_16514ec;         // 0x16514ec  _gpCoreAllocator_Text
// ---- items of slice s00884a20 end

// @ 0x008859f0
int FUN_008859f0(const float* a, const float* b)
{
    if (a[0] != b[0]) return b[0] > a[0];
    if (a[1] != b[1]) return b[1] > a[1];
    if (a[2] != b[2]) return b[2] > a[2];
    return b[3] > a[3];
}

// @ 0x00885a60
void* EA_Text_GetFontServer(char create)
{
    if (g_16514d8 == 0 && create != 0) {
        if (g_16514dc == 0) {
            if (g_16514ec == 0) {
                g_16514ec = e_defaultalloc();
            }
            Allocator* a = (Allocator*)g_16514ec;
            FontServerObj* p = (FontServerObj*)a->alloc(0x2fd0, g_str_fontserver_name, 0, 8, 0);
            g_16514dc = (p != 0) ? p->ctor(0) : 0;
        }
        FontServerObj* fs = (FontServerObj*)g_16514dc;
        g_16514d8 = fs;
        fs->method();
    }
    return g_16514d8;
}
