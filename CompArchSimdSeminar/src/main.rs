#![feature(portable_simd)]
#![allow(dead_code)]
use core_simd::*;
use std::time::Instant;

const N: usize = 10000000;
const X: usize = 32;
fn use_simd(f: Vec<Simd<i8, X>>) -> Vec<Simd<i8, X>> {
    f.into_iter().map(|x| x * 2).collect::<Vec<Simd<i8, X>>>()
}
fn no_simd(f: Vec<i8>) -> Vec<i8> {
    f.into_iter().map(|x| x * 2).collect::<Vec<i8>>()
}
fn timer<T, F: FnOnce() -> Vec<T>>(f: F) -> Vec<T> {
    let start = Instant::now();
    let g = f();
    println!("{:?}", start.elapsed());
    g
}

fn main() {
    println!("NO SIMD");
    let f = vec![2; X * N];
    let g = timer(move || no_simd(f));

    println!("WITH SIMD");
    let a = i8x32::from_array([2; X]);
    let f = vec![a; N];
    let h = timer(move || use_simd(f))
        .into_iter()
        .map(|x| x.as_array().to_vec())
        .into_iter()
        .flatten()
        .collect::<Vec<i8>>();

    assert_eq!(g, h);
}

