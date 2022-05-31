use std::sync::{Arc, Mutex};
use std::thread;
use std::rc::Rc;

fn main() {
    // when we clone counter later, the reference count goes up in a
    // non-thread safe way, we use Arc, astomic
    // let counter = Rc::new(Mutex::new(0));
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());
}

// fn main() {
//     let m = Mutex::new(5);
// 
//     {
//         let mut num = m.lock().unwrap();
//         *num = 6;
//     }
// 
//     println!("m = {:?}", m);
// }
