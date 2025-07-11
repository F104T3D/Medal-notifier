# Steam Game Medal Launcher

This project is a Windows background utility that monitors for running Steam games and automatically launches **Medal** (a game clip recording software) when a Steam game is detected. Once the game ends, the utility restarts itself and waits for the next game session.

## Features

- Detects running Steam games based on their executable paths.
- Launches `Medal.exe` automatically when a game starts.
- Restarts itself after the game closes.
- Runs in the background with minimal resource usage.

## Requirements

- Windows OS
- Qt Creator
- CMake
- Ninja
- Medal installed (make sure `Medal.exe` is accessible)
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

5. **Edit `LaunchMedal()` in `main.cpp`:**  
   Replace `"FILEPATH"` with the full path to your `Medal.exe`, for example:

   ```cpp
   ShellExecuteW(NULL, L"open", L"C:\\Program Files\\Medal\\Medal.exe", NULL, NULL, SW_SHOWNORMAL);
   ```

6. **Run the application:**
   - The app runs in the background and checks for any active Steam games every 30 seconds.
   - If a game is detected and `Medal.exe` is not running, it will launch Medal.
   - When the game closes, the app will restart itself to ensure a clean state.

## Notes

- Add a GUI or system tray icon in the future using Qt if you want to improve usability.
- The application assumes Steam games are launched from the typical `steamapps` path.
- Make sure to run the application with sufficient permissions to access other processes (admin may be required in some cases).

## License

This project is provided for personal use. Feel free to modify it to suit your workflow. Idgaf what you do with it
