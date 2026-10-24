// Slice s0100a7c0 -- four large game-engine entry points in SporeApp.exe
// (0x0100a7c0..0x0100b4??).  Frozen batch gold6.  32-bit x86, MSVC 2008 SP1,
// flags /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
//
// All four functions reach deep into engine singletons (NounManager / TerrainEditor,
// TriggerManager, PropertyManager, StarManager, MessageServer, PlanetModel, SimSingleton)
// and build eastl::string / eastl::vector temporaries by value.  Reconstructing the exact
// source (and therefore the exact register allocation / basic-block layout) was out of
// budget for this slice, so they are recorded as partial below.  The markers are kept so
// the audit can attribute every assigned VA.

#include "types.h"

// @ 0x0100a7c0  FUN_0100a7c0 (403 bytes) -- __thiscall, 6 stack args (ret 0x18), this->c8
//   vector<0x1c-byte element> (begin/end/cap at +0xc8/+0xcc/+0xd0).  When arg7 == 0 it asks
//   FUN_00b3d4d0() (GetTriggerMgr) whether +0x2c is 1 or 2 and bails out (return 0, freeing the
//   by-value eastl string range arg2..arg4 when heap (>1) and non-null).  Otherwise it queries
//   SP::NounManager()+cTerrainEditor::GetCurrentTerrainSphere, FUN_00c772c0(arg6) and bails the
//   same way.  Otherwise it initialises a stack element: eastl string (begin/end = 0x1667bac,
//   cap = 0x1667bad) assigned from the arg2..arg3 range via 0x454cb0, stores arg6 and arg7,
//   calls FUN_00b3d320()+FUN_00b1de80() and, when the virtual at +0x24 returns true with property
//   type 0xd at [prop+0x12], reads SP::Property::GetFloat() into the element's float; multiplies
//   by 1000.0f (0x13ec5b4) and push_backs the 0x1c-byte element into the +0xc8 vector (fast path
//   at +0x1c or slow path via FUN_01009af0), then FUN_01006630 to fill.  Frees both by-value
//   string ranges and returns 1.  No source, not attempted (partial).
//   Engine refs: 0xb3d4d0 GetTriggerMgr, 0xb3d300 SP::NounManager, 0xf67d90
//   cTerrainEditor::GetCurrentTerrainSphere, 0xc772c0, 0xaddd90, 0x454cb0 eastl char-string
//   assign, 0xb3d320, 0xb1de80, 0x41ea70 Property::GetFloat, 0x1006630, 0x1009af0, 0xf47380
//   operator_delete_array.

// @ 0x0100a960  FUN_0100a960 (1364 bytes) -- __thiscall, huge body (sub esp, 0x90), no args.
//   Lazily constructs the SimSingleton at 0x167a60c (operator_new(0xc8,"Simulator/SimSingleton",
//   ...) + ??0SimSingleton 0xae5c30), calls ?ShutdownEntries@SimSingleton (0xae5930),
//   FUN_01021260, dumps the EffectsManager (0x67ddd0, vtable +0x98 / +0x5c / +0x38), pulls the
//   space-tool at [0x16dc0fc]+0x40 through FUN_00ff3f00 / cSPSpaceToolData::FUN_0104cc90 /
//   FUN_00ff4540, iterates the +0x13c record's +0x15c..+0x160 vector (stride 4) calling
//   FUN_00b8dec0 + Resource::DatabasePackedFile::GetAccessFlags + SP::NounManager + FUN_00b25f40
//   + NEmpire + FUN_00ff3190 + SP::StarManager::GetEmpireByID + FUN_00c35310, builds a
//   SlotMessage<...> (vtable 0x13eb90c / 0x13eb844) sent via MessageServer, calls PlanetModel
//   +0x24 vtable +0xac/+0x84, FUN_0106e270, FUN_01021960(-1), copies the 0x16dc100..0x16dc714
//   float table, calls FUN_0067de00 vtable +0xdc, then a long chain of engine teardown/setup
//   calls (FUN_00b3d470, FUN_01034840, FUN_00b3d310, FUN_00b5a390, FUN_00ffa2c0, FUN_01021230
//   + cStar::GetSolarSystem + cSolarSystem::ActivateGraphics, TerraformingManager,
//   FUN_00bbf860, FUN_00b3d3b0, FUN_00b2ed10, FUN_00b3d440, FUN_00b0c190, FUN_00b3d3c0,
//   FUN_00b781d0, cSPToolManager::ClearToolEffects after an eastl vector erase, EffectsManager
//   vtable +0x54(0x3701a5c) +0x34, FUN_00ffbe50, FUN_00ffc230, FUN_00b3d470, FUN_01034950,
//   EA::ResourceMan::GetManager vtable +0x70, FUN_00b3d290, thunk_FUN_00ac4f50, the SimSingleton
//   double-check, EA::Audio::Eapd::sys_gui, SP::SimTicker vtable +0x54, FUN_00b3d480,
//   FUN_00acc770, FUN_00b6c280, FUN_0067ddc0 vtable +0x28/+0x24, FUN_00cfeac0), then drains the
//   +0xcc/+0xd8 element vector (stride 0x1c) freeing each eastl string, and finally
//   GetTriggerMgr + FUN_00addd90.  No source, not attempted (partial).

// @ 0x0100aec0  FUN_0100aec0 (465 bytes) -- __thiscall, 1 stack arg (ret 4), reads this+0xdc
//   vector<0x14-byte element> (begin/end/cap at +0xdc/+0xe0/+0xe4).  Finds the embassy/agent data
//   via the eastl rbtree find at 0xce6950 into a local {0x1495400, 0x149bad8, 0, 0x1495400}
//   key record, resolves SP::PropertyManager (0x67de30) vtable +0x2c(0x249e8357,0x2ae0c7e,&out),
//   switches on FUN_00c70e00 (1/2/4): each case does a vtable +0x24 property lookup
//   (0xa9856bd1 / 0x897907de / 0xcf99dc04) and, when the property type is 9, reads
//   Property::GetInt (0x41e990), scales by 1000.  Then scans the +0xdc vector (stride 0x14) for an
//   element whose +0xc == the found key (release + return if matched), else calls
//   FUN_00b3d2a0(0x1495400) + FUN_00ba6dc0 + cBioElemSort::SortBanners (0xb8de30) + FUN_00bb9b00
//   (8,1) and push_backs a new 0x14-byte element (vtables 0x1495400 / 0x149bad8, key at +0xc,
//   scaled value at +0x10) into the +0xdc vector.  No source, not attempted (partial).

// @ 0x0100b0a0  FUN_0100b0a0 (907 bytes) -- mission / UFO activation logic: walks a mission
//   array, and for each mission either moves a cSPGameDataUFO between planets (CivData::GetCities,
//   FUN_00c5b860, QuaternionFromFacingAndUp, cSPGameDataUFO::SetDestination / PopToDestination /
//   SetDesiredModel) or (FUN_00c5b340 / cSPMission path) creates one with
//   SP::CreateUFOForSolarOrGalaxy(4, ownerEmpire) and ref-counts it into the mission array
//   (AutoRefCount AddRef/Release through the +0/+4 vtable slots, erase via eastl::copy_impl).  No
//   source, not attempted (partial).