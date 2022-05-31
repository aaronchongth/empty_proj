// simple approach
fn is_in_array(array: &Vec<i32>, target: i32) -> bool {
    for &item in array {
        if item == target {
            return true;
        }
    }
    return false;
}

// Naive approach
// fn are_targets_in_array(array: &Vec<i32>, targets: &Vec<i32>) -> bool {
//     for &target in targets {
//         let mut target_not_found: bool = true;
//         for &item in array {
//             if target == item {
//                 target_not_found = false;
//                 break;
//             }
//         }
//         if target_not_found {
//             return false;
//         }
//     }
//     return true;
// }

// Naive approach reuse
fn are_targets_in_array(array: &Vec<i32>, targets: &Vec<i32>) -> bool {
    for &target in targets {
        if !is_in_array(&array, target) {
            return false;
        }
    }
    return true;
}

// Sorted approach

fn main() {
    let input = vec![1,2,3,4,5,6,99,123];
    let target = 1234;
    let targets = vec![123, 4, 99, 1234];

    if is_in_array(&input, target) {
        println!("{} is in input.", target);
    } else {
        println!("{} is not in input.", target);
    }

    if are_targets_in_array(&input, &targets) {
        println!("All targets found");
    } else {
        println!("Not all targets were found.");
    }

    println!("input is {:?}", input);
    
    let sorted_input = input.Sorted();
    println!("sorted input is {:?}", sorted_input);
}
