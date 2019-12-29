//
// Created by Quentin Liardeaux on 10/11/19.
//

#ifndef BABEL_SERVER_INPUTOPTIONSHANDLER_HPP
#define BABEL_SERVER_INPUTOPTIONSHANDLER_HPP

#include <vector>
#include <tuple>
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>

class InputOptionsHandler {
public:
    InputOptionsHandler(int argc, char **argv);
    ~InputOptionsHandler() = default;

    std::string getNickname() const;
    std::string getPassword() const;
    std::string getSessionName() const;
    std::string getLocalAddress() const;
    std::string getRemoteAddress() const;
    short getClientPort() const;
    short getServerPort() const;
    bool isCreateSession() const;
    bool isAskingForHelp() const;

private:
    enum OptionId {
        CREATE_SESSION,
        SESSION_NAME,
        PASSWORD,
        NICKNAME,
        SERVER_PORT,
        CLIENT_PORT,
        HELP,
        LOCAL_ADDRESS,
        REMOTE_ADDRESS,
    };

    struct OptionInfo {
        OptionId id;
        std::string shortName;
        std::string longName;
        bool hasValue;
    };

    const OptionInfo& getOption(OptionId id) const;
    std::string getOptionValue(const OptionInfo &info) const;

    int argc_;
    char **argv_;

    static std::vector<OptionInfo> options_;
};


#endif //BABEL_SERVER_INPUTOPTIONSHANDLER_HPP
