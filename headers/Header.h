#pragma once
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

int q = 0;
int r = 0;
int multi_r = 0;
int sum = 0;

vector <int> secKey;    //������ ��� ���������������� ������������������
vector <int> opKey;
string mes = "";

int generateRanNum(int min, int max) {
    // ������� ��������� ��������� ����� � �������������� ������� ��������� �����
    std::random_device rd; // �������� ��������
    std::mt19937 generator(rd()); // Mersenne Twister ���������
    std::uniform_int_distribution<int> distribution(min, max); // ����������� �������������

    return distribution(generator);
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int generatePrime(int lowerBound, int upperBound) {
    int prime;
    do {
        prime = rand() % (upperBound - lowerBound + 1) + lowerBound; // ��������� ���������� ����� � ���������
    } while (!isPrime(prime)); // ���������� �� ��� ���, ���� �� ������� ������� �����

    return prime;
}

std::pair<int, int> generateQandR(int lowerBound, int upperBound) {
    int q = generatePrime(lowerBound, upperBound); // ���������� ������� ����� q
    int r = rand() % (q - 1) + 1; // ���������� ��������� ����� r (1 <= r < q)

    return { q, r }; // ���������� ���� (q, r)
}

void secret() {
    int beg = generateRanNum(10, 100);
    secKey.push_back(beg);
    secKey.push_back(beg + 5);
    sum += secKey[0] + secKey[1];
    for (int i = 2; i < 8; i++) {
        secKey.push_back(accumulate(secKey.begin(), secKey.end(), 0) + 5);
        sum += secKey[i];
    }
}

void open(int q, int r) {
    for (int i = 0; i < secKey.size(); i++) {
        opKey.push_back((secKey[i] * r) % q);
    }
}

string CharToBinary(unsigned char c) {
    std::string binary = "";
    for (int i = 7; i >= 0; --i) {
        // ���������, ���������� �� i-� ���
        binary += (c & (1 << i)) ? '1' : '0';
    }
    return binary;
}

string StringToBinary(string str) {
    string res = "";
    for (char c : str) {
        // ��������� ������ � �������� ������������� � ��������� � ����������
        res += CharToBinary(static_cast<unsigned char>(c)) + " "; // 8 ��� �� ������
    }
    return res;
}

int Evklid(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1; // ���������� ��� a � b
    int gcd = Evklid(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

void multy_number(int r, int q) {
    int x, y;
    int gcd = Evklid(r, q, x, y);

    // �������� x � �������������� �������� �� ������ q
    multi_r = (x % q + q) % q;
}

vector <int> encrypt(string bin) {
    vector <int> res;
    int sum = 0;
    int j = 0;
    for (int i = 0; i < bin.length(); i++) {
        if (bin[i] != ' ') {
            sum += opKey[j] * (bin[i] - '0');
            j++;
        } 
        else {
            res.push_back(sum);
            sum = 0;
            j = 0;
        }
    }
    return res;
}

string decrypt(vector <int> enc) {
    string res = "";
    int mod = 0;
    for (int i = enc.size() - 1; i >= 0; i--) {
        mod = enc[i] * multi_r % q;
        for (int j = secKey.size() - 1; j >= 0; j--) {
            if (secKey[j] <= mod) {
                res.insert(res.begin(), '1');
                mod -= secKey[j];
            }
            else {
                res.insert(res.begin(), '0');
            }
        }
    }
    return res;
}


string binaryToText(string binaryStr) {
    string text = "";
    for (size_t i = 0; i < binaryStr.size(); i += 8) {
        std::string byte = binaryStr.substr(i, 8);  // ����� 8 ��� (1 ����)
        char character = static_cast<char>(std::stoi(byte, nullptr, 2));  // ����������� � ������
        text += character;
    }
    return text;
}

void clearData() {
    secKey.clear();    // ������� ��������� ����
    opKey.clear();     // ������� �������� ����
    mes = "";          // ������� ���������
    sum = 0;           // ���������� �����
    multi_r = 0;       // ���������� �������� ��������� ����� r
}