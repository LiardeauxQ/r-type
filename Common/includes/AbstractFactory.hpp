//
// Created by nwmqpa
//

#include <tuple>
#include "Definitions.hpp"
#include "IFactorizable.hpp"

template<typename To, typename From>
Box<To> static_unique_pointer_cast(Box<From>&& old){
    To *ptr = dynamic_cast<To *>(old.get());
    if (ptr == nullptr) {
        return Box<To>(nullptr);
    }
    old.release();
    return Box<To>(ptr);
}

template<typename KeyType, typename Hasher>
class AbstractFactory {

    public:
        AbstractFactory() = default;
        ~AbstractFactory() = default;

        template<typename U>
        void register_factorizable() {
            IFactorizable<KeyType> *data = new U();
            KeyType hashedKey = Hasher::hash(data->getKey());
            m_factorizable.push_back(std::make_tuple(hashedKey, data));
        }

        Box<IFactorizable<KeyType>> createWithHash(KeyType key) {
            for (auto tuple : m_factorizable) {
                if (std::get<0>(tuple) == key) {
                    return std::get<1>(tuple)->copy();
                }
            }
            return std::unique_ptr<IFactorizable<KeyType>>(nullptr);
        }

        Box<IFactorizable<KeyType>> create(KeyType key) {
            KeyType hashedKey = Hasher::hash(key);
            return this->createWithHash(hashedKey);
        }
    
    private:
        std::vector<std::tuple<KeyType, IFactorizable<KeyType> *>> m_factorizable;

};
