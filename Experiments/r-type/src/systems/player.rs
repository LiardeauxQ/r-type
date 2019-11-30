use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
    input::{InputHandler, StringBindings},
    core::timing::Time,
};

use crate::components::{Player, Direction, Velocity};

#[derive(SystemDesc)]
pub struct PlayerSystem;

impl<'s> System<'s> for PlayerSystem {
    type SystemData = (
        ReadStorage<'s, Velocity>,
        ReadStorage<'s, Player>,
        WriteStorage<'s, Direction>,
        WriteStorage<'s, Transform>,
        Read<'s, InputHandler<StringBindings>>,
        Read<'s, Time>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            velocities,
            players,
            mut directions,
            mut transforms,
            input,
            time
        ) = data;

        for (player, direction, velocity, transform) in (&players, &mut directions, &velocities, &mut transforms).join() {
            update_direction(direction, &input);
            let movement = match direction {
                Direction::TOP | Direction::BOTTOM => input.axis_value("y_movement"),
                Direction::LEFT | Direction::RIGHT => input.axis_value("x_movement"),
            };
            if let Some(mv_amount) = movement {
                match direction {
                    Direction::TOP | Direction::BOTTOM =>
                        transform.prepend_translation_y(velocity.x * time.delta_seconds() * mv_amount),
                    Direction::LEFT | Direction::RIGHT =>
                        transform.prepend_translation_x(velocity.y * time.delta_seconds() * mv_amount),
                };
            }
        }
    }
}

fn update_direction(direction: &mut Direction, input: &InputHandler<StringBindings>) {
    if let Some(x_movement) = input.axis_value("x_movement") {
        if x_movement > 0.0 {
            *direction = Direction::RIGHT;
        } else if x_movement < 0.0 {
            *direction = Direction::LEFT;
        }
    }
    if let Some(y_movement) = input.axis_value("y_movement") {
        if y_movement > 0.0 {
            *direction = Direction::BOTTOM;
        } else if y_movement < 0.0 {
            *direction = Direction::TOP;
        }
    }
}