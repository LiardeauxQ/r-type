use amethyst::prelude::*;

pub const WIDTH: f32 = 150.0;
pub const HEIGHT: f32 = 150.0;

use crate::common::{AssetType, SpriteInfo, SpriteSheetList};
use crate::entities;

pub struct RType;

impl SimpleState for RType {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;
        let sprite_infos = vec![
            SpriteInfo::new("r-typesheet1.gif", "../resources/player.ron", AssetType::Player),
            SpriteInfo::new("r-typesheet1.gif", "../resources/bullet.ron", AssetType::Bullet),
        ];
        let mut sprite_sheet_list = SpriteSheetList::default();

        sprite_sheet_list.load_from(world, sprite_infos);
        world.insert(sprite_sheet_list);
        entities::initialize_player(world);
        entities::initialize_camera(world);
    }
}
