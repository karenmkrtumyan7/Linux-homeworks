#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE sizeof(BankAccount)*N

struct BankAccount {
    int current_balance;
    int min_balance;
    int max_balance;
    bool frozen;
};

class Bank {
public:
    Bank(int N);
    ~Bank();
    void print_balance(int account_num);
    void print_min_balance(int account_num);
    void print_max_balance(int account_num);
    void freeze_account(int account_num);
    void unfreeze_account(int account_num);
    void transfer(int from_account, int to_account, int amount);
    void adjust_balances(int amount);
    void set_min_balance(int account_num, int min_balance);
    void set_max_balance(int account_num, int max_balance);
private:
    BankAccount* bank_accounts;
    int shmid;
    int N;
};

Bank::Bank(int N) {
    this->N = N;
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    bank_accounts = (BankAccount*) shmat(shmid, NULL, 0);
    if (bank_accounts == (BankAccount*) -1) {
        perror("shmat");
        exit(1);
    }
    memset(bank_accounts, 0, SHM_SIZE);
    for (int i = 0; i < N; i++) {
        bank_accounts[i].max_balance = 10000000;
        bank_accounts[i].min_balance = 0;
        bank_accounts[i].frozen = false;
    }
}

Bank::~Bank() {
    shmdt(bank_accounts);
    shmctl(shmid, IPC_RMID, NULL);
}

void Bank::print_balance(int account_num) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    std::cout << "Current balance of account " << account_num << ": " << bank_accounts[account_num].current_balance << "\n";
}

void Bank::print_min_balance(int account_num) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    std::cout << "Minimum balance of account " << account_num << ": " << bank_accounts[account_num].min_balance << "\n";
}

void Bank::print_max_balance(int account_num) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    std::cout << "Maximum balance of account " << account_num << ": " << bank_accounts[account_num].max_balance << "\n";
}

void Bank::freeze_account(int account_num) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    if (bank_accounts[account_num].frozen) {
        std::cout << "Account is already frozen\n";
        return;
    }
    bank_accounts[account_num].frozen = true;
    std::cout << "Account " << account_num << " has been frozen\n";
}

void Bank::unfreeze_account(int account_num) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    if (!bank_accounts[account_num].frozen) {
        std::cout << "Account is not frozen\n";
        return;
    }
    bank_accounts[account_num].frozen = false;
    std::cout << "Account " << account_num << " has been unfrozen\n";
}

void Bank::transfer(int from_account, int to_account, int amount) {
    if (from_account < 0 || from_account >= N || to_account < 0 || to_account >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    if (bank_accounts[from_account].frozen || bank_accounts[to_account].frozen) {
        std::cout << "Cannot transfer: one of the accounts is frozen\n";
        return;
    }
    if (amount <= 0) {
        std::cout << "Cannot transfer: invalid amount\n";
        return;
    }
    if (bank_accounts[from_account].current_balance < amount) {
        std::cout << "Cannot transfer: insufficient funds in account " << from_account << "\n";
        return;
    }
    int old_from_balance = bank_accounts[from_account].current_balance;
    bank_accounts[from_account].current_balance -= amount;
    int new_from_balance = bank_accounts[from_account].current_balance;
    int old_to_balance = bank_accounts[to_account].current_balance;
    bank_accounts[to_account].current_balance += amount;
    int new_to_balance = bank_accounts[to_account].current_balance;
    std::cout << "Transferred " << amount << " from account " << from_account << " to account " << to_account << "\n";
    std::cout << "Balance of account " << from_account << " changed from " << old_from_balance << " to " << new_from_balance << "\n";
    std::cout << "Balance of account " << to_account << " changed from " << old_to_balance << " to " << new_to_balance << "\n";
}

void Bank::adjust_balances(int amount) {
    for (int i = 0; i < N; i++) {
        if (!bank_accounts[i].frozen) {
            int old_balance = bank_accounts[i].current_balance;
            bank_accounts[i].current_balance += amount;

            if (bank_accounts[i].current_balance < bank_accounts[i].min_balance) {
                bank_accounts[i].current_balance = bank_accounts[i].min_balance;
            }
            if (bank_accounts[i].current_balance > bank_accounts[i].max_balance) {
                bank_accounts[i].current_balance = bank_accounts[i].max_balance;
            }

            int new_balance = bank_accounts[i].current_balance;
            std::cout << "Balance of account " << i << " changed from " << old_balance << " to " << new_balance << "\n";
        }
    }
}

void Bank::set_min_balance(int account_num, int min_balance) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    if (min_balance < 0) {
        std::cout << "Invalid minimum balance\n";
        return;
    }
    bank_accounts[account_num].min_balance = min_balance;
    std::cout << "Minimum balance of account " << account_num << " set to " << min_balance << "\n";
}

void Bank::set_max_balance(int account_num, int max_balance) {
    if (account_num < 0 || account_num >= N) {
        std::cout << "Invalid account number\n";
        return;
    }
    if (max_balance < 0) {
        std::cout << "Invalid maximum balance\n";
        return;
    }
    bank_accounts[account_num].max_balance = max_balance;
}


int main() {
    int n;
    std::cout << "Enter accounts count: ";
    std::cin >> n;
    Bank bank(n);

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "balance") {
            int account_num;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            bank.print_balance(account_num);
        }
        else if (command == "min_balance") {
            int account_num;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            bank.print_min_balance(account_num);
        }
        else if (command == "max_balance") {
            int account_num;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            bank.print_max_balance(account_num);
        }
        else if (command == "freeze") {
            int account_num;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            bank.freeze_account(account_num);
        }
        else if (command == "unfreeze") {
            int account_num;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            bank.unfreeze_account(account_num);
        }
        else if (command == "transfer") {
            int from_account, to_account, amount;
            std::cout << "Enter from account number: ";
            std::cin >> from_account;
            std::cout << "Enter to account number: ";
            std::cin >> to_account;
            std::cout << "Enter amount: ";
            std::cin >> amount;
            bank.transfer(from_account, to_account, amount);
        }
        else if (command == "adjust_balances") {
            int amount;
            std::cout << "Enter amount: ";
            std::cin >> amount;
            bank.adjust_balances(amount);
        }
        else if (command == "set_min_balance") {
            int account_num, min_balance;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            std::cout << "Enter min balance: ";
            std::cin >> min_balance;
            bank.set_min_balance(account_num, min_balance);
        }
        else if (command == "set_max_balance") {
            int account_num, max_balance;
            std::cout << "Enter account number: ";
            std::cin >> account_num;
            std::cout << "Enter max balance: ";
            std::cin >> max_balance;
            bank.set_max_balance(account_num, max_balance);
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Invalid command.\n";
        }
    }

    return 0;
}








