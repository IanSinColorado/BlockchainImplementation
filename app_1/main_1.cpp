#include <iostream>
#include <fstream>
#include "../code_1/Blockchain.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    Blockchain buffCUoin;

    // menu for testing
    buffCUoin.printMenu();

    /*
    buffCUoin.prettyPrint(); 

    cout << "ashutosh mining first block ... " << endl;
    buffCUoin.minePendingTransactions("ashutosh");
    buffCUoin.prettyPrint(); 
    
    cout << "ashutosh paid maciej 1 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","maciej", 1); // this should fail

    cout << "ashutosh paid asa 1 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","asa", 1); // this should fail
    cout << "asa mining second block ... " << endl;
    buffCUoin.minePendingTransactions("asa");
    buffCUoin.prettyPrint(); 
    
    cout << "asa paid ashutosh 1 BFC ... " << endl;
    buffCUoin.addTransaction("asa","ashutosh", 1); // this should fail
    cout << "ashutosh paid maciej 2 BFC ... " << endl;
    buffCUoin.addTransaction("ashutosh","maciej", 2); // this should succeed
    
    cout << "maciej mining third block ... " << endl;
    buffCUoin.minePendingTransactions("maciej");
    buffCUoin.prettyPrint(); 
    
    cout << "ashutosh mining fourth block ... " << endl;
    buffCUoin.minePendingTransactions("ashutosh");
    buffCUoin.prettyPrint();
*/

/*
    buffCUoin.minePendingTransactions("ashutosh");
    buffCUoin.minePendingTransactions("asa");
    buffCUoin.addTransaction("ashutosh","maciej", 2);
    
    buffCUoin.addTransaction("maciej","asa",5); //Unsuccessful
    buffCUoin.minePendingTransactions("maciej");
    buffCUoin.addTransaction("maciej","asa",5);
    buffCUoin.prettyPrint();
    */

   return 0;
}