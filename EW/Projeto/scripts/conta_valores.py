import json
import os

pasta = "./Acordaos"
pasta_resultados = "./Resultados"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
arquivos = ["atco1_acordaos.json"]
i = 0
for arquivo in arquivos:
    print("A realizar Teste ", i)
    i += 1
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    campos = dict()
    for acordao in acordaos:
        for key in acordao:
            if key not in campos:
                campos[key] = 1
            else:
                campos[key] += 1
    print(campos)
    f.close()
