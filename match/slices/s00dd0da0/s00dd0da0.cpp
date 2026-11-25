extern "C" unsigned char g_0147c9f8[];
extern "C" unsigned char g_0147cc78[];
extern "C" unsigned char g_0147cc88[];
extern "C" void __cdecl FUN_00dd0b50(...);

extern "C" int __fastcall FUN_00dd0da0(char* self)
{
    FUN_00dd0b50();
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_0147c9f8);
    *(unsigned int*)(((unsigned int)self) + 16) = ((unsigned int)g_0147cc88);
    *(unsigned int*)(((unsigned int)self) + 20) = ((unsigned int)g_0147cc78);
    return ((unsigned int)self);
}
