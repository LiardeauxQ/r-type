use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Velocity {
    pub x: f32,
    pub y: f32,
}

impl Velocity {
    pub fn new(x: f32, y: f32) -> Self {
        Velocity { x, y }
    }
}

impl Component for Velocity {
    type Storage = DenseVecStorage<Self>;
}

#[derive(PartialEq)]
pub enum Direction {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
}

impl Component for Direction {
    type Storage = DenseVecStorage<Self>;
}

pub struct Movable {
    pub is_movable: bool,
}

impl Component for Movable {
    type Storage = DenseVecStorage<Self>;
}