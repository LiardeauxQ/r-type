use amethyst::{
    assets::{AssetStorage, Handle, Loader, ProgressCounter},
    prelude::*,
    renderer::{ImageFormat, SpriteSheet, SpriteSheetFormat, Texture},
};
use std::collections::HashMap;

#[derive(Hash, PartialEq, Eq, Copy, Clone)]
pub enum AssetType {
    Player,
    Bullet,
    Button,
}

pub struct SpriteInfo<'a> {
    file_name: &'a str,
    ron_name: &'a str,
    asset_type: AssetType,
}

impl<'a> SpriteInfo<'a> {
    pub fn new(file_name: &'a str, ron_name: &'a str, asset_type: AssetType) -> Self {
        SpriteInfo {
            file_name,
            ron_name,
            asset_type,
        }
    }
}

struct TextureLoader<'a> {
    file_name: &'a str,
    texture: Option<Handle<Texture>>,
}

impl<'a> TextureLoader<'a> {
    fn new(file_name: &'a str) -> Self {
        TextureLoader {
            file_name,
            texture: None,
        }
    }

    fn load(&mut self, world: &mut World, counter: &mut ProgressCounter) {
        let loader = world.read_resource::<Loader>();
        let texture_storage = world.read_resource::<AssetStorage<Texture>>();

        self.texture = Some(loader.load(
            self.file_name,
            ImageFormat::default(),
            counter,
            &texture_storage,
        ));
    }
}

struct SpriteLoader<'a> {
    ron_name: &'a str,
    asset_type: AssetType,
    texture_handler: Handle<Texture>,
    sprite_handler: Option<Handle<SpriteSheet>>,
}

impl<'a> SpriteLoader<'a> {
    fn new(ron_name: &'a str, asset_type: AssetType, texture_handler: Handle<Texture>) -> Self {
        SpriteLoader {
            ron_name,
            asset_type,
            texture_handler,
            sprite_handler: None,
        }
    }

    fn load(&mut self, world: &mut World, counter: &mut ProgressCounter) {
        let loader = world.read_resource::<Loader>();
        let sprite_sheet_store = world.read_resource::<AssetStorage<SpriteSheet>>();

        self.sprite_handler = Some(loader.load(
            self.ron_name,
            SpriteSheetFormat(self.texture_handler.clone()),
            counter,
            &sprite_sheet_store,
        ));
    }
}

pub struct SpriteSheetList {
    sprite_sheets: HashMap<AssetType, Handle<SpriteSheet>>,
}

impl SpriteSheetList {
    pub fn default() -> Self {
        SpriteSheetList {
            sprite_sheets: HashMap::new(),
        }
    }

    pub fn get(&self, asset: AssetType) -> Option<Handle<SpriteSheet>> {
        match self.sprite_sheets.get(&asset) {
            Some(sheet) => Some(Handle::from(sheet.clone())),
            None => None,
        }
    }

    pub fn load_from(
        &mut self,
        world: &mut World,
        sprites_info: Vec<SpriteInfo>,
    ) -> Result<ProgressCounter, &'static str> {
        let mut progress_counter = ProgressCounter::new();
        let textures =
            SpriteSheetList::get_textures(world, &sprites_info, &mut progress_counter);

        for texture_loader in &textures {
            for j in 0..sprites_info.len() {
                if texture_loader.file_name != sprites_info[j].file_name {
                    continue;
                }
                let mut sprite_loader = match texture_loader.texture {
                    Some(ref texture_handler) => Some(SpriteLoader::new(
                        sprites_info[j].ron_name,
                        sprites_info[j].asset_type,
                        (*texture_handler).clone(),
                    )),
                    None => None,
                };

                let mut sprite_safe = sprite_loader.ok_or("Cannot init sprite loader")?;
                sprite_safe.load(world, &mut progress_counter);

                let handler = sprite_safe.sprite_handler.unwrap();
                self.sprite_sheets.insert(sprite_safe.asset_type, handler);
            }
        }
        Ok(progress_counter)
    }

    fn get_textures<'a>(world: &mut World,
                    sprites_info: &'a Vec<SpriteInfo>,
                    counter: &mut ProgressCounter) -> Vec<TextureLoader<'a>> {
        let mut textures: Vec<TextureLoader> = Vec::new();

        for sprite_info in sprites_info {
            if textures.iter().any(|v| v.file_name == sprite_info.file_name) {
                continue;
            }
            let mut texture = TextureLoader::new(sprite_info.file_name);

            texture.load(world, counter);
            textures.push(texture);
        }
        textures
    }
}
