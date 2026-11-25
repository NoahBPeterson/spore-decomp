extern "C" int __cdecl FUN_00876e90(unsigned int a_4)
{
    if (((a_4 & a_4)) == 0) goto L_00876eac;
    if (((unsigned)(*(unsigned char*)(a_4 + 295)) >= (unsigned)(((unsigned char)(8))))) goto L_00876eac;
    *(unsigned int*)(a_4 + 112) = (*(unsigned int*)(a_4 + 112) | 4);
    *(unsigned char*)(a_4 + 296) = ((unsigned char)(8));
L_00876eac:;
    return a_4;
}
