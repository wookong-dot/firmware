
# Firmware Guideline

## Chip
ARM SC300, cortex M3 level
192MHz RAM:384KB  FLASH:512KB
IO:USB/SPI/UART/GPIO/ADC, secure boot,OTP and MPU

## IDE
KEIL5, armcc and arm-gcc
compile schnorrkel libsr.a to hex with arm-gcc and using fixed function address to access by main project compiled by armcc.

## modules

### USB
### HAL
* FLASH
* TIMER
* Button control via GPIO
* OLED screen via SPI
### Wallet
* Entropy generate using hardware random source which is physical noise
* Entropy to Mnemonic
* Mnemonic recovery and back up using only screen and buttons on device
* Mnemonic to seed
* Seed to root private key
* Derive for each coins
### Bootloader 
There will be a secure boot-loader for the firmware update. It will verify the hash and signature of the main firmware of course.  
Build test tools by sending USB commands in test scripts to test the firm on EVB abd we wll have strictly code security review.

## How to complie schnorrkel for Cortex

### Core list:
* thumbv6m-none-eabi, for the Cortex-M0 and Cortex-M1 processors
* thumbv7m-none-eabi, for the Cortex-M3 processor
* thumbv7em-none-eabi, for the Cortex-M4 and Cortex-M7 processors
* thumbv7em-none-eabihf, for the Cortex-M4F and Cortex-M7F processors

### Add target
rustup target add thumbv7m-none-eabi //for M3
cargo build --target thumbv7m-none-eabi

or

Create .cargo/config and add
[build]
target = "thumbv7m-none-eabi"    # Cortex-M3


### TO BE DONE
1. Git Clone https://github.com/w3f/schnorrkel
Set all dependcies to no_std
1. merlin 
a. rand_core = { version = "0.3", default-features = false } 
b. byteorder = { version = "1.2.4", default-features = false }
c. keccak = { version = "0.1.0", default-features = false }
d. close [dev-dep..]
e. close [features]
f. strobe.rs 
//use std::ops::{Deref, DerefMut};
use core::ops::{Deref, DerefMut};
g.transcript.rs finalise_simple() finalise_trng()



2.ed25519-dalek
a.secret.rs and ed25519.rs close generate
b.close rand dep


Set backend to 32bit

Add static lib to toml
[lib]
name = "sr"
path = "src/lib.rs"
crate-type = ["staticlib"]