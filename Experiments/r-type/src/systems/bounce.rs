use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    ecs::prelude::{Join, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::components::{Velocity};
use crate::rtype::{WIDTH};

#[derive(SystemDesc)]
pub struct BounceSystem;

impl <'s> System<'s> for BounceSystem {
    type SystemData = (
        WriteStorage<'s, Velocity>,
        ReadStorage<'s, Transform>,
    );

    fn run(&mut self, (mut velocities, transforms): Self::SystemData) {
        for (velocity, transform) in (&mut velocities, &transforms).join() {
            let x = transform.translation().x;
            let y = transform.translation().y;

            if x > WIDTH || x < 0.0 {
                velocity.x *= -1.0;
            }
            if y > WIDTH || y < 0.0 {
                velocity.y *= -1.0;
            }
        }
    }
}