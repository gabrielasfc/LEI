def print_mongoose_schema(data, indent=""):
    for key, value in data.items():
        if isinstance(value, dict):
            print(f"{indent}'{key}': {{")
            print_mongoose_schema(value, indent + "  ")
            print(f"{indent}}}")
        elif isinstance(value, list) and len(value) > 0 and isinstance(value[0], dict):
            print(f"{indent}'{key}': [")
            print_mongoose_schema(value[0], indent + "  ")
            print(f"{indent}]")
        else:
            print(f"{indent}'{key}': {type_to_mongoose(value)},")


def type_to_mongoose(value):
    if isinstance(value, str):
        return "String"
    elif isinstance(value, int):
        return "Number"
    elif isinstance(value, bool):
        return "Boolean"
    elif isinstance(value, list):
        return "[String]"
    elif isinstance(value, dict):
        return "{}"
    else:
        return "Mixed"


# Exemplo de uso:
data = {
    "Processo": "String",
    "Relator": "String",
    "Descritores": ["String"],
    "Data do Acordão": "String",
    "Votação": "String",
    "Sumário": "String",
    "Decisão Texto Integral": "String",
    "tribunal": "String",
    "_id": "String",
    "Decisão": "String",
    "Meio Processual": "String",
    "Legislações": {
        "Legislação Nacional": "String",
        "Legislação Comunitária": "String",
        "Legislação Estrangeira": "String",
    },
    "Área Temática 1": ["String"],
    "Referências Internacionais": ["String"],
    "Jurisprudências": {
        "Jurisprudência Nacional": "String",
        "Jurisprudência Internacional": "String",
        "Jurisprudência Estrangeira": "String",
        "Jurisprudência Constitucional": "String",
        "Outra Jurisprudência": "String",
    },
    "Tribunal Recorrido": "String",
    "Processo no Tribunal Recorrido": "String",
    "Referência Processo": "String",
    "Indicações Eventuais": ["String"],
    "Nº Convencional": "String",
    "Nº do Documento": "String",
    "Requerente": "String",
    "Requerido": ["String"],
    "Data de Entrada": "String",
    "Objecto": "String",
    "Área Temática 2": ["String"],
    "Doutrina": ["String"],
    "Recusa Aplicação": "String",
    "Referência a Pareceres": ["String"],
    "Privacidade": "String",
    "Apêndice": "String",
    "Data do Apêndice": "String",
    "Referências Publicação": ["String"],
    "Reclamações": ["String"],
    "Apenso": "String",
    "Data da Decisão": "String",
    "Recurso": "String",
    "Juízo ou Secção": "String",
    "Tribunal": "String",
    "Parecer Ministério Publico": "String",
    "Magistrado": "String",
    "Acordão": "String",
    "Volume dos Acordãos do T.C.": "String",
    "Autor": "String",
    "Réu": ["String"],
}

print_mongoose_schema(data)
