#include <iostream>
#include <algorithm>

using namespace std;

// Функция для расширенного алгоритма Евклида
long long gcdExtended(long long a, long long b, long long *x, long long *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = gcdExtended(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main() {
    long long a, b, c;
    cin >> a >> b >> c;

    // Обрабатываем отрицательные a и b, запоминая знаки
    long long sign_a = (a < 0) ? -1 : 1;
    long long sign_b = (b < 0) ? -1 : 1;

    a = abs(a);
    b = abs(b);

    long long x, y;
    long long gcd_ab = gcdExtended(a, b, &x, &y);

    if (c % gcd_ab != 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    // Находим одно из решений
    x *= (c / gcd_ab);
    y *= (c / gcd_ab);

    // Учитываем знаки a и b при поиске общего решения
    long long a_div_gcd = a / gcd_ab;
    long long b_div_gcd = b / gcd_ab;

    // Находим такое t, чтобы x было наименьшим неотрицательным

    while (x < 0) {
        x += b_div_gcd;
        y -= a_div_gcd;
    }
    while (x >= b_div_gcd)
    {
      x -= b_div_gcd;
      y += a_div_gcd;
    }


    // Восстанавливаем знаки исходных a и b в решении

    cout << x << " " << y << endl;

    return 0;
}
