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

class InputOptionsHandler {
public:
    InputOptionsHandler(int argc, char **argv);
    ~InputOptionsHandler() = default;

    std::string& getNickname();
    std::string& getPassword();
    std::string& getSessionName();
    short getPort();
    bool isCreateSession();

private:
    enum OptionId {
        CREATE_SESSION,
        SESSION_NAME,
        PASSWORD,
        NICKNAME,
        PORT,
        HELP,
    };

    struct OptionInfo {
        OptionId id;
        std::string shortName;
        std::string longName;
    };

    OptionInfo getOption(OptionId id);
    std::string getOptionValue(OptionInfo &info);

    int argc_;
    char **argv_;

    static std::vector<OptionInfo> options_;
};


#endif //BABEL_SERVER_INPUTOPTIONSHANDLER_HPP
