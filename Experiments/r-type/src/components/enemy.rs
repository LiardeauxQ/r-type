use amethyst::ecs::prelude::{Component, DenseVecStorage};

pub struct Enemy;

impl Component for Enemy {
    type Storage = DenseVecStorage<Self>;
}