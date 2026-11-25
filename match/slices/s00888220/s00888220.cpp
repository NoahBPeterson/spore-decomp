struct C_008880e0 { void FUN_008880e0(unsigned int); };

extern "C" int __fastcall FUN_00888220(char* self, int a_edx_dummy, unsigned int a_4)
{
    ((C_008880e0*)(((unsigned int)self)))->FUN_008880e0(a_4);
    return *(unsigned int*)(((unsigned int)self) + 24);
}
