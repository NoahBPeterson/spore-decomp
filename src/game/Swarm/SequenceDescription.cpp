// src/game/Swarm/SequenceDescription.cpp -- migrated from slice(s) s00f94660 by tools/migrate/rewrite.py
// Object file: Swarm/SequenceDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  FUN_00f47380(void*);                  // 0x00f47380  operator delete
extern "C" void* FUN_00838320(void*, int);             // 0x00838320  cArguments::MainArguments
extern "C" int   FUN_008380b0(void*, const char*);     // 0x008380b0  cArguments::HasFlag
extern "C" void  FUN_00a6fd40(void*, void*, int, void*, int);   // 0x00a6fd40  cEffectsParser::AddAnonDescription

// ---- items of slice s00f94660 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
typedef void  (__thiscall *FnVI)(void*, int);
extern "C" void* FUN_0041e050(void*, const wchar16*, ...); // 0x0041e050  WStr_Format
extern "C" void  FUN_00f47380(void*);                  // 0x00f47380  operator delete
extern "C" void* FUN_00f473a0(uint32_t, const char*, int, int, int, int); // 0x00f473a0  EAAllocate
extern "C" void* FUN_00838320(void*, int);             // 0x00838320  cArguments::MainArguments
extern "C" int   FUN_008380b0(void*, const char*);     // 0x008380b0  cArguments::HasFlag
extern "C" void* FUN_0068d840(void*, const wchar16*, int, int); // 0x0068d840  SPKeyFromName
extern "C" void  FUN_00a6fd40(void*, void*, int, void*, int);   // 0x00a6fd40  cEffectsParser::AddAnonDescription
extern wchar16* gEmptyString16;                 // 0x01667bac  eastl::gEmptyString16
// ---- items of slice s00f94660 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* FUN_0041e050(void*, const wchar16*, ...); // 0x0041e050  WStr_Format
extern "C" void* FUN_00f473a0(uint32_t, const char*, int, int, int, int); // 0x00f473a0  EAAllocate
extern "C" void* FUN_0068d840(void*, const wchar16*, int, int); // 0x0068d840  SPKeyFromName
extern wchar16* gEmptyString16;                 // 0x01667bac  eastl::gEmptyString16

// @ 0x00f94df0
extern "C" void __fastcall FUN_00f94df0(void* self, int, void* args)
{
    void* mainArgs = FUN_00838320(args, 1);

    char* d = (char*)FUN_00f473a0(0x18, "Swarm", 0, 0, 0, 0);
    char* desc = 0;
    if (d) {
        *(uint32_t*)(d + 4) = 0;
        *(void**)(d + 0) = (void*)0x1453948;
        *(uint32_t*)(d + 8) = 0;
        *(uint32_t*)(d + 0xc) = 0;
        *(uint32_t*)(d + 0x10) = 0;
        *(uint32_t*)(d + 0x14) = 0;
        ++*(uint32_t*)(d + 4);
        desc = d;
    }

    void* str[3];
    str[0] = gEmptyString16; str[1] = gEmptyString16; str[2] = (void*)0x1667bae;
    FUN_0041e050(str, (const wchar16*)0x13f3da0, *(void**)mainArgs);
    FUN_0068d840(desc + 0xc, (const wchar16*)str[0], 0, 0);

    if (FUN_008380b0(args, "loop"))
        *(uint32_t*)(desc + 8) |= 1;
    if (FUN_008380b0(args, "noOverlap"))
        *(uint32_t*)(desc + 8) |= 4;
    if (FUN_008380b0(args, "hardStop"))
        *(uint32_t*)(desc + 8) |= 4;
    if (FUN_008380b0(args, "hardStart"))
        *(uint32_t*)(desc + 8) |= 2;
    if (FUN_008380b0(args, "noStop"))
        *(uint32_t*)(desc + 8) |= 8;
    if (FUN_008380b0(args, "overlap"))
        *(uint32_t*)(desc + 8) |= 8;

    FUN_00a6fd40(*(void**)((char*)self + 0xc), args, 0x21, desc, 0);

    if (str[0] && str[0] != (void*)0x1667bac)
        FUN_00f47380(str[0]);
    if (desc) {
        if (--*(uint32_t*)(desc + 4) == 0) {
            *(uint32_t*)(desc + 4) = 1;
            ((FnVI)(*(void***)desc)[0 / 4])(desc, 1);
        }
    }
}
