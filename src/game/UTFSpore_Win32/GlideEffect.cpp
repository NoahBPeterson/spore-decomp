// src/game/UTFSpore_Win32/GlideEffect.cpp
// Object file: UTFSpore_Win32/GlideEffect.obj.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1442584[];
extern "C" char g_14425c0[];
extern "C" char g_14425d8[];
extern "C" char g_14426a0[];
extern "C" char g_14426bc[];

namespace EA {
namespace UTFWinControls {

// No canonical header declares these yet, so they are declared here by their retail addresses.
int   __cdecl FUN_009512c0();                                                  // 0x009512c0
void* __cdecl FUN_009512d0(int size, int align, const char* type, void* fac);  // 0x009512d0
void  __fastcall FadeEffect_ctor(void*);                                       // 0x00963db0

struct FloatSink {
    void Push(float* v);  // 0x0095e890
};

// Layout is partial: only the offsets this file touches are named (size 0x70).
// The vtable slots at +0x00, +0x04 and +0x0c are guesses at their owning bases.
class GlideEffect {
public:
    void* mVtbl00;                      // +0x00
    union {
        void* mVtbl04;                  // +0x04: the constructor stores a vtable pointer here
        float mSrcX;                    // +0x04: Set() stores src[0] here
    };
    float mSrcY;                        // +0x08: Set() stores src[1] here
    void* mVtbl0C;                      // +0x0c
    char  pad10[0x60 - 0x10];
    void* volatile mVtbl60;             // +0x60: the constructor stores two vtables here, in order
    float mScaleX;                      // +0x64
    float mScaleY;                      // +0x68

    void Set(float* src);                              // 0x00970060
    void Scale(void* unused, FloatSink* sink, float scale);  // 0x00970010
};

class BasicFactory_GlideEffect {
public:
    void* CreateInstance(int unused, void* allocator);  // 0x00970100
};

}  // namespace UTFWinControls
}  // namespace EA

namespace EA {
namespace UTFWinControls {

// Vtable addresses stored by the constructor, in the order the retail code writes them.
static const unsigned int kVtblBase60     = (int)g_14426a0;
static const unsigned int kVtblBase00     = (int)g_14425d8;
static const unsigned int kVtblBase04     = (int)g_14425c0;
static const unsigned int kVtblBase0C     = (int)g_1442584;
static const unsigned int kVtblFinal60    = (int)g_14426bc;

// @ 0x00970010
void GlideEffect::Scale(void*, FloatSink* sink, float scale)
{
    float local[3];
    local[0] = mScaleX * scale;
    local[1] = mScaleY * scale;
    local[2] = 0.0f;
    sink->Push(local);
}

// @ 0x00970060
void GlideEffect::Set(float* src)
{
    mSrcX = src[0];
    mSrcY = src[1];
}

// Constructor body. CreateInstance repeats these stores inline: moving them into a shared helper changes the
// retail codegen, so the two copies stay separate.

// @ 0x009700b0
void* __fastcall FUN_009700b0(char* self)
{
    FadeEffect_ctor(self);
    const float zero = 0.0f;
    *(void* volatile*)(self + 0x60) = (void*)kVtblBase60;
    *(void**)(self + 0x00) = (void*)kVtblBase00;
    *(void**)(self + 0x04) = (void*)kVtblBase04;
    *(void**)(self + 0x0c) = (void*)kVtblBase0C;
    *(void* volatile*)(self + 0x60) = (void*)kVtblFinal60;
    *(float*)(self + 0x64) = zero;
    *(float*)(self + 0x68) = zero;
    return self;
}

// @ 0x00970100
void* BasicFactory_GlideEffect::CreateInstance(int, void* allocator)
{
    if (allocator == 0)
        allocator = (void*)FUN_009512c0();
    char* obj = (char*)FUN_009512d0(0x70, 8,
                                    "UTFWin/EA::UTFWinControls::GlideEffect", allocator);
    if (obj != 0) {
        FadeEffect_ctor(obj);
        const float zero = 0.0f;
        *(void* volatile*)(obj + 0x60) = (void*)kVtblBase60;
        *(void**)(obj + 0x00) = (void*)kVtblBase00;
        *(void**)(obj + 0x04) = (void*)kVtblBase04;
        *(void**)(obj + 0x0c) = (void*)kVtblBase0C;
        *(void* volatile*)(obj + 0x60) = (void*)kVtblFinal60;
        *(float*)(obj + 0x64) = zero;
        *(float*)(obj + 0x68) = zero;
        return obj;
    }
    return 0;
}

}  // namespace UTFWinControls
}  // namespace EA
