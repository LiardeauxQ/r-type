use amethyst::{
    assets::Handle,
    ecs::{Entities, LazyUpdate, ReadExpect},
    core::transform::Transform,
    prelude::*,
    renderer::{SpriteRender, SpriteSheet},
};

use crate::components::{
    Spawner,
    AttackSpeed,
    Enemy,
    Velocity,
    Collidee,
    Collider,
    Damage,
    Health,
    Team,
    Direction,
    Movable,
};
use crate::states::{WIDTH, HEIGHT};

const SPAWN_SPEED: u64= 1200;

pub fn initialize_spawners(world: &mut World) -> Result<(), &'static str> {
    let mut transform_s1 = Transform::default();
    let mut transform_s2 = Transform::default();

    transform_s1.set_translation_xyz(WIDTH, HEIGHT * 0.25, 0.0);
    world
        .create_entity()
        .with(Spawner)
        .with(transform_s1)
        .with(AttackSpeed::new(SPAWN_SPEED))
        .with(Team::new(2))
        .build();
    transform_s2.set_translation_xyz(WIDTH, HEIGHT * 0.75, 0.0);
    world
        .create_entity()
        .with(Spawner)
        .with(transform_s2)
        .with(AttackSpeed::new(SPAWN_SPEED))
        .with(Team::new(2))
        .build();
    Ok(())
}

pub fn spawn_enemy(entities: &Entities,
                    sprite_sheet: Handle<SpriteSheet>,
                    lazy_update: &ReadExpect<LazyUpdate>,
                    transform: &Transform,
                    team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };

    let enemy_entity = entities.create();
    lazy_update.insert(enemy_entity, Enemy);
    lazy_update.insert(enemy_entity, Velocity::new(-100.0, 0.0));
    lazy_update.insert(enemy_entity, transform.clone());
    lazy_update.insert(enemy_entity, sprite_render.clone());
    lazy_update.insert(enemy_entity, Collidee::default());
    lazy_update.insert(enemy_entity, Collider);
    lazy_update.insert(enemy_entity, Damage::new(300));
    lazy_update.insert(enemy_entity, Health::new(400, 400));
    lazy_update.insert(enemy_entity, Team::new(team.id));
    lazy_update.insert(enemy_entity, Direction::LEFT);
    lazy_update.insert(enemy_entity, Movable{is_movable: true});
}