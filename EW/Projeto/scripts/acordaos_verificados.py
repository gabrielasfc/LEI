import json
import os
import re

"""
pasta = "./Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
i = 0
arquivos = ["jtrl_acordaos.json"]
for arquivo in arquivos:
    print("A realizar Teste ", i)
    i += 1
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    lista = []
    for acordao in acordaos:
        if "Informação Auxiliar" in acordao:
            for key in acordao["Informação Auxiliar"]:
                if acordao["Informação Auxiliar"][key] == "ver acórdão STJ":
                    lista.append(key)
    f.close()
    f = open(os.path.join(root, "jstj_acordaos.json"))
    acordaos = json.load(f)
    for acordao in acordaos:
        if acordao["Processo"] in lista:
            print("Encontrei o seguinte processo ", acordao["Processo"])
    f.close()
    print(lista)
"""
pasta = "./Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
i = 0
arquivos1 = ["jstj_acordaos.json"]
lista = []
lista1 = []
for arquivo in arquivos:
    print("A realizar Teste ", i)
    i += 1
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    for acordao in acordaos:
        if "Informação Auxiliar" in acordao:
            for key in acordao["Informação Auxiliar"]:
                if isinstance(acordao["Informação Auxiliar"][key], str):
                    if re.search(
                        "ver acórdão STJ", acordao["Informação Auxiliar"][key]
                    ):
                        if acordao["Informação Auxiliar"][key] not in lista1:
                            lista1.append(acordao["Informação Auxiliar"][key])
                        lista.append([key, arquivo])
    f.close()
for file in arquivos:
    f = open(os.path.join(root, file))
    acordaos = json.load(f)
    for acordao in acordaos:
        if acordao["Processo"] in map(lambda l: l[0], lista):
            print(
                "Encontrei o seguinte processo ",
                acordao["Processo"],
                " no file ",
                file,
            )
    f.close()
print(lista)
print(lista1)
