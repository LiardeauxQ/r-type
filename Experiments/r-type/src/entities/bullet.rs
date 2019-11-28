use amethyst::{
    assets::Handle,
    core::transform::Transform,
    renderer::{SpriteRender, SpriteSheet},
    ecs::{Entities, LazyUpdate, ReadExpect},
};

use crate::components::{Bullet, Velocity};

pub fn spawn_bullet(entities: &Entities,
                    sprite_sheet: Handle<SpriteSheet>,
                    lazy_update: &ReadExpect<LazyUpdate>,
                    transform: &Transform) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };

    let bullet_entity = entities.create();
    lazy_update.insert(bullet_entity, Bullet);
    lazy_update.insert(bullet_entity, Velocity::new(150.0, 0.0));
    lazy_update.insert(bullet_entity, transform.clone());
    lazy_update.insert(bullet_entity, sprite_render.clone());
    //.with(Collidee::default())
    //.with(Collider::default())
}
