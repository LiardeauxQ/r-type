//
// Created by nwmqpa on 29/11/2019
//

#pragma once

#include <dlfcn.h>
#include "Definitions.hpp"
#include "Library.hpp"

class LoadingException : public std::exception {
public:
    LoadingException(String errMessage)
     : m_error(std::move(errMessage))
    {}

    const char* what() const noexcept {
        return m_error.c_str();
    }

private:
    const String m_error;
};


class Loader {
public:
    Loader() = default;

    Loader(Loader&& loader) noexcept;
    Loader& operator=(Loader&& loader) noexcept;

    Loader(const Loader& loader) = delete;

    void registerLibrary(Library library);

    template<typename T, typename... Args>
    Vec<T> useSymbol(const String &name, Args... args) {
        Vec<T> results;
        for (const auto& library : m_libraries) {
            T (*handle)(Args...) = reinterpret_cast<T (*)(Args...)>(dlsym(library.m_handle->ptr, name.c_str()));
            if (handle == nullptr) {
                throw LoadingException(String("Error reading ") + name + String(" on ") + library.m_name + String(": ") + dlerror());
            }
            results.push_back(handle(args...));
        }
        return results;
    }

private:
    Vec<Library> m_libraries;
};
