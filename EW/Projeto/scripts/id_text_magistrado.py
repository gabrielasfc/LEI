import json
import os

pasta = "./Acordaos"
pasta_resultados = "./Resultados"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
teste = 0
i = 0
for arquivo in arquivos:
    print("A realizar Teste ", teste)
    teste += 1
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    for acordao in acordaos:
        acordao["_id"] = "a" + i
        i += 1
        if "Magistrado" in acordao:
            acordao["Relator"] = acordao["Magistrado"]
            acordao.pop("Magistrado")
        if "Texto Integral" in acordao and "Decisão Texto Integral" in acordao:
            acordao.pop("Texto Integral")
        elif "Texto Integral" in acordao:
            acordao["Decisão Texto Integral"] = acordao["Texto Integral"]
            acordao.pop("Texto Integral")
        if "Data do Acordão" in acordao:
            acordao["Data"] = acordao["Data do Acordão"]
            acordao.pop("Data do Acordão")
    f.close()
    fp = open(os.path.join(pasta_resultados, arquivo), encoding="utf-8")
    json.dump(acordaos)
    fp.close()
