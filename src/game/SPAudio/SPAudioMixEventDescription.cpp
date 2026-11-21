// src/game/SPAudio/SPAudioMixEventDescription.cpp -- migrated from slice(s) s00a3cbb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixEventDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern char  PTR_FUN_01453930[];            // ICommand vtable for the mixevent inline command
extern char  PTR_FUN_01453918[];            // NotifyAttack command vtable

// ---- items of slice s00a3cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);
inline void* operator new(unsigned int, void* p) { return p; }
extern char  PTR_FUN_01453930[];            // ICommand vtable for the mixevent inline command
extern char  PTR_FUN_01453918[];            // NotifyAttack command vtable
namespace EA {
namespace ArgScript {
void cCommandBase_ctor(void* p);
}
}
inline char* VT(int obj) { return *(char**)obj; }
// ---- items of slice s00a3cbb0 end

void operator delete(void*, const char*, int, int, int, int);
extern "C" const char* g_1553c4c;           // 0x01553c4c: keyword the inline mix-event command registers under
struct CommandBase_a3cce0 {
    const void* mpVTable;                   // +0x00
    void Init();                            // 0x0083c800 cCommandBase::cCommandBase
};
struct MixEventInlineCommand : CommandBase_a3cce0 {
    char pad04[0xc];
    MixEventInlineCommand() { Init(); mpVTable = PTR_FUN_01453930; }
};
struct MixEventCommand : CommandBase_a3cce0 {
    char pad04[0x8];
    MixEventCommand() { Init(); mpVTable = PTR_FUN_01453918; }
};
struct IParser_a3cce0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void AddBlock(const char* keyword, void* command);       // +0x14
    virtual void AddCommand(const char* keyword, void* command);     // +0x18
};
// @ 0x00a3cce0
void MixEventAddCommands(IParser_a3cce0* inlineParser, IParser_a3cce0* blockParser)
{
    inlineParser->AddCommand(g_1553c4c, new ("ArgScript/MixEventInline", 0, 0, 0, 0) MixEventInlineCommand);
    blockParser->AddBlock("mixevent", new ("Swarm", 0, 0, 0, 0) MixEventCommand);
}
