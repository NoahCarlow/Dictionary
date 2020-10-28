#include <iostream> // used for input and output
#include <string>   // used for c strings
#include <cstring>  // used for strcmp
#include <fstream>  // used for file read and write

void loadDictionary(bool, std::string);

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
        if (strcmp(argv[i], "-d") == 0) // '-d' command
        {
            dparam = argv[i+1];
            fileProvided = true; // confirms file was provided
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

    loadDictionary(fileProvided, dparam);

    return 0;
}

void loadDictionary(bool fileProvided, std::string dparam)
{
    std::string fileName = dparam;
    // overwrites file name if user did not enter dparam
    if (!fileProvided)
    {
        fileName = "dictionary.txt";
    }

    // open the file, resort to default file if file not found
    std::ifstream myFile;
    myFile.open(fileName);
    if (!myFile.is_open())
    {
        fileName = "dictionary.txt";
        myFile.open(fileName);
    }

    int numLines = 0;
    std::string line;

    // counts the number of lines in the dictionary file
    while (!myFile.eof())
    {
        getline(myFile, line);
        numLines++;
    }
    std::cout << fileName  << " has " << numLines << " words." << std::endl;
    myFile.close();

}