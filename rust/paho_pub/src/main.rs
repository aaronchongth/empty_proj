use futures::executor::block_on;
use paho_mqtt as mqtt;
use std::{env, process};

/////////////////////////////////////////////////////////////////////////////

fn main() {
    // Initialize the logger from the environment
    env_logger::init();

    // Command-line option(s)
    let host = env::args()
        .nth(1)
        .unwrap_or_else(|| "tcp://broker.emqx.io:1883".to_string());

    // Create the client
    let cli = mqtt::AsyncClient::new(host).unwrap_or_else(|err| {
        println!("Error creating the client: {}", err);
        process::exit(1);
    });

    if let Err(err) = block_on(async {
        // Connect with default options and wait for it to complete or fail
        println!("Connecting to the MQTT server");
        cli.connect(None).await?;

        // Create a message and publish it
        println!("Publishing a message on the topic 'test'");
        let msg = mqtt::Message::new("test", "Hello Rust MQTT world!", mqtt::QOS_1);
        cli.publish(msg).await?;

        // Disconnect from the broker
        println!("Disconnecting");
        cli.disconnect(None).await?;

        Ok::<(), mqtt::Error>(())
    }) {
        eprintln!("{}", err);
    }
}
