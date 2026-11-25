extern "C" unsigned char g_01481804[];

extern "C" int __fastcall FUN_00e2ec40(char* self)
{
    *(unsigned int*)(((unsigned int)self) + 4) = 0;
    *(unsigned int*)(((unsigned int)self)) = ((unsigned int)g_01481804);
    *(unsigned int*)(((unsigned int)self) + 8) = 0;
    return ((unsigned int)self);
}
