#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "linkedList.h"

using namespace std;

void createMsgs(ifstream &file, LinkedList* LL) {
    string line;
    string sender, content;
    long long timestamp;

    // Skip the initial "participants" array
    while (getline(file, line) && line.find("\"participants\":") == string::npos) {}

    // Skip the "\[" of the "participants" array
    getline(file, line);

    // Skip each participant entry until the end of the "participants" array
    while (getline(file, line) && line.find("]") == string::npos) {}

    // Skip the "," and the "\[" of the "messages" array
    getline(file, line);

    // Read the "messages" array
    while (getline(file, line) && line.find("]") == string::npos) {
        // Read "sender_name"
        getline(file, line);
        sender = line.substr(line.find(":") + 3, line.length() - 4);

        // Read "timestamp_ms"
        getline(file, line);
        timestamp = stoll(line.substr(line.find(":") + 2));

        // Read "content"
        getline(file, line);
        content = line.substr(line.find(":") + 3, line.length() - 4);

        // Skip other unnecessary fields until the end of the message
        while (getline(file, line) && line.find("}") == string::npos) {}

        LL->insert(sender, content, timestamp);
    }
}




int main(){
    cout << "Nick's Instagram Message Decoder" << endl;

    cout << "Type in the name of the file containing the messages (WITHOUT the extension (so no .txt))" << endl;
    cout << "> " << flush;
    string filePath;
    filePath += ".txt";
    getline(cin, filePath);

    ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
        std::cerr << "Error opening the file. Tell nick it says \" The file doesnt exist \"" << std::endl;
        cout << "Press Enter to exit ..." << endl;
        cin.get();
        return 1;
    }
    //my logic:
    /**
     * Since code needs to read in timestamps and sort by them, will generate a massive linked list of all the messages
     * then sort linked list
     * then write to file
    */

    string line;
    LinkedList* myLL = new LinkedList();
    cout << "Creating Data Structure ... " << endl;
    createMsgs(inputFile, myLL);
    cout << "Data Structure Created." << endl;
    //myLL->display();
    cout << "Sorting data by timestamp ..." << endl;
    Node* temp = myLL->getHead();
    myLL->sortByTimestamp();
    //myLL->display();
    cout << "Data sorted." << endl;
    cout << "Input name of output file (Only use letters and numbers please) (with no file extension)" << endl;
    cout << "> " << flush;
    getline(cin, filePath);
    cout << "Writing to file ..." << endl;
    filePath += ".txt";
    myLL->writeToFile(filePath);
    cout << "File Sucessfully Written" << endl;

    cout << "Thanks for using the converter! Have a nice day" << endl;

    

    return 0;
}