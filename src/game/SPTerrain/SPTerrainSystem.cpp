// src/game/SPTerrain/SPTerrainSystem.cpp -- migrated from slice(s) s00fc10d0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDirectPropertyList.h"
#include <math.h>

// ---- items of slice s00fc10d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_ModelManager();
char  __cdecl FUN_0075e620_dummy();
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void __cdecl FUN_00fc5480();
void __cdecl FUN_00f4b690();

// Virtual-call shapes used by the model release below.
struct IModelMgr_s00fc1d0 { virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
                            virtual void  v10(); virtual void  v14(); virtual void  v18();
                            virtual void* v1C(int id); };                                 // slot 7 (+0x1c)
struct IModel_s00fc1d0 {   // RefObj: +0x154 is virtual slot 85
    virtual void v000(){}
    virtual void v004(){} virtual void v008(){} virtual void v00c(){} virtual void v010(){}
    virtual void v014(){} virtual void v018(){} virtual void v01c(){} virtual void v020(){}
    virtual void v024(){} virtual void v028(){} virtual void v02c(){} virtual void v030(){}
    virtual void v034(){} virtual void v038(){} virtual void v03c(){} virtual void v040(){}
    virtual void v044(){} virtual void v048(){} virtual void v04c(){} virtual void v050(){}
    virtual void v054(){} virtual void v058(){} virtual void v05c(){} virtual void v060(){}
    virtual void v064(){} virtual void v068(){} virtual void v06c(){} virtual void v070(){}
    virtual void v074(){} virtual void v078(){} virtual void v07c(){} virtual void v080(){}
    virtual void v084(){} virtual void v088(){} virtual void v08c(){} virtual void v090(){}
    virtual void v094(){} virtual void v098(){} virtual void v09c(){} virtual void v0a0(){}
    virtual void v0a4(){} virtual void v0a8(){} virtual void v0ac(){} virtual void v0b0(){}
    virtual void v0b4(){} virtual void v0b8(){} virtual void v0bc(){} virtual void v0c0(){}
    virtual void v0c4(){} virtual void v0c8(){} virtual void v0cc(){} virtual void v0d0(){}
    virtual void v0d4(){} virtual void v0d8(){} virtual void v0dc(){} virtual void v0e0(){}
    virtual void v0e4(){} virtual void v0e8(){} virtual void v0ec(){} virtual void v0f0(){}
    virtual void v0f4(){} virtual void v0f8(){} virtual void v0fc(){} virtual void v100(){}
    virtual void v104(){} virtual void v108(){} virtual void v10c(){} virtual void v110(){}
    virtual void v114(){} virtual void v118(){} virtual void v11c(){} virtual void v120(){}
    virtual void v124(){} virtual void v128(){} virtual void v12c(){} virtual void v130(){}
    virtual void v134(){} virtual void v138(){} virtual void v13c(){} virtual void v140(){}
    virtual void v144(){} virtual void v148(){} virtual void v14c(){} virtual void v150(){}
    virtual void v154(float v);                                       // slot 85 (+0x154)
};
// Interface of the terrain object at +0x18: slot 0 is the enable test, and slot 113 hands out
// the vertical offset the object gives the terrain model.
struct ITerrainModel_s00fc1d0 {
    virtual char IsEnabled();             // +0x00
    virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void v170(); virtual void v174(); virtual void v178(); virtual void v17c();
    virtual void v180(); virtual void v184(); virtual void v188(); virtual void v18c();
    virtual void v190(); virtual void v194(); virtual void v198(); virtual void v19c();
    virtual void v1a0(); virtual void v1a4(); virtual void v1a8(); virtual void v1ac();
    virtual void v1b0();
    virtual void v1b4();
    virtual float GetVerticalOffset();    // the model offset the terrain object carries
};
// The terrain object at +0x18 of cTerrainSystem: it carries its own vtable and the interface
// implementation its vtable pointer points at (which holds the model offset it hands out).
struct cTerrainObject_s00fc1d0 {
    void*  mVtable;                       // +0x00 object vtable
    ITerrainModel_s00fc1d0* mImpl;        // +0x04 the object's interface implementation
    int    mField08;                      // +0x08
    int    mField0c;                      // +0x0c
};
// SP::cTerrainSystem: offsets from its constructor 0x00fc1c00.
struct cTerrainSystem_s00fc1d0 {
    void*  mVtable0;                      // +0x00
    void*  mVtable1;                      // +0x04
    int    mField08;                      // +0x08
    void*  mObj0c;                        // +0x0c terrain editor
    void*  mObj10;                        // +0x10
    void*  mObj14;                        // +0x14
    cTerrainObject_s00fc1d0 mObject18;    // +0x18 the terrain object the model offset belongs to
    SP::cDirectPropertyList* mProps1c;    // +0x1c
    int    mTag20;                        // +0x20 property id of the description
};
// SP::cTerrainEditor::Enable(int unused) -- 0x00f67ff0
void __fastcall FUN_00f67ff0_dummy(void* self, int unused);
// ---- items of slice s00fc10d0 end

// @ 0x00fc19a0
int __cdecl FUN_00fc19a0(void)
{
    FUN_00f7be60();
    FUN_00f580f0();
    FUN_00f61a70();
    FUN_00f52b70(3, "coriolis");
    FUN_00f58230(3, (void*)FUN_00fc5480);
    FUN_00aa7fa0(6, (void*)FUN_00f4b690);
    return 1;
}

// @ 0x00fc1ba0
void __fastcall FUN_00fc1ba0(int self)
{
    cTerrainSystem_s00fc1d0* sys = (cTerrainSystem_s00fc1d0*)self;
    ITerrainModel_s00fc1d0* obj = sys->mObject18.mImpl;
    if (obj->IsEnabled()) {
        IModelMgr_s00fc1d0* mgr = (IModelMgr_s00fc1d0*)SP_ModelManager();
        IModel_s00fc1d0* model = (IModel_s00fc1d0*)mgr->v1C(0x3fbae24);
        float offset = obj->GetVerticalOffset();
        model->v154(offset);
    }
    if (sys->mObj0c)
        FUN_00f67ff0_dummy(sys->mObj0c, 0);
}

// @ 0x00fc1c70
int __fastcall FUN_00fc1c70(int self)
{
    (void)self;
    return 1;
}

// @ 0x00fc1e40
int __fastcall FUN_00fc1e40(int self)
{
    (void)self;
    return 1;
}
