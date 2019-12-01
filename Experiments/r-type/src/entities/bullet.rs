use amethyst::{
    assets::Handle,
    ecs::{Entities, LazyUpdate, ReadExpect},
    core::transform::Transform,
    renderer::{SpriteRender, SpriteSheet},
};

use crate::components::{Bullet, Velocity, Collidee, Collider, Damage, Team, Health, TimeAnimation, TimeAnimationList, SheetPosition, Direction, Movable};

pub fn spawn_bullet(entities: &Entities,
                    sprite_sheet: Handle<SpriteSheet>,
                    lazy_update: &ReadExpect<LazyUpdate>,
                    transform: Transform,
                    team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
    let mut animations = TimeAnimationList::default();

    animations.insert("shoot", TimeAnimation::new(SheetPosition::new(8, 10, 8), 250, false));
    animations.run("shoot");
    let bullet_entity = entities.create();
    lazy_update.insert(bullet_entity, Bullet);
    lazy_update.insert(bullet_entity, Velocity::new(150.0, 0.0));
    lazy_update.insert(bullet_entity, transform);
    lazy_update.insert(bullet_entity, sprite_render.clone());
    lazy_update.insert(bullet_entity, Damage::new(230));
    lazy_update.insert(bullet_entity, Health::new(100, 100));
    lazy_update.insert(bullet_entity, Collidee::default());
    lazy_update.insert(bullet_entity, Collider);
    lazy_update.insert(bullet_entity, Team::new(team.id));
    lazy_update.insert(bullet_entity, animations);
    lazy_update.insert(bullet_entity, Direction::RIGHT);
    lazy_update.insert(bullet_entity, Movable{is_movable: true });
}