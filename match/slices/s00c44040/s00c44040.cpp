// Flags: /O2 /MD /Gy /TP
extern "C" void* memmove_rw(void* dst, void* src, unsigned n); // 0x011e0744

struct Vec {
    char mPad00[0x490];
    int* mpBegin; // +0x490
    int* mpEnd;   // +0x494
    void FUN_00c44040();
};

// @ 0x00c44040
void Vec::FUN_00c44040()
{
    int* begin = mpBegin;
    int* end = mpEnd;
    memmove_rw(begin, end, (unsigned)((char*)mpEnd - (char*)end));
    mpEnd -= end - begin;
}
