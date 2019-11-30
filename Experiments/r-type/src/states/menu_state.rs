use amethyst::{
    ecs::prelude::Entity,
    input::{is_close_requested, is_key_down},
    prelude::*,
    ui::{UiCreator, UiEvent, UiEventType, UiFinder},
    winit::VirtualKeyCode,
};

use crate::states::delete_hierarchy;

const START_GAME_BUTTON: &str = "start_game";
const OPTIONS_BUTTON: &str = "options";
const EXIT_GAME_BUTTON: &str = "exit_game";

#[derive(Default, Debug)]
pub struct MenuState {
    ui_load: Option<Entity>,
    ui_root: Option<Entity>,
    start_game_button: Option<Entity>,
    options_button: Option<Entity>,
    exit_game_button: Option<Entity>,
}

impl SimpleState for MenuState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Entering MenuState");
        let world = data.world;

        self.ui_root = Some(world.exec(|mut creator: UiCreator<'_>| creator.create("ui/menu.ron", ())));
    }

    fn update(&mut self, data: &mut StateData<'_, GameData<'_, '_>>) -> SimpleTrans {
        let StateData { world, .. } = data;

        if self.start_game_button.is_none()
            || self.options_button.is_none()
            || self.exit_game_button.is_none()
        {
            world.exec(|ui_finder: UiFinder<'_>| {
                self.start_game_button = ui_finder.find(START_GAME_BUTTON);
                self.options_button = ui_finder.find(OPTIONS_BUTTON);
                self.exit_game_button = ui_finder.find(EXIT_GAME_BUTTON);
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
                }
                if Some(target) == self.options_button {
                    println!("OPTIONS PRESSED!");
                }
                if Some(target) == self.exit_game_button {
                    println!("EXIT GAME PRESSED!");
                }
                Trans::None
            }
            _ => Trans::None
        }
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        if let Some(entity) = self.ui_root {
            delete_hierarchy(entity, data.world).expect("Failed to remove Menu");
        }
        self.ui_load = None;
        self.ui_root = None;
        self.start_game_button = None;
        self.options_button = None;
        self.exit_game_button = None;
        println!("Leaving MenuState");
    }
}
