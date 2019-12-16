//
// Created by nwmqpa on 29/11/2019
//

#pragma once

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <filesystem>
#include <iostream>
#include "Definitions.hpp"

struct Handle {

    explicit Handle(void *handle)
        : ptr(handle)
    {}

    void *ptr;
};

using LibraryHandle = Box<Handle>;

class LibraryException : public std::exception {
public:
    explicit LibraryException(String errMessage)
     : m_error(std::move(errMessage))
    {}

    [[nodiscard]] const char* what() const noexcept final {
        return m_error.c_str();
    }

private:
    const String m_error;
};

struct Library {

    explicit Library(const std::filesystem::path &path);

    ~Library();

    Library(Library&& library) noexcept;
    Library& operator=(Library&& library) noexcept;

    Library(const Library& library) = delete;

    static LibraryHandle loadFilename(const std::filesystem::path &path);

    LibraryHandle m_handle;
    String m_name;
};