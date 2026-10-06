// Slice s008bb550 (batch big0) — 0x008bb550, 9760 bytes.
//
// PARTIAL. Module "EA-UTF" (work/xmatch/retail_lib.json).  The dev PDB gives this an
// anchor name `Type2BuildChar` — this is a TrueType/Type-2 charstring interpreter
// body (`tsi_*` helpers and a `Tell_InputStream` byte reader, `cff`/`cblock`
// vocabulary), 9.7 KB of /O2 code with a jump-table dispatch on the charstring
// operator.  Neighbour `008bb0d0 tsi_ParseCFFTopDict` and `008bdb70
// tsi_DeleteCFFClass` confirm the Type-2 interpreter.
//
// Signature from the prologue: `__cdecl`, 4 stack args; arg2 ([esp+0x54]) is the
// decoder/build context, whose +0x344/+0x348 are the instruction pointer / end.
// The operator dispatch is stubbed (needs the operand-stack opcode table first).
//
// Direct callee: Tell_InputStream(ctx)  (0x008cc5b0) — returns a pointer into the
// charstring; the interpreter advances it.
//
// @ 0x008bb550

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

extern "C" void* Tell_InputStream(void* ctx);   // 0x008cc5b0

struct T2Decoder {
    u8   pad0[0x344];
    u8*  ip;            // +0x344  current operand byte
    u8*  end;           // +0x348  end of charstring
    u8   pad_34c[0];
};

// @ 0x008bb550
void __cdecl Type2BuildChar(void* env, T2Decoder* dec, u32 charstring, int len)
{
    u8* p = (u8*)Tell_InputStream(dec) + len;
    (void)p; (void)charstring;

    // dec->ip walks the charstring; each byte selects an operator via the switch
    // table.  The interpreter operates on a fixed operand stack and the cff
    // "blend"/"hintmask" state in dec->+0x19c..+0x280.
    /* TODO: full charstring interpreter — dispatch on *dec->ip, handle the
     * number-encoding cases (32..255, 28, 255), the one/two-byte operators
     * (0x01 hstem, 0x03 vstem, 0x05 rlineto, 0x06 hlineto, ... 0x13 hintmask,
     * 0x0e endchar) and the subr/callsubr machinery. Needs the operand-stack
     * layout and the T2Decoder field offsets dumped first. */
}
