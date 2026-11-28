// 0x00ec1670: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone), then tidied by tidy64 (casts C++ adds anyway dropped, copies propagated, single-use temporaries folded, variables named by role); byte-exact.
// Still machine-shaped: byte offsets instead of members, and FUN_/DAT_ names by address. Hand-written source: match/slices/s00ec0a40/s00ec0a40.cpp.

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
    virtual void Unk_0F();
    virtual void Unk_10();
    virtual void Unk_11();
    virtual void Unk_12();
    virtual void Unk_13();
    virtual void Unk_14();
    virtual void Unk_15();
    virtual void Unk_16();
    virtual void Unk_17();
    virtual void Unk_18();
    virtual void Unk_19();
    virtual void Unk_1A();
    virtual void Unk_1B();
    virtual void Unk_1C();
    virtual void Unk_1D();
    virtual void Unk_1E();
    virtual void Unk_1F();
    virtual void Unk_20();
    virtual void Unk_21();
    virtual void Unk_22();
    virtual void Unk_23();
    virtual void Unk_24();
    virtual void Unk_25();
    virtual void Unk_26();
    virtual void Unk_27();
    virtual void Unk_28();
    virtual void Unk_29();
    virtual void Unk_2A();
    virtual void Unk_2B();
    virtual void Unk_2C();
    virtual void Unk_2D();
    virtual int Unk_2E(int);
};
struct VObject2 {
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
    virtual int Unk_0B();
};

extern "C" float DAT_01486110;
extern "C" unsigned char DAT_017f243b[];
struct C_00bc97f0 { int FUN_00bc97f0(unsigned int, unsigned int, float, unsigned int); };
struct C_00c7d070 { int FUN_00c7d070(); };
extern "C" int __cdecl FUN_00c7d090(...);
extern "C" int __cdecl FUN_00ec0c90(...);
extern "C" int __cdecl FUN_00ec0d00(...);

// @ 0x00ec1670
extern "C" float __cdecl FUN_00ec1670(int obj, int unused, int unused2, int unused3, int unused4, int unused5, int obj2)
{
    int v_l8[2];
    int ptr;
    int value;
    int ptr2;
    int ptr3;
    int cursor;
    int ptr4;
    int value2;
    int ptr5;
    int ptr6;
    ptr = ((int)*(unsigned short*)((char*)obj2 + 0x12) << 5) + *(int*)((char*)obj + 0x674);
    if ((unsigned char)(int)FUN_00ec0d00((unsigned int)obj, (unsigned int)ptr) == 0) {
        return (float)0;
    }
    value = *(int*)((char*)ptr + 4);
    ptr2 = ptr + 4;
    if (value != 0) {
        if (value != 1) {
            if (value != 2) {
                if (value != 8) {
                    memcpy((void*)(obj + 1672), (void*)ptr, (unsigned int)32);
                    return (float)1;
                }
            }
        }
    }
    ptr3 = (int)((C_00c7d070*)(obj + 1648))->FUN_00c7d070();
    cursor = *(int*)ptr3;
    ptr4 = *(int*)((char*)ptr3 + 4);
    *(int*)&v_l8[0] = *(int*)ptr2;
    value2 = *(int*)((char*)ptr2 + 4);
    obj2 = ptr4;
    *(int*)&v_l8[1] = value2;
    if (cursor != ptr4) {
        do {
            ptr5 = *(int*)cursor;
            if (ptr5 != 0) {
                ptr6 = ((VObject*)ptr5)->Unk_2E((int)DAT_017f243b);
                if (ptr6 != 0) {
                    if ((unsigned char)((VObject2*)ptr6)->Unk_0B() == 0) {
                        if ((unsigned char)(int)FUN_00c7d090((unsigned int)ptr6, (unsigned int)(int)&v_l8) != 0) {
                            if (*(int*)ptr != 4) goto done;
                            if ((unsigned char)(int)FUN_00ec0c90((unsigned int)ptr6, (unsigned int)ptr2) != 0) goto done;
                        }
                    }
                }
                ptr4 = obj2;
            }
            cursor += 4;
        } while (cursor != ptr4);
    }
    return (float)0;
    done:
    ((C_00bc97f0*)(*(int*)((char*)obj + 0xb4c) + 8))->FUN_00bc97f0((unsigned int)0, (unsigned int)268435456, DAT_01486110, (unsigned int)ptr6);
    memcpy((void*)(obj + 1672), (void*)ptr, (unsigned int)32);
    return (float)1;
}
