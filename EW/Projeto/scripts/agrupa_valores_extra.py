import json
import os

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

keys = [
    "1ª Pág. de Publicação do Acordão",
    "Nº do Volume",
    "Página",
    "Parecer Ministério Público",
    "Nº Processo/TAF",
    "Observações",
    "Peça Processual",
    "Nº Único do Processo",
    "Acórdão",
    "Espécie",
    "Normas Apreciadas",
    "Normas Julgadas Inconst.",
    "Volume dos Acórdãos do T.C.",
    "Constituição",
    "Nº do Diário da República",
    "Série do Diário da República",
    "Data do Diário da República",
    "Página do Diário da República",
    "Nº do Boletim do M.J.",
    "Página do Boletim do M.J.",
    "Normas Suscitadas",
    "Declaração de Voto",
    "Voto Vencido",
    "Normas Declaradas Inconst.",
    "Página do Volume",
    "Tipo de Ação",
    "Tipo de Contrato",
    "Texto das Cláusulas Abusivas",
]

"""
# Data,
file = "./Acordaos/jsta_acordaos.json"
f = open(file, "r")
lista = json.load(f)
i = 0
for elem in lista:
    print(i)
    i += 1
    valores_extra = dict()
    for key in elem:
        if key not in lista1:
            valores_extra[key] = elem[key]
    for key in valores_extra:
        elem.pop(key)
    if len(valores_extra) > 0:
        elem["Informação Auxiliar"] = valores_extra
"""

pasta = "./Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
# arquivos = ["atco1_acordaos.json"]
for arquivo in arquivos:
    print(os.path.join(root, arquivo))
    f = open(os.path.join(root, arquivo), "r")
    lista = json.load(f)
    for elem in lista:
        valores_extra = dict()
        for key in keys:
            if key in elem:
                valores_extra[key] = elem[key]
                elem.pop(key)
        if len(valores_extra) > 0:
            if "Informação Auxiliar" not in elem:
                elem["Informação Auxiliar"] = valores_extra
            else:
                elem["Informação Auxiliar"].update(valores_extra)
    f.close()
    f = open(os.path.join(root, arquivo), "w", encoding="utf-8")
    json.dump(lista, f, indent=" ", ensure_ascii=False)
    f.close()
