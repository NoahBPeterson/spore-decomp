// Slice s010a6860. 0x010a6c00 is not a function entry (it is mid-instruction inside the
// function at 0x010a6b50), so only 0x010a6860 is reconstructed here.

typedef unsigned int size_t;
extern "C" void* memmove(void* dst, const void* src, size_t n);

struct Edge;
struct Node;
struct Entry;

struct Handler {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void GetSize(int kind, int* outSize);              // +0x10
  virtual void v5();
  virtual void Write(Edge* e, char* data, int size);         // +0x18
  virtual void v7();
  virtual void Prepare(int* out);                            // +0x20
};

struct Owner {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual void OnAdd(Edge* e, int* info);                    // +0x0c
};

struct Edge {
  char pad0[4];
  unsigned short f4;
  unsigned short f6;
  Owner* owner;          // 0x08
  Handler* handler;      // 0x0c
  Node* nodes[2];        // 0x10
  unsigned char order;   // 0x18
  unsigned char kind;    // 0x19
  char pad1a[0x0a];
  Entry* entry;          // 0x24
};

struct Entry {
  Edge* edge;            // 0x00
  Node* nodes[2];        // 0x04
  Handler* handler;      // 0x0c
  unsigned char order;   // 0x10
  unsigned char side;    // 0x11
  unsigned short index;  // 0x12
  unsigned short size;   // 0x14
  char* data;            // 0x18
};

struct InsertRange {
  const Entry* p;
  int count;
  unsigned int flags;
};

struct EntryArray {
  Entry* data;
  int size;
  unsigned int cap;
  void Insert(int pos, InsertRange* r);
};

struct ByteArray {
  char* data;
  int size;
  unsigned int cap;
};

struct PtrArray {
  Edge** data;
  int size;
  unsigned int cap;
};

struct Node {
  char pad0[8];
  int f8;
  char padc[0x50];
  Owner* owner;          // 0x5c
  char pad60[0x10];
  EntryArray entries;    // 0x70
  PtrArray edges;        // 0x7c
  ByteArray buffer;      // 0x88
  char pad94[5];
  char f99;              // 0x99
  char pad9a[0x32];
  unsigned int rank;     // 0xcc
};

void FUN_010a1170(int a, Node* n0, Node* n1);
void FUN_0107f4a0(ByteArray* a, int n, int f);
void FUN_0107f530(PtrArray* a, int elemSize);

// @ 0x010a6860
void FUN_010a6860(void* unused, Edge* e)
{
  if (e->f4 != 0)
    e->f6++;
  Entry tmp;
  tmp.edge = e;
  tmp.nodes[0] = e->nodes[0];
  tmp.nodes[1] = e->nodes[1];
  tmp.handler = e->handler;
  tmp.order = e->order;
  if (tmp.nodes[0]->f99 == 0 && tmp.nodes[1]->f99 == 0 && tmp.nodes[0]->owner != tmp.nodes[1]->owner)
    FUN_010a1170(tmp.nodes[0]->f8, tmp.nodes[0], tmp.nodes[1]);
  tmp.side = tmp.nodes[0]->f99 != 0;
  Node* node = tmp.nodes[tmp.side];
  e->owner = node->owner;
  int info;
  tmp.handler->Prepare(&info);
  e->owner->OnAdd(e, &info);

  EntryArray* arr = &node->entries;
  int n = arr->size;
  int i = 0;
  for (; i < n; i++) {
    Entry* p = &arr->data[i];
    if (p->order > tmp.order) break;
    if (p->order == tmp.order) {
      if (p->nodes[0]->rank > tmp.nodes[0]->rank) break;
      if (p->nodes[0]->rank == tmp.nodes[0]->rank && p->nodes[1]->rank > tmp.nodes[1]->rank) break;
    }
  }
  int start = n < (int)(arr->cap & 0x3fffffff) ? i : 0;
  InsertRange r;
  r.p = &tmp;
  r.count = 1;
  r.flags = 0x80000001;
  arr->Insert(i, &r);
  for (int j = start; j < arr->size; j++)
    arr->data[j].edge->entry = &arr->data[j];

  Entry* ent = e->entry;
  ent->handler->GetSize(e->kind, &info);
  ent->size = (unsigned short)info;
  if (info == 0) {
    ent->data = 0;
  } else {
    ByteArray* buf = &node->buffer;
    char* old = buf->data;
    int newSize = buf->size + info;
    if ((int)(buf->cap & 0x3fffffff) < newSize)
      FUN_0107f4a0(buf, newSize, 1);
    buf->size += info;
    char* pos = buf->data;
    int delta = pos - old;
    int k = 0;
    for (; k < i; k++) {
      Entry* p = &arr->data[k];
      if (p->data) {
        p->data += delta;
        pos = p->data + p->size;
      }
    }
    memmove(pos + ent->size, pos, buf->data - ent->size - pos + buf->size);
    ent->data = pos;
    delta += ent->size;
    for (k++; k < arr->size; k++) {
      Entry* p = &arr->data[k];
      p->data = p->data ? p->data + delta : 0;
    }
  }
  ent->handler->Write(e, ent->data, ent->size);
  Node* other = ent->nodes[1 - ent->side];
  ent->index = (unsigned short)other->edges.size;
  PtrArray* v = &other->edges;
  if (v->size == (int)(v->cap & 0x3fffffff))
    FUN_0107f530(v, 4);
  v->data[v->size] = e;
  v->size++;
}
