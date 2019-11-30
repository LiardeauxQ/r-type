use amethyst::ecs::prelude::{Component, DenseVecStorage};
use std::time::Duration;
use std::collections::HashMap;

pub struct SheetPosition {
    pub start: usize,
    pub end: usize,
    pub current: usize,
}

impl SheetPosition {
    pub fn new(start: usize, end: usize, current: usize) -> Self {
        SheetPosition {
            start,
            end,
            current,
        }
    }
}

pub struct TimeAnimation {
    positions: SheetPosition,
    max_duration: Duration,
    current_duration: Duration,
}

impl TimeAnimation {
    pub fn new(positions: SheetPosition, duration: u64) -> Self {
        TimeAnimation {
            positions,
            max_duration: Duration::from_millis(duration),
            current_duration: Duration::from_millis(duration),
        }
    }

    pub fn substract_time(&mut self, amount: Duration) {
        if let Some(result) = self.current_duration.checked_sub(amount) {
            self.current_duration = result;
        }
        self.positions.current = (((self.positions.end - self.positions.start) as u128)
            * self.current_duration.as_millis()
            / self.max_duration.as_millis()) as usize + self.positions.start;
    }

    pub fn get_current_sprite(&self) -> usize {
        self.positions.current
    }
}

pub struct TimeAnimationList {
    animations: HashMap<String, TimeAnimation>,
    current: Option<String>,
}

impl Default for TimeAnimationList {
    fn default() -> Self {
        TimeAnimationList {
            animations: HashMap::new(),
            current: None,
        }
    }
}

impl TimeAnimationList {
    pub fn insert(&mut self, id: &str, animation: TimeAnimation) {
        self.animations.insert(id.to_string(), animation);
    }

    pub fn run(&mut self, id: &str) {
        self.current = Some(id.to_string());
    }

    pub fn substract_time(&mut self, amount: Duration) {
        if let Some(ref id) = self.current {
            match self.animations.get_mut(id.as_str()) {
                Some(animation) => {
                    animation.substract_time(amount);
                }
                None => {}
            }
        }
    }

    pub fn get_current_sprite(&self) -> Option<usize> {
        if let Some(ref id) = self.current {
            return match self.animations.get(id.as_str()) {
                Some(animation) => {
                    Some(animation.get_current_sprite())
                }
                None => None
            }
        }
        None
    }
}

impl Component for TimeAnimationList {
    type Storage = DenseVecStorage<Self>;
}