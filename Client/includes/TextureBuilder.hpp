/*
** EPITECH PROJECT, 2019
** TextureBuilder.hpp
** File description:
** TextureBuilder header
*/

#ifndef TEXTUREBUILDER_HPP
	#define TEXTUREBUILDER_HPP

#include <string>
#include <map>
#include <SFML/Graphics/Texture.hpp>

class TextureBuilder {
    public:
        TextureBuilder();
        ~TextureBuilder() = default;
        sf::Texture *getTexture(std::string name);
    private:
        void createTexture(const std::string path);
        std::map<std::string, sf::Texture*> m_textures;
};

#endif /* !TEXTUREBUILDER_HPP */
