use amethyst::{
    assets::{AssetStorage, Loader, Handle},
    core::transform::Transform,
    prelude::*,
    renderer::{Camera, ImageFormat, SpriteRender, SpriteSheet, SpriteSheetFormat, Texture},
};

pub const WIDTH: f32 = 150.0;
pub const HEIGHT: f32 = 150.0;

use crate::components::{Velocity, Collidee, Collider, Player, Direction};
use crate::common;
use crate::entities;

pub struct RType;

impl SimpleState for RType {

    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world; 
        let sprite_sheet_handle =
            common::load_sprite_sheet(world,
                                      "../assets/r-typesheet1.gif",
                                      "../resources/r-typesheet1.ron");

        world.register::<Player>();
        entities::initialize_player(world, sprite_sheet_handle);
        entities::initialize_camera(world);
    }
}