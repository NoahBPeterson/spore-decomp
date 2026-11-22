// src/game/SPGonzago/_at_00cd0000.cpp -- migrated from slice(s) s00cd18a0, s00ccfc20 by tools/migrate/rewrite.py
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

// ---- items of slice s00cd18a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj_s00cd_18a0 {
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr_s00cd_18a0 {
    IRefObj_s00cd_18a0* mp;

    ~RefPtr_s00cd_18a0() { if (mp) mp->Release(); }
};
struct IHandle_s00cd_18a0 {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void Release();  // slot 0x0c
};
struct HandlePtr_s00cd_18a0 {
    IHandle_s00cd_18a0* mp;

    ~HandlePtr_s00cd_18a0() { if (mp) mp->Release(); }
};
struct MapNode_s00cd_18a0;
struct MapA_s00cd_18a0 {
    int mCompare;
    MapNode_s00cd_18a0* mpNodeRight;
    MapNode_s00cd_18a0* mpNodeLeft;
    MapNode_s00cd_18a0* mpNodeParent;
    int mColor;
    int mnSize;
    int mAllocator;

    ~MapA_s00cd_18a0() { DoNukeSubtree(mpNodeParent); }
    void DoNukeSubtree(MapNode_s00cd_18a0* node);  // 0x00b1b830
};
struct MapB_s00cd_18a0 {
    int mCompare;
    MapNode_s00cd_18a0* mpNodeRight;
    MapNode_s00cd_18a0* mpNodeLeft;
    MapNode_s00cd_18a0* mpNodeParent;
    int mColor;
    int mnSize;
    int mAllocator;

    ~MapB_s00cd_18a0() { DoNukeSubtree(mpNodeParent); }
    void DoNukeSubtree(MapNode_s00cd_18a0* node);  // 0x00e4b990
};
void FreeBlock_s00cd_18a0(void* p, int a, int b, int c, int d);  // 0x00571db0
struct Block_s00cd_18a0 {
    void* mpData;  // +0x00
    int mA, mB, mC, mD;

    ~Block_s00cd_18a0()
    {
        if (mpData) {
            void* p = mpData;
            mpData = 0;
            FreeBlock_s00cd_18a0(p, mA, mB, mC, mD);
        }
    }
};
struct MapPair_s00cd_18a0 {
    MapA_s00cd_18a0 mFirst;   // +0x00
    MapB_s00cd_18a0 mSecond;  // +0x1c
};
struct BaseA_s00cd_18a0 {
    MapPair_s00cd_18a0 mMaps;  // +0x04

    virtual ~BaseA_s00cd_18a0() {}
};
struct BaseB_s00cd_18a0 {
    virtual ~BaseB_s00cd_18a0() {}
};
struct Object_s00cd_18a0 : BaseA_s00cd_18a0, BaseB_s00cd_18a0 {
    char pad40[4];
    Block_s00cd_18a0 mBlock;           // +0x44
    char pad58[4];
    HandlePtr_s00cd_18a0 mpHandle;     // +0x5c
    MapPair_s00cd_18a0 mMaps2;         // +0x60
    RefPtr_s00cd_18a0 mpRef98;         // +0x98
    RefPtr_s00cd_18a0 mpRef9c;         // +0x9c
    char pada0[0xc0 - 0xa0];
    RefPtr_s00cd_18a0 mpRefc0;         // +0xc0

    virtual ~Object_s00cd_18a0();
};
// ---- items of slice s00cd18a0 end

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

// @ 0x00cd18a0
Object_s00cd_18a0::~Object_s00cd_18a0()
{
}
