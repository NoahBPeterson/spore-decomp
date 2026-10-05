// SP::cSPPlayModePhotoBrowser helpers. Region 0x633560-0x63448f.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);
typedef void (__thiscall *TF2)(void*, int, int);
typedef void (__thiscall *TF3)(void*, int, int, int);

extern "C" void* __cdecl MessageServer();
extern "C" void  __cdecl RBTreeNuke(void* node);

struct RBTree { void DoNukeSubtree(void* root); };
struct JobManager { int ContinueJob(); };
struct UIPM { void SetUIGroupVisible(unsigned int key, int b); };

struct PMB {
  void DeleteOne();
  void DeleteAll();
  void MoveOne();
  void MoveAll();
  unsigned PhotoCountChanged();
  void ShowImageThumbnail();
  void UpdatePhotoCountText();
  void DeletePhoto(int idx, int b);
  void ShowSendEmailWindow();
  void* IsPhotosWriting();
  void FUN_00632b00();
};

// @ 0x00633560
void __fastcall FUN_00633560(void* self) { (void)self; }
// @ 0x00633760
void __fastcall FUN_00633760(void* self) { (void)self; }
// @ 0x006338a0
void __fastcall FUN_006338a0(void* self) { (void)self; }

// @ 0x006339e0
void __fastcall FUN_006339e0(void* self) { (void)self; }

// @ 0x00633ac0
void __fastcall FUN_00633ac0(void* self) { (void)self; }
// @ 0x00633cc0
void __fastcall FUN_00633cc0(void* self) { (void)self; }
// @ 0x00633ea0
void __fastcall FUN_00633ea0(void* self) { (void)self; }

// @ 0x00633f90
void __fastcall FUN_00633f90(void* self) {
  char* s = (char*)self;
  int tag = 0;
  switch (*(int*)(s + 0xe74)) {
    case 0: tag = 0x447a553; ((PMB*)s)->DeleteOne(); break;
    case 1: tag = 0x4479851; ((PMB*)s)->DeleteAll(); break;
    case 2: tag = 0x447a54c; ((PMB*)s)->MoveOne(); break;
    case 3: tag = 0x4479848; ((PMB*)s)->MoveAll(); break;
  }
  unsigned c = ((PMB*)s)->PhotoCountChanged();
  *(int*)(s + 0xea4) = c;
  ((PMB*)s)->ShowImageThumbnail();
  ((PMB*)s)->UpdatePhotoCountText();
  FUN_00633ea0(s);
  void* m = MessageServer();
  if (m != 0 && tag != 0) {
    ((TF3)(*(void**)(*(char**)m + 0x14)))(m, tag, 0, 0);
  }
}

// @ 0x00634030
void __fastcall FUN_00634030(void* self) {
  char* s = (char*)self;
  char* map = s + 0x68;
  ((RBTree*)map)->DoNukeSubtree(*(void**)(map + 0xc));
  char* anchor = map + 4;
  *(int*)(map + 8) = (int)anchor;
  *(int*)(map + 0xc) = 0;
  *(unsigned char*)(map + 0x10) = 0;
  *(int*)(map + 0x14) = 0;
  *(int*)anchor = (int)anchor;
  int n = (*(int*)(s + 8) - *(int*)(s + 4)) >> 2;
  for (int i = n - 1; i >= 0; --i) ((PMB*)s)->DeletePhoto(i, 0);
  FUN_006338a0(s);
  *(int*)(s + 0x18) = 0;
  ((PMB*)s)->ShowImageThumbnail();
  ((PMB*)s)->UpdatePhotoCountText();
  int cnt = (*(int*)(s + 8) - *(int*)(s + 4)) >> 2;
  if (cnt == 0)
    ((UIPM*)*(void**)(s + 0x24))->SetUIGroupVisible(0x4463e78u, 0);
  else
    ((UIPM*)*(void**)(s + 0x24))->SetUIGroupVisible(0x4463e78u, 1);
}

// @ 0x006340c0
bool __fastcall FUN_006340c0(void* self) {
  char* s = (char*)self;
  void* m = MessageServer();
  if (m != 0) {
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, (int)self, 0x4235e47);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, (int)self, 0x476e786);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, (int)self, 0x41a218d);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, (int)self, 0x4755bcf);
  }
  unsigned c = ((PMB*)s)->PhotoCountChanged();
  *(int*)(s + 0xea4) = c;
  ((PMB*)s)->UpdatePhotoCountText();
  *(int*)(s + 0x18) = 0;
  ((PMB*)s)->ShowImageThumbnail();
  ((PMB*)s)->UpdatePhotoCountText();
  return true;
}

// @ 0x00634140
void __fastcall FUN_00634140(void* self) { (void)self; }

// @ 0x00634380
void __fastcall FUN_00634380(void* self, unsigned idx) {
  char* s = (char*)self;
  char* map = s + 0x68;
  ((RBTree*)map)->DoNukeSubtree(*(void**)(map + 0xc));
  char* anchor = map + 4;
  *(int*)anchor = (int)anchor;
  *(int*)(map + 8) = (int)anchor;
  *(int*)(map + 0xc) = 0;
  *(unsigned char*)(map + 0x10) = 0;
  *(int*)(map + 0x14) = 0;
  unsigned c = ((PMB*)s)->PhotoCountChanged();
  if (c != *(unsigned*)(s + 0xea4)) {
    *(unsigned*)(s + 0xea4) = c;
    FUN_00634030(s);
  }
  if (idx < (unsigned)((*(int*)(s + 8) - *(int*)(s + 4)) >> 2)) {
    *(unsigned*)(s + 0x1c) = idx;
    ((PMB*)s)->ShowSendEmailWindow();
  }
}

// @ 0x006343f0
void __fastcall FUN_006343f0(void* self) {
  char* s = (char*)self;
  void* job = ((PMB*)s)->IsPhotosWriting();
  if (job != 0) {
    do {
      if (((JobManager*)job)->ContinueJob() != 4) break;
    } while (1);
  }
  char* map = s + 0x68;
  ((RBTree*)map)->DoNukeSubtree(*(void**)(map + 0xc));
  char* anchor = map + 4;
  *(int*)anchor = (int)anchor;
  *(int*)(map + 8) = (int)anchor;
  *(int*)(map + 0xc) = 0;
  *(unsigned char*)(map + 0x10) = 0;
  *(int*)(map + 0x14) = 0;
  unsigned c = ((PMB*)s)->PhotoCountChanged();
  if (c != *(unsigned*)(s + 0xea4)) {
    *(unsigned*)(s + 0xea4) = c;
    FUN_00634030(s);
  }
  int cnt = (*(int*)(s + 8) - *(int*)(s + 4)) >> 2;
  int idx = *(int*)(s + 0x18);
  int nidx = idx + 5;
  *(int*)(s + 0x18) = nidx;
  if (nidx < cnt) {
    ((PMB*)s)->FUN_00632b00();
  } else {
    *(int*)(s + 0x18) = idx;
    ((PMB*)s)->ShowImageThumbnail();
    ((PMB*)s)->UpdatePhotoCountText();
  }
}
