use zenoh::prelude::r#async::*;

#[async_std::main]
async fn main() {
    let session = zenoh::open(zenoh::config::default()).res().await.unwrap();

    let replies = session.get("**/temp").res().await.unwrap();
    while let Ok(reply) = replies.recv_async().await {
        match reply.sample {
            Ok(s) => {
                let temp: f64 = s.value.clone().try_into().unwrap();
                println!("Reply: {} {} ({})", s.key_expr, temp, s.encoding)
            }
            Err(e) => println!("Error: {}", e),
        }
    }
}
