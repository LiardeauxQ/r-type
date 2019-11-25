use std::fmt;

pub trait Collision {
    type Collider: Collision;

    fn is_colliding_with(&self, object: &Self::Collider) -> bool;
}

pub struct Point {
    pub x: f32,
    pub y: f32
}

impl Point {
    pub fn new(x: f32, y: f32) -> Point {
        Point {
            x,
            y
        }
    }
}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Point<{};{}>", self.x, self.y)
    }
}

pub struct SphereCollision {
    pub radius: f32,
    pub center: Point,
}

impl SphereCollision {
    pub fn new(radius: f32, center: Point) -> SphereCollision {
        SphereCollision {
            radius,
            center
        }
    }
}

impl Collision for SphereCollision {
    type Collider = SphereCollision;

    fn is_colliding_with(&self, object: &SphereCollision) -> bool {
        let vector = Point::new((object.center.x - self.center.x).abs(),
            (object.center.y - self.center.y).abs());
        let distance = (vector.x.powf(2.0) + vector.y.powf(2.0)).sqrt();

        distance < (object.radius + self.radius)
    }
}
