use amethyst::{
    ecs::prelude::{Component, DenseVecStorage},
};

pub struct Circle {
    pub radius: f32,
}

impl Circle {
    pub fn new(radius: f32) -> Circle {
        Circle {
            radius,
        }
    }
}

impl Component for Circle {
    type Storage = DenseVecStorage<Self>;
}