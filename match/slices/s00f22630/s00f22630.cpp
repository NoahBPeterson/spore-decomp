typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

struct Vec3 { float x, y, z; };
extern Vec3 gOrigin;
extern float gDefault;
extern float gScale;
extern const char gKeyName[];
struct Key { Key(const char*); uint32_t pad[9]; };

struct Msg {
  uint16_t id;
  uint16_t count;
  float x, y, z;
  float value;
  Key key;
  Msg() : id(0), count(0), x(gOrigin.x), y(gOrigin.y), z(gOrigin.z), value(gDefault), key(gKeyName) {}
};


struct Target {
  virtual void v0();
  virtual void v1();
  virtual void Begin(int);
  virtual void Reset(int);
  virtual void v4();
  virtual void v5();
  virtual void Send(Msg*);
  virtual void v7();
  virtual void Init(Msg*);
};

struct Sub {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12();
  virtual float GetValue();
};

struct Owner {
  Target* Find(uint32_t);
  Target* Create(uint32_t);
  char pad[0xc0];
  Sub sub;
};

// @ 0x00f22630
// Looks up (or creates) a target by id on the owner, resets it, and sends it an
// init message followed by an update message carrying a scaled value from owner+0xC0.
void FUN_00f22630(Owner* owner, uint32_t id) {
  Target* t = owner->Find(id);
  if (!t) t = owner->Create(id);
  t->Reset(0);
  t->Begin(0);
  Msg m;
  t->Init(&m);
  m.value = owner->sub.GetValue() * gScale;
  m.count++;
  t->Send(&m);
}

// Not emitted (not real function starts; listed in the slice by mistake):
//   0x00f226e0  tail of FUN_00f22630 (begins mid-instruction at 0x00f226df)
//   0x00f22790  interior of the function starting at 0x00f22710
//   0x00f22ab0  interior of the function starting at 0x00f22930 (ends with a tail jmp at 0x00f22d42)
