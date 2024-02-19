// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com

//
// Created by alex on 11/19/23.
//

#include "DataBase.h"

#include <iostream>

Database::Database(const std::string& dbFileName)
{
  if (sqlite3_open(dbFileName.c_str(), &db) != SQLITE_OK)
  {
    std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    exit(EXIT_FAILURE);
  }

  // Create a table if it doesn't exist
  const char* createTableSQL =
      "CREATE TABLE IF NOT EXISTS users ("
      "id INTEGER PRIMARY KEY,"
      "user_id INTEGER UNIQUE,"
      "username TEXT);";
  if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr) != SQLITE_OK)
  {
    std::cerr << "Cannot create table: " << sqlite3_errmsg(db) << std::endl;
    exit(EXIT_FAILURE);
  }
}

Database::~Database() { sqlite3_close(db); }

void Database::createUser(int userId, const std::string& username)
{
  const char* insertSQL =
      "INSERT OR REPLACE INTO users (user_id, username) VALUES (?, ?);";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
      std::cerr << "Cannot execute insert statement: " << sqlite3_errmsg(db)
                << std::endl;
    }

    sqlite3_finalize(stmt);
  }
  else
  {
    std::cerr << "Cannot prepare insert statement: " << sqlite3_errmsg(db)
              << std::endl;
  }
}

std::string Database::getUsername(int userId)
{
  const char* selectSQL = "SELECT username FROM users WHERE user_id = ?;";
  sqlite3_stmt* stmt;
  std::string username;

  if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK)
  {
    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
      username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
  }
  else
  {
    std::cerr << "Cannot prepare select statement: " << sqlite3_errmsg(db)
              << std::endl;
  }

  return username;
}
