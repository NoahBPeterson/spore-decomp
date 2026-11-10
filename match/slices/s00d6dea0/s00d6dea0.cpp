// Slice s00d6dea0: the MATE_LEAD helper that sets a creature's hover mode.
#include "types.h"

// The target is a creature-like object whose vtable slot 0x84 is a three-argument
// call, and which has a Hover(int) method at 0x00c13a30.
struct Creature {
    void* m_vtbl;                               // +0x00
    void* m_field04;                            // +0x04
    void* m_field08;                            // +0x08
    void* m_field0c;                            // +0x0c
    void* m_field10;                            // +0x10
    void* m_field14;                            // +0x14
    void* m_field18;                            // +0x18
    void* m_field1c;                            // +0x1c
    void* m_field20;                            // +0x20
    void* m_field24;                            // +0x24
    void* m_field28;                            // +0x28
    void* m_field2c;                            // +0x2c
    void* m_field30;                            // +0x30
    void* m_field34;                            // +0x34
    void* m_field38;                            // +0x38
    void* m_field3c;                            // +0x3c
    void* m_field40;                            // +0x40
    void* m_field44;                            // +0x44
    void* m_field48;                            // +0x48
    void* m_field4c;                            // +0x4c
    void* m_field50;                            // +0x50
    void* m_field54;                            // +0x54
    void* m_field58;                            // +0x58
    void* m_field5c;                            // +0x5c
    void* m_field60;                            // +0x60
    void* m_field64;                            // +0x64
    void* m_field68;                            // +0x68
    void* m_field6c;                            // +0x6c
    void* m_field70;                            // +0x70
    void* m_field74;                            // +0x74
    void* m_field78;                            // +0x78
    void* m_field7c;                            // +0x7c
    void* m_field80;                            // +0x80
    void* m_field84;                            // +0x84

    void __thiscall Hover(int on);              // 0x00c13a30
};

// @ 0x00d6dea0
void __cdecl FUN_00d6dea0(Creature* creature)
{
    typedef void (__thiscall* Vt84)(Creature*, void*, void*, void*);
    ((Vt84)((void**)creature->m_vtbl)[0x84 / 4])(creature, 0, 0, 0);
    creature->Hover(0);
}
