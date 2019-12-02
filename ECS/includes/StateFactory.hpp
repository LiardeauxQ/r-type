//
// Created by nwmqpa on 30/11/19
//

//

#include "Definitions.hpp"
#include "AbstractFactory.hpp"
#include "MD5Hasher.hpp"
#include "AbstractState.hpp"
#include "Event.hpp"
#include "ISystem.hpp"
#include <iostream>
#include <tuple>

namespace ecs {

template<typename T>
class ISystem;

template<typename T>
struct StateData;

template<typename T, typename E>
class StateFactory {

    public:
        StateFactory()
        : m_factory()
        {
        }

        template<typename S>
        void registerState();

        template<typename S, typename... Args>
        void registerSystem(const String &name, Args... args);

        template<typename S>
        void registerSystem(const String &name);

        Box<AbstractState<T, E>> queryState(const String &name) {
            return static_unique_pointer_cast<AbstractState<T, E>>(m_factory.create(name));
        }
    
    private:
        AbstractFactory<String, MD5Hasher> m_factory;

};

template<typename T, typename E>
template<typename S>
void StateFactory<T, E>::registerState()
{
    static_assert(is_base_of<AbstractState<T, E>, S>::value, "Should be a base of AbstractState.");
    m_factory.registerFactorizable<S>();
}

template<typename T, typename E>
template<typename S, typename... Args>
void StateFactory<T, E>::registerSystem(const String &name, Args... args)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    AbstractState<T, E> *state = static_cast<AbstractState<T, E> *>(m_factory.getBaseInstance(name).get());
    state->template registerSystem<S>(args...);
}


template<typename T, typename E>
template<typename S>
void StateFactory<T, E>::registerSystem(const String &name)
{
    static_assert(is_base_of<ISystem<StateData<T>>, S>::value, "Should be a base of ISystem.");
    AbstractState<T, E> *state = static_cast<AbstractState<T, E> *>(m_factory.getBaseInstance(name).get());
    state->template registerSystem<S>();
}


}