extern "C" int __cdecl FUN_00877c20(unsigned int a_4, unsigned int a_8)
{
    *(unsigned char*)(a_4) = ((unsigned char)(((unsigned int)(a_8) >> 24)));
    *(unsigned char*)(a_4 + 1) = ((unsigned char)(((unsigned int)(a_8) >> 16)));
    *(unsigned char*)(a_4 + 2) = ((unsigned char)(((unsigned int)(a_8) >> 8)));
    *(unsigned char*)(a_4 + 3) = ((unsigned char)(a_8));
    return a_8;
}
