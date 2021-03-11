/*Leia um número inteiro que representa um tempo em
segundos. Em seguida, imprima esse tempo em horas,
minutos e segundos.*/
#include <stdio.h>

int main()
{   // declação das variáveis 
    int tempo, hora, minuto, segundo;
    
    //input da variável tempo
    printf("Tempo inteiro: ");
    scanf("%d", &tempo);
    
    //transformação para hora, minuto e segundo
    hora = tempo / 3600;
    minuto = (tempo % 3600) / 60;
    segundo = (tempo % 3600) % 60  ;
    
 
    //output das variáveis
    printf("Hora: %d\n", hora);
    printf("Minuto: %d\n", minuto);
    printf("Segundo: %d\n", segundo);
    printf("Tempo total= %d:%d:%d\n", hora, minuto, segundo);
    
}