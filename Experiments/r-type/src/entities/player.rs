use amethyst::{
    assets::{Handle},
    core::transform::Transform,
    prelude::*,
    renderer::{SpriteRender, SpriteSheet},
};

use crate::components::{Player, Direction, Velocity};
use crate::rtype::{WIDTH, HEIGHT};

pub fn initialize_player(world: &mut World, sprite_sheet: Handle<SpriteSheet>) {
    let mut transform_s1 = Transform::default();

    transform_s1.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 0.0);

    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet.clone(),
        sprite_number: 0,
    };

    world
        .create_entity()
        .with(Player::new(Direction::Right, 10))
        .with(Velocity::new(0.5, 0.5))
        //.with(Collidee::default())
        //.with(Collider::default())
        .with(transform_s1)
        .with(sprite_render.clone())
        .build();
}