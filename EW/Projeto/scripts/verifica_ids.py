import json
import os

pasta = "./Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
"""
chaves = dict()
i = 0
for arquivo in arquivos:
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    for acordao in acordaos:
        if acordao["Processo"] not in chaves:
            chaves[acordao["Processo"]] = arquivo
        else:
            i += 1
            print(
                "Encontrei chaves repetidas ",
                chaves[acordao["Processo"]],
                ",",
                arquivo,
                " ",
                acordao["Processo"],
            )
    f.close()
print(i)
"""
"""
arquivos = ["jtre_acordaos.json"]
for arquivo in arquivos:
    print(arquivo)
    lista = []
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    for acordao in acordaos:
        if acordao not in lista:
            lista.append(acordao)
        # else:
        # print("Registos iguais")
    f.close()

    f = open(os.path.join(root, arquivo), "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
"""

i = 0
for arquivo in arquivos:
    print(arquivo)
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    for acordao in acordaos:
        acordao["_id"] = "a_" + str(i)
        i += 1
    f.close()

    f = open(os.path.join(root, arquivo), "w", encoding="utf-8")
    json.dump(acordaos, f, indent=" ", ensure_ascii=False)
    f.close()
