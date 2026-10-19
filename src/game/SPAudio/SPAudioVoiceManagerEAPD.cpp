// src/game/SPAudio/SPAudioVoiceManagerEAPD.cpp -- migrated from slice(s) s00a459d0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioVoiceManagerEAPD.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" extern float g_13f1160;
extern "C" extern float g_13eb1bc;
extern "C" extern void* g_p16e61a8;   // DAT_016e61a8

// ---- items of slice s00a459d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class AudioSystem {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37();
    virtual void Call98(int a, int b);                       // +0x98
    virtual void Call9c(int a, int b, int c, float f, int e); // +0x9c
    virtual void v40(); virtual void v41();
    virtual char CallA8(int a, int b, int c, int d);          // +0xa8
    virtual char CallAC(int a, int b, float c, int d);        // +0xac
    virtual void v44();
    virtual void CallB4();                                    // +0xb4
};
extern "C" AudioSystem* GetSystemAT();
extern "C" extern float g_13f1160;
extern "C" extern float g_13eb1bc;
extern "C" extern void* g_p16e61a8;   // DAT_016e61a8
// ---- items of slice s00a459d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" AudioSystem* GetSystemAT();

// @ 0x00a45fd0
double GetAudioTime()
{
    double result = 0.0;
    if (g_p16e61a8)
        result = g_13f1160 / *(float*)((char*)g_p16e61a8 + 0xc0) +
                 *(double*)((char*)g_p16e61a8 + 8);
    return result;
}

// @ 0x00a45ff0
void __stdcall AudioFunc98(int a)
{
    AudioSystem* s = GetSystemAT();
    s->Call98(a, 0);
}

// @ 0x00a46010
void __stdcall AudioFunc9c(int a, int b)
{
    AudioSystem* s = GetSystemAT();
    s->Call9c(a, b, 0, g_13eb1bc, 1);
}

// @ 0x00a46040
bool __stdcall AudioCopyPtr(int a, int b, void** out)
{
    *out = (void*)a;
    return true;
}

// @ 0x00a46050
bool __stdcall AudioFuncAC(int a, int b, int c, float d)
{
    AudioSystem* s = GetSystemAT();
    return s->CallAC(a, b, d, 0) != 0;
}

// @ 0x00a46080
bool __stdcall AudioFuncA8(int a, int b, int c, int d, int e)
{
    AudioSystem* s = GetSystemAT();
    return s->CallA8(a, b, e, 0) != 0;
}

// @ 0x00a460b0
void AudioFuncB4()
{
    AudioSystem* s = GetSystemAT();
    s->CallB4();
}

// @ 0x00a46690
int __stdcall AtomCheckPtr(int* p, unsigned int n)
{
    if (p != 0) {
        if (n == 0)
            return 0;
        *p = 0x3f51892;
    }
    return 1;
}
