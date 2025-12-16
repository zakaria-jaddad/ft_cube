# 🧊 cub3D - Our First RayCaster 🕹️

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/School-42-000000?style=for-the-badge&logo=42&logoColor=white)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-purple?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

A **"realistic" 3D maze exploration game** inspired by the classic *Wolfenstein 3D*, developed as a project for **42 School**. This program utilizes **raycasting** technology to render a 2D map into a immersive 3D perspective, built entirely from scratch in **C** using the **MiniLibX** graphical library.

✨ **This project was a collaborative effort between [NotSphyynxx] and [zakaria-jaddad].** ✨

**Some pics of the game**

<img width="1008" height="824" alt="Screenshot 2025-12-17 001543" src="https://github.com/user-attachments/assets/30ac20c5-7d5e-4648-9017-6bc00628f5f6" />

---

<img width="1003" height="826" alt="Screenshot 2025-12-17 001601" src="https://github.com/user-attachments/assets/53ddb09c-bdd0-41cb-aa58-c7d4b4760aaa" />

---

<img width="1005" height="825" alt="Screenshot 2025-12-17 001616" src="https://github.com/user-attachments/assets/7cfd4ae3-6b38-45c7-a93e-b98f5c101367" />


---

## 🚀 Features

### ✅ Mandatory Part
*   **🧠 Raycasting Engine**: Smoothly renders a 3D world from a 2D grid map.
*   **🧱 Textured Walls**: Distinct textures for **North**, **South**, **East**, and **West** facing walls.
*   **🎨 Custom Colors**: Solid RGB colors for the **Floor** and **Ceiling**.
*   **🕹️ Smooth Movement**: Fluid player movement and camera rotation.
*   **📁 Robust Parsing**: Reads `.cub` files with strict error management for invalid maps or configurations.
*   **🪟 Window Management**: Clean exit via `ESC` or clicking the `X` button.

### 🌟 Bonus Part
*   **🗺️ Minimap**: A real-time 2D radar showing player position and rays.
*   **🛑 Wall Collisions**: precise physics preventing the player from phasing through walls.
*   **🖱️ Mouse Look**: Rotate the camera view with your mouse for modern FPS controls.
*   **🚪 Interactive Doors**: Open and close doors to navigate new areas.
*   **👾 Animated Sprites**: 2D objects and decorations placed within the 3D world.

---

## 🛠️ How to Run

### 📋 Prerequisites
*   🐧 A Unix-based system (Linux / macOS)
*   ⚙️ `gcc` compiler & `make`
*   🖥️ **MiniLibX** library (installed locally or on the system)

### ⚙️ Compilation
1.  **Clone the repository:**
    ```
    git clone [git@github.com:zakaria-jaddad/ft_cube.git]
    cd cub3D
    ```
2.  **Compile the mandatory part:**
    ```
    make
    ```
3.  **Compile with BONUS features (Doors, Minimap, etc.):**
    ```
    make bonus
    ```

### 🏃 Execution
Run the executable with a map path:
./cub3D maps/valid_map.cub

---

## 🎮 Controls

| Key | Action | Context |
| :---: | :--- | :--- |
| **`W`** | ⬆️ Move Forward | Movement |
| **`S`** | ⬇️ Move Backward | Movement |
| **`A`** | ⬅️ Strafe Left | Movement |
| **`D`** | ➡️ Strafe Right | Movement |
| **`←`** | 🔄 Rotate Left | Camera |
| **`→`** | 🔄 Rotate Right | Camera |
| **`ESC`** | ❌ Quit Game | System |
| **`O`** | 🚪 **Open Door** | **Bonus** |
| **`C`** | 🔒 **Close Door** | **Bonus** |
| **`Mouse`** | 👀 Look Around | **Bonus** |

---

## 🗺️ `.cub` Scene File Format

The program accepts a description file (`.cub`) to generate the world.

### 1️⃣ Textures
Define paths to your wall textures:
*   🧭 **NO** `./path_to_north.png`
*   🧭 **SO** `./path_to_south.png`
*   🧭 **WE** `./path_to_west.png`
*   🧭 **EA** `./path_to_east.png`

### 2️⃣ Colors
Define RGB colors `[0-255]` for the environment:
*   👇 **F** `220,100,0` (Floor)
*   👆 **C** `225,30,0` (Ceiling)

### 3️⃣ The Map
The map must be the **last element** in the file.
*   `1` = Wall ⬛
*   `0` = Empty Space ⬜
*   `N`, `S`, `E`, `W` = Player Start & Orientation 🧍

**Example File:**
```
NO ./textures/wall_n.png
SO ./textures/wall_s.png
WE ./textures/wall_w.png
EA ./textures/wall_e.png

F 20,20,20
C 200,200,200

1111111111
1000000001
10000N0001
1000000001
1111111111
```


---

## 🧹 Makefile Rules

*   `make`: Compile the mandatory program.
*   `make bonus`: Compile the full game with bonuses.
*   `make clean`: Remove object files (`.o`).
*   `make fclean`: Remove object files and the executable.
*   `make re`: Recompile everything from scratch.

---
Made with ❤️ and ☕ by **[Larhrib Ismail]** & **[Zakaria Jaddad]**
