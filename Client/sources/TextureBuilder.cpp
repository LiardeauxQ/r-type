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

sf::Texture *TextureBuilder::getTexture(std::string name)
{
    if (m_textures.find(name) == m_textures.end())
        this->createTexture(name);
    return m_textures.at(name);
}

void TextureBuilder::createTexture(const std::string path)
{
    m_textures[path] = new sf::Texture();
    m_textures[path]->loadFromFile(path);
}
