use amethyst::{
    assets::Handle,
    ecs::{Entities, LazyUpdate, ReadExpect},
    core::transform::Transform,
    renderer::{SpriteRender, SpriteSheet},
};

use crate::components::{
    Bullet,
    Velocity,
    Collidee,
    Collider,
    Damage,
    Team,
};

pub fn spawn_bullet(entities: &Entities,
                    sprite_sheet: Handle<SpriteSheet>,
                    lazy_update: &ReadExpect<LazyUpdate>,
                    transform: &Transform,
                    team: &Team) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };

    let bullet_entity = entities.create();
    lazy_update.insert(bullet_entity, Bullet);
    lazy_update.insert(bullet_entity, Velocity::new(150.0, 0.0));
    lazy_update.insert(bullet_entity, transform.clone());
    lazy_update.insert(bullet_entity, sprite_render.clone());
    lazy_update.insert(bullet_entity, Damage::new(30));
    lazy_update.insert(bullet_entity, Collidee::default());
    lazy_update.insert(bullet_entity, Collider);
    lazy_update.insert(bullet_entity, Team::new(team.id))
}
