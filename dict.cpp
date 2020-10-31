#include <iostream>     // used for input and output
#include <string>       // used for c strings
#include <cstring>      // used for strcmp
#include <fstream>      // used for file read and write

void loadDictionary(bool, std::string);
void prefixSearch(std::string, bool, std::string, int);
void searchReplace(std::string, std::string, bool, std::string);
void spawnEditor(std::string, std::string);

int main(int argc, char* argv[])
{
    // hold the params for each command entered by user
    std::string dparam = "dictionary.txt";
    std::string pparam = "";
    int nparam = -1;
    std::string sparam = "";
    std::string rparam = "";
    std::string vparam = "";

    // checks if a file was provided
    bool fileProvided = false;

    // checks which commands to run after reading the command line
    bool pparamRun = false;
    bool sparamRun = false;
    bool rparamRun = false;
    bool vparamRun = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0) // '-d' command
        {
            dparam = argv[i+1];
            fileProvided = true; // confirms file was provided
            i++;
        }
        if (strcmp(argv[i], "-p") == 0) // '-p' command
        {
            pparam = argv[i+1];
            pparamRun = true;
            i++;
        }
        if (strcmp(argv[i], "-n") == 0) // '-n' command
        {
            nparam = std::stoi(argv[i+1]);
            i++;
        }
        if (strcmp(argv[i], "-s") == 0) // '-s' command
        {
            sparam = argv[i+1];
            sparamRun = true;
            i++;
        }
        if (strcmp(argv[i], "-r") == 0) // '-r' command
        {
            rparam = argv[i+1];
            rparamRun = true;
            i++;
        }
        if (strcmp(argv[i], "-v") == 0) // '-v' command
        {
            for (int y = i + 1; y < argc; y++)
            {
                vparam += argv[y];
            }
            vparamRun = true;
        }
    }

    // dparam always runs no matter what
    loadDictionary(fileProvided, dparam);

    if (pparamRun)
    {
        prefixSearch(pparam, fileProvided, dparam, nparam);
    }

    if (sparamRun && rparamRun)
    {
        searchReplace(sparam, rparam, fileProvided, dparam);
    }

    if (vparamRun)
    {
        std::cout << vparam << std::endl;
        spawnEditor(vparam, dparam);
    }

    return 0;
}

// this function gets the number of lines in a given dictionary from the user
void loadDictionary(bool fileProvided, std::string dparam)
{
    // overwrites file name if user did not enter dparam
    if (!fileProvided)
    {
        dparam = "dictionary.txt";
    }

    // open the file, resort to default file if file not found
    std::ifstream myFile;
    myFile.open(dparam);
    if (!myFile.is_open())
    {
        dparam = "dictionary.txt";
        myFile.open(dparam);
    }

    int numLines = 0;
    std::string line;

    // counts the number of lines in the dictionary file
    while (!myFile.eof())
    {
        getline(myFile, line);
        if (line != "") // only count non whitespace lines
        {
            numLines++;
        }
    }
    std::cout << std::endl;
    std::cout << dparam  << " has " << numLines << " words." << std::endl;
    std::cout << std::endl;
    myFile.close();
}

// this function will search for a word in the dictionary that begins with the prefix given
void prefixSearch(std::string pparam, bool fileProvided, std::string dparam, int nparam)
{
    int searchLength = pparam.length();

    // overwrites file name if user did not enter dparam
    if (!fileProvided)
    {
        dparam = "dictionary.txt";
    }

    // open the file, resort to default file if file not found
    std::ifstream myFile;
    myFile.open(dparam);
    if (!myFile.is_open())
    {
        dparam = "dictionary.txt";
        myFile.open(dparam);
    }

    std::string line;
    int control = 0;

    // counts the number of lines in the dictionary file
    while (!myFile.eof())
    {
        std::string tempString = "";
        getline(myFile, line);
        // takes the first searchLength amount of chars of each line and adds it to a string
        for (int i = 0; i < searchLength; i++)
        {
            tempString += line[i];
        }

        // if an nparam is given then it will only show that # of results
        // by default if no nparam is give it will show all results
        if (control == nparam && nparam != -1)
        {
            return;
        }
        else
        {
            control++;
        }

        // if it finds a match then it prints the line
        if (tempString.compare(pparam) == 0)
        {
            std::cout << line << std::endl;
            std::cout << std::endl;
        }
    }
    myFile.close();
}

// this function runs a search and replace across the entire file
void searchReplace(std::string sparam, std::string rparam, bool fileProvided, std::string dparam)
{
    int searchLength = sparam.length();
    int replaceLength = rparam.length();
    // overwrites file name if user did not enter dparam
    if (!fileProvided)
    {
        dparam = "dictionary.txt";
    }

    // open the file, resort to default file if file not found
    std::fstream myReadFile;
    myReadFile.open(dparam);
    if (!myReadFile.is_open())
    {
        dparam = "dictionary.txt";
        myReadFile.open(dparam);
    }

    std::string line;
    std::string file;

    // counts the number of lines in the dictionary file
    while (!myReadFile.eof())
    {
        std::string tempString = "";
        getline(myReadFile, line);
        
        // adopted from https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
        // this handles the search and replace of the two arguments sparam and rparam
        size_t start_pos = 0;
        while((start_pos = line.find(sparam, start_pos)) != std::string::npos) 
        {
            line.replace(start_pos, sparam.length(), rparam);
            start_pos += rparam.length(); // Handles case where 'to' is a substring of 'from'
        }
        file.append(line);
        file.append("\n");
    }
    myReadFile.close();

    std::ofstream myWriteFile;
    myWriteFile.open(dparam);
    myWriteFile << file;
    myWriteFile.close();
}

// this function spawns an editor and allows the user to make custom changes
void spawnEditor(std::string vparam, std::string dparam)
{
    std::string temp = vparam + " " + dparam;
    system(temp.c_str());
}
