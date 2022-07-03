pub trait Updater {
    fn name(&self) -> String;

    fn update(&self);
}