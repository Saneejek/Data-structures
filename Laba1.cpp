#include <iostream>

using namespace std;

// Функция для расширенного алгоритма Евклида
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    int x, y;
    int gcd_ab = gcdExtended(a, b, &x, &y);

    if (c % gcd_ab != 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    // Находим одно из решений
    x *= (c / gcd_ab);
    y *= (c / gcd_ab);

    // Находим общее решение:
    // x = x0 + (b/gcd) * t
    // y = y0 - (a/gcd) * t

    // Находим такое t, чтобы x было наименьшим неотрицательным
    int b_div_gcd = b / gcd_ab;
    int t = (x >= 0) ? (x / b_div_gcd) : ((x - b_div_gcd + 1) / b_div_gcd);

    x -= b_div_gcd * t;
    y += (a / gcd_ab) * t;

    // Если x все еще отрицательное, увеличиваем t на 1
    if (x < 0) {
        x += b_div_gcd;
        y -= (a / gcd_ab);
    }
    
    //Проверка, чтобы x был действительно минимальным неотрицательным
    if (x >= b_div_gcd) {
        x -= b_div_gcd;
        y += (a / gcd_ab);
    }

    cout << x << " " << y << endl;

    return 0;
}