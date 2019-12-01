use amethyst::ecs::prelude::{Component, DenseVecStorage, NullStorage};
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
    current_duration: Option<Duration>,
    repeat: bool,
}

impl TimeAnimation {
    pub fn new(positions: SheetPosition, duration: u64, repeat: bool) -> Self {
        TimeAnimation {
            positions,
            max_duration: Duration::from_millis(duration),
            current_duration: Some(Duration::from_millis(duration)),
            repeat,
        }
    }

    pub fn substract_time(&mut self, amount: Duration) {
        self.current_duration = self.current_duration
            .map_or(Some(Duration::new(0, 0)), |c| c.checked_sub(amount));
        if let Some(ref duration) = self.current_duration {
            self.positions.current = (((self.positions.end - self.positions.start) as u128)
                * duration.as_millis()
                / self.max_duration.as_millis()) as usize + self.positions.start;
        } else if self.repeat {
            self.current_duration = Some(self.max_duration);
        }
    }

    pub fn get_current_sprite(&self) -> usize {
        self.positions.current
    }

    pub fn can_repeat(&self) -> bool {
        self.repeat
    }

    pub fn is_animation_ended(&self) -> bool {
        if let Some(current) = self.current_duration {
            println!("{:?}", current);
            if current == Duration::new(0, 0) {
                return true;
            }
        }
        false
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

    pub fn is_animation_left(&self) -> bool {
        for (_, ref v) in self.animations.iter() {
            if !v.is_animation_ended() {
                return false;
            }
        }
        return true;
    }
}

impl Component for TimeAnimationList {
    type Storage = DenseVecStorage<Self>;
}

#[derive(Default)]
pub struct DestroyableAnimation;

impl Component for DestroyableAnimation {
    type Storage = NullStorage<Self>;
}

