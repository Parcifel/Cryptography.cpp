#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

enum class Color {
  RESET       = 0,
  // Regular foreground colors
  BLACK             = 30,
  RED               = 31,
  GREEN             = 32,
  YELLOW            = 33,
  BLUE              = 34,
  MAGENTA           = 35,
  CYAN              = 36,
  WHITE             = 37,
  GRAY             = 90,
  // Bright foreground colors
  BRIGHT_BLACK      = 90,
  BRIGHT_RED        = 91,
  BRIGHT_GREEN      = 92,
  BRIGHT_YELLOW     = 93,
  BRIGHT_BLUE       = 94,
  BRIGHT_MAGENTA    = 95,
  BRIGHT_CYAN       = 96,
  BRIGHT_WHITE      = 97,
  // Regular background colors
  BG_BLACK          = 40,
  BG_RED            = 41,
  BG_GREEN          = 42,
  BG_YELLOW         = 43,
  BG_BLUE           = 44,
  BG_MAGENTA        = 45,
  BG_CYAN           = 46,
  BG_WHITE          = 47,
  BG_GRAY           = 100,
  // Bright background colors
  BG_BRIGHT_BLACK   = 100,
  BG_BRIGHT_RED     = 101,
  BG_BRIGHT_GREEN   = 102,
  BG_BRIGHT_YELLOW  = 103,
  BG_BRIGHT_BLUE    = 104,
  BG_BRIGHT_MAGENTA = 105,
  BG_BRIGHT_CYAN    = 106,
  BG_BRIGHT_WHITE   = 107
};

enum class Decoration {
  BOLD              = 1,
  DIM               = 2,
  ITALIC            = 3,
  UNDERLINE         = 4,
  BLINK             = 5,
  REVERSE           = 7,
  HIDDEN            = 8,
  STRIKETHROUGH     = 9
};

struct MessageTypeInfo {
  string name;
  Color color;
  Color brightColor;
};

enum class MessageType {
  INFO,   // Blue
  DEBUG,  // Magenta
  OUTPUT,  // Cyan
  SUCCESS, // Green
  TABLE,
  VERBOSE,
  ERROR,
  WARNING
};

class Logger {
private:
  static const map<MessageType, MessageTypeInfo> messageTypes;
  static bool debugEnabled;
  static bool verboseEnabled;

  static std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%H:%M:%S");
    return ss.str();
  }

  template<typename T>
  static string toString(const T& value) {
    stringstream ss;
    ss << value;
    return ss.str();
  }

  template<typename T>
  static string toString(const vector<T>& value) {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < value.size(); ++i) {
      ss << toString(value[i]);
      if (i != value.size() - 1) {
        ss << ", ";
      }
    }
    ss << "]";
    return ss.str();
  }

  static vector<size_t> calculateColumnWidths(const vector<string>& headers, const vector<vector<string>>& data) {
    vector<size_t> widths(max(headers.size(), data.empty() ? 0 : data[0].size()), 0);

    for (size_t i = 0; i < headers.size(); ++i) {
      widths[i] = max(widths[i], headers[i].length());
    }

    for (const auto& row : data) {
      for (size_t i = 0; i< row.size(); ++i) {
        widths[i] = max(widths[i], row[i].length());
      }
    }

    return widths;
  }

public:
  static void enableDebug(bool enable = true) { debugEnabled = enable; }
  static void enableVerbose(bool enable = true) { verboseEnabled = enable; }

  template<typename T>
  static void log(MessageType type, const std::string& header, const T& message) {
    if (type == MessageType::DEBUG && !debugEnabled) return;
    if (type == MessageType::VERBOSE && !verboseEnabled) return;

    auto& info = messageTypes.at(type);
    std::cout << "\033[" << static_cast<int>(Color::GRAY) << "m"
              << "[" << getTimestamp() << "] "                          // Timpstamp
              << "\033[" << static_cast<int>(info.color) << "m"
              << "[" << info.name << "] "                               // MessageType
              << "\033[" << static_cast<int>(info.brightColor) << "m"
              << header << ": "                                         // Header
              << "\033[" << static_cast<int>(Color::RESET) << "m"
              << toString(message) << std::endl;                                  // Message
  }

  template<typename T>
  static void log(MessageType type, const std::string& header, const vector<T>& message) {
    if (type == MessageType::DEBUG && !debugEnabled) return;
    if (type == MessageType::VERBOSE && !verboseEnabled) return;

    auto& info = messageTypes.at(type);
    std::cout << "\033[" << static_cast<int>(Color::GRAY) << "m"
              << "[" << getTimestamp() << "] "                          // Timpstamp
              << "\033[" << static_cast<int>(info.color) << "m"
              << "[" << info.name << "] "                               // MessageType
              << "\033[" << static_cast<int>(info.brightColor) << "m"
              << header << ": "                                         // Header
              << "\033[" << static_cast<int>(Color::RESET) << "m"
              << toString(message) << std::endl;                                  // Message
  }

  template<typename... Args>
  static void table(MessageType type, const string& tableHeader, const vector<string>& headers, const vector<vector<Args...>>& rawData) {
    if (type == MessageType::DEBUG && !debugEnabled) return;
    if (type == MessageType::VERBOSE && !verboseEnabled) return;

    vector<vector<string>> data;
    for (const auto& row : rawData) {
      vector<string> stringRow;
      for (const auto&cell : row) {
        stringRow.push_back(toString(cell));
      }
      data.push_back(stringRow);
    }
    if (!headers.empty() && headers.size() != data[0].size()) {
      throw invalid_argument("Headers count must match column count");
    }
    if (data.empty()) {
      throw invalid_argument("Data cannot be empty");
    }

    vector<size_t> columnWidths = calculateColumnWidths(headers, data);

    auto& info = messageTypes.at(type);

    std::cout << "\033[" << static_cast<int>(Color::GRAY) << "m"
              << "[" << getTimestamp() << "] "
              << "\033[" << static_cast<int>(info.color) << "m"
              << "[" << info.name << "] "
              << "\033[" << static_cast<int>(info.brightColor) << "m"
              << tableHeader << ":\n";

    if (!headers.empty()) {
      cout << "\033[" << static_cast<int>(Color::BRIGHT_WHITE) << "m";
      for (size_t i = 0; i < headers.size(); ++i) {
        cout << "  " << setw(columnWidths[i]) << left << headers[i] << " ";
      }
      cout << "\n";
      for (size_t i = 0; i < headers.size(); ++i) {
        cout << " -" << setw(columnWidths[i]) << left << string(columnWidths[i], '-') << "-";
      }
      cout << "\n";
    }

    cout << "\033[" << static_cast<int>(Color::RESET) << "m";
    for (const auto& row : data) {
      for (size_t i = 0; i < row.size(); ++i) {
        cout << "  " << setw(columnWidths[i]) << left << row[i] << " ";
      }
      cout << "\n";
    }
  }

  static void blank(MessageType type) {
    if (type == MessageType::DEBUG && !debugEnabled) return;
    if (type == MessageType::VERBOSE && !verboseEnabled) return;

    cout << "\n";
  }

  static void blank(MessageType type, int n) {
    if (type == MessageType::DEBUG && !debugEnabled) return;
    if (type == MessageType::VERBOSE && !verboseEnabled) return;

    for (int i = 0; i < n; i++) {
      cout << "\n";
    }
  }
};

#endif