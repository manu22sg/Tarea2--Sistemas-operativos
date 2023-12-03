#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h> //

void escalaGrisesThreads(cv::Mat &imagen, int startRow, int endRow) //Se define la funcion que convierte a escala de grises
{
#pragma omp parallel for                    // Divide las iteraciones del for entre los hilos
    for (int r = startRow; r < endRow; ++r) // Recorre la imagen por filas
    {
        for (int c = 0; c < imagen.cols - 1; ++c) // Recorre la imagen por columnas
        {
            cv::Vec3b &pixel = imagen.at<cv::Vec3b>(r, c);                            // Obtiene el pixel en la posicion (fila,olumnac)
            uchar escalaGrises = 0.21 * pixel[0] + 0.72 * pixel[1] + 0.07 * pixel[2]; // Calcula el valor de gris del pixel multiplicando los valores de cada canal por su respectivo valor
            pixel[0] = pixel[1] = pixel[2] = escalaGrises;                            // Asigna el valor de gris a cada canal del pixel
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4) // Se comprueba que esten los argumentos necesarios
    {
        std::cerr << "Uso correcto: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hebras>" << std::endl; // Argumentos para ejecutar el programa
        return 1;
    }

    cv::Mat imagen = cv::imread(argv[1], cv::IMREAD_COLOR); // Carga la imagen de entrada

    if (imagen.empty()) // Verifica que la imagen se haya cargado correctamente
    {
        std::cerr << "Error al cargar la imagen de entrada." << std::endl;
        return 1;
    }

    int numThreads = std::stoi(argv[3]);          // Obtiene el numero de hilos a utilizar
    int rowsPerThread = imagen.rows / numThreads; // Se calcula el numero de filas por hilo

    auto start_time = std::chrono::high_resolution_clock::now(); // Empieza la medicion de tiempo

#pragma omp parallel // Comienza la paralelizacion
    {
        int threadID = omp_get_thread_num();                                                      // Obtiene el id del hilo
        int startRow = threadID * rowsPerThread;                                                  // Calcula la fila inicial de cada hilo
        int endRow = (threadID == numThreads - 1) ? imagen.rows : (threadID + 1) * rowsPerThread; // Calcula la fila final de cada hilo
        endRow = std::min(endRow, imagen.rows);                                                   // Obtienen los li­mites de cada hilo, para que no se salga de la imagen
        escalaGrisesThreads(imagen, startRow, endRow);                                            // Llama a la funcion que convierte a escala de grises
    }

    auto end_time = std::chrono::high_resolution_clock::now();                                                // Termina la medicion de tiempo
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); // Calcula el tiempo de ejecucion

    double seconds = elapsed_time / 1e6; // Convierte de microsegundos a segundos
    std::cout.precision(9);              // Muestra 9 decimales
    std::cout << "Tiempo de ejecucion total: " << std::fixed << seconds << " segundos." << std::endl;

    cv::imshow("Imagen de salida", imagen); // Muestra la imagen resultante
    cv::waitKey(0);                         // Se espera a que se presione una tecla para cerrar la ventana

    cv::imwrite(argv[2], imagen); // Guarda la imagen resultante en la ruta especificada

    return 0;
}
