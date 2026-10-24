// Slice s00cde2f0 (batch gold6) -- the SP tribe/space mode object and its transition helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
//   0x00cde2f0 FUN_00cde2f0            (stamp paint decals, install the mode's 0x6dac-byte model)
//   0x00cde5b0 cMode::FUN_00cde5b0     (collapse the pending "baby" pool, then FUN_00cde2f0)
//   0x00cde600 cMode::FUN_00cde600     (same, then tail-call the +0x44 slot)
//   0x00cde660 cMode::FUN_00cde660     (mode state machine; ret 4, one int argument)
//   0x00cdec80 cModeSub::FUN_00cdec80  (transition handler for the sub-object at cMode+0x0c)
//
// DAT_0169b2c8 points at the mode object, which owns a polymorphic cModeSub sub-object at +0x0c.
// Field offsets are named at their retail positions; virtual slots are modelled with the B<n>
// vtable-leader chain used by slice s00fdcd40.  External callees are declared with the retail
// calling convention: a plain free function where the original pushes its arguments, or a member
// of the cSelf helper below where the original loads ecx.

#include "types.h"

// ---------------------------------------------------------------------------------------------
//  external callees and globals
// ---------------------------------------------------------------------------------------------

void* operator new[](unsigned int n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0

void* FUN_00b969a0(void* first, void* last, void* dest);   // 0x00b969a0  _Uninitialized_copy

void  FUN_00ba1c60(int);                                    // 0x00ba1c60
void  FUN_00ba58e0(void*, int);                             // 0x00ba58e0
void  FUN_00cdd960();                                       // 0x00cdd960
void* FUN_01021260();                                       // 0x01021260
void* FUN_00b3d230();                                       // 0x00b3d230
void* FUN_00b3d300();                                       // 0x00b3d300  GetNounManager
void* FUN_00b3d320();                                       // 0x00b3d320
void* FUN_00b3d340();                                       // 0x00b3d340
void* FUN_00b3d350();                                       // 0x00b3d350
void* FUN_00b3d380();                                       // 0x00b3d380
void* FUN_00b3d410();                                       // 0x00b3d410
void* FUN_00b3d440();                                       // 0x00b3d440
void* FUN_00b3d480();                                       // 0x00b3d480
void* FUN_00b3d4f0(int);                                    // 0x00b3d4f0
void* FUN_00b3d520();                                       // 0x00b3d520  GetGonzagoModelWorld
void* FUN_00bc30b0();                                       // 0x00bc30b0
void* FUN_0067dcc0();                                       // 0x0067dcc0  MessageServer
void* FUN_0067ddd0();                                       // 0x0067ddd0  EffectsManager
void* FUN_0067dd00();                                       // 0x0067dd00  AppSystem
void* FUN_0067dd50();                                       // 0x0067dd50
void* FUN_00401010();                                       // 0x00401010
void* FUN_00401090();                                       // 0x00401090
void* FUN_00cc8b10();                                       // 0x00cc8b10
void* FUN_00cdd9c0(int);                                    // 0x00cdd9c0
void  FUN_00cd9760();                                       // 0x00cd9760
void  FUN_00cd3f20(int);                                    // 0x00cd3f20
void  FUN_00cd3fb0(int);                                    // 0x00cd3fb0
void  FUN_00cd5f70();                                       // 0x00cd5f70  cTribeModeStrategy::ContinueLoading
void  FUN_00cd4280();                                       // 0x00cd4280
void  FUN_00c9a080();                                       // 0x00c9a080  cTribe::HotSpotsShutdown
void  FUN_00cd6040();                                       // 0x00cd6040
void  FUN_00cd7770();                                       // 0x00cd7770  cTribeDisplayStrategy::ShowTribeUI
void  FUN_00cdc8b0();                                       // 0x00cdc8b0
void  FUN_00cddcf0();                                       // 0x00cddcf0
void  FUN_00b976f0();                                       // 0x00b976f0
void  FUN_00e398e0(int, void*);                             // 0x00e398e0
void  FUN_00cd98e0(int);                                    // 0x00cd98e0

extern void*  DAT_0169b2c8;                                 // 0x0169b2c8  the mode object (pointer)
extern void*  DAT_0157f18c;                                 // 0x0157f18c
extern void*  DAT_01581288;                                 // 0x01581288
extern void*  DAT_0164dc58;                                 // 0x0164dc58
extern void*  DAT_015fd928;                                 // 0x015fd928
extern float  DAT_014771f8;                                 // 0x014771f8
extern float  DAT_014763b8;                                 // 0x014763b8
extern const char DAT_01472dac[];                           // 0x01472dac
extern const char DAT_013ebc58[];                           // 0x013ebc58

// ---------------------------------------------------------------------------------------------
//  vtable leaders: B<n> carries n+1 virtual slots (offsets 0x00 .. 4*n).  Deriving from B<k-1>
//  and adding one more virtual places the new entry at offset 4*k.
// ---------------------------------------------------------------------------------------------

struct B00 { virtual void a00() {} };
struct B01 : B00 { virtual void a01() {} };
struct B02 : B01 { virtual void a02() {} };
struct B03 : B02 { virtual void a03() {} };
struct B04 : B03 { virtual void a04() {} };
struct B05 : B04 { virtual void a05() {} };
struct B06 : B05 { virtual void a06() {} };
struct B07 : B06 { virtual void a07() {} };
struct B08 : B07 { virtual void a08() {} };
struct B09 : B08 { virtual void a09() {} };
struct B10 : B09 { virtual void a10() {} };
struct B11 : B10 { virtual void a11() {} };
struct B12 : B11 { virtual void a12() {} };
struct B13 : B12 { virtual void a13() {} };
struct B14 : B13 { virtual void a14() {} };
struct B15 : B14 { virtual void a15() {} };
struct B16 : B15 { virtual void a16() {} };
struct B17 : B16 { virtual void a17() {} };
struct B18 : B17 { virtual void a18() {} };
struct B19 : B18 { virtual void a19() {} };
struct B20 : B19 { virtual void a20() {} };
struct B21 : B20 { virtual void a21() {} };
struct B22 : B21 { virtual void a22() {} };
struct B23 : B22 { virtual void a23() {} };
struct B24 : B23 { virtual void a24() {} };
struct B25 : B24 { virtual void a25() {} };
struct B26 : B25 { virtual void a26() {} };
struct B27 : B26 { virtual void a27() {} };
struct B28 : B27 { virtual void a28() {} };
struct B29 : B28 { virtual void a29() {} };
struct B30 : B29 { virtual void a30() {} };
struct B31 : B30 { virtual void a31() {} };
struct B32 : B31 { virtual void a32() {} };
struct B33 : B32 { virtual void a33() {} };
struct B34 : B33 { virtual void a34() {} };
struct B35 : B34 { virtual void a35() {} };
struct B36 : B35 { virtual void a36() {} };
struct B37 : B36 { virtual void a37() {} };
struct B38 : B37 { virtual void a38() {} };
struct B39 : B38 { virtual void a39() {} };
struct B40 : B39 { virtual void a40() {} };

// --- cSelf: stand-in for arbitrary external __thiscall callees (ecx = the object) ------------

struct cRowSet2;    // returned by cSelf::FUN_00b21340 (vector with begin/end at +0x04/+0x08)

struct cSelf
{
    void  FUN_00cd56e0();                                    // 0x00cd56e0
    uint8_t FUN_00c744e0(void*);                             // 0x00c744e0
    void* FUN_00ce6950();                                    // 0x00ce6950
    void* FUN_00ba4e60(void*);                               // 0x00ba4e60
    void* FUN_00c735e0(void*);                               // 0x00c735e0
    void* FUN_00c8e820(void*, void*, void*, void*, void*, void*);  // 0x00c8e820
    void  FUN_00bc2f70(int, void*);                          // 0x00bc2f70
    cRowSet2* FUN_00b21340(void*, void*, void*, void*, void*); // 0x00b21340 GetGameDataVector
    void* FUN_00bfc5f0();                                    // 0x00bfc5f0 GetPlayerTribe
    void* FUN_00f67d90();                                    // 0x00f67d90 GetCurrentTerrainSphere
    void* FUN_00c90460();                                    // 0x00c90460
    void  FUN_00cd7c70(int);                                 // 0x00cd7c70
    void  FUN_00cd4e10();                                    // 0x00cd4e10
    void* FUN_00597e00();                                    // 0x00597e00
    void  FUN_00599440(int, int, int);                        // 0x00599440
    void  FUN_01023030(void*, void*);                        // 0x01023030 (destroy range)
    void  FUN_00cd9440(void*, void*);                        // 0x00cd9440
    void  FUN_00530c80(void*, void*);                        // 0x00530c80
    void  FUN_00e25bd0(void*, void*);                        // 0x00e25bd0
    void  FUN_00b9c250();                                    // 0x00b9c250
    void  FUN_00cd6610();                                    // 0x00cd6610
    void  FUN_00cd54c0();                                    // 0x00cd54c0
    void  FUN_00ccec20(int);                                 // 0x00ccec20
    void  FUN_00cdcf70();                                    // 0x00cdcf70
    void  FUN_00cd9da0();                                    // 0x00cd9da0
    void  FUN_00cddda0();                                    // 0x00cddda0
    void  FUN_00cdcb10();                                    // 0x00cdcb10 TransitionToSpaceMode
    void  FUN_00cd53e0();                                    // 0x00cd53e0 SetRolloverHandle
    void  FUN_00cc4fa0();                                    // 0x00cc4fa0
    void  FUN_00b1dfc0();                                    // 0x00b1dfc0
    void  FUN_00b1e410(int);                                 // 0x00b1e410
    void  FUN_00b2a100();                                    // 0x00b2a100
    void  FUN_00b32250(int);                                 // 0x00b32250
    void  FUN_00b32220(int);                                 // 0x00b32220 IncPauseGate
    void  FUN_00c77380(int, void*);                          // 0x00c77380
    void  FUN_00b8c330(int, int, int);                       // 0x00b8c330
    uint8_t FUN_00e36e00();                                  // 0x00e36e00
    uint8_t FUN_00e36dd0();                                  // 0x00e36dd0
    uint8_t FUN_00e36de0();                                  // 0x00e36de0
    uint8_t FUN_00e36e10();                                  // 0x00e36e10
    uint8_t FUN_00e36fa0();                                  // 0x00e36fa0
    void  FUN_00e2f270();                                    // 0x00e2f270
    void  FUN_00e3b1f0();                                    // 0x00e3b1f0
    void  FUN_00e3e350(int, int, int);                       // 0x00e3e350
    void  FUN_00c93a40();                                    // 0x00c93a40
    void  FUN_00acc700(void*);                               // 0x00acc700
    void  FUN_00b5e9a0(int);                                 // 0x00b5e9a0 Shutdown
    uint8_t FUN_007b19c0();                                  // 0x007b19c0
    void* FUN_004df420();                                    // 0x004df420
    void  FUN_00572660(void*);                               // 0x00572660
    void* FUN_00a16f40();                                    // 0x00a16f40 AsPPTypeParam
    void  FUN_00421c80(int);                                 // 0x00421c80 MessageBasicRC<5> ctor
    void  FUN_0061df40(void*);                               // 0x0061df40
};

// --- small vtable views: objects whose single needed slot is called via the vtable -----------

struct cVtV4   : public B00 { virtual void         v4() {}; };                       // +0x04
struct cVtV8   : public B01 { virtual uint8_t      v8(int) { return 0; }; };          // +0x08
struct cVtV10  : public B03 { virtual int          v10() { return 0; }; };            // +0x10
struct cVtV14  : public B04 { virtual void         v14(int, void*) {}; };             // +0x14
struct cVtV18  : public B05 { virtual void         v18(int, int) {}; };               // +0x18
struct cVtV24  : public B08 { virtual uint8_t      v24(int, void*) { return 0; }; };  // +0x24
struct cVtV28  : public B09 { virtual int          v28() { return 0; }; };            // +0x28
struct cVtV2c0 : public B10 { virtual void*        v2c() { return 0; }; };            // +0x2c, 0 args
struct cVtV2c1 : public B10 { virtual void         v2c(int) {}; };                    // +0x2c, 1 arg
struct cVtV2c2 : public B10 { virtual void*        v2c(float, float) { return 0; }; };// +0x2c, 2 floats
struct cVtV30  : public B11 { virtual void         v30(int) {}; };                    // +0x30
struct cVtV3c  : public B14 { virtual uint8_t      v3c(void*) { return 0; }; };       // +0x3c
struct cVtV40  : public B15 { virtual void         v40(int) {}; };                    // +0x40
struct cVtV44  : public B16 { virtual uint8_t      v44() { return 0; }; };            // +0x44
struct cVtV50  : public B19 { virtual uint8_t      v50() { return 0; }; };            // +0x50
struct cVtV54  : public B20 { virtual void*        v54(int) { return 0; }; };         // +0x54
struct cVtV5c  : public B22 { virtual void         v5c(int, int) {}; };               // +0x5c
struct cVtV60  : public B23 { virtual void         v60(int, int) {}; };               // +0x60
struct cVtV98  : public B37 { virtual void         v98(int, int) {}; };               // +0x98

// the 0x6dac-byte model object: slot 0 releases a new instance, slot 4 the replaced one
struct cRef0        { virtual void vRelease0() {}; };                                 // +0x00
struct cRef4 : public B00 { virtual void vRelease4() {}; };                           // +0x04

// object at cModeSub+0x390 (mSub.mp390): slots +0x04, +0x08, +0x0c
struct cObj390 : public B00
{
    virtual void    v4() {};
    virtual uint8_t v8(int) { return 0; };
    virtual void    vc(int) {};
};

// object produced by FUN_00572660: slots +0x04 and +0x08 (3-argument v8)
struct cObjEp : public B00
{
    virtual uint8_t v4() { return 0; };
    virtual uint8_t v8(void*, int, int) { return 0; };
};

// message object built by 0x0061df40: slot +0x08 plus named fields 0x08/0x10/0x18/0x30
struct cMsgObj : public B01
{
    virtual void v8() {};
    uint8_t  pad04[0x08 - 0x04];
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10
    uint32_t m14;                       // +0x14
    uint32_t m18;                       // +0x18
    uint8_t  pad1c[0x30 - 0x1c];
    uint32_t m30;                       // +0x30
};

// --- views on foreign objects: named members placed at the retail offsets --------------------

struct cTribeAux { uint8_t pad0[0x24]; void* mp24; };                    // noun-manager +0x24
struct cPlanetView { uint8_t pad0[0x13c]; void* mp13c; };                // active planet +0x13c
struct cSphereView                                                   // terrain sphere
{
    uint8_t pad0[0x10f0];
    float   m10f0;      // +0x10f0
    float   m10f4;      // +0x10f4
    uint8_t pad2[0x11c0 - 0x10f8];
    uint8_t m11c0;      // +0x11c0
};
struct cTribeView : public B18                                           // player tribe
{
    virtual void* v4c() { return 0; };  // +0x4c (0 args)
    uint8_t  pad04[0x120 - 0x04];
    cVtV2c0  m120;      // +0x120
    uint8_t  pad2[0x234 - 0x124];
    uint32_t m234;      // +0x234
};
struct cRowSet { uint8_t pad0[0x1e5f0]; uint32_t m1e5f0; uint32_t m1e5f4; };  // 0xb3d440()
struct cRowSet2 { uint32_t m00; uint32_t* pBegin; uint32_t* pEnd; };           // 0xb21340()
struct cTribeObj { uint8_t pad0[0x144]; uint32_t m144; };                      // player object
struct cStateList { uint8_t pad0[0x70]; void* mp70; };                        // DAT_015fd928
struct cRefObj { void* mp00; uint8_t pad04[0x10 - 0x04]; uint8_t m10; uint8_t pad11; uint16_t m12; };

// ---------------------------------------------------------------------------------------------
//  element type of the "baby" pool vector (stride 0x14)
// ---------------------------------------------------------------------------------------------

struct cBaby
{
    void*    mp00;                      // +0x00
    uint32_t m04;                       // +0x04
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10
};

struct cMode;
struct cModeSub;

// ---------------------------------------------------------------------------------------------
//  cModeSub: polymorphic sub-object at cMode+0x0c.  0x00cdec80 is one of its methods.
// ---------------------------------------------------------------------------------------------

struct cModeSub : public B07
{
    virtual uint32_t vOn20() { return 0; };    // +0x20
    virtual void     v24() {};                 // +0x24
    virtual void     v28() {};                 // +0x28
    virtual void     v2c() {};                 // +0x2c
    virtual void     v30() {};                 // +0x30
    virtual void     v34() {};                 // +0x34
    virtual void     v38() {};                 // +0x38
    virtual void     v3c() {};                 // +0x3c
    virtual void     v40() {};                 // +0x40
    virtual void     vOn44(int) {};            // +0x44
    virtual void     v48() {};                 // +0x48
    virtual void     vOn4c() {};               // +0x4c

    uint8_t  pad04[0x1c - 0x04];               // +0x04
    uint8_t  m1c;                              // +0x1c  (cMode+0x28)
    uint8_t  m1d;                              // +0x1d  (cMode+0x29)
    uint8_t  pad1e[0x20 - 0x1e];               // +0x1e
    cBaby*   mpVec1Begin;                      // +0x20  (cMode+0x2c)
    cBaby*   mpVec1End;                        // +0x24  (cMode+0x30)
    cBaby*   mpVec1Cap;                        // +0x28  (cMode+0x34)
    uint8_t  pad2c[0x34 - 0x2c];               // +0x2c
    cBaby*   mpVec2Begin;                      // +0x34  (cMode+0x40)
    cBaby*   mpVec2End;                        // +0x38  (cMode+0x44)
    uint8_t  pad3c[0x6c - 0x3c];               // +0x3c
    uint32_t m6c;                              // +0x6c  (cMode+0x78)
    cBaby*   mpVec3Begin;                      // +0x70  (cMode+0x7c)
    cBaby*   mpVec3End;                        // +0x74  (cMode+0x80)
    uint8_t  pad78[0x88 - 0x78];               // +0x78
    cBaby*   mpVec4Begin;                      // +0x88  (cMode+0x94)
    cBaby*   mpVec4End;                        // +0x8c  (cMode+0x98)
    uint8_t  pad90[0x9c - 0x90];               // +0x90
    uint8_t  m9c;                              // +0x9c  (cMode+0xa8)
    uint8_t  pad9d[0x190 - 0x9d];              // +0x9d
    void*    mp190;                            // +0x190 (cMode+0x19c)
    float    m194;                             // +0x194 (cMode+0x1a0)
    uint8_t  m198;                             // +0x198 (cMode+0x1a4)
    uint8_t  pad199[0x21c - 0x199];            // +0x199
    uint8_t  m21c;                             // +0x21c (cMode+0x228)
    uint32_t m220;                             // +0x220 (cMode+0x22c) state
    uint32_t m224;                             // +0x224 (cMode+0x230) message
    uint32_t m228;                             // +0x228 (cMode+0x234)
    uint32_t m22c;                             // +0x22c (cMode+0x238) counter
    uint32_t m230;                             // +0x230 (cMode+0x23c)
    uint8_t  pad234[0x248 - 0x234];            // +0x234
    void*    mp248;                            // +0x248 (cMode+0x254)
    uint8_t  pad24c[0x390 - 0x24c];            // +0x24c
    void*    mp390;                            // +0x390 (cMode+0x39c)
    uint8_t  m394;                             // +0x394 (cMode+0x3a0)
    uint8_t  m395;                             // +0x395 (cMode+0x3a1)
    uint8_t  m396;                             // +0x396 (cMode+0x3a2)
    uint8_t  m397;                             // +0x397 (cMode+0x3a3)

    void FUN_00cdec80(int msg, int kind);      // 0x00cdec80
};

// cMode's 0x0c-byte primary prefix -- used to recover the owning cMode from a cModeSub.
struct cModeHdr { uint32_t m00, m04, m08; };

// ---------------------------------------------------------------------------------------------
//  cMode: the mode object (DAT_0169b2c8).  Vtable slots +0x44/+0x48/+0x4c sit above B16.
// ---------------------------------------------------------------------------------------------

struct cMode : public B16
{
    virtual void vOn44() {};                   // +0x44
    virtual void v48() {};                     // +0x48
    virtual void vOn4c() {};                   // +0x4c

    uint32_t pad04;                            // +0x04
    uint32_t pad08;                            // +0x08
    cModeSub mSub;                             // +0x0c

    void FUN_00cde5b0();                       // 0x00cde5b0
    void FUN_00cde600();                       // 0x00cde600
    void FUN_00cde660(int arg1);               // 0x00cde660

    cMode* OwnerOf(cModeSub* sub) { return (cMode*)((cModeHdr*)sub - 1); }
};

void FUN_00cde2f0();

// ---------------------------------------------------------------------------------------------
//  0x00cde5b0  cMode::FUN_00cde5b0  -- collapse the pending baby pool, then restart the mode
// ---------------------------------------------------------------------------------------------

// @ 0x00cde5b0
void cMode::FUN_00cde5b0()
{
    cBaby* begin = mSub.mpVec1Begin;
    cBaby* end   = mSub.mpVec1End;

    // release every pooled element, then rewind the pool back to empty
    cBaby* gap = (cBaby*)FUN_00b969a0(end, end, begin);
    ((cSelf*)&mSub.mpVec1Begin)->FUN_01023030(gap, end);

    uint8_t* endB   = (uint8_t*)mSub.mpVec1End;
    uint8_t* beginB = (uint8_t*)begin;
    endB += (beginB - endB) / (int)sizeof(cBaby) * (int)sizeof(cBaby);
    mSub.mpVec1End = (cBaby*)endB;

    FUN_00cde2f0();
}

// ---------------------------------------------------------------------------------------------
//  0x00cde600  cMode::FUN_00cde600  -- as above, then tail-call the +0x44 slot
// ---------------------------------------------------------------------------------------------

// @ 0x00cde600
void cMode::FUN_00cde600()
{
    cBaby* begin = mSub.mpVec1Begin;
    cBaby* end   = mSub.mpVec1End;

    // release every pooled element, then rewind the pool back to empty
    cBaby* gap = (cBaby*)FUN_00b969a0(end, end, begin);
    ((cSelf*)&mSub.mpVec1Begin)->FUN_01023030(gap, end);

    uint8_t* endB   = (uint8_t*)mSub.mpVec1End;
    uint8_t* beginB = (uint8_t*)begin;
    endB += (beginB - endB) / (int)sizeof(cBaby) * (int)sizeof(cBaby);
    mSub.mpVec1End = (cBaby*)endB;

    FUN_00cde2f0();
    vOn44();
}

// ---------------------------------------------------------------------------------------------
//  0x00cde660  cMode::FUN_00cde660  -- the mode state machine (state = mSub.m220, ret 4)
// ---------------------------------------------------------------------------------------------

// @ 0x00cde660
void cMode::FUN_00cde660(int arg1)
{
    const uint32_t msg = mSub.m224;
    bool runState8 = false;

    switch (mSub.m220)
    {
    case 0:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36e00())
            mSub.m220 = 1;
        break;

    case 1:
        if (msg == 0xdbdba1 && !mSub.m396 && !mSub.m1c && !mSub.m1d)
        {
            void* res    = ((cVtV54*)FUN_0067ddd0())->v54(0x5e5284a);
            void* objPtr = 0;
            ((cSelf*)&objPtr)->FUN_00572660(res);

            void* ep = objPtr;
            if (ep)
            {
                void* bound = ((cSelf*)&mSub.mp390)->FUN_00a16f40();
                if (((cObjEp*)ep)->v8(bound, 0, 0x14f10872))
                    ((cObj390*)mSub.mp390)->v8(0);
                ((cObjEp*)ep)->v4();
            }
        }

        mSub.m220 = 2;
        mSub.m22c = 0;

        if (msg == 0xffffffffu || msg == 0x2ccd1d2)
            FUN_00cd5f70();
        ((cSelf*)this)->FUN_00cd9da0();

        if (msg == 0x2ccd1d2 || msg == 0xffffffffu || msg == 0x1654c01)
        {
            mSub.m198 = 1;
        }
        else if (msg == 0xdbdba1)
        {
            if (!mSub.m198)
                goto tail;
            ((cSelf*)FUN_00b3d4f0(1))->FUN_00e2f270();
        }
        else
        {
            FUN_00cd3fb0(0x56d1871);
            mSub.m198 = 0;
        }
        break;

    case 2:
    {
        ((cSelf*)FUN_00b3d350())->FUN_00b8c330(arg1, 0, 0);

        cRowSet* s = (cRowSet*)FUN_00b3d440();
        if (s->m1e5f0 == s->m1e5f4 && mSub.m22c <= 0x3e8)
            goto tail;

        mSub.m220 = 3;
        mSub.m22c = 0;

        if (msg > 0x1654c01)
        {
            if (msg == 0x1654c08)
            {
                ((cSelf*)this)->FUN_00cddda0();
                goto tail;
            }
            if (msg == 0x2ccd1d2)
            {
                FUN_00cde5b0();
                goto tail;
            }
        }
        else if (msg == 0x1654c01)
        {
            FUN_00cde600();
            goto tail;
        }
        else if (msg == 0xffffffffu)
        {
            FUN_00cde5b0();
            goto tail;
        }
        else if (msg == 0xdbdba1)
        {
            ((cSelf*)this)->FUN_00cdcb10();
            goto tail;
        }
        break;
    }

    case 3:
        mSub.m220 = 4;
        mSub.m22c = 0;
        FUN_00cd7770();
        break;

    case 4:
        ((cSelf*)FUN_00b3d350())->FUN_00b8c330(arg1, 0, 0);
        if (mSub.m22c <= 5)
            goto tail;
        {
            void* obj = ((cTribeAux*)FUN_00b3d350())->mp24;
            if (!((cVtV50*)obj)->v50())
                goto tail;
        }
        mSub.m220 = 5;
        mSub.m22c = 0;
        FUN_00cdc8b0();
        if (msg == 0x1654c08)
            goto tail;
        FUN_00cddcf0();
        goto tail;

    case 5:
        if (mSub.m22c > 5)
        {
            mSub.m220 = 6;
            FUN_00cd6040();
            ((cSelf*)this)->FUN_00cd53e0();
        }
        {
            cTribeView* tribe = (cTribeView*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0();
            if (tribe)
            {
                void* p = ((cVtV2c2*)&tribe->m120)->v2c(DAT_014763b8, DAT_014771f8);
                ((cSelf*)FUN_00b3d480())->FUN_00acc700(p);
            }
            ((cVtV2c1*)FUN_00b3d230())->v2c(arg1);
            ((cVtV30*)FUN_00b3d230())->v30(arg1);
        }
        goto tail;

    case 6:
    {
        ((cVtV5c*)FUN_0067dd50())->v5c(0x16, 2);
        int   ebx = ((cVtV28*)FUN_00401010())->v28();
        int   ebp = ((cVtV10*)FUN_00b3d520())->v10();
        void* p   = ((cSelf*)FUN_00401090())->FUN_004df420();
        p = (uint8_t*)p + 0x504;
        uint8_t ok = ((cVtV3c*)FUN_00401010())->v3c(p);

        if (!ok && ebx <= 0 && ebp <= 0 && ((cSelf*)mSub.mp248)->FUN_007b19c0())
        {
            if (((cVtV44*)FUN_0067dd00())->v44() == 1)
                ((cVtV40*)FUN_0067dd00())->v40(0);
        }
        else
        {
            if (((cVtV44*)FUN_0067dd00())->v44())
                goto tail;
            ((cVtV40*)FUN_0067dd00())->v40(1);
            goto tail;
        }
        ((cSelf*)FUN_00cc8b10())->FUN_00cc4fa0();
        mSub.m220 = 7;
        ((cVtV60*)FUN_0067dd50())->v60(0x16, 2);
        break;
    }

    case 7:
        if (mSub.mp390)
        {
            ((cObj390*)mSub.mp390)->vc(0);
            void* old = mSub.mp390;
            if (old)
            {
                mSub.mp390 = 0;
                ((cVtV4*)old)->v4();
            }
            ((cSelf*)FUN_00b3d320())->FUN_00b1dfc0();
        }

        ((cSelf*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0())->FUN_00c93a40();

        if (msg == 0x2ccd1d2 || msg == 0xffffffffu || msg == 0x1654c01)
        {
            if (!DAT_015fd928 ||
                ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70)
                ((cSelf*)FUN_00b3d340())->FUN_00b2a100();
            FUN_00cd4280();
        }

        if (mSub.m395 && mSub.m396)
        {
            mSub.m396 = 0;
            ((cSelf*)FUN_00b3d320())->FUN_00b1e410(0x1654c04);
            ((cSelf*)FUN_00b3d380())->FUN_00b32250(0x4bf38a7);
        }

        if (mSub.m394)
        {
            ((cSelf*)this)->FUN_00cdcf70();
            mSub.m394 = 0;
        }

        if (mSub.m395 && msg != 0xdbdba1 &&
            ((cSelf*)FUN_00b3d410())->FUN_00e36fa0() &&
            (!DAT_015fd928 ||
             ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70))
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e36de0();
            mSub.m220 = 9;
            goto tail;
        }
        runState8 = true;
        break;

    case 8:
        runState8 = true;
        break;

    case 9:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36dd0())
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e3b1f0();
            mSub.m220 = 0xa;
        }
        break;

    case 10:
        if (((cSelf*)FUN_00b3d410())->FUN_00e36e10())
            runState8 = true;
        break;

    default:
        mSub.m220 = 0xb;
        break;
    }

    if (runState8)
    {
        bool listEmpty = !DAT_015fd928 ||
                         ((cStateList*)DAT_015fd928)->mp70 == &((cStateList*)DAT_015fd928)->mp70;
        if (msg != 0xdbdba1 && !listEmpty)
            ((cSelf*)FUN_00b3d410())->FUN_00e3e350(0, 0x1654c02, 1);
        mSub.m220 = 0xb;
        ((cSelf*)FUN_00b3d380())->FUN_00b32250(0x4bf38a7);
    }

tail:
    ((cSelf*)FUN_00b3d230())->FUN_00b5e9a0(arg1);
}

// ---------------------------------------------------------------------------------------------
//  0x00cdec80  cModeSub::FUN_00cdec80  -- transition handler for the sub-object (ret 8)
// ---------------------------------------------------------------------------------------------

// @ 0x00cdec80
void cModeSub::FUN_00cdec80(int msg, int kind)
{
    if (vOn20() == kind)
        return;

    vOn44(kind);

    if (kind == 0x1654c02)
    {
        ((cVtV98*)FUN_0067ddd0())->v98(9, 1);

        if (m395 && m1d == 1)
        {
            ((cSelf*)FUN_00b3d410())->FUN_00e3e350(1, 0x1654c04, 1);
            m396 = 1;
            m220 = 0;
        }
        else
        {
            m220 = 1;
        }

        m224 = msg;
        m228 = 0x1654c02;
        m22c = 0;
        m21c = 1;
        ((cSelf*)FUN_00b3d380())->FUN_00b32220(0x4bf38a7);

        if (msg == 0xdbdba1)
            ((cSelf*)m230)->FUN_00ccec20(1);

        ((cMode*)((cModeHdr*)this - 1))->FUN_00cde660(0);
        vOn4c();
        return;
    }

    if (msg == 0x1654c02)
    {
        if (kind == 0xdbdba1 && !m1c && !m1d)
        {
            void* server = FUN_0067dcc0();
            if (server)
            {
                cSphereView* sphere = (cSphereView*)((cSelf*)FUN_00b3d300())->FUN_00f67d90();
                uint32_t     stamp  = 0;
                ((cSelf*)sphere)->FUN_00c77380(0x55d6335, &stamp);

                cMsgObj* obj = (cMsgObj*)operator new[](0x40, DAT_013ebc58, 0, 0, 0, 0);
                if (obj)
                    ((cSelf*)obj)->FUN_00421c80(0);
                else
                    obj = 0;

                void* holder = 0;
                ((cSelf*)&holder)->FUN_0061df40(obj);
                obj = (cMsgObj*)holder;

                obj->m30 = 0x90a03fdf;
                obj->m08 = stamp;
                obj->m10 = 5;
                obj->m18 = 1;

                ((cVtV14*)server)->v14((int)obj->m30, obj);
                obj->v8();
                vOn4c();
                return;
            }
        }
        else
        {
            if (FUN_00b3d520())
                ((cVtV18*)FUN_00b3d520())->v18(0, 3);

            cMode* mode = (cMode*)((cModeHdr*)this - 1);
            ((cSelf*)mode)->FUN_00cd54c0();
            FUN_00c9a080();

            ((cSelf*)&mpVec2Begin)->FUN_00cd9440(mpVec2Begin, mpVec2End);
            ((cSelf*)&mpVec1Begin)->FUN_00b9c250();
            ((cSelf*)&mpVec3Begin)->FUN_00530c80(mpVec3Begin, mpVec3End);
            m6c = 0;
            ((cSelf*)&mpVec4Begin)->FUN_00e25bd0(mpVec4Begin, mpVec4End);
            m194 = 0.0f;
            ((cSelf*)&m9c)->FUN_00cd6610();
            mode->vOn4c();

            if (kind == 0x2ccd1d2 || kind == 0xffffffffu || kind == 0x1654c04)
                FUN_00b976f0();
        }
    }

    vOn4c();
}

// ---------------------------------------------------------------------------------------------
//  0x00cde2f0  FUN_00cde2f0  -- stamp paint decals and install the mode's model
// ---------------------------------------------------------------------------------------------

// @ 0x00cde2f0
void FUN_00cde2f0()
{
    ((cSelf*)DAT_0169b2c8)->FUN_00cd56e0();
    FUN_00ba1c60(0x1654c02);
    FUN_00cdd960();

    cPlanetView* planet = (cPlanetView*)FUN_01021260();
    cTribeView*  tribe  = (cTribeView*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0();

    uint32_t v = (uint32_t)tribe->v4c();

    if (!((cSelf*)planet)->FUN_00c744e0(&v))
    {
        cSphereView* sphere = (cSphereView*)((cSelf*)FUN_00b3d300())->FUN_00f67d90();
        uint32_t     src    = (uint32_t)((cSelf*)planet->mp13c)->FUN_00ce6950();
        void*        step0  = ((cSelf*)&sphere->m11c0)->FUN_00ba4e60(&src);
        step0 = (uint8_t*)step0 + 0x68;
        uint8_t* flag = (uint8_t*)((cSelf*)step0)->FUN_00c735e0(&v);
        *flag = 1;
        FUN_00ba58e0(tribe, 7);
    }

    void* mgr = FUN_00bc30b0();
    ((cSelf*)mgr)->FUN_00bc2f70(1, tribe->m120.v2c());

    {
        uint32_t scratch[6] = { 0, 0, 0, 0, 0, 0 };
        void*    sp = ((cSelf*)tribe)->FUN_00c8e820(0, &scratch[1], &scratch[4],
                                                    (void*)tribe->m234, 0, 0);
        FUN_00e398e0(0x279c4e55, (uint8_t*)sp + 0x504);
        FUN_00cd9760();
        FUN_00cd3f20(0);
    }

    void* model = operator new[](0x6dac, DAT_01472dac, 0, 0, 0, 0);
    if (model)
        model = ((cSelf*)model)->FUN_00597e00();
    else
        model = 0;

    {
        void* old = ((cMode*)DAT_0169b2c8)->mSub.mp190;
        if (model != old)
        {
            if (model)
                ((cRef0*)model)->vRelease0();
            ((cMode*)DAT_0169b2c8)->mSub.mp190 = model;
            if (old)
                ((cRef4*)old)->vRelease4();
        }
    }

    ((cSelf*)((cMode*)DAT_0169b2c8)->mSub.mp190)->FUN_00599440(
        0xf71fa311, 0x4a5c4493, (int)DAT_0157f18c);

    FUN_00cd98e0(0);
    ((cMode*)DAT_0169b2c8)->v48();

    int frame = (int)FUN_00cdd9c0(1);

    cSphereView* sphere = (cSphereView*)((cSelf*)FUN_00b3d300())->FUN_00f67d90();
    sphere->m10f0 = 0.0f;

    uint32_t sel;
    void*    ref = 0;
    if (!DAT_01581288 || !((cVtV24*)DAT_01581288)->v24(0xc9ce093a, &ref))
    {
        sel = 5;
    }
    else
    {
        cRefObj* p = (cRefObj*)ref;
        uint16_t k = p->m12;
        if (k == 0x0a || k == 0x10)
            sel = (p->m10 & 0x30) ? *(uint32_t*)p->mp00 : (uint32_t)p->mp00;
        else
            sel = (uint32_t)DAT_0164dc58;
    }

    cRowSet2* set   = ((cSelf*)FUN_00b3d300())->FUN_00b21340(
                          (void*)0xcd7d10, (void*)0xd3d420, (void*)0xaccbb0,
                          (void*)0xb1e500, (void*)0x18c6d19);
    int       count = (int)(set->pEnd - set->pBegin);
    int       limit = frame + count - 1;
    if ((uint32_t)limit < sel)
        sel = (uint32_t)limit;

    ((cSelf*)&((cMode*)DAT_0169b2c8)->mSub.mpVec2Begin)->FUN_00cd7c70((int)sel);
    sphere->m10f4 = (float)sel;

    void* obj = ((cSelf*)((cSelf*)FUN_00b3d300())->FUN_00bfc5f0())->FUN_00c90460();
    if (obj)
        ((cTribeObj*)obj)->m144 = sel;

    ((cSelf*)DAT_0169b2c8)->FUN_00cd4e10();
    ((cMode*)DAT_0169b2c8)->mSub.m397 = 1;
}