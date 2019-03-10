//
//  TxRunner.h
//  Final Project
//
//  Created by Ben on 3/9/19.
//  Copyright © 2019 Ben. All rights reserved.
//

#ifndef TxRunner_h
#define TxRunner_h

#include <iostream>
#include "Transaction.h"
#include <unordered_map>
#include <thread>
#include <mutex>

using TransicationMap = std::unordered_map<std::thread::id, Transaction>;

class TxRunner {
public:
    TxRunner(Database& db)
    : db(db) {
    }
    
    template <typename Callback, typename... Args>
    void runTransactional(Callback& fun, Args... args) {
        std::thread::id id = std::this_thread::get_id();
        if (transactionMap.find(id) == transactionMap.end()) {
            Transaction transaction(db);
            std::lock_guard<std::mutex> lock(m);
            transactionMap.emplace(id, transaction);
            transaction.start();
            try {
                fun(this, args...);
            }
            catch (...) {
                transaction.abort();
                transactionMap.erase(id);
                return;
            }
            transactionMap.erase(id);
            transaction.commit();
        }
        else {
            fun(this, args...);
        }
    }
    
    inline Database& get_db() const {
        return db;
    }
    
private:
    Database& db;
    TransicationMap transactionMap;
    std::mutex m;
};

#endif /* TxRunner_h */
