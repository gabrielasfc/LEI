import json

file = "./Acordaos/jtrp_acordaos.json"
f = open(file, "r")
lista = json.load(f)
for elem in lista:
    campos_remov = []
    for key in elem:
        if elem[key] == "":
            campos_remov.append(key)
    for campo in campos_remov:
        elem.pop(campo)

f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
