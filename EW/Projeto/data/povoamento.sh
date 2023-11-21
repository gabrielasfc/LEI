mongoimport -d ProjetoEngWeb -c acordaos --jsonArray mongodb://localhost:27017/ProjetoEngWeb acordaos.json
mongoimport -d ProjetoEngWeb -c tribunals --jsonArray mongodb://localhost:27017/ProjetoEngWeb tribunais.json
mongoimport -d ProjetoEngWeb -c fields --jsonArray mongodb://localhost:27017/ProjetoEngWeb fields.json
mongoimport -d ProjetoEngWeb -c acordaos_details --jsonArray mongodb://localhost:27017/ProjetoEngWeb acordaos_details.json
