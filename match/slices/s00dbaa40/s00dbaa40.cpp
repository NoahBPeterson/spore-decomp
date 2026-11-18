// 0x00dbaa40: Action* PickAction(PickContext* ctx)
//
// Chooses the action (the sub-object at offset 0x120 of a node) the interface should use for
// the current selection:
//   * walk the nodes the context hands out (vtable slot 0xbc, a begin/end pointer pair),
//   * keep nodes of a selectable kind (bits 1..9), whose action state is not 2 and that are
//     registered in the context's table at 0x394,
//   * prefer the node whose Classify() returns 1, otherwise keep the other one,
//   * with no usable node at all, fall back to the context's current node (vtable slot 0xac)
//     when its action state is not 2.
//
// The structs below stand in for the retail headers: only the layout this function touches is
// spelled out (vtable slots and member offsets).

struct PickContext;
struct Node;
struct Action;

struct NodeVtable {
    void* unused[0x58 / 4];                            // 0x00 .. 0x54
    int (__thiscall* GetKind)(Node* self);             // 0x58
};

struct Action {
    int GetState();                                    // 0x008e7f80, 2 means unusable
};

struct Node {
    NodeVtable* vtable;                                // 0x000
    unsigned char reserved[0x120 - 4];                 // 0x004 .. 0x11f
    Action action;                                     // 0x120
    int Classify();                                    // 0x00c9d110, 1 for the preferred node
};

struct NodeList {
    Node** begin;                                      // 0x00
    Node** end;                                        // 0x04
};

struct TableIterator {
    int IsValid();                                     // 0x00af9f30, nonzero when the entry is usable
};

struct SelectionTable {
    TableIterator* Find(const int& kind);              // 0x00c27d20
};

struct ContextVtable {
    void* unused0[0xac / 4];                           // 0x00 .. 0xa8
    Node* (__thiscall* GetCurrent)(PickContext* self); // 0xac
    void* unused1[3];                                  // 0xb0 .. 0xb8
    NodeList* (__thiscall* GetNodes)(PickContext* self); // 0xbc
};

struct PickContext {
    ContextVtable* vtable;                             // 0x000
    unsigned char reserved[0x394 - 4];                 // 0x004 .. 0x393
    SelectionTable table;                              // 0x394
};

// @ 0x00dbaa40
Action* PickAction(PickContext* ctx)
{
    Node* primary = 0;
    Node* secondary = 0;

    NodeList* nodes = ctx->vtable->GetNodes(ctx);
    Node** it = nodes->begin;
    Node** end = nodes->end;
    for (; it != end; ++it) {
        Node* node = *it;
        if ((1 << node->vtable->GetKind(node)) & 0x3fe) {
            if (node->action.GetState() != 2) {
                if (ctx->table.Find(node->vtable->GetKind(node))->IsValid()) {
                    if (node->Classify() == 1)
                        primary = node;
                    else
                        secondary = node;
                }
            }
        }
    }

    if (primary == 0)
        primary = secondary;

    Action* result = primary != 0 ? &primary->action : 0;
    if (primary == 0) {
        if (ctx->vtable->GetCurrent(ctx)->action.GetState() != 2) {
            Node* current = ctx->vtable->GetCurrent(ctx);
            if (current != 0)
                return &current->action;
            return 0;
        }
    }
    return result;
}
