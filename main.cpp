#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
// TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE
void displayProcs()
{
    // TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE


    // Path to /proc/
    std::filesystem::path p = "/proc";

    // Recursively iterate through the path and print directories
    for(auto it : std::filesystem::recursive_directory_iterator(p))
    {
        cout << it.path().filename();
    }



}

void displayProcName(int PID)
{
    // TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE

    // String manipulation add PID to /proc/
    std::string path = "/proc/";
    path.append(std::to_string(PID));

    // String manipulation add /comm to /proc/<pid>
    path.append("/comm");

    // Specify the file to be opened
    std::ifstream file(path);
    std::string l;

    // Iterate through and print all lines of the comm file
    while(std::getline(file, l))
    {
        cout << l ;
    }

    file.close();

}

int main()
{

    //displayProcs();

    displayProcName(342309);
    return 0;
}
