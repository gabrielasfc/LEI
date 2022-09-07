# Projeto

No âmbito da UC de Sistemas Operativos, foi-nos proposta a implementação de um serviço que permita aos utilizadores armazenar uma cópia dos seus ficheiros
de forma segura e eficiente, poupando espaço de disco.

Assim, o projeto consiste num servidor que acolhe vários pedidos de transformações de ficheiros, enviados por clientes, de forma concorrente. 
O serviço disponibiliza as seguintes funcionalidades de compressão/descompressão e cifragem/decifragem dos ficheiros a serem armazenados:

- __bcompress__ / __bdecompress__. Comprime / descomprime dados com o formato bzip2.
- __gcompress__ / __gdecompress__. Comprime / descomprime dados com o formato gzip.
- __encrypt__ / __decrypt__. Cifra / decifra dados.
- __nop__. Copia dados sem realizar qualquer transformação.

O cliente pode também definir a prioridade da sua transformação no servidor, enviando-a pelo pedido. A arquitetura do servidor, assim como a comunicação
entre este e o cliente encontra-se mais detalhada no nosso [relatório](https://github.com/gabrielasfc/LEI/blob/master/SO/Projeto/Relat%C3%B3rio.pdf).

## Comandos:
Compilar o programa: ```make```

Iniciar o servidor: ```./bin/sdstored etc/sdstored.conf```

Enviar pedido: ```./bin/sdstore proc-file -p <priority> etc/input.txt etc/output.txt <transformation-1> ... <transformation-n>```


## Contributors:
- Gabriela Cunha [@gabrielasfc](https://github.com/gabrielasfc)
- Guilherme Varela [@GVarelaa](https://github.com/GVarelaa)
- Miguel Braga [@MiguelB625](https://github.com/MiguelB625)
