/*
** EPITECH PROJECT, 2019
** test.c
** File description:
** Criterion
*/

#include <criterion/criterion.h>
#include "ParseJSONSprite.hpp"

#include <stdlib.h>

#include <iostream>

Test(ParseJSONSprite, well_formated_file) {
    auto spriteFiles = ParseJSONSprite::parse("files/well_formated_sprite_file.json");

    cr_assert_str_eq(spriteFiles[0]->getFilename().c_str(), "r-typesheet19.gif");
    cr_assert_str_eq(spriteFiles[0]->getName().c_str(), "monster 1");
    auto rightChilds = spriteFiles[0]->getChildWithPosition(SpritePosition::RIGHT);
    cr_assert_eq(rightChilds->getFrameForAnimationAtPos(0).m_x, 1);
    cr_assert_eq(rightChilds->getFrameForAnimationAtPos(0).m_y, 2);
    cr_assert_eq(rightChilds->getFrameForAnimationAtPos(0).m_width, 3);
    cr_assert_eq(rightChilds->getFrameForAnimationAtPos(0).m_height, 4);
}

Test(ParseJSONSprite, well_formated_file2) {
    auto spriteFiles = ParseJSONSprite::parse("files/well_formated_sprite_file.json");

    cr_assert_str_eq(spriteFiles[1]->getFilename().c_str(), "r-typesheet20.gif");
    cr_assert_str_eq(spriteFiles[1]->getName().c_str(), "monster 2");
}

Test(ParserJSONSprite, wrong_json_file) {
    cr_assert_throw(ParseJSONSprite::parse("files/wrong_file.json"), ParseError);
}

Test(ParserJSONSprite, bad_attributes_file) {
    auto spriteFiles = ParseJSONSprite::parse("files/bad_attributes.json");

    cr_assert_eq(spriteFiles.size(), 0);
}

Test(ParserJSONSprite, empty_arguments) {
    auto spriteFiles = ParseJSONSprite::parse("files/empty_arguments.json");

    cr_assert_eq(spriteFiles.size(), 2);
    cr_assert_str_eq(spriteFiles[1]->getFilename().c_str(), "r-typesheet20.gif");
}
