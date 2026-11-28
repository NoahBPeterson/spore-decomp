// 0x00c8fa60: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: src/game/SPGonzago/SPTribe.cpp, match/slices/s00c8ec60/s00c8ec60.cpp.

struct C_00401090 { int FUN_00401090(); };
struct C_004df550 { int FUN_004df550(unsigned int); };
struct C_004df7d0 { int FUN_004df7d0(unsigned int, unsigned int, unsigned int); };
extern "C" void __cdecl FUN_00ba5df0(...);

// @ 0x00c8fa60
extern "C" bool __fastcall FUN_00c8fa60(char* value, int unused)
{
    int v_l12[3];
    int value2;
    int value3;
    int ptr3;
    int value4;
    int ptr4;
    int value5;
    int value6;
    int cursor;
    int cursor2;
    int ptr = (int)((C_00401090*)(int)value)->FUN_00401090();
    int ptr2 = ptr;
    if (*(int*)((char*)(int)value + 0x18cc) == 0) {
        value2 = *(int*)((char*)(int)value + 0x1904);
        value3 = (int)&v_l12;
        ptr3 = ptr2;
        *(int*)&v_l12[0] = 0;
        *(int*)&v_l12[1] = 0;
        *(int*)&v_l12[2] = 0;
        ptr = (int)((C_004df7d0*)ptr3)->FUN_004df7d0((unsigned int)value2, (unsigned int)-1146426130, (unsigned int)value3);
        if ((unsigned char)ptr != 0) {
            FUN_00ba5df0((unsigned int)*(int*)((char*)(int)value + 0x1904), (unsigned int)(int)&v_l12);
            value4 = *(int*)&v_l12[0];
            ptr4 = *(int*)((char*)(int)value + 0x1904);
            *(int*)ptr4 = value4;
            *(int*)((char*)ptr4 + 4) = *(int*)&v_l12[1];
            value5 = *(int*)&v_l12[2];
            value6 = (int)&v_l12;
            *(int*)((char*)ptr4 + 8) = value5;
            *(int*)((char*)(int)value + 0x18cc) = (int)((C_004df550*)ptr2)->FUN_004df550((unsigned int)value6);
            cursor = 12;
            cursor2 = (int)value + 6352;
            do {
                ptr = *(int*)((char*)(int)value + 0x1904);
                if (*(int*)((char*)cursor + ptr) != 0) {
                    if (*(int*)cursor2 == 0) {
                        *(int*)((char*)cursor + ptr) = *(int*)ptr;
                        *(int*)((char*)cursor + ptr + 4) = *(int*)((char*)ptr + 4);
                        *(int*)((char*)cursor + ptr + 8) = *(int*)((char*)ptr + 8);
                        ptr = *(int*)((char*)(int)value + 0x18cc);
                        *(int*)cursor2 = ptr;
                    }
                }
                cursor += 12;
                cursor2 += 4;
            } while (cursor < 168);
        }
    }
    return (bool)true;
}
