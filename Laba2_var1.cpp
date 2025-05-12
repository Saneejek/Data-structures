#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void multiplyMatrices(const std::vector<std::vector<double>>& A,
                      const std::vector<std::vector<double>>& B,
                      std::vector<std::vector<double>>& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    const int n = 1024;
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<std::vector<double>> B(n, std::vector<double>(n));
    std::vector<std::vector<double>> C(n, std::vector<double>(n));

    // Заполнение матриц случайными значениями
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    multiplyMatrices(A, B, C, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double c = 2 * std::pow(n, 3);
    double p = c / (elapsed.count() * 1e6);

    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Performance: " << p << " MFlops" << std::endl;

    return 0;
}
