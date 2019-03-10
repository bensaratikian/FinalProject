//
//  Transaction.h
//  Final Project
//
//  Created by Ben on 3/9/19.
//  Copyright © 2019 Ben. All rights reserved.
//

#ifndef Transaction_h
#define Transaction_h

#include "Database.h"

class Transaction {
public:
    Transaction(Database& db) : db(db) {
        
    }
    
    ~Transaction() {
        
    }
    
    /// Starts the TX. Illegal to call if the TX already started.
    void start() {
        std::cout << "Transication has been started" << std::endl;
    }
    
    /// Commits a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
    void commit() {
        std::cout << "Transication has commited" << std::endl;
    }
    
    /// Aborts a started TX. Illegal to call if TX was not yet started or is already committed/aborted.
    void abort() {
        std::cout << "Transication has been aborted" << std::endl;
    }
    
    
private:
    Database& db;
};



#endif /* Transaction_h */
