use amethyst::{
    input::{is_key_down, VirtualKeyCode},
    prelude::*,
};

pub struct MenuState;

impl SimpleState for MenuState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Entering MenuState");
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        Trans::None
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        println!("Leaving MenuState");
    }
}
