use async_std::{
    prelude::FutureExt,
    sync::{Arc, RwLock},
};
use std::collections::HashMap;
use zenoh::prelude::r#async::*;

#[async_std::main]
async fn main() {
    let key_expr = KeyExpr::try_from("room/*/temp").unwrap();
    let storage = Arc::new(RwLock::new(HashMap::new()));
    let session = zenoh::open(zenoh::config::peer())
        .res()
        .await
        .unwrap()
        .into_arc();

    // sub
    let c_keyexpr = key_expr.clone();
    let c_storage = storage.clone();
    let c_session = session.clone();
    let h_sub = async_std::task::spawn(async move {
        let sub = c_session.declare_subscriber(c_keyexpr).res().await.unwrap();

        while let Ok(sample) = sub.recv_async().await {
            let temp: f64 = sample.value.clone().try_into().unwrap();
            println!(
                "Sub: {} {} ({})",
                sample.key_expr, temp, sample.value.encoding
            );
            let mut w_guard = c_storage.write().await;
            w_guard.insert(sample.key_expr.clone(), sample);
        }
    });

    // queryable
    let c_keyexpr = key_expr.clone();
    let c_storage = storage.clone();
    let c_session = session.clone();
    let h_qble = async_std::task::spawn(async move {
        let qble = c_session
            .declare_queryable(c_keyexpr.clone())
            .res()
            .await
            .unwrap();

        while let Ok(query) = qble.recv_async().await {
            println!("Query: {} ", query.key_expr());
            let r_guard = c_storage.read().await;
            let samples = r_guard
                .iter()
                .filter(|(k, _)| keyexpr::intersects(k, query.key_expr()))
                .map(|(_, s)| s);
            for s in samples {
                let temp: f64 = s.value.clone().try_into().unwrap();
                println!("Reply: {} {} ({})", s.key_expr, temp, s.value.encoding);
                query.reply(Ok(s.clone())).res().await.unwrap();
            }
        }
    });

    h_sub.join(h_qble).await;
}
