use amethyst::{
    core::{SystemDesc, Transform},
    core::timing::Time,
    derive::SystemDesc,
    ecs::prelude::{
        Entities, Join, LazyUpdate, Read, ReadExpect, ReadStorage, System, SystemData, World,
        WriteStorage,
    },
};

use crate::common::SpriteSheetList;
use crate::components::{AttackSpeed, Spawner, Team};
use crate::entities;

#[derive(SystemDesc)]
pub struct EnemySystem;

impl<'s> System<'s> for EnemySystem {
    type SystemData = (
        Entities<'s>,
        ReadStorage<'s, Spawner>,
        WriteStorage<'s, AttackSpeed>,
        ReadStorage<'s, Transform>,
        ReadStorage<'s, Team>,
        ReadExpect<'s, LazyUpdate>,
        ReadExpect<'s, SpriteSheetList>,
        Read<'s, Time>,
    );

    fn run(&mut self, data: Self::SystemData) {
        let (
            entities,
            spawners,
            mut spawns_rate,
            transforms,
            teams,
            lazy_update,
            sprite_sheet_list,
            time,
        ) = data;

        for (spawner, spawn_rate, transform, team)
            in (&spawners, &mut spawns_rate, &transforms, &teams).join() {
            if time.delta_seconds() == 0.0 || spawn_rate.elapsed_time.elapsed() < spawn_rate.frequency {
                continue;
            }
            if entities::spawn_enemy(&entities, &sprite_sheet_list, &lazy_update, &transform, &team) {
                spawn_rate.elapsed_time.restart();
            }
        }
    }
}
