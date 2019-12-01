use amethyst::{
    assets::Handle,
    ecs::{Entities, Entity, LazyUpdate, ReadExpect},
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
    TimeAnimation,
};
use crate::common::{
    SpriteSheetList,
};
use crate::states::{WIDTH, HEIGHT};

const SPAWN_SPEED: u64= 1200;

pub fn initialize_spawners(world: &mut World) -> Result<Vec<Entity>, &'static str> {
    let mut transform_s1 = Transform::default();
    let mut transform_s2 = Transform::default();
    let mut transform_s3 = Transform::default();
    let mut entites = Vec::new();

    transform_s1.set_translation_xyz(WIDTH, HEIGHT * 0.25, 0.0);
    entites.push(world
        .create_entity()
        .with(Spawner)
        .with(transform_s1)
        .with(AttackSpeed::new(SPAWN_SPEED))
        .with(Team::new(2))
        .build());
    transform_s2.set_translation_xyz(WIDTH, HEIGHT * 0.5, 0.0);
    entites.push(world
        .create_entity()
        .with(Spawner)
        .with(transform_s2)
        .with(AttackSpeed::new(SPAWN_SPEED))
        .with(Team::new(2))
        .build());
    transform_s3.set_translation_xyz(WIDTH, HEIGHT * 0.75, 0.0);
    entites.push(world
        .create_entity()
        .with(Spawner)
        .with(transform_s3)
        .with(AttackSpeed::new(SPAWN_SPEED))
        .with(Team::new(2))
        .build());
    Ok(entites)
}

fn choose_attack_pattern() -> AttackPattern {
    let patterns: [AttackPattern; 5] = [
        AttackPattern::new(AttackPattern::compute_on_x, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_cos, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_sin, 50.0, 50.0),
        AttackPattern::new(AttackPattern::compute_ascending_slope, WIDTH, 50.0),
        AttackPattern::new(AttackPattern::compute_descending_slope, WIDTH, 50.0),
    ];

    patterns[rand::random::<usize>() % patterns.len()]
}

fn spawn_robot(entities: &Entities,
               sprite_sheet: Handle<SpriteSheet>,
               lazy_update: &ReadExpect<LazyUpdate>,
               transform: &Transform,
               team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
    let mut animations = TimeAnimationList::default();

    animations.insert("moving", TimeAnimation::new(SheetPosition::new(0, 2, 0), 200, true));
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
    lazy_update.insert(enemy_entity, choose_attack_pattern());
}

fn spawn_super_robot(entities: &Entities,
                     sprite_sheet: Handle<SpriteSheet>,
                     lazy_update: &ReadExpect<LazyUpdate>,
                     transform: &Transform,
                     team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
    let mut animations = TimeAnimationList::default();

    animations.insert("moving", TimeAnimation::new(SheetPosition::new(0, 4, 0), 700, true));
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
    lazy_update.insert(enemy_entity, choose_attack_pattern());
}

fn spawn_ship(entities: &Entities,
              sprite_sheet: Handle<SpriteSheet>,
              lazy_update: &ReadExpect<LazyUpdate>,
              transform: &Transform,
              team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
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
    lazy_update.insert(enemy_entity, choose_attack_pattern());
}

fn spawn_bug(entities: &Entities,
             sprite_sheet: Handle<SpriteSheet>,
             lazy_update: &ReadExpect<LazyUpdate>,
             transform: &Transform,
             team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
    let mut animations = TimeAnimationList::default();

    animations.insert("moving", TimeAnimation::new(SheetPosition::new(0, 3, 0), 500, true));
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
    lazy_update.insert(enemy_entity, choose_attack_pattern());
}

const ENEMIES: [(&str, fn(&Entities, Handle<SpriteSheet>, &ReadExpect<LazyUpdate>, &Transform, &Team)); 4] = [
    ("enemy11", spawn_robot),
    ("enemy14", spawn_super_robot),
    ("enemy16", spawn_bug),
    ("enemy5", spawn_ship)
];

pub fn spawn_enemy(entities: &Entities,
                    sprite_sheet_list: &SpriteSheetList,
                    lazy_update: &ReadExpect<LazyUpdate>,
                    transform: &Transform,
                    team: &Team) -> bool {
    let max_enemy = rand::random::<usize>() % ENEMIES.len();

    if let Some(sprite_sheet) = sprite_sheet_list.get(ENEMIES[max_enemy].0)
    {
        (ENEMIES[max_enemy].1)(&entities, sprite_sheet.clone(), &lazy_update, &transform, &team);
        return true;
    }
    false
}