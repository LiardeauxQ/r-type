/*
** EPITECH PROJECT, 2019
** TextureBuilder.cpp
** File description:
** TextureBuilder implementation
*/

#include <iostream>
#include "TextureBuilder.hpp"

TextureBuilder::TextureBuilder()
    : m_textures()
{}

sf::Texture *TextureBuilder::getTexture(const std::string &name)
{
    return m_textures.at(name);
}

void TextureBuilder::createTexture(const std::string &path, const std::string &name)
{
    m_textures[name] = new sf::Texture();
    m_textures[name]->loadFromFile(path);
}
