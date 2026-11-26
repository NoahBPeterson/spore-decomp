// src/game/UTFSpore_Win32/RelativeNavigator.cpp -- migrated from slice(s) s00980760 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/RelativeNavigator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IScrollbarDrawable.h"
#include "EA/UTFWinControls/IWinScrollbar.h"
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s00980760 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(T, obj, off) ((T)(*(void***)(obj))[(off) / 4])
void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)
void __fastcall Navigator_baseCtor(void* p);                           // 00980430
namespace EA {
namespace UTFWinControls {
extern void* vt_1444238[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444220[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1442188[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1442170[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_async_13fa72c[];
}
}
namespace EA {
namespace UTFWinControls {
extern int g_1440aec;   // 0x01440AEC
}
}
namespace EA {
namespace UTFWinControls {
typedef void* (__thiscall *Nav_ItFn)(void*, int);       // vt[0x48]
}
}
namespace EA {
namespace UTFWinControls {
typedef void* (__thiscall *Nav_GetFn)(void*);           // vt[0x10]
}
}
namespace EA {
namespace UTFWinControls {
typedef void** (__thiscall *Nav_IterFn)(void*, void*);  // vt[0xcc]/vt[0xd0]
}
}
namespace EA {
namespace UTFWinControls {
typedef void  (__thiscall *Nav_SetIterFn)(void*, void*, void*);  // vt[0xd4]
}
}
namespace EA {
namespace UTFWinControls {
typedef int   (__thiscall *Nav_FlagFn)(void*);          // vt[0x28]
}
}
namespace EA {
namespace UTFWinControls {
typedef void  (__thiscall *Nav_VisitFn)(void*, int, void*);      // vt[0x4c]
}
}
namespace EA {
namespace UTFWinControls {
class Navigator { public:
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    int   f10;                                                         // +0x10
    int   f14;                                                         // +0x14
    int   f18;                                                         // +0x18
    int   mode;                                                        // +0x1c
    bool Navigate(void* mgr, int cmd);                                 // 00980760
};
}
}
namespace EA {
namespace UTFWinControls {
class BasicFactory_RelativeNavigator { public:
    Navigator* CreateInstance(int unused, void* alloc);                // 00980b70
};
}
}
// ---- items of slice s00980760 end

// @ 0x00980760
bool EA::UTFWinControls::Navigator::Navigate(void* mgr, int cmd)
{
    void* it = VSLOT(EA::UTFWinControls::Nav_ItFn, mgr, 0x48)(mgr, cmd);
    if (!it) return false;

    void* found;
    switch (mode) {
    case 0: case 1: case 2: case 3: {
        void* list = VSLOT(EA::UTFWinControls::Nav_GetFn, it, 0x10)(it);
        if (!list) return false;

        // vt[0xcc]/vt[0xd0] are begin()/end(): they build an iterator in the
        // caller's slot and return a pointer to it; *ret is the node.
        void* ib0;
        void* ib1;
        void** pend = VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ib0);
        void** pbeg = VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xcc)(list, &ib1);
        if (*pend == *pbeg) return false;

        void* start;
        VSLOT(EA::UTFWinControls::Nav_SetIterFn, list, 0xd4)(list, &start, it);

        void* ib2;
        if (start == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ib2)) return false;

        switch (mode) {
        case 0: {
            void* ib;
            if (start == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xcc)(list, &ib)) return false;
            for (;;) {
                void* node = *(void**)((char*)start + 4);
                start = node;
                void* obj = (char*)node + EA::UTFWinControls::g_1440aec;
                if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
                void* ib3;
                if (start == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xcc)(list, &ib3)) return false;
            }
            break;
        }
        case 1: {
            void* cur = *(void**)start;
            start = cur;
            void* ib;
            if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ib)) return false;
            for (;;) {
                void* obj = (char*)cur + EA::UTFWinControls::g_1440aec;
                if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
                cur = *(void**)cur;
                start = cur;
                void* ib2b;
                if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ib2b)) return false;
            }
            break;
        }
        case 2: {
            void* cur = start;
            for (;;) {
                void* ib;
                if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xcc)(list, &ib)) {
                    void* ie;
                    cur = *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ie);
                }
                void* node = *(void**)((char*)cur + 4);
                cur = node;
                if (cur == start) return false;
                void* obj = (char*)node + EA::UTFWinControls::g_1440aec;
                if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
            }
            break;
        }
        case 3: {
            void* cur = start;
            for (;;) {
                cur = *(void**)cur;
                void* ie;
                if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xd0)(list, &ie)) {
                    void* ib;
                    cur = *VSLOT(EA::UTFWinControls::Nav_IterFn, list, 0xcc)(list, &ib);
                }
                if (cur == start) return false;
                void* obj = (char*)cur + EA::UTFWinControls::g_1440aec;
                if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
            }
            break;
        }
        }
        break;
    }
    case 4: {
        void* cur;
        void* ib;
        VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xcc)(it, &cur);
        if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xd0)(it, &ib)) return false;
        for (;;) {
            void* obj = (char*)cur + EA::UTFWinControls::g_1440aec;
            if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
            cur = *(void**)cur;
            void* ie;
            if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xd0)(it, &ie)) return false;
        }
        break;
    }
    case 5: {
        void* cur;
        void* ib;
        VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xd0)(it, &cur);
        if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xcc)(it, &ib)) return false;
        for (;;) {
            void* node = *(void**)((char*)cur + 4);
            cur = node;
            void* obj = (char*)node + EA::UTFWinControls::g_1440aec;
            if (VSLOT(EA::UTFWinControls::Nav_FlagFn, obj, 0x28)(obj) & 2) { found = obj; break; }
            void* ib2;
            if (cur == *VSLOT(EA::UTFWinControls::Nav_IterFn, it, 0xcc)(it, &ib2)) return false;
        }
        break;
    }
    case 6: {
        found = VSLOT(EA::UTFWinControls::Nav_GetFn, it, 0x10)(it);
        break;
    }
    default:
        return true;
    }
    if (found) VSLOT(EA::UTFWinControls::Nav_VisitFn, mgr, 0x4c)(mgr, cmd, found);
    return true;
}

// @ 0x00980b70
EA::UTFWinControls::Navigator* EA::UTFWinControls::BasicFactory_RelativeNavigator::CreateInstance(int unused, void* alloc)
{
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x20, 4, "UTFWin/EA::UTFWinControls::RelativeNavigator", alloc);
    if (mem != 0) {
        Navigator_baseCtor(mem);
        ((void**)mem)[6] = EA::UTFWinControls::vt_async_13fa72c;
        void*& memRef = mem;
        ((void**)memRef)[0] = EA::UTFWinControls::vt_1444238;
        ((void**)memRef)[1] = EA::UTFWinControls::vt_1444220;
        ((void**)memRef)[3] = EA::UTFWinControls::vt_1442188;
        ((void**)memRef)[6] = EA::UTFWinControls::vt_1442170;
        ((void**)memRef)[7] = (void*)1;
        return (EA::UTFWinControls::Navigator*)memRef;
    }
    return 0;
}
