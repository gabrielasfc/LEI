import re
import json

"""
string = "AC CONFLITOS PROC11/2006 DE 2006/07/04.\nAC CONFLITOS PROC371/02 DE 2002/02/27.\nAC CONFLITOS PROC4/03 DE 2004/03/09.\nAC CONFLITOS PROC5/04 DE 2004/09/23.\nAC STJ DE 1978/06/06 IN BMJ N278 PAG122.\nAC STJ PROC09S02332 DE 2009/05/14.\nAC CONFLITOS PROC4/04 DE 2004/12/16."
string1 = "."
lista = re.split(r".\n", string1)
lista[-1] = lista[-1][:-1]
print(lista)
"""
dir = "./Acordaos/"

"""
  "jcon_acordaos.json",
    "jtrp_acordaos.json",
    "jsta_acordaos.json",
"""
arquivos = ["jcon_acordaos.json", "atco1_acordaos.json"]

arquivos1 = [
    "jsta_acordaos.json",
]
arquivos2 = ["jtre_acordaos.json"]
# "Referência a Pareceres"
"""
for file in arquivos:
    print(file)
    f = open(dir + file, "r")
    lista = json.load(f)
    for elem in lista:
        if "Jurisprudências" in elem:
            if "Jurisprudência Constitucional" in elem["Jurisprudências"]:
                novo_val = re.split(
                    r"\.\n", elem["Jurisprudências"]["Jurisprudência Constitucional"]
                )
                if novo_val[-1] != "" and novo_val[-1][-1] == ".":
                    novo_val[-1] = novo_val[-1][:-1]  # retirar o último ponto
                # novo_val = [elem["Jurisprudências"]["Jurisprudência Constitucional"]]
                lista_final = []
                for val in novo_val:
                    if re.fullmatch(r"\s*", val):
                        pass
                    else:
                        lista_final.append(val.strip())
                if len(lista_final) > 0:
                    elem["Jurisprudências"][
                        "Jurisprudência Constitucional"
                    ] = lista_final
                else:
                    elem["Jurisprudências"].pop("Jurisprudência Constitucional")
                    if len(elem["Jurisprudências"]) == 0:
                        elem.pop("Jurisprudências")
    """
"""
for file in arquivos:
    print(file)
    f = open(dir + file, "r")
    lista = json.load(f)
    for elem in lista:
        if "Jurisprudências" in elem:
            if "Jurisprudência Nacional" in elem["Jurisprudências"]:
                if len(elem["Jurisprudências"]["Jurisprudência Nacional"]) == 1:
                    novo_val = re.split(
                        r"\.\;", elem["Jurisprudências"]["Jurisprudência Nacional"][0]
                    )
                    if novo_val[-1] != "" and novo_val[-1][-1] == ".":
                        novo_val[-1] = novo_val[-1][:-1]  # retirar o último ponto
                    # novo_val = [elem["Jurisprudências"]["Jurisprudência Nacional"]]
                    lista_final = []
                    for val in novo_val:
                        if re.fullmatch(r"\s*", val):
                            pass
                        else:
                            lista_final.append(val.strip())
                    if len(lista_final) > 0:
                        elem["Jurisprudências"]["Jurisprudência Nacional"] = lista_final
                    else:
                        elem["Jurisprudências"].pop("Jurisprudência Nacional")
                        if len(elem["Jurisprudências"]) == 0:
                            elem.pop("Jurisprudências")
"""
"""
for file in arquivos1:
    print(file)
    f = open(dir + file, "r")
    lista = json.load(f)
    for elem in lista:
        if "Área Temática 2" in elem:
            novo_val = re.split(r"\.[ ]\/|\.", elem["Área Temática 2"])
            if novo_val[-1] != "" and novo_val[-1][-1] == ".":
                novo_val[-1] = novo_val[-1][:-1]  # retirar o último ponto
            lista_final = []
            for val in novo_val:
                if re.fullmatch(r"\s*", val):
                    pass
                else:
                    lista_final.append(val.strip())
            if len(lista_final) > 0:
                elem["Área Temática 2"] = lista_final
            else:
                if len(elem) == 0:
                    elem.pop("Área Temática 2")
    f.close()
    f = open(dir + file, "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
"""
arquivos1 = ["jdgpj_acordaos.json"]
for file in arquivos1:
    print(file)
    f = open(dir + file, "r")
    lista = json.load(f)
    for elem in lista:
        if "Réu" in elem:
            if len(elem["Réu"]) == 1:
                novo_val = re.split(r"\.\;", elem["Réu"][0])
                if novo_val[-1] != "" and novo_val[-1][-1] == ".":
                    novo_val[-1] = novo_val[-1][:-1]  # retirar o último ponto
                lista_final = []
                for val in novo_val:
                    if re.fullmatch(r"\s*", val):
                        pass
                    else:
                        lista_final.append(val.strip())
                if len(lista_final) > 0:
                    elem["Réu"] = lista_final
    f.close()
    f = open(dir + file, "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
