use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Level {
    pub max: u32,
    pub current: u32,
}

impl Level {
    pub fn new(max: u32, current: u32) -> Level {
        Level { max, current }
    }
}

impl Component for Level {
    type Storage = DenseVecStorage<Self>;
}
