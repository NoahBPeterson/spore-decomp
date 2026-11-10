// Slice s0129e3a0: dynamic initializer that builds the 4x4 identity matrix on the stack
// and copies it into the global at 0x015f3ca0.
//
// Retail body (134 bytes):
//     sub esp,0x40; xorps xmm0,xmm0; movss xmm1,[g_01485720];
//     push esi; push edi; mov ecx,0x10; lea esi,[esp+8]; mov edi,<&g_015f3ca0>;
//     16x movss [esp+0x8 .. 0x44], ...; rep movsd; pop edi; pop esi; add esp,0x40; ret
// The temporary sits at esp+8 (struct temp above the saved esi/edi), the frame is padded to
// 0x40 on top of the 0x38 temporary, which is what the compiler does when it spills a
// struct temporary of 56 bytes (it rounds the object area up to 16) and copies it with
// rep movsd.
//
// NOT FOUND YET (see nonmatching.txt): stores straight into the global (the sibling
// initializer at 0x0129e890) fold to 16 direct `movss [global],xmm` (35 bytes), and
// `Matrix4 g_015f3ca0 = Matrix4().SetIdentity()` elides the temporary completely.  The
// body below is that plain-store form; it is the closest correct one found.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
extern const float g_01485720;
extern float g_015f3ca0;
extern float g_015f3ca4;
extern float g_015f3ca8;
extern float g_015f3cac;
extern float g_015f3cb0;
extern float g_015f3cb4;
extern float g_015f3cb8;
extern float g_015f3cbc;
extern float g_015f3cc0;
extern float g_015f3cc4;
extern float g_015f3cc8;
extern float g_015f3ccc;
extern float g_015f3cd0;
extern float g_015f3cd4;
extern float g_015f3cd8;
extern float g_015f3cdc;

// @ 0x0129e3a0
void FUN_0129e3a0() {
    g_015f3ca0 = g_01485720;
    g_015f3ca4 = 0.0f;
    g_015f3ca8 = 0.0f;
    g_015f3cac = 0.0f;
    g_015f3cb0 = 0.0f;
    g_015f3cb4 = g_01485720;
    g_015f3cb8 = 0.0f;
    g_015f3cbc = 0.0f;
    g_015f3cc0 = 0.0f;
    g_015f3cc4 = 0.0f;
    g_015f3cc8 = g_01485720;
    g_015f3ccc = 0.0f;
    g_015f3cd0 = 0.0f;
    g_015f3cd4 = 0.0f;
    g_015f3cd8 = 0.0f;
    g_015f3cdc = g_01485720;
}
