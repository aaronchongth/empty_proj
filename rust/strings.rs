let mut s = String::new();

let data = "initial contents";

let s = data.to_string();

// also works on a literal directly
let s = "initial contents".to_string();

let s = String::from("initial contents");

let mut s = String::from("foo");
s.push_str("bar");


let s1 = String::from("tic");
let s2 = String::from("tic");
let s3 = String::from("tic");
let s = format!("{}-{}-{}", s1, s2, s3);

// slicing strings
let hello = "Здравствуйте";
let s = &hello[0..4];

for c in "नमस्ते".chars() {
    println!("{}", c);
}

for b in "नमस्ते".bytes() {
    println!("{}", b);
}