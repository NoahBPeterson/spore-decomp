// src/game/SPGonzago/_at_00cd0000.cpp -- migrated from slice(s) s00ccfc20 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00cd0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __cdecl rt_del_array(void*);                                       // 0xf47380

// ---- items of slice s00ccfc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void*  FUN_00b3d280();                         // 0x00b3d280  GetCameraCtl
void*  FUN_00b3d300();                         // 0x00b3d300  SP::NounManager
void*  FUN_00cd40b0();                         // 0x00cd40b0  cTribeModeStrategy::Instance
void   FUN_00b11870(void*, uint32_t);          // 0x00b11870
extern "C" void  __cdecl rt_del_array(void*);                                       // 0xf47380
void*  FUN_00bfc5f0(void*);                                 // 0x00bfc5f0 (thiscall)
void   FUN_00af1450(void*);                                 // 0x00af1450 (thiscall, 0 args)
void   FUN_00579a90(void*, const wchar_t*);                 // 0x00579a90 (thiscall, 1 arg)
struct CInput {
    void F_ccfc20(void* arg);                            // 0x00ccfc20
    void F_ccfcf0(void* vec, int key, void* a, void* b); // 0x00ccfcf0
    void F_cd07c0(void* a, void* b, void* c);            // 0x00cd07c0
    int  F_cd0830(void* arg);                            // 0x00cd0830
    void F_cd0950();                                     // 0x00cd0950
    void F_cd02d0(void* pos);                            // 0x00cd02d0
    int  F_cd0660(void* flags, void* pos, void* c);      // 0x00cd0660
};
// ---- items of slice s00ccfc20 end

// @ 0x00cd0950
void CInput::F_cd0950()
{
    const wchar_t* str[3];
    if (*(int*)((char*)this + 0xc8) == 1) {
        *(int*)((char*)this + 0xc8) = 0;
        ((void*(__thiscall*)(void*)) FUN_00bfc5f0)(FUN_00b3d300());
        void* cam = FUN_00b3d280();
        if (cam != 0)
            ((void(__thiscall*)(void*, uint32_t)) FUN_00b11870)(cam, 0xcf0a771b);
        void* inst = FUN_00cd40b0();
        str[0] = 0;
        str[1] = 0;
        str[2] = 0;
        ((void(__thiscall*)(void*, const wchar_t*)) FUN_00579a90)((void*)str, L"Free Camera OFF");
        ((void(__thiscall*)(void*)) FUN_00af1450)(((void*(__thiscall*)(void*, void*)) (*(void***)inst)[0x6c / 4])(inst, (void*)str));
        if ((((char*)str[1] - (char*)str[0]) & ~1) > 2 && str[0] != 0)
            rt_del_array((void*)str[0]);
        return;
    }

    *(int*)((char*)this + 0xc8) = 1;
    void* inst = FUN_00cd40b0();
    str[0] = 0;
    str[1] = 0;
    str[2] = 0;
    ((void(__thiscall*)(void*, const wchar_t*)) FUN_00579a90)((void*)str, L"Free Camera ON");
    ((void(__thiscall*)(void*)) FUN_00af1450)(((void*(__thiscall*)(void*, void*)) (*(void***)inst)[0x6c / 4])(inst, (void*)str));
    if ((((char*)str[1] - (char*)str[0]) & ~1) > 2 && str[0] != 0)
        rt_del_array((void*)str[0]);
    if (FUN_00b3d280() != 0)
        ((void(__thiscall*)(void*, uint32_t)) FUN_00b11870)(FUN_00b3d280(), 0xcf14603b);
}
