// fn largest(list: &[i32]) -> i32 {
//     let mut largest = list[0];
//     for &item in list {
//         if item > largest {
//             largest = item;
//         }
//     }
//     largest
// }

// fn largest_i32(list: &[i32]) -> i32 {
//     let mut largest = list[0];

//     for &item in list {
//         if item > largest {
//             largest = item;
//         }
//     }

//     largest
// }

// fn largest_char(list: &[char]) -> char {
//     let mut largest = list[0];

//     for &item in list {
//         if item > largest {
//             largest = item;
//         }
//     }

//     largest
// }

// fn largest<T>(list: &[T]) -> T {
//     let mut largest = list[0];
//     for &item in list {
//         if item > largest {
//             largest = item;
//         }
//     }
//     largest
// }

// fn main_temp() {
//     // println!("Hello, world!");
//     // let number_list = vec![34, 50, 25, 100, 65];
//     // let mut largest = number_list[0];
//     // for number in number_list {
//     //     if number > largest {
//     //         largest = number;
//     //     }
//     // }
//     // let result = largest(&number_list);
//     // println!("The largest number is {}", result);
    
//     // let number_list = vec![102, 34, 6000, 89, 54, 2, 43, 8];
//     // let mut largest = number_list[0];
//     // for number in number_list {
//     //     if number > largest {
//     //         largest = number;
//     //     }
//     // }
//     // let result = largest(&number_list);
//     // println!("The largest number is {}", result);

//     // let result = largest_i32(&number_list);
//     // println!("The largest number is {}", result);

//     let number_list = vec![34, 50, 25, 100, 65];
//     let char_list = vec!['y', 'm', 'a', 'q'];

//     // let result = largest_char(&char_list);
//     // println!("The largest char is {}", result);

//     let result = largest(&number_list);
//     println!("The largest number is {}", result);

//     let char_list = vec!['y', 'm', 'a', 'q'];

//     let result = largest(&char_list);
//     println!("The largest char is {}", result);
// }

struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T> {
    fn x(&self) -> &T {
        &self.x
    }
}

// This code means the type Point<f32> will have a method named
// distance_from_origin and other instances of Point<T>
// where T is not of type f32 will not have this method defined
impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

// for multiple types, we use
// struct Point<T, U> {
//     x: T,
//     y: U
// }

fn main() {
    let integer = Point { x: 5, y: 10 };
    let float = Point { x: 1.0, y: 4.0 };

    // will work for the second point type
    // let wont_work = Point { x: 5, y: 4.0 };

    let p = Point { x: 5, y: 10 };
    println!("p.x = {}", p.x());
}
