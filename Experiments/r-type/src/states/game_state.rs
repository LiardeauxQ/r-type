use amethyst::{
    core::timing::Time,
    input::{is_key_down, VirtualKeyCode},
    prelude::*,
    ecs::Entity,
};

use crate::states::pause_state::PauseState;
use crate::entities;

pub const WIDTH: f32 = 500.0;
pub const HEIGHT: f32 = 500.0;

pub struct GameState {
    player: Option<Entity>,
    spawners: Option<Vec<Entity>>,
    camera: Option<Entity>,
    paused: bool,
    desired_time_scale: f32,
}

impl GameState {
    fn update_time_scale(&self, world: &mut World) {
        world
            .write_resource::<Time>()
            .set_time_scale(if self.paused {
                0.0
            } else {
                self.desired_time_scale
            });
    }
}

impl Default for GameState {
    fn default() -> Self {
        GameState {
            player: None,
            spawners: None,
            camera: None,
            paused: false,
            desired_time_scale: 1.0,
        }
    }
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
                self.paused = true;
                self.update_time_scale(data.world);
                return Trans::Push(Box::new(PauseState));
            }
        }
        Trans::None
    }

    fn on_resume(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        self.paused = false;
        self.update_time_scale(data.world);
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
