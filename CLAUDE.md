# CLAUDE.md

## Repository Overview

This repository contains a structured study archive for **IT CookBook, TCP/IP Windows Socket Programming**.

It focuses on:
- Winsock-based TCP/IP programming
- practical client-server implementations
- exercise solutions and experimentation
- building a reusable reference for network programming

## Purpose

The goals of this repository are to:

- understand TCP/IP fundamentals through implementation
- master Windows socket programming (Winsock API)
- build reliable client-server systems
- document practical insights and edge cases
- create a long-term engineering reference

## Structure

```text
src/
├─ ch01_network_basics/
├─ ch02_winsock_setup/
├─ ch03_address_structures/
├─ ch04_tcp/
├─ ch05_data_transfer/
├─ ch06_multithreading/
├─ ch07_udp/
├─ ch08_socket_options/
├─ ch09_gui/
├─ ch10_io_models_1/
├─ ch11_io_models_2/
├─ ch12_raw_sockets/
├─ ch13_additional_protocols/
└─ ch14_final_project/
```

Each chapter contains:
- `examples/` (rewritten sample code)
- `exercises/` (personal solutions)
- optional `notes.md`

## Visual Studio Setup

- Single solution file (recommended): `TcpIpWindowsSocketProgramming.sln`
- Multiple small projects per chapter
- Use solution folders for chapter grouping

## Naming Conventions

- examples: `ex_<chapter>_<topic>`
- exercises: `exercise_<chapter>_<number>`

## Development Environment

- IDE: Visual Studio 2022
- Language: C++
- Platform: Windows
- API: Winsock2
- Standard: C++17 or later

## Study Approach

1. Understand the networking concept
2. Rebuild sample code independently
3. Test behavior with simple cases
4. Solve exercises without copying
5. Document findings briefly

## Study Rules

1. Do not copy the book verbatim
2. Focus on understanding APIs and behavior
3. Keep code simple and explicit
4. Separate examples and exercises
5. Record mistakes and edge cases

## Disclaimer

This repository is for educational purposes only.

It does not redistribute the original book content.
All code is independently written or adapted for study.
