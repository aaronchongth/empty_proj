use std::fs::File;
// use std::io::ErrorKind;
// use std::io::{self, Read};
use std::error::Error;

// fn read_username_from_file() -> Result<String, io::Error> {
//     let f = File::open("hello.txt");

//     let mut f = match f {
//         Ok(file) => file,
//         Err(e) => return Err(e),
//     };

//     let mut s = String::new();

//     match f.read_to_string(&mut s) {
//         Ok(_) => Ok(s),
//         Err(e) => Err(e),
//     }
// }

// // use ? to remove boiler plate
// fn read_username_from_file() -> Result<String, io::Error> {
//     let mut f = File::open("hello.txt")?;
//     let mut s = String::new();
//     f.read_to_string(&mut s)?;
//     Ok(s)
// }

// // reduce boiler plate further
// fn read_username_from_file() -> Result<String, io::Error> {
//     let mut s = String::new();
//     File::open("hello.txt")?.read_to_string(&mut s)?;
//     Ok(s)
// }

// // even shorter
// fn read_username_from_file() -> Result<String, io::Error> {
//     fs::read_to_string("hello.txt")
// }

fn last_char_of_first_line(text: &str) -> Option<char> {
    text.lines().next()?.chars().last()
}

// fn main() {
//     // let f = File::open("hello.txt");
//     // let f = match f {
//     //     Ok(file) => file,
//     //     Err(error) => panic!("Problem opening the file: {:?}", error),
//     // };

//     // matching on different errors
//     // let f = match f {
//     //     Ok(file) => file,
//     //     Err(error) => match error.kind() {
//     //         ErrorKind::NotFound => match File::create("hello.txt") {
//     //             Ok(fc) => fc,
//     //             Err(e) => panic!("Problem creating the file: {:?}", e),
//     //         },
//     //         other_error => {
//     //             panic!("Problem opening the file: {:?}", other_error)
//     //         }
//     //     },
//     // };

//     // using closures
//     // let f = File::open("hello.txt").unwrap_or_else(|error| {
//     //     if error.kind() == ErrorKind::NotFound {
//     //         File::create("hello.txt").unwrap_or_else(|error| {
//     //             panic!("Problem creating the file: {:?}", error);
//     //         })
//     //     } else {
//     //         panic!("Problem opening the file: {:?}", error);
//     //     }
//     // });

//     // let f = File::open("hello.txt").unwrap();
//     // let f = File::open("hello.txt").expect("Failed to open hello.txt");
// }

fn main() -> Result<(), Box<dyn Error>> {
    let f = File::open("hello.txt")?;
    Ok(())
}

