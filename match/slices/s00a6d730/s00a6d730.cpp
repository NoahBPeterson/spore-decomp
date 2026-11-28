// 0x00a6d730: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00a6d020/s00a6d020.cpp, src/game/Swarm/EffectsManager.cpp.

#include <string.h>
struct VObject {
    virtual void Unk_00();
    virtual void Unk_01();
    virtual void Unk_02();
    virtual void Unk_03();
    virtual void Unk_04();
    virtual void Unk_05();
    virtual void Unk_06();
    virtual void Unk_07();
    virtual void Unk_08();
    virtual void Unk_09();
    virtual void Unk_0A();
    virtual void Unk_0B();
    virtual void Unk_0C();
    virtual void Unk_0D();
    virtual void Unk_0E();
    virtual int Unk_0F(int, int);
};

struct C_00454cb0 { void FUN_00454cb0(unsigned int, unsigned int); };
extern "C" int __cdecl FUN_008409b0(...);

// @ 0x00a6d730
extern "C" bool __fastcall FUN_00a6d730(char* value, int unused, int value2, int obj)
{
    int value3;
    int ptr;
    int ptr2;
    int value4;
    int index;
    int ptr3;
    int value5;
    value3 = (int)strlen((char*)obj) + obj;
    ptr = (int)value + 584;
    ((C_00454cb0*)ptr)->FUN_00454cb0((unsigned int)obj, (unsigned int)value3);
    ptr2 = (int)FUN_008409b0((unsigned int)ptr);
    value4 = (*(int*)((char*)(int)value + 0x30) - *(int*)((char*)(int)value + 0x2c)) >> 2;
    index = 0;
    if (value4 > 0) {
        do {
            ptr2 = *(int*)((char*)(int)value + 0x2c);
            ptr3 = *(int*)((char*)ptr2 + index * 4);
            if (ptr3 != 0) {
                value5 = *(int*)ptr;
                ptr2 = ((VObject*)ptr3)->Unk_0F(value2, value5);
                if ((unsigned char)ptr2 != 0) goto done;
            }
            ++index;
        } while (index < value4);
    }
    return (bool)false;
    done:
    return (bool)true;
}
