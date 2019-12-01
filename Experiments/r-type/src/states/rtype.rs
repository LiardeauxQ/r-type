use amethyst::{
    prelude::*,
    ecs::prelude::{Join}
};

pub const WIDTH: f32 = 500.0;
pub const HEIGHT: f32 = 500.0;

use crate::entities;

pub struct RType;

impl SimpleState for RType {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;

        entities::initialize_player(world);
        entities::initialize_spawners(world);
        entities::initialize_camera(world);
    }
}
