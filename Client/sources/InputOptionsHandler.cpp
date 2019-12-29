//
// Created by Quentin Liardeaux on 10/11/19.
//

#include "InputOptionsHandler.hpp"

std::vector<InputOptionsHandler::OptionInfo> InputOptionsHandler::options_ = {
    OptionInfo { CREATE_SESSION, "-c", "--create-session", false },
    OptionInfo { SESSION_NAME, "-s", "--name", true },
    OptionInfo { PASSWORD, "-w", "--password", true },
    OptionInfo { NICKNAME, "-n", "--nickname", true },
    OptionInfo { SERVER_PORT, "-p1", "--server-port", true },
    OptionInfo { CLIENT_PORT, "-p2", "--client-port", true },
    OptionInfo { LOCAL_ADDRESS, "-l", "--local-address", true },
    OptionInfo { REMOTE_ADDRESS, "-r", "--remote-address", true },
    OptionInfo { HELP, "-h", "--help", false },
};

InputOptionsHandler::InputOptionsHandler(int argc, char** argv)
    : argc_(argc)
    , argv_(argv)
{
}

const InputOptionsHandler::OptionInfo& InputOptionsHandler::getOption(OptionId id) const
{
    for (auto &option : options_) {
        if (option.id == id) {
            return option;
        }
    }
    return OptionInfo {};
}

std::string InputOptionsHandler::getOptionValue(const OptionInfo& info) const
{
    std::string value;

    for (int i = 0; i < argc_; i++) {
        if (!std::strcmp(info.shortName.c_str(), argv_[i])
            || !std::strcmp(info.longName.c_str(), argv_[i])) {
            value = (!info.hasValue) ? argv_[i] : argv_[i + 1];
            break;
        }
    }
    return value;
}

std::string InputOptionsHandler::getNickname() const
{
    OptionInfo info = getOption(NICKNAME);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find nickname option");
    return name;
}

std::string InputOptionsHandler::getPassword() const
{
    OptionInfo info = getOption(PASSWORD);
    std::string pass = getOptionValue(info);

    if (pass.empty() || pass == info.shortName || pass == info.longName)
        throw std::logic_error("Cannot find password option");
    return pass;
}

std::string InputOptionsHandler::getSessionName() const
{
    OptionInfo info = getOption(SESSION_NAME);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find session name option");
    return name;
}

std::string InputOptionsHandler::getLocalAddress() const
{
    OptionInfo info = getOption(LOCAL_ADDRESS);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find local address option");
    return name;
}

std::string InputOptionsHandler::getRemoteAddress() const
{
    OptionInfo info = getOption(REMOTE_ADDRESS);
    std::string name = getOptionValue(info);

    if (name.empty() || name == info.shortName || name == info.longName)
        throw std::logic_error("Cannot find remote address option");
    return name;
}

short InputOptionsHandler::getServerPort() const
{
    OptionInfo info = getOption(SERVER_PORT);
    std::string port = getOptionValue(info);

    if (port.empty() || port == info.shortName || port == info.longName)
        throw std::logic_error("Cannot find port option");
    return static_cast<short>(std::stoi(port));
}

short InputOptionsHandler::getClientPort() const
{
    OptionInfo info = getOption(CLIENT_PORT);
    std::string port = getOptionValue(info);

    if (port.empty() || port == info.shortName || port == info.longName)
        throw std::logic_error("Cannot find port option");
    return static_cast<short>(std::stoi(port));
}

bool InputOptionsHandler::isCreateSession() const
{
    OptionInfo info = getOption(CREATE_SESSION);
    std::string value = getOptionValue(info);

    if (value.size() > 0 && (value == info.longName || value == info.shortName))
        return true;
    return false;
}

bool InputOptionsHandler::isAskingForHelp() const
{
    OptionInfo info = getOption(HELP);
    std::string value = getOptionValue(info);

    if (value.size() > 0 && (value == info.longName || value == info.shortName))
        return true;
    return false;
}