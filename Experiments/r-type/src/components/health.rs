use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Health {
    pub max: u32,
    pub current: u32,
}

impl Health {
    pub fn new(max: u32, current: u32) -> Health {
        Health { max, current }
    }
}

impl Component for Health {
    type Storage = DenseVecStorage<Self>;
}
