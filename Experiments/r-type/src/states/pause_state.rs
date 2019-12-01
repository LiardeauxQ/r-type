use amethyst::{
    ecs::prelude::Entity,
    input::{is_close_requested, is_key_down},
    prelude::*,
    shrev::EventChannel,
    ui::{UiEvent, UiEventType, UiFinder},
    winit::VirtualKeyCode,
};
use crate::states::delete_hierarchy;

const P_RESUME_GAME_BUTTON: &str = "p_resume_game";
const P_OPTIONS_BUTTON: &str = "p_options";
const P_BACK_MENU_BUTTON: &str = "p_back_menu";
const P_EXIT_GAME_BUTTON: &str = "p_exit_game";

#[derive(Debug)]
pub struct PauseState {
    root_ui: Entity,
    resume_game_button: Option<Entity>,
    options_button: Option<Entity>,
    back_menu_button: Option<Entity>,
    exit_game_button: Option<Entity>,
}

impl PauseState {
    pub fn new(root_ui: Entity) -> PauseState {
        PauseState {
            root_ui: root_ui,
            resume_game_button: None,
            options_button: None,
            back_menu_button: None,
            exit_game_button: None,
        }
    }
}

impl SimpleState for PauseState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Entering PauseState");
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        match event {
            StateEvent::Window(event) => {
                if is_close_requested(&event) {
                    Trans::Quit
                } else if is_key_down(&event, VirtualKeyCode::Escape) {
                    Trans::Pop
                } else {
                    Trans::None
                }
            }
            StateEvent::Ui(UiEvent {
                event_type: UiEventType::Click,
                target,
            }) => {
                if Some(target) == self.resume_game_button {
                    println!("RESUME GAME PRESSED!");
                    Trans::Pop
                } else if Some(target) == self.options_button {
                    println!("OPTIONS PRESSED!");
                    Trans::None
                } else if Some(target) == self.back_menu_button {
                    println!("BACK MENU PRESSED!");
                    data.world
                        .write_resource::<EventChannel<TransEvent<GameData, StateEvent>>>()
                        .single_write(Box::new(|| Trans::Pop));
                    Trans::Pop
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

    fn update(&mut self, data: &mut StateData<'_, GameData<'_, '_>>) -> SimpleTrans {
        let StateData { world, .. } = data;

        if self.resume_game_button.is_none()
            || self.options_button.is_none()
            || self.back_menu_button.is_none()
            || self.exit_game_button.is_none()
        {
            world.exec(|ui_finder: UiFinder<'_>| {
                self.resume_game_button = ui_finder.find(P_RESUME_GAME_BUTTON);
                self.options_button = ui_finder.find(P_OPTIONS_BUTTON);
                self.back_menu_button = ui_finder.find(P_BACK_MENU_BUTTON);
                self.exit_game_button = ui_finder.find(P_EXIT_GAME_BUTTON);
            });
        }

        Trans::None
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        delete_hierarchy(self.root_ui, data.world).expect("Failed to remove pause state");
        self.resume_game_button = None;
        self.options_button = None;
        self.back_menu_button = None;
        self.exit_game_button = None;
        println!("Leaving PauseState");
    }
}
