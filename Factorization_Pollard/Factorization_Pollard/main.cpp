//
//  main.cpp
//  NaiveAlgorithm
//
//  Created by MandyXue on 2017/10/26.
//  Copyright © 2017年 kth. All rights reserved.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;
unsigned long long g(unsigned long long x, unsigned long long n);
unsigned long long gcd (unsigned long long n1, unsigned long long n2);
vector<string> pollardGetFactors(unsigned long long number);
bool isPrime(unsigned long long n);

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    
    // ----------------------------------------------------------------------
    // ------------------- This part is to read from file -------------------
    vector<unsigned long long> numbers;
    ifstream inStream;
    inStream.open("/Users/mandyxue/Documents/Coding/AdvancedAlgorithm_Project/Factorization_Pollard/Factorization_Pollard/input.txt");
    string line;
    while (getline(inStream,line)) {
        cout << endl;
        if (line.length() <= 20) {
            //            numbers.push_back(stoull(line));
            unsigned long long number = stoull(line);
            vector<string> factors = pollardGetFactors(number);
            for (int i=0; i<factors.size(); i++) {
                cout << factors[i] << endl;
            }
        } else {
            cout << "fail" << endl;
        }
    }
    
    // -----------------------------------------------------------------------
    // -------------- This part is to read from cin, for Kattis --------------
    // need to take the first round out to avoid blank line at the beginning
//    string line;
//    vector <unsigned long long> myFactors;
//    getline(cin, line);
//    if (line.length() <= 20) {
//        unsigned long long number = stoull(line);
//        vector<string> factors = pollardGetFactors(number);
//        for (int i=0; i<factors.size(); i++) {
//            cout << factors[i] << endl;
//        }
//    } else {
//        cout << "fail" << endl;
//    }
//    while(getline(cin, line)){
//        cout << endl;
//        if (line.length() <= 20) {
//            unsigned long long number = stoull(line);
//            vector<string> factors = pollardGetFactors(number);
//            for (int i=0; i<factors.size(); i++) {
//                cout << factors[i] << endl;
//            }
//        } else {
//            cout << "fail" << endl;
//        }
//    }
    
    return 0;
}

vector<string> pollardGetFactors(unsigned long long number){
    vector<string> vFactors;
    unsigned long long x = 2;
    unsigned long long y = 2;
    unsigned long long d = 1;
    int index = 0;
    while (1) {
        x = g(x, number);
        y = g(g(y, number), number);  // y = x[2i]
        unsigned long long subtract;
        if (x == y) {  // when x is equal to y then we need to generate new random number for x to find the factor
            x = rand() % number;
            index ++;
            if (index > 10) {
                if (d != 1)
                    vFactors.push_back(to_string(d));
                else
                    vFactors.push_back(to_string(number));
                break;
            }
        }
        if (x > y) {
            subtract = x-y;
        } else {
            subtract = y-x;
        }
        d = gcd(subtract, number);
        if (d > 1) {
            // if d is a non-trivial factor, then push d into factor vector and stop
            if (isPrime(d) && number % d == 0) {
                vFactors.push_back(to_string(d));
                if (number/d != 1) {
                    vector<string> otherFactors = pollardGetFactors(number/d);
                    vFactors.insert(vFactors.end(), otherFactors.begin(), otherFactors.end());
                }
                break;
            }
        }
    }
    
    return vFactors;
}

unsigned long long g(unsigned long long x, unsigned long long n) {
    return (x*x+1) % n;
}

unsigned long long gcd (unsigned long long n1, unsigned long long n2) {
    unsigned long long remainder;
    while (n2 != 0) {
        remainder = n1 % n2;
        n1 = n2;
        n2 = remainder;
    }
    return n1;
}

bool isPrime(unsigned long long n) {
    for (unsigned long long i=2; i*i <= n; i++) {
        if (n%i == 0) {
            return false;
        }
    }
    return true;
}
