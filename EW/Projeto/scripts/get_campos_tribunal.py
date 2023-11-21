import json
import os

nomes = {
    "atco1": "Tribunal Constitucional",
    "jcon": "Tribunal dos Conflitos",
    "jdgpj": "Direção-Geral da Política de Justiça",
    "jsta": "Supremo Tribunal Administrativo",
    "jstj": "Supremo Tribunal de Justiça",
    "jtca": "Tribunal Central Administrativo Sul",
    "jtcampca": "Tribunal Central Administrativo Sul - Contencioso Administrativo",
    "jtcampct": "Tribunal Central Administrativo Sul - Contencioso Tributário",
    "jtcn": "Tribunal Central Administrativo Norte",
    "jtrc": "Tribunal da Relação de Coimbra",
    "jtrl": "Tribunal da Relação de Lisboa",
    "jtrg": "Tribunal da Relação de Guimarães",
    "jtre": "Tribunal da Relação de Évora",
    "jtrp": "Tribunal da Relação do Porto",
}

pasta = "./Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
i = 0

lista = []
for arquivo in arquivos:
    print(os.path.join(root, arquivo))
    print("A realizar Teste ", i)
    campos = {}
    f = open(os.path.join(root, arquivo))
    acordaos = json.load(f)
    if arquivo == "jtcampc(a|t)_acordaos.json":
        print("jtcampc")
        campos2 = {}
        campos["_id"] = "jtcampca"
        campos2["_id"] = "jtcampct"
        campos["nome"] = nomes[campos["_id"]]
        campos2["nome"] = nomes[campos2["_id"]]
        descritores = []
        descritores2 = []
        area1=[]
        area1_2=[]
        area2=[]
        area2_2=[]
        for acordao in acordaos:
            if "Descritores" in acordao:
                if campos["_id"] == "jtcampca":
                    for elem in acordao["Descritores"]:
                        if elem not in descritores:
                            descritores.append(elem)
                else:
                    for elem in acordao["Descritores"]:
                        if elem not in descritores2:
                            descritores2.append(elem)
            if "Área Temática 1" in acordao:
                if campos["_id"] == "jtcampca":
                    for elem in acordao["Área Temática 1"]:
                        if elem not in area1:
                            area1.append(elem)
                else:
                    for elem in acordao["Área Temática 1"]:
                        if elem not in area1_2:
                            area1_2.append(elem)
            if "Área Temática 2" in acordao:
                if campos["_id"] == "jtcampca":
                    for elem in acordao["Área Temática 2"]:
                        if elem not in area2:
                            area2.append(elem)
                else:
                    for elem in acordao["Área Temática 2"]:
                        if elem not in area2_2:
                            area2_2.append(elem)

        del acordaos
        f.close()
        campos["descritores"] = descritores
        campos2["descritores"] = descritores2
        lista.append(campos)
        lista.append(campos2)
    else:
        campos["_id"] = acordaos[0]["tribunal"]
        campos["nome"] = nomes[campos["_id"]]
        descritores = []
        area1=[]
        area2=[]
        for acordao in acordaos:
            if "Descritores" in acordao:
                for elem in acordao["Descritores"]:
                    if elem not in descritores:
                        descritores.append(elem)
            if "Área Temática 1" in acordao:
                for elem in acordao["Área Temática 1"]:
                    if elem not in area1:
                        area1.append(elem)
            if "Área Temática 2" in acordao:
                for elem in acordao["Área Temática 2"]:
                    if elem not in area2:
                        area2.append(elem)
        del acordaos
        f.close()
        campos["descritores"] = descritores
        lista.append(campos)

fp = open("campos_tribunal.json", "w", encoding="utf-8")
json.dump(lista, fp, indent=" ", ensure_ascii=False)
fp.close()
