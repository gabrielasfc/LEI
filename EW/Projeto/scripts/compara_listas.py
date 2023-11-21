l1 = [
    "Referência Processo",
    "Nº Único do Processo",
    "Recurso",
    "Data",
    "Processo no Tribunal Recorrido",
    "Apenso",
    "Tribunal Recorrido",
    "Referências Internacionais",
    "Legislação Estrangeira",
    "Jurisprudência Internacional",
    "Jurisprudência Nacional",
    "Nº Convencional",
    "Legislação Nacional",
    "Privacidade",
    "Área Temática",
    "Indicações Eventuais",
    "Processo",
    "Relator",
    "Descritores",
    "Nº do Documento",
    "Data do Acordão",
    "Votação",
    "Meio Processual",
    "Decisão",
    "Sumário",
    "Decisão Texto Integral",
    "url",
    "tribunal",
]
l2 = [
    "Processo",
    "Nº Convencional",
    "Relator",
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
]

lista = []
for elem in l2:
    if elem not in lista:
        lista.append(elem)

for elem in l1:
    if elem not in lista:
        lista.append(elem)
print(lista)
