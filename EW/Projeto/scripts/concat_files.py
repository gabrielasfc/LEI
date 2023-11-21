import json
import os
from datetime import datetime

files = os.listdir("./datasets")

database = []
for file in files:
    print(file)
    with open('./datasets/' + file) as descriptor:
        database += json.load(descriptor)

with open("./database.json" , "w") as f:
    json.dump(database, f, ensure_ascii=False)