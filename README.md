# Backpack-with-Bitcoin-transactions
Testing task for company

How to run this project? You should download all files and run Website Analytics.sin by using Visual Studio. If you haven`t Visual Studio, copy and paste code from main.cpp in your IDE.

1. Reading Transactions (read_transactions function):
Time Complexity: 𝑂(𝑛), where 𝑛 is the number of transactions in the CSV file. This is because we need to read each line from the file and parse it into a transaction object, which involves a constant amount of work per transaction.

2. Constructing the Block (construct_block function):
Sorting: The most computationally intensive part is sorting the transactions based on the ratio tx_fee / tx_size.
Time Complexity: 𝑂(𝑛 log 𝑛), where 𝑛 is the number of transactions. Sorting algorithms like quicksort or mergesort typically have an average time complexity of 𝑂(𝑛 log 𝑛).

Selecting Transactions: After sorting, we iterate through the transactions to select those that fit within the block size limit.
Time Complexity: O(n), because in the worst case, we might need to consider all transactions to fill the block.

3. Overall Time Complexity:
The dominant factor in the time complexity is the sorting step O(n log n)).
Therefore, the overall time complexity of the solution can be approximated as O(n log n).

4. Space Complexity:
Data Storage: We store the transactions in a vector, which takes O(n) space, where 𝑛 is the number of transactions.
Sorting: Depending on the sorting algorithm used, it may require additional space. Quicksort, for instance, typically requires O(log n) auxiliary space for recursion.
