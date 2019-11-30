use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Player {
    pub can_fire: bool,
    pub width: f32,
    pub height: f32,
}

impl Player {
    pub fn new(width: f32, height: f32) -> Self {
        Player {
            can_fire: true,
            width,
            height,
        }
    }
}

impl Default for Player {
    fn default() -> Self {
        Player {
            can_fire: true,
            width: 0.0,
            height: 0.0,
        }
    }
}

impl Component for Player {
    type Storage = DenseVecStorage<Self>;
}
