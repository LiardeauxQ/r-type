use amethyst::{
    core::timing::Time,
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    renderer::{SpriteRender},
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage, Entities},
};

use crate::components::{
    Direction,
};

use crate::states::WIDTH;

#[derive(SystemDesc)]
pub struct DestroySystem;

impl<'s> System<'s> for DestroySystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, Direction>,
        ReadStorage<'s, Transform>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            directions,
            transforms,
        ) = data;

        for (entity, transform, direction) in (&entities, &transforms, &directions).join() {
            if *direction == Direction::LEFT && transform.translation().x < 0.0 {
                 entities.delete(entity);
            } else if *direction == Direction::RIGHT && transform.translation().x > WIDTH {
                entities.delete(entity);
            }
        }
    }
}