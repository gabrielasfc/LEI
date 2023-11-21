import json
import os

pasta = "./Acordaos"
pasta_resultados = "./Resultados"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
arquivos = ["jtrp_acordaos1.json"]
i = 0
for arquivo in arquivos:
    print("A realizar Teste ", i)
    i += 1
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    acordao_1 = acordaos.pop(0)
    campos = dict()
    for key in acordao_1:
        campos[key] = str(type(acordao_1[key]))
    novos_valores = dict()
    for acordao in acordaos:
        for key in acordao:
            if key not in campos:
                novos_valores[key] = acordao[key]
            elif campos[key] != str(type(acordao[key])):
                print(
                    "Tipo diferentes ",
                    key,
                    " ,val1: ",
                    campos[key],
                    " ,val2: ",
                    str(type(acordao[key])),
                )
    f.close()
    fp = open(
        pasta_resultados + "/" + arquivo[:-5] + "_test.txt", "w", encoding="utf-8"
    )
    fp.write("Valores iniciais\n")
    fp.write(json.dumps(campos, indent=4, ensure_ascii=False))
    fp.write("------------------------\n")
    fp.write(json.dumps(novos_valores, indent=4, ensure_ascii=False))
    fp.close()
