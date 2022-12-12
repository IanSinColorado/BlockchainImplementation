# CSCI 2270 – Data Structures - Final Project - Simple Implementation of a Blockchain and Cryptocurrency
Author: J. Ian Stewart

General Description:
This is a simple implementation of a blockchain where the miners are rewarded 10 BuffCUoins. The menu allows for
the user to add transactions, verify the current blockchain, mine the pending transactions, get the balance of
an address, and finally print the blockchain.

Function Descriptions and their Implementations:
Blockchain:
addTransaction:
Purpose: This function adds a transaction to the list of pending transactions, if the source address has enough BuffCUoins.
Implementation: This funcion works by taking in two strings, one representing the source and the other 
the reciever of the transaction, and the amount of coins to be potentially transferred. It first checks if 
the source is "BFC" as this will always get added to the pending list as it is the mining reward. If the name
is not source, then it adds the balance of the source address in the chain and the balance of the source in the
list of pending transactions. If the addition is greater than or equal to the amount of coins transferred, 
the transaction is added, otherwise it prints an error as the source does not have enough BuffCUoins to 
allow the transaction to occur.

isChainValid:
Purpose: This function returns true if the chain is valid, and false otherwise
Implementation: This function has no parameters, but loops through the chain, starting from the second block and
checks that the next block's previousHash and the current block's hash match. It also checks that all of the hash
codes have the correct difficulty, except for the genesis block.

minePendingTransactions:
Purpose: This function adds a block to the chain and puts all pending transactions into the new block.
Implementation: This function first creates a new block by copying the current pending vector, setting 
the time to null, and the latestblock's hash code. It then sets the hash code with the mine() function
explained below. It then clears the pending list of transactions and then adds the new block to the chain.
Finally, it adds the miner's reward to the empty pending list.

getBalanceOfAddress:
Purpose: This function returns the amount of BuffCUoins the given address has in the block chain.
Implementation: This function loops through the chain of blocks. For every block, it loops through
the list of transactions and adds to the number of coins spent if the address is the sender, and adds
to the number of coins earned if the address is the reciever. Finally, it then returns the total amount of coins
by subtracting the number of coins earned and the number of coins spent. If this is a negative value, it
will print an error message.

getBalanceOfPendingAddress:
Purpose: This function returns the amount of BuffCUoins the given address has in the pending transactions.
Implementation: This function loops through the pending transaction list and adds to the number of coins spent
if the address is the sender, and adds to the number of coins earned if the address is the reciever. It then
returns the total coins the address has in the pending list by subtracting the number of coins spent and earned.
Note: This can be a negative number, to make sure coins are not spent multiple times.

prettyPrint:
Purpose: Print the blockchain nicely
Implementation: This function loops through all of the blocks in the chain and prints which block it is in the chain,
its hash code, the hash code of the previous block, the time stamp, the nonce, and loops through and prints all of 
the transactions.

printMenu:
Purpose: A menu that gives the user a list of choices to use the blockchain.
Implementation: This function first prints the menu of choices and allows the user to pick a choice. From there, it
looks at the user's input and asks for additional input, if necessary, and calls the associated function.

Block:
calculateHash:
Purpose: Give a SHA256 value based on the block's data.
Implementation: Returns the string generated from calling the Blockchain::toString() function, explained below.

mineBlock:
Purpose: Set the block's hash so that the first difficulty number of digits are 0's.
Implementation: This function first generates a string that has the correct number of 0's in the beginning of the
hash value. Next the function will loop until a hash code is produced with the correct number of 0's in the beginning.
Finally, it sets the hash code to be the generated code. 

toString:
Purpose: Condense all of the contents of the block into a string.
Implementation: Put all of the block's data (nonce, previousHash, timestamp, transactions) into a stringstream.
Finally, it returns the string equivalent of the generated stringstream.

Getters:
Purpose: To get the private contents of the block to be used in Blockchain.cpp.
Implementation: Simple functions that return the transaction list, previous hash, current hash, nonce, and the timestamp.