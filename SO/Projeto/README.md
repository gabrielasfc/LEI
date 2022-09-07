# Projeto

No âmbito da UC de Sistemas Operativos, foi-nos proposta a implementação de um serviço que permita aos utilizadores armazenar uma cópia dos seus ficheiros
de forma segura e eficiente, poupando espaço de disco.

Assim, o projeto consiste num servidor que acolhe vários pedidos de transformações de ficheiros, enviados por clientes, de forma concorrente. As
transformações existentes podem ser consultadas na seguinte [pasta](https://github.com/gabrielasfc/LEI/tree/master/SO/Projeto/bin/sdstore-transformations).
O cliente pode também definir a prioridade da sua transformação no servidor, enviando-a pelo pedido. A arquitetura do servidor, assim como a comunicação
entre este e o cliente encontra-se mais detalhada no nosso [relatório](https://github.com/gabrielasfc/LEI/blob/master/SO/Projeto/Relat%C3%B3rio.pdf).

## Comandos:
Compilar o programa: ```make```
Iniciar o servidor: ```./bin/sdstored config/config.txt bin/```
Enviar pedido: ```./bin/sdstore proc-file -p <priority> <input-file> <output-file> <transformation-1> ... <transformation-n>```


## Contributors:
- Gabriela Cunha [@gabrielasfc](https://github.com/gabrielasfc)
- Guilherme Varela [@GVarelaa](https://github.com/GVarelaa)
- Miguel Braga [@MiguelB625](https://github.com/MiguelB625)
