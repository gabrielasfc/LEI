import json
import re
import os


pasta = "./Acordaos"
pasta_resultados = "./Resultados"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
# arquivos = ["atco1_acordaos.json"]
#print(arquivos)

file = ["/home/miguel_senra/Desktop/TrabalhoEW/Acordaos/jstj_acordaos.json"]
i = 0
for arquivo in file:
    print(i)
    i += 1
    # file = "./Acordaos/atco1_acordaos.json"
    # file1 = "./Acordaos/jstj_acordaos1.json"
    print(arquivo)
    #f = open(os.path.join(root, arquivo), "r")
    f = open(arquivo, "r")
    lista = json.load(f)
    for elem in lista:
        if "Data da Reclamação" in elem:
            elem["Data do Acordão"]=elem["Data da Reclamação"]
            elem.pop("Data da Reclamação")
    f.close()
    f = open(arquivo, "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
    """
    if (
        "Legislação Comunitária" in elem
        or "Legislação Estrangeira" in elem
        or "Legislação Nacional" in elem
    ):
        elem["Legislações"] = dict()
        if "Legislação Nacional" in elem:
            elem["Legislações"]["Legislação Nacional"] = elem["Legislação Nacional"]
            elem.pop("Legislação Nacional")
        if "Legislação Estrangeira" in elem:
            elem["Legislações"]["Legislação Estrangeira"] = elem[
                "Legislação Estrangeira"
            ]
            elem.pop("Legislação Estrangeira")
        if "Legislação Comunitária" in elem:
            elem["Legislações"]["Legislação Comunitária"] = elem[
                "Legislação Comunitária"
            ]
            elem.pop("Legislação Comunitária")
    """
"""
        if (
            "Outra Jurisprudência" in elem
            or "Jurisprudência Constitucional" in elem
            or "Jurisprudência Estrangeira" in elem
            or "Jurisprudência Internacional" in elem
            or "Jurisprudência Nacional" in elem
        ):
            elem["Jurisprudências"] = dict()
            if "Jurisprudência Nacional" in elem:
                elem["Jurisprudências"]["Jurisprudência Nacional"] = elem[
                    "Jurisprudência Nacional"
                ]
                elem.pop("Jurisprudência Nacional")
            if "Jurisprudência Internacional" in elem:
                elem["Jurisprudências"]["Jurisprudência Internacional"] = elem[
                    "Jurisprudência Internacional"
                ]
                elem.pop("Jurisprudência Internacional")
            if "Jurisprudência Estrangeira" in elem:
                elem["Jurisprudências"]["Jurisprudência Estrangeira"] = elem[
                    "Jurisprudência Estrangeira"
                ]
                elem.pop("Jurisprudência Estrangeira")
            if "Jurisprudência Constitucional" in elem:
                elem["Jurisprudências"]["Jurisprudência Constitucional"] = elem[
                    "Jurisprudência Constitucional"
                ]
                elem.pop("Jurisprudência Constitucional")
            if "Outra Jurisprudência" in elem:
                elem["Jurisprudências"]["Outra Jurisprudência"] = elem[
                    "Outra Jurisprudência"
                ]
                elem.pop("Outra Jurisprudência")
        if "Recorrente" in elem:
            elem["Requerente"] = elem["Recorrente"]
            # elem["Referências Publicação"] = []
            # elem["Referências Publicação"].append(elem["Outras Publicações"])
            elem.pop("Recorrente")

        if "Recorrido 1" in elem:
            # elem["Requerido"] = []
            # elem["Requerido"].append(elem["Recorrido 1"])
            # if "Recorrido 2" in elem:
            # elem["Requerido"].append(elem["Recorrido 2"])
            # elem.pop("Recorrido 2")
            # elem.pop("Recorrido 1")
            pass
        elif "Réu" in elem:
            # elem["Requerido"] = []
            # elem["Requerido"].append(elem["Réu"])
            elem.pop("Réu")

        if "Meio Processual" in elem:
            # elem["Requerido"] = []
            # elem["Requerido"].append(elem["Contencioso"])
            # elem.pop("Contencioso")
            if re.search(r"PARECERES", elem["Meio Processual"]):
                print(arquivo)
        ##if "Ano da Publicação" in elem:
        # elem["Requerido"] = []
        # elem["Requerido"].append(elem["Ano da Publicação"])
        # elem.pop("Ano da Publicação")
    f.close()
    f = open(os.path.join(root, arquivo), "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
"""
