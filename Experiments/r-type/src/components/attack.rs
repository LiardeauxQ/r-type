use amethyst::{
    core::timing::Stopwatch,
    ecs::prelude::{Component, DenseVecStorage},
};

use std::time::Duration;

pub struct AttackSpeed {
    pub frequency: Duration,
    pub elapsed_time: Stopwatch,
}

impl AttackSpeed {
    pub fn new(frequency: u64) -> Self {
        let mut elapsed_time = Stopwatch::new();

        elapsed_time.start();
        AttackSpeed {
            frequency: Duration::new(frequency, 0),
            elapsed_time
        }
    }
}

impl Component for AttackSpeed {
    type Storage = DenseVecStorage<Self>;
}