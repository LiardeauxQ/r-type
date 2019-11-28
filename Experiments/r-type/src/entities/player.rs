use amethyst::{core::transform::Transform, prelude::*, renderer::SpriteRender};

use crate::common::{AssetType, SpriteSheetList};
use crate::components::{Direction, Player, Velocity, AttackSpeed};
use crate::states::{HEIGHT, WIDTH};

pub fn initialize_player(world: &mut World) -> Result<(), &'static str> {
    let mut transform_s1 = Transform::default();
    println!("Init player");
    let player_sheet = world
        .fetch::<SpriteSheetList>()
        .get(AssetType::Player)
        .ok_or("Cannot fetch sprite sheet")?;
    let sprite_render = SpriteRender {
        sprite_sheet: player_sheet.clone(),
        sprite_number: 0,
    };

    transform_s1.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 0.0);
    world
        .create_entity()
        .with(Player::new(Direction::Right, 10))
        .with(Velocity::new(70.0, 70.0))
        //.with(Collidee::default())
        //.with(Collider::default())
        .with(transform_s1)
        .with(sprite_render.clone())
        .with(AttackSpeed::new(1))
        .build();
    Ok(())
}
