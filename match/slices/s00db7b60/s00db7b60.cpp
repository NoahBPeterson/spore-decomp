#include <string.h>

struct RefCounted {
  virtual void AddRef();
  virtual void Release();
};

struct IndexSource : RefCounted {
  virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
  virtual int GetValue();
};

struct Sink : RefCounted {
  void FUN_00c98750(int value, int index);
};

struct Message {
  unsigned int type;     // 0x00
  RefCounted* ref4;      // 0x04
  IndexSource* source;   // 0x08
  Sink* sink;            // 0x0c
  char pad10[0x0c];
  int index;             // 0x1c
};

struct Info {
  char pad0[8];
  float f8;              // 0x08
  char padc[0x20];
  int f2c;               // 0x2c
};

struct Channel {
  Info* FUN_00bc96a0(int a, int b);
  void FUN_00bc97f0(int a, int b, float f, int c);
};

struct Player;

struct Slot {
  bool active;
  Player* player;
  int pad;
};

struct Releaser {
  void FUN_00bc2180(int h);
};
template <class T> struct Ptr {
  T* p;
  T* operator->() { return p; }
};
struct Mgr {
  char pad[0x1c8];
  Ptr<Releaser> rel;
};
Mgr* FUN_00cd40b0();

struct SubState {
  char pad0[0x18];
  int count;             // 0x18
  char pad1c[0x0c];
  int handle;            // 0x28
  RefCounted* a;         // 0x2c
  RefCounted* b;         // 0x30
};

struct Session {
  char pad0[0x10];
  int mode;              // 0x10
  char pad14[4];
  unsigned int numSlots; // 0x18
  char pad1c[4];
  Slot slots[1];         // 0x20
  Player* FUN_00bc9b10();
};

struct Game {
  char pad0[8];
  Channel channel;       // 0x08
  char pad9[0x600 - 9];
  Session* session;      // 0x600
  void FUN_00bcb430();
};

struct Vec {
  int* mpBegin;
  int* mpEnd;
  int* erase(int* first, int* last) {
    memcpy(first, last, (char*)mpEnd - (char*)last);
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};

struct Player {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
  virtual void v32();
  virtual void Reset(int a, int b, int c);
  char pad4[0xb4c - 4];
  Game* game;            // 0xb4c
  char padb50[0xe];
  bool flagB5E;          // 0xb5e
  char padb5f[0xe8c - 0xb5f];
  int e8c;
  int e90;
  float e94;
  Vec vec;               // 0xe98
  void FUN_00c26310(int);
  void FUN_00c14750(int);
  bool FUN_00c0c120();
  void FUN_00c1ad10(int);
  void FUN_00c0ba10();
};

// @ 0x00DB7B60  (needs /arch:SSE or /arch:SSE2 for the xorps/movss float store)
void FUN_00db7b60(Player* self, int a2, int a3, int a4, int a5, Message* msg) {
  if (!self->flagB5E)
    self->FUN_00c26310(-1);
  self->FUN_00c14750(0);
  self->e8c = -1;
  self->e90 = -1;
  self->e94 = 0.0f;
  self->vec.clear();
  self->Reset(0, 0, 0);
  Game* game = self->game;
  Session* session = game->session;
  if (session) {
    SubState* sub = (SubState*)((char*)session + 0x1a4);
    if (msg->type >= 1 && msg->type <= 4) {
      Info* info = game->channel.FUN_00bc96a0(0, 0x80);
      if (info) {
        for (unsigned int i = 0; i < session->numSlots; i++) {
          Slot* s = &session->slots[i];
          if (s->active) { Player* p = s->player; if (p != self)
            p->game->channel.FUN_00bc97f0(0, 0x80, info->f8, info->f2c); }
        }
      }
    }
    if (self == session->FUN_00bc9b10() && sub->handle) {
      FUN_00cd40b0()->rel->FUN_00bc2180(sub->handle);
      sub->handle = 0;
    }
    if (msg->type == 3)
      sub->count--;
    if (session->mode == 1 && sub) {
      if (sub->b) sub->b->Release();
      if (sub->a) sub->a->Release();
    }
    self->game->FUN_00bcb430();
  }
  if (self->FUN_00c0c120())
    self->FUN_00c1ad10(0);
  int index = msg->index;
  if (index >= 0) {
    IndexSource* src = msg->source;
    if (src) { Sink* sink = msg->sink; sink->FUN_00c98750(src->GetValue(), index); }
    else msg->sink->FUN_00c98750(12, index);
  }
  self->FUN_00c0ba10();
  { RefCounted* p = msg->sink; if (p) p->Release(); }
  { RefCounted* p = msg->source; if (p) p->Release(); }
  { RefCounted* p = msg->ref4; if (p) p->Release(); }
}
