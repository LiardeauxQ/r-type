use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Team {
    pub id: usize,
}

impl Team {
    pub fn new(id: usize) -> Self {
        Team {
            id,
        }
    }
}

impl Default for Team {
    fn default() -> Self {
        Team {
            id: 0,
        }
    }
}

impl Component for Team {
    type Storage = DenseVecStorage<Self>;
}
