****************************************************************
*****         SISTEMAS DISTRIBUIDOS - TRABALHO MPI         *****
****************************************************************
                   Aproximação de PI (Wallis)                  

NOME: Alfredo Savi | R.A: 1882872


// Instalação dos pacotes OPENMPI
$ sudo apt install openmpi-bin openmpi-doc openmpi-common

// Instalação do compilador
$ sudo apt install libopenmpi-dev


para compilar o arquivo:
$ mpicc arquivo.c -o nome_objeto -lm   

para executar o projeto:
$ mpirun --oversubscribe -np 2 ./nome_objeto

* Diretiva --oversubscribe vai ignorar quantos cores fisicos vc tem e vai deixar vc executar com mais, exemplo: Se voce tiver 4 cores fisicos e executar com 5 ele vai deixar.

* Parametro -np numero de nucleos
OBS: Ela so trabalha com core fisico