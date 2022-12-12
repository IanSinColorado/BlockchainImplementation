#include<iostream>
#include <sstream>

#include "Transaction.hpp"
#include "Block.hpp"
#include "Blockchain.hpp"
#include<vector>

using namespace std;

Blockchain::Blockchain() {
    Transaction genesis("BFC","BFC",0);
    pending.push_back(genesis);

    Block gBlock(pending, time(nullptr), "In the beginning..");
    chain.push_back(gBlock);
    pending.clear();

    Transaction freeMoney("BFC","make money by mining",0);
    pending.push_back(freeMoney);

    difficulty = 4;
    miningReward = 10;
}

Block Blockchain::getLatestBlock() { 
    return chain.back();
}

void Blockchain::addTransaction(string src, string dst, int coins) {
    // check to see if it is a mining reward
    if(src == "BFC") {
        // add the transaction (for the mining)
        Transaction newTransaction = Transaction(src, dst, coins);
        pending.push_back(newTransaction);
    }
    // check to see if they have enough to spend by adding the total amount in the chain and the pending list
    // Note: the pending list return can be negative to ensure that coins are not spent multiple
    else if((getBalanceOfAddress(src) + getBalanceOfPendingAddress(src)) >= coins) {
        // add the transaction
        Transaction newTransaction = Transaction(src, dst, coins);
        pending.push_back(newTransaction);
    }
    // otherwise, the source address does not have enough coins to complete the transaction
    else {
        cout << "ERROR: Transaction could not be added as amount sent is greater than user BuffCUoins." << endl;
    }
}

bool Blockchain::isChainValid() { 
    // generate the string for checking the difficulty
    string zeroTest;
    for(unsigned int i = 0; i < difficulty; i++) {
        zeroTest += "0";
    }

    // loop through the blockchain starting at the second block
    for(unsigned int i = 1; i < chain.size() - 1; i++) {
        // check if the next block has the correct previous hashcode
        // (make sure they match)
        if(chain[i+1].getPreviousHash() != chain[i].getHash()) {
            // if they don't match, then return false as the chain is invalid
            return false;
        }

        // check that the block has the correct amount of 0s in its hash code
        if(chain[i+1].getHash().substr(0, difficulty) != zeroTest) {
            // if it doesn't, then return false as the chain is invalid
            return false;
        }
    }
    // return true if it can get through the chain
    return true;
}

bool Blockchain::minePendingTransactions(string minerAddress) {
    // copy the current pending vector
    vector<Transaction> currentTransactions = pending;

    // generate a new block with the current pending vector, the time, and the previous block's hash
    Block newBlock = Block(currentTransactions, time(nullptr), getLatestBlock().getHash());

    // mine the block
    newBlock.mineBlock(difficulty);

    // clear the pending list
    pending.clear();

    // push the completed block to the chain
    chain.push_back(newBlock);

    // add mining reward to the pending list
    addTransaction("BFC", minerAddress, 10);

    return true;
}

int Blockchain::getBalanceOfAddress(string address) {
    // initialize counters for the coins spent and earned
    int coinsEarned = 0;
    int coinsSpent = 0;

    // loop through the blockchain
    for(unsigned int i = 1; i < chain.size(); i++) {
        // traverse through the block's transactions and add the coins earned and spent
        for(unsigned int j = 0; j < chain[i].getTransactions().size(); j++) {
            // check to see if the reciever is the address inputted
            if(chain[i].getTransactions()[j].getReceiver() == address) {
                // increase the earned counter
                coinsEarned += chain[i].getTransactions()[j].getAmount();
            }
            // check to see if the sender is the address inputted
            if(chain[i].getTransactions()[j].getSender() == address) {
                // increase the spent counter
                coinsSpent += chain[i].getTransactions()[j].getAmount();
            }
        }
    }

    // get the total by subtracting the amount of coins earned from spent
    int total = coinsEarned - coinsSpent;

    // add a check to see if the total is less than 0 (will never reach)
    if(total < 0) {
        cout << "ERROR: balance less than 0" << endl;
    }

    // return the total
    return total;
}

int Blockchain::getBalanceOfPendingAddress(string address) {
    // initialize counters for the amount of coin spent and earned
    int coinsEarned = 0;
    int coinsSpent = 0;

    // loop through the pending transaction vector
    for(unsigned int i = 0; i < pending.size(); i++) {
        // check to see if the address was the reciever
        if(pending[i].getReceiver() == address) {
            // add to the earned counter
            coinsEarned += pending[i].getAmount();
        }
        // check to see if the address was the sender
        if(pending[i].getSender() == address) {
            // add to the spent counter
            coinsSpent += pending[i].getAmount();
        }
    }

    // get the total coins for the address in the pending menu (can be negative)
    int total = coinsEarned - coinsSpent;

    // return the total coins
    return total;
}

void Blockchain::prettyPrint() {
    // loop throught the blockchain vector
    for(unsigned int i = 0; i < chain.size(); i++) {
        // print the block number, hash, previous hash, time stamp, and nonce
        cout << "Block #" << i + 1 << ": " << endl;
        cout << "Hash: " << chain[i].getHash() << endl;
        cout << "Previous Hash: " << chain[i].getPreviousHash() << endl;
        cout << "Time Stamp: " << chain[i].getTimestamp() << endl;
        cout << "Nonce: " << chain[i].getNonce() << endl;

        // loop through each block's list of transactions and print
        cout << "Transactions: ";
        for(unsigned int j = 0; j < chain[i].getTransactions().size(); j++) {
            cout << chain[i].getTransactions()[j].toString() << ", ";
        }
        cout << endl;
    }
}

void Blockchain::printMenu() {
    // this is the general menu to test the code's functionality
    bool quit = false;
    while (!quit) {
        int option;
        string inputLine;

        cout << "======Main Menu======" << endl;
        cout << "1. Add a transation" << endl;
        cout << "2. Verify Blockchain" << endl;
        cout << "3. Mine Pending Transactions" << endl;
        cout << "4. Get Balance of User" << endl;
        cout << "5. Print the Blockchain" << endl;
        cout << "6. Quit" << endl;

        getline(cin, inputLine);
        option = stoi(inputLine);

        switch (option) {
            case 1: {
                // add transaction
                string senderUser;
                cout << "Enter the sender's username: " << endl;
                getline(cin, senderUser);

                string recieverUser;
                cout << "Enter the reciever's username: " << endl;
                getline(cin, recieverUser);

                string amountSent;
                cout << "Enter the amount of BuffCUoins to be transferred: " << endl;
                getline(cin, amountSent);
                int amount = stoi(amountSent);

                // call the add transaction function with user input
                addTransaction(senderUser, recieverUser, amount);
            break;}

            case 2: {
                // verify blockchain
                bool check = isChainValid();

                if(check) {
                    cout << "The current blockchain is valid." << endl;
                }
                else {
                    cout << "ERROR: Blockchain is invalid." << endl;
                }
            break;}

            case 3: {
                // mine
                string user;
                cout << "Enter the username of the miner: " << endl;
                getline(cin, user);

                minePendingTransactions(user);
            break;}

            case 4: {
                // get balance
                string user;
                cout << "Enter the username of the account owner: " << endl;
                getline(cin, user);

                int accountTotal = getBalanceOfAddress(user);

                cout << "The user " << user << " has " << accountTotal << " BuffCUoins." << endl;
            break;}

            case 5: {
                // print the block chain
                prettyPrint();
            break;}

            case 6: {
                // quit
                cout << "Thank you for using BuffCUoins!" << endl;
                quit = true;
            break;}

            default: cout << "Invalid input. Please enter a number between 1 and 6." << endl; break;
        }
    }
}