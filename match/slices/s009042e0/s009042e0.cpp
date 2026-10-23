// Slice s009042e0 -- expat XML parser internals (xmlparse.c build_model /
// doContent / XML_DefaultCurrent family).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1.  The binary's expat was built
// with LTCG, so several internal statics receive the parser in a register
// (eax/ebx/esi) instead of on the stack; those bodies are transcribed with
// ordinary cdecl/fastcall signatures and are therefore only structurally
// equivalent (see nonmatching.txt).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast

typedef unsigned int  uint;
typedef unsigned char byte;
typedef unsigned int  undefined4;
typedef unsigned short ushort;

typedef void* (*MALLOC_FN)(uint);
typedef void* (*REALLOC_FN)(void*, uint);

template <class T>
static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }

template <class T>
static inline T& at(int p, int off) { return *(T*)(p + off); }

void reportDefault(char* parser, char* s, char* end);
void FUN_00903b40();
void __cdecl FUN_00904400(void* param_1, int param_2, int* param_3, int* param_4, int* param_5);

// @ 0x009042e0 -- nextScaffoldPart (parser passed in eax by its LTCG caller)
// Grows the DTD scaffolding arrays and returns the new part index, or -1 when
// an allocation fails.
int __fastcall FUN_009042e0(void* parser) {
    char* d = (char*)at<int>(parser, 0x164);
    if (at<int>(d, 0xb8) == 0) {
        int* arr = (int*)(*(MALLOC_FN*)((char*)parser + 0xc))(at<int>(parser, 0x1d4) * 4);
        at<int*>(d, 0xb8) = arr;
        if (arr == 0) {
            return -1;
        }
        *arr = 0;
    }
    if (at<uint>(d, 0xac) <= at<uint>(d, 0xb0)) {
        int s;
        if (at<int>(d, 0xa4) == 0) {
            s = (int)(*(MALLOC_FN*)((char*)parser + 0xc))(0x380);
            if (s == 0) {
                return -1;
            }
            at<int>(d, 0xac) = 0x20;
        } else {
            s = (int)(*(REALLOC_FN*)((char*)parser + 0x10))((void*)at<int>(d, 0xa4), at<uint>(d, 0xac) * 0x38);
            if (s == 0) {
                return -1;
            }
            at<int>(d, 0xac) = at<int>(d, 0xac) * 2;
        }
        at<int>(d, 0xa4) = s;
    }
    int iVar2 = at<int>(d, 0xb0);
    int iVar3 = at<int>(d, 0xa4);
    at<int>(d, 0xb0) = iVar2 + 1;
    int iVar5 = iVar3 + iVar2 * 0x1c;
    if (at<int>(d, 0xb4) != 0) {
        int parent = iVar3 + *(int*)(at<int>(d, 0xb8) - 4 + at<int>(d, 0xb4) * 4) * 0x1c;
        if (at<int>(parent, 0x10) != 0) {
            *(int*)(iVar3 + 0x18 + at<int>(parent, 0x10) * 0x1c) = iVar2;
        }
        if (at<int>(parent, 0x14) == 0) {
            at<int>(parent, 0xc) = iVar2;
        }
        at<int>(parent, 0x10) = iVar2;
        at<int>(parent, 0x14) = at<int>(parent, 0x14) + 1;
    }
    at<int>(iVar5, 0x18) = 0;
    at<int>(iVar5, 0x14) = 0;
    at<int>(iVar5, 0x10) = 0;
    at<int>(iVar5, 0xc) = 0;
    return iVar2;
}

// @ 0x00904400 -- build_model
// Walks the DTD scaffolding from element index param_2, emitting the content
// model entries (quantifier, name, children) through param_3/param_4/param_5.
void __cdecl FUN_00904400(void* param_1, int param_2, int* param_3, int* param_4, int* param_5) {
    char* d = (char*)at<int>(param_1, 0x164);
    param_2 = param_2 * 0x1c;
    *param_3 = at<int>(at<int>(d, 0xa4), param_2);
    param_3[1] = at<int>(at<int>(d, 0xa4), param_2 + 4);
    if (*param_3 == 4) {
        param_3[2] = *param_5;
        short* psVar4 = (short*)at<int>(at<int>(d, 0xa4), param_2 + 8);
        *(short*)*param_5 = *psVar4;
        *param_5 = *param_5 + 2;
        short sVar2 = *psVar4;
        while (sVar2 != 0) {
            short* psVar1 = psVar4 + 1;
            psVar4 = psVar4 + 1;
            *(short*)*param_5 = *psVar1;
            *param_5 = *param_5 + 2;
            sVar2 = *psVar4;
        }
        param_3[3] = 0;
        param_3[4] = 0;
        return;
    }
    param_3[3] = at<int>(at<int>(d, 0xa4), param_2 + 0x14);
    param_3[4] = *param_4;
    *param_4 = *param_4 + param_3[3] * 0x14;
    int iVar6 = at<int>(at<int>(d, 0xa4), param_2 + 0xc);
    uint uVar5 = 0;
    if (param_3[3] != 0) {
        int off = 0;
        do {
            FUN_00904400(param_1, iVar6, (int*)(param_3[4] + off), param_4, param_5);
            off += 0x14;
            uVar5 = uVar5 + 1;
            iVar6 = at<int>(at<int>(d, 0xa4), 0x18 + iVar6 * 0x1c);
        } while (uVar5 < (uint)param_3[3]);
    }
    param_3[2] = 0;
}

// @ 0x00904510 -- getElementType copy helper (parser passed in ebx)
// Allocates the copy of the model buffer and lets build_model fill it in.
int __fastcall FUN_00904510(void* parser) {
    int iVar1 = (int)(*(MALLOC_FN*)((char*)parser + 0xc))(
        (at<int>(at<int>(parser, 0x164), 0xa8) + at<int>(at<int>(parser, 0x164), 0xb0) * 10) * 2);
    if (iVar1 == 0) {
        return 0;
    }
    FUN_00904400(parser, 0, (int*)iVar1, (int*)iVar1, (int*)iVar1);
    return iVar1;
}

// @ 0x00904580 -- doContent
// Token-pump driver: switches the parser to the content state, runs the prolog
// tokenizer, then dispatches buffered data to the content handler.
uint __cdecl FUN_00904580(char* param_1, int param_2, int param_3) {
    uint uVar3 = 1;
    if (at<int>(param_1, 0x1e0) == 2) {
        at<int>(param_1, 0x11c) = 0x24;
        return 0;
    }
    if (at<int>(param_1, 0x1e0) != 3) {
        at<int>(param_1, 0x1c) = at<int>(param_1, 0x1c) + param_2;
        at<int>(param_1, 0x24) = at<int>(param_1, 0x24) + param_2;
        undefined4* puVar1 = (undefined4*)(param_1 + 0x18);
        at<int>(param_1, 0x128) = at<int>(param_1, 0x18);
        at<int>(param_1, 0x1e0) = 1;
        at<int>(param_1, 0x28) = at<int>(param_1, 0x1c);
        at<char>(param_1, 0x1e4) = (char)param_3;
        int iVar2 = (*(int(__cdecl**)(char*, int, int, void*))(param_1 + 0x118))(
            param_1, at<int>(param_1, 0x18), at<int>(param_1, 0x1c), puVar1);
        at<int>(param_1, 0x11c) = iVar2;
        if (iVar2 != 0) {
            at<int>(param_1, 0x124) = at<int>(param_1, 0x120);
            at<void(*)()>(param_1, 0x118) = FUN_00903b40;
            return 0;
        }
        iVar2 = at<int>(param_1, 0x1e0);
        if (-1 < iVar2) {
            if (iVar2 < 2) {
                if (param_3 != 0) {
                    at<int>(param_1, 0x1e0) = 2;
                    return 1;
                }
            } else if (iVar2 == 3) {
                uVar3 = 2;
            }
        }
        (*(void(__cdecl**)(int, int, int, char*))(at<int>(param_1, 0x90) + 0x34))(
            at<int>(param_1, 0x90), at<int>(param_1, 0x128), *puVar1, param_1 + 0x198);
        at<int>(param_1, 0x128) = *puVar1;
        return uVar3;
    }
    at<int>(param_1, 0x11c) = 0x21;
    return 0;
}

// @ 0x00904680 -- XML_DefaultCurrent
// Feeds the pending event range (internal entity or main buffer) to the
// default handler, when one is installed.
void __cdecl XML_DefaultCurrent(char* param_1) {
    if (at<int>(param_1, 0x50) != 0) {
        if (at<int>(param_1, 300) != 0) {
            int ev = at<int>(param_1, 300);
            reportDefault(param_1, (char*)at<int>(ev, 0), (char*)at<int>(ev, 4));
            return;
        }
        reportDefault(param_1, (char*)at<int>(param_1, 0x120), (char*)at<int>(param_1, 0x124));
    }
}

// @ 0x009046d0 -- doCdataSection
// CDATA-section token pump.  The original receives its tokenizer state in eax
// (LTCG register-argument static) and threads the "next" pointer of every scan
// through a register, which cannot be expressed in portable C: the body below
// keeps that value in local_c and re-enters the tokenizer through the same
// vtable slots.
byte __cdecl doCdataSection(char* param_1, uint* param_2, undefined4 param_3, uint* param_4, char param_5) {
    int tok = at<int>(param_1, 0x90);
    uint uVar1 = *param_2;
    uint* puVar3;
    uint* puVar4;
    uint local_c = 0;
    if (tok == at<int>(param_1, 0x90)) {
        puVar3 = (uint*)(param_1 + 0x120);
        *puVar3 = uVar1;
        puVar4 = (uint*)(param_1 + 0x124);
    } else {
        puVar3 = *(uint**)(param_1 + 300);
        puVar4 = puVar3 + 1;
    }
    *puVar3 = uVar1;
    *param_2 = 0;
    int iVar2 = (*(int(__cdecl**)(char*, uint*, uint*))(tok + 8))(param_1, &uVar1, &local_c);
    *puVar4 = local_c;
    while (iVar2 + 4U < 0x2d) {
        switch (iVar2 + 4U) {
        case 0:
            *puVar3 = local_c;
            return 4;
        case 6: {
            int iStack_4;
            if (at<int>(param_1, 0x3c) == 0) {
                if (at<int>(param_1, 0x50) != 0) {
                    reportDefault(param_1, (char*)uVar1, (char*)local_c);
                }
            } else if (at<char>(tok, 0x49) == 0 || (uVar1 & 1) != 0) {
                iStack_4 = at<int>(param_1, 0x2c);
                (*(void(__cdecl**)(char*, uint*, uint*))(tok + 0x40))(param_1, &uVar1, &local_c);
                *puVar4 = local_c;
                (*(void(__cdecl**)(int, int, int))(param_1 + 0x3c))(
                    at<int>(param_1, 4), at<int>(param_1, 0x2c),
                    iStack_4 - at<int>(param_1, 0x2c) >> 1);
                while (uVar1 != local_c) {
                    *puVar3 = uVar1;
                    iStack_4 = at<int>(param_1, 0x2c);
                    (*(void(__cdecl**)(char*, uint*, uint*))(tok + 0x40))(param_1, &uVar1, &local_c);
                    *puVar4 = local_c;
                    (*(void(__cdecl**)(int, int, int))(param_1 + 0x3c))(
                        at<int>(param_1, 4), at<int>(param_1, 0x2c),
                        iStack_4 - at<int>(param_1, 0x2c) >> 1);
                }
            } else {
                (*(void(__cdecl**)(int, uint, int))(param_1 + 0x3c))(
                    at<int>(param_1, 4), uVar1, (int)(local_c - uVar1) >> 1);
            }
            break;
        }
        case 7: {
            int iStack_4;
            if (at<int>(param_1, 0x3c) == 0) {
                if (at<int>(param_1, 0x50) != 0) {
                    reportDefault(param_1, (char*)uVar1, (char*)local_c);
                }
            } else {
                iStack_4 = 10;
                (*(void(__cdecl**)(int, int*, int))(param_1 + 0x3c))(
                    at<int>(param_1, 4), &iStack_4, 1);
            }
            break;
        }
        case 0x28:
            if (at<int>(param_1, 0x4c) == 0) {
                if (at<int>(param_1, 0x50) != 0) {
                    reportDefault(param_1, (char*)uVar1, (char*)local_c);
                }
            } else {
                (*(void(__cdecl**)(int))(param_1 + 0x4c))(at<int>(param_1, 4));
            }
            *param_2 = local_c;
            *param_4 = local_c;
            return (at<int>(param_1, 0x1e0) != 2) - 1U & 0x23;
        case 0xfffffffc:
        case 0xffffffff:
            if (param_5 != 0) {
                *param_4 = uVar1;
                return 0;
            }
            return 0x14;
        case 0xfffffffe:
            if (param_5 != 0) {
                *param_4 = uVar1;
                return 0;
            }
            return 6;
        default:
            *puVar3 = local_c;
            return 0x17;
        }
        *puVar3 = local_c;
        if (at<int>(param_1, 0x1e0) == 2) {
            return 0x23;
        }
        if (at<int>(param_1, 0x1e0) == 3) {
            *param_4 = local_c;
            return 0;
        }
        iVar2 = (*(int(__cdecl**)(char*, uint*, uint*))(tok + 8))(param_1, &uVar1, &local_c);
        *puVar4 = local_c;
        uVar1 = local_c;
    }
    *puVar3 = local_c;
    return 0x17;
}

int __cdecl FUN_00917130(void* a, void* b, char* c);
int __cdecl FUN_00916f70(void* a, void* b, char* c);
int handleUnknownEncoding(void* enc);
char poolGrow();
int* lookup(int hash, int n);

// @ 0x009049e0 -- doIgnoreSection
// IGNORE-section token pump; same register-argument shape as doCdataSection
// (tokenizer state in eax, scan "next" pointer threaded through a register).
byte __cdecl doIgnoreSection(char* param_1, int* param_2, undefined4 param_3, int* param_4, char param_5) {
    int tok = at<int>(param_1, 0x90);
    int iVar1 = *param_2;
    int* piVar3;
    int* local_4;
    int cur = 0;
    if (tok == at<int>(param_1, 0x90)) {
        piVar3 = (int*)(param_1 + 0x120);
        local_4 = (int*)(param_1 + 0x124);
        *piVar3 = iVar1;
    } else {
        piVar3 = *(int**)(param_1 + 300);
        local_4 = piVar3 + 1;
    }
    *piVar3 = iVar1;
    *param_2 = 0;
    undefined4 uVar2 = (*(int(__cdecl**)(char*, int*, int*))(tok + 0xc))(param_1, &iVar1, &cur);
    *local_4 = cur;
    switch (uVar2) {
    case 0:
        *piVar3 = cur;
        return 4;
    case 0x2a:
        if (at<int>(param_1, 0x50) != 0) {
            reportDefault(param_1, (char*)iVar1, (char*)cur);
        }
        *param_2 = cur;
        *param_4 = cur;
        return (at<int>(param_1, 0x1e0) != 2) - 1U & 0x23;
    case 0xfffffffc:
    case 0xffffffff:
        break;
    default:
        *piVar3 = cur;
        return 0x17;
    case 0xfffffffe:
        if (param_5 != 0) {
            *param_4 = iVar1;
            return 0;
        }
        return 6;
    }
    if (param_5 != 0) {
        *param_4 = iVar1;
        return 0;
    }
    return 2;
}

// @ 0x00904b40 -- initializeEncoding (parser passed in eax)
// Copies the (narrow) protocol encoding name into a 128-byte buffer, then hands
// it to the encoding initialiser; falls back to the unknown-encoding handler.
int __fastcall initializeEncoding(void* parser) {
    ushort* puVar3 = (ushort*)at<int>(parser, 0xe8);
    char* name = 0;
    char local_80[128];
    if (puVar3 == 0) {
        name = 0;
    } else {
        int iVar4 = 0;
        ushort uVar1 = *puVar3;
        while (uVar1 != 0) {
            if (iVar4 == 0x7f || (*puVar3 & 0xff80) != 0) {
                local_80[0] = 0;
                break;
            }
            local_80[iVar4] = (char)*puVar3;
            puVar3 = puVar3 + 1;
            iVar4 = iVar4 + 1;
            uVar1 = *puVar3;
        }
        local_80[iVar4] = 0;
        name = local_80;
    }
    int (__cdecl*pcVar6)(void*, void*, char*) = FUN_00917130;
    if (at<char>(parser, 0xec) == 0) {
        pcVar6 = FUN_00916f70;
    }
    int iVar4 = (*pcVar6)((char*)parser + 0x94, (char*)parser + 0x90, name);
    if (iVar4 != 0) {
        return 0;
    }
    return handleUnknownEncoding((void*)at<int>(parser, 0xe8));
}

// @ 0x00904be0 -- setElementTypePrefix (parser passed in eax)
// Copies the prefix part of a name into the DTD string pool, NUL-terminates it
// and interns it, storing the resulting string in param_1[1].
int __fastcall setElementTypePrefix(void* parser, int junk, int* param_1) {
    char* d = (char*)at<int>(parser, 0x164);
    short* psVar5 = (short*)*param_1;
    short sVar1 = *psVar5;
    do {
        if (sVar1 == 0) {
            return 1;
        }
        if (sVar1 == 0x3a) {
            for (short* psVar6 = (short*)*param_1; psVar6 != psVar5; psVar6 = psVar6 + 1) {
                if (at<int>(d, 0x5c) == at<int>(d, 0x58) && poolGrow() == 0) {
                    return 0;
                }
                **(short**)at<int>(d, 0x5c) = *psVar6;
                at<int>(d, 0x5c) = at<int>(d, 0x5c) + 2;
            }
            if (at<int>(d, 0x5c) == at<int>(d, 0x58) && poolGrow() == 0) {
                return 0;
            }
            **(short**)at<int>(d, 0x5c) = 0;
            at<int>(d, 0x5c) = at<int>(d, 0x5c) + 2;
            int* piVar4 = lookup(at<int>(d, 0x60), 8);
            if (piVar4 == 0) {
                return 0;
            }
            if (*piVar4 == at<int>(d, 0x60)) {
                at<int>(d, 0x60) = at<int>(d, 0x5c);
            } else {
                at<int>(d, 0x5c) = at<int>(d, 0x60);
            }
            param_1[1] = (int)piVar4;
        }
        sVar1 = psVar5[1];
        psVar5 = psVar5 + 1;
    } while (true);
}

void hashTableClear();
void poolClear();

// @ 0x00904cb0 -- getContext (parser passed in edi by its LTCG caller)
// Rebuilds "</prefix:name=value ...>" style context text for entity and general
// entity declarations into the DTD string pool; returns the pool string or 0.
int __fastcall getContext(void* edi_parser) {
    char* p = (char*)edi_parser;
    char* d = (char*)at<int>(p, 0x164);
    bool bVar4 = false;
#define POOL_PUT(v)                                                       \
    do {                                                                  \
        if (at<int>(p, 0x1ac) == at<int>(p, 0x1a8) && poolGrow() == 0) {  \
            return 0;                                                     \
        }                                                                 \
        **(short**)at<int>(p, 0x1ac) = (short)(v);                        \
        at<int>(p, 0x1ac) = at<int>(p, 0x1ac) + 2;                        \
    } while (0)
    if (at<int>(d, 0x9c) != 0) {
        POOL_PUT(0x3d);
        int iVar7 = at<int>(p, 0x1ac);
        int iVar8 = at<int>(at<int>(d, 0x9c), 0x14);
        if (at<short>(p, 0x1d8) != 0) {
            iVar8 = iVar8 + -1;
        }
        int iVar10 = 0;
        if (0 < iVar8) {
            do {
                if (iVar7 == at<int>(p, 0x1a8) && poolGrow() == 0) {
                    return 0;
                }
                **(short**)at<int>(p, 0x1ac) = at<short>(at<int>(at<int>(d, 0x9c), 0x10), iVar10 * 2);
                at<int>(p, 0x1ac) = at<int>(p, 0x1ac) + 2;
                iVar7 = at<int>(p, 0x1ac);
                iVar10 = iVar10 + 1;
            } while (iVar10 < iVar8);
        }
        bVar4 = true;
    }
    char* puVar6 = (char*)at<int>(d, 0x3c);
    char* puVar11 = puVar6 + at<int>(d, 0x44);
    while (puVar6 != puVar11) {
        char* puVar3;
        for (;;) {
            puVar3 = (char*)at<int>(puVar6, 0);
            puVar6 = puVar6 + 4;
            if (puVar3 != 0) break;
            if (puVar6 == puVar11) goto LAB_00904d95;
        }
        if (at<int>(puVar3, 4) != 0) {
            if (bVar4) {
                POOL_PUT(0xc);
            }
            unsigned short* psVar9 = (unsigned short*)at<int>(puVar3, 0);
            unsigned short sVar1 = *psVar9;
            while (sVar1 != 0) {
                POOL_PUT(*psVar9);
                psVar9 = psVar9 + 1;
                sVar1 = *psVar9;
            }
            POOL_PUT(0x3d);
            int iVar7 = at<int>(at<int>(puVar3, 4), 0x14);
            int iVar8 = at<int>(p, 0x1ac);
            if (at<short>(p, 0x1d8) != 0) {
                iVar7 = iVar7 + -1;
            }
            int iVar10 = 0;
            if (0 < iVar7) {
                do {
                    if (iVar8 == at<int>(p, 0x1a8) && poolGrow() == 0) {
                        return 0;
                    }
                    **(short**)at<int>(p, 0x1ac) =
                        at<short>(at<int>(at<int>(puVar3, 4), 0x10), iVar10 * 2);
                    at<int>(p, 0x1ac) = at<int>(p, 0x1ac) + 2;
                    iVar8 = at<int>(p, 0x1ac);
                    iVar10 = iVar10 + 1;
                } while (iVar10 < iVar7);
            }
            bVar4 = true;
        }
    }
LAB_00904d95:
    puVar11 = (char*)at<int>(d, 0);
    char* puVar2 = puVar11 + at<int>(d, 8);
    while (puVar11 != puVar2) {
        char* puVar6b;
        for (;;) {
            puVar6b = (char*)at<int>(puVar11, 0);
            puVar11 = puVar11 + 4;
            if (puVar6b != 0) break;
            if (puVar11 == puVar2) goto LAB_00904dc2;
        }
        if (at<char>(puVar6b, 0x20) != 0) {
            if (bVar4) {
                POOL_PUT(0xc);
            }
            unsigned short* psVar9 = (unsigned short*)at<int>(puVar6b, 0);
            unsigned short sVar1 = *psVar9;
            while (sVar1 != 0) {
                POOL_PUT(*psVar9);
                psVar9 = psVar9 + 1;
                sVar1 = *psVar9;
            }
            bVar4 = true;
        }
    }
LAB_00904dc2:
    POOL_PUT(0);
    return at<int>(p, 0x1b0);
#undef POOL_PUT
}

// @ 0x00904fe0 -- parserCreate (memory suite passed in esi)
// Allocates and initialises a fresh XML_ParserStruct from the given suite.
void* __fastcall FUN_00904fe0(void* memsuite) {
    char* q = (char*)(*(void*(__cdecl**)(uint))at<int>(memsuite, 0))(0xbc);
    if (q == 0) {
        return 0;
    }
    at<int>(q, 0x50) = 0;
    at<int>(q, 0x54) = 0;
    at<int>(q, 0x60) = 0;
    at<int>(q, 0x5c) = 0;
    at<int>(q, 0x58) = 0;
    at<int>(q, 0x64) = at<int>(memsuite, 0);
    at<int>(q, 0x68) = 0;
    at<int>(q, 0x6c) = 0;
    at<int>(q, 0x78) = 0;
    at<int>(q, 0x74) = 0;
    at<int>(q, 0x70) = 0;
    at<int>(q, 0x7c) = at<int>(memsuite, 0);
    at<char>(q, 0x4) = 0;
    at<int>(q, 0x8) = 0;
    at<int>(q, 0xc) = 0;
    at<int>(q, 0) = 0;
    at<int>(q, 0x10) = at<int>(memsuite, 0);
    at<char>(q, 0x18) = 0;
    at<int>(q, 0x1c) = 0;
    at<int>(q, 0x20) = 0;
    at<int>(q, 0x14) = 0;
    at<int>(q, 0x24) = at<int>(memsuite, 0);
    at<char>(q, 0x2c) = 0;
    at<int>(q, 0x30) = 0;
    at<int>(q, 0x34) = 0;
    at<int>(q, 0x28) = 0;
    at<int>(q, 0x38) = at<int>(memsuite, 0);
    at<char>(q, 0x40) = 0;
    at<int>(q, 0x44) = 0;
    at<int>(q, 0x48) = 0;
    at<int>(q, 0x3c) = 0;
    at<int>(q, 0x4c) = at<int>(memsuite, 0);
    at<char>(q, 0x83) = 0;
    at<char>(q, 0x88) = 0;
    at<int>(q, 0x8c) = 0;
    at<int>(q, 0x90) = 0;
    at<int>(q, 0x84) = 0;
    at<int>(q, 0x94) = at<int>(memsuite, 0);
    at<int>(q, 0x98) = 0;
    at<int>(q, 0x9c) = 0;
    at<char>(q, 0xa0) = 0;
    at<int>(q, 0xb8) = 0;
    at<int>(q, 0xa4) = 0;
    at<int>(q, 0xb4) = 0;
    at<int>(q, 0xac) = 0;
    at<int>(q, 0xb0) = 0;
    at<int>(q, 0xa8) = 0;
    at<char>(q, 0x80) = 1;
    at<char>(q, 0x81) = 0;
    at<char>(q, 0x82) = 0;
    return q;
}

// @ 0x009050d0 -- dtdReset (parser/DTD state passed in edi)
// Frees every pooled entity value, clears the DTD hash tables and pools, and
// drops the scaffolding arrays.
void __fastcall dtdReset(void* edi_parser, int junk, int param_1) {
    char* p = (char*)edi_parser;
    char* piVar3 = (char*)at<int>(p, 0x14);
    char* piVar1 = piVar3 + at<int>(p, 0x1c);
    while (piVar3 != piVar1) {
        int iVar2;
        for (;;) {
            iVar2 = at<int>(piVar3, 0);
            piVar3 = piVar3 + 4;
            if (iVar2 != 0) break;
            if (piVar3 == piVar1) goto LAB_009050f5;
        }
        if (at<int>(iVar2, 0x10) != 0) {
            (*(void(__cdecl**)(int))(param_1 + 8))(at<int>(iVar2, 0x14));
        }
    }
LAB_009050f5:
    hashTableClear();
    at<char>(p, 0x83) = 0;
    hashTableClear();
    hashTableClear();
    hashTableClear();
    hashTableClear();
    poolClear();
    poolClear();
    at<int>(p, 0x98) = 0;
    at<int>(p, 0x9c) = 0;
    at<char>(p, 0xa0) = 0;
    (*(void(__cdecl**)(int))(param_1 + 8))(at<int>(p, 0xb8));
    at<int>(p, 0xb8) = 0;
    (*(void(__cdecl**)(int))(param_1 + 8))(at<int>(p, 0xa4));
    at<int>(p, 0xa4) = 0;
    at<int>(p, 0xb4) = 0;
    at<int>(p, 0xac) = 0;
    at<int>(p, 0xb0) = 0;
    at<int>(p, 0xa8) = 0;
    at<char>(p, 0x81) = 0;
    at<char>(p, 0x82) = 0;
    at<char>(p, 0x80) = 1;
}
