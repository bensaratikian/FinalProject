//
//  main.cpp
//  Final Project
//
//  Created by Ben on 3/9/19.
//  Copyright © 2019 Ben. All rights reserved.
//

#include "TxRunner.h"

int main(int argc, const char * argv[]) {
    
    Database db;
    TxRunner tx_runner(db);
    std::cout << "First test.\n" << "In lambda function we calculate a + b function on every recursive call until 'a' is not 0.\n" << std::endl;
    std::function<void(TxRunner* tx, int a, double b)> func = [&func](TxRunner* tx, int a, double b) {
        if (a == 0)
            return;
        std::cout << "In lambda func: a+b=" << a + b << std::endl;
        
        // Call some write method on transaction database
        tx->get_db().write(a + b);
        tx->runTransactional(func, a - 1, b);
    };
    tx_runner.runTransactional(func, 5, 8.5);
    
    std::cout << "\nSecond test.\n" << "Here we submit a function that throws an exception\n";
    std::function<void(TxRunner* tx, int a, int b)> func_error = [&func](TxRunner* tx, int a, int b) {
        if (b == 0)
            throw std::runtime_error("Division to zero");
        
        // Call some write method on transaction database
        tx->get_db().write(a / b);
    };
    tx_runner.runTransactional(func_error, 10, 0);
    
    return 0;
}
