use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    core::timing::Time,
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::rtype::{Sphere, WIDTH, HEIGHT, CIRCLE_SIZE};

#[derive(SystemDesc)]
pub struct BounceSystem;

impl <'s> System<'s> for BounceSystem {
    type SystemData = (
        WriteStorage<'s, Sphere>,
        ReadStorage<'s, Transform>,
    );

    fn run(&mut self, (mut spheres, transforms): Self::SystemData) {
        for (sphere, transform) in (&mut spheres, &transforms).join() {
            let x = transform.translation().x;
            let y = transform.translation().y;

            if (x > WIDTH || x < 0.0) {
                sphere.velocity[0] *= -1.0;
            }
            if (y > WIDTH || y < 0.0) {
                sphere.velocity[1] *= -1.0;
            }
        }
    }
}