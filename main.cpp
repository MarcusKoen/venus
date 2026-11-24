#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>// for open(2)
#include <unistd.h>// for read(2), lseek(2)
#include <vector>
#include <cstring>// for memcpy
using namespace std;
// TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE

void displayProcName(std::vector<int> listPID, int size)
{
    // TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE


    for(int i = 0; i < size; i++)
    {
        // String manipulation add PID to /proc/
        std::string path = "/proc/";
        path.append(std::to_string(listPID[i]));

        // String manipulation add /comm to /proc/<pid>
        path.append("/comm");

        // Specify the file to be opened
        std::ifstream file(path);
        std::string l;

        // Iterate through and print all lines of the comm file
        while(std::getline(file, l))
        {
            cout << "PID: " << listPID[i] << ", Name: " << l << endl;
        }

        file.close();
    }
}


void displayProcesses()
{
    // TODO BOUNDARY VALUE CHECKS OPENING ADN CLOSING FILES CHECK EXISTENCE

    // Path to /proc/
    std::filesystem::path p = "/proc/";

    // Temp variable to store current directory
    std::string t;

    std::vector<int> listPID;

    // Iterate through the path and print directories
    for(auto it : std::filesystem::directory_iterator(p))
    {
        t = it.path().filename();

        // Only print the process if it contains alphanumerical PID
        if(t.find_first_of("0123456789") != std::string::npos)
        {
            listPID.push_back(std::stoi(t));

        }

    }

    displayProcName(listPID, listPID.size());
}



void displayRegions(int PID)
{
    //cat /proc/23217/maps
    // Need to do similar iteration

    // String manipulation add PID to /proc/
    std::string path = "/proc/";
    path.append(std::to_string(PID));

    // String manipulation add /comm to /proc/<pid>
    path.append("/maps");

    // Specify the file to be opened
    std::ifstream file(path);
    std::string l;

    // Iterate through and print all lines of the comm file
    while(std::getline(file, l))
    {
        // I mean this is cool, but this algorithm will only work for local variables, not constants
        // in other regions. CRITICAL TODO
        if(l.find("[stack]") != std::string::npos)
        {
            cout << l << endl;
        }

    }

    file.close();

}

void checkAddress()
{

}

void searchValue(int PID)
{
    // Get file descriptor
    // This pretty much gives the same as displayRegions,
    // but not relying on std::ifstream/std::ostream
    std::string path = "/proc/100018/mem";

    int fd = open(path.c_str(),O_RDONLY);
    cout << "fd = " << fd << endl;

    // This is hard coded but it works
    off_t loc = 140726292865024;
    off_t offset = lseek(fd, loc, SEEK_SET);
    cout << "lseek returns: " << offset << endl;


    std::size_t count = 135168; //std::size_t prevent overflow
    std::vector<std::byte> buf(count);
    ssize_t n = read(fd, buf.data(), count);


    int converted;
    for(int i = 0 ; i<135168; i++)
    {
        std::memcpy(&converted, buf.data() + i, sizeof(converted));
        if(converted == 22)
            cout << static_cast<std::uintptr_t>(loc) + i << endl;

    }

    close(fd);


}
int main()
{
    //displayRegions(100018);


    displayProcesses();

    return 0;
}
