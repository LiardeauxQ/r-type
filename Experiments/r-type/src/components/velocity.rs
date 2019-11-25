use amethyst::{
    ecs::prelude::{Component, DenseVecStorage},
};

pub struct Velocity {
    pub x: f32,
    pub y: f32,
}

impl Velocity {
    pub fn new(x: f32, y: f32) -> Self {
        Velocity {
            x,
            y
        }
    }
}

impl Component for Velocity {
    type Storage = DenseVecStorage<Self>;
}
