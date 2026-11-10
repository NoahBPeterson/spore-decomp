// Flags: /O2 /MD /Gy /TP
struct Elem20 { char mBytes[20]; };
void MoveRange(Elem20* first, Elem20* last, Elem20* dest); // 0x00951bf0

struct Vec20 {
    char mPad00[0x70];
    Elem20* mpBegin; // +0x70
    Elem20* mpEnd;   // +0x74
    void FUN_00c01310();
};

// @ 0x00c01310
void Vec20::FUN_00c01310()
{
    Elem20* begin = mpBegin;
    Elem20* end = mpEnd;
    MoveRange(end, end, begin);
    mpEnd -= end - begin;
}
