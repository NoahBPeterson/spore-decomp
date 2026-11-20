// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// SP::Audio::cCityMusicViewer::cCityMusicViewer
#include <new>
//
// Rebuilt from the retail constructor at 0x00ea4a10 (202 bytes, 63 instructions).
// The viewer derives from Messaging::IHandler (primary vtable at +0) and
// EA::RefCountVTemplate<int> (secondary vtable at +4, reference count at +8).
// At +0xc sits the player-city-music config, and the tail holds the music
// pointers, the note editor (created last), the note-sound flag and the
// message-listener bookkeeping (see the sibling SetMusic at 0x00ea4f00).
//
// Instruction for instruction this build is retail's: the same three vptr
// stores (offsets 6/23/29, the two secondary-vtable writes to +4 bracketing the
// refcount clear), the config-constructor call, all twelve member stores, the
// six-argument operator_new (0x00f473a0, "Audio", size 0xc8), the null test
// with the placement-new branch, and the guarded AddRef/assign/Release block.
//
// The tail members are declared as the small sub-objects the /O2 scheduler
// actually sees.  Retail interleaves the six operator_new argument pushes with
// the zeroing stores:
//
//   41 mov [esi+0xd4],ebx   47 push ebx
//   48 mov [esi+0xd8],ebx   54 mov [esi+0xdc],ebx
//   60 push ebx             61 push ebx
//   62..80  mov [esi+0xe0..0xf4],ebx (0xf4 byte)
//   86 push ebx             87 push "Audio"   92 push 0xc8
//   97..126 mov [esi+0xf8..0x108],ebx       127 call operator_new
//
// With twelve flat members cl hoists the whole push group above every store
// (the object then carries the "Audio" relocation at offset 46..49, where
// retail has fixed bytes).  The pushes only split at the boundaries of inlined
// initialisers, so the members are grouped here exactly as retail clears them:
// +0xd4 alone, the music/editor pair, the three counters, the 8-byte unknown
// block with the note-sound flag, and the five listener fields.  With those
// boundaries the emitted store/push sequence is retail's byte for byte; every
// flag set, flat-member layout, allocation position and smart-pointer member
// type tried before only moved the diff around (see keep.md).

struct IFace {
    virtual void AddRef();      // slot 0
    virtual void Release();     // slot 1
};

struct IHandler {
    virtual void HandleMessage(int nMessage, void* pMessage);
};

// EA::RefCountVTemplate<int>: secondary vfptr at +4, refcount at +8.
struct RefCountVTemplateInt {
    RefCountVTemplateInt() : mRefCount(0) {}
    virtual void AddRef();
    virtual void Release();
    int mRefCount;
};

// A 4-byte refcounted-pointer member: its inlined constructor is one of the
// scheduling boundaries the retail build shows.
template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) {}
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p) { mpObject = p; return *this; }
};

// cPlayerCityMusicConfig (0x00eb19e0), 0xc8 bytes in retail.
struct PlayerCityMusicConfig {
    PlayerCityMusicConfig();
    unsigned char mData[0xc8];
};

// cCityMusicNoteEditor (0x00ea3c20), a 0xc8-byte refcounted object.
struct CityMusicNoteEditor : IFace {
    CityMusicNoteEditor(PlayerCityMusicConfig* pConfig);
};

void* operator_new(unsigned nSize, const char* pName, int a, int b, int c, int d);

// The viewer's mutable state, 0x0d8..0x10c.
struct MusicTrackRefs {                     // +0x0d8
    IFace*               mpMusic;           // +0x0d8
    CityMusicNoteEditor* mpNoteEditor;      // +0x0dc
    MusicTrackRefs() : mpMusic(0), mpNoteEditor(0) {}
};

struct MusicCounters {                      // +0x0e0
    unsigned             mUnkE0;            // +0x0e0
    unsigned             mUnkE4;            // +0x0e4
    unsigned             mUnkE8;            // +0x0e8
    MusicCounters() : mUnkE0(0), mUnkE4(0), mUnkE8(0) {}
};

struct UnknownBlock {                       // +0x0ec
    unsigned char        mUnkEC[0x08];      // +0x0ec (not touched by the ctor)
    unsigned char        mbNoteSoundsOn;    // +0x0f4
    unsigned char        mPadF5[0x03];      // +0x0f5
    UnknownBlock() : mbNoteSoundsOn(0) {}
};

// The message-server registration (see SetMusic at 0x00ea4f00).
struct ListenerRegistration {               // +0x0f8
    void*                mpServer;          // +0x0f8
    void*                mpOwner;           // +0x0fc
    unsigned             mnIds;             // +0x100
    unsigned             mnCount;           // +0x104
    unsigned             mnIndex;           // +0x108
    ListenerRegistration() : mpServer(0), mpOwner(0), mnIds(0), mnCount(0), mnIndex(0) {}
};

class cCityMusicViewer : public IHandler, public RefCountVTemplateInt {
public:
    cCityMusicViewer();

    PlayerCityMusicConfig mConfig;          // +0x00c (0xc8 bytes)
    AutoRefCount<IFace>   mpUnkD4;          // +0x0d4
    MusicTrackRefs        mMusic;           // +0x0d8
    MusicCounters         mCounters;        // +0x0e0
    UnknownBlock          mUnknown;         // +0x0ec
    ListenerRegistration  mListener;        // +0x0f8
};

// @ 0x00ea4a10
cCityMusicViewer::cCityMusicViewer()
    : mpUnkD4(0)
    , mMusic()
    , mCounters()
    , mUnknown()
    , mListener()
{
    CityMusicNoteEditor* pEditor;
    void* pMemory = operator_new(0xc8, "Audio", 0, 0, 0, 0);
    if (pMemory != 0)
        pEditor = new (pMemory) CityMusicNoteEditor(&mConfig);
    else
        pEditor = 0;

    CityMusicNoteEditor* pOldEditor = mMusic.mpNoteEditor;
    if (pEditor != pOldEditor) {
        if (pEditor != 0)
            pEditor->AddRef();
        mMusic.mpNoteEditor = pEditor;
        if (pOldEditor != 0)
            pOldEditor->Release();
    }
}
