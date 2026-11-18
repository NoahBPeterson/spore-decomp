// Slice s00ff13c0: releases the storage the object owns.  Three members are plain buffers (freed when the
// allocator's count word in front of the buffer is non-zero), two are ranges whose storage is freed only when
// the range holds more than one two-byte element.  Members are released in reverse declaration order.
// Flags: /O2 /MD /Gy /TP /arch:SSE

typedef unsigned int uint;

// 0x00f47380: the allocator's array deallocation routine.
extern "C" void __cdecl operator_delete_arr(void* p);

struct Sim_s00ff_13c0 {                    // size 0xa8
    char  pad00[0x40];                     // +0x00
    void* mpData40;                        // +0x40  range A, start
    char  pad44[0x4];                      // +0x44
    void* mpData48;                        // +0x48  range A, end
    char  pad4c[0x4];                      // +0x4c
    void* mpData50;                        // +0x50  range B, start
    char  pad54[0x4];                      // +0x54
    void* mpData58;                        // +0x58  range B, end
    char  pad5c[0x20];                     // +0x5c
    void* mpBlock7c;                       // +0x7c
    char  pad80[0x10];                     // +0x80
    void* mpBlock90;                       // +0x90
    char  pad94[0x10];                     // +0x94
    void* mpBlockA4;                       // +0xa4

    void __thiscall Release();
};

// @ 0x00ff13c0
void __thiscall Sim_s00ff_13c0::Release()
{
    if (mpBlockA4 && ((int*)mpBlockA4)[-1] != 0)
        operator_delete_arr(mpBlockA4);
    if (mpBlock90 && ((int*)mpBlock90)[-1] != 0)
        operator_delete_arr(mpBlock90);
    if (mpBlock7c && ((int*)mpBlock7c)[-1] != 0)
        operator_delete_arr(mpBlock7c);

    int bytesB = (int)((char*)mpData58 - (char*)mpData50);
    if ((bytesB & ~1) > 2 && mpData50)
        operator_delete_arr(mpData50);

    int bytesA = (int)((char*)mpData48 - (char*)mpData40);
    if ((bytesA & ~1) > 2 && mpData40)
        operator_delete_arr(mpData40);
}
