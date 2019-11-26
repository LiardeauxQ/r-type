extern crate amethyst;
use amethyst::{
    prelude::*,
    renderer::{
        plugins::{RenderFlat2D, RenderToWindow},
        types::DefaultBackend,
        RenderingBundle,
    },
    utils::application_root_dir,
    core::transform::TransformBundle,
    input::{InputBundle, StringBindings},
    {LoggerConfig},
};

mod rtype;
mod systems;
mod components;
mod physics;
mod common;
mod entities;

use crate::rtype::RType;

fn main() -> Result<(), amethyst::Error>{
    let app_root = application_root_dir()?;

    amethyst::start_logger(LoggerConfig::default());
    let display_config_path = app_root.join("resources").join("display_config.ron");
    let assets_dir = app_root.join("assets");
    let binding_path = app_root.join("resources").join("bindings.ron");
    let input_bundle = InputBundle::<StringBindings>::new()
        .with_bindings_from_file(binding_path)?;

    let mut world = World::new();
    let game_data = GameDataBuilder::default()
        .with_bundle(
            RenderingBundle::<DefaultBackend>::new()
                .with_plugin(
                    RenderToWindow::from_config_path(display_config_path)
                        .with_clear([0.0, 0.0, 0.0, 1.0]),
                )
                .with_plugin(RenderFlat2D::default()),
        )?
        .with_bundle(TransformBundle::new())?
        .with_bundle(input_bundle)?
        .with(systems::PlayerSystem, "player_system", &["input_system"]);
        //.with(systems::MovementSystem, "movement_system", &[])
        //.with(systems::BounceSystem, "bounce_system", &["movement_system"])
        //.with(systems::UpdateVelocitySystem, "update_velocity_system", &["movement_system", "bounce_system"]);
    let mut game = Application::new(assets_dir, RType, game_data)?;

    game.run();
    Ok(())
}
