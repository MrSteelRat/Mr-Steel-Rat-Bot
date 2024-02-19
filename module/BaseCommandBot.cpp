// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// http://www.viva64.com
//
// Created by alex on 11/13/23.
//

#include <tgbot/tgbot.h>

#include "token.h"
#include "links_user_data.h"
#include "BaseCommandBot.h"
#include "DataBase.h"

const std::string dbFileName = "body_therapy.db";

BaseCommandBot::BaseCommandBot()
    : m_bot(TOKEN), m_database(dbFileName), m_databaseCreaated(false)
{
}

void BaseCommandBot::createDatabase(int userId, const std::string& username)
{
  m_database.createUser(userId, username);
  m_databaseCreaated = true;
}

void BaseCommandBot::baseCommands()
{
  auto sendMessage = [this](const std::string& command,
                            const std::string& url,
                            TgBot::Message::Ptr message)
  { m_bot.getApi().sendMessage(message->chat->id, url); };

  m_bot.getEvents().onCommand("start",
                              [this](TgBot::Message::Ptr message)
                              {
                                int userId = message->chat->id;
                                std::string username = message->chat->username;
                                createDatabase(userId, username);
                                m_bot.getApi().sendMessage(message->chat->id,
                                                           HELLO_MESSAGE);
                              });

  m_bot.getEvents().onCommand("vk",
                              [sendMessage](TgBot::Message::Ptr message)
                              { sendMessage("vk", URL_VK, message); });

  m_bot.getEvents().onCommand("tg",
                              [sendMessage](TgBot::Message::Ptr message)
                              { sendMessage("tg", URL_TG, message); });

  m_bot.getEvents().onCommand("github",
                              [sendMessage](TgBot::Message::Ptr message)
                              { sendMessage("github", UTL_GITHUB, message); });

  m_bot.getEvents().onCommand("youtube",
                              [sendMessage](TgBot::Message::Ptr message) {
                                sendMessage("youtube", URL_YOUTUBE, message);
                              });

  m_bot.getEvents().onCommand("boosty",
                              [sendMessage](TgBot::Message::Ptr message)
                              { sendMessage("boosty", URL_BOOSTY, message); });

  m_bot.getEvents().onCommand(
      "donat_alert",
      [sendMessage](TgBot::Message::Ptr message)
      { sendMessage("donat_alert", URL_DONAT_ALERT, message); });

  m_bot.getEvents().onCommand("website",
                              [sendMessage](TgBot::Message::Ptr message) {
                                sendMessage("website", URL_WEBSITE, message);
                              });

  m_bot.getEvents().onAnyMessage(
      [this](TgBot::Message::Ptr message)
      {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start"))
        {
          return;
        }
      });
  try
  {
    std::cout << "Bot username: " << m_bot.getApi().getMe()->username
              << std::endl;
    TgBot::TgLongPoll longPoll(m_bot);
    while (true)
    {
      std::cout << "Long poll started" << std::endl;
      longPoll.start();
    }
  }
  catch (const TgBot::TgException& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  } 
  catch (...) {
    std::cout << "error 2" << "\n";
  }
}
