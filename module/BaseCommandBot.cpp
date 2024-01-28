//
// Created by alex on 11/13/23.
//
#include <tgbot/tgbot.h>
#include "BaseCommandBot.h"
#include "DataBase.h"
#include "links_user_data.h"
#include "token.h"

const std::string dbFileName = "body_therapy.db";

BaseCommandBot::BaseCommandBot() : m_bot(TOKEN), m_database(dbFileName), m_databaseCreaated(false) {}

void BaseCommandBot::createDatabase(int userId, const std::string& username) {
    m_database.createUser(userId, username);
    m_databaseCreaated = true;
}

void BaseCommandBot::baseCommands()
{
  m_bot.getEvents().onCommand("start",
                              [this](TgBot::Message::Ptr message)
                              {
                                int userId = message->chat->id;
                                std::string username = message->chat->username;
                                createDatabase(userId, username);
                                m_bot.getApi().sendMessage(message->chat->id,
                                                           HELLO_MESSAGE);
                              });

  m_bot.getEvents().onCommand(
      "vk",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_VK); });

  m_bot.getEvents().onCommand(
      "tg",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_TG); });

  m_bot.getEvents().onCommand(
      "github",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, UTL_GITHUB); });

  m_bot.getEvents().onCommand(
      "youtube",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_YOUTUBE); });

  m_bot.getEvents().onCommand(
      "boosty",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_BOOSTY); });

    m_bot.getEvents().onCommand(
      "donat_alert",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_DONAT_ALERT); });   

    m_bot.getEvents().onCommand(
      "website",
      [this](TgBot::Message::Ptr message)
      { m_bot.getApi().sendMessage(message->chat->id, URL_WEBSITE); });    

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

    longPoll.start();
  }
  catch (const TgBot::TgException& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}