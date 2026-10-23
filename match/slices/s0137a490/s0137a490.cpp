// Slice s0137a490 — global property-table initialisers.
// Compile: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s0137a490.h"

// ---------------------------------------------------------------------------
// @ 0x0137a5e0  InitPropTable_15a674c
// Two descriptors, the first keyed by the literal name "color".
// ---------------------------------------------------------------------------
void InitPropTable_15a674c(void)
{
    g_15a674c[0].name  = SP_sHash("color");
    g_15a674c[0].type  = 4;
    g_15a674c[0].unk08 = 0;
    g_15a674c[0].val0  = PropValI(0x016ad66c);
    g_15a674c[0].val1  = PropValI(4);
    g_15a674c[0].index = 0;
    g_15a674c[0].defVal = PropValI(0);
    g_15a674c[0].unk1C = 4;
    g_15a674c[0].unk20 = 0;
    g_15a674c[0].unk24 = 0;

    g_15a674c[1].name  = SP_sHash(0);
    g_15a674c[1].type  = 0xffffffff;
    g_15a674c[1].unk08 = 0;
    g_15a674c[1].val0  = PropValI(0);
    g_15a674c[1].val1  = PropValI(0);
    g_15a674c[1].index = 0;
    g_15a674c[1].defVal = PropValI(0);
    g_15a674c[1].unk1C = 0;
    g_15a674c[1].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137a490  InitPropTable_16b17b4
// Three descriptors; the last default is the float constant 1.0f.
// ---------------------------------------------------------------------------
void InitPropTable_16b17b4(void)
{
    g_16b17b4[0].name  = SP_sHash(0);
    g_16b17b4[0].type  = 0;
    g_16b17b4[0].unk08 = 0;
    g_16b17b4[0].val0  = PropValI(8);
    g_16b17b4[0].val1  = PropValI(0);
    g_16b17b4[0].index = 0;
    g_16b17b4[0].defVal = PropValI(0x015a5dfc);
    g_16b17b4[0].unk1C = 0;
    g_16b17b4[0].unk20 = 0;
    g_16b17b4[0].unk24 = 0;

    g_16b17b4[1].name  = SP_sHash(0);
    g_16b17b4[1].type  = 0xc;
    g_16b17b4[1].unk08 = 0;
    g_16b17b4[1].val0  = PropValI(2);
    g_16b17b4[1].val1  = PropValI(0);
    g_16b17b4[1].index = 1;
    g_16b17b4[1].defVal = PropValF(1.0f);
    g_16b17b4[1].unk1C = 0;
    g_16b17b4[1].unk20 = 0;
    g_16b17b4[1].unk24 = 0;

    g_16b17b4[2].name  = SP_sHash(0);
    g_16b17b4[2].type  = 0xffffffff;
    g_16b17b4[2].unk08 = 0;
    g_16b17b4[2].val0  = PropValI(0);
    g_16b17b4[2].val1  = PropValI(0);
    g_16b17b4[2].index = 0;
    g_16b17b4[2].defVal = PropValI(0);
    g_16b17b4[2].unk1C = 0;
    g_16b17b4[2].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137a6e0  InitPropTable_16b1d04
// Seven descriptors: one int pair, one lookup, five scalars defaulting to -1.0f.
// ---------------------------------------------------------------------------
void InitPropTable_16b1d04(void)
{
    g_16b1d04[0].name  = SP_sHash(0);
    g_16b1d04[0].type  = 4;
    g_16b1d04[0].unk08 = 0;
    g_16b1d04[0].val0  = PropValI(1);
    g_16b1d04[0].val1  = PropValI(0);
    g_16b1d04[0].index = 0;
    g_16b1d04[0].defVal = PropValI(1);
    g_16b1d04[0].unk1C = 8;
    g_16b1d04[0].unk20 = 0;
    g_16b1d04[0].unk24 = 0;

    g_16b1d04[1].name  = SP_sHash(0);
    g_16b1d04[1].type  = 0;
    g_16b1d04[1].unk08 = 0;
    g_16b1d04[1].val0  = PropValI(7);
    g_16b1d04[1].val1  = PropValI(0);
    g_16b1d04[1].index = 0;
    g_16b1d04[1].defVal = PropValI(0);
    g_16b1d04[1].unk1C = 0;
    g_16b1d04[1].unk20 = 0;
    g_16b1d04[1].unk24 = 0;

    g_16b1d04[2].name  = SP_sHash(0);
    g_16b1d04[2].type  = 8;
    g_16b1d04[2].unk08 = 0;
    g_16b1d04[2].val0  = PropValI(2);
    g_16b1d04[2].val1  = PropValI(0);
    g_16b1d04[2].index = 1;
    g_16b1d04[2].defVal = PropValF(-1.0f);
    g_16b1d04[2].unk1C = 0;
    g_16b1d04[2].unk20 = 0;
    g_16b1d04[2].unk24 = 0;

    g_16b1d04[3].name  = SP_sHash(0);
    g_16b1d04[3].type  = 0xc;
    g_16b1d04[3].unk08 = 0;
    g_16b1d04[3].val0  = PropValI(2);
    g_16b1d04[3].val1  = PropValI(0);
    g_16b1d04[3].index = 2;
    g_16b1d04[3].defVal = PropValF(-1.0f);
    g_16b1d04[3].unk1C = 0;
    g_16b1d04[3].unk20 = 0;
    g_16b1d04[3].unk24 = 0;

    g_16b1d04[4].name  = SP_sHash(0);
    g_16b1d04[4].type  = 0x10;
    g_16b1d04[4].unk08 = 0;
    g_16b1d04[4].val0  = PropValI(2);
    g_16b1d04[4].val1  = PropValI(0);
    g_16b1d04[4].index = 3;
    g_16b1d04[4].defVal = PropValF(-1.0f);
    g_16b1d04[4].unk1C = 0;
    g_16b1d04[4].unk20 = 0;
    g_16b1d04[4].unk24 = 0;

    g_16b1d04[5].name  = SP_sHash(0);
    g_16b1d04[5].type  = 0x14;
    g_16b1d04[5].unk08 = 0;
    g_16b1d04[5].val0  = PropValI(2);
    g_16b1d04[5].val1  = PropValI(0);
    g_16b1d04[5].index = 4;
    g_16b1d04[5].defVal = PropValF(-1.0f);
    g_16b1d04[5].unk1C = 0;
    g_16b1d04[5].unk20 = 0;
    g_16b1d04[5].unk24 = 0;

    g_16b1d04[6].name  = SP_sHash(0);
    g_16b1d04[6].type  = 0xffffffff;
    g_16b1d04[6].unk08 = 0;
    g_16b1d04[6].val0  = PropValI(0);
    g_16b1d04[6].val1  = PropValI(0);
    g_16b1d04[6].index = 0;
    g_16b1d04[6].defVal = PropValI(0);
    g_16b1d04[6].unk1C = 0;
    g_16b1d04[6].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137a9c0  InitPropTable_16b3014
// Same shape as the 16b1d04 table; the first default stays 0.
// ---------------------------------------------------------------------------
void InitPropTable_16b3014(void)
{
    g_16b3014[0].name  = SP_sHash(0);
    g_16b3014[0].type  = 4;
    g_16b3014[0].unk08 = 0;
    g_16b3014[0].val0  = PropValI(1);
    g_16b3014[0].val1  = PropValI(0);
    g_16b3014[0].index = 0;
    g_16b3014[0].defVal = PropValI(0);
    g_16b3014[0].unk1C = 8;
    g_16b3014[0].unk20 = 0;
    g_16b3014[0].unk24 = 0;

    g_16b3014[1].name  = SP_sHash(0);
    g_16b3014[1].type  = 0;
    g_16b3014[1].unk08 = 0;
    g_16b3014[1].val0  = PropValI(7);
    g_16b3014[1].val1  = PropValI(0);
    g_16b3014[1].index = 0;
    g_16b3014[1].defVal = PropValI(0);
    g_16b3014[1].unk1C = 0;
    g_16b3014[1].unk20 = 0;
    g_16b3014[1].unk24 = 0;

    g_16b3014[2].name  = SP_sHash(0);
    g_16b3014[2].type  = 8;
    g_16b3014[2].unk08 = 0;
    g_16b3014[2].val0  = PropValI(2);
    g_16b3014[2].val1  = PropValI(0);
    g_16b3014[2].index = 1;
    g_16b3014[2].defVal = PropValF(-1.0f);
    g_16b3014[2].unk1C = 0;
    g_16b3014[2].unk20 = 0;
    g_16b3014[2].unk24 = 0;

    g_16b3014[3].name  = SP_sHash(0);
    g_16b3014[3].type  = 0xc;
    g_16b3014[3].unk08 = 0;
    g_16b3014[3].val0  = PropValI(2);
    g_16b3014[3].val1  = PropValI(0);
    g_16b3014[3].index = 2;
    g_16b3014[3].defVal = PropValF(-1.0f);
    g_16b3014[3].unk1C = 0;
    g_16b3014[3].unk20 = 0;
    g_16b3014[3].unk24 = 0;

    g_16b3014[4].name  = SP_sHash(0);
    g_16b3014[4].type  = 0x10;
    g_16b3014[4].unk08 = 0;
    g_16b3014[4].val0  = PropValI(2);
    g_16b3014[4].val1  = PropValI(0);
    g_16b3014[4].index = 3;
    g_16b3014[4].defVal = PropValF(-1.0f);
    g_16b3014[4].unk1C = 0;
    g_16b3014[4].unk20 = 0;
    g_16b3014[4].unk24 = 0;

    g_16b3014[5].name  = SP_sHash(0);
    g_16b3014[5].type  = 0x14;
    g_16b3014[5].unk08 = 0;
    g_16b3014[5].val0  = PropValI(2);
    g_16b3014[5].val1  = PropValI(0);
    g_16b3014[5].index = 4;
    g_16b3014[5].defVal = PropValF(-1.0f);
    g_16b3014[5].unk1C = 0;
    g_16b3014[5].unk20 = 0;
    g_16b3014[5].unk24 = 0;

    g_16b3014[6].name  = SP_sHash(0);
    g_16b3014[6].type  = 0xffffffff;
    g_16b3014[6].unk08 = 0;
    g_16b3014[6].val0  = PropValI(0);
    g_16b3014[6].val1  = PropValI(0);
    g_16b3014[6].index = 0;
    g_16b3014[6].defVal = PropValI(0);
    g_16b3014[6].unk1C = 0;
    g_16b3014[6].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137ac90  InitPropTable_16b2b3c
// First default is the int 2.
// ---------------------------------------------------------------------------
void InitPropTable_16b2b3c(void)
{
    g_16b2b3c[0].name  = SP_sHash(0);
    g_16b2b3c[0].type  = 4;
    g_16b2b3c[0].unk08 = 0;
    g_16b2b3c[0].val0  = PropValI(1);
    g_16b2b3c[0].val1  = PropValI(0);
    g_16b2b3c[0].index = 0;
    g_16b2b3c[0].defVal = PropValI(2);
    g_16b2b3c[0].unk1C = 8;
    g_16b2b3c[0].unk20 = 0;
    g_16b2b3c[0].unk24 = 0;

    g_16b2b3c[1].name  = SP_sHash(0);
    g_16b2b3c[1].type  = 0;
    g_16b2b3c[1].unk08 = 0;
    g_16b2b3c[1].val0  = PropValI(7);
    g_16b2b3c[1].val1  = PropValI(0);
    g_16b2b3c[1].index = 0;
    g_16b2b3c[1].defVal = PropValI(0);
    g_16b2b3c[1].unk1C = 0;
    g_16b2b3c[1].unk20 = 0;
    g_16b2b3c[1].unk24 = 0;

    g_16b2b3c[2].name  = SP_sHash(0);
    g_16b2b3c[2].type  = 8;
    g_16b2b3c[2].unk08 = 0;
    g_16b2b3c[2].val0  = PropValI(2);
    g_16b2b3c[2].val1  = PropValI(0);
    g_16b2b3c[2].index = 1;
    g_16b2b3c[2].defVal = PropValF(-1.0f);
    g_16b2b3c[2].unk1C = 0;
    g_16b2b3c[2].unk20 = 0;
    g_16b2b3c[2].unk24 = 0;

    g_16b2b3c[3].name  = SP_sHash(0);
    g_16b2b3c[3].type  = 0xc;
    g_16b2b3c[3].unk08 = 0;
    g_16b2b3c[3].val0  = PropValI(2);
    g_16b2b3c[3].val1  = PropValI(0);
    g_16b2b3c[3].index = 2;
    g_16b2b3c[3].defVal = PropValF(-1.0f);
    g_16b2b3c[3].unk1C = 0;
    g_16b2b3c[3].unk20 = 0;
    g_16b2b3c[3].unk24 = 0;

    g_16b2b3c[4].name  = SP_sHash(0);
    g_16b2b3c[4].type  = 0x10;
    g_16b2b3c[4].unk08 = 0;
    g_16b2b3c[4].val0  = PropValI(2);
    g_16b2b3c[4].val1  = PropValI(0);
    g_16b2b3c[4].index = 3;
    g_16b2b3c[4].defVal = PropValF(-1.0f);
    g_16b2b3c[4].unk1C = 0;
    g_16b2b3c[4].unk20 = 0;
    g_16b2b3c[4].unk24 = 0;

    g_16b2b3c[5].name  = SP_sHash(0);
    g_16b2b3c[5].type  = 0x14;
    g_16b2b3c[5].unk08 = 0;
    g_16b2b3c[5].val0  = PropValI(2);
    g_16b2b3c[5].val1  = PropValI(0);
    g_16b2b3c[5].index = 4;
    g_16b2b3c[5].defVal = PropValF(-1.0f);
    g_16b2b3c[5].unk1C = 0;
    g_16b2b3c[5].unk20 = 0;
    g_16b2b3c[5].unk24 = 0;

    g_16b2b3c[6].name  = SP_sHash(0);
    g_16b2b3c[6].type  = 0xffffffff;
    g_16b2b3c[6].unk08 = 0;
    g_16b2b3c[6].val0  = PropValI(0);
    g_16b2b3c[6].val1  = PropValI(0);
    g_16b2b3c[6].index = 0;
    g_16b2b3c[6].defVal = PropValI(0);
    g_16b2b3c[6].unk1C = 0;
    g_16b2b3c[6].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137af90  InitPropTable_16b2a24
// First default is the int 3.
// ---------------------------------------------------------------------------
void InitPropTable_16b2a24(void)
{
    g_16b2a24[0].name  = SP_sHash(0);
    g_16b2a24[0].type  = 4;
    g_16b2a24[0].unk08 = 0;
    g_16b2a24[0].val0  = PropValI(1);
    g_16b2a24[0].val1  = PropValI(0);
    g_16b2a24[0].index = 0;
    g_16b2a24[0].defVal = PropValI(3);
    g_16b2a24[0].unk1C = 8;
    g_16b2a24[0].unk20 = 0;
    g_16b2a24[0].unk24 = 0;

    g_16b2a24[1].name  = SP_sHash(0);
    g_16b2a24[1].type  = 0;
    g_16b2a24[1].unk08 = 0;
    g_16b2a24[1].val0  = PropValI(7);
    g_16b2a24[1].val1  = PropValI(0);
    g_16b2a24[1].index = 0;
    g_16b2a24[1].defVal = PropValI(0);
    g_16b2a24[1].unk1C = 0;
    g_16b2a24[1].unk20 = 0;
    g_16b2a24[1].unk24 = 0;

    g_16b2a24[2].name  = SP_sHash(0);
    g_16b2a24[2].type  = 8;
    g_16b2a24[2].unk08 = 0;
    g_16b2a24[2].val0  = PropValI(2);
    g_16b2a24[2].val1  = PropValI(0);
    g_16b2a24[2].index = 1;
    g_16b2a24[2].defVal = PropValF(-1.0f);
    g_16b2a24[2].unk1C = 0;
    g_16b2a24[2].unk20 = 0;
    g_16b2a24[2].unk24 = 0;

    g_16b2a24[3].name  = SP_sHash(0);
    g_16b2a24[3].type  = 0xc;
    g_16b2a24[3].unk08 = 0;
    g_16b2a24[3].val0  = PropValI(2);
    g_16b2a24[3].val1  = PropValI(0);
    g_16b2a24[3].index = 2;
    g_16b2a24[3].defVal = PropValF(-1.0f);
    g_16b2a24[3].unk1C = 0;
    g_16b2a24[3].unk20 = 0;
    g_16b2a24[3].unk24 = 0;

    g_16b2a24[4].name  = SP_sHash(0);
    g_16b2a24[4].type  = 0x10;
    g_16b2a24[4].unk08 = 0;
    g_16b2a24[4].val0  = PropValI(2);
    g_16b2a24[4].val1  = PropValI(0);
    g_16b2a24[4].index = 3;
    g_16b2a24[4].defVal = PropValF(-1.0f);
    g_16b2a24[4].unk1C = 0;
    g_16b2a24[4].unk20 = 0;
    g_16b2a24[4].unk24 = 0;

    g_16b2a24[5].name  = SP_sHash(0);
    g_16b2a24[5].type  = 0x14;
    g_16b2a24[5].unk08 = 0;
    g_16b2a24[5].val0  = PropValI(2);
    g_16b2a24[5].val1  = PropValI(0);
    g_16b2a24[5].index = 4;
    g_16b2a24[5].defVal = PropValF(-1.0f);
    g_16b2a24[5].unk1C = 0;
    g_16b2a24[5].unk20 = 0;
    g_16b2a24[5].unk24 = 0;

    g_16b2a24[6].name  = SP_sHash(0);
    g_16b2a24[6].type  = 0xffffffff;
    g_16b2a24[6].unk08 = 0;
    g_16b2a24[6].val0  = PropValI(0);
    g_16b2a24[6].val1  = PropValI(0);
    g_16b2a24[6].index = 0;
    g_16b2a24[6].defVal = PropValI(0);
    g_16b2a24[6].unk1C = 0;
    g_16b2a24[6].unk20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0137b270  InitPropTable_16b24d4
// First default is the int 4.
// ---------------------------------------------------------------------------
void InitPropTable_16b24d4(void)
{
    g_16b24d4[0].name  = SP_sHash(0);
    g_16b24d4[0].type  = 4;
    g_16b24d4[0].unk08 = 0;
    g_16b24d4[0].val0  = PropValI(1);
    g_16b24d4[0].val1  = PropValI(0);
    g_16b24d4[0].index = 0;
    g_16b24d4[0].defVal = PropValI(4);
    g_16b24d4[0].unk1C = 8;
    g_16b24d4[0].unk20 = 0;
    g_16b24d4[0].unk24 = 0;

    g_16b24d4[1].name  = SP_sHash(0);
    g_16b24d4[1].type  = 0;
    g_16b24d4[1].unk08 = 0;
    g_16b24d4[1].val0  = PropValI(7);
    g_16b24d4[1].val1  = PropValI(0);
    g_16b24d4[1].index = 0;
    g_16b24d4[1].defVal = PropValI(0);
    g_16b24d4[1].unk1C = 0;
    g_16b24d4[1].unk20 = 0;
    g_16b24d4[1].unk24 = 0;

    g_16b24d4[2].name  = SP_sHash(0);
    g_16b24d4[2].type  = 8;
    g_16b24d4[2].unk08 = 0;
    g_16b24d4[2].val0  = PropValI(2);
    g_16b24d4[2].val1  = PropValI(0);
    g_16b24d4[2].index = 1;
    g_16b24d4[2].defVal = PropValF(-1.0f);
    g_16b24d4[2].unk1C = 0;
    g_16b24d4[2].unk20 = 0;
    g_16b24d4[2].unk24 = 0;

    g_16b24d4[3].name  = SP_sHash(0);
    g_16b24d4[3].type  = 0xc;
    g_16b24d4[3].unk08 = 0;
    g_16b24d4[3].val0  = PropValI(2);
    g_16b24d4[3].val1  = PropValI(0);
    g_16b24d4[3].index = 2;
    g_16b24d4[3].defVal = PropValF(-1.0f);
    g_16b24d4[3].unk1C = 0;
    g_16b24d4[3].unk20 = 0;
    g_16b24d4[3].unk24 = 0;

    g_16b24d4[4].name  = SP_sHash(0);
    g_16b24d4[4].type  = 0x10;
    g_16b24d4[4].unk08 = 0;
    g_16b24d4[4].val0  = PropValI(2);
    g_16b24d4[4].val1  = PropValI(0);
    g_16b24d4[4].index = 3;
    g_16b24d4[4].defVal = PropValF(-1.0f);
    g_16b24d4[4].unk1C = 0;
    g_16b24d4[4].unk20 = 0;
    g_16b24d4[4].unk24 = 0;

    g_16b24d4[5].name  = SP_sHash(0);
    g_16b24d4[5].type  = 0x14;
    g_16b24d4[5].unk08 = 0;
    g_16b24d4[5].val0  = PropValI(2);
    g_16b24d4[5].val1  = PropValI(0);
    g_16b24d4[5].index = 4;
    g_16b24d4[5].defVal = PropValF(-1.0f);
    g_16b24d4[5].unk1C = 0;
    g_16b24d4[5].unk20 = 0;
    g_16b24d4[5].unk24 = 0;

    g_16b24d4[6].name  = SP_sHash(0);
    g_16b24d4[6].type  = 0xffffffff;
    g_16b24d4[6].unk08 = 0;
    g_16b24d4[6].val0  = PropValI(0);
    g_16b24d4[6].val1  = PropValI(0);
    g_16b24d4[6].index = 0;
    g_16b24d4[6].defVal = PropValI(0);
    g_16b24d4[6].unk1C = 0;
    g_16b24d4[6].unk20 = 0;
}
