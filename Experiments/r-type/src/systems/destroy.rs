use amethyst::{
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{Join, ReadStorage, System, SystemData, World, Entities},
};

use crate::components::{
    Direction,
    TimeAnimationList,
    DestroyableAnimation,
};

use crate::states::WIDTH;

#[derive(SystemDesc)]
pub struct DirectionDestroySystem;

impl<'s> System<'s> for DirectionDestroySystem {
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

#[derive(SystemDesc)]
pub struct AnimationDestroySystem;

impl<'s> System<'s> for AnimationDestroySystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, DestroyableAnimation>,
        ReadStorage<'s, TimeAnimationList>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            destroyables,
            animations,
        ) = data;

        for (entity, destroyable, animation) in (&entities, &destroyables, &animations).join() {
            println!("{:?}", animation.is_animation_left());
            if animation.is_animation_left() {
                entities.delete(entity);
            }
        }
    }
}