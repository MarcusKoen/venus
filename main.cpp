#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;

int main()
{

    // Path to /proc/
    //std::filesystem::path p = "/proc/1/";
    std::filesystem::path p = "/proc/1/cmdline";
/*
    // Recursively iterate through the path and print directories
    for(auto it : std::filesystem::recursive_directory_iterator(p))
    {
        cout << it.path().filename();
    }

*/

    std::ifstream file("/proc/3/cmdline");
    std::string l;
    while(std::getline(file, l))
    {
        cout << l ;
    }

    file.close();

    return 0;
}
