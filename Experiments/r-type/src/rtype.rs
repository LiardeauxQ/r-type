use amethyst::{
    assets::{AssetStorage, Loader, Handle},
    core::transform::Transform,
    prelude::*,
    renderer::{Camera, ImageFormat, SpriteRender, SpriteSheet, SpriteSheetFormat, Texture},
};

pub const WIDTH: f32 = 150.0;
pub const HEIGHT: f32 = 150.0;
pub const VELOCITY_X: f32 = 10.0;
pub const VELOCITY_Y: f32 = 10.0;

pub const CIRCLE_SIZE: f32 = 15.0;

use crate::components::{Circle, Velocity, Collidee, Collider};

pub struct RType;

impl SimpleState for RType {

    fn on_start(&mut self, data: StateData<'_, GameData<'_, '_>>) {
        let world = data.world; 
        let sprite_sheet_handle = load_sprite_sheet(world);

        world.register::<Circle>();
        initialize_sphere(world, sprite_sheet_handle);
        initialize_camera(world);
    }
}

fn initialize_camera(world: &mut World) {
    let mut transform = Transform::default();

    transform.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 1.0);
    world
        .create_entity()
        .with(Camera::standard_2d(WIDTH, HEIGHT))
        .with(transform)
        .build();
}

fn initialize_sphere(world: &mut World, sprite_sheet: Handle<SpriteSheet>) {
    let mut transform_s1 = Transform::default();
    let mut transform_s2 = Transform::default();
    let mut transform_s3 = Transform::default();

    transform_s1.set_translation_xyz(CIRCLE_SIZE * 0.5, CIRCLE_SIZE * 0.5, 0.0);
    transform_s2.set_translation_xyz(WIDTH - (CIRCLE_SIZE * 0.5), CIRCLE_SIZE * 0.5, 0.0);
    transform_s3.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 0.0);

    let sprite_render = SpriteRender {
        sprite_sheet: sprite_sheet.clone(),
        sprite_number: 0,
    };

    world
        .create_entity()
        .with(Circle::new(CIRCLE_SIZE * 0.5))
        .with(Velocity::new(VELOCITY_X, VELOCITY_Y))
        .with(Collidee::default())
        .with(Collider::default())
        .with(transform_s1)
        .with(sprite_render.clone())
        .build();
    world
        .create_entity()
        .with(Circle::new(CIRCLE_SIZE * 0.5))
        .with(Velocity::new(VELOCITY_X, VELOCITY_Y))
        .with(Collidee::default())
        .with(Collider::default())
        .with(transform_s2)
        .with(sprite_render.clone())
        .build();
    world
        .create_entity()
        .with(Circle::new(CIRCLE_SIZE * 0.5))
        .with(Velocity::new(VELOCITY_X, VELOCITY_Y))
        .with(Collidee::default())
        .with(Collider::default())
        .with(transform_s3)
        .with(sprite_render.clone())
        .build();
}

fn load_sprite_sheet(world: &mut World) -> Handle<SpriteSheet> {
    let texture_handle = {
        let loader = world.read_resource::<Loader>();
        let texture_storage = world.read_resource::<AssetStorage<Texture>>();
        loader.load(
            "../assets/circle.png",
            ImageFormat::default(),
            (),
            &texture_storage
        )
    };

    let loader = world.read_resource::<Loader>();
    let sprite_sheet_store = world.read_resource::<AssetStorage<SpriteSheet>>();

    loader.load(
        "../resources/circle.ron",
        SpriteSheetFormat(texture_handle),
        (),
        &sprite_sheet_store,
    )
}
