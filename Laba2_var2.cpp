#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <mkl.h> // Подключаем библиотеку Intel MKL

int main() {
    const int n = 1024;
    std::vector<double> A(n * n);
    std::vector<double> B(n * n);
    std::vector<double> C(n * n);

    // Заполнение матриц случайными значениями
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n * n; ++i) {
        A[i] = dis(gen);
        B[i] = dis(gen);
    }

    // Засекаем время начала выполнения
    auto start = std::chrono::high_resolution_clock::now();

    // Используем функцию cblas_dgemm для перемножения матриц
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A.data(), n, B.data(), n, 0.0, C.data(), n);

    // Засекаем время окончания выполнения
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем затраченное время
    std::chrono::duration<double> elapsed = end - start;

    // Оцениваем сложность алгоритма
    double c = 2 * std::pow(n, 3);

    // Оцениваем производительность в MFlops
    double p = c / (elapsed.count() * 1e6);

    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Performance: " << p << " MFlops" << std::endl;

    return 0;
}
