// 0x00a46690: C++ lifted from retail's machine code by vs2005-cpp lift2il (the lifter alone); byte-exact.
// Machine-shaped on purpose: temporaries, casts and FUN_/g_ names by address. Hand-written source: src/game/SPAudio/SPAudioVoiceManagerEAPD.cpp, match/slices/s00a459d0/s00a459d0.cpp.

// @ 0x00a46690
extern "C" int __stdcall FUN_00a46690(int a4, int a8)
{
    int t1000;
    int t1001;
    t1000 = (int)((int)(a4));
    t1001 = (int)((int)0);
    if (t1000 != (int)0) {
        if ((unsigned int)((int)(a8)) <= (unsigned int)(t1001)) goto La466ab;
        *(int*)((char*)(t1000)) = (int)((int)66394258);
    }
    t1001 = (int)((int)1);
    La466ab:;
    return (int)(t1001);
}
