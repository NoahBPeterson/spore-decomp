#include "types.h"

// Slice s005d7520: SP::cEditorSystem::Init (4727-byte editor bring-up).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
//
// The function is a single monolithic init (the inverse of SP::cEditorSystem::Shutdown in
// slice s005d61b0): it parses the -pollenLogin switch, registers the Pollen/XHTML handlers,
// creates every editor subsystem (asset browsers, paint system, hint manager, clipboard, name
// generator, content-validation summarizers, ...) and wires them into the AppProperties.
// It is not decompiled here; see partial.txt.

struct SP_cEditorSystem { char pad[4]; };

// @ 0x005d7520
bool __fastcall SP_cEditorSystem_Init(void* self, void* cmdLine)
{
    (void)self; (void)cmdLine;
    return true;
}
