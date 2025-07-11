# Steam Game Medal Launcher

This project is a Windows background utility that monitors for running Steam games and automatically launches **Medal** (a game clip recording software) when a Steam game is detected. Once the game ends, the utility restarts itself and waits for the next game session.

## 🔽 Download

You can download the latest precompiled `.exe` from the [Releases](https://github.com/F104T3D/Medal-notifier/releases/) section.

1. Extract the zip from the release section
2. Edit `medal_path.txt` to point to your Medal installation
3. Right click the downloaded exe to open it's properties and select `Create Shortcut`
4. Put the shortcut into your shell startup, found by doing Win+R then typing `shell:startup`.

**Example `medal_path.txt` content:**

```
C:\Program Files\Medal\Medal.exe
```

> ⚠️ Make sure the path points to the correct `Medal.exe`. If it's incorrect or missing, you'll see an error message.

## Features

- Detects running Steam games based on their executable paths.
- Launches `Medal.exe` using the path from a simple `medal_path.txt` file.
- Restarts itself after the game closes.
- Runs in the background with minimal resource usage.

## Requirements

- Windows OS
- Qt Creator
- CMake
- Ninja
- Medal installed
- Steam installed (games must be launched via Steam)

## Setup Instructions

1. **Clone or download the project source.**

2. **Open the project in Qt Creator:**
   - Go to `File` → `Open File or Project...` and select the `CMakeLists.txt` file.
   - When prompted, choose your desired build kit and generator (e.g., Ninja).

3. **Configure build settings (if needed):**
   - Ensure your build environment has access to the Windows SDK.
   - Verify that `PSAPI_VERSION` is defined in your C++ settings (already defined in the code).

4. **Build the project:**
   - Use the **Build** button in Qt Creator or press `Ctrl + B`.

5. **Create the Medal path file:**
   - In the same folder as the `.exe`, create a file named `medal_path.txt`.
   - Paste the full path to your installed `Medal.exe` into the file.
   - Example:
     ```
     C:\Program Files\Medal\Medal.exe
     ```

6. **Run the application:**
   - The app runs in the background and checks for any active Steam games every 30 seconds.
   - If a game is detected and `Medal.exe` is not running, it will launch Medal using the path from `medal_path.txt`.
   - When the game closes, the app will restart itself to ensure a clean state.

## Notes

- You can add a GUI or system tray icon in the future using Qt if you want to improve usability.
- The application assumes Steam games are launched from the typical `steamapps` path.
- Make sure to run the application with sufficient permissions to access other processes (admin may be required in some cases).

## License

This project is provided for personal use. Feel free to modify it to suit your workflow. Idgaf what you do with it.
