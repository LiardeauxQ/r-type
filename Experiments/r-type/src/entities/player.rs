use amethyst::{
    core::transform::Transform,
    prelude::*,
    renderer::SpriteRender,
    ecs::Entity,
};

use crate::common::{SpriteSheetList};
use crate::components::{
    Direction,
    Player,
    Velocity,
    AttackSpeed,
    Collidee,
    Collider,
    Damage,
    Health,
    Shield,
    Team,
    Movable,
};
use crate::states::{HEIGHT, WIDTH};

pub fn initialize_player(world: &mut World) -> Result<Entity, &'static str> {
    let mut transform_s1 = Transform::default();
    let player_sheet = world
        .fetch::<SpriteSheetList>()
        .get("player")
        .ok_or("Cannot fetch sprite sheet")?;
    let sprite_render = SpriteRender {
        sprite_sheet: player_sheet.clone(),
        sprite_number: 0,
    };

    transform_s1.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 0.0);
    Ok(world
        .create_entity()
        .with(Player::new(33.0, 17.0))
        .with(Direction::RIGHT)
        .with(Velocity::new(70.0, 70.0))
        .with(transform_s1)
        .with(sprite_render.clone())
        .with(AttackSpeed::new(240))
        .with(Collidee::default())
        .with(Collider)
        .with(Damage::new(300))
        .with(Health::new(400, 400))
        .with(Shield::new(100, 100))
        .with(Team::new(1))
        .with(Movable{is_movable: true})
        .build())
}
