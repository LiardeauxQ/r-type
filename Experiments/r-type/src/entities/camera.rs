use amethyst::{core::transform::Transform, prelude::*, renderer::Camera};

use crate::states::{HEIGHT, WIDTH};

pub fn initialize_camera(world: &mut World) {
    let mut transform = Transform::default();

    transform.set_translation_xyz(WIDTH * 0.5, HEIGHT * 0.5, 1.0);
    world
        .create_entity()
        .with(Camera::standard_2d(WIDTH, HEIGHT))
        .with(transform)
        .build();
}
