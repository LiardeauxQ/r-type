//
// Created by nwmqpa on 29/11/2019
//

#pragma once

#include <filesystem>
#include "Definitions.hpp"

struct Handle {

    Handle(void *handle)
    : m_handle(handle)
    {}

    void *m_handle;
};

using LibraryHandle = Box<Handle>;

class LibraryException : public std::exception {
public:
    LibraryException(String errMessage)
     : m_error(std::move(errMessage))
    {}

    const char* what() const noexcept {
        return m_error.c_str();
    }

private:
    const String m_error;
};

class Library {

public:
    explicit Library(const std::filesystem::path &path);

    ~Library();

    Library(Library&& library) noexcept;
    Library& operator=(Library&& library) noexcept;

    Library(const Library& library) = delete;

    static LibraryHandle loadFilename(const std::filesystem::path &path);

private:
    LibraryHandle m_handle;
    String m_name;
};