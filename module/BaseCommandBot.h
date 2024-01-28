//
// Created by alex on 11/13/23.
//

#ifndef SOFI_SI_BODY_THERAPY_BASECOMMANDBOT_H
#define SOFI_SI_BODY_THERAPY_BASECOMMANDBOT_H

#include <iostream>
#include <string>

#include <tgbot/tgbot.h>

#include "DataBase.h"

class BaseCommandBot
{
 public:
  BaseCommandBot();
  void baseCommands();

 private:
  TgBot::Bot m_bot;
  Database m_database; 
  bool m_databaseCreaated;
  
  void createDatabase(int userId, const std::string& username);
};

#endif  // SOFI_SI_BODY_THERAPY_BASECOMMANDBOT_H
