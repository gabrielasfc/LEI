import re
import os
import json

pasta = "/home/miguel_senra/Desktop/TrabalhoEW/Acordaos"
for root, dirs, arquivo in os.walk(pasta):
    arquivos = arquivo
print(arquivos)
for file in arquivos:
    print(file)
    f = open(pasta+"/"+file, "r")
    lista = json.load(f)
    for elem in lista:
        t=False
        for key in elem:
            if re.search(r"Data",key):
                t=True
                break
        if t==False:
            print(elem["Processo"])
    f.close()

