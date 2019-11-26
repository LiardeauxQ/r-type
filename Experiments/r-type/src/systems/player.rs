use amethyst::{
    core::{Transform, SystemDesc},
    derive::SystemDesc,
    core::timing::Time,
    ecs::prelude::{Join, Read, ReadStorage, System, SystemData, World, WriteStorage},
    renderer::{SpriteRender},
    input::{InputHandler, StringBindings},
};

use crate::components::{Player, Direction, Velocity};

#[derive(SystemDesc)]
pub struct PlayerSystem;

impl<'s> System<'s> for PlayerSystem {
    type SystemData = (
        ReadStorage<'s, Velocity>,
        WriteStorage<'s, Player>,
        WriteStorage<'s, SpriteRender>,
        WriteStorage<'s, Transform>,
        Read<'s, InputHandler<StringBindings>>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            velocities,
            mut players,
            mut renders,
            mut transforms,
            input,
        ) = data;

        for (player, velocity, transform, render) in (&mut players, &velocities, &mut transforms, &mut renders).join() {
            update_player_direction(player, &input);
            let movement = match player.direction {
                Direction::Top | Direction::Bottom => input.axis_value("y_movement"),
                Direction::Left | Direction::Right => input.axis_value("x_movement"),
            };
            if let Some(mv_amount) = movement {
                match player.direction {
                    Direction::Top | Direction::Bottom =>
                        transform.prepend_translation_y(velocity.x * mv_amount),
                    Direction::Left | Direction::Right =>
                        transform.prepend_translation_x(velocity.y * mv_amount),
                };
            }
        }
    }
}

fn update_player_direction(player: &mut Player, input: &InputHandler<StringBindings>) {
    if let Some(x_movement) = input.axis_value("x_movement") {
        if x_movement > 0.0 {
            player.direction = Direction::Right;
        } else if x_movement < 0.0 {
            player.direction = Direction::Left;
        }
    }
    if let Some(y_movement) = input.axis_value("y_movement") {
        if y_movement > 0.0 {
            player.direction = Direction::Bottom;
        } else if y_movement < 0.0 {
            player.direction = Direction::Top;
        }
    }
}