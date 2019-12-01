use amethyst::ecs::prelude::{Component, NullStorage};

#[derive(Default)]
pub struct Spawner;

impl Component for Spawner {
    type Storage = NullStorage<Self>;
}