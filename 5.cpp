/*
 * Author: James Adams
 * Date: May 2, 2018
 * File: 5.cpp
 */

#include <iostream>
#include "pass.h"
#include <fstream>

using namespace std;

void findi(char a[], int n, int &i) {
    i = 0;
    for (int k = 0; k < n - 1; k++) {
        if (a[k] < a[k + 1])
            i = k;
    }
}

void findj(char a[], int n, int i, int &j) {
    j = i + 1;
    for (int k = i + 1; k < n; k++) {
        if (a[k] > a[i]) {
            if (a[k] < a[j]) j = k;
        }
    }
}

void switch_i_j(int i, int j, char a[]) {
    int num;
    num = a[i];
    a[i] = a[j];
    a[j] = num;
}

void reversetail(int n, int i, char a[]) {
    char b[25];
    int k;
    for (k = i + 1; k < n; k++)
        b[k] = a[n - k + (i + 1) - 1];
    for (k = i + 1; k < n; k++)
        a[k] = b[k];
}

long nfact(int n) {
    int k;
    long p = 1;
    for (k = 1; k <= n; k++)
        p = p * k;
    return p;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int z = atoi(argv[1]);

        int start = 0, finish = 0;
        start = (1 << z) - 1;
        finish = (start << (10 - z));
        ofstream out("permutation.txt");
        for (int i = start; i <= finish; i++) {
            string perm;
            int j = i;
            for (int k = 0; k < 10; k++) {
                if (j % 2 == 1)
                    perm += (k + 48);
                j /= 2;
            }
            if (perm.length() == z)
                out << perm << endl;
        }
        out.close();

        string a;
        ifstream in("permutation.txt");
        while (in >> a) {
            char aStuff[z + 1];
            for (int g = 0; g < z; g++)
                aStuff[g] = a[g];

            aStuff[z] = 0;
            if (pass(aStuff) == 0) {
                cout << "Correct password is: " << aStuff << endl;
                return 0;
            }
            int fac = nfact(z);
            int i, j, y, l;
            for (int x = 1; x < fac; x++) {
                findi(aStuff, z, i);
                findj(aStuff, z, i, j);
                switch_i_j(i, j, aStuff);
                reversetail(z, i, aStuff);
                if (pass(aStuff) == 0) {
                    cout << "Correct password is: " << aStuff << endl;
                    return 0;
                }
            }
        }
        cout << "Incorrect Password" << endl;
        return 0;
    }
    return -1;
}