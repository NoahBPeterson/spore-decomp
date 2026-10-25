import json, sys, os
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.insert(0, os.path.join(ROOT, 'tools', 'difftest'))
import layout_inputs as L

cls = L.class_of(0x703700, '?Add@cHierGrid@@QAEXIMABUVec3@@I@Z')
print('class:', cls)
T = L.types()
s = T.get(cls)
print(json.dumps(s, indent=1)[:6000])
print('---- members ----')
for m in (s.get('members') or []):
    print(m)
