use serde::{Deserialize, Serialize};
// use serde_json::Result;
use std::collections::HashMap;

pub trait StateComponent {
    fn name(&self) -> String;

    fn update(&mut self);

    fn get(&self) -> String;
}

#[derive(Serialize, Deserialize)]
pub struct SCInt {
    value: i32,
}

impl StateComponent for SCInt {
    fn name(self: &SCInt) -> String {
        String::from("sc_int")
    }

    fn update(self: &mut SCInt) {
        self.value += 1;
        // println!("update called from {}", self.name());
    }

    fn get(self: &SCInt) -> String {
        serde_json::to_string(self).unwrap()
    }
}

#[derive(Serialize, Deserialize)]
pub struct SCFloat {
    value: f32,
}

impl StateComponent for SCFloat {
    fn name(self: &SCFloat) -> String {
        String::from("sc_float")
    }

    fn update(self: &mut SCFloat) {
        self.value += 0.001;
        // println!("update called from {}", self.name());
    }

    fn get(self: &SCFloat) -> String {
        serde_json::to_string(self).unwrap()
    }
}

pub struct Client {
    // state_components: Vec<Box<dyn StateComponent>>,
    state_components: HashMap<String, Box<dyn StateComponent>>,
    state: HashMap<String, String>,
    // features
}

impl Client {
    pub fn run_once(self: &mut Client) {
        for (k, v) in self.state_components.iter_mut() {
            v.update();
            self.state.insert(v.name(), v.get());
        }
    }

    pub fn print_state_json(self: &Client) {
        println!("{}", serde_json::to_string(&self.state).unwrap());
    }
}

fn main() {
    // let data = r#"
    //     {
    //         "battery_percentage": 123.23
    //     }"#;

    // let b: BatteryPercentage = serde_json::from_str(data)
    //     .expect("failed to get from json data");
    
    // println!("Hello, world!");

    let sc_int: Box<dyn StateComponent> = Box::new(SCInt {value: 123});
    let sc_float: Box<dyn StateComponent> = Box::new(SCFloat {value: 0.123});

    let mut client: Client = Client {
        // state_components: vec![
        //     Box::new(SCInt {value: 123}),
        //     Box::new(SCFloat {value: 0.123}),
        // ],
        state_components: HashMap::from([
            (sc_int.name(), sc_int),
            (sc_float.name(), sc_float),
        ]),
        state: HashMap::new()
    };

    for _ in 0..10 {
        client.run_once();
        client.print_state_json();
    }
}

// Things to implement
// * Duplicate StateComponents
// * Worker trait with run async
// * Middleware, using paho_mqtt
// * Always use Result