#include <stdio.h>

struct Veiculo {
    int id; // identificador único
    char placa[8];
    char modelo[30];
    float consumoKmL; //Consumo por litro
    float capacidadeCarga; //Capacidade de carga em toneladas
    int status; // 0 - disponivel, 1 - em viagem, 2 - em manutenção
};