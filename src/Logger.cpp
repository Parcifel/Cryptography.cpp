#include "Logger.h"

bool Logger::debugEnabled = false;
bool Logger::verboseEnabled = false;

const map<MessageType, MessageTypeInfo> Logger::messageTypes = {
  {MessageType::INFO,     {"INFO",      Color::BLUE,    Color::BRIGHT_BLUE}},
  {MessageType::DEBUG,    {"DEBUG",     Color::MAGENTA, Color::BRIGHT_MAGENTA}},
  {MessageType::OUTPUT,   {"OUTPUT",    Color::CYAN,    Color::BRIGHT_CYAN}},
  {MessageType::SUCCESS,  {"SUCCESS",   Color::GREEN,   Color::BRIGHT_GREEN}},
  {MessageType::TABLE,    {"TABLE",     Color::BLUE,    Color::BRIGHT_BLUE}},
  {MessageType::VERBOSE,  {"VERBOSE",   Color::BLUE,  Color::BRIGHT_BLUE}},
  {MessageType::ERROR,    {"ERROR",     Color::RED,     Color::BRIGHT_RED}},
  {MessageType::WARNING,    {"WARNING",     Color::YELLOW,     Color::BRIGHT_YELLOW}},
};