use amethyst::{
    ecs::prelude::Entity,
    ui::{UiCreator, UiLoader, UiPrefab},
    assets::{ProgressCounter, Completion, Handle},
    prelude::*,
};

use crate::common::{SpriteInfo, SpriteSheetList};
use crate::components::{Bullet, Enemy, Shield};
use crate::states::MenuState;

#[derive(Default)]
pub struct LoadState {
    ui_counter: ProgressCounter,
    sheet_counter: Option<ProgressCounter>,
    load_ui: Option<Entity>,
    menu_ui: Option<Handle<UiPrefab>>,
    game_ui: Option<Handle<UiPrefab>>,
    pause_ui: Option<Handle<UiPrefab>>,
}

impl SimpleState for LoadState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;
        let sprite_infos = vec![
            SpriteInfo::new("r-typesheet1.gif", "../resources/player.ron", "player"),
            SpriteInfo::new("r-typesheet1.gif", "../resources/bullet.ron", "bullet"),
            SpriteInfo::new("r-typesheet5.gif", "../resources/enemy.ron", "enemy"),
        ];
        let mut sprite_sheet_list = SpriteSheetList::default();

        self.load_ui = Some(world.exec(|mut creator: UiCreator<'_>| creator.create("ui/load.ron", &mut self.ui_counter)));
        self.menu_ui = Some(world.exec(|loader: UiLoader<'_>| loader.load("ui/menu.ron", &mut self.ui_counter)));
        self.game_ui = Some(world.exec(|loader: UiLoader<'_>| loader.load("ui/game.ron", &mut self.ui_counter)));
        self.pause_ui = Some(world.exec(|loader: UiLoader<'_>| loader.load("ui/pause.ron", &mut self.ui_counter)));

        self.sheet_counter = Some(match sprite_sheet_list.load_from(world, sprite_infos) {
            Ok(counter) => counter,
            _ => ProgressCounter::new(),
        });
        world.insert(sprite_sheet_list);
        world.register::<Bullet>();
        world.register::<Enemy>();
        world.register::<Shield>();
    }

    fn update(&mut self, data: &mut StateData<'_, GameData<'_, '_>>) -> SimpleTrans {
        if let Some(ref sheet_counter) = self.sheet_counter {
            if sheet_counter.num_loading() != 0 {
                return Trans::None;
            }
        }
        match self.ui_counter.complete() {
            Completion::Failed => {
                eprintln!("Failed loading ui assets");
                Trans::Quit
            }
            Completion::Complete => {
                println!("Assets loaded");
                if let Some(entity) = self.load_ui {
                    let _ = data.world.delete_entity(entity);
                }
                Trans::Switch(Box::new(MenuState::new(
                    data.world.create_entity().with(self.menu_ui.as_ref().unwrap().clone()).build(),
                    self.game_ui.as_ref().unwrap().clone(),
                    self.pause_ui.as_ref().unwrap().clone(),
                )))
            }
            Completion::Loading => Trans::None,
        }
    }
}
