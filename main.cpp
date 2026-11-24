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
    for(int i = 0; i < size; i++)
    {
        // String manipulation add current PID to /proc/
        std::string path = "/proc/";
        path.append(std::to_string(listPID[i]));

        // String manipulation add /comm to /proc/<pid>
        path.append("/comm");

        // Specify the file to be opened
        // Using ifstream/ofstream might be inefficient here,
        // should most likely use open syscall, but it is fine for now
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
    // Path to /proc/
    std::filesystem::path p = "/proc/";

    // Temp variable to store current directory
    std::string t;

    // List to hold all alphanumeric PIDs
    std::vector<int> listPID;

    // Iterate through the path and print directories
    // for(auto it : std::filesystem::directory_iterator(p))
    // this line wastes memory since it copies the directories instead of RO
    for(const auto& it : std::filesystem::directory_iterator(p))
    {
        t = it.path().filename();

        // Only add process to list if it contains alphanumeric PID
        if(t.find_first_of("0123456789") != std::string::npos)
        {
            // Push int representation of string for later manipulation
            listPID.push_back(std::stoi(t));

        }

    }

    // Call function to resolve and print PID names
    displayProcName(listPID, listPID.size());
}


void searchValue(int PID, uint64_t beg, uint64_t end)
{
    // Get file descriptor
    // This pretty much gives the same as displayRegions,
    // but not relying on std::ifstream/std::ostream
    std::string path = "/proc/";
    path.append(to_string(PID));

    path.append("/mem");

    int fd = open(path.c_str(),O_RDONLY);
    cout << "fd = " << fd << endl;

    // This is hard coded but it works
    off_t loc = beg;
    off_t offset = lseek(fd, loc, SEEK_SET);
    cout << "lseek returns: " << offset << endl;


    std::size_t count = end - beg; //std::size_t prevent overflow
    std::vector<std::byte> buf(count);
    ssize_t n = read(fd, buf.data(), count);


    int converted;
    for(int i = 0 ; i<count; i++)
    {
        std::memcpy(&converted, buf.data() + i, sizeof(converted));
        if(converted == 99)
            cout << static_cast<std::uintptr_t>(loc) + i << endl;

    }

    close(fd);


}
//7ffe8f094ae4

// or
//7FFCF9E2223C


void extractRegions(int PID, std::string region)
{
    std::string beg, end;
    beg = region.substr(0,12);
    end = region.substr(13,12);

    uint64_t b, e;

    b = std::stoul(beg,nullptr,16);
    e = std::stoul(end, nullptr, 16);

    cout << "Start range: "<< b  << endl;
    cout << "End range: " << e << endl;

    searchValue(PID, b, e);

}
void displayRegions(int PID)
{
    // TODO: same issue with ofstream/instream

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
            extractRegions(PID, l);
        }

    }
    // TODO check concurrency with open and close
    file.close();

}

void checkAddress()
{

}


int main()
{
    //displayRegions(100018);


    displayProcesses();

    int choicePID = -1;

    cout << endl << "Enter PID to view memory region:" << endl;
    cout << "Note only the region containing local variables on stack will be displayed." << endl;
    cin >> choicePID;

    displayRegions(choicePID);



    return 0;
}
