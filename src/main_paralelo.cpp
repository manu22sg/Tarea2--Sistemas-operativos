#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <chrono>

// Funcion para convertir la imagen a escala de grises
void escalaGrises(cv::Mat &imagen, int startRow, int endRow)
{
    for (int r = startRow; r < endRow; ++r) // Recorre las filas de la imagen
    {
        for (int c = 0; c < imagen.cols; ++c) // Recorre las columnas de la imagen
        {
            cv::Vec3b &pixel = imagen.at<cv::Vec3b>(r, c);                               // Obtiene el pixel en la posicion (r, c)
            uchar valorGrises = 0.21 * pixel[0] + 0.72 * pixel[1] + 0.07 * pixel[2]; // Calcula el valor de escala de grises del pixel
            pixel[0] = pixel[1] = pixel[2] = valorGrises;                            // Asigna el valor de escala de grises a cada canal de color del pixel
        }
    }
}

int main(int argc, char *argv[])
{

    if (argc != 4 ) // Verifica si se proporcionan todos los parametros necesarios
    {
        std::cerr << "Uso correcto: " << argv[0] << " <imagen_entrada> <imagen_salida> <num_hebras>" << std::endl; //  Muestra argumentos necesarios para la ejecucion correcta del programa
        return 1;
    }

    cv::Mat imagen = cv::imread(argv[1], cv::IMREAD_COLOR); // Lee la imagen de entrada en color

    if (imagen.empty()) // Verifica si la imagen se cargo correctamente
    {
        std::cerr << "Error al cargar la imagen de entrada." << std::endl; // Mensaje de error
        return 1;
    }

    int numThreads = std::stoi(argv[3]);         // Numero de hilos ingresados por el usuario
    int rowsPerThread = imagen.rows / numThreads; // Numero de filas que procesara cada hilo para dividir la imagen

    std::vector<std::thread> threads; // Vector de hilos

    // Inicia mediciÃ³n de tiempo
    auto start_time = std::chrono::high_resolution_clock::now(); // Mide el tiempo de ejecucion del procesamiento de la imagen

    // Divide la imagen entre los hilos ingresados
    for (int i = 0; i < numThreads; ++i) // Bucle que se ejecuta segun el numero de hilos ingresados
    {
        int startRow = i * rowsPerThread;                                          // Calcula la fila inicial de la imagen que procesara el hilo
        int endRow = (i == numThreads - 1) ? imagen.rows : (i + 1) * rowsPerThread; // Calcula la fila final de la imagen que procesara el hilo

        threads.emplace_back(escalaGrises, std::ref(imagen), startRow, endRow); // Agrega un hilo al vector de hilos y asigna la funcion convertToGrayscaleThreaded con sus parametros
    }

    // Espera a que todos los hilos terminen
    for (auto &thread : threads) // Bucle que se ejecuta segun el numero de hilos ingresados
    {
        thread.join(); //  Espera a que el hilo termine
    }

    // Detener la medicion de tiempo
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); // Calcula el tiempo de ejecucion en microsegundos
    double seconds = elapsed_time / 1e6;                                                                      // Se convierte el tiempo de ejecucion a segundos
    std::cout.precision(9);                                                                                   // Establece la precision de la salida, para que muestre decimales
    std::cout << "Tiempo de ejecucion total: " << std::fixed << seconds << " segundos." << std::endl;         // Se muestra la salida en segundos

    cv::imshow("Imagen convertida a escala de grises", imagen); // Muestra la imagen
    cv::waitKey(0);                                            // Espera a que se toque una tecla para cerrar la imagen


    cv::imwrite(argv[2], imagen); // Guarda la imagen resultante

    return 0;
}

