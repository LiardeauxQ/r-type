use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    core::timing::Time,
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::rtype::{Sphere, WIDTH, HEIGHT, CIRCLE_SIZE};

#[derive(SystemDesc)]
pub struct MovementSystem;

impl<'s> System<'s> for MovementSystem {
    type SystemData = (
        ReadStorage<'s, Sphere>,
        WriteStorage<'s, Transform>,
        Read<'s, Time>,
    );

    fn run(&mut self, (spheres, mut locals, time): Self::SystemData) {
        for (sphere, local) in (&spheres, &mut locals).join() {
            local.prepend_translation_x(sphere.velocity[0] * time.delta_seconds());
            local.prepend_translation_y(sphere.velocity[1] * time.delta_seconds());
        }
    }
}
