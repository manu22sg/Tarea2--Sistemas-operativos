# Tarea-2-Sistemas-Operativos: Escala a grises version secuencial
En la tarea 2 de Sistemas Operativos, se solicita aplicar un filtro a una imagen para transformarla a escala de grises, mediante el metodo de luminosidad( Luminosity Method)

En este README, se explicara que software se necesita y como se ejecuta el metodo secuencial, en el cual la matriz de pixeles se va a procesar secuencialmente, es decir, un pixel a la vez.

# Requisitos:
-Tener una imagen a color en el equipo.

-En Debian (y distribuciones basadas en), se debe instalar el paquete libopencv-dev. Para distribuciones basadas en Debian se realiza con el siguiente comando: "sudo apt install phyton3-opencv"

-Se debe instalar g++. En distribuciones basadas en Debian se puede con el siguiente comando: "sudo apt install g++"

Pasos a seguir para compilar el método:
Paso 1) Entrar a la carpeta en la cual se descargó el proyecto. Esto se puede hacer desde la terminal o de forma gráfica y luego abriendo la terminal desde dicha carpeta.

Paso 2) Ejecutar el siguiente comando: "make -f Makefile_secuencial". De está forma, se comprueba que el programa compilé y esté listo para su uso.

Paso 3) Ejecutar el comando: ./grayscale_seq [Nombre imagen] [nombre imagen a escala de grises]

# Ejemplo de la ejecucion
./grayscale_seq /home/manu/Escritorio/imagen1.jpg /home/manu/Escritorio/imagen2.jpg.

"/home/manu/Escritorio/imagen1.jpg" es la dirección dentro del computador en que está la imagen que hay que convertir a escala de grises.

"/home/manu/Escritorio/imagen2.jpg." sería la dirección dentro del equipo en la que se guardará la imagen convertida a escala de grises.

# ¿Que entrega como resultado?
Lo que entrega como resultado es la imagen a escala de grises y el tiempo de ejecución que demoro la imagén en pintar todos los pixeles a gris
# A TENER EN CUENTA
Dependiendo del tamaño de la imagen y del tamaño de la pantalla, es posible que no se muestre como deberia la imagen. Aún así, la imagen que se guarda se ve al mismo tamaño que la imagen original.
