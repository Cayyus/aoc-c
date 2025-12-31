#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// g++ -std=c++23 aoc.cpp -o aoc

// --- Day 2: Gift Shop ----

std::vector<std::string> splitString(const std::string& string, char deLimiter) {
    std::vector<std::string> ranges;
    std::stringstream ss(string);
    std::string range;

    while (std::getline(ss, range, deLimiter)) {
        ranges.push_back(range); // while ss exists, split, put into range and push into ranges
    }

    return ranges;
} 

bool hasRepeatedSequence(long long number) {
    std::string num_str = std::to_string(number);
    int L = num_str.length();
    
    // check if number is even, because repeated two halves would be symmetrical
    if (!(L % 2 == 0)) {
        return false; // not symmetrical, no repeats
    }

    std::string first_half = num_str.substr(0, L / 2);
    std::string second_half = num_str.substr(L / 2, L / 2);

    return first_half == second_half;
}

int main() {
    std::ifstream inputFile("aoc.txt");

    if (!inputFile.is_open()) {
        std::cout << "Error opening input file" << std::endl;
        return 1;
    }

    long long invalidSum = 0;   

    std::string line; 
    while (std::getline(inputFile, line)) {
        // store all ranges
        std::vector<std::string> ranges = splitString(line, ',');
        for (const auto& range: ranges) {
            std::vector<std::string> boundNums = splitString(range, '-'); // split hypens to get start and end

            long long start = std::stoll(boundNums[0]);
            long long end = std::stoll(boundNums[1]);

            for (long long i = start; i <= end; i++) {
                bool repeated = hasRepeatedSequence(i);
                if (repeated) {
                    invalidSum += i;
                }
            }
        }
    }

    std::cout << "Sum of invalid IDs is " << invalidSum << std::endl;

    inputFile.close();

    return 0;
}
