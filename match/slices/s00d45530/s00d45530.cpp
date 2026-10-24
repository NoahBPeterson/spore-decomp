// Slice s00d45530 (0x00d45530..0x00d456fb) — SP::cCreatureModeStrategy::PostGameModeTransition.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc)

#include <stddef.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

struct cGameMode;         // opaque game-mode object (compared by identity)
struct cGameObject;       // opaque scene object (the avatar)

// --- external helpers -------------------------------------------------------
void*  __cdecl eOperatorNew(unsigned size, const char* name, int a, int b,
                            const char* file, int line);   // 0x00f473a0
void*  __cdecl SP_EffectsManager();                        // 0x0067ddd0
void*  __cdecl MessageServer();                            // 0x0067dcc0
void   __cdecl FUN_00b976f0();                             // 0x00b976f0
float  __cdecl FUN_00d2e350();                             // 0x00d2e350

struct cGameNounManager {                                  // 0x00b3d300
  cGameObject* GetAvatar();                                // 0x00b1fdb0
};
cGameNounManager* __cdecl NounManager();                   // 0x00b3d300

struct cGameTimeManager {                                  // 0x00b3d380
  void IncPauseGate(int);                                  // 0x00b32220
};
cGameTimeManager* __cdecl GameTimeManager();               // 0x00b3d380

extern char DAT_01654c00;   // game-mode object B
extern char DAT_01654c01;   // game-mode object A

// --- the 0x40-byte message object posted to the message server --------------
struct cSlotMessage {
  char pad00[0x08];                                  // +0x00..0x07
  int  m08;                                          // +0x08
  char pad0c[0x04];                                  // +0x0c..0x0f
  int  m10;                                          // +0x10
  char pad14[0x04];                                  // +0x14..0x17
  int  m18;                                          // +0x18
  char pad1c[0x14];                                  // +0x1c..0x2f
  int  m30;                                          // +0x30
  char pad34[0x0c];                                  // +0x34..0x3f
  cSlotMessage* Construct(int arg);                  // 0x00421c80
};

// --- the sub-object this method lives on (at +0x08 of cCreatureModeStrategy)
struct cModeStrategy {
  char pad00[0x41];   // +0x00..0x40
  char m41;           // +0x41
  char pad42[0x56];   // +0x42..0x97
  int  m98;           // +0x98
  int  m9c;           // +0x9c
  int  ma0;           // +0xa0
  int  ma4;           // +0xa4
  char padA8[0x2c];   // +0xa8..0xd3
  char md4;           // +0xd4
  char padD5[0x01];   // +0xd5
  char md6;           // +0xd6
  void PostGameModeTransition(cGameMode* from, cGameMode* to);
};

struct cCreatureModeStrategy {
  char          pad00[0x08];            // +0x00..0x07
  cModeStrategy mStrategy;              // +0x08
  void          ContinueLoading(int);   // 0x00d43e30
};

// @ 0x00d45530
void cModeStrategy::PostGameModeTransition(cGameMode* from, cGameMode* to) {
  if (((cGameMode*(__thiscall*)(void*))VT(this, 0x20))(this) == to)
    return;

  ((void(__thiscall*)(void*, cGameMode*))VT(this, 0x44))(this, to);

  if (from != (cGameMode*)&DAT_01654c01) {
    if (to != (cGameMode*)&DAT_01654c01) {
      ((void(__thiscall*)(void*))VT(this, 0x4c))(this);
      return;
    }
  } else {
    if (to != (cGameMode*)&DAT_01654c01) {
      if (to == (cGameMode*)0xdbdba1) {
        void* ms = MessageServer();
        if (ms != 0) {
          cGameObject* avatar = NounManager()->GetAvatar();
          cSlotMessage* p =
              (cSlotMessage*)eOperatorNew(0x40, "App", 0, 0, (const char*)0, 0);
          cSlotMessage* obj;
          if (p != 0) {
            obj = p->Construct(0);
            if (obj != 0)
              ((void(__thiscall*)(void*))VT(obj, 4))(obj);
          } else {
            obj = 0;
          }
          obj->m30 = (int)0x90a03fdf;
          float f = FUN_00d2e350();
          int i = (int)f;
          if (f < (float)i)
            i = i - 1;
          obj->m08 = i;
          int a = ((int(__thiscall*)(void*))VT(avatar, 0xd8))(avatar);
          obj->m10 = a;
          obj->m18 = 1;
          ((void(__thiscall*)(void*, int, cSlotMessage*, int))VT(ms, 0x14))
              (ms, obj->m30, obj, 0);
          ((void(__thiscall*)(void*))VT(obj, 2))(obj);
          ((void(__thiscall*)(void*))VT(this, 0x4c))(this);
          return;
        }
      } else {
        if (to == (cGameMode*)0x2ccd1d2 || to == (cGameMode*)-1)
          FUN_00b976f0();
        this->md6 = 0;
        this->md4 = 0;
      }
      ((void(__thiscall*)(void*))VT(this, 0x4c))(this);
      return;
    }
  }

  void* eff = SP_EffectsManager();
  ((void(__thiscall*)(void*, int, int))VT(eff, 0x98))(eff, 8, 1);

  this->m41 |= (from == (cGameMode*)&DAT_01654c00);
  this->m98 = 0;
  this->m9c = (int)from;
  this->ma0 = (int)to;
  this->ma4 = 0;

  GameTimeManager()->IncPauseGate(0x4bf38a7);
  ((cCreatureModeStrategy*)((char*)this - offsetof(cCreatureModeStrategy, mStrategy)))
      ->ContinueLoading(0);

  ((void(__thiscall*)(void*))VT(this, 0x4c))(this);
}