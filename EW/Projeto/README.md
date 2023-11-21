# Base de Dados de Acordãos

#### Universidade do Minho
#### Licenciatura em Engenharia Informática

#### Trabalho Prático - Engenharia Web

#### Autores:
- A96455 - Nuno Guilherme Cruz Varela - [@GVarelaa](https://github.com/GVarelaa)
- A97393 - Gabriela Santos Ferreira da Cunha - [@gabrielasfc](https://github.com/gabrielasfc)
- A97496 - Miguel Ângelo Silva Senra - [@MiguelSenra](https://github.com/MiguelSenra)

## índice
- [Índice](#índice)
- [Introdução](#introdução)
- [Manipulação dos Dados](#manipulação-dos-dados)
- [Arquitetura Aplicacional](#arquitetura-aplicacional)
- [Conclusão](#conclusão)
- [Anexos](#anexos)



## Introdução
No âmbito do projeto da unidade curricular de Engenharia Web, foi desenvolvida uma plataforma de auxílio ao Ministério da Justiça Português, com vista a unanimizar a consulta dos conjuntos de acórdãos que cada tribunal, com autonomia própria, disponibiliza periodicamente.
Cada tribunal tem a sua própria base de dados, resultando num conjunto distinto de 14 ficheiros JSON. Incialmente, foi efetuado o tratamento destes dados e criada uma base de dados unificada. Em seguida, foram desenvolvidos os serviços de autenticação e API, com recurso ao Express.js, e interface, utilizando React.js. 

## Manipulação dos Dados
Para ser possível realizar o carregamento de todos os dados fornecidos foram, primeiramente, realizados scripts em Python para o processamento, parsing, manipulação e normalização dos dados. Dado que o nosso conhecimento sobre a área não é muito extenso, foi necessário realizar uma análise e uma investigação acerca do significado de cada um dos campos.  Desta forma, conseguimos gerar um ficheiro que indicava todos os campos distintos que um ficheiro possuía juntamente com o tipo de dados que guardava, verificando se existia alguma inconsistência no tipo de dados dentro do mesmo ficheiro, o que acabou por nunca se verificar.

### Agrupamento dos valores em dicionários
Ao verificar os campos de cada um dos ficheiros, verificamos que alguns possuíam informação exclusiva aos mesmos. Pelo que apuramos, segundo o url que foi disponibilizado, estas informações pertenciam ao atributo 'Decisão Texto Integral'. Assim, para uma melhor organização aquando da apresentação do acórdão, construímos um novo atributo cujo nome é "Informação Auxiliar" que é um dicionário com toda esta informação extra.

### Análise de acórdãos repetidos
Durante a análise, apercebemo-nos da presença de alguns registos que estavam duplicados, possuindo exatamente os mesmos campos e os mesmos valores. Desta forma, utilizamos um script que percorria todos os registos de cada um dos ficheiros verificando se havia registos duplicados e removendo-os em caso afirmativo.

### Correção de nomes de atributos para alguns valores
Através da visualização de alguns dos ficheiros foi possível notar que alguns atributos possuíam um valor não correspondente ao tipo de atributo. Para além de causar problemas na hora de observar os campos do acórdão, que apesar de não ser da nossa responsabilidade pode ser corrigido, poderia causar dúvida em quem por vezes estivesse a adicionar novos acórdãos à base de dados. Este processo foi realizado manualmente, pelo que não é garantido que todas as inconsistências fossem corrigidas. Para resolver este problema utilizámos a funcionalidade find and replace disponibilizada pela ferramenta utilizada.

### Limpeza de campos vazios
Foi também possível observar que alguns campos no respetivo valor possuíam uma string vazia, ou seja, sem qualquer informação relevante ao processo. Considerando que iremos utilizar uma base de dados não relacional, o MongoDB, não necessitamos de colocar todos os campos, tendo eles valor ou não na base de dados. 

### Limpeza da variável "Texto Integral"
Durante a análise, na maior parte dos datasets, apercebemo-nos da existência de 2 variáveis que estavam relacionadas - as variáveis 'Texto Integral e Decisão Texto Integral'. A primeira variável é uma variável booleana, que apenas possuía 2 valores (S(Sim) e N(Não)). Quando o valor desta variável era N, não existia o segundo atributo, mas se esta possuísse o valor S, então o atributo 'Decisão Texto Integral' já estava presente. Desta forma, este campo booleano foi removido, visto que o valor do segundo atributo é suficiente e pode ser guardado tal como está, sem ser necessária qualquer outra informação que indique a presença do mesmo.

### Junção de campos que eram semelhantes 
De forma a garantir uma uniformização da nossa base de dados, sem possuir ambiguidades nem redundâncias, e de forma a permitir uma uniformização da informação de cada um dos acórdãos, foi necessário determinar os campos cujo nome era diferente mas o valor era correspondente ao mesmo atributo. Houve um exemplo que foi muito claro: o atributo "Data do Acordão" e o atributo "Data do Acórdão". Numa uniformização automática não era possível resolver este problema pelo que estes casos foram tratados individualemente através de outros scripts.

### Tratamento das datas
As datas ao longo dos vários ficheiros apresentavam um formato fora do convencional (mm/dd/aaaa) ou (mm-dd-aaaa). Consequentemente, de forma a minimizar possíveis ambiguidades tanto no lado do cliente como no nosso, decidimos alterar para o formato mais utilizado (dd/mm/aaaa). De notar ainda um quarto formato que apareceu onde o ano era apenas definido por 2 dígitos e não 4, respetivos aos anos antes de 2000, onde forçamos o aparecimento do ano (19xx). 

### Tratamento dos campos em listas
Foi possível denotar que alguns campos correspondiam a listas mas estavam expressos numa única string onde os vários valores estavam agrupados por separadores. Dentro de cada ficheiro, o separador era praticamente igual para todos os campos podendo haver uma ou outra exceção. Para tal, realizamos uma análise para verificar quais os separadores de cada um dos ficheiros. Este foi dos processos mais demorados do tratamento mas permitiu uma melhor usabilidade e uniformização dos dados do sistema. 

### Remoção de campos desnecessários
Alguns dos atributos presentes nos acórdãos referenciavam a data/ano em que o acórdão se tornou disponível. Também foi possível observar que todos os registos possuíam o atributo url que era referente ao link onde o acórdão estava disponível no seu sistema. Considerando que o nosso objetivo é agregar toda esta informação numa única base de dados, a referência a outros sistemas passaria a não ser relevante pelo facto de toda a informação estar disponibilizada neste mesmo sistema.

### Escolha da chave principal 
Antes de realizar a importação dos registos, necessitamos de definir um identificador "_id". Analisando todos os campos que tínhamos disponíveis, aquele que nos pareceu mais propício era o campo 'Processo'. Para tal, teríamos que garantir que não existissem valores duplicados. No entanto, alguns valores repetiam-se, apesar dos registos serem diferentes, o que inviabilizou esta abordagem. Assim, considerando que nenhum dos outros campos eram comuns a todos os registos e, se o fossem, também não eram únicos, adotamos a estratégia de definir o identificador através de um contador, com o cuidado de garantir que os identificadores não fossem repetidos posteriormente. 

## Arquitetura Aplicacional
A solução arquitetural concebida baseia-se em 3 serviços aplicacionais heterogéneos, proporcionando uma melhor manutenção e escabilidade do projeto e facilitando o seu desenvolvimento. Cada serviço contém funcionalidades específicas e desempenha um diferente papel no funcionamento da aplicação. 

### Autenticação
O serviço de autenticação é destinado ao registo e autenticação dos utilizadores, garantindo a segurança da aplicação. Sendo independente dos dados relativos aos acórdãos, pudemos começar o desenvolvimento deste serviço enquanto efetuavamos o tratamento dos dados. Para gerir os utilizadores e as respetivas sessões foram utilizados os módulos passport-local e jsonwebtoken. Através da atribuição de um token a cada utilizador, garantimos que apenas utilizadores autorizados podem aceder a determinadas rotas e realizar ações específicas, de acordo com os seus níveis de acesso. As rotas definidas para a autenticação são as seguintes:

| Método | Rota    | Descrição |
|--------|---------|-----------|
| GET | /users     | Devolve os utilizadores presentes na coleção de utilizadores |
| GET | /users/:id | Devolve um utilizador consoante o id passado no parâmetro |
| GET | /users/:id/favorites | Devolve os favorites de um utilizador passado como parâmetro |
| GET | /users/check-email/:email | Verifica se o email passado como parâmetro já existe |
| GET | /users/check-username/:username | Verifica se o username passado como parâmetro já existe |
| GET | /users/login/facebook | Redireciona para a autenticação por Facebook |
| GET | /users/login/facebook/callback | Rota callback da autenticação do Facebook |
| GET | /users/login/google | Redireciona para a autenticação por Google |
| GET | /users/login/google/callback | Rota callback da autenticação do Google |
| POST | /users | Adiciona um utilizador à coleção de utilizadores |
| POST | /users/register | Adiciona um utilizador à coleção de utilizadores (registo) |
| POST | /users/login | Autentica um utilizador |
| POST | /users/image/:id | Guarda uma imagem de um utilizador passado por parâmetro |
| PUT | /users/:id | Altera as informações de um utilizador
| PUT | /users/:id/password | Altera a password de um utilizador |
| PUT | /users/:id/favorites | Adiciona um favorito ao utilizador passado por parâmetro |
| PUT | /users/:id/removeFavorite | Remove um favorite ao utilizador passado por parâmetro |
| DELETE | /users/:id | Remove um utilizador passado por parâmetro da coleção |

### API de Dados
Diretamente conectado à base de dados, este serviço é responsável pelo armazenamento e gestão dos dados da aplicação. A base de dados foi criada com recurso ao software MongoDB, armazenando informações dos utilizadores e dos acórdãos. A API fornece, assim, endpoints para a leitura, criação, atualização e exclusão de dados, permitindo que a aplicação interaja com a base de dados de forma segura e eficiente. Todo este serviço encontra-se protegido de forma a que os pedidos só possam ser realizados sob a existência de token válido. Para além disso, existem verificações relativas ao nível de acesso do utilizador correspondente ao token, uma vez que alguns pedidos são exclusivos a uma determinada gama de utilizadores. Este serviços tem acesso às seguintes coleções:

- **Acordãos (acordaos)** : coleção que contém informação sobre todos os acordãos
- **Campos (fields)** : coleção que contém todos os campos que podem estar presentes nos acordãos
- **Tribunais (tribunals)** : coleção que contém todos os tribunais e respetivos descritores
- **Detalhes dos campos (acordaos_details)** : coleção com informação relativa aos vários campos dos acordãos

| Coleção | Método | Rota | Descrição |
|---------|--------|------|-----------|
| Acordãos | GET | /acordaos | Devolve os acordãos da coleção filtrados por uma query string |
| Acordãos | GET | /acordaos/number | Devolve o número de acordãos presentes na coleção |
| Acordãos | GET | /acordaos/:id | Devolve o acordão com o id passado como parâmetro |
| Acordãos | POST | /acordaos | Adiciona um acordão à coleção |
| Acordãos | PUT | /acordaos/:id | Altera um acordão com o id passado como parâmetro |
| Acordãos | DELETE | /acordaos/:id | Remove um acordão da coleção com o id passado como parâmetro |
| Campos | GET | /fields | Devolve todos os registos presentes na coleção |
| Campos | POST | /fields | Adiciona um novo campo à coleção |
| Campos | PUT | /fields:id | Altera o campo com o id passado como parâmetro |
| Campos | DELETE | /fields:id | Remove um campo da coleção com o id passado como parâmetro |
| Tribunais | GET | /tribunais | Devolve todos os tribunais presentes na coleção |
| Tribunais | GET | /tribunais/:id | Devolve o tribunal com o id passado como parâmetro |
| Tribunais | POST | /tribunais | Adiciona um novo tribunal à coleção |
| Tribunais | PUT | /tribunais/:id | Altera um tribunal com o id passado como parâmetro |
| Tribunais | DELETE | /tribunais/:id | Remove um tribunal com o id passado como parâmetro |
| Detalhes dos campos | GET | /details | Devolve todos os detalhes dos campos presentes na coleção |
| Detalhes dos campos | POST | /details | Adiciona um novo detalhe de um campo à coleção |
| Detalhes dos campos | PUT | /details/:id | Altera um detalhe de um campo |
| Detalhes dos campos | DELETE | /details/:id | Remove um detalhe de um campo da coleção |

Um dos objetivos do grupo passava por implementar pesquisas e consultas de informação eficientes. Deste modo, optamos por recorrer aos índices que o MongoDB disponibiliza que são estruturas de dados na forma de árvores que nos permitem efetuar pesquisas rapidamente. No arranque da API de dados são criadas várias estruturas: uma para efetuar pesquisa livre sobre todos os campos dos acordãos e as restantes para implementar os filtros disponibilizados do lado da interface.

### Interface
O serviço mais próximo do utilizador é responsável pela construção de uma interface gráfica a apresentar aos clientes da aplicação. É sobre esta interface que os clientes podem efetuar os seus pedidos, sendo, depois, reencaminhados para os restantes serviços, através de rotas definidas.


## Conclusão
Por fim, consideramos que este projeto se enquadra com o contexto do mundo real, uma vez que os datasets podem não estar uniformizados, sendo importante tratá-los devidamente antes de avançar para a fase seguinte. O desenvolvimento dos serviços aproximou-se do que foi feito nas aulas da unidade curricular mas em maior escala. Relativamente à interface, decidimos explorar e aprimorar o seu aspeto, algo que não era foco nas aulas devido ao tempo reduzido mas que se justifica ter em consideração na realização de um projeto extenso. Assim, utilizamos novas ferramentas, como foi o caso do React, de modo a apresentar uma interface mais próxima do que é realmente produzido em plataformas do quotidiano. De encontro ao que aprendemos, a realização dos 3 microsserviços destacou a importância de uma arquitetura modular e distribuída para o desenvolvimento de sistemas escaláveis, seguros e de fácil utilização. Deste modo, estamos satisfeitos com os resultados obtidos.

## Anexos
### Manual de Utilização

Para simplificar o arranque da aplicação, composta por vários serviços que precisam de interagir entre si, foi utilizado o Docker Compose. Através da definição das configurações no ficheiro ``docker-compose.yml``, o Docker Compose cria e inicia automaticamente todos os containers necessários, configurando também a comunicação entre eles. Para simplificar a importação dos dados, foi criado um script para criar a base de dados e as suas coleções, efetuando o respetivo povoamento da mesma.

1. Clone o repositório para a sua máquina e mova-se para a pasta do projeto:
```bash
git clone https://github.com/GVarelaa/ENGWEB2023-Projeto.git
cd ENGWEB2023-Projeto
```

2. Verifique se o Docker e o Docker Compose estão instalados.

3. Na pasta do projeto, construa e inicie os containers para correr o projeto:

Para correr em modo detached (segundo plano):
```bash
docker-compose up -d --build
```
Para ter acesso aos logs (primeiro plano):
```bash
docker-compose up --build
```

4. Mova-se para a pasta ``data``:
```bash
cd data
```

5. Transfira os [ficheiros](https://mega.nz/folder/RA1xFChZ#1nIryTRdZmmrBbHXI_cukw) diretamente para a pasta.

6. Conceda permissões ao script:
```bash
chmod +x povoamento.sh
```

7. Execute o script:
```bash
./povoamento.sh
```

8. A aplicação deverá estar disponível em: [localhost:8073/](https://localhost:8073/)



