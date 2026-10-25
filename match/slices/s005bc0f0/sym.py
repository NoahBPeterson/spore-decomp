import json, sys
p = "work/devbuild/symbols.json"
d = json.load(open(p))
print(type(d), list(d)[:10] if isinstance(d, dict) else len(d))
