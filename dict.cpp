#include <iostream>
#include <string>
#include <cstring>

void dictFunction(bool, std::string);

int main(int argc, char* argv[])
{
    // hold the params for each command entered by user
    std::string dparam = "";
    std::string pparam = "";
    std::string nparam = "";
    std::string sparam = "";
    std::string rparam = "";
    std::string vparam = "";

    // checks if a file was provided
    bool fileProvided = false;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d")) // '-d' command
        {
            dparam = argv[i+1];
            fileProvided = true; // confirms file was provided
            dictFunction(fileProvided, dparam);
            i++;
        }
        if (!strcmp(argv[i], "-p")) // '-p' command
        {
            pparam = argv[i+1];
        }
        if (!strcmp(argv[i], "-n")) // '-n' command
        {
            nparam = argv[i+1];
        }
        if (!strcmp(argv[i], "-s")) // '-s' command
        {
            sparam = argv[i+1];
        }
        if (!strcmp(argv[i], "-r")) // '-r' command
        {
            rparam = argv[i+1];
        }
        if (!strcmp(argv[i], "-v")) // '-v' command
        {
            vparam = argv[i+1];
        }
    }
}

void dictFunction(bool fileProvided, std::string dparam)
{
    std::string fileName = "dictionary.txt";
    // overwrites file name if user entered dparam
    if (fileProvided)
    {
        fileName = dparam;
    }

    
}