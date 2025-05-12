#include <iostream>
#include <vector>
#include <chrono>
#include <random>

void multiplyMatricesBlocked(const std::vector<std::vector<double>>& A,
                            const std::vector<std::vector<double>>& B,
                            std::vector<std::vector<double>>& C, int n, int blockSize) {
    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int ii = i; ii < std::min(i + blockSize, n); ++ii) {
                    for (int kk = k; kk < std::min(k + blockSize, n); ++kk) {
                        double temp = A[ii][kk];
                        for (int jj = j; jj < std::min(j + blockSize, n); ++jj) {
                            C[ii][jj] += temp * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    const int n = 1024;
    const int blockSize = 32; // Размер блока
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<std::vector<double>> B(n, std::vector<double>(n));
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));

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
    multiplyMatricesBlocked(A, B, C, n, blockSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double c = 2 * std::pow(n, 3);
    double p = c / (elapsed.count() * 1e6);

    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    std::cout << "Performance: " << p << " MFlops" << std::endl;

    return 0;
}
