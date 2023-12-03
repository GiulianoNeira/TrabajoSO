#include <iostream>
#include "/usr/include/opencv4/opencv2/opencv.hpp"
#include <thread>
#include <vector>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

// Función para convertir una sección de la imagen a escala de grises
void conversion_a_gris(const Mat& input, Mat& output, int startRow, int endRow) {
    for (int r = startRow; r < endRow; ++r) {
        for (int c = 0; c < input.cols; ++c) {
            Vec3b pixel = input.at<Vec3b>(r, c);
            int grises = static_cast<int>(0.21 * pixel[2] + 0.72 * pixel[1] + 0.07 * pixel[0]);
            output.at<uchar>(r, c) = static_cast<uchar>(grises);
        }
    }
}

int main() {
	string nombreOriginal, nombreFinal;
	int numThreads;

	cout << "Ingrese el nombre de la imagen a color a procesar: ";
	cin >> nombreOriginal;

	cout << "Nombre deseado para la nueva imagen en escala de grises: ";
	cin >> nombreFinal;

	 cout << "Ingrese la cantidad de hilos a utilizar: ";
	cin >> numThreads;

	// Cargar la imagen original
	Mat original = imread(nombreOriginal, IMREAD_COLOR);

	// Verificar si la imagen se cargó correctamente
	if (original.empty()) {
        	cout << "No se pudo abrir la imagen. Asegúrese de que el archivo existe en el directorio." << endl;
        	return -1;
		}

	// Crear una nueva imagen en escala de grises
	Mat imagenGris(original.rows, original.cols, CV_8UC1);

	// Dividir la imagen entre los hilos
	int rowsPerThread = original.rows / numThreads;
	int startRow = 0;
	int endRow = rowsPerThread;

	// Definir el número de hilos a utilizar
	vector<thread> threads;

	// Medir el tiempo de conversión paralela
	high_resolution_clock::time_point start = high_resolution_clock::now();

	// Crear los hilos y ejecutar la conversión a escala de grises
	for (int i = 0; i < numThreads - 1; ++i) 
	{
        	threads.emplace_back(conversion_a_gris, std::ref(original), std::ref(imagenGris), startRow, endRow);
        	startRow = endRow;
        	endRow += rowsPerThread;
	}

	// Último hilo para procesar las filas restantes
	threads.emplace_back(conversion_a_gris, std::ref(original), std::ref(imagenGris), startRow, original.rows);

	// Esperar a que todos los hilos finalicen su ejecución
	for (auto& thread : threads) {
        	thread.join();
	}

	// Medir el tiempo transcurrido
	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double, std::milli> tiempo_transcurrido = end - start;
	cout << "Imagen creada con exito.\n "; 
	cout << "Tiempo de conversión paralela a escala de grises: " << tiempo_transcurrido.count() / 1000.0 << " segundos" << endl;

	// Guardar la imagen en escala de grises
	imwrite(nombreFinal, imagenGris);

	return 0;
}
