use zenoh::prelude::r#async::*;

#[async_std::main]
async fn main() {
    let key_expr = KeyExpr::try_from("room/bedroom/temp").unwrap();

    let session = zenoh::open(zenoh::config::default()).res().await.unwrap();

    let qble = session
        .declare_queryable(key_expr.clone())
        .res()
        .await
        .unwrap();

    while let Ok(query) = qble.recv_async().await {
        println!("Query: {} ", query.key_expr());
        let temp = 19.5;
        let value: Value = temp.into();
        println!("Reply: {} {} ({})", key_expr, temp, value.encoding);
        query
            .reply(Ok(Sample::new(key_expr.clone(), temp)))
            .res()
            .await
            .unwrap();
    }
}
