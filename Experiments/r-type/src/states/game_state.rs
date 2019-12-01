use amethyst::{
    ecs::prelude::Entity,
    core::timing::Time,
    input::{is_close_requested, is_key_down},
    prelude::*,
    assets::Handle,
    ui::UiPrefab,
    winit::VirtualKeyCode,
};

use crate::states::delete_hierarchy;
use crate::states::PauseState;
use crate::entities;

pub const WIDTH: f32 = 500.0;
pub const HEIGHT: f32 = 500.0;

#[derive(Debug)]
pub struct GameState {
    root_ui: Entity,
    pause_ui: Handle<UiPrefab>,
    player: Option<Entity>,
    spawners: Option<Vec<Entity>>,
    camera: Option<Entity>,
    paused: bool,
    desired_time_scale: f32,
}

impl GameState {
    pub fn new(root_ui: Entity, pause_ui: Handle<UiPrefab>) -> GameState {
        GameState {
            root_ui: root_ui,
            pause_ui: pause_ui,
            player: None,
            spawners: None,
            camera: None,
            paused: false,
            desired_time_scale: 1.0,
        }
    }

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

impl SimpleState for GameState {
    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world;

        self.player = entities::initialize_player(world).ok();
        self.spawners = entities::initialize_spawners(world).ok();
        self.camera = Some(entities::initialize_camera(world));
    }

    fn on_pause(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        self.paused = true;
    }

    fn on_resume(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        self.paused = false;
        self.update_time_scale(data.world);
    }

    fn handle_event(&mut self, data: StateData<'_, GameData<'_, '_>>, event: StateEvent) -> SimpleTrans {
        match event {
            StateEvent::Window(event) => {
                if is_close_requested(&event) {
                    Trans::Quit
                } else if is_key_down(&event, VirtualKeyCode::Escape) {
                    self.paused = true;
                    self.update_time_scale(data.world);
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
        let mut world = data.world;

        delete_hierarchy(self.root_ui, world).expect("Failed to remove game state");
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
