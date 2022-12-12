#include<iostream>
#include <sstream>


#include "Transaction.hpp"
#include "Block.hpp"
#include "sha256.hpp"

using namespace std;

Block::Block(vector<Transaction> _transactions, time_t _timestamp, string _previousHash) {
    nonce = -1;
    transactions = _transactions;
    previousHash = _previousHash;
    timestamp = _timestamp;
    hash = calculateHash();
}

void Block::setPreviousHash(string _previousHash) {
    // set the previous hash to the inputted hash
    this->previousHash = _previousHash;
}

string Block::calculateHash() {
    // return the sha256 of the block's toString
    return sha256(toString());  
}

void Block::mineBlock(unsigned int difficulty) {
    // make the string to check that the number of zeros at the beginning has been reached
    string difficultyZeros;
    for(unsigned int i = 0; i < difficulty; i++) {
        difficultyZeros += "0";
    }

    // loop until the correct hash is found
    bool flag = true;
    string currentHash;
    while(flag) {
        // calculate a random hash
        currentHash = calculateHash();

        // check to see if this hash meets the difficulty requirement
        if(currentHash.substr(0, difficulty) == difficultyZeros) {
            // if it does then break the loop to keep the current hash
            flag = false;
        }

        /*
        // Ensure there is not an integer overflow (just in case)
        if(nonce == 9223372036854775807) {
            nonce = -9223372036854775807;
        }

        // if it loops back to -2 and the flag is still true, then there is not hash that can be created
        if(nonce == -2 && flag != false) {
            cout << "Hash with given difficulty could not be found." << endl;
            break;
        }
        */
        // incremet the nonce value if the proper hashcode is not found
        nonce++;
    }

    // set the block's hashcode to be the new found hashcode
    hash = currentHash;
}

string Block::toString() {
    // generate the string stream
    stringstream ss;

    // put in the data of the block
    ss << nonce << previousHash << timestamp;
    for(unsigned int i = 0; i < transactions.size(); i++) {
        ss << transactions[i].toString();
    }
    return ss.str();
}

// getter functions to access data outside of class
vector<Transaction> Block::getTransactions() {
    return transactions;
}

string Block::getPreviousHash() {
    return previousHash;
}

string Block::getHash() {
    return hash;
}

long long Block::getNonce() {
    return nonce;
}

time_t Block::getTimestamp() {
    return timestamp;
}