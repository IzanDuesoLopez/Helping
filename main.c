#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

    FILE* fichero;
    int contador = 0;
    char frase[80];
    char fraseCifrada[160];
    int opcion;
    char matrizCifr[7][7] = {
                            {' ','X','I','F','R','A','T'},
                            {'N','A','B','C','D','E','F'},
                            {'O','G','H','I','J','K','L'},
                            {'R','M','N','O','P','Q','R'},
                            {'M','S','T','U','V','W','X'},
                            {'A','Y','Z',' ','1','2','3'},
                            {'L','4','5','6','7','8','9'}
                            };

    char filaCifrado [7] = {' ','N','O','R','M','A','L'};
    char columnaCifrado [7] = {' ','X','I','F','R','A','T'};

    printf("Selecciona opcion del menu: \n");
    scanf("%d", &opcion);
    fflush(stdin);
    switch(opcion){
    case 1:
        printf("Introduce un texto por teclado para encriptar: \n");
        scanf("%[^\n]",frase);
        fflush(stdin);
        cifrarFrase(frase, matrizCifr);
        break;
    case 2:
        printf("Introduce un texto por teclado para desencriptar: \n");
        scanf("%[^\n]",fraseCifrada);
        fflush(stdin);
        descifrarFrase(fraseCifrada, matrizCifr, filaCifrado, columnaCifrado);
        break;
    case 3:

        fichero = fopen("encriptar.txt", "r");
        if(NULL == fichero){
            printf("No existe el fichero!\n");
        }

        while(!feof(fichero)){
            frase[contador] = fgetc(fichero);
            printf("%c", frase[contador]);
            contador++;
        }

        fclose(fichero);

        printf("\nFrase encriptada: ");
        cifrarFrase(frase, matrizCifr);
        break;
    case 4:
        break;
    }


    return 0;
}

void cifrarFrase(char frase[80], char matrizCifr[7][7]){
    int i;
    int fil;
    int col;
    int contador = 0;
    char fraseResultante[999] = "";

    for(i = 0; i < strlen(frase); i++){
        for(fil = 1; fil < 7; fil++){
            for(col = 1; col < 7; col++){
                if(frase[i] == matrizCifr[fil][col]){
                   fraseResultante[contador] = matrizCifr[fil][0];
                   contador++;
                   fraseResultante[contador] = matrizCifr[0][col];
                   contador++;
                }
            }
        }
    }
    printf("%s\n", fraseResultante);
}

void descifrarFrase(char fraseCifrada[160], char matrizCifr[7][7], char filaCifrado [7], char columnaCifrado [7]){
    int i;
    int j;
    int filAux;
    int colAux;
    int contador = 0;
    char fraseResultante[999] = "";
    int turno = 0;
    bool completado = false;

    for(i = 0; i < strlen(fraseCifrada); i++){
        if(turno == 0){
            for(j = 1; j < 7; j++){
                if(fraseCifrada[i] == filaCifrado[j]){
                    turno = 1;
                    filAux = j;
                }
            }
        } else if (turno == 1){
            for(j = 1; j < 7; j++){
                if(fraseCifrada[i] == columnaCifrado[j]){
                    turno = 0;
                    colAux = j;
                    completado = true;
                }
            }
        }
        if(completado){
            fraseResultante[contador] = matrizCifr[filAux][colAux];
            contador++;
            completado = false;
        }
    }
    printf("%s\n", fraseResultante);
}
