//
// Created by nwmqpa on 29/11/2019
//

#include "Loader.hpp"

Loader::Loader(Loader&& loader) noexcept
    : m_libraries(move(loader.m_libraries))
{
}

Loader& Loader::operator=(Loader&& loader) noexcept
{
    this->m_libraries = move(loader.m_libraries);
    return *this;
}

void Loader::registerLibrary(Library library)
{
    m_libraries.push_back(std::move(library));
}