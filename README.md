# Dungeon Battle Game (C++)

A robust, text-based terminal combat simulation game engineered in strict compliance with modern standard ISO C++ paradigms. This repository demonstrates the practical application of core Object-Oriented Programming (OOP) principles, featuring runtime polymorphism via dynamic binding, pure virtual abstract interfaces, structured inheritance hierarchies, and protective input stream sanitization routines.


## 🛠️ Tech Stack & Software Environment

* **Programming Language:** Standard ISO C++ (C++11/C++14/C++17/C++20 Compliant).
* **Compiler Subsystem:** MSVC (Microsoft Visual C++ Compiler) / LLVM Clang.
* **Target OS / Platform:** Cross-platform compatible (Optimized for Windows Command Prompt/PowerShell environments).



## 📁 System Architecture & File Structure

The project utilizes a simplified, monolithic file layout optimized to maintain single-thread compilation efficiency and prevent external assembly linkage or reference errors within standard compiler environments:

```text
OOP_CPP_Dungeon_Battle/
│
├── main.cpp  # Unified source file containing core logic, classes, and main game loop.
└── README.md                # Detailed repository overview, technical specifications, and manual.

```

The application separates internal mechanics using strict access specifiers, declaring foundational entity attributes within a `protected` layer to allow child class accessibility while prohibiting outside structural modifications.



## 🧬 Applied OOP Design Patterns & Software Techniques

### 1. Abstract Interfaces & Strict Class Hierarchies

The foundational runtime core is organized around the `Character` abstract base class. It establishes a mandatory structural contract for all subclasses via the pure virtual function signature: `virtual string getTeam() const = 0;`. Concrete implementations (`Knight`, `Archer`, `Orc`, and `Goblin`) leverage public inheritance derivation schemas to inherit common fields seamlessly without structural code duplication.

### 2. Runtime Polymorphism via Dynamic Binding

All live concrete instances are populated dynamically into a unified collection mapping to base class pointers (`std::vector<Character*>`). The core game manager interacts exclusively with these generalized base indicators. This allows the Virtual Method Table (VMT) to resolve overriding operational logic paths—such as specialized class-based `attack()` variants or protective `receiveAttack()` filters—dynamically during execution loops.

### 3. Comprehensive Memory Ownership Control

To guarantee the complete elimination of standard pointer allocation heap leaks, an explicit public virtual destructor is embedded within the `Character` parent interface: `virtual ~Character() {}`. Upon application termination, this structure triggers a sequential, top-down deletion sequence that cleanly releases derived object allocations before the parent envelope is wiped from the heap.



## 🎮 Character Specific Mechanics & Ability Matrix

The simulation handles unscripted, turn-based combat exchanges between conflicting factions using precise probability filters driven by seeded `rand()` routines:

### Knight (Hero Faction)

* **Attributes:** Base HP: 120 | Base ATK: 15
* **Specialized Ability:** **Holy Shield** – Possesses an integrated 60% probability to intercept incoming damage tracks, instantly mitigating the total incoming hit amount by 20% (taking only 80% of the normal damage).

### Archer (Hero Faction)

* **Attributes:** Base HP: 90 | Base ATK: 18
* **Specialized Ability:** **Ammunition Layer** – Spawns with a randomized supply of 1 to 6 arrows. While arrows remain in storage, the Archer consumes 1 arrow per round to deal an enhanced 1.5x damage multiplier. Once empty, the logic seamlessly reverts to standard baseline attacks.

### Orc (Monster Faction)

* **Attributes:** Base HP: 140 | Base ATK: 12
* **Specialized Ability:** **Evasive Swiftness** – Features a built-in 15% absolute probability to completely dodge incoming attack streams, nullifying the opponent's turn and taking 0 damage.

### Goblin (Monster Faction)

* **Attributes:** Base HP: 75 | Base ATK: 10
* **Specialized Ability:** **Sneak Attack** – Features a 25% tactical probability (1-in-4 chance) to bypass standard attack limits and execute a critical strike, dealing double damage to the targeted character.



## 🛡️ Robust Defensive Checking & Input Sanitization

To ensure maximum application resilience against unexpected console terminal inputs, the system enforces a strict input sanitization grid:

* **Alphanumeric Stream Formatting Caps:** When collecting integer options (such as character selections), if an invalid character token like 'd' is supplied, the application deploys `std::cin.clear()` and `std::cin.ignore()` routines. This flushes the bad data from the stream buffer immediately to prevent infinite application loops or thread freezes.
* **Menu Out-of-Bounds Interception:** Intercepts out-of-range inputs by verifying choices against `std::vector::size()` before processing index offsets, completely preventing segmentation faults or invalid index lookups.
* **Strict Session Retry Boundary (y/n):** The play-again confirmation block runs within an isolated evaluation loop, actively ignoring non-compliant characters and forcing correct choice criteria without dropping active execution threads.



## 📈 Engineering Takeaways & Runtime Analysis

The game orchestrator sets up an asynchronous turn manager that randomly awards the starting initiative to one of the two active combatants using seed-based coin flips. Turns alternate inside a synchronized execution loop.

A critical design challenge resolved during the development of this engine was preventing a defeated character from triggering a post-mortem counter-attack within the same round. This was solved by inserting immediate execution lifestyle validation boundaries post-attack, checking health states right away so that combat loops break instantly upon an entity's death. The final code balances strong data shielding through `const` correctness with highly stable, deterministic runtime performance.
