// Slice s00b5cfe0 (batch bfs1) — shared types.
// Module "Spore"; SP::cGonzagoMode (primary vtable at +0, secondary at +4,
// eastl list head/tail at +0x20) and related helpers.

#pragma once
#include "types.h"

struct cGonzagoMode
{
    void** vt0;         // +0x00
    void** vt4;         // +0x04
    int    m08;         // +0x08
    char   b0c, b0d, b0e;// +0x0c..+0x0e
    char   pad_0f[1];
    float  f10, f14;    // +0x10,+0x14
    int    m18, m1c;    // +0x18,+0x1c
    void*  listHead;    // +0x20
    void*  listTail;    // +0x24
    char   pad_28[4];
    char   b2c;         // +0x2c
    char   pad_2d[3];
    int    m30, m34, m38, m3c, m40, m44, m48, m4c;
    int    m50, m54, m58, m5c, m60, m64;

    cGonzagoMode();                     // @ 0x00b5df90
    ~cGonzagoMode();                    // @ 0x00b5d7c0
    bool  FUN_00b5d510(int);            // @ 0x00b5d510
    bool  FUN_00b5db40(int);            // @ 0x00b5db40
    void  FUN_00b5db90();               // @ 0x00b5db90
};

extern "C" void  FUN_00b5d3f0(int*);
extern "C" void __stdcall FUN_00b5d760(int);
extern "C" void __stdcall FUN_00b5d7a0(int*);
extern "C" void  FUN_00b5d130(void*, int);
extern "C" void  FUN_00b5d220(void*, int);
extern "C" void  FUN_00b5d2c0(void*, void*);
extern "C" void  FUN_00b5d430(void*, int);
extern "C" void  FUN_00b5d540(void*);
extern "C" void  FUN_00b5d870(void*, void*);
extern "C" void  FUN_00b5da50(void*, void*);
extern "C" void  FUN_00b5dbb0(void*);
extern "C" void  FUN_00b5cfe0(void*, void*);
extern "C" int   FUN_00b5e050(void*, int*);