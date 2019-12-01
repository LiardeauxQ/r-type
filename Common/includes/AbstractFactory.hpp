//
// Created by nwmqpa
//

#pragma once

#include <tuple>
#include <iostream>
#include "Definitions.hpp"
#include "IFactorizable.hpp"


template<typename KeyType, typename Hasher>
class AbstractFactory {

    public:
        AbstractFactory()
        : m_factorizables()
        {}

        ~AbstractFactory() = default;

        template<typename U>
        void registerFactorizable() {
            auto data = std::make_unique<U>();
            registerFactorizableInstance(move(static_unique_pointer_cast<IFactorizable<KeyType>>(move(data))));
        }

        void registerFactorizableInstance(Box<IFactorizable<KeyType>> instance)
        {
            KeyType hashedKey = Hasher::hash(instance->getKey());
            m_factorizables[hashedKey] = move(instance);
        }

        Box<IFactorizable<KeyType>> createWithHash(KeyType key) {
            if (m_factorizables.find(key) != m_factorizables.end()) {
                return m_factorizables.at(key)->copy();
            }
            throw "Factorizable not found";
        }

        Box<IFactorizable<KeyType>> create(KeyType key) {
            KeyType hashedKey = Hasher::hash(key);
            return this->createWithHash(hashedKey);
        }
    
    private:
        Map<KeyType, Box<IFactorizable<KeyType>>> m_factorizables;

};
