// @ 0x011bdbf0  FUN_011bdbf0
//
// lib_cblock adapter: read the RIPEMD160_CTX* out of the holder's +0xc field and
// tail-call RIPEMD160_Update(ctx, data, len) at 0x011d1f30 (byte-matched by slice
// s011cf390/rmd_dgst.cpp).  The original is a 16-byte tail-call thunk; a plain C
// forwarder reproduces it exactly (cl 15 reuses the incoming argument slot and
// emits jmp).
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /Iscratch_s011bdbf0_inc  (see manifest.txt)

typedef struct {
    unsigned long A, B, C, D, E;
    unsigned long Nl, Nh;
    unsigned long data[16];
    unsigned int  num;
} RIPEMD160_CTX;

extern int RIPEMD160_Update(RIPEMD160_CTX *c, const void *data, unsigned long len);

typedef struct {
    char           pad[0xc];
    RIPEMD160_CTX *ctx;
} RIPEMD160_Holder;

int FUN_011bdbf0(RIPEMD160_Holder *p, const void *data, unsigned long len)
{
    return RIPEMD160_Update(p->ctx, data, len);
}
