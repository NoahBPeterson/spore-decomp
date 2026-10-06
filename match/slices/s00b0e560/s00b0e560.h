// Slice s00b0e560 (batch bfs1) — shared stub types.
//
// Module: "Spore" (work/xmatch/retail_lib.json).  The region is a serialization /
// render-queue manager (EASTL/spstl containers) plus a polymorphic input host whose
// SP::cLocalInputState lives at +0x31c (functions 00b0f140..00b0f240).  The 2008
// dev-build PDB supplies the real cLocalInputState layout (size 0x48).

#pragma once
#include "types.h"

// ---- SP::cLocalInputState (PDB, size 0x48) ---------------------------------
struct cLocalInputState
{
    void Reset();                                    // 0x00697980
    bool OnKeyDown(int vkCode, int modifiers);       // 0x00697a50
    bool OnMouseDown(int button, float x, float y, int state);   // 0x00697ab0
    bool OnMouseUp(int button, float x, float y, int state);     // 0x00697af0
};

// ---- polymorphic input host (this+0x31c = cLocalInputState) ----------------
// Only the vtable slot used by FUN_00b0f170 (offset 0x50, index 20) matters.
struct InputHost
{
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();

    char  pad_front[0x10c - 4];   // vptr is 4 bytes; data members follow at +0x04
    float m10c;          // +0x10c
    char  pad_110[4];
    float m114;          // +0x114
    char  pad_118[0x130 - 0x118];
    float m130;          // +0x130
    char  pad_134[4];
    float m138;          // +0x138
    char  pad_13c[0x154 - 0x13c];
    float m154;          // +0x154
    char  pad_158[4];
    float m15c;          // +0x15c
    char  pad_160[0x31c - 0x160];
    cLocalInputState mInput;   // +0x31c

    bool  FUN_00b0f140(int);
    void  FUN_00b0f170();
    bool  FUN_00b0f190(int, int);
    bool  FUN_00b0f1b0(int, float, float, int);
    bool  FUN_00b0f1e0(int, float, float, int);
    void  FUN_00b0f210(float*, float*, float*);
    void  FUN_00b0f240(float*, float*, float*);
};

// ---------------------------------------------------------------------------
// Serialization / render-queue manager (functions 00b0e560..00b0ee10).
// The exact container layout is only partially recovered, so the functions use
// explicit field offsets through this opaque declaration (char pads per the
// matching playbook).
// ---------------------------------------------------------------------------
struct cRenderQueue
{
    char pad[0x364];

    void FUN_00b0e560(int, int, uint32_t);                 // @ 0x00b0e560
    bool FUN_00b0e610(int);                                // @ 0x00b0e610
    void FUN_00b0e6a0();                                   // @ 0x00b0e6a0
    cRenderQueue* FUN_00b0e780(int);                       // @ 0x00b0e780
    void FUN_00b0e810(int);                                // @ 0x00b0e810
    void FUN_00b0e890();                                   // @ 0x00b0e890
    void FUN_00b0e920();                                   // @ 0x00b0e920
    void FUN_00b0ea30();                                   // @ 0x00b0ea30
    void FUN_00b0eae0(int, int);                           // @ 0x00b0eae0
    void FUN_00b0ee10(int, int);                           // @ 0x00b0ee10
};