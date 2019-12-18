//
// Created by Quentin Liardeaux on 10/11/19.
//

#include "InputOptionsHandler.hpp"

std::vector<InputOptionsHandler::OptionInfo> InputOptionsHandler::options_ = {
    OptionInfo { CREATE_SESSION, "-c", "--createSession" },
    OptionInfo { SESSION_NAME, "-s", "--name" },
    OptionInfo { PASSWORD, "-w", "--password" },
    OptionInfo { NICKNAME, "-n", "--nickname" },
    OptionInfo { PORT, "-p", "--port" },
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

std::string& InputOptionsHandler::getNickname()
{
    OptionInfo info = getOption(NICKNAME);
    std::string name = getOptionValue(info);

    if (name.size() == 0 || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find nickname option");
    return name;
}

std::string& InputOptionsHandler::getPassword()
{
    OptionInfo info = getOption(PASSWORD);
    std::string pass = getOptionValue(info);

    if (pass.size() == 0 || pass == info.shortName || pass == info.longName)
        throw std::logic_error("Cannot find password option");
    return pass;
}

std::string& InputOptionsHandler::getSessionName()
{
    OptionInfo info = getOption(SESSION_NAME);
    std::string name = getOptionValue(info);

    if (name.size() == 0 || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find session name option");
    return name;
}

short InputOptionsHandler::getPort()
{
    OptionInfo info = getOption(PORT);
    std::string port = getOptionValue(info);

    if (port.size() == 0 || port == info.shortName || port == info.longName)
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