extern "C" int __cdecl FUN_00a53310(unsigned int a_4, unsigned int a_8, unsigned int a_12)
{
    if (((int)(*(unsigned char*)(a_4 + 232)) == (int)(0))) goto L_00a53343;
    if (((int)(*(unsigned int*)(a_4 + 200)) == (int)(a_8))) goto L_00a53333;
    *(unsigned int*)(a_4 + 216) = -1;
L_00a53333:;
    *(unsigned int*)(a_4 + 200) = a_8;
    *(unsigned int*)(a_4 + 204) = a_12;
L_00a53343:;
    return a_4;
}
