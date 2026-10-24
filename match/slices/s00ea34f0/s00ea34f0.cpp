// match/slices/s00ea34f0/s00ea34f0.cpp
// Object file: Simulator/SPCityMusicNoteEditor.obj - the note editor of the city
// music screen: its ctor/dtor, the per-frame Update, the layout rebuild
// (DoMessage) and the UTFWin message handler that drags notes around.
//
// Targets: 00ea34f0 00ea3ab0 00ea3b50 00ea3c20 00ea3d10 00ea3ed0
//          00ea3f10 00ea4250 00ea42c0
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//   Scalar float math is SSE (movss/mulss/divss) while every int -> float
//   conversion that feeds a division, and the note-geometry algebra, use x87
//   (fild/fdivp/fsubrp), exactly as VS2008 emits with /arch:SSE and /fp:fast.
//
// The editor keeps three parallel note-layout vectors (one per row group); each
// element is a refcounted UI layout pointer (AutoRefCount<cSPUILayout>) and the
// containers keep the real three-pointer shape so the eastl insert / erase
// idioms stay readable.

#include <string.h>

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;

// ---------------------------------------------------------------------------
// vtables (the class's own vptr stores are modelled by hand)
// ---------------------------------------------------------------------------
extern void* vtEditorMain[];      // 0x014872c0
extern void* vtEditorRefCount[];  // 0x014872b0
extern void* vtEditorBase[];      // 0x013eb938
extern void* vtRefCountBase[];    // 0x013ec458

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------
template <class T> const T& MinRef(const T& a, const T& b) { return a < b ? a : b; }
template <class T> const T& MaxRef(const T& a, const T& b) { return a < b ? b : a; }

struct Vec2 { float x, y; };

// resource key (three dwords: type, group and name hash)
struct ResKey {
  u32 mType_00;
  u32 mGroup_04;
  u32 mName_08;
};

// one element of the note-layout vectors: a refcounted UI layout pointer
struct RefElem {
  struct cUILayout* mpObject;
};

void*  __cdecl operator new(unsigned int size);
void   __cdecl operator_delete_array(void* p);                             // 0x00f47380
void*  __cdecl EAAlloc(u32 size, const char* area, int, int,
                       const char* file, int line);                        // 0x00f473a0
void*  __cdecl operator new(unsigned int size, const char* area,
                            int, int, int, int);                           // tagged operator new
void*  __cdecl memcpy(void* dst, const void* src, unsigned int size);

void __cdecl uninitialized_copy_RefElem(RefElem* first, RefElem* last, RefElem* dst);  // 0x01022c60
void __cdecl copy_backward_ool(RefElem* first, RefElem* last, RefElem* dst);           // 0x005c1dc0
void __cdecl fill_ool(RefElem* first, RefElem* last, const RefElem& value);            // 0x00657f20
void __cdecl uninitialized_fill_n_ref(RefElem* first, u32 n, const RefElem& value);    // 0x005769d0

// ---------------------------------------------------------------------------
// EA::Stopwatch - four dwords; the first two are zero while it is not running
// ---------------------------------------------------------------------------
struct Stopwatch {
  union {
    struct {
      u32 mUnits_00;              // 0x00
      u32 mCoeff_04;              // 0x04
    };
    long long mRunning_00;        // both dwords zero while it is not running
  };
  u32 mStartTime_08;              // 0x08
  u32 mElapsed_0c;                // 0x0c
  void Init(s32 units, bool b);                            // 0x0093a560
  void Restart();                                          // 0x00571e80
  void StopTimer();                                        // 0x0093a2e0
  long long GetElapsedTime();                              // 0x0093a5e0
  bool IsStopped() const { return mRunning_00 == 0; }
};

// ---------------------------------------------------------------------------
// UTFWin UI layout (only the members this translation unit touches)
// ---------------------------------------------------------------------------
struct cUILayout {
  void** mpVtbl_00;               // 0x00

  // vtable slots used here (slot n == byte offset 4*n)
  u32         GetID()      { return ((u32  (__thiscall*)(cUILayout*))mpVtbl_00[7])(this); }   // +0x1c
  u32         GetFlags()   { return ((u32  (__thiscall*)(cUILayout*))mpVtbl_00[10])(this); }  // +0x28
  u32         GetIndex()   { return ((u32  (__thiscall*)(cUILayout*))mpVtbl_00[8])(this); }   // +0x20
  cUILayout*  GetChild()   { return ((cUILayout* (__thiscall*)(cUILayout*))mpVtbl_00[4])(this); } // +0x10
  cUILayout*  FindChildWindow(u32 id)
      { return ((cUILayout* (__thiscall*)(cUILayout*, u32))mpVtbl_00[3])(this, id); }         // +0x0c
  float*      GetRect4()   { return ((float* (__thiscall*)(cUILayout*))mpVtbl_00[13])(this); }  // +0x34
  float*      GetRect()    { return ((float* (__thiscall*)(cUILayout*))mpVtbl_00[14])(this); }  // +0x38
  void        SetNoteIndex(u32 index)
      { ((void (__thiscall*)(cUILayout*, u32))mpVtbl_00[21])(this, index); }                  // +0x54
  void        SetEditor(void* editor)
      { ((void (__thiscall*)(cUILayout*, void*))mpVtbl_00[65])(this, editor); }               // +0x104
  void        ToLocal(Vec2* out, float x, float y)
      { ((void (__thiscall*)(cUILayout*, Vec2*, float, float))mpVtbl_00[48])(this, out, x, y); } // +0xc0
  float*      Transform(Vec2* out, float x, float y)
      { return ((float* (__thiscall*)(cUILayout*, Vec2*, float, float))mpVtbl_00[49])(this, out, x, y); } // +0xc4
  void        AddRef()  { ((void (__thiscall*)(cUILayout*))mpVtbl_00[1])(this); }             // +0x04
  void        Release() { ((void (__thiscall*)(cUILayout*))mpVtbl_00[2])(this); }             // +0x08

  void Construct();                                              // 0x00810000
  bool Init(const ResKey& key, bool flag, u32 name);             // 0x008120d0
  bool SetParentWin(cUILayout* parent, bool flag, u32 name);     // 0x008121b0
  void SetVisibility(bool visible);                              // 0x00810590
  cUILayout* FindWindowByID(u32 id, s32 flag);                   // 0x008105b0
};

struct cWindowManager;

cWindowManager* __cdecl WindowManager();                          // 0x0067caa0

struct cWindowManager {                    // only the vtable slots this file calls
  void** mpVtbl_00;
  void ShowWindow58(s32 a, cUILayout* w)
      { ((void (__thiscall*)(cWindowManager*, s32, cUILayout*))mpVtbl_00[22])(this, a, w); }  // +0x58
  void ShowWindow5c(s32 a, cUILayout* w)
      { ((void (__thiscall*)(cWindowManager*, s32, cUILayout*))mpVtbl_00[23])(this, a, w); }  // +0x5c
  void SetTimerValue(s32 a, s32 value)
      { ((void (__thiscall*)(cWindowManager*, s32, s32))mpVtbl_00[19])(this, a, value); }     // +0x4c
};

// ---------------------------------------------------------------------------
// music configuration / player
// ---------------------------------------------------------------------------
struct cPlayerCityMusicConfig {
  u8          mPad_00[0x14];
  s32         mNoteCount_14;      // 0x14  number of notes per row group
  u8          mPad_18[0x04];
  float       mBeatStep_1c;       // 0x1c  beat distance step
  float       mBeatMax_20;        // 0x20  largest beat distance
  s32         mWheelIncrement_24; // 0x24  mouse wheel unit
  const void* mpBeatUpKey_28;     // 0x28
  const void* mpBeatDownKey_2c;   // 0x2c
  u8          mPad_30[0x2c];
  u32         mRangeMin_5c;       // 0x5c
  u32         mRangeMax_60;       // 0x60
  u8          mPad_64[0x4c];
  u32         mWheelDelay_b0;     // 0xb0  wheel time-out in timer units
};

// a note cell: the same slot is read as a float pitch and compared as bits
union NoteCell {
  u32   mBits;
  float mValue;
};

struct cPlayerCityMusic {
  void**    mpVtbl_00;            // 0x00
  u8        mPad_04[0x154];
  u32       mActiveNoteId_158;    // 0x158
  u32       mTempoBits_15c;       // 0x15c  tempo value forwarded to SetTempo
  u8        mPad_160[0x6c];
  NoteCell* mpNoteCells_1cc;      // 0x1cc  per-note drag cell
  u8        mPad_1d0[0x10];
  float*    mpNotePitches_1e0;    // 0x1e0  per-note pitch
  void PlayNote(u32 note);                                   // 0x00eacf10
  void RemoveNote(u32 note);                                 // 0x00eae610
  void MoveNote(u32 from, u32 to);                           // 0x00eaf8d0
  void SetNotePitch(u32 note, s32 pitch);                    // 0x00ead870
  void SetNoteDuration(u32 note, float duration);            // 0x00ead0c0
  void AddUndoState();                                       // 0x00eb1170
  float FUN_00ead040();                                      // 0x00ead040
  void FUN_00eacf70(s32 a);                                  // 0x00eacf70
  void Release() { ((void (__thiscall*)(cPlayerCityMusic*))mpVtbl_00[1])(this); }
};

// ---------------------------------------------------------------------------
// note-layout vector (eastl::sp_ref_vector<AutoRefCount<cSPUILayout>>)
// ---------------------------------------------------------------------------
struct cNoteVec {
  RefElem* mpBegin_00;            // 0x00
  RefElem* mpEnd_04;              // 0x04
  RefElem* mpCap_08;              // 0x08
  u32      mAlloc_0c;             // 0x0c
  u32      mAlloc2_10;            // 0x10
  RefElem* Erase(RefElem* first, RefElem* last);              // 0x005c2170
  void     Insert(RefElem* pos, u32 count, RefElem* value);    // 0x00ea3d10
};

// ---------------------------------------------------------------------------
// the editor
// ---------------------------------------------------------------------------
struct cCityMusicNoteEditor {
  void**  mpVtbl_00;              // 0x00
  void**  mpVtblRefCount_04;      // 0x04  base refcount vtable
  u32     mRefCount_08;           // 0x08
  cPlayerCityMusicConfig* mConfig_0c;  // 0x0c
  cPlayerCityMusic* mpMusic_10;   // 0x10
  cUILayout*      mpLayout_14;    // 0x14
  cNoteVec        mNoteLayouts_18[3];  // 0x18 .. 0x53
  u8      mEditMode_54;           // 0x54  edit (1) / play (0) layout
  u8      mField_55;              // 0x55  constant 1
  u32     mField_58;              // 0x58  zeroed, unused here
  u32     mField_5c;              // 0x5c
  u32     mField_60;              // 0x60
  float   mOutline_64[4];         // 0x64  note outline {-w,-h,+w,+h}
  float   mfNoteWidth_74;         // 0x74
  float   mfNoteHeight_78;        // 0x78
  float   mfGridLeft_7c;          // 0x7c  pitch grid origin
  float   mfSpacingX_80;          // 0x80  horizontal note spacing
  float   mfSpacingY_84;          // 0x84  vertical note spacing
  float   mfRowHeight_88;         // 0x88  vertical step per pitch degree
  u32     mMovingNoteId_8c;       // 0x8c  dragged note + 1 (0 = none)
  u8      mInitialNote_90;        // 0x90
  float   mInitialPitch_94;       // 0x94
  float   mfInitialDuration_98;   // 0x98
  u32     mLastIndex_9c;          // 0x9c
  NoteCell mDragCell_a0;          // 0xa0
  float   mfWheelStart_a4;        // 0xa4
  float   mfWheelCurrent_a8;      // 0xa8
  u32     mPad_ac;                // 0xac
  Stopwatch mWheelTimer_b0;       // 0xb0

  cCityMusicNoteEditor(cPlayerCityMusicConfig* config);      // 0x00ea3c20
  void Destroy();                                            // 0x00ea3ab0
  void Update();                                             // 0x00ea3b50
  void ResetNoteLayouts();                                   // 0x00ea3ed0
  void DoMessage();                                          // 0x00ea3f10
  bool SetLayoutAndRebuild(cUILayout* layout, bool editMode); // 0x00ea4250
  bool OnMessage(s32 eventId, struct Msg* msg);              // 0x00ea34f0
  void SetSoundProperty(u32 value);                          // 0x00ea3040
  void LoopMelody();                                         // 0x00ea3120
  void SetTempo(u32 tempo);                                  // 0x00ea2f40
  void SetActiveNoteId(u32 id);                              // 0x00ea3390
  void FastRoundToInt23(u32 note, float value);              // 0x00ea2da0
};

// static member of the editor: cdecl, called with (parentWindow, flag)
void __cdecl RedrawNoteDuration(cUILayout* parent, bool flag);  // 0x00ea30b0

// ---------------------------------------------------------------------------
// UTFWin message (only the fields the handler reads)
// ---------------------------------------------------------------------------
union MsgValue {
  float mFloat;
  u32   mUInt;
  void* mPtr;
};

struct Msg {
  u32        mField_00;           // 0x00
  cUILayout* mpSender_04;         // 0x04
  u32        mType_08;            // 0x08  message type
  MsgValue   mValueA_0c;          // 0x0c  payload (float / int / key)
  MsgValue   mValueB_10;          // 0x10  payload (float / int / key)
  u32        mField_14;           // 0x14
  s32        mParam_18;           // 0x18  integer payload
};

// key table of the three note rows
extern u32 gNoteLayoutKeys[3];    // 0x014872a4

// forward declarations of the out-of-line members used before definition
void cCityMusicNoteEditor_SetSoundPropertyDummy();

// ===========================================================================
// 0x00ea42c0 - build one declared parameter of the functional match and push it
// onto the parameter vector when the key type matches
// ===========================================================================
struct MatchParam {
  u32 mType_00;
  u32 mGroup_04;
  u32 mName_08;
};

struct ParamVec {
  MatchParam* mpBegin_00;
  MatchParam* mpEnd_04;
  MatchParam* mpCap_08;
  void DoInsertKey(MatchParam* pos, const MatchParam& value);  // 0x004e3e10
  void Insert(const MatchParam& value)
  {
    MatchParam* slot = mpEnd_04;
    if (slot < mpCap_08) {
      mpEnd_04 = slot + 1;
      if (slot)
        *slot = value;
    } else {
      DoInsertKey(slot, value);
    }
  }
};

struct DeclareParam {
  MatchParam mParam_00;
  DeclareParam(u32 group, u32 type);                           // 0x00558bc0
};

// @ 0x00ea42c0
bool __stdcall FUN_00ea42c0(const MatchParam* param, ParamVec* vec)
{
  bool matches = param->mGroup_04 == 0x4f684a4;
  if (matches)
    vec->Insert(DeclareParam(0x2dc9d1e, 0x4f684a4).mParam_00);
  return matches;
}

// ===========================================================================
// 0x00ea3c20 - constructor
// ===========================================================================
// @ 0x00ea3c20
cCityMusicNoteEditor::cCityMusicNoteEditor(cPlayerCityMusicConfig* config)
{
  mpVtblRefCount_04 = vtRefCountBase;
  mRefCount_08 = 0;
  mConfig_0c = config;
  mpVtbl_00 = vtEditorMain;
  mpVtblRefCount_04 = vtEditorRefCount;
  mpMusic_10 = 0;
  mpLayout_14 = 0;
  for (s32 i = 0; i < 3; ++i) {
    mNoteLayouts_18[i].mpBegin_00 = 0;
    mNoteLayouts_18[i].mpEnd_04 = 0;
    mNoteLayouts_18[i].mpCap_08 = 0;
  }
  mEditMode_54 = 0;
  mField_55 = 1;
  mField_58 = 0;
  mField_5c = 0;
  mField_60 = 0;
  mfNoteWidth_74 = 0.0f;
  mfNoteHeight_78 = 0.0f;
  mfGridLeft_7c = 0.0f;
  mfSpacingX_80 = 0.0f;
  mfSpacingY_84 = 0.0f;
  mfRowHeight_88 = 0.0f;
  mMovingNoteId_8c = 0;
  mInitialNote_90 = 0;
  mInitialPitch_94 = 0.0f;
  mfInitialDuration_98 = 0.0f;
  mLastIndex_9c = 0;
  mDragCell_a0.mBits = 0;
  mfWheelStart_a4 = 0.0f;
  mfWheelCurrent_a8 = 0.0f;
  mWheelTimer_b0.Init(4, false);
}

// ===========================================================================
// 0x00ea3ab0 - destructor body: release the three note-layout rows and the two
// refcounted members, then install the base-class vtables
// ===========================================================================
// @ 0x00ea3ab0
void cCityMusicNoteEditor::Destroy()
{
  mpVtbl_00 = vtEditorMain;
  mpVtblRefCount_04 = vtEditorRefCount;
  for (s32 i = 2; i >= 0; --i) {
    cNoteVec& row = mNoteLayouts_18[i];
    RefElem* end = row.mpEnd_04;
    RefElem* elem = row.mpBegin_00;
    for (; elem < end; ++elem) {
      if (elem->mpObject)
        elem->mpObject->Release();
    }
    if (row.mpBegin_00)
      operator_delete_array(row.mpBegin_00);
  }
  if (mpLayout_14)
    mpLayout_14->Release();
  if (mpMusic_10)
    mpMusic_10->Release();
  mpVtbl_00 = vtEditorBase;
  mpVtblRefCount_04 = vtRefCountBase;
}

// ===========================================================================
// 0x00ea3b50 - per-frame update: refresh tempo/active note, the note-length
// readout and the mouse-wheel time-out undo state
// ===========================================================================
// @ 0x00ea3b50
void cCityMusicNoteEditor::Update()
{
  SetTempo(mpMusic_10->mTempoBits_15c);
  SetActiveNoteId(mpMusic_10->mActiveNoteId_158);

  cUILayout* window = mpLayout_14->FindWindowByID(0x508dc80, 1);
  if (window) {
    cUILayout* bar = window->FindChildWindow(0x10edf11);
    if (bar) {
      void** barVtbl = bar->mpVtbl_00;
      float value = mpMusic_10->FUN_00ead040() * 100.0f;
      ((void (__thiscall*)(cUILayout*, float))barVtbl[1])(bar, value);
    }
  }

  if (!mWheelTimer_b0.IsStopped()) {
    long long elapsed = mWheelTimer_b0.GetElapsedTime();
    if ((unsigned long long)elapsed > (unsigned long long)mConfig_0c->mWheelDelay_b0) {
      mWheelTimer_b0.StopTimer();
      if (mfWheelStart_a4 != mfWheelCurrent_a8)
        mpMusic_10->AddUndoState();
    }
  }
}

// ===========================================================================
// 0x00ea3ed0 - drop every note layout and the active note
// ===========================================================================
// @ 0x00ea3ed0
void cCityMusicNoteEditor::ResetNoteLayouts()
{
  if (mpMusic_10)
    mpMusic_10->FUN_00eacf70(0);
  mField_60 = 0;
  for (s32 i = 0; i < 3; ++i) {
    cNoteVec& row = mNoteLayouts_18[i];
    row.Erase(row.mpBegin_00, row.mpEnd_04);
  }
}

// ===========================================================================
// 0x00ea3d10 - insert `count` copies of `value` at `pos` in a note-layout row
// (eastl::sp_ref_vector::insert)
// ===========================================================================
// @ 0x00ea3d10
void cNoteVec::Insert(RefElem* pos, u32 count, RefElem* value)
{
  if ((u32)(mpCap_08 - mpEnd_04) < count) {
    u32 used = (u32)(mpEnd_04 - mpBegin_00);
    u32 growth = used * 2;
    if (used == 0)
      growth = 1;
    u32 capacity = used + count;
    if (capacity < growth)
      capacity = growth;

    RefElem* buffer = 0;
    if (capacity != 0)
      buffer = (RefElem*)EAAlloc(capacity * sizeof(RefElem), "Simulator", 0, 0,
                                 "eastl/allocator.h", 0xd1);

    u32 head = (u32)(pos - mpBegin_00);
    memcpy(buffer, mpBegin_00, head * sizeof(RefElem));
    RefElem* middle = buffer + head;
    uninitialized_fill_n_ref(middle, count, *value);
    RefElem* tail = middle + count;
    memcpy(tail, pos, (u32)(mpEnd_04 - pos) * sizeof(RefElem));
    if (mpBegin_00)
      operator_delete_array(mpBegin_00);
    mpBegin_00 = buffer;
    mpEnd_04 = tail + (mpEnd_04 - pos);
    mpCap_08 = buffer + capacity;
  } else if (count != 0) {
    RefElem item = *value;
    if (item.mpObject)
      item.mpObject->AddRef();

    u32 tailCount = (u32)(mpEnd_04 - pos);
    if (count < tailCount) {
      RefElem* split = mpEnd_04 - count;
      uninitialized_copy_RefElem(split, mpEnd_04, mpEnd_04);
      mpEnd_04 += count;
      copy_backward_ool(pos, split, mpEnd_04);
      fill_ool(pos, pos + count, item);
    } else {
      uninitialized_fill_n_ref(mpEnd_04, count - tailCount, item);
      mpEnd_04 += count - tailCount;
      uninitialized_copy_RefElem(pos, mpEnd_04 - (count - tailCount), mpEnd_04);
      mpEnd_04 += tailCount;
      fill_ool(pos, pos + tailCount, item);
    }
    if (item.mpObject)
      item.mpObject->Release();
  }
}

// ===========================================================================
// 0x00ea3f10 - rebuild every note layout from the configuration (DoMessage)
// ===========================================================================
// @ 0x00ea3f10
void cCityMusicNoteEditor::DoMessage()
{
  cUILayout* parent = mpLayout_14->FindWindowByID(0x41918a2, 1);
  ResKey key;
  key.mType_00 = 0;
  key.mGroup_04 = 0x510a95b;
  key.mName_08 = 0x40464100;

  for (u32 group = 0; group < 3; ++group) {
    s32 noteCount = mConfig_0c->mNoteCount_14;
    cNoteVec& row = mNoteLayouts_18[group];

    if ((u32)(row.mpEnd_04 - row.mpBegin_00) < (u32)noteCount) {
      RefElem empty;
      empty.mpObject = 0;
      row.Insert(row.mpEnd_04,
                 (u32)noteCount - (u32)(row.mpEnd_04 - row.mpBegin_00), &empty);
    } else {
      row.Erase(row.mpBegin_00 + noteCount, row.mpEnd_04);
    }

    key.mType_00 = gNoteLayoutKeys[group];
    for (u32 i = 0; i < (u32)mConfig_0c->mNoteCount_14; ++i) {
      cUILayout* window = (cUILayout*)operator new(0x18, "Audio", 0, 0, 0, 0);
      if (window) {
        window->Construct();
      }
      RefElem* slot = &row.mpBegin_00[i];
      cUILayout* previous = slot->mpObject;
      if (window != previous) {
        if (window)
          window->AddRef();
        slot->mpObject = window;
        if (previous)
          previous->Release();
      }
      window->Init(key, false, 0x5b598fa);

      if (mEditMode_54 != 0 && group == 2) {
        cUILayout* noteWindow = window->FindWindowByID(0x4506b88, 1);
        noteWindow->SetNoteIndex(i);
        noteWindow->SetEditor(this);
      } else if (group == 1 && i == 0) {
        float* outerRect = parent->GetRect();
        cUILayout* noteRectWindow = window->FindWindowByID(0x4515bb0, 1);
        float* noteRect = noteRectWindow->GetRect();
        cUILayout* noteBoxWindow = window->FindWindowByID(0x4506b98, 1);
        float* noteBox = noteBoxWindow->GetRect4();

        mOutline_64[0] = noteBox[0];
        mOutline_64[1] = noteBox[1];
        mOutline_64[2] = noteBox[2];
        mOutline_64[3] = noteBox[3];

        float ratioX = mOutline_64[2] / (noteRect[2] - noteRect[0]);
        float ratioY = mOutline_64[3] / (noteRect[3] - noteRect[1]);
        float count = (float)(u32)mConfig_0c->mNoteCount_14;

        mfSpacingX_80 = (outerRect[2] - outerRect[0]) / (count + ratioX * 2.0f);
        mfNoteWidth_74 = mfSpacingX_80 * ratioX;
        mfSpacingY_84 = ((noteRect[3] - noteRect[1]) * mfSpacingX_80)
                        / (noteRect[2] - noteRect[0]);
        mfNoteHeight_78 = mfSpacingY_84 * ratioY;

        mOutline_64[2] = mfNoteWidth_74;
        mOutline_64[3] = mfNoteHeight_78;
        mOutline_64[0] = -mfNoteWidth_74;
        mOutline_64[1] = -mfNoteHeight_78;

        u32 range = mConfig_0c->mRangeMax_60 - mConfig_0c->mRangeMin_5c;
        float rangeF = (float)(u32)range;
        mfRowHeight_88 = (((outerRect[3] - outerRect[1]) - mfNoteHeight_78 * 2.0f)
                          - mfSpacingY_84) / rangeF;
      }

      window->SetParentWin(parent, true, 0x5b598fa);
      window->SetVisibility(false);
    }
  }

  if (mEditMode_54 == 0) {
    RedrawNoteDuration(parent, false);
  } else {
    ((void (__thiscall*)(cUILayout*, void*))((void**)parent->mpVtbl_00)[65])(parent, this);
  }
}

// ===========================================================================
// 0x00ea4250 - swap the layout, store the edit flag and rebuild the notes
// ===========================================================================
// @ 0x00ea4250
bool cCityMusicNoteEditor::SetLayoutAndRebuild(cUILayout* layout, bool editMode)
{
  cUILayout* old = mpLayout_14;
  if (layout != old) {
    if (layout)
      layout->AddRef();
    mpLayout_14 = layout;
    if (old)
      old->Release();
  }
  mEditMode_54 = editMode;
  DoMessage();
  return true;
}

// ===========================================================================
// 0x00ea34f0 - UTFWin message handler
//
//   1/9  wheel or beat key: lengthen/shorten the active note
//   6    start dragging the note under the cursor
//   7    drop the dragged note
//   8    move the dragged note to the snapped grid position
//   10   show the wheel time-out in the timer window
// ===========================================================================
// @ 0x00ea34f0
bool cCityMusicNoteEditor::OnMessage(s32 eventId, Msg* msg)
{
  bool handled = false;
  switch (msg->mType_08) {
  case 1:
  case 9: {
    cUILayout* sender = msg->mpSender_04;
    if (sender->GetID() != 0x4506b88)
      return false;

    s32 delta = 0;
    if (msg->mType_08 == 9) {
      delta = msg->mParam_18 / mConfig_0c->mWheelIncrement_24;
    } else if (msg->mValueB_10.mPtr == mConfig_0c->mpBeatUpKey_28) {
      delta = 1;
    } else if (msg->mValueB_10.mPtr == mConfig_0c->mpBeatDownKey_2c) {
      delta = -1;
    }
    handled = delta != 0;
    if (!handled)
      return false;

    u32 note = sender->GetIndex();
    float base = mpMusic_10->mpNotePitches_1e0[note];
    if (mWheelTimer_b0.IsStopped())
      mfWheelStart_a4 = base;
    mWheelTimer_b0.Restart();

    float value = (float)delta * mConfig_0c->mBeatStep_1c + base;
    value = MaxRef(MinRef(value, mConfig_0c->mBeatMax_20),
                   mConfig_0c->mBeatStep_1c);
    mfWheelCurrent_a8 = value;
    if (value != base) {
      mpMusic_10->SetNoteDuration(note, value);
      FastRoundToInt23(note, value);
    }
    return handled;
  }
  case 6: {
    if (mMovingNoteId_8c != 0)
      return false;
    cUILayout* sender = msg->mpSender_04;
    if (sender->GetID() != 0x4506b88)
      return false;
    if ((sender->GetFlags() & 2) == 0)
      return false;

    handled = true;
    u32 note = sender->GetIndex();
    mLastIndex_9c = note;
    mDragCell_a0 = mpMusic_10->mpNoteCells_1cc[note];
    mMovingNoteId_8c = note + 1;

    Vec2 local;
    sender->ToLocal(&local, msg->mValueA_0c.mFloat, msg->mValueB_10.mFloat);
    cUILayout* child = sender->GetChild();
    Vec2 out;
    float* pitch = child->Transform(&out, local.x, local.y);
    mInitialPitch_94 = pitch[0];
    mfInitialDuration_98 = pitch[1];

    WindowManager()->ShowWindow58(1, mpLayout_14->FindWindowByID(0x41918a2, 1));
    if (msg->mParam_18 != 1000)
      return handled;

    SetSoundProperty(0);
    mpMusic_10->PlayNote(mLastIndex_9c);
    mInitialNote_90 = 1;
    return handled;
  }
  case 7: {
    if (mMovingNoteId_8c == 0)
      return false;
    cUILayout* sender = msg->mpSender_04;
    if (sender->GetID() != 0x41918a2)
      return false;

    u32 note = mMovingNoteId_8c - 1;
    handled = true;
    if (note != mLastIndex_9c
        || mpMusic_10->mpNoteCells_1cc[note].mBits != mDragCell_a0.mBits)
      mpMusic_10->AddUndoState();
    mMovingNoteId_8c = 0;
    WindowManager()->ShowWindow5c(1, mpLayout_14->FindWindowByID(0x41918a2, 1));
    if (mInitialNote_90) {
      SetSoundProperty(1);
      mInitialNote_90 = 0;
    }
    return handled;
  }
  case 8: {
    if (mMovingNoteId_8c == 0)
      return false;
    cUILayout* sender = msg->mpSender_04;
    if (sender->GetID() != 0x41918a2)
      return false;

    handled = true;
    u32 note = mMovingNoteId_8c - 1;
    float* rect = sender->GetRect();
    float mouseX = msg->mValueA_0c.mFloat;
    float mouseY = msg->mValueB_10.mFloat;
    float width = rect[2] - rect[0];
    float height = rect[3] - rect[1];

    if (mouseX >= 0.0f && mouseY >= 0.0f && width > mouseX && height > mouseY) {
      float limitX = (width - mfSpacingX_80) - mfGridLeft_7c;
      float limitY = (height - mfSpacingY_84) - mfNoteHeight_78;
      float offsetX = mouseX - mInitialPitch_94;
      float offsetY = mouseY - mfInitialDuration_98;

      float snappedX = MaxRef(MinRef(offsetX, limitX), mfGridLeft_7c);
      float snappedY = MaxRef(MinRef(offsetY, limitY), mfNoteHeight_78);

      s32 newNote = (s32)((snappedX - mfGridLeft_7c) / mfSpacingX_80);
      bool moved = false;
      if (note != (u32)newNote) {
        mpMusic_10->MoveNote(note, (u32)newNote);
        note = (u32)newNote;
        mMovingNoteId_8c = (u32)newNote + 1;
        moved = true;
      }

      s32 pitch = (s32)mConfig_0c->mRangeMax_60
                  - (s32)((snappedY - mfNoteHeight_78) / mfRowHeight_88);
      if (mpMusic_10->mpNoteCells_1cc[note].mBits != (u32)pitch) {
        mpMusic_10->SetNotePitch(note, pitch);
        if (mInitialNote_90) {
          mpMusic_10->PlayNote(note);
          LoopMelody();
          return handled;
        }
      } else if (!moved) {
        return handled;
      }
      LoopMelody();
      return handled;
    }

    mpMusic_10->RemoveNote(note);
    LoopMelody();
    mpMusic_10->AddUndoState();
    mMovingNoteId_8c = 0;
    WindowManager()->ShowWindow5c(1, mpLayout_14->FindWindowByID(0x41918a2, 1));
    if (mInitialNote_90) {
      SetSoundProperty(1);
      mInitialNote_90 = 0;
    }
    return handled;
  }
  case 10: {
    if (msg->mValueA_0c.mUInt != 1)
      return handled;
    cUILayout* sender = msg->mpSender_04;
    if (sender->GetID() != 0x4506b88)
      return handled;
    WindowManager()->SetTimerValue(0, msg->mParam_18);
    return handled;
  }
  }
  return false;
}
