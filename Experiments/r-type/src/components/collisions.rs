use amethyst::{
    ecs::prelude::{Component, DenseVecStorage},
};

pub struct Collidee {
    pub x_collision: bool,
    pub y_collision: bool,
}

impl Component for Collidee {
    type Storage = DenseVecStorage<Self>;
}

impl Default for Collidee {
    fn default() -> Self {
        Collidee {
            x_collision: false,
            y_collision: false,
        }
    }
}

pub struct Collider {
    pub x_collision: bool,
    pub y_collision: bool,
}

impl Default for Collider {
    fn default() -> Self {
        Collider {
            x_collision: false,
            y_collision: false,
        }
    }
}

impl Component for Collider {
    type Storage = DenseVecStorage<Self>;
}