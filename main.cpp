#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <regex>

int main() {
    std::cout << "Tail Number:" << std::endl;
    std::string input = "";
    std::cin >> input;

    std::string tailNumber = "";

    if (regex_match(input, std::regex("^N[1-9]((\\d{0,4})|(\\d{0,3}[A-HJ-NP-Z])|(\\d{0,2}[A-HJ-NP-Z]{2}))$"))) {
        tailNumber = input;
    } else {
        std::cout << "Tail Number did not meet the FAA naming format." << std::endl;
        return 1;
    }

    std::string fName = "C:/Users/Conor/Downloads/WPR19FA093.ppb";
    int numMentions = 0;
    std::string line;

    // tick
    unsigned long long n = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream istrm(fName);
    if(istrm.is_open()) {
        while(istrm.good()) {
            std::getline(istrm, line);
            if (line.find(tailNumber) != std::string::npos) {
                numMentions++;
            }

            // do algorithm here
        }

        istrm.close();
    }

    // tock
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(finish - start).count() << " seconds" << std::endl;
    std::cout << "Tail Number #" << tailNumber << " found " << numMentions << (numMentions == 1 ? " time." : " times.") << std::endl;

    return 0;
}

