# Steam Game Monitor + Medal Auto-Launcher

This Windows application monitors active processes to detect when a Steam game is launched (based on the presence of "steamapps" in its file path). If the Medal app is not running, it automatically launches it.
Once the game session ends, the application restarts itself to monitor for the next game launch.

## Features

- Detects when a Steam game is running.
- Automatically launches `Medal.exe` if it's not already running.
- Displays a message box after launching Medal (can be customized).
- Restarts itself after the game closes for continuous monitoring.

## Usage

1. Replace `FILEPATH` in the `LaunchMedal()` function with the full path to your `Medal.exe` (e.g., `L"C:\\Program Files\\Medal\\Medal.exe"`).
2. Build the project using a C++ compiler that supports Windows API (e.g., Visual Studio).
3. Run the compiled executable. It will continuously check for Steam games and launch Medal as needed.

## Requirements

- Windows
- A Steam game installed
- Medal installed
- Admin privileges might be required to read process information, but in testing this was not apparent

## Notes

- The MessageBox is currently blank—customize it with a message if desired.
- The program uses `ShellExecute` to restart itself and launch Medal.
