#include <iostream>
#include <filesystem>
#include <fstream>
#include <algorithm>

#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
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

   // displayRegions(23217);
    char          buf1[10];
    char          buf2[10];
    pid_t         pid = 23217;    /* PID of remote process */
    ssize_t       nread;
    struct iovec  local[2];
    struct iovec  remote[1];

    local[0].iov_base = buf1;
    local[0].iov_len = 10;
    local[1].iov_base = buf2;
    local[1].iov_len = 10;
    remote[0].iov_base = (void *) 0x10000;
    remote[0].iov_len = 20;

    nread = process_vm_readv(pid, local, 2, remote, 1, 0);

    cout << buf2[1];
    return 0;
}
