// src/game/SPEngine/SPLocalInputState.cpp -- migrated from slice(s) s00696c80 by tools/migrate/rewrite.py
// Object file: SPEngine/SPLocalInputState.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocalInputState.h"
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include <string.h>

// ---- items of slice s00696c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cLocalInputState_s0069_6c80 {
 public:
  unsigned int mKeys[8];         // +0x00
  unsigned int mModifiers;       // +0x20
  bool mMouseButtons[5];         // +0x24
  unsigned char pad29[3];        // +0x29
  float mMouseX;                 // +0x2c
  float mMouseY;                 // +0x30
  unsigned int mDragButton;      // +0x34
  float mMouseStartX;            // +0x38
  float mMouseStartY;            // +0x3c
  unsigned int mMouseDownModifiers;  // +0x40
  unsigned int mScrollDelta;     // +0x44

  void Reset();  // 0x00697980 (SP::cLocalInputState::Reset)
  void ResetIf(bool commit);     // 0x697a10
  void UpdateModifiers();  // 0x006979c0 (SP::cLocalInputState::UpdateModifiers)
  void OnKeyDown(unsigned int key, unsigned int unused);   // 0x697a50
  void OnKeyUp(unsigned int key, unsigned int unused);  // 0x00697a80 (SP::cLocalInputState::OnKeyUp)
  void OnMouseDown(unsigned int button, float x, float y, unsigned int modifiers);  // 0x00697ab0 (SP::cLocalInputState::OnMouseDown)
  void OnMouseUp(unsigned int button, float x, float y, unsigned int unused);  // 0x00697af0 (SP::cLocalInputState::OnMouseUp)
  void AddScrollDelta(int delta, int b, int c, int d);  // 0x697b40
};
}
namespace SP {
inline bool KeyBit(const unsigned int* k, int index, int bit) {
  return (k[index] >> bit) & 1;
}
}
// ---- items of slice s00696c80 end

// @ 0x00697980
void SP::cLocalInputState::Reset()
{
  for (int i = 0; i < 8; ++i) mKeys[i] = 0;
  mModifiers = 0;
  for (int i = 0; i < 5; ++i) mMouseButtons[i] = false;
  mDragButton = 0;
  mMouseStartX = 0.0f;
  mMouseStartY = 0.0f;
  mMouseDownModifiers = 0;
}

// @ 0x006979c0
void SP::cLocalInputState::UpdateModifiers()
{
  mModifiers = 0;
  if (KeyBit(mKeys, 0, 0x10)) mModifiers = 1;
  if (KeyBit(mKeys, 0, 0x11)) mModifiers = mModifiers | 2;
  if (KeyBit(mKeys, 0, 0x12)) mModifiers = mModifiers | 4;
  if (KeyBit(mKeys, 7, 1)) mModifiers = mModifiers | 8;
  if (KeyBit(mKeys, 2, 0x1b)) mModifiers = mModifiers | 0x10;
}

// @ 0x00697a10
namespace SP {
void cLocalInputState_s0069_6c80::ResetIf(bool commit)
{
  if (!commit) {
    for (int i = 0; i < 8; ++i) mKeys[i] = 0;
    mModifiers = 0;
    for (int i = 0; i < 5; ++i) mMouseButtons[i] = false;
    mDragButton = 0;
    mMouseStartX = 0.0f;
    mMouseStartY = 0.0f;
    mMouseDownModifiers = 0;
  }
}
}  // namespace SP

// @ 0x00697a50
void SP::cLocalInputState::OnKeyDown(unsigned int key, unsigned int unused)
{
  (void)unused;
  if (key <= 0xff) {
    mKeys[key >> 5] |= 1u << (key & 0x1f);
    UpdateModifiers();
  }
}

// @ 0x00697a80
void SP::cLocalInputState::OnKeyUp(unsigned int key, unsigned int unused)
{
  (void)unused;
  if (key <= 0xff) {
    mKeys[key >> 5] &= ~(1u << (key & 0x1f));
    UpdateModifiers();
  }
}

// @ 0x00697ab0
void SP::cLocalInputState::OnMouseDown(unsigned int button, float x, float y, unsigned int modifiers)
{
  mMouseButtons[button - 1000] = true;
  mMouseX = x;
  mMouseY = y;
  if (mDragButton == 0) {
    mDragButton = button;
    mMouseDownModifiers = modifiers;
    mMouseStartX = x;
    mMouseStartY = y;
  }
}

// @ 0x00697af0
void SP::cLocalInputState::OnMouseUp(unsigned int button, float x, float y, unsigned int unused)
{
  (void)unused;
  mMouseButtons[button - 1000] = false;
  mMouseX = x;
  mMouseY = y;
  if (mDragButton == button) mDragButton = 0;
}
