use amethyst::{
    input::{is_key_down, VirtualKeyCode},
    prelude::*,
    ecs::Entity,
};

use crate::states::pause_state::PauseState;
use crate::entities;

pub const WIDTH: f32 = 500.0;
pub const HEIGHT: f32 = 500.0;

#[derive(Default)]
pub struct GameState {
    player: Option<Entity>,
    spawners: Option<Vec<Entity>>,
    camera: Option<Entity>,
}

impl SimpleState for GameState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;

        self.player = entities::initialize_player(world).ok();
        self.spawners = entities::initialize_spawners(world).ok();
        self.camera = Some(entities::initialize_camera(world));
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        if let StateEvent::Window(event) = &event {
            if is_key_down(&event, VirtualKeyCode::Escape) {
                return Trans::Push(Box::new(PauseState));
            }
        }
        Trans::None
    }

    fn on_stop(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let mut world = data.world;

        if let Some(player) = self.player {
            world.delete_entity(player);
        }
        if let Some(ref spawners) = self.spawners {
            world.delete_entities(spawners.as_slice());
        }
        if let Some(camera) = self.camera {
            world.delete_entity(camera);
        }
        println!("Leaving GameState");
    }
}
