
/*
Name: Yujesh Joshi, NSHE: 2001780531, Section 1001/1003, Assignment 1
Description: Code will do a coctail sort with linked lists
Input: txt file
Output sorted txt file
*/
#include "LL.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    string fileName;
    ifstream inFile;
    bool swap = true;
    LL<int> sortLL;
    int number;

    cout << endl; //for cg
    cout << "Enter filename: ";
    cin >> fileName; //input file 
    cout << endl;

    inFile.open(fileName);
    
    while (!inFile.is_open())
    { //loop to open file
        cout << "Enter filename: ";
        cin >> fileName;
        cout << endl;
        inFile.open(fileName);
    }

    while (!inFile.eof())
    { //loop to read in info from file
        inFile >> number;
        if (inFile.eof())
        { //case to see if eof is reached
            break;
        }
        sortLL.tailInsert(number); //tail insert number
    }

    inFile.close(); //closes infile

    LL<int>::Iterator i, j, i2, j2;
    LL<int>::Iterator begin, end, nil;
    int temp = 0; //temporary counter variable

    do
    {
        if (temp == 0)
        {
            end = sortLL.end();
            begin = sortLL.begin();
        }
        else
        {
            end = sortLL.end(); //reassigns value of end
            begin = sortLL.begin(); //reassigns value of begin
        }

        swap = false; //idk why this was there, but on the wikipedia page

        for (i = begin; i != end; i++) //loops until the end
        { //going right to left
            i2 = i;
            i2++; //makes sure i2 is always to the right of i
            if (i2 == nullptr)
            { //if i2 is at the end break out
                break;
            }

            if (*i > *i2) //if i is greater than i2
            {   
                sortLL.swapNodes(i, i2);
                swap = true;
            }
        }

        if (!swap) //test case --- also on the wiki page
        {
            break;
        }

        temp++; //increments temp
    
        for (int i = 0; i < temp; i++)
        { //subtract from value of end based on what temp is
            end--;
        }

        for (int i = 0; i < temp; i++)
        { //add onto begin based on what temp is
            begin++;
        }

        swap = false; 

        for (j = end; j != begin; j--)
        { //going left to right
            j2 = j;
            j2--; //makes sure j2 is to the left of j
            if (j2 == nullptr)
            { //check to see if j2 is at the end
                break;
            }

            if (*j < *j2) //if j is less than j2 
            {
                sortLL.swapNodes(j2, j); // swaps
                swap = true;
            }
        }

        if (!swap) //test case ---  also on the wiki page
        {
            break;
        }
     
        
    } while (swap);

    for (i = sortLL.begin(); i != nil; i++)
    { //loop to print out list
        cout << *i << endl;
    }
    
    return 0;
}

