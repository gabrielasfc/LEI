import json
import re

"""
file = "./Acordaos/jstj_acordaos.json"
f = open(file, "r")
lista = json.load(f)
for elem in lista:
    if "Texto Integral" in elem:
        # elem["Relator"] = elem["Magistrado"]
        elem.pop("Texto Integral")
f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
"""
"""
file = "./Acordaos/jstj_acordaos.json"
f = open(file, "r")
lista = json.load(f)
for elem in lista:
    if "Data" in elem:
        if re.match(r"\d{2}/\d{2}/\d{4}|\d{2}-\d{2}-\d{4}", elem["Data"]):
            elem["Data de Entrada"] = elem["Data"]
            elem.pop("Data")
        else:
            elem["Informação Auxiliar"]["Data"] = elem["Data"]
            elem.pop("Data")
f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
"""

file = "/home/miguel_senra/Desktop/TrabalhoEW/Acordaos/jstj_acordaos.json"
f = open(file, "r")
campos = ["Data da Reclamação"]
lista = json.load(f)
for elem in lista:
    for campo in campos:
        if campo in elem:
            if re.match(r"\d{2}/\d{2}/02\d{2}", elem[campo]):
                elem[campo] = re.sub(
                    r"(\d{2})/(\d{2})/02(\d{2})", r"\1/\2/20\3", elem[campo]
                )
                # print(elem[campo])
            if re.match(r"\d{2}/\d{2}/\d{4}", elem[campo]):
                elem[campo] = re.sub(
                    r"(\d{2})/(\d{2})/(\d{4})", r"\2/\1/\3", elem[campo]
                )
            elif re.match(r"\d{2}-\d{2}-\d{4}", elem[campo]):
                elem[campo] = re.sub(
                    r"(\d{2})-(\d{2})-(\d{4})", r"\2/\1/\3", elem[campo]
                )
            # elif re.match(r"\d{2}/\d{2}/\d{2}", elem[campo]):
            # elem[campo] = re.sub(
            #    r"(\d{2})/(\d{2})/(\d{2})", r"\2/\1/19\3", elem[campo]
            # )
            else:
                print(elem[campo])
f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
