//
// Created by Quentin Liardeaux on 12/24/19.
//

#ifndef R_TYPE_IDPROVIDER_HPP
#define R_TYPE_IDPROVIDER_HPP

#include <memory>

class IdProvider {
public:
    IdProvider() = default;
    ~IdProvider() = default;

    static std::unique_ptr<IdProvider>& instance();

    size_t getNextId() { return m_id++; }
private:
    IdProvider(const IdProvider& provider);

    IdProvider &operator=(const IdProvider& provider);

    size_t m_id;
};

#endif //R_TYPE_IDPROVIDER_HPP
