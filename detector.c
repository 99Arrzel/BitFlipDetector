#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>

// FUENTE https://stackoverflow.com/questions/9596945/how-to-get-appropriate-timestamp-in-c-for-logs
char *timestamp()
{
  time_t ltime;       /* Calendario */
  ltime = time(NULL); /* Fecha actual */
  return asctime(localtime(&ltime)); //Esto formatea la fecha y hace el return de char*
}
void escribirEnArchivo(size_t valorcambiado)
{
  FILE *fptr; //Creamos el puntero tipo FILE
  fptr = fopen("historial.txt", "a+"); //Esto nos permite hacer un append de el archivo
  fprintf(fptr, "Fecha: %s\n", timestamp()); //Establecemos la nueva vecha
  fprintf(fptr, "Se detecto un bitflip, nueva suma total = %zu\n", valorcambiado); //Establecemos la nueva suma de los valores dentro del array
  fclose(fptr); //Cerramos la conexion
}

int main()
{
  size_t bytes = 891289600; //Establecemos 850MB
  unsigned int tests = 0; //unsigned para siempre positivo, es un long int, empezamos desde 0 
  size_t total = 0; //El total

  printf("--- Contador de bitflips ---\n");
  printf("==================\n");
  printf("Reservando 850MB ...\n");
  unsigned char *buffer = (unsigned char *)calloc(bytes, 1); //Establecemos el tamaño con calloc
  mlock(buffer, bytes);     //reserva el buffer en memoria.S
  memset(buffer, 0, bytes); //seteamos todo a 0.

  printf("Iniciando : %s\n", timestamp());//Imprimimos que empezo....
  size_t tempTotal = 0;
  fflush(stdout);
  while (NULL == NULL)
  {
    //Loop para recorrer el array [buffer] y sumar todos los valores, si un bit es cambiado en el unsigned char, este cambiara
    tempTotal = total;
    for (size_t i = 0; i < bytes; ++i)
    {
      total += (int)buffer[i]; //Sumamos todos los valores dentro del array
    }
    if (tempTotal != total) //Establecemos que si el total es diferente del total anterior entonces hubo un cambio
    {
      escribirEnArchivo(total); //llamamos al void para imprimir el archivo
    }
    //escribirEnArchivo(1);
    // Nos aseguramos de que corra. XD
    printf("Corriendo test numero: %d\n", tests); 
    ++tests;
  }
}
