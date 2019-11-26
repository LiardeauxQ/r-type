use amethyst::{
    ecs::prelude::{Component, DenseVecStorage},
};

pub enum Direction {
    Top,
    Bottom,
    Left,
    Right
}

pub struct Player {
    pub direction: Direction,
    pub max_sprites: usize,
}

impl Player {
    pub fn new(direction: Direction, max_sprites: usize) -> Self {
        Player {
            direction,
            max_sprites,
        }
    }
}

impl Default for Player {
    fn default() -> Self {
        Player {
            direction: Direction::Right,
            max_sprites: 0,
        }
    }
}

impl Component for Player {
    type Storage = DenseVecStorage<Self>;
}