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
int main()
{
    displayRegions(100018);
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


    return 0;
}
