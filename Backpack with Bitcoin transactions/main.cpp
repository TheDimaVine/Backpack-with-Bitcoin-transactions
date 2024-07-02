#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Transaction {
    std::string tx_id;
    int tx_size;
    int tx_fee;
};

std::vector<Transaction> read_transactions(const std::string& file_path) {
    std::vector<Transaction> transactions;
    std::ifstream file(file_path);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    // Пропускаем заголовок
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string tx_id, tx_size, tx_fee;

        std::getline(ss, tx_id, ',');
        std::getline(ss, tx_size, ',');
        std::getline(ss, tx_fee, ',');

        transactions.push_back({ tx_id, std::stoi(tx_size), std::stoi(tx_fee) });
    }

    file.close();
    return transactions;
}

std::vector<Transaction> construct_block(std::vector<Transaction>& transactions, int max_block_size, int& total_size, int& total_fee) {
    // Сортировка транзакций по убыванию коэффициента "комиссия/размер"
    std::sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
        return (double)a.tx_fee / a.tx_size > (double)b.tx_fee / b.tx_size;
        });

    std::vector<Transaction> block;
    total_size = 0;
    total_fee = 0;

    for (const auto& tx : transactions) {
        if (total_size + tx.tx_size <= max_block_size) {
            block.push_back(tx);
            total_size += tx.tx_size;
            total_fee += tx.tx_fee;
        }
    }

    return block;
}

int main() {
    std::string file_path = "transactions.txt"; // Замените на путь к вашему CSV файлу

    std::vector<Transaction> transactions;
    try {
        transactions = read_transactions(file_path);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    const int max_block_size = 1000000; // 1 MB in bytes
    int total_size = 0;
    int total_fee = 0;

    std::vector<Transaction> block = construct_block(transactions, max_block_size, total_size, total_fee);

    std::cout << "Constructed block:\n";
    for (const auto& tx : block) {
        std::cout << tx.tx_id << '\n';
    }

    std::cout << "Amount of transactions in the block: " << block.size() << '\n';
    std::cout << "Block size: " << total_size << " bytes\n";
    std::cout << "Total extracted value: " << total_fee << " satoshies\n";

    return 0;
}

