use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Health {
    pub max: i32,
    pub current: i32,
}

impl Health {
    pub fn new(max: i32, current: i32) -> Health {
        Health { max, current }
    }
}

impl Component for Health {
    type Storage = DenseVecStorage<Self>;
}
