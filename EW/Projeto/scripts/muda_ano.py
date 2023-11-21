import json
import re

file = "./Acordaos/jsta_acordaos.json"
f = open(file, "r")
campos = ["Ano da Publicação"]
lista = json.load(f)
for elem in lista:
    for campo in campos:
        if campo in elem:
            if re.fullmatch(r"\d{2}", elem[campo]):
                if int(elem[campo]) < 99 and int(elem[campo]) >= 23:
                    elem[campo] = "19" + elem[campo]
                else:
                    elem[campo] = "20" + elem[campo]
f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
