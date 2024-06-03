#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>
// #include <regex>
#include <string>

using namespace std;
using namespace cv;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Русский язык" << endl;
	// cout << "Укажите путь к файлу изображения: ";
	// string path;
	// getline(cin, path);
	
	// кол-во всех изображений
	const int images_cnt = 12;

	// папка для сохранения обработанных изображений
	string output_images_path = "D:\\Cpp_projects\\Project1\\processed_images\\";

	// массив с путями для всех необработанных изображений
	string input_images_path[images_cnt] = {
		"D:\\Cpp_projects\\Project1\\images\\1.jpg", // gaus_blur ws=5
		"D:\\Cpp_projects\\Project1\\images\\2.bmp", // median blur ws=3
		"D:\\Cpp_projects\\Project1\\images\\3.jpg", // gaus_blur ws=3; ws=5
		"D:\\Cpp_projects\\Project1\\images\\4.jpg", // gaus_blur ws=13; ws=15;
		"D:\\Cpp_projects\\Project1\\images\\5.jpg", // gaus_blur ws=7
		"D:\\Cpp_projects\\Project1\\images\\6.png", // median_blur ws=13
		"D:\\Cpp_projects\\Project1\\images\\7.png", // median_blur ws=3
		"D:\\Cpp_projects\\Project1\\images\\8.jpg", // gaus_blur ws=5;
		"D:\\Cpp_projects\\Project1\\images\\9.jpg", // gaus_blur ws=13; ws=15
		"D:\\Cpp_projects\\Project1\\images\\10.jpg", // gaus_blur ws=9
		"D:\\Cpp_projects\\Project1\\images\\11.jpg", // gaus_blur ws=13; ws=15
		"D:\\Cpp_projects\\Project1\\images\\12.jpg", // gaus_blur ws=9
	};

	// лучший фильтр для всех изображений установлены оп. путем
	string image_best_filters[images_cnt] = {
		"gaus",
		"median",
		"gaus",
		"gaus",
		"gaus",
		"median",
		"median",
		"gaus",
		"gaus",
		"gaus",
		"gaus",
		"gaus",
	};

	// лучшие размеры окон размытия для фильтров установлено оп. путем
	int filter_sizes[images_cnt] = { 5, 3, 3, 13, 7, 13, 3, 5, 13, 9, 13, 9, };

	// const regex im_name_rx("\\*.jpg");

	// переменные для хранения изображений
	Mat image;
	// Mat blur_procc_image; неподходит для обработки
	Mat median_blur_procc_image;
	Mat gaus_blur_procc_image;

	for (int i = 0; i < 12; i++) {
		// извлекаем текущий путь изображения из общего массива
		string current_image_path = input_images_path[i];
		// считываем его
		image = imread(current_image_path, IMREAD_COLOR);
		// если не получилось прерываем исполнение программы
		if (image.empty()) {
			cout << "Не получилось открыть файл " << current_image_path << endl;
			return -1;
		}

		// извлекаем размер окна размытия из общего массива
		int ws = filter_sizes[i];

		// проверяем тип используемого фильтра
		if (image_best_filters[i] == "gaus") {
			// обработка и сохранение
			GaussianBlur(image, gaus_blur_procc_image, Size(ws, ws), 0);
			string gaus_blur_image_name = output_images_path + to_string(i + 1) + "_ws" + to_string(ws) + "_gaus_blur.jpg";
			bool check_gaus_blur = imwrite(gaus_blur_image_name, gaus_blur_procc_image);
			// проверка на успешность
			if (check_gaus_blur == false) {
				cout << "Не получилось сохранить изображение " << gaus_blur_image_name << endl;
				return -1;
			}
		}
		else {
			// обработка и сохранение
			medianBlur(image, median_blur_procc_image, ws);
			string median_blur_image_name = output_images_path + to_string(i + 1) + "_ws" + to_string(ws) + "_median_blur.jpg";
			bool check_median_blur = imwrite(median_blur_image_name, median_blur_procc_image);
			// проверка на успешность
			if (check_median_blur == false) {
				cout << "Не получилось сохранить изображение " << median_blur_image_name << endl;
				return -1;
			}
		}


		
		
		
		// старый кусок кода отвечающий за применение и медианного и гауссовского фильтров
		// с постепенно повышаемым шагом размытия
		// нужен для выявления лучшего фильтра и окна размытия
		/* for (int ws = 1; ws <= 13; ws += 2) {
			medianBlur(image, median_blur_procc_image, ws);
			// blur(image, blur_procc_image, Size(7, 7));
			GaussianBlur(image, gaus_blur_procc_image, Size(ws, ws), 0, 0);

			// string blur_image_name = output_images_path + to_string(i + 1) + "_blur.jpg";
			string median_blur_image_name = output_images_path + to_string(i + 1) + "_ws" + to_string(ws) + "_median_blur.jpg";
			string gaus_blur_image_name = output_images_path + to_string(i + 1) + "_ws" + to_string(ws) + "_gaus_blur.jpg";

			// bool check_blur = imwrite(blur_image_name, blur_procc_image);
			bool check_gaus_blur = imwrite(gaus_blur_image_name, gaus_blur_procc_image);
			bool check_median_blur = imwrite(median_blur_image_name, median_blur_procc_image);

			// if (check_blur == false) {
			//	cout << "Не получилось сохранить изображение " << blur_image_name << endl;
			//	return -1;
			//}
			if (check_gaus_blur == false) {
				cout << "Не получилось сохранить изображение " << gaus_blur_image_name << endl;
				return -1;
			}
			if (check_median_blur == false) {
				cout << "Не получилось сохранить изображение " << median_blur_image_name << endl;
				return -1;
			}
		}*/
	}

	return 0;

}