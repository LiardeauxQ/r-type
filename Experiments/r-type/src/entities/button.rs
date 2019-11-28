use amethyst::{core::transform::Transform, prelude::*, renderer::SpriteRender};

use crate::common::{AssetType, SpriteSheetList};
//use crate::components::{};
use crate::states::{HEIGHT, WIDTH};
use crate::states::MenuButton;

pub fn initialize_button(world: &mut World, button: MenuButton, selected: bool) -> Result<(), &'static str> {
    let mut transform_s1 = Transform::default();
    println!("Init button");
    let button_sheet = world
        .fetch::<SpriteSheetList>()
        .get(AssetType::Button)
        .ok_or("Cannot fetch sprite sheet")?;
    let sprite_render = SpriteRender {
        sprite_sheet: button_sheet.clone(),
        sprite_number: button as usize,
    };

    transform_s1.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 0.0);
    world
        .create_entity()
        .with(transform_s1)
        .with(sprite_render.clone())
        .build();
    Ok(())
}
