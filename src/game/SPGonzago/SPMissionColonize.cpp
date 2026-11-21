// src/game/SPGonzago/SPMissionColonize.cpp -- migrated from slice(s) s00c4dbf0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionColonize.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl FUN_0041e920();
extern "C" int   __cdecl FUN_0041ea00();
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
