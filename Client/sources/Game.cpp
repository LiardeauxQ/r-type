/*
** EPITECH PROJECT, 2019
** Game.cpp
** File description:
** Game implementation
*/

#include <iostream>
#include <SFML/System/Clock.hpp>
#include "Game.hpp"

Game::Game(int ac, char **av)
    : m_input(ac, av)
    , m_dispatcher(nullptr)
    , m_textureBuilder()
    , m_stateBuilder()
    , m_states()
    , m_isRunning(false)
    , m_window(nullptr)
    , m_event()
    , m_deltaTime(0.0)
{
}

Game::~Game()
{
    delete m_dispatcher;
    while (!m_states.empty()) {
        delete m_states.top();
    }
}

void Game::run()
{
    if (m_input.isAskingForHelp()) {
        displayHelp();
        return;
    }
    try {
        m_dispatcher = new ClientPacketDispatcher(8678, 0, "0.0.0.0");
        m_dispatcher->start();
        gameConnection();
        m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
        m_window->setVerticalSyncEnabled( true );
        m_states.push(m_stateBuilder.createState(States::GAME, m_textureBuilder));
        m_states.top()->linkWindow(m_window, &m_deltaTime);
        m_isRunning = true;
        this->loop();
    } catch (const char *s) {
        std::cout << s << std::endl;
    }
}

void Game::handleTransition(Transition transition)
{
    switch (transition) {
        case Transition::QUIT:
            m_window->close();
            break;
        default:
            break;
    }
}

void Game::loop()
{
    sf::Clock clock;
    while (m_isRunning && m_window->isOpen()) {
        m_window->clear();
        m_deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        handleTransition(m_states.top()->handleEvent(m_event));
        m_states.top()->update();
        m_window->display();
        checkServerPackets();
    }
}

void Game::gameConnection()
{
    auto sessionName = m_input.getSessionName();
    auto password = m_input.getPassword();
    auto nickname = m_input.getNickname();
    std::cout << "connect" << std::endl;
    if (m_input.isCreateSession())
        m_dispatcher->sendCreateGame(sessionName, password, nickname);
    else
        m_dispatcher->sendJoinGame(sessionName, password, nickname);
}

void Game::checkServerPackets()
{
    auto responses = m_dispatcher->getServerResponses();

    while (!responses.empty()) {
        auto response = responses.front().get();

        handlePacket(*response);
        responses.pop();
    }
}

void Game::handlePacket(const Message& msg)
{
    switch (msg.getId()) {
        case ROOM_INFO:
            roomInfo(dynamic_cast<const RoomInfo&>(msg));
            break;
        case SUCCESS_CONNECT:
            successConnection(dynamic_cast<const SuccessConnect&>(msg));
            break;
        case ERROR:
            break;
        case ROOM_PLAYER_JOIN:
            playerHasJoin(dynamic_cast<const RoomPlayerJoin&>(msg));
            break;
        case ROOM_PLAYER_QUIT:
            playerHasQuit(dynamic_cast<const RoomPlayerQuit&>(msg));
            break;
        case ROOM_PLAYER_STATE:
            getPlayerState(dynamic_cast<const RoomPlayerState&>(msg));
            break;
        case GAME_START:
            break;
        default:
            break;
    }
}

void Game::roomInfo(const RoomInfo& msg)
{

}

void Game::successConnection(const SuccessConnect& msg)
{
}

void Game::playerHasJoin(const RoomPlayerJoin &msg) {}
void Game::playerHasQuit(const RoomPlayerQuit &msg) {}
void Game::getPlayerState(const RoomPlayerState &msg) {}

void Game::displayHelp()
{
    std::cout << "R-TYPE help:" << std::endl;
    std::cout << "\t-c\t --createSession" << std::endl;
    std::cout << "\t-s\t --name $NAME" << std::endl;
    std::cout << "\t-w\t --password $PASSWORD" << std::endl;
    std::cout << "\t-n\t --nickname $NICKNAME" << std::endl;
    std::cout << "\t-p1\t --serverPort $PORT" << std::endl;
    std::cout << "\t-p2\t --clientPort $PORT" << std::endl;
    std::cout << "\t-h\t --help" << std::endl;
}
