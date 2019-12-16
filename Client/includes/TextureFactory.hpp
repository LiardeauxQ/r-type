//
// Crated by nwmqpa
//

#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>

template<typename T>
class TextureFactory {

    public:
        TextureFactory() = default;

        void addTexture(const std::string &key, const std::string &path)
        {
            T texture;
            texture.loadFromFile(path);
            this->m_textures[key] = texture;
        }

        const T &getTexture(const std::string &key) const
        {
            return m_textures.at(key);
        }

    private:
        std::unordered_map<std::string, T> m_textures;

};