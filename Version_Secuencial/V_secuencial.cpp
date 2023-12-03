#include <iostream>
#include "/usr/include/opencv4/opencv2/opencv.hpp" 
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main() {
	string nombreOriginal, nombreFinal;
	cout << "Ingrese el nombre de la imagen a color a procesar: ";
	cin >> nombreOriginal;

	cout << "Nombre deseado para la nueva imagen en escala de grises: ";
	cin >> nombreFinal;

	// Cargar la imagen original
	Mat original = imread(nombreOriginal, IMREAD_COLOR);

	// Verificar si la imagen se cargo correctamente
	if (original.empty())
		 {
        	   cout << "No se pudo abrir la imagen. Asegúrate de que el archivo " << nombreOriginal << " existe en el directorio." << endl;
       		   return -1;
   		 }

	// Crear un objeto para medir el tiempo
	high_resolution_clock::time_point start = high_resolution_clock::now();

	// Crear una nueva imagen en escala de grises
	Mat imagenGris(original.rows, original.cols, CV_8UC1);

	// Convertir la imagen original a escala de grises utilizando el metodo de luminosidad
	for (int r = 0; r < original.rows; ++r)
	{
        	for (int c = 0; c < original.cols; ++c) 
		{
            		Vec3b pixel = original.at<Vec3b>(r, c);

            	// Calcular el valor de gris utilizando el metodo de luminosidad
            	int grises = static_cast<int>(0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0]);

            	// Asignar el valor de gris al pixel correspondiente en la nueva imagen en escala de grises
            	imagenGris.at<uchar>(r, c) = static_cast<uchar>(grises);
        	}
	}

	// Asegurarse de que la conversion se haya completado antes de medir el tiempo
	high_resolution_clock::time_point end = high_resolution_clock::now();

	// Calcular la duración de la conversion a escala de grises
	duration<double> tiempo_transcurrido = duration_cast<duration<double>>(end - start);
	cout << "Imagen creada con exito.\n";
	cout << "Tiempo de conversión a escala de grises: " << tiempo_transcurrido.count() << " segundos" << endl;

	// Guardar la nueva imagen en escala de grises
	imwrite(nombreFinal, imagenGris);
	return 0;
}
