// Slice s008571b0 -- 0x857xxxx region (gwrite-backed stream writers).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP
// /arch:SSE /fp:fast (default /GS on).

typedef unsigned int uint;

// ?gwrite@@YGIPAX0I@Z  (__stdcall, callee cleans the arguments)
unsigned int __stdcall gwrite(void* context, void* buffer, unsigned int size);

// @ 0x00857820 -- FUN_00857820
// Parameter setter: 0xfe selects the secondary slot at +0xc, 0xe0..0xef the
// indexed table at +0x5b8-0x370, anything else raises error 0x43 on the object.
void __cdecl FUN_00857820(int* param_1, unsigned param_2, int param_3) {
    if (param_2 == 0xfe) {
        *(int*)(param_1[0x16e] + 0xc) = param_3;
        return;
    }
    if (param_2 - 0xe0U <= 0xf) {
        *(int*)(param_1[0x16e] - 0x370 + param_2 * 4) = param_3;
        return;
    }
    *(int*)(*param_1 + 0x14) = 0x43;
    *(int*)(*param_1 + 0x18) = param_2;
    (*(void(__cdecl**)(int*))*param_1)(param_1);
}

// @ 0x00857f20 -- FUN_00857f20
// Flushes the full 0x1000-byte buffer through gwrite and rewinds the stream.
int __cdecl FUN_00857f20(int* param_1) {
    int* puVar1 = (int*)param_1[5];
    int iVar2 = gwrite((void*)puVar1[5], (void*)puVar1[6], 0x1000);
    if (iVar2 != 0x1000) {
        *(int*)(*param_1 + 0x14) = 0x24;
        (*(void(__cdecl**)(int*))*param_1)(param_1);
    }
    *puVar1 = puVar1[6];
    puVar1[1] = 0x1000;
    return 1;
}

// @ 0x00857f70 -- FUN_00857f70
// Flushes only the bytes actually held in the buffer (0x1000 - written).
void __cdecl FUN_00857f70(int* param_1) {
    int iVar1 = param_1[5];
    int iVar2 = 0x1000 - *(int*)(iVar1 + 4);
    if (iVar2 != 0) {
        int iVar3 = gwrite((void*)*(int*)(iVar1 + 0x14), (void*)*(int*)(iVar1 + 0x18), iVar2);
        if (iVar3 != iVar2) {
            *(int*)(*param_1 + 0x14) = 0x24;
            (*(void(__cdecl**)(int*))*param_1)(param_1);
        }
    }
}

// @ 0x00857ff0 -- FUN_00857ff0
// Marks the stream state at +0x14 as "final flush done".
void __cdecl FUN_00857ff0(int param_1) {
    *(int*)(*(int*)(param_1 + 0x14) + 0x24) = 1;
}

// @ 0x00858130 -- FUN_00858130
// Resets the write-position counters at +0x94 and selects the stream block
// header size according to the container/stream mode at +0x548 / +0x540.
void __cdecl FUN_00858130(int param_1) {
    int iVar1 = *(int*)(param_1 + 0x5ac);
    *(int*)(param_1 + 0x94) = 0;
    if (1 < *(int*)(param_1 + 0x548)) {
        *(int*)(iVar1 + 0x1c) = 1;
        *(int*)(iVar1 + 0x14) = 0;
        *(int*)(iVar1 + 0x18) = 0;
        return;
    }
    int iVar2 = *(int*)(param_1 + 0x540) - 1;
    if (iVar2 != 0) {
        *(int*)(iVar1 + 0x1c) = *(int*)(*(int*)(param_1 + 0x54c) + 0xc);
        *(int*)(iVar1 + 0x14) = 0;
        *(int*)(iVar1 + 0x18) = 0;
        return;
    }
    *(int*)(iVar1 + 0x1c) = *(int*)(*(int*)(param_1 + 0x54c) + 0x48);
    *(int*)(iVar1 + 0x14) = 0;
    *(int*)(iVar1 + 0x18) = 0;
}
