//
// Created by Quentin Liardeaux on 12/24/19.
//

#include "IdProvider.hpp"

static std::unique_ptr<IdProvider> provider = nullptr;

std::unique_ptr<IdProvider>& IdProvider::instance() {
    if (provider == nullptr)
        provider = std::make_unique<IdProvider>();
    return provider;
}