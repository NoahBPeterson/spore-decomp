extern "C" unsigned char g_01667bac[];
extern "C" unsigned char g_01667bae[];

extern "C" int __fastcall FUN_00b6a700(char* self)
{
    *(unsigned int*)(((unsigned int)self) + 4) = ((unsigned int)g_01667bac);
    *(unsigned int*)(((unsigned int)self) + 8) = ((unsigned int)g_01667bac);
    *(unsigned int*)(((unsigned int)self) + 12) = ((unsigned int)g_01667bae);
    return ((unsigned int)self);
}
