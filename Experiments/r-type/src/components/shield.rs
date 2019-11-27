use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Shield {
    pub max: u32,
    pub current: u32,
}

impl Shield {
    pub fn new(max: u32, current: u32) -> Shield {
        Shield { max, current }
    }
}

impl Component for Shield {
    type Storage = DenseVecStorage<Self>;
}
