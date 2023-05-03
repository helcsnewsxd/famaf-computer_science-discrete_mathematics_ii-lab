#!/bin/bash

gcc -Wall -Wextra -std=c99 -O3 main.c coloreo/APIParte2.c Implementacion_grupo_gonza_APIG.h/APIG23.c -o ej
for i in grafos_de_ejemplo/*
do
  echo $i
  time ./ej < $i
  echo "---------------"
done
rm ej