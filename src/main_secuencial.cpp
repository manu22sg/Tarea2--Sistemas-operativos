#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

// Funcion para convertir la imagen a escala de grises
void escalaGrises(cv::Mat &imagen) // Se pasa por referencia para que se modifique la imagen original
{
    for (int r = 0; r < imagen.rows; ++r) // Recorre las filas
    {
        for (int c = 0; c < imagen.cols; ++c) // Recorre las columnas
        {
            cv::Vec3b &pixel = imagen.at<cv::Vec3b>(r, c);                               // Se obtiene el pixel en la posicion (fila,columna)
            uchar grayscaleValue = 0.21 * pixel[0] + 0.72 * pixel[1] + 0.07 * pixel[2];  // Se calcula el valor de gris
            pixel[0] = pixel[1] = pixel[2] = grayscaleValue;                             // Se asigna el valor de gris a cada canal
        }
    }
}

int main(int argc, char *argv[])
{
    // Se usa en caso de que no se ingresen los argumentos necesarios
    if (argc != 3)
    {
        std::cerr << "Uso correcto: " << argv[0] << " <imagen_entrada> <imagen_salida>" << std::endl; // Se muestra por pantalla los argumentos requeridos
        return 1;
    }


    cv::Mat imagen = cv::imread(argv[1], cv::IMREAD_COLOR); // Se lee la imagen a color

    if (imagen.empty()) // Si la imagen esta vacia que muestre un mensaje
    {
        std::cerr << "Error al cargar la imagen de entrada." << std::endl;
        return 1;
    }

    // Iniciar medicion de tiempo
    auto start_time = std::chrono::high_resolution_clock::now();

    // Convertir imagen a la escala de grises
    escalaGrises(imagen);

    
    auto end_time = std::chrono::high_resolution_clock::now(); // Detener la medicion del tiempo
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    double seconds = elapsed_time / 1e6; // Se convierten los microsegundos a segundos
    std::cout.precision(9);              // Muestra 9 decimales

    
    std::cout << "Tiempo de ejecucion: " << std::fixed << seconds << " segundos." << std::endl; // Muestra el tiempo que demora en convertirse la imagen a escala de grises

   
    cv::imshow("Imagen de salida", imagen); // Muestra la imagen convertida a escala de grises
    cv::waitKey(0);                         // Se Espera hasta que se presione una tecla para cerrar la ventana con la imagen resultante

   
    cv::imwrite(argv[2], imagen); // Guardar la imagen resultante

    std::cout << "Conversion a escala de grises completada." << std::endl;

    return 0;
}
