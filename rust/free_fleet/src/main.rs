use serde::{Deserialize, Serialize};
use serde_json::Result;

pub trait State {
    fn update_value(&self);

    fn get_value(&self);
}

#[derive(Serialize, Deserialize)]
pub struct BatteryPercentage {
    pub battery_percentage: f32,
}

// impl State for BatteryPercentage {
//     fn update_value()
// }

pub trait Feature {
    fn run_once(&self);

    fn 
}

fn main() {
    let data = r#"
        {
            "battery_percentage": 123.23
        }"#;

    let b: BatteryPercentage = serde_json::from_str(data)
        .expect("failed to get from json data");
    
    println!("Hello, world!");
}
