//
//  main.cpp
//  Voice Stories CDATA Tagger
//
//  Created by Tristan Lopus on 1/23/16.
//  Copyright © 2016 Tristan Lopus. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void replaceAll( string& source, const string& from, const string& to );

int main(int argc, const char * argv[]) {
    //cout << "Input name of file: ";
    string filename = argv[1];
    //cin >> filename;

    string newName = filename;
    replaceAll(newName, ".xml", "_CDATA_TAGGED.xml");
    int result = rename(filename.c_str(), newName.c_str());

    ifstream inFile(newName.data());
    ofstream outFile(filename.data());

    //cout << "infile:" << newName;
    //cout << "outfile:" << filename;

    string currentLine;
    int counter = 1;
    while (!inFile.eof()) {
        cout << "loop: " << counter;
        getline(inFile, currentLine);
        replaceAll(currentLine, "CDATA_BEGIN_REPLACE_WITH_TAG", "<![CDATA[");
        replaceAll(currentLine, "CDATA_END_REPLACE_WITH_TAG", "]]>");

        outFile << currentLine; //<< "&nbsp;";
        counter++;
    }

    // string currentLine;
    // while (!inFile.eof()) {
    //     getline(inFile, currentLine);
    //     replaceAll(currentLine, "CDATA_BEGIN_REPLACE_WITH_TAG", "<![CDATA[");
    //     replaceAll(currentLine, "CDATA_END_REPLACE_WITH_TAG", "]]>");
    //
    //     outFile << currentLine; // << "&nbsp;";
    // }

    cout << "Placed CDATA tags.";

    inFile.close();
    outFile.close();


    int deleteResult = remove(newName.c_str());

    return 0;
}

//from minastaros on StackOverflow
void replaceAll( string& source, const string& from, const string& to )
{
    string newString;
    newString.reserve( source.length() );  // avoids a few memory allocations

    string::size_type lastPos = 0;
    string::size_type findPos;

    while( string::npos != ( findPos = source.find( from, lastPos )))
    {
        newString.append( source, lastPos, findPos - lastPos );
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr( lastPos );

    source.swap( newString );
}
