# Tarea-2-Sistemas-Operativos: Escala a grises version paralela
En la tarea 2 de Sistemas Operativos, se solicita aplicar un filtro a una imagen para transformarla a escala de grises, mediante el metodo de luminosidad( Luminosity Method)

En este README, se explicara que software se necesita en el equipo, cual es el resultado que se obtiene y como se ejecuta el metodo Paralelo, en el cual la matriz de pixeles se va a procesar de forma paralela, es decir, se divide la imagen en varias partes y a cada hilo se le asigna cierta parte. Esto resulta en una mejora significativa en el rendimiento, especialmente en sistemas con multiples nucleos de CPU.
# Requisitos:
-Ejecutar desde un sistema basado en Debian.

-Tener una imagen a color en el equipo.

-En Debian (y distribuciones basadas en), se debe instalar el paquete libopencv-dev. Para distribuciones basadas en Debian se realiza con el siguiente comando: "sudo apt install phyton3-opencv".

-Se debe instalar g++. En distribuciones basadas en Debian se puede con el siguiente comando: "sudo apt install g++".

# Pasos a seguir para compilar el método:
Paso 1) Entrar a la carpeta en la cual se descargó el proyecto. Esto se puede hacer desde la terminal o de forma gráfica y luego abriendo la terminal desde dicha carpeta.

Paso 2) Ejecutar el siguiente comando: "make -f Makefile_paralelo". De está forma, se comprueba que el programa compilé y esté listo para su uso.

Paso 3) Ejecutar el comando: ./version_paralelo [Nombre imagen] [nombre imagen a escala de grises]

# Ejemplo de la ejecución
./version_paralelo /home/manu/Escritorio/imagen1.jpg /home/manu/Escritorio/imagen2.jpg 8.

"/home/manu/Escritorio/imagen1.jpg" es la dirección dentro del computador en que está la imagen que hay que convertir a escala de grises.

"/home/manu/Escritorio/imagen2.jpg." sería la dirección dentro del equipo en la que se guardará la imagen convertida a escala de grises.
8 seria la cantidad de hilos que se usaran para convertir la imagen a escala de grises.

# ¿Que entrega como resultado?
Lo que entrega como resultado es la imagen a escala de grises y el tiempo de ejecución que demoro el programa en pintar todos los pixeles a gris de manera paralela.
# A TENER EN CUENTA
Dependiendo del tamaño de la imagen y del tamaño de la pantalla, es posible que no se muestre como deberia la imagen. Aún así, la imagen que se guarda se ve al mismo tamaño que la imagen original.
