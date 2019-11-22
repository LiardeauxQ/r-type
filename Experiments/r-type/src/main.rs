extern crate amethyst;
use amethyst::{
    prelude::*,
    renderer::{
        plugins::{RenderFlat2D, RenderToWindow},
        types::DefaultBackend,
        RenderingBundle,
    },
    utils::application_root_dir,
};

struct RType;
impl SimpleState for RType {}

fn main() -> Result<(), amethyst::Error>{
    let app_root = application_root_dir()?;

    let display_config_path = app_root.join("ressources").join("display_config.ron");
    let assets_dir = app_root.join("assets");

    let mut world = World::new();
    let game_data = GameDataBuilder::default()
        .with_bundle(
            RenderingBundle::<DefaultBackend>::new()
                // The RenderToWindow plugin provides all the scaffolding for opening a window and drawing on it
                .with_plugin(
                    RenderToWindow::from_config_path(display_config_path)
                        .with_clear([0.0, 0.0, 0.0, 1.0]),
                )
                // RenderFlat2D plugin is used to render entities with a `SpriteRender` component.
                .with_plugin(RenderFlat2D::default()),
        )?;
    let mut game = Application::new(assets_dir, RType, game_data)?;

    game.run();
    Ok(())
}
