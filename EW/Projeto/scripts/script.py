import os 
import re
import json

folder = "./datasets"
files = os.listdir(folder)

database = []
test = 1
i = 0
for file in files:
    print("A realizar teste ", test)
    test += 1

    with open(folder + '/' + file) as descriptor:
        accordions = json.load(descriptor)
        for accordion in accordions:
            accordion["_id"] = "a" + str(i)
            i += 1

            if "Magistrado" in accordion:
                accordion["Relator"] = accordion["Magistrado"]
                accordion.pop("Magistrado")
                
            if "Texto Integral" in accordion and "Decisão Texto Integral" in accordion:
                accordion.pop("Texto Integral")
            elif "Texto Integral" in accordion:
                accordion["Decisão Texto Integral"] = accordion["Texto Integral"]
                accordion.pop("Texto Integral")

            if "Texto Parcial" in accordion:
                accordion.pop("Texto Parcial")

            if "Data do Acordão" in accordion:
                accordion["Data"] = accordion["Data do Acordão"]
                accordion.pop("Data do Acordão")
            elif "Data da Decisão" in accordion:
                accordion["Data"] = accordion["Data da Decisão"]
                accordion.pop("Data da Decisão")
            elif "Data da Decisão Sumária" in accordion:
                accordion["Data"] = accordion["Data da Decisão Sumária"]
                accordion.pop("Data da Decisão Sumária")

            if "url" in accordion:
                accordion.pop("url")
        
        database += accordions


with open('./tratados/database.json', 'w') as file:
    json.dump(database, file, ensure_ascii=False)