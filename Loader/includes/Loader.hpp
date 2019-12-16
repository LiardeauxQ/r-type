//
// Created by nwmqpa on 29/11/2019
//

#pragma once

#include "Definitions.hpp"
#include "Library.hpp"

class LoadingException : public std::exception {
public:
    explicit LoadingException(String errMessage)
        : m_error(std::move(errMessage))
    {}

    [[nodiscard]] const char* what() const noexcept final {
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
#ifdef WIN32
            auto handle = reinterpret_cast<T (*)(Args...)>(GetProcAddress(library.m_handle->ptr, name.c_str()));
#else
            auto handle = reinterpret_cast<T (*)(Args...)>(dlsym(library.m_handle->ptr, name.c_str()));
#endif /* WIN32 */
            if (!handle)
                throw LoadingException(String("Error reading ") + name + String(" on ") + library.m_name + String(": ") + dlerror());
            results.push_back(handle(args...));
        }
        return results;
    }

private:
    Vec<Library> m_libraries;
};
