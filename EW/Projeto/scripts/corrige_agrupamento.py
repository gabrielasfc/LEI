import json


lista1 = [
    "Processo",
    "Nº Convencional",
    "Relator",
    "Secção",
    "Descritores",
    "Data do Acordão",
    "Votação",
    "Tribunal Recorrido",
    "Meio Processual",
    "Decisão",
    "Legislação Nacional",
    "Sumário",
    "Decisão Texto Integral",
    "url",
    "tribunal",
    "Indicações Eventuais",
    "Processo no Tribunal Recorrido",
    "Jurisprudência Nacional",
    "Legislação Comunitária",
    "Legislação Estrangeira",
    "Jurisprudência Internacional",
    "Referência de Publicação",
    "Área Temática",
    "Privacidade",
    "Nº do Documento",
    "Objecto",
    "Tribunal",
    "Referência a Pareceres",
    "Data de Entrada",
    "Jurisprudência Estrangeira",
    "Referência Processo",
    "Nº Único do Processo",
    "Recurso",
    "Apenso",
    "Área Temática 1",
    "Área Temática 2",
    "Referências Internacionais",
    "Doutrina",
    "Nº do Volume",
    "Recorrente",
    "Recorrido 1",
    "Recorrido 2",
    "Parecer Ministério Publico",
    "Referência Publicação 2",
    "Referência Publicação 1",
    "Página",
    "Data do Apêndice",
    "Apêndice",
    "Ano da Publicação",
    "1ª Pág. de Publicação do Acordão",
    "Recusa Aplicação",
]

lista3=["Data da Reclamação"]
file = "/home/miguel_senra/Desktop/TrabalhoEW/Acordaos/jstj_acordaos.json"
f = open(file, "r")
lista = json.load(f)
i = 0
for elem in lista:
    print(i)
    i += 1
    valores_extra = dict()
    if "Informação Auxiliar" in elem:
        lista2 = []
        for key in elem["Informação Auxiliar"]:
            if key in lista3:
                elem[key] = elem["Informação Auxiliar"][key]
                lista2.append(key)

        for key in lista2:
            elem["Informação Auxiliar"].pop(key)

        if len(elem["Informação Auxiliar"]) == 0:
            elem.pop("Informação Auxiliar")

f.close()
f = open(file, "w", encoding="utf-8")
json.dump(lista, f, indent=" ", ensure_ascii=False)
f.close()
