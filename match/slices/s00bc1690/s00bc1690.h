// Declarations for slice s00bc1690 (SP tribe/city community update helpers, sound-slot
// table and eastl record-vector sort/merge helpers).
// Callees are external (relocated) in the original; retail symbols land elsewhere, so only
// the call shape (receiver in ecx for the thiscall ones) matters for matching.
#pragma once
#include "types.h"

// --- eastl record-vector helpers (0xc-byte records) ---
void  FUN_00af0d40(void* out);                                  // 0x00AF0D40
void  FUN_00bc0740(void* base, int a, int b, int c,
                   uint32_t v0, uint32_t v1, uint32_t v2);      // 0x00BC0740
void  FUN_00bc0840(void* a, void* b);                           // 0x00BC0840
void  FUN_00bc1940(void* a, void* b, int c);                    // 0x00BC1940
void  FUN_00bbfa30(void* a, void* b);                           // 0x00BBFA30
void  FUN_00bbfb10(void* a, void* b);                           // 0x00BBFB10
void  FUN_0103de50();                                           // 0x0103DE50 (Key accessor)
void  SpVector_DoInsertKey(void* a, void* b, void* c);          // 0x004E3E10

// A 0x1c-byte eastl rbtree node/temporary, constructed through FUN_00af0d40.
struct RcMapNode { void FUN_00af0d40(void* out); };             // 0x00AF0D40
struct RcKeyAccessor { uint32_t* GetKey(void* record); };        // 0x0103DE50

void  DoNukeSubtree(void* key);                                 // 0x009A9600
void  operator_delete__(void* p);                               // 0x00F47380

// --- game subsystems ---
void* cSPLivingUniverse_GetUniverseContext();                   // 0x1021080
void* cSPLivingUniverse_GetActivePlanet();                      // 0x1021260
void  __stdcall FUN_00bc0180(void* a);                          // 0x00BC0180
void* PlanetModel();                                            // 0x00B3D350
void* FUN_00b3d420();                                           // 0x00B3D420
void* GetSetting9();                                            // 0x00401090
void* FUN_008414c0(void* a);                                    // 0x008414C0
void* FUN_00b3d450(int hash);                                   // 0x00B3D450
void  FUN_00bbf2b0(void* a);                                    // 0x00BBF2B0
void  FUN_01043c60(void* mgr, void* key);                       // 0x01043C60

// Receiver structs used to emit genuine thiscall calls (ecx = receiver) to external
// retail functions.  Each symbol is an unresolved extern, so only the call shape matters.
struct RcCommunity   { void  AdvancePhase(float dt); };                       // 0x00BFDF20
struct RcDisplay     { void  FUN_00bc08d0(int a);                             // 0x00BC08D0
                       void  FUN_00bc1b10(void* a);                           // 0x00BC1B10
                       void  FUN_00bbcf00(void* pmv, float f1);               // 0x00BBCF00
                       float FUN_00c70a20(int v);                             // 0x00C70A20
                       float FUN_00c709d0(float f); };                        // 0x00C709D0
struct RcCityDisplay { void  AddResourceNodes(); };                           // 0x00B8BBA0
struct RcPlantMgr    { void* GetSpeciesFromID(void* id); };                   // 0x00B90410
struct RcSpeciesMgr  { void* GetProfile(void* key); };                        // 0x004DF550
struct RcCargo       { void  CargoSlotsUpdate(void* a, void* b); };           // 0x00BBC540
struct RcF7F4C0      { void* FUN_00c7f4c0(void* a); };                        // 0x00C7F4C0
struct RcAc10a0      { void* FUN_00ac10a0(); };                               // 0x00AC10A0
struct RcCamera      { void* GetTargetOrientation(void* out); };              // 0x00B137D0
struct RcKeyVec      { void  DoInsertKey(void* end, void* key); };            // 0x004E3E10
struct RcKeyMap      { void* Find(void* key); };                              // 0x0103DE50
struct RcZoneMgr     { void* FUN_00c7f4c0(void* a); };                        // 0x00C7F4C0
struct RcC745D0      { void  FUN_00c745d0(int a, void* key); };               // 0x00C745D0
struct RcC74730      { void  FUN_00c74730(void* a, void* b); };               // 0x00C74730
struct RcC7ED00      { void  FUN_00c7ed00(void* a, void* b); };               // 0x00C7ED00
struct RcC80680      { void  FUN_00c80680(int a, void* key); };               // 0x00C80680
// --- audio ---
void* EA_Audio_GetSystemAT();                                   // 0x00A206F0
void  FUN_00572020(void* a, int b);                             // 0x00572020
void  Start3dSoundByName(void* name, void* handle, float f1, float f2, float f3); // 0x00571F80
void  AudioSetListener3(void* handle, float f1, float f2, float f3); // 0x009FBC50
void* GetCameraCtl();                                           // 0x00B3D280

// --- planet rotation ---
struct RcPlanet     { void  RotNull(); };                       // (unused)
struct RcSimPlanet  { unsigned char IsRotationNull();           // 0x00C708F0
                      void*         GetRotationAxis(); };       // 0x00C70930
struct RcRotOwner   { void* GetUpAxis(); };                     // vtable slot 0x2c

// --- the sound-slot owner (slots of {handle,float} indexed from +0x10, i.e. +8 + i*8) ---
struct SoundSlots {
    uint32_t pad00[2];                                          // 0x00..0x08
    struct Slot {
        void* mpHandle;                                         // +0x00
        float mDistance;                                        // +0x04
    } mSlots[0x17];                                             // 0x08..
};

// --- constants ---
extern float  kFlt156cfb8;                                      // 0x0156CFB8
extern float  kFlt156cfbc;                                      // 0x0156CFBC
extern float  kFlt156cfc0;                                      // 0x0156CFC0
extern float  kFlt156cfc4;                                      // 0x0156CFC4
extern float  kFlt14666d4;                                      // 0x014666D4
extern float  kFlt14666f0;                                      // 0x014666F0
extern float  kFlt13f4fd0;                                      // 0x013F4FD0
extern float  kFlt13f9428;                                      // 0x013F9428
