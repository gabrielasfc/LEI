import json
import os

keyset = set()
for file in os.listdir("../datasets"):
    with open('../datasets/' + file) as descriptor:
        dataset = json.load(descriptor)
        for acordao in dataset:
            for key in acordao:
                keyset.add(key)

with open("../keys.json", "w") as descriptor:
    json.dump(list(keyset), descriptor, ensure_ascii=False)