use amethyst::{
    assets::Handle,
    ecs::{Entities, LazyUpdate, ReadExpect},
    core::transform::Transform,
    renderer::{SpriteRender, SpriteSheet},
};

use crate::components::{
    Explosion,
    TimeAnimation,
    TimeAnimationList,
    SheetPosition,
};

pub fn spawn_explosion(entities: &Entities,
                       sprite_sheet: Handle<SpriteSheet>,
                       lazy_update: &ReadExpect<LazyUpdate>,
                       transform: Transform) {
    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet,
        sprite_number: 0,
    };
    let mut animations = TimeAnimationList::default();

    animations.insert("explosion", TimeAnimation::new(SheetPosition::new(0, 5, 0), 750, true));
    animations.run("explosion");
    let explosion_entity = entities.create();
    lazy_update.insert(explosion_entity, Explosion);
    lazy_update.insert(explosion_entity, transform);
    lazy_update.insert(explosion_entity, sprite_render.clone());
    lazy_update.insert(explosion_entity, animations);
}