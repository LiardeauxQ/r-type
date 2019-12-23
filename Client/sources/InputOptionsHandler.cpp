//
// Created by Quentin Liardeaux on 10/11/19.
//

#include "InputOptionsHandler.hpp"

std::vector<InputOptionsHandler::OptionInfo> InputOptionsHandler::options_ = {
    OptionInfo { CREATE_SESSION, "-c", "--createSession" },
    OptionInfo { SESSION_NAME, "-s", "--name" },
    OptionInfo { PASSWORD, "-w", "--password" },
    OptionInfo { NICKNAME, "-n", "--nickname" },
    OptionInfo { SERVER_PORT, "-p1", "--serverPort" },
    OptionInfo { CLIENT_PORT, "-p2", "--clientPort" },
    OptionInfo { HELP, "-h", "--help" },
};

InputOptionsHandler::InputOptionsHandler(int argc, char** argv)
    : argc_(argc)
    , argv_(argv)
{
}

InputOptionsHandler::OptionInfo InputOptionsHandler::getOption(OptionId id)
{
    for (auto option : options_) {
        if (option.id == id) {
            return option;
        }
    }
    return OptionInfo {};
}

std::string InputOptionsHandler::getOptionValue(OptionInfo& info)
{
    std::string value;

    for (int i = 0; i < argc_; i++) {
        if (!std::strcmp(info.shortName.c_str(), argv_[i])
            || !std::strcmp(info.longName.c_str(), argv_[i])) {
            value = (i + 1 == argc_) ? argv_[i] : argv_[i + 1];
            break;
        }
    }
    return value;
}

std::string InputOptionsHandler::getNickname()
{
    OptionInfo info = getOption(NICKNAME);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find nickname option");
    return name;
}

std::string InputOptionsHandler::getPassword()
{
    OptionInfo info = getOption(PASSWORD);
    std::string pass = getOptionValue(info);

    if (pass.empty() || pass == info.shortName || pass == info.longName)
        throw std::logic_error("Cannot find password option");
    return pass;
}

std::string InputOptionsHandler::getSessionName()
{
    OptionInfo info = getOption(SESSION_NAME);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find session name option");
    std::cout << name << std::endl;
    return name;
}

short InputOptionsHandler::getServerPort()
{
    OptionInfo info = getOption(SERVER_PORT);
    std::string port = getOptionValue(info);

    if (port.empty() || port == info.shortName || port == info.longName)
        throw std::logic_error("Cannot find port option");
    return std::stoi(port);
}

short InputOptionsHandler::getClientPort()
{
    OptionInfo info = getOption(CLIENT_PORT);
    std::string port = getOptionValue(info);

    if (port.empty() || port == info.shortName || port == info.longName)
        throw std::logic_error("Cannot find port option");
    return std::stoi(port);
}

bool InputOptionsHandler::isCreateSession()
{
    OptionInfo info = getOption(CREATE_SESSION);
    std::string value = getOptionValue(info);

    if (value.size() > 0 && (value == info.longName || value == info.shortName))
        return true;
    return false;
}

bool InputOptionsHandler::isAskingForHelp()
{
    OptionInfo info = getOption(HELP);
    std::string value = getOptionValue(info);

    if (value.size() > 0 && (value == info.longName || value == info.shortName))
        return true;
    return false;
}