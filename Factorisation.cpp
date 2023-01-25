// Factorisation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <climits>
#include <cmath>
#include <numeric>
#include <thread>
#include <vector>

struct Divisors {
    unsigned long long first;
    unsigned long long second;
};

Divisors Ferma(const unsigned long long n);
Divisors Leman(const unsigned long long n);
void parrallel_work(const unsigned int begin, const unsigned int end);

int main()
{
    //srand(time(nullptr));
    //unsigned long long a = ULLONG_MAX * ((double) rand() / RAND_MAX);
    //Divisors div1, div2;
    //std::thread t1(parrallel_work(0, 100));
    std::thread t[12];
    //std::vector <std::thread> vec(12);
    for (unsigned int i = 0; i != 12; i++) {
        t[i] = std::thread(parrallel_work, (i+1) * 1000, (i + 2) * 1000);
        //vec[i] = std::thread(parrallel_work((i * 100), (i + 1) * 100), i + 1);
    }
    for (int i = 0; i != 12; i++) {
        t[i].join();
    }

}

Divisors Ferma(const unsigned long long n) {
    unsigned long long x, a, temp, y;
    Divisors res;
    res.first = 1;
    res.second = n;
    if (((unsigned long long) std::sqrt(n) * (unsigned long long) std::sqrt(n)) == n) {
        res.first = (unsigned long long) std::sqrt(n);
        res.second = res.first;
        return res;
    }
    else {
        a = (unsigned long long) std::sqrt(n) + 1;
        unsigned long long k = 1;
        while (k < (unsigned long long) n / 2 + 1) {
            //std::cout << k << '\n';
            x = a + k;
            temp = x * x - n;
            //std::cout << temp << ' ' << std::sqrt(temp) << '\n';
            if (((unsigned long long) std::sqrt(temp)) * ((unsigned long long) std::sqrt(temp)) == temp) {
                y = (unsigned long long) std::sqrt(x * x - n);
                res.first = x + y;
                res.second = n / res.first;
                return res;
            }
            k++;
        }
    }
    return res;
}

Divisors Leman(const unsigned long long n) {
    Divisors res = { 1, n };
    unsigned long long A, B, d_1;
    for (unsigned long long i = 2; i != std::pow(n, 1.0 / 3.0) + 1; i++) {
        if (n % i == 0) {
            res.first = i;
            res.second = n / i;
            return res;
        }
    }
    for (unsigned long long k = 1; k != std::pow(n, 1.0 / 3.0) + 1; k++) {
        for (unsigned long long d = 0; d != (std::pow(n, 1.0 / 6.0) / (4.0 * std::sqrt(k)) + 2); d++) {
            unsigned long long x = ((unsigned long long) std::sqrt(4.0 * k * n) + 1 + d) * ((unsigned long long) std::sqrt(4.0 * k * n) + 1 + d) - 4.0 * k * n;
            if (((unsigned long long) std::sqrt(x)) * ((unsigned long long) std::sqrt(x)) == x) {
                A = (unsigned long long) std::sqrt(4.0 * k * n) + d;
                B = (unsigned long long) std::sqrt(A * A - 4.0 * k * n);
                d_1 = std::gcd(A - B, n);
                if ((d_1 > 1) && (d_1 < n)) {
                    res.first = d_1;
                    res.second = n / d_1;
                    return res;
                }
            }
        }
    }
    return res;
}

void parrallel_work(const unsigned int begin, const unsigned int end)
{
    Divisors div = { 0, 0 };
    for (unsigned int i = begin; i != end; i++) {
        div = Leman(i);
        std::cout << i << ' ' << div.first << ' ' << div.second << std::endl;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
