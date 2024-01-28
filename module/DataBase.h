//
// Created by alex on 11/19/23.
//

// Database.h
#pragma once

#include <string>
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& dbFileName);
    ~Database();  

    void createUser(int userId, const std::string& username);
    std::string getUsername(int userId);
    
private:
    sqlite3* db;
};
