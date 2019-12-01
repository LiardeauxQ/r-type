use amethyst::{
    core::timing::Stopwatch,
    ecs::prelude::{Component, DenseVecStorage, NullStorage},
};

use std::time::Duration;

pub struct AttackSpeed {
    pub frequency: Duration,
    pub elapsed_time: Stopwatch,
}

impl AttackSpeed {
    pub fn new(micros: u64) -> Self {
        let mut elapsed_time = Stopwatch::new();

        elapsed_time.start();
        AttackSpeed {
            frequency: Duration::from_millis(micros),
            elapsed_time
        }
    }
}

impl Component for AttackSpeed {
    type Storage = DenseVecStorage<Self>;
}

#[derive(Copy, Clone)]
pub struct AttackPattern {
    pattern: fn(f32) -> f32,
    x_max: f32,
    y_max: f32,
}

impl AttackPattern {
    pub fn new(pattern: fn(f32) -> f32, x_max: f32, y_max: f32)-> Self {
        AttackPattern {
            pattern,
            x_max,
            y_max,
        }
    }

    pub fn compute(&self, x: f32) -> f32 {
        (self.pattern)(x / self.x_max) * self.y_max
    }

    pub fn compute_cos(x: f32) -> f32 {
        x.cos()
    }

    pub fn compute_sin(x: f32) -> f32 {
        x.sin()
    }

    pub fn compute_on_x(x: f32) -> f32 {
        1.0 / x
    }

    pub fn compute_descending_slope(x: f32) -> f32 {
        -x
    }

    pub fn compute_ascending_slope(x: f32) -> f32 {
        x
    }
}

impl Component for AttackPattern {
    type Storage = DenseVecStorage<Self>;
}

pub struct Damage {
    pub amount: i32,
}

impl Damage {
    pub fn new(amount: i32) -> Self {
        Damage {
            amount
        }
    }
}

impl Component for Damage {
    type Storage = DenseVecStorage<Self>;
}

#[derive(Default)]
pub struct Explosion;

impl Component for Explosion {
    type Storage = NullStorage<Self>;
}