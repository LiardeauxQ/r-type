use amethyst::{
    assets::{ProgressCounter},
    prelude::*,
};

use crate::common::{AssetType, SpriteInfo, SpriteSheetList};
use crate::components::{Bullet};
use crate::states::RType;

#[derive(Default)]
pub struct LoadState {
    progress_counter: Option<ProgressCounter>,
}

impl SimpleState for LoadState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;
        let sprite_infos = vec![
            SpriteInfo::new("r-typesheet1.gif", "../resources/player.ron", AssetType::Player),
            SpriteInfo::new("r-typesheet1.gif", "../resources/bullet.ron", AssetType::Bullet),
        ];
        let mut sprite_sheet_list = SpriteSheetList::default();

        self.progress_counter = Some(match sprite_sheet_list.load_from(world, sprite_infos) {
            Ok(counter) => counter,
            _ => ProgressCounter::new(),
        });
        world.insert(sprite_sheet_list);
        world.register::<Bullet>();
    }

    fn update(&mut self, data: &mut StateData<'_, GameData<'_, '_>>) -> SimpleTrans {
        if let Some(ref progress_counter) = self.progress_counter {
            if progress_counter.num_loading() == 0 {
                self.progress_counter = None;
                return Trans::Switch(Box::new(RType));
            }
        }
        Trans::None
    }
}