//*************************************************************************
// CPSC2620 Fall 2020 Prof: Zhang
// Assignment #1
// File: dictionary.cc
// Purpose: To simulate entering and deleting words into a "dictionary".
//          Uses a dynamic array
// Written by: Maruf Tonmoy
// Date: Sep. 17, 2020
//*************************************************************************

#include <iostream>
#include <string>
#include <utility>
using namespace std;

string* myAdd(string*, int&, string);
string* myDelete(string *, int&, string);
void myUpdate(string *, int, string, string);
void mySearch(const string*, int, string);
void myList(const string*, int);
bool linearSearch(const string*, int, string, int&);
void myExit();

int main()
{
    string* dictionary = nullptr; // This is the dynamic array
    string aword, newWord; // user input
    int numElements = 0;
    string cmd;
    do
    {
        cout << ">>> ";
        cin >> cmd;
        if(cmd == "EXIT")
            myExit();
        else if(cmd == "LIST")
            myList(dictionary,numElements);
        else
        {
            cin >> aword;
            if(cmd == "ADD")
                dictionary = myAdd(dictionary,numElements,aword);
            else if(cmd == "DELETE")
                dictionary = myDelete(dictionary,numElements,aword);
            else if(cmd == "SEARCH")
                mySearch(dictionary,numElements,aword);
            else if(cmd == "UPDATE")
            {
                cin >> newWord;
                myUpdate(dictionary, numElements,aword, newWord);
            }
        }
    }
    while(cmd != "EXIT");
    delete [] dictionary;
    dictionary = nullptr;
    return 0;
}
//*********************************************************************
// Function: myUpdate
// Purpose: To update a word in the dictionary.  If word does not exist
//          word is left alone.
// ********************************************************************
void myUpdate(string* A, int count, string oldWrd, string newWrd)
{
    int searches = 0;
    linearSearch(A,count,oldWrd,searches);
    if(searches < count)
    {
        A[searches] = newWrd;
        cout << oldWrd << " is replaced by " << newWrd << endl;
    }
    else
        cout << oldWrd << " is not found" << endl;
}

//*********************************************************************
// Function: myAdd
// Purpose: To add a word to the dictionary.  If the word already exists,
//          nothing is done. If the word does not exist in the dictionary,
//          it is added and the number of words is incremented by one.
// ********************************************************************
string* myAdd(string* A, int& count, string s)
{
    int searches = 0; // Don't really need "searches" but linearSearch requires it
    if(linearSearch(A,count,s,searches))
    {
        cout << s << " is already added." << endl;
        return A;
    }
    string* temp = new string[count+1];
    for(int i=0; i<count; i++)
    {
        *(temp + i) = *(A + i); // temp[i] = A[i]
    }
    temp[count++] = s;
    delete [] A;
    A = nullptr;
    cout << s << " is added" << endl;
    return temp;
}

//******************************************************************
// function to delete a word
// params: A - dynamic array from which to delete from
//         wordCount - current # of words in A
//         wrd - word to delete
//******************************************************************
string* myDelete(string* A, int& wordCount, string wrd)
{
    int searches = 0;
    if(!linearSearch(A,wordCount,wrd,searches))
    {
        cout << wrd << " is not found." << endl;
        return A;
    }

    // from where wrd was found move all the wrds to the right left on spot
    for(int i= searches+1; i<wordCount; i++)
        A[i-1] = A[i]; // or *(A+i-1) = *(A+i)
    // Now that wrd is deleted create a new array with wordCount-1.
    string* temp = new string[wordCount-1];
    // We now have 1 less wrd
    wordCount--;
    // copy all the words from A into temp
    for(int i=0; i<wordCount; i++)
        temp[i] = A[i];
    // deallocate the A array
    delete [] A;
    A = nullptr;
    return temp;
}

//******************************************************************
// function mySearch
// params: A is the dynamic array which to search in
//         size is the current size of the dynamic array
//         wrd is the word to search for
// This function calls linear search and if the word is found prints
// out the word and how many comparisons it took to find it.  Prints
// not found of wrd could not be found in A.
//******************************************************************
void mySearch(const string* A, int size, string wrd)
{
    int searches = 0;
    if(linearSearch(A,size,wrd,searches))
        cout << wrd << " is found. " << searches+1 << " comparisons." << endl;
    else
        cout << wrd << " is not found." << endl;
}

//*********************************************************************
// Function: linear_search
// Purpose: To perform linear search on string A of size n
// color is the colour to search and count refers to the number of
// comparisons the function performs
// ********************************************************************
bool linearSearch(const string* A, int n, string wrd, int& count)
{
    // notice that count is a reference parameter
    for(count = 0; count<n; count++)
    {
        if(wrd == A[count])
            return true;
    }
    return false;
}

//******************************************************************
// function to print this dynamic array.
//******************************************************************
void myList(const string* A, int size)
{
    for(int i=0; i<size; i++)
        cout << A[i] << endl;
}

//*********************************************************************
// Function: myExit()
// Purpose: print exit message
// ********************************************************************
void myExit()
{
    cout << "Bye bye" << endl;
}
