use amethyst::{
    ecs::prelude::Entity,
    input::{is_close_requested, is_key_down},
    prelude::*,
    ui::{UiCreator, UiEvent, UiEventType, UiFinder, UiPrefab},
    assets::{Completion, Handle, Prefab},
    winit::VirtualKeyCode,
};

use crate::states::delete_hierarchy;
use crate::states::{GameState, PauseState};

const M_START_GAME_BUTTON: &str = "m_start_game";
const M_OPTIONS_BUTTON: &str = "m_options";
const M_EXIT_GAME_BUTTON: &str = "m_exit_game";

#[derive(Debug)]
pub struct MenuState {
    root_ui: Entity,
    pause_ui: Handle<UiPrefab>,
    start_game_button: Option<Entity>,
    options_button: Option<Entity>,
    exit_game_button: Option<Entity>,
}

impl MenuState {
    pub fn new(root_ui: Entity, pause_ui: Handle<UiPrefab>) -> MenuState {
        MenuState {
            root_ui: root_ui,
            pause_ui: pause_ui,
            start_game_button: None,
            options_button: None,
            exit_game_button: None,
        }
    }
}

impl SimpleState for MenuState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Entering MenuState");
        let world = data.world;
    }

    fn update(&mut self, data: &mut StateData<'_, GameData<'_, '_>>) -> SimpleTrans {
        let StateData { world, .. } = data;

        if self.start_game_button.is_none()
            || self.options_button.is_none()
            || self.exit_game_button.is_none()
        {
            world.exec(|ui_finder: UiFinder<'_>| {
                self.start_game_button = ui_finder.find(M_START_GAME_BUTTON);
                self.options_button = ui_finder.find(M_OPTIONS_BUTTON);
                self.exit_game_button = ui_finder.find(M_EXIT_GAME_BUTTON);
            });
        }

        Trans::None
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        match event {
            StateEvent::Window(event) => {
                if is_close_requested(&event) {
                    Trans::Quit
                } else if is_key_down(&event, VirtualKeyCode::Escape) {
                    Trans::Quit
                } else {
                    Trans::None
                }
            }
            StateEvent::Ui(UiEvent {
                event_type: UiEventType::Click,
                target,
            }) => {
                if Some(target) == self.start_game_button {
                    println!("START GAME PRESSED!");
                    Trans::Push(Box::new(GameState::default()))
                } else if Some(target) == self.options_button {
                    println!("OPTIONS PRESSED!");
                    Trans::None
                } else if Some(target) == self.exit_game_button {
                    println!("EXIT GAME PRESSED!");
                    Trans::Quit
                } else {
                    Trans::None
                }
            }
            _ => Trans::None
        }
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        delete_hierarchy(self.root_ui, data.world).expect("Failed to remove menu");
        self.start_game_button = None;
        self.options_button = None;
        self.exit_game_button = None;
        println!("Leaving MenuState");
    }
}
