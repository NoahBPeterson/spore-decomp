extern "C" unsigned char g_01419040[];
extern "C" unsigned char g_014190b0[];
extern "C" unsigned char g_014191d0[];
extern "C" void __cdecl FUN_00966f90(...);

extern "C" int __fastcall FUN_0081aa00(char* self)
{
    FUN_00966f90();
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_014191d0);
    *(unsigned int*)(((unsigned int)self) + 4) = ((unsigned int)g_014190b0);
    *(unsigned int*)(((unsigned int)self) + 524) = ((unsigned int)g_01419040);
    *(unsigned int*)(((unsigned int)self) + 2184) = -1;
    return ((unsigned int)self);
}
