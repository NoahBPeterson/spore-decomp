// Editor model loading helpers (module built WITHOUT optimization and without
// C++ EH: compile with /Od /Ob1 /MD /Gy /TP).
//
// 0x004063d0  implicit copy constructor of a load-request record
// 0x00406540  compiler-generated `vector copy constructor iterator' (??__G),
//             emitted by the compiler alongside that copy constructor
// 0x00406570  EditorLoader::Load
//
// Class and member names below are inferred (callees, property types, field
// usage); they are not confirmed by symbols.

template <class T> class intrusive_ptr {
public:
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr& Reset();                                  // e.g. 0x0041d9f0 (non-inline)
    T** AsPointer() { return &Reset().mpObject; }
    intrusive_ptr& operator=(const intrusive_ptr& x) { return operator=(x.mpObject); }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* mpObject;
};

struct ResourceKey { unsigned int instanceID, typeID, groupID; };

class DefaultRefCounted { public: int AddRef(); int Release(); int mnRefCount; };

struct Property {
    unsigned int pad[4]; unsigned short pad10; unsigned short mnType;
    float* GetValueFloat(); bool* GetValueBool(); int* GetValueInt32();
};
class PropertyList {
public:
    virtual int AddRef(); virtual int Release(); virtual void f8(); virtual void fc(); virtual void f10();
    virtual void f14(); virtual void f18(); virtual void f1c(); virtual void f20();
    virtual bool GetProperty(unsigned int id, Property*& prop);
};
class IPropManager {
public:
    virtual void f0(); virtual void f4(); virtual void f8(); virtual void fc(); virtual void f10();
    virtual void f14(); virtual void f18(); virtual void f1c(); virtual void f20(); virtual void f24(); virtual void f28();
    virtual bool GetPropertyList(unsigned int instanceID, unsigned int groupID, PropertyList** ppList);
};
IPropManager* PropManager();   // 0x0067de30

class IEditorModel { public: virtual void f0(); };
class EditorModel : public IEditorModel, public DefaultRefCounted {
public:
    void Init(void* p, int a, int b, bool c);   // 0x004ae260
    unsigned int GetCount();                    // 0x004accf0
};
bool LoadEditorModel(const ResourceKey& key, EditorModel** ppModel, int flags);  // 0x004badd0

class Task {
public:
    int AddRef();     // 0x0068f950
    int Release();    // 0x00690120
    int GetState();   // 0x0068f970
    bool IsReady() { switch (GetState()) { case 7: case 8: return true; default: return false; } }
    void SetOwner(void* owner);  // 0x00421f40
    void Start();     // 0x006909b0
    void SetField18(int v) { mField18 = v; }
    unsigned int pad[6];
    int mField18;
};
class ITaskManager {
public:
    virtual void f0(); virtual void f4(); virtual void f8(); virtual void fc();
    virtual bool CreateTask(Task** pp);
};
ITaskManager* TaskManager();  // 0x0068f4d0

// ---------------------------------------------------------------------------
// Load-request record (0x38 bytes) and its implicit copy constructor.
// ---------------------------------------------------------------------------
class SimpleRefCounted {
public:
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
    void* mpVTable;
    int mnRefCount;
};
class IRefCounted {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct Int2 { int x, y; };

struct EditorLoadRequest {
    ResourceKey mKey;                          // 0x00
    Int2 mParams;                              // 0x0c
    intrusive_ptr<SimpleRefCounted> mpA;       // 0x14
    intrusive_ptr<SimpleRefCounted> mpB;       // 0x18
    intrusive_ptr<Task> mpTask;                // 0x1c
    intrusive_ptr<IRefCounted> mpOwner;        // 0x20
    intrusive_ptr<IRefCounted> mpListeners[3]; // 0x24
};

// @ 0x004063d0  EditorLoadRequest::EditorLoadRequest(const EditorLoadRequest&) (implicit)
// @ 0x00406540  `vector copy constructor iterator' (compiler-generated)
// The implicit copy constructor is only emitted when odr-used:
EditorLoadRequest* CloneLoadRequest(const EditorLoadRequest& request)
{
    return new EditorLoadRequest(request);
}

inline void ReadFloat(PropertyList* pList, unsigned int id, float& value) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 0xd) value = *prop->GetValueFloat();
}
inline void ReadBool(PropertyList* pList, unsigned int id, bool& value) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 1) value = *prop->GetValueBool();
}
inline void ReadInt(PropertyList* pList, unsigned int id, int& value) {
    Property* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 9) value = *prop->GetValueInt32();
}
struct EditorData {
    EditorData();                                   // 0x00418120
    ~EditorData();                                  // 0x00418240
    EditorData& operator=(const EditorData& other); // 0x00406ac0
    bool mbValid;
    float mfScale;
    intrusive_ptr<PropertyList> mpPropList;
    unsigned int pad[(0xccc - 0xc) / 4];   // model/rigblock vectors etc.
};
struct EditorState { unsigned int pad[5]; bool mbDirty; };   // refcounted, +0x14 dirty flag
class ModelHolder { public: ModelHolder& operator=(EditorModel* p); EditorModel* mp; };  // 0x0041d980

class EditorLoader {
public:
    bool Load();
    unsigned int pad0[0x74/4];
    void* mp74;
    void* GetEditorContext() const { return mp74; }
    unsigned int pad78[(0x228-0x78)/4];
    ResourceKey mKey;               // 0x228
    unsigned int pad234;
    unsigned short mFlags;          // 0x238
    unsigned short pad23a;
    intrusive_ptr<EditorState> mpState;  // 0x23c
    unsigned int pad240[(0x330-0x240)/4];
    intrusive_ptr<Task> mpTask;  // 0x330
    ModelHolder mModel;             // 0x334
    unsigned int pad338[(0x424-0x338)/4];
    bool mb424;
    bool mb425;
    unsigned short pad426;
    int mn428;
    EditorData mData;               // 0x42c
};

// @ 0x00406570
bool EditorLoader::Load()
{
    ResourceKey key = mKey;
    intrusive_ptr<EditorModel> pModel;
    if (mpTask && !mpTask->IsReady())
        return false;
    if (mData.mbValid)
        mData = EditorData();
    if (!LoadEditorModel(key, pModel.AsPointer(), 0))
        return false;
    pModel->Init(GetEditorContext(), 0, 0, true);
    if (pModel->GetCount() <= 0)
        return false;
    mb424 = (mFlags & 8) != 0;
    mpState->mbDirty = true;
    intrusive_ptr<PropertyList>& propList = mData.mpPropList;
    mb425 = false;
    mn428 = 0;
    if (PropManager()->GetPropertyList(key.instanceID, key.groupID, propList.AsPointer())) {
        ReadFloat(propList.get(), 0x2f35189, mData.mfScale);
        ReadBool(propList.get(), 0x339ff24, mb425);
        ReadInt(propList.get(), 0x339ffa9, mn428);
    }
    intrusive_ptr<Task> pTask;
    if (!TaskManager()->CreateTask(pTask.AsPointer()))
        return false;
    pTask->SetField18(1);
    pTask->SetOwner(this);
    mData.mbValid = true;
    mpTask = pTask;
    mModel = pModel.mpObject;
    pTask->Start();
    return true;
}
