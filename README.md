# RC4 Key and Weakness Testing

## Introduction
This repository contains a C++ implementation of the RC4 encryption algorithm along with several tests to demonstrate its vulnerabilities and weaknesses.

## Description
RC4 is a key stream symmetric encryption algorithm, known for its simplicity and efficiency. However, it has several weaknesses that make it vulnerable to certain attacks. This project tests these vulnerabilities, focusing on key scheduling and keystream generation flaws.

This project implements several tests to evaluate weaknesses in the RC4 encryption algorithm. The program provides three main tests:

1. **Probability of Second Byte Being Zero:** Calculates the probability of the second byte being zero after RC4 key scheduling and keystream generation.
2. **Probability of Two Consecutive Zero Bytes:** Evaluates the probability of generating two consecutive zero bytes in the keystream.
3. **Related Key Attack and Hamming Distance:** Demonstrates a related key attack on RC4, measuring the Hamming distance between keystreams generated with two related keys.

## Features

- **Custom and Random Key Generation:** Allows users to manually enter a 128-bit key or generate a random one.
- **Detailed Testing Options:** Users can select from three different tests to evaluate RC4 weaknesses.
- **Empirical and Theoretical Probability Calculations:** Provides both empirical and theoretical probabilities for RC4 weaknesses.

Worth mentioning: I know this code is written badly as it's an old code of mine. I will rewrite it and fix bugs as soon as possible.
