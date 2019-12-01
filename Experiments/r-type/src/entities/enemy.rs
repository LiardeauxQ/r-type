use amethyst::{
    assets::Handle,
    ecs::{Entities, LazyUpdate, ReadExpect},
    core::transform::Transform,
    prelude::*,
    renderer::{SpriteRender, SpriteSheet},
};

use rand::random;

use crate::components::{
    Spawner,
    AttackSpeed,
    AttackPattern,
    Enemy,
    Velocity,
    Collidee,
    Collider,
    Damage,
    Health,
    Team,
    Direction,
    Movable,
    TimeAnimationList,
    SheetPosition,
    TimeAnimation
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
    let patterns: [AttackPattern; 5] = [
        AttackPattern::new(AttackPattern::compute_on_x, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_cos, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_sin, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_ascending_slope, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_descending_slope, 50.0, 50.0),
    ];
    let mut animations = TimeAnimationList::default();

    animations.insert("moving", TimeAnimation::new(SheetPosition::new(0, 7, 0), 1000, true));
    animations.run("moving");
    let enemy_entity = entities.create();
    lazy_update.insert(enemy_entity, Enemy);
    lazy_update.insert(enemy_entity, Velocity::new(-100.0, 0.0));
    lazy_update.insert(enemy_entity, transform.clone());
    lazy_update.insert(enemy_entity, sprite_render);
    lazy_update.insert(enemy_entity, Collidee::default());
    lazy_update.insert(enemy_entity, Collider);
    lazy_update.insert(enemy_entity, Damage::new(300));
    lazy_update.insert(enemy_entity, Health::new(400, 400));
    lazy_update.insert(enemy_entity, Team::new(team.id));
    lazy_update.insert(enemy_entity, Direction::LEFT);
    lazy_update.insert(enemy_entity, Movable{is_movable: true});
    lazy_update.insert(enemy_entity, animations);
    lazy_update.insert(enemy_entity, patterns[rand::random::<usize>() % patterns.len()]);
}