extern crate amethyst;

use amethyst::{
    core::transform::TransformBundle,
    input::{InputBundle, StringBindings},
    prelude::*,
    renderer::{
        plugins::{RenderFlat2D, RenderToWindow},
        types::DefaultBackend,
        RenderingBundle,
    },
    utils::application_root_dir,
    {Error, LoggerConfig},
};

mod common;
mod components;
mod entities;
mod physics;
mod states;
mod systems;

use crate::states::LoadState;

fn init_game_data<'a, 'b>() -> Result<GameDataBuilder<'a, 'b>, Error> {
    let app_root = application_root_dir()?;
    let display_config_path = app_root.join("resources").join("display_config.ron");
    let binding_path = app_root.join("resources").join("bindings.ron");
    let input_bundle =
        InputBundle::<StringBindings>::new().with_bindings_from_file(binding_path)?;

    Ok(GameDataBuilder::default()
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
        .with(systems::PlayerSystem, "player_system", &["input_system"])
        .with(systems::EnemySystem, "enemy_system", &[])
        .with(systems::FireSystem, "fire_system", &["input_system"])
        .with(systems::MovementSystem, "movement_system", &[])
        .with(systems::BounceSystem, "bounce_system", &["movement_system"])
        .with(systems::CollisionSystem, "collision_system", &["bounce_system"])
    )
    //.with(systems::UpdateVelocitySystem, "update_velocity_system", &["movement_system", "bounce_system"]);
}

fn main() -> Result<(), amethyst::Error> {
    amethyst::start_logger(LoggerConfig::default());

    let app_root = application_root_dir()?;
    let assets_dir = app_root.join("assets");
    let game_data = init_game_data()?;
    let mut game = Application::new(assets_dir, LoadState::default(), game_data)?;

    game.run();
    Ok(())
}
