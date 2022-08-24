#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <regex>

bool does_file_exist(const std::string &fileName)
{
    std::ifstream infile(fileName.c_str());
    return infile.good();
}

void report_error_user(const std::string &message)
{
    std::cout << "Encountered an error: " << message << std::endl;
}

int main()
{
    std::string input = "";
    std::cout << "Filename: " << std::endl;
    std::cin >> input;

    // if we have quotation marks, let's strip them first
    size_t pos = 0;
    while ((pos = input.find('"', pos)) != std::string::npos)
        input = input.erase(pos, 1);

    if (!does_file_exist(input.c_str()))
    {
        report_error_user("Filename does not point to a valid file.");
        return 1;
    }

    std::string fName = input;

    std::cout << "Tail Number:" << std::endl;
    std::cin >> input;

    std::string tailNumber = "";

    if (regex_match(input, std::regex("^N[1-9]((\\d{0,4})|(\\d{0,3}[A-HJ-NP-Z])|(\\d{0,2}[A-HJ-NP-Z]{2}))$")))
    {
        tailNumber = input;
    }
    else
    {
        report_error_user("Tail Number did not meet the FAA naming format.");
        return 1;
    }

    // std::string fName = "C:/Users/Conor/Downloads/WPR19FA093.ppb";
    int numMentions = 0;
    std::string line;

    // tick
    unsigned long long n = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream istrm(fName);
    if (istrm.is_open())
    {
        while (istrm.good())
        {
            std::getline(istrm, line);
            if (line.find(tailNumber) != std::string::npos)
            {
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
