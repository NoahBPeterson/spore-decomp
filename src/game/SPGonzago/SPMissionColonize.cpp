// src/game/SPGonzago/SPMissionColonize.cpp -- migrated from slice(s) s00c4dbf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionColonize.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl FUN_0041e920();
extern "C" int   __cdecl FUN_0041ea00();
extern "C" void  __cdecl FUN_00ba7bd0(void* p);
extern "C" void  __cdecl FUN_00ba8220(void* p);
extern "C" void  __cdecl FUN_00c4a0c0(void* self);
extern "C" int   __cdecl FUN_00c45b40x(void* self);
extern "C" void* __cdecl FUN_00c474b0x(void* self, int a);
extern "C" void* __cdecl FUN_00970b30x(void* self);
extern "C" void  __cdecl FUN_00c4ad50(void* self);
extern "C" void  __cdecl FUN_00c47180(void* self, void* a);
#pragma warning(disable : 4100)

// ---- items of slice s00c4dbf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
extern "C" int   __cdecl FUN_0041e920();
extern "C" int   __cdecl FUN_0041ea00();
// ---- items of slice s00c4dbf0 end

struct Prop_c4e390 {
    char pad[0x12];
    short mType;                               // +0x12
    u8*  FUN_0041e920();                       // Property::GetBool
    u32* FUN_0041ea00();                       // Property::GetUInt
};
struct IPropList_c4e390 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); 
    virtual bool GetProperty(u32 id, Prop_c4e390** out);
};
struct Mission_c4e390 {
    char pad[0x180];
    IPropList_c4e390* mpPropList;              // +0x180
    void FUN_00c4e390(u8* pb, u32* pu, u8* pflag);
};
// @ 0x00c4e390
void Mission_c4e390::FUN_00c4e390(u8* pb, u32* pu, u8* pflag)
{
    if (IPropList_c4e390* pl = mpPropList) {
        Prop_c4e390* prop;
        if (pl->GetProperty(0x36758b07u, &prop) && prop->mType == 1)
            *pb = *prop->FUN_0041e920();
    }
    if (IPropList_c4e390* pl = mpPropList) {
        Prop_c4e390* prop;
        if (pl->GetProperty(0x1f707861u, &prop) && prop->mType == 10)
            *pu = *prop->FUN_0041ea00();
    }
    if (IPropList_c4e390* pl = mpPropList) {
        Prop_c4e390* prop;
        if (pl->GetProperty(0xf924ebf9u, &prop) && prop->mType == 1)
            *pflag = *prop->FUN_0041e920();
    }
}

// @ 0x00c4e440
char __fastcall FUN_00c4e440(void* ecx_this, void* edx)
{
    char ok = (char)((int(__fastcall*)(void*, void*))FUN_00c4ad50)(ecx_this, 0);
    if (!ok)
        return 0;
    int localFlag = 0;
    ((Mission_c4e390*)ecx_this)->FUN_00c4e390((u8*)((char*)ecx_this + 0x1f4), (u32*)((char*)ecx_this + 0x1f5), (u8*)&localFlag);
    u32 type = (u32)FUN_00c45b40x(ecx_this);
    if (type != 0x2ca33dbdu) {
        void* rec = FUN_00c474b0x(ecx_this, (int)type);
        if (rec)
            FUN_00c47180(ecx_this, rec);
        if (FUN_00970b30x(ecx_this) == 0) {
            FUN_00ba7bd0((char*)ecx_this + 8);
            u32 flags = 0;
            switch (localFlag) {
            case 3: flags |= 0x20;
            case 2: flags |= 0x10;
            case 1: flags |= 8;
            case 0: flags |= 4;
            }
            int rec2[13];
            rec2[0] = (int)flags;
            rec2[1] = 2;
            rec2[2] = 2;
            if (*(u8*)((char*)ecx_this + 0x1f4))
                rec2[4] &= ~1;
            else
                rec2[4] = 1;
            int r = (*(int(__thiscall**)(void*, int*))(*(char**)ecx_this + 0x1a4))(ecx_this, rec2);
            if (r == 0) {
                FUN_00ba8220((char*)ecx_this + 8);
                return 0;
            }
            FUN_00c47180(ecx_this, (void*)r);
            FUN_00ba8220((char*)ecx_this + 8);
        }
    }
    char c = (*(char(__thiscall**)(void*))(*(char**)ecx_this + 0x128))(ecx_this);
    if (!c)
        return 0;
    FUN_00c4a0c0(ecx_this);
    (*(void(__thiscall**)(void*))(*(char**)ecx_this + 0x170))(ecx_this);
    return 1;
}
