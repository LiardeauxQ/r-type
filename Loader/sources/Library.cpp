//
// Created by nwmqpa on 28/11/2019
//

#include "Library.hpp"

LibraryHandle Library::loadFilename(const std::filesystem::path &path)
{
    if (std::filesystem::exists(path)) {
        if (std::filesystem::is_regular_file(path)) {
            #ifdef WIN32
                auto handle = LoadLibrary(TEXT(path.c_str()));

                if (!handle)
                    throw LibraryException(String("Error opening ") + path.c_str() + String(": ") + "Windows");
            #else
                auto handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!handle)
                    throw LibraryException(String("Error opening ") + path.c_str() + String(": ") + dlerror());
            #endif
            return std::make_unique<Handle>(handle);
        } else {
            throw LibraryException(String("Path is not a file: ") + path.c_str());
        }
    } else {
        throw LibraryException(String("Path does not exists: ") + path.c_str());
    }
}


Library::~Library()
{
    if (m_handle.get()) {
        #ifdef WIN32
            FreeLibrary(m_handle->ptr);
        #else
            dlclose(m_handle->ptr);
        #endif
    }
}

Library::Library(const std::filesystem::path &path)
    : m_handle(Library::loadFilename(path))
    , m_name(path.filename())
{
}

Library::Library(Library&& library) noexcept
    : m_handle(move(library.m_handle))
    , m_name(move(library.m_name))
{
}

Library& Library::operator=(Library&& library) noexcept
{
    m_handle = move(library.m_handle);
    m_name = move(library.m_name);
    return *this;
}
