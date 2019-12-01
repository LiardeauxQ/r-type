use amethyst::{
    ecs::prelude::Entity,
    input::{is_close_requested, is_key_down},
    prelude::*,
    assets::Handle,
    ui::UiPrefab,
    winit::VirtualKeyCode,
};

use crate::states::delete_hierarchy;
use crate::states::PauseState;

#[derive(Debug)]
pub struct GameState {
    root_ui: Entity,
    pause_ui: Handle<UiPrefab>,
    paused: bool,
}

impl GameState {
    pub fn new(root_ui: Entity, pause_ui: Handle<UiPrefab>) -> GameState {
        GameState {
            root_ui: root_ui,
            pause_ui: pause_ui,
            paused: false,
        }
    }
}

impl SimpleState for GameState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Entering GameState");
    }

    fn on_pause(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        self.paused = true;
    }

    fn on_resume(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        self.paused = false;
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        match event {
            StateEvent::Window(event) => {
                if is_close_requested(&event) {
                    Trans::Quit
                } else if is_key_down(&event, VirtualKeyCode::Escape) {
                    Trans::Push(Box::new(PauseState::new(
                        data.world.create_entity().with(self.pause_ui.clone()).build(),
                    )))
                } else {
                    Trans::None
                }
            }
            _ => Trans::None
        }
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        delete_hierarchy(self.root_ui, data.world).expect("Failed to remove game state");
        println!("Leaving GameState");
    }
}
