// Slice s013792c0 — global property-table initialisers.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_142ed14[];
extern "C" char g_142ed24[];
extern "C" char g_1435f20[];
extern "C" char g_1453710[];
extern "C" char g_145511c[];
extern "C" char g_145a51c[];
extern "C" char g_145a568[];
extern "C" char g_145ed30[];
extern "C" char g_1482758[];
extern "C" char g_1482b60[];
extern "C" char g_1482f10[];
extern "C" char g_1483154[];
extern "C" char g_1483430[];
extern "C" char g_1483438[];
extern "C" char g_1483444[];
extern "C" char g_1483450[];
extern "C" char g_148345c[];
extern "C" char g_1483484[];
extern "C" char g_1483490[];
extern "C" char g_148349c[];
extern "C" char g_14834a8[];
extern "C" char g_14834c4[];
extern "C" char g_16ad3a4[];
extern "C" char g_16ad560[];
extern "C" char g_16ad58c[];
extern "C" char g_16ad5b8[];
extern "C" char g_16b0b04[];
extern "C" char g_16b0b30[];
extern "C" char g_16b0c10[];
extern "C" char g_16b0c4c[];
extern "C" char g_16b0c78[];
extern "C" char g_16b0cfc[];
extern "C" char g_16b0dac[];
extern "C" char g_16b0e18[];
extern "C" char g_16b0e44[];
extern "C" char g_16b0e7c[];
extern "C" char g_16b0f10[];
extern "C" char g_16b0fb8[];
extern "C" char g_16b0fe8[];
extern "C" char g_16b10d0[];

#include "s013792c0.h"

// ---------------------------------------------------------------------------
// @ 0x013792c0  InitPropTable_15a68b4
// Twelve descriptors plus terminator.  Each row's +0x24 name pointer is the
// argument hashed for the next row's key.
// ---------------------------------------------------------------------------
void InitPropTable_15a68b4(void)
{
    g_15a68b4[0].hash = SP_sHash((const char*)g_1435f20);
    g_15a68b4[0].f04 = 0;
    g_15a68b4[0].f08 = 4;
    g_15a68b4[0].f0c = PropValI((int)g_16b0dac);
    g_15a68b4[0].f10 = PropValI(4);
    g_15a68b4[0].f14 = 0;
    g_15a68b4[0].f18 = PropValI(0);
    g_15a68b4[0].f1c = 4;
    g_15a68b4[0].f20 = 0;
    g_15a68b4[0].f24 = (int)g_145511c;

    g_15a68b4[1].hash = SP_sHash((const char*)g_145511c);
    g_15a68b4[1].f04 = 0;
    g_15a68b4[1].f08 = 4;
    g_15a68b4[1].f0c = PropValI((int)g_16ad5b8);
    g_15a68b4[1].f10 = PropValI(4);
    g_15a68b4[1].f14 = 0;
    g_15a68b4[1].f18 = PropValI(0);
    g_15a68b4[1].f1c = 4;
    g_15a68b4[1].f20 = 0;
    g_15a68b4[1].f24 = (int)g_142ed24;

    g_15a68b4[2].hash = SP_sHash((const char*)g_142ed24);
    g_15a68b4[2].f04 = 0;
    g_15a68b4[2].f08 = 4;
    g_15a68b4[2].f0c = PropValI((int)g_16b0e44);
    g_15a68b4[2].f10 = PropValI(4);
    g_15a68b4[2].f14 = 0;
    g_15a68b4[2].f18 = PropValI(0);
    g_15a68b4[2].f1c = 4;
    g_15a68b4[2].f20 = 0;
    g_15a68b4[2].f24 = (int)g_142ed14;

    g_15a68b4[3].hash = SP_sHash((const char*)g_142ed14);
    g_15a68b4[3].f04 = 0;
    g_15a68b4[3].f08 = 4;
    g_15a68b4[3].f0c = PropValI((int)g_16ad58c);
    g_15a68b4[3].f10 = PropValI(4);
    g_15a68b4[3].f14 = 0;
    g_15a68b4[3].f18 = PropValI(0);
    g_15a68b4[3].f1c = 4;
    g_15a68b4[3].f20 = 0;
    g_15a68b4[3].f24 = (int)g_148345c;

    g_15a68b4[4].hash = SP_sHash((const char*)g_148345c);
    g_15a68b4[4].f04 = 0;
    g_15a68b4[4].f08 = 4;
    g_15a68b4[4].f0c = PropValI((int)g_16b0f10);
    g_15a68b4[4].f10 = PropValI(4);
    g_15a68b4[4].f14 = 0;
    g_15a68b4[4].f18 = PropValI(0);
    g_15a68b4[4].f1c = 4;
    g_15a68b4[4].f20 = 0;
    g_15a68b4[4].f24 = (int)g_1483450;

    g_15a68b4[5].hash = SP_sHash((const char*)g_1483450);
    g_15a68b4[5].f04 = 0;
    g_15a68b4[5].f08 = 4;
    g_15a68b4[5].f0c = PropValI((int)g_16b0b04);
    g_15a68b4[5].f10 = PropValI(4);
    g_15a68b4[5].f14 = 0;
    g_15a68b4[5].f18 = PropValI(0);
    g_15a68b4[5].f1c = 4;
    g_15a68b4[5].f20 = 0;
    g_15a68b4[5].f24 = (int)g_145a568;

    g_15a68b4[6].hash = SP_sHash((const char*)g_145a568);
    g_15a68b4[6].f04 = 0;
    g_15a68b4[6].f08 = 4;
    g_15a68b4[6].f0c = PropValI((int)g_16b0b30);
    g_15a68b4[6].f10 = PropValI(4);
    g_15a68b4[6].f14 = 0;
    g_15a68b4[6].f18 = PropValI(0);
    g_15a68b4[6].f1c = 4;
    g_15a68b4[6].f20 = 0;
    g_15a68b4[6].f24 = (int)g_1483154;

    g_15a68b4[7].hash = SP_sHash((const char*)g_1483154);
    g_15a68b4[7].f04 = 0;
    g_15a68b4[7].f08 = 4;
    g_15a68b4[7].f0c = PropValI((int)g_16ad560);
    g_15a68b4[7].f10 = PropValI(4);
    g_15a68b4[7].f14 = 0;
    g_15a68b4[7].f18 = PropValI(0);
    g_15a68b4[7].f1c = 4;
    g_15a68b4[7].f20 = 0;
    g_15a68b4[7].f24 = (int)g_1483444;

    g_15a68b4[8].hash = SP_sHash((const char*)g_1483444);
    g_15a68b4[8].f04 = 0;
    g_15a68b4[8].f08 = 4;
    g_15a68b4[8].f0c = PropValI((int)g_16b0c78);
    g_15a68b4[8].f10 = PropValI(4);
    g_15a68b4[8].f14 = 0;
    g_15a68b4[8].f18 = PropValI(0);
    g_15a68b4[8].f1c = 4;
    g_15a68b4[8].f20 = 0;
    g_15a68b4[8].f24 = (int)g_1483438;

    g_15a68b4[9].hash = SP_sHash((const char*)g_1483438);
    g_15a68b4[9].f04 = 0;
    g_15a68b4[9].f08 = 4;
    g_15a68b4[9].f0c = PropValI((int)g_16b0e7c);
    g_15a68b4[9].f10 = PropValI(4);
    g_15a68b4[9].f14 = 0;
    g_15a68b4[9].f18 = PropValI(0);
    g_15a68b4[9].f1c = 4;
    g_15a68b4[9].f20 = 0;
    g_15a68b4[9].f24 = (int)g_1483430;

    g_15a68b4[10].hash = SP_sHash((const char*)g_1483430);
    g_15a68b4[10].f04 = 0;
    g_15a68b4[10].f08 = 4;
    g_15a68b4[10].f0c = PropValI((int)g_16b0e18);
    g_15a68b4[10].f10 = PropValI(4);
    g_15a68b4[10].f14 = 0;
    g_15a68b4[10].f18 = PropValI(0);
    g_15a68b4[10].f1c = 4;
    g_15a68b4[10].f20 = 0;
    g_15a68b4[10].f24 = (int)g_1482758;

    g_15a68b4[11].hash = SP_sHash((const char*)g_1482758);
    g_15a68b4[11].f04 = 0;
    g_15a68b4[11].f08 = 4;
    g_15a68b4[11].f0c = PropValI((int)g_16b0c10);
    g_15a68b4[11].f10 = PropValI(4);
    g_15a68b4[11].f14 = 0;
    g_15a68b4[11].f18 = PropValI(0);
    g_15a68b4[11].f1c = 4;
    g_15a68b4[11].f20 = 0;
    g_15a68b4[11].f24 = 0;

    g_15a68b4[12].hash = SP_sHash(0);
    g_15a68b4[12].f04 = 0xffffffff;
    g_15a68b4[12].f08 = 0;
    g_15a68b4[12].f0c = PropValI(0);
    g_15a68b4[12].f10 = PropValI(0);
    g_15a68b4[12].f14 = 0;
    g_15a68b4[12].f18 = PropValI(0);
    g_15a68b4[12].f1c = 0;
    g_15a68b4[12].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x013797c0  InitPropTable_16b2434
// Three descriptors plus terminator; the last default is 1.0f.
// ---------------------------------------------------------------------------
void InitPropTable_16b2434(void)
{
    g_16b2434[0].hash = SP_sHash(0);
    g_16b2434[0].f04 = 0;
    g_16b2434[0].f08 = 0;
    g_16b2434[0].f0c = PropValI(5);
    g_16b2434[0].f10 = PropValI(0);
    g_16b2434[0].f14 = 0;
    g_16b2434[0].f18 = PropValI(0);
    g_16b2434[0].f1c = 8;
    g_16b2434[0].f20 = 0;
    g_16b2434[0].f24 = 0;

    g_16b2434[1].hash = SP_sHash(0);
    g_16b2434[1].f04 = 4;
    g_16b2434[1].f08 = 4;
    g_16b2434[1].f0c = PropValI(7);
    g_16b2434[1].f10 = PropValI(0);
    g_16b2434[1].f14 = 0;
    g_16b2434[1].f18 = PropValI(0);
    g_16b2434[1].f1c = 0;
    g_16b2434[1].f20 = 0;
    g_16b2434[1].f24 = (int)g_1482f10;

    g_16b2434[2].hash = SP_sHash((const char*)g_1482f10);
    g_16b2434[2].f04 = 8;
    g_16b2434[2].f08 = 0;
    g_16b2434[2].f0c = PropValI(2);
    g_16b2434[2].f10 = PropValI(0);
    g_16b2434[2].f14 = 0;
    g_16b2434[2].f18 = PropValF(1.0f);
    g_16b2434[2].f1c = 2;
    g_16b2434[2].f20 = 0;
    g_16b2434[2].f24 = 0;

    g_16b2434[3].hash = SP_sHash(0);
    g_16b2434[3].f04 = 0xffffffff;
    g_16b2434[3].f08 = 0;
    g_16b2434[3].f0c = PropValI(0);
    g_16b2434[3].f10 = PropValI(0);
    g_16b2434[3].f14 = 0;
    g_16b2434[3].f18 = PropValI(0);
    g_16b2434[3].f1c = 0;
    g_16b2434[3].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01379970  InitPropTable_16b1a0c
// Six descriptors plus terminator; ranged scalar rows keyed by name pointer.
// ---------------------------------------------------------------------------
void InitPropTable_16b1a0c(void)
{
    g_16b1a0c[0].hash = SP_sHash(0);
    g_16b1a0c[0].f04 = 0;
    g_16b1a0c[0].f08 = 0;
    g_16b1a0c[0].f0c = PropValI(5);
    g_16b1a0c[0].f10 = PropValI(0);
    g_16b1a0c[0].f14 = 0;
    g_16b1a0c[0].f18 = PropValI(1);
    g_16b1a0c[0].f1c = 8;
    g_16b1a0c[0].f20 = 0;
    g_16b1a0c[0].f24 = (int)g_1482f10;

    g_16b1a0c[1].hash = SP_sHash((const char*)g_1482f10);
    g_16b1a0c[1].f04 = 8;
    g_16b1a0c[1].f08 = 0;
    g_16b1a0c[1].f0c = PropValI(2);
    g_16b1a0c[1].f10 = PropValI(0);
    g_16b1a0c[1].f14 = 0;
    g_16b1a0c[1].f18 = PropValF(1.0f);
    g_16b1a0c[1].f1c = 2;
    g_16b1a0c[1].f20 = 0;
    g_16b1a0c[1].f24 = (int)g_14834a8;

    g_16b1a0c[2].hash = SP_sHash((const char*)g_14834a8);
    g_16b1a0c[2].f04 = 0xc;
    g_16b1a0c[2].f08 = 0;
    g_16b1a0c[2].f0c = PropValI(1);
    g_16b1a0c[2].f10 = PropValI(0);
    g_16b1a0c[2].f14 = 0;
    g_16b1a0c[2].f18 = PropValI(-1);
    g_16b1a0c[2].f1c = 2;
    g_16b1a0c[2].f20 = 0;
    g_16b1a0c[2].f24 = (int)g_148349c;

    g_16b1a0c[3].hash = SP_sHash((const char*)g_148349c);
    g_16b1a0c[3].f04 = 0x10;
    g_16b1a0c[3].f08 = 0;
    g_16b1a0c[3].f0c = PropValI(1);
    g_16b1a0c[3].f10 = PropValI(0);
    g_16b1a0c[3].f14 = 0;
    g_16b1a0c[3].f18 = PropValI(-1);
    g_16b1a0c[3].f1c = 2;
    g_16b1a0c[3].f20 = 0;
    g_16b1a0c[3].f24 = (int)g_1483490;

    g_16b1a0c[4].hash = SP_sHash((const char*)g_1483490);
    g_16b1a0c[4].f04 = 0x14;
    g_16b1a0c[4].f08 = 0;
    g_16b1a0c[4].f0c = PropValI(1);
    g_16b1a0c[4].f10 = PropValI(0);
    g_16b1a0c[4].f14 = 0;
    g_16b1a0c[4].f18 = PropValI(-1);
    g_16b1a0c[4].f1c = 2;
    g_16b1a0c[4].f20 = 0;
    g_16b1a0c[4].f24 = (int)g_1483484;

    g_16b1a0c[5].hash = SP_sHash((const char*)g_1483484);
    g_16b1a0c[5].f04 = 0x18;
    g_16b1a0c[5].f08 = 0;
    g_16b1a0c[5].f0c = PropValI(1);
    g_16b1a0c[5].f10 = PropValI(0);
    g_16b1a0c[5].f14 = 0;
    g_16b1a0c[5].f18 = PropValI(-1);
    g_16b1a0c[5].f1c = 2;
    g_16b1a0c[5].f20 = 0;
    g_16b1a0c[5].f24 = 0;

    g_16b1a0c[6].hash = SP_sHash(0);
    g_16b1a0c[6].f04 = 0xffffffff;
    g_16b1a0c[6].f08 = 0;
    g_16b1a0c[6].f0c = PropValI(0);
    g_16b1a0c[6].f10 = PropValI(0);
    g_16b1a0c[6].f14 = 0;
    g_16b1a0c[6].f18 = PropValI(0);
    g_16b1a0c[6].f1c = 0;
    g_16b1a0c[6].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01379c40  InitPropTable_15a78e4
// Two descriptors plus terminator, keyed by "creature"/"pollinated".
// ---------------------------------------------------------------------------
void InitPropTable_15a78e4(void)
{
    g_15a78e4[0].hash = SP_sHash((const char*)g_145ed30);
    g_15a78e4[0].f04 = 4;
    g_15a78e4[0].f08 = 0;
    g_15a78e4[0].f0c = PropValI((int)g_16b0c4c);
    g_15a78e4[0].f10 = PropValI(4);
    g_15a78e4[0].f14 = 0;
    g_15a78e4[0].f18 = PropValI(0);
    g_15a78e4[0].f1c = 4;
    g_15a78e4[0].f20 = 0;
    g_15a78e4[0].f24 = (int)g_14834c4;

    g_15a78e4[1].hash = SP_sHash((const char*)g_14834c4);
    g_15a78e4[1].f04 = 4;
    g_15a78e4[1].f08 = 0;
    g_15a78e4[1].f0c = PropValI((int)g_16b0fb8);
    g_15a78e4[1].f10 = PropValI(4);
    g_15a78e4[1].f14 = 0;
    g_15a78e4[1].f18 = PropValI(0);
    g_15a78e4[1].f1c = 4;
    g_15a78e4[1].f20 = 0;
    g_15a78e4[1].f24 = 0;

    g_15a78e4[2].hash = SP_sHash(0);
    g_15a78e4[2].f04 = 0xffffffff;
    g_15a78e4[2].f08 = 0;
    g_15a78e4[2].f0c = PropValI(0);
    g_15a78e4[2].f10 = PropValI(0);
    g_15a78e4[2].f14 = 0;
    g_15a78e4[2].f18 = PropValI(0);
    g_15a78e4[2].f1c = 0;
    g_15a78e4[2].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01379da0  InitPropTable_16b25ec
// Three descriptors plus terminator; the last row carries the 0x1482b60 ptr.
// ---------------------------------------------------------------------------
void InitPropTable_16b25ec(void)
{
    g_16b25ec[0].hash = SP_sHash(0);
    g_16b25ec[0].f04 = 0;
    g_16b25ec[0].f08 = 0;
    g_16b25ec[0].f0c = PropValI(1);
    g_16b25ec[0].f10 = PropValI(0);
    g_16b25ec[0].f14 = 0;
    g_16b25ec[0].f18 = PropValI(1);
    g_16b25ec[0].f1c = 8;
    g_16b25ec[0].f20 = 0;
    g_16b25ec[0].f24 = 0;

    g_16b25ec[1].hash = SP_sHash(0);
    g_16b25ec[1].f04 = 4;
    g_16b25ec[1].f08 = 0;
    g_16b25ec[1].f0c = PropValI(5);
    g_16b25ec[1].f10 = PropValI(0);
    g_16b25ec[1].f14 = 0;
    g_16b25ec[1].f18 = PropValI(0);
    g_16b25ec[1].f1c = 0;
    g_16b25ec[1].f20 = (int)g_1482b60;
    g_16b25ec[1].f24 = 0;

    g_16b25ec[2].hash = SP_sHash(0);
    g_16b25ec[2].f04 = 0xc;
    g_16b25ec[2].f08 = 0;
    g_16b25ec[2].f0c = PropValI(3);
    g_16b25ec[2].f10 = PropValI((int)g_16ad3a4);
    g_16b25ec[2].f14 = 1;
    g_16b25ec[2].f18 = PropValI(0);
    g_16b25ec[2].f1c = 0;
    g_16b25ec[2].f20 = 0;
    g_16b25ec[2].f24 = 0;

    g_16b25ec[3].hash = SP_sHash(0);
    g_16b25ec[3].f04 = 0xffffffff;
    g_16b25ec[3].f08 = 0;
    g_16b25ec[3].f0c = PropValI(0);
    g_16b25ec[3].f10 = PropValI(0);
    g_16b25ec[3].f14 = 0;
    g_16b25ec[3].f18 = PropValI(0);
    g_16b25ec[3].f1c = 0;
    g_16b25ec[3].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x01379f80  InitPropTable_16b1e1c
// Three descriptors plus terminator; second row's index field is 8.
// ---------------------------------------------------------------------------
void InitPropTable_16b1e1c(void)
{
    g_16b1e1c[0].hash = SP_sHash(0);
    g_16b1e1c[0].f04 = 0;
    g_16b1e1c[0].f08 = 0;
    g_16b1e1c[0].f0c = PropValI(1);
    g_16b1e1c[0].f10 = PropValI(0);
    g_16b1e1c[0].f14 = 0;
    g_16b1e1c[0].f18 = PropValI(0);
    g_16b1e1c[0].f1c = 8;
    g_16b1e1c[0].f20 = 0;
    g_16b1e1c[0].f24 = 0;

    g_16b1e1c[1].hash = SP_sHash(0);
    g_16b1e1c[1].f04 = 4;
    g_16b1e1c[1].f08 = 0;
    g_16b1e1c[1].f0c = PropValI(5);
    g_16b1e1c[1].f10 = PropValI(0);
    g_16b1e1c[1].f14 = 0;
    g_16b1e1c[1].f18 = PropValI(0);
    g_16b1e1c[1].f1c = 0;
    g_16b1e1c[1].f20 = (int)g_1482b60;
    g_16b1e1c[1].f24 = 0;

    g_16b1e1c[2].hash = SP_sHash(0);
    g_16b1e1c[2].f04 = 8;
    g_16b1e1c[2].f08 = 0;
    g_16b1e1c[2].f0c = PropValI(3);
    g_16b1e1c[2].f10 = PropValI((int)g_16ad3a4);
    g_16b1e1c[2].f14 = 1;
    g_16b1e1c[2].f18 = PropValI(0);
    g_16b1e1c[2].f1c = 0;
    g_16b1e1c[2].f20 = 0;
    g_16b1e1c[2].f24 = 0;

    g_16b1e1c[3].hash = SP_sHash(0);
    g_16b1e1c[3].f04 = 0xffffffff;
    g_16b1e1c[3].f08 = 0;
    g_16b1e1c[3].f0c = PropValI(0);
    g_16b1e1c[3].f10 = PropValI(0);
    g_16b1e1c[3].f14 = 0;
    g_16b1e1c[3].f18 = PropValI(0);
    g_16b1e1c[3].f1c = 0;
    g_16b1e1c[3].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137a130  InitPropTable_16b2d6c
// Three descriptors plus terminator; first default is the int 2.
// ---------------------------------------------------------------------------
void InitPropTable_16b2d6c(void)
{
    g_16b2d6c[0].hash = SP_sHash(0);
    g_16b2d6c[0].f04 = 0;
    g_16b2d6c[0].f08 = 0;
    g_16b2d6c[0].f0c = PropValI(1);
    g_16b2d6c[0].f10 = PropValI(0);
    g_16b2d6c[0].f14 = 0;
    g_16b2d6c[0].f18 = PropValI(2);
    g_16b2d6c[0].f1c = 8;
    g_16b2d6c[0].f20 = 0;
    g_16b2d6c[0].f24 = 0;

    g_16b2d6c[1].hash = SP_sHash(0);
    g_16b2d6c[1].f04 = 4;
    g_16b2d6c[1].f08 = 0;
    g_16b2d6c[1].f0c = PropValI(5);
    g_16b2d6c[1].f10 = PropValI(0);
    g_16b2d6c[1].f14 = 0;
    g_16b2d6c[1].f18 = PropValI(0);
    g_16b2d6c[1].f1c = 0;
    g_16b2d6c[1].f20 = (int)g_1482b60;
    g_16b2d6c[1].f24 = 0;

    g_16b2d6c[2].hash = SP_sHash(0);
    g_16b2d6c[2].f04 = 0x10;
    g_16b2d6c[2].f08 = 0;
    g_16b2d6c[2].f0c = PropValI(3);
    g_16b2d6c[2].f10 = PropValI((int)g_16ad3a4);
    g_16b2d6c[2].f14 = 1;
    g_16b2d6c[2].f18 = PropValI(0);
    g_16b2d6c[2].f1c = 0;
    g_16b2d6c[2].f20 = 0;
    g_16b2d6c[2].f24 = 0;

    g_16b2d6c[3].hash = SP_sHash(0);
    g_16b2d6c[3].f04 = 0xffffffff;
    g_16b2d6c[3].f08 = 0;
    g_16b2d6c[3].f0c = PropValI(0);
    g_16b2d6c[3].f10 = PropValI(0);
    g_16b2d6c[3].f14 = 0;
    g_16b2d6c[3].f18 = PropValI(0);
    g_16b2d6c[3].f1c = 0;
    g_16b2d6c[3].f20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137a2e0  InitPropTable_15a63dc
// Three descriptors plus terminator, keyed by "player"/"npc"/"epic".
// ---------------------------------------------------------------------------
void InitPropTable_15a63dc(void)
{
    g_15a63dc[0].hash = SP_sHash((const char*)g_1482758);
    g_15a63dc[0].f04 = 0;
    g_15a63dc[0].f08 = 4;
    g_15a63dc[0].f0c = PropValI((int)g_16b0cfc);
    g_15a63dc[0].f10 = PropValI(4);
    g_15a63dc[0].f14 = 0;
    g_15a63dc[0].f18 = PropValI(0);
    g_15a63dc[0].f1c = 4;
    g_15a63dc[0].f20 = 0;
    g_15a63dc[0].f24 = (int)g_145a51c;

    g_15a63dc[1].hash = SP_sHash((const char*)g_145a51c);
    g_15a63dc[1].f04 = 0;
    g_15a63dc[1].f08 = 4;
    g_15a63dc[1].f0c = PropValI((int)g_16b0fe8);
    g_15a63dc[1].f10 = PropValI(4);
    g_15a63dc[1].f14 = 0;
    g_15a63dc[1].f18 = PropValI(0);
    g_15a63dc[1].f1c = 4;
    g_15a63dc[1].f20 = 0;
    g_15a63dc[1].f24 = (int)g_1453710;

    g_15a63dc[2].hash = SP_sHash((const char*)g_1453710);
    g_15a63dc[2].f04 = 0;
    g_15a63dc[2].f08 = 4;
    g_15a63dc[2].f0c = PropValI((int)g_16b10d0);
    g_15a63dc[2].f10 = PropValI(4);
    g_15a63dc[2].f14 = 0;
    g_15a63dc[2].f18 = PropValI(0);
    g_15a63dc[2].f1c = 4;
    g_15a63dc[2].f20 = 0;
    g_15a63dc[2].f24 = 0;

    g_15a63dc[3].hash = SP_sHash(0);
    g_15a63dc[3].f04 = 0xffffffff;
    g_15a63dc[3].f08 = 0;
    g_15a63dc[3].f0c = PropValI(0);
    g_15a63dc[3].f10 = PropValI(0);
    g_15a63dc[3].f14 = 0;
    g_15a63dc[3].f18 = PropValI(0);
    g_15a63dc[3].f1c = 0;
    g_15a63dc[3].f20 = 0;
}
