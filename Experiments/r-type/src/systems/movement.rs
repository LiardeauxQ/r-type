use amethyst::{
    core::timing::Time,
    core::{SystemDesc, Transform},
    derive::SystemDesc,
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
};

use crate::components::{Player, Collidee, Collider, Velocity, Movable};

#[derive(SystemDesc)]
pub struct MovementSystem;

impl<'s> System<'s> for MovementSystem {
    type SystemData = (
        ReadStorage<'s, Player>,
        ReadStorage<'s, Velocity>,
        ReadStorage<'s, Movable>,
        WriteStorage<'s, Transform>,
        Read<'s, Time>,
    );

    fn run(&mut self, (players, velocities, movables, mut transforms, time): Self::SystemData) {
        for (velocity, movable, transform, ()) in (&velocities, &movables, &mut transforms, !&players).join() {
            if !movable.is_movable {
                continue;
            }
            transform.prepend_translation_x(velocity.x * time.delta_seconds());
            transform.prepend_translation_y(velocity.y * time.delta_seconds());
        }
    }
}

#[derive(SystemDesc)]
pub struct UpdateVelocitySystem;

impl<'s> System<'s> for UpdateVelocitySystem {
    type SystemData = (
        WriteStorage<'s, Velocity>,
        WriteStorage<'s, Collidee>,
        WriteStorage<'s, Collider>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (mut velocities, mut collidees, mut colliders) = data;

        for (velocity, collider, collidee) in
            (&mut velocities, &mut collidees, &mut colliders).join()
        {
            /*if collidee.x_collision || collider.x_collision {
                velocity.x *= -1.0;
                collidee.x_collision = false;
                collider.x_collision = false;
            }
            if collidee.y_collision || collider.y_collision {
                velocity.y *= -1.0;
                collidee.y_collision = false;
                collider.y_collision = false;
            }*/
        }
    }
}
